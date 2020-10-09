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
 *  \addtogroup Os_Hal_Timer_STM HAL Timer STM
 *
 *  \{
 *
 *  \file       Os_Hal_Timer_STMInt.h
 *  \brief      Internal functions and data types related to timer STM.
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

#ifndef OS_HAL_TIMER_STMINT_H
# define OS_HAL_TIMER_STMINT_H
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

/*! Memory mapped STM registers corresponding to the memory layout */
typedef struct Os_Hal_STMCNTType_Tag
{
  uint32 osSTMCNTx;         /*!< +00h Timer counter register.              (32/8 bit write ) */
  uint32 osSTMCNTUnused0;   /*!< +04h No mapped hardware register. */
  uint32 osSTMCNTUnused1;   /*!< +08h No mapped hardware register. */
  uint32 osSTMCNTUnused2;   /*!< +0Ch No mapped hardware register. */
  uint32 osSTMCMPxA;        /*!< +10h Timer compare register.              (32/8 bit write ) */
  uint32 osSTMCMPxB;        /*!< +14h Timer compare register.              (32/8 bit write ) */
  uint32 osSTMCMPxC;        /*!< +18h Timer compare register.              (32/8 bit write ) */
  uint32 osSTMCMPxD;        /*!< +1Ch Timer compare register.              (32/8 bit write ) */
}Os_Hal_STMCNTType;

struct Os_Hal_STMType_Tag
{
  uint32 osSTMnCKSEL;       /*!< +00h Timer counter source clock selection register. ( 32/8 bit read/write ) */
  uint32 osSTMnUnused0;     /*!< +04h No mapped hardware register. */
  uint32 osSTMnUnused1;     /*!< +08h No mapped hardware register. */
  uint32 osSTMnUnused2;     /*!< +0Ch No mapped hardware register. */
  uint32 osSTMnTS;          /*!< +10h 32 bit Timer counter start register. (32/8 bit write ) */
  uint32 osSTMnTT;          /*!< +14h 32 bit Timer counter stop register.  (32/8 bit write ) */
  uint32 osSTMnCSTR;        /*!< +18h Timer counter status register.       (32/8 bit write ) */
  uint32 osSTMnUnused3;     /*!< +1Ch No mapped hardware register. */
  uint32 osSTMnSTR;         /*!< +20h Timer status register.               (32/8 bit write ) */
  uint32 osSTMnSTC;         /*!< +24h Timer status clear.                  (32/8 bit write ) */
  uint32 osSTMnUnused4;     /*!< +28h No mapped hardware register. */
  uint32 osSTMnUnused5;     /*!< +2Ch No mapped hardware register. */
  uint32 osSTMnIS;          /*!< +30h Timer interrupt selection register.  (32/8 bit write ) */
  uint32 osSTMnRM;          /*!< +34h Timer SW reset mask register.        (32/8 bit write ) */
  uint32 osSTMnUnused6;     /*!< +38h No mapped hardware register. */
  uint32 osSTMnUnused7;     /*!< +3Ch No mapped hardware register. */
  uint32 osSTMnCNT0L;       /*!< +40h Timer counter register low.          (32/8 bit write ) */
  uint32 osSTMnCNT0H;       /*!< +44h Timer counter register high.         (32/8 bit write ) */
  uint32 osSTMnUnused8;     /*!< +48h No mapped hardware register. */
  uint32 osSTMnUnused9;     /*!< +4Ch No mapped hardware register. */
  uint32 osSTMnCMP0AL;      /*!< +50h Timer compare register low.          (32/8 bit write ) */
  uint32 osSTMnCMP0AH;      /*!< +54h Timer compare register high.         (32/8 bit write ) */
  uint32 osSTMnCMP0BL;      /*!< +58h Timer compare register low.          (32/8 bit write ) */
  uint32 osSTMnCMP0BH;      /*!< +5Ch Timer compare register high.         (32/8 bit write ) */
  uint32 osSTMnCMP0CL;      /*!< +60h Timer compare register low.          (32/8 bit write ) */
  uint32 osSTMnCMP0CH;      /*!< +64h Timer compare register high.         (32/8 bit write ) */
  uint32 osSTMnCMP0DL;      /*!< +68h Timer compare register low.          (32/8 bit write ) */
  uint32 osSTMnCMP0DH;      /*!< +6Ch Timer compare register high.         (32/8 bit write ) */
  Os_Hal_STMCNTType osSTMnCNT[3]; /*!< +70h ... +8Ch Timer counter and timer compare registers. (32/8 bit write ) */
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
 *  Os_Hal_TimerFrtInit_STM()
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
Os_Hal_TimerFrtInit_STM,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
));


/***********************************************************************************************************************
 *  Os_Hal_GetCounterValue_STM()
 **********************************************************************************************************************/
/*! \brief          Return the current counter register value of the given STM timer.
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
Os_Hal_GetCounterValue_STM,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
));


/***********************************************************************************************************************
 *  Os_Hal_SetCompareValue_STM()
 **********************************************************************************************************************/
/*! \brief          Set the compare value of the given STM.
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
Os_Hal_SetCompareValue_STM,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig,
  Os_Hal_TimerFrtTickType ExpirationTime
));


/***********************************************************************************************************************
 *  Os_Hal_TimerAcknowledge_STM()
 **********************************************************************************************************************/
/*! \brief          Tell the timer hardware, that we are handling the interrupt request.
 *  \details        --no details--
 *
 *  \param[in]      TimerConfig     Timer hardware configuration. Parameter must not be NULL.
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *
 *  \pre            -
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_TimerAcknowledge_STM,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
));


/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_TIMER_STMINT_H */

#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Timer_STMInt.h
 **********************************************************************************************************************/

