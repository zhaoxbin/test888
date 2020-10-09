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
/*! \addtogroup Dem_MemStorageManager
 *  \{
 *  \file       Dem_MemStorageManager_Implementation.h
 *  \brief      Control storage of additional data for DTCs based on storage/update triggers.
 *  \details    Knows depending on storage/update triggers which data to store/change.
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

#if !defined (DEM_MEMSTORAGEMANAGER_IMPLEMENTATION_H)
#define DEM_MEMSTORAGEMANAGER_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemStorageManager_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_ExtDataElementIF_Implementation.h"
#include "Dem_ExtendedEntry_Implementation.h"
#include "Dem_SnapshotEntry_Implementation.h"
#include "Dem_MemState_Implementation.h"
#include "Dem_Cfg_Definitions.h"
#include "Dem_Data_Implementation.h"
#include "Dem_DataStorageIF_Implementation.h"
#include "Dem_UDSStatus_Implementation.h"
#include "Dem_Mem_Implementation.h"
                  
                                             /* Subcomponent Interface files */
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"
#include "Dem_Event_Interface.h"
#include "Dem_DTC_Interface.h"
#include "Dem_OperationCycle_Interface.h"

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
 * \addtogroup Dem_MemStorageManager_Properties
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
 * \addtogroup Dem_MemStorageManager_Private
 * \{
 */

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventUserERecs
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventUserERecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  )
{
  uint8 lBlockModification;
  uint8 lExtendedEntryIndex;
  Dem_ExtendedEntry_IterType lExtendedEntryIter;

  lBlockModification = DEM_DATA_NO_CHANGES;
  lExtendedEntryIndex = 0;
  
  for (Dem_ExtendedEntry_IterInit(EventId, &lExtendedEntryIter);                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_ExtendedEntry_IterExists(&lExtendedEntryIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_ExtendedEntry_IterNext(&lExtendedEntryIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_ERecIndexType lCfgERecIndex;
    lCfgERecIndex = Dem_ExtendedEntry_IterGet(&lExtendedEntryIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if (Dem_Cfg_ERecType(lCfgERecIndex) == DEM_CFG_EREC_TYPE_USER)
    {
      if ((Dem_Cfg_ERecUpdate(lCfgERecIndex) == TRUE)                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        || (Dem_ExtendedEntry_IteratorIsExtendedRecordStored(MemoryEntryId, lExtendedEntryIndex) == FALSE))
      {
        Dem_Data_DestinationBuffer lDestinationBuffer;
        Dem_ExtendedEntry_IteratorUpdateExtendedEntry(MemoryEntryId, lExtendedEntryIndex);

        Dem_Data_InitDestinationBuffer(&lDestinationBuffer,                                                                      /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
                                       Dem_MemoryEntry_GetExtendedRecordDataPtr(MemoryEntryId, lExtendedEntryIndex),
                                       Dem_Cfg_GlobalERecMaxRawSize());

        Dem_DataStorageIF_CollectERec(EventId, Dem_Cfg_ERecDid(lCfgERecIndex), &lDestinationBuffer);                             /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */

        lBlockModification = DEM_DATA_USERDATA_CHANGED;
      }
      else
      {
        /* MISRA */
      }
      lExtendedEntryIndex +=1;
    }
  }

  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventSRecs
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
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventSRecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  UpdateFlags
  )
{
  uint8 lBlockModification;
# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
  uint8 lLastStoredEntryIndex;
# endif
  Dem_SnapshotEntry_IterType lSnapshotEntryIter;

  lBlockModification = DEM_DATA_NO_CHANGES;
# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
  lLastStoredEntryIndex = 0xffU; /* Invalid */
# endif

  for (Dem_SnapshotEntry_IteratorInit(EventId, MemoryEntryId, &lSnapshotEntryIter);                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
       Dem_SnapshotEntry_IteratorExists(&lSnapshotEntryIter) == TRUE;                                                            /* SBSW_DEM_POINTER_FORWARD_STACK */
       Dem_SnapshotEntry_IteratorNext(&lSnapshotEntryIter))                                                                      /* SBSW_DEM_POINTER_FORWARD_STACK */
  {
    Dem_Cfg_SRecIndexType lCfgSRecIndex;

    lCfgSRecIndex = Dem_SnapshotEntry_IteratorGetSnapshotRecordIndex(&lSnapshotEntryIter);                                       /* SBSW_DEM_POINTER_FORWARD_STACK */

    /* If an update is needed: Updates are required when the configured trigger matches,
     * and the record is either not stored or configured for updates */
    if ( (                                                                                                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
# if (DEM_FEATURE_NEED_SREC_OEMTRIGGER == STD_ON)
           (Dem_MemStorageManager_TestOemSRecTrigger(EventId, MemoryEntryId, lCfgSRecIndex, UpdateFlags)) ||
# endif
           (Dem_Cfg_SRecTrigger(lCfgSRecIndex) == (UpdateFlags & Dem_Cfg_SRecTrigger(lCfgSRecIndex))) ) &&
         (  (Dem_Cfg_SRecUpdate(lCfgSRecIndex) == TRUE) 
         || (Dem_SnapshotEntry_IteratorIsSnapshotRecordStored(&lSnapshotEntryIter) == FALSE))                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
       )
    {
      Dem_SnapshotEntry_IteratorUpdateSnapshotEntry(&lSnapshotEntryIter);                                                        /* SBSW_DEM_POINTER_FORWARD_STACK */

# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
      /* For configured snapshot numbers, if the snapshot is already collected copy its data */
      if (lLastStoredEntryIndex != 0xffU)
      {
        Dem_SnapshotEntry_IteratorCopySnapshotEntry(&lSnapshotEntryIter, lLastStoredEntryIndex);                                 /* SBSW_DEM_POINTER_FORWARD_STACK */
      }
      else
# endif
      {
# if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
        /* If 'prestore freezeframe' is enabled and data is prestored, copy the prestored data */
        if (Dem_DataStorageIF_PrestorageApplySRec(Dem_MemoryEntry_GetSnapshotRecordDataPtr(                                      /* SBSW_DEM_POINTER_SNAPSHOT_BUFFER */
                                                  lSnapshotEntryIter.MemoryEntryId, 
                                                  lSnapshotEntryIter.SnapshotEntryIndex),                                                                                                
                                                  Dem_Cfg_EventSRecMaxRawSize()) == FALSE)
# endif
        {
          /* Otherwise, collect new samples from the application. */
          Dem_DataStorageIF_CollectSnapshot(EventId,                                                                             /* SBSW_DEM_POINTER_SNAPSHOT_BUFFER */
                                            Dem_MemoryEntry_GetSnapshotRecordDataPtr(lSnapshotEntryIter.MemoryEntryId, 
                                                                            lSnapshotEntryIter.SnapshotEntryIndex),
                                            Dem_Cfg_EventSRecMaxRawSize());
# if (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
          lLastStoredEntryIndex = Dem_SnapshotEntry_IteratorGetSnapshotEntryIndex(&lSnapshotEntryIter);                          /* SBSW_DEM_POINTER_FORWARD_STACK */
# endif
        }
        lBlockModification = DEM_DATA_USERDATA_CHANGED;
      }
      /* For calculated snapshot records, processing is completed */
# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
      break;
# endif
    }
  }

  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateGlobalSRecs
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateGlobalSRecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  UpdateFlags
  )
{
  uint8 lBlockModification;

  lBlockModification = DEM_DATA_NO_CHANGES;

  /* If an update is needed: Updates are required when the configured trigger matches,
    * and the record is either not stored or configured for updates */
  if ((Dem_Cfg_GlobalSRecTrigger() == (UpdateFlags & Dem_Cfg_GlobalSRecTrigger()))                                               /* PRQA S 3415 */ /* MD_DEM_12.4_cf */ /* COV_DEM_UNSUPPORTED_COMBINATION_GLOBAL_SRECS */
     && ((Dem_Cfg_GlobalSRecUpdate() == TRUE)                                                                                    
       ||(Dem_MemoryEntry_TestGlobalSnapshotRecordStored(MemoryEntryId) == FALSE))                                               
     )
  {
    Dem_MemoryEntry_SetGlobalSnapshotRecordStored(MemoryEntryId, TRUE);

# if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)     
    /* If 'prestore freezeframe' is enabled and data is prestored, copy the prestored data */
    if (Dem_DataStorageIF_PrestorageApplyGlobalSRec(Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr(MemoryEntryId),               /* SBSW_DEM_POINTER_GLOBAL_SNAPSHOT_BUFFER */                                                                         
                                                    Dem_Cfg_GlobalSRecMaxRawSize()) == FALSE)
# endif
     {
      /* Collect new samples from the application. */
       Dem_DataStorageIF_CollectGlobalSnapshot(EventId,                                                                          /* SBSW_DEM_POINTER_GLOBAL_SNAPSHOT_BUFFER */
                                                Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr(MemoryEntryId),
                                                Dem_Cfg_GlobalSRecMaxRawSize());
     }

     lBlockModification = DEM_DATA_USERDATA_CHANGED;

   }

  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventJ1939FF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventJ1939FF(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  )
{
# if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  if (Dem_DataStorageIF_PrestorageApplyJ1939FF(Dem_MemoryEntry_GetJ1939FreezeFramePtr(MemoryEntryId),                            /* SBSW_DEM_POINTER_J1939FREEZEFRAME_BUFFER */
                                      Dem_Cfg_GlobalJ1939FFTotalRawSize()) == FALSE)
# endif
  {
    Dem_DataStorageIF_CollectJ1939FreezeFrame(EventId,                                                                           /* SBSW_DEM_POINTER_J1939FREEZEFRAME_BUFFER */
                                     Dem_MemoryEntry_GetJ1939FreezeFramePtr(MemoryEntryId),
                                     Dem_Cfg_GlobalJ1939FFTotalRawSize());
  }
  return DEM_DATA_USERDATA_CHANGED;
}
#endif

#if (DEM_FEATURE_NEED_SREC_OEMTRIGGER == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_TestOemSRecTrigger
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemStorageManager_TestOemSRecTrigger(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_SRecIndexType, AUTOMATIC)  SRecIndex,
  CONST(uint8, AUTOMATIC)  UpdateFlags
  )
{
  boolean lReturnValue;

  if (Dem_Cfg_SRecTrigger(SRecIndex) != DEM_CFG_TRIGGER_OEM)
  {
    lReturnValue = FALSE;
  }
  else
  {
# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
    {
      /* If the event is already confirmed, do not allow an update. */
      /* Status bits are stored to the event memory after collecting data */
      if (Dem_UDSStatus_Test_CDTC(Dem_Event_GetUDSStatus(EventId)) == TRUE)
      {
        lReturnValue = FALSE;
      }
      /* If the event was already tested 'failed', update with every first failed event per cycle */
      else if (DEM_DTC_TEST_PC_STATUS_TFSLC(Dem_MemoryEntry_GetPreConfirmedStatus(MemoryEntryId)) == TRUE)
      {
        /* Note: here the event was tested failed, but has not confirmed yet */
        lReturnValue = (boolean)(0 != (UpdateFlags & (DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE)));
      }
      /* Otherwise, update once per cycle on a preconfirmed trigger */
      else
      {
        /* Note: here the event is not yet tested */
        lReturnValue = (boolean)((DEM_CFG_TRIGGER_FDC | DEM_CFG_TRIGGER_FIRSTTHISCYCLE)
          == (UpdateFlags & (DEM_CFG_TRIGGER_FDC | DEM_CFG_TRIGGER_FIRSTTHISCYCLE)));
      }
    }
# endif
# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_JLR == STD_ON)
    {
      DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
      
      /* Status bits are stored to the event memory after collecting data */
      if (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(EventId)) == TRUE)
      {
        lReturnValue = FALSE;
      }
      else
      {
        lReturnValue = (boolean)(0 != (UpdateFlags & (DEM_CFG_TRIGGER_PENDING | DEM_CFG_TRIGGER_CONFIRMED)));
      }
    }
# endif
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_TestObdIIFreezeFrameUpdates
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_TestObdIIFreezeFrameUpdates(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects,
  CONST(uint8, AUTOMATIC)  FreezeFrameIndex
  )
{
  uint8 lUpdates;
  Dem_EventIdType lMasterEventId;

  lUpdates = 0;
  lMasterEventId = Dem_Cfg_GetMasterEvent(EventId);

  if (Dem_Mem_FreezeFrameGetEvent(FreezeFrameIndex) == lMasterEventId)
  { /* 0-Trip events have both confirmed and pending triggers simultaneously, prioritize confirmed trigger */
    if ((Effects & DEM_CFG_TRIGGER_CONFIRMED) != 0)
    { /* If configured, confirmed trigger sets visibility flag */
# if (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
      if ((DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE)                                  /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        || (Dem_Cfg_EventTripTarget(EventId) == 0))
      {
        lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_VISIBILITY);
      }
      lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_TIMESTAMP);
# endif
      /* If configured, confirmed trigger updates the data */
# if (DEM_CFG_SUPPORT_PENDING_UPDATE_FREEZE_FRAME == STD_ON)
      lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_DATA);
# endif
    }
  }
  else
  { /* 0-Trip events have both confirmed and pending triggers simultaneously, prioritize confirmed trigger */
    if ((Effects & DEM_CFG_TRIGGER_CONFIRMED) != 0)
    {
# if ((DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON))
      if ((DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE)                                  /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        || (Dem_Cfg_EventTripTarget(EventId) == 0))
#endif
      {
        lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_VISIBILITY);
      }
      lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_DATA);
    }
# if (DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_ON)
    else /* ((Effects & DEM_CFG_TRIGGER_PENDING) != 0) */
    {
#  if (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_OFF)
      lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_VISIBILITY);
#  endif
      lUpdates = (uint8)(lUpdates | DEM_DATA_FF_UPDATE_DATA);
    }
# endif
  }

  return lUpdates;
}
#endif

#if (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateDAGEnvData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemStorageManager_UpdateDAGEnvData(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lExternalTester;
  Dem_MemoryEntry_HandleType lMemoryEntryId;

  lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
  /* Buffer Layout:
      [0]:    Status, 0.0 Presence Flag (Distinguish initial entry from updates)
                      0.1 external tester present
      [1][2]: Original Odometer Value
      [3][4]: MostRecent Odometer Value
      [5-8]:  Operating Time*
      [9]:    Operating Time Status*
    *: only with DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA
  */
  Dem_ExtDataElementIF_DagGetExternalTester(&lExternalTester);                                                                               /* SBSW_DEM_POINTER_FORWARD_STACK */
  Dem_ExtDataElementIF_DagGetCurrentOdometer(lMemoryEntryId);
  #if (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
  /* Always store the operating time, even if the event only wants the standard version.
      Output resolves the different records later */
  Dem_ExtDataElementIF_DagGetOperatingTime(lMemoryEntryId);
  #endif

  if (Dem_MemoryEntry_GetStdEnvData(lMemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_STATUS) == 0x00U)
  {
    /* Set original odometer to the same value as most recent odometer */
    Dem_MemoryEntry_SetStdEnvData(lMemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_FIRSTODOMETER, 
                                  Dem_MemoryEntry_GetStdEnvData(lMemoryEntryId, 
                                  DEM_MEMORYENTRY_STDENVDATA_CURRENTODOMETER));
    Dem_MemoryEntry_SetStdEnvData(lMemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_FIRSTODOMETER + 1, 
                                  Dem_MemoryEntry_GetStdEnvData(lMemoryEntryId, 
                                  DEM_MEMORYENTRY_STDENVDATA_CURRENTODOMETER + 1));
  }

  /* The external tester flag is bit 1, not bit 0 (see Standardized Diagnostic Data) */
  if (lExternalTester == TRUE)
  {
    Dem_MemoryEntry_SetStdEnvData(lMemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_STATUS, 0x3U);
  }
  else
  {
    Dem_MemoryEntry_SetStdEnvData(lMemoryEntryId, DEM_MEMORYENTRY_STDENVDATA_STATUS, 0x1U);
  }
}
#endif

/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventEntryOnTestFailed
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnTestFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lBlockModification;
  lBlockModification = DEM_DATA_NO_CHANGES;

#if (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
  Dem_MemStorageManager_UpdateDAGEnvData(MemoryIndex);
  lBlockModification = DEM_DATA_SET_USERDATA_CHANGED(lBlockModification);      
#endif

# if (DEM_CFG_PROCESS_OCCTR_CONFIRMED == STD_ON)
  if (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(EventId)) == TRUE)
# endif
  {
    if (Dem_MemoryEntry_IncrementOccurrenceCounter(Dem_MemoryEntry_GetId(MemoryIndex)) == TRUE)
    {
      lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
    }
  }

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF)
# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
  {
    Dem_DTC_SetAgingCounter(EventId, MemoryIndex, DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID);
#  if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    Dem_MemoryEntry_SetAgingTimer(Dem_MemoryEntry_GetId(MemoryIndex), DEM_MEMORYENTRY_AGINGTIME_INVALID);
#  endif
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }
# endif
#endif

#if (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
  {
    if (Dem_MemoryEntry_GetCyclesSinceFirstFailed(Dem_MemoryEntry_GetId(MemoryIndex)) 
          == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
    {
      Dem_MemoryEntry_SetCyclesSinceFirstFailed(Dem_MemoryEntry_GetId(MemoryIndex),
                                                Dem_OperationCycle_GetCycleCounter(
                                                Dem_Cfg_EventOperationCycle(EventId)));
      lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
    }
  }
#endif

#if (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
  {
# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
    Dem_MemoryEntry_SetDebounceValueMax(Dem_MemoryEntry_GetId(MemoryIndex), 
                                        Dem_Cfg_EventFailedTarget(EventId));
# else
    Dem_MemoryEntry_SetDebounceValueMax(Dem_MemoryEntry_GetId(MemoryIndex), (sint16)0x7F);
# endif
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
  lBlockModification |= Dem_MemStorageManager_UpdateEventUserERecs(EventId, 
                                                                   Dem_MemoryEntry_GetId(MemoryIndex));
# endif
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventEntryOnTestFailedThisCycle
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnTestFailedThisCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lBlockModification;
  lBlockModification = DEM_DATA_NO_CHANGES;

  if (Dem_MemoryEntry_IncrementFailedCycleCounter(Dem_MemoryEntry_GetId(MemoryIndex)) == TRUE)
  {
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }
  if (Dem_MemoryEntry_IncrementConsecutiveFailedCycleCounter(Dem_MemoryEntry_GetId(MemoryIndex)) == TRUE)
  {
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }
# if (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
  {
    Dem_MemoryEntry_SetCyclesSinceLastFailed(Dem_MemoryEntry_GetId(MemoryIndex), 
                                             Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventOperationCycle(EventId)));
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif

  return lBlockModification;
}

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateVCCEventEntryOnTestFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateVCCEventEntryOnTestFailed(                                                                                 
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex, 
  CONST(boolean, AUTOMATIC)  WIRIndicatorTriggered
  )
{
  uint8 lPreconfirmedStatus;
  Dem_MemoryEntry_HandleType lMemoryEntryId;
  uint8 lBlockModification;

  lBlockModification = DEM_DATA_NO_CHANGES;
  lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
  lPreconfirmedStatus = Dem_MemoryEntry_GetPreConfirmedStatus(lMemoryEntryId);
  lPreconfirmedStatus = DEM_DTC_SET_PC_STATUS_TFSLC(lPreconfirmedStatus);
  if (WIRIndicatorTriggered == TRUE)
  {
    lPreconfirmedStatus = DEM_DTC_SET_PC_STATUS_WIRSLC(lPreconfirmedStatus);
  }

  Dem_MemoryEntry_SetPreConfirmedStatus(lMemoryEntryId, lPreconfirmedStatus);
  lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);

  return lBlockModification;
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
 * \addtogroup Dem_MemStorageManager_Public
 * \{
 */

/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventMemoryStatistics
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventMemoryStatistics(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(boolean, AUTOMATIC)  Occurrence
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;
  uint8 lBlockModification;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(Dem_Cfg_EventDestination(EventId));
  lBlockModification = DEM_DATA_NO_CHANGES;

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON) || (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
  {
    Dem_MemoryEntry_HandleType lMemoryEntryId;
    lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
    if (
#  if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
        (Dem_DTC_GetAgingCounter(EventId, lMemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
#  endif
#  if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON) && (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
      ||
#  endif
#  if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
        (DEM_MEM_TEST_AGING_ONLY(Dem_MemoryEntry_GetState(lMemoryEntryId)) == TRUE)
#  endif
      )
    {
      /* Re-Initialize the memory entry - this will reset special flags like aging only */
      Dem_MemoryEntry_InitializeEntry(lMemoryEntryId);

      lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
    }
  }
# endif
#endif
  if (Occurrence == TRUE)
  {
    /* On re-occurrence also update the chronology */
    Dem_MemState_MemoryUpdateIndex(lMemoryInfo, MemoryIndex);                                                                    /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
    lBlockModification = DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
  }

  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MemStorageManager_UpdateEventEntry
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
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lBlockModification;

  lBlockModification = DEM_DATA_NO_CHANGES;

  if (MemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
  {
    Dem_MemState_MemoryUpdateStart(MemoryIndex);

    /* On a TestFailed trigger */
    if ((UpdateFlags & DEM_CFG_TRIGGER_TESTFAILED) != 0)
    {
      lBlockModification |= Dem_MemStorageManager_UpdateEventEntryOnTestFailed(EventId, MemoryIndex);
    }

    /* On a TestFailedThisCycle trigger */
    if ((UpdateFlags & DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE) != 0)
    {
      lBlockModification |= Dem_MemStorageManager_UpdateEventEntryOnTestFailedThisCycle(EventId, MemoryIndex);
    }

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
    if ((UpdateFlags & (DEM_CFG_TRIGGER_TESTFAILED|DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE)) != 0)
      /* Set SI.30 bit 7 */
    {
      boolean lWirIndicatorTriggered;
      if ((UpdateFlags & DEM_CFG_TRIGGER_INDICATOR) != 0)
      {
        lWirIndicatorTriggered = TRUE;
      }
      else
      {
        lWirIndicatorTriggered = FALSE;
      }

      lBlockModification |= Dem_MemStorageManager_UpdateVCCEventEntryOnTestFailed(MemoryIndex, lWirIndicatorTriggered);
    }

# if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
    if ((DEM_CFG_TRIGGER_FDC | DEM_CFG_TRIGGER_FIRSTTHISCYCLE) == 
         (UpdateFlags & (DEM_CFG_TRIGGER_FDC | DEM_CFG_TRIGGER_FIRSTTHISCYCLE)))
    {
      lBlockModification |= Dem_MemStorageManager_UpdateEventUserERecs(EventId, 
                            Dem_MemoryEntry_GetId(MemoryIndex));
    }
# endif
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
# if (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
    if ((UpdateFlags & DEM_CFG_TRIGGER_TESTFAILED) != 0)
# endif
    {
      lBlockModification |= Dem_MemStorageManager_UpdateEventSRecs(EventId, 
                                                                   Dem_MemoryEntry_GetId(MemoryIndex),
                                                                   UpdateFlags);
    }
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
    {
      lBlockModification |= Dem_MemStorageManager_UpdateGlobalSRecs(EventId,
                                                                    Dem_MemoryEntry_GetId(MemoryIndex),
                                                                    UpdateFlags);
    }
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
    if ( (Dem_Cfg_EventJ1939Dtc(EventId) != DEM_CFG_DTC_J1939_INVALID)
      && ((UpdateFlags & DEM_CFG_TRIGGER_CONFIRMED) != 0) )
    {
      lBlockModification |= Dem_MemStorageManager_UpdateEventJ1939FF(EventId,
                                                                     Dem_MemoryEntry_GetId(MemoryIndex));
    }
#endif

    Dem_MemState_MemoryUpdateFinish(MemoryIndex);
  }

  /* In rare cases this function does nothing */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  return lBlockModification;
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_TriggerWwhObdFreezeFrameStorage
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_TriggerWwhObdFreezeFrameStorage(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lReturnValue;

  lReturnValue = DEM_DATA_NO_CHANGES;
  if (DEM_MEM_INVALID_MEMORY_INDEX != MemoryIndex)
  {
    if ( (((Effects & DEM_CFG_TRIGGER_PENDING) != 0)                                                                             /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(EventId)) == FALSE))
# if (DEM_CFG_SUPPORT_PENDING_UPDATE_FREEZE_FRAME == STD_ON)
      || ((Effects & DEM_CFG_TRIGGER_CONFIRMED) != 0)
# endif
      )
    {
      lReturnValue = Dem_Mem_StoreWwhObdFreezeFrame(EventId, MemoryIndex);
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_TriggerObdIIFreezeFrameStorage
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemStorageManager_TriggerObdIIFreezeFrameStorage(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects
  )
{
  if ( ((Effects & DEM_CFG_TRIGGER_CONFIRMED) != 0)
# if (DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_ON)
    || ((Effects & DEM_CFG_TRIGGER_PENDING) != 0)
# endif
    )
  {
    uint8 lFreezeFrameSlot;
    boolean lDisplacePendingFreezeFrame;

# if (DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON)
    if ((Effects & DEM_CFG_TRIGGER_CONFIRMED) != 0)
    {
      lDisplacePendingFreezeFrame = TRUE;
    }
    else
# endif
    {
      lDisplacePendingFreezeFrame = FALSE;
    }

    /* Checks if a free freezeframe slot is available */
    lFreezeFrameSlot = Dem_Mem_FindOBDIIFreezeFrameSlot(EventId, lDisplacePendingFreezeFrame);
    
    /* If a freeze frame slot is found, calculate the required updates */
    if (lFreezeFrameSlot != Dem_Cfg_GlobalObdIIFFCount())
    {
      uint8 lRequiredUpdates = Dem_MemStorageManager_TestObdIIFreezeFrameUpdates(EventId, Effects, 
                                                                                 lFreezeFrameSlot);
      Dem_Mem_StoreOBDIIFreezeFrame(EventId, lFreezeFrameSlot, lRequiredUpdates);
    }
  }
}                                                                                                                                
#endif 

#if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
/* ****************************************************************************
 % Dem_MemStorageManager_TestCycleCounterLatched
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemStorageManager_TestCycleCounterLatched(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC)  CycleCount
  )
{
  boolean lReturnValue;
  lReturnValue = FALSE;

# if (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
  if ((Dem_MemoryEntry_GetCyclesSinceFirstFailed(MemoryEntryId) < DEM_OPERATIONCYCLE_CYCLECOUNT_MAX)                             /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_OperationCycle_CycleCountDistance(Dem_MemoryEntry_GetCyclesSinceFirstFailed(MemoryEntryId), 
                                              CycleCount) >= 0xffU))
  {
    Dem_MemoryEntry_SetCyclesSinceFirstFailed(MemoryEntryId, DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED);
    lReturnValue = TRUE;
  }
# endif
# if (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
  if ((Dem_MemoryEntry_GetCyclesSinceLastFailed(MemoryEntryId) < DEM_OPERATIONCYCLE_CYCLECOUNT_MAX)                              /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_OperationCycle_CycleCountDistance(Dem_MemoryEntry_GetCyclesSinceLastFailed(MemoryEntryId), 
                                              CycleCount) >= 0xffU))
  {
    Dem_MemoryEntry_SetCyclesSinceLastFailed(MemoryEntryId, DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED);
    lReturnValue = TRUE;
  }
# endif
  return lReturnValue;
}
#endif

#if ( (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON) \
   || (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) )
/* ****************************************************************************
 % Dem_MemStorageManager_UpdateCycleCounter
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemStorageManager_UpdateCycleCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  CycleStatus
)
{
  uint8 lDtcStatus;
  boolean lBlockModification;

  lDtcStatus = Dem_DTC_ApplyCombinedStatus(Dem_DTC_GetDTCStatus(EventId));
  lBlockModification = FALSE;

  if ( ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STOPPED) != 0)                                                                   /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_UDSStatus_Test_TNCTOC(lDtcStatus) == FALSE) )
  {
#if ((DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) || (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON))
    if (Dem_UDSStatus_Test_TFTOC(lDtcStatus) == FALSE)
    { /* reset the 'consecutive failed cycles' */
      Dem_MemoryEntry_SetConsecutiveFailedCycleCounter(MemoryEntryId, 0);
      lBlockModification = TRUE;
    }
# endif

# if (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON)
#  if (DEM_CFG_STORAGE_AT_FDC == STD_ON)
    if (Dem_UDSStatus_Test_TFSLC(lDtcStatus) == TRUE)
#  endif
    {
      if (Dem_MemoryEntry_GetTestedCyclesSinceFirstFailed(MemoryEntryId) < 255)
      {
        Dem_MemoryEntry_SetTestedCyclesSinceFirstFailed(MemoryEntryId, 
                                                        (Dem_MemoryEntry_GetTestedCyclesSinceFirstFailed(MemoryEntryId)
                                                         + 1));
        lBlockModification = TRUE;
      }
    }
# endif
  }

  return lBlockModification;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMSTORAGEMANAGER_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemStorageManager_Implementation.h
 *********************************************************************************************************************/
