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
/*! \addtogroup Dem_EnableCondition
 *  \{
 *  \file       Dem_EnableCondition_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
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

#if !defined (DEM_ENABLECONDITION_TYPES_H)
#define DEM_ENABLECONDITION_TYPES_H

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

/*! Handle for enable condition 'ControlDTCSetting' */
#define DEM_ENABLECONDITION_CONTROLDTCSETTING    0

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/*! Test the active state of an enable condition group */
#define DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_ACTIVE(State)            (((State) & 0x01U) != 0)                          /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set the active state of an enable condition group */
#define DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_ACTIVE(State)             ((uint8)((State) | 0x01U))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset the active state of an enable condition group */
#define DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_ACTIVE(State)           ((uint8)((State) & 0xfeU))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test the 'queued disable' state of an enable condition group */
#define DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_QUEUE_DISABLE(State)     (((State) & 0x02U) != 0)                          /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set the 'queued disable' state of an enable condition group */
#define DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_QUEUE_DISABLE(State)      ((uint8)((State) | 0x02U))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset the 'queued disable' state of an enable condition group */
#define DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_QUEUE_DISABLE(State)    ((uint8)((State) & 0xfdU))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test the 'queued enable' state of an enable condition group */
#define DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_QUEUE_ENABLE(State)      (((State) & 0x04U) != 0)                          /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set the 'queued enable' state of an enable condition group */
#define DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_QUEUE_ENABLE(State)       ((uint8)((State) | 0x04U))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset the 'queued enable' state of an enable condition group */
#define DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_QUEUE_ENABLE(State)     ((uint8)((State) & 0xfbU))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test the 'process disable' state of an enable condition group */
#define DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_PROCESS_DISABLE(State)   (((State) & 0x08U) != 0)                          /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set the 'process disable' state of an enable condition group */
#define DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_PROCESS_DISABLE(State)    ((uint8)((State) | 0x08U))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset the 'process disable' state of an enable condition group */
#define DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_PROCESS_DISABLE(State)  ((uint8)((State) & 0xf7U))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test the 'process enable' state of an enable condition group */
#define DEM_ENABLECONDITION_TEST_ENABLECONDITIONGROUP_PROCESS_ENABLE(State)    (((State) & 0x10U) != 0)                          /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set the 'process enable' state of an enable condition group */
#define DEM_ENABLECONDITION_SET_ENABLECONDITIONGROUP_PROCESS_ENABLE(State)     ((uint8)((State) | 0x10U))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset the 'process enable' state of an enable condition group */
#define DEM_ENABLECONDITION_RESET_ENABLECONDITIONGROUP_PROCESS_ENABLE(State)   ((uint8)((State) & 0xefU))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Iterator type for iteration over enable conditions of an enable condition group */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventEnableConditionGroupIterType;

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

#endif /* DEM_ENABLECONDITION_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EnableCondition_Types.h
 *********************************************************************************************************************/
