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
/*! \addtogroup Dem_OperationCycle
 *  \{
 *  \file       Dem_OperationCycle_Types.h
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

#if !defined (DEM_OPERATIONCYCLE_TYPES_H)
#define DEM_OPERATIONCYCLE_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
#define DEM_OPERATIONCYCLE_CYCLE_STOPPED         (0x01U)     /*!< 0x01: Cycle state change to stopped */
#define DEM_OPERATIONCYCLE_CYCLE_STARTED         (0x02U)     /*!< 0x02: Cycle state change to started */
#define DEM_OPERATIONCYCLE_CYCLE_RESTARTED       (0x03U)     /*!< 0x03: Cycle state change, stop then start */



/*!
 * \defgroup  Dem_Esm_CycleCountValues  Macros encoding magic cycle counter values
 * Macros encoding magic cycle counter values
 * \{
 */
#define DEM_OPERATIONCYCLE_CYCLECOUNT_MAX        (0xeeeeU)  /*!< maximum cycle counter */
#define DEM_OPERATIONCYCLE_CYCLECOUNT_LATCHED    (0xeeffU)  /*!< latched cycle counter */
#define DEM_OPERATIONCYCLE_CYCLECOUNT_AGED       (0xffeeU)  /*!< event is aged */
#define DEM_OPERATIONCYCLE_CYCLECOUNT_INVALID    (0xffffU)  /*!< no cycle counter available */
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/
/*! Test DCY qualified state of OBD cycle status */
# define DEM_OPERATIONCYCLE_TEST_DCY_QUALIFIED(State)       (((State) & 0x01U) != 0)                                             /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set DCY qualified state of OBD cycle status */
# define DEM_OPERATIONCYCLE_SET_DCY_QUALIFIED(State)        ((uint8)((State) | 0x01U))                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset DCY qualified state of OBD cycle status */
# define DEM_OPERATIONCYCLE_RESET_DCY_QUALIFIED(State)      ((uint8)((State) & 0xfeU))                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test PFC conditions reached state of OBD cycle status */
# define DEM_OPERATIONCYCLE_TEST_PFC_CYCLE(State)           (((State) & 0x02U) != 0)                                             /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set PFC conditions reached state of OBD cycle status */
# define DEM_OPERATIONCYCLE_SET_PFC_CYCLE(State)            ((uint8)((State) | 0x02U))                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset PFC conditions reached state of OBD cycle status */
# define DEM_OPERATIONCYCLE_RESET_PFC_CYCLE(State)          ((uint8)((State) & 0xfdU))                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */

# if (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON)
/*! Test warm-up conditions reached state of OBD cycle status */
#  define DEM_OPERATIONCYCLE_TEST_WARMUP_CYCLE(State)       (((State) & 0x04U) != 0)                                             /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set warm-up conditions reached state of OBD cycle status */
#  define DEM_OPERATIONCYCLE_SET_WARMUP_CYCLE(State)        ((uint8)((State) | 0x04U))                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset warm-up conditions reached state of OBD cycle status */
#  define DEM_OPERATIONCYCLE_RESET_WARMUP_CYCLE(State)      ((uint8)((State) & 0xfbU))                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
# endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/*! Test if qualification of DCY is pending*/
# define Dem_OperationCycle_IsPendingDcyCycle()           (Dem_Queue_DcyCycleFlag)                                               /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set qualification of DCY pending */
# define Dem_OperationCycle_SetPendingDcyCycle()          (Dem_Queue_DcyCycleFlag = TRUE)                                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset pending state of DCY qualification */
# define Dem_OperationCycle_ClearPendingDcyCycle()        (Dem_Queue_DcyCycleFlag = FALSE)                                       /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Get OBD cycle state */
# define Dem_OperationCycle_GetObdCycleStates()           (Dem_Cfg_AdminData.ObdCycleState)                                      /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set OBD cycle state */
# define Dem_OperationCycle_SetObdCycleStates(Value)      (Dem_Cfg_AdminData.ObdCycleState = (Value))                            /* PRQA S 3453 */ /* MD_MSR_19.7 */
#endif


/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#endif /* DEM_OPERATIONCYCLE_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_OperationCycle_Types.h
 *********************************************************************************************************************/
