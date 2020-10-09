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
 *         \file  Fee_30_SmallSector_Layer3_ReadManagementBytes.c
 *        \brief  ReadManagementBytes is responsible for reading both header and trailer information of passed instance.
 *
 *      \details  ReadManagementBytes is responsible for reading management information of passed instance.
 *                It distinguishes between two ways of reading. If the Flash driver provides a BlankCheck API, several
 *                blank checks are performed before reading. Otherwise the entire management information is read at once.
 *
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector_Layer3_ReadManagementBytes.h"

#include "Fee_30_SmallSector_TaskManager.h"
#include "Fee_30_SmallSector_FlsCoordinator.h"

#include "Fee_30_SmallSector_PartitionHandler.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define FEE_30_SMALLSECTOR_READ_MANAGEMENT_BYTES_LAYER FEE_30_SMALLSECTOR_LAYER_THREE_INDEX

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#ifndef FEE_30_SMALLSECTOR_LOCAL /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL static
#endif

typedef enum
{
  FEE_30_SMALLSECTOR_RDMGMT_STATE_UNINIT = 0,
  FEE_30_SMALLSECTOR_RDMGMT_STATE_IDLE,
  FEE_30_SMALLSECTOR_RDMGMT_STATE_WAIT_FOR_BLANKCHECK_START,
  FEE_30_SMALLSECTOR_RDMGMT_STATE_WAIT_FOR_BLANKCHECK_END,
  FEE_30_SMALLSECTOR_RDMGMT_STATE_WAIT_FOR_READ_ALL
} Fee_30_SmallSector_RdMgmt_StateType;

typedef struct
{
  MemIf_JobResultType JobResult;
  MemIf_StatusType Status;
  Fee_30_SmallSector_RdMgmt_StateType StateMachine;
} Fee_30_SmallSector_RdMgmt_ComponentParameterType;


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_RdMgmt_ComponentParameterType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_RdMgmt_ComponentParameter =
  { MEMIF_JOB_FAILED, MEMIF_UNINIT, FEE_30_SMALLSECTOR_RDMGMT_STATE_UNINIT };

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL P2VAR(Fee_30_SmallSector_Ih_InstanceType, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_RdMgmt_Instance;

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_FinishJob()
 *********************************************************************************************************************/
/*!
 * \brief      Finishes currently processed job
 * \details    State and status are reset. ReadManagementBytes sub-component is de-registered from TaskManager.
 * \param[in]  JobResult
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_FinishJob(MemIf_JobResultType JobResult);

/**********************************************************************************************************************
 Fee_30_SmallSector_RdMgmt_ProcessIdleState()
 **********************************************************************************************************************/
/*!
 * \brief      Processes idle state of ReadManagementBytes sub-component
 * \details    Processes idle state of ReadManagementBytes sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_ProcessIdleState(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_RdMgmt_ProcessWaitForStartBlankCheckState()
 **********************************************************************************************************************/
/*!
 * \brief      Processes WaitForBlankCheck of StartPattern state of ReadManagementBytes sub-component
 * \details    Processes WaitForBlankCheck of StartPattern state of ReadManagementBytes sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_ProcessWaitForStartBlankCheckState(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_RdMgmt_ProcessWaitForEndBlankCheckState()
 **********************************************************************************************************************/
/*!
 * \brief      Processes WaitForBlankCheck of EndPattern state of ReadManagementBytes sub-component
 * \details    Processes WaitForBlankCheck of EndPattern state of ReadManagementBytes sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_ProcessWaitForEndBlankCheckState(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_RdMgmt_ProcessWaitForReadAllState()
 **********************************************************************************************************************/
/*!
 * \brief      Processes WaitForReadAll state of ReadManagementBytes sub-component
 * \details    Processes WaitForReadAll state of ReadManagementBytes sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_ProcessWaitForReadAllState(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_RdMgmt_ProcessStateMachine()
 **********************************************************************************************************************/
/*!
 * \brief      Processes state machine of ReadManagementBytes sub-component
 * \details    Processes state machine of ReadManagementBytes sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_ProcessStateMachine(void);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_FinishJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_FinishJob(MemIf_JobResultType JobResult)
{
  /* #10 ReadManagementByte sub-component is de-registered from TaskManager */
  Fee_30_SmallSector_Tm_RemoveTask(Fee_30_SmallSector_RdMgmt_Execute, Fee_30_SmallSector_RdMgmt_Cancel, FEE_30_SMALLSECTOR_READ_MANAGEMENT_BYTES_LAYER); /* SBSW_FEE_30_SMALLSECTOR_15 */

  /* #20 Reset internal parameters */
  Fee_30_SmallSector_RdMgmt_ComponentParameter.JobResult = JobResult;
  Fee_30_SmallSector_RdMgmt_ComponentParameter.Status = MEMIF_IDLE;
  Fee_30_SmallSector_RdMgmt_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_RDMGMT_STATE_IDLE;
}

/**********************************************************************************************************************
 Fee_30_SmallSector_RdMgmt_ProcessIdleState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_ProcessIdleState(void)
{
  /* #5 Initialize relevant instance information */
  Fee_30_SmallSector_Ih_SetWP1State(Fee_30_SmallSector_RdMgmt_Instance, FEE_30_SMALLSECTOR_PATTERN_INIT); /* SBSW_FEE_30_SMALLSECTOR_51 */
  Fee_30_SmallSector_Ih_SetWP2State(Fee_30_SmallSector_RdMgmt_Instance, FEE_30_SMALLSECTOR_PATTERN_INIT); /* SBSW_FEE_30_SMALLSECTOR_51 */

  /* #10 Check if FLS module referenced by current instance provides a BlankCheck API */
  if (Fee_30_SmallSector_Ph_GetBlankCheckApi() == TRUE)
  {
    /* #20 Perform BlankCheck on first write pattern */
    if (Fee_30_SmallSector_Ih_BlankCheckStartPattern(Fee_30_SmallSector_RdMgmt_Instance) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_51 */
    {
      Fee_30_SmallSector_RdMgmt_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_RDMGMT_STATE_WAIT_FOR_BLANKCHECK_START;
    }
    else
    {
      Fee_30_SmallSector_RdMgmt_FinishJob(MEMIF_JOB_FAILED);
    }
  }
  else
  {
    /* #30 Read both write patterns and Management info byte */
    if (Fee_30_SmallSector_Ih_ReadAllMgmt(Fee_30_SmallSector_RdMgmt_Instance) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_51 */
    {
      Fee_30_SmallSector_RdMgmt_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_RDMGMT_STATE_WAIT_FOR_READ_ALL;
    }
    else
    {
      Fee_30_SmallSector_RdMgmt_FinishJob(MEMIF_JOB_FAILED);
    }
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_RdMgmt_ProcessWaitForStartBlankCheckState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_ProcessWaitForStartBlankCheckState(void)
{
  if (Fee_30_SmallSector_Fls_GetJobResult() != MEMIF_JOB_FAILED){
    /* #10 First write pattern of instance was successfully checked. State of the page depends on JobResult */
    /* #11 If BlankCheck returns with MEMIF_JOB_OK, StartPattern's state is set to BLANK */
    if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
    {
      /* #20 State of write pattern is set to "BLANK" */
      Fee_30_SmallSector_Ih_SetWP1State(Fee_30_SmallSector_RdMgmt_Instance, FEE_30_SMALLSECTOR_PATTERN_BLANK); /* SBSW_FEE_30_SMALLSECTOR_51 */
    }
    else
    {
      /* #30 State of write pattern is set to "INCONSISTENT" because it's verified to be not blank, but it's not sure that the value is correct */
      Fee_30_SmallSector_Ih_SetWP1State(Fee_30_SmallSector_RdMgmt_Instance, FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT); /* SBSW_FEE_30_SMALLSECTOR_51 */
    }

    /* #40 Perform blank check on second write pattern */
    if (Fee_30_SmallSector_Ih_BlankCheckEndPattern(Fee_30_SmallSector_RdMgmt_Instance) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_51 */
    {
      Fee_30_SmallSector_RdMgmt_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_RDMGMT_STATE_WAIT_FOR_BLANKCHECK_END;
    }
    else
    {
      Fee_30_SmallSector_RdMgmt_FinishJob(MEMIF_JOB_FAILED);
    }
  }
  else
  {
    Fee_30_SmallSector_RdMgmt_FinishJob(MEMIF_JOB_FAILED);
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_RdMgmt_ProcessWaitForEndBlankCheckState()
 **********************************************************************************************************************/
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
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_ProcessWaitForEndBlankCheckState(void)
{
  boolean IsWp1Inconsistent;
  boolean IsWp2Inconsistent;
  if (Fee_30_SmallSector_Fls_GetJobResult() != MEMIF_JOB_FAILED)
  {
    /* #10 Second write pattern of instance was successfully checked. State of the page depends on job result */
    /* #11 If BlankCheck returns with MEMIF_JOB_OK, EndPattern's state is set to BLANK */
    if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
    {
      Fee_30_SmallSector_Ih_SetWP2State(Fee_30_SmallSector_RdMgmt_Instance, FEE_30_SMALLSECTOR_PATTERN_BLANK); /* SBSW_FEE_30_SMALLSECTOR_51 */
    }
    else
    {
      /* #20 State of write pattern is set to "INCONSISTENT" because it's verified to be not blank, but it's not sure that the value is correct */
      Fee_30_SmallSector_Ih_SetWP2State(Fee_30_SmallSector_RdMgmt_Instance, FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT); /* SBSW_FEE_30_SMALLSECTOR_51 */
    }
    IsWp1Inconsistent = (boolean) (Fee_30_SmallSector_Ih_GetWP1State(Fee_30_SmallSector_RdMgmt_Instance) == FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT); /* SBSW_FEE_30_SMALLSECTOR_51 */
    IsWp2Inconsistent = (boolean) (Fee_30_SmallSector_Ih_GetWP2State(Fee_30_SmallSector_RdMgmt_Instance) == FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT); /* SBSW_FEE_30_SMALLSECTOR_51 */
    /* #30 Perform read of management information in case one of the write pattern pages is not blank */
    /* #31 Only if both patterns are blank, it is assumed that the instance is either erased or blank */
    /* #32 Due to hardware properties it may happen that the second write pattern seems to be blank although it was written some time ago */
    if (IsWp1Inconsistent || IsWp2Inconsistent)
    {
      /* #33 Read both write patterns and Management info byte */
      if (Fee_30_SmallSector_Ih_ReadAllMgmt(Fee_30_SmallSector_RdMgmt_Instance) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_51 */
      {
        Fee_30_SmallSector_RdMgmt_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_RDMGMT_STATE_WAIT_FOR_READ_ALL;
      }
      else
      {
        Fee_30_SmallSector_RdMgmt_FinishJob(MEMIF_JOB_FAILED);
      }
    }
    else
    {
      /* #40 Return successfully, because BlankChecks were performed successfully and it's not necessary to read any management information */
      Fee_30_SmallSector_RdMgmt_FinishJob(MEMIF_JOB_OK);
    }
  }
  else
  {
    Fee_30_SmallSector_RdMgmt_FinishJob(MEMIF_JOB_FAILED);
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_RdMgmt_ProcessWaitForReadAllState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_ProcessWaitForReadAllState(void)
{
  if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
  {
    /* #10 Set state of first write pattern according to buffer content */
    Fee_30_SmallSector_Ih_SetWP1State(Fee_30_SmallSector_RdMgmt_Instance, Fee_30_SmallSector_Ih_GetStartPatternFromBuffer(Fee_30_SmallSector_RdMgmt_Instance)); /* SBSW_FEE_30_SMALLSECTOR_51 */ /* SBSW_FEE_30_SMALLSECTOR_51 */

    /* #20 Set state of second write pattern according to buffer content */
    Fee_30_SmallSector_Ih_SetWP2State(Fee_30_SmallSector_RdMgmt_Instance, Fee_30_SmallSector_Ih_GetEndPatternFromBuffer(Fee_30_SmallSector_RdMgmt_Instance)); /* SBSW_FEE_30_SMALLSECTOR_51 */ /* SBSW_FEE_30_SMALLSECTOR_51 */

    /* #30 Management information was read successfully. Store it to instance object */
    Fee_30_SmallSector_Ih_StoreMgmtValueFromBuffer(Fee_30_SmallSector_RdMgmt_Instance); /* SBSW_FEE_30_SMALLSECTOR_51 */

    /* #40 Perform single bit flip correction if enabled */
#   if (FEE_30_SMALLSECTOR_CORRECT_SINGLE_BIT_FLIPS == STD_ON)
    Fee_30_SmallSector_Ih_CorrectSingleBitFlips(&(Fee_30_SmallSector_RdMgmt_Instance)->MgmtValue); /* SBSW_FEE_30_SMALLSECTOR_51 */
#   endif
  }
  else
  {
    /* #50 In case of read error set all page states to inconsistent, so that instance is marked as inconsistent */
    Fee_30_SmallSector_Ih_SetWP1State(Fee_30_SmallSector_RdMgmt_Instance, FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT); /* SBSW_FEE_30_SMALLSECTOR_51 */
    Fee_30_SmallSector_Ih_SetWP2State(Fee_30_SmallSector_RdMgmt_Instance, FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT); /* SBSW_FEE_30_SMALLSECTOR_51 */
  }

  /* #60 Finish ReadManagement job with successful result in every case, because read errors at management entities shall not lead to an abort (ESCAN00097748)*/
  Fee_30_SmallSector_RdMgmt_FinishJob(MEMIF_JOB_OK);
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 Fee_30_SmallSector_RdMgmt_ProcessStateMachine()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_RdMgmt_ProcessStateMachine(void)
{
  switch (Fee_30_SmallSector_RdMgmt_ComponentParameter.StateMachine)
  {
    /*** -------------- IDLE -------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_RDMGMT_STATE_IDLE:

      Fee_30_SmallSector_RdMgmt_ProcessIdleState();
      break;

    /*** -------------- WAIT FOR BLANK CHECK OF START PATTERN ----------------------------- ***/
    case FEE_30_SMALLSECTOR_RDMGMT_STATE_WAIT_FOR_BLANKCHECK_START:

      Fee_30_SmallSector_RdMgmt_ProcessWaitForStartBlankCheckState();
      break;

      /*** -------------- WAIT FOR BLANK CHECK OF END PATTERN ----------------------------- ***/
    case FEE_30_SMALLSECTOR_RDMGMT_STATE_WAIT_FOR_BLANKCHECK_END:

      Fee_30_SmallSector_RdMgmt_ProcessWaitForEndBlankCheckState();
      break;

      /*** -------------- WAIT FOR READ ALL ----------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_RDMGMT_STATE_WAIT_FOR_READ_ALL:

      Fee_30_SmallSector_RdMgmt_ProcessWaitForReadAllState();
      break;

    default:
      Fee_30_SmallSector_RdMgmt_FinishJob(MEMIF_JOB_FAILED);
      break;
  }
}


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_Init(void)
{
  Fee_30_SmallSector_RdMgmt_ComponentParameter.Status = MEMIF_IDLE;
  Fee_30_SmallSector_RdMgmt_ComponentParameter.JobResult = MEMIF_JOB_OK;

  Fee_30_SmallSector_RdMgmt_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_RDMGMT_STATE_IDLE;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_GetStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_GetStatus(void)
{
  return Fee_30_SmallSector_RdMgmt_ComponentParameter.Status;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_GetJobResult(void)
{
  return Fee_30_SmallSector_RdMgmt_ComponentParameter.JobResult;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_StartJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_StartJob(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance)
{
  Std_ReturnType retVal;

  /* #10 Requested job is only accepted if sub-component's state machine is idle */
  if (Fee_30_SmallSector_RdMgmt_ComponentParameter.StateMachine == FEE_30_SMALLSECTOR_RDMGMT_STATE_IDLE)
  {
    /* #20 ReadManagementByte sub-component registers its execution and cancel service to TaskManager */
    retVal = Fee_30_SmallSector_Tm_AddTask(Fee_30_SmallSector_RdMgmt_Execute, Fee_30_SmallSector_RdMgmt_Cancel, FEE_30_SMALLSECTOR_READ_MANAGEMENT_BYTES_LAYER); /* SBSW_FEE_30_SMALLSECTOR_14 */

    if (retVal == E_OK)
    {
      Fee_30_SmallSector_RdMgmt_ComponentParameter.Status = MEMIF_BUSY;
      Fee_30_SmallSector_RdMgmt_ComponentParameter.JobResult = MEMIF_JOB_PENDING;

      Fee_30_SmallSector_RdMgmt_Instance = Instance;
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_Execute()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_Execute(void)
{
  /* #10 ReadManagementByte sub-component's state machine is only processed if status is busy */
  if (Fee_30_SmallSector_RdMgmt_ComponentParameter.Status == MEMIF_BUSY)
  {
    Fee_30_SmallSector_RdMgmt_ProcessStateMachine();
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_RdMgmt_Cancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_RdMgmt_Cancel(void)
{
  Fee_30_SmallSector_RdMgmt_FinishJob(MEMIF_JOB_CANCELED);
}

#define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA L:LongInfixName */

/* SBSW_JUSTIFICATION_BEGIN

   \ID SBSW_FEE_30_SMALLSECTOR_51
    \DESCRIPTION Local pointer to an instance object of type Fee_30_SmallSector_Ih_InstanceType is accessed.
    \COUNTERMEASURE \N Local pointer is initialized with reference to an instance object upon invoking Fee_30_SmallSector_Layer3_ReadManagementBytes job. Reference
                       is assigned to local pointer in Fee_30_SmallSector_RdMgmt_StartJob() service. Thus caller ensures that the pointer passed to this sub-component
                       is valid.

SBSW_JUSTIFICATION_END */


/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Layer3_ReadManagementBytes.c
 *********************************************************************************************************************/
