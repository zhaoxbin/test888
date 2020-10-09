/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 *  \addtogroup Os_Hal_Entry
 *  \{
 *
 *  \file       Os_Hal_Entry.asm
 *  \brief      This component handles hardware exceptions and interrupts.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

                                                                                                                        /* PRQA S 0777 EOF */ /* MD_MSR_Rule5.1 */
#if 0
#define OS_HAL_ENTRY_SOURCE

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

/* Os module dependencies */
#include "Os_Cfg.h"

/* Os Hal dependencies */
#include "Os_Hal_Entry_Cfg.h"
#include "Os_Hal_Compiler_ASM.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/*! \brief Syscall table
 *  \details The syscall table contains only the unhandledSysCall handler because syscalls are not used within the OS.
 */
OS_HAL_ASM_SECTION_CONST(OS_CONST)
OS_HAL_ASM_ALIGN(32)
OS_HAL_ASM_GLOBAL(OS_SYSCALL_TABLE)
OS_HAL_ASM_LABEL(OS_SYSCALL_TABLE)
OS_HAL_ASM_SYSCALL_WORD(_Os_Hal_UnhandledSysCall,_OS_SYSCALL_TABLE)


#define OS_START_SEC_CODE
#include "Os_MemMap_OsCode.h"                                                                                           /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Os_Irq_Isr()
 **********************************************************************************************************************/
/*! \brief      This handler is triggered, if a configured category 2 interrupt occurs.
 *  \details    This handler shall save a minimal set of registers, to be able to call a C-Function and restore
 *              the previous state afterwards. The rest is performed by the kernel's Os_IsrRun() function.
 *
 *              This handler typically has to save the following information:
 *              - Scratch Registers
 *              - Previous Program Counter
 *              - Previous Link Register
 *              - Previous Interrupt Level
 *
 *              The kernel expects Os_IsrRun() to be called on the interrupted stack.
 *              All handlers of this type shall have the following naming convention: Os_Irq_Isr_<Specific-Suffix>.
 *              The <Specific-Suffix> can be either the interrupt vector number or the interrupt source name.
 *              The kernel expects that Os_IsrRun() is executed on the interrupt priority level of the associated ISR2.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 *  \pre          Interrupts disabled.
 **********************************************************************************************************************/
/*!
 * \internal
 *  - #10 Store interrupted context to stack.
 *  - #20 Enter Os Isr handler
 *  - #30 Enter Isr epilogue
 *  - #40 Restore interrupted context.
 *  - #50 Return to interrupted context.
 * \endinternal
 */
OS_HAL_ASM_SECTION_TEXT(OS_CODE)
OS_HAL_ASM_ALIGN(4)
OS_HAL_ASM_GLOBAL(Os_Irq_Isr)
OS_HAL_ASM_LABEL(Os_Irq_Isr)
/* #10 Store interrupted context to stack. */
  OS_HAL_ASM_PUSHSP(r30,r31)
  stsr    0, r11, 0          /* store content of EIPC to r11 */
  stsr    1, r12, 0          /* store content of EIPSW to r12 */
  OS_HAL_ASM_PUSHSP(r11,r12)
#if defined (OS_HAL_ASM_FPU_USAGE)
  stsr    6, r11, 0          /* store content of FPSR to r11 */
  stsr    7, r12, 0          /* store content of FPEPC to r12 */
  OS_HAL_ASM_PUSHSP(r11,r12)
#endif /* defined (OS_HAL_ASM_FPU_USAGE) */
/* #20 Enter Os Isr handler. */
  jarl    _Os_IsrRun, lp
/* #30 Enter Isr epilogue. */
  trap    17

OS_HAL_ASM_SECTION_TEXT(OS_CODE)
OS_HAL_ASM_ALIGN(4)
OS_HAL_ASM_GLOBAL(Os_Hal_IsrEpilogue)
OS_HAL_ASM_LABEL(Os_Hal_IsrEpilogue)
/* #40 Restore interrupted context. */
#if defined (OS_HAL_ASM_FPU_USAGE)
  OS_HAL_ASM_POPSP(r11,r12)
  ldsr    r11, 6, 0         /* load r11 to FPSR */
  ldsr    r12, 7, 0         /* load r12 to  FPEPC */
#endif /* defined (OS_HAL_ASM_FPU_USAGE) */
  OS_HAL_ASM_POPSP(r11,r12)
  ldsr    r11, 0, 0         /* load r11 to EIPC */
  ldsr    r12, 1, 0         /* load r11 to EIPSW */
  OS_HAL_ASM_POPSP(r30,r31)
  OS_HAL_ASM_POPSP(r4,r19)
  OS_HAL_ASM_POPSP(r1,r2)
/* #50 Retrun to interrupted context. */
  eiret


/***********************************************************************************************************************
 *  Os_Hal_UnhandledIrq()
 **********************************************************************************************************************/
/*! \brief    This handler is triggered, if an interrupt occurs, which is not configured.
 *  \details  It shall call the kernel's Os_UnhandledIrq() function. Os_UnhandledIrq() expects the exception
 *            source number and the address of the interrupted instruction to be passed.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 *  \pre          Interrupts disabled.
 *
 *  \trace        CREQ-24
 **********************************************************************************************************************/
/*!
 * \internal
 *  - #10 Synchronize pipeline on exception entry.
 *  - #20 Disable FE level interrupts.
 *  - #30 Get the core ID.
 *  - #40 Switch to kernel stack and reprogram stack window.
 *  - #50 Store the exception index in first parameter of next function call.
 *  - #60 Store the exception address in second parameter of next function call.
 *  - #70 Store the privileged mode in third parameter of next function call.
 *  - #80 Call Os_UnhandledIrq in privileged mode with interrupts disabled.
 * \endinternal
 */
OS_HAL_ASM_SECTION_TEXT(OS_CODE)
OS_HAL_ASM_ALIGN(4)
OS_HAL_ASM_GLOBAL(Os_Hal_UnhandledIrq)
OS_HAL_ASM_LABEL(Os_Hal_UnhandledIrq)
/* #10 Synchronize pipeline on exception entry. */
  syncp
/* #20 Disable FE level interrupts. */
  mov     0x000180A0, r11
  ldsr    r11, 5, 0         /* load r11 to PSW */
/* #30 Get the core ID. */
  stsr    0, r11, 2         /* store HTCFG0 to r11 */
  OS_HAL_COREID_PROCESS(r11)
  shl     2, r11
/* #40 Switch to kernel stack and reprogram stack window. */
  OS_HAL_ASM_MOV_LABEL(OsCfg_Stack_KernelStacks, r12)
  add     r11, r12
  ld.w    0[r12], r12
  ld.w    0[r12], r11
  OS_HAL_ASM_SET_MPIDX_0
  OS_HAL_ASM_SET_MPLA0(r11) /* load r11 to MPLA0 */
  ld.w    4[r12], r3        /* get SP (r3) */
  OS_HAL_ASM_SET_MPUA0(r3)  /* load SP (r3) to MPUA0 */
/* #50 Store the exception index in first parameter of next function call. */
  stsr    13, r6, 0         /* store EIIC to r6 */
  andi    0x01FF, r6, r6
/* #60 Store the exception address in second parameter of next function call. */
  stsr    0, r7, 0          /* store EIPC to r7 */
  ldsr    r7, 16, 0         /* load r7 to CTPC */
/* #70 Store the privileged mode in third parameter of next function call. */
  stsr    1, r8, 0          /* store EIPSW to r8 */
  ldsr    r8, 17, 0         /* store r8 to CTPSW */
  not     r8, r8
  shl     1, r8
  shr     31, r8
/* #80 Call Os_UnhandledIrq in privileged mode with interrupts disabled. */
  OS_HAL_ASM_MOV_LABEL(Os_UnhandledIrq, r11)
  ldsr    r11, 0, 0         /* load r11 to EIPC */
  mov     0x000180A0, r11
  ldsr    r11, 1, 0         /* load r11 to EIPSW */
  eiret


/***********************************************************************************************************************
 *  Os_Hal_UnhandledSysCall()
 **********************************************************************************************************************/
/*! \brief    This handler is called, if a system call is triggered, which is not handled by the OS.
 *  \details  It shall call the kernel's Os_UnhandledSysCall() function. Os_UnhandledSysCall() expects the
 *            address of the instruction that caused the exception to be passed.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 *  \pre          Interrupts disabled.
 **********************************************************************************************************************/
/*!
 * \internal
 *  - #10 Synchronize pipeline on exception entry.
 *  - #20 Disable FE level interrupts.
 *  - #30 Get the core ID.
 *  - #40 Switch to kernel stack and reprogram stack window.
 *  - #50 Store the syscall address in first parameter of next function call.
 *  - #60 Store the privileged mode in second parameter of next function call.
 *  - #70 Call Os_UnhandledSysCall in privileged mode with interrupts disabled.
 * \endinternal
 */
OS_HAL_ASM_SECTION_TEXT(OS_CODE)
OS_HAL_ASM_ALIGN(4)
OS_HAL_ASM_GLOBAL(Os_Hal_UnhandledSysCall)
OS_HAL_ASM_LABEL(Os_Hal_UnhandledSysCall)
/* #10 Synchronize pipeline on exception entry. */
  syncp
/* #20 Disable FE level interrupts. */
  mov     0x00018A0, r11
  ldsr    r11, 5, 0         /* load r11 to PSW */
/* #30 Get the core ID. */
  stsr    0, r11, 2         /* store HTCFG0 to r11 */
  OS_HAL_COREID_PROCESS(r11)
  shl     2, r11
/* #40 Switch to kernel stack an reprogram stack window. */
  OS_HAL_ASM_MOV_LABEL(OsCfg_Stack_KernelStacks, r12)
  add     r11, r12
  ld.w    0[r12], r12
  ld.w    0[r12], r11
  OS_HAL_ASM_SET_MPIDX_0
  OS_HAL_ASM_SET_MPLA0(r11) /* load r11 to MPLA0 */
  ld.w    4[r12], r3        /* r3 = SP */
  OS_HAL_ASM_SET_MPUA0(r3)  /* load SP (r3) to MPUA0 */
/* #50 Store the syscalll address in the first parameter of next function call. */
  stsr    0, r6, 0          /* store EIPC to r6 */
  ldsr    r6, 16 ,0         /* load r6 to CTPC */
/* #60 Store the privileged mode in second parameter of next function call. */
  stsr    1, r7, 0          /* store EIPSW  to r7 */
  ldsr    r7, 17, 0         /* load r7 to CTPSW */
  not     r7, r7
  shl     1, r7
  shr     31, r7
/* #70 Call Os_UnhandledSysCall in privileged mode with interrupts disabled. */
  OS_HAL_ASM_MOV_LABEL(Os_UnhandledSysCall, r11)
  ldsr    r11, 0, 0         /* load r11 to EIPC */
  mov     0x000180A0, r11
  ldsr    r11, 1, 0         /* load r11 to EIPSW */
  eiret


/***********************************************************************************************************************
 *  Os_Hal_MemFaultExc()
 **********************************************************************************************************************/
/*! \brief      This handler is triggered, if a memory fault is detected.
 *  \details    In this handler it is not safe to use the current stack pointer any longer, because the memory fault
 *              may be a result of an invalid stack pointer. For this reason the handler has to switch to the kernel
 *              stack before using any stack. Scratch registers are allowed to be destroyed here, because this function
 *              never returns.
 *
 *              The handler shall call the kernel's Os_MemFault() function with the address of the instruction that
 *              caused the exception as argument.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 *  \pre          Interrupts disabled.
 **********************************************************************************************************************/
/*!
 * \internal
 *  - #10 Synchronize pipeline on exception entry.
 *  - #20 Get the core ID.
 *  - #30 Switch to kernel stack and reprogram stack window.
 *  - #40 Store the exception address in first parameter of next function call.
 *  - #50 Store the privileged mode in second parameter of next function call.
 *  - #60 Call Os_MemFault in privileged mode with interrupts disabled.
 * \endinternal
 */
OS_HAL_ASM_SECTION_TEXT(OS_CODE)
OS_HAL_ASM_ALIGN(4)
OS_HAL_ASM_GLOBAL(Os_Hal_MemFaultExc)
OS_HAL_ASM_LABEL(Os_Hal_MemFaultExc)
/* #10 Synchronize pipeline on exception entry. */
  syncp
/* #20 Get the core ID. */
  stsr    0, r11, 2         /* store HTCFG0 to r11 */
  OS_HAL_COREID_PROCESS(r11)
  shl     2, r11
/* #30 Switch to kernel stack and reprogram stack window.*/
  OS_HAL_ASM_MOV_LABEL(OsCfg_Stack_KernelStacks, r12)
  add     r11, r12
  ld.w    0[r12], r12
  ld.w    0[r12], r11
  OS_HAL_ASM_SET_MPIDX_0
  OS_HAL_ASM_SET_MPLA0(r11) /* load r11 to MPLA0 */
  ld.w    4[r12], r3        /* r3 = SP */
  OS_HAL_ASM_SET_MPUA0(r3)  /* load SP (r3) to MPUA0 */
/* #40 Store the exception address in first parameter of next function call.*/
  stsr    2, r6, 0          /* store FEPC to r6 */
  ldsr    r6, 16 ,0         /* load r6 to CTPC */
/* #50 Store the privileged mode in second parameter of next function call.*/
  stsr    3, r7, 0          /* store FEPSW to r7 */
  ldsr    r7, 17, 0         /* load r7 to CTPSW */
  not     r7, r7
  shl     1, r7
  shr     31, r7
/* #60 Call Os_MemFault in privileged mode with interrupts disabled.*/
  OS_HAL_ASM_MOV_LABEL(Os_MemFault, r11)
  ldsr    r11, 2, 0         /* load r11 to FEPC */
  mov     0x00018A0, r11
  ldsr    r11, 3, 0         /* load r11 to FEPSW */
  feret


/***********************************************************************************************************************
 *  Os_Hal_UnhandledExc()
 **********************************************************************************************************************/
/*! \brief    This handler is called, if an exception is triggered, which is not handled by the OS.
 *  \details  In this handler it is not safe to use the current stack pointer any longer, because the exception
 *            may be a result of an invalid stack pointer. For this reason the handler has to switch to the kernel
 *            stack before using any stack.
 *
 *            This handler shall call the kernel's Os_UnhandledExc() function.
 *            Os_UnhandledExc() expects the following parameters:
 *              <EXC-SOURCE>           The source number of the exception.
 *              <INSTRUCTION-ADDRESS>  The address of the causing instruction.
 *              <CAUSER-PRIVILEGED>    The privilege state before the exception:
 *                                       !0 Before the exception, the core was privileged.
 *                                       0  Before the exception, the core was not privileged.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 *  \pre          Interrupts disabled.
 **********************************************************************************************************************/
  /*!
   * \internal
   *  - #10 Synchronize pipeline on exception entry.
   *  - #20 Get the core ID.
   *  - #30 Switch to kernel stack and reprogram stack window.
   *  - #40 Store the exception index in first parameter of next function call.
   *  - #50 Store the exception address in second parameter of next function call.
   *  - #60 Store the privileged mode in third parameter of next function call.
   *  - #70 Call Os_UnhandledExc in privileged mode with interrupts disabled.
   * \endinternal
   */
OS_HAL_ASM_SECTION_TEXT(OS_CODE)
OS_HAL_ASM_ALIGN(4)
OS_HAL_ASM_GLOBAL(Os_Hal_UnhandledExc)
OS_HAL_ASM_LABEL(Os_Hal_UnhandledExc)
OS_HAL_ASM_EXTERN(_Os_UnhandledExc)
/* #10 Synchronize pipeline on exception entry. */
  syncp
/* #20 Get the core ID. */
  stsr    0, r11, 2         /* store HTCFG0 to r11 */
  OS_HAL_COREID_PROCESS(r11)
  shl     2, r11
/* #30 Switch to kernel stack and reprogram stack window. */
  OS_HAL_ASM_MOV_LABEL(OsCfg_Stack_KernelStacks, r12)
  add     r11, r12
  ld.w    0[r12], r12
  ld.w    0[r12], r11
  OS_HAL_ASM_SET_MPIDX_0
  OS_HAL_ASM_SET_MPLA0(r11) /* load r11 to MPLA0 */
  ld.w    4[r12], r3        /* r3 = SP */
  OS_HAL_ASM_SET_MPUA0(r3)  /* load SP to MPUA0 */
/* #40 Store the exception index in first parameter of next function call. */
  stsr    14, r6, 0         /* store FEIC to r6 */
  shr     4, r6
/*  #50 Store the exception address in second parameter of next function call. */
  stsr    2, r7, 0          /* store FEPC to r7 */
  ldsr    r7, 16, 0         /* load r7 to CTPC */
/* #60 Store the privileged mode in third parameter of next function call. */
  stsr    3, r8, 0          /* store FEPSW to r8 */
  ldsr    r8, 17, 0         /* load r8 to CTPSW */
  not     r8, r8
  shl     1, r8
  shr     31, r8
/* #70 Call Os_UnhandledExc in privileged mode with interrupts disabled. */
  OS_HAL_ASM_MOV_LABEL(Os_UnhandledExc, r11)
  ldsr    r11, 2, 0         /* load r11 to FEPC */
  mov     0x000180A0, r11
  ldsr    r11, 3, 0         /* load r11 to PEPSW */
  feret


#define OS_STOP_SEC_CODE
#include "Os_MemMap_OsCode.h"


#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Entry.asm
 **********************************************************************************************************************/

