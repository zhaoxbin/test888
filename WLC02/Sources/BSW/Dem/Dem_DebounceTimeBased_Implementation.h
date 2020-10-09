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
/*! \addtogroup Dem_DebounceTimeBased
 *  \{
 *  \file       Dem_DebounceTimeBased_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of DebounceTimeBased subcomponent
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

#if !defined (DEM_DEBOUNCETIMEBASED_IMPLEMENTATION_H)
#define DEM_DEBOUNCETIMEBASED_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceTimeBased_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceBase_Implementation.h"
#include "Dem_DebouncingState_Implementation.h"
#include "Dem_EnableCondition_Implementation.h"
#include "Dem_StorageCondition_Implementation.h"
#include "Dem_EventInternalStatus_Implementation.h"
#include "Dem_SatelliteData_Implementation.h"
#include "Dem_DTC_Implementation.h"
#include "Dem_DTCInternalStatus_Implementation.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*!
 * \defgroup  Dem_Debounce_StatusType  Macros encoding debounce status states
 * Macros encoding debounce status states
 * \{
 */
#define DEM_DEBOUNCE_TIMEBASED_NONE                    ((0x00U) << DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS) /*!< debouncing inactive */
#define DEM_DEBOUNCE_TIMEBASED_RESET_FAILED            ((0x01U) << DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS) /*!< debouncing started, counter initialized towards failed threshold */
#define DEM_DEBOUNCE_TIMEBASED_RESET_PASSED            ((0x02U) << DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS) /*!< debouncing started, counter initialized towards passed threshold */
#define DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED            ((0x03U) << DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS) /*!< debouncing in progress, counting towards failed threshold */
#define DEM_DEBOUNCE_TIMEBASED_COUNT_PASSED            ((0x04U) << DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS) /*!< debouncing in progress, counting towards passed threshold */
#define DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED           ((0x05U) << DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS) /*!< debouncing paused while counting towards failed threshold */
#define DEM_DEBOUNCE_TIMEBASED_FROZEN_PASSED           ((0x06U) << DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS) /*!< debouncing paused while counting towards passed threshold */
#define DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED_FDC        ((0x07U) << DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS) /*!< debouncing in progress, counting towards failed threshold, fdc trip already processed */
#define DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED_FDC       ((0x09U) << DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS) /*!< debouncing paused while counting towards failed threshold, fdc trip already processed */
#define DEM_DEBOUNCE_TIMEBASED_DONE_PASSED             ((0x0aU) << DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS) /*!< debouncing completed, passed threshold reached */
#define DEM_DEBOUNCE_TIMEBASED_DONE_FAILED             ((0x0bU) << DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS) /*!< debouncing completed, failed threshold reached */
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
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

DEM_LOCAL CONST(Dem_DebounceFunctionTableType, DEM_CONST) Dem_DebounceTimeBased_FunctionTable =                                  /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  Dem_DebounceTimeBased_Calculate,
  Dem_DebounceTimeBased_Freeze,
  Dem_DebounceTimeBased_Reset,
  Dem_DebounceTimeBased_GetDebouncingState,
  Dem_DebounceTimeBasedSat_UpdateDebounceValueMax,
  Dem_DebounceTimeBasedSat_ResetDebounceValueMax,
  Dem_DebounceTimeBased_GetFaultDetectionCounter,
  Dem_DebounceTimeBased_GetMaxFaultDetectionCounter,
  Dem_DebounceTimeBased_GetDebouncingResult,
  Dem_DebounceTimeBased_RestoreDebounceValue
};

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_DebounceTimeBased_Private
 * \{
 */

/* ****************************************************************************
 % Dem_DebounceTimeBased_CheckDebounceInfoPtr
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceTimeBased_CheckDebounceInfoPtr(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  boolean lDebounceInfoPtrValid;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DebounceInfoPtr->FunctionTable != &Dem_DebounceTimeBased_FunctionTable)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lDebounceInfoPtrValid = FALSE;
  }
  else
#endif
  { 
    lDebounceInfoPtrValid = TRUE;
  }

  return lDebounceInfoPtrValid;
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_Base2TimeBased
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceTimeBased_InfoPtrType, DEM_CODE)
Dem_DebounceTimeBased_Base2TimeBased(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return (Dem_DebounceTimeBased_InfoPtrType)DebounceInfoPtr;                                                                     /* PRQA S 0310 */ /* MD_DEM_11.4_inh */
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_ConstBase2TimeBased
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceTimeBased_ConstInfoPtrType, DEM_CODE)
Dem_DebounceTimeBased_ConstBase2TimeBased(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return (Dem_DebounceTimeBased_ConstInfoPtrType)DebounceInfoPtr;                                                                /* PRQA S 0310 */ /* MD_DEM_11.4_inh */
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_EventFailedTime
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DebounceTimeBased_EventFailedTime(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint16 lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
  lReturnValue = (uint16)(Dem_Cfg_GetFailTimerCyclesOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
  lReturnValue = 1;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_EventPassedTime
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DebounceTimeBased_EventPassedTime(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint16 lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
  lReturnValue = (uint16)(Dem_Cfg_GetPassTimerCyclesOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
#else
  lReturnValue = 1;                                                                                                    
#endif

  return lReturnValue;
}

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 % Dem_DebounceTimeBased_EventStorageTime
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DebounceTimeBased_EventStorageTime(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint16 lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_CFG_STORAGETIMERCYCLESOFDEBOUNCETABLE == STD_ON)
  lReturnValue = (uint16)(Dem_Cfg_GetStorageTimerCyclesOfDebounceTable(Dem_Cfg_GetDebounceTableIdxOfEventTable(EventId)));
# else
  lReturnValue = 0;
# endif

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_DebounceTimeBased_GetOldTimerState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Debounce_StatusType, DEM_CODE)
Dem_DebounceTimeBased_GetOldTimerState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  Dem_Debounce_StatusType lOldTimerState;
        
  Dem_Internal_AssertContinue(DebounceInfoPtr->FunctionTable == &Dem_DebounceTimeBased_FunctionTable, DEM_E_INCONSISTENT_STATE)
  lOldTimerState = Dem_DebounceTimeBased_ConstBase2TimeBased(DebounceInfoPtr)->OldTimerState;                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */      

  return lOldTimerState;
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_GetNewTimerState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Debounce_StatusType, DEM_CODE)
Dem_DebounceTimeBased_GetNewTimerState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  Dem_Debounce_StatusType lNewTimerState;

  Dem_Internal_AssertContinue(DebounceInfoPtr->FunctionTable == &Dem_DebounceTimeBased_FunctionTable, DEM_E_INCONSISTENT_STATE)
  lNewTimerState = Dem_DebounceTimeBased_ConstBase2TimeBased(DebounceInfoPtr)->NewTimerState;                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  return lNewTimerState;
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_SetNewTimerState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_SetNewTimerState(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_Debounce_StatusType, AUTOMATIC)  DebounceState
  )
{
  if (Dem_DebounceTimeBased_CheckDebounceInfoPtr((Dem_DebounceBase_ConstInfoPtrType)DebounceInfoPtr) == TRUE)                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    Dem_DebounceTimeBased_InfoPtrType lDebounceTimeBasedInfoPtr;
    lDebounceTimeBasedInfoPtr = Dem_DebounceTimeBased_Base2TimeBased(DebounceInfoPtr);                                           /* SBSW_DEM_CALL_DEBOUNCETIMEBASED_INFOPTR_INIT */
    lDebounceTimeBasedInfoPtr->NewTimerState = DebounceState;                                                                    /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_WRITE_STACK */
  }
  else
  {
    /* MISRA */
  }
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_GetOldTimerValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DebounceTimeBased_GetOldTimerValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  uint16 lOldTimerValue;

  Dem_Internal_AssertContinue(DebounceInfoPtr->FunctionTable == &Dem_DebounceTimeBased_FunctionTable, DEM_E_INCONSISTENT_STATE)
  lOldTimerValue = Dem_DebounceTimeBased_ConstBase2TimeBased(DebounceInfoPtr)->OldTimerValue;                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return lOldTimerValue;
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_GetNewTimerValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DebounceTimeBased_GetNewTimerValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  uint16 lNewTimerValue;

  Dem_Internal_AssertContinue(DebounceInfoPtr->FunctionTable == &Dem_DebounceTimeBased_FunctionTable, DEM_E_INCONSISTENT_STATE)
  lNewTimerValue = Dem_DebounceTimeBased_ConstBase2TimeBased(DebounceInfoPtr)->NewTimerValue;                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */                                    
  return lNewTimerValue;
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_SetNewTimerValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_SetNewTimerValue(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(uint16, AUTOMATIC)  DebounceTimer
  )
{
  if (Dem_DebounceTimeBased_CheckDebounceInfoPtr((Dem_DebounceBase_ConstInfoPtrType)DebounceInfoPtr) == TRUE)                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    Dem_DebounceTimeBased_InfoPtrType lDebounceTimeBasedInfoPtr;
    lDebounceTimeBasedInfoPtr = Dem_DebounceTimeBased_Base2TimeBased(DebounceInfoPtr);                                           /* SBSW_DEM_CALL_DEBOUNCETIMEBASED_INFOPTR_INIT */
    lDebounceTimeBasedInfoPtr->NewTimerValue = DebounceTimer;                                                                    /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_WRITE_STACK */
  }
  else
  {
    /* MISRA */
  }
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_CalculateFaultDetectionCounter
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
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_DebounceTimeBased_CalculateFaultDetectionCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC)  DebounceValue,
  CONST(Dem_Debounce_StatusType, AUTOMATIC)  DebounceStatus
  )
{
  sint8 lReturnedFdc;

  switch (DebounceStatus)
  {
  case DEM_DEBOUNCE_TIMEBASED_NONE:
    lReturnedFdc = 0;
    break;
  case DEM_DEBOUNCE_TIMEBASED_DONE_FAILED:
    lReturnedFdc = 127;
    break;
  case DEM_DEBOUNCE_TIMEBASED_DONE_PASSED:
    lReturnedFdc = -128;
    break;
  case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED:
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED:
  case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED_FDC:
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED_FDC:
    {
      uint16 lQualifyTarget;
      lQualifyTarget = Dem_DebounceTimeBased_EventFailedTime(EventId);
      lReturnedFdc = (sint8)(((uint32)(lQualifyTarget - DebounceValue) * 127) / lQualifyTarget);

      /* Already counting, assert an FDC of at least 1 */
      if (lReturnedFdc == 0)
      {
        lReturnedFdc = 1;
      }
    }
    break;
  case DEM_DEBOUNCE_TIMEBASED_RESET_FAILED:
    lReturnedFdc = 1;
    break;

  case DEM_DEBOUNCE_TIMEBASED_COUNT_PASSED:
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_PASSED:
    {
      uint16 lQualifyTarget;
      lQualifyTarget = Dem_DebounceTimeBased_EventPassedTime(EventId);
      lReturnedFdc = (sint8)(((sint32)(lQualifyTarget - DebounceValue) * -128) / lQualifyTarget);

      /* Already counting, assert an FDC of at most -1 */
      if (lReturnedFdc == 0)
      {
        lReturnedFdc = -1;
      }
    }
    break;
  case DEM_DEBOUNCE_TIMEBASED_RESET_PASSED:
    lReturnedFdc = -1;
    break;

  default:
    lReturnedFdc = 0;
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
    break;
  }

  return lReturnedFdc;
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_CalculatePrepassed
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
Dem_DebounceTimeBased_CalculatePrepassed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  )
{
  switch (DebounceInfoData->OldTimerState)
  {
  case DEM_DEBOUNCE_TIMEBASED_NONE:
  case DEM_DEBOUNCE_TIMEBASED_RESET_FAILED:
  case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED:
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED:
  case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED_FDC:
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED_FDC:
  case DEM_DEBOUNCE_TIMEBASED_DONE_FAILED:
    DebounceInfoData->NewTimerState = DEM_DEBOUNCE_TIMEBASED_RESET_PASSED;                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    break;
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_PASSED:
    DebounceInfoData->NewTimerState = DEM_DEBOUNCE_TIMEBASED_COUNT_PASSED;                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    break;
  case DEM_DEBOUNCE_TIMEBASED_DONE_PASSED:
    if (Dem_Cfg_EventDebounceContinuous(DebounceInfoData->Base.EventId) == TRUE)
    {
      /*Rare case with continuous debouncing in which a qualified passed result should
      has been reached before but not been processed since enable conditions were disabled.
      Allow for proccessing the passed result qualification with next 'Prepassed'*/
      if (Dem_EnableCondition_TestEventEnableConditionsFulfilled(DebounceInfoData->Base.EventId) == TRUE)
      {
        Dem_DebounceBase_SetMonitorTrigger(&(DebounceInfoData->Base), DEM_EVENT_STATUS_PASSED);                                  /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
      }
    }
    break;
  case DEM_DEBOUNCE_TIMEBASED_RESET_PASSED:
  case DEM_DEBOUNCE_TIMEBASED_COUNT_PASSED:
    /* Nothing to do */
    break;
  default:
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
    break;
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */                                                                             

/* ****************************************************************************
 % Dem_DebounceTimeBased_CalculatePrefailed
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_CalculatePrefailed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  )
{
  switch (DebounceInfoData->OldTimerState)
  {
  case DEM_DEBOUNCE_TIMEBASED_NONE:
  case DEM_DEBOUNCE_TIMEBASED_RESET_PASSED:
  case DEM_DEBOUNCE_TIMEBASED_COUNT_PASSED:
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_PASSED:
  case DEM_DEBOUNCE_TIMEBASED_DONE_PASSED:
    DebounceInfoData->NewTimerState = DEM_DEBOUNCE_TIMEBASED_RESET_FAILED;                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    break;
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED:
    DebounceInfoData->NewTimerState = DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED;                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    break;
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED_FDC:
    DebounceInfoData->NewTimerState = DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED_FDC;                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    break;
  case DEM_DEBOUNCE_TIMEBASED_DONE_FAILED:
    if (Dem_Cfg_EventDebounceContinuous(DebounceInfoData->Base.EventId) == TRUE)
    {
      /*Rare case with continuous debouncing in which a qualified failed result should
        has been reached but not been processed since enable conditions were disabled.
        Allow for proccessing the failed result qualification with next 'Prefailed'*/
      if (Dem_EnableCondition_TestEventEnableConditionsFulfilled(DebounceInfoData->Base.EventId) == TRUE)
      {
        Dem_DebounceBase_SetMonitorTrigger(&(DebounceInfoData->Base), DEM_EVENT_STATUS_FAILED);                                  /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
      }
    }
    break;
  case DEM_DEBOUNCE_TIMEBASED_RESET_FAILED:
  case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED:
  case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED_FDC:
    /* No change */
    break;
  default:
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
    break;
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_DebounceTimeBased_CalculatePassed
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
Dem_DebounceTimeBased_CalculatePassed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  )
{
  boolean lEnableConditionsSatisfied;
  Dem_EventIdType lEventId;

  lEventId = Dem_DebounceBase_GetEventId(&(DebounceInfoData->Base));                                                             /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
  lEnableConditionsSatisfied = Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId);

  DebounceInfoData->NewTimerState = DEM_DEBOUNCE_TIMEBASED_DONE_PASSED;                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DebounceInfoData->NewTimerValue = 0;                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  if (lEnableConditionsSatisfied == FALSE)
  {
    Dem_DebounceBase_SetMonitorTrigger(&(DebounceInfoData->Base), DEM_EVENT_STATUS_PREPASSED);                                   /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
  }
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_CalculateFailed
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
Dem_DebounceTimeBased_CalculateFailed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  )
{
  boolean lEnableConditionsSatisfied;
  Dem_EventIdType lEventId;

  lEventId = Dem_DebounceBase_GetEventId(&(DebounceInfoData->Base));                                                             /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
  lEnableConditionsSatisfied = Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId);

  DebounceInfoData->NewTimerState = DEM_DEBOUNCE_TIMEBASED_DONE_FAILED;                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DebounceInfoData->NewTimerValue = 0;                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  if (lEnableConditionsSatisfied == FALSE)
  {
    Dem_DebounceBase_SetMonitorTrigger(&(DebounceInfoData->Base), DEM_EVENT_STATUS_PREFAILED);                                   /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
  }
  else
  {
    if (DebounceInfoData->OldTimerState != DEM_DEBOUNCE_TIMEBASED_DONE_FAILED)
    {
      Dem_DebounceBase_SetMaximumFdcExceeded(&(DebounceInfoData->Base));                                                         /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
      Dem_DebounceBase_SetRequestFdcProcessing(&(DebounceInfoData->Base));                                                       /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
    }
    if ( (DebounceInfoData->OldTimerState != DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED_FDC)
      && (DebounceInfoData->OldTimerState != DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED_FDC)
      && (DebounceInfoData->OldTimerState != DEM_DEBOUNCE_TIMEBASED_DONE_FAILED) )
    {
      Dem_DebounceBase_SetFdcThresholdExceeded(&(DebounceInfoData->Base));                                                       /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
      Dem_DebounceBase_SetRequestFdcProcessing(&(DebounceInfoData->Base));                                                       /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
    }
  }
}

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 % Dem_DebounceTimeBased_CountingTowardsPassed
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_CountingTowardsPassed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  )
{
  Dem_EventIdType lEventId;
  boolean lEnableConditionsSatisfied;

  lEventId = Dem_DebounceBase_GetEventId(&(DebounceInfoData->Base));                                                             /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
  lEnableConditionsSatisfied = Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId);

  /* process event timer */
  DebounceInfoData->NewTimerValue = (uint16)(DebounceInfoData->OldTimerValue - 1);                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  if (DebounceInfoData->NewTimerValue == 0)
  {
    DebounceInfoData->NewTimerState = DEM_DEBOUNCE_TIMEBASED_DONE_PASSED;                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    if (lEnableConditionsSatisfied == TRUE)
    {
      Dem_DebounceBase_SetMonitorTrigger(&(DebounceInfoData->Base), DEM_EVENT_STATUS_PASSED);                                    /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
    }
  }
}
#endif

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 % Dem_DebounceTimeBased_CountingTowardsFailed
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
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_CountingTowardsFailed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  )
{
  Dem_EventIdType lEventId;
  boolean lEnableConditionsSatisfied;

  lEventId = Dem_DebounceBase_GetEventId(&(DebounceInfoData->Base));                                                             /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
  lEnableConditionsSatisfied = Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId);

  /* process event timer */
  DebounceInfoData->NewTimerValue = (uint16)(DebounceInfoData->OldTimerValue - 1);                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  if (DebounceInfoData->NewTimerValue <= Dem_DebounceTimeBased_EventStorageTime(lEventId))
  {
    if (DebounceInfoData->NewTimerValue == 0)
    {
      DebounceInfoData->NewTimerState = DEM_DEBOUNCE_TIMEBASED_DONE_FAILED;                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      if (lEnableConditionsSatisfied == TRUE)
      {
        Dem_DebounceBase_SetMonitorTrigger(&(DebounceInfoData->Base), DEM_EVENT_STATUS_FAILED);                                  /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
      }
    }
    else
    {
      DebounceInfoData->NewTimerState = DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED_FDC;                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    if (lEnableConditionsSatisfied == TRUE)
    {
      Dem_DebounceBase_SetFdcThresholdExceeded(&(DebounceInfoData->Base));                                                       /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
      Dem_DebounceBase_SetRequestFdcProcessing(&(DebounceInfoData->Base));                                                       /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
    }
  }
  if ((lEnableConditionsSatisfied == TRUE)                                                                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_DebounceBaseSat_GetDebounceValueMax(lEventId) > DebounceInfoData->NewTimerValue))
  {
    Dem_DebounceBase_SetMaximumFdcExceeded(&(DebounceInfoData->Base));                                                           /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
    Dem_DebounceBase_SetRequestFdcProcessing(&(DebounceInfoData->Base));                                                         /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 % Dem_DebounceTimeBased_CountingTowardsFailedWithFDCReached
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_CountingTowardsFailedWithFDCReached(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  )
{
  Dem_EventIdType lEventId;
  boolean lEnableConditionsSatisfied;
  lEventId = Dem_DebounceBase_GetEventId(&(DebounceInfoData->Base));                                                             /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
  lEnableConditionsSatisfied = Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId);

  /* process event timer */
  DebounceInfoData->NewTimerValue = (uint16)(DebounceInfoData->OldTimerValue - 1);                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  if (DebounceInfoData->NewTimerValue == 0)
  {
    DebounceInfoData->NewTimerState = DEM_DEBOUNCE_TIMEBASED_DONE_FAILED;                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    if (lEnableConditionsSatisfied == TRUE)
    {
      Dem_DebounceBase_SetMonitorTrigger(&(DebounceInfoData->Base), DEM_EVENT_STATUS_FAILED);                                    /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
    }
  }

  if ((lEnableConditionsSatisfied == TRUE)                                                                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_DebounceBaseSat_GetDebounceValueMax(lEventId) > DebounceInfoData->NewTimerValue))
  {
    Dem_DebounceBase_SetMaximumFdcExceeded(&(DebounceInfoData->Base));                                                           /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
    Dem_DebounceBase_SetRequestFdcProcessing(&(DebounceInfoData->Base));                                                         /* SBSW_DEM_DEBOUNCETIMEBASED_INFO_BASE_PTR */
  }
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PUBLIC FUNCTION IMPLEMENTATION
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_DebounceTimeBased_Public
 * \{
 */

/* ****************************************************************************
 % Dem_DebounceTimeBased_InfoInit
 *****************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
DEM_LOCAL_INLINE FUNC(Dem_DebounceBase_InfoPtrType, DEM_CODE)
Dem_DebounceTimeBased_InfoInit(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC) DebounceInfoData,
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_DebounceBase_InfoPtrType lReturnValue;
  lReturnValue = Dem_DebounceBase_InfoInitDefault(&(DebounceInfoData->Base),                                                     /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
                                                  &Dem_DebounceTimeBased_FunctionTable,                                          /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
                                                  EventId);                                
  DebounceInfoData->OldTimerState = Dem_SatelliteData_GetDebounceStatus(SatelliteData);                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DebounceInfoData->NewTimerState = DebounceInfoData->OldTimerState;                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DebounceInfoData->OldTimerValue = Dem_SatelliteData_GetDebounceData(SatelliteData);                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DebounceInfoData->NewTimerValue = DebounceInfoData->OldTimerValue;                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_Calculate
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
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DebounceTimeBased_Calculate(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  Dem_EventIdType lEventId;
  Dem_DebounceTimeBased_InfoPtrType lDebounceInfo;
  boolean lEnableConditionsSatisfied;
  boolean lReturnValue;

  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  if (Dem_DebounceTimeBased_CheckDebounceInfoPtr((Dem_DebounceBase_ConstInfoPtrType)DebounceInfoPtr) == TRUE)                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    lDebounceInfo = Dem_DebounceTimeBased_Base2TimeBased(DebounceInfoPtr);                                                       /* SBSW_DEM_CALL_DEBOUNCETIMEBASED_INFOPTR_INIT */
    lEnableConditionsSatisfied = Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId);

    /* Monitor status for this event not supported */
    if (Dem_DebounceBase_GetMonitorTrigger(DebounceInfoPtr) == DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED)                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_DATA);
      lReturnValue = FALSE;           
    }
    else
    {           
      if ((lEnableConditionsSatisfied == TRUE)                                                                                   /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        || (Dem_Cfg_EventDebounceContinuous(lEventId) == TRUE)
        )
      {
        switch (Dem_DebounceBase_GetMonitorTrigger(DebounceInfoPtr))                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        {
        case DEM_EVENT_STATUS_PREPASSED:
          Dem_DebounceTimeBased_CalculatePrepassed(lDebounceInfo);                                                               /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_FORWARD_ARGUMENT */
          break;

        case DEM_EVENT_STATUS_PREFAILED:
          Dem_DebounceTimeBased_CalculatePrefailed(lDebounceInfo);                                                               /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_FORWARD_ARGUMENT */
          break;

        case DEM_EVENT_STATUS_PASSED:
          Dem_DebounceTimeBased_CalculatePassed(lDebounceInfo);                                                                  /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_FORWARD_ARGUMENT */
          break;

        case DEM_EVENT_STATUS_FAILED:
          Dem_DebounceTimeBased_CalculateFailed(lDebounceInfo);                                                                  /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_FORWARD_ARGUMENT */
          break;

        default:
          /* Satisfy Misra */
          break;
        }

        if (lDebounceInfo->OldTimerState != lDebounceInfo->NewTimerState)
        {
          Dem_DebounceBase_SetDebouncingChanged(DebounceInfoPtr);                                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        }
  #if (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON)
        else if ((lEnableConditionsSatisfied == TRUE)                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          && (lDebounceInfo->OldTimerState == DEM_DEBOUNCE_TIMEBASED_DONE_FAILED)
          && (Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(lEventId)) == Dem_DTCInternalStatus_StoredStatus_None))
        {
          Dem_DebounceBase_SetMonitorTrigger(DebounceInfoPtr, DEM_EVENT_STATUS_FAILED);                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
          Dem_DebounceBase_SetDebouncingChanged(DebounceInfoPtr);                                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        }
        else
        {
          /* MISRA */
        }
  #endif

        lReturnValue = TRUE;
      }
      else
      {
        lReturnValue = FALSE;
      }
    }
  }
  else
  {
    lReturnValue = FALSE;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_DebounceTimeBased_Freeze
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_Freeze(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  Dem_EventIdType lEventId;

  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  switch (Dem_DebounceTimeBased_GetOldTimerState(DebounceInfoPtr))                                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
  case DEM_DEBOUNCE_TIMEBASED_RESET_FAILED:
    Dem_DebounceTimeBased_SetNewTimerValue(DebounceInfoPtr, Dem_DebounceTimeBased_EventFailedTime(lEventId));                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_DebounceTimeBased_SetNewTimerState(DebounceInfoPtr, DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED);                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_DEBOUNCE_TIMEBASED_RESET_PASSED:
    Dem_DebounceTimeBased_SetNewTimerValue(DebounceInfoPtr, Dem_DebounceTimeBased_EventPassedTime(lEventId));                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_DebounceTimeBased_SetNewTimerState(DebounceInfoPtr, DEM_DEBOUNCE_TIMEBASED_FROZEN_PASSED);                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED:
    Dem_DebounceTimeBased_SetNewTimerState(DebounceInfoPtr, DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED);                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_DEBOUNCE_TIMEBASED_COUNT_PASSED:
    Dem_DebounceTimeBased_SetNewTimerState(DebounceInfoPtr, DEM_DEBOUNCE_TIMEBASED_FROZEN_PASSED);                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED_FDC:
    Dem_DebounceTimeBased_SetNewTimerState(DebounceInfoPtr, DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED_FDC);                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  default:
    /* Nothing to do */
    break;
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DebounceTimeBased_Reset
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_Reset(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                                /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  Dem_DebounceTimeBased_SetNewTimerState(DebounceInfoPtr, DEM_DEBOUNCE_TIMEBASED_NONE);                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  Dem_DebounceTimeBased_SetNewTimerValue(DebounceInfoPtr, 0);                                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_GetDebouncingState
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
 */
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebounceTimeBased_GetDebouncingState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                           /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  Dem_DebouncingStateType lDebouncingState;
  Dem_EventIdType lEventId;

  lDebouncingState = Dem_DebouncingState_GetInitValue();
  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  switch (Dem_DebounceTimeBased_GetOldTimerState(DebounceInfoPtr))                                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
  case DEM_DEBOUNCE_TIMEBASED_DONE_FAILED:
    lDebouncingState = Dem_DebouncingState_SetFinallyDefective(lDebouncingState);
    lDebouncingState = Dem_DebouncingState_SetTestComplete(lDebouncingState);
    if ((Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId) == TRUE)                                               /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_StorageCondition_TestEventStorageConditionsFulfilled(lEventId) == TRUE))
    {
      lDebouncingState = Dem_DebouncingState_SetDtrUpdate(lDebouncingState);
    }
    break;
  case DEM_DEBOUNCE_TIMEBASED_DONE_PASSED:
    lDebouncingState = Dem_DebouncingState_SetTestComplete(lDebouncingState);
    if ((Dem_EnableCondition_TestEventEnableConditionsFulfilled(lEventId) == TRUE)                                               /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_StorageCondition_TestEventStorageConditionsFulfilled(lEventId) == TRUE))
    {
      lDebouncingState = Dem_DebouncingState_SetDtrUpdate(lDebouncingState);
    }
    break;
  case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED:
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED:
  case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED_FDC:
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED_FDC:
  case DEM_DEBOUNCE_TIMEBASED_RESET_FAILED:
    lDebouncingState = Dem_DebouncingState_SetTemporarilyDefective(lDebouncingState);
    break;
  case DEM_DEBOUNCE_TIMEBASED_COUNT_PASSED:
  case DEM_DEBOUNCE_TIMEBASED_FROZEN_PASSED:
  case DEM_DEBOUNCE_TIMEBASED_RESET_PASSED:
    lDebouncingState = Dem_DebouncingState_SetTemporarilyHealed(lDebouncingState);
    break;
  case DEM_DEBOUNCE_TIMEBASED_NONE:
  default:
    /* debouncing state 0 */
    break;
  }

  return lDebouncingState;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DebounceTimeBasedSat_UpdateDebounceValueMax
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBasedSat_UpdateDebounceValueMax(
CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
)
{
  Dem_EventIdType lEventId;
  Dem_DebounceTimeBased_ConstInfoPtrType lTimeBasedInfo;

  Dem_Internal_AssertContinue(DebounceInfoPtr->FunctionTable == &Dem_DebounceTimeBased_FunctionTable, DEM_E_INCONSISTENT_STATE)
  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lTimeBasedInfo = Dem_DebounceTimeBased_ConstBase2TimeBased(DebounceInfoPtr);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  if (lTimeBasedInfo->NewTimerValue < Dem_DebounceBaseSat_GetDebounceValueMax(lEventId))
  {
    Dem_DebounceBaseSat_SetDebounceValueMax(lEventId, (sint16)lTimeBasedInfo->NewTimerValue);
  }
}

/* ****************************************************************************
 % Dem_DebounceTimeBasedSat_ResetDebounceValueMax
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBasedSat_ResetDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  Dem_EventIdType lEventId;
  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  Dem_DebounceBaseSat_SetDebounceValueMax(lEventId, (sint16)Dem_DebounceTimeBased_EventFailedTime(lEventId));
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceTimeBased_GetFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  )
{
  Dem_EventIdType lEventId;

  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  *FaultDetectionCounter = Dem_DebounceTimeBased_CalculateFaultDetectionCounter(                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
                              lEventId,
                              Dem_DebounceTimeBased_GetOldTimerValue(DebounceInfoPtr),                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                              Dem_DebounceTimeBased_GetOldTimerState(DebounceInfoPtr));                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  return E_OK;
}

/* ****************************************************************************
 % Dem_DebounceTimeBasedSat_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceTimeBased_GetMaxFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  )
{
  Dem_EventIdType lEventId;

  lEventId = Dem_DebounceBase_GetEventId(DebounceInfoPtr);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  if (Dem_DebounceBaseSat_GetDebounceValueMax(lEventId) != Dem_DebounceTimeBased_EventFailedTime(lEventId))
  {
    *FaultDetectionCounter = Dem_DebounceTimeBased_CalculateFaultDetectionCounter(                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
                                lEventId,
                                (uint16)Dem_DebounceBaseSat_GetDebounceValueMax(lEventId),
                                DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED);
  }
  else
  {
    *FaultDetectionCounter = 0;                                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }

  return E_OK;
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_GetDebouncingResult
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceTimeBased_GetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_SatelliteData_DataType lReturnValue;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteData;
  lReturnValue = Dem_SatelliteData_SetDebounceStatus(lReturnValue, Dem_DebounceTimeBased_GetNewTimerState(DebounceInfoPtr));     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lReturnValue = Dem_SatelliteData_SetDebounceData(lReturnValue, Dem_DebounceTimeBased_GetNewTimerValue(DebounceInfoPtr));       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DebounceTimeBased_RestoreDebounceValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceTimeBased_RestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteData)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Value)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ExpectedThreshold)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */

  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);

  return SatelliteData;
}

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 % Dem_DebounceTimeBasedSat_ProcessDebounce
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceTimeBasedSat_ProcessDebounce(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  Dem_DebounceTimeBased_InfoPtrType lDebounceInfo;

  if (Dem_DebounceTimeBased_CheckDebounceInfoPtr((Dem_DebounceBase_ConstInfoPtrType)DebounceInfoPtr) == TRUE)                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    lDebounceInfo = Dem_DebounceTimeBased_Base2TimeBased(DebounceInfoPtr);                                                       /* SBSW_DEM_CALL_DEBOUNCETIMEBASED_INFOPTR_INIT */

    switch (lDebounceInfo->OldTimerState)
    {
    case DEM_DEBOUNCE_TIMEBASED_RESET_PASSED:
    {
      uint16 lNewTimerValue = Dem_DebounceTimeBased_EventPassedTime(Dem_DebounceBase_GetEventId(DebounceInfoPtr));               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      lDebounceInfo->NewTimerValue = lNewTimerValue;                                                                             /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_WRITE_STACK */
      lDebounceInfo->NewTimerState = DEM_DEBOUNCE_TIMEBASED_COUNT_PASSED;                                                        /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_WRITE_STACK */
      break;
    }

    case DEM_DEBOUNCE_TIMEBASED_RESET_FAILED:
    {
      uint16 lNewTimerValue = Dem_DebounceTimeBased_EventFailedTime(Dem_DebounceBase_GetEventId(DebounceInfoPtr));               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      lDebounceInfo->NewTimerValue = lNewTimerValue;                                                                             /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_WRITE_STACK */
      lDebounceInfo->NewTimerState = DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED;                                                        /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_WRITE_STACK */
      break;
    }

    case DEM_DEBOUNCE_TIMEBASED_COUNT_PASSED:
      Dem_DebounceTimeBased_CountingTowardsPassed(lDebounceInfo);                                                                /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_FORWARD_ARGUMENT */
      break;

    case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED:
      Dem_DebounceTimeBased_CountingTowardsFailed(lDebounceInfo);                                                                /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_FORWARD_ARGUMENT */
      break;

    case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED_FDC:
      Dem_DebounceTimeBased_CountingTowardsFailedWithFDCReached(lDebounceInfo);                                                  /* SBSW_DEM_DEBOUNCETIMEBASED_INFOPTR_FORWARD_ARGUMENT */
      break;

    default:
      Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
      break;
    }
  }
  else
  {
    /* MISRA */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif                                                                                                                           

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 % Dem_DebounceTimeBasedSat_IsTimerActive
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
Dem_DebounceTimeBasedSat_IsTimerActive(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  Dem_DebounceTimeBased_InfoPtrType lDebounceInfo;
  boolean lReturnValue;

  lReturnValue = FALSE;
  if (Dem_DebounceTimeBased_CheckDebounceInfoPtr((Dem_DebounceBase_ConstInfoPtrType)DebounceInfoPtr) == TRUE)                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    lDebounceInfo = Dem_DebounceTimeBased_Base2TimeBased(DebounceInfoPtr);                                                       /* SBSW_DEM_CALL_DEBOUNCETIMEBASED_INFOPTR_INIT */

    switch (lDebounceInfo->OldTimerState)
    {
    case DEM_DEBOUNCE_TIMEBASED_FROZEN_PASSED:
    case DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED:
    case DEM_DEBOUNCE_TIMEBASED_FROZEN_FAILED_FDC:
    case DEM_DEBOUNCE_TIMEBASED_DONE_PASSED:
    case DEM_DEBOUNCE_TIMEBASED_DONE_FAILED:
    case DEM_DEBOUNCE_TIMEBASED_NONE:
      break;
    case DEM_DEBOUNCE_TIMEBASED_RESET_PASSED:
    case DEM_DEBOUNCE_TIMEBASED_RESET_FAILED:
    case DEM_DEBOUNCE_TIMEBASED_COUNT_PASSED:
    case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED:
    case DEM_DEBOUNCE_TIMEBASED_COUNT_FAILED_FDC:
      lReturnValue = TRUE;
      break;
    default:
      Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE)
      break;
    }
  }
  else
  {
    /* MISRA */
  }
  return lReturnValue;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DEBOUNCETIMEBASED_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceTimeBased_Implementations.h
 *********************************************************************************************************************/
