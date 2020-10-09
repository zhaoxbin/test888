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
/*! \addtogroup Dem_EventQueue
 *  \{
 *  \file       Dem_EventQueue_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of EventQueue subcomponent
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

#if !defined (DEM_EVENTQUEUE_TYPES_H)
#define DEM_EVENTQUEUE_TYPES_H

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
 * \defgroup  Dem_Queue_Status macros encoding queue states.
 * Macros encoding queue states.
 * \{
 */
#define DEM_EVENTQUEUE_STATE_INITIAL                  ((Dem_EventQueue_StatusType)0)  /*!< Initial queue value. */

#define DEM_EVENTQUEUE_PASSED                         ((Dem_EventQueue_StatusType)1)  /*!< Queued trigger: Passed */
#define DEM_EVENTQUEUE_PASSED_FAILED                  ((Dem_EventQueue_StatusType)2)  /*!< Queued trigger: Passed and Failed */
#define DEM_EVENTQUEUE_PASSED_FAILED_PASSED           ((Dem_EventQueue_StatusType)3)  /*!< Queued trigger: Passed, Failed and Passed */
#define DEM_EVENTQUEUE_FAILED                         ((Dem_EventQueue_StatusType)5)  /*!< Queued trigger: Failed */                     
#define DEM_EVENTQUEUE_FAILED_PASSED                  ((Dem_EventQueue_StatusType)6)  /*!< Queued trigger: Failed and Passed */
#define DEM_EVENTQUEUE_FAILED_PASSED_FAILED           ((Dem_EventQueue_StatusType)7)  /*!< Queued trigger: Failed, Passed and Failed */

/*!
 * \}
 */

#define DEM_EVENTQUEUE_ACTION                         0x07U
#define DEM_EVENTQUEUE_ACTION_MASK                    0xf8U

#define DEM_EVENTQUEUE_SIMILAR_CONDITIONS             0x08U
#define DEM_EVENTQUEUE_SIMILAR_CONDITIONS_MASK        0xf7U

#define DEM_EVENTQUEUE_FDC_TRIP                       0x10U
#define DEM_EVENTQUEUE_FDC_TRIP_MASK                  0xefU

#define DEM_EVENTQUEUE_FDC_MAX_SLC                    0x20U
#define DEM_EVENTQUEUE_FDC_MAX_SLC_MASK               0xdfU

#define DEM_EVENTQUEUE_FDC_PROCESSING                 0x40U
#define DEM_EVENTQUEUE_FDC_PROCESSING_MASK            0xafU

#define DEM_EVENTQUEUE_RESET_TESTFAILED               0x80U
#define DEM_EVENTQUEUE_RESET_TESTFAILED_MASK          0x7fU

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint8 Dem_EventQueue_StatusType;


#endif /* DEM_EVENTQUEUE_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EventQueue_Types.h
 *********************************************************************************************************************/
