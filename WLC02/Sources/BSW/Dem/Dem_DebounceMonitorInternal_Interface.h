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
/*!  Project    MICROSAR Diagnostic Event Manager (Dem)
 *
 *  \ingroup    Dem_Debounce
 *  \defgroup   Dem_DebounceMonitorInternal Monitor Internal Debounce
 *  \{
 *  \file       Dem_DebounceMonitorInternal_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of DebounceMonitorInternal subcomponent
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

#if !defined (DEM_DEBOUNCEMONITORINTERNAL_INTERFACE_H)
#define DEM_DEBOUNCEMONITORINTERNAL_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceMonitorInternal_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DebounceMonitorInternal_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_CheckDebounceInfoPtr
 *****************************************************************************/
/*!
 * \brief         Checks whether the DebounceInfoPtr is initialized for monitor 
 *                internal debouncing.
 *
 * \details       Checks whether the DebounceInfoPtr is initialized for monitor 
 *                internal debouncing.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to debounce base object.
 *
 * \return        TRUE: DebounceInfoPtr is initialized for monitor internal debouncing.
 *                FALSE: Otherwise.
 *
 * \pre           -
 * 
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceMonitorInternal_CheckDebounceInfoPtr(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_Base2MonitorInternal
 *****************************************************************************/
/*!
 * \brief         Derives the monitor internal debounce object from the given base debounce object.
 *
 * \details       Derives the monitor internal debounce object from the given base debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to debounce algorithm management data.
 *
 * \return        The monitor internal debounce object.
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceMonitorInternal_InfoPtrType, DEM_CODE)
 Dem_DebounceMonitorInternal_Base2MonitorInternal(
     Dem_DebounceBase_InfoPtrType DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_ConstBase2MonitorInternal
 *****************************************************************************/
/*!
 * \brief         Derives the monitor internal debounce object from the given base debounce object.
 *
 * \details       Derives the monitor internal debounce object from the given base debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Non-writable pointer to debounce algorithm management data.
 *
 * \return        The monitor internal debounce object.
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceMonitorInternal_ConstInfoPtrType, DEM_CODE)
Dem_DebounceMonitorInternal_ConstBase2MonitorInternal(
     Dem_DebounceBase_ConstInfoPtrType DebounceInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */


/* ****************************************************************************
 * Dem_DebounceMonitorInternal_GetNewMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Get the new monitor status from the given monitor internal debounce object.
 *
 * \details       Get the new monitor status from the given monitor internal debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Non-writable pointer to debounce algorithm management data.
 *
 * \return        The new monitor status.
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DebounceMonitorInternal_GetNewMonitorStatus(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_SetNewMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Set the 'new' monitor status for the given monitor internal debounce object.
 *
 * \details       Set the 'new' monitor status for the given monitor internal debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to debounce algorithm management data.
 * \param[in]     MonitorTrigger
 *                New value.
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceMonitorInternal_SetNewMonitorStatus(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(uint8, AUTOMATIC)  MonitorTrigger
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
 * \defgroup Dem_DebounceMonitorInternal_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_InfoInit
 *****************************************************************************/
/*!
 * \brief         Initializes a debounce object for monitor internal debouncing.
 *
 * \details       This function initializes the fields of a monitor internal
 *                debounce descriptor for a given event. Debounce values are set
 *                to current values from satellite.
 *
 * \param[out]    DebounceInfoData
 *                The monitor internal debouncing element to be initialized.
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     SatelliteData
 *                The satellite data object where the DebounceData is stored.
 *
 * \returns       A pointer to the base debounce object.
 *
 * \pre           Event must use monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceBase_InfoPtrType, DEM_CODE)
Dem_DebounceMonitorInternal_InfoInit(
  CONSTP2VAR(Dem_DebounceMonitorInternal_InfoType, AUTOMATIC, AUTOMATIC) DebounceInfoData,
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_Calculate
 *****************************************************************************/
/*!
 * \brief         Process monitor internal debouncing.
 *
 * \details       Monitor internal debouncing is handled inside the monitor,
 *                this function only validates the arguments.
 *
 * \param[in,out] DebounceInfoPtr
 *                The debouncing information containing the monitor status.
 *                Valid values for the monitor status are:
 *                - DEM_EVENT_STATUS_FAILED
 *                - DEM_EVENT_STATUS_PASSED
 *                - DEM_DEBOUNCE_MONITORINTERNAL_STATUS_FDCTHRESHOLDREACHED
 *
 * \return        TRUE
 *                The monitor result was valid.
 * \return        FALSE
 *                The monitor result was invalid OR
 *                Debouncing failed due to enable conditions OR
 *                DebounceInfoPtr was not initialized for monitor internal debouncing.
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DebounceMonitorInternal_Calculate(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_Freeze
 *****************************************************************************/
/*!
 * \brief         Pauses monitor internal debouncing for an event.
 *
 * \details       Function has no effect.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceMonitorInternal_Freeze(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_Reset
 *****************************************************************************/
/*!
 * \brief         Reset monitor internal debouncing for an event.
 *
 * \details       Reset monitor internal debouncing for an event.
 *
 * \param[in,out] DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceMonitorInternal_Reset(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_GetDebouncingState
 *****************************************************************************/
/*!
 * \brief         Calculates the debouncing state of an event.
 *
 * \details       Calculates the debouncing state of an event.
 *
 * \param[in,out] DebounceInfoPtr
 *                The debouncing information.
 *
 * \return        The debouncing state of the monitor.
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebounceMonitorInternal_GetDebouncingState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceMonitorInternalSat_UpdateDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Updates the stored maximum debounce value for an event.
 *
 * \details       Updates the stored maximum debounce value for an event.
 *
 * \param[in,out] DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceMonitorInternalSat_UpdateDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceMonitorInternalSat_ResetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Resets the stored maximum debounce value for an event.
 *
 * \details       Resets the stored maximum debounce value for an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceMonitorInternalSat_ResetDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the current fault detection counter of an event.
 *
 * \details       Calculates the current fault detection counter of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \param[out]    FaultDetectionCounter
 *                The Fdc based on the debounce value returned by the monitor.
 *                In case that function returns an error, FaultDetectionCounter
 *                stays unchanged.
 *
 * \return        Whether getting the FDC succeeded (E_OK)
 *                or not (DEM_E_NO_FDC_AVAILABLE)
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceMonitorInternal_GetFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the maximum fault detection counter of an event.
 *
 * \details       Calculates the maximum fault detection counter of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 * \param[out]    FaultDetectionCounter
 *                The maximum FaultDetectionCounter based on the maximum
 *                reported debounce value.
 *
 * \return        E_OK
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceMonitorInternal_GetMaxFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_GetDebouncingResult
 *****************************************************************************/
/*!
 * \brief         Update the debouncing data of an event.
 *
 * \details       Update the debouncing data of an event.
 *
 * \param[in,out] DebounceInfoPtr
 *                The debouncing information.
 *
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 *
 * \return        Data object holding the modified debounce data
 *
 * \pre           DebounceInfoPtr was initialized for monitor internal debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceMonitorInternal_GetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceMonitorInternal_RestoreDebounceValue
 *****************************************************************************/
/*!
 * \brief         Restore the given debouncing value.
 *
 * \details       Function call is not valid for monitor internal debouncing.
 *                Det is called.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 *
 * \param[in]     Value
 *                The value to be restored
 *
 * \param[in]     ExpectedThreshold
 *                Specifies whether the negative threshold is expected to be
 *                reached (TRUE), or the positive one (FALSE).
 *
 * \return        Data object holding the unmodified debounce data.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceMonitorInternal_RestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DEBOUNCEMONITORINTERNAL_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceMonitorInternal_Interface.h
 *********************************************************************************************************************/
