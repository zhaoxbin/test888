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
 *         File:  NvM_JobProc.c
 *      Project:  MemService_AsrNvM
 *       Module:  NvM - Submodule JobProc (Job Processing)
 *    Generator:  -
 *
 *  Description:  This sub-module implements the FSM for the NVM, including the state
 *                description table.
 *
 *********************************************************************************************************************/

/* Do not modify this file! */

/**********************************************************************************************************************
 *  MODULE SWITCH
 *********************************************************************************************************************/
#define NVM_JOBPROC_SOURCE

/* PRQA S 5087 inclusions */ /* MD_MSR_19.1 */
/* PRQA S 0857 macros */ /* MD_MSR_1.1_857 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  INCLUDE OF CONFIGURATION (ALL SECTIONS)
 *********************************************************************************************************************/
#include "NvM_Cfg.h"
#include "NvM_PrivateCfg.h"

/**********************************************************************************************************************
 *  MODULE HEADER INCLUDES
 *********************************************************************************************************************/
#include "NvM_JobProc.h"

/**********************************************************************************************************************
 *  INCLUDE OF THE ACTIONS AND QUERIES
 *********************************************************************************************************************/
#include "NvM_Act.h"
#include "NvM_Qry.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
#if ((NVM_JOBPROC_MAJOR_VERSION != (5u)) \
        || (NVM_JOBPROC_MINOR_VERSION != (8u)))
# error "Version numbers of NvM_JobProc.c and NvM_JobProc.h are inconsistent!"
#endif

#if ((NVM_CFG_MAJOR_VERSION != (5u)) \
        || (NVM_CFG_MINOR_VERSION != (8u)))
# error "Version numbers of NvM_JobProc.c and NvM_Cfg.h are inconsistent!"
#endif

#if ((NVM_ACT_MAJOR_VERSION != (5u)) \
        || (NVM_ACT_MINOR_VERSION != (8u)))
# error "Version numbers of NvM_JobProc.c and NvM_Act.h are inconsistent!"
#endif

#if ((NVM_QRY_MAJOR_VERSION != (5u)) \
        || (NVM_QRY_MINOR_VERSION != (8u)))
# error "Version numbers of NvM_JobProc.c and NvM_Qry.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  INTERNAL CHECKS
 *********************************************************************************************************************/
#if (3u != NVM_MAX_NUM_OF_STATE_CONDITIONS)
# error "Only case '3 conditions (4 state exits)' is implemented"
#endif

#if (2u != NVM_MAX_NUM_OF_QRY_AND)
# error "Currently two AND-associated queries per state exit are supported"
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
 * NvM_FsmQuery
 *********************************************************************************************************************/
/*! \brief Process a State machine query.
 *  \details Executes first query and then the second, in case the first was successful.
 *  \param[in] NvM_Queries_at
 *  \return TRUE both queries executed successfully
 *  \return FALSE otherwise
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_FsmQuery(NvM_StateQueryPtrType);

/**********************************************************************************************************************
 * NvM_FsmAction
 *********************************************************************************************************************/
/*! \brief Process a State change - perform the defined actions.
 *  \details Process a State change - perform the defined actions.
 *  \param[in] NvM_Actions_pt
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_FsmAction(NvM_StateChangeActionsPtrType);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *  INTERNAL MODULE GLOBAL VARIABLES
 *********************************************************************************************************************/

#define NVM_START_SEC_VAR_FAST_8
#include "MemMap.h"

/* at least for development mode (where the following two state types are enums) the
* compiler is expected to ensure correct alignment, regardless of any given section alignment.
* The state variables are used quite frequently (but never via pointers)
*/
VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobMainState_t;
VAR(NvM_StateType, NVM_FAST_DATA) NvM_JobSubState_t;

#define NVM_STOP_SEC_VAR_FAST_8
#include "MemMap.h"

#define NVM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/* state of the task state machine */
VAR(NvM_StateType, NVM_PRIVATE_DATA) NvM_TaskState_t = NVM_STATE_UNINIT;

#define NVM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

VAR(NvM_BlockInfoType, NVM_PRIVATE_DATA) NvM_CurrentBlockInfo_t;

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
VAR(NvM_RepairBlockStateType, NVM_PRIVATE_DATA) NvM_RepairRedBlockState;
#endif

#define NVM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define NVM_NO_OF_SERVICES (NVM_INT_FID_NO_JOB_PENDING + 1u)

/**********************************************************************************************************************
 *  JOB DESCRIPTOR TABLE
 *********************************************************************************************************************/
CONST(NvM_IntServiceDescrType, NVM_PRIVATE_CONST) NvM_IntServiceDescrTable_at[NVM_NO_OF_SERVICES] =
{
    /* NVM_INT_FID_WRITE_BLOCK */
    {     //0
        NVM_ACT_ID_InitWriteBlock, NVM_STATE_WRITE_INITIAL, NVM_WRITE_BLOCK
    },

    /* NVM_INT_FID_READ_BLOCK */
    {   //1
        NVM_ACT_ID_ReadNvBlock, NVM_STATE_READ_READ_DATA, NVM_READ_BLOCK
    },

    /* NVM_INT_FID_RESTORE_DEFAULTS */
    {   //2
        NVM_ACT_ID_InitRestoreBlockDefaults, NVM_STATE_RESTORE_LOAD_ROM, NVM_RESTORE_BLOCK_DEFAULTS
    },

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
    /* NVM_INT_FID_INVALIDATE_NV_BLOCK */
    {   //3
        NVM_ACT_ID_InvalidateNvBlock, NVM_STATE_INVALIDATING_BLOCK, NVM_INVALIDATE_NV_BLOCK
    },

    /* NVM_INT_FID_ERASE_BLOCK */
    {   //4
        NVM_ACT_ID_EraseNvBlock, NVM_STATE_ERASE_ERASE_BLOCK, NVM_ERASE_BLOCK
    },
#else
    /* NVM_INT_FID_INVALIDATE_NV_BLOCK */
    {
        NVM_ACT_ID_Nop, NVM_STATE_FSM_FINISHED, NVM_INVALIDATE_NV_BLOCK
    },

    /* NVM_INT_FID_ERASE_BLOCK */
    {
        NVM_ACT_ID_Nop, NVM_STATE_FSM_FINISHED, NVM_ERASE_BLOCK
    },
#endif
    /* NVM_INT_FID_WRITE_ALL */
    {   //5
        NVM_ACT_ID_InitWriteAll, NVM_STATE_WRITEALL_PROC_BLOCK, NVM_WRITE_ALL
    },

    /* NVM_INT_FID_READ_ALL */
    {    //6
        NVM_ACT_ID_InitReadAll, NVM_STATE_READALL_PROC_CONFIG_ID, NVM_READ_ALL
    },
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
    /* NVM_INT_FID_REPAIR_REDUNDANT_BLOCKS */
    {
        NVM_ACT_ID_RepairRedBlocksInit, NVM_STATE_REPAIRREDUNDANT_MAIN, NVM_REPAIR_REDUNDANT_BLOCKS
    },
#else
    /* NVM_INT_FID_REPAIR_REDUNDANT_BLOCKS */
    {    //7
        NVM_ACT_ID_Nop, NVM_STATE_FSM_FINISHED, NVM_REPAIR_REDUNDANT_BLOCKS
    },
#endif
    /* NVM_INT_FID_NO_JOB_PENDING */
    {   //8
        NVM_ACT_ID_Nop, NVM_STATE_FSM_FINISHED, NVM_MAINFUNCTION
    }
};

/* these macros shall increase the readability of the State Descriptor Table */
#define NVM_STATE_IF
#define NVM_STATE_ELSEIF
#define NVM_STATE_THEN
#define NVM_STATE_ELSE

/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#define NVM_NEXT_STATE(state) (state)

/**********************************************************************************************************************
 *  STATE DESCRIPTOR TABLE
 *  - stores all NvM state machines within one single array with states as element type.
 *  - states are accessed via indexes - each state machine knows where to begin, following states are indexed from
 *  current processing state
 *********************************************************************************************************************/
/* PRQA S 3218 1 */ /* MD_NvM_8.7 */
NVM_LOCAL CONST(NvM_StateDescrType, NVM_PRIVATE_CONST) NvM_StateDescrTable_at[] =
{
/**********************************************************************************************************************
 *  NvM uninitialized
 *********************************************************************************************************************/
    /* NVM_STATE_UNINIT
     * if the TASK runs when the NVM is not initialized yet, use Wait Action to remain in UNINIT state.
     * This state can only be left through a call to NvM_Init by ECU state manager */
    {
        {    //0
            /* Exit 1 */
            {
                NVM_STATE_IF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_UNINIT)
            },
            /* Exit 2 */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_UNINIT)
            },
            /* Exit 3 */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_UNINIT)
            }
        },
        /* final case */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Wait},
            NVM_NEXT_STATE(NVM_STATE_UNINIT)
        }
    },
/**********************************************************************************************************************
 *  NvM idle
 *********************************************************************************************************************/
#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_1)
    /* NVM_STATE_IDLE */
    /* in API config class 1, we only have to wait for a multi block job ReadAll or WriteAll */
    {
        {
            /* Multi block job found */
            {
                NVM_STATE_IF{NVM_QRY_ID_MULTI_BLK_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetMultiBlockJob, NVM_ACT_ID_InitMainFsm},
# if (NVM_KILL_WRITEALL_API == STD_ON)
                    NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
# else
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
# endif
            },
            /* no job found */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },
            /* not used */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#elif (NVM_JOB_PRIORISATION == STD_ON) /* && (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) */
    /* NVM_STATE_IDLE */
    /* Scan job lists, if no job was found: wait */
    {
        {
            /* High priority job found */
            {
                NVM_STATE_IF{NVM_QRY_ID_HI_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetHighPrioJob, NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
            },
            /* Normal priority job found */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_NORMAL_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetNormalPrioJob, NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },
            /* Multi block job found */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_MULTI_BLK_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetMultiBlockJob, NVM_ACT_ID_InitMainFsm},
# if (NVM_KILL_WRITEALL_API == STD_ON)
                    NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
# else
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
# endif
            }
        },
        /* final case, no job found */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#else /* (NVM_JOB_PRIORISATION == STD_OFF) && (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) */
    /* NVM_STATE_IDLE */
    /* Scan job lists, if no job was found: wait */
    {
        {    //1
            /* Single block job found */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_NORMAL_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetNormalPrioJob, NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },
            /* Multi block job found */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_MULTI_BLK_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetMultiBlockJob, NVM_ACT_ID_InitMainFsm},
# if (NVM_KILL_WRITEALL_API == STD_ON)
                    NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
# else
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
# endif
            },
            /* no job found */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#endif /* (NVM_JOB_PRIORISATION == STD_OFF) && (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) */
#if ((NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) && (NVM_JOB_PRIORISATION == STD_ON))
    /* NVM_STATE_HIGH_PRIO_JOB = High prio WriteJob, not cancelable */
    {
        {
            /* main job fsm still running */
            {
                NVM_STATE_IF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
            },
            /* main job fsm finished */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    /* Finish the job and exit MainFunction. Reason: when re-starting an canceled WriteAll
                     * (via immediate priority job) directly in same MainFunction as finishing the immediate
                     * priority job, the WriteAll will overwrite the immediate priority job result! Therefore
                     * exit the MainFunction and "allow" processing of other components, which may wait for the
                     * immediate priority job. */
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },
            /* not used */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#endif /* ((NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) && (NVM_JOB_PRIORISATION == STD_ON)) */
#if ((NVM_JOB_PRIORISATION == STD_ON) && (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1))
    /* NVM_STATE_NORMAL_PRIO_JOB = cancelable, all "NOT HighPrioWrite" jobs */
    {
        {
            {   /* low prio job running or finished, immediate job occurred */
                NVM_STATE_IF{NVM_QRY_ID_HI_PRIO_JOB, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_GetHighPrioJob, NVM_ACT_ID_InitMainFsm},
                    NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
            },
            {   /* continue with the running job */
                NVM_STATE_ELSEIF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },
            {   /* job fsm finished */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_QueueFreeLastJob},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },
#else
    /* NVM_STATE_NORMAL_PRIO_JOB */
    /* not cancelable as there are no high prio jobs, jobs do not need to be freed after processing */
    {   //2
        {
            {   /* continue the running job */
                NVM_STATE_IF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_NORMAL_PRIO_JOB)
            },
            {   /* job finished */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            },
            /* not used */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishReadBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_IDLE)
        }
    },

#endif

#if (NVM_KILL_WRITEALL_API == STD_ON)
    /* NVM_STATE_MULTI_BLOCK_JOB */
# if ((NVM_JOB_PRIORISATION == STD_ON) && (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1))
        /* NVM_STATE_NORMAL_PRIO_JOB = cancelable, all "NOT HighPrioWrite" jobs */
        {
            {
                {   /* WriteAll, but it was killed => Finish FSM, even if a high priority job might be waiting
                       It would be next job in "normal" processing - from IDLE */
                    NVM_STATE_IF{NVM_QR_ID_WRITEALL_KILLED, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_KillWritAll, NVM_ACT_ID_Nop},
                        NVM_NEXT_STATE(NVM_STATE_IDLE)
                },
                {   /* low prio job running or finished, immediate job occurred */
                    NVM_STATE_ELSEIF{NVM_QRY_ID_HI_PRIO_JOB, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_GetHighPrioJob, NVM_ACT_ID_InitMainFsm},
                        NVM_NEXT_STATE(NVM_STATE_HIGH_PRIO_JOB)
                },
                {   /* continue with the running job */
                    NVM_STATE_ELSEIF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                        NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
                }
            },
            /* final case: job fsm finished */
            {
                NVM_STATE_ELSE{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
# else
        /* not cancelable as there are no high priority jobs,
         * jobs do not need to be freed after processing */
        {  //3
            {
                {   /* WriteAll, but it was killed => Finish FSM, even if a high prio job might be waiting
                       It would be next job in "normal" processing - from IDLE */
                    NVM_STATE_IF{NVM_QR_ID_WRITEALL_KILLED, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_KillWritAll, NVM_ACT_ID_Nop},
                        NVM_NEXT_STATE(NVM_STATE_IDLE)
                },
                {   /* continue the running job */
                    NVM_STATE_ELSEIF{NVM_QRY_ID_MAIN_FSM_RUNNING, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                        NVM_NEXT_STATE(NVM_STATE_MULTI_BLOCK_JOB)
                },
                {   /* job finished */
                    NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                        NVM_STATE_THEN{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                        NVM_NEXT_STATE(NVM_STATE_IDLE)
                },
            },
            /* not used */
            {
                NVM_STATE_ELSE{NVM_ACT_ID_FinishMainJob, NVM_ACT_ID_Nop},
                NVM_NEXT_STATE(NVM_STATE_IDLE)
            }
        },
# endif /* Job prioritization */
#endif /* NVM_KILL_WRITEALL_API */
/**********************************************************************************************************************
 *  ReadBlock
 *********************************************************************************************************************/
    /* NVM_STATE_READ_READ_DATA */
    {   //4
        {
            {
                /* NV busy -> wait */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_READ_DATA)
            },
            {
                /* NV idle && OK && CRC calculation ongoing -> calculate the CRC */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_CRC_BUSY},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrcRead, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_READ_CMP_CRC)
            },
            {
                /* NV idle && OK && no CRC -> take care about data validation */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_DATA_VALIDATION)
            }
        },
        {
            /* NV idle && != OK -> try recovery */
            NVM_STATE_ELSE{NVM_ACT_ID_Nop,  NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READ_IMPL_RECOV)
        }
    },
    /* NVM_STATE_READ_DATA_VALIDATION */
    {  //5
        {
            {
                /* data valid -> validate RAM and finalize job */
                NVM_STATE_IF{NVM_QRY_POST_READ_TRANSFORM, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_ValidateRam, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_FINALIZE)
            },
            {
                /* data invalid -> set result and try recovery */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetReqNotOk, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_IMPL_RECOV)
            },
            {
                /* not used */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_IMPL_RECOV)
            }
        },
        {
            /* not used */
            NVM_STATE_ELSE{NVM_ACT_ID_Nop,  NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READ_IMPL_RECOV)
        }
    },
    /* NVM_STATE_READ_CMP_CRC */
    {    //6
        {
            {
                /* CRC calculation ongoing -> process next calculation step */
                NVM_STATE_IF{NVM_QRY_ID_CRC_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrcRead, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_READ_CMP_CRC)
            },
            {
                /* CRC calculated && matches -> go the data validation */
                NVM_STATE_ELSEIF{NVM_QRY_ID_CRC_MATCH, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_DATA_VALIDATION)
            },
            {
                /* CRC calculated && mismatch -> try recovery */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetReqIntegrityFailed, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_IMPL_RECOV)
            }
        },
        {
            /* not used */
            NVM_STATE_ELSE{NVM_ACT_ID_SetReqIntegrityFailed, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READ_IMPL_RECOV)
        }
    },
    /* NVM_STATE_READ_IMPL_RECOV */
    {   //7
        {
            {
                /* Redundant block && the first sub block -> try the other one */
                NVM_STATE_IF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant, NVM_ACT_ID_ReadNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_READ_READ_DATA)
            },
            {
                /* Not redundant || the second sub block -> try to restore ROM */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitRestoreBlockDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_LOAD_ROM)
            },
            /* not used */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitRestoreBlockDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_LOAD_ROM)
            }
        },
        /* not used */
        {
            NVM_STATE_THEN{NVM_ACT_ID_InitRestoreBlockDefaults, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READ_LOAD_ROM)
        }
    },
    /* NVM_STATE_READ_LOAD_ROM */
    {   //8
        {
            {
                /* Restoring pending -> next restore step
                   Don't use "ActWait"! It would cause a wait cycle, if we didn't anything (no ROM defaults). */
                NVM_STATE_IF{NVM_QRY_ID_DATA_COPY_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RestoreRomDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READ_LOAD_ROM)
            },
            {
                /* No ROM || default loaded -> finish restoring and the read */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_FinishReadBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            /* not used */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_FinishReadBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        /* not used */
        {
            NVM_STATE_THEN{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_FinishReadBlock},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
    /* NVM_STATE_READ_FINALIZE */
    {   //9
        {
            {
                /* data copy busy (e.g. explicit sync) -> process step and wait */
                NVM_STATE_IF{NVM_QRY_ID_DATA_COPY_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_ReadCopyData, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_READ_FINALIZE)
            },
            {
                /* data copy done -> finalize the read job */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishReadBlock, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            /* not used */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        /* not used */
        {
            NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
/**********************************************************************************************************************
 *  WriteBlock
 *********************************************************************************************************************/
    /* NVM_STATE_WRITE_INITIAL = initial state of Write Block */
    {    //10
        {
            {   /* Create data */
                NVM_STATE_IF{NVM_QRY_ID_DATA_COPY_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_CopyNvDataToBuf, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_INITIAL)
            },
            {   /* Calculate CRC */
                NVM_STATE_ELSEIF{NVM_QRY_ID_CRC_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrc, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_INITIAL)
            },
            {   /* Redundant block -> go to next redundant block write state */
                NVM_STATE_ELSEIF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_PRI_READ)
            }
        },
        /* Native or dataset block -> go to the CRC compare check state */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITE_CRCCOMPMECHANISM)
        }
    },
    /* NVM_STATE_WRITE_CRCCOMPMECHANISM */
    {   //11
        {
            {   /* CRC calculated, check CRC compare mechanism */
                NVM_STATE_IF{NvM_QRY_CRC_COMP_MECHANISM_SKIPWRITE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishWriteBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* CRC does not match or the CRC compare mechanism is disabled for current block -> write */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
            },
            {   /* not used */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
    /* NVM_STATE_WRITE_TEST_PRI_READ */
    {  //12
        {
            {   /* read of primary NvBlock not finished -> wait */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_PRI_READ)
            },
            {   /* result of primary NvBlock OK -> test secondary NvBlock */
                NVM_STATE_IF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_LAST_RESULT_OK},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_TestBlockBlank},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_SEC_READ)
            },
            {   /* result of primary NvBlock not OK -> write primary NvBlock first */
                NVM_STATE_ELSEIF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
            }
        },
        {   /* not used */
            NVM_STATE_ELSE{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
    /* NVM_STATE_WRITE_TEST_SEC_READ */
    {  //13
        {
            {   /* read of secondary NvBlock not finished -> wait */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_TEST_SEC_READ)
            },
            {   /* Both blocks readable, CRC matches -> no write, finalize job */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NvM_QRY_CRC_COMP_MECHANISM_SKIPWRITE},
                   NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishWriteBlock},
                   NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* result of secondary NvBlock OK -> write primary NvBlock first */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_WriteNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
            }
        },
        /* result of secondary NvBlock not OK -> write secondary NvBlock first */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
        }
    },

    /* NVM_STATE_WRITE_WR_DATA_CRC_1 */
    {  //14
        {
            {   /* nv write not finished -> wait */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
            },
            {   /* result ok -> write other NvBlock */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_WriteNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
            },
            {   /* result not ok, write retries exceeded -> write other NvBlock */
                NVM_STATE_ELSEIF{NVM_QRY_ID_WRITE_RETRIES_EXCEEDED, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupOther, NVM_ACT_ID_WriteNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
            }
        },
        {   /* result not ok -> retry */
            NVM_STATE_ELSE{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_1)
        }
    },
    /* NVM_STATE_WRITE_WR_DATA_CRC_2 */
    {   //15
        {
            {   /* nv write not finished -> wait */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
            },
            {   /* result ok -> update NvState and finish block */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishWriteBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* result not ok, retries exceeded -> update NvState and finish block */
                NVM_STATE_ELSEIF{NVM_QRY_ID_WRITE_RETRIES_EXCEEDED, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishWriteBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        {   /* result not ok -> retry */
            NVM_STATE_ELSE{NVM_ACT_ID_WriteNvBlock, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITE_WR_DATA_CRC_2)
        }
    },    
/**********************************************************************************************************************
 *  RestoreBlockDefaults
 *********************************************************************************************************************/
    /* NVM_STATE_RESTORE_LOAD_ROM */
    {  //16
        {
            {   /* copy(!) busy -> continue processing */
                NVM_STATE_IF{NVM_QRY_ID_DATA_COPY_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RestoreRomDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_RESTORE_LOAD_ROM)
            },
            {   /* copy completed */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* not used */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishRestoreRomDefaults, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
#if(NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
/**********************************************************************************************************************
 *  InvalidateNvBlock
 *********************************************************************************************************************/
    /* NVM_STATE_INVALIDATING_BLOCK */
    {  //17
        {
            {   /* nv busy -> wait; if not busy LastResult is set */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_INVALIDATING_BLOCK)
            },
            {   /* nv ready, result okay, redundant -> invalidate redundant */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_REDUNDANT_BLOCK},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant, NVM_ACT_ID_InvalidateNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_INVALIDATING_BLOCK)
            },
            {   /* nv ready and (not redundant or result not ok) -> finish; result is already set */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
/**********************************************************************************************************************
 *  EraseNvBlock
 *********************************************************************************************************************/
    /* NVM_STATE_ERASE_ERASE_BLOCK */
    {  //18
        {
            {   /* nv busy -> wait */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_ERASE_ERASE_BLOCK)
            },
            {   /* nv ready, result ok, redundant -> erase redundant */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_REDUNDANT_BLOCK},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant, NVM_ACT_ID_EraseNvBlock},
                    NVM_NEXT_STATE(NVM_STATE_ERASE_ERASE_BLOCK)
            },
            {   /* nv ready, not redundant or result not ok -> finish (LastResult was previously set) */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_UpdateNvState, NVM_ACT_ID_FinishEraseBlock},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
#endif
/**********************************************************************************************************************
 *  ReadAll
 *********************************************************************************************************************/
    /* NVM_STATE_READALL_PROC_CONFIG_ID = analyze Config NV Block */
    {  //19
        {
            {   /* sub fsm still running? */
                NVM_STATE_IF{NVM_QRY_ID_SUB_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_CONFIG_ID)
            },
            {   /* sub fsm read finished */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishCfgIdCheck, NVM_ACT_ID_InitNextBlockReadAll},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            /* not used */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishCfgIdCheck, NVM_ACT_ID_InitNextBlockReadAll},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_FinishCfgIdCheck, NVM_ACT_ID_InitNextBlockReadAll},
            NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
        }
    },

#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    /* NVM_STATE_READALL_PROC_RAM_BLOCK = analyze Ram Block */
    {  //20
        {
            {   /* last block finished -> end read all */
                NVM_STATE_IF{NVM_QRY_ID_LAST_BLOCK_DONE_READALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* last block not finished, check valid/crc
                   => if the block does not have CRC, this transition will never be taken, because CRC won't be busy */
                NVM_STATE_ELSEIF{NVM_QRY_ID_RAM_VALID, NVM_QRY_ID_CRC_BUSY},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrc, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_RAM_VALIDITY)
            },
            {   /* not valid or no crc */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
        }
    },
#else
    /* NVM_STATE_READALL_PROC_RAM_BLOCK = analyze Ram Block */
    {
        {
            {   /* last block finished -> end read all */
                NVM_STATE_IF{NVM_QRY_ID_LAST_BLOCK_DONE_READALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* last block not finished, we don't check the block's validity */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
            },
            /* not used */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
        }
    },
#endif
    /* NVM_STATE_READALL_CHK_SKIP */
    {  //21
        {
            {   
                NVM_STATE_IF{NVM_QRY_ID_SKIP_BLOCK, NVM_QRY_ID_WRITE_BLOCK_ONCE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_TestBlockBlank},
                    NVM_NEXT_STATE(NVM_STATE_READALL_WR_ONCE_PROT)
            },
            {   
                NVM_STATE_ELSEIF{NVM_QRY_ID_SKIP_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_InitNextBlockReadAll},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitReadBlockFsm, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_READ_NV)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_InitReadBlockFsm, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_READ_NV)
        }
    },
    /* NVM_STATE_READALL_WR_ONCE_PROT = a write once block shall be skipped */
    {  //22
        {
            {   /* one byte was read - wait for MemHwA to finish this read job */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_WR_ONCE_PROT)
            },
            {   /* byte was read - result was ok --> next block, please */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_FinishReadBlock, NVM_ACT_ID_InitNextBlockReadAll},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {   /* result not ok, redundant -> try redundant */
                NVM_STATE_ELSEIF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetupRedundant, NVM_ACT_ID_TestBlockBlank},
                    NVM_NEXT_STATE(NVM_STATE_READALL_WR_ONCE_PROT)
            }
        },
        {   /* not redundant or done, result not ok. */
            NVM_STATE_ELSE{NVM_ACT_ID_FinishReadBlock, NVM_ACT_ID_InitNextBlockReadAll},
            NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
        }
    },
#if(NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
    /* NVM_STATE_READALL_CHK_RAM_VALIDITY = analyze Ram Block */
    {  //23
        {
            {   /* Crc not ready -> Wait */
                NVM_STATE_IF{NVM_QRY_ID_CRC_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrc, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_RAM_VALIDITY)
            },
            {   /* crc ready, crc match -> finish block and use current attributes */
                NVM_STATE_ELSEIF{NVM_QRY_ID_CRC_MATCH, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            {   /* crc mismatch */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_SetInitialAttr, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_CHK_SKIP)
        }
    },
#endif
    /* NVM_STATE_READALL_READ_NV */
    {  //24
        {
            {   /* read in process -> do nothing */
                NVM_STATE_IF{NVM_QRY_ID_SUB_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_READ_NV)
            },
            {   /* sub fsm finished */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            },
            /* not used */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
            }
        },
        /* not used */
        {
            NVM_STATE_ELSE{NVM_ACT_ID_InitNextBlockReadAll, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_READALL_PROC_RAM_BLOCK)
        }
    },
/**********************************************************************************************************************
 *  WriteAll
 *********************************************************************************************************************/
    /* NVM_STATE_WRITEALL_PROC_BLOCK */
    {  //25
        {
            {   /* write all canceled ->finish */
                NVM_STATE_IF{NVM_QRY_ID_CANCEL_WRITE_ALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },

            {   /* last block done  */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_BLOCK_DONE_WRITEALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_WAIT_MEMHWA)
            },
            {    /* not canceled, not last block done, shall be written? */
                NVM_STATE_ELSEIF{NVM_QRY_ID_BLK_WRITE_ALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_SetBlockPendingWriteAll, NVM_ACT_ID_InitWriteBlockFsm},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_WRITE_FSM)
            }
        },
        {   /* skip block */
            NVM_STATE_ELSE{NVM_ACT_ID_SetReqSkipped, NVM_ACT_ID_InitNextBlockWriteAll},
            NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
        }
    },
    /* NVM_STATE_WRITEALL_WRITE_FSM */
    {  //26
        {
            {   /* write fsm still running - do nothing */
                NVM_STATE_IF{NVM_QRY_ID_SUB_FSM_RUNNING, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_WRITE_FSM)
            },
            {   /* fsm finished - handle next block */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockWriteAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
            },
            /* not used */
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockWriteAll, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
            }
        },
        /* not used */
        {
            NVM_STATE_THEN{NVM_ACT_ID_InitNextBlockWriteAll, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_WRITEALL_PROC_BLOCK)
        }
    },
    /* NVM_STATE_WRITEALL_WAIT_MEMHWA */
    {  //27
        {
            {   /* write all cancelled */
                NVM_STATE_IF{NVM_QRY_ID_CANCEL_WRITE_ALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* MemHwA is still busy  */
                NVM_STATE_ELSEIF{NVM_QRY_ID_MEMHWA_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_WRITEALL_WAIT_MEMHWA)
            },
            {   /* MemHwA is completely IDLE */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        /* not used */
        {
            NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    },
#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
/**********************************************************************************************************************
 *  Repair Redundant Blocks
 *********************************************************************************************************************/
    /* NVM_STATE_REPAIRREDUNDANT_MAIN */
    {
        {
            {   /* check end before checking whether to suspend! - does not make sense to suspend though we are done... */
                /* same block order as read all - reached last block, job end */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_BLOCK_DONE_READALL, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksFinish, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* suspend job if there is a single or multi block job */
                NVM_STATE_IF{NVM_QRY_ID_SUSPEND_REPAIR_REDUNDANT_BLOCKS, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* we have a redundant block to check */
                NVM_STATE_ELSEIF{NVM_QRY_ID_REDUNDANT_BLOCK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlockReadCheck, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_FIRST)
            }
        },
        { /* next block */
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksInitNext, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
        }
    },
    /* NVM_STATE_REPAIRREDUNDANT_CHECK_FIRST */
    {
        {
            {   /* wait for underlying modules */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_FIRST)
            },
            {   /* suspend job if there is a single or multi block job */
                NVM_STATE_ELSEIF{NVM_QRY_ID_SUSPEND_REPAIR_REDUNDANT_BLOCKS, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* process Crc calculation in case read was successful and Crc is still busy */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_CRC_BUSY},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrc, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_FIRST)
            }
        },
        { /* first block is done, go to next block */
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlockFinishReadCheck, NVM_ACT_ID_RepairRedBlockReadCheck},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_SECOND)
        }
    },
    /* NVM_STATE_REPAIRREDUNDANT_CHECK_SECOND */
    {
        {
            {   /* wait for underlying modules */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_SECOND)
            },
            {   /* suspend job if there is a single or multi block job */
                NVM_STATE_ELSEIF{NVM_QRY_ID_SUSPEND_REPAIR_REDUNDANT_BLOCKS, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* process Crc calculation in case read was successful and Crc is still busy */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_CRC_BUSY},
                    NVM_STATE_THEN{NVM_ACT_ID_ProcessCrc, NVM_ACT_ID_Wait},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_CHECK_SECOND)
            }
        },
        {   /* second block is done, go to validate state */
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlockFinishReadCheck, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_VALIDATE_BLOCK)
        }
    },
    /* NVM_STATE_REPAIRREDUNDANT_VALIDATE_BLOCK */
    {
        {
            {   /* suspend job if there is a single or multi block job */
                NVM_STATE_ELSEIF{NVM_QRY_ID_SUSPEND_REPAIR_REDUNDANT_BLOCKS, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* repair block in case  */
                NVM_STATE_ELSEIF{NVM_QRY_ID_REPAIR_RED_BLOCK_DEFECT, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksReadValid, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_READ_VALID_BLOCK)
            },
            {   /* nothing to repair, next block */
                NVM_STATE_IF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksInitNext, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
            }
        },
        /* not used */
        {
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksInitNext, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
        }
    },
    /* NVM_STATE_REPAIRREDUNDANT_READ_VALID_BLOCK */
    {
        {
            {   /* wait for underlying modules */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_READ_VALID_BLOCK)
            },
            {   /* suspend job if there is a single or multi block job */
                NVM_STATE_ELSEIF{NVM_QRY_ID_SUSPEND_REPAIR_REDUNDANT_BLOCKS, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {   /* read OK, we do not need to check Crc, setup write job */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlockWriteInvalid, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_WRITE_INVALID_BLOCK)
            }
        },
        {   /* read not ok */
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksFinishBlock, NVM_ACT_ID_RepairRedBlocksInitNext},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
        }
    },
    /* NVM_STATE_REPAIRREDUNDANT_WRITE_INVALID_BLOCK */
    {
        {
            {   /* wait for underlying modules */
                NVM_STATE_IF{NVM_QRY_ID_NV_BUSY, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Wait, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_WRITE_INVALID_BLOCK)
            },
            {   /* validate write job, next block */
                NVM_STATE_ELSEIF{NVM_QRY_ID_LAST_RESULT_OK, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksFinishBlock, NVM_ACT_ID_RepairRedBlocksInitNext},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
            },
            {   /* not used */
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksFinishBlock, NVM_ACT_ID_RepairRedBlocksInitNext},
                    NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
            }
        },
        /* not used */
        {
            NVM_STATE_THEN{NVM_ACT_ID_RepairRedBlocksFinishBlock, NVM_ACT_ID_RepairRedBlocksInitNext},
            NVM_NEXT_STATE(NVM_STATE_REPAIRREDUNDANT_MAIN)
        }
    },
#endif
/**********************************************************************************************************************
 *  NvM job finished
 *********************************************************************************************************************/
    /* NVM_STATE_FSM_FINISHED */
    /* always stay in this state. Only by re-initializing a FSM exits this state */
    {  //28
        {
            {
                NVM_STATE_IF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            },
            {
                NVM_STATE_ELSEIF{NVM_QRY_ID_TRUE, NVM_QRY_ID_TRUE},
                    NVM_STATE_THEN{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
                    NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
            }
        },
        {
            NVM_STATE_ELSE{NVM_ACT_ID_Nop, NVM_ACT_ID_Nop},
            NVM_NEXT_STATE(NVM_STATE_FSM_FINISHED)
        }
    }
};

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/**********************************************************************************************************************
 *  IMPLEMENTATION
 *********************************************************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
*  NvM_JobProcInit
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, NVM_PRIVATE_CODE) NvM_JobProcInit(void)
{
    NvM_CurrentJob_t.JobServiceId_t = NVM_INT_FID_NO_JOB_PENDING;

    NvM_CurrentBlockInfo_t.InternalFlags_u8 = 0;

    NvM_JobMainState_t = NVM_STATE_FSM_FINISHED;
    NvM_JobSubState_t  = NVM_STATE_FSM_FINISHED;
    NvM_TaskState_t    = NVM_STATE_IDLE;
}

/**********************************************************************************************************************
*  NvM_Fsm
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(NvM_StateType, NVM_PRIVATE_CODE) NvM_Fsm(NvM_StateType NvM_CurrentState_t)
{
    /* local variables */
    NvM_StateType NvM_RetState_tloc;
    NvM_StateChangeActionsPtrType ChangeActions_ptloc;
    CONSTP2CONST(NvM_StateDescrType, AUTOMATIC, NVM_PRIVATE_CONST) CurrentState_ptloc =
        &NvM_StateDescrTable_at[NvM_CurrentState_t];

    /* Execute the first query, if it is fulfilled then do the corresponding
     * action and return with the next state to NvM_MainFunction(). If the first
     * query is not true then execute next query as long as the right exit is found.
     */
    /* PRQA S 3344 11 */ /* MD_NvM_13.2 */
    if(NvM_FsmQuery(CurrentState_ptloc->ChangeConditions_at[0].Queries_at)) /* SBSW_NvM_FuncCall_PtrParam_FsmQuery */
    {
        NvM_RetState_tloc = CurrentState_ptloc->ChangeConditions_at[0].NextState_t;
        ChangeActions_ptloc = &CurrentState_ptloc->ChangeConditions_at[0].Actions_t;
    }
    else if (NvM_FsmQuery(CurrentState_ptloc->ChangeConditions_at[1].Queries_at)) /* SBSW_NvM_FuncCall_PtrParam_FsmQuery */
    {
        NvM_RetState_tloc = CurrentState_ptloc->ChangeConditions_at[1].NextState_t;
        ChangeActions_ptloc = &CurrentState_ptloc->ChangeConditions_at[1].Actions_t;
    }
    else if (NvM_FsmQuery(CurrentState_ptloc->ChangeConditions_at[2].Queries_at)) /* SBSW_NvM_FuncCall_PtrParam_FsmQuery */
    {
        NvM_RetState_tloc = CurrentState_ptloc->ChangeConditions_at[2].NextState_t;
        ChangeActions_ptloc = &CurrentState_ptloc->ChangeConditions_at[2].Actions_t;
    }
    else
    {
        NvM_RetState_tloc = CurrentState_ptloc->FinalCondition_t.NextState_t;
        ChangeActions_ptloc = &CurrentState_ptloc->FinalCondition_t.Actions_t;
    }

    NvM_FsmAction(ChangeActions_ptloc); /* SBSW_NvM_FuncCall_PtrParam_FsmAction */

    return NvM_RetState_tloc;
}

/**********************************************************************************************************************
*  NvM_FsmQuery
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
NVM_LOCAL FUNC(boolean, NVM_PRIVATE_CODE) NvM_FsmQuery(NvM_StateQueryPtrType NvM_Queries_at)
{
    /* Currently there are Queries with side-effects, forcing
     * execution in the defined order
     */

    boolean retVal = NvM_QueryTable_ap[NvM_Queries_at[0u]](); /* SBSW_NvM_FuncPtrCall_QueryAction */

    /* PRQA S 3344 1 */ /* MD_NvM_13.2 */
    if (retVal)
    {
        retVal = NvM_QueryTable_ap[NvM_Queries_at[1u]](); /* SBSW_NvM_FuncPtrCall_QueryAction */
    }

    return retVal;
}

/**********************************************************************************************************************
*  NvM_FsmAction
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
NVM_LOCAL FUNC(void, NVM_PRIVATE_CODE) NvM_FsmAction(NvM_StateChangeActionsPtrType NvM_Actions_pt)
{
    NvM_ActionTable_ap[NvM_Actions_pt->ExitHandler_t](); /* SBSW_NvM_FuncPtrCall_QueryAction */
    NvM_ActionTable_ap[NvM_Actions_pt->EntryHandler_t](); /* SBSW_NvM_FuncPtrCall_QueryAction */
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/* PRQA L:inclusions */
/* PRQA L:macros */

/*---- End of File ---------------------------------------------------------*/
