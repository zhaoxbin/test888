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
/*! \ingroup    Dem_DataReportIF
 *  \defgroup   Dem_IntDataElementIF IntDataElementIF
 *  \{
 *  \file       Dem_IntDataElementIF_Interface.h
 *  \brief      Module fetches internal data elements during an on-going read operation.
 *  \details    Module fetches the values for specific internal data elements. The statistical data are calculated 
 *              'live' and provided for an on-going read operation.
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

#if !defined (DEM_INTDATAELEMENTIF_INTERFACE_H)
#define DEM_INTDATAELEMENTIF_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_IntDataElementIF_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_IntDataElementIF_Properties Properties
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
 * \defgroup Dem_IntDataElementIF_Private Private Methods
 * \{
 */

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyUpwardsAgingCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the upward counting aging counter of the event 
 *                holding the event memory entry.
 *
 * \details       Retrieves the upward counting aging counter of the event 
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied          
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyUpwardsAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_Copy1ByteOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the occurrence counter of the event holding the
 *                event memory entry as 1 byte data element.
 *
 * \details       Retrieves the occurrence counter of the event holding the
 *                event memory entry as 1 byte data element. An occurrence 
 *                counter that will not fit 1 byte is written as 255.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_Copy1ByteOccurrenceCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_Copy2ByteOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the occurrence counter of the event holding the
 *                event memory entry as 2 byte data element
 *
 * \details       Retrieves the occurrence counter of the event holding the
 *                event memory entry as 2 byte data element
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_Copy2ByteOccurrenceCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyOverflowIndication
 *****************************************************************************/
/*!
 * \brief         Retrieves the event memory overflow state.
 *
 * \details       Retrieves the event memory overflow state.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyOverflowIndication(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyEventSignificance
 *****************************************************************************/
/*!
 * \brief         Retrieves the significance configuration of the event.
 *
 * \details       Retrieves the significance configuration of the event.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventSignificance(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyEventPriority
 *****************************************************************************/
/*!
 * \brief         Retrieves the priority configuration of the event holding
 *                the event memory entry.
 *
 * \details       Retrieves the priority configuration of the event holding
 *                the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventPriority(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyDownwardsAgingCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the downward counting aging counter of the event 
 *                holding the event memory entry.
 *
 * \details       Retrieves the downward counting aging counter of the event 
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyDownwardsAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyMaxFdcSinceLastClear
 *****************************************************************************/
/*!
 * \brief         Retrieves the maximum fault detection counter since last
 *                clear of the event holding the event memory entry.
 *
 * \details       Retrieves the maximum fault detection counter since last
 *                clear of the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyMaxFdcSinceLastClear(                                                                                   
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyMaxFdcThisCycle
 *****************************************************************************/
/*!
 * \brief         Retrieves the maximum fault detection counter this cycle
 *                of the event holding the event memory entry.
 *
 * \details       Retrieves the maximum fault detection counter this cycle
 *                of the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyMaxFdcThisCycle(                                                                                        
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Retrieves the cycle count since last failed of the event
 *                holding the event memory entry.
 *
 * \details       Retrieves the cycle count since last failed of the event
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Retrieves the cycle count since first failed of the event
 *                holding the event memory entry.
 *
 * \details       Retrieves the cycle count since first failed of the event
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceFirstFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */                                                                         
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyFailedCycles
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles tested failed of the event
 *                holding the event memory entry.
 *
 * \details       Retrieves the number of cycles tested failed of the event
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyFailedCycles(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyConsecutiveFailedCycles
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of consecutive cycles tested failed of
 *                the event holding the event memory entry.
 *
 * \details       Retrieves the number of consecutive cycles tested failed of
 *                the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyConsecutiveFailedCycles(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyFaultPendingCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the 'fault pending counter' of the event holding 
 *                the event memory entry.
 *
 * \details         Retrieves the 'fault pending counter' of the event holding 
 *                the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyFaultPendingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesTestedSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles tested since first failed of
 *                the event holding the event memory entry.
 *
 * \details       Retrieves the number of cycles tested since first failed of
 *                the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesTestedSinceFirstFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesTestedSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles tested since last failed of
 *                the event holding the event memory entry.
 *
 * \details       Retrieves the number of cycles tested since last failed of
 *                the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesTestedSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyHealingCounterDownwards
 *****************************************************************************/
/*!
 * \brief         Retrieves the inverted healing counter of the event holding 
 *                the event memory entry.
 *
 * \details       Retrieves the inverted healing counter of the event holding 
 *                the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyHealingCounterDownwards(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyRootCauseEventId
 *****************************************************************************/
/*!
 * \brief         Retrieves the event that caused event memory storage as
 *                2 byte data element
 *
 * \details       Retrieves the event that caused event memory storage as
 *                2 byte data element. For combined events, this is the exact
 *                sub-event.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyRootCauseEventId(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyEventObdDtc
 *****************************************************************************/
/*!
 * \brief         Retrieves the OBD DTC of the event that stored the
 *                event memory entry as 2 byte data element
 *
 * \details       Retrieves the OBD DTC of the event that stored the
 *                event memory entry as 2 byte data element
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventObdDtc(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyEventObdDtc_3Byte
 *****************************************************************************/
/*!
 * \brief         Retrieves the OBD DTC of the event that stored the
 *                event memory entry as 3 byte data element with trailing 0
 *
 * \details       Retrieves the OBD DTC of the event that stored the
 *                event memory entry as 3 byte data element with trailing 0
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventObdDtc_3Byte(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyEventObdRatio
 *****************************************************************************/
/*!
 * \brief         Retrieves the the ratio/IUMPR attached to the event
 *
 * \details       If ratio availabe copies
 *                [NumeratorHighByte] [NumeratorLowByte] [DenominatorHighByte] [DenominatorLowByte]
 *                If ratio is not available copies
 *                [0x00] [0x00] [0x00] [0x00]
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventObdRatio(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesSinceLastUnconfirmed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles since the last fdc threshold
 *                was exceeded.
 *
 * \details       Retrieves the number of cycles since the last fdc threshold
 *                was exceeded, of the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceLastUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesPassedSinceLastUnconfirmed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles tested passed since the last
 *                fdc threshold was exceeded.
 *
 * \details       Retrieves the number of cycles tested passed since the last
 *                fdc threshold was exceeded, of the event holding the event
 *                memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesPassedSinceLastUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesSinceFirstUnconfirmed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles since the first fdc threshold
 *                was exceeded.
 *
 * \details       Retrieves the number of cycles since the first fdc threshold
 *                was exceeded, of the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceFirstUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyUnconfirmedCycles
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles in which the fdc threshold was
 *                exceeded.
 *
 * \details       Retrieves the number of cycles in which the fdc threshold was
 *                exceeded, of the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyUnconfirmedCycles(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesPassedOrUnconfirmed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles in which the fdc threshold was
 *                exceeded, or a passed result was reported.
 *
 * \details       Retrieves the number of cycles in which the fdc threshold was
 *                exceeded, or a passed result was reported, of the event
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesPassedOrUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCurrentFdc
 *****************************************************************************/
/*!
 * \brief         Retrieves the current fault detection counter of the event
 *                holding the event memory entry.
 *
 * \details       Retrieves the current fault detection counter of the event
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCurrentFdc(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyAgedCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the aged counter of the event.
 *
 * \details       Retrieves the aged counter of the event.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyAgedCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyPreConfirmedStatus
 *****************************************************************************/
/*!
 * \brief         Retrieves the preconfirmed status byte of the event holding
 *                the event memory entry.
 *
 * \details       Retrieves the preconfirmed status byte of the event holding
 *                the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyPreConfirmedStatus(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && \
( (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyStandardEnvData_Dag
 *****************************************************************************/
/*!
 * \brief         Writes a Daimler standard environment data object as 7 byte
 *                data element
 *
 * \details       Writes a Daimler standard environment data object as 7 byte
 *                data element
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Always TRUE
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyStandardEnvData_Dag(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyExtendedEnvData_Dag
 *****************************************************************************/
/*!
 * \brief         Writes a Daimler standard environment data object and
 *                operating time as 12 byte data element
 *
 * \details       Writes a Daimler standard environment data object and
 *                operating time as 12 byte data element
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Always TRUE
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyExtendedEnvData_Dag(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

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
 * \defgroup Dem_IntDataElementIF_Public Public Methods
 * \{
 */

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyInternalDataElement
 *****************************************************************************/
/*!
 * \brief         Copies an internal data element into the destination buffer.
 *
 * \details       Copies an internal data element into the destination buffer.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 * \param[in]     DataIndex
 *                Index of requested data element
 *
 * \return        TRUE
 *                Data element was copied.
 * \return        FALSE
 *                Data element was not copied.
 *
 * \pre           A memory entry has to be locked for Dcm readout.
 * \config        DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyInternalDataElement(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_INTDATAELEMENTIF_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_IntDataElementIF_Interface.h
 *********************************************************************************************************************/
