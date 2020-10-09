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
 *  \defgroup   Dem_MemStorageManager Event Memory Storage Manager
 *  \{
 *  \file       Dem_MemStorageManager_Interface.h
 *  \brief      Control storage of additional data for DTCs based on storage/update triggers.
 *  \details    Knows depending on storage/update triggers which data to store/change.
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

#if !defined (DEM_MEMSTORAGEMANAGER_INTERFACE_H)
#define DEM_MEMSTORAGEMANAGER_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemStorageManager_Types.h"

                                                           /* Required types */
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_MemStorageManager_Properties Properties
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
 * \defgroup Dem_MemStorageManager_Private Private Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventUserERecs
 *****************************************************************************/
/*!
 * \brief         Collects the user provided extended data records stored for
 *                an event entry.
 *
 * \details       Collects the user provided extended data records stored for
 *                an event entry.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_ERECS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventUserERecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventSRecs
 *****************************************************************************/
/*!
 * \brief         Collect all user snapshot records for an event
 *
 * \details       This function will look for every snapshot record of the
 *                event that needs updating due to the status changes encoded
 *                by the trigger flags.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     UpdateFlags
 *                Trigger flags
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventSRecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  UpdateFlags
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateGlobalSRecs
 *****************************************************************************/
/*!
 * \brief         Collect all global snapshot records for an event
 *
 * \details       This function verifies if global snapshot records of an 
 *                event needs updating due to the status changes encoded
 *                by the trigger flags. If required, function updates the 
 *                record.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     UpdateFlags
 *                Trigger flags
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateGlobalSRecs(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  UpdateFlags
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventJ1939FF
 *****************************************************************************/
/*!
 * \brief         Collect J1939 Freeze Frame data stored for an event.
 *
 * \details       Collect J1939 Freeze Frame data stored for an event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_USERDATA_CHANGED    User provided data was updated.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventJ1939FF(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_SREC_OEMTRIGGER == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_TestOemSRecTrigger
 *****************************************************************************/
/*!
 * \brief         Evaluates if the snapshot data needs to be updated.
 *
 * \details       This function evaluates if the snapshot SRecIndex that can
 *                be stored in MemoryEntry is eligible for an update due to
 *                the status changes encoded by the trigger flags.
 *
 *                If the snapshot is not configured to update on OEM trigger,
 *                this function returns false.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     SRecIndex
 *                Index to the snapshot configuration
 * \param[in]     UpdateFlags
 *                Trigger flags
 *
 * \return        TRUE
 *                The snapshot needs updating
 * \return        FALSE
 *                The snapshot does not need updating
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_SREC_OEMTRIGGER == STD_ON)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemStorageManager_TestOemSRecTrigger(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_SRecIndexType, AUTOMATIC)  SRecIndex,
  CONST(uint8, AUTOMATIC)  UpdateFlags
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_TestObdIIFreezeFrameUpdates
 *****************************************************************************/
/*!
 * \brief         Test which parts of the freeze frame data need updating
 *
 * \details       This function tests if the freeze frame data must be updated,
 *                e.g. because it is not yet stored, and if the freeze frame
 *                time stamp must be updated.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     Effects
 *                Trigger flags
 * \param[in]     FreezeFrameIndex
 *                Index of the event's freeze frame
 *
 * \return        Bitcoded (ORed values)
 *                DEM_DATA_FF_UPDATE_DATA if the freeze frame data needs
 *                updating
 *                DEM_DATA_FF_UPDATE_VISIBILITY if the visibility flag needs updating
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_TestObdIIFreezeFrameUpdates(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects,
  CONST(uint8, AUTOMATIC)  FreezeFrameIndex
  );
#endif

#if (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateDAGEnvData
 *****************************************************************************/
/*!
 * \brief         Function updates the DAG relevant environmental data.
 *
 * \details       Function updates the DAG relevant environmental data when 
 *                the event is reported failed.
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           -
 * \config        (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON)
 *                || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemStorageManager_UpdateDAGEnvData(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );
#endif

/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventEntryOnTestFailed
 *****************************************************************************/
/*!
 * \brief         Function updates environmental data of an event on a Test
 *                Failed trigger.
 *
 * \details       Function updates environmental data of an event on a Test
 *                Failed trigger.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed.
 *                DEM_DATA_USERDATA_CHANGED    user provided data was updated.
 *                DEM_DATA_STATISTICS_CHANGED  internal data was updated.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnTestFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,                                                                                    
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventEntryOnTestFailedThisCycle
 *****************************************************************************/
/*!
 * \brief         Function updates environmental data of an event on a Test
 *                Failed this cycle trigger.
 *
 * \details       Function updates environmental data of an event on a Test
 *                Failed this cycle trigger.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_NO_CHANGES          nothing has changed.
 *                DEM_DATA_STATISTICS_CHANGED  internal data was updated.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateEventEntryOnTestFailedThisCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,         
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateVCCEventEntryOnTestFailed
 *****************************************************************************/
/*!
 * \brief         Function updates VCC specific environmental data of an event
 *                on a Test Failed or Test Failed this cycle trigger.
 *
 * \details       Function updates VCC specific environmental data of an event
 *                on a Test Failed or Test Failed this cycle trigger.
 *
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 * \param[in]     WIRIndicatorTriggered
 *                Indicates whether WIR indicator of the event is currently 
 *                triggered.
 *
 * \return        Block modification bitmask:
 *                DEM_DATA_STATISTICS_CHANGED  internal data was updated.
 *
 * \pre           DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON
 * \config        -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemStorageManager_UpdateVCCEventEntryOnTestFailed(   
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(boolean, AUTOMATIC)  WIRIndicatorTriggered
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
 * \defgroup Dem_MemStorageManager_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventMemoryStatistics
 *****************************************************************************/
/*!
 * \brief         Update the statistics of an an event entry.
 *
 * \details       This function updates an event memory after failure.
 *                An aged entry is reinitialized, and an active entry updates
 *                the time stamp when an occurrence was reported.
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
Dem_MemStorageManager_UpdateEventMemoryStatistics(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex,
  CONST(boolean, AUTOMATIC)  Occurrence
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemStorageManager_UpdateEventEntry
 *****************************************************************************/
/*!
 * \brief         Updates all data stored for an event.
 *
 * \details       Depending on configuration of the event data, collect the
 *                data to be updated due to the update trigger(s) in UpdateFlags.
 *                This includes statistical data (e.g. occurrence counter) as
 *                well as environment data collected from callback routines.
 *
 *                Statistical data is stored separately in the MemoryEntry and
 *                is mapped into snapshot and extended records when reading the
 *                data.
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
Dem_MemStorageManager_UpdateEventEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  UpdateFlags,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_TriggerWwhObdFreezeFrameStorage
 *****************************************************************************/
/*!
 * \brief         Initiate the storage of a WWH-OBD FreezeFrame.
 *
 * \details       If the freeze frame storage trigger is met, initiate storage 
 *                of the WWHOBD Freeze Frame.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     Effects
 *                Trigger flags
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           The event must be a WWH-OBD relevant event
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
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
Dem_MemStorageManager_TriggerWwhObdFreezeFrameStorage(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_TriggerObdIIFreezeFrameStorage
 *****************************************************************************/
/*!
 * \brief         Initiate the storage of an OBDII FreezeFrame.
 *
 * \details       If the freeze frame storage trigger is met, initiate storage 
 *                of the OBDII Freeze Frame.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     Effects
 *                Trigger flags
 *
 * \pre           The event must be an OBD relevant event
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemStorageManager_TriggerObdIIFreezeFrameStorage(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects
  );
#endif

#if (DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON)
/* ****************************************************************************
 * Dem_MemStorageManager_TestCycleCounterLatched
 *****************************************************************************/
/*!
 * \brief         Latches overflowing operation cycle counters
 *
 * \details       Latches overflowing operation cycle counters
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     CycleCount
 *                The new cycle counter
 *
 * \return        TRUE: The memory entry has been modified
 *                FALSE: The memory entry has not been modified
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_CYCLE_COUNTERS == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemStorageManager_TestCycleCounterLatched(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC)  CycleCount
  );
#endif

#if ( (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON) \
   || (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON) \
   || (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON) )
/* ****************************************************************************
 * Dem_MemStorageManager_UpdateCycleCounter
 *****************************************************************************/
/*!
 * \brief         Updates operation cycle counters, if necessary.
 *
 * \details       Function resets the consecutive failed cycles and cycles tested
 *                since first failed, if required.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     CycleStatus
 *                Cycle status changes
 *
 * \return        TRUE: The memory entry has been modified
 *                FALSE: The memory entry has not been modified
 *
 * \pre           The passed event must be a master event
 * \config        DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON ||
 *                DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON ||
 *                DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemStorageManager_UpdateCycleCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  CycleStatus
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMSTORAGEMANAGER_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemStorageManager_Interface.h
 *********************************************************************************************************************/
