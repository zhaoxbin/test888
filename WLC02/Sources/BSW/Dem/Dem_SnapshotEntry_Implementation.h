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
/*! \addtogroup Dem_SnapshotEntry
 *  \{
 *  \file       Dem_SnapshotEntry_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Encapsulates the list of snapshot record buffers stored in the memory entry
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

#if !defined (DEM_SNAPSHOTENTRY_IMPLEMENTATION_H)
#define DEM_SNAPSHOTENTRY_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_SnapshotEntry_Interface.h"
/* ------------------------------------------------------------------------- */

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
 * \addtogroup Dem_SnapshotEntry_Properties
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
 * \addtogroup Dem_SnapshotEntry_Private
 * \{
 */

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
 * \addtogroup Dem_SnapshotEntry_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONSTP2VAR(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  )
{
  SnapshotEntryIter->EventId = EventId;                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  SnapshotEntryIter->MemoryEntryId = MemoryEntryId;                                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# if (DEM_CFG_SUPPORT_SRECS == STD_ON)
  if (SnapshotEntryIter->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    SnapshotEntryIter->SnapshotIteratorIndex = 
      Dem_Cfg_GetFreezeFrameNumTableStartIdxOfEventTable(EventId);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  else
  {
    SnapshotEntryIter->SnapshotIteratorIndex = 0;                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
# endif
  SnapshotEntryIter->SnapshotEntryIndex = 0;                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# if(DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  SnapshotEntryIter->GlobalSnapshotReported = FALSE;                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# endif
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorNext(
  CONSTP2VAR(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  )
{
  if (SnapshotEntryIter->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    SnapshotEntryIter->SnapshotIteratorIndex++;                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    SnapshotEntryIter->SnapshotEntryIndex++;                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SnapshotEntry_IteratorExists(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  )
{
  boolean lIteratorExists;
  if (SnapshotEntryIter->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    lIteratorExists = (boolean) (SnapshotEntryIter->SnapshotIteratorIndex < 
      Dem_Cfg_GetFreezeFrameNumTableEndIdxOfEventTable(SnapshotEntryIter->EventId));
  }
  else
  {
    lIteratorExists = FALSE;
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
  return lIteratorExists;
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorGetMemoryEntryHandle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_HandleType, DEM_CODE)
Dem_SnapshotEntry_IteratorGetMemoryEntryHandle(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  )
{
  return SnapshotEntryIter->MemoryEntryId;
}
#endif /* ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)) */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorGetSnapshotRecordIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_SRecIndexType, DEM_CODE)
Dem_SnapshotEntry_IteratorGetSnapshotRecordIndex(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  )
{
  Dem_Cfg_SRecIndexType lIndex;
  if (SnapshotEntryIter->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    lIndex = SnapshotEntryIter->SnapshotIteratorIndex;
  }
  else
  {
    lIndex = 0;
  }
  return lIndex;
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) && \
     ((DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON) || \
      ((DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))))
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorGetSnapshotEntryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_SnapshotEntry_IteratorGetSnapshotEntryIndex(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  )
{
  uint8 lIndex;
  if (SnapshotEntryIter->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    lIndex = SnapshotEntryIter->SnapshotEntryIndex;
  }
  else
  {
    lIndex = 0;
  }
  return lIndex;
}
#endif 

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorGetSnapshotRecordDataConstPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_SnapshotEntry_IteratorGetSnapshotRecordDataConstPtr(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  )
{
  if (SnapshotEntryIter->MemoryEntryId == DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
  return Dem_MemoryEntry_GetSnapshotRecordDataConstPtr(SnapshotEntryIter->MemoryEntryId, SnapshotEntryIter->SnapshotEntryIndex);
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorIsSnapshotRecordStored
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_SnapshotEntry_IteratorIsSnapshotRecordStored(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  )
{
  boolean lSnapshotRecordIsStored;

  lSnapshotRecordIsStored = FALSE;

  if (SnapshotEntryIter->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
    if (Dem_MemoryEntry_GetSnapshotHeader(SnapshotEntryIter->MemoryEntryId) > SnapshotEntryIter->SnapshotEntryIndex)
    {
      lSnapshotRecordIsStored = TRUE;
    }
# endif
# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
    {
      uint8 lMask;

      lMask = (uint8)(1u << SnapshotEntryIter->SnapshotEntryIndex);
      if ((Dem_MemoryEntry_GetSnapshotHeader(SnapshotEntryIter->MemoryEntryId) & lMask) != 0)
      {
        lSnapshotRecordIsStored = TRUE;
      }
    }
# endif
  }
  else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
  return lSnapshotRecordIsStored;
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorUpdateSnapshotEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorUpdateSnapshotEntry(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  )
{
  if (SnapshotEntryIter->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
    if (Dem_MemoryEntry_GetSnapshotHeader(SnapshotEntryIter->MemoryEntryId) == SnapshotEntryIter->SnapshotEntryIndex)
    { /* Only increment if a new snapshot is added, updates keep the current ID */
      Dem_MemoryEntry_SetSnapshotHeader(SnapshotEntryIter->MemoryEntryId, 
        (uint8)(Dem_MemoryEntry_GetSnapshotHeader(SnapshotEntryIter->MemoryEntryId) + 1));
    }
# endif

# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
    {
      uint8 lMask;

      lMask = (uint8)(1u << SnapshotEntryIter->SnapshotEntryIndex);
      Dem_MemoryEntry_SetSnapshotHeader(
        SnapshotEntryIter->MemoryEntryId, (uint8)(Dem_MemoryEntry_GetSnapshotHeader(SnapshotEntryIter->MemoryEntryId) | lMask));
    }
# endif
  }
  else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorCopySnapshotEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorCopySnapshotEntry(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter,
  CONST(uint8, AUTOMATIC)  EntryIndex
  )
{
  if ( (SnapshotEntryIter->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (EntryIndex < Dem_Cfg_GlobalSRecMaxCount()) )
  {
    Dem_MemCpy((Dem_MemoryEntry_GetSnapshotRecordDataPtr(SnapshotEntryIter->MemoryEntryId, SnapshotEntryIter->SnapshotEntryIndex)), /* PRQA S 0602 */ /* MD_DEM_20.2 */ /* SBSW_DEM_POINTER_SNAPSHOT_BUFFER */
               (Dem_MemoryEntry_GetSnapshotRecordDataPtr(SnapshotEntryIter->MemoryEntryId, EntryIndex)),
                Dem_Cfg_EventSRecMaxRawSize());
  }
  else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON) */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorFindLastStoredEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorFindLastStoredEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONSTP2VAR(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  )
{
  for (Dem_SnapshotEntry_IteratorInit(EventId, MemoryEntryId, SnapshotEntryIter);                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
       Dem_SnapshotEntry_IteratorExists(SnapshotEntryIter) == TRUE;                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
       Dem_SnapshotEntry_IteratorNext(SnapshotEntryIter))                                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    if ( (Dem_MemoryEntry_GetSnapshotHeader(MemoryEntryId) > 0)                                                                  /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_MemoryEntry_GetSnapshotHeader(MemoryEntryId) <= Dem_Cfg_GlobalSRecMaxCount()) )
    {
      if ((Dem_MemoryEntry_GetSnapshotHeader(MemoryEntryId) - 1) == SnapshotEntryIter->SnapshotEntryIndex)
      {
        break;
      }
    }
  }
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON) */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorFindEntryWithRecordNumber
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorFindEntryWithRecordNumber(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONSTP2VAR(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  )
{
  for (Dem_SnapshotEntry_IteratorInit(EventId, MemoryEntryId, SnapshotEntryIter);                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
       Dem_SnapshotEntry_IteratorExists(SnapshotEntryIter) == TRUE;                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
       Dem_SnapshotEntry_IteratorNext(SnapshotEntryIter))                                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    Dem_Cfg_SRecIndexType lCfgSRecIndex;

    lCfgSRecIndex = Dem_SnapshotEntry_IteratorGetSnapshotRecordIndex(SnapshotEntryIter);                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

    if (RecordNumber == Dem_Cfg_SRecId(lCfgSRecIndex))
    {
      if (Dem_SnapshotEntry_IteratorIsSnapshotRecordStored(SnapshotEntryIter) == TRUE)                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      {
        break;
      }

    }
  }
}
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_IteratorSetNextStoredEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SnapshotEntry_IteratorSetNextStoredEntry(
  CONSTP2VAR(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter                                                /* PRQA S 3673 */ /* MD_DEM_16.7_False */
  )
{
  boolean lFoundEntry;
  lFoundEntry = FALSE;
  if (SnapshotEntryIter->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
    while (Dem_SnapshotEntry_IteratorExists(SnapshotEntryIter) == TRUE)                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      if (Dem_SnapshotEntry_IteratorIsSnapshotRecordStored(SnapshotEntryIter) == TRUE)                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      {
        lFoundEntry = TRUE;
        break;
      }
      else
      {
        Dem_SnapshotEntry_IteratorNext(SnapshotEntryIter);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      }
    }
# else
    if (Dem_SnapshotEntry_IteratorIsSnapshotRecordStored(SnapshotEntryIter) == TRUE)                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      lFoundEntry = TRUE;
    }
# endif
  }
  else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
  return lFoundEntry;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_SnapshotEntry_GetNumberOfStoredSnapshotRecords
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_SnapshotEntry_GetNumberOfStoredSnapshotRecords(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lNumberOfRecords;
# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
  lNumberOfRecords = Dem_MemoryEntry_GetSnapshotHeader(MemoryEntryId);
# endif
# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
  {
    uint8 lSnapshotHeader;
    lNumberOfRecords = 0;
    lSnapshotHeader = Dem_MemoryEntry_GetSnapshotHeader(MemoryEntryId);
    while (lSnapshotHeader != 0)
    {
      lNumberOfRecords = (uint8)(lNumberOfRecords + (lSnapshotHeader & 0x01U));
      lSnapshotHeader = (uint8)(lSnapshotHeader >> 0x01U);
    }
  }
# endif
  return lNumberOfRecords;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON) */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_SNAPSHOTENTRY_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SnapshotEntry_Implementation.h
 *********************************************************************************************************************/
