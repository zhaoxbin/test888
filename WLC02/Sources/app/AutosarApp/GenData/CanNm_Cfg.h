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
 *            Module: CanNm
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CanNm_Cfg.h
 *   Generation Time: 2020-09-25 15:12:54
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


#if !defined (CANNM_CFG_H)
# define CANNM_CFG_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2_0779 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "ComStack_Types.h"
#include "NmStack_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define CANNM_NUMBER_OF_CANNM_CHANNELS        1u
/* Symbolic name defines for CanNmTxPdus */



/**
 * \defgroup CanNmHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define CanNmConf_CanNmTxPdu_NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_1915286e_Tx 0
/**\} */

/* Symbolic name defines for CanNmTxUserDataPdus */



/**
 * \defgroup CanNmHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define CanNmConf_CanNmUserDataTxPdu_NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_fd222ddc 0
/**\} */

/* Symbolic name defines for CanNmRxPdus */



/**
 * \defgroup CanNmHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define CanNmConf_CanNmRxPdu_NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d_Rx   0
/**\} */

/* Options */
#define CANNM_BUS_LOAD_REDUCTION_ENABLED                STD_OFF
#define CANNM_IMMEDIATE_TXCONF_ENABLED                  STD_OFF
#define CANNM_USER_DATA_ENABLED                         STD_ON
#define CANNM_PASSIVE_MODE_ENABLED                      STD_OFF
#define CANNM_VERSION_INFO_API                          STD_ON
#define CANNM_DISABLE_TX_ERR_REPORT                     STD_OFF
#define CANNM_PDU_RX_INDICATION_ENABLED                 STD_OFF
#define CANNM_STATE_CHANGE_IND_ENABLED                  STD_ON
#define CANNM_REMOTE_SLEEP_IND_ENABLED                  STD_OFF
#define CANNM_BUS_SYNCHRONIZATION_ENABLED               STD_OFF
#define CANNM_COM_USER_DATA_SUPPORT                     STD_ON
#define CANNM_COORDINATOR_SYNC_SUPPORT                  STD_OFF
#define CANNM_RUNTIME_MEASUREMENT_SUPPORT               STD_OFF
#define CANNM_PDUR_CANNM_TXCONFIRMATION                 STD_OFF
#define CANNM_CAR_WUP_RX_FEATURE_ENABLED                STD_OFF
#define CANNM_CAR_WUP_FILTER_FEATURE_ENABLED            STD_OFF
#define CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED           STD_ON
#define CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED            STD_OFF
#define CANNM_PN_FEATURE_ENABLED                        STD_OFF
#define CANNM_PN_ERA_CALC_FEATURE_ENABLED               STD_OFF
#define CANNM_PN_EIRA_CALC_FEATURE_ENABLED              STD_OFF
#define CANNM_PN_TX_TIMEOUT_EXCEPTION_FEATURE_ENABLED   STD_OFF
#define CANNM_BUSNM_SPECIFIC_PDU_RX_INDICATION_ENABLED  STD_OFF
#define CANNM_ALLOW_TRIGGERED_MSG_TRANSMISSION          STD_OFF

/* Integration */


#define CANNM_EXPECTED_GENERATOR_COMPATIBILITY_VERSION  0x1000u


/* Invalid Channel Handle */
#define CANNM_INVALID_CHANNEL  0xFFu

/* Pdu CBV / NID Position Defines */
#define CANNM_PDU_OFF          0xFFu
#define CANNM_PDU_BYTE_0       0x00u
#define CANNM_PDU_BYTE_1       0x01u

/* PN Calculation */
#if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON ) || ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
# define CANNM_PN_CALC_FEATURE_ENABLED
# define CANNM_PN_CLUSTERS_PER_BYTE 8u
#endif

#if defined (CANNM_ISDEF_PNEIRACALCENABLED)
#else
# define CANNM_ISDEF_PNEIRACALCENABLED                     STD_ON
#endif

#if defined (CANNM_ISDEF_PNINFOLENGTH)
#else
# define CANNM_ISDEF_PNINFOLENGTH                          STD_ON
#endif

/**********************************************************************************************************************
    General Defines
**********************************************************************************************************************/
#ifndef CANNM_DEV_ERROR_DETECT
#define CANNM_DEV_ERROR_DETECT STD_OFF
#endif
#ifndef CANNM_DEV_ERROR_REPORT
#define CANNM_DEV_ERROR_REPORT STD_OFF
#endif
#ifndef CANNM_USE_DUMMY_STATEMENT
#define CANNM_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/EcuC/EcucGeneral/DummyStatement */
#endif
#ifndef CANNM_DUMMY_STATEMENT
#define CANNM_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CANNM_DUMMY_STATEMENT_CONST
#define CANNM_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CANNM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define CANNM_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef CANNM_ATOMIC_VARIABLE_ACCESS
#define CANNM_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef CANNM_PROCESSOR_RH850_1649
#define CANNM_PROCESSOR_RH850_1649
#endif
#ifndef CANNM_COMP_GREENHILLS
#define CANNM_COMP_GREENHILLS
#endif
#ifndef CANNM_GEN_GENERATOR_MSR
#define CANNM_GEN_GENERATOR_MSR
#endif
#ifndef CANNM_CPUTYPE_BITORDER_LSB2MSB
#define CANNM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef CANNM_CONFIGURATION_VARIANT_PRECOMPILE
#define CANNM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef CANNM_CONFIGURATION_VARIANT_LINKTIME
#define CANNM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef CANNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define CANNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef CANNM_CONFIGURATION_VARIANT
#define CANNM_CONFIGURATION_VARIANT CANNM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef CANNM_POSTBUILD_VARIANT_SUPPORT
#define CANNM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif
 

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanNmPCDataSwitches  CanNm Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CANNM_CHANNELCONFIG                                           STD_ON
#define CANNM_ACTIVEWAKEUPBITENABLEDOFCHANNELCONFIG                   STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.ActiveWakeUpBitEnabled' Reason: 'ActiveWakeupBitFeature is disabled' */
#define CANNM_ALLMESSAGESKEEPAWAKEOFCHANNELCONFIG                     STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.AllMessagesKeepAwake' Reason: 'PN feature is disabled' */
#define CANNM_BUSLOADREDUCTIONACTIVEOFCHANNELCONFIG                   STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.BusLoadReductionActive' Reason: 'BusLoadReduction is disabled' */
#define CANNM_CARWAKEUPBITMASKOFCHANNELCONFIG                         STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.CarWakeUpBitMask' Reason: 'CarWupRx is disabled' */
#define CANNM_CARWAKEUPBYTEPOSITIONOFCHANNELCONFIG                    STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.CarWakeUpBytePosition' Reason: 'CarWupRx is disabled' */
#define CANNM_CARWAKEUPFILTERENABLEDOFCHANNELCONFIG                   STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.CarWakeUpFilterEnabled' Reason: 'CarWupFilterFeature is disabled' */
#define CANNM_CARWAKEUPFILTERNODEIDOFCHANNELCONFIG                    STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.CarWakeUpFilterNodeId' Reason: 'CarWupFilterFeature is disabled' */
#define CANNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG                       STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.CarWakeUpRxEnabled' Reason: 'CarWupRx is disabled' */
#define CANNM_CHANNELIDOFCHANNELCONFIG                                STD_ON
#define CANNM_COMCONTROLENABLEDOFCHANNELCONFIG                        STD_ON
#define CANNM_ERRORWAITBUSSLEEPTIMEOFCHANNELCONFIG                    STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.ErrorWaitBusSleepTime' Reason: 'the value of CanNm_ErrorWaitBusSleepTimeOfChannelConfig is always '0' due to this, the array is deactivated.' */
#define CANNM_IMMEDIATENMCYCLETIMEOFCHANNELCONFIG                     STD_ON
#define CANNM_IMMEDIATENMTRANSMISSIONSOFCHANNELCONFIG                 STD_ON
#define CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG                  STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.ImmediateRestartEnabled' Reason: 'Immediate Restart is disabled' */
#define CANNM_MSGCYCLETIMEOFCHANNELCONFIG                             STD_ON
#define CANNM_MSGTIMEOUTTIMEOFCHANNELCONFIG                           STD_ON
#define CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG                     STD_ON
#define CANNM_NODEIDENABLEDOFCHANNELCONFIG                            STD_ON
#define CANNM_PDUCBVPOSITIONOFCHANNELCONFIG                           STD_ON
#define CANNM_PDUNIDPOSITIONOFCHANNELCONFIG                           STD_ON
#define CANNM_PNCALLTXTIMEOUTEXCEPTIONOFCHANNELCONFIG                 STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.PnCallTxTimeoutException' Reason: 'PN feature is disabled' */
#define CANNM_PNERACALCENABLEDOFCHANNELCONFIG                         STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.PnEraCalcEnabled' Reason: 'EraCalcFeature is disabled' */
#define CANNM_PNERARXPDUIDOFCHANNELCONFIG                             STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.PnEraRxPduId' Reason: 'EraCalcFeature is disabled' */
#define CANNM_PNHANDLEMULTIPLENETWORKREQUESTOFCHANNELCONFIG           STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.PnHandleMultipleNetworkRequest' Reason: 'PN feature is disabled' */
#define CANNM_REMOTESLEEPINDTIMEOFCHANNELCONFIG                       STD_ON
#define CANNM_REPEATMESSAGETIMEOFCHANNELCONFIG                        STD_ON
#define CANNM_REPEATMSGINDENABLEDOFCHANNELCONFIG                      STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.RepeatMsgIndEnabled' Reason: 'the value of CanNm_RepeatMsgIndEnabledOfChannelConfig is always 'false' due to this, the array is deactivated.' */
#define CANNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG                 STD_OFF  /**< Deactivateable: 'CanNm_ChannelConfig.RetryFirstMessageRequest' Reason: 'Retry First Message Request is disabled' */
#define CANNM_TIMEOUTTIMEOFCHANNELCONFIG                              STD_ON
#define CANNM_WAITBUSSLEEPTIMEOFCHANNELCONFIG                         STD_ON
#define CANNM_COMMSTATE                                               STD_ON
#define CANNM_COORDREADYTOSLEEPSTATE                                  STD_ON
#define CANNM_FINALMAGICNUMBER                                        STD_OFF  /**< Deactivateable: 'CanNm_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define CANNM_GENERATORCOMPATIBILITYVERSION                           STD_OFF  /**< Deactivateable: 'CanNm_GeneratorCompatibilityVersion' Reason: 'Variant is not VARIANT-POST-BUILD-LOADABLE' */
#define CANNM_IMMEDIATENMMSGCOUNT                                     STD_ON
#define CANNM_IMMEDIATERESTARTFAILED                                  STD_OFF  /**< Deactivateable: 'CanNm_ImmediateRestartFailed' Reason: 'Immediate Restart is disabled' */
#define CANNM_INITDATAHASHCODE                                        STD_OFF  /**< Deactivateable: 'CanNm_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define CANNM_MODULEINITIALIZED                                       STD_OFF  /**< Deactivateable: 'CanNm_ModuleInitialized' Reason: 'Initialized flag is only needed for Development Error Detection.' */
#define CANNM_MSGCONFIRMATIONFLAG                                     STD_ON
#define CANNM_MSGINDICATIONFLAG                                       STD_ON
#define CANNM_MSGREQUEST                                              STD_ON
#define CANNM_MSGTIMEOUTTIMER                                         STD_ON
#define CANNM_MSGTIMER                                                STD_ON
#define CANNM_NETWORKRESTARTFLAG                                      STD_ON
#define CANNM_NMSTATE                                                 STD_ON
#define CANNM_PBCHANNELCONFIG                                         STD_ON
#define CANNM_ALLOWTRIGGEREDMSGTRANSMISSIONOFPBCHANNELCONFIG          STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.AllowTriggeredMsgTransmission' Reason: 'Triggered Message Transmission is disabled' */
#define CANNM_MSGCYCLEOFFSETOFPBCHANNELCONFIG                         STD_ON
#define CANNM_MSGREDUCEDTIMEOFPBCHANNELCONFIG                         STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.MsgReducedTime' Reason: 'BusLoadReduction is disabled' */
#define CANNM_NODEIDOFPBCHANNELCONFIG                                 STD_ON
#define CANNM_PNCLUSTERREQEXTENDIDXOFPBCHANNELCONFIG                  STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.PnClusterReqExtEndIdx' Reason: 'EraCalcFeature is disabled' */
#define CANNM_PNCLUSTERREQEXTLENGTHOFPBCHANNELCONFIG                  STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.PnClusterReqExtLength' Reason: 'EraCalcFeature is disabled' */
#define CANNM_PNCLUSTERREQEXTSTARTIDXOFPBCHANNELCONFIG                STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.PnClusterReqExtStartIdx' Reason: 'EraCalcFeature is disabled' */
#define CANNM_PNCLUSTERREQEXTUSEDOFPBCHANNELCONFIG                    STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.PnClusterReqExtUsed' Reason: 'EraCalcFeature is disabled' */
#define CANNM_PNENABLEDOFPBCHANNELCONFIG                              STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.PnEnabled' Reason: 'PN feature is disabled' */
#define CANNM_RXMESSAGEDATAENDIDXOFPBCHANNELCONFIG                    STD_ON
#define CANNM_RXMESSAGEDATALENGTHOFPBCHANNELCONFIG                    STD_ON
#define CANNM_RXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG                  STD_ON
#define CANNM_RXMESSAGEDATAUSEDOFPBCHANNELCONFIG                      STD_ON
#define CANNM_RXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG                   STD_ON
#define CANNM_RXMESSAGEDATA_CBVUSEDOFPBCHANNELCONFIG                  STD_ON
#define CANNM_RXMESSAGEDATA_CARWAKEUPBYTEIDXOFPBCHANNELCONFIG         STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.RxMessageData_CarWakeUpByteIdx' Reason: 'the optional indirection is deactivated because RxMessageData_CarWakeUpByteUsedOfPbChannelConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CANNM_RXMESSAGEDATA_CARWAKEUPBYTEUSEDOFPBCHANNELCONFIG        STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.RxMessageData_CarWakeUpByteUsed' Reason: 'the optional indirection is deactivated because RxMessageData_CarWakeUpByteUsedOfPbChannelConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CANNM_RXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG                   STD_ON
#define CANNM_RXMESSAGEDATA_NIDUSEDOFPBCHANNELCONFIG                  STD_ON
#define CANNM_RXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG           STD_ON
#define CANNM_RXMESSAGEDATA_USERDATALENGTHOFPBCHANNELCONFIG           STD_ON
#define CANNM_RXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG         STD_ON
#define CANNM_RXMESSAGEDATA_USERDATAUSEDOFPBCHANNELCONFIG             STD_ON
#define CANNM_TXMESSAGEDATAENDIDXOFPBCHANNELCONFIG                    STD_ON
#define CANNM_TXMESSAGEDATALENGTHOFPBCHANNELCONFIG                    STD_ON
#define CANNM_TXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG                  STD_ON
#define CANNM_TXMESSAGEDATAUSEDOFPBCHANNELCONFIG                      STD_ON
#define CANNM_TXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG                   STD_ON
#define CANNM_TXMESSAGEDATA_CBVUSEDOFPBCHANNELCONFIG                  STD_ON
#define CANNM_TXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG                   STD_ON
#define CANNM_TXMESSAGEDATA_NIDUSEDOFPBCHANNELCONFIG                  STD_ON
#define CANNM_TXMESSAGEDATA_PNFILTERMASKENDIDXOFPBCHANNELCONFIG       STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.TxMessageData_PnFilterMaskEndIdx' Reason: 'the optional indirection is deactivated because TxMessageData_PnFilterMaskUsedOfPbChannelConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CANNM_TXMESSAGEDATA_PNFILTERMASKSTARTIDXOFPBCHANNELCONFIG     STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.TxMessageData_PnFilterMaskStartIdx' Reason: 'the optional indirection is deactivated because TxMessageData_PnFilterMaskUsedOfPbChannelConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CANNM_TXMESSAGEDATA_PNFILTERMASKUSEDOFPBCHANNELCONFIG         STD_OFF  /**< Deactivateable: 'CanNm_PbChannelConfig.TxMessageData_PnFilterMaskUsed' Reason: 'the optional indirection is deactivated because TxMessageData_PnFilterMaskUsedOfPbChannelConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CANNM_TXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG           STD_ON
#define CANNM_TXMESSAGEDATA_USERDATALENGTHOFPBCHANNELCONFIG           STD_ON
#define CANNM_TXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG         STD_ON
#define CANNM_TXMESSAGEDATA_USERDATAUSEDOFPBCHANNELCONFIG             STD_ON
#define CANNM_TXPDUIDOFPBCHANNELCONFIG                                STD_ON
#define CANNM_TXUSERDATAPDUIDOFPBCHANNELCONFIG                        STD_ON
#define CANNM_PDUIDTOCHINDEX                                          STD_OFF  /**< Deactivateable: 'CanNm_PduIdToChIndex' Reason: 'PB-S is not active or channel reference is invariant over all channels' */
#define CANNM_PNCLUSTERREQ                                            STD_OFF  /**< Deactivateable: 'CanNm_PnClusterReq' Reason: 'EiraCalcFeature is disabled' */
#define CANNM_PNCLUSTERREQEXT                                         STD_OFF  /**< Deactivateable: 'CanNm_PnClusterReqExt' Reason: 'EraCalcFeature is disabled' */
#define CANNM_PNCLUSTERREQEXTNEW                                      STD_OFF  /**< Deactivateable: 'CanNm_PnClusterReqExtNew' Reason: 'EraCalcFeature is disabled' */
#define CANNM_PNCLUSTERREQNEW                                         STD_OFF  /**< Deactivateable: 'CanNm_PnClusterReqNew' Reason: 'EiraCalcFeature is disabled' */
#define CANNM_PNCLUSTERRESETTIMER                                     STD_OFF  /**< Deactivateable: 'CanNm_PnClusterResetTimer' Reason: 'EiraCalcFeature is disabled' */
#define CANNM_PNCLUSTERRESETTIMEREXT                                  STD_OFF  /**< Deactivateable: 'CanNm_PnClusterResetTimerExt' Reason: 'EraCalcFeature is disabled' */
#define CANNM_PNEIRACALCENABLED                                       STD_OFF  /**< Deactivateable: 'CanNm_PnEiraCalcEnabled' Reason: 'ConfigVariant is Pre-Compile or EiraCalcFeature is disabled' */
#define CANNM_PNEIRARXPDUID                                           STD_OFF  /**< Deactivateable: 'CanNm_PnEiraRxPduId' Reason: 'EiraCalcFeature is disabled' */
#define CANNM_PNFILTERMASK                                            STD_OFF  /**< Deactivateable: 'CanNm_PnFilterMask' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define CANNM_PNINFOLENGTH                                            STD_OFF  /**< Deactivateable: 'CanNm_PnInfoLength' Reason: 'PN feature is disabled' */
#define CANNM_PNINFOOFFSET                                            STD_OFF  /**< Deactivateable: 'CanNm_PnInfoOffset' Reason: 'PN feature is disabled' */
#define CANNM_PNMESSAGEFILTERDEACTIVATIONINDICATED                    STD_OFF  /**< Deactivateable: 'CanNm_PnMessageFilterDeactivationIndicated' Reason: 'PN feature is disabled' */
#define CANNM_PNMESSAGEFILTERENABLED                                  STD_OFF  /**< Deactivateable: 'CanNm_PnMessageFilterEnabled' Reason: 'PN feature is disabled' */
#define CANNM_PNRESETTIME                                             STD_OFF  /**< Deactivateable: 'CanNm_PnResetTime' Reason: 'Neither EiraCalcFeature nor EraCalcFeature enabled' */
#define CANNM_REMOTESLEEPINDSTATE                                     STD_OFF  /**< Deactivateable: 'CanNm_RemoteSleepIndState' Reason: 'RemoteSleepIndEnabled is disabled' */
#define CANNM_REMOTESLEEPTIMER                                        STD_OFF  /**< Deactivateable: 'CanNm_RemoteSleepTimer' Reason: 'RemoteSleepIndEnabled is disabled' */
#define CANNM_REPEATMSGBITINDFLAG                                     STD_ON
#define CANNM_REPEATMSGREQFLAG                                        STD_ON
#define CANNM_REPEATMSGTIMER                                          STD_ON
#define CANNM_RETRYFIRSTMESSAGEREQUESTFLAG                            STD_OFF  /**< Deactivateable: 'CanNm_RetryFirstMessageRequestFlag' Reason: 'Retry First Message Request is disabled' */
#define CANNM_RXMESSAGEDATA                                           STD_ON
#define CANNM_SIZEOFCHANNELCONFIG                                     STD_ON
#define CANNM_SIZEOFCOMMSTATE                                         STD_ON
#define CANNM_SIZEOFCOORDREADYTOSLEEPSTATE                            STD_ON
#define CANNM_SIZEOFIMMEDIATENMMSGCOUNT                               STD_ON
#define CANNM_SIZEOFMSGCONFIRMATIONFLAG                               STD_ON
#define CANNM_SIZEOFMSGINDICATIONFLAG                                 STD_ON
#define CANNM_SIZEOFMSGREQUEST                                        STD_ON
#define CANNM_SIZEOFMSGTIMEOUTTIMER                                   STD_ON
#define CANNM_SIZEOFMSGTIMER                                          STD_ON
#define CANNM_SIZEOFNETWORKRESTARTFLAG                                STD_ON
#define CANNM_SIZEOFNMSTATE                                           STD_ON
#define CANNM_SIZEOFPBCHANNELCONFIG                                   STD_ON
#define CANNM_SIZEOFREPEATMSGBITINDFLAG                               STD_ON
#define CANNM_SIZEOFREPEATMSGREQFLAG                                  STD_ON
#define CANNM_SIZEOFREPEATMSGTIMER                                    STD_ON
#define CANNM_SIZEOFSYSTONMCHIND                                      STD_ON
#define CANNM_SIZEOFTIMEOUTTIMER                                      STD_ON
#define CANNM_SIZEOFTXCONTROLSTATE                                    STD_ON
#define CANNM_SIZEOFTXCONTROLSTATEREQUEST                             STD_ON
#define CANNM_SIZEOFTXMESSAGEDATA                                     STD_ON
#define CANNM_SIZEOFWAITBUSSLEEPTIMER                                 STD_ON
#define CANNM_SYSTONMCHIND                                            STD_ON
#define CANNM_TIMEOUTTIMER                                            STD_ON
#define CANNM_TXCONTROLSTATE                                          STD_ON
#define CANNM_TXCONTROLSTATEREQUEST                                   STD_ON
#define CANNM_TXMESSAGEDATA                                           STD_ON
#define CANNM_WAITBUSSLEEPTIMER                                       STD_ON
#define CANNM_PCCONFIG                                                STD_ON
#define CANNM_CHANNELCONFIGOFPCCONFIG                                 STD_ON
#define CANNM_COMMSTATEOFPCCONFIG                                     STD_ON
#define CANNM_COORDREADYTOSLEEPSTATEOFPCCONFIG                        STD_ON
#define CANNM_FINALMAGICNUMBEROFPCCONFIG                              STD_OFF  /**< Deactivateable: 'CanNm_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define CANNM_GENERATORCOMPATIBILITYVERSIONOFPCCONFIG                 STD_OFF  /**< Deactivateable: 'CanNm_PCConfig.GeneratorCompatibilityVersion' Reason: 'Variant is not VARIANT-POST-BUILD-LOADABLE' */
#define CANNM_IMMEDIATENMMSGCOUNTOFPCCONFIG                           STD_ON
#define CANNM_INITDATAHASHCODEOFPCCONFIG                              STD_OFF  /**< Deactivateable: 'CanNm_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define CANNM_MSGCONFIRMATIONFLAGOFPCCONFIG                           STD_ON
#define CANNM_MSGINDICATIONFLAGOFPCCONFIG                             STD_ON
#define CANNM_MSGREQUESTOFPCCONFIG                                    STD_ON
#define CANNM_MSGTIMEOUTTIMEROFPCCONFIG                               STD_ON
#define CANNM_MSGTIMEROFPCCONFIG                                      STD_ON
#define CANNM_NETWORKRESTARTFLAGOFPCCONFIG                            STD_ON
#define CANNM_NMSTATEOFPCCONFIG                                       STD_ON
#define CANNM_PBCHANNELCONFIGOFPCCONFIG                               STD_ON
#define CANNM_PNEIRACALCENABLEDOFPCCONFIG                             STD_OFF  /**< Deactivateable: 'CanNm_PCConfig.PnEiraCalcEnabled' Reason: 'ConfigVariant is Pre-Compile or EiraCalcFeature is disabled' */
#define CANNM_PNEIRARXPDUIDOFPCCONFIG                                 STD_OFF  /**< Deactivateable: 'CanNm_PCConfig.PnEiraRxPduId' Reason: 'EiraCalcFeature is disabled' */
#define CANNM_PNINFOLENGTHOFPCCONFIG                                  STD_OFF  /**< Deactivateable: 'CanNm_PCConfig.PnInfoLength' Reason: 'PN feature is disabled' */
#define CANNM_PNINFOOFFSETOFPCCONFIG                                  STD_OFF  /**< Deactivateable: 'CanNm_PCConfig.PnInfoOffset' Reason: 'PN feature is disabled' */
#define CANNM_PNRESETTIMEOFPCCONFIG                                   STD_OFF  /**< Deactivateable: 'CanNm_PCConfig.PnResetTime' Reason: 'Neither EiraCalcFeature nor EraCalcFeature enabled' */
#define CANNM_REPEATMSGBITINDFLAGOFPCCONFIG                           STD_ON
#define CANNM_REPEATMSGREQFLAGOFPCCONFIG                              STD_ON
#define CANNM_REPEATMSGTIMEROFPCCONFIG                                STD_ON
#define CANNM_RXMESSAGEDATAOFPCCONFIG                                 STD_ON
#define CANNM_SIZEOFCHANNELCONFIGOFPCCONFIG                           STD_ON
#define CANNM_SIZEOFCOMMSTATEOFPCCONFIG                               STD_ON
#define CANNM_SIZEOFCOORDREADYTOSLEEPSTATEOFPCCONFIG                  STD_ON
#define CANNM_SIZEOFIMMEDIATENMMSGCOUNTOFPCCONFIG                     STD_ON
#define CANNM_SIZEOFMSGCONFIRMATIONFLAGOFPCCONFIG                     STD_ON
#define CANNM_SIZEOFMSGINDICATIONFLAGOFPCCONFIG                       STD_ON
#define CANNM_SIZEOFMSGREQUESTOFPCCONFIG                              STD_ON
#define CANNM_SIZEOFMSGTIMEOUTTIMEROFPCCONFIG                         STD_ON
#define CANNM_SIZEOFMSGTIMEROFPCCONFIG                                STD_ON
#define CANNM_SIZEOFNETWORKRESTARTFLAGOFPCCONFIG                      STD_ON
#define CANNM_SIZEOFNMSTATEOFPCCONFIG                                 STD_ON
#define CANNM_SIZEOFPBCHANNELCONFIGOFPCCONFIG                         STD_ON
#define CANNM_SIZEOFREPEATMSGBITINDFLAGOFPCCONFIG                     STD_ON
#define CANNM_SIZEOFREPEATMSGREQFLAGOFPCCONFIG                        STD_ON
#define CANNM_SIZEOFREPEATMSGTIMEROFPCCONFIG                          STD_ON
#define CANNM_SIZEOFSYSTONMCHINDOFPCCONFIG                            STD_ON
#define CANNM_SIZEOFTIMEOUTTIMEROFPCCONFIG                            STD_ON
#define CANNM_SIZEOFTXCONTROLSTATEOFPCCONFIG                          STD_ON
#define CANNM_SIZEOFTXCONTROLSTATEREQUESTOFPCCONFIG                   STD_ON
#define CANNM_SIZEOFTXMESSAGEDATAOFPCCONFIG                           STD_ON
#define CANNM_SIZEOFWAITBUSSLEEPTIMEROFPCCONFIG                       STD_ON
#define CANNM_SYSTONMCHINDOFPCCONFIG                                  STD_ON
#define CANNM_TIMEOUTTIMEROFPCCONFIG                                  STD_ON
#define CANNM_TXCONTROLSTATEOFPCCONFIG                                STD_ON
#define CANNM_TXCONTROLSTATEREQUESTOFPCCONFIG                         STD_ON
#define CANNM_TXMESSAGEDATAOFPCCONFIG                                 STD_ON
#define CANNM_WAITBUSSLEEPTIMEROFPCCONFIG                             STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCMinNumericValueDefines  CanNm Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define CANNM_MIN_COMMSTATE                                           0u
#define CANNM_MIN_COORDREADYTOSLEEPSTATE                              0u
#define CANNM_MIN_IMMEDIATENMMSGCOUNT                                 0u
#define CANNM_MIN_MSGREQUEST                                          0u
#define CANNM_MIN_MSGTIMEOUTTIMER                                     0u
#define CANNM_MIN_MSGTIMER                                            0u
#define CANNM_MIN_NETWORKRESTARTFLAG                                  0u
#define CANNM_MIN_NMSTATE                                             0u
#define CANNM_MIN_REPEATMSGTIMER                                      0u
#define CANNM_MIN_RXMESSAGEDATA                                       0u
#define CANNM_MIN_TIMEOUTTIMER                                        0u
#define CANNM_MIN_TXCONTROLSTATE                                      0u
#define CANNM_MIN_TXCONTROLSTATEREQUEST                               0u
#define CANNM_MIN_TXMESSAGEDATA                                       0u
#define CANNM_MIN_WAITBUSSLEEPTIMER                                   0u
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCMaxNumericValueDefines  CanNm Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define CANNM_MAX_COMMSTATE                                           255u
#define CANNM_MAX_COORDREADYTOSLEEPSTATE                              255u
#define CANNM_MAX_IMMEDIATENMMSGCOUNT                                 255u
#define CANNM_MAX_MSGREQUEST                                          255u
#define CANNM_MAX_MSGTIMEOUTTIMER                                     65535u
#define CANNM_MAX_MSGTIMER                                            65535u
#define CANNM_MAX_NETWORKRESTARTFLAG                                  255u
#define CANNM_MAX_NMSTATE                                             255u
#define CANNM_MAX_REPEATMSGTIMER                                      65535u
#define CANNM_MAX_RXMESSAGEDATA                                       255u
#define CANNM_MAX_TIMEOUTTIMER                                        65535u
#define CANNM_MAX_TXCONTROLSTATE                                      255u
#define CANNM_MAX_TXCONTROLSTATEREQUEST                               255u
#define CANNM_MAX_TXMESSAGEDATA                                       255u
#define CANNM_MAX_WAITBUSSLEEPTIMER                                   65535u
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCNoReferenceDefines  CanNm No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define CANNM_NO_RXMESSAGEDATAENDIDXOFPBCHANNELCONFIG                 255u
#define CANNM_NO_RXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG               255u
#define CANNM_NO_RXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG                255u
#define CANNM_NO_RXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG                255u
#define CANNM_NO_RXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG        255u
#define CANNM_NO_RXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG      255u
#define CANNM_NO_TXMESSAGEDATAENDIDXOFPBCHANNELCONFIG                 255u
#define CANNM_NO_TXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG               255u
#define CANNM_NO_TXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG                255u
#define CANNM_NO_TXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG                255u
#define CANNM_NO_TXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG        255u
#define CANNM_NO_TXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG      255u
#define CANNM_NO_TXPDUIDOFPBCHANNELCONFIG                             255u
#define CANNM_NO_TXUSERDATAPDUIDOFPBCHANNELCONFIG                     255u
#define CANNM_NO_SYSTONMCHIND                                         255u
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCIsReducedToDefineDefines  CanNm Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define CANNM_ISDEF_CHANNELIDOFCHANNELCONFIG                          STD_OFF
#define CANNM_ISDEF_COMCONTROLENABLEDOFCHANNELCONFIG                  STD_OFF
#define CANNM_ISDEF_IMMEDIATENMCYCLETIMEOFCHANNELCONFIG               STD_OFF
#define CANNM_ISDEF_IMMEDIATENMTRANSMISSIONSOFCHANNELCONFIG           STD_OFF
#define CANNM_ISDEF_MSGCYCLETIMEOFCHANNELCONFIG                       STD_OFF
#define CANNM_ISDEF_MSGTIMEOUTTIMEOFCHANNELCONFIG                     STD_OFF
#define CANNM_ISDEF_NODEDETECTIONENABLEDOFCHANNELCONFIG               STD_OFF
#define CANNM_ISDEF_NODEIDENABLEDOFCHANNELCONFIG                      STD_OFF
#define CANNM_ISDEF_PDUCBVPOSITIONOFCHANNELCONFIG                     STD_OFF
#define CANNM_ISDEF_PDUNIDPOSITIONOFCHANNELCONFIG                     STD_OFF
#define CANNM_ISDEF_REMOTESLEEPINDTIMEOFCHANNELCONFIG                 STD_OFF
#define CANNM_ISDEF_REPEATMESSAGETIMEOFCHANNELCONFIG                  STD_OFF
#define CANNM_ISDEF_TIMEOUTTIMEOFCHANNELCONFIG                        STD_OFF
#define CANNM_ISDEF_WAITBUSSLEEPTIMEOFCHANNELCONFIG                   STD_OFF
#define CANNM_ISDEF_MSGCYCLEOFFSETOFPBCHANNELCONFIG                   STD_OFF
#define CANNM_ISDEF_NODEIDOFPBCHANNELCONFIG                           STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATAENDIDXOFPBCHANNELCONFIG              STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATALENGTHOFPBCHANNELCONFIG              STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG            STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATAUSEDOFPBCHANNELCONFIG                STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG             STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATA_CBVUSEDOFPBCHANNELCONFIG            STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG             STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATA_NIDUSEDOFPBCHANNELCONFIG            STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG     STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATA_USERDATALENGTHOFPBCHANNELCONFIG     STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG   STD_OFF
#define CANNM_ISDEF_RXMESSAGEDATA_USERDATAUSEDOFPBCHANNELCONFIG       STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATAENDIDXOFPBCHANNELCONFIG              STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATALENGTHOFPBCHANNELCONFIG              STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG            STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATAUSEDOFPBCHANNELCONFIG                STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG             STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATA_CBVUSEDOFPBCHANNELCONFIG            STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG             STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATA_NIDUSEDOFPBCHANNELCONFIG            STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG     STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATA_USERDATALENGTHOFPBCHANNELCONFIG     STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG   STD_OFF
#define CANNM_ISDEF_TXMESSAGEDATA_USERDATAUSEDOFPBCHANNELCONFIG       STD_OFF
#define CANNM_ISDEF_TXPDUIDOFPBCHANNELCONFIG                          STD_OFF
#define CANNM_ISDEF_TXUSERDATAPDUIDOFPBCHANNELCONFIG                  STD_OFF
#define CANNM_ISDEF_SYSTONMCHIND                                      STD_OFF
#define CANNM_ISDEF_CHANNELCONFIGOFPCCONFIG                           STD_ON
#define CANNM_ISDEF_COMMSTATEOFPCCONFIG                               STD_ON
#define CANNM_ISDEF_COORDREADYTOSLEEPSTATEOFPCCONFIG                  STD_ON
#define CANNM_ISDEF_IMMEDIATENMMSGCOUNTOFPCCONFIG                     STD_ON
#define CANNM_ISDEF_MSGCONFIRMATIONFLAGOFPCCONFIG                     STD_ON
#define CANNM_ISDEF_MSGINDICATIONFLAGOFPCCONFIG                       STD_ON
#define CANNM_ISDEF_MSGREQUESTOFPCCONFIG                              STD_ON
#define CANNM_ISDEF_MSGTIMEOUTTIMEROFPCCONFIG                         STD_ON
#define CANNM_ISDEF_MSGTIMEROFPCCONFIG                                STD_ON
#define CANNM_ISDEF_NETWORKRESTARTFLAGOFPCCONFIG                      STD_ON
#define CANNM_ISDEF_NMSTATEOFPCCONFIG                                 STD_ON
#define CANNM_ISDEF_PBCHANNELCONFIGOFPCCONFIG                         STD_ON
#define CANNM_ISDEF_REPEATMSGBITINDFLAGOFPCCONFIG                     STD_ON
#define CANNM_ISDEF_REPEATMSGREQFLAGOFPCCONFIG                        STD_ON
#define CANNM_ISDEF_REPEATMSGTIMEROFPCCONFIG                          STD_ON
#define CANNM_ISDEF_RXMESSAGEDATAOFPCCONFIG                           STD_ON
#define CANNM_ISDEF_SYSTONMCHINDOFPCCONFIG                            STD_ON
#define CANNM_ISDEF_TIMEOUTTIMEROFPCCONFIG                            STD_ON
#define CANNM_ISDEF_TXCONTROLSTATEOFPCCONFIG                          STD_ON
#define CANNM_ISDEF_TXCONTROLSTATEREQUESTOFPCCONFIG                   STD_ON
#define CANNM_ISDEF_TXMESSAGEDATAOFPCCONFIG                           STD_ON
#define CANNM_ISDEF_WAITBUSSLEEPTIMEROFPCCONFIG                       STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCEqualsAlwaysToDefines  CanNm Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define CANNM_EQ2_CHANNELIDOFCHANNELCONFIG                            
#define CANNM_EQ2_COMCONTROLENABLEDOFCHANNELCONFIG                    
#define CANNM_EQ2_IMMEDIATENMCYCLETIMEOFCHANNELCONFIG                 
#define CANNM_EQ2_IMMEDIATENMTRANSMISSIONSOFCHANNELCONFIG             
#define CANNM_EQ2_MSGCYCLETIMEOFCHANNELCONFIG                         
#define CANNM_EQ2_MSGTIMEOUTTIMEOFCHANNELCONFIG                       
#define CANNM_EQ2_NODEDETECTIONENABLEDOFCHANNELCONFIG                 
#define CANNM_EQ2_NODEIDENABLEDOFCHANNELCONFIG                        
#define CANNM_EQ2_PDUCBVPOSITIONOFCHANNELCONFIG                       
#define CANNM_EQ2_PDUNIDPOSITIONOFCHANNELCONFIG                       
#define CANNM_EQ2_REMOTESLEEPINDTIMEOFCHANNELCONFIG                   
#define CANNM_EQ2_REPEATMESSAGETIMEOFCHANNELCONFIG                    
#define CANNM_EQ2_TIMEOUTTIMEOFCHANNELCONFIG                          
#define CANNM_EQ2_WAITBUSSLEEPTIMEOFCHANNELCONFIG                     
#define CANNM_EQ2_MSGCYCLEOFFSETOFPBCHANNELCONFIG                     
#define CANNM_EQ2_NODEIDOFPBCHANNELCONFIG                             
#define CANNM_EQ2_RXMESSAGEDATAENDIDXOFPBCHANNELCONFIG                
#define CANNM_EQ2_RXMESSAGEDATALENGTHOFPBCHANNELCONFIG                
#define CANNM_EQ2_RXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG              
#define CANNM_EQ2_RXMESSAGEDATAUSEDOFPBCHANNELCONFIG                  
#define CANNM_EQ2_RXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG               
#define CANNM_EQ2_RXMESSAGEDATA_CBVUSEDOFPBCHANNELCONFIG              
#define CANNM_EQ2_RXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG               
#define CANNM_EQ2_RXMESSAGEDATA_NIDUSEDOFPBCHANNELCONFIG              
#define CANNM_EQ2_RXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG       
#define CANNM_EQ2_RXMESSAGEDATA_USERDATALENGTHOFPBCHANNELCONFIG       
#define CANNM_EQ2_RXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG     
#define CANNM_EQ2_RXMESSAGEDATA_USERDATAUSEDOFPBCHANNELCONFIG         
#define CANNM_EQ2_TXMESSAGEDATAENDIDXOFPBCHANNELCONFIG                
#define CANNM_EQ2_TXMESSAGEDATALENGTHOFPBCHANNELCONFIG                
#define CANNM_EQ2_TXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG              
#define CANNM_EQ2_TXMESSAGEDATAUSEDOFPBCHANNELCONFIG                  
#define CANNM_EQ2_TXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG               
#define CANNM_EQ2_TXMESSAGEDATA_CBVUSEDOFPBCHANNELCONFIG              
#define CANNM_EQ2_TXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG               
#define CANNM_EQ2_TXMESSAGEDATA_NIDUSEDOFPBCHANNELCONFIG              
#define CANNM_EQ2_TXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG       
#define CANNM_EQ2_TXMESSAGEDATA_USERDATALENGTHOFPBCHANNELCONFIG       
#define CANNM_EQ2_TXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG     
#define CANNM_EQ2_TXMESSAGEDATA_USERDATAUSEDOFPBCHANNELCONFIG         
#define CANNM_EQ2_TXPDUIDOFPBCHANNELCONFIG                            
#define CANNM_EQ2_TXUSERDATAPDUIDOFPBCHANNELCONFIG                    
#define CANNM_EQ2_SYSTONMCHIND                                        
#define CANNM_EQ2_CHANNELCONFIGOFPCCONFIG                             CanNm_ChannelConfig
#define CANNM_EQ2_COMMSTATEOFPCCONFIG                                 CanNm_CommState.raw
#define CANNM_EQ2_COORDREADYTOSLEEPSTATEOFPCCONFIG                    CanNm_CoordReadyToSleepState.raw
#define CANNM_EQ2_IMMEDIATENMMSGCOUNTOFPCCONFIG                       CanNm_ImmediateNmMsgCount.raw
#define CANNM_EQ2_MSGCONFIRMATIONFLAGOFPCCONFIG                       CanNm_MsgConfirmationFlag.raw
#define CANNM_EQ2_MSGINDICATIONFLAGOFPCCONFIG                         CanNm_MsgIndicationFlag.raw
#define CANNM_EQ2_MSGREQUESTOFPCCONFIG                                CanNm_MsgRequest.raw
#define CANNM_EQ2_MSGTIMEOUTTIMEROFPCCONFIG                           CanNm_MsgTimeoutTimer.raw
#define CANNM_EQ2_MSGTIMEROFPCCONFIG                                  CanNm_MsgTimer.raw
#define CANNM_EQ2_NETWORKRESTARTFLAGOFPCCONFIG                        CanNm_NetworkRestartFlag.raw
#define CANNM_EQ2_NMSTATEOFPCCONFIG                                   CanNm_NmState.raw
#define CANNM_EQ2_PBCHANNELCONFIGOFPCCONFIG                           CanNm_PbChannelConfig
#define CANNM_EQ2_REPEATMSGBITINDFLAGOFPCCONFIG                       CanNm_RepeatMsgBitIndFlag.raw
#define CANNM_EQ2_REPEATMSGREQFLAGOFPCCONFIG                          CanNm_RepeatMsgReqFlag.raw
#define CANNM_EQ2_REPEATMSGTIMEROFPCCONFIG                            CanNm_RepeatMsgTimer.raw
#define CANNM_EQ2_RXMESSAGEDATAOFPCCONFIG                             CanNm_RxMessageData
#define CANNM_EQ2_SYSTONMCHINDOFPCCONFIG                              CanNm_SysToNmChInd
#define CANNM_EQ2_TIMEOUTTIMEROFPCCONFIG                              CanNm_TimeoutTimer.raw
#define CANNM_EQ2_TXCONTROLSTATEOFPCCONFIG                            CanNm_TxControlState.raw
#define CANNM_EQ2_TXCONTROLSTATEREQUESTOFPCCONFIG                     CanNm_TxControlStateRequest.raw
#define CANNM_EQ2_TXMESSAGEDATAOFPCCONFIG                             CanNm_TxMessageData
#define CANNM_EQ2_WAITBUSSLEEPTIMEROFPCCONFIG                         CanNm_WaitBusSleepTimer.raw
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCSymbolicInitializationPointers  CanNm Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define CanNm_Config_Ptr                                              NULL_PTR  /**< symbolic identifier which shall be used to initialize 'CanNm' */
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCInitializationSymbols  CanNm Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define CanNm_Config                                                  NULL_PTR  /**< symbolic identifier which could be used to initialize 'CanNm */
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCGeneral  CanNm General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define CANNM_CHECK_INIT_POINTER                                      STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define CANNM_FINAL_MAGIC_NUMBER                                      0x1F1Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of CanNm */
#define CANNM_INDIVIDUAL_POSTBUILD                                    STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'CanNm' is not configured to be postbuild capable. */
#define CANNM_INIT_DATA                                               CANNM_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define CANNM_INIT_DATA_HASH_CODE                                     305197115  /**< the precompile constant to validate the initialization structure at initialization time of CanNm with a hashcode. The seed value is '0x1F1Eu' */
#define CANNM_USE_ECUM_BSW_ERROR_HOOK                                 STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define CANNM_USE_INIT_POINTER                                        STD_OFF  /**< STD_ON if the init pointer CanNm shall be used. */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanNmPBDataSwitches  CanNm Data Switches  (POST_BUILD)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CANNM_PBCONFIG                                                STD_OFF  /**< Deactivateable: 'CanNm_PBConfig' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define CANNM_LTCONFIGIDXOFPBCONFIG                                   STD_OFF  /**< Deactivateable: 'CanNm_PBConfig.LTConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define CANNM_PCCONFIGIDXOFPBCONFIG                                   STD_OFF  /**< Deactivateable: 'CanNm_PBConfig.PCConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
/** 
  \}
*/ 



/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanNmPCGetConstantDuplicatedRootDataMacros  CanNm Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define CanNm_GetChannelConfigOfPCConfig()                            CanNm_ChannelConfig  /**< the pointer to CanNm_ChannelConfig */
#define CanNm_GetCommStateOfPCConfig()                                CanNm_CommState.raw  /**< the pointer to CanNm_CommState */
#define CanNm_GetCoordReadyToSleepStateOfPCConfig()                   CanNm_CoordReadyToSleepState.raw  /**< the pointer to CanNm_CoordReadyToSleepState */
#define CanNm_GetImmediateNmMsgCountOfPCConfig()                      CanNm_ImmediateNmMsgCount.raw  /**< the pointer to CanNm_ImmediateNmMsgCount */
#define CanNm_GetMsgConfirmationFlagOfPCConfig()                      CanNm_MsgConfirmationFlag.raw  /**< the pointer to CanNm_MsgConfirmationFlag */
#define CanNm_GetMsgIndicationFlagOfPCConfig()                        CanNm_MsgIndicationFlag.raw  /**< the pointer to CanNm_MsgIndicationFlag */
#define CanNm_GetMsgRequestOfPCConfig()                               CanNm_MsgRequest.raw  /**< the pointer to CanNm_MsgRequest */
#define CanNm_GetMsgTimeoutTimerOfPCConfig()                          CanNm_MsgTimeoutTimer.raw  /**< the pointer to CanNm_MsgTimeoutTimer */
#define CanNm_GetMsgTimerOfPCConfig()                                 CanNm_MsgTimer.raw  /**< the pointer to CanNm_MsgTimer */
#define CanNm_GetNetworkRestartFlagOfPCConfig()                       CanNm_NetworkRestartFlag.raw  /**< the pointer to CanNm_NetworkRestartFlag */
#define CanNm_GetNmStateOfPCConfig()                                  CanNm_NmState.raw  /**< the pointer to CanNm_NmState */
#define CanNm_GetPbChannelConfigOfPCConfig()                          CanNm_PbChannelConfig  /**< the pointer to CanNm_PbChannelConfig */
#define CanNm_GetRepeatMsgBitIndFlagOfPCConfig()                      CanNm_RepeatMsgBitIndFlag.raw  /**< the pointer to CanNm_RepeatMsgBitIndFlag */
#define CanNm_GetRepeatMsgReqFlagOfPCConfig()                         CanNm_RepeatMsgReqFlag.raw  /**< the pointer to CanNm_RepeatMsgReqFlag */
#define CanNm_GetRepeatMsgTimerOfPCConfig()                           CanNm_RepeatMsgTimer.raw  /**< the pointer to CanNm_RepeatMsgTimer */
#define CanNm_GetRxMessageDataOfPCConfig()                            CanNm_RxMessageData  /**< the pointer to CanNm_RxMessageData */
#define CanNm_GetSizeOfChannelConfigOfPCConfig()                      1u  /**< the number of accomplishable value elements in CanNm_ChannelConfig */
#define CanNm_GetSizeOfPbChannelConfigOfPCConfig()                    1u  /**< the number of accomplishable value elements in CanNm_PbChannelConfig */
#define CanNm_GetSizeOfSysToNmChIndOfPCConfig()                       1u  /**< the number of accomplishable value elements in CanNm_SysToNmChInd */
#define CanNm_GetSizeOfTxMessageDataOfPCConfig()                      8u  /**< the number of accomplishable value elements in CanNm_TxMessageData */
#define CanNm_GetSysToNmChIndOfPCConfig()                             CanNm_SysToNmChInd  /**< the pointer to CanNm_SysToNmChInd */
#define CanNm_GetTimeoutTimerOfPCConfig()                             CanNm_TimeoutTimer.raw  /**< the pointer to CanNm_TimeoutTimer */
#define CanNm_GetTxControlStateOfPCConfig()                           CanNm_TxControlState.raw  /**< the pointer to CanNm_TxControlState */
#define CanNm_GetTxControlStateRequestOfPCConfig()                    CanNm_TxControlStateRequest.raw  /**< the pointer to CanNm_TxControlStateRequest */
#define CanNm_GetTxMessageDataOfPCConfig()                            CanNm_TxMessageData  /**< the pointer to CanNm_TxMessageData */
#define CanNm_GetWaitBusSleepTimerOfPCConfig()                        CanNm_WaitBusSleepTimer.raw  /**< the pointer to CanNm_WaitBusSleepTimer */
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCGetDuplicatedRootDataMacros  CanNm Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define CanNm_GetSizeOfCommStateOfPCConfig()                          CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_CommState */
#define CanNm_GetSizeOfCoordReadyToSleepStateOfPCConfig()             CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_CoordReadyToSleepState */
#define CanNm_GetSizeOfImmediateNmMsgCountOfPCConfig()                CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_ImmediateNmMsgCount */
#define CanNm_GetSizeOfMsgConfirmationFlagOfPCConfig()                CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_MsgConfirmationFlag */
#define CanNm_GetSizeOfMsgIndicationFlagOfPCConfig()                  CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_MsgIndicationFlag */
#define CanNm_GetSizeOfMsgRequestOfPCConfig()                         CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_MsgRequest */
#define CanNm_GetSizeOfMsgTimeoutTimerOfPCConfig()                    CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_MsgTimeoutTimer */
#define CanNm_GetSizeOfMsgTimerOfPCConfig()                           CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_MsgTimer */
#define CanNm_GetSizeOfNetworkRestartFlagOfPCConfig()                 CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_NetworkRestartFlag */
#define CanNm_GetSizeOfNmStateOfPCConfig()                            CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_NmState */
#define CanNm_GetSizeOfRepeatMsgBitIndFlagOfPCConfig()                CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_RepeatMsgBitIndFlag */
#define CanNm_GetSizeOfRepeatMsgReqFlagOfPCConfig()                   CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_RepeatMsgReqFlag */
#define CanNm_GetSizeOfRepeatMsgTimerOfPCConfig()                     CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_RepeatMsgTimer */
#define CanNm_GetSizeOfTimeoutTimerOfPCConfig()                       CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_TimeoutTimer */
#define CanNm_GetSizeOfTxControlStateOfPCConfig()                     CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_TxControlState */
#define CanNm_GetSizeOfTxControlStateRequestOfPCConfig()              CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_TxControlStateRequest */
#define CanNm_GetSizeOfWaitBusSleepTimerOfPCConfig()                  CanNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in CanNm_WaitBusSleepTimer */
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCGetDataMacros  CanNm Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define CanNm_GetChannelIdOfChannelConfig(Index)                      ((NetworkHandleType)CanNm_GetChannelConfigOfPCConfig()[(Index)].ChannelIdOfChannelConfig)
#define CanNm_IsComControlEnabledOfChannelConfig(Index)               ((CanNm_GetChannelConfigOfPCConfig()[(Index)].ComControlEnabledOfChannelConfig) != FALSE)
#define CanNm_GetImmediateNmCycleTimeOfChannelConfig(Index)           (CanNm_GetChannelConfigOfPCConfig()[(Index)].ImmediateNmCycleTimeOfChannelConfig)
#define CanNm_GetImmediateNmTransmissionsOfChannelConfig(Index)       (CanNm_GetChannelConfigOfPCConfig()[(Index)].ImmediateNmTransmissionsOfChannelConfig)
#define CanNm_GetMsgCycleTimeOfChannelConfig(Index)                   (CanNm_GetChannelConfigOfPCConfig()[(Index)].MsgCycleTimeOfChannelConfig)
#define CanNm_GetMsgTimeoutTimeOfChannelConfig(Index)                 (CanNm_GetChannelConfigOfPCConfig()[(Index)].MsgTimeoutTimeOfChannelConfig)
#define CanNm_IsNodeDetectionEnabledOfChannelConfig(Index)            ((CanNm_GetChannelConfigOfPCConfig()[(Index)].NodeDetectionEnabledOfChannelConfig) != FALSE)
#define CanNm_IsNodeIdEnabledOfChannelConfig(Index)                   ((CanNm_GetChannelConfigOfPCConfig()[(Index)].NodeIdEnabledOfChannelConfig) != FALSE)
#define CanNm_GetPduCbvPositionOfChannelConfig(Index)                 (CanNm_GetChannelConfigOfPCConfig()[(Index)].PduCbvPositionOfChannelConfig)
#define CanNm_GetPduNidPositionOfChannelConfig(Index)                 (CanNm_GetChannelConfigOfPCConfig()[(Index)].PduNidPositionOfChannelConfig)
#define CanNm_GetRemoteSleepIndTimeOfChannelConfig(Index)             (CanNm_GetChannelConfigOfPCConfig()[(Index)].RemoteSleepIndTimeOfChannelConfig)
#define CanNm_GetRepeatMessageTimeOfChannelConfig(Index)              (CanNm_GetChannelConfigOfPCConfig()[(Index)].RepeatMessageTimeOfChannelConfig)
#define CanNm_GetTimeoutTimeOfChannelConfig(Index)                    (CanNm_GetChannelConfigOfPCConfig()[(Index)].TimeoutTimeOfChannelConfig)
#define CanNm_GetWaitBusSleepTimeOfChannelConfig(Index)               (CanNm_GetChannelConfigOfPCConfig()[(Index)].WaitBusSleepTimeOfChannelConfig)
#define CanNm_GetCommState(Index)                                     (CanNm_GetCommStateOfPCConfig()[(Index)])
#define CanNm_GetCoordReadyToSleepState(Index)                        (CanNm_GetCoordReadyToSleepStateOfPCConfig()[(Index)])
#define CanNm_GetImmediateNmMsgCount(Index)                           (CanNm_GetImmediateNmMsgCountOfPCConfig()[(Index)])
#define CanNm_IsMsgConfirmationFlag(Index)                            ((CanNm_GetMsgConfirmationFlagOfPCConfig()[(Index)]) != FALSE)
#define CanNm_IsMsgIndicationFlag(Index)                              ((CanNm_GetMsgIndicationFlagOfPCConfig()[(Index)]) != FALSE)
#define CanNm_GetMsgRequest(Index)                                    (CanNm_GetMsgRequestOfPCConfig()[(Index)])
#define CanNm_GetMsgTimeoutTimer(Index)                               (CanNm_GetMsgTimeoutTimerOfPCConfig()[(Index)])
#define CanNm_GetMsgTimer(Index)                                      (CanNm_GetMsgTimerOfPCConfig()[(Index)])
#define CanNm_GetNetworkRestartFlag(Index)                            (CanNm_GetNetworkRestartFlagOfPCConfig()[(Index)])
#define CanNm_GetNmState(Index)                                       (CanNm_GetNmStateOfPCConfig()[(Index)])
#define CanNm_GetMsgCycleOffsetOfPbChannelConfig(Index)               (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].MsgCycleOffsetOfPbChannelConfig)
#define CanNm_GetNodeIdOfPbChannelConfig(Index)                       (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].NodeIdOfPbChannelConfig)
#define CanNm_GetRxMessageDataEndIdxOfPbChannelConfig(Index)          (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].RxMessageDataEndIdxOfPbChannelConfig)
#define CanNm_GetRxMessageDataLengthOfPbChannelConfig(Index)          (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].RxMessageDataLengthOfPbChannelConfig)
#define CanNm_GetRxMessageDataStartIdxOfPbChannelConfig(Index)        (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].RxMessageDataStartIdxOfPbChannelConfig)
#define CanNm_GetRxMessageData_CBVIdxOfPbChannelConfig(Index)         (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].RxMessageData_CBVIdxOfPbChannelConfig)
#define CanNm_GetRxMessageData_NIDIdxOfPbChannelConfig(Index)         (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].RxMessageData_NIDIdxOfPbChannelConfig)
#define CanNm_GetRxMessageData_UserDataEndIdxOfPbChannelConfig(Index) (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].RxMessageData_UserDataEndIdxOfPbChannelConfig)
#define CanNm_GetRxMessageData_UserDataLengthOfPbChannelConfig(Index) (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].RxMessageData_UserDataLengthOfPbChannelConfig)
#define CanNm_GetRxMessageData_UserDataStartIdxOfPbChannelConfig(Index) (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].RxMessageData_UserDataStartIdxOfPbChannelConfig)
#define CanNm_GetTxMessageDataEndIdxOfPbChannelConfig(Index)          (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageDataEndIdxOfPbChannelConfig)
#define CanNm_GetTxMessageDataLengthOfPbChannelConfig(Index)          (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageDataLengthOfPbChannelConfig)
#define CanNm_GetTxMessageDataStartIdxOfPbChannelConfig(Index)        (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageDataStartIdxOfPbChannelConfig)
#define CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(Index)         (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageData_CBVIdxOfPbChannelConfig)
#define CanNm_GetTxMessageData_NIDIdxOfPbChannelConfig(Index)         (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageData_NIDIdxOfPbChannelConfig)
#define CanNm_GetTxMessageData_UserDataEndIdxOfPbChannelConfig(Index) (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageData_UserDataEndIdxOfPbChannelConfig)
#define CanNm_GetTxMessageData_UserDataLengthOfPbChannelConfig(Index) (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageData_UserDataLengthOfPbChannelConfig)
#define CanNm_GetTxMessageData_UserDataStartIdxOfPbChannelConfig(Index) (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageData_UserDataStartIdxOfPbChannelConfig)
#define CanNm_GetTxPduIdOfPbChannelConfig(Index)                      (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].TxPduIdOfPbChannelConfig)
#define CanNm_GetTxUserDataPduIdOfPbChannelConfig(Index)              (CanNm_GetPbChannelConfigOfPCConfig()[(Index)].TxUserDataPduIdOfPbChannelConfig)
#define CanNm_IsRepeatMsgBitIndFlag(Index)                            ((CanNm_GetRepeatMsgBitIndFlagOfPCConfig()[(Index)]) != FALSE)
#define CanNm_IsRepeatMsgReqFlag(Index)                               ((CanNm_GetRepeatMsgReqFlagOfPCConfig()[(Index)]) != FALSE)
#define CanNm_GetRepeatMsgTimer(Index)                                (CanNm_GetRepeatMsgTimerOfPCConfig()[(Index)])
#define CanNm_GetRxMessageData(Index)                                 (CanNm_GetRxMessageDataOfPCConfig()[(Index)])
#define CanNm_GetSysToNmChInd(Index)                                  (CanNm_GetSysToNmChIndOfPCConfig()[(Index)])
#define CanNm_GetTimeoutTimer(Index)                                  (CanNm_GetTimeoutTimerOfPCConfig()[(Index)])
#define CanNm_GetTxControlState(Index)                                (CanNm_GetTxControlStateOfPCConfig()[(Index)])
#define CanNm_GetTxControlStateRequest(Index)                         (CanNm_GetTxControlStateRequestOfPCConfig()[(Index)])
#define CanNm_GetTxMessageData(Index)                                 (CanNm_GetTxMessageDataOfPCConfig()[(Index)])
#define CanNm_GetWaitBusSleepTimer(Index)                             (CanNm_GetWaitBusSleepTimerOfPCConfig()[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCGetDeduplicatedDataMacros  CanNm Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define CanNm_IsRxMessageDataUsedOfPbChannelConfig(Index)             (((boolean)(CanNm_GetRxMessageDataLengthOfPbChannelConfig(Index) != 0u)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to CanNm_RxMessageData */
#define CanNm_IsRxMessageData_CBVUsedOfPbChannelConfig(Index)         (((boolean)(CanNm_GetRxMessageData_CBVIdxOfPbChannelConfig(Index) != CANNM_NO_RXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to CanNm_RxMessageData */
#define CanNm_IsRxMessageData_NIDUsedOfPbChannelConfig(Index)         (((boolean)(CanNm_GetRxMessageData_NIDIdxOfPbChannelConfig(Index) != CANNM_NO_RXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to CanNm_RxMessageData */
#define CanNm_IsRxMessageData_UserDataUsedOfPbChannelConfig(Index)    (((boolean)(CanNm_GetRxMessageData_UserDataLengthOfPbChannelConfig(Index) != 0u)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to CanNm_RxMessageData */
#define CanNm_IsTxMessageDataUsedOfPbChannelConfig(Index)             (((boolean)(CanNm_GetTxMessageDataLengthOfPbChannelConfig(Index) != 0u)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to CanNm_TxMessageData */
#define CanNm_IsTxMessageData_CBVUsedOfPbChannelConfig(Index)         (((boolean)(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(Index) != CANNM_NO_TXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to CanNm_TxMessageData */
#define CanNm_IsTxMessageData_NIDUsedOfPbChannelConfig(Index)         (((boolean)(CanNm_GetTxMessageData_NIDIdxOfPbChannelConfig(Index) != CANNM_NO_TXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to CanNm_TxMessageData */
#define CanNm_IsTxMessageData_UserDataUsedOfPbChannelConfig(Index)    (((boolean)(CanNm_GetTxMessageData_UserDataLengthOfPbChannelConfig(Index) != 0u)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to CanNm_TxMessageData */
#define CanNm_GetSizeOfChannelConfig()                                CanNm_GetSizeOfChannelConfigOfPCConfig()
#define CanNm_GetSizeOfCommState()                                    CanNm_GetSizeOfCommStateOfPCConfig()
#define CanNm_GetSizeOfCoordReadyToSleepState()                       CanNm_GetSizeOfCoordReadyToSleepStateOfPCConfig()
#define CanNm_GetSizeOfImmediateNmMsgCount()                          CanNm_GetSizeOfImmediateNmMsgCountOfPCConfig()
#define CanNm_GetSizeOfMsgConfirmationFlag()                          CanNm_GetSizeOfMsgConfirmationFlagOfPCConfig()
#define CanNm_GetSizeOfMsgIndicationFlag()                            CanNm_GetSizeOfMsgIndicationFlagOfPCConfig()
#define CanNm_GetSizeOfMsgRequest()                                   CanNm_GetSizeOfMsgRequestOfPCConfig()
#define CanNm_GetSizeOfMsgTimeoutTimer()                              CanNm_GetSizeOfMsgTimeoutTimerOfPCConfig()
#define CanNm_GetSizeOfMsgTimer()                                     CanNm_GetSizeOfMsgTimerOfPCConfig()
#define CanNm_GetSizeOfNetworkRestartFlag()                           CanNm_GetSizeOfNetworkRestartFlagOfPCConfig()
#define CanNm_GetSizeOfNmState()                                      CanNm_GetSizeOfNmStateOfPCConfig()
#define CanNm_GetSizeOfPbChannelConfig()                              CanNm_GetSizeOfPbChannelConfigOfPCConfig()
#define CanNm_GetSizeOfRepeatMsgBitIndFlag()                          CanNm_GetSizeOfRepeatMsgBitIndFlagOfPCConfig()
#define CanNm_GetSizeOfRepeatMsgReqFlag()                             CanNm_GetSizeOfRepeatMsgReqFlagOfPCConfig()
#define CanNm_GetSizeOfRepeatMsgTimer()                               CanNm_GetSizeOfRepeatMsgTimerOfPCConfig()
#define CanNm_GetSizeOfSysToNmChInd()                                 CanNm_GetSizeOfSysToNmChIndOfPCConfig()
#define CanNm_GetSizeOfTimeoutTimer()                                 CanNm_GetSizeOfTimeoutTimerOfPCConfig()
#define CanNm_GetSizeOfTxControlState()                               CanNm_GetSizeOfTxControlStateOfPCConfig()
#define CanNm_GetSizeOfTxControlStateRequest()                        CanNm_GetSizeOfTxControlStateRequestOfPCConfig()
#define CanNm_GetSizeOfTxMessageData()                                CanNm_GetSizeOfTxMessageDataOfPCConfig()
#define CanNm_GetSizeOfWaitBusSleepTimer()                            CanNm_GetSizeOfWaitBusSleepTimerOfPCConfig()
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCSetDataMacros  CanNm Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define CanNm_SetCommState(Index, Value)                              CanNm_GetCommStateOfPCConfig()[(Index)] = (Value)
#define CanNm_SetCoordReadyToSleepState(Index, Value)                 CanNm_GetCoordReadyToSleepStateOfPCConfig()[(Index)] = (Value)
#define CanNm_SetImmediateNmMsgCount(Index, Value)                    CanNm_GetImmediateNmMsgCountOfPCConfig()[(Index)] = (Value)
#define CanNm_SetMsgConfirmationFlag(Index, Value)                    CanNm_GetMsgConfirmationFlagOfPCConfig()[(Index)] = (Value)
#define CanNm_SetMsgIndicationFlag(Index, Value)                      CanNm_GetMsgIndicationFlagOfPCConfig()[(Index)] = (Value)
#define CanNm_SetMsgRequest(Index, Value)                             CanNm_GetMsgRequestOfPCConfig()[(Index)] = (Value)
#define CanNm_SetMsgTimeoutTimer(Index, Value)                        CanNm_GetMsgTimeoutTimerOfPCConfig()[(Index)] = (Value)
#define CanNm_SetMsgTimer(Index, Value)                               CanNm_GetMsgTimerOfPCConfig()[(Index)] = (Value)
#define CanNm_SetNetworkRestartFlag(Index, Value)                     CanNm_GetNetworkRestartFlagOfPCConfig()[(Index)] = (Value)
#define CanNm_SetNmState(Index, Value)                                CanNm_GetNmStateOfPCConfig()[(Index)] = (Value)
#define CanNm_SetRepeatMsgBitIndFlag(Index, Value)                    CanNm_GetRepeatMsgBitIndFlagOfPCConfig()[(Index)] = (Value)
#define CanNm_SetRepeatMsgReqFlag(Index, Value)                       CanNm_GetRepeatMsgReqFlagOfPCConfig()[(Index)] = (Value)
#define CanNm_SetRepeatMsgTimer(Index, Value)                         CanNm_GetRepeatMsgTimerOfPCConfig()[(Index)] = (Value)
#define CanNm_SetRxMessageData(Index, Value)                          CanNm_GetRxMessageDataOfPCConfig()[(Index)] = (Value)
#define CanNm_SetTimeoutTimer(Index, Value)                           CanNm_GetTimeoutTimerOfPCConfig()[(Index)] = (Value)
#define CanNm_SetTxControlState(Index, Value)                         CanNm_GetTxControlStateOfPCConfig()[(Index)] = (Value)
#define CanNm_SetTxControlStateRequest(Index, Value)                  CanNm_GetTxControlStateRequestOfPCConfig()[(Index)] = (Value)
#define CanNm_SetTxMessageData(Index, Value)                          CanNm_GetTxMessageDataOfPCConfig()[(Index)] = (Value)
#define CanNm_SetWaitBusSleepTimer(Index, Value)                      CanNm_GetWaitBusSleepTimerOfPCConfig()[(Index)] = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCGetAddressOfDataMacros  CanNm Get Address Of Data Macros (PRE_COMPILE)
  \brief  These macros can be used to get the data by the address operator.
  \{
*/ 
#define CanNm_GetAddrNmState(Index)                                   (&CanNm_GetNmState(Index))
#define CanNm_GetAddrRxMessageData(Index)                             (&CanNm_GetRxMessageData(Index))
#define CanNm_GetAddrTxMessageData(Index)                             (&CanNm_GetTxMessageData(Index))
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCHasMacros  CanNm Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define CanNm_HasChannelConfig()                                      (TRUE != FALSE)
#define CanNm_HasChannelIdOfChannelConfig()                           (TRUE != FALSE)
#define CanNm_HasComControlEnabledOfChannelConfig()                   (TRUE != FALSE)
#define CanNm_HasImmediateNmCycleTimeOfChannelConfig()                (TRUE != FALSE)
#define CanNm_HasImmediateNmTransmissionsOfChannelConfig()            (TRUE != FALSE)
#define CanNm_HasMsgCycleTimeOfChannelConfig()                        (TRUE != FALSE)
#define CanNm_HasMsgTimeoutTimeOfChannelConfig()                      (TRUE != FALSE)
#define CanNm_HasNodeDetectionEnabledOfChannelConfig()                (TRUE != FALSE)
#define CanNm_HasNodeIdEnabledOfChannelConfig()                       (TRUE != FALSE)
#define CanNm_HasPduCbvPositionOfChannelConfig()                      (TRUE != FALSE)
#define CanNm_HasPduNidPositionOfChannelConfig()                      (TRUE != FALSE)
#define CanNm_HasRemoteSleepIndTimeOfChannelConfig()                  (TRUE != FALSE)
#define CanNm_HasRepeatMessageTimeOfChannelConfig()                   (TRUE != FALSE)
#define CanNm_HasTimeoutTimeOfChannelConfig()                         (TRUE != FALSE)
#define CanNm_HasWaitBusSleepTimeOfChannelConfig()                    (TRUE != FALSE)
#define CanNm_HasCommState()                                          (TRUE != FALSE)
#define CanNm_HasCoordReadyToSleepState()                             (TRUE != FALSE)
#define CanNm_HasImmediateNmMsgCount()                                (TRUE != FALSE)
#define CanNm_HasMsgConfirmationFlag()                                (TRUE != FALSE)
#define CanNm_HasMsgIndicationFlag()                                  (TRUE != FALSE)
#define CanNm_HasMsgRequest()                                         (TRUE != FALSE)
#define CanNm_HasMsgTimeoutTimer()                                    (TRUE != FALSE)
#define CanNm_HasMsgTimer()                                           (TRUE != FALSE)
#define CanNm_HasNetworkRestartFlag()                                 (TRUE != FALSE)
#define CanNm_HasNmState()                                            (TRUE != FALSE)
#define CanNm_HasPbChannelConfig()                                    (TRUE != FALSE)
#define CanNm_HasMsgCycleOffsetOfPbChannelConfig()                    (TRUE != FALSE)
#define CanNm_HasNodeIdOfPbChannelConfig()                            (TRUE != FALSE)
#define CanNm_HasRxMessageDataEndIdxOfPbChannelConfig()               (TRUE != FALSE)
#define CanNm_HasRxMessageDataLengthOfPbChannelConfig()               (TRUE != FALSE)
#define CanNm_HasRxMessageDataStartIdxOfPbChannelConfig()             (TRUE != FALSE)
#define CanNm_HasRxMessageDataUsedOfPbChannelConfig()                 (TRUE != FALSE)
#define CanNm_HasRxMessageData_CBVIdxOfPbChannelConfig()              (TRUE != FALSE)
#define CanNm_HasRxMessageData_CBVUsedOfPbChannelConfig()             (TRUE != FALSE)
#define CanNm_HasRxMessageData_NIDIdxOfPbChannelConfig()              (TRUE != FALSE)
#define CanNm_HasRxMessageData_NIDUsedOfPbChannelConfig()             (TRUE != FALSE)
#define CanNm_HasRxMessageData_UserDataEndIdxOfPbChannelConfig()      (TRUE != FALSE)
#define CanNm_HasRxMessageData_UserDataLengthOfPbChannelConfig()      (TRUE != FALSE)
#define CanNm_HasRxMessageData_UserDataStartIdxOfPbChannelConfig()    (TRUE != FALSE)
#define CanNm_HasRxMessageData_UserDataUsedOfPbChannelConfig()        (TRUE != FALSE)
#define CanNm_HasTxMessageDataEndIdxOfPbChannelConfig()               (TRUE != FALSE)
#define CanNm_HasTxMessageDataLengthOfPbChannelConfig()               (TRUE != FALSE)
#define CanNm_HasTxMessageDataStartIdxOfPbChannelConfig()             (TRUE != FALSE)
#define CanNm_HasTxMessageDataUsedOfPbChannelConfig()                 (TRUE != FALSE)
#define CanNm_HasTxMessageData_CBVIdxOfPbChannelConfig()              (TRUE != FALSE)
#define CanNm_HasTxMessageData_CBVUsedOfPbChannelConfig()             (TRUE != FALSE)
#define CanNm_HasTxMessageData_NIDIdxOfPbChannelConfig()              (TRUE != FALSE)
#define CanNm_HasTxMessageData_NIDUsedOfPbChannelConfig()             (TRUE != FALSE)
#define CanNm_HasTxMessageData_UserDataEndIdxOfPbChannelConfig()      (TRUE != FALSE)
#define CanNm_HasTxMessageData_UserDataLengthOfPbChannelConfig()      (TRUE != FALSE)
#define CanNm_HasTxMessageData_UserDataStartIdxOfPbChannelConfig()    (TRUE != FALSE)
#define CanNm_HasTxMessageData_UserDataUsedOfPbChannelConfig()        (TRUE != FALSE)
#define CanNm_HasTxPduIdOfPbChannelConfig()                           (TRUE != FALSE)
#define CanNm_HasTxUserDataPduIdOfPbChannelConfig()                   (TRUE != FALSE)
#define CanNm_HasRepeatMsgBitIndFlag()                                (TRUE != FALSE)
#define CanNm_HasRepeatMsgReqFlag()                                   (TRUE != FALSE)
#define CanNm_HasRepeatMsgTimer()                                     (TRUE != FALSE)
#define CanNm_HasRxMessageData()                                      (TRUE != FALSE)
#define CanNm_HasSizeOfChannelConfig()                                (TRUE != FALSE)
#define CanNm_HasSizeOfCommState()                                    (TRUE != FALSE)
#define CanNm_HasSizeOfCoordReadyToSleepState()                       (TRUE != FALSE)
#define CanNm_HasSizeOfImmediateNmMsgCount()                          (TRUE != FALSE)
#define CanNm_HasSizeOfMsgConfirmationFlag()                          (TRUE != FALSE)
#define CanNm_HasSizeOfMsgIndicationFlag()                            (TRUE != FALSE)
#define CanNm_HasSizeOfMsgRequest()                                   (TRUE != FALSE)
#define CanNm_HasSizeOfMsgTimeoutTimer()                              (TRUE != FALSE)
#define CanNm_HasSizeOfMsgTimer()                                     (TRUE != FALSE)
#define CanNm_HasSizeOfNetworkRestartFlag()                           (TRUE != FALSE)
#define CanNm_HasSizeOfNmState()                                      (TRUE != FALSE)
#define CanNm_HasSizeOfPbChannelConfig()                              (TRUE != FALSE)
#define CanNm_HasSizeOfRepeatMsgBitIndFlag()                          (TRUE != FALSE)
#define CanNm_HasSizeOfRepeatMsgReqFlag()                             (TRUE != FALSE)
#define CanNm_HasSizeOfRepeatMsgTimer()                               (TRUE != FALSE)
#define CanNm_HasSizeOfSysToNmChInd()                                 (TRUE != FALSE)
#define CanNm_HasSizeOfTimeoutTimer()                                 (TRUE != FALSE)
#define CanNm_HasSizeOfTxControlState()                               (TRUE != FALSE)
#define CanNm_HasSizeOfTxControlStateRequest()                        (TRUE != FALSE)
#define CanNm_HasSizeOfTxMessageData()                                (TRUE != FALSE)
#define CanNm_HasSizeOfWaitBusSleepTimer()                            (TRUE != FALSE)
#define CanNm_HasSysToNmChInd()                                       (TRUE != FALSE)
#define CanNm_HasTimeoutTimer()                                       (TRUE != FALSE)
#define CanNm_HasTxControlState()                                     (TRUE != FALSE)
#define CanNm_HasTxControlStateRequest()                              (TRUE != FALSE)
#define CanNm_HasTxMessageData()                                      (TRUE != FALSE)
#define CanNm_HasWaitBusSleepTimer()                                  (TRUE != FALSE)
#define CanNm_HasPCConfig()                                           (TRUE != FALSE)
#define CanNm_HasChannelConfigOfPCConfig()                            (TRUE != FALSE)
#define CanNm_HasCommStateOfPCConfig()                                (TRUE != FALSE)
#define CanNm_HasCoordReadyToSleepStateOfPCConfig()                   (TRUE != FALSE)
#define CanNm_HasImmediateNmMsgCountOfPCConfig()                      (TRUE != FALSE)
#define CanNm_HasMsgConfirmationFlagOfPCConfig()                      (TRUE != FALSE)
#define CanNm_HasMsgIndicationFlagOfPCConfig()                        (TRUE != FALSE)
#define CanNm_HasMsgRequestOfPCConfig()                               (TRUE != FALSE)
#define CanNm_HasMsgTimeoutTimerOfPCConfig()                          (TRUE != FALSE)
#define CanNm_HasMsgTimerOfPCConfig()                                 (TRUE != FALSE)
#define CanNm_HasNetworkRestartFlagOfPCConfig()                       (TRUE != FALSE)
#define CanNm_HasNmStateOfPCConfig()                                  (TRUE != FALSE)
#define CanNm_HasPbChannelConfigOfPCConfig()                          (TRUE != FALSE)
#define CanNm_HasRepeatMsgBitIndFlagOfPCConfig()                      (TRUE != FALSE)
#define CanNm_HasRepeatMsgReqFlagOfPCConfig()                         (TRUE != FALSE)
#define CanNm_HasRepeatMsgTimerOfPCConfig()                           (TRUE != FALSE)
#define CanNm_HasRxMessageDataOfPCConfig()                            (TRUE != FALSE)
#define CanNm_HasSizeOfChannelConfigOfPCConfig()                      (TRUE != FALSE)
#define CanNm_HasSizeOfCommStateOfPCConfig()                          (TRUE != FALSE)
#define CanNm_HasSizeOfCoordReadyToSleepStateOfPCConfig()             (TRUE != FALSE)
#define CanNm_HasSizeOfImmediateNmMsgCountOfPCConfig()                (TRUE != FALSE)
#define CanNm_HasSizeOfMsgConfirmationFlagOfPCConfig()                (TRUE != FALSE)
#define CanNm_HasSizeOfMsgIndicationFlagOfPCConfig()                  (TRUE != FALSE)
#define CanNm_HasSizeOfMsgRequestOfPCConfig()                         (TRUE != FALSE)
#define CanNm_HasSizeOfMsgTimeoutTimerOfPCConfig()                    (TRUE != FALSE)
#define CanNm_HasSizeOfMsgTimerOfPCConfig()                           (TRUE != FALSE)
#define CanNm_HasSizeOfNetworkRestartFlagOfPCConfig()                 (TRUE != FALSE)
#define CanNm_HasSizeOfNmStateOfPCConfig()                            (TRUE != FALSE)
#define CanNm_HasSizeOfPbChannelConfigOfPCConfig()                    (TRUE != FALSE)
#define CanNm_HasSizeOfRepeatMsgBitIndFlagOfPCConfig()                (TRUE != FALSE)
#define CanNm_HasSizeOfRepeatMsgReqFlagOfPCConfig()                   (TRUE != FALSE)
#define CanNm_HasSizeOfRepeatMsgTimerOfPCConfig()                     (TRUE != FALSE)
#define CanNm_HasSizeOfSysToNmChIndOfPCConfig()                       (TRUE != FALSE)
#define CanNm_HasSizeOfTimeoutTimerOfPCConfig()                       (TRUE != FALSE)
#define CanNm_HasSizeOfTxControlStateOfPCConfig()                     (TRUE != FALSE)
#define CanNm_HasSizeOfTxControlStateRequestOfPCConfig()              (TRUE != FALSE)
#define CanNm_HasSizeOfTxMessageDataOfPCConfig()                      (TRUE != FALSE)
#define CanNm_HasSizeOfWaitBusSleepTimerOfPCConfig()                  (TRUE != FALSE)
#define CanNm_HasSysToNmChIndOfPCConfig()                             (TRUE != FALSE)
#define CanNm_HasTimeoutTimerOfPCConfig()                             (TRUE != FALSE)
#define CanNm_HasTxControlStateOfPCConfig()                           (TRUE != FALSE)
#define CanNm_HasTxControlStateRequestOfPCConfig()                    (TRUE != FALSE)
#define CanNm_HasTxMessageDataOfPCConfig()                            (TRUE != FALSE)
#define CanNm_HasWaitBusSleepTimerOfPCConfig()                        (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCIncrementDataMacros  CanNm Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define CanNm_IncCommState(Index)                                     CanNm_GetCommState(Index)++
#define CanNm_IncCoordReadyToSleepState(Index)                        CanNm_GetCoordReadyToSleepState(Index)++
#define CanNm_IncImmediateNmMsgCount(Index)                           CanNm_GetImmediateNmMsgCount(Index)++
#define CanNm_IncMsgRequest(Index)                                    CanNm_GetMsgRequest(Index)++
#define CanNm_IncMsgTimeoutTimer(Index)                               CanNm_GetMsgTimeoutTimer(Index)++
#define CanNm_IncMsgTimer(Index)                                      CanNm_GetMsgTimer(Index)++
#define CanNm_IncNetworkRestartFlag(Index)                            CanNm_GetNetworkRestartFlag(Index)++
#define CanNm_IncNmState(Index)                                       CanNm_GetNmState(Index)++
#define CanNm_IncRepeatMsgTimer(Index)                                CanNm_GetRepeatMsgTimer(Index)++
#define CanNm_IncRxMessageData(Index)                                 CanNm_GetRxMessageData(Index)++
#define CanNm_IncTimeoutTimer(Index)                                  CanNm_GetTimeoutTimer(Index)++
#define CanNm_IncTxControlState(Index)                                CanNm_GetTxControlState(Index)++
#define CanNm_IncTxControlStateRequest(Index)                         CanNm_GetTxControlStateRequest(Index)++
#define CanNm_IncTxMessageData(Index)                                 CanNm_GetTxMessageData(Index)++
#define CanNm_IncWaitBusSleepTimer(Index)                             CanNm_GetWaitBusSleepTimer(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCDecrementDataMacros  CanNm Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define CanNm_DecCommState(Index)                                     CanNm_GetCommState(Index)--
#define CanNm_DecCoordReadyToSleepState(Index)                        CanNm_GetCoordReadyToSleepState(Index)--
#define CanNm_DecImmediateNmMsgCount(Index)                           CanNm_GetImmediateNmMsgCount(Index)--
#define CanNm_DecMsgRequest(Index)                                    CanNm_GetMsgRequest(Index)--
#define CanNm_DecMsgTimeoutTimer(Index)                               CanNm_GetMsgTimeoutTimer(Index)--
#define CanNm_DecMsgTimer(Index)                                      CanNm_GetMsgTimer(Index)--
#define CanNm_DecNetworkRestartFlag(Index)                            CanNm_GetNetworkRestartFlag(Index)--
#define CanNm_DecNmState(Index)                                       CanNm_GetNmState(Index)--
#define CanNm_DecRepeatMsgTimer(Index)                                CanNm_GetRepeatMsgTimer(Index)--
#define CanNm_DecRxMessageData(Index)                                 CanNm_GetRxMessageData(Index)--
#define CanNm_DecTimeoutTimer(Index)                                  CanNm_GetTimeoutTimer(Index)--
#define CanNm_DecTxControlState(Index)                                CanNm_GetTxControlState(Index)--
#define CanNm_DecTxControlStateRequest(Index)                         CanNm_GetTxControlStateRequest(Index)--
#define CanNm_DecTxMessageData(Index)                                 CanNm_GetTxMessageData(Index)--
#define CanNm_DecWaitBusSleepTimer(Index)                             CanNm_GetWaitBusSleepTimer(Index)--
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
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
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  CanNmPCIterableTypes  CanNm Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate CanNm_ChannelConfig */
typedef uint8_least CanNm_ChannelConfigIterType;

/**   \brief  type used to iterate CanNm_PbChannelConfig */
typedef uint8_least CanNm_PbChannelConfigIterType;

/**   \brief  type used to iterate CanNm_RxMessageData */
typedef uint8_least CanNm_RxMessageDataIterType;

/**   \brief  type used to iterate CanNm_SysToNmChInd */
typedef uint8_least CanNm_SysToNmChIndIterType;

/**   \brief  type used to iterate CanNm_TxMessageData */
typedef uint8_least CanNm_TxMessageDataIterType;

/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCIterableTypesWithSizeRelations  CanNm Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate CanNm_CommState */
typedef CanNm_ChannelConfigIterType CanNm_CommStateIterType;

/**   \brief  type used to iterate CanNm_CoordReadyToSleepState */
typedef CanNm_ChannelConfigIterType CanNm_CoordReadyToSleepStateIterType;

/**   \brief  type used to iterate CanNm_ImmediateNmMsgCount */
typedef CanNm_ChannelConfigIterType CanNm_ImmediateNmMsgCountIterType;

/**   \brief  type used to iterate CanNm_MsgConfirmationFlag */
typedef CanNm_ChannelConfigIterType CanNm_MsgConfirmationFlagIterType;

/**   \brief  type used to iterate CanNm_MsgIndicationFlag */
typedef CanNm_ChannelConfigIterType CanNm_MsgIndicationFlagIterType;

/**   \brief  type used to iterate CanNm_MsgRequest */
typedef CanNm_ChannelConfigIterType CanNm_MsgRequestIterType;

/**   \brief  type used to iterate CanNm_MsgTimeoutTimer */
typedef CanNm_ChannelConfigIterType CanNm_MsgTimeoutTimerIterType;

/**   \brief  type used to iterate CanNm_MsgTimer */
typedef CanNm_ChannelConfigIterType CanNm_MsgTimerIterType;

/**   \brief  type used to iterate CanNm_NetworkRestartFlag */
typedef CanNm_ChannelConfigIterType CanNm_NetworkRestartFlagIterType;

/**   \brief  type used to iterate CanNm_NmState */
typedef CanNm_ChannelConfigIterType CanNm_NmStateIterType;

/**   \brief  type used to iterate CanNm_RepeatMsgBitIndFlag */
typedef CanNm_ChannelConfigIterType CanNm_RepeatMsgBitIndFlagIterType;

/**   \brief  type used to iterate CanNm_RepeatMsgReqFlag */
typedef CanNm_ChannelConfigIterType CanNm_RepeatMsgReqFlagIterType;

/**   \brief  type used to iterate CanNm_RepeatMsgTimer */
typedef CanNm_ChannelConfigIterType CanNm_RepeatMsgTimerIterType;

/**   \brief  type used to iterate CanNm_TimeoutTimer */
typedef CanNm_ChannelConfigIterType CanNm_TimeoutTimerIterType;

/**   \brief  type used to iterate CanNm_TxControlState */
typedef CanNm_ChannelConfigIterType CanNm_TxControlStateIterType;

/**   \brief  type used to iterate CanNm_TxControlStateRequest */
typedef CanNm_ChannelConfigIterType CanNm_TxControlStateRequestIterType;

/**   \brief  type used to iterate CanNm_WaitBusSleepTimer */
typedef CanNm_ChannelConfigIterType CanNm_WaitBusSleepTimerIterType;

/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCValueTypes  CanNm Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for CanNm_ChannelIdOfChannelConfig */
typedef uint8 CanNm_ChannelIdOfChannelConfigType;

/**   \brief  value based type definition for CanNm_ComControlEnabledOfChannelConfig */
typedef boolean CanNm_ComControlEnabledOfChannelConfigType;

/**   \brief  value based type definition for CanNm_ImmediateNmCycleTimeOfChannelConfig */
typedef uint8 CanNm_ImmediateNmCycleTimeOfChannelConfigType;

/**   \brief  value based type definition for CanNm_ImmediateNmTransmissionsOfChannelConfig */
typedef uint8 CanNm_ImmediateNmTransmissionsOfChannelConfigType;

/**   \brief  value based type definition for CanNm_MsgCycleTimeOfChannelConfig */
typedef uint8 CanNm_MsgCycleTimeOfChannelConfigType;

/**   \brief  value based type definition for CanNm_MsgTimeoutTimeOfChannelConfig */
typedef uint8 CanNm_MsgTimeoutTimeOfChannelConfigType;

/**   \brief  value based type definition for CanNm_NodeDetectionEnabledOfChannelConfig */
typedef boolean CanNm_NodeDetectionEnabledOfChannelConfigType;

/**   \brief  value based type definition for CanNm_NodeIdEnabledOfChannelConfig */
typedef boolean CanNm_NodeIdEnabledOfChannelConfigType;

/**   \brief  value based type definition for CanNm_PduCbvPositionOfChannelConfig */
typedef uint8 CanNm_PduCbvPositionOfChannelConfigType;

/**   \brief  value based type definition for CanNm_PduNidPositionOfChannelConfig */
typedef uint8 CanNm_PduNidPositionOfChannelConfigType;

/**   \brief  value based type definition for CanNm_RemoteSleepIndTimeOfChannelConfig */
typedef uint8 CanNm_RemoteSleepIndTimeOfChannelConfigType;

/**   \brief  value based type definition for CanNm_RepeatMessageTimeOfChannelConfig */
typedef uint16 CanNm_RepeatMessageTimeOfChannelConfigType;

/**   \brief  value based type definition for CanNm_TimeoutTimeOfChannelConfig */
typedef uint8 CanNm_TimeoutTimeOfChannelConfigType;

/**   \brief  value based type definition for CanNm_WaitBusSleepTimeOfChannelConfig */
typedef uint8 CanNm_WaitBusSleepTimeOfChannelConfigType;

/**   \brief  value based type definition for CanNm_CommState */
typedef uint8 CanNm_CommStateType;

/**   \brief  value based type definition for CanNm_CoordReadyToSleepState */
typedef uint8 CanNm_CoordReadyToSleepStateType;

/**   \brief  value based type definition for CanNm_ImmediateNmMsgCount */
typedef uint8 CanNm_ImmediateNmMsgCountType;

/**   \brief  value based type definition for CanNm_MsgConfirmationFlag */
typedef boolean CanNm_MsgConfirmationFlagType;

/**   \brief  value based type definition for CanNm_MsgIndicationFlag */
typedef boolean CanNm_MsgIndicationFlagType;

/**   \brief  value based type definition for CanNm_MsgRequest */
typedef uint8 CanNm_MsgRequestType;

/**   \brief  value based type definition for CanNm_MsgTimeoutTimer */
typedef uint16 CanNm_MsgTimeoutTimerType;

/**   \brief  value based type definition for CanNm_MsgTimer */
typedef uint16 CanNm_MsgTimerType;

/**   \brief  value based type definition for CanNm_NetworkRestartFlag */
typedef uint8 CanNm_NetworkRestartFlagType;

/**   \brief  value based type definition for CanNm_NmState */
typedef uint8 CanNm_NmStateType;

/**   \brief  value based type definition for CanNm_MsgCycleOffsetOfPbChannelConfig */
typedef uint8 CanNm_MsgCycleOffsetOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_NodeIdOfPbChannelConfig */
typedef uint8 CanNm_NodeIdOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageDataEndIdxOfPbChannelConfig */
typedef uint8 CanNm_RxMessageDataEndIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageDataLengthOfPbChannelConfig */
typedef uint8 CanNm_RxMessageDataLengthOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageDataStartIdxOfPbChannelConfig */
typedef uint8 CanNm_RxMessageDataStartIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageDataUsedOfPbChannelConfig */
typedef boolean CanNm_RxMessageDataUsedOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageData_CBVIdxOfPbChannelConfig */
typedef uint8 CanNm_RxMessageData_CBVIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageData_CBVUsedOfPbChannelConfig */
typedef boolean CanNm_RxMessageData_CBVUsedOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageData_NIDIdxOfPbChannelConfig */
typedef uint8 CanNm_RxMessageData_NIDIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageData_NIDUsedOfPbChannelConfig */
typedef boolean CanNm_RxMessageData_NIDUsedOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageData_UserDataEndIdxOfPbChannelConfig */
typedef uint8 CanNm_RxMessageData_UserDataEndIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageData_UserDataLengthOfPbChannelConfig */
typedef uint8 CanNm_RxMessageData_UserDataLengthOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageData_UserDataStartIdxOfPbChannelConfig */
typedef uint8 CanNm_RxMessageData_UserDataStartIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RxMessageData_UserDataUsedOfPbChannelConfig */
typedef boolean CanNm_RxMessageData_UserDataUsedOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageDataEndIdxOfPbChannelConfig */
typedef uint8 CanNm_TxMessageDataEndIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageDataLengthOfPbChannelConfig */
typedef uint8 CanNm_TxMessageDataLengthOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageDataStartIdxOfPbChannelConfig */
typedef uint8 CanNm_TxMessageDataStartIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageDataUsedOfPbChannelConfig */
typedef boolean CanNm_TxMessageDataUsedOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageData_CBVIdxOfPbChannelConfig */
typedef uint8 CanNm_TxMessageData_CBVIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageData_CBVUsedOfPbChannelConfig */
typedef boolean CanNm_TxMessageData_CBVUsedOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageData_NIDIdxOfPbChannelConfig */
typedef uint8 CanNm_TxMessageData_NIDIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageData_NIDUsedOfPbChannelConfig */
typedef boolean CanNm_TxMessageData_NIDUsedOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageData_UserDataEndIdxOfPbChannelConfig */
typedef uint8 CanNm_TxMessageData_UserDataEndIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageData_UserDataLengthOfPbChannelConfig */
typedef uint8 CanNm_TxMessageData_UserDataLengthOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageData_UserDataStartIdxOfPbChannelConfig */
typedef uint8 CanNm_TxMessageData_UserDataStartIdxOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxMessageData_UserDataUsedOfPbChannelConfig */
typedef boolean CanNm_TxMessageData_UserDataUsedOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxPduIdOfPbChannelConfig */
typedef uint8 CanNm_TxPduIdOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_TxUserDataPduIdOfPbChannelConfig */
typedef uint8 CanNm_TxUserDataPduIdOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_RepeatMsgBitIndFlag */
typedef boolean CanNm_RepeatMsgBitIndFlagType;

/**   \brief  value based type definition for CanNm_RepeatMsgReqFlag */
typedef boolean CanNm_RepeatMsgReqFlagType;

/**   \brief  value based type definition for CanNm_RepeatMsgTimer */
typedef uint16 CanNm_RepeatMsgTimerType;

/**   \brief  value based type definition for CanNm_RxMessageData */
typedef uint8 CanNm_RxMessageDataType;

/**   \brief  value based type definition for CanNm_SizeOfChannelConfig */
typedef uint8 CanNm_SizeOfChannelConfigType;

/**   \brief  value based type definition for CanNm_SizeOfCommState */
typedef uint8 CanNm_SizeOfCommStateType;

/**   \brief  value based type definition for CanNm_SizeOfCoordReadyToSleepState */
typedef uint8 CanNm_SizeOfCoordReadyToSleepStateType;

/**   \brief  value based type definition for CanNm_SizeOfImmediateNmMsgCount */
typedef uint8 CanNm_SizeOfImmediateNmMsgCountType;

/**   \brief  value based type definition for CanNm_SizeOfMsgConfirmationFlag */
typedef uint8 CanNm_SizeOfMsgConfirmationFlagType;

/**   \brief  value based type definition for CanNm_SizeOfMsgIndicationFlag */
typedef uint8 CanNm_SizeOfMsgIndicationFlagType;

/**   \brief  value based type definition for CanNm_SizeOfMsgRequest */
typedef uint8 CanNm_SizeOfMsgRequestType;

/**   \brief  value based type definition for CanNm_SizeOfMsgTimeoutTimer */
typedef uint8 CanNm_SizeOfMsgTimeoutTimerType;

/**   \brief  value based type definition for CanNm_SizeOfMsgTimer */
typedef uint8 CanNm_SizeOfMsgTimerType;

/**   \brief  value based type definition for CanNm_SizeOfNetworkRestartFlag */
typedef uint8 CanNm_SizeOfNetworkRestartFlagType;

/**   \brief  value based type definition for CanNm_SizeOfNmState */
typedef uint8 CanNm_SizeOfNmStateType;

/**   \brief  value based type definition for CanNm_SizeOfPbChannelConfig */
typedef uint8 CanNm_SizeOfPbChannelConfigType;

/**   \brief  value based type definition for CanNm_SizeOfRepeatMsgBitIndFlag */
typedef uint8 CanNm_SizeOfRepeatMsgBitIndFlagType;

/**   \brief  value based type definition for CanNm_SizeOfRepeatMsgReqFlag */
typedef uint8 CanNm_SizeOfRepeatMsgReqFlagType;

/**   \brief  value based type definition for CanNm_SizeOfRepeatMsgTimer */
typedef uint8 CanNm_SizeOfRepeatMsgTimerType;

/**   \brief  value based type definition for CanNm_SizeOfSysToNmChInd */
typedef uint8 CanNm_SizeOfSysToNmChIndType;

/**   \brief  value based type definition for CanNm_SizeOfTimeoutTimer */
typedef uint8 CanNm_SizeOfTimeoutTimerType;

/**   \brief  value based type definition for CanNm_SizeOfTxControlState */
typedef uint8 CanNm_SizeOfTxControlStateType;

/**   \brief  value based type definition for CanNm_SizeOfTxControlStateRequest */
typedef uint8 CanNm_SizeOfTxControlStateRequestType;

/**   \brief  value based type definition for CanNm_SizeOfTxMessageData */
typedef uint8 CanNm_SizeOfTxMessageDataType;

/**   \brief  value based type definition for CanNm_SizeOfWaitBusSleepTimer */
typedef uint8 CanNm_SizeOfWaitBusSleepTimerType;

/**   \brief  value based type definition for CanNm_SysToNmChInd */
typedef uint8 CanNm_SysToNmChIndType;

/**   \brief  value based type definition for CanNm_TimeoutTimer */
typedef uint16 CanNm_TimeoutTimerType;

/**   \brief  value based type definition for CanNm_TxControlState */
typedef uint8 CanNm_TxControlStateType;

/**   \brief  value based type definition for CanNm_TxControlStateRequest */
typedef uint8 CanNm_TxControlStateRequestType;

/**   \brief  value based type definition for CanNm_TxMessageData */
typedef uint8 CanNm_TxMessageDataType;

/**   \brief  value based type definition for CanNm_WaitBusSleepTimer */
typedef uint16 CanNm_WaitBusSleepTimerType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  CanNmPCStructTypes  CanNm Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in CanNm_ChannelConfig */
typedef struct sCanNm_ChannelConfigType
{
  CanNm_RepeatMessageTimeOfChannelConfigType RepeatMessageTimeOfChannelConfig;  /**< Timeout for Repeat Message State [ms]. */
  CanNm_ComControlEnabledOfChannelConfigType ComControlEnabledOfChannelConfig;  /**< Determines if Com Control is active or not */
  CanNm_NodeDetectionEnabledOfChannelConfigType NodeDetectionEnabledOfChannelConfig;  /**< Determines if Node Detection feature is active or not */
  CanNm_NodeIdEnabledOfChannelConfigType NodeIdEnabledOfChannelConfig;  /**< Determines if Node Ids are enabled or not */
  CanNm_ChannelIdOfChannelConfigType ChannelIdOfChannelConfig;  /**< Channel ID configured for the respective instance of the NM. */
  CanNm_ImmediateNmCycleTimeOfChannelConfigType ImmediateNmCycleTimeOfChannelConfig;  /**< Fast NM PDU Transmission Time during WUP */
  CanNm_ImmediateNmTransmissionsOfChannelConfigType ImmediateNmTransmissionsOfChannelConfig;  /**< Number of fast NM PDU Transmissions during WUP */
  CanNm_MsgCycleTimeOfChannelConfigType MsgCycleTimeOfChannelConfig;  /**< Period of a NM message [ms]. It determines the periodic rate in the periodic transmission mode. */
  CanNm_MsgTimeoutTimeOfChannelConfigType MsgTimeoutTimeOfChannelConfig;  /**< Transmission Timeout [ms] of NM message. If there is no transmission confirmation by the CAN Interface within this timeout, the CAN NM module shall give an error notification. */
  CanNm_PduCbvPositionOfChannelConfigType PduCbvPositionOfChannelConfig;  /**< Control Bit Vector Position in the PDU */
  CanNm_PduNidPositionOfChannelConfigType PduNidPositionOfChannelConfig;  /**< Node ID Position in the PDU */
  CanNm_RemoteSleepIndTimeOfChannelConfigType RemoteSleepIndTimeOfChannelConfig;  /**< Timeout for Remote Sleep Indication [ms]. */
  CanNm_TimeoutTimeOfChannelConfigType TimeoutTimeOfChannelConfig;  /**< Timeout for the NM messages [ms]. */
  CanNm_WaitBusSleepTimeOfChannelConfigType WaitBusSleepTimeOfChannelConfig;  /**< Timeout for bus calm down phase [ms]. */
} CanNm_ChannelConfigType;

/**   \brief  type used in CanNm_PbChannelConfig */
typedef struct sCanNm_PbChannelConfigType
{
  CanNm_MsgCycleOffsetOfPbChannelConfigType MsgCycleOffsetOfPbChannelConfig;
  CanNm_NodeIdOfPbChannelConfigType NodeIdOfPbChannelConfig;
  CanNm_RxMessageDataEndIdxOfPbChannelConfigType RxMessageDataEndIdxOfPbChannelConfig;  /**< the end index of the 0:n relation pointing to CanNm_RxMessageData */
  CanNm_RxMessageDataLengthOfPbChannelConfigType RxMessageDataLengthOfPbChannelConfig;  /**< the number of relations pointing to CanNm_RxMessageData */
  CanNm_RxMessageDataStartIdxOfPbChannelConfigType RxMessageDataStartIdxOfPbChannelConfig;  /**< the start index of the 0:n relation pointing to CanNm_RxMessageData */
  CanNm_RxMessageData_CBVIdxOfPbChannelConfigType RxMessageData_CBVIdxOfPbChannelConfig;  /**< the index of the 0:1 relation pointing to CanNm_RxMessageData */
  CanNm_RxMessageData_NIDIdxOfPbChannelConfigType RxMessageData_NIDIdxOfPbChannelConfig;  /**< the index of the 0:1 relation pointing to CanNm_RxMessageData */
  CanNm_RxMessageData_UserDataEndIdxOfPbChannelConfigType RxMessageData_UserDataEndIdxOfPbChannelConfig;  /**< the end index of the 0:n relation pointing to CanNm_RxMessageData */
  CanNm_RxMessageData_UserDataLengthOfPbChannelConfigType RxMessageData_UserDataLengthOfPbChannelConfig;  /**< the number of relations pointing to CanNm_RxMessageData */
  CanNm_RxMessageData_UserDataStartIdxOfPbChannelConfigType RxMessageData_UserDataStartIdxOfPbChannelConfig;  /**< the start index of the 0:n relation pointing to CanNm_RxMessageData */
  CanNm_TxMessageDataEndIdxOfPbChannelConfigType TxMessageDataEndIdxOfPbChannelConfig;  /**< the end index of the 0:n relation pointing to CanNm_TxMessageData */
  CanNm_TxMessageDataLengthOfPbChannelConfigType TxMessageDataLengthOfPbChannelConfig;  /**< the number of relations pointing to CanNm_TxMessageData */
  CanNm_TxMessageDataStartIdxOfPbChannelConfigType TxMessageDataStartIdxOfPbChannelConfig;  /**< the start index of the 0:n relation pointing to CanNm_TxMessageData */
  CanNm_TxMessageData_CBVIdxOfPbChannelConfigType TxMessageData_CBVIdxOfPbChannelConfig;  /**< the index of the 0:1 relation pointing to CanNm_TxMessageData */
  CanNm_TxMessageData_NIDIdxOfPbChannelConfigType TxMessageData_NIDIdxOfPbChannelConfig;  /**< the index of the 0:1 relation pointing to CanNm_TxMessageData */
  CanNm_TxMessageData_UserDataEndIdxOfPbChannelConfigType TxMessageData_UserDataEndIdxOfPbChannelConfig;  /**< the end index of the 0:n relation pointing to CanNm_TxMessageData */
  CanNm_TxMessageData_UserDataLengthOfPbChannelConfigType TxMessageData_UserDataLengthOfPbChannelConfig;  /**< the number of relations pointing to CanNm_TxMessageData */
  CanNm_TxMessageData_UserDataStartIdxOfPbChannelConfigType TxMessageData_UserDataStartIdxOfPbChannelConfig;  /**< the start index of the 0:n relation pointing to CanNm_TxMessageData */
  CanNm_TxPduIdOfPbChannelConfigType TxPduIdOfPbChannelConfig;
  CanNm_TxUserDataPduIdOfPbChannelConfigType TxUserDataPduIdOfPbChannelConfig;
} CanNm_PbChannelConfigType;

/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCSymbolicStructTypes  CanNm Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to CanNm_CommState */
typedef struct CanNm_CommStateStructSTag
{
  CanNm_CommStateType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_CommStateStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_CoordReadyToSleepState */
typedef struct CanNm_CoordReadyToSleepStateStructSTag
{
  CanNm_CoordReadyToSleepStateType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_CoordReadyToSleepStateStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_ImmediateNmMsgCount */
typedef struct CanNm_ImmediateNmMsgCountStructSTag
{
  CanNm_ImmediateNmMsgCountType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_ImmediateNmMsgCountStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_MsgConfirmationFlag */
typedef struct CanNm_MsgConfirmationFlagStructSTag
{
  CanNm_MsgConfirmationFlagType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_MsgConfirmationFlagStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_MsgIndicationFlag */
typedef struct CanNm_MsgIndicationFlagStructSTag
{
  CanNm_MsgIndicationFlagType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_MsgIndicationFlagStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_MsgRequest */
typedef struct CanNm_MsgRequestStructSTag
{
  CanNm_MsgRequestType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_MsgRequestStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_MsgTimeoutTimer */
typedef struct CanNm_MsgTimeoutTimerStructSTag
{
  CanNm_MsgTimeoutTimerType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_MsgTimeoutTimerStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_MsgTimer */
typedef struct CanNm_MsgTimerStructSTag
{
  CanNm_MsgTimerType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_MsgTimerStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_NetworkRestartFlag */
typedef struct CanNm_NetworkRestartFlagStructSTag
{
  CanNm_NetworkRestartFlagType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_NetworkRestartFlagStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_NmState */
typedef struct CanNm_NmStateStructSTag
{
  CanNm_NmStateType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_NmStateStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_RepeatMsgBitIndFlag */
typedef struct CanNm_RepeatMsgBitIndFlagStructSTag
{
  CanNm_RepeatMsgBitIndFlagType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_RepeatMsgBitIndFlagStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_RepeatMsgReqFlag */
typedef struct CanNm_RepeatMsgReqFlagStructSTag
{
  CanNm_RepeatMsgReqFlagType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_RepeatMsgReqFlagStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_RepeatMsgTimer */
typedef struct CanNm_RepeatMsgTimerStructSTag
{
  CanNm_RepeatMsgTimerType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_RepeatMsgTimerStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_TimeoutTimer */
typedef struct CanNm_TimeoutTimerStructSTag
{
  CanNm_TimeoutTimerType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_TimeoutTimerStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_TxControlState */
typedef struct CanNm_TxControlStateStructSTag
{
  CanNm_TxControlStateType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_TxControlStateStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_TxControlStateRequest */
typedef struct CanNm_TxControlStateRequestStructSTag
{
  CanNm_TxControlStateRequestType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_TxControlStateRequestStructSType;

/**   \brief  type to be used as symbolic data element access to CanNm_WaitBusSleepTimer */
typedef struct CanNm_WaitBusSleepTimerStructSTag
{
  CanNm_WaitBusSleepTimerType CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
} CanNm_WaitBusSleepTimerStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCUnionIndexAndSymbolTypes  CanNm Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access CanNm_CommState in an index and symbol based style. */
typedef union CanNm_CommStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_CommStateType raw[1];
  CanNm_CommStateStructSType str;
} CanNm_CommStateUType;

/**   \brief  type to access CanNm_CoordReadyToSleepState in an index and symbol based style. */
typedef union CanNm_CoordReadyToSleepStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_CoordReadyToSleepStateType raw[1];
  CanNm_CoordReadyToSleepStateStructSType str;
} CanNm_CoordReadyToSleepStateUType;

/**   \brief  type to access CanNm_ImmediateNmMsgCount in an index and symbol based style. */
typedef union CanNm_ImmediateNmMsgCountUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_ImmediateNmMsgCountType raw[1];
  CanNm_ImmediateNmMsgCountStructSType str;
} CanNm_ImmediateNmMsgCountUType;

/**   \brief  type to access CanNm_MsgConfirmationFlag in an index and symbol based style. */
typedef union CanNm_MsgConfirmationFlagUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_MsgConfirmationFlagType raw[1];
  CanNm_MsgConfirmationFlagStructSType str;
} CanNm_MsgConfirmationFlagUType;

/**   \brief  type to access CanNm_MsgIndicationFlag in an index and symbol based style. */
typedef union CanNm_MsgIndicationFlagUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_MsgIndicationFlagType raw[1];
  CanNm_MsgIndicationFlagStructSType str;
} CanNm_MsgIndicationFlagUType;

/**   \brief  type to access CanNm_MsgRequest in an index and symbol based style. */
typedef union CanNm_MsgRequestUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_MsgRequestType raw[1];
  CanNm_MsgRequestStructSType str;
} CanNm_MsgRequestUType;

/**   \brief  type to access CanNm_MsgTimeoutTimer in an index and symbol based style. */
typedef union CanNm_MsgTimeoutTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_MsgTimeoutTimerType raw[1];
  CanNm_MsgTimeoutTimerStructSType str;
} CanNm_MsgTimeoutTimerUType;

/**   \brief  type to access CanNm_MsgTimer in an index and symbol based style. */
typedef union CanNm_MsgTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_MsgTimerType raw[1];
  CanNm_MsgTimerStructSType str;
} CanNm_MsgTimerUType;

/**   \brief  type to access CanNm_NetworkRestartFlag in an index and symbol based style. */
typedef union CanNm_NetworkRestartFlagUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_NetworkRestartFlagType raw[1];
  CanNm_NetworkRestartFlagStructSType str;
} CanNm_NetworkRestartFlagUType;

/**   \brief  type to access CanNm_NmState in an index and symbol based style. */
typedef union CanNm_NmStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_NmStateType raw[1];
  CanNm_NmStateStructSType str;
} CanNm_NmStateUType;

/**   \brief  type to access CanNm_RepeatMsgBitIndFlag in an index and symbol based style. */
typedef union CanNm_RepeatMsgBitIndFlagUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_RepeatMsgBitIndFlagType raw[1];
  CanNm_RepeatMsgBitIndFlagStructSType str;
} CanNm_RepeatMsgBitIndFlagUType;

/**   \brief  type to access CanNm_RepeatMsgReqFlag in an index and symbol based style. */
typedef union CanNm_RepeatMsgReqFlagUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_RepeatMsgReqFlagType raw[1];
  CanNm_RepeatMsgReqFlagStructSType str;
} CanNm_RepeatMsgReqFlagUType;

/**   \brief  type to access CanNm_RepeatMsgTimer in an index and symbol based style. */
typedef union CanNm_RepeatMsgTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_RepeatMsgTimerType raw[1];
  CanNm_RepeatMsgTimerStructSType str;
} CanNm_RepeatMsgTimerUType;

/**   \brief  type to access CanNm_TimeoutTimer in an index and symbol based style. */
typedef union CanNm_TimeoutTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_TimeoutTimerType raw[1];
  CanNm_TimeoutTimerStructSType str;
} CanNm_TimeoutTimerUType;

/**   \brief  type to access CanNm_TxControlState in an index and symbol based style. */
typedef union CanNm_TxControlStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_TxControlStateType raw[1];
  CanNm_TxControlStateStructSType str;
} CanNm_TxControlStateUType;

/**   \brief  type to access CanNm_TxControlStateRequest in an index and symbol based style. */
typedef union CanNm_TxControlStateRequestUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_TxControlStateRequestType raw[1];
  CanNm_TxControlStateRequestStructSType str;
} CanNm_TxControlStateRequestUType;

/**   \brief  type to access CanNm_WaitBusSleepTimer in an index and symbol based style. */
typedef union CanNm_WaitBusSleepTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  CanNm_WaitBusSleepTimerType raw[1];
  CanNm_WaitBusSleepTimerStructSType str;
} CanNm_WaitBusSleepTimerUType;

/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCRootPointerTypes  CanNm Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to CanNm_ChannelConfig */
typedef P2CONST(CanNm_ChannelConfigType, TYPEDEF, CANNM_CONST) CanNm_ChannelConfigPtrType;

/**   \brief  type used to point to CanNm_CommState */
typedef P2VAR(CanNm_CommStateType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_CommStatePtrType;

/**   \brief  type used to point to CanNm_CoordReadyToSleepState */
typedef P2VAR(CanNm_CoordReadyToSleepStateType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_CoordReadyToSleepStatePtrType;

/**   \brief  type used to point to CanNm_ImmediateNmMsgCount */
typedef P2VAR(CanNm_ImmediateNmMsgCountType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_ImmediateNmMsgCountPtrType;

/**   \brief  type used to point to CanNm_MsgConfirmationFlag */
typedef P2VAR(CanNm_MsgConfirmationFlagType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_MsgConfirmationFlagPtrType;

/**   \brief  type used to point to CanNm_MsgIndicationFlag */
typedef P2VAR(CanNm_MsgIndicationFlagType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_MsgIndicationFlagPtrType;

/**   \brief  type used to point to CanNm_MsgRequest */
typedef P2VAR(CanNm_MsgRequestType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_MsgRequestPtrType;

/**   \brief  type used to point to CanNm_MsgTimeoutTimer */
typedef P2VAR(CanNm_MsgTimeoutTimerType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_MsgTimeoutTimerPtrType;

/**   \brief  type used to point to CanNm_MsgTimer */
typedef P2VAR(CanNm_MsgTimerType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_MsgTimerPtrType;

/**   \brief  type used to point to CanNm_NetworkRestartFlag */
typedef P2VAR(CanNm_NetworkRestartFlagType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_NetworkRestartFlagPtrType;

/**   \brief  type used to point to CanNm_NmState */
typedef P2VAR(CanNm_NmStateType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_NmStatePtrType;

/**   \brief  type used to point to CanNm_PbChannelConfig */
typedef P2CONST(CanNm_PbChannelConfigType, TYPEDEF, CANNM_CONST) CanNm_PbChannelConfigPtrType;

/**   \brief  type used to point to CanNm_RepeatMsgBitIndFlag */
typedef P2VAR(CanNm_RepeatMsgBitIndFlagType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_RepeatMsgBitIndFlagPtrType;

/**   \brief  type used to point to CanNm_RepeatMsgReqFlag */
typedef P2VAR(CanNm_RepeatMsgReqFlagType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_RepeatMsgReqFlagPtrType;

/**   \brief  type used to point to CanNm_RepeatMsgTimer */
typedef P2VAR(CanNm_RepeatMsgTimerType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_RepeatMsgTimerPtrType;

/**   \brief  type used to point to CanNm_RxMessageData */
typedef P2VAR(CanNm_RxMessageDataType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_RxMessageDataPtrType;

/**   \brief  type used to point to CanNm_SysToNmChInd */
typedef P2CONST(CanNm_SysToNmChIndType, TYPEDEF, CANNM_CONST) CanNm_SysToNmChIndPtrType;

/**   \brief  type used to point to CanNm_TimeoutTimer */
typedef P2VAR(CanNm_TimeoutTimerType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_TimeoutTimerPtrType;

/**   \brief  type used to point to CanNm_TxControlState */
typedef P2VAR(CanNm_TxControlStateType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_TxControlStatePtrType;

/**   \brief  type used to point to CanNm_TxControlStateRequest */
typedef P2VAR(CanNm_TxControlStateRequestType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_TxControlStateRequestPtrType;

/**   \brief  type used to point to CanNm_TxMessageData */
typedef P2VAR(CanNm_TxMessageDataType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_TxMessageDataPtrType;

/**   \brief  type used to point to CanNm_WaitBusSleepTimer */
typedef P2VAR(CanNm_WaitBusSleepTimerType, TYPEDEF, CANNM_VAR_NOINIT) CanNm_WaitBusSleepTimerPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  CanNmPCRootValueTypes  CanNm Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in CanNm_PCConfig */
typedef struct sCanNm_PCConfigType
{
  uint8 CanNm_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} CanNm_PCConfigType;

typedef CanNm_PCConfigType CanNm_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
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
  CanNm_ChannelConfig
**********************************************************************************************************************/
/** 
  \var    CanNm_ChannelConfig
  \details
  Element                     Description
  RepeatMessageTime           Timeout for Repeat Message State [ms].
  ComControlEnabled           Determines if Com Control is active or not
  NodeDetectionEnabled        Determines if Node Detection feature is active or not
  NodeIdEnabled               Determines if Node Ids are enabled or not
  ChannelId                   Channel ID configured for the respective instance of the NM.
  ImmediateNmCycleTime        Fast NM PDU Transmission Time during WUP
  ImmediateNmTransmissions    Number of fast NM PDU Transmissions during WUP
  MsgCycleTime                Period of a NM message [ms]. It determines the periodic rate in the periodic transmission mode.
  MsgTimeoutTime              Transmission Timeout [ms] of NM message. If there is no transmission confirmation by the CAN Interface within this timeout, the CAN NM module shall give an error notification.
  PduCbvPosition              Control Bit Vector Position in the PDU
  PduNidPosition              Node ID Position in the PDU
  RemoteSleepIndTime          Timeout for Remote Sleep Indication [ms].
  TimeoutTime                 Timeout for the NM messages [ms].
  WaitBusSleepTime            Timeout for bus calm down phase [ms].
*/ 
#define CANNM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(CanNm_ChannelConfigType, CANNM_CONST) CanNm_ChannelConfig[1];
#define CANNM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_PbChannelConfig
**********************************************************************************************************************/
/** 
  \var    CanNm_PbChannelConfig
  \details
  Element                           Description
  MsgCycleOffset                
  NodeId                        
  RxMessageDataEndIdx               the end index of the 0:n relation pointing to CanNm_RxMessageData
  RxMessageDataLength               the number of relations pointing to CanNm_RxMessageData
  RxMessageDataStartIdx             the start index of the 0:n relation pointing to CanNm_RxMessageData
  RxMessageData_CBVIdx              the index of the 0:1 relation pointing to CanNm_RxMessageData
  RxMessageData_NIDIdx              the index of the 0:1 relation pointing to CanNm_RxMessageData
  RxMessageData_UserDataEndIdx      the end index of the 0:n relation pointing to CanNm_RxMessageData
  RxMessageData_UserDataLength      the number of relations pointing to CanNm_RxMessageData
  RxMessageData_UserDataStartIdx    the start index of the 0:n relation pointing to CanNm_RxMessageData
  TxMessageDataEndIdx               the end index of the 0:n relation pointing to CanNm_TxMessageData
  TxMessageDataLength               the number of relations pointing to CanNm_TxMessageData
  TxMessageDataStartIdx             the start index of the 0:n relation pointing to CanNm_TxMessageData
  TxMessageData_CBVIdx              the index of the 0:1 relation pointing to CanNm_TxMessageData
  TxMessageData_NIDIdx              the index of the 0:1 relation pointing to CanNm_TxMessageData
  TxMessageData_UserDataEndIdx      the end index of the 0:n relation pointing to CanNm_TxMessageData
  TxMessageData_UserDataLength      the number of relations pointing to CanNm_TxMessageData
  TxMessageData_UserDataStartIdx    the start index of the 0:n relation pointing to CanNm_TxMessageData
  TxPduId                       
  TxUserDataPduId               
*/ 
#define CANNM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(CanNm_PbChannelConfigType, CANNM_CONST) CanNm_PbChannelConfig[1];
#define CANNM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_SysToNmChInd
**********************************************************************************************************************/
/** 
  \var    CanNm_SysToNmChInd
  \brief  Channel indirection: System Channel handle to NM channel handle
*/ 
#define CANNM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(CanNm_SysToNmChIndType, CANNM_CONST) CanNm_SysToNmChInd[1];
#define CANNM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_CommState
**********************************************************************************************************************/
/** 
  \var    CanNm_CommState
  \brief  Internal state for the application's need for communication.
*/ 
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_CommStateUType, CANNM_VAR_NOINIT) CanNm_CommState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_CoordReadyToSleepState
**********************************************************************************************************************/
/** 
  \var    CanNm_CoordReadyToSleepState
  \brief  State for Rx of Coordinator Sleep Ready Bit:
*/ 
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_CoordReadyToSleepStateUType, CANNM_VAR_NOINIT) CanNm_CoordReadyToSleepState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_ImmediateNmMsgCount
**********************************************************************************************************************/
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_ImmediateNmMsgCountUType, CANNM_VAR_NOINIT) CanNm_ImmediateNmMsgCount;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_MsgConfirmationFlag
**********************************************************************************************************************/
/** 
  \var    CanNm_MsgConfirmationFlag
  \brief  Message Confirmation Flag
*/ 
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_MsgConfirmationFlagUType, CANNM_VAR_NOINIT) CanNm_MsgConfirmationFlag;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_MsgIndicationFlag
**********************************************************************************************************************/
/** 
  \var    CanNm_MsgIndicationFlag
  \brief  Message Indication Flag
*/ 
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_MsgIndicationFlagUType, CANNM_VAR_NOINIT) CanNm_MsgIndicationFlag;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_MsgRequest
**********************************************************************************************************************/
/** 
  \var    CanNm_MsgRequest
  \brief  Internal Message Request Variable
*/ 
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_MsgRequestUType, CANNM_VAR_NOINIT) CanNm_MsgRequest;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_MsgTimeoutTimer
**********************************************************************************************************************/
#define CANNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_MsgTimeoutTimerUType, CANNM_VAR_NOINIT) CanNm_MsgTimeoutTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_MsgTimer
**********************************************************************************************************************/
/** 
  \var    CanNm_MsgTimer
  \brief  Timer for NM message transmission.
*/ 
#define CANNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_MsgTimerUType, CANNM_VAR_NOINIT) CanNm_MsgTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_NetworkRestartFlag
**********************************************************************************************************************/
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_NetworkRestartFlagUType, CANNM_VAR_NOINIT) CanNm_NetworkRestartFlag;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_NmState
**********************************************************************************************************************/
/** 
  \var    CanNm_NmState
  \brief  Current state of the state machine
*/ 
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_NmStateUType, CANNM_VAR_NOINIT) CanNm_NmState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_RepeatMsgBitIndFlag
**********************************************************************************************************************/
/** 
  \var    CanNm_RepeatMsgBitIndFlag
  \brief  Repeat Message Bit Indication Flag
*/ 
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_RepeatMsgBitIndFlagUType, CANNM_VAR_NOINIT) CanNm_RepeatMsgBitIndFlag;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_RepeatMsgReqFlag
**********************************************************************************************************************/
/** 
  \var    CanNm_RepeatMsgReqFlag
  \brief  Repeat Message Request Flag
*/ 
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_RepeatMsgReqFlagUType, CANNM_VAR_NOINIT) CanNm_RepeatMsgReqFlag;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_RepeatMsgTimer
**********************************************************************************************************************/
#define CANNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_RepeatMsgTimerUType, CANNM_VAR_NOINIT) CanNm_RepeatMsgTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_RxMessageData
**********************************************************************************************************************/
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_RxMessageDataType, CANNM_VAR_NOINIT) CanNm_RxMessageData[8];
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_TimeoutTimer
**********************************************************************************************************************/
/** 
  \var    CanNm_TimeoutTimer
  \brief  Timer for NM Algorithm.
*/ 
#define CANNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_TimeoutTimerUType, CANNM_VAR_NOINIT) CanNm_TimeoutTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_TxControlState
**********************************************************************************************************************/
/** 
  \var    CanNm_TxControlState
  \brief  Message transmission control state.
*/ 
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_TxControlStateUType, CANNM_VAR_NOINIT) CanNm_TxControlState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_TxControlStateRequest
**********************************************************************************************************************/
/** 
  \var    CanNm_TxControlStateRequest
  \brief  Message transmission control state request.
*/ 
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_TxControlStateRequestUType, CANNM_VAR_NOINIT) CanNm_TxControlStateRequest;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_TxMessageData
**********************************************************************************************************************/
#define CANNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_TxMessageDataType, CANNM_VAR_NOINIT) CanNm_TxMessageData[8];
#define CANNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanNm_WaitBusSleepTimer
**********************************************************************************************************************/
#define CANNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanNm_WaitBusSleepTimerUType, CANNM_VAR_NOINIT) CanNm_WaitBusSleepTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define CANNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/




/**********************************************************************************************************************
  END OF FILE: CanNm_Cfg.h
**********************************************************************************************************************/
#endif /* CANNM_CFG_H */

