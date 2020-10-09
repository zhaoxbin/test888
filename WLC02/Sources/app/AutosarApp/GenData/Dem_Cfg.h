/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Dem
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Dem_Cfg.h
 *   Generation Time: 2020-09-22 22:03:05
 *           Project: WLC - Version 1.0
 *          Delivery: CBD1900162_D00
 *      Tool Version: DaVinci Configurator (beta) 5.19.29
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 ! BETA VERSION                                                                                                       !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 ! This version of DaVinci Configurator Pro and/or the related Basic Software Package is BETA software.               !
 ! BETA Software is basically operable, but not sufficiently tested, verified and/or qualified for use in series      !
 ! production and/or in vehicles operating on public or non-public roads.                                             !
 ! In particular, without limitation, BETA Software may cause unpredictable ECU behavior, may not provide all         !
 ! functions necessary for use in series production and/or may not comply with quality requirements which are         !
 ! necessary according to the state of the art. BETA Software must not be used in series production.                  !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**********************************************************************************************************************/

/**********************************************************************************************************************
 * WARNING: This code has been generated with reduced-severity errors. 
 * The created output files contain errors that have been ignored. Usage of the created files can lead to unpredictable behavior of the embedded code.
 * Usage of the created files happens at own risk!
 * 
 * [Warning] DEM12652 - DemDataElementDataType is not configured correctly according to the value of DemDataElementDataSize 
 * - [Reduced Severity due to User-Defined Parameter] For DemDataElementDataSize == 3 bytes, the parameter DemDataElementDataType must be one of [UINT8_N, SINT8_N, UINT8, SINT8]
 * Erroneous configuration elements:
 * /ActiveEcuC/Dem/DemGeneral/OdometerValue_OdometerValue[0:DemDataElementDataType](value=UINT32) (DefRef: /MICROSAR/Dem/DemGeneral/DemDataClass/DemDataElementDataType)
 *********************************************************************************************************************/

/* configuration, interrupt handling and callback headers use different names
 * for the multiple inclusion protection define, shown in this example. The
 * appropriate names for these files can be taken from this list:
 *
 * Dem_Cfg.h:                   DEM_CFG_H
 * Dem_Lcfg.h:                  DEM_LCFG_H
 * Dem_PBcfg.h:                 DEM_PBFG_H
 * Dem_AdditionalIncludeCfg.h:  DEM_ADDITIONALINCLUDECFG_H
 * Dem_Swc.h:                   DEM_SWC_H
 * Dem_Swc_Types.h:             DEM_SWC_TYPES_H
 */
#if !defined (DEM_CFG_H)
# define DEM_CFG_H


/**********************************************************************************************************************
  MISRA JUSTIFICATIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/* -----------------------------------------------------------------------------
    Version information
 ----------------------------------------------------------------------------- */
/* AUTOSAR Version (from xsi:schemaLocation) */
#define DEM_CFG_AR_RELEASE_MAJOR_VERSION                              4u
#define DEM_CFG_AR_RELEASE_MINOR_VERSION                              1u
#define DEM_CFG_AR_RELEASE_REVISION_VERSION                           2u

/* AUTOSAR Software Specification Version Information of BSW-IMPLEMENTATION */
#define DEM_CFG_AR_MAJOR_VERSION                                      4u
#define DEM_CFG_AR_MINOR_VERSION                                      1u
#define DEM_CFG_AR_PATCH_VERSION                                      2u

/* SW version number of BSW-IMPLEMENTATION */
#define DEM_CFG_SW_MAJOR_VERSION                                      16u
#define DEM_CFG_SW_MINOR_VERSION                                      6u
#define DEM_CFG_SW_PATCH_VERSION                                      0u

/* Generator Version Information */
#define DEM_CFG_GEN_MAJOR_VERSION                                     16
#define DEM_CFG_GEN_MINOR_VERSION                                     6
#define DEM_CFG_GEN_PATCH_VERSION                                     0
#define DEM_CFG_GEN_COMPATIBILITY_VERSION                             107213uL

/* Module Implementation Variant */
#define DEM_CFG_VARIANT_PRECOMPILE                                    STD_ON      /* STD_ON: PreCompile phase is the latest point to change the configuration. STD_OFF: PostBuild phase is the latest point. */
#define DEM_CFG_VARIANT_POSTBUILD_LOADABLE                            STD_OFF      /* STD_ON: PostBuild phase is the latest point to change the configuration. STD_OFF: PreCompile phase is the latest point. */
#define DEM_CFG_VARIANT_POSTBUILD_SELECTABLE                          STD_OFF      /* STD_ON: The module can have variants. STD_OFF: The module can't have variants. */

/* Config Core Feature Version                                        5.5.0 */
/* Generator Internal Version                                         16.06.00 (Cfg5.16.x/Cfg5.17.x/Cfg5.18.x compatible, Release AR4-22), Revision: 107213, Variant: Vag (Vector) */


/* -----------------------------------------------------------------------------
    Dem configuration type definitions
 ----------------------------------------------------------------------------- */
 /*  Dem general switches  */ 
#define DEM_CFG_AGING_00_START_TESTS_TFTOC                                 STD_OFF      /* Autodetected - STD_ON: DemAgingBehavior == (DEM_AGING_TYPE_2 | DEM_AGING_TYPE_3 | DEM_AGING_TYPE_5),  STD_OFF: /Dem/DemGeneral/DemAgingBehavior == (DEM_AGING_TYPE_1 | DEM_AGING_TYPE_4 | DEM_AGING_TYPE_6) */ 
#define DEM_CFG_AGING_00_START_TRIGGER_PASSED                              STD_ON       /* Autodetected - STD_ON: DemAgingBehavior == (DEM_AGING_TYPE_1 | DEM_AGING_TYPE_4 | DEM_AGING_TYPE_5 | DEM_AGING_TYPE_6),  STD_OFF: /Dem/DemGeneral/DemAgingBehavior == (DEM_AGING_TYPE_2 | DEM_AGING_TYPE_3) */ 
#define DEM_CFG_AGING_AFTER_HEALING                                        STD_OFF      /* Autodetected - STD_ON: DemAgingAfterHealing == DEM_AGING_AFTER_HEALING,  STD_OFF: /Dem/DemGeneral/DemAgingAfterHealing == (DEM_AGING_WHILE_HEALING | DEM_AGING_AFTER_HEALING_ALL_DTC) */ 
#define DEM_CFG_AGING_AFTER_HEALING_ALL_DTC                                STD_OFF      /* Autodetected - STD_ON: DemAgingAfterHealing == DEM_AGING_AFTER_HEALING_ALL_DTC,  STD_OFF: /Dem/DemGeneral/DemAgingAfterHealing == (DEM_AGING_WHILE_HEALING | DEM_AGING_AFTER_HEALING) */ 
#define DEM_CFG_AGING_COUNT_ONLY_AGEABLE                                   STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemAgingCounterBehavior == DEM_AGING_COUNT_ONLY_AGEABLE */ 
#define DEM_CFG_AGING_NEXT_TESTS_TFTOC                                     STD_OFF      /* Autodetected - STD_ON: DemAgingBehavior == (DEM_AGING_TYPE_3 | DEM_AGING_TYPE_5 | DEM_AGING_TYPE_6),  STD_OFF: /Dem/DemGeneral/DemAgingBehavior == (DEM_AGING_TYPE_1 | DEM_AGING_TYPE_2 | DEM_AGING_TYPE_4) */ 
#define DEM_CFG_AGING_NEXT_TESTS_TNCTOC                                    STD_OFF      /* Autodetected - STD_ON: DemAgingBehavior == (DEM_AGING_TYPE_3 | DEM_AGING_TYPE_4 | DEM_AGING_TYPE_5 | DEM_AGING_TYPE_6),  STD_OFF: /Dem/DemGeneral/DemAgingBehavior == (DEM_AGING_TYPE_1 | DEM_AGING_TYPE_2) */ 
#define DEM_CFG_AGING_REPORT_ZERO_AS_ONE                                   STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemAgingCounterReporting == DEM_AGING_ZERO_AS_ONE_REPORTING */ 
#define DEM_CFG_AGING_RETAIN_MEMORY_ENTRY                                  STD_OFF      /* Vector extension - /Dem/DemGeneral/DemAgingRetainEnvironmentalData */ 
#define DEM_CFG_AGING_START_TESTS_TFTOC                                    STD_OFF      /* Autodetected - STD_ON: DemAgingBehavior == (DEM_AGING_TYPE_2 | DEM_AGING_TYPE_3 | DEM_AGING_TYPE_5 | DEM_AGING_TYPE_6),  STD_OFF: /Dem/DemGeneral/DemAgingBehavior == (DEM_AGING_TYPE_1 | DEM_AGING_TYPE_4) */ 
#define DEM_CFG_AGING_START_TRIGGER_PASSED                                 STD_ON       /* Autodetected - STD_ON: DemAgingBehavior == (DEM_AGING_TYPE_1 | DEM_AGING_TYPE_4 | DEM_AGING_TYPE_6),  STD_OFF: /Dem/DemGeneral/DemAgingBehavior == (DEM_AGING_TYPE_2 | DEM_AGING_TYPE_3 | DEM_AGING_TYPE_5) */ 
#define DEM_CFG_BSW_API_3_XX_XX                                            STD_OFF      /* Vector extension - /Dem/DemGeneral/DemBswApiVersion == DEM_BSW_API_3_XX_XX */ 
#define DEM_CFG_BSW_API_3_XX_XX_FIM                                        STD_OFF      /* Vector extension - /Dem/DemGeneral/DemBswApiVersionFiM == DEM_BSW_API_3_XX_XX */ 
#define DEM_CFG_BSW_API_3_XX_XX_NVM                                        STD_OFF      /* Vector extension - /Dem/DemGeneral/DemBswApiVersionNvM == DEM_BSW_API_3_XX_XX */ 
#define DEM_CFG_BSW_API_4_XX_XX                                            STD_ON       /* Vector extension - /Dem/DemGeneral/DemBswApiVersion == DEM_BSW_API_4_XX_XX */ 
#define DEM_CFG_BSW_API_4_XX_XX_FIM                                        STD_ON       /* Vector extension - /Dem/DemGeneral/DemBswApiVersionFiM == DEM_BSW_API_4_XX_XX */ 
#define DEM_CFG_BSW_API_4_XX_XX_NVM                                        STD_ON       /* Vector extension - /Dem/DemGeneral/DemBswApiVersionNvM == DEM_BSW_API_4_XX_XX */ 
#define DEM_CFG_CAPTURE_EXTDATA_EVENT_STORAGE                              STD_ON       /* Autodetected - via /Dem/DemGeneral/DemExtendedDataCapture == DEM_TRIGGER_EVENT_MEMORY_STORAGE */ 
#define DEM_CFG_CAPTURE_EXTDATA_TESTFAILED                                 STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemExtendedDataCapture == DEM_TRIGGER_TESTFAILED */ 
#define DEM_CFG_CAPTURE_FREEZEF_EVENT_STORAGE                              STD_ON       /* Autodetected - via /Dem/DemGeneral/DemFreezeFrameCapture == DEM_TRIGGER_EVENT_MEMORY_STORAGE */ 
#define DEM_CFG_CAPTURE_FREEZEF_TESTFAILED                                 STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemFreezeFrameCapture == DEM_TRIGGER_TESTFAILED */ 
#define DEM_CFG_CLEAR_ALL_DTCS                                             STD_ON       /* Autodetected - via /Dem/DemGeneral/DemClearDTCLimitation == (DEM_ALL_SUPPORTED_DTCS | DEM_ONLY_CLEAR_ALL_DTCS | DEM_ONLY_CLEAR_OBDII_AND_ALL_DTCS | DEM_ONLY_CLEAR_SINGLE_AND_ALL_DTCS | DEM_ONLY_CLEAR_WWHOBD_AND_ALL_DTCS) */ 
#define DEM_CFG_CLEAR_GROUP_DTCS                                           STD_ON       /* Autodetected - via /Dem/DemGeneral/DemClearDTCLimitation == DEM_ALL_SUPPORTED_DTCS */ 
#define DEM_CFG_CLEAR_IMMEDIATE_RESPONSE                                   STD_ON       /* Autodetected - via /Dem/DemGeneral/DemClearDTCBehavior == DEM_CLRRESP_VOLATILE */ 
#define DEM_CFG_CLEAR_NV_END_RESPONSE                                      STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemClearDTCBehavior == DEM_CLRRESP_NONVOLATILE_FINISH */ 
#define DEM_CFG_CLEAR_NV_START_RESPONSE                                    STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemClearDTCBehavior == DEM_CLRRESP_NONVOLATILE_TRIGGER */ 
#define DEM_CFG_CLEAR_OBDII_GROUP_DTCS                                     STD_ON       /* Autodetected - via /Dem/DemGeneral/DemClearDTCLimitation == (DEM_ALL_SUPPORTED_DTCS | DEM_ONLY_CLEAR_OBDII_AND_ALL_DTCS) */ 
#define DEM_CFG_CLEAR_REINIT_BEFORE_RESPONSE                               STD_ON       /* /Dem/DemGeneral/DemTriggerMonitorInitBeforeClearOk */ 
#define DEM_CFG_CLEAR_SINGLE_DTCS                                          STD_ON       /* Autodetected - via /Dem/DemGeneral/DemClearDTCLimitation == (DEM_ALL_SUPPORTED_DTCS | DEM_ONLY_CLEAR_SINGLE_AND_ALL_DTCS) */ 
#define DEM_CFG_CLEAR_WWHOBD_GROUP_DTCS                                    STD_ON       /* Autodetected - via /Dem/DemGeneral/DemClearDTCLimitation == (DEM_ALL_SUPPORTED_DTCS | DEM_ONLY_CLEAR_WWHOBD_AND_ALL_DTCS) */ 
#define DEM_CFG_DATA_AGED_COUNTER                                          STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_AGED_COUNTER exists, STD_OFF: else */ 
#define DEM_CFG_DATA_AGINGCTR                                              STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_AGINGCTR exists, STD_OFF: else */ 
#define DEM_CFG_DATA_AGINGCTR_INVERTED                                     STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_AGINGCTR_INVERTED exists, STD_OFF: else */ 
#define DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES                             STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_CONSECUTIVE_FAILED_CYCLES exists, STD_OFF: else */ 
#define DEM_CFG_DATA_CURRENT_FDC                                           STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_CURRENT_FDC exists, STD_OFF: else */ 
#define DEM_CFG_DATA_CYCLES_PASSED_OR_UNCONFIRMED_SINCE_FIRST_UNCONFIRMED  STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_CYCLES_PASSED_OR_UNCONFIRMED_SINCE_FIRST_UNCONFIRMED exists, STD_OFF: else */ 
#define DEM_CFG_DATA_CYCLES_PASSED_SINCE_LAST_UNCONFIRMED                  STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_CYCLES_PASSED_SINCE_LAST_UNCONFIRMED exists, STD_OFF: else */ 
#define DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED                             STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_CYCLES_SINCE_FIRST_FAILED exists, STD_OFF: else */ 
#define DEM_CFG_DATA_CYCLES_SINCE_FIRST_UNCONFIRMED                        STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_CYCLES_SINCE_FIRST_UNCONFIRMED exists, STD_OFF: else */ 
#define DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED                              STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_CYCLES_SINCE_LAST_FAILED exists, STD_OFF: else */ 
#define DEM_CFG_DATA_CYCLES_SINCE_LAST_UNCONFIRMED                         STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_CYCLES_SINCE_LAST_UNCONFIRMED exists, STD_OFF: else */ 
#define DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED                      STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_CYCLES_TESTED_SINCE_FIRST_FAILED exists, STD_OFF: else */ 
#define DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED                       STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_CYCLES_TESTED_SINCE_LAST_FAILED exists, STD_OFF: else */ 
#define DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA                                 STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_DAG_STANDARD_ENV_DATA_OPERATING_TIME exists, STD_OFF: else */ 
#define DEM_CFG_DATA_DAG_STANDARD_ENV_DATA                                 STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_DAG_STANDARD_ENV_DATA exists, STD_OFF: else */ 
#define DEM_CFG_DATA_DTC_STATUS_INDICATOR                                  STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_DTC_STATUS_INDICATOR exists, STD_OFF: else */ 
#define DEM_CFG_DATA_FAILED_CYCLES                                         STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_FAILED_CYCLES exists, STD_OFF: else */ 
#define DEM_CFG_DATA_FAULT_PENDING_COUNTER                                 STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_FAULT_PENDING_COUNTER exists, STD_OFF: else */ 
#define DEM_CFG_DATA_HEALINGCTR_DOWNCNT                                    STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_HEALINGCTR_DOWNCNT exists, STD_OFF: else */ 
#define DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE                          STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_MAX_FDC_DURING_CURRENT_CYCLE exists, STD_OFF: else */ 
#define DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR                              STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_MAX_FDC_SINCE_LAST_CLEAR exists, STD_OFF: else */ 
#define DEM_CFG_DATA_OBDDTC                                                STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_OBDDTC exists, STD_OFF: else */ 
#define DEM_CFG_DATA_OBDDTC_3BYTE                                          STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_OBDDTC_3BYTE exists, STD_OFF: else */ 
#define DEM_CFG_DATA_OBD_RATIO                                             STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_OBD_RATIO exists, STD_OFF: else */ 
#define DEM_CFG_DATA_OCCCTR                                                STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_OCCCTR exists, STD_OFF: else */ 
#define DEM_CFG_DATA_OCCCTR_2BYTE                                          STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_OCCCTR_2BYTE exists, STD_OFF: else */ 
#define DEM_CFG_DATA_OVFLIND                                               STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_OVFLIND exists, STD_OFF: else */ 
#define DEM_CFG_DATA_PRIORITY                                              STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_PRIORITY exists, STD_OFF: else */ 
#define DEM_CFG_DATA_ROOTCAUSE_EVENTID                                     STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_ROOTCAUSE_EVENTID exists, STD_OFF: else */ 
#define DEM_CFG_DATA_SIGNIFICANCE                                          STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_SIGNIFICANCE exists, STD_OFF: else */ 
#define DEM_CFG_DATA_UNCONFIRMED_CYCLES                                    STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemDataClass/DemDataElementInternalData == DEM_UNCONFIRMED_CYCLES exists, STD_OFF: else */ 
#define DEM_CFG_DISPLACEMENT_FALLBACK_OLDEST                               STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemEventDisplacementFallbackStrategy == DEM_FALLBACK_DISPLACE_OLDEST_EVENT */ 
#define DEM_CFG_DISPLACEMENT_PREFER_PASSIVE                                STD_ON       /* Autodetected - via /Dem/DemGeneral/DemEventDisplacementStrategy == (DEM_DISPLACEMENT_FULL | DEM_DISPLACEMENT_LEGACY_403) */ 
#define DEM_CFG_DISPLACEMENT_TNCTOC_IS_PASSIVE                             STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemEventDisplacementStrategy == DEM_DISPLACEMENT_FULL */ 
#define DEM_CFG_HAS_J1939_NODE                                             STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_HAS_STORAGE_CONDITIONS                                     STD_OFF      /* Internal - STD_ON: (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON) and have /Dem/DemGeneral/DemStorageCondition container(s)) and (not PreCompile implementation variant or have /Dem/DemGeneral/DemStorageConditionGroup container(s)); STD_OFF: (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_OFF) or no /Dem/DemGeneral/DemStorageCondition containers or (variant PreCompile and no /Dem/DemGeneral/DemStorageConditionGroup containers) */ 
#define DEM_CFG_ISCONST_AVAILABLEINVARIANT                                 STD_ON       /* Autodetected - STD_ON: all /Dem/DemConfigSet/DemEventParameter/DemEventAvailableInVariant == TRUE, STD_OFF: else */ 
#define DEM_CFG_NOTIFY_CLEAR_ALLOWED                                       STD_OFF      /* Autodetected - STD_ON: /Dem/DemConfigSet/DemEventParameter/DemCallbackClearEventAllowed container(s) exist, STD_OFF: no such container */ 
#define DEM_CFG_NOTIFY_CONTROL_DTC_SETTING                                 STD_OFF      /* Vector extension - /Dem/DemGeneral/DemTriggerControlDTCSetting */ 
#define DEM_CFG_NOTIFY_DCM                                                 STD_OFF      /* /Dem/DemGeneral/DemTriggerDcmReports */ 
#define DEM_CFG_NOTIFY_DLT                                                 STD_OFF      /* /Dem/DemGeneral/DemTriggerDltReports */ 
#define DEM_CFG_NOTIFY_DTC_STATUS                                          STD_OFF      /* Autodetected - STD_ON: /Dem/DemGeneral/DemCallbackDTCStatusChanged container(s) exist, STD_OFF: no such container */ 
#define DEM_CFG_NOTIFY_ENABLECONDITION                                     STD_OFF      /* Vector extension - /Dem/DemGeneral/DemTriggerMonitorInitForEnableConditions */ 
#define DEM_CFG_NOTIFY_EVENT_DATA                                          STD_OFF      /* Autodetected - STD_ON: /Dem/DemConfigSet/DemEventParameter/DemCallbackEventDataChanged container(s) exist, STD_OFF: no such container */ 
#define DEM_CFG_NOTIFY_EVENT_STATUS                                        STD_OFF      /* Autodetected - STD_ON: /Dem/DemConfigSet/DemEventParameter/DemCallbackEventStatusChanged container(s) exist, STD_OFF: no such container */ 
#define DEM_CFG_NOTIFY_EVENT_STATUS_FIM                                    STD_OFF      /* /Dem/DemGeneral/DemTriggerFiMReportsExtended */ 
#define DEM_CFG_NOTIFY_GENERAL_DATA                                        STD_OFF      /* Autodetected - STD_ON: any /Dem/DemConfigSet/DemEventParameter/DemCallbackEventDataChanged container defines a port-if, STD_OFF: no such container or only C-functions */ 
#define DEM_CFG_NOTIFY_GENERAL_MONITORSTATUS_CHANGED                       STD_OFF      /* Autodetected - STD_ON: parameter /Dem/DemGeneral/DemGeneralCallbackMonitorStatusChangedFnc defines notification function, STD_OFF: no (valid) C-function definition */ 
#define DEM_CFG_NOTIFY_GENERAL_STATUS                                      STD_OFF      /* Autodetected - STD_ON: any /Dem/DemConfigSet/DemEventParameter/DemCallbackEventStatusChanged container defines a port-if, STD_OFF: no such container or only C-functions */ 
#define DEM_CFG_NOTIFY_INIT_FUNC                                           STD_OFF      /* Autodetected - STD_ON: /Dem/DemConfigSet/DemDTCClass/DemCallbackInitMForF container(s) exist (and DTC is ref'd by an event), STD_OFF: no such container */ 
#define DEM_CFG_NOTIFY_INIT_MONITOR                                        STD_OFF      /* Autodetected - STD_ON: /Dem/DemConfigSet/DemEventParameter/DemCallbackInitMForE container(s) exist, STD_OFF: no such container */ 
#define DEM_CFG_NOTIFY_J1939DCM                                            STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_NOTIFY_J1939DTC_STATUS                                     STD_OFF      /* Autodetected - STD_ON: /Dem/DemGeneral/DemGeneralJ1939/DemCallbackJ1939DTCStatusChanged container(s) exist, STD_OFF: no such container */ 
#define DEM_CFG_NOTIFY_MONITOR_STATUS_FIM                                  STD_OFF      /* /Dem/DemGeneral/DemTriggerFiMReports */ 
#define DEM_CFG_PROCESS_CDTC_ALL_DTC                                       STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemResetConfirmedBitOnOverflow == FALSE */ 
#define DEM_CFG_PROCESS_CDTC_STOREDONLY                                    STD_ON       /* Autodetected - via /Dem/DemGeneral/DemResetConfirmedBitOnOverflow == TRUE */ 
#define DEM_CFG_PROCESS_OCCTR_CONFIRMED                                    STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemOccurrenceCounterProcessing == DEM_PROCESS_OCCCTR_CDTC */ 
#define DEM_CFG_PROCESS_OCCTR_TESTFAILED                                   STD_ON       /* Autodetected - via /Dem/DemGeneral/DemOccurrenceCounterProcessing == DEM_PROCESS_OCCCTR_TF */ 
#define DEM_CFG_PROCESS_PDTC_ALL_DTC                                       STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemPendingDtcProcessing == DEM_PROCESS_PDTC_ALL_DTC */ 
#define DEM_CFG_PROCESS_PDTC_STOREDONLY                                    STD_ON       /* Autodetected - via /Dem/DemGeneral/DemPendingDtcProcessing == DEM_PROCESS_PDTC_STOREDONLY */ 
#define DEM_CFG_PROCESS_PID41_COMPREHENSIVE_COMPLETE                       STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_PROCESS_TFSLC_ALL_DTC                                      STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemStatusBitHandlingTestFailedSinceLastClear == DEM_STATUS_BIT_AGING */ 
#define DEM_CFG_PROCESS_TFSLC_CLEARONLY                                    STD_ON       /* Autodetected - via /Dem/DemGeneral/DemStatusBitHandlingTestFailedSinceLastClear == DEM_STATUS_BIT_NORMAL */ 
#define DEM_CFG_PROCESS_TFSLC_STOREDONLY                                   STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemStatusBitHandlingTestFailedSinceLastClear == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT */ 
#define DEM_CFG_PROCESS_WIR_ALL_DTC                                        STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemWarningIndicatorRequestedProcessing == DEM_PROCESS_WIR_ALL_DTC */ 
#define DEM_CFG_PROCESS_WIR_STOREDONLY                                     STD_ON       /* Autodetected - via /Dem/DemGeneral/DemWarningIndicatorRequestedProcessing == DEM_PROCESS_WIR_STOREDONLY */ 
#define DEM_CFG_REPORT_BLINKING_MIL_AS_ACTIVE                              STD_ON       /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_REPORT_SUPPRESSED_DTCS_IN_19_0A                            STD_ON       /* Vector extension - /Dem/DemGeneral/DemReportSuppressedDTCsInService19x0A */ 
#define DEM_CFG_RESET_DEBOUNCE_ON_DISABLE_ENABLE_CONDITIONS                STD_ON       /* Autodetected - via /Dem/DemGeneral/DemResetDebounceBehavior == DEM_RESET_DEBOUNCE_ON_DISABLE_ENABLE_CONDITIONS */ 
#define DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS                 STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemResetDebounceBehavior == DEM_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS */ 
#define DEM_CFG_SAFE_BSW_MODE                                              STD_OFF      /* Vector extension - /Dem/DemGeneral/DemSafeBswChecks */ 
#define DEM_CFG_STORAGE_AT_CONFIRMED                                       STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemEventMemoryEntryStorageTrigger == DEM_STORAGE_ON_CONFIRMED */ 
#define DEM_CFG_STORAGE_AT_FAILED                                          STD_ON       /* Autodetected - via /Dem/DemGeneral/DemEventMemoryEntryStorageTrigger == DEM_STORAGE_ON_TEST_FAILED */ 
#define DEM_CFG_STORAGE_AT_FDC                                             STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemEventMemoryEntryStorageTrigger == DEM_STORAGE_ON_FDC_THRESHOLD */ 
#define DEM_CFG_STORAGE_AT_PENDING                                         STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemEventMemoryEntryStorageTrigger == DEM_STORAGE_ON_PENDING */ 
#define DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS                                 STD_OFF      /* Vector extension - /Dem/DemGeneral/DemSupportAgingForAllDTCs */ 
#define DEM_CFG_SUPPORT_AWL                                                STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_CLEAR_DTC_RUNTIME_LIMIT                            STD_OFF      /* Vector extension - /Dem/DemGeneral/DemClearDTCRuntimeLimit */ 
#define DEM_CFG_SUPPORT_CLEAR_PDTC_NO_PFC                                  STD_OFF      /* (DEM_CFG_SUPPORT_OBDII == STD_OFF) */ 
#define DEM_CFG_SUPPORT_CLEAR_TESTFAILED_ON_OPCYCLE                        STD_OFF      /* Vector extension - /Dem/DemGeneral/DemResetTestFailedOnOperationCycleStart */ 
#define DEM_CFG_SUPPORT_CLIENTS                                            STD_ON       /* Autodetected - STD_ON: 1 or more /Dem/DemGeneral/DemClient exists, STD_OFF: else */ 
#define DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME                     STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME                     STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_CYCLE_IGNITION                                     STD_ON       /* Autodetected - STD_ON: cycle type is referenced by any *CycleRef or the /Dem/DemGeneral/DemRestartCycleOnInitRef parameter, STD_OFF: cycle type is not referenced. The '*CycleRef' params are (here 3 refs): /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemAgingCycleRef, ~/DemOperationCycleRef, ~/DemIndicatorAttribute/DemIndicatorFailureCycleRef and ~/DemIndicatorAttribute/DemIndicatorHealingCycleRef. */ 
#define DEM_CFG_SUPPORT_CYCLE_IGNITION_HYBRID                              STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemOperationCycle/DemOperationCycleType == DEM_OPCYC_IGNITION_HYBRID exists, STD_OFF: else. */ 
#define DEM_CFG_SUPPORT_CYCLE_OBD_DCY                                      STD_OFF      /* Autodetected - STD_ON: cycle type is referenced by any *CycleRef or the /Dem/DemGeneral/DemRestartCycleOnInitRef parameter, STD_OFF: cycle type is not referenced. The '*CycleRef' params are (here 0 refs): /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemAgingCycleRef, ~/DemOperationCycleRef, ~/DemIndicatorAttribute/DemIndicatorFailureCycleRef and ~/DemIndicatorAttribute/DemIndicatorHealingCycleRef. */ 
#define DEM_CFG_SUPPORT_CYCLE_OTHER                                        STD_OFF      /* Autodetected - STD_ON: cycle type is referenced by any *CycleRef or the /Dem/DemGeneral/DemRestartCycleOnInitRef parameter, STD_OFF: cycle type is not referenced. The '*CycleRef' params are (here 0 refs): /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemAgingCycleRef, ~/DemOperationCycleRef, ~/DemIndicatorAttribute/DemIndicatorFailureCycleRef and ~/DemIndicatorAttribute/DemIndicatorHealingCycleRef. */ 
#define DEM_CFG_SUPPORT_CYCLE_POWER                                        STD_ON       /* Autodetected - STD_ON: cycle type is referenced by any *CycleRef or the /Dem/DemGeneral/DemRestartCycleOnInitRef parameter, STD_OFF: cycle type is not referenced. The '*CycleRef' params are (here 36 refs): /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemAgingCycleRef, ~/DemOperationCycleRef, ~/DemIndicatorAttribute/DemIndicatorFailureCycleRef and ~/DemIndicatorAttribute/DemIndicatorHealingCycleRef. */ 
#define DEM_CFG_SUPPORT_CYCLE_TIME                                         STD_OFF      /* Autodetected - STD_ON: cycle type is referenced by any *CycleRef or the /Dem/DemGeneral/DemRestartCycleOnInitRef parameter, STD_OFF: cycle type is not referenced. The '*CycleRef' params are (here 0 refs): /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemAgingCycleRef, ~/DemOperationCycleRef, ~/DemIndicatorAttribute/DemIndicatorFailureCycleRef and ~/DemIndicatorAttribute/DemIndicatorHealingCycleRef. */ 
#define DEM_CFG_SUPPORT_CYCLE_WARMUP                                       STD_OFF      /* Autodetected - STD_ON: cycle type is referenced by any *CycleRef or the /Dem/DemGeneral/DemRestartCycleOnInitRef parameter, STD_OFF: cycle type is not referenced. The '*CycleRef' params are (here 0 refs): /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemAgingCycleRef, ~/DemOperationCycleRef, ~/DemIndicatorAttribute/DemIndicatorFailureCycleRef and ~/DemIndicatorAttribute/DemIndicatorHealingCycleRef. */ 
#define DEM_CFG_SUPPORT_DCM                                                STD_ON       /* Vector extension - /Dem/DemGeneral/DemDcmSupport */ 
#define DEM_CFG_SUPPORT_DEBOUNCE_COUNTER                                   STD_ON       /* /Dem/DemGeneral/DemDebounceCounterBasedSupport */ 
#define DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL                           STD_OFF      /* Autodetected - STD_ON: any /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceMonitorInternal container exists, STD_OFF: else */ 
#define DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL_GETFDC                    STD_OFF      /* Autodetected - STD_ON: any /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceMonitorInternal/DemCallbackGetFDC container exists, STD_OFF: else */ 
#define DEM_CFG_SUPPORT_DEBOUNCE_NV                                        STD_OFF      /* Autodetected - STD_ON: any /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased/DemDebounceCounterStorage == TRUE, STD_OFF: no such parameter */ 
#define DEM_CFG_SUPPORT_DEBOUNCE_TIME                                      STD_OFF      /* /Dem/DemGeneral/DemDebounceTimeBasedSupport */ 
#define DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY                                   STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_DISABLED_COMBINATION                               STD_ON       /* Autodetected - via /Dem/DemGeneral/DemEventCombinationSupport == DEM_EVCOMB_DISABLED */ 
#define DEM_CFG_SUPPORT_DISPLACEMENT                                       STD_ON       /* Autodetected - via /Dem/DemGeneral/DemEventDisplacementStrategy == (DEM_DISPLACEMENT_PRIO_OCC | DEM_DISPLACEMENT_FULL | DEM_DISPLACEMENT_LEGACY_403) */ 
#define DEM_CFG_SUPPORT_DLT                                                STD_OFF      /* Feature not supported. */ 
#define DEM_CFG_SUPPORT_DTCSUPPRESSION                                     STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemSuppressionSupport == (DEM_DTC_SUPPRESSION | DEM_EVENT_AND_DTC_SUPPRESSION) */ 
#define DEM_CFG_SUPPORT_DTR                                                STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_ENABLE_CONDITIONS                                  STD_OFF      /* /Dem/DemGeneral/DemEnableConditionSupport */ 
#define DEM_CFG_SUPPORT_ERECS                                              STD_ON       /* Internal - STD_ON: any DTC has ExtendedDataRecord(s), STD_OFF: no DTC has ExtendedDataRecords */ 
#define DEM_CFG_SUPPORT_EVENTAVAILABLE                                     STD_OFF      /* Autodetected - STD_ON: /Dem/DemGeneral/DemAvailabilitySupport == DEM_EVENT_AVAILABILITY, STD_OFF: else */ 
#define DEM_CFG_SUPPORT_EVENTAVAILABLE_DEFAULT                             STD_ON       /* Vector extension - /Dem/DemGeneral/DemPostbuild/DemEventAvailableDefaultSupport */ 
#define DEM_CFG_SUPPORT_EVENTAVAILABLE_NV                                  STD_OFF      /* Autodetected - STD_ON: /Dem/DemGeneral/DemAvailabilityStorage == TRUE, STD_OFF: else */ 
#define DEM_CFG_SUPPORT_EVENTSUPPRESSION                                   STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemSuppressionSupport == (DEM_EVENT_SUPPRESSION | DEM_EVENT_AND_DTC_SUPPRESSION) */ 
#define DEM_CFG_SUPPORT_EVENT_QUEUE                                        STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemBswErrorBufferSize > 0 */ 
#define DEM_CFG_SUPPORT_FREEZEFRAME                                        STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemMaxNumberEventEntryOBDFreezeFrame > 0 */ 
#define DEM_CFG_SUPPORT_GLOBAL_SRECS                                       STD_OFF      /* Vector extension - /Dem/DemGeneral/DemGlobalFreezeFrame */ 
#define DEM_CFG_SUPPORT_INDICATORS                                         STD_OFF      /* Autodetected - STD_ON: /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemIndicatorAttribute container(s) exist, STD_OFF: no such container */ 
#define DEM_CFG_SUPPORT_IUMPR                                              STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_J1939                                              STD_OFF      /* Feature not licensed. */ 
#define DEM_CFG_SUPPORT_J1939_CLEAR_DTC                                    STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_J1939_DM31                                         STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME                         STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_J1939_FREEZEFRAME                                  STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_J1939_RATIO                                        STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_J1939_READINESS1                                   STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_J1939_READINESS2                                   STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_J1939_READINESS3                                   STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_J1939_READ_DTC                                     STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_MAJOR_MONITORS                                     STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_MIL                                                STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_MIL_GROUP                                          STD_OFF      /* Vector extension - STD_ON: [PreCompile] any valid /Dem/DemConfigSet/DemDTCClass/DemMILGroupRef exists, STD_OFF: else. */ 
#define DEM_CFG_SUPPORT_MIRROR                                             STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemMaxNumberEventEntryMirror > 0 */ 
#define DEM_CFG_SUPPORT_MULTIPLE_SATELLITES                                STD_OFF      /* Autodetected - STD_ON: count of different /Dem/DemConfigSet/DemEventParameter/DemOsApplicationRef plus /Dem/DemGeneral/DemOsApplicationRef targets > 1; STD_OFF: master and all satellites run in the same partition */ 
#define DEM_CFG_SUPPORT_MULTITRIP                                          STD_OFF      /* Autodetected - STD_ON: any /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemIndicatorAttribute/DemIndicatorHealingCycleCounterThreshold parameter or /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemEventFailureCycleCounterThreshold parameter has value > 1 or DEM module has Implemenation Variant VARIANT-POST-BUILD-LOADABLE, STD_OFF: (no such parameters or all values <= 1) and module is VARIANT-PRE-COMPILE */ 
#define DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE                               STD_OFF      /* Vector extension - /Dem/DemGeneral/DemNvSynchronizeSupport */ 
#define DEM_CFG_SUPPORT_NVM_IMMEDIATE                                      STD_ON       /* Autodetected - STD_ON: /Dem/DemGeneral/DemImmediateNvStorageSupport == TRUE || any /Dem/DemConfigSet/DemDTCClass/DemImmediateNvStorage == TRUE - STD_OFF: StorageSupport parameter absent or FALSE and all DTCClass values == FALSE */ 
#define DEM_CFG_SUPPORT_NVM_WRITELIMIT                                     STD_OFF      /* Autodetected - STD_ON: /Dem/DemGeneral/DemImmediateNvStorageLimit parameter exists, STD_OFF: no such parameter */ 
#define DEM_CFG_SUPPORT_OBDII                                              STD_OFF      /* Feature not licensed. */ 
#define DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19                         STD_OFF      /* (DEM_CFG_SUPPORT_OBDII == STD_OFF) */ 
#define DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES                               STD_OFF      /* (DEM_CFG_SUPPORT_OBDII == STD_OFF) */ 
#define DEM_CFG_SUPPORT_OBD_PTO                                            STD_OFF      /* (DEM_CFG_SUPPORT_OBDII == STD_OFF) */ 
#define DEM_CFG_SUPPORT_OPCYCLE_AUTOMATIC_END                              STD_OFF      /* Autodetected - STD_ON: any /Dem/DemGeneral/DemOperationCycle/DemOperationCycleAutomaticEnd == TRUE, STD_OFF: all parameters are either undefined or FALSE. */ 
#define DEM_CFG_SUPPORT_OPCYCLE_STORAGE                                    STD_OFF      /* /Dem/DemGeneral/DemOperationCycleStatusStorage */ 
#define DEM_CFG_SUPPORT_OVFLIND_API                                        STD_ON       /* Vector extension - /Dem/DemGeneral/DemEvMemOverflowIndicationSupport == TRUE */ 
#define DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME                      STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME                       STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_PENDING_UPDATE_FREEZE_FRAME                        STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_PERMANENT                                          STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemMaxNumberEventEntryPermanent > 0 */ 
#define DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE                   STD_OFF      /* (DEM_CFG_SUPPORT_OBDII == STD_OFF) */ 
#define DEM_CFG_SUPPORT_PERMANENT_CONDITION_DCY                            STD_OFF      /* (DEM_CFG_SUPPORT_OBDII == STD_OFF) */ 
#define DEM_CFG_SUPPORT_PERMANENT_MANDATORY_PFC                            STD_OFF      /* (DEM_CFG_SUPPORT_OBDII == STD_OFF) */ 
#define DEM_CFG_SUPPORT_PID01                                              STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_PID1C                                              STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_PID21                                              STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_PID30                                              STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_PID31                                              STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_PID41                                              STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_PID4D                                              STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_PID4E                                              STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_PID91                                              STD_OFF      /* (DEM_CFG_SUPPORT_WWHOBD == STD_OFF) */ 
#define DEM_CFG_SUPPORT_PL                                                 STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_PRESTORED_FF                                       STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemMaxNumberPrestoredFF > 0 */ 
#define DEM_CFG_SUPPORT_PRIMARY                                            STD_ON       /* Autodetected - via /Dem/DemGeneral/DemMaxNumberEventEntryPrimary > 0 */ 
#define DEM_CFG_SUPPORT_RESTART_CYCLE                                      STD_OFF      /* Vector extension - /Dem/DemGeneral/DemRestartCycleOnInitRef */ 
#define DEM_CFG_SUPPORT_RESTART_DCY_ON_CLEAR_DTC                           STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_RETRY_STORAGE                                      STD_OFF      /* Vector extension - /Dem/DemGeneral/DemRetryStorageSupport */ 
#define DEM_CFG_SUPPORT_RSL                                                STD_OFF      /* (DEM_CFG_SUPPORT_J1939 == STD_OFF) */ 
#define DEM_CFG_SUPPORT_SECONDARY                                          STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemMaxNumberEventEntrySecondary > 0 */ 
#define DEM_CFG_SUPPORT_SIMILAR_CONDITIONS                                 STD_OFF      /* ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) */ 
#define DEM_CFG_SUPPORT_SRECS                                              STD_OFF      /* Internal - STD_ON: any EventParameter references FreezeFrame(s), STD_OFF: no EventParameter references FreezeFrames */ 
#define DEM_CFG_SUPPORT_SRECS_CALCULATED                                   STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemTypeOfFreezeFrameRecordNumeration == DEM_FF_RECNUM_CALCULATED */ 
#define DEM_CFG_SUPPORT_SRECS_CONFIGURED                                   STD_ON       /* Autodetected - via /Dem/DemGeneral/DemTypeOfFreezeFrameRecordNumeration == DEM_FF_RECNUM_CONFIGURED */ 
#define DEM_CFG_SUPPORT_STORAGE_CONDITIONS                                 STD_OFF      /* /Dem/DemGeneral/DemStorageConditionSupport */ 
#define DEM_CFG_SUPPORT_TESTFAILED_STORAGE                                 STD_ON       /* /Dem/DemGeneral/DemStatusBitStorageTestFailed */ 
#define DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST                            STD_OFF      /* Autodetected - STD_ON: (/Dem/DemGeneral/DemMaxNumberTimeSeriesSnapshots > 0) && (/Dem/DemGeneral/DemTimeSeriesSnapshot/DemTimeSeriesFastRateFutureSamples > 0) && (PostBuild-Loadable || any event has DemEventTimeSeries==FAST_RATE), STD_OFF: else. */ 
#define DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL                          STD_OFF      /* Autodetected - STD_ON: (/Dem/DemGeneral/DemMaxNumberTimeSeriesSnapshots > 0) && (/Dem/DemGeneral/DemTimeSeriesSnapshot/DemTimeSeriesNormalRateFutureSamples > 0) && (PostBuild-Loadable || any event has DemEventTimeSeries==NORMAL_RATE|FAST_RATE), STD_OFF: else. */ 
#define DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST                              STD_OFF      /* Autodetected - STD_ON: (/Dem/DemGeneral/DemMaxNumberTimeSeriesSnapshots > 0) && (/Dem/DemGeneral/DemTimeSeriesSnapshot/DemTimeSeriesFastRatePastSamples > 0) && (PostBuild-Loadable || any event has DemEventTimeSeries==FAST_RATE), STD_OFF: else. */ 
#define DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL                            STD_OFF      /* Autodetected - STD_ON: (/Dem/DemGeneral/DemMaxNumberTimeSeriesSnapshots > 0) && (/Dem/DemGeneral/DemTimeSeriesSnapshot/DemTimeSeriesNormalRatePastSamples > 0) && (PostBuild-Loadable || any event has DemEventTimeSeries==NORMAL_RATE|FAST_RATE), STD_OFF: else. */ 
#define DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE                         STD_OFF      /* STD_ON: any /Dem/DemGeneral/DemFreezeFrameRecNumClass/DemFreezeFrameRecordTrigger has value DEM_RECORD_TRIGGER_TESTFAILED_FIRST_IN_CYCLE or DEM_RECORD_TRIGGER_FDC_FIRST_IN_CYCLE, STD_OFF: else. */ 
#define DEM_CFG_SUPPORT_TYPE1_COMBINATION                                  STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemEventCombinationSupport == DEM_EVCOMB_TYPE1 */ 
#define DEM_CFG_SUPPORT_TYPE2_COMBINATION                                  STD_OFF      /* Autodetected - via /Dem/DemGeneral/DemEventCombinationSupport == DEM_EVCOMB_TYPE2 */ 
#define DEM_CFG_SUPPORT_USER_CAS                                           STD_OFF      /* Vector extension - /Dem/DemGeneral/DemUserDefinedCompareAndSwap */ 
#define DEM_CFG_SUPPORT_USER_CONTROLLED_WIR                                STD_OFF      /* Vector extension - /Dem/DemGeneral/DemUserControlledWirSupport */ 
#define DEM_CFG_SUPPORT_USER_CONTROLLED_WIR_DURING_CDTCS                   STD_ON       /* Autodetected - via /Dem/DemGeneral/DemUserControlledWirBehavior == DEM_ENABLED_DURING_CONTROLDTCSETTING */ 
#define DEM_CFG_SUPPORT_USER_ERECS                                         STD_ON       /* Internal - STD_ON: require generic buffer ExtendedData[], STD_OFF: all configured DemDataClass of DemExtendedDataRecordClass have individual buffers in Dem_Cfg_PrimaryEntryType */ 
#define DEM_CFG_SUPPORT_USER_INDICATORS                                    STD_OFF      /* Autodetected - STD_ON: any event has a user (non-special) indicator, STD_OFF: no event has standard user indicator (but some events may have a special indicators like MIL or any J1939 Lamp) */ 
#define DEM_CFG_SUPPORT_VERSION_INFO                                       STD_ON       /* /Dem/DemGeneral/DemVersionInfoApi */ 
#define DEM_CFG_SUPPORT_VID08                                              STD_OFF      /* (DEM_CFG_SUPPORT_OBDII == STD_OFF) */ 
#define DEM_CFG_SUPPORT_VID0B                                              STD_OFF      /* (DEM_CFG_SUPPORT_OBDII == STD_OFF) */ 
#define DEM_CFG_SUPPORT_WWHOBD                                             STD_OFF      /* Feature not licensed. */ 
#define DEM_CFG_USE_MEMCOPY_MACROS                                         STD_OFF      /* Vector extension - /Dem/DemGeneral/DemUseMemcopyMacros */ 
#define DEM_CFG_USE_MULTI_PARTITION_FIM                                    STD_OFF      /* Vector extension - /Dem/DemGeneral/DemUseMultiPartitionFiM */ 
#define DEM_CFG_USE_NVM                                                    STD_OFF      /* Overwritten by Vector extension - /Dem/DemGeneral/DemUseNvm */ 
#define DEM_CFG_USE_OHDS                                                   STD_OFF      /* Vector extension - /Dem/DemGeneral/DemUseOHDS */ 

 /*  Timebased debouncing - high/low resolution timer values are configured (or may be configured by PostBuild-Loadable)  */ 
#define DEM_CFG_SUPPORT_DEBOUNCE_TIME_HR                              STD_OFF      /* Autodetected - STD_ON: any event requires the high-resolution timer, i.e. any /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceTimeBase/DemDebounceTimeFailedThreshold or ~/DemDebounceTimePassedThreshold parameter is < /Dem/DemGeneral/DemDebounceTimeLowResThreshold (here: 5.0s), STD_OFF: all configured DemDebounceTimeFailedThreshold and DemDebounceTimePassedThreshold values are >= 5.0s */ 
#define DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR                              STD_OFF      /* Autodetected - STD_ON: any event requires the low-resolution timer, i.e. any /Dem/DemConfigSet/DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceTimeBase/DemDebounceTimeFailedThreshold or ~/DemDebounceTimePassedThreshold parameter is >= /Dem/DemGeneral/DemDebounceTimeLowResThreshold (here: 5.0s), STD_OFF: all configured DemDebounceTimeFailedThreshold and DemDebounceTimePassedThreshold values are < 5.0s */ 

 /*  Dem global switches  */ 
#define DEM_CFG_USE_RTE                                               STD_ON       /* Vector extension - /Dem/DemGeneral/DemUseRte */ 



/* -----------------------------------------------------------------------------
    EcuC and general definitions
 ----------------------------------------------------------------------------- */
#ifndef DEM_DEV_ERROR_DETECT
#define DEM_DEV_ERROR_DETECT STD_OFF
#endif
#ifndef DEM_DEV_ERROR_REPORT
#define DEM_DEV_ERROR_REPORT STD_OFF
#endif
#ifndef DEM_USE_DUMMY_STATEMENT
#define DEM_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/EcuC/EcucGeneral/DummyStatement */
#endif
#ifndef DEM_DUMMY_STATEMENT
#define DEM_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef DEM_DUMMY_STATEMENT_CONST
#define DEM_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef DEM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define DEM_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef DEM_ATOMIC_VARIABLE_ACCESS
#define DEM_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef DEM_PROCESSOR_RH850_1649
#define DEM_PROCESSOR_RH850_1649
#endif
#ifndef DEM_COMP_GREENHILLS
#define DEM_COMP_GREENHILLS
#endif
#ifndef DEM_GEN_GENERATOR_MSR
#define DEM_GEN_GENERATOR_MSR
#endif
#ifndef DEM_CPUTYPE_BITORDER_LSB2MSB
#define DEM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef DEM_CONFIGURATION_VARIANT_PRECOMPILE
#define DEM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef DEM_CONFIGURATION_VARIANT_LINKTIME
#define DEM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef DEM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define DEM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef DEM_CONFIGURATION_VARIANT
#define DEM_CONFIGURATION_VARIANT DEM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef DEM_POSTBUILD_VARIANT_SUPPORT
#define DEM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif



#define DEM_CFG_DIAGNOSTIC_OEM                                        DEM_OEM_VAG
#define DEM_CFG_HAVE_LICENSE_OBDII                                    STD_OFF                    /* Licensed feature "Diag_AsrDem_OBDSupport" */
#define DEM_CFG_HAVE_LICENSE_WWHOBD                                   STD_OFF                    /* Licensed feature "Diag_AsrDem_WwhObd" */
#define DEM_CFG_HAVE_LICENSE_J1939                                    STD_OFF                    /* Licensed feature "Diag_AsrDem_J1939Support" */
#define DEM_INIT_DATA                                                 DEM_CFG_INIT_DATA         /* Memory class of the initialization data. */

/* --------------------------------------------------------------------------- */

#define DEM_CFG_USE_DET                                               DEM_DEV_ERROR_REPORT      /* /Dem/DemGeneral/DemDevErrorDetect */

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  Justification of MISRA deviations
**********************************************************************************************************************/


#endif  /* DEM_CFG_H */
/**********************************************************************************************************************
  END OF FILE: Dem_Cfg.h     [Vag (Vector), VARIANT-PRE-COMPILE, 16.06.00.107213]
**********************************************************************************************************************/

