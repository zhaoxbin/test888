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
 *              File: Os_Types_Lcfg.h
 *   Generation Time: 2020-09-01 09:22:57
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

#ifndef OS_TYPES_LCFG_H
# define OS_TYPES_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */

/* Os hal dependencies */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* OS-Application identifiers. */
#define SystemApplication_OsCore0 SystemApplication_OsCore0

/* Trusted function identifiers. */

/* Non-trusted function identifiers. */

/* Fast trusted function identifiers. */

/* Task identifiers. */
#define IdleTask_OsCore0 IdleTask_OsCore0
#define OsTask OsTask
#define OsTask_APP OsTask_APP
#define OsTask_BSW_SCHM OsTask_BSW_SCHM

/* Category 2 ISR identifiers. */
#define CanIsrGlobalStatus CanIsrGlobalStatus
#define CanIsrRxFifo CanIsrRxFifo
#define CanIsrStatus_0 CanIsrStatus_0
#define CanIsrTx_0 CanIsrTx_0
#define CanIsrWakeup_0 CanIsrWakeup_0
#define CounterIsr_SystemTimer CounterIsr_SystemTimer

/* Alarm identifiers. */
#define Rte_Al_TE2_OsTask_BSW_SCHM_0_10ms Rte_Al_TE2_OsTask_BSW_SCHM_0_10ms
#define Rte_Al_TE2_OsTask_BSW_SCHM_0_20ms Rte_Al_TE2_OsTask_BSW_SCHM_0_20ms
#define Rte_Al_TE2_OsTask_BSW_SCHM_0_5ms Rte_Al_TE2_OsTask_BSW_SCHM_0_5ms
#define Rte_Al_TE_OsTask_APP_0_10ms Rte_Al_TE_OsTask_APP_0_10ms

/* Counter identifiers. */
#define SystemTimer SystemTimer

/* ScheduleTable identifiers. */

/* Resource identifiers. */
#define OsResource OsResource

/* Spinlock identifiers. */

/* Peripheral identifiers. */

/* Barrier identifiers. */

/* Trace thread identifiers (Tasks and ISRs inclusive system objects). */

/* Trace spinlock identifiers (All spinlocks inclusive system objects). */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! OS-Application identifiers. */
typedef enum
{
  SystemApplication_OsCore0 = 0, /* 0x00000001 */  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_APPID_COUNT = 1,
  INVALID_OSAPPLICATION = OS_APPID_COUNT
} ApplicationType;

/*! Trusted function identifiers. */
typedef enum
{
  OS_TRUSTEDFUNCTIONID_COUNT = 0
} TrustedFunctionIndexType;

/*! Non-trusted function identifiers. */
typedef enum
{
  OS_NONTRUSTEDFUNCTIONID_COUNT = 0
} Os_NonTrustedFunctionIndexType;

/*! Fast trusted function identifiers. */
typedef enum
{
  OS_FASTTRUSTEDFUNCTIONID_COUNT = 0
} Os_FastTrustedFunctionIndexType;

/*! Task identifiers. */
typedef enum
{
  IdleTask_OsCore0 = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask = 1,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_APP = 2,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OsTask_BSW_SCHM = 3,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_TASKID_COUNT = 4,
  INVALID_TASK = OS_TASKID_COUNT
} TaskType;

/*! Category 2 ISR identifiers. */
typedef enum
{
  CanIsrGlobalStatus = 0,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CanIsrRxFifo = 1,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CanIsrStatus_0 = 2,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CanIsrTx_0 = 3,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CanIsrWakeup_0 = 4,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  CounterIsr_SystemTimer = 5,   /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_ISRID_COUNT = 6,
  INVALID_ISR = OS_ISRID_COUNT
} ISRType;

/*! Alarm identifiers. */
typedef enum
{
  Rte_Al_TE2_OsTask_BSW_SCHM_0_10ms = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE2_OsTask_BSW_SCHM_0_20ms = 1,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE2_OsTask_BSW_SCHM_0_5ms = 2,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  Rte_Al_TE_OsTask_APP_0_10ms = 3,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_ALARMID_COUNT = 4
} AlarmType;

/*! Counter identifiers. */
typedef enum
{
  SystemTimer = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_COUNTERID_COUNT = 1
} CounterType;

/*! ScheduleTable identifiers. */
typedef enum
{
  OS_SCHTID_COUNT = 0
} ScheduleTableType;

/*! Resource identifiers. */
typedef enum
{
  OsResource = 0,  /* PRQA S 0784 */ /* MD_Os_Rule5.5_0784 */
  OS_RESOURCEID_COUNT = 1
} ResourceType;

/*! Spinlock identifiers. */
typedef enum
{
  OS_SPINLOCKID_COUNT = 0,
  INVALID_SPINLOCK = OS_SPINLOCKID_COUNT
} SpinlockIdType;

/*! Peripheral identifiers. */
typedef enum
{
  OS_PERIPHERALID_COUNT = 0
} Os_PeripheralIdType;

/*! Barrier identifiers. */
typedef enum
{
  OS_BARRIERID_COUNT = 0
} Os_BarrierIdType;

/*! Trace thread identifiers (Tasks and ISRs inclusive system objects). */
typedef enum
{
  OS_TRACE_THREADID_COUNT = 0,
  OS_TRACE_INVALID_THREAD = OS_TRACE_THREADID_COUNT + 1
} Os_TraceThreadIdType;

/*! Trace spinlock identifiers (All spinlocks inclusive system objects). */
typedef enum
{
  OS_TRACE_NUMBER_OF_CONFIGURED_SPINLOCKS = OS_SPINLOCKID_COUNT,
  OS_TRACE_NUMBER_OF_ALL_SPINLOCKS = OS_SPINLOCKID_COUNT + 0u,  /* PRQA S 4521 */ /* MD_Os_Rule10.1_4521 */
  OS_TRACE_INVALID_SPINLOCK = OS_TRACE_NUMBER_OF_ALL_SPINLOCKS + 1
} Os_TraceSpinlockIdType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_TYPES_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Types_Lcfg.h
 *********************************************************************************************************************/
