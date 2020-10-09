/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = Fls.h                                                       */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2015-2018 Renesas Electronics Corporation                     */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains macros, FLS type definitions, structure data types and  */
/* API function prototypes of FLS Driver                                      */
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
 *                         1. Removed the inclusion of Det.h.
 *                         2. Added the function declaration of Fls_Suspend,
 *                            Fls_Resume, Fls_GetVersionInfo APIs.
 *                         3. Removed the macro Fls_GetVersionInfo as per JIRA
 *                            Ticket ARDAAGA-75.
 *                         4. Removed Fcu_Config structure declaration.
 *                         5. Added justification for Msg(4:3684)
 *
 * V1.1.1:  08-Sep-2016  : Changed parameter type for TargetAddressPtr in
 *                         Fls_Read(ARDAABD-651)
 *
 * V1.2.1:  28-Sep-2016  :  #ARDAABD-843
 *                          1. Removed AR322 support
 *
 * V2.0.0:  11-Nov-2016  : #ARDAABD-732
 *                          1. added FLS_E_PARAM_DMA_CONFIG DET error
 *                          2. added Fls_GstDmaUnitConfig declaration
 *                         #ARDAABD-941 - changed Fls_Suspend function
 *                             return type.
 *
 * V2.0.1:  24-Jan-2017  : #ARDAABD-418
 *                         1. linked some AR requirements, no functional changes
 *
 * V2.0.2:  26-Jan-2017  : #ARDAABD-843
 *                         1. Fls debug support is obsolete in AR 4.2.2,
 *                            so removed if AR is higher version.
 *
 * V2.1.0:  31-Jan-2017  :  #ARDAABD-571
 *                          1. Addded MemMap_Fls vs MemMap.h inclusion based on
 *                             AR revision.
 *                          2. Added Fls_HWCheckConsistency API.
 *                          3. Added register write verify realted bit masks.
 *                          4. Changes after review.
 *
 * V2.1.1:  14-Feb-2017  :  #ARDAABD-571
 *                          1. Fixed acceptance findings.
 *
 * V2.1.2:  13-Mar-2017  :  #ARDAABD-829
 *                          1.  MISRA fixes.
 * V2.1.3:  24-Jul-2017  :  #ARDAABD-1325 - added definition for
 *                          FCURETURNFROMCMDLOCK_API
 * V2.1.4:  11-Oct-2017  :  #ARDAABD-2578 - Corrected FLS_BLANK_CHECK_SID value.
 * V2.1.5:  16-Oct-2017  :  #ARDAABD-2552 - Added DET Runtime Error Codes
 *
 * V2.1.6:  20-Jun-2018  :  Following changes are made:
 *                          1. As part of merging activity, #ARDAABD-3465
 *                             below changes are made(Ref : ARDAABD-908):
 *                           a. FLS_START_SEC_DBTOC_DATA_UNSPECIFIED has
 *                              changed to FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
 *                              and FLS_STOP_SEC_DBTOC_DATA_UNSPECIFIED has
 *                              changed to FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED.
 *                           b. Inserted a one space character after
 *                              'if' statement.
 *                           c. Copyright information has been updated.
 *                           d. As per ARDAABD-3853, traceability has been
 *                              improved.
 */
/******************************************************************************/
#ifndef FLS_H
#define FLS_H

/*******************************************************************************
**      To support different AUTOSAR releases in a single package             **
*******************************************************************************/
#define FLS_AR_FOUR_TWO_TWO       422
#define FLS_AR_FOUR_ZERO_THREE    403

#define FLS_AR_HIGHER_VERSION     FLS_AR_FOUR_TWO_TWO
#define FLS_AR_LOWER_VERSION      FLS_AR_FOUR_ZERO_THREE

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* To publish the standard types */
#include "Std_Types.h"
/* Included for pre-compile time parameters */
#include "Fls_Cfg.h"
#include "Fls_Hardware.h"
/* To publish the type Fls_ConfigType */
#include "Fls_Types.h"
#if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
#if (FLS_DEV_ERROR_DETECT == STD_ON)
/*FLS_H_001:  FLS303, FLS077, FLS162, FLS287_Conf,ECUC_Fls_00287  */
/* Implements: FLS303 */
/* Only in case of DET enabled, Debug variables will be available externally */
#include "Fls_Debug.h"
#endif /* #if (FLS_DEV_ERROR_DETECT == STD_ON) */
#endif /* #if (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* Version identification */
#define FLS_VENDOR_ID              FLS_VENDOR_ID_VALUE
#define FLS_MODULE_ID              FLS_MODULE_ID_VALUE
/*FLS_H_002:  FLS_ESDD_UD_035                                                 */
/*FLS_H_003:  FLS288_Conf                                                     */
/*FLS_H_004:  ECUC_Fls_00288                                                  */
#define FLS_INSTANCE_ID            FLS_INSTANCE_ID_VALUE

#if (FLS_AR_VERSION == FLS_AR_HIGHER_VERSION) /* START of FLS_AR_VERSION */
/* Functionality related to R4.2 */
/* AUTOSAR release version information */
#define FLS_AR_RELEASE_MAJOR_VERSION      4
#define FLS_AR_RELEASE_MINOR_VERSION      2
#define FLS_AR_RELEASE_REVISION_VERSION   2

#elif (FLS_AR_VERSION == FLS_AR_LOWER_VERSION)
/* Functionality related to R4.0 */
/* AUTOSAR release version information */
#define FLS_AR_RELEASE_MAJOR_VERSION      4
#define FLS_AR_RELEASE_MINOR_VERSION      0
#define FLS_AR_RELEASE_REVISION_VERSION   3

#endif
/* Module Software version information */
#define FLS_SW_MAJOR_VERSION    FLS_SW_MAJOR_VERSION_VALUE
#define FLS_SW_MINOR_VERSION    FLS_SW_MINOR_VERSION_VALUE
#define FLS_SW_PATCH_VERSION    FLS_SW_PATCH_VERSION_VALUE
/*******************************************************************************
**                      API Service Id Macros                                 **
*******************************************************************************/
/* Service Id of Fls_Init */
#define FLS_INIT_SID                        (uint8)0x00
/* Service Id of Fls_Erase */
#define FLS_ERASE_SID                       (uint8)0x01
/* Service Id of Fls_Write */
#define FLS_WRITE_SID                       (uint8)0x02
/* Service Id of Fls_Cancel */
#define FLS_CANCEL_SID                      (uint8)0x03
/* Service Id of Fls_GetStatus */
#define FLS_GET_STATUS_SID                  (uint8)0x04
/* Service Id of Fls_GetJobResult */
#define FLS_GET_JOB_RESULT_SID              (uint8)0x05
/* Service Id of Fls_MainFunction */
#define FLS_MAINFUNCTION_SID                (uint8)0x06
/* Service Id of Fls_Read */
#define FLS_READ_SID                        (uint8)0x07
/* Service Id of Fls_Compare */
#define FLS_COMPARE_SID                     (uint8)0x08
/* Service Id of Fls_SetMode */
#define FLS_SET_MODE_SID                    (uint8)0x09
/* Service Id of Fls_BlankCheck */
#define FLS_BLANK_CHECK_SID                 (uint8)0x0A
/* Service Id of Fls_GetVersionInfo */
#define FLS_GET_VERSION_INFO_SID            (uint8)0x10
/* Service Id of Fls_ReadImmediate */
#define FLS_READ_IMM_SID                    (uint8)0x11
/* Service Id of Fls_Suspend */
#define FLS_SUSPEND_SID                     (uint8)0x13
/* Service Id of Fls_Resume */
#define FLS_RESUME_SID                      (uint8)0x14
/* Service Id of Fls_CheckHWConsistency */
#define FLS_CHECK_HW_CONSISTENCY_SID        (uint8)0x15
/* Service Id of internal functions - needed for WV and Ram mirror */
#define FLS_FCUCLEARSTATUS_API_ID           (uint8)0x16
#define FLS_FCU_SWITCH_MODE_SID             (uint8)0x17
#define FLS_CLEAR_INT_REQ_SID               (uint8)0x18
#define FLS_SET_INT_REQ_SID                 (uint8)0x19
#define FLS_FCURETURNFROMCMDLOCK_API_ID     (uint8)0x1A
/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/

/*FLS_H_005:  FLS_ESDD_UD_200                                                 */
/*FLS_H_006:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_007:  FLS314, FLS361, FLS319                                          */
/*FLS_H_008:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_009:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_010:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_011:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* Implements: FLS004, SWS_Fls_00004 */
/* A wrong parameter passed to Fls_Init API. */
#define FLS_E_PARAM_CONFIG                  (uint8)0x01

/*FLS_H_012:  FLS_ESDD_UD_201                                                 */
/*FLS_H_013:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_014:  FLS314, FLS361                                                  */
/*FLS_H_015:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_016:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_017:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_018:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* Implements: FLS004, SWS_Fls_00004 */
/* A wrong address passed to the APIs */
#define FLS_E_PARAM_ADDRESS                 (uint8)0x02

/*FLS_H_019:  FLS_ESDD_UD_202                                                 */
/*FLS_H_020:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_021:  FLS314, FLS361                                                  */
/*FLS_H_022:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_023:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_024:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_025:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* Implements: FLS004, SWS_Fls_00004 */
/* A wrong length of the address passed to the APIs */
#define FLS_E_PARAM_LENGTH                  (uint8)0x03

/*FLS_H_026:  FLS_ESDD_UD_203                                                 */
/*FLS_H_027:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_028:  FLS314, FLS361                                                  */
/*FLS_H_029:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_030:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_031:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_032:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* Implements: FLS004, SWS_Fls_00004 */
/* A null buffer address passed to the APIs */
#define FLS_E_PARAM_DATA                    (uint8)0x04

/*FLS_H_033:  FLS_ESDD_UD_204                                                 */
/*FLS_H_034:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_035:  FLS314, FLS361                                                  */
/*FLS_H_036:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_037:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_038:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_039:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* Implements: FLS004, SWS_Fls_00004 */
/* API service is used without driver initialization */
#define FLS_E_UNINIT                        (uint8)0x05

/*FLS_H_040:  FLS_ESDD_UD_205                                                 */
/*FLS_H_041:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_042:  FLS314, FLS361                                                  */
/*FLS_H_043:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_044:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_045:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_046:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* Implements: FLS004, SWS_Fls_00004 */
/* API service used when the driver is busy */
#define FLS_E_BUSY                          (uint8)0x06

/*FLS_H_047:  FLS_ESDD_UD_206                                                 */
/*FLS_H_048:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_049:  FLS314, FLS361                                                  */
/*FLS_H_050:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_051:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_052:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_053:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* Implements: FLS004, SWS_Fls_00004 */
/* DET error code to report that the erase job has failed */
#define FLS_E_VERIFY_ERASE_FAILED           (uint8)0x07

/*FLS_H_054:  FLS_ESDD_UD_207                                                 */
/*FLS_H_055:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_056:  FLS314, FLS361                                                  */
/*FLS_H_057:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_058:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_059:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_060:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* Implements: FLS004, SWS_Fls_00004 */
/* DET error code to report that the block is not erased for a write job */
#define FLS_E_VERIFY_WRITE_FAILED           (uint8)0x08

/*FLS_H_061:  FLS_ESDD_UD_208                                                 */
/*FLS_H_062:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_063:  FLS314, FLS361                                                  */
/*FLS_H_064:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_065:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_066:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_067:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* Implements: FLS004, SWS_Fls_00004 */
/*
 * DET error code to report when timeout supervision of a read, write, erase or
 * compare job failed
 */
#define FLS_E_TIMEOUT                       (uint8)0x09

/*FLS_H_067:  FLS_ESDD_UD_209                                                 */
/*FLS_H_068:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_069:  FLS314, FLS361                                                  */
/*FLS_H_070:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_071:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_072:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_073:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* When valid Database is not available */
#define FLS_E_INVALID_DATABASE              (uint8)0xEF

/*FLS_H_074:  FLS_ESDD_UD_210                                                 */
/*FLS_H_075:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_076:  FLS314, FLS361                                                  */
/*FLS_H_077:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_078:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_079:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_080:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* Implements: FLS004, SWS_Fls_00004 */
/* API Fls_GetVersionInfo invoked with a null pointer */
#define FLS_E_PARAM_POINTER                 (uint8)0x0A

/*FLS_H_081:  FLS_ESDD_UD_211                                                 */
/*FLS_H_082:  FLS004, FLS007, FLS161, FLS310, FLS311, FLS312, FLS313, FLS267  */
/*FLS_H_083:  FLS314, FLS361                                                  */
/*FLS_H_084:  SWS_Fls_00315, SWS_Fls_00004, SWS_Fls_00310, SWS_Fls_00311      */
/*FLS_H_085:  SWS_Fls_00312, SWS_Fls_00313, SWS_Fls_00314, SWS_Fls_00361      */
/*FLS_H_086:  SWS_Fls_00004, SWS_Fls_00315, SWS_Fls_00316, SWS_Fls_00317      */
/*FLS_H_087:  SWS_Fls_00318, SWS_Fls_00319                                    */
/* DET error for missing DMA configuration. */
#define FLS_E_PARAM_DMA_CONFIG              (uint8)0x0B

/* DET error for Fls_CheckHWConsistency invalid call parameter. */
#define FLS_E_PARAM_VALUE                   (uint8)0x0C

/*******************************************************************************
**                      DET Runtime Error Codes                               **
*******************************************************************************/
#if (FLS_AR_VERSION == FLS_AR_HIGHER_VERSION)
/* Implements: SWS_Fls_00315, ECUC_Fls_00310, FLS310_Conf */
/* FLS_H_212: FLS_ESDD_UD_256, FLS_ESDD_UD_249, FLS311_Conf, ECUC_Fls_00311 */
#define FLS_E_ERASE_FAILED                  (uint8)0x01
/* Implements: SWS_Fls_00316, FLS312_Conf, SWS_Fls_00312 */
/* FLS_H_215: FLS_ESDD_UD_259, FLS_ESDD_UD_252 */
#define FLS_E_WRITE_FAILED                  (uint8)0x02
/* Implements: SWS_Fls_00317, FLS313_Conf, SWS_Fls_00313 */
/* FLS_H_213: FLS_ESDD_UD_257,FLS_ESDD_UD_250 */
#define FLS_E_READ_FAILED                   (uint8)0x03
/* Implements: SWS_Fls_00318 */
/* FLS_H_211: FLS_ESDD_UD_255, FLS_ESDD_UD_248, FLS314_Conf, ECUC_Fls_00314 */
#define FLS_E_COMPARE_FAILED                (uint8)0x04
/* Implements: SWS_Fls_00319, FLS315_Conf, ECUC__Fls_00315 */
/* FLS_H_214: FLS_ESDD_UD_258, FLS_ESDD_UD_251 */
#define FLS_E_UNEXPECTED_FLASH_ID           (uint8)0x05
/* read job failed due to double bit error */
/* FLS_H_210: FLS_ESDD_UD_096, FLS_ESDD_UD_260, FLS_ESDD_UD_216 */
#define FLS_E_READ_FAILED_DED               (uint8)0x10
/* ECC control register is inconsistent */
/* FLS_H_217: FLS_ESDD_UD_262, FLS_ESDD_UD_218 */
#define FLS_E_ECC_FAILED                    (uint8)0x11
/* Register Write Verify error */
/* FLS_H_216: FLS_ESDD_UD_261, FLS_ESDD_UD_217 */
#define FLS_E_REG_WRITE_VERIFY              (uint8)0x12

#endif /* (FLS_AR_VERSION == FLS_AR_LOWER_VERSION) */
/*******************************************************************************
**                       MISRA C Rule Violations                              **
*******************************************************************************/
/******************************************************************************/
/* 1. MISRA C RULE VIOLATION:                                                 */
/* Message       : (4:3684) Array declared with unknown size.                 */
/* Rule          : MISRA-C:2004 Rule 8.12                                     */
/* Justification : Config array used is verified in the file which is only    */
/*                 declaration and size is configuration dependent.           */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(4:3684)-1 and                           */
/*                 END Msg(4:3684)-1 tags in the code.                        */
/******************************************************************************/

/*******************************************************************************
**                         Macro Defines                                      **
*******************************************************************************/

/*FLS_H_088:  FLS_ESDD_UD_052                                                 */
/*FLS_H_089:  FLS216                                                          */
/*FLS_H_090:  SWS_Fls_00216, SWS_Fls_00369                                    */
/* Address offset from the configured flash base address to access a certain
 * flash memory area
 */
typedef uint32 Fls_AddressType;

/*FLS_H_091:  FLS_ESDD_UD_053 */
/*FLS_H_092:  SWS_Fls_00370 */
/* Specifies the number of bytes to read/write/erase/compare */
typedef uint32 Fls_LengthType;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_Init" */
extern FUNC(void, FLS_PUBLIC_CODE) Fls_Init();
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_Erase" */
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Erase
        (Fls_AddressType TargetAddress, Fls_LengthType Length);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_Write" */
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Write
(Fls_AddressType TargetAddress,
P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) SourceAddressPtr,
Fls_LengthType Length);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE

#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_Read" */
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Read
(Fls_AddressType SourceAddress, P2VAR(uint8, AUTOMATIC, FLS_APPL_CONST)
 TargetAddressPtr, Fls_LengthType Length);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE

#if (FLS_READIMMEDIATE_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_ReadImmediate" */
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_ReadImmediate
(Fls_AddressType SourceAddress, P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST)
TargetAddressPtr, Fls_LengthType Length);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
#endif
/*FLS_H_101: FLS286_Conf, ECUC_Fls_00286 */
#if (FLS_COMPARE_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_Compare" */
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Compare
(Fls_AddressType SourceAddress, P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST)
 TargetAddressPtr, Fls_LengthType Length);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
#endif
/*FLS_H_100: FLS285_Conf, ECUC_Fls_00285 */
#if (FLS_CANCEL_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_Cancel" */
extern FUNC(void, FLS_PUBLIC_CODE)Fls_Cancel(void);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
#endif
/*FLS_H_103: FLS291_Conf, ECUC_Fls_00291 */
#if (FLS_SET_MODE_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_SetMode" */
extern FUNC(void, FLS_PUBLIC_CODE) Fls_SetMode(MemIf_ModeType LenMode);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
#endif

#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_MainFunction" */
extern FUNC(void, FLS_PUBLIC_CODE) Fls_MainFunction(void);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE

#if (FLS_GET_STATUS_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_GetStatus" */
extern FUNC(MemIf_StatusType, FLS_PUBLIC_CODE) Fls_GetStatus(void);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
#endif
/*FLS_H_102: FLS289_Conf, ECUC_Fls_00289 */
#if (FLS_GET_JOB_RESULT_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_GetJobResult" */
extern FUNC(MemIf_JobResultType, FLS_PUBLIC_CODE) Fls_GetJobResult(void);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
#endif

#if (FLS_SUSPEND_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_Suspend" */
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Suspend(void);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
#endif

#if (FLS_RESUME_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_Resume" */
extern FUNC(void, FLS_PUBLIC_CODE) Fls_Resume(void);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
#endif

#if (FLS_BLANKCHECK_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_BlankCheck" */
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_BlankCheck
(Fls_AddressType TargetAddress, Fls_LengthType Length);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
#endif
/*FLS_H_105: FLS293_Conf,ECUC_Fls_00293 */
#if (FLS_VERSION_INFO_API == STD_ON)
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
/* Declaration of API "Fls_GetVersionInfo" */
extern FUNC(void, FLS_PUBLIC_CODE) Fls_GetVersionInfo
(P2VAR(Std_VersionInfoType, AUTOMATIC, FLS_APPL_DATA)versioninfo);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
#endif
/*FLS_H_104: FLS_ESDD_UD_125 */
#if (FLS_RAM_MIRROR == FLS_MIRROR_ENABLE)
#define FLS_START_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
extern FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_CheckHWConsistency
(
  Fls_HWConsistencyModeType LenHWConsistencyMode
);
#define FLS_STOP_SEC_PUBLIC_CODE
#include FLS_MEMMAP_FILE
#endif /* (FLS_RAM_MIRROR == FLS_MIRROR_ENABLE) */

#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
#include FLS_MEMMAP_FILE
/* MISRA Violation: START Msg(4:3684)-1 */
/* Declaration for FLS Database */
//extern CONST(Fls_ConfigType, FLS_CONST) Fls_GstConfiguration[];
#if (FLS_SET_MODE_API == STD_ON)
/* Declaration for DMA unit configuration structure */
extern CONST(Fls_DmaUnitConfig, FLS_CONST) Fls_GstDmaUnitConfig[];
#endif /* FLS_SET_MODE_API == STD_ON */
/* END Msg(4:3684)-1 */
#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include FLS_MEMMAP_FILE

#endif /* FLS_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
