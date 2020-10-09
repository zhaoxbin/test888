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
 *             File:  SchM_Icu.h
 *           Config:  WLC.dpa
 *      ECU-Project:  WLC
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Header of BSW Scheduler for BSW Module <Icu>
 *********************************************************************************************************************/
#ifndef SCHM_ICU_H
# define SCHM_ICU_H

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

# include "SchM_Icu_Type.h"

# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

FUNC(void, RTE_CODE) SchM_Enter_Icu_ICU_CHANNEL_DATA_PROTECTION(void);
FUNC(void, RTE_CODE) SchM_Exit_Icu_ICU_CHANNEL_DATA_PROTECTION(void);
FUNC(void, RTE_CODE) SchM_Enter_Icu_ICU_EDGECOUNT_DATA_PROTECTION(void);
FUNC(void, RTE_CODE) SchM_Exit_Icu_ICU_EDGECOUNT_DATA_PROTECTION(void);
FUNC(void, RTE_CODE) SchM_Enter_Icu_ICU_SIGNALMEASURE_DATA_PROTECTION(void);
FUNC(void, RTE_CODE) SchM_Exit_Icu_ICU_SIGNALMEASURE_DATA_PROTECTION(void);
FUNC(void, RTE_CODE) SchM_Enter_Icu_ICU_TIMESTAMP_DATA_PROTECTION(void);
FUNC(void, RTE_CODE) SchM_Exit_Icu_ICU_TIMESTAMP_DATA_PROTECTION(void);

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif  /* __cplusplus */

#endif /* SCHM_ICU_H */
