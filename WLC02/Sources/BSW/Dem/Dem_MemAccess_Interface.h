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
 *  \defgroup   Dem_MemAccess MemAccess
 *  \{
 *  \file       Dem_MemAccess_Interface.h
 *  \brief      Basic routines for event memories.
 *  \details    In general, returns a memory entry or allows queries concerning the whole event memory
 *              - find free memory entries including displacement and aging
 *              - allocate memory entries
 *              - free event memory entries and trigger removal of event related data (OBD freeze frame, time series & permanent entries).
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

#if !defined (DEM_MEMACCESS_INTERFACE_H)
#define DEM_MEMACCESS_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemAccess_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_MemAccess_Properties Properties
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
 * \defgroup Dem_MemAccess_Private Private Methods
 * \{
 */

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON))
/* ****************************************************************************
 * Dem_MemAccess_Displace_GetNextCandidate
 *****************************************************************************/
/*!
 * \brief         Get the next event memory entry candidate for the displacement check.
 *
 * \details       Get the next event memory entry candidate for the displacement check.
 *
 * \param[out]    CandidateInfo
 *                Buffer that receives the candidate's characteristic data.
 * \param[in]     MemoryInfo
 *                Event memory descriptor
 * \param[in]     ChronoIndexIterator
 *                Iterator on the chronology of elements to be displaced.
 *                The iterator must be in range
 *                [1..Dem_MemState_MemoryGetCurrentSize(MemoryInfo)[.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemAccess_Displace_GetNextCandidate(
  CONSTP2VAR(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) CandidateInfo,
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(uint8, AUTOMATIC)  ChronoIndexIterator
  );
#endif

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON))
/* ****************************************************************************
 * Dem_MemAccess_Displace_UpdateBestMatch
 *****************************************************************************/
/*!
 * \brief         Update the best match info by the candidate info.
 *
 * \details       Update the best match info by the candidate info.
 *
 * \param[in,out] BestMatchInfo
 *                IN: The current best match for displacement.
 *                OUT: The best match updated with the relevant candidate info.
 * \param[in]     CandidateInfo
 *                The candidate info.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemAccess_Displace_UpdateBestMatch(
  CONSTP2VAR(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) BestMatchInfo,
  CONSTP2CONST(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) CandidateInfo
  );
#endif


#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON))
/* ****************************************************************************
 * Dem_MemAccess_Displace_CheckInvalidEntry
 *****************************************************************************/
/*!
 * \brief         Check if candidate is an invalid entry.
 *
 * \details       Check if candidate is the invalid entry. If so, it is the
 *                best match.
 *
 * \param[in,out] BestMatchInfo
 *                IN: The current best match for displacement.
 *                OUT: Either the candidate (if better match) or the previous
 *                value.
 * \param[in]     CandidateInfo
 *                The candidate to be checked against the current best match.
 *
 * \return        Dem_MemAccess_Displace_NeedMoreTests
 *                Candidate may be a match, but this check can't decide that it
 *                is the 'best match', so this candidate shall undergo further
 *                checks. 'BestMatchInfo' is unmodified.
 * \return        Dem_MemAccess_Displace_FoundBestMatch
 *                Candidate is the best match for sure. 'BestMatchInfo'
 *                is updated.
 *                No further scanning for better matches is required.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemAccess_Displace_CheckResultType, DEM_CODE)
Dem_MemAccess_Displace_CheckInvalidEntry(
  CONSTP2VAR(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) BestMatchInfo,
  CONSTP2CONST(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) CandidateInfo
  );
#endif

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON) \
  && (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON))
/* ****************************************************************************
 * Dem_MemAccess_Displace_CheckAgedCandidate
 *****************************************************************************/
/*!
 * \brief         Check if candidate is aged.
 *
 * \details       Check if candidate is aged, so can be displaced immediately.
 *                If so, it is the best match.
 *
 * \param[in,out] BestMatchInfo
 *                IN: The current best match for displacement.
 *                OUT: Either the candidate (if better match) or the previous
 *                value.
 * \param[in]     CandidateInfo
 *                The candidate to be checked against the current best match.
 *
 * \return        Dem_MemAccess_Displace_NeedMoreTests
 *                Candidate may be a match, but this check can't decide that it
 *                is the 'best match', so this candidate shall undergo further
 *                checks. 'BestMatchInfo' is unmodified.
 * \return        Dem_MemAccess_Displace_FoundBestMatch
 *                Candidate is the best match for sure. 'BestMatchInfo'
 *                is updated.
 *                No further scanning for better matches is required.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
 *                && (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemAccess_Displace_CheckResultType, DEM_CODE)
Dem_MemAccess_Displace_CheckAgedCandidate(
  CONSTP2VAR(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) BestMatchInfo,
  CONSTP2CONST(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) CandidateInfo
  );
#endif

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON) \
  && (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON))
/* ****************************************************************************
 * Dem_MemAccess_Displace_CheckHasAgingCounter
 *****************************************************************************/
/*!
 * \brief         Check if candidate has an exclusive aging counter.
 *
 * \details       Check if candidate has an exclusive aging counter, so can be
 *                displaced immediately. If so, it is the best match.
 *
 * \param[in,out] BestMatchInfo
 *                IN: The current best match for displacement.
 *                OUT: Either the candidate (if better match) or the previous
 *                value.
 * \param[in]     CandidateInfo
 *                The candidate to be checked against the current best match.
 *
 * \return        Dem_MemAccess_Displace_NeedMoreTests
 *                Candidate may be a match, but this check can't decide that it
 *                is the 'best match', so this candidate shall undergo further
 *                checks. 'BestMatchInfo' is unmodified.
 * \return        Dem_MemAccess_Displace_FoundBestMatch
 *                Candidate is the best match for sure. 'BestMatchInfo'
 *                is updated.
 *                No further scanning for better matches is required.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
 *                && (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemAccess_Displace_CheckResultType, DEM_CODE)
Dem_MemAccess_Displace_CheckHasAgingCounter(
  CONSTP2VAR(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) BestMatchInfo,
  CONSTP2CONST(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) CandidateInfo
  );
#endif

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON))
/* ****************************************************************************
 * Dem_MemAccess_Displace_CheckPriority
 *****************************************************************************/
/*!
 * \brief         Check if candidate's priority qualifies the displacement.
 *
 * \details       Check if candidate has an event priority, that qualifies it
 *                or disqualifies it for the displacement.
 *                Otherwise it needs further tests.
 *
 * \param[in,out] BestMatchInfo
 *                IN: The current best match for displacement.
 *                OUT: Either the candidate (if better match) or the previous
 *                value.
 * \param[in]     CandidateInfo
 *                The candidate to be checked against the current best match.
 *
 * \return        Dem_MemAccess_Displace_NeedMoreTests
 *                This check can't decide if candidate is a match, so this
 *                candidate shall undergo further checks.
 *                'BestMatchInfo' is unmodified.
 * \return        Dem_MemAccess_Displace_RatingDone
 *                Rating complete - continue the scan with next candidate.
 *                If candidate is no match, 'BestMatchInfo' is unmodified.
 *                If candidate is a match, 'BestMatchInfo' is updated.
 * \return        Dem_MemAccess_Displace_FoundBestMatch
 *                Candidate is the best match for sure.
 *                'BestMatchInfo' is updated.
 *                No further scanning for better matches is required.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemAccess_Displace_CheckResultType, DEM_CODE)
Dem_MemAccess_Displace_CheckPriority(
  CONSTP2VAR(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) BestMatchInfo,
  CONSTP2CONST(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) CandidateInfo
  );
#endif

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON) \
  && (DEM_CFG_SUPPORT_OBDII == STD_ON))
/* ****************************************************************************
 * Dem_MemAccess_Displace_CheckObdII
 *****************************************************************************/
/*!
 * \brief         Check if candidate's status qualifies the displacement.
 *
 * \details       Check if candidate is passive, and this qualifies it
 *                for the displacement.
 *                Otherwise it needs further tests.
 *                BestMatchInfo's OldestDisplaceableIndex value may be set 
 *                if it is currently undefined.
 *
 * \param[in,out] BestMatchInfo
 *                IN: The current best match for displacement.
 *                OUT: OldestDisplaceableIndex value may be set if it is
*                      currently undefined. Other values are unmodified.
 * \param[in]     CandidateInfo
 *                The candidate to be checked.
 *
 * \return        Dem_MemAccess_Displace_NeedMoreTests
 *                This check can't decide if candidate is a match, so this
 *                candidate shall undergo further checks.
 * \return        Dem_MemAccess_Displace_RatingDone
 *                Rating complete - continue the scan with next candidate.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
 *                && (DEM_CFG_SUPPORT_OBDII == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemAccess_Displace_CheckResultType, DEM_CODE)
Dem_MemAccess_Displace_CheckObdII(
  CONSTP2VAR(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) BestMatchInfo,
  CONSTP2CONST(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) CandidateInfo
  );
#endif

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON) \
  && (DEM_CFG_DISPLACEMENT_PREFER_PASSIVE == STD_ON))
/* ****************************************************************************
 * Dem_MemAccess_Displace_CheckPassiveState
 *****************************************************************************/
/*!
 * \brief         Check if candidate's status (TestFailed bit) qualifies the
 *                displacement.
 *
 * \details       Check if candidate is passive, and this qualifies it
 *                for the displacement.
 *                Otherwise it needs further tests.
 *
 * \param[in,out] BestMatchInfo
 *                IN: The current best match for displacement.
 *                OUT: Either the candidate (if better match) or the previous
 *                value.
 * \param[in]     CandidateInfo
 *                The candidate to be checked against the current best match.
 *
 * \return        Dem_MemAccess_Displace_NeedMoreTests
 *                This check can't decide if candidate is a match, so this
 *                candidate shall undergo further checks.
 *                'BestMatchInfo' is unmodified.
 * \return        Dem_MemAccess_Displace_RatingDone
 *                Rating complete - continue the scan with next candidate.
 *                If candidate is no match, 'BestMatchInfo' is unmodified.
 *                If candidate is a match, 'BestMatchInfo' is updated.
 * \return        Dem_MemAccess_Displace_FoundBestMatch
 *                Candidate is the best match for sure.
 *                'BestMatchInfo' is updated.
 *                No further scanning for better matches is required.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
 *                && (DEM_CFG_DISPLACEMENT_PREFER_PASSIVE == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemAccess_Displace_CheckResultType, DEM_CODE)
Dem_MemAccess_Displace_CheckPassiveState(
  CONSTP2VAR(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) BestMatchInfo,
  CONSTP2CONST(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) CandidateInfo
  );
#endif

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON) \
  && (DEM_CFG_DISPLACEMENT_TNCTOC_IS_PASSIVE == STD_ON))
/* ****************************************************************************
 * Dem_MemAccess_Displace_CheckReadinessState
 *****************************************************************************/
/*!
 * \brief         Check if candidate's status (TNCTOC bit) qualifies the
 *                displacement.
 *
 * \details       Check if candidate's readiness (TNCTOC bit) is a better match
 *                than the current 'best match' for the displacement.
 *                Otherwise it needs further tests.
 *
 * \param[in,out] BestMatchInfo
 *                IN: The current best match for displacement.
 *                OUT: Either the candidate (if better match) or the previous
 *                value.
 * \param[in]     CandidateInfo
 *                The candidate to be checked against the current best match.
 *
 * \return        Dem_MemAccess_Displace_NeedMoreTests
 *                This check can't decide if candidate is a match, so this
 *                candidate shall undergo further checks.
 *                'BestMatchInfo' is unmodified.
 * \return        Dem_MemAccess_Displace_RatingDone
 *                Rating complete - continue the scan with next candidate.
 *                If candidate is no match, 'BestMatchInfo' is unmodified.
 *                If candidate is a match, 'BestMatchInfo' is updated.
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
 *                && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
 *                && (DEM_CFG_DISPLACEMENT_TNCTOC_IS_PASSIVE == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MemAccess_Displace_CheckResultType, DEM_CODE)
Dem_MemAccess_Displace_CheckReadinessState(
  CONSTP2VAR(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) BestMatchInfo,
  CONSTP2CONST(Dem_MemAccess_DisplacementInfoType, AUTOMATIC, AUTOMATIC) CandidateInfo
  );
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 * Dem_MemAccess_SelectDisplacedIndex_Vcc
 *****************************************************************************/
/*!
 * \brief         Selects an event to displace in a filled memory
 *
 * \details       Selects an event to displace in a filled memory
 *
 * \param[in]     MemoryInfo
 *                Event memory descriptor
 * \param[in]     DisplacingEventId
 *                Unique handle of the Event to be entered into the memory
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index of the displaced memory entry if one could
 *                be identified. DEM_MEM_INVALID_MEMORY_INDEX if displacement
 *                was not possible.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemAccess_SelectDisplacedIndex_Vcc(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_EventIdType, AUTOMATIC)  DisplacingEventId
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
 * \defgroup Dem_MemAccess_Public Public Methods
 * \{
 */

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 * Dem_MemAccess_SelectDisplacedIndex
 *****************************************************************************/
/*!
 * \brief         Selects an event to displace in a filled memory
 *
 * \details       Selects an event to displace in a filled memory
 *
 * \param[in]     MemoryInfo
 *                Event memory descriptor
 * \param[in]     DisplacingEventId
 *                Unique handle of the Event to be entered into the memory
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index of the displaced memory entry if one could
 *                be identified. DEM_MEM_INVALID_MEMORY_INDEX if displacement
 *                was not possible.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemAccess_SelectDisplacedIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_EventIdType, AUTOMATIC)  DisplacingEventId
  );
#endif

/* ****************************************************************************
 * Dem_MemAccess_MemoryAllocateIndex
 *****************************************************************************/
/*!
 * \brief         Selects a memory entry for an event
 *
 * \details       This function manages the event memory storage. If a free
 *                slot is available, it is returned directly. In case no free
 *                slot is available, the configured displacement algorithm is
 *                applied to free a slot.
 *
 * \param[in]     MemoryInfo
 *                Event memory descriptor
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
Dem_MemAccess_MemoryAllocateIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if ((DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) \
 && (DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON))
/* ****************************************************************************
 * Dem_MemAccess_MemoryAllocateAging
 *****************************************************************************/
/*!
 * \brief         Selects a memory entry for an event's aging counter
 *
 * \details       If a free memory slot is available, it is returned directly.
 *                There is no fallback in case of a filled up event memory.
 *
 * \param[in]     MemoryInfo
 *                Event memory descriptor
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index of the allocated event memory entry if one
 *                could be identified. DEM_MEM_INVALID_MEMORY_INDEX if no entry
 *                was allocated.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF
 *             && DEM_FEATURE_NEED_AGING_REALLOCATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemAccess_MemoryAllocateAging(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_MemAccess_MemoryFreeIndex
 *****************************************************************************/
/*!
 * \brief         Frees an event memory entry
 *
 * \details       This function frees an event memory entry.
 *
 * \param[in]     MemoryInfo
 *                Event memory descriptor
 * \param[in]     MemoryIndex
 *                Handle of the memory block
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemAccess_MemoryFreeIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  );

/* ****************************************************************************
 * Dem_MemAccess_MemoryFindIndex_Checked
 *****************************************************************************/
/*!
 * \brief         Finds the event memory allocated to an event.
 *
 * \details       Finds the event memory allocated to an event. If the event
 *                does not have a valid memory index, any valid index is
 *                returned instead.
 *
 * \param[in]     MemoryInfo
 *                Event memory descriptor.
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
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemAccess_MemoryFindIndex_Checked(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_MemAccess_MemoryFindIndex
 *****************************************************************************/
/*!
 * \brief         Finds the event memory allocated to an event.
 *
 * \details       Finds the event memory allocated to an event.
 *
 * \param[in]     MemoryInfo
 *                Event memory descriptor
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The memory index used by the event if one was found.
 *                Otherwise, DEM_MEM_INVALID_MEMORY_INDEX is returned.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemAccess_MemoryFindIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMACCESS_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemAccess_Interface.h
 *********************************************************************************************************************/
