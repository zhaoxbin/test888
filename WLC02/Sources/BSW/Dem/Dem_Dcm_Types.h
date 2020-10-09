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
/*!
 *  \addtogroup Dem_Dcm
 *  \{
 *  \file       Dem_Dcm_Types.h
 *  \brief      Diagnostic Event Manager (Dem) Type and Macro definition file
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

#if !defined (DEM_DCM_TYPES_H)
#define DEM_DCM_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*!
 * \defgroup  Dem_Dcm_ExtendedDataRecord_Value Extended Data Records
 * List of special extended data record values
 * \{
 */
#define DEM_DCM_EXTENDEDDATARECORD_INVALID         (0x00u)     /*! Invalid extended record */
#define DEM_DCM_EXTENDEDDATARECORD_FIRST           (0x01u)     /*! The first valid extended record */
#define DEM_DCM_EXTENDEDDATARECORD_FIRST_OBD       (0x90u)     /*! The first valid OBD extended record */
#define DEM_DCM_EXTENDEDDATARECORD_LAST            (0xEFu)     /*! The last valid extended record */
#define DEM_DCM_EXTENDEDDATARECORD_FIRST_RESERVED  (0xF0u)     /*! The first reserved extended record */
#define DEM_DCM_EXTENDEDDATARECORD_OBD             (0xFEu)     /*! Select all OBD records */
#define DEM_DCM_EXTENDEDDATARECORD_ALL             (0xFFu)     /*! Select all extended records */
/*!
 * \}
 */
 
/*!
 * \defgroup  Dem_Dcm_SnapshotDataRecord_Value Snapshot data Records
 * List of special snapshot data record values
 * \{
 */
#define DEM_DCM_SNAPSHOTDATARECORD_TMC_FIRST        (0x10u)     /*! The first valid TMC time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_TMC_LAST         (0x4Fu)     /*! The last valid TMC time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_TMC_FAST_FIRST   (0x10u)     /*! The first valid TMC fast time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_TMC_FAST_LAST    (0x2Fu)     /*! The last valid TMC fast time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_TMC_NORMAL_FIRST (0x30u)     /*! The first valid TMC normal time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_TMC_NORMAL_LAST  (0x4Fu)     /*! The last valid TMC normal time series record */
#define DEM_DCM_SNAPSHOTDATARECORD_OBD              (0x00u)     /*! OBD record */
#define DEM_DCM_SNAPSHOTDATARECORD_VCC              (0x30u)     /*! VCC record */
#define DEM_DCM_SNAPSHOTDATARECORD_STANDARD_FIRST   (0x01u)     /*! The first vaild standard snapshot data record */
#define DEM_DCM_SNAPSHOTDATARECORD_STANDARD_LAST    (0xFEu)     /*! The last valid standard snapshot data record */
#define DEM_DCM_SNAPSHOTDATARECORD_ALL              (0xFFu)     /*! All snapshot data records */
/*!
* \}
*/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/*! Filter data for IUMPR requests */
struct Dem_Dcm_IumprFilterInfoType_s
{
  uint16      FirstEvent;  /*!< First event matching the request */
  uint16      CurrentEvent;  /*!< Current iterator position */
  uint16      LastEvent;  /*!< Last event matching the request */
  uint8       ReadinessGroup;  /*!< Filtered readiness group */
};

/*! Filter data type for IUMPR requests */
typedef struct Dem_Dcm_IumprFilterInfoType_s Dem_Dcm_IumprFilterInfoType;
#endif

#endif /* DEM_DCM_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Dcm_Types.h
 *********************************************************************************************************************/
