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
 *  \defgroup   Dem_MemoryEntry Event Memory Entry
 *  \{
 *  \file       Dem_MemoryEntry_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Encapsulates the Memory entry and known data stored in the memory entry
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

#if !defined (DEM_MEMORYENTRY_INTERFACE_H)
#define DEM_MEMORYENTRY_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryEntry_Types.h"
#include "Dem_Data_Types.h"
#include "Dem_OperationCycle_Types.h"

/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_MemoryEntry_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_MemoryEntry_GetEventId
 *****************************************************************************/
/*!
 * \brief         Get the Event Id of the memory entry
 *
 * \details       Get the Event Id of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The Event Id of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemoryEntry_GetEventId(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetEventId
 *****************************************************************************/
/*!
 * \brief         Set the event Id in the memory entry
 *
 * \details       Set the event Id in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     EventId
 *                The event Id to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetEventId(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetTimestamp
 *****************************************************************************/
/*!
 * \brief         Get the timestamp of the memory entry
 *
 * \details       Get the timestamp of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The timestamp of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemoryEntry_GetTimestamp(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetTimestamp
 *****************************************************************************/
/*!
 * \brief         Set the timestamp in the memory entry
 *
 * \details       Set the timestamp in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     Timestamp
 *                The timestamp to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetTimestamp(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint32, AUTOMATIC) Timestamp
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Get the maximum debounce value of the memory entry
 *
 * \details       Get the maximum debounce value of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The maximum debounce value of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_MemoryEntry_GetDebounceValueMax(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Set the maximum debounce value in the memory entry
 *
 * \details       Set the maximum debounce value in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     MaxDebounceValue
 *                The maximum debounce value to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetDebounceValueMax(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(sint16, AUTOMATIC) MaxDebounceValue
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetState
 *****************************************************************************/
/*!
 * \brief         Get the state of the memory entry
 *
 * \details       Get the state of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The state of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetState(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetState
 *****************************************************************************/
/*!
 * \brief         Set the state in the memory entry
 *
 * \details       Set the state in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     State
 *                The state to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetState(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) State
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Get the aging counter of the memory entry
 *
 * \details       Get the aging counter of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The aging counter of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetAgingCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Set the aging counter in the memory entry
 *
 * \details       Set the aging counter in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     AgingCounter
 *                The aging counter to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetAgingCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC) AgingCounter
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetAgingTimer
 *****************************************************************************/
/*!
 * \brief         Get the aging timer of the memory entry
 *
 * \details       Get the aging timer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The aging timer of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemoryEntry_GetAgingTimer(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetAgingTimer
 *****************************************************************************/
/*!
 * \brief         Set the aging timer in the memory entry
 *
 * \details       Set the aging timer in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     AgingTimer
 *                The aging timer to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetAgingTimer(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint32, AUTOMATIC) AgingTimer
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter1Byte
 *****************************************************************************/
/*!
 * \brief         Get the 1 byte occurrence counter of the memory entry
 *
 * \details       Get the 1 byte occurrence counter of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 1 byte occurrence counter of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter1Byte(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter2Byte
 *****************************************************************************/
/*!
 * \brief         Get the 2 byte occurrence counter of the memory entry
 *
 * \details       Get the 2 byte occurrence counter of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 2 byte occurrence counter of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter2Byte(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter in the memory entry
 *
 * \details       Set the occurrence counter in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter
 *                The occurrence counter to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_MemoryEntry_OccurrenceCounterType, AUTOMATIC) OccurrenceCounter
  );


/* ****************************************************************************
 * Dem_MemoryEntry_ResetOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Reset the occurrence counter in the memory entry
 *
 * \details       Reset the occurrence counter in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_ResetOccurrenceCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Get the 'Failed Cycle Counter' of the memory entry
 *
 * \details       Get the 'Failed Cycle Counter' of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The'Failed Cycle Counter' of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetFailedCycleCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Set the 'Failed Cycle Counter' in the memory entry
 *
 * \details       Set the 'Failed Cycle Counter' in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     FailedCycleCounter
 *                The 'Failed Cycle Counter' to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetFailedCycleCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) FailedCycleCounter
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetConsecutiveFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Get the 'Consecutive Failed Cycle Counter' of the memory 
 *                entry
 *
 * \details       Get the 'Consecutive Failed Cycle Counter' of the memory 
 *                entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 'Consecutive Failed Cycle Counter' of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetConsecutiveFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Set the 'Consecutive Failed Cycle Counter' in the memory 
 *                entry
 *
 * \details       Set the 'Consecutive Failed Cycle Counter' in the memory 
 *                entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     ConsecutiveFailedCycleCounter
 *                The 'Consecutive Failed Cycle Counter' to be set in the 
 *                memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetConsecutiveFailedCycleCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) ConsecutiveFailedCycleCounter
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Get the 'Cycles Since First Failed' of the memory entry
 *
 * \details       Get the 'Cycles Since First Failed' of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 'Cycles Since First Failed' of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetCyclesSinceFirstFailed(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Set the 'Cycles Since First Failed' in the memory entry
 *
 * \details       Set the 'Cycles Since First Failed' in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     CyclesSinceFirstFailed
 *                The 'Cycles Since First Failed' to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetCyclesSinceFirstFailed(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC) CyclesSinceFirstFailed
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetTestedCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Get the 'Tested Cycles Since First Failed' of the memory 
 *                entry
 *
 * \details       Get the 'Tested Cycles Since First Failed' of the memory 
 *                entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 'Tested Cycles Since First Failed' of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetTestedCyclesSinceFirstFailed(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetTestedCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Set the 'Tested Cycles Since First Failed' in the memory 
 *                entry
 *
 * \details       Set the 'Tested Cycles Since First Failed' in the memory 
 *                entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     TestedCyclesSinceFirstFailed
 *                The 'Tested Cycles Since First Failed' to be set in the 
 *                memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetTestedCyclesSinceFirstFailed(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) TestedCyclesSinceFirstFailed
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Get the 'Cycles Since Last Failed' of the memory entry
 *
 * \details       Get the 'Cycles Since Last Failed' of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The 'Cycles Since Last Failed' of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemoryEntry_GetCyclesSinceLastFailed(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Set the 'Cycles Since Last Failed' in the memory entry
 *
 * \details       Set the 'Cycles Since Last Failed' in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     CyclesSinceLastFailed
 *                The 'Cycles Since Last Failed' to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetCyclesSinceLastFailed(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint16, AUTOMATIC) CyclesSinceLastFailed
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetPreConfirmedStatus
 *****************************************************************************/
/*!
 * \brief         Get the preconfirmed status of the memory entry
 *
 * \details       Get the preconfirmed status of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The preconfirmed status of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetPreConfirmedStatus(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetPreConfirmedStatus
 *****************************************************************************/
/*!
 * \brief         Set the preconfirmed status in the memory entry
 *
 * \details       Set the preconfirmed status in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     StatusIndicator
 *                The preconfirmed status to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetPreConfirmedStatus(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) StatusIndicator
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter1
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter #1 of the memory entry
 *
 * \details       Get the occurrence counter #1 of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter #1 of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter1(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter1
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter #1 in the memory entry
 *
 * \details       Set the occurrence counter #1 in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter1
 *                The occurrence counter #1 to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter1(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter1
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter2
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter #2 of the memory entry
 *
 * \details       Get the occurrence counter #2 of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter #2 of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter2(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter2
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter #2 in the memory entry
 *
 * \details       Set the occurrence counter #2 in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter2
 *                The occurrence counter #2 to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter2(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter2
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter3
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter #3 of the memory entry
 *
 * \details       Get the occurrence counter #3 of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter #3 of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter3(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter3
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter #3 in the memory entry
 *
 * \details       Set the occurrence counter #3 in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter3
 *                The occurrence counter #3 to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter3(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter3
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter4
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter #4 of the memory entry
 *
 * \details       Get the occurrence counter #4 of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter #4 of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter4(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter4
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter #4 in the memory entry
 *
 * \details       Set the occurrence counter #4 in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter4
 *                The occurrence counter #4 to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter4(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter4
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter7
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter #7 of the memory entry
 *
 * \details       Get the occurrence counter #7 of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter #7 of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter7(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_SetOccurrenceCounter7
 *****************************************************************************/
/*!
 * \brief         Set the occurrence counter #7 in the memory entry
 *
 * \details       Set the occurrence counter #7 in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     OccurrenceCounter7
 *                The occurrence counter #7 to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetOccurrenceCounter7(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) OccurrenceCounter7
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_GetStdEnvData
 *****************************************************************************/
/*!
 * \brief         Get the requested data element of the standard environmental 
 *                data of the memory entry
 *
 * \details       Get the requested data element of the standard environmental 
 *                data of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     DataIndex
 *                The index of the standard environmental data
 *
 * \return        The requested data element of the standard environmental 
 *                data of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetStdEnvData(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  DataIndex
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetStdEnvData
 *****************************************************************************/
/*!
 * \brief         Set the requested data element of the standard environmental 
 *                data in the memory entry
 *
 * \details       Set the requested data element of the standard environmental 
 *                data in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     DataIndex
 *                The index of the standard environmental data element
 * \param[in]     DataValue
 *                The data value to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetStdEnvData(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  DataIndex,
  CONST(uint8, AUTOMATIC)  DataValue
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetSnapshotHeader
 *****************************************************************************/
/*!
 * \brief         Get the snapshot header of the memory entry
 *
 * \details       Get the snapshot header of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The snapshot header of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetSnapshotHeader(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetSnapshotHeader
 *****************************************************************************/
 /*!
 * \brief         Set the snapshot header in the memory entry
 *
 * \details       Set the snapshot header in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     SnapshotHeader
 *                The snapshot header to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetSnapshotHeader(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) SnapshotHeader
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetExtendedHeader
 *****************************************************************************/
/*!
 * \brief         Get the extended header of the memory entry
 *
 * \details       Get the extended header of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The extended header of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemoryEntry_GetExtendedHeader(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetExtendedHeader
 *****************************************************************************/
/*!
 * \brief         Set the extended header in the memory entry
 *
 * \details       Set the extended header in the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     ExtendedHeader
 *                The extended header to be set in the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetExtendedHeader(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC) ExtendedHeader
  );

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetSnapshotRecordDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the indexed snapshot data buffer of the memory entry
 *
 * \details       Get the indexed snapshot data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     SRecIndex
 *                Index of the snapshot data record
 *
 * \return        Pointer to the indexed snapshot data buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetSnapshotRecordDataPtr(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  SRecIndex
  );
#endif

#if (DEM_CFG_SUPPORT_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetSnapshotRecordDataConstPtr
 *****************************************************************************/
 /*!
 * \brief         Get the indexed snapshot data buffer of the memory entry
 *
 * \details       Get the indexed snapshot data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     SRecIndex
 *                Index of the snapshot data record
 *
 * \return        Pointer to the unmodifiable (const) indexed snapshot data
 *                buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetSnapshotRecordDataConstPtr(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(Dem_Cfg_SRecIndexType, AUTOMATIC)  SRecIndex
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetExtendedRecordDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the indexed extended data buffer of the memory entry
 *
 * \details       Get the indexed extended data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     ERecIndex
 *                Index of the extended data record
 *
 * \return        Pointer to the indexed extended data buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetExtendedRecordDataPtr(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ERecIndex
  );
#endif

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetExtendedRecordDataConstPtr
 *****************************************************************************/
/*!
 * \brief         Get the indexed extended data buffer of the memory entry
 *
 * \details       Get the indexed extended data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 * \param[in]     ERecIndex
 *                Index of the extended data record
 *
 * \return        Pointer to the unmodifiable (const) indexed extended data
 *                buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_ERECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetExtendedRecordDataConstPtr(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ERecIndex
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetWwhObdFreezeFrameDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the WWH-OBD freeze frame data buffer of the memory entry
 *
 * \details       Get the WWH-OBD freeze frame data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Pointer to the WWH-OBD freeze frame data buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetWwhObdFreezeFrameDataPtr(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON) || (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetJ1939FreezeFramePtr
 *****************************************************************************/
/*!
 * \brief         Get the J1939 freeze frame data buffer of the memory entry
 *
 * \details       Get the J1939 freeze frame data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Pointer to the J1939 freeze frame data buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON ||
 *                DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetJ1939FreezeFramePtr(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr
 *****************************************************************************/
/*!
 * \brief         Get the global snapshot record data buffer of the memory entry
 *
 * \details       Get the global snapshot record data buffer of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        Pointer to the global snapshot record data buffer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedDataPtrType, DEM_CODE)
Dem_MemoryEntry_GetGlobalSnapshotRecordDataPtr(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );
#endif

/* ****************************************************************************
 * Dem_MemoryEntry_TestGlobalSnapshotRecordStored
 *****************************************************************************/
/*!
 * \brief         Checks whether the global snapshot record of the event in 
 *                memory is stored.
 *
 * \details       Checks whether the global snapshot record of the event in 
 *                memory is stored.
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 *
 * \return        TRUE
 *                Global snapshot record is stored.
 * \return        FALSE
 *                Otherwise
 *                
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_TestGlobalSnapshotRecordStored(                                                                                  
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_SetGlobalSnapshotRecordStored
 *****************************************************************************/
/*!
 * \brief         Sets the global snapshot record stored state of an event in 
 *                memory.
 *
 * \details       Sets the global snapshot record stored state of an event in 
 *                memory.
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 * \param[in]     StoredState
 *                The global snapshot record stored state.                
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_SetGlobalSnapshotRecordStored(                                                                                   
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(boolean, AUTOMATIC) StoredState
  );

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
 * \defgroup Dem_MemoryEntry_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_MemoryEntry_GetEntry
 *****************************************************************************/
/*!
 * \brief         Get the N-th memory entry
 *
 * \details       Get the N-th memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle selects the index 'N'
 *
 * \return        Pointer to the N-th memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SharedMemoryEntryPtrType, DEM_CODE)
Dem_MemoryEntry_GetEntry(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
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
 * \defgroup Dem_MemoryEntry_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_TestGlobalSnapshotStored
 *****************************************************************************/
/*!
 * \brief         Test if global snapshot is stored in memory entry
 *
 * \details       Test if global snapshot is stored in memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        TRUE, global snapshot stored
 *                FALSE, global snapshot not stored
 *
 * \pre           -
   \config        DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_TestGlobalSnapshotStored(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

/* ****************************************************************************
 * Dem_MemoryEntry_GetOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Get the occurrence counter of the memory entry
 *
 * \details       Get the occurrence counter of the memory entry
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        The occurrence counter of the memory entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_OccurrenceCounterType, DEM_CODE)
Dem_MemoryEntry_GetOccurrenceCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemoryEntry_Init
 *****************************************************************************/
/*!
  * \brief         Initializes the memory entry
  *
  * \details       Initializes the memory entry
  *
  * \param[in]     MemoryEntryId
  *                The memory entry handle
  *
  * \pre           -
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE
  *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_Init(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
* Dem_MemoryEntry_CopyEntry
*****************************************************************************/
/*!
* \brief         Copies the content of a memory entry to another memory entry
*
* \details       Copies the content of a memory entry to another memory entry
*
* \param[in]     DestinationMemoryEntryId
*                The memory entry handle of the destination memory entry
* \param[in]     SourceMemoryEntryId
*                The memory entry handle of the source memory entry
*
* \pre           -
* \config        DEM_CFG_SUPPORT_DCM == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemoryEntry_CopyEntry(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  DestinationMemoryEntryId,
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  SourceMemoryEntryId
  );
#endif

/* ****************************************************************************
 * Dem_MemoryEntry_IncrementOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Increment the occurrence counter in the memory entry.
 *
 * \details       Increment the occurrence counter in the memory entry, if it
 *                is lower than the maximum value (latch at maximum value).
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 *
 * \return        TRUE
 *                The occurrence counter was incremented succesfully.
 *                FALSE
 *                The occurrence counter was not incremented.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_IncrementOccurrenceCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_IncrementFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Increment the 'Failed Cycle Counter' in the memory entry.
 *
 * \details       Increment the 'Failed Cycle Counter' in the memory entry, if
 *                it is lower than the maximum value (latch at maximum value).
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 *
 * \return        TRUE
 *                The 'Failed Cycle Counter' was incremented succesfully.
 *                FALSE
 *                The 'Failed Cycle Counter' was not incremented.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_IncrementFailedCycleCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_IncrementConsecutiveFailedCycleCounter
 *****************************************************************************/
/*!
 * \brief         Increment the 'Consecutive Failed Cycle Counter' in the 
 *                memory entry
 *
 * \details       Increment the 'Consecutive Failed Cycle Counter' in the 
 *                memory entry, if it is lower than the maximum value (latch at
 *                maximum value).
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle
 *
 * \return        TRUE
 *                The 'Consecutive Failed Cycle Counter' was incremented 
 *                succesfully
 *                FALSE
 *                The 'Consecutive Failed Cycle Counter' was not incremented
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_IncrementConsecutiveFailedCycleCounter(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_InitializeEntry
 *****************************************************************************/
/*!
 * \brief         Initializes an event memory entry.
 *
 * \details       Initialize the different elements of an event's MemoryEntry 
 *                struct.
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemoryEntry_InitializeEntry(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );

/* ****************************************************************************
 * Dem_MemoryEntry_GetId
 *****************************************************************************/
/*!
 * \brief         Get the memory entry Id
 *
 * \details       Get the memory entry Id from the block index
 *
 * \param[in]     BlockIndex
 *                NV Block index of the memory entry
 *
 * \return        The memory entry Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemoryEntry_HandleType, DEM_CODE)
Dem_MemoryEntry_GetId(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  BlockIndex
  );

#if (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
/* ****************************************************************************
 * Dem_MemoryEntry_TestAgingOnlyEntry
 *****************************************************************************/
/*!
 * \brief         Checks whether the event memory entry is an aging only entry.
 *
 * \details       Checks whether the event memory entry is an aging only entry.
 *
 * \param[in]     MemoryEntryId
 *                The memory entry handle.
 *
 * \return        TRUE
 *                Aging only entry
 * \return        FALSE
 *                Otherwise
 *                
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemoryEntry_TestAgingOnlyEntry(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMORYENTRY_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemoryEntry_Interface.h
 *********************************************************************************************************************/
