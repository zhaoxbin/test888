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
/*! \ingroup    Dem_MemoryEntry
 *  \defgroup   Dem_SnapshotEntry SnapshotEntry
 *  \{
 *  \file       Dem_SnapshotEntry_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Encapsulates the list of snapshot record buffers stored in the memory entry
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

#if !defined (DEM_SNAPSHOTENTRY_INTERFACE_H)
#define DEM_SNAPSHOTENTRY_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_SnapshotEntry_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_SnapshotEntry_Properties Properties
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
 * \defgroup Dem_SnapshotEntry_Private Private Methods
 * \{
 */

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
 * \defgroup Dem_SnapshotEntry_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorInit
 *****************************************************************************/
/*!
 * \brief         Initializes the snapshot entry iterator
 *
 * \details       Initializes the iterator to enumerate snapshot entries in 
 *                an memory entry
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[out]    SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *                || DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONSTP2VAR(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorNext
 *****************************************************************************/
/*!
 * \brief         Move the snapshot entry iterator to the next element
 *
 * \details       Move the snapshot entry iterator to the next element
 *
 * \param[in,out] SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \pre           SnapshotEntryIter has been initialized
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorNext(
  CONSTP2VAR(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorExists
 *****************************************************************************/
/*!
 * \brief         Test if the snapshot entry iterator points to a valid element
 *
 * \details       Test if the snapshot entry iterator points to a valid element
 *
 * \param[in]     SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \return        TRUE
 *                SnapshotEntryIter points to a valid element
 * \return        FALSE
 *                SnapshotEntryIter doesn't point to a valid element
 *
 * \pre           SnapshotEntryIter has been initialized
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SnapshotEntry_IteratorExists(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) */

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorGetMemoryEntryHandle
 *****************************************************************************/
/*!
 * \brief         Get the memory entry handle 
 *
 * \details       Get the memory entry handle  pointed to by the iterator
 *
 * \param[in]     SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \return        The memory entry handle
 *
 * \pre           SnapshotEntryIter has been initialized
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *                || DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_HandleType, DEM_CODE)
Dem_SnapshotEntry_IteratorGetMemoryEntryHandle(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );
#endif /* (DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) */

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorGetSnapshotRecordIndex
 *****************************************************************************/
/*!
 * \brief         Get the snapshot record index 
 *
 * \details       Get the snapshot record index pointed to by the iterator
 *
 * \param[in]     SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \return        Handle to the snapshot record descriptor table
 *
 * \pre           SnapshotEntryIter has been initialized
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_SRecIndexType, DEM_CODE)
Dem_SnapshotEntry_IteratorGetSnapshotRecordIndex(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );
#endif

#if ((DEM_CFG_SUPPORT_SRECS == STD_ON) && \
     ((DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON) || \
      ((DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))))
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorGetSnapshotEntryIndex
 *****************************************************************************/
/*!
 * \brief         Get the snapshot record index 
 *
 * \details       Get the snapshot record index pointed to by the iterator
 *
 * \param[in]     SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \return        Index of the snapshot data buffer in the memory entry
 *
 * \pre           SnapshotEntryIter has been initialized
 * \config        ((DEM_CFG_SUPPORT_SRECS == STD_ON) && \
 *                 ((DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON) || \
 *                  ((DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON))))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_SnapshotEntry_IteratorGetSnapshotEntryIndex(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorGetSnapshotRecordDataConstPtr
 *****************************************************************************/
/*!
 * \brief         Get the snapshot data buffer
 *
 * \details       Get the snapshot data buffer at the index pointed to by the 
 *                iterator
 *
 * \param[in]     SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \return        Pointer to the unmodifiable (const) snapshot data buffer
 *
 * \pre           SnapshotEntryIter has been initialized
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_SnapshotEntry_IteratorGetSnapshotRecordDataConstPtr(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorIsSnapshotRecordStored
 *****************************************************************************/
/*!
 * \brief         Tests whether a snapshot record is currently stored
 *
 * \details       Tests whether a snapshot record pointed to by the iterator 
 *                is currently stored
 *
 * \param[in]     SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \return        TRUE
 *                The snapshot record is stored
 * \return        FALSE
 *                The snapshot record is not stored
 *
 * \pre           SnapshotEntryIter->MemoryEntryId must be inside valid range
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_SnapshotEntry_IteratorIsSnapshotRecordStored(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorUpdateSnapshotEntry
 *****************************************************************************/
/*!
 * \brief         Set the 'stored' flag for a snapshot entry
 *
 * \details       If configured records are used, set the corresponding bit in
 *                the SnapshotHeader of the memory entry.
 *                If calculated records are used, increment the SnapshotHeader
 *                value of the memory entry.
 *
 * \param[in]     SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \pre           SnapshotEntryIter->MemoryEntryId must be inside valid range
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorUpdateSnapshotEntry(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorCopySnapshotEntry
 *****************************************************************************/
/*!
 * \brief         Copy the snapshot entry at the given index to the given 
 *                snapshot entry
 *
 * \details       Copy the snapshot entry at the given index to the snapshot 
 *                entry pointed to by the iterator
 *
 * \param[in]     SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 * \param[in]     EntryIndex
 *                Index of the snapshot entry to be copied
 *
 * \pre           SnapshotEntryIter->MemoryEntryId and EntryIndex must be
 *                inside valid range
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS_CONFIGURED == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorCopySnapshotEntry(
  CONSTP2CONST(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter,
  CONST(uint8, AUTOMATIC)  EntryIndex
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON) && (DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorFindLastStoredEntry
 *****************************************************************************/
/*!
 * \brief         Move the snapshot entry iterator to the index of the last 
 *                stored snapshot entry.
 *
 * \details       Move the snapshot entry iterator to the index of the last 
 *                stored snapshot entry. The snapshot entry pointer always 
 *                points to a valid snapshot entry afterwards.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[out]    SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \pre           SnapshotEntryIter->MemoryEntryId must be inside valid range
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS_CALCULATED == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorFindLastStoredEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONSTP2VAR(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorFindEntryWithRecordNumber
 *****************************************************************************/
/*!
 * \brief         Move the snapshot entry iterator to the index of the
 *                snapshot entry with requested record number.
 *
 * \details       Move the snapshot entry iterator to the index of the snapshot 
 *                entry with requested record number. The snapshot entry pointer 
 *                always points to a valid snapshot entry afterwards.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     RecordNumber
 *                Snapshot record number.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[out]    SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \pre           SnapshotEntryIter->MemoryEntryId must be inside valid range
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SnapshotEntry_IteratorFindEntryWithRecordNumber(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  RecordNumber,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONSTP2VAR(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_IteratorSetNextStoredEntry
 *****************************************************************************/
/*!
 * \brief         Move the snapshot entry iterator to the index of the next
 *                stored snapshot entry.
 *
 * \details       Move the snapshot entry iterator to the index of the next 
 *                stored snapshot entry. The iterator only points to the index
 *                of a valid and stored entry, if the function returns TRUE.
 *
 * \param[out]    SnapshotEntryIter
 *                Pointer to the snapshot entry iterator
 *
 * \return        TRUE
 *                SnapshotEntryIter points to the index of a stored entry.
 *                FALSE
 *                No stored entry was found. 
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SnapshotEntry_IteratorSetNextStoredEntry(
  CONSTP2VAR(Dem_SnapshotEntry_IterType, AUTOMATIC, AUTOMATIC)  SnapshotEntryIter
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_SnapshotEntry_GetNumberOfStoredSnapshotRecords
 *****************************************************************************/
/*!
 * \brief         Counts the number of snapshot records stored in a memory
 *                entry
 *
 * \details       Counts the number of snapshot records stored in a memory
 *                entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The number of stored snapshot records
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON &&
 *                DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_SnapshotEntry_GetNumberOfStoredSnapshotRecords(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_SNAPSHOTENTRY_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SnapshotEntry_Interface.h
 *********************************************************************************************************************/
