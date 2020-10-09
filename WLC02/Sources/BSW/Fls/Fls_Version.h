/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Version.h                                               */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015 - 2017 Renesas Electronics Corporation                   */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains macros required for checking versions of modules        */
/* included by FLS Driver                                                     */
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
 * V1.1.1:  16-Oct-2017  :  #ARDAABD-2552 - Added AUTOSAR version check for
 *                             DEM inclusion.
 */
/******************************************************************************/

#ifndef FLS_VERSION_H
#define FLS_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Included for version information macros */
#include "Fls.h"
#if (FLS_DEV_ERROR_DETECT == STD_ON)
/* DET module version information is required only when DET is enabled */
#include "Det.h"
#endif
#if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
/* DEM module version information*/
#include "Dem.h"
#endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */

#if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
/*
 * RTE module version information is required only when critical section
 * protection is enabled
 */
#include "Rte.h"

#endif

/* Memif module version information*/
#if (FLS_VERSION_CHECK_EXT_MODULES == STD_ON)
#include "MemIf.h"
#endif
/* Memif module version information*/
#include "Os.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Release version information */
#define FLS_VERSION_AR_RELEASE_MAJOR_VERSION      FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_VERSION_AR_RELEASE_MINOR_VERSION      FLS_AR_RELEASE_MINOR_VERSION
#define FLS_VERSION_AR_RELEASE_REVISION_VERSION   \
                                               FLS_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FLS_VERSION_SW_MAJOR_VERSION   FLS_SW_MAJOR_VERSION
#define FLS_VERSION_SW_MINOR_VERSION   FLS_SW_MINOR_VERSION

#endif /* FLS_VERSION_H  */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
