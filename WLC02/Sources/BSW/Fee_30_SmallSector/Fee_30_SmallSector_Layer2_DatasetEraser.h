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
 *         \file  Fee_30_SmallSector_Layer2_DatasetEraser.h
 *        \brief  DatasetEraser sub-component is responsible for erasing all physical flash sectors of one FEE dataset.
 *
 *      \details  DatasetEraser starts the erase procedure by writing a static pattern to the first page of a dataset,
 *                which is reserved for this case. If a dataset consists of more than one flash sector, these sectors
 *                are erased in reverse order, so that the sector containing the erase pattern is erased last.
 *
 *********************************************************************************************************************/


#ifndef FEE_30_SMALLSECTOR_LAYER2_DATASET_ERASER_H
# define FEE_30_SMALLSECTOR_LAYER2_DATASET_ERASER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector.h"
#include "Fee_30_SmallSector_DatasetHandler.h"
#include "Fee_30_SmallSector_Layer2_InstanceFinder.h" /* Include is necessary for InstanceFinder Result Type */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_Init()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes internal parameter of DatasetEraser sub-component
 * \details    Initializes internal parameter of DatasetEraser sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_Init(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_GetStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current status of DatasetEraser sub-component
 * \details    Returns current status of DatasetEraser sub-component
 * \return     Status of DatasetEraser
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_GetStatus(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_GetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current job result of DatasetEraser sub-component
 * \details    Returns current job result of DatasetEraser sub-component
 * \return     Job result of DatasetEraser
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_GetJobResult(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_StartJob()
 *********************************************************************************************************************/
/*!
 * \brief      Initiates DatasetEraser sub-component's state machine
 * \details    Initiates DatasetEraser sub-component's state machine and registers DatasetEraser sub-component to TaskManager
 * \param[in]  InstanceFinderResult
 * \return     E_OK: Job was accepted by DatasetEraser sub-component
 * \return     E_NOT_OK: Job request failed
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_StartJob(Fee_30_SmallSector_If_ResultType InstanceFinderResult);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_Execute()
 *********************************************************************************************************************/
/*!
 * \brief      Processes internal state machine
 * \details    Processes state machine of DatasetEraser sub-component
 * \pre        State machine is initialized.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_Execute(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_Cancel()
 *********************************************************************************************************************/
/*!
 * \brief      Cancels currently running job
 * \details    Cancels currently running job and resets all internal parameter
 * \pre        Sub-component is not idle.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_Cancel(void);


# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* FEE_30_SMALLSECTOR_LAYER2_DATASET_ERASER_H */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Layer2_DatasetEraser.h
 *********************************************************************************************************************/
