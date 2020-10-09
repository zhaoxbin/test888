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
/*! \ingroup    Dem_Memory
 *  \defgroup   Dem_MemoryRestoration Memory Restoration
 *  \{
 *  \file       Dem_MemoryRestoration_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the Memory Restoration subcomponent which restores the status of a memory entry, 
 *              fixes memory entry allocation errors etc.
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

#if !defined (DEM_MEMORYRESTORATION_INTERFACE_H)
#define DEM_MEMORYRESTORATION_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryRestoration_Types.h"

/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_MemoryRestoration_Private Private Methods
 * \{
 */

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreVccStatusBits
 *****************************************************************************/
/*!
 * \brief         Restore the VCC status bits and internal status of an event.
 *
 * \details       Restore the VCC status bits and internal status of an event.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 * \param[in]     InternalStatus
 *                Current internal status of the event.
 *
 * \return        Updated value for the internal status.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_MemoryRestoration_RestoreVccStatusBits(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId,
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  );
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreStoredStatusFromEntry
 *****************************************************************************/
/*!
 * \brief         Update the aging status of an event in it's internal status.
 *
 * \details       Update the aging status of an event in it's internal status.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 * \param[in]     InternalStatus
 *                Current internal status of the event.
 *
 * \return        Updated value for the internal status.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_MemoryRestoration_RestoreStoredStatusFromEntry(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId,
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  );
#endif

#if ((DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF))
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreStatusBits_OnConfirmedStorage
 *****************************************************************************/
/*!
 * \brief         Restore parts of the UDS status, using redundant data.
 *
 * \details       Restore parts of the UDS status, using redundant data, when
 *                storage happens on confirmed.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \pre           -
 * \config        (DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON) 
 *                &&(DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnConfirmedStorage(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ((DEM_CFG_STORAGE_AT_FAILED == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF))
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreStatusBits_OnFailedStorage
 *****************************************************************************/
/*!
 * \brief         Restore parts of the UDS status, using redundant data.
 *
 * \details       Restore parts of the UDS status, using redundant data, when
 *                storage happens on failed.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \pre           -
 * \config        (DEM_CFG_STORAGE_AT_FAILED == STD_ON)
 *                && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnFailedStorage(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ((DEM_CFG_STORAGE_AT_FDC == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF))
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreStatusBits_OnFdcThresholdStorage
 *****************************************************************************/
/*!
 * \brief         Restore parts of the UDS status, using redundant data.
 *
 * \details       Restore parts of the UDS status, using redundant data, when
 *                storage happens at a FDC threshold.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \pre           -
 * \config        (DEM_CFG_STORAGE_AT_FDC == STD_ON)
 *                && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnFdcThresholdStorage(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ((DEM_CFG_STORAGE_AT_PENDING == STD_ON) && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF))
/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreStatusBits_OnPendingStorage
 *****************************************************************************/
/*!
 * \brief         Restore parts of the UDS status, using redundant data.
 *
 * \details       Restore parts of the UDS status, using redundant data, when
 *                storage happens on pending.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \pre           -
 * \config        (DEM_CFG_STORAGE_AT_PENDING == STD_ON)
 *                && (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreStatusBits_OnPendingStorage(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
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
 * \defgroup Dem_MemoryRestoration_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_MemoryRestoration_FixCorruptMemoryEntry
 *****************************************************************************/
/*!
 * \brief         Check for corrupt memory entry.
 *
 * \details       Test if a memory entry is corrupt. If so, fix it and report
 *                DET.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event memory.
 * \param[in]     MemoryIndex
 *                Memory index of the current memory entry.
 *
 * \return        TRUE
 *                Entry was corrupt - caller shall continue with next entry.
 * \return        FALSE
 *                Entry is correct.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryRestoration_FixCorruptMemoryEntry(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)    MemoryIndex
  );

/* ****************************************************************************
 * Dem_MemoryRestoration_FixDoubleAllocation
 *****************************************************************************/
/*!
 * \brief         Check for duplicate memory entry.
 *
 * \details       Test if memory entry is allocated to an event that already
 *                has a memory entry. If so, remove the duplicate.
 *
 * \param[in]     MemoryInfo
 *                Pointer to the memory descriptor for the event memory.
 * \param[in]     MemoryIndex
 *                Memory index of the current memory entry.
 *
 * \return        TRUE
 *                This memory entry was the duplicate - the caller shall
 *                continue with next entry, this one was removed.
 * \return        FALSE
 *                This entry is correct.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryRestoration_FixDoubleAllocation(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)     MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)       MemoryIndex
  );

/* ****************************************************************************
 * Dem_MemoryRestoration_RestoreEventStatus
 *****************************************************************************/
/*!
 * \brief         Restores the event status of an event
 *
 * \details       Restores the event status and internal status based on the 
 *                configured storage trigger.
 *
 * \param[in]     MemoryEntryId
 *                Memory Entry Id of the current memory entry.
 * \param[in]     EventId
 *                EventId stored at the memory index.
 *
 * \return        - 
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryRestoration_RestoreEventStatus(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)    MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC)               EventId
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMORYRESTORATION_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemoryRestoration_Interface.h
 *********************************************************************************************************************/
