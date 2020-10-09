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
 *         \file  Fee_30_SmallSector_Layer2_WriteInstance.h
 *        \brief  WriteInstance sub-component is responsible for writing an instance and veryfing the written data.
 *
 *      \details  WriteInstance sub-component is responsible for writing an instance and veryfing the written data,
 *                if configured. WriteInstance will write the user data to the instance object which is passed as
 *                input. Verification of written data can be enabled/disabled by pre-compile switch.
 *
 *********************************************************************************************************************/


#ifndef FEE_30_SMALLSECTOR_LAYER2_WRITE_INSTANCE_H
# define FEE_30_SMALLSECTOR_LAYER2_WRITE_INSTANCE_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector.h"
#include "Fee_30_SmallSector_InstanceHandler.h"


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_Init()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes internal parameter of WriteInstance sub-component
 * \details    Initializes internal parameter of WriteInstance sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_Init(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_GetStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current status of WriteInstance sub-component
 * \details    Returns current status of WriteInstance sub-component
 * \return     Status of WriteInstance
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_GetStatus(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_GetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current job result of WriteInstance sub-component
 * \details    Returns current job result of WriteInstance sub-component
 * \return     Job result of WriteInstance
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_GetJobResult(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_StartJob()
 *********************************************************************************************************************/
/*!
 * \brief      Initiates WriteInstance sub-component's state machine
 * \details    Initiates WriteInstance sub-component's state machine and registers WriteInstance sub-component to TaskManager
 * \param[in]  Instance
 * \param[in]  UserJobParameter
 * \return     E_OK: Job was accepted by WriteInstance sub-component
 * \return     E_NOT_OK: Job request failed
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_StartJob(Fee_30_SmallSector_Ih_InstanceType Instance, Fee_30_SmallSector_UserJobParameterType UserJobParameter);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_Execute()
 *********************************************************************************************************************/
/*!
 * \brief      Processes internal state machine
 * \details    Processes state machine of WriteInstance sub-component
 * \pre        State machine is initialized.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_Execute(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_Cancel()
 *********************************************************************************************************************/
/*!
 * \brief      Cancels currently running job
 * \details    Cancels currently running job and resets all internal parameter
 * \pre        Sub-component is not idle.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_Cancel(void);


# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* FEE_30_SMALLSECTOR_LAYER2_WRITE_INSTANCE_H */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Layer2_WriteInstance.h
 *********************************************************************************************************************/
