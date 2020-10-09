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
 * \addtogroup Os_Hal_Compiler
 * \{
 *
 * \file       Os_Hal_Compiler_Greenhills_ASMInt.h
 * \brief      Compiler abstraction for assembler macros compiler Greenhills
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_COMPILER_GREENHILLS_ASM
# define OS_HAL_COMPILER_GREENHILLS_ASM
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */
/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/
#if 0
/*! PSW Mask for EP flag - Disable EI interrupt handling. */
# define OS_HAL_PSW_EP_MSK                     //      (0x00000040)

/* Compiler abstraction of assembler directive .section (const ) */
#define OS_HAL_ASM_SECTION_CONST(SEC_NAME)      //     .##section .##SEC_NAME, a

/* Compiler abstraction of assembler directive .section (text) */
#define OS_HAL_ASM_SECTION_TEXT(SEC_NAME)       //     .##section .##SEC_NAME, ax

/* Compiler abstraction of assembler directive .align */
#define OS_HAL_ASM_ALIGN(ALIGN_VAL)            //      .##align ALIGN_VAL

/* Compiler abstraction of assembler directive to declare global label */
#define OS_HAL_ASM_GLOBAL(LABEL)              //       .##globl _##LABEL

/* Compiler abstraction of assembler directive to define label */
#define OS_HAL_ASM_LABEL(LABEL)               //       _##LABEL:

/* Compiler abstraction of assembler directive to allocate memory area */
#define OS_HAL_ASM_WORD(LABEL)                //       .##word _##LABEL

/* Compiler abstraction of assembler directive pushsp */
#define OS_HAL_ASM_PUSHSP(R1,R2)             //        pushsp R1-R2

/* Compiler abstraction of assembler directive popsp */
#define OS_HAL_ASM_POPSP(R1,R2)               //       popsp R1-R2

#define OS_HAL_ASM_EXTERN(LABEL)

#define OS_HAL_ASM_EXC(LABEL,FUNC)          //         OS_HAL_ASM_EXC_GHS LABEL,FUNC

#define OS_HAL_ASM_CAT2ISR(ISRNAME)          //        OS_HAL_ASM_CAT2ISR_GHS ISRNAME

#define OS_HAL_ASM_SYSCALL_WORD(LABEL_A,LABEL_B) //    .##word(LABEL_A - LABEL_B)

#define OS_HAL_ASM_MOV_LABEL(LABEL,REGISTER)         mov _##LABEL, REGISTER

#if defined (OS_CFG_DERIVATIVEGROUP_RH850U2A16)                                                                         /* COV_OS_DERIVATIVEBETAMODULE */

# define OS_HAL_ASM_SET_MPIDX_0                      ldsr r0, 16, 5

# define OS_HAL_ASM_SET_MPLA0(REG)                   ldsr REG, 20, 5

# define OS_HAL_ASM_SET_MPUA0(REG)                   ldsr REG, 21, 5

# define OS_HAL_ASM_SET_MPAT0(REG)                   ldsr REG, 22, 5

# define OS_HAL_ASM_SET_ADDRESS_ID_REG(REG)          ldsr REG, 0, 1

#define OS_HAL_COREID_PROCESS(REG)

#elif defined (OS_CFG_DERIVATIVEGROUP_RH850U2A8)                                                                        /* COV_OS_DERIVATIVEBETAMODULE */

# define OS_HAL_ASM_SET_MPIDX_0                      ldsr r0, 16, 5

# define OS_HAL_ASM_SET_MPLA0(REG)                   ldsr REG, 20, 5

# define OS_HAL_ASM_SET_MPUA0(REG)                   ldsr REG, 21, 5

# define OS_HAL_ASM_SET_MPAT0(REG)                   ldsr REG, 22, 5

# define OS_HAL_ASM_SET_ADDRESS_ID_REG(REG)          ldsr REG, 0, 1

#define OS_HAL_COREID_PROCESS(REG)

#else

# define OS_HAL_ASM_SET_MPIDX_0

# define OS_HAL_ASM_SET_MPLA0(REG)                //   ldsr REG, 0, 6

# define OS_HAL_ASM_SET_MPUA0(REG)                //   ldsr REG, 1, 6

# define OS_HAL_ASM_SET_MPAT0(REG)                //   ldsr REG, 2, 6

# define OS_HAL_ASM_SET_ADDRESS_ID_REG(REG)        //  ldsr REG, 7, 2

#define OS_HAL_COREID_PROCESS(REG)                  // shr 17, REG

#endif

#pragma asm

/* Macro to create the entries of the exception table */
.macro OS_HAL_ASM_EXC_GHS LABEL,FUNC
  .align 16
  .globl _><LABEL
  _><LABEL:
  /* #10 Jump to the passed exception handler symbol. */
  jr32 _><FUNC
  nop
  nop
  nop
.endm

.macro OS_HAL_ASM_CAT2ISR_GHS ISRNAME
  .section ".OS_CODE", "ax"
  .align 4
  _Os_Hal_Irq_><ISRNAME:
  /* #10 Store temporary registers on the stack. */
  pushsp r1-r2
  pushsp r4-r19
  /* #20 Store the pointer to ISR configuration in function parameter 1. */
  mov   _OsCfg_Isr_><ISRNAME, r6
  /* #30 Jump to function Os_Irq_Isr */
  jr    _Os_Irq_Isr

.endm

#pragma endasm

#endif /* OS_HAL_COMPILER_GREENHILLS_ASM */
#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Compiler_Greenhills_ASMInt.h
 **********************************************************************************************************************/
