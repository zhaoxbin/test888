/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Version.c                                               */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015 - 2017 Renesas Electronics Corporation                   */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains code for version checking for modules included by FLS   */
/* Driver                                                                     */
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
 * V1.1.0:  28-Sep-2016  :  #ARDAABD-843
 *                          1. Removed support for
 *                             FLS_AR_HIGHER_VERSION / FLS_AR_LOWER_VERSION
 * V1.1.1:  31-Aug-2017  : ARDAABD-2151 - Corrected QAC/MISRA Warning.
 * V1.1.2:  16-Oct-2017  : ARDAABD-2552 - Added AUTOSAR version check for DEM.
 */
/******************************************************************************/

/*******************************************************************************
**                         QAC Warning                                        **
*******************************************************************************/
/* 1. QAC Warning:                                                            */
/* Message       : (2:0553) Translation unit contains no object or function   */
/*                 definitions with external linkage.                         */
/* Justification : Interrupt is disabled for particular configuration, Hence  */
/*                 no object or function definitions are available.           */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:0553)-1 and                           */
/*                 END Msg(2:0553)-1 tags in the code.                        */
/******************************************************************************/

/* QAC Warning: START Msg(2:0553)-1 */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/*
 * Included for Fls module version information and other modules version
 * information
 */
#include "Fls_Version.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR release version information */
#define FLS_VERSION_C_AR_RELEASE_MAJOR_VERSION \
                                  FLS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLS_VERSION_C_AR_RELEASE_MINOR_VERSION \
                                  FLS_AR_RELEASE_MINOR_VERSION_VALUE
#define FLS_VERSION_C_AR_RELEASE_REVISION_VERSION \
                               FLS_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FLS_VERSION_C_SW_MAJOR_VERSION    FLS_SW_MAJOR_VERSION_VALUE
#define FLS_VERSION_C_SW_MINOR_VERSION    FLS_SW_MINOR_VERSION_VALUE

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* Implements: FLS_ESDD_UD_263*/
/* Implements:  FLS206, FLS364 */
/* Implements:  SWS_Fls_00206 */
#if (FLS_VERSION_AR_RELEASE_MAJOR_VERSION != \
                              FLS_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fls_Version.c : Mismatch in Release Major Version"
#endif
#if (FLS_VERSION_AR_RELEASE_MINOR_VERSION != \
                              FLS_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "Fls_Version.c : Mismatch in Release Minor Version"
#endif
#if (FLS_VERSION_AR_RELEASE_REVISION_VERSION != \
                           FLS_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "Fls_Version.c : Mismatch in Release Revision Version"
#endif


#if (FLS_VERSION_SW_MAJOR_VERSION != FLS_VERSION_C_SW_MAJOR_VERSION)
  #error "Fls_Version.c : Mismatch in Software Major Version"
#endif
#if (FLS_VERSION_SW_MINOR_VERSION != FLS_VERSION_C_SW_MINOR_VERSION)
  #error "Fls_Version.c : Mismatch in Software Minor Version"
#endif
/* Implements: FLS_ESDD_UD_042 */
#if (FLS_VERSION_CHECK_EXT_MODULES == STD_ON)

/* Rte Module Version Check */
/* Implements: FLS_ESDD_UD_036 */
#if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
#if ((RTE_AR_RELEASE_MAJOR_VERSION != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != FLS_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif
#endif /* (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */

/* Det Module Version Check */
#if (FLS_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION != FLS_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif /* End of FLS_DEV_ERROR_DETECT */

#if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
/* Dem Module Version Check */
#if ((DEM_AR_RELEASE_MAJOR_VERSION != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (DEM_AR_RELEASE_MINOR_VERSION != FLS_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif
#endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */

/* MemIf Module Version Check */
#if ((MEMIF_AR_RELEASE_MAJOR_VERSION != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (MEMIF_AR_RELEASE_MINOR_VERSION != FLS_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of MemIf.h does not match the expected version"
#endif

/* Os Module Version Check */
#if ((OS_AR_RELEASE_MAJOR_VERSION != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (OS_AR_RELEASE_MINOR_VERSION != FLS_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif

#endif /* End of(FLS_VERSION_CHECK_EXT_MODULES == STD_ON) */

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* END Msg(2:0553)-1 */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
