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
/*! \addtogroup Dem_ExtDataElementIF
 *  \{
 *  \file       Dem_ExtDataElementIF_Types.h
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

#if !defined (DEM_EXTDATAELEMENTIF_TYPES_H)
#define DEM_EXTDATAELEMENTIF_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_DataReportIF_Types.h"
/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*! Data byte value substituted when callbacks fail to retrieve data */
#define DEM_EXTDATAELEMENTIF_INVALID_DATA_PATTERN            (0xffU)
#define DEM_EXTDATAELEMENTIF_INVALID_DATA_SIGNED             (-1)
#define DEM_EXTDATAELEMENTIF_INVALID_DATA_1Byte              (0xffU)
#define DEM_EXTDATAELEMENTIF_INVALID_DATA_2Byte              (0xffffU)
#define DEM_EXTDATAELEMENTIF_INVALID_DATA_4Byte              (0xffffffffU)
/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef Dem_DataReportIF_CopyDidInfoType    Dem_ExtDataElementIF_CollectDidInfoType;                                             /* PRQA S 0779 */ /* MD_DEM_5.1 */
typedef Dem_DataReportIF_CopyDidInfoPtrType Dem_ExtDataElementIF_CollectDidInfoPtrType;                                          /* PRQA S 0779 */ /* MD_DEM_5.1 */

#endif /* DEM_EXTDATAELEMENTIF_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ExtDataElementIF_Types.h
 *********************************************************************************************************************/
