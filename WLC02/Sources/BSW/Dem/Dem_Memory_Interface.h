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
 *  \defgroup   Dem_Memory Event Memory
 *  \{
 *  \file       Dem_Memory_Interface.h
 *  \brief      Abstraction for multiple event memories.
 *  \details    Facade for all memory related tasks.
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

#if !defined (DEM_MEMORY_INTERFACE_H)
#define DEM_MEMORY_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Memory_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Memory_Properties Properties
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
 * \defgroup Dem_Memory_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Memory_Init_RestoreMemory
 *****************************************************************************/
/*!
 * \brief         Test and restore corrupted primary/secondary memory.
 *
 * \details       This function verifies the integrity of memory entries and
 *                links them up into the runtime control structures.
 *
 * \param[in]     MemoryInfo
 *                Event memory descriptor.
 *
 * \pre           NvM must have restored NV mirrors.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_Init_RestoreMemory(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  );

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
 * \defgroup Dem_Memory_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Memory_FindIndex_Checked
 *****************************************************************************/
/*!
 * \brief         Finds the memory index of the event if allocated.
 *
 * \details       Finds the memory index of the event if allocated. If the event
 *                does not have a valid memory entry, any valid index is
 *                returned instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index used by the event.
 *                In error cases, a valid index is returned to avoid out of
 *                bounds memory access.
 *
 * \pre           The event must have a memory entry, i.e it is marked as
 *                'stored'.
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_FindIndex_Checked(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

#if ( (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON) \
   || (DEM_FEATURE_NEED_TIME_SERIES == STD_ON) \
   || (DEM_CFG_SUPPORT_ERECS == STD_ON) \
   || (DEM_CFG_SUPPORT_SRECS == STD_ON) \
   || (DEM_CFG_SUPPORT_WWHOBD == STD_ON) \
   || (DEM_CFG_SUPPORT_DCM == STD_ON))
/* ****************************************************************************
 * Dem_Memory_FindIndex
 *****************************************************************************/
/*!
 * \brief         Finds the memory index of the event if allocated.
 *
 * \details       Finds the memory index of the event if allocated. If the event
 *                does not have a valid memory entry, an invalid index is
 *                returned instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index used by the event.
 *                In error cases, an invalid index is returned.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON 
 *                || DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *                || (DEM_CFG_SUPPORT_ERECS == STD_ON)
 *                || (DEM_CFG_SUPPORT_SRECS == STD_ON)
 *                || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
 *                || DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_FindIndex(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

/* ****************************************************************************
 * Dem_Memory_FreeEvent
 *****************************************************************************/
/*!
 * \brief         Frees an event memory entry
 *
 * \details       This function frees an event memory entry.
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_FreeEvent(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Memory_GetFirstMemoryIndex
 *****************************************************************************/
/*!
 * \brief         Get the start memory index of a memory.
 *
 * \details       Get the start memory index of a memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 *
 * \return        Memory index of the first memory entry belonging to the memory.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_GetFirstMemoryIndex(
  CONST(uint8, AUTOMATIC)  MemoryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */


/* ****************************************************************************
 * Dem_Memory_AllocateIndex
 *****************************************************************************/
/*!
 * \brief         Selects a memory entry for an event
 *
 * \details       This function manages the event memory storage. If a free
 *                slot is available, it is returned directly. In case no free
 *                slot is available, the configured displacement algorithm is
 *                applied to free a slot.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index of the allocated event memory entry if one
 *                could be identified. DEM_MEM_INVALID_MEMORY_INDEX if no entry
 *                was allocated.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocateIndex(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if ((DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF))
/* ****************************************************************************
 * Dem_Memory_AllocateIndexAging
 *****************************************************************************/
/*!
 * \brief         Selects a memory entry for an event's aging counter
 *
 * \details       If a free memory slot is available, it is returned directly.
 *                There is no fallback in case of a filled up event memory.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index of the allocated event memory entry if one
 *                could be identified. DEM_MEM_INVALID_MEMORY_INDEX if no entry
 *                was allocated.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON 
 *                 && DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocateIndexAging(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 * Dem_Memory_GetOverflow
 *****************************************************************************/
/*!
 * \brief         Get the 'overflowed' state for an event memory.
 *
 * \details       Get the 'overflowed' state for an event memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 *
 * \return        TRUE
 *                The event memory overflowed.
 * \return        FALSE
 *                The event memory didn't overflow.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OVFLIND == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_GetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  );
#endif

/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterExists(
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * \brief         Get the event memory index derived from the iterator in 
 *                chronologial order starting with the most recent event entry.
 *
 * \details       Get the event memory index derived from the iterator in 
 *                chronologial order starting with the most recent event entry.
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Memory index derived from the iterator.
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterGet
 *****************************************************************************/
/*!
 * \brief         Get the current position of the iterator
 *
 * \details       Get the current position of the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Chrono index for the current position of the iterator.
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterGet(
  CONSTP2CONST(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterInit
 *****************************************************************************/
/*!
 * \brief         Initializes for iteration over allocated event memory entries.
 *
 * \details       Initializes for iteration over allocated event memory entries.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the event memory.
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           Memory has a chronology.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterInit(
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterResume
 *****************************************************************************/
/*!
 * \brief         Initializes for continued iteration over allocated event 
 *                memory entries.
 *
 * \details       Initializes for continued iteration over allocated event 
 *                memory entries. The previous iterator position is provided 
 *                by calling function.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the event memory.
 * \param[in]     StoredChronoIter
 *                Stored chrono iterator that shall be continued with.
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           Memory has a chronology.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterResume(
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  StoredChronoIter,
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */



/* ****************************************************************************
 * Dem_Memory_AllocMemEntriesChrono_IterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next (older) element
 *
 * \details       Move the iterator to the next (older) element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllocMemEntriesChrono_IterNext(
  CONSTP2VAR(Dem_Memory_AllocMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_AllEventMemEntries_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Memory index derived from the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterGetMemoryIndex(
  CONSTP2CONST(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_AllEventMemEntries_IterInit
 *****************************************************************************/
/*!
 * \brief         Initializes for iteration over all event memory entries.
 *
 * \details       Initializes for iteration over all event memory entries.
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterInit(
  CONSTP2VAR(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_AllEventMemEntries_IterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterNext(
  CONSTP2VAR(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_AllEventMemEntries_IterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_Memory_AllEventMemEntries_IterGetMemoryIndex() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_Memory_AllEventMemEntries_IterGetMemoryIndex() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_AllEventMemEntries_IterExists(
  CONSTP2CONST(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_MemEntry_IterGetMemoryIndex
 *****************************************************************************/
/*!
 * \brief         Get the memory index of element pointed to by the iterator
 *
 * \details       Get the memory index of element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        MemoryIndex
 *                Handle of the memory block
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_Memory_MemEntry_IterGetMemoryIndex(
  CONSTP2CONST(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */


/* ****************************************************************************
 * Dem_Memory_MemEntry_IterGetEntryId
 *****************************************************************************/
/*!
 * \brief         Get the memory entry id of element pointed to by the iterator
 *
 * \details       Get the memory entry id of element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        MemoryEntryId
 *                The memory entry handle
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_HandleType, DEM_CODE)
Dem_Memory_MemEntry_IterGetEntryId(
  CONSTP2CONST(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_MemEntry_IterInit
 *****************************************************************************/
/*!
 * \brief         Initializes for iteration over memory entries of the given memory
 *
 * \details       Initializes for iteration over memory entries of the given memory
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterInit(
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONSTP2VAR(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */


/* ****************************************************************************
 Dem_Memory_MemEntry_IterResume
 *****************************************************************************/
/*!
 * \brief         Initializes for continued iteration over memory entries.
 *
 * \details       Initializes for continued iteration over memory entries. 
 *                The previous iterator position is provided by calling function.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 * \param[in]     StoredChronoIndex
 *                Stored chrono index that shall be continued with.
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterResume(
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONSTP2VAR(Dem_Memory_MemEntryIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_MemEntry_IterNext
 *****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in,out] IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_MemEntry_IterNext(
  CONSTP2VAR(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_MemEntry_IterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_Memory_MemEntry_IterGetMemoryIndex() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_Memory_MemEntry_IterGetMemoryIndex() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_MemEntry_IterExists(
  CONSTP2CONST(Dem_Memory_AllEventMemEntriesIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Memory_GetNumAllocatedMemoryEntry
 *****************************************************************************/
/*!
 * \brief         Facade, fetch the number of allocated entries of the respective memory.
 *
 * \details       Facade, fetch the number of allocated entries of the respective memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 *
 * \return        Number of allocated entries.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_GetNumAllocatedMemoryEntry(                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryId
  );

/* ****************************************************************************
 * Dem_Memory_UpdateGetState
 *****************************************************************************/
/*!
 * \brief         Get the update state of the memory block.
 *
 * \details       Get the update state of the memory block.
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        The update state of the memory block.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_UpdateGetState(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );

/* ****************************************************************************
 * Dem_Memory_TestUpdateInProgress
 *****************************************************************************/
/*!
 * \brief         Test if an update is in progress in a memory state.
 *
 * \details       Test if an update is in progress in a memory state.
 *
 * \param[in]     MemoryState
 *                Memory update state of the memory block.
 *
 * \return        TRUE
 *                Update is in progress.
 * \return        FALSE
 *                Update is not in progress.
 *
 * \pre           -
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Memory_TestUpdateInProgress(
  CONST(uint8, AUTOMATIC)  MemoryState
  );

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 * Dem_Memory_ResetOverflow
 *****************************************************************************/
/*!
 * \brief         Clear the 'overflowed' state for the given memory.
 *
 * \details       Clear the 'overflowed' state for the given memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OVFLIND == STD_ON.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ResetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  );
#endif

/* ****************************************************************************
 * Dem_Memory_UpdateEventStatistics
 *****************************************************************************/
/*!
 * \brief         Update the statistics of an an event entry.
 *
 * \details       Update the statistics of an an event entry.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 * \param[in]     Occurrence
 *                TRUE if the TF bit has transitioned FALSE->TRUE
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *                DEM_DATA_STATISTICS_CHANGED  internal data was updated
 *
 * \pre           The event must be stored
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_UpdateEventStatistics(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(boolean, AUTOMATIC)  Occurrence
  );

/* ****************************************************************************
 * Dem_Memory_TriggerObdFreezeFrameStorage
 *****************************************************************************/
/*!
 * \brief         Initiate the storage of a OBD FreezeFrame (OBDII or WWH-OBD).
 *
 * \details       If the freeze frame storage trigger is met, initiate storage 
 *                of the OBD Freeze Frame (OBDII or WWH-OBD).
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     Effects
 *                Trigger flags
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           The event must be a OBD relevant event
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_TriggerObdFreezeFrameStorage(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );

/* ****************************************************************************
 * Dem_Memory_UpdateEventEntry
 *****************************************************************************/
/*!
 * \brief         Updates all data stored for an event.
 *
 * \details       Updates all data stored for an event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     UpdateFlags
 *                Trigger flags.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *                DEM_DATA_STATISTICS_CHANGED  internal data was updated
 *
 * \pre           The event must be stored.
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Memory_UpdateEventEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );

/* ****************************************************************************
 * Dem_Memory_UpdateEventsCycleCounter
 *****************************************************************************/
/*!
 * \brief         Update the operation cycle counter in the event memory entry.
 *
 * \details       Update the operation cycle counter in the event memory entry.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_UpdateEventsCycleCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );

#if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
/* ****************************************************************************
 * Dem_Memory_LatchCycleCounters
 *****************************************************************************/
/*!
 * \brief         Test if cycle counters need to be latched. Latch the counters 
 *                if it is required.
 *
 * \details       Test if cycle counters need to be latched. Latch the counters 
 *                if it is required.
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 * \param[in]     CycleCounter
 *                Current cycle count
 *
 * \pre           Cycle counters have already been incremented for the cycle
   \config        DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_LatchCycleCounters(
CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
CONST(uint16, AUTOMATIC)  CycleCounter
);
#endif

/* ****************************************************************************
 * Dem_Memory_GetFirstEvent
 *****************************************************************************/
/*!
 * \brief         Get the first event mapped to the given memory.
 *
 * \details       Get the first event mapped to the given memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 *
 * \return        Unique handle of the event.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Memory_GetFirstEvent(
  CONST(uint8, AUTOMATIC)  MemoryId
  );

/* ****************************************************************************
 * Dem_Memory_GetLastEvent
 *****************************************************************************/
/*!
 * \brief         Get the last event mapped to the given memory.
 *
 * \details       Get the last event mapped to the given memory.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the memory.
 *
 * \return        Unique handle of the event.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Memory_GetLastEvent(
  CONST(uint8, AUTOMATIC)  MemoryId
  );

/* ****************************************************************************
 * Dem_Memory_Init
 *****************************************************************************/
/*!
 * \brief         Initializes backing memory
 *
 * \details       This function controls initialization of the memory
 *                subcomponent. After the function completes, event memories
 *                are available.
 *
 * \pre           May only be called during initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_Init(
  void
  );

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Memory_InitConfirmedChronology
 *****************************************************************************/
/*!
 * \brief         Initialize confirmed chronology
 *
 * \details       Initialize confimred chronology
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_InitConfirmedChronology(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Memory_ConfirmedChronologyResetOverflown
 *****************************************************************************/
/*!
 * \brief         Reset overflow state of confirmed chronology
 *
 * \details       Reset overflow state of confirmed chronology
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronologyResetOverflown(
  void
  );
#endif


#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Memory_ConfirmedChronoAddEvent
 *****************************************************************************/
/*!
 * \brief         Add an confirmed event to confirmed chronology
 *
 * \details       Add an confirmed event to confirmed chronology.
 *
 * \param[in]     MasterEventId
 *                Unique handle of the DTC.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronoAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  MasterEventId
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Memory_PermanentFillUp
 *****************************************************************************/
/*!
 * \brief         Fillup permanent memory and confirmed chronology.
 *
 * \details       Fillup permanent memory and confirmed chronology.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Memory_PermanentFillUp(void);
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Memory_ConfirmedChronoFreeEvent
 *****************************************************************************/
/*!
 * \brief         Frees the entry in confirmed chronology for the event
 *
 * \details       Frees the entry in confirmed chronology for the event
 *
 * \param[in]     ConfirmedChronologyIndex
 *                Index in Dem_Cfg_StatusData.ConfirmedChronology[]
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Memory_ConfirmedChronoFreeEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMORY_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Memory_Interface.h
 *********************************************************************************************************************/
