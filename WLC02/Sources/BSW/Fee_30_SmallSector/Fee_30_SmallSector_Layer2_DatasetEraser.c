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
 *         \file  Fee_30_SmallSector_Layer2_DatasetEraser.c
 *        \brief  DatasetEraser sub-component is responsible for erasing all physical flash sectors of one FEE dataset.
 *
 *      \details  DatasetEraser starts the erase procedure by writing a static pattern to the first page of a dataset,
 *                which is reserved for this case. If a dataset consists of more than one flash sector, these sectors
 *                are erased in reverse order, so that the sector containing the erase pattern is erased last.
 *
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector_Layer2_DatasetEraser.h"

#include "Fee_30_SmallSector_TaskManager.h"
#include "Fee_30_SmallSector_FlsCoordinator.h"
#include "Fee_30_SmallSector_DatasetHandler.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define FEE_30_SMALLSECTOR_DATASET_ERASER_LAYER FEE_30_SMALLSECTOR_LAYER_TWO_INDEX

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#ifndef FEE_30_SMALLSECTOR_LOCAL /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL static
#endif

typedef enum
{
  FEE_30_SMALLSECTOR_DE_STATE_UNINIT = 0,
  FEE_30_SMALLSECTOR_DE_STATE_IDLE,
  FEE_30_SMALLSECTOR_DE_STATE_WAITFOR_WRITE_ERASE_PATTERN1,
  FEE_30_SMALLSECTOR_DE_STATE_WAITFOR_ERASE_SECTOR,
  FEE_30_SMALLSECTOR_DE_STATE_WAITFOR_WRITE_ERASE_PATTERN2
} Fee_30_SmallSector_De_StateType;

typedef struct
{
  MemIf_JobResultType JobResult;
  MemIf_StatusType Status;
  Fee_30_SmallSector_De_StateType StateMachine;
} Fee_30_SmallSector_De_ComponentParameterType;


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_De_ComponentParameterType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_De_ComponentParameter =
  { MEMIF_JOB_FAILED, MEMIF_UNINIT, FEE_30_SMALLSECTOR_DE_STATE_UNINIT };

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_If_ResultType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_De_InstanceFinderResult;
FEE_30_SMALLSECTOR_LOCAL VAR(sint16, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_De_SectorIndex;

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_FinishJob()
 *********************************************************************************************************************/
/*!
 * \brief      Finishes currently processed job
 * \details    State and status are reset. DatasetEraser sub-component is de-registered from TaskManager.
 * \param[in]  JobResult
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_FinishJob(MemIf_JobResultType JobResult);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_EraseLastSector()
 *********************************************************************************************************************/
/*!
 * \brief      Erases last flash sector which is not yet erased
 * \details    Erases last flash sector which is not yet erased
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_EraseLastSector(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_De_ProcessStateIdle()
 **********************************************************************************************************************/
/*!
 * \brief      Processes idle state of DatasetEraser state machine
 * \details    Checks if ErasePattern needs to be written and initiates respective job.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_ProcessStateIdle(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_De_ProcessStateWriteErasePattern1()
 **********************************************************************************************************************/
/*!
 * \brief      Processes WriteErasePattern1 state of DatasetEraser state machine
 * \details    Initiates erase of sector
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_ProcessStateWriteErasePattern1(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_De_ProcessStateEraseSector()
 **********************************************************************************************************************/
/*!
 * \brief      Processes EraseSector state of DatasetEraser state machine
 * \details    Initiates erase of sector
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_ProcessStateEraseSector(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_De_ProcessStateMachine()
 **********************************************************************************************************************/
/*!
 * \brief      Processes state machine of DatasetEraser sub-component
 * \details    Processes state machine of DatasetEraser sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_ProcessStateMachine(void);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_FinishJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_FinishJob(MemIf_JobResultType JobResult)
{
  /* #10 DatasetEraser sub-component is de-registered from TaskManager */
  Fee_30_SmallSector_Tm_RemoveTask(Fee_30_SmallSector_De_Execute, Fee_30_SmallSector_De_Cancel, FEE_30_SMALLSECTOR_DATASET_ERASER_LAYER); /* SBSW_FEE_30_SMALLSECTOR_15 */

  /* #20 Reset internal parameters */
  Fee_30_SmallSector_De_ComponentParameter.JobResult = JobResult;
  Fee_30_SmallSector_De_ComponentParameter.Status = MEMIF_IDLE;
  Fee_30_SmallSector_De_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_DE_STATE_IDLE;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_EraseLastSector()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_EraseLastSector(void)
{
  /* #10 Erase Flash sector which is referenced by sector index */
  if (Fee_30_SmallSector_Dh_EraseSector((uint16) Fee_30_SmallSector_De_SectorIndex) == E_OK)
  {
    Fee_30_SmallSector_De_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_DE_STATE_WAITFOR_ERASE_SECTOR;
  }
  else
  {
    Fee_30_SmallSector_De_FinishJob(MEMIF_JOB_FAILED);
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_De_ProcessStateIdle()
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
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_ProcessStateIdle(void)
{
  /* #10 ErasePattern1 needs to be written if InstanceFinder job was OK or if ErasePattern2 was incorrect. */
  /* #11 If InstanceFinder returns with INSTANCE_FINDER_EP1_INCORRECT, no write is necessary and the last sector can be erased right away */
  if ((Fee_30_SmallSector_De_InstanceFinderResult == INSTANCE_FINDER_OK) ||
      (Fee_30_SmallSector_De_InstanceFinderResult == INSTANCE_FINDER_EP2_INCORRECT)
     )
  {
    /* #20 Write ErasePattern to first page of dataset */
    if (Fee_30_SmallSector_Dh_WriteErasePattern(DATASET_ERASE_PATTERN_1) == E_OK)
    {
      Fee_30_SmallSector_De_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_DE_STATE_WAITFOR_WRITE_ERASE_PATTERN1;
    }
    else
    {
      Fee_30_SmallSector_De_FinishJob(MEMIF_JOB_FAILED);
    }
  }
  /* #30 InstanceFinder job returned with INSTANCE_FINDER_EP1_INCORRECT, which indicates that ErasePattern1 is not blank. */
  /* #31 Therefore it's not necessary to write the ErasePattern1. Dataset's Flash sectors can be erased immediately */
  else
  {
    /* #40 InstanceFinderResult: INSTANCE_FINDER_EP1_INCORRECT --> Start erasing the Flash sectors */
    Fee_30_SmallSector_De_EraseLastSector();
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_De_ProcessStateWriteErasePattern1()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_ProcessStateWriteErasePattern1(void)
{
  /* #10 Flash finished writing the erase pattern 1 */
  if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
  {
    /* #20 Start erasing the Flash sectors */
    Fee_30_SmallSector_De_EraseLastSector();
  }
  else
  {
    Fee_30_SmallSector_De_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_De_ProcessStateEraseSector()
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
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_ProcessStateEraseSector(void)
{
  /* #10 Flash finished erasing a sector */
  if (Fee_30_SmallSector_Fls_GetJobResult() == MEMIF_JOB_OK)
  {
    /* #20 Decrement SectorIndex because sector with current index was successfully erased */
    Fee_30_SmallSector_De_SectorIndex--;

    /* #30 Erase next Flash sector if there are still sectors to erase */
    /* #31 If SectorIndex is negative there are no more sectors to erase */
    if (Fee_30_SmallSector_De_SectorIndex >= 0)
    {
      /* #40 Erase next Flash sector */
      Fee_30_SmallSector_De_EraseLastSector();
    }
    else
    {
      /* #50 After erasing all sectors, ErasePattern2 needs to be written */
      if (Fee_30_SmallSector_Dh_WriteErasePattern(DATASET_ERASE_PATTERN_2) == E_OK)
      {
        Fee_30_SmallSector_De_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_DE_STATE_WAITFOR_WRITE_ERASE_PATTERN2;
      }
      else
      {
        Fee_30_SmallSector_De_FinishJob(MEMIF_JOB_FAILED);
      }
    }
  }
  else
  {
    Fee_30_SmallSector_De_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
  }
}

/**********************************************************************************************************************
 Fee_30_SmallSector_De_ProcessStateMachine()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_De_ProcessStateMachine(void)
{
  switch (Fee_30_SmallSector_De_ComponentParameter.StateMachine)
  {
      /*** ---------------- IDLE -------------------------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_DE_STATE_IDLE:
      Fee_30_SmallSector_De_ProcessStateIdle();
      break;

      /*** ---------------- WRITE ERASE PATTERN 1 --------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_DE_STATE_WAITFOR_WRITE_ERASE_PATTERN1:
      Fee_30_SmallSector_De_ProcessStateWriteErasePattern1();
      break;

      /*** ---------------- ERASE SECTOR ------------------------------------------------------------------ ***/
    case FEE_30_SMALLSECTOR_DE_STATE_WAITFOR_ERASE_SECTOR:
      Fee_30_SmallSector_De_ProcessStateEraseSector();
      break;

      /*** ---------------- WRITE ERASE PATTERN 2 --------------------------------------------------------- ***/
    case FEE_30_SMALLSECTOR_DE_STATE_WAITFOR_WRITE_ERASE_PATTERN2:
      Fee_30_SmallSector_De_FinishJob(Fee_30_SmallSector_Fls_GetJobResult());
      break;

    default:
      Fee_30_SmallSector_De_FinishJob(MEMIF_JOB_FAILED);
      break;
  }
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_Init(void)
{
  /* #10 Initialize component parameter */
  Fee_30_SmallSector_De_ComponentParameter.Status = MEMIF_IDLE;
  Fee_30_SmallSector_De_ComponentParameter.JobResult = MEMIF_JOB_OK;

  /* #20 Initialize job parameter */
  Fee_30_SmallSector_De_InstanceFinderResult = INSTANCE_FINDER_OK;
  Fee_30_SmallSector_De_SectorIndex = 0;

  Fee_30_SmallSector_De_ComponentParameter.StateMachine = FEE_30_SMALLSECTOR_DE_STATE_IDLE;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_GetStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_GetStatus(void)
{
  return Fee_30_SmallSector_De_ComponentParameter.Status;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_GetJobResult(void)
{
  return Fee_30_SmallSector_De_ComponentParameter.JobResult;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_StartJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_StartJob(Fee_30_SmallSector_If_ResultType InstanceFinderResult)
{
  Std_ReturnType retVal;
  /* #10 Requested job is only accepted if sub-component's state machine is idle */
  if (Fee_30_SmallSector_De_ComponentParameter.StateMachine == FEE_30_SMALLSECTOR_DE_STATE_IDLE)
  {
    /* #20 DatasetEraser registers its execution and cancel service to TaskManager */
    retVal = Fee_30_SmallSector_Tm_AddTask(Fee_30_SmallSector_De_Execute, Fee_30_SmallSector_De_Cancel, FEE_30_SMALLSECTOR_DATASET_ERASER_LAYER); /* SBSW_FEE_30_SMALLSECTOR_14 */

    if (retVal == E_OK)
    {
      Fee_30_SmallSector_De_ComponentParameter.Status = MEMIF_BUSY;
      Fee_30_SmallSector_De_ComponentParameter.JobResult = MEMIF_JOB_PENDING;
      /* #30 Save input parameter */
      Fee_30_SmallSector_De_InstanceFinderResult = InstanceFinderResult;
      /* #40 Initialize index of last flash sector in current dataset */
      Fee_30_SmallSector_De_SectorIndex = Fee_30_SmallSector_Dh_GetLastSectorIndex();
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_Execute()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_Execute(void)
{
  /* #10 State machine is only processed if DatasetEraser sub-component's status is busy */
  if (Fee_30_SmallSector_De_ComponentParameter.Status == MEMIF_BUSY)
  {
    Fee_30_SmallSector_De_ProcessStateMachine();
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_De_Cancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_De_Cancel(void)
{
  Fee_30_SmallSector_De_FinishJob(MEMIF_JOB_CANCELED);
}

#define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA L:LongInfixName */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Layer2_DatasetEraser.c
 *********************************************************************************************************************/
