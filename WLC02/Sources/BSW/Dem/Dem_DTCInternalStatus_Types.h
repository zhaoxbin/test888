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
/*! \addtogroup Dem_DTCInternalStatus
 *  \{
 *  \file       Dem_DTCInternalStatus_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of DTCInternalStatus subcomponent
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

#if !defined (DEM_DTCINTERNALSTATUS_TYPES_H)
#define DEM_DTCINTERNALSTATUS_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_EventInternalStatus_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \defgroup  Dem_DTCInternalStatusBitPosition  Macros encoding bit position for internal status
 * Macros encoding bit position for internal status
 * \{
 */
 
#define DEM_DTCINTERNALSTATUS_STORED_STATUS_POS                0  /*!< bit start position of stored status */
#define DEM_DTCINTERNALSTATUS_SUPPRESSED_DTC_POS               2  /*!< bit start position of DTC suppressed */
#define DEM_DTCINTERNALSTATUS_FDC_TOC_POS                      5 /*!< bit start position of fault detection counter threshold this cycle */
#define DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR_POS          7  /*!< bit position of user controlled warning indicator request */

/*!
 * \}
 */


/*!
 * \defgroup  Dem_Esm_StoredStatus  Encoding stored status states
 * \{
 */
 
/*! Enum to encode stored status states */
enum Dem_DTCInternal_StoredStatus
{
  Dem_DTCInternalStatus_StoredStatus_None   = (0U << DEM_DTCINTERNALSTATUS_STORED_STATUS_POS), /*!< Not stored */                 /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
  Dem_DTCInternalStatus_StoredStatus_Active = (1U << DEM_DTCINTERNALSTATUS_STORED_STATUS_POS), /*!< Active memory entry exists */ /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
  Dem_DTCInternalStatus_StoredStatus_Aging  = (2U << DEM_DTCINTERNALSTATUS_STORED_STATUS_POS), /*!< Aging memory entry exists */  /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
  Dem_DTCInternalStatus_StoredStatus_Aged   = (3U << DEM_DTCINTERNALSTATUS_STORED_STATUS_POS)  /*!< Aged memory entry exists */   /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
};
typedef enum Dem_DTCInternal_StoredStatus Dem_DTCInternal_StoredStatusType;

/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Type to store the internal status of an DTC */
typedef uint8 Dem_DTC_InternalStatusType;
/*! Type to store the extended status of an DTC */
typedef uint8 Dem_DTC_ExtendedStatusType;

#endif /* DEM_DTCINTERNALSTATUS_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCInternalStatus_Types.h
 *********************************************************************************************************************/
