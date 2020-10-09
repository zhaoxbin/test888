/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Hardware.h                                              */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015-2017  Renesas Electronics Corporation                    */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains pre-compile time parameters.                            */
/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                 */
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
 * V1.0.0:  05-Oct-2015 : Initial Version
 * V2.0.0:  10-Oct-2016 : Changed copyright
 * V2.0.1:  24-Aug-2017 : ARDAABD-2151 - Added QAC/MISRA Warning justifications
 * V2.0.2:  08-Nov-2017 : ARDAABD-2370 - Te following variable names has been
 *                        changed: 
 *                        - FACIReg_BaseAddress to  FLS_GpFACIReg_BaseAddress
 *                        - ECCReg_BaseAddress to FLS_GpECCReg_BaseAddress
 *                        - FlsDmaReg_BaseAddress to Fls_GaaDmaReg_BaseAddress
 */
/******************************************************************************/

/*******************************************************************************
**                       Generation Tool Version                              **
*******************************************************************************/
/*
 * TOOL VERSION:    2.0.2
 */
/*******************************************************************************
**                         Input File                                         **
*******************************************************************************/
/*
 * INPUT FILE:    D:\TEMP\DaVinci\Cfg-0475095\Generation\Cfg_Gen-1556000558540-0\AutosarFiles_ValGen-1556000592207-0\ExtGen_DrvFls_ECUC_4.2.2_4651371078630412703.arxml
 *                D:\usr\usage\Delivery\CBD19x\CBD1900162\D00\external\ThirdParty\Mcal_Rh850F1x\Supply\ASR_RH850_F1KM_42.02.01\X1X\F1x\modules\fls\generator\R422_FLS_F1x_BSWMDT.arxml
 * GENERATED ON:  23 Apr 2019 - 14:23:22
 */

#ifndef FLS_HARDWARE_H
#define FLS_HARDWARE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

//#include "Iocommon_Types.h"
#include "Fls_Cfg.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR release version information */
#define FLS_HW_AR_RELEASE_MAJOR_VERSION  4U
#define FLS_HW_AR_RELEASE_MINOR_VERSION  2U
#define FLS_HW_AR_RELEASE_REVISION_VERSION  2U

/* File version information */
#define FLS_HW_SW_MAJOR_VERSION  1U
#define FLS_HW_SW_MINOR_VERSION  1U

/******************************************************************************/
/*******************************************************************************
**                      MISRA C Rule Violations                               **
*******************************************************************************/
/******************************************************************************/
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

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* DMA channels */
#define FLS_DMA_INSTANCES 0U
/*******************************************************************************
**                      Macro Definitions                                     **
*******************************************************************************/

/*******************************************************************************
**                      Channel Handles                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */



/* Structure of DMA registers */
/* extern volatile DmaReg* const 
             Fls_GaaDmaReg_BaseAddress[FLS_DMA_INSTANCES];*/

#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/* MISRA Violation: START Msg(2:0832)-1 */
#include FLS_MEMMAP_FILE
/* END Msg(2:0832)-1 */

#endif /* FLS_HARDWARE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
