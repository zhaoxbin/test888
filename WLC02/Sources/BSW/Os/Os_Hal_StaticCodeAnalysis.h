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
 *  \file
 *  \brief   Compiler abstraction of the ANSI C compiler used for MISRA and ReviewHelper
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_STATICCODEANALYSIS_H
# define OS_HAL_STATICCODEANALYSIS_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/*! \brief    Force the compiler to inline a function.
 *  \details
 *  This attribute forces the compiler to inline the specified function, regardless of the optimization strategy of the
 *  compiler itself.
 */
# define OS_ALWAYS_INLINE


/*! \brief    This attribute tells the compiler that a function never returns.
 *  \details
 *  It can then optimize without regard to what would happen if the function ever did return.
 *  This makes slightly better code. More importantly, it helps avoid spurious warnings of uninitialized variables.
 */
# define OS_NORETURN


/*! \brief    This attribute forces inlining of all function calls in a function, including nested function calls.
 * \details
 * Whether the function itself is considered for inlining depends on its size and the current inlining parameters.
 */
# define OS_FLATTEN


/*! \brief    This attribute tells that a function has no side effects and will not access global data.
 *  \details
 * This can help the compiler to optimize code. Such functions do not examine any values except their arguments,
 * and have no effects except the return value. This is just slightly more strict class than the OS_PURE attribute,
 * since function is not allowed to read global memory.
 */
# define OS_NOSIDEEFFECTS


/*! \brief    This attribute tells that a function has no side effects, although it may read global data.
 *  \details
 * Such pure functions can be subject to common subexpression elimination and loop optimization.
 */
# define OS_PURE
# define OS_NAKED
# define OS_HAL_NOINLINE

# define OS_HAL_RH850_REGMODE   (32u)

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/*! \brief      Declares a function with a compiler specific attribute.
 *  \details    The implementations prototype has to be created with OS_FUNC_ATTRIBUTE_DEFINITION.
 *
 *  \param[in]  rettype       The return type of the function.
 *  \param[in]  memclass      The memory class of the function.
 *  \param[in]  attribute     The function attribute {OS_ALWAYS_INLINE; OS_PURE, ...}.
 *  \param[in]  functionName  The function name.
 *  \param[in]  arguments     The function arguments in brackets. E.g. (uint8 a, uint16 b) or (void).
 *
 *  \note       Prevent multiple usage of memclass in case of pointer return type.
 */
# define OS_FUNC_ATTRIBUTE_DECLARATION(rettype, memclass, attribute, functionName, arguments)                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */ \
      attribute FUNC(rettype, memclass) functionName arguments                                                          /* PRQA S 0850 */ /* MD_MSR_MacroArgumentEmpty */


/*! \brief      Provides a function prototype for function definitions with a compiler specific attribute.
 *  \details    The declaration has to be created with OS_FUNC_ATTRIBUTE_DECLARE.
 *  \param[in]  rettype       The return type of the function.
 *  \param[in]  memclass      The memory class of the function.
 *  \param[in]  attribute     The function attribute {OS_ALWAYS_INLINE; OS_PURE, ...}.
 *  \param[in]  functionName  The function name.
 *  \param[in]  arguments     The function arguments in brackets. E.g. (uint8 a, uint16 b) or (void).
 *
 *  \note       Prevent multiple usage of memclass in case of pointer return type.
 */
# define OS_FUNC_ATTRIBUTE_DEFINITION(rettype, memclass, attribute, functionName, arguments)                            /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */ \
      attribute FUNC(rettype, memclass)  functionName arguments                                                         /* PRQA S 0850 */ /* MD_MSR_MacroArgumentEmpty */



/*! \brief    Tells the compiler that the conditional statement is likely to be true.
 *  \details
 *  The compiler, in turn, can then perform block reordering, and other optimization to
 *  improve the performance of conditional branches.
 *
 *  \param[in]  CONDITION   The condition which is likely to be true
 */
# define OS_LIKELY(CONDITION)                   (CONDITION)                                                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! \brief    Tells the compiler that the conditional statement is likely to be false.
 *  \details
 *  The compiler, in turn, can then perform block reordering, and other optimization to
 *  improve the performance of conditional branches.
 *
 *  \param[in]  CONDITION   The condition which is likely to be false
 */
# define OS_UNLIKELY(CONDITION)                 (CONDITION)                                                             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/*! \brief         Abstraction of executing arbitrary assembler instruction
 *  \details       --no details--
 *  \param[in]     x       Assembler instruction
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_ASM(str)

/*! \brief         Abstraction of the assembler align directive
 *  \details       --no details--
 *  \param[in]     val      Alignment
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_ALIGN(str)

/*! \brief         Defines an externally visible identifier.
 *  \details       --no details--
 *  \param[in]     name      Name of the identifier
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_LABEL(str)

/*! \brief         Starts a program code (.text) section
 *  \details       --no details--
 *  \param[in]     name      Name of the section
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_SECTION(str)

/*! \brief         Stores the value of a constant expressions as successive 32-bit data.
 *  \details       --no details--
 *  \param[in]     name
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_WORD(str)

/*! \brief         Abstraction of the assembler nop instruction
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_NOP()

/*! \brief         Disables acknowledgment of EI level interrupts
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_DisableGlobal()

/*! \brief         Enables acknowledgment of EI level interrupts
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_EnableGlobal()

/*! \brief         Abstraction of the assembler syncp instruction
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_SyncPipeline()

/*! \brief         Abstraction of the assembler synci instruction
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_SyncInstruction()

/*! \brief         Abstraction of the assembler syncm instruction
 *  \details       --no details--
 *  \context       OS_INTERNAL
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
# define Os_Hal_SyncMemory()


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

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
static inline uint32 Os_Hal_GetSP(void);

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
static inline void Os_Hal_SetLP(uint32 val);

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
static inline uint32 Os_Hal_GetLP(void);

/***********************************************************************************************************************
 *  Os_Hal_CallFunc()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_CallFunc(uint32* current, uint32* next)
 *  \brief        Enters a function defined by 'next' without performing a stack switch.
 *  \details      --no details--
 *
 *  \param[in]    current   The current context.
 *  \param[in]    next      The context to be continued.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
static inline void Os_Hal_CallFunc(const uint32 *current, const uint32* next);

/***********************************************************************************************************************
 *  Os_Hal_CallFuncOnStack()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_CallFuncOnStack(uint32* current, uint32* next)
 *  \brief        Enters a function defined by 'next' with stack switch.
 *  \details      --no details--
 *
 *  \param[in]    current   The current context.
 *  \param[in]    next      The context to be continued.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
static inline void Os_Hal_CallFuncOnStack(const uint32* current, const uint32* next);

/***********************************************************************************************************************
 *  Os_Hal_SetSPR()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetSPR(uint32 regID, uint32 groupID, uint32 value)
 *  \brief      Writes a value to the given register.
 *  \details    --no details--
 *
 *  \param[in]    regID     The register to write to.
 *  \param[in]    groupID   The register's group.
 *  \param[in]    value     The value to write to the register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
static inline void Os_Hal_SetSPR(uint32 regID, uint32 groupID, uint32 value);

/***********************************************************************************************************************
 *  Os_Hal_GetSPR()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_GetSPR(uint32 regID, uint32 groupID)
 *  \brief        Returns the given register
 *  \details      --no details--
 *
 *  \param[in]    regID     The register to read from.
 *  \param[in]    groupID   The register's group.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetSPR(uint32 regID, uint32 groupID);

/***********************************************************************************************************************
 *  Os_Hal_StartNextThread()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_StartNextThread(uint32* current, uint32* next)
 *  \brief        Starts the next thread.
 *  \details      --no details--
 *
 *  \param[in]    current   The current context.
 *  \param[in]    next      The context to be continued.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
static inline void Os_Hal_StartNextThread(const uint32* current, const uint32* next);

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
static inline uint32 Os_Hal_CountLeadingZeros(uint32 bitfield);

/***********************************************************************************************************************
 *  Os_Hal_GetDisableGlobal()
 **********************************************************************************************************************/
/*! \fn           Os_Hal_IntGlobalStateType Os_Hal_GetDisableGlobal(void)
 *  \brief        Disables EI interrupts and returns current ID-Flag from PSW.
 *  \details      --no details--
 *
 *  \return       The global interrupt flag.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetDisableGlobal(void);

/***********************************************************************************************************************
 *  Os_Hal_GetDisableLevel()
 **********************************************************************************************************************/
/*! \fn           Os_Hal_IntLevelType Os_Hal_GetDisableLevel(Os_Hal_IntLevelType Level)
 *  \brief        Sets the current interrupt level and returns the previous one.
 *  \details      --no details--
 *
 *  param[in]     The level to set.
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
static inline uint32 Os_Hal_GetDisableLevel(uint32 Level);

/***********************************************************************************************************************
 *  Os_Hal_SetLevelG3X()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetLevelG3X(Os_Hal_IntLevelType Level)
 *  \brief        Set the current interrupt level.
 *  \details      --no details--
 *
 *  \param[in]    The level to set.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
static inline void Os_Hal_SetLevelG3X(uint32 Level);

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
static inline uint32 Os_Hal_GetLevelG3X(void);

/***********************************************************************************************************************
 *  Os_Hal_TryGetLock()
 **********************************************************************************************************************/
/*! \fn           Os_Hal_SpinlockResultType Os_Hal_TryGetLock(volatile uint32* addr)
 *  \brief        Tries to get a spinlock
 *  \details      --no details--
 *
 *  \param[in]    addr    The spinlock to get.
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
static inline uint32 Os_Hal_TryGetLock(volatile uint32* addr);

/***********************************************************************************************************************
 *  Os_Hal_StartNext()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_StartNext(uint32* current, uint32* next)
 *  \brief        Starts the next thread.
 *  \details      --no details--
 *
 *  \param[in]    current   The current context.
 *  \param[in]    next      The context to be continued.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
static inline void Os_Hal_StartNext(const uint32 *Next);

/***********************************************************************************************************************
 *  Os_Hal_EndOfInterrupt()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_EndOfInterrupt(void)
 *  \brief        Signals the end of an interrput to the hardware.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
static inline void Os_Hal_EndOfInterrupt(void);


/***********************************************************************************************************************
 *  Os_Hal_CoreGetCpuMode()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_CoreGetCpuMode(void)
 *  \brief        Returns the current CPU mode.
 *  \details      --no details--
 *
 *  \return       The current CPU mode.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          -
 **********************************************************************************************************************/
static inline uint32 Os_Hal_CoreGetCpuMode(void);


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
static inline void Os_Hal_SetPSW(uint32 value);


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
static inline uint32 Os_Hal_GetPSW(void);


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
static inline void Os_Hal_SetINTCFG(uint32 value);


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
static inline void Os_Hal_SetEBASE(uint32 value);


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
static inline void Os_Hal_SetINTBP(uint32 value);


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
static inline void Os_Hal_SetASID(uint32 value);


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
static inline void Os_Hal_SetSCCFG(uint32 value);


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
static inline void Os_Hal_SetSCBP(uint32 value);


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
static inline uint32 Os_Hal_GetCoreID(void);


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
static inline void Os_Hal_SetEIWR(uint32 value);


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
static inline uint32 Os_Hal_GetEIWR(void);


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
static inline void Os_Hal_SetMPM(uint32 value);


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
static inline uint32 Os_Hal_GetPMR(void);


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
static inline uint32 Os_Hal_GetASID(void);


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
static inline void Os_Hal_SetPMR(uint32 value);


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
static inline uint32 Os_Hal_GetIntState(void);


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
static inline uint32 Os_Hal_GetMPLA0(void);


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
static inline uint32 Os_Hal_GetMPUA0(void);


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
static inline void Os_Hal_SetMPLA15(uint32 value);


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
static inline void Os_Hal_SetMPUA15(uint32 value);


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
static inline void Os_Hal_SetMPAT15(uint32 value);


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
static inline void Os_Hal_SetMPLA14(uint32 value);


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
static inline void Os_Hal_SetMPUA14(uint32 value);


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
static inline void Os_Hal_SetMPAT14(uint32 value);


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
static inline void Os_Hal_SetMPLA13(uint32 value);


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
static inline void Os_Hal_SetMPUA13(uint32 value);


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
static inline void Os_Hal_SetMPAT13(uint32 value);


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
static inline void Os_Hal_SetMPLA12(uint32 value);


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
static inline void Os_Hal_SetMPUA12(uint32 value);


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
static inline void Os_Hal_SetMPAT12(uint32 value);


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
static inline void Os_Hal_SetMPLA11(uint32 value);


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
static inline void Os_Hal_SetMPUA11(uint32 value);


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
static inline void Os_Hal_SetMPAT11(uint32 value);


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
static inline void Os_Hal_SetMPLA10(uint32 value);


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
static inline void Os_Hal_SetMPUA10(uint32 value);


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
static inline void Os_Hal_SetMPAT10(uint32 value);


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
static inline void Os_Hal_SetMPLA9(uint32 value);


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
static inline void Os_Hal_SetMPUA9(uint32 value);


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
static inline void Os_Hal_SetMPAT9(uint32 value);


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA8()
 **********************************************************************************************************************/
/*! \fn         void Os_Hal_SetMPLA8(uint32 value)
 *  \brief      Sets the protection area minimum address to the passed address.
 *  \details    --no details--
 *
 *  \param[in]    value     The value to write to the MPLA8 register.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA8(uint32 value);


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
static inline void Os_Hal_SetMPUA8(uint32 value);


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
static inline void Os_Hal_SetMPAT8(uint32 value);


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
static inline void Os_Hal_SetMPLA7(uint32 value);


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
static inline void Os_Hal_SetMPUA7(uint32 value);


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
static inline void Os_Hal_SetMPAT7(uint32 value);


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
static inline void Os_Hal_SetMPLA6(uint32 value);


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
static inline void Os_Hal_SetMPUA6(uint32 value);


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
static inline void Os_Hal_SetMPAT6(uint32 value);


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
static inline void Os_Hal_SetMPLA5(uint32 value);


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
static inline void Os_Hal_SetMPUA5(uint32 value);


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
static inline void Os_Hal_SetMPAT5(uint32 value);


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
static inline void Os_Hal_SetMPLA4(uint32 value);


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
static inline void Os_Hal_SetMPUA4(uint32 value);


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
static inline void Os_Hal_SetMPAT4(uint32 value);


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
static inline void Os_Hal_SetMPLA3(uint32 value);


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
static inline void Os_Hal_SetMPUA3(uint32 value);


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
static inline void Os_Hal_SetMPAT3(uint32 value);


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
static inline void Os_Hal_SetMPLA2(uint32 value);


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
static inline void Os_Hal_SetMPUA2(uint32 value);


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
static inline void Os_Hal_SetMPAT2(uint32 value);


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
static inline void Os_Hal_SetMPLA1(uint32 value);


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
static inline void Os_Hal_SetMPUA1(uint32 value);


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
static inline void Os_Hal_SetMPAT1(uint32 value);


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
static inline void Os_Hal_SetMPLA0(uint32 value);


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
static inline void Os_Hal_SetMPUA0(uint32 value);


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
static inline void Os_Hal_SetMPAT0(uint32 value);


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
static inline void Os_Hal_SetMPIDX0(void);


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
static inline void Os_Hal_SetMPIDX1(void);


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
static inline void Os_Hal_SetMPIDX2(void);


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
static inline void Os_Hal_SetMPIDX3(void);


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
static inline void Os_Hal_SetMPIDX4(void);


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
static inline void Os_Hal_SetMPIDX5(void);


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
static inline void Os_Hal_SetMPIDX6(void);


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
static inline void Os_Hal_SetMPIDX7(void);


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
static inline void Os_Hal_SetMPIDX8(void);


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
static inline void Os_Hal_SetMPIDX9(void);


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX10()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX10(void)
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
static inline void Os_Hal_SetMPIDX10(void);


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX11()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX11(void)
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
static inline void Os_Hal_SetMPIDX11(void);


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
static inline void Os_Hal_SetMPIDX12(void);


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX13()
 **********************************************************************************************************************/
/*! \fn           void Os_Hal_SetMPIDX13(void)
 *  \brief        Sets MPIDX register access MPU region 13 registers.
 *  \details      --no details--
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *
 *  \pre          Supervisor mode.
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX13(void);


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
static inline void Os_Hal_SetMPIDX14(void);


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
static inline void Os_Hal_SetMPIDX15(void);


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
static inline void Os_Hal_SetMPIDX16(void);


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
static inline void Os_Hal_SetMPIDX17(void);


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
static inline void Os_Hal_SetMPIDX18(void);


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
static inline void Os_Hal_SetMPIDX19(void);


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
static inline void Os_Hal_SetMPIDX20(void);


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX21()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_SetMPIDX21(void)
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
static inline void Os_Hal_SetMPIDX21(void);


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
static inline void Os_Hal_SetMPIDX22(void);


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX23()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_SetMPIDX23(void)
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
static inline void Os_Hal_SetMPIDX23(void);


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
static inline void Os_Hal_SetMPIDX24(void);


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
static inline void Os_Hal_SetMPIDX25(void);


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
static inline void Os_Hal_SetMPIDX26(void);


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
static inline void Os_Hal_SetMPIDX27(void);


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX28()
 **********************************************************************************************************************/
/*! \fn           uint32 Os_Hal_SetMPIDX28(void)
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
static inline void Os_Hal_SetMPIDX28(void);


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
static inline void Os_Hal_SetMPIDX29(void);


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
static inline void Os_Hal_SetMPIDX30(void);


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
static inline void Os_Hal_SetMPIDX31(void);


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
static inline void Os_Hal_SetLevelG4X(uint32 Level);


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
static inline uint32 Os_Hal_GetLevelG4X(void);


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
static inline void Os_Hal_SetSPID(uint32 value);


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
static inline void Os_Hal_Init_MPIDn(void);


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
static inline void Os_Hal_SetMPLA(uint32 value);


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
static inline void Os_Hal_SetMPUA(uint32 value);


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
static inline void Os_Hal_SetMPAT(uint32 value);


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
static inline uint32 Os_Hal_GetMPLA(void);


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
static inline uint32 Os_Hal_GetMPUA(void);


/***********************************************************************************************************************
 *  Os_Hal_SetPSW()
 **********************************************************************************************************************/
static inline void Os_Hal_SetPSW(uint32 value)                                                                          /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_GetPSW()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetPSW(void)                                                                                /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_SetINTCFG()
 **********************************************************************************************************************/
static inline void Os_Hal_SetINTCFG(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetEBASE()
 **********************************************************************************************************************/
static inline void Os_Hal_SetEBASE(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetINTBP()
 **********************************************************************************************************************/
static inline void Os_Hal_SetINTBP(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetINTBP()
 **********************************************************************************************************************/
static inline void Os_Hal_SetASID(uint32 value)                                                                         /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetSCCFG()
 **********************************************************************************************************************/
static inline void Os_Hal_SetSCCFG(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetSCBP()
 **********************************************************************************************************************/
static inline void Os_Hal_SetSCBP(uint32 value)                                                                         /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_GetCoreID()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetCoreID(void)                                                                             /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_SetEIWR()
 **********************************************************************************************************************/
static inline void Os_Hal_SetEIWR(uint32 value)                                                                         /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_GetEIWR()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetEIWR(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}

/***********************************************************************************************************************
 *  Os_Hal_SetMPM()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPM(uint32 value)                                                                          /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_GetPMR()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetPMR(void)                                                                                /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_GetASID()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetASID(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_GetASID()
 **********************************************************************************************************************/
static inline void Os_Hal_SetPMR(uint32 value)                                                                          /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_GetIntState()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetIntState(void)                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_GetMPLA0()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetMPLA0(void)                                                                              /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_GetMPLA0()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetMPUA0(void)                                                                              /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA15()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA15(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA15()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA15(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT15()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT15(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA14()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA14(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA14()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA14(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT14()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT14(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA13()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA13(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA13()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA13(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT13()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT13(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA12()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA12(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA12()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA12(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT12()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT12(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA11()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA11(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA11()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA11(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT11()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT11(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA10()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA10(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA10()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA10(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT10()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT10(uint32 value)                                                                       /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA9()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA9(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA9()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA9(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT9()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT9(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA8()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA8(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA8()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA8(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT8()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT8(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA7()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA7(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA7()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA7(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT7()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT7(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA6()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA6(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA6()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA6(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT6()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT6(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA5()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA5(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA5()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA5(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT5()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT5(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA4()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA4(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA4()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA4(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT4()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT4(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA3()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA3(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA3()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA3(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT3()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT3(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA2()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA2(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA2()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA2(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT2()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT2(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA1()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA1(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA1()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA1(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT1()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT1(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA0()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA0(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA0()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA0(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT0()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT0(uint32 value)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_GetSP()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetSP(void)                                                                                 /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_SetLP()
 **********************************************************************************************************************/
static inline void Os_Hal_SetLP(uint32 val)                                                                             /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(val);                                                                                           /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_GetLP()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetLP(void)                                                                                 /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_EndOfInterrupt()
 **********************************************************************************************************************/
static inline void Os_Hal_EndOfInterrupt(void)                                                                          /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_CallFunc()
 **********************************************************************************************************************/
static inline void Os_Hal_CallFunc(const uint32 *current, const uint32 *next)                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(current);                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  OS_IGNORE_UNREF_PARAM(next);                                                                                          /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_CallFuncOnStack()
 **********************************************************************************************************************/
static inline void Os_Hal_CallFuncOnStack(const uint32 *current, const uint32 *next)                                    /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(current);                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  OS_IGNORE_UNREF_PARAM(next);                                                                                          /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetSPR()
 **********************************************************************************************************************/
static inline void Os_Hal_SetSPR(uint32 regID, uint32 groupID, uint32 value)                                            /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(regID);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  OS_IGNORE_UNREF_PARAM(groupID);                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_GetSPR()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetSPR(uint32 regID, uint32 groupID)                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(regID);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  OS_IGNORE_UNREF_PARAM(groupID);                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_StartNextThread()
 **********************************************************************************************************************/
static inline void Os_Hal_StartNextThread(const uint32* current, const uint32* next)                                    /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(current);                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  OS_IGNORE_UNREF_PARAM(next);                                                                                          /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_StartNext()
 **********************************************************************************************************************/
static inline void Os_Hal_StartNext(const uint32 *Next)                                                                 /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(Next);                                                                                          /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_CountLeadingZeros()
 **********************************************************************************************************************/
static inline  uint32 Os_Hal_CountLeadingZeros(uint32 bitfield)                                                         /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(bitfield);                                                                                      /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_GetDisableGlobal()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetDisableGlobal(void)                                                                      /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_GetDisableLevel()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetDisableLevel(uint32 Level)                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(Level);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_SetLevelG3X()
 **********************************************************************************************************************/
static inline void Os_Hal_SetLevelG3X(uint32 Level)                                                                     /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(Level);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_GetLevelG3X()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetLevelG3X(void)                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_TryGetLock()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_TryGetLock(volatile uint32 *addr)                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  (*addr) *= 2uL;                                                                                                       /* SBSW_OS_HAL_PWA_CALLER */
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_CoreGetCpuMode()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_CoreGetCpuMode(void)                                                                        /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX0()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX0(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX1()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX1(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX2()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX2(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX3()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX3(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX4()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX4(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX5()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX5(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX6()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX6(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX7()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX7(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX8()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX8(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX9()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX9(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX10()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX10(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX11()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX11(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX12()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX12(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX13()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX13(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX14()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX14(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX15()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX15(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX16()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX16(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX17()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX17(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX18()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX18(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX19()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX19(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX20()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX20(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX21()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX21(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX22()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX22(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX23()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX23(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX24()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX24(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX25()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX25(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX26()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX26(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX27()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX27(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX28()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX28(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX29()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX29(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX30()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX30(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPIDX31()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPIDX31(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetLevelG4X()
 **********************************************************************************************************************/
static inline void Os_Hal_SetLevelG4X(uint32 Level)                                                                     /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(Level);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_GetLevelG4X()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetLevelG4X(void)                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_SetSPID()
 **********************************************************************************************************************/
static inline void Os_Hal_SetSPID(uint32 value)                                                                         /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_Init_MPIDn()
 **********************************************************************************************************************/
static inline void Os_Hal_Init_MPIDn(void)                                                                              /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPLA()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPLA(uint32 value)                                                                         /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPUA()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPUA(uint32 value)                                                                         /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_SetMPAT()
 **********************************************************************************************************************/
static inline void Os_Hal_SetMPAT(uint32 value)                                                                         /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  OS_IGNORE_UNREF_PARAM(value);                                                                                         /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_GetMPLA()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetMPLA(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


/***********************************************************************************************************************
 *  Os_Hal_GetMPUA()
 **********************************************************************************************************************/
static inline uint32 Os_Hal_GetMPUA(void)                                                                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  return 0uL;
}


# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* OS_HAL_COMPILER_GCCINT_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_StaticCodeAnalysis.h
 **********************************************************************************************************************/

