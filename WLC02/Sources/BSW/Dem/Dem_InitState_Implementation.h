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
/*! \addtogroup Dem_InitState
 *  \{
 *  \file       Dem_InitState_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
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

#if !defined (DEM_INITSTATE_IMPLEMENTATION_H)
#define DEM_INITSTATE_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_InitState_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Satellite_Interface.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_INIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Initialization state of the Dem */
DEM_LOCAL VAR(uint8, DEM_VAR_INIT) Dem_InitState_CoreInitializationStatus = DEM_INITSTATE_UNINITIALIZED;

#define DEM_STOP_SEC_VAR_INIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_InitState_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_InitState_SetInitState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_InitState_SetInitState(
  uint8 InitState
  )
{
  Dem_InitState_CoreInitializationStatus = InitState;
}

/* ****************************************************************************
 % Dem_InitState_GetInitState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_InitState_GetInitState(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return Dem_InitState_CoreInitializationStatus;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 %  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_InitState_Public
 * \{
 */

/* ****************************************************************************
 % Dem_InitState_TestMasterInState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_InitState_TestMasterInState(
  CONST(uint8, AUTOMATIC) InitState
  )
{
  return (boolean)(Dem_InitState_CoreInitializationStatus == InitState);
}

/* ****************************************************************************
 % Dem_InitState_TestMasterAtLeastInState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_InitState_TestMasterAtLeastInState(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC) InitState
  )
{
  return (boolean)(Dem_InitState_CoreInitializationStatus >= InitState);
}

/* ****************************************************************************
 % Dem_InitState_TestSatelliteInState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_InitState_TestSatelliteInState(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
  )
{
  return (boolean)(Dem_Satellite_GetInitState(SatelliteId) == InitState);
}

/* ****************************************************************************
 % Dem_InitState_TestAllSatellitesAtLeastInState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_InitState_TestAllSatellitesAtLeastInState(                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC) InitState
  )
{
  boolean lReturnValue;
  Dem_Satellite_IdType lSatelliteId;

  lReturnValue = TRUE;
  for (lSatelliteId = 0;
       lSatelliteId < Dem_Cfg_GlobalSatelliteCount();
       ++lSatelliteId)
  {
    if (Dem_InitState_TestSatelliteAtLeastInState(lSatelliteId, InitState) == FALSE)
    {
      lReturnValue = FALSE;
      break;
    }
  }

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_InitState_TestSatelliteAtLeastInState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_InitState_TestSatelliteAtLeastInState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
  )
{
  return (boolean)(Dem_Satellite_GetInitState(SatelliteId) >= InitState);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_INITSTATE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_InitState_Implementation.h
 *********************************************************************************************************************/
