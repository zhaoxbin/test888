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
/*! \addtogroup Dem_MemoryRestoration
 *  \{
 *  \file       Dem_MemoryRestoration_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the Memory Restoration subcomponent which restores the status of a memory entry, 
 *              fixes memory entry allocation errors etc.
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

#if !defined (DEM_MEMORYRESTORATION_IMPLEMENTATION_H)
#define DEM_MEMORYRESTORATION_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryRestoration_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg_Definitions.h"
#include "Dem_Event_Implementation.h"
#include "Dem_DTC_Implementation.h"
#include "Dem_DTCInternalStatus_Implementation.h"
#include "Dem_UDSStatus_Implementation.h"
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_MemAccess_Implementation.h"
#include "Dem_MemState_Implementation.h"
#include "Dem_Nvm_Implementation.h"
#include "Dem_Error_Implementation.h"
                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_MemoryRestoration_Private
 * \{
 */

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreVccStatusBits
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
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_MemoryRestoration_RestoreVccStatusBits(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  uint8 lEventStatus;
  Dem_Event_InternalStatusType lInternalStatus;

  /* If the entry is aged, clear CDTC bit */
  lEventStatus = Dem_Event_GetUDSStatus(EventId);
  if (DEM_DTC_TEST_PC_STATUS_ADTC(Dem_MemoryEntry_GetPreConfirmedStatus(MemoryEntryId)) == TRUE)
  {
    lEventStatus = Dem_UDSStatus_Reset_CDTC(lEventStatus);
  }
  else
  {
    /* If there are consecutive failed cycles > 0, set PDTC and TFSLC bit */
    if (Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId) > 0)
    {
      lEventStatus = Dem_UDSStatus_Set_TFSLC(lEventStatus);
      lEventStatus = Dem_UDSStatus_Set_PDTC(lEventStatus);
    }

    /* If the consecutive failed cycles exceeded the trip target, set CDTC bit */
    if (Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId) > Dem_Cfg_EventTripTarget(EventId))
    {
      lEventStatus = Dem_UDSStatus_Set_CDTC(lEventStatus);
    }
  }

  /* Store the modified bits for the event */
  Dem_Event_SetUDSStatus(EventId, lEventStatus);

  /* Mark the event as ACTIVE */
  lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(InternalStatus, Dem_DTCInternalStatus_StoredStatus_Active);

  return lInternalStatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreStoredStatusFromEntry
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
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_MemoryRestoration_RestoreStoredStatusFromEntry(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId,
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  Dem_Event_InternalStatusType  lReturnValue;
  uint16  lAgingCounter;
  lAgingCounter = Dem_DTC_GetAgingCounter(EventId, MemoryEntryId);

  /* If the memory entry is currently aging, mark the event as AGING */
  if ((lAgingCounter <= DEM_OPERATIONCYCLE_CYCLECOUNT_MAX) || (lAgingCounter == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED))
  {
    lReturnValue = Dem_DTCInternalStatus_SetStoredStatus(InternalStatus, Dem_DTCInternalStatus_StoredStatus_Aging);
  }
  else
#if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
  /* Otherwise if aging keeps memory entries intact and the entry is aged, mark the event as AGED */
  if (lAgingCounter == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
  {
    lReturnValue = Dem_DTCInternalStatus_SetStoredStatus(InternalStatus, Dem_DTCInternalStatus_StoredStatus_Aged);
  }
  else
#endif /* (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON) */
  /* Otherwise: Mark the event as ACTIVE */
  {
    lReturnValue = Dem_DTCInternalStatus_SetStoredStatus(InternalStatus, Dem_DTCInternalStatus_StoredStatus_Active);
  }

  return lReturnValue;
}
#endif

#if ((DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF))
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreStatusBits_OnConfirmedStorage
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnConfirmedStorage(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  )
{
  /* If the event belongs to a combined group, ignore the event */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DEM_CFG_COMBINED_GROUP_INVALID == Dem_Cfg_EventCombinedGroup(EventId))
# endif
  {
    /* If retaining memory after aging is supported, ignore aged events 
       else process the event */
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) != DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
# endif
    {
      uint8 lEventStatus;
      lEventStatus = Dem_Event_GetUDSStatus(EventId);

      /* Since DTCs are stored only on confirmed, set CDTC and TFSLC bits */
      lEventStatus = Dem_UDSStatus_Set_TFSLC(lEventStatus);
      lEventStatus = Dem_UDSStatus_Set_CDTC(lEventStatus);

      /* If there are consecutive failed cycles, and cycles > 0, set PDTC bit */
# if ((DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) || (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON))
      if (Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId) > 0)
      {
        lEventStatus = Dem_UDSStatus_Set_PDTC(lEventStatus);
      }
# endif
      /* Store the modified bits for the event */
      Dem_Event_SetUDSStatus(EventId, lEventStatus);
    }
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_STORAGE_AT_FAILED == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF))
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreStatusBits_OnFailedStorage
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnFailedStorage(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  )
{
  /* If the event belongs to a combined group, ignore the event */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DEM_CFG_COMBINED_GROUP_INVALID == Dem_Cfg_EventCombinedGroup(EventId))
# endif
  {
    uint8 lEventStatus;
    lEventStatus = Dem_Event_GetUDSStatus(EventId);

    /* If retaining memory after aging is supported and memory entry is aged, clear TF bit */
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
    {
      lEventStatus = Dem_UDSStatus_Reset_TF(lEventStatus);
    }
    else
# endif
    {
      /* Set TFSLC bit */
      lEventStatus = Dem_UDSStatus_Set_TFSLC(lEventStatus);

# if ((DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) || (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON))
      /* If there are consecutive failed cycles > 0, set PDTC bit, as the last cycle(s) were 'failed' */
      if (Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId) > 0)
      {
        lEventStatus = Dem_UDSStatus_Set_PDTC(lEventStatus);
      }

      /* If the consecutive failed cycles exceeded the trip target, set CDTC bit */
      if (Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId) > Dem_Cfg_EventTripTarget(EventId))
      {
        lEventStatus = Dem_UDSStatus_Set_CDTC(lEventStatus);
      }
# else
      /* If event has trip target == 0, set CDTC bit */
      if (Dem_Cfg_EventTripTarget(EventId) == 0)
      {
        lEventStatus = Dem_UDSStatus_Set_CDTC(lEventStatus);
      }
# endif
    }

    /* Store the modified bits for the event */
    Dem_Event_SetUDSStatus(EventId, lEventStatus);
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_STORAGE_AT_FDC == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF))
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreStatusBits_OnFdcThresholdStorage
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnFdcThresholdStorage(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  )
{
  /* If the event belongs to a combined group, ignore the event */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DEM_CFG_COMBINED_GROUP_INVALID == Dem_Cfg_EventCombinedGroup(EventId))
# endif
  {
    uint8 lEventStatus;
    lEventStatus = Dem_Event_GetUDSStatus(EventId);

    /* If retaining memory after aging is supported and memory entry is aged, clear TF bit */
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
    {
      lEventStatus = Dem_UDSStatus_Reset_TF(lEventStatus);
    }
    else
# endif
    {
# if ((DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) || (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON))
      /* If there are consecutive failed cycles > 0, set PDTC and TFSLC bit, as the last cycle(s) had TFTOC set */
      if (Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId) > 0)
      {
        lEventStatus = Dem_UDSStatus_Set_TFSLC(lEventStatus);
        lEventStatus = Dem_UDSStatus_Set_PDTC(lEventStatus);
      }

      /* If the consecutive failed cycles exceeded the trip target, set CDTC bit */
      if (Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId) > Dem_Cfg_EventTripTarget(EventId))
      {
        lEventStatus = Dem_UDSStatus_Set_CDTC(lEventStatus);
      }

# elif ((DEM_CFG_DATA_OCCCTR_2BYTE == STD_ON) || (DEM_CFG_DATA_OCCCTR == STD_ON))
      /* If there is an occurrence counter > 0, set TFSLC bit, as we know about some TF 0->1 transitions */
      if (Dem_MemoryEntry_GetOccurrenceCounter(MemoryEntryId) > 0)
      {
        lEventStatus = Dem_UDSStatus_Set_TFSLC(lEventStatus);
      }
# endif
    }

    /* Store the modified bits for the event */
    Dem_Event_SetUDSStatus(EventId, lEventStatus);
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_STORAGE_AT_PENDING == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF))
/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreStatusBits_OnPendingStorage
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnPendingStorage(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  )
{
  /* If the event belongs to a combined group, ignore the event */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DEM_CFG_COMBINED_GROUP_INVALID == Dem_Cfg_EventCombinedGroup(EventId))
# endif
  {
    uint8 lEventStatus;
    lEventStatus = Dem_Event_GetUDSStatus(EventId);

    /* If retaining memory after aging is supported and memory entry is aged, unset TF bit */
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    if (Dem_DTC_GetAgingCounter(EventId, MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
    {
      lEventStatus = Dem_UDSStatus_Reset_TF(lEventStatus);
    }
    else
# endif
    {
      /* Set TFSLC bit */
      lEventStatus = Dem_UDSStatus_Set_TFSLC(lEventStatus);

# if ((DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) || (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON))
      /* If there are consecutive failed cycles > 0, set PDTC bit, as the last cycle(s) were 'failed' */
      if (Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId) > 0)
      {
        lEventStatus = Dem_UDSStatus_Set_PDTC(lEventStatus);
      }

      /* If the consecutive failed cycles exceeded the trip target, set CDTC bit */
      if (Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(MemoryEntryId) > Dem_Cfg_EventTripTarget(EventId))
      {
        lEventStatus = Dem_UDSStatus_Set_CDTC(lEventStatus);
      }
# else
      /* If event has trip target == 0, set CDTC bit */
      if (Dem_Cfg_EventTripTarget(EventId) == 0)
      {
        lEventStatus = Dem_UDSStatus_Set_CDTC(lEventStatus);
      }
# endif
    }

    /* Store the modified bits for the event */
    Dem_Event_SetUDSStatus(EventId, lEventStatus);
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                                /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
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
 * \addtogroup Dem_MemoryRestoration_Public
 * \{
 */

/* ****************************************************************************
 % Dem_MemoryRestoration_FixCorruptMemoryEntry
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryRestoration_FixCorruptMemoryEntry(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  boolean lReturnValue;
  Dem_MemoryEntry_HandleType lMemoryEntryId;
  Dem_EventIdType lEventId;

  lReturnValue = FALSE;
  lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
  lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);

  if (lEventId != DEM_EVENT_INVALID)
  {
    if ((lEventId >= Dem_Cfg_GlobalEventCount())                                                                                 /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      || (Dem_Cfg_EventDestination(lEventId) != Dem_MemState_MemoryGetId(MemoryInfo))                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      || (lEventId != Dem_Cfg_GetMasterEvent(lEventId))
#endif
      )
    {
      /* The memory entry is not allocated to the master event. Remove it. */
      Dem_MemoryEntry_SetEventId(lMemoryEntryId, DEM_EVENT_INVALID);
      Dem_MemoryEntry_SetTimestamp(lMemoryEntryId, 0U);
      Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);

      /* DET: To get this inconsistency, it requires a configuration change without clearing the NV contents */
      Dem_Error_ReportError(DEM_INIT_APIID, DEM_E_INCONSISTENT_STATE);

      lReturnValue = TRUE;  /* caller shall continue with next memory entry */
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MemoryRestoration_FixDoubleAllocation
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryRestoration_FixDoubleAllocation(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  boolean lReturnValue;
  Dem_MemoryEntry_HandleType lMemoryEntryId;
  Dem_EventIdType lEventId;

  lReturnValue = FALSE;
  lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
  lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);
  if (lEventId != DEM_EVENT_INVALID)
  {
    Dem_Event_InternalStatusType lInternalStatus;
    lInternalStatus = Dem_DTC_GetInternalStatus(lEventId);

    if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) != Dem_DTCInternalStatus_StoredStatus_None)
    { 
      /* Runtime error, no DET. This can happen due to NV errors */
      uint8 lOtherIndex;
      uint32 lTimestamp;

      /* Dem_MemAccess_MemoryFindIndex will always succeed since we are processing a duplicate */
      lOtherIndex = Dem_MemAccess_MemoryFindIndex_Checked(MemoryInfo, lEventId);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      lTimestamp = Dem_MemoryEntry_GetTimestamp(lMemoryEntryId);

      /* Clear the older memory entry */
      if (Dem_MemoryEntry_GetTimestamp(Dem_MemoryEntry_GetId(lOtherIndex)) < lTimestamp)
      {
        Dem_MemAccess_MemoryFreeIndex(MemoryInfo, lOtherIndex);                                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        Dem_Nvm_SetEventMemoryBlockState(lOtherIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
      }
      else
      {
        Dem_MemoryEntry_SetEventId(lMemoryEntryId, DEM_EVENT_INVALID);
        Dem_MemoryEntry_SetTimestamp(lMemoryEntryId, 0U);
        Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
        lReturnValue = TRUE;  /* caller shall continue with next memory entry */
      }
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6060 */ /* MD_MSR_STCAL, MD_MSR_STPAR */

/* ****************************************************************************
 % Dem_MemoryRestoration_RestoreEventStatus
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
Dem_MemoryRestoration_RestoreEventStatus(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Event_InternalStatusType lInternalStatus;
  lInternalStatus = Dem_DTC_GetInternalStatus(EventId);

  /* Dependent on the available redundancy, restore UDS status bits and the internal status */
#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)                                                                              /* PRQA S 0883 */ /* MD_DEM_19.15 */
  lInternalStatus = Dem_MemoryRestoration_RestoreVccStatusBits(MemoryEntryId, EventId, lInternalStatus);
#else
# if (DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON)
  Dem_MemoryRestoration_RestoreStatusBits_OnConfirmedStorage(MemoryEntryId, EventId);
# endif
# if (DEM_CFG_STORAGE_AT_FAILED == STD_ON)
  Dem_MemoryRestoration_RestoreStatusBits_OnFailedStorage(MemoryEntryId, EventId);
# endif
# if (DEM_CFG_STORAGE_AT_FDC == STD_ON)
  Dem_MemoryRestoration_RestoreStatusBits_OnFdcThresholdStorage(MemoryEntryId, EventId);
# endif
# if (DEM_CFG_STORAGE_AT_PENDING == STD_ON)
  Dem_MemoryRestoration_RestoreStatusBits_OnPendingStorage(MemoryEntryId, EventId);
# endif
  lInternalStatus = Dem_MemoryRestoration_RestoreStoredStatusFromEntry(MemoryEntryId, EventId, lInternalStatus);
#endif

  /*Store the modified internal status for the event*/
  Dem_DTC_SetInternalStatus(EventId, lInternalStatus);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_MEMORYRESTORATION_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemoryRestoration_Implementation.h
 *********************************************************************************************************************/
