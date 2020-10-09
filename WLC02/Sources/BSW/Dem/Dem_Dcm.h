
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
 *         File:  Dem_Dcm.h
 *      Project:  MICROSAR Diagnostic Event Manager (Dem)
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Static public API declarations of Dem.
 *                Dynamically available APIs are declared in the generated file Rte_Dem.h
 *
 *********************************************************************************************************************/
/*!
 *  \addtogroup   Dem_Ungrouped
 *  \{
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

#if !defined (DEM_DCM_H)                                                                                                         /* COV_MSR_HEADERGUARD TX */
#define DEM_DCM_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
                                                               /* Dem itself */
/* ------------------------------------------------------------------------- */
#include "Dem.h"
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_DCM != STD_ON)
# error "Dcm API is not supported"
#endif

#include "Dem_DcmAPI_Interface.h"

#endif  /* DEM_DCM_H */
/*!
 *  \}
 */

/* ********************************************************************************************************************
 *  END OF FILE: Dem_DcmS.h
 *********************************************************************************************************************/
