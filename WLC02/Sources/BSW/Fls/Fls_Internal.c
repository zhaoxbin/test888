/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Internal.c                                              */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015 - 2018 Renesas Electronics Corporation                   */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains Internal functions implementation of Flash              */
/* Wrapper Component.                                                         */
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
 * V1.0.0:  08-Oct-2015    : Initial Version
 *
 * V1.1.0:  04-Dec-2015    : As a part of F1K 4.00.01 release following changes
 *                          are made:
 *                           1. Added the inclusion of Fls_Hardware.h and
 *                              SchM_Fls.h.
 *                           2. Added functions Fls_PreFcuInitCheck,
 *                              Fls_InitiateEraseJob, Fls_InitiateWriteJob,
 *                              Fls_FcuWritePreCheck, Fls_InitiateReadJob,
 *                              Fls_CompleteReadJob, Fls_FcuSwitchBFlash,
 *                              Fls_InitiateBlankCheckJob, Fls_ProcessJobResult,
 *                              Fls_ClearIntReq, Fls_SetIntReq,
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
 *                              Fls_FcuResetErrorBits as per JIRA Ticket
 *                              ARDAAGA-69
 *                           3. Removed functions Fls_VerifyECC,
 *                              Fls_ProcessErase, Fls_VerifyAfterWrite,
 *                              Fls_VerifyAfterErase, Fls_ProcessWrite.
 *                           4. Added justification for Msg(4:4397),Msg(4:3138)
 *                              Msg(4:1505)
 *
 * V1.1.1:  24-Jun-2016 : #ARDAABD-454
 *                         1. Included Fls_Private.h as this in now exporting
 *                            FACI / FCU related internal driver functions.
 *                         2. Removed functions: Fls_PreFcuInitCheck,
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
 *                            As they are moved to Fls_Private.c file
 *
 *                           Add changes in order for Fls_Read to read
 *                           FlsMaxReadNormallMode (or FlsMaxReadFastMode)
 *                           in a single mainfunction call
 *
 * V1.1.2:  05-Jul-2016 : Code adaptions regarding save/restore/clear RFxxx
 *                           bit in ICxxx register (ARDAABD-422)
 *
 * V1.2.2:  28-Sep-2016 : #ARDAABD-843
 *                        1. Removed support for
 *                           FLS_AR_HIGHER_VERSION / FLS_AR_LOWER_VERSION
 *
 * V2.0.0:  31-Oct-2016 : #ARDAABD-650
 *                        1. Added Fls_SuspendPreCheck
 *                        2. Fixed Fls_InitiateBlankCheckJob review findings
 *                        #ARDAABD-667
 *                        1. generating Fls_GulTimeOutCounter's value based on
 *                           FLS_INTERRUPT_MODE define.
 *
 * V2.1.0:  11-Nov-2016 : #ARDAABD-732
 *                        1. added Fls_InitiateDmaWriteJob
 *                           Fls_DisableFaciEndInt, Fls_EnableFaciEndInt and
 *                           Fls_DmaIsr functions, which are used in DMA write
 *                           job process.
 *                        2. Fls_MainWrite, Fls_ProcessResume and
 *                           Fls_SuspendPreCheck has been updated in order to
 *                           support DMA write job.
 *                        #ARDAABD-941 - Fls_GblJobSuspendRequest global is set
 *                           to FALSE in Fls_ProcessSuspend function.
 *
 * V2.1.1:  15_Nov-2016 : #ARDAABD-893 - function's Fls_FcuPerformBlankCheck
 *                                       Luscount parameter changed to uint32
 *                        #ARDAABD-754 - linked AR 4.0.3 requirements
 *
 * V2.1.2   6-Dec-2016  : ARDAABD-941 - Fls_GblJobSuspended value check is added
 *                          in Fls_MainErase and Fls_MainWrite functions, if it
 *                          is TRUE, write/erase procedure is not continued.
 *
 * V2.1.3   16-Jan-2017 : ARDAABD-459
 *                        1. Fls_DisableDmaChannel function added.
 *                        2. Changed write verify MASK for DTCT and DCEN
 *                           registers in Fls_InitiateDmaWriteJob
 *                        3. Fls_DisableDmaChannel function call has been added
 *                           in Fls_ProcessJobResult function.
 *                        4. Added clear of DCSTCm register in
 *                           Fls_InitiateDmaWriteJob function.
 *                        5. Inclusion of MemMap.h file has been replaced with
 *                           FLS_MEMMAP_FILE macro in Fls_DmaIsr function.
 *
 * V2.1.4:  27-Jan-2017  : #ARDAABD-454
 *                         1. Fls_Private.h renamed to Fls_Private_Fcu.h
 *
 * V2.1.5:  30-Jan-2017  : #ARDAABD-459
 *                         1. Fls_InitiateDmaWriteJob Dma register checked
 *                            to be 0 after initialization.
 *
 * V2.1.0:  30-Jan-2017  :  #ARDAABD-571
 *                          1. Addded MemMap_Fls vs MemMap.h inclusion based on
 *                             AR revision.
 *                          2. Added Fls_HWCheckConsistency API related data
 *                             mirroring.
 *                          3. Changes after review.
 *                          4. Masked reference values for bit registers not
 *                             stored in HW (reads 0 always).
 *                          5. Repalced magic numbers.
 *
 * V2.2.0:  31-Jan-2017 : #ARDAABD-454
 *                        1. Fls_DmaInit moved in Fls_Internal.
 *
 * V2.2.1:  28-Feb-2017  :  #ARDAABD-571
 *                          1. Fixed acceptance findings.
 *                          2. Verify DTFRRQ after writing to DTFRRQC.
 *                          3. Fixed review findings.
 *                          4. Fls_EnableFaciEndInt, Fls_DisableFaciEndInt,
 *                             Fls_SetIntReq, Fls_ClearIntReq - functions
 *                             are using now RAM_MASK_FLS_ICFLENDNM.
 *
 * V2.2.2:  28-Feb-2017  :  #ARDAABD-1294
 *                          1. DMA's DTC & DSA registers no more Ram mirrored.
 *
 * V2.2.3:  08-Mar-2017  :  #ARDAABD-997
 *                          1. Suspend is stopping now the timeout monitoring.
 *
 * V2.2.4:  26-May-2017  :  #ARDAABD-446
 *                          1.In order to allow reading of FlsMaxReadXMode bytes
 *                          in one main cycle call, the following changes were
 *                          made: Fls_MainRead function has been changed.
 *                          Fls_CompleteReadJob and Fls_InitiateReadJob
 *                          functions has been removed. Added Fls_ProcessRead
 *                          and Fls_PerformBlankCheckForReadOp functions.
 *                          2. Call to Fls_InitiateReadJob and
 *                          Fls_InitiateBlankCheckJob functions has been removed
 *                          from Fls_ProcessResume, since read and blank check
 *                          jobs cannot be suspended.
 *
 * V2.2.5   1-Jun-2017   :  #ARDAABD-446: The following updates are made after
 *                          review No.096"
 *                          1.Removed unused Fls_ReadCopyToTarget function.
 *                          2.LblLastRead, LblSECError, LenJobResult local
 *                          variables from the Fls_ProcessRead functions are
 *                          initialized at their declaration.
 *                          3. Updated Fls_ProcessResume function header.
 * V2.2.6  28-Jun-2017   :  #ARDAABD-2102 - "MemMap.h" has been replaced by
 *                          FLS_MEMMAP_FILE
 * V2.2.7  20-Jul-2017   :  ARDAABD-1170 - Fls_FcuBlankCheckResult return value
 *                          evaluation has been added.
 *                          ARDAABD-1139 - ulDFERSTR register access has been
 *                          changed to ucDFERSTR.
 *                          ARDAABD-1964 - Reset of the ucOffset variable
 *                          has been removed from Fls_ProcessReadImm function.
 *                          ARDAABD-1588 - ICFLENDNM register write macro is
 *                          changed to RH850_SV_MODE.
 * V2.2.8  01-Aug-2017   :  ARDAABD-2196 - FLS_FCU_ERR_INTERNAL check has been
 *                          added in Fls_MainErase and Fls_MainWrite functions.
 * V2.2.9  25-Aug-2017   :  ARDAABD-2151 - Added QAC/MISRA Warnings
 *                          justification. Corrected QAC/MISRA Warning.
 * V2.2.10 14-Sep-2017   :  ARDAABD-2139 - entire Fls_PerformReadCheckECC()
 *                          function has been enclosed in critical section
 *                          protection.
 * V2.2.11 19-Sep-2017   :  ARDAABD-2160 - Iocommon split
 * V2.2.12 25-Sep-2017   :  ARDAABD-2370 - corrected variables naming convention
 *                          ARDAABD-2418 - Register write + dummy read + SYNCP
 *                          has been replaced by RH850_SV_CLEAR_ICR_SYNCP macro.
 * V2.3.0  16-Oct-2017   :  ARDAABD-2552 - Dem_ReportErrorStatus interface has
 *                          been replaced by Det_ReportRuntimeError for AUTOSAR
 *                          version 4.2.2
 * V2.3.1  22-Jan-2018   :  ARDAABD-2917 - Updated functions header with used
 *                          registers and invoked functions.
 * V2.3.2  20-Jun-2018   :  Following changes are made:
 *                          1. As part of merging activity, #ARDAABD-3465
 *                             below changes are made(Ref : ARDAABD-2158):
 *                           a. Replaced the usage of 'IMRn' Registers
 *                              with 'ICxxx' registers to avoid unprotected
 *                              Read/Modify/Write access to 'IMR' registers.
 *                           b. Misra warning Tag for Message Msg(4:0303) has
 *                              been added.
 *                           c. Misra Violation tag for message Msg(2:0832)
 *                              has been corrected.
 *                           d. Inserted a one space character after
 *                              'if' statement.
 *                           e. Copyright information has been updated.
 *                           f. As per ARDAABD-3853, traceability has been
 *                              improved.
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
//#include "Iocommon_Defines.h"

/* Included for macro definitions and API prototypes */
#include "Fls.h"
/* Included for prototypes for internal functions of Flash Wrapper Component  */
#include "Fls_Internal.h"
/* Included prototypes for private functions of Flash Wrapper Component       */
#include "Fls_Private_Fcu.h"
/* Included for Flash Wrapper Component specific types used within the module */
#include "Fls_Types.h"
/* Included for RAM variable declarations */
#include "Fls_Ram.h"
/* Included for Prototype Declarations for FLS callback Notification FUNCTIONS*/
#include "Fls_Cbk.h"

#include "Fls_Hardware.h"
/* Included for the declaration of Det_ReportError, Det_ReportRuntimeError */
#include "Det.h"
#if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
/* Included for declaration of the function Dem_ReportErrorStatus() */
#include "Dem.h"
#endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
/* Included for the macro declaration of supervisor mode(SV) write enabled
    Registers ICxxx */
//#include "rh850_Types.h"
#if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Fls.h"
#endif
/* Included for macro declarations for wv and ram mirror */
#include "Fls_RegWrite.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR release version information */
#define FLS_INTERNAL_C_AR_RELEASE_MAJOR_VERSION \
                                        FLS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLS_INTERNAL_C_AR_RELEASE_MINOR_VERSION \
                                        FLS_AR_RELEASE_MINOR_VERSION_VALUE
#define FLS_INTERNAL_C_AR_RELEASE_REVISION_VERSION \
                                     FLS_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FLS_INTERNAL_C_SW_MAJOR_VERSION    FLS_SW_MAJOR_VERSION_VALUE
#define FLS_INTERNAL_C_SW_MINOR_VERSION    FLS_SW_MINOR_VERSION_VALUE

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (FLS_INTERNAL_AR_RELEASE_MAJOR_VERSION != \
                                       FLS_INTERNAL_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fls_Internal.c : Mismatch in Release Major Version"
#endif
#if (FLS_INTERNAL_AR_RELEASE_MINOR_VERSION != \
                                       FLS_INTERNAL_C_AR_RELEASE_MINOR_VERSION)
  #error "Fls_Internal.c : Mismatch in Release Minor Version"
#endif
#if (FLS_INTERNAL_AR_RELEASE_REVISION_VERSION != \
                                    FLS_INTERNAL_C_AR_RELEASE_REVISION_VERSION)
  #error "Fls_Internal.c : Mismatch in Release Revision Version"
#endif


#if (FLS_INTERNAL_SW_MAJOR_VERSION != FLS_INTERNAL_C_SW_MAJOR_VERSION)
  #error "Fls_Internal.c : Mismatch in Software Major Version"
#endif
#if (FLS_INTERNAL_SW_MINOR_VERSION != FLS_INTERNAL_C_SW_MINOR_VERSION)
  #error "Fls_Internal.c : Mismatch in Software Minor Version"
#endif
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      MISRA C Rule Violations                               **
*******************************************************************************/

/******************************************************************************/

/* 1. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0303) [I] Cast between a pointer to volatile object     */
/*                 and an integral type.                                      */
/* Rule          : MISRA-C:2004 Rule 3.1 and 11.3                             */
/* Justification : This macro is used to write or read values from hardware   */
/*                 addresses.                                                 */
/* Verification  : However, this part of the code is verified manually and it */
/*                 is not having any impact.                                  */
/* Reference     : Look for START Msg(4:0303)-1 and                           */
/*                 END Msg(4:0303)-1 tags in the code.                        */

/******************************************************************************/

/* 2. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0306) [I] Cast between a pointer to object and an       */
/*                 integral type.                                             */
/* Rule          : MISRA-C:2004 Rule 3.1 and 11.3                             */
/* Justification : The input addresses specified by the pointers are converted*/
/*                 to addresses for storing into the registers and for        */
/*                 reading purposes.                                          */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:0306)-2 and                           */
/*                 END Msg(4:0306)-2 tags in the code.                        */

/******************************************************************************/

/* 3. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0488) Performing Pointer arithmetic.                    */
/* Rule          : MISRA-C:2004 Rule 17.4                                     */
/* Justification : This addresses pointed by the pointers needs to be         */
/*                 incremented after each cycle.                              */
/* Verification  : However, part of code is verified manually and it is not   */
/*                 having any impact.                                         */
/* Reference     : Look for START Msg(4:0488)-3 and                           */
/*                 END Msg(4:0488)-3 tags in the code.                        */

/******************************************************************************/

/* 4. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0489) The integer value 1 is being added or subtracted  */
/*                 from a pointer.                                            */
/* Rule          : MISRA-C:2004 Rule 17.4                                     */
/* Justification : This is to get the next address value by incrementing      */
/*                 the pointers.                                              */
/* Verification  : However, part of code is verified manually and it is not   */
/*                 having any impact.                                         */
/* Reference     : Look for START Msg(4:0489)-4 and                           */
/*                 END Msg(4:0489)-4 tags in the code.                        */

/******************************************************************************/

/* 5. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0310) Casting to different object pointer type.         */
/* Rule          : MISRA-C:2004 Rule 11.4                                     */
/* Justification : This is to get the value to pointer.                       */
/* Verification  : However, this part of the code is verified  manually and   */
/*                 it is not having any impact.                               */
/* Reference     : Look for START Msg(4:0310)-5 and                           */
/*                 END Msg(4:0310)-5 tags in the code.                        */

/******************************************************************************/

/* 6. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0311) Dangerous pointer cast results in loss of const   */
/*                 qualification.                                             */
/* Rule          : MISRA-C:2004 Rule 11.5                                     */
/* Justification : In this instance, it is verified that the address stored in*/
/*                 the global pointer is not a constant value address.        */
/* Verification  : However, this part of the code is verified  manually and   */
/*                 it is not having any impact.                               */
/* Reference     : Look for START Msg(4:0311)-6 and                           */
/*                 END Msg(4:0311)-6 tags in the code.                        */

/******************************************************************************/

/* 7. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:4397) An expression which is the result of a ~ or <<    */
/*                 operation has not been cast to its essential type.         */
/* Rule          : MISRA-C:2004 Rule 10.5                                     */
/* Justification : The expression has no reliance on the effects of integral  */
/*                 promotion.                                                 */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:4397)-7 and                           */
/*                 END Msg(4:4397)-7 tags in the code.                        */

/******************************************************************************/
/**                         QAC Warning                                      **/
/******************************************************************************/

/* 1. QAC Warning:                                                            */
/* Message       : (2:3227) The value of this function parameter is never     */
/*                 modified. It could be declared with the 'const' type       */
/*                 Qualifier.                                                 */
/* Justification : The function parameters of AUTOSAR APIs cannot be modified */
/*                 to be made as constant.                                    */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:3227)-1 and END Msg(2:3227)-1 tags in */
/*                 the code.                                                  */
/******************************************************************************/
/* 2. QAC Warning:                                                            */
/* Message       : (2:3416) Logical operation performed on expression with    */
/*                 possible side effects.                                     */
/* Justification : Logical operation accesses volatile object which is a      */
/*                 register access or global variable. All register addresses */
/*                 are generated with volatile qualifier. There is no impact  */
/*                 on the functionality due to this conditional check for mode*/
/*                 change.                                                    */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:3416)-2 and END Msg(2:3416)-2         */
/*                 tags in the code.                                          */
/******************************************************************************/
/* 3. QAC Warning:                                                            */
/*Message       : (2:2814) Possible: Dereference of NULL pointer.             */
/* Justification : The Pointers generated using Post Build configurations may */
/*                 not be NULL.                                               */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:2814)-3 and END Msg(2:2814)-3 tags in */
/*                 the code.                                                  */
/******************************************************************************/
/* 4. QAC Warning:                                                            */
/* Message       : (2:3204) This variable is only set once and so it could    */
/*                 be declared with the 'const' qualifier.                    */
/* Justification : These variables cannot be declared with 'const' qualifier  */
/*                 since these variables are subjected to change in each      */
/*                 cycle of Fls_MainFunction call.                            */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any safety impact.                              */
/* Reference     : Look for START Msg(2:3204)-4 and                           */
/*                 END Msg(2:3204)-4 tags in the code.                        */
/******************************************************************************/
/* 5. QAC Warning:                                                            */
/* Message       : (2:3892) The result of this cast is implicitly converted to*/
/*                 another type.                                              */
/* Justification : This is used for write verification of a particular        */
/*                 register so even if it is unsigned or signed type it has no*/
/*                 impact.                                                    */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any safety impact.                              */
/* Reference     : Look for START Msg(2:3892)-5 and                           */
/*                 END Msg(2:3892)-5 tags in the code.                        */
/******************************************************************************/
/* 6. QAC Warning:                                                            */
/* Message       : (2:2016) This 'switch' statement 'default' clause is empty.*/
/* Justification : No action is required for default statements. Hence it is  */
/*                 left empty.                                                */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:2016)-6 and                           */
/*                 END Msg(2:2016)-6 tags in the code.                        */
/******************************************************************************/
/* 7. QAC Warning:                                                            */
/* Message       : (3:3305) Pointer cast to stricter alignment.               */
/* Justification : In this instance, it is verified that the address stored in*/
/*                 the global pointer is not a constant value address.        */
/* Verification  : However, this part of the code is verified  manually and   */
/*                 it is not having any impact.                               */
/* Reference     : Look for START Msg(3:3305)-7 and                           */
/*                 END Msg(3:3305)-7 tags in the code.                        */
/******************************************************************************/
/* 8. QAC Warning:                                                            */
/* Message       : (2:0380) Number of macro definitions exceeds 4095          */
/*                          - program does not conform strictly to ISO:C99.   */
/* Justification : In order to ensure portability, it is advisable to avoid   */
/*                 writing code that assumes a level of compiler capability   */
/*                 which may not always be supported.                         */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:0380)-8 and                           */
/*                 END Msg(2:0380)-8 tags in the code.                        */
/******************************************************************************/
/* 9.  MISRA C RULE VIOLATION:                                                */
/* Message       : (2:0832) Macro substitution in #include preprocessing      */
/*                 directive.                                                 */
/* Rule          : No MISRA-C:2004 Rule                                       */
/* Justification : Required to optimize MemMap inclusion because of ASR403    */
/*                 and ASR422 support.                                        */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:0832)-9 and                           */
/*                 END Msg(2:0832)-9 tags in the code.                        */
/******************************************************************************/
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name             : Fls_InitiateEraseJob
**
** Service ID                : NA
**
** Description               : This function initiates the Erase Job for
**                             configured Data Flash Blocks.
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Std_ReturnType
**
** Return parameter          : LenReturn
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.ulJobStartAddress,
**                             Fls_GstVar.enDFStatus, Fls_GblFlashEnable,
**                             Fls_GblTimeOutMonitor
**
** Function(s) invoked       : Fls_FcuSwitchMode,Fls_FcuErasePreCheck,
**                             FLS_FCU_DF_ISSUE_BYTE_CMD,Fls_SetFHVE
**
** Registers Used            : FSADDR,FEADDR,FHVE3,FHVE15,FSTATR,FASTAT,FENTRYR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0380)-8 */
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_160, FLS_ESDD_UD_001, FLS_ESDD_UD_016 */
/* Implements: FLS250, FLS145, FLS218 */
/* Implements: SWS_Fls_00250, SWS_Fls_00145, SWS_Fls_00218 */
/* Implements: AR_PN0072_FR_0005  */
FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InitiateEraseJob(void)
{
  /* Variable to return Job Initiation status */
  Std_ReturnType LucReturn = E_NOT_OK;
  /* Initialize the local variable to hold the FCU Status */
  Fls_FcuStatusType LenStatus;
  /* Local variables to hold current start and end addresses */
  uint32 LulCurrentEndAddr;
  uint32 LulCurrentStartAddr;


  return(LucReturn);
} /* End of function Fls_InitiateEraseJob */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_MainErase
**
** Service ID                : NA
**
** Description               : This function is called from Fls_MainFunction,
**                             when the command is Erase Operation.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.enCommand,
**                             Fls_GblVerifyCompletedJob,
**                             Fls_GstVar.ulJobStartAddress,
**                             Fls_GstVar.ulJobEndAddress
**
** Function(s) invoked       : Fls_FcuCheckJobStatus,Fls_InitiateBlankCheckJob,
**                             Fls_ProcessJobResult,Dem_ReportErrorStatus,
**                             Det_ReportRuntimeError,Fls_InitiateEraseJob
**
** Registers Used            : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,
**                             DCSTCm,DCENm,DTCTm,ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_001, FLS_ESDD_UD_128, FLS_ESDD_UD_267  */
/* Implements: FLS037, FLS104, FLS022, FLS313 */
/* Implements: SWS_Fls_00037, SWS_Fls_00104, SWS_Fls_00022, SWS_Fls_00313 */
FUNC(void, FLS_PRIVATE_CODE) Fls_MainErase(void)
{

  /* Local variable to hold the return from Fls_InitiateBlankCheckJob
     Function */
  Std_ReturnType LucReturnValue = E_OK;
  /* Variable to hold the Data Flash Status */
  Fls_FcuStatusType LenStatus;
  /* Get the Data Flash Status */
  LenStatus = Fls_FcuCheckJobStatus();

  if (FLS_FCU_OK == LenStatus)
  {
    #if (FLS_SUSPEND_API == STD_ON)
    /* QAC Warning: START Msg(2:3416)-2 */
    if (FLS_FALSE == Fls_GblJobSuspended)
    /* END Msg(2:3416)-2 */
    {
    #endif /* FLS_SUSPEND_API == STD_ON */
      if (Fls_GstVar.ulJobStartAddress < Fls_GstVar.ulJobEndAddress)
      {
        /* For subsequent blocks of erase, invoke Fls_InitiateEraseJob */
        LucReturnValue = Fls_InitiateEraseJob();
      }
      else
      {
        #if (FLS_DEV_ERROR_DETECT == STD_ON)
        /* Set the command to blank check */
        Fls_GstVar.enCommand = FLS_COMMAND_BLANKCHECK;
        Fls_GblVerifyCompletedJob = FLS_TRUE;
        /* Implements: Fls022, SWS_Fls_00022, AR_PN0072_FR_0003 */
        /* Initiate Blank Check */
        LucReturnValue = Fls_InitiateBlankCheckJob();
        #else
        Fls_ProcessJobResult(MEMIF_JOB_OK);
        #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
      }
    #if (FLS_SUSPEND_API == STD_ON)
    }
    else
    {
      /* do nothing - job is suspended*/
    }
    #endif
  }
  else
  {
    /* No Action required */
  }

  /* If Initiate Erase or Blank Check is failed due to Switch Mode Failure,
   DEM/DET shall be reported from here. Else if Erase Fails due to Erasure Error
   DEM/DET shall be reported from Fls_ProcessJobResult function */
  if (E_NOT_OK == LucReturnValue)
  {
    #if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
    /* Report DEM as Erase Job Failed */
    /* Implements: FLS_ESDD_UD_256, FLS315, SWS_Fls_00315   */
    Dem_ReportErrorStatus(FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
    #else
    /* Report DET as Erase Job Failed */
    (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                              FLS_ERASE_SID, FLS_E_ERASE_FAILED);
    #endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
    /* Process Job Failure */
    Fls_ProcessJobResult(MEMIF_JOB_FAILED);
  }
  else if ((FLS_FCU_ERR_ERASE == LenStatus) ||
     (FLS_FCU_ERR_INTERNAL == LenStatus))
  {
    /* Process Job Failure */
    Fls_ProcessJobResult(MEMIF_JOB_FAILED);
  }
  else
  {
    /* No action Required */
  }

} /* End of function Fls_MainErase */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_InitiateWriteJob
**
** Service ID                : NA
**
** Description               : This function initiates the write Job for
**                             each word.
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Std_ReturnType
**
** Return parameter          : LenReturn
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.ulJobStartAddress,
**                             Fls_GblTimeOutMonitor,Fls_GstVar.pBufferAddress,
**                             Fls_GstVar.enDFStatus
**
** Function(s) invoked       : Fls_FcuSwitchMode,Fls_FcuWritePreCheck,
**                             FLS_FCU_DF_ISSUE_BYTE_CMD,FLS_DF_READ8,
**                             FLS_FCU_DF_ISSUE_WORD_CMD,Fls_SetFHVE
**
** Registers Used            : FSADDR,FEADDR,FHVE3,FHVE15,FSTATR,FENTRYR,FASTAT
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_189, FLS_ESDD_UD_001 */
/* Implements: FLS146, FLS223 */
/* Implements: SWS_Fls_00146, SWS_Fls_00223*/
/* Implements: AR_PN0072_FR_0006, AR_PN0072_FR_0044*/
FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InitiateWriteJob(void)
{
  /* Variable to return Job Initiation status */
  Std_ReturnType LucReturn = E_NOT_OK;
  /* Initialize the local variable to hold the FCU Status */
  Fls_FcuStatusType LenStatus;
  /* Local Variable to hold the Data */
  uint16 LusData;
  uint32 LulWriteCount;
  uint32 LulReadAddress;
  uint32 LulCurrentStartAddr;




  return(LucReturn);
} /* End of function Fls_InitiateWriteJob */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

#if ((FLS_SET_MODE_API == STD_ON) &&\
    (FLS_DMA_INSTANCES != FLS_DMA_ZERO))
/*******************************************************************************
** Function Name             : Fls_InitiateDmaWriteJob
**
** Service ID                : NA
**
** Description               : This function initiates DMA transfer for Write
**                             Job.
**
** Sync/Async                : Asynchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Std_ReturnType
**
** Return parameter          : LenReturn
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GblFlashEnable,Fls_GpDmaUnitConfig
**
** Function(s) invoked       : Fls_SetFHVE,Fls_FcuSwitchMode,
**                             Fls_FcuWritePreCheck, Fls_DisableFaciEndInt,
**                             FLS_FCU_DF_ISSUE_BYTE_CMD,
**                             FLS_FCU_DF_ISSUE_WORD_CMD
**
** Registers Used            : DTCTm,DSAm,DTCm,DCENm,DCSTCm,FSADDR,FEADDR,
**                             FHVE3,FHVE15,FSTATR,FENTRYR,FASTAT,
**                             ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_150, FLS_ESDD_UD_001 */
/* Implements: FLS251 */
/* Implements: SWS_Fls_00251 */
/* Implements: AR_PN0072_FR_0056 */
FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InitiateDmaWriteJob(void)
{
  /* Variable to return Job Initiation status */
  Std_ReturnType LucReturn = E_NOT_OK;
  /* Initialize the local variable to hold the FCU Status */
  Fls_FcuStatusType LenStatus;
  #if (FLS_INTERRUPT_MODE == STD_ON)
  P2VAR(volatile uint16, AUTOMATIC, FLS_CONFIG_DATA) LpIntpCntrlReg;
  #endif /* FLS_INTERRUPT_MODE == STD_ON */
  P2CONST(Fls_DmaUnitConfig, AUTOMATIC, FLS_CONFIG_DATA) LpDmaConfig;
  /* Local Variable to hold the Data */
  uint32 LulCurrentStartAddr;
  uint32 LulRegValue;
  /* Local variable to store the index to DMA registers address */
  uint8 LucDmaRegIndex;
  /* Local pointer which holds the base address of DMA channel  */
  P2VAR(volatile DmaReg, AUTOMATIC, FLS_CONFIG_DATA) LpDmaRegisters;

  /* Implements: FLS_ESDD_UD_120 */
  #if (FLS_FHVE_REGS == SUPPORTED)
  if (FLS_FALSE == Fls_GblFlashEnable)
  {
    /* Disable the flash memory software protection */
    Fls_SetFHVE(FLS_FLASH_PROTECTION_OFF);
    Fls_GblFlashEnable = FLS_TRUE;
  }
  else
  {
    /* No action required */
  }
  #endif /* End of #if (FLS_FHVE_REGS == SUPPORTED) */
  /* Check if FCU is ready to initiate write Job */
  LenStatus = Fls_FcuWritePreCheck();

  if (FLS_FCU_OK == LenStatus)
  {
    /* Switching to P/E Mode */
    LenStatus = Fls_FcuSwitchMode(FLS_FCU_MODE_PE);

    if (FLS_FCU_OK == LenStatus)
    {
      #if (FLS_INTERRUPT_MODE == STD_ON)
      /* Mask the ICFLENDNM  */
      Fls_DisableFaciEndInt();
      #endif /* FLS_INTERRUPT_MODE == STD_ON */
      LpDmaConfig = Fls_GpDmaUnitConfig;
      LulCurrentStartAddr = Fls_GstVar.ulJobStartAddress -
                                                           FLS_DF_BASE_ADDRESS;
      /* QAC Warning: START Msg(2:2814)-3 */
      /* Get index to DMA channel base address */
      LucDmaRegIndex = LpDmaConfig->ucDmaRegIndex;
      /* Store the base address to DMA channel  */
      LpDmaRegisters = Fls_GaaDmaReg_BaseAddress[LucDmaRegIndex];
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Disable relevant interrupts to protect this critical section */
      FLS_ENTER_CRITICAL_SECTION(FLS_REGISTER_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */

      /* Load the transfer control register */
      FLS_WRITE_REG_AND_MIRROR(
                                &LpDmaRegisters->ulDTCT,
                                FLS_DMA_DTCT_REG_VALUE,
                                &Fls_GaaRamMirror[RAM_IDX_DTCT]
                              )
      FLS_CHECK_WRITE_VERIFY_RUNTIME(
                                      &LpDmaRegisters->ulDTCT,
                                      FLS_DMA_DTCT_REG_VALUE,
                                      RAM_MASK_DTCT,
                                      FLS_WRITE_SID
                                    )

      /* load the source address register for DMA transfer */
      /* MISRA Violation: START Msg(4:0306)-2 */
      FLS_WRITE_REG_ONLY(
                          &LpDmaRegisters->ulDSA,
                          (uint32)Fls_GstVar.pBufferAddress
                        )
      FLS_CHECK_WRITE_VERIFY_RUNTIME(&LpDmaRegisters->ulDSA,
                              (uint32)Fls_GstVar.pBufferAddress,
                              RAM_MASK_NO_MASK,
                              FLS_WRITE_SID)
      /* MISRA Violation: END Msg(4:0306)-2 */
      /* QAC Warning: START Msg(2:3892)-5 */
      /* Load the transfer count(16bit) value and reload count value */
      FLS_WRITE_REG_ONLY(
                         &LpDmaRegisters->ulDTC,
                         (uint32)(FLS_DMA_DTC_RELOAD_CNT |
                         (uint32)(Fls_GstVar.ulRequestedLength >> FLS_ONE))
                        )
      FLS_CHECK_WRITE_VERIFY_RUNTIME(&LpDmaRegisters->ulDTC,
                 (uint32)(FLS_DMA_DTC_RELOAD_CNT |
                 (uint32)(Fls_GstVar.ulRequestedLength >> FLS_ONE)),
                 RAM_MASK_NO_MASK,
                 FLS_WRITE_SID)
      /* END Msg(2:3892)-5 */
      #if (FLS_INTERRUPT_MODE == STD_ON)
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Implements: FLS_ESDD_UD_254 */
      /* Clear the pending interrupts with dummy read and SYNCP */
      RH850_SV_CLEAR_ICR_SYNCP(16, (LpDmaConfig->pDmaIntCntlReg),
                                                (FLS_RESET_INT_REQ));
      #else
      /* Clear the pending interrupts (no dummy read and SYNCP) */
      RH850_SV_MODE_ICR_AND(16, (LpDmaConfig->pDmaIntCntlReg),
                                       (FLS_RESET_INT_REQ));
      #endif /* (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
      /* Enable the DMA interrupt control register */
      LpIntpCntrlReg = LpDmaConfig->pDmaIntCntlReg;
      RH850_SV_MODE_ICR_AND(16, (LpIntpCntrlReg),(FLS_RESET_INT_MK));
      #endif /* (FLS_INTERRUPT_MODE == STD_ON) */
      /* Clear DMA channel Status register Register */
      LulRegValue = LpDmaRegisters->ulDCSTC | FLS_DMA_DCST_CLEAR;
      FLS_WRITE_REG_ONLY(&LpDmaRegisters->ulDCSTC,
                                      LulRegValue)
      FLS_CHECK_WRITE_VERIFY_INIT(&LpDmaRegisters->ulDCST,
                                      FLS_FCU_ZERO, FLS_DMA_DCST_CLEAR,
                                      FLS_INIT_SID)
      /* DMA transfer enable  */
      FLS_WRITE_REG_AND_MIRROR(&LpDmaRegisters->ulDCEN,
                                      FLS_DMA_DCEN_ENABLE,
                                      &Fls_GaaRamMirror[RAM_IDX_DCEN])
      FLS_CHECK_WRITE_VERIFY_RUNTIME(&LpDmaRegisters->ulDCEN,
                                      FLS_DMA_DCEN_ENABLE, RAM_MASK_DCEN,
                                      FLS_WRITE_SID)
      /* Setting Write Start and End Address */
      FLS_WRITE_REG_AND_MIRROR(
                                &FLS_GpFACIReg_BaseAddress->ulFSADDR,
                                LulCurrentStartAddr,
                                &Fls_GaaRamMirror[RAM_IDX_FSADDR]
                              )
      FLS_CHECK_WRITE_VERIFY_RUNTIME
        (
          &FLS_GpFACIReg_BaseAddress->ulFSADDR,
          (LulCurrentStartAddr & RAM_MASK_FSADDR),
          RAM_MASK_FSADDR,
          FLS_WRITE_SID
        )
      FLS_WRITE_REG_AND_MIRROR
      (
        &FLS_GpFACIReg_BaseAddress->ulFEADDR,
        (LulCurrentStartAddr + Fls_GstVar.ulRequestedLength) - FLS_FCU_ONE,
        &Fls_GaaRamMirror[RAM_IDX_FEADDR]
      )
      FLS_CHECK_WRITE_VERIFY_RUNTIME
      (
        &FLS_GpFACIReg_BaseAddress->ulFEADDR,
        (
          (
            (LulCurrentStartAddr + Fls_GstVar.ulRequestedLength) -
            FLS_FCU_ONE
          )&
          RAM_MASK_FEADDR
        ),
        RAM_MASK_FEADDR,
        FLS_WRITE_SID
      )
      /* END Msg(2:2814)-3 */
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enable relevant interrupts to exit this critical section */
      FLS_EXIT_CRITICAL_SECTION(FLS_REGISTER_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
      /* Issuing DMA WRITE Command */
      /* MISRA Violation: START Msg(4:0303)-1 */
      FLS_FCU_DF_ISSUE_BYTE_CMD(FLS_FACI_CMD_DMA_WRITE);
      /* Issuing "N", N = data size / 2 */
      FLS_FCU_DF_ISSUE_WORD_CMD((uint16)(Fls_GstVar.ulRequestedLength >>
                                                             (uint32)FLS_ONE));
      /* MISRA Violation: END Msg(4:0303)-1 */

      /* Set E_OK since Job Initiation Success */
      LucReturn = E_OK;
    }
    else
    {
      /*No Action required */
    }
  }
  else
  {
    /*No Action required */
  }

  /* Save the FCU status */
  Fls_GstVar.enDFStatus = LenStatus;

  return(LucReturn);
} /* End of function Fls_InitiateWriteJob */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if ((FLS_SET_MODE_API == STD_ON) &&\
                      (FLS_DMA_INSTANCES != FLS_DMA_ZERO)) */

#if ((FLS_SET_MODE_API == STD_ON) &&\
    (FLS_DMA_INSTANCES != FLS_DMA_ZERO))
/*******************************************************************************
** Function Name             : Fls_DisableDmaChannel
**
** Service ID                : NA
**
** Description               : This function disable / cancel transfer of
**                             current the DMA channel.
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : NA
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : DCENm, DTCTm
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_158, FLS_ESDD_UD_001 */
FUNC(void, FLS_PRIVATE_CODE) Fls_DisableDmaChannel(void)
{
  uint32 LulRegValue;
  /* Local variable to store the index to DMA registers address */
  uint8 LucDmaRegIndex;
  /* Local pointer which holds the base address of DMA channel  */
  P2VAR(volatile DmaReg, AUTOMATIC, FLS_CONFIG_DATA) LpDmaRegisters;
  /* Local pointer to DMA channel configuration */
  P2CONST(Fls_DmaUnitConfig, AUTOMATIC, FLS_CONFIG_DATA) LpDmaConfig;

  LpDmaConfig = Fls_GpDmaUnitConfig;
  /* Get index to DMA channel base address */
  /* QAC Warning: START Msg(2:2814)-3 */
  LucDmaRegIndex = LpDmaConfig->ucDmaRegIndex;
  /* Store the base address to DMA channel  */
  LpDmaRegisters = Fls_GaaDmaReg_BaseAddress[LucDmaRegIndex];
  LulRegValue = (LpDmaRegisters->ulDTCT & FLS_DMA_MLE_CLEAR);
  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Disable relevant interrupts to protect this critical section */
  FLS_ENTER_CRITICAL_SECTION(FLS_REGISTER_PROTECTION);
  #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)*/
  /* Disable DMA continuous transfer */
  FLS_WRITE_REG_AND_MIRROR(&LpDmaRegisters->ulDTCT,
                           LulRegValue, &Fls_GaaRamMirror[RAM_IDX_DTCT])
  FLS_CHECK_WRITE_VERIFY_RUNTIME(&LpDmaRegisters->ulDTCT,
                                 LulRegValue, RAM_MASK_DTCT, FLS_CANCEL_SID)
  /* DMA transfer disable  */
  FLS_WRITE_REG_AND_MIRROR(&LpDmaRegisters->ulDCEN,
                          FLS_DMA_DCEN_DISABLE, &Fls_GaaRamMirror[RAM_IDX_DCEN])
  FLS_CHECK_WRITE_VERIFY_RUNTIME(&LpDmaRegisters->ulDCEN,
                                 FLS_DMA_DCEN_DISABLE, RAM_MASK_DCEN,
                                 FLS_CANCEL_SID)
  #if (FLS_INTERRUPT_MODE == STD_ON)
  /* Clear pending interrupt request */
  RH850_SV_MODE_ICR_AND(16, (LpDmaConfig->pDmaIntCntlReg),
                            (FLS_RESET_INT_REQ));
  /* Disable the DMA interrupt control register */
  /* MISRA Violation: START Msg(4:4397)-7 */
  /* Implements: FLS_ESDD_UD_103 */
  RH850_SV_MODE_ICR_OR(16, LpDmaConfig->pDmaIntCntlReg,
                         (FLS_SET_INT_MK));
  /* MISRA Violation: END Msg(4:4397)-7 */
  /* END Msg(2:2814)-3 */
  #endif /* FLS_INTERRUPT_MODE == STD_ON */
  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enable relevant interrupts to exit this critical section */
  FLS_EXIT_CRITICAL_SECTION(FLS_REGISTER_PROTECTION);
  #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)*/
}

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /*((FLS_SET_MODE_API == STD_ON) && (FLS_DMA_INSTANCES != FLS_DMA_ZERO))*/

/*******************************************************************************
** Function Name             : Fls_MainWrite
**
** Service ID                : NA
**
** Description               : This function is called from Fls_MainFunction,
**                             when the command is Write Operation.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.enCommand,
**                             Fls_GstVar.pBufferAddress,
**                             Fls_GstVar.ulJobStartAddress,
**                             Fls_GstVar.ulJobEndAddress,
**                             Fls_GstVar.ulCurrentLength
**
** Function(s) invoked       : Fls_FcuCheckJobStatus,Fls_InitiateWriteJob,
**                             Fls_ProcessJobResult,Dem_ReportErrorStatus,
**                             Det_ReportError,Det_ReportRuntimeError
**
** Registers Used            : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,
**                             DCSTCm,DCENm,DTCTm,DCSTm,ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_130 */
/* Implements: FLS251, FLS105, FLS056 */
/* Implements: SWS_Fls_00251, SWS_Fls_00105, SWS_Fls_00056 */
FUNC(void, FLS_PRIVATE_CODE) Fls_MainWrite(void)
{
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  boolean LblWriteVerify = FLS_TRUE;
  uint32 LulCurrentLength = (uint32)FLS_ZERO;
  #endif /* End of (FLS_DEV_ERROR_DETECT == STD_ON) */
  /* Variable to return Job Initiation status */
  Std_ReturnType LucReturn;
  /* Variable to hold the Data Flash Status */
  Fls_FcuStatusType LenStatus;
  /* Get the DF Status */
  LenStatus = Fls_FcuCheckJobStatus();

  if (FLS_FCU_OK == LenStatus)
  {
    #if ((FLS_SET_MODE_API == STD_ON) &&\
         (FLS_DMA_INSTANCES != FLS_DMA_ZERO))
    if (MEMIF_MODE_FAST == Fls_GenCurrentMode)
    {
      Fls_ProcessJobResult(MEMIF_JOB_OK);
    }
    else
    #endif
    #if (FLS_SUSPEND_API == STD_ON)
    /* QAC Warning: START Msg(2:3416)-2 */
    if ((FLS_FALSE == Fls_GblJobSuspended) ||
        (FLS_COMMAND_WRITE != Fls_GstBackUpVar.enCommand))
    /* END Msg(2:3416)-2 */
    {
    #endif /* FLS_SUSPEND_API == STD_ON */
      if (Fls_GstVar.ulJobStartAddress < Fls_GstVar.ulJobEndAddress)
      {
        /* For issuing write command for remaining blocks */
        LucReturn = Fls_InitiateWriteJob();
        if (E_NOT_OK == LucReturn)
        {
          #if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
          /* Report DEM as Write Job Failed */
          /* Implements: FLS316, SWS_Fls_00316 */
          Dem_ReportErrorStatus(FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
          #else
          /* Report DET as Write Job Failed */
          (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                      FLS_WRITE_SID, FLS_E_WRITE_FAILED);
          #endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
          /* Process Job Failure */
          Fls_ProcessJobResult(MEMIF_JOB_FAILED);
        }
        else
        {
          /*No Action required */
        }
      }
      else
      {
        #if (FLS_DEV_ERROR_DETECT == STD_ON)
        #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
        /* Disable relevant interrupts to protect this critical section */
        FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
        #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
        /* Restore the Start address of Write Job for verification */
        Fls_GstVar.ulJobStartAddress = Fls_GstVar.ulJobStartAddress -
                                         Fls_GstVar.ulCurrentLength;
        /* MISRA Violation: START Msg(4:0488)-3 */
        Fls_GstVar.pBufferAddress = Fls_GstVar.pBufferAddress -
                                    Fls_GstVar.ulCurrentLength;
        /* END Msg(4:0488)-3 */
        #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
        /* Enable relevant interrupts to exit this critical section */
        FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
        #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */

        while (LulCurrentLength < Fls_GstVar.ulCurrentLength)
        {
          /* Check if the target memory matches with the application buffer */
          /* MISRA Violation: START Msg(4:0306)-2 */
          if (*(Fls_GstVar.pBufferAddress) !=
                                     *((uint8 *)Fls_GstVar.ulJobStartAddress))
          /* MISRA Violation: END Msg(4:0306)-2 */
          {
            LulCurrentLength = Fls_GstVar.ulCurrentLength;
            /* Set LblWriteVerify as FLS_FALSE if comparison failed */
            LblWriteVerify = FLS_FALSE;
          }
          else /* Target memory value matches with the application buffer */
          {
            #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
            /* Disable relevant interrupts to protect this critical section */
            FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
            #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
            /* Increment the pointers to point to the next locations */
            /* MISRA Violation: START Msg(4:0489)-4 */
            Fls_GstVar.pBufferAddress++;
            /* END Msg(4:0489)-4 */
            Fls_GstVar.ulJobStartAddress++;
            #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
            /* Enable relevant interrupts to exit this critical section */
            FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
            #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
            /*
             * Increment the number of bytes and the total number of bytes
             * processing in this cycle.
             */
            LulCurrentLength++;
          }
        }
        if (FLS_FALSE == LblWriteVerify)
        {
          Fls_ProcessJobResult(MEMIF_JOB_FAILED);
          /* Report error to DET */
          (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                               FLS_MAINFUNCTION_SID, FLS_E_VERIFY_WRITE_FAILED);
        }
        else
        #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
        {
          Fls_ProcessJobResult(MEMIF_JOB_OK);
        }

      }
    #if (FLS_SUSPEND_API == STD_ON)
    }
    else
    {
      /* do nothing */
    }
    #endif /* FLS_SUSPEND_API == STD_ON */
  }
  else if ((FLS_FCU_ERR_WRITE == LenStatus) ||
           (FLS_FCU_ERR_INTERNAL == LenStatus))
  {
    /* Process Job Failure */
    Fls_ProcessJobResult(MEMIF_JOB_FAILED);
  }
  else
  {
    /* No Action required */
  }

}/* End of function Fls_MainWrite */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_MainRead
**
** Service ID                : NA
**
** Description               : This function is called from Fls_MainFunction,
**                             when the command is Read Operation.
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : Non Re-entrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.enCommand, Fls_GenState,
**                             Fls_GenJobResult
**
** Function(s) invoked       : Fls_ProcessRead,Fls_CallJobNotification,
**                             Fls_RestoreIntReq
**
** Registers Used            : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,
**                             DFERRINT,FBCSTAT,DFERSTC,DFERSTR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS106, FLS337, FLS236 */
/* Implements: SWS_Fls_00106, SWS_Fls_00337, SWS_Fls_00236, FLS_ESDD_UD_132 */
FUNC(void, FLS_PRIVATE_CODE) Fls_MainRead(void)
{
  /* Local variable to hold the return from ProcessRead Function */
  MemIf_JobResultType LenInternalJobResult;
  /* Call Internal Read Process Function */
  LenInternalJobResult = Fls_ProcessRead();
  /* Check the internal job result */
  if (MEMIF_JOB_PENDING != LenInternalJobResult)
  {
    /* Set the command to none */
    Fls_GstVar.enCommand = FLS_COMMAND_NONE;
    /* Set the driver state to idle */
    Fls_GenState = MEMIF_IDLE;
    /* Set the job result to internal job status */
    Fls_GenJobResult = LenInternalJobResult;
    #if (FLS_INTERRUPT_MODE == STD_ON)
    Fls_RestoreIntReq();
    #endif /* #if (FLS_INTERRUPT_MODE == STD_ON) */
    /* Implements: FLS_ESDD_UD_034 */
    #if (FLS_JOB_NOTIF_CONFIG == STD_ON)
    Fls_CallJobNotification();
    #endif /* #if (FLS_JOB_NOTIF_CONFIG == STD_ON) */
  }
  else
  {
    /* No Action required */
  }
}/* End of function Fls_MainRead */



#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name            : Fls_ProcessRead
**
** Service ID               : NA
**
** Description              : This function processes the read command for
**                            data flash
**
** Sync/Async               : NA
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : MemIf_JobResultType
**
** Return parameter         : LenJobResult
**
** Preconditions            : None
**
** Global Variable(s) Used  : Fls_GVar.ulCurrentLength(RW),
**                            Fls_GVar.ulRequestedLength(RW),
**                            Fls_GVar.ucOffset(R),
**                            Fls_GVar.ulReadAddress(RW),
**                            Fls_GVar.pTempBufferAddress(RW),
**                            Fls_GVar.ulSrcDestAddress(R),
**                            Fls_GstVar.enDFStatus(W),
**                            Fls_GVar.enReadType(W)
**
** Function(s) invoked      : Fls_PerformBlankCheckForReadOp,
**                            Fls_PerformReadCheckECC,Fls_CopyToTargetBuff
**                            Fls_GetMaxReadBytes,Dem_ReportErrorStatus,
**                            Fls_ReportECCErrorToCbk, Det_ReportRuntimeError
**
** Registers Used           : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,
**                            DFERRINT,FBCSTAT,DFERSTC,DFERSTR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_161 */
/* Implements: FLS236, FLS337 */
/* Implements: SWS_Fls_00236, SWS_Fls_00337 */
/* Implements: EAAR_PN0072_FR_0004, EAAR_PN0072_FR_0007 */
FUNC(MemIf_JobResultType, FLS_PRIVATE_CODE) Fls_ProcessRead(void)
{
  /* Initialize the local variable to hold the FCU Status */
  Fls_FcuStatusType LenStatus;
  MemIf_JobResultType LenJobResult = MEMIF_JOB_OK;
  /* Local variable to hold the SEC error occurrence status */
  boolean LblSECError = FLS_FALSE;
  boolean LblLastRead = FLS_FALSE;
  /* Local variable to hold the loop count */
  uint32 LulLoopCount;
  /* Local variable to hold the maximum read bytes */
  uint32 LulMaxReadBytes;
  uint32 LulReadAddress;
  uint32 LulReadPhAddress;
  uint32 LulBufferAddress;
  /* Get the maximum read bytes based on the Mode */
  LulMaxReadBytes = Fls_GetMaxReadBytes();

  /* Check whether the length exceeds the maximum number of read bytes */
  if (Fls_GstVar.ulCurrentLength > LulMaxReadBytes)
  {
    /* Set the variable length to read Maximum number of bytes */
    LulLoopCount = (LulMaxReadBytes / (uint32)FLS_FOUR);
    /* Calculate Remaining bytes of the length */
    Fls_GstVar.ulCurrentLength =
                            Fls_GstVar.ulCurrentLength - LulMaxReadBytes;
    Fls_GstVar.ulRequestedLength = Fls_GstVar.ulRequestedLength -
                                  (LulMaxReadBytes - Fls_GstVar.ucOffset);
  }
  else
  {
    /* Calculate the length for remaining bytes */
    LulLoopCount = (Fls_GstVar.ulCurrentLength / (uint32)FLS_FOUR);
    /* Set the Last Read variable to True */
    LblLastRead = FLS_TRUE;
  }
  do
  {

    LulReadAddress = Fls_GstVar.ulReadAddress - FLS_DF_BASE_ADDRESS;

    LenStatus = Fls_PerformBlankCheckForReadOp((uint32)(LulReadAddress),
                                                  (uint16)(FLS_FCU_WRITE_SIZE));
    /* Implements: FLS_ESDD_UD_087 */
    if (FLS_FCU_OK == LenStatus)
    {
      /* MISRA Violation: START Msg(4:0310)-5 */
      /* MISRA Violation: START Msg(4:0311)-6 */
      /* QAC Warning: START Msg(3:3305)-7 */
      /* Writing the fixed pattern data to application buffer */
      *((volatile uint32 *) Fls_GstVar.pTempBufferAddress) = FLS_ERASED_VALUE;
      /* END Msg(3:3305)-7 */
      /* END Msg(4:0311)-6 */
      /* END Msg(4:0310)-5 */
    }
    else if (FLS_FCU_ERR_BLANKCHECK == LenStatus)
    {
      /* MISRA Violation: START Msg(4:0306)-2 */
      LulBufferAddress = (uint32)Fls_GstVar.pTempBufferAddress;
      /* MISRA Violation: END Msg(4:0306)-2 */
      LulReadPhAddress = Fls_GstVar.ulReadAddress;
      LenStatus = Fls_PerformReadCheckECC (LulReadPhAddress, LulBufferAddress);
      /* Check if the single bit error occurred from Data Flash read */
      if (FLS_FCU_ERR_ECC_SED == LenStatus)
      {
        /* Global variable to hold the ECC error occurrence address */
        Fls_GstVar.ulSrcDestAddress = Fls_GstVar.ulReadAddress;
       /* Set the local variable of SEC error occurrence status to true */
        LblSECError = FLS_TRUE;
      }
      else
      {
        /* No action required */
      }
    }
    else
    {
      /* No action required */
    }
    /* MISRA Violation: START Msg(4:0488)-3 */
    Fls_GstVar.pTempBufferAddress = Fls_GstVar.pTempBufferAddress +
                                                    FLS_FCU_WRITE_SIZE;
    /* END Msg(4:0488)-3 */
    LulLoopCount--;
    Fls_GstVar.ulReadAddress = Fls_GstVar.ulReadAddress +
                                                    FLS_FCU_WRITE_SIZE;
  } while ((LulLoopCount > (uint32)FLS_ZERO) &&
          ((FLS_FCU_OK == LenStatus) || (FLS_FCU_ERR_ECC_SED == LenStatus)));

  /* Read Process Completed*/
  /* Check the Request Status and set Job status to return */
  if ((FLS_FCU_OK == LenStatus) || (FLS_FCU_ERR_ECC_SED == LenStatus))
  {
    /* Set Read Type to MISALIGNED since data is to be copied from Temporary
       Buffer to Target Buffer */
    Fls_GstVar.enReadType = FLS_MISALIGNED_READ;
    /* Copy Data from Temporary Buffer to Target Buffer */
    LenJobResult = Fls_CopyToTargetBuff(LblLastRead, LulMaxReadBytes);
  }
  /* Report Job Failed if DED has occurred */
  else if (FLS_FCU_ERR_ECC_DED == LenStatus)
  {
    /* Implements: FLS_ESDD_UD_130, FLS_ESDD_UD_257, FLS317, SWS_Fls_00317 */
    #if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
    /* Report error to DEM that read job failed due to double bit error */
    Dem_ReportErrorStatus(FLS_E_READ_FAILED_DED, DEM_EVENT_STATUS_FAILED);
    #else
    /* Report error to DET that read job failed due to double bit error */
    (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                              FLS_READ_SID, FLS_E_READ_FAILED_DED);
    #endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
    /* Set Job Status as failed */
    LenJobResult = MEMIF_JOB_FAILED;
  }
  else if (FLS_FCU_ERR_INTERNAL == LenStatus)
  {

    #if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
    /* Report error to DEM that read job failed due to internal hardware
    error during blank check operation */
    Dem_ReportErrorStatus(FLS_E_READ_FAILED, DEM_EVENT_STATUS_FAILED);
    #else
    /* Report error to DET that read job failed due to internal hardware
       error during blank check operation */
    (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                              FLS_READ_SID, FLS_E_READ_FAILED);
    #endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
    /* Set Job Status as failed */
    LenJobResult = MEMIF_JOB_FAILED;
  }
  else
  {
    /* No action Required */
  }
  /* Check for SEC/DED error and report */
  Fls_ReportECCErrorToCbk(LenStatus, LblSECError);

  Fls_GstVar.enDFStatus = LenStatus;

  return(LenJobResult);
} /* End of function Fls_ProcessRead */


#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name            : Fls_PerformBlankCheckForReadOp
**
** Service ID               : NA
**
** Description              : This function performs the blank check operation
**                            when the command is FLS_COMMAND_READ.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LulStartAddr, Luscount
**
** InOut Parameters         : None
**
** Output Parameters        : Fls_FcuStatusType
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : Fls_GpConfigPtr(R),Fls_GblFlashEnable(RW),
**                            Fls_GstVar.enGenCommand(W),Fls_GenState(W),
**                            Fls_GenJobResult(W)
**
** Function(s) invoked      : Fls_FcuSwitchMode,FLS_FCU_DF_ISSUE_BYTE_CMD,
**                            Fls_ProcessCancel,Fls_CallJobNotification,
**                            Det_ReportError,Fls_SetFHVE,
**                            Fls_FcuBlankCheckResult
**
** Registers Used           : FSADDR,FEADDR,FSTATR,FHVE3,FHVE15,FENTRYR,FBCSTAT
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS361,FLS346,FLS359,FLS360,FLS362,FLS261,FLS163,FLS161,FLS164 */
/* Implements: SWS_Fls_00261 */
/* Implements: EAAR_PN0072_FR_0051,EAAR_PN0072_FR_0022,EAAR_PN0072_FR_0059 */
/* Implements: EAAR_PN0034_FSR_0002,EAAR_PN0034_FSR_0001 */
/* Implements: EAAR_PN0034_FSR_0003,EAAR_PN0034_FSR_0004 */
/* Implements: EAAR_PN0072_EAFR_0059,EAAR_PN0072_FR_0023 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_PerformBlankCheckForReadOp
(const uint32 LulStartAddr, const uint16 Luscount)
{
  Fls_FcuStatusType LenStatus;
  Fls_FcuStatusType LenBCStatus;
  /* QAC Warning: START Msg(2:3204)-4 */
  uint32 LulEndAddr;
  /* END Msg(2:3204)-4 */

  return(LenStatus);

} /* End of function Fls_PerformBlankCheckForReadOp */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_PerformReadCheckECC
**
** Service ID                : NA
**
** Description               : This function reads data from the Data Flash.
**                             Doing so, it disables the ECC error interrupts to
**                             avoid interrupt generation on accepted ECC errors
**                             when reading e.g. blank or partly written Flash
**                             words.Instead,the error and fail address is
**                             returned to the calling function.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : LulDestAddr
**
** InOut Parameters          : LulSrcAddr
**
** Output Parameters         : Fls_FcuStatusType
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : FLS_DF_READ32,FLS_DF_READ32,FLS_DF_WRITE32
**
** Registers Used            : DFERSTC,DFERRINT,DFERSTR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_133 */
/* Implements: AR_PN0072_FSR_0029 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_PerformReadCheckECC
/* QAC Warning: START Msg(2:3227)-1*/
(uint32 LulSrcAddr, uint32 LulDestAddr)
/* END Msg(2:3227)-1*/
{
  /* Local variable to hold the read data */
  uint32 LulData;
  uint8  LucRegValue;
  uint8 LucErrorRegValue;
  /*Local variable to hold the FCU status*/
  Fls_FcuStatusType LenStatus = FLS_FCU_OK;

  return(LenStatus);

}/* End of function Fls_PerformReadCheckECC */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

#if (FLS_COMPARE_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_MainCompare
**
** Service ID                : NA
**
** Description               : This function is called from Fls_MainFunction,
**                             when the command is Compare Operation.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.enCommand, Fls_GenJobResult,
**                             and Fls_GenState
**
** Function(s) invoked       : Fls_ProcessCompare,Fls_CallJobNotification
**
** Registers Used            : DFERRINT,DFERSTC,DFERSTR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_134 */
/* Implements: FLS257 */
/* Implements: SWS_Fls_00257 */
FUNC(void, FLS_PRIVATE_CODE) Fls_MainCompare(void)
{
  /* Local variable to hold the return from ProcessCompare Function */
  MemIf_JobResultType LenInternalJobResult;
  /* Call Internal Compare Process Function */
  LenInternalJobResult = Fls_ProcessCompare();
  if (MEMIF_JOB_PENDING != LenInternalJobResult)
  {
    /* Set the command to none */
    Fls_GstVar.enCommand = FLS_COMMAND_NONE;
    /* Set the job result to internal job result */
    Fls_GenJobResult = LenInternalJobResult;
    /* Set the driver state to idle */
    Fls_GenState = MEMIF_IDLE;
    /* Implements: FLS_ESDD_UD_034 */
    #if (FLS_JOB_NOTIF_CONFIG == STD_ON)
    Fls_CallJobNotification();
    #endif /* End of #if (FLS_JOB_NOTIF_CONFIG == STD_ON) */
  }
  else
  {
      /* No Action required */
  }

}/* End of function Fls_MainCompare */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_CompareWithTargetBuff
**
** Service ID                : NA
**
** Description               : This function is used to compare data between
**                             Temporary Buffer and Target Buffer.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : LblLastRead
**
** InOut Parameters          : None
**
** Output Parameters         : MemIf_JobResultType
**
** Return parameter          : LucReturnValue
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.ucOffset,
**                             Fls_GstVar.pTempBufferAddress,
**                             ulCurrentLength,Fls_GstVar.pBufferAddress,
**                             Fls_GstVar.ulRequestedLength
**
** Function(s) invoked       : Fls_GetMaxReadBytes, Dem_ReportErrorStatus,
**                             Det_ReportRuntimeError
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_135 */
/* Implements: FLS257, FLS200 */
/* Implements: SWS_Fls_00257, SWS_Fls_00200 */
/* QAC Warning: START Msg(2:3227)-1*/
FUNC(MemIf_JobResultType, FLS_PRIVATE_CODE) Fls_CompareWithTargetBuff
(boolean LblLastRead)
/* END Msg(2:3227)-1*/

{
  /* Local variable to store the processed bytes count */
  uint32 LulBytesProcessed;
  /* Local variable to hold the loop count */
  uint32 LulLoopCount = (uint32)FLS_ZERO;
  /* Local variable to hold the maximum read bytes */
  uint32 LulMaxReadBytes;
  /* Local variable to return the Job Status */
  MemIf_JobResultType LenReturnValue;
  /* Local variable to hold the compare operation status */
  boolean LblCompareStatus = E_OK;
  if (FLS_TRUE != LblLastRead)
  {
    /* Get the Maximum Read bytes */
    LulMaxReadBytes = Fls_GetMaxReadBytes();
    /* Set the bytes to be processed to maximum read bytes per cycle */
    LulBytesProcessed = (LulMaxReadBytes - Fls_GstVar.ucOffset);
    /* MISRA Violation: START Msg(4:0488)-3 */
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Reset the buffer pointer with number of bytes it processed */
    Fls_GstVar.pTempBufferAddress = (Fls_GstVar.pTempBufferAddress -
                                                       LulBytesProcessed);
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* END Msg(4:0488)-3 */
  }
  else
  {
    /* Set the bytes to be processed to remaining read bytes */
    LulBytesProcessed = Fls_GstVar.ulCurrentLength;
    /* MISRA Violation: START Msg(4:0488)-3 */
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Reset the buffer pointer with number of bytes it processed */
    Fls_GstVar.pTempBufferAddress = (Fls_GstVar.pTempBufferAddress +
                                 Fls_GstVar.ucOffset) - LulBytesProcessed;
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* END Msg(4:0488)-3 */
    LulBytesProcessed = Fls_GstVar.ulRequestedLength;
  }
  /* Loop until the number of bytes read in one cycle */
  while (LulLoopCount < LulBytesProcessed)
  {
    /* Check if read data and buffer data are same */
    if (*(Fls_GstVar.pBufferAddress) !=
                                *(Fls_GstVar.pTempBufferAddress))
    {
      /* Set the loop count to maximum number of bytes processed */
      LulLoopCount = LulBytesProcessed;
      LblCompareStatus = E_NOT_OK;
    }
    else
    {
      /* No action required */
    }
    /* Increment the loop count, buffer address and temp buffer address */
    LulLoopCount++;
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* MISRA Violation: START Msg(4:0489)-4 */
    Fls_GstVar.pBufferAddress++;
    Fls_GstVar.pTempBufferAddress++;
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* END Msg(4:0489)-4 */
  } /* End of while */
  if (E_OK == LblCompareStatus)
  {
    if (FLS_TRUE != LblLastRead)
    {
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Disable relevant interrupts to protect this critical section */
      FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
      /* MISRA Violation: START Msg(4:0488)-3 */
      /* Reset the buffer pointer by number of bytes it processes */
      Fls_GstVar.pTempBufferAddress = Fls_GstVar.pTempBufferAddress -
                            (Fls_GstVar.ucOffset + LulBytesProcessed);
      /* END Msg(4:0488)-3 */
      /* Set the global variable offset to zero */
      Fls_GstVar.ucOffset = FLS_ZERO;
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enable relevant interrupts to exit this critical section */
      FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
      LenReturnValue = MEMIF_JOB_PENDING;
    }
    else /* Compare done successfully  */
    {
      /* Set the job result */
      LenReturnValue = MEMIF_JOB_OK;
    }
  }
  else /* compare mismatches */
  {
    #if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
    /* Report error to DEM that compare job has failed */
    /* Implements: FLS_ESDD_UD_255 */
    Dem_ReportErrorStatus(FLS_E_COMPARE_FAILED, DEM_EVENT_STATUS_FAILED);
    #else
    /* Report error to DET that compare job has failed */
    (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                              FLS_COMPARE_SID, FLS_E_COMPARE_FAILED);
    #endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
    /* Set the job result to Block Inconsistent */
    LenReturnValue = MEMIF_BLOCK_INCONSISTENT;
  }

  return(LenReturnValue);
}/* End of function Fls_CompareWithTargetBuff */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_ProcessCompare
**
** Service ID                : NA
**
** Description               : This function processes the compare command for
**                             data flash.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : MemIf_JobResultType
**
** Return parameter          : LenJobResult
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.ulCurrentLength,
**                             Fls_GstVar.ulReadAddress,
**                             Fls_GstVar.ucOffset,
**                             Fls_GstVar.ulSrcDestAddress,
**                             Fls_GstVar.pTempBufferAddress,
**                             Fls_GstVar.ulRequestedLength,
**
**
** Function(s) invoked       : Fls_GetMaxReadBytes,Fls_PerformReadCheckECC,
**                             Fls_CompareWithTargetBuff,Dem_ReportErrorStatus,
**                             Fls_ReportECCErrorToCbk, Det_ReportRuntimeError
**
** Registers Used            : DFERRINT,DFERSTC,DFERSTR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_081 */
/* Implements: FLS257 */
/* Implements: SWS_Fls_00257 */
/* Implements: AR_PN0072_FSR_0029 */
FUNC(MemIf_JobResultType, FLS_PRIVATE_CODE) Fls_ProcessCompare(void)
{
  /* Local variable to hold the status of the FCU status */
  Fls_FcuStatusType LenStatus;
  /* Local variable to denote if this is last read cycle */
  boolean LblLastRead = FLS_FALSE;
  /* Local variable to hold the loop count */
  uint32 LulLoopCount;
  /* Local variable to hold the maximum read bytes */
  uint32 LulMaxReadBytes;
  /* Local variable to hold the read address */
  uint32 LulReadAddress;
  /* Local variable to hold the temporary buffer address */
  uint32 LulBufferAddress;
  /* Local variable to return the Job Status */
  MemIf_JobResultType LenJobResult;
  /* Local variable to hold the SEC error occurrence status */
  boolean LblSECError = FLS_FALSE;
  /* Get the maximum read bytes based on the Mode */
  LulMaxReadBytes = Fls_GetMaxReadBytes();

  /* Check whether the length exceeds the maximum number of read bytes */
  if (Fls_GstVar.ulCurrentLength > LulMaxReadBytes)
  {
    /* Set the variable length to read Maximum number of bytes */
    LulLoopCount = (LulMaxReadBytes / (uint32)FLS_FOUR);
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Calculate Remaining bytes of the length */
    Fls_GstVar.ulCurrentLength =
                            Fls_GstVar.ulCurrentLength - LulMaxReadBytes;

    Fls_GstVar.ulRequestedLength = Fls_GstVar.ulRequestedLength -
                                   (LulMaxReadBytes - Fls_GstVar.ucOffset);
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
  }
  else
  {
    /* Calculate the length for remaining bytes */
    LulLoopCount = (Fls_GstVar.ulCurrentLength / (uint32)FLS_FOUR);

    /* Set the Last Read variable to False */
    LblLastRead = FLS_TRUE;
  }
  do
  {
    LulReadAddress = (uint32)Fls_GstVar.ulReadAddress;
    /* MISRA Violation: START Msg(4:0306)-2 */
    LulBufferAddress = (uint32)Fls_GstVar.pTempBufferAddress;
    /* MISRA Violation: END Msg(4:0306)-2 */
    LenStatus = Fls_PerformReadCheckECC(LulReadAddress, LulBufferAddress);
     /* Check if the single bit error occurred from Data Flash read */
     if (FLS_FCU_ERR_ECC_SED == LenStatus)
     {
       /* Global variable to hold the ECC error occurrence address */
       Fls_GstVar.ulSrcDestAddress = Fls_GstVar.ulReadAddress;

       /* Set the local variable of SEC error occurrence status to true */
       LblSECError = FLS_TRUE;
     }
     else
     {
       /* No action required */
     }
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* MISRA Violation: START Msg(4:0488)-3 */
    Fls_GstVar.pTempBufferAddress = Fls_GstVar.pTempBufferAddress +
                                                            FLS_FCU_WRITE_SIZE;
    /* END Msg(4:0488)-3 */

    Fls_GstVar.ulReadAddress = Fls_GstVar.ulReadAddress +
                                                            FLS_FCU_WRITE_SIZE;
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    LulLoopCount--;
  } while ((LulLoopCount > (uint32)FLS_ZERO) &&
          ((FLS_FCU_OK == LenStatus) || (FLS_FCU_ERR_ECC_SED == LenStatus)));

  /* Check the Request Status and set Job status to return */
  if ((FLS_FCU_OK == LenStatus) || (FLS_FCU_ERR_ECC_SED == LenStatus))
  {
    /* Compare the Data Read with the Target Buffer data */
    LenJobResult = Fls_CompareWithTargetBuff(LblLastRead);
  }
  /* Report Job Failed if DED has occurred */
  else
  {
    #if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
    /* Report error to DEM that read job failed due to double bit error */
    Dem_ReportErrorStatus(FLS_E_READ_FAILED_DED, DEM_EVENT_STATUS_FAILED);
    #else
    /* Report error to DET that read job failed due to double bit error */
    (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
        FLS_COMPARE_SID, FLS_E_READ_FAILED_DED);
    #endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
    /* Set Job Status as failed */
    LenJobResult = MEMIF_JOB_FAILED;
  }

  /* Check for SEC/DED error and report */
  Fls_ReportECCErrorToCbk(LenStatus, LblSECError);
  /* Return the Job status */
  return(LenJobResult);
}/* End of function Fls_ProcessCompare */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if (FLS_COMPARE_API == STD_ON) */

#if (FLS_READIMMEDIATE_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_MainReadImm
**
** Service ID                : NA
**
** Description               : This function is called from Fls_MainFunction,
**                             when the command is ReadImmediate Operation.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.enCommand, Fls_GenJobResult,
**                             and Fls_GenState
**
** Function(s) invoked       : Fls_ProcessReadImm,Fls_CallJobNotification
**
** Registers Used            : DFERRINT,DFERSTC,DFERSTR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_136*/
FUNC(void, FLS_PRIVATE_CODE) Fls_MainReadImm(void)
{
  /* Local variable to hold the return from ProcessReadImm Function */
  MemIf_JobResultType LenInternalJobResult;
  /* Call Internal Read Immediate Process Function */
  LenInternalJobResult = Fls_ProcessReadImm();
  if (MEMIF_JOB_PENDING != LenInternalJobResult)
  {
    /* Set the command to none */
    Fls_GstVar.enCommand = FLS_COMMAND_NONE;
    /* Set the job result to internal job status */
    Fls_GenJobResult = LenInternalJobResult;
    /* Set the driver state to idle */
    Fls_GenState = MEMIF_IDLE;
    #if (FLS_JOB_NOTIF_CONFIG == STD_ON)
    Fls_CallJobNotification();
    #endif /* End of #if (FLS_JOB_NOTIF_CONFIG == STD_ON) */
  }
  else
  {
    /* No Action required */
  }

}/* End of function Fls_MainReadImm */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_ProcessReadImm
**
** Service ID                : NA
**
** Description               : This function processes the read immediate
**                             command for data flash.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : MemIf_JobResultType
**
** Return parameter          : LucReturnValue
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.ulCurrentLength,
**                             Fls_GstVar.ulReadAddress,
**                             Fls_GstVar.enReadType,Fls_GstVar.pBufferAddress
**                             Fls_GstVar.pTempBufferAddress,
**                             Fls_GstVar.ulRequestedLength,
**                             Fls_GstVar.ucOffset,
**                             Fls_GstVar.ulSrcDestAddress
**
** Function(s) invoked       : Fls_GetMaxReadBytes, Fls_FcuDataCopy,
**                             Fls_CopyToTargetBuff, Dem_ReportErrorStatus,
**                             Fls_ReportECCErrorToCbk, Fls_FcuOffsetDataCopy,
**                             Det_ReportRuntimeError
**
** Registers Used            : DFERSTC,DFERSTR,DFERRINT
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/* Implements: AR_PN0072_FR_0041, AR_PN0072_FR_0049 */
/* Implements: FLS_ESDD_UD_126  */
FUNC(MemIf_JobResultType, FLS_PRIVATE_CODE) Fls_ProcessReadImm(void)
{
  /* Local variable to hold the status of the FCU */
  Fls_FcuStatusType LenStatus;
  /* Local variable to hold internal Job Status */
  MemIf_JobResultType LenReturnValue;
  /* Local variable to hold the length */
  uint32 LulDFLength;
  /* Local variable to hold the maximum read bytes */
  uint32 LulMaxReadBytes;
  /* Local variable to hold the read start and end addresses */
  uint32 LulReadStartAddress;
  uint32 LulReadEndAddress;
  uint32 LulBuffAddress;
  /* Local variable to hold the backup of ECC error interrupt value */
  uint8 LucDFERRInt;
  uint8 LucLenOffset = FLS_ZERO;
  /* Local variable to hold the value of Data Flash error status register */
  uint8 LucErrorStatus = FLS_FCU_REGVAL_DFERSTR_NOERR;
  /* Local variable to denote if this is last read cycle */
  boolean LblLastRead = FLS_FALSE;
  /* Local variable to hold the SEC error occurrence status */
  boolean LblSECError = FLS_FALSE;
  /* Get the maximum read bytes based on the Mode */
  LulMaxReadBytes = Fls_GetMaxReadBytes();

  /* Check whether the length exceeds the maximum number of read bytes */
  if (Fls_GstVar.ulCurrentLength > LulMaxReadBytes)
  {
    /* Set the variable length to read Maximum number of bytes */
    LulDFLength = LulMaxReadBytes;
    /* Calculate Remaining bytes of the length */
    Fls_GstVar.ulCurrentLength = Fls_GstVar.ulCurrentLength -
                                                             LulMaxReadBytes;

    if (FLS_MISALIGNED_READ == Fls_GstVar.enReadType)
    {
      Fls_GstVar.ulRequestedLength = Fls_GstVar.ulRequestedLength -
                                   (LulMaxReadBytes - Fls_GstVar.ucOffset);
    }
    else
    {
      /* No Action Required */
    }
  }
  else
  {
    if (FLS_MISALIGNED_READ != Fls_GstVar.enReadType)
    {
      /* QAC Warning: START Msg(2:3892)-5 */
      LucLenOffset = (uint8)Fls_GstVar.ulCurrentLength &
                                            (FLS_PAGE_SIZE - FLS_ONE);
      /* END Msg(2:3892)-5 */
      /* Calculate the length for remaining bytes */
      LulDFLength = Fls_GstVar.ulCurrentLength - LucLenOffset;
    }
    else
    {
      /* Calculate the length for remaining bytes */
      LulDFLength = Fls_GstVar.ulCurrentLength;
    }
    LblLastRead = FLS_TRUE;
  }
  /* Get the read start and end addresses */
  LulReadStartAddress = Fls_GstVar.ulReadAddress;
  LulReadEndAddress = (LulReadStartAddress + LulDFLength) - (uint32)FLS_ONE;
  /* Clear ECC errors */
  /* QAC Warning: START Msg(2:2814)-3 */
  FLS_WRITE_REG_ONLY(
                      &FLS_GpECCReg_BaseAddress->ucDFERSTC,
                      FLS_FCU_REGBIT_DFERSTC_ERRCLR
                    )
  FLS_CHECK_WRITE_VERIFY_RUNTIME(
                                  &FLS_GpECCReg_BaseAddress->ucDFERSTR,
                                  FLS_FCU_REGVAL_DFERSTR_NOERR,
                                  RAM_MASK_DFERSTR,
                                  FLS_READ_IMM_SID
                                )
  /* BackUp and Clear ECC Interrupts */
  LucDFERRInt = FLS_GpECCReg_BaseAddress->ucDFERRINT;
  FLS_WRITE_REG_AND_MIRROR(&FLS_GpECCReg_BaseAddress->ucDFERRINT,
                                FLS_FCU_REGVAL_DFERRINT_NOINT,
                                &Fls_GaaRamMirror[RAM_IDX_DFERRINT])
  FLS_CHECK_WRITE_VERIFY_RUNTIME(
                                  &FLS_GpECCReg_BaseAddress->ucDFERRINT,
                                  FLS_FCU_REGVAL_DFERRINT_NOINT,
                                  RAM_MASK_DFERRINT,
                                  FLS_READ_IMM_SID
                                )
  /* END Msg(2:2814)-3 */
  if (FLS_MISALIGNED_READ == Fls_GstVar.enReadType)
  {
    do
    {
      /* MISRA Violation: START Msg(4:0306)-2 */
      LulBuffAddress = (uint32)Fls_GstVar.pTempBufferAddress;
      /* MISRA Violation: END Msg(4:0306)-2 */
      LucErrorStatus = Fls_FcuDataCopy(LulReadStartAddress, LulBuffAddress);
      /* Incrementing the address pointers */
      LulReadStartAddress = LulReadStartAddress + FLS_FCU_WRITE_SIZE;
      /* MISRA Violation: START Msg(4:0488)-3 */
      Fls_GstVar.pTempBufferAddress = Fls_GstVar.pTempBufferAddress +
                                                          FLS_FCU_WRITE_SIZE;
      /* END Msg(4:0488)-3 */
      /* Check for the read address reached the end address */
    } while (LulReadStartAddress <= LulReadEndAddress);

    /* Global variable to hold the ECC error occurrence address */
    Fls_GstVar.ulSrcDestAddress = Fls_GstVar.ulSrcDestAddress -
                                                            FLS_FCU_WRITE_SIZE;
  }
  else
  {
    /* Check for the read address reached the end address */
    while (LulReadStartAddress < LulReadEndAddress)
    {
      /* MISRA Violation: START Msg(4:0306)-2 */
      LulBuffAddress = (uint32)Fls_GstVar.pBufferAddress;
      /* MISRA Violation: END Msg(4:0306)-2 */
      LucErrorStatus = Fls_FcuDataCopy(LulReadStartAddress, LulBuffAddress);
      /* MISRA Violation: START Msg(4:0488)-3 */
      Fls_GstVar.pBufferAddress = Fls_GstVar.pBufferAddress +
                                                           FLS_FCU_WRITE_SIZE;
      /* END Msg(4:0488)-3 */
      LulReadStartAddress = LulReadStartAddress + FLS_FCU_WRITE_SIZE;
    }
    /* MISRA Violation: START Msg(4:0306)-2 */
    /* Copying Offset Data */
    LulBuffAddress = (uint32)Fls_GstVar.pBufferAddress;
    /* END Msg(4:0306)-2 */
    Fls_FcuOffsetDataCopy(LulReadStartAddress, LulBuffAddress, LucLenOffset);
    /* MISRA Violation: START Msg(4:0488)-3 */
    Fls_GstVar.pBufferAddress = Fls_GstVar.pBufferAddress + LucLenOffset;
    /* END Msg(4:0488)-3 */
    LulReadStartAddress = LulReadStartAddress + LucLenOffset;
  }

  /* Get the updated read start address value to the global variable  */
  Fls_GstVar.ulReadAddress = LulReadStartAddress;
  /* Check ECC Status Register for Read Errors and set the status */
  if (FLS_FCU_REGVAL_DFERSTR_NOERR != LucErrorStatus)
  {
    if (FLS_FCU_REGBIT_DFERSTR_DEDF ==
                              (FLS_FCU_REGBIT_DFERSTR_DEDF & LucErrorStatus))
    {
      LenStatus = FLS_FCU_ERR_ECC_DED;
    }
    else
    {
      LenStatus = FLS_FCU_ERR_ECC_SED;
      LblSECError = FLS_TRUE;
    }
  }
  else
  {
    LenStatus = FLS_FCU_OK;
  }
  /* Check the Request Status and set Job status to return */
  if ((FLS_FCU_OK == LenStatus) || (FLS_FCU_ERR_ECC_SED == LenStatus))
  {
    /* Copy Data from Temporary Buffer to Target Buffer */
    LenReturnValue = Fls_CopyToTargetBuff (LblLastRead, LulMaxReadBytes);
  }
  /* Report Job Failed if DED has occurred */
  else
  {
    #if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
    /* Report error to DEM that read job failed due to double bit error */
    Dem_ReportErrorStatus(FLS_E_READ_FAILED_DED, DEM_EVENT_STATUS_FAILED);
    #else
    /* Report error to DET that read job failed due to double bit error */
    (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                            FLS_READ_IMM_SID, FLS_E_READ_FAILED_DED);
    #endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
    /* Set Job Status as failed */
    LenReturnValue = MEMIF_JOB_FAILED;
  }

  /* Check for SEC/DED error and report */
  Fls_ReportECCErrorToCbk(LenStatus, LblSECError);
  /* Restore the Error Interrupt Register value */
  FLS_WRITE_REG_AND_MIRROR(
                            &FLS_GpECCReg_BaseAddress->ucDFERRINT,
                            LucDFERRInt,
                            &Fls_GaaRamMirror[RAM_IDX_DFERRINT]
                          )
  FLS_CHECK_WRITE_VERIFY_RUNTIME(
                                  &FLS_GpECCReg_BaseAddress->ucDFERRINT,
                                  LucDFERRInt,
                                  RAM_MASK_DFERRINT,
                                  FLS_READ_IMM_SID
                                )
  /* Return the Job status */
  return(LenReturnValue);
} /* End of function Fls_ProcessReadImm */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_ReadMisAlignHandler
**
** Service ID                : NA
**
** Description               : This function is used to adjust the Read Source
**                             Address and length when the Source Address,
**                             Target Address or Length values are not aligned.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : SourceAddress,TargetAddress,Length
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : Length
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.enReadType,Fls_GstVar.ucOffset,
**                             Fls_GstVar.ulReadAddress,
**                             Fls_GstVar.pTempBufferAddress,
**                             Fls_GstVar.ulRequestedLength
**
** Function(s) invoked       : None
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_137 */
/* Implements: AR_PN0072_FR_0041, AR_PN0072_FR_0008, AR_PN0072_FR_0043, */
FUNC(Fls_LengthType, FLS_PRIVATE_CODE) Fls_ReadMisAlignHandler
(const Fls_AddressType LulSourceAddress, const Fls_AddressType LulTargetAddress,
 Fls_LengthType LulLength)
{
  /* QAC Warning: START Msg(2:3204)-4 */
  /* Local variable to hold offset of source address when not word-aligned */
  uint8 LucSrcOffset;
  /* Local variable to hold offset of target address when not word-aligned */
  uint8 LucTgtOffset;
  /* END Msg(2:3204)-4 */
  /* Get the offset value by masking the source address with page size */
  LucSrcOffset = (uint8)(LulSourceAddress &(FLS_PAGE_SIZE - FLS_ONE));
  /* Get offset value by masking the target address with page size */
  LucTgtOffset = (uint8)(LulTargetAddress & (FLS_PAGE_SIZE - FLS_ONE));
  /* Set the Read Type to FLS_MISALIGNED_READ */
  Fls_GstVar.enReadType = FLS_MISALIGNED_READ;
  /* Check whether offset value is not zero */
  if (FLS_ZERO != LucSrcOffset)
  {
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Set the global variable with length of bytes to be processed */
    Fls_GstVar.ulRequestedLength = LulLength;
    /*
     * Round off the source address value to the page boundary by
     * subtracting the offset value.
     */
    Fls_GstVar.ulReadAddress = LulSourceAddress - LucSrcOffset;
    /* Increment the length with offset value */
    LulLength = LulLength + LucSrcOffset;
    Fls_GstVar.ucOffset = LucSrcOffset;
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
  }
  /* TargetAddress is not aligned */
  else if (FLS_ZERO != LucTgtOffset)
  {
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Set the global variable with length of bytes to be processed */
    Fls_GstVar.ulRequestedLength = LulLength;
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
  }
  else
  {
    /* Set the Read Type to FLS_ALIGNED_READ */
    Fls_GstVar.enReadType = FLS_ALIGNED_READ;
  }
  /* Check whether length is not aligned to the page boundary */
  if (FLS_MISALIGNED_READ == Fls_GstVar.enReadType)
  {
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* MISRA Violation: START Msg(4:0310)-5 */
    /* QAC Warning: START Msg(2:3892)-5 */
    /* Assign Temporary Buffer Address */
    Fls_GstVar.pTempBufferAddress = (const uint8 *)&Fls_GulTempBuffer[FLS_ZERO];
    /* END Msg(2:3892)-5 */
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* END Msg(4:0310)-5 */
    if ((uint32)FLS_ZERO != (LulLength & (uint32)(FLS_PAGE_SIZE - FLS_ONE)))
    {
      /* Round off the length value to the page boundary */
      LulLength = LulLength + ((uint32)FLS_PAGE_SIZE - (LulLength &
          (uint32)(FLS_PAGE_SIZE - FLS_ONE)));
    }
    else
    {
      /* No action required */
    }
  }
  else
  {
    /* No action required */
  }
  return(LulLength);
}/* End of function Fls_ReadMisAlignHandler */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if (FLS_READIMMEDIATE_API == STD_ON) */

/*******************************************************************************
** Function Name             : Fls_GetMaxReadBytes
**
** Service ID                : NA
**
** Description               : This function returns the maximum number of read
**                             bytes based on the current Driver Mode.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : Mode
**
** InOut Parameters          : None
**
** Output Parameters         : Maximum Read bytes
**
** Return parameter          : LulMaxReadBytes
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GenCurrentMode,Fls_GpConfigPtr
**
** Function(s) invoked       : None
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_138 */
/* Implements: FLS275_Conf, FLS276_Conf */
/* Implements: ECUC_Fls_00275, ECUC_Fls_00276*/
FUNC(uint32, FLS_PRIVATE_CODE) Fls_GetMaxReadBytes(void)
{
  /* Local variable to hold the maximum read bytes */
  uint32 LulMaxReadBytes;
  /* Check if the FAST Mode is Set */
  /* QAC Warning: START Msg(2:2814)-3 */
  if (MEMIF_MODE_FAST == Fls_GenCurrentMode)
  {
    LulMaxReadBytes = Fls_GpConfigPtr->ulFlsFastModeMaxReadBytes;
  }
  else
  {
    LulMaxReadBytes = Fls_GpConfigPtr->ulFlsSlowModeMaxReadBytes;
  }
  /* END Msg(2:2814)-3 */
  return(LulMaxReadBytes);
}/* End of function Fls_GetMaxReadBytes */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_ReportECCErrorToCbk
**
** Service ID                : NA
**
** Description               : This function checks and reports ECC Error.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : LenStatus, LblSECError
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.ulSrcDestAddress,
**                             Fls_GstVar.ulReadAddress,
**                             Fls_GpConfigPtr->pEccSEDNotificationPointer,
**                             Fls_GpConfigPtr->pEccDEDNotificationPointer
**
** Function(s) invoked       : None
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_139 */
/* Implements: AR_PN0072_FSR_0029 */
/* QAC Warning: START Msg(2:3227)-1*/
FUNC(void, FLS_PRIVATE_CODE) Fls_ReportECCErrorToCbk
       (Fls_FcuStatusType LenStatus, boolean LblSECError)
/* END Msg(2:3227)-1*/
{
  uint32 LulSrcDestAddress;
  if (FLS_FCU_ERR_ECC_DED == LenStatus)
  {
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Global variable to hold the ECC error occurrence address */
    Fls_GstVar.ulSrcDestAddress = Fls_GstVar.ulReadAddress -
                                                           FLS_FCU_WRITE_SIZE;
    Fls_GstVar.ulSrcDestAddress = Fls_GstVar.ulSrcDestAddress -
                                                        FLS_DF_BASE_ADDRESS;
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Check for ECC DED notification pointer is configured as null */
    /* QAC Warning: START Msg(2:2814)-3 */
    if (NULL_PTR != Fls_GpConfigPtr->pEccDEDNotificationPointer)
    /* END Msg(2:2814)-3 */
    {
      LulSrcDestAddress = Fls_GstVar.ulSrcDestAddress;
      /* ECC double bit error notification to the upper layer */
      Fls_GpConfigPtr->pEccDEDNotificationPointer(LulSrcDestAddress);
    }
    else
    {
      /* No action required */
    }
  }
  else if ((FLS_FCU_ERR_ECC_SED == LenStatus) && (FLS_TRUE == LblSECError))
  {
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    Fls_GstVar.ulSrcDestAddress = Fls_GstVar.ulSrcDestAddress -
                                                        FLS_DF_BASE_ADDRESS;
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Report SEC if Error has occurred and Notification pointer is NULL */
    if (NULL_PTR != Fls_GpConfigPtr->pEccSEDNotificationPointer)
    {
      LulSrcDestAddress = Fls_GstVar.ulSrcDestAddress;
      /* ECC single bit error notification to the upper layer */
      Fls_GpConfigPtr->pEccSEDNotificationPointer(LulSrcDestAddress);
    }
    else
    {
      /* No action required */
    }
  }
  else
  {
     /* No action required */
  }

}/* End of function Fls_ReportECCErrorToCbk */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_CopyToTargetBuff
**
** Service ID                : NA
**
** Description               : This function is used to copy data from Temporary
**                             Buffer to Target Buffer when the command is
**                             FLS_COMMAND_READ_IMM.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : LblLastRead, LulMaxReadBytes
**
** InOut Parameters          : None
**
** Output Parameters         : MemIf_JobResultType
**
** Return parameter          : LucReturnValue
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.ucOffset,
**                             Fls_GstVar.pTempBufferAddress,
**                             Fls_GstVar.ulCurrentLength,
**                             Fls_GstVar.ulRequestedLength,
**                             Fls_GstVar.pBufferAddress
**
** Function(s) invoked       : None
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_141 */
/* Implements: FLS241 */
/* Implements: SWS_Fls_00241 */
/* Implements: AR_PN0072_FR_0014 */
/* QAC Warning: START Msg(2:3227)-1*/
FUNC(MemIf_JobResultType, FLS_PRIVATE_CODE) Fls_CopyToTargetBuff
(boolean LblLastRead, const uint32 LulMaxReadBytes)
/* END Msg(2:3227)-1*/
{
  /* Local variable to store the processed bytes count */
  uint32 LulBytesProcessed;
  /* Local variable to hold the loop count */
  uint32 LulLoopCount = (uint32)FLS_ZERO;
  /* Local variable to return the Job Status */
  MemIf_JobResultType LenReturnValue;

  if (FLS_MISALIGNED_READ == Fls_GstVar.enReadType)
  {
    if (FLS_TRUE != LblLastRead)
    {
    /* Set the bytes to be processed to maximum read bytes per cycle */
      LulBytesProcessed = (LulMaxReadBytes - Fls_GstVar.ucOffset);
      /* MISRA Violation: START Msg(4:0488)-3 */
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Disable relevant interrupts to protect this critical section */
      FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
      /* Reset the buffer pointer with number of bytes it processed */
      Fls_GstVar.pTempBufferAddress = (Fls_GstVar.pTempBufferAddress -
                                                        LulBytesProcessed);
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enable relevant interrupts to exit this critical section */
      FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
      /* END Msg(4:0488)-3 */
      /* Set the Job Status to Pending */
      LenReturnValue = MEMIF_JOB_PENDING;
    }
    else
    {
      /* Set the bytes to be processed to remaining read bytes */
      LulBytesProcessed = Fls_GstVar.ulCurrentLength;
      /* MISRA Violation: START Msg(4:0488)-3 */
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Disable relevant interrupts to protect this critical section */
      FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
      /* Reset the buffer pointer with number of bytes it processed */
      Fls_GstVar.pTempBufferAddress = (Fls_GstVar.pTempBufferAddress +
                                 Fls_GstVar.ucOffset) - LulBytesProcessed;
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enable relevant interrupts to exit this critical section */
      FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
      /* END Msg(4:0488)-3 */
      LulBytesProcessed = Fls_GstVar.ulRequestedLength;
      /* Set the Job Status to OK */
      LenReturnValue = MEMIF_JOB_OK;
    }

    /* Loop until the number of bytes read in one cycle */
    while (LulLoopCount < LulBytesProcessed)
    {
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Disable relevant interrupts to protect this critical section */
      FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
      /* MISRA Violation: START Msg(4:0311)-6 */
      *((uint8 *) Fls_GstVar.pBufferAddress) =
                               *((uint8 *)Fls_GstVar.pTempBufferAddress);
      /* END Msg(4:0311)-6 */
      LulLoopCount++;
      /* MISRA Violation: START Msg(4:0489)-4 */
      Fls_GstVar.pBufferAddress++;
      Fls_GstVar.pTempBufferAddress++;
      /* END Msg(4:0489)-4 */
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enable relevant interrupts to exit this critical section */
      FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    }
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* MISRA Violation: START Msg(4:0488)-3 */
    /* Increment the buffer pointer with number of bytes it processed */
    Fls_GstVar.pTempBufferAddress = Fls_GstVar.pTempBufferAddress -
                               (Fls_GstVar.ucOffset + LulBytesProcessed);
    /* END Msg(4:0488)-3 */
    /* Set the global variable offset to zero */
    Fls_GstVar.ucOffset = FLS_ZERO;
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
  }
  else
  {
    if (FLS_TRUE != LblLastRead)
    {
      /* Set the Job Status to Pending */
      LenReturnValue = MEMIF_JOB_PENDING;
    }
    else
    {
      /* Set the Job Status to OK */
      LenReturnValue = MEMIF_JOB_OK;
    }
  }

  return(LenReturnValue);
}/* End of function Fls_CopyToTargetBuff */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/*******************************************************************************
** Function Name             : Fls_ProcessCancel
**
** Service ID                : NA
**
** Description               : This function invokes issues the Forced Stop
**                             Command to stop the ongoing FCU operation.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.enDFStatus
**
** Function(s) invoked       : Fls_FcuSwitchMode, Fls_FcuForcedStop,
**                             Fls_FcuClearStatus
**
** Registers Used            : FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */


/* Implements: FLS_ESDD_UD_142 */
/* Implements: FLS229, FLS348 */
/* Implements: SWS_Fls_00229, SWS_Fls_00348 */
FUNC(void, FLS_PRIVATE_CODE) Fls_ProcessCancel(void)
{
  Fls_FcuStatusType LenStatus;

  /* Switching to P/E Mode */
  LenStatus = Fls_FcuSwitchMode(FLS_FCU_MODE_PE);
  if (FLS_FCU_OK == LenStatus)
  {
    /* Issuing Forced Stop Command */
    LenStatus = Fls_FcuForcedStop();
  }
  else
  {
    /* No action required */
  }

  if (FLS_FCU_OK == LenStatus)
  {
    /* Issue Clear Status command */
    Fls_FcuClearStatus();
    LenStatus = Fls_FcuSwitchMode(FLS_FCU_MODE_USER);

  }
  else
  {
    /* No action required */
  }

  if (FLS_FCU_OK == LenStatus)
  {
     LenStatus = FLS_FCU_CANCELED;
  }
  else
  {
    LenStatus = FLS_FCU_ERR_INTERNAL;
  }

  Fls_GstVar.enDFStatus = LenStatus;
} /* End of function Fls_ProcessCancel */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

#if (FLS_FHVE_REGS == SUPPORTED)
/*******************************************************************************
** Function Name             : Fls_SetFHVE
**
** Service ID                : NA
**
** Description               : Pull FHVE3 and FHVE15 registers pin to VDD or VSS
**                             to Enable or to Disable the flash memory software
**                             protection.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : NA
**
** Input Parameters          : value (protection enable or disable)
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GblFlashEnable
**
** Function(s) invoked       : REGVERIFY
**
** Registers Used            : FHVE3,FHVE15
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_247 */
/* Implements: AR_PN0072_FR_0009 */
FUNC(void, FLS_PRIVATE_CODE) Fls_SetFHVE(boolean LblEnableMemProtect)
{

  if (Fls_GblFlashEnable != LblEnableMemProtect)
  {
    FLS_WRITE_REG_AND_MIRROR(
                              &FLS_FHVE3,
                              (uint8)LblEnableMemProtect,
                              &Fls_GaaRamMirror[RAM_IDX_FHVE3]
                            )
    FLS_CHECK_WRITE_VERIFY_RUNTIME(
                                    &FLS_FHVE3,
                                    (uint8)LblEnableMemProtect,
                                    (uint8)RAM_MASK_NO_MASK,
                                    FLS_SETFHVE_SID
                                  )
    FLS_WRITE_REG_AND_MIRROR(
                              &FLS_FHVE15,
                              (uint8)LblEnableMemProtect,
                              &Fls_GaaRamMirror[RAM_IDX_FHVE15]
                            )
    FLS_CHECK_WRITE_VERIFY_RUNTIME(
                                    &FLS_FHVE15,
                                    (uint8)LblEnableMemProtect,
                                    (uint8)RAM_MASK_NO_MASK,
                                    FLS_SETFHVE_SID
                                  )
    Fls_GblFlashEnable = LblEnableMemProtect;
  }
  else
  {
    /* No Action required */
  }
} /* End of function Fls_SetFHVE */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if (FLS_FHVE_REGS == SUPPORTED) */

/*******************************************************************************
** Function Name             : Fls_InitiateBlankCheckJob
**
** Service ID                : NA
**
** Description               : This function initiates the Blank Check Job
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Std_ReturnType
**
** Return parameter          : LenReturn
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.enDFStatus,Fls_GulTimeOutCounter,
**                             Fls_GblTimeOutMonitor
**                             Fls_GstVar.ulSrcDestAddress,
**
** Function(s) invoked       : Fls_FcuPerformBlankCheck
**
** Registers Used            : FSADDR,FEADDR,
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_127 */
/* Implements: AR_PN0072_FR_0040, AR_PN0072_FR_0049*/
FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InitiateBlankCheckJob(void)
{
  /* Variable to return Job Initiation status */
  Std_ReturnType LucReturn = E_OK;
  /* Initialize the local variable to hold the FCU Status */
  Fls_FcuStatusType LenStatus;
  /* Variable to save the address for Blank Check */
  uint32 LulBCAddress;
  /* Variable which holds requested length */
  uint32 LulRequestedLength;
  /* Get the address for Blank Check Job */
  LulBCAddress = Fls_GstVar.ulSrcDestAddress - FLS_DF_BASE_ADDRESS;

  #if (FLS_TIMEOUT_MONITORING == STD_ON)
  #if (FLS_INTERRUPT_MODE == STD_OFF)
  /* Implements AR_PN0072_FR_0059 */
  Fls_GulTimeOutCounter = (uint32)((uint32)FLS_BLANKCHECK_TIMEOUT_COUNT * \
                     ( Fls_GstVar.ulRequestedLength / FLS_FCU_WRITE_SIZE));
    #else
    Fls_GulTimeOutCounter = (uint32)((uint32)FLS_ISR_TIMEOUT_COUNT * \
                    ( Fls_GstVar.ulRequestedLength / FLS_FCU_WRITE_SIZE));
    #endif /* #if (FLS_INTERRUPT_MODE == STD_OFF) */
  /* Set Time Out Monitor Flag to TRUE */
  Fls_GblTimeOutMonitor = FLS_TRUE;
  #endif /* End of #if (FLS_TIMEOUT_MONITORING == STD_ON) */

  LulRequestedLength = Fls_GstVar.ulRequestedLength;
  /* Call Fls_FcuPerformBlankCheck to perform Blank Check */
  LenStatus = Fls_FcuPerformBlankCheck(LulBCAddress, LulRequestedLength);
  if (FLS_FCU_OK != LenStatus)
  {
    LucReturn = E_NOT_OK;
  }
  else
  {
    /* No Action required */
  }

  /* Save the FCU status */
  Fls_GstVar.enDFStatus = LenStatus;

  return(LucReturn);
} /* End of function Fls_InitiateBlankCheckJob */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_MainBlankCheck
**
** Service ID                : NA
**
** Description               : This function is called from Fls_MainFunction,
**                             when the command is BlankCheck Operation.
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GblVerifyCompletedJob
**
** Function(s) invoked       : Fls_FcuCheckBCJobStatus,Fls_FcuBlankCheckResult,
**                             Fls_ProcessJobResult,Fls_FcuSwitchMode,
**                             Det_ReportError
**
** Registers Used            : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,
**                             DCENm,DTCTm,FBCSTAT,ICFLENDNM,
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_165 */
/* Implements: AR_PN0072_FR_0040, AR_PN0072_FR_0049*/
FUNC(void, FLS_PRIVATE_CODE) Fls_MainBlankCheck(void)
{
  /* Variable to hold the Data Flash Status */
  Fls_FcuStatusType LenStatus;

  /* Get the Data flash Status */
  LenStatus = Fls_FcuCheckBCJobStatus();

  if (FLS_FCU_OK == LenStatus)
  {
    /* Switching Back to User Mode */
    LenStatus = Fls_FcuSwitchMode(FLS_FCU_MODE_USER);
    if (FLS_FCU_OK == LenStatus)
    {
      /* Check if Block is inconsistent or Erased */
      LenStatus = Fls_FcuBlankCheckResult();

      /* Check Blank Check Status and process accordingly */
      if (FLS_FCU_OK == LenStatus)
      {
        /* Data Flash is Erased */
        Fls_ProcessJobResult(MEMIF_JOB_OK);
      }
      else
      {
        #if (FLS_DEV_ERROR_DETECT == STD_ON)
        /* QAC Warning: START Msg(2:3416)-2 */
        if (FLS_TRUE == Fls_GblVerifyCompletedJob)
        /* END Msg(2:3416)-2 */
        {
          /* Process Job Failure in case of verification after Erase operation
             Failed */
          Fls_ProcessJobResult(MEMIF_JOB_FAILED);
          /* Report error to DET */
         (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                               FLS_MAINFUNCTION_SID, FLS_E_VERIFY_ERASE_FAILED);
        }
        else
        #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
        {
          /* Set Job result as Block Consistent */
          Fls_ProcessJobResult(MEMIF_BLOCK_INCONSISTENT);
        }
      }
    }
    else
    {
      Fls_ProcessJobResult(MEMIF_JOB_FAILED);
    }
  }
  else
  {
    /* No Action required */
  }

}/* End of function Fls_MainBlankCheck */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_ProcessJobResult
**
** Service ID                : NA
**
** Description               : Function to process in case of Job Success/
**                             Failure for erase, write and read operations.
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : Re-entrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GenJobResult,Fls_GstVar.enCommand
**                             Fls_GenState,Fls_GblFlashEnable,
**                             Fls_GblVerifyCompletedJob,Fls_GblTimeOutMonitor,
**                             Fls_GpConfigPtr
**
** Function(s) invoked       : Fls_SetFHVE,Fls_RestoreIntReq,
**                             Fls_FcuResetErrorBits,Fls_CallJobNotification
**                             Dem_ReportErrorStatus, Det_ReportRuntimeError,
**                             Fls_DisableDmaChannel
**
** Registers Used            : FHVE3,FHVE15,DCENm,DTCTm,ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_187 */
/* QAC Warning: START Msg(2:3227)-1*/
FUNC(void, FLS_PRIVATE_CODE) Fls_ProcessJobResult
                                      (MemIf_JobResultType LenResult)
/* END Msg(2:3227)-1*/
{
  Std_ReturnType LucReturn;
  #if (FLS_INTERRUPT_MODE == STD_ON)
  /* MISRA Violation: START Msg(4:4397)-7 */
  /* QAC Warning: START Msg(2:2814)-3 */
  /* MISRA Violation: START Msg(4:0303)-1 */
  /* Disable interrupt processing */
  /* Implements: FLS_ESDD_UD_103 */
  RH850_SV_MODE_ICR_OR(16, &(FLS_ICFLENDNM), (FLS_SET_INT_MK));
  /* END Msg(4:0303)-1 */
  /* END Msg(2:2814)-3 */
  /* MISRA Violation: END Msg(4:4397)-7 */
  Fls_RestoreIntReq();
  #endif /* End of #if (FLS_INTERRUPT_MODE == STD_ON) */

  #if (FLS_FHVE_REGS == SUPPORTED)
  if (FLS_TRUE == Fls_GblFlashEnable)
  {
    /* Enable the flash memory software protection */
    Fls_SetFHVE(FLS_FLASH_PROTECTION_ON);
    Fls_GblFlashEnable = FLS_FALSE;
  }
  else
  {
    /* No action required */
  }
  #endif /* End of #if (FLS_FHVE_REGS == SUPPORTED) */
  #if ((FLS_SET_MODE_API == STD_ON) &&\
       (FLS_DMA_INSTANCES != FLS_DMA_ZERO))
  if (FLS_COMMAND_DMA_WRITE == Fls_GstVar.enCommand)
  {
    /* Disable DMA channel after transfer is complete, or transfer error */
    Fls_DisableDmaChannel();
  }
  else
  {
    /* no action needed */
  }
  #endif /*(FLS_SET_MODE_API == STD_ON) && (FLS_DMA_INSTANCES != FLS_DMA_ZERO)*/
  /* Set the job result to Job Failed */
  Fls_GenJobResult = LenResult;
  /* Set the command as None */
  Fls_GstVar.enCommand = FLS_COMMAND_NONE;
  /* Check for the status is FCU_ERR_INTERNAL */
  if (FLS_FCU_ERR_INTERNAL == Fls_GstVar.enDFStatus)
  {
    /* Set the driver state to uninitialized */
    Fls_GenState = MEMIF_UNINIT;
  }
  else if (FLS_FCU_ERR_ERASE == Fls_GstVar.enDFStatus)
  {
    #if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
    /* Report DEM as Erase Job Failed */
    Dem_ReportErrorStatus(FLS_E_ERASE_FAILED, DEM_EVENT_STATUS_FAILED);
    #else
    /* Report DET as Erase Job Failed */
    (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                            FLS_ERASE_SID, FLS_E_ERASE_FAILED);
    #endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */

    /*Invoke Fls_FcuResetErrorBits to clear error bits */
    LucReturn = Fls_FcuResetErrorBits();
    if (E_OK == LucReturn)
    {
      /* Set the driver state to idle */
      Fls_GenState = MEMIF_IDLE;
    }
    else
    {
      /* Set the driver state to UNINIT */
      Fls_GenState = MEMIF_UNINIT;
    }
  }
  else if (FLS_FCU_ERR_WRITE == Fls_GstVar.enDFStatus)
  {
    #if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
    /* Report DEM as Write Job Failed */
    Dem_ReportErrorStatus(FLS_E_WRITE_FAILED, DEM_EVENT_STATUS_FAILED);
    #else
    /* Report DET as Write Job Failed */
    (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                              FLS_WRITE_SID, FLS_E_WRITE_FAILED);
    #endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */

    /*Invoke Fls_FcuResetErrorBits to clear error bits */
    LucReturn = Fls_FcuResetErrorBits();
    if (E_OK == LucReturn)
    {
      /* Set the driver state to idle */
      Fls_GenState = MEMIF_IDLE;
    }
    else
    {
      /* Set the driver state to UNINIT */
      Fls_GenState = MEMIF_UNINIT;
    }
  }
  else
  {
    /* Set the driver state to idle */
    Fls_GenState = MEMIF_IDLE;
  }

  #if (FLS_TIMEOUT_MONITORING == STD_ON)
  /* Clear the Global Time out Monitor after servicing */
  Fls_GblTimeOutMonitor = FLS_FALSE;
  #endif /* End of #if (FLS_TIMEOUT_MONITORING == STD_ON) */
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  Fls_GblVerifyCompletedJob = FLS_FALSE;
  #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  #if (FLS_JOB_NOTIF_CONFIG == STD_ON)
  Fls_CallJobNotification();
  #endif /* End of #if (FLS_JOB_NOTIF_CONFIG == STD_ON) */
}/* End of function Fls_ProcessJobResult */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

#if (FLS_JOB_NOTIF_CONFIG == STD_ON)
/*******************************************************************************
** Function Name             : Fls_CallJobNotification
**
** Service ID                : NA
**
** Description               : This function calls the required Notification
**                             function based on the Job result.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GenJobResult,Fls_GpConfigPtr
**
** Function(s) invoked       : Fls_GpConfigPtr->pJobEndNotificationPointer,
**                             Fls_GpConfigPtr->pJobErrorNotificationPointer
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_164*/
/* Implements: FLS307_Conf, FLS274_Conf, FLS262, FLS167, FLS263, FLS347 */
/* Implements: ECUC_Fls_00307, ECUC_Fls_00274, SWS_Fls_00262 */
/* Implements: SWS_Fls_00167, SWS_Fls_00263, SWS_Fls_00347*/
FUNC(void, FLS_PRIVATE_CODE) Fls_CallJobNotification(void)
{
  /* Call the Job Notification corresponding to the Job result */
  /* QAC Warning: START Msg(2:3416)-2 */
  /* QAC Warning: START Msg(2:2814)-3 */
  if ((MEMIF_JOB_OK == Fls_GenJobResult) &&
      (NULL_PTR != Fls_GpConfigPtr->pJobEndNotificationPointer))
    /* END Msg(2:2814)-3 */
    /* END Msg(2:3416)-2 */
  {
    /* If job ended with success and call the job end call back function */
    Fls_GpConfigPtr->pJobEndNotificationPointer();
  }
  /* Job ended with an error */
  else if (NULL_PTR != Fls_GpConfigPtr->pJobErrorNotificationPointer)
  {
    /* If job ended with error and call the job error call back function */
    Fls_GpConfigPtr->pJobErrorNotificationPointer();
  }
  else
  {
    /* No action required */
  }

}/* End of function Fls_CallJobNotification */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if (FLS_JOB_NOTIF_CONFIG == STD_ON) */

#if (FLS_INTERRUPT_MODE == STD_ON)
/*******************************************************************************
** Function Name             : Fls_ClearIntReq
**
** Service ID                : NA
**
** Description               : This function clears interrupt request flag from
**                             ICFLENDNM
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : NA
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_166 */
/* Implements: AR_PN0072_FR_0047 */
FUNC(void, FLS_PRIVATE_CODE) Fls_ClearIntReq(void)
{
  /* MISRA Violation: START Msg(4:0303)-1 */
  RH850_SV_MODE_ICR_AND (16, &(FLS_ICFLENDNM), (FLS_RESET_INT_REQ));
  /* END Msg(4:0303)-1 */
} /* End of function Fls_ClearIntReq */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_SetIntReq
**
** Service ID                : NA
**
** Description               : This function sets interrupt request flag from
**                             ICFLENDNM
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : NA
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_131 */
/* Implements: AR_PN0072_FR_0047 */
FUNC(void, FLS_PRIVATE_CODE) Fls_SetIntReq(void)
{
  /* MISRA Violation: START Msg(4:0303)-1 */
  RH850_SV_MODE_ICR_OR (16, &(FLS_ICFLENDNM), (FLS_SET_INT_REQ));
  /* MISRA Violation: END Msg(4:0303)-1 */
}/* End of function Fls_SetIntReq */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_RestoreIntReq
**
** Service ID                : NA
**
** Description               : This function restores interrupt pending bit from
**                             Fls_GblIntrRqstFlag
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : NA
**
** Global Variables Used     : Fls_GblIntrRqstFlag
**
** Function(s) invoked       : Fls_SetIntReq,Fls_ClearIntReq
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_167*/
/* Implements: AR_PN0072_FR_0047*/
FUNC(void, FLS_PRIVATE_CODE) Fls_RestoreIntReq(void)
{
  if (FLS_TRUE == Fls_GblIntrRqstFlag)
  {
    /* Set the Interrupt Flag if the TRUE */
    Fls_SetIntReq();
  }
  else
  {
    /* Clear the Interrupt Flag if the FALSE */
    Fls_ClearIntReq();
  }
} /* End of function Fls_RestoreIntReq */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_GetIntReq
**
** Service ID                : NA
**
** Description               : This function gets interrupt request flag from
**                             ICFLENDNM
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : NA
**
** Global Variables Used     : Fls_GblIntrRqstFlag
**
** Function(s) invoked       : None
**
** Registers Used            : ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_168 */
/* Implements: AR_PN0072_FR_0047 */
FUNC(void, FLS_PRIVATE_CODE) Fls_GetIntReq(void)
{
  uint16 LusRegvalue;
  /* MISRA Violation: START Msg(4:0303)-1 */
  LusRegvalue = FLS_ICFLENDNM;
  /* Get the Value of Interrupt Request Bit */
  LusRegvalue = (((uint16)(LusRegvalue >> FLS_INTERRUPT_BIT_NUM)) &
                                              (uint16)FLS_ONE);
  Fls_GblIntrRqstFlag = (boolean)LusRegvalue;
  /* MISRA Violation: END Msg(4:0303)-1 */

}/* End of function Fls_GetIntReq */


#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_DisableFaciEndInt
**
** Service ID                : NA
**
** Description               : This function clears interrupt mask flag and
**                             interrupt request flag from ICFLENDNM register.
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : NA
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_151 */
/* Implements: AR_PN0072_FR_0047 */
FUNC(void, FLS_PRIVATE_CODE) Fls_DisableFaciEndInt(void)
{
  volatile uint16 LusRegvalue;
  /* MISRA Violation: START Msg(4:0303)-1 */
  LusRegvalue = FLS_ICFLENDNM;
  LusRegvalue &= FLS_RESET_INT_REQ;
  LusRegvalue |= FLS_SET_INT_MK;
  /*Clear the Interrupt Request and set the interrupt mask Bit */
  RH850_SV_MODE_ICR_AND (16, &(FLS_ICFLENDNM), (LusRegvalue));
  /* MISRA Violation: END Msg(4:0303)-1 */
} /* End of function Fls_ClearIntReq */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_EnableFaciEndInt
**
** Service ID                : NA
**
** Description               : This function sets interrupt mask flag
**                             from ICFLENDNM register.
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : NA
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_152 */
/* Implements: AR_PN0072_FR_0047 */
FUNC(void, FLS_PRIVATE_CODE) Fls_EnableFaciEndInt(void)
{

  volatile uint16 LusRegvalue;
  /* MISRA Violation: START Msg(4:0303)-1 */
  LusRegvalue = FLS_ICFLENDNM;
  LusRegvalue &= FLS_RESET_INT_MK;
  /*Reset the Interrupt Mask Bit */
  /* Implements: FLS_ESDD_UD_103 */
  RH850_SV_MODE_ICR_OR (16, &(FLS_ICFLENDNM), (LusRegvalue));
  /* MISRA Violation: END Msg(4:0303)-1 */
}/* End of function Fls_SetIntReq */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

#endif /* End of #if (FLS_INTERRUPT_MODE == STD_ON) */

#if (FLS_RESUME_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_ProcessResume
**
** Service ID                : NA
**
** Description               : The function restores the job data and resumes
**                             the job
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : NA
**
** Global Variables Used     : Fls_GenState,Fls_GenJobResult,
**                             Fls_GstVar.enCommand,Fls_GblJobSuspended
**
**  Function(s) invoked      : Fls_RestoreJobData, Fls_InitiateEraseJob,
**                             Fls_InitiateWriteJob,Fls_SetFHVE,
**                             Fls_ProcessJobResult
**
** Registers Used            : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,
**                             DCENm,DTCTm,ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_169 */
/* Implements: AR_PN0072_FR_0046, AR_PN0072_FR_0049 */
FUNC(void, FLS_PRIVATE_CODE) Fls_ProcessResume(void)
{
  Std_ReturnType LucReturnValue = E_OK;
  /* Check if any Job is Suspended */
  /* QAC Warning: START Msg(2:3416)-2 */
  if (FLS_TRUE == Fls_GblJobSuspended)
  /* END Msg(2:3416)-2 */
  {
    /* Restore the Job Variables from the back-up structure */
    Fls_RestoreJobData();
    /* Set the Driver status to Busy */
    Fls_GenState = MEMIF_BUSY;
    /* Set the Job Status to Pending */
    Fls_GenJobResult = MEMIF_JOB_PENDING;
    /* Clear the Flag*/
    Fls_GblJobSuspended = FLS_FALSE;
    #if (FLS_FHVE_REGS == SUPPORTED)
    if (FLS_FALSE == Fls_GblFlashEnable)
    {
      /* Disable the flash memory software protection */
      Fls_SetFHVE(FLS_FLASH_PROTECTION_OFF);
      Fls_GblFlashEnable = FLS_TRUE;
    }
    else
    {
      /* No action required */
    }
    #endif /* End of #if (FLS_FHVE_REGS == SUPPORTED) */

    switch (Fls_GstVar.enCommand)
    {
    /* In case of Erase Operation */
    case FLS_COMMAND_ERASE:
         LucReturnValue = Fls_InitiateEraseJob();
    break;
    case FLS_COMMAND_WRITE:
         LucReturnValue = Fls_InitiateWriteJob();
    break;
    /* QAC Warning: START Msg(2:2016)-6 */
    default:
         /* No action required */
    break;
    }
    /* END Msg(2:2016)-6 */
    /* Check for the status is FLS_FCU_OK */
    if (E_NOT_OK == LucReturnValue)
    {
      Fls_ProcessJobResult(MEMIF_JOB_FAILED);
    }
    else
    {
      /* No action Required */
    }
  }
  else
  {
    /* No action required */
  }

} /* End of function Fls_ProcessResume */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if (FLS_RESUME_API == STD_ON) */

#if (FLS_RESUME_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_RestoreJobData
**
** Service ID                : NA
**
** Description               : This function takes the job result from the back
**                             up global job structure and restores it into
**                             the original job structure when suspend operation
**                             occurs
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : NA
**
** Global Variables Used     : Fls_GstVar.pBufferAddress,
**                             Fls_GstVar.ulSrcDestAddress,
**                             Fls_GstVar.ulReadAddress,
**                             Fls_GstVar.ulJobStartAddress,
**                             Fls_GstVar.ulJobEndAddress,
**                             Fls_GstVar.ulCurrentLength,
**                             Fls_GstVar.ulRequestedLength,
**                             Fls_GstVar.ucOffset,Fls_GstVar.enReadType,
**                             Fls_GstVar.enCommand,
**                             Fls_GstBackUpVar.pBufferAddress,
**                             Fls_GstBackUpVar.ulSrcDestAddress,
**                             Fls_GstBackUpVar.ulReadAddress,
**                             Fls_GstBackUpVar.ulJobStartAddress,
**                             Fls_GstBackUpVar.ulJobEndAddress,
**                             Fls_GstBackUpVar.ulCurrentLength,
**                             Fls_GstBackUpVar.ulRequestedLength,
**                             Fls_GstBackUpVar.ucOffset,
**                             Fls_GstBackUpVar.enReadType,
**                             Fls_GstBackUpVar.enCommand
**
** Function(s) invoked       : None
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_170 */
/* Implements: AR_PN0072_FR_0046, AR_PN0072_FR_0049 */
FUNC(void, FLS_PRIVATE_CODE) Fls_RestoreJobData(void)
{
  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Disable relevant interrupts to protect this critical section */
  FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
  #endif /* #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
  /* Store the source address */
  Fls_GstVar.pBufferAddress = Fls_GstBackUpVar.pBufferAddress;
  /* Store the target address */
  Fls_GstVar.ulSrcDestAddress = Fls_GstBackUpVar.ulSrcDestAddress;
  /* Store the read address */
  Fls_GstVar.ulReadAddress = Fls_GstBackUpVar.ulReadAddress;
  /* Store the erase/write start address */
  Fls_GstVar.ulJobStartAddress = Fls_GstBackUpVar.ulJobStartAddress;
  /* Store the erase/write end address */
  Fls_GstVar.ulJobEndAddress = Fls_GstBackUpVar.ulJobEndAddress;
  /* Store the adjusted length */
  Fls_GstVar.ulCurrentLength = Fls_GstBackUpVar.ulCurrentLength;
  /* Store the requested number of bytes to be processed */
  Fls_GstVar.ulRequestedLength = Fls_GstBackUpVar.ulRequestedLength;
  /* Store offset by masking the source address with page size */
  Fls_GstVar.ucOffset = Fls_GstBackUpVar.ucOffset;
  /* Store the Flash read type */
  Fls_GstVar.enReadType = Fls_GstBackUpVar.enReadType;
  /* Store the requested commands */
  Fls_GstVar.enCommand = Fls_GstBackUpVar.enCommand;
  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enable relevant interrupts to exit this critical section */
  FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
  #endif /* #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
} /* End of function Fls_RestoreJobData */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if (FLS_RESUME_API == STD_ON) */

#if ((FLS_RESUME_API == STD_ON) || (FLS_SUSPEND_API == STD_ON))
/*******************************************************************************
** Function Name             : Fls_ClearBackUpData
**
** Service ID                : NA
**
** Description               : This function clears the job data from the back
**                             up global job structure.
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : NA
**
** Global Variables Used     : Fls_GstVar.pBufferAddress,
**                             Fls_GstVar.ulSrcDestAddress,
**                             Fls_GstVar.ulReadAddress,
**                             Fls_GstVar.ulJobStartAddress,
**                             Fls_GstVar.ulJobEndAddress,
**                             Fls_GstVar.ulCurrentLength,
**                             Fls_GstVar.ulRequestedLength,
**                             Fls_GstVar.ucOffset,Fls_GstVar.enReadType,
**                             Fls_GstVar.enCommand,
**                             Fls_GstBackUpVar.pBufferAddress,
**                             Fls_GstBackUpVar.ulSrcDestAddress,
**                             Fls_GstBackUpVar.ulReadAddress,
**                             Fls_GstBackUpVar.ulJobStartAddress,
**                             Fls_GstBackUpVar.ulJobEndAddress,
**                             Fls_GstBackUpVar.ulCurrentLength,
**                             Fls_GstBackUpVar.ulRequestedLength,
**                             Fls_GstBackUpVar.ucOffset,
**                             Fls_GstBackUpVar.enReadType,
**                             Fls_GstBackUpVar.enCommand
**
** Function(s) invoked       : None
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_171, SWS_Fls_00171 */
/* Implements: AR_PN0072_FR_0045, AR_PN0072_FR_0049 */
FUNC(void, FLS_PRIVATE_CODE) Fls_ClearBackUpData(void)
{
  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Disable relevant interrupts to protect this critical section */
  FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
  #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */

  /* Store the source address */
  /* QAC Warning: START Msg(2:3892)-5 */
  Fls_GstBackUpVar.pBufferAddress = FLS_NULL;
  /* END Msg(2:3892)-5 */
  /* Store the target address */
  Fls_GstBackUpVar.ulSrcDestAddress = (uint32)FLS_ZERO;
  /* Store the read address */
  Fls_GstBackUpVar.ulReadAddress = (uint32)FLS_ZERO;
  /* Store the erase/write start address */
  Fls_GstBackUpVar.ulJobStartAddress = (uint32)FLS_ZERO;
  /* Store the erase/write end address */
  Fls_GstBackUpVar.ulJobEndAddress = (uint32)FLS_ZERO;
  /* Store the adjusted length */
  Fls_GstBackUpVar.ulCurrentLength = (uint32)FLS_ZERO;
  /* Store the requested number of bytes to be processed */
  Fls_GstBackUpVar.ulRequestedLength = (uint32)FLS_ZERO;
  /* Store offset by masking the source address with page size */
  Fls_GstBackUpVar.ucOffset = FLS_ZERO;
  /* Store the Flash read type */
  Fls_GstBackUpVar.enReadType = FLS_MISALIGNED_READ;
  /* Store the requested commands */
  Fls_GstBackUpVar.enCommand = FLS_COMMAND_NONE;

  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enable relevant interrupts to exit this critical section */
  FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
  #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */

} /* End of function Fls_ClearBackUpData */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if ((FLS_RESUME_API == STD_ON) || \
                      (FLS_SUSPEND_API == STD_ON)) */

#if (FLS_SUSPEND_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_ProcessSuspend
**
** Service ID                : NA
**
** Description               : This function backs up the Job structure and
**                             clears original job structure
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : NA
**
** Global Variables Used     : Fls_GenState,Fls_GenJobResult,
**                             Fls_GstVar.enCommand,Fls_GblJobSuspended,
**                             Fls_GblJobSuspendRequest
**
** Function(s) invoked       : Fls_BackupJobData,Fls_FcuSwitchMode
**                             Fls_ProcessJobResult
**
** Registers Used            : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,
**                             DCENm,DTCTm,ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_172 */
/* Implements: AR_PN0072_FR_0045, AR_PN0072_FR_0049 */
FUNC(void, FLS_PRIVATE_CODE) Fls_ProcessSuspend(void)
{
  Fls_FcuStatusType LenStatus;
  LenStatus = Fls_FcuSwitchMode(FLS_FCU_MODE_USER);
  if (FLS_FCU_OK == LenStatus)
  {

    /* Backup the required data in the Job Structure*/
    Fls_BackupJobData();
    /* Set the driver state to idle */
    Fls_GenState = MEMIF_IDLE;
    /* Set the job Result to OK */
    Fls_GenJobResult = MEMIF_JOB_OK;
    /* Set the command to none */
    Fls_GstVar.enCommand = FLS_COMMAND_NONE;
    /* Setting the Flag*/
    Fls_GblJobSuspended = FLS_TRUE;

    #if (FLS_TIMEOUT_MONITORING == STD_ON)
    /* Clear the Global Time out Monitor after servicing */
    Fls_GblTimeOutMonitor = FLS_FALSE;
    #endif /* FLS_TIMEOUT_MONITORING == STD_ON */
  }
  else
  {
    Fls_ProcessJobResult(MEMIF_JOB_FAILED);
  }
  Fls_GblJobSuspendRequest = FLS_FALSE;
} /* End of function Fls_ProcessSuspend */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/*******************************************************************************
** Function Name             : Fls_BackupJobData
**
** Service ID                : NA
**
** Description               : This function takes the job result from the
**                             global job structure and stores it into the
**                             backup structure when suspend operation occurs
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.pBufferAddress,
**                             Fls_GstVar.ulSrcDestAddress,
**                             Fls_GstVar.ulReadAddress,
**                             Fls_GstVar.ulJobStartAddress,
**                             Fls_GstVar.ulJobEndAddress,
**                             Fls_GstVar.ulCurrentLength,
**                             Fls_GstVar.ulRequestedLength,
**                             Fls_GstVar.ucOffset,Fls_GstVar.enReadType,
**                             Fls_GstVar.enCommand,
**                             Fls_GstBackUpVar.pBufferAddress,
**                             Fls_GstBackUpVar.ulSrcDestAddress,
**                             Fls_GstBackUpVar.ulReadAddress,
**                             Fls_GstBackUpVar.ulJobStartAddress,
**                             Fls_GstBackUpVar.ulJobEndAddress,
**                             Fls_GstBackUpVar.ulCurrentLength,
**                             Fls_GstBackUpVar.ulRequestedLength,
**                             Fls_GstBackUpVar.ucOffset,
**                             Fls_GstBackUpVar.enReadType,
**                             Fls_GstBackUpVar.enCommand
**
** Function(s) invoked       : None
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_173 */
/* Implements: AR_PN0072_FR_0045, AR_PN0072_FR_0049 */
FUNC(void, FLS_PRIVATE_CODE) Fls_BackupJobData(void)
{
  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Disable relevant interrupts to protect this critical section */
  FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
  #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */

  /* Store the source address */
  Fls_GstBackUpVar.pBufferAddress = Fls_GstVar.pBufferAddress;
  /* Store the target address */
  Fls_GstBackUpVar.ulSrcDestAddress = Fls_GstVar.ulSrcDestAddress;
  /* Store the read address */
  Fls_GstBackUpVar.ulReadAddress = Fls_GstVar.ulReadAddress;
  /* Store the erase/write start address */
  Fls_GstBackUpVar.ulJobStartAddress = Fls_GstVar.ulJobStartAddress;
  /* Store the erase/write end address */
  Fls_GstBackUpVar.ulJobEndAddress = Fls_GstVar.ulJobEndAddress;
  /* Store the adjusted length */
  Fls_GstBackUpVar.ulCurrentLength = Fls_GstVar.ulCurrentLength;
  /* Store the requested number of bytes to be processed */
  Fls_GstBackUpVar.ulRequestedLength = Fls_GstVar.ulRequestedLength;
  /* Store offset by masking the source address with page size */
  Fls_GstBackUpVar.ucOffset = Fls_GstVar.ucOffset;
  /* Store the Flash read type */
  Fls_GstBackUpVar.enReadType = Fls_GstVar.enReadType;
  /* Store the requested commands */
  Fls_GstBackUpVar.enCommand = Fls_GstVar.enCommand;

  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enable relevant interrupts to exit this critical section */
  FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
  #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */

} /* End of function Fls_BackupJobData */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if (FLS_SUSPEND_API == STD_ON) */

#if (FLS_TIMEOUT_MONITORING == STD_ON)
/*******************************************************************************
** Function Name             : Fls_TimeOutCheckAndProcessing
**
** Service ID                : NA
**
** Description               : This Function checks for Time out and performs
**                             further processing in case of time-out.
**
** Sync/Async                : NA
**
** Re-entrancy               : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : Time Out Processing shall be configured by User.
**
** Global Variables Used     : Fls_GulTimeOutCounter
**
** Function(s) invoked       : Fls_ProcessCancel, Fls_ProcessJobResult,
**                             Det_ReportError,Fls_ClearIntReq
**
** Registers Used            : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,
**                             DCENm,DTCTm,ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_174 */
/* Implements: FLS272, FLS359, FLS360, FLS262 */
/* Implements: SWS_Fls_00272, SWS_Fls_00359, SWS_Fls_00360, SWS_Fls_00262 */
FUNC(void, FLS_PRIVATE_CODE) Fls_TimeOutCheckAndProcessing(void)
{
  /* QAC Warning: START Msg(2:3416)-2 */
  if ((uint32)FLS_ZERO == Fls_GulTimeOutCounter)
  /* END Msg(2:3416)-2 */
  {
    /* Cancel the ongoing job in case of Time-out */
    Fls_ProcessCancel();
    #if (FLS_INTERRUPT_MODE == STD_ON)
    Fls_ClearIntReq();
    #endif /* End of #if (FLS_INTERRUPT_MODE == STD_ON) */
    /* Calling Fls_ProcessJobResult for setting results */
    Fls_ProcessJobResult(MEMIF_JOB_FAILED);
    #if (FLS_DEV_ERROR_DETECT == STD_ON)
    /* Report FLS_E_TIMEOUT to DET */
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                          FLS_MAINFUNCTION_SID, FLS_E_TIMEOUT);
    #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  }
  else
  {
    /* Decrement the Time Out Counter */
    Fls_GulTimeOutCounter--;
  }

} /* End of function Fls_TimeOutCheckAndProcessing */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if (FLS_TIMEOUT_MONITORING == STD_ON) */

#if (FLS_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Function Name             : Fls_DetErrorCheck
**
** Service ID                : NA
**
** Description               : This function is used to check whether the driver
**                             is initialised or busy and report DET accordingly
**                             depending on the service id of each API.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : LucServiceId
**
** InOut Parameters          : None
**
** Output Parameters         : Std_ReturnType
**
** Return parameter          : LucReturnValue
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GblInitStatus,Fls_GenState
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
*******************************************************************************/

#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_162 */
/* Implements: FLS065, FLS023, FLS033, FLS066, FLS099, FLS100, FLS153, FLS154 */
/* Implements: FLS156 */
/* Implements: SWS_Fls_00065, SWS_Fls_00023, SWS_Fls_00033, SWS_Fls_00066 */
/* Implements: SWS_Fls_00099, SWS_Fls_00100, SWS_Fls_00153, SWS_Fls_00154 */
/* Implements: SWS_Fls_00156 */
FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_DetErrorCheck
    (const uint8 LucServiceId)
{
  /* Initialise the variable to hold the DET return value */
  Std_ReturnType LucReturnValue = E_OK;

  /* Check if the module is initialized */
  if (FLS_UNINITIALIZED == Fls_GblInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                          LucServiceId, FLS_E_UNINIT);

    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }

  /* Check if the driver is busy by servicing another request */
  /* QAC Warning: START Msg(2:3416)-2 */
  if (MEMIF_BUSY == Fls_GenState)
  /* END Msg(2:3416)-2 */
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                          LucServiceId, FLS_E_BUSY);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }

  return (LucReturnValue);
}

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* #if (FLS_DEV_ERROR_DETECT == STD_ON) */

#if (FLS_SUSPEND_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_SuspendPreCheck
**
** Service ID                : NA
**
** Description               : This function checks for whether different
**                             sequences of requests for suspension is to be
**                             allowed or not
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : NA
**
** Input Parameters          : LenRequestedCmd
**
** InOut Parameters          : None
**
** Output Parameters         : Std_ReturnType
**
** Return parameter          : LucReturnValue
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.enDFStatus
**
** Function(s) invoked       : None
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_176 */
/* Implements: AR_PN0072_FR_0045, AR_PN0072_FR_0049 */
FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_SuspendPreCheck
(
  const Fls_CommandType LenRequestedCmd
)
{
  /* Variable to store return variable */
  Std_ReturnType LucReturnValue = E_OK;


  /*
    Following sequences of requests shall be rejected.
    Erase -> Suspend -> Erase
    Write -> Suspend -> Erase
  */
  /* QAC Warning: START Msg(2:3416)-2 */
  if (FLS_TRUE == Fls_GblJobSuspended)
  /* END Msg(2:3416)-2 */
  {
    if (
        (FLS_COMMAND_ERASE  == LenRequestedCmd) &&
        (
          (FLS_COMMAND_ERASE == Fls_GstBackUpVar.enCommand) ||
          (FLS_COMMAND_WRITE == Fls_GstBackUpVar.enCommand)
        )
      )
    {
      LucReturnValue = E_NOT_OK;
    }
    /* Following sequences of requests shall be rejected.
                Write -> Suspend -> Write
                Write -> Suspend -> DmaWrite */
    else if (
              ((FLS_COMMAND_WRITE  == LenRequestedCmd) ||
              (FLS_COMMAND_DMA_WRITE  == LenRequestedCmd)) &&
              (FLS_COMMAND_WRITE == Fls_GstBackUpVar.enCommand)
            )
    {
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* No Action required */
    }
  }
  else
  {
    /* No Action required */
  }

  if (E_NOT_OK == LucReturnValue)
  {
    /* Set request status as rejected */
    Fls_GstVar.enDFStatus = FLS_FCU_ERR_REJECTED;
  }
  else
  {
    /* No Action required */
  }
  return(LucReturnValue);
} /* End of function Fls_SuspendPreCheck */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if (FLS_SUSPEND_API == STD_ON) */

#if ((FLS_INTERRUPT_MODE == STD_ON) && (FLS_SET_MODE_API == STD_ON))

/*******************************************************************************
** Function Name        : Fls_DmaIsr
**
** Service ID           : NA
**
** Description          : This function is an DMA Completer interrupt service
**                        routine for FLS.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : None
**
** Functions invoked    : Fls_EnableFaciEndInt
**
** Registers Used       : None
*******************************************************************************/
#define FLS_START_SEC_CODE_FAST
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */

/* Implements: FLS_ESDD_UD_153 */
/* Implements: AR_PN0072_FR_0047 */
FUNC(void, FLS_FAST_CODE) Fls_DmaIsr(void)
{
  /* Unmask the ICFLENDNM interrupt  */
  Fls_EnableFaciEndInt();
}

#define FLS_STOP_SEC_CODE_FAST
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* (FLS_INTERRUPT_MODE == STD_ON) && (FLS_SET_MODE_API == STD_ON) */


#if ((FLS_SET_MODE_API == STD_ON) &&\
     (FLS_DMA_INSTANCES != FLS_DMA_ZERO))
/*******************************************************************************
** Function Name             : Fls_DmaInit
**
** Service ID                : NA
**
** Description               : This function initializes DMA registers
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GpDmaUnitConfig
**
** Function(s) invoked       : None
**
** Registers Used            : DCSTCm,DCENm,DTCm,DTFRm,DTFRRQCm,DTCTm,DDAm,
**                             DRDAm,DRTCm,DCSTm,DTFRRQm
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
/* Implements: FLS_ESDD_UD_154 */
/* Implements: FLS251 */
/* Implements: SWS_Fls_00251 */
/* Implements: AR_PN0072_FR_0056 */
FUNC(void, FLS_PRIVATE_CODE) Fls_DmaInit(void)
{
  P2CONST(Fls_DmaUnitConfig, AUTOMATIC, FLS_CONFIG_DATA) LpDmaConfig;
  /* Local pointer which holds the base address of DMA channel  */
  P2VAR(volatile DmaReg, AUTOMATIC, FLS_CONFIG_DATA) LpDmaRegisters;
  uint32 LulRegValue;
  /* Local variable to store the index to DMA registers address */
  uint8 LucDmaRegIndex;

  LpDmaConfig = Fls_GpDmaUnitConfig;
  /* Get index to DMA channel base address */
  /* QAC Warning: START Msg(2:2814)-3 */
  LucDmaRegIndex = LpDmaConfig->ucDmaRegIndex;
  /* END Msg(2:2814)-3 */
  /* Store the base address to DMA channel  */
  LpDmaRegisters = Fls_GaaDmaReg_BaseAddress[LucDmaRegIndex];
  /* QAC Warning: START Msg(2:2814)-3 */
  LulRegValue = LpDmaRegisters->ulDCSTC | FLS_DMA_DCST_CLEAR;
   /* END Msg(2:2814)-3 */
  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Disable relevant interrupts to protect this critical section */
  FLS_ENTER_CRITICAL_SECTION(FLS_REGISTER_PROTECTION);
  #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */

  /* Initialize Transfer Status Clear Register */
  FLS_WRITE_REG_ONLY(
                      &LpDmaRegisters->ulDCSTC,
                      LulRegValue
                    )
  /* Check that status register is error free */
  FLS_CHECK_WRITE_VERIFY_INIT (
                                &LpDmaRegisters->ulDCST,
                                FLS_FCU_ZERO,
                                FLS_DMA_DCST_CLEAR,
                                FLS_INIT_SID
                              )

  /* Disable DMA channel */
  FLS_WRITE_REG_AND_MIRROR(
                            &LpDmaRegisters->ulDCEN,
                            FLS_DMA_DCEN_DISABLE,
                            &Fls_GaaRamMirror[RAM_IDX_DCEN]
                          )
  FLS_CHECK_WRITE_VERIFY_INIT (
                                &LpDmaRegisters->ulDCEN,
                                FLS_DMA_DCEN_DISABLE,
                                RAM_MASK_DCEN,
                                FLS_INIT_SID
                              )

  /* initialize the transfer count value to the DMA register */
  FLS_WRITE_REG_ONLY(
                      &LpDmaRegisters->ulDTC,
                      FLS_RESET_DTC
                    )
  FLS_CHECK_WRITE_VERIFY_INIT (
                                &LpDmaRegisters->ulDTC,
                                FLS_RESET_DTC,
                                RAM_MASK_NO_MASK,
                                FLS_INIT_SID
                              )

  /* Load the trigger factor configured for the SGm unit and enable HW trigger*/
  FLS_WRITE_REG_ONLY(
                      &LpDmaRegisters->ulDTFR,
                      (uint32)(LpDmaConfig->usDmaDtfrRegValue)
                    )
  FLS_CHECK_WRITE_VERIFY_INIT (
                                &LpDmaRegisters->ulDTFR,
                                (uint32)(LpDmaConfig->usDmaDtfrRegValue),
                                RAM_MASK_DTFR,
                                FLS_INIT_SID
                              )

  /* Set transfer request clear register*/
  FLS_WRITE_REG_ONLY(
                      &LpDmaRegisters->ulDTFRRQC,
                      FLS_DMA_DRQ_CLEAR
                    )
  FLS_CHECK_WRITE_VERIFY_INIT (
                                &LpDmaRegisters->ulDTFRRQ,
                                FLS_FCU_ZERO,
                                FLS_DMA_DRQ_CLEAR,
                                FLS_INIT_SID
                              )

  /* Load the transfer control register */
  FLS_WRITE_REG_AND_MIRROR(
                            &LpDmaRegisters->ulDTCT,
                            FLS_DMA_DTCT_REG_VALUE,
                            &Fls_GaaRamMirror[RAM_IDX_DTCT]
                          )
  FLS_CHECK_WRITE_VERIFY_INIT (
                                &LpDmaRegisters->ulDTCT,
                                FLS_DMA_DTCT_REG_VALUE,
                                RAM_MASK_DTCT,
                                FLS_INIT_SID
                              )

  /* Set the destination address to FACI command-issuing area */
  FLS_WRITE_REG_ONLY(
                      &LpDmaRegisters->ulDDA,
                      FLS_FCU_DFLASH_CMD_ADD
                    )
  FLS_CHECK_WRITE_VERIFY_INIT (
                                &LpDmaRegisters->ulDDA,
                                FLS_FCU_DFLASH_CMD_ADD,
                                RAM_MASK_NO_MASK,
                                FLS_INIT_SID
                              )

  /* Load the destination address to reload register, it will be always fixed */
  FLS_WRITE_REG_ONLY(
                      &LpDmaRegisters->ulDRDA,
                      FLS_FCU_DFLASH_CMD_ADD
                    )
  FLS_CHECK_WRITE_VERIFY_INIT (
                                &LpDmaRegisters->ulDRDA,
                                FLS_FCU_DFLASH_CMD_ADD,
                                RAM_MASK_NO_MASK,
                                FLS_INIT_SID
                              )

  /* Load Reload transfer count register*/
  FLS_WRITE_REG_ONLY(
                      &LpDmaRegisters->ulDRTC,
                      FLS_DMA_DRTC_REG_VALUE
                    )
  FLS_CHECK_WRITE_VERIFY_INIT (
                                &LpDmaRegisters->ulDRTC,
                                FLS_DMA_DRTC_REG_VALUE,
                                RAM_MASK_NO_MASK,
                                FLS_INIT_SID
                              )
  #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enable relevant interrupts to exit this critical section */
  FLS_EXIT_CRITICAL_SECTION(FLS_REGISTER_PROTECTION);
  #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */

}/* End of function Fls_DmaInit */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-9 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-9 */
#endif /* End of #if ((FLS_SET_MODE_API == STD_ON) &&\
                      (FLS_DMA_INSTANCES != FLS_DMA_ZERO)) */
/* END Msg(2:0380)-8 */

/*******************************************************************************
**                           End of File                                      **
*******************************************************************************/
