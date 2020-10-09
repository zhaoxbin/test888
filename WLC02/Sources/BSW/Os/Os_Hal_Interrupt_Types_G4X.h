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
 *  \addtogroup Os_Hal_Interrupt_Types
 *  \{
 *
 *  \file       Os_Hal_Interrupt_Types_G4X.h
 *  \brief
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

#ifndef OS_HAL_INTERRUPT_TYPES_G4X_H
# define OS_HAL_INTERRUPT_TYPES_G4X_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */

/* Os Hal dependencies */


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/
# define OS_HAL_EIC_OFFSET    4uL

# define OS_HAL_IBD_OFFSET    4uL


/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*! \brief    Interrupt state.
 *  \details  The kernel uses this data type to suspend/resume interrupts, also in case of timing protection and
 *            to protect OS internal critical sections.
 *            This type is typically some kind of bit mask (e.g. processor status word). */
typedef uint32 Os_Hal_IntGlobalStateType;

/*! \brief    Interrupt level.
 *  \details  The kernel uses this data type to suspend/resume category 2 ISRs up to a certain level.
 *            This data type is needed to implement interrupt resources. */
typedef uint32 Os_Hal_IntLevelType;

/*! \brief    Interrupt state (with trap information).
 *  \details  The kernel uses this data type to restore the caller's interrupt state on OS service requests.
 *            On TriCore this data type also contains a pointer to the user space CSA. */
typedef Os_Hal_IntGlobalStateType Os_Hal_IntTrapStateType;


struct Os_Hal_IntStateType_Tag;
typedef struct Os_Hal_IntStateType_Tag Os_Hal_IntStateType;


/*! \brief    Interrupt source.
 *  \details  The kernel uses this data type to disable an interrupt source.
 *            This data type is needed to implement killing of applications.
 *            It is typically an interrupt index or interrupt source address. */
typedef uint16 Os_Hal_IntSourceType;

struct Os_Hal_IntIsrConfigType_Tag;
typedef struct Os_Hal_IntIsrConfigType_Tag Os_Hal_IntIsrConfigType;

/*! \brief    Type to access EI level interrupt control registers.
 *  \details  Register contains information about interrupt priority,
 *            interrupt overflow, interrupt method (direct branching, table
 *            reference mode), interrupt mask, interrupt request flag and
 *            interrupt detection mode of one specific interrupt source.
 *            For G4X cores Extended EI level interrupt control registers are
 *            used. Only available in G4X derivatives. EEICn register are 32
 *            bits wide and provide additional interrupt priorities (up to 64)
 *            compared to 16 priority levels using EICn registers.
 */
typedef struct
{
  uint16 EICnLo;   /*!< +00h lower bytes */
  uint16 EICnHi;   /*!< +02h higher bytes */
} Os_Hal_EICnType;

/*! Pointer to an EI level interrupt control register. */
typedef P2VAR(volatile Os_Hal_EICnType, AUTOMATIC, OS_VAR_NOINIT) Os_Hal_EICnRefType;

/*! Type to access an EI level interrupt bind register.*/
typedef struct
{
  uint32 IBDnReg; /*!< +00h 32 bit hardware register.*/
} Os_Hal_IBDnType;

/*! Pointer to an EI level interrupt bind register.*/
typedef P2VAR(volatile Os_Hal_IBDnType, AUTOMATIC, OS_VAR_NOINIT) Os_Hal_IBDnRefType;


/*! Pointer to a platform specific configuration type of an ISR. */
typedef P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_CONST) Os_Hal_IntIsrConfigRefType;

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#endif /* OS_HAL_INTERRUPT_TYPES_G4X_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Interrupt_Types_G4X.h
 **********************************************************************************************************************/
