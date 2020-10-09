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
 * \file        Os_Hal_Core_Types.h
 * \brief       Core and multi-core related primitives.
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
#ifndef OS_HAL_CORE_TYPES_H
# define OS_HAL_CORE_TYPES_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */
# include "Os_Cfg.h"

/* Os HAL dependencies */
# include "Os_Hal_Interrupt_Types.h"
# include "Os_Hal_Context_Types.h"
# include "Os_Hal_Derivative.h"

/* Os HAL Core defines */
#if (OS_HAL_CORE_G3X == STD_ON)
# include "Os_Hal_Core_G3X_Types_Defines.h"
#elif (OS_HAL_CORE_G4X == STD_ON)                                                                                       /* COV_OS_DERIVATIVEBETAMODULE */
# include "Os_Hal_Core_G4X_Types_Defines.h"
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
/*! Platform specific core data. */
typedef uint32 Os_Hal_CoreType;

/*! Data type which is used to perform efficient calculation of count leading zero bits. */
typedef uint32 Os_Hal_BitFieldType;

/*! Platform type of an 8 bit hardware register */
typedef uint8 Os_Hal_Reg8BitType;

/*! Platform type of a 16 bit hardware register */
typedef uint16 Os_Hal_Reg16BitType;

/*! Platform type of a 32 bit hardware register */
typedef uint32 Os_Hal_Reg32BitType;

/*! Pointer to a 8 bit hardware register */
typedef P2VAR(volatile Os_Hal_Reg8BitType, TYPEDEF, AUTOMATIC) Os_Hal_Reg8BitRefType;

/*! Pointer to a 16 bit hardware register */
typedef P2VAR(volatile Os_Hal_Reg16BitType, TYPEDEF, AUTOMATIC) Os_Hal_Reg16BitRefType;

/*! Pointer to a 32 bit hardware register */
typedef P2VAR(volatile Os_Hal_Reg32BitType, TYPEDEF, AUTOMATIC) Os_Hal_Reg32BitRefType;


/*! Defines the type of the stack array. */
typedef uint32 Os_Hal_StackType;

/*! Platform type of a spinlock */
typedef uint32 Os_Hal_SpinlockType;

/*! Platform type of a spinlock result */
typedef Os_Hal_SpinlockType Os_Hal_SpinlockResultType;

/*! Forward declaration of platform core configuration type. */
struct Os_Hal_CoreConfigType_Tag;
typedef struct Os_Hal_CoreConfigType_Tag Os_Hal_CoreConfigType;

/*! Forward declaration of platform specific dynamic system information type. */
struct Os_Hal_Core2ThreadType_Tag;
typedef struct Os_Hal_Core2ThreadType_Tag Os_Hal_Core2ThreadType;

/*! Forward declaration of platform specific system information configuration type. */
struct Os_Hal_Core2ThreadConfigType_Tag;
typedef struct Os_Hal_Core2ThreadConfigType_Tag Os_Hal_Core2ThreadConfigType;

/*! Forward declaration of a platform specific AUTOSAR core configuration type.*/
struct Os_Hal_CoreAsrConfigType_Tag;
typedef struct Os_Hal_CoreAsrConfigType_Tag Os_Hal_CoreAsrConfigType;

/*! Forward declaration of a platform specific system information configuration type. */
struct Os_Hal_SystemConfigType_Tag;
typedef struct Os_Hal_SystemConfigType_Tag Os_Hal_SystemConfigType;

/*! Forward declaration of a platform specific XSignal interrupt configuration type. */
struct Os_Hal_XSigInterruptConfigType_Tag;
typedef struct Os_Hal_XSigInterruptConfigType_Tag Os_Hal_XSigInterruptConfigType;


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

#endif /* OS_HAL_CORE_TYPES_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Core_Types.h
 **********************************************************************************************************************/

