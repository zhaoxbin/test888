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
/*! \addtogroup Dem_DtrIF
 *  \{
 *  \file       Dem_DtrIF_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
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

#if !defined (DEM_DTRIF_IMPLEMENTATION_H)
#define DEM_DTRIF_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DtrIF_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Dtr_Implementation.h"
#include "Dem_MidLookup_Implementation.h"

                                                  /* Subcomponents callbacks */
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 * SUBCOMPONENT DATA
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_DtrIF_Private
 * \{
 */

# if (DEM_FEATURE_NEED_DTR_CONFIGCHECK == STD_ON)
/* ****************************************************************************
 % Dem_Dtr_TestDtrConfigured
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrIF_TestDtrConfigured(
  void
  )
{
  boolean lreturn;
  if (Dem_Dtr_GetGlobalDtrCount() > 0)
  {
    lreturn = TRUE;
  }
  else
  {
    lreturn = FALSE;
  }
  return lreturn;
}
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h" 

/* ********************************************************************************************************************
 * SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_DtrIF_Public
 * \{
 */

/* ****************************************************************************
 % Dem_DtrIF_IsValidHandle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DtrIF_IsValidHandle(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  return Dem_Dtr_IsValidHandle(DtrId);
}

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_DtrIF_SetDtrValues
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrIF_SetDtrValues(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(uint16, AUTOMATIC) TestValue,
  CONST(uint16, AUTOMATIC) LowerLimit,
  CONST(uint16, AUTOMATIC) UpperLimit
  )
{
# if (DEM_FEATURE_NEED_DTR_CONFIGCHECK == STD_ON)
  if (Dem_DtrIF_TestDtrConfigured() == TRUE)
# endif
  {
    Dem_Dtr_SetDtrValues(DTRId, TestValue, LowerLimit, UpperLimit);
  }
}
#endif

/* ****************************************************************************
 % Dem_DtrIF_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrIF_Init(
  void
  )
{
# if (DEM_FEATURE_NEED_DTR_CONFIGCHECK == STD_ON)
  if (Dem_DtrIF_TestDtrConfigured() == TRUE)
# endif
  {
    Dem_Dtr_Init();
    Dem_MidLookup_Init();
  }
}

/* ****************************************************************************
 % Dem_DtrIF_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrIF_PreInit(
  void
  )
{
# if (DEM_FEATURE_NEED_DTR_CONFIGCHECK == STD_ON)
  if (Dem_DtrIF_TestDtrConfigured() == TRUE)
# endif
  {
    Dem_Dtr_PreInit();
    Dem_MidLookup_PreInit();
  }
}

/* ****************************************************************************
 % Dem_DtrIF_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrIF_MainFunction(
  void
  )
{
  Dem_Dtr_MainFunction();
}

/* ****************************************************************************
 % Dem_DtrIF_Shutdown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrIF_Shutdown(
  void
  )
{
  Dem_Dtr_Shutdown();
}

/* ****************************************************************************
 % Dem_DtrIF_EventAvailabilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrIF_EventAvailabilityChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_FEATURE_NEED_DTR_CONFIGCHECK == STD_ON)
  if (Dem_DtrIF_TestDtrConfigured() == TRUE)
# endif
  {
    Dem_Dtr_EventAvailabilityChanged(EventId);
  }
}

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_DtrIF_DTCSuppressionChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrIF_DTCSuppressionChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_FEATURE_NEED_DTR_CONFIGCHECK == STD_ON)
  if (Dem_DtrIF_TestDtrConfigured() == TRUE)
# endif
  {
    Dem_Dtr_DTCSuppressionChanged(EventId);
  }
}
#endif

/* ****************************************************************************
 % Dem_DtrIF_ResetDtrsOfEvent
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
Dem_DtrIF_ResetDtrsOfEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_FEATURE_NEED_DTR_CONFIGCHECK == STD_ON)
  if (Dem_DtrIF_TestDtrConfigured() == TRUE)
# endif
  {
    if (EventId == DEM_EVENT_INVALID)
    {
      Dem_Dtr_ResetDtrsWithoutEvent();
    }
    else
    {
      Dem_Dtr_ResetDtrsOfEvent(EventId);
    }
  }
}

/* ****************************************************************************
 % Dem_DtrIF_SetDtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DtrIF_SetDtr(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(sint32, AUTOMATIC) TestResult,
  CONST(sint32, AUTOMATIC) LowerLimit,
  CONST(sint32, AUTOMATIC) UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC) Ctrlval
  )
{
  /* Check for configured Dtr is done on API top level */
  return Dem_Dtr_SetDtr(DTRId, TestResult, LowerLimit, UpperLimit, Ctrlval);
}

/* ****************************************************************************
 % Dem_DtrIF_UpdateMidVisibility
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DtrIF_UpdateMidVisibility(
  void
  )
{
# if (DEM_FEATURE_NEED_DTR_CONFIGCHECK == STD_ON)
  if (Dem_DtrIF_TestDtrConfigured() == TRUE)
# endif
  {
    Dem_MidLookup_UpdateMidVisibility();
  }
}

/* ****************************************************************************
 % Dem_DtrIF_GetSupportedMidValue
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
Dem_DtrIF_GetSupportedMidValue(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONST(uint8, AUTOMATIC)  Mid,
CONSTP2VAR(uint32, AUTOMATIC, AUTOMATIC)  MidValue
)
{
  boolean lReturnValue;

# if (DEM_FEATURE_NEED_DTR_CONFIGCHECK == STD_ON)
  if (Dem_DtrIF_TestDtrConfigured() == FALSE)
  {
    lReturnValue = FALSE;
  }
  else
# endif
  {
    if (Dem_MidLookup_IsSupportedMid(Mid) == TRUE)
    {
      *MidValue = Dem_MidLookup_GetSupportedMidValue(Mid);                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      lReturnValue = TRUE;
    }
    else
    {
      lReturnValue = FALSE;
    }
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_DtrIF_GetTidCountOfMid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_DtrIF_GetTidCountOfMid(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  Mid,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  TidCount
  )
{
  Std_ReturnType lReturn;
  # if (DEM_FEATURE_NEED_DTR_CONFIGCHECK == STD_ON)
  if (Dem_DtrIF_TestDtrConfigured() == FALSE)
  {
    lReturn = E_NOT_OK;
  }
  else
# endif
  {
    lReturn = Dem_MidLookup_GetTidCountOfMid(Mid, TidCount);                                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  return lReturn;
}

/* ****************************************************************************
 % Dem_DtrIF_GetDataAndTidOfMid
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
Dem_DtrIF_GetDataAndTidOfMid(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC) Mid,
  CONST(uint8, AUTOMATIC) TidIndex,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  Tid,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  UaSid,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) TestResult,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) LowerLimit,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) UpperLimit
)
{
  uint8 lTid;
  DTRIdType lDtrId;
  Std_ReturnType lReturnValue;

# if (DEM_FEATURE_NEED_DTR_CONFIGCHECK == STD_ON)
  if (Dem_DtrIF_TestDtrConfigured() == FALSE)
  {
    lReturnValue = E_NOT_OK;
  }
  else
# endif
  {
    lDtrId = Dem_MidLookup_FindDtrId(Mid, TidIndex, &lTid);                                                                        /* SBSW_DEM_POINTER_FORWARD_STACK */
    if (Dem_DtrIF_IsValidHandle(lDtrId) == TRUE)
    {
      *Tid = lTid;                                                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      *UaSid = Dem_Dtr_GetUaSId(lDtrId);                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

      /* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
      Dem_EnterCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */

      *TestResult = Dem_Dtr_GetTestValue(lDtrId);                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      *LowerLimit = Dem_Dtr_GetLowerLimit(lDtrId);                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      *UpperLimit = Dem_Dtr_GetUpperLimit(lDtrId);                                                                                 /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

      Dem_LeaveCritical_DiagMonitor();                                                                                             /* PRQA S 3109 */ /* MD_MSR_14.3 */
      /* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

      lReturnValue = E_OK;
    }
    else
    {
      lReturnValue = E_NOT_OK;
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6060 */ /* MD_MSR_STCAL, MD_MSR_STPAR */

/*!
 * \}
 */

#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_DTRIF_IMPLEMENTATION_H */
/*!
 * \}
 */
/* *********************************************************************************************************************
 *  END OF FILE: Dem_DtrIF_Implementation.h
 **********************************************************************************************************************/
