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
/*! \addtogroup Dem_SatelliteInfo
 *  \{
 *  \file       Dem_SatelliteInfo_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of SatelliteInfo subcomponent
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

#if !defined (DEM_SATELLITEINFO_IMPLEMENTATION_H)
#define DEM_SATELLITEINFO_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_SatelliteInfo_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Initial satellite info value */
#define DEM_SATELLITEINFO_INIT_VALUE           0

#define DEM_SATELLITEINFO_SATELLITE_STATUS_SIZE  DEM_1BYTE      /*!< Size of the satellite status type */
#define DEM_SATELLITEINFO_EVENTQUEUE_STATUS_POS       0              /*!< Bit offset of the event queue status */
#define DEM_SATELLITEINFO_EVENTQUEUE_STATUS_SIZE      1              /*!< Size of event queue status flag*/

#define DEM_SATELLITEINFO_EVENTQUEUE_STATUS           DEM_NBIT(DEM_SATELLITEINFO_EVENTQUEUE_STATUS_SIZE, DEM_SATELLITEINFO_EVENTQUEUE_STATUS_POS)  /*!< Bit mask for queue status bit(s) */
#define DEM_SATELLITEINFO_EVENTQUEUE_STATUS_MASK      DEM_NBIT_MASK(DEM_SATELLITEINFO_EVENTQUEUE_STATUS_SIZE, DEM_SATELLITEINFO_EVENTQUEUE_STATUS_POS,DEM_SATELLITEINFO_SATELLITE_STATUS_SIZE)  /*!< Negated bit mask for queue status bit(s) */

#define DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_POS       1              /*!< Bit offset of the prestore queue status */
#define DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_SIZE      1              /*!< Size of prestore queue status flag*/

#define DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS           DEM_NBIT(DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_SIZE, DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_POS)  /*!< Bit mask for queue status bit(s) */
#define DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_MASK      DEM_NBIT_MASK(DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_SIZE, DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS_POS,DEM_SATELLITEINFO_SATELLITE_STATUS_SIZE)  /*!< Negated bit mask for queue status bit(s) */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_SatelliteInfo_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_SatelliteInfo_SetInitStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_SetInitStatus(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo,
  CONST(uint8, AUTOMATIC) InitStatus
  )
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteInfo;
  lReturnValue.Data.InitStatus = InitStatus;
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_GetInitStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_SatelliteInfo_GetInitStatus(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  )
{
  return SatelliteInfo.Data.InitStatus;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_SetEventQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_SetEventQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo)
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteInfo;
  lReturnValue.Data.SatelliteStatus = (uint8)(lReturnValue.Data.SatelliteStatus | DEM_SATELLITEINFO_EVENTQUEUE_STATUS);
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_ResetEventQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_ResetEventQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo  )
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteInfo;
  lReturnValue.Data.SatelliteStatus = (uint8)(lReturnValue.Data.SatelliteStatus & ~DEM_SATELLITEINFO_EVENTQUEUE_STATUS);
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_GetEventQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteInfo_GetEventQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  )
{
  return (boolean)((SatelliteInfo.Data.SatelliteStatus & DEM_SATELLITEINFO_EVENTQUEUE_STATUS) != 0);
}

/* ****************************************************************************
 % Dem_SatelliteInfo_SetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_SetPrestoreQueueUpdated(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo)
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteInfo;
  lReturnValue.Data.SatelliteStatus = (uint8)(lReturnValue.Data.SatelliteStatus | DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS);
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_ResetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_ResetPrestoreQueueUpdated(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo  )
{
  Dem_SatelliteInfo_Type lReturnValue;                                                                                           /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteInfo;
  lReturnValue.Data.SatelliteStatus = (uint8)(lReturnValue.Data.SatelliteStatus & ~DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS);
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteInfo_GetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteInfo_GetPrestoreQueueUpdated(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  )
{
  return (boolean)((SatelliteInfo.Data.SatelliteStatus & DEM_SATELLITEINFO_PRESTOREQUEUE_STATUS) != 0);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_SATELLITEINFO_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteInfo_Implementation.h
 *********************************************************************************************************************/
