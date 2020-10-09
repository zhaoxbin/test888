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
/*! \addtogroup Dem_Statistics
 *  \{
 *  \file       Dem_Statistics_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the Statistics subcomponent which calculates global and event related statistics.
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

#if !defined (DEM_STATISTICS_IMPLEMENTATION_H)
#define DEM_STATISTICS_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Statistics_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg_Definitions.h"
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_Mem_Implementation.h"
#include "Dem_UDSStatus_Implementation.h"
#include "Dem_DebounceCounterBased_Implementation.h"

/* Include interface to prevent circular dependencies */
#include "Dem_Event_Interface.h"
#include "Dem_DTC_Interface.h"
#include "Dem_OperationCycle_Interface.h"
#include "Dem_Satellite_Interface.h"
                                                   /* Subcomponents callbacks*/
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
 * \addtogroup Dem_Statistics_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_Statistics_GetFirstFailedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetFirstFailedEvent(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return (Dem_EventIdType)Dem_Cfg_StatusData.FirstFailedEvent;
}


/* ****************************************************************************
 % Dem_Statistics_SetFirstFailedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetFirstFailedEvent(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType EventId
  )
{
  Dem_Cfg_StatusData.FirstFailedEvent = EventId;
}

/* ****************************************************************************
 % Dem_Statistics_GetFirstConfirmedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetFirstConfirmedEvent(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return (Dem_EventIdType)Dem_Cfg_StatusData.FirstConfirmedEvent;
}

/* ****************************************************************************
 % Dem_Statistics_SetFirstConfirmedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetFirstConfirmedEvent(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType EventId
  )
{
  Dem_Cfg_StatusData.FirstConfirmedEvent = EventId;
}

/* ****************************************************************************
 % Dem_Statistics_GetMostRecentFailedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetMostRecentFailedEvent(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return (Dem_EventIdType)Dem_Cfg_StatusData.MostRecentFailedEvent;
}

/* ****************************************************************************
 % Dem_Statistics_SetMostRecentFailedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetMostRecentFailedEvent(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType EventId
  )
{
  Dem_Cfg_StatusData.MostRecentFailedEvent = EventId;
}

/* ****************************************************************************
 % Dem_Statistics_GetMostRecentConfirmedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetMostRecentConfirmedEvent(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return (Dem_EventIdType)Dem_Cfg_StatusData.MostRecentConfmdEvent;
}

/* ****************************************************************************
 % Dem_Statistics_SetMostRecentConfirmedEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetMostRecentConfirmedEvent(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  Dem_EventIdType EventId
  )
{
  Dem_Cfg_StatusData.MostRecentConfmdEvent = EventId;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && \
( (DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON) || (DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON) )
/* ****************************************************************************
 % Dem_Statistics_TestHealingCounterReadable
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
Dem_Statistics_TestHealingCounterReadable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lCounterReadable;
  uint8 lDtcStatus;

  lCounterReadable = FALSE;
  lDtcStatus = Dem_DTC_GetDTCStatus(EventId);

  if ( (Dem_UDSStatus_Test_TFSLC(lDtcStatus) == TRUE) && (Dem_UDSStatus_Test_PDTC(lDtcStatus) == FALSE) )                        /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
  {
    lCounterReadable = TRUE;
  }

  return lCounterReadable;
}
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_Statistics_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Statistics_UpdateGlobalFailureStatistics
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
Dem_Statistics_UpdateGlobalFailureStatistics(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects
  )
{
  if ( (EventId >= Dem_Cfg_GlobalPrimaryFirst())                                                                                 /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (EventId <= Dem_Cfg_GlobalPrimaryLast()) )
  {
    if ((Effects & DEM_CFG_TRIGGER_CONFIRMED) != 0)
    {
      if (Dem_Statistics_GetFirstConfirmedEvent() == DEM_EVENT_INVALID)
      {
        Dem_Statistics_SetFirstConfirmedEvent(EventId);
      }

      Dem_Statistics_SetMostRecentConfirmedEvent(EventId);
    }

    if (Dem_Statistics_GetFirstFailedEvent() == DEM_EVENT_INVALID)
    {
      Dem_Statistics_SetFirstFailedEvent(EventId);
    }
    Dem_Statistics_SetMostRecentFailedEvent(EventId);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_AGINGCTR == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateUpwardsAgingCounter
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateUpwardsAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  uint8 lAgingCounter;

  if ( (Dem_DTC_GetAgingCounter(CopyDidInfoPtr->EventId, CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)/* PRQA S 3415 */ /* MD_DEM_12.4_cf */
# if (DEM_CFG_AGING_COUNT_ONLY_AGEABLE == STD_ON)
    || (Dem_Cfg_EventSupportAging(CopyDidInfoPtr->EventId) == FALSE)
# endif
     )
  {
    lAgingCounter = 0x00U;
  }
  else
  if (Dem_DTC_GetAgingCounter(CopyDidInfoPtr->EventId, CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)
  {
    lAgingCounter = 0xffU;
  }
# if ((DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON) || (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON))
  else
  if (Dem_DTC_GetAgingCounter(CopyDidInfoPtr->EventId, CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
  {
    lAgingCounter = (uint8)(Dem_Cfg_EventAgingTarget(CopyDidInfoPtr->EventId));
  }
# endif
  else
  {
    uint16 lTarget = Dem_DTC_GetAgingCounter(CopyDidInfoPtr->EventId, CopyDidInfoPtr->MemoryEntryId);
    uint16 lCurrent = Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventAgingCycle(CopyDidInfoPtr->EventId));
    lAgingCounter = (uint8)(Dem_Cfg_EventAgingTarget(CopyDidInfoPtr->EventId) - Dem_OperationCycle_CycleCountDistance(lCurrent, lTarget));
# if (DEM_CFG_AGING_REPORT_ZERO_AS_ONE == STD_ON)
    if (lAgingCounter == 0x00U)
    {
      lAgingCounter = 0x01U;
    }
# endif
  }

  return lAgingCounter;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_OCCCTR == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_Calculate1ByteOccurrenceCounter
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
Dem_Statistics_Calculate1ByteOccurrenceCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  uint8 lOccurrenceCounter;

# if (DEM_CFG_DATA_OCCCTR_2BYTE == STD_ON)
  {
    uint16 lOccurrenceCounter2Byte;
    lOccurrenceCounter2Byte = Dem_MemoryEntry_GetOccurrenceCounter2Byte(CopyDidInfoPtr->MemoryEntryId);
    if (lOccurrenceCounter2Byte > 0xffU)
    {
      lOccurrenceCounter = 0xffU;
    }
    else
    {
      lOccurrenceCounter = (uint8) lOccurrenceCounter2Byte;
    }
  }
# else
  lOccurrenceCounter = (uint8)Dem_MemoryEntry_GetOccurrenceCounter1Byte(CopyDidInfoPtr->MemoryEntryId);
# endif

  return lOccurrenceCounter;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_SIGNIFICANCE == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateEventSignificance
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateEventSignificance(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  uint8 lEventSignificance;

  lEventSignificance = (uint8)(Dem_Cfg_EventSignificance(CopyDidInfoPtr->EventId) == DEM_CFG_EVENT_SIGNIFICANCE_FAULT);
  return lEventSignificance;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_AGINGCTR_INVERTED == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateDownwardsAgingCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateDownwardsAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  uint8 lAgingCounterInverted;

  if ((Dem_DTC_GetAgingCounter(CopyDidInfoPtr->EventId, CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID) /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
# if (DEM_CFG_AGING_COUNT_ONLY_AGEABLE == STD_ON)
    || (Dem_Cfg_EventSupportAging(CopyDidInfoPtr->EventId) == FALSE)
# endif
     )
  {
    lAgingCounterInverted = Dem_Cfg_EventAgingTarget(CopyDidInfoPtr->EventId);
  }
  else
  if ( (Dem_DTC_GetAgingCounter(CopyDidInfoPtr->EventId, CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)/* PRQA S 3415 */ /* MD_DEM_12.4_cf */
# if ((DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON) || (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON))
    || (Dem_DTC_GetAgingCounter(CopyDidInfoPtr->EventId, CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_AGED)
# endif
    )
  {
    lAgingCounterInverted = 0x00U;
  }
  else
  {
    uint16 lTarget = Dem_DTC_GetAgingCounter(CopyDidInfoPtr->EventId, CopyDidInfoPtr->MemoryEntryId);
    uint16 lCurrent = Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventAgingCycle(CopyDidInfoPtr->EventId));
    lAgingCounterInverted = (uint8)(Dem_OperationCycle_CycleCountDistance(lCurrent, lTarget));
  }

  return lAgingCounterInverted;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateMaxFdcSinceLastClear
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
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Statistics_CalculateMaxFdcSinceLastClear(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  sint8 lMaxFdcSinceLastClear;

  if (Dem_UDSStatus_Test_TFSLC(Dem_DTC_GetDTCStatus(CopyDidInfoPtr->EventId)) == TRUE)
  {
    lMaxFdcSinceLastClear = 127;
  }
  else
  {
    lMaxFdcSinceLastClear = (sint8)Dem_MemoryEntry_GetDebounceValueMax(CopyDidInfoPtr->MemoryEntryId);
  }

  return lMaxFdcSinceLastClear;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateMaxFdcThisCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Statistics_CalculateMaxFdcThisCycle(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  sint8 lMaxFdcThisCycle;

# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  Dem_Cfg_CombinedGroupIndexType lGroupId;
  lGroupId = Dem_Cfg_EventCombinedGroup(CopyDidInfoPtr->EventId);
  if (lGroupId != DEM_CFG_COMBINED_GROUP_INVALID)
  {
    lMaxFdcThisCycle = Dem_DTC_CombinedGroupGetFDCMax(lGroupId);
  }
  else
# endif
  {
    lMaxFdcThisCycle = Dem_Satellite_GetMaxFaultDetectionCounter(
                         Dem_Cfg_EventSatelliteId(CopyDidInfoPtr->EventId),
                         Dem_Cfg_EventSatelliteEventId(CopyDidInfoPtr->EventId)
                         );
  }

  return lMaxFdcThisCycle;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateCyclesSinceLastFailed
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
Dem_Statistics_CalculateCyclesSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  uint8 lCyclesSinceLastFailed;

  if (Dem_MemoryEntry_GetCyclesSinceLastFailed(CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
  {
    lCyclesSinceLastFailed = 0x00U;
  }
  else
  if (Dem_MemoryEntry_GetCyclesSinceLastFailed(CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)
  {
    lCyclesSinceLastFailed = 0xffU;
  }
  else
  {
    lCyclesSinceLastFailed = (uint8)Dem_OperationCycle_CycleCountDistance(
                                      Dem_MemoryEntry_GetCyclesSinceLastFailed(CopyDidInfoPtr->MemoryEntryId),
                                      Dem_OperationCycle_GetCycleCounter(
                                      Dem_Cfg_EventOperationCycle(CopyDidInfoPtr->EventId))
                                      );
  }

  return lCyclesSinceLastFailed;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateCyclesSinceFirstFailed
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
Dem_Statistics_CalculateCyclesSinceFirstFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  uint8 lCyclesSinceFirstFailed;

  if (Dem_MemoryEntry_GetCyclesSinceFirstFailed(CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
  {
    lCyclesSinceFirstFailed = 0x00U;
  }
  else
  if (Dem_MemoryEntry_GetCyclesSinceFirstFailed(CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)
  {
    lCyclesSinceFirstFailed = 0xffU;
  }
  else
  {
    lCyclesSinceFirstFailed = (uint8)Dem_OperationCycle_CycleCountDistance(
                                       Dem_MemoryEntry_GetCyclesSinceFirstFailed(CopyDidInfoPtr->MemoryEntryId),
                                       Dem_OperationCycle_GetCycleCounter(
                                       Dem_Cfg_EventOperationCycle(CopyDidInfoPtr->EventId))
                                       );
  }

  return lCyclesSinceFirstFailed;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateCyclesTestedSinceLastFailed
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCyclesTestedSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  uint8 lCyclesTestedSinceLastFailed;

  if (Dem_Statistics_TestHealingCounterReadable(CopyDidInfoPtr->EventId) == TRUE)
  {
    lCyclesTestedSinceLastFailed = Dem_Event_GetTripCount(CopyDidInfoPtr->EventId);
  }
  else
  {
    lCyclesTestedSinceLastFailed = 0x00;
  }

  return lCyclesTestedSinceLastFailed;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateFaultPendingCounter
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateFaultPendingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  uint8 lConsecutiveFailedCycleCounter;
  uint8 lFaultPendingCounter;

  lConsecutiveFailedCycleCounter = Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(CopyDidInfoPtr->MemoryEntryId);
  
  if (lConsecutiveFailedCycleCounter > (Dem_Cfg_EventTripTarget(CopyDidInfoPtr->EventId) + 1))
  {
    /* Different to the trip counter, the 'consecutive failed cycle counter' 
       takes first failed cycle into account */
    lFaultPendingCounter = Dem_Cfg_EventTripTarget(CopyDidInfoPtr->EventId) + 1;
  }
  else
  {
    lFaultPendingCounter = lConsecutiveFailedCycleCounter;
  }

  return lFaultPendingCounter;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateInvertedHealingCounter
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
Dem_Statistics_CalculateInvertedHealingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  uint8 lHealingCounterInverted;

  if (Dem_Statistics_TestHealingCounterReadable(CopyDidInfoPtr->EventId) == TRUE)
  {
    if (Dem_Event_GetTripCount(CopyDidInfoPtr->EventId) < Dem_Cfg_EventHealingTarget(CopyDidInfoPtr->EventId))
    {
      lHealingCounterInverted = (Dem_Cfg_EventHealingTarget(CopyDidInfoPtr->EventId) - Dem_Event_GetTripCount(CopyDidInfoPtr->EventId));
    }
    else
    {
      lHealingCounterInverted = 0x00;
    }
  }
  else
  {
    lHealingCounterInverted = Dem_Cfg_EventHealingTarget(CopyDidInfoPtr->EventId);
  }

  return lHealingCounterInverted;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_OBD_RATIO == STD_ON)
/* ****************************************************************************
 % Dem_Statistics_CalculateObdRatio
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
Dem_Statistics_CalculateObdRatio(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr,                                                         /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) Numerator,
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) Denominator
  )
{
# if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
  Dem_RatioIdIndexType  lRatioIndex;
  lRatioIndex = Dem_Cfg_EventRatioIdIdx(CopyDidInfoPtr->EventId);

  if ( (lRatioIndex != DEM_CFG_RATIOINDEX_INVALID)                                                                               /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
       && (Dem_Cfg_EventIsCombined(CopyDidInfoPtr->EventId) == FALSE)
     )
  {
    *Numerator = Dem_Mem_GetNumerator(lRatioIndex);                                                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    *Denominator = Dem_Mem_GetDenominator(lRatioIndex);                                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
  
  else
# endif
  {
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
    *Numerator = 0x00;                                                                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    *Denominator = 0x00;                                                                                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && \
( (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_Statistics_CalculateDAGAgingCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateDAGAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_16.7_Internal */
  )
{
  uint8 lAgingCounter;

  if (Dem_DTC_GetAgingCounter(CopyDidInfoPtr->EventId, CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID)
  {
    lAgingCounter = 0x00U;
  }
  else
  if (Dem_DTC_GetAgingCounter(CopyDidInfoPtr->EventId, CopyDidInfoPtr->MemoryEntryId) == DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED)
  {
    lAgingCounter = 0xffU;
  }
  else
  {
    uint16 lTarget = Dem_DTC_GetAgingCounter(CopyDidInfoPtr->EventId, CopyDidInfoPtr->MemoryEntryId);
    uint16 lCurrent = Dem_OperationCycle_GetCycleCounter(Dem_Cfg_EventAgingCycle(CopyDidInfoPtr->EventId));
    lAgingCounter = (uint8)(Dem_Cfg_EventAgingTarget(CopyDidInfoPtr->EventId) - Dem_OperationCycle_CycleCountDistance(lCurrent, lTarget));
  }

  return lAgingCounter;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_STATISTICS_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Statistics_Implementation.h
 *********************************************************************************************************************/
