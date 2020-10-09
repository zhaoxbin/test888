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
 *         \file  Fee_30_SmallSector_Layer2_InstanceFinder.h
 *        \brief  InstanceFinder is responsible for finding the most recent data
 *
 *      \details  InstanceFinder is responsible for determination of the address of recently written data (here: instance)
 *                in Flash according to specific BlockNumber (UserJobParameter). InstanceFinder is responsible for
 *                evaluating the determined instance's status and stores it to the instance object which is passed by caller.
 *
 *********************************************************************************************************************/


#ifndef FEE_30_SMALLSECTOR_SUB_INSTANCE_FINDER_H
# define FEE_30_SMALLSECTOR_SUB_INSTANCE_FINDER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector.h"
#include "Fee_30_SmallSector_InstanceHandler.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES
 *********************************************************************************************************************/

typedef enum
{
  INSTANCE_FINDER_OK = 0,
  INSTANCE_FINDER_PENDING,
  INSTANCE_FINDER_CANCELED,
  INSTANCE_FINDER_FAILED,
  INSTANCE_FINDER_INCONSISTENT,
  INSTANCE_FINDER_INVALID,
  INSTANCE_FINDER_EP1_INCORRECT,
  INSTANCE_FINDER_EP2_INCORRECT
}Fee_30_SmallSector_If_ResultType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_If_Init()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes internal parameter of InstanceFinder sub-component
 * \details    Initializes internal parameter of InstanceFinder sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_If_Init(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_If_GetStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current status of InstanceFinder sub-component
 * \details    Returns current status of InstanceFinder sub-component
 * \return     Status of InstanceFinder
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_If_GetStatus(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_If_GetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current job result of InstanceFinder sub-component
 * \details    Returns current job result of InstanceFinder sub-component
 * \return     Job result of InstanceFinder
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(Fee_30_SmallSector_If_ResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_If_GetJobResult(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_If_StartJob()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes InstanceFinder sub-component's state machine
 * \details    Initializes InstanceFinder sub-component's state machine and registers sub-component to TaskManager
 * \param[in]  Instance
 * \return     E_OK: Job was accepted by InstanceFinder sub-component
 * \return     E_NOT_OK: Job request failed
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_If_StartJob(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_If_Execute()
 *********************************************************************************************************************/
/*!
 * \brief      Processes internal state machine
 * \details    Processes state machine of InstanceFinder sub-component, only if status is busy
 * \pre        State machine is initialized.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_If_Execute(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_If_Cancel()
 *********************************************************************************************************************/
/*!
 * \brief      Cancels currently running job
 * \details    Cancels currently running job and resets all internal parameter
 * \pre        Sub-component is not idle.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_If_Cancel(void);


/**********************************************************************************************************************
 Fee_30_SmallSector_If_MapResult()
 **********************************************************************************************************************/
/*!
 * \brief      Maps Fee_30_SmallSector_If_ResultType to MemIf_JobResultType
 * \details    Maps Fee_30_SmallSector_If_ResultType to MemIf_JobResultType
 * \param[in]  JobResult
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_If_MapResult(Fee_30_SmallSector_If_ResultType JobResult);

# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* FEE_30_SMALLSECTOR_SUB_INSTANCE_FINDER_H */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Layer2_InstanceFinder.h
 *********************************************************************************************************************/
