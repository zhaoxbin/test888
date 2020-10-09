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
 *              File: Os_Link_Core0_Stacks.ld
 *   Generation Time: 2020-02-08 12:42:12
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

/**********************************************************************************************************************
 *  STACK SECTIONS
 *********************************************************************************************************************/

#if defined ( OS_LINK_KERNEL_STACKS )
_OS_CORE0_STACKS_START = .;
__OS_CORE0_STACKS_START = .;

/* Stack: OsCore0_Error (1024 Byte) */
.OS_STACK_OSCORE0_ERROR_VAR_NOINIT ALIGN(4) :> .
_OS_STACK_OSCORE0_ERROR_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_ERROR_VAR_NOINIT);
_OS_STACK_OSCORE0_ERROR_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_ERROR_VAR_NOINIT) - 1;

/* Stack: OsCore0_Init (1024 Byte) */
.OS_STACK_OSCORE0_INIT_VAR_NOINIT ALIGN(4) :> .
_OS_STACK_OSCORE0_INIT_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_INIT_VAR_NOINIT);
_OS_STACK_OSCORE0_INIT_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_INIT_VAR_NOINIT) - 1;

/* Stack: OsCore0_Isr_Core (1024 Byte) */
.OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT ALIGN(4) :> .
_OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT);
_OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT) - 1;

/* Stack: OsCore0_Kernel (1024 Byte) */
.OS_STACK_OSCORE0_KERNEL_VAR_NOINIT ALIGN(4) :> .
_OS_STACK_OSCORE0_KERNEL_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_KERNEL_VAR_NOINIT);
_OS_STACK_OSCORE0_KERNEL_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_KERNEL_VAR_NOINIT) - 1;

/* Stack: OsCore0_Task_Prio0 (1024 Byte) */
.OS_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT ALIGN(4) :> .
_OS_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT);
_OS_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT) - 1;

/* Stack: OsCore0_Task_Prio4294967295 (1024 Byte) */
.OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT ALIGN(4) :> .
_OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_START = ADDR(.OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT);
_OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT) - 1;

/* Stack: OsTask_APP (1024 Byte) */
.OS_STACK_OSTASK_APP_VAR_NOINIT ALIGN(4) :> .
_OS_STACK_OSTASK_APP_VAR_NOINIT_START = ADDR(.OS_STACK_OSTASK_APP_VAR_NOINIT);
_OS_STACK_OSTASK_APP_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSTASK_APP_VAR_NOINIT) - 1;

/* Stack: OsTask_BSW_SCHM (1024 Byte) */
.OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT ALIGN(4) :> .
_OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_START = ADDR(.OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT);
_OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_END = ENDADDR(.OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT) - 1;



_OS_CORE0_STACKS_END = .-1;
__OS_CORE0_STACKS_END = .-1;
#endif

#ifdef OS_LINK_KERNEL_STACKS
# undef OS_LINK_KERNEL_STACKS
#endif


