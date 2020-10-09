/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 * 
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  BswM.c
 *        \brief  MICROSAR Basic Software Mode Manager
 *
 *      \details  Implements AUTOSAR BswM.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 * 
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define BSWM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BswM.h"
#include "BswM_Private_Cfg.h"
#if ( BSWM_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif

#include "SchM_BswM.h"

#if ( BSWM_ENABLE_WDGM == STD_ON )
/* BswM_WdgM.h is included here instead of BswM_Private_Cfg.h because it includes Os.h */
# include "BswM_WdgM.h"
#endif

#if (BSWM_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
# include "EcuM_Error.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if((BSWM_SW_MAJOR_VERSION != (0x11)) || \
    (BSWM_SW_MINOR_VERSION != (0x01)) || \
    (BSWM_SW_PATCH_VERSION != (0x00)) )
# error "Vendor specific version numbers of BswM.c and BswM.h are inconsistent"
#endif

/*********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define BSWM_REQUEST_SEMAPHORE_UNLOCKED   (0u)
#define BSWM_REQUEST_SEMAPHORE_LOCKED     (1u)

#if(BSWM_IMMEDIATEUSER == STD_ON)
# define BSWM_REQUEST_IDLE                (0x00u)
# define BSWM_REQUEST_QUEUED              (0x01u)
# define BSWM_REQUEST_PROCESSED           (0x02u)
# define BSWM_REQUEST_PENDING             (0x03u)
# define BSWM_REQUEST_QUEUE_RELEASE       (0x04u)
#endif

#define BSWM_ACTIONLIST_IDLE              (0x00u)
#define BSWM_ACTIONLIST_PENDING           (0x01u)
#define BSWM_ACTIONLIST_BLOCKED           (0xFFu)

#define BSWM_INVALID_PARTITION            (0xFFu)

#define BSWM_SYNC_LEVEL_ONE               (0x01u)
#define BSWM_SYNC_LEVEL_TWO               (0x02u)


#if !defined (BSWM_LOCAL) /* COV_BSWM_LOCAL TX */
# define BSWM_LOCAL static
#endif

#if !defined (BSWM_LOCAL_INLINE) /* COV_BSWM_LOCAL_INLINE TX */
# define BSWM_LOCAL_INLINE LOCAL_INLINE
#endif

#if defined ECUM_WKSTATUS_ENABLED /* COV_BSWM_ECUM_COMPATIBILITY */
# define BSWM_ECUM_MAX_WKSTATUS ECUM_WKSTATUS_ENABLED
#elif defined ECUM_WKSTATUS_CHECKWAKEUP /* COV_BSWM_ECUM_COMPATIBILITY */
# define BSWM_ECUM_MAX_WKSTATUS ECUM_WKSTATUS_CHECKWAKEUP
#else /* COV_BSWM_ECUM_COMPATIBILITY */
# define BSWM_ECUM_MAX_WKSTATUS ECUM_WKSTATUS_DISABLED
#endif

/*********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#if (BSWM_IMMEDIATEUSER == STD_ON)
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#  define BSWM_CALL_IMMEDIATE(start, end, sid, partitionIdx) BswM_ImmediateModeRequest((BswM_SizeOfImmediateUserType)(start), (BswM_SizeOfImmediateUserType)(end), (sid), (partitionIdx))
# else
/* PRQA S 3453 1 */ /* MD_MSR_FctLikeMacro */
#  define BSWM_CALL_IMMEDIATE(start, end, sid, partitionIdx) BswM_ImmediateModeRequest((BswM_SizeOfImmediateUserType)(start), (BswM_SizeOfImmediateUserType)(end), (partitionIdx))
# endif
#endif

/* Dummy Statements */
#if (BSWM_DEV_ERROR_DETECT == STD_ON)
# define BSWM_DUMMY_STATEMENT_DET_OFF(statement) /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#else
# define BSWM_DUMMY_STATEMENT_DET_OFF(statement) BSWM_DUMMY_STATEMENT((statement)) /* PRQA S 1338, 2983, 3112, 3453 */ /* MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_MSR_FctLikeMacro */
#endif

#if (BSWM_DEV_ERROR_DETECT == STD_ON) && (BSWM_MODE_CHECK == STD_ON)
# define BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(statement) /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#else
# define BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(statement) BSWM_DUMMY_STATEMENT((statement)) /* PRQA S 1338, 2983, 3112, 3453 */ /* MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_MSR_DummyStmt, MD_MSR_FctLikeMacro */
#endif

#if (BSWM_MULTIPARTITION == STD_OFF)
# define BswM_GetPartitionIdx() 0u
#endif

/*********************************************************************************************************************
 * Development Error Detection                                                                                       
 *********************************************************************************************************************/
#define BswM_EnterCriticalArea_0()      SchM_Enter_BswM_BSWM_EXCLUSIVE_AREA_0()
#define BswM_LeaveCriticalArea_0()      SchM_Exit_BswM_BSWM_EXCLUSIVE_AREA_0()

/*********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"

#if (BSWM_USE_INIT_POINTER == STD_ON)
P2CONST(BswM_ConfigType, AUTOMATIC, BSWM_PBCFG) BswM_ConfigPtr;
#endif

#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define BSWM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"

#if(BSWM_MULTIPARTITION == STD_ON)
/***********************************************************************************************************************
 *  BswM_CreatePartitionLookUpTable()
 **********************************************************************************************************************/
/*! \brief      Creates the lookup table of external OsApplications to the internal BswM index
 * \details     -
 * \pre         -
 * \context     TASK
 * \reentrant   TRUE
 * \synchronous TRUE
 * \note        Called by BswM_PreInit function
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_CreatePartitionLookUpTable(void);
#endif

#if(BSWM_IMMEDIATEUSER == STD_ON)
/***********************************************************************************************************************
 *  BswM_ProcessQueuedRequests()
 **********************************************************************************************************************/
/*! \brief      Called by mode request functions in order to process other pending immediate requests.
 * \details     Arbitrate rules and execute action lists of queued immediate requests.
 * \pre         Global queue semaphore is locked.
 * \param[in]   partitionIdx: Index of current partition Context
 * \context     TASK|ISR1|ISR2
 * \reentrant   FALSE
 * \synchronous TRUE
 * \note        Called by BswM mode request functions.
 */
BSWM_LOCAL FUNC(void, BSWM_CODE) BswM_ProcessQueuedRequests(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);

/***********************************************************************************************************************
 *  BswM_ReleaseQueue()
 **********************************************************************************************************************/
/*! \brief      Releases processed requests from the queue.
 * \details     Iterates over the queue and set processed requests to idle and pending requests to queued.
 * \pre         -
 * \param[in]   partitionIdx: Index of current partition Context
 * \context     TASK|ISR1|ISR2
 * \reentrant   FALSE
 * \synchronous TRUE
 * \note        Only called by BswM_ProcessQueuedRequests.
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_ReleaseQueue(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
#endif

#if (BSWM_ACTIONLISTPRIORITYQUEUE == STD_ON)
/**********************************************************************************************************************
 *  BswM_PushIntoActionListQueue()
 **********************************************************************************************************************/
/*! \brief      Insert new action list to be executed into the Action List queue.
 * \details     Inserts action list index into the priority queue.
 * \param[in]   actionListIndex The index of the Action List to execute
 * \param[in]   partitionIdx: Index of current partition Context
 * \pre         actionListIndex is not already queued and BSWM_EXCLUSIVE_AREA_0 must be entered.
 * \context     TASK|ISR1|ISR2
 * \reentrant   FALSE
 * \synchronous TRUE
 * \trace       DSGN-BswM24022
 * \note        Called by BswM_ProcessQueuedRequests, BswM_ExecuteDeferredRules, BswM_ExecuteForcedImmediateUser
 */
BSWM_LOCAL FUNC(void, BSWM_CODE) BswM_PushIntoActionListQueue(BswM_SizeOfActionListQueueType actionListIndex, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);

/**********************************************************************************************************************
 *  BswM_PopFromActionListQueue()
 **********************************************************************************************************************/
/*! \brief      Gets the next minimum action list index from the action list queue with the given executionLevel
 * \details     Determines the minimum action list index from the priority queue with the given executionLevel and deletes
 *              the element from the priority queue.
 *              If no element can be found, BswM_GetSizeOfActionListQueue() is returned.
 * \param[in]   executionLevel The executionLevel of the current action list execution context
 * \param[in]   partitionIdx Index of current partition Context
 * \return      The action list index or BswM_GetSizeOfActionListQueue() if not found
 * \pre         BSWM_EXCLUSIVE_AREA_0 must be entered.
 * \context     TASK|ISR1|ISR2
 * \reentrant   FALSE
 * \synchronous TRUE
 * \trace       DSGN-BswM24022
 * \note        Called by BswM_ProcessQueuedRequests, BswM_ExecuteDeferredRules, BswM_ExecuteForcedImmediateUser
 */
BSWM_LOCAL FUNC(BswM_SizeOfActionListQueueType, BSWM_CODE) BswM_PopFromActionListQueue(uint8 executionLevel, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);

/**********************************************************************************************************************
 *  BswM_DetermineMinimalQueueIdx()
 **********************************************************************************************************************/
/*! \brief      Gets the next minimum action list queue index with the given executionLevel.
 * \details     If no element can be found, BswM_GetSizeOfActionListPriorityQueue() is returned.
 * \param[in]   executionLevel The executionLevel of the current action list execution context.
 * \param[in]   partitionIdx Index of current partition Context
 * \return      The action list index or BswM_GetSizeOfActionListQueue() if not found
 * \pre         BSWM_EXCLUSIVE_AREA_0 must be entered.
 * \context     TASK|ISR1|ISR2
 * \reentrant   FALSE
 * \synchronous TRUE
 * \trace       DSGN-BswM24022
 * \note        Called by BswM_PopFromActionListQueue
 */
BSWM_LOCAL_INLINE FUNC(BswM_SizeOfActionListPriorityQueueType, BSWM_CODE) BswM_DetermineMinimalQueueIdx(uint8 executionLevel, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);

/**********************************************************************************************************************
 *  BswM_RemoveIdxFromQueue()
 **********************************************************************************************************************/
/*! \brief      Removes the given index from the priority queue.
 * \details     The index with the given id is removed from the priority queue and the property of the minimal heap
                is restored.
 * \param[in]   executionLevel The executionLevel of the current action list execution context.
 * \param[in]   partitionIdx Index of current partition Context
 * \pre         BSWM_EXCLUSIVE_AREA_0 must be entered.
 * \context     TASK|ISR1|ISR2
 * \reentrant   FALSE
 * \synchronous TRUE
 * \trace       DSGN-BswM24022
 * \note        Called by BswM_PopFromActionListQueue
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_RemoveIdxFromQueue(BswM_SizeOfActionListPriorityQueueType index, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
#endif

#if (BSWM_TIMERSTATE == STD_ON)
/***********************************************************************************************************************
 *  BswM_DecreaseTimer()
 **********************************************************************************************************************/
/*! \brief      Decreases the running timer of BswM.
 * \details     Iterates over all timers and decrease running ones. If a timer reaches zero, state of the timer is set
 *              to expired.
 * \param[in]   partitionIdx Index of current partition Context
 * \pre         Interrupts must be blocked.
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 * \note        May only be called by BswM_MainFunction.
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_DecreaseTimer(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
#endif

#if (BSWM_ACTIONLISTS == STD_ON)
/**********************************************************************************************************************
 *  BswM_ExecuteActionLists()
 **********************************************************************************************************************/
/*! \brief      Executes queued action lists.
 * \details     Iterates over all action lists and executes the action if it is queued with the given executionLevel.
 * \param[in]   executionLevel         executionLevel of action list which shall be executed.
 * \param[in]   partitionIdx Index of current partition Context
 * \pre         BSWM_EXCLUSIVE_AREA_0 must be entered.
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_ExecuteActionLists(uint8 executionLevel, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
#endif

#if (BSWM_DEFERREDRULES == STD_ON)
/**********************************************************************************************************************
 *  BswM_ExecuteDeferredRules()
 **********************************************************************************************************************/
/*! \brief      Executes deferred rules.
 * \details     Arbitrates all deferred rules and executes the corresponding action lists.
 * \param[in]   partitionIdx Index of current partition Context
 * \pre         BSWM_EXCLUSIVE_AREA_0 must be entered.
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_ExecuteDeferredRules(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
#endif

#if (BSWM_FORCEDOFIMMEDIATEUSER == STD_ON)
/**********************************************************************************************************************
 *  BswM_ExecuteForcedImmediateUser()
 **********************************************************************************************************************/
/*! \brief      Executes a forced immediate user.
 * \details     Arbitrates corresponding rules of a forced immediate user and executes the corresponding action lists.
 * \param[in]   immediateUserIndex   Index of an immediate user.
 * \param[in]   partitionIdx Index of current partition Context
 * \pre         BSWM_EXCLUSIVE_AREA_0 must be entered.
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 * \note        Only called by BswM_ImmediateModeRequest.
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_ExecuteForcedImmediateUser(BswM_SizeOfImmediateUserType immediateUserIndex, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
#endif

/*********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
# if(BSWM_MULTIPARTITION == STD_ON)
/**********************************************************************************************************************
 *  BswM_CreatePartitionLookUpTable()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_CreatePartitionLookUpTable(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  BswM_PartitionIdentifiersIterType partitionIdIterator;
  uint16 arrayIndexCount;

  /* ----- Implementation ----------------------------------------------- */
  
  /* #10 Iterate over all entries in the OsApplication LookUp Table
   *      Initialize the variable with 0xFF
   *      Iterate over all entries of the partition identifiers
   *       Enter the internal BswM index at the correct OsApplication index
   */
  for (arrayIndexCount = 0u; arrayIndexCount < BswM_GetSizeOfOsApplicationToBswM(); arrayIndexCount++) /* COV_BSWM_PART_ARRAY TX */
  {
    BswM_SetOsApplicationToBswM(0xFFu, arrayIndexCount); /* SBSW_BSWM_OSAPPLICATIONTOBSWM */

    for (partitionIdIterator = 0u; partitionIdIterator < BswM_GetSizeOfPartitionIdentifiers(); partitionIdIterator++)
    {
      if ( (uint16)BswM_GetPartitionSNVOfPartitionIdentifiers(partitionIdIterator) == arrayIndexCount )
      {
        BswM_SetOsApplicationToBswM(BswM_GetPCPartitionConfigIdxOfPartitionIdentifiers(partitionIdIterator), arrayIndexCount); /* SBSW_BSWM_OSAPPLICATIONTOBSWM */
        break;
      }
    }
  }
}

/**********************************************************************************************************************
 *  BswM_GetInternalPartitionIdx()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType, BSWM_CODE) BswM_GetInternalPartitionIdx(ApplicationType osApplication)
{
  /* ----- Local Variables ---------------------------------------------- */
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType retVal = 0xFFu;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if passed osApplication is in range
   *      Return internal index
   *      Return 0xFF if osApplication is not in range
   */
  if ((uint16)osApplication < BswM_GetSizeOfOsApplicationToBswM())
  {
    retVal = BswM_GetOsApplicationToBswM(osApplication);
  }

  return retVal;
}
#else
# define BswM_GetInternalPartitionIdx(index) 0u
#endif

#if((BSWM_RULES == STD_ON) && (BSWM_FUNCTION_BASED == STD_OFF))
/**********************************************************************************************************************
 *  BswM_ArbitrateRule()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(BswM_SizeOfActionListsType, BSWM_CODE) BswM_ArbitrateRule(BswM_HandleType ruleId, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 state;
  BswM_SizeOfActionListsType actionList = BSWM_NO_ACTIONLIST(partitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  if ((ruleId < BswM_GetSizeOfRuleStates(partitionIdx))
# if ( BSWM_ENABLE_RULE_CONTROL == STD_ON )
      && (BswM_GetRuleStates(ruleId, partitionIdx) != BSWM_DEACTIVATED)
# endif
      )
  {
    if (BswM_GetExpressions(BswM_GetExpressionsIdxOfRules(ruleId, partitionIdx), partitionIdx)(partitionIdx) != 0u) /* SBSW_BSWM_EXPRESSIONFCTPTR */
    {
# if ( BSWM_ACTIONLISTSTRUEIDXOFRULES == STD_ON )
      actionList = BswM_GetActionListsTrueIdxOfRules(ruleId, partitionIdx);
# endif
      state = BSWM_TRUE;
    }
    else
    {
# if ( BSWM_ACTIONLISTSFALSEIDXOFRULES == STD_ON )
      actionList = BswM_GetActionListsFalseIdxOfRules(ruleId, partitionIdx);
# endif
      state = BSWM_FALSE;
    }

# if (BSWM_CONDITIONALOFACTIONLISTS == STD_OFF || (BSWM_CONDITIONALOFACTIONLISTS == STD_ON && BSWM_ISDEF_CONDITIONALOFACTIONLISTS == STD_OFF))
    if ((actionList != BSWM_NO_ACTIONLIST(partitionIdx)) && (BswM_GetRuleStates(ruleId, partitionIdx) == state)
#  if (BSWM_CONDITIONALOFACTIONLISTS == STD_ON )
    && (!BswM_IsConditionalOfActionLists(actionList, partitionIdx))
#  endif
    )
    {
      /* Action list shall only be executed on trigger but result of expression has not changed */
      actionList = BSWM_NO_ACTIONLIST(partitionIdx);
    }
# endif
    BswM_SetRuleStates(ruleId, state, partitionIdx); /* SBSW_BSWM_SETRULESTATE */
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  return actionList;
}
#endif

#if (BSWM_IMMEDIATEUSER == STD_ON)

/**********************************************************************************************************************
 *  BswM_ReleaseQueue()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_ReleaseQueue(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  BswM_ModeRequestQueueIterType queueIndex;

  /* ----- Implementation ----------------------------------------------- */
  BswM_EnterCriticalArea_0();
  for(queueIndex = 0u; queueIndex < BswM_GetSizeOfModeRequestQueue(partitionIdx); queueIndex++)
  {
    if(BSWM_REQUEST_PROCESSED == BswM_GetModeRequestQueue(queueIndex, partitionIdx))
    {
      BswM_SetModeRequestQueue(queueIndex, BSWM_REQUEST_IDLE, partitionIdx); /* SBSW_BSWM_SETMODEREQUESTQUEUE */
    }
    else if(BSWM_REQUEST_PENDING == BswM_GetModeRequestQueue(queueIndex, partitionIdx)) /* COV_BSWM_MODEREQUESTPENDING */
    {
      BswM_SetQueueWritten(TRUE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
      BswM_SetModeRequestQueue(queueIndex, BSWM_REQUEST_QUEUED, partitionIdx); /* SBSW_BSWM_SETMODEREQUESTQUEUE */
    }
    else
    {
      /* nothing to do */
    }
  }
  BswM_LeaveCriticalArea_0();
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}

/**********************************************************************************************************************
 *  BswM_ProcessQueuedRequests()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
BSWM_LOCAL FUNC(void, BSWM_CODE) BswM_ProcessQueuedRequests(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  BswM_ModeRequestQueueIterType immediateUserIndex;
  BswM_RulesIndIterType ruleIndex;
  BswM_SizeOfActionListsType actionListIndex;
  boolean executeActionLists = TRUE;
  uint8 queueState = BSWM_REQUEST_IDLE;

  /* ----- Implementation ----------------------------------------------- */

  BswM_EnterCriticalArea_0();
  while((executeActionLists == TRUE) && (BswM_IsQueueWritten(partitionIdx)))
  {
    BswM_SetQueueWritten(FALSE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    executeActionLists = FALSE;
    for(immediateUserIndex = 0u; immediateUserIndex < BswM_GetSizeOfModeRequestQueue(partitionIdx); immediateUserIndex++)
    {
      if(BSWM_REQUEST_QUEUED == BswM_GetModeRequestQueue(immediateUserIndex, partitionIdx))
      { 
        for(ruleIndex = BswM_GetRulesIndStartIdxOfImmediateUser(immediateUserIndex, partitionIdx); ruleIndex < BswM_GetRulesIndEndIdxOfImmediateUser(immediateUserIndex, partitionIdx); ruleIndex++)
        {
          {
# if (BSWM_FUNCTION_BASED == STD_ON)
            actionListIndex = BswM_GetFctPtrOfRules(BswM_GetRulesInd(ruleIndex, partitionIdx), partitionIdx)(partitionIdx); /* SBSW_BSWM_RULEFCTPTR */
# else
            actionListIndex = BswM_ArbitrateRule((BswM_HandleType)BswM_GetRulesInd(ruleIndex, partitionIdx), partitionIdx);
# endif
            if((actionListIndex < BswM_GetSizeOfActionListQueue(partitionIdx)) && (BswM_GetActionListQueue(actionListIndex, partitionIdx) == BSWM_ACTIONLIST_IDLE)) /* COV_BSWM_ACTIONLISTIDLE */
            {
              queueState = BSWM_REQUEST_PROCESSED;
              BswM_SetActionListQueue(actionListIndex, BSWM_ACTIONLIST_PENDING, partitionIdx); /* SBSW_BSWM_SETACTIONLISTQUEUE */
# if (BSWM_ACTIONLISTPRIORITYQUEUE == STD_ON)
              BswM_PushIntoActionListQueue(actionListIndex, partitionIdx);
# endif
            }
          }
        }
        if(queueState == BSWM_REQUEST_PROCESSED)
        {
          BswM_SetModeRequestQueue(immediateUserIndex, BSWM_REQUEST_PROCESSED, partitionIdx); /* SBSW_BSWM_SETMODEREQUESTQUEUE */
          queueState = BSWM_REQUEST_QUEUE_RELEASE;
          executeActionLists = TRUE;
        } else
        {
          BswM_SetModeRequestQueue(immediateUserIndex, BSWM_REQUEST_IDLE, partitionIdx); /* SBSW_BSWM_SETMODEREQUESTQUEUE */
        }
      }
    }
    if(executeActionLists == TRUE)
    {
      /* BSWM_EXCLUSIVE_AREA_0 must be entered before calling BswM_ExecuteActionLists.
       * Area is left and reentered during execution so blocked time should be acceptable. */
      BswM_ExecuteActionLists(BSWM_ACTIONLIST_PENDING, partitionIdx);
    }
  }
  BswM_LeaveCriticalArea_0();

  if(queueState == BSWM_REQUEST_QUEUE_RELEASE)
  {
    BswM_ReleaseQueue(partitionIdx);
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  BswM_ImmediateModeRequest()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
FUNC(void, BSWM_CODE) BswM_ImmediateModeRequest(BswM_SizeOfImmediateUserType start, BswM_SizeOfImmediateUserType end, uint8 sid, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
# else
FUNC(void, BSWM_CODE) BswM_ImmediateModeRequest(BswM_SizeOfImmediateUserType start, BswM_SizeOfImmediateUserType end, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
# endif
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 localSemaphore;
  BswM_SizeOfImmediateUserType immediateUserIndex;

  /* ----- Implementation ----------------------------------------------- */
  if((end <= BswM_GetSizeOfImmediateUser(partitionIdx))
# if ( BSWM_DEV_ERROR_DETECT == STD_OFF )
      /* #30 Verify that BswM is initialized - (This prevents queuing of new mode request if BswM_DeInit was called). (\trace SPEC-7833) */
      && BswM_IsInitialized(partitionIdx)
# endif
      )
  {
    BswM_EnterCriticalArea_0();

    localSemaphore = BswM_GetQueueSemaphore(partitionIdx);
    if (BswM_GetQueueSemaphore(partitionIdx) == BSWM_REQUEST_SEMAPHORE_UNLOCKED)
    {
      BswM_SetQueueSemaphore(BSWM_REQUEST_SEMAPHORE_LOCKED, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    }

    for (immediateUserIndex = start; immediateUserIndex < end; immediateUserIndex++)
    {
# if ( BSWM_FORCEDOFIMMEDIATEUSER == STD_ON )
      if (BswM_IsForcedOfImmediateUser(immediateUserIndex, partitionIdx))
      {
        BswM_ExecuteForcedImmediateUser(immediateUserIndex, partitionIdx);
      }
      else
# endif /* ( BSWM_FORCEDOFIMMEDIATEUSER == STD_ON )*/
      {
        if (BswM_GetModeRequestQueue(immediateUserIndex, partitionIdx) == BSWM_REQUEST_IDLE)
        {
          BswM_SetQueueWritten(TRUE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
          BswM_SetModeRequestQueue(immediateUserIndex, BSWM_REQUEST_QUEUED, partitionIdx); /* SBSW_BSWM_IMMEDIATEMODEREQUEST */
        }
        else if(BswM_GetModeRequestQueue(immediateUserIndex, partitionIdx) == BSWM_REQUEST_PROCESSED) /* COV_BSWM_MODEREQUESTPENDING */
        {
          BswM_SetModeRequestQueue(immediateUserIndex, BSWM_REQUEST_PENDING, partitionIdx); /* SBSW_BSWM_IMMEDIATEMODEREQUEST */
        }
        else
        {
          /* Mode is already queued. That means that there is a former mode change on this mode port which has not been processed yet. */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
          BswM_LeaveCriticalArea_0();
          (void)Det_ReportError(BSWM_MODULE_ID, 0, sid, BSWM_E_ALREADY_QUEUED);
          BswM_EnterCriticalArea_0();
# endif
        }
      }
    }
    BswM_LeaveCriticalArea_0();

    if (BSWM_REQUEST_SEMAPHORE_UNLOCKED == localSemaphore)
    {
      /* Immediately process other pending immediate requests. */
      BswM_ProcessQueuedRequests(partitionIdx);
      /* Unlock semaphore after processing of the queue. */
      BswM_SetQueueSemaphore(BSWM_REQUEST_SEMAPHORE_UNLOCKED, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
# if(BSWM_IPDU_GROUP_CONTROL == STD_ON)
      BswM_ExecuteIpduGroupControl();
# endif
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ACTIONLISTPRIORITYQUEUE == STD_ON)
/**********************************************************************************************************************
 *  BswM_PushIntoActionListQueue()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
BSWM_LOCAL FUNC(void, BSWM_CODE) BswM_PushIntoActionListQueue(BswM_SizeOfActionListQueueType actionListIndex, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
  /* Insert the new child element to the bottom level of the heap (last element of the array) */
  BswM_ActionListQueueIterType child = BswM_GetLengthOfActionListPriorityQueue(partitionIdx);
  /* Determine the parents array index */
  BswM_ActionListQueueIterType parent = (BswM_ActionListQueueIterType)((child - 1u) >> 1u);

# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check that the priority queue is not full. */
  if (child >= BswM_GetSizeOfActionListPriorityQueue(partitionIdx))
  {
    errorId = BSWM_E_ACTION_LIST_QUEUE_ERROR;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Locate parent of the new child element and check if priority of the parent is smaller, if not 
     *     swap the child node and the parent until the parent has the lower priority (Min-Heap property).
     */
    
    /*                        +--------+
     *                        | PARENT |
     *                        +--------+
     *                      /            \
     *            +--------+              +--------+
     *            | CHILD1 |              | CHILD2 |
     *            +--------+              +--------+
     */
    while ((child > 0u) && (BswM_GetActionListPriorityQueue(parent, partitionIdx) > actionListIndex))
    {
      /* Min-Heap property violated -> Swap child and parent */
      BswM_SetActionListPriorityQueue(child, BswM_GetActionListPriorityQueue(parent, partitionIdx), partitionIdx); /* SBSW_BSWM_PUSHINTOACTIONLISTPRIORITYQUEUE */
      child = parent;
      parent = (BswM_ActionListQueueIterType)((parent - 1u) >> 1u);
    }

    /* #30 Store the inserted actionListIndex at the correct position in the heap */
    BswM_SetActionListPriorityQueue(child, actionListIndex, partitionIdx); /* SBSW_BSWM_PUSHINTOACTIONLISTPRIORITYQUEUE */

    /* #40 Increment size of Action List Queue Indexes */
    BswM_IncLengthOfActionListPriorityQueue(partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_PUSH_INTO_ACTION_LIST_QUEUE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}

/**********************************************************************************************************************
 *  BswM_PopFromActionListQueue()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
BSWM_LOCAL FUNC(BswM_SizeOfActionListQueueType, BSWM_CODE) BswM_PopFromActionListQueue(uint8 executionLevel, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  BswM_SizeOfActionListPriorityQueueType priorityQueueIdx;
  BswM_SizeOfActionListQueueType minActionListIdx = BswM_GetSizeOfActionListQueue(partitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Determine if the Action List Queue contains any element. If not, return the size of the Action List Queue */
  if (BswM_GetLengthOfActionListPriorityQueue(partitionIdx) > 0u)
  {
    /* #20 If there are elements in the queue, determine the minimum Action List Queue item that matches the provided executionLevel */

    /* In case of executionLevel BSWM_ACTIONLIST_PENDING the element on position 0 of the queue has the minimal action list index */
    if (executionLevel == BSWM_ACTIONLIST_PENDING)
    {
      priorityQueueIdx = 0u;
    }
    else
    {
      priorityQueueIdx = BswM_DetermineMinimalQueueIdx(executionLevel, partitionIdx);
    }

    /* #30 If there was no minimum Action List Queue item for the given executionLevel, return the size of Action List Queue */
    if (priorityQueueIdx < BswM_GetSizeOfActionListPriorityQueue(partitionIdx)) /*lint -e{661, 662} */
    {
      /* #40 Otherwise, return the found Action List Queue item and remove it from the queue */
      minActionListIdx = (BswM_SizeOfActionListQueueType)BswM_GetActionListPriorityQueue(priorityQueueIdx, partitionIdx);

      BswM_RemoveIdxFromQueue(priorityQueueIdx, partitionIdx); /*lint -e{661, 662} */
    }
  }

  return minActionListIdx;
}

/**********************************************************************************************************************
 *  BswM_DetermineMinimalQueueIdx
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
BSWM_LOCAL_INLINE FUNC(BswM_SizeOfActionListPriorityQueueType, BSWM_CODE) BswM_DetermineMinimalQueueIdx(uint8 executionLevel, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  BswM_SizeOfActionListPriorityQueueType tempPriorityQueueIdx, priorityQueueIdx, lastIdxInLevel;
  BswM_SizeOfActionListQueueType minActionListIdx = BswM_GetSizeOfActionListQueue(partitionIdx);
  BswM_SizeOfActionListQueueType minActionListIdxInLevel = BswM_GetSizeOfActionListQueue(partitionIdx);

  /* ----- Implementation ----------------------------------------------- */
  lastIdxInLevel = 0u;
  priorityQueueIdx = BswM_GetSizeOfActionListPriorityQueue(partitionIdx);

  for( tempPriorityQueueIdx = 0u; tempPriorityQueueIdx < BswM_GetLengthOfActionListPriorityQueue(partitionIdx); tempPriorityQueueIdx++ )
  {
    BswM_SizeOfActionListQueueType currentActionListIndex = BswM_GetActionListPriorityQueue(tempPriorityQueueIdx, partitionIdx);
      /* #10 Iterate over the ActionListPriorityQueue elements of the same level (all children) and search for 
             an action with the minimal action list index and the passed executionLevel. */
    if ( (currentActionListIndex < minActionListIdx) &&
          (BswM_GetActionListQueue(currentActionListIndex, partitionIdx) == executionLevel))
    {
      priorityQueueIdx = tempPriorityQueueIdx;
      minActionListIdx = currentActionListIndex;
    }
    else if(currentActionListIndex < minActionListIdxInLevel)
    {
      minActionListIdxInLevel = currentActionListIndex;
    }
    else
    {
      /* Element has not the smallest index on level. */
    }

    /* #20 In case that an element was found on a level and this element has the minimal index on this level, 
           the search is over. Other elements on deeper levels can not have a smaller index because of the min heap 
           property that parents have always the higher priority compared to the children. */
    if( tempPriorityQueueIdx == lastIdxInLevel )
    {
      if(minActionListIdx < minActionListIdxInLevel)
      {
        break;
      }
      /* #30 Otherwise the search has to be continued on a deeper level. */
      minActionListIdxInLevel = BswM_GetSizeOfActionListQueue(partitionIdx);
      lastIdxInLevel = (BswM_SizeOfActionListPriorityQueueType)((lastIdxInLevel << 1) + 2u);
    }
  }

  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return priorityQueueIdx;
}


/**********************************************************************************************************************
 *  BswM_RemoveIdxFromQueue
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_RemoveIdxFromQueue(BswM_SizeOfActionListPriorityQueueType index, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
    /* ----- Local Variables ---------------------------------------------- */
  BswM_SizeOfActionListPriorityQueueType priorityQueueIdx = index; /*lint -e{661, 662} */

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Set the last element of the priority queue to the position of the found index and reduce the list length. */
  BswM_DecLengthOfActionListPriorityQueue(partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */

  BswM_SetActionListPriorityQueue(priorityQueueIdx, BswM_GetActionListPriorityQueue(BswM_GetLengthOfActionListPriorityQueue(partitionIdx), partitionIdx), partitionIdx); /* SBSW_BSWM_POPFROMACTIONLISTPRIORITYQUEUE */

  /* #20 If one of the children of the element on the new position has a smaller index compared to the parent, the
         children with the smallest index has to be swaped with the parent to restore the heap property. This has to be 
         repeated as long as the heap property is not fulfilled. */
  while (1) /* COV_BSWM_WHILE_1 TX */
  {
    BswM_SizeOfActionListPriorityQueueType temp, leftChild;
    leftChild = (BswM_SizeOfActionListPriorityQueueType)((priorityQueueIdx << 1u) + 1u); /*lint -e{661, 662} */

    /* Check if the right child (leftChild + 1) has minimum priority */
    if ((((BswM_ActionListQueueIterType)leftChild + 1u) < BswM_GetLengthOfActionListPriorityQueue(partitionIdx)) && 
        (BswM_GetActionListPriorityQueue((leftChild + 1u), partitionIdx) < BswM_GetActionListPriorityQueue(priorityQueueIdx, partitionIdx)) && /*lint -e{661, 662} */
        (BswM_GetActionListPriorityQueue((leftChild + 1u), partitionIdx) < BswM_GetActionListPriorityQueue(leftChild, partitionIdx)) ) /*lint -e{661, 662} */
    {
      leftChild++; /*lint -e{661, 662} */ /* Minimum is right child */
    }
    /* Check if the left child has minimum priority */
    else if ((leftChild < BswM_GetLengthOfActionListPriorityQueue(partitionIdx)) &&
        (BswM_GetActionListPriorityQueue(leftChild, partitionIdx) < BswM_GetActionListPriorityQueue(priorityQueueIdx, partitionIdx))) /*lint -e{661, 662} */
    {
      /* Minimum is left child (index already set) */
    }
    /* break if the children have the minimum priority or the end of the list is reached */
    else
    {
      break; /* Minimum is parent */
    }

    /* Swap parent with minimum child */
    temp = BswM_GetActionListPriorityQueue(leftChild, partitionIdx); /*lint -e{661, 662} */
    BswM_SetActionListPriorityQueue(leftChild, BswM_GetActionListPriorityQueue(priorityQueueIdx, partitionIdx), partitionIdx); /*lint -e{661, 662} */ /* SBSW_BSWM_POPFROMACTIONLISTPRIORITYQUEUE */
    BswM_SetActionListPriorityQueue(priorityQueueIdx, temp, partitionIdx); /* SBSW_BSWM_POPFROMACTIONLISTPRIORITYQUEUE */

    /* Child becomes parent */
    priorityQueueIdx = leftChild; /*lint -e{661, 662} */
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
#endif


#if ((BSWM_FUNCTION_BASED == STD_OFF) && (BSWM_ACTIONLISTS == STD_ON))
/**********************************************************************************************************************
 *  BswM_Action_ActionListHandler()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, BSWM_CODE) BswM_Action_ActionListHandler(BswM_HandleType handleId, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  BswM_ActionItemsIterType itemId;
  BswM_HandleType parameterIdx;

  /* ----- Implementation ----------------------------------------------- */
  for(itemId = BswM_GetActionItemsStartIdxOfActionLists(handleId, partitionIdx); itemId < BswM_GetActionItemsEndIdxOfActionLists(handleId, partitionIdx); itemId++)
  {
# if (BSWM_PARAMETERIDXOFACTIONITEMS == STD_ON)
    parameterIdx = BswM_GetParameterIdxOfActionItems(itemId, partitionIdx);
# else
    parameterIdx = 0u;
# endif


# if (BSWM_ABORTOFACTIONITEMS == STD_ON || BSWM_REPORTOFACTIONITEMS == STD_ON)
    if(BswM_GetActions(BswM_GetActionsIdxOfActionItems(itemId, partitionIdx), partitionIdx)(parameterIdx, partitionIdx) != E_OK) /* SBSW_BSWM_ACTIONFCTPTR */
    {
#  if (BSWM_REPORTOFACTIONITEMS == STD_ON)
      if(BswM_GetReportOfActionItems(itemId, partitionIdx) != 0u)
      {
        Dem_ReportErrorStatus(BswM_GetReportOfActionItems(itemId, partitionIdx), DEM_EVENT_STATUS_FAILED);
      }
#  endif
#  if (BSWM_ABORTOFACTIONITEMS == STD_ON)
      if(BswM_IsAbortOfActionItems(itemId, partitionIdx))
      {
        retVal = E_NOT_OK;
        break;
      }
#  endif
    }
# else
    (void)BswM_GetActions(BswM_GetActionsIdxOfActionItems(itemId, partitionIdx), partitionIdx)(parameterIdx, partitionIdx); /* SBSW_BSWM_ACTIONFCTPTR */
# endif
  }

  return retVal;
}
#endif

#if (BSWM_TIMERSTATE == STD_ON)
/**********************************************************************************************************************
 *  BswM_DecreaseTimer()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_DecreaseTimer(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  BswM_TimerStateIterType timerIndex;

  /* ----- Implementation ----------------------------------------------- */
  for(timerIndex = 0u; timerIndex < BswM_GetSizeOfTimerValue(partitionIdx); timerIndex++)
  {
    if(BswM_GetTimerValue(timerIndex, partitionIdx) > 0u)
    {
      BswM_DecTimerValue(timerIndex, partitionIdx); /* SBSW_BSWM_SETTIMER */
      if(BswM_GetTimerValue(timerIndex, partitionIdx) == 0u)
      {
        BswM_SetTimerState(timerIndex, BSWM_TIMER_EXPIRED, partitionIdx); /* SBSW_BSWM_SETTIMER */
      }
    }
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
#endif /* BSWM_TIMERSTATE == STD_ON */

#if (BSWM_ACTIONLISTS == STD_ON)
/**********************************************************************************************************************
 *  BswM_ExecuteActionLists()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_ExecuteActionLists(uint8 executionLevel, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  BswM_SizeOfActionListQueueType actionListIndex;

  /* ----- Implementation ----------------------------------------------- */
# if (BSWM_ACTIONLISTPRIORITYQUEUE == STD_ON)
  for (actionListIndex = BswM_PopFromActionListQueue(executionLevel, partitionIdx);
       actionListIndex < BswM_GetSizeOfActionListQueue(partitionIdx);
       actionListIndex = BswM_PopFromActionListQueue(executionLevel, partitionIdx))
# else
  for (actionListIndex = 0u; actionListIndex < BswM_GetSizeOfActionListQueue(partitionIdx); actionListIndex++)
# endif
  {
# if (BSWM_ACTIONLISTPRIORITYQUEUE == STD_OFF)
    if (BswM_GetActionListQueue(actionListIndex, partitionIdx) == executionLevel)
# endif
    {
      BswM_SetActionListQueue(actionListIndex, BSWM_ACTIONLIST_BLOCKED, partitionIdx); /* SBSW_BSWM_SETACTIONLISTQUEUE */
      BswM_LeaveCriticalArea_0();
# if (BSWM_FUNCTION_BASED == STD_ON)
      (void)BswM_GetFctPtrOfActionLists(actionListIndex, partitionIdx)(partitionIdx); /* SBSW_BSWM_ACTIONLISTFCTPTR */
# else
      (void)BswM_Action_ActionListHandler((BswM_HandleType)actionListIndex, partitionIdx);
# endif
      BswM_EnterCriticalArea_0();
      BswM_SetActionListQueue(actionListIndex, BSWM_ACTIONLIST_IDLE, partitionIdx); /* SBSW_BSWM_SETACTIONLISTQUEUE */
    }
  }
}
#endif

#if (BSWM_DEFERREDRULES == STD_ON)
/**********************************************************************************************************************
 *  BswM_ExecuteDeferredRules()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_ExecuteDeferredRules(BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  BswM_DeferredRulesIterType ruleIndex;
  BswM_SizeOfActionListsType actionListIndex;
  boolean executeActionLists = FALSE;
  
  /* ----- Implementation ----------------------------------------------- */
  for (ruleIndex = 0u; ruleIndex < BswM_GetSizeOfDeferredRules(partitionIdx); ruleIndex++)
  {
# if (BSWM_FUNCTION_BASED == STD_ON)
    actionListIndex = BswM_GetFctPtrOfRules(BswM_GetRulesIdxOfDeferredRules(ruleIndex, partitionIdx), partitionIdx)(partitionIdx); /* SBSW_BSWM_RULEFCTPTR */
# else
    actionListIndex = BswM_ArbitrateRule((BswM_HandleType)BswM_GetRulesIdxOfDeferredRules(ruleIndex, partitionIdx), partitionIdx);
# endif
    if ((actionListIndex < BswM_GetSizeOfActionListQueue(partitionIdx)) && (BswM_GetActionListQueue(actionListIndex, partitionIdx) == BSWM_ACTIONLIST_IDLE)) /* COV_BSWM_ACTIONLISTIDLE */
    {
      executeActionLists = TRUE;
      BswM_SetActionListQueue(actionListIndex, BSWM_ACTIONLIST_PENDING, partitionIdx); /* SBSW_BSWM_SETACTIONLISTQUEUE */
#  if (BSWM_ACTIONLISTPRIORITYQUEUE == STD_ON)
      BswM_PushIntoActionListQueue(actionListIndex, partitionIdx);
#  endif
    }
  }
  if(executeActionLists == TRUE)
  {
    BswM_ExecuteActionLists(BSWM_ACTIONLIST_PENDING, partitionIdx);
  }
}
#endif

#if (BSWM_FORCEDOFIMMEDIATEUSER == STD_ON)
/**********************************************************************************************************************
 *  BswM_ExecuteForcedImmediateUser()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
BSWM_LOCAL_INLINE FUNC(void, BSWM_CODE) BswM_ExecuteForcedImmediateUser(BswM_SizeOfImmediateUserType immediateUserIndex, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  BswM_RulesIndIterType ruleIndex;
  BswM_SizeOfActionListsType actionListIndex;
  boolean executeActionLists = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  BswM_IncForcedActionListPriority(partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */

  for(ruleIndex = BswM_GetRulesIndStartIdxOfImmediateUser(immediateUserIndex, partitionIdx); ruleIndex < BswM_GetRulesIndEndIdxOfImmediateUser(immediateUserIndex, partitionIdx); ruleIndex++)
  {
    {
# if (BSWM_FUNCTION_BASED == STD_ON)
      actionListIndex = BswM_GetFctPtrOfRules(BswM_GetRulesInd(ruleIndex, partitionIdx), partitionIdx)(partitionIdx); /* SBSW_BSWM_RULEFCTPTR */
# else
      actionListIndex = BswM_ArbitrateRule((BswM_HandleType)BswM_GetRulesInd(ruleIndex, partitionIdx), partitionIdx);
# endif
      if((actionListIndex < BswM_GetSizeOfActionListQueue(partitionIdx)) && (BswM_GetActionListQueue(actionListIndex, partitionIdx) != BSWM_ACTIONLIST_BLOCKED)) /* COV_BSWM_ACTIONLISTBLOCKED */
      {
        executeActionLists = TRUE;
# if (BSWM_ACTIONLISTPRIORITYQUEUE == STD_ON)
        if (BswM_GetActionListQueue(actionListIndex, partitionIdx) == BSWM_ACTIONLIST_IDLE)
        {
          BswM_PushIntoActionListQueue(actionListIndex, partitionIdx);
        }
# endif

        BswM_SetActionListQueue(actionListIndex, BswM_GetForcedActionListPriority(partitionIdx), partitionIdx); /* SBSW_BSWM_SETACTIONLISTQUEUE */
      }
    }
  }

  if(executeActionLists == TRUE)
  {
    BswM_ExecuteActionLists(BswM_GetForcedActionListPriority(partitionIdx), partitionIdx);
  }
  BswM_DecForcedActionListPriority(partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
}
#endif

/*********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  BswM_InitMemory()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_InitMemory(void)
{
  /* #10 Set variable PreInitialized to FALSE. */
  BswM_SetPreInitialized(FALSE);
}

/**********************************************************************************************************************
 *  BswM_PreInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_PreInit(P2CONST(BswM_ConfigType, AUTOMATIC, BSWM_INIT_DATA) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionCounter;

#if (BSWM_USE_INIT_POINTER == STD_ON)
  /* #10 Set BswM_ConfigPtr */
  BswM_ConfigPtr = ConfigPtr;

  /* ----- Development Error Checks ------------------------------------- */
  /* Check if the config pointer is a null pointer. */
  if(ConfigPtr == NULL_PTR)
  {
# if (BSWM_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
    EcuM_BswErrorHook((uint16) BSWM_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
# elif (BSWM_DEV_ERROR_DETECT == STD_ON)
    errorId = BSWM_E_NULL_POINTER;
# endif
  }
# if (BSWM_FINALMAGICNUMBER == STD_ON && BSWM_USE_ECUM_BSW_ERROR_HOOK == STD_ON)
  else if(BswM_GetFinalMagicNumber() != BSWM_FINAL_MAGIC_NUMBER)
  {
    EcuM_BswErrorHook((uint16) BSWM_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
# endif
  else
#else
  BSWM_DUMMY_STATEMENT_CONST(ConfigPtr);
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 If all Det checks passed
     *      Create Internal Partition Idx Lookup Table
     *      Set all partition init flags to uninitialized
     *      Set CoreSync Value
     *      Set PreInitialized variable to TRUE
     */
#if(BSWM_MULTIPARTITION == STD_ON)
    BswM_CreatePartitionLookUpTable();
#endif

    for (partitionCounter = 0u; partitionCounter < BswM_GetSizeOfPartitionIdentifiers(); partitionCounter++)
    {
      BswM_SetInitialized(FALSE, partitionCounter); /* SBSW_BSWM_PARTITIONINDEXACCESS */
#if(BSWM_MULTIPARTITION == STD_ON)
      BswM_SetCoreSyncValue(BswM_GetSyncValue(partitionCounter), partitionCounter); /* SBSW_BSWM_PARTITIONINDEXACCESS */
#endif
    }
  }
  
  BswM_SetPreInitialized(TRUE);

  /* ----- Development Error Report --------------------------------------- */
#if (BSWM_DEV_ERROR_REPORT == STD_ON) && (BSWM_USE_INIT_POINTER == STD_ON) && (BSWM_USE_ECUM_BSW_ERROR_HOOK == STD_OFF)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_PREINIT_ID, errorId);
  }
#else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}

/**********************************************************************************************************************
 *  BswM_Init()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_Init(P2CONST(BswM_ConfigType, AUTOMATIC, BSWM_INIT_DATA) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
#if ((BSWM_ACTIONLISTQUEUE == STD_ON) || (BSWM_RULES == STD_ON) || (BSWM_IMMEDIATEUSER == STD_ON))
  BswM_HandleType idx;
#endif

  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetPartitionContext();

  /* ----- Development Error Checks ------------------------------------- */
#if (BSWM_DEV_ERROR_DETECT == STD_ON)
# if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
# endif
  if (BswM_IsPreInitialized() == FALSE)
  {
    errorId = BSWM_E_NO_PREINIT;
  }
  else if (BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_ALREADY_INITIALIZED;
  }
  else
#endif
    /* ----- Implementation ----------------------------------------------- */
  {
    /* #30 Initialize all static module variables. */
    
    /* Lock semaphore during initialization to queue incoming mode requests */
    BswM_SetQueueSemaphore(BSWM_REQUEST_SEMAPHORE_LOCKED, partitionIdx); /* PRQA S 2982 */ /* MD_BSWM_2982 */ /* SBSW_BSWM_PARTITIONINDEXACCESS */

#if (BSWM_IMMEDIATEUSER == STD_ON)
    BswM_SetQueueWritten(FALSE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
#endif

#if ( BSWM_FORCEDOFIMMEDIATEUSER == STD_ON )
    BswM_SetForcedActionListPriority(BSWM_ACTIONLIST_PENDING, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
#endif

#if ( BSWM_ACTIONLISTQUEUE == STD_ON )
    for (idx = 0u; idx < BswM_GetSizeOfActionListQueue(partitionIdx); idx++)
    {
      BswM_SetActionListQueue(idx, BSWM_ACTIONLIST_IDLE, partitionIdx); /* SBSW_BSWM_SETACTIONLISTQUEUE */
    }
# if (BSWM_ACTIONLISTPRIORITYQUEUE == STD_ON)
    BswM_SetLengthOfActionListPriorityQueue(0u, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
# endif
#endif

#if (BSWM_RULES == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfRules(partitionIdx); idx++)
    {
      BswM_SetRuleStates(idx, BswM_GetInitOfRules(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_SETRULESTATE */
    }
#endif

#if (BSWM_CANSMCHANNELSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfCanSMChannelState(partitionIdx); idx++)
    {
      BswM_SetCanSMChannelState(idx, BswM_GetInitValueOfCanSMChannelMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_CANSMCHANNELSTATE */
    }
#endif

#if (BSWM_COMMCHANNELSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfComMChannelState(partitionIdx); idx++)
    {
      BswM_SetComMChannelState(idx, BswM_GetInitValueOfComMChannelMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_COMMCHANNELSTATE */
    }
#endif

#if (BSWM_COMMINITIATERESETSTATE == STD_ON)
# if((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON && BSWM_USE_INIT_POINTER == STD_ON) || (BSWM_MULTIPARTITION == STD_ON))
    for (idx = 0u; idx < BswM_GetSizeOfComMInitiateResetMapping(partitionIdx); idx++) /* Size can only be 0 or 1. */
# endif
    {
      BswM_SetComMInitiateResetState(BswM_GetInitValueOfComMInitiateResetMapping(0u, partitionIdx), partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    }
#endif

#if (BSWM_COMMPNCSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfComMPncState(partitionIdx); idx++)
    {
      BswM_SetComMPncState(idx, BswM_GetInitValueOfComMPncMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_COMMPNCSTATE */
    }
#endif

#if (BSWM_DCMAPPLUPDATESTATE == STD_ON)
# if((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON && BSWM_USE_INIT_POINTER == STD_ON) || (BSWM_MULTIPARTITION == STD_ON))
    for (idx = 0u; idx < BswM_GetSizeOfDcmApplUpdateMapping(partitionIdx); idx++) /* Size can only be 0 or 1. */
# endif
    {
      BswM_SetDcmApplUpdateState(BswM_GetInitValueOfDcmApplUpdateMapping(0u, partitionIdx), partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    }
#endif

#if (BSWM_DCMCOMSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfDcmComState(partitionIdx); idx++)
    {
      BswM_SetDcmComState(idx, BswM_GetInitValueOfDcmComMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_DCMCOMSTATE */
    }
#endif

#if (BSWM_ECUMMODESTATE == STD_ON)
# if((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON && BSWM_USE_INIT_POINTER == STD_ON) || (BSWM_MULTIPARTITION == STD_ON))
    for (idx = 0u; idx < BswM_GetSizeOfEcuMModeMapping(partitionIdx); idx++) /* Size can only be 0 or 1. */
# endif
    {
      BswM_SetEcuMModeState(BswM_GetInitValueOfEcuMModeMapping(0u, partitionIdx), partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    }
#endif

#if (BSWM_ECUMRUNREQUESTSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfEcuMRunRequestState(partitionIdx); idx++)
    {
      BswM_SetEcuMRunRequestState(idx, BswM_GetInitValueOfEcuMRunRequestMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_ECUMRUNREQUESTSTATE */
    }
#endif

#if (BSWM_ECUMWAKEUPSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfEcuMWakeupState(partitionIdx); idx++)
    {
      BswM_SetEcuMWakeupState(idx, BswM_GetInitValueOfEcuMWakeupMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_ECUMWAKEUPSTATE */
    }
#endif

#if (BSWM_ETHIFPORTSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfEthIfPortState(partitionIdx); idx++)
    {
      BswM_SetEthIfPortState(idx, BswM_GetInitValueOfEthIfPortMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_ETHIFPORTSTATE */
    }
#endif

#if (BSWM_ETHSMSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfEthSMState(partitionIdx); idx++)
    {
      BswM_SetEthSMState(idx, BswM_GetInitValueOfEthSMMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_ETHSMSTATE */
    }
#endif

#if (BSWM_FRSMSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfFrSMState(partitionIdx); idx++)
    {
      BswM_SetFrSMState(idx, BswM_GetInitValueOfFrSMMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_FRSMSTATE */
    }
#endif

#if (BSWM_GENERICSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfGenericState(partitionIdx); idx++)
    {
      BswM_SetGenericState(idx, BswM_GetInitValueOfGenericMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_GENERICSTATE */
    }
#endif

#if (BSWM_J1939DCMSTATE == STD_ON)
# if((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON && BSWM_USE_INIT_POINTER == STD_ON) || (BSWM_MULTIPARTITION == STD_ON))
    for (idx = 0u; idx < BswM_GetSizeOfJ1939DcmMapping(partitionIdx); idx++) /* Size can only be 0 or 1. */
# endif
    {
      BswM_SetJ1939DcmState(BswM_GetInitValueOfJ1939DcmMapping(0, partitionIdx), partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    }
#endif

#if (BSWM_J1939NMSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfJ1939NmState(partitionIdx); idx++)
    {
      BswM_SetJ1939NmState(idx, BswM_GetInitValueOfJ1939NmMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_J1939NMSTATE */
    }
#endif

#if (BSWM_LINSCHEDULESTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfLinScheduleState(partitionIdx); idx++)
    {
      BswM_SetLinScheduleState(idx, BswM_GetInitValueOfLinScheduleMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_LINSCHEDULESTATE */
    }
#endif

#if (BSWM_LINSCHEDULEENDSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfLinScheduleEndState(partitionIdx); idx++)
    {
      BswM_SetLinScheduleEndState(idx, BswM_GetInitValueOfLinScheduleEndMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_LINSCHEDULEENDSTATE */
    }
#endif

#if (BSWM_LINSMSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfLinSMState(partitionIdx); idx++)
    {
      BswM_SetLinSMState(idx, BswM_GetInitValueOfLinSMMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_LINSMSTATE */
    }
#endif

#if (BSWM_LINTPSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfLinTPState(partitionIdx); idx++)
    {
      BswM_SetLinTPState(idx, BswM_GetInitValueOfLinTPMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_LINTPSTATE */
    }
#endif

#if (BSWM_NMSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfNmState(partitionIdx); idx++)
    {
      BswM_SetNmState(idx, BswM_GetInitValueOfNmMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_NMSTATE */
    }
#endif

#if (BSWM_NVMJOBSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfNvMJobState(partitionIdx); idx++)
    {
      BswM_SetNvMJobState(idx, BswM_GetInitValueOfNvMJobMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_NVMJOBSTATE */
    }
#endif

#if (BSWM_NVMBLOCKSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfNvMBlockState(partitionIdx); idx++)
    {
      BswM_SetNvMBlockState(idx, BswM_GetInitValueOfNvMBlockMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_NVMBLOCKSTATE */
    }
#endif

#if (BSWM_PDURRXINDICATIONSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfPduRRxIndicationState(partitionIdx); idx++)
    {
      BswM_SetPduRRxIndicationState(idx, FALSE, partitionIdx); /* SBSW_BSWM_PDURRXINDICATIONSTATE */
    }
#endif

#if (BSWM_PDURTPRXINDICATIONSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfPduRTpRxIndicationState(partitionIdx); idx++)
    {
      BswM_SetPduRTpRxIndicationState(idx, FALSE, partitionIdx); /* SBSW_BSWM_PDURTPRXINDICATIONSTATE */
    }
#endif

#if (BSWM_PDURTPSTARTOFRECEPTIONSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfPduRTpStartOfReceptionState(partitionIdx); idx++)
    {
      BswM_SetPduRTpStartOfReceptionState(idx, FALSE, partitionIdx); /* SBSW_BSWM_PDURTPSTARTOFRECEPTIONSTATE */
    }
#endif

#if (BSWM_PDURTPTXCONFIRMATIONSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfPduRTpTxConfirmationState(partitionIdx); idx++)
    {
      BswM_SetPduRTpTxConfirmationState(idx, FALSE, partitionIdx); /* SBSW_BSWM_PDURTPTXCONFIRMATIONSTATE */
    }
#endif

#if (BSWM_PDURTRANSMITSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfPduRTransmitState(partitionIdx); idx++)
    {
      BswM_SetPduRTransmitState(idx, FALSE, partitionIdx); /* SBSW_BSWM_PDURTRANSMITSTATE */
    }
#endif

#if (BSWM_PDURTXCONFIRMATIONSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfPduRTxConfirmationState(partitionIdx); idx++)
    {
      BswM_SetPduRTxConfirmationState(idx, FALSE, partitionIdx); /* SBSW_BSWM_PDURTXCONFIRMATIONSTATE */
    }
#endif

#if (BSWM_SDCLIENTSERVICESTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfSdClientServiceState(partitionIdx); idx++)
    {
      BswM_SetSdClientServiceState(idx, BswM_GetInitValueOfSdClientServiceMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_SDCLIENTSERVICESTATE */
    }
#endif

#if (BSWM_SDCONSUMEDEVENTSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfSdConsumedEventState(partitionIdx); idx++)
    {
      BswM_SetSdConsumedEventState(idx, BswM_GetInitValueOfSdConsumedEventMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_SDCONSUMEDEVENTSTATE */
    }
#endif

#if (BSWM_SDEVENTHANDLERSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfSdEventHandlerState(partitionIdx); idx++)
    {
      BswM_SetSdEventHandlerState(idx, BswM_GetInitValueOfSdEventHandlerMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_SDEVENTHANDLERSTATE */
    }
#endif

#if (BSWM_TIMERSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfTimerState(partitionIdx); idx++)
    {
      BswM_SetTimerState(idx, BSWM_TIMER_STOPPED, partitionIdx); /* SBSW_BSWM_SETTIMER */
      BswM_SetTimerValue(idx, 0u, partitionIdx); /* SBSW_BSWM_SETTIMER */
    }
#endif

#if (BSWM_WDGMSTATE == STD_ON)
    for (idx = 0u; idx < BswM_GetSizeOfWdgMState(partitionIdx); idx++)
    {
      BswM_SetWdgMState(idx, BswM_GetInitValueOfWdgMMapping(idx, partitionIdx), partitionIdx); /* SBSW_BSWM_WDGMSTATE */
    }
#endif

#if (BSWM_IMMEDIATEUSER == STD_ON)
    for(idx = 0u; idx < BswM_GetSizeOfModeRequestQueue(partitionIdx); idx++)
    {
# if (BSWM_ONINITOFIMMEDIATEUSER == STD_ON && BSWM_INITGENVARANDINITAL == STD_OFF)
      if(BswM_IsOnInitOfImmediateUser(idx, partitionIdx))
      {
        BswM_SetQueueWritten(TRUE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
        BswM_SetModeRequestQueue(idx, BSWM_REQUEST_QUEUED, partitionIdx); /* SBSW_BSWM_SETMODEREQUESTQUEUE */
      }
      else
# endif
      {
        BswM_SetModeRequestQueue(idx, BSWM_REQUEST_IDLE, partitionIdx); /* SBSW_BSWM_SETMODEREQUESTQUEUE */
      }
    }
#endif

    BswM_SetInitialized(TRUE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    
#if(BSWM_MULTIPARTITION == STD_ON)
    /* #31 In case of Multi Partition, synchronize all partitions and cores */
    BswM_GetInitSyncCallout(0u, partitionIdx)(partitionIdx, BSWM_SYNC_LEVEL_ONE); /* SBSW_BSWM_PARTITIONINDEXACCESS */
#endif

#if (BSWM_INITGENVARANDINITAL == STD_ON)
# if(BSWM_MULTIPARTITION == STD_ON)
    if (BswM_HasInitGenVarAndInitAL(partitionIdx)) /* PRQA S 2741 */ /* MD_BSWM_2741 */ /* COV_BSWM_ALL_TRUE TX */
# endif
    {
      /* #32 Initialize dynamic variables and initiating action lists. */
      (void)BswM_GetInitGenVarAndInitAL(0u, partitionIdx)(partitionIdx); /* SBSW_BSWM_ACTIONLISTFCTPTR */
    }
# if (BSWM_ONINITOFIMMEDIATEUSER == STD_ON)
#  if(BSWM_MULTIPARTITION == STD_ON)
    /* #33 In case of Multi Partition, synchronize all partitions and cores */
    BswM_GetInitSyncCallout(0u, partitionIdx)(partitionIdx, BSWM_SYNC_LEVEL_TWO); /* SBSW_BSWM_PARTITIONINDEXACCESS */
#  endif

    /* #34 Queue mode request which shall be arbitrated on initialization (this must be done after executing the
     *       initiating action lists to avoid development errors due to already queued mode requests). */
    for(idx = 0u; idx < BswM_GetSizeOfModeRequestQueue(partitionIdx); idx++)
    {
      if (BswM_IsOnInitOfImmediateUser(idx, partitionIdx))
      {
        BswM_SetQueueWritten(TRUE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
        BswM_SetModeRequestQueue(idx, BSWM_REQUEST_QUEUED, partitionIdx); /* SBSW_BSWM_SETMODEREQUESTQUEUE */
      }
    }
# endif
#endif

#if (BSWM_IMMEDIATEUSER == STD_ON)
    /* #35 Arbitrate mode requests which shall be arbitrated on initialization or occurred during the execution of the
     *     initiating action lists. */
    BswM_ProcessQueuedRequests(partitionIdx);
#endif
    
    BswM_SetQueueSemaphore(BSWM_REQUEST_SEMAPHORE_UNLOCKED, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
  }
# if(BSWM_MULTIPARTITION == STD_OFF)
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

  BSWM_DUMMY_STATEMENT_CONST(ConfigPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Report --------------------------------------- */
#if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_INIT_ID, errorId);
  }
#else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */



/**********************************************************************************************************************
 *  BswM_Deinit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_Deinit(void)
{
  /* ----- Local Variables ---------------------------------------------- */
#if (BSWM_IMMEDIATEUSER == STD_ON)
  BswM_ModeRequestQueueIterType queueIndex;
#endif

  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetPartitionContext();

  /* ----- Implementation ----------------------------------------------- */
  /* #30 Set state of BswM to not initialized. */
  BswM_SetInitialized(FALSE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */

#if (BSWM_IMMEDIATEUSER == STD_ON)
  BswM_EnterCriticalArea_0();

  /* #31 Remove queued mode requests. */
  for(queueIndex = 0u; queueIndex < BswM_GetSizeOfModeRequestQueue(partitionIdx); queueIndex++)
  {
    BswM_SetModeRequestQueue(queueIndex, BSWM_REQUEST_IDLE, partitionIdx); /* SBSW_BSWM_SETMODEREQUESTQUEUE */
  }

  BswM_LeaveCriticalArea_0();
#endif

  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}

#if(BSWM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  BswM_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, BSWM_APPL_DATA) VersionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if the passed parameter is not a null pointer. */
  if (VersionInfo == NULL_PTR)
  {
    errorId = BSWM_E_PARAM_INVALID;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
    /* #30 Pass the version information to the Std_VersionInfoType pointer. */
    VersionInfo -> vendorID         = BSWM_VENDOR_ID; /* SBSW_BSWM_GETVERSIONINFO */
    VersionInfo -> moduleID         = BSWM_MODULE_ID; /* SBSW_BSWM_GETVERSIONINFO */
    VersionInfo -> sw_major_version = (uint8)BSWM_SW_MAJOR_VERSION; /* SBSW_BSWM_GETVERSIONINFO */
    VersionInfo -> sw_minor_version = BSWM_SW_MINOR_VERSION; /* SBSW_BSWM_GETVERSIONINFO */
    VersionInfo -> sw_patch_version = BSWM_SW_PATCH_VERSION; /* SBSW_BSWM_GETVERSIONINFO */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_GETVERSIONINFO_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

/**********************************************************************************************************************
 *  BswM_RequestMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_RequestMode(BswM_UserType requesting_user, BswM_ModeType requested_mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
#if(BSWM_GENERICSTATE == STD_ON)
  BswM_GenericStateIterType userHandle;
#endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
#if (BSWM_DEV_ERROR_DETECT == STD_ON)
# if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
# endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
#endif
  /* ----- Implementation ----------------------------------------------- */
  {
#if(BSWM_GENERICSTATE == STD_ON)
    for(userHandle = 0u; userHandle < BswM_GetSizeOfGenericState(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfGenericMapping(userHandle, partitionIdx) == requesting_user)
      {
        BswM_SetGenericState(userHandle, requested_mode, partitionIdx); /* SBSW_BSWM_GENERICSTATE */
# if(BSWM_IMMEDIATEUSERUSEDOFGENERICMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfGenericMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfGenericMapping(userHandle, partitionIdx), BSWM_REQUESTMODE_ID, partitionIdx);
# endif
        /* errorId is initialized with BSWM_E_REQ_USER_OUT_OF_RANGE but user exists - set errorId to BSWM_E_NO_ERROR */
        errorId = BSWM_E_NO_ERROR;
        break;
      }
    }
#else
    BSWM_DUMMY_STATEMENT(requesting_user); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT(requested_mode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
#if (BSWM_DEV_ERROR_REPORT == STD_ON)
# if(BSWM_GENERICSTATE == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
# endif
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_REQUESTMODE_ID, errorId);
  }
#else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* BswM_RequestMode() */

#if (BSWM_ENABLE_RULE_CONTROL == STD_ON) && (BSWM_RULES == STD_ON)
/**********************************************************************************************************************
 *  BswM_RuleControl()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_RuleControl(BswM_IdOfRulesType ruleId, uint8 state)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  BswM_HandleType idx;
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (state > BSWM_DEACTIVATED)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
    for(idx = 0u; idx < BswM_GetSizeOfRules(partitionIdx); idx++)
    {
      if(BswM_GetIdOfRules(idx, partitionIdx) == ruleId)
      {
        BswM_SetRuleStates(idx, state, partitionIdx); /* SBSW_BSWM_SETRULESTATE */
        /* errorId is initialized with BSWM_E_REQ_USER_OUT_OF_RANGE but user exists - set errorId to BSWM_E_NO_ERROR */
        errorId = BSWM_E_NO_ERROR;
        break;
      }
    }
  }

  BSWM_DUMMY_STATEMENT(ruleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  BSWM_DUMMY_STATEMENT_DET_OFF(state); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_RULECONTROL_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if( BSWM_ENABLE_COMM == STD_ON )
/**********************************************************************************************************************
 *  BswM_ComM_CurrentMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_ComM_CurrentMode(NetworkHandleType Network, ComM_ModeType RequestedMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_COMMCHANNELSTATE == STD_ON)
  BswM_ComMChannelStateIterType userHandle;
# endif

  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. (\trace SPEC-7924, SPEC-7863, SPEC-7903) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (Network >= BSWM_CHANNEL_COUNT)
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (RequestedMode > COMM_FULL_COMMUNICATION)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_COMMCHANNELSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfComMChannelState(partitionIdx); userHandle++) /* COV_BSWM_ALLNETWORKPORTS */
    {
      if (BswM_GetExternalIdOfComMChannelMapping(userHandle, partitionIdx) == Network)
      {
        BswM_SetComMChannelState(userHandle, RequestedMode, partitionIdx); /* SBSW_BSWM_COMMCHANNELSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFCOMMCHANNELMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfComMChannelMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfComMChannelMapping(userHandle, partitionIdx), BSWM_COMM_CURRENTMODE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(Network); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(RequestedMode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_COMM_CURRENTMODE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_COMM_INITIATE_RESET == STD_ON)
/**********************************************************************************************************************
 *  BswM_ComM_InitiateReset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_ComM_InitiateReset(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_IMMEDIATEUSERUSEDOFCOMMINITIATERESETMAPPING == STD_ON) && ((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON && BSWM_USE_INIT_POINTER == STD_ON) || BSWM_MULTIPARTITION == STD_ON)
  BswM_ComMInitiateResetMappingIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {

# if(BSWM_IMMEDIATEUSERUSEDOFCOMMINITIATERESETMAPPING == STD_ON)
#  if((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON && BSWM_USE_INIT_POINTER == STD_ON) || (BSWM_MULTIPARTITION == STD_ON))
    for (userHandle = 0u; userHandle < BswM_GetSizeOfComMInitiateResetMapping(partitionIdx); userHandle++) /* Size can only be 0 or 1. */
#  endif
    {
      BswM_SetComMInitiateResetState(TRUE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
      BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfComMInitiateResetMapping(0u, partitionIdx), BswM_GetImmediateUserEndIdxOfComMInitiateResetMapping(0u, partitionIdx), BSWM_COMM_INITIATERESET_ID, partitionIdx);
      BswM_SetComMInitiateResetState(FALSE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    }
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_COMM_INITIATERESET_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

#if (BSWM_COMM_PNC_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  BswM_ComM_CurrentPNCMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_ComM_CurrentPNCMode(PNCHandleType PNC, ComM_PncModeType RequestedMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_COMMPNCSTATE == STD_ON)
  BswM_ComMPncStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed mode is in range.  (\trace SPEC-16710, SPEC-16754) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (RequestedMode > COMM_PNC_REQUESTED)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_COMMPNCSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfComMPncState(partitionIdx); userHandle++) /* COV_BSWM_ALLNETWORKPORTS */
    {
      if (BswM_GetExternalIdOfComMPncMapping(userHandle, partitionIdx) == PNC)
      {
        BswM_SetComMPncState(userHandle, RequestedMode, partitionIdx); /* SBSW_BSWM_COMMPNCSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFCOMMPNCMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfComMPncMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfComMPncMapping(userHandle, partitionIdx), BSWM_COMM_PNC_CURRENTMODE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT(PNC); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(RequestedMode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_COMM_PNC_CURRENTMODE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_DCM == STD_ON)
/**********************************************************************************************************************
 *  BswM_Dcm_ApplicationUpdated()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_Dcm_ApplicationUpdated(void) 
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_IMMEDIATEUSERUSEDOFDCMAPPLUPDATEMAPPING == STD_ON) && ((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON && BSWM_USE_INIT_POINTER == STD_ON) || BSWM_MULTIPARTITION == STD_ON)
  BswM_DcmApplUpdateMappingIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if(BSWM_IMMEDIATEUSERUSEDOFDCMAPPLUPDATEMAPPING == STD_ON)
#  if((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON && BSWM_USE_INIT_POINTER == STD_ON) || (BSWM_MULTIPARTITION == STD_ON))
    for (userHandle = 0u; userHandle < BswM_GetSizeOfDcmApplUpdateMapping(partitionIdx); userHandle++) /* Size can only be 0 or 1. */
#  endif
    {
      BswM_SetDcmApplUpdateState(TRUE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
      BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfDcmApplUpdateMapping(0u, partitionIdx), BswM_GetImmediateUserEndIdxOfDcmApplUpdateMapping(0u, partitionIdx), BSWM_DCM_APPLICATION_UPDATED_ID, partitionIdx);
      BswM_SetDcmApplUpdateState(FALSE, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    }
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_DCM_APPLICATION_UPDATED_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

#if(BSWM_ENABLE_DCM == STD_ON)
/**********************************************************************************************************************
 *  BswM_Dcm_CommunicationMode_CurrentState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_Dcm_CommunicationMode_CurrentState(NetworkHandleType Network, Dcm_CommunicationModeType RequestedMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_DCMCOMSTATE == STD_ON)
  BswM_DcmComStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. (\trace SPEC-7844, SPEC-7923, SPEC-7946) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (Network >= BSWM_CHANNEL_COUNT)
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (RequestedMode > DCM_DISABLE_RX_TX_NORM_NM)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_DCMCOMSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfDcmComState(partitionIdx); userHandle++) /* COV_BSWM_ALLNETWORKPORTS */
    {
      if (BswM_GetExternalIdOfDcmComMapping(userHandle, partitionIdx) == Network)
      {
        BswM_SetDcmComState(userHandle, RequestedMode, partitionIdx); /* SBSW_BSWM_DCMCOMSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFDCMCOMMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfDcmComMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfDcmComMapping(userHandle, partitionIdx), BSWM_DCM_COMMUNICATION_STATE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(Network); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(RequestedMode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_DCM_COMMUNICATION_STATE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_CANSM == STD_ON)
/**********************************************************************************************************************
 *  BswM_CanSM_CurrentState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_CanSM_CurrentState(NetworkHandleType Network, CanSM_BswMCurrentStateType CurrentState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_CANSMCHANNELSTATE == STD_ON)
  BswM_CanSMChannelStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. (\trace SPEC-7737, SPEC-7915, SPEC-7908) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (Network >= BSWM_CHANNEL_COUNT)
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (CurrentState > CANSM_BSWM_CHANGE_BAUDRATE)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_CANSMCHANNELSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfCanSMChannelState(partitionIdx); userHandle++) /* COV_BSWM_ALLNETWORKPORTS */
    {
      if (BswM_GetExternalIdOfCanSMChannelMapping(userHandle, partitionIdx) == Network)
      {
        BswM_SetCanSMChannelState(userHandle, CurrentState, partitionIdx); /* SBSW_BSWM_CANSMCHANNELSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFCANSMCHANNELMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfCanSMChannelMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfCanSMChannelMapping(userHandle, partitionIdx), BSWM_CANSM_CURRENTSTATE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(Network); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(CurrentState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_CANSM_CURRENTSTATE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_ETHIF == STD_ON)
/**********************************************************************************************************************
 *  BswM_EthIf_PortGroupLinkStateChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_EthIf_PortGroupLinkStateChg(EthIf_SwitchPortGroupIdxType PortGroupIdx, EthTrcv_LinkStateType PortGroupState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_ETHIFPORTSTATE == STD_ON)
  BswM_EthIfPortStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (PortGroupState > ETHTRCV_LINK_STATE_ACTIVE)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_ETHIFPORTSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfEthIfPortState(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfEthIfPortMapping(userHandle, partitionIdx) == PortGroupIdx)
      {
        BswM_SetEthIfPortState(userHandle, PortGroupState, partitionIdx); /* SBSW_BSWM_ETHIFPORTSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFETHIFPORTMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfEthIfPortMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfEthIfPortMapping(userHandle, partitionIdx), BSWM_ETHIF_PORTGROUPLINKSTATECHANGE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT(PortGroupIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(PortGroupState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_ETHIF_PORTGROUPLINKSTATECHANGE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_ETHSM == STD_ON)
/**********************************************************************************************************************
 *  BswM_EthSM_CurrentState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_EthSM_CurrentState(NetworkHandleType Network, EthSM_NetworkModeStateType CurrentState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_ETHSMSTATE == STD_ON)
  BswM_EthSMStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. (\trace SPEC-7782, SPEC-7875, SPEC-7881) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (Network >= BSWM_CHANNEL_COUNT)
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (CurrentState > ETHSM_BSWM_WAIT_OFFLINE)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_ETHSMSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfEthSMState(partitionIdx); userHandle++) /* COV_BSWM_ALLNETWORKPORTS */
    {
      if (BswM_GetExternalIdOfEthSMMapping(userHandle, partitionIdx) == Network)
      {
        BswM_SetEthSMState(userHandle, CurrentState, partitionIdx); /* SBSW_BSWM_ETHSMSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFETHSMMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfEthSMMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfEthSMMapping(userHandle, partitionIdx), BSWM_ETHSM_CURRENTMODE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(Network); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(CurrentState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_ETHSM_CURRENTMODE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_FRSM == STD_ON)
/**********************************************************************************************************************
 *  BswM_FrSM_CurrentState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_FrSM_CurrentState(NetworkHandleType Network, FrSM_BswM_StateType CurrentState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_FRSMSTATE == STD_ON)
  BswM_FrSMStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. (\trace SPEC-7886, SPEC-7890, SPEC-7955) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (Network >= BSWM_CHANNEL_COUNT)
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (CurrentState > FRSM_BSWM_ONLINE_PASSIVE_ECU_PASSIVE)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_FRSMSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfFrSMState(partitionIdx); userHandle++) /* COV_BSWM_ALLNETWORKPORTS */
    {
      if (BswM_GetExternalIdOfFrSMMapping(userHandle, partitionIdx) == Network)
      {
        BswM_SetFrSMState(userHandle, CurrentState, partitionIdx); /* SBSW_BSWM_FRSMSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFFRSMMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfFrSMMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfFrSMMapping(userHandle, partitionIdx), BSWM_FRSM_CURRENTSTATE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(Network); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(CurrentState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_FRSM_CURRENTSTATE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_J1939DCM == STD_ON)
/**********************************************************************************************************************
 *  BswM_J1939DcmBroadcastStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_J1939DcmBroadcastStatus(uint16 NetworkMask)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_IMMEDIATEUSERUSEDOFJ1939DCMMAPPING == STD_ON) && ((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON && BSWM_USE_INIT_POINTER == STD_ON) || BSWM_MULTIPARTITION == STD_ON)
  BswM_J1939DcmMappingIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_J1939DCMSTATE == STD_ON)
    BswM_SetJ1939DcmState(NetworkMask, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
#  if(BSWM_IMMEDIATEUSERUSEDOFJ1939DCMMAPPING == STD_ON)
#   if((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON && BSWM_USE_INIT_POINTER == STD_ON) || (BSWM_MULTIPARTITION == STD_ON))
    for (userHandle = 0u; userHandle < BswM_GetSizeOfJ1939DcmMapping(partitionIdx); userHandle++) /* Size can only be 0 or 1. */
#   endif
    {
      BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfJ1939DcmMapping(0u, partitionIdx), BswM_GetImmediateUserEndIdxOfJ1939DcmMapping(0u, partitionIdx), BSWM_J1939DCM_BROADCASTSTATUS_ID, partitionIdx);
    }
#  endif
# else
    BSWM_DUMMY_STATEMENT(NetworkMask); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_J1939DCM_BROADCASTSTATUS_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

#if (BSWM_ENABLE_J1939NM == STD_ON)
/**********************************************************************************************************************
 *  BswM_J1939Nm_StateChangeNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_J1939Nm_StateChangeNotification(NetworkHandleType Network, uint8 Node, Nm_StateType NmState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if(BSWM_J1939NMSTATE == STD_ON)
  uint16 index = (uint16)((((uint16) Node) << 8) | Network);
  BswM_J1939NmStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (Network >= BSWM_CHANNEL_COUNT)
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (!((NmState == NM_STATE_OFFLINE) || (NmState == NM_STATE_NORMAL_OPERATION) || (NmState == NM_STATE_BUS_SLEEP)))
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_J1939NMSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfJ1939NmState(partitionIdx); userHandle++) /* COV_BSWM_ALLNETWORKPORTS */
    {
      if (BswM_GetExternalIdOfJ1939NmMapping(userHandle, partitionIdx) == index)
      {
        BswM_SetJ1939NmState(userHandle, NmState, partitionIdx); /* SBSW_BSWM_J1939NMSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFJ1939NMMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfJ1939NmMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfJ1939NmMapping(userHandle, partitionIdx), BSWM_J1939NM_STATE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(Network); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT(Node); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(NmState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_J1939NM_STATE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_LINSM == STD_ON)
/**********************************************************************************************************************
 *  BswM_LinSM_CurrentSchedule()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_LinSM_CurrentSchedule(NetworkHandleType Network, LinIf_SchHandleType CurrentSchedule)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_LINSCHEDULESTATE == STD_ON)
  BswM_LinScheduleStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. (\trace SPEC-7856, SPEC-7753) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (Network >= BSWM_CHANNEL_COUNT)
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_LINSCHEDULESTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfLinScheduleState(partitionIdx); userHandle++) /* COV_BSWM_ALLNETWORKPORTS */
    {
      if (BswM_GetExternalIdOfLinScheduleMapping(userHandle, partitionIdx) == Network)
      {
        BswM_SetLinScheduleState(userHandle, CurrentSchedule, partitionIdx); /* SBSW_BSWM_LINSCHEDULESTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFLINSCHEDULEMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfLinScheduleMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfLinScheduleMapping(userHandle, partitionIdx), BSWM_LINSM_CURRENTSCHEDULE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(Network); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT(CurrentSchedule); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_LINSM_CURRENTSCHEDULE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  BswM_LinSM_CurrentState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_LinSM_CurrentState(NetworkHandleType Network, LinSM_ModeType CurrentState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_LINSMSTATE == STD_ON)
  BswM_LinSMStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. (\trace SPEC-7943, SPEC-7911, SPEC-7883) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (Network >= BSWM_CHANNEL_COUNT)
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (!((CurrentState == LINSM_BSWM_FULL_COM) || (CurrentState == LINSM_BSWM_NO_COM)))
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_LINSMSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfLinSMState(partitionIdx); userHandle++) /* COV_BSWM_ALLNETWORKPORTS */
    {
      if (BswM_GetExternalIdOfLinSMMapping(userHandle, partitionIdx) == Network)
      {
        BswM_SetLinSMState(userHandle, CurrentState, partitionIdx); /* SBSW_BSWM_LINSMSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFLINSMMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfLinSMMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfLinSMMapping(userHandle, partitionIdx), BSWM_LINSM_CURRENTSTATE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(Network); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(CurrentState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_LINSM_CURRENTSTATE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  BswM_LinSM_ScheduleEndNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_LinSM_ScheduleEndNotification(NetworkHandleType Network, LinIf_SchHandleType Schedule)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_LINSCHEDULEENDSTATE == STD_ON)
  BswM_LinScheduleEndStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (Network >= BSWM_CHANNEL_COUNT)
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_LINSCHEDULEENDSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfLinScheduleEndState(partitionIdx); userHandle++) /* COV_BSWM_ALLNETWORKPORTS */
    {
      if (BswM_GetExternalIdOfLinScheduleEndMapping(userHandle, partitionIdx) == Network)
      {
        BswM_SetLinScheduleEndState(userHandle, Schedule, partitionIdx); /* SBSW_BSWM_LINSCHEDULEENDSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFLINSCHEDULEENDMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfLinScheduleEndMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfLinScheduleEndMapping(userHandle, partitionIdx), BSWM_LINSM_SCHEDULEENDNOTIFICATION_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(Network); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT(Schedule); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_LINSM_SCHEDULEENDNOTIFICATION_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* BSWM_ENABLE_LINSM == STD_ON */

#if (BSWM_ENABLE_LINTP == STD_ON)
/**********************************************************************************************************************
 *  BswM_LinTp_RequestMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_LinTp_RequestMode(NetworkHandleType Network, LinTp_Mode LinTpRequestedMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_LINTPSTATE == STD_ON)
  BswM_LinTPStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. (\trace SPEC-7873, SPEC-7891, SPEC-16660) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (Network >= BSWM_CHANNEL_COUNT)
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (LinTpRequestedMode > LINTP_DIAG_RESPONSE)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_LINTPSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfLinTPState(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfLinTPMapping(userHandle, partitionIdx) == Network)
      {
        BswM_SetLinTPState(userHandle, LinTpRequestedMode, partitionIdx); /* SBSW_BSWM_LINTPSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFLINTPMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfLinTPMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfLinTPMapping(userHandle, partitionIdx), BSWM_LINTP_REQUESTMODE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(Network); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(LinTpRequestedMode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_LINTP_REQUESTMODE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_ECUM == STD_ON)
/**********************************************************************************************************************
 *  BswM_EcuM_CurrentState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_EcuM_CurrentState(EcuM_StateType CurrentState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_IMMEDIATEUSERUSEDOFECUMMODEMAPPING == STD_ON) && (((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON) && (BSWM_USE_INIT_POINTER == STD_ON)) || (BSWM_MULTIPARTITION == STD_ON))
  BswM_EcuMModeMappingIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (!(
      /* Most used states are located at the top to improve runtime */
      (CurrentState == ECUM_STATE_APP_RUN)           ||
      (CurrentState == ECUM_STATE_APP_POST_RUN)      ||
      (CurrentState == ECUM_STATE_SLEEP)             ||
      (CurrentState == ECUM_STATE_SHUTDOWN)          ||
      (CurrentState == ECUM_STATE_PREP_SHUTDOWN)     ||
      (CurrentState == ECUM_STATE_STARTUP)           ||
      (CurrentState == ECUM_STATE_STARTUP_ONE)       ||
      (CurrentState == ECUM_STATE_STARTUP_TWO)       ||
      (CurrentState == ECUM_STATE_WAKEUP)            ||
      (CurrentState == ECUM_STATE_RUN)               ||
      (CurrentState == ECUM_STATE_WAKEUP_ONE)        ||
      (CurrentState == ECUM_STATE_WAKEUP_VALIDATION) ||
      (CurrentState == ECUM_STATE_WAKEUP_REACTION)   ||
      (CurrentState == ECUM_STATE_WAKEUP_TWO)        ||
      (CurrentState == ECUM_STATE_WAKEUP_WAKESLEEP)  ||
      (CurrentState == ECUM_STATE_WAKEUP_TTII)       ||
      (CurrentState == ECUM_STATE_GO_SLEEP)          ||
      (CurrentState == ECUM_STATE_GO_OFF_ONE)        ||
      (CurrentState == ECUM_STATE_GO_OFF_TWO)        ||
      (CurrentState == ECUM_STATE_RESET)             ||
      (CurrentState == ECUM_STATE_OFF)
     ))
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_ECUMMODESTATE == STD_ON)
    BswM_SetEcuMModeState(CurrentState, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
#  if(BSWM_IMMEDIATEUSERUSEDOFECUMMODEMAPPING == STD_ON)
#   if((BSWM_POSTBUILD_VARIANT_SUPPORT == STD_ON && BSWM_USE_INIT_POINTER == STD_ON) || (BSWM_MULTIPARTITION == STD_ON))
    for (userHandle = 0u; userHandle < BswM_GetSizeOfEcuMModeMapping(partitionIdx); userHandle++) /* Size can only be 0 or 1. */
#   endif
    {
      BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfEcuMModeMapping(0u, partitionIdx), BswM_GetImmediateUserEndIdxOfEcuMModeMapping(0u, partitionIdx), BSWM_ECUM_CURRENTSTATE_ID, partitionIdx);
    }
#  endif
# else
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(CurrentState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_ECUM_CURRENTSTATE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

#if (BSWM_ENABLE_ECUM == STD_ON)
/**********************************************************************************************************************
 *  BswM_EcuM_CurrentWakeup()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_EcuM_CurrentWakeup(EcuM_WakeupSourceType source, EcuM_WakeupStateType state)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if(BSWM_ECUMWAKEUPSTATE == STD_ON)
  BswM_EcuMWakeupStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. (\trace SPEC-7850, SPEC-7921) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (state > BSWM_ECUM_MAX_WKSTATUS)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if(BSWM_ECUMWAKEUPSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfEcuMWakeupState(partitionIdx); userHandle++)
    {
      if ((((EcuM_WakeupSourceType)BswM_GetExternalIdOfEcuMWakeupMapping(userHandle, partitionIdx)) & source) != 0u)
      {
        BswM_SetEcuMWakeupState(userHandle, state, partitionIdx); /* SBSW_BSWM_ECUMWAKEUPSTATE */
#  if(BSWM_IMMEDIATEUSERUSEDOFECUMWAKEUPMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfEcuMWakeupMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfEcuMWakeupMapping(userHandle, partitionIdx), BSWM_ECUM_CURRENTWAKEUP_ID, partitionIdx);
#  endif
      }
    }
# else
    BSWM_DUMMY_STATEMENT(source); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(state); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_ECUM_CURRENTWAKEUP_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  BswM_EcuM_RequestedState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_EcuM_RequestedState(EcuM_StateType State, EcuM_RunStatusType CurrentStatus)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_ECUMRUNREQUESTSTATE == STD_ON)
  BswM_EcuMRunRequestStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (!((State == ECUM_STATE_APP_RUN) || (State == ECUM_STATE_APP_POST_RUN)))
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (CurrentStatus > ECUM_RUNSTATUS_RELEASED)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_ECUMRUNREQUESTSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfEcuMRunRequestState(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfEcuMRunRequestMapping(userHandle, partitionIdx) == State)
      {
        BswM_SetEcuMRunRequestState(userHandle, CurrentStatus, partitionIdx); /* SBSW_BSWM_ECUMRUNREQUESTSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFECUMRUNREQUESTMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfEcuMRunRequestMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfEcuMRunRequestMapping(userHandle, partitionIdx), BSWM_ECUM_REQUESTEDSTATE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(State); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(CurrentStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_ECUM_REQUESTEDSTATE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* BSWM_ENABLE_ECUM == STD_ON */

#if (BSWM_ENABLE_NM == STD_ON)
/**********************************************************************************************************************
 *  BswM_Nm_StateChangeNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( void, BSWM_CODE ) BswM_Nm_StateChangeNotification( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle,
                                                         CONST( Nm_StateType, AUTOMATIC) nmPreviousState,
                                                         CONST( Nm_StateType, AUTOMATIC ) nmCurrentState )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_NMSTATE == STD_ON)
  BswM_NmStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. */
  /* nmPreviousState is not relevant */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (nmNetworkHandle >= BSWM_CHANNEL_COUNT)
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
#   if defined NM_STATE_NUMBER_OF_STATES /* COV_BSWM_NM_COMPATIBILITY */
  else if (nmCurrentState >= NM_STATE_NUMBER_OF_STATES)
#   else
  else if (nmCurrentState > NM_STATE_OFFLINE)
#   endif
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_NMSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfNmState(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfNmMapping(userHandle, partitionIdx) == nmNetworkHandle)
      {
        BswM_SetNmState(userHandle, nmCurrentState, partitionIdx); /* SBSW_BSWM_NMSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFNMMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfNmMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfNmMapping(userHandle, partitionIdx), BSWM_NM_STATE_CHANGE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
#  if (BSWM_DEV_ERROR_DETECT == STD_OFF)
    BSWM_DUMMY_STATEMENT_CONST(nmNetworkHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
#  if (BSWM_DEV_ERROR_DETECT == STD_OFF) || (BSWM_MODE_CHECK == STD_OFF)
    BSWM_DUMMY_STATEMENT_CONST(nmCurrentState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
# endif
    BSWM_DUMMY_STATEMENT_CONST(nmPreviousState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_NM_STATE_CHANGE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_NVM == STD_ON)
/**********************************************************************************************************************
 *  BswM_NvM_CurrentBlockMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC (void, BSWM_CODE) BswM_NvM_CurrentBlockMode(NvM_BlockIdType Block, NvM_RequestResultType CurrentBlockMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_NVMBLOCKSTATE == STD_ON)
  BswM_NvMBlockStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed mode is in range. (\trace SPEC-7795, SPEC-7945) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (CurrentBlockMode > NVM_REQ_RESTORED_FROM_ROM)
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_NVMBLOCKSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfNvMBlockState(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfNvMBlockMapping(userHandle, partitionIdx) == Block)
      {
        BswM_SetNvMBlockState(userHandle, CurrentBlockMode, partitionIdx); /* SBSW_BSWM_NVMBLOCKSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFNVMBLOCKMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfNvMBlockMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfNvMBlockMapping(userHandle, partitionIdx), BSWM_NVM_CURRENTBLOCKMODE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT(Block); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(CurrentBlockMode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_NVM_CURRENTBLOCKMODE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_NVM == STD_ON)
/**********************************************************************************************************************
 *  BswM_NvM_CurrentJobMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC (void, BSWM_CODE) BswM_NvM_CurrentJobMode(uint8 ServiceId, NvM_RequestResultType CurrentJobMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_NVMJOBSTATE == STD_ON)
  BswM_NvMJobStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed mode is in range. (\trace SPEC-16676, SPEC-16673, SPEC-16749) */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else if (!((ServiceId == 0x0Cu) || (ServiceId == 0x0Du)))
  {
    errorId = BSWM_E_REQ_USER_OUT_OF_RANGE;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  else if (!((CurrentJobMode == NVM_REQ_OK) || (CurrentJobMode == NVM_REQ_PENDING) || (CurrentJobMode == NVM_REQ_NOT_OK)
      || (CurrentJobMode == NVM_REQ_CANCELED)))
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_NVMJOBSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfNvMJobState(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfNvMJobMapping(userHandle, partitionIdx) == ServiceId)
      {
        BswM_SetNvMJobState(userHandle, CurrentJobMode, partitionIdx); /* SBSW_BSWM_NVMJOBSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFNVMJOBMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfNvMJobMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfNvMJobMapping(userHandle, partitionIdx), BSWM_NVM_CURRENTJOBMODE_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT_DET_OFF(ServiceId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(CurrentJobMode); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_NVM_CURRENTJOBMODE_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_PDUR == STD_ON)
/**********************************************************************************************************************
 *  BswM_PduR_RxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_PduR_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, BSWM_APPL_DATA) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_PDURRXINDICATIONSTATE == STD_ON)
  BswM_PduRRxIndicationMappingIterType userHandle;
#  if (BSWM_PDURRXINDICATIONSTATEIDXOFPDURRXINDICATIONMAPPING == STD_ON)
  BswM_PduRRxIndicationStateIterType internalId;
#  endif
# endif

  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_IMMEDIATEUSERUSEDOFPDURRXINDICATIONMAPPING == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfPduRRxIndicationMapping(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfPduRRxIndicationMapping(userHandle, partitionIdx) == RxPduId)
      {
#  if (BSWM_PDURRXINDICATIONSTATEIDXOFPDURRXINDICATIONMAPPING == STD_ON)
        internalId = BswM_GetPduRRxIndicationStateIdxOfPduRRxIndicationMapping(userHandle, partitionIdx);
        BswM_SetPduRRxIndicationState(internalId, TRUE, partitionIdx); /* SBSW_BSWM_PDURRXINDICATIONSTATEIND */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRRxIndicationMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRRxIndicationMapping(userHandle, partitionIdx), BSWM_PDUR_RXINDICATION_ID, partitionIdx);
        BswM_SetPduRRxIndicationState(internalId, FALSE, partitionIdx); /* SBSW_BSWM_PDURRXINDICATIONSTATEIND */
        /* Do not break, PduId could be used in multiple ports */
#  else
        BswM_SetPduRRxIndicationState(userHandle, TRUE, partitionIdx); /* SBSW_BSWM_PDURRXINDICATIONSTATE */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRRxIndicationMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRRxIndicationMapping(userHandle, partitionIdx), BSWM_PDUR_RXINDICATION_ID, partitionIdx);
        BswM_SetPduRRxIndicationState(userHandle, FALSE, partitionIdx); /* SBSW_BSWM_PDURRXINDICATIONSTATE */
        break;
#  endif
      }
    }
# else
    BSWM_DUMMY_STATEMENT(RxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
    BSWM_DUMMY_STATEMENT_CONST(PduInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }

  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_PDUR_RXINDICATION_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}

/**********************************************************************************************************************
 *  BswM_PduR_TpRxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_PduR_TpRxIndication(PduIdType id, Std_ReturnType result)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_PDURTPRXINDICATIONSTATE == STD_ON)
  BswM_PduRTpRxIndicationMappingIterType userHandle;
#  if (BSWM_PDURTPRXINDICATIONSTATEIDXOFPDURTPRXINDICATIONMAPPING == STD_ON)
  BswM_PduRTpRxIndicationStateIterType internalId;
#  endif
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_IMMEDIATEUSERUSEDOFPDURTPRXINDICATIONMAPPING == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfPduRTpRxIndicationMapping(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfPduRTpRxIndicationMapping(userHandle, partitionIdx) == id)
      {
#  if (BSWM_PDURTPRXINDICATIONSTATEIDXOFPDURTPRXINDICATIONMAPPING == STD_ON)
        internalId = BswM_GetPduRTpRxIndicationStateIdxOfPduRTpRxIndicationMapping(userHandle, partitionIdx);
        BswM_SetPduRTpRxIndicationState(internalId, TRUE, partitionIdx); /* SBSW_BSWM_PDURTPRXINDICATIONSTATEIND */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRTpRxIndicationMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRTpRxIndicationMapping(userHandle, partitionIdx), BSWM_PDUR_TPRXINDICATION_ID, partitionIdx);
        BswM_SetPduRTpRxIndicationState(internalId, FALSE, partitionIdx); /* SBSW_BSWM_PDURTPRXINDICATIONSTATEIND */
        /* Do not break, PduId could be used in multiple ports */
#  else
        BswM_SetPduRTpRxIndicationState(userHandle, TRUE, partitionIdx); /* SBSW_BSWM_PDURTPRXINDICATIONSTATE */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRTpRxIndicationMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRTpRxIndicationMapping(userHandle, partitionIdx), BSWM_PDUR_TPRXINDICATION_ID, partitionIdx);
        BswM_SetPduRTpRxIndicationState(userHandle, FALSE, partitionIdx); /* SBSW_BSWM_PDURTPRXINDICATIONSTATE */
        break;
#  endif
      }
    }
# else
    BSWM_DUMMY_STATEMENT(id); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
    BSWM_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_PDUR_TPRXINDICATION_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}

/**********************************************************************************************************************
 *  BswM_PduR_TpStartOfReception()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_BSWM_3673 */
FUNC(void, BSWM_CODE) BswM_PduR_TpStartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, BSWM_APPL_DATA) info,
                                                   PduLengthType TpSduLength,
                                                   P2VAR(PduLengthType, AUTOMATIC, BSWM_APPL_DATA) bufferSizePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_PDURTPSTARTOFRECEPTIONSTATE == STD_ON)
  BswM_PduRTpStartOfReceptionMappingIterType userHandle;
#  if (BSWM_PDURTPSTARTOFRECEPTIONSTATEIDXOFPDURTPSTARTOFRECEPTIONMAPPING == STD_ON)
  BswM_PduRTpStartOfReceptionStateIterType internalId;
#  endif
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_IMMEDIATEUSERUSEDOFPDURTPSTARTOFRECEPTIONMAPPING == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfPduRTpStartOfReceptionMapping(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfPduRTpStartOfReceptionMapping(userHandle, partitionIdx) == id)
      {
#  if (BSWM_PDURTPSTARTOFRECEPTIONSTATEIDXOFPDURTPSTARTOFRECEPTIONMAPPING == STD_ON)
        internalId = BswM_GetPduRTpStartOfReceptionStateIdxOfPduRTpStartOfReceptionMapping(userHandle, partitionIdx);
        BswM_SetPduRTpStartOfReceptionState(internalId, TRUE, partitionIdx); /* SBSW_BSWM_PDURTPSTARTOFRECEPTIONSTATEIND */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRTpStartOfReceptionMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRTpStartOfReceptionMapping(userHandle, partitionIdx), BSWM_PDUR_TPSTARTOFRECEPTION_ID, partitionIdx);
        BswM_SetPduRTpStartOfReceptionState(internalId, FALSE, partitionIdx); /* SBSW_BSWM_PDURTPSTARTOFRECEPTIONSTATEIND */
        /* Do not break, PduId could be used in multiple ports */
#  else
        BswM_SetPduRTpStartOfReceptionState(userHandle, TRUE, partitionIdx); /* SBSW_BSWM_PDURTPSTARTOFRECEPTIONSTATE */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRTpStartOfReceptionMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRTpStartOfReceptionMapping(userHandle, partitionIdx), BSWM_PDUR_TPSTARTOFRECEPTION_ID, partitionIdx);
        BswM_SetPduRTpStartOfReceptionState(userHandle, FALSE, partitionIdx); /* SBSW_BSWM_PDURTPSTARTOFRECEPTIONSTATE */
        break;
#  endif
      }
    }
# else
    BSWM_DUMMY_STATEMENT(id); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
    BSWM_DUMMY_STATEMENT(info); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT(TpSduLength); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT(bufferSizePtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_PDUR_TPSTARTOFRECEPTION_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}

/**********************************************************************************************************************
 *  BswM_PduR_TpTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_PduR_TpTxConfirmation(PduIdType id, Std_ReturnType result)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_PDURTPTXCONFIRMATIONSTATE == STD_ON)
  BswM_PduRTpTxConfirmationMappingIterType userHandle;
#  if (BSWM_PDURTPTXCONFIRMATIONSTATEIDXOFPDURTPTXCONFIRMATIONMAPPING == STD_ON)
  BswM_PduRTpTxConfirmationStateIterType internalId;
#  endif
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_IMMEDIATEUSERUSEDOFPDURTPTXCONFIRMATIONMAPPING == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfPduRTpTxConfirmationMapping(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfPduRTpTxConfirmationMapping(userHandle, partitionIdx) == id)
      {
#  if (BSWM_PDURTPTXCONFIRMATIONSTATEIDXOFPDURTPTXCONFIRMATIONMAPPING == STD_ON)
        internalId = BswM_GetPduRTpTxConfirmationStateIdxOfPduRTpTxConfirmationMapping(userHandle, partitionIdx);
        BswM_SetPduRTpTxConfirmationState(internalId, TRUE, partitionIdx); /* SBSW_BSWM_PDURTPTXCONFIRMATIONSTATEIND */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRTpTxConfirmationMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRTpTxConfirmationMapping(userHandle, partitionIdx), BSWM_PDUR_TPTXCONFIRMATION_ID, partitionIdx);
        BswM_SetPduRTpTxConfirmationState(internalId, FALSE, partitionIdx); /* SBSW_BSWM_PDURTPTXCONFIRMATIONSTATEIND */
        /* Do not break, PduId could be used in multiple ports */
#  else
        BswM_SetPduRTpTxConfirmationState(userHandle, TRUE, partitionIdx); /* SBSW_BSWM_PDURTPTXCONFIRMATIONSTATE */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRTpTxConfirmationMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRTpTxConfirmationMapping(userHandle, partitionIdx), BSWM_PDUR_TPTXCONFIRMATION_ID, partitionIdx);
        BswM_SetPduRTpTxConfirmationState(userHandle, FALSE, partitionIdx); /* SBSW_BSWM_PDURTPTXCONFIRMATIONSTATE */
        break;
#  endif
      }
    }
# else
    BSWM_DUMMY_STATEMENT(id); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
    BSWM_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_PDUR_TPTXCONFIRMATION_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}

/**********************************************************************************************************************
 *  BswM_PduR_Transmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_PduR_Transmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, BSWM_APPL_DATA) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_PDURTRANSMITSTATE == STD_ON)
  BswM_PduRTransmitMappingIterType userHandle;
#  if (BSWM_PDURTRANSMITSTATEIDXOFPDURTRANSMITMAPPING == STD_ON)
  BswM_PduRTransmitStateIterType internalId;
#  endif
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_IMMEDIATEUSERUSEDOFPDURTRANSMITMAPPING == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfPduRTransmitMapping(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfPduRTransmitMapping(userHandle, partitionIdx) == id)
      {
#  if (BSWM_PDURTRANSMITSTATEIDXOFPDURTRANSMITMAPPING == STD_ON)
        internalId = BswM_GetPduRTransmitStateIdxOfPduRTransmitMapping(userHandle, partitionIdx);
        BswM_SetPduRTransmitState(internalId, TRUE, partitionIdx); /* SBSW_BSWM_PDURTRANSMITSTATEIND */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRTransmitMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRTransmitMapping(userHandle, partitionIdx), BSWM_PDUR_TRANSMIT_ID, partitionIdx);
        BswM_SetPduRTransmitState(internalId, FALSE, partitionIdx); /* SBSW_BSWM_PDURTRANSMITSTATEIND */
        /* Do not break, PduId could be used in multiple ports */
#  else
        BswM_SetPduRTransmitState(userHandle, TRUE, partitionIdx); /* SBSW_BSWM_PDURTRANSMITSTATE */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRTransmitMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRTransmitMapping(userHandle, partitionIdx), BSWM_PDUR_TRANSMIT_ID, partitionIdx);
        BswM_SetPduRTransmitState(userHandle, FALSE, partitionIdx); /* SBSW_BSWM_PDURTRANSMITSTATE */
        break;
#  endif
      }
    }
# else
    BSWM_DUMMY_STATEMENT(id); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
    BSWM_DUMMY_STATEMENT_CONST(PduInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_PDUR_TRANSMIT_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}

/**********************************************************************************************************************
 *  BswM_PduR_TxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_PduR_TxConfirmation(PduIdType TxPduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_PDURTXCONFIRMATIONSTATE == STD_ON)
  BswM_PduRTxConfirmationMappingIterType userHandle;
#  if (BSWM_PDURTXCONFIRMATIONSTATEIDXOFPDURTXCONFIRMATIONMAPPING == STD_ON)
  BswM_PduRTxConfirmationStateIterType internalId;
#  endif
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_IMMEDIATEUSERUSEDOFPDURTXCONFIRMATIONMAPPING == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfPduRTxConfirmationMapping(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfPduRTxConfirmationMapping(userHandle, partitionIdx) == TxPduId)
      {
#  if (BSWM_PDURTXCONFIRMATIONSTATEIDXOFPDURTXCONFIRMATIONMAPPING == STD_ON)
        internalId = BswM_GetPduRTxConfirmationStateIdxOfPduRTxConfirmationMapping(userHandle, partitionIdx);
        BswM_SetPduRTxConfirmationState(internalId, TRUE, partitionIdx); /* SBSW_BSWM_PDURTXCONFIRMATIONSTATEIND */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRTxConfirmationMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRTxConfirmationMapping(userHandle, partitionIdx), BSWM_PDUR_TXCONFIRMATION_ID, partitionIdx);
        BswM_SetPduRTxConfirmationState(internalId, FALSE, partitionIdx); /* SBSW_BSWM_PDURTXCONFIRMATIONSTATEIND */
        /* Do not break, PduId could be used in multiple ports */
#  else
        BswM_SetPduRTxConfirmationState(userHandle, TRUE, partitionIdx); /* SBSW_BSWM_PDURTXCONFIRMATIONSTATE */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfPduRTxConfirmationMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfPduRTxConfirmationMapping(userHandle, partitionIdx), BSWM_PDUR_TXCONFIRMATION_ID, partitionIdx);
        BswM_SetPduRTxConfirmationState(userHandle, FALSE, partitionIdx); /* SBSW_BSWM_PDURTXCONFIRMATIONSTATE */
        break;
#  endif
      }
    }
# else
    BSWM_DUMMY_STATEMENT(TxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_PDUR_TXCONFIRMATION_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

#if (BSWM_ENABLE_SD == STD_ON)
/**********************************************************************************************************************
 *  BswM_Sd_ClientServiceCurrentState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_Sd_ClientServiceCurrentState(uint16 SdClientServiceHandleId, Sd_ClientServiceCurrentStateType CurrentClientState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_SDCLIENTSERVICESTATE == STD_ON)
  BswM_SdClientServiceStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  /* If type is an enumeration the following code will cause MISRA violations because the conditions will always be
   * true, the expression always be false and so the statement is unreachable */
  else if (!((CurrentClientState == SD_CLIENT_SERVICE_DOWN) || (CurrentClientState == SD_CLIENT_SERVICE_AVAILABLE)))
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_SDCLIENTSERVICESTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfSdClientServiceState(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfSdClientServiceMapping(userHandle, partitionIdx) == SdClientServiceHandleId)
      {
        BswM_SetSdClientServiceState(userHandle, CurrentClientState, partitionIdx); /* SBSW_BSWM_SDCLIENTSERVICESTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFSDCLIENTSERVICEMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfSdClientServiceMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfSdClientServiceMapping(userHandle, partitionIdx), BSWM_SD_CLIENTSERVICE_CURRENT_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT(SdClientServiceHandleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(CurrentClientState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_SD_CLIENTSERVICE_CURRENT_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_SD == STD_ON)
/**********************************************************************************************************************
 *  BswM_Sd_ConsumedEventGroupCurrentState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_Sd_ConsumedEventGroupCurrentState(uint16 SdConsumedEventGroupHandleId, Sd_ConsumedEventGroupCurrentStateType ConsumedEventGroupState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_SDCONSUMEDEVENTSTATE == STD_ON)
  BswM_SdConsumedEventStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  /* If type is an enumeration the following code will cause MISRA violations because the conditions will always be
   * true, the expression always be false and so the statement is unreachable */
  else if (!((ConsumedEventGroupState == SD_CONSUMED_EVENTGROUP_DOWN) || (ConsumedEventGroupState == SD_CONSUMED_EVENTGROUP_AVAILABLE)))
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_SDCONSUMEDEVENTSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfSdConsumedEventState(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfSdConsumedEventMapping(userHandle, partitionIdx) == SdConsumedEventGroupHandleId)
      {
        BswM_SetSdConsumedEventState(userHandle, ConsumedEventGroupState, partitionIdx); /* SBSW_BSWM_SDCONSUMEDEVENTSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFSDCONSUMEDEVENTMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfSdConsumedEventMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfSdConsumedEventMapping(userHandle, partitionIdx), BSWM_SD_CONSUMEDEVENTGROUP_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT(SdConsumedEventGroupHandleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(ConsumedEventGroupState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_SD_CONSUMEDEVENTGROUP_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_SD == STD_ON)
/**********************************************************************************************************************
 *  BswM_Sd_EventHandlerCurrentState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_Sd_EventHandlerCurrentState(uint16 SdEventHandlerHandleId, Sd_EventHandlerCurrentStateType EventHandlerStatus)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_SDEVENTHANDLERSTATE == STD_ON)
  BswM_SdEventHandlerStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized and passed parameters are in range. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
#  if (BSWM_MODE_CHECK == STD_ON)
  /* If type is an enumeration the following code will cause MISRA violations because the conditions will always be
   * true, the expression always be false and so the statement is unreachable */
  else if (!((EventHandlerStatus == SD_EVENT_HANDLER_RELEASED) || (EventHandlerStatus == SD_EVENT_HANDLER_REQUESTED)))
  {
    errorId = BSWM_E_REQ_MODE_OUT_OF_RANGE;
  }
#  endif
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_SDEVENTHANDLERSTATE == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfSdEventHandlerState(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfSdEventHandlerMapping(userHandle, partitionIdx) == SdEventHandlerHandleId)
      {
        BswM_SetSdEventHandlerState(userHandle, EventHandlerStatus, partitionIdx); /* SBSW_BSWM_SDEVENTHANDLERSTATE */
#  if (BSWM_IMMEDIATEUSERUSEDOFSDEVENTHANDLERMAPPING == STD_ON)
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfSdEventHandlerMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfSdEventHandlerMapping(userHandle, partitionIdx), BSWM_SD_EVENTHANDLER_CURRENT_ID, partitionIdx);
#  endif
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT(SdEventHandlerHandleId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    BSWM_DUMMY_STATEMENT_MODE_CHECK_OFF(EventHandlerStatus); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_SD_EVENTHANDLER_CURRENT_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (BSWM_ENABLE_WDGM == STD_ON)
/**********************************************************************************************************************
 *  BswM_WdgM_RequestPartitionReset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, BSWM_CODE) BswM_WdgM_RequestPartitionReset(ApplicationType Application)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
# if (BSWM_WDGMSTATE == STD_ON)
  BswM_WdgMStateIterType userHandle;
# endif
  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(GetApplicationID());

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized. */
#  if (BSWM_MULTIPARTITION == STD_ON)
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
# endif
  /* ----- Implementation ----------------------------------------------- */
  {
# if (BSWM_IMMEDIATEUSERUSEDOFWDGMMAPPING == STD_ON)
    for (userHandle = 0u; userHandle < BswM_GetSizeOfWdgMState(partitionIdx); userHandle++)
    {
      if (BswM_GetExternalIdOfWdgMMapping(userHandle, partitionIdx) == Application)
      {
        BswM_SetWdgMState(userHandle, (BswM_WdgMStateType)TRUE, partitionIdx); /* SBSW_BSWM_WDGMSTATE */
        BSWM_CALL_IMMEDIATE(BswM_GetImmediateUserStartIdxOfWdgMMapping(userHandle, partitionIdx), BswM_GetImmediateUserEndIdxOfWdgMMapping(userHandle, partitionIdx), BSWM_WDGM_REQUESTPARTITIONRESET_ID, partitionIdx);
        BswM_SetWdgMState(userHandle, (BswM_WdgMStateType)FALSE, partitionIdx); /* SBSW_BSWM_WDGMSTATE */
        break;
      }
    }
# else
    BSWM_DUMMY_STATEMENT(Application); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_WDGM_REQUESTPARTITIONRESET_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

#define BSWM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "BswM_vMemMap.h"

#define BSWM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "MemMap.h"

/**********************************************************************************************************************
*  BswM_MainFunction()
*********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
*/
#if (BSWM_MULTIPARTITION == STD_ON)
FUNC(void, BSWM_CODE) BswM_MainFunction(ApplicationType applicationId)
#else
FUNC(void, BSWM_CODE) BswM_MainFunction(void)
#endif
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = BSWM_E_NO_ERROR;
#if(BSWM_IMMEDIATEUSER == STD_ON)
  uint8 localSemaphore;
#endif

  BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx = BswM_GetInternalPartitionIdx(applicationId);

  /* ----- Development Error Checks ------------------------------------- */
# if (BSWM_DEV_ERROR_DETECT == STD_ON)
#  if (BSWM_MULTIPARTITION == STD_ON)
  /* #20 Check if partition is valid and BswM is initialized. (\trace SPEC-7833) */
  if ( partitionIdx == BSWM_INVALID_PARTITION )
  {
    errorId = BSWM_E_REQ_USER_INV_PARTITION;
  }
  else
#  endif
  if (!BswM_IsInitialized(partitionIdx))
  {
    errorId = BSWM_E_NO_INIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if(BSWM_IMMEDIATEUSER == STD_ON)
    BswM_EnterCriticalArea_0();
    localSemaphore = BswM_GetQueueSemaphore(partitionIdx);
    if (BswM_GetQueueSemaphore(partitionIdx) == BSWM_REQUEST_SEMAPHORE_UNLOCKED)
    {
      BswM_SetQueueSemaphore(BSWM_REQUEST_SEMAPHORE_LOCKED, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    }
    BswM_LeaveCriticalArea_0();

    /* #31 Process pending immediate requests if semaphore was locked. */
    if (BSWM_REQUEST_SEMAPHORE_UNLOCKED == localSemaphore)
    {
      BswM_ProcessQueuedRequests(partitionIdx);
    }
#endif

#if(BSWM_SWCMODEREQUESTUPDATEFCT == STD_ON)
# if (BSWM_MULTIPARTITION == STD_ON)
    if (BswM_HasSwcModeRequestUpdateFct(partitionIdx)) /* PRQA S 2741 */ /* MD_BSWM_2741 */ /* COV_BSWM_ALL_TRUE TX */
# endif
    {
      BswM_GetSwcModeRequestUpdateFct(0u, partitionIdx)(); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    }
#endif

#if((BSWM_DEFERREDRULES == STD_ON) || (BSWM_TIMERSTATE == STD_ON))
    BswM_EnterCriticalArea_0();
# if (BSWM_TIMERSTATE == STD_ON)
    /* #33 Decrease all configured timers. */
    BswM_DecreaseTimer(partitionIdx);
# endif /* (BSWM_TIMERSTATE == STD_ON) */

# if(BSWM_DEFERREDRULES == STD_ON)
    /* #34 Arbitrate and execute all rules which have at least one deferred port (BswM_ExecuteDeferredRules). */
    BswM_ExecuteDeferredRules(partitionIdx);
# endif /* (BSWM_DEFERREDRULES == STD_ON) */
    BswM_LeaveCriticalArea_0();
#endif /* ((BSWM_DEFERREDRULES == STD_ON) || (BSWM_TIMERSTATE == STD_ON)) */

#if(BSWM_IMMEDIATEUSER == STD_ON)
    if (BSWM_REQUEST_SEMAPHORE_UNLOCKED == localSemaphore)
    {
      /* Immediately process other pending immediate requests */
      BswM_ProcessQueuedRequests(partitionIdx);
      /* Unlock semaphore AFTER processing of the queue */
      BswM_SetQueueSemaphore(BSWM_REQUEST_SEMAPHORE_UNLOCKED, partitionIdx); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    }
#endif
#if(BSWM_MODENOTIFICATIONFCT == STD_ON)
# if (BSWM_MULTIPARTITION == STD_ON)
    if (BswM_HasModeNotificationFct(partitionIdx)) /* PRQA S 2741 */ /* MD_BSWM_2741 */
# endif
    {
      BswM_GetModeNotificationFct(0u, partitionIdx)(); /* SBSW_BSWM_PARTITIONINDEXACCESS */
    }
#endif

#if(BSWM_IPDU_GROUP_CONTROL == STD_ON)
    BswM_ExecuteIpduGroupControl();
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != BSWM_E_NO_ERROR)
  {
    (void)Det_ReportError(BSWM_MODULE_ID, BSWM_INSTANCE_ID_DET, BSWM_MAINFUNCTION_ID, errorId);
  }
# else
  BSWM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

  BSWM_DUMMY_STATEMENT(partitionIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}

#define BSWM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "MemMap.h"

/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_BSWM_ACTIONFCTPTR
  \DESCRIPTION Access to generated table which contains function pointer
  \COUNTERMEASURE \S User verifies generated functions (SMI-8) and performs adequate integration (SMI-4).

\ID SBSW_BSWM_ACTIONLISTFCTPTR
  \DESCRIPTION Access to generated table which contains function pointer
  \COUNTERMEASURE \S User verifies generated functions (SMI-8) and performs adequate integration (SMI-4).

\ID SBSW_BSWM_EXPRESSIONFCTPTR
  \DESCRIPTION Access to generated table which contains function pointer
  \COUNTERMEASURE \S User verifies generated functions (SMI-8) and performs adequate integration (SMI-4).

\ID SBSW_BSWM_RULEFCTPTR
  \DESCRIPTION Access to generated table which contains function pointer
  \COUNTERMEASURE \S User verifies generated functions (SMI-8) and performs adequate integration (SMI-4).

\ID SBSW_BSWM_IMMEDIATEMODEREQUEST
  \DESCRIPTION Access to ModeRequestQueue via indirection over Domain. Immediate and ModeRequestQueue have same index using ComStackLib.
  \COUNTERMEASURE \N Qualified use-case CSL02 and CSL03 of ComStackLib

\ID SBSW_BSWM_SETACTIONLISTQUEUE
  \DESCRIPTION Access of ActionListQueue using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_PARTITIONINDEXACCESS
  \DESCRIPTION Access of all variables and functions created and used by ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib
                     If BSWM_MULTIPARTITION is STD_OFF GetPartitionIdx is defined to 0 which is always a valid index.

\ID SBSW_BSWM_SETMODEREQUESTQUEUE
  \DESCRIPTION Access of ModeRequestQueue using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_SETRULESTATE
  \DESCRIPTION Access of RuleStates using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_SETTIMER
  \DESCRIPTION Access of TimerState and TimerValue with same index using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_BSWM_GETVERSIONINFO
  \DESCRIPTION The function BswM_GetVersionInfo writes to the object referenced by parameter VersionInfo
  \COUNTERMEASURE \N The caller ensures that the pointers passed to the parameter VersionInfo is valid.

\ID SBSW_BSWM_DCMCOMSTATE
  \DESCRIPTION Access of DcmComState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_CANSMCHANNELSTATE
  \DESCRIPTION Access of CanSMChanelState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_COMMCHANNELSTATE
  \DESCRIPTION Access of ComMChanelState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_COMMPNCSTATE
  \DESCRIPTION Access of ComMPncState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_ECUMRUNREQUESTSTATE
  \DESCRIPTION Access of EcuMRunRequestState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_ECUMWAKEUPSTATE
  \DESCRIPTION Access of EcuMWakeupState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_ETHIFPORTSTATE
  \DESCRIPTION Access of EthIfPortState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_ETHSMSTATE
  \DESCRIPTION Access of EthSMState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_FRSMSTATE
  \DESCRIPTION Access of FrSMState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_GENERICSTATE
  \DESCRIPTION Access of GenericState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_J1939NMSTATE
  \DESCRIPTION Access of J1939NmState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib
  
\ID SBSW_BSWM_LINSCHEDULEENDSTATE
  \DESCRIPTION Access of LinScheduleEndState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_LINSCHEDULESTATE
  \DESCRIPTION Access of LinScheduleState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_LINSMSTATE
  \DESCRIPTION Access of LinSMState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_LINTPSTATE
  \DESCRIPTION Access of LinTPState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_NMSTATE
  \DESCRIPTION Access of NmState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_NVMBLOCKSTATE
  \DESCRIPTION Access of NvMBlockState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_NVMJOBSTATE
  \DESCRIPTION Access of NvMJobState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_PDURRXINDICATIONSTATE
  \DESCRIPTION Access of PduRRxIndicationState and PduRRxIndicationMapping with same index using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_BSWM_PDURRXINDICATIONSTATEIND
  \DESCRIPTION Access to PduRRxIndicationState via indirection over PduRRxIndicationMapping.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_BSWM_PDURTPRXINDICATIONSTATE
  \DESCRIPTION Access of PduRTpRxIndicationState and PduRTpRxIndicationMapping with same index using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_BSWM_PDURTPRXINDICATIONSTATEIND
  \DESCRIPTION Access to PduRTpRxIndicationState via indirection over PduRTpRxIndicationMapping.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_BSWM_PDURTPSTARTOFRECEPTIONSTATE
  \DESCRIPTION Access of PduRTpStartOfReceptionState and PduRTpStartOfReceptionMapping with same index using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_BSWM_PDURTPSTARTOFRECEPTIONSTATEIND
  \DESCRIPTION Access to PduRTpStartOfReceptionState via indirection over PduRTpStartOfReceptionMapping.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_BSWM_PDURTPTXCONFIRMATIONSTATE
  \DESCRIPTION Access of PduRTpTxConfirmationState and PduRTpTxConfirmationMapping with same index using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_BSWM_PDURTPTXCONFIRMATIONSTATEIND
  \DESCRIPTION Access to PduRTpTxConfirmationState via indirection over PduRTpTxConfirmationMapping.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_BSWM_PDURTRANSMITSTATE
  \DESCRIPTION Access of PduRTransmitState and PduRTransmitMapping with same index using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_BSWM_PDURTRANSMITSTATEIND
  \DESCRIPTION Access to PduRTransmitState via indirection over PduRTransmitMapping.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_BSWM_PDURTXCONFIRMATIONSTATE
  \DESCRIPTION Access of PduRTxConfirmationState and PduRTxConfirmationMapping with same index using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_BSWM_PDURTXCONFIRMATIONSTATEIND
  \DESCRIPTION Access to PduRTxConfirmationState via indirection over PduRTxConfirmationMapping.
  \COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_BSWM_SDCLIENTSERVICESTATE
  \DESCRIPTION Access of SdClientServiceState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_SDCONSUMEDEVENTSTATE
  \DESCRIPTION Access of SdConsumedEventState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_SDEVENTHANDLERSTATE
  \DESCRIPTION Access of SdEventHandlerState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_WDGMSTATE
  \DESCRIPTION Access of WdgMState using ComStackLib
  \COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_BSWM_RTE_READ
  \DESCRIPTION The Rte_Read_<Port> function is called with an address to a static variable
  \COUNTERMEASURE \N Write access to a static variable - address is always valid

\ID SBSW_BSWM_RTE_MODE
  \DESCRIPTION The Rte_Mode_<Port> function is called with an address to a static variable and a local variable
  \COUNTERMEASURE \N Write access to a static and a local variable - addresses are always valid

\ID SBSW_BSWM_FCTCALL_LOCALVAR
  \DESCRIPTION The function is called with an address to a local variable.
  \COUNTERMEASURE \N Write access to a local variable - address is always valid. Size is ensured through same type. No array.

\ID SBSW_BSWM_SETIPDUGROUPVECTOR
  \DESCRIPTION Access to generated table which contains function pointer
  \COUNTERMEASURE \M Size of BSWM_IPDUGROUPVECTORSIZE must be equal to the size of Com_IpduGroupVector in bytes.

\ID SBSW_BSWM_IPDUGROUPVECTORCALL
  \DESCRIPTION A Com function is called with an address of a Com_IpduGroupVector. Size of this vector is defined by Com itself
  \COUNTERMEASURE \N Write access to a local variable of same type - address is always valid

\ID SBSW_BSWM_PUSHINTOACTIONLISTPRIORITYQUEUE
  \DESCRIPTION Write access to generated array ActionListPriorityQueue
  \COUNTERMEASURE \R The DET check of the function ensures that child never exceeds the size of the array ActionListPriorityQueue.

\ID SBSW_BSWM_POPFROMACTIONLISTPRIORITYQUEUE
  \DESCRIPTION Write access to generated array ActionListPriorityQueue
  \COUNTERMEASURE \R The access on the ActionListPriorityQueue array is protected with checking the index against the variable
  BswM_LengthOfActionListPriorityQueue which represents the current length of the queue. It is verified in the function 
  BswM_PushIntoActionListQueue that the queue size can only grow until it reaches the absolut size of the array.

\ID SBSW_BSWM_OSAPPLICATIONTOBSWM
  \DESCRIPTION Write access to generated array OsApplicationToBswM
  \COUNTERMEASURE \N The access of the array is only within its bounds. The generated variable SizeOfOsApplication is generated with the exact same
                     data as the variable size itself.

SBSW_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN

\ID COV_BSWM_LOCAL
  \REASON Ensures that BSWM_LOCAL is always be set.

\ID COV_BSWM_LOCAL_INLINE
  \REASON Ensures that BSWM_LOCAL_INLINE is always be set.

\ID COV_BSWM_ECUM_COMPATIBILITY
  \ACCEPT XX
  \ACCEPT TX
  \REASON States are only available to be compatible with former AUTOSAR releases.

\ID COV_BSWM_NM_COMPATIBILITY
  \ACCEPT TX
  \REASON States are only available to be compatible with former AUTOSAR releases.

\ID COV_BSWM_ACTIONLISTBLOCKED
  \ACCEPT TF tf tx
  \REASON Action list is only blocked if configuration of rules leads to the call of the same action list.

\ID COV_BSWM_ACTIONLISTIDLE
  \ACCEPT TF tf tx
  \REASON Action list is only not idle if two rules are arbitrated which shall execute the same action list.

\ID COV_BSWM_ALLNETWORKPORTS
  \ACCEPT TX
  \REASON Configurations contains ports for all available networks. Therefore, loop is always left by break.

\ID COV_BSWM_MODEREQUESTPENDING
  \ACCEPT XF
  \REASON A mode request is only set to pending if the mode request requests itself during its arbitration.

\ID COV_BSWM_TRIGGEREDRULEEXECUTION
  \ACCEPT TX
  \REASON The pattern of triggered rules is tested centrally and must not be tested for each rule of a configuration.

\ID COV_BSWM_WHILE_1
  \REASON The condition while(1) will always return True.

\ID COV_BSWM_PART_ARRAY
  \REASON High effort to cover. Covered by review.

\ID COV_BSWM_ALL_TRUE
  \REASON Due to the configuration, this if statement is always true.

\ID COV_BSWM_INITACTIONLISTS
  \REASON Due to the configurations, there might be no InitActionLists at all. Therefore the size will be zero. The generated function is generic.

COV_JUSTIFICATION_END */

/* Justification for module-specific MISRA deviations:

 MD_BSWM_0310:
      Reason:     Only a valid address is needed, data is not accessed.
      Risk:       Access to invalid data.
      Prevention: Covered by code review and test.

 MD_BSWM_2741:
      Reason:     In certain cofigurations this statement results always in true.
      Risk:       No functional risk.
      Prevention: Covered by code review.

 MD_BSWM_2982:
      Reason:     The semaphore is locked at the beginning and released at the end of the main function. It can be interrupted by other functions.
      Risk:       No functional risk.
      Prevention: Covered by code review and comment in code.

 MD_BSWM_3200:
      Reason:     The returned value of an arbitrary user callout is not used, because it can be any configured
                  string, and such return value can not be predicted during generation of the code. 
      Risk:       Testability might become too complex.
      Prevention: Covered by code review.

 MD_BSWM_3415:
      Reason:     Generated code of Logical Expression function might contain function calls.
      Risk:       A function that should have been called, is not called.
      Prevention: Covered by generator code review.

 MD_BSWM_3449:
      Reason:     The declarations are generated and are always the same.
      Risk:       No functional risk.
      Prevention: Covered by code review.

 MD_BSWM_3451:
      Reason:     The declarations are generated and are always the same.
      Risk:       No functional risk.
      Prevention: Covered by code review.

 MD_BSWM_3673:
      Reason:     Function prototype needs to be equal to specified AUTOSAR API of calling module.
      Risk:       No functional risk.
      Prevention: Covered by code review.

*/

/**********************************************************************************************************************
 *  END OF FILE: BswM.c
 *********************************************************************************************************************/
