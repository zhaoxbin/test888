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
/*! \addtogroup Dem_ClearDTC
 *  \{
 *  \file       Dem_ClearDTC_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of ClearDTC subcomponent
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

#if !defined (DEM_CLEARDTC_IMPLEMENTATION_H)
#define DEM_CLEARDTC_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_ClearDTC_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_ClearTask_Implementation.h"
#include "Dem_DTCSelector_Implementation.h"
#include "Dem_DTC_Implementation.h"
#include "Dem_Error_Implementation.h"
#include "Dem_Notifications_Implementation.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */


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
 * \addtogroup Dem_ClearDTC_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_ClearDTC_GetClearStatus()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_StatusType, DEM_CODE) Dem_ClearDTC_GetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  return Dem_ClearDTC_GetClearData(ClearDTCHandle).ClearDTCStatus;
}

/* ****************************************************************************
 % Dem_ClearDTC_TestClearWwhObdAllDTCsAllowed()
*****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) Dem_ClearDTC_TestClearWwhObdAllDTCsAllowed(
  void
  )
{
#if (DEM_CFG_SUPPORT_WWHOBD == STD_OFF) || (DEM_CFG_CLEAR_WWHOBD_GROUP_DTCS == STD_OFF)
  return FALSE;
#else   
  return TRUE;
#endif
}

/* ****************************************************************************
 % Dem_ClearDTC_TestClearObdAllDTCsAllowed()
*****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) Dem_ClearDTC_TestClearObdAllDTCsAllowed(
  void
  )
{
#if (DEM_CFG_SUPPORT_OBDII == STD_OFF) || (DEM_CFG_CLEAR_OBDII_GROUP_DTCS == STD_OFF)
  return FALSE;
#else   
  return TRUE;
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
 * \addtogroup Dem_ClearDTC_Private
 * \{
 */

/* ****************************************************************************
 % Dem_ClearDTC_SetClearData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_SetClearData(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_ClearDTC_DataType, AUTOMATIC)  ClearDTCData
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (ClearDTCHandle >= Dem_Cfg_GetSizeOfClearDTCTable())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetClearDTCTable(ClearDTCHandle, ClearDTCData);                                                                      /* SBSW_DEM_ARRAY_WRITE_CLEARDTCTABLE */
  }  
}

/* ****************************************************************************
 % Dem_ClearDTC_GetClearData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_DataType, DEM_CODE) Dem_ClearDTC_GetClearData(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  return Dem_Cfg_GetClearDTCTable(ClearDTCHandle);
}

/* ****************************************************************************
 % Dem_ClearDTC_SetClearStatus()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_SetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_ClearDTC_StatusType, AUTOMATIC)  ClearDTCStatus
  )
{
  Dem_ClearDTC_DataType lClearData;

  lClearData = Dem_ClearDTC_GetClearData(ClearDTCHandle);
  lClearData.ClearDTCStatus = ClearDTCStatus;
  Dem_ClearDTC_SetClearData(ClearDTCHandle, lClearData);
}

/* ****************************************************************************
 % Dem_ClearDTC_GetClearSelector()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_HandleType, DEM_CODE) Dem_ClearDTC_GetClearSelector(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  return Dem_ClearDTC_GetClearData(ClearDTCHandle).DTCSelector;
}

/* ****************************************************************************
 % Dem_ClearDTC_CallStartNotifications()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_CallStartNotifications(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  Dem_DTCSelector_HandleType lDTCSelector;
  Dem_DTCSelector_RequestType lSelectionRequest;

  lDTCSelector = Dem_ClearDTC_GetClearSelector(ClearDTCHandle);
  lSelectionRequest = Dem_DTCSelector_GetSelectionArguments(lDTCSelector);
  Dem_Notifications_ClearDTCStart(
    lSelectionRequest.DTC,
    lSelectionRequest.DTCFormat,
    lSelectionRequest.DTCOrigin);
}

/* ****************************************************************************
 % Dem_ClearDTC_CallEndNotifications()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_CallEndNotifications(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  Dem_DTCSelector_HandleType lDTCSelector;
  Dem_DTCSelector_RequestType lSelectionRequest;

  lDTCSelector = Dem_ClearDTC_GetClearSelector(ClearDTCHandle);
  lSelectionRequest = Dem_DTCSelector_GetSelectionArguments(lDTCSelector);
  Dem_Notifications_ClearDTCEnd(
    lSelectionRequest.DTC,
    lSelectionRequest.DTCFormat,
    lSelectionRequest.DTCOrigin);
  Dem_DTCSelector_ReleaseSelectDTC(lDTCSelector);
}

/* ****************************************************************************
 % Dem_ClearDTC_StartClearOperation()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearOperation(
  CONST(Dem_ClearTask_ClearRequestConstPtrType, AUTOMATIC)  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  )
{
  Dem_ClearDTC_DataType lClearData;
  Std_ReturnType lReturnValue;
  boolean lClearStarted;

  lClearStarted = Dem_ClearTask_TryNewClear(ClearRequest);                                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  if (lClearStarted == TRUE)
  {
    lClearData.ClearDTCStatus = DEM_CLEARDTC_STATUS_PENDING;
    Dem_DTCSelector_LockSelectDTC(DTCSelector);
    lReturnValue = DEM_PENDING;
  }
  else
  {
    lClearData.ClearDTCStatus = DEM_CLEARDTC_STATUS_IDLE;
    lReturnValue = DEM_CLEAR_BUSY;
  }

  lClearData.DTCSelector = DTCSelector;

  Dem_ClearDTC_SetClearData(ClearRequest->ClearClient, lClearData);
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_ClearDTC_StartClearEvent()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearEvent(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,                                                                               /* PRQA S 3673 */ /* MD_DEM_16.7_False */
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  )
{
  Std_ReturnType lReturnValue;
#if (DEM_CFG_CLEAR_SINGLE_DTCS == STD_ON)
  Dem_EventIdType lEventId;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ClearRequest)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCSelector)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif

#if (DEM_CFG_CLEAR_SINGLE_DTCS == STD_ON)
  lEventId = Dem_DTCSelector_GetEventId(DTCSelector);
  if (Dem_DTC_TestDtcSuppressed(lEventId) == FALSE)
  {
    ClearRequest->ClearEventId = lEventId;                                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = Dem_ClearDTC_StartClearOperation(ClearRequest, DTCSelector);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  {
    lReturnValue = DEM_WRONG_DTC;
  }
#else
  lReturnValue = DEM_WRONG_DTC;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_ClearDTC_StartClearGroup()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearGroup(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,                                                                               /* PRQA S 3673 */ /* MD_DEM_16.7_False */
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  )
{
  Std_ReturnType lReturnValue;

#if (DEM_CFG_CLEAR_GROUP_DTCS == STD_ON)
  ClearRequest->ClearGroup = Dem_DTCSelector_GetGroupMask(DTCSelector);                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  lReturnValue = Dem_ClearDTC_StartClearOperation(ClearRequest, DTCSelector);                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ClearRequest)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCSelector)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lReturnValue = DEM_WRONG_DTC;
#endif

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_ClearDTC_StartClearAllDTCs()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearAllDTCs(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  )
{
  Std_ReturnType lReturnValue;

  if (Dem_DTCSelector_GetGroupId(DTCSelector) == DEM_DTCSELECTOR_GROUP_WWH_OBD_ALL_DTC)
  {
    if ((Dem_ClearDTC_TestClearWwhObdAllDTCsAllowed() == TRUE)                                                                   /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (ClearRequest->ClearMemoryId == DEM_CFG_MEMORYID_PRIMARY))
    {
      lReturnValue = E_OK;
    }
    else
    {
      lReturnValue = DEM_WRONG_DTC;
    }
  }
  else
  if (Dem_DTCSelector_GetGroupId(DTCSelector) == DEM_DTCSELECTOR_GROUP_EMISSION_RELATED)
  {
    if ((Dem_ClearDTC_TestClearObdAllDTCsAllowed() == TRUE)                                                                      /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (ClearRequest->ClearMemoryId == DEM_CFG_MEMORYID_PRIMARY))
    {
      lReturnValue = E_OK;
    }
    else
    {
      lReturnValue = DEM_WRONG_DTC;
    }
  }
  else
  {
    lReturnValue = E_OK;
  }

  if (lReturnValue == E_OK)
  {
    ClearRequest->ClearGroup = DEM_CFG_GROUPMASK_ALLDTCS;                                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = Dem_ClearDTC_StartClearOperation(ClearRequest, DTCSelector);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  return lReturnValue;
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
 * \addtogroup Dem_ClearDTC_Public
 * \{
 */

/* ****************************************************************************
 % Dem_ClearDTC_Init()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_Init(
  void
  )
{
  Dem_ClearDTC_HandleType lClearClient;
  
  for (lClearClient = 0;
       lClearClient < Dem_Cfg_GetSizeOfClearDTCTable();
       ++lClearClient)
  {
    Dem_ClearDTC_SetClearStatus(lClearClient, DEM_CLEARDTC_STATUS_IDLE);
  }
}

#if (DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON)
/* ****************************************************************************
 % Dem_ClearDTC_StartClearJ1939()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearJ1939(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector,
  CONST(uint8, AUTOMATIC)  DTCTypeFilter,
  CONST(uint8, AUTOMATIC)  Node
  )
{
  Dem_ClearTask_ClearRequestType lClearRequest;
  lClearRequest.ClearClient = ClearDTCHandle;
  lClearRequest.ClearEventId = DEM_EVENT_INVALID;
  lClearRequest.ClearGroup = DEM_CFG_GROUPMASK_ALLDTCS;

  if (DTCTypeFilter == DEM_J1939DTC_CLEAR_ACTIVE)
  { /* Clear all active DTCs */
    lClearRequest.ClearCode = (uint8)(DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_TF);
    lClearRequest.ClearMask = (uint8)(DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_TF);
  }
  else if (DTCTypeFilter == DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE)
  { /* Clear previously active DTCs */
    lClearRequest.ClearCode = (uint8)(DEM_UDS_STATUS_CDTC);
    lClearRequest.ClearMask = (uint8)(DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_TF);
  }
  else
  { /* Clear active and previously active DTCs */
    lClearRequest.ClearCode = (uint8)(DEM_UDS_STATUS_CDTC);
    lClearRequest.ClearMask = (uint8)(DEM_UDS_STATUS_CDTC);
  }

  lClearRequest.ClearMemoryId = Dem_DTCSelector_GetMemoryId(DTCSelector);
  lClearRequest.ClearNode = Node;

  return Dem_ClearDTC_StartClearOperation(&lClearRequest, DTCSelector);                                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
}
#endif

/* ****************************************************************************
 % Dem_ClearDTC_StartClear()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClear(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  )
{
  Std_ReturnType lReturnValue;
  Dem_ClearTask_ClearRequestType lClearRequest;

  lClearRequest.ClearClient = ClearDTCHandle;
  lClearRequest.ClearEventId = DEM_EVENT_INVALID;
  lClearRequest.ClearGroup = DEM_CFG_GROUPMASK_NONE;
  lClearRequest.ClearCode = 0xffU;
  lClearRequest.ClearMask = 0x00U;
  lClearRequest.ClearMemoryId = Dem_DTCSelector_GetMemoryId(DTCSelector);
  lClearRequest.ClearNode = DEM_CFG_J1939_NODE_INVALID;
  
  switch (Dem_DTCSelector_GetSelectionResult(DTCSelector))
  {
  case DEM_DTCSELECTOR_SELECTION_DTC:
    lReturnValue = Dem_ClearDTC_StartClearEvent(&lClearRequest, DTCSelector);                                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
    break;
  case DEM_DTCSELECTOR_SELECTION_GROUP:
    lReturnValue = Dem_ClearDTC_StartClearGroup(&lClearRequest, DTCSelector);                                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
    break;
  case DEM_DTCSELECTOR_SELECTION_ALL_DTCS:
    lReturnValue = Dem_ClearDTC_StartClearAllDTCs(&lClearRequest, DTCSelector);                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */
    break;
  case DEM_DTCSELECTOR_SELECTION_NO_MATCH:
  case DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN:
  case DEM_DTCSELECTOR_SELECTION_INIT:
  default:
    /* cannot reach: cases already handled by caller */
    lReturnValue = DEM_CLEAR_FAILED;
    break;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_ClearDTC_ResetClearStatus()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_ResetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  )
{
  Dem_ClearDTC_DataType lClearData;
  lClearData = Dem_ClearDTC_GetClearData(ClearDTCHandle);
  if (lClearData.ClearDTCStatus != DEM_CLEARDTC_STATUS_PENDING)
  {
    lClearData.ClearDTCStatus = DEM_CLEARDTC_STATUS_IDLE;
    Dem_ClearDTC_SetClearData(ClearDTCHandle, lClearData);
  }
}

/* ****************************************************************************
 % Dem_ClearDTC_NotifyClearResult()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_NotifyClearResult(
  CONST(uint8, AUTOMATIC)  QueueClearState
  )
{
  Dem_ClearDTC_HandleType lClearHandle;
  lClearHandle = Dem_ClearTask_GetClearClient();
  if (Dem_ClearDTC_GetClearStatus(lClearHandle) != DEM_CLEARDTC_STATUS_IDLE)
  {
    switch (QueueClearState)
    {
    case DEM_CLEARTASK_INPROGRESS:
      Dem_ClearDTC_CallStartNotifications(lClearHandle);
      break;

    case DEM_CLEARTASK_DONE:
      Dem_ClearDTC_CallEndNotifications(lClearHandle);
      Dem_ClearDTC_SetClearStatus(lClearHandle, DEM_CLEARDTC_STATUS_DONE);
      break;
    case DEM_CLEARTASK_FAILED:
      Dem_ClearDTC_CallEndNotifications(lClearHandle);
      Dem_ClearDTC_SetClearStatus(lClearHandle, DEM_CLEARDTC_STATUS_FAILED);
      break;
    case DEM_CLEARTASK_NVERROR:
      Dem_ClearDTC_CallEndNotifications(lClearHandle);
      Dem_ClearDTC_SetClearStatus(lClearHandle, DEM_CLEARDTC_STATUS_NV_ERROR);
      break;
    case DEM_CLEARTASK_IDLE:
    default:
      /* no update */
      break;
    }
  }
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_CLEARDTC_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClearDTC_Implementation.h
 *********************************************************************************************************************/
