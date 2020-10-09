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
 *              File: Os_MemMap_StacksInt.h
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

                                                                                                                        /* PRQA S 0883 */ /* MD_Os_Dir4.10_0883_MemMap */

/**********************************************************************************************************************
 *  STACK SECTIONS
 *********************************************************************************************************************/

#ifdef OS_START_SEC_STACK_OSCORE0_ERROR_VAR_NOINIT_UNSPECIFIED
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_STACK_OSCORE0_ERROR_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs startdata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs section bss = ".OS_STACK_OSCORE0_ERROR_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma alignvar(4) /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_START_SEC_STACK_OSCORE0_ERROR_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_STOP_SEC_STACK_OSCORE0_ERROR_VAR_NOINIT_UNSPECIFIED
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef OS_STACK_OSCORE0_ERROR_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_STACK_OSCORE0_ERROR_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_STACK_OSCORE0_ERROR_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs section bss = default /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs enddata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_STOP_SEC_STACK_OSCORE0_ERROR_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_START_SEC_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs startdata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs section bss = ".OS_STACK_OSCORE0_INIT_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma alignvar(4) /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_START_SEC_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_STOP_SEC_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef OS_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs section bss = default /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs enddata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_STOP_SEC_STACK_OSCORE0_INIT_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_START_SEC_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs startdata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs section bss = ".OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma alignvar(4) /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_START_SEC_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_STOP_SEC_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs section bss = default /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs enddata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_STOP_SEC_STACK_OSCORE0_ISR_CORE_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_START_SEC_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs startdata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs section bss = ".OS_STACK_OSCORE0_KERNEL_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma alignvar(4) /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_START_SEC_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_STOP_SEC_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef OS_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs section bss = default /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs enddata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_STOP_SEC_STACK_OSCORE0_KERNEL_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_START_SEC_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT_UNSPECIFIED
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs startdata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs section bss = ".OS_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma alignvar(4) /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_START_SEC_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT_UNSPECIFIED
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef OS_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs section bss = default /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs enddata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO0_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_START_SEC_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs startdata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs section bss = ".OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma alignvar(4) /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_START_SEC_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs section bss = default /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs enddata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_STOP_SEC_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_START_SEC_STACK_OSTASK_APP_VAR_NOINIT_UNSPECIFIED
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_STACK_OSTASK_APP_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs startdata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs section bss = ".OS_STACK_OSTASK_APP_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma alignvar(4) /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_START_SEC_STACK_OSTASK_APP_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_STOP_SEC_STACK_OSTASK_APP_VAR_NOINIT_UNSPECIFIED
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef OS_STACK_OSTASK_APP_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_STACK_OSTASK_APP_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_STACK_OSTASK_APP_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs section bss = default /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs enddata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_STOP_SEC_STACK_OSTASK_APP_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_START_SEC_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_UNSPECIFIED
# ifdef OS_MEMMAP_SECTION_OPEN
#  error A MemMap section is already open. Nesting is not supported.
# endif
# define OS_MEMMAP_SECTION_OPEN
# define OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_UNSPECIFIED_OPEN
# ifndef MEMMAP_ERROR
#  error Each MemMap include may only perform one action. Include MemMap.h separately for each action.
# endif
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs startdata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs section bss = ".OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma alignvar(4) /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_START_SEC_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

#ifdef OS_STOP_SEC_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_UNSPECIFIED
# ifndef OS_MEMMAP_SECTION_OPEN
#  error No MemMap section is currently opened.
# endif
# undef OS_MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Section OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_UNSPECIFIED is currently not opened and so cannot be closed.
# endif
# undef OS_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# pragma ghs section bss = default /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma ghs enddata /* PRQA S 3116 */ /* MD_MSR_Pragma */
# undef OS_STOP_SEC_STACK_OSTASK_BSW_SCHM_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

/* PRQA S 0883 */ /* MD_Os_Dir4.10_0883_MemMap */
