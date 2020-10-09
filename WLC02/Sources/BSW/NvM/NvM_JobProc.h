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
 *         File:  NvM_JobProc.h
 *    Component:  MemService_AsrNvM
 *       Module:  NvM - Submodule JobProc (Job Processing)
 *    Generator:  -
 *
 *  Description:  This sub-module implements the FSM for the NVM, including the state description table
 *
 *                This file is an internal include; it shall not be included by other modules than NvM!
 *
 *********************************************************************************************************************/

/* Do not modify this file! */

/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
#if (!defined NVM_JOBPROC_H_)
#define NVM_JOBPROC_H_

/**********************************************************************************************************************
 * VERSION IDENTIFICATION
 *********************************************************************************************************************/
#define NVM_JOBPROC_MAJOR_VERSION    (5u)
#define NVM_JOBPROC_MINOR_VERSION    (8u)
#define NVM_JOBPROC_PATCH_VERSION    (0u)

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "NvM_Act.h"
#include "NvM_Qry.h"
#include "NvM_Crc.h"

/**********************************************************************************************************************
 * API TYPE DEFINITIONS
 *********************************************************************************************************************/
/* type of a job that is to be queued */
typedef struct
{
    NvM_BlockIdType             JobBlockId_t; /* NvM block ID */
    NvM_InternalServiceIdType   JobServiceId_t; /* requested job */
    NvM_RamAddressType          RamAddr_t; /* data pointer */
} NvM_JobType;

typedef P2VAR(NvM_JobType, AUTOMATIC, NVM_PRIVATE_DATA) NvM_JobPtrType;

/* job processing structure: contains all information related to
   the processing of one certain job */
typedef struct
{
    NvM_BlockDescrPtrType       Descriptor_pt; /* pointer to the block descriptor */
    NvM_RamMngmtPtrType         Mngmt_pt; /* pointer to the RAM management */
    NvM_RamAddressType          RamAddr_t; /* pointer to data */
    NvM_CrcJobType              BlockCrcJob_t; /* pointer to CRC job */
    uint16                      NvIdentifier_u16; /* Nv ID, which will be passed to underlying modules */
    uint16                      ByteCount_u16; /* used for block-wise copy - also if internal buffer is OFF! */
    NvM_RequestResultType       LastResult_t; /* job result */
    uint8                       WriteRetryCounter_u8; /* write retry counter */
    uint8                       InternalFlags_u8; /* job flags */
    uint8                       NvState_u8; /* current state of the block */
    uint8                       blockId; /*  the block id  ,*/
} NvM_BlockInfoType;

typedef P2VAR(NvM_BlockInfoType, AUTOMATIC, NVM_FAST_DATA) NvM_BlockInfoPtrType;

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
/* structure required by RepairRedundantBlocks job */
typedef struct
{
    NvM_BlockIdType CurrentBlockId; /* current block ID */
    uint8 NvBlockState; /* current state */
    uint32 CrcBuffer; /* CRC buffer to be able to compare two CRCs */
} NvM_RepairBlockStateType;

extern VAR(NvM_RepairBlockStateType, NVM_PRIVATE_DATA) NvM_RepairRedBlockState;
#endif

/* Possible states of the NVManager */
/* Used for the task-, the jobmain-, and the jobsub-state machine */
typedef enum
{
    /* Possible states of the task state machine */

    /* \trace DSGN-NvM22853 */
    NVM_STATE_UNINIT = 0u,             //0
    /* \trace DSGN-NvM22979 */
    NVM_STATE_IDLE,                   //1
#if ((NVM_JOB_PRIORISATION == STD_ON) && (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1))
    /* \trace DSGN-NvM22983 */
    NVM_STATE_HIGH_PRIO_JOB,
#endif
    /* \trace DSGN-NvM22981 */
    NVM_STATE_NORMAL_PRIO_JOB,         //2
#if (NVM_KILL_WRITEALL_API == STD_ON)
    /* \trace DSGN-NvM22980 */
    NVM_STATE_MULTI_BLOCK_JOB,        //3
#endif
    /* Possible states of the jobmain- and jobsub state machine */

    /* Read Block */

    /* \trace DSGN-NvM22815 */
    NVM_STATE_READ_READ_DATA,         //4
    /* \trace DSGN-NvM24164 */
    NVM_STATE_READ_DATA_VALIDATION,  //5
    /* \trace DSGN-NvM22816 */
    NVM_STATE_READ_CMP_CRC,          //6
    /* \trace DSGN-NvM22818 */
    NVM_STATE_READ_IMPL_RECOV,      //7
    /* \trace DSGN-NvM22819 */
    NVM_STATE_READ_LOAD_ROM,        //8
    /* \trace DSGN-NvM24163 */
    NVM_STATE_READ_FINALIZE,       //9

    /* Write Block */

    /* \trace DSGN-NvM24148 */
    NVM_STATE_WRITE_INITIAL,       //10
    /* \trace DSGN-NvM22806 */
    NVM_STATE_WRITE_CRCCOMPMECHANISM,  //11
    /* \trace DSGN-NvM22807 */
    NVM_STATE_WRITE_TEST_PRI_READ,     //12
    /* \trace DSGN-NvM22808 */
    NVM_STATE_WRITE_TEST_SEC_READ,    //13
    /* \trace DSGN-NvM22809 */
    NVM_STATE_WRITE_WR_DATA_CRC_1,    //14
    /* \trace DSGN-NvM22810 */
    NVM_STATE_WRITE_WR_DATA_CRC_2,    //15

    /* RestoreBlockDefaults */

    /* \trace DSGN-NvM22825 */
    NVM_STATE_RESTORE_LOAD_ROM,      //16

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    /* Invalidate Nv Block */

    /* \trace DSGN-NvM22829 */
    NVM_STATE_INVALIDATING_BLOCK,    //17

    /* Erase Nv Block */

    /* \trace DSGN-NvM22833 */
    NVM_STATE_ERASE_ERASE_BLOCK,      //18
#endif

    /* Read All */

    /* \trace DSGN-NvM22840 */
    NVM_STATE_READALL_PROC_CONFIG_ID,    //19
    /* \trace DSGN-NvM22841 */
    NVM_STATE_READALL_PROC_RAM_BLOCK,    //20
    /* \trace DSGN-NvM22843 */
    NVM_STATE_READALL_CHK_SKIP,          //21
    /* \trace DSGN-NvM22845 */
    NVM_STATE_READALL_WR_ONCE_PROT,     //22
#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    /* \trace DSGN-NvM22842 */
    NVM_STATE_READALL_CHK_RAM_VALIDITY,   //23
#endif
    /* \trace DSGN-NvM22846 */
    NVM_STATE_READALL_READ_NV,     //24

    /* Write All */

    /* \trace DSGN-NvM22847 */
    NVM_STATE_WRITEALL_PROC_BLOCK,    //25
    /* \trace DSGN-NvM22850 */
    NVM_STATE_WRITEALL_WRITE_FSM,     //26
    /* \trace DSGN-NvM22848 */
    NVM_STATE_WRITEALL_WAIT_MEMHWA,   //27

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    /* RepairRedundantBlocks */

    /* \trace DSGN-NvM23540 */
    NVM_STATE_REPAIRREDUNDANT_MAIN,
    /* \trace DSGN-NvM23542 */
    NVM_STATE_REPAIRREDUNDANT_CHECK_FIRST,
    /* \trace DSGN-NvM23543 */
    /* PRQA S 0779 1 */ /* MD_MSR_5.1_779 */
    NVM_STATE_REPAIRREDUNDANT_CHECK_SECOND,
    /* \trace DSGN-NvM23544 */
    NVM_STATE_REPAIRREDUNDANT_VALIDATE_BLOCK,
    /* \trace DSGN-NvM23545 */
    NVM_STATE_REPAIRREDUNDANT_READ_VALID_BLOCK,
    /* \trace DSGN-NvM23546 */
    NVM_STATE_REPAIRREDUNDANT_WRITE_INVALID_BLOCK,
#endif
    /* \trace DSGN-NvM22817 */
    NVM_STATE_FSM_FINISHED     //28
} NvM_StateIdType;

/* Force implizit cast for enum NvM_StateIdType into uint8 when using
 * NvMStateType as data type. But only for production mode in order to
 * see not only numbers when debugging in debug mode
 */
#if (NVM_DEV_ERROR_DETECT == STD_ON)
    typedef NvM_StateIdType NvM_StateType;
#else
    typedef uint8 NvM_StateType;
#endif

/* Descriptor, describing an internal service (async  NVM job) */
typedef struct
{
    NvM_StateActionType    InitialActionId;
    NvM_StateType          InitialState_t;
    NvM_ServiceIdType      PublicFid_t;
} NvM_IntServiceDescrType;

/**********************************************************************************************************************
 * MACROS / DEFINES
 *********************************************************************************************************************/

/* the maximum number of conditional exits a stat can have, the final ("else") exit is implicit */
#define NVM_MAX_NUM_OF_STATE_CONDITIONS (3u)

/* the maximum number of Query functions that can be ANDed together to form a state exit condition */
#define NVM_MAX_NUM_OF_QRY_AND (2u)

/**********************************************************************************************************************
 * TYPE DEFINITIONS
 *********************************************************************************************************************/
/* */
typedef struct
{
    NvM_StateActionType ExitHandler_t; /* action ID */
    NvM_StateActionType EntryHandler_t; /* action ID */
} NvM_StateChangeActionsType;

typedef P2CONST(NvM_StateChangeActionsType, AUTOMATIC, NVM_PRIVATE_CONST) NvM_StateChangeActionsPtrType;

/* describe one State exit with its condition, its Actions and its following state */
typedef struct
{
    NvM_StateQueryType         Queries_at[NVM_MAX_NUM_OF_QRY_AND]; /* queries, which decide whether the actions shall be executed */
    NvM_StateChangeActionsType Actions_t; /* action IDs to execute */
    NvM_StateType              NextState_t; /* next state to execute */
} NvM_StateChangeIfDescrType;

/* describe the final state exit ("else") to be taken if no condition matched */
typedef struct
{
    NvM_StateChangeActionsType Actions_t; /* action IDs to execute */
    NvM_StateType              NextState_t; /* next state to execute */
} NvM_StateChangeElseDescrType;

/* describe a state with it's possible change conditions */
typedef struct
{
    NvM_StateChangeIfDescrType   ChangeConditions_at[NVM_MAX_NUM_OF_STATE_CONDITIONS]; /* all conditions with queries */
    NvM_StateChangeElseDescrType FinalCondition_t; /* fallback condition without queries */
} NvM_StateDescrType;

/**********************************************************************************************************************
 * VARIABLES
 *********************************************************************************************************************/
#define NVM_START_SEC_VAR_FAST_8
#include "MemMap.h"

/* at least for development mode (where the following two state types are enums)
* the compiler is expected to ensure correct alignment, regardless of any given section alignment.
* The state variables are used quite frequently (but never via pointers)
*/
extern VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobMainState_t;
extern VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobSubState_t;

/* extern definition of variables that area used in the NvM submodules
* They are defined in NvM.c
*/
extern VAR(uint8, NVM_FAST_DATA) NvM_ApiFlags_u8;

#define NVM_STOP_SEC_VAR_FAST_8
#include "MemMap.h"

#define NVM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/* state of the task state machine */
extern VAR(NvM_StateType, NVM_PRIVATE_DATA) NvM_TaskState_t;

#define NVM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

extern VAR(NvM_JobType, NVM_PRIVATE_DATA) NvM_CurrentJob_t;
extern VAR(NvM_BlockInfoType, NVM_PRIVATE_DATA) NvM_CurrentBlockInfo_t;

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Internal job descriptor table */
/* PRQA S 3684 1 */ /* MD_NvM_8.12 */
extern CONST(NvM_IntServiceDescrType, NVM_PRIVATE_CONST) NvM_IntServiceDescrTable_at[];

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/**********************************************************************************************************************
 * FUNCTIONS
 *********************************************************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 * NvM_JobProcInit
 *********************************************************************************************************************/
/*! \brief Initialize the module variables
 *  \details Initialize the module variables
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(void, NVM_PRIVATE_CODE) NvM_JobProcInit(void);

/**********************************************************************************************************************
 * NvM_Fsm
 *********************************************************************************************************************/
/*! \brief Sets next state machine state to process depending on query results.
 *  \details This function executes exactly one State of a state machine: e.g. the initial state of the State Machine
 *           for ReadBlock. This initial state contains four exits. Which exit is taken depends on the queries
 *           which in turn lead to the actions. At last the next state is stored. The next time the function is called,
 *           it executes this next state. This function is called from NvM_Mainfunction() which is called cyclically
 *           by an Application (or event-driven when NVM is an ECC Task).
 *  \param[in] NvM_CurrentState_t
 *  \return next state
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(NvM_StateType, NVM_PRIVATE_CODE) NvM_Fsm(NvM_StateType);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* NVM_JOBPROC_H_ */

/*---- End of File -------------------------------------------------------- */
