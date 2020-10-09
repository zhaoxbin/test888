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
/*! \addtogroup Dem_DataStorageIF
 *  \{
 *  \file       Dem_DataStorageIF_Implementation.h
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

#if !defined (DEM_DATASTORAGEIF_IMPLEMENTATION_H)
#define DEM_DATASTORAGEIF_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DataStorageIF_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Prestore_Interface.h"
#include "Dem_ExtDataElementIF_Implementation.h"
#include "Dem_Mem_Implementation.h"
#include "Dem_Data_Interface.h"
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_DataStorageIF_Properties
 * \{
 */

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
 * \addtogroup Dem_DataStorageIF_Private
 * \{
 */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_GetDidNVSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DataStorageIF_GetDidNVSize(
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  )
{
  Dem_Cfg_DataIndexType lDataIndex;
  Dem_Cfg_DidDataIterType lDataIter;
  uint8 lDidTotalSize;

  lDidTotalSize = 0;
  for (Dem_Cfg_DidDataIterInit(DidIndex, &lDataIter);                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DataIsStoredInNV(lDataIndex) == TRUE)
    {
      switch (Dem_Cfg_DataCallbackType(lDataIndex))
      {
      case DEM_CFG_DATA_FROM_ROOTCAUSE_EVENTID:
      case DEM_CFG_DATA_FROM_CBK:
      case DEM_CFG_DATA_FROM_CBK_WITH_EVENTID:
      case DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT8:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT8:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT16:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT16:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT32:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT32:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL:
      case DEM_CFG_DATA_FROM_SR_PORT_SINT8_N:
      case DEM_CFG_DATA_FROM_SR_PORT_UINT8_N:
          lDidTotalSize += Dem_Cfg_DataSize(lDataIndex);
          break;

      default:
          break;
      }
    }
  }
  return lDidTotalSize;
}
#endif

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
 * \addtogroup Dem_DataStorageIF_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_PrestorageApplyGlobalSRec
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorageIF_PrestorageApplyGlobalSRec(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  boolean lReturnValue;
  Dem_Cfg_PrestorageIndexType lPrestoreLockedIndex;

  lReturnValue = FALSE;

  lPrestoreLockedIndex = Dem_Prestore_GetLockedIndex();
  if (DEM_PRESTORE_INVALID_BUFFER_ENTRY != lPrestoreLockedIndex)
  {
    Dem_MemCpy(DestinationBuffer,                                                                                                /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
               Dem_Prestore_PrestorageEntryGetGlobalSRecDataPtr(lPrestoreLockedIndex),
               BufferSize);

    lReturnValue = TRUE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_PrestorageApplySRec
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorageIF_PrestorageApplySRec(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  boolean lReturnValue;
  Dem_Cfg_PrestorageIndexType lPrestoreLockedIndex;

  lReturnValue = FALSE;

  lPrestoreLockedIndex = Dem_Prestore_GetLockedIndex();
  if (DEM_PRESTORE_INVALID_BUFFER_ENTRY != lPrestoreLockedIndex)
  {
    Dem_MemCpy(DestinationBuffer,                                                                                                /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
               Dem_Prestore_PrestorageEntryGetSRecDataPtr(lPrestoreLockedIndex),
               BufferSize);

    lReturnValue = TRUE;
  }

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_PrestorageApplyObdIIFF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorageIF_PrestorageApplyObdIIFF(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  boolean lReturnValue;
  Dem_Cfg_PrestorageIndexType lPrestoreLockedIndex;

  lReturnValue = FALSE;

  lPrestoreLockedIndex = Dem_Prestore_GetLockedIndex();
  if (DEM_PRESTORE_INVALID_BUFFER_ENTRY != lPrestoreLockedIndex)
  {
    Dem_MemCpy(DestinationBuffer,                                                                                                /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
               Dem_Prestore_PrestorageEntryGetObdIIFFDataPtr(lPrestoreLockedIndex),
               BufferSize);

    lReturnValue = TRUE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_PrestorageApplyWwhObdFF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorageIF_PrestorageApplyWwhObdFF(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  boolean lReturnValue;
  Dem_Cfg_PrestorageIndexType lPrestoreLockedIndex;

  lReturnValue = FALSE;

  lPrestoreLockedIndex = Dem_Prestore_GetLockedIndex();
  if (DEM_PRESTORE_INVALID_BUFFER_ENTRY != lPrestoreLockedIndex)
  {
    Dem_MemCpy(DestinationBuffer,                                                                                                /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
               Dem_Prestore_PrestorageEntryGetWwhObdFFDataPtr(lPrestoreLockedIndex),
               BufferSize);

    lReturnValue = TRUE;
  }

  return lReturnValue;
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_PrestorageApplyJ1939FF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataStorageIF_PrestorageApplyJ1939FF(
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  boolean lReturnValue;
  Dem_Cfg_PrestorageIndexType lPrestoreLockedIndex;

  lReturnValue = FALSE;

  lPrestoreLockedIndex = Dem_Prestore_GetLockedIndex();
  if (DEM_PRESTORE_INVALID_BUFFER_ENTRY != lPrestoreLockedIndex)
  {
    Dem_MemCpy(DestinationBuffer,                                                                                                /* PRQA S 0310, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
               Dem_Prestore_PrestorageEntryGetJ1939FFDataPtr(lPrestoreLockedIndex),
               BufferSize);

    lReturnValue = TRUE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_CollectObdIIFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectObdIIFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  Dem_ExtDataElementIF_CollectDidInfoType lCollectDidInfo;
  Dem_Cfg_GlobalPidIterType lPidIter;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize collection context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  Dem_ExtDataElementIF_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */                                                          
                                         ,&lDestinationBuffer
                                         ,EventId);

  for (Dem_Cfg_GlobalPidIterInit(&lPidIter);                                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalPidIterExists(&lPidIter) == TRUE;                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalPidIterNext(&lPidIter))                                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_GlobalPidIterGet(&lPidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElementIF_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_CollectWwhObdFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectWwhObdFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  Dem_ExtDataElementIF_CollectDidInfoType lCollectDidInfo;
  Dem_Data_DestinationBuffer lDestinationBuffer;
  Dem_Cfg_EventObdDidIterType lDidIter;

  /* Initialize collection context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  Dem_ExtDataElementIF_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */  
                                         , &lDestinationBuffer
                                         , EventId);

  for (Dem_Cfg_EventObdDidIterInit(EventId, &lDidIter);                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventObdDidIterExists(&lDidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventObdDidIterNext(&lDidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventObdDidIterGet(&lDidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElementIF_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_CollectJ1939FreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectJ1939FreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  Dem_ExtDataElementIF_CollectDidInfoType lCollectDidInfo;
  Dem_Data_DestinationBuffer lDestinationBuffer;
  Dem_Cfg_EventSPNIterType lSpnIter;

  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  Dem_ExtDataElementIF_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */  
                                         ,&lDestinationBuffer
                                         , EventId);

  if (Dem_Cfg_EventJ1939FFExists(EventId) == FALSE)
  { /* skip the buffer area reserved for standard FreezeFrame */
    (void)  Dem_Data_IncrementWriteIndexDestinationBuffer(lCollectDidInfo.DestinationBuffer, Dem_Cfg_GlobalJ1939FFRawSize());    /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO_DESTINATIONBUFFER */
  }

  for (Dem_Cfg_EventSPNIterInit(EventId, &lSpnIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventSPNIterExists(&lSpnIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventSPNIterNext(&lSpnIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventSPNIterGet(&lSpnIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElementIF_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_CollectGlobalSnapshot
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectGlobalSnapshot(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  Dem_ExtDataElementIF_CollectDidInfoType lCollectDidInfo;
  Dem_Cfg_GlobalSnapshotDidIterType lDidIter;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize collection context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  Dem_ExtDataElementIF_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
                                         ,&lDestinationBuffer
                                         ,EventId);

  for (Dem_Cfg_GlobalSnapshotDidIterInit(&lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalSnapshotDidIterExists(&lDidIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalSnapshotDidIterNext(&lDidIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_GlobalSnapshotDidIterGet(&lDidIter);                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElementIF_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_CollectSnapshot
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectSnapshot(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize
  )
{
  Dem_ExtDataElementIF_CollectDidInfoType lCollectDidInfo;
  Dem_Cfg_EventDidIterType lDidIter;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize collection context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  Dem_ExtDataElementIF_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
                                         ,&lDestinationBuffer
                                         , EventId);

  for (Dem_Cfg_EventDidIterInit(EventId, &lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterExists(&lDidIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterNext(&lDidIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventDidIterGet(&lDidIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElementIF_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }
}
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_CollectERec
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectERec(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_DidIndexType,AUTOMATIC) DidIndex,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Dem_ExtDataElementIF_CollectDidInfoType lCollectDidInfo;

  Dem_ExtDataElementIF_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
                                         ,DestinationBuffer
                                         ,EventId);

  Dem_ExtDataElementIF_CollectStoredDid(&lCollectDidInfo, DidIndex);                                                             /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
}
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_CollectTimeSeriesNormalSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectTimeSeriesNormalSamples(
  void
  )
{
  uint8 lCurrentIndex;
  Dem_ExtDataElementIF_CollectDidInfoType lCollectDidInfo;
  Dem_Cfg_TimeSeriesDidNormalIterType lDidIter;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  lCurrentIndex = Dem_Mem_GetCurrentRingBufferIndexNormal();

  /* Collect all DIDs used in normal rate time series snapshot records and store them into ring buffer */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer,                                                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
                                 Dem_Mem_RingBufferNormalRatePtr(lCurrentIndex), 
                                 Dem_Cfg_GlobalTimeSeriesNormalBufferSize());
  Dem_ExtDataElementIF_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
                                         , &lDestinationBuffer
                                         , DEM_EVENT_INVALID);

  for (Dem_Cfg_TimeSeriesDidNormalIterInit(&lDidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_TimeSeriesDidNormalIterExists(&lDidIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_TimeSeriesDidNormalIterNext(&lDidIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_TimeSeriesDidNormalIterGet(&lDidIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElementIF_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }

  /* update number of written samples in ring buffer */
# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)
  if (Dem_Mem_GetSampleCountNormal() < Dem_Cfg_TimeSeriesPastSamplesNormal())
  {
    Dem_Mem_SetSampleCountNormal(Dem_Mem_GetSampleCountNormal() + 1);
  }

  /* update current index of ring buffer */
  lCurrentIndex = ((lCurrentIndex + 1) % Dem_Cfg_TimeSeriesPastSamplesNormal());
  Dem_Mem_SetCurrentRingBufferIndexNormal(lCurrentIndex);
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_CollectTimeSeriesFastSamples
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CollectTimeSeriesFastSamples(
  void
  )
{
  uint8 lCurrentIndex;
  Dem_ExtDataElementIF_CollectDidInfoType lCollectDidInfo;
  Dem_Data_DestinationBuffer lDestinationBuffer;
  Dem_Cfg_TimeSeriesDidFastIterType lDidIter;

  lCurrentIndex = Dem_Mem_GetCurrentRingBufferIndexFast();

  /* Collect all DIDs used in fast rate time series snapshot records and store them into ring buffer */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer,                                                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
                                 Dem_Mem_RingBufferFastRatePtr(lCurrentIndex), 
                                 Dem_Cfg_GlobalTimeSeriesFastBufferSize());
  Dem_ExtDataElementIF_InitCollectDidInfo(&lCollectDidInfo                                                                       /* SBSW_DEM_CALL_COLLECTDIDINFO_INIT */
                                          ,&lDestinationBuffer
                                          , DEM_EVENT_INVALID);

  for (Dem_Cfg_TimeSeriesDidFastIterInit(&lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_TimeSeriesDidFastIterExists(&lDidIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_TimeSeriesDidFastIterNext(&lDidIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
 {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_TimeSeriesDidFastIterGet(&lDidIter);                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_ExtDataElementIF_CollectStoredDid(&lCollectDidInfo, lDidIndex);                                                          /* SBSW_DEM_POINTER_LOCAL_COLLECTDIDINFO */
  }

# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)
  /* update number of written samples in ring buffer */
  if (Dem_Mem_GetSampleCountFast() < Dem_Cfg_TimeSeriesPastSamplesFast())
  {
    Dem_Mem_SetSampleCountFast(Dem_Mem_GetSampleCountFast() + 1);
  }

  /* update current index of ring buffer */
  lCurrentIndex = ((lCurrentIndex + 1) % Dem_Cfg_TimeSeriesPastSamplesFast());
  Dem_Mem_SetCurrentRingBufferIndexFast(lCurrentIndex);
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_CopyTimeSeriesNormalDids
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CopyTimeSeriesNormalDids(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  SourceIndex,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Cfg_EventDidIterType lDidIter;
  Dem_ConstSharedDataPtrType lSourceBuffer;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize destination buffer context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BufferSize)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)
  if (Dem_Mem_GetSampleCountNormal() < Dem_Cfg_TimeSeriesPastSamplesNormal())
  {
    lSourceBuffer = Dem_Mem_RingBufferNormalRatePtr(SourceIndex);
  }
  else
  {
    lSourceBuffer = Dem_Mem_RingBufferNormalRatePtr(
      (Dem_Mem_GetCurrentRingBufferIndexNormal() + SourceIndex) % Dem_Cfg_TimeSeriesPastSamplesNormal()
      );
  }
# else
  lSourceBuffer = Dem_Mem_RingBufferNormalRatePtr(SourceIndex);
# endif
  for (Dem_Cfg_EventDidIterInit(EventId, &lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterExists(&lDidIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterNext(&lDidIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    uint8 lDidSize;
    uint16 lWriteIndex;

    lDidIndex = Dem_Cfg_EventDidIterGet(&lDidIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lDidSize = Dem_DataStorageIF_GetDidNVSize(lDidIndex);
    lWriteIndex = lDestinationBuffer.WriteIndex;

    if (Dem_Data_IncrementWriteIndexDestinationBuffer(&lDestinationBuffer, lDidSize) == E_OK)                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      Dem_MemCpy(&lDestinationBuffer.Buffer[lWriteIndex],                                                                        /* PRQA S 0311, 0602 */ /* MD_DEM_11.5, MD_DEM_20.2 */ /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
        &lSourceBuffer[Dem_Cfg_DidBufferIndexNormal(lDidIndex)],
        lDidSize);
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES_FAST == STD_ON)
/* ****************************************************************************
 % Dem_DataStorageIF_CopyTimeSeriesFastDids
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataStorageIF_CopyTimeSeriesFastDids(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  SourceIndex,
  CONST(Dem_SharedDataPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC)  BufferSize                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Cfg_EventDidIterType lDidIter;
  Dem_ConstSharedDataPtrType lSourceBuffer;
  Dem_Data_DestinationBuffer lDestinationBuffer;

  /* Initialize destination buffer context */
  Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestinationBuffer, BufferSize);                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BufferSize)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)
  if (Dem_Mem_GetSampleCountFast() < Dem_Cfg_TimeSeriesPastSamplesFast())
  {
    lSourceBuffer = Dem_Mem_RingBufferFastRatePtr(SourceIndex);
  }
  else
  {
    lSourceBuffer = Dem_Mem_RingBufferFastRatePtr((Dem_Mem_GetCurrentRingBufferIndexFast() + SourceIndex) % Dem_Cfg_TimeSeriesPastSamplesFast());
  }
# else
  lSourceBuffer = Dem_Mem_RingBufferFastRatePtr(SourceIndex);
# endif

  for (Dem_Cfg_EventDidIterInit(EventId, &lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterExists(&lDidIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterNext(&lDidIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    uint8 lDidSize;
    uint16 lWriteIndex;

    lDidIndex = Dem_Cfg_EventDidIterGet(&lDidIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lDidSize = Dem_DataStorageIF_GetDidNVSize(lDidIndex);
    lWriteIndex = lDestinationBuffer.WriteIndex;

    if (Dem_Data_IncrementWriteIndexDestinationBuffer(&lDestinationBuffer, lDidSize) == E_OK)                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      Dem_MemCpy(&lDestinationBuffer.Buffer[lWriteIndex],                                                                        /* PRQA S 0311, 0602 */ /* MD_DEM_11.5, MD_DEM_20.2 */ /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
        &lSourceBuffer[Dem_Cfg_DidBufferIndexFast(lDidIndex)],
        lDidSize);
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DATASTORAGEIF_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DataStorageIF_Implementation.h
 *********************************************************************************************************************/
