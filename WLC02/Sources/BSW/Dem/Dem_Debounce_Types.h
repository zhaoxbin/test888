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
 *  \addtogroup Dem_Debounce
 *  \{
 *  \file       Dem_Debounce_Types.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public types of Debounce subcomponent
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

#if !defined (DEM_DEBOUNCE_TYPES_H)
#define DEM_DEBOUNCE_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

                                                           /* Required types */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceBase_Types.h"
#include "Dem_DebounceCounterBased_Types.h"
#include "Dem_DebounceTimeBased_Types.h"
#include "Dem_DebounceMonitorInternal_Types.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! General debounce type. */
typedef union Dem_Debounce_InfoType_u Dem_Debounce_InfoType;

/*! General debounce type. */
union Dem_Debounce_InfoType_u
{                                                                                                                                /* PRQA S 0750 */ /* MD_MSR_18.4 */
  Dem_DebounceBase_InfoType InvalidDebounce;                /*!< Used in case that the selected debounce algorithm is invalid. */
  Dem_DebounceCounterBased_InfoType CounterBased;           /*!< Data storage for counter based debouncing. */
  Dem_DebounceMonitorInternal_InfoType MonitorInternal;     /*!< Data storage for monitor internal debouncing. */
  Dem_DebounceTimeBased_InfoType TimeBased;                 /*!< Data storage for time based debouncing. */
};


#endif /* DEM_DEBOUNCE_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Debounce_Types.h
 *********************************************************************************************************************/
