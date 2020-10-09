/*============================================================================*/
/* Project      = AUTOSAR Renesas X1X MCAL Components                         */
/* Module       = Fls_RegWrite.h                                              */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2016-2018 Renesas Electronics Corporation                     */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains the macro definitions of Pwrite verify and hardware     */
/* consistency check functionallity                                           */
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
 * V1.0.0  17-Aug-2016:  Initial Version
 * V1.0.1  24-Aug-2017:  #ARDAABD-2151 - Added QAC/MISRA Warnings justification.
 *                       Corrected QAC/MISRA Warning.
 * V1.0.2  16-Oct-2017:  #ARDAABD-2552 - Dem_ReportErrorStatus interface has
 *                       been replaced by Det_ReportRuntimeError for AUTOSAR
 *                       version 4.2.2.
 * V1.0.3  20-Jun-2018:  Following changes are made:
 *                          1. As part of merging activity, #ARDAABD-3465
 *                             below changes are made(Ref : ARDAABD-908):
 *                           a. Misra Violation tag for Message Msg(4:3453)is
 *                              added and corrected the End tag for Msg(4:3412).
 *                           b. Inserted a one space character after 'if'
 *                              statement.
 *                           c. Copyright information has been updated.
 *                           d. As per ARDAABD-3853, traceability has been
 *                              improved.
 */
/******************************************************************************/

#ifndef FLS_REGWRITE_H
#define FLS_REGWRITE_H

/*******************************************************************************
**                      Version Information                                  **
*******************************************************************************/
/*******************************************************************************
**                       MISRA C Rule Violations                              **
*******************************************************************************/
/* 1. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:3412) Macro defines an unrecognized code-fragment.      */
/* Rule          : MISRA-C:2004 Rule 19.4                                     */
/* Justification : Needed terminator token for macro code line                */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:3412)-1 and                           */
/*                 END Msg(4:3412)-1 tags in the code.                        */

/* 2. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:3453) A function could probably be used instead of this */
/*                 function-like macro.                                       */
/* Rule          : MISRA-C:2004 Rule 19.7                                     */
/* Justification : Necessary for the practical extension of functionality to  */
/*                  multiple registers                                        */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:3453)-2 and                           */
/*                 END Msg(4:3453)-2 tags in the code.                        */

/* 3. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:3458) Macro defines a braced code statement block.      */
/* Rule          : MISRA-C:2004 Rule 19.4                                     */
/* Justification : Necessary for defining a new scope                         */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:3458)-3 and                           */
/*                 END Msg(4:3458)-3 tags in the code.                        */
/******************************************************************************/

/******************************************************************************/
/***************************Register Write and RAM Mirroring*******************/
/******************************************************************************/
/*******************************************************************************
** Macro Name            : FLS_WRITE_REG_ONLY
**
** Description           : This macro is to perform the write operation to the
**                         register which is passed. This macro shall be used
**                         for registers for witch Ram Mirroring is not possible
**                         (Write-Only or Static registers)
**
** Input Parameters      : pWriteRegAddr, uiRegWriteValue
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : None
**
** Functions invoked     : None
*******************************************************************************/
/* MISRA Violation: START Msg(4:3458)-3 */
#define FLS_WRITE_REG_ONLY(pWriteRegAddr, uiRegWriteValue)  \
{ \
  (*(pWriteRegAddr)) = (uiRegWriteValue); \
}
/* END Msg(4:3458)-3 */

/*******************************************************************************
** Macro Name            : INTERNAL_FLS_WRITE_REG_AND_MIRROR
**
** Description           : This macro is to perform the write operation to the
**                         register and respective RAM mirroring
**
** Input Parameters      : pWriteRegAddr, pMirrorAddr, uiRegWriteValue
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : RAM Mirror ON
**
** Functions invoked     : None
*******************************************************************************/
/* MISRA Violation: START Msg(4:3458)-3 */
#define INTERNAL_FLS_WRITE_REG_AND_MIRROR(pWriteRegAddr,\
pMirrorAddr, uiRegWriteValue) \
{ \
  (*(pWriteRegAddr)) = (uiRegWriteValue); \
  (*(pMirrorAddr)) = (uint32)(uiRegWriteValue); \
}
/* END Msg(4:3458)-3 */
/*******************************************************************************
** Macro Name            : FLS_WRITE_REG_AND_MIRROR
**
** Description           : This macro is to do the write and RAM mirroring for
**                         FlsTst registers. This macro shall not be used for
**                         registers for witch Ram Mirroring is impossible.
**
** Input Parameters      : pWriteRegAddr, uiRegWriteValue, pMirrorAddr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : None
**
** Functions invoked     : None
*******************************************************************************/

#if (FLS_RAM_MIRROR == FLS_MIRROR_ENABLE)
/* QAC Warning: START Msg(2:3457)-1 */
/* MISRA Violation: START Msg(4:3453)-2 */
#define FLS_WRITE_REG_AND_MIRROR(pWriteRegAddr, uiRegWriteValue, pMirrorAddr)  \
     INTERNAL_FLS_WRITE_REG_AND_MIRROR(pWriteRegAddr, \
      pMirrorAddr, uiRegWriteValue )
/* END Msg(2:3457)-1 */
#else
#define FLS_WRITE_REG_AND_MIRROR(pWriteRegAddr, uiRegWriteValue, pMirrorAddr) \
     FLS_WRITE_REG_ONLY(pWriteRegAddr, uiRegWriteValue)
/* END Msg(4:3453)-2 */
#endif

/******************************************************************************/
/******************************WRITE-VERIFY MACROS*****************************/
/******************************************************************************/

/*******************************************************************************
** Macro Name            : FLS_WV_REPORT_ERROR
**
** Description           : This macro is to report the error to respective
**                         interface.
**
** Input Parameters      : WVErrId, ErrStat, uiApiId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : None
**
** Functions invoked     : Dem_ReportErrorStatus, Det_ReportRuntimeError
**                         FLS_ERROR_NOTIFICATION
*******************************************************************************/
/* MISRA Violation: START Msg(4:3412)-1 */
/* FLS_REGWRITE_H_001: FLS_ESDD_UD_144, FLS_ESDD_UD_159 */
#if ( FLS_USE_WV_ERROR_INTERFACE == STD_ON )
#define FLS_WV_REPORT_ERROR(WVErrId, ErrStat, ApiId) \
            FLS_ERROR_NOTIFICATION(WVErrId, ApiId);
#else
#if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
#define FLS_WV_REPORT_ERROR(WVErrId, ErrStat, ApiId) \
        Dem_ReportErrorStatus(WVErrId, (Dem_EventStatusType)(ErrStat));
#else
#define FLS_WV_REPORT_ERROR(WVErrId, ErrStat, ApiId) \
        (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, \
                                        ApiId,  WVErrId);
#endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
#endif
/* END Msg(4:3412)-1 */
/*******************************************************************************
** Macro Name            : INTERNAL_FLS_CHECK_WRITE_VERIFY
**
** Description           : This macro is to do the comparison check and do
**                         the error reporting if the comparison fails.
**
** Input Parameters      : pCompareRegAddr, uiCheckValue, ApiId, uiMaskValue
**                         uiApiId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : None
**
** Functions invoked     : None
*******************************************************************************/
/* MISRA Violation: START Msg(4:3412)-1 */
#define INTERNAL_FLS_CHECK_WRITE_VERIFY(pCompareRegAddr,        \
        uiCheckValue, uiMaskValue, ApiId)                       \
{                                                               \
  if ((uiCheckValue) != ((*(pCompareRegAddr)) & (uiMaskValue)))  \
  {                                                             \
      FLS_WV_REPORT_ERROR(FLS_E_REG_WRITE_VERIFY,               \
                          DEM_EVENT_STATUS_FAILED,              \
                          ApiId)                                \
  }                                                             \
  else                                                          \
  {                                                             \
  }                                                             \
}
/* END Msg(4:3412)-1 */
/*******************************************************************************
** Macro Name            : FLS_CHECK_WRITE_VERIFY_INIT
**
** Description           : This macro is to do the write verify call only for
**                         FLS_Init API.
**
** Input Parameters      : pCompareRegAddr, uiCheckValue, uiMaskValue, ApiId.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : None
**
** Functions invoked     : None
*******************************************************************************/
/* MISRA Violation: START Msg(4:3453)-2 */
/* MISRA Violation: START Msg(4:3412)-1 */
/* FLS_REGWRITE_H_002: FLS_ESDD_UD_143 */
#if (FLS_WRITE_VERIFY != FLS_WV_DISABLE)
#define FLS_CHECK_WRITE_VERIFY_INIT(pCompareRegAddr,      \
        uiCheckValue, uiMaskValue, ApiId)                 \
  INTERNAL_FLS_CHECK_WRITE_VERIFY(pCompareRegAddr,        \
        uiCheckValue, uiMaskValue, ApiId)
#else
#define FLS_CHECK_WRITE_VERIFY_INIT(pCompareRegAddr,      \
        uiCheckValue, uiMaskValue, ApiId)     \
  {\
  }
#endif
/* END Msg(4:3453)-2 */
/* END Msg(4:3412)-1 */

/*******************************************************************************
** Macro Name            : FLS_CHECK_WRITE_VERIFY_RUNTIME
**
** Description           : This macro is to do the write verify call only for
**                         the API's other than FLS_Init.
**
** Input Parameters      : pCompareRegAddr, uiCheckValue, uiMaskValue, ApiId.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : None
**
** Functions invoked     : None
*******************************************************************************/
/* MISRA Violation: START Msg(4:3412)-1 */
/* MISRA Violation: START Msg(4:3453)-2 */
#if (FLS_WRITE_VERIFY == FLS_WV_INIT_RUNTIME)
#define FLS_CHECK_WRITE_VERIFY_RUNTIME(pCompareRegAddr, \
              uiCheckValue, uiMaskValue, ApiId)         \
  INTERNAL_FLS_CHECK_WRITE_VERIFY(pCompareRegAddr,      \
              uiCheckValue, uiMaskValue, ApiId)
#else
#define FLS_CHECK_WRITE_VERIFY_RUNTIME(pCompareRegAddr, \
              uiCheckValue, uiMaskValue, ApiId )        \
  {                                                     \
  }
#endif
/* END Msg(4:3453)-2 */
/* END Msg(4:3412)-1 */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* FLS_REGWRITE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
