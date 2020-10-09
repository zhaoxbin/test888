/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls.c                                                       */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015 - 2018 Renesas Electronics Corporation                   */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains API implementations of Fls Driver Component.            */
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
 * V1.1.0:  04-Dec-2015  : As a part of F1K 4.00.01 release following changes
 *                          are made:
 *                         1. Added the inclusion of Det.h
 *                         2. Updated Fls_Init, Fls_Erase, Fls_Write,
 *                            Fls_Cancel, Fls_GetStatus, Fls_GetJobResult,
 *                            Fls_MainFunction, Fls_Read, Fls_Compare,
 *                            Fls_SetMode, Fls_SetMode, Fls_ReadImmediate
 *                            APIs as per new design as per JIRA Ticket
 *                            ARDAAGA-69
 *                         3. As per JIRA Ticket ARDAAGA-75, Version Info API
 *                            update from macro to function implementation.
 *                         4. Added vendor specific API Fls_Suspend and
 *                            Fls_Resume
 *                         5. Added justification for Msg(4:2984), Msg(4:2982)
 *                         6. Changed the software minor version
 *
 * V1.1.1:  24-Jun-2016  : #ARDAABD-454
 *                         1. Included Fls_Private.h as this in now exporting
 *                            FACI / FCU related internal driver functions.
 *                         #ARDAABD-518
 *                         1. If condition added to check if function
 *                            Fls_Suspend is called for allowed command.
 *                         #ARDAABD-418
 *                         1. Module's main function evaluates module's
 *                            initialized state independently of Det On/Off.
 *
 * V1.1.2:  05-Jul-2016  : Code adaptions regarding save/restore/clear RFxxx bit
 *                         in ICxxx register (ARDAABD-422)
 *
 * V1.1.3:  08-Sep-2016  : Changed parameter type for TargetAddressPtr in
 *                         Fls_Read(ARDAABD-651)
 *
 * V1.2.3:  28-Sep-2016  : #ARDAABD-843
 *                          1. Removed support for
 *                             FLS_AR_HIGHER_VERSION / FLS_AR_LOWER_VERSION
 *
 * V2.0.0:  31-Oct-2016  : #ARDAABD-650
 *                        1. Renamed Fls_FcuSuspendCheck to Fls_SuspendPreCheck
 *                        2. Fls_BlankCheck: added extra Det check
 *                        #ARDAABD-752
 *                        1. For Fls_Cancel API, the backup data is cleared
 *                           only if a backup was made
 *                           (Fls_GblJobSuspended is true).
 *
 * V2.1.0:  11-Nov-2016  : #ARDAABD-732 - Fls_Init, Fls_Write, Fls_Cancel,
 *                           Fls_MainFunction and Fls_CheckHWConsistency
 *                           functions has been updated in order to
 *                           support DMA write job
 *                         #ARDAABD-941 - Fls_Suspend API call is changed to
 *                           Asynchronous and return type to Std_ReturnType.
 *                         #ARDAABD-754 - linked AR 4.0.3 requirements
 *
 * V2.1.1:  11-Nov-2016  : #ARDAABD-732
 *                           fixed compilation problem when DET is OFF
 *
 * V2.1.2:  05-Jan-2017  : #ARDAABD-893
 *                           initialized flag set just if Det ON was removed
 *                           from this ticket
 *                         #ARDAABD-995
 *                           initialized flag set just if Det ON was added
 *                           with this ticket (traceability reason)
 *
 * v2.2.0:  18-Jan-2017  : #ARDAABD-923
 *                         1. Added FLS_ECC_INITCHK_SUPPORT macro
 *
 * V2.2.1:  19-Jan-2017  : #ARDAABD-459
 *                           in Fls_Cancel function, the source code under
 *                           FLS_COMMAND_DMA_WRITE case, has been replaced
 *                           with Fls_DisableDmaChannel function call.
 *
 * V2.2.2:  27-Jan-2017  : #ARDAABD-454
 *                         1. Fls_Private.h renamed to Fls_Private_Fcu.h
 *
 * V2.3.0:  31-Jan-2017  :  #ARDAABD-571
 *                          1. Addded MemMap_Fls vs MemMap.h inclusion based on
 *                             AR revision.
 *                          2. Added Fls_HWCheckConsistency API.
 *                          3. Changes after review.
 *                          4. FPCKAR register no more RAM mirrored.
 *                          5. FCURAME register no more RAM mirrored.
 *
 * V2.4.0:  03 -Feb-2017  :  #ARDAABD-650
 *                           1. Rejected Blank check if target address + length
 *                              not multiple of Fls page size.
 *
 * V2.4.1:  23-Feb-2017  :  #ARDAABD-571
 *                          1. Fixed acceptance findings.
 *                          2. Fixed review findings.
 *                          3. Updated Fls_CheckHWConsistency used registers.
 *
 * V2.4.2:  28-Feb-2017  :  #ARDAABD-1294
 *                          1. DMA's DTC & DSA registers no more Ram mirrored.
 *
 * V2.4.3:  14-Mar-2017  :  #ARDAABD-997
 *                          1. Moved call to timout handler at end of main
 *                             function processing.
 *                          2. Reset the timeout monitoring in Fls_Cancel.
 *                          3. Removed timeout monitoring for Dma Write job.
 *                          4. Added timeout monitoring for Blank check job.
 *
 * V2.4.4:  26-May-2017  :  #ARDAABD-446
 *                          1. Removed call to Fls_InitiateReadJob
 *                          function from the Fls_Read API.
 *                          2. Removed Timeout monitoring for read operation.
 *
 * V2.4.5   1-Jun-2017   :  #ARDAABD-446: The following updates are made after
 *                          review No.096":
 *                          -Removed Fls_ProcessJobResult call from the Fls_Read
 *                          function.
 * V2.4.6   3-Jun-2017   :  #ARDAABD-1199 - Check for alignment to flash page
 *                            boundary has been added in Fls_BlankCheck API.
 * V2.4.7  20-Jul-2017   :  #ARDAABD-1139 - ulDFERSTR register access has been
 *                          changed to ucDFERSTR.
 *                          #ARDAABD-1246 - Removed Firmware copy support.
 *                          #ARDAABD-1368 - If internal error occur during
 *                          cancellation of blank check operation, the driver
 *                          state is set to IDLE.
 * V2.4.8  01-Aug-2017   :  ARDAABD-2196 - FLS_FCU_ERR_INTERNAL check has been
 *                          added in Fls_MainFunction function.
 * V2.4.9  25-Aug-2017   :  #ARDAABD-2151 - Added QAC/MISRA Warnings
 *                          justification. Corrected QAC/MISRA Warning.
 * V2.4.10 25-Sep-2017      ARDAABD-2370: corrected variables naming convention.
 * V2.4.11 11-Oct-2017   :  ARDAABD-2578 - Corrected Fls_BlankCheck SID value.
 * V2.5.0  16-Oct-2017   :  ARDAABD-2552 - Dem_ReportErrorStatus interface has
 *                          been replaced by Det_ReportRuntimeError for AUTOSAR
 *                          version 4.2.2
 * V2.5.1  23-Oct-2017   :  ARDAABD-2645 - FLS_ECC_INITCHK_SUPPORT compiler
 *                          switch has been added for LenECCStatus variable
 *                          declaration and its value check.
 * V2.5.2  22-Jan-2018   :  ARDAABD-2917 - Updated functions header with used
 *                          registers and invoked functions.
 * V2.5.3: 20-Jun-2018   :  Following changes are made:
 *                          1. As part of merging activity, #ARDAABD-3465
 *                             below changes are made(Ref : ARDAABD-2158):
 *                             a. Replaced the usage of 'IMRn' Registers
 *                                with 'ICxxx' registers to avoid unprotected
 *                                Read/Modify/Write access to 'IMR' registers.
 *                                ARDAABD-2158.
 *                             b. Misra warning Tag for Message Msg(4:0303)
 *                                has been added.
 *                             c. Inserted a one space character after
 *                                'if' statement.
 *                             d. Copyright information has been updated.
 *                          2. As part of #ARDAABD-3633, the list of
 *                             registers in the function banner of APIs
 *                             Fls_CheckHWConsistency and Fls_Erase is updated.
 *                          3. As part of ARDAABD-3663, the nested critical
 *                             sections in Fls_Cancel API and Fls_ReadImmediate
 *                             API is split.
 *                          4. As per ARDAABD-3853, traceability has been
 *                             improved.
 * V2.5.4: 22-May-2018  :  As part of ARDAABD-3707, Following changes are made:
 *                          1.Add RH850_DUMMY_READ_SYNCP(16, ICP0) to fix the fault
 *                             synchronization at the timing when control shifts from MCAL to application
 * V2.5.5: 05-Oct-2018  :  Following changes are done : 
 *                          1. As part of ARDAABD-3707, ICP0 usage error
 *                             modified RH850_DUMMY_READ_SYNCP(16, ICP0)  to 
 *                             RH850_DUMMY_READ_SYNCP(16, &(ICP0))
 * V2.5.6: 19-Oct-2018   : As part of ARDAABD-3707
 *                           Remove the RH850_DUMMY_READ_SYNCP Marco
 */
/******************************************************************************/
/*******************************************************************************
**                      General Traceability Section                          **
*******************************************************************************/
/* Implements: EAAR_PN0034_FR_0045, EAAR_PN0034_NR_0007, EAAR_PN0034_FR_0052  */
/* Implements: EAAR_PN0034_NR_0062, EAAR_PN0034_FR_0039, EAAR_PN0034_NR_0066  */
/* Implements: EAAR_PN0034_NR_0042, EAAR_PN0034_NR_0046, EAAR_PN0034_NR_0048  */
/* Implements: EAAR_PN0034_FR_0037, EAAR_PN0034_FR_0063, EAAR_PN0034_NR_0029  */
/* Implements: EAAR_PN0034_FR_0043, EAAR_PN0034_NR_0061, EAAR_PN0034_NR_0001  */
/* Implements: EAAR_PN0034_NR_0044, EAAR_PN0034_NR_0015, EAAR_PN0034_FR_0004  */
/* Implements: EAAR_PN0034_NR_0020, EAAR_PN0034_NR_0073, EAAR_PN0034_NR_0075  */
/* Implements: EAAR_PN0034_FR_0066, EAAR_PN0034_NR_0016, EAAR_PN0034_NR_0025  */
/* Implements: EAAR_PN0034_FR_0046, EAAR_PN0034_NR_0023, EAAR_PN0034_FR_0002  */
/* Implements: EAAR_PN0034_FR_0025, EAAR_PN0034_FR_0020, EAAR_PN0034_FR_0026  */
/* Implements: EAAR_PN0034_NR_0006, EAAR_PN0034_NR_0012, EAAR_PN0034_FR_0041  */
/* Implements: EAAR_PN0034_FR_0080, EAAR_PN0034_NR_0054, EAAR_PN0034_FR_0065  */
/* Implements: EAAR_PN0034_FR_0081, EAAR_PN0034_FR_0018, EAAR_PN0034_FR_0006  */
/* Implements: EAAR_PN0034_NR_0063, EAAR_PN0034_FR_0060, EAAR_PN0034_NR_0045  */
/* Implements: EAAR_PN0034_FR_0008, EAAR_PN0034_NR_0043, EAAR_PN0034_NR_0018  */
/* Implements: EAAR_PN0034_NR_0002, EAAR_PN0034_FR_0056, EAAR_PN0034_NR_0019  */
/* Implements: EAAR_PN0034_NR_0069, EAAR_PN0034_FR_0054, EAAR_PN0034_FR_0038  */
/* Implements: EAAR_PN0034_FR_0055, EAAR_PN0034_NR_0036, EAAR_PN0034_NR_0071  */
/* Implements: EAAR_PN0034_FR_0005, EAAR_PN0034_NR_0008, EAAR_PN0034_FR_0023  */
/* Implements: EAAR_PN0034_NR_0056, EAAR_PN0034_FR_0042, EAAR_PN0034_FR_0048  */
/* Implements: EAAR_PN0034_FR_0001, EAAR_PN0034_NR_0010, EAAR_PN0034_FR_0019  */
/* Implements: EAAR_PN0034_NR_0028, EAAR_PN0034_NR_0030, EAAR_PN0034_NR_0037  */
/* Implements: EAAR_PN0034_NR_0024, EAAR_PN0034_FR_0007, EAAR_PN0034_NR_0006  */
/* Implements: EAAR_PN0034_FR_0058, EAAR_PN0034_FR_0024, EAAR_PN0034_NR_0039  */
/* Implements: EAAR_PN0034_NR_0021, EAAR_PN0034_FR_0062, EAAR_PN0034_FR_0083  */
/* Implements: EAAR_PN0034_NR_0026, EAAR_PN0034_FR_0053, EAAR_PN0034_FR_0047  */
/* Implements: EAAR_PN0034_NR_0064, EAAR_PN0034_NR_0022, EAAR_PN0034_NR_0011  */
/* Implements: EAAR_PN0034_FR_0068, EAAR_PN0034_FR_0067, EAAR_PN0034_FR_0003  */
/* Implements: EAAR_PN0034_FSR_0001, EAAR_PN0034_FSR_0002                     */
/* Implements: EAAR_PN0034_FSR_0003, EAAR_PN0034_FSR_0004                     */
/* Implements: EAAR_PN0034_FSR_0005, EAAR_PN0034_FSR_0006                     */
/* Implements: EAAR_PN0034_FSR_0007, EAAR_PN0034_FSR_0008                     */
/* Implements: EAAR_PN0034_FSR_0009, EAAR_PN0034_FSR_0010                     */
/* Implements: EAAR_PN0034_FSR_0011, EAAR_PN0034_FSR_0012                     */
/* Implements: EAAR_PN0034_FSR_0013, AR_PN0072_FR_0002                        */
/* Implements: AR_PN0072_FR_0055                                              */
/* Implements: FLS_ESDD_UD_003, FLS_ESDD_UD_008, FLS_ESDD_UD_092              */
/* Implements: FLS_ESDD_UD_010, FLS_ESDD_UD_025                               */
/* Implements: FLS_ESDD_UD_094, FLS_ESDD_UD_110, FLS_ESDD_UD_240              */
/* Implements: FLS107,FLS159, FLS179, FLS308, FLS309, FLS248, FLS303, FLS205  */
/* Implements: FLS320, FLS321, SWS_Fls_00309  */
/* Implements: FLS006, FLS160, SWS_Fls_00107, SWS_Fls_00205, FLS304           */
/* Implements: SWS_Fls_00248, SWS_Fls_00308           */


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
//#include "Iocommon_Defines.h"
/* Included for module version information and other types declarations */
#include "Fls.h"
/* Included for the macro declaration of supervisor mode(SV) write enabled
    Registers ICxxx */
//#include "rh850_Types.h"
/* Included prototypes for internal functions of Flash Wrapper Component */
#include "Fls_Internal.h"
/* Included prototypes for private functions of Flash Wrapper Component  */
#include "Fls_Private_Fcu.h"
/* Included for RAM variable declarations */
#include "Fls_Ram.h"
#if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
/* Included for declaration of the function Dem_ReportErrorStatus() */
#include "Dem.h"
#endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
/* Included for Prototype Declaration for Callback Notification functions */
#include "Fls_Cbk.h"
/* Implements: FLS_ESDD_UD_036 */
#if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Fls.h"
#endif
/* Included for the declaration of Det_ReportError, Det_ReportRuntimeError */
#include "Det.h"
/* Included for macro declarations for wv and ram mirror */
#include "Fls_RegWrite.h"
#include "hal.h"
#include "flash_driver.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR release version information */
#define FLS_C_AR_RELEASE_MAJOR_VERSION     FLS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLS_C_AR_RELEASE_MINOR_VERSION     FLS_AR_RELEASE_MINOR_VERSION_VALUE
#define FLS_C_AR_RELEASE_REVISION_VERSION  FLS_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FLS_C_SW_MAJOR_VERSION      1
#define FLS_C_SW_MINOR_VERSION      1

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (FLS_AR_RELEASE_MAJOR_VERSION != FLS_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fls.c : Mismatch in Release Major Version"
#endif

#if (FLS_AR_RELEASE_MINOR_VERSION != FLS_C_AR_RELEASE_MINOR_VERSION)
  #error "Fls.c : Mismatch in Release Minor Version"
#endif

#if (FLS_AR_RELEASE_REVISION_VERSION != FLS_C_AR_RELEASE_REVISION_VERSION)
  #error "Fls.c : Mismatch in Release Revision Version"
#endif

#if (FLS_SW_MAJOR_VERSION != FLS_C_SW_MAJOR_VERSION)
  #error "Fls.c : Mismatch in Software Major Version"
#endif

#if (FLS_SW_MINOR_VERSION != FLS_C_SW_MINOR_VERSION)
  #error "Fls.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                       MISRA C Rule Violations                              **
*******************************************************************************/

/******************************************************************************/
/* 1. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:4397) An expression which is the result of a ~ or <<    */
/*                 operation has not been cast to its essential type.         */
/* Rule          : MISRA-C:2004 Rule 10.5                                     */
/* Justification : The expression has no reliance on the effects of integral  */
/*                 promotion.                                                 */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:4397)-1 and                           */
/*                 END Msg(4:4397)-1 tags in the code.                        */
/******************************************************************************/
/* 2. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0310) Casting to different object pointer type.         */
/* Rule          : MISRA-C:2004 Rule 11.4                                     */
/* Justification : This is to get the value to pointer.                       */
/* Verification  : However, this part of the code is verified  manually and   */
/*                 it is not having any impact.                               */
/* Reference     : Look for START Msg(4:0310)-2 and                           */
/*                 END Msg(4:0310)-2 tags in the code.                        */

/******************************************************************************/
/* 3. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0306) [I] Cast between a pointer to object and an       */
/*                 integral type.                                             */
/* Rule          : MISRA-C:2004 Rule 3.1 and 11.3                             */
/* Justification : The input addresses specified by the pointers are converted*/
/*                 to addresses for storing into the registers and for        */
/*                 reading purposes.                                          */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:0306)-3 and                           */
/*                 END Msg(4:0306)-3 tags in the code.                        */
/******************************************************************************/
/* 5.  MISRA C RULE VIOLATION:                                                */
/* Message       : (2:0832) Macro substitution in #include preprocessing      */
/*                 directive.                                                 */
/* Rule          : No MISRA-C:2004 Rule                                       */
/* Justification : Required to optimize MemMap inclusion because of ASR403    */
/*                 and ASR422 support.                                        */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:0832)-5 and                           */
/*                 END Msg(2:0832)-5 tags in the code.                        */
/******************************************************************************/
/* 6. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:3415)Right hand operand of '&&' or '||' is an           */
/*                 expression with possible side effects.                     */
/* Rule          : MISRA-C:2004 Rule 12.4                                     */
/* Justification : The left hand operand of '&&' is not always false and left */
/*                 hand operand of '||' is not always true.                   */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:3415)-6 and END Msg(4:3415)-6 tags    */
/*                 in the code.                                               */
/******************************************************************************/
/* 7. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:2003)The preceding 'switch' clause is not empty and does*/
/*                 not end with a 'jump' statement. Execution will fall       */
/*                 through.                                                   */
/* Rule          : MISRA-C:2004 Rule                                          */
/* Justification : Intended fall through made in order to keep cleaner code   */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:2003)-7 and END Msg(4:2003)-7 tags    */
/*                 in the code.                                               */
/******************************************************************************/
/* 8. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:3673)The object addressed by the pointer parameter      */
/*                 is not modified and so the pointer could be of type        */
/*                 'pointer to const'.                                        */
/* Rule          : MISRA-C:2004 Rule 16.7                                     */
/* Justification : pointer variable is used to modify the value at the address*/
/*                 so the pointer cannot be declared as 'pointer to const'    */
/*                 type.                                                      */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:3673)-8 and END Msg(4:3673)-8 tags    */
/*                 in the code.                                               */
/******************************************************************************/
/* 9. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0303) [I] Cast between a pointer to volatile object     */
/*                 and an integral type.                                      */
/* Rule          : MISRA-C:2004 Rule 3.1 and 11.3                             */
/* Justification : This macro is used to write or read values from hardware   */
/*                 addresses.                                                 */
/* Verification  : However, this part of the code is verified manually and it */
/*                 is not having any impact.                                  */
/* Reference     : Look for START Msg(4:0303)-9 and                           */
/*                 END Msg(4:0303)-9 tags in the code.                        */
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
/* Message       : (2:3892) The result of this cast is implicitly converted to*/
/*                 another type.                                              */
/*                 REFERENCE - ISO:C90-6.3.2.1 Semantics                      */
/* Justification : This is to get the value to pointer.                       */
/* Verification  : However, this part of the code is verified  manually and   */
/*                 it is not having any impact.                               */
/* Reference     : Look for START Msg(2:3892)-4 and END Msg(2:3892)-4 tags in */
/*                 the code.                                                  */
/******************************************************************************/
/******************************************************************************/
/* 5. QAC Warning:                                                            */
/* Message       : (2:2016) This 'switch' statement 'default' clause is empty.*/
/* Justification : No action is required for default statements. Hence it is  */
/*                 left empty.                                                */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:2016)-5 and END Msg(2:2016)-5 tags in */
/*                 the code.                                                  */
/******************************************************************************/
/* 6. QAC Warning:                                                            */
/* Message       : (2:3204) This variable is only set once and so it could    */
/*                 be declared with the 'const' qualifier.                    */
/* Justification : These variables cannot be declared with 'const' qualifier  */
/*                 since these variables are subjected to change based on     */
/*                 DET configuration                                          */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any safety impact.                              */
/* Reference     : Look for START Msg(2:3204)-6 and                           */
/*                 END Msg(2:3204)-6 tags in the code.                        */
/******************************************************************************/
/**                      Function Definitions                                **/
/******************************************************************************/

/*******************************************************************************
** Function Name             : Fls_Init
**
** Service ID                : 0x00
**
** Description               : This API performs the initialization of the FLS
**                             Driver Component.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : ConfigPtr
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GenState, Fls_GenJobResult,
**                             Fls_GstVar.enCommand, Fls_GpConfigPtr,
**                             Fls_GstVar.ulRequestedLength,
**                             Fls_GstVar.ulCurrentLength,
**                             Fls_GblFlashEnable, Fls_GblInitStatus,
**                             Fls_GstVar.ucOffset,
**                             Fls_GstVar.enReadType,Fls_GenCurrentMode
**                             Fls_GblVerifyCompletedJob, Fls_GpDmaUnitConfig
**
** Function(s) invoked       : Det_ReportError,Fls_FcuInit,Fls_PreFcuInitCheck,
**                             Fls_SetFHVE,Fls_ClearBackUpData, Fls_DmaInit,
**                             Det_ReportRuntimeError
**
** Registers Used            : FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,FPCKAR,
**                             DFECCCTL,DFERRINT,DFTSTCTL,DCSTCm,DCENm,DTCm,
**                             DTFRm,DTFRRQCm,DTCTm,DDAm,DRDAm,DRTCm,DCSTm,
**                             DTFRRQm
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
/* Implements: FLS_ESDD_UD_062, FLS_ESDD_UD_108, FLS_ESDD_UD_051 */
/* Implements: FLS_ESDD_UD_149, FLS_ESDD_UD_012 */
/* Implements: FLS249, FLS086, FLS015, FLS048 */
/* Implements: SWS_Fls_00249, SWS_Fls_00086, SWS_Fls_00015, SWS_Fls_00048 */
/* Implements: AR_PN0072_FR_0010, AR_PN0072_FR_0002, EAAR_PN0034_FR_0016 */
FUNC(void, FLS_PUBLIC_CODE) Fls_Init
(
  /* QAC Warning: START Msg(2:3227)-1*/
  P2CONST(Fls_ConfigType, AUTOMATIC, FLS_APPL_CONST) ConfigPtr
  /* END Msg(2:3227)-1*/
)
{
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold the return value */
  Std_ReturnType LucReturnValue = E_OK;
  #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  /* Local variable to hold the ECC status during Fls_PreFcuInitCheck() */
  #if (STD_ON == FLS_ECC_INITCHK_SUPPORT)
  Fls_FcuStatusType LenECCStatus;
  #endif /* (STD_ON == FLS_ECC_INITCHK_SUPPORT) */


} /* End of API Fls_Init */

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
/*******************************************************************************
** Function Name             : Fls_Erase
**
** Service ID                : 0x01
**
** Description               : This API will erase the one or more complete
**                             flash sectors.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : TargetAddress, Length
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : Std_ReturnType
**                             E_OK: If Erase command has been accepted.
**                             E_NOT_OK: If Erase command has not been accepted.
**
** Preconditions             : Component must be initialized using Fls_Init().
**
** Global Variables Used     : Fls_GblInitStatus, Fls_GenState,
**                             Fls_GstVar.enCommand, Fls_GenJobResult,
**                             Fls_GstVar.ulJobStartAddress,Fls_GpConfigPtr
**                             Fls_GstVar.ulJobEndAddress,
**                             Fls_GstVar.ulRequestedLength,
**                             Fls_GstVar.ulSrcDestAddress
**
** Function(s) invoked       : Det_ReportError,Fls_InitiateEraseJob
**                             Fls_ProcessJobResult,Fls_GetIntReq
**                             Fls_ClearIntReq,Fls_SuspendPreCheck
**
** Registers Used            : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,
**                             FASTAT,DCENm,DTCTm,ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
/* Implements: FLS_ESDD_UD_063, FLS_ESDD_UD_093, FLS_ESDD_UD_095 */
/* Implements: FLS_ESDD_UD_087 */
/* Implements: FLS250, FLS218, FLS327, FLS328, FLS329, FLS330, FLS220, FLS221 */
/* Implements: FLS020, FLS021, FLS023, FLS065, FLS145, FLS209, FLS001 */
/* Implements: SWS_Fls_00250, SWS_Fls_00218, SWS_Fls_00327, SWS_Fls_00328 */
/* Implements: SWS_Fls_00329, SWS_Fls_00330, SWS_Fls_00220, SWS_Fls_00221 */
/* Implements: SWS_Fls_00020, SWS_Fls_00021, SWS_Fls_00065, SWS_Fls_00023 */
/* Implements: SWS_Fls_00145, SWS_Fls_00209, SWS_Fls_00001 */
/* Implements: AR_PN0072_FR_0005 */
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Erase
(
  Fls_AddressType TargetAddress,
  Fls_LengthType Length
)
{
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;



  return(LucReturnValue);
}/* End of API Fls_Erase */

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
/*******************************************************************************
** Function Name             : Fls_Write
**
** Service ID                : 0x02
**
** Description               : This API performs programming of one or more
**                             complete flash pages of the flash device. The
**                             data from input buffer (source address) is
**                             written to the flash pointed by the target offset
**                             .The target address must be aligned to flash page
**                             boundary.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : TargetAddress, SourceAddressPtr, Length
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : Std_ReturnType
**                             E_OK: if Write command has been accepted.
**                             E_NOT_OK: if Write command has not been accepted.
**
** Preconditions             : Component must be initialized using Fls_Init().
**
** Global Variables Used     : Fls_GblInitStatus,Fls_GpConfigPtr
**                             Fls_GstVar.enCommand, Fls_GenState,
**                             Fls_GenJobResult,Fls_GstVar.ulCurrentLength,
**                             Fls_GstVar.pBufferAddress,
**                             Fls_GstVar.ulRequestedLength
**                             Fls_GstVar.ulJobStartAddress
**                             Fls_GstVar.ulJobEndAddress
**
** Function(s) invoked       : Det_ReportError,Fls_ProcessJobResult,
**                             Fls_InitiateWriteJob,Fls_GetIntReq,
**                             Fls_ClearIntReq,Fls_SuspendPreCheck,
**                             Fls_InitiateDmaWriteJob
**
** Registers Used            : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,
**                             FASTAT,DCSTCm,DCENm,DTCm,DTCTm,
**                             ICFLENDNM,DSAm
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
extern flash_ssd_config_t pSSDConfig;
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
/* Implements: FLS_ESDD_UD_064, FLS_ESDD_UD_006 */
/* Implements: FLS251, FLS223, FLS331, FLS332, FLS333, FLS334, FLS225, FLS226 */
/* Implements: FLS026, FLS027, FLS066, FLS030, FLS157, FLS146, FLS001 */
/* Implements: SWS_Fls_00251, SWS_Fls_00223, SWS_Fls_00331, SWS_Fls_00332 */
/* Implements: SWS_Fls_00333, SWS_Fls_00334, SWS_Fls_00225, SWS_Fls_00226 */
/* Implements: SWS_Fls_00026, SWS_Fls_00027, SWS_Fls_00066, SWS_Fls_00030 */
/* Implements: SWS_Fls_00157, SWS_Fls_00146, SWS_Fls_00001 */
/* Implements: AR_PN0072_FR_0006, AR_PN0072_FR_0056 */
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Write
(
  /* QAC Warning: START Msg(2:3227)-1*/
  Fls_AddressType                           TargetAddress,
  P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) SourceAddressPtr,
  Fls_LengthType                            Length
  /* END Msg(2:3227)-1*/
)
{
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;

 // FLASH_DRV_EEEWrite(&pSSDConfig, TargetAddress, Length, SourceAddressPtr);
  LucReturnValue=E_OK;
  return(LucReturnValue);
}/* End of API Fls_Write */

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
/* Implements: FLS_ESDD_UD_029 */
#if (FLS_CANCEL_API == STD_ON)
/*******************************************************************************
** Function Name              : Fls_Cancel
**
** Service ID                 : 0x03
**
** Description                : This API cancels the on going job. The driver
**                              state is set to MEMIF_IDLE and the job result to
**                              MEMIF_JOB_CANCELED if a job is currently
**                              being processed.
**
** Sync/Async                 : Synchronous
**
** Reentrancy                 : Non Reentrant
**
** Input Parameters           : None
**
** InOut Parameters           : None
**
** Output Parameters          : None
**
** Return parameter           : None
**
** Preconditions              : Component must be initialized using Fls_Init().
**
** Global Variables Used      : Fls_GblInitStatus,Fls_GstVar.enCommand,
**                              Fls_GenJobResult,Fls_GblJobSuspended
**                              Fls_GenState, Fls_GpConfigPtr
**
** Function(s) invoked        : Det_ReportError,Fls_ProcessCancel
**                              Fls_GpConfigPtr->pJobErrorNotificationPointer,
**                              Fls_RestoreIntReq,Fls_ClearBackUpData,
**                              Fls_DisableDmaChannel
**
** Registers Used             : DTCTm,DCENm,FSADDR,FEADDR,FSTATR,
**                              FENTRYR,FASTAT
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
/* Implements: FLS_ESDD_UD_065 */
/* Implements: FLS252, FLS229, FLS230, FLS335, FLS336, FLS033, FLS147, FLS183 */
/* Implements: FLS356 */
/* Implements: SWS_Fls_00252, SWS_Fls_00229, SWS_Fls_00230, SWS_Fls_00335 */
/* Implements: SWS_Fls_00336, SWS_Fls_00033, SWS_Fls_00147, SWS_Fls_00183 */
/* Implements: SWS_Fls_00356, FLS285 */
/* Implements: AR_PN0072_FR_0011 */
FUNC(void, FLS_PUBLIC_CODE)Fls_Cancel(void)
{
  /* Local variable to hold the FLS command to be cancelled */
  Fls_CommandType LenCmdToCancel;


} /* End of API Fls_Cancel */
#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
#endif /* End of #if (FLS_CANCEL_API == STD_ON) */

#if (FLS_GET_STATUS_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_GetStatus
**
** Service ID                : 0x04
**
** Description               : This API Returns the FLS module state
**                             synchronously.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_StatusType
**
** Preconditions             : Component must be initialized using Fls_Init().
**
** Global Variables Used     : Fls_GblInitStatus,Fls_GenState
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */

/* Implements: FLS_ESDD_UD_066, FLS_ESDD_UD_032 */
/* Implements: FLS253, FLS034, FLS184, FLS357, FLS290_Conf */
/* Implements: SWS_Fls_00253, SWS_Fls_00034, SWS_Fls_00184, ECUC_Fls_00290 */
/* Implements: AR_PN0072_FR_0012 */
FUNC(MemIf_StatusType, FLS_PUBLIC_CODE)Fls_GetStatus(void)
{
  /* Local variable to hold the driver status */
  MemIf_StatusType LenStatus;
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;
  #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  /* Set local variable with the default return value */
  LenStatus = MEMIF_UNINIT;
  /* Set local variable with the default DET return value */
  LucReturnValue = E_OK;
  /* Check if the module is initialized */
  if (FLS_UNINITIALIZED == Fls_GblInitStatus)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                            FLS_GET_STATUS_SID, FLS_E_UNINIT);
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  /* Check whether any error reported to DET */
  if (LucReturnValue == E_OK)
  #endif  /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Read the current state of the driver */
    LenStatus = Fls_GenState;
  }
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action required */
  }
  #endif  /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */

  LenStatus= MEMIF_IDLE;
  /* return the current state of the driver */
  return(LenStatus);
} /* End of API Fls_GetStatus */

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
#endif /* End of #if (FLS_GET_STATUS_API == STD_ON) */

#if (FLS_GET_JOB_RESULT_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_GetJobResult
**
** Service ID                : 0x05
**
** Description               : This API returns the result of the last job.
**                             All erase, write, read and compare jobs share the
**                             same job result. Every new job accepted by the
**                             flash driver  overwrites the job result with
**                             MEMIF_JOB_PENDING.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemIf_JobResultType
**
** Preconditions             : Component must be initialized using Fls_Init().
**
** Global Variables Used     : Fls_GblInitStatus, Fls_GenJobResult
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */

/* Implements: FLS_ESDD_UD_067, FLS_ESDD_UD_033 */
/* Implements: FLS254, FLS035, FLS036, FLS185, FLS358 */
/* Implements: SWS_Fls_00254, SWS_Fls_00035, SWS_Fls_00036, SWS_Fls_00185 */
/* Implements: SWS_Fls_00358 */
/* Implements: AR_PN0072_FR_0013 */
FUNC(MemIf_JobResultType, FLS_PUBLIC_CODE)Fls_GetJobResult(void)
{
  /* Local variable to hold the job result */
  MemIf_JobResultType LenJobResult;


  {
    /* Read the job status */
    LenJobResult = MEMIF_JOB_OK;
  }

  /* Return the job result */
  return(LenJobResult);
} /* End of API Fls_GetJobResult */
#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
#endif /* End of #if (FLS_GET_JOB_RESULT_API == STD_ON)*/

/*******************************************************************************
** Function Name             : Fls_MainFunction
**
** Service ID                : 0x06
**
** Description               : This API performs the job processing of erase,
**                             write, read and compare jobs. This API is called
**                             cyclically until the job is processed completely.
**
** Sync/Async                : NA
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : Component must be initialized using Fls_Init().
**
** Global Variables Used     : Fls_GblInitStatus,Fls_GstVar.enCommand,
**                             Fls_GenState,Fls_GstVar.enDFStatus,
**                             Fls_GblTimeOutMonitor
**
** Function(s) invoked       : Det_ReportError, Fls_MainErase, Fls_MainWrite
**                             Fls_MainBlankCheck, Fls_MainRead, Fls_MainCompare
**                             Fls_MainReadImm, Fls_TimeOutCheckAndProcessing,
**                             Fls_FcuCheckJobStatus, Fls_ProcessJobResult
**
** Registers Used            : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,
**                             DFERRINT,DCSTCm,DCENm,DTCTm,DCSTm,FBCSTAT,
**                             ICFLENDNM,DFERSTC,DFERSTR
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */

/* Implements: FLS_ESDD_UD_072*/
/* Implements: FLS255, FLS037, FLS038, FLS039, FLS040, FLS104, FLS105, FLS106 */
/* Implements: FLS154, FLS200, FLS022, FLS055, FLS056, FLS345, FLS346, FLS235 */
/* Implements: FLS272, FLS359, FLS360, FLS362, FLS117, FLS196 */
/* Implements: SWS_Fls_00255, SWS_Fls_00037, SWS_Fls_00038, SWS_Fls_00039 */
/* Implements: SWS_Fls_00040, SWS_Fls_00104, SWS_Fls_00105, SWS_Fls_00106 */
/* Implements: SWS_Fls_00154, SWS_Fls_00200, SWS_Fls_00022, SWS_Fls_00055 */
/* Implements: SWS_Fls_00056, SWS_Fls_00345, SWS_Fls_00346, SWS_Fls_00235 */
/* Implements: SWS_Fls_00272, SWS_Fls_00359, SWS_Fls_00360, SWS_Fls_00362 */
/* Implements: SWS_Fls_00117, SWS_Fls_00196 */
/* Implements: AR_PN0072_FR_0015, AR_PN0072_FR_0021 */
FUNC(void, FLS_PUBLIC_CODE)Fls_MainFunction(void)
{
  #if ((FLS_SET_MODE_API == STD_ON) &&\
       (FLS_INTERRUPT_MODE == STD_ON) &&\
       (FLS_DMA_INSTANCES != FLS_DMA_ZERO))
  /* Variable to store DF Status*/
  Fls_FcuStatusType LenStatus;
  #endif


} /* End of API Fls_MainFunction */

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
/*******************************************************************************
** Function Name             : Fls_Read
**
** Service ID                : 0x07
**
** Description               : This API performs the reading of the flash
**                             memory.The data from flash memory
**                             (source address) is read to the data buffer
**                             (Target address) of the application.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : SourceAddress, Length
**
** InOut Parameters          : None
**
** Output Parameters         : TargetAddressPtr
**
** Return parameter          : Std_ReturnType
**                             E_OK: if Read command has been accepted.
**                             E_NOT_OK: if Read command has not been accepted.
**
** Preconditions             : Component must be initialized using Fls_Init().
**
** Global Variables Used     : Fls_GblInitStatus,Fls_GstVar.pTempBufferAddress,
**                             Fls_GstVar.ulReadAddress,
**                             Fls_GstVar.pBufferAddress, Fls_GulTempBuffer
**                             Fls_GstVar.ulRequestedLength,
**                             Fls_GstVar.ulCurrentLength,
**                             Fls_GstVar.enCommand, Fls_GenState,
**                             Fls_GenJobResult,Fls_GstVar.ucOffset
**
**  Function(s) invoked      : Det_ReportError,Fls_DetErrorCheck,Fls_SetFHVE,
**                             Fls_GetIntReq,Fls_ClearIntReq
**
** Registers Used            : FHVE3,FHVE15,ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */

/* Implements: FLS_ESDD_UD_068, FLS_ESDD_UD_006 */
/* Implements: FLS256, FLS236, FLS337, FLS338, FLS339, FLS340, FLS238, FLS239 */
/* Implements: FLS097, FLS098, FLS099, FLS100, FLS158, FLS240, FLS209, FLS361 */
/* Implements: FLS269 */
/* Implements: SWS_Fls_00256, SWS_Fls_00236, SWS_Fls_00337, SWS_Fls_00338 */
/* Implements: SWS_Fls_00339, SWS_Fls_00340, SWS_Fls_00238, SWS_Fls_00239 */
/* Implements: SWS_Fls_00097, SWS_Fls_00098, SWS_Fls_00099, SWS_Fls_00100 */
/* Implements: SWS_Fls_00158, SWS_Fls_00240, SWS_Fls_00209, SWS_Fls_00361 */
/* Implements: SWS_Fls_00269 */
/* Implements: AR_PN0072_FR_0007, AR_PN0072_FR_0043, AR_PN0072_FR_0004 */
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Read
(
  /* QAC Warning: START Msg(2:3227)-1*/
  /* MISRA Warning: START Msg(4:3673)-8 */
  Fls_AddressType                         SourceAddress,
  P2VAR(uint8, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
  Fls_LengthType                          Length
  /* END Msg(2:3227)-1*/
  /* END Msg(4:3673)-8 */
)
{
  /* Local variable to hold the DET return value */
  /* QAC Warning: START Msg(2:3204)-6 */
  Std_ReturnType LucReturnValue;
//  HAL_ReadEEPROMMemory(TargetAddressPtr,SourceAddress, Length);
  LucReturnValue=E_OK;
 return(LucReturnValue);

} /* End of API Fls_Read */
#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
/* Implements: FLS_ESDD_UD_030 */
#if (FLS_COMPARE_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_Compare
**
** Service ID                : 0x08
**
** Description               : This API Fls_Compare shall compare the contents
**                             of an area of flash memory with that of an
**                             application data buffer.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : SourceAddress, TargetAddressPtr, Length
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : Std_ReturnType
**                             E_OK: if Compare command has been accepted.
**                             E_NOT_OK: if Compare command has not been
**                             accepted.
**
** Preconditions             : Component must be initialized using Fls_Init().
**
** Global Variables Used     : Fls_GblInitStatus, Fls_GenState,
**                             Fls_GstVar.ulSrcDestAddress,
**                             Fls_GstVar.pBufferAddress, Fls_GulTempBuffer,
**                             Fls_GstVar.ulRequestedLength,
**                             Fls_GstVar.ulCurrentLength,
**                             Fls_GstVar.enCommand,Fls_GenJobResult,
**                             Fls_GstVar.ucOffset,
**                             Fls_GstVar.pTempBufferAddress
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */

/* Implements: FLS_ESDD_UD_069*/
/* Implements: FLS257, FLS241, FLS341, FLS342, FLS343, FLS344, FLS243, FLS244 */
/* Implements: FLS150, FLS151, FLS152, FLS153, FLS273, FLS186, FLS209, FLS318 */
/* Implements: SWS_Fls_00257, SWS_Fls_00241, SWS_Fls_00341, SWS_Fls_00342 */
/* Implements: SWS_Fls_00343, SWS_Fls_00344, SWS_Fls_00243, SWS_Fls_00244 */
/* Implements: SWS_Fls_00150, SWS_Fls_00151, SWS_Fls_00152, SWS_Fls_00153 */
/* Implements: SWS_Fls_00273, SWS_Fls_00186, SWS_Fls_00209, SWS_Fls_00318 */
/* Implements: AR_PN0072_FR_0014, AR_PN0072_FR_0043, ECUC_Fls_00286, FLS286 */
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Compare
(
  /* QAC Warning: START Msg(2:3227)-1*/
  Fls_AddressType                           SourceAddress,
  P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
  Fls_LengthType                            Length
  /* END Msg(2:3227)-1*/
)
{
  /* Local variable to hold the DET return value */
  /* QAC Warning: START Msg(2:3204)-6 */
  Std_ReturnType LucReturnValue;
  /* END Msg(2:3204)-6 */

  return(LucReturnValue);
} /* End of API Fls_Compare */

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
#endif /* End of #if (FLS_COMPARE_API == STD_ON) */

/* Implements: Fls187, SWS_Fls_00187 */
#if (FLS_SET_MODE_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_SetMode
**
** Service ID                : 0x09
**
** Description               : This API sets the flash driver operation mode.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : Mode
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GblInitStatus,Fls_GenState,Fls_GenCurrentMode
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */

/* Implements: FLS_ESDD_UD_070 */
/* Implements: FLS258, FLS155, FLS156, FLS187 */
/* Implements: SWS_Fls_00258, SWS_Fls_00155, SWS_Fls_00156, SWS_Fls_00187 */
/* Implements: AR_PN0072_FR_0020, AR_PN0072_FR_0056*/
/* QAC Warning: START Msg(2:3227)-1*/
FUNC(void, FLS_PUBLIC_CODE) Fls_SetMode(MemIf_ModeType LenMode)
/* END Msg(2:3227)-1*/
{
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;
  /* Implements: Fls156, SWS_Fls_00156 */
  /* Invoking function to check whether driver is initialised/busy */
  LucReturnValue = Fls_DetErrorCheck(FLS_SET_MODE_SID);
  /* Set the Mode if no DET is reported */
  if (E_OK == LucReturnValue)
  #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Implements: Fls155, SWS_Fls_00155 */
    Fls_GenCurrentMode = LenMode;
  }
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action required */
  }
  #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
}/* End of API Fls_SetMode */

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
#endif /* End of #if (FLS_SET_MODE_API == STD_ON) */

#if (FLS_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_GetVersionInfo
**
** Service ID                : 0x10
**
** Description               : This API returns the version information of
**                             this module.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : VersioninfoPtr - Pointer to where to store the
**                             version information of this module.
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
*******************************************************************************/
/* Implements EAAR_PN0034_FR_0051, FLS_ESDD_UD_028 */
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */

/* Implements: FLS_ESDD_UD_071*/
/* Implements: FLS259, FLS165, FLS166, FLS247, FLS363 */
/* Implements: SWS_Fls_00259, SWS_Fls_00363 */
/* Implements: EAAR_PN0034_FR_0092 */
FUNC(void, FLS_PUBLIC_CODE) Fls_GetVersionInfo
/* QAC Warning: START Msg(2:3227)-1*/
(P2VAR(Std_VersionInfoType, AUTOMATIC, FLS_APPL_DATA)versioninfo)
/* END Msg(2:3227)-1*/
{
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
    /* Report to DET  */
    /* Implements: FLS_ESDD_UD_110 */
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                 FLS_GET_VERSION_INFO_SID, FLS_E_PARAM_POINTER);
  }
  else
  #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* QAC Warning: START Msg(2:2814)-3 */
    /* Copy the vendor Id */
    versioninfo->vendorID = (uint16)FLS_VENDOR_ID;
    /* Copy the module Id */
    versioninfo->moduleID = (uint16)FLS_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = FLS_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = FLS_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = FLS_SW_PATCH_VERSION;
    /* END Msg(2:2814)-3 */
  }
}

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
#endif /* End of #if (FLS_VERSION_INFO_API == STD_ON) */

#if (FLS_READIMMEDIATE_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_ReadImmediate
**
** Service ID                : 0x11
**
** Description               : This API performs the reading of the flash
**                             memory. The data from flash memory
**                             (source address) is read to the data buffer
**                             (Target address) of application without
**                             performing blank check before read.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Reentrant
**
** Input Parameters          : SourceAddress, Length
**
** InOut Parameters          : None
**
** Output Parameters         : TargetAddressPtr
**
** Return parameter          : Std_ReturnType
**                             E_OK: if Read command has been accepted.
**                             E_NOT_OK: if Read command has not been accepted.
**
** Preconditions             : Component must be initialized using Fls_Init().
**
** Global Variables Used     : Fls_GblInitStatus, Fls_GstVar.ulReadAddress,
**                             Fls_GstVar.pBufferAddress,
**                             Fls_GstVar.ulCurrentLength,
**                             Fls_GstVar.enCommand, Fls_GenState,
**                             Fls_GenJobResult,
**                             Fls_GstVar.enReadType
**
**  Function(s) invoked      : Det_ReportError,Fls_ReadMisAlignHandler
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */

/* Implements: FLS_ESDD_UD_102*/
/* Implements: AR_PN0072_FR_0049, AR_PN0072_FR_0041*/
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_ReadImmediate
(
  Fls_AddressType                           SourceAddress,
  /* QAC Warning: START Msg(2:3227)-1*/
  P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
  /* END Msg(2:3227)-1*/
  Fls_LengthType                            Length
)
{
  /* Local variable to hold the DET return value */
  /* QAC Warning: START Msg(2:3204)-6 */
  Std_ReturnType LucReturnValue;
  /* END Msg(2:3204)-6 */
  #if (FLS_DEV_ERROR_DETECT == STD_OFF)
  LucReturnValue = E_OK;
  #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_OFF) */

  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  /* Check if the module is initialized */
  /* Invoking function to check whether driver is initialised/busy */
  LucReturnValue = Fls_DetErrorCheck(FLS_READ_IMM_SID);

  if (E_OK == LucReturnValue)
  #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Virtual address is mapped to physical address */
    /* Implements: FLS_ESDD_UD_015 */
    SourceAddress = SourceAddress + FLS_DF_BASE_ADDRESS;

    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Local variable to hold the read start address */
    Fls_GstVar.ulReadAddress = SourceAddress;

    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    /* Implements EAAR_PN0034_FR_0013 */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */

    #if (FLS_DEV_ERROR_DETECT == STD_ON)

    /* Check if the read start address is lies within the specified lower and
     * upper flash address boundaries.
     */
    if (
        (SourceAddress < FLS_DF_SECTOR_START_ADDRESS) ||
        (
          (SourceAddress - FLS_DF_SECTOR_START_ADDRESS) >
          (uint32)(FLS_DF_TOTAL_SIZE - FLS_ONE)
        )
      )
    {
      /* Report error to DET */
      (void)Det_ReportError (
                              FLS_MODULE_ID,
                              FLS_INSTANCE_ID,
                              FLS_READ_IMM_SID,
                              FLS_E_PARAM_ADDRESS
                            );
      /* Set Return Value as E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* No action required */
    }

    /* Check if the read length is greater than 0 and that the read end address
     * (read start address + length) lies within the specified upper flash
     * address boundary.
     */
    if (
        ((uint32)FLS_ZERO == Length) ||
        (
          (
            (Fls_GstVar.ulReadAddress - FLS_DF_SECTOR_START_ADDRESS) +
            Length
          ) >
          (uint32)FLS_DF_TOTAL_SIZE
        )
      )
    {
      /* Report error to DET */
      (void)Det_ReportError (
                              FLS_MODULE_ID,
                              FLS_INSTANCE_ID,
                              FLS_READ_IMM_SID,
                              FLS_E_PARAM_LENGTH
                            );
      /* Set Return Value as E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* No action required */
    }

    /* Check whether the target address pointer is a null pointer */
    if (NULL_PTR == TargetAddressPtr)
    {
      /* Report error to DET */
      (void)Det_ReportError (
                              FLS_MODULE_ID,
                              FLS_INSTANCE_ID,
                              FLS_READ_IMM_SID,
                              FLS_E_PARAM_DATA
                            );
      /* Set Return Value as E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* No action required */
    }

    /* Check whether any error is reported to DET */
    if (E_OK == LucReturnValue)
    #endif  /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
    {
      Length = Fls_ReadMisAlignHandler(SourceAddress,
                                  (uint32)TargetAddressPtr, Length);
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Disable relevant interrupts to protect this critical section */
      FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
      /* END Msg(4:0306)-3 */
      /* Initialize the global variable with target address and length */
      Fls_GstVar.pBufferAddress = TargetAddressPtr;
       /* Implements: FLS002, FLS003, SWS_Fls_00002, SWS_Fls_00003 */
      /* Set the current length of bytes to be processed */
      Fls_GstVar.ulCurrentLength = Length;
      /* Set the command to Read Immediate */
      Fls_GstVar.enCommand = FLS_COMMAND_READ_IMM;
      /* set the driver state to busy */
      Fls_GenState = MEMIF_BUSY;
      /* set the job result as pending */
      Fls_GenJobResult = MEMIF_JOB_PENDING;
      #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enable relevant interrupts to exit this critical section */
      /* Implements EAAR_PN0034_FR_0013 */
      FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
      #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    }

    #if (FLS_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* No action required */
    }
    #endif  /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  }
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action required */
  }
  #endif  /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  return(LucReturnValue);
} /* End of API Fls_ReadImmediate */

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
#endif /* End of #if (FLS_READIMMEDIATE_API == STD_ON) */
/* Implements: FLS_ESDD_UD_115, SWS_Fls_00371, SWS_Fls_00373 */
/* Implements: SWS_Fls_00374, SWS_Fls_00375, SWS_Fls_00376, SWS_Fls_00377 */
/* Implements: SWS_Fls_00379, SWS_Fls_00380, SWS_Fls_00381, SWS_Fls_00382 */
/* Implements: SWS_Fls_00383, SWS_Fls_00378 */
#if (FLS_BLANKCHECK_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_BlankCheck
**
** Service ID                : 0x0A
**
** Description               : This API performs the blank check of flash
**                             memory.
**
** Sync/Async                : Asynchronous
**
** Re-entrancy               : Non Re-entrant
**
** Input Parameters          : TargetAddress, Length
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : Std_ReturnType
**                             E_OK: if Read command has been accepted.
**                             E_NOT_OK: if Read command has not been accepted.
**
** Preconditions             : Component must be initialized using Fls_Init().
**
** Global Variables Used     : Fls_GblInitStatus,
**                             Fls_GstVar.ulRequestedLength
**                             Fls_GstVar.ulSrcDestAddress,
**                             Fls_GstVar.enCommand,Fls_GenState,
**                             Fls_GenJobResult
**
**  Function(s) invoked      : Det_ReportError,Fls_InitiateBlankCheckJob,
**                             Fls_ProcessJobResult,Fls_SetFHVE
**
** Registers Used            : FHVE3,FHVE15,DCENm,DTCTm,ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */

/* Implements: FLS_ESDD_UD_101, FLS_ESDD_UD_041, ECUC_Fls_00319, FLS319_Conf */
/* Implements: AR_PN0072_FR_0040, AR_PN0072_FR_0049, AR_PN0072_FR_0050 */
/* Implements: AR_PN0072_FR_0004 */
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_BlankCheck
(
  Fls_AddressType TargetAddress,
  /* QAC Warning: START Msg(2:3227)-1*/
  Fls_LengthType  Length
  /* END Msg(2:3227)-1*/
)
{
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;

  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  /* Invoking function to check whether driver is initialised/busy */
  LucReturnValue = Fls_DetErrorCheck(FLS_BLANK_CHECK_SID);
  #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */

  /* Virtual address is mapped to physical address */
  /* Implements: FLS_ESDD_UD_015, FLS_ESDD_UD_023 */
  TargetAddress = TargetAddress + FLS_DF_BASE_ADDRESS;
  /* Set the global variable with length */
  Fls_GstVar.ulRequestedLength = Length;
  /* Local variable to hold the blank check start address */
  Fls_GstVar.ulSrcDestAddress = TargetAddress;

  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  /* Check if the start address is aligned to a flash page boundary and lies
   * within the specified lower and upper flash address boundaries.
   */
  if (
      ((uint32)FLS_ZERO != (TargetAddress & (uint32)(FLS_PAGE_SIZE - FLS_ONE)))
      ||
      (TargetAddress < FLS_DF_SECTOR_START_ADDRESS) ||
        (
          (TargetAddress - FLS_DF_SECTOR_START_ADDRESS) >
          (uint32)(FLS_DF_TOTAL_SIZE - FLS_ONE)
        )
    )
  {
    /* Report error to DET */
    (void)Det_ReportError (
                            FLS_MODULE_ID,
                            FLS_INSTANCE_ID,
                            FLS_BLANK_CHECK_SID,
                            FLS_E_PARAM_ADDRESS
                          );
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  /* Check if the length is greater than 0 and that the end address
   * (start address + length) lies within the specified upper flash
   * address boundary.
   */
  if (
      ((uint32)FLS_ZERO == Length) ||
      (
        (
          (Fls_GstVar.ulSrcDestAddress - FLS_DF_SECTOR_START_ADDRESS) +
          Length
        ) >
        (uint32)FLS_DF_TOTAL_SIZE
      ) ||
      (
        (uint32)FLS_ZERO !=
        (
          (Fls_GstVar.ulSrcDestAddress + Length) &
          (uint32)(FLS_PAGE_SIZE - FLS_ONE)
        )
      )
    )
  {
    /* Report error to DET */
    (void)Det_ReportError (
                            FLS_MODULE_ID,
                            FLS_INSTANCE_ID,
                            FLS_BLANK_CHECK_SID,
                            FLS_E_PARAM_LENGTH
                          );
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  /* Check whether any error is reported to DET */
  if (E_OK == LucReturnValue)
  #endif  /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Disable relevant interrupts to protect this critical section */
    FLS_ENTER_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Set the command as blank check command */
    Fls_GstVar.enCommand = FLS_COMMAND_BLANKCHECK;
    /* Set the job result to Job pending */
    Fls_GenJobResult = MEMIF_JOB_PENDING;
    /* Set the driver state as Busy */
    Fls_GenState = MEMIF_BUSY;
    #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant interrupts to exit this critical section */
    /* Implements EAAR_PN0034_FR_0013 */
    FLS_EXIT_CRITICAL_SECTION(FLS_DRIVERSTATE_DATA_PROTECTION);
    #endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */
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

    #if (FLS_INTERRUPT_MODE == STD_ON)
    Fls_GetIntReq();
    Fls_ClearIntReq();
    /* Enable interrupt processing */
    /* QAC Warning: START Msg(2:2814)-3 */
    /* MISRA Violation: START Msg(4:0303)-9 */
    RH850_SV_MODE_ICR_AND(16, &(FLS_ICFLENDNM), (FLS_RESET_INT_MK));
    /* END Msg(4:0303)-9 */
    /* END Msg(2:2814)-3 */
    #endif /* End of #if (FLS_INTERRUPT_MODE == STD_ON) */

    /* Initiate blank check Job */
    LucReturnValue = Fls_InitiateBlankCheckJob();

    /* Check for the status is FLS_FCU_OK */
    if (E_NOT_OK == LucReturnValue)
    {
      Fls_ProcessJobResult(MEMIF_JOB_FAILED);
    }
    else
    {
    /* No action required */
    }
  }
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action required */
  }
  #endif  /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */

  return(LucReturnValue);
}
#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
#endif /* End of #if (FLS_BLANKCHECK_API == STD_ON) */

#if (FLS_SUSPEND_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_Suspend
**
** Service ID                : 0x13
**
** Description               : This API performs the suspend of the on going
**                             job. This function returns E_NOT_OK if requested
**                             job cannot be suspended.
**
** Sync/Async                : Asynchronous
**
** Re-entrancy               : Non Re-entrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Std_ReturnType
**
** Return parameter          : None
**
** Preconditions             : Component must be initialized using Fls_Init().
**
** Global Variables Used     : Fls_GblInitStatus,Fls_GenState,
**                             Fls_GstVar.enDFStatus,Fls_GblJobSuspended,
**                             Fls_GblJobSuspendRequest
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */

/* Implements: FLS_ESDD_UD_192*/
/* Implements: AR_PN0072_FR_0045, AR_PN0072_FR_0049 */
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Suspend(void)
{
  /* Variable to store API's return value */
  Std_ReturnType LucReturnValue = E_OK;

  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  /* Check if the module is initialized */
  if (FLS_UNINITIALIZED == Fls_GblInitStatus)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                                 FLS_SUSPEND_SID, FLS_E_UNINIT);
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }

  /* Check whether any error reported to DET */
  if (E_OK == LucReturnValue)
  #endif  /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if the function is called for allowed command (write or erase) and
       if driver state is not Idle */
    if (
        /* MISRA Violation: START Msg(4:3415)-6 */
        /* QAC Warning: START Msg(2:3416)-2 */
        (
          (FLS_COMMAND_WRITE == Fls_GstVar.enCommand) ||
          (FLS_COMMAND_ERASE == Fls_GstVar.enCommand)
        ) &&
        (MEMIF_BUSY == Fls_GenState) &&
        (FLS_FALSE == Fls_GblJobSuspended)
       /* END Msg(2:3416)-2 */
       /* END Msg(4:3415)-6 */
      )
    {
      Fls_GblJobSuspendRequest = FLS_TRUE;
    }
    else
    {
      Fls_GstVar.enDFStatus = FLS_FCU_ERR_REJECTED;
      LucReturnValue = E_NOT_OK;
    }
  }
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action required */
  }
  #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  return(LucReturnValue);
} /* End of API Fls_Suspend */

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
#endif /* End of #if (FLS_SUSPEND_API == STD_ON) */

#if (FLS_RESUME_API == STD_ON)
/*******************************************************************************
** Function Name             : Fls_Resume
**
** Service ID                : 0x14
**
** Description               : This API resumes the suspended job.
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
** Preconditions             : Component must be initialized using Fls_Init().
**
** Global Variables Used     : Fls_GblInitStatus,Fls_GenState,
**                             Fls_GblJobSuspended,Fls_GenState,
**                             Fls_GstVar.enDFStatus
**
**  Function(s) invoked      : Det_ReportError,Fls_ProcessResume
**
** Registers Used            : FHVE3,FHVE15,FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,
**                             DCENm,DTCTm,ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */

/* Implements: FLS_ESDD_UD_193 */
/* Implements: AR_PN0072_FR_0046, AR_PN0072_FR_0049 */
FUNC(void, FLS_PUBLIC_CODE) Fls_Resume(void)
{
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  Std_ReturnType LucReturnValue = E_OK;

  /* Check if the module is initialized */
  if (FLS_UNINITIALIZED == Fls_GblInitStatus)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                                 FLS_RESUME_SID, FLS_E_UNINIT);
    /* Set Return Value as E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  /* Check whether any error reported to DET */
  if (E_OK == LucReturnValue)
  #endif  /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if currently the Driver is in Idle State */
      /* MISRA Violation: START Msg(4:3415)-6 */
      /* QAC Warning: START Msg(2:3416)-2 */
    if ((FLS_TRUE == Fls_GblJobSuspended) && \
                                        (MEMIF_IDLE == Fls_GenState))
      /* END Msg(2:3416)-2 */
      /* END Msg(4:3415)-6 */
    {
      #if (FLS_INTERRUPT_MODE == STD_ON)
      /* Enable interrupt processing */
      /* QAC Warning: START Msg(2:2814)-3 */
      /* MISRA Violation: START Msg(4:0303)-9 */
      RH850_SV_MODE_ICR_AND(16, &(FLS_ICFLENDNM), (FLS_RESET_INT_MK));
      /* END Msg(4:0303)-9 */
      /* END Msg(2:2814)-3 */
      #endif /* End of #if (FLS_INTERRUPT_MODE == STD_ON) */
      Fls_ProcessResume();
    }
    else
    {
      Fls_GstVar.enDFStatus = FLS_FCU_ERR_REJECTED;
    }
  }
  #if (FLS_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* No action required */
  }
  #endif /* End of #if (FLS_DEV_ERROR_DETECT == STD_ON) */

} /* End of API Fls_Resume */

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
#endif /* End of #if (FLS_RESUME_API == STD_ON) */

/*******************************************************************************
** Function Name         : Fls_CheckHWConsistency
**
** Service ID            : 0x15
**
** Description           : This API will execute registers ram mirroring check.
**
** Sync/Async            : synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : HWConsistencyMode
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType - Returns E_OK if the registers values
**                         corresponds with their ram copy else returns E_NOT_OK
**                         if there is at least one difference.
**
** Preconditions         : Component must be initialized using Fls_Init().
**
** Global Variables Used : Fls_GaaRamMirror
**
** Function(s) invoked   : Det_ReportError
**
** Registers Used        : DFERRINT,DFERSTR,FASTAT,FEADDR,FENTRYR,FSADDR,FPCKAR,
**                         DTCTm,DCENm,DTFRm,DRDAm,DRTCm
**
*******************************************************************************/
#if (FLS_RAM_MIRROR == FLS_MIRROR_ENABLE)

#define FLS_START_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
/* TRACE [R4, EAAR_PN0034_FSR_0006 ] */
/* Implements: FLS_ESDD_UD_265, FLS_ESDD_UD_145 */
/* Implements: EAAR_PN0034_FSR_0007, EAAR_PN0034_FSR_0006 */
/* Implementation of Fls_CheckHWConsistency API */
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_CheckHWConsistency
(
  /* QAC Warning: START Msg(2:3227)-1*/
  Fls_HWConsistencyModeType LenHWConsistencyMode
  /* END Msg(2:3227)-1*/
)
{
  /* Local variable to hold the return value of the function */
  Std_ReturnType LucReturnValue = E_OK;

  return(LucReturnValue);
} /* End of API Fls_CheckHWConsistency  */

#define FLS_STOP_SEC_PUBLIC_CODE
/* MISRA Violation: START Msg(2:0832)-5 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-5 */
#endif /* (FLSTST_RAM_MIRROR == FLS_MIRROR_ENABLE) */
/*******************************************************************************
**                           End of File                                      **
*******************************************************************************/
