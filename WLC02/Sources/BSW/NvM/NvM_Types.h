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
 *         File:  NvM_Types.h
 *    Component:  MemService_AsrNvM
 *       Module:  NvM
 *    Generator:  -
 *
 *********************************************************************************************************************/

/* Do not modify this file! */

/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
#if (!defined NVM_TYPES_H_)
#define NVM_TYPES_H_

/**********************************************************************************************************************
 * VERSION IDENTIFICATION
 *********************************************************************************************************************/
#define NVM_TYPES_MAJOR_VERSION       (5u)
#define NVM_TYPES_MINOR_VERSION       (8u)
#define NVM_TYPES_PATCH_VERSION       (0u)

/**********************************************************************************************************************
 * API TYPE DEFINITIONS
 *********************************************************************************************************************/
/* type of a request result */
#ifndef Rte_TypeDef_NvM_RequestResultType
typedef uint8 NvM_RequestResultType;
#endif

#ifndef Rte_TypeDef_NvM_BlockIdType
typedef uint16 NvM_BlockIdType;
#endif

/* result values of asynchronous requests (stored in the RAM Mngmnt),
    * They are also defined by the RTE, since these are the important values for an SW-C */

#ifndef NVM_REQ_OK
# define NVM_REQ_OK               (0u)  /* The last asynchronous request has been finished successfully */
#endif
#ifndef NVM_REQ_NOT_OK
# define NVM_REQ_NOT_OK           (1u)  /* The last asynchronous request has been finished unsuccessfully */
#endif
#ifndef NVM_REQ_PENDING
# define NVM_REQ_PENDING          (2u)  /* An asynchronous request is currently being processed */
#endif
#ifndef NVM_REQ_INTEGRITY_FAILED
# define NVM_REQ_INTEGRITY_FAILED (3u)  /* Result of the last NvM_ReadBlock or NvM_ReadAll is an integrity failure */
#endif
#ifndef NVM_REQ_BLOCK_SKIPPED
# define NVM_REQ_BLOCK_SKIPPED    (4u)  /* The referenced block was skipped during a multi block request */
#endif
#ifndef NVM_REQ_NV_INVALIDATED
# define NVM_REQ_NV_INVALIDATED   (5u)  /* The NV block is invalidated. */
#endif
#ifndef NVM_REQ_CANCELED
# define NVM_REQ_CANCELED        (6u)  /* A WriteAll was cancelled */
#endif
#ifndef NVM_REQ_REDUNDANCY_FAILED
# define NVM_REQ_REDUNDANCY_FAILED  (7u) /* A redundant block lost its redundancy */
#endif
#ifndef NVM_REQ_RESTORED_FROM_ROM
# define NVM_REQ_RESTORED_FROM_ROM  (8u) /* Default data from ROM are restored */
#endif

/* Service ID type */
#ifndef Rte_TypeDef_NvM_ServiceIdType
typedef uint8 NvM_ServiceIdType;   /* type of a service id */
#endif

/* These Sevice IDs are important to an SW-C, as they can be passed to it in the
"single block job end notification" callback.
Therefore they are also defined by the RTE */
#ifndef NVM_READ_BLOCK
# define NVM_READ_BLOCK             (6u) /* Service ID NvM_ReadBlock() */
#endif
#ifndef NVM_WRITE_BLOCK
# define NVM_WRITE_BLOCK            (7u) /* Service ID NvM_WriteBlock() */
#endif
#ifndef NVM_RESTORE_BLOCK_DEFAULTS
# define NVM_RESTORE_BLOCK_DEFAULTS (8u) /* Service ID NvM_RestoreBlockDefaults() */
#endif
#ifndef NVM_ERASE_BLOCK
# define NVM_ERASE_BLOCK            (9u) /* Service ID NvM_EraseNvBlock() */
#endif
#ifndef NVM_INVALIDATE_NV_BLOCK
# define NVM_INVALIDATE_NV_BLOCK   (11u) /* Service ID NvM_InvalidateNvBlock() */
#endif
#ifndef NVM_READ_ALL
# define NVM_READ_ALL              (12u) /* Service ID NvM_ReadAll() */
#endif

/* Service Ids of the different service routines of the NVM
 * These sevice IDs should never be defined by the RTE. However, it doesn't hurt to protect them ... */

#ifndef NVM_INIT
# define NVM_INIT                   (0u) /* Service ID NvM_Init() */
#endif
#ifndef NVM_SET_DATA_INDEX
# define NVM_SET_DATA_INDEX         (1u) /* Service ID NvM_SetDataIndex() */
#endif
#ifndef NVM_GET_DATA_INDEX
# define NVM_GET_DATA_INDEX         (2u) /* Service ID NvM_GetDataIndex() */
#endif
#ifndef NVM_SET_BLOCK_PROTECTION
# define NVM_SET_BLOCK_PROTECTION   (3u) /* Service ID NvM_SetBlockProtection() */
#endif
#ifndef NVM_GET_ERROR_STATUS
# define NVM_GET_ERROR_STATUS       (4u) /* Service ID NvM_GetErrorStatus() */
#endif
#ifndef NVM_SET_RAM_BLOCK_STATUS
# define NVM_SET_RAM_BLOCK_STATUS   (5u) /* Service ID NvM_SetRamBlockStatus() */
#endif

#ifndef NVM_CANCEL_WRITE_ALL
# define NVM_CANCEL_WRITE_ALL      (10u) /* Service ID NvM_CancelRequest() */
#endif

#ifndef NVM_WRITE_ALL
# define NVM_WRITE_ALL             (13u) /* Service ID NvM_WriteAll() */
#endif
#ifndef NVM_MAINFUNCTION
# define NVM_MAINFUNCTION          (14u) /* Service ID NvM_MainFunction() */
#endif
#ifndef NVM_GET_VERSION_INFO
# define NVM_GET_VERSION_INFO      (15u) /* Service ID NvM_GetVersionInfo() */
#endif

#ifndef NVM_CANCEL_JOBS
# define NVM_CANCEL_JOBS           (16u) /* Service ID NvM_CancelJobs() */
#endif
#ifndef NVM_SET_BLOCK_LOCK_STATUS
# define NVM_SET_BLOCK_LOCK_STATUS (19u) /* Service ID NvM_SetBlockProtection() */
#endif
#ifndef NVM_KILL_WRITE_ALL
# define NVM_KILL_WRITE_ALL        (20u) /* Service ID NvM_KillWriteAll() */
#endif

#ifndef NVM_REPAIR_REDUNDANT_BLOCKS
# define NVM_REPAIR_REDUNDANT_BLOCKS (21u) /* Service ID NvM_RepairRedundantBlocks() */
#endif

#endif /* NVM_TYPES_H_ */
/* ---- End of File --------------------------------------------------------- */
