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
 *  \addtogroup Os_Hal_Compiler
 *  \{
 *
 *  \file       Os_Hal_Compiler_RenesasASM.inc
 *  \brief      Additional Renesas assembler compiler abstraction.
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_COMPILERRENESASASM_INC
# define OS_HAL_COMPILERRENESASASM_INC

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#if 0

/*! \brief    Assembler macro used for exception vector table definition.
 */
OS_HAL_ASM_EXC_RENESAS .macro  LABEL, EXCHANDLER
               .align 16
               _Exc_~LABEL:
               jr32 _~EXCHANDLER
               nop
               nop
               nop
               .endm


/*! \brief    Assembler macro used for cat2 isr prologue.
 */
OS_HAL_ASM_CAT2ISR_RENESAS .macro ISRNAME
               .section ".OS_CODE.text", text
               .align 4
               _Os_Hal_Irq_~ISRNAME:
               .extern _OsCfg_Isr_~ISRNAME
               $nowarning       /* Disable warnings to suppress warning W0550013. */
               pushsp r1,r2
               $warning         /* Enable warnings */
               pushsp r4,r19
               mov    #_OsCfg_Isr_~ISRNAME, r6
               jr     _Os_Irq_Isr
               .endm


/*! \brief    Assembler macro used for interrupt vector table definition.
 */
OS_HAL_ASM_WORD_RENESAS .macro LABEL
                .DW #_~LABEL
                .endm


/*! \brief    Assembler macro used for syscall table definition.
 */
OS_HAL_ASM_SYSCALL_WORD_RENESAS .macro
                .extern _Os_Hal_UnhandledSysCall
                .DW 4
                jarl _Os_Hal_UnhandledSysCall, lp
                .endm


/*! \brief    Assembler macro to use labels with mov directive correctly.
 */
OS_HAL_ASM_MOV_LABEL_RENESAS .macro LABEL, REGISTER
                mov #_~LABEL, REGISTER
                .endm


/*! \brief    Assembler macro to push registers to stack, including
 *            suppression of warning W0550013.
 */
OS_HAL_ASM_PUSHP_RENESAS .macro R1, R2
                $nowarning
                pushsp R1, R2
                $warning
                .endm


/*! \brief    Assembler macro to pop register from stack including
 *            suppression of warning W0550013.
 */
OS_HAL_ASM_POPSP_RENESAS .macro R1,R2
                $nowarning
                popsp R1, R2
                $warning
                .endm


#endif /* OS_HAL_COMPILERRENESASASM_INC */


#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Compiler_RenesasASM.inc
 **********************************************************************************************************************/
