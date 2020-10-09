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
 * \file        Os_Hal_Core_G4X.h
 * \brief       Core and multi-core related primitives.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_CORE_G4X_H
# define OS_HAL_CORE_G4X_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */

/* Os module declarations */

/* Os kernel module declarations */

/* Os HAL dependencies */


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

# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Os_Hal_XSigInit()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_XSigInit,
(
  P2CONST(Os_Hal_XSigInterruptConfigType, AUTOMATIC, OS_CONST) XSigConfig
))
{
  OS_IGNORE_UNREF_PARAM(XSigConfig);                                                                                    /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

  /* #10 Enable XSignal interrupt. */
  OS_HAL_XSIG_ENABLEINTERUPT(OS_HAL_INTC1_BASE+(0x4u*Os_Hal_GetCoreID())) &= 0xFF7FFFFFu;                               /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */

  /* #20 Clear pending interrupt flag. */
  OS_HAL_XSIG_CLEARPENDING((OS_HAL_IPIR_BASE+0x08u)) = 0xFFu;                                                           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */

  /* #30 Enable all four channels. */
  OS_HAL_XSIG_ENABLECHANNEL(OS_HAL_IPIR_BASE) = 0x0Fu;                                                                  /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  OS_HAL_XSIG_ENABLECHANNEL(OS_HAL_IPIR_BASE+0x20u) = 0x0Fu;                                                            /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  OS_HAL_XSIG_ENABLECHANNEL(OS_HAL_IPIR_BASE+0x40u) = 0x0Fu;                                                            /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  OS_HAL_XSIG_ENABLECHANNEL(OS_HAL_IPIR_BASE+0x60u) = 0x0Fu;                                                            /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */

  Os_Hal_SyncMemory();
}


/***********************************************************************************************************************
 *  Os_Hal_XSigTrigger()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_XSigTrigger,
(
  P2CONST(Os_Hal_XSigInterruptConfigType, AUTOMATIC, OS_CONST) XSigConfig
))
{
  /* #10 Trigger XSignal interrupt. */
  OS_HAL_XSIG_TRIGGER(OS_HAL_IPIR_BASE+(0x10u+(0x20u*(XSigConfig->XSigCoreID-0x1u)))) = (0x01u<<((XSigConfig->XSigCoreID)-0x1u));/* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */

  Os_Hal_SyncMemory();
}


/***********************************************************************************************************************
 *  Os_Hal_XSigAcknowledge()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Rule2.1_3219 */
Os_Hal_XSigAcknowledge,
(
  P2CONST(Os_Hal_XSigInterruptConfigType, AUTOMATIC, OS_CONST) XSigConfig
))
{
  /* #10 Clear interrupt flag. */
  OS_IGNORE_UNREF_PARAM(XSigConfig);                                                                                    /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
  OS_HAL_XSIG_CLEARPENDING(OS_HAL_IPIR_BASE+0x08u+(0x20u*Os_Hal_GetCoreID())) = 0x0Fu;                                  /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
}


# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_CORE_G4X_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Core_G4X.h
 **********************************************************************************************************************/

