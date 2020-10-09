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
/*! \addtogroup Dem_Notifications
 *  \{
 *  \file       Dem_Notifications_Implementation.h
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

#if !defined (DEM_NOTIFICATIONS_IMPLEMENTATION_H)
#define DEM_NOTIFICATIONS_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Notifications_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_UDSStatus_Implementation.h"
#include "Dem_InitState_Implementation.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"
#include "Dem_DTC_Interface.h"

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
 * \addtogroup Dem_Notifications_Properties
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
 * \addtogroup Dem_Notifications_Private
 * \{
 */

# if (DEM_CFG_NOTIFY_J1939DCM == STD_ON)
/* ****************************************************************************
 % Dem_Notifications_CallJ1939NotificationForConcernedClients
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Notifications_CallJ1939NotificationForConcernedClients(
  CONST(uint32, AUTOMATIC)  J1939DTC,
  CONST(uint16, AUTOMATIC)  NmNodeId
  )
{
  uint8 lClientId;
              
  for (lClientId = 0; lClientId < Dem_Cfg_GetSizeOfClientTable(); lClientId++)
  {
    if (NmNodeId == Dem_Cfg_GetNmNodeIdOfClientTable(lClientId))
    {
      J1939Dcm_DemTriggerOnDTCStatus(J1939DTC, lClientId);
    }
  }
}
#endif

/* ****************************************************************************
 % Dem_Notifications_J1939DtcStatusChanged
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
Dem_Notifications_J1939DtcStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusOld,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusNew
  )
{
#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
  uint32 lJ1939Dtc;

  lJ1939Dtc = Dem_Cfg_EventJ1939Dtc(EventId);

  if (lJ1939Dtc != DEM_CFG_DTC_J1939_INVALID)
  {
    Dem_Cfg_GlobalCbkJ1939DtcIterType lIter;

    /* Call all configured status change callbacks */
    for (Dem_Cfg_GlobalCbkJ1939DtcIterInit(&lIter);                                                                              /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
         Dem_Cfg_GlobalCbkJ1939DtcIterExists(&lIter) == TRUE;                                                                    /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
         Dem_Cfg_GlobalCbkJ1939DtcIterNext(&lIter))                                                                              /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
    {
      Dem_DtcStatusChangedFPtrType lpDtcStatusFunc;
      lpDtcStatusFunc = Dem_Cfg_GlobalCbkJ1939DtcIterGet(&lIter);                                                                /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
      if (lpDtcStatusFunc != NULL_PTR)
      {
        (void)lpDtcStatusFunc(lJ1939Dtc, DtcStatusOld, DtcStatusNew);                                                            /* SBSW_DEM_GLOBALCBKJ1939DTCSTATUS_FPTR */
      }
    }
# if (DEM_CFG_NOTIFY_J1939DCM == STD_ON)
    if (Dem_UDSStatus_Test_TF((Dem_UDSStatus_Type) (DtcStatusOld ^ DtcStatusNew)) == TRUE)
    { /* J1939Dcm is only triggered if testFailed bit changes */
      Dem_Cfg_EventJ1939NodeIterType lNodeIter;
      for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
           Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_Notifications_CallJ1939NotificationForConcernedClients(lJ1939Dtc, 
                                                         Dem_Cfg_J1939NmNodeId(Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter)));      /* SBSW_DEM_CALL_ITERATOR_POINTER */
      }
    }
# endif
  }
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtcStatusOld)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtcStatusNew)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


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
 * \addtogroup Dem_Notifications_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Notifications_EventDataChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_EventDataChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  if (Dem_Cfg_EventCbkData(EventId) != NULL_PTR)
  {
    (void)(*Dem_Cfg_EventCbkData(EventId))();                                                                                    /* SBSW_DEM_EVENTCBKDATA_FPTR */
  }
  if (Dem_Cfg_GlobalCbkData() != NULL_PTR)
  {
    (void)(*Dem_Cfg_GlobalCbkData())(EventId);                                                                                   /* SBSW_DEM_GLOBALCBKEVENTDATA_FPTR */
  }
}

/* ****************************************************************************
 % Dem_Notifications_InitMonitorForEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_InitMonitorForEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_InitMonitorReasonType, AUTOMATIC)  InitReason
  )
{
  Dem_InitMonitorForEventFPtrType lpInitMonitorForEventFunc;

  lpInitMonitorForEventFunc = Dem_Cfg_EventCbkInitMonitor(EventId);

  if (lpInitMonitorForEventFunc != NULL_PTR)
  {
    (void)(*lpInitMonitorForEventFunc)(InitReason);                                                                              /* SBSW_DEM_INITMONITORFOREVENT_FPTR */
  }
}

/* ****************************************************************************
 % Dem_Notifications_InitMonitorForFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_InitMonitorForFunction(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_Cfg_EventCbkInitFuncIterType lIter;

  for (Dem_Cfg_EventCbkInitFuncIterInit(EventId, &lIter);                                                                        /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
       Dem_Cfg_EventCbkInitFuncIterExists(&lIter) == TRUE;                                                                       /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
       Dem_Cfg_EventCbkInitFuncIterNext(&lIter))                                                                                 /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
  {
    Dem_InitMonitorForFuncFPtrType lpInitMonitorForFuncFunc;

    lpInitMonitorForFuncFunc = Dem_Cfg_EventCbkInitFuncIterGet(&lIter);                                                          /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
    if (lpInitMonitorForFuncFunc != NULL_PTR)
    {
      (void)(lpInitMonitorForFuncFunc());                                                                                        /* SBSW_DEM_INITMONITORFORFUNCTION_FPTR */
    }
  }
}

/* ****************************************************************************
 % Dem_Notifications_DtcStatusChanged
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
Dem_Notifications_DtcStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusOld,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusNew,
  CONST(uint8, AUTOMATIC)  NotificationReason                                                                                    /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NotificationReason)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */

  if (Dem_DTC_TestDtcSuppressed(EventId) == FALSE)
  {
    uint8 lDtcStatusOld;
    uint8 lDtcStatusNew;

    lDtcStatusOld = (uint8)(DtcStatusOld & Dem_Cfg_GlobalStatusMask());
    lDtcStatusNew = (uint8)(DtcStatusNew & Dem_Cfg_GlobalStatusMask());

    if (lDtcStatusOld != lDtcStatusNew)
    {
      uint32 lUdsDtc;

      lUdsDtc = Dem_Cfg_EventUdsDtc(EventId);

      if (lUdsDtc != DEM_CFG_DTC_UDS_INVALID)
      {
        Dem_Cfg_GlobalCbkDtcIterType lIter;
        for (Dem_Cfg_GlobalCbkDtcIterInit(&lIter);                                                                               /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
             Dem_Cfg_GlobalCbkDtcIterExists(&lIter) == TRUE;                                                                     /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
             Dem_Cfg_GlobalCbkDtcIterNext(&lIter))                                                                               /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
        {
          Dem_DtcStatusChangedFPtrType lpDtcStatusFunc;
          lpDtcStatusFunc = Dem_Cfg_GlobalCbkDtcIterGet(&lIter);                                                                 /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
          if (lpDtcStatusFunc != NULL_PTR)
          {
            (void)lpDtcStatusFunc(lUdsDtc, lDtcStatusOld, lDtcStatusNew);                                                        /* SBSW_DEM_GLOBALCBKDTCSTATUS_FPTR */
          }
        }

#if (DEM_CFG_NOTIFY_DCM == STD_ON)
        if (NotificationReason != DEM_NOTIFICATIONS_DTC_CLEAR)
        {
          /* Call Dcm Dtc status change callback */
          (void)Dcm_DemTriggerOnDTCStatus(lUdsDtc, lDtcStatusOld, lDtcStatusNew);
        }
#endif
      } /* if (DEM_CFG_DTC_UDS_INVALID != lUdsDtc) */

      Dem_Notifications_J1939DtcStatusChanged(EventId, lDtcStatusOld, lDtcStatusNew);
    } /* if DTC Status has changed */
  } /* if DTC is not suppressed */
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Notifications_EventStatusChanged
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
Dem_Notifications_EventStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  EventUdsStatusOld,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  EventUdsStatusNew
  )
{
  if (EventUdsStatusOld != EventUdsStatusNew)
  {
#if (DEM_CFG_NOTIFY_EVENT_STATUS_FIM == STD_ON)
    /* Call FiM event status change callback */
    (void)FiM_DemTriggerOnEventStatus(EventId, EventUdsStatusOld, EventUdsStatusNew);
#endif

#if (DEM_CFG_NOTIFY_DLT == STD_ON)
    /* Call Dlt event status change callback */
    Dlt_DemTriggerOnEventStatus(EventId, EventUdsStatusOld, EventUdsStatusNew);
#endif
    {
      Dem_Cfg_EventCbkStatusIterType lIter;
      /* Call all configured status change callbacks for this event */
      for (Dem_Cfg_EventCbkStatusIterInit(EventId, &lIter);                                                                      /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
           Dem_Cfg_EventCbkStatusIterExists(&lIter) == TRUE;                                                                     /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
           Dem_Cfg_EventCbkStatusIterNext(&lIter))                                                                               /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
      {
        Dem_EventStatusChangedFPtrType lpEventCbkStatusFunc;
        lpEventCbkStatusFunc = Dem_Cfg_EventCbkStatusIterGet(&lIter);                                                            /* SBSW_DEM_CALL_FUNCPTR_ITERATOR_POINTER */
        if (lpEventCbkStatusFunc != NULL_PTR)
        {
          (void)(lpEventCbkStatusFunc(EventUdsStatusOld, EventUdsStatusNew));                                                    /* SBSW_DEM_EVENTCBKSTATUS_FPTR */
        }
      }
    }

    /* Call general event status changed callback */
    if (Dem_Cfg_GlobalCbkStatus() != NULL_PTR)
    {
      (void)(*Dem_Cfg_GlobalCbkStatus())(EventId, EventUdsStatusOld, EventUdsStatusNew);                                         /* SBSW_DEM_GLOBALCBKEVENTSTATUS_FPTR */
    }
  }
}

/* ****************************************************************************
 % Dem_Notifications_MonitorStatusChanged
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
Dem_Notifications_MonitorStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)   EventId
  )
{
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == TRUE)
  {
    if (Dem_Cfg_GlobalTriggerOnMonitorStatusFPtr() != NULL_PTR)
    {
      (void)(*Dem_Cfg_GlobalTriggerOnMonitorStatusFPtr())(EventId);                                                              /* SBSW_DEM_GLOBALTRIGGERONMONITORSTATUS_FPTR */
    }
#if (DEM_CFG_NOTIFY_MONITOR_STATUS_FIM == STD_ON)
    (void)FiM_DemTriggerOnMonitorStatus(EventId);
#endif
  }
}

/* ****************************************************************************
 % Dem_Notifications_ClearDTCStart()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_Notifications_ClearDTCStart(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  )
{
#if (DEM_CFG_CLEARDTCNOTIFICATIONSTARTTABLE == STD_ON)
  Dem_SimpleIterType lClearNotificationIter;

  for (lClearNotificationIter = 0;
       lClearNotificationIter < Dem_Cfg_GetSizeOfClearDtcNotificationStartTable();
       ++lClearNotificationIter)
  {
    Dem_ClearDtcNotificationFPtrType lpClearDtcNotificationStartFunc;

    lpClearDtcNotificationStartFunc = Dem_Cfg_GetClearDtcNotificationStartTable(lClearNotificationIter);
    if (lpClearDtcNotificationStartFunc != NULL_PTR)
    {
      (void)lpClearDtcNotificationStartFunc(DTC, DTCFormat, DTCOrigin);                                                          /* SBSW_DEM_CLEARDTCNOTIFICATIONSTARTFUNCTION_FPTR */
    }
  }
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTC)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCFormat)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCOrigin)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

/* ****************************************************************************
 % Dem_Notifications_ClearDTCEnd()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_Notifications_ClearDTCEnd(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  )
{
#if (DEM_CFG_CLEARDTCNOTIFICATIONFINISHTABLE == STD_ON)
  Dem_SimpleIterType lClearNotificationIter;

  for (lClearNotificationIter = 0;
       lClearNotificationIter < Dem_Cfg_GetSizeOfClearDtcNotificationFinishTable();
       ++lClearNotificationIter)
  {
    Dem_ClearDtcNotificationFPtrType lpClearDtcNotificationFinishFunc;

    lpClearDtcNotificationFinishFunc = Dem_Cfg_GetClearDtcNotificationFinishTable(lClearNotificationIter);
    if (lpClearDtcNotificationFinishFunc != NULL_PTR)
    {
      (void)lpClearDtcNotificationFinishFunc(DTC, DTCFormat, DTCOrigin);                                                         /* SBSW_DEM_CLEARDTCNOTIFICATIONFINISHFUNCTION_FPTR */
    }
  }
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTC)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCFormat)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCOrigin)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_Notifications_EventAvailabilityChanged()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_EventAvailabilityChanged(
  CONST(Dem_EventIdType, AUTOMATIC)   EventId,
  CONST(boolean, AUTOMATIC)   DisconnectedStatus
  )
{
# if (DEM_CFG_NOTIFY_EVENT_STATUS_FIM == STD_ON)
  if (DisconnectedStatus == TRUE)
  {
    (void)FiM_DemTriggerOnEventStatus(EventId, 0x50U, 0x00U);
  }
  else
  {
    (void)FiM_DemTriggerOnEventStatus(EventId, 0x00U, 0x50U);
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DisconnectedStatus)                                                                           /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
% Dem_Notifications_ControlDtcSettingChanged()
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_ControlDtcSettingChanged(
CONST(boolean, AUTOMATIC)   Enabled
)
{
  if (Dem_Cfg_GlobalCbkControlDtcSetting() != NULL_PTR)
  {
    (void)(*Dem_Cfg_GlobalCbkControlDtcSetting())(Enabled);                                                                      /* SBSW_DEM_GLOBALCBKCONTROLDTCSETTING_FPTR */
  }
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_NOTIFICATIONS_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Notifications_Implementation.h
 *********************************************************************************************************************/
