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
 *              File: Os_Hal_Interrupt_Lcfg.c
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

#define OS_HAL_INTERRUPT_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Interrupt_Lcfg.h"
#include "Os_Hal_Interrupt.h"

/* Os kernel module dependencies */

/* Os hal dependencies */
#include "Os_Hal_Core.h"


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

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CanIsrGlobalStatus */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CanIsrGlobalStatus =
{
  /* .EICBaseAddr = */ (Os_Hal_EICnRefType)(OS_HAL_INTC1_BASE + (OS_HAL_EIC_OFFSET * 5uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IBDBaseAddr = */ (Os_Hal_IBDnRefType)(OS_HAL_EIBD1_BASE + (OS_HAL_IBD_OFFSET * 5uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IntChannel  = */ (uint32)5uL,
  /* .IntLevel    = */ (uint32)0uL,
  /* .IntMask     = */ (uint32)(0x0000FFFFuL & OS_HAL_PMR_MASK),
  /* .CoreID      = */ (uint32)0uL
};

/*! HAL ISR configuration data: CanIsrRxFifo */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CanIsrRxFifo =
{
  /* .EICBaseAddr = */ (Os_Hal_EICnRefType)(OS_HAL_INTC1_BASE + (OS_HAL_EIC_OFFSET * 2uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IBDBaseAddr = */ (Os_Hal_IBDnRefType)(OS_HAL_EIBD1_BASE + (OS_HAL_IBD_OFFSET * 2uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IntChannel  = */ (uint32)2uL,
  /* .IntLevel    = */ (uint32)0uL,
  /* .IntMask     = */ (uint32)(0x0000FFFFuL & OS_HAL_PMR_MASK),
  /* .CoreID      = */ (uint32)0uL
};

/*! HAL ISR configuration data: CanIsrStatus_0 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CanIsrStatus_0 =
{
  /* .EICBaseAddr = */ (Os_Hal_EICnRefType)(OS_HAL_INTC1_BASE + (OS_HAL_EIC_OFFSET * 3uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IBDBaseAddr = */ (Os_Hal_IBDnRefType)(OS_HAL_EIBD1_BASE + (OS_HAL_IBD_OFFSET * 3uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IntChannel  = */ (uint32)3uL,
  /* .IntLevel    = */ (uint32)0uL,
  /* .IntMask     = */ (uint32)(0x0000FFFFuL & OS_HAL_PMR_MASK),
  /* .CoreID      = */ (uint32)0uL
};

/*! HAL ISR configuration data: CanIsrTx_0 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CanIsrTx_0 =
{
  /* .EICBaseAddr = */ (Os_Hal_EICnRefType)(OS_HAL_INTC1_BASE + (OS_HAL_EIC_OFFSET * 4uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IBDBaseAddr = */ (Os_Hal_IBDnRefType)(OS_HAL_EIBD1_BASE + (OS_HAL_IBD_OFFSET * 4uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IntChannel  = */ (uint32)4uL,
  /* .IntLevel    = */ (uint32)0uL,
  /* .IntMask     = */ (uint32)(0x0000FFFFuL & OS_HAL_PMR_MASK),
  /* .CoreID      = */ (uint32)0uL
};

/*! HAL ISR configuration data: CanIsrWakeup_0 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CanIsrWakeup_0 =
{
  /* .EICBaseAddr = */ (Os_Hal_EICnRefType)(OS_HAL_INTC1_BASE + (OS_HAL_EIC_OFFSET * 1uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IBDBaseAddr = */ (Os_Hal_IBDnRefType)(OS_HAL_EIBD1_BASE + (OS_HAL_IBD_OFFSET * 1uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IntChannel  = */ (uint32)1uL,
  /* .IntLevel    = */ (uint32)0uL,
  /* .IntMask     = */ (uint32)(0x0000FFFFuL & OS_HAL_PMR_MASK),
  /* .CoreID      = */ (uint32)0uL
};

/*! HAL ISR configuration data: CounterIsr_SystemTimer */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer =
{
  /* .EICBaseAddr = */ (Os_Hal_EICnRefType)(OS_HAL_INTC2_BASE + (OS_HAL_EIC_OFFSET * 84uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IBDBaseAddr = */ (Os_Hal_IBDnRefType)(OS_HAL_EIBD2_BASE + (OS_HAL_IBD_OFFSET * 84uL)),           /* PRQA S 0303 */ /* MD_Os_Hal_Rule11.4_0303 */
  /* .IntChannel  = */ (uint32)84uL,
  /* .IntLevel    = */ (uint32)0uL,
  /* .IntMask     = */ (uint32)(0x0000FFFFuL & OS_HAL_PMR_MASK),
  /* .CoreID      = */ (uint32)0uL
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
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
 *  END OF FILE: Os_Hal_Interrupt_Lcfg.c
 *********************************************************************************************************************/
