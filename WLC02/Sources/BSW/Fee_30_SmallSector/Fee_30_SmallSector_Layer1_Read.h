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
 *        \file  Fee_30_SmallSector_Layer1_Read.h
 *        \brief  This sub-component of FEE module is processing read jobs
 *
 *      \details  FeeRead sub-component is responsible for processing read jobs. Upon job request it registers itself
 *                to TaskManager and after finishing the job, it de-registers itself from TaskManager. To process the
 *                internal state machine, sub-component InstanceFinder is used to find most recent data.
 *
 *********************************************************************************************************************/


#ifndef FEE_30_SMALLSECTOR_LAYER1_READ_H
# define FEE_30_SMALLSECTOR_LAYER1_READ_H

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
 *  Fee_30_SmallSector_Rd_Init()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes internal parameters of FeeRead sub-component
 * \details    Initializes internal parameters of FeeRead sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_Init(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Rd_GetStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current status of FeeRead sub-component
 * \details    Returns current status of FeeRead sub-component
 * \return     Sub-component's status
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_GetStatus(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Rd_GetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current job result of FeeRead sub-component
 * \details    Returns current job result of FeeRead sub-component
 * \return     Returns job result of recent read job
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_GetJobResult(void);


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Rd_StartJob()
 *********************************************************************************************************************/
/*!
 * \brief      Initiates FeeRead sub-component's state machine
 * \details    Initiates FeeRead sub-component's state machine and registers FeeRead sub-component to TaskManager
 * \param[in]  Fee_30_SmallSector_UserJobParameter
 * \return     E_OK: Job was accepted by FeeRead sub-component
 * \return     E_NOT_OK: Job request failed
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_StartJob(Fee_30_SmallSector_UserJobParameterType Fee_30_SmallSector_UserJobParameter);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Rd_Execute()
 *********************************************************************************************************************/
/*!
 * \brief      Processes internal state machine
 * \details    Processes state machine of FeeRead sub-component
 * \pre        State machine is initialized.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_Execute(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Rd_Cancel()
 *********************************************************************************************************************/
/*!
 * \brief      Cancels currently running job
 * \details    Cancels currently running job and resets all internal parameter
 * \pre        Sub-component is not idle.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_Cancel(void);



# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* FEE_30_SMALLSECTOR_LAYER1_READ_H */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Layer1_Read.h
 *********************************************************************************************************************/
