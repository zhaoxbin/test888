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
 *        \file  Fee_30_SmallSector_Layer1_Write.h
 *        \brief  This sub-component of FEE module is processing write jobs
 *
 *      \details  FeeWrite sub-component is responsible for writing data from a DataBufferPtr to Flash. Destination in
 *                Flash is specified by passed BlockNumber. Internally, InstanceFinder is used to find most recent write
 *                destination and WriteInstance is used to perform the write job on the determined instance object.
 *
 *********************************************************************************************************************/


#ifndef FEE_30_SMALLSECTOR_LAYER1_WRITE_H
# define FEE_30_SMALLSECTOR_LAYER1_WRITE_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "Fee_30_SmallSector.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_Init()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes internal parameters of FeeWrite sub-component
 * \details    Initializes internal parameters of FeeWrite sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_Init(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_GetStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current status of FeeWrite sub-component
 * \details    Returns current status of FeeWrite sub-component
 * \return     Sub-component's status
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_GetStatus(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_GetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current job result of FeeWrite sub-component
 * \details    Returns current job result of FeeWrite sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_GetJobResult(void);


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_StartJob()
 *********************************************************************************************************************/
/*!
 * \brief      Initiates FeeWrite sub-component's state machine
 * \details    Initiates FeeWrite sub-component's state machine and registers FeeWrite to TaskManager
 * \param[in]  Fee_30_SmallSector_UserJobParameter
 * \return     E_OK: Job was accepted by FeeWrite sub-component
 * \return     E_NOT_OK: Job request failed
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_StartJob(Fee_30_SmallSector_UserJobParameterType Fee_30_SmallSector_UserJobParameter);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_Execute()
 *********************************************************************************************************************/
/*!
 * \brief      Processes internal state machine
 * \details    Processes state machine of FeeWrite sub-component, only if status is busy
 * \pre        State machine is initialized.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_Execute(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_Cancel()
 *********************************************************************************************************************/
/*!
 * \brief      Cancels currently running job
 * \details    Cancels currently running job and resets all internal parameters
 * \pre        Sub-component is not idle.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_Cancel(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_SuspendWrites()
 *********************************************************************************************************************/
/*!
 * \brief      Blocks all write jobs
 * \details    Blocks all write jobs. Pending write jobs are paused until writes are resumed again.
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_SuspendWrites(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_ResumeWrites()
 *********************************************************************************************************************/
/*!
 * \brief      Resumes previously suspended write jobs
 * \details    Resumes previously suspended write jobs
 * \pre        Write jobs were previously suspended by SuspendWrites API
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_ResumeWrites(void);

# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* FEE_30_SMALLSECTOR_LAYER1_WRITE_H */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Layer1_Write.h
 *********************************************************************************************************************/
