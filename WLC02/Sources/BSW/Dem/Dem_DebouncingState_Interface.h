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
 *  \defgroup   Dem_DebouncingState DebouncingState
 *  \{
 *  \file       Dem_DebouncingState_Interface.h
 *  \brief      Debouncing State
 *  \details    Encapsulation of AUTOSAR Debouncing State
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

#if !defined (DEM_DEBOUNCINGSTATE_INTERFACE_H)
#define DEM_DEBOUNCINGSTATE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DebouncingState_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DebouncingState_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_DebouncingState_GetInitValue()
 *****************************************************************************/
/*!
 * \brief         Get an initialized debouncing state
 *
 * \details       Get a debouncing state with no flags set
 *
 * \return        A debounceing value without any flags set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_GetInitValue(
  void
  );

/* ****************************************************************************
 * Dem_DebouncingState_TestTemporarilyDefective()
 *****************************************************************************/
/*!
 * \brief         Test the TemporarilyDefective flag of the given DebounceStatus
 *
 * \details       Get the TemporarilyDefective flag of the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        TRUE
 *                The TemporarilyDefective flag is set
 * \return        FALSE
 *                The TemporarilyDefective flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTemporarilyDefective(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );

/* ****************************************************************************
 * Dem_DebouncingState_SetTemporarilyDefective()
 *****************************************************************************/
/*!
 * \brief         Set the TemporarilyDefective flag in the given DebounceStatus
 *
 * \details       Set the TemporarilyDefective flag in the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        DebounceStatus with the TemporarilyDefective flag set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetTemporarilyDefective(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );

/* ****************************************************************************
 * Dem_DebouncingState_TestFinallyDefective()
 *****************************************************************************/
/*!
 * \brief         Test the FinallyDefective flag of the given DebounceStatus
 *
 * \details       Get the FinallyDefective flag of the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        TRUE
 *                The FinallyDefective flag is set
 * \return        FALSE
 *                The FinallyDefective flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestFinallyDefective(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );

/* ****************************************************************************
 * Dem_DebouncingState_SetFinallyDefective()
 *****************************************************************************/
/*!
 * \brief         Set the FinallyDefective flag in the given DebounceStatus
 *
 * \details       Set the FinallyDefective flag in the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        DebounceStatus with the FinallyDefective flag set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetFinallyDefective(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );

/* ****************************************************************************
 % Dem_DebouncingState_TestTemporarilyHealed()
 *****************************************************************************/
/*!
 * \brief         Test the TemporarilyHealed flag of the given DebounceStatus
 *
 * \details       Get the TemporarilyHealed flag of the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        TRUE
 *                The TemporarilyHealed flag is set
 * \return        FALSE
 *                The TemporarilyHealed flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTemporarilyHealed(                                                                                       
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DebouncingState_SetTemporarilyHealed()
 *****************************************************************************/
/*!
 * \brief         Set the TemporarilyHealed flag in the given DebounceStatus
 *
 * \details       Set the TemporarilyHealed flag in the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        DebounceStatus with the TemporarilyHealed flag set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetTemporarilyHealed(                                                                              
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 % Dem_DebouncingState_TestTestComplete()
 *****************************************************************************/
/*!
 * \brief         Test the TestComplete flag of the given DebounceStatus
 *
 * \details       Get the TestComplete flag of the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        TRUE
 *                The TestComplete flag is set
 * \return        FALSE
 *                The TestComplete flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTestComplete(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );

/* ****************************************************************************
 * Dem_DebouncingState_SetTestComplete()
 *****************************************************************************/
/*!
 * \brief         Set the TestComplete flag in the given DebounceStatus
 *
 * \details       Set the TestComplete flag in the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        DebounceStatus with the TestComplete flag set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetTestComplete(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );

/* ****************************************************************************
 * Dem_DebouncingState_TestDtrUpdate()
 *****************************************************************************/
/*!
 * \brief         Test the DtrUpdate flag of the given DebounceStatus
 *
 * \details       Get the DtrUpdate flag of the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        TRUE
 *                The DtrUpdate flag is set
 * \return        FALSE
 *                The DtrUpdate flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestDtrUpdate(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );

/* ****************************************************************************
 * Dem_DebouncingState_SetDtrUpdate()
 *****************************************************************************/
/*!
 * \brief         Set the DtrUpdate flag in the given DebounceStatus
 *
 * \details       Set the DtrUpdate flag in the given DebounceStatus
 *
 * \param[in]     DebounceStatus
 *                The debounce status
 *
 * \return        DebounceStatus with the DtrUpdate flag set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetDtrUpdate(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DEBOUNCINGSTATE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebouncingState_Interface.h
 *********************************************************************************************************************/
