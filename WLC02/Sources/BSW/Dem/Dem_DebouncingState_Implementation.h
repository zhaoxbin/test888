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
/*! \addtogroup Dem_DebouncingState
 *  \{
 *  \file       Dem_DebouncingState_Implementation.h
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

#if !defined (DEM_DEBOUNCINGSTATE_IMPLEMENTATION_H)
#define DEM_DEBOUNCINGSTATE_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DebouncingState_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
#define DEM_DEBOUNCINGSTATE_INITVALUE            0         /*!< The debouncing status initialization value */


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_DebouncingState_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_DebouncingState_GetInitValue()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_GetInitValue(
  void
  )
{
  return DEM_DEBOUNCINGSTATE_INITVALUE;
}

/* ****************************************************************************
 % Dem_DebouncingState_TestTemporarilyDefective()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTemporarilyDefective(                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (boolean)((DebounceStatus & DEM_TEMPORARILY_DEFECTIVE) != 0);
}

/* ****************************************************************************
 % Dem_DebouncingState_SetTemporarilyDefective()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetTemporarilyDefective(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (Dem_DebouncingStateType)(DebounceStatus | DEM_TEMPORARILY_DEFECTIVE);
}

/* ****************************************************************************
 % Dem_DebouncingState_TestFinallyDefective()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestFinallyDefective(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (boolean)((DebounceStatus & DEM_FINALLY_DEFECTIVE) != 0);
}

/* ****************************************************************************
 % Dem_DebouncingState_SetFinallyDefective()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetFinallyDefective(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (Dem_DebouncingStateType)(DebounceStatus | DEM_FINALLY_DEFECTIVE);
}

/* ****************************************************************************
 % Dem_DebouncingState_TestTemporarilyHealed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTemporarilyHealed(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (boolean)((DebounceStatus & DEM_TEMPORARILY_HEALED) != 0);
}

/* ****************************************************************************
 % Dem_DebouncingState_SetTemporarilyHealed()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetTemporarilyHealed(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (Dem_DebouncingStateType)(DebounceStatus | DEM_TEMPORARILY_HEALED);
}

/* ****************************************************************************
 % Dem_DebouncingState_TestTestComplete()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestTestComplete(                                                                                            /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (boolean)((DebounceStatus & DEM_TEST_COMPLETE) != 0);
}

/* ****************************************************************************
 % Dem_DebouncingState_SetTestComplete()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetTestComplete(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (Dem_DebouncingStateType)(DebounceStatus | DEM_TEST_COMPLETE);
}

/* ****************************************************************************
 % Dem_DebouncingState_TestDtrUpdate()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DebouncingState_TestDtrUpdate(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (boolean)((DebounceStatus & DEM_DTR_UPDATE) != 0);
}

/* ****************************************************************************
 % Dem_DebouncingState_SetDtrUpdate()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_DebouncingState_SetDtrUpdate(
  CONST(Dem_DebouncingStateType, AUTOMATIC) DebounceStatus
  )
{
  return (Dem_DebouncingStateType)(DebounceStatus | DEM_DTR_UPDATE);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DEBOUNCINGSTATE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebouncingState_Implementation.h
 *********************************************************************************************************************/
