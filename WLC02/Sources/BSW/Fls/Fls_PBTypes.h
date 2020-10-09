/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls_PBTypes.h                                               */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015-2018 Renesas Electronics Corporation                     */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains the type definitions of Post Build time Parameters      */
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
 *                         1. Added macros as per new design.
 *                         2. Added macro functions FLS_FCU_DF_ISSUE_BYTE_CMD
 *                            and FLS_FCU_DF_ISSUE_WORD_CMD.
 *                         3. Added justification for Msg(4:3412), Msg(4:3453),
 *                            Msg(4:3410) and Msg(4:3684)
 *                         4. Fls_FlashReadType and Fls_CommandType are removed
 *                            as part of JIRA ticket "ARDAAGA-69
 *
 * V1.1.1:  25-Jul-2016  : #ARDAABD-437
 *                         1. Added FLS_FCU_FENTRYD_MASK and
 *                            FLS_FCU_FRDY_POOL_COUNT macros
 *
 * V1.2.1:  03-Oct-2016  :  #ARDAABD-843
 *                          1. Removed support for
 *                             FLS_AR_HIGHER_VERSION / FLS_AR_LOWER_VERSION
 *
 * V1.2.2:  20-Oct-2016  :  #ARDAABD-447
 *                          1. Removed FLS_FCU_SWITCHMODE_WAIT_COUNT macro
 *                          2. Removed FLS_FCU_FORCESTOP_WAIT_COUNT macro
 *
 * V1.2.3:  24-Oct-2016  : #ARDAABD-854
 *                         1. Reworked Schm_<Enter/Exit> functions for
 *                            aligning with Rte requirements.
 *
 * V2.0.0:  11-Nov-2016  : #ARDAABD-732 - added FLS_SET_INT_MK, FLS_RESET_INT_MK
 *                            FLS_DMA_DCEN_DISABLE, FLS_DMA_DCST_CLEAR,
 *                            FLS_DMA_DCST_ERR, FLS_RESET_DTC, FLS_DMA_DRQ_CLEAR
 *                            FLS_DMA_DTCT_REG_VALUE, FLS_DMA_DRTC_REG_VALUE,
 *                            FLS_DMA_DCEN_ENABLE, FLS_DMA_MLE_CLEAR,
 *                            FLS_DMA_DTC_RELOAD_CNT, FLS_FACI_CMD_DMA_WRITE
 *
 * V2.0.1:  10-Jan-2017  : #ARDAABD-854
 *                         1. Schm_<Enter/Exit> functions are not anymore
 *                            generated based on VENDOR_API_INFIX_DEFINED
 *                            macro value since the vendor API infix will always
 *                            be provided by drivers's BSWMDT file
 *
 * V2.0.2:  10-Jan-2017  : #ARDAABD-854
 *                         1. Use FLS_CRITICAL_SECTION_PROTECTION macro value
 *                            for FLS_ENTER/EXIT_CRITICAL_SECTION definition
 *
 * v2.1.0:  18-Jan-2017  : #ARDAABD-923
 *                         1. Added FLS_ECC_INITCHK_SUPPORT macro
 *
 * V2.1.1   19-Jan-2017  : #ARDAABD-459 - FLS_FCU_FSTATR_PE_ERROR macro value
 *                            has been corrected.
 *
 * V2.1.2:  20-Jan-2017  : #ARDAABD-437
 *                         1. Removed FLS_FCU_FENTRYD_MASK as it is not used
 *                         2. Fixed review findings.
 *
 * V2.1.2:  13-Mar-2017  : #ARDAABD-829
 *                          1.  MISRA fixes.
 *
 * V2.1.3:  26-May-2017  : #ARDAABD-446
 *                         Defined FLS_FCU_BLANKCHECK_COUNT value.
 * V2.1.4:  20-Jul-2017  : #ARDAABD-1139 DFERSTR register masks has been changed
 *                          to 8bit.
 *                         #ARDAABD-1246 - Removed Firmware copy support.
 *                         #ARDAABD-1325 - added definition for FASTAT_DFAE bit.
 * V2.1.5:  25-Aug-2017  : #ARDAABD-2151 - New defines added in order to correct
 *                         magic number usage.
 * V2.1.6:  25-Sep-2017  : #ARDAABD-2370 - added FLS_FACI_CMD_DF_WRITE define.
 * V2.1.7:  23-Oct-2017  : FLS_ECC_INITCHK_SUPPORT compiler switch has been
 *                         removed for DFECCCTL, DFERRINT, DFTSTCTL register
 *                         reset value.
 * V2.1.8:  13-Apr-2018  : Following changes are made:
 *                         1. As part of merging activity, #ARDAABD-3465
 *                            below changes are made(Ref : ARDAABD-908):
 *                          a. FLS_START_SEC_BUFFER_CODE has been
 *                             changed to FLS_START_SEC_VAR_NO_INIT_32 and
 *                             FLS_STOP_SEC_BUFFER_CODE has been
 *                             changed to FLS_STOP_SEC_VAR_NO_INIT_32.
 *                          b. Misra Violation END tag for Message Msg(4:3453)
 *                             has been added.
 *                          c. Misra Violation tag for messages Msg(4:3412) and
 *                             Msg(4:3410) has been removed.
 *                          d. Copyright information has been updated.
 * V2.1.9   09-Aug-2018 :  ARDAABD-3696 - add FLS_BOUNDARY_SIZE_64K define
 */
/******************************************************************************/
#ifndef FLS_PBTYPES_H
#define FLS_PBTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Included for module version information */
#include "Fls.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR release version information */
#define FLS_PBTYPES_AR_RELEASE_MAJOR_VERSION     FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_PBTYPES_AR_RELEASE_MINOR_VERSION     FLS_AR_RELEASE_MINOR_VERSION
#define FLS_PBTYPES_AR_RELEASE_REVISION_VERSION  FLS_AR_RELEASE_REVISION_VERSION

/* File version information */
#define FLS_PBTYPES_SW_MAJOR_VERSION             FLS_SW_MAJOR_VERSION
#define FLS_PBTYPES_SW_MINOR_VERSION             FLS_SW_MINOR_VERSION

/*******************************************************************************
**                         MISRA C Rule Violations                            **
*******************************************************************************/
/******************************************************************************/
/* 1. MISRA C RULE VIOLATION:                                                 */
/* Message       : Msg(4:3453) A function could probably be used instead of   */
/*                 this function-like macro.                                  */
/* Rule          : MISRA-C:2004                                               */
/* Justification : This function macro is used here to reduce the complexity  */
/*                 of having utility functions for performing 8, 16 and 32 bit*/
/*                 data flash reading and writing operations                  */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:3453)-1 and                           */
/*                 END Msg(4:3453)-1 tags in the code.                        */
/******************************************************************************/
/******************************************************************************/
/* 2. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:3684) Array declared with unknown                       */
/*                 size.                                                      */
/* Rule          : MISRA-C:2004 Rule 8.12                                     */
/* Justification : All operations are checked and array is necessary to       */
/*                 perform read/compare functionality. This is used in        */
/*                 misalignment handling.Temporary buffer array size is       */
/*                 configuration dependent.                                   */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:3684)-2 and                           */
/*                 END Msg(4:3684)-2 tags in the code.                        */
/******************************************************************************/

/*******************************************************************************
**                         Macro Defines                                      **
*******************************************************************************/
/* FLS_PBTYPES_H_001:  FLS_ESDD_UD_090                                        */
/* FLS_PBTYPES_H_002:  EAAR_PN0034_FR_0052                                    */
/* General defines */
#define FLS_DBTOC_VALUE                 ((FLS_VENDOR_ID_VALUE << 22) | \
                                         (FLS_MODULE_ID_VALUE << 14) | \
                                         (FLS_SW_MAJOR_VERSION_VALUE << 8) | \
                                         (FLS_SW_MINOR_VERSION_VALUE << 3))
/* Driver status Macros */
#define FLS_INITIALIZED               (boolean)1
#define FLS_UNINITIALIZED             (boolean)0

/* Macros to avoid direct numbers */
#define FLS_ZERO                               (uint8)0
#define FLS_ONE                                (uint8)1
#define FLS_TWO                                (uint8)2
#define FLS_THREE                              (uint8)3
#define FLS_FOUR                               (uint8)4
#define FLS_EIGHT                              (uint16)8

#define FLS_INTERRUPT_BIT_NUM                  (uint16)12
#define FLS_NULL                               (uint8*)0x00000000uL
#define FLS_BOUNDARY_SIZE_64K                  (uint32)0x00010000

/* Macros for boolean variables */
#define FLS_FALSE                             (boolean)0
#define FLS_TRUE                              (boolean)1

/* Macros for Flash protection Support */
#define SUPPORTED                              0
#define NOT_SUPPORTED                          1

/* Implements: FLS014, SWS_Fls_00014, Jira-ARDAABD-923 */
#define FLS_DFECCCTL_RESET_VAL                (uint16)0
#define FLS_DFERRINT_RESET_VAL                (uint8)2
#define FLS_DFTSTCTL_RESET_VAL                (uint16)0

#define FLS_FACI_FRTEINT_RESET_VAL            (uint8)3

#define FLS_CLEAR_INT_REQ                     (uint16)0x1000
#define FLS_SET_INT_REQ                       (uint16)0x1000
#define FLS_SET_INT_MK                        (uint16)0x0080
#define FLS_RESET_INT_REQ                     (uint16)0xEFFF
#define FLS_RESET_INT_MK                      (uint16)0xFF7F

#if (FLS_FHVE_REGS == SUPPORTED)
/* Macro to enable flash memory software protection */
#define FLS_FLASH_PROTECTION_ON                (uint8)0
/* Macro to disable flash memory software protection */
#define FLS_FLASH_PROTECTION_OFF               (uint8)1
#endif /* end of #if (FLS_FHVE_REGS == SUPPORTED) */


/* FASTAT */
#define FLS_FCU_REGBIT_FASTAT_CMDLK     (uint8)(0x10u)
#define FLS_FCU_REGBIT_FASTAT_DFAE      (uint8)(0x08u)
#define FLS_FASTAT_RESET_VAL            (uint8)(0x00u)

/* FCURAME */
#define FLS_FCU_REGBIT_FCURAME_KEY      (uint16)(0xC400u)
#define FLS_FCU_REGBIT_FCURAME_FCRME    (uint16)(0x0001u)
#define FLS_FCU_REGBIT_FCURAME_FRAMTRAN (uint16)(0x0002u)
#define FLS_FCU_REGBIT_FCURAME_RESET    (uint16)(0x0000u)

/* FSTATR */
#define FLS_FCU_REGBIT_FSTATR_ILGERR    (0x00004000uL)
#define FLS_FCU_REGBIT_FSTATR_FRDY      (0x00008000uL)
#define FLS_FCU_REGBIT_FSTATR_SUSRDY    (0x00000800uL)

/* FENTRYR */
#define FLS_FCU_REGBIT_FENTRY_KEY       (uint16)(0xAA00u)
#define FLS_FCU_REGBIT_FENTRY_KEYMASK   (uint16)(0x00FFu)
#define FLS_FCU_MODE_PE                 (uint16)(0x0080u)
#define FLS_FCU_MODE_CPE                (uint16)(0x0001u)
#define FLS_FCU_MODE_USER               (uint16)(0x0000u)
#define FLS_FENTRYR_RESET_VAL           (uint16)(0x0000u)

/* FEADDR */
#define FPCKAR            (uint32)0x00000000ul

/* FSADDR */
#define FLS_FSADDR_RESET_VAL            (uint32)0x00000000ul
/* FBCSTAT */
#define FLS_FCU_REGBIT_FBCSTAT_BCST     (0x01u)

/* FPCKAR */
#define FLS_FCU_REGBIT_FPCKAR_KEY       (uint16)(0x1E00u)
#define FLS_FEADDR_RESET_VAL            (uint16)(0x0000u)

/* DFERSTR */
#define FLS_FCU_REGBIT_DFERSTR_SEDF     (0x01u)
#define FLS_FCU_REGBIT_DFERSTR_DEDF     (0x02u)
#define FLS_FCU_REGVAL_DFERSTR_NOERR    (0x00u)
#define FLS_DFERSTR_RESET_VAL           (0x00u)

/* DFERSTC */
#define FLS_FCU_REGBIT_DFERSTC_ERRCLR   (0x01u)

/* DFERRINT */
#define FLS_FCU_REGVAL_DFERRINT_NOINT    (0x00u)

#define FLS_FCU_DF_SIZE_MASK            (0x0000FFFFuL)

#define FLS_FCU_DISABLE_BFLASH                      (0x00u)
#define FLS_FCU_ENABLE_BFLASH                       (0x01u)
#if (FLS_SET_MODE_API == STD_ON)
/* DMA */
#define FLS_DMA_DCEN_DISABLE            (uint32)0x00000000ul
#define FLS_DMA_DCST_CLEAR              (uint32)0x00000091ul
#define FLS_DMA_DCST_ERR                (uint32)0x00000080ul
#define FLS_RESET_DTC                   (uint32)0x00000000ul
#define FLS_DMA_DRQ_CLEAR               (uint32)0x00000001ul
#define FLS_DMA_DTCT_REG_VALUE          (uint32)0x04007106ul
#define FLS_DMA_DTCT_RESET_VALUE        (uint32)0x00000000ul
#define FLS_DMA_DRTC_REG_VALUE          (uint32)0x00020000ul
#define FLS_DMA_DCEN_ENABLE             (uint32)0x00000001ul
#define FLS_DMA_DCEN_RESET_VAL          (uint32)0x00000000ul
#define FLS_DMA_MLE_CLEAR               (uint32)0xFFFFDFFFul
/* Reload function2 count / Block transfer2 count */
#define FLS_DMA_DTC_RELOAD_CNT          (uint32)0x00020000ul
#endif /* FLS_SET_MODE_API == STD_ON */
#define FLS_DMA_ZERO                    (0U)

/* do not use brackets to access system register */
#define FLS_FCU_SYSTEM_REGISTER_CDBCR     24, 13
#define FLS_FCU_SYSTEM_REGISTER_PID       6, 1
#define FLS_FCU_SYSTEM_REGISTER_ICCTRL    24, 4

#define FLS_FCU_EXTRA3_FDIV_FWVER       (0x00010264uL)
#define FLS_FCU_EXTRA3_FWVER            (0x01030219uL)
#define FLS_FCU_EXTRA3_FMAX             (0x01030234uL)
#define FLS_FCU_EXTRA3_FMIN             (0x01030238uL)
#define FLS_FCU_EXTRA3_FDIV_FWVER_03    (0x01030264uL)
#define FLS_FCU_EXTRA3_FPCLK_FWVER_03   (0x01030274uL)
#define FLS_FCU_EXTRA3_FDIV_FWVER_04    (0x01030265uL)
#define FLS_FCU_EXTRA3_FPCLK_FWVER_04   (0x01030278uL)
#define FLS_FCU_EXTRA3_SCDSADD          (0x01030270uL)
#define FLS_FCU_EXTRA3_ECCADDR          (0x01030288uL)

#define FLS_FCU_DFLASH_CMD_ADD          (0xFFA20000uL)

#define FLS_FCU_FWVER_VAL_MASK          (0x00000003uL)

#define FLS_FCU_FWVER_03                (0x03u)
#define FLS_FCU_FWVER_04                (0x04u)

#define FLS_FCU_PRDSEL3_OFFSET          (0xC8uL)

/* FCU Process Command Macros */
#define FLS_FACI_CMD_DF_WRITE            (0x02u)
#define FLS_FACI_CMD_ERASE               (0x20u)
#define FLS_FACI_CMD_CLEARSTAT           (0x50u)
#define FLS_FACI_CMD_BLANKCHECK          (0x71u)
#define FLS_FACI_CMD_SUSPEND             (0xB0u)
#define FLS_FACI_CMD_FORCED_STOP         (0xB3u)
#define FLS_FACI_CMD_WRITE               (0xE8u)
#define FLS_FACI_CMD_EXE                 (0xD0u)
#if (FLS_SET_MODE_API == STD_ON)
#define FLS_FACI_CMD_DMA_WRITE           (0xEAu)
#endif /*FLS_SET_MODE_API == STD_ON*/

/* Data Flash Size macros */
#define FLS_FCU_BLOCK_SIZE              (0x0040u)
#define FLS_FCU_BLOCK_SIZE_2N           (0x0006u)
#define FLS_FCU_WRITE_SIZE              (0x00000004uL)

#define FLS_FCU_NULL                     0x00000000uL

#define FLS_FCU_ADDR_REG_RESET          (uint32)0x00000000u
#define FLS_FCU_WORD_ZERO               (uint16)0x0000u
#define FLS_FCU_ZERO                    (uint32)0x00000000uL
#define FLS_FCU_ONE                     (uint32)0x00000001uL
#define FLS_FCU_TWO                     (uint32)0x00000002uL
#define FLS_FCU_THREE                   (uint32)0x00000003uL
#define FLS_FCU_FOUR                    (uint32)0x00000004uL
#define FLS_FCU_FIVE                    (uint32)0x00000005uL
#define FLS_FCU_EIGHT                   (uint32)0x00000008uL
#define FLS_FCU_FIFTEEN                 (uint32)0x0000000FuL
#define FLS_FCU_ONE_KB                  (uint32)0x00000400uL
#define FLS_FCU_BYTE_RESET              (uint8)0xFFu
#define FLS_FCU_ONE_MHZ                 (uint32)0x000F4240uL

#define FLS_FCU_BLANKCHECK_COUNT        (uint16)(0x100)
/* Macro define for clearing the ICHCLR bit of ICCTRL register */
#define FLS_FCU_REGBIT_ICHCLR           (uint32)0x00000100uL

/* The time it takes for the flash sequencer to process         */
/* a command. Determined empirically, as there where no timming */
/* information, regarding the flash sequencer cmd issuing,      */
/* at the moment of implementation.                             */
#define FLS_FCU_FRDY_POOL_COUNT         (uint32)(0x00000BB8)

/* To mask the error bits of FSTATR register during Erase operation */
#define FLS_FCU_ERASE_ERROR_CHECK       (uint32)(0x0000E040)

/* To mask the error bits of FSTATR register during Write operation */
#define FLS_FCU_WRITE_ERROR_CHECK       (uint32)(0x0000D040)
/* Program and erase error bits */
#define FLS_FCU_FSTATR_PE_ERROR         (uint32)(0x00007000)
/* ERRSPD and PRGSPD bits of status register FSTATR */
#define FLS_SUSPEND_CHK_FOR_ERASE       (uint32)(0x00000300)
/* PRGSPD bit of status register FSTATR */
#define FLS_SUSPEND_CHK_FOR_WRITE       (uint32)(0x00000100)
/*******************************************************************************
**                         Macro Functions                                   **
*******************************************************************************/
/* MISRA Violation: START Msg(4:3453)-1 */
#define FLS_DF_READ16(Address)             \
                (*((volatile uint16 *)(Address)))

#define FLS_DF_READ8(Address)             \
                (*((volatile uint8 *)(Address)))

#define FLS_DF_WRITE8(Address, Data)             \
                ((*((volatile uint8 *)(Address))) = (Data))

#define FLS_DF_WRITE16(Address, Data)             \
                ((*((volatile uint16 *)(Address))) = (Data))

#define FLS_DF_READ32(Address)             \
                (*((volatile uint32 *)(Address)))

#define FLS_DF_WRITE32(Address, Data)      \
         ((*((volatile uint32*)(Address))) = (Data))

#define FLS_FCU_DF_ISSUE_BYTE_CMD(Command)     \
          ((*((volatile uint8*)(0xFFA20000uL))) = (Command))

#define FLS_FCU_DF_ISSUE_WORD_CMD(Command)     \
          ((*((volatile uint16*)(0xFFA20000uL))) = (Command))
/* END Msg(4:3453)-1 */
/*******************************************************************************
**               SchM Critical Section Protection Macros                      **
*******************************************************************************/

#if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
/* FLS_PBTYPES_H_003:  FLS_ESDD_UD_003                                        */
/* FLS_PBTYPES_H_004:  SWS_Rte_07250                                          */
/* FLS_PBTYPES_H_005:  EAAR_PN0034_FR_0030, EAAR_PN0034_FR_0061               */
/* TRACE SWS_Rte_07250 */
#define FLS_ENTER_CRITICAL_SECTION(Exclusive_Area) \
  SchM_Enter_Fls_##Exclusive_Area()
/* FLS_PBTYPES_H_006:  SWS_Rte_07253                                          */
/* TRACE SWS_Rte_07253 */
#define FLS_EXIT_CRITICAL_SECTION(Exclusive_Area) \
  SchM_Exit_Fls_##Exclusive_Area()
#endif /* End of #if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON) */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**             Extern declarations for Global Arrays Of Structures            **
*******************************************************************************/
#define FLS_START_SEC_VAR_NO_INIT_32
#include FLS_MEMMAP_FILE
/* MISRA Violation: START Msg(4:3684)-2 */
/* Temporary Buffer used for read/compare functionality */
extern VAR(uint32, AUTOMATIC)Fls_GulTempBuffer[];
/* END Msg(4:3684)-2 */
#define FLS_STOP_SEC_VAR_NO_INIT_32
#include FLS_MEMMAP_FILE

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* FLS_PBTYPES_H  */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
