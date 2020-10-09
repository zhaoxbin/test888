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
/*! \addtogroup Dem_Event
 *  \{
 *  \file       Dem_Event_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the Event subcomponent
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

#if !defined (DEM_EVENT_IMPLEMENTATION_H)                                                                                        /* PRQA S 0883 */ /* MD_DEM_19.15 */
#define DEM_EVENT_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Event_Interface.h"


                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

#include "Dem_UDSStatus_Implementation.h"
#include "Dem_EventInternalStatus_Implementation.h"
#include "Dem_DTC_Implementation.h"
#include "Dem_DTCInternalStatus_Implementation.h"
#include "Dem_StorageCondition_Implementation.h"
#include "Dem_InitState_Implementation.h"
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_Scheduler_Implementation.h"
#include "Dem_DtrIF_Implementation.h"
#include "Dem_OperationCycle_Implementation.h"
#include "Dem_Nvm_Implementation.h"
#include "Dem_Prestore_Implementation.h"
#include "Dem_Esm_Implementation.h"
#include "Dem_Indicator_Implementation.h"
#include "Dem_Notifications_Implementation.h"
#include "Dem_Statistics_Implementation.h"
#include "Dem_Mem_Implementation.h"
#include "Dem_MemPermanent_Implementation.h"
#include "Dem_MemObdFreezeFrame_Implementation.h"

                                                  /* Subcomponents callbacks */
/* ------------------------------------------------------------------------- */
#include "Dem_Satellite_Interface.h"
#include "Dem_Error_Interface.h"
#include "Dem_Memory_Interface.h"

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
 * \addtogroup Dem_Event_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_Event_TestValidHandle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestValidHandle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  return (boolean)( (EventId != DEM_EVENT_INVALID)                                                                               /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
                 && (EventId < Dem_Cfg_GlobalEventCount()) );
}


#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_Event_TestMilSupport
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestMilSupport(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  return (boolean)(Dem_Cfg_GlobalMilIndicator() == Dem_Cfg_EventSpecialIndicator(EventId));
}
#endif

/* ****************************************************************************
 % Dem_Event_GetInternalStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_Event_GetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  return Dem_Cfg_GetEventInternalStatus(EventId);
}

/* ****************************************************************************
 % Dem_Event_SetInternalStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (EventId >= Dem_Cfg_GetSizeOfEventInternalStatus())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_SetEventInternalStatus(EventId, Status);                                                                             /* SBSW_DEM_ARRAY_WRITE_EVENTINTERNALSTATUS */
  }
}

/* Extended internal status  --------------------- */
/* ****************************************************************************
 % Dem_Event_GetExtendedStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_ExtendedStatusType, DEM_CODE)
Dem_Event_GetExtendedStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) || (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
  /* Return extended status of event  */
  return Dem_Cfg_GetStatusData().ExtendedEventStatus[EventId];
#else
  return DEM_EXT_STATUS_INITIALIZE;
#endif
}

/* ****************************************************************************
 % Dem_Event_SetExtendedStatus
 *****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetExtendedStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ExtendedStatusType, AUTOMATIC)  Status
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Status)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) || (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    /* Set extended status of event */
    Dem_Cfg_GetStatusData().ExtendedEventStatus[EventId] = Status;                                                               /* SBSW_DEM_ARRAY_WRITE_STATUSDATA_EXTENDEDEVENTSTATUS */
  }
#endif
}

#if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
/* ****************************************************************************
 % Dem_Event_GetTripCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
   */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_GetTripCount(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  return Dem_Cfg_GetStatusData().TripCount[EventId];
}
#endif

#if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
/* ****************************************************************************
 % Dem_Event_SetTripCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetTripCount(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  TripCount
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetStatusData().TripCount[EventId] = TripCount;                                                                      /* SBSW_DEM_ARRAY_WRITE_STATUSDATA_TRIPCOUNT */
  }
}
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_Event_GetQualifyStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_GetQualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
  return Dem_Cfg_GetStatusData().State[EventId];
# else
  return Dem_Cfg_GetEventCycleStatus(EventId);
# endif
}
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_Event_SetQualifyStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetQualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Status
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (EventId >= Dem_Cfg_EventCycleStatusCount())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
# if (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
    Dem_Cfg_GetStatusData().State[EventId] = Status;                                                                             /* SBSW_DEM_ARRAY_WRITE_STATUSDATA_STATE */
# else
    Dem_Cfg_SetEventCycleStatus(EventId, Status);                                                                                /* SBSW_DEM_ARRAY_WRITE_EVENTCYCLESTATUS */
# endif
  }
}
#endif

/* ****************************************************************************
 % Dem_Event_GetUDSStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_Event_GetUDSStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  return Dem_Cfg_GetStatusData().EventStatus[EventId];
}

/* ****************************************************************************
 % Dem_Event_SetUDSStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetUDSStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  Status
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (EventId >= Dem_Cfg_GlobalEventCount())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_GetStatusData().EventStatus[EventId] = Status;                                                                       /* SBSW_DEM_ARRAY_WRITE_STATUSDATA_EVENTSTATUS */
  }
}

/* ****************************************************************************
 % Dem_Event_GetExternalUDSStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_Event_GetExternalUDSStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  EventStatus
  )
{
#if (DEM_FEATURE_NEED_OBD == STD_ON)
    /* suppress not qualified status bits */
  return (Dem_UdsStatusByteType)(Dem_Event_GetQualifyStatus(EventId) & EventStatus);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return EventStatus;
#endif
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
 * \addtogroup Dem_Event_Private
 * \{
 */

/* ****************************************************************************
 % Dem_Event_TestSimilarConditions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestSimilarConditions(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
  if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
  {
    lReturnValue = (boolean)(((Dem_Event_GetExtendedStatus(EventId)) & DEM_EXT_STATUS_SIMILAR_CONDITIONS) != 0);
  }
  else
  {
    lReturnValue = TRUE;
  }
#else
  lReturnValue = TRUE;
#endif
  return lReturnValue;
}

#if (DEM_FEATURE_NEED_IMMEDIATEHEAL == STD_ON)
/* ****************************************************************************
 % Dem_Event_Passed_ProcessHealing
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
Dem_Event_Passed_ProcessHealing(
  CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext                                                           /* PRQA S 3673 */ /* MD_DEM_16.7_Design */
  )
{
  if (Dem_Cfg_EventHealingTarget(EventContext->EventId) == 0)
  {
# if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
    if ( (Dem_UDSStatus_Test_PDTC(EventContext->OldEventStatus) == TRUE) &&                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
         (Dem_Indicator_TestHasIndicator(EventContext->EventId) == TRUE) )
    {
      Dem_Event_SetTripCount(EventContext->EventId, 0);
    }
# endif

    if (Dem_UDSStatus_Test_WIR(EventContext->OldEventStatus) == TRUE)
    {
      Dem_UDSStatus_Type lNewEventStatus;

      lNewEventStatus = EventContext->NewEventStatus;
      lNewEventStatus = Dem_Event_Healed(EventContext->EventId, lNewEventStatus);
      EventContext->NewEventStatus = lNewEventStatus;                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* DEM_FEATURE_NEED_IMMEDIATEHEAL == STD_ON */

/* ****************************************************************************
 % Dem_Event_TestConfirmed
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
Dem_Event_TestConfirmed(
  CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext                                                           /* PRQA S 3673 */ /* MD_DEM_16.7_Design */
  )
{
  boolean lReturnValue;
  lReturnValue = FALSE;

  /* event is configured as single-trip */
  if (Dem_Cfg_EventTripTarget(EventContext->EventId) == 0)
  {
    lReturnValue = TRUE;
  }
  else
  {
    if (Dem_Event_TestSimilarConditions(EventContext->EventId) == TRUE)
    {
#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
      if (Dem_Cfg_EventMilGroupIndex(EventContext->EventId) != DEM_CFG_MIL_GROUP_INVALID)
      {
        if (Dem_Mem_GetMilGroupTripCount(Dem_Cfg_EventMilGroupIndex(EventContext->EventId)) >= Dem_Cfg_EventTripTarget(EventContext->EventId))
        {
          /* MIL Group is used and MIL group tripped */
          lReturnValue = TRUE;
        }
        /* else: event has a MIL group, but the group has not tripped yet */
      }
      else
#endif
      {
#if (DEM_CFG_SUPPORT_MULTITRIP == STD_ON)
        if (Dem_Event_GetTripCount(EventContext->EventId) >= Dem_Cfg_EventTripTarget(EventContext->EventId))
        {
          /* multi-trip target reached */
          lReturnValue = TRUE;
        }
#else
        if ( ((Dem_UDSStatus_Test_PDTC(EventContext->OldEventStatus)) == TRUE)                                                   /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          && ((Dem_UDSStatus_Test_TFTOC(EventContext->OldEventStatus)) == FALSE) )
        {
          /* event has tripped twice */
          lReturnValue = TRUE;
        }
#endif
      }
    }
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Event_OpCycleStart
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
Dem_Event_OpCycleStart(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint8 lOldEventStatus;
  uint8 lNewEventStatus;

  lOldEventStatus = Dem_Event_GetUDSStatus(EventId);

  lNewEventStatus = lOldEventStatus;
#if (DEM_CFG_SUPPORT_CLEAR_TESTFAILED_ON_OPCYCLE == STD_ON)
  lNewEventStatus = Dem_UDSStatus_Reset_TF(lNewEventStatus);
#endif
  lNewEventStatus = Dem_UDSStatus_Reset_TFTOC(lNewEventStatus);
  lNewEventStatus = Dem_UDSStatus_Set_TNCTOC(lNewEventStatus);

  Dem_Event_SetUDSStatus(EventId, lNewEventStatus);

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  {
    Dem_RatioIdIndexType lRatioIndex;
    lRatioIndex = Dem_Cfg_EventRatioIdIdx(EventId);

    if (lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)
    {
      /* reset all status bits of this ratio to the following setting:
       * - denominator not incremented
       * - denominator conditions not fulfilled
       * - denominator not locked
       * - numerator not incremented
       * - numerator conditions not fulfilled (no fault detected / detectable)
       * - ratio not locked by suppression
       * - ratio not locked by pending FID
       */
      Dem_Mem_SetIumprStatus(lRatioIndex, 0);
    }
  }
#endif

#if ( (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_FEATURE_NEED_CYCLEAUTOMATICEND == STD_ON) \
   || (DEM_CFG_SUPPORT_RESTART_CYCLE == STD_ON) )
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
#endif
  {
    Dem_SatelliteCore_RestartEvent(
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
#if (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON)
    {
      Dem_Event_InternalStatusType lInternalStatus;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */

      lInternalStatus = Dem_Event_GetInternalStatus(EventId);
      lInternalStatus = Dem_DTCInternalStatus_ResetFdcToc(lInternalStatus);
      Dem_Event_SetInternalStatus(EventId, lInternalStatus);

      Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
    }
#endif

  }

}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Event_ProcessHealing
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_ProcessHealing(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  EventStatus
  )
{
  uint8 lNewEventStatus;

  lNewEventStatus = EventStatus;
  {
#if (DEM_FEATURE_NEED_HEALINGCOUNTER == STD_ON)
    if (Dem_Event_GetTripCount(EventId) < 0xffU)
    {
      Dem_Event_SetTripCount(EventId, (uint8)(Dem_Event_GetTripCount(EventId) + 1));
    }
    if (Dem_Event_GetTripCount(EventId) >= Dem_Cfg_EventHealingTarget(EventId))
    {
      lNewEventStatus = Dem_Event_Healed(EventId, EventStatus);
    }
#else
    if (Dem_UDSStatus_Test_WIR(EventStatus) == TRUE)
    { /* Healing target reached -> heal all related indicators */
      lNewEventStatus = Dem_Event_Healed(EventId, lNewEventStatus);
    }
#endif
  }
  return lNewEventStatus;
}

/* ****************************************************************************
 % Dem_Event_OpCycleEnd_Healing
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
 */
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_OpCycleEnd_Healing(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  EventStatus
  )
{
  boolean lEventMayAge;
  uint8 lNewEventStatus;
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  boolean lClearObdFreezeFrame;

  lClearObdFreezeFrame = FALSE;
#endif
  lEventMayAge = FALSE;
  lNewEventStatus = EventStatus;

  if (Dem_UDSStatus_Test_TNCTOC(lNewEventStatus) == FALSE)
  {
    if (Dem_UDSStatus_Test_TFTOC(lNewEventStatus) == FALSE)
    { /* Event tested this operation cycle and was not failed, reset pending state */
      if (Dem_UDSStatus_Test_PDTC(lNewEventStatus) == TRUE)
      {
# if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
        Dem_Event_SetTripCount(EventId, 0);
# endif
# if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
        /* pending bit was set before and is now reset: reduce number of pending events in MIL group */
        if (Dem_Cfg_EventMilGroupIndex(EventId) != DEM_CFG_MIL_GROUP_INVALID)
        {
#  if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
          if (Dem_EventInternalStatus_GetMilGroupPendingCount(Dem_Cfg_EventMilGroupIndex(EventId)) <= 0)
          {
            Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                    /* SBSW_DEM_POINTER_RUNTIME_CHECK */
          }
#  endif
          Dem_Mem_DecrementMilGroupPendingCount(Dem_Cfg_EventMilGroupIndex(EventId));
        }
# endif

# if (DEM_FEATURE_NEED_PID01_CALCULATION  == STD_ON)
        if (Dem_Esm_TestPid01ReadinessState(Dem_Queue_Pid01UpdateFlag, Dem_Cfg_EventReadinessGroup(EventId)) == FALSE)
        {
          uint16 lDem_Queue_Pid01UpdateFlag;
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
          Dem_EnterCritical_DiagMonitor();                                                                                       /* PRQA S 3109 */ /* MD_MSR_14.3 */
          lDem_Queue_Pid01UpdateFlag = Dem_Esm_SetPid01ReadinessState(Dem_Queue_Pid01UpdateFlag, Dem_Cfg_EventReadinessGroup(EventId));
          Dem_Queue_SetPid01UpdateFlag(lDem_Queue_Pid01UpdateFlag);
          Dem_LeaveCritical_DiagMonitor();                                                                                       /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
        }
# endif  

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
        lClearObdFreezeFrame = TRUE;
#endif
      }

      lNewEventStatus = Dem_UDSStatus_Reset_PDTC(lNewEventStatus);
      lNewEventStatus = Dem_Event_ProcessHealing(EventId, lNewEventStatus);

      lEventMayAge = Dem_Event_TestEventMayAge(EventId, lNewEventStatus);
    }
    else
    {
      if (Dem_UDSStatus_Test_PDTC(lNewEventStatus) == TRUE)
      {
#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
        /* test failed; check if MIL group exists */
        if (Dem_Cfg_EventMilGroupIndex(EventId) != DEM_CFG_MIL_GROUP_INVALID)
        {
          /* increment MIL group trip counter once per DCY if trip target has not yet been reached */
          if (Dem_Mem_GetMilGroupTripCount(Dem_Cfg_EventMilGroupIndex(EventId)) < Dem_Cfg_EventTripTarget(EventId))
          {
            if (Dem_Mem_GetMilGroupIncremented(Dem_Cfg_EventMilGroupIndex(EventId)) == FALSE)
            {
              Dem_Mem_IncrementMilGroupTripCount(Dem_Cfg_EventMilGroupIndex(EventId));
              Dem_Mem_SetMilGroupIncremented(Dem_Cfg_EventMilGroupIndex(EventId));
            }
          }
        }
        else
#endif
#if (DEM_CFG_SUPPORT_MULTITRIP == STD_ON)
        {
          /* test failed: increment trip counter if trip target has not yet been reached */
          if (Dem_Event_GetTripCount(EventId) < Dem_Cfg_EventTripTarget(EventId))
          {
            Dem_Event_SetTripCount(EventId, (uint8)(Dem_Event_GetTripCount(EventId) + 1));
          }
        }
#endif
      }
    }

    Dem_Event_SetUDSStatus(EventId, lNewEventStatus);

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    if (lClearObdFreezeFrame == TRUE)
    {
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      Dem_Cfg_CombinedGroupIndexType lGroupId;
      lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
      if ( (lGroupId == DEM_CFG_COMBINED_GROUP_INVALID)                                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        || (Dem_UDSStatus_Test_PDTC(Dem_DTC_CalculateCombineGroupUdsStatus(lGroupId)) == FALSE) )
# endif
      {
        Dem_DTC_ClearOBDFreezeFrame(EventId);
      }
    }
#endif
  }

  return lEventMayAge;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Event_OpCycleEnd
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
Dem_Event_OpCycleEnd(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  OldDtcStatus                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  uint8 lEventStatus;
#if (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)
  boolean lEventMayAge;
#endif

  /* Argument unused in some configurations */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(OldDtcStatus)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lEventStatus = Dem_Event_GetUDSStatus(EventId);

  if (Dem_Event_TestSimilarConditions(EventId) == TRUE)
  {
#if (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)
    lEventMayAge = Dem_Event_OpCycleEnd_Healing(EventId, lEventStatus);
#else
    (void)Dem_Event_OpCycleEnd_Healing(EventId, lEventStatus);
#endif
  }
  else
  {
#if (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)
    lEventMayAge = FALSE;
#endif
  }

#if (DEM_FEATURE_NEED_AGING_TRIGGER_CYCLE == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
# if (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)
  if (lEventMayAge == TRUE)
# endif
  {
    Dem_DTC_OpCycleEnd_Aging(EventId, OldDtcStatus);
  }
#endif
}

/* ****************************************************************************
 % Dem_Event_InitEventContext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitEventContext(
CONST(Dem_EventIdType, AUTOMATIC)  EventId,
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
)
{
  EventContext->EventId = EventId;                                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  EventContext->OldEventStatus = Dem_Event_GetUDSStatus(EventId);                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  EventContext->OldExternalEventStatus = Dem_Event_GetExternalUDSStatus(EventId, EventContext->OldEventStatus);                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  EventContext->NewEventStatus = EventContext->OldEventStatus;                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  EventContext->EventEffects = DEM_CFG_TRIGGER_NONE;                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  EventContext->DataModified = FALSE;                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Event_CalculateStatusOnFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_CalculateStatusOnFailed(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
)
{
    /* Process the deferred 'asynchronous' status bit transitions for the event */
  EventContext->NewEventStatus = Dem_UDSStatus_Set_TFTOC(EventContext->NewEventStatus);                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  EventContext->NewEventStatus = Dem_UDSStatus_Set_TF(EventContext->NewEventStatus);                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#if (DEM_CFG_PROCESS_TFSLC_STOREDONLY == STD_OFF)
  EventContext->NewEventStatus = Dem_UDSStatus_Set_TFSLC(EventContext->NewEventStatus);                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
#endif
  EventContext->NewEventStatus = Dem_UDSStatus_Reset_TNCSLC(EventContext->NewEventStatus);                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  EventContext->NewEventStatus = Dem_UDSStatus_Reset_TNCTOC(EventContext->NewEventStatus);                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

  Dem_Event_SetUDSStatus(EventContext->EventId, EventContext->NewEventStatus);
}

/* ****************************************************************************
 % Dem_Event_CalculateFailedEffects
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_CalculateFailedEffects(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
)
{
#if (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON)
  /* If event is not stored already */
  if (Dem_DTC_TestStoredStatus(EventContext->EventId) == FALSE)
  {
    EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_TESTFAILED);                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE);                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_FIRSTTHISCYCLE);                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  else
#endif
  {
    /* Derive the triggers for the event from the changes of the status bits */
    if (Dem_UDSStatus_Test_TF(EventContext->OldEventStatus) == FALSE)
    {
      EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_TESTFAILED);                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    if (Dem_UDSStatus_Test_TFTOC(EventContext->OldEventStatus) == FALSE)
    {
      EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE);                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_FIRSTTHISCYCLE);                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
}

/* ****************************************************************************
 % Dem_Event_CalculateStatusOnFailed_OnStorage
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_CalculateStatusOnFailed_OnStorage(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
)
{
#if (DEM_CFG_PROCESS_TFSLC_STOREDONLY == STD_ON)
  if (Dem_DTC_TestStoredStatus(EventContext->EventId) == TRUE)
  {
    EventContext->NewEventStatus = Dem_UDSStatus_Set_TFSLC(EventContext->NewEventStatus);                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
#endif

  if ((EventContext->EventEffects & DEM_CFG_TRIGGER_PENDING) != 0)
  {
    EventContext->NewEventStatus = Dem_UDSStatus_Set_PDTC(EventContext->NewEventStatus);                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  if ((EventContext->EventEffects & DEM_CFG_TRIGGER_CONFIRMED) != 0)
  {
    EventContext->NewEventStatus = Dem_UDSStatus_Set_CDTC(EventContext->NewEventStatus);                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  if ((EventContext->EventEffects & DEM_CFG_TRIGGER_INDICATOR) != 0)
  {
    EventContext->NewEventStatus = Dem_UDSStatus_Set_WIR(EventContext->NewEventStatus);                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  Dem_Event_SetUDSStatus(EventContext->EventId, EventContext->NewEventStatus);
}

/* ****************************************************************************
 % Dem_Event_CalculateFailedEffects_OnStorage
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
Dem_Event_CalculateFailedEffects_OnStorage(
  CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
  )
{
  {
    /* Calculate effects for 'Pending' bit */
    if (Dem_UDSStatus_Test_PDTC(EventContext->OldEventStatus) == FALSE)
    {
      /* Not yet pending, set pending independently of TFTOC */
      EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_PENDING);                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
      /* increment number of MIL group events that are pending (at most 127 are possible) */
      if (Dem_Cfg_EventMilGroupIndex(EventContext->EventId) != DEM_CFG_MIL_GROUP_INVALID)
      {
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
        if (Dem_EventInternalStatus_GetMilGroupPendingCount(Dem_Cfg_EventMilGroupIndex(EventContext->EventId)) >= 0x7Fu)
        {
          Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                      /* SBSW_DEM_POINTER_RUNTIME_CHECK */
        }
# endif
        Dem_Mem_IncrementMilGroupPendingCount(Dem_Cfg_EventMilGroupIndex(EventContext->EventId));
      }
#endif
    }
#if (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON) && (DEM_CFG_PROCESS_PDTC_ALL_DTC == STD_ON)
    else if (Dem_DTC_TestStoredStatus(EventContext->EventId) == FALSE)
    {
      EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_PENDING);                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
#endif
    else
    {
      /* Nothing to do */
    }
  }

  {
    /* Calculate effects for 'Confirmed' and 'WIR' bit */
    boolean lEventConfirmed;
    lEventConfirmed = Dem_Event_TestConfirmed(EventContext);                                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    if (lEventConfirmed == TRUE)
    { /* Event has confirmed */
#if (DEM_FEATURE_NEED_INDICATORS == STD_ON)
      if (Dem_UDSStatus_Test_WIR(EventContext->OldEventStatus) == FALSE)
      {
        if (Dem_Indicator_TestHasIndicator(EventContext->EventId) == TRUE)
        {
          EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_INDICATOR);                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        }
      }
#endif

      if (Dem_UDSStatus_Test_CDTC(EventContext->OldEventStatus) == FALSE)
      {
        EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_CONFIRMED);                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      } /* else: No transition for confirmed dtc, so no update */
#if (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
      else if (Dem_DTC_TestStoredStatus(EventContext->EventId) == FALSE)
      {
        EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_CONFIRMED);                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      }
#endif
      else
      {
        /* Nothing to do */
      }
    } /* else: not yet confirmed, no further action */
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Event_ProcessFailedEffects
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
Dem_Event_ProcessFailedEffects(
CONSTP2CONST(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
)
{
#if (DEM_FEATURE_NEED_OBD == STD_ON)
  if (Dem_Cfg_EventObdRelated(EventContext->EventId) == TRUE)
  {
    Dem_Event_QualifyStatus(EventContext->EventId, EventContext->EventEffects);
  }
#endif

  if ((EventContext->EventEffects & DEM_CFG_TRIGGER_INDICATOR) != 0)
  {
#if (DEM_FEATURE_NEED_OBD == STD_ON)
    /* Suppress the Indicators if the driving cycle is not qualified yet */
    if (Dem_EventInternalStatus_Test_QualifyStatus_WIR(Dem_Event_GetQualifyStatus(EventContext->EventId)) == TRUE)
#endif /* (DEM_FEATURE_NEED_OBD == STD_ON) */
    {
      Dem_Indicator_IndicatorEnable(EventContext->EventId);
    }
  }

# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if ((EventContext->EventEffects & DEM_CFG_TRIGGER_INDICATOR) != 0)
  {
    if (Dem_Event_TestMilSupport(EventContext->EventId) == TRUE)
    { /* Always try to store a permanent DTC */
#  if (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
      if (Dem_Mem_GetPermanentActivationState() != FALSE)
#  endif
      {
        Dem_Data_PermanentEntryAdd(EventContext->EventId);
      }
    }
  }
# endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) */

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  /* increment counter only if event initially becomes confirmed or
     if it is still confirmed and test failed changes from 0 to 1 */
  if ( ((EventContext->EventEffects & DEM_CFG_TRIGGER_CONFIRMED) != 0)                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (((EventContext->EventEffects & DEM_CFG_TRIGGER_TESTFAILED) != 0)
    && (Dem_UDSStatus_Test_CDTC(EventContext->OldEventStatus) == TRUE)))
  {
    Dem_Esm_IncrementQualifiedActiveEventCount(EventContext->EventId);
  }
#endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventContext);                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Event_CalculateStatusOnPassed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_CalculateStatusOnPassed(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
)
{
  EventContext->NewEventStatus = Dem_UDSStatus_Reset_TF(EventContext->NewEventStatus);                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  EventContext->NewEventStatus = Dem_UDSStatus_Reset_TNCSLC(EventContext->NewEventStatus);                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  EventContext->NewEventStatus = Dem_UDSStatus_Reset_TNCTOC(EventContext->NewEventStatus);                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}

/* ****************************************************************************
 % Dem_Event_Passed_CalcEventEffects
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Passed_CalcEventEffects(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
)
{
  if (Dem_UDSStatus_Test_TF(EventContext->OldEventStatus) == TRUE)
  {
    EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_TESTPASSED);                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  if (Dem_UDSStatus_Test_TNCTOC(EventContext->OldEventStatus) == TRUE)
  {
    EventContext->EventEffects = (uint8)(EventContext->EventEffects | DEM_CFG_TRIGGER_FIRSTTHISCYCLE);                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}

/* ****************************************************************************
 % Dem_Event_ProcessPassedEffects
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_ProcessPassedEffects(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext                                                             /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
)
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventContext);                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  if ((EventContext->EventEffects & DEM_CFG_TRIGGER_TESTPASSED) != FALSE)
  {
    Dem_Esm_DecrementQualifiedActiveEventCount(EventContext->EventId, FALSE);
  }
#endif

#if (DEM_FEATURE_NEED_IMMEDIATEHEAL == STD_ON)
  if (Dem_Event_TestSimilarConditions(EventContext->EventId) == TRUE)
  {
    Dem_Event_Passed_ProcessHealing(EventContext);                                                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
  Dem_Prestore_StateSetDiscard();
#endif
}

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_Event_QualifyStatus
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
Dem_Event_QualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects
  )
{
# if (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF)
  Dem_DTCInternal_StoredStatusType lStoredStatus;

  lStoredStatus = Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(EventId));
  /* Event is currently active (normal case) or aging (happens with 0-Trip events) */
  if ( (lStoredStatus == Dem_DTCInternalStatus_StoredStatus_Active)
    || (lStoredStatus == Dem_DTCInternalStatus_StoredStatus_Aging) )
# endif
  {
    uint8 lEventQualifyStatus;

    lEventQualifyStatus = Dem_Event_GetQualifyStatus(EventId);

    if ((DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(Dem_OperationCycle_GetObdCycleStates()) == TRUE)                                  /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      || (Dem_Cfg_EventTripTarget(EventId) == 0) )
    {
      /* The event has confirmed */
      if ((Effects & DEM_CFG_TRIGGER_CONFIRMED) != 0)
      {
        lEventQualifyStatus = Dem_EventInternalStatus_Set_QualifyStatus_CDTC(lEventQualifyStatus);
# if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
        if ((Dem_Cfg_EventReadinessGroup(EventId) != DEM_CFG_READINESS_FLSYS)                                                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
            && (Dem_Cfg_EventReadinessGroup(EventId) != DEM_CFG_READINESS_CMPRCMPT))
        {
          Dem_Util_SetReadinessGroupCompleted(TRUE, Dem_Cfg_EventReadinessGroup(EventId), &Dem_Mem_GetPid01CompletedMask());     /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
        }
# endif
      }
      /* The event has requested the MIL */
      if ((Effects & DEM_CFG_TRIGGER_INDICATOR) != 0)
      {
        lEventQualifyStatus = Dem_EventInternalStatus_Set_QualifyStatus_WIR(lEventQualifyStatus);
      }
    }

    Dem_DTC_SetQualifyStatus(EventId, lEventQualifyStatus);

# if (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
    /* If configured that DTC status is independent from stored status, always set
     * NV status data block to DIRTY */
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_STATUS),
                                DEM_NVM_BLOCKSTATE_DIRTY);
# else
    {
      Dem_Cfg_MemoryIndexType lMemoryIndex;
      Dem_MemoryEntry_HandleType lMemoryEntryId;

      lMemoryIndex = Dem_Memory_FindIndex_Checked(EventId);
      lMemoryEntryId = Dem_MemoryEntry_GetId(lMemoryIndex);

      /* synchronize the qualification state with the primary memory entry */
      if (DEM_MEM_GET_QUALIFIED_MASK(Dem_MemoryEntry_GetState(lMemoryEntryId)) != lEventQualifyStatus)
      {
        Dem_MemoryEntry_SetState(lMemoryEntryId, DEM_MEM_SET_QUALIFIED_MASK(Dem_MemoryEntry_GetState(lMemoryEntryId), lEventQualifyStatus));
        Dem_Nvm_SetEventMemoryBlockState(lMemoryIndex, DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
      }
    }
# endif
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_FEATURE_NEED_OBD == STD_ON) */

/* ****************************************************************************
 % Dem_Event_InitAvailableNV
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitAvailableNV(
  void
  )
{
#if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
  Dem_EventIdType lEventId;
  uint16 lMaskIndex;
  uint16 lMaskIndex_End;

  lEventId = 0;
  lMaskIndex_End = Dem_Cfg_GlobalEventAvailableDataSize();

  for (lMaskIndex = 0; lMaskIndex < lMaskIndex_End; ++lMaskIndex)
  {
    Dem_EventIdType lEventId_End;
    uint8 lNvAvailableMask;

    lEventId_End = lEventId + 8;
    if (lEventId_End > Dem_Cfg_GlobalEventCount())
    {
      lEventId_End = Dem_Cfg_GlobalEventCount();
    }
    lNvAvailableMask = Dem_Mem_EventGetAvailableMask(lMaskIndex);

    while (lEventId < lEventId_End)
    {
      if ((lNvAvailableMask & 0x01) != 0)
      {
        boolean lMayDisconnect;
        lMayDisconnect = Dem_Event_MayDisconnect(lEventId);
        Dem_Event_SetDisconnectedBit(lEventId, lMayDisconnect);
      }
      else
      {
        Dem_Event_SetDisconnectedBit(lEventId, FALSE);
      }
      lNvAvailableMask = (uint8)(lNvAvailableMask >> 1);
      ++lEventId;
    }
  }
#endif
}

/* ****************************************************************************
 % Dem_Event_InitQualification
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitQualification(
  void
  )
{
#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_OFF)
  Dem_EventIdType lEventId;

  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  { /* Initialize the qualified status for all events */
    uint8 lEventQualifyStatus;

    lEventQualifyStatus = 0xFF;
    if (Dem_Cfg_EventObdRelated(lEventId) == TRUE)
    { /* only OBD related events supports the qualification of Confirmed and WIR bit */
      lEventQualifyStatus = Dem_EventInternalStatus_Reset_QualifyStatus_CDTC(lEventQualifyStatus);
      lEventQualifyStatus = Dem_EventInternalStatus_Reset_QualifyStatus_WIR(lEventQualifyStatus);
    }
    Dem_DTC_SetQualifyStatus(lEventId, lEventQualifyStatus);
  }
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Event_InitEventInternalStatus
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
Dem_Event_InitEventInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_FEATURE_NEED_EVENTAVAILABLE_DEFAULT == STD_ON)
  if (Dem_Cfg_EventAvailableByDefault(EventId) == FALSE)
  {
    Dem_Event_SetDisconnectedBit(EventId, Dem_Event_MayDisconnect(EventId));
    Dem_DtrIF_EventAvailabilityChanged(EventId);
  }
  else
  {
    Dem_Event_SetDisconnectedBit(EventId, FALSE);
  }
#endif
}

/* ****************************************************************************
 % Dem_Event_InitStatus_ResetStoredOnlyBits
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_Event_InitStatus_ResetStoredOnlyBits(
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  EventStatus
)
{
  Dem_UDSStatus_Type lReturnValue;
  lReturnValue = EventStatus;

  /* Note: this relies on the compiler to optimize the different bit operations into a single mask operation.
  * The intention is to find a dedicated access for each Bit modification for review purposes. */
# if (DEM_CFG_PROCESS_PDTC_STOREDONLY == STD_ON)
  lReturnValue = Dem_UDSStatus_Reset_PDTC(lReturnValue);
# endif
# if (DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON)
  lReturnValue = Dem_UDSStatus_Reset_CDTC(lReturnValue);
# endif
# if (DEM_CFG_PROCESS_TFSLC_STOREDONLY == STD_ON)
  lReturnValue = Dem_UDSStatus_Reset_TFSLC(lReturnValue);
# endif
  return lReturnValue;
}

#if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
/* ****************************************************************************
 % Dem_Event_InitStatus_AgedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_Event_InitStatus_AgedEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  EventStatus
)
{
  Dem_UDSStatus_Type lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = EventStatus;

# if (DEM_CFG_STORAGE_AT_CONFIRMED == STD_OFF)
    if ( (Dem_UDSStatus_Test_PDTC(EventStatus) == TRUE)                                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
#  if (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_ON)
      && (Dem_Cfg_EventAgingTarget(EventId) == 0) 
#  endif
       )
    {
      lReturnValue = Dem_UDSStatus_Reset_PDTC(lReturnValue);
      if (Dem_Cfg_EventHealingTarget(EventId) == 0)
      {
        if (Dem_UDSStatus_Test_WIR(EventStatus) == TRUE)
        {
          lReturnValue = Dem_UDSStatus_Reset_WIR(lReturnValue);
#  if (DEM_FEATURE_NEED_OBD == STD_ON)
          if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
          {
            Dem_Event_SetQualifyStatus(EventId, Dem_EventInternalStatus_Reset_QualifyStatus_WIR(Dem_Event_GetQualifyStatus(EventId)));
          }
#  endif
        }
      }
    }

#  if (DEM_CFG_PROCESS_TFSLC_ALL_DTC == STD_ON)
    lReturnValue = Dem_UDSStatus_Reset_TFSLC(lReturnValue);
#  endif
# endif

    lReturnValue = Dem_UDSStatus_Reset_CDTC(lReturnValue);
# if (DEM_FEATURE_NEED_OBD == STD_ON)
    if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
    {
      Dem_Event_SetQualifyStatus(EventId, Dem_EventInternalStatus_Reset_QualifyStatus_CDTC(Dem_Event_GetQualifyStatus(EventId)));
    }
# endif

# if (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)
#  if (DEM_FEATURE_NEED_AGING_AFTER_HEALING_MIL_ONLY == STD_ON)
    if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
#  endif
    {
      lReturnValue = Dem_UDSStatus_Reset_WIR(lReturnValue);
#  if (DEM_FEATURE_NEED_OBD == STD_ON)
      if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
      {
        Dem_Event_SetQualifyStatus(EventId, Dem_EventInternalStatus_Reset_QualifyStatus_WIR(Dem_Event_GetQualifyStatus(EventId)));
      }
#  endif
    }
# endif

# if (DEM_CFG_STORAGE_AT_CONFIRMED == STD_OFF) && (DEM_FEATURE_NEED_HEALINGCOUNTER == STD_ON)
    if ((Dem_UDSStatus_Test_PDTC(EventStatus) == TRUE)                                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
#  if (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_ON)
      && (Dem_Cfg_EventAgingTarget(EventId) == 0) 
#  endif
      )
    {
#  if (DEM_CFG_AGING_AFTER_HEALING_ALL_DTC == STD_OFF)
      if ( (Dem_Cfg_EventHealingTarget(EventId) != 0)                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        || ( (Dem_Cfg_EventHealingTarget(EventId) == 0)                                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          && (Dem_UDSStatus_Test_WIR(EventStatus) == TRUE) )                                                                     /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
#   if (DEM_FEATURE_NEED_AGING_AFTER_HEALING_MIL_ONLY == STD_ON)
        /* Obd relevant events have to heal before they can age */
        || ( (Dem_Cfg_EventHealingTarget(EventId) == 0)                                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          && (Dem_UDSStatus_Test_WIR(EventStatus) == FALSE)                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          && (Dem_Cfg_EventObdRelated(EventId) == TRUE) )
#   endif
        )
#  endif
      {
        Dem_Event_SetTripCount(EventId, 0);
      }
    }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */
#endif

/* ****************************************************************************
% Dem_Event_InitStatus_AgingEvent
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_Event_InitStatus_AgingEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  EventStatus
  )
{
  Dem_UDSStatus_Type lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = EventStatus;
  
#if (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_OFF)
  if (Dem_UDSStatus_Test_PDTC(EventStatus) == TRUE)
  {
    lReturnValue = Dem_UDSStatus_Reset_PDTC(lReturnValue);
    if (Dem_Cfg_EventHealingTarget(EventId) == 0)
    {
      if (Dem_UDSStatus_Test_WIR(EventStatus) == TRUE)
      {
        lReturnValue = Dem_UDSStatus_Reset_WIR(lReturnValue);
# if (DEM_FEATURE_NEED_OBD == STD_ON)
        if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
        {
          Dem_Event_SetQualifyStatus(EventId, Dem_EventInternalStatus_Reset_QualifyStatus_WIR(Dem_Event_GetQualifyStatus(EventId)));
        }
# endif
      }
    }
  }

# if (DEM_FEATURE_NEED_HEALINGCOUNTER == STD_ON)
    if (Dem_UDSStatus_Test_PDTC(EventStatus) == TRUE)
    {
#  if (DEM_CFG_AGING_AFTER_HEALING_ALL_DTC == STD_OFF)
      if ((Dem_Cfg_EventHealingTarget(EventId) != 0)                                                                             /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        ||((Dem_Cfg_EventHealingTarget(EventId) == 0)                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_UDSStatus_Test_WIR(EventStatus) == TRUE))                                                                        /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
#   if (DEM_FEATURE_NEED_AGING_AFTER_HEALING_MIL_ONLY == STD_ON)
        /* Obd relevant events have to heal before they can age */
        ||((Dem_Cfg_EventHealingTarget(EventId) == 0)                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_UDSStatus_Test_WIR(EventStatus) != TRUE)                                                                         /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_Cfg_EventObdRelated(EventId) == TRUE))
#   endif
        )
#  endif
      {
        Dem_Event_SetTripCount(EventId, 0);
      }
    }
# endif
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Event_InitStatus_UpdateIndicators
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
Dem_Event_InitStatus_UpdateIndicators(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
# if (DEM_FEATURE_NEED_OBD == STD_ON)
  /* Suppress the Indicator updates, if the warningIndicator is not qualified yet */
  if (Dem_EventInternalStatus_Test_QualifyStatus_WIR(Dem_Event_GetQualifyStatus(EventId)) == TRUE)
# endif /* (DEM_FEATURE_NEED_OBD == STD_ON) */
  {
    Dem_Indicator_UserIndicatorEnable(EventId);
    (void)Dem_Indicator_SpecialIndicatorEnable(EventId);
  }
}

#if (DEM_FEATURE_NEED_INDICATORS == STD_ON) && (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 % Dem_Event_InitStatus_UpdateMilGroups
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
Dem_Event_InitStatus_UpdateMilGroups(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  if (Dem_Cfg_EventMilGroupIndex(EventId) != DEM_CFG_MIL_GROUP_INVALID)
  {
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
    if (Dem_EventInternalStatus_GetMilGroupPendingCount(Dem_Cfg_EventMilGroupIndex(EventId)) >= 0x7FU)
    {
      Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                          /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    }
# endif
    Dem_Mem_IncrementMilGroupPendingCount(Dem_Cfg_EventMilGroupIndex(EventId));
  }
}
#endif

/* ****************************************************************************
 % Dem_Event_InitEventStatus
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
Dem_Event_InitEventStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_UDSStatus_Type lEventStatus;

  lEventStatus = Dem_Event_GetUDSStatus(EventId);
  if (Dem_Cfg_EventAvailableByVariant(EventId) == FALSE)
  {
    lEventStatus = 0x00;
    Dem_DtrIF_EventAvailabilityChanged(EventId);
  }
  else
  {
    Dem_DTCInternal_StoredStatusType lAgedStatus;                                                                                /* PRQA S 3203 */ /* MD_DEM_3203 */
    lAgedStatus = Dem_DTCInternalStatus_GetStoredStatus(Dem_DTC_GetInternalStatus(EventId));                                     /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

    switch (lAgedStatus)
    {
    case Dem_DTCInternalStatus_StoredStatus_None:
      /* Initialize event status of aging and non aging events without memory entry */
      lEventStatus = Dem_Event_InitStatus_ResetStoredOnlyBits(lEventStatus);
#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
      /* Initialize event status of aging events without memory entry */
      if (Dem_DTC_GetAgingStatus(EventId) == Dem_DTC_AgingStatusInProgress)
      {
        lEventStatus = Dem_Event_InitStatus_AgingEvent(EventId, lEventStatus);
      }
#endif
      break;

#if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
      /* Initialize event status of aged events with memory entry */
    case Dem_DTCInternalStatus_StoredStatus_Aged:
      lEventStatus = Dem_Event_InitStatus_AgedEvent(EventId, lEventStatus);
      break;
#endif

      /* Initialize event status of aging events with memory entry */
    case Dem_DTCInternalStatus_StoredStatus_Aging:
      lEventStatus = Dem_Event_InitStatus_AgingEvent(EventId, lEventStatus);
      break;

    default:
      break;
    }
  }

#if (DEM_CFG_SUPPORT_TESTFAILED_STORAGE != STD_ON)
  lEventStatus = Dem_UDSStatus_Reset_TF(lEventStatus);
#endif

  if ((lEventStatus & (DEM_UDS_STATUS_TFTOC | DEM_UDS_STATUS_TNCTOC)) == (DEM_UDS_STATUS_TFTOC | DEM_UDS_STATUS_TNCTOC))
  { /* Test not completed, but failed this cycle is not a consistent state.
    *  Reset TFTOC to restore consistency. This also makes sure a new test result is processed */
    lEventStatus = Dem_UDSStatus_Reset_TFTOC(lEventStatus);
  }

  if ((lEventStatus & (DEM_UDS_STATUS_TFSLC | DEM_UDS_STATUS_TNCSLC)) == (DEM_UDS_STATUS_TFSLC | DEM_UDS_STATUS_TNCSLC))
  { /* Test not completed, but failed since last clear is not a consistent state.
    *  Reset TNCSLC to restore consistency. Keep TFSLC since it is sometimes set by correction code */
    lEventStatus = Dem_UDSStatus_Reset_TNCSLC(lEventStatus);
  }

  if (Dem_Indicator_TestHasIndicator(EventId) == FALSE)
  {
    lEventStatus = Dem_UDSStatus_Reset_WIR(lEventStatus);
#  if (DEM_FEATURE_NEED_OBD == STD_ON)
    if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
    {
      Dem_Event_SetQualifyStatus(EventId, Dem_EventInternalStatus_Reset_QualifyStatus_WIR(Dem_Event_GetQualifyStatus(EventId)));
    }
#  endif
  }

  Dem_Event_SetUDSStatus(EventId, lEventStatus);

  if (Dem_UDSStatus_Test_WIR(lEventStatus) == TRUE)
  {
    Dem_Event_InitStatus_UpdateIndicators(EventId);
  }

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  /* count qualified confirmed & failed events */
  Dem_Esm_IncrementQualifiedActiveEventCount(EventId);
#endif /* (DEM_CFG_SUPPORT_WWHOBD == STD_ON) */

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
  if (Dem_UDSStatus_Test_PDTC(lEventStatus) == TRUE)
  {
    Dem_Event_InitStatus_UpdateMilGroups(EventId);
  }
#endif /* (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON) */
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_Event_ProcessEventAvailable
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
Dem_Event_ProcessEventAvailable(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
  if (Dem_EventInternalStatus_TestAvailabilityChanged(Dem_Event_GetInternalStatus(EventId)) == TRUE)
  {
    Dem_Event_InternalStatusType lInternalStatus;
    boolean lNewDisconnectedStatus;

/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */

    lInternalStatus = Dem_Event_GetInternalStatus(EventId);
    lInternalStatus = Dem_EventInternalStatus_ResetAvailabilityChanged(lInternalStatus);
    Dem_Event_SetInternalStatus(EventId, lInternalStatus);

    lNewDisconnectedStatus = (boolean)(Dem_EventInternalStatus_TestEventDisconnected(lInternalStatus) == TRUE);
    if (lNewDisconnectedStatus == TRUE)
    {
      /* Dtc was disconnected */
      Dem_DTC_Disconnect(EventId);

      if (Dem_Cfg_EventPrestorageIndex(EventId) != DEM_PRESTORE_NOT_CONFIGURED_FOR_EVENT)
      {
        (void)Dem_Prestore_EventPrestorageClear(EventId);
      }

# if (DEM_FEATURE_NEED_IUMPR == STD_ON)
      {
        /* If the DTC has a Ratio, disable the IUMPR calculation */
        Dem_RatioIdIndexType  lRatioIndex;

        lRatioIndex = Dem_Cfg_EventRatioIdIdx(EventId);
        if (lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)
        {
          Dem_Mem_SetIumprStatus(lRatioIndex, DEM_ESM_SET_IUMPR_DISCONNECTED(Dem_Mem_GetIumprStatus(lRatioIndex)));
        }
      }
# endif
    }
    else
    {
      /* Event was reconnected */
      Dem_DTC_Reconnect(EventId);

# if (DEM_FEATURE_NEED_IUMPR == STD_ON)
      {
        Dem_RatioIdIndexType  lRatioIndex;

        lRatioIndex = Dem_Cfg_EventRatioIdIdx(EventId);

        if (lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)
        {
          Dem_Mem_SetIumprStatus(lRatioIndex, DEM_ESM_RESET_IUMPR_DISCONNECTED(Dem_Mem_GetIumprStatus(lRatioIndex)));
        }
      }
# endif
    }

    Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

    Dem_Notifications_EventAvailabilityChanged(EventId, lNewDisconnectedStatus);
  }
}                                                                                                                                /* PRQA S 6080, 6050 */ /* MD_MSR_STMIF, MD_MSR_STCAL */
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
 * \addtogroup Dem_Event_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Event_TestEventMayAge
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
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_TestEventMayAge(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  EventStatus                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  boolean lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventStatus)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_FEATURE_NEED_HEALING == STD_ON) && (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)                                     /* PRQA S 0883 */ /* MD_DEM_19.15 */
  
  if ( (Dem_UDSStatus_Test_WIR(EventStatus) == TRUE)                                                                             /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
# if (DEM_FEATURE_NEED_AGING_AFTER_HEALING_MIL_ONLY == STD_ON)
    && (Dem_Cfg_EventObdRelated(EventId) == TRUE) 
# endif
     )
  {
    lReturnValue = FALSE;
  }
  else
  if ( (Dem_UDSStatus_Test_CDTC(EventStatus) == TRUE)                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
# if (DEM_CFG_AGING_AFTER_HEALING_ALL_DTC == STD_OFF)
    && (Dem_Cfg_EventObdRelated(EventId) == TRUE)
# endif
    )
  {
#  if (DEM_FEATURE_NEED_IMMEDIATEHEAL == STD_ON)
    if (Dem_Cfg_EventHealingTarget(EventId) == 0)
    {
      lReturnValue = (boolean)( (Dem_UDSStatus_Test_TF(EventStatus) == FALSE)                                                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
                             && (Dem_UDSStatus_Test_TNCTOC(EventStatus) == FALSE) );
    }
    else /* Dem_Cfg_EventHealingTarget(EventId) > 0 */
#  endif
    {
#  if (DEM_FEATURE_NEED_HEALINGCOUNTER == STD_ON)
      /* TripCount is the healing counter when PDTC == false */
      lReturnValue = (boolean)( (Dem_Event_GetTripCount(EventId) >= Dem_Cfg_EventHealingTarget(EventId))                         /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
                             && (Dem_UDSStatus_Test_PDTC(EventStatus) == FALSE) );
#  else
      lReturnValue = (Dem_UDSStatus_Test_PDTC(EventStatus) == FALSE);
#  endif
    }
  }
  else
  {
    lReturnValue = TRUE;
  }
#elif (DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON)
  lReturnValue = TRUE;
#else
  lReturnValue = FALSE;
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_Event_Disconnect_Normal
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
Dem_Event_Disconnect_Normal(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Event_InternalStatusType lInternalStatus;

  lInternalStatus = Dem_Event_GetInternalStatus(EventId);
  lInternalStatus = Dem_DTCInternalStatus_ResetFdcToc(lInternalStatus);
  Dem_Event_SetInternalStatus(EventId, lInternalStatus);

  Dem_SatelliteCore_ClearEvent(
      Dem_Cfg_EventSatelliteId(EventId),
      Dem_Cfg_EventSatelliteEventId(EventId));

  if(Dem_Cfg_EventObdRelated(EventId) == TRUE)
  {
    Dem_Event_SetExtendedStatus(EventId, 
      Dem_EventInternalStatus_ResetSimilarConditions(
      Dem_Event_GetExtendedStatus(EventId)
      )
      );
  }
  Dem_Event_SetUDSStatus(EventId, 0x00U);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif


#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_Event_Reconnect_Normal
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Reconnect_Normal(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Event_SetUDSStatus(EventId, 0x50U);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_Event_TestEventAvailable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestEventAvailable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
  lReturnValue = (boolean)(Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE);
#else
  lReturnValue = TRUE;
#endif
  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 % Dem_Event_TestEventSuppressed
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
Dem_Event_TestEventSuppressed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  lReturnValue = (boolean)                                                                                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
     ( (Dem_DTCInternalStatus_TestDtcSuppressed(Dem_Event_GetInternalStatus(EventId)) == TRUE)
    || (Dem_Cfg_EventAvailableByVariant(EventId) == FALSE)
    || ( (Dem_Event_TestEventAvailable(EventId) == FALSE)
      && (Dem_DTCInternalStatus_GetStoredStatus(Dem_Event_GetInternalStatus(EventId))
              == Dem_DTCInternalStatus_StoredStatus_None) )
      );
  return lReturnValue;
}
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) || (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
/* ****************************************************************************
 % Dem_Event_TestEventUnavailable
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
Dem_Event_TestEventUnavailable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;
  lReturnValue = (boolean)                                                                                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
     ( (Dem_Cfg_EventAvailableByVariant(EventId) == FALSE)
    || ( (Dem_Event_TestEventAvailable(EventId) == FALSE)
      && (Dem_DTCInternalStatus_GetStoredStatus(Dem_Event_GetInternalStatus(EventId))
              == Dem_DTCInternalStatus_StoredStatus_None) )
     );
  return lReturnValue;
}
#endif

#if (DEM_FEATURE_NEED_EVENTAVAILABLE_DEFAULT == STD_ON) || (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
/* ****************************************************************************
 % Dem_Event_SetDisconnectedBit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetDisconnectedBit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  IsDisconnected
  )
{
  Dem_Event_InternalStatusType lInternalStatus;
  lInternalStatus = Dem_Event_GetInternalStatus(EventId);

  if (IsDisconnected == TRUE)
  {
    lInternalStatus = Dem_EventInternalStatus_SetEventDisconnected(lInternalStatus);
    Dem_Event_SetUDSStatus(EventId, 0x00);
  }
  else
  {
    lInternalStatus = Dem_EventInternalStatus_ResetEventDisconnected(lInternalStatus);
  }

  Dem_Event_SetInternalStatus(EventId, lInternalStatus);
  Dem_DtrIF_EventAvailabilityChanged(EventId);
}
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_Event_MayDisconnect
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
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_MayDisconnect(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;
  uint8 lEventStatus;
  Dem_Event_InternalStatusType lInternalStatus;

  lInternalStatus = Dem_DTC_GetInternalStatus(EventId);
  lEventStatus = Dem_Event_GetUDSStatus(EventId);

  if ( (Dem_UDSStatus_Test_TF(lEventStatus) == FALSE)                                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_UDSStatus_Test_WIR(lEventStatus) == FALSE)
    && (Dem_UDSStatus_Test_CDTC(lEventStatus) == FALSE)
    )
  {
    if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) == Dem_DTCInternalStatus_StoredStatus_None)
    {
      lReturnValue = TRUE;
    }
    else
    {
      lReturnValue = Dem_DTC_TestRemainingEventforDtc(EventId);
    }
  }
  else
  {
    lReturnValue = FALSE;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_Event_Disconnect
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_Disconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Event_InternalStatusType lEventInternalStatus;

  lEventInternalStatus = Dem_Event_GetInternalStatus(EventId);
  if (Dem_EventInternalStatus_TestEventDisconnected(lEventInternalStatus) == FALSE)
  {
    if ( ((Dem_InitState_TestMasterInState(DEM_INITSTATE_PREINITIALIZED) == TRUE) || (Dem_Event_MayDisconnect(EventId) == TRUE)) /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_EventInternalStatus_TestAvailabilityChanged(lEventInternalStatus) == FALSE) )
    {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */
      lEventInternalStatus = Dem_Event_GetInternalStatus(EventId);
      lEventInternalStatus = Dem_EventInternalStatus_SetEventDisconnected(lEventInternalStatus);
      lEventInternalStatus = Dem_EventInternalStatus_SetAvailabilityChanged(lEventInternalStatus);
      Dem_Event_SetInternalStatus(EventId, lEventInternalStatus);
      Dem_LeaveCritical_DiagMonitor();                                                                                           /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */
      
      Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_Event);

# if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
      {
        uint8 lNvAvailableMask;
        lNvAvailableMask = Dem_Mem_EventGetAvailableMask(EventId / 8u);
        lNvAvailableMask = (uint8)(lNvAvailableMask | DEM_BIT(EventId % 8u));
        Dem_Mem_EventSetAvailableMask(EventId / 8u, lNvAvailableMask);
        Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AVAILABILITY),
                                    DEM_NVM_BLOCKSTATE_DIRTY);
      }
# endif
# if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
      {
        uint16 lDem_Queue_Pid01UpdateFlag;
        /* If major monitor enabled by configuration mark readiness group of event to recalculate readiness state */
        lDem_Queue_Pid01UpdateFlag = Dem_Esm_SetPid01ReadinessState(Dem_Queue_Pid01UpdateFlag, Dem_Cfg_EventReadinessGroup(EventId));
        Dem_Queue_SetPid01UpdateFlag(lDem_Queue_Pid01UpdateFlag);
      }
# endif

      Dem_DtrIF_EventAvailabilityChanged(EventId);

      lReturnValue = E_OK;
    }
    else
    {
      lReturnValue = E_NOT_OK;
    }
  }
  else
  {
    lReturnValue = E_OK;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) */

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_Event_Reconnect
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
Dem_Event_Reconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Event_InternalStatusType lEventInternalStatus;

  lEventInternalStatus = Dem_Event_GetInternalStatus(EventId);
  if ( (Dem_EventInternalStatus_TestEventDisconnected(lEventInternalStatus) == TRUE)                                             /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_EventInternalStatus_TestAvailabilityChanged(lEventInternalStatus) == FALSE) )
  {
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
    Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
    lEventInternalStatus = Dem_Event_GetInternalStatus(EventId);
    lEventInternalStatus = Dem_EventInternalStatus_ResetEventDisconnected(lEventInternalStatus);
    lEventInternalStatus = Dem_EventInternalStatus_SetAvailabilityChanged(lEventInternalStatus);
    Dem_Event_SetInternalStatus(EventId, lEventInternalStatus);
    Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

    Dem_Scheduler_EnableTaskOnce(Dem_Scheduler_Task_Event);

# if (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
    {
      uint8 lNvAvailableMask;
      lNvAvailableMask = Dem_Mem_EventGetAvailableMask(EventId / 8u);
      lNvAvailableMask = (uint8)(lNvAvailableMask & DEM_BIT_MASK(EventId % 8u, DEM_1BYTE));
      Dem_Mem_EventSetAvailableMask(EventId / 8u, lNvAvailableMask);
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_AVAILABILITY),
                                  DEM_NVM_BLOCKSTATE_DIRTY);
    }
# endif

# if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
    if ((Dem_Cfg_EventReadinessGroup(EventId) != DEM_CFG_READINESS_FLSYS)                                                        /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_Cfg_EventReadinessGroup(EventId) != DEM_CFG_READINESS_CMPRCMPT))
    {
      Dem_Util_SetReadinessGroupCompleted(FALSE, Dem_Cfg_EventReadinessGroup(EventId), &Dem_Mem_GetPid01CompletedMask());        /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
    }
# endif

    Dem_DtrIF_EventAvailabilityChanged(EventId);
    Dem_DtrIF_ResetDtrsOfEvent(EventId);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) */

/* ****************************************************************************
 % Dem_Event_ProcessFdc
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
Dem_Event_ProcessFdc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  FdcThresholdExceeded,
  CONST(boolean, AUTOMATIC)  FdcMaximumExceeded
  )
{
#if (DEM_FEATURE_NEED_FDC_TRIP == STD_ON)
  Dem_Event_InternalStatusType lOldEventInternalStatus;
  Dem_Event_InternalStatusType lNewEventInternalStatus;

/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */
  {

    lOldEventInternalStatus = Dem_Event_GetInternalStatus(EventId);
    lNewEventInternalStatus = lOldEventInternalStatus;
    if (FdcThresholdExceeded == TRUE)
    {
      lNewEventInternalStatus = Dem_DTCInternalStatus_SetFdcToc(lNewEventInternalStatus);
    }
    Dem_Event_SetInternalStatus(EventId, lNewEventInternalStatus);
  }
  Dem_LeaveCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

  /* no events without a DTC attached, disabled storage conditions, dtc/event suppressed... */
  if ( (Dem_Cfg_EventUdsDtc(EventId) != DEM_CFG_DTC_UDS_INVALID)                                                                 /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        /* Don't store with disabled storage conditions */
    && (Dem_StorageCondition_TestEventStorageConditionsFulfilled(EventId) == TRUE) )
  {
# if (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON) || (DEM_CFG_STORAGE_AT_FDC == STD_ON)
    if (FdcThresholdExceeded == TRUE)
    {
      /* Pass 'TRUE' if the old bit is false, so the status change did happen just now */
      Dem_DTC_FdcTrip(EventId, (boolean)(Dem_DTCInternalStatus_TestFdcToc(lOldEventInternalStatus) == FALSE));
    }
# endif
# if (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
    if (FdcMaximumExceeded == TRUE)
    {
      Dem_DTC_UpdateFdcMax(EventId);
    }
# else
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(FdcMaximumExceeded)                                                                         /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FdcThresholdExceeded)                                                                         /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FdcMaximumExceeded)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Event_Passed
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Event_Passed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  if (Dem_Event_TestLatchedTestFailed(EventId) == FALSE)
  {
    Dem_Event_ContextType lEventContext;
    Dem_DTC_ContextType lDTCContext;

    Dem_Event_InitEventContext(EventId, &lEventContext);                                                                         /* SBSW_DEM_POINTER_FORWARD_STACK */
    Dem_DTC_InitDTCContext(EventId, &lDTCContext);                                                                               /* SBSW_DEM_POINTER_FORWARD_STACK */

    Dem_Event_CalculateStatusOnPassed(&lEventContext);                                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
    Dem_Event_Passed_CalcEventEffects(&lEventContext);                                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */

#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_OFF) 
    if (lEventContext.OldEventStatus != lEventContext.NewEventStatus)
#endif
    {
      Dem_Event_ProcessPassedEffects(&lEventContext);                                                                            /* SBSW_DEM_POINTER_FORWARD_STACK */

      Dem_Event_SetUDSStatus(lEventContext.EventId, lEventContext.NewEventStatus);

      Dem_DTC_CalculateDTCStatus(&lDTCContext);                                                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
      Dem_DTC_Passed_CalcDTCEffects_VCC(&lDTCContext, lEventContext.EventEffects);                                               /* SBSW_DEM_POINTER_FORWARD_STACK */
#endif
      Dem_Notifications_EventStatusChanged(lEventContext.EventId, 
                                           lEventContext.OldExternalEventStatus, 
                                           Dem_Event_GetExternalUDSStatus(lEventContext.EventId, lEventContext.NewEventStatus));
      if (lEventContext.DataModified == TRUE)
      {
        Dem_Notifications_EventDataChanged(lEventContext.EventId);
      }
      Dem_Notifications_DtcStatusChanged(lDTCContext.EventId, 
                                         lDTCContext.OldExternalDtcStatus,
                                         Dem_DTC_ApplyExternalOnlyStatus(lDTCContext.EventId, lDTCContext.NewDtcStatus), 
                                         DEM_NOTIFICATIONS_DTC_UPDATED);

      Dem_DTC_Passed_ProcessDTCEffects(&lDTCContext);                                                                            /* SBSW_DEM_POINTER_FORWARD_STACK */
    }

    if (Dem_UDSStatus_IsNvRelevantStatusChange(lEventContext.OldEventStatus, lEventContext.NewEventStatus) == TRUE)
    {
      Dem_Nvm_SetStatusBlockChanged();
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Event_Healed
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
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Event_Healed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  CONST(uint8, AUTOMATIC)  EventStatus
  )
{
  uint8 lNewEventStatus;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lNewEventStatus = EventStatus;
  if (Dem_UDSStatus_Test_WIR(EventStatus) == TRUE)
  {
    lNewEventStatus = Dem_UDSStatus_Reset_WIR(lNewEventStatus);

#if (DEM_FEATURE_NEED_OBD == STD_ON)
    if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
    { /* only OBD related events supports the qualification of Confirmed and WIR bit */
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      Dem_Cfg_CombinedGroupIndexType lGroupId;
      Dem_DTC_UDSStatusType lDtcStatus;

      lDtcStatus= 0;
      lGroupId = Dem_Cfg_EventCombinedGroup(EventId);
      if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
      {
        Dem_Cfg_CombinedGroupIterType lCombinedIter;
        Dem_EventIdType lSubEventId;

        for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
          Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */

          if ((lSubEventId != EventId)                                                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
            && (Dem_Cfg_EventAvailableByVariant(lSubEventId) == TRUE)
            && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lSubEventId)) == FALSE))
          {
            lDtcStatus = (Dem_DTC_UDSStatusType)(lDtcStatus | Dem_Event_GetUDSStatus(lSubEventId));
          }
        }
      }

      if (Dem_UDSStatus_Test_WIR(lDtcStatus) == FALSE)
# endif
      {
        Dem_DTC_SetQualifyStatus(EventId, Dem_EventInternalStatus_Reset_QualifyStatus_WIR(Dem_Event_GetQualifyStatus(EventId)));
      }
    }
#endif

    Dem_Indicator_IndicatorDisable(EventId);
  }
  return lNewEventStatus;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Event_Failed
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
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Event_Failed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Event_ContextType lEventContext;
  Dem_DTC_ContextType lDTCContext;

  Dem_Event_InitEventContext(EventId, &lEventContext);                                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
  Dem_DTC_InitDTCContext(EventId, &lDTCContext);                                                                                 /* SBSW_DEM_POINTER_FORWARD_STACK */

  Dem_Event_CalculateStatusOnFailed(&lEventContext);                                                                             /* SBSW_DEM_POINTER_FORWARD_STACK */
  Dem_DTC_CalculateDTCStatus(&lDTCContext);                                                                                      /* SBSW_DEM_POINTER_FORWARD_STACK */

  Dem_Event_CalculateFailedEffects(&lEventContext);                                                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
  Dem_DTC_CalculateFailedEffects(&lDTCContext, lEventContext.EventEffects);                                                      /* SBSW_DEM_POINTER_FORWARD_STACK */

  if (Dem_UDSStatus_IsNvRelevantStatusChange(lEventContext.OldEventStatus, lEventContext.NewEventStatus) == TRUE)
  {
    Dem_Nvm_SetStatusBlockChanged();
  }

  /* Invalidate aging counter on a test failed trigger */
#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  if ((lDTCContext.DtcEffects & DEM_CFG_TRIGGER_TESTFAILED) != 0)
  {
    Dem_DTC_TestAndInvalidateAgingCounter(EventId);
  }
#endif

  if ( (lEventContext.OldEventStatus != lEventContext.NewEventStatus)                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
#if (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON)
    || (Dem_DTC_TestStoredStatus(EventId) == FALSE)
#endif
      )
  {
# if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
    if (Dem_UDSStatus_Test_PDTC(lEventContext.OldEventStatus) == FALSE)
    {
      /* Initialize trip counter */
      Dem_Event_SetTripCount(EventId, 0);
    }
# endif
    if ( (Dem_Cfg_EventUdsDtc(EventId) != DEM_CFG_DTC_UDS_INVALID)                                                               /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_StorageCondition_TestEventStorageConditionsFulfilled(EventId) == TRUE))
    {
      Dem_Event_CalculateFailedEffects_OnStorage(&lEventContext);                                                                /* SBSW_DEM_POINTER_FORWARD_STACK */
      Dem_DTC_CalculateFailedEffects_OnStorage(&lDTCContext, lEventContext.EventEffects);                                        /* SBSW_DEM_POINTER_FORWARD_STACK */

      Dem_DTC_ProcessStorage(&lEventContext, &lDTCContext);                                                                      /* SBSW_DEM_POINTER_FORWARD_STACK */

      Dem_Event_CalculateStatusOnFailed_OnStorage(&lEventContext);                                                               /* SBSW_DEM_POINTER_FORWARD_STACK */
      Dem_DTC_CalculateDTCStatus(&lDTCContext);                                                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */


      if (lDTCContext.DtcEffects != DEM_CFG_TRIGGER_NONE)
      {
        Dem_DTC_ProcessFailedEffects(&lDTCContext);                                                                              /* SBSW_DEM_POINTER_FORWARD_STACK */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
        if (Dem_Event_TestMilSupport(EventId) == TRUE)
        {
          if ((Dem_UDSStatus_Test_CDTC(lDTCContext.OldDtcStatus) == FALSE)                                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
            && (Dem_UDSStatus_Test_CDTC(lDTCContext.NewDtcStatus) == TRUE))
          {
            Dem_EventIdType lMasterEventId;
            lMasterEventId = Dem_Cfg_GetMasterEvent(EventId);
            Dem_Memory_ConfirmedChronoAddEvent(lMasterEventId);
          }
        }
#endif
      }

      if (lEventContext.EventEffects != DEM_CFG_TRIGGER_NONE)
      {
        Dem_Event_ProcessFailedEffects(&lEventContext);                                                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
      }
      Dem_Statistics_UpdateGlobalFailureStatistics(lEventContext.EventId, lEventContext.EventEffects);
#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
      Dem_Prestore_StateSetDiscard();
#endif
      Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_STATUS),
                                  DEM_NVM_BLOCKSTATE_DIRTY);
    }
  }
  Dem_Notifications_EventStatusChanged(lEventContext.EventId, 
                                       lEventContext.OldExternalEventStatus, 
                                       Dem_Event_GetExternalUDSStatus(lEventContext.EventId, lEventContext.NewEventStatus));
  if (lEventContext.DataModified == TRUE)
  {
    Dem_Notifications_EventDataChanged(lEventContext.EventId);
  }
  Dem_Notifications_DtcStatusChanged(lDTCContext.EventId, 
                                     lDTCContext.OldExternalDtcStatus,
                                     Dem_DTC_ApplyExternalOnlyStatus(lDTCContext.EventId, lDTCContext.NewDtcStatus), 
                                     DEM_NOTIFICATIONS_DTC_UPDATED);
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPTH */

/* ****************************************************************************
 % Dem_Event_OpCycle
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
Dem_Event_OpCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr                                                                    /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
)
{
  Dem_UdsStatusByteType lOldEventStatus;
  Dem_UdsStatusByteType lOldExternalEventStatus;
  Dem_UdsStatusByteType lNewEventStatus;

  lOldEventStatus = Dem_Event_GetUDSStatus(EventId);
  lOldExternalEventStatus = Dem_Event_GetExternalUDSStatus(EventId, lOldEventStatus);

  if ((ArgPtr->Specific.EventOpCycle_Internal.CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STOPPED) != 0U)
  {
    Dem_Event_OpCycleEnd(EventId, ArgPtr->Common.OldDtcStatus);
  }
  if ((ArgPtr->Specific.EventOpCycle_Internal.CycleStatus & DEM_OPERATIONCYCLE_CYCLE_STARTED) != 0U)
  {
    Dem_Event_OpCycleStart(EventId);
  }
  lNewEventStatus = Dem_Event_GetUDSStatus(EventId);

  if (Dem_UDSStatus_IsNvRelevantStatusChange(lOldEventStatus, lNewEventStatus) == TRUE)
  {
    Dem_Nvm_SetStatusBlockChanged();
  }

  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Notifications_EventStatusChanged(EventId, 
                                         lOldExternalEventStatus, 
                                         Dem_Event_GetExternalUDSStatus(EventId, lNewEventStatus));
    /* Call Init Monitor Callbacks */
    Dem_Notifications_InitMonitorForEvent(EventId, DEM_INIT_MONITOR_RESTART);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Event_ResetTestFailed
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
Dem_Event_ResetTestFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Event_ContextType lEventContext;
  Dem_DTC_ContextType lDTCContext;

  Dem_Event_InitEventContext(EventId, &lEventContext);                                                                           /* SBSW_DEM_POINTER_FORWARD_STACK */
  Dem_DTC_InitDTCContext(EventId, &lDTCContext);                                                                                 /* SBSW_DEM_POINTER_FORWARD_STACK */

  lEventContext.NewEventStatus = Dem_UDSStatus_Reset_TF(lEventContext.OldEventStatus);
  Dem_Event_SetUDSStatus(EventId, lEventContext.NewEventStatus);

  Dem_DTC_CalculateDTCStatus(&lDTCContext);                                                                                      /* SBSW_DEM_POINTER_FORWARD_STACK */
  Dem_DTC_ResetFdcToc(&lDTCContext);                                                                                             /* SBSW_DEM_POINTER_FORWARD_STACK */
  
  if (Dem_UDSStatus_IsNvRelevantStatusChange(lEventContext.OldEventStatus, lEventContext.NewEventStatus) == TRUE)
  {
    Dem_Nvm_SetStatusBlockChanged();
  }

  Dem_Notifications_EventStatusChanged(lEventContext.EventId, 
                                       lEventContext.OldExternalEventStatus, 
                                       Dem_Event_GetExternalUDSStatus(lEventContext.EventId, lEventContext.NewEventStatus));
  if (lEventContext.DataModified == TRUE)
  {
    Dem_Notifications_EventDataChanged(lEventContext.EventId);
  }
  Dem_Notifications_DtcStatusChanged(lDTCContext.EventId, 
                                     lDTCContext.OldExternalDtcStatus,
                                     Dem_DTC_ApplyExternalOnlyStatus(lDTCContext.EventId, lDTCContext.NewDtcStatus), 
                                     DEM_NOTIFICATIONS_DTC_UPDATED);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Event_Aged
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
Dem_Event_Aged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr                                                                    /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_Internal */
  )
{
  Dem_UdsStatusByteType lOldEventStatus;
  Dem_UdsStatusByteType lOldExternalEventStatus;
  Dem_UdsStatusByteType lNewEventStatus;
  Dem_Event_InternalStatusType lInternalStatus;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ArgPtr)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lOldEventStatus = Dem_Event_GetUDSStatus(EventId);
  lOldExternalEventStatus = Dem_Event_GetExternalUDSStatus(EventId, lOldEventStatus);
  lNewEventStatus = lOldEventStatus;

  /* remove the aged event from the primary memory */
  lNewEventStatus = Dem_UDSStatus_Reset_CDTC(lNewEventStatus);

  if (Dem_Cfg_EventAgingTarget(EventId) == 0)
  {
# if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
    if (Dem_UDSStatus_Test_PDTC(lOldEventStatus) == TRUE)
    {
      Dem_Event_SetTripCount(EventId, 0);
    }
# endif
    lNewEventStatus = Dem_UDSStatus_Reset_PDTC(lNewEventStatus);
    lNewEventStatus = Dem_UDSStatus_Reset_TFTOC(lNewEventStatus);
  }
# if (DEM_CFG_PROCESS_TFSLC_CLEARONLY != STD_ON)
  lNewEventStatus = Dem_UDSStatus_Reset_TFSLC(lNewEventStatus);
# endif
  Dem_Event_SetUDSStatus(EventId, lNewEventStatus);

/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */

  lInternalStatus = Dem_Event_GetInternalStatus(EventId);
# if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
  if (Dem_DTCInternalStatus_GetStoredStatus(lInternalStatus) != Dem_DTCInternalStatus_StoredStatus_None)
  {
    lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_Aged);
  }
# else
  lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_None);
# endif
  Dem_Event_SetInternalStatus(EventId, lInternalStatus);

  Dem_LeaveCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

# if (DEM_FEATURE_NEED_OBD == STD_ON)
  if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
  { /* only OBD related events supports the qualification of Confirmed and WIR bit */
    Dem_Event_SetQualifyStatus(EventId, Dem_EventInternalStatus_Reset_QualifyStatus_CDTC(Dem_Event_GetQualifyStatus(EventId)));
  }
# endif

  if (Dem_UDSStatus_IsNvRelevantStatusChange(lOldEventStatus, lNewEventStatus) == TRUE)
  {
    Dem_Nvm_SetStatusBlockChanged();
  }

  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    Dem_Notifications_EventStatusChanged(EventId, 
                                         lOldExternalEventStatus, 
                                         Dem_Event_GetExternalUDSStatus(EventId, lNewEventStatus));
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


/* ****************************************************************************
 % Dem_Event_Cleared
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Cleared(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr                                                                    /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_Internal */
  )
{
  Dem_Event_InternalStatusType lInternalStatus;
  Dem_UdsStatusByteType lOldEventStatus;
  Dem_UdsStatusByteType lOldExternalEventStatus;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ArgPtr)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */

  Dem_SatelliteCore_ClearEvent(
      Dem_Cfg_EventSatelliteId(EventId),
      Dem_Cfg_EventSatelliteEventId(EventId));

/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */

  lInternalStatus = Dem_Event_GetInternalStatus(EventId);
  lOldEventStatus = Dem_Event_GetUDSStatus(EventId);
  lOldExternalEventStatus = Dem_Event_GetExternalUDSStatus(EventId, lOldEventStatus);

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  if (Dem_UDSStatus_Test_TF(lOldEventStatus) == TRUE)
  {
    Dem_Esm_DecrementQualifiedActiveEventCount(EventId, TRUE);
  }
#endif

  lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_None);
  lInternalStatus = Dem_DTCInternalStatus_ResetFdcToc(lInternalStatus);

  /* Reset extended status */
  Dem_Event_SetExtendedStatus(EventId, DEM_EXT_STATUS_INITIALIZE);

  Dem_Event_SetInternalStatus(EventId, lInternalStatus);
  /* Reset status byte */
  Dem_Event_SetUDSStatus(EventId, DEM_UDS_STATUS_INITIALIZE);
  /* EventStatus is marked modified by the caller to reduce runtime overhead */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_DtrIF_ResetDtrsOfEvent(EventId);
#endif

  Dem_LeaveCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

#if (DEM_FEATURE_NEED_INDICATORS == STD_ON)
  if (Dem_UDSStatus_Test_WIR(lOldEventStatus) == TRUE)
  {
# if (DEM_FEATURE_NEED_OBD == STD_ON)
    if (Dem_EventInternalStatus_Test_QualifyStatus_WIR(Dem_Event_GetQualifyStatus(EventId)) == TRUE)
# endif
    {
      Dem_Indicator_IndicatorDisable(EventId);
    }
  }
#endif /* (DEM_FEATURE_NEED_INDICATORS == STD_ON) */
#if (DEM_FEATURE_NEED_OBD == STD_ON)
  if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
  { /* only OBD related events supports the qualification of Confirmed and WIR bit */
    Dem_Event_SetQualifyStatus(EventId, DEM_QUALIFICATION_STATUS_ALL_UNQUALIFIED);
  }
#endif

  if (Dem_Cfg_EventPrestorageIndex(EventId) != DEM_PRESTORE_NOT_CONFIGURED_FOR_EVENT)
  {
    (void)Dem_Prestore_EventPrestorageClear(EventId);
  }

#if (DEM_FEATURE_NEED_OBD == STD_ON)
# if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
  {
    uint16 lMilGroupIndex;
    lMilGroupIndex = Dem_Cfg_EventMilGroupIndex(EventId);

    if (lMilGroupIndex != DEM_CFG_MIL_GROUP_INVALID)
    { /* decrement MIL group pending count if event pending state has changed from 1 to 0 */
      Dem_Mem_InitMilGroupTripCount(lMilGroupIndex);

      if (Dem_UDSStatus_Test_PDTC((uint8)(lOldEventStatus ^ Dem_Event_GetUDSStatus(EventId))) == TRUE)
      {
        Dem_Mem_DecrementMilGroupPendingCount(lMilGroupIndex);
      }
    }
  }
# endif
# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if (Dem_Mem_FreezeFrameIndexMode02 == Dem_Cfg_GlobalObdIIFFCount())
  { /* No Freeze Frame visible in Mode02, scan for one */
    Dem_Mem_FreezeFrameIndexMode02 = Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame();
  }
# endif
#endif /* (DEM_FEATURE_NEED_OBD == STD_ON) */

#if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
  Dem_Event_SetTripCount(EventId, 0);
#endif

  Dem_Notifications_EventStatusChanged(EventId, 
                                       lOldExternalEventStatus, 
                                       DEM_UDS_STATUS_INITIALIZE);
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

#if (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
/* ****************************************************************************
 % Dem_Event_Displaced
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
Dem_Event_Displaced(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr                                                                    /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_Internal */
  )
{
  Dem_Event_InternalStatusType lInternalStatus;
# if (DEM_FEATURE_NEED_STOREDONLY_BITS == STD_ON)
  Dem_UdsStatusByteType lOldEventStatus;
  Dem_UdsStatusByteType lOldExternalEventStatus;
  Dem_UdsStatusByteType lNewEventStatus;
# endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ArgPtr)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */

/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */

  lInternalStatus = Dem_Event_GetInternalStatus(EventId);
  lInternalStatus = Dem_DTCInternalStatus_SetStoredStatus(lInternalStatus, Dem_DTCInternalStatus_StoredStatus_None);
  Dem_Event_SetInternalStatus(EventId, lInternalStatus);

  Dem_LeaveCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

# if (DEM_FEATURE_NEED_STOREDONLY_BITS == STD_ON)
  lOldEventStatus = Dem_Event_GetUDSStatus(EventId);
  lOldExternalEventStatus = Dem_Event_GetExternalUDSStatus(EventId, lOldEventStatus);
  lNewEventStatus = lOldEventStatus;
# endif
  /* Update the status bit */
# if (DEM_CFG_PROCESS_PDTC_STOREDONLY == STD_ON)
  lNewEventStatus = Dem_UDSStatus_Reset_PDTC(lNewEventStatus);
# endif
# if (DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON)
  lNewEventStatus = Dem_UDSStatus_Reset_CDTC(lNewEventStatus);
#  if (DEM_FEATURE_NEED_OBD == STD_ON)
  if (Dem_Cfg_EventObdRelated(EventId) == TRUE)
  {
    Dem_Event_SetQualifyStatus(EventId, Dem_EventInternalStatus_Reset_QualifyStatus_CDTC(Dem_Event_GetQualifyStatus(EventId)));
  }
#  endif
# endif
# if (DEM_CFG_PROCESS_TFSLC_STOREDONLY == STD_ON)
  lNewEventStatus = Dem_UDSStatus_Reset_TFSLC(lNewEventStatus);
# endif
# if (DEM_FEATURE_NEED_STOREDONLY_BITS == STD_ON)
  Dem_Event_SetUDSStatus(EventId, lNewEventStatus);
# endif
  /* Displacement follows an event status change. No need to mark Nv modification again. */

# if (DEM_FEATURE_NEED_STOREDONLY_BITS == STD_ON)
  Dem_Notifications_EventStatusChanged(EventId, 
                                       lOldExternalEventStatus, 
                                       lNewEventStatus);
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif



/* ****************************************************************************
 % Dem_Event_GetEventUDSStatus
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_GetEventUDSStatus(
    CONST(Dem_EventIdType, AUTOMATIC)  EventId,
    CONSTP2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA)  EventUDSStatus
  )
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_NOT_OK;
  if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)                                                                        /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) )
  {
    *EventUDSStatus = Dem_Event_GetExternalUDSStatus(EventId, Dem_Event_GetUDSStatus(EventId));                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = E_OK;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Event_GetEventFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_GetEventFailed(
    CONST(Dem_EventIdType, AUTOMATIC)  EventId,
    CONSTP2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventFailed
    )
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_NOT_OK;
  if ( (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)                                                                        /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE) )
  {
    if (Dem_UDSStatus_Test_TF(Dem_Event_GetUDSStatus(EventId)) == TRUE)
    {
      *EventFailed = TRUE;                                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
    {
      *EventFailed = FALSE;                                                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    lReturnValue = E_OK;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Event_GetEventTested
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_GetEventTested(
    CONST(Dem_EventIdType, AUTOMATIC)  EventId,
    CONSTP2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventTested
  )
{
  Std_ReturnType lReturnValue;
  lReturnValue = E_NOT_OK;
  if ( (Dem_OperationCycle_GetCurrentCycleStatus(Dem_Cfg_EventOperationCycle(EventId)) == DEM_OPERATIONCYCLE_CYCLE_STARTED)      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_Cfg_EventAvailableByVariant(EventId) == TRUE)
    && (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(EventId)) == FALSE)
    )
  {
    if (Dem_UDSStatus_Test_TNCTOC(Dem_Event_GetUDSStatus(EventId)) == FALSE)
    {
      *EventTested = TRUE;                                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
    {
      *EventTested = FALSE;                                                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    lReturnValue = E_OK;
  }
  /* else: with stopped cycle the bit value is undecided */
  return lReturnValue;
}

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_Event_CycleQualifyDcy
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
Dem_Event_CycleQualifyDcy(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr                                                                    /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_Internal */
)
{
  Dem_UdsStatusByteType lEventStatus;
  Dem_UdsStatusByteType lOldExternalEventStatus;
  uint8 lEventQualifyStatus;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ArgPtr)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lEventStatus = Dem_Event_GetUDSStatus(EventId);
  lOldExternalEventStatus = Dem_Event_GetExternalUDSStatus(EventId, lEventStatus);
  lEventQualifyStatus = Dem_Event_GetQualifyStatus(EventId);

  if ( (Dem_EventInternalStatus_Test_QualifyStatus_CDTC(lEventQualifyStatus) == FALSE)                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_UDSStatus_Test_CDTC(lEventStatus) == TRUE)
    )
  { /* set confirmed status to qualified */
    lEventQualifyStatus = Dem_EventInternalStatus_Set_QualifyStatus_CDTC(lEventQualifyStatus);

# if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
    /* Set readiness group to completed */
    {
      uint8 lEventReadinessGroup;
      lEventReadinessGroup = Dem_Cfg_EventReadinessGroup(EventId);
      if ((lEventReadinessGroup != DEM_CFG_READINESS_FLSYS) 
          && (lEventReadinessGroup != DEM_CFG_READINESS_CMPRCMPT))
      {
        Dem_Util_SetReadinessGroupCompleted(TRUE, lEventReadinessGroup, &Dem_Mem_GetPid01CompletedMask());                       /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
      }
    }
# endif

# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    /* count qualified confirmed & failed events */
    Dem_Esm_IncrementQualifiedActiveEventCount(EventId);
# endif
  }

  if ( (Dem_EventInternalStatus_Test_QualifyStatus_WIR(lEventQualifyStatus) == FALSE)                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_UDSStatus_Test_WIR(lEventStatus) == TRUE))
  { /* set warningIndicatorRequested status to qualified */
    lEventQualifyStatus = Dem_EventInternalStatus_Set_QualifyStatus_WIR(lEventQualifyStatus);
      /* Process the indicators */
    Dem_Indicator_UserIndicatorEnable(EventId);

    (void)Dem_Indicator_SpecialIndicatorEnable(EventId);
  }

  Dem_DTC_SetQualifyStatus(EventId, lEventQualifyStatus);

  Dem_Notifications_EventStatusChanged(EventId, 
                                       lOldExternalEventStatus, 
                                       Dem_Event_GetExternalUDSStatus(EventId, lEventStatus));
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_FEATURE_NEED_OBD == STD_ON) */

/* ****************************************************************************
 % Dem_Event_TestLatchedTestFailed
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
Dem_Event_TestLatchedTestFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lReturnValue;

  if (Dem_Cfg_EventLatchTestFailed(EventId) == TRUE)
  {
    lReturnValue = 
      (boolean)(((DEM_UDS_STATUS_TFTOC | DEM_UDS_STATUS_CDTC) & Dem_Event_GetUDSStatus(EventId)) != 0);
  }
  else
  {
    lReturnValue = FALSE;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Event_InitNvData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitNvData(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Event_SetUDSStatus(EventId, DEM_UDS_STATUS_INITIALIZE);
  Dem_Event_SetExtendedStatus(EventId, DEM_EXT_STATUS_INITIALIZE);

#if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
  Dem_Event_SetTripCount(EventId, 0);
#endif
#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
  if (Dem_Cfg_EventObdRelated(EventId) == FALSE)
  {
    Dem_DTC_SetQualifyStatus(EventId, DEM_QUALIFICATION_STATUS_ALL_QUALIFIED);
  }
  else
  {
    Dem_DTC_SetQualifyStatus(EventId, DEM_QUALIFICATION_STATUS_ALL_UNQUALIFIED);
  }
#endif
}

/* ****************************************************************************
 % Dem_Event_Init
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
Dem_Event_Init(
  void
  )
{
  Dem_EventIdType lEventId;

  Dem_Event_InitQualification();
  Dem_DTC_InitQualification();
  Dem_Indicator_InitWwhObdStatistics();
#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
  /* ----- MIL group handling at DCY restart ----- */
  {
    uint16 lMilGroupIndex;
    lMilGroupIndex = Dem_Cfg_GlobalMilGroupCount();
    while (lMilGroupIndex != DEM_CFG_MIL_GROUP_INVALID)
    {
      lMilGroupIndex--;
      Dem_EventInternalStatus_SetMilGroupPendingCount(lMilGroupIndex, 0);
    }
  }
#endif /* (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON) */

  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  {
    Dem_Event_InitEventInternalStatus(lEventId);
    Dem_Event_InitEventStatus(lEventId);

#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON)
    /* Set qualification state for all UDS DTCs to qualified */
    if (Dem_Cfg_EventObdRelated(lEventId) == FALSE)
    {
      Dem_DTC_SetQualifyStatus(lEventId, DEM_QUALIFICATION_STATUS_ALL_QUALIFIED);
    }
#endif
  } /* for each event */

  Dem_Event_InitAvailableNV();
  (void)Dem_DtrIF_UpdateMidVisibility();
  Dem_Indicator_InitSpecialIndicator();
  Dem_Indicator_InitUserIndicator();
  
#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
  {
    uint16 lMilGroupIndex;
    lMilGroupIndex = Dem_Cfg_GlobalMilGroupCount();
    while (lMilGroupIndex != DEM_CFG_MIL_GROUP_INVALID)
    {
      lMilGroupIndex--;
      if (Dem_EventInternalStatus_GetMilGroupPendingCount(lMilGroupIndex) == 0)
      {
        Dem_Mem_ResetMilGroupTripCount(lMilGroupIndex);
      }
    }
  }
#endif /* (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON) */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


/* ****************************************************************************
 % Dem_Event_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_PreInit(
  void
  )
{
  Dem_EventIdType lEventId;
  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  {
    if (Dem_Cfg_EventAvailableByDefault(lEventId) == TRUE)
    {
      Dem_Event_SetInternalStatus(lEventId, 0);
    }
    else
    {
      Dem_Event_SetInternalStatus(lEventId, Dem_EventInternalStatus_SetEventDisconnected(0));
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Event_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_MainFunction(
  void
  )
{
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
  Dem_EventIdType lEventId;
  for (lEventId = DEM_EVENT_FIRST; lEventId < Dem_Cfg_GlobalEventCount(); ++lEventId)
  {
    Dem_Event_ProcessEventAvailable(lEventId);
  }
#endif
}

/* ****************************************************************************
 % Dem_Event_SetAgingCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetAgingCounter(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC) AgingCounter
  )
{
#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  {
    uint16 lAgingCounterIndex;
    lAgingCounterIndex = Dem_Cfg_GetAgingCounterIndexOfEventTable(EventId);

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
    if (lAgingCounterIndex >= DEM_CFG_MAX_NUMBER_AGING_DTCS)
    {
      /* DEM_CFG_MAX_NUMBER_AGING_DTCS is always lesser than DEM_CFG_AGINGCOUNTER_INDEX_INVALID */
      Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                          /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    }
    else
# endif
    {
      Dem_Cfg_GetAgingData().AgingCounter[lAgingCounterIndex] = AgingCounter;                                                    /* SBSW_DEM_ARRAY_WRITE_AGINGDATA_AGINGCOUNTER */
    }
  } 
#else
  {
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(AgingCounter)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
#endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

/* ****************************************************************************
 % Dem_Event_GetAgingCounter
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
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Event_GetAgingCounter(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint16 lAgingCounter;
  lAgingCounter = DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID;

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  {  
    uint16 lAgingCounterIndex;
    lAgingCounterIndex = Dem_Cfg_GetAgingCounterIndexOfEventTable(EventId);

    if (lAgingCounterIndex == DEM_CFG_AGINGCOUNTER_INDEX_INVALID)
    {
      /* Do nothing it is an internal event */
    }
    else if (lAgingCounterIndex < DEM_CFG_MAX_NUMBER_AGING_DTCS)
    {
      /* If indexing is inside the array, read out the value, else return default */
      lAgingCounter = Dem_Cfg_GetAgingData().AgingCounter[lAgingCounterIndex];
    }
    else
    {
      /* MISRA */
    }
  }
#else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  return lAgingCounter;
}

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
% Dem_Event_TestHighPriorReadinessGroup
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_TestHighPriorReadinessGroup(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lIsMisfireOrFuelSystem;
# if (DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON)
  uint8 lReadinessGroup;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif

  lIsMisfireOrFuelSystem = FALSE;
# if (DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON)

  if (EventId != DEM_EVENT_INVALID)
  {
    lReadinessGroup = Dem_Cfg_EventReadinessGroup(EventId);

    if ((lReadinessGroup == DEM_CFG_READINESS_FLSYS_NONCONT)
      || (lReadinessGroup == DEM_CFG_READINESS_FLSYS)
      || (lReadinessGroup == DEM_CFG_READINESS_MISF))
    {
      lIsMisfireOrFuelSystem = TRUE;
    }
  }
#endif
  return lIsMisfireOrFuelSystem;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_EVENT_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Event_Implementation.h
 *********************************************************************************************************************/
