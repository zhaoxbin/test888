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
/*! \addtogroup Dem_EventQueue
 *  \{
 *  \file       Dem_EventQueue_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of EventQueue subcomponent
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

#if !defined (DEM_EVENTQUEUE_IMPLEMENTATION_H)
#define DEM_EVENTQUEUE_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_EventQueue_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg_Definitions.h"
#include "Dem_Scheduler_Implementation.h"
#include "Dem_Event_Implementation.h"
#include "Dem_EventInternalStatus_Implementation.h"
#include "Dem_Nvm_Implementation.h"
#include "Dem_UDSStatus_Implementation.h"
#include "Dem_SatelliteData_Implementation.h"
#include "Dem_DTC_Implementation.h"
#include "Dem_Prestore_Implementation.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Satellite_Interface.h"
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

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_EventQueue_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_EventQueue_ResetQueueStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_EventQueue_ResetQueueStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData
  )
{
  return Dem_SatelliteData_SetQueueStatus(SatelliteData, DEM_EVENTQUEUE_STATE_INITIAL);
}

/* ****************************************************************************
 % Dem_EventQueue_GetQueueStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_GetQueueStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  return Dem_SatelliteData_GetQueueStatus(SatelliteData);
}

/* ****************************************************************************
 % Dem_EventQueue_TestSimilarConditionStatusChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestSimilarConditionStatusChanged(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(QueueStatus)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
  return (boolean)((QueueStatus & DEM_EVENTQUEUE_SIMILAR_CONDITIONS) != 0);
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_EventQueue_SetSimilarConditionStatusChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetSimilarConditionStatusChanged(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus | DEM_EVENTQUEUE_SIMILAR_CONDITIONS);
}

/* ****************************************************************************
 % Dem_EventQueue_ResetSimilarConditionStatusChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_ResetSimilarConditionStatusChanged(                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus & DEM_EVENTQUEUE_SIMILAR_CONDITIONS_MASK);
}

/* ****************************************************************************
 % Dem_EventQueue_TestFdcTripStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestFdcTripStatus(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus                                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)((QueueStatus & DEM_EVENTQUEUE_FDC_TRIP) != 0);
}

/* ****************************************************************************
 % Dem_EventQueue_SetFdcTripStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetFdcTripStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus | DEM_EVENTQUEUE_FDC_TRIP);
}

/* ****************************************************************************
 % Dem_EventQueue_TestFdcMaxSLCStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestFdcMaxSLCStatus(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus                                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)((QueueStatus & DEM_EVENTQUEUE_FDC_MAX_SLC) != 0);
}

/* ****************************************************************************
 % Dem_EventQueue_SetFdcMaxSLCStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetFdcMaxSLCStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus | DEM_EVENTQUEUE_FDC_MAX_SLC);
}

/* ****************************************************************************
 % Dem_EventQueue_TestFdcProcessingStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestFdcProcessingStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus                                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(QueueStatus)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_FDC_TRIP == STD_ON)
  return (boolean)((QueueStatus & DEM_EVENTQUEUE_FDC_PROCESSING) != 0);
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_EventQueue_SetFdcProcessingStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetFdcProcessingStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus | DEM_EVENTQUEUE_FDC_PROCESSING);
}

/* ****************************************************************************
 % Dem_EventQueue_TestResetTestFailedRequested
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestResetTestFailedRequested(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus                                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  return (boolean)((QueueStatus & DEM_EVENTQUEUE_RESET_TESTFAILED) != 0);
}

/* ****************************************************************************
 % Dem_EventQueue_SetResetTestFailedRequested
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetResetTestFailedRequested(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  return (Dem_EventQueue_StatusType)(QueueStatus | DEM_EVENTQUEUE_RESET_TESTFAILED);
}

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
 * \addtogroup Dem_EventQueue_Private
 * \{
 */

/* ****************************************************************************
 % Dem_EventQueue_GetQueueAction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EventQueue_GetQueueAction(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
  )
{
  return (uint8)(QueueStatus & DEM_EVENTQUEUE_ACTION);
}

/* ****************************************************************************
 % Dem_EventQueue_SetQueueAction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_SetQueueAction(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus,
  CONST(uint8, AUTOMATIC) Action
  )
{
  return (uint8)(
       (QueueStatus & DEM_EVENTQUEUE_ACTION_MASK)
     | (Action & DEM_EVENTQUEUE_ACTION) );
}

/* ****************************************************************************
 % Dem_EventQueueCore_ProcessQueuedEventActions
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
Dem_EventQueueCore_ProcessQueuedEventActions(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
  if (Dem_EventQueue_TestResetTestFailedRequested(QueueStatus) == TRUE)
  {
    Dem_Event_ResetTestFailed(EventId);
  }
#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
  if (Dem_EventQueue_TestFdcProcessingStatus(QueueStatus) == TRUE)
  {
    uint8 lTestCompleted;
    /* First completed test this cycle */
    lTestCompleted = (uint8)( (Dem_EventQueue_GetQueueAction(QueueStatus) != 0)                                                  /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
                           && (Dem_UDSStatus_Test_TNCTOC(Dem_Event_GetUDSStatus(EventId)) == TRUE) );

    Dem_DTC_FdcTrip_Vcc(EventId, lTestCompleted);
  }
#else
  if (Dem_EventQueue_TestFdcProcessingStatus(QueueStatus) == TRUE)
  {
    Dem_Event_ProcessFdc(EventId,
      (boolean)(Dem_EventQueue_TestFdcTripStatus(QueueStatus) == TRUE),
      (boolean)(Dem_EventQueue_TestFdcMaxSLCStatus(QueueStatus) == TRUE));
  }
#endif

  switch (Dem_EventQueue_GetQueueAction(QueueStatus))
  {
  case DEM_EVENTQUEUE_PASSED:
    Dem_Event_Passed(EventId);
    break;
  case DEM_EVENTQUEUE_PASSED_FAILED:
    Dem_Event_Passed(EventId);
    Dem_Event_Failed(EventId);
    break;
  case DEM_EVENTQUEUE_PASSED_FAILED_PASSED:
    Dem_Event_Passed(EventId);
    Dem_Event_Failed(EventId);
    Dem_Event_Passed(EventId);
    break;

  case DEM_EVENTQUEUE_FAILED:
    Dem_Event_Failed(EventId);
    break;
  case DEM_EVENTQUEUE_FAILED_PASSED:
    Dem_Event_Failed(EventId);
    Dem_Event_Passed(EventId);
    break;
  case DEM_EVENTQUEUE_FAILED_PASSED_FAILED:
    Dem_Event_Failed(EventId);
    Dem_Event_Passed(EventId);
    Dem_Event_Failed(EventId);
    break;

  default:
    /* No action */
    break;
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_EventQueue_ProcessEventQueuedEventActions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueue_ProcessEventQueuedEventActions(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  )
{
#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  Dem_Prestore_EventPrestorageLock(EventId);
#endif

  Dem_EventQueueCore_ProcessQueuedEventActions(EventId, QueueStatus);

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  Dem_Prestore_EventPrestorageRelease();
#endif
}

/* ****************************************************************************
 % Dem_EventQueue_ProcessSatelliteSimilarCondition
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
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_ProcessSatelliteSimilarCondition(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
  Dem_EventQueue_StatusType lQueueStatus;
  lQueueStatus = QueueStatus;
  if (Dem_EventQueue_TestSimilarConditionStatusChanged(QueueStatus) == TRUE)
  {
    Dem_DTC_ExtendedStatusType lOldExtendedStatus;
    boolean lOldSimilarConditionStatus;
    boolean lNewSimilarConditionStatus;

    Dem_Internal_AssertContinue(Dem_Cfg_EventObdRelated(EventId), DEM_E_INCONSISTENT_STATE)
    lOldExtendedStatus = Dem_Event_GetExtendedStatus(EventId);
    lOldSimilarConditionStatus = Dem_EventInternalStatus_TestSimilarConditions(lOldExtendedStatus);
    lNewSimilarConditionStatus = Dem_SatelliteData_TestSimilarConditionStatus(SatelliteData);

    if (lNewSimilarConditionStatus != lOldSimilarConditionStatus)
    {
      Dem_Event_ExtendedStatusType lNewExtendedStatus;
      if (lNewSimilarConditionStatus == TRUE)
      {
        lNewExtendedStatus = Dem_EventInternalStatus_SetSimilarConditions(lOldExtendedStatus);
      }
      else
      {
        lNewExtendedStatus = Dem_EventInternalStatus_ResetSimilarConditions(lOldExtendedStatus);
      }
      Dem_Event_SetExtendedStatus(EventId, lNewExtendedStatus);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_STATUS), 
                                  DEM_NVM_BLOCKSTATE_DIRTY);
    }
    lQueueStatus = Dem_EventQueue_ResetSimilarConditionStatusChanged(lQueueStatus);
  }
  return lQueueStatus;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(QueueStatus)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteData)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return QueueStatus;
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_EventQueue_ProcessSatelliteQueuedEventActions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueue_ProcessSatelliteQueuedEventActions(
  CONST(Dem_Satellite_IdType, AUTOMATIC) SatelliteId
  )
{
  Dem_Satellite_MonitorIdType lMonitorId;

  for (lMonitorId = 0;
       lMonitorId < Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId);
       ++lMonitorId)
  {
    if (Dem_Satellite_PeekEventQueueStatus(SatelliteId, lMonitorId) != DEM_EVENTQUEUE_STATE_INITIAL)
    {
      Dem_SatelliteData_DataType lSatelliteData;                                                                                 /* PRQA S 0759 */ /* MD_MSR_18.4 */
      Dem_EventQueue_StatusType lQueueStatus;
      Dem_EventIdType lEventId;

      lEventId = Dem_Satellite_GetEventId(SatelliteId, lMonitorId);
      lSatelliteData = Dem_SatelliteCore_ConsumeEventQueueStatus(SatelliteId, lMonitorId);
      lQueueStatus = Dem_SatelliteData_GetQueueStatus(lSatelliteData);
      lQueueStatus = Dem_EventQueue_ProcessSatelliteSimilarCondition(lQueueStatus, lSatelliteData, lEventId);
      if (lQueueStatus != DEM_EVENTQUEUE_STATE_INITIAL)
      {
        Dem_EventQueue_ProcessEventQueuedEventActions(lEventId, lQueueStatus);
      }
    }
  }
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
 * \addtogroup Dem_EventQueue_Public
 * \{
 */

/* ****************************************************************************
 % Dem_EventQueue_TestQueueOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventQueue_TestQueueOverflow(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_EventStatusType, AUTOMATIC)  MonitorTrigger
  )
{
  Std_ReturnType lReturnValue;
  uint8 lQueueAction;

  lQueueAction = Dem_EventQueue_GetQueueAction(QueueStatus);

  if ( ((MonitorTrigger == DEM_EVENT_STATUS_FAILED) && (lQueueAction == DEM_EVENTQUEUE_PASSED_FAILED_PASSED))
    || ((MonitorTrigger == DEM_EVENT_STATUS_PASSED) && (lQueueAction == DEM_EVENTQUEUE_FAILED_PASSED_FAILED)))
  {
    lReturnValue = TRUE;
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_EventQueue_CalculateQueueStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_EventQueue_CalculateQueueStatus(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_EventStatusType, AUTOMATIC)  MonitorTrigger
  )
{
  Dem_EventQueue_StatusType lReturnValue;

  if (MonitorTrigger == DEM_EVENT_STATUS_FAILED)
  {
    switch (Dem_EventQueue_GetQueueAction(QueueStatus))
    {
    case DEM_EVENTQUEUE_STATE_INITIAL:
      lReturnValue = Dem_EventQueue_SetQueueAction(QueueStatus, DEM_EVENTQUEUE_FAILED);
      break;
    case DEM_EVENTQUEUE_PASSED:
    case DEM_EVENTQUEUE_FAILED_PASSED:
      lReturnValue = (Dem_EventQueue_StatusType)(QueueStatus + 1);
      break;
    default:
      lReturnValue = QueueStatus;
      break;
    }
  }
  else if (MonitorTrigger == DEM_EVENT_STATUS_PASSED)
  {
    switch (Dem_EventQueue_GetQueueAction(QueueStatus))
    {
    case DEM_EVENTQUEUE_STATE_INITIAL:
      lReturnValue = Dem_EventQueue_SetQueueAction(QueueStatus, DEM_EVENTQUEUE_PASSED);
      break;
    case DEM_EVENTQUEUE_FAILED:
    case DEM_EVENTQUEUE_PASSED_FAILED:
      lReturnValue = (Dem_EventQueue_StatusType)(QueueStatus + 1);
      break;
    default:
      lReturnValue = QueueStatus;
      break;
    }
  }
  else
  {
    /* Not a qualified result */
    lReturnValue = QueueStatus;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_EventQueue_GetResult
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_EventQueue_GetResult(
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  return Dem_SatelliteData_SetQueueStatus(SatelliteData, QueueStatus);
}

/* ****************************************************************************
 % Dem_EventQueueCore_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueueCore_Init(
  void
  )
{
  Dem_Scheduler_EnableTask(Dem_Scheduler_Task_EventQueue);
}

/* ****************************************************************************
 % Dem_EventQueueCore_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventQueueCore_MainFunction(
  void
  )
{
  Dem_Satellite_IdType lSatelliteId;
  for (lSatelliteId = 0; lSatelliteId < Dem_Cfg_GlobalSatelliteCount(); ++lSatelliteId)
  {
    if (Dem_SatelliteCore_TestAndClearEventQueueUpdated(lSatelliteId) == TRUE)
    {
      Dem_EventQueue_ProcessSatelliteQueuedEventActions(lSatelliteId);
    }
  }
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_EVENTQUEUE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EventQueue_Implementation.h
 *********************************************************************************************************************/
