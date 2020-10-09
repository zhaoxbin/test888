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
 *              File: Os_Scheduler_Lcfg.c
 *   Generation Time: 2020-02-08 12:42:12
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

#define OS_SCHEDULER_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Scheduler_Cfg.h"
#include "Os_Scheduler_Lcfg.h"
#include "Os_Scheduler.h"

/* Os kernel module dependencies */
#include "Os_BitArray.h"
#include "Os_Common.h"
#include "Os_Deque.h"

/* Os hal dependencies */


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

#define OS_START_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic scheduler data: OsCore0 */
OS_LOCAL VAR(Os_SchedulerType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore0_Dyn;
OS_LOCAL VAR(Os_BitArrayType, OS_VAR_NOINIT) OsCfg_Scheduler_OsCore0_BitArray_Dyn;
OS_LOCAL OS_BITARRAY_DECLARE(OsCfg_Scheduler_OsCore0_BitField_Dyn, OS_CFG_NUM_TASKQUEUES, OS_VAR_NOINIT);

/*! Dynamic task queues data: OsCore0 */
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue0_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes0_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE0_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue1_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes1_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE1_OSCORE0_SLOTS];
OS_LOCAL VAR(Os_DequeType, OS_VAR_NOINIT) OsCfg_TaskQueue2_OsCore0_Dyn;
OS_LOCAL VAR(Os_DequeNodeType, OS_VAR_NOINIT)
  OsCfg_TaskQueueNodes2_OsCore0_Dyn[OS_CFG_NUM_TASKQUEUE2_OSCORE0_SLOTS];

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Task queues configuration data: OsCore0 */
OS_LOCAL CONST(Os_DequeConfigType, OS_CONST) OsCfg_Scheduler_OsCore0_TaskQueues[OS_CFG_NUM_TASKQUEUES] =
{
  /* [0] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue0_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes0_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE0_OSCORE0_SLOTS
  },
  /* [1] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue1_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes1_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE1_OSCORE0_SLOTS
  },
  /* [2] = */
  {
    /* .Dyn    = */ &OsCfg_TaskQueue2_OsCore0_Dyn,
    /* .Buffer = */ OsCfg_TaskQueueNodes2_OsCore0_Dyn,
    /* .Size   = */ OS_CFG_NUM_TASKQUEUE2_OSCORE0_SLOTS
  }
};

/*! Scheduler configuration data: OsCore0 */
CONST(Os_SchedulerConfigType, OS_CONST) OsCfg_Scheduler_OsCore0 =
{
  /* .BitArray           = */
  {
    /* .Dyn       = */ &OsCfg_Scheduler_OsCore0_BitArray_Dyn,
    /* .Data      = */ OsCfg_Scheduler_OsCore0_BitField_Dyn,
    /* .Size      = */ (uint16)OS_BITARRAY_SIZE(OS_CFG_NUM_TASKQUEUES),
    /* .BitLength = */ (uint16)OS_BITARRAY_LENGTH(OS_CFG_NUM_TASKQUEUES),
  },
  /* .Dyn                = */ &OsCfg_Scheduler_OsCore0_Dyn,
  /* .TaskQueues         = */ OsCfg_Scheduler_OsCore0_TaskQueues,
  /* .NumberOfPriorities = */ OS_CFG_NUM_TASKQUEUES
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
 *  END OF FILE: Os_Scheduler_Lcfg.c
 *********************************************************************************************************************/
