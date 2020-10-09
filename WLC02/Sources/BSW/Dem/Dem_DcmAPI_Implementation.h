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
 *  \addtogroup Dem_DcmAPI
 *  \{
 *  \file       Dem_DcmAPI_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
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

#if !defined (DEM_DCMAPI_IMPLEMENTATION_H)
#define DEM_DCMAPI_IMPLEMENTATION_H


/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DcmAPI_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Dcm_Implementation.h"
#include "Dem_InitState_Implementation.h"
#include "Dem_Cfg_Definitions.h"
#include "Dem_DtrIF_Implementation.h"
#include "Dem_ClientAccess_Implementation.h"
#include "Dem_EnableCondition_Implementation.h"
#include "Dem_Indicator_Implementation.h"
#include "Dem_Mem_Implementation.h"

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
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_DcmAPI_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_SetDTCFilter
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTCFilter(
  uint8  ClientId,
  uint8  DTCStatusMask,
  Dem_DTCFormatType  DTCFormat,                                                                                                  /* PRQA S 3206 */ /* MD_DEM_3206 */
  Dem_DTCOriginType  DTCOrigin,
  boolean  FilterWithSeverity,                                                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  Dem_DTCSeverityType  DTCSeverityMask,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  boolean  FilterForFaultDetectionCounter
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
  if ((DTCFormat != DEM_DTC_FORMAT_UDS) && (DTCFormat != DEM_DTC_FORMAT_OBD))
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ((DTCOrigin == 0) || (DTCOrigin >= DEM_DTC_ORIGIN_INVALID))
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (FilterWithSeverity > TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (FilterForFaultDetectionCounter > TRUE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (Dem_ClientAccess_TestFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
#  if (DEM_FEATURE_NEED_OBD != STD_ON)
  if (DTCFormat == DEM_DTC_FORMAT_OBD)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG);
  }
  else
#  endif
# endif /*DEM_DEV_ERROR_DETECT*/
    {
      /* ----- Implementation ------------------------------------------------ */
      /* Returns E_NOT_OK if function arguments does not match configuration. */
      lReturnValue = Dem_ClientAccess_SetDTCFilter(ClientId,
                                                   DTCStatusMask,
                                                   DTCFormat,
                                                   DTCOrigin,
                                                   FilterWithSeverity,
                                                   DTCSeverityMask,
                                                   FilterForFaultDetectionCounter);

# if (DEM_DEV_ERROR_DETECT == STD_ON)
      if (lReturnValue == E_NOT_OK)
      {
        Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG);
      }
# endif
    }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETDTCFILTER_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6060, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetNumberOfFilteredDTC
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfFilteredDTC(
  uint8 ClientId,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredDTC
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)        
  lReturnValue = E_NOT_OK;
#endif

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
  if (Dem_ClientAccess_TestFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_TestDTCFilterSet(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    *NumberOfFilteredDTC = Dem_ClientAccess_FilterNumberMemory(ClientId);                                                        /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNUMBEROFFILTEREDDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetNextFilteredDTC
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFilteredDTC(
  uint8 ClientId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCStatus
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
  if (DTC == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (DTCStatus == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_ClientAccess_TestFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_TestDTCFilterSet(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    Dem_FilterData_ResultType  lFilterResult;
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_ClientAccess_GetNextFilteredDTC(ClientId, &lFilterResult);                                                /* SBSW_DEM_POINTER_FORWARD_STACK */

    if (lReturnValue == E_OK)
    { /* Set out parameter only if a filtered DTC was found*/
      *DTC = lFilterResult.DTC;                                                                                                  /* SBSW_DEM_POINTER_WRITE_API */
      *DTCStatus = lFilterResult.DTCStatus;                                                                                      /* SBSW_DEM_POINTER_WRITE_API */
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNEXTFILTEREDDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetNextFilteredDTCAndFDC
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFilteredDTCAndFDC(
  uint8 ClientId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  P2VAR(sint8, AUTOMATIC, DEM_DCM_DATA)  DTCFaultDetectionCounter
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
  if (DTC == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (DTCFaultDetectionCounter == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_ClientAccess_TestFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_TestDTCFilterWithFDCSet(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    Dem_FilterData_ResultType  lFilterResult;
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_ClientAccess_GetNextFilteredDTC(ClientId, &lFilterResult);                                                /* SBSW_DEM_POINTER_FORWARD_STACK */

    if (lReturnValue == E_OK)
    { /* Set out parameter only if a filtered DTC was found*/
      *DTC = lFilterResult.DTC;                                                                                                  /* SBSW_DEM_POINTER_WRITE_API */
      *DTCFaultDetectionCounter = lFilterResult.FDC;                                                                             /* SBSW_DEM_POINTER_WRITE_API */
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNEXTFILTEREDDTCANDFDC_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetNextFilteredDTCAndSeverity
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFilteredDTCAndSeverity(
  uint8 ClientId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,                                                                                   /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCStatus,                                                                              /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_DCM_DATA)  DTCSeverity,                                                              /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCFunctionalUnit                                                                       /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
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
  if (DTC == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (DTCStatus == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (DTCSeverity == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (DTCFunctionalUnit == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Dem_ClientAccess_TestFilterValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_TestDTCFilterWithSeveritySet(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    Dem_FilterData_ResultType  lFilterResult;
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_ClientAccess_GetNextFilteredDTC(ClientId, &lFilterResult);                                                /* SBSW_DEM_POINTER_FORWARD_STACK */

    if (lReturnValue == E_OK)
    { /* Set out parameter only if a filtered DTC was found*/
      *DTC = lFilterResult.DTC;                                                                                                  /* SBSW_DEM_POINTER_WRITE_API */
      *DTCStatus = lFilterResult.DTCStatus;                                                                                      /* SBSW_DEM_POINTER_WRITE_API */
      *DTCSeverity = lFilterResult.Severity;                                                                                     /* SBSW_DEM_POINTER_WRITE_API */
      *DTCFunctionalUnit = lFilterResult.FunctionalUnit;                                                                         /* SBSW_DEM_POINTER_WRITE_API */
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNEXTFILTEREDDTCANDSEVERITY_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_SetFreezeFrameRecordFilter
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetFreezeFrameRecordFilter(
  uint8                                   ClientId,
  Dem_DTCFormatType                       DTCFormat,                                                                             /* PRQA S 3206 */ /* MD_DEM_3206 */
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords
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
  if (Dem_ClientAccess_TestFreezeFrameIteratorValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if ( (DTCFormat != DEM_DTC_FORMAT_UDS)
#  if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    && (DTCFormat != DEM_DTC_FORMAT_OBD)
#  endif
#  if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    && (DTCFormat != DEM_DTC_FORMAT_J1939)
#  endif
    )
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (NumberOfFilteredRecords == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
# if (DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
    lReturnValue = Dem_ClientAccess_StartFreezeFrameIterator(ClientId, DTCFormat, NumberOfFilteredRecords);                      /* SBSW_DEM_POINTER_FORWARD_API */

# else
    DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                         /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
    DEM_IGNORE_UNUSED_ARGUMENT(DTCFormat)                                                                                        /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
    *NumberOfFilteredRecords = 0;                                                                                                /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
# endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)*/
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETFREEZEFRAMERECORDFILTER_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetNextFilteredRecord
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFilteredRecord(
  uint8                                   ClientId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,                                                                                   /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)   RecordNumber                                                                           /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
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
  if (Dem_ClientAccess_TestFreezeFrameIteratorValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTC == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (RecordNumber == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_TestFreezeFrameFilterSet(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */

# if (DEM_CFG_SUPPORT_SRECS == STD_OFF) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_OFF)
    DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                         /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
    DEM_IGNORE_UNUSED_ARGUMENT(DTC)                                                                                              /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
    DEM_IGNORE_UNUSED_ARGUMENT(RecordNumber)                                                                                     /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
# else
    if (Dem_ClientAccess_GetNextFreezeFrameRecord(ClientId, DTC, RecordNumber) == TRUE)                                          /* SBSW_DEM_POINTER_FORWARD_API */
    {
      lReturnValue = E_OK;
    }
    else
# endif
    {
      lReturnValue = DEM_NO_SUCH_ELEMENT;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNEXTFILTEREDRECORD_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 2006, 6030, 6080 */ /* MD_DEM_14.7, MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetStatusOfDTC
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetStatusOfDTC(
  uint8  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCStatus
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
  if (DTCStatus == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_DTCSelector_ResultType lSelectionResult;

    lSelectionResult = Dem_ClientAccess_GetSelectionResult(ClientId);
    switch (lSelectionResult)
    {
    case DEM_DTCSELECTOR_SELECTION_DTC:
      lReturnValue = Dem_Dcm_GetStatusOfSelectedDTC(ClientId, DTCStatus);                                                        /* SBSW_DEM_POINTER_FORWARD_API */
      break;

    case DEM_DTCSELECTOR_SELECTION_GROUP:
    case DEM_DTCSELECTOR_SELECTION_ALL_DTCS:
    case DEM_DTCSELECTOR_SELECTION_NO_MATCH:
      lReturnValue = DEM_WRONG_DTC;
      break;

    case DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN:
      lReturnValue = DEM_WRONG_DTCORIGIN;
      break;

    case DEM_DTCSELECTOR_SELECTION_INIT:
      /* E_NOT_OK */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION);
      break;

    default:
      /* MISRA case */
      /* E_NOT_OK */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETSTATUSOFDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetDTCStatusAvailabilityMask
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCStatusAvailabilityMask(
  uint8  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCStatusMask
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                           /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

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
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCStatusMask == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    *DTCStatusMask = Dem_Cfg_GlobalStatusMask();                                                                                 /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETDTCSTATUSAVAILABILITYMASK_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetDTCByOccurrenceTime
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCByOccurrenceTime(
  uint8                                   ClientId,
  Dem_DTCRequestType                      DTCRequest,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                           /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

# if (DEM_DEV_ERROR_DETECT == STD_ON) 
  lReturnValue = E_NOT_OK;
#endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if ( (DTCRequest != DEM_FIRST_FAILED_DTC)
    && (DTCRequest != DEM_MOST_RECENT_FAILED_DTC)
    && (DTCRequest != DEM_FIRST_DET_CONFIRMED_DTC)
    && (DTCRequest != DEM_MOST_REC_DET_CONFIRMED_DTC))
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTC == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    boolean lSuccess;
    lSuccess = Dem_ClientAccess_GetDTCByOccurrenceTime(DTCRequest, DTC);                                                         /* SBSW_DEM_POINTER_FORWARD_API */

    if (lSuccess == TRUE)
    {
      lReturnValue = E_OK;
    }
    else
    {
      lReturnValue = DEM_NO_SUCH_ELEMENT;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETDTCBYOCCURRENCETIME_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetTranslationType
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
FUNC(Dem_DTCTranslationFormatType, DEM_CODE)
Dem_GetTranslationType(
  uint8 ClientId
  )
{
  Dem_DTCTranslationFormatType lTranslationFormat;

  Dem_Det_ErrorRegisterDefine()

  DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                           /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
    lTranslationFormat = 0;
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
    lTranslationFormat = 0;
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
    lTranslationFormat = 0;
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lTranslationFormat = Dem_Cfg_GlobalDtcFormat();
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETTRANSLATIONTYPE_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lTranslationFormat;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetSeverityOfDTC
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSeverityOfDTC(
  uint8  ClientId,
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_DCM_DATA)  DTCSeverity                                                               /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
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
  if (DTCSeverity == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_DTCSelector_ResultType lSelectionResult;

    lSelectionResult = Dem_ClientAccess_GetSelectionResult(ClientId);
    switch (lSelectionResult)
    {
    case DEM_DTCSELECTOR_SELECTION_DTC:
      lReturnValue = Dem_Dcm_GetSeverityOfSelectedDTC(ClientId, DTCSeverity);                                                    /* SBSW_DEM_POINTER_FORWARD_API */
      break;

    case DEM_DTCSELECTOR_SELECTION_GROUP:
    case DEM_DTCSELECTOR_SELECTION_ALL_DTCS:
    case DEM_DTCSELECTOR_SELECTION_NO_MATCH:
      lReturnValue = DEM_WRONG_DTC;
      break;

    case DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN:
      lReturnValue = DEM_WRONG_DTCORIGIN;
      break;

    case DEM_DTCSELECTOR_SELECTION_INIT:
      /* E_NOT_OK */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION);
      break;

    default:
      /* MISRA case */
      /* E_NOT_OK */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETSEVERITYOFDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetDTCSeverityAvailabilityMask
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
FUNC(Std_ReturnType, DEM_CODE) 
Dem_GetDTCSeverityAvailabilityMask(
  uint8  ClientId,
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_DCM_DATA)  DTCSeverityMask
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                           /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

# if (DEM_DEV_ERROR_DETECT == STD_ON)
  lReturnValue = E_NOT_OK;
# endif

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
  if (DTCSeverityMask == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    *DTCSeverityMask = Dem_Cfg_GlobalSeverityMask();                                                                             /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETDTCSEVERITYAVAILABILITYMASK_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetFunctionalUnitOfDTC
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetFunctionalUnitOfDTC(
  uint8  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCFunctionalUnit
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
  if (DTCFunctionalUnit == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_DTCSelector_ResultType lSelectionResult;

    lSelectionResult = Dem_ClientAccess_GetSelectionResult(ClientId);
    switch (lSelectionResult)
    {
    case DEM_DTCSELECTOR_SELECTION_DTC:
      lReturnValue = Dem_Dcm_GetFunctionalUnitOfSelectedDTC(ClientId, DTCFunctionalUnit);                                        /* SBSW_DEM_POINTER_FORWARD_API */
      break;

    case DEM_DTCSELECTOR_SELECTION_GROUP:
    case DEM_DTCSELECTOR_SELECTION_ALL_DTCS:
    case DEM_DTCSELECTOR_SELECTION_NO_MATCH:
      lReturnValue = DEM_WRONG_DTC;
      break;

    case DEM_DTCSELECTOR_SELECTION_WRONG_ORIGIN:
      lReturnValue = DEM_WRONG_DTCORIGIN;
      break;

    case DEM_DTCSELECTOR_SELECTION_INIT:
      /* E_NOT_OK */
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION);
      break;

    default:
      /* MISRA case */
      /* E_NOT_OK */
      break;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETFUNCTIONALUNITOFDTC_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DisableDTCRecordUpdate
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DisableDTCRecordUpdate(
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)     
  lReturnValue = E_NOT_OK;
#endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_ClientAccess_TestReadoutBufferValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_ClientAccess_DisableDTCRecordUpdate(ClientId);

    if (lReturnValue == E_NOT_OK)
    {
      /* new request with different parameters than ongoing request */
#  if (DEM_DEV_ERROR_DETECT == STD_ON)
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
#  endif
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DISABLEDTCRECORDUPDATE_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_EnableDTCRecordUpdate
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
Dem_EnableDTCRecordUpdate(
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;
  Dem_Det_ErrorRegisterDefine()

# if (DEM_DEV_ERROR_DETECT == STD_ON)     
  lReturnValue = E_NOT_OK;
#endif
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (Dem_ClientAccess_TestReadoutBufferValid(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_ClientAccess_EnableDTCRecordUpdate(ClientId);
    
#  if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (lReturnValue == E_NOT_OK)
    {
      Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
    }
#  endif
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_ENABLEDTCRECORDUPDATE_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_SelectFreezeFrameData
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_SelectFreezeFrameData(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint8, AUTOMATIC)  RecordNumber
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
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_Dcm_SRec_SelectFirstSource(ClientId, RecordNumber);

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SELECTFREEZEFRAMEDATA_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetNextFreezeFrameData
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
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFreezeFrameData(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize
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
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_ClientAccess_TestSnapshotRecordSelected(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_ClientAccess_TestDTCRecordUpdateDisabled(ClientId) == FALSE)
    {
      lReturnValue = DEM_PENDING;
    }
    else
    {
      lReturnValue = Dem_Dcm_SRec_ReadNextRecord(ClientId, DestBuffer, BufSize);                                                 /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
    }
  }
  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNEXTFREEZEFRAMEDATA_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetSizeOfFreezeFrameSelection
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfFreezeFrameSelection(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfFreezeFrame
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
  if (SizeOfFreezeFrame == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    /* missing prior call to Dem_SelectDTC() */
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_ClientAccess_TestSnapshotRecordSelected(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_ClientAccess_TestDTCRecordUpdateDisabled(ClientId) == FALSE)
    {
      lReturnValue = DEM_PENDING;
    }
    else
    {
      lReturnValue = Dem_Dcm_SRec_GetSize(ClientId, SizeOfFreezeFrame);                                                          /* SBSW_DEM_POINTER_FORWARD_API */
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETSIZEOFFREEZEFRAMESELECTION_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_SelectExtendedDataRecord
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_SelectExtendedDataRecord(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint8, AUTOMATIC)  ExtendedDataNumber
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
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_Dcm_ERec_SelectRecord(ClientId, ExtendedDataNumber);

    lReturnValue = E_OK;
  }
  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SELECTEXTENDEDDATARECORD_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetNextExtendedDataRecord
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
  FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextExtendedDataRecord(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,                                                                             /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize                                                                                /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
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
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    /* missing prior call to Dem_SelectDTC() */
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_ClientAccess_TestExtendedRecordSelected(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_ClientAccess_TestDTCRecordUpdateDisabled(ClientId) == FALSE)
    {
      lReturnValue = DEM_PENDING;
    }
    else
    {
      lReturnValue = Dem_Dcm_ERec_ReadNextRecord(ClientId, DestBuffer, BufSize);                                                 /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETNEXTEXTENDEDDATARECORD_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_GetSizeOfExtendedDataRecordSelection
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
Dem_GetSizeOfExtendedDataRecordSelection(
  CONST(uint8, AUTOMATIC) ClientId,                                                                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfExtendedDataRecord                                                               /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
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
  if (SizeOfExtendedDataRecord == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
  if (Dem_ClientAccess_GetSelectionResult(ClientId) == DEM_DTCSELECTOR_SELECTION_INIT)
  {
    /* missing prior call to Dem_SelectDTC() */
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_ClientAccess_TestDTCRecordUpdateRequested(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
  if (Dem_ClientAccess_TestExtendedRecordSelected(ClientId) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    if (Dem_ClientAccess_TestDTCRecordUpdateDisabled(ClientId) == FALSE)
    {
      lReturnValue = DEM_PENDING;
    }
    else
    {
      lReturnValue = Dem_Dcm_ERec_GetSize(ClientId, SizeOfExtendedDataRecord);                                                   /* SBSW_DEM_POINTER_FORWARD_API */
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DisableDTCSetting
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
Dem_DisableDTCSetting(
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;

  Dem_Det_ErrorRegisterDefine()

  DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                           /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

# if (DEM_DEV_ERROR_DETECT == STD_ON)     
  lReturnValue = E_NOT_OK;
#endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_EnableCondition_ResetEnableConditionFulfilled(DEM_ENABLECONDITION_CONTROLDTCSETTING);

    Dem_Notifications_ControlDtcSettingChanged(FALSE);

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DISABLEDTCSETTING_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_EnableDTCSetting
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
Dem_EnableDTCSetting(
  uint8  ClientId
  )
{
  Std_ReturnType lReturnValue;

  Dem_Det_ErrorRegisterDefine()

  DEM_IGNORE_UNUSED_ARGUMENT(ClientId)                                                                                           /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */

# if (DEM_DEV_ERROR_DETECT == STD_ON)    
  lReturnValue = E_NOT_OK;
#endif

  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* ----- Development Error Checks ---------------------------------------- */
# if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitState_TestMasterInState(DEM_INITSTATE_INITIALIZED) == FALSE)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_UNINIT)
  }
  else
  if (ClientId >= Dem_ClientAccess_GlobalClientCount())
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_EnableCondition_SetEnableConditionFulfilled(DEM_ENABLECONDITION_CONTROLDTCSETTING);

    Dem_Notifications_ControlDtcSettingChanged(TRUE);
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_ENABLEDTCSETTING_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif

                                                    /* Dcm <-> Dem : OBD DTR */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_DTR == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DcmGetDTRData
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetDTRData(
  uint8 Obdmid,
  uint8 TIDindex,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) TIDvalue,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) UaSID,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) Testvalue,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) Lowlimvalue,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) Upplimvalue
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
  if (TIDvalue == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (UaSID == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Testvalue == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Lowlimvalue == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (Upplimvalue == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_DtrIF_GetDataAndTidOfMid(Obdmid, TIDindex, TIDvalue, UaSID, Testvalue, Lowlimvalue, Upplimvalue);         /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMGETDTRDATA, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6060, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR, MD_MSR_STMIF */
#endif

                                                   /* Dcm <-> Dem : OBD MIDs */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_DTR == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DcmGetAvailableOBDMIDs
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
Dem_DcmGetAvailableOBDMIDs(
  uint8 Obdmid,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  Obdmidvalue
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
  if (Obdmidvalue == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    uint32 lMidValue;
    if (Dem_DtrIF_GetSupportedMidValue(Obdmid, &lMidValue) == TRUE)                                                              /* SBSW_DEM_POINTER_FORWARD_STACK */
    {
      *Obdmidvalue = lMidValue;                                                                                                  /* SBSW_DEM_POINTER_WRITE_API */
      lReturnValue = E_OK;
    }
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMGETAVAILABLEOBDMIDS, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DcmGetNumTIDsOfOBDMID
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetNumTIDsOfOBDMID(
  uint8 Obdmid,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) numberOfTIDs
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
  if (numberOfTIDs == NULL_PTR)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    lReturnValue = Dem_DtrIF_GetTidCountOfMid(Obdmid, numberOfTIDs);                                                             /* SBSW_DEM_POINTER_FORWARD_API */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMGETNUMTIDSOFOBDMID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) */


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_DcmGetOBDFreezeFrameData
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
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetOBDFreezeFrameData(
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,                                                                                   /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,                                                                             /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize                                                                                /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
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
  if (NULL_PTR == DTC)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (NULL_PTR == DestBuffer)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (NULL_PTR == BufSize)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    uint8  lSelectedIndex;
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    boolean lModificationDetected;
# else
    DEM_IGNORE_UNUSED_ARGUMENT(DTC)                                                                                              /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
    DEM_IGNORE_UNUSED_ARGUMENT(DestBuffer)                                                                                       /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
    DEM_IGNORE_UNUSED_ARGUMENT(BufSize)                                                                                          /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
# endif

    /* ----- Implementation ------------------------------------------------ */
# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    lMemoryIndex = Dem_Cfg_MemoryFreezeFrameIndex();

    /* Check if provided buffer is large enough */
    if (*BufSize >= (Dem_Cfg_GlobalObdIIFFUdsSize() - 1)) /* -1 as RecordNumber is not taken into account here */
    {
      do
      {
        lModificationDetected = FALSE;
        /* copy Mode02 index on the stack as it might change in the background */
        lSelectedIndex = Dem_Mem_FreezeFrameIndexMode02;
  
        /* first check if FF0 is available */
        if (lSelectedIndex != Dem_Cfg_GlobalObdIIFFCount())
        {
          uint32 lUdsDtc;
          uint8 lUpdateState;

          lUdsDtc = Dem_Cfg_EventUdsDtc(Dem_Mem_FreezeFrameGetEvent(lSelectedIndex));
          lUpdateState = Dem_Memory_UpdateGetState(lMemoryIndex);

          if (Dem_Memory_TestUpdateInProgress(lUpdateState) == FALSE)
          {
            Dem_Data_DestinationBuffer lDestinationBuffer;
            Dem_DataReportIF_BufferIndexType lBufferIdx;                                                                         /* PRQA S 0759 */ /* MD_MSR_18.4 */
            lBufferIdx.FreezeFrameIndex = lSelectedIndex;
            /* Initialize a DestinationBuffer Context. */
            Dem_Data_InitDestinationBuffer(&lDestinationBuffer, DestBuffer, *BufSize);                                           /* SBSW_DEM_CALL_DESTINATIONBUFFER_INIT */

            Dem_DataReportIF_ObdIIFreezeFrameCopyUdsData(lBufferIdx,
                                                         &lDestinationBuffer, 
                                                         DEM_DATAREPORTIF_SOURCE_OBDII_FF_BUFFER);                               /* SBSW_DEM_POINTER_LOCAL_DESTINATIONBUFFER */


            if (lUpdateState != Dem_Memory_UpdateGetState(lMemoryIndex))
            { /* The OBD II FF block has been modified while trying to copy the stored data. */                                  /* PRQA S 0715 */  /* MD_MSR_1.1_715 */
              /* We cannot be sure it is still used by the same event nor data, so start from the
              beginning */
              lModificationDetected = TRUE;
            }
            else if ( (Dem_Cfg_EventUdsDtc(Dem_Mem_FreezeFrameGetEvent(lSelectedIndex)) == lUdsDtc)                              /* PRQA S 0715, 3415 */ /* MD_MSR_1.1_715, MD_DEM_12.4_cf */
              && (Dem_Mem_FreezeFrameGetEvent(lSelectedIndex) != DEM_EVENT_INVALID) )
            {                                                                                                                    /* PRQA S 0715 */  /* MD_MSR_1.1_715 */
              /* verify that the FreezeFrame EventId is still the same and valid */
              lReturnValue = E_OK;
              *DTC = lUdsDtc;                                                                                                    /* SBSW_DEM_POINTER_WRITE_API */
              *BufSize = (uint16)(Dem_Cfg_GlobalObdIIFFUdsSize() - 1); /* -1 as RecordNumber is not taken into account here */   /* SBSW_DEM_POINTER_WRITE_API */
            }
            else
            { /* EventId has changed, so the freeze frame data too */                                                            /* PRQA S 0715 */  /* MD_MSR_1.1_715 */
               lReturnValue = E_OK;
              *BufSize = 0;                                                                                                      /* SBSW_DEM_POINTER_WRITE_API */
            }
          }
          else
          {
            /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
            the update to complete. The requested data is not available at this moment. */
            lReturnValue = E_NOT_OK;
          }
        }
        else
        { /* OBD freezeFrame not available */
          *BufSize = 0;                                                                                                            /* SBSW_DEM_POINTER_WRITE_API */
          lReturnValue  = E_OK;
        }
      }
      while (lModificationDetected == TRUE);
    }
    /* lReturnValue = E_NOT_OK initially set */
# endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMGETOBDFREEZEFRAMEDATA_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

                                           /* Dcm <-> Dem : OBD Freeze Frame */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DcmReadDataOfOBDFreezeFrame
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
Dem_DcmReadDataOfOBDFreezeFrame(
  uint8  PID,
  uint8  DataElementIndexOfPID,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  BufSize
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
  if (NULL_PTR == DestBuffer)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (NULL_PTR == BufSize)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    Dem_EventIdType lFreezeFrameEventId;
    uint8 lSelectedIndex;

    /* ----- Implementation ------------------------------------------------ */
    Dem_Cfg_MemoryIndexType lMemoryIndex;
    boolean lModificationDetected;
    lMemoryIndex = Dem_Cfg_MemoryFreezeFrameIndex();

    do
    {
      lModificationDetected = FALSE;

      /* copy Mode02 index on the stack as it might change in the background */
      lSelectedIndex = Dem_Mem_FreezeFrameIndexMode02;

      /* Verify that OBD FreezeFrame is available and visible */
      if (Dem_Cfg_GlobalObdIIFFCount() != lSelectedIndex)
      {
        uint8 lUpdateState;
        lUpdateState = Dem_Memory_UpdateGetState(lMemoryIndex);

        if (Dem_Memory_TestUpdateInProgress(lUpdateState) == FALSE)
        {
          lFreezeFrameEventId = Dem_Mem_FreezeFrameGetEvent(lSelectedIndex);
          {
            lReturnValue = Dem_DataReportIF_ObdIIFreezeFrameCopyPidData(lSelectedIndex, PID, DataElementIndexOfPID, DestBuffer, BufSize);  /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */

            if ( (lReturnValue == E_OK)                                                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
              && (lUpdateState != Dem_Memory_UpdateGetState(lMemoryIndex)) )
            { /* The OBD II FF block has been modified while trying to copy the stored data. */
              /* We cannot be sure it is still used by the same event nor data, so start from the
              beginning */
              lReturnValue = E_NOT_OK;
              lModificationDetected = TRUE;
            }
            else if ( (Dem_Mem_FreezeFrameGetEvent(lSelectedIndex) != lFreezeFrameEventId)                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
              && (Dem_Mem_FreezeFrameGetEvent(lSelectedIndex) != DEM_EVENT_INVALID) )
            {                                                                                                                    /* PRQA S 0715 */  /* MD_MSR_1.1_715 */
              /* Verify that Freeze Frame event Id has not changed, no data can be returned */
              lReturnValue = E_NOT_OK;
            }
            else
            {                                                                                                                    /* PRQA S 0715 */  /* MD_MSR_1.1_715 */
              /* MISRA */
            }
          }
        }
        else
        {
          /* The caller task has higher priority than Dem_MainFunction, but we cannot 'wait' for
          the update to complete. The requested data is not available at this moment. */
          lReturnValue = E_NOT_OK;
        }
      }
    }
    while (lModificationDetected == TRUE);
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFOBDFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif  /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_DcmGetDTCOfOBDFreezeFrame
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetDTCOfOBDFreezeFrame(
  uint8  FrameNumber,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC
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
  if (NULL_PTR == DTC)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
  if (FrameNumber != 0x00)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_DATA)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    uint32 lObdDtc;
    uint8 lSelectedIndex;

    /* ----- Implementation ------------------------------------------------ */
    /* copy Mode02 index on the stack as it might change in the background */
    lSelectedIndex = Dem_Mem_FreezeFrameIndexMode02;

    if (Dem_Cfg_GlobalObdIIFFCount() != lSelectedIndex)
    {
      lObdDtc = Dem_Cfg_EventObdDtc(Dem_Mem_FreezeFrameGetEvent(lSelectedIndex));

      if (DEM_CFG_DTC_OBD_INVALID != lObdDtc)
      {
        *DTC = (uint32)(lObdDtc << 8);                                                                                         /* SBSW_DEM_POINTER_WRITE_API */
        lReturnValue = E_OK;
      }
    }
    /* else No Freeze Frame stored, return value lReturnValue = E_NOT_OK initially set */
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMGETDTCOFOBDFREEZEFRAME_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  DEM_IGNORE_UNUSED_ARGUMENT(FrameNumber)                                                                                        /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON) */


                                                   /* Dcm <-> Dem : OBD PIDs */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID01 == STD_ON)
/* ****************************************************************************
 % Dem_DcmReadDataOfPID01
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID01(
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID01value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
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
  if (NULL_PTR == PID01value)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    Dem_Dcm_ReadDataOfPID01(PID01value, 4);                                                                                      /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFPID01_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID01 == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID1C == STD_ON)
/* ****************************************************************************
 % Dem_DcmReadDataOfPID1C
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID1C(
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID1Cvalue                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
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
  if (NULL_PTR == PID1Cvalue)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    *PID1Cvalue = Dem_Cfg_GlobalObdRequirements();                                                                               /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFPID1C_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID1C == STD_ON) */


#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID21 == STD_ON)
/* ****************************************************************************
 % Dem_DcmReadDataOfPID21
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID21(
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID21value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
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
  if (NULL_PTR == PID21value)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    uint32  lOdometerValue;
    uint32  lStoredOdometerValue;

    /* ----- Implementation ------------------------------------------------ */
    /* If the Distance travelled with MIL on is latched due to inactive MIL, the mileage can be taken directly.
       If the MIL is active, the difference between the stored value and the current odometer value is calculated */

/* >>>> -------------------------------- Enter Critical Section: NonAtomic32bit */
    Dem_EnterCritical_NonAtomic32bit();                                                                                          /* PRQA S 3109 */ /* MD_MSR_14.3 */

    lStoredOdometerValue = Dem_Mem_GetOdometerMilOn();

    Dem_LeaveCritical_NonAtomic32bit();                                                                                          /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: NonAtomic32bit */

    if (DEM_MEM_TEST_ODOMETER_ISINVALID(lStoredOdometerValue) == FALSE)
    {
      if (Dem_Indicator_TestMilReportedActive() == TRUE)
      { /* MIL is considered active, get current Odometer value */
        if (Dem_Data_GetObdOdometer(&lOdometerValue) != E_OK)                                                                    /* SBSW_DEM_POINTER_FORWARD_STACK */
        { /* application currently can't provide a valid odometer */
          lOdometerValue = DEM_DATA_MAX_OBD_ODOMETER;
        }
        else
        {
          lOdometerValue = lOdometerValue - lStoredOdometerValue;
        }
      }
      else
      { /* MIL is considered inactive */
        lOdometerValue = lStoredOdometerValue;
      }

      /* The Odometer shall be latched at 0xFFFF */
      if (lOdometerValue > DEM_DATA_MAX_OBD_ODOMETER)
      {
        lOdometerValue = DEM_DATA_MAX_OBD_ODOMETER;
      }
    }
    else
    { /* currently no odometer available */
      lOdometerValue = DEM_DATA_MAX_OBD_ODOMETER;
    }

    PID21value[0] = Dem_GetLoHiByte(lOdometerValue);                                                                             /* SBSW_DEM_POINTER_WRITE_API */
    PID21value[1] = Dem_GetLoLoByte(lOdometerValue);                                                                             /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFPID21_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID21 == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID30 == STD_ON)
/* ****************************************************************************
 % Dem_DcmReadDataOfPID30
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID30(
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID30value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
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
  if (NULL_PTR == PID30value)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    *PID30value = Dem_Mem_GetWarmUpCountSinceClear();                                                                            /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFPID30_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID30 == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID31 == STD_ON)
/* ****************************************************************************
 % Dem_DcmReadDataOfPID31
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
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID31(
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID31value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
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
  if (NULL_PTR == PID31value)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    uint32 lCurrentOdometer;
    uint32 lLastOdometer;

    /* ----- Implementation ------------------------------------------------ */
    lCurrentOdometer = 0;

/* >>>> -------------------------------- Enter Critical Section: NonAtomic32bit */
    Dem_EnterCritical_NonAtomic32bit();                                                                                          /* PRQA S 3109 */ /* MD_MSR_14.3 */

    lLastOdometer = Dem_Mem_GetOdometerAtClear();

    Dem_LeaveCritical_NonAtomic32bit();                                                                                          /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: NonAtomic32bit */

    if (DEM_MEM_TEST_ODOMETER_ISINVALID(lLastOdometer) == FALSE)
    {
      if (Dem_Data_GetObdOdometer(&lCurrentOdometer) == E_OK)                                                                    /* SBSW_DEM_POINTER_FORWARD_STACK */                                                        
      { /* Application returned valid odometer value, validate that returned
           odometer is greater than stored odometer from last clear */
        if (lCurrentOdometer >= lLastOdometer)
        { /* use lCurrentOdometer variable for delta result */
          lCurrentOdometer = lCurrentOdometer - lLastOdometer;

          /* reported odometer value shall be latched at 0xffff */
          if (lCurrentOdometer > DEM_DATA_MAX_OBD_ODOMETER)
          {
            lCurrentOdometer = DEM_DATA_MAX_OBD_ODOMETER;
          }
        }
        else
        { /* returned odometer is smaller than stored odometer */
          lCurrentOdometer = DEM_DATA_MAX_OBD_ODOMETER;
        }
      }
      else
      { /* Application can not provide a valid odometer value, set maximum value */
        lCurrentOdometer = DEM_DATA_MAX_OBD_ODOMETER;
      }
    }
    else
    { /* currently no odometer available */
      lCurrentOdometer = DEM_DATA_MAX_OBD_ODOMETER;
    }

    PID31value[0] = Dem_GetLoHiByte(lCurrentOdometer);                                                                           /* SBSW_DEM_POINTER_WRITE_API */
    PID31value[1] = Dem_GetLoLoByte(lCurrentOdometer);                                                                           /* SBSW_DEM_POINTER_WRITE_API */
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFPID31_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID31 == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID41 == STD_ON)
/* ****************************************************************************
 % Dem_DcmReadDataOfPID41
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID41(
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID41value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
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
  if (NULL_PTR == PID41value)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */

    PID41value[0] = 0x00; /* reserved */                                                                                         /* SBSW_DEM_POINTER_WRITE_API */
# if (DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_OFF)
    Dem_Data_GetPid41ComprehensiveOnly(PID41value, 4);                                                                           /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
# else
    Dem_Data_GetPid41(PID41value, 4);                                                                                            /* SBSW_DEM_POINTER_FORWARD_API_ARGUMENT_BUFFER */
# endif
    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFPID41_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID41 == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID4D == STD_ON)
/* ****************************************************************************
 % Dem_DcmReadDataOfPID4D
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID4D(
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID4Dvalue                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
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
  if (NULL_PTR == PID4Dvalue)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    uint16 lPid4D;

    /* ----- Implementation ------------------------------------------------ */
    lPid4D = Dem_Mem_GetEngineTimeMilOn();

    PID4Dvalue[0] = Dem_GetHiByte(lPid4D);                                                                                       /* SBSW_DEM_POINTER_WRITE_API */
    PID4Dvalue[1] = Dem_GetLoByte(lPid4D);                                                                                       /* SBSW_DEM_POINTER_WRITE_API */

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFPID4D_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID4D == STD_ON) */


#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID4E == STD_ON)
/* ****************************************************************************
 % Dem_DcmReadDataOfPID4E
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID4E(
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID4Evalue                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
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
  if (NULL_PTR == PID4Evalue)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    uint16 lPid4E;

    /* ----- Implementation ------------------------------------------------ */
    lPid4E = Dem_Mem_GetEngineTimeSinceClear();

    PID4Evalue[0] = Dem_GetHiByte(lPid4E);                                                                                       /* SBSW_DEM_POINTER_WRITE_API */
    PID4Evalue[1] = Dem_GetLoByte(lPid4E);                                                                                       /* SBSW_DEM_POINTER_WRITE_API */

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFPID4E_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID4E == STD_ON) */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PID91 == STD_ON)
/* ****************************************************************************
 % Dem_DcmReadDataOfPID91
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
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID91(
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID91value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
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
  if (NULL_PTR == PID91value)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_POINTER)
  }
  else
#  if (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON)
  if (GetCurrentApplicationID() != DEM_CFG_MASTER_APPLICATION_ID)
  {
    Dem_Det_ErrorRegisterSet(DEM_E_WRONG_CONDITION)
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ------------------------------------------------ */
    PID91value[0] = Dem_Dcm_TranslateActivationMode(Dem_Indicator_GlobalIndicatorActivationMode());                              /* SBSW_DEM_POINTER_WRITE_API */

    PID91value[1] = 0x00; /* continuous MI counter is latched at 255 hours */                                                    /* SBSW_DEM_POINTER_WRITE_API */
    /* internal resolution of 1min/bit must be converted to 1h/bit */
    PID91value[2] = (uint8)(Dem_Mem_GetContinuousMiCounter()/60);                                                                /* SBSW_DEM_POINTER_WRITE_API */

    PID91value[3] = 0x00U; /* B1 counter is latched at 255 hours */                                                              /* SBSW_DEM_POINTER_WRITE_API */
    /* internal resolution of 1min/bit must be converted to 1h/bit */
    PID91value[4] = (uint8)(Dem_Mem_GetB1Counter()/60);                                                                          /* SBSW_DEM_POINTER_WRITE_API */

    lReturnValue = E_OK;
  }

  /* ----- Development Error Report ---------------------------------------- */
# if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_DCMREADDATAOFPID91_APIID, Dem_Det_ErrorRegisterGet());
  }
# endif

  return lReturnValue;
}
#endif /* (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PID91 == STD_ON) */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DCMAPI_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DcmAPI_Implementation.h
 *********************************************************************************************************************/
