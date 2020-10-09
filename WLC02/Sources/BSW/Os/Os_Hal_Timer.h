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
 * \addtogroup  Os_Hal_Timer
 * \{
 *
 * \file        Os_Hal_Timer.h
 * \brief       HAL interface to work with timer hardware.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_TIMER_H
# define OS_HAL_TIMER_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_TimerInt.h"

/* Os kernel module dependencies */
# include "Os_Common.h"

/* Os HAL dependencies */
# include "Os_Hal_Compiler.h"
# include "Os_Hal_Derivative.h"
# include "Os_Hal_Interrupt.h"
# include "Os_Hal_Timer_OSTM.h"
# include "Os_Hal_Timer_TAUJ.h"
# include "Os_Hal_Timer_STM.h"
# include "Os_Hal_Timer_Lcfg.h"


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/*! Defines whether the HAL supports a free running timer (STD_ON) or not (STD_OFF). */
# define OS_HAL_FREE_RUNNING_TIMER            STD_ON

/*! Defines whether the HAL supports a programmable interval timer (STD_ON) or not (STD_OFF). */
# define OS_HAL_PROGRAMMABLE_INTERVAL_TIMER   STD_ON

/*! Defines the OSTM timer type. */
# define OS_HAL_TIMER_OSTM  (10u)
/*! Defines the OSTM timer unit index. */
# define OS_HAL_TIMER_OSTM0 (0u)
# define OS_HAL_TIMER_OSTM1 (1u)
# define OS_HAL_TIMER_OSTM2 (2u)
# define OS_HAL_TIMER_OSTM5 (5u)

/*! Defines the TAUJ timer type. */
# define OS_HAL_TIMER_TAUJ  (20u)
/*! Defines the TAUJ timer unit index. */
# define OS_HAL_TIMER_TAUJ0 (0u)
# define OS_HAL_TIMER_TAUJ1 (1u)
# define OS_HAL_TIMER_TAUJ2 (2u)

/*! Defines the STM timer type. */
# define OS_HAL_TIMER_STM   (30u)
/*! Defines the STM timer unit index. */
# define OS_HAL_TIMER_STM0  (0u)
# define OS_HAL_TIMER_STM1  (1u)

/*! Defines the timer channel index 0. */
#define OS_HAL_TIMER_CH0    (0u)
/*! Defines the timer channel index 1. */
#define OS_HAL_TIMER_CH1    (1u)
/*! Defines the timer channel index 2. */
#define OS_HAL_TIMER_CH2    (2u)
/*! Defines the timer channel index 3. */
#define OS_HAL_TIMER_CH3    (3u)



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
 *  Os_Hal_TimerPitInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_TimerPitInit,
(
  P2CONST(Os_Hal_TimerPitConfigType, AUTOMATIC, OS_CONST) TimerConfig
))                                                                                                                      /* COV_OS_HALPLATFORMPITUNSUPPORTED_XX */
{
  /* #10 Disable the timer's interrupt resource. */
  Os_Hal_IntDisableSource(TimerConfig->IsrConfig);                                                                      /* SBSW_OS_HAL_FC_CALLER */

  /* #20 Call the PIT initialization function depending on the timer type. */
  switch(TimerConfig->TimerType)
  {
    case OS_HAL_TIMER_OSTM: Os_Hal_TimerPitInit_OSTM(TimerConfig);                                                      /* SBSW_OS_HAL_FC_CALLER */ /* COV_OS_HALTIMEROSTMUNSUPPORTED_XX */
                            break;
    case OS_HAL_TIMER_TAUJ: Os_Hal_TimerPitInit_TAUJ(TimerConfig);                                                      /* SBSW_OS_HAL_FC_CALLER */ /* COV_OS_HALTIMERTAUJUNSUPPORTED_XX */
                            break;
    default: break;                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */ /* COV_OS_INVSTATE */
  }

  /* #30 Reenable the given timer source. */
  Os_Hal_IntEnableSource(TimerConfig->IsrConfig);                                                                       /* SBSW_OS_HAL_FC_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_TimerPitAckAndReload()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219*/
Os_Hal_TimerPitAckAndReload,
(
  P2CONST(Os_Hal_TimerPitConfigType, AUTOMATIC, OS_CONST) TimerConfig
))                                                                                                                      /* COV_OS_HALPLATFORMPITUNSUPPORTED_XX */
{
  /* Nothing to be done. */
  OS_IGNORE_UNREF_PARAM(TimerConfig);                                                                                   /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_TimerPitIsPending()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint32, OS_CODE, OS_ALWAYS_INLINE,                                         /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_TimerPitIsPending,
(
  P2CONST(Os_Hal_TimerPitConfigType, AUTOMATIC, OS_CONST) TimerConfig
))                                                                                                                      /* COV_OS_HALPLATFORMPITUNSUPPORTED_XX */
{
  /* #10 Return whether the given interrupt is pending. */
  return Os_Hal_IntGetRequest(TimerConfig->IsrConfig);                                                                  /* SBSW_OS_HAL_FC_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_TimerFrtInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_TimerFrtInit,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
))
{
  Os_Hal_IntDisableSource(TimerConfig->IsrConfig);                                                                      /* SBSW_OS_HAL_FC_CALLER */
  switch(TimerConfig->TimerType)
  {
    case OS_HAL_TIMER_OSTM: Os_Hal_TimerFrtInit_OSTM(TimerConfig);                                                      /* SBSW_OS_HAL_FC_CALLER */ /* COV_OS_HALTIMEROSTMUNSUPPORTED_XX */
                            break;
    case OS_HAL_TIMER_STM:  Os_Hal_TimerFrtInit_STM(TimerConfig);                                                       /* SBSW_OS_HAL_FC_CALLER */ /* COV_OS_HALTIMERSTMUNSUPPORTED_XX */
                            break;
    default: break;                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */ /* COV_OS_INVSTATE */
  }
  Os_Hal_IntEnableSource(TimerConfig->IsrConfig);                                                                       /* SBSW_OS_HAL_FC_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_TimerFrtGetCounterValue()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(                                                                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
OS_LOCAL_INLINE Os_Hal_TimerFrtTickType, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_TimerFrtGetCounterValue,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
))
{
  /* #10 Call the getter function depending on the timer type. */
  Os_Hal_TimerFrtTickType returnVal;
  switch(TimerConfig->TimerType)
  {
    case OS_HAL_TIMER_OSTM: returnVal = Os_Hal_GetCounterValue_OSTM(TimerConfig);                                       /* SBSW_OS_HAL_FC_CALLER */ /* COV_OS_HALTIMEROSTMUNSUPPORTED_XX */
                            break;
    case OS_HAL_TIMER_STM:  returnVal = Os_Hal_GetCounterValue_STM(TimerConfig);                                        /* SBSW_OS_HAL_FC_CALLER */ /* COV_OS_HALTIMERSTMUNSUPPORTED_XX */
                            break;
    default: returnVal = 0u;                                                                                             /* COV_OS_INVSTATE */
             break;
  }
  return returnVal;
}


/***********************************************************************************************************************
 *  Os_Hal_TimerFrtSetCompareValue()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_TimerFrtSetCompareValue,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig,
  Os_Hal_TimerFrtTickType ExpirationTime
))
{
  /* #10 Call the set compare value function depending on the timer type. */
  switch(TimerConfig->TimerType)
  {
    case OS_HAL_TIMER_OSTM: Os_Hal_SetCompareValue_OSTM(TimerConfig, ExpirationTime);                                   /* SBSW_OS_HAL_FC_CALLER */ /* COV_OS_HALTIMEROSTMUNSUPPORTED_XX */
                            break;
    case OS_HAL_TIMER_STM:  Os_Hal_SetCompareValue_STM(TimerConfig, ExpirationTime);                                    /* SBSW_OS_HAL_FC_CALLER */ /* COV_OS_HALTIMERSTMUNSUPPORTED_XX */
                            break;
    default: break;                                                                                                     /* PRQA S 2016 */ /* MD_MSR_EmptyClause */ /* COV_OS_INVSTATE */
  }
}


/***********************************************************************************************************************
 *  Os_Hal_TimerFrtAcknowledge()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_TimerFrtAcknowledge,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
))
{
  /* #10 Acknowledge the timer interrupt for STMs. */
  if(Os_Hal_TimerStmEnabled() != 0u)                                                                                     /* COV_OS_HALTIMERSTMUNSUPPORTED_XF */
  {
    if (TimerConfig->TimerType == OS_HAL_TIMER_STM)
    {
      Os_Hal_TimerAcknowledge_STM(TimerConfig);                                                                         /* SBSW_OS_HAL_FC_CALLER */
    }
  }
}


/***********************************************************************************************************************
 *  Os_Hal_TimerFrtTriggerIrq()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_TimerFrtTriggerIrq,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
))
{
  Os_Hal_IntSetRequest(TimerConfig->IsrConfig);                                                                         /* SBSW_OS_HAL_FC_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_TimerStmEnabled()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_TimerStmEnabled, (void))
{
  return (Os_StdReturnType)(OS_HAL_CFG_TIMER_STM == STD_ON);                                                            /* PRQA S 4304 */ /* MD_Os_C90BooleanCompatibility */
}


# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_TIMER_H */


#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Timer.h
 **********************************************************************************************************************/

