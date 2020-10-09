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
 *         \file  Fee_30_SmallSector_Layer3_ReadManagementBytes.h
 *        \brief  ReadManagementBytes is responsible for reading management information of passed instance.
 *
 *      \details  ReadManagementBytes is responsible for reading management information of passed instance.
 *                It distinguishes between two ways of reading. If the Flash driver provides a BlankCheck API, several
 *                blank checks are performed before reading. Otherwise the entire management information is read at once.
 *
 *********************************************************************************************************************/


#ifndef FEE_30_SMALLSECTOR_LAYER3_READ_MANAGEMENT_BYTES_H
# define FEE_30_SMALLSECTOR_LAYER3_READ_MANAGEMENT_BYTES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Fee_30_SmallSector.h"
# include "Fee_30_SmallSector_InstanceHandler.h"


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_Init()
 *********************************************************************************************************************/
/*! \brief       Initializes internal parameter of ReadManagementBytes sub-component
 *  \details     Initializes internal parameter of ReadManagementBytes sub-component
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_Init(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_GetStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current status of ReadManagementBytes sub-component
 * \details    Returns current status of ReadManagementBytes sub-component
 * \return     Status of ReadManagementBytes
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_GetStatus(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_GetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Returns current job result of ReadManagementBytes sub-component
 * \details    Returns current job result of ReadManagementBytes sub-component
 * \return     Job result of ReadManagementBytes
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_GetJobResult(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_StartJob()
 *********************************************************************************************************************/
/*!
 * \brief      Initiates ReadManagementBytes sub-component's state machine
 * \details    Initiates ReadManagementBytes sub-component's state machine and registers ReadManagementBytes
 *             sub-component to TaskManager
 * \param[in]  Instance
 * \param[in]  UserJobParameter
 * \return     E_OK: Job was accepted by ReadManagementBytes sub-component
 * \return     E_NOT_OK: Job request failed
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_StartJob(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_Execute()
 *********************************************************************************************************************/
/*!
 * \brief      Processes internal state machine
 * \details    Processes state machine of ReadManagementBytes sub-component
 * \pre        State machine is initialized.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_Execute(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_Cancel()
 *********************************************************************************************************************/
/*!
 * \brief      Cancels currently running job
 * \details    Cancels currently running job and resets all internal parameter
 * \pre        Sub-component is not idle.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_Cancel(void);

# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* FEE_30_SMALLSECTOR_LAYER3_READ_MANAGEMENT_BYTES_H */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Layer3_ReadManagementBytes.h
 *********************************************************************************************************************/
