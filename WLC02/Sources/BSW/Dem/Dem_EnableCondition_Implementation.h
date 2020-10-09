/* ********************************************************************************************************************
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
 *  -------------------------------------------------------------------------------------------------------------------
 */
/*! \addtogroup Dem_EnableCondition
 *  \{
 *  \file       Dem_EnableCondition_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the EnableCondition subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Savas Ates                    vissat        Vector Informatik GmbH
 *  Anna Bosch                    visanh        Vector Informatik GmbH
 *  Stefan Huebner                vishrs        Vector Informatik GmbH
 *  Thomas Dedler                 visdth        Vector Informatik GmbH
 *  Alexander Ditte               visade        Vector Informatik GmbH
 *  Matthias Heil                 vismhe        Vector Informatik GmbH
 *  Erik Jeglorz                  visejz        Vector Informatik GmbH
 *  Friederike Hitzler            visfrs        Vector Informatik GmbH
 *  Aswin Vijayamohanan Nair      visavi        Vector Informatik GmbH
 *  Fabian Wild                   viszfa        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_ENABLECONDITION_IMPLEMENTATION_H)
#define DEM_ENABLECONDITION_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_EnableCondition_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg_Definitions.h"
#include "Dem_Scheduler_Implementation.h"
#include "Dem_EventInternalStatus_Implementation.h"
#include "Dem_Error_Implementation.h"
#include "Dem_Notifications_Implementation.h"
#include "Dem_MemCopy.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Event_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_EnableCondition_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_EnableCondition_GetGlobalEnableConditionCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetGlobalEnableConditionCount(
  void
  )
{
  return DEM_CFG_GLOBAL_ENABLE_COND_COUNT;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_EnableCondition_Private
 * \{
 */

/* ****************************************************************************
 % Dem_EnableCondition_GetGlobalEnableConditionGroupCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetGlobalEnableConditionGroupCount(
  void
  )
{
  return (uint8)Dem_Cfg_GetSizeOfEnableConditionGroupTable();
}

/* ****************************************************************************
 % Dem_EnableCondition_GetEnableConditionInitValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetEnableConditionInitValue(
  CONST(uint8, AUTOMATIC) EnableCondition
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EnableCondition)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetInitValueOfEnableConditionInitTable(EnableCondition);
}

#if ((DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON) \
    ||((DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) && (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF)))
/* ****************************************************************************
 % Dem_EnableCondition_GetEnableConditionActive
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_GetEnableConditionActive(
  CONST(uint8, AUTOMATIC)  EnableCondition
  )
{
  return Dem_Cfg_GetEnableConditionState(EnableCondition);
}
#endif

/* ****************************************************************************
 % Dem_EnableCondition_GetEventEnableConditionGroup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EnableCondition_GetEventEnableConditionGroup(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
    return (uint8)(Dem_Cfg_GetEnableConditionGroupTableIdxOfEventTable(EventId));
#else
    return DEM_ENABLECONDITION_CONTROLDTCSETTING;
#endif
}

/* ****************************************************************************
 % Dem_EnableCondition_GetEnableConditionGroupState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetEnableConditionGroupState(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup
  )
{
  return Dem_Cfg_GetEnableConditionGroupState(EnableConditionGroup);
}

/* ****************************************************************************
 % Dem_EnableCondition_GetEnableConditionGroupCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetEnableConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup
  )
{
  return Dem_Cfg_GetEnableConditionGroupCounter(EnableConditionGroup);
}

/* ****************************************************************************
 % Dem_EnableCondition_SetEnableConditionActive
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionActive(
  CONST(uint8, AUTOMATIC)  EnableCondition,
  CONST(boolean, AUTOMATIC)  ActiveStatus
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (EnableCondition >= Dem_Cfg_GetSizeOfEnableConditionState())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_SetEnableConditionState(EnableCondition, ActiveStatus);                                                              /* SBSW_DEM_ARRAY_WRITE_ENABLECONDITIONSTATE */
  }
}

/* ****************************************************************************
 % Dem_EnableCondition_SetEnableConditionGroupState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionGroupState(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup,
  CONST(uint8, AUTOMATIC)  State
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (EnableConditionGroup >= Dem_Cfg_GetSizeOfEnableConditionGroupState())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_SetEnableConditionGroupState(EnableConditionGroup, State);                                                           /* SBSW_DEM_ARRAY_WRITE_ENABLECONDITIONGROUPSTATE */
  }
}

/* ****************************************************************************
 % Dem_EnableCondition_SetEnableConditionGroupCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup,
  CONST(uint8, AUTOMATIC)  Counter
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (EnableConditionGroup >= Dem_Cfg_GetSizeOfEnableConditionGroupCounter())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_SetEnableConditionGroupCounter(EnableConditionGroup, Counter);                                                       /* SBSW_DEM_ARRAY_WRITE_ENABLECONDITIONGROUPCOUNTER */
  }
}

/* ****************************************************************************
 % Dem_EnableCondition_ProcessQueueEventEnableConditions
 *****************************************************************************/
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
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_ProcessQueueEventEnableConditions(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint16 lEnableConditionGroup;
  uint8 lGroupState;

  lEnableConditionGroup = Dem_EnableCondition_GetEventEnableConditionGroup(EventId);
  lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);

  /* Reset/Freeze debouncing on enable condition state change unlocked -> locked */
  if (DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_PROCESS_DISABLE(lGroupState))
  {
    if (Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) == 1)
    {
      /* Enable conditions become disabled.
       * If DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS:
       * If the event is configured to freeze and not continue, or will not continue counting at all: freeze it
       * If DEM_CFG_RESET_DEBOUNCE_ON_DISABLE_ENABLE_CONDITIONS:
       * If the event is configured to freeze: freeze it
       * Otherwise: reset it
       */
#if (DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS == STD_ON)
      if (Dem_Cfg_EventDebounceContinuous(EventId) == FALSE)
      {
        Dem_SatelliteCore_FreezeDebounceStatus(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));
      }
#endif
#if (DEM_CFG_RESET_DEBOUNCE_ON_DISABLE_ENABLE_CONDITIONS == STD_ON)
      if (Dem_Cfg_EventDebounceReset(EventId) == FALSE)
      {
        Dem_SatelliteCore_FreezeDebounceStatus(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));
      }
      else
      {
        Dem_SatelliteCore_ResetDebounceStatus(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));

      }
#endif
    }
  }


#if ( (DEM_CFG_NOTIFY_ENABLECONDITION == STD_ON) \
   || (DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS == STD_ON) )
  if (DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_PROCESS_ENABLE(lGroupState))
  {
    if (Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) == 0)
    {
      /* 
       * If the event is configured to reset, and the global setting is to reset on enable EC:
       *   -Reset the debouncing
       * If the event is configured to freeze, and the global setting is to freeze on enable EC:
       *   -Freeze the debouncing
       * Call InitMonitor for event/function:
       * If any are configured
       */
# if (DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS == STD_ON)
      if (Dem_Cfg_EventDebounceReset(EventId) == TRUE)
      {
        Dem_SatelliteCore_ResetDebounceStatus(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));
      }
      else
      {
        if(Dem_Cfg_EventDebounceContinuous(EventId) == TRUE)
        {
          Dem_SatelliteCore_FreezeDebounceStatus(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));
        }
      }
# endif
      Dem_Notifications_InitMonitorForEvent(EventId, DEM_INIT_MONITOR_REENABLED);
      Dem_Notifications_InitMonitorForFunction(EventId);
    }
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


/* ****************************************************************************
 % Dem_EnableCondition_GroupIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_GroupIterExists(
  CONSTP2CONST(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}


/* ****************************************************************************
 % Dem_EnableCondition_GroupIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EnableCondition_GroupIterGet(
  CONSTP2CONST(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetEnableConditionGroupTableInd(IterPtr->mIdx);
}

/* ****************************************************************************
 % Dem_EnableCondition_GroupIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_GroupIterInit(
  CONST(uint8, AUTOMATIC)  EnableCondition,                                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                            /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_False */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EnableCondition)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx = Dem_Cfg_GetEnableConditionGroupTableIndStartIdxOfEnableConditionTable(EnableCondition);                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetEnableConditionGroupTableIndEndIdxOfEnableConditionTable(EnableCondition);                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_EnableCondition_GroupIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_GroupIterNext(
  CONSTP2VAR(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                                            /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_False */
  )
{
  IterPtr->mIdx += 1;                                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
} 

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_EnableCondition_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_EnableCondition_SetEnableConditionFulfilled
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_EnableCondition_SetEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableCondition
  )
{
  boolean lEnableConditionGroupStatePending;

  lEnableConditionGroupStatePending = FALSE;

  /* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */

  if (Dem_EnableCondition_GetEnableConditionActive(EnableCondition) == FALSE)
  {
    Dem_Cfg_EventEnableConditionGroupIterType lEnableConditionIter;
    for (Dem_EnableCondition_GroupIterInit(EnableCondition, &lEnableConditionIter);                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_EnableCondition_GroupIterExists(&lEnableConditionIter) == TRUE;                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_EnableCondition_GroupIterNext(&lEnableConditionIter))                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint16 lEnableConditionGroup;
      uint8 lGroupState;

      lEnableConditionGroup = Dem_EnableCondition_GroupIterGet(&lEnableConditionIter);                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
      if (Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) > 0)
# endif
      {
        Dem_EnableCondition_SetEnableConditionGroupCounter(lEnableConditionGroup,
          (uint8)(Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) - 1));
      }

      lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);
      lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_QUEUE_ENABLE(lGroupState);
      Dem_EnableCondition_SetEnableConditionGroupState(lEnableConditionGroup, lGroupState);
      lEnableConditionGroupStatePending = TRUE;
    }
    Dem_EnableCondition_SetEnableConditionActive(EnableCondition, TRUE);
  }

  Dem_LeaveCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* <<<< -------------------------------- Leave Critical Section: StateManager */

  if (lEnableConditionGroupStatePending == TRUE)
  {
    Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_EnableCondition);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_EnableCondition_ResetEnableConditionFulfilled
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_ResetEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableCondition
  )
{
  boolean lEnableConditionGroupStatePending;

  lEnableConditionGroupStatePending = FALSE;

  /* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */

  if (Dem_EnableCondition_GetEnableConditionActive(EnableCondition) == TRUE)
  {
    Dem_Cfg_EventEnableConditionGroupIterType lEnableConditionIter;
    for (Dem_EnableCondition_GroupIterInit(EnableCondition, &lEnableConditionIter);                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_EnableCondition_GroupIterExists(&lEnableConditionIter) == TRUE;                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_EnableCondition_GroupIterNext(&lEnableConditionIter))                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint16 lEnableConditionGroup;
      uint8 lGroupState;

      lEnableConditionGroup = Dem_EnableCondition_GroupIterGet(&lEnableConditionIter);                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_EnableCondition_SetEnableConditionGroupCounter(lEnableConditionGroup, 
        (uint8)(Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) + 1));

      lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);
      lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_ACTIVE(lGroupState);
      lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_QUEUE_DISABLE(lGroupState);
      lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_QUEUE_ENABLE(lGroupState);
      Dem_EnableCondition_SetEnableConditionGroupState(lEnableConditionGroup, lGroupState);

      lEnableConditionGroupStatePending = TRUE;
    }
    Dem_EnableCondition_SetEnableConditionActive(EnableCondition, FALSE);
  }

  Dem_LeaveCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* <<<< -------------------------------- Leave Critical Section: StateManager */

  if (lEnableConditionGroupStatePending == TRUE)
  {
    Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_EnableCondition);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_EnableCondition_MainFunction
 *****************************************************************************/
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
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_MainFunction(
  void
  )
{
  Dem_EventIdType lEventId;
  uint8 lEnableConditionGroup;

  /* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */

  for (lEnableConditionGroup = 0; 
       lEnableConditionGroup < Dem_EnableCondition_GetGlobalEnableConditionGroupCount();
       ++lEnableConditionGroup)
  {
    uint8 lGroupState;
    lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);
    if (DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_QUEUE_DISABLE(lGroupState))
    {
      lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_PROCESS_DISABLE(lGroupState);
      lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_QUEUE_DISABLE(lGroupState);
    }
    if (DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_QUEUE_ENABLE(lGroupState))
    {
      lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_PROCESS_ENABLE(lGroupState);
      lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_QUEUE_ENABLE(lGroupState);
    }
    Dem_EnableCondition_SetEnableConditionGroupState(lEnableConditionGroup, lGroupState);
  }

  Dem_LeaveCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* <<<< -------------------------------- Leave Critical Section: StateManager */

  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  {
    if (Dem_Cfg_EventAvailableByVariant(lEventId) == TRUE)
    {
      if (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lEventId)) == FALSE)
      {
        /* Process enable condition groups for every event */
        Dem_EnableCondition_ProcessQueueEventEnableConditions(lEventId);
      }
    }
  }

  /* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* Remove process flags from group state of all enable condition groups */
  for (lEnableConditionGroup = 0; 
       lEnableConditionGroup < Dem_EnableCondition_GetGlobalEnableConditionGroupCount(); 
       ++lEnableConditionGroup)
  {
    uint8 lGroupState;
    lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);
    if (DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_PROCESS_ENABLE(lGroupState))
    {
      if (Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) == 0)
      {
        lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_ACTIVE(lGroupState);
      }
    }
    lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_PROCESS_DISABLE(lGroupState);
    lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_PROCESS_ENABLE(lGroupState);
    Dem_EnableCondition_SetEnableConditionGroupState(lEnableConditionGroup, lGroupState);
  }

  Dem_LeaveCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* <<<< -------------------------------- Leave Critical Section: StateManager */
}                                                                                                                                /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_EnableCondition_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_Init(
  void
  )
{
  uint8 lGroupState;
  uint8 lEnableCondition;
  /* Initialize enable condition group counter and set enable condition group state active */
  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetEnableConditionGroupCounter(0),                                                        /* PRQA S 0310, 0312, 0602, 3109 */ /* MD_DEM_11.4_cpy, MD_DEM_11.5, MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_MEMSET_ENABLECONDITIONGROUPCOUNTER */
    0,
    Dem_Cfg_GetSizeOfEnableConditionGroupCounter() * sizeof(Dem_Cfg_GetEnableConditionGroupCounter(0)));

  lGroupState = 0;
  lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_ACTIVE(lGroupState);

  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetEnableConditionGroupState(0),                                                          /* PRQA S 0310, 0312, 0602, 3109 */ /* MD_DEM_11.4_cpy, MD_DEM_11.5, MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_MEMSET_ENABLECONDITIONGROUPSTATE */
    lGroupState,
    Dem_Cfg_GetSizeOfEnableConditionGroupState() * sizeof(Dem_Cfg_GetEnableConditionGroupState(0)));

  for (lEnableCondition = 0; 
       lEnableCondition < Dem_EnableCondition_GetGlobalEnableConditionCount();
       ++lEnableCondition)
  {
    uint8 lEnableConditionInitState;
    Dem_Cfg_EventEnableConditionGroupIterType lEnableConditionIter;

    lEnableConditionInitState = Dem_EnableCondition_GetEnableConditionInitValue(lEnableCondition);

    if (lEnableConditionInitState == FALSE)
    {
      for (Dem_EnableCondition_GroupIterInit(lEnableCondition, &lEnableConditionIter);                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_EnableCondition_GroupIterExists(&lEnableConditionIter) == TRUE;                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_EnableCondition_GroupIterNext(&lEnableConditionIter))                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        uint16 lEnableConditionGroup;

        lEnableConditionGroup = Dem_EnableCondition_GroupIterGet(&lEnableConditionIter);                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_EnableCondition_SetEnableConditionGroupCounter(lEnableConditionGroup, 
          (uint8)(Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup) + 1));

        lGroupState = DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_ACTIVE
                      (Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup));
        Dem_EnableCondition_SetEnableConditionGroupState(lEnableConditionGroup, lGroupState);
      }
    }
    Dem_EnableCondition_SetEnableConditionActive(lEnableCondition, lEnableConditionInitState);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_EnableCondition_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_PreInit(
  void
  )
{
  uint8 lGroupState;

  /* Initialize enable and storage conditions (all enabled due to init phase) */
  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetEnableConditionState(0),                                                               /* PRQA S 0310, 0312, 0602, 3109 */ /* MD_DEM_11.4_cpy, MD_DEM_11.5, MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_MEMSET_ENABLECONDITIONSTATE */
    TRUE,
    Dem_Cfg_GetSizeOfEnableConditionState()*sizeof(Dem_Cfg_GetEnableConditionState(0)));

  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetEnableConditionGroupCounter(0),                                                        /* PRQA S 0310, 0312, 0602, 3109 */ /* MD_DEM_11.4_cpy, MD_DEM_11.5, MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_MEMSET_ENABLECONDITIONGROUPCOUNTER */
    0,
    Dem_Cfg_GetSizeOfEnableConditionGroupCounter()*sizeof(Dem_Cfg_GetEnableConditionGroupCounter(0)));

  lGroupState = 0;
  lGroupState = DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_ACTIVE(lGroupState);

  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetEnableConditionGroupState(0),                                                          /* PRQA S 0310, 0312, 0602, 3109 */ /* MD_DEM_11.4_cpy, MD_DEM_11.5, MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_MEMSET_ENABLECONDITIONGROUPSTATE */
    lGroupState,
    Dem_Cfg_GetSizeOfEnableConditionGroupState()*sizeof(Dem_Cfg_GetEnableConditionGroupState(0)));
} 

/* ****************************************************************************
 % Dem_EnableCondition_TestEventEnableConditionsFulfilled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_TestEventEnableConditionsFulfilled(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint16 lEnableConditionGroup;
  uint8 lGroupState;

  lEnableConditionGroup = Dem_EnableCondition_GetEventEnableConditionGroup(EventId);
  lGroupState = Dem_EnableCondition_GetEnableConditionGroupState(lEnableConditionGroup);

  return (boolean)DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_ACTIVE(lGroupState);
}                                                                                                                              

#if ((DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) \
     ||((DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) && (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF)))
/* ****************************************************************************
 % Dem_EnableCondition_TestEnableConditionFulfilled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_EnableCondition_TestEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableCondition
  )
{
  return Dem_EnableCondition_GetEnableConditionActive(EnableCondition);
}
#endif

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_EnableCondition_TestEventProcessingPrecondition
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_TestEventProcessingPrecondition(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint16 lEnableConditionGroup;
  uint8 lCounter;
  boolean ConditionFulfilled;

  ConditionFulfilled = FALSE;
  lEnableConditionGroup = Dem_EnableCondition_GetEventEnableConditionGroup(EventId);
  lCounter = Dem_EnableCondition_GetEnableConditionGroupCounter(lEnableConditionGroup);

  /* all enable conditions fulfilled*/
  if (lCounter == 0)
  {
    ConditionFulfilled = TRUE;
  }
  /* all enable conditions fulfilled except of ControlDTCSetting */
  else if ((Dem_EnableCondition_TestEnableConditionFulfilled(DEM_ENABLECONDITION_CONTROLDTCSETTING) == FALSE)
            && (lCounter == 1))
  {
    ConditionFulfilled = TRUE;
  }
  else
  {
     /* MISRA */
  }

  return ConditionFulfilled;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_ENABLECONDITION_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EnableCondition_Implementation.h
 *********************************************************************************************************************/
