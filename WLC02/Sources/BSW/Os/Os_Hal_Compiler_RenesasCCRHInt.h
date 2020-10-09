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
 * \file       Os_Hal_Compiler_RenesasCCRHInt.h
 * \brief      Compiler abstraction for compiler Renesas CC_RH
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_COMPILER_RENESASCCRH_H
# define OS_HAL_COMPILER_RENESASCCRH_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"
# include "Os_Hal_Core_Types.h"
# include "Os_MemoryProtection_Cfg.h"


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
# define OS_HAL_NOINLINE

/*! \brief    This attribute tells the compiler that a function never returns.
 *  \details
 * It can then optimize without regard to what would happen if the function ever did return.
 * This makes slightly better code. More importantly, it helps avoid spurious warnings of uninitialized variables.
 *
 * Availability: GCC ('noreturn'), Diab, Tasking, GreenHills
 */
# define OS_NORETURN

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
# define OS_PURE



#if 0
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
 *  Os_Hal_DisableGlobal()
 **********************************************************************************************************************/
#pragma inline_asm Os_Hal_DisableGlobal
static void Os_Hal_DisableGlobal(void)
{
  di
}

 /***********************************************************************************************************************
  *  Os_Hal_EnableGlobal()
  **********************************************************************************************************************/
#pragma inline_asm Os_Hal_EnableGlobal
static void Os_Hal_EnableGlobal(void)
{
  ei
}

 /***********************************************************************************************************************
  *  Os_Hal_SyncInstruction()
  **********************************************************************************************************************/
#pragma inline_asm Os_Hal_SyncInstruction
static void Os_Hal_SyncInstruction(void)
{
  synci
}


 /***********************************************************************************************************************
  *  Os_Hal_SyncPipeline()
  **********************************************************************************************************************/
#pragma inline_asm Os_Hal_SyncPipeline
static void Os_Hal_SyncPipeline(void)
{
  syncp
}


 /***********************************************************************************************************************
  *  Os_Hal_SyncMemory()
  **********************************************************************************************************************/
#pragma inline_asm Os_Hal_SyncMemory
static void Os_Hal_SyncMemory(void)
{
  syncm
}


 /***********************************************************************************************************************
  *  Os_Hal_NOP()
  **********************************************************************************************************************/
#pragma inline_asm Os_Hal_NOP
static void Os_Hal_NOP(void)
{
  nop
}


/***********************************************************************************************************************
 *  Os_Hal_GetSP()
 **********************************************************************************************************************/
 /*! \fn           uint32 Os_Hal_GetSP(void)
  *  \brief        Set the current stack pointer.
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
#pragma inline_asm Os_Hal_GetSP
static uint32 Os_Hal_GetSP(void)
{
  mov   sp, r10
}


/***********************************************************************************************************************
  *  Os_Hal_SetLP()
  **********************************************************************************************************************/
 /*! \fn           void Os_Hal_SetLP(uint32 val)
  *  \brief        Set the current link pointer.
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
#pragma inline_asm Os_Hal_SetLP
static void Os_Hal_SetLP(uint32 val)
{
   mov  r6, lp
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
#pragma inline_asm Os_Hal_GetLP
static uint32 Os_Hal_GetLP(void)
{
  mov  lp, r10
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
#pragma inline_asm Os_Hal_SetPSW
static void Os_Hal_SetPSW(uint32 value)
{
  ldsr  r6, 5, 0
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
#pragma inline_asm Os_Hal_SetPMR
static void Os_Hal_SetPMR(uint32 value)
{
  ldsr  r6, 11, 2
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
#pragma inline_asm Os_Hal_SetASID
static void Os_Hal_SetASID(uint32 value)
{
  ldsr  r6, 7, 2
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
#pragma inline_asm Os_Hal_SetCTBP
static void Os_Hal_SetCTBP(uint32 value)
{
  ldsr  r6, 20, 0
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
#pragma inline_asm Os_Hal_SetSCCFG
static void Os_Hal_SetSCCFG(uint32 value)
{
  ldsr  r6, 11, 1
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
#pragma inline_asm Os_Hal_SetSCBP
static void Os_Hal_SetSCBP(uint32 value)
{
  ldsr  r6, 12, 1
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
#pragma inline_asm Os_Hal_SetEIPC
static void Os_Hal_SetEIPC(uint32 value)
{
  ldsr  r6, 0, 0
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
#pragma inline_asm Os_Hal_SetEIPSW
static void Os_Hal_SetEIPSW(uint32 value)
{
  ldsr  r6, 1, 0
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
#pragma inline_asm Os_Hal_SetEIWR
static void Os_Hal_SetEIWR(uint32 value)
{
  ldsr  r6, 28, 0
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
#pragma inline_asm Os_Hal_SetFPSR
static void Os_Hal_SetFPSR(uint32 value)
{
  ldsr  r6, 6, 0
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
#pragma inline_asm Os_Hal_SetFPEPC
static void Os_Hal_SetFPEPC(uint32 value)
{
  ldsr  r6, 7, 0
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
#pragma inline_asm Os_Hal_SetEBASE
static void Os_Hal_SetEBASE(uint32 value)
{
  ldsr  r6, 3, 1
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
#pragma inline_asm Os_Hal_SetINTBP
static void Os_Hal_SetINTBP(uint32 value)
{
  ldsr  r6, 4, 1
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
#pragma inline_asm Os_Hal_SetINTCFG
static void Os_Hal_SetINTCFG(uint32 value)
{
  ldsr  r6, 13, 2
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
#pragma inline_asm Os_Hal_SetMPM
static void Os_Hal_SetMPM(uint32 value)
{
  ldsr  r6, 0, 5
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
#pragma inline_asm Os_Hal_SetMPRC
static void Os_Hal_SetMPRC(uint32 value)
{
  ldsr  r6, 1, 5
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
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
#pragma inline_asm Os_Hal_GetMPLA0
static uint32 Os_Hal_GetMPLA0(void)
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
#pragma inline_asm Os_Hal_SetMPLA0
static void Os_Hal_SetMPLA0(uint32 value)
{
  ldsr  r6, 0, 6
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
#pragma inline_asm Os_Hal_GetMPUA0
static uint32 Os_Hal_GetMPUA0(void)
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
#pragma inline_asm Os_Hal_SetMPUA0
static void Os_Hal_SetMPUA0(uint32 value)
{
  ldsr  r6, 1, 6
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
#pragma inline_asm Os_Hal_SetMPAT0
static void Os_Hal_SetMPAT0(uint32 value)
{
  ldsr  r6, 2, 6
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
#pragma inline_asm Os_Hal_SetMPLA1
static void Os_Hal_SetMPLA1(uint32 value)
{
  ldsr  r6, 4, 6
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
#pragma inline_asm Os_Hal_SetMPUA1
static void Os_Hal_SetMPUA1(uint32 value)
{
  ldsr  r6, 5, 6
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
#pragma inline_asm Os_Hal_SetMPAT1
static void Os_Hal_SetMPAT1(uint32 value)
{
  ldsr  r6, 6, 6
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
#pragma inline_asm Os_Hal_SetMPLA2
static void Os_Hal_SetMPLA2(uint32 value)
{
  ldsr  r6, 8, 6
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
#pragma inline_asm Os_Hal_SetMPUA2
static void Os_Hal_SetMPUA2(uint32 value)
{
  ldsr  r6, 9, 6
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
#pragma inline_asm Os_Hal_SetMPAT2
static void Os_Hal_SetMPAT2(uint32 value)
{
  ldsr  r6, 10, 6
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
#pragma inline_asm Os_Hal_SetMPLA3
static void Os_Hal_SetMPLA3(uint32 value)
{
  ldsr  r6, 12, 6
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
#pragma inline_asm Os_Hal_SetMPUA3
static void Os_Hal_SetMPUA3(uint32 value)
{
  ldsr  r6, 13, 6
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
#pragma inline_asm Os_Hal_SetMPAT3
static void Os_Hal_SetMPAT3(uint32 value)
{
  ldsr  r6, 14, 6
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
#pragma inline_asm Os_Hal_SetMPLA4
static void Os_Hal_SetMPLA4(uint32 value)
{
  ldsr  r6, 16, 6
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
#pragma inline_asm Os_Hal_SetMPUA4
static void Os_Hal_SetMPUA4(uint32 value)
{
  ldsr  r6, 17, 6
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
#pragma inline_asm Os_Hal_SetMPAT4
static void Os_Hal_SetMPAT4(uint32 value)
{
  ldsr  r6, 18, 6
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
#pragma inline_asm Os_Hal_SetMPLA5
static void Os_Hal_SetMPLA5(uint32 value)
{
  ldsr  r6, 20, 6
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
#pragma inline_asm Os_Hal_SetMPUA5
static void Os_Hal_SetMPUA5(uint32 value)
{
  ldsr  r6, 21, 6
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
#pragma inline_asm Os_Hal_SetMPAT5
static void Os_Hal_SetMPAT5(uint32 value)
{
  ldsr  r6, 22, 6
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
#pragma inline_asm Os_Hal_SetMPLA6
static void Os_Hal_SetMPLA6(uint32 value)
{
  ldsr  r6, 24, 6
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
#pragma inline_asm Os_Hal_SetMPUA6
static void Os_Hal_SetMPUA6(uint32 value)
{
  ldsr  r6, 25, 6
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
#pragma inline_asm Os_Hal_SetMPAT6
static void Os_Hal_SetMPAT6(uint32 value)
{
  ldsr  r6, 26, 6
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
#pragma inline_asm Os_Hal_SetMPLA7
static void Os_Hal_SetMPLA7(uint32 value)
{
  ldsr  r6, 28, 6
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
#pragma inline_asm Os_Hal_SetMPUA7
static void Os_Hal_SetMPUA7(uint32 value)
{
  ldsr  r6, 29, 6
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
#pragma inline_asm Os_Hal_SetMPAT7
static void Os_Hal_SetMPAT7(uint32 value)
{
  ldsr  r6, 30, 6
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
#pragma inline_asm Os_Hal_SetMPLA8
static void Os_Hal_SetMPLA8(uint32 value)
{
  ldsr  r6, 0, 7
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
#pragma inline_asm Os_Hal_SetMPUA8
static void Os_Hal_SetMPUA8(uint32 value)
{
  ldsr  r6, 1, 7
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
#pragma inline_asm Os_Hal_SetMPAT8
static void Os_Hal_SetMPAT8(uint32 value)
{
  ldsr  r6, 2, 7
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
#pragma inline_asm Os_Hal_SetMPLA9
static void Os_Hal_SetMPLA9(uint32 value)
{
  ldsr  r6, 4, 7
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
#pragma inline_asm Os_Hal_SetMPUA9
static void Os_Hal_SetMPUA9(uint32 value)
{
  ldsr  r6, 5, 7
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
#pragma inline_asm Os_Hal_SetMPAT9
static void Os_Hal_SetMPAT9(uint32 value)
{
  ldsr  r6, 6, 7
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
#pragma inline_asm Os_Hal_SetMPLA10
static void Os_Hal_SetMPLA10(uint32 value)
{
  ldsr  r6, 8, 7
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
#pragma inline_asm Os_Hal_SetMPUA10
static void Os_Hal_SetMPUA10(uint32 value)
{
  ldsr  r6, 9, 7
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
#pragma inline_asm Os_Hal_SetMPAT10
static void Os_Hal_SetMPAT10(uint32 value)
{
  ldsr  r6, 10, 7
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
#pragma inline_asm Os_Hal_SetMPLA11
static void Os_Hal_SetMPLA11(uint32 value)
{
  ldsr  r6, 12, 7
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
#pragma inline_asm Os_Hal_SetMPUA11
static void Os_Hal_SetMPUA11(uint32 value)
{
  ldsr  r6, 13, 7
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
#pragma inline_asm Os_Hal_SetMPAT11
static void Os_Hal_SetMPAT11(uint32 value)
{
  ldsr  r6, 14, 7
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
#pragma inline_asm Os_Hal_SetMPLA12
static void Os_Hal_SetMPLA12(uint32 value)
{
  ldsr  r6, 16, 7
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
#pragma inline_asm Os_Hal_SetMPUA12
static void Os_Hal_SetMPUA12(uint32 value)
{
  ldsr  r6, 17, 7
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
#pragma inline_asm Os_Hal_SetMPAT12
static void Os_Hal_SetMPAT12(uint32 value)
{
  ldsr  r6, 18, 7
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
#pragma inline_asm Os_Hal_SetMPLA13
static void Os_Hal_SetMPLA13(uint32 value)
{
  ldsr  r6, 20, 7
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
#pragma inline_asm Os_Hal_SetMPUA13
static void Os_Hal_SetMPUA13(uint32 value)
{
  ldsr  r6, 21, 7
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
#pragma inline_asm Os_Hal_SetMPAT13
static void Os_Hal_SetMPAT13(uint32 value)
{
  ldsr  r6, 22, 7
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
#pragma inline_asm Os_Hal_SetMPLA14
static void Os_Hal_SetMPLA14(uint32 value)
{
  ldsr  r6, 24, 7
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
#pragma inline_asm Os_Hal_SetMPUA14
static void Os_Hal_SetMPUA14(uint32 value)
{
  ldsr  r6, 25, 7
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
#pragma inline_asm Os_Hal_SetMPAT14
static void Os_Hal_SetMPAT14(uint32 value)
{
  ldsr  r6, 26, 7
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
#pragma inline_asm Os_Hal_SetMPLA15
static void Os_Hal_SetMPLA15(uint32 value)
{
  ldsr  r6, 28, 7
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
#pragma inline_asm Os_Hal_SetMPUA15
static void Os_Hal_SetMPUA15(uint32 value)
{
  ldsr  r6, 29, 7
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
#pragma inline_asm Os_Hal_SetMPAT15
static void Os_Hal_SetMPAT15(uint32 value)
{
  ldsr  r6, 30, 7
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
#pragma inline_asm Os_Hal_GetCoreID
static uint32 Os_Hal_GetCoreID(void)
{
  stsr  0, r10, 2
  shr   17, r10
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
#pragma inline_asm Os_Hal_GetIntState
static uint32 Os_Hal_GetIntState(void)
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
#pragma inline_asm Os_Hal_GetPSW
static uint32 Os_Hal_GetPSW(void)
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
#pragma inline_asm Os_Hal_GetPMR
static uint32 Os_Hal_GetPMR(void)
{
  stsr  11, r10, 2          /* r10 = PMR */
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
#pragma inline_asm Os_Hal_GetASID
static uint32 Os_Hal_GetASID(void)
{
  stsr  7, r10, 2           /* r10 = ASID */
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
#pragma inline_asm Os_Hal_GetSCCFG
static uint32 Os_Hal_GetSCCFG(void)
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
#pragma inline_asm Os_Hal_GetCTBP
static uint32 Os_Hal_GetCTBP(void)
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
#pragma inline_asm Os_Hal_GetSCBP
static uint32 Os_Hal_GetSCBP(void)
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
#pragma inline_asm Os_Hal_GetEIPC
static uint32 Os_Hal_GetEIPC(void)
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
#pragma inline_asm Os_Hal_GetEIPSW
static uint32 Os_Hal_GetEIPSW(void)
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
#pragma inline_asm Os_Hal_GetEIWR
static uint32 Os_Hal_GetEIWR(void)
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
#pragma inline_asm Os_Hal_GetFPSR
static uint32 Os_Hal_GetFPSR(void)
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
#pragma inline_asm Os_Hal_GetFPEPC
static uint32 Os_Hal_GetFPEPC(void)
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
#pragma inline_asm Os_Hal_EndOfInterrupt
static void Os_Hal_EndOfInterrupt(void)
{
.local Os_Hal_EndOfIntLabel
   /* #10 Get the current PSW. */
   stsr  5, r12, 0 /* r12 = PSW */
   /* #20 Disable all EIINT interrupts. */
   di
   /* #30 Prepare PC */
   mov   #Os_Hal_EndOfIntLabel, r11
   ldsr  r11, 0, 0  /* EIPC = r11 */
   /* #40 Prepare PSW */
   ldsr  r12, 1, 0 /* EIPSW = r12 */
   /* #50 Signal end of interrupt. */
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
#pragma inline_asm Os_Hal_CallFunc
 static void Os_Hal_CallFunc(uint32* current, const uint32* next)
 {
 .local FuncCallReturnCallFunc
  /* #10 Store current context */
  pushsp  r20,r29                             /* save registers r20 ... r29 to stack */
  mov   #FuncCallReturnCallFunc, r11   /* get label for return */
  st.w  r11, 0x00[r6]                         /* save PC, r6 = current */
  st.w  SP,  0x10[r6]                         /* save SP */
  /* #20 Prepare next context */
  ld.w  0x20[r7], r6                          /* get first parameter r7=next */
  ld.w  0x00[r7], r12                         /* get PC */
  ld.w  0x04[r7], r11                         /* get PSW */
  ldsr  r11, 5, 0                             /* PSW = r11 */
  /* #30 Synchronize instruction fetches */
  synci                                       /* sync instructions */
  /* #40 Execute next context */
  jmp   [r12]                                 /* branch to function */
FuncCallReturnCallFunc:
  /* #50 Restore permanent registers of current context */
  popsp r20,r29                               /* restore registers r20 ... r29 from stack */
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
#pragma inline_asm Os_Hal_CallFuncOnStack
 static void Os_Hal_CallFuncOnStack(uint32* current, const uint32* next)
 {
 .local FuncCallReturnCallFuncOnStack
  /* #10 store current context. */
  pushsp  r20,r29            /* save registers r20 ... r29 to stack */
  mov   #FuncCallReturnCallFuncOnStack, r11  /* get label for return */
  st.w  r11, 0x00[r6]        /* save PC */
  st.w  SP,  0x10[r6]        /* save SP */
  /* #20 Switch the next context stack. */
  ld.w  0x10[r7], SP         /* set SP */
#if (OS_CFG_MEMORY_PROTECTION == STD_ON)
  /* #30 Reprogram stack window. */
  ld.w  0x14[r7], r11        /* get MPLA0 */
  ldsr  r11, 0, 6            /* set MPLA0 */
  ld.w  0x18[r7], r11        /* get MPUA0 */
  ldsr  r11, 1, 6            /* set MPUA0 */
  ld.w  0x1C[r7], r11        /* get ASID */
  ldsr  r11, 7, 2            /* set ASID */
  /* #40 Synchronize the pipeline. */
  syncp                      /* sync pipeline */
#endif
  /* #50 prepare next context. */
  ld.w  0x20[r7], r6         /* get first parameter */
  ld.w  0x00[r7], r12        /* get PC */
  ld.w  0x04[r7], r11        /* get PSW */
  ldsr  r11, 5, 0            /* set PSW */
  /* #60 Synchronize instruction fetch. */
  synci                      /* sync instructions */
  /* #70 Start next context */
  jmp   [r12]                /* branch to function */
  /* #80 Restore permanent register for current context on return to current context. */
FuncCallReturnCallFuncOnStack:
  popsp r20,r29              /* restore registers r20 ... r29 from stack */
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
#pragma inline_asm Os_Hal_StartNextThread
static void Os_Hal_StartNextThread(uint32* current,const uint32* next)
{
 .local Os_Hal_Thread_ReturnLabel
   /* #10 Store current context */
  pushsp r20,r29            /* push r20 ... r29 onto stack */
  mov   #Os_Hal_Thread_ReturnLabel, r11
  st.w  r11, 0x00[r6]       /* save PC */
  st.w  SP,  0x10[r6]       /* save SP */
   /* #20 Prepare next context */
   ld.w  0x10[r7], SP        /* set SP */
 #if (OS_CFG_MEMORY_PROTECTION == STD_ON)
   /* #30 Reprogram stack window. */
   ld.w  0x14[r7], r11       /* get MPLA0 */
   ldsr  r11, 0, 6           /* set MPLA0 */
   ld.w  0x18[r7], r11       /* get MPUA0 */
   ldsr  r11, 1, 6           /* set MPUA0 */
   ld.w  0x1C[r7], r11       /* get ASID */
   ldsr  r11, 7, 2           /* set ASID */
   /* #40 Synchronize the pipeline. */
   syncp                     /* sync pipeline */
 #endif
   ld.w  0x00[r7], r12       /* get entry address */
   ld.w  0x04[r7], r11       /* get PSW */
   ldsr  r11, 5, 0           /* set PSW */
   /* #50 Synchronize instruction fetch. */
   synci                     /* synchronize instruction */
   /* #60 Execute new context. */
   jmp   [r12]               /* branch to entry address */
 Os_Hal_Thread_ReturnLabel:
   /* #70 Restore permanent register for current context on return to current context */
   popsp r20,r29             /* restore r20 ... r29 from stack */
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
#pragma inline_asm Os_Hal_StartNext
static void Os_Hal_StartNext(const uint32* next)
{
  /* #10 Prepare next context */
  ld.w  0x00[r6], r12       /* get entry address */
  ld.w  0x04[r6], r11       /* get PSW */
  ld.w  0x10[r6], SP        /* set SP */
  ldsr  r11, 5, 0           /* set PSW */
  /* #20 Synchronize instruction fetch */
  synci                     /* synchronize instruction */
  /* #30 Execute new context */
  jmp   [r12]               /* branch to entry address */
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
#pragma inline_asm Os_Hal_CountLeadingZeros
static uint32 Os_Hal_CountLeadingZeros(uint32 bitfield)
{
 .local Os_Hal_ReturnLabel
  /* #10 Prepare default return value. */
  mov    32, r10
  /* #20 Return default return value if passed bitfield is zero. */
  cmp    zero, r6           /* r6 = bitfield */
  be     Os_Hal_ReturnLabel
  /* #30 Else count leading zeros */
  sch1l  r6, r10
  addi   -1, r10, r10
Os_Hal_ReturnLabel:
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
#pragma inline_asm Os_Hal_GetDisableLevel
static Os_Hal_IntLevelType Os_Hal_GetDisableLevel(Os_Hal_IntLevelType Level)
{
  stsr   5, r11, 0          /* r11 = PSW */
  di                        /* disable interrupts */
  stsr   11, r10, 2         /* r10 = PMR */
  mov    r6, r12            /* r6 = Level */
  ldsr   r12, 11, 2         /* PMR = r12 */
  ldsr   r11, 5, 0          /* PSW = r11 */
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
#pragma inline_asm Os_Hal_SetLevelG3X
static void Os_Hal_SetLevelG3X(Os_Hal_IntLevelType Level)
{
   stsr   5, r11, 0          /* r11 = PSW */
   di                        /* Disable interrupts */
   ldsr   r6, 11, 2          /* PMR = Level (Level = r6) */
   ldsr   r11, 5, 0          /* PSW = r11 */
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
#pragma inline_asm Os_Hal_GetLevelG3X
static Os_Hal_IntLevelType Os_Hal_GetLevelG3X(void)
{
  stsr   5, r11, 0          /* r11 = PSW */
  di                        /* Disable interrupts */
  stsr   11, r10, 2         /* r10 = PMR */
  ldsr   r11, 5, 0          /* PSW = r11 */
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
#pragma inline_asm Os_Hal_TryGetLock
static Os_Hal_SpinlockResultType Os_Hal_TryGetLock(volatile uint32* addr)
{
  .local osLock_NoSuccess
  .local osLock_Success
  /* #10 Load spinlock result from passed addr and aquire link for passed addr */
  ldl.w   [r6], r10         /* r10 = addr */
  /* #20 Goto label osLock_NoSuccess if spinlock result is not 0 */
  cmp     r0, r10
  bnz     osLock_NoSuccess
  /* #30 Else try to write 1 to passed addr */
  mov     1, r10
  stc.w   r10, [r6]
  /* #40 Goto osLock_Success if write access was successful (link was still valid) */
  cmp     r0, r10
  bnz     osLock_Success
  /* #50 Else return 0 */
osLock_NoSuccess:
  /* #60 Write access successful. Return r10 (1) */
  mov     0, r10
osLock_Success:
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
#pragma inline_asm Os_Hal_CoreGetCpuMode
static uint32 Os_Hal_CoreGetCpuMode(void)
{
  stsr  5, r10, 0           /* r10 = PSW */
  shr   30, r10
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
#pragma inline_asm Os_Hal_SetMPIDX0
static void Os_Hal_SetMPIDX0(void)
{
  /* empty function, only needed for G4X cores */
}


/* ECO_IGNORE_BLOCK_END */

#endif /* OS_HAL_COMPILER_GREENHILLSINT_H */


#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Compiler_RenesasCCRHInt.h
 **********************************************************************************************************************/

