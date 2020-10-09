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
/*! \addtogroup Dem_DTCReadoutBuffer
 *  \{
 *  \file       Dem_DTCReadoutBuffer_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
 *  \details    Buffer event specific data after Dem_DisableDTCRecordUpdate() call.
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

#if !defined (DEM_DTCREADOUTBUFFER_IMPLEMENTATION_H)
#define DEM_DTCREADOUTBUFFER_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCReadoutBuffer_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_SnapshotEntry_Implementation.h"
#include "Dem_ExtendedEntry_Implementation.h"
#include "Dem_DTCSelector_Implementation.h"
#include "Dem_Scheduler_Implementation.h"
#include "Dem_MemCopy.h"
#include "Dem_Memory_Implementation.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \addtogroup  Dem_DTCReadoutBuffer_StatusType
 * \{
 */
#define DEM_DTCREADOUTBUFFER_STATUS_UNUSED            0  /*!< Initialization value, buffer is unused and contains invalid data */
#define DEM_DTCREADOUTBUFFER_STATUS_QUEUED            1  /*!< Buffer contains EventId, MemoryId configuration - waiting for MainFunction to copy the data */
#define DEM_DTCREADOUTBUFFER_STATUS_IN_USE            2  /*!< Buffer contains configuration and event data */
#define DEM_DTCREADOUTBUFFER_STATUS_NOT_STORED        3  /*!< Buffer contains EventId, MemoryId configuration - no data found to copy */
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \addtogroup Dem_DTCReadoutBuffer_Properties
 * \{
 */

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_TestDataRequested
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestDataRequested(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return (boolean)(Dem_DTCReadoutBuffer_GetState(ReadoutBufferId) != DEM_DTCREADOUTBUFFER_STATUS_UNUSED);
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_TestResultReady
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestResultReady(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  Dem_DTCReadoutBuffer_StatusType lBufferStatus;
  lBufferStatus = Dem_DTCReadoutBuffer_GetState(ReadoutBufferId);
  return (boolean)( (lBufferStatus == DEM_DTCREADOUTBUFFER_STATUS_IN_USE)
                          || (lBufferStatus == DEM_DTCREADOUTBUFFER_STATUS_NOT_STORED) );
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_TestStoredDataAvailable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestStoredDataAvailable(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return (boolean)(Dem_DTCReadoutBuffer_GetState(ReadoutBufferId) == DEM_DTCREADOUTBUFFER_STATUS_IN_USE);
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_TestExtendedRecordSelected
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestExtendedRecordSelected(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return Dem_DTCReadoutBuffer_GetExtendedIteratorPtr(ReadoutBufferId)->ExtendedRecordSelected;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetExtendedDataEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedDataEventId(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  )
{
  return Dem_DTCReadoutBuffer_GetExtendedIteratorPtr(ReadoutBufferId)->EventId;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetExtendedDataMemoryEntryId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_HandleType, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedDataMemoryEntryId(                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  )
{
  return Dem_DTCReadoutBuffer_GetExtendedIteratorPtr(ReadoutBufferId)->MemoryEntryId;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetExtendedEntryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedEntryIndex(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  )
{
  return Dem_DTCReadoutBuffer_GetExtendedIteratorPtr(ReadoutBufferId)->ExtendedEntryIndex;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetExtendedEntryIterator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ExtendedEntry_IterType, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedEntryIterator(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  )
{
  return Dem_DTCReadoutBuffer_GetExtendedIteratorPtr(ReadoutBufferId)->ExtendedEntryIter;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SetExtendedEntryIterator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetExtendedEntryIterator(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_ExtendedEntry_IterType, AUTOMATIC)  ExtendedEntryIter
  )
{
  Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId)->ExtendedIterator.ExtendedEntryIter = ExtendedEntryIter;                    /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_IncExtendedEntryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_IncExtendedEntryIndex(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  ERecType
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ReadoutBufferId)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ERecType)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  if (ERecType == DEM_CFG_EREC_TYPE_USER)
  {
    uint8 lExtendedEntryIndex;

    lExtendedEntryIndex = Dem_DTCReadoutBuffer_GetExtendedEntryIndex(ReadoutBufferId) + 1;
    Dem_DTCReadoutBuffer_SetExtendedEntryIndex(ReadoutBufferId, lExtendedEntryIndex);
  }
# endif
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetExtendedDataNumber
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedDataNumber(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  )
{
  return Dem_DTCReadoutBuffer_GetExtendedIteratorPtr(ReadoutBufferId)->ExtendedDataNumber;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_TestSnapshotRecordSelected
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestSnapshotRecordSelected(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return Dem_DTCReadoutBuffer_GetSnapshotIteratorPtr(ReadoutBufferId)->SnapshotSelected;
}
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON))
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetSnapshotEntryIterator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SnapshotEntry_IterType, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotEntryIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
)
{
  return Dem_DTCReadoutBuffer_GetSnapshotIteratorPtr(ReadoutBufferId)->SnapshotEntryIter;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SetSnapshotEntryIterator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetSnapshotEntryIterator(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_SnapshotEntry_IterType, AUTOMATIC)  SnapshotEntryIter
)
{
  Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId)->SnapshotIterator.SnapshotEntryIter = SnapshotEntryIter;                    /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */  
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetSnapshotRecordNumber
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotRecordNumber(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
)
{
  return Dem_DTCReadoutBuffer_GetSnapshotIteratorPtr(ReadoutBufferId)->RecordNumber;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetSnapshotRecordSource
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_SnapshotSourceType, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotRecordSource(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
)
{
  return Dem_DTCReadoutBuffer_GetSnapshotIteratorPtr(ReadoutBufferId)->Source;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SetSnapshotRecordSource
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetSnapshotRecordSource(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_DTCReadoutBuffer_SnapshotSourceType, AUTOMATIC)  Source
)
{
  Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId)->SnapshotIterator.Source = Source;                                          /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */  
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetSnapshotSourceIterator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ComplexIterType, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotSourceIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
)
{
  return Dem_DTCReadoutBuffer_GetSnapshotIteratorPtr(ReadoutBufferId)->SourceIterator;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SetSnapshotSourceIterator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetSnapshotSourceIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(Dem_Cfg_ComplexIterType, AUTOMATIC)  SourceIterator
)
{
  Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId)->SnapshotIterator.SourceIterator = SourceIterator;                          /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */
}
#endif

/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetMemoryEntryId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_HandleType, DEM_CODE)
Dem_DTCReadoutBuffer_GetMemoryEntryId(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return (DEM_MEMORYENTRY_HANDLE_READOUTBUFFER + ReadoutBufferId);
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCReadoutBuffer_GetEventId(
    CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
    )
{
  return (Dem_EventIdType)Dem_Cfg_GetReadoutBuffer(ReadoutBufferId).EventId;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetMemoryId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCReadoutBuffer_GetMemoryId(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return Dem_Cfg_GetReadoutBuffer(ReadoutBufferId).MemoryId;
}
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON) )
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SetOBDData_IsStored
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetOBDData_IsStored(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(boolean, AUTOMATIC) IsStored
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (ReadoutBufferId >= Dem_Cfg_GetSizeOfReadoutBuffer())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetReadoutBuffer(ReadoutBufferId).OBDFreezeFrameData.IsStored = IsStored;                                                       /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER_CSL */
  }
}
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON) )
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetOBDData_IsStored
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_GetOBDData_IsStored(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return Dem_Cfg_GetReadoutBuffer(ReadoutBufferId).OBDFreezeFrameData.IsStored;
}
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON) )
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetPtrToOBDFreezeFrameBuffer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_DTCReadoutBuffer_GetPtrToOBDFreezeFrameBuffer(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return &(Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId)->OBDFreezeFrameData.ObdFreezeFrame[0]);
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_DTCReadoutBuffer_Private
 * \{
 */

/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SetReadoutBufferEntry()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_DTCReadoutBuffer_SetReadoutBufferEntry(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(uint16, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  State,
  Dem_DTCReadoutBuffer_ExtendedDataIteratorConstPtrType  ExtendedIterator,
  Dem_DTCReadoutBuffer_SnapshotDataIteratorConstPtrType  SnapshotIterator
  )
{
  Dem_Cfg_ReadoutBufferEntryPtrType lReadoutBufferEntryPtr;
  lReadoutBufferEntryPtr = Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId);

  lReadoutBufferEntryPtr->EventId = EventId;                                                                                     /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */
  lReadoutBufferEntryPtr->MemoryId = MemoryId;                                                                                   /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */
  lReadoutBufferEntryPtr->State = State;                                                                                         /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */
  lReadoutBufferEntryPtr->ExtendedIterator = *ExtendedIterator;                                                                  /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */
  lReadoutBufferEntryPtr->SnapshotIterator = *SnapshotIterator;                                                                  /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */
}                                                                                                                                /* PRQA S 6060 */ /* MD_MSR_STPAR */


/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetEntrySafe()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ReadoutBufferEntryPtrType, DEM_CODE)
Dem_DTCReadoutBuffer_GetEntrySafe(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  )
{
  Dem_Cfg_ReadoutBufferEntryPtrType lResult;
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (ReadoutBufferId >= Dem_Cfg_GetSizeOfReadoutBuffer())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lResult = &Dem_Cfg_GetReadoutBuffer(0);
  }
  else
# endif
  {
    lResult =  Dem_Cfg_GetAddrReadoutBuffer(ReadoutBufferId);
  }

  return lResult;
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_ExtendedDataRecord_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_ExtendedDataRecord_Init(
  Dem_DTCReadoutBuffer_ExtendedDataIteratorPtrType ExtendedDataIterator
)
{
# if(DEM_CFG_SUPPORT_ERECS == STD_ON)
  Dem_ExtendedEntry_IterInit(DEM_EVENT_INVALID, &(ExtendedDataIterator->ExtendedEntryIter));                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT_STRUCT_MEMBER */
  ExtendedDataIterator->MemoryEntryId = DEM_MEMORYENTRY_HANDLE_INVALID;                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  ExtendedDataIterator->ExtendedEntryIndex = 0;                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  ExtendedDataIterator->EventId = DEM_EVENT_INVALID;                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# endif
  ExtendedDataIterator->ExtendedDataNumber = 0;                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  ExtendedDataIterator->ExtendedRecordSelected = FALSE;                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SnapshotRecord_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SnapshotRecord_Init(
  Dem_DTCReadoutBuffer_SnapshotDataIteratorPtrType SnapshotDataIterator
  )
{
  Dem_Cfg_ComplexIterClear(&(SnapshotDataIterator->SourceIterator));                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT_STRUCT_MEMBER */
# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  Dem_SnapshotEntry_IteratorInit(DEM_EVENT_INVALID, DEM_MEMORYENTRY_HANDLE_INVALID, &(SnapshotDataIterator->SnapshotEntryIter)); /* SBSW_DEM_POINTER_FORWARD_ARGUMENT_STRUCT_MEMBER */
# endif
  SnapshotDataIterator->RecordNumber = 0;                                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  SnapshotDataIterator->Source = Dem_DTCReadoutBuffer_SnapshotSource_Invalid;                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  SnapshotDataIterator->SnapshotSelected = FALSE;                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetExtendedIteratorPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_ExtendedDataIteratorPtrType, DEM_CODE)
Dem_DTCReadoutBuffer_GetExtendedIteratorPtr(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return &(Dem_Cfg_GetReadoutBuffer(ReadoutBufferId).ExtendedIterator);
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SetExtendedIterator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetExtendedIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  Dem_DTCReadoutBuffer_ExtendedDataIteratorConstPtrType  ExtendedDataIterator
  )
{
  Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId)->ExtendedIterator = *ExtendedDataIterator;                                  /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */  
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetSnapshotIteratorPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_SnapshotDataIteratorPtrType, DEM_CODE)
Dem_DTCReadoutBuffer_GetSnapshotIteratorPtr(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return &(Dem_Cfg_GetReadoutBuffer(ReadoutBufferId).SnapshotIterator);
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SetSnapshotIterator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetSnapshotIterator(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  Dem_DTCReadoutBuffer_SnapshotDataIteratorConstPtrType  SnapshotIterator
  )
{
  Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId)->SnapshotIterator = *SnapshotIterator;                                      /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */  
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_StatusType, DEM_CODE)
Dem_DTCReadoutBuffer_GetState(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return Dem_Cfg_GetReadoutBuffer(ReadoutBufferId).State;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SetState()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetState(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  State
  )
{
  Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId)->State = State;                                                             /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */ 
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SetExtendedEntryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SetExtendedEntryIndex(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  )
{
  Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId)->ExtendedIterator.ExtendedEntryIndex = ExtendedEntryIndex;                  /* SBSW_DEM_ARRAY_POINTER_READOUTBUFFER */
}
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII == STD_ON) \
   && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON) )
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_CopyOBDFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_CopyOBDFreezeFrame(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  uint8 lSelectedIndex;
  Dem_EventIdType lEventId;

  lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId);
  lSelectedIndex = Dem_Mem_FreezeFrameFindIndex(lEventId);
  if (lSelectedIndex == Dem_Cfg_GlobalObdIIFFCount())
  {
    Dem_DTCReadoutBuffer_SetOBDData_IsStored(ReadoutBufferId, FALSE);
  }
  else
  {
    Dem_SharedDataPtrType lSourceEntry;
    Dem_DataPtrType lDestinationEntry;
    uint16 lObdFreezeFrameMaxSize;

    lSourceEntry = Dem_Mem_FreezeFrameObdIIGetDataPtr(lSelectedIndex);
    lDestinationEntry = Dem_DTCReadoutBuffer_GetPtrToOBDFreezeFrameBuffer(ReadoutBufferId);
    lObdFreezeFrameMaxSize = Dem_Cfg_GlobalObdFreezeFrameMaxSize();
    Dem_MemCpy((Dem_SharedDataPtrType)lDestinationEntry,                                                                         /* PRQA S 0602 */ /* MD_DEM_20.2 */ /* SBSW_DEM_POINTER_FORWARD_READOUTBUFFER_OBDFREEZEFRAME */
                    (Dem_SharedDataPtrType)lSourceEntry,
                    lObdFreezeFrameMaxSize);
    Dem_DTCReadoutBuffer_SetOBDData_IsStored(ReadoutBufferId, TRUE);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_DTCReadoutBuffer_Public
 * \{
 */

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_GetGlobalSnapshotDataPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_DTCReadoutBuffer_GetGlobalSnapshotDataPtr(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return &(Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId)->Data.GlobalSnapshotData[0]);
}
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_TestGlobalSnapshotStored
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReadoutBuffer_TestGlobalSnapshotStored(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  return Dem_DTCReadoutBuffer_GetEntrySafe(ReadoutBufferId)->Data.GlobalSnapshotRecordStored;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_Init(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId
  )
{
  Dem_DTCReadoutBuffer_ExtendedDataIteratorType lExtendedIterator;
  Dem_DTCReadoutBuffer_SnapshotDataIteratorType lSnapshotIterator;

  Dem_DTCReadoutBuffer_ExtendedDataRecord_Init(&lExtendedIterator);                                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
  Dem_DTCReadoutBuffer_SnapshotRecord_Init(&lSnapshotIterator);                                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */

  Dem_DTCReadoutBuffer_SetReadoutBufferEntry(ReadoutBufferId, 
                                             DEM_EVENT_INVALID, 
                                             DEM_MEMORYENTRY_HANDLE_INVALID, 
                                             DEM_DTCREADOUTBUFFER_STATUS_UNUSED, 
                                             &lExtendedIterator,                                                                 /* SBSW_DEM_POINTER_FORWARD_STACK */
                                             &lSnapshotIterator);                                                                /* SBSW_DEM_POINTER_FORWARD_STACK */
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_CheckAndSetState
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTCReadoutBuffer_CheckAndSetState(
    CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
    CONST(Dem_EventIdType, AUTOMATIC)                 EventId,
    CONST(uint8, AUTOMATIC)                           MemoryId,
    CONST(Dem_DTCSelector_HandleType, AUTOMATIC)      DTCSelector
    )
{
  Dem_DTCReadoutBuffer_ExtendedDataIteratorType lExtendedIterator;
  Dem_DTCReadoutBuffer_SnapshotDataIteratorType lSnapshotIterator;
  Std_ReturnType lReturnValue;

  if (Dem_DTCReadoutBuffer_GetState(ReadoutBufferId) == DEM_DTCREADOUTBUFFER_STATUS_UNUSED)
  {
    /* new request */
    Dem_DTCSelector_LockSelectDTC(DTCSelector);

    Dem_DTCReadoutBuffer_ExtendedDataRecord_Init(&lExtendedIterator);                                                            /* SBSW_DEM_POINTER_FORWARD_STACK */
    Dem_DTCReadoutBuffer_SnapshotRecord_Init(&lSnapshotIterator);                                                                /* SBSW_DEM_POINTER_FORWARD_STACK */

    Dem_DTCReadoutBuffer_SetReadoutBufferEntry(ReadoutBufferId,
                                               EventId,
                                               MemoryId,
                                               DEM_DTCREADOUTBUFFER_STATUS_QUEUED,
                                               &lExtendedIterator,                                                               /* SBSW_DEM_POINTER_FORWARD_STACK */
                                               &lSnapshotIterator);                                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
    
    /* Scheduler task needs to be enabled last. This ensures readout buffer data are 
       written back to memory before executing the task.*/

    Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_FilterEventData);
    lReturnValue = DEM_PENDING;
  }
  else 
  if (EventId == Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId))
  {
    if (MemoryId == Dem_DTCReadoutBuffer_GetMemoryId(ReadoutBufferId))
    {
      /* repeated request with identical parameters */
      if (Dem_DTCReadoutBuffer_GetState(ReadoutBufferId) == DEM_DTCREADOUTBUFFER_STATUS_QUEUED)
      {
        /* request is still queued, copying of data is not finished */
        lReturnValue = DEM_PENDING;
      }
      else
      {
        /* copying of data is finished */
        lReturnValue = E_OK;
      }
    }
    else
    {
      /* repeated request with different parameters */
      lReturnValue = E_NOT_OK;
    }
  }
  else
  {
    /* repeated request with different parameters */
    lReturnValue = E_NOT_OK;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
% Dem_DTCReadoutBuffer_FillData
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_FillData(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)      DTCSelector
)
{
  if (ReadoutBufferId != DEM_CFG_READOUTBUFFER_INVALID)
  {
    /* copy memory entry only for readout buffer in state QUEUED */
    if (Dem_DTCReadoutBuffer_GetState(ReadoutBufferId) == DEM_DTCREADOUTBUFFER_STATUS_QUEUED)
    {
      Dem_Cfg_MemoryIndexType lMemoryIndex;

# if (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 ==STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
      Dem_DTCReadoutBuffer_CopyOBDFreezeFrame(ReadoutBufferId);
# endif

      lMemoryIndex = Dem_Memory_FindIndex(Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId));
      if (lMemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX)
      {
        Dem_MemoryEntry_InitializeEntry(Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId));
        Dem_EnterCritical_DcmApi();
        if (Dem_DTCReadoutBuffer_GetState(ReadoutBufferId) == DEM_DTCREADOUTBUFFER_STATUS_QUEUED)
        {
          Dem_DTCReadoutBuffer_SetState(ReadoutBufferId, DEM_DTCREADOUTBUFFER_STATUS_NOT_STORED);
          Dem_DTCSelector_ReleaseSelectDTC(DTCSelector);
        }
        Dem_LeaveCritical_DcmApi();
      }
      else
      {
        Dem_MemoryEntry_CopyEntry(Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId), 
                                  Dem_MemoryEntry_GetId(lMemoryIndex));
        Dem_EnterCritical_DcmApi();
        if (Dem_DTCReadoutBuffer_GetState(ReadoutBufferId) == DEM_DTCREADOUTBUFFER_STATUS_QUEUED)
        {
          Dem_DTCReadoutBuffer_SetState(ReadoutBufferId, DEM_DTCREADOUTBUFFER_STATUS_IN_USE);
          Dem_DTCSelector_ReleaseSelectDTC(DTCSelector);
        }
        Dem_LeaveCritical_DcmApi();
      }
# if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
      lMemoryIndex = Dem_Mem_TimeSeriesFindIndex(Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId));
      if (lMemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX)
      {
        /* no time series entry for event - there is no data to be copied */
        /* Mark the buffer as unused - this can be used to verify the validity of statistic records */
        Dem_Cfg_TimeSeriesReadoutBuffer.EventId = DEM_EVENT_INVALID;
        /* Initialize 'no record stored', this allows a common test for the validity of stored records */
        Dem_TimeSeriesData_EntryInit(&Dem_Cfg_TimeSeriesReadoutBuffer);                                                          /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
      }
      else
      {
        /* copy time series entry */
        Dem_MemCpy((Dem_DataPtrType)(&Dem_Cfg_TimeSeriesReadoutBuffer),                                                          /* PRQA S 0310, 3305, 0602 */ /* MD_DEM_11.4_cpy, MD_DEM_3305, MD_DEM_20.2 */ /* SBSW_DEM_POINTER_MEMCPY_TIMESERIESREADOUTBUFFER */
          (Dem_NvDataPtrType)(Dem_Mem_TimeSeriesGetEntry(lMemoryIndex)),
          sizeof(Dem_Cfg_TimeSeriesReadoutBuffer));
      }
# endif
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
% Dem_DTCReadoutBuffer_FreeBuffer
*****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_FreeBuffer(
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)      DTCSelector
  )
{
  Dem_EnterCritical_DcmApi();
  if (Dem_DTCReadoutBuffer_GetState(ReadoutBufferId) == DEM_DTCREADOUTBUFFER_STATUS_QUEUED)
  {
    Dem_DTCSelector_ReleaseSelectDTC(DTCSelector);
  }
  Dem_DTCReadoutBuffer_SetState(ReadoutBufferId, DEM_DTCREADOUTBUFFER_STATUS_UNUSED);
  Dem_LeaveCritical_DcmApi();
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DTCReadoutBuffer_SelectExtendedDataRecord
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SelectExtendedDataRecord(
CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
CONST(uint8, AUTOMATIC) ExtendedDataNumber
)
{
  Dem_DTCReadoutBuffer_ExtendedDataIteratorType lExtendedDataIterator;

  lExtendedDataIterator = *Dem_DTCReadoutBuffer_GetExtendedIteratorPtr(ReadoutBufferId);

# if (DEM_CFG_SUPPORT_ERECS == STD_ON) 
  {
    Dem_EventIdType lEventId;

    lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId);
    Dem_ExtendedEntry_IterInit(lEventId, &(lExtendedDataIterator.ExtendedEntryIter));                                            /* SBSW_DEM_POINTER_FORWARD_STACK */
    lExtendedDataIterator.MemoryEntryId = Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId);
    lExtendedDataIterator.ExtendedEntryIndex = 0;
    lExtendedDataIterator.EventId = lEventId;
  }
# endif
  lExtendedDataIterator.ExtendedDataNumber = ExtendedDataNumber;
  lExtendedDataIterator.ExtendedRecordSelected = TRUE;
  
  Dem_DTCReadoutBuffer_SetExtendedIterator(ReadoutBufferId, &lExtendedDataIterator);                                             /* SBSW_DEM_POINTER_FORWARD_STACK */
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
% Dem_DTCReadoutBuffer_SelectSnapshotRecord
*****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReadoutBuffer_SelectSnapshotRecord(
CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC) ReadoutBufferId,
CONST(uint8, AUTOMATIC) RecordNumber
)
{
  Dem_DTCReadoutBuffer_SnapshotDataIteratorType lSnapshotDataIterator;

  lSnapshotDataIterator = *Dem_DTCReadoutBuffer_GetSnapshotIteratorPtr(ReadoutBufferId);

# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  {
    Dem_EventIdType lEventId;

    lEventId = Dem_DTCReadoutBuffer_GetEventId(ReadoutBufferId);
    Dem_SnapshotEntry_IteratorInit(lEventId,
                                   Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId), 
                                   &(lSnapshotDataIterator.SnapshotEntryIter));                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */
  }
# endif
  lSnapshotDataIterator.RecordNumber = RecordNumber;
  lSnapshotDataIterator.Source = Dem_DTCReadoutBuffer_SnapshotSource_Invalid;
  lSnapshotDataIterator.SnapshotSelected = TRUE;
  Dem_Cfg_ComplexIterClear(&(lSnapshotDataIterator.SourceIterator));                                                             /* SBSW_DEM_POINTER_FORWARD_STACK */

  Dem_DTCReadoutBuffer_SetSnapshotIterator(ReadoutBufferId, &lSnapshotDataIterator);                                             /* SBSW_DEM_POINTER_FORWARD_STACK */
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DTCREADOUTBUFFER_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCReadoutBuffer_Implementation.h
 *********************************************************************************************************************/
