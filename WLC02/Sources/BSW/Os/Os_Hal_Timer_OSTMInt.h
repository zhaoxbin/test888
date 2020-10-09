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
 *  \ingroup    Os_Hal
 *  \addtogroup Os_Hal_Timer_OSTM HAL Timer OSTM
 *
 *  \{
 *
 *  \file       Os_Hal_Timer_OSTMInt.h
 *  \brief      Internal functions and data types related to timer OSTM.
 *
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
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_TIMER_OSTMINT_H
# define OS_HAL_TIMER_OSTMINT_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */

/* Os HAL dependencies */
# include "Os_Hal_InterruptInt.h"


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*! Memory mapped OSTM registers corresponding to the memory layout */
struct Os_Hal_OSTMType_Tag
{
  uint32 osOSTMnCMP;      /*!< +00h Compare register. (32 bit read/write) */

  uint32 osOSTMnCNT;      /*!< +04h Counter register. (32 bit read) */

  uint8  osOSTMnTO;       /*!< +08h OSTM output register. (8 bit read/write) */
  uint8  osOSTMnTO1;      /* unused */
  uint16 osOSTMnTO2;      /* unused */

  uint8  osOSTMnTOE;      /*!< +0Ch OSTM output enable register. (8 bit read/write) */
  uint8  osOSTMnTOE1;     /* unused */
  uint16 osOSTMnTOE2;     /* unused */

  uint8  osOSTMnTE;       /*!< +10h Counter enable status register. (8 bit read) */
  uint8  osOSTMnTE1;      /* unused */
  uint16 osOSTMnTE2;      /* unused */

  uint8  osOSTMnTS;       /*!< +14h Count start trigger register. (8 bit read/write) */
  uint8  osOSTMnTS1;      /* unused */
  uint16 osOSTMnTS2;      /* unused */

  uint8  osOSTMnTT;       /*!< +18h Count stop trigger register. (8 bit read/write) */
  uint8  osOSTMnTT1;      /* unused */
  uint16 osOSTMnTT2;      /* unused */

  uint32 osOSTMnUnused;   /*!< +1Ch No hardware register mapped. */

  uint8  osOSTMnCTL;      /*!< +20h Control register. (8 bit read/write) */
  uint8  osOSTMnCTL1;     /* unused */
  uint16 osOSTMnCTL2;     /* unused */

  uint8  osOSTMnEMU;      /*!< +24h Emulation register. (8 bit read/write) */
};


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
 *  Os_Hal_TimerPitInit_OSTM()
 **********************************************************************************************************************/
/*! \brief          Initialize a programmable interval timer hardware using the given configuration.
 *  \details        --no details--
 *
 *  \param[in]      TimerConfig   Timer hardware configuration. Parameter must not be NULL.
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *
 *  \pre            -
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_TimerPitInit_OSTM,
(
  P2CONST(Os_Hal_TimerPitConfigType, AUTOMATIC, OS_CONST) TimerConfig
));


/***********************************************************************************************************************
 *  Os_Hal_TimerFrtInit_OSTM()
 **********************************************************************************************************************/
/*! \brief          Initialize a free running timer using the given configuration.
 *  \details        --no details--
 *
 *  \param[in]      TimerConfig   Timer hardware configuration. Parameter must not be NULL.
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *
 *  \pre            -
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_TimerFrtInit_OSTM,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
));


/***********************************************************************************************************************
 *  Os_Hal_GetCounterValue_OSTM()
 **********************************************************************************************************************/
/*! \brief          Return the current counter register value of the given OSTM timer.
 *  \details        --no details--
 *
 *  \param[in]      TimerConfig     Timer hardware configuration. Parameter must not be NULL.
 *
 *  \return         Current counter register value.
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *
 *  \pre            -
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE Os_Hal_TimerFrtTickType, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_GetCounterValue_OSTM,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
));


/***********************************************************************************************************************
 *  Os_Hal_SetCompareValue_OSTM()
 **********************************************************************************************************************/
/*! \brief          Set the compare value of the given OSTM.
 *  \details        --no details--
 *
 *  \param[in,out]  TimerConfig     Timer hardware configuration. Parameter must not be NULL.
 *  \param[in]      ExpirationTime  The new compare value.
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *
 *  \pre            -
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_SetCompareValue_OSTM,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig,
  Os_Hal_TimerFrtTickType ExpirationTime
));


/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_TIMER_OSTMINT_H */

#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Timer_OSTMInt.h
 **********************************************************************************************************************/

