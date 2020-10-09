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
 * \file       Os_Hal_Compiler_RenesasCCRH_ASMInt.h
 * \brief      Compiler abstraction for assembler makros compiler Renesas CC_RH
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_COMPILER_RENESASCCRH_ASM
# define OS_HAL_COMPILER_RENESASCCRH_ASM
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */
/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/
#if 0
/*! PSW Mask for EP flag - Disable EI interrupt handling. */
# define OS_HAL_PSW_EP_MSK                           (0x00000040)

/* Compiler abstraction of assembler directive .section (const ) */
# define OS_HAL_ASM_SECTION_CONST(SEC_NAME)          .##section .##SEC_NAME##.##const, const

/* Compiler abstraction of assembler directive .section (text) */
# define OS_HAL_ASM_SECTION_TEXT(SEC_NAME)           .##section .##SEC_NAME##.##text, text

/* Compiler abstraction of assembler directive .align */
# define OS_HAL_ASM_ALIGN(ALIGN_VAL)                 .##align ALIGN_VAL

/* Compiler abstraction of assembler directive to declare global label */
# define OS_HAL_ASM_GLOBAL(LABEL)                    .##public _##LABEL

/* Compiler abstraction of assembler directive to define label */
# define OS_HAL_ASM_LABEL(LABEL)                     _##LABEL:

/* Compiler abstraction of assembler directive to declare extern label */
# define OS_HAL_ASM_EXTERN(LABEL)                    .##extern LABEL

/* Compiler abstraction of assembler directive to allocate memory area */
# define OS_HAL_ASM_WORD(LABEL)                      OS_HAL_ASM_WORD_RENESAS LABEL

/* Compiler abstraction of assembler directive to declare CAT2 Isr */
# define OS_HAL_ASM_CAT2ISR(LABEL)                   OS_HAL_ASM_CAT2ISR_RENESAS LABEL

/* Compiler abstraction to declare exception vector table */
# define OS_HAL_ASM_EXC(LABEL, FUNC)                 OS_HAL_ASM_EXC_RENESAS LABEL, FUNC

/* Compiler abstraction of assembler directive pushsp */
# define OS_HAL_ASM_PUSHSP(R1,R2)                    OS_HAL_ASM_PUSHP_RENESAS R1, R2

/* Compiler abstraction of assembler directive popsp */
# define OS_HAL_ASM_POPSP(R1,R2)                     OS_HAL_ASM_POPSP_RENESAS R1,R2

/* Compiler abstraction of assembler directive .dw */
# define OS_HAL_ASM_SYSCALL_WORD(LABEL_A,LABEL_B)    OS_HAL_ASM_SYSCALL_WORD_RENESAS

/* Compiler abstraction of assembler directive mov, using labels */
# define OS_HAL_ASM_MOV_LABEL(LABEL,REGISTER)        OS_HAL_ASM_MOV_LABEL_RENESAS LABEL, REGISTER

# define OS_HAL_ASM_SET_MPIDX_0

# define OS_HAL_ASM_SET_MPLA0(REG)                   ldsr REG, 0, 6

# define OS_HAL_ASM_SET_MPUA0(REG)                   ldsr REG, 1, 6

# define OS_HAL_ASM_SET_MPAT0(REG)                   ldsr REG, 2, 6

# define OS_HAL_ASM_SET_ADDRESS_ID_REG(REG)          ldsr REG, 7, 2

#define OS_HAL_COREID_PROCESS(REG)                   shr 17, REG


#endif /* OS_HAL_COMPILER_RENESASCCRH_ASM */


#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Compiler_RenesasCCRH_ASMInt.h
 **********************************************************************************************************************/
