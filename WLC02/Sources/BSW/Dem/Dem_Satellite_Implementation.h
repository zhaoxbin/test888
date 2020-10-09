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
/*!
 *  \addtogroup Dem_Satellite
 *  \{
 *  \file       Dem_Satellite_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of Satellite subcomponent
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

#if !defined (DEM_SATELLITE_IMPLEMENTATION_H)                                                                                    /* PRQA S 0883 */ /* MD_DEM_19.15 */
#define DEM_SATELLITE_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Satellite_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_SatelliteInfo_Implementation.h"
#include "Dem_SatelliteData_Implementation.h"
#include "Dem_Monitor_Implementation.h"
#include "Dem_EventQueue_Implementation.h"
#include "Dem_Debounce_Implementation.h"
#include "Dem_Com_Implementation.h"
#include "Dem_EnableCondition_Implementation.h"
#include "Dem_EventInternalStatus_Implementation.h"
#include "Dem_InitState_Implementation.h"
#include "Dem_UDSStatus_Implementation.h"
#include "Dem_Event_Implementation.h"
#include "Dem_OperationCycle_Implementation.h"
#include "Dem_Notifications_Implementation.h"

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

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_Satellite_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_Satellite_GetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Satellite_GetEventId(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return Dem_Cfg_GetEventTableInd(Dem_Cfg_GetEventTableIndStartIdxOfSatelliteInfo(SatelliteId) + MonitorId);
}

/* ****************************************************************************
 % Dem_Satellite_GetApplicationId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Satellite_ApplicationType, DEM_CODE)
Dem_Satellite_GetApplicationId(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId                                                                            /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_Satellite_ApplicationType lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  lReturnValue = Dem_Cfg_GetApplicationIdOfSatelliteInfo(SatelliteId);
#else
  lReturnValue = DEM_SATELLITE_APPLICATION_ZERO;
#endif

  return lReturnValue;
}

#if (DEM_DEV_ERROR_DETECT == STD_ON)     
/* ****************************************************************************
 % Dem_Satellite_CheckEventApplicationId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_CheckEventApplicationId(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  lReturnValue = (boolean)(GetCurrentApplicationID() == Dem_Satellite_GetApplicationId(Dem_Cfg_GetSatelliteInfoIdxOfEventTable(EventId)));
#else
  lReturnValue = TRUE;
#endif

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR == STD_ON)
/* ****************************************************************************
 % Dem_Satellite_SetDebounceLoResTimer
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_SetDebounceLoResTimer(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Cfg_DebounceLoResTimerType, AUTOMATIC)  LoResTimer
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
    if (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())
    {
      Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                          /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    }
    else
# endif
    {
      *Dem_Cfg_GetDebounceLoResTimerOfSatelliteInfo(SatelliteId) = LoResTimer;                                                   /* SBSW_DEM_WRITE_SATELLITEINFO */
    }
}
#endif

/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/*!
 * \addtogroup Dem_Satellite_Private
 * \{
 */

/* ****************************************************************************
 % Dem_Satellite_GetSatelliteInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_Satellite_GetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_18.4 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue.Raw = *(Dem_Cfg_GetSatelliteStatusOfSatelliteInfo(SatelliteId));
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteSat_SetSatelliteInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  NewSatelliteInfo
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    *Dem_Cfg_GetSatelliteStatusOfSatelliteInfo(SatelliteId) = NewSatelliteInfo.Raw;                                              /* SBSW_DEM_WRITE_SATELLITEINFO */
  }
}

/* ****************************************************************************
 % Dem_SatelliteSat_SyncSetSatelliteInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) OldSatelliteInfo,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) NewSatelliteInfo
  )
{
  boolean lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = TRUE;
  }
  else
#endif
  {
    lReturnValue = Dem_Com_SyncCompareAndSwap(                                                                                   /* SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP_SATELLITEINFO */
        Dem_Cfg_GetSatelliteStatusOfSatelliteInfo(SatelliteId),
        OldSatelliteInfo.Raw,
        NewSatelliteInfo.Raw);
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteCore_SyncSetSatelliteInfo
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_SyncSetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) OldSatelliteInfo,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) NewSatelliteInfo
  )
{
  return Dem_SatelliteSat_SyncSetSatelliteInfo(SatelliteId, OldSatelliteInfo, NewSatelliteInfo);
}

/* ****************************************************************************
 % Dem_Satellite_GetSatelliteData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_GetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (Dem_Cfg_GetSatelliteDataOfSatelliteInfo(SatelliteId))[MonitorId];
}

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 % Dem_Satellite_GetSatelliteExtendedData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_Satellite_GetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (Dem_Cfg_GetSatelliteExtendedDataOfSatelliteInfo(SatelliteId))[MonitorId];
}
#endif

/* ****************************************************************************
 % Dem_SatelliteSat_SetSatelliteData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())                                                                         /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (MonitorId >= (Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId))) )
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    (Dem_Cfg_GetSatelliteDataOfSatelliteInfo(SatelliteId))[MonitorId] = NewSatelliteData;                                        /* SBSW_DEM_WRITE_SATELLITEINFO_SATELLITEDATA */
  }
}

/* ****************************************************************************
 % Dem_SatelliteSat_SetSatelliteExtendedData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  NewSatelliteExtendedData
  )
{
#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())                                                                         /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (MonitorId >= (Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId))) )
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    (Dem_Cfg_GetSatelliteExtendedDataOfSatelliteInfo(SatelliteId))[MonitorId] = NewSatelliteExtendedData;                        /* SBSW_DEM_WRITE_SATELLITEINFO_SATELLITE_EXTENDEDDATA */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MonitorId)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NewSatelliteExtendedData)                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_SatelliteSat_SyncSetSatelliteData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  )
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())                                                                         /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (MonitorId >= (Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId))) )
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = TRUE;
  }
  else
#endif
  {
    /* Swap the new data into the buffer if the buffer's value is identical to the old data.
     * Return whether operation succeeded. */
    lReturnValue = Dem_Com_SyncCompareAndSwap(&((Dem_Cfg_GetSatelliteDataOfSatelliteInfo(SatelliteId))[MonitorId].Raw),          /* SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP_SATELLITEDATA */
      OldSatelliteData.Raw, NewSatelliteData.Raw);
  }
  return lReturnValue;
}

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 % Dem_SatelliteSat_SyncSetSatelliteExtendedData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  OldSatelliteExtendedData,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  NewSatelliteExtendedData
  )
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (SatelliteId >= Dem_Cfg_GetSizeOfSatelliteInfo())                                                                         /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (MonitorId >= (Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId))) )
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    lReturnValue = TRUE;
  }
  else
#endif
  {
    /* Swap the new data into the buffer if the buffer's value is identical to the old data.
     * Return whether operation succeeded. */
    lReturnValue = Dem_Com_SyncCompareAndSwap(&((Dem_Cfg_GetSatelliteExtendedDataOfSatelliteInfo(SatelliteId))[MonitorId].Raw),  /* SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP_SATELLITE_EXTENDEDDATA */
                                                 OldSatelliteExtendedData.Raw, NewSatelliteExtendedData.Raw);
  }
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_SatelliteCore_SyncSetSatelliteData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_SyncSetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  )
{
  /* Behavior is identical for core and satellite --> use satellite method. */
  return Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, OldSatelliteData, NewSatelliteData);
}

/* ****************************************************************************
 % Dem_SatelliteSat_SetEventQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetEventQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_18.4 */
  do
  {
    lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lNewSatelliteInfo = Dem_SatelliteInfo_SetEventQueueUpdated(lOldSatelliteInfo);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);
}

/* ****************************************************************************
 % Dem_Satellite_TestSimilarConditionsChanged
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
Dem_Satellite_TestSimilarConditionsChanged(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  )
{
  boolean lReturnValue;
  lReturnValue = 
    (Dem_SatelliteData_TestSimilarConditionStatus(OldSatelliteData) != Dem_SatelliteData_TestSimilarConditionStatus(NewSatelliteData));
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Satellite_UpdateSimilarConditions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_UpdateSimilarConditions(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_EventStatusType, AUTOMATIC)         MonitorTrigger
  )
{
#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  if (MonitorTrigger >= DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED)
  {
    lNewSatelliteData = Dem_SatelliteData_ResetSimilarConditionStatus(OldSatelliteData);
  }
  else
  {
    lNewSatelliteData = Dem_SatelliteData_SetSimilarConditionStatus(OldSatelliteData);
  }

  if (Dem_Satellite_TestSimilarConditionsChanged(OldSatelliteData, lNewSatelliteData) == TRUE)
  {
    Dem_EventQueue_StatusType lOldQueueStatus;
    Dem_EventQueue_StatusType lNewQueueStatus;
    lOldQueueStatus = Dem_EventQueue_GetQueueStatus(lNewSatelliteData);
    lNewQueueStatus = Dem_EventQueue_SetSimilarConditionStatusChanged(lOldQueueStatus);
    lNewSatelliteData = Dem_EventQueue_GetResult(lNewQueueStatus, lNewSatelliteData);
  }

  return lNewSatelliteData;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MonitorTrigger);                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return OldSatelliteData;
#endif
}

/* ****************************************************************************
 % Dem_Satellite_UpdateSatelliteData
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
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_UpdateSatelliteData(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  )
{
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_EventQueue_StatusType lOldQueueStatus;
  Dem_EventQueue_StatusType lNewQueueStatus;
  Dem_MonitorStatusType lMonitorStatus;

  lNewSatelliteData = OldSatelliteData;
  lOldQueueStatus = Dem_EventQueue_GetQueueStatus(OldSatelliteData);
  lNewQueueStatus = Dem_EventQueue_CalculateQueueStatus(lOldQueueStatus, Dem_Debounce_GetMonitorTrigger(DebounceInfoPtr));       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lMonitorStatus = Dem_Monitor_GetMonitorStatus(OldSatelliteData);
  lMonitorStatus = Dem_Monitor_CalculateMonitorStatus(lMonitorStatus, Dem_Debounce_GetMonitorTrigger(DebounceInfoPtr));          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  if (Dem_Debounce_TestRequestFdcProcessing(DebounceInfoPtr) == TRUE)                                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  { /* update event entry with a new max value > pre-confirmation limit on task level */
    lNewQueueStatus = Dem_EventQueue_SetFdcProcessingStatus(lNewQueueStatus);
  }
  if (Dem_Debounce_TestFdcThresholdExceeded(DebounceInfoPtr) == TRUE)                                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    lNewQueueStatus = Dem_EventQueue_SetFdcTripStatus(lNewQueueStatus);
  }
  if (Dem_Debounce_TestMaximumFdcExceeded(DebounceInfoPtr) == TRUE)                                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    lNewQueueStatus = Dem_EventQueue_SetFdcMaxSLCStatus(lNewQueueStatus);
  }
  lNewSatelliteData = Dem_Debounce_GetDebouncingResult(DebounceInfoPtr, lNewSatelliteData);                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lNewSatelliteData = Dem_Monitor_SetMonitorStatus(lNewSatelliteData, lMonitorStatus);
  lNewSatelliteData = Dem_EventQueue_GetResult(lNewQueueStatus, lNewSatelliteData);

  return lNewSatelliteData;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Satellite_UpdateRatio
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_UpdateRatio(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
  Dem_RatioIdIndexType  lRatioIndex;
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
  lRatioIndex = Dem_Cfg_EventRatioIdIdx(EventId);

  if ( (lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)                                                                               /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_Cfg_ObdRatioIdType(lRatioIndex) == DEM_RATIO_OBSERVER)
    && (Dem_InitState_TestMasterAtLeastInState(DEM_INITSTATE_INITIALIZED) == TRUE)
    )
  {
    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */

    Dem_Esm_RatioQueueAsync(lRatioIndex);

    Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
#endif
}

/* ****************************************************************************
 % Dem_Satellite_TestQueueStatusUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_TestQueueStatusUpdated(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  )
{
  Dem_EventQueue_StatusType lOldQueueStatus;
  Dem_EventQueue_StatusType lNewQueueStatus;
  lOldQueueStatus = Dem_EventQueue_GetQueueStatus(OldSatelliteData);
  lNewQueueStatus = Dem_EventQueue_GetQueueStatus(NewSatelliteData);

  return (boolean)( (lOldQueueStatus == DEM_EVENTQUEUE_STATE_INITIAL)
                 && (lNewQueueStatus != DEM_EVENTQUEUE_STATE_INITIAL) );
}

/* ****************************************************************************
 % Dem_SatelliteSat_UpdateMonitorTrigger
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_SatelliteSat_UpdateMonitorTrigger(
  CONST(Dem_Satellite_IdType, AUTOMATIC)        SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC) MonitorId,
  CONST(Dem_EventStatusType, AUTOMATIC)         MonitorTrigger
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */

  lReturnValue = E_OK;
  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);

  /* Possible concurrent modification :
     ClearEvent
     ResetEventStatus
     Displacement
     Aging */

  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;
    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    Dem_Debounce_SetMonitorTrigger(lDebounceInfoPtr, MonitorTrigger);                                                            /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    if (Dem_Debounce_CalculateDebouncing(lDebounceInfoPtr) == TRUE)                                                              /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    {
      if(Dem_Cfg_EventObdRelated(lEventId) == TRUE)
      {
        lNewSatelliteData = Dem_Satellite_UpdateSimilarConditions(lNewSatelliteData, MonitorTrigger);
      }

      if ( (Dem_Debounce_TestDebouncingChanged(lDebounceInfoPtr) == TRUE)                                                        /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */ /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        || (Dem_Satellite_TestMonitorQualificationNeeded(lOldSatelliteData, lNewSatelliteData, lDebounceInfoPtr)  == TRUE) )     /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
      {
        boolean lOverflow;
        lOverflow = Dem_EventQueue_TestQueueOverflow(
          Dem_EventQueue_GetQueueStatus(lOldSatelliteData),
          Dem_Debounce_GetMonitorTrigger(lDebounceInfoPtr));                                                                     /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
        if (lOverflow == FALSE)
        {
          lReturnValue = E_OK;
          lNewSatelliteData = Dem_Satellite_UpdateSatelliteData(lNewSatelliteData, lDebounceInfoPtr);                            /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
        }
        else
        {
          /* Event update must be discarded due to queue overflow */
          lReturnValue = E_NOT_OK;
          break;                                                                                                                 /* PRQA S 0771 */ /* MD_DEM_14.6_err */
        }
      }

      if (Dem_Debounce_TestQualifiedResult(lDebounceInfoPtr) == TRUE)                                                            /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
      {
        Dem_Satellite_UpdateRatio(lEventId);
      }
    }
    else
    {
      lReturnValue = E_NOT_OK;
    }

  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);

  if (Dem_Debounce_TestMaximumFdcExceeded(lDebounceInfoPtr) == TRUE)                                                             /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
  {
    Dem_DebounceBaseSat_UpdateDebounceValueMax(lDebounceInfoPtr);                                                                /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
  }
  if (Dem_Satellite_TestQueueStatusUpdated(lOldSatelliteData, lNewSatelliteData) == TRUE)
  {
    Dem_SatelliteSat_SetEventQueueUpdated(SatelliteId);
  }

  /* Notify monitor status change */
  if (Dem_Monitor_GetMonitorStatus(lOldSatelliteData) != Dem_Monitor_GetMonitorStatus(lNewSatelliteData))
  {
    Dem_Notifications_MonitorStatusChanged(lEventId);
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 % Dem_SatelliteSat_ProcessTimeBasedDebouncing
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
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_ProcessTimeBasedDebouncing(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                             /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

  if (Dem_DebounceTimeBasedSat_IsTimerActive(lDebounceInfoPtr) == TRUE)                                                          /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
  {
    Dem_EventQueue_StatusType lOldQueueStatus;
    Dem_EventQueue_StatusType lNewQueueStatus;
    Dem_MonitorStatusType lMonitorStatus;
    boolean lQueueUpdated;

    do
    {
      lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
      lNewSatelliteData = lOldSatelliteData;
      lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                         /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

      lOldQueueStatus = Dem_EventQueue_GetQueueStatus(lOldSatelliteData);
      lMonitorStatus = Dem_Monitor_GetMonitorStatus(lOldSatelliteData);

      Dem_DebounceTimeBasedSat_ProcessDebounce(lDebounceInfoPtr);                                                                /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

      lMonitorStatus = Dem_Monitor_CalculateMonitorStatus(lMonitorStatus, Dem_Debounce_GetMonitorTrigger(lDebounceInfoPtr));     /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
      lNewQueueStatus = Dem_EventQueue_CalculateQueueStatus(lOldQueueStatus, Dem_Debounce_GetMonitorTrigger(lDebounceInfoPtr));  /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
      if (Dem_Debounce_TestRequestFdcProcessing(lDebounceInfoPtr) == TRUE)                                                       /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
      { /* update event entry with a new max value > pre-confirmation limit on task level */
        lNewQueueStatus = Dem_EventQueue_SetFdcProcessingStatus(lNewQueueStatus);
      }
      if (Dem_Debounce_TestFdcThresholdExceeded(lDebounceInfoPtr) == TRUE)                                                       /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
      {
        lNewQueueStatus = Dem_EventQueue_SetFdcTripStatus(lNewQueueStatus);
      }
      if (Dem_Debounce_TestMaximumFdcExceeded(lDebounceInfoPtr) == TRUE)                                                         /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
      {
        lNewQueueStatus = Dem_EventQueue_SetFdcMaxSLCStatus(lNewQueueStatus);
      }

      lNewSatelliteData = Dem_Debounce_GetDebouncingResult(lDebounceInfoPtr, lNewSatelliteData);                                 /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
      lNewSatelliteData = Dem_Monitor_SetMonitorStatus(lNewSatelliteData, lMonitorStatus);
      lNewSatelliteData = Dem_EventQueue_GetResult(lNewQueueStatus, lNewSatelliteData);

      lQueueUpdated = (boolean)((lOldQueueStatus == DEM_EVENTQUEUE_STATE_INITIAL)
        && (lNewQueueStatus != DEM_EVENTQUEUE_STATE_INITIAL));
    } while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);

    if (Dem_Debounce_TestMaximumFdcExceeded(lDebounceInfoPtr) == TRUE)                                                           /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    {
      Dem_DebounceBaseSat_UpdateDebounceValueMax(lDebounceInfoPtr);                                                              /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    }
    if (lQueueUpdated == TRUE)
    {
      Dem_SatelliteSat_SetEventQueueUpdated(SatelliteId);
    }
    /* Notify monitor status change */
    if (Dem_Monitor_GetMonitorStatus(lOldSatelliteData) != Dem_Monitor_GetMonitorStatus(lNewSatelliteData))
    {
      Dem_Notifications_MonitorStatusChanged(lEventId);
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_SatelliteSat_SetInitState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetInitState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
  )
{
  Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_18.4 */
  do
  {
    lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lNewSatelliteInfo = Dem_SatelliteInfo_SetInitStatus(lOldSatelliteInfo, InitState);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);
}

/* ****************************************************************************
 % Dem_Satellite_TestMonitorQualificationNeeded
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_TestMonitorQualificationNeeded(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData,
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  )
{
  Std_ReturnType lReturn;
  lReturn = FALSE;

  if (Dem_Cfg_EventDebounceContinuous(DebounceInfoPtr->EventId) == TRUE)
  {
    Dem_MonitorStatusType lMonitorStatus;
    lMonitorStatus = Dem_Monitor_GetMonitorStatus(OldSatelliteData);
    if (((Dem_Debounce_TestQualifiedResult(DebounceInfoPtr) == TRUE)                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */ /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_Monitor_TestMonitorStatusTNCTOC(lMonitorStatus) == TRUE))
      || ((Dem_Debounce_GetMonitorTrigger(DebounceInfoPtr) == DEM_EVENT_STATUS_FAILED)                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      && (Dem_Monitor_TestMonitorStatusTF(lMonitorStatus) == FALSE))
      || ((Dem_Debounce_GetMonitorTrigger(DebounceInfoPtr) == DEM_EVENT_STATUS_PASSED)                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      && (Dem_Monitor_TestMonitorStatusTF(lMonitorStatus) == TRUE)))
    {
      lReturn = TRUE;
    }
  }

  if ( (Dem_Satellite_TestSimilarConditionsChanged(OldSatelliteData, NewSatelliteData) == TRUE)                                  /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_Debounce_GetMonitorTrigger(DebounceInfoPtr) == DEM_EVENT_STATUS_PASSED)                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    && (Dem_Cfg_EventHealingTarget(DebounceInfoPtr->EventId) == 0) )
  {
    lReturn = TRUE;
  }

  return lReturn;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
/*!
 * \}
 */


/*!
 * \addtogroup Dem_Satellite_Public
 * \{
 */

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 % Dem_SatelliteSat_SetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetPrestoreQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_18.4 */
  do
  {
    lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lNewSatelliteInfo = Dem_SatelliteInfo_SetPrestoreQueueUpdated(lOldSatelliteInfo);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);
}
#endif

/* ****************************************************************************
 % Dem_SatelliteSat_FreezeDebounceStatus
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
Dem_SatelliteSat_FreezeDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;
    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    lNewSatelliteData = Dem_Debounce_FreezeDebouncing(lDebounceInfoPtr, lNewSatelliteData);                                      /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);
}

/* ****************************************************************************
 % Dem_SatelliteCore_FreezeDebounceStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteCore_FreezeDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteSat_FreezeDebounceStatus(SatelliteId, MonitorId);
}

/* ****************************************************************************
 % Dem_SatelliteSat_GetDebouncingState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_SatelliteSat_GetDebouncingState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lSatelliteData;                                                                                     /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  lSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lSatelliteData);                                /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

  return Dem_Debounce_GetDebouncingState(lDebounceInfoPtr);                                                                      /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
}

/* ****************************************************************************
 % Dem_SatelliteSat_ReportMonitorTrigger
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
Dem_SatelliteSat_ReportMonitorTrigger(
  CONST(Dem_EventIdType, AUTOMATIC)     EventId,
  CONST(Dem_EventStatusType, AUTOMATIC) MonitorTrigger
  )
{
  Std_ReturnType lReturnValue;

  if ( (Dem_OperationCycle_GetCurrentCycleStatus(Dem_Cfg_EventOperationCycle(EventId)) == DEM_OPERATIONCYCLE_CYCLE_STARTED)      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)
    && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE)
    )
  {
    lReturnValue =
        Dem_SatelliteSat_UpdateMonitorTrigger(
            Dem_Cfg_EventSatelliteId(EventId),
            Dem_Cfg_EventSatelliteEventId(EventId),
            MonitorTrigger);
  }
  else
  {
    lReturnValue = E_NOT_OK;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteSat_ResetEventStatus
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
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_SatelliteSat_ResetEventStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Std_ReturnType lReturnValue;

  lReturnValue = E_NOT_OK;
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  /* Confirmed (independent of qualification state) WWH OBD events with MIL can't
      reset their test failed bit as this will effect the activation mode */
  if ( (Dem_Event_TestMilSupport(EventId) == FALSE)                                                                               /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_UDSStatus_Test_CDTC(Dem_Event_GetUDSStatus(EventId)) == FALSE) )
#endif
  {
    if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE)
      && (Dem_UDSStatus_Test_TNCTOC(Dem_Event_GetUDSStatus(EventId)) == TRUE) )
    {
      Dem_Satellite_IdType lSatelliteId;
      Dem_EventIdType lMonitorId;
      boolean lProcessingDone;

      lSatelliteId = Dem_Cfg_EventSatelliteId(EventId);
      lMonitorId = Dem_Cfg_EventSatelliteEventId(EventId);
      do
      {
        Dem_SatelliteData_DataType lOldSatelliteData;                                                                            /* PRQA S 0759 */ /* MD_MSR_18.4 */
        Dem_SatelliteData_DataType lNewSatelliteData;                                                                            /* PRQA S 0759 */ /* MD_MSR_18.4 */
        Dem_EventQueue_StatusType lQueueStatus;

        lOldSatelliteData = Dem_Satellite_GetSatelliteData(lSatelliteId, lMonitorId);
        lNewSatelliteData = lOldSatelliteData;

        lQueueStatus = Dem_EventQueue_GetQueueStatus(lOldSatelliteData);
        if ( (lQueueStatus & DEM_EVENTQUEUE_SIMILAR_CONDITIONS_MASK) == DEM_EVENTQUEUE_STATE_INITIAL)
        {
          Dem_Debounce_InfoType lDebounceInfoData;                                                                               /* PRQA S 0759 */ /* MD_MSR_18.4 */
          Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;

          lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(EventId, &lDebounceInfoData, lOldSatelliteData);                      /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
          lNewSatelliteData = Dem_Debounce_ResetDebouncing(lDebounceInfoPtr, lNewSatelliteData);                                 /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

          lQueueStatus = Dem_EventQueue_SetResetTestFailedRequested(lQueueStatus);
          lNewSatelliteData = Dem_EventQueue_GetResult(lQueueStatus, lNewSatelliteData);
          lProcessingDone = Dem_SatelliteSat_SyncSetSatelliteData(lSatelliteId, lMonitorId, lOldSatelliteData, lNewSatelliteData);
          if (lProcessingDone == TRUE)
          {
            lReturnValue = E_OK;
            Dem_SatelliteSat_SetEventQueueUpdated(lSatelliteId);
          }
        }
        else
        {
          /* Event is already queued, so there was a qualified result. Technically, reseteventstatus is not
            * allowed to interrupt seteventstatus, so the queue status should not change in this loop - better be
            * paranoid though */
          lProcessingDone = TRUE;
        }
      }
      while (lProcessingDone == FALSE);
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 % Dem_SatelliteSat_UpdatePrestore
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
Dem_SatelliteSat_UpdatePrestore(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Prestore_QueueActionType, AUTOMATIC)  NewPrestoreAction
  )
{
  Dem_Satellite_IdType lSatelliteId;
  Dem_EventIdType lMonitorId;
  boolean lProcessingDone;
  
  lSatelliteId = Dem_Cfg_EventSatelliteId(EventId);
  lMonitorId = Dem_Cfg_EventSatelliteEventId(EventId);
  do
  {
    Dem_SatelliteData_ExtendedDataType lOldSatelliteExtendedData;                                                                /* PRQA S 0759 */ /* MD_MSR_18.4 */
    Dem_SatelliteData_ExtendedDataType lNewSatelliteExtendedData;                                                                /* PRQA S 0759 */ /* MD_MSR_18.4 */
    Dem_Prestore_QueueActionType       lOldPrestoreAction;

    lOldSatelliteExtendedData = Dem_Satellite_GetSatelliteExtendedData(lSatelliteId, lMonitorId);
    lOldPrestoreAction = Dem_SatelliteData_GetPrestoreActionsQueued(lOldSatelliteExtendedData);

    if (lOldPrestoreAction != NewPrestoreAction)
    {
      if (NewPrestoreAction == Dem_Prestore_PrestoreFF)
      {
        lNewSatelliteExtendedData = Dem_SatelliteData_QueuePrestoreFF(lOldSatelliteExtendedData);
      }
      else
      {
        lNewSatelliteExtendedData = Dem_SatelliteData_QueueClearPrestoredFF(lOldSatelliteExtendedData);
      }
      lProcessingDone = Dem_SatelliteSat_SyncSetSatelliteExtendedData(lSatelliteId, lMonitorId, lOldSatelliteExtendedData, lNewSatelliteExtendedData);
    }
    else
    {
      /* Prestorage of freeze frame is already queued */
      lProcessingDone = TRUE;
    }
  }
  while (lProcessingDone == FALSE);
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

/* ****************************************************************************
 % Dem_SatelliteSat_MainFunction
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
Dem_SatelliteSat_MainFunction(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
# if (DEM_CFG_SUPPORT_DEBOUNCE_TIME_HR == STD_ON)
  {
    Dem_Cfg_DebounceHiResIterType lIter;

    /* Process Time Based Debounce Events assigned to current satellite which use the high resolution timer */
    for (Dem_Cfg_DebounceHiResIterInit(SatelliteId, &lIter);                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_DebounceHiResIterExists(&lIter) == TRUE;                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_DebounceHiResIterNext(&lIter))                                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_SatelliteSat_ProcessTimeBasedDebouncing(SatelliteId,
                                                  Dem_Cfg_EventSatelliteEventId(Dem_Cfg_DebounceHiResIterGet(&lIter)));          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    }
  }
# endif /* ( DEM_CFG_SUPPORT_DEBOUNCE_TIME_HR == STD_ON ) */

# if (DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR == STD_ON)
  {
    uint8 lLoResTimer;
    lLoResTimer = *Dem_Cfg_GetDebounceLoResTimerOfSatelliteInfo(SatelliteId);

    lLoResTimer--;

    if (lLoResTimer == 0)
    {
      Dem_Cfg_DebounceLoResIterType lIter;

      /* Process Time Based Debounce Events assigned to current satellite which use the low resolution timer */
      for (Dem_Cfg_DebounceLoResIterInit(SatelliteId, &lIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_DebounceLoResIterExists(&lIter) == TRUE;                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_DebounceLoResIterNext(&lIter))                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_SatelliteSat_ProcessTimeBasedDebouncing(SatelliteId,
                                                    Dem_Cfg_EventSatelliteEventId(Dem_Cfg_DebounceLoResIterGet(&lIter)));        /* SBSW_DEM_CALL_ITERATOR_POINTER */
      }

      /* restart low resolution timer */
      lLoResTimer = Dem_Cfg_DebounceLoResTimerValue();
    }

    Dem_Satellite_SetDebounceLoResTimer(SatelliteId, lLoResTimer);
  }
# endif /* (DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR == STD_ON) */
#endif /* (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON) */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteSat_ResetDebounceStatus
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
Dem_SatelliteSat_ResetDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;
    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    lNewSatelliteData = Dem_Debounce_ResetDebouncing(lDebounceInfoPtr, lNewSatelliteData);                                       /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);
}


/* ****************************************************************************
 % Dem_SatelliteCore_ResetDebounceStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_ResetDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteSat_ResetDebounceStatus(SatelliteId, MonitorId);
}

/* ****************************************************************************
 % Dem_SatelliteCore_RestartEvent
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
Dem_SatelliteCore_RestartEvent(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;
  Dem_EventIdType lEventId;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;
    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    lNewSatelliteData = Dem_Debounce_ResetDebouncing(lDebounceInfoPtr, lNewSatelliteData);                                       /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    lNewSatelliteData = Dem_EventQueue_ResetQueueStatus(lNewSatelliteData);
    lNewSatelliteData = Dem_Monitor_ResetTNCTOC(lNewSatelliteData);
    lNewSatelliteData = Dem_SatelliteData_ResetSimilarConditionStatus(lNewSatelliteData);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);
  Dem_DebounceBaseCore_ResetDebounceValueMax(lDebounceInfoPtr);                                                                  /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

  /* Notify monitor status change */
  if (Dem_Monitor_GetMonitorStatus(lOldSatelliteData) != Dem_Monitor_GetMonitorStatus(lNewSatelliteData))
  {
    Dem_Notifications_MonitorStatusChanged(lEventId);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteCore_ClearEvent
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
Dem_SatelliteCore_ClearEvent(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;
  Dem_EventIdType lEventId;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;
    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    lNewSatelliteData = Dem_Debounce_ResetDebouncing(lDebounceInfoPtr, lNewSatelliteData);                                       /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    lNewSatelliteData = Dem_EventQueue_ResetQueueStatus(lNewSatelliteData);
    lNewSatelliteData = Dem_Monitor_ResetMonitorStatus(lNewSatelliteData);
    lNewSatelliteData = Dem_SatelliteData_ResetSimilarConditionStatus(lNewSatelliteData);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);
  Dem_DebounceBaseCore_ResetDebounceValueMax(lDebounceInfoPtr);                                                                  /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

  /* Notify monitor status change */
  if (Dem_Monitor_GetMonitorStatus(lOldSatelliteData) != Dem_Monitor_GetMonitorStatus(lNewSatelliteData))
  {
    Dem_Notifications_MonitorStatusChanged(lEventId);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteCore_TestAndClearEventQueueUpdated
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
Dem_SatelliteCore_TestAndClearEventQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_18.4 */
  do
  {
    lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lNewSatelliteInfo = Dem_SatelliteInfo_ResetEventQueueUpdated(lOldSatelliteInfo);
  }
  while (Dem_SatelliteCore_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);
  return Dem_SatelliteInfo_GetEventQueueUpdated(lOldSatelliteInfo);
}

/* ****************************************************************************
 % Dem_SatelliteCore_TestAndClearPrestoreQueueUpdated
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
Dem_SatelliteCore_TestAndClearPrestoreQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
  Dem_SatelliteInfo_Type lOldSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteInfo_Type lNewSatelliteInfo;                                                                                      /* PRQA S 0759 */ /* MD_MSR_18.4 */
  do
  {
    lOldSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lNewSatelliteInfo = Dem_SatelliteInfo_ResetPrestoreQueueUpdated(lOldSatelliteInfo);
  }
  while (Dem_SatelliteCore_SyncSetSatelliteInfo(SatelliteId, lOldSatelliteInfo, lNewSatelliteInfo) == FALSE);
  return Dem_SatelliteInfo_GetPrestoreQueueUpdated(lOldSatelliteInfo);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Satellite_PeekEventQueueStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_Satellite_PeekEventQueueStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  return Dem_EventQueue_GetQueueStatus(lOldSatelliteData);
}

/* ****************************************************************************
 % Dem_SatelliteCore_ConsumeEventQueueStatus
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
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteCore_ConsumeEventQueueStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = Dem_EventQueue_ResetQueueStatus(lOldSatelliteData);
  }
  while (Dem_SatelliteCore_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);
  return lOldSatelliteData;
}

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 % Dem_Satellite_PeekPrestoreActionQueue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Prestore_QueueActionType, DEM_CODE)
Dem_Satellite_PeekPrestoreActionQueue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_ExtendedDataType lOldSatelliteExtendedData;                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lOldSatelliteExtendedData = Dem_Satellite_GetSatelliteExtendedData(SatelliteId, MonitorId);
  return Dem_SatelliteData_GetPrestoreActionsQueued(lOldSatelliteExtendedData);
}
#endif

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 % Dem_Satellite_ConsumePrestoreActionQueue
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
DEM_LOCAL_INLINE FUNC(Dem_Prestore_QueueActionType, DEM_CODE)
Dem_Satellite_ConsumePrestoreActionQueue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_ExtendedDataType lOldSatelliteExtendedData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteData_ExtendedDataType lNewSatelliteExtendedData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  do
  {
    lOldSatelliteExtendedData = Dem_Satellite_GetSatelliteExtendedData(SatelliteId, MonitorId);
    lNewSatelliteExtendedData = Dem_SatelliteData_DequeuePrestoreActions(lOldSatelliteExtendedData);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteExtendedData(SatelliteId, MonitorId, lOldSatelliteExtendedData, lNewSatelliteExtendedData) == FALSE);
  return Dem_SatelliteData_GetPrestoreActionsQueued(lOldSatelliteExtendedData);
}
#endif


/* ****************************************************************************
 % Dem_SatelliteCore_MemoryInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_MemoryInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteInfo_Type lSatelliteInfo;                                                                                         /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lSatelliteInfo.Data.InitStatus = DEM_INITSTATE_UNINITIALIZED;
  Dem_SatelliteSat_SetSatelliteInfo(SatelliteId, lSatelliteInfo);
}

/* ****************************************************************************
 % Dem_SatelliteSat_PreInit
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
Dem_SatelliteSat_PreInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  {
    Dem_Satellite_MonitorIdType lMonitorId;
    Dem_SatelliteData_DataType lSatelliteData;                                                                                   /* PRQA S 0759 */ /* MD_MSR_18.4 */
    Dem_SatelliteData_ExtendedDataType lSatelliteExtendedData;                                                                   /* PRQA S 0759 */ /* MD_MSR_18.4 */

    lSatelliteData = Dem_SatelliteData_GetInitValue();
    lSatelliteExtendedData.Raw  = 0;

    for (lMonitorId = 0;
         lMonitorId < Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId);
         ++lMonitorId)
    {
      Dem_SatelliteSat_SetSatelliteData(SatelliteId, lMonitorId, lSatelliteData);
      Dem_SatelliteSat_SetSatelliteExtendedData(SatelliteId, lMonitorId, lSatelliteExtendedData);
      Dem_DebounceSat_PreInit(SatelliteId, lMonitorId);
    }
  }

#if (DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR == STD_ON)
  {
    Dem_Satellite_SetDebounceLoResTimer(SatelliteId, Dem_Cfg_DebounceLoResTimerValue());
  }
#endif

  {
    Dem_SatelliteInfo_Type lSatelliteInfo;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
    lSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
    lSatelliteInfo = Dem_SatelliteInfo_SetInitStatus(lSatelliteInfo, DEM_INITSTATE_PREINITIALIZED);
    Dem_SatelliteSat_SetSatelliteInfo(SatelliteId, lSatelliteInfo);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_SatelliteSat_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_Init(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteSat_SetInitState(SatelliteId, DEM_INITSTATE_INITIALIZED);
#if ((DEM_CFG_NOTIFY_MONITOR_STATUS_FIM == STD_ON) && (DEM_CFG_USE_MULTI_PARTITION_FIM == STD_ON))
  {
    Dem_Satellite_ApplicationType lSatelliteApplicationId;

    lSatelliteApplicationId = Dem_Satellite_GetApplicationId(SatelliteId);
    
    FiM_DemInitSatellite((ApplicationType)lSatelliteApplicationId);
  }
#endif
}

/* ****************************************************************************
 % Dem_Satellite_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Satellite_GetFaultDetectionCounter(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter                                                             /* PRQA S 3673 */ /* MD_DEM_16.7 */
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lSatelliteData;                                                                                     /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;
  Std_ReturnType lReturnValue;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  lSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lSatelliteData);                                /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
  lReturnValue = Dem_Debounce_GetFaultDetectionCounter(lDebounceInfoPtr, FaultDetectionCounter);                                 /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Satellite_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Satellite_GetMaxFaultDetectionCounter(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lSatelliteData;                                                                                     /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  lSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lSatelliteData);                                /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */
  return Dem_Debounce_GetMaxFaultDetectionCounter(lDebounceInfoPtr);                                                             /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
}

#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
/* ****************************************************************************
 % Dem_SatelliteCore_RestoreDebounceValue
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
Dem_SatelliteCore_RestoreDebounceValue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  )
{
  Dem_EventIdType lEventId;
  Dem_SatelliteData_DataType lOldSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_SatelliteData_DataType lNewSatelliteData;                                                                                  /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_Debounce_InfoType lDebounceInfoData;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  Dem_DebounceBase_InfoPtrType lDebounceInfoPtr;

  lEventId = Dem_Satellite_GetEventId(SatelliteId, MonitorId);
  do
  {
    lOldSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
    lNewSatelliteData = lOldSatelliteData;
    lDebounceInfoPtr = Dem_Debounce_DebounceInfoInit(lEventId, &lDebounceInfoData, lOldSatelliteData);                           /* SBSW_DEM_CALL_DEBOUNCEINFO_INIT */

    lNewSatelliteData = Dem_Debounce_RestoreDebounceValue(lDebounceInfoPtr, lNewSatelliteData, Value, ExpectedThreshold);        /* SBSW_DEM_CALL_DEBOUNCEINFO_POINTER */
    lNewSatelliteData = Dem_EventQueue_ResetQueueStatus(lNewSatelliteData);
  }
  while (Dem_SatelliteSat_SyncSetSatelliteData(SatelliteId, MonitorId, lOldSatelliteData, lNewSatelliteData) == FALSE);
}
#endif

/* ****************************************************************************
 % Dem_Satellite_GetDebounceValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Debounce_DataType, DEM_CODE)
Dem_Satellite_GetDebounceValue(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lSatelliteData;                                                                                     /* PRQA S 0759 */ /* MD_MSR_18.4 */

  lSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  return Dem_SatelliteData_GetDebounceData(lSatelliteData);
}

/* ****************************************************************************
 % Dem_Satellite_GetInitState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Satellite_GetInitState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  )
{
  Dem_SatelliteInfo_Type lSatelliteInfo;                                                                                         /* PRQA S 0759 */ /* MD_MSR_18.4 */

  lSatelliteInfo = Dem_Satellite_GetSatelliteInfo(SatelliteId);
  return Dem_SatelliteInfo_GetInitStatus(lSatelliteInfo);
}

/* ****************************************************************************
 % Dem_Satellite_GetMonitorStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Satellite_GetMonitorStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  )
{
  Dem_SatelliteData_DataType lSatelliteData;                                                                                     /* PRQA S 0759 */ /* MD_MSR_18.4 */

  lSatelliteData = Dem_Satellite_GetSatelliteData(SatelliteId, MonitorId);
  return Dem_Monitor_GetMonitorStatus(lSatelliteData);
}

/* ****************************************************************************
 % Dem_Satellite_GetCurrentSatelliteId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Satellite_IdType, DEM_CODE)
Dem_Satellite_GetCurrentSatelliteId(
  void
  )
{
  Dem_Satellite_IdType lSatelliteId;
#if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  {
    ApplicationType lCurrentApplication;
    lCurrentApplication = GetCurrentApplicationID();

    for (lSatelliteId = 0;
         lSatelliteId < Dem_Cfg_GlobalSatelliteCount();
         ++lSatelliteId)
    {
      if (Dem_Satellite_GetApplicationId(lSatelliteId) == lCurrentApplication)
      {
        break;
      }
    }
    Dem_Internal_AssertReturnValue(lSatelliteId  < Dem_Cfg_GlobalSatelliteCount(), DEM_E_INCONSISTENT_STATE, DEM_SATELLITE_APPLICATION_ZERO)
  }

#else
  lSatelliteId = DEM_SATELLITE_APPLICATION_ZERO;
#endif
  return lSatelliteId;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_SATELLITE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Satellite_Implementation.h
 *********************************************************************************************************************/
