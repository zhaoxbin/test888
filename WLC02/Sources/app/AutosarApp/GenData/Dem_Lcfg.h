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
 *              File: Dem_Lcfg.h
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
#if !defined (DEM_LCFG_H)
# define DEM_LCFG_H

/**********************************************************************************************************************
  MISRA JUSTIFICATIONS
**********************************************************************************************************************/

/* PRQA S 0777 EOF */ /* MD_DEM_5.1 */                                          /* External identifier does not differ in 32 significant characters */
/* PRQA S 0779 EOF */ /* MD_DEM_5.1 */                                          /* Identifier does not differ in 32 significant characters */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */                                      /* Number of macro definitions exceeds 1024 - program is non-conforming -- caused by #include'd files. */


/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Dem_SatelliteData_Types.h"
#include "Dem_DTCSelector_Types.h"
#include "Dem_FilterData_Types.h"
#include "Dem_FreezeFrameIterator_Types.h"
#include "Dem_ClearDTC_Types.h"
#include "Dem_Event_Types.h"
#include "Dem_DTCReadoutBuffer_Types.h"
#include "Dem_MemoryEntry_Types.h"

#include "Os.h"                                                                           /* get: ApplicationType    */

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  Dem_CfgPCDataSwitches  Dem_Cfg Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define DEM_CFG_ADMINDATA                                             STD_ON
#define DEM_CFG_AGINGDATA                                             STD_OFF  /**< Deactivateable: 'Dem_Cfg_AgingData' Reason: 'DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS==STD_OFF && DEM_CFG_DATA_AGED_COUNTER==STD_OFF' */
#define DEM_CFG_CALLBACKCLEAREVENTALLOWED                             STD_OFF  /**< Deactivateable: 'Dem_Cfg_CallbackClearEventAllowed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_CALLBACKDTCSTATUSCHANGED                              STD_OFF  /**< Deactivateable: 'Dem_Cfg_CallbackDtcStatusChanged' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_CALLBACKGETFDC                                        STD_OFF  /**< Deactivateable: 'Dem_Cfg_CallbackGetFdc' Reason: '(DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL == STD_OFF)' */
#define DEM_CFG_CALLBACKJ1939DTCSTATUSCHANGED                         STD_OFF  /**< Deactivateable: 'Dem_Cfg_CallbackJ1939DtcStatusChanged' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_CLEARDTCTABLE                                         STD_ON
#define DEM_CFG_CLEARDTCNOTIFICATIONFINISHTABLE                       STD_OFF  /**< Deactivateable: 'Dem_Cfg_ClearDtcNotificationFinishTable' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_CLEARDTCNOTIFICATIONSTARTTABLE                        STD_OFF  /**< Deactivateable: 'Dem_Cfg_ClearDtcNotificationStartTable' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_CLIENTTABLE                                           STD_ON
#define DEM_CFG_CLEARDTCINDEXOFCLIENTTABLE                            STD_ON
#define DEM_CFG_FILTERINDEXOFCLIENTTABLE                              STD_ON
#define DEM_CFG_FREEZEFRAMEITERATORINDEXOFCLIENTTABLE                 STD_ON
#define DEM_CFG_NMNODEIDOFCLIENTTABLE                                 STD_OFF  /**< Deactivateable: 'Dem_Cfg_ClientTable.NmNodeId' Reason: '(DEM_CFG_SUPPORT_J1939 == STD_OFF)' */
#define DEM_CFG_READOUTBUFFERINDEXOFCLIENTTABLE                       STD_ON
#define DEM_CFG_SELECTORINDEXOFCLIENTTABLE                            STD_ON
#define DEM_CFG_COMMITBUFFER                                          STD_ON
#define DEM_CFG_CONFIGURATIONID                                       STD_ON
#define DEM_CFG_CYCLEIDTABLE                                          STD_ON
#define DEM_CFG_ENDSONINITOFCYCLEIDTABLE                              STD_OFF  /**< Deactivateable: 'Dem_Cfg_CycleIdTable.EndsOnInit' Reason: 'no DemOperationCycle/DemOperationCycleAutomaticEnd defined or all defined parameters are 'false'' */
#define DEM_CFG_OPCYCLETYPEOFCYCLEIDTABLE                             STD_ON
#define DEM_CFG_USEDFORAGINGOFCYCLEIDTABLE                            STD_ON
#define DEM_CFG_DTCSELECTORTABLE                                      STD_ON
#define DEM_CFG_DATACOLLECTIONTABLE                                   STD_ON
#define DEM_CFG_COLLECTIONSIZEOFDATACOLLECTIONTABLE                   STD_ON
#define DEM_CFG_DATAELEMENTTABLECOL2ELMTINDENDIDXOFDATACOLLECTIONTABLE STD_ON
#define DEM_CFG_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE STD_ON
#define DEM_CFG_DATAELEMENTTABLECOL2ELMTINDUSEDOFDATACOLLECTIONTABLE  STD_ON
#define DEM_CFG_DIDOFFSETFASTOFDATACOLLECTIONTABLE                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_DataCollectionTable.DidOffsetFast' Reason: '(DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_OFF) && (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_OFF)' */
#define DEM_CFG_DIDOFFSETNORMALOFDATACOLLECTIONTABLE                  STD_OFF  /**< Deactivateable: 'Dem_Cfg_DataCollectionTable.DidOffsetNormal' Reason: '(DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_OFF) && (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_OFF)' */
#define DEM_CFG_IDNUMBEROFDATACOLLECTIONTABLE                         STD_ON
#define DEM_CFG_MASKEDBITSOFDATACOLLECTIONTABLE                       STD_ON
#define DEM_CFG_STORAGEKINDOFDATACOLLECTIONTABLE                      STD_ON
#define DEM_CFG_UPDATEOFDATACOLLECTIONTABLE                           STD_ON
#define DEM_CFG_DATACOLLECTIONTABLEEDR2COLLIND                        STD_ON
#define DEM_CFG_DATACOLLECTIONTABLEFFM2COLLIND                        STD_OFF  /**< Deactivateable: 'Dem_Cfg_DataCollectionTableFfm2CollInd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_DATACOLLECTIONTABLEJ19392COLLIND                      STD_OFF  /**< Deactivateable: 'Dem_Cfg_DataCollectionTableJ19392CollInd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_DATACOLLECTIONTABLEPID2COLLIND                        STD_OFF  /**< Deactivateable: 'Dem_Cfg_DataCollectionTablePid2CollInd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_DATAELEMENTTABLE                                      STD_ON
#define DEM_CFG_DATAISSTOREDINNVOFDATAELEMENTTABLE                    STD_ON
#define DEM_CFG_ELEMENTKINDOFDATAELEMENTTABLE                         STD_ON
#define DEM_CFG_ELEMENTSIZEOFDATAELEMENTTABLE                         STD_ON
#define DEM_CFG_READDATAFUNCOFDATAELEMENTTABLE                        STD_ON
#define DEM_CFG_DATAELEMENTTABLECOL2ELMTIND                           STD_ON
#define DEM_CFG_DEBOUNCEDATA                                          STD_OFF  /**< Deactivateable: 'Dem_Cfg_DebounceData' Reason: 'DEM_CFG_SUPPORT_DEBOUNCE_NV==STD_OFF' */
#define DEM_CFG_DEBOUNCEHIRESTABLE                                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_DebounceHiResTable' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_DEBOUNCELORESTABLE                                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_DebounceLoResTable' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_DEBOUNCETABLE                                         STD_ON
#define DEM_CFG_DEBOUNCECONTINUOUSOFDEBOUNCETABLE                     STD_ON
#define DEM_CFG_DECREMENTSTEPSIZEOFDEBOUNCETABLE                      STD_ON
#define DEM_CFG_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE                 STD_ON
#define DEM_CFG_EVENTDEBOUNCEBEHAVIOROFDEBOUNCETABLE                  STD_ON
#define DEM_CFG_FAILTIMERCYCLESOFDEBOUNCETABLE                        STD_ON
#define DEM_CFG_FAILEDTHRESHOLDOFDEBOUNCETABLE                        STD_ON
#define DEM_CFG_INCREMENTSTEPSIZEOFDEBOUNCETABLE                      STD_ON
#define DEM_CFG_JUMPDOWNOFDEBOUNCETABLE                               STD_ON
#define DEM_CFG_JUMPDOWNVALUEOFDEBOUNCETABLE                          STD_ON
#define DEM_CFG_JUMPUPOFDEBOUNCETABLE                                 STD_ON
#define DEM_CFG_JUMPUPVALUEOFDEBOUNCETABLE                            STD_ON
#define DEM_CFG_MASKEDBITSOFDEBOUNCETABLE                             STD_ON
#define DEM_CFG_PASSTIMERCYCLESOFDEBOUNCETABLE                        STD_ON
#define DEM_CFG_PASSEDTHRESHOLDOFDEBOUNCETABLE                        STD_ON
#define DEM_CFG_PRECONFIRMEDTHRESHOLDOFDEBOUNCETABLE                  STD_OFF  /**< Deactivateable: 'Dem_Cfg_DebounceTable.PreconfirmedThreshold' Reason: 'DemDebounceCounterPreconfirmedThreshold is not required' */
#define DEM_CFG_STORAGEOFDEBOUNCETABLE                                STD_ON
#define DEM_CFG_STORAGETHRESHOLDOFDEBOUNCETABLE                       STD_OFF  /**< Deactivateable: 'Dem_Cfg_DebounceTable.StorageThreshold' Reason: 'DemEventDebounceCounterStorageThreshold is not required. (due Parameter DemGeneral/DemTypeOfFreezeFrameRecordNumeration != DEM_FF_RECNUM_CONFIGURED)' */
#define DEM_CFG_STORAGETIMERCYCLESOFDEBOUNCETABLE                     STD_OFF  /**< Deactivateable: 'Dem_Cfg_DebounceTable.StorageTimerCycles' Reason: 'DemDebounceTimeStorageThreshold is not required.  (due Parameter DemGeneral/DemTypeOfFreezeFrameRecordNumeration != DEM_FF_RECNUM_CONFIGURED)' */
#define DEM_CFG_DTCGROUPMASK                                          STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtcGroupMask' Reason: 'No configured DemGroupOfDTC containers.' */
#define DEM_CFG_GROUPMASKOFDTCGROUPMASK                               STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtcGroupMask.GroupMask' Reason: 'No configured DemGroupOfDTC containers.' */
#define DEM_CFG_UDSGROUPDTCOFDTCGROUPMASK                             STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtcGroupMask.UdsGroupDtc' Reason: 'No configured DemGroupOfDTC containers.' */
#define DEM_CFG_DTCTABLE                                              STD_ON
#define DEM_CFG_DTCSEVERITYOFDTCTABLE                                 STD_ON
#define DEM_CFG_FUNCTIONALUNITOFDTCTABLE                              STD_ON
#define DEM_CFG_IMMEDIATENVSTORAGEOFDTCTABLE                          STD_ON
#define DEM_CFG_J1939DTCOFDTCTABLE                                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtcTable.J1939Dtc' Reason: '(DEM_CFG_SUPPORT_J1939 == STD_OFF)' */
#define DEM_CFG_J1939NODEIDINDENDIDXOFDTCTABLE                        STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtcTable.J1939NodeIdIndEndIdx' Reason: '(DEM_CFG_HAS_J1939_NODE == STD_OFF)' */
#define DEM_CFG_J1939NODEIDINDSTARTIDXOFDTCTABLE                      STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtcTable.J1939NodeIdIndStartIdx' Reason: '(DEM_CFG_HAS_J1939_NODE == STD_OFF)' */
#define DEM_CFG_J1939NODEIDINDUSEDOFDTCTABLE                          STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtcTable.J1939NodeIdIndUsed' Reason: '(DEM_CFG_HAS_J1939_NODE == STD_OFF)' */
#define DEM_CFG_OBDDTCOFDTCTABLE                                      STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtcTable.ObdDtc' Reason: '(DEM_CFG_SUPPORT_OBDII == STD_OFF)' */
#define DEM_CFG_UDSDTCOFDTCTABLE                                      STD_ON
#define DEM_CFG_DTRDATA                                               STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtrData' Reason: '(((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF))) || (DEM_CFG_SUPPORT_DTR==STD_OFF)' */
#define DEM_CFG_DTRSTATUS                                             STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtrStatus' Reason: '(DEM_CFG_SUPPORT_DTR==STD_OFF) || (((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)))' */
#define DEM_CFG_DTRTABLE                                              STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtrTable' Reason: 'No Dtr support.' */
#define DEM_CFG_DIVISOROFDTRTABLE                                     STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtrTable.Divisor' Reason: 'No Dtr support.' */
#define DEM_CFG_EVENTTABLEIDXOFDTRTABLE                               STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtrTable.EventTableIdx' Reason: 'No Dtr support.' */
#define DEM_CFG_LINEARFACTOROFDTRTABLE                                STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtrTable.LinearFactor' Reason: 'No Dtr support.' */
#define DEM_CFG_OFFSETOFDTRTABLE                                      STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtrTable.Offset' Reason: 'No Dtr support.' */
#define DEM_CFG_UASIDOFDTRTABLE                                       STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtrTable.Uasid' Reason: 'No Dtr support.' */
#define DEM_CFG_UPDATEKINDOFDTRTABLE                                  STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtrTable.UpdateKind' Reason: 'No Dtr support.' */
#define DEM_CFG_DTRTABLEIND                                           STD_OFF  /**< Deactivateable: 'Dem_Cfg_DtrTableInd' Reason: 'No Dtr support.' */
#define DEM_CFG_ENABLECONDITIONGROUPCOUNTER                           STD_ON
#define DEM_CFG_ENABLECONDITIONGROUPSTATE                             STD_ON
#define DEM_CFG_ENABLECONDITIONGROUPTABLE                             STD_ON
#define DEM_CFG_INDEXOFENABLECONDITIONGROUPTABLE                      STD_ON
#define DEM_CFG_ENABLECONDITIONGROUPTABLEIND                          STD_ON
#define DEM_CFG_ENABLECONDITIONINITTABLE                              STD_ON
#define DEM_CFG_INITVALUEOFENABLECONDITIONINITTABLE                   STD_ON
#define DEM_CFG_ENABLECONDITIONSTATE                                  STD_ON
#define DEM_CFG_ENABLECONDITIONTABLE                                  STD_ON
#define DEM_CFG_ENABLECONDITIONGROUPTABLEINDENDIDXOFENABLECONDITIONTABLE STD_ON
#define DEM_CFG_ENABLECONDITIONGROUPTABLEINDSTARTIDXOFENABLECONDITIONTABLE STD_ON
#define DEM_CFG_ENABLECONDITIONGROUPTABLEINDUSEDOFENABLECONDITIONTABLE STD_ON
#define DEM_CFG_EVENTAVAILABLEDATA                                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventAvailableData' Reason: 'DEM_CFG_SUPPORT_EVENTAVAILABLE_NV==STD_OFF' */
#define DEM_CFG_EVENTAVAILABLEDEFAULT                                 STD_ON
#define DEM_CFG_EVENTAVAILABLEINVARIANT                               STD_ON
#define DEM_CFG_EVENTCYCLESTATUS                                      STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventCycleStatus' Reason: '(((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF))) || (DEM_CFG_PROCESS_CDTC_STOREDONLY==STD_OFF)' */
#define DEM_CFG_EVENTDATACHANGED                                      STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventDataChanged' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_EVENTDEBOUNCEVALUE                                    STD_ON
#define DEM_CFG_EVENTINTERNALSTATUS                                   STD_ON
#define DEM_CFG_EVENTSTATUSCHANGED                                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventStatusChanged' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_EVENTTABLE                                            STD_ON
#define DEM_CFG_AGINGALLOWEDOFEVENTTABLE                              STD_ON
#define DEM_CFG_AGINGCYCLECOUNTERTHRESHOLDOFEVENTTABLE                STD_ON
#define DEM_CFG_AGINGCYCLEIDOFEVENTTABLE                              STD_ON
#define DEM_CFG_CALLBACKCLEAREVENTALLOWEDIDXOFEVENTTABLE              STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.CallbackClearEventAllowedIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_CALLBACKCLEAREVENTALLOWEDUSEDOFEVENTTABLE             STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.CallbackClearEventAllowedUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_CALLBACKGETFDCIDXOFEVENTTABLE                         STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.CallbackGetFdcIdx' Reason: '(DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL == STD_OFF)' */
#define DEM_CFG_DEBOUNCETABLEIDXOFEVENTTABLE                          STD_ON
#define DEM_CFG_DTCTABLEIDXOFEVENTTABLE                               STD_ON
#define DEM_CFG_DTRTABLEINDENDIDXOFEVENTTABLE                         STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.DtrTableIndEndIdx' Reason: 'the optional indirection is deactivated because DtrTableIndUsedOfEventTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_DTRTABLEINDSTARTIDXOFEVENTTABLE                       STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.DtrTableIndStartIdx' Reason: 'the optional indirection is deactivated because DtrTableIndUsedOfEventTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_DTRTABLEINDUSEDOFEVENTTABLE                           STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.DtrTableIndUsed' Reason: 'the optional indirection is deactivated because DtrTableIndUsedOfEventTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_ENABLECONDITIONGROUPTABLEIDXOFEVENTTABLE              STD_ON
#define DEM_CFG_EVENTDATACHANGEDIDXOFEVENTTABLE                       STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.EventDataChangedIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_EVENTDESTINATIONOFEVENTTABLE                          STD_ON
#define DEM_CFG_EVENTFAILURECYCLECOUNTERTHRESHOLDOFEVENTTABLE         STD_ON
#define DEM_CFG_EVENTKINDOFEVENTTABLE                                 STD_ON
#define DEM_CFG_EVENTLATCHTFOFEVENTTABLE                              STD_ON
#define DEM_CFG_EVENTPRIORITYOFEVENTTABLE                             STD_ON
#define DEM_CFG_EVENTSIGNIFICANCEOFEVENTTABLE                         STD_ON
#define DEM_CFG_EVENTSTATUSCHANGEDENDIDXOFEVENTTABLE                  STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.EventStatusChangedEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_EVENTSTATUSCHANGEDSTARTIDXOFEVENTTABLE                STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.EventStatusChangedStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_EVENTSTATUSCHANGEDUSEDOFEVENTTABLE                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.EventStatusChangedUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_EXTENDEDDATATABLEIDXOFEVENTTABLE                      STD_ON
#define DEM_CFG_FREEZEFRAMENUMTABLEENDIDXOFEVENTTABLE                 STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.FreezeFrameNumTableEndIdx' Reason: 'the optional indirection is deactivated because FreezeFrameNumTableUsedOfEventTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_FREEZEFRAMENUMTABLESTARTIDXOFEVENTTABLE               STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.FreezeFrameNumTableStartIdx' Reason: 'the optional indirection is deactivated because FreezeFrameNumTableUsedOfEventTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_FREEZEFRAMENUMTABLEUSEDOFEVENTTABLE                   STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.FreezeFrameNumTableUsed' Reason: 'the optional indirection is deactivated because FreezeFrameNumTableUsedOfEventTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_FREEZEFRAMETABLESTDFFIDXOFEVENTTABLE                  STD_ON
#define DEM_CFG_HEALINGTARGETOFEVENTTABLE                             STD_ON
#define DEM_CFG_INITMONLISTFORFUNCIDXOFEVENTTABLE                     STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.InitMonListForFuncIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_INITMONITORFOREVENTIDXOFEVENTTABLE                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.InitMonitorForEventIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_INITMONITORFOREVENTUSEDOFEVENTTABLE                   STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.InitMonitorForEventUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_MASKEDBITSOFEVENTTABLE                                STD_ON
#define DEM_CFG_NORMALINDICATORTABLEENDIDXOFEVENTTABLE                STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.NormalIndicatorTableEndIdx' Reason: 'no normal indicator is configured (DEM_CFG_SUPPORT_USER_INDICATORS==STD_OFF)' */
#define DEM_CFG_NORMALINDICATORTABLESTARTIDXOFEVENTTABLE              STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.NormalIndicatorTableStartIdx' Reason: 'no normal indicator is configured (DEM_CFG_SUPPORT_USER_INDICATORS==STD_OFF)' */
#define DEM_CFG_NORMALINDICATORTABLEUSEDOFEVENTTABLE                  STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.NormalIndicatorTableUsed' Reason: 'no normal indicator is configured (DEM_CFG_SUPPORT_USER_INDICATORS==STD_OFF)' */
#define DEM_CFG_OPERATIONCYCLEIDOFEVENTTABLE                          STD_ON
#define DEM_CFG_SATELLITEEVENTIDXOFEVENTTABLE                         STD_ON
#define DEM_CFG_SATELLITEINFOIDXOFEVENTTABLE                          STD_ON
#define DEM_CFG_STORAGECONDITIONGROUPTABLEIDXOFEVENTTABLE             STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.StorageConditionGroupTableIdx' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_STORAGECONDITIONGROUPTABLEUSEDOFEVENTTABLE            STD_OFF  /**< Deactivateable: 'Dem_Cfg_EventTable.StorageConditionGroupTableUsed' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_EVENTTABLEIND                                         STD_ON
#define DEM_CFG_EXTENDEDDATATABLE                                     STD_ON
#define DEM_CFG_DATACOLLECTIONTABLEEDR2COLLINDENDIDXOFEXTENDEDDATATABLE STD_ON
#define DEM_CFG_DATACOLLECTIONTABLEEDR2COLLINDSTARTIDXOFEXTENDEDDATATABLE STD_ON
#define DEM_CFG_DATACOLLECTIONTABLEEDR2COLLINDUSEDOFEXTENDEDDATATABLE STD_ON
#define DEM_CFG_MAXRECORDSIZEOFEXTENDEDDATATABLE                      STD_ON
#define DEM_CFG_FILTERINFOTABLE                                       STD_ON
#define DEM_CFG_FILTERREPORTEDEVENTS                                  STD_ON
#define DEM_CFG_FINALMAGICNUMBER                                      STD_OFF  /**< Deactivateable: 'Dem_Cfg_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define DEM_CFG_FREEZEFRAMEDATA                                       STD_OFF  /**< Deactivateable: 'Dem_Cfg_FreezeFrameData' Reason: '(DEM_CFG_SUPPORT_OBDII == STD_OFF)' */
#define DEM_CFG_FREEZEFRAMEITERATORTABLE                              STD_ON
#define DEM_CFG_FREEZEFRAMENUMTABLE                                   STD_OFF  /**< Deactivateable: 'Dem_Cfg_FreezeFrameNumTable' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define DEM_CFG_FFNUMBEROFFREEZEFRAMENUMTABLE                         STD_OFF  /**< Deactivateable: 'Dem_Cfg_FreezeFrameNumTable.FFNumber' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_FFTRIGGEROFFREEZEFRAMENUMTABLE                        STD_OFF  /**< Deactivateable: 'Dem_Cfg_FreezeFrameNumTable.FFTrigger' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_FFUPDATEOFFREEZEFRAMENUMTABLE                         STD_OFF  /**< Deactivateable: 'Dem_Cfg_FreezeFrameNumTable.FFUpdate' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_FREEZEFRAMETABLE                                      STD_ON
#define DEM_CFG_DATACOLLECTIONTABLEFFM2COLLINDENDIDXOFFREEZEFRAMETABLE STD_OFF  /**< Deactivateable: 'Dem_Cfg_FreezeFrameTable.DataCollectionTableFfm2CollIndEndIdx' Reason: 'the optional indirection is deactivated because DataCollectionTableFfm2CollIndUsedOfFreezeFrameTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_DATACOLLECTIONTABLEFFM2COLLINDSTARTIDXOFFREEZEFRAMETABLE STD_OFF  /**< Deactivateable: 'Dem_Cfg_FreezeFrameTable.DataCollectionTableFfm2CollIndStartIdx' Reason: 'the optional indirection is deactivated because DataCollectionTableFfm2CollIndUsedOfFreezeFrameTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_DATACOLLECTIONTABLEFFM2COLLINDUSEDOFFREEZEFRAMETABLE  STD_OFF  /**< Deactivateable: 'Dem_Cfg_FreezeFrameTable.DataCollectionTableFfm2CollIndUsed' Reason: 'the optional indirection is deactivated because DataCollectionTableFfm2CollIndUsedOfFreezeFrameTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_RECORDSIZEOFFREEZEFRAMETABLE                          STD_ON
#define DEM_CFG_RECORDSIZEUDSOFFREEZEFRAMETABLE                       STD_ON
#define DEM_CFG_GENERALJ1939TABLE                                     STD_OFF  /**< Deactivateable: 'Dem_Cfg_GeneralJ1939Table' Reason: 'no DemJ1939FreezeFrameClass (FreezeFrames)' */
#define DEM_CFG_DATACOLLECTIONTABLEJ19392COLLINDENDIDXOFGENERALJ1939TABLE STD_OFF  /**< Deactivateable: 'Dem_Cfg_GeneralJ1939Table.DataCollectionTableJ19392CollIndEndIdx' Reason: 'no DemJ1939FreezeFrameClass (FreezeFrames)' */
#define DEM_CFG_DATACOLLECTIONTABLEJ19392COLLINDSTARTIDXOFGENERALJ1939TABLE STD_OFF  /**< Deactivateable: 'Dem_Cfg_GeneralJ1939Table.DataCollectionTableJ19392CollIndStartIdx' Reason: 'no DemJ1939FreezeFrameClass (FreezeFrames)' */
#define DEM_CFG_DATACOLLECTIONTABLEJ19392COLLINDUSEDOFGENERALJ1939TABLE STD_OFF  /**< Deactivateable: 'Dem_Cfg_GeneralJ1939Table.DataCollectionTableJ19392CollIndUsed' Reason: 'no DemJ1939FreezeFrameClass (FreezeFrames)' */
#define DEM_CFG_RECORDSIZEOFGENERALJ1939TABLE                         STD_OFF  /**< Deactivateable: 'Dem_Cfg_GeneralJ1939Table.RecordSize' Reason: 'no DemJ1939FreezeFrameClass (FreezeFrames)' */
#define DEM_CFG_GENERALOBDINPUT                                       STD_ON
#define DEM_CFG_DATAELEMENTTABLEIDXOFGENERALOBDINPUT                  STD_ON
#define DEM_CFG_GLOBALINDICATORSTATES                                 STD_OFF  /**< Deactivateable: 'Dem_Cfg_GlobalIndicatorStates' Reason: 'the array is deactivated because the size is 0 in all variants and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_GLOBALOBDREQUIREMENTS                                 STD_OFF  /**< Deactivateable: 'Dem_Cfg_GlobalObdRequirements' Reason: '((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF))' */
#define DEM_CFG_GLOBALSEVERITYMASK                                    STD_ON
#define DEM_CFG_INDICATORBLINKING                                     STD_OFF  /**< Deactivateable: 'Dem_Cfg_IndicatorBlinking' Reason: 'the array is deactivated because the size is 0 in all variants and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_INDICATORCONTINUOUS                                   STD_OFF  /**< Deactivateable: 'Dem_Cfg_IndicatorContinuous' Reason: 'the array is deactivated because the size is 0 in all variants and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_INDICATORFASTFLASH                                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_IndicatorFastFlash' Reason: '(DEM_CFG_SUPPORT_J1939 == STD_OFF)' */
#define DEM_CFG_INDICATORSLOWFLASH                                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_IndicatorSlowFlash' Reason: '(DEM_CFG_SUPPORT_J1939 == STD_OFF)' */
#define DEM_CFG_INITDATAHASHCODE                                      STD_OFF  /**< Deactivateable: 'Dem_Cfg_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define DEM_CFG_INITMONLISTFORFUNC                                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_InitMonListForFunc' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define DEM_CFG_INITMONITORSFORFUNCENDIDXOFINITMONLISTFORFUNC         STD_OFF  /**< Deactivateable: 'Dem_Cfg_InitMonListForFunc.InitMonitorsForFuncEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_INITMONITORSFORFUNCSTARTIDXOFINITMONLISTFORFUNC       STD_OFF  /**< Deactivateable: 'Dem_Cfg_InitMonListForFunc.InitMonitorsForFuncStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_INITMONITORSFORFUNCUSEDOFINITMONLISTFORFUNC           STD_OFF  /**< Deactivateable: 'Dem_Cfg_InitMonListForFunc.InitMonitorsForFuncUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_INITMONITORFOREVENT                                   STD_OFF  /**< Deactivateable: 'Dem_Cfg_InitMonitorForEvent' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_INITMONITORSFORFUNC                                   STD_OFF  /**< Deactivateable: 'Dem_Cfg_InitMonitorsForFunc' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_J1939NODEID                                           STD_OFF  /**< Deactivateable: 'Dem_Cfg_J1939NodeId' Reason: '(DEM_CFG_HAS_J1939_NODE == STD_OFF)' */
#define DEM_CFG_J1939NODEIDIND                                        STD_OFF  /**< Deactivateable: 'Dem_Cfg_J1939NodeIdInd' Reason: '(DEM_CFG_HAS_J1939_NODE == STD_OFF)' */
#define DEM_CFG_J1939NODEINDICATOR                                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_J1939NodeIndicator' Reason: '(DEM_CFG_HAS_J1939_NODE == STD_OFF)' */
#define DEM_CFG_MEMORYBLOCKID                                         STD_OFF  /**< Deactivateable: 'Dem_Cfg_MemoryBlockId' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define DEM_CFG_MEMORYBLOCKIDTOMEMORYENTRYID                          STD_ON
#define DEM_CFG_MEMORYCOMMITNUMBER                                    STD_ON
#define DEM_CFG_MEMORYDATAPTR                                         STD_ON
#define DEM_CFG_MEMORYDATASIZE                                        STD_ON
#define DEM_CFG_MEMORYENTRY                                           STD_ON
#define DEM_CFG_MEMORYENTRYINIT                                       STD_ON
#define DEM_CFG_MEMORYSTATUS                                          STD_ON
#define DEM_CFG_MIDTABLE                                              STD_OFF  /**< Deactivateable: 'Dem_Cfg_MidTable' Reason: 'No Dtr support.' */
#define DEM_CFG_DTRTABLEIDXOFMIDTABLE                                 STD_OFF  /**< Deactivateable: 'Dem_Cfg_MidTable.DtrTableIdx' Reason: 'No Dtr support.' */
#define DEM_CFG_MIDOFMIDTABLE                                         STD_OFF  /**< Deactivateable: 'Dem_Cfg_MidTable.Mid' Reason: 'No Dtr support.' */
#define DEM_CFG_TIDOFMIDTABLE                                         STD_OFF  /**< Deactivateable: 'Dem_Cfg_MidTable.Tid' Reason: 'No Dtr support.' */
#define DEM_CFG_MIRRORDATA                                            STD_OFF  /**< Deactivateable: 'Dem_Cfg_MirrorData' Reason: 'DEM_CFG_SUPPORT_MIRROR==STD_OFF' */
#define DEM_CFG_NORMALINDICATORTABLE                                  STD_OFF  /**< Deactivateable: 'Dem_Cfg_NormalIndicatorTable' Reason: 'no normal indicator is configured (DEM_CFG_SUPPORT_USER_INDICATORS==STD_OFF)' */
#define DEM_CFG_BEHAVIOROFNORMALINDICATORTABLE                        STD_OFF  /**< Deactivateable: 'Dem_Cfg_NormalIndicatorTable.Behavior' Reason: 'no normal indicator is configured (DEM_CFG_SUPPORT_USER_INDICATORS==STD_OFF)' */
#define DEM_CFG_IDOFNORMALINDICATORTABLE                              STD_OFF  /**< Deactivateable: 'Dem_Cfg_NormalIndicatorTable.Id' Reason: 'no normal indicator is configured (DEM_CFG_SUPPORT_USER_INDICATORS==STD_OFF)' */
#define DEM_CFG_OBDIUMPRDATA                                          STD_OFF  /**< Deactivateable: 'Dem_Cfg_ObdIumprData' Reason: '(((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF))) || (DEM_CFG_SUPPORT_IUMPR==STD_OFF)' */
#define DEM_CFG_OBDIUMPRUPDATEPENDING                                 STD_OFF  /**< Deactivateable: 'Dem_Cfg_ObdIumprUpdatePending' Reason: '(((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF))) || (DEM_CFG_SUPPORT_IUMPR==STD_OFF)' */
#define DEM_CFG_PERMANENTDATA                                         STD_OFF  /**< Deactivateable: 'Dem_Cfg_PermanentData' Reason: '(DEM_CFG_SUPPORT_PERMANENT==STD_OFF) || ((DEM_CFG_SUPPORT_OBDII == STD_OFF))' */
#define DEM_CFG_PIDTABLE                                              STD_OFF  /**< Deactivateable: 'Dem_Cfg_PidTable' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define DEM_CFG_DATACOLLECTIONTABLEPID2COLLINDENDIDXOFPIDTABLE        STD_OFF  /**< Deactivateable: 'Dem_Cfg_PidTable.DataCollectionTablePid2CollIndEndIdx' Reason: 'the optional indirection is deactivated because DataCollectionTablePid2CollIndUsedOfPidTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_DATACOLLECTIONTABLEPID2COLLINDSTARTIDXOFPIDTABLE      STD_OFF  /**< Deactivateable: 'Dem_Cfg_PidTable.DataCollectionTablePid2CollIndStartIdx' Reason: 'the optional indirection is deactivated because DataCollectionTablePid2CollIndUsedOfPidTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_DATACOLLECTIONTABLEPID2COLLINDUSEDOFPIDTABLE          STD_OFF  /**< Deactivateable: 'Dem_Cfg_PidTable.DataCollectionTablePid2CollIndUsed' Reason: 'the optional indirection is deactivated because DataCollectionTablePid2CollIndUsedOfPidTable is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_PRESTORAGE                                            STD_OFF  /**< Deactivateable: 'Dem_Cfg_Prestorage' Reason: 'DEM_CFG_SUPPORT_PRESTORED_FF==STD_OFF' */
#define DEM_CFG_PRESTORAGEINDEX                                       STD_OFF  /**< Deactivateable: 'Dem_Cfg_PrestorageIndex' Reason: 'DEM_CFG_SUPPORT_PRESTORED_FF==STD_OFF' */
#define DEM_CFG_PRIMARYCHRONOLOGY                                     STD_ON
#define DEM_CFG_PRIMARYENTRY_0                                        STD_ON
#define DEM_CFG_PRIMARYENTRY_1                                        STD_ON
#define DEM_CFG_PRIMARYENTRY_10                                       STD_ON
#define DEM_CFG_PRIMARYENTRY_11                                       STD_ON
#define DEM_CFG_PRIMARYENTRY_12                                       STD_ON
#define DEM_CFG_PRIMARYENTRY_13                                       STD_ON
#define DEM_CFG_PRIMARYENTRY_14                                       STD_ON
#define DEM_CFG_PRIMARYENTRY_15                                       STD_ON
#define DEM_CFG_PRIMARYENTRY_16                                       STD_ON
#define DEM_CFG_PRIMARYENTRY_17                                       STD_ON
#define DEM_CFG_PRIMARYENTRY_2                                        STD_ON
#define DEM_CFG_PRIMARYENTRY_3                                        STD_ON
#define DEM_CFG_PRIMARYENTRY_4                                        STD_ON
#define DEM_CFG_PRIMARYENTRY_5                                        STD_ON
#define DEM_CFG_PRIMARYENTRY_6                                        STD_ON
#define DEM_CFG_PRIMARYENTRY_7                                        STD_ON
#define DEM_CFG_PRIMARYENTRY_8                                        STD_ON
#define DEM_CFG_PRIMARYENTRY_9                                        STD_ON
#define DEM_CFG_RATIOIDTABLE                                          STD_OFF  /**< Deactivateable: 'Dem_Cfg_RatioIdTable' Reason: 'no OBD support or no DemRatioId container configured' */
#define DEM_CFG_READOUTBUFFER                                         STD_ON
#define DEM_CFG_REPORTEDEVENTSOFFILTER                                STD_ON
#define DEM_CFG_SATELLITEINFO                                         STD_ON
#define DEM_CFG_APPLICATIONIDOFSATELLITEINFO                          STD_ON
#define DEM_CFG_DEBOUNCELORESTIMEROFSATELLITEINFO                     STD_OFF  /**< Deactivateable: 'Dem_Cfg_SatelliteInfo.DebounceLoResTimer' Reason: 'No LowRes Timebased Debouncing support (DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR == STD_OFF)' */
#define DEM_CFG_EVENTCOUNTOFSATELLITEINFO                             STD_ON
#define DEM_CFG_EVENTTABLEINDENDIDXOFSATELLITEINFO                    STD_ON
#define DEM_CFG_EVENTTABLEINDSTARTIDXOFSATELLITEINFO                  STD_ON
#define DEM_CFG_EVENTTABLEINDUSEDOFSATELLITEINFO                      STD_ON
#define DEM_CFG_MAXDEBOUNCEVALUESOFSATELLITEINFO                      STD_OFF  /**< Deactivateable: 'Dem_Cfg_SatelliteInfo.MaxDebounceValues' Reason: 'Neither DataElement type DEM_MAX_FDC_SINCE_LAST_CLEAR nor DEM_MAX_FDC_DURING_CURRENT_CYCLE is used (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_OFF) && (DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_OFF)' */
#define DEM_CFG_SATELLITEDATAOFSATELLITEINFO                          STD_ON
#define DEM_CFG_SATELLITEEXTENDEDDATAOFSATELLITEINFO                  STD_OFF  /**< Deactivateable: 'Dem_Cfg_SatelliteInfo.SatelliteExtendedData' Reason: 'No Prestored FreezeFrame support (DEM_CFG_SUPPORT_PRESTORED_FF == STD_OFF)' */
#define DEM_CFG_SATELLITESTATUSOFSATELLITEINFO                        STD_ON
#define DEM_CFG_SATELLITEINFO0                                        STD_ON
#define DEM_CFG_SATELLITETIMEDEBOUNCEINFO                             STD_OFF  /**< Deactivateable: 'Dem_Cfg_SatelliteTimeDebounceInfo' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define DEM_CFG_DEBOUNCEHIRESTABLEENDIDXOFSATELLITETIMEDEBOUNCEINFO   STD_OFF  /**< Deactivateable: 'Dem_Cfg_SatelliteTimeDebounceInfo.DebounceHiResTableEndIdx' Reason: 'the optional indirection is deactivated because DebounceHiResTableUsedOfSatelliteTimeDebounceInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_DEBOUNCEHIRESTABLESTARTIDXOFSATELLITETIMEDEBOUNCEINFO STD_OFF  /**< Deactivateable: 'Dem_Cfg_SatelliteTimeDebounceInfo.DebounceHiResTableStartIdx' Reason: 'the optional indirection is deactivated because DebounceHiResTableUsedOfSatelliteTimeDebounceInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_DEBOUNCEHIRESTABLEUSEDOFSATELLITETIMEDEBOUNCEINFO     STD_OFF  /**< Deactivateable: 'Dem_Cfg_SatelliteTimeDebounceInfo.DebounceHiResTableUsed' Reason: 'the optional indirection is deactivated because DebounceHiResTableUsedOfSatelliteTimeDebounceInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_DEBOUNCELORESTABLEENDIDXOFSATELLITETIMEDEBOUNCEINFO   STD_OFF  /**< Deactivateable: 'Dem_Cfg_SatelliteTimeDebounceInfo.DebounceLoResTableEndIdx' Reason: 'the optional indirection is deactivated because DebounceLoResTableUsedOfSatelliteTimeDebounceInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_DEBOUNCELORESTABLESTARTIDXOFSATELLITETIMEDEBOUNCEINFO STD_OFF  /**< Deactivateable: 'Dem_Cfg_SatelliteTimeDebounceInfo.DebounceLoResTableStartIdx' Reason: 'the optional indirection is deactivated because DebounceLoResTableUsedOfSatelliteTimeDebounceInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_DEBOUNCELORESTABLEUSEDOFSATELLITETIMEDEBOUNCEINFO     STD_OFF  /**< Deactivateable: 'Dem_Cfg_SatelliteTimeDebounceInfo.DebounceLoResTableUsed' Reason: 'the optional indirection is deactivated because DebounceLoResTableUsedOfSatelliteTimeDebounceInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define DEM_CFG_SECONDARYCHRONOLOGY                                   STD_OFF  /**< Deactivateable: 'Dem_Cfg_SecondaryChronology' Reason: 'DEM_CFG_SUPPORT_SECONDARY==STD_OFF' */
#define DEM_CFG_SIZEOFCLEARDTCTABLE                                   STD_ON
#define DEM_CFG_SIZEOFCLIENTTABLE                                     STD_ON
#define DEM_CFG_SIZEOFDTCSELECTORTABLE                                STD_ON
#define DEM_CFG_SIZEOFDATAELEMENTTABLE                                STD_ON
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPCOUNTER                     STD_ON
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPSTATE                       STD_ON
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPTABLE                       STD_ON
#define DEM_CFG_SIZEOFENABLECONDITIONSTATE                            STD_ON
#define DEM_CFG_SIZEOFENABLECONDITIONTABLE                            STD_ON
#define DEM_CFG_SIZEOFEVENTDEBOUNCEVALUE                              STD_ON
#define DEM_CFG_SIZEOFEVENTINTERNALSTATUS                             STD_ON
#define DEM_CFG_SIZEOFEVENTTABLE                                      STD_ON
#define DEM_CFG_SIZEOFFILTERINFOTABLE                                 STD_ON
#define DEM_CFG_SIZEOFFILTERREPORTEDEVENTS                            STD_ON
#define DEM_CFG_SIZEOFFREEZEFRAMEITERATORTABLE                        STD_ON
#define DEM_CFG_SIZEOFMEMORYBLOCKIDTOMEMORYENTRYID                    STD_ON
#define DEM_CFG_SIZEOFMEMORYCOMMITNUMBER                              STD_ON
#define DEM_CFG_SIZEOFMEMORYENTRY                                     STD_ON
#define DEM_CFG_SIZEOFMEMORYSTATUS                                    STD_ON
#define DEM_CFG_SIZEOFPRIMARYCHRONOLOGY                               STD_ON
#define DEM_CFG_SIZEOFREADOUTBUFFER                                   STD_ON
#define DEM_CFG_SIZEOFREPORTEDEVENTSOFFILTER                          STD_ON
#define DEM_CFG_SIZEOFSATELLITEINFO                                   STD_ON
#define DEM_CFG_SPECIALINDICATORTABLE                                 STD_OFF  /**< Deactivateable: 'Dem_Cfg_SpecialIndicatorTable' Reason: 'no special indicator is configured' */
#define DEM_CFG_BEHAVIOROFSPECIALINDICATORTABLE                       STD_OFF  /**< Deactivateable: 'Dem_Cfg_SpecialIndicatorTable.Behavior' Reason: 'no special indicator is configured' */
#define DEM_CFG_IDOFSPECIALINDICATORTABLE                             STD_OFF  /**< Deactivateable: 'Dem_Cfg_SpecialIndicatorTable.Id' Reason: 'no special indicator is configured' */
#define DEM_CFG_STATUSDATA                                            STD_ON
#define DEM_CFG_STORAGECONDITIONGROUPCOUNTER                          STD_OFF  /**< Deactivateable: 'Dem_Cfg_StorageConditionGroupCounter' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_STORAGECONDITIONGROUPTABLE                            STD_OFF  /**< Deactivateable: 'Dem_Cfg_StorageConditionGroupTable' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_INDEXOFSTORAGECONDITIONGROUPTABLE                     STD_OFF  /**< Deactivateable: 'Dem_Cfg_StorageConditionGroupTable.Index' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_STORAGECONDITIONGROUPTABLEIND                         STD_OFF  /**< Deactivateable: 'Dem_Cfg_StorageConditionGroupTableInd' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_STORAGECONDITIONINITTABLE                             STD_OFF  /**< Deactivateable: 'Dem_Cfg_StorageConditionInitTable' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_INITVALUEOFSTORAGECONDITIONINITTABLE                  STD_OFF  /**< Deactivateable: 'Dem_Cfg_StorageConditionInitTable.InitValue' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_STORAGECONDITIONSTATE                                 STD_OFF  /**< Deactivateable: 'Dem_Cfg_StorageConditionState' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_STORAGECONDITIONTABLE                                 STD_OFF  /**< Deactivateable: 'Dem_Cfg_StorageConditionTable' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_STORAGECONDITIONGROUPTABLEINDENDIDXOFSTORAGECONDITIONTABLE STD_OFF  /**< Deactivateable: 'Dem_Cfg_StorageConditionTable.StorageConditionGroupTableIndEndIdx' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_STORAGECONDITIONGROUPTABLEINDSTARTIDXOFSTORAGECONDITIONTABLE STD_OFF  /**< Deactivateable: 'Dem_Cfg_StorageConditionTable.StorageConditionGroupTableIndStartIdx' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_STORAGECONDITIONGROUPTABLEINDUSEDOFSTORAGECONDITIONTABLE STD_OFF  /**< Deactivateable: 'Dem_Cfg_StorageConditionTable.StorageConditionGroupTableIndUsed' Reason: '(DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF)' */
#define DEM_CFG_SUPPORTEDMIDSTABLE                                    STD_OFF  /**< Deactivateable: 'Dem_Cfg_SupportedMidsTable' Reason: 'No Dtr support.' */
#define DEM_CFG_STARTIDXMIDTABLEOFSUPPORTEDMIDSTABLE                  STD_OFF  /**< Deactivateable: 'Dem_Cfg_SupportedMidsTable.StartIdxMidTable' Reason: 'No Dtr support.' */
#define DEM_CFG_SUPPORTEDMIDMASKOFSUPPORTEDMIDSTABLE                  STD_OFF  /**< Deactivateable: 'Dem_Cfg_SupportedMidsTable.SupportedMidMask' Reason: 'No Dtr support.' */
#define DEM_CFG_TIMESERIESCHRONOLOGY                                  STD_OFF  /**< Deactivateable: 'Dem_Cfg_TimeSeriesChronology' Reason: '(DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL==STD_OFF && DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL==STD_OFF && DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST==STD_OFF && DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST==STD_OFF) || (DEM_CFG_SUPPORT_PRIMARY==STD_OFF)' */
#define DEM_CFG_TIMESERIESENTRYINIT                                   STD_ON
#define DEM_CFG_TIMESERIESREADOUTBUFFER                               STD_OFF  /**< Deactivateable: 'Dem_Cfg_TimeSeriesReadoutBuffer' Reason: 'DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL==STD_OFF && DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL==STD_OFF && DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST==STD_OFF && DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST==STD_OFF' */
#define DEM_PCCONFIG                                                  STD_ON
#define DEM_CFG_ADMINDATAOFPCCONFIG                                   STD_ON
#define DEM_CFG_CLEARDTCTABLEOFPCCONFIG                               STD_ON
#define DEM_CFG_CLIENTTABLEOFPCCONFIG                                 STD_ON
#define DEM_CFG_COMMITBUFFEROFPCCONFIG                                STD_ON
#define DEM_CFG_CONFIGURATIONIDOFPCCONFIG                             STD_ON
#define DEM_CFG_CYCLEIDTABLEOFPCCONFIG                                STD_ON
#define DEM_CFG_DTCSELECTORTABLEOFPCCONFIG                            STD_ON
#define DEM_CFG_DATACOLLECTIONTABLEEDR2COLLINDOFPCCONFIG              STD_ON
#define DEM_CFG_DATACOLLECTIONTABLEOFPCCONFIG                         STD_ON
#define DEM_CFG_DATAELEMENTTABLECOL2ELMTINDOFPCCONFIG                 STD_ON
#define DEM_CFG_DATAELEMENTTABLEOFPCCONFIG                            STD_ON
#define DEM_CFG_DEBOUNCETABLEOFPCCONFIG                               STD_ON
#define DEM_CFG_DTCTABLEOFPCCONFIG                                    STD_ON
#define DEM_CFG_ENABLECONDITIONGROUPCOUNTEROFPCCONFIG                 STD_ON
#define DEM_CFG_ENABLECONDITIONGROUPSTATEOFPCCONFIG                   STD_ON
#define DEM_CFG_ENABLECONDITIONGROUPTABLEINDOFPCCONFIG                STD_ON
#define DEM_CFG_ENABLECONDITIONGROUPTABLEOFPCCONFIG                   STD_ON
#define DEM_CFG_ENABLECONDITIONINITTABLEOFPCCONFIG                    STD_ON
#define DEM_CFG_ENABLECONDITIONSTATEOFPCCONFIG                        STD_ON
#define DEM_CFG_ENABLECONDITIONTABLEOFPCCONFIG                        STD_ON
#define DEM_CFG_EVENTAVAILABLEDEFAULTOFPCCONFIG                       STD_ON
#define DEM_CFG_EVENTAVAILABLEINVARIANTOFPCCONFIG                     STD_ON
#define DEM_CFG_EVENTDEBOUNCEVALUEOFPCCONFIG                          STD_ON
#define DEM_CFG_EVENTINTERNALSTATUSOFPCCONFIG                         STD_ON
#define DEM_CFG_EVENTTABLEINDOFPCCONFIG                               STD_ON
#define DEM_CFG_EVENTTABLEOFPCCONFIG                                  STD_ON
#define DEM_CFG_EXTENDEDDATATABLEOFPCCONFIG                           STD_ON
#define DEM_CFG_FILTERINFOTABLEOFPCCONFIG                             STD_ON
#define DEM_CFG_FILTERREPORTEDEVENTSOFPCCONFIG                        STD_ON
#define DEM_CFG_FINALMAGICNUMBEROFPCCONFIG                            STD_OFF  /**< Deactivateable: 'Dem_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define DEM_CFG_FREEZEFRAMEITERATORTABLEOFPCCONFIG                    STD_ON
#define DEM_CFG_FREEZEFRAMETABLEOFPCCONFIG                            STD_ON
#define DEM_CFG_GENERALOBDINPUTOFPCCONFIG                             STD_ON
#define DEM_CFG_GLOBALOBDREQUIREMENTSOFPCCONFIG                       STD_OFF  /**< Deactivateable: 'Dem_PCConfig.GlobalObdRequirements' Reason: '((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF))' */
#define DEM_CFG_GLOBALSEVERITYMASKOFPCCONFIG                          STD_ON
#define DEM_CFG_INITDATAHASHCODEOFPCCONFIG                            STD_OFF  /**< Deactivateable: 'Dem_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define DEM_CFG_MEMORYBLOCKIDTOMEMORYENTRYIDOFPCCONFIG                STD_ON
#define DEM_CFG_MEMORYCOMMITNUMBEROFPCCONFIG                          STD_ON
#define DEM_CFG_MEMORYDATAPTROFPCCONFIG                               STD_ON
#define DEM_CFG_MEMORYDATASIZEOFPCCONFIG                              STD_ON
#define DEM_CFG_MEMORYENTRYINITOFPCCONFIG                             STD_ON
#define DEM_CFG_MEMORYENTRYOFPCCONFIG                                 STD_ON
#define DEM_CFG_MEMORYSTATUSOFPCCONFIG                                STD_ON
#define DEM_CFG_PRIMARYCHRONOLOGYOFPCCONFIG                           STD_ON
#define DEM_CFG_PRIMARYENTRY_0OFPCCONFIG                              STD_ON
#define DEM_CFG_PRIMARYENTRY_10OFPCCONFIG                             STD_ON
#define DEM_CFG_PRIMARYENTRY_11OFPCCONFIG                             STD_ON
#define DEM_CFG_PRIMARYENTRY_12OFPCCONFIG                             STD_ON
#define DEM_CFG_PRIMARYENTRY_13OFPCCONFIG                             STD_ON
#define DEM_CFG_PRIMARYENTRY_14OFPCCONFIG                             STD_ON
#define DEM_CFG_PRIMARYENTRY_15OFPCCONFIG                             STD_ON
#define DEM_CFG_PRIMARYENTRY_16OFPCCONFIG                             STD_ON
#define DEM_CFG_PRIMARYENTRY_17OFPCCONFIG                             STD_ON
#define DEM_CFG_PRIMARYENTRY_1OFPCCONFIG                              STD_ON
#define DEM_CFG_PRIMARYENTRY_2OFPCCONFIG                              STD_ON
#define DEM_CFG_PRIMARYENTRY_3OFPCCONFIG                              STD_ON
#define DEM_CFG_PRIMARYENTRY_4OFPCCONFIG                              STD_ON
#define DEM_CFG_PRIMARYENTRY_5OFPCCONFIG                              STD_ON
#define DEM_CFG_PRIMARYENTRY_6OFPCCONFIG                              STD_ON
#define DEM_CFG_PRIMARYENTRY_7OFPCCONFIG                              STD_ON
#define DEM_CFG_PRIMARYENTRY_8OFPCCONFIG                              STD_ON
#define DEM_CFG_PRIMARYENTRY_9OFPCCONFIG                              STD_ON
#define DEM_CFG_READOUTBUFFEROFPCCONFIG                               STD_ON
#define DEM_CFG_REPORTEDEVENTSOFFILTEROFPCCONFIG                      STD_ON
#define DEM_CFG_SATELLITEINFO0OFPCCONFIG                              STD_ON
#define DEM_CFG_SATELLITEINFOOFPCCONFIG                               STD_ON
#define DEM_CFG_SIZEOFCLEARDTCTABLEOFPCCONFIG                         STD_ON
#define DEM_CFG_SIZEOFCLIENTTABLEOFPCCONFIG                           STD_ON
#define DEM_CFG_SIZEOFDTCSELECTORTABLEOFPCCONFIG                      STD_ON
#define DEM_CFG_SIZEOFDATAELEMENTTABLEOFPCCONFIG                      STD_ON
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPCOUNTEROFPCCONFIG           STD_ON
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPSTATEOFPCCONFIG             STD_ON
#define DEM_CFG_SIZEOFENABLECONDITIONGROUPTABLEOFPCCONFIG             STD_ON
#define DEM_CFG_SIZEOFENABLECONDITIONSTATEOFPCCONFIG                  STD_ON
#define DEM_CFG_SIZEOFENABLECONDITIONTABLEOFPCCONFIG                  STD_ON
#define DEM_CFG_SIZEOFEVENTDEBOUNCEVALUEOFPCCONFIG                    STD_ON
#define DEM_CFG_SIZEOFEVENTINTERNALSTATUSOFPCCONFIG                   STD_ON
#define DEM_CFG_SIZEOFEVENTTABLEOFPCCONFIG                            STD_ON
#define DEM_CFG_SIZEOFFILTERINFOTABLEOFPCCONFIG                       STD_ON
#define DEM_CFG_SIZEOFFILTERREPORTEDEVENTSOFPCCONFIG                  STD_ON
#define DEM_CFG_SIZEOFFREEZEFRAMEITERATORTABLEOFPCCONFIG              STD_ON
#define DEM_CFG_SIZEOFMEMORYBLOCKIDTOMEMORYENTRYIDOFPCCONFIG          STD_ON
#define DEM_CFG_SIZEOFMEMORYCOMMITNUMBEROFPCCONFIG                    STD_ON
#define DEM_CFG_SIZEOFMEMORYENTRYOFPCCONFIG                           STD_ON
#define DEM_CFG_SIZEOFMEMORYSTATUSOFPCCONFIG                          STD_ON
#define DEM_CFG_SIZEOFPRIMARYCHRONOLOGYOFPCCONFIG                     STD_ON
#define DEM_CFG_SIZEOFREADOUTBUFFEROFPCCONFIG                         STD_ON
#define DEM_CFG_SIZEOFREPORTEDEVENTSOFFILTEROFPCCONFIG                STD_ON
#define DEM_CFG_SIZEOFSATELLITEINFOOFPCCONFIG                         STD_ON
#define DEM_CFG_STATUSDATAOFPCCONFIG                                  STD_ON
#define DEM_CFG_TIMESERIESENTRYINITOFPCCONFIG                         STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCMinNumericValueDefines  Dem_Cfg Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define DEM_CFG_MIN_ENABLECONDITIONGROUPCOUNTER                       0u
#define DEM_CFG_MIN_ENABLECONDITIONGROUPSTATE                         0u
#define DEM_CFG_MIN_ENABLECONDITIONSTATE                              0u
#define DEM_CFG_MIN_EVENTDEBOUNCEVALUE                                -32768
#define DEM_CFG_MIN_FILTERREPORTEDEVENTS                              0u
#define DEM_CFG_MIN_MEMORYCOMMITNUMBER                                0u
#define DEM_CFG_MIN_MEMORYSTATUS                                      0u
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCMaxNumericValueDefines  Dem_Cfg Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define DEM_CFG_MAX_ENABLECONDITIONGROUPCOUNTER                       255u
#define DEM_CFG_MAX_ENABLECONDITIONGROUPSTATE                         255u
#define DEM_CFG_MAX_ENABLECONDITIONSTATE                              255u
#define DEM_CFG_MAX_EVENTDEBOUNCEVALUE                                32767
#define DEM_CFG_MAX_FILTERREPORTEDEVENTS                              255u
#define DEM_CFG_MAX_MEMORYCOMMITNUMBER                                255u
#define DEM_CFG_MAX_MEMORYSTATUS                                      255u
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCNoReferenceDefines  Dem_Cfg No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define DEM_CFG_NO_DATAELEMENTTABLECOL2ELMTINDENDIDXOFDATACOLLECTIONTABLE 255u
#define DEM_CFG_NO_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE 255u
#define DEM_CFG_NO_ENABLECONDITIONGROUPTABLEINDENDIDXOFENABLECONDITIONTABLE 255u
#define DEM_CFG_NO_ENABLECONDITIONGROUPTABLEINDSTARTIDXOFENABLECONDITIONTABLE 255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEEDR2COLLINDENDIDXOFEXTENDEDDATATABLE 255u
#define DEM_CFG_NO_DATACOLLECTIONTABLEEDR2COLLINDSTARTIDXOFEXTENDEDDATATABLE 255u
#define DEM_CFG_NO_EVENTTABLEINDENDIDXOFSATELLITEINFO                 255u
#define DEM_CFG_NO_EVENTTABLEINDSTARTIDXOFSATELLITEINFO               255u
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCEnumExistsDefines  Dem_Cfg Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define DEM_CFG_EXISTS_DEM_CFG_DEBOUNCETYPE_COUNTER_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE STD_ON
#define DEM_CFG_EXISTS_DEM_CFG_DEBOUNCETYPE_TIMER_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE STD_OFF
#define DEM_CFG_EXISTS_DEM_CFG_DEBOUNCETYPE_EXTERNAL_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE STD_OFF
#define DEM_CFG_EXISTS_DEM_CFG_DEBOUNCETYPE_INVALID_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE STD_ON
#define DEM_CFG_EXISTS_DEM_EVENT_KIND_BSW_EVENTKINDOFEVENTTABLE       STD_ON
#define DEM_CFG_EXISTS_DEM_EVENT_KIND_SWC_EVENTKINDOFEVENTTABLE       STD_ON
#define DEM_CFG_EXISTS_DEM_EVENT_SIGNIFICANCE_OCCURRENCE_EVENTSIGNIFICANCEOFEVENTTABLE STD_OFF
#define DEM_CFG_EXISTS_DEM_EVENT_SIGNIFICANCE_FAULT_EVENTSIGNIFICANCEOFEVENTTABLE STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCEnumDefines  Dem_Cfg Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define DEM_CFG_DEM_CFG_DEBOUNCETYPE_COUNTER_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE 0x00u
#define DEM_CFG_DEM_CFG_DEBOUNCETYPE_INVALID_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE 0x03u
#define DEM_CFG_DEM_EVENT_KIND_BSW_EVENTKINDOFEVENTTABLE              0x00u
#define DEM_CFG_DEM_EVENT_KIND_SWC_EVENTKINDOFEVENTTABLE              0x01u
#define DEM_CFG_DEM_EVENT_SIGNIFICANCE_FAULT_EVENTSIGNIFICANCEOFEVENTTABLE 0x01u
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCMaskedBitDefines  Dem_Cfg Masked Bit Defines (PRE_COMPILE)
  \brief  These defines are masks to extract packed boolean data.
  \{
*/ 
#define DEM_CFG_DATAELEMENTTABLECOL2ELMTINDUSEDOFDATACOLLECTIONTABLE_MASK 0x02u
#define DEM_CFG_UPDATEOFDATACOLLECTIONTABLE_MASK                      0x01u
#define DEM_CFG_DEBOUNCECONTINUOUSOFDEBOUNCETABLE_MASK                0x10u
#define DEM_CFG_EVENTDEBOUNCEBEHAVIOROFDEBOUNCETABLE_MASK             0x08u
#define DEM_CFG_JUMPDOWNOFDEBOUNCETABLE_MASK                          0x04u
#define DEM_CFG_JUMPUPOFDEBOUNCETABLE_MASK                            0x02u
#define DEM_CFG_STORAGEOFDEBOUNCETABLE_MASK                           0x01u
#define DEM_CFG_AGINGALLOWEDOFEVENTTABLE_MASK                         0x02u
#define DEM_CFG_EVENTLATCHTFOFEVENTTABLE_MASK                         0x01u
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCIsReducedToDefineDefines  Dem_Cfg Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define DEM_CFG_ISDEF_CLEARDTCINDEXOFCLIENTTABLE                      STD_ON
#define DEM_CFG_ISDEF_FILTERINDEXOFCLIENTTABLE                        STD_ON
#define DEM_CFG_ISDEF_FREEZEFRAMEITERATORINDEXOFCLIENTTABLE           STD_ON
#define DEM_CFG_ISDEF_READOUTBUFFERINDEXOFCLIENTTABLE                 STD_ON
#define DEM_CFG_ISDEF_SELECTORINDEXOFCLIENTTABLE                      STD_ON
#define DEM_CFG_ISDEF_OPCYCLETYPEOFCYCLEIDTABLE                       STD_OFF
#define DEM_CFG_ISDEF_USEDFORAGINGOFCYCLEIDTABLE                      STD_OFF
#define DEM_CFG_ISDEF_COLLECTIONSIZEOFDATACOLLECTIONTABLE             STD_OFF
#define DEM_CFG_ISDEF_DATAELEMENTTABLECOL2ELMTINDENDIDXOFDATACOLLECTIONTABLE STD_OFF
#define DEM_CFG_ISDEF_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE STD_OFF
#define DEM_CFG_ISDEF_DATAELEMENTTABLECOL2ELMTINDUSEDOFDATACOLLECTIONTABLE STD_OFF
#define DEM_CFG_ISDEF_IDNUMBEROFDATACOLLECTIONTABLE                   STD_OFF
#define DEM_CFG_ISDEF_MASKEDBITSOFDATACOLLECTIONTABLE                 STD_OFF
#define DEM_CFG_ISDEF_STORAGEKINDOFDATACOLLECTIONTABLE                STD_OFF
#define DEM_CFG_ISDEF_UPDATEOFDATACOLLECTIONTABLE                     STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEDR2COLLIND                  STD_OFF
#define DEM_CFG_ISDEF_DATAISSTOREDINNVOFDATAELEMENTTABLE              STD_OFF
#define DEM_CFG_ISDEF_ELEMENTKINDOFDATAELEMENTTABLE                   STD_OFF
#define DEM_CFG_ISDEF_ELEMENTSIZEOFDATAELEMENTTABLE                   STD_OFF
#define DEM_CFG_ISDEF_READDATAFUNCOFDATAELEMENTTABLE                  STD_OFF
#define DEM_CFG_ISDEF_DATAELEMENTTABLECOL2ELMTIND                     STD_OFF
#define DEM_CFG_ISDEF_DEBOUNCECONTINUOUSOFDEBOUNCETABLE               STD_ON
#define DEM_CFG_ISDEF_DECREMENTSTEPSIZEOFDEBOUNCETABLE                STD_OFF
#define DEM_CFG_ISDEF_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE           STD_OFF
#define DEM_CFG_ISDEF_EVENTDEBOUNCEBEHAVIOROFDEBOUNCETABLE            STD_ON
#define DEM_CFG_ISDEF_FAILTIMERCYCLESOFDEBOUNCETABLE                  STD_ON
#define DEM_CFG_ISDEF_FAILEDTHRESHOLDOFDEBOUNCETABLE                  STD_OFF
#define DEM_CFG_ISDEF_INCREMENTSTEPSIZEOFDEBOUNCETABLE                STD_OFF
#define DEM_CFG_ISDEF_JUMPDOWNOFDEBOUNCETABLE                         STD_OFF
#define DEM_CFG_ISDEF_JUMPDOWNVALUEOFDEBOUNCETABLE                    STD_ON
#define DEM_CFG_ISDEF_JUMPUPOFDEBOUNCETABLE                           STD_OFF
#define DEM_CFG_ISDEF_JUMPUPVALUEOFDEBOUNCETABLE                      STD_ON
#define DEM_CFG_ISDEF_MASKEDBITSOFDEBOUNCETABLE                       STD_OFF
#define DEM_CFG_ISDEF_PASSTIMERCYCLESOFDEBOUNCETABLE                  STD_ON
#define DEM_CFG_ISDEF_PASSEDTHRESHOLDOFDEBOUNCETABLE                  STD_OFF
#define DEM_CFG_ISDEF_STORAGEOFDEBOUNCETABLE                          STD_ON
#define DEM_CFG_ISDEF_DTCSEVERITYOFDTCTABLE                           STD_ON
#define DEM_CFG_ISDEF_FUNCTIONALUNITOFDTCTABLE                        STD_OFF
#define DEM_CFG_ISDEF_IMMEDIATENVSTORAGEOFDTCTABLE                    STD_OFF
#define DEM_CFG_ISDEF_UDSDTCOFDTCTABLE                                STD_OFF
#define DEM_CFG_ISDEF_INDEXOFENABLECONDITIONGROUPTABLE                STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEIND                    STD_ON
#define DEM_CFG_ISDEF_INITVALUEOFENABLECONDITIONINITTABLE             STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEINDENDIDXOFENABLECONDITIONTABLE STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEINDSTARTIDXOFENABLECONDITIONTABLE STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEINDUSEDOFENABLECONDITIONTABLE STD_ON
#define DEM_CFG_ISDEF_EVENTAVAILABLEDEFAULT                           STD_ON
#define DEM_CFG_ISDEF_EVENTAVAILABLEINVARIANT                         STD_ON
#define DEM_CFG_ISDEF_AGINGALLOWEDOFEVENTTABLE                        STD_ON
#define DEM_CFG_ISDEF_AGINGCYCLECOUNTERTHRESHOLDOFEVENTTABLE          STD_ON
#define DEM_CFG_ISDEF_AGINGCYCLEIDOFEVENTTABLE                        STD_OFF
#define DEM_CFG_ISDEF_DEBOUNCETABLEIDXOFEVENTTABLE                    STD_ON
#define DEM_CFG_ISDEF_DTCTABLEIDXOFEVENTTABLE                         STD_OFF
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEIDXOFEVENTTABLE        STD_ON
#define DEM_CFG_ISDEF_EVENTDESTINATIONOFEVENTTABLE                    STD_ON
#define DEM_CFG_ISDEF_EVENTFAILURECYCLECOUNTERTHRESHOLDOFEVENTTABLE   STD_ON
#define DEM_CFG_ISDEF_EVENTKINDOFEVENTTABLE                           STD_OFF
#define DEM_CFG_ISDEF_EVENTLATCHTFOFEVENTTABLE                        STD_ON
#define DEM_CFG_ISDEF_EVENTPRIORITYOFEVENTTABLE                       STD_ON
#define DEM_CFG_ISDEF_EVENTSIGNIFICANCEOFEVENTTABLE                   STD_ON
#define DEM_CFG_ISDEF_EXTENDEDDATATABLEIDXOFEVENTTABLE                STD_OFF
#define DEM_CFG_ISDEF_FREEZEFRAMETABLESTDFFIDXOFEVENTTABLE            STD_ON
#define DEM_CFG_ISDEF_HEALINGTARGETOFEVENTTABLE                       STD_ON
#define DEM_CFG_ISDEF_MASKEDBITSOFEVENTTABLE                          STD_ON
#define DEM_CFG_ISDEF_OPERATIONCYCLEIDOFEVENTTABLE                    STD_OFF
#define DEM_CFG_ISDEF_SATELLITEEVENTIDXOFEVENTTABLE                   STD_OFF
#define DEM_CFG_ISDEF_SATELLITEINFOIDXOFEVENTTABLE                    STD_ON
#define DEM_CFG_ISDEF_EVENTTABLEIND                                   STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEDR2COLLINDENDIDXOFEXTENDEDDATATABLE STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEDR2COLLINDSTARTIDXOFEXTENDEDDATATABLE STD_OFF
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEDR2COLLINDUSEDOFEXTENDEDDATATABLE STD_OFF
#define DEM_CFG_ISDEF_MAXRECORDSIZEOFEXTENDEDDATATABLE                STD_OFF
#define DEM_CFG_ISDEF_RECORDSIZEOFFREEZEFRAMETABLE                    STD_ON
#define DEM_CFG_ISDEF_RECORDSIZEUDSOFFREEZEFRAMETABLE                 STD_ON
#define DEM_CFG_ISDEF_DATAELEMENTTABLEIDXOFGENERALOBDINPUT            STD_ON
#define DEM_CFG_ISDEF_MEMORYBLOCKIDTOMEMORYENTRYID                    STD_OFF
#define DEM_CFG_ISDEF_MEMORYDATAPTR                                   STD_OFF
#define DEM_CFG_ISDEF_MEMORYDATASIZE                                  STD_OFF
#define DEM_CFG_ISDEF_MEMORYENTRY                                     STD_OFF
#define DEM_CFG_ISDEF_APPLICATIONIDOFSATELLITEINFO                    STD_ON
#define DEM_CFG_ISDEF_EVENTCOUNTOFSATELLITEINFO                       STD_ON
#define DEM_CFG_ISDEF_EVENTTABLEINDENDIDXOFSATELLITEINFO              STD_ON
#define DEM_CFG_ISDEF_EVENTTABLEINDSTARTIDXOFSATELLITEINFO            STD_ON
#define DEM_CFG_ISDEF_EVENTTABLEINDUSEDOFSATELLITEINFO                STD_ON
#define DEM_CFG_ISDEF_SATELLITEDATAOFSATELLITEINFO                    STD_ON
#define DEM_CFG_ISDEF_SATELLITESTATUSOFSATELLITEINFO                  STD_ON
#define DEM_CFG_ISDEF_ADMINDATAOFPCCONFIG                             STD_ON
#define DEM_CFG_ISDEF_CLEARDTCTABLEOFPCCONFIG                         STD_ON
#define DEM_CFG_ISDEF_CLIENTTABLEOFPCCONFIG                           STD_ON
#define DEM_CFG_ISDEF_COMMITBUFFEROFPCCONFIG                          STD_ON
#define DEM_CFG_ISDEF_CYCLEIDTABLEOFPCCONFIG                          STD_ON
#define DEM_CFG_ISDEF_DTCSELECTORTABLEOFPCCONFIG                      STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEEDR2COLLINDOFPCCONFIG        STD_ON
#define DEM_CFG_ISDEF_DATACOLLECTIONTABLEOFPCCONFIG                   STD_ON
#define DEM_CFG_ISDEF_DATAELEMENTTABLECOL2ELMTINDOFPCCONFIG           STD_ON
#define DEM_CFG_ISDEF_DATAELEMENTTABLEOFPCCONFIG                      STD_ON
#define DEM_CFG_ISDEF_DEBOUNCETABLEOFPCCONFIG                         STD_ON
#define DEM_CFG_ISDEF_DTCTABLEOFPCCONFIG                              STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPCOUNTEROFPCCONFIG           STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPSTATEOFPCCONFIG             STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEINDOFPCCONFIG          STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONGROUPTABLEOFPCCONFIG             STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONINITTABLEOFPCCONFIG              STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONSTATEOFPCCONFIG                  STD_ON
#define DEM_CFG_ISDEF_ENABLECONDITIONTABLEOFPCCONFIG                  STD_ON
#define DEM_CFG_ISDEF_EVENTAVAILABLEDEFAULTOFPCCONFIG                 STD_ON
#define DEM_CFG_ISDEF_EVENTAVAILABLEINVARIANTOFPCCONFIG               STD_ON
#define DEM_CFG_ISDEF_EVENTDEBOUNCEVALUEOFPCCONFIG                    STD_ON
#define DEM_CFG_ISDEF_EVENTINTERNALSTATUSOFPCCONFIG                   STD_ON
#define DEM_CFG_ISDEF_EVENTTABLEINDOFPCCONFIG                         STD_ON
#define DEM_CFG_ISDEF_EVENTTABLEOFPCCONFIG                            STD_ON
#define DEM_CFG_ISDEF_EXTENDEDDATATABLEOFPCCONFIG                     STD_ON
#define DEM_CFG_ISDEF_FILTERINFOTABLEOFPCCONFIG                       STD_ON
#define DEM_CFG_ISDEF_FILTERREPORTEDEVENTSOFPCCONFIG                  STD_ON
#define DEM_CFG_ISDEF_FREEZEFRAMEITERATORTABLEOFPCCONFIG              STD_ON
#define DEM_CFG_ISDEF_FREEZEFRAMETABLEOFPCCONFIG                      STD_ON
#define DEM_CFG_ISDEF_GENERALOBDINPUTOFPCCONFIG                       STD_ON
#define DEM_CFG_ISDEF_MEMORYBLOCKIDTOMEMORYENTRYIDOFPCCONFIG          STD_ON
#define DEM_CFG_ISDEF_MEMORYCOMMITNUMBEROFPCCONFIG                    STD_ON
#define DEM_CFG_ISDEF_MEMORYDATAPTROFPCCONFIG                         STD_ON
#define DEM_CFG_ISDEF_MEMORYDATASIZEOFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_MEMORYENTRYINITOFPCCONFIG                       STD_ON
#define DEM_CFG_ISDEF_MEMORYENTRYOFPCCONFIG                           STD_ON
#define DEM_CFG_ISDEF_MEMORYSTATUSOFPCCONFIG                          STD_ON
#define DEM_CFG_ISDEF_PRIMARYCHRONOLOGYOFPCCONFIG                     STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_0OFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_10OFPCCONFIG                       STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_11OFPCCONFIG                       STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_12OFPCCONFIG                       STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_13OFPCCONFIG                       STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_14OFPCCONFIG                       STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_15OFPCCONFIG                       STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_16OFPCCONFIG                       STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_17OFPCCONFIG                       STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_1OFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_2OFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_3OFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_4OFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_5OFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_6OFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_7OFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_8OFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_PRIMARYENTRY_9OFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_READOUTBUFFEROFPCCONFIG                         STD_ON
#define DEM_CFG_ISDEF_REPORTEDEVENTSOFFILTEROFPCCONFIG                STD_ON
#define DEM_CFG_ISDEF_SATELLITEINFO0OFPCCONFIG                        STD_ON
#define DEM_CFG_ISDEF_SATELLITEINFOOFPCCONFIG                         STD_ON
#define DEM_CFG_ISDEF_STATUSDATAOFPCCONFIG                            STD_ON
#define DEM_CFG_ISDEF_TIMESERIESENTRYINITOFPCCONFIG                   STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCEqualsAlwaysToDefines  Dem_Cfg Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define DEM_CFG_EQ2_CLEARDTCINDEXOFCLIENTTABLE                        0u
#define DEM_CFG_EQ2_FILTERINDEXOFCLIENTTABLE                          0u
#define DEM_CFG_EQ2_FREEZEFRAMEITERATORINDEXOFCLIENTTABLE             0u
#define DEM_CFG_EQ2_READOUTBUFFERINDEXOFCLIENTTABLE                   0u
#define DEM_CFG_EQ2_SELECTORINDEXOFCLIENTTABLE                        0u
#define DEM_CFG_EQ2_OPCYCLETYPEOFCYCLEIDTABLE                         
#define DEM_CFG_EQ2_USEDFORAGINGOFCYCLEIDTABLE                        
#define DEM_CFG_EQ2_COLLECTIONSIZEOFDATACOLLECTIONTABLE               
#define DEM_CFG_EQ2_DATAELEMENTTABLECOL2ELMTINDENDIDXOFDATACOLLECTIONTABLE 
#define DEM_CFG_EQ2_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE 
#define DEM_CFG_EQ2_DATAELEMENTTABLECOL2ELMTINDUSEDOFDATACOLLECTIONTABLE 
#define DEM_CFG_EQ2_IDNUMBEROFDATACOLLECTIONTABLE                     
#define DEM_CFG_EQ2_MASKEDBITSOFDATACOLLECTIONTABLE                   
#define DEM_CFG_EQ2_STORAGEKINDOFDATACOLLECTIONTABLE                  
#define DEM_CFG_EQ2_UPDATEOFDATACOLLECTIONTABLE                       
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEDR2COLLIND                    
#define DEM_CFG_EQ2_DATAISSTOREDINNVOFDATAELEMENTTABLE                
#define DEM_CFG_EQ2_ELEMENTKINDOFDATAELEMENTTABLE                     
#define DEM_CFG_EQ2_ELEMENTSIZEOFDATAELEMENTTABLE                     
#define DEM_CFG_EQ2_READDATAFUNCOFDATAELEMENTTABLE                    
#define DEM_CFG_EQ2_DATAELEMENTTABLECOL2ELMTIND                       
#define DEM_CFG_EQ2_DEBOUNCECONTINUOUSOFDEBOUNCETABLE                 FALSE
#define DEM_CFG_EQ2_DECREMENTSTEPSIZEOFDEBOUNCETABLE                  
#define DEM_CFG_EQ2_EVENTDEBOUNCEALGORITHMOFDEBOUNCETABLE             
#define DEM_CFG_EQ2_EVENTDEBOUNCEBEHAVIOROFDEBOUNCETABLE              FALSE
#define DEM_CFG_EQ2_FAILTIMERCYCLESOFDEBOUNCETABLE                    0
#define DEM_CFG_EQ2_FAILEDTHRESHOLDOFDEBOUNCETABLE                    
#define DEM_CFG_EQ2_INCREMENTSTEPSIZEOFDEBOUNCETABLE                  
#define DEM_CFG_EQ2_JUMPDOWNOFDEBOUNCETABLE                           
#define DEM_CFG_EQ2_JUMPDOWNVALUEOFDEBOUNCETABLE                      0
#define DEM_CFG_EQ2_JUMPUPOFDEBOUNCETABLE                             
#define DEM_CFG_EQ2_JUMPUPVALUEOFDEBOUNCETABLE                        0
#define DEM_CFG_EQ2_MASKEDBITSOFDEBOUNCETABLE                         
#define DEM_CFG_EQ2_PASSTIMERCYCLESOFDEBOUNCETABLE                    0
#define DEM_CFG_EQ2_PASSEDTHRESHOLDOFDEBOUNCETABLE                    
#define DEM_CFG_EQ2_STORAGEOFDEBOUNCETABLE                            FALSE
#define DEM_CFG_EQ2_DTCSEVERITYOFDTCTABLE                             0u
#define DEM_CFG_EQ2_FUNCTIONALUNITOFDTCTABLE                          
#define DEM_CFG_EQ2_IMMEDIATENVSTORAGEOFDTCTABLE                      
#define DEM_CFG_EQ2_UDSDTCOFDTCTABLE                                  
#define DEM_CFG_EQ2_INDEXOFENABLECONDITIONGROUPTABLE                  0u
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEIND                      0u
#define DEM_CFG_EQ2_INITVALUEOFENABLECONDITIONINITTABLE               1u
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEINDENDIDXOFENABLECONDITIONTABLE 1u
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEINDSTARTIDXOFENABLECONDITIONTABLE 0u
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEINDUSEDOFENABLECONDITIONTABLE TRUE
#define DEM_CFG_EQ2_EVENTAVAILABLEDEFAULT                             TRUE
#define DEM_CFG_EQ2_EVENTAVAILABLEINVARIANT                           TRUE
#define DEM_CFG_EQ2_AGINGALLOWEDOFEVENTTABLE                          FALSE
#define DEM_CFG_EQ2_AGINGCYCLECOUNTERTHRESHOLDOFEVENTTABLE            255u
#define DEM_CFG_EQ2_AGINGCYCLEIDOFEVENTTABLE                          
#define DEM_CFG_EQ2_DEBOUNCETABLEIDXOFEVENTTABLE                      0u
#define DEM_CFG_EQ2_DTCTABLEIDXOFEVENTTABLE                           
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEIDXOFEVENTTABLE          0u
#define DEM_CFG_EQ2_EVENTDESTINATIONOFEVENTTABLE                      DEM_CFG_MEMORYID_PRIMARY
#define DEM_CFG_EQ2_EVENTFAILURECYCLECOUNTERTHRESHOLDOFEVENTTABLE     0u
#define DEM_CFG_EQ2_EVENTKINDOFEVENTTABLE                             
#define DEM_CFG_EQ2_EVENTLATCHTFOFEVENTTABLE                          FALSE
#define DEM_CFG_EQ2_EVENTPRIORITYOFEVENTTABLE                         2u
#define DEM_CFG_EQ2_EVENTSIGNIFICANCEOFEVENTTABLE                     DEM_CFG_DEM_EVENT_SIGNIFICANCE_FAULT_EVENTSIGNIFICANCEOFEVENTTABLE
#define DEM_CFG_EQ2_EXTENDEDDATATABLEIDXOFEVENTTABLE                  
#define DEM_CFG_EQ2_FREEZEFRAMETABLESTDFFIDXOFEVENTTABLE              0u
#define DEM_CFG_EQ2_HEALINGTARGETOFEVENTTABLE                         0u
#define DEM_CFG_EQ2_MASKEDBITSOFEVENTTABLE                            0x00u
#define DEM_CFG_EQ2_OPERATIONCYCLEIDOFEVENTTABLE                      
#define DEM_CFG_EQ2_SATELLITEEVENTIDXOFEVENTTABLE                     
#define DEM_CFG_EQ2_SATELLITEINFOIDXOFEVENTTABLE                      0u
#define DEM_CFG_EQ2_EVENTTABLEIND                                     
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEDR2COLLINDENDIDXOFEXTENDEDDATATABLE 
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEDR2COLLINDSTARTIDXOFEXTENDEDDATATABLE 
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEDR2COLLINDUSEDOFEXTENDEDDATATABLE 
#define DEM_CFG_EQ2_MAXRECORDSIZEOFEXTENDEDDATATABLE                  
#define DEM_CFG_EQ2_RECORDSIZEOFFREEZEFRAMETABLE                      0u
#define DEM_CFG_EQ2_RECORDSIZEUDSOFFREEZEFRAMETABLE                   0u
#define DEM_CFG_EQ2_DATAELEMENTTABLEIDXOFGENERALOBDINPUT              0u
#define DEM_CFG_EQ2_MEMORYBLOCKIDTOMEMORYENTRYID                      
#define DEM_CFG_EQ2_MEMORYDATAPTR                                     
#define DEM_CFG_EQ2_MEMORYDATASIZE                                    
#define DEM_CFG_EQ2_MEMORYENTRY                                       
#define DEM_CFG_EQ2_APPLICATIONIDOFSATELLITEINFO                      0
#define DEM_CFG_EQ2_EVENTCOUNTOFSATELLITEINFO                         22u
#define DEM_CFG_EQ2_EVENTTABLEINDENDIDXOFSATELLITEINFO                22u
#define DEM_CFG_EQ2_EVENTTABLEINDSTARTIDXOFSATELLITEINFO              0u
#define DEM_CFG_EQ2_EVENTTABLEINDUSEDOFSATELLITEINFO                  TRUE
#define DEM_CFG_EQ2_SATELLITEDATAOFSATELLITEINFO                      &Dem_Cfg_GetSatelliteInfo0().SatelliteData[0]
#define DEM_CFG_EQ2_SATELLITESTATUSOFSATELLITEINFO                    &Dem_Cfg_GetSatelliteInfo0().SatelliteStatus
#define DEM_CFG_EQ2_ADMINDATAOFPCCONFIG                               Dem_Cfg_AdminData
#define DEM_CFG_EQ2_CLEARDTCTABLEOFPCCONFIG                           Dem_Cfg_ClearDTCTable
#define DEM_CFG_EQ2_CLIENTTABLEOFPCCONFIG                             Dem_Cfg_ClientTable
#define DEM_CFG_EQ2_COMMITBUFFEROFPCCONFIG                            Dem_Cfg_CommitBuffer
#define DEM_CFG_EQ2_CYCLEIDTABLEOFPCCONFIG                            Dem_Cfg_CycleIdTable
#define DEM_CFG_EQ2_DTCSELECTORTABLEOFPCCONFIG                        Dem_Cfg_DTCSelectorTable
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEEDR2COLLINDOFPCCONFIG          Dem_Cfg_DataCollectionTableEdr2CollInd
#define DEM_CFG_EQ2_DATACOLLECTIONTABLEOFPCCONFIG                     Dem_Cfg_DataCollectionTable
#define DEM_CFG_EQ2_DATAELEMENTTABLECOL2ELMTINDOFPCCONFIG             Dem_Cfg_DataElementTableCol2ElmtInd
#define DEM_CFG_EQ2_DATAELEMENTTABLEOFPCCONFIG                        Dem_Cfg_DataElementTable
#define DEM_CFG_EQ2_DEBOUNCETABLEOFPCCONFIG                           Dem_Cfg_DebounceTable
#define DEM_CFG_EQ2_DTCTABLEOFPCCONFIG                                Dem_Cfg_DtcTable
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPCOUNTEROFPCCONFIG             Dem_Cfg_EnableConditionGroupCounter
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPSTATEOFPCCONFIG               Dem_Cfg_EnableConditionGroupState
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEINDOFPCCONFIG            Dem_Cfg_EnableConditionGroupTableInd
#define DEM_CFG_EQ2_ENABLECONDITIONGROUPTABLEOFPCCONFIG               Dem_Cfg_EnableConditionGroupTable
#define DEM_CFG_EQ2_ENABLECONDITIONINITTABLEOFPCCONFIG                Dem_Cfg_EnableConditionInitTable
#define DEM_CFG_EQ2_ENABLECONDITIONSTATEOFPCCONFIG                    Dem_Cfg_EnableConditionState
#define DEM_CFG_EQ2_ENABLECONDITIONTABLEOFPCCONFIG                    Dem_Cfg_EnableConditionTable
#define DEM_CFG_EQ2_EVENTAVAILABLEDEFAULTOFPCCONFIG                   Dem_Cfg_EventAvailableDefault
#define DEM_CFG_EQ2_EVENTAVAILABLEINVARIANTOFPCCONFIG                 Dem_Cfg_EventAvailableInVariant
#define DEM_CFG_EQ2_EVENTDEBOUNCEVALUEOFPCCONFIG                      Dem_Cfg_EventDebounceValue
#define DEM_CFG_EQ2_EVENTINTERNALSTATUSOFPCCONFIG                     Dem_Cfg_EventInternalStatus
#define DEM_CFG_EQ2_EVENTTABLEINDOFPCCONFIG                           Dem_Cfg_EventTableInd
#define DEM_CFG_EQ2_EVENTTABLEOFPCCONFIG                              Dem_Cfg_EventTable
#define DEM_CFG_EQ2_EXTENDEDDATATABLEOFPCCONFIG                       Dem_Cfg_ExtendedDataTable
#define DEM_CFG_EQ2_FILTERINFOTABLEOFPCCONFIG                         Dem_Cfg_FilterInfoTable
#define DEM_CFG_EQ2_FILTERREPORTEDEVENTSOFPCCONFIG                    Dem_Cfg_FilterReportedEvents
#define DEM_CFG_EQ2_FREEZEFRAMEITERATORTABLEOFPCCONFIG                Dem_Cfg_FreezeFrameIteratorTable
#define DEM_CFG_EQ2_FREEZEFRAMETABLEOFPCCONFIG                        Dem_Cfg_FreezeFrameTable
#define DEM_CFG_EQ2_GENERALOBDINPUTOFPCCONFIG                         Dem_Cfg_GeneralObdInput
#define DEM_CFG_EQ2_MEMORYBLOCKIDTOMEMORYENTRYIDOFPCCONFIG            Dem_Cfg_MemoryBlockIdToMemoryEntryId
#define DEM_CFG_EQ2_MEMORYCOMMITNUMBEROFPCCONFIG                      Dem_Cfg_MemoryCommitNumber
#define DEM_CFG_EQ2_MEMORYDATAPTROFPCCONFIG                           Dem_Cfg_MemoryDataPtr
#define DEM_CFG_EQ2_MEMORYDATASIZEOFPCCONFIG                          Dem_Cfg_MemoryDataSize
#define DEM_CFG_EQ2_MEMORYENTRYINITOFPCCONFIG                         Dem_Cfg_MemoryEntryInit
#define DEM_CFG_EQ2_MEMORYENTRYOFPCCONFIG                             Dem_Cfg_MemoryEntry
#define DEM_CFG_EQ2_MEMORYSTATUSOFPCCONFIG                            Dem_Cfg_MemoryStatus
#define DEM_CFG_EQ2_PRIMARYCHRONOLOGYOFPCCONFIG                       Dem_Cfg_PrimaryChronology
#define DEM_CFG_EQ2_PRIMARYENTRY_0OFPCCONFIG                          Dem_Cfg_PrimaryEntry_0
#define DEM_CFG_EQ2_PRIMARYENTRY_10OFPCCONFIG                         Dem_Cfg_PrimaryEntry_10
#define DEM_CFG_EQ2_PRIMARYENTRY_11OFPCCONFIG                         Dem_Cfg_PrimaryEntry_11
#define DEM_CFG_EQ2_PRIMARYENTRY_12OFPCCONFIG                         Dem_Cfg_PrimaryEntry_12
#define DEM_CFG_EQ2_PRIMARYENTRY_13OFPCCONFIG                         Dem_Cfg_PrimaryEntry_13
#define DEM_CFG_EQ2_PRIMARYENTRY_14OFPCCONFIG                         Dem_Cfg_PrimaryEntry_14
#define DEM_CFG_EQ2_PRIMARYENTRY_15OFPCCONFIG                         Dem_Cfg_PrimaryEntry_15
#define DEM_CFG_EQ2_PRIMARYENTRY_16OFPCCONFIG                         Dem_Cfg_PrimaryEntry_16
#define DEM_CFG_EQ2_PRIMARYENTRY_17OFPCCONFIG                         Dem_Cfg_PrimaryEntry_17
#define DEM_CFG_EQ2_PRIMARYENTRY_1OFPCCONFIG                          Dem_Cfg_PrimaryEntry_1
#define DEM_CFG_EQ2_PRIMARYENTRY_2OFPCCONFIG                          Dem_Cfg_PrimaryEntry_2
#define DEM_CFG_EQ2_PRIMARYENTRY_3OFPCCONFIG                          Dem_Cfg_PrimaryEntry_3
#define DEM_CFG_EQ2_PRIMARYENTRY_4OFPCCONFIG                          Dem_Cfg_PrimaryEntry_4
#define DEM_CFG_EQ2_PRIMARYENTRY_5OFPCCONFIG                          Dem_Cfg_PrimaryEntry_5
#define DEM_CFG_EQ2_PRIMARYENTRY_6OFPCCONFIG                          Dem_Cfg_PrimaryEntry_6
#define DEM_CFG_EQ2_PRIMARYENTRY_7OFPCCONFIG                          Dem_Cfg_PrimaryEntry_7
#define DEM_CFG_EQ2_PRIMARYENTRY_8OFPCCONFIG                          Dem_Cfg_PrimaryEntry_8
#define DEM_CFG_EQ2_PRIMARYENTRY_9OFPCCONFIG                          Dem_Cfg_PrimaryEntry_9
#define DEM_CFG_EQ2_READOUTBUFFEROFPCCONFIG                           Dem_Cfg_ReadoutBuffer
#define DEM_CFG_EQ2_REPORTEDEVENTSOFFILTEROFPCCONFIG                  Dem_Cfg_ReportedEventsOfFilter
#define DEM_CFG_EQ2_SATELLITEINFO0OFPCCONFIG                          Dem_Cfg_SatelliteInfo0
#define DEM_CFG_EQ2_SATELLITEINFOOFPCCONFIG                           Dem_Cfg_SatelliteInfo
#define DEM_CFG_EQ2_STATUSDATAOFPCCONFIG                              Dem_Cfg_StatusData
#define DEM_CFG_EQ2_TIMESERIESENTRYINITOFPCCONFIG                     Dem_Cfg_TimeSeriesEntryInit
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCSymbolicInitializationPointers  Dem_Cfg Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define Dem_Config_Ptr                                                NULL_PTR  /**< symbolic identifier which shall be used to initialize 'Dem' */
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCInitializationSymbols  Dem_Cfg Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define Dem_Config                                                    NULL_PTR  /**< symbolic identifier which could be used to initialize 'Dem */
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGeneral  Dem_Cfg General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define DEM_CFG_CHECK_INIT_POINTER                                    STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define DEM_CFG_FINAL_MAGIC_NUMBER                                    0x361Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of Dem */
#define DEM_CFG_INDIVIDUAL_POSTBUILD                                  STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'Dem' is not configured to be postbuild capable. */
#define DEM_CFG_INIT_DATA                                             DEM_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define DEM_CFG_INIT_DATA_HASH_CODE                                   -504453132L  /**< the precompile constant to validate the initialization structure at initialization time of Dem with a hashcode. The seed value is '0x361Eu' */
#define DEM_CFG_USE_ECUM_BSW_ERROR_HOOK                               STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define DEM_CFG_USE_INIT_POINTER                                      STD_OFF  /**< STD_ON if the init pointer Dem shall be used. */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  Dem_CfgLTDataSwitches  Dem_Cfg Data Switches  (LINK)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define DEM_LTCONFIG                                                  STD_OFF  /**< Deactivateable: 'Dem_LTConfig' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
/** 
  \}
*/ 


/*********************************************************************************************************************/


 /*  Invalid Indicator IDs  */ 
#define DEM_CFG_INDICATOR_INVALID                                     0u           /* Lowest, unused IndicatorID */ 
#define DEM_CFG_SPECIAL_INDICATOR_NONE                                255u         /* Always different from DEM_CFG_INDICATOR_INVALID */ 

 /*  Indicator global definitions  */ 
#define DEM_CFG_GLOBAL_INDICATOR_COUNT                                0u           /* Total number of configured Indicators */ 
#define DEM_G_NUMBER_SPECIAL_INDICATORS                               0u           /* Number of special indicators (i.e. only MIL, AWL, PL, RSL) */ 


 /*  Aging- and OperationCycle IDs [symbolic name value]  */ 
#define DemConf_DemOperationCycle_IgnitionCycle                       0u 
#define DemConf_DemOperationCycle_OBDDrivingCycle                     1u 
#define DemConf_DemOperationCycle_PowerCycle                          2u 
#define DemConf_DemOperationCycle_WarmUpCycle                         3u 

 /*  Global, cycle related values  */ 
#define DEM_CFG_GLOBAL_CYCLE_COUNT                                    4u           /* Total number of configured (operation and aging) cycles. */ 
#define DEM_CFG_GLOBAL_OBD_DRIVING_CYCLE_ID                           1u           /* Cycle ID of the DemOperationCycleType 'DEM_OPCYC_OBD_DCY'. */ 
#define DEM_CFG_GLOBAL_WARMUP_CYCLE_ID                                3u           /* Cycle ID of the DemOperationCycleType 'DEM_OPCYC_WARMUP'. */ 


 /*  Dem general defines  */ 
#define DEM_CFG_BSW_ERROR_BUFFER_SIZE                                 0u                                /* /Dem/DemGeneral/DemBswErrorBufferSize */ 
#define DEM_CFG_GLOBALCBKCONTROLDTCSETTING_FUNC                       NULL_PTR                          /* DEM_CFG_NOTIFY_CONTROL_DTC_SETTING==STD_OFF */ 
#define DEM_CFG_GLOBALCBKDATA_FUNC                                    NULL_PTR                          /* No ClientServerInterface GeneralCallbackEventDataChanged, DEM_CFG_NOTIFY_GENERAL_DATA==STD_OFF */ 
#define DEM_CFG_GLOBALCBKSTATUS_FUNC                                  NULL_PTR                          /* No ClientServerInterface GeneralCallbackEventUdsStatusChanged, DEM_CFG_NOTIFY_GENERAL_STATUS==STD_OFF */ 
#define DEM_CFG_GLOBALTRIGGERONMONITORSTATUS_FUNC                     NULL_PTR                          /* No or empty /Dem/DemGeneral/DemGeneralCallbackMonitorStatusChangedFnc parameter, DEM_CFG_NOTIFY_GENERAL_MONITORSTATUS_CHANGED==STD_OFF */ 
#define DEM_CFG_GLOBAL_CLEAR_DTC_RUNTIME_LIMIT                        22u                               /* not configured, here substituted by number of events (incl. event #0) */ 
#define DEM_CFG_GLOBAL_DEBOUNCE_STORAGE_EVENT_COUNT                   0u                                /* Number of events with .../DemEventClass/DemDebounceAlgorithClass/DemDebounceCounterBased/DemDebounceCounterStorage == TRUE */ 
#define DEM_CFG_GLOBAL_DTC_FORMAT                                     DEM_DTC_TRANSLATION_ISO14229_1    /* /Dem/DemGeneral/DemTypeOfDTCSupported */ 
#define DEM_CFG_GLOBAL_FREEZEFRAME_SIZE                               0u                                /* /Dem/DemGeneral/DemMaxNumberEventEntryOBDFreezeFrame */ 
#define DEM_CFG_GLOBAL_MIRROR_SIZE                                    0u                                /* /Dem/DemGeneral/DemMaxNumberEventEntryMirror */ 
#define DEM_CFG_GLOBAL_NV_STORAGE_LIMIT                               0u                                /* /Dem/DemGeneral/DemImmediateNvStorageLimit, 0: no limit configured */ 
#define DEM_CFG_GLOBAL_PERMANENT_SIZE                                 0u                                /* /Dem/DemGeneral/DemMaxNumberEventEntryPermanent */ 
#define DEM_CFG_GLOBAL_PRESTORED_FF_SIZE                              0u                                /* /Dem/DemGeneral/DemMaxNumberPrestoredFF, see Dem_Cfg_GlobalPrestorageSize() */ 
#define DEM_CFG_GLOBAL_PRIMARY_SIZE                                   18u                               /* /Dem/DemGeneral/DemMaxNumberEventEntryPrimary */ 
#define DEM_CFG_GLOBAL_SECONDARY_SIZE                                 0u                                /* /Dem/DemGeneral/DemMaxNumberEventEntrySecondary */ 
#define DEM_CFG_GLOBAL_STATUS_MASK                                    0x79u                             /* /Dem/DemGeneral/DemDtcStatusAvailabilityMask */ 
#define DEM_CFG_GLOBAL_TASK_MS                                        10u                               /* /Dem/DemGeneral/DemTaskTime in [ms]. See also macro DEM_CFG_TASK_TIME for exact float value */ 
#define DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE                      0u                                /* /Dem/DemGeneral/DemMaxNumberTimeSeriesSnapshots */ 
#define DEM_CFG_J1939_NODE_INVALID                                    0u                                /* Invalid NmNode index (Dem internal) */ 
#define DEM_CFG_MAX_NUMBER_PERMANENT_CHRONOLOGY                       1u                                /* /Dem/DemGeneral/DemGeneralOBD/DemOBDPermanentChronologyMaxNumberEvents */ 
#define DEM_CFG_OEMCBKGETCURRENTODOMETER_FUNC                         NULL_PTR                          /* unused */ 
#define DEM_CFG_OEMCBKGETEXTERNALTESTERSTATUS_FUNC                    NULL_PTR                          /* unused */ 
#define DEM_CFG_RATIOINDEX_INVALID                                    255u                              /* Internal use: no OBD RatioId configured */ 
#define DEM_CFG_SIZEOF_MAX_DATA_VALUE_TYPE                            6u                                /* sizeof(Dem_MaxDataValueType) - typedef is generated by the RTE into Rte_Type.h */ 
#define DEM_CFG_TASK_TIME                                             10.0                              /* /Dem/DemGeneral/DemTaskTime in [ms]. See also macro DEM_CFG_GLOBAL_TASK_MS for integer value. */ 
#define DEM_G_GLOBAL_PRESTORED_EVENT_COUNT                            0u                                /* Number of events with DemEventClass/DemFFPrestorageSupported == TRUE, see Dem_Cfg_GlobalPrestorageEventCount() */ 
#define DEM_G_MAX_NUMBER_J1939_NODES                                  1u                                /* Number of different J1939Nm node targets (=J1939NmNode) referenced via /Dem/DemConfigSet/DemJ1939NodeAddress/DemJ1939NmNodeRef - plus 1 when there are DTCs without a DemJ1939DTC_NodeAddressRef value. */ 
#define DEM_G_NUMBER_OF_EVENTS                                        22u                               /* Total number of DemEventParameter, incl. event #0 */ 
#define DEM_G_NUMBER_OF_RATIO_IDS                                     0u                                /* Number of OBD RatioIds (incl. ID 0, internally used for global values) */ 


 /*  Support for optimized routines of Vector DCM - Extended Data records  */ 
#define DEM_DCM_NUM_EXTDATA_RECID                                     5u 
#define DEM_DCM_LST_EXTDATA_RECID                                     0x01u, 0x02u, 0x03u, 0x04u, 0x05u 

 /*  Event IDs [symbolic name value] - sorted by name.
     See Dem_Cfg_EventTable[] for this list sorted by Ids.  */ 
#define DemConf_DemEventParameter_A4814BDemEventParameter_003                                 4u 
#define DemConf_DemEventParameter_A48249DemEventParameter_004                                 5u 
#define DemConf_DemEventParameter_A48368DemEventParameter_005                                 6u 
#define DemConf_DemEventParameter_A48468DemEventParameter_006                                 7u 
#define DemConf_DemEventParameter_AutoCreatedDemEvent_ECUM_E_ALL_RUN_REQUESTS_KILLED          18u 
#define DemConf_DemEventParameter_AutoCreatedDemEvent_ECUM_E_CONFIGURATION_DATA_INCONSISTENT  19u 
#define DemConf_DemEventParameter_AutoCreatedDemEvent_ECUM_E_IMPROPER_CALLER                  20u 
#define DemConf_DemEventParameter_DEM_EVENT_StartApplication                                  21u 
#define DemConf_DemEventParameter_E70200DemEventParameter                                     1u 
#define DemConf_DemEventParameter_E70568DemEventParameter_007                                 8u 
#define DemConf_DemEventParameter_E70600DemEventParameter_008                                 9u 
#define DemConf_DemEventParameter_E70887DemEventParameter_009                                 10u 
#define DemConf_DemEventParameter_E70987DemEventParameter_010                                 11u 
#define DemConf_DemEventParameter_E70A87DemEventParameter_011                                 12u 
#define DemConf_DemEventParameter_E70B29DemEventParameter_012                                 13u 
#define DemConf_DemEventParameter_E70C29DemEventParameter_013                                 14u 
#define DemConf_DemEventParameter_E70D29DemEventParameter_014                                 15u 
#define DemConf_DemEventParameter_E70E87DemEventParameter_015                                 16u 
#define DemConf_DemEventParameter_E70F87DemEventParameter_016                                 17u 
#define DemConf_DemEventParameter_F00616DemEventParameter_001                                 2u 
#define DemConf_DemEventParameter_F00617DemEventParameter_002                                 3u 




 /*  Existance of iterator interfaces  */ 
#define DEM_CFG_HAVEITER_CLEARDTCNOTIFICATIONFINISH                   STD_OFF      /* Deactivated due DEM_CFG_CLEARDTCNOTIFICATIONFINISHTABLE==STD_OFF */ 
#define DEM_CFG_HAVEITER_CLEARDTCNOTIFICATIONSTART                    STD_OFF      /* Deactivated due DEM_CFG_CLEARDTCNOTIFICATIONSTARTTABLE==STD_OFF */ 
#define DEM_CFG_HAVEITER_COMBINEDGROUP                                STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_TYPE1_COMBINATION==STD_OFF */ 
#define DEM_CFG_HAVEITER_DEBOUNCEHIRES                                STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_DEBOUNCE_TIME_HR==STD_OFF */ 
#define DEM_CFG_HAVEITER_DEBOUNCELORES                                STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR==STD_OFF */ 
#define DEM_CFG_HAVEITER_DIDDATA                                      STD_ON 
#define DEM_CFG_HAVEITER_ENABLECONDITIONGROUPS                        STD_ON 
#define DEM_CFG_HAVEITER_EVENTCBKINITFUNC                             STD_OFF      /* Deactivated due DEM_CFG_INITMONLISTFORFUNC==STD_OFF */ 
#define DEM_CFG_HAVEITER_EVENTCBKSTATUS                               STD_OFF      /* Deactivated due DEM_CFG_EVENTSTATUSCHANGED==STD_OFF */ 
#define DEM_CFG_HAVEITER_EVENTDID                                     STD_ON 
#define DEM_CFG_HAVEITER_EVENTEREC                                    STD_ON 
#define DEM_CFG_HAVEITER_EVENTIDLIST                                  STD_ON 
#define DEM_CFG_HAVEITER_EVENTINDICATOR                               STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_USER_INDICATORS==STD_OFF */ 
#define DEM_CFG_HAVEITER_EVENTJ1939NODE                               STD_OFF      /* Deactivated due (DEM_CFG_HAS_J1939_NODE == STD_OFF) */ 
#define DEM_CFG_HAVEITER_EVENTOBDDID                                  STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_WWHOBD==STD_OFF */ 
#define DEM_CFG_HAVEITER_EVENTSPN                                     STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_J1939==STD_OFF */ 
#define DEM_CFG_HAVEITER_EVENTSREC                                    STD_OFF      /* Deactivated due DEM_CFG_FREEZEFRAMENUMTABLE==STD_OFF */ 
#define DEM_CFG_HAVEITER_GLOBALCBKDTC                                 STD_OFF      /* Deactivated due DEM_CFG_CALLBACKDTCSTATUSCHANGED==STD_OFF */ 
#define DEM_CFG_HAVEITER_GLOBALCBKJ1939DTC                            STD_OFF      /* Deactivated due DEM_CFG_CALLBACKJ1939DTCSTATUSCHANGED==STD_OFF */ 
#define DEM_CFG_HAVEITER_GLOBALPID                                    STD_ON 
#define DEM_CFG_HAVEITER_OBDFIMFID                                    STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_IUMPR==STD_OFF */ 
#define DEM_CFG_HAVEITER_OBDRATIOID                                   STD_OFF      /* Deactivated due DEM_CFG_SUPPORT_IUMPR==STD_OFF */ 
#define DEM_CFG_HAVEITER_STORAGECONDITIONGROUPS                       STD_OFF      /* Deactivated due (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF) */ 
#define DEM_CFG_HAVEITER_TIMESERIESDIDFAST                            STD_OFF      /* Deactivated due (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL || DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL || DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST || DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST) == STD_OFF */ 
#define DEM_CFG_HAVEITER_TIMESERIESDIDNORMAL                          STD_OFF      /* Deactivated due (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL || DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL || DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST || DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST) == STD_OFF */ 

 /*  Event global definitions  */ 
#define DEM_CFG_GLOBAL_DTC_COUNT                                      19u 
#define DEM_CFG_GLOBAL_MIRROR_FIRST                                   0u           /* Lowest EventID with DemEventDestination==DEM_DTC_ORIGIN_MIRROR_MEMORY, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_MIRROR_LAST                                    0u           /* Highest EventID with DemEventDestination==DEM_DTC_ORIGIN_MIRROR_MEMORY, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_PERMANENT_FIRST                                0u           /* Lowest EventID with EventDestination==DEM_CFG_MEMORYID_PERMANENT, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_PERMANENT_LAST                                 0u           /* Highest EventID with EventDestination==DEM_CFG_MEMORYID_PERMANENT, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_PRIMARY_FIRST                                  1u           /* Lowest EventID with DemEventDestination==DEM_DTC_ORIGIN_PRIMARY_MEMORY, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_PRIMARY_LAST                                   21u          /* Highest EventID with DemEventDestination==DEM_DTC_ORIGIN_PRIMARY_MEMORY, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_SECONDARY_FIRST                                0u           /* Lowest EventID with DemEventDestination==DEM_DTC_ORIGIN_SECONDARY_MEMORY, or 0 if no such destination is configured. */ 
#define DEM_CFG_GLOBAL_SECONDARY_LAST                                 0u           /* Highest EventID with DemEventDestination==DEM_DTC_ORIGIN_SECONDARY_MEMORY, or 0 if no such destination is configured. */ 


 /*  Timebased debouncing - timing constants  */ 
#define DEM_CFG_DEBOUNCE_LO_RES_TIMER_VALUE                           15u          /* Ticks of the low resolution timer, based on Dem_MasterMainFunction() call cycle [10.0ms]. Tick count here equals 150.0ms. */ 


 /*  StorageCondition global definitions  */ 
#define DEM_CFG_GLOBAL_STORAGE_COND_COUNT                             0u           /* (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_OFF) */ 

 /*  Satellite global definitions  */ 
#define DEM_CFG_GLOBAL_PARTITION_COUNT                                1u           /* Total number of different, referenced /Os/OsApplication containers (plus Application "0"). */ 
#define DEM_CFG_MASTER_APPLICATION_ID                                 0            /* no /Dem/DemGeneral/DemMasterOsApplicationRef configured */ 
#define DEM_SATELLITEINFO_0                                           0x00u        /* Index of partition "0" in SatelliteInfo[] table */ 


 /*  PID global definitions  */ 
#define DEM_CFG_GLOBAL_OBD_IIFFRAW_SIZE                               0u           /* Pure data size of OBD-II record. */ 
#define DEM_CFG_GLOBAL_OBD_IIFFUDS_SIZE                               2u           /* Data size of OBD-II record incl PID numbers (each 2B) plus RecordNumber (1B) plus RecordCount (1B). */ 

 /*  Defines for supporting A2L  */ 
#define DEM_A2L_MAX_NUMBER_PRIMEM_EXTRECORD                           5uL 
#define DEM_A2L_MAX_SIZE_PRIMEM_EXTRECORD                             6uL 
#define DEM_A2L_NUMBER_OF_EVENTS                                      22uL         /* incl. event #0 */ 
#define DEM_A2L_NUMBER_OF_MIL_GROUPS                                  0uL          /* number of DemMILGroup containers + 1 */ 
#define DEM_A2L_MAX_SIZE_STDENV_RECORD                                0uL          /* largest, configured StdEnvData */ 





 /*  NV block global definitions  */ 
#define DEM_CFG_EVENTAVAILABLEDATATYPE_SIZE                           3u           /* Number of elements in arraytype 'Dem_Cfg_EventAvailableDataType'. */ 
#define DEM_CFG_GLOBAL_NV_BLOCK_COUNT                                 20u          /* Number of NV blocks. */ 
#define DEM_CFG_GLOBAL_PROCESSORWORDS_PER_REPORTEDEVENTSTYPE          1u           /* Number of Dem_Com_ProcessorWordType elements in arraytype 'Dem_Cfg_ReportedEventsType'. */ 
#define DEM_CFG_MAX_J1939_EXP_FF_SIZE                                 0u           /* Data size of the largest configured J1939 FreezeFrame record. */ 
#define DEM_CFG_MAX_J1939_FF_SIZE                                     0u           /* Data size of the largest configured J1939 FreezeFrame record. */ 
#define DEM_CFG_MAX_NUMBER_AGED_DTCS                                  0u           /* Maximum number of aged DTCs (number of DTCs assigned to an ageable event). */ 
#define DEM_CFG_MAX_NUMBER_AGING_DTCS                                 0u           /* Maximum number of aging DTCs (number of DTCs assigned to an event). */ 
#define DEM_CFG_MAX_NUMBER_CONFIGURABLE_DTRS                          0u           /* Maximum number of configurable Dtrs (defined by the largest DemDtrId value, or with PostBuild-Loadable the value /Dem/DemGeneral/DemPostbuild/DemMaxNumberDtr). */ 
#define DEM_CFG_MAX_NUM_EXT_RECORDS                                   5u           /* Largest count of EDR records per event to be stored in ExtendedData[DEM_CFG_MAX_NUM_EXT_RECORDS][DEM_CFG_MAX_SIZE_EXT_RECORD] - ignore records with pure ROM data and/or data having own_variable. '1' if there are 0 records. */ 
#define DEM_CFG_MAX_NUM_SNAPSHOTS                                     1u           /* Largest count of FreezeFrame records per event to be stored in SnapshotData[DEM_CFG_MAX_NUM_SNAPSHOTS][DEM_CFG_MAX_SIZE_SNAPSHOT]. '1' if there are 0 records. */ 
#define DEM_CFG_MAX_SIZE_EXT_RECORD                                   6u           /* Data size of the largest EDR record to be stored in ExtendedData[DEM_CFG_MAX_NUM_EXT_RECORDS][DEM_CFG_MAX_SIZE_EXT_RECORD] or '1' if size is 0. */ 
#define DEM_CFG_MAX_SIZE_GLOBAL_SNAPSHOT                              1u           /* Data size of the global freeze frame record to be stored in GlobalSnapshotData[DEM_CFG_MAX_SIZE_GLOBAL_SNAPSHOT] or '1' if size is 0 or there is no global freeze frame. */ 
#define DEM_CFG_MAX_SIZE_OBDFREEZEFRAME                               0u           /* Data size of largest configured FreezeFrame 0 (OBD II) record. */ 
#define DEM_CFG_MAX_SIZE_SNAPSHOT                                     1u           /* Data size of the largest FreezeFrame record to be stored in SnapshotData[DEM_CFG_MAX_NUM_SNAPSHOTS][DEM_CFG_MAX_SIZE_SNAPSHOT] or '1' if size is 0 or there are 0 records. */ 
#define DEM_CFG_MAX_SIZE_WWHFREEZEFRAME                               1u           /* Data size of the largest WWH-OBD FreezeFrame record to be stored in ObdFreezeFrameData[DEM_CFG_MAX_SIZE_WWHFREEZEFRAME] or '1' if size is 0 or there are 0 records. */ 
#define DEM_CFG_MEMORY_ADMIN_INDEX                                    0u           /* Index into Dem_Cfg_MemoryBlockId[], Dem_Cfg_MemoryDataSize[], Dem_Cfg_MemoryDataPtr[] and other Memory*[] arrays. */ 
#define DEM_CFG_MEMORY_PRIMARY_INDEX                                  2u           /* Index into Dem_Cfg_MemoryBlockId[], Dem_Cfg_MemoryDataSize[], Dem_Cfg_MemoryDataPtr[] and other Memory*[] arrays. Buffer count: Dem_Cfg_GlobalPrimarySize() = 18 */ 
#define DEM_CFG_MEMORY_STATUS_INDEX                                   1u           /* Index into Dem_Cfg_MemoryBlockId[], Dem_Cfg_MemoryDataSize[], Dem_Cfg_MemoryDataPtr[] and other Memory*[] arrays. */ 



 /*  OBD global definitions  */ 
#define DEM_CFG_OBDACCELERATORPEDALINFORMATION_INDEX                  0u           /* not defined */ 
#define DEM_CFG_OBDAMBIENTPRESSURE_INDEX                              0u           /* not defined */ 
#define DEM_CFG_OBDAMBIENTTEMPERATURE_INDEX                           0u           /* not defined */ 
#define DEM_CFG_OBDDISTANCEINFORMATION_INDEX                          0u           /* not defined */ 
#define DEM_CFG_OBDENGINERUNTIME_INDEX                                0u           /* not defined */ 
#define DEM_CFG_OBDENGINESPEED_INDEX                                  0u           /* not defined */ 
#define DEM_CFG_OBDENGINETEMPERATURE_INDEX                            0u           /* not defined */ 
#define DEM_CFG_OBDPROGRAMMINGEVENT_INDEX                             0u           /* not defined */ 
#define DEM_CFG_OBDVEHICLESPEED_INDEX                                 0u           /* not defined */ 

 /*  EnableCondition IDs [symbolic name value]  */ 
#define DemConf_DemEnableCondition___Internal_ControlDtcSetting       0u 

 /*  EnableCondition global definitions  */ 
#define DEM_CFG_GLOBAL_ENABLE_COND_COUNT                              1u           /* (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON) or there are internal EnableConditions. */ 

 /*  Client IDs [symbolic name value]  */ 
#define DemConf_DemClient_DemClient                                   0u 

 /*  Client global definitions  */ 
#define DEM_CFG_CLEARDTC_INVALID                                      255u         /* Value used as invalid index in Dem_Cfg_ClientTable[] for the ClearDTCIndex - the Client has no ClearDTC filter. */ 
#define DEM_CFG_DTCSELECTOR_INVALID                                   255u         /* Value used as invalid index in Dem_Cfg_ClientTable[] for the SelectorIndex - the Client has no selector. */ 
#define DEM_CFG_FILTER_INVALID                                        255u         /* Value used as invalid index in Dem_Cfg_ClientTable[] for the FilterIndex - the Client has no filter. */ 
#define DEM_CFG_FREEZEFRAMEITERATOR_INVALID                           255u         /* Value used as invalid index in Dem_Cfg_ClientTable[] for the FreezeFrameIteratorIndex - the Client has no FreezeFrameIterator. */ 
#define DEM_CFG_GLOBAL_CLIENT_COUNT                                   1u           /* Total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_NMNODEID_INVALID                                      65535u       /* Value used in Dem_Cfg_ClientTable[] for a Client, that has no J1939NmNode configured in the J1939Dcm. */ 
#define DEM_CFG_NUMBER_OF_CLEARDTCS                                   1u           /* Currently equal to the total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_NUMBER_OF_DTCSELECTORS                                1u           /* Currently equal to the total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_NUMBER_OF_FILTER                                      1u           /* Currently equal to the total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_NUMBER_OF_FREEZEFRAMEITERATORS                        1u           /* Currently equal to the total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_NUMBER_OF_READOUTBUFFERS                              1u           /* Currently equal to the total number of configured /Dem/DemGeneral/DemClient containers. */ 
#define DEM_CFG_READOUTBUFFER_INVALID                                 255u         /* Value used as invalid index in Dem_Cfg_ClientTable[] for the ReadoutBufferIndex - the Client has no ReadoutBuffer. */ 




/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 MACROS_3453 */  /* MD_CSL_3453 */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  Dem_CfgPCGetConstantDuplicatedRootDataMacros  Dem_Cfg Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define Dem_Cfg_GetAdminDataOfPCConfig()                              Dem_Cfg_AdminData  /**< the pointer to Dem_Cfg_AdminData */
#define Dem_Cfg_GetClearDTCTableOfPCConfig()                          Dem_Cfg_ClearDTCTable  /**< the pointer to Dem_Cfg_ClearDTCTable */
#define Dem_Cfg_GetClientTableOfPCConfig()                            Dem_Cfg_ClientTable  /**< the pointer to Dem_Cfg_ClientTable */
#define Dem_Cfg_GetCommitBufferOfPCConfig()                           Dem_Cfg_CommitBuffer  /**< the pointer to Dem_Cfg_CommitBuffer */
#define Dem_Cfg_GetConfigurationIdOfPCConfig()                        0x1087u  /**< Magic constant derived from the configuration parameters /Dem/DemGeneral/DemCompiledConfigId and /Dem/DemGeneral/DemCompiledPostbuildCrc. Each value change is evidence to incompatible NV stored data and triggers a re-initialization of the NV data. */
#define Dem_Cfg_GetCycleIdTableOfPCConfig()                           Dem_Cfg_CycleIdTable  /**< the pointer to Dem_Cfg_CycleIdTable */
#define Dem_Cfg_GetDTCSelectorTableOfPCConfig()                       Dem_Cfg_DTCSelectorTable  /**< the pointer to Dem_Cfg_DTCSelectorTable */
#define Dem_Cfg_GetDataCollectionTableEdr2CollIndOfPCConfig()         Dem_Cfg_DataCollectionTableEdr2CollInd  /**< the pointer to Dem_Cfg_DataCollectionTableEdr2CollInd */
#define Dem_Cfg_GetDataCollectionTableOfPCConfig()                    Dem_Cfg_DataCollectionTable  /**< the pointer to Dem_Cfg_DataCollectionTable */
#define Dem_Cfg_GetDataElementTableCol2ElmtIndOfPCConfig()            Dem_Cfg_DataElementTableCol2ElmtInd  /**< the pointer to Dem_Cfg_DataElementTableCol2ElmtInd */
#define Dem_Cfg_GetDataElementTableOfPCConfig()                       Dem_Cfg_DataElementTable  /**< the pointer to Dem_Cfg_DataElementTable */
#define Dem_Cfg_GetDebounceTableOfPCConfig()                          Dem_Cfg_DebounceTable  /**< the pointer to Dem_Cfg_DebounceTable */
#define Dem_Cfg_GetDtcTableOfPCConfig()                               Dem_Cfg_DtcTable  /**< the pointer to Dem_Cfg_DtcTable */
#define Dem_Cfg_GetEnableConditionGroupCounterOfPCConfig()            Dem_Cfg_EnableConditionGroupCounter  /**< the pointer to Dem_Cfg_EnableConditionGroupCounter */
#define Dem_Cfg_GetEnableConditionGroupStateOfPCConfig()              Dem_Cfg_EnableConditionGroupState  /**< the pointer to Dem_Cfg_EnableConditionGroupState */
#define Dem_Cfg_GetEnableConditionGroupTableIndOfPCConfig()           Dem_Cfg_EnableConditionGroupTableInd  /**< the pointer to Dem_Cfg_EnableConditionGroupTableInd */
#define Dem_Cfg_GetEnableConditionGroupTableOfPCConfig()              Dem_Cfg_EnableConditionGroupTable  /**< the pointer to Dem_Cfg_EnableConditionGroupTable */
#define Dem_Cfg_GetEnableConditionInitTableOfPCConfig()               Dem_Cfg_EnableConditionInitTable  /**< the pointer to Dem_Cfg_EnableConditionInitTable */
#define Dem_Cfg_GetEnableConditionStateOfPCConfig()                   Dem_Cfg_EnableConditionState  /**< the pointer to Dem_Cfg_EnableConditionState */
#define Dem_Cfg_GetEnableConditionTableOfPCConfig()                   Dem_Cfg_EnableConditionTable  /**< the pointer to Dem_Cfg_EnableConditionTable */
#define Dem_Cfg_GetEventAvailableDefaultOfPCConfig()                  Dem_Cfg_EventAvailableDefault  /**< the pointer to Dem_Cfg_EventAvailableDefault */
#define Dem_Cfg_GetEventAvailableInVariantOfPCConfig()                Dem_Cfg_EventAvailableInVariant  /**< the pointer to Dem_Cfg_EventAvailableInVariant */
#define Dem_Cfg_GetEventDebounceValueOfPCConfig()                     Dem_Cfg_EventDebounceValue  /**< the pointer to Dem_Cfg_EventDebounceValue */
#define Dem_Cfg_GetEventInternalStatusOfPCConfig()                    Dem_Cfg_EventInternalStatus  /**< the pointer to Dem_Cfg_EventInternalStatus */
#define Dem_Cfg_GetEventTableIndOfPCConfig()                          Dem_Cfg_EventTableInd  /**< the pointer to Dem_Cfg_EventTableInd */
#define Dem_Cfg_GetEventTableOfPCConfig()                             Dem_Cfg_EventTable  /**< the pointer to Dem_Cfg_EventTable */
#define Dem_Cfg_GetExtendedDataTableOfPCConfig()                      Dem_Cfg_ExtendedDataTable  /**< the pointer to Dem_Cfg_ExtendedDataTable */
#define Dem_Cfg_GetFilterInfoTableOfPCConfig()                        Dem_Cfg_FilterInfoTable  /**< the pointer to Dem_Cfg_FilterInfoTable */
#define Dem_Cfg_GetFilterReportedEventsOfPCConfig()                   Dem_Cfg_FilterReportedEvents  /**< the pointer to Dem_Cfg_FilterReportedEvents */
#define Dem_Cfg_GetFreezeFrameIteratorTableOfPCConfig()               Dem_Cfg_FreezeFrameIteratorTable  /**< the pointer to Dem_Cfg_FreezeFrameIteratorTable */
#define Dem_Cfg_GetFreezeFrameTableOfPCConfig()                       Dem_Cfg_FreezeFrameTable  /**< the pointer to Dem_Cfg_FreezeFrameTable */
#define Dem_Cfg_GetGeneralObdInputOfPCConfig()                        Dem_Cfg_GeneralObdInput  /**< the pointer to Dem_Cfg_GeneralObdInput */
#define Dem_Cfg_GetGlobalSeverityMaskOfPCConfig()                     0x00u  /**< Variant specific mask from OR'ed /Dem/DemConfigSet/DemDTCClass/DemDTCSeverity bits. */
#define Dem_Cfg_GetMemoryBlockIdToMemoryEntryIdOfPCConfig()           Dem_Cfg_MemoryBlockIdToMemoryEntryId  /**< the pointer to Dem_Cfg_MemoryBlockIdToMemoryEntryId */
#define Dem_Cfg_GetMemoryCommitNumberOfPCConfig()                     Dem_Cfg_MemoryCommitNumber  /**< the pointer to Dem_Cfg_MemoryCommitNumber */
#define Dem_Cfg_GetMemoryDataPtrOfPCConfig()                          Dem_Cfg_MemoryDataPtr  /**< the pointer to Dem_Cfg_MemoryDataPtr */
#define Dem_Cfg_GetMemoryDataSizeOfPCConfig()                         Dem_Cfg_MemoryDataSize  /**< the pointer to Dem_Cfg_MemoryDataSize */
#define Dem_Cfg_GetMemoryEntryInitOfPCConfig()                        Dem_Cfg_MemoryEntryInit  /**< the pointer to Dem_Cfg_MemoryEntryInit */
#define Dem_Cfg_GetMemoryEntryOfPCConfig()                            Dem_Cfg_MemoryEntry  /**< the pointer to Dem_Cfg_MemoryEntry */
#define Dem_Cfg_GetMemoryStatusOfPCConfig()                           Dem_Cfg_MemoryStatus  /**< the pointer to Dem_Cfg_MemoryStatus */
#define Dem_Cfg_GetPrimaryChronologyOfPCConfig()                      Dem_Cfg_PrimaryChronology  /**< the pointer to Dem_Cfg_PrimaryChronology */
#define Dem_Cfg_GetPrimaryEntry_0OfPCConfig()                         Dem_Cfg_PrimaryEntry_0  /**< the pointer to Dem_Cfg_PrimaryEntry_0 */
#define Dem_Cfg_GetPrimaryEntry_10OfPCConfig()                        Dem_Cfg_PrimaryEntry_10  /**< the pointer to Dem_Cfg_PrimaryEntry_10 */
#define Dem_Cfg_GetPrimaryEntry_11OfPCConfig()                        Dem_Cfg_PrimaryEntry_11  /**< the pointer to Dem_Cfg_PrimaryEntry_11 */
#define Dem_Cfg_GetPrimaryEntry_12OfPCConfig()                        Dem_Cfg_PrimaryEntry_12  /**< the pointer to Dem_Cfg_PrimaryEntry_12 */
#define Dem_Cfg_GetPrimaryEntry_13OfPCConfig()                        Dem_Cfg_PrimaryEntry_13  /**< the pointer to Dem_Cfg_PrimaryEntry_13 */
#define Dem_Cfg_GetPrimaryEntry_14OfPCConfig()                        Dem_Cfg_PrimaryEntry_14  /**< the pointer to Dem_Cfg_PrimaryEntry_14 */
#define Dem_Cfg_GetPrimaryEntry_15OfPCConfig()                        Dem_Cfg_PrimaryEntry_15  /**< the pointer to Dem_Cfg_PrimaryEntry_15 */
#define Dem_Cfg_GetPrimaryEntry_16OfPCConfig()                        Dem_Cfg_PrimaryEntry_16  /**< the pointer to Dem_Cfg_PrimaryEntry_16 */
#define Dem_Cfg_GetPrimaryEntry_17OfPCConfig()                        Dem_Cfg_PrimaryEntry_17  /**< the pointer to Dem_Cfg_PrimaryEntry_17 */
#define Dem_Cfg_GetPrimaryEntry_1OfPCConfig()                         Dem_Cfg_PrimaryEntry_1  /**< the pointer to Dem_Cfg_PrimaryEntry_1 */
#define Dem_Cfg_GetPrimaryEntry_2OfPCConfig()                         Dem_Cfg_PrimaryEntry_2  /**< the pointer to Dem_Cfg_PrimaryEntry_2 */
#define Dem_Cfg_GetPrimaryEntry_3OfPCConfig()                         Dem_Cfg_PrimaryEntry_3  /**< the pointer to Dem_Cfg_PrimaryEntry_3 */
#define Dem_Cfg_GetPrimaryEntry_4OfPCConfig()                         Dem_Cfg_PrimaryEntry_4  /**< the pointer to Dem_Cfg_PrimaryEntry_4 */
#define Dem_Cfg_GetPrimaryEntry_5OfPCConfig()                         Dem_Cfg_PrimaryEntry_5  /**< the pointer to Dem_Cfg_PrimaryEntry_5 */
#define Dem_Cfg_GetPrimaryEntry_6OfPCConfig()                         Dem_Cfg_PrimaryEntry_6  /**< the pointer to Dem_Cfg_PrimaryEntry_6 */
#define Dem_Cfg_GetPrimaryEntry_7OfPCConfig()                         Dem_Cfg_PrimaryEntry_7  /**< the pointer to Dem_Cfg_PrimaryEntry_7 */
#define Dem_Cfg_GetPrimaryEntry_8OfPCConfig()                         Dem_Cfg_PrimaryEntry_8  /**< the pointer to Dem_Cfg_PrimaryEntry_8 */
#define Dem_Cfg_GetPrimaryEntry_9OfPCConfig()                         Dem_Cfg_PrimaryEntry_9  /**< the pointer to Dem_Cfg_PrimaryEntry_9 */
#define Dem_Cfg_GetReadoutBufferOfPCConfig()                          Dem_Cfg_ReadoutBuffer  /**< the pointer to Dem_Cfg_ReadoutBuffer */
#define Dem_Cfg_GetReportedEventsOfFilterOfPCConfig()                 Dem_Cfg_ReportedEventsOfFilter  /**< the pointer to Dem_Cfg_ReportedEventsOfFilter */
#define Dem_Cfg_GetSatelliteInfo0OfPCConfig()                         Dem_Cfg_SatelliteInfo0  /**< the pointer to Dem_Cfg_SatelliteInfo0 */
#define Dem_Cfg_GetSatelliteInfoOfPCConfig()                          Dem_Cfg_SatelliteInfo  /**< the pointer to Dem_Cfg_SatelliteInfo */
#define Dem_Cfg_GetSizeOfClearDTCTableOfPCConfig()                    1u  /**< the number of accomplishable value elements in Dem_Cfg_ClearDTCTable */
#define Dem_Cfg_GetSizeOfClientTableOfPCConfig()                      1u  /**< the number of accomplishable value elements in Dem_Cfg_ClientTable */
#define Dem_Cfg_GetSizeOfDTCSelectorTableOfPCConfig()                 1u  /**< the number of accomplishable value elements in Dem_Cfg_DTCSelectorTable */
#define Dem_Cfg_GetSizeOfDataElementTableOfPCConfig()                 7u  /**< the number of accomplishable value elements in Dem_Cfg_DataElementTable */
#define Dem_Cfg_GetSizeOfEnableConditionGroupTableOfPCConfig()        1u  /**< the number of accomplishable value elements in Dem_Cfg_EnableConditionGroupTable */
#define Dem_Cfg_GetSizeOfEnableConditionTableOfPCConfig()             1u  /**< the number of accomplishable value elements in Dem_Cfg_EnableConditionTable */
#define Dem_Cfg_GetSizeOfEventTableOfPCConfig()                       22u  /**< the number of accomplishable value elements in Dem_Cfg_EventTable */
#define Dem_Cfg_GetSizeOfFilterInfoTableOfPCConfig()                  1u  /**< the number of accomplishable value elements in Dem_Cfg_FilterInfoTable */
#define Dem_Cfg_GetSizeOfFilterReportedEventsOfPCConfig()             3u  /**< the number of accomplishable value elements in Dem_Cfg_FilterReportedEvents */
#define Dem_Cfg_GetSizeOfFreezeFrameIteratorTableOfPCConfig()         1u  /**< the number of accomplishable value elements in Dem_Cfg_FreezeFrameIteratorTable */
#define Dem_Cfg_GetSizeOfMemoryBlockIdToMemoryEntryIdOfPCConfig()     20u  /**< the number of accomplishable value elements in Dem_Cfg_MemoryBlockIdToMemoryEntryId */
#define Dem_Cfg_GetSizeOfMemoryCommitNumberOfPCConfig()               20u  /**< the number of accomplishable value elements in Dem_Cfg_MemoryCommitNumber */
#define Dem_Cfg_GetSizeOfMemoryEntryOfPCConfig()                      19u  /**< the number of accomplishable value elements in Dem_Cfg_MemoryEntry */
#define Dem_Cfg_GetSizeOfMemoryStatusOfPCConfig()                     20u  /**< the number of accomplishable value elements in Dem_Cfg_MemoryStatus */
#define Dem_Cfg_GetSizeOfPrimaryChronologyOfPCConfig()                18u  /**< the number of accomplishable value elements in Dem_Cfg_PrimaryChronology */
#define Dem_Cfg_GetSizeOfReadoutBufferOfPCConfig()                    1u  /**< the number of accomplishable value elements in Dem_Cfg_ReadoutBuffer */
#define Dem_Cfg_GetSizeOfReportedEventsOfFilterOfPCConfig()           1u  /**< the number of accomplishable value elements in Dem_Cfg_ReportedEventsOfFilter */
#define Dem_Cfg_GetSizeOfSatelliteInfoOfPCConfig()                    1u  /**< the number of accomplishable value elements in Dem_Cfg_SatelliteInfo */
#define Dem_Cfg_GetStatusDataOfPCConfig()                             Dem_Cfg_StatusData  /**< the pointer to Dem_Cfg_StatusData */
#define Dem_Cfg_GetTimeSeriesEntryInitOfPCConfig()                    Dem_Cfg_TimeSeriesEntryInit  /**< the pointer to Dem_Cfg_TimeSeriesEntryInit */
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGetDuplicatedRootDataMacros  Dem_Cfg Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define Dem_Cfg_GetSizeOfEnableConditionGroupCounterOfPCConfig()      Dem_Cfg_GetSizeOfEnableConditionGroupTableOfPCConfig()  /**< the number of accomplishable value elements in Dem_Cfg_EnableConditionGroupCounter */
#define Dem_Cfg_GetSizeOfEnableConditionGroupStateOfPCConfig()        Dem_Cfg_GetSizeOfEnableConditionGroupTableOfPCConfig()  /**< the number of accomplishable value elements in Dem_Cfg_EnableConditionGroupState */
#define Dem_Cfg_GetSizeOfEnableConditionStateOfPCConfig()             Dem_Cfg_GetSizeOfEnableConditionTableOfPCConfig()  /**< the number of accomplishable value elements in Dem_Cfg_EnableConditionState */
#define Dem_Cfg_GetSizeOfEventDebounceValueOfPCConfig()               Dem_Cfg_GetSizeOfEventTableOfPCConfig()  /**< the number of accomplishable value elements in Dem_Cfg_EventDebounceValue */
#define Dem_Cfg_GetSizeOfEventInternalStatusOfPCConfig()              Dem_Cfg_GetSizeOfEventTableOfPCConfig()  /**< the number of accomplishable value elements in Dem_Cfg_EventInternalStatus */
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGetDataMacros  Dem_Cfg Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define Dem_Cfg_GetAdminData()                                        (Dem_Cfg_GetAdminDataOfPCConfig())
#define Dem_Cfg_GetClearDTCTable(Index)                               (Dem_Cfg_GetClearDTCTableOfPCConfig()[(Index)])
#define Dem_Cfg_GetCommitBuffer()                                     (Dem_Cfg_GetCommitBufferOfPCConfig())
#define Dem_Cfg_GetOpCycleTypeOfCycleIdTable(Index)                   (Dem_Cfg_GetCycleIdTableOfPCConfig()[(Index)].OpCycleTypeOfCycleIdTable)
#define Dem_Cfg_IsUsedForAgingOfCycleIdTable(Index)                   ((Dem_Cfg_GetCycleIdTableOfPCConfig()[(Index)].UsedForAgingOfCycleIdTable) != FALSE)
#define Dem_Cfg_GetDTCSelectorTable(Index)                            (Dem_Cfg_GetDTCSelectorTableOfPCConfig()[(Index)])
#define Dem_Cfg_GetCollectionSizeOfDataCollectionTable(Index)         (Dem_Cfg_GetDataCollectionTableOfPCConfig()[(Index)].CollectionSizeOfDataCollectionTable)
#define Dem_Cfg_GetDataElementTableCol2ElmtIndEndIdxOfDataCollectionTable(Index) (Dem_Cfg_GetDataCollectionTableOfPCConfig()[(Index)].DataElementTableCol2ElmtIndEndIdxOfDataCollectionTable)
#define Dem_Cfg_GetDataElementTableCol2ElmtIndStartIdxOfDataCollectionTable(Index) (Dem_Cfg_GetDataCollectionTableOfPCConfig()[(Index)].DataElementTableCol2ElmtIndStartIdxOfDataCollectionTable)
#define Dem_Cfg_GetIdNumberOfDataCollectionTable(Index)               (Dem_Cfg_GetDataCollectionTableOfPCConfig()[(Index)].IdNumberOfDataCollectionTable)
#define Dem_Cfg_GetMaskedBitsOfDataCollectionTable(Index)             (Dem_Cfg_GetDataCollectionTableOfPCConfig()[(Index)].MaskedBitsOfDataCollectionTable)
#define Dem_Cfg_GetStorageKindOfDataCollectionTable(Index)            (Dem_Cfg_GetDataCollectionTableOfPCConfig()[(Index)].StorageKindOfDataCollectionTable)
#define Dem_Cfg_GetDataCollectionTableEdr2CollInd(Index)              (Dem_Cfg_GetDataCollectionTableEdr2CollIndOfPCConfig()[(Index)])
#define Dem_Cfg_GetElementKindOfDataElementTable(Index)               (Dem_Cfg_GetDataElementTableOfPCConfig()[(Index)].ElementKindOfDataElementTable)
#define Dem_Cfg_GetElementSizeOfDataElementTable(Index)               (Dem_Cfg_GetDataElementTableOfPCConfig()[(Index)].ElementSizeOfDataElementTable)
#define Dem_Cfg_GetReadDataFuncOfDataElementTable(Index)              (Dem_Cfg_GetDataElementTableOfPCConfig()[(Index)].ReadDataFuncOfDataElementTable)
#define Dem_Cfg_GetDataElementTableCol2ElmtInd(Index)                 (Dem_Cfg_GetDataElementTableCol2ElmtIndOfPCConfig()[(Index)])
#define Dem_Cfg_GetDecrementStepSizeOfDebounceTable(Index)            (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].DecrementStepSizeOfDebounceTable)
#define Dem_Cfg_GetEventDebounceAlgorithmOfDebounceTable(Index)       (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].EventDebounceAlgorithmOfDebounceTable)
#define Dem_Cfg_GetFailedThresholdOfDebounceTable(Index)              (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].FailedThresholdOfDebounceTable)
#define Dem_Cfg_GetIncrementStepSizeOfDebounceTable(Index)            (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].IncrementStepSizeOfDebounceTable)
#define Dem_Cfg_GetMaskedBitsOfDebounceTable(Index)                   (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].MaskedBitsOfDebounceTable)
#define Dem_Cfg_GetPassedThresholdOfDebounceTable(Index)              (Dem_Cfg_GetDebounceTableOfPCConfig()[(Index)].PassedThresholdOfDebounceTable)
#define Dem_Cfg_GetFunctionalUnitOfDtcTable(Index)                    (Dem_Cfg_GetDtcTableOfPCConfig()[(Index)].FunctionalUnitOfDtcTable)
#define Dem_Cfg_GetUdsDtcOfDtcTable(Index)                            (Dem_Cfg_GetDtcTableOfPCConfig()[(Index)].UdsDtcOfDtcTable)
#define Dem_Cfg_GetEnableConditionGroupCounter(Index)                 (Dem_Cfg_GetEnableConditionGroupCounterOfPCConfig()[(Index)])
#define Dem_Cfg_GetEnableConditionGroupState(Index)                   (Dem_Cfg_GetEnableConditionGroupStateOfPCConfig()[(Index)])
#define Dem_Cfg_GetEnableConditionState(Index)                        (Dem_Cfg_GetEnableConditionStateOfPCConfig()[(Index)])
#define Dem_Cfg_GetEventDebounceValue(Index)                          (Dem_Cfg_GetEventDebounceValueOfPCConfig()[(Index)])
#define Dem_Cfg_GetEventInternalStatus(Index)                         (Dem_Cfg_GetEventInternalStatusOfPCConfig()[(Index)])
#define Dem_Cfg_GetAgingCycleIdOfEventTable(Index)                    (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].AgingCycleIdOfEventTable)
#define Dem_Cfg_GetDtcTableIdxOfEventTable(Index)                     (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].DtcTableIdxOfEventTable)
#define Dem_Cfg_GetExtendedDataTableIdxOfEventTable(Index)            (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].ExtendedDataTableIdxOfEventTable)
#define Dem_Cfg_GetOperationCycleIdOfEventTable(Index)                (Dem_Cfg_GetEventTableOfPCConfig()[(Index)].OperationCycleIdOfEventTable)
#define Dem_Cfg_GetDataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable(Index) (Dem_Cfg_GetExtendedDataTableOfPCConfig()[(Index)].DataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable)
#define Dem_Cfg_GetDataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable(Index) (Dem_Cfg_GetExtendedDataTableOfPCConfig()[(Index)].DataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable)
#define Dem_Cfg_GetMaxRecordSizeOfExtendedDataTable(Index)            (Dem_Cfg_GetExtendedDataTableOfPCConfig()[(Index)].MaxRecordSizeOfExtendedDataTable)
#define Dem_Cfg_GetFilterInfoTable(Index)                             (Dem_Cfg_GetFilterInfoTableOfPCConfig()[(Index)])
#define Dem_Cfg_GetFilterReportedEvents(Index)                        (Dem_Cfg_GetFilterReportedEventsOfPCConfig()[(Index)])
#define Dem_Cfg_GetFreezeFrameIteratorTable(Index)                    (Dem_Cfg_GetFreezeFrameIteratorTableOfPCConfig()[(Index)])
#define Dem_Cfg_GetMemoryBlockIdToMemoryEntryId(Index)                (Dem_Cfg_GetMemoryBlockIdToMemoryEntryIdOfPCConfig()[(Index)])
#define Dem_Cfg_GetMemoryCommitNumber(Index)                          (Dem_Cfg_GetMemoryCommitNumberOfPCConfig()[(Index)])
#define Dem_Cfg_GetMemoryDataPtr(Index)                               (Dem_Cfg_GetMemoryDataPtrOfPCConfig()[(Index)])
#define Dem_Cfg_GetMemoryDataSize(Index)                              (Dem_Cfg_GetMemoryDataSizeOfPCConfig()[(Index)])
#define Dem_Cfg_GetMemoryEntry(Index)                                 (Dem_Cfg_GetMemoryEntryOfPCConfig()[(Index)])
#define Dem_Cfg_GetMemoryEntryInit()                                  (Dem_Cfg_GetMemoryEntryInitOfPCConfig())
#define Dem_Cfg_GetMemoryStatus(Index)                                (Dem_Cfg_GetMemoryStatusOfPCConfig()[(Index)])
#define Dem_Cfg_GetPrimaryChronology(Index)                           (Dem_Cfg_GetPrimaryChronologyOfPCConfig()[(Index)])
#define Dem_Cfg_GetPrimaryEntry_0()                                   (Dem_Cfg_GetPrimaryEntry_0OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_1()                                   (Dem_Cfg_GetPrimaryEntry_1OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_10()                                  (Dem_Cfg_GetPrimaryEntry_10OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_11()                                  (Dem_Cfg_GetPrimaryEntry_11OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_12()                                  (Dem_Cfg_GetPrimaryEntry_12OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_13()                                  (Dem_Cfg_GetPrimaryEntry_13OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_14()                                  (Dem_Cfg_GetPrimaryEntry_14OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_15()                                  (Dem_Cfg_GetPrimaryEntry_15OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_16()                                  (Dem_Cfg_GetPrimaryEntry_16OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_17()                                  (Dem_Cfg_GetPrimaryEntry_17OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_2()                                   (Dem_Cfg_GetPrimaryEntry_2OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_3()                                   (Dem_Cfg_GetPrimaryEntry_3OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_4()                                   (Dem_Cfg_GetPrimaryEntry_4OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_5()                                   (Dem_Cfg_GetPrimaryEntry_5OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_6()                                   (Dem_Cfg_GetPrimaryEntry_6OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_7()                                   (Dem_Cfg_GetPrimaryEntry_7OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_8()                                   (Dem_Cfg_GetPrimaryEntry_8OfPCConfig())
#define Dem_Cfg_GetPrimaryEntry_9()                                   (Dem_Cfg_GetPrimaryEntry_9OfPCConfig())
#define Dem_Cfg_GetReadoutBuffer(Index)                               (Dem_Cfg_GetReadoutBufferOfPCConfig()[(Index)])
#define Dem_Cfg_GetReportedEventsOfFilter(Index)                      (Dem_Cfg_GetReportedEventsOfFilterOfPCConfig()[(Index)])
#define Dem_Cfg_GetSatelliteInfo0()                                   (Dem_Cfg_GetSatelliteInfo0OfPCConfig())
#define Dem_Cfg_GetStatusData()                                       (Dem_Cfg_GetStatusDataOfPCConfig())
#define Dem_Cfg_GetTimeSeriesEntryInit()                              (Dem_Cfg_GetTimeSeriesEntryInitOfPCConfig())
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGetBitDataMacros  Dem_Cfg Get Bit Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read bitcoded data elements.
  \{
*/ 
#define Dem_Cfg_IsJumpUpOfDebounceTable(Index)                        (DEM_CFG_JUMPUPOFDEBOUNCETABLE_MASK == (Dem_Cfg_GetMaskedBitsOfDebounceTable(Index) & DEM_CFG_JUMPUPOFDEBOUNCETABLE_MASK))  /**< DemDebounceCounterJumpUp of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGetDeduplicatedDataMacros  Dem_Cfg Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define Dem_Cfg_GetClearDTCIndexOfClientTable(Index)                  0u  /**< 'DEM_CFG_CLEARDTC_INVALID'(=255): no ClearDTC for the Client, else: index in Dem_Cfg_ClearDTCTable[] */
#define Dem_Cfg_GetFilterIndexOfClientTable(Index)                    0u  /**< 'DEM_CFG_FILTER_INVALID'(=255): no filter for the Client, else: index in Dem_Cfg_FilterInfoTable[] */
#define Dem_Cfg_GetFreezeFrameIteratorIndexOfClientTable(Index)       0u  /**< 'DEM_CFG_FREEZEFRAMEITERATOR_INVALID'(=255): no FreezeFrameIterator for the Client, else: index in Dem_Cfg_FreezeFrameIteratorTable[] */
#define Dem_Cfg_GetReadoutBufferIndexOfClientTable(Index)             0u  /**< 'DEM_CFG_READOUTBUFFER_INVALID'(=255): no ReadoutBuffer for the Client, else: index in Dem_Cfg_ReadoutBuffer[] */
#define Dem_Cfg_GetSelectorIndexOfClientTable(Index)                  0u  /**< 'DEM_CFG_DTCSELECTOR_INVALID'(=255): no selector for the Client, else: index in Dem_Cfg_DTCSelectorTable[] */
#define Dem_Cfg_GetConfigurationId()                                  Dem_Cfg_GetConfigurationIdOfPCConfig()
#define Dem_Cfg_IsDataElementTableCol2ElmtIndUsedOfDataCollectionTable(Index) (((boolean)(Dem_Cfg_GetDataElementTableCol2ElmtIndStartIdxOfDataCollectionTable(Index) != DEM_CFG_NO_DATAELEMENTTABLECOL2ELMTINDSTARTIDXOFDATACOLLECTIONTABLE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Dem_Cfg_DataElementTableCol2ElmtInd */
#define Dem_Cfg_IsUpdateOfDataCollectionTable(Index)                  (((boolean)(Dem_Cfg_GetMaskedBitsOfDataCollectionTable(Index) == 0x03u)) != FALSE)
#define Dem_Cfg_IsDataIsStoredInNVOfDataElementTable(Index)           (((boolean)(Dem_Cfg_GetElementSizeOfDataElementTable(Index) != 0u)) != FALSE)
#define Dem_Cfg_IsDebounceContinuousOfDebounceTable(Index)            (((FALSE)) != FALSE)  /**< DemDebounceContinuous of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased and ~/DemDebounceTimeBase */
#define Dem_Cfg_IsEventDebounceBehaviorOfDebounceTable(Index)         (((FALSE)) != FALSE)  /**< DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/[algorithm]/DemDebounceBehavior == DEM_DEBOUNCE_RESET */
#define Dem_Cfg_GetFailTimerCyclesOfDebounceTable(Index)              0  /**< HiRes- or LoRes-Timer ticks for DemDebounceTimeFailedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceTimeBase */
#define Dem_Cfg_IsJumpDownOfDebounceTable(Index)                      Dem_Cfg_IsJumpUpOfDebounceTable(Index)  /**< DemDebounceCounterJumpDown of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBase */
#define Dem_Cfg_GetJumpDownValueOfDebounceTable(Index)                0  /**< DemDebounceCounterJumpDownValue of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
#define Dem_Cfg_GetJumpUpValueOfDebounceTable(Index)                  0  /**< DemDebounceCounterJumpUpValue of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
#define Dem_Cfg_GetPassTimerCyclesOfDebounceTable(Index)              0  /**< HiRes- or LoRes-Timer ticks for DemDebounceTimePassedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceTimeBase */
#define Dem_Cfg_IsStorageOfDebounceTable(Index)                       (((FALSE)) != FALSE)  /**< DemDebounceCounterStorage of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
#define Dem_Cfg_GetDtcSeverityOfDtcTable(Index)                       0u
#define Dem_Cfg_IsImmediateNvStorageOfDtcTable(Index)                 (((boolean)(Dem_Cfg_GetFunctionalUnitOfDtcTable(Index) == 0u)) != FALSE)
#define Dem_Cfg_GetIndexOfEnableConditionGroupTable(Index)            0u  /**< Dummy - contains always the index of this element (self) */
#define Dem_Cfg_GetEnableConditionGroupTableInd(Index)                0u  /**< the indexes of the 1:1 sorted relation pointing to Dem_Cfg_EnableConditionGroupTable */
#define Dem_Cfg_GetInitValueOfEnableConditionInitTable(Index)         1u  /**< Initial value: '0' condition is in state 'disable', '1' condition is in state 'enable' */
#define Dem_Cfg_GetEnableConditionGroupTableIndEndIdxOfEnableConditionTable(Index) 1u  /**< the end index of the 0:n relation pointing to Dem_Cfg_EnableConditionGroupTableInd */
#define Dem_Cfg_GetEnableConditionGroupTableIndStartIdxOfEnableConditionTable(Index) 0u  /**< the start index of the 0:n relation pointing to Dem_Cfg_EnableConditionGroupTableInd */
#define Dem_Cfg_IsEnableConditionGroupTableIndUsedOfEnableConditionTable(Index) (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Dem_Cfg_EnableConditionGroupTableInd */
#define Dem_Cfg_IsEventAvailableDefault(Index)                        (((TRUE)) != FALSE)
#define Dem_Cfg_IsEventAvailableInVariant(Index)                      (((TRUE)) != FALSE)
#define Dem_Cfg_IsAgingAllowedOfEventTable(Index)                     (((FALSE)) != FALSE)  /**< DemAgingAllowed of the DemEventParameter/DemEventClass */
#define Dem_Cfg_GetAgingCycleCounterThresholdOfEventTable(Index)      255u  /**< DemAgingCycleCounterThreshold of the DemEventParameter/DemEventClass, if AgingAllowedOfEventTable==FALSE we use '255' here, too. */
#define Dem_Cfg_GetDebounceTableIdxOfEventTable(Index)                0u  /**< the index of the 1:1 relation pointing to Dem_Cfg_DebounceTable */
#define Dem_Cfg_GetEnableConditionGroupTableIdxOfEventTable(Index)    0u  /**< the index of the 1:1 relation pointing to Dem_Cfg_EnableConditionGroupTable */
#define Dem_Cfg_GetEventDestinationOfEventTable(Index)                DEM_CFG_MEMORYID_PRIMARY  /**< DemEventDestination of the DemEventParameter/DemEventClass */
#define Dem_Cfg_GetEventFailureCycleCounterThresholdOfEventTable(Index) 0u  /**< DemEventFailureCycleCounterThreshold of the DemEventParameter/DemEventClass, '0': is also default for unset parameter */
#define Dem_Cfg_GetEventKindOfEventTable(Index)                       Dem_Cfg_GetExtendedDataTableIdxOfEventTable(Index)  /**< DemEventKind of the DemEventParameter */
#define Dem_Cfg_IsEventLatchTFOfEventTable(Index)                     (((FALSE)) != FALSE)  /**< DemEventLatchTestFailed of the DemEventParameter */
#define Dem_Cfg_GetEventPriorityOfEventTable(Index)                   2u  /**< DemEventParameter/DemEventClass/DemEventPriority, values [1..255] for the configuration range [1..255]. */
#define Dem_Cfg_GetEventSignificanceOfEventTable(Index)               DEM_CFG_DEM_EVENT_SIGNIFICANCE_FAULT_EVENTSIGNIFICANCEOFEVENTTABLE  /**< DemEventSignificance of the DemEventParameter/DemEventClass */
#define Dem_Cfg_GetFreezeFrameTableStdFFIdxOfEventTable(Index)        0u  /**< the index of the 1:1 relation pointing to Dem_Cfg_FreezeFrameTable */
#define Dem_Cfg_GetHealingTargetOfEventTable(Index)                   0u  /**< DemIndicatorHealingCycleCounterThreshold of the DemEventParameter/DemEventClass/DemIndicatorAttribute (for each event all attribute's value must be identical). Events without DemIndicatorAttribute have: 0. */
#define Dem_Cfg_GetMaskedBitsOfEventTable(Index)                      0x00u  /**< contains bitcoded the boolean data of Dem_Cfg_AgingAllowedOfEventTable, Dem_Cfg_EventLatchTFOfEventTable */
#define Dem_Cfg_GetSatelliteEventIdxOfEventTable(Index)               ((Dem_Cfg_SatelliteEventIdxOfEventTableType)((Index)))  /**< Index of this event in the satellite's RAM buffers Dem_Cfg_SatelliteInfoNN.SatelliteData[] and Dem_Cfg_SatelliteInfoNN.SatelliteExtendedData[]. */
#define Dem_Cfg_GetSatelliteInfoIdxOfEventTable(Index)                0u  /**< the index of the 1:1 relation pointing to Dem_Cfg_SatelliteInfo */
#define Dem_Cfg_GetEventTableInd(Index)                               ((Dem_Cfg_EventTableIndType)((Index)))  /**< the indexes of the 1:1 sorted relation pointing to Dem_Cfg_EventTable */
#define Dem_Cfg_IsDataCollectionTableEdr2CollIndUsedOfExtendedDataTable(Index) (((boolean)(Dem_Cfg_GetDataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable(Index) != DEM_CFG_NO_DATACOLLECTIONTABLEEDR2COLLINDSTARTIDXOFEXTENDEDDATATABLE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Dem_Cfg_DataCollectionTableEdr2CollInd */
#define Dem_Cfg_GetRecordSizeOfFreezeFrameTable(Index)                0u  /**< Summarized size of did data that is stored in Dem_Cfg_PrimaryEntryType.SnapshotData[][] (i.e. typically without size of dids containing internal data elements). */
#define Dem_Cfg_GetRecordSizeUdsOfFreezeFrameTable(Index)             0u  /**< Summarized size of did data, did numbers and snapshot header (i.e. dynamical payload size of the uds response message). */
#define Dem_Cfg_GetDataElementTableIdxOfGeneralObdInput(Index)        0u  /**< the index of the 1:1 relation pointing to Dem_Cfg_DataElementTable */
#define Dem_Cfg_GetGlobalSeverityMask()                               Dem_Cfg_GetGlobalSeverityMaskOfPCConfig()
#define Dem_Cfg_GetApplicationIdOfSatelliteInfo(Index)                0  /**< Partition (OsApplication identifier) of the satellite. */
#define Dem_Cfg_GetEventCountOfSatelliteInfo(Index)                   22u  /**< Satellite individual size of the monitor/event data RAM buffer */
#define Dem_Cfg_GetEventTableIndEndIdxOfSatelliteInfo(Index)          22u  /**< the end index of the 0:n relation pointing to Dem_Cfg_EventTableInd */
#define Dem_Cfg_GetEventTableIndStartIdxOfSatelliteInfo(Index)        0u  /**< the start index of the 0:n relation pointing to Dem_Cfg_EventTableInd */
#define Dem_Cfg_IsEventTableIndUsedOfSatelliteInfo(Index)             (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Dem_Cfg_EventTableInd */
#define Dem_Cfg_GetSatelliteDataOfSatelliteInfo(Index)                &Dem_Cfg_GetSatelliteInfo0().SatelliteData[0]  /**< Satellite individual RAM buffer 1 for the monitor/event data */
#define Dem_Cfg_GetSatelliteStatusOfSatelliteInfo(Index)              &Dem_Cfg_GetSatelliteInfo0().SatelliteStatus  /**< Satellite individual RAM buffer for the monitor/event status */
#define Dem_Cfg_GetSizeOfClearDTCTable()                              Dem_Cfg_GetSizeOfClearDTCTableOfPCConfig()
#define Dem_Cfg_GetSizeOfClientTable()                                Dem_Cfg_GetSizeOfClientTableOfPCConfig()
#define Dem_Cfg_GetSizeOfDTCSelectorTable()                           Dem_Cfg_GetSizeOfDTCSelectorTableOfPCConfig()
#define Dem_Cfg_GetSizeOfDataElementTable()                           Dem_Cfg_GetSizeOfDataElementTableOfPCConfig()
#define Dem_Cfg_GetSizeOfEnableConditionGroupCounter()                Dem_Cfg_GetSizeOfEnableConditionGroupCounterOfPCConfig()
#define Dem_Cfg_GetSizeOfEnableConditionGroupState()                  Dem_Cfg_GetSizeOfEnableConditionGroupStateOfPCConfig()
#define Dem_Cfg_GetSizeOfEnableConditionGroupTable()                  Dem_Cfg_GetSizeOfEnableConditionGroupTableOfPCConfig()
#define Dem_Cfg_GetSizeOfEnableConditionState()                       Dem_Cfg_GetSizeOfEnableConditionStateOfPCConfig()
#define Dem_Cfg_GetSizeOfEnableConditionTable()                       Dem_Cfg_GetSizeOfEnableConditionTableOfPCConfig()
#define Dem_Cfg_GetSizeOfEventDebounceValue()                         Dem_Cfg_GetSizeOfEventDebounceValueOfPCConfig()
#define Dem_Cfg_GetSizeOfEventInternalStatus()                        Dem_Cfg_GetSizeOfEventInternalStatusOfPCConfig()
#define Dem_Cfg_GetSizeOfEventTable()                                 Dem_Cfg_GetSizeOfEventTableOfPCConfig()
#define Dem_Cfg_GetSizeOfFilterInfoTable()                            Dem_Cfg_GetSizeOfFilterInfoTableOfPCConfig()
#define Dem_Cfg_GetSizeOfFilterReportedEvents()                       Dem_Cfg_GetSizeOfFilterReportedEventsOfPCConfig()
#define Dem_Cfg_GetSizeOfFreezeFrameIteratorTable()                   Dem_Cfg_GetSizeOfFreezeFrameIteratorTableOfPCConfig()
#define Dem_Cfg_GetSizeOfMemoryBlockIdToMemoryEntryId()               Dem_Cfg_GetSizeOfMemoryBlockIdToMemoryEntryIdOfPCConfig()
#define Dem_Cfg_GetSizeOfMemoryCommitNumber()                         Dem_Cfg_GetSizeOfMemoryCommitNumberOfPCConfig()
#define Dem_Cfg_GetSizeOfMemoryEntry()                                Dem_Cfg_GetSizeOfMemoryEntryOfPCConfig()
#define Dem_Cfg_GetSizeOfMemoryStatus()                               Dem_Cfg_GetSizeOfMemoryStatusOfPCConfig()
#define Dem_Cfg_GetSizeOfPrimaryChronology()                          Dem_Cfg_GetSizeOfPrimaryChronologyOfPCConfig()
#define Dem_Cfg_GetSizeOfReadoutBuffer()                              Dem_Cfg_GetSizeOfReadoutBufferOfPCConfig()
#define Dem_Cfg_GetSizeOfReportedEventsOfFilter()                     Dem_Cfg_GetSizeOfReportedEventsOfFilterOfPCConfig()
#define Dem_Cfg_GetSizeOfSatelliteInfo()                              Dem_Cfg_GetSizeOfSatelliteInfoOfPCConfig()
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCSetDataMacros  Dem_Cfg Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define Dem_Cfg_SetAdminData(Value)                                   Dem_Cfg_GetAdminDataOfPCConfig() = (Value)
#define Dem_Cfg_SetClearDTCTable(Index, Value)                        Dem_Cfg_GetClearDTCTableOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetCommitBuffer(Value)                                Dem_Cfg_GetCommitBufferOfPCConfig() = (Value)
#define Dem_Cfg_SetDTCSelectorTable(Index, Value)                     Dem_Cfg_GetDTCSelectorTableOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetEnableConditionGroupCounter(Index, Value)          Dem_Cfg_GetEnableConditionGroupCounterOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetEnableConditionGroupState(Index, Value)            Dem_Cfg_GetEnableConditionGroupStateOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetEnableConditionState(Index, Value)                 Dem_Cfg_GetEnableConditionStateOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetEventDebounceValue(Index, Value)                   Dem_Cfg_GetEventDebounceValueOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetEventInternalStatus(Index, Value)                  Dem_Cfg_GetEventInternalStatusOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetFilterInfoTable(Index, Value)                      Dem_Cfg_GetFilterInfoTableOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetFilterReportedEvents(Index, Value)                 Dem_Cfg_GetFilterReportedEventsOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetFreezeFrameIteratorTable(Index, Value)             Dem_Cfg_GetFreezeFrameIteratorTableOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetMemoryCommitNumber(Index, Value)                   Dem_Cfg_GetMemoryCommitNumberOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetMemoryStatus(Index, Value)                         Dem_Cfg_GetMemoryStatusOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetPrimaryChronology(Index, Value)                    Dem_Cfg_GetPrimaryChronologyOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetPrimaryEntry_0(Value)                              Dem_Cfg_GetPrimaryEntry_0OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_1(Value)                              Dem_Cfg_GetPrimaryEntry_1OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_10(Value)                             Dem_Cfg_GetPrimaryEntry_10OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_11(Value)                             Dem_Cfg_GetPrimaryEntry_11OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_12(Value)                             Dem_Cfg_GetPrimaryEntry_12OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_13(Value)                             Dem_Cfg_GetPrimaryEntry_13OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_14(Value)                             Dem_Cfg_GetPrimaryEntry_14OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_15(Value)                             Dem_Cfg_GetPrimaryEntry_15OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_16(Value)                             Dem_Cfg_GetPrimaryEntry_16OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_17(Value)                             Dem_Cfg_GetPrimaryEntry_17OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_2(Value)                              Dem_Cfg_GetPrimaryEntry_2OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_3(Value)                              Dem_Cfg_GetPrimaryEntry_3OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_4(Value)                              Dem_Cfg_GetPrimaryEntry_4OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_5(Value)                              Dem_Cfg_GetPrimaryEntry_5OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_6(Value)                              Dem_Cfg_GetPrimaryEntry_6OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_7(Value)                              Dem_Cfg_GetPrimaryEntry_7OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_8(Value)                              Dem_Cfg_GetPrimaryEntry_8OfPCConfig() = (Value)
#define Dem_Cfg_SetPrimaryEntry_9(Value)                              Dem_Cfg_GetPrimaryEntry_9OfPCConfig() = (Value)
#define Dem_Cfg_SetReadoutBuffer(Index, Value)                        Dem_Cfg_GetReadoutBufferOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetReportedEventsOfFilter(Index, Value)               Dem_Cfg_GetReportedEventsOfFilterOfPCConfig()[(Index)] = (Value)
#define Dem_Cfg_SetSatelliteInfo0(Value)                              Dem_Cfg_GetSatelliteInfo0OfPCConfig() = (Value)
#define Dem_Cfg_SetStatusData(Value)                                  Dem_Cfg_GetStatusDataOfPCConfig() = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCGetAddressOfDataMacros  Dem_Cfg Get Address Of Data Macros (PRE_COMPILE)
  \brief  These macros can be used to get the data by the address operator.
  \{
*/ 
#define Dem_Cfg_GetAddrClearDTCTable(Index)                           &Dem_Cfg_GetClearDTCTable(Index)
#define Dem_Cfg_GetAddrDTCSelectorTable(Index)                        &Dem_Cfg_GetDTCSelectorTable(Index)
#define Dem_Cfg_GetAddrEnableConditionGroupCounter(Index)             &Dem_Cfg_GetEnableConditionGroupCounter(Index)
#define Dem_Cfg_GetAddrEnableConditionGroupState(Index)               &Dem_Cfg_GetEnableConditionGroupState(Index)
#define Dem_Cfg_GetAddrEnableConditionState(Index)                    &Dem_Cfg_GetEnableConditionState(Index)
#define Dem_Cfg_GetAddrEventDebounceValue(Index)                      &Dem_Cfg_GetEventDebounceValue(Index)
#define Dem_Cfg_GetAddrEventInternalStatus(Index)                     &Dem_Cfg_GetEventInternalStatus(Index)
#define Dem_Cfg_GetAddrFilterInfoTable(Index)                         &Dem_Cfg_GetFilterInfoTable(Index)
#define Dem_Cfg_GetAddrFilterReportedEvents(Index)                    &Dem_Cfg_GetFilterReportedEvents(Index)
#define Dem_Cfg_GetAddrFreezeFrameIteratorTable(Index)                &Dem_Cfg_GetFreezeFrameIteratorTable(Index)
#define Dem_Cfg_GetAddrMemoryCommitNumber(Index)                      &Dem_Cfg_GetMemoryCommitNumber(Index)
#define Dem_Cfg_GetAddrMemoryStatus(Index)                            &Dem_Cfg_GetMemoryStatus(Index)
#define Dem_Cfg_GetAddrPrimaryChronology(Index)                       &Dem_Cfg_GetPrimaryChronology(Index)
#define Dem_Cfg_GetAddrReadoutBuffer(Index)                           &Dem_Cfg_GetReadoutBuffer(Index)
#define Dem_Cfg_GetAddrReportedEventsOfFilter(Index)                  &Dem_Cfg_GetReportedEventsOfFilter(Index)
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCHasMacros  Dem_Cfg Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define Dem_Cfg_HasAdminData()                                        (TRUE != FALSE)
#define Dem_Cfg_HasClearDTCTable()                                    (TRUE != FALSE)
#define Dem_Cfg_HasClientTable()                                      (TRUE != FALSE)
#define Dem_Cfg_HasClearDTCIndexOfClientTable()                       (TRUE != FALSE)
#define Dem_Cfg_HasFilterIndexOfClientTable()                         (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameIteratorIndexOfClientTable()            (TRUE != FALSE)
#define Dem_Cfg_HasReadoutBufferIndexOfClientTable()                  (TRUE != FALSE)
#define Dem_Cfg_HasSelectorIndexOfClientTable()                       (TRUE != FALSE)
#define Dem_Cfg_HasCommitBuffer()                                     (TRUE != FALSE)
#define Dem_Cfg_HasConfigurationId()                                  (TRUE != FALSE)
#define Dem_Cfg_HasCycleIdTable()                                     (TRUE != FALSE)
#define Dem_Cfg_HasOpCycleTypeOfCycleIdTable()                        (TRUE != FALSE)
#define Dem_Cfg_HasUsedForAgingOfCycleIdTable()                       (TRUE != FALSE)
#define Dem_Cfg_HasDTCSelectorTable()                                 (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTable()                              (TRUE != FALSE)
#define Dem_Cfg_HasCollectionSizeOfDataCollectionTable()              (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableCol2ElmtIndEndIdxOfDataCollectionTable() (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableCol2ElmtIndStartIdxOfDataCollectionTable() (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableCol2ElmtIndUsedOfDataCollectionTable() (TRUE != FALSE)
#define Dem_Cfg_HasIdNumberOfDataCollectionTable()                    (TRUE != FALSE)
#define Dem_Cfg_HasMaskedBitsOfDataCollectionTable()                  (TRUE != FALSE)
#define Dem_Cfg_HasStorageKindOfDataCollectionTable()                 (TRUE != FALSE)
#define Dem_Cfg_HasUpdateOfDataCollectionTable()                      (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableEdr2CollInd()                   (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTable()                                 (TRUE != FALSE)
#define Dem_Cfg_HasDataIsStoredInNVOfDataElementTable()               (TRUE != FALSE)
#define Dem_Cfg_HasElementKindOfDataElementTable()                    (TRUE != FALSE)
#define Dem_Cfg_HasElementSizeOfDataElementTable()                    (TRUE != FALSE)
#define Dem_Cfg_HasReadDataFuncOfDataElementTable()                   (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableCol2ElmtInd()                      (TRUE != FALSE)
#define Dem_Cfg_HasDebounceTable()                                    (TRUE != FALSE)
#define Dem_Cfg_HasDebounceContinuousOfDebounceTable()                (TRUE != FALSE)
#define Dem_Cfg_HasDecrementStepSizeOfDebounceTable()                 (TRUE != FALSE)
#define Dem_Cfg_HasEventDebounceAlgorithmOfDebounceTable()            (TRUE != FALSE)
#define Dem_Cfg_HasEventDebounceBehaviorOfDebounceTable()             (TRUE != FALSE)
#define Dem_Cfg_HasFailTimerCyclesOfDebounceTable()                   (TRUE != FALSE)
#define Dem_Cfg_HasFailedThresholdOfDebounceTable()                   (TRUE != FALSE)
#define Dem_Cfg_HasIncrementStepSizeOfDebounceTable()                 (TRUE != FALSE)
#define Dem_Cfg_HasJumpDownOfDebounceTable()                          (TRUE != FALSE)
#define Dem_Cfg_HasJumpDownValueOfDebounceTable()                     (TRUE != FALSE)
#define Dem_Cfg_HasJumpUpOfDebounceTable()                            (TRUE != FALSE)
#define Dem_Cfg_HasJumpUpValueOfDebounceTable()                       (TRUE != FALSE)
#define Dem_Cfg_HasMaskedBitsOfDebounceTable()                        (TRUE != FALSE)
#define Dem_Cfg_HasPassTimerCyclesOfDebounceTable()                   (TRUE != FALSE)
#define Dem_Cfg_HasPassedThresholdOfDebounceTable()                   (TRUE != FALSE)
#define Dem_Cfg_HasStorageOfDebounceTable()                           (TRUE != FALSE)
#define Dem_Cfg_HasDtcTable()                                         (TRUE != FALSE)
#define Dem_Cfg_HasDtcSeverityOfDtcTable()                            (TRUE != FALSE)
#define Dem_Cfg_HasFunctionalUnitOfDtcTable()                         (TRUE != FALSE)
#define Dem_Cfg_HasImmediateNvStorageOfDtcTable()                     (TRUE != FALSE)
#define Dem_Cfg_HasUdsDtcOfDtcTable()                                 (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupCounter()                      (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupState()                        (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTable()                        (TRUE != FALSE)
#define Dem_Cfg_HasIndexOfEnableConditionGroupTable()                 (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableInd()                     (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionInitTable()                         (TRUE != FALSE)
#define Dem_Cfg_HasInitValueOfEnableConditionInitTable()              (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionState()                             (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionTable()                             (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableIndEndIdxOfEnableConditionTable() (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableIndStartIdxOfEnableConditionTable() (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableIndUsedOfEnableConditionTable() (TRUE != FALSE)
#define Dem_Cfg_HasEventAvailableDefault()                            (TRUE != FALSE)
#define Dem_Cfg_HasEventAvailableInVariant()                          (TRUE != FALSE)
#define Dem_Cfg_HasEventDebounceValue()                               (TRUE != FALSE)
#define Dem_Cfg_HasEventInternalStatus()                              (TRUE != FALSE)
#define Dem_Cfg_HasEventTable()                                       (TRUE != FALSE)
#define Dem_Cfg_HasAgingAllowedOfEventTable()                         (TRUE != FALSE)
#define Dem_Cfg_HasAgingCycleCounterThresholdOfEventTable()           (TRUE != FALSE)
#define Dem_Cfg_HasAgingCycleIdOfEventTable()                         (TRUE != FALSE)
#define Dem_Cfg_HasDebounceTableIdxOfEventTable()                     (TRUE != FALSE)
#define Dem_Cfg_HasDtcTableIdxOfEventTable()                          (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableIdxOfEventTable()         (TRUE != FALSE)
#define Dem_Cfg_HasEventDestinationOfEventTable()                     (TRUE != FALSE)
#define Dem_Cfg_HasEventFailureCycleCounterThresholdOfEventTable()    (TRUE != FALSE)
#define Dem_Cfg_HasEventKindOfEventTable()                            (TRUE != FALSE)
#define Dem_Cfg_HasEventLatchTFOfEventTable()                         (TRUE != FALSE)
#define Dem_Cfg_HasEventPriorityOfEventTable()                        (TRUE != FALSE)
#define Dem_Cfg_HasEventSignificanceOfEventTable()                    (TRUE != FALSE)
#define Dem_Cfg_HasExtendedDataTableIdxOfEventTable()                 (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameTableStdFFIdxOfEventTable()             (TRUE != FALSE)
#define Dem_Cfg_HasHealingTargetOfEventTable()                        (TRUE != FALSE)
#define Dem_Cfg_HasMaskedBitsOfEventTable()                           (TRUE != FALSE)
#define Dem_Cfg_HasOperationCycleIdOfEventTable()                     (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteEventIdxOfEventTable()                    (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteInfoIdxOfEventTable()                     (TRUE != FALSE)
#define Dem_Cfg_HasEventTableInd()                                    (TRUE != FALSE)
#define Dem_Cfg_HasExtendedDataTable()                                (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable() (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable() (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableEdr2CollIndUsedOfExtendedDataTable() (TRUE != FALSE)
#define Dem_Cfg_HasMaxRecordSizeOfExtendedDataTable()                 (TRUE != FALSE)
#define Dem_Cfg_HasFilterInfoTable()                                  (TRUE != FALSE)
#define Dem_Cfg_HasFilterReportedEvents()                             (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameIteratorTable()                         (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameTable()                                 (TRUE != FALSE)
#define Dem_Cfg_HasRecordSizeOfFreezeFrameTable()                     (TRUE != FALSE)
#define Dem_Cfg_HasRecordSizeUdsOfFreezeFrameTable()                  (TRUE != FALSE)
#define Dem_Cfg_HasGeneralObdInput()                                  (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableIdxOfGeneralObdInput()             (TRUE != FALSE)
#define Dem_Cfg_HasGlobalSeverityMask()                               (TRUE != FALSE)
#define Dem_Cfg_HasMemoryBlockIdToMemoryEntryId()                     (TRUE != FALSE)
#define Dem_Cfg_HasMemoryCommitNumber()                               (TRUE != FALSE)
#define Dem_Cfg_HasMemoryDataPtr()                                    (TRUE != FALSE)
#define Dem_Cfg_HasMemoryDataSize()                                   (TRUE != FALSE)
#define Dem_Cfg_HasMemoryEntry()                                      (TRUE != FALSE)
#define Dem_Cfg_HasMemoryEntryInit()                                  (TRUE != FALSE)
#define Dem_Cfg_HasMemoryStatus()                                     (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryChronology()                                (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_0()                                   (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_1()                                   (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_10()                                  (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_11()                                  (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_12()                                  (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_13()                                  (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_14()                                  (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_15()                                  (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_16()                                  (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_17()                                  (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_2()                                   (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_3()                                   (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_4()                                   (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_5()                                   (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_6()                                   (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_7()                                   (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_8()                                   (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_9()                                   (TRUE != FALSE)
#define Dem_Cfg_HasReadoutBuffer()                                    (TRUE != FALSE)
#define Dem_Cfg_HasReportedEventsOfFilter()                           (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteInfo()                                    (TRUE != FALSE)
#define Dem_Cfg_HasApplicationIdOfSatelliteInfo()                     (TRUE != FALSE)
#define Dem_Cfg_HasEventCountOfSatelliteInfo()                        (TRUE != FALSE)
#define Dem_Cfg_HasEventTableIndEndIdxOfSatelliteInfo()               (TRUE != FALSE)
#define Dem_Cfg_HasEventTableIndStartIdxOfSatelliteInfo()             (TRUE != FALSE)
#define Dem_Cfg_HasEventTableIndUsedOfSatelliteInfo()                 (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteDataOfSatelliteInfo()                     (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteStatusOfSatelliteInfo()                   (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteInfo0()                                   (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClearDTCTable()                              (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClientTable()                                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDTCSelectorTable()                           (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDataElementTable()                           (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupCounter()                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupState()                  (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupTable()                  (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionState()                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionTable()                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventDebounceValue()                         (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventInternalStatus()                        (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventTable()                                 (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFilterInfoTable()                            (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFilterReportedEvents()                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFreezeFrameIteratorTable()                   (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryBlockIdToMemoryEntryId()               (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryCommitNumber()                         (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryEntry()                                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryStatus()                               (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfPrimaryChronology()                          (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfReadoutBuffer()                              (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfReportedEventsOfFilter()                     (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfSatelliteInfo()                              (TRUE != FALSE)
#define Dem_Cfg_HasStatusData()                                       (TRUE != FALSE)
#define Dem_Cfg_HasTimeSeriesEntryInit()                              (TRUE != FALSE)
#define Dem_HasPCConfig()                                             (TRUE != FALSE)
#define Dem_Cfg_HasAdminDataOfPCConfig()                              (TRUE != FALSE)
#define Dem_Cfg_HasClearDTCTableOfPCConfig()                          (TRUE != FALSE)
#define Dem_Cfg_HasClientTableOfPCConfig()                            (TRUE != FALSE)
#define Dem_Cfg_HasCommitBufferOfPCConfig()                           (TRUE != FALSE)
#define Dem_Cfg_HasConfigurationIdOfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasCycleIdTableOfPCConfig()                           (TRUE != FALSE)
#define Dem_Cfg_HasDTCSelectorTableOfPCConfig()                       (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableEdr2CollIndOfPCConfig()         (TRUE != FALSE)
#define Dem_Cfg_HasDataCollectionTableOfPCConfig()                    (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableCol2ElmtIndOfPCConfig()            (TRUE != FALSE)
#define Dem_Cfg_HasDataElementTableOfPCConfig()                       (TRUE != FALSE)
#define Dem_Cfg_HasDebounceTableOfPCConfig()                          (TRUE != FALSE)
#define Dem_Cfg_HasDtcTableOfPCConfig()                               (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupCounterOfPCConfig()            (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupStateOfPCConfig()              (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableIndOfPCConfig()           (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionGroupTableOfPCConfig()              (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionInitTableOfPCConfig()               (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionStateOfPCConfig()                   (TRUE != FALSE)
#define Dem_Cfg_HasEnableConditionTableOfPCConfig()                   (TRUE != FALSE)
#define Dem_Cfg_HasEventAvailableDefaultOfPCConfig()                  (TRUE != FALSE)
#define Dem_Cfg_HasEventAvailableInVariantOfPCConfig()                (TRUE != FALSE)
#define Dem_Cfg_HasEventDebounceValueOfPCConfig()                     (TRUE != FALSE)
#define Dem_Cfg_HasEventInternalStatusOfPCConfig()                    (TRUE != FALSE)
#define Dem_Cfg_HasEventTableIndOfPCConfig()                          (TRUE != FALSE)
#define Dem_Cfg_HasEventTableOfPCConfig()                             (TRUE != FALSE)
#define Dem_Cfg_HasExtendedDataTableOfPCConfig()                      (TRUE != FALSE)
#define Dem_Cfg_HasFilterInfoTableOfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasFilterReportedEventsOfPCConfig()                   (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameIteratorTableOfPCConfig()               (TRUE != FALSE)
#define Dem_Cfg_HasFreezeFrameTableOfPCConfig()                       (TRUE != FALSE)
#define Dem_Cfg_HasGeneralObdInputOfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasGlobalSeverityMaskOfPCConfig()                     (TRUE != FALSE)
#define Dem_Cfg_HasMemoryBlockIdToMemoryEntryIdOfPCConfig()           (TRUE != FALSE)
#define Dem_Cfg_HasMemoryCommitNumberOfPCConfig()                     (TRUE != FALSE)
#define Dem_Cfg_HasMemoryDataPtrOfPCConfig()                          (TRUE != FALSE)
#define Dem_Cfg_HasMemoryDataSizeOfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasMemoryEntryInitOfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasMemoryEntryOfPCConfig()                            (TRUE != FALSE)
#define Dem_Cfg_HasMemoryStatusOfPCConfig()                           (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryChronologyOfPCConfig()                      (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_0OfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_10OfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_11OfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_12OfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_13OfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_14OfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_15OfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_16OfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_17OfPCConfig()                        (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_1OfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_2OfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_3OfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_4OfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_5OfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_6OfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_7OfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_8OfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasPrimaryEntry_9OfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasReadoutBufferOfPCConfig()                          (TRUE != FALSE)
#define Dem_Cfg_HasReportedEventsOfFilterOfPCConfig()                 (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteInfo0OfPCConfig()                         (TRUE != FALSE)
#define Dem_Cfg_HasSatelliteInfoOfPCConfig()                          (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClearDTCTableOfPCConfig()                    (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfClientTableOfPCConfig()                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDTCSelectorTableOfPCConfig()                 (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfDataElementTableOfPCConfig()                 (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupCounterOfPCConfig()      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupStateOfPCConfig()        (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionGroupTableOfPCConfig()        (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionStateOfPCConfig()             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEnableConditionTableOfPCConfig()             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventDebounceValueOfPCConfig()               (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventInternalStatusOfPCConfig()              (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfEventTableOfPCConfig()                       (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFilterInfoTableOfPCConfig()                  (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFilterReportedEventsOfPCConfig()             (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfFreezeFrameIteratorTableOfPCConfig()         (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryBlockIdToMemoryEntryIdOfPCConfig()     (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryCommitNumberOfPCConfig()               (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryEntryOfPCConfig()                      (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfMemoryStatusOfPCConfig()                     (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfPrimaryChronologyOfPCConfig()                (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfReadoutBufferOfPCConfig()                    (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfReportedEventsOfFilterOfPCConfig()           (TRUE != FALSE)
#define Dem_Cfg_HasSizeOfSatelliteInfoOfPCConfig()                    (TRUE != FALSE)
#define Dem_Cfg_HasStatusDataOfPCConfig()                             (TRUE != FALSE)
#define Dem_Cfg_HasTimeSeriesEntryInitOfPCConfig()                    (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCIncrementDataMacros  Dem_Cfg Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define Dem_Cfg_IncClearDTCTable(Index)                               Dem_Cfg_GetClearDTCTable(Index)++
#define Dem_Cfg_IncDTCSelectorTable(Index)                            Dem_Cfg_GetDTCSelectorTable(Index)++
#define Dem_Cfg_IncEnableConditionGroupCounter(Index)                 Dem_Cfg_GetEnableConditionGroupCounter(Index)++
#define Dem_Cfg_IncEnableConditionGroupState(Index)                   Dem_Cfg_GetEnableConditionGroupState(Index)++
#define Dem_Cfg_IncEnableConditionState(Index)                        Dem_Cfg_GetEnableConditionState(Index)++
#define Dem_Cfg_IncEventDebounceValue(Index)                          Dem_Cfg_GetEventDebounceValue(Index)++
#define Dem_Cfg_IncEventInternalStatus(Index)                         Dem_Cfg_GetEventInternalStatus(Index)++
#define Dem_Cfg_IncFilterInfoTable(Index)                             Dem_Cfg_GetFilterInfoTable(Index)++
#define Dem_Cfg_IncFilterReportedEvents(Index)                        Dem_Cfg_GetFilterReportedEvents(Index)++
#define Dem_Cfg_IncFreezeFrameIteratorTable(Index)                    Dem_Cfg_GetFreezeFrameIteratorTable(Index)++
#define Dem_Cfg_IncMemoryCommitNumber(Index)                          Dem_Cfg_GetMemoryCommitNumber(Index)++
#define Dem_Cfg_IncMemoryStatus(Index)                                Dem_Cfg_GetMemoryStatus(Index)++
#define Dem_Cfg_IncPrimaryChronology(Index)                           Dem_Cfg_GetPrimaryChronology(Index)++
#define Dem_Cfg_IncReadoutBuffer(Index)                               Dem_Cfg_GetReadoutBuffer(Index)++
#define Dem_Cfg_IncReportedEventsOfFilter(Index)                      Dem_Cfg_GetReportedEventsOfFilter(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCDecrementDataMacros  Dem_Cfg Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define Dem_Cfg_DecClearDTCTable(Index)                               Dem_Cfg_GetClearDTCTable(Index)--
#define Dem_Cfg_DecDTCSelectorTable(Index)                            Dem_Cfg_GetDTCSelectorTable(Index)--
#define Dem_Cfg_DecEnableConditionGroupCounter(Index)                 Dem_Cfg_GetEnableConditionGroupCounter(Index)--
#define Dem_Cfg_DecEnableConditionGroupState(Index)                   Dem_Cfg_GetEnableConditionGroupState(Index)--
#define Dem_Cfg_DecEnableConditionState(Index)                        Dem_Cfg_GetEnableConditionState(Index)--
#define Dem_Cfg_DecEventDebounceValue(Index)                          Dem_Cfg_GetEventDebounceValue(Index)--
#define Dem_Cfg_DecEventInternalStatus(Index)                         Dem_Cfg_GetEventInternalStatus(Index)--
#define Dem_Cfg_DecFilterInfoTable(Index)                             Dem_Cfg_GetFilterInfoTable(Index)--
#define Dem_Cfg_DecFilterReportedEvents(Index)                        Dem_Cfg_GetFilterReportedEvents(Index)--
#define Dem_Cfg_DecFreezeFrameIteratorTable(Index)                    Dem_Cfg_GetFreezeFrameIteratorTable(Index)--
#define Dem_Cfg_DecMemoryCommitNumber(Index)                          Dem_Cfg_GetMemoryCommitNumber(Index)--
#define Dem_Cfg_DecMemoryStatus(Index)                                Dem_Cfg_GetMemoryStatus(Index)--
#define Dem_Cfg_DecPrimaryChronology(Index)                           Dem_Cfg_GetPrimaryChronology(Index)--
#define Dem_Cfg_DecReadoutBuffer(Index)                               Dem_Cfg_GetReadoutBuffer(Index)--
#define Dem_Cfg_DecReportedEventsOfFilter(Index)                      Dem_Cfg_GetReportedEventsOfFilter(Index)--
/** 
  \}
*/ 

  /* PRQA L:MACROS_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 MACROS_3453 */  /* MD_CSL_3453 */
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:MACROS_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/



/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
 /*  Return type of Dem_Cfg_EventIndicatorIterGet() - returns: eventIndicatorIndex  */ 
typedef uint8                                                         Dem_Cfg_IndicatorIndexType; 

typedef volatile P2VAR(Dem_Com_ProcessorWordType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_ProcessorWordPtrType; 

typedef volatile P2VAR(Dem_SatelliteData_DataType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_SatelliteDataPtrType; 

typedef struct Dem_Cfg_SatelliteInfoType0_s {
  volatile Dem_SatelliteData_DataType SatelliteData[ 22 ];
  volatile Dem_Com_ProcessorWordType  SatelliteStatus;
}                                                                     Dem_Cfg_SatelliteInfoType0;            /* Data structure for DEM satellite on partition "0" */ 

typedef struct Dem_Cfg_AdminDataType_s {
  uint16 ImplementationVersion;
  uint16 ConfigurationId;
  uint16 CycleCounter[ 4 /*DEM_CFG_GLOBAL_CYCLE_COUNT*/];
  uint8  MemoryOverflow;                                                        /* (DEM_CFG_DATA_OVFLIND == STD_ON) || (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON) */
}                                                                     Dem_Cfg_AdminDataType; 

typedef struct Dem_Cfg_StatusDataType_s {
  uint16         FirstFailedEvent;
  uint16         FirstConfirmedEvent;
  uint16         MostRecentFailedEvent;
  uint16         MostRecentConfmdEvent;
  volatile uint8 EventStatus[ 22 /*DEM_G_NUMBER_OF_EVENTS (incl. #0)*/];
}                                                                     Dem_Cfg_StatusDataType; 

typedef struct Dem_Cfg_PrimaryEntryType_s {
  uint32 Timestamp;
  uint16 AgingCounter;
  uint16 EventId;
  uint8  ExtendedData[ 5 /*DEM_CFG_MAX_NUM_EXT_RECORDS*/][ 6 /*DEM_CFG_MAX_SIZE_EXT_RECORD*/];  /* (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) */
  uint8  ExtendedHeader;                                                                        /* (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) */
}                                                                     Dem_Cfg_PrimaryEntryType; 

typedef P2VAR(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_SHARED_DATA)     Dem_SharedMemoryEntryPtrType; 

typedef P2CONST(Dem_Cfg_PrimaryEntryType, TYPEDEF, DEM_SHARED_DATA)   Dem_ConstSharedMemoryEntryPtrType; 

typedef struct Dem_Cfg_TimeSeriesEntryType_s {
  uint32 Timestamp;
  uint16 EventId;
}                                                                     Dem_Cfg_TimeSeriesEntryType; 

typedef uint8                                                         Dem_Cfg_MemoryIndexType;               /* Number of NV blocks, see Dem_Cfg_GlobalNvBlockCount(). */ 

typedef uint8                                                         Dem_Cfg_DtrStatusType; 

typedef Dem_Com_ProcessorWordType                                     Dem_Cfg_ReportedEventsType[1];         /* size: [ceiling( DEM_G_NUMBER_OF_EVENTS / 32 )] = (((DEM_G_NUMBER_OF_EVENTS - 1) / 32) + 1), here: 1. See define DEM_CFG_GLOBAL_PROCESSORWORDS_PER_REPORTEDEVENTSTYPE */ 

typedef uint16                                                        Dem_Cfg_IndicatorContinuousType[1];    /* size = DEM_G_MAX_NUMBER_J1939_NODES */ 

typedef uint16                                                        Dem_Cfg_IndicatorBlinkingType[1];      /* size = DEM_G_MAX_NUMBER_J1939_NODES */ 

typedef uint16                                                        Dem_Cfg_IndicatorFastFlashType[1];     /* size = DEM_G_MAX_NUMBER_J1939_NODES */ 

typedef uint16                                                        Dem_Cfg_IndicatorSlowFlashType[1];     /* size = DEM_G_MAX_NUMBER_J1939_NODES */ 

typedef uint8                                                         Dem_Cfg_GlobalIndicatorStatesType[1];    /* size = DEM_G_MAX_NUMBER_J1939_NODES */ 

 /*  Temporary buffer for interaction with NvM  */ 
typedef union Dem_Cfg_CommitBufferType_u { /* PRQA S 0750 */ /* MD_MSR_18.4 */
  uint8                    mRaw[ 1 ];
  Dem_Cfg_AdminDataType    mAdmin;
  Dem_Cfg_StatusDataType   mStatus;
  Dem_Cfg_PrimaryEntryType mPrimary;
}                                                                     Dem_Cfg_CommitBufferType; 

 /*  Buffer for Event Data, used after calling Dem_DisableDTCRecordUpdate().  */ 
typedef struct Dem_Cfg_ReadoutBufferEntryType_s {
  Dem_Cfg_PrimaryEntryType                      Data;                           /* Backed event data */
  Dem_DTCReadoutBuffer_ExtendedDataIteratorType ExtendedIterator;               /* Internal state for reporting ExtendedData record(s) */
  Dem_DTCReadoutBuffer_SnapshotDataIteratorType SnapshotIterator;               /* Internal state for reporting SnapshotData record(s) */
  uint16                                        EventId;                        /* EventId of this Data record */
  uint8                                         MemoryId;                       /* MemoryId of this Data record */
  uint8                                         State;                          /* Internal state of this buffer, see Dem_DTCReadoutBuffer_StatusType */
}                                                                     Dem_Cfg_ReadoutBufferEntryType; 

typedef P2VAR(Dem_Cfg_ReadoutBufferEntryType, TYPEDEF, DEM_VAR_NOINIT) Dem_Cfg_ReadoutBufferEntryPtrType; 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  Dem_CfgPCIterableTypes  Dem_Cfg Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate Dem_Cfg_ClearDTCTable */
typedef uint8_least Dem_Cfg_ClearDTCTableIterType;

/**   \brief  type used to iterate Dem_Cfg_ClientTable */
typedef uint8_least Dem_Cfg_ClientTableIterType;

/**   \brief  type used to iterate Dem_Cfg_CycleIdTable */
typedef uint8_least Dem_Cfg_CycleIdTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DTCSelectorTable */
typedef uint8_least Dem_Cfg_DTCSelectorTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DataCollectionTable */
typedef uint8_least Dem_Cfg_DataCollectionTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DataCollectionTableEdr2CollInd */
typedef uint8_least Dem_Cfg_DataCollectionTableEdr2CollIndIterType;

/**   \brief  type used to iterate Dem_Cfg_DataElementTable */
typedef uint8_least Dem_Cfg_DataElementTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DataElementTableCol2ElmtInd */
typedef uint8_least Dem_Cfg_DataElementTableCol2ElmtIndIterType;

/**   \brief  type used to iterate Dem_Cfg_DebounceTable */
typedef uint8_least Dem_Cfg_DebounceTableIterType;

/**   \brief  type used to iterate Dem_Cfg_DtcTable */
typedef uint8_least Dem_Cfg_DtcTableIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionGroupTable */
typedef uint8_least Dem_Cfg_EnableConditionGroupTableIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionGroupTableInd */
typedef uint8_least Dem_Cfg_EnableConditionGroupTableIndIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionInitTable */
typedef uint8_least Dem_Cfg_EnableConditionInitTableIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionTable */
typedef uint8_least Dem_Cfg_EnableConditionTableIterType;

/**   \brief  type used to iterate Dem_Cfg_EventAvailableDefault */
typedef uint8_least Dem_Cfg_EventAvailableDefaultIterType;

/**   \brief  type used to iterate Dem_Cfg_EventAvailableInVariant */
typedef uint8_least Dem_Cfg_EventAvailableInVariantIterType;

/**   \brief  type used to iterate Dem_Cfg_EventTable */
typedef uint8_least Dem_Cfg_EventTableIterType;

/**   \brief  type used to iterate Dem_Cfg_EventTableInd */
typedef uint8_least Dem_Cfg_EventTableIndIterType;

/**   \brief  type used to iterate Dem_Cfg_ExtendedDataTable */
typedef uint8_least Dem_Cfg_ExtendedDataTableIterType;

/**   \brief  type used to iterate Dem_Cfg_FilterInfoTable */
typedef uint8_least Dem_Cfg_FilterInfoTableIterType;

/**   \brief  type used to iterate Dem_Cfg_FilterReportedEvents */
typedef uint8_least Dem_Cfg_FilterReportedEventsIterType;

/**   \brief  type used to iterate Dem_Cfg_FreezeFrameIteratorTable */
typedef uint8_least Dem_Cfg_FreezeFrameIteratorTableIterType;

/**   \brief  type used to iterate Dem_Cfg_FreezeFrameTable */
typedef uint8_least Dem_Cfg_FreezeFrameTableIterType;

/**   \brief  type used to iterate Dem_Cfg_GeneralObdInput */
typedef uint8_least Dem_Cfg_GeneralObdInputIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryBlockIdToMemoryEntryId */
typedef uint8_least Dem_Cfg_MemoryBlockIdToMemoryEntryIdIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryCommitNumber */
typedef uint8_least Dem_Cfg_MemoryCommitNumberIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryDataPtr */
typedef uint8_least Dem_Cfg_MemoryDataPtrIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryDataSize */
typedef uint8_least Dem_Cfg_MemoryDataSizeIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryEntry */
typedef uint8_least Dem_Cfg_MemoryEntryIterType;

/**   \brief  type used to iterate Dem_Cfg_MemoryStatus */
typedef uint8_least Dem_Cfg_MemoryStatusIterType;

/**   \brief  type used to iterate Dem_Cfg_PrimaryChronology */
typedef uint8_least Dem_Cfg_PrimaryChronologyIterType;

/**   \brief  type used to iterate Dem_Cfg_ReadoutBuffer */
typedef uint8_least Dem_Cfg_ReadoutBufferIterType;

/**   \brief  type used to iterate Dem_Cfg_ReportedEventsOfFilter */
typedef uint8_least Dem_Cfg_ReportedEventsOfFilterIterType;

/**   \brief  type used to iterate Dem_Cfg_SatelliteInfo */
typedef uint8_least Dem_Cfg_SatelliteInfoIterType;

/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCIterableTypesWithSizeRelations  Dem_Cfg Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate Dem_Cfg_EnableConditionGroupCounter */
typedef Dem_Cfg_EnableConditionGroupTableIterType Dem_Cfg_EnableConditionGroupCounterIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionGroupState */
typedef Dem_Cfg_EnableConditionGroupTableIterType Dem_Cfg_EnableConditionGroupStateIterType;

/**   \brief  type used to iterate Dem_Cfg_EnableConditionState */
typedef Dem_Cfg_EnableConditionTableIterType Dem_Cfg_EnableConditionStateIterType;

/**   \brief  type used to iterate Dem_Cfg_EventDebounceValue */
typedef Dem_Cfg_EventTableIterType Dem_Cfg_EventDebounceValueIterType;

/**   \brief  type used to iterate Dem_Cfg_EventInternalStatus */
typedef Dem_Cfg_EventTableIterType Dem_Cfg_EventInternalStatusIterType;

/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCValueTypes  Dem_Cfg Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for Dem_Cfg_ClearDTCIndexOfClientTable */
typedef uint8 Dem_Cfg_ClearDTCIndexOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_FilterIndexOfClientTable */
typedef uint8 Dem_Cfg_FilterIndexOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_FreezeFrameIteratorIndexOfClientTable */
typedef uint8 Dem_Cfg_FreezeFrameIteratorIndexOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_ReadoutBufferIndexOfClientTable */
typedef uint8 Dem_Cfg_ReadoutBufferIndexOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_SelectorIndexOfClientTable */
typedef uint8 Dem_Cfg_SelectorIndexOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_ConfigurationId */
typedef uint16 Dem_Cfg_ConfigurationIdType;

/**   \brief  value based type definition for Dem_Cfg_OpCycleTypeOfCycleIdTable */
typedef uint8 Dem_Cfg_OpCycleTypeOfCycleIdTableType;

/**   \brief  value based type definition for Dem_Cfg_UsedForAgingOfCycleIdTable */
typedef boolean Dem_Cfg_UsedForAgingOfCycleIdTableType;

/**   \brief  value based type definition for Dem_Cfg_CollectionSizeOfDataCollectionTable */
typedef uint8 Dem_Cfg_CollectionSizeOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_DataElementTableCol2ElmtIndEndIdxOfDataCollectionTable */
typedef uint8 Dem_Cfg_DataElementTableCol2ElmtIndEndIdxOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_DataElementTableCol2ElmtIndStartIdxOfDataCollectionTable */
typedef uint8 Dem_Cfg_DataElementTableCol2ElmtIndStartIdxOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_DataElementTableCol2ElmtIndUsedOfDataCollectionTable */
typedef boolean Dem_Cfg_DataElementTableCol2ElmtIndUsedOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_IdNumberOfDataCollectionTable */
typedef uint8 Dem_Cfg_IdNumberOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_MaskedBitsOfDataCollectionTable */
typedef uint8 Dem_Cfg_MaskedBitsOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_StorageKindOfDataCollectionTable */
typedef uint8 Dem_Cfg_StorageKindOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_UpdateOfDataCollectionTable */
typedef boolean Dem_Cfg_UpdateOfDataCollectionTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableEdr2CollInd */
typedef uint8 Dem_Cfg_DataCollectionTableEdr2CollIndType;

/**   \brief  value based type definition for Dem_Cfg_DataIsStoredInNVOfDataElementTable */
typedef boolean Dem_Cfg_DataIsStoredInNVOfDataElementTableType;

/**   \brief  value based type definition for Dem_Cfg_ElementKindOfDataElementTable */
typedef uint8 Dem_Cfg_ElementKindOfDataElementTableType;

/**   \brief  value based type definition for Dem_Cfg_ElementSizeOfDataElementTable */
typedef uint8 Dem_Cfg_ElementSizeOfDataElementTableType;

/**   \brief  value based type definition for Dem_Cfg_DataElementTableCol2ElmtInd */
typedef uint8 Dem_Cfg_DataElementTableCol2ElmtIndType;

/**   \brief  value based type definition for Dem_Cfg_DebounceContinuousOfDebounceTable */
typedef boolean Dem_Cfg_DebounceContinuousOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_DecrementStepSizeOfDebounceTable */
typedef sint8 Dem_Cfg_DecrementStepSizeOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_EventDebounceAlgorithmOfDebounceTable */
typedef uint8 Dem_Cfg_EventDebounceAlgorithmOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_EventDebounceBehaviorOfDebounceTable */
typedef boolean Dem_Cfg_EventDebounceBehaviorOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_FailTimerCyclesOfDebounceTable */
typedef sint8 Dem_Cfg_FailTimerCyclesOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_FailedThresholdOfDebounceTable */
typedef sint8 Dem_Cfg_FailedThresholdOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_IncrementStepSizeOfDebounceTable */
typedef sint8 Dem_Cfg_IncrementStepSizeOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_JumpDownOfDebounceTable */
typedef boolean Dem_Cfg_JumpDownOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_JumpDownValueOfDebounceTable */
typedef sint8 Dem_Cfg_JumpDownValueOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_JumpUpOfDebounceTable */
typedef boolean Dem_Cfg_JumpUpOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_JumpUpValueOfDebounceTable */
typedef sint8 Dem_Cfg_JumpUpValueOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_MaskedBitsOfDebounceTable */
typedef uint8 Dem_Cfg_MaskedBitsOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_PassTimerCyclesOfDebounceTable */
typedef sint8 Dem_Cfg_PassTimerCyclesOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_PassedThresholdOfDebounceTable */
typedef sint8 Dem_Cfg_PassedThresholdOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_StorageOfDebounceTable */
typedef boolean Dem_Cfg_StorageOfDebounceTableType;

/**   \brief  value based type definition for Dem_Cfg_DtcSeverityOfDtcTable */
typedef uint8 Dem_Cfg_DtcSeverityOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_FunctionalUnitOfDtcTable */
typedef uint8 Dem_Cfg_FunctionalUnitOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_ImmediateNvStorageOfDtcTable */
typedef boolean Dem_Cfg_ImmediateNvStorageOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_UdsDtcOfDtcTable */
typedef uint32 Dem_Cfg_UdsDtcOfDtcTableType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupCounter */
typedef uint8 Dem_Cfg_EnableConditionGroupCounterType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupState */
typedef uint8 Dem_Cfg_EnableConditionGroupStateType;

/**   \brief  value based type definition for Dem_Cfg_IndexOfEnableConditionGroupTable */
typedef uint8 Dem_Cfg_IndexOfEnableConditionGroupTableType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupTableInd */
typedef uint8 Dem_Cfg_EnableConditionGroupTableIndType;

/**   \brief  value based type definition for Dem_Cfg_InitValueOfEnableConditionInitTable */
typedef uint8 Dem_Cfg_InitValueOfEnableConditionInitTableType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionState */
typedef uint8 Dem_Cfg_EnableConditionStateType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupTableIndEndIdxOfEnableConditionTable */
typedef uint8 Dem_Cfg_EnableConditionGroupTableIndEndIdxOfEnableConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupTableIndStartIdxOfEnableConditionTable */
typedef uint8 Dem_Cfg_EnableConditionGroupTableIndStartIdxOfEnableConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupTableIndUsedOfEnableConditionTable */
typedef boolean Dem_Cfg_EnableConditionGroupTableIndUsedOfEnableConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_EventAvailableDefault */
typedef boolean Dem_Cfg_EventAvailableDefaultType;

/**   \brief  value based type definition for Dem_Cfg_EventAvailableInVariant */
typedef boolean Dem_Cfg_EventAvailableInVariantType;

/**   \brief  value based type definition for Dem_Cfg_EventDebounceValue */
typedef sint16 Dem_Cfg_EventDebounceValueType;

/**   \brief  value based type definition for Dem_Cfg_AgingAllowedOfEventTable */
typedef boolean Dem_Cfg_AgingAllowedOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_AgingCycleCounterThresholdOfEventTable */
typedef uint8 Dem_Cfg_AgingCycleCounterThresholdOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_AgingCycleIdOfEventTable */
typedef uint8 Dem_Cfg_AgingCycleIdOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_DebounceTableIdxOfEventTable */
typedef uint8 Dem_Cfg_DebounceTableIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_DtcTableIdxOfEventTable */
typedef uint8 Dem_Cfg_DtcTableIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EnableConditionGroupTableIdxOfEventTable */
typedef uint8 Dem_Cfg_EnableConditionGroupTableIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventDestinationOfEventTable */
typedef uint8 Dem_Cfg_EventDestinationOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventFailureCycleCounterThresholdOfEventTable */
typedef uint8 Dem_Cfg_EventFailureCycleCounterThresholdOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventKindOfEventTable */
typedef uint8 Dem_Cfg_EventKindOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventLatchTFOfEventTable */
typedef boolean Dem_Cfg_EventLatchTFOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventPriorityOfEventTable */
typedef uint8 Dem_Cfg_EventPriorityOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventSignificanceOfEventTable */
typedef uint8 Dem_Cfg_EventSignificanceOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_ExtendedDataTableIdxOfEventTable */
typedef uint8 Dem_Cfg_ExtendedDataTableIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_FreezeFrameTableStdFFIdxOfEventTable */
typedef uint8 Dem_Cfg_FreezeFrameTableStdFFIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_HealingTargetOfEventTable */
typedef uint8 Dem_Cfg_HealingTargetOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_MaskedBitsOfEventTable */
typedef uint8 Dem_Cfg_MaskedBitsOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_OperationCycleIdOfEventTable */
typedef uint8 Dem_Cfg_OperationCycleIdOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_SatelliteEventIdxOfEventTable */
typedef uint8 Dem_Cfg_SatelliteEventIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_SatelliteInfoIdxOfEventTable */
typedef uint8 Dem_Cfg_SatelliteInfoIdxOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_EventTableInd */
typedef uint8 Dem_Cfg_EventTableIndType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable */
typedef uint8 Dem_Cfg_DataCollectionTableEdr2CollIndEndIdxOfExtendedDataTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable */
typedef uint8 Dem_Cfg_DataCollectionTableEdr2CollIndStartIdxOfExtendedDataTableType;

/**   \brief  value based type definition for Dem_Cfg_DataCollectionTableEdr2CollIndUsedOfExtendedDataTable */
typedef boolean Dem_Cfg_DataCollectionTableEdr2CollIndUsedOfExtendedDataTableType;

/**   \brief  value based type definition for Dem_Cfg_MaxRecordSizeOfExtendedDataTable */
typedef uint8 Dem_Cfg_MaxRecordSizeOfExtendedDataTableType;

/**   \brief  value based type definition for Dem_Cfg_FilterReportedEvents */
typedef uint8 Dem_Cfg_FilterReportedEventsType;

/**   \brief  value based type definition for Dem_Cfg_RecordSizeOfFreezeFrameTable */
typedef uint8 Dem_Cfg_RecordSizeOfFreezeFrameTableType;

/**   \brief  value based type definition for Dem_Cfg_RecordSizeUdsOfFreezeFrameTable */
typedef uint8 Dem_Cfg_RecordSizeUdsOfFreezeFrameTableType;

/**   \brief  value based type definition for Dem_Cfg_DataElementTableIdxOfGeneralObdInput */
typedef uint8 Dem_Cfg_DataElementTableIdxOfGeneralObdInputType;

/**   \brief  value based type definition for Dem_Cfg_GlobalSeverityMask */
typedef uint8 Dem_Cfg_GlobalSeverityMaskType;

/**   \brief  value based type definition for Dem_Cfg_MemoryCommitNumber */
typedef uint8 Dem_Cfg_MemoryCommitNumberType;

/**   \brief  value based type definition for Dem_Cfg_MemoryDataSize */
typedef uint16 Dem_Cfg_MemoryDataSizeType;

/**   \brief  value based type definition for Dem_Cfg_MemoryStatus */
typedef uint8 Dem_Cfg_MemoryStatusType;

/**   \brief  value based type definition for Dem_Cfg_EventCountOfSatelliteInfo */
typedef uint8 Dem_Cfg_EventCountOfSatelliteInfoType;

/**   \brief  value based type definition for Dem_Cfg_EventTableIndEndIdxOfSatelliteInfo */
typedef uint8 Dem_Cfg_EventTableIndEndIdxOfSatelliteInfoType;

/**   \brief  value based type definition for Dem_Cfg_EventTableIndStartIdxOfSatelliteInfo */
typedef uint8 Dem_Cfg_EventTableIndStartIdxOfSatelliteInfoType;

/**   \brief  value based type definition for Dem_Cfg_EventTableIndUsedOfSatelliteInfo */
typedef boolean Dem_Cfg_EventTableIndUsedOfSatelliteInfoType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfClearDTCTable */
typedef uint8 Dem_Cfg_SizeOfClearDTCTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfClientTable */
typedef uint8 Dem_Cfg_SizeOfClientTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfDTCSelectorTable */
typedef uint8 Dem_Cfg_SizeOfDTCSelectorTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfDataElementTable */
typedef uint8 Dem_Cfg_SizeOfDataElementTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEnableConditionGroupCounter */
typedef uint8 Dem_Cfg_SizeOfEnableConditionGroupCounterType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEnableConditionGroupState */
typedef uint8 Dem_Cfg_SizeOfEnableConditionGroupStateType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEnableConditionGroupTable */
typedef uint8 Dem_Cfg_SizeOfEnableConditionGroupTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEnableConditionState */
typedef uint8 Dem_Cfg_SizeOfEnableConditionStateType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEnableConditionTable */
typedef uint8 Dem_Cfg_SizeOfEnableConditionTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEventDebounceValue */
typedef uint8 Dem_Cfg_SizeOfEventDebounceValueType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEventInternalStatus */
typedef uint8 Dem_Cfg_SizeOfEventInternalStatusType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfEventTable */
typedef uint8 Dem_Cfg_SizeOfEventTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfFilterInfoTable */
typedef uint8 Dem_Cfg_SizeOfFilterInfoTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfFilterReportedEvents */
typedef uint8 Dem_Cfg_SizeOfFilterReportedEventsType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfFreezeFrameIteratorTable */
typedef uint8 Dem_Cfg_SizeOfFreezeFrameIteratorTableType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfMemoryBlockIdToMemoryEntryId */
typedef uint8 Dem_Cfg_SizeOfMemoryBlockIdToMemoryEntryIdType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfMemoryCommitNumber */
typedef uint8 Dem_Cfg_SizeOfMemoryCommitNumberType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfMemoryEntry */
typedef uint8 Dem_Cfg_SizeOfMemoryEntryType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfMemoryStatus */
typedef uint8 Dem_Cfg_SizeOfMemoryStatusType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfPrimaryChronology */
typedef uint8 Dem_Cfg_SizeOfPrimaryChronologyType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfReadoutBuffer */
typedef uint8 Dem_Cfg_SizeOfReadoutBufferType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfReportedEventsOfFilter */
typedef uint8 Dem_Cfg_SizeOfReportedEventsOfFilterType;

/**   \brief  value based type definition for Dem_Cfg_SizeOfSatelliteInfo */
typedef uint8 Dem_Cfg_SizeOfSatelliteInfoType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  Dem_CfgPCStructTypes  Dem_Cfg Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in Dem_Cfg_ClientTable */
typedef struct sDem_Cfg_ClientTableType
{
  uint8 Dem_Cfg_ClientTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_ClientTableType;

/**   \brief  type used in Dem_Cfg_CycleIdTable */
typedef struct sDem_Cfg_CycleIdTableType
{
  Dem_Cfg_UsedForAgingOfCycleIdTableType UsedForAgingOfCycleIdTable;  /**< DemOperationCycle is target of any DemEventParameter/DemEventClass/DemAgingCycleRef */
  Dem_Cfg_OpCycleTypeOfCycleIdTableType OpCycleTypeOfCycleIdTable;  /**< DemOperationCycleType of the DemOperationCycle: [DEM_CFG_OPCYC_IGNITION, DEM_CFG_OPCYC_OBD_DCY, DEM_CFG_OPCYC_OTHER, DEM_CFG_OPCYC_POWER, DEM_CFG_OPCYC_TIME, DEM_CFG_OPCYC_WARMUP, DEM_CFG_OPCYC_IGNITION_HYBRID, DEM_CFG_OPCYC_AGING] */
} Dem_Cfg_CycleIdTableType;

/**   \brief  type used in Dem_Cfg_DataCollectionTable */
typedef struct sDem_Cfg_DataCollectionTableType
{
  Dem_Cfg_CollectionSizeOfDataCollectionTableType CollectionSizeOfDataCollectionTable;
  Dem_Cfg_DataElementTableCol2ElmtIndEndIdxOfDataCollectionTableType DataElementTableCol2ElmtIndEndIdxOfDataCollectionTable;  /**< the end index of the 0:n relation pointing to Dem_Cfg_DataElementTableCol2ElmtInd */
  Dem_Cfg_DataElementTableCol2ElmtIndStartIdxOfDataCollectionTableType DataElementTableCol2ElmtIndStartIdxOfDataCollectionTable;  /**< the start index of the 0:n relation pointing to Dem_Cfg_DataElementTableCol2ElmtInd */
  Dem_Cfg_IdNumberOfDataCollectionTableType IdNumberOfDataCollectionTable;
  Dem_Cfg_MaskedBitsOfDataCollectionTableType MaskedBitsOfDataCollectionTable;  /**< contains bitcoded the boolean data of Dem_Cfg_DataElementTableCol2ElmtIndUsedOfDataCollectionTable, Dem_Cfg_UpdateOfDataCollectionTable */
  Dem_Cfg_StorageKindOfDataCollectionTableType StorageKindOfDataCollectionTable;
} Dem_Cfg_DataCollectionTableType;

/**   \brief  type used in Dem_Cfg_DataElementTable */
typedef struct sDem_Cfg_DataElementTableType
{
  Dem_Cfg_ElementKindOfDataElementTableType ElementKindOfDataElementTable;  /**< DataElement kind, returned by Dem_Cfg_DataCallbackType() */
  Dem_Cfg_ElementSizeOfDataElementTableType ElementSizeOfDataElementTable;  /**< Size of data element in Byte. */
  Dem_ReadDataFPtrType ReadDataFuncOfDataElementTable;  /**< C-function for getting the data. Its signature depends on ElementKind: With value(s) DEM_CFG_DATA_FROM_CBK_WITH_EVENTID use: Std_ReturnType (*)(uint8* Buffer, uint16 EventId); - and use: Std_ReturnType (*)(uint8* Buffer); with the other values DEM_CFG_DATA_FROM_CBK, DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN, DEM_CFG_DATA_FROM_SR_PORT_SINT16, DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL, DEM_CFG_DATA_FROM_SR_PORT_SINT32, DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL, DEM_CFG_DATA_FROM_SR_PORT_SINT8, DEM_CFG_DATA_FROM_SR_PORT_SINT8_N, DEM_CFG_DATA_FROM_SR_PORT_UINT16, DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL, DEM_CFG_DATA_FROM_SR_PORT_UINT32, DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL, DEM_CFG_DATA_FROM_SR_PORT_UINT8, DEM_CFG_DATA_FROM_SR_PORT_UINT8_N. */
} Dem_Cfg_DataElementTableType;

/**   \brief  type used in Dem_Cfg_DebounceTable */
typedef struct sDem_Cfg_DebounceTableType
{
  Dem_Cfg_DecrementStepSizeOfDebounceTableType DecrementStepSizeOfDebounceTable;  /**< (-1) * DemDebounceCounterDecrementStepSize of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
  Dem_Cfg_FailedThresholdOfDebounceTableType FailedThresholdOfDebounceTable;  /**< DemDebounceCounterFailedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
  Dem_Cfg_IncrementStepSizeOfDebounceTableType IncrementStepSizeOfDebounceTable;  /**< DemDebounceCounterIncrementStepSize of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
  Dem_Cfg_PassedThresholdOfDebounceTableType PassedThresholdOfDebounceTable;  /**< DemDebounceCounterPassedThreshold of the DemEventParameter/DemEventClass/DemDebounceAlgorithmClass/DemDebounceCounterBased */
  Dem_Cfg_EventDebounceAlgorithmOfDebounceTableType EventDebounceAlgorithmOfDebounceTable;  /**< Used DemEventParameter/DemEventClass/DemDebounceAlgorithmClass */
  Dem_Cfg_MaskedBitsOfDebounceTableType MaskedBitsOfDebounceTable;  /**< contains bitcoded the boolean data of Dem_Cfg_DebounceContinuousOfDebounceTable, Dem_Cfg_EventDebounceBehaviorOfDebounceTable, Dem_Cfg_JumpDownOfDebounceTable, Dem_Cfg_JumpUpOfDebounceTable, Dem_Cfg_StorageOfDebounceTable */
} Dem_Cfg_DebounceTableType;

/**   \brief  type used in Dem_Cfg_DtcTable */
typedef struct sDem_Cfg_DtcTableType
{
  Dem_Cfg_UdsDtcOfDtcTableType UdsDtcOfDtcTable;
  Dem_Cfg_FunctionalUnitOfDtcTableType FunctionalUnitOfDtcTable;
} Dem_Cfg_DtcTableType;

/**   \brief  type used in Dem_Cfg_EnableConditionGroupTable */
typedef struct sDem_Cfg_EnableConditionGroupTableType
{
  uint8 Dem_Cfg_EnableConditionGroupTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_EnableConditionGroupTableType;

/**   \brief  type used in Dem_Cfg_EnableConditionInitTable */
typedef struct sDem_Cfg_EnableConditionInitTableType
{
  uint8 Dem_Cfg_EnableConditionInitTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_EnableConditionInitTableType;

/**   \brief  type used in Dem_Cfg_EnableConditionTable */
typedef struct sDem_Cfg_EnableConditionTableType
{
  uint8 Dem_Cfg_EnableConditionTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_EnableConditionTableType;

/**   \brief  type used in Dem_Cfg_EventTable */
typedef struct sDem_Cfg_EventTableType
{
  Dem_Cfg_AgingCycleIdOfEventTableType AgingCycleIdOfEventTable;  /**< DemOperationCycle (ID) referenced by DemEventParameter/DemEventClass/DemAgingCycleRef */
  Dem_Cfg_DtcTableIdxOfEventTableType DtcTableIdxOfEventTable;  /**< the index of the 1:1 relation pointing to Dem_Cfg_DtcTable */
  Dem_Cfg_ExtendedDataTableIdxOfEventTableType ExtendedDataTableIdxOfEventTable;  /**< the index of the 1:1 relation pointing to Dem_Cfg_ExtendedDataTable */
  Dem_Cfg_OperationCycleIdOfEventTableType OperationCycleIdOfEventTable;  /**< DemOperationCycle (ID) referenced by DemEventParameter/DemEventClass/DemOperationCycleRef */
} Dem_Cfg_EventTableType;

/**   \brief  type used in Dem_Cfg_ExtendedDataTable */
typedef struct sDem_Cfg_ExtendedDataTableType
{
  Dem_Cfg_DataCollectionTableEdr2CollIndEndIdxOfExtendedDataTableType DataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable;  /**< the end index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableEdr2CollInd */
  Dem_Cfg_DataCollectionTableEdr2CollIndStartIdxOfExtendedDataTableType DataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable;  /**< the start index of the 0:n relation pointing to Dem_Cfg_DataCollectionTableEdr2CollInd */
  Dem_Cfg_MaxRecordSizeOfExtendedDataTableType MaxRecordSizeOfExtendedDataTable;
} Dem_Cfg_ExtendedDataTableType;

/**   \brief  type used in Dem_Cfg_FreezeFrameTable */
typedef struct sDem_Cfg_FreezeFrameTableType
{
  uint8 Dem_Cfg_FreezeFrameTableNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_FreezeFrameTableType;

/**   \brief  type used in Dem_Cfg_GeneralObdInput */
typedef struct sDem_Cfg_GeneralObdInputType
{
  uint8 Dem_Cfg_GeneralObdInputNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_GeneralObdInputType;

/**   \brief  type used in Dem_Cfg_SatelliteInfo */
typedef struct sDem_Cfg_SatelliteInfoType
{
  uint8 Dem_Cfg_SatelliteInfoNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_Cfg_SatelliteInfoType;

/** 
  \}
*/ 

/** 
  \defgroup  Dem_CfgPCRootValueTypes  Dem_Cfg Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in Dem_PCConfig */
typedef struct sDem_PCConfigType
{
  uint8 Dem_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Dem_PCConfigType;

typedef Dem_PCConfigType Dem_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
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
extern CONST(Dem_Cfg_CycleIdTableType, DEM_CONST) Dem_Cfg_CycleIdTable[4];
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
extern CONST(Dem_Cfg_DataCollectionTableType, DEM_CONST) Dem_Cfg_DataCollectionTable[7];
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
extern CONST(Dem_Cfg_DataCollectionTableEdr2CollIndType, DEM_CONST) Dem_Cfg_DataCollectionTableEdr2CollInd[5];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
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
extern CONST(Dem_Cfg_DataElementTableType, DEM_CONST) Dem_Cfg_DataElementTable[7];
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
extern CONST(Dem_Cfg_DataElementTableCol2ElmtIndType, DEM_CONST) Dem_Cfg_DataElementTableCol2ElmtInd[6];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
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
extern CONST(Dem_Cfg_DebounceTableType, DEM_CONST) Dem_Cfg_DebounceTable[2];
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
extern CONST(Dem_Cfg_DtcTableType, DEM_CONST) Dem_Cfg_DtcTable[19];
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
extern CONST(Dem_Cfg_EventTableType, DEM_CONST) Dem_Cfg_EventTable[22];
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
extern CONST(Dem_Cfg_ExtendedDataTableType, DEM_CONST) Dem_Cfg_ExtendedDataTable[2];
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
extern CONST(Dem_MemoryEntry_HandleType, DEM_CONST) Dem_Cfg_MemoryBlockIdToMemoryEntryId[20];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
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
extern CONST(Dem_NvDataPtrType, DEM_CONST) Dem_Cfg_MemoryDataPtr[20];
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
extern CONST(Dem_Cfg_MemoryDataSizeType, DEM_CONST) Dem_Cfg_MemoryDataSize[20];
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
extern CONST(Dem_SharedMemoryEntryPtrType, DEM_CONST) Dem_Cfg_MemoryEntry[19];
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
extern CONST(Dem_Cfg_PrimaryEntryType, DEM_CONST) Dem_Cfg_MemoryEntryInit;
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
extern CONST(Dem_Cfg_TimeSeriesEntryType, DEM_CONST) Dem_Cfg_TimeSeriesEntryInit;
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
extern VAR(Dem_Cfg_AdminDataType, DEM_NVM_DATA_NOINIT) Dem_Cfg_AdminData;
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
extern VAR(Dem_ClearDTC_DataType, DEM_VAR_NOINIT) Dem_Cfg_ClearDTCTable[1];
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
extern VAR(Dem_Cfg_CommitBufferType, DEM_VAR_NOINIT) Dem_Cfg_CommitBuffer;  /* PRQA S 0759 */ /* MD_MSR_18.4 */
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
extern VAR(Dem_DTCSelector_DataType, DEM_VAR_NOINIT) Dem_Cfg_DTCSelectorTable[1];
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
extern VAR(Dem_Cfg_EnableConditionGroupCounterType, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionGroupCounter[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
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
extern volatile VAR(Dem_Cfg_EnableConditionGroupStateType, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionGroupState[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
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
extern VAR(Dem_Cfg_EnableConditionStateType, DEM_VAR_NOINIT) Dem_Cfg_EnableConditionState[1];
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
extern volatile VAR(Dem_Cfg_EventDebounceValueType, DEM_VAR_NOINIT) Dem_Cfg_EventDebounceValue[22];
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
extern volatile VAR(Dem_Event_InternalStatusType, DEM_VAR_NOINIT) Dem_Cfg_EventInternalStatus[22];
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
extern VAR(Dem_FilterData_InfoType, DEM_VAR_NOINIT) Dem_Cfg_FilterInfoTable[1];
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
extern VAR(Dem_Cfg_FilterReportedEventsType, DEM_VAR_NOINIT) Dem_Cfg_FilterReportedEvents[3];
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
extern VAR(Dem_FreezeFrameIterator_FilterType, DEM_VAR_NOINIT) Dem_Cfg_FreezeFrameIteratorTable[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
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
extern volatile VAR(Dem_Cfg_MemoryCommitNumberType, DEM_VAR_NOINIT) Dem_Cfg_MemoryCommitNumber[20];
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
extern VAR(Dem_Cfg_MemoryStatusType, DEM_VAR_NOINIT) Dem_Cfg_MemoryStatus[20];
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
extern VAR(Dem_Cfg_MemoryIndexType, DEM_VAR_NOINIT) Dem_Cfg_PrimaryChronology[18];
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_0;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_1;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_10;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_11;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_12;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_13;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_14;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_15;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_16;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_17;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_2;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_3;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_4;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_5;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_6;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_7;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_8;
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
extern VAR(Dem_Cfg_PrimaryEntryType, DEM_NVM_DATA_NOINIT) Dem_Cfg_PrimaryEntry_9;
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
extern VAR(Dem_Cfg_ReadoutBufferEntryType, DEM_VAR_NOINIT) Dem_Cfg_ReadoutBuffer[1];
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
extern VAR(Dem_Cfg_ReportedEventsType, DEM_VAR_NOINIT) Dem_Cfg_ReportedEventsOfFilter[1];
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
extern VAR(Dem_Cfg_SatelliteInfoType0, DEM_VAR_ZERO_INIT) Dem_Cfg_SatelliteInfo0;
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
extern VAR(Dem_Cfg_StatusDataType, DEM_NVM_DATA_NOINIT) Dem_Cfg_StatusData;
#define DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  Justification of MISRA deviations
**********************************************************************************************************************/


#endif  /* DEM_LCFG_H */
/**********************************************************************************************************************
  END OF FILE: Dem_Lcfg.h     [Vag (Vector), VARIANT-PRE-COMPILE, 16.06.00.107213]
**********************************************************************************************************************/

