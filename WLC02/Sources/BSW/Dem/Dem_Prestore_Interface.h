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
 *  \defgroup   Dem_Prestore Prestore
 *  \{
 *  \file       Dem_Prestore_Interface.h
 *  \brief      Stores and manages 'prestored freezeframes'.
 *  \details    Pre-store snapshot data for an event, in order to freeze that data set when the event is stored later.
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

#if !defined (DEM_PRESTORE_INTERFACE_H)
#define DEM_PRESTORE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Prestore_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Prestore_Properties Properties
 * \{
 */

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_GetLockedIndex
 *****************************************************************************/
/*!
 * \brief         Get the LockedIndex value.
 *
 * \details       Get the LockedIndex value.
 *
 * \return        LockedIndex value.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_GetLockedIndex(
  void
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetGlobalSRecDataPtr
 *****************************************************************************/
/*!
 * \brief         Get data buffer for global snapshot record data of a prestored
 *                entry.
 *
 * \details       Get data buffer for global snapshot record data of a prestored
 *                entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Address of the data buffer.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
 *                && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetGlobalSRecDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetSRecDataPtr
 *****************************************************************************/
/*!
 * \brief         Get data buffer for UDS snapshot record data of a prestored
 *                entry.
 *
 * \details       Get data buffer for UDS snapshot record data of a prestored
 *                entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Address of the data buffer.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
 *                && (DEM_CFG_SUPPORT_SRECS == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetSRecDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetObdIIFFDataPtr
 *****************************************************************************/
/*!
 * \brief         Get data buffer for OBD freeze frame data of a prestored
 *                entry.
 *
 * \details       Get data buffer for OBD freeze frame data of a prestored
 *                entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Address of the data buffer.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
 *                && (DEM_CFG_SUPPORT_OBDII == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetObdIIFFDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && ((DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON) || (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON))
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetJ1939FFDataPtr
 *****************************************************************************/
/*!
 * \brief         Get data buffer for J1939 freeze frame data of a prestored
 *                entry.
 *
 * \details       Get data buffer for J1939 freeze frame data of a prestored
 *                entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Address of the data buffer.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
 *                && ( (DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON)
 *                  || (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON))
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetJ1939FFDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetWwhObdFFDataPtr
 *****************************************************************************/
/*!
 * \brief         Get data buffer for WWH-OBD freeze frame data of a prestored
 *                entry.
 *
 * \details       Get data buffer for WWH-OBD freeze frame data of a prestored
 *                entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Address of the data buffer.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
 *                && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DataPtrType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetWwhObdFFDataPtr(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

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
 * \defgroup Dem_Prestore_Private Private Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntry_Checked
 *****************************************************************************/
/*!
 * \brief         Check position 'PrestorageEntry' for being a valid index.
 *
 * \details       If run-time checks are enabled, check index 'PrestorageEntry'. 
 *                When the check fails, return the 'invalid' prestorage entry
 *                that points to an existing temporary buffer element.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Without runtime checks: argument 'PrestorageEntry'.
 * \return        With runtime checks: 'PrestorageEntry' for valid positions,
 *                otherwise DEM_PRESTORE_INVALID_BUFFER_ENTRY (which is the
 *                position of the temporary buffer element).
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_PrestorageEntry_Checked(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC) PrestorageEntry
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetEventId
 *****************************************************************************/
/*!
 * \brief         Get the EventId of a prestored entry.
 *
 * \details       Get the EventId of a prestored entry. The requested entry
 *                must be allocated and not be part of the free list.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        EventId that has set this prestored entry.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Prestore_PrestorageEntryGetEventId(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntrySetEventId
 *****************************************************************************/
/*!
 * \brief         Set the EventId of a prestored entry.
 *
 * \details       Set EventId of a prestored entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 * \param[in]     EventId
 *                New EventId for the entry.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_PrestorageEntrySetEventId(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_FreeListGetNext
 *****************************************************************************/
/*!
 * \brief         Get the next prestorage entry from the list of free buffers.
 *
 * \details       Get the immediate following entry from the linked list of
 *                free buffers.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        Next prestored entry.
 * \return        DEM_PRESTORE_INVALID_BUFFER_ENTRY
 *                No next prestorage entry.
 *
 * \pre           'PrestorageEntry' is part of the free list.
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_FreeListGetNext(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_FreeListSetNext
 *****************************************************************************/
/*!
 * \brief         Set the 'next' prestorage entry (for list of free buffers).
 *
 * \details       Set the 'PrestorageEntry' to link to the
 *                'NextPrestorageEntry'. This inserts this entry in the list of
 *                free buffers.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 * \param[in]     NextPrestorageEntry
 *                Next free prestorage entry after 'PrestorageEntry'. Use
 *                DEM_PRESTORE_INVALID_BUFFER_ENTRY for no-next-element.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_FreeListSetNext(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry,
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  NextPrestorageEntry
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryGetState
 *****************************************************************************/
/*!
 * \brief         Get the state of a prestored entry.
 *
 * \details       Get the state of a prestored entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 *
 * \return        DEM_PRESTORE_STATUS_FREE
 *                Prestored entry is free.
 * \return        DEM_PRESTORE_STATUS_READY
 *                Prestored entry contains valid data.
 * \return        DEM_PRESTORE_STATUS_UPDATING
 *                Prestored entry is updating data.
 * \return        DEM_PRESTORE_STATUS_LOCKED
 *                Prestored entry is locked.
 * \return        DEM_PRESTORE_STATUS_DISCARDED
 *                Prestored entry needs to be freed.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Prestore_PrestorageEntryGetState(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntrySetState
 *****************************************************************************/
/*!
 * \brief         Set the state of a prestored entry.
 *
 * \details       Set state of a prestored entry.
 *
 * \param[in]     PrestorageEntry
 *                Position of a prestorage entry.
 * \param[in]     State
 *                New state for the entry.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_PrestorageEntrySetState(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry,
  CONST(uint8, AUTOMATIC)  State
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_SetPrestorageEntry
 *****************************************************************************/
/*!
 * \brief         Set the prestorage buffer slot, allocated to the event.
 *
 * \details       Set the prestorage buffer, that is allocated to the event.
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     PrestorageEntry
 *                Prestorage buffer slot (currently) allocated to the event.
 *                DEM_PRESTORE_INVALID_BUFFER_ENTRY is '(currently) no buffer'.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_SetPrestorageEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_PrestorageEntryUpdate
 *****************************************************************************/
/*!
 * \brief         Samples all event related data into a prestorage entry
 *
 * \details       Samples all event related data into a prestorage entry
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     PrestorageEntry
 *                Position of the prestorage entry.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_PrestorageEntryUpdate(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_GetPrestorageEntry
 *****************************************************************************/
/*!
 * \brief         Locates the prestored data entry of an event.
 *
 * \details       This function looks up the prestorage entry for the given
 *                event, and returns its handle (position in buffer).
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *                The event must have configured prestorage.
 *
 * \return        Position in Prestorage buffer.
 *
 * \pre           The event must support prestorage, always proove that before
 *                by calling Dem_Cfg_EventPrestorageIndex(EventId). If run-time
 *                checks are enabled, a violation of this precondition will
 *                return DEM_PRESTORE_INVALID_BUFFER_ENTRY.
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_GetPrestorageEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_AllocatePrestorageEntry
 *****************************************************************************/
/*!
 * \brief         Allocates a new prestored entry for an event
 *
 * \details       This function consumes the next free prestorage entry (if
 *                available) and allocates it to the given event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Index into Prestorage area, if one was found.
 *                DEM_PRESTORE_INVALID_BUFFER_ENTRY otherwise.
 *
 * \pre           The event must support prestorage
 * \pre           The event must not have a prestored entry
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_PrestorageIndexType, DEM_CODE)
Dem_Prestore_AllocatePrestorageEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_FreePrestorageEntry
 *****************************************************************************/
/*!
 * \brief         Free a prestored entry
 *
 * \details       This function removes the ownership of the prestored entry
 *                buffer and returns it to the free list.
 *
 * \param[in]     PrestorageEntry
 *                Prestored entry to free
 *
 * \pre           Must be called within critical section 'DiagMonitor'
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_FreePrestorageEntry(
  CONST(Dem_Cfg_PrestorageIndexType, AUTOMATIC)  PrestorageEntry
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_EventPrestorageUpdate
 *****************************************************************************/
/*!
 * \brief         Store prestored data for an event
 *
 * \details       This function tries to find a prestorage entry for the given
 *                event, allocating a new one if needed.
 *                If a prestorage entry is found, it is updated with sample
 *                data.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        E_OK
 *                Prestored data was successfully collected
 * \return        E_NOT_OK
 *                No data was collected
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventPrestorageUpdate(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_Prestore_ProcessSatelliteQueueActions
 *****************************************************************************/
/*!
 * \brief         Processes all queued prestore actions.
 *
 * \details       This function processes queued prestore actions for all
 *                events of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Unique handle of the Satellite.
 *                The SatelliteId must be in range [1..Dem_Cfg_GlobalSatelliteCount()[.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_ProcessSatelliteQueueActions(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
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
 * \defgroup Dem_Prestore_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the prestorage free list.
 *
 * \details       Initializes the prestorage free list.
 *
 * \pre           Can only be called during Dem initialization
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_Init(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_StateSetDiscard
 *****************************************************************************/
/*!
 * \brief         Marks a prestored entry as used up
 *
 * \details       Prestored data (if available) is valid throughout the whole
 *                event processing step. This function marks the current data
 *                to be discarded after event processing completes.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_StateSetDiscard(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_EventPrestorageLock
 *****************************************************************************/
/*!
 * \brief         Locks a ready prestored entry to use its data
 *
 * \details       This function prepares the prestored data of the given event
 *                (if available) for consumption during the event processing
 *                step.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Must be called within critical section 'DiagMonitor'
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_EventPrestorageLock(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_EventPrestorageRelease
 *****************************************************************************/
/*!
 * \brief         Unlock the previously locked prestored entry
 *
 * \details       This function releases the prestored data locked by
 *                Dem_Prestore_EventPrestorageLock, if such data exists.
 *
 *                If the data was consumed during the event processing step,
 *                the data is discarded.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_EventPrestorageRelease(
  void
  );
#endif

/* ****************************************************************************
 * Dem_Prestore_EventPrestorageClear
 *****************************************************************************/
/*!
 * \brief         Clears the prestorage entry of an event
 *
 * \details       Clears the prestorage entry of an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        E_OK
 *                The data was cleared successfully
 * \return        E_NOT_OK
 *                The data was not cleared, e.g. no data was available
 *
 * \pre           Must be called within critical section 'DiagMonitor'
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventPrestorageClear(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_EventPrestoreFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Trigger prestoring freeze frame data for an event
 *
 * \details       Trigger prestoring freeze frame data for an event if
 *                preconditions are fulfilled.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        E_OK
 *                The data was collected successfully (if processed synchronously).
 *                Prestore freeze frame request accepted (if processed asynchronously).
 *
 * \return        E_NOT_OK
 *                No data was collected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventPrestoreFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_Prestore_EventClearPrestoredFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Trigger clearing the prestored freeze frame data for an event
 *
 * \details       Trigger clearing the prestored freeze frame data for an event
 *                if preconditions are fulfilled.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        E_OK
 *                Prestore data cleared (if processed synchronously).
 *                Clear prestore data request accepted (if processed asynchronously).
 *
 * \return        E_NOT_OK
 *                No data was cleared, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Prestore_EventClearPrestoredFreezeFrame(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_Prestore_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process queued prestorage operations
 *
 * \details       Process queued prestorage operations
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Prestore_MainFunction(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_PRESTORE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Prestore_Interface.h
 *********************************************************************************************************************/
