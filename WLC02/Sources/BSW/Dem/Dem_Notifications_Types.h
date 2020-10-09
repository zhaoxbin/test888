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
/*! \addtogroup Dem_Notifications
 *  \{
 *  \file       Dem_Notifications_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    
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

#if !defined (DEM_NOTIFICATIONS_TYPES_H)
#define DEM_NOTIFICATIONS_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \defgroup  Dem_Callback_Reasons  Macros encoding reasons for calling notifications
 * Macros encoding reasons for calling notifications
 * \{
 */
#define DEM_NOTIFICATIONS_DTC_CLEAR              (0U)  /*!< DTC was cleared */
#define DEM_NOTIFICATIONS_DTC_UPDATED            (1U)  /*!< DTC was updated */
#define DEM_NOTIFICATIONS_DTC_AGED               (2U)  /*!< DTC was aged */
#define DEM_NOTIFICATIONS_DTC_HEALED             (3U)  /*!< DTC was healed */
#define DEM_NOTIFICATIONS_DTC_DISPLACED          (4U)  /*!< DTC was displaced */
#define DEM_NOTIFICATIONS_DTC_REINIT             (5U)  /*!< DTC operating cycle was restarted */
#define DEM_NOTIFICATIONS_CYCLE_QUALIFIED        (6U)  /*!< DTC operating cycle was qualified */
#define DEM_NOTIFICATIONS_USER_WIR               (7U)  /*!< DTC WIR bit was set by application API */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#endif /* DEM_NOTIFICATIONS_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Notifications_Types.h
 *********************************************************************************************************************/
