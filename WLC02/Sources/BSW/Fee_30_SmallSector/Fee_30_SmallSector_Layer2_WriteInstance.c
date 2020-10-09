/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *        \file  Fee_30_SmallSector_Layer2_WriteInstance.c
 *        \brief  WriteInstance sub-component is responsible for writing an instance and verifying the written data.
 *
 *      \details  WriteInstance sub-component is responsible for writing an instance and verifying the written data,
 *                if configured. WriteInstance will write the user data to the instance object which is passed as
 *                input. Verification of written data can be enabled/disabled by pre-compile switch.
 *
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector_Layer2_WriteInstance.h"

#include "Fee_30_SmallSector_TaskManager.h"
#include "Fee_30_SmallSector_FlsCoordinator.h"

#include "Fee_30_SmallSector_DatasetHandler.h"
#include "Fee_30_SmallSector_BlockHandler.h"
#include "Fee_30_SmallSector_PartitionHandler.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define FEE_30_SMALLSECTOR_WRITE_INSTANCE_LAYER FEE_30_SMALLSECTOR_LAYER_TWO_INDEX

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#ifndef FEE_30_SMALLSECTOR_LOCAL /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL static
#endif

typedef enum
{
  FEE_30_SMALLSECTOR_WRINST_STATE_UNINIT = 0,
  FEE_30_SMALLSECTOR_WRINST_STATE_IDLE,
  FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_START_PATTERN,
  FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_START_PATTERN,
  FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_MGMT_PAGE,
  FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_MGMT_PAGE,
  FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_PAYLOAD,
  FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_PAYLOAD,
  FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_LAST_PAGE,
  FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_LAST_PAGE,
  FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_END_PATTERN,
  FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_END_PATTERN
} Fee_30_SmallSector_WrInst_StateType;

typedef struct
{
  MemIf_JobResultType JobResult;
  MemIf_StatusType Status;
  Fee_30_SmallSector_WrInst_StateType StateMachine;
} Fee_30_SmallSector_WrInst_ComponentParameterType;


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_WrInst_ComponentParameterType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_WrInst_ComponentParameter =
  { MEMIF_JOB_FAILED, MEMIF_UNINIT, FEE_30_SMALLSECTOR_WRINST_STATE_UNINIT };

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_Ih_CompareParameterType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_WrInst_CompareParameter;

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_Ih_InstanceType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_WrInst_Instance;

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_UserJobParameterType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_WrInst_UserJobParameter;

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_FinishJob()
 *********************************************************************************************************************/
/*!
 * \brief      Finishes currently processed job
 * \details    State and status are reset. WriteInstance sub-component is de-registered from TaskManager.
 * \param[in]  JobResult
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_FinishJob(MemIf_JobResultType JobResult);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_PrepareInstanceForWriting()
 *********************************************************************************************************************/
/*!
 * \brief      Prepares instance for writing
 * \details    Sets status and management value according to current job type
 * \param[in]  Instance
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_PrepareInstanceForWriting(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_InitiateVerifyState()
 *********************************************************************************************************************/
/*!
 * \brief      Initiates verification of recently written data
 * \details    Initiates verification of recently written data and switches to input state
 * \param[in]  nextState
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_InitiateVerifyState(Fee_30_SmallSector_WrInst_StateType nextState);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_StartManagementPageWrite()
 *********************************************************************************************************************/
/*!
 * \brief      Starts the write job of the management page
 * \details    Starts the write job of the page containing the management byte and some optional payload bytes
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_StartManagementPageWrite(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_InitiateNextWriteState()
 *********************************************************************************************************************/
/*!
 * \brief      Determines and initiates next write state
 * \details    Depending on instance length, either payload part is written or the static end pattern of the instance.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_InitiateNextWriteState(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_WriteLastPageOrEndPattern()
 *********************************************************************************************************************/
/*!
 * \brief      Determines and initiates next write state
 * \details    Depending on instance length, either the last page is written or the static end pattern of the instance.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_WriteLastPageOrEndPattern(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_StartEndPatternWrite()
 *********************************************************************************************************************/
/*!
 * \brief      Start the write job of the static end pattern
 * \details    Start the write job of the static end pattern
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_StartEndPatternWrite(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessIdleState()
 **********************************************************************************************************************/
/*!
 * \brief      Processes idle state of WriteInstance state machine
 * \details    Processes idle state of WriteInstance state machine
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateIdle(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateWriteStartPattern()
 **********************************************************************************************************************/
/*!
 * \brief      Processes WriteStartPattern state of WriteInstance state machine
 * \details    Processes WriteStartPattern state of WriteInstance state machine
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateWriteStartPattern(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateWriteManagementPage()
 **********************************************************************************************************************/
/*!
 * \brief      Processes WriteManagementPage state of WriteInstance state machine
 * \details    Processes WriteManagementPage state of WriteInstance state machine
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateWriteManagementPage(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateWritePayload()
 **********************************************************************************************************************/
/*!
 * \brief      Processes WritePayload state of WriteInstance state machine
 * \details    Processes WritePayload state of WriteInstance state machine
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateWritePayload(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateWriteLastPage()
 **********************************************************************************************************************/
/*!
 * \brief      Processes WriteLastPage state of WriteInstance state machine
 * \details    Processes WriteLastPage state of WriteInstance state machine
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateWriteLastPage(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateWriteEndPattern()
 **********************************************************************************************************************/
/*!
 * \brief      Processes WriteEndPattern state of WriteInstance state machine
 * \details    Processes WriteEndPattern state of WriteInstance state machine
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateWriteEndPattern(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateMachine()
 **********************************************************************************************************************/
/*!
 * \brief      Processes state machine of WriteInstance sub-component
 * \details    Processes state machine of WriteInstance sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateMachine(void);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_FinishJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_FinishJob(MemIf_JobResultType JobResult)
{
  /* #10 WriteInstance sub-component is de-registered from TaskManager */
  Fee_30_SmallSector_Tm_RemoveTask(Fee_30_SmallSector_WrInst_Execute, Fee_30_SmallSector_WrInst_Cancel, FEE_30_SMALLSECTOR_WRITE_INSTANCE_LAYER); /* SBSW_FEE_30_SMALLSECTOR_15 */

  /* #20 Reset internal parameters */
  Fee_30_SmallSector_WrInst_ComponentParameter.JobResult = JobResult;
  Fee_30_SmallSector_WrInst_ComponentParameter.Status = MEMIF_IDLE;
  Fee_30_SmallSector_WrInst_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WRINST_STATE_IDLE;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_PrepareInstanceForWriting()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_PrepareInstanceForWriting(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance)
{
  /* #10 Status depends on current job: Either a write job or a invalidate/erase job */
  if (Fee_30_SmallSector_WrInst_UserJobParameter.JobType == FEE_30_SMALLSECTOR_WRITE_JOB)
  {
      Fee_30_SmallSector_Ih_SetInstanceStatus(Instance, INSTANCE_STATUS_OK); /* SBSW_FEE_30_SMALLSECTOR_61 */
  }
  else
  {
    Fee_30_SmallSector_Ih_SetInstanceStatus(Instance, INSTANCE_STATUS_INVALID); /* SBSW_FEE_30_SMALLSECTOR_61 */
  }

  /* #20 Set instance's management value according to its status */
  Fee_30_SmallSector_Ih_SetManagementValuesAccordingToStatus(Instance); /* SBSW_FEE_30_SMALLSECTOR_61 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_InitiateVerifyState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_InitiateVerifyState(Fee_30_SmallSector_WrInst_StateType nextState)
{
  if (Fee_30_SmallSector_Ih_VerifyData(Fee_30_SmallSector_WrInst_CompareParameter) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_62 */
  {
    Fee_30_SmallSector_WrInst_ComponentParameter.StateMachine = nextState;
  }
  else
  {
    Fee_30_SmallSector_WrInst_FinishJob(MEMIF_JOB_FAILED);
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_StartManagementPageWrite()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_StartManagementPageWrite(void)
{
  if (Fee_30_SmallSector_Ih_WriteManagementPage(&Fee_30_SmallSector_WrInst_Instance, Fee_30_SmallSector_WrInst_UserJobParameter, &Fee_30_SmallSector_WrInst_CompareParameter) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_63 */
  {
    Fee_30_SmallSector_WrInst_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_MGMT_PAGE;
  }
  else
  {
    Fee_30_SmallSector_WrInst_FinishJob(MEMIF_JOB_FAILED);
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_InitiateNextWriteState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_InitiateNextWriteState(void)
{
  /* #10 Depending on length of instance's data there are three different ways to go on: */
  /* #11 DataLength <= PageSize - ManagementSize --> All data bytes were already written; continue with EndPattern */
  /* #12 PageSize - ManagementSize < DataLength <= (2 * PageSize) - ManagementSize --> Residual bytes can be written to last page; continue with LastPage */
  /* #13 DataLength > (2 * PageSize) - ManagementSize --> At least one payload page is necessary; continue with Payload */
  /* #14 Additionally, if current job is different to a write job (e.g. invalidate/erase job), just continue with static end pattern */

  uint16 PageSize = Fee_30_SmallSector_Ph_GetPartitionWriteAlignment();
  uint16 MgmtSize = (uint16) FEE_30_SMALLSECTOR_MANAGEMENT_SIZE;
  uint16 PayloadLength = Fee_30_SmallSector_Ih_GetInstanceDataLength(&Fee_30_SmallSector_WrInst_Instance); /* SBSW_FEE_30_SMALLSECTOR_64 */

  /* #20 CASE1: All data bytes were already written */
  if ((PayloadLength <= (PageSize - MgmtSize)) || (Fee_30_SmallSector_WrInst_UserJobParameter.JobType != FEE_30_SMALLSECTOR_WRITE_JOB))
  {
    /* #22 Start writing the static end pattern */
    Fee_30_SmallSector_WrInst_StartEndPatternWrite();
  }
  /* #30 CASE3: At least one payload page needs to be written */
  else if (PayloadLength > ((2u * PageSize) - MgmtSize))
  {
    /* #31 Start writing the payload pages */
    if (Fee_30_SmallSector_Ih_WritePayload(&Fee_30_SmallSector_WrInst_Instance, Fee_30_SmallSector_WrInst_UserJobParameter, &Fee_30_SmallSector_WrInst_CompareParameter) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_63 */
    {
      Fee_30_SmallSector_WrInst_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_PAYLOAD;
    }
    else
    {
      Fee_30_SmallSector_WrInst_FinishJob(MEMIF_JOB_FAILED);
    }
  }
  /* #40 CASE2: Last page is sufficient for writing the remaining bytes */
  else
  {
    /* #41 Start writing the last page */
    if (Fee_30_SmallSector_Ih_WriteLastPage(&Fee_30_SmallSector_WrInst_Instance, Fee_30_SmallSector_WrInst_UserJobParameter, &Fee_30_SmallSector_WrInst_CompareParameter) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_63 */
    {
      Fee_30_SmallSector_WrInst_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_LAST_PAGE;
    }
    else
    {
      Fee_30_SmallSector_WrInst_FinishJob(MEMIF_JOB_FAILED);
    }
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_WriteLastPageOrEndPattern()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_WriteLastPageOrEndPattern(void)
{
  /* #10 Check if already entire payload was written or if there are still some bytes left, which need to be written to the last page */
  /* #11 Instance's with: [ (DataLength + MgmtSize) % PageSize != 0 ] need to write the last page separately */
  if (Fee_30_SmallSector_Ih_IsLastPageNecessary(&Fee_30_SmallSector_WrInst_Instance) == TRUE) /* SBSW_FEE_30_SMALLSECTOR_63 */
  {
    /* #20 Start writing the last page containing payload */
    if (Fee_30_SmallSector_Ih_WriteLastPage(&Fee_30_SmallSector_WrInst_Instance, Fee_30_SmallSector_WrInst_UserJobParameter, &Fee_30_SmallSector_WrInst_CompareParameter) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_63 */
    {
      Fee_30_SmallSector_WrInst_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_LAST_PAGE;
    }
    else
    {
      Fee_30_SmallSector_WrInst_FinishJob(MEMIF_JOB_FAILED);
    }
  }
  else
  {
    /* #30 Start writing the static end pattern */
    Fee_30_SmallSector_WrInst_StartEndPatternWrite();
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_StartEndPatternWrite()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_StartEndPatternWrite(void)
{
  if (Fee_30_SmallSector_Ih_WriteEndPattern(&Fee_30_SmallSector_WrInst_Instance, &Fee_30_SmallSector_WrInst_CompareParameter) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_63 */
  {
    Fee_30_SmallSector_WrInst_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_END_PATTERN;
  }
  else
  {
    Fee_30_SmallSector_WrInst_FinishJob(MEMIF_JOB_FAILED);
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateIdle()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateIdle(void)
{
  /* #10 Prepare instance properties for upcoming write job */
  Fee_30_SmallSector_WrInst_PrepareInstanceForWriting(&Fee_30_SmallSector_WrInst_Instance); /* SBSW_FEE_30_SMALLSECTOR_64 */

  /* #20 The first step is to write the static pattern to the first page of the instance */
  if (Fee_30_SmallSector_Ih_WriteStartPattern(&Fee_30_SmallSector_WrInst_Instance, &Fee_30_SmallSector_WrInst_CompareParameter) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_63 */
  {
    Fee_30_SmallSector_WrInst_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_START_PATTERN;
  }
  else
  {
    Fee_30_SmallSector_WrInst_FinishJob(MEMIF_JOB_FAILED);
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateWriteStartPattern()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateWriteStartPattern(void)
{
  /* #10 Flash finished writing the start pattern */
  if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
  {
    /* #20 Depending on configuration, either the recently written start pattern is verified or the next part is written */
    if (Fee_30_SmallSector_Bh_HasVerificationEnabled() == TRUE)
    {
      Fee_30_SmallSector_WrInst_InitiateVerifyState(FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_START_PATTERN);
    }
    else
    {
      Fee_30_SmallSector_WrInst_StartManagementPageWrite();
    }
  }
  else
  {
    Fee_30_SmallSector_WrInst_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateWriteManagementPage()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateWriteManagementPage(void)
{
  /* #10 Flash finished writing the management page */
  if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
  {
    /* #20 Depending on configuration, either the recently written management page is verified or the next part is written */
    if (Fee_30_SmallSector_Bh_HasVerificationEnabled() == TRUE)
    {
      Fee_30_SmallSector_WrInst_InitiateVerifyState(FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_MGMT_PAGE);
    }
    else
    {
      Fee_30_SmallSector_WrInst_InitiateNextWriteState();
    }
  }
  else
  {
    Fee_30_SmallSector_WrInst_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateWritePayload()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateWritePayload(void)
{
  /* #10 Flash finished writing the payload pages */
  if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
  {
    /* #20 Depending on configuration, either the recently written data is verified or the next part is written */
    if (Fee_30_SmallSector_Bh_HasVerificationEnabled() == TRUE)
    {
      Fee_30_SmallSector_WrInst_InitiateVerifyState(FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_PAYLOAD);
    }
    else
    {
      /* #30 Start either writing the last page or writing the end pattern */
      Fee_30_SmallSector_WrInst_WriteLastPageOrEndPattern();
    }
  }
  else
  {
    Fee_30_SmallSector_WrInst_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateWriteLastPage()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateWriteLastPage(void)
{
  /* #10 Flash finished writing the payload pages */
  if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
  {
    /* #20 Depending on configuration, either the recently written data is verified or the next part is written */
    if (Fee_30_SmallSector_Bh_HasVerificationEnabled() == TRUE)
    {
      Fee_30_SmallSector_WrInst_InitiateVerifyState(FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_LAST_PAGE);
    }
    else
    {
      /* #30 Start writing the end pattern */
      Fee_30_SmallSector_WrInst_StartEndPatternWrite();
    }
  }
  else
  {
    Fee_30_SmallSector_WrInst_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateWriteEndPattern()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateWriteEndPattern(void)
{
  /* #10 Flash finished writing the static end pattern */
  if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
  {
    /* #20 Depending on configuration, either the recently written static end pattern is verified or the job is finished */
    if (Fee_30_SmallSector_Bh_HasVerificationEnabled() == TRUE)
    {
      Fee_30_SmallSector_WrInst_InitiateVerifyState(FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_END_PATTERN);
    }
    else
    {
      Fee_30_SmallSector_WrInst_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
    }
  }
  else
  {
    Fee_30_SmallSector_WrInst_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_WrInst_ProcessStateMachine()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_WrInst_ProcessStateMachine(void)
{
  switch (Fee_30_SmallSector_WrInst_ComponentParameter.StateMachine)
  {
      /*** ---------------- IDLE -------------------------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WRINST_STATE_IDLE:
      Fee_30_SmallSector_WrInst_ProcessStateIdle();
      break;
      /*** -------------- WRITE START PATTERN ------------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_START_PATTERN:
      Fee_30_SmallSector_WrInst_ProcessStateWriteStartPattern();
      break;
      /*** -------------- VERIFY START PATTERN ------------------------------------------------------------ ***/
    case FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_START_PATTERN:
      if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
      {
        Fee_30_SmallSector_WrInst_StartManagementPageWrite();
      }
      else
      {
        Fee_30_SmallSector_WrInst_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
      }
      break;
      /*** -------------- WRITE MANAGEMENT PAGE ----------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_MGMT_PAGE:
      Fee_30_SmallSector_WrInst_ProcessStateWriteManagementPage();
      break;
      /*** -------------- VERIFY MANAGEMENT PAGE ---------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_MGMT_PAGE:
      if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
      {
        Fee_30_SmallSector_WrInst_InitiateNextWriteState();
      }
      else
      {
        Fee_30_SmallSector_WrInst_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
      }
      break;
      /*** -------------- WRITE REMAINING PAYLOAD---------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_PAYLOAD:
      Fee_30_SmallSector_WrInst_ProcessStateWritePayload();
      break;
      /*** -------------- VERIFY REMAINING PAYLOAD -------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_PAYLOAD:
      if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
      {
        Fee_30_SmallSector_WrInst_WriteLastPageOrEndPattern();
      }
      else
      {
        Fee_30_SmallSector_WrInst_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
      }
      break;
      /*** -------------- WRITE LAST PAGE ----------------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_LAST_PAGE:
      Fee_30_SmallSector_WrInst_ProcessStateWriteLastPage();
      break;
      /*** -------------- VERIFY LAST PAGE ---------------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_LAST_PAGE:
      if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
      {
        Fee_30_SmallSector_WrInst_StartEndPatternWrite();
      }
      else
      {
        Fee_30_SmallSector_WrInst_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
      }
      break;
      /*** -------------- WRITE END PATTERN --------------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WRINST_STATE_WRITE_END_PATTERN:
      Fee_30_SmallSector_WrInst_ProcessStateWriteEndPattern();
      break;
      /*** -------------- VERIFY END PATTERN -------------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WRINST_STATE_VERIFY_END_PATTERN:
        Fee_30_SmallSector_WrInst_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
      break;

    default:
      Fee_30_SmallSector_WrInst_FinishJob(MEMIF_JOB_FAILED);
      break;
  }
} /* PRQA S 6050, 6030 */ /* MD_MSR_STCAL, MD_MSR_STCYC */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_Init(void)
{
  Fee_30_SmallSector_WrInst_ComponentParameter.Status = MEMIF_IDLE;
  Fee_30_SmallSector_WrInst_ComponentParameter.JobResult = MEMIF_JOB_OK;

  Fee_30_SmallSector_WrInst_CompareParameter.Fee_30_SmallSector_Ih_CompareAddress = 0x0000U;
  Fee_30_SmallSector_WrInst_CompareParameter.Fee_30_SmallSector_Ih_CompareBufferPtr = NULL_PTR;
  Fee_30_SmallSector_WrInst_CompareParameter.Fee_30_SmallSector_Ih_CompareLength = 0x0000U;

  Fee_30_SmallSector_Ih_InitInstance(&Fee_30_SmallSector_WrInst_Instance); /* SBSW_FEE_30_SMALLSECTOR_64 */

  Fee_30_SmallSector_WrInst_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WRINST_STATE_IDLE;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_GetStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_GetStatus(void)
{
  return Fee_30_SmallSector_WrInst_ComponentParameter.Status;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_GetJobResult(void)
{
  return Fee_30_SmallSector_WrInst_ComponentParameter.JobResult;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_StartJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_StartJob(Fee_30_SmallSector_Ih_InstanceType Instance,
        Fee_30_SmallSector_UserJobParameterType UserJobParameter)
{
  Std_ReturnType retVal;
  /* #10 Requested job is only accepted if sub-component's state machine is idle */
  if (Fee_30_SmallSector_WrInst_ComponentParameter.StateMachine == FEE_30_SMALLSECTOR_WRINST_STATE_IDLE)
  {
    /* #20 WriteInstance registers its execution and cancel service to TaskManager */
    retVal = Fee_30_SmallSector_Tm_AddTask(Fee_30_SmallSector_WrInst_Execute, Fee_30_SmallSector_WrInst_Cancel, FEE_30_SMALLSECTOR_WRITE_INSTANCE_LAYER); /* SBSW_FEE_30_SMALLSECTOR_14 */

    if (retVal == E_OK)
    {
      Fee_30_SmallSector_WrInst_ComponentParameter.Status = MEMIF_BUSY;
      Fee_30_SmallSector_WrInst_ComponentParameter.JobResult = MEMIF_JOB_PENDING;

      Fee_30_SmallSector_WrInst_Instance = Instance;
      Fee_30_SmallSector_WrInst_UserJobParameter = UserJobParameter;
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_Execute()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_Execute(void)
{
  /* #10 State machine is only processed if WriteInstance sub-component's status is busy */
  if (Fee_30_SmallSector_WrInst_ComponentParameter.Status == MEMIF_BUSY)
  {
    Fee_30_SmallSector_WrInst_ProcessStateMachine();
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_WrInst_Cancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_WrInst_Cancel(void)
{
  Fee_30_SmallSector_WrInst_FinishJob(MEMIF_JOB_CANCELED);
}

#define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA L:LongInfixName */

/* SBSW_JUSTIFICATION_BEGIN
    \ID SBSW_FEE_30_SMALLSECTOR_61
      \DESCRIPTION Function is called with pointer to an instance object
      \COUNTERMEASURE \N Caller ensures that pointer passed to service is valid

    \ID SBSW_FEE_30_SMALLSECTOR_62
      \DESCRIPTION Function is called with local structure Fee_30_SmallSector_WrInst_CompareParameter, which contains a pointer to data buffer.
      \COUNTERMEASURE \N Function is always called after valid reference was assigned to pointer parameter. Test cases within WriteInstance ensure
                         that state machine of Fee_30_SmallSector_Layer2_WriteInstance works accordingly.

    \ID SBSW_FEE_30_SMALLSECTOR_63
      \DESCRIPTION Function is called with local structure Fee_30_SmallSector_WrInst_UserJobParameter, which contains a pointer to data buffer. Function is also called
                   with a reference to local instance Fee_30_SmallSector_WrInst_Instance and with a local structure Fee_30_SmallSector_WrInst_CompareParameter, which contains a pointer
                   to a data buffer.
      \COUNTERMEASURE \N Fee_30_SmallSector_WrInst_UserJobParameter is initialized with input parameter of function Fee_30_SmallSector_WrInst_StartJob, which is invoked upon start
                         of Fee_30_SmallSector_Layer2_WriteInstance sub-component. Thus caller ensures pointer to be valid.
                         Reference to local parameter Fee_30_SmallSector_WrInst_Instance is always valid.
                         Fee_30_SmallSector_WrInst_CompareParameter structure is initialized within called service. Therefore this service assures that content of
                         Fee_30_SmallSector_WrInst_CompareParameter is valid.

    \ID SBSW_FEE_30_SMALLSECTOR_64
      \DESCRIPTION Function is called with reference to local parameter Fee_30_SmallSector_WrInst_Instance
      \COUNTERMEASURE \N Fee_30_SmallSector_WrInst_Instance is a local parameter, thus references to this parameter are valid.

SBSW_JUSTIFICATION_END */


/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Layer2_WriteInstance.c
 *********************************************************************************************************************/
