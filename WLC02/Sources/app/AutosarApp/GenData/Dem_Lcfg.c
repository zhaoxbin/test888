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
 *              File: Dem_Lcfg.c
 *   Generation Time: 2020-09-22 21:48:45
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


/* configuration, interrupt handling implementations differ from the
 * source identification define used here. The naming
 * schemes for those files can be taken from this list:
 *
 * Dem.c:         DEM_SOURCE
 * Dem_Lcfg.c:    DEM_LCFG_SOURCE
 * Dem_PBcfg.c:   DEM_PBCFG_SOURCE */
#define DEM_LCFG_SOURCE


/**********************************************************************************************************************
  MISRA JUSTIFICATIONS
**********************************************************************************************************************/

/* PRQA S 0810 EOF */ /* MD_MSR_1.1_810 */                                      /* #include "..." causes nesting to exceed 8 levels - program is non-conforming. -- caused by #include'd files. */
/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */                                      /* Maximum '#if...' nesting exceeds 8 levels - program is non-conforming -- caused by #include'd files. */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */                                      /* Number of macro definitions exceeds 1024 - program is non-conforming -- caused by #include'd files. */
/* PRQA S 0779 EOF */ /* MD_DEM_5.1 */                                          /* Identifier does not differ in 32 significant characters -- caused by Autosar algorithm for unique symbolic names. */
/* PRQA S 0612 EOF */ /* MD_DEM_1.1_612 */                                      /* The size of an object exceeds 32767 bytes - program is non-conforming -- caused by large user configration. */


/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/

#include "Dem.h"
#include "Os.h"
#if (DEM_CFG_USE_NVM == STD_ON)
# include "NvM.h"                                                               /* get: symbolic names for NvM block IDs */
#endif
#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
# include "J1939Nm.h"                                                           /* get: symbolic names for J1939Nm node IDs */
#endif
#if (DEM_CFG_USE_RTE == STD_ON)
/* DEM used with RTE */
# include "Rte_DemMaster_0.h"
#endif
#include "Dem_AdditionalIncludeCfg.h"                                           /* additional, configuration defined files */

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/



/**********************************************************************************************************************
  LOCAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA
**********************************************************************************************************************/



/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  Dem_Cfg_CycleIdTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_CycleIdTable
  \details
  Element         Description
  UsedForAging    DemOperationCycle is target of any DemEventParameter/DemEventClass/DemAgingCycleRef
  OpCycleType     DemOperationCycleType of the DemOperationCycle: [DEM_CFG_OPCYC_IGNITION, DEM_CFG_OPCYC_OBD_DCY, DEM_CFG_OPCYC_OTHER, DEM_CFG_OPCYC_POWER, DEM_CFG_OPCYC_TIME, DEM_CFG_OPCYC_WARMUP, DEM_CFG_OPCYC_IGNITION_HYBRID, DEM_CFG_OPCYC_AGING]
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_CycleIdTableType, DEM_CONST) Dem_Cfg_CycleIdTable[4] = {
    /* Index    UsedForAging  OpCycleType                   Comment */
  { /*     0 */        FALSE, DEM_CFG_OPCYC_IGNITION },  /* [DemConf_DemOperationCycle_IgnitionCycle] */
  { /*     1 */        FALSE, DEM_CFG_OPCYC_OBD_DCY  },  /* [DemConf_DemOperationCycle_OBDDrivingCycle] */
  { /*     2 */         TRUE, DEM_CFG_OPCYC_POWER    },  /* [DemConf_DemOperationCycle_PowerCycle] */
  { /*     3 */        FALSE, DEM_CFG_OPCYC_WARMUP   }   /* [DemConf_DemOperationCycle_WarmUpCycle] */
};
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DataCollectionTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DataCollectionTable
  \details
  Element                                Description
  CollectionSize                     
  DataElementTableCol2ElmtIndEndIdx      the end index of the 0:n relation pointing to Dem_Cfg_DataElementTableCol2ElmtInd
  DataElementTableCol2ElmtIndStartIdx    the start index of the 0:n relation pointing to Dem_Cfg_DataElementTableCol2ElmtInd
  IdNumber                           
  MaskedBits                             contains bitcoded the boolean data of Dem_Cfg_DataElementTableCol2ElmtIndUsedOfDataCollectionTable, Dem_Cfg_UpdateOfDataCollectionTable
  StorageKind                        
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_DataCollectionTableType, DEM_CONST) Dem_Cfg_DataCollectionTable[7] = {
    /* Index    CollectionSize  DataElementTableCol2ElmtIndEndIdx                                  DataElementTableCol2ElmtIndStartIdx                                  IdNumber  MaskedBits  StorageKind                     Referable Keys */
  { /*     0 */             0u, DEM_CFG_NO_DATAELEMENTTABLECOL2ELMTINDENDIDXOFDATACOLLECTIONTABLE, DEM_CFG_NO_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE,  0x0000u,      0x00u, DEM_CFG_EREC_TYPE_GLOBAL },  /* [#NoDataCollectionConfigured] */
  { /*     1 */             1u,                                                                1u,                                                                  0u,  0x0004u,      0x03u, DEM_CFG_EREC_TYPE_USER   },  /* [#EdrDemExtendedDataRecordClass_LV_Battary_Voltage, Ext:DemExtendedDataClass] */
  { /*     2 */             6u,                                                                2u,                                                                  1u,  0x0002u,      0x03u, DEM_CFG_EREC_TYPE_USER   },  /* [#EdrDemExtendedDataRecordClass_Timestamp, Ext:DemExtendedDataClass] */
  { /*     3 */             2u,                                                                3u,                                                                  2u,  0x0005u,      0x03u, DEM_CFG_EREC_TYPE_USER   },  /* [#EdrDemExtendedDataRecordClass_Vehicle_Speed, Ext:DemExtendedDataClass] */
  { /*     4 */             1u,                                                                4u,                                                                  3u,  0x0001u,      0x02u, DEM_CFG_EREC_TYPE_USER   },  /* [#EdrOccurrenceCounter, Ext:DemExtendedDataClass] */
  { /*     5 */             3u,                                                                5u,                                                                  4u,  0x0003u,      0x02u, DEM_CFG_EREC_TYPE_USER   },  /* [#EdrOdometerValue, Ext:DemExtendedDataClass] */
  { /*     6 */             2u,                                                                6u,                                                                  5u,  0x0055u,      0x02u, DEM_CFG_EREC_TYPE_USER   }   /* [#DidDemDidClass_StartApplication] */
};
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DataCollectionTableEdr2CollInd
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DataCollectionTableEdr2CollInd
  \brief  the indexes of the 1:1 sorted relation pointing to Dem_Cfg_DataCollectionTable
*/ 
#define DEM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_DataCollectionTableEdr2CollIndType, DEM_CONST) Dem_Cfg_DataCollectionTableEdr2CollInd[5] = {
  /* Index     DataCollectionTableEdr2CollInd      Referable Keys */
  /*     0 */                              4u,  /* [Ext:DemExtendedDataClass] */
  /*     1 */                              2u,  /* [Ext:DemExtendedDataClass] */
  /*     2 */                              5u,  /* [Ext:DemExtendedDataClass] */
  /*     3 */                              1u,  /* [Ext:DemExtendedDataClass] */
  /*     4 */                              3u   /* [Ext:DemExtendedDataClass] */
};
#define DEM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DataElementTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DataElementTable
  \details
  Element         Description
  ElementKind     DataElement kind, returned by Dem_Cfg_DataCallbackType()
  ElementSize     Size of data element in Byte.
  ReadDataFunc    C-function for getting the data. Its signature depends on ElementKind: With value(s) DEM_CFG_DATA_FROM_CBK_WITH_EVENTID use: Std_ReturnType (*)(uint8* Buffer, uint16 EventId); - and use: Std_ReturnType (*)(uint8* Buffer); with the other values DEM_CFG_DATA_FROM_CBK, DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN, DEM_CFG_DATA_FROM_SR_PORT_SINT16, DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL, DEM_CFG_DATA_FROM_SR_PORT_SINT32, DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL, DEM_CFG_DATA_FROM_SR_PORT_SINT8, DEM_CFG_DATA_FROM_SR_PORT_SINT8_N, DEM_CFG_DATA_FROM_SR_PORT_UINT16, DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL, DEM_CFG_DATA_FROM_SR_PORT_UINT32, DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL, DEM_CFG_DATA_FROM_SR_PORT_UINT8, DEM_CFG_DATA_FROM_SR_PORT_UINT8_N.
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_DataElementTableType, DEM_CONST) Dem_Cfg_DataElementTable[7] = {
    /* Index    ElementKind                  ElementSize  ReadDataFunc                                                                                                                         Referable Keys */
  { /*     0 */ DEM_CFG_DATAELEMENT_INVALID,          0u,  (Dem_ReadDataFPtrType) /* PRQA S 0313 */ /* MD_DEM_11.1 */ NULL_PTR                                                          },  /* [#NoDataElementConfigured] */
  { /*     1 */ DEM_CFG_DATA_FROM_CBK      ,          1u,  (Dem_ReadDataFPtrType) /* PRQA S 0313 */ /* MD_DEM_11.1 */ Rte_Call_CBReadData_OccurrenceCounter_OccurenceCounter_ReadData   },  /* [#OccurrenceCounter_OccurenceCounter, EdrOccurrenceCounter] */
  { /*     2 */ DEM_CFG_DATA_FROM_CBK      ,          3u,  (Dem_ReadDataFPtrType) /* PRQA S 0313 */ /* MD_DEM_11.1 */ Rte_Call_CBReadData_OdometerValue_OdometerValue_ReadData          },  /* [#OdometerValue_OdometerValue, EdrOdometerValue] */
  { /*     3 */ DEM_CFG_DATA_FROM_CBK      ,          2u,  (Dem_ReadDataFPtrType) /* PRQA S 0313 */ /* MD_DEM_11.1 */ Rte_Call_CBReadData_DemDataElementClass_StartApplication_ReadData },  /* [#DemDataElementClass_StartApplication, DidDemDidClass_StartApplication] */
  { /*     4 */ DEM_CFG_DATA_FROM_CBK      ,          6u,  (Dem_ReadDataFPtrType) /* PRQA S 0313 */ /* MD_DEM_11.1 */ Rte_Call_CBReadData_DemDataClass_Timestamp_ReadData               },  /* [#DemDataClass_Timestamp, EdrDemExtendedDataRecordClass_Timestamp] */
  { /*     5 */ DEM_CFG_DATA_FROM_CBK      ,          1u,  (Dem_ReadDataFPtrType) /* PRQA S 0313 */ /* MD_DEM_11.1 */ Rte_Call_CBReadData_DemDataClass_LV_Battary_Voltage_ReadData      },  /* [#DemDataClass_LV_Battary_Voltage, EdrDemExtendedDataRecordClass_LV_Battary_Voltage] */
  { /*     6 */ DEM_CFG_DATA_FROM_CBK      ,          2u,  (Dem_ReadDataFPtrType) /* PRQA S 0313 */ /* MD_DEM_11.1 */ Rte_Call_CBReadData_DemDataClass_Vehicle_Speed_ReadData           }   /* [#DemDataClass_Vehicle_Speed, EdrDemExtendedDataRecordClass_Vehicle_Speed] */
};
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DataElementTableCol2ElmtInd
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DataElementTableCol2ElmtInd
  \brief  the indexes of the 1:1 sorted relation pointing to Dem_Cfg_DataElementTable
*/ 
#define DEM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_DataElementTableCol2ElmtIndType, DEM_CONST) Dem_Cfg_DataElementTableCol2ElmtInd[6] = {
  /* Index     DataElementTableCol2ElmtInd      Referable Keys */
  /*     0 */                           5u,  /* [EdrDemExtendedDataRecordClass_LV_Battary_Voltage] */
  /*     1 */                           4u,  /* [EdrDemExtendedDataRecordClass_Timestamp] */
  /*     2 */                           6u,  /* [EdrDemExtendedDataRecordClass_Vehicle_Speed] */
  /*     3 */                           1u,  /* [EdrOccurrenceCounter] */
  /*     4 */                           2u,  /* [EdrOdometerValue] */
  /*     5 */                           3u   /* [DidDemDidClass_StartApplication] */
};
#define DEM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DebounceTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DebounceTable
  \details
  Element                   Description
  DecrementStepSize         (-1) * DemDebounceCounterDecrementStepSize of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased
  FailedThreshold           DemDebounceCounterFailedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased
  IncrementStepSize         DemDebounceCounterIncrementStepSize of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased
  PassedThreshold           DemDebounceCounterPassedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased
  EventDebounceAlgorithm    Used DemEventParameter/DemEventClass/DemDebounceAlgorithmClass
  MaskedBits                contains bitcoded the boolean data of Dem_Cfg_DebounceContinuousOfDebounceTable, Dem_Cfg_EventDebounceBehaviorOfDebounceTable, Dem_Cfg_JumpDownOfDebounceTable, Dem_Cfg_JumpUpOfDebounceTable, Dem_Cfg_StorageOfDebounceTable
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_DebounceTableType, DEM_CONST) Dem_Cfg_DebounceTable[2] = {
    /* Index    DecrementStepSize  FailedThreshold  IncrementStepSize  PassedThreshold  EventDebounceAlgorithm                                                      MaskedBits        Referable Keys */
  { /*     0 */                -1,             127,                 1,            -128, DEM_CFG_DEM_CFG_DEBOUNCETYPE_COUNTER_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE,      0x06u },  /* [A4814BDemEventParameter_003, A48249DemEventParameter_004, A48368DemEventParameter_005, A48468DemEventParameter_006, AutoCreatedDemEvent_ECUM_E_ALL_RUN_REQUESTS_KILLED, AutoCreatedDemEvent_ECUM_E_CONFIGURATION_DATA_INCONSISTENT, AutoCreatedDemEvent_ECUM_E_IMPROPER_CALLER, DEM_EVENT_StartApplication, E70200DemEventParameter, E70568DemEventParameter_007, E70600DemEventParameter_008, E70887DemEventParameter_009, E70987DemEventParameter_010, E70A87DemEventParameter_011, E70B29DemEventParameter_012, E70C29DemEventParameter_013, E70D29DemEventParameter_014, E70E87DemEventParameter_015, E70F87DemEventParameter_016, F00616DemEventParameter_001, F00617DemEventParameter_002] */
  { /*     1 */                 0,               0,                 0,               0, DEM_CFG_DEM_CFG_DEBOUNCETYPE_INVALID_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE,      0x00u }   /* [#EVENT_INVALID] */
};
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DtcTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DtcTable
  \details
  Element           Description
  UdsDtc        
  FunctionalUnit
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_DtcTableType, DEM_CONST) Dem_Cfg_DtcTable[19] = {
    /* Index    UdsDtc        FunctionalUnit        Referable Keys */
  { /*     0 */ 0x00FFFFFFuL,           255u },  /* [#NoUdsDtcConfigured, #NoObdDtcConfigured, #NoJ1939DtcConfigured] */
  { /*     1 */ 0x00E70200uL,             0u },  /* [DTCClass_DTC_0xE70200] */
  { /*     2 */ 0x00F00616uL,             0u },  /* [DTCClass_DTC_0xF00616] */
  { /*     3 */ 0x00F00617uL,             0u },  /* [DTCClass_DTC_0xF00617] */
  { /*     4 */ 0x00A4814BuL,             0u },  /* [DTCClass_DTC_0xA4814B] */
  { /*     5 */ 0x00A48249uL,             0u },  /* [DTCClass_DTC_0xA48249] */
  { /*     6 */ 0x00A48368uL,             0u },  /* [DTCClass_DTC_0xA48368] */
  { /*     7 */ 0x00A48468uL,             0u },  /* [DTCClass_DTC_0xA48468] */
  { /*     8 */ 0x00E70568uL,             0u },  /* [DTCClass_DTC_0xE70568] */
  { /*     9 */ 0x00E70600uL,             0u },  /* [DTCClass_DTC_0xE70600] */
  { /*    10 */ 0x00E70887uL,             0u },  /* [DTCClass_DTC_0xE70887] */
  { /*    11 */ 0x00E70987uL,             0u },  /* [DTCClass_DTC_0xE70987] */
  { /*    12 */ 0x00E70A87uL,             0u },  /* [DTCClass_DTC_0xE70A87] */
  { /*    13 */ 0x00E70B29uL,             0u },  /* [DTCClass_DTC_0xE70B29] */
  { /*    14 */ 0x00E70C29uL,             0u },  /* [DTCClass_DTC_0xE70C29] */
  { /*    15 */ 0x00E70D29uL,             0u },  /* [DTCClass_DTC_0xE70D29] */
  { /*    16 */ 0x00E70E87uL,             0u },  /* [DTCClass_DTC_0xE70E87] */
  { /*    17 */ 0x00E70F87uL,             0u },  /* [DTCClass_DTC_0xE70F87] */
  { /*    18 */ 0x00482BFFuL,             0u }   /* [DemDTCClass_StartApplication] */
};
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EventTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EventTable
  \details
  Element                 Description
  AgingCycleId            DemOperationCycle (ID) referenced by DemEventParameter/DemEventClass/DemAgingCycleRef
  DtcTableIdx             the index of the 1:1 relation pointing to Dem_Cfg_DtcTable
  ExtendedDataTableIdx    the index of the 1:1 relation pointing to Dem_Cfg_ExtendedDataTable
  OperationCycleId        DemOperationCycle (ID) referenced by DemEventParameter/DemEventClass/DemOperationCycleRef
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_EventTableType, DEM_CONST) Dem_Cfg_EventTable[22] = {
    /* Index    AgingCycleId                          DtcTableIdx  ExtendedDataTableIdx  OperationCycleId                               Referable Keys */
  { /*     0 */ DemConf_DemOperationCycle_PowerCycle,          1u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [#EVENT_INVALID, Satellite#0] */
  { /*     1 */ DemConf_DemOperationCycle_PowerCycle,          1u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [E70200DemEventParameter, Satellite#0] */
  { /*     2 */ DemConf_DemOperationCycle_PowerCycle,          2u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [F00616DemEventParameter_001, Satellite#0] */
  { /*     3 */ DemConf_DemOperationCycle_PowerCycle,          3u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [F00617DemEventParameter_002, Satellite#0] */
  { /*     4 */ DemConf_DemOperationCycle_PowerCycle,          4u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [A4814BDemEventParameter_003, Satellite#0] */
  { /*     5 */ DemConf_DemOperationCycle_PowerCycle,          5u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [A48249DemEventParameter_004, Satellite#0] */
  { /*     6 */ DemConf_DemOperationCycle_PowerCycle,          6u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [A48368DemEventParameter_005, Satellite#0] */
  { /*     7 */ DemConf_DemOperationCycle_PowerCycle,          7u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [A48468DemEventParameter_006, Satellite#0] */
  { /*     8 */ DemConf_DemOperationCycle_PowerCycle,          8u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [E70568DemEventParameter_007, Satellite#0] */
  { /*     9 */ DemConf_DemOperationCycle_PowerCycle,          9u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [E70600DemEventParameter_008, Satellite#0] */
  { /*    10 */ DemConf_DemOperationCycle_PowerCycle,         10u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [E70887DemEventParameter_009, Satellite#0] */
  { /*    11 */ DemConf_DemOperationCycle_PowerCycle,         11u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [E70987DemEventParameter_010, Satellite#0] */
  { /*    12 */ DemConf_DemOperationCycle_PowerCycle,         12u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [E70A87DemEventParameter_011, Satellite#0] */
  { /*    13 */ DemConf_DemOperationCycle_PowerCycle,         13u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [E70B29DemEventParameter_012, Satellite#0] */
  { /*    14 */ DemConf_DemOperationCycle_PowerCycle,         14u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [E70C29DemEventParameter_013, Satellite#0] */
  { /*    15 */ DemConf_DemOperationCycle_PowerCycle,         15u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [E70D29DemEventParameter_014, Satellite#0] */
  { /*    16 */ DemConf_DemOperationCycle_PowerCycle,         16u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [E70E87DemEventParameter_015, Satellite#0] */
  { /*    17 */ DemConf_DemOperationCycle_PowerCycle,         17u,                   1u, DemConf_DemOperationCycle_PowerCycle    },  /* [E70F87DemEventParameter_016, Satellite#0] */
  { /*    18 */ /*no AgingCycle*/ 4U                ,          0u,                   0u, DemConf_DemOperationCycle_IgnitionCycle },  /* [AutoCreatedDemEvent_ECUM_E_ALL_RUN_REQUESTS_KILLED, Satellite#0] */
  { /*    19 */ /*no AgingCycle*/ 4U                ,          0u,                   0u, DemConf_DemOperationCycle_IgnitionCycle },  /* [AutoCreatedDemEvent_ECUM_E_CONFIGURATION_DATA_INCONSISTENT, Satellite#0] */
  { /*    20 */ /*no AgingCycle*/ 4U                ,          0u,                   0u, DemConf_DemOperationCycle_IgnitionCycle },  /* [AutoCreatedDemEvent_ECUM_E_IMPROPER_CALLER, Satellite#0] */
  { /*    21 */ DemConf_DemOperationCycle_PowerCycle,         18u,                   1u, DemConf_DemOperationCycle_PowerCycle    }   /* [DEM_EVENT_StartApplication, Satellite#0] */
};
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_ExtendedDataTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_ExtendedDataTable
  \details
  Element                                   Description
  DataCollectionTableEdr2CollIndEndIdx      the end index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableEdr2CollInd
  DataCollectionTableEdr2CollIndStartIdx    the start index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableEdr2CollInd
  MaxRecordSize                         
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_ExtendedDataTableType, DEM_CONST) Dem_Cfg_ExtendedDataTable[2] = {
    /* Index    DataCollectionTableEdr2CollIndEndIdx                                DataCollectionTableEdr2CollIndStartIdx                                MaxRecordSize        Referable Keys */
  { /*     0 */ DEM_CFG_NO_DATACOLLECTIONTABLEEDR2COLLINDENDIDXOFEXTENDEDDATATABLE, DEM_CFG_NO_DATACOLLECTIONTABLEEDR2COLLINDSTARTIDXOFEXTENDEDDATATABLE,            0u },  /* [#NoExtendedDataRecordConfigured, AutoCreatedDemEvent_ECUM_E_ALL_RUN_REQUESTS_KILLED, AutoCreatedDemEvent_ECUM_E_CONFIGURATION_DATA_INCONSISTENT, AutoCreatedDemEvent_ECUM_E_IMPROPER_CALLER] */
  { /*     1 */                                                                 5u,                                                                   0u,            6u }   /* [#DemExtendedDataClass, #EVENT_INVALID, E70200DemEventParameter, F00616DemEventParameter_001, F00617DemEventParameter_002, A4814BDemEventParameter_003, A48249DemEventParameter_004, A48368DemEventParameter_005, A48468DemEventParameter_006, E70568DemEventParameter_007, E70600DemEventParameter_008, E70887DemEventParameter_009, E70987DemEventParameter_010, E70A87DemEventParameter_011, E70B29DemEventParameter_012, E70C29DemEventParameter_013, E70D29DemEventParameter_014, E70E87DemEventParameter_015, E70F87DemEventParameter_016, DEM_EVENT_StartApplication] */
};
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryBlockIdToMemoryEntryId
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryBlockIdToMemoryEntryId
  \brief  The array contains these items: Admin, Status, 18 * Primary
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_MemoryEntry_HandleType, DEM_CONST) Dem_Cfg_MemoryBlockIdToMemoryEntryId[20] = {
  /* Index     MemoryBlockIdToMemoryEntryId        Comment */
  /*     0 */ DEM_MEMORYENTRY_HANDLE_INVALID ,  /* [DemAdminDataBlock] */
  /*     1 */ DEM_MEMORYENTRY_HANDLE_INVALID ,  /* [Dem_StatusData] */
  /*     2 */ 0u                             ,  /* [DemNvRamBlockId_001] */
  /*     3 */ 1u                             ,  /* [DemNvRamBlockId_002] */
  /*     4 */ 2u                             ,  /* [DemNvRamBlockId_003] */
  /*     5 */ 3u                             ,  /* [DemNvRamBlockId_004] */
  /*     6 */ 4u                             ,  /* [DemNvRamBlockId_005] */
  /*     7 */ 5u                             ,  /* [DemNvRamBlockId_006] */
  /*     8 */ 6u                             ,  /* [DemNvRamBlockId_007] */
  /*     9 */ 7u                             ,  /* [DemNvRamBlockId_008] */
  /*    10 */ 8u                             ,  /* [DemNvRamBlockId_009] */
  /*    11 */ 9u                             ,  /* [DemNvRamBlockId_010] */
  /*    12 */ 10u                            ,  /* [DemNvRamBlockId_011] */
  /*    13 */ 11u                            ,  /* [DemNvRamBlockId_012] */
  /*    14 */ 12u                            ,  /* [DemNvRamBlockId_013] */
  /*    15 */ 13u                            ,  /* [DemNvRamBlockId_014] */
  /*    16 */ 14u                            ,  /* [DemNvRamBlockId_015] */
  /*    17 */ 15u                            ,  /* [DemNvRamBlockId_016] */
  /*    18 */ 16u                            ,  /* [DemNvRamBlockId_017] */
  /*    19 */ 17u                               /* [DemNvRamBlockId_018] */
};
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryDataPtr
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryDataPtr
  \brief  The array contains these items: Admin, Status, 18 * Primary
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_NvDataPtrType, DEM_CONST) Dem_Cfg_MemoryDataPtr[20] = {
  /* Index     MemoryDataPtr                                                                                   Comment */
  /*     0 */ (Dem_NvDataPtrType) &Dem_Cfg_GetAdminData()         /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemAdminDataBlock] */
  /*     1 */ (Dem_NvDataPtrType) &Dem_Cfg_GetStatusData()        /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [Dem_StatusData] */
  /*     2 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_0()    /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_001] */
  /*     3 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_1()    /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_002] */
  /*     4 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_2()    /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_003] */
  /*     5 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_3()    /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_004] */
  /*     6 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_4()    /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_005] */
  /*     7 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_5()    /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_006] */
  /*     8 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_6()    /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_007] */
  /*     9 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_7()    /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_008] */
  /*    10 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_8()    /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_009] */
  /*    11 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_9()    /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_010] */
  /*    12 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_10()   /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_011] */
  /*    13 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_11()   /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_012] */
  /*    14 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_12()   /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_013] */
  /*    15 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_13()   /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_014] */
  /*    16 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_14()   /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_015] */
  /*    17 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_15()   /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_016] */
  /*    18 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_16()   /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_017] */
  /*    19 */ (Dem_NvDataPtrType) &Dem_Cfg_GetPrimaryEntry_17()   /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */   /* [DemNvRamBlockId_018] */
};
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryDataSize
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryDataSize
  \brief  The array contains these items: Admin, Status, 18 * Primary
*/ 
#define DEM_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_MemoryDataSizeType, DEM_CONST) Dem_Cfg_MemoryDataSize[20] = {
  /* Index     MemoryDataSize                                                         Comment */
  /*     0 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetAdminData())       ,  /* [DemAdminDataBlock] */
  /*     1 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetStatusData())      ,  /* [Dem_StatusData] */
  /*     2 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_0())  ,  /* [DemNvRamBlockId_001] */
  /*     3 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_1())  ,  /* [DemNvRamBlockId_002] */
  /*     4 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_2())  ,  /* [DemNvRamBlockId_003] */
  /*     5 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_3())  ,  /* [DemNvRamBlockId_004] */
  /*     6 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_4())  ,  /* [DemNvRamBlockId_005] */
  /*     7 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_5())  ,  /* [DemNvRamBlockId_006] */
  /*     8 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_6())  ,  /* [DemNvRamBlockId_007] */
  /*     9 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_7())  ,  /* [DemNvRamBlockId_008] */
  /*    10 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_8())  ,  /* [DemNvRamBlockId_009] */
  /*    11 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_9())  ,  /* [DemNvRamBlockId_010] */
  /*    12 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_10()) ,  /* [DemNvRamBlockId_011] */
  /*    13 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_11()) ,  /* [DemNvRamBlockId_012] */
  /*    14 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_12()) ,  /* [DemNvRamBlockId_013] */
  /*    15 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_13()) ,  /* [DemNvRamBlockId_014] */
  /*    16 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_14()) ,  /* [DemNvRamBlockId_015] */
  /*    17 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_15()) ,  /* [DemNvRamBlockId_016] */
  /*    18 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_16()) ,  /* [DemNvRamBlockId_017] */
  /*    19 */ (Dem_Cfg_MemoryDataSizeType) sizeof(Dem_Cfg_GetPrimaryEntry_17())    /* [DemNvRamBlockId_018] */
};
#define DEM_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryEntry
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryEntry
  \brief  The array contains these items: 18 * Primary, ReadoutBuffer; size = DEM_CFG_GLOBAL_PRIMARY_SIZE + DEM_CFG_GLOBAL_SECONDARY_SIZE + DEM_CFG_NUMBER_OF_READOUTBUFFERS
*/ 
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_SharedMemoryEntryPtrType, DEM_CONST) Dem_Cfg_MemoryEntry[19] = {
  /* Index     MemoryEntry                                                                     Comment */
  /*     0 */ &Dem_Cfg_GetPrimaryEntry_0()        /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_001] */
  /*     1 */ &Dem_Cfg_GetPrimaryEntry_1()        /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_002] */
  /*     2 */ &Dem_Cfg_GetPrimaryEntry_2()        /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_003] */
  /*     3 */ &Dem_Cfg_GetPrimaryEntry_3()        /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_004] */
  /*     4 */ &Dem_Cfg_GetPrimaryEntry_4()        /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_005] */
  /*     5 */ &Dem_Cfg_GetPrimaryEntry_5()        /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_006] */
  /*     6 */ &Dem_Cfg_GetPrimaryEntry_6()        /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_007] */
  /*     7 */ &Dem_Cfg_GetPrimaryEntry_7()        /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_008] */
  /*     8 */ &Dem_Cfg_GetPrimaryEntry_8()        /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_009] */
  /*     9 */ &Dem_Cfg_GetPrimaryEntry_9()        /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_010] */
  /*    10 */ &Dem_Cfg_GetPrimaryEntry_10()       /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_011] */
  /*    11 */ &Dem_Cfg_GetPrimaryEntry_11()       /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_012] */
  /*    12 */ &Dem_Cfg_GetPrimaryEntry_12()       /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_013] */
  /*    13 */ &Dem_Cfg_GetPrimaryEntry_13()       /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_014] */
  /*    14 */ &Dem_Cfg_GetPrimaryEntry_14()       /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_015] */
  /*    15 */ &Dem_Cfg_GetPrimaryEntry_15()       /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_016] */
  /*    16 */ &Dem_Cfg_GetPrimaryEntry_16()       /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_017] */
  /*    17 */ &Dem_Cfg_GetPrimaryEntry_17()       /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */,  /* [DemNvRamBlockId_018] */
  /*    18 */ &Dem_Cfg_GetReadoutBuffer(0).Data   /* PRQA S 0310 */ /* MD_DEM_11.4_nvm */   /* [Dem_Cfg_ReadoutBuffer[0].Data] */
};
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryEntryInit
**********************************************************************************************************************/
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_PrimaryEntryType, DEM_CONST) Dem_Cfg_MemoryEntryInit = { 0 };
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_TimeSeriesEntryInit
**********************************************************************************************************************/
#define DEM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Dem_Cfg_TimeSeriesEntryType, DEM_CONST) Dem_Cfg_TimeSeriesEntryInit = { 0 };
#define DEM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_AdminData
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_AdminDataType, DEM_NVM_DATA_NOINIT) Dem_Cfg_AdminData;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_ClearDTCTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_ClearDTCTable
  \brief  size = DEM_CFG_NUMBER_OF_CLEARDTCS
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_ClearDTC_DataType, DEM_VAR_NOINIT) Dem_Cfg_ClearDTCTable[1];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_CommitBuffer
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_CommitBufferType, DEM_VAR_NOINIT) Dem_Cfg_CommitBuffer;  /* PRQA S 0759 */ /* MD_MSR_18.4 */
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_DTCSelectorTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_DTCSelectorTable
  \brief  size = DEM_CFG_NUMBER_OF_DTCSELECTORS
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_DTCSelector_DataType, DEM_VAR_NOINIT) Dem_Cfg_DTCSelectorTable[1];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EnableConditionGroupCounter
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EnableConditionGroupCounter
  \brief  (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) or there are internal EnableConditions. Table index: Condition group number. Table value: count of conditions in state 'enable'.
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_EnableConditionGroupCounterType, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionGroupCounter[1];
  /* Index        Referable Keys  */
  /*     0 */  /* [##NoEnableConditionGroupConfigured, __Internal_ControlDtcSetting] */

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EnableConditionGroupState
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EnableConditionGroupState
  \brief  (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) or there are internal EnableConditions. Table index: Condition group number. Table value: count of conditions in state 'enable'.
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
volatile VAR(Dem_Cfg_EnableConditionGroupStateType, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionGroupState[1];
  /* Index        Referable Keys  */
  /*     0 */  /* [##NoEnableConditionGroupConfigured, __Internal_ControlDtcSetting] */

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EnableConditionState
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EnableConditionState
  \brief  (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) or there are internal EnableConditions. Table index: Condition ID. Table value: current condition state '0' disable, '1' enable.
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_EnableConditionStateType, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionState[1];
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EventDebounceValue
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EventDebounceValue
  \brief  size = DEM_G_NUMBER_OF_EVENTS
*/ 
#define DEM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
volatile VAR(Dem_Cfg_EventDebounceValueType, DEM_VAR_NOINIT) Dem_Cfg_EventDebounceValue[22];
  /* Index        Referable Keys  */
  /*     0 */  /* [#EVENT_INVALID, Satellite#0] */
  /*     1 */  /* [E70200DemEventParameter, Satellite#0] */
  /*     2 */  /* [F00616DemEventParameter_001, Satellite#0] */
  /*     3 */  /* [F00617DemEventParameter_002, Satellite#0] */
  /*     4 */  /* [A4814BDemEventParameter_003, Satellite#0] */
  /*     5 */  /* [A48249DemEventParameter_004, Satellite#0] */
  /*     6 */  /* [A48368DemEventParameter_005, Satellite#0] */
  /*     7 */  /* [A48468DemEventParameter_006, Satellite#0] */
  /*     8 */  /* [E70568DemEventParameter_007, Satellite#0] */
  /*     9 */  /* [E70600DemEventParameter_008, Satellite#0] */
  /*    10 */  /* [E70887DemEventParameter_009, Satellite#0] */
  /*    11 */  /* [E70987DemEventParameter_010, Satellite#0] */
  /*    12 */  /* [E70A87DemEventParameter_011, Satellite#0] */
  /*    13 */  /* [E70B29DemEventParameter_012, Satellite#0] */
  /*    14 */  /* [E70C29DemEventParameter_013, Satellite#0] */
  /*    15 */  /* [E70D29DemEventParameter_014, Satellite#0] */
  /*    16 */  /* [E70E87DemEventParameter_015, Satellite#0] */
  /*    17 */  /* [E70F87DemEventParameter_016, Satellite#0] */
  /*    18 */  /* [AutoCreatedDemEvent_ECUM_E_ALL_RUN_REQUESTS_KILLED, Satellite#0] */
  /*    19 */  /* [AutoCreatedDemEvent_ECUM_E_CONFIGURATION_DATA_INCONSISTENT, Satellite#0] */
  /*    20 */  /* [AutoCreatedDemEvent_ECUM_E_IMPROPER_CALLER, Satellite#0] */
  /*    21 */  /* [DEM_EVENT_StartApplication, Satellite#0] */

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_EventInternalStatus
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_EventInternalStatus
  \brief  size = DEM_G_NUMBER_OF_EVENTS
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
volatile VAR(Dem_Event_InternalStatusType, DEM_VAR_NOINIT) Dem_Cfg_EventInternalStatus[22];
  /* Index        Referable Keys  */
  /*     0 */  /* [#EVENT_INVALID, Satellite#0] */
  /*     1 */  /* [E70200DemEventParameter, Satellite#0] */
  /*     2 */  /* [F00616DemEventParameter_001, Satellite#0] */
  /*     3 */  /* [F00617DemEventParameter_002, Satellite#0] */
  /*     4 */  /* [A4814BDemEventParameter_003, Satellite#0] */
  /*     5 */  /* [A48249DemEventParameter_004, Satellite#0] */
  /*     6 */  /* [A48368DemEventParameter_005, Satellite#0] */
  /*     7 */  /* [A48468DemEventParameter_006, Satellite#0] */
  /*     8 */  /* [E70568DemEventParameter_007, Satellite#0] */
  /*     9 */  /* [E70600DemEventParameter_008, Satellite#0] */
  /*    10 */  /* [E70887DemEventParameter_009, Satellite#0] */
  /*    11 */  /* [E70987DemEventParameter_010, Satellite#0] */
  /*    12 */  /* [E70A87DemEventParameter_011, Satellite#0] */
  /*    13 */  /* [E70B29DemEventParameter_012, Satellite#0] */
  /*    14 */  /* [E70C29DemEventParameter_013, Satellite#0] */
  /*    15 */  /* [E70D29DemEventParameter_014, Satellite#0] */
  /*    16 */  /* [E70E87DemEventParameter_015, Satellite#0] */
  /*    17 */  /* [E70F87DemEventParameter_016, Satellite#0] */
  /*    18 */  /* [AutoCreatedDemEvent_ECUM_E_ALL_RUN_REQUESTS_KILLED, Satellite#0] */
  /*    19 */  /* [AutoCreatedDemEvent_ECUM_E_CONFIGURATION_DATA_INCONSISTENT, Satellite#0] */
  /*    20 */  /* [AutoCreatedDemEvent_ECUM_E_IMPROPER_CALLER, Satellite#0] */
  /*    21 */  /* [DEM_EVENT_StartApplication, Satellite#0] */

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_FilterInfoTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_FilterInfoTable
  \brief  size = DEM_CFG_NUMBER_OF_FILTER
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_FilterData_InfoType, DEM_VAR_NOINIT) Dem_Cfg_FilterInfoTable[1];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_FilterReportedEvents
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_FilterReportedEvents
  \brief  size = ceiling( DEM_G_NUMBER_OF_EVENTS / 8 )
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_FilterReportedEventsType, DEM_VAR_NOINIT) Dem_Cfg_FilterReportedEvents[3];
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_FreezeFrameIteratorTable
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_FreezeFrameIteratorTable
  \brief  size = DEM_CFG_NUMBER_OF_FREEZEFRAMEITERATORS
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_FreezeFrameIterator_FilterType, DEM_VAR_NOINIT) Dem_Cfg_FreezeFrameIteratorTable[1];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryCommitNumber
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryCommitNumber
  \brief  The array contains these items: Admin, Status, 18 * Primary
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
volatile VAR(Dem_Cfg_MemoryCommitNumberType, DEM_VAR_NOINIT) Dem_Cfg_MemoryCommitNumber[20];
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_MemoryStatus
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_MemoryStatus
  \brief  The array contains these items: Admin, Status, 18 * Primary
*/ 
#define DEM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_MemoryStatusType, DEM_VAR_NOINIT) Dem_Cfg_MemoryStatus[20];
#define DEM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryChronology
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_PrimaryChronology
  \brief  size = DEM_CFG_GLOBAL_PRIMARY_SIZE
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_MemoryIndexType, DEM_VAR_NOINIT) Dem_Cfg_PrimaryChronology[18];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_0
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_0;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_1
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_1;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_10
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_10;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_11
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_11;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_12
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_12;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_13
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_13;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_14
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_14;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_15
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_15;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_16
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_16;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_17
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_17;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_2
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_2;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_3
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_3;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_4
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_4;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_5
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_5;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_6
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_6;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_7
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_7;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_8
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_8;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_PrimaryEntry_9
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_9;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_ReadoutBuffer
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_ReadoutBufferEntryType, DEM_VAR_NOINIT) Dem_Cfg_ReadoutBuffer[1];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_ReportedEventsOfFilter
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_ReportedEventsOfFilter
  \brief  size = DEM_CFG_NUMBER_OF_FILTER
*/ 
#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_ReportedEventsType, DEM_VAR_NOINIT) Dem_Cfg_ReportedEventsOfFilter[1];
#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_SatelliteInfo0
**********************************************************************************************************************/
/** 
  \var    Dem_Cfg_SatelliteInfo0
  \brief  Buffer for satellite data on OsApplication "0"
*/ 
#define DEM_START_SEC_0_VAR_ZERO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_SatelliteInfoType0, DEM_VAR_ZERO_INIT) Dem_Cfg_SatelliteInfo0 = {0uL};
#define DEM_STOP_SEC_0_VAR_ZERO_INIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Dem_Cfg_StatusData
**********************************************************************************************************************/
#define DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Dem_Cfg_StatusDataType, DEM_NVM_DATA_NOINIT) Dem_Cfg_StatusData;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/



/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/



/**********************************************************************************************************************
  END OF FILE: Dem_Lcfg.c     [Vag (Vector), VARIANT-PRE-COMPILE, 16.06.00.107213]
**********************************************************************************************************************/

