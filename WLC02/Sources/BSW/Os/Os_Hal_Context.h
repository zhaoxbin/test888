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
 *  \addtogroup Os_Hal_Context
 *  \trace      CREQ-1201
 *
 *  \{
 *
 *  \file       Os_Hal_Context.h
 *  \brief      Context switching primitives.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_CONTEXT_H
# define OS_HAL_CONTEXT_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_ContextInt.h"
# include "Os_Hal_Context_Lcfg.h"

/* Os kernel module dependencies */

/* Os HAL dependencies */
# include "Os_Hal_Compiler.h"
# include "Os_Hal_Core.h"
# include "Os_Hal_Interrupt.h"
# include "Os_Hal_Os.h"


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
#if 0
# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Os_Hal_ContextInit()
 **********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextInit,
(
  P2CONST(Os_Hal_ContextConfigType, AUTOMATIC, OS_CONST) Config,
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Context
))
{
  /* #10 Initialize common fields of the given context from its configuration. */
  Context->Os_Hal_PC  = Config->Entry;  /* Program counter = Entry point of thread */                                   /* SBSW_OS_HAL_PWA_CALLER */
  Context->Os_Hal_PSW = Config->Os_Hal_PSW; /* Program status word = Initial machine status of thread */                /* SBSW_OS_HAL_PWA_CALLER */
  Context->Os_Hal_PMR = Config->Os_Hal_PMR; /* Priority Mask Register */                                                /* SBSW_OS_HAL_PWA_CALLER */
  Context->Os_Hal_LP  = Config->ReturnAddress;  /* Link pointer = Return address of the thread */                       /* SBSW_OS_HAL_PWA_CALLER */
  Context->Os_Hal_SP  = Config->Os_Hal_SP;  /* Stack top address for stack pointer */                                   /* SBSW_OS_HAL_PWA_CALLER */
  /* #20 If MemoryProtection is enabled, also initialize MemoryProtection specific fields. */
  if (Os_MpIsEnabled() != 0u)
  {
    Context->Os_Hal_ASID  = Config->Os_Hal_ASID; /* set ASID for MPU regions */                                         /* SBSW_OS_HAL_PWA_CALLER */
    Context->Os_Hal_MPLA0 = Config->Os_Hal_SL;   /* Stack bottom address for MPU */                                     /* SBSW_OS_HAL_PWA_CALLER */
    Context->Os_Hal_MPUA0 = Config->Os_Hal_SP;   /* Stack top address for MPU */                                        /* SBSW_OS_HAL_PWA_CALLER */
  }
}


/***********************************************************************************************************************
 *  Os_Hal_ContextReset()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextReset,
(
  P2CONST(Os_Hal_ContextConfigType, AUTOMATIC, OS_CONST) Config,
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Context
))
{
  /* #10 Same as \ref Os_Hal_ContextInit(). */
  Os_Hal_ContextInit(Config, Context);                                                                                  /* SBSW_OS_HAL_FC_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextSetParameter()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextSetParameter,
(
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Context,
  P2CONST(void, AUTOMATIC, OS_VAR_NOINIT) Parameter
))
{
  /* #10 Set the first parameter register of the given context. */
  Context->Os_Hal_PARAM = (uint32)Parameter;                                                                            /* PRQA S 0326 */ /* MD_Os_Hal_Rule11.6_0326 */ /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextSetStack()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextSetStack,
(
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Context,
  P2CONST(Os_Hal_ContextStackConfigType, AUTOMATIC, OS_VAR_NOINIT) Stack
))
{
  /* #10 Set the stack registers of the given context. */
  Context->Os_Hal_SP    = Stack->Os_Hal_StackEnd;                                                                       /* SBSW_OS_HAL_PWA_CALLER */
  Context->Os_Hal_MPLA0 = Stack->Os_Hal_StackStart;                                                                     /* SBSW_OS_HAL_PWA_CALLER */
  Context->Os_Hal_MPUA0 = Stack->Os_Hal_StackEnd;                                                                       /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextGetStack()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextGetStack,
(
  P2CONST(Os_Hal_ContextConfigType, AUTOMATIC, OS_CONST) Context,
  P2VAR(Os_Hal_ContextStackConfigType, AUTOMATIC, OS_VAR_NOINIT) Stack
))
{
  /* #10 Get the stack config from given context config. */
  Stack->Os_Hal_StackStart = Context->Os_Hal_SL;                                                                        /* SBSW_OS_HAL_PWA_CALLER */
  Stack->Os_Hal_StackEnd   = Context->Os_Hal_SP;                                                                        /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextSetInterruptState()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextSetInterruptState,
(
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Context,
  P2CONST(Os_Hal_IntStateType, AUTOMATIC, OS_VAR_NOINIT) InterruptState
))
{
  /* #10 Set the interrupt state flags in PSW register of the given context. */
  Context->Os_Hal_PSW = (Context->Os_Hal_PSW & (uint32)~(OS_HAL_PSW_ID_MSK)) | InterruptState->PSW;                     /* SBSW_OS_HAL_PWA_CALLER */
  Context->Os_Hal_PMR = InterruptState->PMR;                                                                            /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextSetUserMsrBits()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextSetUserMsrBits,
(
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Context
))
{
  /* #10 Update PSW according to user settings. */
  Context->Os_Hal_PSW = ((Context->Os_Hal_PSW & (~OS_HAL_CORE_MSR_USER_BIT_MSK)) |                                      /* SBSW_OS_HAL_PWA_CALLER */
                         (Os_Hal_GetPSW() & OS_HAL_CORE_MSR_USER_BIT_MSK));
}


/***********************************************************************************************************************
 *  Os_Hal_ContextStartNext()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextStartNext,
(
  P2CONST(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Next
))
{
  /* #10 If MemoryProtection is enabled, set MemoryProtection specific registers from the given context. */
  if (Os_MpIsEnabled() != 0u)
  {
    Os_Hal_SetMPIDX0();
    Os_Hal_Set_MemRegionID(Next->Os_Hal_ASID);
    OS_HAL_SETMPLA_0(Next->Os_Hal_MPLA0);
    OS_HAL_SETMPUA_0(Next->Os_Hal_MPUA0);
    OS_HAL_SETMPAT_0(OS_HAL_MPU_MPAT0);
    Os_Hal_SyncPipeline();
  }
  /* #20 Set common context registers. */
  Os_Hal_SetLP(Next->Os_Hal_LP);
  Os_Hal_SetPMR(Next->Os_Hal_PMR);
  Os_Hal_StartNext((const uint32*)Next);                                                                                /* PRQA S 0310 */ /* MD_Os_Hal_Rule11.3_0310 */ /* SBSW_OS_HAL_FC_CALLER */
}                                                                                                                       /* PRQA S 6050 */ /* MD_Os_Hal_STCAL */


/***********************************************************************************************************************
 *  Os_Hal_ContextFirstResume()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextFirstResume,
(
  P2CONST(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Next
))
{
  /* #10 Disable EI and FE interrupts, then resume next context. */
  Os_Hal_DisableGlobal();
  Os_Hal_DisableFE();
  Os_Hal_ContextStartNext(Next);                                                                                        /* SBSW_OS_HAL_FC_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_ContextResetAndResume()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextResetAndResume,
(
  P2CONST(Os_Hal_ContextConfigType, AUTOMATIC, OS_CONST) CurrentConfig,
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Current,
  P2CONST(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Next
))
{

  /* #10 Reset current context data structure. */
  Os_Hal_ContextInit(CurrentConfig, Current);                                                                           /* SBSW_OS_HAL_FC_CALLER */

  /* #20 Disable EI and FE interrupts. */
  Os_Hal_DisableGlobal();
  Os_Hal_DisableFE();

  /* #30 Start or resume next thread. */
  Os_Hal_ContextStartNext(Next);                                                                                        /* SBSW_OS_HAL_FC_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextAbort()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextAbort,
(
  P2CONST(Os_Hal_ContextConfigType, AUTOMATIC, OS_CONST) Config,
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Context
))
{
  /* #10 Set program counter of the given context to the return function, and reset stack pointer. */
  Context->Os_Hal_PC = Config->ReturnAddress;                                                                           /* SBSW_OS_HAL_PWA_CALLER */
  Context->Os_Hal_SP = Config->Os_Hal_SP;                                                                               /* SBSW_OS_HAL_PWA_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_ContextReturn()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextReturn,
(
  P2CONST(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Current,
  P2CONST(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Next
))
{
  /* #10 Disable EI and FE interrupts, then start or resume next thread. */
  Os_Hal_DisableGlobal();
  Os_Hal_DisableFE();
  Os_Hal_ContextStartNext(Next);                                                                                        /* SBSW_OS_HAL_FC_CALLER */
  OS_IGNORE_UNREF_PARAM(Current);                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextIsExceptionContextSupported()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextIsExceptionContextSupported,
(
  void
))
{
  return 0u;
}


/***********************************************************************************************************************
 *  Os_Hal_ContextFetchInitialFpuContext()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219, 3673 */ /* MD_Os_Rule2.1_3219, MD_Os_Hal_Rule8.13_3673_NotUsed */
Os_Hal_ContextFetchInitialFpuContext,
(
  P2VAR(Os_Hal_ContextFpuContextType, AUTOMATIC, OS_VAR_NOINIT) InitialContext
))
{
  /* #10 Stub implementation: fpu registers are already saved in the context switch mechanism. */
  OS_IGNORE_UNREF_PARAM(InitialContext);                                                                                /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextInitFpu()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextInitFpu,
(
  P2CONST(Os_Hal_ContextFpuContextType, AUTOMATIC, OS_VAR_NOINIT) InitialContext
))
{
  /* Stub implementation: fpu registers are already saved in the context switch mechanism. */
  OS_IGNORE_UNREF_PARAM(InitialContext);                                                                                /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextInitFpuContext()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219, 3673 */ /* MD_Os_Rule2.1_3219, MD_Os_Hal_Rule8.13_3673_NotUsed */
Os_Hal_ContextInitFpuContext,
(
  P2VAR(Os_Hal_ContextFpuContextType, AUTOMATIC, OS_VAR_NOINIT) Context,
  P2CONST(Os_Hal_ContextFpuContextType, AUTOMATIC, OS_VAR_NOINIT) InitialContext
))
{
  /* #10 Stub implementation: fpu registers are already saved in the context switch mechanism. */
  OS_IGNORE_UNREF_PARAM(Context);                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  OS_IGNORE_UNREF_PARAM(InitialContext);                                                                                /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextStoreFpuContext()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219, 3673 */ /* MD_Os_Rule2.1_3219, MD_Os_Hal_Rule8.13_3673_NotUsed */
Os_Hal_ContextStoreFpuContext,
(
  P2VAR(Os_Hal_ContextFpuContextType, AUTOMATIC, OS_VAR_NOINIT) Context
))
{
  /* #10 Stub implementation: fpu context is saved during the context switch mechanism. */
  OS_IGNORE_UNREF_PARAM(Context);                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_ContextRestoreFpuContext()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_ContextRestoreFpuContext,
(
  P2CONST(Os_Hal_ContextFpuContextType, AUTOMATIC, OS_VAR_NOINIT) Context
))
{
  /* #10 Stub implementation: fpu context is restored during the context switch mechanism. */
  OS_IGNORE_UNREF_PARAM(Context);                                                                                       /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_CONTEXT_H */


#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Context.h
 **********************************************************************************************************************/

