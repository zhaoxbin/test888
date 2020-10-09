/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
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
 *  \file       Os_Hal_Interrupt_G3X.h
 *  \brief
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_INTERRUPT_G3X_H
# define OS_HAL_INTERRUPT_G3X_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/*! Calculates the priority mask for the passed level. */
# define OS_HAL_LEVEL_MASK(Level)     ((uint32)(((uint32)OS_HAL_PMR_MASK) >> (Level)) << (Level))                       /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* Compares two interrupt levels depending on core architecture. */
/* Compares two interrupt levels depending on core architecture. */
/*! \brief    Compares two interrupt levels depending on core architecture.
 *  \details  Comparing interrupt priority levels works differently for G3X
 *            and G4X cores.
 *            On G3X PMR register is used to mask certain interrupt priority
 *            levels. PMR registers contains 16 bits, each representing one
 *            of the 16 possible interrupt priority levels to be masked. Bit 0
 *            represents priority 0 (highest) to be masked, bit 15 represents
 *            priority 15 to be masked.
 */
# define OS_HAL_INT_LEVEL_GT(x,y)     ((*x)>(*y))                                                                       /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

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
 *  Os_Hal_IntGetLevel()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntGetLevel,
(
  P2VAR(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  *Level = Os_Hal_GetLevelG3X();                                                                                           /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_IntSetLevel()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntSetLevel,
(
  P2CONST(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  Os_Hal_SetLevelG3X(*Level);
}


/***********************************************************************************************************************
 *  Os_Hal_IntGetInterruptState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntGetInterruptState,
(
  P2VAR(Os_Hal_IntStateType, AUTOMATIC, OS_VAR_NOINIT) InterruptState
))
{
  /* #10 Fetch level and global interrupt state. */
  InterruptState->PSW = Os_Hal_GetIntState();                                                                           /* SBSW_OS_HAL_PWA_CALLER */
  InterruptState->PMR = Os_Hal_GetLevelG3X();                                                                              /* SBSW_OS_HAL_PWA_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_InitIBD()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_InitIBD,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_CONST) IsrConfig
))
{
  /* #10 Check whether the hardware has a bind register or not */
  if(OS_HAL_EIBD2_BASE != 0u)                                                                                           /* PRQA S 2741 */ /* MD_Os_Hal_Rule14.3_2741 */
  {
    /* #20 Initialize the binding register. */
    IsrConfig->IBDnRef->IBDnReg = (uint32)(IsrConfig->CoreID << 16u) | (IsrConfig->CoreID + 1u);                        /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */
  }
}


/***********************************************************************************************************************
 *  Os_Hal_IntDisableSource()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntDisableSource,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  /* #10 Disable the given source. */
  IsrConfig->EICnRef->EICnLo |= OS_HAL_INTC_INT_SET_MASK;                                                               /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */

  /* #20 Ensure that the state is changed in hardware. */
  Os_Hal_SyncMemory();
}


/***********************************************************************************************************************
 *  Os_Hal_IntEnableSource()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntEnableSource,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  /* #10 Enable the given source. */
  IsrConfig->EICnRef->EICnLo &= OS_HAL_INTC_INT_CLR_MASK;                                                               /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */

  /* #20 Ensure that the state is changed in hardware. */
  Os_Hal_SyncMemory();
}


/***********************************************************************************************************************
 *  Os_Hal_IntClearPending()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntClearPending,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  /* #10 Clear the pending flag of the given interrupt. */
  IsrConfig->EICnRef->EICnHi &= OS_HAL_INTC_INT_CLR_PEND;                                                               /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */

  /* #20 Ensure that the state is changed in hardware. */
  Os_Hal_SyncMemory();
}


/***********************************************************************************************************************
 *  Os_Hal_IntIsInterruptSourceEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntIsInterruptSourceEnabled,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  return ((IsrConfig->EICnRef->EICnLo & OS_HAL_INTC_INT_SET_MASK) == 0x0u);                                             /* PRQA S 4404 */ /* MD_Os_C90BooleanCompatibility */
}


/***********************************************************************************************************************
 *  Os_Hal_IntIsInterruptPending()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntIsInterruptPending,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  return ((IsrConfig->EICnRef->EICnHi & OS_HAL_INTC_INT_SET_PEND) != 0x0u);                                             /* PRQA S 4404 */ /* MD_Os_C90BooleanCompatibility */
}


/***********************************************************************************************************************
 *  Os_Hal_IntIsrLevelIsLe()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType,                                                          /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_CODE, OS_ALWAYS_INLINE, Os_Hal_IntIsrLevelIsLe,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig,
  P2CONST(Os_Hal_IntLevelType, AUTOMATIC, OS_CONST) Level
))
{
  return (Os_StdReturnType)(IsrConfig->IntMask <= (*Level));                                                            /* PRQA S 4304 */ /* MD_Os_C90BooleanCompatibility */
}


/***********************************************************************************************************************
 *  Os_Hal_IntLevelIsGt()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE,                                                 /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_ALWAYS_INLINE, Os_Hal_IntLevelIsGt,
(
  P2CONST(Os_Hal_IntLevelType, AUTOMATIC, OS_CONST) LevelX,
  P2CONST(Os_Hal_IntLevelType, AUTOMATIC, OS_CONST) LevelY
))
{
  return (Os_StdReturnType)OS_HAL_INT_LEVEL_GT(LevelX,LevelY);                                                          /* PRQA S 4304 */ /* MD_Os_C90BooleanCompatibility */
}


/***********************************************************************************************************************
 *  Os_Hal_IntInterruptSourceInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE,                                                             /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_ALWAYS_INLINE, Os_Hal_IntInterruptSourceInit,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) InterruptSource
))
{
  /* #10 Bind the interrupt to its core */
  Os_Hal_InitEIC(InterruptSource);                                                                                      /* SBSW_OS_HAL_FC_CALLER */

  /* #20 Initialize interrupt control register */
  Os_Hal_InitIBD(InterruptSource);                                                                                      /* SBSW_OS_HAL_FC_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_InitEIC()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_InitEIC,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_CONST) IsrConfig
))
{
  /* #10 Initialize the error interrupt control register. */
  IsrConfig->EICnRef->EICnLo = (uint8)(IsrConfig->EICnRef->EICnLo & 0x80u)                                              /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */
                                    | OS_HAL_INTC_TABLE_MODE
                                    | ((uint8)IsrConfig->IntLevel);
}


/***********************************************************************************************************************
 *  Os_Hal_IntSetRequest()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntSetRequest,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_CONST) IsrConfig
))
{
  /* #10 Request the given interrupt. */
  Os_Hal_IntDisableSource(IsrConfig);                                                                                   /* SBSW_OS_HAL_FC_CALLER */
  IsrConfig->EICnRef->EICnHi |= OS_HAL_INTC_REQUEST_FLAG;                                                               /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */
  Os_Hal_IntEnableSource(IsrConfig);                                                                                    /* SBSW_OS_HAL_FC_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntGetRequest()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint8, OS_CODE, OS_ALWAYS_INLINE,                                          /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_IntGetRequest,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_CONST) IsrConfig
))                                                                                                                      /* COV_OS_HALPLATFORMPITUNSUPPORTED_XX */
{
  /* #10 The the request state from the hardware. */
  return (IsrConfig->EICnRef->EICnHi & OS_HAL_INTC_REQUEST_FLAG);
}


# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_INTERRUPT_G3X_H */


#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Interrupt_G3X.h
 **********************************************************************************************************************/
