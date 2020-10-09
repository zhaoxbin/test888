/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NvM_Act.h
 *    Component:  MemService_AsrNvM
 *       Module:  NvM - Submodule Act (Actions)
 *    Generator:  -
 *
 *  Description:  This sub-module implements actions to be performed upon state transitions.
 *
 *                This file is an internal include; it shall not be included by other modules than NvM!
 *
 *********************************************************************************************************************/

/* Do not modify this file! */

/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
#if (!defined NVM_ACT_H_)
#define NVM_ACT_H_

/**********************************************************************************************************************
 * VERSION IDENTIFICATION
 *********************************************************************************************************************/
#define NVM_ACT_MAJOR_VERSION    (5u)
#define NVM_ACT_MINOR_VERSION    (8u)
#define NVM_ACT_PATCH_VERSION    (0u)

/**********************************************************************************************************************
 * API TYPE DEFINITIONS
 *********************************************************************************************************************/
/* Enumeration of Action handler IDs */
typedef enum
{
    NVM_ACT_ID_SetInitialAttr,
    NVM_ACT_ID_InitMainFsm,
    NVM_ACT_ID_InitBlock,
    NVM_ACT_ID_InitReadAll,
    NVM_ACT_ID_InitReadBlockFsm,
    NVM_ACT_ID_InitWriteAll,
    NVM_ACT_ID_InitWriteBlock,
    NVM_ACT_ID_InitWriteBlockFsm,
    NVM_ACT_ID_InitRestoreBlockDefaults,
    NVM_ACT_ID_FinishMainJob,
#if (NVM_KILL_WRITEALL_API == STD_ON)
    NVM_ACT_ID_KillWritAll,
#endif
    NVM_ACT_ID_FinishBlock,
    NVM_ACT_ID_InitNextBlockReadAll,
    NVM_ACT_ID_InitNextBlockWriteAll,
    NVM_ACT_ID_FinishCfgIdCheck,
    NVM_ACT_ID_FinishReadBlock,
    NVM_ACT_ID_FinishWriteBlock,
#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    NVM_ACT_ID_FinishEraseBlock,
    NVM_ACT_ID_EraseNvBlock,
    NVM_ACT_ID_InvalidateNvBlock,
#endif
    NVM_ACT_ID_ProcessCrc,
    NVM_ACT_ID_WriteNvBlock,
    NVM_ACT_ID_ReadNvBlock,
    NVM_ACT_ID_ProcessCrcRead,
    NVM_ACT_ID_ReadCopyData,
    NVM_ACT_ID_RestoreRomDefaults,
    NVM_ACT_ID_FinishRestoreRomDefaults,
    NVM_ACT_ID_TestBlockBlank,
    NVM_ACT_ID_ValidateRam,
    NVM_ACT_ID_SetupRedundant,
    NVM_ACT_ID_SetupOther,
    NVM_ACT_ID_UpdateNvState,
    NVM_ACT_ID_SetReqIntegrityFailed,
    NVM_ACT_ID_SetReqSkipped,
    NVM_ACT_ID_SetReqNotOk,
    NVM_ACT_ID_SetBlockPendingWriteAll,
    NVM_ACT_ID_CopyNvDataToBuf,
    NVM_ACT_ID_GetMultiBlockJob,
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    NVM_ACT_ID_RepairRedBlocksInit,
    NVM_ACT_ID_RepairRedBlocksInitNext,
    NVM_ACT_ID_RepairRedBlockReadCheck,
    NVM_ACT_ID_RepairRedBlockFinishReadCheck,
    NVM_ACT_ID_RepairRedBlocksReadValid,
    NVM_ACT_ID_RepairRedBlockWriteInvalid,
    NVM_ACT_ID_RepairRedBlocksFinishBlock,
    /* PRQA S 0779 1 */ /* MD_MSR_5.1_779 */
    NVM_ACT_ID_RepairRedBlocksFinish,
#endif
#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
    NVM_ACT_ID_GetNormalPrioJob,
# if (NVM_JOB_PRIORISATION == STD_ON)
        NVM_ACT_ID_GetHighPrioJob,
        NVM_ACT_ID_QueueFreeLastJob,
# endif
#endif
    NVM_ACT_ID_Wait,
    NVM_ACT_ID_Nop
} NvM_StateActionIdType;

/* Force implicit cast for enum NvM_StateActionIdType into uint8 when using
 * NvM_StateActionType as data type. But only for production mode in order to
 * see not only numbers when debugging in debug mode
 */
#if (NVM_DEV_ERROR_DETECT == STD_ON)
typedef NvM_StateActionIdType NvM_StateActionType;
#else
typedef uint8 NvM_StateActionType;
#endif

typedef P2CONST(NvM_StateActionType, AUTOMATIC, NVM_PRIVATE_CONST) NvM_StateActionPtrType;

/* type of an action function pointer */
typedef P2FUNC(void, NVM_PRIVATE_CODE, NvM_ActFctPtrType) (void);

/**********************************************************************************************************************
 * API VARIABLES
 *********************************************************************************************************************/
/* because of platform independence we cannot say anything about a pointer's
 * size. So we use the "UNSPECIFIED" section
 */
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* the Action function table, indexed by NvM_StateActionType
 * declaration of the action function pointer table
 */
extern CONST(NvM_ActFctPtrType, NVM_PRIVATE_CONST) NvM_ActionTable_ap[NVM_ACT_ID_Nop + 1];

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#endif /* NVM_ACT_H_ */

/*---- End of File -------------------------------------------------------- */
