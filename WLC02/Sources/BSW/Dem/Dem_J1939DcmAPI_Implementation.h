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
/*! \addtogroup Dem_J1939DcmAPI
 *  \{
 *  \file       Dem_J1939DcmAPI_Implementation.h
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

#if !defined (DEM_J1939DCMAPI_IMPLEMENTATION_H)
#define DEM_J1939DCMAPI_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_J1939DcmAPI_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Esm_Implementation.h"
#include "Dem_ClientAccess_Interface.h"
#include "Dem_InitState_Implementation.h"

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
 * \addtogroup Dem_J1939DcmAPI_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmClearDTC
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmClearDTC(
  Dem_J1939DcmSetClearFilterType  DTCTypeFilter,
  Dem_DTCOriginType  DTCOrigin,
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = DEM_CLEAR_FAILED;
# endif
  DEM_IGNORE_UNUSED_ARGUMENT(DTCOrigin)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (DTCTypeFilter >= DEM_J1939_CLEAR_FILTER_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ((DTCOrigin == 0) || (DTCOrigin >= DEM_DTC_ORIGIN_INVALID))
  {
    lReturnValue = DEM_WRONG_DTCORIGIN;
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */    
    lReturnValue = Dem_ClientAccess_J1939ClearDTC(ClientId, DTCTypeFilter, DTCOrigin);
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMCLEARDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON) */

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmFirstDTCwithLampStatus
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
FUNC(void, DEM_CODE)
Dem_J1939DcmFirstDTCwithLampStatus(
  uint8  ClientId
  )
{
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_ClientAccess_SetFirstDTCWithLampStatus(ClientId);
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMFIRSTDTCWITHLAMPSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif
}
#endif /* (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) */

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmGetNextDTCwithLampStatus
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextDTCwithLampStatus(
  P2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_J1939DCM_DATA)  LampStatus,
  P2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter,
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = DEM_NO_SUCH_ELEMENT;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (LampStatus == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (J1939DTC == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (OccurrenceCounter == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestJ1939DTCFilterWithLampStatusSet(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_ClientAccess_GetNextDTCwithLampStatus(ClientId, LampStatus, J1939DTC, OccurrenceCounter);                 /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMGETNEXTDTCWITHLAMPSTATUS_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) */

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmSetDTCFilter
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmSetDTCFilter(
  Dem_J1939DcmDTCStatusFilterType  DTCStatusFilter,
  Dem_DTCKindType  DTCKind,
  Dem_DTCOriginType  DTCOrigin,
  uint8  ClientId,
  P2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_J1939DCM_DATA)  LampStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (DTCStatusFilter >= DEM_J1939_FILTER_DTC_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCKind >= DEM_DTC_KIND_INVALID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ((DTCOrigin == 0) || (DTCOrigin >= DEM_DTC_ORIGIN_INVALID))
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (LampStatus == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_ClientAccess_SetJ1939DTCFilter(ClientId, DTCStatusFilter, DTCKind, DTCOrigin, LampStatus);                /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMSETDTCFILTER_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) */

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmGetNumberOfFilteredDTC
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNumberOfFilteredDTC(
  P2VAR(uint16, AUTOMATIC, DEM_J1939DCM_DATA)  NumberOfFilteredDTC,
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = DEM_NO_SUCH_ELEMENT;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (NumberOfFilteredDTC == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestJ1939DTCFilterSet(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    *NumberOfFilteredDTC = Dem_ClientAccess_GetNumberOfFilteredJ1939DTC(ClientId);                                               /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMGETNUMBEROFFILTEREDDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) */

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmGetNextFilteredDTC
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextFilteredDTC(
  P2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter,
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = DEM_NO_SUCH_ELEMENT;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (J1939DTC == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (OccurrenceCounter == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestJ1939DTCFilterSet(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_ClientAccess_GetNextFilteredJ1939DTC(ClientId, J1939DTC, OccurrenceCounter);                               /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMGETNEXTFILTEREDDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) */

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmSetFreezeFrameFilter
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmSetFreezeFrameFilter(
  Dem_J1939DcmSetFreezeFrameFilterType  FreezeFrameKind,
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if ( (FreezeFrameKind != DEM_J1939DCM_FREEZEFRAME) && (FreezeFrameKind != DEM_J1939DCM_EXPANDED_FREEZEFRAME) )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestFreezeFrameIteratorValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_ClientAccess_SetJ1939FreezeFrameIterator(ClientId, FreezeFrameKind);
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMSETFREEZEFRAMEFILTER_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON */

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmGetNextFreezeFrame
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextFreezeFrame(
  P2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  DestBuffer,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  BufSize, 
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = DEM_NO_SUCH_ELEMENT;
# endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (J1939DTC == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (OccurrenceCounter == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (DestBuffer == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (BufSize == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestJ1939FreezeFrameFilterSet(ClientId) == FALSE)
  { 
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_ClientAccess_GetNextJ1939FreezeFrame(ClientId, J1939DTC, OccurrenceCounter, DestBuffer, BufSize);         /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMGETNEXTFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON */

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmGetNextSPNInFreezeFrame
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextSPNInFreezeFrame(
  P2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  SPNSupported,                                                                     /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  SPNDataLength,                                                                     /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  uint8 ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = DEM_NO_SUCH_ELEMENT;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (SPNSupported == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (SPNDataLength == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    DEM_IGNORE_UNUSED_ARGUMENT(SPNSupported)                                                                                     /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
    DEM_IGNORE_UNUSED_ARGUMENT(SPNDataLength)                                                                                    /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
    DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                         /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON */

#if (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON)
/* ****************************************************************************
 % Dem_J1939DcmReadDiagnosticReadiness1
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmReadDiagnosticReadiness1(
  P2VAR(Dem_J1939DcmDiagnosticReadiness1Type, AUTOMATIC, DEM_J1939DCM_DATA)  DataValue,                                          /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  lReturnValue = E_NOT_OK;
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (DataValue == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_ClientAccess_TestNodeValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
# if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_ClientAccess_ReadDiagnosticReadiness(ClientId, DataValue);                                                /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_J1939DCMREADDIAGNOSTICREADINESS1_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif
  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON) */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_J1939DCMAPI_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_J1939DcmAPI_Implementation.h
 *********************************************************************************************************************/
