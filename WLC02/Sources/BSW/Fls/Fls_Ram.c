/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Ram.c                                                   */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015-2018 Renesas Electronics Corporation                     */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision of Global variable definitions for Flash Wrapper Component.      */
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
 * V1.1.0:  04-Dec-2015  :  As a part of F1K 4.00.01 release following changes
 *                          are made:
 *                          1. Added variables Fls_GstFcuVar, Fls_GstBackUpVar
 *                             Fls_GenJobResult, Fls_GenState,
 *                             Fls_GblJobSuspended, Fls_VerifyCompletedJob,
 *                             Fls_GulTimeOutCounter, Fls_GbIntrRqstFlag,
 *                             Fls_GblFlashEnable.
 *                          2. Removed variable Fls_GVar.
 *                          3. Compiler Arguments of Fls_GblInitStatus,
 *                             Fls_GstVar,Fls_GenCurrentMode has been updated
 *
 * V1.1.1:  27-sep-2016  : #ARDAABD-786
 *                         1. Changed type qualifiers to volatile for following
 *                            global variables: Fls_GstVar, Fls_GenJobResult,
 *                            Fls_GenState, Fls_GblTimeOutMonitor,
 *                            Fls_GblFlashEnable, Fls_VerifyCompletedJob,
 *                            Fls_GulTimeOutCounter
 *                         #ARDAABD-418
 *                         1. Module's initialized status variable was not
 *                            declared if det was off.
 *
 * V1.2.1:  28-Sep-2016  :  #ARDAABD-843
 *                          1. Removed support for
 *                             FLS_AR_HIGHER_VERSION / FLS_AR_LOWER_VERSION
 *                          2. Removed AR 3.2.2 memory sections support
 *
 * V2.0.0:  11-Nov-2016  :  1. #ARDAABD-732 - Added Fls_GpDmaUnitConfig
 *                          2. #ARDAABD-941 - Added Fls_GblJobSuspendRequest
 *                          3. #ARDAABD-786 - Fls_GulTimeOutCounter no more
 *                             volatile
 *
 * V2.0.1:  05-Jan-2017  :  1. #ARDAABD-786 - Fls_GulTimeOutCounter changed to
 *                             volatile
 *
 * V2.0.2:  09-Jan-2017  :  #ARDAABD-786
 *                          1. Fls_GstBackUpVar and Fls_GblJobSuspended changed
 *                             to volatile
 *
 * V2.0.3:  10-Jan-2017  :  #ARDAABD-786
 *                          1. Fls_GblFlashEnable removed volatile qualifier
 *
 * V2.1.0:  30-Jan-2017  :  #ARDAABD-571
 *                          1. Addded MemMap_Fls vs MemMap.h inclusion based on
 *                             AR revision.
 *                          2. Added Fls_HWCheckConsistency API related data.
 *                          3. Changes after review.
 *                          4. FPCKAR register no more RAM mirrored.
 *                          5. FCURAME register no more RAM mirrored.
 *
 * V2.1.1:  14-Feb-2017  :  #ARDAABD-571
 *                          1. Fixed acceptance findings.
 *
 * V2.2.2:  28-Feb-2017  :  #ARDAABD-1294
 *                          1. DMA's DTC & DSA registers no more Ram mirrored.
 * V2.2.3:  20-Jul-2017  :  #ARDAABD-1246 - Removed Firmware copy support.
 * V2.2.4:  24-Aug-2017  :  #ARDAABD-2151 - Added QAC/MISRA Warnings
 *                          justification.Corrected QAC/MISRA Warning
 * V2.2.5:  25-Sep-2017  :  #ARDAABD-2370 corrected variables naming convention.
 *
 * V2.2.6:  20-Jun-2018  :  Following changes are made:
 *                          1. As part of merging activity, #ARDAABD-3465
 *                             below changes are made(Ref : ARDAABD-908):
 *                           a. FLS_START_SEC_VAR_UNSPECIFIED has been
 *                              changed to FLS_START_SEC_VAR_INIT_UNSPECIFIED
 *                              and FLS_STOP_SEC_VAR_UNSPECIFIED has been
 *                              changed to FLS_STOP_SEC_VAR_INIT_UNSPECIFIED.
 *                           b. FLS_START_SEC_VAR_BOOLEAN has been
 *                              changed to FLS_START_SEC_VAR_INIT_BOOLEAN
 *                              and FLS_STOP_SEC_VAR_BOOLEAN has been
 *                              changed to FLS_STOP_SEC_VAR_INIT_BOOLEAN.
 *                           c. As per ARDAABD-3853, traceability has been
 *                              improved.
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Included for macro definitions and API prototypes */
#include "Fls.h"
/* Included for RAM variable declarations */
#include "Fls_Ram.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Release version information */
#define FLS_RAM_C_AR_RELEASE_MAJOR_VERSION      \
              FLS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLS_RAM_C_AR_RELEASE_MINOR_VERSION      \
              FLS_AR_RELEASE_MINOR_VERSION_VALUE
#define FLS_RAM_C_AR_RELEASE_REVISION_VERSION   \
              FLS_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FLS_RAM_C_SW_MAJOR_VERSION              FLS_SW_MAJOR_VERSION_VALUE
#define FLS_RAM_C_SW_MINOR_VERSION              FLS_SW_MINOR_VERSION_VALUE

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (FLS_RAM_AR_RELEASE_MAJOR_VERSION != FLS_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fls_Ram.c : Mismatch in Release Major Version"
#endif

#if (FLS_RAM_AR_RELEASE_MINOR_VERSION != FLS_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Fls_Ram.c : Mismatch in Release Minor Version"
#endif

#if (FLS_RAM_AR_RELEASE_REVISION_VERSION != \
                                          FLS_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Fls_Ram.c : Mismatch in Release Revision Version"
#endif


#if (FLS_RAM_SW_MAJOR_VERSION != FLS_RAM_C_SW_MAJOR_VERSION)
  #error "Fls_Ram.c : Mismatch in Software Major Version"
#endif

#if (FLS_RAM_SW_MINOR_VERSION != FLS_RAM_C_SW_MINOR_VERSION)
  #error "Fls_Ram.c : Mismatch in Software Minor Version"
#endif

/*******************************************************************************
**                       MISRA C Rule Violations                              **
*******************************************************************************/
/* 1.  MISRA C RULE VIOLATION:                                                */
/* Message       : (2:0832) Macro substitution in #include preprocessing      */
/*                 directive.                                                 */
/* Rule          : No MISRA-C:2004 Rule                                       */
/* Justification : Required to optimize MemMap inclusion because of ASR403    */
/*                 and ASR422 support.                                        */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:0832)-1 and                           */
/*                 END Msg(2:0832)-1 tags in the code.                        */
/******************************************************************************/
/* 2.  MISRA C RULE VIOLATION:                                                */
/* Message       : (2:0862) This #include '' directive is redundant.          */
/* Rule          : No MISRA-C:2004 Rule                                       */
/* Justification : Each header has implemented safety for multiple inclusion. */
/*                 Header will not be included multiple times.                */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:0862)-2 and                           */
/*                 END Msg(2:0862)-2 tags in the code.                        */
/*******************************************************************************
**                         QAC Warning                                        **
*******************************************************************************/

/* 1. QAC Warning:                                                            */
/* Message      : (2:2022) This is a tentative definition and according to    */
/*                the ISO:C Standard, the object will automatically be        */
/*                initialized to zero.                                        */
/* Justification: The object's initialisation to zero will not affect the     */
/*                functionality.                                              */
/* Verification : However, part of the code is verified                       */
/*                manually and it is not having any impact                    */
/* Reference    : Look for START Msg(2:2022)-1 and                            */
/*                END Msg(2:2022)-1 tags in the code.                         */
/******************************************************************************/

/* 2. QAC Warning:                                                            */
/* Message      : (2:3211) The global identifier 'Fls_GpConfigPtr' is defined */
/*                here but is not used in this translation unit.              */
/* Justification: As per AUTOSAR, all global variables extern declaration     */
/*                shall be given in Fls_Ram.h                                 */
/* Verification : However, part of the code is verified                       */
/*                manually and it is not having any impact                    */
/* Reference    : Look for START Msg(2:3211)-2 and                            */
/*                END Msg(2:3211)-2 tags in the code.                         */
/******************************************************************************/
/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/
/* MISRA Violation: START Msg(2:0862)-2 */
#define FLS_START_SEC_VAR_NO_INIT_UNSPECIFIED
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */
/* QAC Warning: START Msg(2:2022)-1 */
/* QAC Warning: START Msg(2:3211)-2 */
/* Implements: EAAR_PN0034_FR_0021*/
/* Implements: FLS_ESDD_UD_234*/
/* FCU Data Global Structure Declaration */
VAR(Fls_FcuDataType, FLS_VAR_NOINIT)Fls_GstFcuVar;

/* Implements: FLS_ESDD_UD_219, FLS_ESDD_UD_051, FLS_ESDD_UD_002 */
P2CONST(Fls_ConfigType, FLS_VAR, FLS_CONFIG_CONST) Fls_GpConfigPtr;
#if (FLS_SET_MODE_API == STD_ON)
/* Implements: FLS_ESDD_UD_220*/
/* Global pointer variable for DMA channel configuration */
P2CONST(Fls_DmaUnitConfig, FLS_VAR, FLS_CONFIG_CONST)Fls_GpDmaUnitConfig;
#endif /* FLS_SET_MODE_API == STD_ON */

/* Implements: FLS_ESDD_UD_235 */
/* Structure variable that contains FLS Global variables */
VAR(volatile Fls_GstVarProperties, FLS_VAR_NOINIT) Fls_GstVar;

#if ((FLS_SUSPEND_API == STD_ON) || (FLS_RESUME_API == STD_ON))
/* Implements: FLS_ESDD_UD_233*/
/* Structure variable to Back Up Global Variables in case of Job Suspend */
VAR(volatile Fls_GstVarProperties, FLS_VAR_NOINIT) Fls_GstBackUpVar;
#endif

#define FLS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */

#define FLS_START_SEC_VAR_INIT_UNSPECIFIED
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */

/* Implements: FLS_ESDD_UD_232*/
/* Implements: FLS248, FLS322*/
/* Variable to store the job result */
VAR(volatile MemIf_JobResultType, FLS_VAR) Fls_GenJobResult = MEMIF_JOB_OK;

/* Implements: FLS_ESDD_UD_231*/
/* Implements: FLS248, FLS322*/
/* Variable to store the driver state */
VAR(volatile MemIf_StatusType, FLS_VAR) Fls_GenState = MEMIF_UNINIT;

/* Implements: FLS_ESDD_UD_230*/
/* Implements: FLS248, FLS322*/
/* Variable to Hold the Current Mode */
VAR(MemIf_ModeType, FLS_VAR) Fls_GenCurrentMode = MEMIF_MODE_SLOW;

#define FLS_STOP_SEC_VAR_INIT_UNSPECIFIED
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */


#define FLS_START_SEC_VAR_INIT_BOOLEAN
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */
/* /Implements: FLS_ESDD_UD_050*/
/* Variable to store the module initialization status */
VAR(boolean, FLS_VAR) Fls_GblInitStatus = FLS_UNINITIALIZED;
#if (FLS_TIMEOUT_MONITORING == STD_ON)
/* Implements: AR_PN0072_FR_0059*/
/* Implements: FLS_ESDD_UD_229*/
VAR(volatile boolean, FLS_VAR) Fls_GblTimeOutMonitor = FLS_FALSE;
#endif
#define FLS_STOP_SEC_VAR_INIT_BOOLEAN
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */


#define FLS_START_SEC_VAR_NO_INIT_BOOLEAN
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */

#if (FLS_FHVE_REGS == SUPPORTED)
/* Implements: FLS_ESDD_UD_263*/
/* Variable to store the flash enable / protection off status */
VAR(boolean, FLS_VAR_NOINIT) Fls_GblFlashEnable;
#endif /* end of #if (FLS_FHVE_REGS == SUPPORTED) */

#if ((FLS_SUSPEND_API == STD_ON) || (FLS_RESUME_API == STD_ON))
/* Implements: FLS_ESDD_UD_224*/
/* Variable to store the Job Suspended state */
VAR(volatile boolean, FLS_VAR_NOINIT) Fls_GblJobSuspended;
#endif
#if (FLS_SUSPEND_API == STD_ON)
/* Implements: FLS_ESDD_UD_221*/
VAR(volatile boolean, FLS_VAR_NOINIT) Fls_GblJobSuspendRequest;
#endif
#if (FLS_DEV_ERROR_DETECT == STD_ON)
/* Implements: FLS_ESDD_UD_223*/
VAR(volatile boolean, FLS_VAR_NOINIT) Fls_GblVerifyCompletedJob;
#endif

#define FLS_STOP_SEC_VAR_NO_INIT_BOOLEAN
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */


#define FLS_START_SEC_VAR_NO_INIT_32
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */
#if (FLS_TIMEOUT_MONITORING == STD_ON)
/* Implements: FLS_ESDD_UD_222*/
VAR(volatile uint32, FLS_VAR_NOINIT) Fls_GulTimeOutCounter;
#endif

#if (FLS_RAM_MIRROR == FLS_MIRROR_ENABLE)
/* Implements: FLS_ESDD_UD_242*/
/* Variable to store the registers values in RAM  */
/* must be initialized with registers values after reset */
VAR(uint32, FLS_VAR_NOINIT)Fls_GaaRamMirror[FLS_NB_OF_MIRRORED_REGS]=
{
  (uint32)FLS_DFERRINT_RESET_VAL, /* RAM_IDX_DFERRINT  */
  (uint32)FLS_DFERSTR_RESET_VAL,  /* RAM_IDX_DFERSTR   */
  (uint32)FLS_FASTAT_RESET_VAL,   /* RAM_IDX_FASTAT    */
  (uint32)FLS_FEADDR_RESET_VAL,           /* RAM_IDX_FEADDR    */
  (uint32)FLS_FENTRYR_RESET_VAL,  /* RAM_IDX_FENTRYR   */
  FLS_FSADDR_RESET_VAL,           /* RAM_IDX_FSADDR    */
  (uint32)FLS_FEADDR_RESET_VAL /* RAM_IDX_FPCKAR    */

#if (                                     \
      (FLS_SET_MODE_API == STD_ON) &&     \
      (FLS_DMA_INSTANCES > FLS_DMA_ZERO)  \
    )
  ,FLS_DMA_DTCT_RESET_VALUE /* RAM_IDX_DTCT      */
  ,FLS_DMA_DCEN_RESET_VAL /* RAM_IDX_DCEN      */
#endif /* End #if ((FLS_SET_MODE_API == STD_ON) &&
 (FLS_DMA_INSTANCES > FLS_DMA_ZERO)) */
};
#endif

#define FLS_STOP_SEC_VAR_NO_INIT_32
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */
#if (FLS_INTERRUPT_MODE == STD_ON)

#define FLS_START_SEC_VAR_INIT_BOOLEAN
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */
/*Implements: FLS_ESDD_UD_243*/
/* Variable to store the Interrupt request flag status */
VAR(boolean, FLS_VAR) Fls_GblIntrRqstFlag = FLS_ZERO;
/* END Msg(2:3211)-2 */
/* END Msg(2:2022)-1 */
#define FLS_STOP_SEC_VAR_INIT_BOOLEAN
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */
#endif /* #if (FLS_INTERRUPT_MODE == STD_ON) */
/* END Msg(2:0862)-2 */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
