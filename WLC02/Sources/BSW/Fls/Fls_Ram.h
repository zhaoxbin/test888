/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Ram.h                                                   */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015-2018 Renesas Electronics Corporation                     */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains Global variable declarations of FLS Driver              */
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
 *                          1. Added variables Fls_FcuGstVar, Fls_GstBackUpVar
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
 * V2.0.0:  11-Nov-2016  :  1. #ARDAABD-732 - Added Fls_GpDmaUnitConfig, defined
 *                             RAM mirror ID's for DMA registers.
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
 * V2.0.4:  16-Jan-2017  :  #ARDAABD-459 Defined RAM_MASK_DCEN, RAM_MASK_DTFR
 *                             and RAM_MASK_DTCT masks.
 *
 * V2.0.5:  31-Jan-2017  :  #ARDAABD-571
 *                          1. Dma RAM indexes macros only when Dma enabled.
 *                          2. FPCKAR register no more RAM mirrored.
 *                          3. FCURAME register no more RAM mirrored.
 *                          4. Improve FLS_NB_OF_MIRRORED_REGS macro generation.
 *
 * V2.0.6:  28-Feb-2017  :  #ARDAABD-571
 *                          1. Fixed acceptance findings.
 *                          2. Fixed review findings.
 *                          3. Added RAM_MASK_FLS_ICFLENDNM macro.
 *
 * V2.0.7:  28-Feb-2017  :  #ARDAABD-1294
 *                          1. DMA's DTC & DSA registers no more Ram mirrored.
 * V2.0.8:  20-Jul-2017  :  #ARDAABD-1246 - Removed Firmware copy support.
 *                          #ARDAABD-1325 - Corrected RAM_MASK_FASTAT value.
 * V2.0.9:  25-Sep-2017  :  #ARDAABD-2370: corrected variables naming convention
 *
 * V2.0.10: 12-Jul-2018  :  Following changes are made:
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
 *                           c. Added MISRA C RULE VIOLATION tag for
 *                              Msg(4:0828).
 *                           d. As per ARDAABD-3853, traceability has been
 *                              improved.
 */
/******************************************************************************/
#ifndef FLS_RAM_H
#define FLS_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fls_Types.h"
/* Included for macro definitions for RAM MIRRORING*/
#include "Fls_Cfg.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Release version information */
#define FLS_RAM_AR_RELEASE_MAJOR_VERSION      FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_RAM_AR_RELEASE_MINOR_VERSION      FLS_AR_RELEASE_MINOR_VERSION
#define FLS_RAM_AR_RELEASE_REVISION_VERSION   FLS_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FLS_RAM_SW_MAJOR_VERSION              FLS_SW_MAJOR_VERSION
#define FLS_RAM_SW_MINOR_VERSION              FLS_SW_MINOR_VERSION
/*******************************************************************************
**                       MISRA C Rule Violations                              **
*******************************************************************************/
/******************************************************************************/

/* 1. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:0828) More than 8 levels of nested conditional          */
/*                 inclusion - program does not conform strictly to ISO:C90.  */
/* Rule          : MISRA-C:2004 Rule 1.1                                      */
/* Justification : All levels of nested conditional checks are verified and   */
/*                 no such 8 levels are observed.                             */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:0828)-1 and                           */
/*                 END Msg(4:0828)-1 tags in the code.                        */
/*******************************************************************************
**                         Macro definition                                   **
*******************************************************************************/
#define RAM_MASK_FEADDR                     (uint32)(0xFFFFFFFCUL)
#define RAM_MASK_FENTRYR                    (uint16)(0x0081U)
#define RAM_MASK_FPCKAR                     (uint16)(0x00FFU)
#define RAM_MASK_FSADDR                     (uint32)(0xFFFFFFFCUL)
#define RAM_MASK_DCEN                       (uint32)(0x00000001UL)
#define RAM_MASK_DTFR                       (uint32)(0x000000FFUL)
#define RAM_MASK_DTCT                       (uint32)(0x0C1F7FFFUL)
#define RAM_MASK_NO_MASK                    (uint32)(0xFFFFFFFFUL)
#define RAM_MASK_FASTAT                     (uint8)(0x08U)
#define RAM_MASK_DFERRINT                   (uint8)(0x3U)
#define RAM_MASK_DFERSTR                    (uint8)(0x3U)
#define RAM_MASK_FLS_ICFLENDNM              (uint16)(0xFFFFU)

#if (FLS_RAM_MIRROR == FLS_MIRROR_ENABLE)

#define RAM_IDX_DFERRINT                    (0x00U)
#define RAM_IDX_DFERSTR                     (0x01U)
#define RAM_IDX_FASTAT                      (0x02U)
#define RAM_IDX_FEADDR                      (0x03U)
#define RAM_IDX_FENTRYR                     (0x04U)
#define RAM_IDX_FSADDR                      (0x05U)
#define RAM_IDX_FPCKAR                      (0x06U)

/* Total number of FACI mirrored registers */
#define FLS_NB_OF_FACI_MIRRORED_REGS        (0x07U)

/* MISRA Violation: START Msg(4:0828)-1 */
#if (                                     \
      (FLS_SET_MODE_API == STD_ON) &&     \
      (FLS_DMA_INSTANCES > FLS_DMA_ZERO)  \
    )

#define RAM_IDX_DTCT                        (0x07U)
#define RAM_IDX_DCEN                        (0x08U)

/* Total number of DMA mirrored registers */
#define FLS_NB_OF_DMA_MIRRORED_REGS         (0x02U)

#else /* From #if ((FLS_SET_MODE_API == STD_ON) &&
 (FLS_DMA_INSTANCES > FLS_DMA_ZERO)) */

/* Total number of DMA mirrored registers */
#define FLS_NB_OF_DMA_MIRRORED_REGS         (0x00U)

#endif /* End #if ((FLS_SET_MODE_API == STD_ON) &&
 (FLS_DMA_INSTANCES > FLS_DMA_ZERO)) */

/* END Msg(4:0828)-1 */
/* Total number of mirrored registers */
#define FLS_NB_OF_MIRRORED_REGS                   \
  (                                               \
    FLS_NB_OF_FACI_MIRRORED_REGS  +               \
    FLS_NB_OF_DMA_MIRRORED_REGS                   \
  )

#endif /* #if (FLS_RAM_MIRROR == FLS_MIRROR_ENABLE) */

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* FLS_RAM_H_001: EAAR_PN0034_FR_0019, EAAR_PN0034_FR_0021*/
#define FLS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include FLS_MEMMAP_FILE
/* FLS_RAM_H_002: FLS_ESDD_UD_219    */
/* Global variable to store pointer to Configuration */
extern P2CONST(Fls_ConfigType, FLS_VAR, FLS_CONFIG_CONST) Fls_GpConfigPtr;
#if (FLS_SET_MODE_API == STD_ON)
/* FLS_RAM_H_003: FLS_ESDD_UD_220   */
/* Global pointer variable for HW group configuration */
extern P2CONST(Fls_DmaUnitConfig, FLS_VAR, FLS_CONFIG_CONST)Fls_GpDmaUnitConfig;
#endif /* FLS_SET_MODE_API == STD_ON */

/* FLS_RAM_H_004: FLS_ESDD_UD_235   */
/* Structure variable that contains FLS Global variables */
extern VAR(volatile Fls_GstVarProperties, FLS_VAR_NOINIT) Fls_GstVar;

/* FLS_RAM_H_005: FLS_ESDD_UD_234    */
/* FCU Data Global Structure Declaration */
extern VAR(Fls_FcuDataType, FLS_VAR_NOINIT)Fls_GstFcuVar;

#if ((FLS_SUSPEND_API == STD_ON) || (FLS_RESUME_API == STD_ON))
/* FLS_RAM_H_006: FLS_ESDD_UD_233    */
/* Structure variable to Back Up Global Variables in case of Job Suspend */
extern VAR(volatile Fls_GstVarProperties, FLS_VAR_NOINIT) Fls_GstBackUpVar;
#endif

#define FLS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_VAR_INIT_UNSPECIFIED
#include FLS_MEMMAP_FILE

/* FLS_RAM_H_007: FLS_ESDD_UD_232    */
/* Variable to store the job result */
extern VAR(volatile MemIf_JobResultType, FLS_VAR) Fls_GenJobResult;

/* FLS_RAM_H_008: FLS_ESDD_UD_231    */
/* Variable to store the driver state */
extern VAR(volatile MemIf_StatusType, FLS_VAR) Fls_GenState;

/* FLS_RAM_H_009: FLS_ESDD_UD_230   */
/* Variable to Hold the Current Mode */
extern VAR(MemIf_ModeType, FLS_VAR) Fls_GenCurrentMode;

#define FLS_STOP_SEC_VAR_INIT_UNSPECIFIED
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_VAR_INIT_BOOLEAN
#include FLS_MEMMAP_FILE
/* FLS_RAM_H_010: FLS_ESDD_UD_050    */
/* Declaration of variable that stores the module initialization status */
extern VAR(boolean, FLS_VAR) Fls_GblInitStatus;
#if (FLS_TIMEOUT_MONITORING == STD_ON)
/* FLS_RAM_H_011: FLS_ESDD_UD_229    */
extern VAR(volatile boolean, FLS_VAR) Fls_GblTimeOutMonitor;
#endif
#define FLS_STOP_SEC_VAR_INIT_BOOLEAN
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_VAR_NO_INIT_BOOLEAN
#include FLS_MEMMAP_FILE
#if (FLS_FHVE_REGS == SUPPORTED)
/* FLS_RAM_H_012: FLS_ESDD_UD_225    */
/* Variable to store the flash enable / protection off status */
extern VAR(boolean, FLS_VAR_NOINIT) Fls_GblFlashEnable;
#endif /* end of #if (FLS_FHVE_REGS == SUPPORTED) */

#if ((FLS_SUSPEND_API == STD_ON) || (FLS_RESUME_API == STD_ON))
/* Variable to store the Job Suspended state */
/* FLS_RAM_H_013: FLS_ESDD_UD_224    */
extern VAR(volatile boolean, FLS_VAR_NOINIT) Fls_GblJobSuspended;
#endif
#if (FLS_SUSPEND_API == STD_ON)
/* FLS_RAM_H_014: FLS_ESDD_UD_224   */
extern VAR(volatile boolean, FLS_VAR_NOINIT) Fls_GblJobSuspendRequest;
#endif
/* FLS_RAM_H_015: FLS_ESDD_UD_223   */
extern VAR(volatile boolean, FLS_VAR_NOINIT) Fls_GblVerifyCompletedJob;
#define FLS_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_VAR_NO_INIT_32
#include FLS_MEMMAP_FILE
#if (FLS_TIMEOUT_MONITORING == STD_ON)
/* FLS_RAM_H_016: FLS_ESDD_UD_222   */
extern VAR(volatile uint32, FLS_VAR_NOINIT) Fls_GulTimeOutCounter;
#endif

#if (FLS_RAM_MIRROR == FLS_MIRROR_ENABLE)
/* FLS_RAM_H_017: FLS_ESDD_UD_242   */
extern VAR(uint32, FLS_VAR_NOINIT)Fls_GaaRamMirror[FLS_NB_OF_MIRRORED_REGS];
#endif

#define FLS_STOP_SEC_VAR_NO_INIT_32
#include FLS_MEMMAP_FILE

#if (FLS_INTERRUPT_MODE == STD_ON)

#define FLS_START_SEC_VAR_INIT_BOOLEAN
#include FLS_MEMMAP_FILE
/* FLS_RAM_H_018: FLS_ESDD_UD_243   */
/* Variable to store the Interrupt request flag status */
extern VAR(boolean, FLS_VAR) Fls_GblIntrRqstFlag;
#define FLS_STOP_SEC_VAR_INIT_BOOLEAN
#include FLS_MEMMAP_FILE

#endif /* #if (FLS_INTERRUPT_MODE == STD_ON) */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif  /* FLS_RAM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
