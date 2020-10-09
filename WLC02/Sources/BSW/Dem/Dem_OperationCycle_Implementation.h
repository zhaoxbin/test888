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
/*! \addtogroup Dem_OperationCycle
 *  \{
 *  \file       Dem_OperationCycle_Implementation.h
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

#if !defined (DEM_OPERATIONCYCLE_IMPLEMENTATION_H)
#define DEM_OPERATIONCYCLE_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_OperationCycle_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_EventInternalStatus_Implementation.h"
#include "Dem_InitState_Implementation.h"
#include "Dem_Scheduler_Implementation.h"
#include "Dem_Nvm_Implementation.h"
#include "Dem_Mem_Implementation.h"
#include "Dem_Queue_Implementation.h"
#include "Dem_Indicator_Implementation.h"
#include "Dem_Notifications_Implementation.h"
#include "Dem_DTCInternalStatus_Implementation.h"
#include "Dem_MemObdFreezeFrame_Implementation.h"
                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Memory_Interface.h"
#include "Dem_Cfg_Declarations.h"
#include "Dem_Event_Interface.h"
#include "Dem_DTC_Interface.h"
#include "Dem_Esm_Interface.h"
#include "Dem_Error_Interface.h"



/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/
/*! Test if cycle change is pending for 'CycleId' */
#define Dem_OperationCycle_IsPendingCycle(CycleId)   ((Dem_OperationCycle_CycleFlag & ((uint8)(1U << (CycleId)))) != 0)          /* PRQA S 3453 */ /* MD_MSR_19.7 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Current operating cycle states */
DEM_LOCAL VAR(uint16, DEM_VAR_NOINIT)               Dem_OperationCycle_CurrentCycleState;
/*! Pending operating cycle states - protected by critical section DEM_EXCLUSIVE_AREA_1 (StateManager) */
DEM_LOCAL VAR(uint16, DEM_VAR_NOINIT)               Dem_OperationCycle_PendingCycleState;
/*! Operating cycle states update flags - protected by critical section DEM_EXCLUSIVE_AREA_1 (StateManager) */
DEM_LOCAL volatile VAR(uint16, DEM_VAR_NOINIT)      Dem_OperationCycle_CycleFlag;

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_OperationCycle_Properties
 * \{
 */
/* ****************************************************************************
 % Dem_OperationCycle_GetCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_OperationCycle_GetCycleCounter(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  return Dem_Cfg_AdminData.CycleCounter[CycleId];
}

/* ****************************************************************************
 % Dem_OperationCycle_SetCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetCycleCounter(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (CycleId >= Dem_Cfg_GlobalCycleCount())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_AdminData.CycleCounter[CycleId] = CycleCounter;                                                                      /* SBSW_DEM_ARRAY_WRITE_ADMINDATA_CYCLECOUNTER */
  }
}

/* ****************************************************************************
 % Dem_OperationCycle_GetCurrentCycleStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_OperationCycle_GetCurrentCycleStatus(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  return (uint8)(((Dem_OperationCycle_CurrentCycleState & (uint16)(1U << (CycleId))) != 0)
    ? DEM_OPERATIONCYCLE_CYCLE_STARTED
    : DEM_OPERATIONCYCLE_CYCLE_STOPPED);
}

/* ****************************************************************************
 % Dem_OperationCycle_SetCycleStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetCycleStatus(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  Status
  )
{
  uint16 lMask;

  lMask = (uint16)(1U << CycleId);
  if (Status == DEM_OPERATIONCYCLE_CYCLE_STOPPED)
  {
    lMask = (uint16) (~lMask);
    Dem_OperationCycle_CurrentCycleState = (uint16)(Dem_OperationCycle_CurrentCycleState & lMask);
  }
  else
  {
    Dem_OperationCycle_CurrentCycleState = (uint16)(Dem_OperationCycle_CurrentCycleState | lMask);
  }
}


/* ****************************************************************************
 % Dem_OperationCycle_AddCycleCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_OperationCycle_AddCycleCount(
  CONST(uint16, AUTOMATIC)  CurrentCounter,
  CONST(uint8, AUTOMATIC)  DeltaValue
  )
{
  uint16 lTargetCycle;

  lTargetCycle = (uint16)(CurrentCounter + DeltaValue);

  if (lTargetCycle > DEM_OPERATIONCYCLE_CYCLECOUNT_MAX)
  { /* Overflow needs to wrap around at DEM_OPERATIONCYCLE_CYCLECOUNT_MAX */
    lTargetCycle = (uint16)(lTargetCycle - DEM_OPERATIONCYCLE_CYCLECOUNT_MAX);
  }

  return lTargetCycle;
}

#if (DEM_FEATURE_NEED_AGING_CYCLE_DISTANCE == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_CycleCountDistance
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_OperationCycle_CycleCountDistance(
  CONST(uint16, AUTOMATIC)  CurrentCounter,
  CONST(uint16, AUTOMATIC)  TargetCounter
  )
{
  uint16 lReturnValue;

  if (TargetCounter < CurrentCounter)
  {
    lReturnValue = (uint16)((DEM_OPERATIONCYCLE_CYCLECOUNT_MAX - CurrentCounter) + TargetCounter);
  }
  else
  {
    lReturnValue = (uint16)(TargetCounter - CurrentCounter);
  }

  return lReturnValue;
}
#endif

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
 * \addtogroup Dem_OperationCycle_Private
 * \{
 */

/* ****************************************************************************
 % Dem_OperationCycle_GetPendingCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_OperationCycle_GetPendingCycle(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  return (uint8)(((Dem_OperationCycle_PendingCycleState & (uint16)(1U << CycleId)) != 0U)
          ? DEM_OPERATIONCYCLE_CYCLE_STARTED
          : DEM_OPERATIONCYCLE_CYCLE_STOPPED);
}

/* ****************************************************************************
 % Dem_OperationCycle_SetPendingCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_SetPendingCycle(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  Status
  )
{
  uint16 lMask = (uint16)(1U << CycleId);

  Dem_OperationCycle_CycleFlag = (uint16)(Dem_OperationCycle_CycleFlag | lMask);

  if (Status == DEM_OPERATIONCYCLE_CYCLE_STOPPED)
  {
    Dem_OperationCycle_PendingCycleState = (uint16)(Dem_OperationCycle_PendingCycleState & ((uint16)(~lMask)));
  }
  else
  {
    Dem_OperationCycle_PendingCycleState = (uint16)(Dem_OperationCycle_PendingCycleState | lMask);
  }

  Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_OperationCycle);
}

#if (DEM_FEATURE_NEED_OBD == STD_ON)    
/* ****************************************************************************
 % Dem_OperationCycle_QualifyDcy_IgnCycleCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_QualifyDcy_IgnCycleCounter(
  void
  )
{
# if (DEM_FEATURE_NEED_IUMPR == STD_ON)
  {
    boolean lFaultPending;
    Std_ReturnType lFiMStatus;

    /* increment ignition cycle counter when DCY is qualified and increment is not inhibited by an input fault */
    lFiMStatus = FiM_GetFunctionPendingStatus(Dem_Cfg_ObdIgnitionCycleFimFid(), &lFaultPending);                                 /* SBSW_DEM_POINTER_FORWARD_STACK */
    if ((lFiMStatus == E_OK) && (lFaultPending == FALSE))
    {
      Dem_Mem_SetIgnitionCycleCounter(Dem_Mem_GetIgnitionCycleCounter() + 1);
    }
  }
# endif
}
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_QualifyDcy
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
Dem_OperationCycle_QualifyDcy(
  void
  )
{
# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
  boolean lOldMilIsActive;

  lOldMilIsActive = Dem_Indicator_TestMilReportedActive();
# endif

  Dem_DTC_CycleQualifyDcy();
  
  /* Synchronize the global MIL state */
  Dem_Indicator_UpdateGlobalSpecialIndicatorStates(Dem_Cfg_GlobalMilIndicator());
# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
 if ( (lOldMilIsActive == FALSE)                                                                                                 /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_Indicator_TestMilReportedActive() == TRUE) )
  {
    Dem_Indicator_UpdatePIDsMilEnabled();
  }
# endif

 Dem_OperationCycle_QualifyDcy_IgnCycleCounter();

/* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */

  Dem_OperationCycle_SetObdCycleStates(DEM_OPERATIONCYCLE_SET_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()));

  Dem_LeaveCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: StateManager */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_FEATURE_NEED_OBD == STD_ON) */

/* ****************************************************************************
 % Dem_OperationCycle_ProcessCycles
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
Dem_OperationCycle_ProcessCycles(
  void
  )
{
  uint8 lCycleId;
  uint16 lDem_Queue_CycleState;
  uint16 lDem_Queue_CycleFlag;
  uint16 lObdDcyMask;
#if (DEM_FEATURE_NEED_OBD == STD_ON) 
  lObdDcyMask  = (uint16)(1U << Dem_Cfg_GlobalObdDrivingCycleId());
#else
  lObdDcyMask = 0;
#endif

/* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */

  lDem_Queue_CycleState = Dem_OperationCycle_PendingCycleState;
  Dem_OperationCycle_PendingCycleState = (uint16)(Dem_OperationCycle_PendingCycleState & lObdDcyMask);

  lDem_Queue_CycleFlag = Dem_OperationCycle_CycleFlag;
  /* Queue state for the OBD driving cycle has to be reset after processing to prevent new 
     restart while restart is still processed */
  Dem_OperationCycle_CycleFlag = (uint16)(Dem_OperationCycle_CycleFlag & lObdDcyMask);

  Dem_LeaveCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: StateManager */

  lCycleId = 0;
  while (lDem_Queue_CycleFlag != 0)
  {
    if ((lDem_Queue_CycleFlag & 0x01U) != 0)
    {
      uint8 lNewStatus;
      uint8 lOldStatus;
      lNewStatus = (uint8)(((lDem_Queue_CycleState & 0x01U) != 0)
        ? DEM_OPERATIONCYCLE_CYCLE_STARTED : DEM_OPERATIONCYCLE_CYCLE_STOPPED);
      lOldStatus = Dem_OperationCycle_GetCurrentCycleStatus(lCycleId);
      if (lNewStatus == DEM_OPERATIONCYCLE_CYCLE_STARTED)
      {
#if ((DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON))
        if ( (Dem_Cfg_CycleIsObdDcy(lCycleId) == TRUE)
          && (DEM_OPERATIONCYCLE_TEST_WARMUP_CYCLE(Dem_OperationCycle_GetObdCycleStates()) == TRUE) )
        { /* Move the WarmupCycle start to a different trigger
            (respective bit lDem_Queue_CycleFlag may not be set for warmup cycles) */
          Dem_OperationCycle_CycleUpdate(Dem_Cfg_GlobalWarmupCycleId(), DEM_OPERATIONCYCLE_CYCLE_RESTARTED);
        }        
#endif

        if (lNewStatus == lOldStatus)
        {
          Dem_OperationCycle_CycleUpdate(lCycleId, DEM_OPERATIONCYCLE_CYCLE_RESTARTED);
        }
        else
        {
          Dem_OperationCycle_CycleUpdate(lCycleId, DEM_OPERATIONCYCLE_CYCLE_STARTED);
        }
      }
      else
      {
        Dem_OperationCycle_CycleUpdate(lCycleId, DEM_OPERATIONCYCLE_CYCLE_STOPPED);
      }
    }
    ++lCycleId;
    lDem_Queue_CycleFlag = (uint16)(lDem_Queue_CycleFlag >> 1U);
    lDem_Queue_CycleState = (uint16)(lDem_Queue_CycleState >> 1U);
  }
#if (DEM_FEATURE_NEED_OBD == STD_ON) 
  /* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */       
  /* Reset the queue state for the OBD driving cycle after processing */
  Dem_OperationCycle_PendingCycleState = (uint16)(Dem_OperationCycle_PendingCycleState & (uint16)(~lObdDcyMask));
  Dem_OperationCycle_CycleFlag = (uint16)(Dem_OperationCycle_CycleFlag & (uint16)(~lObdDcyMask));
  Dem_LeaveCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* <<<< -------------------------------- Leave Critical Section: StateManager */
#endif
}

#if ((DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF) \
     && ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) || (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)))
/* ****************************************************************************
 % Dem_OperationCycle_ProcessCycleUpdate_StoredEvents
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
Dem_OperationCycle_ProcessCycleUpdate_StoredEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  )
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_Memory_AllEventMemEntriesIterType MemEntryIter;

  /* Iterate through the primary indices - the chronological index becomes
      invalid in case an event ages */
  for (Dem_Memory_AllEventMemEntries_IterInit(&MemEntryIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllEventMemEntries_IterExists(&MemEntryIter) == TRUE;                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllEventMemEntries_IterNext(&MemEntryIter))                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;

    lMemoryIndex = Dem_Memory_AllEventMemEntries_IterGetMemoryIndex(&MemEntryIter);                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lEventId = Dem_MemoryEntry_GetEventId(Dem_MemoryEntry_GetId(lMemoryIndex));
    if (Dem_Event_TestValidHandle(lEventId) == TRUE)
    {
# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
      if (Dem_Cfg_EventAgingCycle(lEventId) == CycleId)
      {
        Dem_DTC_AgingCycle(lEventId, CycleCounter, lMemoryIndex);
      }
# endif
# if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)      
      if (Dem_Cfg_EventOperationCycle(lEventId) == CycleId)
      {
        Dem_Memory_LatchCycleCounters(lMemoryIndex, CycleCounter);
      }
# endif
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_ProcessCycleUpdate_AllEvents
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
Dem_OperationCycle_ProcessCycleUpdate_AllEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  )
{
  Dem_OperationCycle_RecalculateAgingThreshold_AllEvents(CycleId, CycleCounter);

# if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
  {
    Dem_OperationCycle_LatchCycleCounters(CycleId, CycleCounter);
  }
# endif
}                                                                                                                                
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_RecalculateAgingThreshold_AllEvents
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
Dem_OperationCycle_RecalculateAgingThreshold_AllEvents(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  )
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_EventIdType lEventId;
  Dem_DTCInternal_StoredStatusType lStoredStatus;

  /* Iterate over all events, considering only Master Events,  */
  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  {
    /* Events which do not have a DTC configured need not be handled */
    if (Dem_Cfg_EventUdsDtc(lEventId) == DEM_CFG_DTC_UDS_INVALID)    
    {
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    /* Only process master events because combined events have the same DTC */
    if (Dem_Cfg_GetMasterEvent(lEventId) != lEventId)
    {
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }
# endif

    /* Event is currently active (normal case) or aging with a memory entry */
    lStoredStatus = Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(lEventId));
    if ( (lStoredStatus == Dem_DTCInternalStatus_StoredStatus_Active) 
      || (lStoredStatus == Dem_DTCInternalStatus_StoredStatus_Aging) )
    {
      if (Dem_Cfg_EventAgingCycle(lEventId) == CycleId)
      {
        lMemoryIndex = Dem_Memory_FindIndex_Checked(lEventId);
        if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
        {
          Dem_DTC_AgingCycle(lEventId, CycleCounter, lMemoryIndex);
        }
        continue;                                                                                                                /* PRQA S 0770 */ /* MD_DEM_14.5 */
      }
    }

    /* Event is currently aging without a memory entry */
    if (Dem_DTC_GetAgingStatus(lEventId) == Dem_DTC_AgingStatusInProgress)
    {
      if (Dem_Cfg_EventAgingCycle(lEventId) == CycleId)
      {
        Dem_DTC_AgingCycle(lEventId, CycleCounter, DEM_MEM_INVALID_MEMORY_INDEX);
      }
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON) && (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON))
/* ****************************************************************************
 % Dem_OperationCycle_LatchCycleCounters
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_LatchCycleCounters(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint16, AUTOMATIC)  CycleCounter
  )
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_Memory_AllEventMemEntriesIterType MemEntryIter;

  /* Iterate through the primary indices - the chronological index becomes
      invalid in case an event ages */
  for (Dem_Memory_AllEventMemEntries_IterInit(&MemEntryIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllEventMemEntries_IterExists(&MemEntryIter) == TRUE;                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllEventMemEntries_IterNext(&MemEntryIter))                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lEventId;

    lMemoryIndex = Dem_Memory_AllEventMemEntries_IterGetMemoryIndex(&MemEntryIter);                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lEventId = Dem_MemoryEntry_GetEventId(Dem_MemoryEntry_GetId(lMemoryIndex));
    if (Dem_Event_TestValidHandle(lEventId) == TRUE)
    {
      if (Dem_Cfg_EventOperationCycle(lEventId) == CycleId)
      {
        Dem_Memory_LatchCycleCounters(lMemoryIndex, CycleCounter);
      }
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */    
#endif

/* ****************************************************************************
 % Dem_OperationCycle_UpdateTestEventAffected
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
Dem_OperationCycle_UpdateTestEventAffected(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  boolean lReturnValue;
  lReturnValue = TRUE;

  if (Dem_Cfg_EventOperationCycle(EventId) != CycleId)
  { /* Event needs to depend on the modified cycle */
    lReturnValue = FALSE;
  }
#if (DEM_CFG_ISCONST_AVAILABLEINVARIANT != STD_ON)
  if (Dem_DTC_TestDtcAvailableInVariant(EventId) == FALSE)
  { /* Don't process unavailable DTCs */
    lReturnValue = FALSE;
  }
#endif
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (Dem_Cfg_GetMasterEvent(EventId) != EventId)
  { /* Make sure to only process each event once */
    lReturnValue = FALSE;
  }
#endif
  if (Dem_EventInternalStatus_TestEventDisconnected(Dem_DTC_GetInternalStatus(EventId)) == TRUE)
  { /* Don't process unavailable DTCs */
    lReturnValue = FALSE;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_OperationCycle_UpdateProcessEvent
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
Dem_OperationCycle_UpdateProcessEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  )
{
  Dem_DTC_UDSStatusType lOldDtcStatus;
  Dem_DTC_UDSStatusType lOldExternalDtcStatus;
  Dem_DTC_UDSStatusType lNewDtcStatus;

  {
    if (Dem_DTC_TestStoredStatus(EventId) == TRUE)
    {
      Dem_Memory_UpdateEventsCycleCounter(EventId, CycleStatus);
    }
  }

  lOldDtcStatus = Dem_DTC_GetDTCStatus(EventId);
  lOldExternalDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(EventId, lOldDtcStatus);
  Dem_DTC_OpCycle(EventId, CycleStatus);
  lNewDtcStatus = Dem_DTC_GetDTCStatus(EventId);

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  /* Process permanent memory healing */
  if (Dem_Event_TestMilSupport(EventId) == TRUE)
  {
    Dem_Data_PermanentEntryUpdate(EventId, lOldDtcStatus, lNewDtcStatus);
  }
#endif

  /* Skip notifications if the cycle is started during Dem_Init - the
  environment is not initialized yet and cannot handle callbacks */
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Notifications_DtcStatusChanged(EventId, 
                                       lOldExternalDtcStatus, 
                                       Dem_DTC_ApplyExternalOnlyStatus(EventId, lNewDtcStatus),
                                       DEM_NOTIFICATIONS_DTC_REINIT);
    Dem_Notifications_InitMonitorForFunction(EventId);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_OperationCycle_CycleUpdateReadiness
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
Dem_OperationCycle_CycleUpdateReadiness(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  )
{
  Dem_EventIdType lEventId;
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  uint8 lOldPermanentCount;
#endif

  /* Perform transitions due to cycle end or tick */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  lOldPermanentCount = Dem_Memory_GetNumAllocatedMemoryEntry(DEM_CFG_MEMORYID_PERMANENT);
#endif

  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  {
    if (Dem_OperationCycle_UpdateTestEventAffected(lEventId, CycleId) == TRUE)
    {
      Dem_OperationCycle_UpdateProcessEvent(lEventId, CycleStatus);
    }
  } /* while (lEventId > DEM_EVENT_INVALID) */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if ( (lOldPermanentCount == Dem_Cfg_GlobalPermanentMaxCount())                                                                 /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
     && (lOldPermanentCount > 
         Dem_Memory_GetNumAllocatedMemoryEntry(DEM_CFG_MEMORYID_PERMANENT)) )
  { /* One or more events healed from full permanent memory, fill up */
    Dem_Memory_PermanentFillUp();
  }
#endif
}

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_UpdateObdDcy_End
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
Dem_OperationCycle_UpdateObdDcy_End(
  void
  )
{
# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
  /* Reset PID aging counter if at least one DTC triggers the MIL */
  if (Dem_Indicator_TestMilReportedActive() == TRUE)
  {
    Dem_Mem_SetPidAgingCounter(DEM_MEM_PID_AGING_COUNTER_THRESHOLD);
  }
# endif
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  { /* Process B1 counter Healing */
    uint8 lB1HealingCounter;

    lB1HealingCounter = Dem_Mem_GetB1HealingCounter();

    if (lB1HealingCounter < DEM_DATA_B1_HEALING_COUNTER_THRESHOLD)
    {
      ++lB1HealingCounter;
      Dem_Mem_SetB1HealingCounter(lB1HealingCounter);
    }

    /* clear the B1 counter if it has healed */
    if ( (Dem_Indicator_GetDtcClassMILCount(DEM_ESM_WWHOBD_DTCCLASS_B1) == 0)
      && (lB1HealingCounter >= DEM_DATA_B1_HEALING_COUNTER_THRESHOLD) )
    {
      Dem_Mem_SetB1Counter(0);
    }
  }
  { /* Process Continuous MI counter Healing */
    uint8 lContinuousMiHealingCounter;

    lContinuousMiHealingCounter = Dem_Mem_GetContinuousMiHealingCounter();

    if (lContinuousMiHealingCounter == DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_LOCKED)
    { /* Start Healing */
      Dem_Mem_SetContinuousMiHealingCounter(0);
    }
    else if (lContinuousMiHealingCounter < DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_HEALED)
    {  /* Healing is active */
      ++lContinuousMiHealingCounter;

      if (lContinuousMiHealingCounter == DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_THRESHOLD)
      {
        lContinuousMiHealingCounter = DEM_DATA_CONTINUOUS_MI_HEALING_COUNTER_HEALED;
        Dem_Mem_SetContinuousMiAgingCounter(0);
        Dem_Mem_SetContinuousMiAgingTimer(0);
      }
      Dem_Mem_SetContinuousMiHealingCounter(lContinuousMiHealingCounter);
    }
    else
    {
      /* nothing to do here */
    }
  }
# endif
}
#endif /* (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) */

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_UpdateObdWarmup_End
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
Dem_OperationCycle_UpdateObdWarmup_End(
  void
  )
{
  uint8 lContinuousMiAgingCounter;

  lContinuousMiAgingCounter = Dem_Mem_GetContinuousMiAgingCounter();

  if (lContinuousMiAgingCounter < DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_AGED)
  { /* Aging is active, process MI aging counter */
    ++lContinuousMiAgingCounter;

    if (lContinuousMiAgingCounter == DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_THRESHOLD)
    {
      Dem_Mem_SetContinuousMiCounter(0);
      lContinuousMiAgingCounter = DEM_DATA_CONTINUOUS_MI_AGING_COUNTER_AGED;
      Dem_Mem_SetContinuousMiAgingTimer(DEM_DATA_CONTINUOUS_MI_AGING_TIMER_AGED);
    }
    Dem_Mem_SetContinuousMiAgingCounter(lContinuousMiAgingCounter);
  }
}
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_UpdateObdDcy_Start
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
Dem_OperationCycle_UpdateObdDcy_Start(
  void
  )
{
# if (DEM_FEATURE_NEED_IUMPR == STD_ON)
  /* ----- IUMPR handling at DCY restart ----- */
  /* the ratio status flags must be reset */
  {
    /* reset general denominator status bits to the following setting:
      * - general denominator not incremented
      * - general conditions not fulfilled
      * - general conditions not failed
      */
    Dem_Mem_SetGeneralDenominatorStatus(0);

    /* reset hybrid status to the following setting:
    * - hybrid ignition cycle counter not incremented
    */
    Dem_Mem_SetGlobalIumprHybridStatus(0);

    /* reset Numerators status to the following setting:
    * - Numerators Unlocked
    */
    Dem_Mem_SetGlobalNumeratorsLocked(0);

    /* update NvRam blocks */
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR), 
                                DEM_NVM_BLOCKSTATE_DIRTY);
    /* admin block has already been set to dirty at the beginning of this function */
  }
# endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */

# if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
  /* ----- MIL group handling at DCY restart ----- */
  {
    uint16  MilGroupIndex = Dem_Cfg_GlobalMilGroupCount();

    while (MilGroupIndex != DEM_CFG_MIL_GROUP_INVALID)
    {
      MilGroupIndex--;
      /* reset incremented flag for each MIL group */
      Dem_Mem_ResetMilGroupIncremented(MilGroupIndex);

      /* reset trip counter of MIL group if no events are pending */
      if (Dem_EventInternalStatus_GetMilGroupPendingCount(MilGroupIndex) == 0)
      {
        Dem_Mem_ResetMilGroupTripCount(MilGroupIndex);
      }
    }
  }
# endif /* (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON) */

  {
    uint8  lObdCycleStates;
    /* The reset of the DCY and the PFC cycle must be done at last,
     * so all preceding actions may use the correct states.
     */
/* >>>> -------------------------------- Enter Critical Section: StateManager */
    Dem_EnterCritical_StateManager();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */

    lObdCycleStates = Dem_OperationCycle_GetObdCycleStates();
    lObdCycleStates = DEM_OPERATIONCYCLE_RESET_DCY_QUALIFIED(lObdCycleStates);
    lObdCycleStates = DEM_OPERATIONCYCLE_RESET_PFC_CYCLE(lObdCycleStates);
# if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
    lObdCycleStates = DEM_OPERATIONCYCLE_RESET_WARMUP_CYCLE(lObdCycleStates);
# endif
    Dem_OperationCycle_SetObdCycleStates(lObdCycleStates);

    Dem_LeaveCritical_StateManager();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: StateManager */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_UpdateObdAging
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdAging(
  void
  )
{
  uint8 lPidAgingCounter;

  lPidAgingCounter = Dem_Mem_GetPidAgingCounter();

  if (lPidAgingCounter != 0)
  {
    --lPidAgingCounter;

    if (lPidAgingCounter == 0)
    { /* Reset the PIDs */
# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
/* >>>> -------------------------------- Enter Critical Section: NonAtomic32bit */
      Dem_EnterCritical_NonAtomic32bit();                                                                                        /* PRQA S 3109 */ /* MD_MSR_14.3 */
      /* Clear Odometer for MIL on */
      Dem_Mem_SetOdometerMilOn(0);
      Dem_LeaveCritical_NonAtomic32bit();                                                                                        /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: NonAtomic32bit */
# endif
# if (DEM_CFG_SUPPORT_PID4D == STD_ON)
      Dem_Mem_SetEngineTimeMilOn(0);
# endif
    }
    Dem_Mem_SetPidAgingCounter(lPidAgingCounter);
  }
}
#endif /* (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON) */


#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_UpdateObdWarmup_Start
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateObdWarmup_Start(
  void
  )
{
# if (DEM_CFG_SUPPORT_PID30 == STD_ON)
  uint8 lWarmUpCount;

  lWarmUpCount = Dem_Mem_GetWarmUpCountSinceClear();
  /* Check if counter is latched */
  if (lWarmUpCount < 0xffU)
  {
    lWarmUpCount++;
    Dem_Mem_SetWarmUpCountSinceClear(lWarmUpCount);
  }
# endif
# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
  /* Process PID aging if MIL is reported as inactive */
  if (Dem_Indicator_TestMilReportedActive() == FALSE)
  {
    Dem_OperationCycle_UpdateObdAging();
  }
# endif
}
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)  
/* ****************************************************************************
 % Dem_OperationCycle_SetStateObdDcy
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_OperationCycle_SetStateObdDcy(
  CONST(uint8, AUTOMATIC)  ObdDcyId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  )
{
  Std_ReturnType lReturnValue;

  lReturnValue = E_OK;

  /* The OBD driving cycle is always started but changes between qualified and not qualified */
  if (CycleState == DEM_CYCLE_STATE_START)
  { /* Qualify Driving Cycle */
    if ( (Dem_OperationCycle_IsPendingDcyCycle() == FALSE)
      && (DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == FALSE))
    { /* Queue the qualification of driving cycle unless already qualified */
      if (Dem_OperationCycle_IsPendingCycle(ObdDcyId) == FALSE)
      {
        Dem_OperationCycle_SetPendingDcyCycle();
        Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_OperationCycle);
      }
      else
      {
        /* Stop-Start shall notify the application that no action was taken */
        lReturnValue = E_NOT_OK;
      }
    }
  }
  else
  {
    /* Restart DCY */
    if (DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE)
    {
      if (Dem_OperationCycle_IsPendingCycle(ObdDcyId) == FALSE)
      {
        /* >>>> -------------------------------- Enter Critical Section: StateManager */
        Dem_EnterCritical_StateManager();                                                                                        /* PRQA S 3109 */ /* MD_MSR_14.3 */
        /* Qualified driving cycle is re-started */
        Dem_OperationCycle_SetPendingCycle(ObdDcyId, DEM_OPERATIONCYCLE_CYCLE_STARTED);

        Dem_LeaveCritical_StateManager();                                                                                        /* PRQA S 3109 */ /* MD_MSR_14.3 */
        /* <<<< -------------------------------- Leave Critical Section: StateManager */
      }
      else
      {
        /* Stop-Stop is silently ignored */
      }
    }
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_OperationCycle_SetStateNormalCycle
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
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_OperationCycle_SetStateNormalCycle(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  )
{
  uint8 lOldCycleStatus;
  lOldCycleStatus = Dem_OperationCycle_GetCurrentCycleStatus(CycleId);

  if ((lOldCycleStatus != DEM_OPERATIONCYCLE_CYCLE_STOPPED)
    || (CycleState != DEM_CYCLE_STATE_END))
  {
    /* >>>> -------------------------------- Enter Critical Section: StateManager */
    Dem_EnterCritical_StateManager();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */

    if (Dem_OperationCycle_IsPendingCycle(CycleId) == TRUE)
    {
      uint8 lPendingCycleStatus;

      lPendingCycleStatus = Dem_OperationCycle_GetPendingCycle(CycleId);

      if (lPendingCycleStatus == DEM_OPERATIONCYCLE_CYCLE_STOPPED)
      { /* START->END, END->START through two calls to the function is accepted and queued */
        if (CycleState == DEM_CYCLE_STATE_START)
        {                                                                                                                        /* PRQA S 0715 */ /* MD_MSR_1.1_715 */
          Dem_OperationCycle_SetPendingCycle(CycleId, DEM_OPERATIONCYCLE_CYCLE_STARTED);
        }
      }
    }
    else
    {
      Dem_OperationCycle_SetPendingCycle(CycleId,
        ((CycleState == DEM_CYCLE_STATE_START)
        ? DEM_OPERATIONCYCLE_CYCLE_STARTED
        : DEM_OPERATIONCYCLE_CYCLE_STOPPED)
        );
    }

    Dem_LeaveCritical_StateManager();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* <<<< -------------------------------- Leave Critical Section: StateManager */
  }
}

# if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_ProcessIgnHybridCounter
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
  Dem_OperationCycle_ProcessIgnHybridCounter(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  )
{
  /* increment optional ignition cycle counter once per driving cycle */
  if (CycleState == DEM_CYCLE_STATE_START)
  {
    if (DEM_ESM_TEST_IUMPR_IGN_CYC_HYBRID_INCREMENTED(Dem_Mem_GetGlobalIumprHybridStatus()) == FALSE)
    {
#  if (DEM_CFG_SUPPORT_CYCLE_IGNITION_HYBRID == STD_ON)
      Dem_Mem_SetIgnitionCycleCounterHybrid(Dem_Mem_GetIgnitionCycleCounterHybrid() + 1);
#  endif
      Dem_Mem_SetGlobalIumprHybridStatus(
        DEM_ESM_SET_IUMPR_IGN_CYC_HYBRID_INCREMENTED(Dem_Mem_GetGlobalIumprHybridStatus()));

      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_IUMPR), 
                                  DEM_NVM_BLOCKSTATE_DIRTY);
    }
  }
  Dem_OperationCycle_SetStateNormalCycle(CycleId, CycleState);
}
#endif

#if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_SetStateWarmUp
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_OperationCycle_SetStateWarmUp(
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  )
{  
  if (CycleState == DEM_CYCLE_STATE_START)
  { /* Don't actually start the cycle, only set flag this DCY */
    /* >>>> -------------------------------- Enter Critical Section: StateManager */
    Dem_EnterCritical_StateManager();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */

    Dem_OperationCycle_SetObdCycleStates(DEM_OPERATIONCYCLE_SET_WARMUP_CYCLE(Dem_OperationCycle_GetObdCycleStates()));

    Dem_LeaveCritical_StateManager();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* <<<< -------------------------------- Leave Critical Section: StateManager */
  }
  /* Else: Ignore */
}
#endif

/* ****************************************************************************
 % Dem_OperationCycle_CycleUpdateEnd
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
Dem_OperationCycle_CycleUpdateEnd(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  uint16 lCycleCounter;
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  uint8 lMode02FreezeFrameOld;
  lMode02FreezeFrameOld = Dem_Mem_FreezeFrameIndexMode02;
#endif
  /* Tick the cycle if necessary */
  lCycleCounter = Dem_OperationCycle_GetCycleCounter(CycleId);
  lCycleCounter = Dem_OperationCycle_AddCycleCount(lCycleCounter, 1U);
  Dem_OperationCycle_SetCycleCounter(CycleId, lCycleCounter);

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) || (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
  /* Aging cycle start */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  Dem_OperationCycle_ProcessCycleUpdate_AllEvents(CycleId, lCycleCounter);
# else
  Dem_OperationCycle_ProcessCycleUpdate_StoredEvents(CycleId, lCycleCounter);
# endif
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  /* If no Event is visible (index has changed during aging) in Mode02 after aging, scan for a new one */
  if (lMode02FreezeFrameOld != Dem_Mem_FreezeFrameIndexMode02)
  {
    Dem_Mem_FreezeFrameIndexMode02 = Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame();
  }
#endif
}

#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_CycleUpdateStart
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdateStart(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  if (Dem_Cfg_CycleIsObdDcy(CycleId) == TRUE)
  {
    Dem_Mem_SetPid41DisabledMask(0);
  }
}
#endif

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_ObdCycleStop
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
Dem_OperationCycle_ObdCycleStop(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  if (CycleId == Dem_Cfg_GlobalObdDrivingCycleId())
  {
    Dem_OperationCycle_UpdateObdDcy_End();
  }
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  if (CycleId == Dem_Cfg_GlobalWarmupCycleId())
  {
    Dem_OperationCycle_UpdateObdWarmup_End();
  }
# endif  
}
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_OperationCycle_ObdCycleStart
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
Dem_OperationCycle_ObdCycleStart(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  /* If WarmUpCycle -> raise WUC counter */
  if (Dem_Cfg_CycleIsWarmup(CycleId) == TRUE)
  {
    Dem_OperationCycle_UpdateObdWarmup_Start();
  }

  if (Dem_Cfg_CycleIsObdDcy(CycleId) == TRUE)
  {
    Dem_OperationCycle_UpdateObdDcy_Start();
  }
}
#endif

/* ****************************************************************************
 % Dem_OperationCycle_ObdCycleUpdate
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
Dem_OperationCycle_ObdCycleUpdate(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CycleId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CycleStatus)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  if ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STOPPED) != 0U)
  {
    Dem_OperationCycle_ObdCycleStop(CycleId);
  }
#endif
#if (DEM_FEATURE_NEED_OBD == STD_ON)
  if ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STARTED) != 0U)
  {
    Dem_OperationCycle_ObdCycleStart(CycleId);
  }
#endif
}

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
 * \addtogroup Dem_OperationCycle_Public
 * \{
 */

/* ****************************************************************************
 % Dem_OperationCycle_UpdateCycleStatesInNvBlock
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_UpdateCycleStatesInNvBlock(
  void
  )
{
#if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_ON)
  /* copy back cycle state for NVRAM storage */
  Dem_Cfg_AdminData.CycleState = Dem_OperationCycle_CurrentCycleState;
#endif
}

/* ****************************************************************************
 % Dem_OperationCycle_MainFunction
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
Dem_OperationCycle_MainFunction(
  void
  )
{
#if (DEM_FEATURE_NEED_OBD == STD_ON)
  if (Dem_OperationCycle_IsPendingDcyCycle() == TRUE)
  {
    Dem_OperationCycle_QualifyDcy();

    Dem_OperationCycle_ClearPendingDcyCycle();
  }
#endif

  if (Dem_OperationCycle_CycleFlag != 0U)
  {
    Dem_OperationCycle_ProcessCycles();
  }
}

/* ****************************************************************************
 % Dem_OperationCycle_CycleUpdate
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_OperationCycle_CycleUpdate(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  )
{
  Dem_OperationCycle_SetCycleStatus(CycleId, DEM_OPERATIONCYCLE_CYCLE_STOPPED);

  if ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STOPPED) != 0U)
  {
    Dem_OperationCycle_CycleUpdateEnd(CycleId);
  }

#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
  if ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STARTED) != 0U)
  {
    Dem_OperationCycle_CycleUpdateStart(CycleId);
  }
#endif

  /* Operation Cycle start / end */
  Dem_OperationCycle_CycleUpdateReadiness(CycleId, CycleStatus);

  Dem_OperationCycle_ObdCycleUpdate(CycleId, CycleStatus);

  if ((CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STARTED) != 0U)
  {
    Dem_OperationCycle_SetCycleStatus(CycleId, DEM_OPERATIONCYCLE_CYCLE_STARTED);
  }

}

/* ****************************************************************************
 % Dem_OperationCycle_SetState
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
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_OperationCycle_SetState(
  CONST(uint8, AUTOMATIC)  CycleId,
  CONST(Dem_OperationCycleStateType, AUTOMATIC)  CycleState
  )
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_OK;

#if (DEM_FEATURE_NEED_OBD == STD_ON)
  /* If OBD is enabled, the driving cycle is handled different */
  if (Dem_Cfg_CycleIsObdDcy(CycleId) == TRUE)
  {
    lReturnValue = Dem_OperationCycle_SetStateObdDcy(CycleId, CycleState);
  }
# if (DEM_FEATURE_NEED_IUMPR == STD_ON)
  else if (Dem_Cfg_CycleIsIgnitionHybrid(CycleId) == TRUE)
  { 
    Dem_OperationCycle_ProcessIgnHybridCounter(CycleId, CycleState);
  }
# endif
# if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
  else if (Dem_Cfg_CycleIsWarmup(CycleId) == TRUE)
  {
    Dem_OperationCycle_SetStateWarmUp(CycleState);
  }
# endif
  else
#endif /* (DEM_FEATURE_NEED_OBD == STD_ON) */
  {
    Dem_OperationCycle_SetStateNormalCycle(CycleId, CycleState);
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_OperationCycle_GetCycleState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_OperationCycleStateType, DEM_CODE)
Dem_OperationCycle_GetCycleState(
  CONST(uint8, AUTOMATIC)  CycleId
  )
{
  Dem_OperationCycleStateType lReturnValue;

#if (DEM_FEATURE_NEED_OBD == STD_ON)
  if (Dem_Cfg_CycleIsObdDcy(CycleId) == TRUE)
  {
    if (DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE)
    {
      lReturnValue = DEM_CYCLE_STATE_START;
    }
    else
    {
      lReturnValue = DEM_CYCLE_STATE_END;
    }
  }
  else
#endif
  {
    if (Dem_OperationCycle_GetCurrentCycleStatus(CycleId) == DEM_OPERATIONCYCLE_CYCLE_STARTED)
    {
      lReturnValue = DEM_CYCLE_STATE_START;
    }
    else
    {
      lReturnValue = DEM_CYCLE_STATE_END;
    }
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_OperationCycle_PreInit
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
Dem_OperationCycle_PreInit(
  void
  )
{
  Dem_OperationCycle_CurrentCycleState = 0U;
#if (DEM_CFG_SUPPORT_RESTART_CYCLE == STD_ON)
  Dem_OperationCycle_CurrentCycleState = (uint16)(Dem_OperationCycle_CurrentCycleState | (uint16)(1U << Dem_Cfg_GlobalRestartCycleId()));
#endif
#if (DEM_FEATURE_NEED_OBD == STD_ON)
  Dem_OperationCycle_CurrentCycleState = (uint16)(Dem_OperationCycle_CurrentCycleState | (uint16)(1U << Dem_Cfg_GlobalObdDrivingCycleId()));
#endif

  Dem_OperationCycle_PendingCycleState = 0U;
  Dem_OperationCycle_CycleFlag = 0U;
#if (DEM_FEATURE_NEED_OBD == STD_ON)
  Dem_OperationCycle_ClearPendingDcyCycle();
#endif
}

/* ****************************************************************************
 * Dem_OperationCycle_Init
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_Init(
  void
  )
{
#if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_ON)
  /* If operation cycle states are stored in NV, restore them */
  Dem_OperationCycle_CurrentCycleState = Dem_Cfg_AdminData.CycleState;
#endif
#if (DEM_FEATURE_NEED_OBD == STD_ON)
  /* In OBD configurations, make sure the OBD DCY is in state 'started' */
  Dem_OperationCycle_CurrentCycleState = (uint16)(Dem_OperationCycle_CurrentCycleState | (uint16)(1U << Dem_Cfg_GlobalObdDrivingCycleId()));
#endif
  /* Start the relevant cycles. */
#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_FEATURE_NEED_CYCLEAUTOMATICEND == STD_ON)
  if ((Dem_Cfg_CycleIsAutomaticEnd(Dem_Cfg_GlobalObdDrivingCycleId()) == TRUE)
    && (DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE))
  { /* Driving Cycle was/is confirmed, restart driving cycle */
# if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
    if (DEM_OPERATIONCYCLE_TEST_WARMUP_CYCLE(Dem_OperationCycle_GetObdCycleStates()) == TRUE)
    {
      Dem_OperationCycle_CycleUpdate(Dem_Cfg_GlobalWarmupCycleId(), DEM_OPERATIONCYCLE_CYCLE_RESTARTED);
    }
# endif
    Dem_OperationCycle_CycleUpdate(Dem_Cfg_GlobalObdDrivingCycleId(), DEM_OPERATIONCYCLE_CYCLE_RESTARTED);
  }
#endif /* (DEM_FEATURE_NEED_CYCLEAUTOMATICEND == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) */
#if (DEM_CFG_SUPPORT_RESTART_CYCLE == STD_ON)
# if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_ON)
  if (DEM_OPERATIONCYCLE_CYCLE_STARTED == Dem_OperationCycle_GetCurrentCycleStatus(Dem_Cfg_GlobalRestartCycleId()))
  {
    Dem_OperationCycle_CycleUpdate(Dem_Cfg_GlobalRestartCycleId(), DEM_OPERATIONCYCLE_CYCLE_RESTARTED);
  }
  else
# endif
  {
    Dem_OperationCycle_CycleUpdate(Dem_Cfg_GlobalRestartCycleId(), DEM_OPERATIONCYCLE_CYCLE_STARTED);
  }
#endif
  Dem_Scheduler_EnableTask(Dem_Scheduler_Task_OperationCycle);
}

/* ****************************************************************************
 * Dem_OperationCycle_Shutdown
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
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_OperationCycle_Shutdown(
  void
  )
{
#if (DEM_CFG_SUPPORT_OPCYCLE_STORAGE == STD_OFF) || (DEM_CFG_SUPPORT_OPCYCLE_AUTOMATIC_END == STD_ON)
  uint8 lCycleIndex;

  for (lCycleIndex = 0; lCycleIndex < Dem_Cfg_GlobalCycleCount(); ++lCycleIndex)
  {
# if (DEM_FEATURE_NEED_OBD == STD_ON)
    /* Never stop the OBD_DCY */
    if (Dem_Cfg_CycleIsObdDcy(lCycleIndex) == FALSE)
# endif
    {
      if ( (DEM_OPERATIONCYCLE_CYCLE_STARTED == Dem_OperationCycle_GetCurrentCycleStatus(lCycleIndex))                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_Cfg_CycleIsAutomaticEnd(lCycleIndex) == TRUE)
        )
      {
        Dem_OperationCycle_CycleUpdate(lCycleIndex, DEM_OPERATIONCYCLE_CYCLE_STOPPED);
      }
    }
  }

# if (DEM_CFG_SUPPORT_RESTART_CYCLE == STD_ON)
  Dem_OperationCycle_CurrentCycleState =
    (uint16)(Dem_OperationCycle_CurrentCycleState | (uint16)(1U << Dem_Cfg_GlobalRestartCycleId()));
# endif
#endif

  Dem_OperationCycle_UpdateCycleStatesInNvBlock();

  Dem_OperationCycle_PendingCycleState = 0U;
  Dem_OperationCycle_CycleFlag = 0U;

#if (DEM_FEATURE_NEED_OBD == STD_ON)
  Dem_OperationCycle_ClearPendingDcyCycle();
#endif
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_OPERATIONCYCLE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_OperationCycle_Implementation.h
 *********************************************************************************************************************/
