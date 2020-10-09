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
/*! \ingroup    Dem_Satellite
 *  \defgroup   Dem_SatelliteInfo Satellite Info
 *  \{
 *  \file       Dem_SatelliteInfo_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of SatelliteInfo subcomponent
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

#if !defined (DEM_SATELLITEINFO_INTERFACE_H)
#define DEM_SATELLITEINFO_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_SatelliteInfo_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_SatelliteInfo_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_SatelliteInfo_SetInitStatus
 *****************************************************************************/
/*!
 * \brief         Set the given init status into the satellite info object.
 *
 * \details       Set the given init status into the satellite info object.
 *
 * \param[in]     SatelliteInfo
 *                The data object to modify
 * \param[in]     InitStatus
 *                The data to write to SatelliteInfo.
 *
 * \return        The modified satellite info object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_SetInitStatus(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo,
  CONST(uint8, AUTOMATIC) InitStatus
  );

/* ****************************************************************************
 * Dem_SatelliteInfo_GetInitStatus
 *****************************************************************************/
/*!
 * \brief         Reads the init status from the satellite info object.
 *
 * \details       Reads the init status from the satellite info object.
 *
 * \param[in]     SatelliteInfo
 *                The data object to read from.
 *
 * \return        The requested data.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_SatelliteInfo_GetInitStatus(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  );

/* ****************************************************************************
 * Dem_SatelliteInfo_ResetEventQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Unset the queue updated flag in the satellite info object.
 *
 * \details       Unset the queue updated flag in the satellite info object.
 *
 * \param[in]     SatelliteInfo
 *                The data object to modify
 *
 * \return        The modified satellite info object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_ResetEventQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  );

/* ****************************************************************************
 * Dem_SatelliteInfo_SetEventQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Set the queue updated flag in the satellite info object.
 *
 * \details       Set the queue updated flag in the satellite info object.
 *
 * \param[in]     SatelliteInfo
 *                The data object to modify
 *
 * \return        The modified satellite info object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_SetEventQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  );

/* ****************************************************************************
 * Dem_SatelliteInfo_GetEventQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Reads the queue updated flag from the satellite info object.
 *
 * \details       Reads the queue updated flag from the satellite info object.
 *
 * \param[in]     SatelliteInfo
 *                The data object to read from.
 *
 * \return        The requested flag.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteInfo_GetEventQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  );

/* ****************************************************************************
 * Dem_SatelliteInfo_ResetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Unset the prestore queue updated flag in the satellite info object.
 *
 * \details       Unset the prestore queue updated flag in the satellite info object.
 *
 * \param[in]     SatelliteInfo
 *                The data object to modify
 *
 * \return        The modified satellite info object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_ResetPrestoreQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  );

/* ****************************************************************************
 * Dem_SatelliteInfo_SetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Set the prestore queue updated flag in the satellite info object.
 *
 * \details       Set the prestore queue updated flag in the satellite info object.
 *
 * \param[in]     SatelliteInfo
 *                The data object to modify
 *
 * \return        The modified satellite info object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_SatelliteInfo_SetPrestoreQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  );

/* ****************************************************************************
 * Dem_SatelliteInfo_GetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Reads the prestore queue updated flag from the satellite info object.
 *
 * \details       Reads the prestore queue updated flag from the satellite info object.
 *
 * \param[in]     SatelliteInfo
 *                The data object to read from.
 *
 * \return        The requested flag.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteInfo_GetPrestoreQueueUpdated(
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  SatelliteInfo
  );
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_SATELLITEINFO_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteInfo_Interface.h
 *********************************************************************************************************************/
