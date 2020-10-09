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
 *  \defgroup   Dem_Data Data
 *  \{
 *  \file       Dem_Data_Interface.h
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

#if !defined (DEM_DATA_INTERFACE_H)
#define DEM_DATA_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Data_Types.h"
#include "Dem_DataReportIF_Types.h"
#include "Dem_Mem_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Data_Properties Properties
 * \{
 */

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
 * \defgroup Dem_Data_Private Private Methods
 * \{
 */

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
 * \defgroup Dem_Data_Public Public Methods
 * \{
 */

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
* Dem_Data_Calc_Pid01_MonitorCompleted
*****************************************************************************/
/*!
* \brief         Calculates Pid01 monitor completed value for given Readiness 
*                Group
*
* \details       Calculates Pid01 monitor completed value for given Readiness 
*                Group
*
* \param[in]     ReadinessGroup
*                OBD Readiness Group
*
* \pre           -
* \config        DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE) Dem_Data_Calc_Pid01_MonitorCompleted(
  CONST(uint8, AUTOMATIC)  ReadinessGroup
  );
#endif


#if (DEM_FEATURE_NEED_PID41_MMONLY_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_Data_GetPid41
 *****************************************************************************/
/*!
 * \brief         Calculates Value of PID41
 *
 * \details       Calculates Byte B, C and D Of PID41
 *                (A = HiHi, B = HiLo, C = LoHi, D = LoLo)
 *
 * \param[out]    PID41value
 *                Pointer to PID41 data buffer
 * \param[in]     BufferSize
 *                Size of PID41 data buffer
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID41_MMONLY_CALCULATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_GetPid41(
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID41value,
  CONST(uint8, AUTOMATIC) BufferSize
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID41 == STD_ON) && (DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_OFF)
/* ****************************************************************************
 * Dem_Data_GetPid41ComprehensiveOnly
 *****************************************************************************/
/*!
 * \brief         Calculates Value of PID41
 *
 * \details       Calculates comprehensive component supported and completed
 *                Bit in Byte B
 *                (A= HiHi, B = HiLo, C = LoHi, D = LoLo)
 *
 * \param[out]    PID41value
 *                Pointer to PID41 data buffer
 * \param[in]     BufferSize
 *                Size of PID41 data buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON &&
 *                DEM_FEATURE_NEED_OBD == STD_ON &&
 *                DEM_CFG_SUPPORT_PID41 == STD_ON &&
 *                DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_OFF
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_GetPid41ComprehensiveOnly(
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID41value,
  CONST(uint8, AUTOMATIC) BufferSize
  );
#endif

#if ( (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) || (DEM_FEATURE_NEED_PID41_MMONLY_CALCULATION == STD_ON) )
/* ****************************************************************************
 * Dem_Data_TestReadinessGroupCompleted
 *****************************************************************************/
/*!
 * \brief         Checks if Readiness Group is completed
 *
 * \details       Checks if Readiness Group is completed by evaluating 
 *                passed completed mask
 *
 * \param[in]     ReadinessGroup
 *                OBD Readiness Group
 * \param[in]     Pid01CompletedMask
 *                Readiness Group completed mask
 *
 * \return        TRUE
 *                Readiness group is completed
 * \return        FALSE
 *                Readiness group is not completed
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON ||
 *                DEM_FEATURE_NEED_PID41_MMONLY_CALCULATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Data_TestReadinessGroupCompleted(
  CONST(uint8, AUTOMATIC)  ReadinessGroup,
  CONST(uint32, AUTOMATIC)  Pid01CompletedMask
  );
#endif

#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_Data_TestReadinessGroupDisabled
 *****************************************************************************/
/*!
 * \brief         Checks if Readiness Group is disabled
 *
 * \details       Checks if Readiness Group is disabled
 *
 * \param[in]     ReadinessGroup
 *                OBD Readiness Group
 *
 * \return        TRUE
 *                Readiness group is disabled
 * \return        FALSE
 *                Readiness group is enabled
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Data_TestReadinessGroupDisabled(
  CONST(uint8, AUTOMATIC)  ReadinessGroup
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Data_PermanentEntryAdd
 *****************************************************************************/
/*!
 * \brief         Stores an event to permanent memory
 *
 * \details       If a free slot is available in the permanent memory, this
 *                function stores a permanent entry for the given event.
 *
 *                This function maps combined events to their master event, so
 *                any event can be passed.
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
Dem_Data_PermanentEntryAdd(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_TimeSeriesData_EntryInit
 *****************************************************************************/
/*!
 * \brief         Initializes a time series entry
 *
 * \details       Initializes a time series entry
 *
 * \param[in]     TimeSeriesEntry
 *                Pointer to the time series entry
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_TimeSeriesData_EntryInit(
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  TimeSeriesEntry
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_PAST == STD_ON)
/* ****************************************************************************
 * Dem_Data_StoreTimeSeriesPastSamples
 *****************************************************************************/
/*!
 * \brief         Store past samples for given event
 *
 * \details       Store past samples for given event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           time series entry allocated for event
 * \config        DEM_FEATURE_NEED_TIME_SERIES_PAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_StoreTimeSeriesPastSamples(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FUTURE == STD_ON)
/* ****************************************************************************
 * Dem_Data_StoreTimeSeriesFutureSamples
 *****************************************************************************/
/*!
 * \brief         Store future samples for all time series entries
 *
 * \details       Store future samples for all time series entries
 *
 * \param[in]     SampleUpdate
 *                Indicates if timers for normal or fast rate have expired
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FUTURE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_StoreTimeSeriesFutureSamples(
  CONST(uint8, AUTOMATIC)  SampleUpdate
  );
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON)
/* ****************************************************************************
 * Dem_Data_StoreTimeSeriesNormalFutureSamples
 *****************************************************************************/
/*!
 * \brief         Store future normal samples for given entry
 *
 * \details       Store future normal samples for given entry
 *
 * \param[in]     Entry
 *                Time Series Entry
 * \param[in]     EntryIndex
 *                Index of Time Series Entry
 *
 * \return        TRUE
 *                Entry has changed
 * \return        FALSE
 *                Entry has not changed
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Data_StoreTimeSeriesNormalFutureSamples(
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  Entry,
  CONST(uint8, AUTOMATIC)  EntryIndex
  );
#endif

#if (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON)
/* ****************************************************************************
 * Dem_Data_StoreTimeSeriesFastFutureSamples
 *****************************************************************************/
/*!
 * \brief         Store future fast samples for given entry
 *
 * \details       Store future fast samples for given entry
 *
 * \param[in]     Entry
 *                Time Series Entry
 * \param[in]     EntryIndex
 *                Index of Time Series Entry
 *
 * \return        TRUE
 *                Entry has changed
 * \return        FALSE
 *                Entry has not changed
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Data_StoreTimeSeriesFastFutureSamples(
  CONST(Dem_Mem_TimeSeriesEntryPtrType, AUTOMATIC)  Entry,
  CONST(uint8, AUTOMATIC)  EntryIndex
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_Data_ERecAllDataElementsStored
 *****************************************************************************/
/*!
 * \brief         Tests if the internal data elements are stored
 *
 * \details       Tests if the internal data elements of an extended data record 
 *                are stored
 *
 * \param[in]     DidIndex
 *                Handle to DID descriptor table
 * \param[in]     ReadoutBufferId
 *                Handle to readout buffer
 *
 * \return        TRUE
 *                The data elements are stored
 * \return        FALSE
 *                The data elements are not stored
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Data_ERecAllDataElementsStored(
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Data_TimeSeriesSRecCount
 *****************************************************************************/
/*!
 * \brief         Counts the number of snapshot records stored in a time series
 *                entry
 *
 * \details       Counts the number of snapshot records stored in a time series
 *                entry
 *
 * \param[in]     TimeSeriesEntry
 *                Pointer to the time series entry
 *
 * \return        Number of stored time series snapshot records
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Data_TimeSeriesSRecCount(
  CONST(Dem_Mem_ConstTimeSeriesEntryPtrType, AUTOMATIC)  TimeSeriesEntry
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Data_TimeSeriesSRecIsStored
 *****************************************************************************/
/*!
 * \brief         Tests whether a time series snapshot record is currently stored
 *
 * \details       Tests whether a time series snapshot record is currently stored
 *
 * \param[in]     TimeSeriesEntry
 *                Pointer to the time series entry
 * \param[in]     RecordNumber
 *                Snapshot record number
 *
 * \return        TRUE
 *                The record is stored
 * \return        FALSE
 *                The record is not stored
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Data_TimeSeriesSRecIsStored(
  CONST(Dem_Mem_ConstTimeSeriesEntryPtrType, AUTOMATIC)  TimeSeriesEntry,
  CONST(uint8, AUTOMATIC)  RecordNumber
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Data_TimeSeriesSRecIsValid
 *****************************************************************************/
/*!
 * \brief         Tests whether a time series snapshot record number is valid
 *
 * \details       Tests whether a time series snapshot record number is valid
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     RecordNumber
 *                Snapshot record number
 *
 * \return        TRUE
 *                The record number is valid
 * \return        FALSE
 *                The record number is invalid
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Data_TimeSeriesSRecIsValid(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Data_TimeSeriesGetNextValidSRec
 *****************************************************************************/
/*!
 * \brief         Gets the next valid time series snapshot record number
 *
 * \details       Gets the next valid time series snapshot record number
 *
 * \param[in]     TimeSeriesEntry
 *                Pointer to the time series entry
 * \param[in]     RecordNumber
 *                Snapshot record number
 *
 * \return        Next valid record number larger than the given record number
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON && DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Data_TimeSeriesGetNextValidSRec(
  CONST(Dem_Mem_ConstTimeSeriesEntryPtrType, AUTOMATIC)  TimeSeriesEntry,
  CONST(uint8, AUTOMATIC)  RecordNumber
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Data_PermanentEntryUpdate
 *****************************************************************************/
/*!
 * \brief         Processes the permanent memory state update.
 *
 * \details       This function transitions the permanent memory states at the
 *                end of a driving cycle.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     OldDtcStatus
 *                Dtc status before DCY restart
 * \param[in]     NewDtcStatus
 *                Dtc status after DCY restart
 *
 * \pre           The passed event must be a master event
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_PermanentEntryUpdate(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  OldDtcStatus,
  CONST(uint8, AUTOMATIC)  NewDtcStatus
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Data_PermanentEntryClear
 *****************************************************************************/
/*!
 * \brief         Processes clearing a permanent DTC
 *
 * \details       Processes clearing a permanent DTC
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     ProcessClearDTC
 *                TRUE  Function is called from ClearDTC processing context
 *                FALSE Function is not called from ClearDTC processing context
 *
 * \pre           The passed event must be a master event
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_PermanentEntryClear(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)   ProcessClearDTC
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Data_PermanentEntryRemove
 *****************************************************************************/
/*!
 * \brief         Frees a permanent memory index
 *
 * \details       Frees a permanent memory index
 *
 * \param[in]     PermanentIndex
 *                Index of a permanent entry
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Data_PermanentEntryRemove(
  CONST(uint8, AUTOMATIC)  PermanentIndex
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Data_PermanentEntryFind
 *****************************************************************************/
/*!
 * \brief         Searches an eventId in the permanent memory
 *
 * \details       Searches an eventId in the permanent memory
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Index of the permanent entry used by the event. If no entry
 *                is found, Dem_Cfg_GlobalPermanentMaxCount() is returned.
 *
 * \pre           The passed event must be a master event
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Data_PermanentEntryFind(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif



#if (DEM_FEATURE_NEED_OBD_ODOMETER == STD_ON)
/* ****************************************************************************
 * Dem_Data_GetObdOdometer
 *****************************************************************************/
/*!
 * \brief         Requests the OBD Odometer from application and composes the
 *                returned data into an uint32 element.
 *
 * \details       Requests the OBD Odometer from application and composes the
 *                returned data into an uint32 element.
 *
 * \param[out]    Odometer
 *                Pointer to receive the value
 *
 * \return        E_OK
 *                An odometer value was successfully retrieved.
 * \return        E_NOT_OK
 *                No odometer could be retrieved. The Odometer parameter is
 *                initialized to 0.
 *
 * \pre           RTE is started (if using RTE)
 * \config        DEM_FEATURE_NEED_OBD_ODOMETER == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Data_GetObdOdometer(
  CONSTP2VAR(uint32, AUTOMATIC, DEM_VAR_NOINIT)  Odometer
  );
#endif

/* ****************************************************************************
 * Dem_Data_InitDestinationBuffer
 *****************************************************************************/
/*!
 * \brief         Initialize passed destination buffer structure
 *
 * \details       Initialize passed destination buffer structure
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure that shall be initialized
 * \param[in]     Buffer
 *                Valid buffer that will be assigned to destination buffer structure
 * \param[in]     Size
 *                Size of passed buffer
 *
 * \pre           DestinationBuffer is a valid pointer
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_InitDestinationBuffer(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_SharedDataPtrType, AUTOMATIC) Buffer,
  CONST(uint16, AUTOMATIC) Size
  );

/* ****************************************************************************
 * Dem_Data_IncrementWriteIndexDestinationBuffer
 *****************************************************************************/
/*!
 * \brief         Increment write index of passed Destination buffer
 *
 * \details       Increment write index of passed destination buffer if available 
 *                buffer size is sufficient
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 * \param[in]     Size
 *                Value by which write index shall be incremented
 *
 * \return        E_OK
 *                Write index was incremented
 * \return        E_NOT_OK
 *                Write index not incremented due to insufficient available buffer size
 *
 * \pre           DestinationBuffer is a valid pointer
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Data_IncrementWriteIndexDestinationBuffer(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC) Size
  );

/* ****************************************************************************
 * Dem_Data_ResetWriteIndexDestinationBuffer
 *****************************************************************************/
/*!
 * \brief         Reset write index
 *
 * \details       Reset write index of destination buffer structure
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 *
 * \pre           DestinationBuffer is a valid pointer
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_ResetWriteIndexDestinationBuffer(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );

/* ****************************************************************************
 * Dem_Data_WriteDestinationBuffer
 *****************************************************************************/
/*!
 * \brief         Copy data to destination buffer
 *
 * \details       Copy data from source buffer to destination buffer if available 
 *                buffer size is sufficient
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 * \param[in]     SourceBuffer
 *                Pointer to source buffer
 * \param[in]     Size
 *                Number of bytes to be copied
 *
 * \pre           DestinationBuffer is a valid pointer
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBuffer(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC) SourceBuffer,
  CONST(uint16, AUTOMATIC) Size
  );

/* ****************************************************************************
 * Dem_Data_WriteDestinationBufferAtIndex
 *****************************************************************************/
/*!
 * \brief         Copy data to destination buffer
 *
 * \details       Copy passed uint8 data to destination buffer at passed write index
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 * \param[in]     WriteIndex
 *                Write index where to copy to
 * \param[in]     Data
 *                Data to be copied
 *
 * \pre           DestinationBuffer is a valid pointer
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferAtIndex(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC) WriteIndex,
  CONST(uint8, AUTOMATIC) Data
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
* Dem_Data_WriteDestinationBufferUint8
*****************************************************************************/
/*!
 * \brief         Copy data to destination buffer
 *
 * \details       Copy passed uint8 data to destination buffer 
 *                if available buffer size is sufficient
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 * \param[in]     Data
 *                Data to be copied
 *
 * \pre           DestinationBuffer is a valid pointer
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferUint8(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint8, AUTOMATIC) Data
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
* Dem_Data_WriteDestinationBufferUint16
*****************************************************************************/
/*!
 * \brief         Copy data to destination buffer
 *
 * \details       Copy passed uint16 data in motorola byte order to destination buffer 
 *                if available buffer size is sufficient
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 * \param[in]     Data
 *                Data to be copied
 *
 * \pre           DestinationBuffer is a valid pointer
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferUint16(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC) Data
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
* Dem_Data_WriteDestinationBufferUint16_Intel
*****************************************************************************/
/*!
 * \brief         Copy data to destination buffer
 *
 * \details       Copy passed uint16 data in intel byte order to destination buffer 
 *                if available buffer size is sufficient
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 * \param[in]     Data
 *                Data to be copied
 *
 * \pre           DestinationBuffer is a valid pointer
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferUint16_Intel(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC) Data
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
* Dem_Data_WriteDestinationBufferUint32
*****************************************************************************/
/*!
 * \brief         Copy data to destination buffer
 *
 * \details       Copy passed uint32 data in motorola byte order to destination buffer 
 *                if available buffer size is sufficient
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 * \param[in]     Data
 *                Data to be copied
 *
 * \pre           DestinationBuffer is a valid pointer
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferUint32(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint32, AUTOMATIC) Data
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
* Dem_Data_WriteDestinationBufferUint32_Intel
*****************************************************************************/
/*!
 * \brief         Copy data to destination buffer
 *
 * \details       Copy passed uint32 data in intel byte order to destination buffer 
 *                if available buffer size is sufficient
 *
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 * \param[in]     Data
 *                Data to be copied
 *
 * \pre           DestinationBuffer is a valid pointer
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferUint32_Intel(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint32, AUTOMATIC) Data
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DATA_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Data_Interface.h
 *********************************************************************************************************************/
