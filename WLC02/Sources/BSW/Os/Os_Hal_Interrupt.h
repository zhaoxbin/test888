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
 *  \addtogroup Os_Hal_Interrupt
 *  \{
 *
 *  \file       Os_Hal_Interrupt.h
 *  \brief
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_INTERRUPT_H
# define OS_HAL_INTERRUPT_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_InterruptInt.h"
# include "Os_Hal_Interrupt_Lcfg.h"

/* Os kernel module declarations */
# include "Os_Interrupt.h"
# include "Os_Cfg.h"
# include "Os_TimingProtection_Cfg.h"
# include "Os_Common.h"
# include "Os_TimingProtection.h"

/* Os HAL dependencies */
# include "Os_Hal_Interrupt_Cfg.h"
# include "Os_Hal_Compiler.h"
# include "Os_Hal_Core.h"
# include "Os_Hal_Derivative.h"

/* Select type of interrupt controller */
# if (OS_HAL_INTC_G3X == STD_ON)
#  include "Os_Hal_Interrupt_G3X.h"
# elif (OS_HAL_INTC_G4X == STD_ON)                                                                                      /* COV_OS_DERIVATIVEBETAMODULE */
#  include "Os_Hal_Interrupt_G4X.h"
# endif

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/*! Priority mask to disable all timing protection, CAT1 and CAT2 interrupts. */
# define OS_HAL_DISABLE_TP_LEVEL      OS_HAL_LEVEL_MASK(OS_CFG_HAL_TP_DISABLE_LEVEL)
/*! Priority mask to disable all CAT1 and CAT2 interrupts. */
# define OS_HAL_DISABLE_CAT1_LEVEL    OS_HAL_LEVEL_MASK(OS_CFG_HAL_ISR1_DISABLE_LEVEL)
/*! Priority mask to disable all CAT2 interrupts. */
# define OS_HAL_DISABLE_CAT2_LEVEL    OS_HAL_LEVEL_MASK(OS_CFG_HAL_ISR2_DISABLE_LEVEL)

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
 *  Os_Hal_IntEnableGlobal()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntEnableGlobal, (void))
{
  /* #10 Enable global core interrupts */
  Os_Hal_EnableGlobal();
}


/***********************************************************************************************************************
 *  Os_Hal_IntDisableGlobal()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntDisableGlobal, (void))
{
  /* #10 Disable global core interrupts */
  Os_Hal_DisableGlobal();
}


/***********************************************************************************************************************
 *  Os_Hal_IntDisableAndReturnGlobalState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_Hal_IntGlobalStateType, OS_CODE, OS_ALWAYS_INLINE,                      /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntDisableAndReturnGlobalState, (void))
{
  Os_Hal_IntGlobalStateType retState;

  /* #10 Get the masked global flag from PSW */
  retState = Os_Hal_GetIntState();

  /* #20 Disable global core interrupts */
  Os_Hal_DisableGlobal();

  return retState;
}


/***********************************************************************************************************************
 *  Os_Hal_IntSetGlobalState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntSetGlobalState,
(
  P2CONST(Os_Hal_IntGlobalStateType, AUTOMATIC, OS_APPL_DATA) State
))
{
  Os_Hal_IntGlobalStateType psw;

  /* #10 get the current PSW */
  psw = (Os_Hal_IntGlobalStateType)Os_Hal_GetPSW();
  /* #20 clear the global flag */
  psw &= (Os_Hal_IntGlobalStateType)~OS_HAL_PSW_ID_MSK;
  /* #30 write the new wanted global flag */
  Os_Hal_SetPSW((uint32)(psw | (*State)));
}


/***********************************************************************************************************************
 *  Os_Hal_IntGetGlobalEnable()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntGetGlobalEnable,
(
  P2VAR(Os_Hal_IntGlobalStateType, AUTOMATIC, OS_APPL_DATA) State
))
{
  /* #10 Return global flag state to enable all interrupts. */
  *State = (Os_Hal_IntGlobalStateType)OS_HAL_INTERRUPT_GLOBAL_ENABLE_STATE;                                             /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_IntGetCat2LockLevel()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntGetCat2LockLevel,
(
  P2VAR(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  /* #10 Return the interrupt lock level to disable all cat2 interrupts. */
  *Level = (Os_Hal_IntLevelType)OS_HAL_DISABLE_CAT2_LEVEL;                                                              /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_IntGetCat1LockLevel()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntGetCat1LockLevel,
(
  P2VAR(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  /* #10 Return the interrupt lock level to disable all cat2 and cat1 interrupts. */
  *Level = (Os_Hal_IntLevelType)OS_HAL_DISABLE_CAT1_LEVEL;                                                              /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_IntGetTPLockLevel()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntGetTPLockLevel,
(
  P2VAR(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  /* #10 Return the interrupt lock level to disable TP, cat1 and cat2 interrupts. */
  *Level = (Os_Hal_IntLevelType)OS_HAL_DISABLE_TP_LEVEL;                                                                /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_IntGetTaskLevel()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntGetTaskLevel,
(
  P2VAR(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  /* #10 Return the interrupt lock level for tasks. */
  *Level = (Os_Hal_IntLevelType)OS_HAL_INTERRUPT_LOCK_LEVEL_TASK;                                                       /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_IntIsClearPendingSupported()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntIsClearPendingSupported,( void ))
{
  return !0u;                                                                                                           /* PRQA S 4404, 4558 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule10.1_4558 */
}


/***********************************************************************************************************************
 *  Os_Hal_IntEndOfInterrupt()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntEndOfInterrupt,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  OS_IGNORE_UNREF_PARAM(IsrConfig);                                                                                     /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Inform hardware about end of interrupt. */
  Os_Hal_EndOfInterrupt();
}


/***********************************************************************************************************************
 *  Os_Hal_IntTrapRestore()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE,                                                             /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_ALWAYS_INLINE, Os_Hal_IntTrapRestore,
(
  P2CONST(Os_Hal_IntTrapStateType, AUTOMATIC, OS_VAR_NOINIT) InterruptState
))
{
  Os_Hal_IntSetGlobalState(InterruptState);                                                                             /* SBSW_OS_HAL_FC_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_IntTrapUpdate()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE,                                                             /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_ALWAYS_INLINE, Os_Hal_IntTrapUpdate,
(
  P2VAR(Os_Hal_IntTrapStateType, AUTOMATIC, OS_VAR_NOINIT) InterruptState
))
{
  *InterruptState = Os_Hal_GetIntState();                                                                               /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_IntIsGlobal2LevelSwitchSupported()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntIsGlobal2LevelSwitchSupported, (void))
{
  return !0u;                                                                                                           /* PRQA S 4404, 4558 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule10.1_4558 */
}


/***********************************************************************************************************************
 *  Os_Hal_IntIsPeripheralInterruptTriggerSupported()
 **********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntIsPeripheralInterruptTriggerSupported, (void))
{
  /* #10 Return !0 because the peripheral interrupts can be triggered. */
  return !0u;                                                                                                           /* PRQA S 4404, 4558 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule10.1_4558 */
}


/***********************************************************************************************************************
 *  Os_Hal_IntIsLevelSupported()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntIsLevelSupported, (void))
{
  return !0u;                                                                                                           /* PRQA S 4404, 4558 */ /* MD_Os_C90BooleanCompatibility, MD_Os_Rule10.1_4558 */
}


# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_INTERRUPT_H */


#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Interrupt.h
 **********************************************************************************************************************/
