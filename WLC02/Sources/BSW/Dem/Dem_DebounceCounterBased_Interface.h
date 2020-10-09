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
/*!  Project    MICROSAR Diagnostic Event Manager (Dem)
 *
 *  \ingroup    Dem_Debounce
 *  \defgroup   Dem_DebounceCounterBased Counter Based Debounce
 *  \{
 *  \file       Dem_DebounceCounterBased_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of DebounceCounterBased subcomponent
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

#if !defined (DEM_DEBOUNCECOUNTERBASED_INTERFACE_H)
#define DEM_DEBOUNCECOUNTERBASED_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceCounterBased_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION INTERFACE
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DebounceCounterBased_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_DebounceCounterBased_CheckDebounceInfoPtr
 *****************************************************************************/
/*!
 * \brief         Checks whether the DebounceInfoPtr is initialized for counter 
 *                based debouncing.
 *
 * \details       Checks whether the DebounceInfoPtr is initialized for counter 
 *                based debouncing.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to debounce base object.
 *
 * \return        TRUE: DebounceInfoPtr is initialized for counter based debouncing.
 *                FALSE: Otherwise.
 *
 * \pre           -
 * 
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebounceCounterBased_CheckDebounceInfoPtr(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceCounterBased_Base2CounterBased
 *****************************************************************************/
/*!
 * \brief         Derives the counter based object from the given base object.
 *
 * \details       Derives the counter based debounce object from the given base
 *                debounceobject.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to debounce base object.
 *
 * \return        Pointer to counter based debounce object.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceCounterBased_InfoPtrType, DEM_CODE)
Dem_DebounceCounterBased_Base2CounterBased(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceCounterBased_ConstBase2CounterBased
 *****************************************************************************/
/*!
 * \brief         Derives the counter based object from the given base object.
 *
 * \details       Derives the counter based debounce object from the given base
 *                debounceobject.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to base debounce object.
 *
 * \return        Pointer to counter based debounce object.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceCounterBased_ConstInfoPtrType, DEM_CODE)
Dem_DebounceCounterBased_ConstBase2CounterBased(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceCounterBased_GetNewDebounceValue
 *****************************************************************************/
/*!
 * \brief         Gets the new debounce value.
 *
 * \details       Gets the new debounce value.
 *
 * \param[in]     DebounceInfoPtr
 *                Pointer to base debounce object.
 *
 * \return        The new debounce value.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint16, DEM_CODE)
Dem_DebounceCounterBased_GetNewDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceCounterBased_SetNewDebounceValue
 *****************************************************************************/
/*!
 * \brief         Sets the new debounce value to the given value.
 *
 * \details       Sets the new debounce value to the given value.
 *
 * \param[in,out] DebounceInfoPtr
 *                Pointer to base debounce object.
 *
 * \param[in]     DebounceValue
 *                Debounce value to be set
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_SetNewDebounceValue(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(sint16, AUTOMATIC)  DebounceValue
  );

/* ****************************************************************************
 * Dem_DebounceCounterBased_CalculatePrepassed
 *****************************************************************************/
/*!
 * \brief         Process the counter based debouncing of an event which has
 *                been reported as prepassed.
 *
 * \details       Process the counter based debouncing of an event which has
 *                been reported as prepassed.
 *
 * \param[in,out] DebounceInfoData
 *                The counter based specific debouncing information.
 *
 * \pre           The event must use counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculatePrepassed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceCounterBased_CalculatePassed
 *****************************************************************************/
/*!
 * \brief         Process the counter based debouncing of an event which has
 *                been reported as passed.
 *
 * \details       Process the counter based debouncing of an event which has
 *                been reported as passed.
 *
 * \param[in,out] DebounceInfoData
 *                The counter based specific debouncing information.
 *
 * \pre           The event must use counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculatePassed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceCounterBased_CalculatePrefailed
 *****************************************************************************/
/*!
 * \brief         Process the counter based debouncing of an event which has
 *                been reported as prefailed.
 *
 * \details       Process the counter based debouncing of an event which has
 *                been reported as prefailed.
 *
 * \param[in,out] DebounceInfoData
 *                The counter based specific debouncing information.
 *
 * \pre           The event must use counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculatePrefailed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceCounterBased_CalculateFailed
 *****************************************************************************/
/*!
 * \brief         Process the counter based debouncing of an event which has
 *                been reported as failed.
 *
 * \details       Process the counter based debouncing of an event which has
 *                been reported as failed.
 *
 * \param[in,out] DebounceInfoData
 *                The counter based specific debouncing information.
 *
 * \pre           The event must use counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_CalculateFailed(
  CONST(Dem_DebounceCounterBased_InfoPtrType, AUTOMATIC)  DebounceInfoData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

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
 * \defgroup Dem_DebounceCounterBased_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_DebounceCounterBased_InfoInit
 *****************************************************************************/
/*!
 * \brief         Initializes a debounce object for counter based debouncing.
 *
 * \details       This function initializes the fields of a counter based
 *                debounce descriptor for a given event. debounce values are set
 *                to the given values.
 *
 * \param[out]    DebounceInfoData
 *                The counter based debouncing element to be initialized.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     SatelliteData
 *                Satellite Data containing the current debounce values.
 *
 * \returns       Pointer to the base debounce object.
 *
 * \pre           The event must use counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebounceBase_InfoPtrType, DEM_CODE)
Dem_DebounceCounterBased_InfoInit(
  CONSTP2VAR(Dem_DebounceCounterBased_InfoType, AUTOMATIC, AUTOMATIC) DebounceInfoData,
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceCounterBased_Calculate
 *****************************************************************************/
/*!
 * \brief         Process the counter based debouncing of an event.
 *
 * \details       Process the counter based debouncing of an event.
 *
 * \param[in,out] DebounceInfoPtr
 *                The debouncing information.
 *
 * \return        TRUE
 *                debouncing was processed
 *
 * \return        FALSE
 *                Debouncing failed due to enable conditions OR
 *                DebounceInfoPtr was not initialized for counter based debouncing.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_DebounceCounterBased_Calculate(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebounceCounterBased_Freeze
 *****************************************************************************/
/*!
 * \brief         Pauses counter based debouncing for an event.
 *
 * \details       Function has no effect.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_Freeze(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceCounterBased_Reset
 *****************************************************************************/
/*!
 * \brief         Resets counter based debouncing for an event.
 *
 * \details       Resets counter based debouncing for an event.
 *
 * \param[in,out] DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceCounterBased_Reset(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );


/* ****************************************************************************
 * Dem_DebounceCounterBased_GetDebouncingState
 *****************************************************************************/
/*!
 * \brief         Calculates the debouncing state of an event.
 *
 * \details       Calculates the debouncing state of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \return        The debouncing state of the event.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebounceCounterBased_GetDebouncingState(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceCounterBasedSat_UpdateDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Updates the stored maximum debounce value for an event.
 *
 * \details       Updates the stored maximum debounce value for an event.
 *
 * \param[in,out] DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceCounterBasedSat_UpdateDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceCounterBasedSat_ResetDebounceValueMax
 *****************************************************************************/
/*!
 * \brief         Resets the stored maximum debounce value for an event.
 *
 * \details       Resets the stored maximum debounce value for an event.
 *
 * \param[in,out] DebounceInfoPtr
 *                The debouncing information.
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_DebounceCounterBasedSat_ResetDebounceValueMax(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_DebounceCounterBased_GetFaultDetectionCounter
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
 *                The current FDC based on the debounce value
 *
 * \return        Always E_OK
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceCounterBased_GetFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  );

/* ****************************************************************************
 * Dem_DebounceCounterBased_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the maximum fault detection counter of an event.
 *
 * \details       Calculates the maximum fault detection counter of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \param[out]    FaultDetectionCounter
 *                The maximum FDC based on the current debounce value
 *
 * \return        Always E_OK
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_DebounceCounterBased_GetMaxFaultDetectionCounter(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FaultDetectionCounter
  );

/* ****************************************************************************
 * Dem_DebounceCounterBased_GetDebouncingResult
 *****************************************************************************/
/*!
 * \brief         Update the debouncing data of an event.
 *
 * \details       Update the debouncing data of an event.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
 *
 * \param[in]     SatelliteData
 *                Data object holding the current debounce data
 *
 * \return        Data object holding the modified debounce data
 *
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceCounterBased_GetDebouncingResult(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* *****************************************************************************
 * Dem_DebounceCounterBased_RestoreDebounceValue
 *****************************************************************************/
/*!
 * \brief         Restore the debouncing value of an event.
 *
 * \details       Value is restored, if
 *                 - the given debounce value is not qualified
 *                 - or if the debounce value is qualified and the reached
 *                   threshold equals the ExpectedThreshold.
 *
 *                Otherwise value is not restored.
 *
 * \param[in]     DebounceInfoPtr
 *                The debouncing information.
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
 * \pre           DebounceInfoPtr was initialized for counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_DebounceCounterBased_RestoreDebounceValue(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC) SatelliteData,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  );

/* ****************************************************************************
 * Dem_DebounceCounterBased_CalculateFaultDetectionCounter
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
 *                Debounce counter value
 *
 * \return        The FaultDetectionCounter based on DebounceValue
 *
 * \pre           The event must use counter based debouncing.
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(sint8, DEM_CODE)
Dem_DebounceCounterBased_CalculateFaultDetectionCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(sint16, AUTOMATIC)  DebounceValue
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DEBOUNCECOUNTERBASED_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceCounterBased_Interfaces.h
 *********************************************************************************************************************/
