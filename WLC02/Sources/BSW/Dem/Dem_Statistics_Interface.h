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
 *  \defgroup   Dem_Statistics Statistics
 *  \{
 *  \file       Dem_Statistics_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the Statistics subcomponent which calculates global and event related statistics.
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

#if !defined (DEM_STATISTICS_INTERFACE_H)
#define DEM_STATISTICS_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Statistics_Types.h"

/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Statistics_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Statistics_GetFirstFailedEvent
 *****************************************************************************/
/*!
 * \brief         Get the first failed event.
 *
 * \details       Get the first failed event.
 *
 * \return        The first failed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetFirstFailedEvent(
  void
  );

/* ****************************************************************************
 * Dem_Statistics_SetFirstFailedEvent
 *****************************************************************************/
/*!
 * \brief         Set the first failed event.
 *
 * \details       Set the first failed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetFirstFailedEvent(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_Statistics_GetFirstConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Get the first confirmed event.
 *
 * \details       Get the first confirmed event.
 *
 * \return        The first confirmed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetFirstConfirmedEvent(
  void
  );


/* ****************************************************************************
 * Dem_Statistics_SetFirstConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Set the first confirmed event.
 *
 * \details       Set the first confirmed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetFirstConfirmedEvent(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_Statistics_GetMostRecentFailedEvent
 *****************************************************************************/
/*!
 * \brief         Get the most recently failed event.
 *
 * \details       Get the most recently failed event.
 *
 * \return        The most recently failed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetMostRecentFailedEvent(
  void
  );

/* ****************************************************************************
 * Dem_Statistics_SetMostRecentFailedEvent
 *****************************************************************************/
/*!
 * \brief         Set the most recently failed event.
 *
 * \details       Set the most recently failed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetMostRecentFailedEvent(
  Dem_EventIdType EventId
  );

/* ****************************************************************************
 * Dem_Statistics_GetMostRecentConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Get the most recently confirmed event.
 *
 * \details       Get the most recently confirmed event.
 *
 * \return        The most recently confirmed event.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Statistics_GetMostRecentConfirmedEvent(
  void
  );

/* ****************************************************************************
 * Dem_Statistics_SetMostRecentConfirmedEvent
 *****************************************************************************/
/*!
 * \brief         Set the most recently confirmed event.
 *
 * \details       Set the most recently confirmed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_SetMostRecentConfirmedEvent(
  Dem_EventIdType EventId
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && \
( (DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON) || (DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON) )
/* ****************************************************************************
 * Dem_Statistics_TestHealingCounterReadable
 *****************************************************************************/
/*!
 * \brief         Returns if the healing counter can be read.
 *
 * \details       The healing counter (corresponding to 'Cycles Tested
 *                Since Last Failed') can be read, if the event is currently
 *                healing or is already healed.
 *                In order that the counter is not reported, if the event was
 *                never tested failed, the TFSLC status bit has to be set.
 *                In order that the counter is not reported, if healing hasn't
 *                been started for the event, the PDTC status bit has to be
 *                unset (in configurations with PDTC status bit set
 *                'Stored Only' this is only secure, if the event is stored).
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The healing counter can be read.
 *                FALSE
 *                The healing counter can not be read.
 *
 * \pre           -
 * \config        ((DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON || 
 *                  DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                 (DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON ||
 *                  DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Statistics_TestHealingCounterReadable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Statistics_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Statistics_UpdateGlobalFailureStatistics
 *****************************************************************************/
/*!
 * \brief         This function updates global failure statistics.
 *
 * \details       This function updates global failure statistics like first
 *                and most recently failed event, first and most recently 
 *                confirmed event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     Effects
 *                Trigger flags
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_UpdateGlobalFailureStatistics(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects
  );

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_AGINGCTR == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateUpwardsAgingCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates the upward counting aging counter of the 
 *                event holding the event memory entry.
 *
 * \details       Function calculates the upward counting aging counter of the 
 *                event holding the event memory entry.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of upward counting aging counter.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_AGINGCTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateUpwardsAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_OCCCTR == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_Calculate1ByteOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates the 1 Byte occurrence counter of the 
 *                event holding the event memory entry.
 *
 * \details       Function calculates the 1 Byte occurrence counter of the 
 *                event holding the event memory entry.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of 1 Byte occurrence counter.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_OCCCTR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_Calculate1ByteOccurrenceCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_SIGNIFICANCE == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateEventSignificance
 *****************************************************************************/
/*!
 * \brief         Function calculates the significance of the event.
 *
 * \details       Function calculates the significance of the event.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of event significance.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_SIGNIFICANCE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateEventSignificance(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_AGINGCTR_INVERTED == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateDownwardsAgingCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates the downward counting aging counter of the 
 *                event holding the event memory entry.
 *
 * \details       Function calculates the downward counting aging counter of the 
 *                event holding the event memory entry.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of downward counting aging counter.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_AGINGCTR_INVERTED == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateDownwardsAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateMaxFdcSinceLastClear
 *****************************************************************************/
/*!
 * \brief         Function calculates the maximum fault detection counter since 
 *                last clear of the event holding the event memory entry.
 *
 * \details       Function calculates the maximum fault detection counter since 
 *                last clear of the event holding the event memory entry.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of maximum fault detection counter since last clear.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Statistics_CalculateMaxFdcSinceLastClear(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateMaxFdcThisCycle
 *****************************************************************************/
/*!
 * \brief         Function calculates the maximum fault detection counter during 
 *                current cycle of the event holding the event memory entry.
 *
 * \details       Function calculates the maximum fault detection counter during 
 *                current cycle of the event holding the event memory entry.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of maximum fault detection counter during current cycle.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Statistics_CalculateMaxFdcThisCycle(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Function calculates number of cycles since last failed report 
 *                of the event holding the event memory entry.
 *
 * \details       Function calculates number of cycles since last failed report 
 *                of the event holding the event memory entry.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of number of cycles since last failed report.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCyclesSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Function calculates number of cycles since first failed report 
 *                of the event holding the event memory entry.
 *
 * \details       Function calculates number of cycles since first failed report 
 *                of the event holding the event memory entry.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of number of cycles since first failed.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCyclesSinceFirstFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateCyclesTestedSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Function calculates the number of cycles tested since last 
 *                failed report of the event.
 *
 * \details       Function calculates the number of cycles tested since last 
 *                failed report of the event.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of the number of cycles tested since last failed report.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateCyclesTestedSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateFaultPendingCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates the 'fault pending counter' of the event.
 *
 * \details       Function calculates the 'fault pending counter' of the event.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of the number of consecutive cycles tested failed with 
 *                a maximum value that is reached when the DTC confirms.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateFaultPendingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateInvertedHealingCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates the inverted healing counter of the event.
 *
 * \details       Function calculates the inverted healing counter of the event.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of the inverted healing counter.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateInvertedHealingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_OBD_RATIO == STD_ON)
/* ****************************************************************************
 * Dem_Statistics_CalculateObdRatio
 *****************************************************************************/
/*!
 * \brief         Function retrieves the IUMPR numerator and denominator of the 
 *                ratio associated with the event.
 *
 * \details       Function retrieves the IUMPR numerator and denominator of the 
 *                ratio associated with the event.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 * \param[out]    Numerator
 *                Pointer to receive the IUMPR numerator
 * \param[out]    Denominator
 *                Pointer to receive the IUMPR denominator
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_OBD_RATIO == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Statistics_CalculateObdRatio(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr, 
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) Numerator,
  CONSTP2VAR(uint16, AUTOMATIC, AUTOMATIC) Denominator
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && \
( (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON) )
/* ****************************************************************************
 * Dem_Statistics_CalculateDAGAgingCounter
 *****************************************************************************/
/*!
 * \brief         Function calculates the DAG specific upward counting aging 
 *                counter of the event holding the event memory entry.
 *
 * \details       Function calculates the DAG specific upward counting aging 
 *                counter of the event holding the event memory entry.
 *
 * \param[in]     CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Value of DAG specific upward counting aging counter.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON ||
 *                DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Statistics_CalculateDAGAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_STATISTICS_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Statistics_Interface.h
 *********************************************************************************************************************/
