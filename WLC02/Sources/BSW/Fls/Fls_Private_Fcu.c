/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Private_Fcu.c                                           */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2016 - 2018 Renesas Electronics Corporation                   */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains FCU related API implementations                         */
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
 * V1.0.1:  10-Aug-2016  : As a part of JIRA ticket ARDAABD-513,
 *                         1. SYNCP where added in Fls_FcuSwitchBFlash,
 *                            Fls_FcuGetFWParam and Fls_FcuCopytoRam functions
 *                         2. function call to Fls_FcuClearCache() were added
 *                            in Fls_FcuGetFWParam() and Fls_FcuCopytoRam()
 *
 * V1.0.2:  11-Aug-2016  : Update after review of JIRA ticket ARDAABD-513
 *
 * V1.0.3:  06-Sep-2016  : Removed param FLS_FACI_ECC_CHECK ARDAABD-701
 *
 * V1.1.0:  28-Sep-2016  :  #ARDAABD-843
 *                          1. Removed support for
 *                             FLS_AR_HIGHER_VERSION / FLS_AR_LOWER_VERSION
 *
 * V1.1.1:  20-Oct-2016  :  #ARDAABD-447
 *                          1. Replaced FLS_FCU_SWITCHMODE_WAIT_COUNT macro
 *                             with FLS_FCU_WAIT_COUNT
 *                          2. Replaced FLS_FCU_FORCESTOP_WAIT_COUNT macro
 *                             with FLS_FCU_WAIT_COUNT
 *
 * V2.0.0:  31-Oct-2016 : #ARDAABD-650
 *                        1. Removed Fls_FcuSuspendCheck which is renamed to
 *                           Fls_SuspendPreCheck and moved to Fls_Internal.c
 *
 * V2.1.0:  11-Nov-2016:  #ARDAABD-732
 *                        1. Fls_DmaInit function added, which initialize the
 *                           DMA channel registers.
 *                        2. in Fls_FcuCheckJobStatus function, DMA transfer
 *                           error check is added, FSTATR FRDY and ERR check
 *                           has been swapped.
 *
 * V2.1.1:  15-Nov-2016 : #ARDAABD-893 - function's Fls_FcuPerformBlankCheck
 *                                       Luscount parameter changed to uint32
 *
 * V2.1.2:  15-Nov-2016 : #ARDAABD-649 - fixed minor review finding
 *
 * V2.1.3:  25-Nov-2016 : #ARDAABD-454 - added include of Fls_Internal.h
 *
 * V2.1.4:  07-Dec-2016 : #ARDAABD-437 - added dummy read for FACI's FENTRYR
 *
 * V2.1.5:  19-Dec-2016 : #ARDAABD-736 - In Fls_DmaInit function, write verify
 *                          macro has been changed from WRITE_VERIFY_RUNTIME
 *                          to WRITE_VERIFY_INIT.
 *
 * v2.2.0:  18-Jan-2017  : #ARDAABD-923
 *                         1. Added FLS_ECC_INITCHK_SUPPORT macro
 *
 * V2.2.1:  19-Jan-2016  : #ARDAABD-459
 *                         1. Changed the Write Verify MASK value for DCEN, DTCT
 *                           and DTFR registers.
 *                         2. Removed Write Verify check for DTFRRQC register.
 *                         3. Corrected value written to DCSTC register in
 *                           Fls_FcuCheckJobStatus function.
 *
 * V2.2.2:  19-Jan-2017  :  #ARDAABD-447
 *                          1. added timeout protection for Fls_FcuClearCache
 *                             function
 *
 * V2.2.3:  20-Jan-2017  : #ARDAABD-437
 *                         1. Replaced numbers with macros
 *
 * V2.3.0:  27-Jan-2017  : #ARDAABD-454
 *                         1. Fixing file's name and header.
 *                         2. Replced number by macro.
 *
 * V2.3.1:  30-Jan-2017  : #ARDAABD-459
 *                         1. Fls_DmaInit Dma register checked
 *                            to be 0 after initialization.
 *
 * V2.3.2:  30-Jan-2017  :  #ARDAABD-571
 *                          1. Masked reference values for bit registers not
 *                             stored in HW (reads 0 always).
 *                          2. FPCKAR register no more RAM mirrored.
 *                          3. In initailization called routines, replaced
 *                             FLS_CHECK_WRITE_VERIFY_RUNTIME by
 *                             FLS_CHECK_WRITE_VERIFY_INIT.
 *
 * V2.3.3:  31-Jan-2017  : #ARDAABD-459
 *                         1. Dma status register checked to be 0 after
 *                            clearing it.
 *
 * V2.4.0:  31-Jan-2017  :  #ARDAABD-571
 *                          1. Addded MemMap_Fls vs MemMap.h inclusion based on
 *                             AR revision.
 *                          2. Added reg write verify feature.
 *                          3. Changes after review.
 *                          4. FPCKAR register no more RAM mirrored.
 *                          5. FCURAME register no more RAM mirrored.
 *
 * V2.5.0:  31-Jan-2017 : #ARDAABD-454
 *                        1. Fls_DmaInit moved in Fls_Internal.
 *
 * V2.5.1:  14-Feb-2017  :  #ARDAABD-571
 *                          1. Fixed acceptance findings.
 *                          2. Fixed review findings.
 *
 * V2.5.2:  13-Mar-2017  :  #ARDAABD-829
 *                          1.  MISRA fixes.
 * V2.5.3:  20-Jul-2017  :  ARDAABD-1170 - Fls_FcuBlankCheckResult return value
 *                          evaluation has been added.
 *                          ARDAABD-1139 - ulDFERSTR register access has been
 *                          changed to ucDFERSTR. Fls_FcuDataCopy return value
 *                          has been changed to uint8.
 *                          ARDAABD-1118 - Error bit checking has been removed
 *                          from the Fls_FcuClearStatus function.
 *                          ARDAABD-1246 - Removed Firmware copy support.
 *                          ARDAABD-1325 - Fls_FcuReturnFromCmdLock function has
 *                          been added.
 *                          Updated Fls_FcuCheckSequencerStatus function.
 *                          ARDAABD-1329 - CMDLK bit checked has been added in
 *                          Fls_FcuForcedStop function.
 * V2.5.4:  24-Aug-2017  :  #ARDAABD-2151 - Added QAC/MISRA Warnings
 *                          justification. Corrected QAC/MISRA Warning.
 * V2.5.5   22-Sep-2017  :  #ARDAABD-2442 - LucFreqDivider is set to
 *                          FLS_CPUCLK_UL_DIV value for Firmware version >=
 *                          FLS_FCU_FWVER_04.
 *                          #ARDAABD-2515 - Removed the KEY for FPCKAR and
 *                          FENTRYR CHECK_WRITE_VERIFY macro.
 *                          #ARDAABD-2370 corrected variables naming convention
 * V2.5.6   16-Oct-2017  :  #ARDAABD-2552 - removed Dem.h inclusion for AR4.2.2
 *                          added Det.h inclusion for AR4.2.2
 * V2.5.7  22-Jan-2018   :  ARDAABD-2917 - Updated functions header with used
 *                          registers and invoked functions.
 * V2.5.8  05-Jul-2018   :  Following changes are made:
 *                          1. As part of merging activity, #ARDAABD-3465
 *                             below changes are made(Ref : ARDAABD-2158):
 *                             a. Replaced the usage of 'IMRn' Registers
 *                                with 'ICxxx' registers for the comment
 *                                provided for Include Section.
 *                             b. Inserted a one space character after
 *                                'if' statement.
 *                             c. Copyright information has been updated.
 *                          2. As part of #ARDAABD-3633, the list of
 *                             registers in the function banners of APIs
 *                             Fls_FcuForcedStop, Fls_PreFcuInitCheck and
 *                             Fls_FcuSwitchMode are updated.
 *                          3. As per ARDAABD-3853, traceability has been
 *                             improved.
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Included for macro definitions and API prototypes */
#include "Fls_Private_Fcu.h"
/* Included for RAM variable declarations */
#include "Fls_Ram.h"
#include "Fls_Hardware.h"
/* Included for the macro declaration of supervisor mode(SV) write enabled
    Registers ICR */
//#include "rh850_Types.h"
/* Included for Prototype Declarations for FLS callback Notification FUNCTIONS*/
#include "Fls_Cbk.h"
#if (FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)
/* Included for the declaration of Det_ReportRuntimeError */
#include "Det.h"
#endif /* (FLS_AR_VERSION == FLS_AR_HIGHER_VERSION) */
/* Included for macro declarations for wv and ram mirror */
//#include "Fls_RegWrite.h"
#if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Fls.h"
#endif
/* Included prototypes for internal functions of Flash Wrapper Component */
#include "Fls_Internal.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR release version information */
#define FLS_PRIVATE_FCU_C_AR_RELEASE_MAJOR_VERSION \
                                        FLS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLS_PRIVATE_FCU_C_AR_RELEASE_MINOR_VERSION \
                                        FLS_AR_RELEASE_MINOR_VERSION_VALUE
#define FLS_PRIVATE_FCU_C_AR_RELEASE_REVISION_VERSION \
                                     FLS_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FLS_PRIVATE_FCU_C_SW_MAJOR_VERSION     FLS_SW_MAJOR_VERSION_VALUE
#define FLS_PRIVATE_FCU_C_SW_MINOR_VERSION     FLS_SW_MINOR_VERSION_VALUE

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (FLS_PRIVATE_FCU_AR_RELEASE_MAJOR_VERSION != \
                                  FLS_PRIVATE_FCU_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fls_Private_Fcu.c : Mismatch in Release Major Version"
#endif
#if (FLS_PRIVATE_FCU_AR_RELEASE_MINOR_VERSION != \
                                  FLS_PRIVATE_FCU_C_AR_RELEASE_MINOR_VERSION)
  #error "Fls_Private_Fcu.c : Mismatch in Release Minor Version"
#endif
#if (FLS_PRIVATE_FCU_AR_RELEASE_REVISION_VERSION != \
                                  FLS_PRIVATE_FCU_C_AR_RELEASE_REVISION_VERSION)
  #error "Fls_Private_Fcu.c : Mismatch in Release Revision Version"
#endif

#if (FLS_PRIVATE_FCU_SW_MAJOR_VERSION != FLS_PRIVATE_FCU_C_SW_MAJOR_VERSION)
  #error "Fls_Private_Fcu.c : Mismatch in Software Major Version"
#endif
#if (FLS_PRIVATE_FCU_SW_MINOR_VERSION != FLS_PRIVATE_FCU_C_SW_MINOR_VERSION)
  #error "Fls_Private_Fcu.c : Mismatch in Software Minor Version"
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
/* 2.  MISRA C RULE VIOLATION:                                                */
/* Message       : (2:0832) Macro substitution in #include preprocessing      */
/*                 directive.                                                 */
/* Rule          : No MISRA-C:2004 Rule                                       */
/* Justification : Required to optimize MemMap inclusion because of ASR403    */
/*                 and ASR422 support.                                        */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:0832)-2 and                           */
/*                 END Msg(2:0832)-2 tags in the code.                        */
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
/*******************************************************************************
**                         QAC Warning                                        **
*******************************************************************************/
/* 1. QAC Warning:                                                            */
/* Message       : (2:2814) Possible: Dereference of NULL pointer.            */
/* Justification : The Pointers generated using Post Build configurations may */
/*                 not be NULL.                                               */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:2814)-1 and                           */
/*                 END Msg(2:2814)-1 tags in the code.                        */
/******************************************************************************/
/* 2. QAC Warning:                                                            */
/* Message       : (2:3204) This variable is only set once and so it could    */
/*                 be declared with the 'const' qualifier.                    */
/* Justification : These variables cannot be declared with 'const' qualifier  */
/*                 since these variables are subjected to change based on     */
/*                 register value.                                            */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any safety impact.                              */
/* Reference     : Look for START Msg(2:3204)-2 and                           */
/*                 END Msg(2:3204)-2 tags in the code.                        */
/******************************************************************************/
/* 3. QAC Warning:                                                            */
/* Message       : (2:2016) This 'switch' statement 'default' clause is empty.*/
/* Justification : No action is required for default statements. Hence it is  */
/*                 left empty.                                                */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:2016)-3 and                           */
/*                 END Msg(2:2016)-3 tags in the code.                        */
/******************************************************************************/
/* 4. QAC Warning:                                                            */
/* Message       : (2:3892) The result of this cast is implicitly converted   */
/*                 to another type                                            */
/* Rule          : MISRA-C:2004 Message 3892                                  */
/*                 REFERENCE - ISO:C90-6.3.2.1 Semantics                      */
/* Justification : This implicit conversion is done to access the data from   */
/*                 the post build configuration                               */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:3892)-4 and                           */
/*                 END Msg(2:3892)-4 tags in the code.                        */
/******************************************************************************/
/* 5. QAC Warning:                                                            */
/* Message       : (2:3416) Logical operation performed on expression with    */
/*                 possible side effects.                                     */
/* Justification : Logical operation accesses volatile object which is a      */
/*                 register access or global variable. All register addresses */
/*                 are generated with volatile qualifier. There is no impact  */
/*                 on the functionality due to this conditional check for mode*/
/*                 change.                                                    */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:3416)-5 and END Msg(2:3416)-5         */
/*                 tags in the code.                                          */
/******************************************************************************/
/******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#if (STD_ON == FLS_ECC_INITCHK_SUPPORT)
/*******************************************************************************
** Function Name             : Fls_PreFcuInitCheck
**
** Service ID                : NA
**
** Description               : This function checks there are no ECC errors
**                             during FLS initialisation
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Fls_FcuStatusType
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : DFECCCTL,DFERRINT,DFTSTCTL
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/* Implements: FLS_ESDD_UD_157*/
/* Implements: FLS014, SWS_Fls_00014, FLS_ESDD_UD_002 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_PreFcuInitCheck(void)
{
  /* Initialise the local variable to hold the FCU Status */
  Fls_FcuStatusType LenStatus = FLS_FCU_OK;


  return LenStatus;
}/* End of function Fls_PreFcuInitCheck */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
#endif /* #if (STD_ON == FLS_ECC_INITCHK_SUPPORT) */

/*******************************************************************************
** Function Name             : Fls_FcuWritePreCheck
**
** Service ID                : NA
**
** Description               : This Function checks if Write Job shall be
**                             initiated
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : Re-entrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Fls_FcuStatusType
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : FSTATR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_188 */
/* Implements: FLS331 */
/* Implements: SWS_Fls_00331, FLS_ESDD_UD_002 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuWritePreCheck(void)
{
  Fls_FcuStatusType LenStatus;
  /* Checking against error bits */
  /* QAC Warning: START Msg(2:2814)-1 */

  return(LenStatus);
} /* End of function Fls_FcuWritePreCheck */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuCheckSequencerStatus
**
** Service ID                : NA
**
** Description               : This function checks the FRDY bit and if
**                             there is a cmd lock based on timeout values.

** Sync/Async                : Synchronous
**
** Re-entrancy               : Re-entrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Fls_FcuStatusType
**
** Return parameter          : retVal
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : FSTATR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_182, FLS_ESDD_UD_002 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuCheckSequencerStatus(void)
{
  Fls_FcuStatusType LenRetVal = FLS_FCU_ERR_INTERNAL;
  uint32  LulTimeout          = FLS_FCU_FRDY_POOL_COUNT;
  boolean LblFrdyCheck = FLS_FALSE; /* frdy = 0, not ready */
  boolean LblCmdLockCheck; /* no cmd lock */


  return(LenRetVal);
} /* End of function Fls_FcuCheckSequencerStatus */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuSwitchMode
**
** Service ID                : NA
**
** Description               : This function Switch FCU mode to Programming/User
**                             mode and checks if the Flash sequencer operation
**                             mode switch is performed correctly
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : LusMode
**
** InOut Parameters          : None
**
** Output Parameters         : Fls_FcuStatusType
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstFcuVar.usFcuFlashMode
**
** Function(s) invoked       : Fls_FcuCheckSequencerStatus, Fls_FcuForcedStop
**
** Registers Used            : FENTRYR,FSADDR,FEADDR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_002, FLS_ESDD_UD_146 */
/* Implements: FLS_ESDD_UD_183 */
/* Implements: FLS249 */
/* Implements: SWS_Fls_00249 */
/* Implements: EAAR_PN0034_FR_0084, EAAR_PN0034_FR_0085, EAAR_PN0034_FR_0086 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuSwitchMode
(VAR(const uint16, FLS_APPL_DATA) LusMode)
{
  Fls_FcuStatusType LenRetVal;
  uint8 LucLoopCount = (uint8)FLS_FCU_WAIT_COUNT;
  /* QAC Warning: START Msg(2:2814)-1 */

  return (LenRetVal);
}/* End of function Fls_FcuSwitchMode */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuPrepareEnvironment
**
** Service ID                : NA
**
** Description               : This function initialises the FCU RAM, sets the
**                             FACI frequency, resets FCU and initialise
**                             hardware registers to default values.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Fls_FcuStatusType
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstFcuVar.ulFcuDfSize
**
** Function(s) invoked       : Fls_FcuSwitchMode,Fls_FcuForcedStop,
**                             Fls_FcuClearStatus,Fls_FcuSetFrequency,
**                             Fls_FcuGetDFSize
**
** Registers Used            : FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,FPCKAR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_184*/
/* Implements: FLS249 */
/* Implements: SWS_Fls_00249*/
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuPrepareEnvironment(void)
{
  Fls_FcuStatusType LenStatus;

  /* Switching to P/E Mode */
  LenStatus = Fls_FcuSwitchMode(FLS_FCU_MODE_PE);

  if (FLS_FCU_OK == LenStatus)
  {
     /* Reset FCU again to clear any possible ECC errors */
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
    /* Switching to USER Mode */
    LenStatus = Fls_FcuSwitchMode(FLS_FCU_MODE_USER);
  }
  else
  {
    /* No action required */
  }

  if (FLS_FCU_OK == LenStatus)
  {
    LenStatus = FLS_FCU_BUSY;
  }
  else
  {
    /* No action required */
  }

  if (FLS_FCU_BUSY == LenStatus)
  {
    Fls_GstFcuVar.ulFcuDfSize = Fls_FcuGetDFSize();

    if ((uint16)FLS_DF_POOL_SIZE <=
        (uint16)(Fls_GstFcuVar.ulFcuDfSize >> FLS_FCU_BLOCK_SIZE_2N))
    {
      /* Configure the FCU frequency */
      LenStatus = Fls_FcuSetFrequency();
    }
    else
    {
      LenStatus = FLS_FCU_ERR_CONFIGURATION;
    }
  }
  else
  {
    /* No action required */
  }

  return (LenStatus);
} /* End of function Fls_FcuPrepareEnvironment */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuForcedStop
**
** Service ID                : NA
**
** Description               : This function issues Forced Stop command and
**                             resets FCU and FACI registers.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Fls_FcuStatusType
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : FLS_FCU_DF_ISSUE_BYTE_CMD
**
** Registers Used            : FSTATR,FASTAT
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_185*/
/* Implements: FLS249 */
/* Implements: SWS_Fls_00249*/
/* Implements EAAR_PN0034_FR_0084,EAAR_PN0034_FR_0085,EAAR_PN0034_FR_0086 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuForcedStop(void)
{
  uint32 LulReturnValue;
  Fls_FcuStatusType LenStatus;
  uint8 LucLoopCount;
  uint8 LucFlsStatusRegValue;


  return(LenStatus);

}/* End of function Fls_FcuForcedStop */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuClearStatus
**
** Service ID                : NA
**
** Description               : This function clears (error) status of the
**                             sequencer by issuing the clear status FCU
**                             command.
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
** Global Variables Used     : None
**
** Function(s) invoked       : FLS_FCU_DF_ISSUE_BYTE_CMD
**
** Registers Used            : NA
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/* Implements: FLS249 */
/* Implements: SWS_Fls_00249 */
/* Implements: FLS_ESDD_UD_264 */
FUNC(void, FLS_PRIVATE_CODE) Fls_FcuClearStatus(void)
{
  /* MISRA Violation: START Msg(4:0303)-1 */
  /* Issue Clear Status Command */
  FLS_FCU_DF_ISSUE_BYTE_CMD(FLS_FACI_CMD_CLEARSTAT);
  /* END Msg(4:0303)-1 */

} /* End of function Fls_FcuClearStatus */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuGetFWParam
**
** Service ID                : NA
**
** Description               : This function reads the out a firmware parameter
**                             from the Extra area
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : LulAddress
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : LulValue
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : Fls_FcuSwitchBFlash,FLS_DF_READ32,
**                             Fls_FcuClearCache
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_118*/
/* Implements: FLS249 */
/* Implements: SWS_Fls_00249*/
FUNC(uint32, FLS_PRIVATE_CODE) Fls_FcuGetFWParam(const uint32 LulAddress)
{
  uint32 LulValue;
  /* QAC Warning: START Msg(2:2814)-1 */
  /* MISRA Violation: START Msg(4:0306)-3 */
  LulValue = (*(uint32*)LulAddress);
  /* END Msg(2:2814)-1 */
  /* MISRA Violation: END Msg(4:0306)-3 */
  return(LulValue);

}/*End of function Fls_FcuGetFWParam */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuGetDFSize
**
** Service ID                : NA
**
** Description               : This function is used to get the Data Flash size
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Size of data flash
**
** Return parameter          : LulReturn
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : Fls_FcuGetFWParam,FLS_DF_READ32
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_119*/
/* Implements: FLS249 */
/* Implements: SWS_Fls_00249*/
FUNC(uint32, FLS_PRIVATE_CODE) Fls_FcuGetDFSize(void)
{
  uint32 LulReturn;
  uint32 LulData;
  uint32 LulDataAddr;

  /* Entry tells where to find the PRD* information */
  LulDataAddr = Fls_FcuGetFWParam(FLS_FCU_EXTRA3_SCDSADD);
  /* MISRA Violation: START Msg(4:0303)-1 */
  LulData = FLS_DF_READ32(LulDataAddr + FLS_FCU_PRDSEL3_OFFSET);
  /* END Msg(4:0303)-1 */
  /* Lower 16Byte are the DF size in kB. So, multiply accordingly */
  LulData &= FLS_FCU_DF_SIZE_MASK;
  LulReturn = LulData * FLS_FCU_ONE_KB;

  return(LulReturn);
} /*End of function Fls_FcuGetDFSize */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuSetFrequency
**
** Service ID                : NA
**
** Description               : This function is used to set the FCU frequency.
**                             FCU frequency, set in MHz is needed.
**                             The function may return an error if the
**                             frequency could not be set.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Fls_FcuStatusType
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : Fls_FcuGetFWParam
**
** Registers Used            : FPCKAR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_122*/
/* Implements: FLS249 */
/* Implements: SWS_Fls_00249*/
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuSetFrequency(void)
{
  Fls_FcuStatusType LenStatus;
  /* QAC Warning: START Msg(2:3204)-2 */
  uint16 LusCpuFreq;
  uint16 LusFaciFreq;
  /* END Msg(2:3204)-2 */
  uint32 LulFwVal;
  uint8  LucFwVer;
  uint8  LucFreqDivider;
  uint32 LulMinFreq;
  uint32 LulMaxFreq;
  uint32 LulPClkFreq;
  uint32 LulFreqData;



  return(LenStatus);
} /*End of function Fls_FcuSetFrequency */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuInit
**
** Service ID                : NA
**
** Description               : This function initialises FCU Global Variable
**                             Structure and prepares the environment
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
** Global Variables Used     : Fls_GstFcuVar.usCpuFrequencyMHz
**                             Fls_GstFcuVar.usFcuFlashMode
**                             Fls_GstFcuVar.ulFcuDfSize
**                             Fls_GstFcuVar.ulFcuBaseAddrECC
**                             Fls_GstFcuVar.ulFcuChksumEndAddr
**                             Fls_GstFcuVar.ulFcuChksumVal
**                             Fls_GstFcuVar.usDFPoolSize
**
** Function(s) invoked       : Fls_FcuPrepareEnvironment
**
** Registers Used            : FSADDR,FEADDR,FSTATR,FENTRYR,FASTAT,FPCKAR
*******************************************************************************/

#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_186*/
/* Implements: FLS249 */
/* Implements: SWS_Fls_00249*/
FUNC(void, FLS_PRIVATE_CODE) Fls_FcuInit(void)
{
  Fls_FcuStatusType LenStatus;
  /* Initializing the FCU Global Variable Structure */
  Fls_GstFcuVar.usCpuFrequencyMHz   = FLS_CPU_FREQUENCY_MHZ;
  Fls_GstFcuVar.usDFPoolSize        = FLS_DF_POOL_SIZE;
  Fls_GstFcuVar.usFcuFlashMode      = FLS_FCU_MODE_USER;
  Fls_GstFcuVar.ulFcuDfSize         = (uint32)(FLS_FCU_NULL);
  Fls_GstFcuVar.ulFcuBaseAddrECC    = (uint32)(FLS_FCU_NULL);
  Fls_GstFcuVar.ulFcuChksumEndAddr  = (uint32)(FLS_FCU_NULL);
  Fls_GstFcuVar.ulFcuChksumVal      = (uint32)(FLS_FCU_NULL);

  /* Preparing Environment */
  LenStatus = Fls_FcuPrepareEnvironment();
  /* Returning Status after Prepare Environment */
  Fls_GstVar.enDFStatus = LenStatus;

}/* End of function Fls_FcuInit */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/*******************************************************************************
** Function Name             : Fls_FcuDataCopy
**
** Service ID                : None
**
** Description               : This function copies the Read data from Temporary
**                             Buffer to Application Buffer.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : LulSrcAddr, LulBufferAddr
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : LulDFERStatus
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.ulSrcDestAddress
**
** Function(s) invoked       : FLS_DF_READ32,FLS_DF_WRITE32
**
** Registers Used            : DFERSTR,DFERSTC
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/* Implements: AR_PN0072_FR_0041, FLS_ESDD_UD_265 */
FUNC(uint8, FLS_PRIVATE_CODE) Fls_FcuDataCopy
(const uint32 LulSrcAddr, const uint32 LulBufferAddr)
{
  uint32 LulReadData;
  /* Local variable to hold the value of Data Flash error status register */
  uint8 LucDFERStatus;
  /* MISRA Violation : START Msg(4:0303)-1 */
  /* QAC Warning: START Msg(2:2814)-1 */


  return(LucDFERStatus);
}/* End of function Fls_FcuDataCopy */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuOffsetDataCopy
**
** Service ID                : None
**
** Description               : This function is used to copy the data from
**                             Temporary Buffer to Application Buffer in case of
**                             Misaligned address or length is input.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Reentrant
**
** Input Parameters          : LulSrcAddr, LulBufferAddr, LucOffset
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : Read operation address/length are not page
**                             aligned.
**
** Global Variables Used     : None
**
** Function(s) invoked       : FLS_DF_READ8,FLS_DF_READ16,FLS_DF_WRITE8,
**                             FLS_DF_WRITE16
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: AR_PN0072_FR_0041, FLS_ESDD_UD_266 */
FUNC(void, FLS_PRIVATE_CODE) Fls_FcuOffsetDataCopy
(uint32 LulSrcAddr, uint32 LulBufferAddr, const uint8 LucOffset)
{
  uint8 LucReadData;
  uint16 LusReadData;

  switch (LucOffset)
  {
  case FLS_ONE:
    /* MISRA Violation: START Msg(4:0303)-1 */
    /* QAC Warning: START Msg(2:2814)-1 */

    /* Reading the data from source address */
    LucReadData = FLS_DF_READ8(LulSrcAddr);
    /* Writing the data to application buffer */
    FLS_DF_WRITE8(LulBufferAddr, LucReadData);

  break;
  case FLS_TWO:
    /* Reading the data from source address */
    LusReadData = FLS_DF_READ16(LulSrcAddr);
    /* Writing the data to application buffer */
    FLS_DF_WRITE16(LulBufferAddr, LusReadData);

  break;
  case FLS_THREE:
    /* Reading the data from source address */
    LusReadData = FLS_DF_READ16(LulSrcAddr);
    /* Writing the data to application buffer */
    FLS_DF_WRITE16(LulBufferAddr, LusReadData);
    LulBufferAddr = LulBufferAddr + (uint32)FLS_TWO;
    LulSrcAddr = LulSrcAddr + (uint32)FLS_TWO;
    /* Reading the data from source address */
    LucReadData = FLS_DF_READ8(LulSrcAddr);
    /* Writing the data to application buffer */
    FLS_DF_WRITE8(LulBufferAddr, LucReadData);
    /* END Msg(2:2814)-1 */
    /*END Msg(4:0303)-1 */
  break;
  default:
  /* QAC Warning: START Msg(2:2016)-3 */
  break;
  }
  /* END Msg(2:2016)-3 */
}/* End of function Fls_FcuOffsetDataCopy */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuErasePreCheck
**
** Service ID                : NA
**
** Description               : Function to Check if Erase Job shall be initiated
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : Re-entrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Fls_FcuStatusType
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : FSTATR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_177 */
/* Implements: FLS250 */
/* Implements: SWS_Fls_00250 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuErasePreCheck(void)
{
  Fls_FcuStatusType LenStatus;
  /* Checking against error bits */
  /* QAC Warning: START Msg(2:2814)-1 */


  return(LenStatus);
}
/* End of function Fls_FcuErasePreCheck */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuCheckJobStatus
**
** Service ID                : NA
**
** Description               : This function is called from Fls_MainFunction,
**                             when the command is Erase Operation/ Write
**                             operation.This function checks if the FACI is
**                             ready to accept a new command and checks if any
**                             error bits are set after completion of a job.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Fls_FcuStatusType(FLS_FCU_BUSY, FLS_FCU_OK,
**                             FLS_FCU_ERR_WRITE, FLS_FCU_ERR_ERASE)
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.enDFStatus,Fls_GstVar.enCommand
**                             Fls_GblJobSuspendRequest
**
** Function(s) invoked       : Fls_FcuSwitchMode,Fls_ProcessSuspend
**
** Registers Used            : FSTATR,DCSTCm,DCSTm,FHVE3,FHVE15,FSADDR,FEADDR,
**                             FENTRYR,FASTAT,DCENm,DTCTm,ICFLENDNM
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_178 */
/* Implements: FLS250, FLS251 */
/* Implements: SWS_Fls_00250, SWS_Fls_00251 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuCheckJobStatus(void)
{
  /* Variable to hold the Register value */
  uint32 LulRegValue;
  /* Return variable to store DF Status*/
  Fls_FcuStatusType LenStatus = FLS_FCU_BUSY;

  /* Store the DF Status */
  Fls_GstVar.enDFStatus = LenStatus;

  return(LenStatus);
}/* End of function Fls_FcuCheckJobStatus */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuCheckBCJobStatus
**
** Service ID                : NA
**
** Description               : This function is called from Fls_MainFunction,
**                             when the command is Read Operation.
**                             This function checks if the FACI is ready to
**                             accept a new command.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : NA
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Fls_FcuStatusType
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : Fls_GstVar.enDFStatus
**
** Function(s) invoked       : None
**
** Registers Used            : FSTATR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_179*/
/* Implements: FLS256 */
/* Implements: SWS_Fls_00256 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuCheckBCJobStatus(void)
{
  /* Variable to hold the Register value */
  volatile uint32 LulRegValue;
  /* Return variable to store DF Status*/
  Fls_FcuStatusType LenStatus;
  /* Get the register value */

  return(LenStatus);
}/* End of function Fls_FcuCheckBCJobStatus */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuBlankCheckResult
**
** Service ID                : NA
**
** Description               : This function is to the status of Blank Check
**                             Operation
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
** Return parameter          : LenBCStatus
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : None
**
** Registers Used            : FBCSTAT
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_180*/
/* Implements: : AR_PN0072_FR_0040, AR_PN0072_FR_0050, AR_PN0072_FR_0049 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuBlankCheckResult(void)
{
  /* Variable to hold the Register value */
  volatile uint32 LulRegValue;
  /* Variable to hold the status of Blank Check Job*/
  Fls_FcuStatusType LenBCStatus;



  return(LenBCStatus);

}/* End of function Fls_FcuBlankCheckResult */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
** Function Name             : Fls_FcuPerformBlankCheck
**
** Service ID                : NA
**
** Description               : This function performs the blank check operation.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : NA
**
** Input Parameters          : LulStartAddr,Luscount
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : Fls_FcuSwitchMode,FLS_FCU_DF_ISSUE_BYTE_CMD
**
** Registers Used            : FSADDR,FEADDR
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_124*/
/* Implements: : AR_PN0072_FR_0040, AR_PN0072_FR_0050, AR_PN0072_FR_0049 */
FUNC(Fls_FcuStatusType, FLS_PRIVATE_CODE) Fls_FcuPerformBlankCheck
(
  const uint32 LulStartAddr,
  const uint32 Luscount
)
{
  Fls_FcuStatusType LenStatus;
  /* QAC Warning: START Msg(2:3204)-2 */
  uint32 LulEndAddr;
  /* END Msg(2:3204)-2 */



  return(LenStatus);
}/* End of function Fls_FcuPerformBlankCheck */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/*******************************************************************************
** Function Name             : Fls_FcuResetErrorBits
**
** Service ID                : NA
**
** Description               : This function clears the error bits
**                            (erasure error or program error) by issuing Status
**                             Clear Command
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : Non-Reentrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : Std_ReturnType
**
** Return parameter          : LucReturnValue
**
** Preconditions             : None
**
** Global Variables Used     : None
**
** Function(s) invoked       : Fls_FcuSwitchMode,Fls_FcuClearStatus
**
** Registers Used            : None
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/* Implements: FLS_ESDD_UD_181*/
/* Implements: FLS249, FLS250, FLS252 */
/* Implements: SWS_Fls_00249, SWS_Fls_00250, SWS_Fls_00252 */
FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_FcuResetErrorBits(void)
{
  /* Variable to store return variable */
  Std_ReturnType LucReturnValue = E_OK;
  Fls_FcuStatusType LenStatus;
  /* Switching to P/E Mode */
  LenStatus = Fls_FcuSwitchMode(FLS_FCU_MODE_PE);

  if (FLS_FCU_OK == LenStatus)
  {
    /* Issue Clear Status command */
    Fls_FcuClearStatus();

    /* Switching to USER Mode */
    LenStatus = Fls_FcuSwitchMode(FLS_FCU_MODE_USER);
    if (FLS_FCU_OK != LenStatus)
    {
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* do nothing*/
    }
  }
  else
  {
    LucReturnValue = E_NOT_OK;
  }

  return(LucReturnValue);
} /* End of function Fls_FcuResetErrorBits */

#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */

/*******************************************************************************
** Function Name            : Fls_FcuReturnFromCmdLock
**
** Service ID               : NA
**
** Description              : This function Check ILGLERR, DFAE bits and write
**                            DFAE bit if required.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : None
**
** Function(s) invoked      : None
**
** Registers Used           : FSTATR,FASTAT
*******************************************************************************/
#define FLS_START_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
 /* Implements FLS_ESDD_UD_123, FLS_ESDD_UD_253 */
FUNC(void, FLS_PRIVATE_CODE) Fls_FcuReturnFromCmdLock(void)
{
  /*  Checking ILGLERR bit */
  /* QAC Warning: START Msg(2:2814)-1 */

}/* End of function Fls_FcuReturnFromCmdLock */
#define FLS_STOP_SEC_PRIVATE_CODE
/* MISRA Violation: START Msg(2:0832)-2 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-2 */
/*******************************************************************************
**                           End of File                                      **
*******************************************************************************/
