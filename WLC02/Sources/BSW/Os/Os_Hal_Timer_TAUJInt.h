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
 *  \addtogroup Os_Hal_Timer_TAUJ HAL Timer TAUJ
 *
 *  \{
 *
 *  \file       Os_Hal_Timer_TAUJInt.h
 *  \brief      Internal functions and data types related to timer TAUJ.
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

#ifndef OS_HAL_TIMER_TAUJINT_H
# define OS_HAL_TIMER_TAUJINT_H
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

struct Os_Hal_TAUJType_Tag
{
  uint32 osTAUJnCDR[4];   /*!< +00h TAUJn control register. ( 32 bit read/write ) */

  uint32 osTAUJnCNT[4];   /*!< +10h TAUJn channel counter register. ( 32 bit read ) */

  uint8 osTAUJnCMUR[16];  /*!< +20h TAUJn channel mode user register. (8 bit read/write) */

  uint32 osTAUJnCSR[4];   /*!< +30h TAUJn channel status register. (8 bit read ) */

  uint32 osTAUJnCSC[4];   /*!< +40h TAUJn channel status clear trigger register ( 8 bit write ) */

  uint8  osTAUJnTE;       /*!< +50h TAUJn channel enable status register. ( 8 bit read ) */
  uint8  osTAUJnTE0;      /*!< +51h No hardware register mapped */
  uint16 osTAUJnTE1;      /*!< +52h No hardware register mapped */
  uint8  osTAUJnTS;       /*!< +54h TAUJn channel start trigger register. ( 8 bit write )*/
  uint8  osTAUJnTS0;      /*!< +55h No hardware register mapped */
  uint16 osTAUJnTS1;      /*!< +56h No hardware register mapped */

  uint8  osTAUJnTT;       /*!< +58h TAUJn channel stop register. ( 8 bit write ) */
  uint8  osTAUJnTT0;      /*!< +59h No hardware register mapped */
  uint16 osTAUJnTT1;      /*!< +5Ah No hardware register mapped */

  uint8  osTAUJnTO;       /*!< +5Ch TAUJn channel output register. (8 bit read/write ) */
  uint8  osTAUJnTO0;      /*!< +5Dh No hardware register mapped */
  uint16 osTAUJnTO1;      /*!< +5Eh No hardware register mapped */

  uint8  osTAUJnTOE;      /*!< +60h TAUJn channel output enable register. (8 bit read/write) */
  uint8  osTAUJnTOE0;     /*!< +61h No hardware register mapped */
  uint16 osTAUJnTOE1;     /*!< +62h No hardware register mapped */

  uint8  osTAUJnTOL;      /*!< +64h TAUJn Channel Output register. ( bit read/write) */
  uint8  osTAUJnTOL0;     /*!< +65h No hardware register mapped */
  uint16 osTAUJnTOL1;     /*!< +66h No hardware register mapped */

  uint8  osTAUJnRDT;      /*!< +68h TAUJn channel reload data trigger register. (8 bit write) */
  uint8  osTAUJnRDT0;     /*!< +69h No hardware register mapped */
  uint16 osTAUJnRDT1;     /*!< +6Ah No hardware register mapped */

  uint8  osTAUJnRSF;      /*!< +6Ch TAUJn channel reload status register. (8 bit read) */
  uint8  osTAUJnRSF0;     /*!< +6Dh No hardware register mapped */
  uint16 osTAUJnRSF1;     /*!< +6Eh No hardware register mapped */

  uint32 osTAUJnRSF2[4];  /*!< +70h No hardware register mapped */

  uint16 osTAUJnCMOR[8];  /*!< +80 Channel Mode OS register. (16 bit read/write) */

  uint16 osTAUJnTPS;      /*!< +90h Prescaler clock select register. (16 bit read/write) */
  uint16 osTAUJnTPS0;     /*!< +92h No hardware register mapped */

  uint8  osTAUJnBRS;      /*!< +94h TAUJn Prescaler baud rate setting register (8 bit read/write) */
  uint8  osTAUJnBRS0;     /*!< +95h No hardware register mapped */
  uint16 osTAUJnBRS1;     /*!< +96h No hardware register mapped */

  uint8  osTAUJnTOM;      /*!< +98h TAUJn Channel output mode register. (8 bit read/write) */
  uint8  osTAUJnTOM0;     /*!< +99h No hardware register mapped */
  uint16 osTAUJnTOM1;     /*!< +9Ah No hardware register mapped */

  uint8  osTAUJnTOC;      /*!< +9Ch TAUJn channel output configuration register. (8 bit read/write) */
  uint8  osTAUJnTOC0;     /*!< +99h No hardware register mapped */
  uint16 osTAUJnTOC1;     /*!< +9Ah No hardware register mapped */

  uint8  osTAUJnRDE;      /*!< +A0h TAUJn channel reload data enable register. (8 bit read/write) */
  uint8  osTAUJnRDE0;     /*!< +A1h No hardware register mapped */
  uint16 osTAUJnRDE1;     /*!< +A2h No hardware register mapped */

  uint8  osTAUJnRDM;      /*!< +A4h TAUJn channel reload data mode register. (8 bit read/write) */
  uint8  osTAUJnRDM0;     /*!< +A5h No hardware register mapped */
  uint16 osTAUJnRDM1;     /*!< +A6h No hardware register mapped */
};


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

#if 0
/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Os_Hal_TimerPitInit_TAUJ()
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
Os_Hal_TimerPitInit_TAUJ,
(
  P2CONST(Os_Hal_TimerPitConfigType, AUTOMATIC, OS_CONST) TimerConfig
));


/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_TIMER_TAUJINT_H */

#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Timer_TAUJInt.h
 **********************************************************************************************************************/

