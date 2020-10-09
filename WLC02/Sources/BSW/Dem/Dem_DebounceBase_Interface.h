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
/*!
 *  \ingroup    Dem_Debounce
 *  \defgroup   Dem_DebounceBase Abstract Debounce Base
 *  \{
 *  \file       Dem_DebounceBase_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of DebounceBase subcomponent
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

#if !defined (DEM_DEBOUNCEBASE_INTERFACE_H)
#define DEM_DEBOUNCEBASE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceBase_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DebounceBase_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_DebounceBase_GetEventId()
 *****************************************************************************/
/*!
 * \brief         Get the Event which is assigned to the debounce object.
 *
 * \details       Get the Event which is assigned to the debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to read from.
 *
 * \return        The Event which is assigned to the debounce object
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DebounceBase_GetEventId(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_GetMonitorTrigger()
 *****************************************************************************/
/*!
 * \brief         Get the MonitorTrigger of the given debounce object.
 *
 * \details       Get the MonitorTrigger of the given debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to read from.
 *
 * \return        The MonitorTrigger which is assigned to the debounce object
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventStatusType, DEM_CODE)
Dem_DebounceBase_GetMonitorTrigger(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 *  Dem_DebounceBase_SetMonitorTrigger()
 *****************************************************************************/
/*!
 * \brief         Set the MonitorTrigger of the given debounce object.
 *
 * \details       Set the MonitorTrigger of the given debounce object.
 *
 * \param[out]    DebounceInfoPtr
 *                The object to write to.
 *
 * \param[in]     MonitorTrigger
 *                The status (of the application monitor) to set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceBase_SetMonitorTrigger(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_EventStatusType, AUTOMATIC)           MonitorTrigger
  );

/* ****************************************************************************
 * Dem_DebounceBase_TestDebouncingChanged()
 *****************************************************************************/
/*!
 * \brief         Get the DebouncingChanged flag of the given debounce object.
 *
 * \details       Get the DebouncingChanged flag of the given debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to read from.
 *
 * \return        The state of the DebouncingChanged flag
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceBase_TestDebouncingChanged(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_SetDebouncingChanged()
 *****************************************************************************/
/*!
 * \brief         Set the DebouncingChanged flag of the given debounce object.
 *
 * \details       Set the DebouncingChanged flag of the given debounce object.
 *
 * \param[out]    DebounceInfoPtr
 *                The object to write to.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceBase_SetDebouncingChanged(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_TestRequestFdcProcessing()
 *****************************************************************************/
/*!
 * \brief         Get the RequestFdcProcessing flag of the given debounce object.
 *
 * \details       Get the RequestFdcProcessing flag of the given debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to read from.
 *
 * \return        The state of the RequestProcessing flag
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceBase_TestRequestFdcProcessing(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_SetRequestFdcProcessing()
 *****************************************************************************/
/*!
 * \brief         Set the RequestFdcProcessing flag of the given debounce object.
 *
 * \details       Set the RequestFdcProcessing flag of the given debounce object.
 *
 * \param[out]    DebounceInfoPtr
 *                The object to write to.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceBase_SetRequestFdcProcessing(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_TestMaximumFdcExceeded()
 *****************************************************************************/
/*!
 * \brief         Get the MaximumFdcExceeded flag of the given debounce object.
 *
 * \details       Get the MaximumFdcExceeded flag of the given debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to read from.
 *
 * \return        The state of the MaximumFdcExceeded flag
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceBase_TestMaximumFdcExceeded(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_SetMaximumFdcExceeded()
 *****************************************************************************/
/*!
 * \brief         Set the MaximumFdcExceeded flag of the given debounce object.
 *
 * \details       Set the MaximumFdcExceeded flag of the given debounce object.
 *
 * \param[out]    DebounceInfoPtr
 *                The object to write to.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceBase_SetMaximumFdcExceeded(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_TestFdcThresholdExceeded()
 *****************************************************************************/
/*!
 * \brief         Get the FdcThresholdExceeded flag of the given debounce object.
 *
 * \details       Get the FdcThresholdExceeded flag of the given debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to read from.
 *
 * \return        The state of the FdcThresholdExceeded flag
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceBase_TestFdcThresholdExceeded(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_SetFdcThresholdExceeded()
 *****************************************************************************/
/*!
 * \brief         Set the FdcThresholdExceeded flag of the given debounce object.
 *
 * \details       Set the FdcThresholdExceeded flag of the given debounce object.
 *
 * \param[out]    DebounceInfoPtr
 *                The object to write to.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceBase_SetFdcThresholdExceeded(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the current fault detection counter of an event.
 *
 * \details       Calculates the current fault detection counter of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to read from.
 *
 * \param[out]    FaultDetectionCounter
 *                The FaultDetectionCounter based on the given time and state.
 *                In case that function returns an error, FaultDetectionCounter
 *                stays unchanged.
 *
 * \return        E_OK if out value is valid. Otherwise an error is returned.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceBase_GetFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  );

/* ****************************************************************************
 * Dem_DebounceBase_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the maximum fault detection counter of an event.
 *
 * \details       Calculates the maximum fault detection counter of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to read from.
 *
 * \param[out]    FaultDetectionCounterMax
 *                
 * \return        E_OK if out value is valid. Otherwise an error is returned.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceBase_GetMaxFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounterMax
  );

/* ****************************************************************************
 * Dem_DebounceBase_GetDebouncingState
 *****************************************************************************/
/*!
 * \brief         Calculates the debouncing state of an event.
 *
 * \details       Calculates the debouncing state of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to read from.
 *
 * \return        The debouncing state of the monitor
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebounceBase_GetDebouncingState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_CalculateDebouncing
 *****************************************************************************/
/*!
 * \brief         Calculates the debouncing value.
 *
 * \details       Calculates the debouncing value.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to modify.
 *
 * \return        TRUE
 *                Debouncing was processed
 * \return        FALSE
 *                Processing was rejected due to failed  preconditions
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DebounceBase_CalculateDebouncing(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_Reset
 *****************************************************************************/
/*!
 * \brief         Reset the debounce value and state.
 *
 * \details       Reset the debounce value and state.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to modify.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceBase_Reset(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_Freeze
 *****************************************************************************/
/*!
 * \brief         Pause debouncing.
 *
 * \details       Pause debouncing.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to modify.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceBase_Freeze(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBaseSat_UpdateDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Updates the stored maximum debounce value.
 *
 * \details       Updates the stored maximum debounce value.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to modify.
 *
 * \pre           Must be called from the local DemSatellite partition of the
 *                passed EventId.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceBaseSat_UpdateDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBaseSat_ResetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Updates the stored maximum debounce value
 *
 * \details       Updates the stored maximum debounce value
 *
 * \param[in]     DebounceInfoPtr
 *                The object to modify.
 *
 * \pre           Must be called from the local DemSatellite partition of the
 *                passed EventId.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceBaseSat_ResetDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBaseCore_ResetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Updates the stored maximum debounce value.
 *
 * \details       Updates the stored maximum debounce value.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to modify.
 *
 * \pre           Must be called from DemMaster partition only.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 *
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceBaseCore_ResetDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceBase_GetDebouncingResult
 *****************************************************************************/
/*!
 * \brief         Update the debouncing data.
 *
 * \details       Update the debouncing data.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to read from.
 *
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 *
 * \return        Data object holding the modified debounce data
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceBase_GetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
/* ****************************************************************************
 * Dem_DebounceBase_RestoreDebounceValue
 *****************************************************************************/
/*!
 * \brief         Restore the given debouncing value.
 *
 * \details       Value is restored, if
 *                 - the given debounce value is not qualified
 *                 - or if the debounce value is qualified and the reached
 *                   threshold equals the ExpectedThreshold.
 *
 *                Otherwise Value is not restored.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to query.
 *
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 *
 * \param[in]     Value
 *                The value to be restored
 *
 * \param[in]     ExpectedThreshold
 *                Specifies whether the negative (TRUE) or the positive (FALSE)
 *                threshold is expected to be reached.
 *
 * \return        Data object holding the modified debounce data
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceBase_RestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PUBLIC FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DebounceBase_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_DebounceBase_InfoInitDefault
 *****************************************************************************/
/*!
 * \brief         Initializes a debounce descriptor.
 *
 * \details       This function initializes the basic common fields of a
 *                debounce descriptor. State information remains uninitialized
 *                as it is not known without context.
 *                The generic fields that will be set here are 'EventId' and
 *                'FunctionTable'.
 *
 * \param[out]    DebounceInfoPtr
 *                The debouncing element to be initialized.
 * \param[in]     FunctionTable
 *                The virtual function table of the specific class.
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \returns       The generic base type object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceBase_InfoPtrType, DEM_CODE)
Dem_DebounceBase_InfoInitDefault(
  CONSTP2VAR(Dem_DebounceBase_InfoType, AUTOMATIC, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_DebounceFunctionTablePtrType, AUTOMATIC)  FunctionTable,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DebounceBaseSat_GetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Get current maximum debounce value of the event.
 *
 * \details       Get current maximum debounce value of the event.
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \return        Current maximum debounce value of the event
 *
 * \pre           Must be called from the local DemSatellite partition of the
 *                passed EventId.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_DebounceBaseSat_GetDebounceValueMax(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_DebounceBaseSat_SetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Set current maximum debounce value of the event.
 *
 * \details       Set current maximum debounce value of the event.
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     DebounceValue
 *                New maximum debounce value of the event
 *
 * \pre           Must be called from the local DemSatellite partition of the
 *                passed EventId.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceBaseSat_SetDebounceValueMax(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(sint16, AUTOMATIC) DebounceValue
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DEBOUNCEBASE_INTERFACE_H */

/*!
 * \}
 */
/**********************************************************************************************************************
 *  END OF FILE: Dem_DebounceBase_Interface.h
 *********************************************************************************************************************/
