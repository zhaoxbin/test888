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
/*! \addtogroup Dem_Data
 *  \{
 *  \file       Dem_Data_Implementation.h
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

#if !defined (DEM_DATA_IMPLEMENTATION_H)
#define DEM_DATA_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Data_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_MemState_Implementation.h"
#include "Dem_Mem_Implementation.h"
                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"
#include "Dem_DTCReadoutBuffer_Interface.h"
#include "Dem_UDSStatus_Interface.h"
#include "Dem_Memory_Interface.h" 

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

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_Data_Public
 * \{
 */


#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_Data_PermanentEntryRemove
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Data_PermanentEntryRemove(
  CONST(uint8, AUTOMATIC)  PermanentIndex
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);
  /* Free the given permanent slot */
  Dem_Mem_PermanentSetEvent(PermanentIndex, DEM_EVENT_INVALID);

  Dem_Internal_AssertReturnVoid(Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) > 0, DEM_E_INCONSISTENT_STATE)

  Dem_MemState_MemorySetCurrentSize(lMemoryInfo, Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) - 1);                            /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  Dem_Mem_PermanentSetStatus(PermanentIndex, DEM_ESM_PERMANENT_NONE);
  Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_PERMANENT), 
                              DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_OBDII  == STD_ON) */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_Data_PermanentEntryFind
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Data_PermanentEntryFind(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint8 lPermanentIndex;

  for (lPermanentIndex = 0; lPermanentIndex < Dem_Cfg_GlobalPermanentMaxCount(); ++lPermanentIndex)
  {
    if (Dem_Mem_PermanentGetEvent(lPermanentIndex) == EventId)
    {
      break;
    }
  }
  return lPermanentIndex;
}
#endif


#if (DEM_FEATURE_NEED_OBD_ODOMETER == STD_ON)
/* ****************************************************************************
 % Dem_Data_GetObdOdometer
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
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Data_GetObdOdometer(
  CONSTP2VAR(uint32, AUTOMATIC, DEM_VAR_NOINIT)  Odometer
  )
{
  Std_ReturnType lReturnValue;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (Dem_Cfg_ObdDistanceInformation() >= Dem_Cfg_GlobalDataElementCount())                                                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_DataIsStoredInNV(Dem_Cfg_ObdDistanceInformation()) == FALSE)
    || (Dem_Cfg_DataCallbackType(Dem_Cfg_ObdDistanceInformation()) != DEM_CFG_DATA_FROM_CBK)
    || (Dem_Cfg_DataSize(Dem_Cfg_ObdDistanceInformation()) != 4) )
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    *Odometer = 0;                                                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = E_NOT_OK;
  }
  else
# endif
  {
    uint8 lBuffer[4];

    lReturnValue = ((Dem_ReadDataStandardFPtrType)Dem_Cfg_DataCbkRead(Dem_Cfg_ObdDistanceInformation()))(&lBuffer[0]);           /* PRQA S 0313 */ /* MD_DEM_11.1 */ /* SBSW_DEM_CALL_LOCAL_DESTINATIONBUFFER */
    if (lReturnValue == E_OK)
    {
      *Odometer = Dem_Make32Bit(lBuffer[0], lBuffer[1], lBuffer[2], lBuffer[3]);                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
    {
      *Odometer = 0;                                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }

  return lReturnValue;
}
#endif /* (DEM_FEATURE_NEED_OBD_ODOMETER == STD_ON) */





#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
% Dem_Data_ERecAllDataElementsStored
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Data_ERecAllDataElementsStored(
  CONST(Dem_Cfg_DidIndexType, AUTOMATIC)  DidIndex,
  CONST(Dem_DTCReadoutBuffer_HandleType, AUTOMATIC)  ReadoutBufferId
  )
{
  boolean lReturnValue;

  lReturnValue = TRUE;
# if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
  if (DEM_MEM_TEST_AGING_ONLY(Dem_MemoryEntry_GetState(Dem_DTCReadoutBuffer_GetMemoryEntryId(ReadoutBufferId))) == TRUE)
  {
    Dem_Cfg_DidDataIterType lDataIter;

    for (Dem_Cfg_DidDataIterInit(DidIndex, &lDataIter);                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_DidDataIterExists(&lDataIter) == TRUE;                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_DidDataIterNext(&lDataIter))                                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint8 lCallbackType;
      Dem_Cfg_DataIndexType lDataIndex;
      lDataIndex = Dem_Cfg_DidDataIterGet(&lDataIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */

      lCallbackType = Dem_Cfg_DataCallbackType(lDataIndex);

      if ((lCallbackType == DEM_CFG_DATA_FROM_OCCCTR)
        || (lCallbackType == DEM_CFG_DATA_FROM_OCCCTR_2BYTE)
        || (lCallbackType == DEM_CFG_DATA_FROM_MAX_FDC_SINCE_LAST_CLEAR)
        || (lCallbackType == DEM_CFG_DATA_FROM_FAILED_CYCLES)
        || (lCallbackType == DEM_CFG_DATA_FROM_CONSECUTIVE_FAILED_CYCLES)
        || (lCallbackType == DEM_CFG_DATA_FROM_FAULT_PENDING_COUNTER)
        || (lCallbackType == DEM_CFG_DATA_FROM_CYCLES_TESTED_SINCE_FIRST_FAILED)
        )
      {
        lReturnValue = FALSE;
        break;
      }
    }
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DidIndex)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ReadoutBufferId)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */   
# endif
  return lReturnValue;
}
#endif





#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_Data_PermanentEntryUpdate
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_PermanentEntryUpdate(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  OldDtcStatus,
  CONST(uint8, AUTOMATIC)  NewDtcStatus
  )
{
  uint8 lPermanentIndex;

  /* If the event has a permanent DTC */
  lPermanentIndex = Dem_Data_PermanentEntryFind(EventId);
  if (lPermanentIndex != Dem_Cfg_GlobalPermanentMaxCount())
  {
    boolean lExitPassive;
    uint8 lPermanentStateNew;
    uint8 lPermanentStateOld;

    lExitPassive = FALSE;
    lPermanentStateNew = Dem_Mem_PermanentGetStatus(lPermanentIndex);
    lPermanentStateOld = lPermanentStateNew;

    /* Mark the permanent entry as visible */
    lPermanentStateNew = DEM_ESM_SET_PERMANENT_VISIBLE(lPermanentStateNew);

    switch (DEM_ESM_GET_PERMANENT_STATE(lPermanentStateOld))
    {
    /* In state PERMANENT_ACTIVE: */
    case DEM_ESM_PERMANENT_ACTIVE:
      if (Dem_UDSStatus_Test_WIR(OldDtcStatus) == TRUE)
      {
        if (Dem_UDSStatus_Test_WIR(NewDtcStatus) == FALSE)
        { /* If the MIL became inactive, remove the permanent entry */
          Dem_Data_PermanentEntryRemove(lPermanentIndex);
        }
      }
      break;

    /* In state PERMANENT_PASSIVE: */
    case DEM_ESM_PERMANENT_PASSIVE:
# if (DEM_CFG_SUPPORT_PERMANENT_MANDATORY_PFC == STD_OFF)
      /* Unless MANDATORY_PFC is configured, leave the PASSIVE state if the Event requests the MIL */
      if (Dem_UDSStatus_Test_WIR(NewDtcStatus) == TRUE)
      {
        lExitPassive = TRUE;
      }
      else
# endif
      /* Otherwise, if the event was not tested failed this cycle */
      if (Dem_UDSStatus_Test_TFTOC(OldDtcStatus) == FALSE)
      {
        /* Test if the PCF conditions are met, if so set the PFC condition for the permanent entry */
        if (DEM_OPERATIONCYCLE_TEST_PFC_CYCLE(Dem_OperationCycle_GetObdCycleStates()) == TRUE)
        {
          lPermanentStateNew = DEM_ESM_SET_PERMANENT_CONDITION_PFC(lPermanentStateNew);
        }
        /* Test for a qualified passed test result, if so set the TESTED condition for the permanent entry */
        if (Dem_UDSStatus_Test_TNCTOC(OldDtcStatus) == FALSE)
        {
          lPermanentStateNew = DEM_ESM_SET_PERMANENT_CONDITION_TESTED(lPermanentStateNew);
        }
        /* If all conditions are met for the permanent entry, exit the passive state */
        if ( (DEM_ESM_TEST_PERMANENT_CONDITION_TESTED(lPermanentStateNew) == TRUE)
          && (DEM_ESM_TEST_PERMANENT_CONDITION_PFC(lPermanentStateNew) == TRUE)
# if (DEM_CFG_SUPPORT_PERMANENT_CONDITION_DCY == STD_ON)
          && (DEM_ESM_TEST_PERMANENT_CONDITION_DCY(lPermanentStateNew) == TRUE)
# endif
          )
        {
          lExitPassive = TRUE;
        }
# if (DEM_CFG_SUPPORT_PERMANENT_CONDITION_DCY == STD_ON)
        /* Otherwise, if DCY qualification is configured as permanent clear condition, set the DCY condition
         * for the permanent entry */
        else
        {
          lPermanentStateNew = DEM_ESM_SET_PERMANENT_CONDITION_DCY(lPermanentStateNew);
        }
# endif
      }
      else
      {
        /* If the event was tested failed, reset the PFC and TESTED conditions for the permanent entry */
        lPermanentStateNew = DEM_ESM_RESET_PERMANENT_CONDITION_TESTED(lPermanentStateNew);
        lPermanentStateNew = DEM_ESM_RESET_PERMANENT_CONDITION_PFC(lPermanentStateNew);
# if (DEM_CFG_SUPPORT_PERMANENT_CONDITION_DCY == STD_ON)
        /* If DCY qualification is configured as permanent clear condition, also set the DCY condition for the
         * permanent entry */
        lPermanentStateNew = DEM_ESM_SET_PERMANENT_CONDITION_DCY(lPermanentStateNew);
# endif
      }
      break;

    default:
      break;
    } /* end switch */

    /* On exit of state PASSIVE */
    if (lExitPassive == TRUE)
    {
      if (Dem_UDSStatus_Test_WIR(NewDtcStatus) == FALSE)
      { /* If the event no longer requests the MIL, remove the permanent entry. */
        Dem_Data_PermanentEntryRemove(lPermanentIndex);
      }
      else
      { /* Otherwise, go to ACTIVE state and reset the PFC and TESTED conditions for the permanent entry. */
        lPermanentStateNew = DEM_ESM_SET_PERMANENT_STATE(lPermanentStateNew, DEM_ESM_PERMANENT_ACTIVE);
        lPermanentStateNew = DEM_ESM_RESET_PERMANENT_CONDITION_TESTED(lPermanentStateNew);
        lPermanentStateNew = DEM_ESM_RESET_PERMANENT_CONDITION_PFC(lPermanentStateNew);
      }
    }

    /* If the permanent entry was changed, mark it for immediate NV synchronization */
    if (lPermanentStateNew != lPermanentStateOld)
    {
      Dem_Mem_PermanentSetStatus(lPermanentIndex, lPermanentStateNew);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_PERMANENT), 
                                  DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
    }
  } /* (lPermanentIndex != Dem_Cfg_GlobalPermanentMaxCount()) */
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_Data_PermanentEntryClear
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_PermanentEntryClear(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)   ProcessClearDTC
  )
{
  uint8 lPermanentIndex;

  lPermanentIndex = Dem_Data_PermanentEntryFind(EventId);
  if (lPermanentIndex != Dem_Cfg_GlobalPermanentMaxCount())
  {
    uint8 lPermanentState;
    lPermanentState = Dem_Mem_PermanentGetStatus(lPermanentIndex);

    /* Go to PASSIVE state and reset the conditions to remove the PDTC. Keep its visibility state. */
    lPermanentState = DEM_ESM_SET_PERMANENT_STATE(lPermanentState, DEM_ESM_PERMANENT_PASSIVE);
    lPermanentState = DEM_ESM_RESET_PERMANENT_CONDITION_TESTED(lPermanentState);

    if (Dem_DTC_TestPfcRequired(EventId) == TRUE)
    {
      lPermanentState = DEM_ESM_RESET_PERMANENT_CONDITION_PFC(lPermanentState);
    }
    else
    {
      lPermanentState = DEM_ESM_SET_PERMANENT_CONDITION_PFC(lPermanentState);
    }
# if (DEM_CFG_SUPPORT_PERMANENT_CONDITION_DCY == STD_ON)
    /* If DCY qualification is configured as permanent clear condition */
    if (DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE)
    { /* If the DCY is qualified, RESET the DCY condition for the permanent entry */
      lPermanentState = DEM_ESM_RESET_PERMANENT_CONDITION_DCY(lPermanentState);
    }
    else
    { /* Otherwise, set the DCY condition for the permanent entry */
      lPermanentState = DEM_ESM_SET_PERMANENT_CONDITION_DCY(lPermanentState);
    }
# endif

    /* If the permanent entry was changed, mark it for cleared and immediate NV synchronization */
    if (lPermanentState != Dem_Mem_PermanentGetStatus(lPermanentIndex))
    {
      Dem_Mem_PermanentSetStatus(lPermanentIndex, lPermanentState);
      if (ProcessClearDTC == TRUE)
      {
        Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_PERMANENT),
          DEM_NVM_BLOCKSTATE_DIRTYCLEAREDIMMEDIATE);
      }
      else
      {
        Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_PERMANENT),
          DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
      }
    }
  }
}
#endif /* (DEM_CFG_SUPPORT_OBDII== STD_ON) */

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
 % Dem_Data_Calc_Pid01_MonitorCompleted
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
Dem_Data_Calc_Pid01_MonitorCompleted(
  CONST(uint8, AUTOMATIC)  ReadinessGroup
  )
{
  /* If readiness group is valid */
  if ( (ReadinessGroup != DEM_CFG_READINESS_NONE) 
    && (ReadinessGroup != DEM_CFG_READINESS_FLSYS) && (ReadinessGroup != DEM_CFG_READINESS_CMPRCMPT))
  {
    /* If readiness group is not completed */
    if (Dem_Data_TestReadinessGroupCompleted(ReadinessGroup, Dem_Mem_GetPid01CompletedMask()) == FALSE)
    {
      Dem_EventIdType lEventId;
      boolean lIsCompleted;
      
      lIsCompleted = TRUE;

      for (lEventId = Dem_Cfg_GlobalPrimaryFirst();
           lEventId <= Dem_Cfg_GlobalPrimaryLast();
           lEventId++)
      {
        uint8 lReadinessGroup;
        lReadinessGroup = Dem_Cfg_EventReadinessGroup(lEventId);
        /* If event is assigned to passed group */
        if (lReadinessGroup == ReadinessGroup)
        {
          /* If event is available */
          if (Dem_Event_TestEventUnavailable(lEventId) == FALSE)
          {
            uint8 lDtcStatus;
            Dem_DTC_ExtendedStatusType lExtStatus;
            lDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(lEventId, Dem_DTC_GetDTCStatus(lEventId));
            lExtStatus = Dem_Event_GetExtendedStatus(lEventId);
            if ((Dem_DTCInternalStatus_TestExtendedStatus_TPSLC(lExtStatus) == FALSE)                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
              || (Dem_UDSStatus_Test_PDTC(lDtcStatus) == TRUE))
            {
              /* Leave readiness group not completed */
              lIsCompleted = FALSE;
              break;
            }
          }
        }
      }

      /* Otherwise set readiness group to completed */
      if (lIsCompleted == TRUE)
      {
        Dem_Util_SetReadinessGroupCompleted(TRUE, ReadinessGroup, &Dem_Mem_GetPid01CompletedMask());                             /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
      }
    }
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
/* ****************************************************************************
 % Dem_Data_TestReadinessGroupDisabled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Data_TestReadinessGroupDisabled(
  CONST(uint8, AUTOMATIC)  ReadinessGroup
  )
{
  uint8 lReadinessGroup;
  if (ReadinessGroup == DEM_CFG_READINESS_FLSYS)
  {
    lReadinessGroup = DEM_CFG_READINESS_FLSYS_NONCONT;
  }
  else
  {
    lReadinessGroup = ReadinessGroup;
  }
  return (boolean)(((Dem_Mem_GetPid41DisabledMask() & (1u << (lReadinessGroup))) != 0) ? TRUE : FALSE);
}
#endif

#if (DEM_FEATURE_NEED_PID41_MMONLY_CALCULATION == STD_ON)
/* ****************************************************************************
 % Dem_Data_GetPid41
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
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_GetPid41(
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID41value,
  CONST(uint8, AUTOMATIC) BufferSize
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BufferSize)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (BufferSize < 4)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint32 lReadinessCompletedMask;
    uint32 lPid41;
    Dem_EventIdType lEventId;

    /* Set all groups in CompletedMask to not completed -> (completed = 0, not completed = 1) */
    lReadinessCompletedMask = 0xFFFFFFFFUL;

    /* Get supported and completed state from configuration */
    lPid41 = Dem_Cfg_GlobalPid01SupportedMask();

    /* Iterate over all events assigned to primary memory (OBD related events are assigned to primary memory */
    for (lEventId = Dem_Cfg_GlobalPrimaryFirst(); lEventId <= Dem_Cfg_GlobalPrimaryLast(); lEventId++)
    {
      uint8 lReadinessGroup = Dem_Cfg_EventReadinessGroup(lEventId);

      /* If a readiness group is assigned to event */
      if ((lReadinessGroup != DEM_CFG_READINESS_NONE)                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        /* If event is available */
        && (Dem_Event_TestEventUnavailable(lEventId) == FALSE)
        )
      {
        /* If Comprehensive Complete is supported and readiness group is DEM_CFG_READINESS_CMPRCMPT */
# if (DEM_CFG_PROCESS_PID41_COMPREHENSIVE_COMPLETE == STD_ON)
        if (lReadinessGroup == DEM_CFG_READINESS_CMPRCMPT)
        {
          if (Dem_Data_TestReadinessGroupDisabled(lReadinessGroup) == TRUE)
          {
            /* Set readiness group to not supported */
            Dem_Util_SetReadinessGroupSupported(FALSE, lReadinessGroup, &lPid41);                                                /* SBSW_DEM_POINTER_FORWARD_STACK */
          }
          else
          {
            /* Readiness group is set to supported (it will be set also to completed in last step) */
            Dem_Util_SetReadinessGroupSupported(TRUE, lReadinessGroup, &lPid41);                                                 /* SBSW_DEM_POINTER_FORWARD_STACK */
          }

          /* continue with next event */
          continue;                                                                                                              /* PRQA S 0770 */ /* MD_DEM_14.5 */
        }
# endif
        /* If readiness group is disabled */
        if (Dem_Data_TestReadinessGroupDisabled(lReadinessGroup) == TRUE)
        {
          /* Set readiness group to n/a (= completed)*/
          Dem_Util_SetReadinessGroupCompleted(TRUE, lReadinessGroup, &lPid41);                                                   /* SBSW_DEM_POINTER_FORWARD_STACK */

          /* Set readiness group to not supported */
          Dem_Util_SetReadinessGroupSupported(FALSE, lReadinessGroup, &lPid41);                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */
        }
        else
        {
          /* If readiness group in CompletedMask is not completed */
          if (Dem_Data_TestReadinessGroupCompleted(lReadinessGroup, lReadinessCompletedMask) == FALSE)
          {
            uint8 lDtcStatus;
            lDtcStatus = Dem_DTC_GetDTCStatus(lEventId);

            /* If event is failed this operation cycle */
            if (Dem_UDSStatus_Test_TFTOC(lDtcStatus) == TRUE)
            {
              /* Set readiness group to completed  */
              Dem_Util_SetReadinessGroupCompleted(TRUE, lReadinessGroup, &lReadinessCompletedMask);                              /* SBSW_DEM_POINTER_FORWARD_STACK */
            }
            /* Otherwise if event is not tested this cycle */
            else if (Dem_UDSStatus_Test_TNCTOC(lDtcStatus) == TRUE)
            {
              /* Set readiness group to not completed  */
              Dem_Util_SetReadinessGroupCompleted(FALSE, lReadinessGroup, &lPid41);                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
            }
            else
            {
              /* do nothing */
            }
          }

          /* If Event Availability is supported */
# if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
          /* Set readiness group to supported*/
          Dem_Util_SetReadinessGroupSupported(TRUE, lReadinessGroup, &lPid41);                                                   /* SBSW_DEM_POINTER_FORWARD_STACK */
# endif
        }
      }
    }

    /* If readiness group in CompletedMask is completed set readiness group to completed -> (completed = 0, not completed = 1) */
    lPid41 &= lReadinessCompletedMask;

    /* Set reserved completed bits to 0 */
    if ((lPid41 & DEM_READINESS_SUPPORT_COMPRESSION) != 0)
    {
      lPid41 &= DEM_READINESS_INITIALIZE_PID01COMPLETED_COMPRESSION;
    }
    else
    {
      lPid41 &= DEM_READINESS_INITIALIZE_PID01COMPLETED_SPARK;
    }

    /* If Comprehensive Complete is supported set readiness group DEM_CFG_READINESS_CMPRCMPT to complete */
# if (DEM_CFG_PROCESS_PID41_COMPREHENSIVE_COMPLETE == STD_ON)
    Dem_Util_SetReadinessGroupCompleted(TRUE, DEM_CFG_READINESS_CMPRCMPT, &lPid41);                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
# endif

    PID41value[1] = Dem_GetHiLoByte(lPid41);                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
    PID41value[2] = Dem_GetLoHiByte(lPid41);                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
    PID41value[3] = Dem_GetLoLoByte(lPid41);                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
  }
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID41 == STD_ON) && (DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_OFF)
/* ****************************************************************************
 % Dem_Data_GetPid41ComprehensiveOnly
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
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_GetPid41ComprehensiveOnly(
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID41value,
  CONST(uint8, AUTOMATIC) BufferSize
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BufferSize)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (BufferSize < 4)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
# if (DEM_CFG_PROCESS_PID41_COMPREHENSIVE_COMPLETE == STD_OFF)
    Dem_EventIdType lEventId;

    boolean lSupported;
    boolean lCompleted;

    lSupported = (boolean)((Dem_Cfg_GlobalPid01SupportedMask() & DEM_READINESS_SUPPORT_CMPRCMPT) != 0);
    /* If readiness group is disabled */
    if (Dem_Data_TestReadinessGroupDisabled(DEM_CFG_READINESS_CMPRCMPT) == TRUE)
    {
      /* Set readiness group to complete ( = not applicable) */
      lCompleted = TRUE;

      /* Set readiness group to not supported */
      lSupported = FALSE;
    }
    /* Otherwise */
    else
    {
      lCompleted = TRUE;
#  if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
      /* Set readiness group DEM_CFG_READINESS_CMPRCMPT to not supported -> will be calculated later*/
      lSupported = FALSE;
#  else
      /* Otherwise use state for DEM_CFG_READINESS_CMPRCMPT from configuration, all others are not supported and complete */
      if (lSupported == TRUE)
#  endif
        /* If Event Availability is supported or readiness group DEM_CFG_READINESS_CMPRCMPT is supported */
      {
        /* Iterate over all events assigned to primary memory (OBD related events are assigned to primary memory */
        for (lEventId = Dem_Cfg_GlobalPrimaryFirst(); lEventId <= Dem_Cfg_GlobalPrimaryLast(); lEventId++)
        {
          /* If event readiness group is DEM_CFG_READINESS_CMPRCMPT and event is available */
          if ((Dem_Cfg_EventReadinessGroup(lEventId) == DEM_CFG_READINESS_CMPRCMPT)                                                /* PRQA S 3415 */ /* MD_DEM_12.4_cs */
            && (Dem_Event_TestEventUnavailable(lEventId) == FALSE)
            )
          {
            uint8 lDtcStatus;
            lDtcStatus = Dem_DTC_GetDTCStatus(lEventId);

            /* If Event Availability is supported */
#  if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
            /* Set readiness group to supported*/
            lSupported = TRUE;
#  endif /* If Event Availability is not supported supported state is in configuration */

            /* If event is failed this operation cycle */
            if (Dem_UDSStatus_Test_TFTOC(lDtcStatus) == TRUE)
            {
              lCompleted = TRUE;
              /* Stop iterating over all events  */
              break;
            }
            /* Otherwise if event is not tested this cycle */
            else if (Dem_UDSStatus_Test_TNCTOC(lDtcStatus) == TRUE)
            {
              /* Set readiness group to not completed */
              lCompleted = FALSE;
            }
            else
            {
              /* do nothing */
            }
          }
        }
      }

    }

    /* Return Pid41 value */
    PID41value[1] = 0x00;                                                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
    PID41value[2] = 0x00;                                                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
    PID41value[3] = 0x00;                                                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
    if (lSupported == TRUE)
    {
      PID41value[1] |= 0x04;                                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
    }
    /* Only supported monitors can be set not completed */
    if (lCompleted == FALSE)
    {
      PID41value[1] |= 0x40;                                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
    }
# else
    PID41value[1] = 0x04;                                                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
    PID41value[2] = 0x00; /* not supported */                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
    PID41value[3] = 0x00; /* not supported */                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT_BUFFER */
# endif
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if ( (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) || (DEM_FEATURE_NEED_PID41_MMONLY_CALCULATION == STD_ON) )
/* ****************************************************************************
 % Dem_Data_TestReadinessGroupCompleted
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Data_TestReadinessGroupCompleted(
  CONST(uint8, AUTOMATIC)  ReadinessGroup,
  CONST(uint32, AUTOMATIC)  Pid01CompletedMask
  )
{
  boolean lReturnValue;

  switch (ReadinessGroup)
  {
  case DEM_CFG_READINESS_MISF:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_MISF_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_FLSYS:
  case DEM_CFG_READINESS_FLSYS_NONCONT:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_FLSYS_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_CMPRCMPT:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_CMPRCMPT) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_CAT:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_CAT_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_HCCAT:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_HCCAT_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_HTCAT:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_HTCAT_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_NOXCAT:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_NOXCAT_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_EVAP:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_EVAP_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_SECAIR:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_SECAIR_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_BOOSTPR:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_BOOSTPR_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_O2SENS:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_O2SENS_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_EGSENS:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_EGSENS_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_O2SENSHT:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_O2SENSHT_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_PMFLT:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_PMFLT_MASK) == 0) ? TRUE : FALSE);
    break;
  case DEM_CFG_READINESS_EGR:
    lReturnValue = (boolean)(((Pid01CompletedMask & DEM_READINESS_COMPLETE_EGR_MASK) == 0) ? TRUE : FALSE);
    break;
  default:
    /* case DEM_CFG_READINESS_NONE: */
    lReturnValue = FALSE;
    break;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif


                                                         /* Permanent Memory */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_Data_PermanentEntryAdd
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
Dem_Data_PermanentEntryAdd(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_EventIdType lMasterEventId;
  uint8   lPermanentIndex;
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);
  lMasterEventId = Dem_Cfg_GetMasterEvent(EventId);

  /* scan through the permanent memory if the given event is available */
  lPermanentIndex = Dem_Data_PermanentEntryFind(lMasterEventId);

  if (Dem_MemState_MemoryGetMaxSize(lMemoryInfo) == lPermanentIndex)                                                             /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  { /* Event not stored, try to find an empty slot */
    lPermanentIndex = Dem_Data_PermanentEntryFind(DEM_EVENT_INVALID);

    if (lPermanentIndex != Dem_MemState_MemoryGetMaxSize(lMemoryInfo))                                                           /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
    {
      uint8 lPermanentState;

      lPermanentState = DEM_ESM_PERMANENT_NONE;
      lPermanentState = DEM_ESM_SET_PERMANENT_STATE(lPermanentState, DEM_ESM_PERMANENT_ACTIVE);

      if (0 == Dem_Cfg_EventTripTarget(EventId))
      { /* 0-trip DTCs shall be visible immediately */
        lPermanentState = DEM_ESM_SET_PERMANENT_VISIBLE(lPermanentState);
      }

      Dem_Mem_PermanentSetEvent(lPermanentIndex, lMasterEventId);
      Dem_Mem_PermanentSetStatus(lPermanentIndex, lPermanentState);

      Dem_MemState_MemorySetCurrentSize(lMemoryInfo, Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) + 1 );                       /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */

      /* persist status change in NVM */
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_PERMANENT), 
                                  DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
    }
# if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
    else
    { /* Entry was not available and no free slot detected --> set overflow indication */
      Dem_MemState_SetOverflow(DEM_CFG_MEMORYID_PERMANENT);
    }
# endif
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_OBDII== STD_ON) */

/* ****************************************************************************
 % Dem_Data_InitDestinationBuffer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_InitDestinationBuffer(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_LIB */
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_SharedDataPtrType, AUTOMATIC) Buffer,
  CONST(uint16, AUTOMATIC) Size
  )
{
  DestinationBuffer->Buffer = Buffer;                                                                                            /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  DestinationBuffer->BufferSize = Size;                                                                                          /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
  DestinationBuffer->WriteIndex = 0;                                                                                             /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */
}

/* ****************************************************************************
 % Dem_Data_ResetWriteIndexDestinationBuffer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_ResetWriteIndexDestinationBuffer(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_LIB */
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer
  )
{
  DestinationBuffer->WriteIndex = 0;                                                                                             /* SBSW_DEM_DESTINATIONBUFFER_WRITEINDEX */
}

/* ****************************************************************************
% Dem_Data_IncrementWriteIndexDestinationBuffer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Data_IncrementWriteIndexDestinationBuffer(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_LIB */
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC) Size
  )
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_OK;

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((((uint32)DestinationBuffer->WriteIndex) + Size) > DestinationBuffer->BufferSize)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = E_NOT_OK;
  }
  else
# endif
  {
    DestinationBuffer->WriteIndex += Size;                                                                                       /* SBSW_DEM_DESTINATIONBUFFER_WRITEINDEX */
  }

  return lReturnValue;
}

/* ****************************************************************************
% Dem_Data_WriteDestinationBuffer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBuffer(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_LIB */
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(Dem_ConstSharedDataPtrType, AUTOMATIC) SourceBuffer,
  CONST(uint16, AUTOMATIC) Size
  )
{
  Std_ReturnType lReturnValue;
  uint16 lWriteIndex;
  lWriteIndex = DestinationBuffer->WriteIndex;
  lReturnValue = Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, Size);                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  if (lReturnValue == E_OK)
  {
    Dem_MemCpy(&DestinationBuffer->Buffer[lWriteIndex], SourceBuffer, Size);                                                     /* PRQA S 0311, 0602 */ /* MD_DEM_11.5, MD_DEM_20.2 */ /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
  }
}

/* ****************************************************************************
% Dem_Data_WriteDestinationBufferAtIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferAtIndex(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_LIB */
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC) WriteIndex,
  CONST(uint8, AUTOMATIC) Data
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (WriteIndex >= DestinationBuffer->BufferSize)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    DestinationBuffer->Buffer[WriteIndex] = Data;                                                                                /* SBSW_DEM_WRITE_DESTINATIONBUFFER_AT_INDEX */
  }
}

/* ****************************************************************************
% Dem_Data_WriteDestinationBufferUint8
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferUint8(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_LIB */
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint8, AUTOMATIC) Data
  )
{
  Std_ReturnType lReturnValue;
  uint16 lWriteIndex;
  lWriteIndex = DestinationBuffer->WriteIndex;
  lReturnValue = Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 1);                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  if (lReturnValue == E_OK)
  {
    DestinationBuffer->Buffer[lWriteIndex] = Data;                                                                               /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
  }
}

/* ****************************************************************************
% Dem_Data_WriteDestinationBufferUint16
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferUint16(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_LIB */
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC) Data
  )
{
  Std_ReturnType lReturnValue;
  uint16 lWriteIndex;
  lWriteIndex = DestinationBuffer->WriteIndex;
  lReturnValue = Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 2);                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  if (lReturnValue == E_OK)
  {
    DestinationBuffer->Buffer[lWriteIndex] = Dem_GetHiByte(Data);                                                                /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
    DestinationBuffer->Buffer[lWriteIndex + 1] = Dem_GetLoByte(Data);                                                            /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
  }
}

/* ****************************************************************************
% Dem_Data_WriteDestinationBufferUint16_Intel
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferUint16_Intel(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_LIB */
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint16, AUTOMATIC) Data
  )
{
  Std_ReturnType lReturnValue;
  uint16 lWriteIndex;
  lWriteIndex = DestinationBuffer->WriteIndex;
  lReturnValue = Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 2);                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  if (lReturnValue == E_OK)
  {
    DestinationBuffer->Buffer[lWriteIndex] = Dem_GetLoByte(Data);                                                                /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
    DestinationBuffer->Buffer[lWriteIndex + 1] = Dem_GetHiByte(Data);                                                            /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
  }
}

/* ****************************************************************************
% Dem_Data_WriteDestinationBufferUint32
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferUint32(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_LIB */
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint32, AUTOMATIC) Data
  )
{
  Std_ReturnType lReturnValue;
  uint16 lWriteIndex;
  lWriteIndex = DestinationBuffer->WriteIndex;
  lReturnValue = Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 4);                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  
  if (lReturnValue == E_OK)
  {
    DestinationBuffer->Buffer[lWriteIndex] = Dem_GetHiHiByte(Data);                                                              /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
    DestinationBuffer->Buffer[lWriteIndex + 1] = Dem_GetHiLoByte(Data);                                                          /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
    DestinationBuffer->Buffer[lWriteIndex + 2] = Dem_GetLoHiByte(Data);                                                          /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
    DestinationBuffer->Buffer[lWriteIndex + 3] = Dem_GetLoLoByte(Data);                                                          /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
  }
}

/* ****************************************************************************
% Dem_Data_WriteDestinationBufferUint32_Intel
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Data_WriteDestinationBufferUint32_Intel(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_LIB */
  CONST(Dem_Data_DestinationBufferPtrType, AUTOMATIC)  DestinationBuffer,
  CONST(uint32, AUTOMATIC) Data
  )
{
  Std_ReturnType lReturnValue;
  uint16 lWriteIndex;
  lWriteIndex = DestinationBuffer->WriteIndex;
  lReturnValue = Dem_Data_IncrementWriteIndexDestinationBuffer(DestinationBuffer, 4);                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  
  if (lReturnValue == E_OK)
  {
    DestinationBuffer->Buffer[lWriteIndex] = Dem_GetLoLoByte(Data);                                                              /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
    DestinationBuffer->Buffer[lWriteIndex + 1] = Dem_GetLoHiByte(Data);                                                          /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
    DestinationBuffer->Buffer[lWriteIndex + 2] = Dem_GetHiLoByte(Data);                                                          /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
    DestinationBuffer->Buffer[lWriteIndex + 3] = Dem_GetHiHiByte(Data);                                                          /* SBSW_DEM_WRITE_DESTINATIONBUFFER */
  }
}
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DATA_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Data_Implementation.h
 *********************************************************************************************************************/
