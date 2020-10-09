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
/*! \addtogroup Dem_ClearDTC
 *  \{
 *  \file       Dem_ClearDTC_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of ClearDTC subcomponent
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

#if !defined (DEM_CLEARDTC_TYPES_H)
#define DEM_CLEARDTC_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_DTCSelector_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
#define DEM_CLEARDTC_HANDLE_INVALID              0xffU     /*!< Value for an invalid clear DTC handle */

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Type to identify clear a operation handler */
typedef uint8 Dem_ClearDTC_HandleType;

/*!
* \defgroup  Dem_ClearDTC_StatusType Dem_ClearDTC_StatusType
* \{
*/
/*! Type to encode the state of a clear operation */
typedef uint8 Dem_ClearDTC_StatusType;
#define DEM_CLEARDTC_STATUS_IDLE                 0  /*!< No clear operation in progress */
#define DEM_CLEARDTC_STATUS_PENDING              1  /*!< Currently clearing of DTCs is in progress */
#define DEM_CLEARDTC_STATUS_DONE                 2  /*!< ClearDTC has finished sucessfully */
#define DEM_CLEARDTC_STATUS_FAILED               3  /*!< ClearDTC has not finished sucessfully */
#define DEM_CLEARDTC_STATUS_NV_ERROR             4  /*!< NV write error during ClearDTC */

/*!
* \}
*/

/*! Type to store the state of a clear operation */
struct Dem_ClearDTC_DataType_s
{
  Dem_ClearDTC_StatusType ClearDTCStatus;        /*!< The status of the clear operation */
  Dem_DTCSelector_HandleType DTCSelector;
};

/*! Type for the state of a clear operation */
typedef struct Dem_ClearDTC_DataType_s Dem_ClearDTC_DataType;

#endif /* DEM_CLEARDTC_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClearDTC_Types.h
 *********************************************************************************************************************/
