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
 *  \defgroup   Os_Hal_Compiler  HAL Compiler
 *  \brief      Abstraction of compiler specific keywords to allow the compiler to generate more efficient code.
 *  \details
 *  The kernel should be able to give the compiler meta information to generate more efficient code.
 *  It also needs to tell the linker where to put data and code to implement Memory Protection.
 *  In multi core systems there may be the need for data/code duplication.
 *  The keywords to provide this information are not part of ANSI-C and are highly compiler dependent.
 *
 *  AUTOSAR already defines concepts to abstract compiler specifics:
 *  - [AUTOSAR Compiler Abstraction](www.autosar.org/fileadmin/files/releases/4-2/software-architecture/
 *                                   implementation-integration/standard/AUTOSAR_SWS_CompilerAbstraction.pdf)
 *  - [AUTOSAR Memory Mapping](www.autosar.org/fileadmin/files/releases/3-2/software-architecture/implementation
 *                             -integration/standard/AUTOSAR_SWS_MemoryMapping.pdf)
 *
 *  They are used in MICROSAR OS. This module defines additional compiler abstraction keywords for MICROSAR OS.
 *  They are relevant to provide OS functionality or improve efficiency.
 *
 *  \{
 *
 *  \file       Os_Hal_CompilerInt.h
 *  \brief      Additional services defined here are available to the user.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_COMPILERINT_H
# define OS_HAL_COMPILERINT_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */
# include "Os_Cfg.h"
# include "Os_CommonInt.h"

/* Os HAL dependencies */
# if defined(OS_STATIC_CODE_ANALYSIS)                                                                                   /* COV_OS_STATICCODEANALYSIS */
#  include "Os_Hal_StaticCodeAnalysis.h"
# else
#  if defined (OS_CFG_COMPILER_RENESAS)                                                                                 /* COV_OS_DERIVATIVEBETAMODULE */
#   include "Os_Hal_Compiler_RenesasCCRHInt.h"
#  elif defined (OS_CFG_COMPILER_GREENHILLS)
#   include "Os_Hal_Compiler_GreenHillsInt.h"
#  else
#   error "Undefined or unsupported compiler"
#  endif
# endif


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

# define Os_Hal_Expand(x)   Os_Hal_Expand2(x)                                                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Os_Hal_Expand2(x)  Os_Hal_Expand3(x)                                                                           /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define Os_Hal_Expand3(x)  #x                                                                                          /* PRQA S 0341 */ /* MD_Os_Hal_Rule20.10_0341 */

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/


#endif /* OS_HAL_COMPILERINT_H */

/* module specific MISRA deviations:

  MD_Os_Hal_Rule1.1_0605_ASM:
      Reason:     This is a assembler stub function for static code analysis. Analyzing the original code is impossible.
      Risk:       None.
      Prevention: None.

  MD_Os_Hal_Rule8.13_3673_NotUsed:
      Reason:     This input parameter is not used in this HAL implementation, thus it is not modified. However, since
                  it may be used or modified in other platforms, it is unavoidable to keep it as "pointer to non-const".
      Risk:       None.
      Prevention: None.

  MD_Os_Hal_Rule8.13_3673_ModifiedArgument:
      Reason:     As the passed argument is modified within a called function, the argument has to be of type pointer
                  to variable.
      Risk:       None.
      Prevention: None.

  MD_Os_Hal_Rule11.1_0305:
      Reason:     This statement converts a function pointer to an integral address. This is unavoidable to put the
                  function pointer to a core register.
      Risk:       None.
      Prevention: None.

  MD_Os_Hal_Rule11.3_0310:
      Reason:     Assembler interface which requires a pointer to a native data type.
      Risk:       None, as compiler dependencies are considered by the compiler abstraction.
      Prevention: None.

  MD_Os_Hal_Rule11.4_0303:
      Reason:     This statement converts an integral address to a pointer or vice versa. This is unavoidable for
                  memory access of that address or to put a pointer to a core register.
      Risk:       None.
      Prevention: None.

  MD_Os_Hal_Rule11.4_0306:
      Reason:     This statement converts a pointer to object to an integral address. This is unavoidable to read back
                  or write the corresponding address from or to a core register.
      Risk:       None.
      Prevention: None.

  MD_Os_Hal_Rule11.6_0326:
      Reason:     This statement converts a register value to an address type during function call. This is unavoidable
                  to read the according value from an core register.
      Risk:       None.
      Prevention: None.

  MD_Os_Hal_Rule14.3_2741:
     Reason:      The evaluation of the controlling expression depends on the underlying derivative.
                  For the derivative under test, the decision is always true.
     Risk:        None.
     Prevention:  None.

  MD_Os_Hal_Rule16.3_2003:
     Description: The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return'
                  statement.
     Reason:      To use optimal design small switch-case dispatchers use fall-through cases.
     Risk:        None, since the switch case has a regular structure and is therefore easy to understand.
     Prevention:  None.

  MD_Os_Hal_Rule18.4_0488:
      Reason:     Pointer arithmetic is used here to calculate the stack usage. The returned value is never used as a pointer.
      Risk:       None.
      Prevention: None.

  MD_Os_Hal_Rule20.10_0341:
      Reason:     This statement concatenates two strings or a string and a value. This is unavoidable for
                  memory access of that address or put a pointer to a core register.
      Risk:       None.
      Prevention: None.

  MD_Os_Hal_STCAL:
     Description: Functions contains multiple number of inline assembly function calls. Inline assembly function
                  is interpreted as function call and thus violating STCAL metric.
     Reason:      Simplicity and readability of code is increased.
     Risk:        None.
     Prevention:  None.

 */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_CompilerInt.h
 **********************************************************************************************************************/

