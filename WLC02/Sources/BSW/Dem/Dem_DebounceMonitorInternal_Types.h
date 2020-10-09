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
 *  \addtogroup Dem_DebounceMonitorInternal
 *  \{
 *  \file       Dem_DebounceMonitorInternal_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of DebounceMonitorInternal subcomponent
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

#if !defined (DEM_DEBOUNCEMONITORINTERNAL_TYPES_H)
#define DEM_DEBOUNCEMONITORINTERNAL_TYPES_H

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

/*!
 * \defgroup  Dem_Esm_MonitorStatus  Macros encoding qualified monitor status reports
 * Macros encoding qualified monitor status reports
 * \{
 */
#define DEM_DEBOUNCE_MONITORINTERNAL_STATUS_NONE                      (0)   /*! < No result */
#define DEM_DEBOUNCE_MONITORINTERNAL_STATUS_FAILED                    (1)   /*! < Failed result */
#define DEM_DEBOUNCE_MONITORINTERNAL_STATUS_PASSED                    (2)   /*! < Passed result */
#define DEM_DEBOUNCE_MONITORINTERNAL_STATUS_FDCTHRESHOLDREACHED       (3)   /*! < Fdc threshold reached result */
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef struct Dem_DebounceMonitorInternal_InfoType_s Dem_DebounceMonitorInternal_InfoType;

/*! Data for monitor internal debouncing
  *  \extends Dem_DebounceBase_InfoType_s  */
struct Dem_DebounceMonitorInternal_InfoType_s
{
  Dem_DebounceBase_InfoType Base;  /*!< Base class object. This attribute must come first! */
  uint8 OldMonitorStatus;          /*!< [in] Last monitor result before processing */
  uint8 NewMonitorStatus;          /*!< [out] Last monitor result after processing */
};

/*! Pointer to debounce algorithm management data */
typedef P2VAR(Dem_DebounceMonitorInternal_InfoType, TYPEDEF, AUTOMATIC) Dem_DebounceMonitorInternal_InfoPtrType;                 /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
/*! Non-writeable pointer to debounce algorithm management data */
typedef P2CONST(Dem_DebounceMonitorInternal_InfoType, TYPEDEF, AUTOMATIC) Dem_DebounceMonitorInternal_ConstInfoPtrType;


#endif /* DEM_DEBOUNCEMONITORINTERNAL_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceMonitorInternal_Types.h
 *********************************************************************************************************************/
