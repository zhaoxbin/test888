/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Rte_SWC_WLCAPP_Type.h
 *           Config:  D:/Auto/Demo/WLCProject/WLC.dpa
 *        SW-C Type:  SWC_WLCAPP
 *  Generation Time:  2020-09-22 21:25:06
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Application types header file for SW-C <SWC_WLCAPP> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SWC_WLCAPP_TYPE_H
# define _RTE_SWC_WLCAPP_TYPE_H

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

# include "Rte_Type.h"

/**********************************************************************************************************************
 * Range, Invalidation, Enumeration and Bit Field Definitions
 *********************************************************************************************************************/

# ifndef COMM_NO_COMMUNICATION
#  define COMM_NO_COMMUNICATION (0U)
# endif

# ifndef COMM_SILENT_COMMUNICATION
#  define COMM_SILENT_COMMUNICATION (1U)
# endif

# ifndef COMM_FULL_COMMUNICATION
#  define COMM_FULL_COMMUNICATION (2U)
# endif

# ifndef DEM_EVENT_STATUS_PASSED
#  define DEM_EVENT_STATUS_PASSED (0U)
# endif

# ifndef DEM_EVENT_STATUS_FAILED
#  define DEM_EVENT_STATUS_FAILED (1U)
# endif

# ifndef DEM_EVENT_STATUS_PREPASSED
#  define DEM_EVENT_STATUS_PREPASSED (2U)
# endif

# ifndef DEM_EVENT_STATUS_PREFAILED
#  define DEM_EVENT_STATUS_PREFAILED (3U)
# endif

# ifndef DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED
#  define DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED (4U)
# endif

# ifndef DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED
#  define DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED (5U)
# endif

# ifndef DEM_EVENT_STATUS_FAILED_CONDITIONS_NOT_FULFILLED
#  define DEM_EVENT_STATUS_FAILED_CONDITIONS_NOT_FULFILLED (6U)
# endif

# ifndef DEM_EVENT_STATUS_PREPASSED_CONDITIONS_NOT_FULFILLED
#  define DEM_EVENT_STATUS_PREPASSED_CONDITIONS_NOT_FULFILLED (7U)
# endif

# ifndef DEM_EVENT_STATUS_PREFAILED_CONDITIONS_NOT_FULFILLED
#  define DEM_EVENT_STATUS_PREFAILED_CONDITIONS_NOT_FULFILLED (8U)
# endif

# ifndef DEM_CYCLE_STATE_START
#  define DEM_CYCLE_STATE_START (0U)
# endif

# ifndef DEM_CYCLE_STATE_END
#  define DEM_CYCLE_STATE_END (1U)
# endif

# ifndef NVM_REQ_OK
#  define NVM_REQ_OK (0U)
# endif

# ifndef NVM_REQ_NOT_OK
#  define NVM_REQ_NOT_OK (1U)
# endif

# ifndef NVM_REQ_PENDING
#  define NVM_REQ_PENDING (2U)
# endif

# ifndef NVM_REQ_INTEGRITY_FAILED
#  define NVM_REQ_INTEGRITY_FAILED (3U)
# endif

# ifndef NVM_REQ_BLOCK_SKIPPED
#  define NVM_REQ_BLOCK_SKIPPED (4U)
# endif

# ifndef NVM_REQ_NV_INVALIDATED
#  define NVM_REQ_NV_INVALIDATED (5U)
# endif

# ifndef NVM_REQ_CANCELED
#  define NVM_REQ_CANCELED (6U)
# endif

# ifndef NVM_REQ_REDUNDANCY_FAILED
#  define NVM_REQ_REDUNDANCY_FAILED (7U)
# endif

# ifndef NVM_REQ_RESTORED_FROM_ROM
#  define NVM_REQ_RESTORED_FROM_ROM (8U)
# endif

# ifndef NVM_READ_BLOCK
#  define NVM_READ_BLOCK (6U)
# endif

# ifndef NVM_WRITE_BLOCK
#  define NVM_WRITE_BLOCK (7U)
# endif

# ifndef NVM_RESTORE_BLOCK_DEFAULTS
#  define NVM_RESTORE_BLOCK_DEFAULTS (8U)
# endif

# ifndef NVM_ERASE_BLOCK
#  define NVM_ERASE_BLOCK (9U)
# endif

# ifndef NVM_INVALIDATE_NV_BLOCK
#  define NVM_INVALIDATE_NV_BLOCK (11U)
# endif

# ifndef NVM_READ_ALL
#  define NVM_READ_ALL (12U)
# endif



/**********************************************************************************************************************
 * Definitions for Mode Management
 *********************************************************************************************************************/
# ifndef RTE_MODETYPE_ComMMode
#  define RTE_MODETYPE_ComMMode
typedef uint8 Rte_ModeType_ComMMode;
# endif

# define RTE_MODE_SWC_WLCAPP_ComMMode_COMM_FULL_COMMUNICATION (0U)
# ifndef RTE_MODE_ComMMode_COMM_FULL_COMMUNICATION
#  define RTE_MODE_ComMMode_COMM_FULL_COMMUNICATION (0U)
# endif
# define RTE_MODE_SWC_WLCAPP_ComMMode_COMM_NO_COMMUNICATION (1U)
# ifndef RTE_MODE_ComMMode_COMM_NO_COMMUNICATION
#  define RTE_MODE_ComMMode_COMM_NO_COMMUNICATION (1U)
# endif
# define RTE_MODE_SWC_WLCAPP_ComMMode_COMM_SILENT_COMMUNICATION (2U)
# ifndef RTE_MODE_ComMMode_COMM_SILENT_COMMUNICATION
#  define RTE_MODE_ComMMode_COMM_SILENT_COMMUNICATION (2U)
# endif
# define RTE_TRANSITION_SWC_WLCAPP_ComMMode (3U)
# ifndef RTE_TRANSITION_ComMMode
#  define RTE_TRANSITION_ComMMode (3U)
# endif

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_SWC_WLCAPP_TYPE_H */
