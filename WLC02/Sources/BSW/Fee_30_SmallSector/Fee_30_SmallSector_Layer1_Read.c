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
 *        \file   Fee_30_SmallSector_Layer1_Read.c
 *        \brief  This sub-component of FEE module is processing read jobs
 *
 *      \details  FeeRead sub-component is responsible for processing read jobs. Upon job request it registers itself
 *                to TaskManager and after finishing the job, it de-registers itself from TaskManager. To process the
 *                internal state machine, sub-component InstanceFinder is used to find most recent data.
 *
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector_Layer1_Read.h"
#include "Fee_30_SmallSector_Layer2_InstanceFinder.h"

#include "Fee_30_SmallSector_TaskManager.h"
#include "Fee_30_SmallSector_FlsCoordinator.h"

#include "Fee_30_SmallSector_PartitionHandler.h"
#include "Fee_30_SmallSector_InstanceHandler.h"


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define FEE_30_SMALLSECTOR_READ_LAYER FEE_30_SMALLSECTOR_LAYER_ONE_INDEX

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#ifndef FEE_30_SMALLSECTOR_LOCAL /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL static
#endif

typedef enum
{
    FEE_30_SMALLSECTOR_RD_STATE_UNINIT = 0,
    FEE_30_SMALLSECTOR_RD_STATE_IDLE,
    FEE_30_SMALLSECTOR_RD_STATE_WAIT_FOR_INSTANCEFINDER,
    FEE_30_SMALLSECTOR_RD_STATE_READ_DATA
}Fee_30_SmallSector_Rd_StateType;

typedef struct
{
    MemIf_JobResultType JobResult;
    MemIf_StatusType Status;
    Fee_30_SmallSector_Rd_StateType StateMachine;
}Fee_30_SmallSector_Rd_ComponentParameterType;


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define FEE_30_SMALLSECTOR_START_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_Rd_ComponentParameterType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Rd_ComponentParameter =
    {MEMIF_JOB_FAILED, MEMIF_UNINIT, FEE_30_SMALLSECTOR_RD_STATE_UNINIT};

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_Ih_InstanceType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Rd_Instance;

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_UserJobParameterType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Rd_UserJobParameter;

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
  Fee_30_SmallSector_Rd_FinishJob()
**********************************************************************************************************************/
/*!
 * \brief      Finishes currently processed job
 * \details    State and status are reset. FeeRead sub-component de-registers itself from TaskManager.
 * \param[in]  JobResult
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_FinishJob(MemIf_JobResultType JobResult);

/**********************************************************************************************************************
  Fee_30_SmallSector_Rd_ProcessStateMachine()
**********************************************************************************************************************/
/*!
 * \brief      Processes state machine of FeeRead sub-component
 * \details    Processes state machine of FeeRead sub-component, only if status is busy
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Rd_ProcessStateMachine(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Rd_ProcessInstanceFinderState()
**********************************************************************************************************************/
/*!
 * \brief      Processes distinct state of FeeRead sub-component
 * \details    Processes state FEE_30_SMALLSECTOR_RD_STATE_WAIT_FOR_INSTANCEFINDER
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Rd_ProcessInstanceFinderState(void);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
  Fee_30_SmallSector_Rd_FinishJob()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_FinishJob(MemIf_JobResultType JobResult)
{
  /* #10 FeeRead sub-component de-registers itself from TaskManager */
  Fee_30_SmallSector_Tm_RemoveTask(Fee_30_SmallSector_Rd_Execute, Fee_30_SmallSector_Rd_Cancel, FEE_30_SMALLSECTOR_READ_LAYER); /* SBSW_FEE_30_SMALLSECTOR_15 */

  Fee_30_SmallSector_Rd_ComponentParameter.JobResult = JobResult;
  Fee_30_SmallSector_Rd_ComponentParameter.Status = MEMIF_IDLE;
  Fee_30_SmallSector_Rd_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_RD_STATE_IDLE;
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Rd_ProcessStateMachine()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Rd_ProcessStateMachine(void)
{
  switch (Fee_30_SmallSector_Rd_ComponentParameter.StateMachine)
  {
    /*** -------------- IDLE -------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_RD_STATE_IDLE:
      /* #10 Initiate InstanceFinder job */
   //   if (Fee_30_SmallSector_If_StartJob(&Fee_30_SmallSector_Rd_Instance) == E_OK) /* SBSW_FEE_30_SMALLSECTOR_91 */
      {
        Fee_30_SmallSector_Rd_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_RD_STATE_WAIT_FOR_INSTANCEFINDER;
      }
    //  else
   //   {
   //     Fee_30_SmallSector_Rd_FinishJob(MEMIF_JOB_FAILED);
   //   }
      break;
      /*** -------------- WAIT FOR INSTANCE FINDER ----------------------------- ***/
    case FEE_30_SMALLSECTOR_RD_STATE_WAIT_FOR_INSTANCEFINDER:
      /* #20 Result of InstanceFinder is awaited and processed */
      Fee_30_SmallSector_Rd_ProcessInstanceFinderState();
      break;
      /*** -------------- READING DATA ----------------------------------------- ***/
    case FEE_30_SMALLSECTOR_RD_STATE_READ_DATA:
      /* #30 Flash driver finished */
      Fee_30_SmallSector_Rd_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
      break;

    default:
      Fee_30_SmallSector_Rd_FinishJob(MEMIF_JOB_FAILED);
      break;
  }
}



/**********************************************************************************************************************
  Fee_30_SmallSector_Rd_ProcessInstanceFinderState()
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
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Rd_ProcessInstanceFinderState(void)
{
  /* #10 InstanceFinder is finished */
 // if (Fee_30_SmallSector_If_MapResult(Fee_30_SmallSector_If_GetJobResult()) == MEMIF_JOB_OK)
  {
    /* #20 Check if found instance is valid for reading */
   // if (Fee_30_SmallSector_Rd_Instance.InstanceStatus == INSTANCE_STATUS_OK)
    {
      /* #30 Start reading instance data */
      if (Fee_30_SmallSector_Ih_ReadData(&Fee_30_SmallSector_Rd_Instance,                        /* SBSW_FEE_30_SMALLSECTOR_92 */
                      Fee_30_SmallSector_Rd_UserJobParameter.DataBufferPtr,
                      Fee_30_SmallSector_Rd_UserJobParameter.BlockOffset,
                      Fee_30_SmallSector_Rd_UserJobParameter.Length,Fee_30_SmallSector_Rd_UserJobParameter.Blockid) == E_OK)
      {
        Fee_30_SmallSector_Rd_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_RD_STATE_READ_DATA;
      }
      else
      {
        Fee_30_SmallSector_Rd_FinishJob(MEMIF_JOB_FAILED);
      }
    }
   // else
  //  {
      /* #40 Status of found instance is either INVALID or INCONSISTENT */
   ///   Fee_30_SmallSector_Rd_FinishJob(Fee_30_SmallSector_Ih_SetNegativeJobResultAccordingToStatus(&Fee_30_SmallSector_Rd_Instance)); /* SBSW_FEE_30_SMALLSECTOR_91 */
    //}/
  }
  //else
 // {
    /* #50 InstanceFinder either failed or detected an inconsistent dataset, thus InstanceFinder's job result is reported to upper layer */
 //   Fee_30_SmallSector_Rd_FinishJob(Fee_30_SmallSector_If_MapResult(Fee_30_SmallSector_If_GetJobResult()));
  //}
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Rd_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_Init(void)
{
  Fee_30_SmallSector_Rd_ComponentParameter.Status = MEMIF_IDLE;
  Fee_30_SmallSector_Rd_ComponentParameter.JobResult = MEMIF_JOB_OK;

  Fee_30_SmallSector_Ih_InitInstance(&Fee_30_SmallSector_Rd_Instance); /* SBSW_FEE_30_SMALLSECTOR_91 */

  Fee_30_SmallSector_Rd_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_RD_STATE_IDLE;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Rd_GetStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_GetStatus(void)
{
  return Fee_30_SmallSector_Rd_ComponentParameter.Status;
}  

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Rd_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_GetJobResult(void)
{
  return Fee_30_SmallSector_Rd_ComponentParameter.JobResult;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Rd_StartJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_StartJob(Fee_30_SmallSector_UserJobParameterType Fee_30_SmallSector_UserJobParameter)
{
  Std_ReturnType retVal;

  /* #10 Job request is accepted if FeeRead sub-component's state machine is idle */
  if (Fee_30_SmallSector_Rd_ComponentParameter.StateMachine == FEE_30_SMALLSECTOR_RD_STATE_IDLE)
  {
    /* #20 FeeRead sub-component registers its execution and cancel service to TaskManager */
    retVal = Fee_30_SmallSector_Tm_AddTask(Fee_30_SmallSector_Rd_Execute, Fee_30_SmallSector_Rd_Cancel, FEE_30_SMALLSECTOR_READ_LAYER); /* SBSW_FEE_30_SMALLSECTOR_14 */

    if (retVal == E_OK)
    {
      Fee_30_SmallSector_Rd_ComponentParameter.Status = MEMIF_BUSY;
      Fee_30_SmallSector_Rd_ComponentParameter.JobResult = MEMIF_JOB_PENDING;

      Fee_30_SmallSector_Rd_UserJobParameter = Fee_30_SmallSector_UserJobParameter;
    }

  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Rd_Execute()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_Execute(void)
{
  /* #10 State machine is only processed if FeeRead sub-component's status is busy */
  if (Fee_30_SmallSector_Rd_ComponentParameter.Status == MEMIF_BUSY)
  {
    Fee_30_SmallSector_Rd_ProcessStateMachine();
  }
}


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Rd_Cancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Rd_Cancel(void)
{
  Fee_30_SmallSector_Rd_FinishJob(MEMIF_JOB_CANCELED);
}


#define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA L:LongInfixName */

/* SBSW_JUSTIFICATION_BEGIN
    \ID SBSW_FEE_30_SMALLSECTOR_91
      \DESCRIPTION Function is called with reference to local parameter Fee_30_SmallSector_Rd_Instance
      \COUNTERMEASURE \N Fee_30_SmallSector_Rd_Instance is a local parameter, thus references to this parameter are valid.
    \ID SBSW_FEE_30_SMALLSECTOR_92
      \DESCRIPTION Reference to local parameter Fee_30_SmallSector_Rd_Instance and parameters of Fee_30_SmallSector_Rd_UserJobParameter structure are passed to function.
      \COUNTERMEASURE \N Fee_30_SmallSector_Rd_Instance is a local parameter, thus references to this parameter are valid. Data buffer pointer and length/offset parameters
                         of Fee_30_SmallSector_Rd_UserJobParameter structure are both checked by development error checks upon request of read job. Input/job parameters
                         of Fee_30_SmallSector_Read API are passed to Fee_30_SmallSector_Layer1_Read sub-component via call-by-value of Fee_30_SmallSector_Rd_StartJob service.
SBSW_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Layer1_Read.c
 *********************************************************************************************************************/
