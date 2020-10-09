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
/*! \ingroup    Dem_ClientAccess
 *  \defgroup   Dem_FreezeFrameIterator FreezeFrame Iterator
 *  \{
 *  \file       Dem_FreezeFrameIterator_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
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

#if !defined (DEM_FREEZEFRAMEITERATOR_INTERFACE_H)
#define DEM_FREEZEFRAMEITERATOR_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
# include "Dem_FreezeFrameIterator_Types.h"
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
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DEM_START_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_FreezeFrameIterator_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_FreezeFrameIterator_SetFreezeFrameFilterData()
 *****************************************************************************/
/*!
 * \brief         Set the filter data of a freeze frame iterator.
 *
 * \details       Set the filter data of a freeze frame iterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.
 * \param[in]     FreezeFrameFilterData
 *                The freeze frame filter data to be set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_FreezeFrameIterator_SetFreezeFrameFilterData(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONST(Dem_FreezeFrameIterator_FilterType, AUTOMATIC)  FreezeFrameFilterData
  );

/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetFreezeFrameFilterData()
 *****************************************************************************/
/*!
 * \brief         Get the filter data of a freeze frame iterator.
 *
 * \details       Get the filter data of a freeze frame iterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.

 * \return        The filter data of the freeze frame iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FreezeFrameIterator_FilterType, DEM_CODE) 
Dem_FreezeFrameIterator_GetFreezeFrameFilterData(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetDTCFormat
 *****************************************************************************/
/*!
 * \brief         Get the DTCFormat of the FreezeFrameIterator.
 *
 * \details       Get the DTCFormat of the FreezeFrameIterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.
 *
 * \return        DEM_FREEZEFRAMEITERATOR_DTCFORMAT_INIT
 *                Initialization value, filter/iterator is unused.
 *
 *                DEM_FREEZEFRAMEITERATOR_DTCFORMAT_UDS
 *                The filter selects the 3-byte UDS DTC format
 *                (refer to configuration parameter DemUdsDTC).
 *
 *                DEM_FREEZEFRAMEITERATOR_DTCFORMAT_OBD
 *                The filter selects the 2-byte OBD DTC format
 *                (refer to configuration parameter DemObdDTC).
 *
 *                DEM_FREEZEFRAMEITERATOR_DTCFORMAT_J1939
 *                Selects the merged SPN + FMI to 3-byte J1939 DTC format
 *                (refer to configuration parameter DemJ1939DTC).
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FreezeFrameIterator_DTCFormatType, DEM_CODE)
Dem_FreezeFrameIterator_GetDTCFormat(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetMemoryIndex
 *****************************************************************************/
/*!
 * \brief         Get the MemoryIndex of the FreezeFrameIterator.
 *
 * \details       Get the MemoryIndex of the FreezeFrameIterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.
 *
 * \return        The memory entry iterator position.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetMemoryIndex(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNodeId
 *****************************************************************************/
/*!
 * \brief         Get the node Id of the FreezeFrameIterator.
 *
 * \details       Get the node Id of the FreezeFrameIterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.
 *
 * \return        The node Id of the FreezeFrameIterator.
 *
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetNodeId(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetFilterState
 *****************************************************************************/
/*!
 * \brief         Get the filter state of the FreezeFrameIterator.
 *
 * \details       Get the filter state of the FreezeFrameIterator.
 *
 * \param[in]     FreezeFrameIteratorId
 *                Index in FreezeFrameIteratorTable, derived from the ClientId.
 *
 * \return        The filter state of the FreezeFrameIterator.
 *
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different FreezeFrameIterator Ids
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FreezeFrameIterator_GetFilterState(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_FilterGlobalSRec
 *****************************************************************************/
/*!
 * \brief         Filter for glonal snapshot
 *
 * \details       Filter for glonal snapshot
 *
 * \param[in,out] SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \pre           SnapshotEntryIter has been initialized
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON ||
 *                DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_FilterGlobalSRec(
  CONSTP2VAR(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_FreezeFrameIterator_FilterSRec
 *****************************************************************************/
/*!
 * \brief         Filters the snapshot records of events stored in primary
 *                memory.
 * \details       Filters the snapshot records of events stored in primary
 *                memory.
 *
 * \param[in]     FreezeFrameIteratorId
 *                The FreezeFrameIteratorId that defines the filter.
 * \param[out]    DTC
 *                Pointer to receive the UDS DTC number
 * \param[out]    RecordNumber
 *                Pointer to receive the snapshot record number
 *
 * \return        TRUE
 *                Next record was found
 *                FALSE
 *                No more record found
 *
 * \pre           The record filter has been initialized by
 *                Dem_SetFreezeFrameRecordFilter
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && ((DEM_CFG_SUPPORT_SRECS == STD_ON) 
 *                   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_FilterSRec(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  RecordNumber
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif

# if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_FilterTimeSeriesSRec
 *****************************************************************************/
/*!
 * \brief         Filters the time series snapshot records
 *
 * \details       Filters the time series snapshot records
 *
 * \param[in]     FreezeFrameIteratorId
 *                The FreezeFrameIteratorId that defines the filter.
 * \param[out]    DTC
 *                Pointer to receive the UDS DTC number
 * \param[out]    RecordNumber
 *                Pointer to receive the snapshot record number
 *
 * \return        TRUE
 *                Next record was found
 *                FALSE
 *                No more record found
 *
 * \pre           The record filter has been initialized by
 *                Dem_SetFreezeFrameRecordFilter
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && (DEM_CFG_SUPPORT_SRECS == STD_ON)
 *                && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_FilterTimeSeriesSRec(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  RecordNumber
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNumberOfSRec
 *****************************************************************************/
/*!
 * \brief         Gets the number of stored snapshot records
 *
 * \details       Gets the number of stored snapshot records
 *
 * \return        Number of stored records
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && ((DEM_CFG_SUPPORT_SRECS == STD_ON) 
 *                   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_FreezeFrameIterator_GetNumberOfSRec(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif

# if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNumberOfTimeSeriesSRec
 *****************************************************************************/
/*!
 * \brief         Gets the number of stored time series snapshot records
 *
 * \details       Gets the number of stored time series snapshot records
 *
 * \return        number of stored records
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && (DEM_CFG_SUPPORT_SRECS == STD_ON)
 *                && (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_FreezeFrameIterator_GetNumberOfTimeSeriesSRec(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_FindNextJ1939DTC
 *****************************************************************************/
/*!
 * \brief         Filters the next J1939 DTC
 *
 * \details       Filters the next J1939 DTC
 *
 * \param[in]     FreezeFrameIteratorId
 *                Current iteration handle
 * \param[in]     LastEventId
 *                Current iteration position
 * \param[in]     FreezeFrameKind
 *                DEM_J1939DCM_FREEZEFRAME 
 *                Find the next event with a freeze frame
 *                DEM_J1939DCM_EXPANDED_FREEZEFRAME 
 *                Find the next event with an expanded freeze frame
 *
 * \return        E_OK
 *                A DTC was returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                No DTC left to iterate
 *
 * \pre           A J1939 freeze frame filter has been set up by 
 *                Dem_FreezeFrameIterator_StartJ1939Iterator
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_FreezeFrameIterator_FindNextJ1939DTC(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONST(Dem_EventIdType, AUTOMATIC)  LastEventId,
  CONST(uint8, AUTOMATIC)  FreezeFrameKind
  );
#endif

/*!
 * \}
 */
# define DEM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DEM_START_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_FreezeFrameIterator_Public Public Methods
 * \{
 */

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) )
/* ****************************************************************************
 * Dem_FreezeFrameIterator_InitDefault
 *****************************************************************************/
/*!
 * \brief         Initialize a FreezeFrameIterator.
 *
 * \details       Initializes a FreezeFrameIterator, the resulting filter
 *                cannot be used by GetNextFilteredRecord without prior
 *                calling Dem_SetFreezeFrameRecordFilter.
 *
 * \param[in]     FreezeFrameIteratorId
 *                The FreezeFrameIteratorId to initialize.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON ||
 *                DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FreezeFrameIteratorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FreezeFrameIterator_InitDefault(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );
#endif

# if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_TestFilterSet
 *****************************************************************************/
/*!
 * \brief         Test FreezeFrameIterator for containing valid filter setting.
 *
 * \details       Test that freeze frame filter has been set.
 *
 * \param[in]     FreezeFrameIteratorId
 *                The FreezeFrameIteratorId to test.
 *
 * \return        TRUE
 *                The freeze frame filter can be used.
 * \return        FALSE
 *                The freeze frame filter is not initialized.
 *                
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FreezeFrameIteratorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_TestFilterSet(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );
#endif

# if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_TestJ1939FreezeFrameFilterSet
 *****************************************************************************/
/*!
 * \brief         Test if a J1939 freeze frame filter has been set.
 *
 * \details       Test if a J1939 freeze frame filter has been set.
 *
 * \param[in]     FreezeFrameIteratorId
 *                The FreezeFrameIteratorId to test.
 *
 * \return        TRUE
 *                A J1939 freeze frame filter has been set.
 * \return        FALSE
 *                No J1939 freeze frame filter has been set.
 *                
 *
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FreezeFrameIteratorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_TestJ1939FreezeFrameFilterSet(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId
  );
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_FreezeFrameIterator_StartIterator
 *****************************************************************************/
/*!
 * \brief         Initialize (start) FreezeFrameIterator with given criteria.
 *
 * \details       Initialize (start) FreezeFrameIterator with given criteria.
 *
 * \param[in]     FreezeFrameIteratorId
 *                The FreezeFrameIteratorId to initialize.
 * \param[in]     FilterDTCFormat
 *                Defines the output-format of the requested DTC values.
 * \param[in]     MemoryIndex
 *                First memory block index belonging to the memory.
 *
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && ((DEM_CFG_SUPPORT_SRECS == STD_ON) 
 *                   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FreezeFrameIterator_StartIterator(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONST(Dem_FreezeFrameIterator_DTCFormatType, AUTOMATIC)  FilterDTCFormat,
  CONST(uint8, AUTOMATIC)  MemoryIndex
  );
# endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNext
 *****************************************************************************/
/*!
 * \brief         Initialize (start) FreezeFrameIterator with given criteria.
 *
 * \details       Initialize (start) FreezeFrameIterator with given criteria.
 *
 * \param[in]     FreezeFrameIteratorId
 *                The FreezeFrameIteratorId to iterate.
 * \param[out]    DTC
 *                With return value TRUE: the next filtered DTC number.
 * \param[out]    RecordNumber
 *                With return value TRUE: the next filtered RecordNumber
 *                number of the DTC.
 *
 * \return        TRUE
 *                Returned next filtered element.
 * \return        FALSE
 *                No further element (matching the filter criteria) found,
 *                iteration is complete.
 *
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && ((DEM_CFG_SUPPORT_SRECS == STD_ON) 
 *                   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FreezeFrameIterator_GetNext(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,                                                                                   /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  RecordNumber                                                                            /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  );
# endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNumberOfFreezeFrameRecords
 *****************************************************************************/
/*!
 * \brief         Gets the total number of stored FreezeFrame records
 *
 * \details       Gets the number of stored FreezeFrame records
 *
 * \return        Number of stored records
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && ((DEM_CFG_SUPPORT_SRECS == STD_ON) 
 *                   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_FreezeFrameIterator_GetNumberOfFreezeFrameRecords(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# endif

# if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_StartJ1939Iterator
 *****************************************************************************/
/*!
 * \brief         Initialize the J1939 freeze frame iterator with given criteria.
 *
 * \details       Initialize the J1939 freeze frame iterator with given criteria.
 *
 * \param[in]     FreezeFrameIteratorId
 *                The FreezeFrameIteratorId to initialize.
 * \param[in]     FreezeFrameKind
 *                Kind of freeze frames to be filtered.
 * \param[in]     NodeId
 *                The node Id.
 *
 * \return        E_OK
 *                The filter was set
 * \return        E_NOT_OK
 *                The filter was not set due to an invalid freeze frame kind
 *
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_FreezeFrameIterator_StartJ1939Iterator(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)  FreezeFrameIteratorId,
  CONST(Dem_J1939DcmSetFreezeFrameFilterType, AUTOMATIC)  FreezeFrameKind,
  CONST(uint8, AUTOMATIC)  NodeId
  );
#endif

# if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_FreezeFrameIterator_GetNextJ1939FreezeFrame
 *****************************************************************************/
/*!
 * \brief         Initialize (start) FreezeFrameIterator with given criteria.
 *
 * \details       Initialize (start) FreezeFrameIterator with given criteria.
 *
 * \param[in]     FreezeFrameIteratorId
 *                The FreezeFrameIteratorId to iterate.
 * \param[out]    J1939DTC
 *                Pointer to the J1939DTC .
 * \param[out]    OccurrenceCounter
 *                Pointer to the OccurrenceCounter buffer.
 * \param[out]    DestBuffer
 *                Buffer to receive the J1939 freeze frame data.
 * \param[in,out] BufSize
 *                In:  Buffer size
 *                Out: Number of bytes written
 *
 * \return        E_OK
 *                Matching element returned in output parameters.
 * \return        DEM_NO_SUCH_ELEMENT
 *                No more matching elements, output parameters not modified.
 * \return        DEM_PENDING
 *                The operation was started and is currently processed.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer is not large enough.
 *
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 * \pre           A J1939 freeze frame filter has been set up by 
 *                Dem_FreezeFrameIterator_StartJ1939Iterator
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_FreezeFrameIterator_GetNextJ1939FreezeFrame(
  CONST(Dem_FreezeFrameIterator_HandleType, AUTOMATIC)    FreezeFrameIteratorId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  DestBuffer,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  BufSize 
  );
#endif

/*!
 * \}
 */
# define DEM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_FREEZEFRAMEITERATOR_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_FreezeFrameIterator_Interface.h
 *********************************************************************************************************************/
