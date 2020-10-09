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
/*! \ingroup    Dem_Debounce
 *  \defgroup   Dem_DebounceTimeBased Timer Based Debounce
 *
 *  \{
 *  \file       Dem_DebounceTimeBased_Interface.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public interface of DebounceTimeBased subcomponent
 *
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

#if !defined (DEM_DEBOUNCETIMEBASED_INTERFACE_H)
#define DEM_DEBOUNCETIMEBASED_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceTimeBased_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION INTERFACE
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
* \defgroup Dem_DebounceTimeBased_Private Private Methods
* \{
*/

/* ****************************************************************************
 * Dem_DebounceTimeBased_CheckDebounceInfoPtr
 *****************************************************************************/
/*!
 * \brief         Checks whether the DebounceInfoPtr is initialized for time 
 *                based debouncing.
 *
 * \details       Checks whether the DebounceInfoPtr is initialized for time 
 *                based debouncing.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to debounce base object.
 *
 * \return        TRUE: DebounceInfoPtr is initialized for time based debouncing.
 *                FALSE: Otherwise.
 *
 * \pre           -
 * 
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceTimeBased_CheckDebounceInfoPtr(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_Base2TimeBased
 *****************************************************************************/
/*!
 * \brief         Derives the time based object from the given base object.
 *
 * \details       Derives the time based debounce object from the given base
 *                debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to debounce base object.
 *
 * \return        Pointer to time based debounce object.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceTimeBased_InfoPtrType, DEM_CODE)
Dem_DebounceTimeBased_Base2TimeBased(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_ConstBase2TimeBased
 *****************************************************************************/
/*!
 * \brief         Derives the time based object from the given base object.
 *
 * \details       Derives the time based debounce object from the given base
 *                debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Non-writable pointer to debounce base object.
 *
 * \return        Non-writable pointer to time based debounce object.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceTimeBased_ConstInfoPtrType, DEM_CODE)
Dem_DebounceTimeBased_ConstBase2TimeBased(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_EventFailedTime
 *****************************************************************************/
/*!
 * \brief         Get the failed timeout for the event
 *
 * \details       Get the failed timeout for the event. When time based 
 *                debouncing is not supported, the function returns 1 in order 
 *                to prevent the division by zero error.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Failed timeout for the event.
 *
 * \pre           Event must be configured for time based debouncing
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DebounceTimeBased_EventFailedTime(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_EventPassedTime
 *****************************************************************************/
/*!
 * \brief         Get the passed timeout for the event
 *
 * \details       Get the passed timeout for the event. When time based 
 *                debouncing is not supported, the function returns 1 in order 
 *                to prevent the division by zero error.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Passed timeout for the event.
 *
 * \pre           Event must be configured for time based debouncing
 * \config        DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DebounceTimeBased_EventPassedTime(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 * Dem_DebounceTimeBased_EventStorageTime
 *****************************************************************************/
/*!
 * \brief         Get the storage timeout for the event
 *
 * \details       Get the storage timeout for the event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The storage timeout
 *
 * \pre           Event must be configured for time based debouncing
 * \config        DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DebounceTimeBased_EventStorageTime(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_DebounceTimeBased_GetOldTimerState
 *****************************************************************************/
/*!
 * \brief         Gets the old debounce state.
 *
 * \details       Gets the old debounce state from the debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to base debounce object.
 *
 * \return        The old debounce state.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Debounce_StatusType, DEM_CODE)
Dem_DebounceTimeBased_GetOldTimerState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_GetNewTimerState
 *****************************************************************************/
/*!
 * \brief         Gets the new debounce state.
 *
 * \details       Gets the new debounce state from the debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to base debounce object.
 *
 * \return        The new debounce state.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Debounce_StatusType, DEM_CODE)
Dem_DebounceTimeBased_GetNewTimerState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_SetNewTimerState
 *****************************************************************************/
/*!
 * \brief         Sets the new debounce state.
 *
 * \details       Sets the new debounce state of the debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to base debounce object.
 * \param[in]     DebounceState
 *                New debounce timer state to set
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_SetNewTimerState(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_Debounce_StatusType, AUTOMATIC)  DebounceState
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_GetOldTimerValue
 *****************************************************************************/
/*!
 * \brief         Gets the old debounce timer.
 *
 * \details       Gets the old debounce timer from the debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to base debounce object.
 *
 * \return        The old debounce timer.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DebounceTimeBased_GetOldTimerValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceTimeBased_GetNewTimerValue
 *****************************************************************************/
/*!
 * \brief         Gets the new debounce timer.
 *
 * \details       Gets the new debounce timer from the debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to base debounce object.
 *
 * \return        The new debounce timer.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_DebounceTimeBased_GetNewTimerValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceTimeBased_SetNewTimerValue
 *****************************************************************************/
/*!
 * \brief         Sets the new debounce timer.
 *
 * \details       Sets the new debounce timer of the debounce object.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to base debounce object.
 * \param[in]     DebounceTimer
 *                New timer value to set.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_SetNewTimerValue(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(uint16, AUTOMATIC)  DebounceTimer
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceTimeBased_CalculateFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the current fault detection counter of an event.
 *
 * \details       Calculates the current fault detection counter of an event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     DebounceValue
 *                Debounce timer value
 *
 * \param[in]     DebounceStatus
 *                Debounce state value
 *
 * \return        The FaultDetectionCounter based on the given time and state
 *
 * \pre           The event must use time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_DebounceTimeBased_CalculateFaultDetectionCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC)  DebounceValue,
  CONST(Dem_Debounce_StatusType, AUTOMATIC)  DebounceStatus
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_CalculatePrepassed
 *****************************************************************************/
/*!
 * \brief         Process the time based debouncing of an event which is in
 *                state prepassed.
 *
 * \details       Process the time based debouncing of an event which is in
 *                state prepassed.
 *
 * \param[in,out] DebounceInfoData
 *                The debouncing information.
 *
 * \pre           The event must use time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_CalculatePrepassed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceTimeBased_CalculatePrefailed
 *****************************************************************************/
/*!
 * \brief         Process the timer based debouncing of an event which is in
 *                state prefailed.
 *
 * \details       Process the timer based debouncing of an event which is in
 *                state prefailed.
 *
 * \param[in,out] DebounceInfoData
 *                The debouncing information.
 *
 * \pre           The event must use time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_CalculatePrefailed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceTimeBased_CalculatePassed
 *****************************************************************************/
/*!
 * \brief         Process the timer based debouncing of an event which is in
 *                state passed.
 *
 * \details       Process the timer based debouncing of an event which is in
 *                state passed.
 *
 * \param[in,out] DebounceInfoData
 *                The debouncing information.
 *
 * \pre           The event must use time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_CalculatePassed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceTimeBased_CalculateFailed
 *****************************************************************************/
/*!
 * \brief         Process the timer based debouncing of an event which is in
 *                state failed.
 *
 * \details       Process the timer based debouncing of an event which is in
 *                state failed.
 *
 * \param[in,out] DebounceInfoData
 *                The debouncing information.
 *
 * \pre           The event must use time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_CalculateFailed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 * Dem_DebounceTimeBased_CountingTowardsPassed
 *****************************************************************************/
/*!
 * \brief         Process the debounce timer of an event debouncing in direction 
 *                of 'Passed'.
 *
 * \details       Process the debounce timer of an event debouncing in direction 
 *                of 'Passed'.
 *
 * \param[in,out] DebounceInfoData
 *                The debouncing information.
 *
 * \pre           The event must use time based debouncing.
 * \config        DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_CountingTowardsPassed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );
#endif

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 * Dem_DebounceTimeBased_CountingTowardsFailed
 *****************************************************************************/
/*!
 * \brief         Process the debounce timer of an event debouncing in direction
 *                of 'Failed'.
 *
 * \details       Process the debounce timer of an event debouncing in direction
 *                of 'Failed'.
 *
 * \param[in,out] DebounceInfoData
 *                The debouncing information.
 *
 * \pre           The event must use time based debouncing.
 * \config        DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_CountingTowardsFailed(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 * Dem_DebounceTimeBased_CountingTowardsFailedWithFDCReached
 *****************************************************************************/
/*!
 * \brief         Process the debounce timer of an event debouncing in direction
 *                of 'Failed' while FDC threshold is already reached.
 *
 * \details       Process the debounce timer of an event debouncing in direction
 *                of 'Failed' while FDC threshold is already reached.
 *
 * \param[in,out] DebounceInfoData
 *                The debouncing information.
 *
 * \pre           The event must use time based debouncing.
 * \config        DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_CountingTowardsFailedWithFDCReached(
  CONST(Dem_DebounceTimeBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

/*!
* \}
*/
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT API PUBLIC FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DebounceTimeBased_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_DebounceTimeBased_InfoInit
 *****************************************************************************/
/*!
 * \brief         Initializes a debounce object for time based debouncing.
 *
 * \details       This function initializes the fields of a time based
 *                debounce descriptor. Debounce state and timer values are 
 *                set to the given values.
 *
 * \param[out]    DebounceInfoData
 *                The debouncing element to be initialized.
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     SatelliteData
 *                The satellite data element holding the data used to 
 *                initialize the debouncing info.
 *
 * \returns       Pointer to the base debounce object.
 *
 * \pre           The event must use time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceBase_InfoPtrType, DEM_CODE)
Dem_DebounceTimeBased_InfoInit(
  CONSTP2VAR(Dem_DebounceTimeBased_InfoType, AUTOMATIC, AUTOMATIC) DebounceInfoData,
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_Calculate
 *****************************************************************************/
/*!
 * \brief         Process the time based debouncing of an event.
 *
 * \details       Process the time based debouncing of an event.
 *
 * \param[in,out] DebounceInfoPtr
 *                The debouncing information.
 *
 * \return        TRUE
 *                Debouncing was processed.

 * \return        FALSE
 *                Debouncing failed due to enable condition OR
 *                DebounceInfoPtr was not initialized for time based debouncing.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DebounceTimeBased_Calculate(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_Freeze
 *****************************************************************************/
/*!
 * \brief         Pauses time based debouncing for an event.
 *
 * \details       Pauses time based debouncing for an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_Freeze(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_Reset
 *****************************************************************************/
/*!
 * \brief         Resets time based debouncing for an event.
 *
 * \details       Resets time based debouncing for an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBased_Reset(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

 /* ****************************************************************************
  * Dem_DebounceTimeBased_GetDebouncingState
  *****************************************************************************/
 /*!
  * \brief         Calculates the debouncing state of an event.
  *
  * \details       Calculates the debouncing state of an event.
  *
  * \param[in,out] DebounceInfoPtr
  *                The debouncing information.
  *
  * \return        The debouncing state of the event.
  *
  * \pre           DebounceInfoPtr was initialized for time based debouncing.
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE for different events
  *****************************************************************************/
 DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
 Dem_DebounceTimeBased_GetDebouncingState(
   CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
   );

 /* ****************************************************************************
  * Dem_DebounceTimeBasedSat_UpdateDebounceValueMax
  *****************************************************************************/
 /*!
  * \brief         Updates the stored maximum debounce value for an event.
  *
  * \details       Updates the stored maximum debounce value for an event.
  *
  * \param[in]     DebounceInfoPtr
  *                The debouncing information.
  *
  * \pre           DebounceInfoPtr was initialized for time based debouncing.
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE
  *****************************************************************************/
 DEM_LOCAL FUNC(void, DEM_CODE)
 Dem_DebounceTimeBasedSat_UpdateDebounceValueMax(
   CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
   );

/* ****************************************************************************
 * Dem_DebounceTimeBasedSat_ResetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Resets the stored maximum debounce value for an event.
 *
 * \details       Resets the stored maximum debounce value for an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceTimeBasedSat_ResetDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the current fault detection counter of an event.
 *
 * \details       Calculates the current fault detection counter of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \param[out]    FaultDetectionCounter
 *                The current FDC based on the debounce time and state.
 *
 * \return        Always E_OK
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceTimeBased_GetFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the maximum fault detection counter of an event.
 *
 * \details       Calculates the maximum fault detection counter of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 * \param[out]    FaultDetectionCounter
 *                The maximum FDC based on the debounce time and state
 *
 * \return        Always E_OK
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceTimeBased_GetMaxFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  );

/* ****************************************************************************
 * Dem_DebounceTimeBased_GetDebouncingResult
 *****************************************************************************/
/*!
 * \brief         Updates the debouncing data of an event.
 *
 * \details       Updates the debouncing data of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 *
 * \return        Data object holding the modified debounce data
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceTimeBased_GetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceTimeBased_RestoreDebounceValue
 *****************************************************************************/
/*!
 * \brief         Restore the debouncing value of an event.
 *
 * \details       Value is restored, if
 *                 - the given debounce value is not qualified
 *                 - or if the debounce value is qualified and the reached
 *                   threshold equals the ExpectedThreshold.
 *
 *                Otherwise Value is not restored.
 *
 * \param[in]     DebounceInfoPtr
 *                The object to query.
 *
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 *
 * \param[in]     Value
 *                The value to be restored
 *
 * \param[in]     ExpectedThreshold
 *                Specifies whether the negative threshold is expected to be
 *                reached (TRUE), or the positive one (FALSE).
 *
 * \return        Data object holding the modified debounce data
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceTimeBased_RestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  );

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 * Dem_DebounceTimeBasedSat_ProcessDebounce
 *****************************************************************************/
/*!
 * \brief         Processes the time based debouncing of an event.
 *
 * \details       Updates the debouncing state and timers of the debounced
 *                event. Any resulting event processing is deferred to the
 *                context of the Dem task.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 * \config        DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceTimeBasedSat_ProcessDebounce(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC) DebounceInfoPtr
  );
#endif

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 * Dem_DebounceTimeBasedSat_IsTimerActive
 *****************************************************************************/
/*!
 * \brief         Tests if the debounce timer of the event is active.
 *
 * \details       Tests if the debounce timer of the event is active, i.e.
 *                the timer is already started, not frozen and not expired.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \return        TRUE
 *                Debounce timer is active
 *                FALSE
 *                Debounce timer is inactive
 *
 * \pre           DebounceInfoPtr was initialized for time based debouncing.
 * \config        DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceTimeBasedSat_IsTimerActive(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC) DebounceInfoPtr
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DEBOUNCETIMEBASED_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceTimeBased_Interfaces.h
 *********************************************************************************************************************/
