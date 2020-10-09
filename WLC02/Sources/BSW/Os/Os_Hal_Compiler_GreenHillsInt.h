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
 * \file       Os_Hal_Compiler_GreenHillsInt.h
 * \brief      Compiler abstraction for compiler Green Hills
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_COMPILER_GREENHILLSINT_H
# define OS_HAL_COMPILER_GREENHILLSINT_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"
# include "Os_Hal_Core_Types.h"
# include "Os_MemoryProtection_Cfg.h"
# include "Os_Hal_Compiler_Greenhills_ASMInt.h"


#if 0
/*
 * Suppress all warnings with regard to pointer to integer conversion, this kind of warning is also a MISRA finding
 * and is already analyzed during MISRA analysis.
 */
# pragma ghs nowarning 32

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/*! \brief      Declares a function with a compiler specific attribute.
 *  \details    The implementations prototype has to be created with OS_FUNC_ATTRIBUTE_DEFINITION.
 *  \param[in]  rettype       The return type of the function.
 *  \param[in]  memclass      The memory class of the function.
 *  \param[in]  attribute     The function attribute {OS_ALWAYS_INLINE; OS_PURE, ...}.
 *  \param[in]  functionName  The function name.
 *  \param[in]  arguments     The function arguments in brackets. E.g. (uint8 a, uint16 b) or (void).
 */
# define OS_FUNC_ATTRIBUTE_DECLARATION(rettype, memclass, attribute, functionName, arguments) \
      FUNC(rettype, memclass)  functionName arguments attribute                                                         /* PRQA S 3410, 3453 */ /* MD_Os_Rule20.7_3410, MD_MSR_FctLikeMacro */

/*! \brief      Provides a function prototype for function definitions with a compiler specific attribute.
 *  \details    The declaration has to be created with OS_FUNC_ATTRIBUTE_DECLARATION.
 *  \param[in]  rettype       The return type of the function.
 *  \param[in]  memclass      The memory class of the function.
 *  \param[in]  attribute     The function attribute {OS_ALWAYS_INLINE; OS_PURE, ...}.
 *  \param[in]  functionName  The function name.
 *  \param[in]  arguments     The function arguments in brackets. E.g. (uint8 a, uint16 b) or (void).
 */
# define OS_FUNC_ATTRIBUTE_DEFINITION(rettype, memclass, attribute, functionName, arguments) \
      FUNC(rettype, memclass)  functionName arguments                                                                   /* PRQA S 3410, 3453 */ /* MD_Os_Rule20.7_3410, MD_MSR_FctLikeMacro */

/*! \brief    Tells the compiler that the conditional statement is likely to be true.
 *  \details
 *  The compiler, in turn, can then perform block reordering, and other optimization to
 *  improve the performance of conditional branches.
 *
 *  Availability: GCC ('__builtin_expect'), Diab
 *
 *  \param[in]  CONDITION   The condition which is likely to be true
 */
# define OS_LIKELY(CONDITION)       (CONDITION)                                                                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! \brief    Tells the compiler that the conditional statement is likely to be false.
 *  \details
 *  The compiler, in turn, can then perform block reordering, and other optimization to
 *  improve the performance of conditional branches.
 *
 *  Availability: GCC ('__builtin_expect'), Diab
 *
 *  \param[in]  CONDITION   The condition which is likely to be false
 */
# define OS_UNLIKELY(CONDITION)     (CONDITION)                                                                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/*! \brief    Force the compiler to inline a function.
 *  \details  This attribute forces the compiler to inline the specified function,
 *        regardless of the optimization strategy of the compiler itself.
 *        On some compilers you may be able to disable even this kind of inlining, using debugging options.
 *
 *        Availability: GCC ('always_inline'), Diab, Tasking
 */
# define OS_ALWAYS_INLINE

/*! \brief  Abstraction for HAL specific compiler attribute to prevent from inlining a function. */
# define OS_HAL_NOINLINE             __attribute__((noinline))

/*! \brief    This attribute tells the compiler that a function never returns.
 *  \details
 * It can then optimize without regard to what would happen if the function ever did return.
 * This makes slightly better code. More importantly, it helps avoid spurious warnings of uninitialized variables.
 *
 * Availability: GCC ('noreturn'), Diab, Tasking, GreenHills
 */
# define OS_NORETURN    __attribute__((noreturn))


/*! \brief    This attribute forces inlining of all function calls in a function, including nested function calls.
 * \details
 * Whether the function itself is considered for inlining depends on its size and the current inlining parameters.
 *
 * Availability: GCC ('flatten'), Diab, Tasking
 */
# define OS_FLATTEN


/*! \brief    This attribute tells that a function has no side effects and will not access global data.
 *  \details
 * This can help the compiler to optimize code. Such functions do not examine any values except their arguments,
 * and have no effects except the return value. This is just slightly more strict class than the OS_PURE attribute,
 * since function is not allowed to read global memory.
 *
 * Availability: GCC ('const'), Diab ('no_side_effects'), Tasking, Green Hills
 */
# define OS_NOSIDEEFFECTS


/*! \brief    This attribute tells that a function has no side effects, although it may read global data.
 *  \details
 * Such pure functions can be subject to common subexpression elimination and loop optimization.
 *
 * Availability: GCC ('pure'), Diab, Tasking, Green Hills
 */
# define OS_PURE        __attribute__((pure))

/*! \brief         Abstraction of executing arbitrary assembler instruction
 *  \param[in]     x       Assembler instruction
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_ASM(x)             __asm(x)

/*! \brief         Abstraction of the assembler align directive
 *  \param[in]     val      Alignment
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_ALIGN(val)         __asm(".align "val)

/*! \brief         Defines an externally visible identifier.
 *  \param[in]     name      Name of the identifier
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_LABEL(name)        __asm(".globl _"name);__asm("_"name":")

/*! \brief         Starts a program code (.text) section
 *  \details       --no details--
 *  \param[in]     name      Name of the section
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_SECTION(name)      __asm(".section "name", \"ax\"")

/*! \brief         Stores the value of a constant expressions as successive 32-bit data.
 *  \details       --no details--
 *  \param[in]     name
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_WORD(name)         __asm(".word _"name);

/*! \brief         Abstraction of the assembler nop instruction
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_NOP()              __asm("nop")

/*! \brief         Disables acknowledgment of EI level interrupts
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Supervisor mode
 */
# define Os_Hal_DisableGlobal()    __asm("di")

/*! \brief         Enables acknowledgment of EI level interrupts
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Supervisor mode
 */
# define Os_Hal_EnableGlobal()     __asm("ei")

/*! \brief         Abstraction of the assembler synci instruction
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_SyncInstruction()  __asm("synci")

/*! \brief         Abstraction of the assembler syncp instruction
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_SyncPipeline()     __asm("syncp")

/*! \brief         Abstraction of the assembler syncm instruction
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_SyncMemory()       __asm("syncm")

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/* ECO_IGNORE_BLOCK_BEGIN */

/***********************************************************************************************************************
 *  Os_Hal_GetSP()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetSP(void)
 *  \brief        Get the current stack pointer.
 *  \details      --no details--
 *
 *  \return       The current stack pointer.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetSP(void)
{
  mov  SP, r10
}


/***********************************************************************************************************************
 *  Os_Hal_SetLP()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetLP(uint32 val)
 *  \brief        Set the current stack pointer.
 *  \details      --no details--
 *
 *  \param[in]    The link pointer to set.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm void Os_Hal_SetLP(uint32 val)
{
%reg val
  mov  val, LP
%mem val
  ld.w val, LP
%error
}


/***********************************************************************************************************************
 *  Os_Hal_GetLP()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetLP(void)
 *  \brief        Returns the current link pointer.
 *  \details      --no details--
 *
 *  \return       The current link pointer.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetLP(void)
{
  mov  LP, r10
}


/***********************************************************************************************************************
 *  Os_Hal_SetPSW()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetPSW(uint32 value)
 *  \brief      Writes a value to the PSW register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the PSW register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetPSW(uint32 value)
{
%reg value
  ldsr  value, 5, 0
%con value
  mov   value, r11
  ldsr  r11, 5, 0
%mem value
  mov   value, r11
  ldsr  r11, 5, 0
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetPMR()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetPMR(uint32 value)
 *  \brief      Writes a value to the PMR register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the PMR register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode and EI level interrupts disabled.
 **********************************************************************************************************************/
asm void Os_Hal_SetPMR(uint32 value)
{
%reg value
  ldsr  value, OS_HAL_PMR
%con value
  mov   value, r11
  ldsr  r11, OS_HAL_PMR
%mem value
  mov   value, r11
  ldsr  r11, OS_HAL_PMR
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetASID()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetASID(uint32 value)
 *  \brief      Writes a value to the ASID register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the ASID register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetASID(uint32 value)
{
%reg value
  ldsr  value, OS_HAL_ADDRESS_ID_REG
%con value
  mov   value, r11
  ldsr  r11, OS_HAL_ADDRESS_ID_REG
%mem value
  mov   value, r11
  ldsr  r11, OS_HAL_ADDRESS_ID_REG
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetCTBP()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetCTBP(uint32 value)
 *  \brief      Writes a value to the CTBP register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the CTBP register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm void Os_Hal_SetCTBP(uint32 value)
{
%reg value
  ldsr  value, 20, 0
%con value
  mov   value, r11
  ldsr  r11, 20, 0
%mem value
  mov   value, r11
  ldsr  r11, 20, 0
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetSCCFG()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetSCCFG(uint32 value)
 *  \brief      Writes a value to the SCCFG register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the SCCFG register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetSCCFG(uint32 value)
{
%reg value
  ldsr  value, 11, 1
%con value
  mov   value, r11
  ldsr  r11, 11, 1
%mem value
  mov   value, r11
  ldsr  r11, 11, 1
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetSCBP()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetSCBP(uint32 value)
 *  \brief      Writes a value to the SCBP register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the SCBP register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetSCBP(uint32 value)
{
%reg value
  ldsr  value, 12, 1
%con value
  mov   value, r11
  ldsr  r11, 12, 1
%mem value
  mov   value, r11
  ldsr  r11, 12, 1
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetEIPC()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetEIPC(uint32 value)
 *  \brief      Writes a value to the EIPC register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the EIPC register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetEIPC(uint32 value)
{
%reg value
  ldsr  value, 0, 0
%con value
  mov   value, r11
  ldsr  r11, 0, 0
%mem value
  mov   value, r11
  ldsr  r11, 0, 0
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetEIPSW()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetEIPSW(uint32 value)
 *  \brief      Writes a value to the EIPSW register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the EIPSW register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetEIPSW(uint32 value)
{
%reg value
  ldsr  value, 1, 0
%con value
  mov   value, r11
  ldsr  r11, 1, 0
%mem value
  mov   value, r11
  ldsr  r11, 1, 0
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetEIWR()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetEIWR(uint32 value)
 *  \brief      Writes a value to the EIWR register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the EIWR register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetEIWR(uint32 value)
{
%reg value
  ldsr  value, 28, 0
%con value
  mov   value, r11
  ldsr  r11, 28, 0
%mem value
  mov   value, r11
  ldsr  r11, 28, 0
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetFPSR()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetFPSR(uint32 value)
 *  \brief      Writes a value to the FPSR register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the FPSR register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode or enabled CU0 flag in PSW.
 **********************************************************************************************************************/
asm void Os_Hal_SetFPSR(uint32 value)
{
%reg value
  ldsr  value, 6, 0
%con value
  mov   value, r11
  ldsr  r11, 6, 0
%mem value
  mov   value, r11
  ldsr  r11, 6, 0
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetFPEPC()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetFPEPC(uint32 value)
 *  \brief      Writes a value to the FPEPC register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the FPEPC register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode or enabled CU0 flag in PSW.
 **********************************************************************************************************************/
asm void Os_Hal_SetFPEPC(uint32 value)
{
%reg value
  ldsr  value, 7, 0
%con value
  mov   value, r11
  ldsr  r11, 7, 0
%mem value
  mov   value, r11
  ldsr  r11, 7, 0
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetEBASE()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetEBASE(uint32 value)
 *  \brief      Writes a value to the EBASE register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the EBASE register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetEBASE(uint32 value)
{
%reg value
  ldsr  value, 3, 1
%con value
  mov   value, r11
  ldsr  r11, 3, 1
%mem value
  mov   value, r11
  ldsr  r11, 3, 1
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetINTBP()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetINTBP(uint32 value)
 *  \brief      Writes a value to the INTBP register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the INTB register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetINTBP(uint32 value)
{
%reg value
  ldsr  value, 4, 1
%con value
  mov   value, r11
  ldsr  r11, 4, 1
%mem value
  mov   value, r11
  ldsr  r11, 4, 1
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetINTCFG()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetINTCFG(uint32 value)
 *  \brief      Writes a value to the INTCFG register.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the INTCFG register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetINTCFG(uint32 value)
{
%reg value
  ldsr  value, 13, 2
%con value
  mov   value, r11
  ldsr  r11, 13, 2
%mem value
  mov   value, r11
  ldsr  r11, 13, 2
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPM()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPM(uint32 value)
 *  \brief      Sets the memory protection operation mode register to the passed value.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPU region control register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPM(uint32 value)
{
%reg value
  ldsr  value, 0, 5
%con value
  mov   value, r11
  ldsr  r11, 0, 5
%mem value
  mov   value, r11
  ldsr  r11, 0, 5
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPRC()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPRC(uint32 value)
 *  \brief      Sets the MPU region control register to the passed value.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPU region control register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPRC(uint32 value)
{
%reg value
  ldsr  value, 1, 5
%con value
  mov   value, r11
  ldsr  r11, 1, 5
%mem value
  mov   value, r11
  ldsr  r11, 1, 5
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA(uint32 value)
{
%reg value
  ldsr  value, 20, 5
%con value
  mov   value, r11
  ldsr  r11, 20, 5
%mem value
  mov   value, r11
  ldsr  r11, 20, 5
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA(uint32 value)
{
%reg value
  ldsr  value, 21, 5
%con value
  mov   value, r11
  ldsr  r11, 21, 5
%mem value
  mov   value, r11
  ldsr  r11, 21, 5
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT(uint32 value)
{
%reg value
  ldsr  value, 22, 5
%con value
  mov   value, r11
  ldsr  r11, 22, 5
%mem value
  mov   value, r11
  ldsr  r11, 22, 5
%error
}


/***********************************************************************************************************************
 *  Os_Hal_GetMPLA()
 **********************************************************************************************************************/
/*! \fn         uint32 Os_Hal_GetMPLA(void)
 *  \brief      Returns the protection area minimum address of the specific core MPU region (G4X cores only).
 *  \details    --no details--
 *
 *  \return       MPLA register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          SUPERVISOR
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetMPLA(void)
{
  stsr  20, r10, 5
}


/***********************************************************************************************************************
 *  Os_Hal_GetMPUA()
 **********************************************************************************************************************/
/*! \fn         uint32 Os_Hal_GetMPUA(void)
 *  \brief      Returns the protection area minimum address of the specific core MPU region (G4X cores only).
 *  \details    --no details--
 *
 *  \return       MPUA register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          SUPERVISOR
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetMPUA(void)
{
  stsr  21, r10, 5
}


/***********************************************************************************************************************
 *  Os_Hal_GetMPLA0()
 **********************************************************************************************************************/
/*! \fn         uint32 Os_Hal_GetMPLA0(void)
 *  \brief      Returns the protection area minimum address of the specific core MPU region.
 *  \details    --no details--
 *
 *  \return       MPLA0 register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          SUPERVISOR
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetMPLA0(void)
{
  stsr  0, r10, 6
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA0()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA0(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA0 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA0(uint32 value)
{
%reg value
  ldsr  value, 0, 6
%con value
  mov   value, r11
  ldsr  r11, 0, 6
%mem value
  mov   value, r11
  ldsr  r11, 0, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_GetMPUA0()
 **********************************************************************************************************************/
/*! \fn         uint32 Os_Hal_GetMPUA0(void)
 *  \brief      Returns the protection area minimum address of the specific core MPU region.
 *  \details    --no details--
 *
 *  \return       MPUA0 register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetMPUA0(void)
{
  stsr  1, r10, 6
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA0()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA0(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA0 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA0(uint32 value)
{
%reg value
  ldsr  value, 1, 6
%con value
  mov   value, r11
  ldsr  r11, 1, 6
%mem value
  mov   value, r11
  ldsr  r11, 1, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT0()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT0(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT0 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT0(uint32 value)
{
%reg value
  ldsr  value, 2, 6
%con value
  mov   value, r11
  ldsr  r11, 2, 6
%mem value
  mov   value, r11
  ldsr  r11, 2, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA1()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA1(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA1 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA1(uint32 value)
{
%reg value
  ldsr  value, 4, 6
%con value
  mov   value, r11
  ldsr  r11, 4, 6
%mem value
  mov   value, r11
  ldsr  r11, 4, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA1()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA1(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA1 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA1(uint32 value)
{
%reg value
  ldsr  value, 5, 6
%con value
  mov   value, r11
  ldsr  r11, 5, 6
%mem value
  mov   value, r11
  ldsr  r11, 5, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT1()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT1(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT1 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT1(uint32 value)
{
%reg value
  ldsr  value, 6, 6
%con value
  mov   value, r11
  ldsr  r11, 6, 6
%mem value
  mov   value, r11
  ldsr  r11, 6, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA2()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA2(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA2 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA2(uint32 value)
{
%reg value
  ldsr  value, 8, 6
%con value
  mov   value, r11
  ldsr  r11, 8, 6
%mem value
  mov   value, r11
  ldsr  r11, 8, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA2()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA2(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA2 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA2(uint32 value)
{
%reg value
  ldsr  value, 9, 6
%con value
  mov   value, r11
  ldsr  r11, 9, 6
%mem value
  mov   value, r11
  ldsr  r11, 9, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT2()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT2(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT2 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT2(uint32 value)
{
%reg value
  ldsr  value, 10, 6
%con value
  mov   value, r11
  ldsr  r11, 10, 6
%mem value
  mov   value, r11
  ldsr  r11, 10, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA3()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA3(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA3 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA3(uint32 value)
{
%reg value
  ldsr  value, 12, 6
%con value
  mov   value, r11
  ldsr  r11, 12, 6
%mem value
  mov   value, r11
  ldsr  r11, 12, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA3()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA3(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA3 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA3(uint32 value)
{
%reg value
  ldsr  value, 13, 6
%con value
  mov   value, r11
  ldsr  r11, 13, 6
%mem value
  mov   value, r11
  ldsr  r11, 13, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT3()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT3(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT3 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT3(uint32 value)
{
%reg value
  ldsr  value, 14, 6
%con value
  mov   value, r11
  ldsr  r11, 14, 6
%mem value
  mov   value, r11
  ldsr  r11, 14, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA4()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA4(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA4 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA4(uint32 value)
{
%reg value
  ldsr  value, 16, 6
%con value
  mov   value, r11
  ldsr  r11, 16, 6
%mem value
  mov   value, r11
  ldsr  r11, 16, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA4()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA4(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA4 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA4(uint32 value)
{
%reg value
  ldsr  value, 17, 6
%con value
  mov   value, r11
  ldsr  r11, 17, 6
%mem value
  mov   value, r11
  ldsr  r11, 17, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT4()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT4(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT4 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT4(uint32 value)
{
%reg value
  ldsr  value, 18, 6
%con value
  mov   value, r11
  ldsr  r11, 18, 6
%mem value
  mov   value, r11
  ldsr  r11, 18, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA5()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA5(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA5 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA5(uint32 value)
{
%reg value
  ldsr  value, 20, 6
%con value
  mov   value, r11
  ldsr  r11, 20, 6
%mem value
  mov   value, r11
  ldsr  r11, 20, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA5()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA5(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA5 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA5(uint32 value)
{
%reg value
  ldsr  value, 21, 6
%con value
  mov   value, r11
  ldsr  r11, 21, 6
%mem value
  mov   value, r11
  ldsr  r11, 21, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT5()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT5(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT5 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT5(uint32 value)
{
%reg value
  ldsr  value, 22, 6
%con value
  mov   value, r11
  ldsr  r11, 22, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA6()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA6(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA6 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA6(uint32 value)
{
%reg value
  ldsr  value, 24, 6
%con value
  mov   value, r11
  ldsr  r11, 24, 6
%mem value
  mov   value, r11
  ldsr  r11, 24, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA6()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA6(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA6 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA6(uint32 value)
{
%reg value
  ldsr  value, 25, 6
%con value
  mov   value, r11
  ldsr  r11, 25, 6
%mem value
  mov   value, r11
  ldsr  r11, 25, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT6()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT6(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT6 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT6(uint32 value)
{
%reg value
  ldsr  value, 26, 6
%con value
  mov   value, r11
  ldsr  r11, 26, 6
%mem value
  mov   value, r11
  ldsr  r11, 26, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA7()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA7(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA7 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA7(uint32 value)
{
%reg value
  ldsr  value, 28, 6
%con value
  mov   value, r11
  ldsr  r11, 28, 6
%mem value
  mov   value, r11
  ldsr  r11, 28, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA7()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA7(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA7 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA7(uint32 value)
{
%reg value
  ldsr  value, 29, 6
%con value
  mov   value, r11
  ldsr  r11, 29, 6
%mem value
  mov   value, r11
  ldsr  r11, 29, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT7()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT7(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT7 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT7(uint32 value)
{
%reg value
  ldsr  value, 30, 6
%con value
  mov   value, r11
  ldsr  r11, 30, 6
%mem value
  mov   value, r11
  ldsr  r11, 30, 6
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA8()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA8(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA0 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA8(uint32 value)
{
%reg value
  ldsr  value, 0, 7
%con value
  mov   value, r11
  ldsr  r11, 0, 7
%mem value
  mov   value, r11
  ldsr  r11, 0, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA8()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA8(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA8 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA8(uint32 value)
{
%reg value
  ldsr  value, 1, 7
%con value
  mov   value, r11
  ldsr  r11, 1, 7
%mem value
  mov   value, r11
  ldsr  r11, 1, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT8()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT8(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT8 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT8(uint32 value)
{
%reg value
  ldsr  value, 2, 7
%con value
  mov   value, r11
  ldsr  r11, 2, 7
%mem value
  mov   value, r11
  ldsr  r11, 2, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA9()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA9(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA9 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA9(uint32 value)
{
%reg value
  ldsr  value, 4, 7
%con value
  mov   value, r11
  ldsr  r11, 4, 7
%mem value
  mov   value, r11
  ldsr  r11, 4, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA9()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA9(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA9 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA9(uint32 value)
{
%reg value
  ldsr  value, 5, 7
%con value
  mov   value, r11
  ldsr  r11, 5, 7
%mem value
  mov   value, r11
  ldsr  r11, 5, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT9()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT9(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT9 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT9(uint32 value)
{
%reg value
  ldsr  value, 6, 7
%con value
  mov   value, r11
  ldsr  r11, 6, 7
%mem value
  mov   value, r11
  ldsr  r11, 6, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA10()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA10(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA10 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA10(uint32 value)
{
%reg value
  ldsr  value, 8, 7
%con value
  mov   value, r11
  ldsr  r11, 8, 7
%mem value
  mov   value, r11
  ldsr  r11, 8, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA10()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA10(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA10 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA10(uint32 value)
{
%reg value
  ldsr  value, 9, 7
%con value
  mov   value, r11
  ldsr  r11, 9, 7
%mem value
  mov   value, r11
  ldsr  r11, 9, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT10()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT10(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT10 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT10(uint32 value)
{
%reg value
  ldsr  value, 10, 7
%con value
  mov   value, r11
  ldsr  r11, 10, 7
%mem value
  mov   value, r11
  ldsr  r11, 10, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA11()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA11(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA11 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA11(uint32 value)
{
%reg value
  ldsr  value, 12, 7
%con value
  mov   value, r11
  ldsr  r11, 12, 7
%mem value
  mov   value, r11
  ldsr  r11, 12, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA11()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA11(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA11 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA11(uint32 value)
{
%reg value
  ldsr  value, 13, 7
%con value
  mov   value, r11
  ldsr  r11, 13, 7
%mem value
  mov   value, r11
  ldsr  r11, 13, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT11()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT11(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT11 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT11(uint32 value)
{
%reg value
  ldsr  value, 14, 7
%con value
  mov   value, r11
  ldsr  r11, 14, 7
%mem value
  mov   value, r11
  ldsr  r11, 14, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA12()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA12(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA12 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA12(uint32 value)
{
%reg value
  ldsr  value, 16, 7
%con value
  mov   value, r11
  ldsr  r11, 16, 7
%mem value
  mov   value, r11
  ldsr  r11, 16, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA12()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA12(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA12 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA12(uint32 value)
{
%reg value
  ldsr  value, 17, 7
%con value
  mov   value, r11
  ldsr  r11, 17, 7
%mem value
  mov   value, r11
  ldsr  r11, 17, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT12()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT12(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT12 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT12(uint32 value)
{
%reg value
  ldsr  value, 18, 7
%con value
  mov   value, r11
  ldsr  r11, 18, 7
%mem value
  mov   value, r11
  ldsr  r11, 18, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA13()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA13(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA13 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA13(uint32 value)
{
%reg value
  ldsr  value, 20, 7
%con value
  mov   value, r11
  ldsr  r11, 20, 7
%mem value
  mov   value, r11
  ldsr  r11, 20, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA13()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA13(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA13 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA13(uint32 value)
{
%reg value
  ldsr  value, 21, 7
%con value
  mov   value, r11
  ldsr  r11, 21, 7
%mem value
  mov   value, r11
  ldsr  r11, 21, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT13()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT13(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT13 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT13(uint32 value)
{
%reg value
  ldsr  value, 22, 7
%con value
  mov   value, r11
  ldsr  r11, 22, 7
%mem value
  mov   value, r11
  ldsr  r11, 22, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA14()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA14(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA14 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA14(uint32 value)
{
%reg value
  ldsr  value, 24, 7
%con value
  mov   value, r11
  ldsr  r11, 24, 7
%mem value
  mov   value, r11
  ldsr  r11, 24, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA14()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA14(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA14 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA14(uint32 value)
{
%reg value
  ldsr  value, 25, 7
%con value
  mov   value, r11
  ldsr  r11, 25, 7
%mem value
  mov   value, r11
  ldsr  r11, 25, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT14()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT14(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT14 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT14(uint32 value)
{
%reg value
  ldsr  value, 26, 7
%con value
  mov   value, r11
  ldsr  r11, 26, 7
%mem value
  mov   value, r11
  ldsr  r11, 26, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA15()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA15(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA15 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPLA15(uint32 value)
{
%reg value
  ldsr  value, 28, 7
%con value
  mov   value, r11
  ldsr  r11, 28, 7
%mem value
  mov   value, r11
  ldsr  r11, 28, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA15()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPUA15(uint32 value)
 *  \brief      Sets the protection area maximum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPUA15 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPUA15(uint32 value)
{
%reg value
  ldsr  value, 29, 7
%con value
  mov   value, r11
  ldsr  r11, 29, 7
%mem value
  mov   value, r11
  ldsr  r11, 29, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT15()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPAT15(uint32 value)
 *  \brief      Sets the protection area attributes to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPAT15 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPAT15(uint32 value)
{
%reg value
  ldsr  value, 30, 7
%con value
  mov   value, r11
  ldsr  r11, 30, 7
%mem value
  mov   value, r11
  ldsr  r11, 30, 7
%error
}


/***********************************************************************************************************************
 *  Os_Hal_GetCoreID()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetCoreID(void)
 *  \brief        Returns the physical id of the core.
 *  \details      --no details--
 *
 *  \return       The current core id.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetCoreID(void)
{
  stsr  0, r10, 2
  OS_HAL_COREID_PROCESS(r10)
}


/***********************************************************************************************************************
 *  Os_Hal_GetIntState()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetIntState(void)
 *  \brief        Returns the interrupt state of the core.
 *  \details      --no details--
 *
 *  \return        0x0   Interrupt acknowledgment is enabled
 *                 0x20  Interrupt acknowledgment is disabled
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetIntState(void)
{
  stsr  5, r10, 0           /* r10 = PSW */
  andi   0x20, r10, r10
}


/***********************************************************************************************************************
 *  Os_Hal_GetPSW()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetPSW(void)
 *  \brief        Returns the program status word of the core.
 *  \details      --no details--
 *
 *  \return       PSW register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetPSW(void)
{
  stsr  5, r10, 0           /* r10 = PSW */
}


/***********************************************************************************************************************
 *  Os_Hal_GetPMR()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetPMR(void)
 *  \brief        Returns the interrupt priority masking register of the core.
 *  \details      --no details--
 *
 *  \return       PMR register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode and EI level interrupts disabled.
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetPMR(void)
{
  stsr    OS_HAL_PMR_GET(r10)
}


/***********************************************************************************************************************
 *  Os_Hal_GetASID()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetASID(void)
 *  \brief        Returns the address space identifier register of the core.
 *  \details      --no details--
 *
 *  \return       ASID register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetASID(void)
{
  stsr  OS_HAL_ASM_GET_ADDRESS_ID_REG(r10)
}


/***********************************************************************************************************************
 *  Os_Hal_GetSCCFG()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetSCCFG(void)
 *  \brief        Returns the SYSCALL operation settings  of the core.
 *  \details      --no details--
 *
 *  \return       SYSCALL operation settings
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetSCCFG(void)
{
  stsr  11, r10, 1          /* r10 = SCCFG */
}


/***********************************************************************************************************************
 *  Os_Hal_GetCTBP()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetCTBP(void)
 *  \brief        Returns the SYSCALL base pointer register of the core.
 *  \details      --no details--
 *
 *  \return       SYSCALL base pointer
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetCTBP(void)
{
  stsr  12, r10, 1          /* r10 = CTBP */
}


/***********************************************************************************************************************
 *  Os_Hal_GetSCBP()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetSCBP(void)
 *  \brief        Returns the CALLT base pointer register of the core.
 *  \details      --no details--
 *
 *  \return       CALLT base pointer
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetSCBP(void)
{
  stsr  20, r10, 0          /* r10 = SCBP */
}


/***********************************************************************************************************************
 *  Os_Hal_GetEIPC()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetEIPC(void)
 *  \brief        Gets the EIPC register of the core.
 *  \details      --no details--
 *
 *  \return       EIPC register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetEIPC(void)
{
  stsr  0, r10, 0           /* r10 = EIPC */
}


/***********************************************************************************************************************
 *  Os_Hal_GetEIPSW()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetEIPSW(void)
 *  \brief        Gets the EIPSW register of the core.
 *  \details      --no details--
 *
 *  \return       EIPSW register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetEIPSW(void)
{
  stsr  1, r10, 0           /* r10 = EIPSW */
}


/***********************************************************************************************************************
 *  Os_Hal_GetEIWR()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetEIWR(void)
 *  \brief        Gets the EI level exception working register of the core.
 *  \details      --no details--
 *
 *  \return       EIWR register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetEIWR(void)
{
  stsr  28, r10, 0          /* r10 = EIWR */
}


/***********************************************************************************************************************
 *  Os_Hal_GetFPSR()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetFPSR(void)
 *  \brief        Gets the floating-point configuration/status register of core.
 *  \details      --no details--
 *
 *  \return       FPSR register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode or enabled CU0 flag in PSW.
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetFPSR(void)
{
  stsr  6, r10, 0           /* r10 = FPSR */
}


/***********************************************************************************************************************
 *  Os_Hal_GetFPEPC()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetFPEPC(void)
 *  \brief        Gets the floating-point exception program counter register of core.
 *  \details      --no details--
 *
 *  \return       FPEPC register
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode or enabled CU0 flag in PSW.
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetFPEPC(void)
{
  stsr  7, r10, 0           /* r10 = FPEPC */
}


/***********************************************************************************************************************
 *  Os_Hal_EndOfInterrupt()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_EndOfInterrupt(void)
 *  \brief        Signals the end of an interrupt to the hardware.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
asm void Os_Hal_EndOfInterrupt(void)
{
%lab Os_Hal_EndOfIntLabel
   -- #10 Get the current PSW.
   stsr  PSW, r12
   -- #20 Disable all EIINT interrupts.
   di
   -- #30 Prepare PC
   mov   Os_Hal_EndOfIntLabel, r11
   ldsr  r11, EIPC
   -- #40 Prepare PSW
   ldsr  r12, EIPSW
   -- #50 Signal end of interrupt.
   eiret
Os_Hal_EndOfIntLabel:
}


/***********************************************************************************************************************
 *  Os_Hal_CallFunc()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_CallFunc(uint32* current, uint32* next)
 *  \brief        Enters a function defined by 'next' without performing a stack switch.
 *  \details      --no details--
 *
 *  \param[in]    current   The current context. Parameter must not be NULL.
 *  \param[in]    next      The context to be continued. Parameter must not be NULL.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
asm void Os_Hal_CallFunc(uint32* current, uint32* next)
{
%reg current %reg next %lab FuncCallReturn
  -- #10 Store current context
  pushsp  r20-r29            -- save registers r20 ... r29 to stack
  mov   FuncCallReturn, r11  -- get label for return
  st.w  r11, 0x00[current]   -- save PC
  st.w  SP,  0x10[current]   -- save SP
  -- #20 Prepare next context
  ld.w  0x20[next], r6       -- get first parameter
  ld.w  0x00[next], r12      -- get PC
  ld.w  0x04[next], r11      -- get PSW
  ldsr  r11, PSW             -- set PSW
  -- #30 Synchronize instruction fetches
  synci                      -- sync instructions
  -- #40 Execute next context
  jmp   [r12]                -- branch to function
FuncCallReturn:
  -- #50 Restore permanent registers of current context
  popsp r20-r29              -- restore registers r20 ... r29 from stack
%error
}


/***********************************************************************************************************************
 *  Os_Hal_CallFuncOnStack()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_CallFuncOnStack(uint32* current, uint32* next)
 *  \brief        Enters a function defined by 'next' with stack switch.
 *  \details      --no details--
 *
 *  \param[in]    current   The current context. Parameter must not be NULL.
 *  \param[in]    next      The context to be continued. Parameter must not be NULL.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
asm void Os_Hal_CallFuncOnStack(uint32* current, uint32* next)
{
%reg current %reg next %lab FuncCallReturn
  -- #10 store current context.
  pushsp  r20-r29            -- save registers r20 ... r29 to stack
  mov   FuncCallReturn, r11  -- get label for return
  st.w  r11, 0x00[current]   -- save PC
  st.w  SP,  0x10[current]   -- save SP
  -- #20 Switch the next context stack.
  ld.w  0x10[next], SP       -- set SP
#if (OS_CFG_MEMORY_PROTECTION == STD_ON)
  -- #30 Reprogram stack window.
  ld.w  0x14[next], r11      -- get MPLA0
  OS_HAL_ASM_SET_MPIDX_0
  OS_HAL_ASM_SET_MPLA0(r11)
  ld.w  0x18[next], r11      -- get MPUA0
  OS_HAL_ASM_SET_MPUA0(r11)
  ld.w  0x1C[next], r11      -- get ASID
  OS_HAL_ASM_SET_ADDRESS_ID_REG(r11)
  -- #40 Synchronize the pipeline.
  syncp                      -- sync pipeline
#endif
  -- #50 prepare next context.
  ld.w  0x20[next], r6       -- get first parameter
  ld.w  0x00[next], r12      -- get PC
  ld.w  0x04[next], r11      -- get PSW
  ldsr  r11, PSW             -- set PSW
  -- #60 Synchronize instruction fetch.
  synci                      -- sync instructions
  -- #70 Start next context
  jmp   [r12]                -- branch to function
  -- #80 Restore permanent register for current context on return to current context
FuncCallReturn:
  popsp r20-r29              -- restore registers r20 ... r29 from stack
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetSPR()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetSPR(uint32 regID, uint32 groupID, uint32 value)
 *  \brief      Writes a value to the given register.
 *  \details    --no details--
 *
 *  \param[in]    regID     The register to write to. Parameter must be a valid system register number.
 *  \param[in]    groupID   The register's group. Parameter must be a valid group number.
 *  \param[in]    value     The value to write to the register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm void Os_Hal_SetSPR(uint32 regID, uint32 groupID, uint32 value)
{
%con regID %con groupID %con value
  mov    value, r11
  ldsr   r11, regID, groupID
%con regID %con groupID %reg value
  ldsr   value, regID, groupID
%con regID %con groupID %mem value
  ld.w   value, r11
  ldsr   r11, regID, groupID
%error
}


/***********************************************************************************************************************
 *  Os_Hal_GetSPR()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetSPR(uint32 regID, uint32 groupID)
 *  \brief        Returns the given register
 *  \details      --no details--
 *
 *  \param[in]    regID     The register to read from. Parameter must be a valid system register number.
 *  \param[in]    groupID   The register's group. Parameter must be a valid group number.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetSPR(uint32 regID, uint32 groupID)
{
%con regID %con groupID
  stsr   regID, r10, groupID
%error
}


/***********************************************************************************************************************
 *  Os_Hal_StartNextThread()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_StartNextThread(uint32* current, uint32* next)
 *  \brief        Starts the next thread.
 *  \details      --no details--
 *
 *  \param[in]    current   The current context. Parameter must not be NULL.
 *  \param[in]    next      The context to be continued. Parameter must not be NULL.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
asm void Os_Hal_StartNextThread(uint32* current, uint32* next)
{
%reg current %reg next %lab Os_Hal_Thread_ReturnLabel
  -- #10 Store current context
  pushsp r20-r29            -- push r20 ... r29 onto stack
  mov   Os_Hal_Thread_ReturnLabel, r11
  st.w  r11, 0x00[current]  -- save PC
  st.w  SP,  0x10[current]  -- save SP
  -- #20 Prepare next context
  ld.w  0x10[next], SP      -- set SP
#if (OS_CFG_MEMORY_PROTECTION == STD_ON)
  -- #30 Reprogram stack window.
  ld.w  0x14[next], r11      -- get MPLA0
  OS_HAL_ASM_SET_MPIDX_0
  OS_HAL_ASM_SET_MPLA0(r11)
  ld.w  0x18[next], r11      -- get MPUA0
  OS_HAL_ASM_SET_MPUA0(r11)
  ld.w  0x1C[next], r11      -- get ASID
  OS_HAL_ASM_SET_ADDRESS_ID_REG(r11)
  -- #40 Synchronize the pipeline.
  syncp                      -- sync pipeline
#endif
  ld.w  0x00[next], r12     -- get entry address
  ld.w  0x04[next], r11     -- get PSW
  ldsr  r11, PSW            -- set PSW
  -- #50 Synchronize instruction fetch
  synci                     -- synchronize instruction
  -- #60 Execute new context
  jmp   [r12]               -- branch to entry address
Os_Hal_Thread_ReturnLabel:
  -- #70 Restore permanent register for current context on return to current context
  popsp r20-r29             -- restore r20 ... r29 from stack
%error
}


/***********************************************************************************************************************
 *  Os_Hal_StartNext()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_StartNext(uint32* next)
 *  \brief        Starts the next thread.
 *  \details      --no details--
 *
 *  \param[in]    next      The context to be continued. Parameter must not be NULL.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
asm void Os_Hal_StartNext(uint32* next)
{
%reg next
  -- #10 Prepare next context
  ld.w  0x00[next], r12  -- get entry address
  ld.w  0x04[next], r11  -- get PSW
  ld.w  0x10[next], SP   -- set SP
  ldsr  r11, PSW         -- set PSW
  -- #20 Synchronize instruction fetch
  synci                  -- synchronize instruction
  -- #30 Execute new context
  jmp   [r12]            -- branch to entry address
%error
}


/***********************************************************************************************************************
 *  Os_Hal_CountLeadingZeros()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_CountLeadingZeros(uint32 bitfield)
 *  \brief        Returns the number of leading zeros in bitfield.
 *  \details      --no details--
 *
 *  \param[in]    bitfield  The value to query.
 *
 *  \return       The number of leading zero bits.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
asm uint32 Os_Hal_CountLeadingZeros(uint32 bitfield)
{
%reg bitfield %lab Os_Hal_ReturnLabel
  -- #10 Prepare default return value
  mov    32, r10
  -- #20 Return default return value if passed bitfield is zero
  cmp    zero, bitfield
  be     Os_Hal_ReturnLabel
  -- #30 Else count leading zeros
  sch1l  bitfield, r10
  addi   -1, r10, r10
Os_Hal_ReturnLabel:
%error
}


/***********************************************************************************************************************
 *  Os_Hal_GetDisableLevel()
 **********************************************************************************************************************/
/*! \fn           Os_Hal_IntLevelType Os_Hal_GetDisableLevel(Os_Hal_IntLevelType Level)
 *  \brief        Sets the current interrupt level and returns the previous one.
 *  \details      --no details--
 *
 *  param[in]     The level to set. Parameter must be in range [0, OS_HAL_PMR_MASK].
 *
 *  \return       The previous interrupt level
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm Os_Hal_IntLevelType Os_Hal_GetDisableLevel(Os_Hal_IntLevelType Level)
{
%reg Level
  stsr   PSW, r11
  di
  stsr   PMR, r10
  ldsr   Level, PMR
  ldsr   r11, PSW
%con Level
  stsr   PSW, r11
  di
  stsr   PMR, r10
  mov    Level, r12
  ldsr   r12, PMR
  ldsr   r11, PSW
%mem Level
  stsr   PSW, r11
  di
  stsr   PMR, r10
  ld.w   Level, r12
  ldsr   r12, PMR
  ldsr   r11, PSW
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetLevelG3X()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetLevelG3X(Os_Hal_IntLevelType Level)
 *  \brief        Set the current interrupt level.
 *  \details      --no details--
 *
 *  \param[in]    The level to set.  Parameter must be in range [0, OS_HAL_PMR_MASK].
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm void Os_Hal_SetLevelG3X(Os_Hal_IntLevelType Level)
{
%reg Level
  stsr   PSW, r11
  di
  ldsr   Level, PMR
  ldsr   r11, PSW
%con Level
  stsr   PSW, r11
  di
  mov    Level, r12
  ldsr   r12, PMR
  ldsr   r11, PSW
%mem Level
  stsr   PSW, r11
  di
  ld.w   Level, r12
  ldsr   r12, PMR
  ldsr   r11, PSW
%error
}


/***********************************************************************************************************************
 *  Os_Hal_SetLevelG4X()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetLevelG4X(Os_Hal_IntLevelType Level)
 *  \brief        Set the current interrupt level.
 *  \details      --no details--
 *
 *  \param[in]    The level to set.  Parameter must be in range [0, OS_HAL_PMR_MASK].
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm void Os_Hal_SetLevelG4X(Os_Hal_IntLevelType Level)
{
%reg Level
  stsr   PSW, r11
  di
  ldsr   Level, 14, 2 /* PLMR = Level */
  ldsr   r11, PSW
%con Level
  stsr   PSW, r11
  di
  mov    Level, r12
  ldsr   r12, 14, 2 /* PLMR = Level */
  ldsr   r11, PSW
%mem Level
  stsr   PSW, r11
  di
  ld.w   Level, r12
  ldsr   r12, 14, 2 /* PLMR = Level */
  ldsr   r11, PSW
%error
}


/***********************************************************************************************************************
 *  Os_Hal_GetLevelG3X()
 **********************************************************************************************************************/
/*! \fn           Os_Hal_IntLevelType Os_Hal_GetLevelG3X(void)
 *  \brief        Returns the current interrupt level.
 *  \details      --no details--
 *
 *  \return       The current interrupt level.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm Os_Hal_IntLevelType Os_Hal_GetLevelG3X(void)
{
  stsr   PSW, r11
  di
  stsr   PMR, r10
  ldsr   r11, PSW
}


/***********************************************************************************************************************
 *  Os_Hal_GetLevelG4X()
 **********************************************************************************************************************/
/*! \fn           Os_Hal_IntLevelType Os_Hal_GetLevelG4X(void)
 *  \brief        Returns the current interrupt level.
 *  \details      --no details--
 *
 *  \return       The current interrupt level.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm Os_Hal_IntLevelType Os_Hal_GetLevelG4X(void)
{
  stsr   PSW, r11
  di
  stsr   14, r10, 2 /* R10 = PLMR */
  ldsr   r11, PSW
}


/***********************************************************************************************************************
 *  Os_Hal_TryGetLock()
 **********************************************************************************************************************/
/*! \fn           Os_Hal_SpinlockResultType Os_Hal_TryGetLock(volatile uint32* addr)
 *  \brief        Tries to get a spinlock
 *  \details      --no details--
 *
 *  \param[in]    addr    The spinlock to get. Parameter must not be NULL.
 *
 *  \return       Returns whether getting the spinlock succeeded.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
asm Os_Hal_SpinlockResultType Os_Hal_TryGetLock(volatile uint32* addr)
{
%reg addr %lab osLock_Success %lab osLock_NoSuccess
  -- #10 Load spinlock result from passed addr and aquire link for passed addr
  ldl.w   [addr], r10
  -- #20 Goto label osLock_NoSuccess if spinlock result is not 0
  cmp     r0, r10
  bnz     osLock_NoSuccess
  -- #30 Else try to write 1 to passed addr
  mov     1, r10
  stc.w   r10, [addr]
  -- #40 Goto osLock_Success if write access was successful (link was still valid)
  cmp     r0, r10
  bnz     osLock_Success
  -- #50 Else return 0
osLock_NoSuccess:
  -- #60 Write access successful. Return r10 (1)
  mov     0, r10
osLock_Success:
%mem addr %lab osLock_Success %lab osLock_NoSuccess
  -- #10 Load spinlock result from passed addr and aquire link for passed addr
  ld.w    addr, r12
  ldl.w   [r12], r10
  -- #20 Goto label osLock_NoSuccess if spinlock result is not 0
  cmp     r0, r10
  bnz     osLock_NoSuccess
  -- #30 Else try to write 1 to passed addr
  mov     1, r10
  stc.w   r10, [r12]
  -- #40 Goto osLock_Success if write access was successful (link was still valid)
  cmp     r0, r10
  bnz     osLock_Success
  -- #50 Else return 0
osLock_NoSuccess:
  mov     0, r10
  -- #60 Write access successful. Return r10 (1)
osLock_Success:
%error
}


/***********************************************************************************************************************
 *  Os_Hal_CoreGetCpuMode()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_CoreGetCpuMode(void)
 *  \brief        Returns the current CPU mode.
 *  \details      --no details--
 *
 *  \return       The current CPU mode. 1 = user mode, 0 = supervisor mode
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm uint32 Os_Hal_CoreGetCpuMode(void)
{
  stsr  PSW, r10
  shr   30, r10
}


/***********************************************************************************************************************
 *  Os_Hal_Init_MPIDn()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_Init_MPIDn(void)
 *  \brief        Initializes MPIDn registers.
 *  \details      --no details--
 *
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_Init_MPIDn(void)
{
  mov   0, r10
  ldsr  r10, 24, 5  /* MPID0 = r10 */
  mov   1, r10
  ldsr  r10, 25, 5  /* MPID1 = r10 */
  mov   2, r10
  ldsr  r10, 26, 5  /* MPID2 = r10 */
  mov   3, r10
  ldsr  r10, 27, 5  /* MPID3 = r10 */
  mov   4, r10
  ldsr  r10, 28, 5  /* MPID4 = r10 */
  mov   5, r10
  ldsr  r10, 29, 5  /* MPID5 = r10 */
  mov   6, r10
  ldsr  r10, 30, 5  /* MPID6 = r10 */
  mov   7, r10
  ldsr  r10, 31, 5  /* MPID7 = r10 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX0()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX0(void)
 *  \brief        Sets MPIDX register access MPU region 0 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX0(void)
{
  mov   0, r10
  ldsr  r10, 16, 5  /* MPIDX = 0 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX1()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX1(void)
 *  \brief        Sets MPIDX register access MPU region 1 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX1(void)
{
  mov   1, r10
  ldsr  r10, 16, 5  /* MPIDX = 1 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX2()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX2(void)
 *  \brief        Sets MPIDX register access MPU region 2 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX2(void)
{
  mov   2, r10
  ldsr  r10, 16, 5  /* MPIDX = 2 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX3()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX3(void)
 *  \brief        Sets MPIDX register access MPU region 3 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX3(void)
{
  mov   3, r10
  ldsr  r10, 16, 5  /* MPIDX = 3 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX4()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX4(void)
 *  \brief        Sets MPIDX register access MPU region 4 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX4(void)
{
  mov   4, r10
  ldsr  r10, 16, 5  /* MPIDX = 4 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX5()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX5(void)
 *  \brief        Sets MPIDX register access MPU region 5 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX5(void)
{
  mov   5, r10
  ldsr  r10, 16, 5  /* MPIDX = 5 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX6()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX6(void)
 *  \brief        Sets MPIDX register access MPU region 6 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX6(void)
{
  mov   6, r10
  ldsr  r10, 16, 5  /* MPIDX = 6 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX7()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX7(void)
 *  \brief        Sets MPIDX register access MPU region 7 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX7(void)
{
  mov   7, r10
  ldsr  r10, 16, 5  /* MPIDX = 7 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX8()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX8(void)
 *  \brief        Sets MPIDX register access MPU region 8 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX8(void)
{
  mov   8, r10
  ldsr  r10, 16, 5  /* MPIDX = 8 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX9()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX9(void)
 *  \brief        Sets MPIDX register access MPU region 9 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX9(void)
{
  mov   9, r10
  ldsr  r10, 16, 5  /* MPIDX = 9 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX10()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX10(void)
 *  \brief        Sets MPIDX register access MPU region 10 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX10(void)
{
  mov   10, r10
  ldsr  r10, 16, 5  /* MPIDX = 10 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX11()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX10(void)
 *  \brief        Sets MPIDX register access MPU region 11 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX11(void)
{
  mov   11, r10
  ldsr  r10, 16, 5  /* MPIDX = 11 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX12()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX12(void)
 *  \brief        Sets MPIDX register access MPU region 12 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX12(void)
{
  mov   12, r10
  ldsr  r10, 16, 5  /* MPIDX = 12 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX13()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX13(void)
 *  \brief        Sets MPIDX register access MPU region 130 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX13(void)
{
  mov   13, r10
  ldsr  r10, 16, 5  /* MPIDX = 13 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX14()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX14(void)
 *  \brief        Sets MPIDX register access MPU region 14 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX14(void)
{
  mov   14, r10
  ldsr  r10, 16, 5  /* MPIDX = 14 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX15()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX15(void)
 *  \brief        Sets MPIDX register access MPU region 15 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX15(void)
{
  mov   15, r10
  ldsr  r10, 16, 5  /* MPIDX = 15 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX16()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX16(void)
 *  \brief        Sets MPIDX register access MPU region 16 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX16(void)
{
  mov   16, r10
  ldsr  r10, 16, 5  /* MPIDX = 16 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX17()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX17(void)
 *  \brief        Sets MPIDX register access MPU region 17 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX17(void)
{
  mov   17, r10
  ldsr  r10, 16, 5  /* MPIDX = 17 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX18()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX18(void)
 *  \brief        Sets MPIDX register access MPU region 18 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX18(void)
{
  mov   18, r10
  ldsr  r10, 16, 5  /* MPIDX = 18 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX19()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX19(void)
 *  \brief        Sets MPIDX register access MPU region 19 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX19(void)
{
  mov   19, r10
  ldsr  r10, 16, 5  /* MPIDX = 19 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX20()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX20(void)
 *  \brief        Sets MPIDX register access MPU region 20 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX20(void)
{
  mov   20, r10
  ldsr  r10, 16, 5  /* MPIDX = 20 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX21()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX20(void)
 *  \brief        Sets MPIDX register access MPU region 21 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX21(void)
{
  mov   21, r10
  ldsr  r10, 16, 5  /* MPIDX = 21 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX22()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX22(void)
 *  \brief        Sets MPIDX register access MPU region 22 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX22(void)
{
  mov   22, r10
  ldsr  r10, 16, 5  /* MPIDX = 22 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX23()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX20(void)
 *  \brief        Sets MPIDX register access MPU region 23 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX23(void)
{
  mov   23, r10
  ldsr  r10, 16, 5  /* MPIDX = 23 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX24()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX24(void)
 *  \brief        Sets MPIDX register access MPU region 24 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX24(void)
{
  mov   24, r10
  ldsr  r10, 16, 5  /* MPIDX = 24 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX25()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX25(void)
 *  \brief        Sets MPIDX register access MPU region 25 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX25(void)
{
  mov   25, r10
  ldsr  r10, 16, 5  /* MPIDX = 25 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX26()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX26(void)
 *  \brief        Sets MPIDX register access MPU region 26 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX26(void)
{
  mov   26, r10
  ldsr  r10, 16, 5  /* MPIDX = 26 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX27()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX27(void)
 *  \brief        Sets MPIDX register access MPU region 27 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX27(void)
{
  mov   27, r10
  ldsr  r10, 16, 5  /* MPIDX = 27 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX28()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX28(void)
 *  \brief        Sets MPIDX register access MPU region 28 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX28(void)
{
  mov   28, r10
  ldsr  r10, 16, 5  /* MPIDX = 28 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX29()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX29(void)
 *  \brief        Sets MPIDX register access MPU region 29 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX29(void)
{
  mov   29, r10
  ldsr  r10, 16, 5  /* MPIDX = 29 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX30()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX30(void)
 *  \brief        Sets MPIDX register access MPU region 30 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX30(void)
{
  mov   30, r10
  ldsr  r10, 16, 5  /* MPIDX = 30 */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX31()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX31(void)
 *  \brief        Sets MPIDX register access MPU region 31 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetMPIDX31(void)
{
  mov   31, r10
  ldsr  r10, 16, 5  /* MPIDX = 31 */
}


/***********************************************************************************************************************
 *  Os_Hal_GetSPID()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetSPID(void)
 *  \brief        Returns the current value of the SPID register.
 *  \details      --no details--
 *
 *  \return       The current System Protection Identifier.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
asm uint32 Os_Hal_GetSPID(void)
{
  stsr  0, r10, 1   /* r10 = SPID */
}


/***********************************************************************************************************************
 *  Os_Hal_SetSPID()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_SetSPID(void)
 *  \brief        Sets the SPID register to given value.
 *  \details      --no details--
 *
 *  \param[in]    The value to be set to the System Protection Identifier.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
asm void Os_Hal_SetSPID(uint32 value)
{
%reg value
  ldsr  value, 0, 1 /* SPID = value */
%con value
  mov   value, r10
  ldsr  r10, 0, 1   /* SPID = r10 */
%mem value
  ld.w  value, r10
  ldsr  r10, 0, 1   /* SPID = r10 */
%error
}


/* ECO_IGNORE_BLOCK_END */

#endif /* OS_HAL_COMPILER_GREENHILLSINT_H */


#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Compiler_GreenHillsInt.h
 **********************************************************************************************************************/

