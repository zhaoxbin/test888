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
 * \addtogroup  Os_Hal_Coverage
 * \{
 *
 * \file
 * \brief  This file contains derivative specific coverage justifications.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_COVERAGE_F1HINT_H
# define OS_HAL_COVERAGE_F1HINT_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */

/* Os module declarations */

/* Os kernel module dependencies */

/* Os hal dependencies */

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

/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/* START_COVERAGE_JUSTIFICATION

\ID COV_OS_HALTIMERSTMUNSUPPORTED_XX
   \ACCEPT XX
   \REASON Timer STM is not available on this derivative but it is tested on reference derivative P1HC.
   
\ID COV_OS_HALTIMERSTMUNSUPPORTED_XF
   \ACCEPT XF
   \REASON Timer STM is not available on this derivative but it is tested on reference derivative P1HC.

\ID COV_OS_HALPLATFORMPFRTUNSUPPORTED_XX
   \ACCEPT XX
   \REASON Timer PFRT is not available on this derivative but it is tested on reference derivative P1HC.

\ID COV_OS_HALPLATFORMPERIPHERALINTTRIGGERSUPPORTED
  \ACCEPT TX
  \REASON This platform always support peripheral interrupt software trigger.

\ID COV_OS_HALPLATFORMLEVELSUPPORT
  \ACCEPT TX
  \REASON This derivative does support interrupt level switching.

END_COVERAGE_JUSTIFICATION */

#endif /* OS_HAL_COVERAGE_F1HINT_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Coverage_F1HInt.h
 **********************************************************************************************************************/
 
