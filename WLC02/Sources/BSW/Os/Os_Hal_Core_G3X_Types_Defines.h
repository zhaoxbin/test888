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
 * \file        Os_Hal_Core_G3X_Types_Defines.h
 * \brief
 *
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/
#ifndef OS_HAL_CORE_G3X_TYPES_DEFINES_H
# define OS_HAL_CORE_G3X_TYPES_DEFINES_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/*! Defines whether the HAL provides a count leading zeros command (STD_ON) or not (STD_OFF). */
# define OS_HAL_COUNT_LEADING_ZEROS_HARDWARE     STD_ON

/*! The required address width to subscript the bits of a Os_Hal_CoreBitFieldType.
 * The value can be selected from the following table:
 * typeof(Os_Hal_BitFieldType)      | OS_HAL_INDEXBITWIDTH
 * :------------------------------: | :----------------------------
 * uint8                            | 3
 * uint16                           | 4
 * uint32                           | 5
 * uint64                           | 6
 */
# define OS_HAL_INDEXBITWIDTH       (5)

/*! Defines the stack fill pattern, which is used to initialize an empty stack. */
# define OS_HAL_STACK_FILL_PATTERN  ((Os_Hal_StackType)0xAAAAAAAAuL)

/*! Defines the value which is returned by \ref Os_Hal_SpinTryLock, if locking succeeded. */
# define OS_HAL_SPINLOCKSUCCEEDED   ((Os_Hal_SpinlockResultType)1)

/*! Defines the value of lock variable, when it is unlocked. */
# define OS_HAL_SPIN_UNLOCKED       ((Os_Hal_SpinlockType)0)

/*! Mask to set the table mode flag in the EI level interrupt control register.*/
# define OS_HAL_INTC_TABLE_MODE     ((uint8)0x40)
/*! Mask to set the request flag in the EI level interrupt control register.*/
# define OS_HAL_INTC_REQUEST_FLAG   ((uint8)0x10)
/*! Mask to set the interrupt processing disabled bit in the EI level interrupt control register.*/
# define OS_HAL_INTC_INT_SET_MASK   ((uint8)0x80)
/*! Mask to clear the interrupt processing disabled bit in the EI level interrupt control register.*/
# define OS_HAL_INTC_INT_CLR_MASK   ((uint8)0x7F)
/*! Mask to set the request flag in the EI level interrupt control register.*/
# define OS_HAL_INTC_INT_SET_PEND   (OS_HAL_INTC_REQUEST_FLAG)
/*! Mask to clear the request flag in the EI level interrupt control register.*/
# define OS_HAL_INTC_INT_CLR_PEND   ((uint8)0xEF)

/*! PSW Mask for ID flag - Disable EI interrupt handling. */
# define OS_HAL_PSW_ID_MSK   (0x00000020uL)

/*! PSW Mask for NP flag - Disable FE interrupt handling. */
# define OS_HAL_PSW_NP_MSK   (0x00000080uL)

/*! Defines the value for register MPM which is used to disable the MPU. */
# define OS_HAL_MPU_DISABLE  ((uint32)0x00000000uL)

/*! Defines the memory start address. */
# define OS_HAL_MEM_STARTADDR   ((uint32)0x00000000uL)
/*! Defines the memory end address. */
# define OS_HAL_MEM_ENDADDR     ((uint32)0xFFFFFFFFuL)

/*! Defines the value to be set to INTCFG register. */
# define OS_HAL_INTCFG_MODE     0

/*! Macro to access the high byte of INTIPIRn EI level interrupt register */
# define OS_HAL_XSIG_INTCTRL(addr)   (*((P2VAR(volatile uint8, AUTOMATIC, OS_VAR_NOINIT))(addr)))                       /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro to access the inter-processor interrupt control register IPIR_CHn */
# define OS_HAL_XSIG_TRIGGER(addr)   (*((P2VAR(volatile uint32, AUTOMATIC, OS_VAR_NOINIT))(addr)))                      /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro to clear pending inter-processor interrupts (only needed for G4X cores.) */
# define OS_HAL_XSIG_CLEARPENDING(addr)

/*! Defines the address to be accessed to trigger an inter-processor interrupt. */
# define OS_HAL_XSIG_TRIGGERADDR          XSigConfig->IPIRCHnAddr

/*! Macro to initialize XSignal component. */
# define OS_HAL_XSIG_INIT()          OS_HAL_XSIG_INTCTRL(XSigConfig->ICIPIRnAddr) &= OS_HAL_INTC_INT_CLR_MASK;          /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro to acknowledge an inter-processor interrupt. */
# define OS_HAL_XSIG_ACKNOWLEDGE()   OS_IGNORE_UNREF_PARAM(XSigConfig);                                                 /* PRQA S 3112 */ /* MD_MSR_DummyStmt */

/*!
 * \brief Interrupt lock level for tasks.
 * \details The PMR register must be set to zero to enable all interrupts.
 *
 */
# define OS_HAL_INTERRUPT_LOCK_LEVEL_TASK     (0uL)

/*!
 * \briefs Global interrupt state to enable all interrupts.
 * \details The PSW ID flag must be cleared to enable all interrupts.
 */
# define OS_HAL_INTERRUPT_GLOBAL_ENABLE_STATE (0uL)

/*!
 * \briefs Global interrupt state to disable all interrupts.
 * \details The PSW ID flag must be set to disable all interrupts.
 */
# define OS_HAL_INTERRUPT_GLOBAL_DISABLE_STATE (OS_HAL_PSW_ID_MSK)

/*!
 *  \briefs Interrupt priority masking register set macro.
 */
# define OS_HAL_PMR     11, 2

/*!
 *  \briefs Interrupt priority masking register get macro.
 */
# define OS_HAL_PMR_GET(REG)    11, REG, 2                                                                              /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*!
 *  \briefs Register to set address space ID.
 */
# define OS_HAL_ADDRESS_ID_REG     7, 2

/*!
 *  \briefs Macro to set address space ID register.
 */
# define OS_HAL_ASM_GET_ADDRESS_ID_REG(REG)     7, REG, 2                                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*!
 *  \briefs Dummy statement, only needed for G4X cores.
 */
# define OS_HAL_ASM_SETMPIDX0()

/*!
 *  \briefs Abstraction of core specific access to MPU registers.
 */
# define OS_HAL_SETMPLA_0(x)       Os_Hal_SetMPLA0(x)                                                                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*!
 *  \briefs Abstraction of core specific access to MPU registers.
 */
# define OS_HAL_SETMPUA_0(x)       Os_Hal_SetMPUA0(x)                                                                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*!
 *  \briefs Abstraction of core specific access to MPU registers.
 */
# define OS_HAL_SETMPAT_0(x)       Os_Hal_SetMPAT0(x)                                                                   /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */



/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/


#endif /* OS_HAL_CORE_G3X_TYPES_DEFINES_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Core_G3X_Types_Defines.h
 **********************************************************************************************************************/

