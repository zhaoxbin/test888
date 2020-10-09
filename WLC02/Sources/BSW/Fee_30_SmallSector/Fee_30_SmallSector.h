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
 *         \file  Fee_30_SmallSector.h
 *        \brief  FEE header file
 *
 *      \details  The Fee Flash Emulation abstracts from the device specific addressing scheme and segmentation and
 *                provides a virtual addressing scheme and segmentation to upper layers as well as a virtually
 *                unlimited number of erase cycles.
 *
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  AUTHOR IDENTITY
 *--------------------------------------------------------------------------------------------------------------------
 *  Initials    Name                    Company
 *  --------    ---------------------   ----------------------------------------------------------------------------
 *  virgmi      Michael Goss            Vector Informatik GmbH
 *  virbka      Bernhard Karl           Vector Informatik GmbH
 *--------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *--------------------------------------------------------------------------------------------------------------------
 *  Version     Date        Author      Change Id      Description
 * -------------------------------------------------------------------------------------------------------------------
 *  1.00.00     2016-04-21  virgmi      ESCAN00089697  FEAT-1839: SmallSectorFee Initial version
 *  1.00.01     2016-09-30  virgmi      ESCAN00092145  Correct results are passed to NvM via callback services
 *                                      FEAT-2036      AUTOSAR SWS SPEC-Item traceability was introduced
 *  1.00.02     2016-11-17  virgmi      ESCAN00092823  ASR4 variant of MEMIF_JOB_CANCELED is now used
 *                                      ESCAN00092861  Instance status is determined correctly
 *  2.00.00     2017-09-29  virgmi      STORY-1231     Introduce additional erase pattern in each dataset of SmallSectorFee
 *                                      ESCAN00094013  Missing callback configuration is not detected
 *                                      ESCAN00096859  Added check for invalid dataset index within block number
 *  2.00.01     2018-01-02  virbka      ESCAN00096901  Possible incorrect interpretation of last page status
 *                                      ESCAN00097748  Memory corruption of management information leads to dead lock
 *                                                     of corresponding block
 *  2.01.00     2019-03-07  virbka      STORY-6251     MISRA-C:2012: If_AsrIfFeeSmallSector
 *********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/
#ifndef FEE_30_SMALLSECTOR_H
# define FEE_30_SMALLSECTOR_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "Std_Types.h"
# include "MemIf_Types.h"
# include "Fee_30_SmallSector_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_VENDOR_ID                    (30u)
# define FEE_30_SMALLSECTOR_MODULE_ID                    (21u)
# define FEE_30_SMALLSECTOR_INSTANCE_ID                  (0u)

# define FEE_30_SMALLSECTOR_AR_RELEASE_MAJOR_VERSION     (4u)
# define FEE_30_SMALLSECTOR_AR_RELEASE_MINOR_VERSION     (0u)
# define FEE_30_SMALLSECTOR_AR_RELEASE_REVISION_VERSION  (3u)

# define FEE_30_SMALLSECTOR_SW_MAJOR_VERSION             (2u)
# define FEE_30_SMALLSECTOR_SW_MINOR_VERSION             (1u)
# define FEE_30_SMALLSECTOR_SW_PATCH_VERSION             (0u)


/**** Error Codes in Development-Mode ******************************************************************************/
/* AUTOSAR 4 development error codes */
# define FEE_30_SMALLSECTOR_E_NO_ERROR                   (0x00u)
# define FEE_30_SMALLSECTOR_E_UNINIT                     (0x01u)
# define FEE_30_SMALLSECTOR_E_INVALID_BLOCK_NO           (0x02u)
# define FEE_30_SMALLSECTOR_E_INVALID_BLOCK_OFS          (0x03u)
# define FEE_30_SMALLSECTOR_E_INVALID_DATA_POINTER       (0x04u)
# define FEE_30_SMALLSECTOR_E_INVALID_BLOCK_LEN          (0x05u)
# define FEE_30_SMALLSECTOR_E_BUSY                       (0x06u)
# define FEE_30_SMALLSECTOR_E_BUSY_INTERNAL              (0x07u)
# define FEE_30_SMALLSECTOR_E_INVALID_CANCEL             (0x08u)

/* Development error codes additionally defined to AUTOSAR */
# define FEE_30_SMALLSECTOR_E_PARAM_MODE                 (0x0Au)

/**** Fee Service Identification ************************************************************************************/
# define FEE_30_SMALLSECTOR_SID_INIT                     (0x00u)
# define FEE_30_SMALLSECTOR_SID_SET_MODE                 (0x01u)
# define FEE_30_SMALLSECTOR_SID_READ                     (0x02u)
# define FEE_30_SMALLSECTOR_SID_WRITE                    (0x03u)
# define FEE_30_SMALLSECTOR_SID_CANCEL                   (0x04u)
# define FEE_30_SMALLSECTOR_SID_GET_STATUS               (0x05u)
# define FEE_30_SMALLSECTOR_SID_GET_JOB_RESULT           (0x06u)
# define FEE_30_SMALLSECTOR_SID_INVALIDATE_BLOCK         (0x07u)
# define FEE_30_SMALLSECTOR_SID_GET_VERSION_INFO         (0x08u)
# define FEE_30_SMALLSECTOR_SID_ERASE_IMMEDIATE_BLOCK    (0x09u)
# define FEE_30_SMALLSECTOR_SID_JOB_END_NOTIFICATION     (0x10u)
# define FEE_30_SMALLSECTOR_SID_JOB_ERROR_NOTIFICATION   (0x11u)
# define FEE_30_SMALLSECTOR_SID_MAINFUNCTION             (0x12u)


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

typedef P2VAR(uint8, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_VarDataPtrType;

typedef enum
{
  FEE_30_SMALLSECTOR_READ_JOB = 0,
  FEE_30_SMALLSECTOR_WRITE_JOB,
  FEE_30_SMALLSECTOR_INVALIDATE_JOB,
  FEE_30_SMALLSECTOR_ERASE_JOB
} Fee_30_SmallSector_JobType;

typedef enum
{
  FEE_30_SMALLSECTOR_PATTERN_INIT = 0,
  FEE_30_SMALLSECTOR_PATTERN_BLANK,
  FEE_30_SMALLSECTOR_PATTERN_VALID,
  FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT
} Fee_30_SmallSector_StaticPatternState;

typedef struct
{
  uint16 Blockid;
  uint16 BlockNumber;
  uint16 BlockOffset;
  uint16 Length;
  Fee_30_SmallSector_VarDataPtrType DataBufferPtr;
  Fee_30_SmallSector_JobType JobType;
}Fee_30_SmallSector_UserJobParameterType;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Init()
 *********************************************************************************************************************/
/*!
 * \brief      Initializes the Fee Flash Emulation module.
 * \details    Initializes internal component parameter in order to prepare module for successful job processing.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-107316
 * \trace DSGN-Fee23460
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Init (void);

 /**********************************************************************************************************************
  *  Fee_30_SmallSector_Read()
  *********************************************************************************************************************/
/*!
 * \brief      Reads Length bytes of block BlockNumber at offset BlockOffset into the buffer DataBufferPtr.
 * \details    Reads Length bytes of block BlockNumber at offset BlockOffset into the buffer DataBufferPtr.
 * \param[in]  BlockNumber
 * \param[in]  BlockOffset - read offset within block
 * \param[in]  DataBufferPtr
 * \param[in]  Length of read job
 * \return     Returns if requested job has been accepted by the FEE module.
 * \pre        FEE component status is MEMIF_IDLE.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 * \trace CREQ-109013
 * \trace DSGN-Fee23438
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Read (uint16 Blockid,uint16 BlockNumber, uint16 BlockOffset,
    Fee_30_SmallSector_VarDataPtrType DataBufferPtr, uint16 Length);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Write()
 *********************************************************************************************************************/
/*!
 * \brief      Writes the contents of the DataBufferPtr to the block BlockNumber.
 * \details    Writes the contents of the DataBufferPtr to the block BlockNumber.
 * \param[in]  BlockNumber
 * \param[in]  DataBufferPtr
 * \return     Returns if requested job has been accepted by the FEE module.
 * \pre        FEE component status is MEMIF_IDLE.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 * \trace CREQ-109012
 * \trace DSGN-Fee23439
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Write (uint16 Blockid,uint16 BlockNumber, Fee_30_SmallSector_VarDataPtrType DataBufferPtr);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_InvalidateBlock()
 *********************************************************************************************************************/
/*!
 * \brief      Invalidates the block BlockNumber.
 * \details    Invalidates the block BlockNumber.
 * \param[in]  BlockNumber
 * \return     Returns if requested job has been accepted by the FEE module.
 * \pre        FEE component status is MEMIF_IDLE.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 * \trace CREQ-109014
 * \trace DSGN-Fee23440
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_InvalidateBlock (uint16 Blockid,uint16 BlockNumber);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_EraseImmediateBlock()
 *********************************************************************************************************************/
/*!
 * \brief      Erases the block BlockNumber.
 * \details    Erases the entire dataset which is referenced by BlockNumber.
 * \param[in]  BlockNumber
 * \return     Returns if requested job has been accepted by the FEE module.
 * \pre        FEE component status is MEMIF_IDLE.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 * \trace CREQ-109015
 * \trace DSGN-Fee23441
 */
FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_EraseImmediateBlock (uint16 Blockid,uint16 BlockNumber);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Cancel()
 *********************************************************************************************************************/
/*!
 * \brief      Cancels the ongoing asynchronous operation.
 * \details    Cancels the ongoing asynchronous operation.
 * \pre        FEE component status is MEMIF_BUSY.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-109011
 * \trace DSGN-Fee23452
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Cancel (void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_GetStatus()
 *********************************************************************************************************************/
/*!
 * \brief      Service to return the status.
 * \details    Returns current status of FEE module.
 * \return     Status of FEE module.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-109009
 * \trace DSGN-Fee23461
 */
FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_GetStatus (void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_GetJobResult()
 *********************************************************************************************************************/
/*!
 * \brief      Service to return the job result.
 * \details    Returns current job result of FEE module.
 * \return     Job result of FEE module.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-109010
 * \trace DSGN-Fee23461
 */
FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_GetJobResult (void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * \brief      Service to get the version information of FEE module.
 * \details    Stores version information, i.e. Module Id, Vendor Id, Vendor specific version numbers,
 *             to structure pointed by VersionInfoPtr.
 * \param[in]  VersionInfoPtr
 * \pre        GetVersionInfo API is enabled via pre-compile switch.
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-107318
 * \trace DSGN-Fee22733
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_GetVersionInfo (P2VAR(Std_VersionInfoType, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) VersionInfoPtr);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SetMode()
 *********************************************************************************************************************/
/*!
 * \brief      Sets the mode.
 * \details    Sets the mode Mode for the underlying Flash driver.
 * \param[in]  Mode
 * \pre        SetMode API is enabled via pre-compile switch.
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_SetMode (MemIf_ModeType Mode);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_SuspendWrites()
 *********************************************************************************************************************/
/*!
 * \brief      Blocks all write jobs
 * \details    Blocks all write jobs. Pending write jobs are paused until writes are resumed again.
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-109760
 * \trace DSGN-Fee23489
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_SuspendWrites (void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_ResumeWrites()
 *********************************************************************************************************************/
/*!
 * \brief      Resumes previously suspended write jobs
 * \details    Resumes previously suspended write jobs
 * \pre        Write jobs were previously suspended by SuspendWrites API
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-109761
 * \trace DSGN-Fee23489
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_ResumeWrites (void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_MainFunction()
 *********************************************************************************************************************/
/*!
 * \brief      Service to handle the requested jobs and the internal management operations.
 * \details    Service to handle the requested jobs and the internal management operations.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_MainFunction (void);

# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h"


# ifdef FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE /* COV_FEE_30_SMALLSECTOR_INTERNAL_SERVICE */

#  define FEE_30_SMALLSECTOR_START_SEC_CODE
#  include "MemMap.h"

/**********************************************************************************************************************
 *  Fee_30_SmallSector_AlignValue()
 *********************************************************************************************************************/
/*!
 * \brief      Aligns passed Value to Alignment
 * \details    Aligns passed Value to Alignment. If Value is not aligned, the next larger aligned value is returned
 * \param[in]  Value
 * \param[in]  Alignment
 * \return     Aligned value
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint32, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_AlignValue(uint32 Value, uint16 Alignment);

#  define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#  include "MemMap.h"

# endif /* FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE */

#endif /* FEE_30_SMALLSECTOR_H */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector.h
 *********************************************************************************************************************/
