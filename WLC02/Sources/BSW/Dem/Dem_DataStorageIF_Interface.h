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
 *  \defgroup   Dem_DataStorageIF DataStorageIF
 *  \{
 *  \file       Dem_DataStorageIF_Interface.h
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

#if !defined (DEM_DATASTORAGEIF_INTERFACE_H)
#define DEM_DATASTORAGEIF_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DataStorageIF_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DataStorageIF_Properties Properties
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
 * \defgroup Dem_DataStorageIF_Private Private Methods
 * \{
 */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_GetDidNVSize
 *****************************************************************************/
/*!
 * \brief         Sums up size of all non-volatile stored data elements
 *
 * \details       Sums up size of all non-volatile stored data elements
 *
 * \param[in]     DidIndex
 *                Unique handle of the DID
 *
 * \return        Number of bytes used in NV-Ram for the DID
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DataStorageIF_GetDidNVSize(
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
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
 * \defgroup Dem_DataStorageIF_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_PrestorageApplyGlobalSRec
 *****************************************************************************/
/*!
 * \brief         Copies a prestored global snapshot for an event
 *
 * \details       This function copies the prestored data only if a prestored
 *                entry has been locked for the event. Otherwise, this function
 *                does not modify the destination buffer.
 *
 * \param[out]    DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \return        TRUE
 *                Data has been copied
 * \return        FALSE
 *                No data has been copied
 *
 * \pre           A Prestorage entry has been locked
 * \config        DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON &&
 *                DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorageIF_PrestorageApplyGlobalSRec(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_PrestorageApplySRec
 *****************************************************************************/
/*!
 * \brief         Copies a prestored snapshot for an event
 *
 * \details       This function copies the prestored data only if a prestored
 *                entry has been locked for the event. Otherwise, this function
 *                does not modify the destination buffer.
 *
 * \param[out]    DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \return        TRUE
 *                Data has been copied
 * \return        FALSE
 *                No data has been copied
 *
 * \pre           A Prestorage entry has been locked
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON &&
 *                DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorageIF_PrestorageApplySRec(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_PrestorageApplyObdIIFF
 *****************************************************************************/
/*!
 * \brief         Copies a prestored OBD freeze frame for an event
 *
 * \details       This function copies the prestored data only if a prestored
 *                entry has been locked for the event. Otherwise, this function
 *                does not modify the destination buffer.
 *
 * \param[out]    DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \return        TRUE
 *                Data has been copied
 * \return        FALSE
 *                No data has been copied
 *
 * \pre           A Prestorage entry has been locked
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON &&
 *                DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorageIF_PrestorageApplyObdIIFF(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_PrestorageApplyWwhObdFF
 *****************************************************************************/
/*!
 * \brief         Copies a prestored WWH-OBD freeze frame for an event
 *
 * \details       This function copies the prestored data only if a prestored
 *                entry has been locked for the event. Otherwise, this function
 *                does not modify the destination buffer.
 *
 * \param[out]    DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \return        TRUE
 *                Data has been copied
 * \return        FALSE
 *                No data has been copied
 *
 * \pre           A Prestorage entry has been locked
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON &&
 *                DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorageIF_PrestorageApplyWwhObdFF(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_PrestorageApplyJ1939FF
 *****************************************************************************/
/*!
 * \brief         Copies a prestored J1939 freeze frame for an event (both
 *                normal and expanded)
 *
 * \details       This function copies the prestored data only if a prestored
 *                entry has been locked for the event. Otherwise, this function
 *                does not modify the destination buffer.
 *
 * \param[out]    DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \return        TRUE
 *                Data has been copied
 * \return        FALSE
 *                No data has been copied
 *
 * \pre           A Prestorage entry has been locked
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON &&
 *                DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorageIF_PrestorageApplyJ1939FF(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_CollectObdIIFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Samples an OBD freeze frame for an event.
 *
 * \details       Collect each PID configured for the given event's OBD-II
 *                freeze frame.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \pre           DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectObdIIFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_CollectWwhObdFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Samples a WWH-OBD freeze frame for an event.
 *
 * \details       Collect each DID configured for the given event's
 *                WWH-OBD FreezeFrame.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectWwhObdFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_CollectJ1939FreezeFrame
 *****************************************************************************/
/*!
 * \brief         Samples J1939 freeze frame(s) for an event
 *
 * \details       Collect each DID configured for the given event's J1939
 *                freeze frame(s) (both normal and expanded).
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[out]    DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectJ1939FreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_CollectGlobalSnapshot
 *****************************************************************************/
/*!
 * \brief         Samples global snapshot record of an event
 *
 * \details       Samples global snapshot record of an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectGlobalSnapshot(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_CollectSnapshot
 *****************************************************************************/
/*!
 * \brief         Samples a snapshot for an event
 *
 * \details       Samples a snapshot for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectSnapshot(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_CollectERec
 *****************************************************************************/
/*!
 * \brief         Samples extended data record for an event
 *
 * \details       Samples extended data record for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DidIndex
 *                Unique handle of the DID
 * \param[in,out] DestinationBuffer
 *                Pointer to the destination buffer structure to store the data
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_ERECS == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectERec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_DidIndexType,AUTOMATIC) DidIndex,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_CopyTimeSeriesNormalDids
 *****************************************************************************/
/*!
 * \brief         Copy time series samples from the normal rate sample ringbuffer
 *
 * \details       Copy time series samples from the normal rate sample ringbuffer
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     SourceIndex
 *                RingBuffer Index to copy. 0: Oldest Sample
 * \param[out]    DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CopyTimeSeriesNormalDids(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  SourceIndex,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_CopyTimeSeriesFastDids
 *****************************************************************************/
/*!
 * \brief         Copy time series samples from the fast rate sample ringbuffer
 *
 * \details       Copy time series samples from the fast rate sample ringbuffer
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     SourceIndex
 *                RingBuffer Index to copy. 0: Oldest Sample
 * \param[out]    DestinationBuffer
 *                Pointer to the buffer to store the data
 * \param[in]     BufferSize
 *                Size of the destination buffer
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CopyTimeSeriesFastDids(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  SourceIndex,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_CollectTimeSeriesNormalSamples
 *****************************************************************************/
/*!
 * \brief         Collect time series samples of normal rate
 *
 * \details       Collect time series samples of normal rate
 *
 * \pre           timer for normal rate has expired
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectTimeSeriesNormalSamples(
  void
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 * Dem_DataStorageIF_CollectTimeSeriesFastSamples
 *****************************************************************************/
/*!
 * \brief         Collect time series samples of fast rate
 *
 * \details       Collect time series samples of fast rate
 *
 * \pre           timer for fast rate has expired
 * \config        DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectTimeSeriesFastSamples(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DATASTORAGEIF_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DataStorageIF_Interface.h
 *********************************************************************************************************************/
