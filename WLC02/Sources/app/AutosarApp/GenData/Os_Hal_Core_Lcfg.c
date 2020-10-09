/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Os
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Hal_Core_Lcfg.c
 *   Generation Time: 2020-06-20 15:53:48
 *           Project: WLC - Version 1.0
 *          Delivery: CBD1900162_D00
 *      Tool Version: DaVinci Configurator (beta) 5.19.29
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 ! BETA VERSION                                                                                                       !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 ! This version of DaVinci Configurator Pro and/or the related Basic Software Package is BETA software.               !
 ! BETA Software is basically operable, but not sufficiently tested, verified and/or qualified for use in series      !
 ! production and/or in vehicles operating on public or non-public roads.                                             !
 ! In particular, without limitation, BETA Software may cause unpredictable ECU behavior, may not provide all         !
 ! functions necessary for use in series production and/or may not comply with quality requirements which are         !
 ! necessary according to the state of the art. BETA Software must not be used in series production.                  !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**********************************************************************************************************************/

/* PRQA S 0777, 0779, 0828 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2, MD_MSR_Dir1.1 */

#define OS_HAL_CORE_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Core_Lcfg.h"
#include "Os_Hal_Core.h"

/* Os kernel module dependencies */

/* Os hal dependencies */
#include "Os_Hal_Context_Lcfg.h"
#include "Os_Hal_Entry_Lcfg.h"
#include "Os_Hal_Interrupt_Lcfg.h"
#include "Os_Hal_Kernel_Lcfg.h"


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_VAR_FAST_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL dynamic core to thread data: OsCore0 */
OS_LOCAL VAR(Os_Hal_Core2ThreadType, OS_VAR_NOINIT_FAST) OsCfg_Hal_Core2Thread_OsCore0_Dyn;

#define OS_STOP_SEC_CORE0_VAR_FAST_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL core initialized interrupt sources: OsCore0 */
CONSTP2CONST(Os_Hal_IntIsrConfigType, OS_CONST, OS_CONST)
  OsCfg_Hal_Core_OsCore0_InterruptSourceRefs[OS_CFG_NUM_CORE_OSCORE0_INTERRUPTSOURCEREFS + 1u] =
{
  &OsCfg_Hal_IntIsr_CanIsrGlobalStatus,
  &OsCfg_Hal_IntIsr_CanIsrRxFifo,
  &OsCfg_Hal_IntIsr_CanIsrStatus_0,
  &OsCfg_Hal_IntIsr_CanIsrTx_0,
  &OsCfg_Hal_IntIsr_CanIsrWakeup_0,
  NULL_PTR
};


/*! HAL core configuration data: OsCore0 */
CONST(Os_Hal_CoreConfigType, OS_CONST) OsCfg_Hal_Core_OsCore0 =
{
  0
};

/*! HAL AUTOSAR core configuration data: OsCore0 */
CONST(Os_Hal_CoreAsrConfigType, OS_CONST) OsCfg_Hal_CoreAsr_OsCore0 =
{
  _OS_EXCVEC_CORE0_CODE_START,
  _OS_INTVEC_CORE0_CODE_START,
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL core to thread configuration data. */
CONST(Os_Hal_Core2ThreadConfigType, OS_CONST) OsCfg_Hal_Core2Thread =
{
  /* .Core2Thread = */
  {
    &OsCfg_Hal_Core2Thread_OsCore0_Dyn, /* OS_CORE_ID_0 */
  }
};

/*! HAL system configuration data. */
CONST(Os_Hal_SystemConfigType, OS_CONST) OsCfg_Hal_System =
{
  1,
  {
    &OsCfg_Hal_CoreAsr_OsCore0,
    NULL_PTR
  }  
};

/*! Interrupt sources which are initialized by the hardware init core. */
CONSTP2CONST(Os_Hal_IntIsrConfigType, OS_CONST, OS_CONST)
  OsCfg_Hal_System_InterruptSourceRefs[OS_CFG_NUM_SYSTEM_INTERRUPTSOURCEREFS + 1u] =
{
  &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer,
  NULL_PTR
};


#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Core_Lcfg.c
 *********************************************************************************************************************/

