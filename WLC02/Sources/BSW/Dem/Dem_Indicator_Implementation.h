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
/*! \addtogroup Dem_Indicator
 *  \{
 *  \file       Dem_Indicator_Implementation.h
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

#if !defined (DEM_INDICATOR_IMPLEMENTATION_H)
#define DEM_INDICATOR_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Indicator_Interface.h"
                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_UDSStatus_Implementation.h"
                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Event_Interface.h"
#include "Dem_DTC_Interface.h"
#include "Dem_Error_Interface.h"
#include "Dem_Esm_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*!
 * \defgroup  Dem_J1939_LampStates Macros encoding J1939 lamp states
 * \{
 */
#define DEM_J1939_LAMP_NA              (0x03U)  /*!< Indicator not configured */
#define DEM_J1939_LAMP_OFF             (0x00U)  /*!< Indicator off */
#define DEM_J1939_LAMP_ON              (0x01U)  /*!< Indicator on */

#define DEM_J1939_LAMP_MIL_NA          (DEM_J1939_LAMP_NA << 6)  /*!< Bitmask for MIL indicator */
#define DEM_J1939_LAMP_RSL_NA          (DEM_J1939_LAMP_NA << 4)  /*!< Bitmask for RSL indicator */
#define DEM_J1939_LAMP_AWL_NA          (DEM_J1939_LAMP_NA << 2)  /*!< Bitmask for AWL indicator */
#define DEM_J1939_LAMP_PL_NA           (DEM_J1939_LAMP_NA)       /*!< Bitmask for PL indicator */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_J1939_FlashLampStates Macros encoding J1939 flash lamp states
 * \{
 */
#define DEM_J1939_FLASHLAMP_FAST_FLASH      (0x01U)  /*!< Indicator fast flashing */
#define DEM_J1939_FLASHLAMP_SLOW_FLASH      (0x00U)  /*!< Indicator slow flashing */
#define DEM_J1939_FLASHLAMP_NO_FLASH        (0x03U)  /*!< Indicator not flashing (either not configured, off or continuous) */

#define DEM_J1939_FLASHLAMP_MIL_NO_FLASH    (DEM_J1939_FLASHLAMP_NO_FLASH << 6)  /*!< Bitmask for MIL flashing */
#define DEM_J1939_FLASHLAMP_RSL_NO_FLASH    (DEM_J1939_FLASHLAMP_NO_FLASH << 4)  /*!< Bitmask for RSL flashing */
#define DEM_J1939_FLASHLAMP_AWL_NO_FLASH    (DEM_J1939_FLASHLAMP_NO_FLASH << 2)  /*!< Bitmask for AWL flashing */
#define DEM_J1939_FLASHLAMP_PL_NO_FLASH     (DEM_J1939_FLASHLAMP_NO_FLASH)       /*!< Bitmask for PL flashing */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/*! Number of qualified active and failed events per WWHO-OBD class. Index 0 (no class) is unused. */
DEM_LOCAL VAR(Dem_EventIdType, DEM_VAR_NOINIT)   Dem_Esm_QualifiedActiveEventCount[DEM_ESM_WWHOBD_NUMBER_DTCCLASS];
/*! Number of MIL requests per WWHO-OBD class. Index 0 (no class) is unused. */
DEM_LOCAL VAR(Dem_EventIdType, DEM_VAR_NOINIT)   Dem_Esm_DtcClassMILCount[DEM_ESM_WWHOBD_NUMBER_DTCCLASS];
#endif

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_Indicator_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_Indicator_TestHasIndicator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Indicator_TestHasIndicator(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
)
{
  boolean lReturnValue;
  lReturnValue = TRUE;
  {
#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
    Dem_Cfg_EventIndicatorIterType lIndicatorIter;
    Dem_Cfg_EventIndicatorIterInit(EventId, &lIndicatorIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
    if (Dem_Cfg_EventIndicatorIterExists(&lIndicatorIter) == FALSE)                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
#endif
    {
#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
      if (Dem_Cfg_EventSpecialIndicator(EventId) == DEM_CFG_SPECIAL_INDICATOR_NONE)
#endif
      {
        lReturnValue = FALSE;
      }
    }
  }
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_GetQualifiedActiveEventCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Indicator_GetQualifiedActiveEventCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass
  )
{
  return Dem_Esm_QualifiedActiveEventCount[WwhObdDtcClass];
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_SetQualifiedActiveEventCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetQualifiedActiveEventCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass,
  CONST(Dem_EventIdType, AUTOMATIC)  QualifiedActiveEventCount
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (WwhObdDtcClass >= DEM_ESM_WWHOBD_NUMBER_DTCCLASS)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Esm_QualifiedActiveEventCount[WwhObdDtcClass] = QualifiedActiveEventCount;                                               /* SBSW_DEM_ARRAY_WRITE_QUALIFIEDACTIVEEVENTCOUNT */
  }
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_GetDtcClassMILCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Indicator_GetDtcClassMILCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass
  )
{
  return Dem_Esm_DtcClassMILCount[WwhObdDtcClass];
}
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_SetDtcClassMILCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetDtcClassMILCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass,
  CONST(Dem_EventIdType, AUTOMATIC)  DtcClassMILCount
  )
{

# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (WwhObdDtcClass >= DEM_ESM_WWHOBD_NUMBER_DTCCLASS)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Esm_DtcClassMILCount[WwhObdDtcClass] = DtcClassMILCount;                                                                 /* SBSW_DEM_ARRAY_WRITE_DTCCLASSMILCOUNT */
  }
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
 * \addtogroup Dem_Indicator_Private
 * \{
 */


/* ****************************************************************************
 % Dem_Indicator_SetGlobalIndicatorState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetGlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint8, AUTOMATIC)  IndicatorState
  )
{
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (IndicatorId >= Dem_Cfg_GetSizeOfGlobalIndicatorStates())                                                                 /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (NmNodeIndex >= Dem_Cfg_GlobalJ1939NodeCount()))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GlobalIndicatorStates[IndicatorId][NmNodeIndex] = IndicatorState;                                                    /* SBSW_DEM_ARRAY_WRITE_GLOBALINDICATORSTATES */
  }
#else
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                /* PRQA S 3112 */ /* MD_DEM_14.2 */
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorState)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Indicator_GetGlobalIndicatorState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_GetGlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  )
{
  uint8 lReturnValue;
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
  lReturnValue = Dem_Cfg_GlobalIndicatorStates[IndicatorId][NmNodeIndex];
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = DEM_INDICATOR_OFF;
#endif
  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_J1939PriorityOfIndicatorState
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939PriorityOfIndicatorState(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  )
{
  uint8 lReturnValue;
  switch(ConfigIndicatorState)
  {
  case DEM_INDICATOR_OFF:
    lReturnValue = 0x00U;
    break;
  case DEM_INDICATOR_SLOW_FLASH:
    lReturnValue = 0x01U;
    break;
  case DEM_INDICATOR_FAST_FLASH:
    lReturnValue = 0x02U;
    break;
  case DEM_INDICATOR_CONTINUOUS:
    lReturnValue = 0x03U;
    break;

  default:
    Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
    lReturnValue = 0x00U;
    break;
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_J1939IndicatorStateFromPriority
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939IndicatorStateFromPriority(
  CONST(uint8, AUTOMATIC)  Priority
  )
{
  uint8 lReturnValue;
  switch(Priority)
  {
  case 0x00U:
    lReturnValue = DEM_INDICATOR_OFF;
    break;
  case 0x01U:
    lReturnValue = DEM_INDICATOR_SLOW_FLASH;
    break;
  case 0x02U:
    lReturnValue = DEM_INDICATOR_FAST_FLASH;
    break;
  case 0x03U:
    lReturnValue = DEM_INDICATOR_CONTINUOUS;
    break;

  default:
    Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
    lReturnValue = DEM_INDICATOR_OFF;
    break;
  }
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_J1939GlobalIndicatorState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939GlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId
  )
{
  uint8 lGlobalIndicatorState;
  uint8 lNmNodeIndex;

  lGlobalIndicatorState = 0;
  lNmNodeIndex = Dem_Cfg_GlobalJ1939NodeCount();

  if ( (Dem_Cfg_GlobalMilIndicator() == IndicatorId)                                                                             /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_Cfg_GlobalRslIndicator() == IndicatorId)
    || (Dem_Cfg_GlobalAwlIndicator() == IndicatorId)
    || (Dem_Cfg_GlobalPlIndicator() == IndicatorId))
  {
    /*Requested indicator is J1939 special indicator, search across all nodes for state with highest priority*/
    uint8 lSpecialIndicatorPriority;
    lSpecialIndicatorPriority = 0;
    while (lNmNodeIndex != 0)
    {
      uint8 lTempPriority;

      --lNmNodeIndex;
      lTempPriority = Dem_Indicator_J1939PriorityOfIndicatorState(Dem_Indicator_GetGlobalIndicatorState(IndicatorId, lNmNodeIndex));

      if (lSpecialIndicatorPriority < lTempPriority)
      {
        lSpecialIndicatorPriority = lTempPriority;
      }
    }

    lGlobalIndicatorState = Dem_Indicator_J1939IndicatorStateFromPriority(lSpecialIndicatorPriority);
  }
  else
  {
    /*Requested indicator is user indicator*/
    while (lNmNodeIndex != 0)
    {
      --lNmNodeIndex;
      lGlobalIndicatorState = (uint8)(Dem_Indicator_GetGlobalIndicatorState(IndicatorId, lNmNodeIndex) | lGlobalIndicatorState);
    }
  }
  return lGlobalIndicatorState;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif /* (DEM_CFG_SUPPORT_J1939 == STD_ON)*/

#if (DEM_CFG_SUPPORT_PID21 == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_GlobalMilStateDisable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_GlobalMilStateDisable(
  void
  )
{
  /* If the Indicator state changes from on to off, the current Odometer value is set to invalid */
/* >>>> -------------------------------- Enter Critical Section: NonAtomic32bit */
  Dem_EnterCritical_NonAtomic32bit();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */

  Dem_Mem_SetOdometerMilOn(DEM_MEM_SET_ODOMETER_INVALID(Dem_Mem_GetOdometerMilOn()));

  Dem_LeaveCritical_NonAtomic32bit();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: NonAtomic32bit */
}
#endif /* (DEM_CFG_SUPPORT_PID21 == STD_ON) */

/* ****************************************************************************
 % Dem_Indicator_GetEventCountContinuous
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountContinuous(
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
  return Dem_Cfg_IndicatorContinuous[IndicatorId][NmNodeIndex];
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#endif
}

/* ****************************************************************************
 % Dem_Indicator_SetEventCountContinuous
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountContinuous(
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint16, AUTOMATIC)  ActiveEventCount                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (IndicatorId >= Dem_Cfg_GlobalIndicatorCount())                                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (NmNodeIndex >= Dem_Cfg_GlobalJ1939NodeCount()))
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_IndicatorContinuous[IndicatorId][NmNodeIndex] = ActiveEventCount;                                                    /* SBSW_DEM_ARRAY_WRITE_INDICATORCONTINUOUS */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ActiveEventCount)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Indicator_GetEventCountBlinking
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountBlinking(
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
  return Dem_Cfg_IndicatorBlinking[IndicatorId][NmNodeIndex];
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#endif
}

/* ****************************************************************************
 % Dem_Indicator_SetEventCountBlinking
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountBlinking(
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint16, AUTOMATIC)  ActiveEventCount                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_SUPPORT_INDICATORS == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (IndicatorId >= Dem_Cfg_GlobalIndicatorCount())                                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (NmNodeIndex >= Dem_Cfg_GlobalJ1939NodeCount()) )
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_IndicatorBlinking[IndicatorId][NmNodeIndex] = ActiveEventCount;                                                      /* SBSW_DEM_ARRAY_WRITE_INDICATORBLINKING */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ActiveEventCount)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Indicator_GetEventCountFastFlash
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountFastFlash(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_INDICATORFASTFLASH == STD_ON)
  return Dem_Cfg_IndicatorFastFlash[IndicatorId][NmNodeIndex];
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#endif
}

/* ****************************************************************************
 % Dem_Indicator_SetEventCountFastFlash
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
Dem_Indicator_SetEventCountFastFlash(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint16, AUTOMATIC)  ActiveEventCount                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_INDICATORFASTFLASH == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (IndicatorId >= Dem_Cfg_GlobalIndicatorCount())                                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (NmNodeIndex >= Dem_Cfg_GlobalJ1939NodeCount()) )
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_IndicatorFastFlash[IndicatorId][NmNodeIndex] = ActiveEventCount;                                                     /* SBSW_DEM_ARRAY_WRITE_INDICATORFASTFLASH */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ActiveEventCount)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Indicator_GetEventCountSlowFlash
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountSlowFlash(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex                                                                                           /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_INDICATORSLOWFLASH == STD_ON)
  return Dem_Cfg_IndicatorSlowFlash[IndicatorId][NmNodeIndex];
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return 0;
#endif
}

/* ****************************************************************************
 % Dem_Indicator_SetEventCountSlowFlash
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
Dem_Indicator_SetEventCountSlowFlash(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  IndicatorId,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC)  NmNodeIndex,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint16, AUTOMATIC)  ActiveEventCount                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
#if (DEM_CFG_INDICATORSLOWFLASH == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (IndicatorId >= Dem_Cfg_GlobalIndicatorCount())                                                                           /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (NmNodeIndex >= Dem_Cfg_GlobalJ1939NodeCount()) )
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_IndicatorSlowFlash[IndicatorId][NmNodeIndex] = ActiveEventCount;                                                     /* SBSW_DEM_ARRAY_WRITE_INDICATORSLOWFLASH */
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(NmNodeIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ActiveEventCount)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

#if (((DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)) \
    && (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON))
/* ****************************************************************************
 % Dem_Indicator_J1939LampStatus
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
Dem_Indicator_J1939LampStatus(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  )
{
  uint8 lReturnValue;
  switch(ConfigIndicatorState)
  {
  case DEM_INDICATOR_OFF:
    lReturnValue = DEM_J1939_LAMP_OFF;
    break;
  case DEM_INDICATOR_FAST_FLASH:
  case DEM_INDICATOR_SLOW_FLASH:
  case DEM_INDICATOR_CONTINUOUS:
    lReturnValue = DEM_J1939_LAMP_ON;
    break;
  default:
    Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
    lReturnValue = DEM_J1939_LAMP_OFF;
    break;
  }
  return lReturnValue;
}
#endif

#if (((DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)) \
    && (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON))
/* ****************************************************************************
 % Dem_Indicator_J1939FlashLampStatus
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
Dem_Indicator_J1939FlashLampStatus(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  )
{
  uint8 lReturnValue;
  switch(ConfigIndicatorState)
  {
  case DEM_INDICATOR_OFF:
    lReturnValue = DEM_J1939_FLASHLAMP_NO_FLASH;
    break;
  case DEM_INDICATOR_FAST_FLASH:
    lReturnValue = DEM_J1939_FLASHLAMP_FAST_FLASH;
    break;
  case DEM_INDICATOR_SLOW_FLASH:
    lReturnValue = DEM_J1939_FLASHLAMP_SLOW_FLASH;
    break;
  case DEM_INDICATOR_CONTINUOUS:
    lReturnValue = DEM_J1939_FLASHLAMP_NO_FLASH;
    break;
  default:
    Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
    lReturnValue = DEM_J1939_FLASHLAMP_NO_FLASH;
    break;
  }
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Indicator_UpdateGlobalUserIndicatorStates
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
Dem_Indicator_UpdateGlobalUserIndicatorStates(
  CONST(uint8, AUTOMATIC)  IndicatorId
  )
{
  uint8 lNmNodeIndex;
  
  for (lNmNodeIndex = 0; lNmNodeIndex < Dem_Cfg_GlobalJ1939NodeCount(); ++lNmNodeIndex)
  {
    Dem_IndicatorStatusType lIndicatorState;
    lIndicatorState = DEM_INDICATOR_OFF;

    if (Dem_Indicator_GetEventCountContinuous(IndicatorId, lNmNodeIndex) > 0)
    {
      lIndicatorState = DEM_INDICATOR_CONTINUOUS;
    }

    if (Dem_Indicator_GetEventCountBlinking(IndicatorId, lNmNodeIndex) > 0)
    {
      lIndicatorState |= DEM_INDICATOR_BLINKING;
    }
    Dem_Indicator_SetGlobalIndicatorState(IndicatorId, lNmNodeIndex, lIndicatorState);
  }
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
 * \addtogroup Dem_Indicator_Public
 * \{
 */

#if (DEM_FEATURE_NEED_REPORTED_MIL_STATE == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_TestMilReportedActive
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Indicator_TestMilReportedActive(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  boolean lReturnValue;
  uint8 lMilState;

  lReturnValue = FALSE;
  lMilState =  Dem_Indicator_GetGlobalIndicatorState(Dem_Cfg_GlobalMilIndicator(), 0);

  if ( ( (lMilState & DEM_INDICATOR_CONTINUOUS) != 0)
# if (DEM_CFG_REPORT_BLINKING_MIL_AS_ACTIVE == STD_ON)
      || (lMilState == DEM_INDICATOR_BLINKING)
# endif
    )
  {
    lReturnValue = TRUE;
  }

  return lReturnValue;
}
#endif

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_UpdatePIDsMilEnabled
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
Dem_Indicator_UpdatePIDsMilEnabled(
  void
  )
{
  /* The MIL Indicator state has changed from FALSE to TRUE, the current Odometer value shall be fetched */
# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
/* >>>> -------------------------------- Enter Critical Section: NonAtomic32bit */
  Dem_EnterCritical_NonAtomic32bit();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */

  Dem_Mem_SetOdometerMilOn(DEM_MEM_SET_ODOMETER_INVALID(0));
  Dem_LeaveCritical_NonAtomic32bit();                                                                                            /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: NonAtomic32bit */
# endif
# if (DEM_CFG_SUPPORT_PID4D == STD_ON)
  Dem_Mem_SetEngineTimeMilOn(0);
# endif
}
#endif /* (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON) */

/* ****************************************************************************
 % Dem_Indicator_UserIndicatorEnable
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UserIndicatorEnable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
  Dem_Cfg_EventIndicatorIterType lIndicatorIter;

  for (Dem_Cfg_EventIndicatorIterInit(EventId, &lIndicatorIter);                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventIndicatorIterExists(&lIndicatorIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventIndicatorIterNext(&lIndicatorIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_IndicatorIndexType lIndicatorIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    Dem_Cfg_EventJ1939NodeIterType lNodeIter;
# endif
    lIndicatorIndex = Dem_Cfg_EventIndicatorIterGet(&lIndicatorIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */

# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
# endif
    {
      /* Increment the (node specific) indicator counter for continuous or blinking, according to configuration */
      uint8 lNmNodeIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      lNmNodeIndex = Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
# else
      lNmNodeIndex = 0;
# endif
      if ((DEM_INDICATOR_CONTINUOUS & Dem_Cfg_IndicatorStatus(lIndicatorIndex)) != 0)
      {
        Dem_Indicator_SetEventCountContinuous(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex) + 1));
      }
      if ((DEM_INDICATOR_BLINKING & Dem_Cfg_IndicatorStatus(lIndicatorIndex)) != 0)
      {
        Dem_Indicator_SetEventCountBlinking(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex) + 1));
      }
    }
  }
#endif /* (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON) */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_SpecialIndicatorEnable
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_SpecialIndicatorEnable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  uint8 lSpecialIndicator;
  /* EventId might not be used depending on configuration optimization */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lSpecialIndicator = Dem_Cfg_EventSpecialIndicator(EventId);
#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
  if (lSpecialIndicator != DEM_CFG_SPECIAL_INDICATOR_NONE)
  {
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    Dem_Cfg_EventJ1939NodeIterType lNodeIter;

    for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
# endif
    {
      uint8 lNmNodeIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      lNmNodeIndex = Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
# else
      lNmNodeIndex = 0;
# endif
      switch (Dem_Cfg_EventSpecialIndicatorState(EventId))
      {
      case DEM_INDICATOR_CONTINUOUS:
        Dem_Indicator_SetEventCountContinuous(Dem_Cfg_EventSpecialIndicator(EventId), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(Dem_Cfg_EventSpecialIndicator(EventId), lNmNodeIndex) + 1));
        break;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      case DEM_INDICATOR_FAST_FLASH:
        Dem_Indicator_SetEventCountFastFlash(Dem_Cfg_EventSpecialIndicator(EventId), lNmNodeIndex, 
          (uint16)(Dem_Indicator_GetEventCountFastFlash(Dem_Cfg_EventSpecialIndicator(EventId), lNmNodeIndex) + 1));
        break;
      case DEM_INDICATOR_SLOW_FLASH:
        Dem_Indicator_SetEventCountSlowFlash(Dem_Cfg_EventSpecialIndicator(EventId), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountSlowFlash(Dem_Cfg_EventSpecialIndicator(EventId),lNmNodeIndex) + 1));
        break;
# endif /* (DEM_CFG_SUPPORT_J1939 == STD_ON) */
# if (DEM_CFG_SUPPORT_J1939 != STD_ON)
      case DEM_INDICATOR_BLINKING:
        Dem_Indicator_SetEventCountBlinking(Dem_Cfg_EventSpecialIndicator(EventId), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(Dem_Cfg_EventSpecialIndicator(EventId), lNmNodeIndex) + 1));
        break;
      case DEM_INDICATOR_BLINK_CONT:
        Dem_Indicator_SetEventCountContinuous(Dem_Cfg_EventSpecialIndicator(EventId), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(Dem_Cfg_EventSpecialIndicator(EventId), lNmNodeIndex) + 1));
        Dem_Indicator_SetEventCountBlinking(Dem_Cfg_EventSpecialIndicator(EventId), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(Dem_Cfg_EventSpecialIndicator(EventId), lNmNodeIndex) + 1));
        break;
# endif
      default:
        Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
        break;
      }
    }
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    if (lSpecialIndicator == Dem_Cfg_GlobalMilIndicator())
    {
      uint8 lWwhObdDtcClass;
      lWwhObdDtcClass = Dem_Util_SeverityWwhObdDtcClass(Dem_Cfg_EventSeverity(EventId));
      Dem_Indicator_SetDtcClassMILCount(lWwhObdDtcClass, Dem_Indicator_GetDtcClassMILCount(lWwhObdDtcClass) + 1);
    }
# endif
  }
#endif
  return lSpecialIndicator;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_UserIndicatorDisable
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
Dem_Indicator_UserIndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
  Dem_Cfg_EventIndicatorIterType lIndicatorIter;

  for (Dem_Cfg_EventIndicatorIterInit(EventId, &lIndicatorIter);                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventIndicatorIterExists(&lIndicatorIter) == TRUE;                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventIndicatorIterNext(&lIndicatorIter))                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_IndicatorIndexType lIndicatorIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    Dem_Cfg_EventJ1939NodeIterType lNodeIter;
# endif

    lIndicatorIndex = Dem_Cfg_EventIndicatorIterGet(&lIndicatorIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    DEM_IGNORE_UNUSED_VARIABLE(lIndicatorIndex)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */

# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    /* Process all nodes linked to the event */
    for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
# endif
    {
      uint8 lNmNodeIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      lNmNodeIndex = Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
# else
      lNmNodeIndex = 0;
# endif
      if ((Dem_Cfg_IndicatorStatus(lIndicatorIndex) & DEM_INDICATOR_CONTINUOUS) != 0)
      {
        Dem_Indicator_SetEventCountContinuous(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex) - 1));
      }
      if ((Dem_Cfg_IndicatorStatus(lIndicatorIndex) & DEM_INDICATOR_BLINKING) != 0)
      {
        Dem_Indicator_SetEventCountBlinking(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(Dem_Cfg_IndicatorId(lIndicatorIndex), lNmNodeIndex) - 1));
      }
    }
  }
#endif /* DEM_CFG_SUPPORT_USER_INDICATORS */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_SpecialIndicatorDisable
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_SpecialIndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  boolean lSpecialIndicator;

  /* EventId might not be used depending on configuration */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lSpecialIndicator = Dem_Cfg_EventSpecialIndicator(EventId);
#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
  if (lSpecialIndicator != DEM_CFG_SPECIAL_INDICATOR_NONE)
  {
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    Dem_Cfg_EventJ1939NodeIterType lNodeIter;

    for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
# endif
    {
      uint8 lNmNodeIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      lNmNodeIndex = Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter);                                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
# else
      lNmNodeIndex = 0;
# endif
      switch (Dem_Cfg_EventSpecialIndicatorState(EventId))
      {
      case DEM_INDICATOR_CONTINUOUS:
        Dem_Indicator_SetEventCountContinuous(lSpecialIndicator, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(lSpecialIndicator, lNmNodeIndex) - 1));
        break;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      case DEM_INDICATOR_FAST_FLASH:
        Dem_Indicator_SetEventCountFastFlash(lSpecialIndicator, lNmNodeIndex, 
          (uint16)(Dem_Indicator_GetEventCountFastFlash(lSpecialIndicator,lNmNodeIndex) - 1));
        break;
      case DEM_INDICATOR_SLOW_FLASH:
        Dem_Indicator_SetEventCountSlowFlash(lSpecialIndicator, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountSlowFlash(lSpecialIndicator, lNmNodeIndex) - 1));
        break;
# endif /* (DEM_CFG_SUPPORT_J1939 == STD_ON) */
# if (DEM_CFG_SUPPORT_J1939 != STD_ON)
      case DEM_INDICATOR_BLINKING:
        Dem_Indicator_SetEventCountBlinking(lSpecialIndicator, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(lSpecialIndicator, lNmNodeIndex) - 1));
        break;
      case DEM_INDICATOR_BLINK_CONT:
        Dem_Indicator_SetEventCountContinuous(lSpecialIndicator, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountContinuous(lSpecialIndicator, lNmNodeIndex) - 1));
        Dem_Indicator_SetEventCountBlinking(lSpecialIndicator, lNmNodeIndex,
          (uint16)(Dem_Indicator_GetEventCountBlinking(lSpecialIndicator, lNmNodeIndex) - 1));
        break;
# endif
      default:
        Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_INCONSISTENT_STATE);
        break;
      }
    }
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
    if (lSpecialIndicator == Dem_Cfg_GlobalMilIndicator())
    {
      uint8 lWwhObdDtcClass;
      lWwhObdDtcClass = Dem_Util_SeverityWwhObdDtcClass(Dem_Cfg_EventSeverity(EventId));
      Dem_Indicator_SetDtcClassMILCount(lWwhObdDtcClass, Dem_Indicator_GetDtcClassMILCount(lWwhObdDtcClass) - 1);
    }
# endif
  }
#endif /* (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON) */
  return lSpecialIndicator;
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */


/* ****************************************************************************
 % Dem_Indicator_IndicatorDisable
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
Dem_Indicator_IndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  uint8 lSpecialIndicator;
  Dem_Indicator_UserIndicatorDisable(EventId);
  Dem_Indicator_UpdateGlobalUserIndicatorForEvent(EventId);
  
  lSpecialIndicator = Dem_Indicator_SpecialIndicatorDisable(EventId);
  if (lSpecialIndicator != DEM_CFG_SPECIAL_INDICATOR_NONE)
  { /* Special indicator was modified, recalculate new state */

# if (DEM_CFG_SUPPORT_PID21 == STD_ON)
    boolean lOldMilIsActive;
    lOldMilIsActive = Dem_Indicator_TestMilReportedActive();
# endif

    Dem_Indicator_UpdateGlobalSpecialIndicatorStates(lSpecialIndicator);
#  if (DEM_CFG_SUPPORT_PID21 == STD_ON)
    if (lSpecialIndicator == Dem_Cfg_GlobalMilIndicator())
    {
      if ( (lOldMilIsActive == TRUE)                                                                                             /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_Indicator_TestMilReportedActive() == FALSE) )
      { /* MIL indicator has changed to OFF */
        Dem_Indicator_GlobalMilStateDisable();
      }
    }
#  endif
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_IndicatorEnable
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
Dem_Indicator_IndicatorEnable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
)
{
  Dem_Indicator_UserIndicatorEnable(EventId);
  Dem_Indicator_UpdateGlobalUserIndicatorForEvent(EventId);
  {
    uint8 lSpecialIndicator;
    lSpecialIndicator = Dem_Indicator_SpecialIndicatorEnable(EventId);
  
    if (lSpecialIndicator != DEM_CFG_SPECIAL_INDICATOR_NONE)
    { /* Special indicator was modified, recalculate new state */
#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
      boolean lOldMilIsActive;
      lOldMilIsActive = Dem_Indicator_TestMilReportedActive();
#endif
      Dem_Indicator_UpdateGlobalSpecialIndicatorStates(lSpecialIndicator);
# if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
      if (Dem_Event_TestMilSupport(EventId) == TRUE)
      {
        if ((lOldMilIsActive == FALSE)                                                                                             /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
           && (Dem_Indicator_TestMilReportedActive() == TRUE))
        {
          Dem_Indicator_UpdatePIDsMilEnabled();
        }
      }
# endif /* (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON) */
    }
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_InitSpecialIndicator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_InitSpecialIndicator(
  void
  )
{
#if (DEM_CFG_SUPPORT_MIL == STD_ON)
  Dem_Indicator_UpdateGlobalSpecialIndicatorStates(Dem_Cfg_GlobalMilIndicator());
#endif
# if (DEM_CFG_SUPPORT_RSL == STD_ON)
  Dem_Indicator_UpdateGlobalSpecialIndicatorStates(Dem_Cfg_GlobalRslIndicator());
# endif
# if (DEM_CFG_SUPPORT_AWL == STD_ON)
  Dem_Indicator_UpdateGlobalSpecialIndicatorStates(Dem_Cfg_GlobalAwlIndicator());
# endif
# if (DEM_CFG_SUPPORT_PL == STD_ON)
  Dem_Indicator_UpdateGlobalSpecialIndicatorStates(Dem_Cfg_GlobalPlIndicator());
# endif
}                                                                                                                                /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_Indicator_InitUserIndicator
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_InitUserIndicator(
  void
  )
{
  Dem_Cfg_IndicatorIndexType lUserIndicatorId;

  /*configuration of indicator ids: 
    0 <= special indicator id < user indicator id < number of all indicators*/
  lUserIndicatorId = Dem_Cfg_SpecialIndicatorCount();

  for (; lUserIndicatorId < Dem_Cfg_GlobalIndicatorCount(); lUserIndicatorId++)
  {
    Dem_Indicator_UpdateGlobalUserIndicatorStates(lUserIndicatorId);
  }
}


/* ****************************************************************************
 % Dem_Indicator_GetIndicatorStatus
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
DEM_LOCAL FUNC(Dem_IndicatorStatusType, DEM_CODE)
Dem_Indicator_GetIndicatorStatus(
  CONST(uint8, AUTOMATIC)  IndicatorId
  )
{
  Dem_IndicatorStatusType lIndicatorStatus;
#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
  lIndicatorStatus = Dem_Indicator_J1939GlobalIndicatorState(IndicatorId);
#else
# if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  if (Dem_Cfg_GlobalMilIndicator() == IndicatorId)
  {
    lIndicatorStatus = Dem_Indicator_GlobalIndicatorActivationMode();
  }
  else
# endif
  {
    lIndicatorStatus = Dem_Indicator_GetGlobalIndicatorState(IndicatorId, 0);
  }
#endif
  return lIndicatorStatus;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */


/* ****************************************************************************
 % Dem_Indicator_InitWwhObdStatistics
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_InitWwhObdStatistics(
  void
  )
{
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
  {
    uint8 lDtcClassIndex;

    lDtcClassIndex = DEM_ESM_WWHOBD_NUMBER_DTCCLASS;

    while (lDtcClassIndex != 0)
    {
      --lDtcClassIndex;

      Dem_Indicator_SetQualifiedActiveEventCount(lDtcClassIndex, 0);
      Dem_Indicator_SetDtcClassMILCount(lDtcClassIndex, 0);
    }
  }
#endif
}

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_GlobalIndicatorActivationMode
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
DEM_LOCAL_INLINE FUNC(Dem_IndicatorStatusType, DEM_CODE)
Dem_Indicator_GlobalIndicatorActivationMode(
  void
  )
{
  Dem_IndicatorStatusType lReturnValue;

  /* calculate the current activation mode */
  if ( (Dem_Indicator_GetQualifiedActiveEventCount(DEM_ESM_WWHOBD_DTCCLASS_A) != 0)
    || (DEM_DATA_B1COUNTER_200H <= Dem_Mem_GetB1Counter()) )
  { /* Class A event currently active or B1 counter exceeds threshold */
    lReturnValue = DEM_INDICATOR_CONTINUOUS;
  }
  else if ( (Dem_Indicator_GetDtcClassMILCount(DEM_ESM_WWHOBD_DTCCLASS_A) != 0)                                                  /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
         || (Dem_Indicator_GetDtcClassMILCount(DEM_ESM_WWHOBD_DTCCLASS_B1) != 0)
         || (Dem_Indicator_GetDtcClassMILCount(DEM_ESM_WWHOBD_DTCCLASS_B2) != 0) )
  {
    lReturnValue = DEM_INDICATOR_SHORT;
  }
  else if (Dem_Indicator_GetDtcClassMILCount(DEM_ESM_WWHOBD_DTCCLASS_C) != 0)
  {
    lReturnValue = DEM_INDICATOR_ON_DEMAND;
  }
  else /* DEM_ESM_WWHOBD_DTCCLASS_NO */
  {
    lReturnValue = DEM_INDICATOR_OFF;
  }
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_Indicator_UpdateGlobalSpecialIndicatorStates
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateGlobalSpecialIndicatorStates(
  CONST(uint8, AUTOMATIC)  IndicatorId
  )
{
#if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
  uint8 lNmNodeIndex;
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
  lNmNodeIndex = Dem_Cfg_GlobalJ1939NodeCount();

  while (lNmNodeIndex != 0)
# else
  lNmNodeIndex = 0;
# endif
  {
    Dem_IndicatorStatusType lIndicatorState;

# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    --lNmNodeIndex;
# endif
    lIndicatorState = DEM_INDICATOR_OFF;

    if (Dem_Indicator_GetEventCountContinuous(IndicatorId, lNmNodeIndex) > 0)
    {
      lIndicatorState = DEM_INDICATOR_CONTINUOUS;
    }
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
    else
    if (Dem_Indicator_GetEventCountFastFlash(IndicatorId, lNmNodeIndex) > 0)
    {
      lIndicatorState = DEM_INDICATOR_FAST_FLASH;
    }
    else
    if (Dem_Indicator_GetEventCountSlowFlash(IndicatorId, lNmNodeIndex) > 0)
    {
      lIndicatorState = DEM_INDICATOR_SLOW_FLASH;
    }
# endif
    else
    {
      /* MISRA*/
    }

# if (DEM_CFG_SUPPORT_J1939 != STD_ON)
    if (Dem_Indicator_GetEventCountBlinking(IndicatorId, lNmNodeIndex) > 0)
    {
      lIndicatorState |= DEM_INDICATOR_BLINKING;
    }
# endif
    Dem_Indicator_SetGlobalIndicatorState(IndicatorId, lNmNodeIndex, lIndicatorState);
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IndicatorId)                                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}

/* ****************************************************************************
 % Dem_Indicator_UpdateGlobalUserIndicatorForEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateGlobalUserIndicatorForEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)
  Dem_Cfg_EventIndicatorIterType lIndicatorIter;

  for (Dem_Cfg_EventIndicatorIterInit(EventId, &lIndicatorIter);                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventIndicatorIterExists(&lIndicatorIter) == TRUE;                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_Cfg_EventIndicatorIterNext(&lIndicatorIter))                                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    Dem_Cfg_IndicatorIndexType lIndicatorIndex;
    uint8 lIndicatorId;

    lIndicatorIndex = Dem_Cfg_EventIndicatorIterGet(&lIndicatorIter);                                                            /* SBSW_DEM_CALL_ITERATOR_POINTER */
    lIndicatorId = Dem_Cfg_IndicatorId(lIndicatorIndex);

    Dem_Indicator_UpdateGlobalUserIndicatorStates(lIndicatorId);
  }
#endif
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
}

/* ****************************************************************************
 % Dem_Indicator_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_Init(void)
{
  /* If indicators are configured, initialize all indicator state counters */
  uint8 lIndicatorId;
  for (lIndicatorId = 0; lIndicatorId < Dem_Cfg_GlobalIndicatorCount(); ++lIndicatorId)
  {
    uint8 lNmNodeIndex;
    for (lNmNodeIndex = 0; lNmNodeIndex < Dem_Cfg_GlobalJ1939NodeCount(); ++lNmNodeIndex)
    {
      Dem_Indicator_SetEventCountContinuous(lIndicatorId, lNmNodeIndex, 0);
      Dem_Indicator_SetEventCountBlinking(lIndicatorId, lNmNodeIndex, 0);
# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
      Dem_Indicator_SetEventCountFastFlash(lIndicatorId, lNmNodeIndex, 0);
      Dem_Indicator_SetEventCountSlowFlash(lIndicatorId, lNmNodeIndex, 0);
# endif
    }
  }
}

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_CalculateGlobalJ1939LampStatus
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
DEM_LOCAL_INLINE FUNC(Dem_J1939DcmLampStatusType, DEM_CODE)
Dem_Indicator_CalculateGlobalJ1939LampStatus(
  CONST(uint8, AUTOMATIC)  NodeId
  )
{
  Dem_J1939DcmLampStatusType lLampStatus;

# if (DEM_CFG_SUPPORT_MIL == STD_ON)                                                                                             /* COV_DEM_UNSUPPORTED_FEATURE XF */
  uint8 lGlobalMilState;
# endif
# if (DEM_CFG_SUPPORT_RSL == STD_ON)
  uint8 lGlobalRslState;
# endif
# if (DEM_CFG_SUPPORT_AWL == STD_ON)
  uint8 lGlobalAwlState;
#endif
# if (DEM_CFG_SUPPORT_PL == STD_ON)
  uint8 lGlobalPlState;
# endif

# if (DEM_CFG_SUPPORT_MIL == STD_ON)                                                                                             /* COV_DEM_UNSUPPORTED_FEATURE XF */
  lGlobalMilState = Dem_Indicator_GetGlobalIndicatorState(Dem_Cfg_GlobalMilIndicator(), NodeId);
# endif
# if (DEM_CFG_SUPPORT_RSL == STD_ON)
  lGlobalRslState = Dem_Indicator_GetGlobalIndicatorState(Dem_Cfg_GlobalRslIndicator(), NodeId);
# endif
# if (DEM_CFG_SUPPORT_AWL == STD_ON)
  lGlobalAwlState = Dem_Indicator_GetGlobalIndicatorState(Dem_Cfg_GlobalAwlIndicator(), NodeId);
#endif
# if (DEM_CFG_SUPPORT_PL == STD_ON)
  lGlobalPlState = Dem_Indicator_GetGlobalIndicatorState(Dem_Cfg_GlobalPlIndicator(), NodeId);
# endif

  /* calculate node related lamp status */
  lLampStatus.LampStatus = (uint8)(Dem_GetHiByte(Dem_Cfg_J1939NodeIndicatorReadiness(NodeId))
# if (DEM_CFG_SUPPORT_MIL == STD_ON)                                                                                             /* COV_DEM_UNSUPPORTED_FEATURE XF */
    | (Dem_Indicator_J1939LampStatus(lGlobalMilState) << 6)
# endif
# if (DEM_CFG_SUPPORT_RSL == STD_ON)
    | (Dem_Indicator_J1939LampStatus(lGlobalRslState) << 4)
# endif
# if (DEM_CFG_SUPPORT_AWL == STD_ON)
    | (Dem_Indicator_J1939LampStatus(lGlobalAwlState) << 2)
# endif
# if (DEM_CFG_SUPPORT_PL == STD_ON)
    | (Dem_Indicator_J1939LampStatus(lGlobalPlState))
# endif
    );

  /* calculate node related flash lamp status */
  lLampStatus.FlashLampStatus = (uint8)( Dem_GetLoByte(Dem_Cfg_J1939NodeIndicatorReadiness(NodeId))
# if (DEM_CFG_SUPPORT_MIL == STD_ON)                                                                                             /* COV_DEM_UNSUPPORTED_FEATURE XF */
    | (Dem_Indicator_J1939FlashLampStatus(lGlobalMilState) << 6)
# endif
# if (DEM_CFG_SUPPORT_RSL == STD_ON)
    | (Dem_Indicator_J1939FlashLampStatus(lGlobalRslState) << 4)
# endif
# if (DEM_CFG_SUPPORT_AWL == STD_ON)
    | (Dem_Indicator_J1939FlashLampStatus(lGlobalAwlState) << 2)
# endif
# if (DEM_CFG_SUPPORT_PL == STD_ON)
    | (Dem_Indicator_J1939FlashLampStatus(lGlobalPlState))
# endif
    );
  return lLampStatus;
}
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_Indicator_CalculateEventJ1939LampStatus
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_Indicator_CalculateEventJ1939LampStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
)
{
  Std_ReturnType lReturnValue;
  Dem_Cfg_EventJ1939NodeIterType lNodeIter;

  lReturnValue = DEM_NO_SUCH_ELEMENT;
  for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
       Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    if (Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter) == NodeId)                                                                     /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      break;
    }
  }
  if (Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE)                                                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    /* Match only events belonging to the requested node */
    lReturnValue = E_OK;

# if (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON)
    if (Dem_Cfg_EventSpecialIndicator(EventId) != DEM_CFG_SPECIAL_INDICATOR_NONE)
    {
      uint8 lEventStatus;
      uint8 lLampStatus;
      uint8 lFlashLampStatus;
      uint8  lSpecialIndicator;

      lEventStatus = Dem_DTC_ApplyExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));

      if (Dem_UDSStatus_Test_WIR(lEventStatus) == TRUE)
      {
        /* indicator requested/active */
        lLampStatus = Dem_Indicator_J1939LampStatus(Dem_Cfg_EventSpecialIndicatorState(EventId));
        lFlashLampStatus = Dem_Indicator_J1939FlashLampStatus(Dem_Cfg_EventSpecialIndicatorState(EventId));
      }
      else
      {
        lLampStatus = DEM_J1939_LAMP_OFF;
        lFlashLampStatus = DEM_J1939_FLASHLAMP_NO_FLASH;
      }

      lSpecialIndicator = Dem_Cfg_EventSpecialIndicator(EventId);

#  if (DEM_FEATURE_NEED_OBD == STD_ON)                                                                                           /* COV_DEM_UNSUPPORTED_FEATURE XF */
      if (lSpecialIndicator == Dem_Cfg_GlobalMilIndicator())
      {
        (FilterResult->LampStatus).LampStatus =                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          (uint8) (DEM_J1939_LAMP_RSL_NA | DEM_J1939_LAMP_AWL_NA | DEM_J1939_LAMP_PL_NA | (lLampStatus << 6));
        (FilterResult->LampStatus).FlashLampStatus =                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          (uint8) (DEM_J1939_FLASHLAMP_RSL_NO_FLASH | DEM_J1939_FLASHLAMP_AWL_NO_FLASH | DEM_J1939_FLASHLAMP_PL_NO_FLASH | (lFlashLampStatus << 6));
      }
      else
#  endif
      if (lSpecialIndicator == Dem_Cfg_GlobalRslIndicator())
      {
        (FilterResult->LampStatus).LampStatus =                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          (uint8) (DEM_J1939_LAMP_MIL_NA | DEM_J1939_LAMP_AWL_NA | DEM_J1939_LAMP_PL_NA | (lLampStatus << 4));
        (FilterResult->LampStatus).FlashLampStatus =                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          (uint8) (DEM_J1939_FLASHLAMP_MIL_NO_FLASH | DEM_J1939_FLASHLAMP_AWL_NO_FLASH | DEM_J1939_FLASHLAMP_PL_NO_FLASH | (lFlashLampStatus << 4));
      }
      else if (lSpecialIndicator == Dem_Cfg_GlobalAwlIndicator())
      {
        (FilterResult->LampStatus).LampStatus =                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          (uint8) (DEM_J1939_LAMP_MIL_NA | DEM_J1939_LAMP_RSL_NA | DEM_J1939_LAMP_PL_NA | (lLampStatus << 2));
        (FilterResult->LampStatus).FlashLampStatus =                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          (uint8) (DEM_J1939_FLASHLAMP_MIL_NO_FLASH | DEM_J1939_FLASHLAMP_RSL_NO_FLASH | DEM_J1939_FLASHLAMP_PL_NO_FLASH | (lFlashLampStatus << 2));
      }
      else if (lSpecialIndicator == Dem_Cfg_GlobalPlIndicator())
      {
        (FilterResult->LampStatus).LampStatus =                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          (uint8) (DEM_J1939_LAMP_MIL_NA | DEM_J1939_LAMP_RSL_NA | DEM_J1939_LAMP_AWL_NA | lLampStatus);
        (FilterResult->LampStatus).FlashLampStatus =                                                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
          (uint8) (DEM_J1939_FLASHLAMP_MIL_NO_FLASH | DEM_J1939_FLASHLAMP_RSL_NO_FLASH | DEM_J1939_FLASHLAMP_AWL_NO_FLASH | lFlashLampStatus);
      }
      else
      {
        Dem_Error_ReportError(DEM_INTERNAL_APIID, DEM_E_PARAM_CONFIG);
      }
    }
    else
# endif /* (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON) */
    { /* No special indicator available for this event, so all lamps are set to no applicable */
      (FilterResult->LampStatus).LampStatus =                                                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        (uint8)(DEM_J1939_LAMP_MIL_NA | DEM_J1939_LAMP_RSL_NA | DEM_J1939_LAMP_AWL_NA | DEM_J1939_LAMP_PL_NA);
      (FilterResult->LampStatus).FlashLampStatus =                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        (uint8)(DEM_J1939_FLASHLAMP_MIL_NO_FLASH | DEM_J1939_FLASHLAMP_RSL_NO_FLASH | DEM_J1939_FLASHLAMP_AWL_NO_FLASH | DEM_J1939_FLASHLAMP_PL_NO_FLASH);
    }
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STPTH */

#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_INDICATOR_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Indicator_Implementation.h
 *********************************************************************************************************************/
