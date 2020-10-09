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
/*! \addtogroup Dem_DTC
 *  \{
 *  \file       Dem_DTC_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of DTC subcomponent
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

#if !defined (DEM_DTC_IMPLEMENTATION_H)
#define DEM_DTC_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTC_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
/*Interface includes to avoid circular dependencies*/
#include "Dem_Event_Interface.h"
#include "Dem_OperationCycle_Interface.h"
#include "Dem_Satellite_Interface.h"
#include "Dem_ClearTask_Interface.h"
#include "Dem_Memory_Interface.h"

#include "Dem_DTCInternalStatus_Implementation.h"
#include "Dem_UDSStatus_Implementation.h"
#include "Dem_EventInternalStatus_Implementation.h"
#include "Dem_InitState_Implementation.h"
#include "Dem_StorageCondition_Implementation.h"
#include "Dem_EnableCondition_Implementation.h"
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_Nvm_Implementation.h"
#include "Dem_Prestore_Implementation.h"
#include "Dem_DebounceBase_Implementation.h"
#include "Dem_DtrIF_Implementation.h"
#include "Dem_Notifications_Implementation.h"
#include "Dem_Mem_Implementation.h"
#include "Dem_MemObdFreezeFrame_Implementation.h"
                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

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
 * \addtogroup Dem_DTC_Properties
 * \{
 */
/* ****************************************************************************
 % Dem_DTC_GetInternalStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTC_GetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_InternalStatusType lInternalStatus;
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);
  }
  else
#endif
  {
    lInternalStatus = Dem_Event_GetInternalStatus(EventId);
  }
  return lInternalStatus;
}

/* ****************************************************************************
 % Dem_DTC_SetInternalStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, InternalStatus);
  }
  else
#endif
  {
    Dem_Event_SetInternalStatus(EventId, InternalStatus);
  }
}

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_DTC_SetQualifyStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetQualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Status
  )
{
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_Cfg_CombinedGroupIterType lCombinedIter;
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      /* Ignore event availability to prevent inconsistent qualification states later on */
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Event_SetQualifyStatus(lSubEventId, Status);
    }
  }
  else
# endif
  {
    Dem_Event_SetQualifyStatus(EventId, Status);
  }
}
#endif


#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_DTC_SetAgedCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC) AgedCounter
  )
{
  uint16 lAgedCounterIndex;
  lAgedCounterIndex = Dem_Cfg_GetAgedCounterIndexOfEventTable(EventId);

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lAgedCounterIndex >= DEM_CFG_MAX_NUMBER_AGED_DTCS)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetAgingData().AgedCounter[lAgedCounterIndex] = AgedCounter;                                                         /* SBSW_DEM_ARRAY_WRITE_AGINGDATA_AGEDCOUNTER */
  }
} 
#endif

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_DTC_GetAgedCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint16 lAgedCounterIndex;

  lAgedCounterIndex = Dem_Cfg_GetAgedCounterIndexOfEventTable(EventId);
  return Dem_Cfg_GetAgingData().AgedCounter[lAgedCounterIndex];
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
 * \addtogroup Dem_DTC_Private
 * \{
 */

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_GetCombinedGroupUDSStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTC_GetCombinedGroupUDSStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId
  )
{
  return Dem_Cfg_GetCombinedGroupStatus(GroupId);
}
#endif

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_SetCombinedGroupUDSStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_SetCombinedGroupUDSStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId,
  CONST(uint8, AUTOMATIC)  Status
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (GroupId >= Dem_Cfg_GetSizeOfCombinedGroupStatus())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetCombinedGroupStatus(GroupId, Status);                                                                             /* SBSW_DEM_ARRAY_WRITE_COMBINEDGROUPSTATUS */
  }
}
#endif

#if ((DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON) || (DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON))
/* ****************************************************************************
 % Dem_DTC_TestStatusForAgingCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
  Dem_DTC_TestStatusForAgingCycle(
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DTCStatus
  )
{
  return (boolean)(                                                                                                              /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
# if (DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON)
    (Dem_UDSStatus_Test_TFTOC(DTCStatus) == FALSE)
    &&
# endif
    (Dem_UDSStatus_Test_TNCTOC(DTCStatus) == FALSE));
}
#endif


/* ****************************************************************************
 % Dem_DTC_TestGroupAvailable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupAvailable(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) && (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
  lReturnValue = (boolean)(Dem_EventInternalStatus_TestEventDisconnected(Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(GroupId)) == FALSE);
#else
  lReturnValue = TRUE;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_TestGroupAvailableInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupAvailableInVariant(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_EventInternalStatus_TestAvailableInVariant(Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(GroupId));
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_TestGroupSuppression
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestGroupSuppression(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) && (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
  lReturnValue = Dem_DTCInternalStatus_TestDtcSuppressed(Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(GroupId));
#else
  lReturnValue = FALSE;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_ApplyUserControlledWIR
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_ApplyUserControlledWIR(
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus,
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(InternalStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
  return ((Dem_DTC_UDSStatusType)((DtcStatus) | ((InternalStatus) & DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR)));
#else
  return DtcStatus;
#endif
}

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CombinedGroupGetFDC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_CombinedGroupGetFDC(
CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId,                                                                       /* PRQA S 3206 */ /* MD_DEM_3206 */
CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
)
{
  Std_ReturnType lReturnValue;
  sint8 lMaxFdc;
  Dem_Cfg_CombinedGroupIterType lCombinedIter;

  /* In rare cases GroupId is not required */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

    lReturnValue = E_OK;
  lMaxFdc = -128;

  for (Dem_Cfg_CombinedGroupIterInit(GroupId, &lCombinedIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lSubEventId;
    lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */

    if ((Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)                                                                   /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE))
    {
      sint8 lFdc;
      lReturnValue = Dem_GetFaultDetectionCounter(lSubEventId, &lFdc);                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
      if ((lReturnValue == E_OK) && (lMaxFdc < lFdc))
      {
        lMaxFdc = lFdc;
      }
    }
    if (lReturnValue != E_OK)
    {
      break;
    }
  }

  if (lReturnValue == E_OK)
  {
    *FaultDetectionCounter = lMaxFdc;                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( ((DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON) || (DEM_FEATURE_NEED_AGING_TRIGGER_PASSED == STD_ON)) \
    && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) )
/* ****************************************************************************
 % Dem_DTC_TestDtcMayAge
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcMayAge(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  lReturnValue = TRUE;                                                                                                           /* PRQA S 3198 */ /* MD_DEM_3198_na */

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if ((DEM_FEATURE_NEED_HEALING == STD_ON) && (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON))
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  {
    Dem_Cfg_CombinedGroupIndexType lGroupId;
    lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      Dem_Cfg_CombinedGroupIterType lGroupIter;
      for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lGroupIter);                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterExists(&lGroupIter) == TRUE;                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterNext(&lGroupIter))                                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_EventIdType lSubEvent;
        lSubEvent = Dem_Cfg_CombinedGroupIterGet(&lGroupIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
        if (Dem_Event_TestEventMayAge(lSubEvent, Dem_Event_GetUDSStatus(lSubEvent)) == FALSE)
        {
          break;
        }
      }
      lReturnValue = !(Dem_Cfg_CombinedGroupIterExists(&lGroupIter));                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    }
    else
    {
      lReturnValue = Dem_Event_TestEventMayAge(EventId, Dem_Event_GetUDSStatus(EventId));
    }
  }
#  elif (DEM_FEATURE_NEED_AGING_TRIGGER_PASSED == STD_ON)
  lReturnValue = Dem_Event_TestEventMayAge(EventId, Dem_Event_GetUDSStatus(EventId));  
#  endif
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Disconnect_Combined
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
Dem_DTC_Disconnect_Combined(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  Dem_DTC_InternalStatusType lGroupInternalStatus;

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  lGroupInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);

  /* Remove pending actions: time debouncing, FDC triggers and queue state  */
  Dem_SatelliteCore_ClearEvent(
    Dem_Cfg_EventSatelliteId(EventId),
    Dem_Cfg_EventSatelliteEventId(EventId));

  if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
  {
    Dem_Event_SetExtendedStatus(EventId, 
      Dem_EventInternalStatus_ResetSimilarConditions(
      Dem_Event_GetExtendedStatus(EventId)
      )
      );
  }
  Dem_Event_SetUDSStatus(EventId, 0x00U);

  if (Dem_EventInternalStatus_TestEventDisconnected(lGroupInternalStatus) == FALSE)
  { /* If all Events belonging to a DTC are disconnected, that DTC is disconnected as well */
    /* If all connected events are suppressed or disconnected, the DTC is suppressed as well */
    uint8 lCombinedGroupStatus;
    boolean lDoDisconnect;
    Dem_Cfg_CombinedGroupIterType lCombinedIter;

    lCombinedGroupStatus = 0x00;
    lDoDisconnect = TRUE;

    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
      {
        Dem_Event_InternalStatusType lInternalStatus;
        lInternalStatus = Dem_Event_GetInternalStatus(lSubEventId);

        /* If all events are disconnected now, the combined group is set to disconnected */
        lDoDisconnect = (boolean)(lDoDisconnect && (Dem_EventInternalStatus_TestEventDisconnected(lInternalStatus) == TRUE));    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */

        lCombinedGroupStatus = (uint8)(lCombinedGroupStatus | Dem_Event_GetUDSStatus(lSubEventId));
      }
    }
    if (lDoDisconnect == TRUE)
    {
      lGroupInternalStatus = Dem_EventInternalStatus_SetEventDisconnected(lGroupInternalStatus);
    }
# if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
    /* If all combined events are tested this cycle and no one is currently test failed */
    if ( (Dem_Cfg_EventReadinessGroup(EventId) != DEM_CFG_READINESS_NONE)                                                        /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_UDSStatus_Test_TF(lCombinedGroupStatus) == FALSE)
      && (Dem_UDSStatus_Test_TNCTOC(lCombinedGroupStatus) == FALSE)
      )
    {
      for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_EventIdType lSubEventId;
        lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
        /* If event is available */
        if (Dem_Event_TestEventUnavailable(lSubEventId) == FALSE)
        {
          Dem_DTC_ExtendedStatusType lExtendedStatus;
          lExtendedStatus = Dem_Event_GetExtendedStatus(lSubEventId);
          lExtendedStatus = Dem_DTCInternalStatus_SetExtendedStatus_TPSLC(lExtendedStatus);
          Dem_Event_SetExtendedStatus(lSubEventId, lExtendedStatus);
        }
      }
    }
# endif
    Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lGroupInternalStatus);
    Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, lCombinedGroupStatus);
  }
}                                                                                                                                /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Reconnect_Combined
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
Dem_DTC_Reconnect_Combined(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  Dem_DTC_InternalStatusType lGroupInternalStatus;

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  lGroupInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);

  Dem_Event_SetUDSStatus(EventId, 0x50U);

  if (Dem_EventInternalStatus_TestEventDisconnected(lGroupInternalStatus) == TRUE)
  {
    uint8 lCombinedGroupStatus;
    Dem_Cfg_CombinedGroupIterType lCombinedIter;

    lCombinedGroupStatus = 0x00;

    /* Reconnecting an event can cause a suppressed DTC to become un-suppressed */
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
      {
        /* Calculate the combined event status - logical 'or' of all connected event status bytes (includes self) */
        lCombinedGroupStatus = (uint8)(lCombinedGroupStatus | Dem_Event_GetUDSStatus(lSubEventId));
      }
    }

    /* Since at least one sub-events is connected now, set the combined group to connected */
    lGroupInternalStatus = Dem_EventInternalStatus_ResetEventDisconnected(lGroupInternalStatus);

    Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lGroupInternalStatus);
    Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, lCombinedGroupStatus);
  }
  else
  {
    Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, Dem_DTC_CalculateCombineGroupUdsStatus(lGroupId));
  }


}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 % Dem_DTC_AgingStartZeroTarget
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
Dem_DTC_AgingStartZeroTarget(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  Dem_DTC_InternalStatusType lInternalStatus;

  lInternalStatus = Dem_DTC_GetInternalStatus(EventId);
  if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) < Dem_DTCInternalStatus_StoredStatus_Aging)                         /* PRQA S 3415 */ /* MD_DEM_12.4_cf */ 
  {
    if (Dem_Cfg_EventSupportAging(EventId) == TRUE)
    {
      Dem_Cfg_MemoryIndexType  lMemoryIndex;

# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
      Dem_DTC_ClearOBDFreezeFrame(EventId);
# endif

      lMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;

      if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_Active)
      {
        lMemoryIndex = Dem_Memory_FindIndex_Checked(EventId);
      }
      Dem_DTC_Aged(EventId, lMemoryIndex);
    }
  }
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */
#endif /* DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF */

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 % Dem_DTC_AgingStartMultiTarget
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_AgingStartMultiTarget(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  if (Dem_DTC_GetAgingStatus(EventId) == Dem_DTC_AgingStatusNone)
  {
    /* Age all events, irrespective of the memory entry */
    Dem_DTC_StartAgingWithoutMemoryEntryMultiTarget(EventId);
  }
# else
  {
    Dem_DTC_InternalStatusType lInternalStatus;
    lInternalStatus = Dem_DTC_GetInternalStatus(EventId);

    if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) < Dem_DTCInternalStatus_StoredStatus_Aging)
    {
      /* Age only events with memory entry */
      Dem_DTC_StartAgingWithMemoryEntryMultiTarget(EventId);
    }
  }
# endif
}                                                                                                                               
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Aging_Vcc
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
Dem_DTC_Aging_Vcc(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  if (Dem_Cfg_EventSupportAging(EventId) == TRUE)
  {
    uint8 lEventStatus;
    Dem_DTC_InternalStatusType lInternalStatus;

    lEventStatus = Dem_Event_GetUDSStatus(EventId);
    lInternalStatus = Dem_Event_GetInternalStatus(EventId);

    if ( (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) != Dem_DTCInternalStatus_StoredStatus_None)                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_UDSStatus_Test_TF(lEventStatus) == FALSE) )
    { /* Stored, not active event */
      Dem_Cfg_MemoryIndexType lMemoryIndex;
      Dem_MemoryEntry_HandleType lMemoryEntryId;
      Dem_UdsStatusByteType lOldEventStatus;
      Dem_UdsStatusByteType lOldExternalEventStatus;
      Dem_DTC_UDSStatusType lPreconfirmedStatus;

      lMemoryIndex = Dem_Memory_FindIndex_Checked(EventId);
      lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

      /* Update UDS status byte */
      /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */

      lEventStatus = Dem_Event_GetUDSStatus(EventId);
      lOldEventStatus = lEventStatus;
      lOldExternalEventStatus = Dem_Event_GetExternalUDSStatus(EventId, lOldEventStatus);

      lEventStatus = Dem_UDSStatus_Reset_CDTC(lEventStatus);

      Dem_Event_SetUDSStatus(EventId, lEventStatus);

      /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
      Dem_LeaveCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */

      if (Dem_UDSStatus_IsNvRelevantStatusChange(lOldEventStatus, lEventStatus) == TRUE)
      {
        Dem_Nvm_SetStatusBlockChanged();
      }

      /* Update SI.30 status byte */
      lPreconfirmedStatus = Dem_MemoryEntry_GetPreConfirmedStatus(lMemoryEntryId);
      lPreconfirmedStatus = DEM_DTC_SET_PC_STATUS_ADTC(lPreconfirmedStatus);
      lPreconfirmedStatus = DEM_DTC_RESET_PC_STATUS_TFSLC(lPreconfirmedStatus);
      Dem_MemoryEntry_SetPreConfirmedStatus(lMemoryEntryId, lPreconfirmedStatus);

      Dem_Notifications_EventStatusChanged(EventId, 
                                           lOldExternalEventStatus, 
                                           Dem_Event_GetExternalUDSStatus(EventId, lEventStatus));
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 % Dem_DTC_AgingStartVCC
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
Dem_DTC_AgingStartVCC(
CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
)
{
  Dem_DTC_InternalStatusType lInternalStatus;

  lInternalStatus = Dem_Event_GetInternalStatus(DTCContext->EventId);
  if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) != Dem_DTCInternalStatus_StoredStatus_None)
  {
    boolean lIsModified;
    Dem_DTC_UDSStatusType lOldPreconfirmedStatus;
    Dem_DTC_UDSStatusType lNewPreconfirmedStatus;
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_MemoryEntry_HandleType lMemoryEntryId;

    lMemoryIndex = Dem_Memory_FindIndex_Checked(DTCContext->EventId);
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

    lOldPreconfirmedStatus = Dem_MemoryEntry_GetPreConfirmedStatus(lMemoryEntryId);
    lNewPreconfirmedStatus = DEM_DTC_RESET_PC_STATUS_UDTC(lOldPreconfirmedStatus);
    Dem_MemoryEntry_SetPreConfirmedStatus(lMemoryEntryId, lNewPreconfirmedStatus);

    lIsModified = (boolean)(lOldPreconfirmedStatus != lNewPreconfirmedStatus);

    if ( (DEM_DTC_TEST_PC_STATUS_UDTCTOC(lOldPreconfirmedStatus) == FALSE)
      && ((DTCContext->DtcEffects & DEM_CFG_TRIGGER_FIRSTTHISCYCLE) != FALSE) )
    { /* OCC2 if preconfirmed level had not been reached */
      if (Dem_MemoryEntry_GetOccurrenceCounter2(lMemoryEntryId) < 0xffU)
      {
        Dem_MemoryEntry_SetOccurrenceCounter2(lMemoryEntryId, Dem_MemoryEntry_GetOccurrenceCounter2(lMemoryEntryId) + 1);
        lIsModified = TRUE;
      }

      /* OCC7 once per cycle, and also consider FDC preconfirmed */
      if (Dem_MemoryEntry_GetOccurrenceCounter7(lMemoryEntryId) < 0xffU)
      {
        Dem_MemoryEntry_SetOccurrenceCounter7(lMemoryEntryId, Dem_MemoryEntry_GetOccurrenceCounter7(lMemoryEntryId) + 1);
        lIsModified = TRUE;
      }

      /* VCC start aging at event passed */
      if (Dem_MemoryEntry_GetOccurrenceCounter2(lMemoryEntryId) == Dem_Cfg_EventAgingTarget(DTCContext->EventId))
      {
        Dem_DTC_Aging_Vcc(DTCContext->EventId);
        lIsModified = TRUE;
      }
    }

    if (lIsModified == TRUE)
    {
      Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* defined DEM_ORGANI_OEM_VCC_SUPPORT_COMMENT */

/* ****************************************************************************
 % Dem_DTC_Cleared_Internal
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
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_Cleared_Internal(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
#endif

  {
    Dem_DTC_InternalStatusType lInternalStatus;
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);
    }
    else
#endif
    {
      lInternalStatus = Dem_Event_GetInternalStatus(EventId);
    }

    if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) != Dem_DTCInternalStatus_StoredStatus_None)
    {
      Dem_Cfg_MemoryIndexType lMemoryIndex;
      lMemoryIndex = Dem_Memory_FindIndex_Checked(EventId);
      /* Remove the event from the memory */
      Dem_Memory_FreeEvent(lMemoryIndex, EventId);
      Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYCLEAREDIMMEDIATE);
    }

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */

      Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_None));

      Dem_LeaveCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */
      /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

    }
#endif
  }

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
  { /* Clear the OBD FreezeFrame (if available) */
    uint8 lSelectedIndex;

    lSelectedIndex = Dem_Mem_FreezeFrameFindIndex(EventId);

    if (lSelectedIndex != Dem_Cfg_GlobalObdIIFFCount())
    { /* No need to clear the complete FreezeFrame entry as it is only valid if the EventId is valid */
      Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(lSelectedIndex);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_OBDFREEZEFRAME), 
                                  DEM_NVM_BLOCKSTATE_DIRTYCLEAREDIMMEDIATE);

      /* if this event is visible in Mode02, clear this cache also */
      if (Dem_Mem_FreezeFrameIndexMode02 == lSelectedIndex)
      {
        Dem_Mem_FreezeFrameIndexMode02 = Dem_Cfg_GlobalObdIIFFCount();
      }
    }
  }
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  { /* Test and invalidate the aging counter */
    Dem_DTC_TestAndInvalidateAgingCounter(EventId);
  }
#endif

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
    Dem_DTC_ResetAgedCounter(EventId);
#endif

  {
    Dem_DTC_ForEachCombinedArgType lArgs;
    Dem_DTC_UDSStatusType lOldDtcStatus;

    lOldDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));
    Dem_DTC_ForEachCombinedEvent(EventId, Dem_Event_Cleared, &lArgs);                                                            /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    if (Dem_Event_TestMilSupport(EventId) == TRUE)
    {
      Dem_Data_PermanentEntryClear(EventId, TRUE);

      /*CDTC bit could be reset already*/
      if ( (Dem_UDSStatus_Test_CDTC(lArgs.Common.OldDtcStatus) == TRUE)                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_UDSStatus_Test_CDTC(lArgs.Common.NewDtcStatus) == FALSE) )
      {
        Dem_Memory_ConfirmedChronoFreeEvent(EventId);
      }
    }
#endif
    Dem_Notifications_DtcStatusChanged(EventId, 
                                       lOldDtcStatus, 
                                       DEM_UDS_STATUS_INITIALIZE, 
                                       DEM_NOTIFICATIONS_DTC_CLEAR);
  }
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Passed_ProcessDTCEffects_TPSLC
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
Dem_DTC_Passed_ProcessDTCEffects_TPSLC(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC)  DTCContext
)
{
  /* If event combination is supported and event is in a combined group */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    /* If all combined events are tested this cycle and no one is currently test failed */
    if ((Dem_UDSStatus_Test_TF(DTCContext->NewDtcStatus) == FALSE)                                                               /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_UDSStatus_Test_TNCTOC(DTCContext->NewDtcStatus) == FALSE)
      )
    {
      Dem_DTC_ExtendedStatusType lExtendedStatus;
      lExtendedStatus= Dem_Event_GetExtendedStatus(DTCContext->EventId);
      /* If TestPassedSinceLastClear is not set already */
      if (Dem_DTCInternalStatus_TestExtendedStatus_TPSLC(lExtendedStatus) == FALSE)
      {
        Dem_Cfg_CombinedGroupIterType lCombinedIter;

        /* Set all events of combined group to TestPassedSinceLastClear */
        for (Dem_Cfg_CombinedGroupIterInit(DTCContext->GroupId, &lCombinedIter);                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          Dem_EventIdType lSubEventId;
          lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
          /* If event is available */
          if (Dem_Event_TestEventUnavailable(lSubEventId) == FALSE)
          {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
            Dem_EnterCritical_DiagMonitor();                                                                                     /* PRQA S 3109 */ /* MD_MSR_14.3 */
            lExtendedStatus = Dem_Event_GetExtendedStatus(lSubEventId);
            lExtendedStatus = Dem_DTCInternalStatus_SetExtendedStatus_TPSLC(lExtendedStatus);
            Dem_Event_SetExtendedStatus(lSubEventId, lExtendedStatus);

            Dem_LeaveCritical_DiagMonitor();                                                                                     /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
          }
        }

        /* Check if monitor is complete for event readiness group */
        Dem_Data_Calc_Pid01_MonitorCompleted((Dem_Cfg_EventReadinessGroup(DTCContext->EventId)));
      }
    }
  }
  else
# endif
  {
    /* Otherwise*/
    Dem_DTC_ExtendedStatusType lExtendedStatus;
    lExtendedStatus = Dem_Event_GetExtendedStatus(DTCContext->EventId);
    if (Dem_DTCInternalStatus_TestExtendedStatus_TPSLC(lExtendedStatus) == FALSE)
    {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */

      /* Set extended status of event to TestPassedSinceLastClear */
      lExtendedStatus = Dem_Event_GetExtendedStatus(DTCContext->EventId);
      lExtendedStatus = Dem_DTCInternalStatus_SetExtendedStatus_TPSLC(lExtendedStatus);
      Dem_Event_SetExtendedStatus(DTCContext->EventId, lExtendedStatus);

      Dem_LeaveCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

      /* Check if monitor is complete for event readiness group */
      Dem_Data_Calc_Pid01_MonitorCompleted(Dem_Cfg_EventReadinessGroup(DTCContext->EventId));
    }
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

/* ****************************************************************************
 % Dem_DTC_ForEachCombinedEvent
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
Dem_DTC_ForEachCombinedEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Util_ForEachCombinedFuncType, AUTOMATIC)  FuncPtr,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  )
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    /* DTC has combined group */

    Dem_DTC_UDSStatusType lDtcStatus;
    Dem_Cfg_CombinedGroupIterType lCombinedIter;
    Dem_EventIdType lSubEventId;

    lDtcStatus = 0; /* neutral value */
    ArgPtr->Common.OldDtcStatus = Dem_DTC_GetCombinedGroupUDSStatus(lGroupId);                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

    /* Iterate through all active sub-events */
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */

      if ( (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)                                                                /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE) )
      {
        (*FuncPtr)(lSubEventId, ArgPtr);                                                                                         /* SBSW_DEM_CALL_FOREACH_FUNCPTR */
        /* Combined event status created by ORing the status bits or all sub-events */
        lDtcStatus = (Dem_DTC_UDSStatusType)(lDtcStatus | Dem_Event_GetUDSStatus(lSubEventId));
      }
    }
    Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, lDtcStatus);

    ArgPtr->Common.NewDtcStatus = lDtcStatus;                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  else
#endif
  {
    /* EventId is not a combined event */

    ArgPtr->Common.OldDtcStatus = Dem_Event_GetUDSStatus(EventId);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    (*FuncPtr)(EventId, ArgPtr);                                                                                                 /* SBSW_DEM_CALL_FOREACH_FUNCPTR */
    ArgPtr->Common.NewDtcStatus = Dem_Event_GetUDSStatus(EventId);                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_InitGroupInternalStatus
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
Dem_DTC_InitGroupInternalStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
# if (DEM_FEATURE_NEED_EVENTAVAILABLE_DEFAULT == STD_ON)
  Dem_Cfg_CombinedGroupIterType lSubEventIter;
  Dem_Event_InternalStatusType lInternalStatus;

  lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(GroupId);
  lInternalStatus = Dem_EventInternalStatus_SetEventDisconnected(lInternalStatus);

  for (Dem_Cfg_CombinedGroupIterInit(GroupId, &lSubEventIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterExists(&lSubEventIter) == TRUE;                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterNext(&lSubEventIter))                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    if (Dem_Cfg_EventAvailableByDefault(Dem_Cfg_CombinedGroupIterGet(&lSubEventIter)) == TRUE)                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      lInternalStatus = Dem_EventInternalStatus_ResetEventDisconnected(lInternalStatus);
      break;
    }
  }
  Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(GroupId, lInternalStatus);
# endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CycleQualifyDcy_AllDtc
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy_AllDtc(
  void
  )
{
  Dem_EventIdType lEventId;

  for (lEventId = Dem_Cfg_GlobalPrimaryFirst(); lEventId <= Dem_Cfg_GlobalPrimaryLast(); lEventId++)
  {
    uint8 lOldDtcStatus;
    Dem_DTC_ForEachCombinedArgType lArgs;

    /* Skip non OBD Events */
    if (Dem_Cfg_EventObdRelated(lEventId) == FALSE)
    {
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    /* Only process master events (subevents are handled with the master) */
    if (lEventId != Dem_Cfg_GetMasterEvent(lEventId))
    {
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }
# endif

    lOldDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(lEventId, Dem_DTC_GetDTCStatus(lEventId));

    /* Process the DTC status qualification of the stored event or combination group */
    Dem_DTC_ForEachCombinedEvent(lEventId, Dem_Event_CycleQualifyDcy, &lArgs);                                                   /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */

    lArgs.Common.NewDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(lEventId, lArgs.Common.NewDtcStatus);
# if (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
    if ((Dem_UDSStatus_Test_CDTC(lOldDtcStatus) == FALSE)                                                                        /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_UDSStatus_Test_CDTC(lArgs.Common.NewDtcStatus) == TRUE))
    {
      Dem_MemObdFreezeFrame_SetFFOfEventVisible(lEventId);
      Dem_Mem_FreezeFrameIndexMode02 = Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame();
    }
#endif
    Dem_Notifications_DtcStatusChanged(lEventId, 
                                       lOldDtcStatus, 
                                       lArgs.Common.NewDtcStatus, 
                                       DEM_NOTIFICATIONS_CYCLE_QUALIFIED);
    if (Dem_UDSStatus_Test_CDTC((uint8)(lOldDtcStatus ^ lArgs.Common.NewDtcStatus)) == TRUE)
    {
      Dem_Notifications_EventDataChanged(lEventId);
    }
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_STATUS), 
                                DEM_NVM_BLOCKSTATE_DIRTY);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF)
/* ****************************************************************************
 % Dem_DTC_CycleQualifyDcy_StoredOnly
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
Dem_DTC_CycleQualifyDcy_StoredOnly(
  void
  )
{
  Dem_Memory_AllocMemEntriesIterType lStoredEventsIter;

  for (Dem_Memory_AllocMemEntriesChrono_IterInit(DEM_CFG_MEMORYID_PRIMARY, &lStoredEventsIter);                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllocMemEntriesChrono_IterExists(&lStoredEventsIter) == TRUE;                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Memory_AllocMemEntriesChrono_IterNext(&lStoredEventsIter))                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_MemoryEntry_HandleType lMemoryEntryId;
    Dem_EventIdType lEventId;
    uint8 lEventQualifyStatus;
    uint8 lEntryQualifyStatus;
    uint8 lOldDtcStatus;
    Dem_DTC_ForEachCombinedArgType lArgs;

    lMemoryIndex = Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(&lStoredEventsIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
    lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
    if (Dem_Event_TestValidHandle(lEventId) == FALSE)
    {
      Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                          /* SBSW_DEM_POINTER_RUNTIME_CHECK */
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }
# endif
    /* Skip non OBD Events */
    if (Dem_Cfg_EventObdRelated(lEventId) == FALSE)
    {
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }

    lOldDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(lEventId, Dem_DTC_GetDTCStatus(lEventId));

    /* Process the DTC status qualification of the stored event or combination group */
    Dem_DTC_ForEachCombinedEvent(lEventId, Dem_Event_CycleQualifyDcy, &lArgs);                                                   /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */

    lEventQualifyStatus = Dem_Event_GetQualifyStatus(lEventId);
    lEntryQualifyStatus = DEM_MEM_GET_QUALIFIED_MASK(Dem_MemoryEntry_GetState(lMemoryEntryId));

    /* Synchronize the events qualification status */
    if ((lEntryQualifyStatus ^ lEventQualifyStatus) != 0)
    {
      Dem_MemoryEntry_SetState(lMemoryEntryId, DEM_MEM_SET_QUALIFIED_MASK(Dem_MemoryEntry_GetState(lMemoryEntryId), 
                              (lEntryQualifyStatus | lEventQualifyStatus)));
      Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
    }

    lArgs.Common.NewDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(lEventId, lArgs.Common.NewDtcStatus);

# if (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
    if ((Dem_UDSStatus_Test_CDTC(lOldDtcStatus) == FALSE)                                                                        /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_UDSStatus_Test_CDTC(lArgs.Common.NewDtcStatus) == TRUE))
    {
      Dem_MemObdFreezeFrame_SetFFOfEventVisible(lEventId);
      Dem_Mem_FreezeFrameIndexMode02 = Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame();
    }
#endif

    Dem_Notifications_DtcStatusChanged(lEventId, 
                                       lOldDtcStatus, 
                                       lArgs.Common.NewDtcStatus, 
                                       DEM_NOTIFICATIONS_CYCLE_QUALIFIED);
    if (Dem_UDSStatus_Test_CDTC((uint8)(lOldDtcStatus ^ lArgs.Common.NewDtcStatus)) == TRUE)
    {
      Dem_Notifications_EventDataChanged(lEventId);
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_SetDtcSuppression
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
Dem_DTC_SetDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_InternalStatusType lInternalStatus;
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;

  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
    lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);
    lInternalStatus = Dem_DTCInternalStatus_SetDtcSuppressed(lInternalStatus);
    Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lInternalStatus);

    Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
  else
# endif
  {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
    lInternalStatus = Dem_Event_GetInternalStatus(EventId);
    lInternalStatus = Dem_DTCInternalStatus_SetDtcSuppressed(lInternalStatus);
    Dem_Event_SetInternalStatus(EventId, lInternalStatus);

    Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON) */

/* ****************************************************************************
 % Dem_DTC_EventCreateMemory
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
Dem_DTC_EventCreateMemory(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;

  lMemoryIndex = Dem_Memory_AllocateIndex(EventId);
  if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
  { /* Created new entry */
    Dem_DTC_InternalStatusType lInternalStatus;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
    lInternalStatus = Dem_DTC_GetInternalStatus(EventId);
    lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_Active);
    Dem_DTC_SetInternalStatus(EventId,lInternalStatus);
    Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

    if (Dem_Cfg_EventSupportImmediateNv(EventId) == TRUE)
    {
      Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
    }
    else
    {
      Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
    }
  }
  return lMemoryIndex;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF))
/* ****************************************************************************
 % Dem_DTC_StartAgingWithMemoryEntryMultiTarget
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
Dem_DTC_StartAgingWithMemoryEntryMultiTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_InternalStatusType lInternalStatus;
  Dem_Cfg_MemoryIndexType  lMemoryIndex;

  lInternalStatus = Dem_DTC_GetInternalStatus(EventId);
  lMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;

# if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
  if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_None)
  {
    /* If necessary allocate an aging counter */
    if (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(EventId)) == TRUE)
    {
      lMemoryIndex = Dem_Memory_AllocateIndexAging(EventId);
    }
  }
  else
# endif
    if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_Active)
    {
      lMemoryIndex = Dem_Memory_FindIndex_Checked(EventId);
    }
    else
    { 
      /* MISRA */
    }

  if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
  { /* Start Aging */
    uint16 lAgingCounter;
    Dem_MemoryEntry_HandleType lMemoryEntryId;
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
    if (Dem_DTC_GetAgingCounter(EventId, lMemoryEntryId) != DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
    {
      Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                          /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    }
# endif
    /* Initialize the aging target of the memory entry */
    lAgingCounter = Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventAgingCycle(EventId));
    lAgingCounter = Dem_OperationCycle_AddCycleCount(lAgingCounter, Dem_Cfg_EventAgingTarget(EventId));
    Dem_DTC_SetAgingCounter(EventId, lMemoryIndex, lAgingCounter);

# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    /* For WWH-OBD, also start the event's aging timer */
    if (Dem_Cfg_EventSupportAging(EventId) == TRUE)
    {
      uint32 lAgingTimer;

      lAgingTimer = Dem_Mem_GetCumulativeEngRuntime();
      lAgingTimer = Dem_Esm_AddAgingTime(lAgingTimer, DEM_ESM_AGINGTIME_200h);
      Dem_MemoryEntry_SetAgingTimer(lMemoryEntryId, lAgingTimer);
      Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
    }
# endif

    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
    lInternalStatus = Dem_DTC_GetInternalStatus(EventId);
    /* In critical section 'DiagMonitor', set the events stored status to 'AGING' */
    lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_Aging);
    Dem_DTC_SetInternalStatus(EventId, lInternalStatus);
    Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON))
/* ****************************************************************************
 % Dem_DTC_StartAgingWithoutMemoryEntryMultiTarget
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
Dem_DTC_StartAgingWithoutMemoryEntryMultiTarget(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_InternalStatusType lInternalStatus;
  
  lInternalStatus = Dem_DTC_GetInternalStatus(EventId);

  if ((Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_Active)                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
     || (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(EventId)) == TRUE))                                                        
  {
      /* Start Aging, initialize the aging target of the memory entry */
    uint16 lAgingCounter;
    lAgingCounter = Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventAgingCycle(EventId));
    lAgingCounter = Dem_OperationCycle_AddCycleCount(lAgingCounter, Dem_Cfg_EventAgingTarget(EventId));
    Dem_DTC_SetAgingCounter(EventId, DEM_MEM_INVALID_MEMORY_INDEX, lAgingCounter);

    /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */
    lInternalStatus = Dem_DTC_GetInternalStatus(EventId);

    if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_Active)
    {
      /* In critical section 'DiagMonitor', set the events stored status to 'AGING' */
      lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_Aging);
    }

    Dem_DTC_SetInternalStatus(EventId, lInternalStatus);
    Dem_LeaveCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */  
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_DTC_IncrementAgedCounter
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
Dem_DTC_IncrementAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  if (Dem_Cfg_EventSupportAgedCounter(EventId) == TRUE)
  {
    uint8 lAgedCounter;
    lAgedCounter = Dem_DTC_GetAgedCounter(EventId);
    if (lAgedCounter < DEM_DTC_AGED_COUNTER_MAX_VALUE)
    {
      Dem_DTC_SetAgedCounter(EventId, lAgedCounter + 1);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AGINGDATA),
        DEM_NVM_BLOCKSTATE_DIRTY);
    }
  }
} 
#endif

#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_DTC_ResetAgedCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_ResetAgedCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  if (Dem_Cfg_EventSupportAgedCounter(EventId) == TRUE)
  {
    if (Dem_DTC_GetAgedCounter(EventId) != DEM_DTC_AGED_COUNTER_INIT_VALUE)
    {
      Dem_DTC_SetAgedCounter(EventId, DEM_DTC_AGED_COUNTER_INIT_VALUE);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AGINGDATA),
        DEM_NVM_BLOCKSTATE_DIRTY);
    }
  }
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
 * \addtogroup Dem_DTC_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CalculateCombineGroupUdsStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_CalculateCombineGroupUdsStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_DTC_UDSStatusType lReturnValue;
  Dem_Cfg_CombinedGroupIterType lCombinedIter;

  /* In rare cases GroupId is not required */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lReturnValue = 0x00u;

  for (Dem_Cfg_CombinedGroupIterInit(GroupId, &lCombinedIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lSubEventId;

    lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if ((Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)                                                                   /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE))
    {
      lReturnValue = (Dem_DTC_UDSStatusType)(lReturnValue | Dem_Event_GetUDSStatus(lSubEventId));
    }
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DTC_TestPfcRequired
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
Dem_DTC_TestPfcRequired(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;
# if (DEM_CFG_SUPPORT_CLEAR_PDTC_NO_PFC == STD_ON) && (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  lReturnValue = FALSE;
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    {
      Dem_Cfg_CombinedGroupIndexType lGroupId;
            
      lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
      if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
      {
        Dem_Cfg_CombinedGroupIterType lCombinedIter;
        for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          Dem_EventIdType lSubEventId;
          lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
          if ( (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
              && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE) )
          {
            if (Dem_Cfg_EventRatioIdIdx(lSubEventId) == DEM_CFG_RATIOINDEX_INVALID)
            {
              lReturnValue = TRUE;
              break;
            }
          }
        }
      }
      else
      {
        if (Dem_Cfg_EventRatioIdIdx(EventId) == DEM_CFG_RATIOINDEX_INVALID)
        {
          lReturnValue = TRUE;
        }
      }
    }
#  else
    /* If event has a ratio attached, it can be cleared without respect the PFC cycle. So set PFC cycle to fulfilledPerm */
    if (Dem_Cfg_EventRatioIdIdx(EventId) == DEM_CFG_RATIOINDEX_INVALID)
    {
      lReturnValue = TRUE;
    }
#  endif
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = TRUE;
# endif
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_DTC_TestStoredStatus
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
Dem_DTC_TestStoredStatus(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;
  Dem_DTCInternal_StoredStatusType lInternalStoredStatus;
  lInternalStoredStatus = Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(EventId));

  if (lInternalStoredStatus != Dem_DTCInternalStatus_StoredStatus_None)
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
 % Dem_DTC_TestDtcAvailable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcAvailable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  if (Dem_Cfg_EventIsCombined(EventId) == TRUE)
  {
    lReturnValue = Dem_DTC_TestGroupAvailable(Dem_Cfg_EventCombinedGroup(EventId));
  }
  else
  {
    lReturnValue = Dem_Event_TestEventAvailable(EventId);
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_TestDtcAvailableInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcAvailableInVariant(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  if (Dem_Cfg_EventIsCombined(EventId) == TRUE)
  {
    lReturnValue = Dem_DTC_TestGroupAvailableInVariant(Dem_Cfg_EventCombinedGroup(EventId));
  }
  else
  {
    lReturnValue = Dem_Cfg_EventAvailableByVariant(EventId);
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_TestDtcSuppression
 *****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_TestDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;

  if (Dem_Cfg_EventIsCombined(EventId) == TRUE)
  {
    lReturnValue = Dem_DTC_TestGroupSuppression(Dem_Cfg_EventCombinedGroup(EventId));
  }
  else
  {
    lReturnValue = Dem_DTCInternalStatus_TestDtcSuppressed(Dem_Event_GetInternalStatus(EventId));
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DTC_TestDtcSuppressed
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
Dem_DTC_TestDtcSuppressed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  lReturnValue = (boolean)                                                                                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
     ( (Dem_DTC_TestDtcSuppression(EventId) == TRUE)
    || (Dem_DTC_TestDtcAvailableInVariant(EventId) == FALSE)
    || ( (Dem_DTC_TestDtcAvailable(EventId) == FALSE)
      && (Dem_DTC_TestStoredStatus(EventId) == FALSE) )
     );
  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_DTC_TestRemainingEventforDtc
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
Dem_DTC_TestRemainingEventforDtc(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  Dem_DTC_InternalStatusType lInternalStatus;
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  lReturnValue = FALSE;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_Cfg_CombinedGroupIterType lCombinedIter;

    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      lInternalStatus = Dem_Event_GetInternalStatus(lSubEventId);
      if ( (lSubEventId != EventId)                                                                                              /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_EventInternalStatus_TestEventDisconnected(lInternalStatus) == FALSE) )
      {
        lReturnValue = TRUE;
        break;
      }
    }
  }
  else
# endif
  {
    lReturnValue = FALSE;
  }
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_DTC_ResetFdcToc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ResetFdcToc(
  CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC)  DTCContext
  )
{
  Dem_DTC_InternalStatusType lInternalStatus;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */

  lInternalStatus = Dem_Event_GetInternalStatus(DTCContext->EventId);
  lInternalStatus = Dem_DTCInternalStatus_ResetFdcToc(lInternalStatus);
  Dem_Event_SetInternalStatus(DTCContext->EventId, lInternalStatus);

  Dem_LeaveCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_ResetDtcSuppression
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
Dem_DTC_ResetDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_DTC_InternalStatusType lInternalStatus;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
    lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);
    lInternalStatus = Dem_DTCInternalStatus_ResetDtcSuppressed(lInternalStatus);
    Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lInternalStatus);
    Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
  else
# endif
  {
    Dem_DTC_InternalStatusType lInternalStatus;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
    lInternalStatus = Dem_Event_GetInternalStatus(EventId);
    lInternalStatus = Dem_DTCInternalStatus_ResetDtcSuppressed(lInternalStatus);
    Dem_Event_SetInternalStatus(EventId, lInternalStatus);
    Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON) */

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_DTC_ChangeDtcSuppression
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_ChangeDtcSuppression(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  SuppressionStatus
  )
{
  Std_ReturnType lReturnValue;

  lReturnValue = E_NOT_OK;


  if (EventId != DEM_EVENT_INVALID)
  {
    if (SuppressionStatus == TRUE)
    {
      Dem_DTC_SetDtcSuppression(EventId);
    }
    else
    {
      Dem_DTC_ResetDtcSuppression(EventId);
    }

    Dem_DtrIF_DTCSuppressionChanged(EventId);
    lReturnValue = E_OK;
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_DTC_CalculateDTCStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CalculateDTCStatus(
CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
)
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    DTCContext->NewDtcStatus = Dem_DTC_CalculateCombineGroupUdsStatus(DTCContext->GroupId);                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    Dem_DTC_SetCombinedGroupUDSStatus(DTCContext->GroupId, DTCContext->NewDtcStatus);
  }
  else
#endif
  {
    DTCContext->NewDtcStatus = Dem_Event_GetUDSStatus(DTCContext->EventId);                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}

/* ****************************************************************************
 % Dem_DTC_GetDTCStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_GetDTCStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_UDSStatusType lDtcStatus;
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    lDtcStatus = Dem_DTC_GetCombinedGroupUDSStatus(lGroupId);
  }
  else
#endif
  {
    lDtcStatus = Dem_Event_GetUDSStatus(EventId);
  }
  return lDtcStatus;
}

/* ****************************************************************************
 % Dem_DTC_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_GetFaultDetectionCounter(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
  )
{
  Std_ReturnType lGetFdcReturnValue;
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    lGetFdcReturnValue = Dem_DTC_CombinedGroupGetFDC(lGroupId, FaultDetectionCounter);                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
# endif
  {
    lGetFdcReturnValue = Dem_GetFaultDetectionCounter(EventId, FaultDetectionCounter);                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  return lGetFdcReturnValue;
}


#if ( (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
   && ( ( ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON) ) \
     || ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) ) ) )
/* ****************************************************************************
 % Dem_DTC_CombinedGroupGetFDCMax
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(sint8, DEM_CODE)
Dem_DTC_CombinedGroupGetFDCMax(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  sint8 lMaxFdc;
  Dem_Cfg_CombinedGroupIterType lCombinedIter;

  /* In rare cases GroupId is not required */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

    lMaxFdc = 0;
  for (Dem_Cfg_CombinedGroupIterInit(GroupId, &lCombinedIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_EventIdType lSubEventId;
    lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if ( (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)                                                                  /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE) )
    {
      sint8 lFdc;
      lFdc = Dem_Satellite_GetMaxFaultDetectionCounter(
        Dem_Cfg_EventSatelliteId(lSubEventId),
        Dem_Cfg_EventSatelliteEventId(lSubEventId));
      if (lMaxFdc < lFdc)
      {
        lMaxFdc = lFdc;
      }
    }
  }

  return lMaxFdc;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if ( (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) \
   || (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON) \
   || (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON) \
   || (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) \
   || (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) )
/* ****************************************************************************
 % Dem_DTC_ApplyCombinedStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_ApplyCombinedStatus(
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  )
{
  Dem_DTC_UDSStatusType lReturnValue;
  lReturnValue = DtcStatus;
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (Dem_UDSStatus_Test_TFSLC(lReturnValue) == TRUE)
  {
    lReturnValue = Dem_UDSStatus_Reset_TNCSLC(lReturnValue);
  }
  if (Dem_UDSStatus_Test_TFTOC(lReturnValue) == TRUE)
  {
    lReturnValue = Dem_UDSStatus_Reset_TNCTOC(lReturnValue);
  }
# endif
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_DTC_ApplyExternalOnlyStatus
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
DEM_LOCAL_INLINE FUNC(Dem_DTC_UDSStatusType, DEM_CODE)
Dem_DTC_ApplyExternalOnlyStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  DtcStatus
  )
{
  Dem_DTC_UDSStatusType lReturnValue;
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lReturnValue = DtcStatus;

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    /* DTC has combined group*/
    boolean lWirActive = FALSE;
    Dem_Cfg_CombinedGroupIterType lCombinedIter;

    /* Scan through all active sub-events */
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;

      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if ( (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)                                                                /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE) )
      {
        lWirActive = (boolean)(lWirActive                                                                                        /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          || (Dem_DTCInternalStatus_TestUserControlledWir(Dem_Event_GetInternalStatus(lSubEventId)) == TRUE));
      }
    }
# if (DEM_FEATURE_NEED_OBD == STD_ON)
    lReturnValue = (Dem_DTC_UDSStatusType)(lReturnValue & Dem_Event_GetQualifyStatus(EventId));
# endif
    if (lWirActive == TRUE)
    {
      lReturnValue = Dem_UDSStatus_Set_WIR(lReturnValue);
    }
    lReturnValue = Dem_DTC_ApplyCombinedStatus(lReturnValue);
  }
  else
#endif
  {
    /* EventId is not a combined event */
#if (DEM_FEATURE_NEED_OBD == STD_ON)
    lReturnValue = (Dem_DTC_UDSStatusType)(Dem_Event_GetQualifyStatus(EventId) & lReturnValue);
#endif
    lReturnValue = (Dem_DTC_UDSStatusType)(Dem_DTC_ApplyUserControlledWIR(lReturnValue, Dem_Event_GetInternalStatus(EventId)));
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTC_AgingCycle
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
Dem_DTC_AgingCycle(
CONST(Dem_EventIdType, AUTOMATIC)  EventId,
CONST(uint16, AUTOMATIC)  CycleCounter,
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
)
{
  Dem_DTC_UDSStatusType lDtcStatus;
  Dem_MemoryEntry_HandleType lMemoryEntryHandle;

  lDtcStatus = Dem_DTC_GetDTCStatus(EventId);
#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  if (MemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX)
  {
    lMemoryEntryHandle = DEM_MEMORYENTRY_HANDLE_INVALID;
  }
  else
#endif
  {
    lMemoryEntryHandle = Dem_MemoryEntry_GetId(MemoryIndex);
  }

  if (Dem_UDSStatus_Test_TF(lDtcStatus) == FALSE)
  { 
    /* passive event */
    uint16 lCycleCount;
    lCycleCount = Dem_DTC_GetAgingCounter(EventId, lMemoryEntryHandle);
#if ((DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON) || (DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON))
    if (Dem_DTC_TestStatusForAgingCycle(lDtcStatus) == FALSE)
    { 
      /* Untested cycle requires recalculation of aging target */
      if (lCycleCount <= DEM_OPERATIONCYCLE_CYCLECOUNT_MAX)
      { /* Ignore maxed (latched) counter */
        lCycleCount = Dem_OperationCycle_AddCycleCount(lCycleCount, 1);
        Dem_DTC_SetAgingCounter(EventId, MemoryIndex, lCycleCount);
      }
    }
    else
#endif
    if (CycleCounter == lCycleCount)
    { /* Aging cycle reached, so this event has aged */
      Dem_DTC_Aged(EventId, MemoryIndex);
    }
    else
    { /* Still counting */ }
  }
}                                                                                                                                /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTC_Aged
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
Dem_DTC_Aged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  if (Dem_Cfg_EventSupportAging(EventId) == TRUE)
  {
    Dem_DTC_UDSStatusType lOldDtcStatus;
    Dem_DTC_ForEachCombinedArgType lArgs;

    /* Process aging for each sub-event status */
    lOldDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));
    Dem_DTC_ForEachCombinedEvent(EventId, Dem_Event_Aged, &lArgs);                                                               /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */

# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    if (Dem_Event_TestMilSupport(EventId) == TRUE)
    {
      Dem_EventIdType lMasterEventId;
      lMasterEventId = Dem_Cfg_GetMasterEvent(EventId);

      /* CDTC bit is always reset on aging -> free unconditionally*/
      Dem_Memory_ConfirmedChronoFreeEvent(lMasterEventId);
    }
# endif

# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
#  if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF)
    if (MemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
#  endif
    {
      /* clear the OBD freeze frame */
      if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
      {
        uint8 lObdFreezeFrameIndex;

        lObdFreezeFrameIndex = Dem_Mem_FreezeFrameFindIndex(EventId);

        if (lObdFreezeFrameIndex != Dem_Cfg_GlobalObdIIFFCount())
        {
          if (lObdFreezeFrameIndex == Dem_Mem_FreezeFrameIndexMode02)
          {
            Dem_Mem_FreezeFrameIndexMode02 = Dem_Cfg_GlobalObdIIFFCount();
          }

          Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(lObdFreezeFrameIndex);
          Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_OBDFREEZEFRAME),
            DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
        }
      }
    }
# endif

    if (MemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
    {
#if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
      Dem_DTC_SetAgingCounter(EventId, MemoryIndex, DEM_OPERATIONCYCLE_CYCLECOUNT_AGED);
#else
      {
        /* While clearing an aged memory entry, set the aging counter to Aged */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
        Dem_DTC_SetAgingCounter(EventId, MemoryIndex, DEM_OPERATIONCYCLE_CYCLECOUNT_AGED);
# endif

        /* Remove the event from the memory */
        Dem_Memory_FreeEvent(MemoryIndex, EventId);
      }
#endif
      /* Block is set dirty due to updates from aging counter 
         and free operation */
      Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      /* For combined events, synchronize the combined internal stored status */
      {
        Dem_Cfg_CombinedGroupIndexType lGroupId;
        lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

        if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
        {
          Dem_DTC_InternalStatusType lGroupInternalStatus;

          /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
          Dem_EnterCritical_DiagMonitor();                                                                                       /* PRQA S 3109 */ /* MD_MSR_14.3 */

          lGroupInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);

          Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, lArgs.Common.NewDtcStatus);
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
          lGroupInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lGroupInternalStatus, Dem_DTCInternalStatus_StoredStatus_Aged);
# else
          lGroupInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lGroupInternalStatus, Dem_DTCInternalStatus_StoredStatus_None);
# endif
          Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lGroupInternalStatus);

          Dem_LeaveCritical_DiagMonitor();                                                                                       /* PRQA S 3109 */ /* MD_MSR_14.3 */
          /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
        }
      }
#endif

      /* If configured, notify the DTC status change */
      if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
      {
        Dem_Notifications_DtcStatusChanged(EventId, 
                                           lOldDtcStatus, 
                                           Dem_DTC_ApplyExternalOnlyStatus(EventId, lArgs.Common.NewDtcStatus), 
                                           DEM_NOTIFICATIONS_DTC_AGED);
      }
    }
    else
    {
      /* When a memory entry is aged, set the aging counter to aged */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
      Dem_DTC_SetAgingCounter(EventId, DEM_MEM_INVALID_MEMORY_INDEX, DEM_OPERATIONCYCLE_CYCLECOUNT_AGED);
# endif
    }
#if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
    Dem_DTC_IncrementAgedCounter(EventId);
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
    {
      Dem_Cfg_MemoryIndexType lTimeSeriesIndex;

      lTimeSeriesIndex = Dem_Mem_TimeSeriesFindIndex(EventId);
      if (lTimeSeriesIndex != DEM_MEM_INVALID_MEMORY_INDEX)
      { /* remove the time series entry */
        Dem_Mem_TimeSeriesFreeIndex(lTimeSeriesIndex);
        Dem_Nvm_SetTimeSeriesMemoryBlockState(lTimeSeriesIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
#endif
  }
  else
  {
    /* Every event has an aging counter and hence must be latched */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF)
    if (MemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
# endif
    {
      /* Latch the aging counter and set the memory entries NV status to DIRTY */
      Dem_DTC_SetAgingCounter(EventId, MemoryIndex, DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED);
    }
  }
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */


#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DTC_ClearOBDFreezeFrame
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
Dem_DTC_ClearOBDFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId);                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_ON)
  if ( (Dem_Cfg_EventObdRelated(EventId) == TRUE)                                                                                /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(EventId)) == FALSE) )
  { /* DTC did not confirm before starting to age - release the OBD freeze
       frame if held by the event */
    uint8 lObdFreezeFrameIndex;

    lObdFreezeFrameIndex = Dem_Mem_FreezeFrameFindIndex(EventId);

    if (lObdFreezeFrameIndex != Dem_Cfg_GlobalObdIIFFCount())
    {
      if (lObdFreezeFrameIndex == Dem_Mem_FreezeFrameIndexMode02)
      {
        Dem_Mem_FreezeFrameIndexMode02 = Dem_Cfg_GlobalObdIIFFCount();
      }
      Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(lObdFreezeFrameIndex);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_OBDFREEZEFRAME), 
                                  DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
    }
  }
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif



/* ****************************************************************************
 % Dem_DTC_Cleared
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
Dem_DTC_Cleared(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lDoClear;
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
# endif

# if (DEM_CFG_NOTIFY_CLEAR_ALLOWED == STD_ON)
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_Cfg_CombinedGroupIterType lGroupIter;
    lDoClear = TRUE;
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lGroupIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterExists(&lGroupIter) == TRUE;                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */ /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterNext(&lGroupIter))                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lGroupIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
      {
        if (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE)
        {
          lDoClear = Dem_ClearTask_ClearEventAllowed(lSubEventId);
        }
      }
      if (lDoClear == FALSE)
      {
        break;
      }
    }
  }
  else
#  endif /* (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) */
  {
    lDoClear = Dem_ClearTask_ClearEventAllowed(EventId);
  }

  if (lDoClear == TRUE)
  {
    Dem_DTC_Cleared_Internal(EventId);
  }
# else
  lDoClear = TRUE;
  Dem_DTC_Cleared_Internal(EventId);
# endif

  /* Always call init monitor callbacks */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_Cfg_CombinedGroupIterType lGroupIter;
    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lGroupIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterExists(&lGroupIter) == TRUE;                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Cfg_CombinedGroupIterNext(&lGroupIter))                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lGroupIter);                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
      {
        if (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE)
        {
          Dem_Notifications_InitMonitorForEvent(lSubEventId, DEM_INIT_MONITOR_CLEAR);
        }
      }
    }
  }
  else
# endif /* (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) */
  {
    Dem_Notifications_InitMonitorForEvent(EventId, DEM_INIT_MONITOR_CLEAR);
  }

  Dem_Notifications_InitMonitorForFunction(EventId);

  return lDoClear;
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Displaced
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
Dem_DTC_Displaced(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_UDSStatusType lOldDtcStatus;
  Dem_DTC_ForEachCombinedArgType lArgs;

  lOldDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));
  Dem_DTC_ForEachCombinedEvent(EventId, Dem_Event_Displaced, &lArgs);                                                            /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */

# if ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON))
    if (Dem_Event_TestMilSupport(EventId) == TRUE)
    {
#  if(DEM_CFG_STORAGE_AT_CONFIRMED == STD_OFF)
      if ( (Dem_UDSStatus_Test_CDTC(lArgs.Common.OldDtcStatus) == TRUE)                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_UDSStatus_Test_CDTC(lArgs.Common.NewDtcStatus) == FALSE) )
#  endif
      {
        Dem_EventIdType lMasterEventId;
        lMasterEventId = Dem_Cfg_GetMasterEvent(EventId);
        Dem_Memory_ConfirmedChronoFreeEvent(lMasterEventId);
      }
    }
# endif

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  {
    Dem_Cfg_CombinedGroupIndexType lGroupId;
    lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
    if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, lArgs.Common.NewDtcStatus);

      /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */
      {
        Dem_DTC_InternalStatusType lInternalStatus;
        lInternalStatus = Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(lGroupId);
        lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_None);
        Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lInternalStatus);
      }
      Dem_LeaveCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */
      /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
    }
  }
# endif

  /* If the displaced memory entry is not confirmed, reset the aging counter */
# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  if ((Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(EventId)) == FALSE))
  {
    Dem_DTC_TestAndInvalidateAgingCounter(EventId);
  }
# endif

  /* Call status changed notifications (there is always a change) */
  Dem_Notifications_DtcStatusChanged(EventId, 
                                     lOldDtcStatus, 
                                     Dem_DTC_ApplyExternalOnlyStatus(EventId, lArgs.Common.NewDtcStatus), 
                                     DEM_NOTIFICATIONS_DTC_DISPLACED);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 % Dem_DTC_OpCycleEnd_Aging
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
Dem_DTC_OpCycleEnd_Aging(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_UDSStatusType, AUTOMATIC)  OldDtcStatus                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(OldDtcStatus);                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */

  if (Dem_Cfg_EventAgingTarget(EventId) == 0)
  {
# if (DEM_CFG_AGING_00_START_TRIGGER_PASSED == STD_OFF) || (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)
#  if (DEM_CFG_AGING_00_START_TRIGGER_PASSED == STD_ON) && (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)
    /* Events with healing target 0 are aged at passed result */
    if (Dem_Cfg_EventHealingTarget(EventId) != 0)
#  endif
    {
      if ((Dem_UDSStatus_Test_TNCTOC(OldDtcStatus) == FALSE)                                                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
#  if (DEM_CFG_AGING_00_START_TESTS_TFTOC == STD_ON)
        && (Dem_UDSStatus_Test_TFTOC(OldDtcStatus) == FALSE))
#  else
        && (Dem_UDSStatus_Test_TF(OldDtcStatus) == FALSE))
#  endif
      {
        if ((Dem_Cfg_EventCombinedGroup(EventId) == DEM_CFG_COMBINED_GROUP_INVALID)                                               /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          || (Dem_DTC_TestDtcMayAge(EventId) == TRUE))
        {
          Dem_DTC_AgingStartZeroTarget(EventId);
        }
      }
    }
# endif
  }
  else
  {
# if (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_OFF) || (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)                         /* COV_DEM_UNSUPPORTED_FEATURE TX tf tf */
    if ((Dem_UDSStatus_Test_TNCTOC(OldDtcStatus) == FALSE)                                                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
#  if (DEM_CFG_AGING_START_TESTS_TFTOC == STD_ON)
      && (Dem_UDSStatus_Test_TFTOC(OldDtcStatus) == FALSE))
#  else
      && (Dem_UDSStatus_Test_TF(OldDtcStatus) == FALSE))
#  endif
    {
      if ( (Dem_Cfg_EventCombinedGroup(EventId) == DEM_CFG_COMBINED_GROUP_INVALID)                                               /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        || (Dem_DTC_TestDtcMayAge(EventId) == TRUE) )
      {
        Dem_DTC_AgingStartMultiTarget(EventId);
      }
    }
# endif /* (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_OFF) || (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON) */
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /*(DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON)*/

/* ****************************************************************************
 % Dem_DTC_InitDTCContext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitDTCContext(
CONST(Dem_EventIdType, AUTOMATIC)  EventId,
CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
)
{
  DTCContext->EventId = EventId;                                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DTCContext->OldDtcStatus = Dem_DTC_GetDTCStatus(EventId);                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DTCContext->OldExternalDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(EventId,  DTCContext->OldDtcStatus);                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  DTCContext->DtcEffects = DEM_CFG_TRIGGER_NONE;                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DTCContext->GroupId = Dem_Cfg_EventCombinedGroup(EventId);                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
}

/* ****************************************************************************
 % Dem_DTC_CalculateFailedEffects
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
Dem_DTC_CalculateFailedEffects(
CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
CONST(uint8, AUTOMATIC)  EventEffects
)
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
# if (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON)
    if (Dem_DTC_TestStoredStatus(DTCContext->EventId) == FALSE)
    {
      DTCContext->DtcEffects = (uint8)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_TESTFAILED);                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      DTCContext->DtcEffects = (uint8)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE);                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      DTCContext->DtcEffects = (uint8)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_FIRSTTHISCYCLE);                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
# endif
    {
      if (Dem_UDSStatus_Test_TF(DTCContext->OldDtcStatus) == FALSE)
      {
        DTCContext->DtcEffects = (uint8)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_TESTFAILED);                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
      if (Dem_UDSStatus_Test_TFTOC(DTCContext->OldDtcStatus) == FALSE)
      {
        DTCContext->DtcEffects = (uint8)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE);                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        DTCContext->DtcEffects = (uint8)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_FIRSTTHISCYCLE);                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
    }
  }
  else
#endif
  {
    DTCContext->DtcEffects = EventEffects;                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}

/* ****************************************************************************
 % Dem_DTC_CalculateFailedEffects_OnStorage
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
Dem_DTC_CalculateFailedEffects_OnStorage(
CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext,
CONST(uint8, AUTOMATIC)  EventEffects
)
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
   if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    if((EventEffects & DEM_CFG_TRIGGER_PENDING) != 0)
    {
      if ((Dem_UDSStatus_Test_PDTC(DTCContext->OldDtcStatus) == FALSE)                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
# if (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON) && (DEM_CFG_PROCESS_PDTC_ALL_DTC == STD_ON)
        || (Dem_DTC_TestStoredStatus(DTCContext->EventId) == FALSE)
# endif
        )
      {
        DTCContext->DtcEffects = (uint8)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_PENDING);                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
    }

    if((EventEffects & DEM_CFG_TRIGGER_CONFIRMED) != 0)
    {
      if ( (Dem_UDSStatus_Test_CDTC(DTCContext->OldDtcStatus) == FALSE)                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
# if (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
        || (Dem_DTC_TestStoredStatus(DTCContext->EventId) == FALSE)
# endif
        )
      {
        DTCContext->DtcEffects = (uint8)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_CONFIRMED);                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
    }

    if((EventEffects & DEM_CFG_TRIGGER_INDICATOR) != 0)
    {
      if (Dem_UDSStatus_Test_WIR(DTCContext->OldDtcStatus) == FALSE)
      {
        DTCContext->DtcEffects = (uint8)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_INDICATOR);                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
    }
  }
  else
#endif
  {
    DTCContext->DtcEffects = EventEffects;                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}                                                                                                                                /* PRQA S 6010 */ /* MD_MSR_STPTH */

/* ****************************************************************************
 % Dem_DTC_ProcessFailedEffects
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessFailedEffects(
CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
)
{
  Dem_DTC_InternalStatusType   lNewInternalStatus;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
   Dem_EnterCritical_DiagMonitor();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */
   lNewInternalStatus = Dem_DTC_GetInternalStatus(DTCContext->EventId);
   if (Dem_DTCInternalStatus_GetStoredStatus(lNewInternalStatus) != Dem_DTCInternalStatus_StoredStatus_None)
   {
     lNewInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lNewInternalStatus, Dem_DTCInternalStatus_StoredStatus_Active);
     Dem_DTC_SetInternalStatus(DTCContext->EventId, lNewInternalStatus);
   }
    Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
}

/* ****************************************************************************
 % Dem_DTC_Passed_ProcessDTCEffects
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
Dem_DTC_Passed_ProcessDTCEffects(
CONSTP2CONST(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCContext)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
  /* if event is assigned to a readiness group */
  if (Dem_Cfg_EventReadinessGroup(DTCContext->EventId) != DEM_CFG_READINESS_NONE)
  {
    Dem_DTC_Passed_ProcessDTCEffects_TPSLC(DTCContext);                                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
  Dem_DTC_AgingStartVCC(DTCContext);                                                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#else
# if (DEM_FEATURE_NEED_AGING_TRIGGER_PASSED == STD_ON)
  if (Dem_Cfg_EventAgingTarget(DTCContext->EventId) == 0)
# endif
  {
# if (DEM_CFG_AGING_00_START_TRIGGER_PASSED == STD_ON)
    if (Dem_DTC_TestDtcMayAge(DTCContext->EventId) == TRUE)
    {
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
      {
        if ( (Dem_UDSStatus_Test_TF(DTCContext->NewDtcStatus) == FALSE)                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          && (Dem_UDSStatus_Test_TNCTOC(DTCContext->NewDtcStatus) == FALSE)
#   if (DEM_CFG_AGING_00_START_TESTS_TFTOC == STD_ON)
          && (Dem_UDSStatus_Test_TFTOC(DTCContext->NewDtcStatus) == FALSE)
#   endif
          )
        {
          Dem_DTC_AgingStartZeroTarget(DTCContext->EventId);
        }
      }
      else
#  endif
      {
#  if (DEM_CFG_AGING_00_START_TESTS_TFTOC == STD_ON)
        if (Dem_UDSStatus_Test_TFTOC(DTCContext->NewDtcStatus) == FALSE)
#  endif
        {
          Dem_DTC_AgingStartZeroTarget(DTCContext->EventId);
        }
      }
    }
# endif
  }
# if (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_ON)
  else
  {
    if (Dem_DTC_TestDtcMayAge(DTCContext->EventId) == TRUE)
    {
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      if (DTCContext->GroupId != DEM_CFG_COMBINED_GROUP_INVALID)
      {
        if ( (Dem_UDSStatus_Test_TF(DTCContext->NewDtcStatus) == FALSE)                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          && (Dem_UDSStatus_Test_TNCTOC(DTCContext->NewDtcStatus) == FALSE)
#   if (DEM_CFG_AGING_START_TESTS_TFTOC == STD_ON)
          && (Dem_UDSStatus_Test_TFTOC(DTCContext->NewDtcStatus) == FALSE)
#   endif
          )
        {
          Dem_DTC_AgingStartMultiTarget(DTCContext->EventId);
        }
      }
      else
#  endif
      {
#  if (DEM_CFG_AGING_START_TESTS_TFTOC == STD_ON)
        if (Dem_UDSStatus_Test_TFTOC(DTCContext->NewDtcStatus) == FALSE)
#  endif
        {
          Dem_DTC_AgingStartMultiTarget(DTCContext->EventId);
        }
      }
    }
  }
# endif
#endif /* (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON) */
}                                                                                                                                 /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTC_ProcessStorage
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_ProcessStorage(
  CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext,
  CONSTP2VAR(Dem_DTC_ContextType, AUTOMATIC, AUTOMATIC) DTCContext
  )
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;
  Dem_Event_InternalStatusType lInternalStatus;
  boolean lIsOccurrence;
  uint8 lBlockModification;
#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
  uint16 lOldOccurrenceCount;
#endif

  lMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;
  lInternalStatus = Dem_DTC_GetInternalStatus(DTCContext->EventId);
  lIsOccurrence = FALSE;                                                                                                         /* PRQA S 3198 */ /* MD_DEM_3198_fp */
  lBlockModification = DEM_DATA_NO_CHANGES;

  if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_None)
  { /* Not stored yet - If no entry can be created we need to discard some updates */
#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
    lOldOccurrenceCount = 0;
#endif
    if ((DTCContext->DtcEffects & DEM_ESM_EVENT_STORAGE_TRIGGER) != 0)
    { /* We have to store this event in memory */
      lMemoryIndex = Dem_DTC_EventCreateMemory(DTCContext->EventId);
    }
    if (lMemoryIndex == DEM_MEM_INVALID_MEMORY_INDEX)
    { /* Storage was not possible, discard changes that require storage */
      EventContext->EventEffects = (uint8)(EventContext->EventEffects & DEM_ESM_EVENT_RESET_TRIGGER_MASK);                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      DTCContext->DtcEffects = (uint8)(DTCContext->DtcEffects & DEM_ESM_EVENT_RESET_TRIGGER_MASK);                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
    {
      EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_TESTFAILED);                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      DTCContext->DtcEffects = (uint8)(DTCContext->DtcEffects | DEM_CFG_TRIGGER_TESTFAILED);                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
  else
  { /* Already stored - Update the existing entry if necessary */
    lMemoryIndex = Dem_Memory_FindIndex_Checked(DTCContext->EventId);
#if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
    if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_Aged)
    {
      if ((DTCContext->DtcEffects & DEM_ESM_EVENT_STORAGE_TRIGGER) != 0)
      { /* Reclaim aged event */
        lIsOccurrence = TRUE;
        lBlockModification = Dem_Memory_UpdateEventStatistics(
                             DTCContext->EventId, lMemoryIndex, lIsOccurrence);
      }
    }
    else
#endif
    {
      lIsOccurrence = (boolean)((DTCContext->DtcEffects & DEM_ESM_EVENT_UPDATE_TRIGGER) != 0);
      lBlockModification = Dem_Memory_UpdateEventStatistics(
                             DTCContext->EventId, lMemoryIndex, lIsOccurrence);
    }
#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
    lOldOccurrenceCount = Dem_MemoryEntry_GetOccurrenceCounter(Dem_MemoryEntry_GetId(lMemoryIndex));
#endif
#if (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
    {
      /* initialize the CyclesSinceFirstFailed counter when not done yet, e.g. due memory entry allocation via FDC */
      if (Dem_MemoryEntry_GetCyclesSinceFirstFailed(Dem_MemoryEntry_GetId(lMemoryIndex)) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
      {
        Dem_MemoryEntry_SetCyclesSinceFirstFailed(Dem_MemoryEntry_GetId(lMemoryIndex), Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventOperationCycle(DTCContext->EventId)));
        lBlockModification |= DEM_DATA_SET_STATISTICS_CHANGED(lBlockModification);
      }
    }
#endif
  }

  if (Dem_Cfg_EventObdRelated(DTCContext->EventId) == TRUE)
  { /* OBD related Event, store Freeze Frame */
    lBlockModification |= Dem_Memory_TriggerObdFreezeFrameStorage(DTCContext->EventId, DTCContext->DtcEffects, lMemoryIndex);
  }

  lBlockModification |= Dem_Memory_UpdateEventEntry(DTCContext->EventId, DTCContext->DtcEffects, lMemoryIndex);

  if ( (lIsOccurrence == TRUE)                                                                                                   /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_Cfg_EventSupportImmediateNv(DTCContext->EventId) == TRUE) )
  {
    /* If the event is configured for immediate NV updates, set the entries NV state to immediate update */
#if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
    uint16 lNewOccurrenceCount;
    lNewOccurrenceCount = Dem_MemoryEntry_GetOccurrenceCounter(Dem_MemoryEntry_GetId(lMemoryIndex));
    Dem_Nvm_TestAndSetBlockStateImmediate(lMemoryIndex,
                                          lOldOccurrenceCount,
                                          lNewOccurrenceCount);
#else
    Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
#endif
  }
  else
  if (lBlockModification != DEM_DATA_NO_CHANGES)
  {
    /* Otherwise set the entries NV state to 'DIRTY' */
    Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
  }
  else
  {
    /* MISRA */
  }
  EventContext->DataModified = (boolean)DEM_DATA_TEST_USERDATA_CHANGED(lBlockModification);                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON) || (DEM_CFG_STORAGE_AT_FDC == STD_ON)
/* ****************************************************************************
 % Dem_DTC_FdcTrip
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
Dem_DTC_FdcTrip(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  FirstThisCycle
  )
{
  Dem_Cfg_MemoryIndexType lMemoryIndex;

  lMemoryIndex = DEM_MEM_INVALID_MEMORY_INDEX;                                                                                   /* PRQA S 3112, 3198 */ /* MD_DEM_14.2, MD_DEM_3198_na */

  if (Dem_DTC_TestStoredStatus(EventId) == TRUE)
  {
    lMemoryIndex = Dem_Memory_FindIndex_Checked(EventId);
# if (DEM_CFG_STORAGE_AT_FDC == STD_ON)
#  if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON) || (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
    if (
#   if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
         (Dem_DTC_GetAgingCounter(EventId, Dem_MemoryEntry_GetId(lMemoryIndex)) == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
#   endif
#   if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON) && (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
      ||
#   endif
#   if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
         (DEM_MEM_TEST_AGING_ONLY(Dem_MemoryEntry_GetState(Dem_MemoryEntry_GetId(lMemoryIndex))) == TRUE)
#   endif
      )
    {
      Dem_MemoryEntry_InitializeEntry(Dem_MemoryEntry_GetId(lMemoryIndex));
    }
#  endif
# endif
  }
# if (DEM_CFG_STORAGE_AT_FDC == STD_ON)
  else
  {
    /* FdcTrip is the storage trigger and the event is not yet stored */
    lMemoryIndex = Dem_DTC_EventCreateMemory(EventId);
  }
# endif

  if (lMemoryIndex != DEM_MEM_INVALID_MEMORY_INDEX)
  {
    uint8 lBlockModification;
    uint8 lUpdateFlags;

# if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
    if (Dem_DTC_GetAgingCounter(EventId, Dem_MemoryEntry_GetId(lMemoryIndex)) == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
    {
      Dem_DTC_TestAndInvalidateAgingCounter(EventId);
    }
# endif

    /* If the event is stored, update the event data with FDC respectively FDC & FirstThisCycle */
    lUpdateFlags = (uint8)((FirstThisCycle == TRUE) ? DEM_CFG_TRIGGER_FDC_FIRST_IN_CYCLE:DEM_CFG_TRIGGER_FDC);

    lBlockModification = Dem_Memory_UpdateEventEntry(EventId, lUpdateFlags, lMemoryIndex);

    if (lBlockModification != DEM_DATA_NO_CHANGES)
    {
      if (Dem_Cfg_EventSupportImmediateNv(EventId) == TRUE)
      {
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
      }
      else
      {
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }

    if (DEM_DATA_TEST_USERDATA_CHANGED(lBlockModification) == TRUE)
    {
      Dem_Notifications_EventDataChanged(EventId);
    }
  }

# if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  Dem_Prestore_StateSetDiscard();
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif



#if ((DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON) \
      && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF))
/* ****************************************************************************
 % Dem_DTC_UpdateFdcMax
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
Dem_DTC_UpdateFdcMax(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  if (Dem_DTC_TestStoredStatus(EventId) == TRUE)
  { /* Already stored - Find, *but don't update* the memory entry */
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_MemoryEntry_HandleType lMemoryEntryId;

    lMemoryIndex = Dem_Memory_FindIndex_Checked(EventId);
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    if (Dem_Cfg_EventCombinedGroup(EventId) != DEM_CFG_COMBINED_GROUP_INVALID)
    {
      /* synchronize the current max FDC with the stored FDC max value */
      sint8 lOldFdc;
      sint8 lNewFdc;

      lOldFdc = (sint8) Dem_MemoryEntry_GetDebounceValueMax(lMemoryEntryId);
      lNewFdc = Dem_DTC_CombinedGroupGetFDCMax(Dem_Cfg_EventCombinedGroup(EventId));
      if (lOldFdc < lNewFdc)
      {
        Dem_MemoryEntry_SetDebounceValueMax(lMemoryEntryId, (sint16)lNewFdc);
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
    else
# endif
    {
      /* synchronize the current max FDC with the stored FDC max value */
      sint8 lOldFdc;
      sint8 lNewFdc;

      lOldFdc = (sint8)Dem_MemoryEntry_GetDebounceValueMax(lMemoryEntryId);
      lNewFdc = Dem_Satellite_GetMaxFaultDetectionCounter(
          Dem_Cfg_EventSatelliteId(EventId),
          Dem_Cfg_EventSatelliteEventId(EventId));
      if (lOldFdc < lNewFdc)
      {
        Dem_MemoryEntry_SetDebounceValueMax(lMemoryEntryId, (sint16)lNewFdc);
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
      }
    }
    /*
    No data changed callbacks for modified internal data
    */
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Disconnect
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
Dem_DTC_Disconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (Dem_Cfg_EventCombinedGroup(EventId) != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_DTC_Disconnect_Combined(EventId);
  }
  else
# endif
  {

    Dem_Event_Disconnect_Normal(EventId);
  }
}
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_DTC_Reconnect
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
  Dem_DTC_Reconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (Dem_Cfg_EventCombinedGroup(EventId) != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_DTC_Reconnect_Combined(EventId);
  }
  else
# endif
  {
    Dem_Event_Reconnect_Normal(EventId);
  }
}
#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 % Dem_DTC_GetWIRStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTC_GetWIRStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
 return (boolean)(Dem_DTCInternalStatus_TestUserControlledWir(Dem_Event_GetInternalStatus(EventId))); 
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 % Dem_DTC_SetWIRStatus
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DTC_SetWIRStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC) WIRStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Event_InternalStatusType lInternalStatus;

  lReturnValue = E_NOT_OK;                                                                                                       /* PRQA S 3198 */ /* MD_DEM_3198_na */
# if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS == STD_OFF)
  if (Dem_EnableCondition_TestEnableConditionFulfilled(DEM_ENABLECONDITION_CONTROLDTCSETTING) == TRUE)
# endif
  {
    /* DTC setting is enabled, proceed */
    if (Dem_DTCInternalStatus_TestUserControlledWir(Dem_Event_GetInternalStatus(EventId)) != WIRStatus)
    {
      uint8 lOldDtcStatus;
      uint8 lNewDtcStatus;
      /* override status has to be changed */
      lNewDtcStatus = Dem_DTC_GetDTCStatus(EventId);
      lOldDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(EventId, lNewDtcStatus);
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */

      /* update internal status bit */
      lInternalStatus = Dem_Event_GetInternalStatus(EventId);
      if (WIRStatus == FALSE)
      {
        lInternalStatus = Dem_DTCInternalStatus_ResetUserControlledWir(lInternalStatus);
      }
      else
      {
        lInternalStatus = Dem_DTCInternalStatus_SetUserControlledWir(lInternalStatus);
      }
      Dem_Event_SetInternalStatus(EventId, lInternalStatus);

      Dem_LeaveCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

      lNewDtcStatus = Dem_DTC_ApplyExternalOnlyStatus(EventId, lNewDtcStatus);
      Dem_Notifications_DtcStatusChanged(EventId, 
                                         lOldDtcStatus, 
                                         lNewDtcStatus, 
                                         DEM_NOTIFICATIONS_USER_WIR);
    }

    lReturnValue = E_OK;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_DTC_CycleQualifyDcy
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_CycleQualifyDcy(
  void
  )
{
# if (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
  Dem_DTC_CycleQualifyDcy_AllDtc();
# else
  Dem_DTC_CycleQualifyDcy_StoredOnly();
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


/* ****************************************************************************
 % Dem_DTC_OpCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_OpCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  )
{
  Dem_DTC_ForEachCombinedArgType lArgs;
  lArgs.Specific.EventOpCycle_Internal.CycleStatus = CycleStatus;
  Dem_DTC_ForEachCombinedEvent(EventId, Dem_Event_OpCycle, &lArgs);                                                              /* SBSW_DEM_CALL_FOREACH_COMBINED_EVENT */
}

/* ****************************************************************************
 % Dem_DTC_InitQualification
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_InitQualification(
  void
  )
{
#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF)
  Dem_EventIdType lEventId;
  Dem_Memory_AllocMemEntriesIterType lStoredEventsIter;

  /* Scan the primary memory and extract qualified warningIndicatorRequested and confirmedDTC status */
  for (Dem_Memory_AllocMemEntriesChrono_IterInit(DEM_CFG_MEMORYID_PRIMARY, &lStoredEventsIter);                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Memory_AllocMemEntriesChrono_IterExists(&lStoredEventsIter) == TRUE;                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Memory_AllocMemEntriesChrono_IterNext(&lStoredEventsIter))                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    Dem_MemoryEntry_HandleType lMemoryEntryId;
    uint8 lEntryState;

    lMemoryIndex = Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(&lStoredEventsIter);                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);
    lEventId = Dem_MemoryEntry_GetEventId(lMemoryEntryId);
    if ( (Dem_Event_TestValidHandle(lEventId) == TRUE)                                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_Cfg_EventObdRelated(lEventId) == TRUE))
    { /* only OBD related events supports the qualification of Confirmed and WIR bit */
      lEntryState = Dem_MemoryEntry_GetState(lMemoryEntryId);
      Dem_DTC_SetQualifyStatus(lEventId, DEM_MEM_GET_QUALIFIED_MASK(lEntryState));
    }
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTC_Init
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
Dem_DTC_Init(
  void
  )
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  {
    lGroupId = Dem_Cfg_GlobalCombinedGroupCount();
    while (lGroupId > 0)
    {
      --lGroupId;
      Dem_DTC_InitGroupInternalStatus(lGroupId);
      Dem_DTC_SetCombinedGroupUDSStatus(lGroupId, Dem_DTC_CalculateCombineGroupUdsStatus(lGroupId));
    }
  }
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  {
    Dem_EventIdType lEventId;
    Dem_DTC_InternalStatusType lInternalStatus;
    for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
    {
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      /* Only process master events with memory entry */
      if (Dem_Cfg_GetMasterEvent(lEventId) != lEventId)
      {
        continue;                                                                                                                /* PRQA S 0770 */ /* MD_DEM_14.5 */
      }
# endif

      lInternalStatus = Dem_DTC_GetInternalStatus(lEventId);

      /* Invalidate the aging counter of events which are not stored and confirmed */
      if ((Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_None)                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(lEventId)) == FALSE))                                                   
      {
        Dem_DTC_TestAndInvalidateAgingCounter(lEventId);
      }
    }
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTC_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTC_PreInit(
  void
  )
{
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  {
    Dem_Cfg_CombinedGroupIndexType lGroupId;
    for (lGroupId = 0; lGroupId < Dem_Cfg_GlobalCombinedGroupCount(); ++lGroupId)
    {
      Dem_Event_InternalStatusType lInternalStatus;
      Dem_Cfg_CombinedGroupIterType lSubEventIter;

      lInternalStatus = Dem_EventInternalStatus_SetEventDisconnected(0);
      for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lSubEventIter);                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterExists(&lSubEventIter) == TRUE;                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterNext(&lSubEventIter))                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        if (Dem_Cfg_EventAvailableByVariant(Dem_Cfg_CombinedGroupIterGet(&lSubEventIter)) == TRUE)                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          lInternalStatus = Dem_EventInternalStatus_SetAvailableInVariant(lInternalStatus);
        }
        if (Dem_Cfg_EventAvailableByDefault(Dem_Cfg_CombinedGroupIterGet(&lSubEventIter)) == TRUE)                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          lInternalStatus = Dem_EventInternalStatus_ResetEventDisconnected(lInternalStatus);
        }
      }
      Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(lGroupId, lInternalStatus);
    }
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_DTC_SetAgingCounter
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
Dem_DTC_SetAgingCounter(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(uint16, AUTOMATIC) AgingCounter
  )
{
#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  if (Dem_Cfg_EventUdsDtc(EventId) != DEM_CFG_DTC_UDS_INVALID)        
  {
    Dem_Event_SetAgingCounter(EventId, AgingCounter);
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AGINGDATA), 
                                DEM_NVM_BLOCKSTATE_DIRTY);
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryIndex)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
  }
  else
  {
    /* MISRA */
  }
#else
  {    
    Dem_MemoryEntry_HandleType lMemoryEntryId;
    lMemoryEntryId = Dem_MemoryEntry_GetId(MemoryIndex);
    Dem_MemoryEntry_SetAgingCounter(lMemoryEntryId, AgingCounter);
    Dem_Nvm_SetEventMemoryBlockState(MemoryIndex, DEM_NVM_BLOCKSTATE_DIRTY);
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  }
#endif
}

/* ****************************************************************************
 % Dem_DTC_GetAgingCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_DTC_GetAgingCounter(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC) MemoryEntryId
  )
{
  uint16 lAgingCounter;

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  {
    lAgingCounter = Dem_Event_GetAgingCounter(EventId);
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryEntryId)                                                                              /* PRQA S 3112 */ /* MD_DEM_14.2 */
  }
#else
  {
    lAgingCounter = Dem_MemoryEntry_GetAgingCounter(MemoryEntryId);
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  }
#endif

  return lAgingCounter;
}

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 % Dem_DTC_TestAndInvalidateAgingCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DTC_TestAndInvalidateAgingCounter(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  if ((Dem_Cfg_EventUdsDtc(EventId) != DEM_CFG_DTC_UDS_INVALID)                                                                  /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_Event_GetAgingCounter(EventId) != DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID))
  {
    Dem_Event_SetAgingCounter(EventId, DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID);
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AGINGDATA), 
                                DEM_NVM_BLOCKSTATE_DIRTY);
  }
}
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
/* ****************************************************************************
 % Dem_DTC_GetAgingStatus
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
DEM_LOCAL FUNC(Dem_DTC_AgingStatusType, DEM_CODE)
Dem_DTC_GetAgingStatus(                                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_DTC_AgingStatusType lAgingStatus;
  uint16 lEventAgingCounter;

  lAgingStatus = Dem_DTC_AgingStatusNone;
  lEventAgingCounter = Dem_Event_GetAgingCounter(EventId);
  if (lEventAgingCounter <= DEM_OPERATIONCYCLE_CYCLECOUNT_MAX)
  {
    lAgingStatus = Dem_DTC_AgingStatusInProgress;
  }
  else if ((lEventAgingCounter == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)                                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          || (lEventAgingCounter == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED))
  {
    lAgingStatus = Dem_DTC_AgingStatusAged;
  }
  else
  { 
    /* MISRA */
  }

  return lAgingStatus;
}
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DTC_IMPLEMENTATION_H */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTC_Implementation.h
 *********************************************************************************************************************/
