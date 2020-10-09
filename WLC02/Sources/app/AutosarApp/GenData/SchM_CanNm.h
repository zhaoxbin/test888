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
 *             File:  SchM_CanNm.h
 *           Config:  WLC.dpa
 *      ECU-Project:  WLC
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Header of BSW Scheduler for BSW Module <CanNm>
 *********************************************************************************************************************/
#ifndef SCHM_CANNM_H
# define SCHM_CANNM_H

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

# include "SchM_CanNm_Type.h"

# include "Os.h" /* PRQA S 0828, 0883 */ /* MD_MSR_1.1_828, MD_Rte_Os */

# define CANNM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

FUNC(void, CANNM_CODE) CanNm_MainFunction(void); /* PRQA S 3451 */ /* MD_Rte_3451 */

# define CANNM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_0() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_0() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_1() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_1() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_2() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_2() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_3() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_3() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_4() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_4() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_5() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_5() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_6() SuspendAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */

# define SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_6() ResumeAllInterrupts()  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */


# ifdef __cplusplus
} /* extern "C" */
# endif  /* __cplusplus */

#endif /* SCHM_CANNM_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3451:  MISRA rule: 8.8
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_Os:
     Reason:     This justification is used as summary justification for all deviations caused by the MICROSAR OS
                 which is for testing of the RTE. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

*/
