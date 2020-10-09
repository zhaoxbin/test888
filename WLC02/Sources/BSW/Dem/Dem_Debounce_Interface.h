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
/*! \ingroup    Dem_Satellite
 *  \defgroup   Dem_Debounce Debounce Interface (Facade)
 *  \{
 *  \file       Dem_Debounce_Interface.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public interface of Debounce subcomponent
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

#if !defined (DEM_DEBOUNCE_INTERFACE_H)
#define DEM_DEBOUNCE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Debounce_Types.h"

                                                           /* Required types */
/* ------------------------------------------------------------------------- */
#include "Dem_DebouncingState_Types.h"
#include "Dem_Satellite_Types.h"
#include "Dem_SatelliteData_Types.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION INTERFACE
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Debounce_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Debounce_RemoveSimilarConditionQualifier
 *****************************************************************************/
/*!
 * \brief         Remove similar condition qualifier for debouncing calculation.
 *
 * \details       Remove similar condition qualifier for debouncing calculation.
 *
 * \param[in]     MonitorTrigger
 *                The reported MonitorTrigger.
 *
 * \return        The monitor trigger mapped to the basic event status type.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventStatusType, DEM_CODE)
Dem_Debounce_RemoveSimilarConditionQualifier(
  CONST(Dem_EventStatusType, AUTOMATIC)  MonitorTrigger
  );

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
 * \defgroup Dem_Debounce_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Debounce_GetDebouncingResult
 *****************************************************************************/
/*!
 * \brief         Update and return the debouncing data.
 *
 * \details       Update and return the debouncing data.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to query.
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
Dem_Debounce_GetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_Debounce_ResetDebouncing
 *****************************************************************************/
/*!
 * \brief         Reset the debouncing status and data.
 *
 * \details       Reset the debouncing status and data.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to query.
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
Dem_Debounce_ResetDebouncing(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_Debounce_FreezeDebouncing
 *****************************************************************************/
/*!
 * \brief         Freeze the debouncing status and data.
 *
 * \details       Freeze the debouncing status and data.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to query.
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
Dem_Debounce_FreezeDebouncing(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_Debounce_CalculateDebouncing
 *****************************************************************************/
/*!
 * \brief         Calculates the debouncing value.
 *
 * \details       Calculates the debouncing value.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to query.
 *
 * \return        TRUE The debouncing object was updated
 * \return        FALSE The debouncing object was not updated due to errors
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_CalculateDebouncing(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Debounce_SetMonitorTrigger
 *****************************************************************************/
/*!
 * \brief         Set the MonitorTrigger of the given debounce object.
 *
 * \details       Set the MonitorTrigger of the given debounce object.
 *
 * \param[out]    DebounceInfoPtr
 *                The object to query.
 *
 * \param[in]     MonitorTrigger
 *                The monitor status to set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Debounce_SetMonitorTrigger(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_EventStatusType, AUTOMATIC)  MonitorTrigger
  );

/* ****************************************************************************
 * Dem_Debounce_GetMonitorTrigger()
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
Dem_Debounce_GetMonitorTrigger(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Debounce_TestRequestFdcProcessing()
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
Dem_Debounce_TestRequestFdcProcessing(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Debounce_TestFdcThresholdExceeded()
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
Dem_Debounce_TestFdcThresholdExceeded(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Debounce_TestMaximumFdcExceeded()
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
Dem_Debounce_TestMaximumFdcExceeded(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Debounce_GetFaultDetectionCounter
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Debounce_GetFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  );

/* ****************************************************************************
 * Dem_Debounce_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the maximum fault detection counter of an event.
 *
 * \details       Calculates the maximum fault detection counter of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to read from.
 *
 * \return        The maximum FaultDetectionCounter
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Debounce_GetMaxFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Debounce_GetDebouncingState
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
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_Debounce_GetDebouncingState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Debounce_TestDebouncingChanged
 *****************************************************************************/
/*!
 * \brief         Get the 'changed state' of the debounce status.
 *
 * \details       Get the 'changed state' of the debounce status.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to query.
 *
 * \return        Whether debouncing data changed (TRUE) or not (FALSE).
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestDebouncingChanged(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Debounce_DebounceInfoInit
 *****************************************************************************/
/*!
 * \brief         Initializes a debounce descriptor
 *
 * \details       This function initializes the basic common fields of a
 *                debounce descriptor. State information remains uninitialized
 *                as it is not known without context.
 *                The generic fields that will be set here are 'EventId' and
 *                'FunctionTable'.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    DebounceInfoData
 *                The debouncing element used as storge for the initialized
 *                object.
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 *
 * \returns       The initialized object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceBase_InfoPtrType, DEM_CODE)
Dem_Debounce_DebounceInfoInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_Debounce_InfoType, AUTOMATIC, AUTOMATIC)  DebounceInfoData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_Debounce_TestQualifiedResult
 *****************************************************************************/
/*!
 * \brief         Determine the qualification of the current test result.
 *
 * \details       Determine the qualification of the current test result.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \return        TRUE
 *                The monitor result was qualified
 * \return        FALSE
 *                The monitor result was not qualified
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestQualifiedResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceSat_PreInit
 *****************************************************************************/
/*!
 * \brief         Preinitialize the debouncing of a monitor.
 *
 * \details       Preinitialize the debouncing of a monitor.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 * \param[in]     MonitorId
 *                Index of the monitor
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceSat_PreInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
/* ****************************************************************************
 * Dem_Debounce_RestoreDebounceValue
 *****************************************************************************/
/*!
 * \brief         Restore the debouncing value of an event.
 *
 * \details       Restore the debouncing value of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 * \param[in]     Value
 *                The value to be restored
 * \param[in]     ExpectedThreshold
 *                Specifies whether the negative threshold is expected to be
 *                reached (TRUE), or the positive one (FALSE).
 *
 * \return        Data object holding the modified debounce data
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 * \config        DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_RestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  );
#endif

/* ****************************************************************************
 * Dem_Debounce_InvalidCalculate
 *****************************************************************************/
/*!
 * \brief         Fallback implementation, instead of NULL_PTR.
 *
 * \details       This function will always assert.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *                This function uses no specialization.
 *
 * \return        FALSE
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Debounce_InvalidCalculate(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Debounce_InvalidVoid
 *****************************************************************************/
/*!
 * \brief         Fallback implementation, instead of NULL_PTR.
 *
 * \details       This function will always assert.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *                This function uses no specialization.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Debounce_InvalidVoid(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Debounce_InvalidUpdateMax
 *****************************************************************************/
/*!
 * \brief         Fallback implementation, instead of NULL_PTR
 *
 * \details       This function will always assert.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *                This function uses no specialization.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Debounce_InvalidUpdateMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );


/* ****************************************************************************
 * Dem_Debounce_InvalidGetDebouncingState
 *****************************************************************************/
/*!
 * \brief         Fallback implementation, instead of NULL_PTR.
 *
 * \details       This function will always assert.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *                This function uses no specialization.
 *
 * \return        A default initialized debouncing state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_Debounce_InvalidGetDebouncingState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Debounce_InvalidGetDebouncingResult
 *****************************************************************************/
/*!
 * \brief         Fallback implementation, instead of NULL_PTR.
 *
 * \details       This function will always assert.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *                This function uses no specialization.
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 *
 * \return        Unmodified data passed in as SatelliteData
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_InvalidGetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Debounce_InvalidGetFDC
 *****************************************************************************/
/*!
 * \brief         Fallback implementation, instead of NULL_PTR.
 *
 * \details       This function will always assert.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *                This function uses no specialization.
 * \param[in]     FaultDetectionCounter
 *
 * \return        E_NOT_OK
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Debounce_InvalidGetFDC(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
  );

/* ****************************************************************************
 * Dem_Debounce_InvalidRestoreDebounceValue
 *****************************************************************************/
/*!
 * \brief         Fallback implementation, instead of NULL_PTR.
 *
 * \details       This function will always assert.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to query.
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 * \param[in]     Value
 *                The value to be restored
 * \param[in]     ExpectedThreshold
 *
 * \return        Data object holding the modified debounce data
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_InvalidRestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData,
  CONST(sint16, AUTOMATIC)  Value,
  CONST(boolean, AUTOMATIC)  ExpectedThreshold
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DEBOUNCE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Debounce_Interface.h
 *********************************************************************************************************************/
