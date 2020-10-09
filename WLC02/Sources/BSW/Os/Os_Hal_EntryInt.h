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
 *  \defgroup   Os_Hal HAL
 *  \brief      The HAL provides the platform specific low level part of the OS. It has to be implemented by the
 *              platform.
 *  \details    All files given here define the HAL and can be seen as a template to implement a new platform.
 */
/**
 *  \ingroup    Os_Hal
 *  \defgroup   Os_Hal_Entry  HAL Entry
 *  \brief      This component handles hardware exceptions and interrupts.
 *  \details
 *  Most of the HAL consists of macros and functions that are called by the kernel via the
 *  HAL interface. These perform the required low level operations by accessing the hardware and then return.
 *  The entry component is an exception to this. It handles exceptions: either synchronous hardware traps or
 *  asynchronous device interrupts. So we have some kind of control inversion here.
 *
 *  First the control is passed to the HAL, which then passes it to the kernel or the application.
 *  After the kernel has finished, control is passed back to the HAL for in order to restore the CPU
 *  state and resume processing from the point at which the exception occurred.
 *
 *  The exact implementation of this code is under the control of the HAL implementer. As long as it interacts
 *  correctly with the functions defined in Kernel Interface it may take any form. However there is typically
 *  the entry type pattern which is listed in this component description.
 *
 *  If there are any statements within a HAL function, which have influence to the control flow, the platform
 *  developer has to ensure that all paths are covered by tests (MC/DC). If this it not possible, the
 *  functionality has to be ensured by review.
 *
 *  Timing Protection Interrupt
 *  ---------------------------
 *  The kernel handles timing protection interrupts in an ISR. The ISR has to be executed with highest priority
 *  (or NMI).
 *
 *  Inter Processor Interrupt
 *  -------------------------
 *  The kernel handles inter processor interrupts in an ISR.
 *
 *   \{
 *  \file       Os_Hal_EntryInt.h
 *  \brief      This component handles hardware exceptions and interrupts.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_ENTRYINT_H
# define OS_HAL_ENTRYINT_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_Entry_Types.h"

/* Os kernel module dependencies */
# include "Os_KernelInt.h"

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

extern void Os_Hal_UnhandledSysCall(void);


#endif /* OS_HAL_ENTRYINT_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_EntryInt.h
 **********************************************************************************************************************/

