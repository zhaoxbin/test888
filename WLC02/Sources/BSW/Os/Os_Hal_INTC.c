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
 *  \addtogroup  Os_Hal_INTC
 *  \{
 *
 *  \file        Os_Hal_INTC.c
 *  \brief       Interrupt controller INTC related data
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

                                                                                                                        /* PRQA S 0777 EOF */ /* MD_MSR_Rule5.1 */

#define OS_HAL_INTC_SOURCE

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Core.h"

/* Os kernel module dependencies */
#include "Os_Hal_Os.h"

/* Os HAL dependencies */


/***********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h"                                                                                       /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! \brief Interrupt mapping for STMn timer interrupt selection register
 *  \details The table contains for each STMn timer channel 0,1,2,3 the interrupt mapping for the timer interrupt
             selection register STMnIS. The corresponding value is ORed into register STMnIS.
             STM0 channel 0A, 0B, 0C and 0D are not used by the OS and cannot be configured.
             STM1 channel 0A, 0B, 0C and 0D are not used by the OS and cannot be configured.
             STM0 channel 1A is mapped to INTSTM04. STM0 channel 1B, 1C and 1D are not used.
             STM0 channel 2B is mapped to INTSTM05. STM0 channel 2A, 2C and 2D are not used.
             STM0 channel 3A is mapped to INTSTM06. STM0 channel 3B, 3C and 3D are not used.
             STM1 channel 1A is mapped to INTSTM14. STM1 channel 1B, 1C and 1D are not used.
             STM1 channel 2B is mapped to INTSTM15. STM1 channel 2A, 2C and 2D are not used.             
             STM1 channel 3A is mapped to INTSTM16. STM1 channel 3B, 3C and 3D are not used.             
 */
CONST(uint32, OS_CONST) osINTSTMnConfig[4] = 
{
  0x00000000uL, /* STMn CH0 is not used by OS  */
  0x00000000uL, /* STMn CH1 mapped to INTSTMn4 */
  0x00000400uL, /* STMn CH2 mapped to INTSTMn5 */
  0x00001000uL  /* STMn CH3 mapped to INTSTMn6 */
};

/*! \brief Interrupt FEINT level masking for STMn timer channel 1
 *  \details The table contains for each STMn timer the base address of the corresponding FEINFMSKn register
             in the interrupt controller INTC. Only STMn interrupt channel 1 has FEINT level interrupt.
             The FEINT level interrupt is disabled by the OS if STM0_CH1 or STM1_CH1 is configured.
             FEINTFMSK0 is set to disable FEINT level interrupt of STM0_CH1.
             FEINTFMSK1 is set to disable FEINT level interrupt of STM1_CH1.             
 */
CONST(uint32, OS_CONST) osFEINTFMSKnBase[2] = 
{
  0xFFD42004uL, /* FEINTFMSK0 base address: used to disable FEINT level interrupt of STM0_CH1 */
  0xFFD43004uL  /* FEINTFMSK1 base address: used to disable FEINT level interrupt of STM1_CH1 */
};

/*! \brief Interrupt FEINT level masking for STMn timer channel 1
 *  \details The table contains for each STMn timer the mask value of the corresponding FEINFMSKn register
             in the interrupt controller INTC. Only STMn interrupt channel 1 has FEINT level interrupt.
             The FEINT level interrupt is disabled by the OS if STM0_CH1 or STM1_CH1 is configured.
             FEINTFMSK0 is set to disable FEINT level interrupt of STM0_CH1.
             FEINTFMSK1 is set to disable FEINT level interrupt of STM1_CH1.             
             The corresponding value is ORed into register FEINTFMSKn.
 */
CONST(uint32, OS_CONST) osFEINTFMSK[4] = 
{
  0x00000000uL, /* STMn CH0: no change  */
  0x00000001uL, /* STMn CH1: set bit FEINTEMSK0 to disable FEINT level interrupt of STM CH1 */
  0x00000000uL, /* STMn CH2: no change  */
  0x00000000uL  /* STMn CH3: no change  */
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h"                                                                                       /* PRQA S 5087 */ /* MD_MSR_MemMap */


/***********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_INTC.c
 **********************************************************************************************************************/
