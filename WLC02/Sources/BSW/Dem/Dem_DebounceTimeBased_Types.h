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
/*! \addtogroup Dem_DebounceTimeBased
 *  \{
 *  \file       Dem_DebounceTimeBased_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of DebounceTimeBased subcomponent
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

#if !defined (DEM_DEBOUNCETIMEBASED_TYPES_H)
#define DEM_DEBOUNCETIMEBASED_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_DebounceBase_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef struct Dem_DebounceTimeBased_InfoType_s Dem_DebounceTimeBased_InfoType;

/*! Data for time-based debouncing
 *  \extends Dem_DebounceBase_InfoType_s  */
struct Dem_DebounceTimeBased_InfoType_s
{
  Dem_DebounceBase_InfoType Base;                      /*!< Base class object. This attribute must come first! */
  uint16 OldTimerValue;                                /*!< [in] debounce timer before processing */
  uint16 NewTimerValue;                                /*!< [out] debounce timer after processing */
  Dem_Debounce_StatusType OldTimerState;  /*!< [in] debounce state before processing */
  Dem_Debounce_StatusType NewTimerState;  /*!< [out] debounce state after processing */
};

/*! Pointer to debounce algorithm management data */
typedef P2VAR(Dem_DebounceTimeBased_InfoType, TYPEDEF, AUTOMATIC) Dem_DebounceTimeBased_InfoPtrType;
/*! Non-writeable pointer to debounce algorithm management data */
typedef P2CONST(Dem_DebounceTimeBased_InfoType, TYPEDEF, AUTOMATIC) Dem_DebounceTimeBased_ConstInfoPtrType;

#endif /* DEM_DEBOUNCETIMEBASED_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceTimeBased_Types.h
 *********************************************************************************************************************/
