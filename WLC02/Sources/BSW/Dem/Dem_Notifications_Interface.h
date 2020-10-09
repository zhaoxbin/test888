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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_Notifications Notifications
 *  \{
 *  \file       Dem_Notifications_Interface.h
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

#if !defined (DEM_NOTIFICATIONS_INTERFACE_H)
#define DEM_NOTIFICATIONS_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Notifications_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Notifications_Properties Properties
 * \{
 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Notifications_Private Private Methods
 * \{
 */

# if (DEM_CFG_NOTIFY_J1939DCM == STD_ON)
/* ****************************************************************************
 * Dem_Notifications_CallJ1939NotificationForConcernedClients
 *****************************************************************************/
/*!
 * \brief         Call the J1939 notification callback for all clients assigned
 *                to a node
 *
 * \details       Call the J1939 notification callback for all clients assigned
 *                to a node
 *
 * \param[in]     J1939DTC
 *                J1939 DTC number
 * \param[in]     NmNodeId
 *                Nm Node Id of the node
 *
 * \pre           -
 * \config        DEM_CFG_NOTIFY_J1939DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Notifications_CallJ1939NotificationForConcernedClients(
  CONST(uint32, AUTOMATIC)  J1939DTC,
  CONST(uint16, AUTOMATIC)  NmNodeId
  );
#endif

/* ****************************************************************************
 * Dem_Notifications_J1939DtcStatusChanged
 *****************************************************************************/
/*!
 * \brief         Call all J1939 notification callbacks relevant for DTC 
 *                status changes
 *
 * \details       The following callbacks are called here:
 *                - J1939DcmDtcStatusChanged(1...*)
 *                - J1939Dcm_DemTriggerOnDTCStatus
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DtcStatusOld
 *                The old DTC status
 * \param[in]     DtcStatusNew
 *                The new DTC status
 *
 * \pre           EventStatusOld must be different from EventStatusNew.
 * \pre           The external only status modifications must have been applied
 *                to the passed status bytes.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Notifications_J1939DtcStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusOld,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusNew
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Notifications_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Notifications_EventDataChanged
 *****************************************************************************/
/*!
 * \brief         Calls all configured event data notification functions
 *
 * \details       If configured, event specific and general data changed
 *                callbacks are invoked, unconditionally.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           RTE must be started
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_EventDataChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Notifications_InitMonitorForEvent
 *****************************************************************************/
/*!
 * \brief         Calls all configured 'init monitor for event' callbacks.
 *
 * \details       Calls all configured 'init monitor for event' callbacks.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     InitReason
 *                The reason why the init callback is called
 *
 * \pre           RTE must be started
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_InitMonitorForEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_InitMonitorReasonType, AUTOMATIC)  InitReason
  );

/* ****************************************************************************
 * Dem_Notifications_InitMonitorForFunction
 *****************************************************************************/
/*!
 * \brief         Calls all configured 'init monitor for function' callbacks.
 *
 * \details       Calls all configured 'init monitor for function' callbacks.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           RTE must be started
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_InitMonitorForFunction(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Notifications_DtcStatusChanged
 *****************************************************************************/
/*!
 * \brief         Call all configured DTC status notification functions
 *
 * \details       The following callbacks are called here:
 *                - DtcStatusChanged(1...*)
 *                - DcmDtcStatusChanged(1)
 *                - J1939DcmDtcStatusChanged(1)
 *
 *                Before the callbacks are processed, the passed event status
 *                is masked with the status availability mask
 *
 *                Although the callback processing is technically not possible
 *                reentrantly, the Autosar design forces this behavior. The
 *                resulting inconsistencies are documented in RfC 48668
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DtcStatusOld
 *                The old DTC status
 * \param[in]     DtcStatusNew
 *                The new DTC status
 * \param[in]     NotificationReason
 *                Reason for notification
 *
 * \pre           The external only status modifications must have been applied
 *                to the passed status bytes
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Notifications_DtcStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusOld,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  DtcStatusNew,
  CONST(uint8, AUTOMATIC)  NotificationReason
  );

/* ****************************************************************************
 * Dem_Notifications_EventStatusChanged
 *****************************************************************************/
/*!
 * \brief         Call all configured event status notification functions
 *
 * \details       The following callbacks are called here:
 *                - EventStatusChanged(1...*)
 *                - GeneralEventStatusChanged(1)
 *                - FimEventStatusChanged(1)
 *                - DltEventStatusChanged(1)
 *
 *                Although the callback processing is technically not possible
 *                reentrantly, the Autosar design forces this behavior. The
 *                resulting inconsistencies are documented in RfC 48668
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     EventUdsStatusOld
 *                The old DTC status
 * \param[in]     EventUdsStatusNew
 *                The new DTC status
 *
 * \pre           EventStatusOld must be different from EventStatusNew.
 * \pre           The external only status modifications must have been applied
 *                to the passed status bytes
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Notifications_EventStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  EventUdsStatusOld,
  CONST(Dem_UdsStatusByteType, AUTOMATIC)  EventUdsStatusNew
  );

/* ****************************************************************************
 * Dem_Notifications_MonitorStatusChanged
 *****************************************************************************/
/*!
 * \brief         Notifies a MonitorStatus change.
 *
 * \details       Notifies a MonitorStatus change by calling the configured
 *                function.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_MonitorStatusChanged(
  CONST(Dem_EventIdType, AUTOMATIC)   EventId
  );

/* ****************************************************************************
 * Dem_Notifications_ClearDTCStart()
 *****************************************************************************/
/*!
 * \brief         Calls all clear start notification callbacks.
 *
 * \details       Calls all clear start notification callbacks.
 *
 * \param[in]     DTC
 *                The DTC number to pass to the notification function.
 * \param[in]     DTCFormat
 *                The DTC format to pass to the notification function.
 * \param[in]     DTCOrigin
 *                The DTC origin to pass to the notification function.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_Notifications_ClearDTCStart(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  );

/* ****************************************************************************
 * Dem_Notifications_ClearDTCEnd()
 *****************************************************************************/
/*!
 * \brief         Calls all clear end notification callbacks.
 *
 * \details       Calls all clear end notification callbacks.
 *
 * \param[in]     DTC
 *                The DTC number to pass to the notification function.
 * \param[in]     DTCFormat
 *                The DTC format to pass to the notification function.
 * \param[in]     DTCOrigin
 *                The DTC origin to pass to the notification function.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_Notifications_ClearDTCEnd(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  );

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_Notifications_EventAvailabilityChanged()
 *****************************************************************************/
/*!
 * \brief         Calls FiM event status change notification depending on 
 *                current disconnected status.
 *
 * \details       Calls FiM event status change notification depending on 
 *                current disconnected status.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     DisconnectedStatus
 *                Defines if event is currently available (DisconnectedStatus
 *                FALSE) or not (DisconnectedStatus TRUE)
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_EventAvailabilityChanged(
  CONST(Dem_EventIdType, AUTOMATIC)   EventId,
  CONST(boolean, AUTOMATIC)   DisconnectedStatus
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
* Dem_Notifications_ControlDtcSettingChanged()
*****************************************************************************/
/*!
* \brief         Calls ControlDtcSetting change notification.
*
* \details       Calls ControlDtcSetting change notification.
*
* \param[in]     Enabled
*                TRUE   ControlDtcSetting is enabled
*                FALSE  ControlDtcSetting is disabled
* \pre           -
* \config        DEM_CFG_SUPPORT_DCM == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Notifications_ControlDtcSettingChanged(
CONST(boolean, AUTOMATIC)   Enabled
);
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_NOTIFICATIONS_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Notifications_Interface.h
 *********************************************************************************************************************/
