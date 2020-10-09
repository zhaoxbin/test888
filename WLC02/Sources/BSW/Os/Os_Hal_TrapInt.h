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
 *  \defgroup   Os_Hal_Trap HAL Trap
 *  \brief      The platform shall provide trap functions to the OS services here.
 *  \details    The trap functions shall call the associated kernel function in privileged mode.
 *
 *  \{
 *
 *  \file       Os_Hal_TrapInt.h
 *  \brief
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_TRAPINT_H
# define OS_HAL_TRAPINT_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_Trap_Types.h"

/* Os kernel module dependencies */
# include "Os_Trap_Types.h"

/* Os HAL dependencies */
# include "Os_Hal_CompilerInt.h"
# include "Os_Hal_Interrupt_Types.h"


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

#if 0
/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  Os_Hal_Trap()
 **********************************************************************************************************************/
/*! \brief        Trigger trap to execute OS service.
 *  \details      -
 *
 *  \param[in]    Parameters   Parameters to be bypassed to kernel's trap handler. Parameter must not be NULL.
 *
 *  \context      OS_INTERNAL
 *
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *
 *  \pre          Reference API parameters of the TrapPacket are valid.
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DECLARATION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_Trap,
(
  P2VAR(Os_TrapPacketType, AUTOMATIC, OS_VAR_NOINIT) Parameters
));


/***********************************************************************************************************************
 *  Os_Hal_SystemTrap()
 **********************************************************************************************************************/
/*! \brief          Trap instruction (Assembler).
 *  \details        --no details--
 *
 *  \param[in]      Parameters    Parameters to be bypassed to kernel's trap handler.  Parameter must not be NULL.
 *  \param[in,out]  State         Interrupt state of the caller which shall be restored/modified.
 *                                Parameter must not be NULL.
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *
 *  \pre            -
 **********************************************************************************************************************/
FUNC(void, OS_CODE) Os_Hal_SystemTrap
(
  P2VAR(Os_TrapPacketType, AUTOMATIC, OS_VAR_NOINIT) Parameters,
  P2VAR(uint32, AUTOMATIC, OS_VAR_NOINIT) State
);


/***********************************************************************************************************************
 *  Os_Hal_TrapHandler()
 **********************************************************************************************************************/
/*! \brief          Indirects trap requests to \ref Os_TrapHandler().
 *  \details        --no details--
 *
 *  \context        OS_INTERNAL
 *
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *
 *  \pre            -
 **********************************************************************************************************************/
FUNC(void, OS_CODE) Os_Hal_TrapHandler(void);


/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_HAL_TRAPINT_H */

#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_TrapInt.h
 **********************************************************************************************************************/

