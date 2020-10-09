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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_EnableCondition Enable Condition
 *  \{
 *  \file       Dem_EnableCondition_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the EnableCondition subcomponent
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

#if !defined (DEM_ENABLECONDITION_INTERFACE_H)
#define DEM_ENABLECONDITION_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_EnableCondition_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_EnableCondition_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_EnableCondition_GetGlobalEnableConditionCount
 *****************************************************************************/
/*!
 * \brief         Get the number of configured enable conditions
 *
 * \details       Get the number of configured enable conditions
 *
 * \return        The number of configured enable conditions
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetGlobalEnableConditionCount(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_EnableCondition_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_EnableCondition_GetGlobalEnableConditionGroupCount
 *****************************************************************************/
/*!
 * \brief         Get the number of configured enable condition groups
 *
 * \details       Get the number of configured enable condition groups
 *
 * \return        The number of configured enable condition groups
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetGlobalEnableConditionGroupCount(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_EnableCondition_GetEnableConditionInitValue
 *****************************************************************************/
/*!
 * \brief         Get the initial value of enable condition
 *
 * \details       Get the initial value of enable condition
 *
 * \param[in]     EnableCondition
 *                Unique handle of the enable condition.
 *
 * \return        The initial value of enable condition
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetEnableConditionInitValue(
  CONST(uint8, AUTOMATIC) EnableCondition
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

#if ((DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON) \
    ||((DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) && (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF)))
/* ****************************************************************************
 * Dem_EnableCondition_GetEnableConditionActive
 *****************************************************************************/
/*!
 * \brief         Get current activation state of enable condition
 *
 * \details       Get current activation state of enable condition
 *
 * \param[in]     EnableCondition
 *                Unique handle of the enable condition
 *
 * \return        The activation state of enable condition
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON) \
 *                ||( (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) \
 *                    &&(DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF) )
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_GetEnableConditionActive(
  CONST(uint8, AUTOMATIC)  EnableCondition
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

/* ****************************************************************************
 * Dem_EnableCondition_GetEventEnableConditionGroup
 *****************************************************************************/
/*!
 * \brief         Get the enable condition group for an event
 *
 * \details       Get the enable condition group for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()].
 *
 * \return        Enable condition group for the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EnableCondition_GetEventEnableConditionGroup(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_EnableCondition_GetEnableConditionGroupState
 *****************************************************************************/
/*!
 * \brief         Get current internal state of enable condition group
 *
 * \details       Get current internal state of enable condition group
 *
 * \param[in]     EnableConditionGroup
 *                Unique handle of the enable condition group
 *
 * \return        Current activation state of the enable condition group
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetEnableConditionGroupState(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_EnableCondition_GetEnableConditionGroupCounter
 *****************************************************************************/
/*!
 * \brief         Get current internal counter of enable condition group
 *
 * \details       Get current internal counter of enable condition group
 *
 * \param[in]     EnableConditionGroup
 *                Unique handle of the enable condition group
 *
 * \return        Current number of enable conditions currently disabling the 
 *                group.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EnableCondition_GetEnableConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_EnableCondition_SetEnableConditionActive
 *****************************************************************************/
/*!
 * \brief         Set current activation status of enable condition
 *
 * \details       Set current activation status of enable condition
 *
 * \param[in]     EnableCondition
 *                Unique handle of the enable condition
 * \param[in]     ActiveStatus
 *                New activation state of the enable condition
 *
 * \pre           -
 * 
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionActive(
  CONST(uint8, AUTOMATIC)  EnableCondition,
  CONST(boolean, AUTOMATIC)  ActiveStatus
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_EnableCondition_SetEnableConditionGroupState
 *****************************************************************************/
/*!
 * \brief         Set current internal state of enable condition group
 *
 * \details       Set current internal state of enable condition group
 *
 * \param[in]     EnableConditionGroup
 *                Unique handle of the enable condition group
 * \param[in]     State
 *                New internal state of the enable condition group
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionGroupState(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup,
  CONST(uint8, AUTOMATIC)  State
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_EnableCondition_SetEnableConditionGroupCounter
 *****************************************************************************/
/*!
 * \brief         Set current internal counter of enable condition group
 *
 * \details       Set current internal counter of enable condition group
 *
 * \param[in]     EnableConditionGroup
 *                 Unique handle of the enable condition group
 * \param[in]     Counter
 *                New internal counter of the enable condition group
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  EnableConditionGroup,
  CONST(uint8, AUTOMATIC)  Counter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_EnableCondition_ProcessQueueEventEnableConditions
 *****************************************************************************/
/*!
 * \brief         Processes changes of enable condition states
 *
 * \details       This function resets or freezes debouncing of an event, based
 *                on the changes of the enable condition states since this
 *                function was called last. When the event is re-enabled, this
 *                function also calls the init monitor notifications.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_ProcessQueueEventEnableConditions(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                      

/* ****************************************************************************
 * Dem_EnableCondition_GroupIterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 * 
 * \return        TRUE
 *                Dem_EnableCondition_GroupIterGet() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_EnableCondition_GroupIterGet() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_GroupIterExists(
  CONSTP2CONST(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_EnableCondition_GroupIterGet
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Handle to Enable condition group descriptor table
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EnableCondition_GroupIterGet(
  CONSTP2CONST(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_EnableCondition_GroupIterInit
 *****************************************************************************/
/*!
 * \brief         Init the iterator
 *
 * \details       Initializes the iterator to enumerate enable condition groups
 *                referencing given enable condition
 *
 * \param[in]     EnableCondition
 *                Unique handle of the enable condition.
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_GroupIterInit(
  CONST(uint8, AUTOMATIC)  EnableCondition,
  CONSTP2VAR(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_EnableCondition_GroupIterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_GroupIterNext(
  CONSTP2VAR(Dem_Cfg_EventEnableConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_EnableCondition_Public Public Methods
 * \{
 */


#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_EnableCondition_SetEnableConditionFulfilled
 *****************************************************************************/
/*!
 * \brief         Sets the enable condition
 *
 * \details       Sets the enable condition
 *
 * \param[in]     EnableCondition
 *                Unique handle of the enable condition.
 *                The EnableCondition must be in range [0..Dem_EnableCondition_GetGlobalEnableConditionCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON ||
 *                DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_SetEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableCondition
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_EnableCondition_ResetEnableConditionFulfilled
 *****************************************************************************/
/*!
 * \brief         Clears the enable condition
 *
 * \details       Clears the enable condition
 *
 * \param[in]     EnableCondition
 *                Unique handle of the enable condition.
 *                The EnableCondition must be in range [0..Dem_EnableCondition_GetGlobalEnableConditionCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON ||
 *                DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_ResetEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableCondition
  );
#endif

/* ****************************************************************************
 * Dem_EnableCondition_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process enable condition changes
 *
 * \details       This function processes changes of the enable conditions for
 *                all events.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_EnableCondition_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the enable conditions and enable condition groups
 *
 * \details       Initializes the enable conditions and enable condition groups
 *
 * \pre           May only be called during Dem initialization
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_Init(
  void
  );

/* ****************************************************************************
 * Dem_EnableCondition_PreInit
 *****************************************************************************/
/*!
 * \brief         Enables all enable conditions
 *
 * \details       Enables all enable conditions
 *
 * \pre           May only be called during Dem preinitialization
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EnableCondition_PreInit(
  void
  );    

#if ((DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) \
    ||((DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) \
      && (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF)))
/* ****************************************************************************
 * Dem_EnableCondition_TestEnableConditionFulfilled
 *****************************************************************************/
/*!
 * \brief         Retrieves activation state of an enable condition
 *
 * \details       This function retrieves activation state of an enable condition
 *
 * \param[in]     EnableCondition
 *                Unique handle of the enable condition.
 *                The EnableCondition must be in range [0..Dem_EnableCondition_GetGlobalEnableConditionCount()[.
 *
 * \return        TRUE
 *                The enable condition is fulfilled
 *                FALSE
 *                The enable condition is not fulfilled
 *
 * \pre           -
 * \config        ((DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) \
 *                ||((DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) \
 *                  && (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF))
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_EnableCondition_TestEnableConditionFulfilled(
  CONST(uint8, AUTOMATIC)  EnableCondition
  );
#endif

/* ****************************************************************************
 * Dem_EnableCondition_TestEventEnableConditionsFulfilled
 *****************************************************************************/
/*!
 * \brief         Tests whether the enable conditions are fulfilled for an event
 *
 * \details       Tests whether the enable conditions are fulfilled for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [0..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The enable conditions are fulfilled
 * \return        FALSE
 *                The enable conditions are not fulfilled
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_TestEventEnableConditionsFulfilled(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_EnableCondition_TestEventProcessingPrecondition
 *****************************************************************************/
/*!
 * \brief         Tests if enable condition blocks event processing
 *
 * \details       Test if the current enable condition state blocks
 *                the processing of an event, ignoring enable condition 
 *                'control DTC setting' .
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [0..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Event processing preconditions fulfilled
 * \return        FALSE
 *                Event processing preconditions are not fulfilled
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EnableCondition_TestEventProcessingPrecondition(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_ENABLECONDITION_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EnableCondition_Interface.h
 *********************************************************************************************************************/
