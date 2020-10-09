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
/*!  Project    MICROSAR Diagnostic Event Manager (Dem)
 *
 *  \addtogroup Dem_Debounce
 *  \{
 *  \file       Dem_Debounce_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of Debounce subcomponent
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

#if !defined (DEM_DEBOUNCE_IMPLEMENTATION_H)
#define DEM_DEBOUNCE_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Debounce_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceBase_Implementation.h"
#include "Dem_DebounceCounterBased_Implementation.h"
#include "Dem_DebounceTimeBased_Implementation.h"
#include "Dem_DebounceMonitorInternal_Implementation.h"
#include "Dem_SatelliteData_Implementation.h"
#include "Dem_Event_Implementation.h"
#include "Dem_EventInternalStatus_Implementation.h"

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
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/


#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

DEM_LOCAL CONST(Dem_DebounceFunctionTableType, DEM_CONST) Dem_Debounce_InvalidFunctionTable =                                    /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  Dem_Debounce_InvalidCalculate,
  Dem_Debounce_InvalidVoid,
  Dem_Debounce_InvalidVoid,
  Dem_Debounce_InvalidGetDebouncingState,
  Dem_Debounce_InvalidUpdateMax,
  Dem_Debounce_InvalidUpdateMax,
  Dem_Debounce_InvalidGetFDC,
  Dem_Debounce_InvalidGetFDC,
  Dem_Debounce_InvalidGetDebouncingResult,
  Dem_Debounce_InvalidRestoreDebounceValue
};

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \addtogroup Dem_Debounce_Private
 * \{
 */

/* ****************************************************************************
 % Dem_Debounce_RemoveSimilarConditionQualifier
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventStatusType, DEM_CODE)
Dem_Debounce_RemoveSimilarConditionQualifier(
  CONST(Dem_EventStatusType, AUTOMATIC)  MonitorTrigger
  )
{
#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
  Dem_EventStatusType lMonitorTrigger;
  switch (MonitorTrigger)
  {
  case DEM_EVENT_STATUS_PREPASSED_CONDITIONS_NOT_FULFILLED:
    lMonitorTrigger = DEM_EVENT_STATUS_PREPASSED;
    break;
  case DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED:
    lMonitorTrigger = DEM_EVENT_STATUS_PASSED;
    break;
  case DEM_EVENT_STATUS_PREFAILED_CONDITIONS_NOT_FULFILLED:
    lMonitorTrigger = DEM_EVENT_STATUS_PREFAILED;
    break;
  case DEM_EVENT_STATUS_FAILED_CONDITIONS_NOT_FULFILLED:
    lMonitorTrigger = DEM_EVENT_STATUS_FAILED;
    break;
  default:
    lMonitorTrigger = MonitorTrigger;
    break;
  }
  return lMonitorTrigger;
#else
  return MonitorTrigger;
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION IMPLEMENTATION
 *********************************************************************************************************************/

/*!
 * \addtogroup Dem_Debounce_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Debounce_GetDebouncingResult
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_GetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  return Dem_DebounceBase_GetDebouncingResult(DebounceInfoPtr, SatelliteData);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_ResetDebouncing
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_ResetDebouncing(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_DebounceBase_Reset(DebounceInfoPtr);                                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return Dem_DebounceBase_GetDebouncingResult(DebounceInfoPtr, SatelliteData);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_FreezeDebouncing
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_FreezeDebouncing(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_DebounceBase_Freeze(DebounceInfoPtr);                                                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return Dem_DebounceBase_GetDebouncingResult(DebounceInfoPtr, SatelliteData);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_CalculateDebouncing
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_CalculateDebouncing(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  Dem_EventStatusType lOldMonitorTrigger;
  Dem_EventStatusType lNewMonitorTrigger;

  lOldMonitorTrigger = Dem_DebounceBase_GetMonitorTrigger(DebounceInfoPtr);                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lNewMonitorTrigger = Dem_Debounce_RemoveSimilarConditionQualifier(lOldMonitorTrigger);

  Dem_DebounceBase_SetMonitorTrigger(DebounceInfoPtr, lNewMonitorTrigger);                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return Dem_DebounceBase_CalculateDebouncing(DebounceInfoPtr);                                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_SetMonitorTrigger
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Debounce_SetMonitorTrigger(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_EventStatusType, AUTOMATIC)           MonitorTrigger
  )
{
  Dem_DebounceBase_SetMonitorTrigger(DebounceInfoPtr, MonitorTrigger);                                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_GetMonitorTrigger
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventStatusType, DEM_CODE)
Dem_Debounce_GetMonitorTrigger(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return Dem_DebounceBase_GetMonitorTrigger(DebounceInfoPtr);                                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_TestRequestFdcProcessing()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestRequestFdcProcessing(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  return Dem_DebounceBase_TestRequestFdcProcessing(DebounceInfoPtr);                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_TestFdcThresholdExceeded()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestFdcThresholdExceeded(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  return Dem_DebounceBase_TestFdcThresholdExceeded(DebounceInfoPtr);                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_TestMaximumFdcExceeded()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestMaximumFdcExceeded(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  return Dem_DebounceBase_TestMaximumFdcExceeded(DebounceInfoPtr);                                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 %  Dem_Debounce_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Debounce_GetFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  )
{
  return Dem_DebounceBase_GetFaultDetectionCounter(DebounceInfoPtr, FaultDetectionCounter);                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 %  Dem_Debounce_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Debounce_GetMaxFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  sint8 lFdcMax;
  (void)Dem_DebounceBase_GetMaxFaultDetectionCounter(DebounceInfoPtr, &lFdcMax);                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  return lFdcMax;
}

/* ****************************************************************************
 % Dem_Debounce_GetDebouncingState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_Debounce_GetDebouncingState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return Dem_DebounceBase_GetDebouncingState(DebounceInfoPtr);                                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_TestDebouncingChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestDebouncingChanged(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return Dem_DebounceBase_TestDebouncingChanged(DebounceInfoPtr);                                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Debounce_DebounceInfoInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DebounceBase_InfoPtrType, DEM_CODE)
Dem_Debounce_DebounceInfoInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_Debounce_InfoType, AUTOMATIC, AUTOMATIC)  DebounceInfoData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_DebounceBase_InfoPtrType base;

  switch(Dem_Cfg_EventDebounceType(EventId))
  {
  case DEM_CFG_DEBOUNCETYPE_COUNTER:
    base = Dem_DebounceCounterBased_InfoInit(&(DebounceInfoData->CounterBased), EventId, SatelliteData);                         /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
    break;
  case DEM_CFG_DEBOUNCETYPE_TIMER:
    base = Dem_DebounceTimeBased_InfoInit(&(DebounceInfoData->TimeBased), EventId, SatelliteData);                               /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
    break;
  case DEM_CFG_DEBOUNCETYPE_MONITORINTERNAL: 
    base = Dem_DebounceMonitorInternal_InfoInit(&(DebounceInfoData->MonitorInternal), EventId, SatelliteData);                   /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
    break;
  default:
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
#endif
    base = Dem_DebounceBase_InfoInitDefault(&(DebounceInfoData->InvalidDebounce), &Dem_Debounce_InvalidFunctionTable, EventId);  /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
    break;
  }

  return base;
}


/* ****************************************************************************
 % Dem_Debounce_TestQualifiedResult
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Debounce_TestQualifiedResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  return (boolean)(Dem_DebounceBase_GetMonitorTrigger(DebounceInfoPtr) <= DEM_EVENT_STATUS_FAILED);                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/* ****************************************************************************
 % Dem_DebounceSat_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceSat_PreInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MonitorId)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_MAX_DEBOUNCE_VALUE == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ((SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())                                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (MonitorId >= (Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId))))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    (Dem_Cfg_GetMaxDebounceValuesOfSatelliteInfo(SatelliteId))[MonitorId] = 0;                                                   /* SBSW_DEM_WRITE_SATELLITEINFO_MAXDEBOUNCE_VALUE */
  }
#endif
}

#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
/* ****************************************************************************
 % Dem_Debounce_RestoreDebounceValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_RestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  )
{
  return Dem_DebounceBase_RestoreDebounceValue(DebounceInfoPtr, SatelliteData, Value, ExpectedThreshold);                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}
#endif

/* ****************************************************************************
 % Dem_Debounce_InvalidCalculate
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Debounce_InvalidCalculate(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                                /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_Internal */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
  return FALSE;
}

/* ****************************************************************************
 % Dem_Debounce_InvalidVoid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Debounce_InvalidVoid(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                                /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_Internal */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
}


/* ****************************************************************************
 % Dem_Debounce_InvalidUpdateMax
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Debounce_InvalidUpdateMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                           /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_Internal */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
}

/* ****************************************************************************
 % Dem_Debounce_InvalidGetDebouncingState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_Debounce_InvalidGetDebouncingState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr                                                           /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_Internal */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
  return 0;
}

/* ****************************************************************************
 % Dem_Debounce_InvalidGetDebouncingResult
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_InvalidGetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
  return SatelliteData;
}

/* ****************************************************************************
 % Dem_Debounce_InvalidGetFDC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Debounce_InvalidGetFDC(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter                                                              /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_Internal */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FaultDetectionCounter)                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
  return E_NOT_OK;
}

/* ****************************************************************************
 * Dem_Debounce_InvalidRestoreDebounceValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Debounce_InvalidRestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,                                                                    /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_Internal */
  CONST(sint16, AUTOMATIC) Value,                                                                                                /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(boolean, AUTOMATIC) ExpectedThreshold                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DebounceInfoPtr)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteData)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Value)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ExpectedThreshold)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */

  Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);

  return SatelliteData;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DEBOUNCE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Debounce_Implementation.h
 *********************************************************************************************************************/
