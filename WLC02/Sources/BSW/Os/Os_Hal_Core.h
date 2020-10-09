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
 * \addtogroup  Os_Hal_Core
 * \{
 *
 * \file        Os_Hal_Core.h
 * \brief       Core and multi-core related primitives.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_CORE_H
# define OS_HAL_CORE_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_CoreInt.h"
# include "Os_Hal_Core_Lcfg.h"

/* Os kernel module declarations */
# include "Os_Common.h"
# include "Os_Core.h"
# include "Os_Thread.h"
# include "Os_Lcfg.h"

/* Os HAL dependencies */
# include "Os_Hal_Compiler.h"
# include "Os_Hal_Derivative.h"
# include "Os_Hal_Interrupt.h"

#if (OS_HAL_CORE_G3X == STD_ON)
# include "Os_Hal_Core_G3X.h"
#elif (OS_HAL_CORE_G4X == STD_ON)                                                                                       /* COV_OS_DERIVATIVEBETAMODULE */
# include "Os_Hal_Core_G4X.h"
#endif

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
 *  Os_Hal_CoreGetId()
 **********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_CorePhysicalIdType, OS_CODE, OS_ALWAYS_INLINE,                          /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_CoreGetId,
(
  void
))
{
  /* #10 Return the physical CoreId. */
  return (Os_CorePhysicalIdType)Os_Hal_GetCoreID();
}


/***********************************************************************************************************************
 *  Os_Hal_CoreIsThreadPointerUserReadable()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_CoreIsThreadPointerUserReadable,
(
  void
))
{
  /* #10 Thread pointer cannot be read in user mode -> return 0. */
  return 0u;
}


/***********************************************************************************************************************
 *  Os_Hal_CoreIsCoreIdUserReadable()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_CoreIsCoreIdUserReadable,
(
  void
))                                                                                                                      /* COV_OS_HALCOREISCOREIDUSERREADABLE */
{
  return 0u;
}


/***********************************************************************************************************************
 *  Os_Hal_CoreSetThread()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_CoreSetThread,
(
  P2CONST(Os_Hal_Core2ThreadConfigType, AUTOMATIC, OS_CONST) Core2Thread,
  P2CONST(Os_ThreadConfigType, AUTOMATIC, OS_CONST) Thread
))
{
  /* #10 Store Thread in core register. */
  Os_Hal_SetEIWR((uint32)Thread);                                                                                       /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  OS_IGNORE_UNREF_PARAM(Core2Thread);                                                                                   /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_CoreGetThread()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE P2CONST(Os_ThreadConfigType, AUTOMATIC, OS_CONST), OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_CoreGetThread,
(
  P2CONST(Os_Hal_Core2ThreadConfigType, AUTOMATIC, OS_CONST) Core2Thread
))
{
  OS_IGNORE_UNREF_PARAM(Core2Thread);                                                                                   /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Return Thread from core register. */
  return ((P2CONST(Os_ThreadConfigType, AUTOMATIC, OS_CONST))Os_Hal_GetEIWR());                                         /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
}


/***********************************************************************************************************************
 *  Os_Hal_CoreIsPrivilegedModeUserReadable()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_CoreIsPrivilegedModeUserReadable,
(
  void
))
{
  /* #10 Privileged mode is readable in user mode -> return 1. */
  return !0u;                                                                                                           /* PRQA S 4404, 4558 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule10.1_4558 */
}


/***********************************************************************************************************************
 *  Os_Hal_CoreGetPrivilegedMode()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_CoreGetPrivilegedMode,
(
  void
))
{
  /* #10 Return 0 if current mode is user, !0 otherwise. */
  return ((Os_StdReturnType)(Os_Hal_CoreGetCpuMode() == 0u));                                                           /* PRQA S 4304 */ /* MD_Os_C90BooleanCompatibility */
}


/***********************************************************************************************************************
 *  Os_Hal_StackEndGet()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219, 3673 */ /* MD_Os_Rule2.1_3219, MD_Os_Hal_Rule8.13_3673_NotUsed */
OS_LOCAL_INLINE P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT), OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_StackEndGet,
(
  P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT) LowAddress,
  P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT) HighAddress
))
{
  OS_IGNORE_UNREF_PARAM(HighAddress);                                                                                   /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  /* #10 Return LowAddress. */
  return (P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT))LowAddress;
}


/***********************************************************************************************************************
 *  Os_Hal_StackBottomGet()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219, 3673 */ /* MD_Os_Rule2.1_3219, MD_Os_Hal_Rule8.13_3673_NotUsed */
OS_LOCAL_INLINE P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT), OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_StackBottomGet,
(
  P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT) LowAddress,
  P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT) HighAddress
))
{
  OS_IGNORE_UNREF_PARAM(LowAddress);                                                                                    /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  /* #10 Return HighAddress. */
  return (P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT))HighAddress;
}


/***********************************************************************************************************************
 *  Os_Hal_StackTopGet()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT), OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_StackTopGet,
(
  void
))
{
  /* #10 Return stack pointer. */
  return (P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT))Os_Hal_GetSP();                                             /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
}


/***********************************************************************************************************************
 *  Os_Hal_StackPointerMoveDown()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT), OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_StackPointerMoveDown,
(
  P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT) StackPointer
))
{
  /* #10 Return (StackPointer + 1). */
  return (P2VAR(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT))(StackPointer + 1);
}


/***********************************************************************************************************************
 *  Os_Hal_StackCalculateUsage()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE,                                         /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_StackCalculateUsage,
(
  P2CONST(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT) StackBottom,
  P2CONST(Os_Hal_StackType, AUTOMATIC, OS_VAR_NOINIT) StackTop
))
{
  /* #10 Return (StackBottom - StackTop). */
  return (uint32)(StackBottom - StackTop);                                                                              /* PRQA S 0488 */ /* MD_Os_Hal_Rule18.4_0488 */
}


/***********************************************************************************************************************
 *  Os_Hal_CoreStart()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_CoreStart,
(
  P2CONST(Os_Hal_CoreConfigType, AUTOMATIC, OS_CONST) Core
))                                                                                                                      /* COV_OS_HALPLATFORMNONAUTOSTARTCORE */
{
  OS_IGNORE_UNREF_PARAM(Core);                                                                                          /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_CoreSynchronize()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */ /* COV_OS_UNSUPPORTED88830 */
Os_Hal_CoreSynchronize, (void))                                                                                         /* COV_OS_UNSUPPORTED88830 */
{
  /* #10 Instruction and memory barrier. */
  Os_Hal_SyncPipeline();
  Os_Hal_SyncInstruction();
  Os_Hal_SyncMemory();
}


/***********************************************************************************************************************
 *  Os_Hal_SpinInit()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_SpinInit,
(
  P2VAR(volatile Os_Hal_SpinlockType, AUTOMATIC, OS_VAR_NOINIT) Spinlock
))
{
  /* #10 Set Spinlock to unlocked. */
  *Spinlock = OS_HAL_SPIN_UNLOCKED;                                                                                     /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_SpinIsLocked()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_SpinIsLocked,
(
  P2CONST(volatile Os_Hal_SpinlockType, AUTOMATIC, OS_VAR_NOINIT) Spinlock
))
{
  /* #10 Return 0 if Spinlock is unlocked, !0 otherwise. */
  return (Os_StdReturnType)(*Spinlock != OS_HAL_SPIN_UNLOCKED);                                                         /* PRQA S 4304 */ /* MD_Os_C90BooleanCompatibility */
}


/***********************************************************************************************************************
 *  Os_Hal_SpinTryLock()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_Hal_SpinlockResultType, OS_CODE, OS_ALWAYS_INLINE,                      /* PRQA S 3219, 3673 */ /* MD_Os_Rule2.1_3219, MD_Os_Hal_Rule8.13_3673_ModifiedArgument */
Os_Hal_SpinTryLock,
(
  P2VAR(volatile Os_Hal_SpinlockType, AUTOMATIC, OS_VAR_NOINIT) Spinlock
))
{
  /* #10 Try to get the Spinlock. */
  return (Os_Hal_TryGetLock((volatile uint32*)Spinlock));                                                               /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */ /* SBSW_OS_HAL_FC_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_SpinUnlock()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_SpinUnlock,
(
  P2VAR(volatile Os_Hal_SpinlockType, AUTOMATIC, OS_VAR_NOINIT) Spinlock
))
{
  /* #10 Set Spinlock to unlocked. */
  *Spinlock = OS_HAL_SPIN_UNLOCKED;                                                                                     /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_CoreIdle()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_CoreIdle, (void))                  /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  /* #10 Do nothing. */
}


/***********************************************************************************************************************
 *  Os_Hal_CoreNop()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE, Os_Hal_CoreNop, (void))                   /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
{
  /* #10 Perform NOP. */
  Os_Hal_NOP();
}


/***********************************************************************************************************************
 *  Os_Hal_CoreGetMaxAllowedStack()
 **********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_CoreGetMaxAllowedStack,
(
  P2VAR(Os_Hal_ContextStackConfigType, AUTOMATIC, OS_VAR_NOINIT) Stack
))
{
  /* #10 Get the memory settings for maximum stack window. */
  Stack->Os_Hal_StackStart = OS_HAL_MEM_STARTADDR;                                                                      /* SBSW_OS_HAL_PWA_CALLER */
  Stack->Os_Hal_StackEnd   = OS_HAL_MEM_ENDADDR;                                                                        /* SBSW_OS_HAL_PWA_CALLER */
}


# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_CORE_H */


#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Core.h
 **********************************************************************************************************************/

