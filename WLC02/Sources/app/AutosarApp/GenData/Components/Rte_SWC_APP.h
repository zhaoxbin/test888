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
 *             File:  Rte_SWC_APP.h
 *           Config:  WLC.dpa
 *      ECU-Project:  WLC
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Application header file for SW-C <SWC_APP>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SWC_APP_H
# define _RTE_SWC_APP_H

# ifndef RTE_CORE
#  ifdef RTE_APPLICATION_HEADER_FILE
#   error Multiple application header files included.
#  endif
#  define RTE_APPLICATION_HEADER_FILE
#  ifndef RTE_PTR2ARRAYBASETYPE_PASSING
#   define RTE_PTR2ARRAYBASETYPE_PASSING
#  endif
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_SWC_APP_Type.h"
# include "Rte_DataHandleType.h"

# ifndef RTE_CORE

#  include "Com.h"


# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_VehSpd_VehSpd (0U)
# endif


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_VehSpd_VehSpd Rte_Read_SWC_APP_VehSpd_VehSpd
#  define Rte_Read_SWC_APP_VehSpd_VehSpd(data) (Com_ReceiveSignal(ComConf_ComSignal_VehSpd_oBCU_04_oNIO_ES6_RF_CAN_SR_V3_0_91cf0813_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */


# endif /* !defined(RTE_CORE) */


# define SWC_APP_START_SEC_CODE
# include "SWC_APP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_WLCAPP_Runnable WLCAPP_Runnable
# endif

FUNC(void, SWC_APP_CODE) WLCAPP_Runnable(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */

# define SWC_APP_STOP_SEC_CODE
# include "SWC_APP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_SWC_APP_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3451:  MISRA rule: 8.8
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
