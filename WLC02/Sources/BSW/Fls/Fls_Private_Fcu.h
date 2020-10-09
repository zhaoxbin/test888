/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Private_Fcu.h                                           */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2016 - 2017 Renesas Electronics Corporation                   */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains API Declarations of Flash Control Unit specific         */
/* functions                                                                  */
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
 * V1.0.0:  13-Jun-2016  : #ARDAABD-454
 *                         1. Initial Version
 *
 * V1.1.0:  28-Sep-2016  :  #ARDAABD-843
 *                          1. Removed support for
 *                             FLS_AR_HIGHER_VERSION / FLS_AR_LOWER_VERSION
 *
 * V2.0.0:  31-Oct-2016 : #ARDAABD-650
 *                        1. Removed Fls_FcuSuspendCheck which is renamed to
 *                           Fls_SuspendPreCheck and moved to Fls_Internal.h
 *
 * V2.1.0:  11_Nov-2016 : #ARDAABD-732 - added Fls_DmaInit function declaration
 *
 * V2.1.1:  15_Nov-2016 : #ARDAABD-893 - function's Fls_FcuPerformBlankCheck
 *                                       Luscount parameter changed to uint32
 *
 * v2.2.0:  18-Jan-2017  : #ARDAABD-923
 *                         1. Added FLS_ECC_INITCHK_SUPPORT macro
 *
 * V2.2.1:  19-Jan-2017  : #ARDAABD-459 - added memory start/stop of memory
 *                           section for Fls_DmaInit function.
 *
 * V2.2.2:  27-Jan-2017  : #ARDAABD-454
 *                         1. Fixing file's name and header.
 *                         2. Grouping FW COPY supported functions in same
 *                            preprocessor macro define.
 *
 * V2.3.0:  31-Jan-2017 : #ARDAABD-454
 *                        1. Fls_DmaInit moved in Fls_Internal.
 *
 * V2.4.0:  31-Jan-2017  :  #ARDAABD-571
 *                          1. Addded MemMap_Fls vs MemMap.h inclusion based on
 *                             AR revision.
 *                          2. Changes after review.
 *
 * V2.1.2:  13-Mar-2017  :  #ARDAABD-829
 *                          1.  MISRA fixes.
 * V2.1.3:  20-Jul-2017  :  #ARDAABD-1139 - Fls_FcuDataCopy return value has
 *                             been changed to uint8.
 *                          #ARDAABD-1246 - Removed Firmware copy support.
 *                          #ARDAABD-1325 - added declaration of
 *                          Fls_FcuReturnFromCmdLock private function.
 * V2.1.4:  24-Aug-2017  :  #ARDAABD-2151 - Corrected QAC/MISRA Warning.
 *
 */
/******************************************************************************/
#ifndef FLS_PRIVATE_FCU_H
#define FLS_PRIVATE_FCU_H

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
#define FLS_PRIVATE_FCU_AR_RELEASE_MAJOR_VERSION \
                                        FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_PRIVATE_FCU_AR_RELEASE_MINOR_VERSION \
                                        FLS_AR_RELEASE_MINOR_VERSION
#define FLS_PRIVATE_FCU_AR_RELEASE_REVISION_VERSION \
                                        FLS_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FLS_PRIVATE_FCU_SW_MAJOR_VERSION            FLS_SW_MAJOR_VERSION
#define FLS_PRIVATE_FCU_SW_MINOR_VERSION            FLS_SW_MINOR_VERSION

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#if (STD_ON == FLS_ECC_INITCHK_SUPPORT)
/* Implements: FLS014, SWS_Fls_00014, Jira-ARDAABD-923*/
#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_PreFcuInitCheck". */
extern FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_PreFcuInitCheck(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
#endif /* #if (STD_ON == FLS_ECC_INITCHK_SUPPORT) */

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuErasePreCheck" */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuErasePreCheck(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuWritePreCheck" */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuWritePreCheck(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuCheckJobStatus" */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuCheckJobStatus(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuResetErrorBits" */
extern FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_FcuResetErrorBits(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuBlankCheckStatus" */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuBlankCheckResult(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuPerformBlankCheck" */
extern FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuPerformBlankCheck
(
  const uint32 LulStartAddr,
  const uint32 Luscount
);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuCheckBCJobStatus" */
extern FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuCheckBCJobStatus(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE


#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuCheckSequencerStatus" */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuCheckSequencerStatus(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE


#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuInit" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_FcuInit(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuSwitchMode" */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuSwitchMode
(
  VAR(const uint16, FLS_APPL_DATA) LusMode
);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuPrepareEnvironment" */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuPrepareEnvironment(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuForcedStop" */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuForcedStop(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuClearStatus" */
FUNC(void, FLS_PRIVATE_CODE) Fls_FcuClearStatus(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuGetDFSize" */
FUNC(uint32, FLS_PRIVATE_CODE) Fls_FcuGetDFSize(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuGetFWParam" */
FUNC(uint32, FLS_PRIVATE_CODE) Fls_FcuGetFWParam
(
  const uint32 LulAddress
);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuSetFrequency" */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuSetFrequency(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuDataCopy" */
FUNC(uint8, FLS_PRIVATE_CODE) Fls_FcuDataCopy
(
  const uint32 LulSrcAddr,
  const uint32 LulBufferAddr
);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_FcuOffsetDataCopy" */
FUNC(void, FLS_PRIVATE_CODE) Fls_FcuOffsetDataCopy
(
  uint32 LulSrcAddr,
  uint32 LulBufferAddr,
  const uint8 LucOffset
);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE
/* Declaration of internal function "Fls_FcuReturnFromCmdLock" */
extern FUNC(void, FLS_PRIVATE_CODE) Fls_FcuReturnFromCmdLock(void);
#define FLS_STOP_SEC_PRIVATE_CODE
#include FLS_MEMMAP_FILE

#endif  /* FLS_PRIVATE_FCU_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
