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
 *        \file  Fee_30_SmallSector_Layer1_Write.c
 *        \brief  This sub-component of FEE module is processing write jobs
 *
 *      \details  FeeWrite sub-component is responsible for writing data from a DataBufferPtr to Flash. Destination in
 *                Flash is specified by passed BlockNumber. Internally, InstanceFinder is used to find most recent write
 *                destination and WriteInstance is used to perform the write job on the determined instance object.
 *
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector_Layer1_Write.h"
#include "Fee_30_SmallSector_Layer2_InstanceFinder.h"
#include "Fee_30_SmallSector_Layer2_DatasetEraser.h"
#include "Fee_30_SmallSector_Layer2_WriteInstance.h"

#include "Fee_30_SmallSector_DatasetHandler.h"
#include "Fee_30_SmallSector_InstanceHandler.h"
#include "Fee_30_SmallSector_TaskManager.h"


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define FEE_30_SMALLSECTOR_WRITE_LAYER FEE_30_SMALLSECTOR_LAYER_ONE_INDEX

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#ifndef FEE_30_SMALLSECTOR_LOCAL /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL static
#endif


typedef enum
{
  FEE_30_SMALLSECTOR_WR_STATE_UNINIT = 0,
  FEE_30_SMALLSECTOR_WR_STATE_IDLE,
  FEE_30_SMALLSECTOR_WR_STATE_WAIT_FOR_INSTANCEFINDER,
  FEE_30_SMALLSECTOR_WR_STATE_ERASE_DATASET,
  FEE_30_SMALLSECTOR_WR_STATE_WRITE_INSTANCE
}Fee_30_SmallSector_Wr_StateType;

typedef struct
{
  MemIf_JobResultType JobResult;
  MemIf_StatusType Status;
  Fee_30_SmallSector_Wr_StateType StateMachine;
  boolean SuspendWrites;
}Fee_30_SmallSector_Wr_ComponentParameterType;


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_Wr_ComponentParameterType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Wr_ComponentParameter =
    {MEMIF_JOB_FAILED, MEMIF_UNINIT, FEE_30_SMALLSECTOR_WR_STATE_UNINIT, FALSE};

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_Ih_InstanceType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Wr_Instance;

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_UserJobParameterType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Wr_UserJobParameter;

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_InitiateDatasetErase()
 *********************************************************************************************************************/
/*!
 * \brief      Initiates DatasetEraser job
 * \details    Initiates DatasetEraser job with current InstanceFinder result
 * \param[in]  Current result of InstanceFinder sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_InitiateDatasetErase(Fee_30_SmallSector_If_ResultType InstanceFinderResult);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_InitiateWriteInstance()
 *********************************************************************************************************************/
/*!
 * \brief      Initiates WriteInstance job
 * \details    Initiates WriteInstance job
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_InitiateWriteInstance(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_ProcessInstanceFinderState()
 *********************************************************************************************************************/
/*!
 * \brief      Processes InstanceFinder state of FeeWrite sub-component
 * \details    Processes InstanceFinder state of FeeWrite sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_ProcessInstanceFinderState(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_ProcessDatasetEraseState()
 *********************************************************************************************************************/
/*!
 * \brief      Processes DatasetEraser state of FeeWrite sub-component
 * \details    Processes DatasetEraser state of FeeWrite sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_ProcessDatasetEraseState(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_ProcessStateMachine()
 *********************************************************************************************************************/
/*!
 * \brief      Processes state machine of FeeWrite sub-component
 * \details    Processes state machine of FeeWrite sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_ProcessStateMachine(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_FinishJob()
 *********************************************************************************************************************/
/*!
 * \brief      Finishes currently processed job
 * \details    State and status are reset. FeeWrite sub-component de-registers from TaskManager.
 * \param[in]  JobResult
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_FinishJob(MemIf_JobResultType JobResult);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_InitiateDatasetErase()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_InitiateDatasetErase(Fee_30_SmallSector_If_ResultType InstanceFinderResult)
{
  /* #10 Initiate DatasetEraser job with current job result of InstanceFinder */
  if (Fee_30_SmallSector_De_StartJob(InstanceFinderResult) == E_OK)
  {
    Fee_30_SmallSector_Wr_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WR_STATE_ERASE_DATASET;
  }
  else
  {
    Fee_30_SmallSector_Wr_FinishJob(MEMIF_JOB_FAILED);
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_InitiateWriteInstance()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_InitiateWriteInstance(void)
{
  /* #10 Initiate WriteInstance job */
  if (Fee_30_SmallSector_WrInst_StartJob(Fee_30_SmallSector_Wr_Instance, Fee_30_SmallSector_Wr_UserJobParameter) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_82 */
  {
    Fee_30_SmallSector_Wr_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WR_STATE_WRITE_INSTANCE;
  }
  else
  {
    Fee_30_SmallSector_Wr_FinishJob(MEMIF_JOB_FAILED);
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_ProcessInstanceFinderState()
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
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_ProcessInstanceFinderState(void)
{
	Fee_30_SmallSector_Ih_CompareParameterPointerType Fee_30_SmallSector_Wr_CompareParameter;
    /* #31 Start writing the payload pages */
    if (Fee_30_SmallSector_Ih_WritePayload(&Fee_30_SmallSector_Wr_Instance, Fee_30_SmallSector_Wr_UserJobParameter, &Fee_30_SmallSector_Wr_CompareParameter) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_63 */
    {
    	 Fee_30_SmallSector_Wr_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WR_STATE_ERASE_DATASET;
    }
    else
    {
      Fee_30_SmallSector_Wr_FinishJob(MEMIF_JOB_FAILED);
    }


	 Fee_30_SmallSector_Wr_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WR_STATE_ERASE_DATASET;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_ProcessDatasetEraseState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_ProcessDatasetEraseState(void)
{
  /* #10 Process this state if DatasetEraser finished its job successfully */
  if (Fee_30_SmallSector_De_GetJobResult() == MEMIF_JOB_OK)
  {
    /* #20 Initiate WriteInstance job with first instance of dataset */
    Fee_30_SmallSector_Ih_CreateInstance(&Fee_30_SmallSector_Wr_Instance, Fee_30_SmallSector_Dh_GetFirstInstanceAddress(), Fee_30_SmallSector_Dh_GetDataLength()); /* SBSW_FEE_30_SMALLSECTOR_81 */
    Fee_30_SmallSector_Wr_InitiateWriteInstance();
  }
  else
  {
    Fee_30_SmallSector_Wr_FinishJob(Fee_30_SmallSector_De_GetJobResult());
  }
}
/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_ProcessStateMachine()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_ProcessStateMachine(void)
{
  switch (Fee_30_SmallSector_Wr_ComponentParameter.StateMachine)
  {
    /*** -------------- IDLE -------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WR_STATE_IDLE:

      /* #10 New job was requested */
      /* #15 InstanceFinder job is initiated */
    //  if (Fee_30_SmallSector_If_StartJob(&Fee_30_SmallSector_Wr_Instance) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_81 */
      {
        Fee_30_SmallSector_Wr_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WR_STATE_WAIT_FOR_INSTANCEFINDER;
      }
    //  else
    //  {
   //     Fee_30_SmallSector_Wr_FinishJob(MEMIF_JOB_FAILED);
    //  }

      break;
    /*** -------------- FIND INSTANCE ----------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WR_STATE_WAIT_FOR_INSTANCEFINDER:
      /* #20 Result of InstanceFinder is awaited and processed */
      Fee_30_SmallSector_Wr_ProcessInstanceFinderState();

      break;

    /*** -------------- ERASE DATASET ----------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WR_STATE_ERASE_DATASET:
      /* #30 Result of DatasetEraser is awaited and processed */
     // Fee_30_SmallSector_Wr_ProcessDatasetEraseState();
    	 Fee_30_SmallSector_Wr_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WR_STATE_WRITE_INSTANCE;
      break;
    /*** -------------- WRITE INSTANCE --------------------------------------- ***/
    case FEE_30_SMALLSECTOR_WR_STATE_WRITE_INSTANCE:
      /* #40 WriteInstance sub-component finished its job, thus Layer1 FeeWrite sub-component is finished */
     // Fee_30_SmallSector_Wr_FinishJob(Fee_30_SmallSector_WrInst_GetJobResult()); Fee_30_SmallSector_Fls_GetJobResult()
    	Fee_30_SmallSector_Wr_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
      break;

    default:
      Fee_30_SmallSector_Wr_FinishJob(MEMIF_JOB_FAILED);
      break;
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_FinishJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Wr_FinishJob(MemIf_JobResultType JobResult)
{
  /* #10 FeeWrite sub-component de-registers itself from TaskManager */
  Fee_30_SmallSector_Tm_RemoveTask(Fee_30_SmallSector_Wr_Execute, Fee_30_SmallSector_Wr_Cancel, FEE_30_SMALLSECTOR_WRITE_LAYER); /* SBSW_FEE_30_SMALLSECTOR_15 */

  Fee_30_SmallSector_Wr_ComponentParameter.JobResult = JobResult;
  Fee_30_SmallSector_Wr_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WR_STATE_IDLE;
  Fee_30_SmallSector_Wr_ComponentParameter.Status = MEMIF_IDLE;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_Init(void)
{
  Fee_30_SmallSector_Wr_ComponentParameter.Status = MEMIF_IDLE;
  Fee_30_SmallSector_Wr_ComponentParameter.JobResult = MEMIF_JOB_OK;

  Fee_30_SmallSector_Ih_InitInstance(&Fee_30_SmallSector_Wr_Instance); /* SBSW_FEE_30_SMALLSECTOR_81 */

  Fee_30_SmallSector_Wr_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_WR_STATE_IDLE;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_GetStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_GetStatus(void)
{
  return Fee_30_SmallSector_Wr_ComponentParameter.Status;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_GetJobResult(void)
{
  return Fee_30_SmallSector_Wr_ComponentParameter.JobResult;
}


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_StartJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_StartJob(Fee_30_SmallSector_UserJobParameterType Fee_30_SmallSector_UserJobParameter)
{
  Std_ReturnType retVal;

  /* #10 Requested job is only accepted if FeeWrite's state machine is idle */
  if (Fee_30_SmallSector_Wr_ComponentParameter.StateMachine == FEE_30_SMALLSECTOR_WR_STATE_IDLE)
  {
    /* #20 FeeWrite sub-component registers its execution and cancel service to TaskManger */
    retVal = Fee_30_SmallSector_Tm_AddTask(Fee_30_SmallSector_Wr_Execute, Fee_30_SmallSector_Wr_Cancel, FEE_30_SMALLSECTOR_WRITE_LAYER); /* SBSW_FEE_30_SMALLSECTOR_14 */

    if (retVal == E_OK)
    {
      Fee_30_SmallSector_Wr_ComponentParameter.Status = MEMIF_BUSY;
      Fee_30_SmallSector_Wr_ComponentParameter.JobResult = MEMIF_JOB_PENDING;

      Fee_30_SmallSector_Wr_UserJobParameter = Fee_30_SmallSector_UserJobParameter;
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}
/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_Execute()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_Execute(void)
{
  /* #10 State machine is only processed if sub-component's status is busy and if writes are not suspended */
  if ((Fee_30_SmallSector_Wr_ComponentParameter.Status == MEMIF_BUSY) &&
      (Fee_30_SmallSector_Wr_ComponentParameter.SuspendWrites == FALSE))
  {
      Fee_30_SmallSector_Wr_ProcessStateMachine();
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_Cancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_Cancel(void)
{
  Fee_30_SmallSector_Wr_FinishJob(MEMIF_JOB_CANCELED);
}


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_SuspendWrites()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_SuspendWrites(void)
{
  /* #10 Set flag to suspend further Layer 1 Write processing */
  Fee_30_SmallSector_Wr_ComponentParameter.SuspendWrites = TRUE;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Wr_ResumeWrites()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Wr_ResumeWrites(void)
{
  /* #10 Reset flag to resume Layer 1 Write processing */
  Fee_30_SmallSector_Wr_ComponentParameter.SuspendWrites = FALSE;
}

#define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA L:LongInfixName */

/* SBSW_JUSTIFICATION_BEGIN
    \ID SBSW_FEE_30_SMALLSECTOR_81
      \DESCRIPTION Function is called with reference to local parameter Fee_30_SmallSector_Wr_Instance
      \COUNTERMEASURE \N Fee_30_SmallSector_Wr_Instance is a local parameter, thus references to this parameter are valid.

    \ID SBSW_FEE_30_SMALLSECTOR_82
      \DESCRIPTION Function is called with local structure Fee_30_SmallSector_Wr_UserJobParameter, which contains a pointer to data buffer.
      \COUNTERMEASURE \N Fee_30_SmallSector_Wr_UserJobParameter is initialized with input parameter of function Fee_30_SmallSector_Wr_StartJob, which is invoked upon start
                         of Fee_30_SmallSector_Layer1_Write sub-component. Thus caller ensures pointer to be valid.
SBSW_JUSTIFICATION_END */


/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Layer1_Write.c
 *********************************************************************************************************************/
