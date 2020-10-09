/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  SchM_Nm.h
 *           Config:  WLC.dpa
 *      ECU-Project:  WLC
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Header of BSW Scheduler for BSW Module <Nm>
 *********************************************************************************************************************/
#ifndef SCHM_NM_H
# define SCHM_NM_H

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

# include "SchM_Nm_Type.h"

# include "Os.h" /* PRQA S 0828, 0883 */ /* MD_MSR_1.1_828, MD_Rte_Os */

# define SchM_Enter_Nm_NM_EXCLUSIVE_AREA_0() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Nm_NM_EXCLUSIVE_AREA_0() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_Nm_NM_EXCLUSIVE_AREA_1() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_Nm_NM_EXCLUSIVE_AREA_1() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */


# ifdef __cplusplus
} /* extern "C" */
# endif  /* __cplusplus */

#endif /* SCHM_NM_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_Os:
     Reason:     This justification is used as summary justification for all deviations caused by the MICROSAR OS
                 which is for testing of the RTE. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

*/
