/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Internal.h                                              */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015 - 2017 Renesas Electronics Corporation                   */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision of prototypes for internal functions of Flash Wrapper Component. */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        X1x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * V1.0.0:  08-Oct-2015  : Initial Version
 *
 * V1.1.0:  04-Dec-2015    :As a part of F1K 4.00.01 release following changes
 *                          are made:
 *                           1. Added function declaration of Fls_SetIntReq,
 *                              Fls_InitiateEraseJob, Fls_InitiateWriteJob,
 *                              Fls_FcuWritePreCheck, Fls_InitiateReadJob,
 *                              Fls_CompleteReadJob, Fls_FcuSwitchBFlash,
 *                              Fls_InitiateBlankCheckJob, Fls_ProcessJobResult,
 *                              Fls_ClearIntReq, Fls_PreFcuInitCheck,
 *                              Fls_RestoreIntReq, Fls_GetIntReq,
 *                              Fls_RestoreJobData, Fls_ClearBackUpData,
 *                              Fls_ProcessSuspend, Fls_BackupJobData,
 *                              Fls_TimeOutCheckAndProcessing,
 *                              Fls_FcuPrepareEnvironment, Fls_FcuSwitchMode,
 *                              Fls_FcuForcedStop, Fls_FcuClearStatus,
 *                              Fls_FcuVerifyChecksum, Fls_FcuGetFWParam
 *                              Fls_FcuGetDFSize, Fls_FcuInitRAM,
 *                              Fls_FcuSetFrequency, Fls_FcuInit,
 *                              Fls_FcuDataCopy, Fls_FcuOffsetDataCopy,
 *                              Fls_FcuErasePreCheck, Fls_FcuCheckJobStatus,
 *                              Fls_FcuCheckBCJobStatus, Fls_SuspendPreCheck,
 *                              Fls_FcuBlankCheckResult, Fls_FcuClearCache
 *                              Fls_FcuPerformBlankCheck, Fls_FcuCopytoRam,
 *                              Fls_ReadCopyToTarget, Fls_DetErrorCheck,
 *                              Fls_FcuResetErrorBits.
 *                           2. Removed functions Fls_VerifyECC,
 *                              Fls_ProcessErase, Fls_VerifyAfterWrite,
 *                              Fls_VerifyAfterErase, Fls_ProcessWrite.
 *
 * V1.1.1:  24-Jun-2016 : #ARDAABD-454
 *                        1.  Removed functions: Fls_PreFcuInitCheck,
 *                            Fls_FcuWritePreCheck, Fls_FcuSwitchMode,
 *                            Fls_FcuPrepareEnvironment, Fls_FcuForcedStop,
 *                            Fls_FcuClearStatus,Fls_FcuVerifyChecksum,
 *                            Fls_FcuGetFWParam, Fls_FcuGetDFSize,
 *                            Fls_FcuInitRAM, Fls_FcuSetFrequency,Fls_FcuInit,
 *                            Fls_FcuDataCopy, Fls_FcuOffsetDataCopy,
 *                            Fls_FcuErasePreCheck, Fls_FcuCheckJobStatus,
 *                            Fls_FcuCheckBCJobStatus, Fls_FcuBlankCheckResult,
 *                            Fls_FcuPerformBlankCheck, Fls_FcuSuspendCheck,
 *                            Fls_FcuResetErrorBits, Fls_FcuCopytoRam,
 *                            Fls_FcuSwitchBFlash, Fls_FcuClearCache
 *                            As they are moved to Fls_Private.h file
 *
 * V1.2.0:  28-Sep-2016 : #ARDAABD-843
 *                        1. Removed support for
 *                           FLS_AR_HIGHER_VERSION / FLS_AR_LOWER_VERSION
 *
 * V2.0.0:  31-Oct-2016 : #ARDAABD-650
 *                        1. Added Fls_SuspendPreCheck
 *
 * V2.1.0:  11-Nov-2016 : #ARDAABD-732 - Addedfunction declaration of
 *                           Fls_InitiateDmaWriteJob, Fls_DisableFaciEndInt,
 *                           Fls_EnableFaciEndInt, Fls_DmaIsr
 *
 * V2.1.1   16-Jan-2017 : #ARDAABD-459 - Added Fls_DisableDmaChannel function
 *                           declaration.
 *
 * V2.1.0:  30-Jan-2017  :  #ARDAABD-571
 *                          1. Addded MemMap_Fls vs MemMap.h inclusion based on
 *                             AR revision.
 *                          2. Added Fls_HWCheckConsistency API related data
 *                             mirroring.
 *                          3. Changes after review.
 *
 * V2.2.0:  31-Jan-2017 : #ARDAABD-454
 *                        1. Fls_DmaInit moved in Fls_Internal.
 *
 * V2.2.1:  26-May-2017 : #ARDAABD-446
 *                        Removed declaration of Fls_InitiateReadJob and
 *                        Fls_CompleteReadJob functions. Added declaration of
 *                        Fls_PerformBlankCheckForReadOp and Fls_ProcessRead
 *                        functions.
 *
 * V2.2.2   1-Jun-2017  : #ARDAABD-446: The following updates are made after
 *                        review No.096":
 *                        - Removed Fls_ReadCopyToTarget function declaration
 *                        - removed "extern" keyword for Fls_ProcessRead and
 *                         Fls_PerformBlankCheckForReadOp functions
 * V2.2.3  24-Aug-2017  : #ARDAABD-2151 - Corrected QAC/MISRA Warning.
 * V2.2.4  20-Jun-2017  : As per ARDAABD-3853, traceability has been improved.
 *
 */
/******************************************************************************/
#ifndef FLS_INTERNAL_H
#define FLS_INTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Included for version information macros */
#include "Fls.h"
#include "Fls_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR release version information */
#define FLS_INTERNAL_AR_RELEASE_MAJOR_VERSION    FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_INTERNAL_AR_RELEASE_MINOR_VERSION    FLS_AR_RELEASE_MINOR_VERSION
#define FLS_INTERNAL_AR_RELEASE_REVISION_VERSION \
                                     FLS_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FLS_INTERNAL_SW_MAJOR_VERSION    FLS_SW_MAJOR_VERSION
#define FLS_INTERNAL_SW_MINOR_VERSION    FLS_SW_MINOR_VERSION

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_InitiateEraseJob" */
extern FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InitiateEraseJob(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_MainErase". */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_MainErase(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_InitiateWriteJob" */
extern FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InitiateWriteJob(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#if ((FLS_SET_MODE_API == STD_ON) &&\
    (FLS_DMA_INSTANCES != FLS_DMA_ZERO))
#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_InitiateDmaWriteJob" */
extern FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InitiateDmaWriteJob(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_DisableDmaChannel" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_DisableDmaChannel(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
#endif /* End of #if ((FLS_SET_MODE_API == STD_ON) &&\
                      (FLS_DMA_INSTANCES != FLS_DMA_ZERO)) */

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_MainWrite" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_MainWrite(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#if (FLS_COMPARE_API == STD_ON)

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_MainCompare" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_MainCompare(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ProcessCompare" */
FUNC(MemIf_JobResultType, FLS_PRIVATE_CODE) Fls_ProcessCompare(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_CompareWithTargetBuff" */
FUNC(MemIf_JobResultType, FLS_PRIVATE_CODE) Fls_CompareWithTargetBuff
(
  boolean LblLastRead
);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#endif /* #if (FLS_COMPARE_API == STD_ON) */

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_MainRead" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_MainRead(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_PerformBlankCheckForReadOp" */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_PerformBlankCheckForReadOp
                             (const uint32 LulStartAddr, const uint16 Luscount);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_PerformReadCheckECC" */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_PerformReadCheckECC
(
  uint32 LulSrcAddr,
  uint32 LulDestAddr
);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ProcessRead" */
FUNC(MemIf_JobResultType, FLS_PRIVATE_CODE) Fls_ProcessRead(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#if (FLS_READIMMEDIATE_API == STD_ON)

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_MainReadImm" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_MainReadImm(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ProcessReadImm" */
FUNC(MemIf_JobResultType, FLS_PRIVATE_CODE) Fls_ProcessReadImm(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ReadMisAlignHandler" */
extern FUNC(Fls_LengthType, FLS_PRIVATE_CODE) Fls_ReadMisAlignHandler
(const Fls_AddressType LulSourceAddress, const Fls_AddressType LulTargetAddress,
 Fls_LengthType LulLength);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#endif /* #if (FLS_READIMMEDIATE_API == STD_ON) */

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_GetMaxReadBytes" */
FUNC(uint32, FLS_PRIVATE_CODE) Fls_GetMaxReadBytes(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ReportECCErrorToCbk" */
FUNC(void, FLS_PRIVATE_CODE) Fls_ReportECCErrorToCbk
(
  Fls_FcuStatusType LenStatus,
  boolean LblSECError
);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_CopyToTargetBuff" */
FUNC(MemIf_JobResultType, FLS_PRIVATE_CODE) Fls_CopyToTargetBuff
(boolean LblLastRead, const uint32 LulMaxReadBytes);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_InitiateBlankCheckJob" */
extern FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InitiateBlankCheckJob(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_MainBlankCheck" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_MainBlankCheck(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ProcessCancel" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_ProcessCancel(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#if (FLS_FHVE_REGS == SUPPORTED)

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_SetFHVE" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_SetFHVE(boolean value);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
#endif /* END of #if (FLS_FHVE_REGS == SUPPORTED) */

#if (FLS_JOB_NOTIF_CONFIG == STD_ON)

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_CallJobNotification" */
FUNC(void, FLS_PRIVATE_CODE) Fls_CallJobNotification(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#endif /* #if (FLS_JOB_NOTIF_CONFIG == STD_ON) */
/*FLS_INTERNAL_H_001: FLS_ESDD_UD_116 */
#if (FLS_INTERRUPT_MODE == STD_ON)

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_SetResetIntReq" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_SetIntReq(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_RestoreIntReq" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_RestoreIntReq(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ClearIntReq" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_ClearIntReq(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_GetIntReq" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_GetIntReq(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_DisableFaciEndInt" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_DisableFaciEndInt(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_EnableFaciEndInt" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_EnableFaciEndInt(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#if (FLS_SET_MODE_API == STD_ON)
#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_DmaIsr" */
FUNC(void, FLS_FAST_CODE) Fls_DmaIsr(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
#endif /* (FLS_SET_MODE_API == STD_ON) */

#endif /* #if (FLS_INTERRUPT_MODE == STD_ON) */

#if (FLS_SUSPEND_API == STD_ON)

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ProcessSuspend" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_ProcessSuspend(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_BackupJobData" */
FUNC(void, FLS_PRIVATE_CODE) Fls_BackupJobData(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#endif /* #if (FLS_SUSPEND_API == STD_ON) */

#if (FLS_RESUME_API == STD_ON)

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ProcessResume" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_ProcessResume(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_RestoreJobData" */
FUNC(void, FLS_PRIVATE_CODE) Fls_RestoreJobData(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#endif /* #if (FLS_RESUME_API == STD_ON) */

#if (FLS_TIMEOUT_MONITORING == STD_ON)

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_TimeOutCheckAndProcessing" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_TimeOutCheckAndProcessing(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#endif /* #if (FLS_TIMEOUT_MONITORING == STD_ON) */

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ProcessJobResult" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_ProcessJobResult
(
  MemIf_JobResultType LenResult
);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#if ((FLS_RESUME_API == STD_ON) || (FLS_SUSPEND_API == STD_ON))

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ClearBackUpData" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_ClearBackUpData(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#endif /* #if ((FLS_RESUME_API == STD_ON) || (FLS_SUSPEND_API == STD_ON)) */

#if (FLS_DEV_ERROR_DETECT == STD_ON)

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_DetErrorCheck" */
extern FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_DetErrorCheck
(
  const uint8 LucServiceId
);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#endif /* #if (FLS_DEV_ERROR_DETECT == STD_ON) */

#if (FLS_SUSPEND_API == STD_ON)
#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_SuspendPreCheck" */
extern FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_SuspendPreCheck
(
  const Fls_CommandType LenRequestedCmd
);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
#endif /* End of #if (FLS_SUSPEND_API == STD_ON) */

#if ((FLS_SET_MODE_API == STD_ON) &&\
     (FLS_DMA_INSTANCES != FLS_DMA_ZERO))
#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_DmaInit" */
FUNC(void, FLS_PRIVATE_CODE) Fls_DmaInit(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
#endif /* (FLS_SET_MODE_API == STD_ON) &&\
     (FLS_DMA_INSTANCES != FLS_DMA_ZERO) */

#endif  /* FLS_INTERNAL_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
