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
 *         \file  Fee_30_SmallSector.c
 *        \brief  FEE source file
 *
 *      \details  The Fee Flash Emulation abstracts from the device specific addressing scheme and segmentation and
 *                provides a virtual addressing scheme and segmentation to upper layers as well as a virtually
 *                unlimited number of erase cycles.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  DESIGN DECISIONS
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
 */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Fee_30_SmallSector.h"
#include "Fee_30_SmallSector_Cbk.h"

/**** Sub-Component Includes *****************************************************************************************/
#include "Fee_30_SmallSector_TaskManager.h"
#include "Fee_30_SmallSector_FlsCoordinator.h"

/* Data Storage Handler */
#include "Fee_30_SmallSector_PartitionHandler.h"
#include "Fee_30_SmallSector_BlockHandler.h"
#include "Fee_30_SmallSector_DatasetHandler.h"

/* Layer 1 sub-components */
#include "Fee_30_SmallSector_Layer1_Read.h"
#include "Fee_30_SmallSector_Layer1_Write.h"

/* Layer 2 sub-components */
#include "Fee_30_SmallSector_Layer2_WriteInstance.h"
#include "Fee_30_SmallSector_Layer2_DatasetEraser.h"
#include "Fee_30_SmallSector_Layer2_InstanceFinder.h"

/* Layer 3 sub-component */
#include "Fee_30_SmallSector_Layer3_ReadManagementBytes.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

#if (   (FEE_30_SMALLSECTOR_SW_MAJOR_VERSION != (2u)) \
     || (FEE_30_SMALLSECTOR_SW_MINOR_VERSION != (1u)) \
     || (FEE_30_SMALLSECTOR_AR_RELEASE_MAJOR_VERSION != (4u)) \
     || (FEE_30_SMALLSECTOR_AR_RELEASE_MINOR_VERSION != (0u)))
# error "Version numbers of Fee_30_SmallSector.c and Fee_30_SmallSector.h are inconsistent!"
#endif

#if (   (FEE_30_SMALLSECTOR_CFG_MAJOR_VERSION != (2u)) \
     || (FEE_30_SMALLSECTOR_CFG_MINOR_VERSION != (0u)))
# error "Version numbers of Fee_30_SmallSector.c and Fee_30_SmallSector_Cfg.h are inconsistent!"
#endif

#if (   (FEE_30_SMALLSECTOR_CBK_MAJOR_VERSION != (2u)) \
     || (FEE_30_SMALLSECTOR_CBK_MINOR_VERSION != (1u)))
# error "Version numbers of Fee_30_SmallSector.c and Fee_30_SmallSector_Cbk.h are inconsistent!"
#endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_RESERVED_BLOCK_NUMBER_1             (0x0000u) /*!< \trace SPEC-2567374 */
#define FEE_30_SMALLSECTOR_RESERVED_BLOCK_NUMBER_2             (0xFFFFu) /*!< \trace SPEC-2567374 */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (FEE_30_SMALLSECTOR_LOCAL) /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL static
#endif

#if !defined (FEE_30_SMALLSECTOR_LOCAL_INLINE) /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL_INLINE LOCAL_INLINE
#endif


typedef struct
{
  MemIf_JobResultType JobResult;
  MemIf_StatusType Status;
}Fee_30_SmallSector_ComponentParameterType;

typedef enum
{
  FEE_30_SMALLSECTOR_STATE_UNINIT = 0,
  FEE_30_SMALLSECTOR_STATE_IDLE,
  FEE_30_SMALLSECTOR_STATE_BUSY
} EFeeStateType;

/*!
 * Internal comment removed.
 *
 *
 */
typedef struct
{
  boolean MainFunctionBusy;
  boolean JobRequested;
  boolean CancelRequested;
} Fee_30_SmallSector_InternalFlagsType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/*---------- FAST INIT VARIABLES ----------*/
#define FEE_30_SMALLSECTOR_START_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_ComponentParameterType, FEE_30_SMALLSECTOR_FAST_DATA) Fee_30_SmallSector_ComponentParameter = {MEMIF_JOB_FAILED, MEMIF_UNINIT};

FEE_30_SMALLSECTOR_LOCAL VAR(EFeeStateType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_StateMachine = FEE_30_SMALLSECTOR_STATE_UNINIT;

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*---------- NO INIT VARIABLES ----------*/
#define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_UserJobParameterType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_UserJobParameter;

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_InternalFlagsType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_InternalFlags;

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define FEE_30_SMALLSECTOR_START_SEC_CODE
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetFlagJobRequested()
 *********************************************************************************************************************/
/*!
 * \brief      Sets flag to signal requested job
 * \details    Sets flag to signal requested job
 * \param[in]  value is either TRUE or FALSE
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_SetFlagJobRequested(boolean value);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetFlagCancelRequested()
 *********************************************************************************************************************/
/*!
 * \brief      Sets flag to signal that cancel is requested
 * \details    Sets flag to signal that cancel is requested
 * \param[in]  value is either TRUE or FALSE
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_SetFlagCancelRequested(boolean value);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetFlagMainFunctionBusy()
 *********************************************************************************************************************/
/*!
 * \brief      Sets flag to signal that main function is busy
 * \details    Sets flag to signal that main function is busy
 * \param[in]  value is either TRUE or FALSE
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_SetFlagMainFunctionBusy(boolean value);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_GetLayer1Status()
 *********************************************************************************************************************/
/*!
 * \brief      Returns status of active layer 1 sub-component
 * \details    Returns status of active layer 1 sub-component
 * \return     Status of sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_GetLayer1Status(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_GetLayer1JobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Returns job result of active layer 1 sub-component
 * \details    Returns job result of active layer 1 sub-component
 * \return     JobResult of sub-component
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_GetLayer1JobResult(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_StartLayer1Job()
 *********************************************************************************************************************/
/*!
 * \brief      Calls start service of layer 1 job
 * \details    Depending on currently requested job, this service calls the
 *             appropriate layer 1 sub-component's start service
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_StartLayer1Job(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetUserParameter()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes global struct with user job parameter
 * \details    Initializes global struct with user job parameter which were passed by API service call
 * \param[in]  BlockNumber
 * \param[in]  BlockOffset
 * \param[in]  DataBufferPtr
 * \param[in]  Length
 * \param[in]  JobType
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_SetUserParameter(uint16 Blockid,uint16 BlockNumber,
                                                             uint16 BlockOffset,
                                                             Fee_30_SmallSector_DataPtr DataBufferPtr,
                                                             uint16 Length,
                                                             Fee_30_SmallSector_JobType JobType);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetJobParameter()
 *********************************************************************************************************************/
/*!
 * \brief      Relevant internal parameter are set upon job request
 * \details    Upon job request internal parameter are set, such as status, job result and internal flags
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_SetJobParameter(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_StartJob()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes job parameter and calls Fee_30_SmallSector_StartLayer1Job
 * \details    Initializes job parameter and calls Fee_30_SmallSector_StartLayer1Job
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_StartJob(void);


/**********************************************************************************************************************
 *  Fee_30_SmallSector_CheckIdle()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if FEE module is idle
 * \details    Checks if FEE module is idle
 * \return     E_OK: FEE module is idle
 * \return     E_NOT_OK: FEE module is busy/busy_internal or uninit
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_CheckIdle(void);

#if (FEE_30_SMALLSECTOR_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  Fee_30_SmallSector_DetChkInit()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if FEE module is initialized
 * \details    Checks if FEE module is initialized
 * \return     E_OK: FEE module is initialized
 * \return     E_NOT_OK: FEE module is not initialized
 * \pre        Switch FEE_30_SMALLSECTOR_DEV_ERROR_DETECT is enabled.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_DetChkInit(void);


/**********************************************************************************************************************
 *  Fee_30_SmallSector_DetChkBlockNumberOk()
 *********************************************************************************************************************/
/*!
 *
 * \brief      Checks if BlockNumber is invalid
 * \details    Checks if BlockNumber is either one of the reserved values or if BlockNumber is not configured
 * \param[in]  BlockNumber
 * \return     E_OK: BlockNumber is valid
 * \return     E_NOT_OK: BlockNumber is invalid
 * \pre        Switch FEE_30_SMALLSECTOR_DEV_ERROR_DETECT is enabled.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_DetChkBlockNumberOk(uint16 BlockNumber, uint8 ApiID);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_DetChkDataPointerOk()
 *********************************************************************************************************************/
/*!
 *
 * \brief      Checks if DataBufferPtr is invalid
 * \details    Checks if DataBufferPtr is NULL_PTR
 * \param[in]  DataBufferPtr
 * \return     E_OK: DataBufferPtr is valid
 * \return     E_NOT_OK: DataBufferPtr is NULL
 * \pre        Switch FEE_30_SMALLSECTOR_DEV_ERROR_DETECT is enabled.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_DetChkDataPointerOk(
        P2CONST(uint8, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) DataBufferPtr);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_DetChkBlockOffsetOk()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if BlockOffset is out of range
 * \details    Checks if BlockOffset is out of range
 * \param[in]  BlockOffset
 * \return     E_OK: BlockOffset is in range
 * \return     E_NOT_OK: BlockOffset is out of range
 * \pre        Switch FEE_30_SMALLSECTOR_DEV_ERROR_DETECT is enabled.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_DetChkBlockOffsetOk(uint16 BlockNumber, uint16 BlockOffset);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_DetChkBlockLengthOk()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if Length is out of range
 * \details    Checks if Length is out of range
 * \param[in]  BlockNumber
 * \param[in]  Length
 * \param[in]  BlockOffset
 * \return     E_OK: Length is in range
 * \return     E_NOT_OK: Length is out of range
 * \pre        Switch FEE_30_SMALLSECTOR_DEV_ERROR_DETECT is enabled.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_DetChkBlockLengthOk(uint16 BlockNumber,
        uint16 Length, uint16 BlockOffset);
#endif

/**********************************************************************************************************************
 *  Fee_30_SmallSector_InitDataHandler()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes all data handlers of storage system
 * \details    Initializes PartitionHandler, BlockHandler and InstanceHandler
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_InitDataHandler(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_ProcessStateMachine()
 *********************************************************************************************************************/
/*!
 * \brief      Processes main state machine
 * \details    Processes main state machine based on current state
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_ProcessStateMachine(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_FinishJob()
 *********************************************************************************************************************/
/*!
 * \brief      Finishes currently processed job
 * \details    State and status are reset.
 * \param[in]  JobResult
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace DSGN-Fee22977
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_FinishJob(MemIf_JobResultType JobResult);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetFlagJobRequested()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_SetFlagJobRequested(boolean value)
{
  Fee_30_SmallSector_InternalFlags.JobRequested = value;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetFlagCancelRequested()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_SetFlagCancelRequested(boolean value)
{
  Fee_30_SmallSector_InternalFlags.CancelRequested = value;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetFlagMainfunctionBusy()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_SetFlagMainFunctionBusy(boolean value)
{
  Fee_30_SmallSector_InternalFlags.MainFunctionBusy = value;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_GetLayer1Status()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_GetLayer1Status(void)
{
  /* #10 Depending on JobType, status of currently processed job is requested. */
  /* #20 Possible jobs are: Read, Write, Invalidate, Erase */

  MemIf_StatusType retVal;

  switch (Fee_30_SmallSector_UserJobParameter.JobType)
  {
    case (FEE_30_SMALLSECTOR_READ_JOB):
      retVal = Fee_30_SmallSector_Rd_GetStatus();
      break;
    default: /* #30 All other jobs are handled by Layer 1 Write sub-component */
      retVal = Fee_30_SmallSector_Wr_GetStatus();
      break;
  }
  return retVal;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_GetLayer1JobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_GetLayer1JobResult(void)
{
  /* #10 Depending on JobType, job result of currently processed job is requested. */
  /* #20 Possible jobs are: Read, Write, Invalidate, Erase */

  MemIf_JobResultType retVal;

  switch (Fee_30_SmallSector_UserJobParameter.JobType)
  {
    case (FEE_30_SMALLSECTOR_READ_JOB):
      retVal = Fee_30_SmallSector_Rd_GetJobResult();
      break;
    default: /* #30 All other jobs are handled by Layer 1 Write sub-component */
      retVal = Fee_30_SmallSector_Wr_GetJobResult();
      break;
  }
  return retVal;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_StartLayer1Job()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_StartLayer1Job(void)
{
  /* #10 Depending on JobType, currently requested job is initiated. */
  /* #20 Possible jobs are: Read, Write, Invalidate, Erase */

  switch (Fee_30_SmallSector_UserJobParameter.JobType)
  {
    case (FEE_30_SMALLSECTOR_READ_JOB):
      (void) Fee_30_SmallSector_Rd_StartJob(Fee_30_SmallSector_UserJobParameter); /* SBSW_FEE_30_SMALLSECTOR_02 */
      break;
    default: /* #30 All other jobs are handled by Layer 1 Write sub-component */
      (void) Fee_30_SmallSector_Wr_StartJob(Fee_30_SmallSector_UserJobParameter); /* SBSW_FEE_30_SMALLSECTOR_02 */
      break;
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetUserParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_SetUserParameter(uint16 Blockid,uint16 BlockNumber,
                                                            uint16 BlockOffset,
                                                            Fee_30_SmallSector_DataPtr DataBufferPtr,
                                                            uint16 Length,
                                                            Fee_30_SmallSector_JobType JobType)
{
  Fee_30_SmallSector_UserJobParameter.Blockid=Blockid;
  Fee_30_SmallSector_UserJobParameter.BlockNumber = BlockNumber;
  Fee_30_SmallSector_UserJobParameter.BlockOffset = BlockOffset;
  Fee_30_SmallSector_UserJobParameter.DataBufferPtr = DataBufferPtr;
  Fee_30_SmallSector_UserJobParameter.Length = Length;
  Fee_30_SmallSector_UserJobParameter.JobType = JobType;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetJobParameter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_SetJobParameter(void)
{
  Fee_30_SmallSector_ComponentParameter.Status = MEMIF_BUSY;
  Fee_30_SmallSector_ComponentParameter.JobResult = MEMIF_JOB_PENDING;

  Fee_30_SmallSector_SetFlagJobRequested(TRUE);
  Fee_30_SmallSector_SetFlagMainFunctionBusy(TRUE);
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_StartJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_StartJob(void)
{
  /* #10 TaskManager has to be initialized with every job in order to clear its service stack */
  Fee_30_SmallSector_Tm_Init();

  /* #20 DataHandlers have to be initialized in order to set values of current job */
  Fee_30_SmallSector_InitDataHandler();

  /* #30 Start requested job by initiating appropriate sub-component */
  Fee_30_SmallSector_StartLayer1Job();

  Fee_30_SmallSector_StateMachine = FEE_30_SMALLSECTOR_STATE_BUSY;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_CheckIdle()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_CheckIdle(void)
{
  return (Std_ReturnType) ((Fee_30_SmallSector_ComponentParameter.Status == MEMIF_IDLE) ? E_OK : E_NOT_OK);
}

#if (FEE_30_SMALLSECTOR_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  Fee_30_SmallSector_DetChkInit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_DetChkInit(void)
{
  return (Std_ReturnType) ((Fee_30_SmallSector_ComponentParameter.Status == MEMIF_UNINIT) ? E_NOT_OK : E_OK);
}


/**********************************************************************************************************************
 *  Fee_30_SmallSector_DetChkBlockNumberOk()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_DetChkBlockNumberOk(uint16 BlockNumber, uint8 ApiID)
{
  Std_ReturnType retVal;

  if ((BlockNumber == (uint16)FEE_30_SMALLSECTOR_RESERVED_BLOCK_NUMBER_1) ||
      (BlockNumber == (uint16)FEE_30_SMALLSECTOR_RESERVED_BLOCK_NUMBER_2))
  {
    retVal = E_NOT_OK;
  }
  /* #10 BlockIndex is zero based, thus (1u) has to be added to BlockIndex */
  else if ((Fee_30_SmallSector_Bh_GetBlockIndex(BlockNumber) + 1u) > FEE_30_SMALLSECTOR_NUMBER_OF_BLOCKS)
  {
    retVal = E_NOT_OK;
  }
  else if (ApiID == (uint8) FEE_30_SMALLSECTOR_SID_ERASE_IMMEDIATE_BLOCK)
  {
    /* #20 Erase immediate block API only works with immediate data blocks */
    retVal = ( (Fee_30_SmallSector_Bh_IsImmediateData(BlockNumber) == FALSE) ? E_NOT_OK : E_OK);
  }
  /* #30 Check that DatasetIndex is valid */
  else if (Fee_30_SmallSector_Bh_GetNrOfDatasets(BlockNumber) <= Fee_30_SmallSector_Bh_GetDatasetIndex(BlockNumber))
  {
    retVal = E_NOT_OK;
  }
  else
  {
    retVal = E_OK;
  }
  return retVal;
}


/**********************************************************************************************************************
 *  Fee_30_SmallSector_DetChkDataPointerOk()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_DetChkDataPointerOk(
        P2CONST(uint8, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) DataBufferPtr)
{
  return (Std_ReturnType) ((DataBufferPtr == NULL_PTR) ? E_NOT_OK : E_OK);
}


/**********************************************************************************************************************
 *  Fee_30_SmallSector_DetChkBlockOffsetOk()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_DetChkBlockOffsetOk(uint16 BlockNumber, uint16 BlockOffset)
{
  return (Std_ReturnType) ((BlockOffset >= Fee_30_SmallSector_Bh_GetDataLength(BlockNumber)) ? E_NOT_OK : E_OK);
}


/**********************************************************************************************************************
 *  Fee_30_SmallSector_DetChkBlockLengthOk()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL_INLINE FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_DetChkBlockLengthOk(uint16 BlockNumber,
        uint16 Length, uint16 BlockOffset)
{
  Std_ReturnType retVal;

  if(Length == 0u)
  {
    retVal = E_NOT_OK;
  }
  /* #10 It must be assured that data is only accessed within block bounds */
  else if( Fee_30_SmallSector_Bh_GetDataLength(BlockNumber) < (Length + BlockOffset) )
  {
    retVal = E_NOT_OK;
  }
  else
  {
    retVal = E_OK;
  }

  return (Std_ReturnType) retVal;
}
#endif


/**********************************************************************************************************************
 *  Fee_30_SmallSector_InitDataHandler()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_InitDataHandler(void)
{
  Fee_30_SmallSector_Ph_Init(Fee_30_SmallSector_UserJobParameter.BlockNumber);
  Fee_30_SmallSector_Bh_Init(Fee_30_SmallSector_UserJobParameter.BlockNumber, Fee_30_SmallSector_Ph_GetPartitionStartAddress());
  Fee_30_SmallSector_Dh_Init(Fee_30_SmallSector_UserJobParameter.BlockNumber, Fee_30_SmallSector_Bh_GetDataLength(Fee_30_SmallSector_UserJobParameter.BlockNumber), 
          Fee_30_SmallSector_Bh_GetNrOfInstances(Fee_30_SmallSector_UserJobParameter.BlockNumber), Fee_30_SmallSector_Bh_GetBlockStartAddress(), Fee_30_SmallSector_Ph_GetPartitionAddressAlignment());
} /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  Fee_30_SmallSector_ProcessStateMachine()
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
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_ProcessStateMachine(void)
{
  switch (Fee_30_SmallSector_StateMachine)
  {
    /**---------- STATE IDLE ----------------------------------------------------*/
    case FEE_30_SMALLSECTOR_STATE_IDLE:
      if (Fee_30_SmallSector_InternalFlags.CancelRequested == TRUE)
      {
        /* #5 Job requests were not yet processed, thus it is sufficient to clear the internal flag */
        Fee_30_SmallSector_SetFlagCancelRequested(FALSE);
      }
      else
      {
        /* #7 Requested job has to be started */
        Fee_30_SmallSector_StartJob();
        Fee_30_SmallSector_SetFlagJobRequested(FALSE);
      }

      break;

      /**---------- STATE BUSY ----------------------------------------------------*/
    case FEE_30_SMALLSECTOR_STATE_BUSY:
      if (Fee_30_SmallSector_InternalFlags.CancelRequested == TRUE)
      {
        Fee_30_SmallSector_Tm_CancelTasks();

        /* #10 If no new job was requested during cancellation, MainFunctionBusy flag has to be cleared */
        if (Fee_30_SmallSector_InternalFlags.JobRequested == FALSE)
        {
          Fee_30_SmallSector_SetFlagMainFunctionBusy(FALSE);
        }

        Fee_30_SmallSector_StateMachine = FEE_30_SMALLSECTOR_STATE_IDLE;
        Fee_30_SmallSector_SetFlagCancelRequested(FALSE);
      }
      else
      {
        if (Fee_30_SmallSector_Fls_GetStatus() == MEMIF_IDLE)
        {
          /* #20 Process sub-components */
          Fee_30_SmallSector_Tm_ExecuteTask();

          /* #25 Check if job is finished and if there was no cancel request while job processing*/
          if ((Fee_30_SmallSector_GetLayer1Status() == MEMIF_IDLE) && (Fee_30_SmallSector_InternalFlags.CancelRequested == FALSE)) /* COV_FEE_30_SMALLSECTOR_NO_CODE_INSTRUMENTATION */
          {
            Fee_30_SmallSector_FinishJob(Fee_30_SmallSector_GetLayer1JobResult());
          }
        }
      }
      break;
    default: /* COV_FEE_30_SMALLSECTOR_MISRA */
      break;
  }
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_FinishJob()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_FinishJob(MemIf_JobResultType JobResult)
{
  /* #10 Reset local parameters upon job finish */
  Fee_30_SmallSector_SetFlagMainFunctionBusy(FALSE);
  Fee_30_SmallSector_StateMachine = FEE_30_SMALLSECTOR_STATE_IDLE;

  /* #15 Global job result and status need to be updated before callback services are called */
  Fee_30_SmallSector_ComponentParameter.JobResult = JobResult;
  Fee_30_SmallSector_ComponentParameter.Status = MEMIF_IDLE;

  /* #20 Depending on configuration, job finish is reported to upper layer via callback hooks */
#if (FEE_30_SMALLSECTOR_NVM_POLLING_MODE == STD_OFF)
  if (JobResult == MEMIF_JOB_OK)
  {
    Fee_30_SmallSector_CbkJobEndNotification(); /* SBSW_FEE_30_SMALLSECTOR_05 */
  }
  else
  {
    Fee_30_SmallSector_CbkJobErrorNotification(); /* SBSW_FEE_30_SMALLSECTOR_05 */
  }
#endif

}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Init(void)
{
  Fee_30_SmallSector_ComponentParameter.JobResult = MEMIF_JOB_OK;
  Fee_30_SmallSector_ComponentParameter.Status = MEMIF_IDLE;

  Fee_30_SmallSector_StateMachine = FEE_30_SMALLSECTOR_STATE_IDLE;

  Fee_30_SmallSector_SetFlagMainFunctionBusy(FALSE);
  Fee_30_SmallSector_SetFlagJobRequested(FALSE);
  Fee_30_SmallSector_SetFlagCancelRequested(FALSE);

  /* #10 Initialize FEE's sub-components */
  Fee_30_SmallSector_Rd_Init();
  Fee_30_SmallSector_Wr_Init();

 // Fee_30_SmallSector_If_Init();
 // Fee_30_SmallSector_De_Init();
  //Fee_30_SmallSector_WrInst_Init();

  //Fee_30_SmallSector_RdMgmt_Init();
} /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Read()
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
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Read(uint16 Blockid,uint16 BlockNumber, uint16 BlockOffset,
    Fee_30_SmallSector_VarDataPtrType DataBufferPtr,uint16 Length)
{
  /* ----- Local Variables -----------------------------------------------------------------------------*/
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = FEE_30_SMALLSECTOR_E_NO_ERROR;



  {
    /* ----- Implementation ------------------------------------------------------------------------------*/
    Fee_30_SmallSector_SetUserParameter(Blockid,BlockNumber, BlockOffset, DataBufferPtr, Length, FEE_30_SMALLSECTOR_READ_JOB); /* SBSW_FEE_30_SMALLSECTOR_03 */
    Fee_30_SmallSector_SetJobParameter();

    retVal = E_OK;
  }
  /* ----- Development Error Report --------------------------------------------------------------------*/
  /* #70 Report development error if any occurred */
#if (FEE_30_SMALLSECTOR_DEV_ERROR_REPORT == STD_ON)
  if (errorId != FEE_30_SMALLSECTOR_E_NO_ERROR)
  {
    (void)Det_ReportError(FEE_30_SMALLSECTOR_MODULE_ID, FEE_30_SMALLSECTOR_INSTANCE_ID, FEE_30_SMALLSECTOR_SID_READ, errorId);
  }
#else
  FEE_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
/* Fee_30_SmallSector_Read */



/**********************************************************************************************************************
 *  Fee_30_SmallSector_Write()
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
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Write(uint16 Blockid,uint16 BlockNumber, Fee_30_SmallSector_VarDataPtrType DataBufferPtr)
{
  /* ----- Local Variables -----------------------------------------------------------------------------*/
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = FEE_30_SMALLSECTOR_E_NO_ERROR;


  {
    /* ----- Implementation ------------------------------------------------------------------------------*/
    Fee_30_SmallSector_SetUserParameter(Blockid,BlockNumber, 0x0000U, DataBufferPtr, Fee_30_SmallSector_Bh_GetDataLength(BlockNumber), FEE_30_SMALLSECTOR_WRITE_JOB); /* SBSW_FEE_30_SMALLSECTOR_03 */
    Fee_30_SmallSector_SetJobParameter();

    retVal = E_OK;
  }
  /* ----- Development Error Report --------------------------------------------------------------------*/
  /* #60 Report development error if any occurred */
#if (FEE_30_SMALLSECTOR_DEV_ERROR_REPORT == STD_ON)
  if (errorId != FEE_30_SMALLSECTOR_E_NO_ERROR)
  {
    (void)Det_ReportError(FEE_30_SMALLSECTOR_MODULE_ID, FEE_30_SMALLSECTOR_INSTANCE_ID, FEE_30_SMALLSECTOR_SID_WRITE, errorId);
  }
#else
  FEE_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */
/* Fee_30_SmallSector_Write */



/**********************************************************************************************************************
 *  Fee_30_SmallSector_InvalidateBlock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_InvalidateBlock(uint16 Blockid,uint16 BlockNumber)
{
  /* ----- Local Variables -----------------------------------------------------------------------------*/
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = FEE_30_SMALLSECTOR_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------------------------------------*/
#if (FEE_30_SMALLSECTOR_DEV_ERROR_DETECT == STD_ON)

  /* ----- UNINIT CHECK --------------------------------------------------------------------------------*/
  /* #10 Perform Uninitialized check */
  if (Fee_30_SmallSector_DetChkInit() == E_NOT_OK)
  {
    errorId = FEE_30_SMALLSECTOR_E_UNINIT;
  }
  else
  /* ----- INVALID BLOCK NO CHECK ----------------------------------------------------------------------*/
  /* #20 Perform Invalid Block Number check */
  if (Fee_30_SmallSector_DetChkBlockNumberOk(BlockNumber, FEE_30_SMALLSECTOR_SID_INVALIDATE_BLOCK) == E_NOT_OK)
  {
    errorId = FEE_30_SMALLSECTOR_E_INVALID_BLOCK_NO;
  }
  else

#endif /* FEE_30_SMALLSECTOR_DEV_ERROR_DETECT */

  /* ----- BUSY CHECK ----------------------------------------------------------------------------------*/
  /* #30 Perform Busy check. At this point "Not-Idle" is equal to "Busy" since "Busy-internal" is not used */
  if (Fee_30_SmallSector_CheckIdle() == E_NOT_OK)
  {
    errorId = FEE_30_SMALLSECTOR_E_BUSY;
  }
  else
  {
    /* ----- Implementation ------------------------------------------------------------------------------*/
    Fee_30_SmallSector_SetUserParameter(Blockid,BlockNumber, 0x0000U, NULL_PTR, 0x0000U, FEE_30_SMALLSECTOR_INVALIDATE_JOB); /* SBSW_FEE_30_SMALLSECTOR_04 */
    Fee_30_SmallSector_SetJobParameter();

    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------------------------------------*/
  /* #40 Report development error if any occurred */
#if (FEE_30_SMALLSECTOR_DEV_ERROR_REPORT == STD_ON)
  if (errorId != FEE_30_SMALLSECTOR_E_NO_ERROR)
  {
    (void)Det_ReportError(FEE_30_SMALLSECTOR_MODULE_ID, FEE_30_SMALLSECTOR_INSTANCE_ID, FEE_30_SMALLSECTOR_SID_INVALIDATE_BLOCK, errorId);
  }
#else
  FEE_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
}
/* Fee_30_SmallSector_InvalidateBlock */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_EraseImmediateBlock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_EraseImmediateBlock(uint16 Blockid,uint16 BlockNumber)
{
  /* ----- Local Variables -----------------------------------------------------------------------------*/
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = FEE_30_SMALLSECTOR_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------------------------------------*/
#if (FEE_30_SMALLSECTOR_DEV_ERROR_DETECT == STD_ON)

  /* ----- UNINIT CHECK --------------------------------------------------------------------------------*/
  /* #10 Perform Uninitialized check */
  if (Fee_30_SmallSector_DetChkInit() == E_NOT_OK)
  {
    errorId = FEE_30_SMALLSECTOR_E_UNINIT;
  }
  else
  /* ----- INVALID BLOCK NO CHECK ----------------------------------------------------------------------*/
  /* #30 Perform Invalid Block Number check */
  if (Fee_30_SmallSector_DetChkBlockNumberOk(BlockNumber, FEE_30_SMALLSECTOR_SID_ERASE_IMMEDIATE_BLOCK) == E_NOT_OK)
  {
    errorId = FEE_30_SMALLSECTOR_E_INVALID_BLOCK_NO;
  }
  else

#endif /* FEE_30_SMALLSECTOR_DEV_ERROR_DETECT */

  /* ----- BUSY CHECK ----------------------------------------------------------------------------------*/
  /* #40 Perform Busy check. At this point "Not-Idle" is equal to "Busy" since "Busy-internal" is not used */
  if (Fee_30_SmallSector_CheckIdle() == E_NOT_OK)
  {
    errorId = FEE_30_SMALLSECTOR_E_BUSY;
  }
  else
  {
  /* ----- Implementation ------------------------------------------------------------------------------*/
    Fee_30_SmallSector_SetUserParameter(Blockid,BlockNumber, 0x0000U, NULL_PTR, 0x0000U, FEE_30_SMALLSECTOR_ERASE_JOB); /* SBSW_FEE_30_SMALLSECTOR_04 */
    Fee_30_SmallSector_SetJobParameter();

    retVal = E_OK;
  }
  /* ----- Development Error Report --------------------------------------------------------------------*/
  /* #50 Report development error if any occurred */
#if (FEE_30_SMALLSECTOR_DEV_ERROR_REPORT == STD_ON)
  if (errorId != FEE_30_SMALLSECTOR_E_NO_ERROR)
  {
    (void)Det_ReportError(FEE_30_SMALLSECTOR_MODULE_ID, FEE_30_SMALLSECTOR_INSTANCE_ID, FEE_30_SMALLSECTOR_SID_ERASE_IMMEDIATE_BLOCK, errorId);
  }
#else
  FEE_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
}
/* Fee_30_SmallSector_EraseImmediateBlock */



/**********************************************************************************************************************
 *  Fee_30_SmallSector_Cancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Cancel(void)
{
  /* ----- Local Variables -----------------------------------------------------------------------------*/
  uint8 errorId = FEE_30_SMALLSECTOR_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------------------------------------*/
#if (FEE_30_SMALLSECTOR_DEV_ERROR_DETECT == STD_ON)

  /* ----- UNINIT CHECK --------------------------------------------------------------------------------*/
  /* #10 Perform Uninitialized check */
  if (Fee_30_SmallSector_DetChkInit() == E_NOT_OK)
  {
    errorId = FEE_30_SMALLSECTOR_E_UNINIT;
  }
  else

#endif /* FEE_30_SMALLSECTOR_DEV_ERROR_DETECT */

  /* ----- IDLE CHECK --------------------------------------------------------------------------------*/
  /* #20 Perform invalid cancel check */
  if (Fee_30_SmallSector_CheckIdle() == E_OK)
  {
    errorId = FEE_30_SMALLSECTOR_E_INVALID_CANCEL;
  }
  else
  {
    /* ----- Implementation ------------------------------------------------------------------------------*/
    Fee_30_SmallSector_SetFlagCancelRequested(TRUE);
    Fee_30_SmallSector_SetFlagJobRequested(FALSE);

    Fee_30_SmallSector_ComponentParameter.JobResult = MEMIF_JOB_CANCELED;
    Fee_30_SmallSector_ComponentParameter.Status = MEMIF_IDLE;
  }

  /* ----- Development Error Report --------------------------------------------------------------------*/
  /* #30 Report development error if any occurred */
#if (FEE_30_SMALLSECTOR_DEV_ERROR_REPORT == STD_ON)
  if (errorId != FEE_30_SMALLSECTOR_E_NO_ERROR)
  {
    (void)Det_ReportError(FEE_30_SMALLSECTOR_MODULE_ID, FEE_30_SMALLSECTOR_INSTANCE_ID, FEE_30_SMALLSECTOR_SID_CANCEL, errorId);
  }
#else
  FEE_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
}
/* Fee_30_SmallSector_Cancel */


/**********************************************************************************************************************
 *  Fee_30_SmallSector_GetStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_GetStatus(void)
{
  return Fee_30_SmallSector_ComponentParameter.Status;
}
/* Fee_30_SmallSector_GetStatus */


/**********************************************************************************************************************
 *  Fee_30_SmallSector_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_GetJobResult(void)
{
  /* ----- Local Variables -----------------------------------------------------------------------------*/
  MemIf_JobResultType retVal;
  uint8 errorId = FEE_30_SMALLSECTOR_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------------------------------------*/
#if (FEE_30_SMALLSECTOR_DEV_ERROR_DETECT == STD_ON)

  /* ----- UNINIT CHECK --------------------------------------------------------------------------------*/
  /* #10 Perform Uninitialized check */
  if (Fee_30_SmallSector_DetChkInit() == E_NOT_OK)
  {
    errorId = FEE_30_SMALLSECTOR_E_UNINIT;
    retVal = MEMIF_JOB_FAILED;
  }
  else

#endif /* FEE_30_SMALLSECTOR_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ------------------------------------------------------------------------------*/

    retVal = Fee_30_SmallSector_ComponentParameter.JobResult;

  }
  /* ----- Development Error Report --------------------------------------------------------------------*/
  /* #20 Report development error if any occurred */
#if (FEE_30_SMALLSECTOR_DEV_ERROR_REPORT == STD_ON)
  if (errorId != FEE_30_SMALLSECTOR_E_NO_ERROR)
  {
    (void)Det_ReportError(FEE_30_SMALLSECTOR_MODULE_ID, FEE_30_SMALLSECTOR_INSTANCE_ID, FEE_30_SMALLSECTOR_SID_GET_JOB_RESULT, errorId);
  }
#else
  FEE_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

  return retVal;
}
/* Fee_30_SmallSector_GetJobResult */


#if (FEE_30_SMALLSECTOR_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Fee_30_SmallSector_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) VersionInfoPtr)
{
  /* ----- Local Variables -----------------------------------------------------------------------------*/
  uint8 errorId = FEE_30_SMALLSECTOR_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------------------------------------*/
# if (FEE_30_SMALLSECTOR_DEV_ERROR_DETECT == STD_ON) /* COV_FEE_30_SMALLSECTOR_DET_NEVER_ON */

  /* ----- VERSION POINTER CHECK ------------------------------------------------------------------------*/
  /* #10 Perform Version Pointer check */
  if (VersionInfoPtr == NULL_PTR)
  {
    errorId = FEE_30_SMALLSECTOR_E_INVALID_DATA_POINTER;
  }
  else

# endif /* FEE_30_SMALLSECTOR_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ------------------------------------------------------------------------------*/

    VersionInfoPtr->vendorID = FEE_30_SMALLSECTOR_VENDOR_ID; /* SBSW_FEE_30_SMALLSECTOR_01 */
    VersionInfoPtr->moduleID = FEE_30_SMALLSECTOR_MODULE_ID; /* SBSW_FEE_30_SMALLSECTOR_01 */

    VersionInfoPtr->sw_major_version = FEE_30_SMALLSECTOR_SW_MAJOR_VERSION; /* SBSW_FEE_30_SMALLSECTOR_01 */
    VersionInfoPtr->sw_minor_version = FEE_30_SMALLSECTOR_SW_MINOR_VERSION; /* SBSW_FEE_30_SMALLSECTOR_01 */
    VersionInfoPtr->sw_patch_version = FEE_30_SMALLSECTOR_SW_PATCH_VERSION; /* SBSW_FEE_30_SMALLSECTOR_01 */

  }
  /* ----- Development Error Report --------------------------------------------------------------------*/
  /* #20 Report development error if any occurred */
#if (FEE_30_SMALLSECTOR_DEV_ERROR_REPORT == STD_ON) /* COV_FEE_30_SMALLSECTOR_DET_NEVER_ON */
  if (errorId != FEE_30_SMALLSECTOR_E_NO_ERROR)
  {
    (void)Det_ReportError(FEE_30_SMALLSECTOR_MODULE_ID, FEE_30_SMALLSECTOR_INSTANCE_ID, FEE_30_SMALLSECTOR_SID_GET_VERSION_INFO, errorId);
  }
#else
  FEE_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif
}
/* Fee_30_SmallSector_GetVersionInfo */
#endif /* FEE_30_SMALLSECTOR_VERSION_INFO_API */


/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_SetMode(MemIf_ModeType Mode)
{
  /* #10 Implementation intentionally left empty - See design decisions */
  FEE_DUMMY_STATEMENT(Mode); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/**********************************************************************************************************************
 *  Fee_30_SmallSector_SuspendWrites()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_SuspendWrites (void)
{
  /* #10 Force Layer 1 Write sub-component to pause all kind of write jobs */
  Fee_30_SmallSector_Wr_SuspendWrites();
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_ResumeWrites()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_ResumeWrites (void)
{
  /* #10 Force Layer 1 Write sub-component to resume all kind of write jobs */
  Fee_30_SmallSector_Wr_ResumeWrites();
}


#if (FEE_30_SMALLSECTOR_FLS_POLLING_MODE == STD_OFF)
/**********************************************************************************************************************
 *  Fee_30_SmallSector_JobEndNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_JobEndNotification(void)
{
  Fee_30_SmallSector_Fls_SetCurrentFlsJobResult();
}
/* Fee_30_SmallSector_JobEndNotification */

/**********************************************************************************************************************
 *  Fee_30_SmallSector_JobErrorNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_JobErrorNotification(void)
{
  Fee_30_SmallSector_Fls_SetCurrentFlsJobResult();
}
/* Fee_30_SmallSector_JobErrorNotification */
#endif

/**********************************************************************************************************************
 *  Fee_30_SmallSector_MainFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_MainFunction (void)
{
  /* ----- Local Variables -----------------------------------------------------------------------------*/
  uint8 errorId = FEE_30_SMALLSECTOR_E_NO_ERROR;


  /* ----- Development Error Checks --------------------------------------------------------------------*/
#if (FEE_30_SMALLSECTOR_DEV_ERROR_DETECT == STD_ON)

  /* ----- UNINIT CHECK --------------------------------------------------------------------------------*/
  /* #10 Perform Uninitialized check */
  if (Fee_30_SmallSector_DetChkInit() == E_NOT_OK)
  {
    errorId = FEE_30_SMALLSECTOR_E_UNINIT;
  }
  else

#endif /* FEE_30_SMALLSECTOR_DEV_ERROR_DETECT */
  {
  /* ----- Implementation ------------------------------------------------------------------------------*/
    /* #20 MainFunction is only processed if it's busy */
    if(Fee_30_SmallSector_InternalFlags.MainFunctionBusy == TRUE)
    {
        Fee_30_SmallSector_ProcessStateMachine();
    }
  }
  /* ----- Development Error Report --------------------------------------------------------------------*/
  /* #30 Report development error if any occurred */
#if (FEE_30_SMALLSECTOR_DEV_ERROR_REPORT == STD_ON)
  if (errorId != FEE_30_SMALLSECTOR_E_NO_ERROR)
  {
    (void)Det_ReportError(FEE_30_SMALLSECTOR_MODULE_ID, FEE_30_SMALLSECTOR_INSTANCE_ID, FEE_30_SMALLSECTOR_SID_MAINFUNCTION, errorId);
  }
#else
  FEE_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
#endif

}
/* Fee_30_SmallSector_MainFunction */


/**********************************************************************************************************************
  Fee_30_SmallSector_AlignValue()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (uint32, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_AlignValue(uint32 Value, uint16 Alignment)
{
  uint32 retVal;

  /* #10 Aligns Value to Alignment */
  if ((Value % Alignment) == 0u)
  {
    retVal = Value;
  }
  else
  {
    /* #20 If Value is not aligned, next greater value is returned which is aligned to Alignment */
    retVal = ((Value / Alignment) + 1u) * Alignment;
  }

  return retVal;
}

#define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA L:LongInfixName */


/* Justification for module-specific MISRA deviations:
 *
 MD_FEE_30_SMALLSECTOR_RightHandOperand: rule 13.5
     Reason:      Right hand operand of '&&' or '||' is a function which is not necessarily called and consequently may lead to side effects.
     Risk:        No risk. The right hand operand of '&&' or '||' does not have any side effects. It's only a query.
     Prevention:  None necessary. Functions in right hand operand are only queries which do not necessarily have to be called.

 MD_FEE_30_SMALLSECTOR_SideEffects: rule 2.2
     Reason:      The function sets a global variable of the flash driver interface when polling mode is disabled and therefore has side effects.
     Risk:        No risk.
     Prevention:  Program flow has been verified by component tests and review.
*/


/* START_COVERAGE_JUSTIFICATION
    \ID COV_FEE_30_SMALLSECTOR_NO_CODE_INSTRUMENTATION
    \ACCEPT TF tf tx
    \REASON Condition "Fee_30_SmallSector_InternalFlags.CancelRequested == FALSE" is never false in TscStandard.
            Condition can only be true in case Fee_30_SmallSector_Cancel() service is called while Layer1 sub-component was executed
            for the LAST time. It is not possible to force this cancel without instrumenting the source code.

    \ID COV_FEE_30_SMALLSECTOR_DET_NEVER_ON
    \ACCEPT TX
    \REASON Due to low complexity there is no separate configuration with GetVersionInfo API enabled and DET
            (Detection and Reporting) disabled.

    \ID COV_FEE_30_SMALLSECTOR_INTERNAL_SERVICE
    \ACCEPT TX
    \REASON Function Fee_30_SmallSector_AlignValue shall only be accessed by module internal sub-components.
            This condition is never false, since only FEE and its sub-components are considered within
            variant coverage analysis.

    \ID COV_FEE_30_SMALLSECTOR_MISRA
    \ACCEPT XX
    \REASON [MSR_COV_MISRA]

    \ID COV_FEE_30_SMALLSECTOR_COMPATIBILITY
    \ACCEPT XF
    \ACCEPT TX
    \REASON [COV_MSR_COMPATIBILITY]
END_COVERAGE_JUSTIFICATION */


/* SBSW_JUSTIFICATION_BEGIN
   \ID SBSW_FEE_30_SMALLSECTOR_01
    \DESCRIPTION The function Fee_30_SmallSector_GetVersionInfo writes to the object referenced by parameter VersionInfoPtr.
                 Additionally, VersionInfoPtr is checked if it's valid.
    \COUNTERMEASURE \N The caller ensures that the pointer passed to the parameters VersionInfoPtr is valid.

   \ID SBSW_FEE_30_SMALLSECTOR_02
    \DESCRIPTION Fee_30_SmallSector_UserJobParameter structure contains pointer to data buffer (DataBufferPtr), which was passed by
                 caller of FEE component.
    \COUNTERMEASURE \N The caller of FEE ensures that the pointers passed to public APIs (e.g. Read, Write) are valid.
                       DataBufferPtr which is contained in Fee_30_SmallSector_UserJobParameter structure is always initialized in an
                       asynchronous API service before being used in Fee_30_SmallSector_MainFunction. Fee_30_SmallSector_MainFunction is only processed
                       if any asynchronous job is pending.

   \ID SBSW_FEE_30_SMALLSECTOR_03
    \DESCRIPTION DataBufferPtr, which points to data array of caller, is passed to local function.
    \COUNTERMEASURE \N The caller ensures that the pointer passed to the public APIs is valid.

   \ID SBSW_FEE_30_SMALLSECTOR_04
    \DESCRIPTION NULL_PTR is passed to local function Fee_30_SmallSector_SetUserParameter in Fee_30_SmallSector_InvalidateBlock() and
                 Fee_30_SmallSector_EraseImmediateBlock() API.
    \COUNTERMEASURE \N Local structure Fee_30_SmallSector_UserJobParameter is initialized with values passed to
                       function Fee_30_SmallSector_SetUserParameter. Structure member DataBufferPtr is initialized with NULL_PTR
                       in case Fee_30_SmallSector_InvalidateBlock() or Fee_30_SmallSector_EraseImmediateBlock() API is called.
                       That's because DataBufferPtr is not used if an invalidate or erase job is requested but still a value
                       needs to be provided to Fee_30_SmallSector_SetUserParameter.

   \ID SBSW_FEE_30_SMALLSECTOR_05
    \DESCRIPTION Callback function of NvM component is called via function pointer
    \COUNTERMEASURE \S Verify that valid notification routines are provided for 'FeeNvmJobEndNotification' and
                       'FeeNvmJobErrorNotification'. SMI-1292
SBSW_JUSTIFICATION_END */
