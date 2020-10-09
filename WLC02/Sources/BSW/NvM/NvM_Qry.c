/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NvM_Qry.c
 *      Project:  MemService_AsrNvM
 *       Module:  NvM - Submodule Qry (Query functions)
 *    Generator:  -
 *
 *  Description:  This sub-module implements the queries to be executed to evaluate
 *                the conditions for a state transition
 *
 *********************************************************************************************************************/

/* Do not modify this file! */

/**********************************************************************************************************************
 *  MODULE SWITCH
 *********************************************************************************************************************/
#define NVM_QRY_SOURCE

/* PRQA S 5087 inclusions */ /* MD_MSR_19.1 */
/* PRQA S 0857 macros */ /* MD_MSR_1.1_857 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  INCLUDE OF CONFIGURATION (PUBLIC SECTION)
 *********************************************************************************************************************/
#include "NvM_Cfg.h"
#include "NvM_PrivateCfg.h"

/**********************************************************************************************************************
 *  INCLUDE OF THE CENTRAL INTERNAL INCLUDE
 *********************************************************************************************************************/
#include "NvM_JobProc.h"

/**********************************************************************************************************************
 *  MODULE HEADER INCLUDES
 *********************************************************************************************************************/
#include "NvM_Qry.h"

/**********************************************************************************************************************
 *  INCLUDE OF THE QUEUE VARIABLES
 *********************************************************************************************************************/
#include "NvM_Queue.h"

/**********************************************************************************************************************
 *  INCLUDE OF THE CRC VARIABLES
 *********************************************************************************************************************/
#include "NvM_Crc.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if ((NVM_QRY_MAJOR_VERSION != (5u)) \
        || (NVM_QRY_MINOR_VERSION != (8u)))
# error "Version numbers of NvM_Qry.c and NvM_Qry.h are inconsistent!"
#endif

#if ((NVM_CFG_MAJOR_VERSION != (5u)) \
        || (NVM_CFG_MINOR_VERSION != (8u)))
# error "Version numbers of NvM_Qry.c and NvM_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  INTERNAL MACROS
 **********************************************************************************************************************/
#ifndef NVM_LOCAL /* COV_NVM_COMPATIBILITY */
# define NVM_LOCAL static
#endif

/**********************************************************************************************************************
 *  INTERNAL FORWARD DECLARATIONS
 **********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 * NvM_QryBlockWriteAll
 *********************************************************************************************************************/
/*! \brief Check if the block shall be written during NvM_WriteAll().
 *  \details Check if the block shall be written during NvM_WriteAll().
 *  \return TRUE block shall be written during WriteAll
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryBlockWriteAll(void);

/**********************************************************************************************************************
 * NvM_QryCancelWriteAll
 *********************************************************************************************************************/
/*! \brief Checks whether a NvM_CancelWriteAll request was setup.
 *  \details Checks whether a NvM_CancelWriteAll request was setup.
 *  \return TRUE CancelWriteAll setup
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCancelWriteAll(void);

#if (NVM_KILL_WRITEALL_API == STD_ON)
/**********************************************************************************************************************
 * NvM_QryWriteAllKilled
 *********************************************************************************************************************/
/*! \brief Checks whether a NvM_KillWriteAll request was setup.
 *  \details Checks whether a NvM_KillWriteAll request was setup.
 *  \return TRUE KillWriteAll setup
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config KillWriteAll is enabled
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteAllKilled(void);
#endif /* (NVM_KILL_WRITEALL_API == STD_ON) */

/**********************************************************************************************************************
 * NvM_QryCrcMatch
 *********************************************************************************************************************/
/*! \brief Check whether the recalculated Crc matches the read one, in case the is a configured Crc.
 *  \details Check whether the recalculated Crc matches the read one, in case the is a configured Crc.
 *  \return TRUE Crc matches
 *  \return FALSE no Crc configured or the Crc does not match
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcMatch(void);

/**********************************************************************************************************************
 * NvM_QryCrcBusy
 *********************************************************************************************************************/
/*! \brief Checks the current block CRC calculation state.
 *  \details -
 *  \return TRUE if the CRC is busy, FALSE otherwise.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcBusy(void);

/**********************************************************************************************************************
 * NvM_QryDataCopyBusy
 *********************************************************************************************************************/
/*!
 * \brief       Checks the current block's ByteCount value.
 * \details     -
 * \return      TRUE, if ByteCount > 0, FALSE otherwise.
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 * \pre         -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryDataCopyBusy(void);

/**********************************************************************************************************************
 * NvM_QryLastBlockDone_ReadAll
 *********************************************************************************************************************/
/*! \brief Check whether the NvM_ReadAll job is finished.
 *  \details Check whether the NvM_ReadAll job is finished.
 *  \return TRUE NvM_ReadAll job is finished
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_ReadAll(void);

/**********************************************************************************************************************
 * NvM_QryLastBlockDone_WriteAll
 *********************************************************************************************************************/
/*! \brief Checks whether the NvM_WriteAll job is finished.
 *  \details Checks whether the NvM_WriteAll job is finished.
 *  \return TRUE WriteAll job is finished
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_WriteAll(void);

/**********************************************************************************************************************
 * NvM_QryLastResultOk
 *********************************************************************************************************************/
/*! \brief Checks whether the last MemIf job was successful.
 *  \details Checks whether the last MemIf job was successful.
 *  \return TRUE last MemIf job was successful
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastResultOk(void);

/**********************************************************************************************************************
 * NvM_QryMainFsmRunning
 *********************************************************************************************************************/
/*! \brief Checks whether the main-FSM is currently pending.
 *  \details Checks whether the main-FSM is currently pending.
 *  \return TRUE main-FSM is pending
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMainFsmRunning(void);

/**********************************************************************************************************************
 * NvM_QryMultiJob
 *********************************************************************************************************************/
/*! \brief Checks whether a multi block job is requested.
 *  \details Checks whether a multi block job is requested.
 *  \return TRUE multi block job is setup
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMultiJob(void);

/**********************************************************************************************************************
 * NvM_QryNvBusy
 *********************************************************************************************************************/
/*! \brief Checks whether the underlying module for current job is busy.
 *  \details we differ between polling mode on and off: in case we are running in polling mode and the corresponding
 *           underlying module is not busy, we set the current job result, too. In case we are running with polling
 *           mode off, we set the job to pending - the underlying module has to invoke the corresponding job-end or
 *           job-error callback to signal a finished job.
 *  \return TRUE underlying module is busy
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNvBusy(void);

/**********************************************************************************************************************
 * NvM_QryMemHwaBusy
 *********************************************************************************************************************/
/*! \brief Check whether the underlying modules are busy.
 *  \details Check whether the underlying modules are busy.
 *  \return TRUE at least one underlying module is busy
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMemHwaBusy(void);

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
/**********************************************************************************************************************
 * NvM_QryRamValid
 *********************************************************************************************************************/
/*! \brief Test if the RAM of the block is still valid or if the block is locked - i.e. Read during ReadAll
 *  \details Test if the RAM of the block is still valid or if the block is locked - i.e. Read during ReadAll
 *  \return TRUE RAM is valid and not locked
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRamValid(void);
#endif /* (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) */

/**********************************************************************************************************************
 * NvM_QryRedundantBlock
 *********************************************************************************************************************/
/*! \brief Test if the current block has been configured redundant, and the redundant NV block is not selected.
 *  \details Test if the current block has been configured redundant, and the redundant NV block is not selected.
 *  \return TRUE redundant block
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRedundantBlock(void);

/**********************************************************************************************************************
 * NvM_QrySkipBlock
 *********************************************************************************************************************/
/*! \brief Checks whether the block is not selected for NvM_ReadAll-job or it isn't a dataset block (shall be skipped)
 *  \details Checks whether the block is not selected for NvM_ReadAll-job or it isn't a dataset block (shall be skipped)
 *  \return TRUE block shall be skipped
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySkipBlock(void);

/**********************************************************************************************************************
 * NvM_QrySubFsmRunning
 *********************************************************************************************************************/
/*! \brief Checks whether the sub-FSM is currently pending.
 *  \details Checks whether the sub-FSM is currently pending.
 *  \return TRUE sub-FSM is pending
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySubFsmRunning(void);

/**********************************************************************************************************************
 * NvM_QryTrue
 *********************************************************************************************************************/
/*! \brief Simply returns TRUE.
 *  \details Simply returns TRUE.
 *  \return always TRUE
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryTrue(void);

/**********************************************************************************************************************
 * NvM_QryWriteBlockOnce
 *********************************************************************************************************************/
/*! \brief Checks whether the block is a write once block.
 *  \details Checks whether the block is a write once block.
 *  \return TRUE in case the current block is write once
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteBlockOnce(void);

/**********************************************************************************************************************
 * NvM_QryWriteRetriesExceeded
 *********************************************************************************************************************/
/*! \brief Checks whether the current number of write retries do not exceed the allowed boundary.
 *  \details Checks whether the current number of write retries do not exceed the allowed boundary.
 *  \return FALSE in case the write retries counter exceeded
 *  \return TRUE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteRetriesExceeded(void);

#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
/**********************************************************************************************************************
 * NvM_QryHasRom
 *********************************************************************************************************************/
/*! \brief Checks whether the current block has defaults (ROM block or Init callback)
 *  \details Checks whether the current block has defaults (ROM block or Init callback)
 *  \return FALSE block has no defaults
 *  \return TRUE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHasRom(void);

/**********************************************************************************************************************
 * NvM_QryExtRuntime
 *********************************************************************************************************************/
/*! \brief Checks whether for current block the extended runtime preparation shall be executed.
 *  \details Checks whether for current block the extended runtime preparation shall be executed.
 *  \return FALSE normal runtime preparation shall be executed
 *  \return TRUE extended runtime preparation shall be executed
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \config Dynamic configuration handling is enabled
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryExtRuntime(void);
#endif /* (NVM_DYNAMIC_CONFIGURATION == STD_ON) */

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
/**********************************************************************************************************************
 * NvM_QrySuspendRepairRedundantBlocks
 *********************************************************************************************************************/
/*!
 * \brief Checks whether the pending background repair redundant blocks job shall be suspended (non-Destructively) or not.
 * \details Since the redundant block repairing is a background job, it can be suspended in a non-destructive way 
 *          by all possible jobs - single or multi block. This query checks whether there is a normal priority job,
 *          or multi block job (ReadAll or WriteAll). It does not care about the high priority jobs - NvM handles this itself.
 * \return FALSE 
 * \return TRUE 
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \config Repair Redundant Blocks Api is enabled
 * \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySuspendRepairRedundantBlocks(void);

/**********************************************************************************************************************
 * NvM_QryRepairRedBlockDefect
 *********************************************************************************************************************/
/*!
 * \brief Checks whether current redundant block can and shall be repaired or not.
 * \details We decide between three situations:
 *          1. both blocks are valid, nothing to repair
 *          2. both blocks are defect, NvM cannot repair
 *          3. only one block is defect, NvM will try to repair the redundancy
 * \return FALSE block does not have to be repaired or cannot be repaired
 * \return TRUE  block is defect and shall be repaired
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \config Repair Redundant Blocks Api is enabled
 * \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRepairRedBlockDefect(void);
#endif

/**********************************************************************************************************************
 * NvM_QryCRCCompMechanismSkipWrite
 *********************************************************************************************************************/
/*!
 * \brief Checks whether the block writing shall be skipped because of CRCCompMechanism and clean block.
 * \details -
 * \return TRUE  if the block shall be skipped
 * \return FALSE if the block shall not be skipped
 * \context TASK
 * \reentrant FALSE
 * \synchronous TRUE
 * \config -
 * \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCRCCompMechanismSkipWrite(void);

/**********************************************************************************************************************
 * NvM_QryPostReadTransform
 *********************************************************************************************************************/
/*!
 * \brief       Invokes the post read transformation callback with the read data and returns its result.
 * \details     Within post read transformation the user can decide whether the data is valid or not - in case it isn't
 *              NvM shall behave same as in case the CRC does not match or there is no data.
 * \return      TRUE, if the post read transformation callback returns OK, or is not configured; FALSE otherwise
 * \pre         -
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryPostReadTransform(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"
/**********************************************************************************************************************
 *  INTERNAL MODULE GLOBAL VARIABLES
 *********************************************************************************************************************/

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* the query function table, indexed by NvM_StateQueryType */
CONST(NvM_QryFctPtrType, NVM_PRIVATE_CONST) NvM_QueryTable_ap[NVM_QRY_ID_TRUE + 1] =
{
    NvM_QryBlockWriteAll,
    NvM_QryCancelWriteAll,
#if (NVM_KILL_WRITEALL_API == STD_ON)
    NvM_QryWriteAllKilled,
#endif
    NvM_QryCrcBusy,
    NvM_QryDataCopyBusy,
    NvM_QryCrcMatch,
    NvM_QryLastBlockDone_ReadAll,
    NvM_QryLastBlockDone_WriteAll,
    NvM_QryLastResultOk,
    NvM_QryMainFsmRunning,
    NvM_QryMultiJob,
#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
    NvM_QryNormalPrioJob,
# if (NVM_JOB_PRIORISATION == STD_ON)
    NvM_QryHighPrioJob,
# endif
#endif
    NvM_QryNvBusy,
    NvM_QryMemHwaBusy,
#if  (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    NvM_QryRamValid,
#endif
    NvM_QryRedundantBlock,
    NvM_QrySkipBlock,
    NvM_QrySubFsmRunning,
    NvM_QryWriteBlockOnce,
    NvM_QryWriteRetriesExceeded,
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
    NvM_QryHasRom,
    NvM_QryExtRuntime,
#endif
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    NvM_QrySuspendRepairRedundantBlocks,
    NvM_QryRepairRedBlockDefect,
#endif
    NvM_QryCRCCompMechanismSkipWrite,
    NvM_QryPostReadTransform,
    NvM_QryTrue
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/**********************************************************************************************************************
 *  IMPLEMENTATION
 *********************************************************************************************************************/
#define NVM_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
*  NvM_QryBlockWriteAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryBlockWriteAll(void)
{
#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    return (boolean)(((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 &
               (NVM_WR_PROT_SET | NVM_LOCK_STAT_SET | NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET)) ==
                                              (NVM_STATE_CHANGED_SET | NVM_STATE_VALID_SET)) &&
            ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_SELECT_BLOCK_FOR_WRITEALL_ON) != 0));
#else
    return (boolean)(((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & 
                                                        (NVM_WR_PROT_SET | NVM_LOCK_STAT_SET)) == 0) &&
            ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_SELECT_BLOCK_FOR_WRITEALL_ON) != 0));
#endif
}

/**********************************************************************************************************************
*  NvM_QryCancelWriteAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCancelWriteAll(void)
{
    return (boolean)(NvM_ApiFlags_u8 & NVM_APIFLAG_CANCEL_WR_ALL_SET);
}

#if (NVM_KILL_WRITEALL_API == STD_ON)
/**********************************************************************************************************************
*  NvM_QryWriteAllKilled
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteAllKilled(void)
{
    return (boolean)((NvM_CurrentJob_t.JobServiceId_t == NVM_INT_FID_WRITE_ALL) && 
        ((NvM_ApiFlags_u8 & NVM_APIFLAG_KILL_WR_ALL_SET) != 0));
}
#endif /* (NVM_KILL_WRITEALL_API == STD_ON) */

/**********************************************************************************************************************
*  NvM_QryCrcMatch
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcMatch(void)
{
    return (boolean)NvM_CrcJob_Compare(&NvM_CurrentBlockInfo_t.BlockCrcJob_t); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
}

/**********************************************************************************************************************
*  NvM_QryCrcBusy
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCrcBusy(void)
{
    return (boolean)(NvM_CrcJob_isBusy(&NvM_CurrentBlockInfo_t.BlockCrcJob_t));
}

/**********************************************************************************************************************
*  NvM_QryDataCopyBusy
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryDataCopyBusy(void)
{
    return (boolean)(NvM_CurrentBlockInfo_t.ByteCount_u16 > 0u);
}

/**********************************************************************************************************************
*  NvM_QryLastBlockDone_ReadAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_ReadAll(void)
{
    return (boolean)(NvM_CurrentJob_t.JobBlockId_t >= NvM_NoOfBlockIds_t);
}

/**********************************************************************************************************************
*  NvM_QryLastBlockDone_WriteAll
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastBlockDone_WriteAll(void)
{
    return (boolean)(NvM_CurrentJob_t.JobBlockId_t == 0u);
}

/**********************************************************************************************************************
*  NvM_QryLastResultOk
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryLastResultOk(void)
{
    return (boolean)(NVM_REQ_OK == NvM_CurrentBlockInfo_t.LastResult_t);
}

/**********************************************************************************************************************
*  NvM_QryMainFsmRunning
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMainFsmRunning(void)
{
    return (boolean)(NVM_STATE_FSM_FINISHED != NvM_JobMainState_t);
}

/**********************************************************************************************************************
*  NvM_QryMultiJob
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMultiJob(void)
{
    return (boolean)((NvM_ApiFlags_u8 &
        (NVM_APIFLAG_WRITE_ALL_SET | NVM_APIFLAG_READ_ALL_SET 
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)  /* ECO_IGNORE_LINE */
        | NVM_APIFLAG_REPAIR_REDUNDANT_BLOCKS_SET
#endif  /* ECO_IGNORE_LINE */
        )) != 0);
}

/**********************************************************************************************************************
*  NvM_QryNvBusy
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
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryNvBusy(void)
{
#if(NVM_POLLING_MODE == STD_ON)
    const uint8 deviceId = (uint8)NvM_CurrentBlockInfo_t.Descriptor_pt->DeviceId_u8;
    uint8 retVal = FALSE;

    if(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_PENDING)
    {
        if (MEMIF_BUSY == MemIf_GetStatus(deviceId))
        {
            retVal = TRUE;
        }
        else
        {
            switch(MemIf_GetJobResult(deviceId))
            {
                case MEMIF_JOB_OK:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_OK;
                    break;

                case MEMIF_BLOCK_INCONSISTENT:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_INTEGRITY_FAILED;
                    break;

                case MEMIF_BLOCK_INVALID:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NV_INVALIDATED;
                    break;

                default:
                    NvM_CurrentBlockInfo_t.LastResult_t = NVM_REQ_NOT_OK;
            }
        }
    }
    return retVal;
#else
    return (boolean)(NvM_CurrentBlockInfo_t.LastResult_t == NVM_REQ_PENDING);
#endif
}

/**********************************************************************************************************************
*  NvM_QryMemHwaBusy
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryMemHwaBusy(void)
{
    const MemIf_StatusType MemHwaStatus = MemIf_GetStatus(MEMIF_BROADCAST_ID);

    return (boolean)((MemHwaStatus == MEMIF_BUSY) || (MemHwaStatus == MEMIF_BUSY_INTERNAL));
}

/**********************************************************************************************************************
*  NvM_QryRedundantBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRedundantBlock(void)
{
    /* PRQA S 3760 2 */ /* MD_NvM_10.1 */
    return (boolean)(
        ((NvM_CurrentBlockInfo_t.Descriptor_pt->MngmtType_t & NVM_BLOCK_REDUNDANT) != 0) &&
        ((NvM_CurrentBlockInfo_t.NvIdentifier_u16 & 0x0001u) == 0));
}

/**********************************************************************************************************************
*  NvM_QrySkipBlock
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySkipBlock(void)
{
    /* PRQA S 3760 3 */ /* MD_NvM_10.1 */
    /* PRQA S 3415 2 */ /* MD_NvM_12.4 */
    return (boolean)(((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_SELECT_BLOCK_FOR_READALL_ON) == 0)
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON) /* ECO_IGNORE_LINE */
        || ((!NvM_QryHasRom()) && (NvM_QryExtRuntime()))
#endif /* ECO_IGNORE_LINE */
        );
}

/**********************************************************************************************************************
*  NvM_QrySubFsmRunning
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySubFsmRunning(void)
{
    return (boolean)(NVM_STATE_FSM_FINISHED != NvM_JobSubState_t);
}

/**********************************************************************************************************************
*  NvM_QryTrue
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryTrue(void)
{
    return TRUE;
}

/**********************************************************************************************************************
*  NvM_QryWriteBlockOnce
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteBlockOnce(void)
{
    /* PRQA S 3760 2 */ /* MD_NvM_10.1 */
    /* PRQA S 3415 1 */ /* MD_NvM_12.4 */
    boolean writeOnce = (boolean)(((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_BLOCK_WRITE_BLOCK_ONCE_ON) != 0)
#if(NVM_DYNAMIC_CONFIGURATION == STD_ON) /* ECO_IGNORE_LINE */
    && (!NvM_QryExtRuntime())
#endif /* ECO_IGNORE_LINE */
    );

    return writeOnce;
}

/**********************************************************************************************************************
*  NvM_QryWriteRetriesExceeded
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryWriteRetriesExceeded(void)
{
    /* the initial try is also counted as retry. Therefore the total number of
       write retries may reach the configured number of attempts. */
    return (boolean)(NvM_CurrentBlockInfo_t.WriteRetryCounter_u8 > NvM_NoOfWrAttempts_u8);
}

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
/**********************************************************************************************************************
*  NvM_QryRamValid
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRamValid(void)
{
    return (boolean)((NvM_CurrentBlockInfo_t.Descriptor_pt->RamBlockDataAddr_t != NULL_PTR) &&
        ((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & NVM_STATE_VALID_SET) != 0)
        && ((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & NVM_LOCK_STAT_SET) == 0));
}
#endif /* (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) */

#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
/**********************************************************************************************************************
*  NvM_QryHasRom
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryHasRom(void)
{
    return (boolean)((NvM_CurrentBlockInfo_t.Descriptor_pt->RomBlockDataAddr_pt != NULL_PTR) ||
        (NvM_CurrentBlockInfo_t.Descriptor_pt->InitCallback_pt != NULL_PTR));
}

/**********************************************************************************************************************
*  NvM_QryExtRuntime
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryExtRuntime(void)
{
    return (boolean)(
        ((NvM_CurrentBlockInfo_t.InternalFlags_u8 & NVM_INTFLAG_DYN_MISMATCH_SET) != 0) &&
        /* PRQA S 3760 1 */ /* MD_NvM_10.1 */
        ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_RESISTANT_TO_CHANGED_SW_ON) == 0));
}
#endif

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
/**********************************************************************************************************************
 * NvM_QrySuspendRepairRedundantBlocks
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QrySuspendRepairRedundantBlocks(void)
{
    /* we do not have to check the high priority job here - it is done within NvM processing */
    return (
#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) /* ECO_IGNORE_LINE */
        (NvM_QryNormalPrioJob()) ||
#endif /* ECO_IGNORE_LINE */
        ((NvM_ApiFlags_u8 & NVM_APIFLAG_READ_ALL_SET) != 0) ||
        ((NvM_ApiFlags_u8 & NVM_APIFLAG_WRITE_ALL_SET) != 0));
}

/**********************************************************************************************************************
 * NvM_QryRepairRedBlockDefect
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryRepairRedBlockDefect(void)
{
    /* PRQA S 3760 2 */ /* MD_NvM_10.1 */
    boolean firstBlockOk = (boolean)((NvM_RepairRedBlockState.NvBlockState & 0x0F) == NVM_NVBLOCK_STATE_UPTODATE);
    boolean secondBlockOk = (boolean)(((NvM_RepairRedBlockState.NvBlockState & 0xF0) >> ((uint8)4)) == NVM_NVBLOCK_STATE_UPTODATE);

    /* #10 block is defect in case one sub-block is already marked as defect, no matter whether the block has a Crc or not */
    boolean blockDefect = (firstBlockOk ^ secondBlockOk);

    /* #20 in case both sub-blocks are valid and the block is configured with Crc */
    /* PRQA S 3760 1 */ /* MD_NvM_10.1 */
    if((firstBlockOk && secondBlockOk) && (NvM_CurrentBlockInfo_t.Descriptor_pt->CrcSettings != NVM_BLOCK_USE_CRC_OFF))
    {
        /* #21 check whether the Crc values fit to each other - block is defect in case the Crcs differ! */
        blockDefect = (boolean)(NvM_RepairRedBlockState.CrcBuffer != NvM_CurrentBlockInfo_t.BlockCrcJob_t.CurrentCrcValue);

        /* #22 for different Crcs we assume the second block is defect - NvM shall repair it (overwrite with first block data) */
        /* PRQA S 3344 1 */ /* MD_NvM_13.2 */
        if(blockDefect)
        {
            NvM_RepairRedBlockState.NvBlockState |= (NVM_NVBLOCK_STATE_DEFECT << 4);
        }
    }

    return blockDefect;
}
#endif

/**********************************************************************************************************************
 * NvM_QryCRCCompMechanismSkipWrite
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryCRCCompMechanismSkipWrite(void)
{
    /* #10 CRCCompMechanims enabled: check CRC and NV RAM state, otherwise the block must not be skipped */
    boolean skipBlock = FALSE;
    /* PRQA S 3760 2 */ /* MD_NvM_10.1 */
    if ((NvM_CurrentBlockInfo_t.Descriptor_pt->Flags_u8 & NVM_CRC_COMP_MECHANISM_ON) == NVM_CRC_COMP_MECHANISM_ON)
    {
        skipBlock = ((NvM_CrcJob_Compare(&NvM_CurrentBlockInfo_t.BlockCrcJob_t)) &&
            ((NvM_CurrentBlockInfo_t.Mngmt_pt->NvRamAttributes_u8 & NVM_NVRAM_UPTODATE_SET) == NVM_NVRAM_UPTODATE_SET)); /* SBSW_NvM_FuncCall_PtrParam_CurrBlockInfo */
    }

    return skipBlock;
}

/**********************************************************************************************************************
 * NvM_QryPostReadTransform
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_QryPostReadTransform(void)
{
    boolean retVal = TRUE;

    if(NvM_CurrentBlockInfo_t.Descriptor_pt->CbkPostReadTransform != NULL_PTR)
    {
        retVal = (boolean)(NvM_CurrentBlockInfo_t.Descriptor_pt->CbkPostReadTransform(NvM_CurrentJob_t.JobBlockId_t, /* SBSW_NvM_FuncPtrCall_UserCallbacks */
            NvM_CurrentBlockInfo_t.RamAddr_t, NvM_CurrentBlockInfo_t.Descriptor_pt->NvBlockLength_u16) == E_OK);
    }

    return retVal;
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/* PRQA L:inclusions */
/* PRQA L:macros */

/*---- End of File ---------------------------------------------------------*/

