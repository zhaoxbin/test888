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
/*! \addtogroup Dem_DataReportIF
 *  \{
 *  \file       Dem_DataReportIF_Implementation.h
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

#if !defined (DEM_DATAREPORTIF_IMPLEMENTATION_H)
#define DEM_DATAREPORTIF_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DataReportIF_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_Mem_Implementation.h"
#include "Dem_SnapshotEntry_Implementation.h"
#include "Dem_ExtendedEntry_Implementation.h"
#include "Dem_ExtDataElementIF_Implementation.h"
#include "Dem_DTCReadoutBuffer_Implementation.h"
#include "Dem_IntDataElementIF_Implementation.h"
#include "Dem_Data_Interface.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
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
 * \addtogroup Dem_DataReportIF_Properties
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
 * \addtogroup Dem_DataReportIF_Private
 * \{
 */

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_DataReportIF_FindDataElementKind
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DataReportIF_FindDataElementKind(
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex                                                                            
  )
{
  uint8 lDataElementKind;
  uint8 lDataCallbackType;
  
  lDataCallbackType = Dem_Cfg_DataCallbackType(DataIndex);
  switch (lDataCallbackType)
  {
  case DEM_CFG_DATA_FROM_AGINGCTR:
  case DEM_CFG_DATA_FROM_OCCCTR:
  case DEM_CFG_DATA_FROM_OCCCTR_2BYTE:
  case DEM_CFG_DATA_FROM_OVFLIND:
  case DEM_CFG_DATA_FROM_SIGNIFICANCE:
  case DEM_CFG_DATA_FROM_PRIORITY:
  case DEM_CFG_DATA_FROM_AGINGCTR_INVERTED:
  case DEM_CFG_DATA_FROM_MAX_FDC_SINCE_LAST_CLEAR:
  case DEM_CFG_DATA_FROM_MAX_FDC_DURING_CURRENT_CYCLE:
  case DEM_CFG_DATA_FROM_CYCLES_SINCE_LAST_FAILED:
  case DEM_CFG_DATA_FROM_CYCLES_SINCE_FIRST_FAILED:
  case DEM_CFG_DATA_FROM_FAILED_CYCLES:
  case DEM_CFG_DATA_FROM_CONSECUTIVE_FAILED_CYCLES:
  case DEM_CFG_DATA_FROM_FAULT_PENDING_COUNTER:
  case DEM_CFG_DATA_FROM_CYCLES_TESTED_SINCE_FIRST_FAILED:
  case DEM_CFG_DATA_FROM_CYCLES_TESTED_SINCE_LAST_FAILED:
  case DEM_CFG_DATA_FROM_HEALINGCTR_DOWNCNT:
  case DEM_CFG_DATA_FROM_ROOTCAUSE_EVENTID:
  case DEM_CFG_DATA_FROM_OBDDTC:
  case DEM_CFG_DATA_FROM_OBDDTC_3BYTE:
  case DEM_CFG_DATA_FROM_OBD_RATIO:
  case DEM_CFG_DATA_FROM_CYCLES_SINCE_LAST_UNCONFIRMED:
  case DEM_CFG_DATA_FROM_CYCLES_PASSED_SINCE_LAST_UNCONFIRMED:
  case DEM_CFG_DATA_FROM_CYCLES_SINCE_FIRST_UNCONFIRMED:
  case DEM_CFG_DATA_FROM_UNCONFIRMED_CYCLES:
  case DEM_CFG_DATA_FROM_CYCLES_PASSED_OR_UNCONFIRMED_SINCE_FIRST_UNCONFIRMED:
  case DEM_CFG_DATA_FROM_CURRENT_FDC:
  case DEM_CFG_DATA_FROM_AGED_COUNTER:
  case DEM_CFG_DATA_FROM_DTC_STATUS_INDICATOR:
  case DEM_CFG_DATA_FROM_DAG_STANDARD_ENV_DATA:
  case DEM_CFG_DATA_FROM_DAG_EXTENDED_ENV_DATA:
    lDataElementKind = DEM_DATAREPORTIF_DATAELEMENT_INTERNAL;
    break;
  
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
    lDataElementKind = DEM_DATAREPORTIF_DATAELEMENT_EXTERNAL;
    break;

  default: 
    lDataElementKind = DEM_DATAREPORTIF_DATAELEMENT_INVALID;
    break;
  }

  return lDataElementKind;
}
#endif

#if ( (DEM_CFG_SUPPORT_SRECS == STD_ON) \
   || (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) \
   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) \
   || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) )
/* ****************************************************************************
 % Dem_DataReportIF_SkipDid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReportIF_SkipDid(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr,
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  )
{
  Dem_Cfg_DidDataIterType lDataIter;

  /* Iterate all data elements in the DID */
  for (Dem_Cfg_DidDataIterInit(DidIndex, &lDataIter);                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DataIndexType lDataIndex;
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
            CopyDidInfoPtr->ReadIndex += Dem_Cfg_DataSize(lDataIndex);                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        break;

      default:
        break;
      }
    }
  }
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)|| (DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) */

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_DataReportIF_CopyReplacementBytes
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataReportIF_CopyReplacementBytes(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
  uint16 lDataSize = Dem_Cfg_DataSize(DataIndex);
  uint16 lWriteIndex = DestinationBuffer->WriteIndex;
  if (Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, lDataSize) == E_OK)                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    Dem_MemSet(&DestinationBuffer->Buffer[lWriteIndex],                                                                          /* PRQA S 0602 */ /* MD_DEM_20.2 */ /* SBSW_DEM_MEMSET_DESTINATIONBUFFER */
                DEM_DATAREPORTIF_INVALID_DATA_PATTERN,
                lDataSize);
  }
  return TRUE;
}
#endif


/* ------------------------------------------------------------------------- */
#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
% Dem_DataReportIF_CopyStoredUserData
*****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataReportIF_CopyStoredUserData(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
  uint8 lDataSize;
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->SourceBuffer != NULL_PTR, DEM_E_INCONSISTENT_STATE, FALSE)
  lDataSize = Dem_Cfg_DataSize(DataIndex);
  
  Dem_Data_WriteDestinationBuffer(CopyDidInfoPtr->DestinationBuffer,                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                 &CopyDidInfoPtr->SourceBuffer[CopyDidInfoPtr->ReadIndex],
                                  lDataSize);

  CopyDidInfoPtr->ReadIndex += lDataSize;                                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  return TRUE;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_DataReportIF_CopyStoredDataElement
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DataReportIF_CopyStoredDataElement(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
  boolean lReturnValue;
  uint8 lDataElementKind;

  lDataElementKind = Dem_DataReportIF_FindDataElementKind(DataIndex);
  if (lDataElementKind == DEM_DATAREPORTIF_DATAELEMENT_INTERNAL)
  {
    lReturnValue = Dem_IntDataElementIF_CopyInternalDataElement(CopyDidInfoPtr, DataIndex);                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  if (lDataElementKind == DEM_DATAREPORTIF_DATAELEMENT_EXTERNAL)
  {
    lReturnValue = Dem_DataReportIF_CopyStoredUserData(CopyDidInfoPtr, DataIndex);                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_DataReportIF_CopyDid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DataReportIF_CopyDid(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr,
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  )
{
  boolean lReturnValue;
  Dem_Cfg_DidDataIterType lDataIter;

  lReturnValue = TRUE;
  for (Dem_Cfg_DidDataIterInit(DidIndex, &lDataIter);                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DataIndexType lDataIndex;
    lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DataIsStoredInNV(lDataIndex) == TRUE)
    {
      lReturnValue = (boolean)(Dem_DataReportIF_CopyStoredDataElement(CopyDidInfoPtr, lDataIndex) & lReturnValue);               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
    else
    {
      lReturnValue = (boolean)(Dem_ExtDataElementIF_CollectDataElement(CopyDidInfoPtr, lDataIndex) & lReturnValue);              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_DataReportIF_CopyDid_NoInternalData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DataReportIF_CopyDid_NoInternalData(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr,
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex
  )
{
  boolean lReturnValue;
  Dem_Cfg_DidDataIterType lDataIter;

  lReturnValue = TRUE;

  for (Dem_Cfg_DidDataIterInit(DidIndex, &lDataIter);                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DataIndexType lDataIndex;
    lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DataIsStoredInNV(lDataIndex) == TRUE)
    {
      switch (Dem_Cfg_DataCallbackType(lDataIndex))
      {
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
        lReturnValue = (boolean)(Dem_DataReportIF_CopyStoredUserData(CopyDidInfoPtr, lDataIndex) & lReturnValue);                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        break;

      default:
        lReturnValue = (boolean)(Dem_DataReportIF_CopyReplacementBytes(CopyDidInfoPtr->DestinationBuffer, lDataIndex) & lReturnValue);              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        break;
      }
    }
    else
    {
      lReturnValue = (boolean)(Dem_ExtDataElementIF_CollectDataElement(CopyDidInfoPtr, lDataIndex) & lReturnValue);              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
% Dem_DataReportIF_InitCopyDidInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DataReportIF_InitCopyDidInfo(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  )
{
  CopyDidInfoPtr->DestinationBuffer = DestinationBuffer;                                                                         /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
  CopyDidInfoPtr->SourceBuffer = SourceBuffer;                                                                                   /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
  CopyDidInfoPtr->ReadIndex = 0;                                                                                                 /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
  CopyDidInfoPtr->MemoryEntryId = MemoryEntryId;                                                                                 /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
  CopyDidInfoPtr->EventId = EventId;                                                                                             /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
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
 * \addtogroup Dem_DataReportIF_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON))
/* ****************************************************************************
 % Dem_DataReportIF_SRecCopyData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReportIF_SRecCopyData(
CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
CONST(Dem_EventIdType, AUTOMATIC)  EventId,
CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
)
{
  uint16 lWriteIndex;

  /* Reserve one byte for Did count */
  lWriteIndex = DestinationBuffer->WriteIndex;
  if (Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 1) == E_OK)                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    uint16 lDidCount;
    Dem_Cfg_EventDidIterType lDidIter;
    Dem_DataReportIF_CopyDidInfoType lCopyDidInfo;

    /* Initialize a CopyDid Context. */
    Dem_DataReportIF_InitCopyDidInfo(&lCopyDidInfo, DestinationBuffer, SourceBuffer, EventId, MemoryEntryId);                    /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
    
    /* Initialize number of DIDs */
    lDidCount = 0;
    for (Dem_Cfg_EventDidIterInit(EventId, &lDidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_EventDidIterExists(&lDidIter) == TRUE;                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_EventDidIterNext(&lDidIter))                                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {

      Dem_Cfg_DidIndexType lDidIndex;
      lDidIndex = Dem_Cfg_EventDidIterGet(&lDidIter);                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */

      ++lDidCount;

      Dem_Data_WriteDestinationBufferUint16(lCopyDidInfo.DestinationBuffer, Dem_Cfg_DidNumber(lDidIndex));                       /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */

      {
        (void)Dem_DataReportIF_CopyDid(&lCopyDidInfo, lDidIndex);                                                                /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
      }
    }

    /* Set the DID count to 0 in case of more than 255 DIDs. */
    if (lDidCount > 255)
    {
      lDidCount = 0;
    }
    /* first byte contains record number */
    Dem_Data_WriteDestinationBufferAtIndex(lCopyDidInfo.DestinationBuffer, lWriteIndex, Dem_GetLoByte(lDidCount));               /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_DataReportIF_GlobalSnapshotCopyData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReportIF_GlobalSnapshotCopyData(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  )
{
  if (DestinationBuffer->BufferSize > DestinationBuffer->WriteIndex)
  {
    uint16 lDidCount;
    uint16 lWriteIndex;
    Dem_Cfg_EventObdDidIterType lDidIter;
    Dem_DataReportIF_CopyDidInfoType lCopyDidInfo;

    /* Initialize a CopyDid Context. Reserve one byte at the start for the DID count. */
    lWriteIndex = DestinationBuffer->WriteIndex;
    (void)Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 1);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_DataReportIF_InitCopyDidInfo(&lCopyDidInfo, DestinationBuffer, SourceBuffer, EventId, MemoryEntryId);                    /* SBSW_DEM_CALL_COPYDIDINFO_INIT */

    lDidCount = 0;
     
    for (Dem_Cfg_GlobalSnapshotDidIterInit(&lDidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_GlobalSnapshotDidIterExists(&lDidIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_GlobalSnapshotDidIterNext(&lDidIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_Cfg_DidIndexType lDidIndex;
      lDidIndex = Dem_Cfg_GlobalSnapshotDidIterGet(&lDidIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */

      ++lDidCount;

      Dem_Data_WriteDestinationBufferUint16(lCopyDidInfo.DestinationBuffer, Dem_Cfg_DidNumber(lDidIndex));                       /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_TMC == STD_ON)
      Dem_Data_WriteDestinationBufferUint8(lCopyDidInfo.DestinationBuffer, Dem_GetLoByte(Dem_Cfg_DidSize(lDidIndex)));           /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# endif
      (void)Dem_DataReportIF_CopyDid(&lCopyDidInfo, lDidIndex);                                                                  /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
    }

    /* Set the DID count to 0 in case of more than 255 DIDs. */
    if (lDidCount > 255)
    {
      lDidCount = 0;
    }
    Dem_Data_WriteDestinationBufferAtIndex(lCopyDidInfo.DestinationBuffer, lWriteIndex, Dem_GetLoByte(lDidCount));               /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_DataReportIF_WWHOBDFreezeFrameCopyData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DataReportIF_WWHOBDFreezeFrameCopyData(
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId)
{
  if (DestinationBuffer->BufferSize > DestinationBuffer->WriteIndex)
  {
    uint16 lDidCount;
    uint16 lWriteIndex;
    Dem_Cfg_EventObdDidIterType lDidIter;
    Dem_DataReportIF_CopyDidInfoType lCopyDidInfo;

    /* Initialize a CopyDid Context. Reserve one byte at the start for the DID count. */
    lWriteIndex = DestinationBuffer->WriteIndex;
    (void)Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 1);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_DataReportIF_InitCopyDidInfo(&lCopyDidInfo, DestinationBuffer, SourceBuffer, EventId, MemoryEntryId);                    /* SBSW_DEM_CALL_COPYDIDINFO_INIT */

    lDidCount = 0;
     
    for (Dem_Cfg_EventObdDidIterInit(EventId, &lDidIter);                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventObdDidIterExists(&lDidIter) == TRUE;                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventObdDidIterNext(&lDidIter))                                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_Cfg_DidIndexType lDidIndex;
      lDidIndex = Dem_Cfg_EventObdDidIterGet(&lDidIter);                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */

      ++lDidCount;

      Dem_Data_WriteDestinationBufferUint16(lCopyDidInfo.DestinationBuffer, Dem_Cfg_DidNumber(lDidIndex));                       /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_TMC == STD_ON)
      Dem_Data_WriteDestinationBufferUint8(lCopyDidInfo.DestinationBuffer, Dem_GetLoByte(Dem_Cfg_DidSize(lDidIndex)));           /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
# endif
      (void)Dem_DataReportIF_CopyDid(&lCopyDidInfo, lDidIndex);                                                                  /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
    }

    /* Set the DID count to 0 in case of more than 255 DIDs. */
    if (lDidCount > 255)
    {
      lDidCount = 0;
    }
    Dem_Data_WriteDestinationBufferAtIndex(lCopyDidInfo.DestinationBuffer, lWriteIndex, Dem_GetLoByte(lDidCount));               /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DataReportIF_ObdIIFreezeFrameCopyPidData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReportIF_ObdIIFreezeFrameCopyPidData(
  CONST(uint8, AUTOMATIC)  FreezeFrameIndex,
  CONST(uint8, AUTOMATIC)  Pid,
  CONST(uint8, AUTOMATIC)  DataElementIndex,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  Buffer,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  BufSize
  )
{
  uint16_least              lSrcBufferOffset;
  Dem_Cfg_GlobalPidIterType lPidIter;
  Std_ReturnType            lReturnValue;

  lSrcBufferOffset = 0;
  lReturnValue     = E_NOT_OK;

  for (Dem_Cfg_GlobalPidIterInit(&lPidIter);                                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalPidIterExists(&lPidIter) == TRUE;                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalPidIterNext(&lPidIter))                                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
  { /* look for the requested PID */
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_GlobalPidIterGet(&lPidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    /* Check for the requested PID -> the PID value stored in the configuration is from type uint16 with a
       leading 0xF4 which is only used from UDS services */
    if (Pid == Dem_GetLoByte(Dem_Cfg_DidNumber(lDidIndex)))
    {
      /* This is the requested PID, now find the requested data element */
      Dem_Cfg_DidDataIterType lDataIter;
      uint8 lDataElementIndex;

      /* Each DID consists of 1-* data elements. */
      lDataElementIndex = 0;
      for (Dem_Cfg_DidDataIterInit(lDidIndex, &lDataIter);                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
      { /* look for the requested data element of the PID */
        Dem_Cfg_DataIndexType lDataIndex;
        uint8 lElementSize;

        lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
        lElementSize = Dem_Cfg_DataSize(lDataIndex);
        if (DataElementIndex == lDataElementIndex)
        {
          /* This is the requested element index, check if data fits into the provided buffer */
          if (lElementSize <= *BufSize)
          {
            uint8* lObdFreezeFrameDataPtr;

            lObdFreezeFrameDataPtr = Dem_Mem_FreezeFrameObdIIGetDataPtr(FreezeFrameIndex);

            Dem_MemCpy(Buffer, &lObdFreezeFrameDataPtr[lSrcBufferOffset], lElementSize);                                         /* PRQA S 0602, 3109 */ /* MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
            *BufSize = lElementSize;                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

            lReturnValue = E_OK;
          }
          /* data element of PID identified, leave loop */
          break;
        }
        ++lDataElementIndex;
        lSrcBufferOffset = (uint16_least)(lSrcBufferOffset + lElementSize);
      }
      /* PID identified, leave loop */
      break;
    }
    lSrcBufferOffset = (uint16_least)(lSrcBufferOffset + Dem_Cfg_DidSize(lDidIndex));
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) */


#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DataReportIF_ObdIIFreezeFrameCopyUdsData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DataReportIF_ObdIIFreezeFrameCopyUdsData(
  CONST(Dem_DataReportIF_BufferIndexType, AUTOMATIC)  BufferIdx,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint8, AUTOMATIC)  Source
  )
{
  if ((DestinationBuffer->BufferSize - DestinationBuffer->WriteIndex) > 0)
  {
    uint16 lDidCount;
    uint16 lWriteIndex;
    Dem_Cfg_GlobalPidIterType lPidIter;
    Dem_DataReportIF_CopyDidInfoType  lCopyDidInfo;
    Dem_ConstSharedDataPtrType lPtrToSource;

    DEM_IGNORE_UNUSED_CONST_ARGUMENT(Source)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if(DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON)
    if (Source == DEM_DATAREPORTIF_SOURCE_OBDII_FF_READOUTBUFFER)
    {
      lPtrToSource = (Dem_ConstSharedDataPtrType)Dem_DTCReadoutBuffer_GetPtrToOBDFreezeFrameBuffer(BufferIdx.ReadoutBufferId);
    }
    else
# endif
    {
      lPtrToSource = (Dem_ConstSharedDataPtrType)Dem_Mem_FreezeFrameObdIIGetDataPtr(BufferIdx.FreezeFrameIndex);
    }
    /* Initialize a CopyDid Context. Reserve one byte at the start for the DID count. */
    lWriteIndex = DestinationBuffer->WriteIndex;
    (void) Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 1);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_DataReportIF_InitCopyDidInfo(&lCopyDidInfo                                                                               /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
                                   , DestinationBuffer
                                   , lPtrToSource
                                   , DEM_EVENT_INVALID
                                   , DEM_MEMORYENTRY_HANDLE_INVALID);

    /* initialize PID counter */
    lDidCount = 0;

    for (Dem_Cfg_GlobalPidIterInit(&lPidIter);                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_GlobalPidIterExists(&lPidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_GlobalPidIterNext(&lPidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_Cfg_DidIndexType lDidIndex;
      lDidIndex = Dem_Cfg_GlobalPidIterGet(&lPidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */

      /* Count the PIDs */
      ++lDidCount;

        /* Store the UDS DID number 0xF4 <PID> into the destination buffer */
      Dem_Data_WriteDestinationBufferUint8(lCopyDidInfo.DestinationBuffer, 0xf4U);                                               /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
      Dem_Data_WriteDestinationBufferUint8(lCopyDidInfo.DestinationBuffer, Dem_GetLoByte(Dem_Cfg_DidNumber(lDidIndex)));         /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */

      /* Copy the PID data into the destination buffer */
      (void)Dem_DataReportIF_CopyDid(&lCopyDidInfo, lDidIndex);                                                                  /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */

    }
    /* Store the number of PIDs to the first byte of the destination buffer.
     * Set the DID count to 0 in case of more than 255 DIDs. */
    if (lDidCount > 255)
    {
      lDidCount = 0;
    }
    Dem_Data_WriteDestinationBufferAtIndex(lCopyDidInfo.DestinationBuffer, lWriteIndex, Dem_GetLoByte(lDidCount));               /* SBSW_DEM_POINTER_LOCAL_COPYDID_DESTINATIONBUFFER */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) */


#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_DataReportIF_CopyExtendedDataRecord
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DataReportIF_CopyExtendedDataRecord(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC) ExtendedEntryIndex,
  CONST(Dem_Cfg_ERecIndexType, AUTOMATIC) CfgERecIndex,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC) MemoryEntryId,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  boolean lReturnValue;
  Dem_DataReportIF_CopyDidInfoType lCopyDidInfo;
  Dem_ConstSharedDataPtrType lSourceBuffer;

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)  
  uint8 lERecType;
  lERecType = Dem_Cfg_ERecType(CfgERecIndex);
# endif

  lReturnValue = E_OK;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ExtendedEntryIndex)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  if (lERecType == DEM_CFG_EREC_TYPE_USER)
  {
    lSourceBuffer = Dem_ExtendedEntry_IteratorGetExtendedRecordDataConstPtr(MemoryEntryId, ExtendedEntryIndex);
  }
  else /*lERecType == DEM_CFG_EREC_TYPE_GLOBAL or lERecType == DEM_CFG_EREC_TYPE_INTERNAL*/
# endif
  {
    lSourceBuffer = (Dem_ConstSharedDataPtrType)NULL_PTR;
  }

  Dem_DataReportIF_InitCopyDidInfo(&lCopyDidInfo, DestinationBuffer, lSourceBuffer, EventId, MemoryEntryId);                     /* SBSW_DEM_CALL_COPYDIDINFO_INIT */

  if (Dem_DataReportIF_CopyDid(&lCopyDidInfo, Dem_Cfg_ERecDid(CfgERecIndex)) == FALSE)                                           /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
    Dem_Data_ResetWriteIndexDestinationBuffer(DestinationBuffer);                                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6060 */ /* MD_MSR_STCAL, MD_MSR_STPAR */
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
% Dem_DataReportIF_CopyDidFromWwhObdFreezeFrame
*****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReportIF_CopyDidFromWwhObdFreezeFrame(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC) MemoryEntry,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_EventObdDidIterType   lDidIter;
  Dem_DataReportIF_CopyDidInfoType lCopyDidInfo;
  Dem_EventIdType lEventId;

  /* Initialize a CopyDid Context. */
  lEventId = Dem_MemoryEntry_GetEventId(MemoryEntry);
  Dem_DataReportIF_InitCopyDidInfo(&lCopyDidInfo                                                                                 /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
                                 , DestinationBuffer
                                 , SourceBuffer
                                 , lEventId
                                 , MemoryEntry);

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  for (Dem_Cfg_EventObdDidIterInit(lEventId, &lDidIter);                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventObdDidIterExists(&lDidIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventObdDidIterNext(&lDidIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventObdDidIterGet(&lDidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DidNumber(lDidIndex) == DataId)
    {
      if (Dem_Cfg_DidSize(lDidIndex) <= lCopyDidInfo.DestinationBuffer->BufferSize)
      {
        (void)Dem_DataReportIF_CopyDid(&lCopyDidInfo, lDidIndex);                                                                /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      break;
    }
    else
    { /* not the requested DID */
      Dem_DataReportIF_SkipDid(&lCopyDidInfo, lDidIndex);                                                                        /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 % Dem_DataReportIF_CopyDidTimeSeriesSRec
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReportIF_CopyDidTimeSeriesSRec(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(uint8, AUTOMATIC)  MemoryIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_EventDidIterType lDidIter;
  Dem_DataReportIF_CopyDidInfoType lCopyDidInfo;
  Dem_MemoryEntry_HandleType lMemoryEntryId;
  Dem_EventIdType lEventId;

  if (MemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX)
  {
    lMemoryEntryId = DEM_MEMORYENTRY_HANDLE_INVALID;
    lEventId = DEM_EVENT_INVALID;
  }
  else
  {
    lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
    lEventId = EventId;
  }

  /* Initialize a CopyDid Context. */
  Dem_DataReportIF_InitCopyDidInfo(&lCopyDidInfo                                                                                 /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
                                 , DestinationBuffer
                                 , SourceBuffer
                                 , lEventId
                                 , lMemoryEntryId);

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  for (Dem_Cfg_EventDidIterInit(EventId, &lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterExists(&lDidIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterNext(&lDidIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventDidIterGet(&lDidIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DidNumber(lDidIndex) == DataId)
    {
      uint16 DataSize;
      DataSize = Dem_Cfg_DidSize(lDidIndex);
      if (DataSize <= lCopyDidInfo.DestinationBuffer->BufferSize)
      {
        if (lCopyDidInfo.EventId == DEM_EVENT_INVALID)
        {                                                                                                                        /* PRQA S 0715 */ /* MD_MSR_1.1_715 */
          (void)Dem_DataReportIF_CopyDid_NoInternalData(&lCopyDidInfo, lDidIndex);                                               /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
        }
        else
        {                                                                                                                        /* PRQA S 0715 */ /* MD_MSR_1.1_715 */
          (void)Dem_DataReportIF_CopyDid(&lCopyDidInfo, lDidIndex);                                                              /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
        }

        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      break;
    }
    else
    { /* not the requested DID */
      Dem_DataReportIF_SkipDid(&lCopyDidInfo, lDidIndex);                                                                        /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_DataReportIF_CopyDidSRec
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReportIF_CopyDidSRec(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntry,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;

  Dem_Cfg_EventDidIterType lDidIter;
  Dem_DataReportIF_CopyDidInfoType lCopyDidInfo;

  /* Initialize a CopyDid Context */
  Dem_DataReportIF_InitCopyDidInfo(&lCopyDidInfo                                                                                 /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
                                 , DestinationBuffer
                                 , SourceBuffer
                                 , Dem_MemoryEntry_GetEventId(MemoryEntry)
                                 , MemoryEntry);

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  for (Dem_Cfg_EventDidIterInit(lCopyDidInfo.EventId, &lDidIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterExists(&lDidIter) == TRUE;                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventDidIterNext(&lDidIter))                                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_EventDidIterGet(&lDidIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DidNumber(lDidIndex) == DataId)
    {
      uint16 DataSize;
      DataSize = Dem_Cfg_DidSize(lDidIndex);
      if (DataSize <= lCopyDidInfo.DestinationBuffer->BufferSize)
      {
        (void)Dem_DataReportIF_CopyDid(&lCopyDidInfo, lDidIndex);                                                                /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      break;                                                                                                                     /* PRQA S 0771 */ /* MD_DEM_14.6_err */
    }
    else
    { /* not the requested DID */
      Dem_DataReportIF_SkipDid(&lCopyDidInfo, lDidIndex);                                                                        /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_DataReportIF_CopyDidGlobalSRec
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReportIF_CopyDidGlobalSRec(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntry,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;

  Dem_Cfg_EventDidIterType lDidIter;
  Dem_DataReportIF_CopyDidInfoType lCopyDidInfo;

  /* Initialize a CopyDid Context */
  Dem_DataReportIF_InitCopyDidInfo(&lCopyDidInfo                                                                                 /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
                                 , DestinationBuffer
                                 , SourceBuffer
                                 , Dem_MemoryEntry_GetEventId(MemoryEntry)
                                 , MemoryEntry);

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  for (Dem_Cfg_GlobalSnapshotDidIterInit(&lDidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalSnapshotDidIterExists(&lDidIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_GlobalSnapshotDidIterNext(&lDidIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_GlobalSnapshotDidIterGet(&lDidIter);                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_DidNumber(lDidIndex) == DataId)
    {
      uint16 DataSize;
      DataSize = Dem_Cfg_DidSize(lDidIndex);
      if (DataSize <= lCopyDidInfo.DestinationBuffer->BufferSize)
      {
        (void)Dem_DataReportIF_CopyDid(&lCopyDidInfo, lDidIndex);                                                                /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      break;                                                                                                                     /* PRQA S 0771 */ /* MD_DEM_14.6_err */
    }
    else
    { /* not the requested DID */
      Dem_DataReportIF_SkipDid(&lCopyDidInfo, lDidIndex);                                                                        /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DataReportIF_CopyPidFromObdIIFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DataReportIF_CopyPidFromObdIIFreezeFrame(
  CONST(uint16, AUTOMATIC)  DataId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntry,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC)  SourceBuffer,
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_GlobalPidIterType  lPidIter;
  Dem_DataReportIF_CopyDidInfoType lCopyDidInfo;

  lReturnValue = DEM_NO_SUCH_ELEMENT;

  /* Initialize a CopyDid Context */
  Dem_DataReportIF_InitCopyDidInfo(&lCopyDidInfo                                                                                 /* SBSW_DEM_CALL_COPYDIDINFO_INIT */
                                , DestinationBuffer
                                , SourceBuffer                                                                                   
                                , DEM_EVENT_INVALID
                                , MemoryEntry);

  for (Dem_Cfg_GlobalPidIterInit(&lPidIter);                                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_GlobalPidIterExists(&lPidIter) == TRUE;                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_GlobalPidIterNext(&lPidIter))                                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_DidIndexType lDidIndex;
    lDidIndex = Dem_Cfg_GlobalPidIterGet(&lPidIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_GetLoByte(Dem_Cfg_DidNumber(lDidIndex)) == Dem_GetLoByte(DataId))
    {
      uint16 DataSize;
      DataSize = Dem_Cfg_DidSize(lDidIndex);
      if (DataSize <= lCopyDidInfo.DestinationBuffer->BufferSize)
      {
        (void)Dem_DataReportIF_CopyDid(&lCopyDidInfo, lDidIndex);                                                                /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
        lReturnValue = E_OK;
      }
      else
      {
        lReturnValue = DEM_BUFFER_TOO_SMALL;
      }
      break;                                                                                                                     /* PRQA S 0771 */ /* MD_DEM_14.6_err */
    }
    else
    { /* not the requested DID */
      Dem_DataReportIF_SkipDid(&lCopyDidInfo, lDidIndex);                                                                        /* SBSW_DEM_POINTER_LOCAL_COPYDIDINFO */
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) */



/* ------------------------------------------------------------------------- */
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DATAREPORTIF_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DataReportIF_Implementation.h
 *********************************************************************************************************************/
