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
 *  \defgroup   Dem_OperationCycle OperationCycle
 *  \{
 *  \file       Dem_OperationCycle_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    
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

#if !defined (DEM_OPERATIONCYCLE_INTERFACE_H)
#define DEM_OPERATIONCYCLE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_OperationCycle_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_OperationCycle_Properties Properties
 * \{
 */
/* ****************************************************************************
 * Dem_OperationCycle_GetCurrentCycleStatus
 *****************************************************************************/
/*!
 * \brief         Gets the current state of a cycle.
 *
 * \details       Gets the current state of a cycle.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \return        DEM_OPERATIONCYCLE_CYCLE_STARTED
 *                The cycle is currently started
 * \return        DEM_OPERATIONCYCLE_CYCLE_STOPPED
 *                The cycle is currently stopped
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_OperationCycle_GetCurrentCycleStatus(
  CONST(uint8, AUTOMATIC)  CycleId
  );

/* ****************************************************************************
 * Dem_OperationCycle_SetCycleStatus
 *****************************************************************************/
/*!
 * \brief         Set current state of a cycle.
 *
 * \details       Set current state of a cycle.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     Status
 *                The state of the cycle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetCycleStatus(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  Status
  );

/* ****************************************************************************
 * Dem_OperationCycle_GetCycleCounter
 *****************************************************************************/
/*!
 * \brief         Get current counter of the cycle
 *
 * \details       Get current counter of the cycle
 *
 * \param[in]     CycleId
 *                Unique handle of the cycle
 *
 * \return        Current counter of the cycle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_OperationCycle_GetCycleCounter(
  CONST(uint8, AUTOMATIC) CycleId
  );

/* ****************************************************************************
 * Dem_OperationCycle_SetCycleCounter
 *****************************************************************************/
/*!
 * \brief         Set current counter value of the cycle
 *
 * \details       Set current counter value of the cycle
 *
 * \param[in]     CycleId
 *                Unique handle of the cycle
 * \param[in]     CycleCounter
 *                New counter value of the cycle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetCycleCounter(
  CONST(uint8, AUTOMATIC) CycleId,
  CONST(uint16, AUTOMATIC) CycleCounter
  );

/* ****************************************************************************
 * Dem_OperationCycle_AddCycleCount
 *****************************************************************************/
/*!
 * \brief         Calculates wrapped cycle counter
 *
 * \details       This function increments and wraps a cycle count avoiding
 *                overflow and 'magic numbers'.
 *
 * \param[in]     CurrentCounter
 *                Current value of the cycle counter
 * \param[in]     DeltaValue
 *                Value by which CurrentCounter is incremented.
 *
 * \return        Value of (CurrentCounter + DeltaValue) mod X
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_OperationCycle_AddCycleCount(
  CONST(uint16, AUTOMATIC)  CurrentCounter,
  CONST(uint8, AUTOMATIC)  DeltaValue
  );

#if (DEM_FEATURE_NEED_AGING_CYCLE_DISTANCE == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_CycleCountDistance
 *****************************************************************************/
/*!
 * \brief         Calculates the distance between cycle counter values
 *
 * \details       Calculates the distance between cycle counter values
 *
 * \param[in]     CurrentCounter
 *                Current value of the cycle counter
 * \param[in]     TargetCounter
 *                Target counter value to find the distance to
 *
 * \return        Number of increments until current counter reaches target
 *                counter
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_AGING_CYCLE_DISTANCE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_OperationCycle_CycleCountDistance(
  CONST(uint16, AUTOMATIC)  CurrentCounter,
  CONST(uint16, AUTOMATIC)  TargetCounter
  );
#endif

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
 * \defgroup Dem_OperationCycle_Private Private Methods
 * \{
 */
/* ****************************************************************************
 * Dem_OperationCycle_GetPendingCycle
 *****************************************************************************/
/*!
 * \brief         Looks up a pending cycle state change
 *
 * \details       This function looks up a pending cycle state change.
 *                The value returned is only meaningful if the modification
 *                flag is also set for this cycle
 *                (see Dem_OperationCycle_CycleFlag).
 *
 * \param[in]     CycleId
 *                Unique handle of the Cycle.
 *
 * \return        DEM_OPERATIONCYCLE_CYCLE_STARTED
 *                Cycle state change to start is pending
 * \return        DEM_OPERATIONCYCLE_CYCLE_STOPPED
 *                Cycle state change to stop is pending
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_OperationCycle_GetPendingCycle(
  CONST(uint8, AUTOMATIC)  CycleId
  );

/* ****************************************************************************
 * Dem_OperationCycle_SetPendingCycle
 *****************************************************************************/
/*!
 * \brief         Stores a pending cycle state change
 *
 * \details       This function stores a pending cycle state change to be
 *                processed later on task context.
 *
 *                The queue can encode one STOP, one START or one STOP->START
 *                action. The modification flag (see
 *                Dem_OperationCycle_CycleFlag) is set always.
 *
 * \param[in]     CycleId
 *                Unique handle of the Cycle.
 * \param[in]     Status
 *                DEM_OPERATIONCYCLE_CYCLE_STARTED  To start a cycle
 *                DEM_OPERATIONCYCLE_CYCLE_STOPPED  To stop a cycle
 *
 * \pre           Must be called within critical section 'StateManager'
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetPendingCycle(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  Status
  );

#if (DEM_FEATURE_NEED_OBD == STD_ON)    
/* ****************************************************************************
 * Dem_OperationCycle_QualifyDcy_IgnCycleCounter
 *****************************************************************************/
/*!
 * \brief         Proccesses ignition cycle counter
 *
 * \details       Increments ignition cycle counter if conditions are fulfilled
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_QualifyDcy_IgnCycleCounter(
  void
  );
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_QualifyDcy
 *****************************************************************************/
/*!
 * \brief         Qualifies the OBD driving cycle
 *
 * \details       When the driving cycle is qualified, the environmental data,
 *                ConfirmedDTC bit and WIR bit become visible for external
 *                testers and the application.
 *
 *                If the ConfirmedDTC bit qualifies of an event holding the OBD
 *                FreezeFrame, the FreezeFrame becomes visible as well.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_QualifyDcy(
  void
  );
#endif

/* ****************************************************************************
 * Dem_OperationCycle_ProcessCycles
 *****************************************************************************/
/*!
 * \brief         Process all queued operation cycles
 *
 * \details       The function processes cycle management for aging and
 *                operation cycle management (readiness bits etc)
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ProcessCycles(
  void
  );

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_ProcessCycleUpdate_AllEvents
 *****************************************************************************/
/*!
 * \brief         Processes cycle update for all events
 *
 * \details       This function invokes functions to recalculate the aging cycle 
 *                counter threshold for all events. Also invokes the 
 *                functions for re-calculation of operation cycle counter
 *                latching.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     CycleCounter
 *                Current cycle count
 *
 * \pre           Cycle counter has already been incremented for the cycle
 * \config        (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ProcessCycleUpdate_AllEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ((DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF) \
     && ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) || (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)))
/* ****************************************************************************
 * Dem_OperationCycle_ProcessCycleUpdate_StoredEvents
 *****************************************************************************/
/*!
 * \brief         Processes cycle update for stored entries
 *
 * \details       This function recalculates the aging cycle 
 *                counter threshold and operation cycle counter latching
*                 for stored events. 
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     CycleCounter
 *                Current cycle count
 *
 * \pre           Cycle counter has already been incremented for the cycle
 * \config        ((DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF)
 *                  && ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) 
                        || (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)))
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ProcessCycleUpdate_StoredEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_RecalculateAgingThreshold_AllEvents
 *****************************************************************************/
/*!
 * \brief         Function recalculates the aging counter threshold
 *
 * \details       This function recalculates the aging counter threshold for
 *                all master events which are either confirmed or stored in 
 *                memory based on the status. If the aging
 *                threshold for the event is reached, it is aged.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     CycleCounter
 *                Current cycle count
 *
 * \pre           Cycle counter has already been incremented for the cycle
 * \config        DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_RecalculateAgingThreshold_AllEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  );
#endif

#if ((DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON) && (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON))
/* ****************************************************************************
 * Dem_OperationCycle_LatchCycleCounters
 *****************************************************************************/
/*!
 * \brief         Processes latching for cycle counters
 *
 * \details       This function iterates through all the memory 
 *                entries and latches the operation cycle counters if required.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     CycleCounter
 *                Current cycle count
 *
 * \pre           Cycle counter has already been incremented for the cycle
 * \config        (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON) 
 *                 && (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_LatchCycleCounters(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  );
#endif

/* ****************************************************************************
 * Dem_OperationCycle_UpdateTestEventAffected
 *****************************************************************************/
/*!
 * \brief         Checks if passed event is affected by cycle update
 *
 * \details       Checks if passed event is affected by cycle update
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \return        FALSE
 *                - CycleId does not match operation cycle of event.
 *                - Event is unavailable.
 *                - For combined events: event is not the master event.
 * \return        TRUE
 *                - Otherwise.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_OperationCycle_UpdateTestEventAffected(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleId
  );

/* ****************************************************************************
 * Dem_OperationCycle_UpdateProcessEvent
 *****************************************************************************/
/*!
 * \brief         Processes the operation cycle update for the passed event
 *
 * \details       Updates status and stored entry for the passed event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateProcessEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );

/* ****************************************************************************
 * Dem_OperationCycle_CycleUpdateReadiness
 *****************************************************************************/
/*!
 * \brief         Processes operation cycle updates
 *
 * \details       This function processes the operation cycle updates for all
 *                events using that cycle as operation cycle.
 *
 *                Since operation cycles can restart or only stop/start, the
 *                cycle status can be one of DEM_OPERATIONCYCLE_CYCLE_STARTED,
 *                DEM_OPERATIONCYCLE_CYCLE_STOPPED or
 *                DEM_OPERATIONCYCLE_CYCLE_RESTARTED (most other APIs only
 *                accept the first two states).
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdateReadiness(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_UpdateObdDcy_End
 *****************************************************************************/
/*!
 * \brief         Processes driving cycle updates at stop trigger
 *
 * \details       This function processes the OBD driving cycle specific state
 *                transitions.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON ||
 *                DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdDcy_End(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_UpdateObdWarmup_End
 *****************************************************************************/
/*!
 * \brief         Processes warmup cycle updates at stop trigger
 *
 * \details       This function processes the warm-up cycle specific state
 *                transitions. This does not include aging, as aging is handled
 *                generically.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdWarmup_End(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_UpdateObdDcy_Start
 *****************************************************************************/
/*!
 * \brief         Processes driving cycle updates at start trigger
 *
 * \details       This function processes the OBD driving cycle specific state
 *                transitions, e.g. IUMPR and DCY qualification. This does not
 *                include healing and status bit processing, as those are
 *                handled generically.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdDcy_Start(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_UpdateObdAging
 *****************************************************************************/
/*!
 * \brief         Processes aging of OBD global statistics
 *
 * \details       Processes aging of OBD global statistics
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdAging(
  void
  );
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_UpdateObdWarmup_Start
 *****************************************************************************/
/*!
 * \brief         Processes warmup cycle updates at start trigger
 *
 * \details       This function processes the warm-up cycle specific state
 *                transitions. This does not include aging, as aging is handled
 *                generically.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdWarmup_Start(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)  
/* ****************************************************************************
 * Dem_OperationCycle_SetStateObdDcy
 *****************************************************************************/
/*!
 * \brief         Queues restart or qualification of OBD driving cycle
 *
 * \details       Queues restart or qualification of OBD driving cycle
 *
 * \param[in]     ObdDcyId
 *                Unique Id of the OBD driving cycle
 *
 * \param[in]     CycleState
 *                DEM_CYCLE_STATE_START: Qualify OBD driving cycle
 *                DEM_CYCLE_STATE_END:   Restart OBD driving cycle.
 *
 * \return        E_OK
 *                Cycle state was queued successfully
 *
 * \return        E_NOT_OK
 *                Cycle state was not queued
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_OperationCycle_SetStateObdDcy(
  CONST(uint8, AUTOMATIC)  ObdDcyId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  );
#endif

/* ****************************************************************************
 * Dem_OperationCycle_SetStateNormalCycle
 *****************************************************************************/
/*!
 * \brief         Queues the cycle state
 *
 * \details       Queues the cycle state for a normal operation cycle (no 
 *                OBD driving, WarmUp or HybridIgnition cycle)
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \param[in]     CycleState
 *                DEM_CYCLE_STATE_START: Start a stopped cycle, or restart an
 *                                       active cycle.
 *                DEM_CYCLE_STATE_END:   Stop an active cycle.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_OperationCycle_SetStateNormalCycle(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  );

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_ProcessIgnHybridCounter
 *****************************************************************************/
/*!
 * \brief         Processes hybrid ignition counter
 *
 * \details       Processes hybrid ignition counter
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 * \param[in]     CycleState
 *                DEM_CYCLE_STATE_START: Start a stopped cycle, or restart an
 *                                       active cycle.
 *                DEM_CYCLE_STATE_END:   Stop an active cycle.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_IUMPR == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_OperationCycle_ProcessIgnHybridCounter(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  );
#endif

# if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_SetStateWarmUp
 *****************************************************************************/
/*!
 * \brief         Queues state for WarmUp Cycle
 *
 * \details       Queues state for WarmUp Cycle
 *
 * \param[in]     CycleState
 *                DEM_CYCLE_STATE_START: Start a stopped cycle, or restart an
 *                                       active cycle.
 *                DEM_CYCLE_STATE_END:   Stop an active cycle.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_OperationCycle_SetStateWarmUp(
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  );
#endif

/* ****************************************************************************
 * Dem_OperationCycle_CycleUpdateEnd
 *****************************************************************************/
/*!
 * \brief         Updates cycle state when cycle is ended
 *
 * \details       Processes global cycle counter and aging cycles
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdateEnd(
  CONST(uint8, AUTOMATIC)  CycleId
  ); 

#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_CycleUpdateStart
 *****************************************************************************/
/*!
 * \brief         Updates cycle state when cycle is started
 *
 * \details       Processes PID41
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdateStart(
  CONST(uint8, AUTOMATIC)  CycleId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_ObdCycleStop
 *****************************************************************************/
/*!
 * \brief         Stops passed Obd cycle
 *
 * \details       Stops passed Obd warm up or driving cycle
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON 
 *                OR
 *                DEM_CFG_SUPPORT_WWHOBD == STD_ON 
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ObdCycleStop(
  CONST(uint8, AUTOMATIC)  CycleId
  );
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_OperationCycle_ObdCycleStart
 *****************************************************************************/
/*!
 * \brief         Starts passed Obd cycle
 *
 * \details       Starts passed Obd warm up or driving cycle
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ObdCycleStart(
  CONST(uint8, AUTOMATIC)  CycleId
  );
#endif

/* ****************************************************************************
 * Dem_OperationCycle_ObdCycleUpdate
 *****************************************************************************/
/*!
 * \brief         Updates status of passed Obd cycle
 *
 * \details       Updates status of passed Obd warm up or driving cycle
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_ObdCycleUpdate(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );

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
 * \defgroup Dem_OperationCycle_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_OperationCycle_UpdateCycleStatesInNvBlock
 *****************************************************************************/
/*!
 * \brief         Update the cycle states in Nv block
 *
 * \details       Update the cycle states in Nv block
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateCycleStatesInNvBlock(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process all queued operation cycle changes
 *
 * \details       Process all queued operation cycle changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_CycleUpdate
 *****************************************************************************/
/*!
 * \brief         Updates cycle state
 *
 * \details       Updates cycle state
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdate(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );

/* ****************************************************************************
 * Dem_OperationCycle_SetState
 *****************************************************************************/
/*!
 * \brief         Queues the cycle state
 *
 * \details       Queues the cycle state
 *
 * \param[in]     CycleId
 *                Unique Id of the cycle
 *
 * \param[in]     CycleState
 *                DEM_CYCLE_STATE_START: Start a stopped cycle, or restart an
 *                                       active cycle.
 *                DEM_CYCLE_STATE_END:   Stop an active cycle.
 *
 * \return        E_OK
 *                Cycle state was queued successfully
 *
 * \return        E_NOT_OK
 *                Cycle state was not queued
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_OperationCycle_SetState(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  );

/* ****************************************************************************
 * Dem_OperationCycle_GetCycleState
 *****************************************************************************/
/*!
 * \brief         Get the current operation cycle state
 *
 * \details       Maps internal cycle state to the equivalent reported 
 *                operation cycle state and return it.
 *
 * \param[in]     CycleId
 *                Unique identifier of the operation cycle
 *
 * \return        The current indicator status
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_OperationCycleStateType, DEM_CODE)
Dem_OperationCycle_GetCycleState(
  CONST(uint8, AUTOMATIC)  CycleId
  );

/* ****************************************************************************
 * Dem_OperationCycle_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-Initializes Dem queue states
 *
 * \details       This function initializes the operation cycle states.
 *
 * \pre           May be called only during pre-initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_PreInit(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the Dem queue states
 *
 * \details       This function can be used to restore the operation cycle 
 *                state stored in NV ram.
 *
 * \pre           May be called only during initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_Init(
  void
  );

/* ****************************************************************************
 * Dem_OperationCycle_Shutdown
 *****************************************************************************/
/*!
 * \brief         Prepare operation cycle for shutdown
 *
 * \details       This function stops all running operation cycles and prepares
 *                the NV state for writeback
 *
 * \pre           May be called only during module shutdown
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_Shutdown(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_OPERATIONCYCLE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_OperationCycle_Interface.h
 *********************************************************************************************************************/
