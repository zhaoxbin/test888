/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_Cfg.h                                                   */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015 - 2017 Renesas Electronics Corporation                   */
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
 * V1.0.0:  05-Oct-2015 : Initial version
 *
 * V1.0.1:  03-Dec-2015 : The following changes were made:
 *                        1. Added Iocommon.h in the Include Section
 *                        2. Added Macro FLS_FACI_ECC_CHECK, FLS_DF_POOL_SIZE,
 *                        FLS_WRITE_TIMEOUT_COUNT, FLS_BLANKCHECK_TIMEOUT_COUNT,
 *                        FLS_ERASE_TIMEOUT_COUNT, FLS_CPU_FREQUENCY_MHZ,
 *                        FLS_ICFLENDNM.
 *                        3. Removed macro FLS_BLANK_CHECK, FlS_SECTOR_SIZE
 *                        FLS_NUMBER_OF_SECTORS, FLS_SECTOR_START_ADDRESS.
 *                        4. Added file 'Iocommon.h' in Include Section.
 * V1.0.2:  06-Sep-2016 : Removed Macro FLS_FACI_ECC_CHECK.
 *                        ARDAABD-650
 *                        1. removed FLS_DF_TOTAL_BLOCKS macro generation
 *                        2. FLS_DF_SECTOR_START_ADDRESS comment updated
 * V2.0.0   14-Nov-2016 : The following changes were made:
 *                        #ARDAABD-571
 *                        1. Added generation of containers:
 *                           FLS_WRITE_VERIFY,
 *                           FLS_USE_WV_ERROR_INTERFACE,
 *                           FLS_ERROR_NOTIFICATION,
 *                           FLS_RAM_MIRROR,
 *                           FLS_E_REG_WRITE_VERIFY
 *                        2. #ARDAABD-731: Added number of DMA instances and
 *                           declaration of FlsDmaReg_BaseAddress array
 *                        ARDAABD-854
 *                        1. Removed generation of VENDOR_API_INFIX_DEFINED
 *                           macro value
 * V2.0.1:  20-Sep-2017 : #ARDAABD-2160
 *                        1. Iocommon split
 *                        #ARDAABD-2442 - added FLS_CPUCLK_UL_DIV macro
 */
/******************************************************************************/

/*******************************************************************************
**                       Generation Tool Version                              **
*******************************************************************************/
/*
 * TOOL VERSION:  2.0.2
 */
/*******************************************************************************
**                         Input File                                         **
*******************************************************************************/

/*
 * INPUT FILE:    D:\TEMP\DaVinci\Cfg-0475095\Generation\Cfg_Gen-1556000558540-0\AutosarFiles_ValGen-1556000592207-0\ExtGen_DrvFls_ECUC_4.2.2_4651371078630412703.arxml
 *                D:\usr\usage\Delivery\CBD19x\CBD1900162\D00\external\ThirdParty\Mcal_Rh850F1x\Supply\ASR_RH850_F1KM_42.02.01\X1X\F1x\modules\fls\generator\R422_FLS_F1x_BSWMDT.arxml
 * GENERATED ON:  23 Apr 2019 - 14:23:22
 */
#ifndef FLS_CFG_H
#define FLS_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "MemIf_Types.h"
//#include "Iocommon_Types.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR release version information */
#define FLS_CFG_AR_RELEASE_MAJOR_VERSION  4U
#define FLS_CFG_AR_RELEASE_MINOR_VERSION  2U
#define FLS_CFG_AR_RELEASE_REVISION_VERSION  2U

/* File version information */
#define FLS_CFG_SW_MAJOR_VERSION  1U
#define FLS_CFG_SW_MINOR_VERSION  1U

/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
/* TRACE [R4, FLS365] */
#define FLS_AR_RELEASE_MAJOR_VERSION_VALUE  4U
#define FLS_AR_RELEASE_MINOR_VERSION_VALUE  2U
#define FLS_AR_RELEASE_REVISION_VERSION_VALUE  2U

#define FLS_SW_MAJOR_VERSION_VALUE  1U
#define FLS_SW_MINOR_VERSION_VALUE  1U
#define FLS_SW_PATCH_VERSION_VALUE  4U

#define FLS_VENDOR_ID_VALUE  59U
#define FLS_MODULE_ID_VALUE  92U


/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/* Instance ID of the FLS Driver */
#define FLS_INSTANCE_ID_VALUE             0U
/* Write verify options */
#define FLS_WV_DISABLE                    0U
#define FLS_WV_INIT_ONLY                  1U
#define FLS_WV_INIT_RUNTIME               2U
#define FLS_MIRROR_DISABLE                3U
#define FLS_MIRROR_ENABLE                 4U

#if( FLS_CFG_AR_RELEASE_MAJOR_VERSION    == 4U  &&      \
     FLS_CFG_AR_RELEASE_MINOR_VERSION    == 2U  &&      \
     FLS_CFG_AR_RELEASE_REVISION_VERSION == 2U )
#define FLS_MEMMAP_FILE "Fls_MemMap.h"
#else
#define FLS_MEMMAP_FILE "MemMap.h"
#endif

/* Pre-compile option for Version information */
#define FLS_AR_VERSION                    FLS_AR_HIGHER_VERSION

/* TRACE [R4, FLS077] */
/* TRACE [R4, FLS162] */
/* TRACE [R4, FLS287_Conf] */
/* Pre-compile option for development error detect */
#define FLS_DEV_ERROR_DETECT              STD_ON

/* TRACE [R4, FLS293_Conf] */
/* Pre-compile option for version info API */
#define FLS_VERSION_INFO_API              STD_ON

/* TRACE [R4, FLS285_Conf] */
/* Enable/Disable the Fls_Cancel function */
#define FLS_CANCEL_API                    STD_ON

/* TRACE [R4, FLS286_Conf] */
/* Enable/Disable the Fls_Compare function */
#define FLS_COMPARE_API                   STD_ON

/* TRACE [R4, FLS291_Conf] */
/* TRACE [R4, ECUC_Fls_00291] */
/* TRACE [R4, SWS_Fls_00187] */
/* TRACE [R3, Fls187] */
/* Enable/Disable the Fls_SetMode function */
#define FLS_SET_MODE_API                  STD_ON

/* TRACE [R4, FLS290_Conf] */
/* Enable/Disable the Fls_GetStatus function */
#define FLS_GET_STATUS_API                STD_ON

/* TRACE [R4, FLS289_Conf] */
/* Enable/Disable the Fls_GetJobResult function */
#define FLS_GET_JOB_RESULT_API            STD_ON

/* Macros for enabling/disabling Hardware units ISRS */
#define FLS_DMA00_ISR_API                 STD_OFF

#define FLS_DMA01_ISR_API                 STD_OFF

#define FLS_DMA02_ISR_API                 STD_OFF

#define FLS_DMA03_ISR_API                 STD_OFF

#define FLS_DMA04_ISR_API                 STD_OFF

#define FLS_DMA05_ISR_API                 STD_OFF

#define FLS_DMA06_ISR_API                 STD_OFF

#define FLS_DMA07_ISR_API                 STD_OFF

#define FLS_DMA08_ISR_API                 STD_OFF

#define FLS_DMA09_ISR_API                 STD_OFF

#define FLS_DMA10_ISR_API                 STD_OFF

#define FLS_DMA11_ISR_API                 STD_OFF

#define FLS_DMA12_ISR_API                 STD_OFF

#define FLS_DMA13_ISR_API                 STD_OFF

#define FLS_DMA14_ISR_API                 STD_OFF

#define FLS_DMA15_ISR_API                 STD_OFF

#define FLS_DMA16_ISR_API                 STD_OFF

#define FLS_DMA17_ISR_API                 STD_OFF

#define FLS_DMA18_ISR_API                 STD_OFF

#define FLS_DMA19_ISR_API                 STD_OFF

#define FLS_DMA20_ISR_API                 STD_OFF

#define FLS_DMA21_ISR_API                 STD_OFF

#define FLS_DMA22_ISR_API                 STD_OFF

#define FLS_DMA23_ISR_API                 STD_OFF

#define FLS_DMA24_ISR_API                 STD_OFF

#define FLS_DMA25_ISR_API                 STD_OFF

#define FLS_DMA26_ISR_API                 STD_OFF

#define FLS_DMA27_ISR_API                 STD_OFF

#define FLS_DMA28_ISR_API                 STD_OFF

#define FLS_DMA29_ISR_API                 STD_OFF

#define FLS_DMA30_ISR_API                 STD_OFF

#define FLS_DMA31_ISR_API                 STD_OFF

/* Enable/disable the version check of inter-module dependencies */
#define FLS_VERSION_CHECK_EXT_MODULES     STD_OFF

/* Enable/disable the Critical section protection */
#define FLS_CRITICAL_SECTION_PROTECTION   STD_ON

/* TRACE [R4, FLS299_Conf] */
/* The contents of erased flash memory cell */
#define FLS_ERASED_VALUE                  0xffffffffUL

/* TRACE [R4, FLS307_Conf] */
/* TRACE [R4, FLS274_Conf] */
/* Information whether job notification functions are configured */
#define FLS_JOB_NOTIF_CONFIG              STD_OFF

/* This Parameter compiles switch to enable or disable the FlsTimeout
Supervision */
#define FLS_TIMEOUT_MONITORING            STD_OFF

/* Enable/Disable the Fls_Blankcheck function */
#define FLS_BLANKCHECK_API                STD_OFF

/* Enable/Disable the Fls_Readimmediate function */
#define FLS_READIMMEDIATE_API             STD_OFF

/* TRACE [R4, FLS292_Conf] */
/* Enable/Disable Job processing triggered by interrupt */
#define FLS_INTERRUPT_MODE                STD_OFF

/* Enable/Disable the Fls_Suspend function */
#define FLS_SUSPEND_API                   STD_OFF

/* Enable/Disable the Fls_Resume function */
#define FLS_RESUME_API                    STD_OFF

/* TRACE [R4, EAAR_PN0034_FSR_0002 ] */
/* Enables/Disables registers write verify */
#define FLS_WRITE_VERIFY                  FLS_WV_DISABLE

/* TRACE [R4, EAAR_PN0034_FSR_0006 ] */
/* Enables/Disables register Ram mirroring functionallity */
#define FLS_RAM_MIRROR                    FLS_MIRROR_DISABLE

/* TRACE [R4, EAAR_PN0034_FSR_0004 ] */
/* Enables/Disables FLS Notification */
#define FLS_USE_WV_ERROR_INTERFACE        STD_ON

/* TRACE [R4, EAAR_PN0034_FSR_0004 ] */
/* FLS Notification function in case of error during write verify */
#define FLS_ERROR_NOTIFICATION            

/* TRACE [R4, EAAR_PN0034_FSR_0011] */
/* TRACE [R4, EAAR_PN0034_FSR_0012] */
/* TRACE [R4, EAAR_PN0034_FSR_0013] */
/* Number of cycles to wait FCU an own register writing before
triggering error */
#define FLS_FCU_WAIT_COUNT                32U

/* TRACE [R4, FLS014] */
/* TRACE [R4, SWS_Fls_00014] */
/* TRACE [Jira, https://jira.renesas.eu/browse/ARDAABD-923] */
/* Enable/Disable FACI ECC Register Settings Check */
#define FLS_ECC_INITCHK_SUPPORT           STD_ON


/* Flash Programming HW frequency in MHz */
#define FLS_CPU_FREQUENCY_MHZ             80U

/* fPCLK clock devider */
#define FLS_CPUCLK_UL_DIV                 8U

/* Data flash pool size */
#define FLS_DF_POOL_SIZE                  2048U

/*  Physical memory address of the specified virtual sector start address */
#define FLS_DF_SECTOR_START_ADDRESS       4280287232UL

/* Total amount of data flash memory in bytes */
#define FLS_DF_TOTAL_SIZE                 32768U

/* TRACE [R4, FLS281_Conf] */
/* Smallest amount of flash memory written that can be programmed */
#define FLS_PAGE_SIZE                     (uint8)4

/* FLS_DF_BASE_ADDRESS related macros */

/* Data flash memory start address */
#define FLS_DF_BASE_ADDRESS               4280287232UL

/* FLS_DF_BLOCK_SIZE related macros */

/* Block size of data flash memory in bytes */
#define FLS_DF_BLOCK_SIZE                 64U


/* Macro to make  FHVE3 and FHVE15  Registers setting available only for
supported variants */
#define FLS_FHVE_REGS               NOT_SUPPORTED

/* Macro for FLS_ICFLENDNM Register address*/
#define FLS_ICFLENDNM                ICFLENDNM




/* FlsConfigSet handles */
#define FlsConfigSet //(&Fls_GstConfiguration[0])


/* FcuConfigSet handles */
#define FcuConfigSet0 (&Fcu_Config[0])

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* FLS_CFG_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
