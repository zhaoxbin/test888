/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Os
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Hal_Cfg.h
 *   Generation Time: 2020-06-20 15:53:47
 *           Project: WLC - Version 1.0
 *          Delivery: CBD1900162_D00
 *      Tool Version: DaVinci Configurator (beta) 5.19.29
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 ! BETA VERSION                                                                                                       !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 ! This version of DaVinci Configurator Pro and/or the related Basic Software Package is BETA software.               !
 ! BETA Software is basically operable, but not sufficiently tested, verified and/or qualified for use in series      !
 ! production and/or in vehicles operating on public or non-public roads.                                             !
 ! In particular, without limitation, BETA Software may cause unpredictable ECU behavior, may not provide all         !
 ! functions necessary for use in series production and/or may not comply with quality requirements which are         !
 ! necessary according to the state of the art. BETA Software must not be used in series production.                  !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**********************************************************************************************************************/


                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

#ifndef OS_HAL_CFG_H
# define OS_HAL_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! HAL configuration major version identification. */
# define OS_CFG_HAL_MAJOR_VERSION                (2u)

/*! HAL configuration minor version identification. */
# define OS_CFG_HAL_MINOR_VERSION                (20u)

/* ISR core and level definitions */
# define OS_ISR_CANISRGLOBALSTATUS_CORE      (0)
# define OS_ISR_CANISRGLOBALSTATUS_LEVEL     (0)
# define OS_ISR_CANISRRXFIFO_CORE      (0)
# define OS_ISR_CANISRRXFIFO_LEVEL     (0)
# define OS_ISR_CANISRSTATUS_0_CORE      (0)
# define OS_ISR_CANISRSTATUS_0_LEVEL     (0)
# define OS_ISR_CANISRTX_0_CORE      (0)
# define OS_ISR_CANISRTX_0_LEVEL     (0)
# define OS_ISR_CANISRWAKEUP_0_CORE      (0)
# define OS_ISR_CANISRWAKEUP_0_LEVEL     (0)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_CORE      (0)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_LEVEL     (0)

/* Hardware counter timing macros */

/* Counter timing macros and constants: SystemTimer */
# define OSMAXALLOWEDVALUE_SystemTimer     (2147483647uL) /* 0x7FFFFFFFuL */
# define OSMINCYCLE_SystemTimer            (1uL)
# define OSTICKSPERBASE_SystemTimer        (1uL)
# define OSTICKDURATION_SystemTimer        (1000000uL)

/* OSEK compatibility for the system timer. */
# define OSMAXALLOWEDVALUE     (OSMAXALLOWEDVALUE_SystemTimer)
# define OSMINCYCLE            (OSMINCYCLE_SystemTimer)
# define OSTICKSPERBASE        (OSTICKSPERBASE_SystemTimer)
# define OSTICKDURATION        (OSTICKDURATION_SystemTimer)

/*! Macro OS_NS2TICKS_SystemTimer was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer(x)     ( (TickType) (((((uint32)(x)) * 1) + 500000) / 1000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer(x)     ( (TickType) (((((uint32)(x)) * 1) + 500) / 1000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer was approximated with a deviation of 1.1102230246251565E-10ppm. */
# define OS_TICKS2US_SystemTimer(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer(x)     ( (TickType) (((((uint32)(x)) * 1) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer(x)     ( (TickType) (((((uint32)(x)) * 1000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 500) / 1000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */








/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_HAL_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Cfg.h
 *********************************************************************************************************************/
