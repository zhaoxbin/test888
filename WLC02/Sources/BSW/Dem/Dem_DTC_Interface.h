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
 *  \defgroup   Dem_DTC DTC Status
 *  \{
 *  \file       Dem_DTC_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interfaces of DTC subcomponent
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

#if !defined (DEM_DTC_INTERFACE_H)
#define DEM_DTC_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTC_Types.h"

                                                           /* Required types */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCInternalStatus_Types.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DTC_Properties Properties
 * \{
 */
/* ****************************************************************************
 * Dem_DTC_GetInternalStatus
 *****************************************************************************/
/*!
 * \brief         Get the internal status byte with consideration of event
 *                combination
 *
 * \details       This function retrieves the event's internal status byte for
 *                normal events, and the group's internal status byte for
 *                combined events.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The internal status byte relevant for the event or group.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTC_GetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DTC_SetInternalStatus
 *****************************************************************************/
/*!
 * \brief         Set the internal status byte with consideration of event
 *                combination
 *
 * \details       This function stores the event's internal status byte for
 *                normal events, and the group's internal status byte for
 *                combined events.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     InternalStatus
 *                New internal status to set
 *
 * \pre           Must be called within critical section DiagMonitor
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus
  );

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_DTC_SetQualifyStatus
 *****************************************************************************/
/*!
 * \brief         Set current qualification status of the DTC
 *
 * \details       Set current qualification status of the event and all subevents
 *                in case of event combination
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     Status
 *                New qualification status of the event
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetQualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(uint8, AUTOMATIC) Status
  );
#endif

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 * Dem_DTC_SetAgedCounter
 *****************************************************************************/
/*!
 * \brief         Sets the aged counter for the respective DTC.
 *
 * \details       Sets the aged counter for the respective DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     AgedCounter
 *                The aged counter to be set.
 *
 * \config        DEM_CFG_DATA_AGED_COUNTER == STD_ON
 *
 * \pre           Event has a dedicated entry in the aged counter array.
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC) AgedCounter
  );
#endif

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 * Dem_DTC_GetAgedCounter
 *****************************************************************************/
/*!
 * \brief         Gets the Aged Counter of the respective DTC.
 *
 * \details       Gets the Aged Counter of the respective DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \config        DEM_CFG_DATA_AGED_COUNTER == STD_ON
 *
 * \return        Aged Counter of the DTC.
 *
 * \pre           Event has a dedicated entry in the aged counter array.
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
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
 * \defgroup Dem_DTC_Private Private Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_GetCombinedGroupUDSStatus
 *****************************************************************************/
/*!
 * \brief         Get current status of the combined group
 *
 * \details       -
 *
 * \param[in]     GroupId
 *                Unique handle of the combined group
 *
 * \return        Current status of the combined group
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetCombinedGroupUDSStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId
  );
#endif

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_SetCombinedGroupUDSStatus
 *****************************************************************************/
/*!
 * \brief         Set current status of the combined group
 *
 * \details       -
 *
 * \param[in]     GroupId
 *                Unique handle of the combined group
 * \param[in]     Status
 *                New status of the combined group
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetCombinedGroupUDSStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId,
  CONST(uint8, AUTOMATIC) Status
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) \
 && ((DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON) || (DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON))
/* ****************************************************************************
 * Dem_DTC_TestStatusForAgingCycle
 *****************************************************************************/
/*!
 * \brief         Tests whether the current cycle fulfills the conditions for
 *                aging
 *
 * \details       Tests whether the current cycle fulfills the conditions for
 *                aging
 *
 * \param[in]     DtcStatus
 *                UDS DTC status to test
 *
 * \return        TRUE
 *                The aging conditions are fulfilled for this cycle
 * \return        FALSE
 *                the aging conditions are not fulfilled for this cycle
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF &&
 *                (DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON ||
 *                DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestStatusForAgingCycle(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  DTCStatus
  );
#endif

/* ****************************************************************************
 * Dem_DTC_TestGroupAvailable
 *****************************************************************************/
/*!
 * \brief         Tests if a combined event group is available based on runtime
 *                calibration
 *
 * \details       Tests if a combined event group is available based on runtime
 *                calibration
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \return        TRUE
 *                The group is available
 * \return        FALSE
 *                The group is not available
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupAvailable(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );

/* ****************************************************************************
 * Dem_DTC_TestGroupAvailableInVariant
 *****************************************************************************/
/*!
 * \brief         Tests if a combined event group is available based on the PB-S
 *                variant
 *
 * \details       Tests if a combined event group is available based on the PB-S
 *                variant
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \return        TRUE
 *                The group is available in the selected variant
 * \return        FALSE
 *                The group is not available in the selected variant
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupAvailableInVariant(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );

/* ****************************************************************************
 * Dem_DTC_TestGroupSuppression
 *****************************************************************************/
/*!
 * \brief         Tests if a combined event group is suppressed for reporting API
 *
 * \details       Tests if a combined event group is suppressed for reporting API
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \return        TRUE
 *                The group is suppressed
 * \return        FALSE
 *                The group is not suppressed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupSuppression(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );

/* ****************************************************************************
 * Dem_DTC_ApplyUserControlledWIR
 *****************************************************************************/
/*!
 * \brief         Apply the user controlled WIR bit to the DTC's status
 *
 * \details       This function applies a user controlled WIR bit from the
 *                given internal status to the given DTC status byte.
 *
 *                The resulting WIR status cannot be reset by this function.
 *
 * \param[in]     DtcStatus
 *                Unmodified DTC status byte
 *
 * \param[in]     InternalStatus
 *                Internal event status information
 *
 * \return        The resulting DTC status
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_ApplyUserControlledWIR(
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus,
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus
  );

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_CombinedGroupGetFDC
 *****************************************************************************/
/*!
 * \brief         Calculates the fault detection counter of a combined event
 *
 * \details       This function iterates through all sub-events, and takes the
 *                largest fault detection counter to represent the combined
 *                FDC.
 *                This is not stable against preemptive modification of the
 *                set of FDCs concerned. This is not prevented as it would
 *                lead to a large runtime within a critical section, without
 *                actually increasing the expected quality of the result.
 *
 *                Explanation: If all sub-events report a fairly stable result
 *                (the FDCs count fairly linearly), the combined FDC is also
 *                reliable if it is collected without critical section.
 *                If the sub-events change their result often and chaotically,
 *                the combined FDC also behaves chaotically, based on report
 *                order and task priorities. Collecting the FDCs within a
 *                critical section will not improve the result.
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 * \param[out]    FaultDetectionCounter
 *                Pointer to receive the FDC value
 *
 * \return        E_OK
 *                The combined FDC was returned in FaultDetectionCounter
 * \return        E_NOT_OK
 *                The combined FDC could not be determined.
 *
 * \pre           RTE is started (if RTE is used)
 * \config        ((DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_DATA_CURRENT_FDC == STD_ON))
 *                && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) )
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_CombinedGroupGetFDC(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
  );
#endif

#if ( (DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON) \
   || ((DEM_FEATURE_NEED_AGING_TRIGGER_PASSED == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)))
/* ****************************************************************************
 * Dem_DTC_TestDtcMayAge
 *****************************************************************************/
/*!
 * \brief         Tests whether an event or combined event may age
 *
 * \details       Tests whether an event or combined event may age
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event may age
 * \return        FALSE
 *                The event may not age
 *
 * \pre           -
 *
 * \config        (DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON) ||
 *                ((DEM_FEATURE_NEED_AGING_TRIGGER_PASSED == STD_ON) && 
 *                 (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) )
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcMayAge(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Disconnect_Combined
 *****************************************************************************/
/*!
 * \brief         Marks a combined event unavailable
 *
 * \details       This function sets a sub-event unavailable and re-calculates
 *                the availability and suppression states for the combined
 *                DTC.
 *
 *                A stored DTC may not be set to unavailable, so this function
 *                performes no actions on stored DTCs.
 *
 *                Do not call directly, use Dem_DTC_Disconnect instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Must be called in critical section DiagMonitor
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Disconnect_Combined(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Reconnect_Combined
 *****************************************************************************/
/*!
 * \brief         Marks a combined event available
 *
 * \details       This function sets a sub-event available and re-calculates
 *                the availability and suppression states for the combined
 *                DTC.
 *
 *                Do not call directly, use Dem_DTC_Reconnect instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Must be called in critical section DiagMonitor
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON &&
 *                DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Reconnect_Combined(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_AgingStartZeroTarget
 *****************************************************************************/
 /*!
 * \brief         Starts aging of an event with aging target 0
 *
 * \details       This function processes aging for events with aging target
 *                0. I.e. the event will age immediately. This function has
 *                no effect if the event in question is already aged or does
 *                not support aging.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_AgingStartZeroTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_AgingStartMultiTarget
 *****************************************************************************/
/*!
 * \brief         Starts aging of an event.
 *
 * \details       This function sets up an event for aging. In case the event
 *                already ages (or does not support aging), this function has
 *                no effect.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_AgingStartMultiTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Aging_Vcc
 *****************************************************************************/
/*!
 * \brief         Update event due to aging event (OEM specific trigger)
 *
 * \details       Update event due to aging event (OEM specific trigger)
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Aging_Vcc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 * Dem_DTC_AgingStartVCC
 *****************************************************************************/
/*!
 * \brief         Process event aging and occurrence counters
 *
 * \details       Process event aging and occurrence counters
 *
 * \param[in]     DTCContext
 *                DTC processing context
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_AgingStartVCC(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );
#endif

/* ****************************************************************************
 * Dem_DTC_Cleared_Internal
 *****************************************************************************/
/*!
 * \brief         Clears a DTC
 *
 * \details       Clears a DTC
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_Cleared_Internal(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Passed_ProcessDTCEffects_TPSLC
 *****************************************************************************/
/*!
 * \brief         Processes DTCs that are relevant for Pid01 calculation
 *
 * \details       Extended Status of DTC is set to 'passed since last clear'.
 *                For DTC with combined group status it is only set if all 
 *                subevents are tested this cycle and no subevent has status 
 *                failed.
 *
 * \param[in]     DTCContext
 *                DTC processing context
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different DTCContext
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Passed_ProcessDTCEffects_TPSLC(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC)  DTCContext
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

/* ****************************************************************************
 * Dem_DTC_ForEachCombinedEvent
 *****************************************************************************/
/*!
 * \brief         Executes a combined operation.
 *
 * \details       Due to excessive code duplication it was necessary to fall
 *                back to higher order functions. This function takes a
 *                function pointer to an operation to be executed for all
 *                sub-events of a combined event.
 *                For normal events, the operation is executed for that event
 *                only, so the caller does not need to distinguish between
 *                combined and non-combined events too much.
 *
 *                The caller is still reponsible to call this function only
 *                once per combined event, e.g. by calling it only for the
 *                master event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     FuncPtr
 *                Operation to perform on all subevents
 * \param[in]     ArgPtr
 *                Arguments passed to the operation.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ForEachCombinedEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Util_ForEachCombinedFuncType, AUTOMATIC)  FuncPtr,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_InitGroupInternalStatus
 *****************************************************************************/
/*!
 * \brief         Initializes the internal event status of a given combined
 *                event group
 *
 * \details       Initializes the internal event status of a given combined
 *                event group
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \pre           May be called only during module initialization
 * \config        DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitGroupInternalStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
/* ****************************************************************************
 * Dem_DTC_CycleQualifyDcy_AllDtc
 *****************************************************************************/
/*!
 * \brief         Qualifies the OBD driving cycle in case event confirmation
 *                is independent from event memory entry creation.
 *
 * \details       When the driving cycle is qualified, the environmental data,
 *                ConfirmedDTC bit and WIR bit become visible for external
 *                testers and the application.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON &&
 *                DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy_AllDtc(
  void
  );
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_CycleQualifyDcy_StoredOnly
 *****************************************************************************/
/*!
 * \brief         Qualifies the OBD driving cycle in case event confirmation
 *                is coupled with event memory entry creation.
 *
 * \details       When the driving cycle is qualified, the environmental data,
 *                ConfirmedDTC bit and WIR bit become visible for external
 *                testers and the application.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON &&
 *                DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy_StoredOnly(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_SetDtcSuppression
 *****************************************************************************/
/*!
 * \brief         Marks an event's DTC suppressed
 *
 * \details       This function sets an event's DTC suppressed.
 *                For combined events, it does not matter which sub-event is
 *                passed to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif


/* ****************************************************************************
 * Dem_DTC_EventCreateMemory
 *****************************************************************************/
/*!
 * \brief         Allocate an event memory entry
 *
 * \details       This function tries to allocate an event memory entry for
 *                the given event. This can displace existing memory entries
 *                if the memory is already full.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        MemoryIndex of the allocated memory entry. If no entry was
 *                allocated, DEM_MEM_INVALID_MEMORY_INDEX is returned.
 *
 * \pre           The event may not be stored already
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_EventCreateMemory(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF))
/* ****************************************************************************
 * Dem_DTC_StartAgingWithMemoryEntryMultiTarget
 *****************************************************************************/
/*!
 * \brief         Starts aging of an event.
 *
 * \details       This function sets up an event for aging according to the 
 *                legacy aging algorithm. Here the aging proceeds only if a 
 *                memory entry could be allocated for the event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_StartAgingWithMemoryEntryMultiTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON))
/* ****************************************************************************
 * Dem_DTC_StartAgingWithoutMemoryEntryMultiTarget
 *****************************************************************************/
/*!
 * \brief         Starts aging of an event.
 *
 * \details       This function sets up an event for aging. Here the aging 
 *                proceeds event if a memory entry does not exist for the event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_StartAgingWithoutMemoryEntryMultiTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 * Dem_DTC_ResetAgedCounter
 *****************************************************************************/
/*!
 * \brief         Reset the aged counter of the respective DTC.
 *
 * \details       Reset the aged counter of the respective DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \config        DEM_CFG_DATA_AGED_COUNTER == STD_ON
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_ResetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 * Dem_DTC_IncrementAgedCounter
 *****************************************************************************/
/*!
 * \brief         Increments the aged counter for the respective DTC.
 *
 * \details       Increments the aged counter for the respective DTC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \config        DEM_CFG_DATA_AGED_COUNTER == STD_ON
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_IncrementAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif
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
 * \defgroup Dem_DTC_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_CalculateCombineGroupUdsStatus
 *****************************************************************************/
/*!
 * \brief         Gets the combined event group status of a combined event
 *
 * \details       This calculates the logical OR of all subevent status bytes.
 *                Combined event status bytes only change on the main function,
 *                so no critical section is required from the main function.
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \return        'Raw' combined UDS status of the DTC consisting of the 
 *                logical OR of the UDS status of all its events.
 *                
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_CalculateCombineGroupUdsStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );
#endif

#if ( (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
   || (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON) \
   || (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON) \
   || (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) \
   || (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) )
/* ****************************************************************************
 * Dem_DTC_ApplyCombinedStatus
 *****************************************************************************/
/*!
 * \brief         Apply interdependent status bits on a combined status
 *
 * \details       This function corrects the status byte inconsistencies
 *                resulting from event combination, according to the Autosar
 *                specification.
 *
 * \param[in]     DtcStatus
 *                Unmodified DTC status byte
 *
 * \return        The resulting DTC status
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) ||
 *                (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON) ||
 *                (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON) ||
 *                (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) ||
 *                (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_ApplyCombinedStatus(
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  );
#endif

/* ****************************************************************************
 * Dem_DTC_ApplyExternalOnlyStatus
 *****************************************************************************/
/*!
 * \brief         Apply correction term for DTC status modification
 *
 * \details       This function applies a filter to the DTC status byte to set
 *                bits that are forced to true by different mechanisms than
 *                event status modification.
 *                Also, status bits not contained in the status availability
 *                mask are masked out.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DtcStatus
 *                Unmodified DTC status byte
 *
 * \return        The resulting DTC status
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_ApplyExternalOnlyStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  );

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_AgingCycle
 *****************************************************************************/
/*!
 * \brief         Processes the aging cycle for a DTC
 *
 * \details       Processes the aging cycle for a DTC
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     CycleCounter
 *                Current cycle count
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_AgingCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC)  CycleCounter,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_Aged
 *****************************************************************************/
/*!
 * \brief         Completes aging of a DTC.
 *
 * \details       Depending on configuration this will clear the DTC's memory
 *                entry, or simply mark it as 'aged'.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Aged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_DTC_ClearOBDFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Clears OBD FreezeFrame data
 *
 * \details       Clears OBD FreezeFrame data if stored by passed event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ClearOBDFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Passed_CalcDTCEffects_VCC
 *****************************************************************************/
/*!
 * \brief         Calculate DTC triggers on 'Passed' status report.
 *
 * \details       If the DTC has a combined group calculate the DTC triggers
 *                from DTC's changed UDS status byte. If the DTC has no
 *                combined group, the DTC trigger equals event triggers.
 *
 * \param[in,out] DTCContext
 *                DTC processing context. This function updates the DTC trigger
 *                member.
 * \param[in]     EventEffects
 *                Event trigger mask holding the relevant event status changes.
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON
 *
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Passed_CalcDTCEffects_VCC(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
  CONST(uint8, AUTOMATIC) EventEffects
  );
#endif

/* ****************************************************************************
 * Dem_DTC_Cleared
 *****************************************************************************/
/*!
 * \brief         Clears an event from the given origin memory, if allowed
 *
 * \details       This function clears an event based on the return value of
 *                its 'clear event allowed' callback.
 *                InitMonitor notifications are called also when the event is
 *                not allowed to be cleared.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event was cleared
 * \return        FALSE
 *                The event was not cleared
 *
 * \pre           RTE must be started
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_Cleared(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) \
 && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Displaced
 *****************************************************************************/
/*!
 * \brief         Updates the status of a displaced DTC
 *
 * \details       Updates the status of a displaced DTC
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF &&
 *                DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Displaced(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Displaced_Vcc
 *****************************************************************************/
/*!
 * \brief         Updates the status of a displaced DTC
 *
 * \details       Updates the status of a displaced DTC
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     SI30
 *                Status Indicator byte of the displaced event
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Displaced_Vcc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  SI30
  );
#endif

/* ****************************************************************************
 * Dem_DTC_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Gets the FaultDetectionCounter (FDC) of a DTC
 *
 * \details       This function retrieves the DTC's FDC. If the DTC has a
 *                combined event group, the largest FDC of all subevents is 
 *                returned.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    FaultDetectionCounter
 *                Pointer to receive the FDC value
 *
 * \return        The current FDC of the event or group.
 *
 * \pre           RTE must be started
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_GetFaultDetectionCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
  );

#if ( (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
   && ( ( ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON) ) \
     || ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) ) ) )
/* ****************************************************************************
 * Dem_DTC_CombinedGroupGetFDCMax
 *****************************************************************************/
/*!
 * \brief         Calculates the maximum fault detection counter this cycle of
 *                a combined event
 *
 * \details       This function iterates through all sub-events, and takes the
 *                largest maximum fault detection counter to represent the
 *                combined maximum FDC.
 *
 * \param[in]     GroupId
 *                Unique identifier of the combined event group
 *
 * \return        The maximum FDC value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *                && ( ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
 *                && DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)
 *                || (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF && DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) )
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(sint8, DEM_CODE)
Dem_DTC_CombinedGroupGetFDCMax(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  );
#endif

/* ****************************************************************************
 * Dem_DTC_GetDTCStatus
 *****************************************************************************/
/*!
 * \brief         Gets the UDS status byte of a DTC
 *
 * \details       This function retrieves the event's status byte for normal
 *                events, and the combined event group's status byte for
 *                combined events.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The status byte relevant for the event or group
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GetDTCStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_ResetDtcSuppression
 *****************************************************************************/
/*!
 * \brief         Marks an event's DTC un-suppressed
 *
 * \details       This function sets an event's DTC un-suppressed.
 *                For combined events, it does not matter which sub-event is
 *                passed to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ResetDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_DTC_ChangeDtcSuppression
 *****************************************************************************/
/*!
 * \brief         Change suppression of a DTC
 *
 * \details       This function suppresses the DTC or releases its suppression.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     SuppressionStatus
 *                TRUE: Suppress the DTC
 *                FALSE: Lift suppression of the DTC
 *
 * \return        E_OK
 *                The suppression was changed successfully
 * \return        E_NOT_OK
 *                The request was rejected because of invalid event
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_ChangeDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  SuppressionStatus
  );
#endif

/* ****************************************************************************
 * Dem_DTC_TestDtcAvailable
 *****************************************************************************/
/*!
 * \brief         Tests if a DTC is available based on runtime calibration
 *
 * \details       Tests if a event or combined event group is available based
 *                on runtime calibration. Any event of a combined group can be
 *                passed to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event or combined event group is available
 * \return        FALSE
 *                The event or combined event group is not available
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcAvailable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DTC_TestDtcAvailableInVariant
 *****************************************************************************/
/*!
 * \brief         Tests if a DTC is available based on the PB-S variant
 *
 * \details       For normal events, this function simply looks up the event
 *                configuration. A combined event group is available only if at
 *                least one sub-event is available in the active variant.
 *                Any event of a combined group can be passed to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event or combined event group is available in the selected
 *                variant
 * \return        FALSE
 *                The event or combined event group is not available in the
 *                selected variant
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcAvailableInVariant(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DTC_TestDtcSuppression
 *****************************************************************************/
/*!
 * \brief         Tests if a DTC is suppressed for reporting API
 *
 * \details       Tests if an event or combined event group is suppressed for
 *                reporting API. Any event of a combined group can be passed
 *                to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event or combined event group is suppressed
 * \return        FALSE
 *                The event or comined event group is not suppressed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DTC_TestDtcSuppressed
 *****************************************************************************/
/*!
 * \brief         Tests a DTC can be considered for reporting API
 *
 * \details       Tests all options due to which an event or combined event group has to be
 *                has to be excluded from reporting API, based on the combined event group
 *                for combined events. Any event of a combined group can be passed
 *                to this function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event or combined event group is currently suppressed
 * \return        FALSE
 *                The event or combined event group is currently not suppressed
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcSuppressed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 * Dem_DTC_OpCycleEnd_Aging
 *****************************************************************************/
/*!
 * \brief         Processes aging at the end of the DTC's operation cycle
 *
 * \details       Processes aging at the end of the DTC's operation cycle.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     OldDtcStatus
 *                Dtc status before cycle restart
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON)
 *                 && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_OpCycleEnd_Aging(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  OldDtcStatus
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_DTC_TestPfcRequired
 *****************************************************************************/
/*!
 * \brief         Tests whether evaluation of the permanent fault condition 
 *                is required.
 *
 * \details       Tests whether evaluation of the permanent fault condition 
 *                is required.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Evaluation of the permanent fault condition is required
 *                for event.
 * \return        FALSE
 *                Evaluation of the permanent fault condition is not required 
 *                for event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestPfcRequired(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_DTC_TestStoredStatus
 *****************************************************************************/
/*!
 * \brief         Tests whether a memory entry exists for the DTC
 *
 * \details       Tests whether a memory entry exists for the DTC. 
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Memory entry for DTC exists.
 * \return        FALSE
 *                Memory entry for DTC does not exist.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_DTC_TestStoredStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DTC_InitDTCContext
 *****************************************************************************/
/*!
 * \brief         Initialize context of DTC's status report processing.
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    DTCContext
 *                DTC processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitDTCContext(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );

/* ****************************************************************************
 * Dem_DTC_CalculateDTCStatus
 *****************************************************************************/
/*!
 * \brief         Update of DTC UDS status byte
 *
 * \details       If the DTC has a combined group, the UDS status is calculated
 *                from the UDS status of all its subevents. Without combined 
 *                group the DTC status equals the event status.
 *
 * \param[in,out] DTCContext
 *                DTC processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CalculateDTCStatus(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );

/* ****************************************************************************
 * Dem_DTC_CalculateFailedEffects
 *****************************************************************************/
/*!
 * \brief         Calculate storage independent DTC triggers on 'Failed' 
 *                status report.
 *
 * \details       If the DTC has a combined group calculate the storage independent
 *                DTC triggers from DTC's changed UDS status byte. If the DTC 
 *                has no combined group the DTC trigger equals event triggers.
 *
 * \param[in,out] DTCContext
 *                DTC processing context. This function updates the DTC trigger
 *                member.
 * \param[in]     EventEffects
 *                Event trigger mask holding the relevant event status changes.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CalculateFailedEffects(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
  CONST(uint8, AUTOMATIC)  EventEffects
  );

/* ****************************************************************************
 * Dem_DTC_CalculateFailedEffects_OnStorage
 *****************************************************************************/
/*!
 * \brief         Calculate storage dependent DTC triggers on 'Failed' 
 *                status report.
 *
 * \details       If the DTC has a combined group calculate the storage dependent
 *                DTC triggers from DTC's changed UDS status byte. If the DTC 
 *                has no combined group the DTC trigger equals event triggers.
 *
 * \param[in,out] DTCContext
 *                DTC processing context. This function updates the DTC trigger
 *                member.
 * \param[in]     EventEffects
 *                Event trigger mask holding the relevant event status changes.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CalculateFailedEffects_OnStorage(
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
  CONST(uint8, AUTOMATIC)  EventEffects
  );

/* ****************************************************************************
 * Dem_DTC_ProcessFailedEffects
 *****************************************************************************/
/*!
 * \brief         Process DTC triggers on 'Failed' status report.
 *
 * \details       Set internal state of the DTC to 'stored'.
 *
 * \param[in]     DTCContext
 *                DTC processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessFailedEffects(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );

/* ****************************************************************************
* Dem_DTC_Passed_ProcessDTCEffects
*****************************************************************************/
/*!
 * \brief         Process DTC triggers on 'Passed' status report.
 *
 * \details       Process PID01 calculation (if configrued) and aging start
 *                conditions.
 *
 * \param[in]     DTCContext
 *                DTC processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Passed_ProcessDTCEffects(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC)  DTCContext
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DTC_ProcessStorage
 *****************************************************************************/
/*!
 * \brief         Process Dtc storage into event memory
 *
 * \details       Processes Dtc storage into event memory and triggers
 *                updating the stored data.
 *
 * \param[in,out] EventContext
 *                Event processing context
 * \param[in,out] DTCContext
 *                DTC processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessStorage(
  CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext,
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  );

/* ****************************************************************************
 * Dem_DTC_ResetFdcToc
 *****************************************************************************/
/*!
 * \brief         Resets Fdc trip flag for the DTC
 *
 * \details       Resets Fdc trip flag of the DTC in the DTC internal status
 *                field.
 *
 * \param[in]     DTCContext
 *                DTC processing context
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ResetFdcToc(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC)  DTCContext
  );

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && \
    ((DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON) || (DEM_CFG_STORAGE_AT_FDC == STD_ON))
/* ****************************************************************************
 * Dem_DTC_FdcTrip
 *****************************************************************************/
/*!
 * \brief         Updates event data due to exceeding a FDC threshold
 *
 * \details       Updates event data due to exceeding a FDC threshold
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     FirstThisCycle
 *                Flag to mark if FDC did already trip this cycle
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF &&
 *                (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON ||
 *                 DEM_CFG_STORAGE_AT_FDC == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_FdcTrip(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  FirstThisCycle
  );
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 * Dem_DTC_FdcTrip_Vcc
 *****************************************************************************/
/*!
 * \brief         Updates event data due to exceeding a FDC threshold
 *
 * \details       Updates event data due to exceeding a FDC threshold
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     TCTOC
 *                Flag to mark if the event was already tested this cycle
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_FdcTrip_Vcc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  TCTOC
  );
#endif

/* ****************************************************************************
 * Dem_DTC_UpdateFdcMax
 *****************************************************************************/
/*!
 * \brief         Update event data 'maximum FDC since last clear'
 *
 * \details       Update event data 'maximum FDC since last clear'
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_UpdateFdcMax(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Disconnect
 *****************************************************************************/
/*!
 * \brief         Disconnects a DTC
 *
 * \details       Disconnect the DTC's event. If the DTC has a combined group, 
 *                disconnect all its subevents.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_DTC_Disconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_DTC_Reconnect
 *****************************************************************************/
/*!
 * \brief         Reconnects a DTC
 *
 * \details       Reconnect the DTC's event. If the DTC has a combined group, 
 *                reconnect all its subevents.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_DTC_Reconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_DTC_TestRemainingEventforDtc
 *****************************************************************************/
/*!
 * \brief         For Stored DTCs having a combined group, test if another event 
 *                is available beside the event to set unavailable.
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Another event is still available
 *                FALSE
 *                All events are now unavailable (DTC is now unavailable)
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestRemainingEventforDtc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 ! Dem_DTC_GetWIRStatus
 *****************************************************************************/
/*!
 * \brief         Get the user controlled WIR status 
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \return        TRUE
 *                User controlled WIR bit is set
 *
 * \return        FALSE
 *                User controlled WIR bit is not set
 *
 * \config        DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_GetWIRStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 ! Dem_DTC_SetWIRStatus
 *****************************************************************************/
/*!
 * \brief         Sets or resets the WIR status bit manually
 *
 * \details       Sets or resets the WIR status bit manually
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[in]     WIRStatus
 *                TRUE:  Latch WIR-bit to TRUE
 *                FALSE: Release the latch
 *
 * \return        E_OK
 *                Request processed successfully
 *
 * \return        E_NOT_OK
 *                The request was rejected due to variant coding
 *
 * \config        DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_SetWIRStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC) WIRStatus
  );
#endif

#if DEM_FEATURE_NEED_OBD == STD_ON
/* ****************************************************************************
 * Dem_DTC_CycleQualifyDcy
 *****************************************************************************/
/*!
 * \brief         Forward application of OBD driving cycle qualification on DTC.
 *
 * \details       Forward application of OBD driving cycle qualification on DTC.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy(
  void
  );
#endif

/* ****************************************************************************
 * Dem_DTC_OpCycle
 *****************************************************************************/
/*!
 * \brief         Update the UDS status of DTC due to operation cycle
 *                state change
 *
 * \details       -
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
Dem_DTC_OpCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );

/* ****************************************************************************
 * Dem_DTC_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the DTC status processing sub-component
 *
 * \details       Initializes the DTC status processing sub-component
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_Init(
  void
  );

/* ****************************************************************************
 * Dem_DTC_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-Initializes the Dem DTCs
 *
 * \details       Pre-Initializes the Dem DTCs
 *
 * \pre           May be called only during module pre-initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_PreInit(
  void
  );

/* ****************************************************************************
 * Dem_DTC_InitQualification
 *****************************************************************************/
/*!
 * \brief         Initializes the qualification states derived from DTC storage
 *
 * \details       Initializes the qualification states derived from DTC storage
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitQualification(
  void
  );

/* ****************************************************************************
 * Dem_DTC_SetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Sets the aging target for the event.
 *
 * \details       Sets the aging target for the event in the respective 
 *                array based on the selected aging compliance.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \param[in]     AgingCounter
 *                The aging counter to be set in the memory entry or array
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_SetAgingCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(uint16, AUTOMATIC) AgingCounter
  );

/* ****************************************************************************
 * Dem_DTC_GetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Gets the aging counter of the event.
 *
 * \details       Gets the aging counter of the event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Aging counter of the event.
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_DTC_GetAgingCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC) MemoryEntryId
  );

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 * Dem_DTC_TestAndInvalidateAgingCounter
 *****************************************************************************/
/*!
 * \brief         Tests and invalidates aging counter of the event.
 *
 * \details       Tests and invalidates aging counter of the event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_TestAndInvalidateAgingCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 * Dem_DTC_GetAgingStatus
 *****************************************************************************/
/*!
 * \brief         Function returns the current aging status of an event.
 *
 * \details       Function returns the current aging status of an event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Current aging status of the event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DTC_AgingStatusType, DEM_CODE)
Dem_DTC_GetAgingStatus(                                                                                                          
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DTC_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTC_Interface.h
 *********************************************************************************************************************/
