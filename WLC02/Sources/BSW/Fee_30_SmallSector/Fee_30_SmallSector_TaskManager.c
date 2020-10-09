/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *        \file  Fee_30_SmallSector_TaskManager.c
 *       \brief  Fee Sub-component TaskManager source file
 *
 *     \details  TaskManager is responsible for processing asynchronous sub-components in correct order by calling the
 *               appropriate execution services. TaskManager is also responsible for canceling all active sub-components
 *               in case Fee_30_SmallSector_Cancel was called by user.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#define FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector_TaskManager.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_NUMBER_OF_LAYERS        (0x03u)

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#ifndef FEE_30_SMALLSECTOR_LOCAL /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL static
#endif

typedef P2FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_Tm_FctPtrType)(void);

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Variable which represents job stack */
FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_Tm_FctPtrType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Tm_ExecuteServiceStack[FEE_30_SMALLSECTOR_NUMBER_OF_LAYERS];

/* Variable which represents cancel stack */
FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_Tm_FctPtrType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Tm_CancelServiceStack[FEE_30_SMALLSECTOR_NUMBER_OF_LAYERS];

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_CODE
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_GetActiveTask()
**********************************************************************************************************************/
/*!
 * \brief      Returns most recent execution service from job stack
 * \details    Returns most recent execution service from job stack
 * \return     Function pointer of execution service
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (Fee_30_SmallSector_Tm_FctPtrType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Tm_GetActiveTask (void);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_GetActiveTask()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (Fee_30_SmallSector_Tm_FctPtrType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Tm_GetActiveTask (void)
{
  sint8 LoopCounter;
  Fee_30_SmallSector_Tm_FctPtrType returnValue = NULL_PTR;

  /* #10 Loop steps backwards through job stack beginning with layer 3 element */
  for (LoopCounter = ((sint8) FEE_30_SMALLSECTOR_NUMBER_OF_LAYERS - (sint8) 1); LoopCounter >= (sint8) 0; LoopCounter--)
  {
    /* #20 First element in job stack which contains an execution function will be returned */
    if (Fee_30_SmallSector_Tm_ExecuteServiceStack[LoopCounter] != NULL_PTR)
    {
      returnValue = Fee_30_SmallSector_Tm_ExecuteServiceStack[LoopCounter];
      break;
    }
  }
  return returnValue;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_Init()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Tm_Init(void)
{
  uint8 LoopCounter;
  for (LoopCounter = 0; LoopCounter < FEE_30_SMALLSECTOR_NUMBER_OF_LAYERS; LoopCounter++)
  {
    Fee_30_SmallSector_Tm_ExecuteServiceStack[LoopCounter] = NULL_PTR; /* SBSW_FEE_30_SMALLSECTOR_11 */
    Fee_30_SmallSector_Tm_CancelServiceStack[LoopCounter] = NULL_PTR; /* SBSW_FEE_30_SMALLSECTOR_11 */
  }
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_AddTask()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Tm_AddTask (Fee_30_SmallSector_Tm_ExecuteServicePointerType ExecuteService,
        Fee_30_SmallSector_Tm_CancelServicePointerType CancelService, uint8 Layer)
{
  Std_ReturnType retVal;
  /* #10 Ensure that position in job stack is empty before adding services to execution and cancel stack */
  if ((Fee_30_SmallSector_Tm_ExecuteServiceStack[Layer] == NULL_PTR) && (Fee_30_SmallSector_Tm_CancelServiceStack[Layer] == NULL_PTR))
  {
    Fee_30_SmallSector_Tm_ExecuteServiceStack[Layer] = ExecuteService; /* SBSW_FEE_30_SMALLSECTOR_12 */
    Fee_30_SmallSector_Tm_CancelServiceStack[Layer] = CancelService; /* SBSW_FEE_30_SMALLSECTOR_12 */
    retVal = E_OK;
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_RemoveTask()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Tm_RemoveTask (Fee_30_SmallSector_Tm_ExecuteServicePointerType ExecuteService,
        Fee_30_SmallSector_Tm_CancelServicePointerType CancelService, uint8 Layer)
{
  /* #10 Ensure that services which should be removed match services of calling layer */
  if ((Fee_30_SmallSector_Tm_ExecuteServiceStack[Layer] == ExecuteService) && (Fee_30_SmallSector_Tm_CancelServiceStack[Layer] == CancelService))
  {
    Fee_30_SmallSector_Tm_ExecuteServiceStack[Layer] = NULL_PTR; /* SBSW_FEE_30_SMALLSECTOR_12 */
    Fee_30_SmallSector_Tm_CancelServiceStack[Layer] = NULL_PTR; /* SBSW_FEE_30_SMALLSECTOR_12 */
  }
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_ExecuteTask()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Tm_ExecuteTask (void)
{
  /* #10 Retrieve last execution service in job stack */
  Fee_30_SmallSector_Tm_FctPtrType currentExecuteService = Fee_30_SmallSector_Tm_GetActiveTask();

  /* #20 Check for NULL_PTR which is returned in case no sub-component is registered to TaskManager */
  if (currentExecuteService != NULL_PTR)
  {
    currentExecuteService(); /* SBSW_FEE_30_SMALLSECTOR_13 */
  }
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_CancelTasks()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Tm_CancelTasks (void)
{
  sint8 LoopCounter;

  /* #10 Cancel services of all registered layers are called beginning with layer 3 */
  /* #20 Index accessing CancelServiceStack is zero based, thus FEE_30_SMALLSECTOR_NUMBER_OF_LAYERS is decremented by one */
  for (LoopCounter = ((sint8) FEE_30_SMALLSECTOR_NUMBER_OF_LAYERS - (sint8) 1); LoopCounter >= (sint8) 0; LoopCounter--)
  {
    if (Fee_30_SmallSector_Tm_CancelServiceStack[LoopCounter] != NULL_PTR)
    {
      Fee_30_SmallSector_Tm_CancelServiceStack[LoopCounter](); /* SBSW_FEE_30_SMALLSECTOR_13 */
    }
  }
}


#define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA L:LongInfixName */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_TaskManager.c
 *********************************************************************************************************************/

/* SBSW_JUSTIFICATION_BEGIN
    \ID SBSW_FEE_30_SMALLSECTOR_11
      \DESCRIPTION Array write access of parameters Fee_30_SmallSector_Tm_ExecuteServiceStack and Fee_30_SmallSector_Tm_CancelServiceStack in for-loop.
      \COUNTERMEASURE \N Array write access is not critical because both the upper limit of the for-loop and the size of
                         the array parameters is determined by private #define FEE_30_SMALLSECTOR_NUMBER_OF_LAYERS.
                         The lower limit (0) of the for-loop is legitimate as well.

    \ID SBSW_FEE_30_SMALLSECTOR_12
      \DESCRIPTION Array write access of parameters Fee_30_SmallSector_Tm_ExecuteServiceStack and Fee_30_SmallSector_Tm_CancelServiceStack at
                   index Layer. Every sub-component of FEE module accesses the service, thus it has to be assured that
                   no out of bounds access occurs.
      \COUNTERMEASURE \T TCASE-391761
                         The test ensures that each sub-component passes a valid Layer index which is not out of bounds.

    \ID SBSW_FEE_30_SMALLSECTOR_13
      \DESCRIPTION Function, which is referenced by function pointer, is invoked. Function pointers are registered to TaskManager by FEE's
                   sub-components.
      \COUNTERMEASURE \R It is checked whether the function pointer to be invoked is not NULL_PTR

    \ID SBSW_FEE_30_SMALLSECTOR_14
      \DESCRIPTION TaskManager's function Fee_30_SmallSector_Tm_AddTask is called with pointers to sub-component's execution service and cancel service
      \COUNTERMEASURE \N Fee_30_SmallSector_Tm_AddTask is explicitly called with pointers to local functions

    \ID SBSW_FEE_30_SMALLSECTOR_15
      \DESCRIPTION TaskManager's function Fee_30_SmallSector_Tm_RemoveTask is called with pointers to sub-component's execution service and cancel service
      \COUNTERMEASURE \N Fee_30_SmallSector_Tm_RemoveTask is explicitly called with pointers to local functions

SBSW_JUSTIFICATION_END */


