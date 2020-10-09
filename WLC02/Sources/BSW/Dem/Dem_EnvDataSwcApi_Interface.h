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
/*! \ingroup    Dem_API
 *  \defgroup   Dem_EnvDataSwcApi EnvDataSwcApi
 *  \{
 *  \file       Dem_EnvDataSwcApi_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    The EnvDataSwcApi subcomponent contains APIs to read the environmental data (ExtendedData, FreezeFrame...) 
                for SWC APIs.
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

#if !defined (DEM_ENVDATASWCAPI_INTERFACE_H)
#define DEM_ENVDATASWCAPI_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_EnvDataSwcApi_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_EnvDataSwcApi_Properties Properties
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
 * \defgroup Dem_EnvDataSwcApi_Private Private Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyPidFromObdIIFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Extracts the OBD freezeframe, or a single PID from it
 *
 * \details       The stored OBD freezeframe data of an event is written to
 *                DestBuffer in no particular format (raw hex).
 *
 * \param[in]     MasterEventId
 *                Unique handle of the UDS DTC.
 *                The MasterEventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DataId
 *                Return only the data of this PID.
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is currently not stored for the requested event
 *                or
 *                the event is not OBD relevant
 *                or
 *                the PID is undefined for the event.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer size is too small.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyPidFromObdIIFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  MasterEventId,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyDidFromWwhObdFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Extracts the WWH-OBD freezeframe, or a single DID from it
 *
 * \details       The stored WWH-OBD freezeframe data of an event is written to
 *                DestBuffer in no particular format (raw hex).
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        E_NOT_OK
 *                Operation could not be performed, e.g. when the data is
 *                concurrently updated.
 * \return        DEM_E_NODATAAVAILABLE
 *                The data is currently not stored for the requested event
 *                or
 *                the event is not WWH-OBD relevant
 *                or
 *                the requested data identifier is undefined for the event.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer size is too small.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyDidFromWwhObdFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyDidFromTimeSeriesSRec
 *****************************************************************************/
/*!
 * \brief         Extracts a time series snapshot record, or a single DID from it
 *
 * \details       The stored time series snapshot data of the event is written to
 *                DestBuffer in no particular format.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     RecordNumber
 *                Snapshot record number.
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[in,out] DestinationBuffer
 *                Pointer to destination buffer structure
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer
 * \return        E_NOT_OK
 *                Operation could not be performed, e.g. when the data is
 *                concurrently updated.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is currently not stored for the requested event
 *                or
 *                the RecordNumber for the given event is undefined
 *                or
 *                the data indentifier within the requested record is
 *                undefined.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer size is too small.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyDidFromTimeSeriesSRec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyDidFromGlobalSRec
 *****************************************************************************/
/*!
 * \brief         Extracts requested DID of global snapshot record
 *
 * \details       The stored global snapshot data of the event is written to
 *                DestBuffer in no particular format.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        E_NOT_OK
 *                The requested data was not copied due to an error. E.g. when
 *                called with invalid arguments, or the data is concurrently
 *                updated.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested event data is not currently stored (but the
 *                request was valid)
 *                or
 *                the requested DataId is not supported by the event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyDidFromGlobalSRec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyDidFromSRec
 *****************************************************************************/
/*!
 * \brief         Extracts a snapshot record, or a single DID from it
 *
 * \details       The stored snapshot data of the event is written to
 *                DestBuffer in no particular format.
 *                The record number 0xff (in this case: most recent snapshot)
 *                is supported only in configurations using "calculated" record
 *                numbers.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     RecordNumber
 *                Snapshot record number.
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        E_NOT_OK
 *                The requested data was not copied due to an error. E.g. when
 *                called with invalid arguments, or the data is concurrently
 *                updated.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested event data is not currently stored (but the
 *                request was valid)
 *                or
 *                the requested RecordNumber is not supported by the event
 *                or
 *                the requested DataId is not supported by the event.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyDidFromSRec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_EnvDataSwcApi_CopyERecs
 *****************************************************************************/
/*!
 * \brief         Extract an extended data record for an event
 *
 * \details       Read and copy the stored extended data record of an event. The
 *                data is written to DestBuffer in no particular format.
 *                The record numbers 0xfe and 0xff are not supported.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     RecordNumber
 *                Extended record number
 * \param[in,out] DestinationBuffer
 *                Pointer to DestinationBuffer context
 *
 *
 * \return        E_OK
 *                Operation was successful.
 *                The requested data was copied to the destination buffer.
 * \return        E_NOT_OK
 *                Operation could not be performed, e.g. when the data is
 *                concurrently updated.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested event data is not currently stored (but the
 *                request was valid) OR The requested record number is not
 *                supported by the event.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer size is too small.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_CopyERecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer                                                         /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
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
 * \defgroup Dem_EnvDataSwcApi_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_EnvDataSwcApi_GetEventFreezeFrameDataEx
 *****************************************************************************/
/*!
 * \brief         Implementation of SWC API Dem_GetEventFreezeFrameDataEx().
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 *                Dem_GetEventFreezeFrameDataEx() copies data from the stored
 *                snapshot data of an event into DestBuffer, following no
 *                particular format and contains no header-information like
 *                RecordNumber or DataId.
 *
 *                Only the DID data actually stored in the event storage is
 *                returned here. If the Dcm adds additional parts to a DID,
 *                these will be missing.
 *
 *                The record number 0xff is a magic value used to read the most
 *                recently stored record. This is only supported in case record
 *                numbers are calculated (DemTypeOfFreezeFrameRecordNumeration).
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[in]     RecordNumber
 *                SnapshotRecord number to read. Contrary to usual usage, 0xFF
 *                returns the most recently stored record. (See notes.)
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[out]    DestBuffer
 *                Buffer to receive the data.
 * \param[in,out] BufSize
 *                In: Size of the buffer.
 *                Out: Number of bytes written.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is currently not stored for the requested event.
 *                or
 *                the requested RecordNumber is not supported for the given
 *                event
 *                or
 *                the requested data identifier is not supported within the
 *                requested record (freeze frame).
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *                or
 *                the requested data is currently not accessible (e.g. in case
 *                of asynchronous preempted data retrieval from application).
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer is too small.
 *
 * \pre           RTE is active (if RTE is used).
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_GetEventFreezeFrameDataEx(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(uint16, AUTOMATIC)  DataId,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  );

/* ****************************************************************************
 * Dem_EnvDataSwcApi_GetEventExtendedDataRecordEx
 *****************************************************************************/
/*!
 * \brief         Implementaion of SWC API Dem_GetEventExtendedDataRecordEx().
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 *                Dem_GetEventExtendedDataRecordEx() copies extended data
 *                available or stored for an event into the passed buffer.
 *                This is particularly useful to retrieve statistic data, like
 *                occurrence counter or aging counter - if these are mapped to
 *                an extended data record.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[in]     RecordNumber
 *                Extended DataRecord number to read. The record numbers 0xfe
 *                and 0xff are reserved.
 * \param[out]    DestBuffer
 *                Buffer to receive the data.
 * \param[in,out] BufSize
 *                In:  Size of the buffer.
 *                Out: Number of bytes written.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is not currently stored for the requested event
 *                or
 *                the requested data was not copied due to an undefined
 *                RecordNumber for the given event.
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *                or
 *                the requested data is currently not accessible (e.g. in case
 *                of asynchronous preempted data retrieval from application).
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer is too small.
 *
 * \pre           RTE is active (if RTE is used).
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_EnvDataSwcApi_GetEventExtendedDataRecordEx(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_ENVDATASWCAPI_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EnvDataSwcApi_Interface.h
 *********************************************************************************************************************/
