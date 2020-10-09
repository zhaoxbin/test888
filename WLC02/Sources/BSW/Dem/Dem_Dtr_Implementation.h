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
/*! \addtogroup Dem_Dtr
 *  \{
 *  \file       Dem_Dtr_Implementation.h
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

#if !defined (DEM_DTR_IMPLEMENTATION_H)
#define DEM_DTR_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Dtr_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

#include "Dem_Scheduler_Implementation.h"
#include "Dem_EventInternalStatus_Implementation.h"
#include "Dem_DebouncingState_Implementation.h"
#include "Dem_Nvm_Implementation.h"
#include "Dem_MemCopy.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_DTC_Interface.h"
#include "Dem_Event_Interface.h"
#include "Dem_MidLookup_Interface.h"
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \defgroup  Dem_Dtr_Validity  Macro indicating an invalid DTR Id
 * Macro indicating an invalid DTR Id
 * \{
 */
#define DEM_DTR_INVALIDDTRID                          Dem_Dtr_GetGlobalDtrCount()  /*!< Invalid DTR Id */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Dtr_ConversionStatus  Macros encoding DTR conversion status values
 * Macros encoding DTR conversion status values
 * \{
 */
#define DEM_DTR_OK                                    (0x00U)  /*!< DTR conversion OK */
#define DEM_DTR_CONVERSION_UNDERFLOW                  (0x01U)  /*!< DTR conversion undeflow */
#define DEM_DTR_CONVERSION_OVERFLOW                   (0x02U)  /*!< DTR conversion overflow */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Dtr_TestValueProperties  Macros encoding test value properties
 * Macros encoding test value properties
 * \{
 */
#define DEM_DTR_TEST_VALUE_WITHIN_LIMITS              (0x00U)  /*!< test value within limits */
#define DEM_DTR_TEST_VALUE_VIOLATES_LOWER_LIMIT       (0x01U)  /*!< test value exceeds the upper limit */
#define DEM_DTR_TEST_VALUE_VIOLATES_UPPER_LIMIT       (0x02U)  /*!< test value is under the lower limit */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Dtr_Visibility  Macros encoding DTR visibility values
 * Macros encoding DTR visibility values
 * \{
 */
#define DEM_DTR_VISIBLE                               (0x00U)  /*!< DTR is visible */
#define DEM_DTR_INVISIBLE                             (0x01U)  /*!< DTR is invisible */
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/*! Variable to indicate a DTR modification. Used to serialize NvM calls, */
DEM_LOCAL volatile VAR(boolean, DEM_VAR_NOINIT)  Dem_Dtr_DataChanged;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITION
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_Dtr_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_Dtr_GetGlobalDtrCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_Dtr_GetGlobalDtrCount(
  void
  )
{
  uint16 lReturnValue;
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = Dem_Cfg_GetSizeOfDtrTable();
#else
  lReturnValue = 0;
#endif
  return lReturnValue;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \addtogroup Dem_Dtr_Private
 * \{
 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_Dtr_EventDtrIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dtr_EventDtrIterExists(
  CONSTP2CONST(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC) IterPtr
)
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_Dtr_EventDtrIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_Dtr_EventDtrIterGet(
  CONSTP2CONST(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_DTRTABLEIND == STD_ON)
  return Dem_Cfg_GetDtrTableInd(IterPtr->mIdx);
# else
  return DEM_DTR_INVALIDDTRID;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_Dtr_EventDtrIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_EventDtrIterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC) IterPtr                                                             /* PRQA S 3673 */ /* MD_DEM_16.7_False */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_DTRTABLEIND == STD_ON)
  IterPtr->mIdx = Dem_Cfg_GetDtrTableIndStartIdxOfEventTable(EventId);                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetDtrTableIndEndIdxOfEventTable(EventId);                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# else
  IterPtr->mIdx = 0;                                                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = 0;                                                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# endif
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_Dtr_EventDtrIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_EventDtrIterNext(
  CONSTP2VAR(Dem_Cfg_EventDtrIterType, AUTOMATIC, AUTOMATIC) IterPtr                                                             /* PRQA S 3673 */ /* MD_DEM_16.7_False */
  )
{
  IterPtr->mIdx += 1;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

/* ****************************************************************************
 % Dem_Dtr_RoundFloatToInt
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Dtr_RoundFloatToInt(
  CONST(float32, AUTOMATIC)  Value
  )
{
  return (uint16)(Value + 0.5);
}

/* ****************************************************************************
 % Dem_Dtr_GetRelatedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Dtr_GetRelatedEvent(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  Dem_EventIdType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = ((Dem_EventIdType)(Dem_Cfg_GetEventTableIdxOfDtrTable(DtrId)));
#else
  lReturnValue = DEM_EVENT_INVALID;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Dtr_GetUpdateKind
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Dtr_GetUpdateKind(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  uint8 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = (uint8)(Dem_Cfg_GetUpdateKindOfDtrTable(DtrId));
#else
  lReturnValue = DEM_DTR_UPDATE_ALWAYS;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Dtr_GetDivisor
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(float32, DEM_CODE)
Dem_Dtr_GetDivisor(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  float32 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = Dem_Cfg_GetDivisorOfDtrTable(DtrId);
#else
  lReturnValue = 1.0f;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Dtr_GetLinearFactor
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(float32, DEM_CODE)
Dem_Dtr_GetLinearFactor(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  float32 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = Dem_Cfg_GetLinearFactorOfDtrTable(DtrId);
#else
  lReturnValue = 1.0f;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Dtr_GetOffset
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(float32, DEM_CODE)
Dem_Dtr_GetOffset(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  float32 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = Dem_Cfg_GetOffsetOfDtrTable(DtrId);
#else
  lReturnValue = 0.0f;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Dtr_GetStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Dtr_GetStatus(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  uint8 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = Dem_Cfg_GetDtrStatus(DtrId);
#else
  lReturnValue = DEM_DTR_INVISIBLE;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Dtr_SetStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_SetStatus(
  CONST(DTRIdType, AUTOMATIC) DtrId,
  CONST(uint8, AUTOMATIC) Status
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Status)                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DtrId >= Dem_Cfg_GetSizeOfDtrStatus())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetDtrStatus(DtrId, Status);                                                                                         /* SBSW_DEM_ARRAY_WRITE_DTRSTATUS */
  }
#endif
}

/* ****************************************************************************
 % Dem_Dtr_SetTestValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_SetTestValue(
  CONST(DTRIdType, AUTOMATIC)  DtrId,
  CONST(uint16, AUTOMATIC)  Value
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DtrId >= DEM_CFG_MAX_NUMBER_CONFIGURABLE_DTRS)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetDtrData().TestValue[DtrId] = Value;                                                                               /* SBSW_DEM_ARRAY_WRITE_DTRDATA_TESTVALUE */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Value)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Dtr_SetLowerLimit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_SetLowerLimit(
  CONST(DTRIdType, AUTOMATIC)  DtrId,
  CONST(uint16, AUTOMATIC)  Value
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DtrId >= DEM_CFG_MAX_NUMBER_CONFIGURABLE_DTRS)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetDtrData().LowLimValue[DtrId] = Value;                                                                             /* SBSW_DEM_ARRAY_WRITE_DTRDATA_LOWLIMVALUE */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Value)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Dtr_SetUpperLimit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_SetUpperLimit(
  CONST(DTRIdType, AUTOMATIC)  DtrId,
  CONST(uint16, AUTOMATIC)  Value
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (DtrId >= DEM_CFG_MAX_NUMBER_CONFIGURABLE_DTRS)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetDtrData().UppLimValue[DtrId] = Value;                                                                             /* SBSW_DEM_ARRAY_WRITE_DTRDATA_UPPLIMVALUE */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Value)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Dtr_TestWriteOnShutdown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dtr_TestWriteOnShutdown(
  void
  )
{
  boolean lReturnValue;
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = Dem_Dtr_DataChanged;
#else
  lReturnValue = FALSE;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Dtr_SetWriteOnShutdown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_SetWriteOnShutdown(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_Dtr_DataChanged = TRUE;
  Dem_Scheduler_EnableTask(Dem_Scheduler_Task_Dtr);
#endif
}

/* ****************************************************************************
 % Dem_Dtr_ResetWriteOnShutdown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_ResetWriteOnShutdown(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_Dtr_DataChanged = FALSE;
#endif
}

/* ****************************************************************************
 % Dem_Dtr_IsTestResultInLimits
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
Dem_Dtr_IsTestResultInLimits(
  CONST(sint32, AUTOMATIC) TestResult,
  CONST(sint32, AUTOMATIC) LowerLimit,
  CONST(sint32, AUTOMATIC) UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC) Ctrlval
  )
{
  boolean lTestResultInLimits;

  lTestResultInLimits = TRUE;

  if (TestResult < LowerLimit)
  {
    if (Ctrlval != DEM_DTR_CTL_NO_MIN)
    {
      lTestResultInLimits = FALSE;
    }
  }
  else if (TestResult > UpperLimit)
  {
    if (Ctrlval != DEM_DTR_CTL_NO_MAX)
    {
      lTestResultInLimits = FALSE;
    }
  }
  else
  {
    /* Misra */
  }

  return lTestResultInLimits;
}

/* ****************************************************************************
 % Dem_Dtr_IsProcessable
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
Dem_Dtr_IsProcessable(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(sint32, AUTOMATIC) TestResult,
  CONST(sint32, AUTOMATIC) LowerLimit,
  CONST(sint32, AUTOMATIC) UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC) Ctrlval
  )
{
  boolean lDtrProcessed;

  lDtrProcessed = FALSE;

  if (Dem_Dtr_GetUpdateKind(DTRId) == DEM_DTR_UPDATE_ALWAYS)
  {
    lDtrProcessed = TRUE;
  }
  else
  {
    Dem_EventIdType lEventId;
    Dem_DebouncingStateType lDebouncingState;

    lEventId = Dem_Dtr_GetRelatedEvent(DTRId);
    lDebouncingState = Dem_SatelliteSat_GetDebouncingState(Dem_Cfg_EventSatelliteId(lEventId), 
                                                            Dem_Cfg_EventSatelliteEventId(lEventId));

    /* event is tested and storage and enable conditions are fulfilled */
    if (Dem_DebouncingState_TestDtrUpdate(lDebouncingState) == TRUE)
    {
      /* event is tested failed */
      if (Dem_DebouncingState_TestFinallyDefective(lDebouncingState) == TRUE)
      {
        lDtrProcessed = TRUE;
      }
      /* event is tested passed */
      else
      {
        /* Test result doesn't violate the limits */
        if (Dem_Dtr_IsTestResultInLimits(TestResult, LowerLimit, UpperLimit, Ctrlval) == TRUE)
        {
          lDtrProcessed = TRUE;
        }
      }
    }
  }

  return lDtrProcessed;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Dtr_ConvertValue
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
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Dtr_ConvertValue(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(sint32, AUTOMATIC) InitialValue,
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) ConvertedValue
  )
{
  Std_ReturnType lReturnValue;
  float32 lDivisor, lLinFactor, lOffset, lConvertedValue;

  lDivisor = Dem_Dtr_GetDivisor(DTRId);
  lLinFactor = Dem_Dtr_GetLinearFactor(DTRId);
  lOffset = Dem_Dtr_GetOffset(DTRId);

  lConvertedValue = ((lLinFactor * (float32) InitialValue) + lOffset) / lDivisor;
  if (lConvertedValue < 0)
  {
    *ConvertedValue = 0;                                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = DEM_DTR_CONVERSION_UNDERFLOW;
  }
  else if (lConvertedValue > 0xffffU)
  {
    *ConvertedValue = 0xffffU;                                                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = DEM_DTR_CONVERSION_OVERFLOW;
  }
  else
  {
    *ConvertedValue = Dem_Dtr_RoundFloatToInt(lConvertedValue);                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = DEM_DTR_OK;
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Dtr_ShiftThresholds
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
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Dtr_ShiftThresholds(
  CONST(uint16, AUTOMATIC) TestValue,
  CONST(uint8, AUTOMATIC) LimitViolation,
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) LowerLimit,
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) UpperLimit
  )
{
  Std_ReturnType lReturnValue;
  uint16 lLowerLimit;
  uint16 lUpperLimit;

  lReturnValue = E_OK;
  lLowerLimit = *LowerLimit;
  lUpperLimit = *UpperLimit;

  switch (LimitViolation)
  {
  case DEM_DTR_TEST_VALUE_WITHIN_LIMITS:
    /* test value violates lower limit */
    if (TestValue < lLowerLimit)
    {
      /* Test value violates lower limit by more than one. */
      if ( (lLowerLimit - TestValue) > 1 )
      {
        lReturnValue = E_NOT_OK;
      }
      else
      {
        /* from if: TestValue < lLowerLimit:
             => lLowerLimit > TestValue

           with max(TestValue) = 0
             => lLowerLimit > 0
             => Underflow may not occur.
           */
        lLowerLimit--;
      }
    }
    /* test value violates upper limit */
    else if (TestValue > lUpperLimit)
    {
      /* test value violates upper limit by more than one */
      if ( (TestValue - lUpperLimit) > 1 )
      {
        lReturnValue = E_NOT_OK;
      }
      else
      {
        /* from if(TestValue > lUpperLimit):
             => lUpperLimit < TestValue

           with max(TestValue) = 0xFFFF
             => lUpperLimit < 0xFFFF
             => Overflow may not occur.
           */
        lUpperLimit++;
      }
    }
    else
    {
      /* MISRA */
    }
    break;
  case DEM_DTR_TEST_VALUE_VIOLATES_LOWER_LIMIT:
    /* test value doesn't violate lower limit */
    if (TestValue >= lLowerLimit)
    {
      /* lower limit has to be shifted by more than one or lower limit is already 0xffff */
      if ( (TestValue > lLowerLimit) || (lLowerLimit == 0xffffU) )
      {
        lReturnValue = E_NOT_OK;
      }
      else
      {
        lLowerLimit++;
        if (lLowerLimit > lUpperLimit)
        {
          lUpperLimit++;
        }
      }
    }
    break;
  case DEM_DTR_TEST_VALUE_VIOLATES_UPPER_LIMIT:
    /* test value doesn't violate upper limit */
    if (TestValue <= lUpperLimit)
    {
      /* upper limit has to be shifted by more than one  or upper limit is already 0 */
      if ( (TestValue < lUpperLimit) || (lUpperLimit == 0) )
      {
        lReturnValue = E_NOT_OK;
      }
      else
      {
        lUpperLimit--;
        if (lLowerLimit > lUpperLimit)
        {
          (lLowerLimit)--;
        }
      }
    }
    break;
  default:
    /* Misra */
    lReturnValue = E_NOT_OK;
    break;
  }

  *LowerLimit = lLowerLimit;                                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  *UpperLimit = lUpperLimit;                                                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030 */ /* MD_MSR_STCYC */

/* ****************************************************************************
 % Dem_Dtr_ProcessDtrValues
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
Dem_Dtr_ProcessDtrValues(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(sint32, AUTOMATIC) TestResult,
  CONST(sint32, AUTOMATIC) LowerLimit,
  CONST(sint32, AUTOMATIC) UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC) Ctrlval
  )
{
  Std_ReturnType lConvResult_LowerLimit;
  Std_ReturnType lConvResult_UpperLimit;
  Std_ReturnType lConvResult_TestResult;
  uint16 lConvLowerLimit;
  uint16 lConvUpperLimit;
  uint16 lConvTestResult;

  Dem_Det_ErrorRegisterDefine()
  Dem_Det_ErrorRegisterSet(DEM_E_NO_ERROR)

  /* convert Dtr values */
  if (Ctrlval == DEM_DTR_CTL_NO_MIN)
  {
    lConvLowerLimit = 0;
    lConvResult_LowerLimit = DEM_DTR_OK;
  }
  else
  {
    lConvResult_LowerLimit = Dem_Dtr_ConvertValue(DTRId, LowerLimit, &lConvLowerLimit);                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
  }
  if (Ctrlval == DEM_DTR_CTL_NO_MAX)
  {
    lConvUpperLimit = 0xffff;
    lConvResult_UpperLimit = DEM_DTR_OK;
  }
  else
  {
    lConvResult_UpperLimit = Dem_Dtr_ConvertValue(DTRId, UpperLimit, &lConvUpperLimit);                                          /* SBSW_DEM_POINTER_FORWARD_STACK */
  }
  lConvResult_TestResult = Dem_Dtr_ConvertValue(DTRId, TestResult, &lConvTestResult);                                            /* SBSW_DEM_POINTER_FORWARD_STACK */

  if ((lConvResult_LowerLimit == DEM_DTR_CONVERSION_UNDERFLOW) 
    || (lConvResult_LowerLimit == DEM_DTR_CONVERSION_OVERFLOW))
  {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG)
#endif
    Dem_Dtr_SetDtrValues(DTRId, 0, 0, 0);
  }
  else
  if ((lConvResult_UpperLimit == DEM_DTR_CONVERSION_UNDERFLOW) 
    || (lConvResult_UpperLimit == DEM_DTR_CONVERSION_OVERFLOW))
  {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
    Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG)
#endif
    Dem_Dtr_SetDtrValues(DTRId, 0, 0, 0);
  }
  else
  {
    Std_ReturnType lShiftResult;
    lShiftResult = E_OK;

    /* shift thresholds if necessary to reach previous meaning */
    switch (lConvResult_TestResult)
    {
    case DEM_DTR_CONVERSION_UNDERFLOW:
      if (Ctrlval != DEM_DTR_CTL_NO_MIN)
      {
        lShiftResult = Dem_Dtr_ShiftThresholds(lConvTestResult,                                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */
                                               DEM_DTR_TEST_VALUE_VIOLATES_LOWER_LIMIT, 
                                               &lConvLowerLimit,
                                               &lConvUpperLimit);
      }
      break;
    case DEM_DTR_CONVERSION_OVERFLOW:
      if (Ctrlval != DEM_DTR_CTL_NO_MAX)
      {
        lShiftResult = Dem_Dtr_ShiftThresholds(lConvTestResult,                                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */
                                               DEM_DTR_TEST_VALUE_VIOLATES_UPPER_LIMIT, 
                                               &lConvLowerLimit, 
                                               &lConvUpperLimit);
      }
      break;
    case DEM_DTR_OK:
      if ((TestResult < LowerLimit) && (Ctrlval != DEM_DTR_CTL_NO_MIN))
      {
        lShiftResult = Dem_Dtr_ShiftThresholds(lConvTestResult,                                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */
                                               DEM_DTR_TEST_VALUE_VIOLATES_LOWER_LIMIT, 
                                               &lConvLowerLimit, 
                                               &lConvUpperLimit);
      }
      else if ((TestResult > UpperLimit) && (Ctrlval != DEM_DTR_CTL_NO_MAX))
      {
        lShiftResult = Dem_Dtr_ShiftThresholds(lConvTestResult,                                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */
                                               DEM_DTR_TEST_VALUE_VIOLATES_UPPER_LIMIT, 
                                               &lConvLowerLimit, 
                                               &lConvUpperLimit);
      }
      else
      {
        lShiftResult = Dem_Dtr_ShiftThresholds(lConvTestResult,                                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */
                                               DEM_DTR_TEST_VALUE_WITHIN_LIMITS, 
                                               &lConvLowerLimit, 
                                               &lConvUpperLimit);
      }
      break;
    default:
      /* Misra */
      break;
    }

    /* shift was successful */
    if (lShiftResult == E_OK)
    {
      Dem_Dtr_SetDtrValues(DTRId, lConvTestResult, lConvLowerLimit, lConvUpperLimit);
    }
    /* thresholds would have to be shifted by more than one or go below 0 or exceed 0xffff --> reset Dtr values */
    else
    {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
      Dem_Det_ErrorRegisterSet(DEM_E_PARAM_CONFIG)
#endif
      Dem_Dtr_SetDtrValues(DTRId, 0, 0, 0);
    }
  }
  /* ----- Development Error Report ---------------------------------------- */
#if (DEM_DEV_ERROR_REPORT == STD_ON)
  if (Dem_Det_ErrorRegisterGet() != DEM_E_NO_ERROR)
  {
    Dem_Error_ReportError(DEM_SETDTR_APIID, Dem_Det_ErrorRegisterGet());
  }
#endif
}                                                                                                                                /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_Dtr_IsEventAvailable
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
Dem_Dtr_IsEventAvailable(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  boolean lEventAvailable;
  Dem_EventIdType lEventId;

  lEventAvailable = TRUE;
  lEventId = Dem_Dtr_GetRelatedEvent(DtrId);
  if (lEventId != DEM_EVENT_INVALID)
  {
    if ( (Dem_Cfg_EventAvailableByVariant(lEventId) == FALSE)                                                                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      || (Dem_EventInternalStatus_TestEventDisconnected(Dem_Event_GetInternalStatus(lEventId)) == TRUE) )
    {
      lEventAvailable = FALSE;
    }
  }
  return lEventAvailable;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return FALSE;
#endif
}

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_Dtr_IsDTCSuppressed
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
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Dtr_IsDTCSuppressed(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  boolean lDTCSuppressed;
  Dem_EventIdType lEventId;

  lDTCSuppressed = FALSE;
  lEventId = Dem_Dtr_GetRelatedEvent(DtrId);
  if (lEventId != DEM_EVENT_INVALID)
  {
    if (Dem_DTC_TestDtcSuppression(lEventId) == TRUE)
    {
      lDTCSuppressed = TRUE;
    }
  }
  return lDTCSuppressed;
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
 * \addtogroup Dem_Dtr_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Dtr_SetDtrValues
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_SetDtrValues(
  CONST(DTRIdType, AUTOMATIC) DTRId,
  CONST(uint16, AUTOMATIC) TestValue,
  CONST(uint16, AUTOMATIC) LowerLimit,
  CONST(uint16, AUTOMATIC) UpperLimit
  )
{
/* >>>> -------------------------------- Enter Critical Section: DiagMonitor */
  Dem_EnterCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */

  Dem_Dtr_SetTestValue(DTRId, TestValue);
  Dem_Dtr_SetLowerLimit(DTRId, LowerLimit);
  Dem_Dtr_SetUpperLimit(DTRId, UpperLimit);

  Dem_LeaveCritical_DiagMonitor();                                                                                               /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: DiagMonitor */

  Dem_Dtr_SetWriteOnShutdown();
}

/* ****************************************************************************
 % Dem_Dtr_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_Init(
  void
  )
{
  Dem_Dtr_ResetWriteOnShutdown();
}

/* ****************************************************************************
 % Dem_Dtr_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_PreInit(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_MemSet((Dem_DataPtrType)(&Dem_Cfg_GetDtrStatus(0)),                                                                        /* PRQA S 0310, 0312, 0602, 3109 */ /* MD_DEM_11.4_cpy, MD_DEM_11.5, MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_MEMSET_DTRSTATUS */
             DEM_DTR_VISIBLE,
             Dem_Cfg_GetSizeOfDtrStatus() * sizeof(Dem_Cfg_GetDtrStatus(0)));
#endif
}

/* ****************************************************************************
 % Dem_Dtr_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_MainFunction(
  void
  )
{
  Dem_Dtr_ResetWriteOnShutdown();
  Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_DTR), 
                              DEM_NVM_BLOCKSTATE_DIRTY);
}

/* ****************************************************************************
 % Dem_Dtr_Shutdown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_Shutdown(
  void
  )
{
  if (Dem_Dtr_TestWriteOnShutdown() != 0)
  {
    Dem_Dtr_ResetWriteOnShutdown();
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_DTR), 
                                DEM_NVM_BLOCKSTATE_DIRTY);
  }
}

/* ****************************************************************************
 % Dem_Dtr_IsValidHandle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dtr_IsValidHandle(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  boolean lDtrValid;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
    
  lDtrValid = FALSE;
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  if (DtrId < Dem_Dtr_GetGlobalDtrCount())
  {
    if (Dem_Dtr_GetDivisor(DtrId) != 0.0f)                                                                                       /* PRQA S 3341 */ /* MD_DEM_13.3 */
    {
      lDtrValid = TRUE;
    }
  }
#endif
  return lDtrValid;
}

/* ****************************************************************************
 % Dem_Dtr_EventAvailabilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_EventAvailabilityChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_Cfg_EventDtrIterType lDtrIter;
  Dem_Dtr_EventDtrIterInit(EventId, &lDtrIter);                                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
  if (Dem_Dtr_EventDtrIterExists(&lDtrIter) == TRUE)                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_MidLookup_NotifyVisibilityChanged();
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_Dtr_DTCSuppressionChanged
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
Dem_Dtr_DTCSuppressionChanged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_CFG_SUPPORT_DTR == STD_ON)
#  if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(EventId);

  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    Dem_Cfg_CombinedGroupIterType lCombinedIter;

    for (Dem_Cfg_CombinedGroupIterInit(lGroupId, &lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterExists(&lCombinedIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_CombinedGroupIterNext(&lCombinedIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_EventIdType lSubEventId;
      Dem_Cfg_EventDtrIterType lDtrIter;
      lSubEventId = Dem_Cfg_CombinedGroupIterGet(&lCombinedIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_Dtr_EventDtrIterInit(lSubEventId, &lDtrIter);                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
      if (Dem_Dtr_EventDtrIterExists(&lDtrIter) == TRUE)                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        Dem_MidLookup_NotifyVisibilityChanged();
        /* if one event has been found, flag is already set */
        break;
      }
    }
  }
  else
#  endif
  {
    Dem_Cfg_EventDtrIterType lDtrIter;
    Dem_Dtr_EventDtrIterInit(EventId, &lDtrIter);                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if (Dem_Dtr_EventDtrIterExists(&lDtrIter) == TRUE)                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      Dem_MidLookup_NotifyVisibilityChanged();
    }
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# endif
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_Dtr_ResetDtrsOfEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_ResetDtrsOfEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_Cfg_EventDtrIterType lDtrIter;
  for (Dem_Dtr_EventDtrIterInit(EventId, &lDtrIter);                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Dtr_EventDtrIterExists(&lDtrIter) == TRUE;                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Dtr_EventDtrIterNext(&lDtrIter))                                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    DTRIdType lDtrId;
    lDtrId = Dem_Dtr_EventDtrIterGet(&lDtrIter);                                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Dtr_SetDtrValues(lDtrId, 0, 0, 0);
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Dtr_ResetDtrsWithoutEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Dtr_ResetDtrsWithoutEvent(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  DTRIdType lDtrId;
  /* reset Dtr values of Dtrs not referencing an event */
  for (lDtrId = 0; lDtrId < Dem_Dtr_GetGlobalDtrCount(); lDtrId++)
  {
    if (Dem_Dtr_GetRelatedEvent(lDtrId) == DEM_EVENT_INVALID)
    {
      Dem_Dtr_SetDtrValues(lDtrId, 0, 0, 0);
    }
  }
#endif
}

/* ****************************************************************************
 % Dem_Dtr_SetDtr
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Dtr_SetDtr(
  CONST(DTRIdType, AUTOMATIC) DTRId,                                                                                             /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
  CONST(sint32, AUTOMATIC) TestResult,
  CONST(sint32, AUTOMATIC) LowerLimit,
  CONST(sint32, AUTOMATIC) UpperLimit,
  CONST(Dem_DTRControlType, AUTOMATIC) Ctrlval
  )
{
  Std_ReturnType lReturnValue;

  lReturnValue = E_NOT_OK;

  if ( (Dem_Dtr_IsValidHandle(DTRId) == TRUE)                                                                                    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (Dem_Dtr_IsEventAvailable(DTRId) == TRUE) )
  {
    switch (Ctrlval)
    {
    case DEM_DTR_CTL_INVISIBLE:
      /* Set state of Dtr to invisible. Dtr result and limits are ignored */
      if (Dem_Dtr_GetStatus(DTRId) == DEM_DTR_VISIBLE)
      {
        Dem_Dtr_SetStatus(DTRId, DEM_DTR_INVISIBLE);
        Dem_MidLookup_NotifyVisibilityChanged();
      }
      break;
    case DEM_DTR_CTL_RESET:
      /* Set state of Dtr to visible. Reset Dtr values */
      if (Dem_Dtr_GetStatus(DTRId) == DEM_DTR_INVISIBLE)
      {
        Dem_Dtr_SetStatus(DTRId, DEM_DTR_VISIBLE);
        Dem_MidLookup_NotifyVisibilityChanged();
      }
      /* reset Dtr values */
      Dem_Dtr_SetDtrValues(DTRId, 0, 0, 0);
      break;
    case DEM_DTR_CTL_NORMAL:
    case DEM_DTR_CTL_NO_MAX:
    case DEM_DTR_CTL_NO_MIN:
      /* Set state of Dtr to visible. Process Dtr values if Dtr result is valid */
      if (Dem_Dtr_GetStatus(DTRId) == DEM_DTR_INVISIBLE)
      {
        Dem_Dtr_SetStatus(DTRId, DEM_DTR_VISIBLE);
        Dem_MidLookup_NotifyVisibilityChanged();
      }
      /* Dtr result is valid --> process Dtr values */
      if (Dem_Dtr_IsProcessable(DTRId, TestResult, LowerLimit, UpperLimit, Ctrlval) == TRUE)
      {
        Dem_Dtr_ProcessDtrValues(DTRId, TestResult, LowerLimit, UpperLimit, Ctrlval);
      }
      break;
    default:
      break;
    }
    lReturnValue = E_OK;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_Dtr_TestDtrVisibility
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Dtr_TestDtrVisibility(
  CONST(DTRIdType, AUTOMATIC) DTRId
  )
{
  return (boolean)( (Dem_Dtr_GetStatus(DTRId) == DEM_DTR_VISIBLE)                                                                /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
                 && (Dem_Dtr_IsEventAvailable(DTRId) == TRUE)
                 && (Dem_Dtr_IsDTCSuppressed(DTRId) == FALSE) );
}
#endif

/* ****************************************************************************
 % Dem_Dtr_GetUaSId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Dtr_GetUaSId(
  CONST(DTRIdType, AUTOMATIC) DtrId
  )
{
  uint8 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  lReturnValue = Dem_Cfg_GetUasidOfDtrTable(DtrId);
#else
  lReturnValue = 0;
#endif
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Dtr_GetTestValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Dtr_GetTestValue(
  CONST(DTRIdType, AUTOMATIC)  DtrId
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_OFF)
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#else
  return Dem_Cfg_GetDtrData().TestValue[DtrId];
#endif
}

/* ****************************************************************************
 % Dem_Dtr_GetLowerLimit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Dtr_GetLowerLimit(
  CONST(DTRIdType, AUTOMATIC)  DtrId
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_OFF)
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#else
  return Dem_Cfg_GetDtrData().LowLimValue[DtrId];
#endif
}

/* ****************************************************************************
 % Dem_Dtr_GetUpperLimit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Dtr_GetUpperLimit(
  CONST(DTRIdType, AUTOMATIC)  DtrId
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_OFF)
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DtrId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#else
  return Dem_Cfg_GetDtrData().UppLimValue[DtrId];
#endif
}

/*!
 * \}
 */

#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_DTR_IMPLEMENTATION_H */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Dtr_Implementation.h
 *********************************************************************************************************************/
