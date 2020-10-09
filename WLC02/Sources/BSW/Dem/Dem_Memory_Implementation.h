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
/*! \addtogroup Dem_Memory
 *  \{
 *  \file       Dem_Memory_Implementation.h
 *  \brief      Abstraction for multiple event memories.
 *  \details    Facade for all memory related tasks.
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

#if !defined (DEM_MEMORY_IMPLEMENTATION_H)
#define DEM_MEMORY_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Memory_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg_Definitions.h"
#include "Dem_MemoryRestoration_Implementation.h"
#include "Dem_MemStorageManager_Implementation.h"
#include "Dem_MemState_Implementation.h"
#include "Dem_Mem_Implementation.h"
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_MemAccess_Implementation.h"

#include "Dem_Event_Implementation.h"
#include "Dem_EventInternalStatus_Implementation.h"
#include "Dem_DTCInternalStatus_Implementation.h"
#include "Dem_UDSStatus_Implementation.h"
#include "Dem_Nvm_Implementation.h"
#include "Dem_Satellite_Implementation.h"
#include "Dem_EnableCondition_Implementation.h"
#include "Dem_StorageCondition_Implementation.h"
#include "Dem_Prestore_Implementation.h"
#include "Dem_MemPermanent_Implementation.h"
#include "Dem_MemObdFreezeFrame_Implementation.h"

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

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_Memory_Private
 * \{
 */

/* ****************************************************************************
 % Dem_Memory_Init_RestoreMemory
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_Init_RestoreMemory(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{ /* No reinitialization - restore primary stack */
  Dem_Memory_MemEntryIterType MemEntryIter;

  Dem_MemState_MemorySetCurrentSize(MemoryInfo, 0);                                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  /* Iterate through all memory entries. The iteration order must be identical to Dem_MemAccess_MemoryFindIndex. */
  for (Dem_Memory_MemEntry_IterInit(MemoryInfo->MemoryId, &MemEntryIter);                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterExists(&MemEntryIter) == TRUE;                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_MemEntry_IterNext(&MemEntryIter))                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_MemoryEntry_HandleType lMemoryEntryId;
    Dem_EventIdType lEventId;

    lMemoryIndex = Dem_Memory_MemEntry_IterGetMemoryIndex(&MemEntryIter);                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */

    /* Check and fix problems with internal corruption of the memory entry record: */
    if (Dem_MemoryRestoration_FixCorruptMemoryEntry(MemoryInfo, lMemoryIndex) == TRUE)                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    { /* Continue with next memory entry */
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }

    /* If the memory entry is allocated to an event that already has a memory entry: */
    if (Dem_MemoryRestoration_FixDoubleAllocation(MemoryInfo, lMemoryIndex) == TRUE)                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    { /* Continue with next memory entry */
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }

    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
    lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);
    if (lEventId != DEM_EVENT_INVALID)
    {
      uint32 lTimestamp;
      lTimestamp = Dem_MemoryEntry_GetTimestamp(lMemoryEntryId);

      Dem_MemoryRestoration_RestoreEventStatus(lMemoryEntryId, lEventId);

      /* Synchronize the global timestamp with the timestamp stored in the memory entry */
      if (lTimestamp > Dem_MemState_GetCurrentTimestamp())
      {
        Dem_MemState_SetCurrentTimestamp(lTimestamp);
      }

      /* Sort the memory entry into the chronological list */
      Dem_MemState_SortEntryIntoChronologicalList(MemoryInfo, lMemoryIndex, lTimestamp);                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

      /* Update the number of occupied memory entries */
      Dem_MemState_MemorySetCurrentSize(MemoryInfo,                                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        (uint8)(Dem_MemState_MemoryGetCurrentSize(MemoryInfo) + 1));                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    }
  }

  /* Update the global timestamp */
  Dem_MemState_SetCurrentTimestamp(Dem_MemState_GetCurrentTimestamp() + 1);;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

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
 * \addtogroup Dem_Memory_Public
 * \{
 */

#if ( (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) \
   || (DEM_CFG_SUPPORT_ERECS == STD_ON) \
   || (DEM_CFG_SUPPORT_SRECS == STD_ON) \
   || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) \
   || (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 % Dem_Memory_FindIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_FindIndex(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));

  return Dem_MemAccess_MemoryFindIndex(lMemoryInfo,EventId);                                                                     /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}
#endif

/* ****************************************************************************
 % Dem_Memory_FindIndex_Checked
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_FindIndex_Checked(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));

  return Dem_MemAccess_MemoryFindIndex_Checked(lMemoryInfo,EventId);                                                             /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_FreeEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_FreeEvent(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));
  Dem_MemAccess_MemoryFreeIndex(lMemoryInfo, MemoryIndex);                                                                       /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_GetFirstMemoryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_GetFirstMemoryIndex(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  return Dem_MemState_MemoryInfoInit(MemoryId)->FirstMemoryIndex;
}

/* ****************************************************************************
 % Dem_Memory_AllocateIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocateIndex(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_MemAccess_MemoryAllocateIndex(lMemoryInfo, EventId);                                                                /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

#if ((DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF))
/* ****************************************************************************
 % Dem_Memory_AllocateIndexAging
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocateIndexAging(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lMemoryIndex = Dem_MemAccess_MemoryAllocateAging(lMemoryInfo, EventId);                                                        /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  return lMemoryIndex;
}
#endif

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_Memory_GetOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_GetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  boolean lReturnValue;

  if ((Dem_MemState_GetMemoryOverflow() & (1U << MemoryId)) != 0)
  {
    lReturnValue = TRUE;
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterInit(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  Dem_Internal_AssertReturnVoid(MemoryId != DEM_CFG_MEMORYID_PERMANENT , DEM_E_INCONSISTENT_STATE)

  IterPtr->mMemoryInfoPtr = Dem_MemState_MemoryInfoInit(MemoryId);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mIdx = 0;                                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  /*Assign number of stored events*/
  IterPtr->mEndIdx = *(IterPtr->mMemoryInfoPtr->SizePtr);                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterResume
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterResume(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  StoredChronoIter,
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  Dem_Internal_AssertReturnVoid(MemoryId != DEM_CFG_MEMORYID_PERMANENT , DEM_E_INCONSISTENT_STATE)
  IterPtr->mMemoryInfoPtr = Dem_MemState_MemoryInfoInit(MemoryId);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mIdx = StoredChronoIter;                                                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = *(IterPtr->mMemoryInfoPtr->SizePtr);                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterNext(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx += 1;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterExists(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}


/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return Dem_MemState_MemoryGetChronology(IterPtr->mMemoryInfoPtr,                                                               /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
         (uint8)((IterPtr->mEndIdx - 1) - IterPtr->mIdx ));
}

/* ****************************************************************************
 % Dem_Memory_AllocMemEntriesChrono_IterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterGet(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (Dem_Cfg_MemoryIndexType)IterPtr->mIdx;
}

/* ****************************************************************************
 % Dem_Memory_AllEventMemEntries_IterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterInit(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx = Dem_MemState_GetFirstValidEventBlockIndex();                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  /*Assign number of stored events*/
  IterPtr->mEndIdx = Dem_MemState_GetFirstInvalidEventBlockIndex();                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_AllEventMemEntries_IterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterNext(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx += 1;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_AllEventMemEntries_IterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterExists(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}


/* ****************************************************************************
 % Dem_Memory_AllEventMemEntries_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterGetMemoryIndex(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (Dem_Cfg_MemoryIndexType)IterPtr->mIdx;
}


/* ****************************************************************************
 % Dem_Memory_MemEntry_IterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterInit(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(MemoryId);

  IterPtr->mIdx = Dem_MemState_MemoryGetFirstIndex(lMemoryInfo);                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */

  IterPtr->mEndIdx = Dem_MemState_MemoryGetLastIndex(lMemoryInfo);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_MemEntry_IterResume
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterResume(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC) MemoryIndex,
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(MemoryId);

  IterPtr->mIdx = MemoryIndex;                                                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_MemState_MemoryGetLastIndex(lMemoryInfo);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_MemEntry_IterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterNext(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx += 1;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Memory_MemEntry_IterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_MemEntry_IterExists(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}


/* ****************************************************************************
 % Dem_Memory_MemEntry_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_MemEntry_IterGetMemoryIndex(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return (Dem_Cfg_MemoryIndexType)IterPtr->mIdx;
}


/* ****************************************************************************
 % Dem_Memory_MemEntry_IterGetEntryId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_HandleType, DEM_CODE)
Dem_Memory_MemEntry_IterGetEntryId(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONSTP2CONST(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  return Dem_MemoryEntry_GetId((Dem_Cfg_MemoryIndexType)IterPtr->mIdx);
}


/* ****************************************************************************
 % Dem_Memory_GetNumAllocatedMemoryEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_GetNumAllocatedMemoryEntry(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(MemoryId);
  return Dem_MemState_MemoryGetCurrentSize(lMemoryInfo);                                                                         /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_UpdateGetState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_UpdateGetState(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  return Dem_MemState_UpdateGetState(MemoryIndex);
}

/* ****************************************************************************
 % Dem_Memory_TestUpdateInProgress
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TestUpdateInProgress(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryState
  )
{
  return  Dem_MemState_TestCommitStarted(MemoryState);
}

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_Memory_ResetOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ResetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  Dem_MemState_ResetOverflow(MemoryId);
}
#endif

/* ****************************************************************************
 % Dem_Memory_UpdateEventStatistics
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_UpdateEventStatistics(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(boolean, AUTOMATIC)  Occurrence
  )
{
  return Dem_MemStorageManager_UpdateEventMemoryStatistics(EventId, MemoryIndex, Occurrence);
}

/* ****************************************************************************
 % Dem_Memory_TriggerObdFreezeFrameStorage
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TriggerObdFreezeFrameStorage(
CONST(Dem_EventIdType, AUTOMATIC)  EventId,
CONST(uint8, AUTOMATIC)  Effects,
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
)
{
  uint8 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Effects)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lReturnValue = DEM_DATA_NO_CHANGES;
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  Dem_MemStorageManager_TriggerObdIIFreezeFrameStorage(EventId, Effects);
#endif
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  lReturnValue = Dem_MemStorageManager_TriggerWwhObdFreezeFrameStorage(EventId, Effects, MemoryIndex);
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Memory_UpdateEventEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_UpdateEventEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  return Dem_MemStorageManager_UpdateEventEntry(EventId, UpdateFlags, MemoryIndex);
}

/* ****************************************************************************
 % Dem_Memory_UpdateEventsCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_UpdateEventsCycleCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
)
{
#if ( (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON) \
   || (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) )
  boolean lBlockModification;
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_MemoryEntry_HandleType lMemoryEntryId;

  lMemoryIndex = Dem_Memory_FindIndex_Checked(EventId);
  lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

  lBlockModification = Dem_MemStorageManager_UpdateCycleCounter(EventId, lMemoryEntryId, CycleStatus);
  if (lBlockModification == TRUE)
  {
    Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
  }
#else
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(CycleStatus)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

#if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
/* ****************************************************************************
 % Dem_Memory_LatchCycleCounters
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_LatchCycleCounters(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(uint16, AUTOMATIC)  CycleCounter
)
{
  boolean lDirty;
  lDirty = Dem_MemStorageManager_TestCycleCounterLatched(Dem_MemoryEntry_GetId(MemoryIndex), CycleCounter);
  if (lDirty == TRUE)
  {
    Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
  }
}
#endif

/* ****************************************************************************
 % Dem_Memory_GetFirstEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Memory_GetFirstEvent(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  return Dem_MemState_MemoryGetFirstEvent(Dem_MemState_MemoryInfoInit(MemoryId));                                                /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_GetLastEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Memory_GetLastEvent(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  return Dem_MemState_MemoryGetLastEvent(Dem_MemState_MemoryInfoInit(MemoryId));                                                 /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
}

/* ****************************************************************************
 % Dem_Memory_Init
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_Init(
  void
  )
{
  uint8 lResetStoredData;
  Dem_EventIdType lEventId;
#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
  uint16 lDebounceNvIndex = 0;
#endif

  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  { /* Only reset stored status, since debouncing can have changed since pre-initalization */
    Dem_Event_SetInternalStatus(lEventId,
      Dem_DTCInternalStatus_SetStoredStatus(Dem_Event_GetInternalStatus(lEventId), Dem_DTCInternalStatus_StoredStatus_None));

#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
    /* If NV storage of debounce values is configured, and the event uses that feature */
    /* Its safe to do it here since supporting events are not allowed to report before Dem_Init() */
    if (Dem_Cfg_EventSupportDebounceNv(lEventId) == TRUE)
    {
      sint16 lDebounceValue;
      boolean lFailedThresholdReached;

      Dem_Internal_AssertReturnVoid(lDebounceNvIndex < Dem_Cfg_GlobalDebounceStorageEventCount(), DEM_E_INCONSISTENT_STATE)

      lDebounceValue = Dem_Mem_DebounceGetStoredValue(lDebounceNvIndex);
      lFailedThresholdReached = Dem_UDSStatus_Test_TF(Dem_Event_GetUDSStatus(lEventId));

      Dem_SatelliteCore_RestoreDebounceValue(
        Dem_Cfg_EventSatelliteId(lEventId),
        Dem_Cfg_EventSatelliteEventId(lEventId),
        lDebounceValue,
        lFailedThresholdReached);

      ++lDebounceNvIndex;
    }
#endif
  }

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  {
    Dem_Cfg_CombinedGroupIndexType lGroupId;
    for (lGroupId = 0; lGroupId < Dem_Cfg_GlobalCombinedGroupCount(); ++lGroupId)
    {
      Dem_Event_InternalStatusType lInternalStatus;
      Dem_Cfg_CombinedGroupIterType lSubEventIter;

      /* Initialize the combination group internal status */
      lInternalStatus = Dem_DTCInternalStatus_StoredStatus_None;

      /* For all combination groups, test if at least one sub-events is available by configuration.
         Initialization in PreInit and Init can have different settings for
         event availability, so repeat the calculation for combined DTCs */
      for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lSubEventIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_CombinedGroupIterExists(&lSubEventIter) == TRUE;                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_CombinedGroupIterNext(&lSubEventIter))                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        if (Dem_Cfg_EventAvailableByVariant(Dem_Cfg_CombinedGroupIterGet(&lSubEventIter)) == TRUE)                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
        { /* If so, set the availability in the combination status. */
          lInternalStatus = Dem_EventInternalStatus_SetAvailableInVariant(lInternalStatus);
          break;
        }
      }
      Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lInternalStatus);
    }
  }
#endif

  /* Initialize enable and storage conditions (based on configuration) */
  Dem_EnableCondition_Init();
#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
  Dem_StorageCondition_Init();
#endif

  /* Initialize transactional update commit numbers */
  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetMemoryCommitNumber(0), DEM_MEMORY_INIT_COMMIT_NUMBER, Dem_Cfg_GetSizeOfMemoryCommitNumber()*sizeof(Dem_Cfg_GetMemoryCommitNumber(0))); /* PRQA S 0312, 0602, 3109 */ /* MD_DEM_11.5, MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_MEMSET_MEMORYCOMMITNUMBER */

  lResetStoredData = (uint8)( (Dem_Cfg_AdminData.ImplementationVersion != Dem_Make16Bit(DEM_SW_MAJOR_VERSION, DEM_SW_MINOR_VERSION))  /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
                           || (Dem_Cfg_AdminData.ConfigurationId != Dem_Cfg_GlobalConfigurationId()) );

  if (lResetStoredData == TRUE)
  {
    /* If the NV data is not compatible to the configuration */
    /* Re-initialize all NV data content and reset the global time stamp */
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_Memory_AllEventMemEntriesIterType lEventMemEntryIter;

    Dem_Nvm_SetAllBlocksDirty();

    (void)Dem_NvM_InitAdminData();
    (void)Dem_NvM_InitStatusData();
#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
    (void)Dem_NvM_InitDebounceData();
#endif
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    (void)Dem_NvM_InitObdFreezeFrameData();
    if (Dem_Mem_PermanentGetInitPattern() != DEM_MEM_PERMANENT_INIT_PATTERN)
    { /* only initialize permanent memory if it was not initialized before */
      (void)Dem_NvM_InitObdPermanentData();
    }
#endif
#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
    (void)Dem_NvM_InitObdIumprData();
#endif
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
    (void)Dem_NvM_InitDtrData();
#endif
#if (DEM_FEATURE_NEED_AGING_DATA == STD_ON)
    (void)Dem_NvM_InitAgingData();
#endif
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON)
    (void)Dem_NvM_InitEventAvailableData();
#endif
    
    Dem_MemState_SetCurrentTimestamp(1U);
    Dem_MemState_MemorySetCurrentSize(Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PRIMARY), 0);                                 /* SBSW_DEM_CALL_MEMORYINFO_POINTER */

#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
    Dem_MemState_MemorySetCurrentSize(Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_SECONDARY), 0);                               /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
#endif
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    Dem_MemState_MemorySetCurrentSize(Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT), 0);                               /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
#endif

    for (Dem_Memory_AllEventMemEntries_IterInit(&lEventMemEntryIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Memory_AllEventMemEntries_IterExists(&lEventMemEntryIter) == TRUE;                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Memory_AllEventMemEntries_IterNext(&lEventMemEntryIter))                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      lMemoryIndex = Dem_Memory_AllEventMemEntries_IterGetMemoryIndex(&lEventMemEntryIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_MemoryEntry_Init(Dem_MemoryEntry_GetId(lMemoryIndex));
      Dem_MemState_MemoryUpdateInit(lMemoryIndex);
    }
  }
  /* Otherwise */
  else
  {
    Dem_MemState_SetCurrentTimestamp(0U);

    /* Rebuild the event memory control data from NV data contents */
    Dem_Memory_Init_RestoreMemory(Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PRIMARY));                                        /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
    Dem_Memory_Init_RestoreMemory(Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_SECONDARY));                                      /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
#endif

  }
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  /* In OBD configurations, initialize the visible OBD freeze frame */
  Dem_Mem_FreezeFrameIndexMode02 = Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame();
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  /* If prestore freeze frame is enabled, initialize freeze frame prestorage */
  Dem_Prestore_Init();
#endif

}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_Memory_InitConfirmedChronology
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_InitConfirmedChronology(
  void
  )
{
  Dem_MemPermanent_ConfirmedChronologyInit();
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_Memory_ConfirmedChronologyResetOverflown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronologyResetOverflown(
  void
  )
{
  Dem_MemPermanent_ConfirmedChronologyResetOverflown();
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_Memory_ConfirmedChronoAddEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronoAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  MasterEventId
  )
{
  Dem_MemPermanent_ConfirmedChronoAddEvent(MasterEventId, FALSE);
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_Memory_PermanentFillUp
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_PermanentFillUp(void)
{
  Dem_MemPermanent_FillUp();
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_Memory_ConfirmedChronoFreeEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronoFreeEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_MemPermanent_ConfirmedChronoFreeEvent(EventId);
}
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMORY_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Memory_Implementation.h
 *********************************************************************************************************************/
