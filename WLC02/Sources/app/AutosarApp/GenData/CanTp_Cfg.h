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
 *            Module: CanTp
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CanTp_Cfg.h
 *   Generation Time: 2020-03-24 15:59:25
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

#if !defined(CANTP_CFG_H)
#define CANTP_CFG_H

/* -----------------------------------------------------------------------------
    &&&~ Include files
 ----------------------------------------------------------------------------- */

#include "ComStack_Types.h"

/* Definition of feature switches in the library delivered */
#ifndef CANTP_USE_DUMMY_STATEMENT
#define CANTP_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/EcuC/EcucGeneral/DummyStatement */
#endif
#ifndef CANTP_DUMMY_STATEMENT
#define CANTP_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CANTP_DUMMY_STATEMENT_CONST
#define CANTP_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CANTP_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define CANTP_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef CANTP_ATOMIC_VARIABLE_ACCESS
#define CANTP_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef CANTP_PROCESSOR_RH850_1649
#define CANTP_PROCESSOR_RH850_1649
#endif
#ifndef CANTP_COMP_GREENHILLS
#define CANTP_COMP_GREENHILLS
#endif
#ifndef CANTP_GEN_GENERATOR_MSR
#define CANTP_GEN_GENERATOR_MSR
#endif
#ifndef CANTP_CPUTYPE_BITORDER_LSB2MSB
#define CANTP_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef CANTP_CONFIGURATION_VARIANT_PRECOMPILE
#define CANTP_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef CANTP_CONFIGURATION_VARIANT_LINKTIME
#define CANTP_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef CANTP_CONFIGURATION_VARIANT
#define CANTP_CONFIGURATION_VARIANT CANTP_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef CANTP_POSTBUILD_VARIANT_SUPPORT
#define CANTP_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/* PRQA S 3453 MACROS_3453 */  /* MD_CSL_3453 */
 /*  Version information  */ 
#define CANTP_CFG_GEN_MAJOR_VERSION                                            4u 
#define CANTP_CFG_GEN_MINOR_VERSION                                            4u 
#define CANTP_CFG_GEN_PATCH_VERSION                                            0u 

 /*  Global defines  */ 
#define CANTP_VERSION_INFO_API                                                 STD_ON 
#define CANTP_DEV_ERROR_DETECT                                                 STD_OFF 
#define CANTP_DEV_ERROR_REPORT                                                 STD_OFF 
#define CANTP_TC                                                               STD_OFF 
#define CANTP_RC                                                               STD_OFF 
#define CANTP_INVALID_HDL                                                      ((PduIdType) 255u) 
#define CANTP_TASK_CYCLE                                                       5u 

 /*  Global constant defines  */ 
#define CANTP_MAX_FRAME_LENGTH                                                 8u 
#define CANTP_MAX_PAYLOAD_LENGTH                                               7u 
#define CANTP_MAX_PDU_METADATA_LENGTH                                          0u 
#define CANTP_MAX_SDU_METADATA_LENGTH                                          0u 
#define CANTP_NUM_RX_CHANNELS                                                  CanTp_GetSizeOfRxState() 
#define CANTP_NUM_RX_SDUS                                                      5 
#define CANTP_NUM_TX_CHANNELS                                                  CanTp_GetSizeOfTxState() 
#define CANTP_NUM_TX_SDUS                                                      4 
#define CANTP_SIZEOF_PDULENGTHTYPE                                             2 

 /*  Communication Type  */ 
#define CANTP_MODE_FULL_DUPLEX                                                 1u 
#define CANTP_MODE_HALF_DUPLEX                                                 0u 
#define CANTP_TATYPE_FUNCTIONAL                                                1u 
#define CANTP_TATYPE_PHYSICAL                                                  0u 

 /*  CanTp Adress Format  */ 
#define CANTP_ADDRESS_FORMAT_EXTENDED                                          1u 
#define CANTP_ADDRESS_FORMAT_MIXED11                                           2u 
#define CANTP_ADDRESS_FORMAT_MIXED29                                           4u 
#define CANTP_ADDRESS_FORMAT_NORMALFIXED                                       3u 
#define CANTP_ADDRESS_FORMAT_STANDARD                                          0u 

 /*  Can Type  */ 
#define CANTP_CANTYPE_CAN20                                                    0u 
#define CANTP_CANTYPE_CANFD                                                    1u 

 /*  Vector-CanTp extended capabilities  */ 
#define CANTP_GENERATOR_COMPATIBILITY_VERSION                                  0x0005D047uL                                                   /* Extended error detection capabilities */ 
#define CANTP_CAN20_PADDING_ACTIVE                                             STD_ON 
#define CANTP_HAVE_PADDING_BYTE                                                STD_ON 
#define CANTP_PADDING_PATTERN                                                  0xAAu                                                          /* Padding byte to be used for the Tx side if CANTP_HAVE_PADDING_BYTE is ON */ 
#define CANTP_DYN_CHANNEL_ASSIGNMENT                                           STD_OFF 
#define CANTP_STANDARD_ADDRESSING                                              STD_ON 
#define CANTP_EXTENDED_ADDRESSING                                              STD_ON 
#define CANTP_MIXED11_ADDRESSING                                               STD_ON 
#define CANTP_MIXED29_ADDRESSING                                               STD_ON 
#define CANTP_NORMALFIXED_ADDRESSING                                           STD_ON 
#define CANTP_SINGLE_RX_BUFFER_OPTIMIZED                                       STD_OFF 
#define CANTP_RXTX_MAINFUNCTION_API                                            STD_OFF 
#define CANTP_CONSTANT_BS                                                      STD_ON 
#define CANTP_REJECT_FC_WITH_RES_STMIN                                         STD_OFF 
#define CANTP_USE_ONLY_FIRST_FC                                                STD_ON 
#define CANTP_ENABLE_CHANGE_PARAM                                              STD_OFF 
#define CANTP_ENABLE_READ_PARAM                                                STD_OFF 
#define CANTP_ONLY_NOTIFY_INFORMED_APPL                                        STD_ON 
#define CANTP_TRANSMIT_QUEUE                                                   STD_OFF 
#define CANTP_SUPPORT_LONG_FF                                                  STD_OFF 
#define CANTP_PDUR_API_AR_VERSION                                              0x412 
#define CANTP_SYNC_TRANSMIT                                                    STD_OFF 
#define CANTP_SUPPORT_CANFD                                                    STD_OFF 
#define CANTP_STMIN_BY_APPL                                                    STD_OFF 
#define CANTP_DCM_REQUEST_DETECT                                               STD_OFF 
#define CANTP_GENERIC_CONNECTIONS                                              STD_OFF 
#define CanTp_ApplStartSeparationTime                                           /*  mapping of user defined function to internal name  */  

 /*  CanTp Lower Layer  */ 
#define CANTP_LOLAYER_CANIF                                                    STD_ON 
#define CANTP_LOLAYER_TC                                                       STD_OFF 
#define CanTp_CanIfCancelTransmit(Dir, SduId, PduId)                            
#define CanTp_CanIfTransmit(Dir, SduId, PduId, Data)                           (CanIf_Transmit((PduId),(Data))) 


/* PRQA L:MACROS_3453 */



/* -----------------------------------------------------------------------------
    &&&~ Pre-Compile optimized configuration
 ----------------------------------------------------------------------------- */
 




/* -----------------------------------------------------------------------------
    &&&~ Rx Sdu Handle IDs
----------------------------------------------------------------------------- */
#define CanTpConf_CanTpRxNSdu_CanTpRxNSdu_002      0u 
#define CanTpConf_CanTpRxNSdu_CanTpRxNSdu_585bdea6 1u 
#define CanTpConf_CanTpRxNSdu_CanTpRxNSdu          2u 
#define CanTpConf_CanTpRxNSdu_CanTpRxNSdu_001      3u 
#define CanTpConf_CanTpRxNSdu_CanTpRxNSdu_fab217f5 4u 

 
/* -----------------------------------------------------------------------------
    &&&~ Tx Sdu Handle IDs
----------------------------------------------------------------------------- */
#define CanTpConf_CanTpTxNSdu_CanTpTxNSdu_002      0u 
#define CanTpConf_CanTpTxNSdu_CanTpTxNSdu          1u 
#define CanTpConf_CanTpTxNSdu_CanTpTxNSdu_001      2u 
#define CanTpConf_CanTpTxNSdu_CanTpTxNSdu_fab217f5 3u 


/* -----------------------------------------------------------------------------
    &&&~ Rx Pdu IDs
 ----------------------------------------------------------------------------- */
#define CanTpConf_CanTpRxFcNPdu_CanTpRxFcNPdu          0u 
#define CanTpConf_CanTpRxNPdu_CanTpRxNPdu              0u 
#define CanTpConf_CanTpRxFcNPdu_CanTpRxFcNPdu_b9a7b042 1u 
#define CanTpConf_CanTpRxNPdu_CanTpRxNPdu_9b5d64b0     1u 
#define CanTpConf_CanTpRxFcNPdu_CanTpRxFcNPdu_01       2u 
#define CanTpConf_CanTpRxNPdu_CanTpRxNPdu_1            2u 
#define CanTpConf_CanTpRxFcNPdu_CanTpRxFcNPdu_001      3u 
#define CanTpConf_CanTpRxNPdu_CanTpRxNPdu_2            3u 
#define CanTpConf_CanTpRxNPdu_CanTpRxNPdu_210b33f5     4u 


/* -----------------------------------------------------------------------------
    &&&~ TxConfirmation Pdu IDs
 ----------------------------------------------------------------------------- */
#define CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu_9b5d64b0 0u 
#define CanTpConf_CanTpTxNPdu_CanTpTxNPdu_b9a7b042     0u 
#define CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu_001      1u 
#define CanTpConf_CanTpTxNPdu_CanTpTxNPdu_1            1u 
#define CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu          2u 
#define CanTpConf_CanTpTxNPdu_CanTpTxNPdu              2u 
#define CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu_002      3u 
#define CanTpConf_CanTpTxNPdu_CanTpTxNPdu_2            3u 




 /**********************************************************************************************************************
 * MACROS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanTpPCDataSwitches  CanTp Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CANTP_CALCBS                                                                                STD_ON
#define CANTP_COMPATIBILITYVERSION                                                                  STD_ON
#define CANTP_DYNFCPARAMETERS                                                                       STD_OFF  /**< Deactivateable: 'CanTp_DynFCParameters' Reason: 'Change Paramter Api is disabled' */
#define CANTP_FINALMAGICNUMBER                                                                      STD_OFF  /**< Deactivateable: 'CanTp_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define CANTP_INITDATAHASHCODE                                                                      STD_OFF  /**< Deactivateable: 'CanTp_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define CANTP_LOLAYERFCTS                                                                           STD_OFF  /**< Deactivateable: 'CanTp_LoLayerFcts' Reason: 'A function table is not required, since just one lower layer exists.' */
#define CANTP_CANCELTRANSMITFCTOFLOLAYERFCTS                                                        STD_OFF  /**< Deactivateable: 'CanTp_LoLayerFcts.CancelTransmitFct' Reason: 'A function table is not required, since just one lower layer exists.' */
#define CANTP_TRANSMITFCTOFLOLAYERFCTS                                                              STD_OFF  /**< Deactivateable: 'CanTp_LoLayerFcts.TransmitFct' Reason: 'A function table is not required, since just one lower layer exists.' */
#define CANTP_RXCHANNELMAP                                                                          STD_OFF  /**< Deactivateable: 'CanTp_RxChannelMap' Reason: 'Dynamic Channel Assignment is disabled' */
#define CANTP_RXPDUMAP                                                                              STD_ON
#define CANTP_ADDRESSINGFORMATOFRXPDUMAP                                                            STD_ON
#define CANTP_GENERICCONNECTIONOFRXPDUMAP                                                           STD_ON
#define CANTP_PDUMETADATALENGTHOFRXPDUMAP                                                           STD_ON
#define CANTP_RXSDUCFGINDENDIDXOFRXPDUMAP                                                           STD_ON
#define CANTP_RXSDUCFGINDSTARTIDXOFRXPDUMAP                                                         STD_ON
#define CANTP_RXSDUCFGINDUSEDOFRXPDUMAP                                                             STD_ON
#define CANTP_TXSDUCFGINDENDIDXOFRXPDUMAP                                                           STD_ON
#define CANTP_TXSDUCFGINDSTARTIDXOFRXPDUMAP                                                         STD_ON
#define CANTP_TXSDUCFGINDUSEDOFRXPDUMAP                                                             STD_ON
#define CANTP_RXSDUCFG                                                                              STD_ON
#define CANTP_BLOCKSIZEOFRXSDUCFG                                                                   STD_ON
#define CANTP_CANTYPEOFRXSDUCFG                                                                     STD_ON
#define CANTP_CHANNELMODEOFRXSDUCFG                                                                 STD_ON
#define CANTP_GENERICCONNECTIONOFRXSDUCFG                                                           STD_ON
#define CANTP_LOLAYERFCTSIDXOFRXSDUCFG                                                              STD_OFF  /**< Deactivateable: 'CanTp_RxSduCfg.LoLayerFctsIdx' Reason: 'All indirection targets are deactivated in all variants.' */
#define CANTP_LOLAYERTXFCPDUIDOFRXSDUCFG                                                            STD_ON
#define CANTP_NAROFRXSDUCFG                                                                         STD_ON
#define CANTP_NBROFRXSDUCFG                                                                         STD_ON
#define CANTP_NCROFRXSDUCFG                                                                         STD_ON
#define CANTP_PASSSDUMETADATAOFRXSDUCFG                                                             STD_ON
#define CANTP_PDURRXSDUIDOFRXSDUCFG                                                                 STD_ON
#define CANTP_RXADDRESSOFRXSDUCFG                                                                   STD_ON
#define CANTP_RXADDRESSINGFORMATOFRXSDUCFG                                                          STD_ON
#define CANTP_RXMAXPAYLOADLENGTHOFRXSDUCFG                                                          STD_ON
#define CANTP_RXPADDINGACTIVATIONOFRXSDUCFG                                                         STD_ON
#define CANTP_RXPDUIDOFRXSDUCFG                                                                     STD_ON
#define CANTP_RXTATYPEOFRXSDUCFG                                                                    STD_ON
#define CANTP_RXWFTMAXOFRXSDUCFG                                                                    STD_ON
#define CANTP_STMINOFRXSDUCFG                                                                       STD_ON
#define CANTP_TXFCADDRESSOFRXSDUCFG                                                                 STD_ON
#define CANTP_TXFCPDUCONFIRMATIONPDUIDOFRXSDUCFG                                                    STD_ON
#define CANTP_TXSDUCFGIDXOFRXSDUCFG                                                                 STD_ON
#define CANTP_TXSDUCFGUSEDOFRXSDUCFG                                                                STD_ON
#define CANTP_RXSDUCFGIND                                                                           STD_ON
#define CANTP_RXSDUSNV2HDL                                                                          STD_ON
#define CANTP_RXSDUCFGIDXOFRXSDUSNV2HDL                                                             STD_ON
#define CANTP_RXSDUCFGUSEDOFRXSDUSNV2HDL                                                            STD_ON
#define CANTP_RXSTATE                                                                               STD_ON
#define CANTP_SIZEOFCALCBS                                                                          STD_ON
#define CANTP_SIZEOFRXPDUMAP                                                                        STD_ON
#define CANTP_SIZEOFRXSDUCFG                                                                        STD_ON
#define CANTP_SIZEOFRXSDUCFGIND                                                                     STD_ON
#define CANTP_SIZEOFRXSDUSNV2HDL                                                                    STD_ON
#define CANTP_SIZEOFRXSTATE                                                                         STD_ON
#define CANTP_SIZEOFTXSDUCFG                                                                        STD_ON
#define CANTP_SIZEOFTXSDUCFGIND                                                                     STD_ON
#define CANTP_SIZEOFTXSDUSNV2HDL                                                                    STD_ON
#define CANTP_SIZEOFTXSEMAPHORES                                                                    STD_ON
#define CANTP_SIZEOFTXSTATE                                                                         STD_ON
#define CANTP_TXCHANNELMAP                                                                          STD_OFF  /**< Deactivateable: 'CanTp_TxChannelMap' Reason: 'Dynamic Channel Assignment is disabled' */
#define CANTP_TXQUEUE                                                                               STD_OFF  /**< Deactivateable: 'CanTp_TxQueue' Reason: 'Transmit Queue is disabled' */
#define CANTP_TXSDUCFG                                                                              STD_ON
#define CANTP_CANTYPEOFTXSDUCFG                                                                     STD_ON
#define CANTP_CHANNELMODEOFTXSDUCFG                                                                 STD_ON
#define CANTP_LOLAYERFCTSIDXOFTXSDUCFG                                                              STD_OFF  /**< Deactivateable: 'CanTp_TxSduCfg.LoLayerFctsIdx' Reason: 'All indirection targets are deactivated in all variants.' */
#define CANTP_LOLAYERTXPDUIDOFTXSDUCFG                                                              STD_ON
#define CANTP_NASOFTXSDUCFG                                                                         STD_ON
#define CANTP_NBSOFTXSDUCFG                                                                         STD_ON
#define CANTP_NCSOFTXSDUCFG                                                                         STD_ON
#define CANTP_PDURTXSDUIDOFTXSDUCFG                                                                 STD_ON
#define CANTP_RXFCADDRESSOFTXSDUCFG                                                                 STD_ON
#define CANTP_RXFCPDUIDOFTXSDUCFG                                                                   STD_ON
#define CANTP_RXSDUCFGIDXOFTXSDUCFG                                                                 STD_ON
#define CANTP_RXSDUCFGUSEDOFTXSDUCFG                                                                STD_ON
#define CANTP_SDUMETADATALENGTHOFTXSDUCFG                                                           STD_ON
#define CANTP_TRANSMITCANCELLATIONOFTXSDUCFG                                                        STD_ON
#define CANTP_TXADDRESSOFTXSDUCFG                                                                   STD_ON
#define CANTP_TXADDRESSINGFORMATOFTXSDUCFG                                                          STD_ON
#define CANTP_TXMAXPAYLOADLENGTHOFTXSDUCFG                                                          STD_ON
#define CANTP_TXPADDINGACTIVATIONOFTXSDUCFG                                                         STD_ON
#define CANTP_TXPDUCONFIRMATIONPDUIDOFTXSDUCFG                                                      STD_ON
#define CANTP_TXTATYPEOFTXSDUCFG                                                                    STD_ON
#define CANTP_TXSDUCFGIND                                                                           STD_ON
#define CANTP_TXSDUSNV2HDL                                                                          STD_ON
#define CANTP_TXSDUCFGIDXOFTXSDUSNV2HDL                                                             STD_ON
#define CANTP_TXSDUCFGUSEDOFTXSDUSNV2HDL                                                            STD_ON
#define CANTP_TXSEMAPHORES                                                                          STD_ON
#define CANTP_TXSTATE                                                                               STD_ON
#define CANTP_PCCONFIG                                                                              STD_ON
#define CANTP_CALCBSOFPCCONFIG                                                                      STD_ON
#define CANTP_COMPATIBILITYVERSIONOFPCCONFIG                                                        STD_ON
#define CANTP_FINALMAGICNUMBEROFPCCONFIG                                                            STD_OFF  /**< Deactivateable: 'CanTp_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define CANTP_INITDATAHASHCODEOFPCCONFIG                                                            STD_OFF  /**< Deactivateable: 'CanTp_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define CANTP_RXPDUMAPOFPCCONFIG                                                                    STD_ON
#define CANTP_RXSDUCFGINDOFPCCONFIG                                                                 STD_ON
#define CANTP_RXSDUCFGOFPCCONFIG                                                                    STD_ON
#define CANTP_RXSDUSNV2HDLOFPCCONFIG                                                                STD_ON
#define CANTP_RXSTATEOFPCCONFIG                                                                     STD_ON
#define CANTP_SIZEOFCALCBSOFPCCONFIG                                                                STD_ON
#define CANTP_SIZEOFRXPDUMAPOFPCCONFIG                                                              STD_ON
#define CANTP_SIZEOFRXSDUCFGINDOFPCCONFIG                                                           STD_ON
#define CANTP_SIZEOFRXSDUCFGOFPCCONFIG                                                              STD_ON
#define CANTP_SIZEOFRXSDUSNV2HDLOFPCCONFIG                                                          STD_ON
#define CANTP_SIZEOFRXSTATEOFPCCONFIG                                                               STD_ON
#define CANTP_SIZEOFTXSDUCFGINDOFPCCONFIG                                                           STD_ON
#define CANTP_SIZEOFTXSDUCFGOFPCCONFIG                                                              STD_ON
#define CANTP_SIZEOFTXSDUSNV2HDLOFPCCONFIG                                                          STD_ON
#define CANTP_SIZEOFTXSEMAPHORESOFPCCONFIG                                                          STD_ON
#define CANTP_SIZEOFTXSTATEOFPCCONFIG                                                               STD_ON
#define CANTP_TXSDUCFGINDOFPCCONFIG                                                                 STD_ON
#define CANTP_TXSDUCFGOFPCCONFIG                                                                    STD_ON
#define CANTP_TXSDUSNV2HDLOFPCCONFIG                                                                STD_ON
#define CANTP_TXSEMAPHORESOFPCCONFIG                                                                STD_ON
#define CANTP_TXSTATEOFPCCONFIG                                                                     STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCMinNumericValueDefines  CanTp Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define CANTP_MIN_CALCBS                                                                            0u
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCMaxNumericValueDefines  CanTp Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define CANTP_MAX_CALCBS                                                                            255u
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCNoReferenceDefines  CanTp No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define CANTP_NO_RXSDUCFGINDENDIDXOFRXPDUMAP                                                        255u
#define CANTP_NO_RXSDUCFGINDSTARTIDXOFRXPDUMAP                                                      255u
#define CANTP_NO_TXSDUCFGINDENDIDXOFRXPDUMAP                                                        255u
#define CANTP_NO_TXSDUCFGINDSTARTIDXOFRXPDUMAP                                                      255u
#define CANTP_NO_TXSDUCFGIDXOFRXSDUCFG                                                              255u
#define CANTP_NO_RXSDUCFGIDXOFRXSDUSNV2HDL                                                          255u
#define CANTP_NO_RXSDUCFGIDXOFTXSDUCFG                                                              255u
#define CANTP_NO_TXSDUCFGIDXOFTXSDUSNV2HDL                                                          255u
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCEnumExistsDefines  CanTp Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define CANTP_EXISTS_NORMAL_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                                   STD_ON
#define CANTP_EXISTS_EXTENDED_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                                 STD_OFF
#define CANTP_EXISTS_MIXED11_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                                  STD_OFF
#define CANTP_EXISTS_NORMALFIXED_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                              STD_OFF
#define CANTP_EXISTS_MIXED29_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                                  STD_OFF
#define CANTP_EXISTS_CAN20_CANTYPEOFRXSDUCFG                                                        STD_ON
#define CANTP_EXISTS_CANFD_CANTYPEOFRXSDUCFG                                                        STD_OFF
#define CANTP_EXISTS_HALF_DUPLEX_CHANNELMODEOFRXSDUCFG                                              STD_OFF
#define CANTP_EXISTS_FULL_DUPLEX_CHANNELMODEOFRXSDUCFG                                              STD_ON
#define CANTP_EXISTS_NORMAL_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                                 STD_ON
#define CANTP_EXISTS_EXTENDED_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                               STD_OFF
#define CANTP_EXISTS_MIXED11_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                                STD_OFF
#define CANTP_EXISTS_NORMALFIXED_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                            STD_OFF
#define CANTP_EXISTS_MIXED29_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                                STD_OFF
#define CANTP_EXISTS_PHYSICAL_RXTATYPEOFRXSDUCFG                                                    STD_ON
#define CANTP_EXISTS_FUNCTIONAL_RXTATYPEOFRXSDUCFG                                                  STD_ON
#define CANTP_EXISTS_CANFD_PHYSICAL_RXTATYPEOFRXSDUCFG                                              STD_ON
#define CANTP_EXISTS_CANFD_FUNCTIONAL_RXTATYPEOFRXSDUCFG                                            STD_ON
#define CANTP_EXISTS_CAN20_CANTYPEOFTXSDUCFG                                                        STD_ON
#define CANTP_EXISTS_CANFD_CANTYPEOFTXSDUCFG                                                        STD_OFF
#define CANTP_EXISTS_HALF_DUPLEX_CHANNELMODEOFTXSDUCFG                                              STD_OFF
#define CANTP_EXISTS_FULL_DUPLEX_CHANNELMODEOFTXSDUCFG                                              STD_ON
#define CANTP_EXISTS_NORMAL_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                                 STD_ON
#define CANTP_EXISTS_EXTENDED_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                               STD_OFF
#define CANTP_EXISTS_MIXED11_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                                STD_OFF
#define CANTP_EXISTS_NORMALFIXED_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                            STD_OFF
#define CANTP_EXISTS_MIXED29_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                                STD_OFF
#define CANTP_EXISTS_PHYSICAL_TXTATYPEOFTXSDUCFG                                                    STD_ON
#define CANTP_EXISTS_FUNCTIONAL_TXTATYPEOFTXSDUCFG                                                  STD_OFF
#define CANTP_EXISTS_CANFD_PHYSICAL_TXTATYPEOFTXSDUCFG                                              STD_ON
#define CANTP_EXISTS_CANFD_FUNCTIONAL_TXTATYPEOFTXSDUCFG                                            STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCEnumDefines  CanTp Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define CANTP_NORMAL_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                                          0x00u
#define CANTP_CAN20_CANTYPEOFRXSDUCFG                                                               0x00u
#define CANTP_FULL_DUPLEX_CHANNELMODEOFRXSDUCFG                                                     0x01u
#define CANTP_NORMAL_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                                        0x00u
#define CANTP_PHYSICAL_RXTATYPEOFRXSDUCFG                                                           0x00u
#define CANTP_FUNCTIONAL_RXTATYPEOFRXSDUCFG                                                         0x01u
#define CANTP_CANFD_PHYSICAL_RXTATYPEOFRXSDUCFG                                                     0x00u
#define CANTP_CANFD_FUNCTIONAL_RXTATYPEOFRXSDUCFG                                                   0x01u
#define CANTP_CAN20_CANTYPEOFTXSDUCFG                                                               0x00u
#define CANTP_FULL_DUPLEX_CHANNELMODEOFTXSDUCFG                                                     0x01u
#define CANTP_NORMAL_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                                        0x00u
#define CANTP_PHYSICAL_TXTATYPEOFTXSDUCFG                                                           0x00u
#define CANTP_CANFD_PHYSICAL_TXTATYPEOFTXSDUCFG                                                     0x00u
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCIsReducedToDefineDefines  CanTp Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define CANTP_ISDEF_ADDRESSINGFORMATOFRXPDUMAP                                                      STD_ON
#define CANTP_ISDEF_GENERICCONNECTIONOFRXPDUMAP                                                     STD_ON
#define CANTP_ISDEF_PDUMETADATALENGTHOFRXPDUMAP                                                     STD_ON
#define CANTP_ISDEF_RXSDUCFGINDENDIDXOFRXPDUMAP                                                     STD_OFF
#define CANTP_ISDEF_RXSDUCFGINDSTARTIDXOFRXPDUMAP                                                   STD_OFF
#define CANTP_ISDEF_RXSDUCFGINDUSEDOFRXPDUMAP                                                       STD_ON
#define CANTP_ISDEF_TXSDUCFGINDENDIDXOFRXPDUMAP                                                     STD_OFF
#define CANTP_ISDEF_TXSDUCFGINDSTARTIDXOFRXPDUMAP                                                   STD_OFF
#define CANTP_ISDEF_TXSDUCFGINDUSEDOFRXPDUMAP                                                       STD_OFF
#define CANTP_ISDEF_BLOCKSIZEOFRXSDUCFG                                                             STD_ON
#define CANTP_ISDEF_CANTYPEOFRXSDUCFG                                                               STD_ON
#define CANTP_ISDEF_CHANNELMODEOFRXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_GENERICCONNECTIONOFRXSDUCFG                                                     STD_ON
#define CANTP_ISDEF_LOLAYERTXFCPDUIDOFRXSDUCFG                                                      STD_OFF
#define CANTP_ISDEF_NAROFRXSDUCFG                                                                   STD_OFF
#define CANTP_ISDEF_NBROFRXSDUCFG                                                                   STD_OFF
#define CANTP_ISDEF_NCROFRXSDUCFG                                                                   STD_OFF
#define CANTP_ISDEF_PASSSDUMETADATAOFRXSDUCFG                                                       STD_ON
#define CANTP_ISDEF_PDURRXSDUIDOFRXSDUCFG                                                           STD_OFF
#define CANTP_ISDEF_RXADDRESSOFRXSDUCFG                                                             STD_ON
#define CANTP_ISDEF_RXADDRESSINGFORMATOFRXSDUCFG                                                    STD_ON
#define CANTP_ISDEF_RXMAXPAYLOADLENGTHOFRXSDUCFG                                                    STD_ON
#define CANTP_ISDEF_RXPADDINGACTIVATIONOFRXSDUCFG                                                   STD_ON
#define CANTP_ISDEF_RXPDUIDOFRXSDUCFG                                                               STD_OFF
#define CANTP_ISDEF_RXTATYPEOFRXSDUCFG                                                              STD_OFF
#define CANTP_ISDEF_RXWFTMAXOFRXSDUCFG                                                              STD_ON
#define CANTP_ISDEF_STMINOFRXSDUCFG                                                                 STD_OFF
#define CANTP_ISDEF_TXFCADDRESSOFRXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_TXFCPDUCONFIRMATIONPDUIDOFRXSDUCFG                                              STD_OFF
#define CANTP_ISDEF_TXSDUCFGIDXOFRXSDUCFG                                                           STD_OFF
#define CANTP_ISDEF_TXSDUCFGUSEDOFRXSDUCFG                                                          STD_OFF
#define CANTP_ISDEF_RXSDUCFGIND                                                                     STD_OFF
#define CANTP_ISDEF_RXSDUCFGIDXOFRXSDUSNV2HDL                                                       STD_OFF
#define CANTP_ISDEF_RXSDUCFGUSEDOFRXSDUSNV2HDL                                                      STD_ON
#define CANTP_ISDEF_CANTYPEOFTXSDUCFG                                                               STD_ON
#define CANTP_ISDEF_CHANNELMODEOFTXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_LOLAYERTXPDUIDOFTXSDUCFG                                                        STD_OFF
#define CANTP_ISDEF_NASOFTXSDUCFG                                                                   STD_ON
#define CANTP_ISDEF_NBSOFTXSDUCFG                                                                   STD_ON
#define CANTP_ISDEF_NCSOFTXSDUCFG                                                                   STD_ON
#define CANTP_ISDEF_PDURTXSDUIDOFTXSDUCFG                                                           STD_OFF
#define CANTP_ISDEF_RXFCADDRESSOFTXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_RXFCPDUIDOFTXSDUCFG                                                             STD_OFF
#define CANTP_ISDEF_RXSDUCFGIDXOFTXSDUCFG                                                           STD_OFF
#define CANTP_ISDEF_RXSDUCFGUSEDOFTXSDUCFG                                                          STD_ON
#define CANTP_ISDEF_SDUMETADATALENGTHOFTXSDUCFG                                                     STD_ON
#define CANTP_ISDEF_TRANSMITCANCELLATIONOFTXSDUCFG                                                  STD_ON
#define CANTP_ISDEF_TXADDRESSOFTXSDUCFG                                                             STD_ON
#define CANTP_ISDEF_TXADDRESSINGFORMATOFTXSDUCFG                                                    STD_ON
#define CANTP_ISDEF_TXMAXPAYLOADLENGTHOFTXSDUCFG                                                    STD_ON
#define CANTP_ISDEF_TXPADDINGACTIVATIONOFTXSDUCFG                                                   STD_ON
#define CANTP_ISDEF_TXPDUCONFIRMATIONPDUIDOFTXSDUCFG                                                STD_OFF
#define CANTP_ISDEF_TXTATYPEOFTXSDUCFG                                                              STD_ON
#define CANTP_ISDEF_TXSDUCFGIND                                                                     STD_OFF
#define CANTP_ISDEF_TXSDUCFGIDXOFTXSDUSNV2HDL                                                       STD_OFF
#define CANTP_ISDEF_TXSDUCFGUSEDOFTXSDUSNV2HDL                                                      STD_ON
#define CANTP_ISDEF_CALCBSOFPCCONFIG                                                                STD_ON
#define CANTP_ISDEF_RXPDUMAPOFPCCONFIG                                                              STD_ON
#define CANTP_ISDEF_RXSDUCFGINDOFPCCONFIG                                                           STD_ON
#define CANTP_ISDEF_RXSDUCFGOFPCCONFIG                                                              STD_ON
#define CANTP_ISDEF_RXSDUSNV2HDLOFPCCONFIG                                                          STD_ON
#define CANTP_ISDEF_RXSTATEOFPCCONFIG                                                               STD_ON
#define CANTP_ISDEF_TXSDUCFGINDOFPCCONFIG                                                           STD_ON
#define CANTP_ISDEF_TXSDUCFGOFPCCONFIG                                                              STD_ON
#define CANTP_ISDEF_TXSDUSNV2HDLOFPCCONFIG                                                          STD_ON
#define CANTP_ISDEF_TXSEMAPHORESOFPCCONFIG                                                          STD_ON
#define CANTP_ISDEF_TXSTATEOFPCCONFIG                                                               STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCEqualsAlwaysToDefines  CanTp Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define CANTP_EQ2_ADDRESSINGFORMATOFRXPDUMAP                                                        CANTP_NORMAL_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP
#define CANTP_EQ2_GENERICCONNECTIONOFRXPDUMAP                                                       FALSE
#define CANTP_EQ2_PDUMETADATALENGTHOFRXPDUMAP                                                       0u
#define CANTP_EQ2_RXSDUCFGINDENDIDXOFRXPDUMAP                                                       
#define CANTP_EQ2_RXSDUCFGINDSTARTIDXOFRXPDUMAP                                                     
#define CANTP_EQ2_RXSDUCFGINDUSEDOFRXPDUMAP                                                         TRUE
#define CANTP_EQ2_TXSDUCFGINDENDIDXOFRXPDUMAP                                                       
#define CANTP_EQ2_TXSDUCFGINDSTARTIDXOFRXPDUMAP                                                     
#define CANTP_EQ2_TXSDUCFGINDUSEDOFRXPDUMAP                                                         
#define CANTP_EQ2_BLOCKSIZEOFRXSDUCFG                                                               8u
#define CANTP_EQ2_CANTYPEOFRXSDUCFG                                                                 CANTP_CAN20_CANTYPEOFRXSDUCFG
#define CANTP_EQ2_CHANNELMODEOFRXSDUCFG                                                             CANTP_FULL_DUPLEX_CHANNELMODEOFRXSDUCFG
#define CANTP_EQ2_GENERICCONNECTIONOFRXSDUCFG                                                       FALSE
#define CANTP_EQ2_LOLAYERTXFCPDUIDOFRXSDUCFG                                                        
#define CANTP_EQ2_NAROFRXSDUCFG                                                                     
#define CANTP_EQ2_NBROFRXSDUCFG                                                                     
#define CANTP_EQ2_NCROFRXSDUCFG                                                                     
#define CANTP_EQ2_PASSSDUMETADATAOFRXSDUCFG                                                         FALSE
#define CANTP_EQ2_PDURRXSDUIDOFRXSDUCFG                                                             
#define CANTP_EQ2_RXADDRESSOFRXSDUCFG                                                               255u
#define CANTP_EQ2_RXADDRESSINGFORMATOFRXSDUCFG                                                      CANTP_NORMAL_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG
#define CANTP_EQ2_RXMAXPAYLOADLENGTHOFRXSDUCFG                                                      7u
#define CANTP_EQ2_RXPADDINGACTIVATIONOFRXSDUCFG                                                     TRUE
#define CANTP_EQ2_RXPDUIDOFRXSDUCFG                                                                 
#define CANTP_EQ2_RXTATYPEOFRXSDUCFG                                                                
#define CANTP_EQ2_RXWFTMAXOFRXSDUCFG                                                                15u
#define CANTP_EQ2_STMINOFRXSDUCFG                                                                   
#define CANTP_EQ2_TXFCADDRESSOFRXSDUCFG                                                             255u
#define CANTP_EQ2_TXFCPDUCONFIRMATIONPDUIDOFRXSDUCFG                                                
#define CANTP_EQ2_TXSDUCFGIDXOFRXSDUCFG                                                             
#define CANTP_EQ2_TXSDUCFGUSEDOFRXSDUCFG                                                            
#define CANTP_EQ2_RXSDUCFGIND                                                                       
#define CANTP_EQ2_RXSDUCFGIDXOFRXSDUSNV2HDL                                                         
#define CANTP_EQ2_RXSDUCFGUSEDOFRXSDUSNV2HDL                                                        TRUE
#define CANTP_EQ2_CANTYPEOFTXSDUCFG                                                                 CANTP_CAN20_CANTYPEOFTXSDUCFG
#define CANTP_EQ2_CHANNELMODEOFTXSDUCFG                                                             CANTP_FULL_DUPLEX_CHANNELMODEOFTXSDUCFG
#define CANTP_EQ2_LOLAYERTXPDUIDOFTXSDUCFG                                                          
#define CANTP_EQ2_NASOFTXSDUCFG                                                                     15u
#define CANTP_EQ2_NBSOFTXSDUCFG                                                                     31u
#define CANTP_EQ2_NCSOFTXSDUCFG                                                                     14u
#define CANTP_EQ2_PDURTXSDUIDOFTXSDUCFG                                                             
#define CANTP_EQ2_RXFCADDRESSOFTXSDUCFG                                                             255u
#define CANTP_EQ2_RXFCPDUIDOFTXSDUCFG                                                               
#define CANTP_EQ2_RXSDUCFGIDXOFTXSDUCFG                                                             
#define CANTP_EQ2_RXSDUCFGUSEDOFTXSDUCFG                                                            TRUE
#define CANTP_EQ2_SDUMETADATALENGTHOFTXSDUCFG                                                       0u
#define CANTP_EQ2_TRANSMITCANCELLATIONOFTXSDUCFG                                                    FALSE
#define CANTP_EQ2_TXADDRESSOFTXSDUCFG                                                               255u
#define CANTP_EQ2_TXADDRESSINGFORMATOFTXSDUCFG                                                      CANTP_NORMAL_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG
#define CANTP_EQ2_TXMAXPAYLOADLENGTHOFTXSDUCFG                                                      7u
#define CANTP_EQ2_TXPADDINGACTIVATIONOFTXSDUCFG                                                     TRUE
#define CANTP_EQ2_TXPDUCONFIRMATIONPDUIDOFTXSDUCFG                                                  
#define CANTP_EQ2_TXTATYPEOFTXSDUCFG                                                                CANTP_PHYSICAL_TXTATYPEOFTXSDUCFG
#define CANTP_EQ2_TXSDUCFGIND                                                                       
#define CANTP_EQ2_TXSDUCFGIDXOFTXSDUSNV2HDL                                                         
#define CANTP_EQ2_TXSDUCFGUSEDOFTXSDUSNV2HDL                                                        TRUE
#define CANTP_EQ2_CALCBSOFPCCONFIG                                                                  CanTp_CalcBS
#define CANTP_EQ2_RXPDUMAPOFPCCONFIG                                                                CanTp_RxPduMap
#define CANTP_EQ2_RXSDUCFGINDOFPCCONFIG                                                             CanTp_RxSduCfgInd
#define CANTP_EQ2_RXSDUCFGOFPCCONFIG                                                                CanTp_RxSduCfg
#define CANTP_EQ2_RXSDUSNV2HDLOFPCCONFIG                                                            CanTp_RxSduSnv2Hdl
#define CANTP_EQ2_RXSTATEOFPCCONFIG                                                                 CanTp_RxState
#define CANTP_EQ2_TXSDUCFGINDOFPCCONFIG                                                             CanTp_TxSduCfgInd
#define CANTP_EQ2_TXSDUCFGOFPCCONFIG                                                                CanTp_TxSduCfg
#define CANTP_EQ2_TXSDUSNV2HDLOFPCCONFIG                                                            CanTp_TxSduSnv2Hdl
#define CANTP_EQ2_TXSEMAPHORESOFPCCONFIG                                                            CanTp_TxSemaphores
#define CANTP_EQ2_TXSTATEOFPCCONFIG                                                                 CanTp_TxState
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCSymbolicInitializationPointers  CanTp Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define CanTp_Config_Ptr                                                                            NULL_PTR  /**< symbolic identifier which shall be used to initialize 'CanTp' */
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCInitializationSymbols  CanTp Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define CanTp_Config                                                                                NULL_PTR  /**< symbolic identifier which could be used to initialize 'CanTp */
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCGeneral  CanTp General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define CANTP_CHECK_INIT_POINTER                                                                    STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define CANTP_FINAL_MAGIC_NUMBER                                                                    0x231Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of CanTp */
#define CANTP_INDIVIDUAL_POSTBUILD                                                                  STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'CanTp' is not configured to be postbuild capable. */
#define CANTP_INIT_DATA                                                                             CANTP_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define CANTP_INIT_DATA_HASH_CODE                                                                   835452236  /**< the precompile constant to validate the initialization structure at initialization time of CanTp with a hashcode. The seed value is '0x231Eu' */
#define CANTP_USE_ECUM_BSW_ERROR_HOOK                                                               STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define CANTP_USE_INIT_POINTER                                                                      STD_OFF  /**< STD_ON if the init pointer CanTp shall be used. */
/** 
  \}
*/ 


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
  \defgroup  CanTpPCGetConstantDuplicatedRootDataMacros  CanTp Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define CanTp_GetCalcBSOfPCConfig()                                                                 CanTp_CalcBS  /**< the pointer to CanTp_CalcBS */
#define CanTp_GetCompatibilityVersionOfPCConfig()                                                   380999u
#define CanTp_GetRxPduMapOfPCConfig()                                                               CanTp_RxPduMap  /**< the pointer to CanTp_RxPduMap */
#define CanTp_GetRxSduCfgIndOfPCConfig()                                                            CanTp_RxSduCfgInd  /**< the pointer to CanTp_RxSduCfgInd */
#define CanTp_GetRxSduCfgOfPCConfig()                                                               CanTp_RxSduCfg  /**< the pointer to CanTp_RxSduCfg */
#define CanTp_GetRxSduSnv2HdlOfPCConfig()                                                           CanTp_RxSduSnv2Hdl  /**< the pointer to CanTp_RxSduSnv2Hdl */
#define CanTp_GetRxStateOfPCConfig()                                                                CanTp_RxState  /**< the pointer to CanTp_RxState */
#define CanTp_GetSizeOfCalcBSOfPCConfig()                                                           5u  /**< the number of accomplishable value elements in CanTp_CalcBS */
#define CanTp_GetSizeOfRxPduMapOfPCConfig()                                                         5u  /**< the number of accomplishable value elements in CanTp_RxPduMap */
#define CanTp_GetSizeOfRxSduCfgIndOfPCConfig()                                                      5u  /**< the number of accomplishable value elements in CanTp_RxSduCfgInd */
#define CanTp_GetSizeOfRxSduCfgOfPCConfig()                                                         5u  /**< the number of accomplishable value elements in CanTp_RxSduCfg */
#define CanTp_GetSizeOfRxSduSnv2HdlOfPCConfig()                                                     5u  /**< the number of accomplishable value elements in CanTp_RxSduSnv2Hdl */
#define CanTp_GetSizeOfRxStateOfPCConfig()                                                          5u  /**< the number of accomplishable value elements in CanTp_RxState */
#define CanTp_GetSizeOfTxSduCfgIndOfPCConfig()                                                      4u  /**< the number of accomplishable value elements in CanTp_TxSduCfgInd */
#define CanTp_GetSizeOfTxSduCfgOfPCConfig()                                                         4u  /**< the number of accomplishable value elements in CanTp_TxSduCfg */
#define CanTp_GetSizeOfTxSduSnv2HdlOfPCConfig()                                                     4u  /**< the number of accomplishable value elements in CanTp_TxSduSnv2Hdl */
#define CanTp_GetSizeOfTxSemaphoresOfPCConfig()                                                     4u  /**< the number of accomplishable value elements in CanTp_TxSemaphores */
#define CanTp_GetSizeOfTxStateOfPCConfig()                                                          4u  /**< the number of accomplishable value elements in CanTp_TxState */
#define CanTp_GetTxSduCfgIndOfPCConfig()                                                            CanTp_TxSduCfgInd  /**< the pointer to CanTp_TxSduCfgInd */
#define CanTp_GetTxSduCfgOfPCConfig()                                                               CanTp_TxSduCfg  /**< the pointer to CanTp_TxSduCfg */
#define CanTp_GetTxSduSnv2HdlOfPCConfig()                                                           CanTp_TxSduSnv2Hdl  /**< the pointer to CanTp_TxSduSnv2Hdl */
#define CanTp_GetTxSemaphoresOfPCConfig()                                                           CanTp_TxSemaphores  /**< the pointer to CanTp_TxSemaphores */
#define CanTp_GetTxStateOfPCConfig()                                                                CanTp_TxState  /**< the pointer to CanTp_TxState */
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCGetDataMacros  CanTp Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define CanTp_GetCalcBS(Index)                                                                      (CanTp_GetCalcBSOfPCConfig()[(Index)])
#define CanTp_GetRxSduCfgIndEndIdxOfRxPduMap(Index)                                                 (CanTp_GetRxPduMapOfPCConfig()[(Index)].RxSduCfgIndEndIdxOfRxPduMap)
#define CanTp_GetRxSduCfgIndStartIdxOfRxPduMap(Index)                                               (CanTp_GetRxPduMapOfPCConfig()[(Index)].RxSduCfgIndStartIdxOfRxPduMap)
#define CanTp_GetTxSduCfgIndEndIdxOfRxPduMap(Index)                                                 (CanTp_GetRxPduMapOfPCConfig()[(Index)].TxSduCfgIndEndIdxOfRxPduMap)
#define CanTp_GetTxSduCfgIndStartIdxOfRxPduMap(Index)                                               (CanTp_GetRxPduMapOfPCConfig()[(Index)].TxSduCfgIndStartIdxOfRxPduMap)
#define CanTp_GetLoLayerTxFcPduIdOfRxSduCfg(Index)                                                  (CanTp_GetRxSduCfgOfPCConfig()[(Index)].LoLayerTxFcPduIdOfRxSduCfg)
#define CanTp_GetNArOfRxSduCfg(Index)                                                               (CanTp_GetRxSduCfgOfPCConfig()[(Index)].NArOfRxSduCfg)
#define CanTp_GetNBrOfRxSduCfg(Index)                                                               (CanTp_GetRxSduCfgOfPCConfig()[(Index)].NBrOfRxSduCfg)
#define CanTp_GetNCrOfRxSduCfg(Index)                                                               (CanTp_GetRxSduCfgOfPCConfig()[(Index)].NCrOfRxSduCfg)
#define CanTp_GetPduRRxSduIdOfRxSduCfg(Index)                                                       (CanTp_GetRxSduCfgOfPCConfig()[(Index)].PduRRxSduIdOfRxSduCfg)
#define CanTp_GetRxPduIdOfRxSduCfg(Index)                                                           (CanTp_GetRxSduCfgOfPCConfig()[(Index)].RxPduIdOfRxSduCfg)
#define CanTp_GetRxTaTypeOfRxSduCfg(Index)                                                          (CanTp_GetRxSduCfgOfPCConfig()[(Index)].RxTaTypeOfRxSduCfg)
#define CanTp_GetSTminOfRxSduCfg(Index)                                                             (CanTp_GetRxSduCfgOfPCConfig()[(Index)].STminOfRxSduCfg)
#define CanTp_GetTxFcPduConfirmationPduIdOfRxSduCfg(Index)                                          (CanTp_GetRxSduCfgOfPCConfig()[(Index)].TxFcPduConfirmationPduIdOfRxSduCfg)
#define CanTp_GetTxSduCfgIdxOfRxSduCfg(Index)                                                       (CanTp_GetRxSduCfgOfPCConfig()[(Index)].TxSduCfgIdxOfRxSduCfg)
#define CanTp_GetRxSduCfgInd(Index)                                                                 (CanTp_GetRxSduCfgIndOfPCConfig()[(Index)])
#define CanTp_GetRxSduCfgIdxOfRxSduSnv2Hdl(Index)                                                   (CanTp_GetRxSduSnv2HdlOfPCConfig()[(Index)].RxSduCfgIdxOfRxSduSnv2Hdl)
#define CanTp_GetRxState(Index)                                                                     (CanTp_GetRxStateOfPCConfig()[(Index)])
#define CanTp_GetLoLayerTxPduIdOfTxSduCfg(Index)                                                    (CanTp_GetTxSduCfgOfPCConfig()[(Index)].LoLayerTxPduIdOfTxSduCfg)
#define CanTp_GetPduRTxSduIdOfTxSduCfg(Index)                                                       (CanTp_GetTxSduCfgOfPCConfig()[(Index)].PduRTxSduIdOfTxSduCfg)
#define CanTp_GetRxFcPduIdOfTxSduCfg(Index)                                                         (CanTp_GetTxSduCfgOfPCConfig()[(Index)].RxFcPduIdOfTxSduCfg)
#define CanTp_GetRxSduCfgIdxOfTxSduCfg(Index)                                                       (CanTp_GetTxSduCfgOfPCConfig()[(Index)].RxSduCfgIdxOfTxSduCfg)
#define CanTp_GetTxPduConfirmationPduIdOfTxSduCfg(Index)                                            (CanTp_GetTxSduCfgOfPCConfig()[(Index)].TxPduConfirmationPduIdOfTxSduCfg)
#define CanTp_GetTxSduCfgInd(Index)                                                                 (CanTp_GetTxSduCfgIndOfPCConfig()[(Index)])
#define CanTp_GetTxSduCfgIdxOfTxSduSnv2Hdl(Index)                                                   (CanTp_GetTxSduSnv2HdlOfPCConfig()[(Index)].TxSduCfgIdxOfTxSduSnv2Hdl)
#define CanTp_GetTxSemaphores(Index)                                                                (CanTp_GetTxSemaphoresOfPCConfig()[(Index)])
#define CanTp_GetTxState(Index)                                                                     (CanTp_GetTxStateOfPCConfig()[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCGetDeduplicatedDataMacros  CanTp Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define CanTp_GetCompatibilityVersion()                                                             CanTp_GetCompatibilityVersionOfPCConfig()
#define CanTp_GetAddressingFormatOfRxPduMap(Index)                                                  CANTP_NORMAL_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP
#define CanTp_IsGenericConnectionOfRxPduMap(Index)                                                  (((FALSE)) != FALSE)
#define CanTp_GetPduMetadataLengthOfRxPduMap(Index)                                                 0u
#define CanTp_IsRxSduCfgIndUsedOfRxPduMap(Index)                                                    (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to CanTp_RxSduCfgInd */
#define CanTp_IsTxSduCfgIndUsedOfRxPduMap(Index)                                                    (((boolean)(CanTp_GetTxSduCfgIndStartIdxOfRxPduMap(Index) != CANTP_NO_TXSDUCFGINDSTARTIDXOFRXPDUMAP)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to CanTp_TxSduCfgInd */
#define CanTp_GetBlockSizeOfRxSduCfg(Index)                                                         8u
#define CanTp_GetCanTypeOfRxSduCfg(Index)                                                           CANTP_CAN20_CANTYPEOFRXSDUCFG
#define CanTp_GetChannelModeOfRxSduCfg(Index)                                                       CANTP_FULL_DUPLEX_CHANNELMODEOFRXSDUCFG
#define CanTp_IsGenericConnectionOfRxSduCfg(Index)                                                  (((FALSE)) != FALSE)
#define CanTp_IsPassSduMetadataOfRxSduCfg(Index)                                                    (((FALSE)) != FALSE)
#define CanTp_GetRxAddressOfRxSduCfg(Index)                                                         255u
#define CanTp_GetRxAddressingFormatOfRxSduCfg(Index)                                                CANTP_NORMAL_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG
#define CanTp_GetRxMaxPayloadLengthOfRxSduCfg(Index)                                                7u
#define CanTp_IsRxPaddingActivationOfRxSduCfg(Index)                                                (((TRUE)) != FALSE)
#define CanTp_GetRxWftMaxOfRxSduCfg(Index)                                                          15u
#define CanTp_GetTxFcAddressOfRxSduCfg(Index)                                                       255u
#define CanTp_IsTxSduCfgUsedOfRxSduCfg(Index)                                                       (((boolean)(CanTp_GetTxSduCfgIdxOfRxSduCfg(Index) != CANTP_NO_TXSDUCFGIDXOFRXSDUCFG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to CanTp_TxSduCfg */
#define CanTp_IsRxSduCfgUsedOfRxSduSnv2Hdl(Index)                                                   (((TRUE)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to CanTp_RxSduCfg */
#define CanTp_GetSizeOfCalcBS()                                                                     CanTp_GetSizeOfCalcBSOfPCConfig()
#define CanTp_GetSizeOfRxPduMap()                                                                   CanTp_GetSizeOfRxPduMapOfPCConfig()
#define CanTp_GetSizeOfRxSduCfg()                                                                   CanTp_GetSizeOfRxSduCfgOfPCConfig()
#define CanTp_GetSizeOfRxSduCfgInd()                                                                CanTp_GetSizeOfRxSduCfgIndOfPCConfig()
#define CanTp_GetSizeOfRxSduSnv2Hdl()                                                               CanTp_GetSizeOfRxSduSnv2HdlOfPCConfig()
#define CanTp_GetSizeOfRxState()                                                                    CanTp_GetSizeOfRxStateOfPCConfig()
#define CanTp_GetSizeOfTxSduCfg()                                                                   CanTp_GetSizeOfTxSduCfgOfPCConfig()
#define CanTp_GetSizeOfTxSduCfgInd()                                                                CanTp_GetSizeOfTxSduCfgIndOfPCConfig()
#define CanTp_GetSizeOfTxSduSnv2Hdl()                                                               CanTp_GetSizeOfTxSduSnv2HdlOfPCConfig()
#define CanTp_GetSizeOfTxSemaphores()                                                               CanTp_GetSizeOfTxSemaphoresOfPCConfig()
#define CanTp_GetSizeOfTxState()                                                                    CanTp_GetSizeOfTxStateOfPCConfig()
#define CanTp_GetCanTypeOfTxSduCfg(Index)                                                           CANTP_CAN20_CANTYPEOFTXSDUCFG
#define CanTp_GetChannelModeOfTxSduCfg(Index)                                                       CANTP_FULL_DUPLEX_CHANNELMODEOFTXSDUCFG
#define CanTp_GetNAsOfTxSduCfg(Index)                                                               15u
#define CanTp_GetNBsOfTxSduCfg(Index)                                                               31u
#define CanTp_GetNCsOfTxSduCfg(Index)                                                               14u
#define CanTp_GetRxFcAddressOfTxSduCfg(Index)                                                       255u
#define CanTp_IsRxSduCfgUsedOfTxSduCfg(Index)                                                       (((TRUE)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to CanTp_RxSduCfg */
#define CanTp_GetSduMetadataLengthOfTxSduCfg(Index)                                                 0u
#define CanTp_IsTransmitCancellationOfTxSduCfg(Index)                                               (((FALSE)) != FALSE)
#define CanTp_GetTxAddressOfTxSduCfg(Index)                                                         255u
#define CanTp_GetTxAddressingFormatOfTxSduCfg(Index)                                                CANTP_NORMAL_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG
#define CanTp_GetTxMaxPayloadLengthOfTxSduCfg(Index)                                                7u
#define CanTp_IsTxPaddingActivationOfTxSduCfg(Index)                                                (((TRUE)) != FALSE)
#define CanTp_GetTxTaTypeOfTxSduCfg(Index)                                                          CANTP_PHYSICAL_TXTATYPEOFTXSDUCFG
#define CanTp_IsTxSduCfgUsedOfTxSduSnv2Hdl(Index)                                                   (((TRUE)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to CanTp_TxSduCfg */
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCSetDataMacros  CanTp Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define CanTp_SetCalcBS(Index, Value)                                                               CanTp_GetCalcBSOfPCConfig()[(Index)] = (Value)
#define CanTp_SetRxState(Index, Value)                                                              CanTp_GetRxStateOfPCConfig()[(Index)] = (Value)
#define CanTp_SetTxSemaphores(Index, Value)                                                         CanTp_GetTxSemaphoresOfPCConfig()[(Index)] = (Value)
#define CanTp_SetTxState(Index, Value)                                                              CanTp_GetTxStateOfPCConfig()[(Index)] = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCHasMacros  CanTp Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define CanTp_HasCalcBS()                                                                           (TRUE != FALSE)
#define CanTp_HasCompatibilityVersion()                                                             (TRUE != FALSE)
#define CanTp_HasRxPduMap()                                                                         (TRUE != FALSE)
#define CanTp_HasAddressingFormatOfRxPduMap()                                                       (TRUE != FALSE)
#define CanTp_HasGenericConnectionOfRxPduMap()                                                      (TRUE != FALSE)
#define CanTp_HasPduMetadataLengthOfRxPduMap()                                                      (TRUE != FALSE)
#define CanTp_HasRxSduCfgIndEndIdxOfRxPduMap()                                                      (TRUE != FALSE)
#define CanTp_HasRxSduCfgIndStartIdxOfRxPduMap()                                                    (TRUE != FALSE)
#define CanTp_HasRxSduCfgIndUsedOfRxPduMap()                                                        (TRUE != FALSE)
#define CanTp_HasTxSduCfgIndEndIdxOfRxPduMap()                                                      (TRUE != FALSE)
#define CanTp_HasTxSduCfgIndStartIdxOfRxPduMap()                                                    (TRUE != FALSE)
#define CanTp_HasTxSduCfgIndUsedOfRxPduMap()                                                        (TRUE != FALSE)
#define CanTp_HasRxSduCfg()                                                                         (TRUE != FALSE)
#define CanTp_HasBlockSizeOfRxSduCfg()                                                              (TRUE != FALSE)
#define CanTp_HasCanTypeOfRxSduCfg()                                                                (TRUE != FALSE)
#define CanTp_HasChannelModeOfRxSduCfg()                                                            (TRUE != FALSE)
#define CanTp_HasGenericConnectionOfRxSduCfg()                                                      (TRUE != FALSE)
#define CanTp_HasLoLayerTxFcPduIdOfRxSduCfg()                                                       (TRUE != FALSE)
#define CanTp_HasNArOfRxSduCfg()                                                                    (TRUE != FALSE)
#define CanTp_HasNBrOfRxSduCfg()                                                                    (TRUE != FALSE)
#define CanTp_HasNCrOfRxSduCfg()                                                                    (TRUE != FALSE)
#define CanTp_HasPassSduMetadataOfRxSduCfg()                                                        (TRUE != FALSE)
#define CanTp_HasPduRRxSduIdOfRxSduCfg()                                                            (TRUE != FALSE)
#define CanTp_HasRxAddressOfRxSduCfg()                                                              (TRUE != FALSE)
#define CanTp_HasRxAddressingFormatOfRxSduCfg()                                                     (TRUE != FALSE)
#define CanTp_HasRxMaxPayloadLengthOfRxSduCfg()                                                     (TRUE != FALSE)
#define CanTp_HasRxPaddingActivationOfRxSduCfg()                                                    (TRUE != FALSE)
#define CanTp_HasRxPduIdOfRxSduCfg()                                                                (TRUE != FALSE)
#define CanTp_HasRxTaTypeOfRxSduCfg()                                                               (TRUE != FALSE)
#define CanTp_HasRxWftMaxOfRxSduCfg()                                                               (TRUE != FALSE)
#define CanTp_HasSTminOfRxSduCfg()                                                                  (TRUE != FALSE)
#define CanTp_HasTxFcAddressOfRxSduCfg()                                                            (TRUE != FALSE)
#define CanTp_HasTxFcPduConfirmationPduIdOfRxSduCfg()                                               (TRUE != FALSE)
#define CanTp_HasTxSduCfgIdxOfRxSduCfg()                                                            (TRUE != FALSE)
#define CanTp_HasTxSduCfgUsedOfRxSduCfg()                                                           (TRUE != FALSE)
#define CanTp_HasRxSduCfgInd()                                                                      (TRUE != FALSE)
#define CanTp_HasRxSduSnv2Hdl()                                                                     (TRUE != FALSE)
#define CanTp_HasRxSduCfgIdxOfRxSduSnv2Hdl()                                                        (TRUE != FALSE)
#define CanTp_HasRxSduCfgUsedOfRxSduSnv2Hdl()                                                       (TRUE != FALSE)
#define CanTp_HasRxState()                                                                          (TRUE != FALSE)
#define CanTp_HasSizeOfCalcBS()                                                                     (TRUE != FALSE)
#define CanTp_HasSizeOfRxPduMap()                                                                   (TRUE != FALSE)
#define CanTp_HasSizeOfRxSduCfg()                                                                   (TRUE != FALSE)
#define CanTp_HasSizeOfRxSduCfgInd()                                                                (TRUE != FALSE)
#define CanTp_HasSizeOfRxSduSnv2Hdl()                                                               (TRUE != FALSE)
#define CanTp_HasSizeOfRxState()                                                                    (TRUE != FALSE)
#define CanTp_HasSizeOfTxSduCfg()                                                                   (TRUE != FALSE)
#define CanTp_HasSizeOfTxSduCfgInd()                                                                (TRUE != FALSE)
#define CanTp_HasSizeOfTxSduSnv2Hdl()                                                               (TRUE != FALSE)
#define CanTp_HasSizeOfTxSemaphores()                                                               (TRUE != FALSE)
#define CanTp_HasSizeOfTxState()                                                                    (TRUE != FALSE)
#define CanTp_HasTxSduCfg()                                                                         (TRUE != FALSE)
#define CanTp_HasCanTypeOfTxSduCfg()                                                                (TRUE != FALSE)
#define CanTp_HasChannelModeOfTxSduCfg()                                                            (TRUE != FALSE)
#define CanTp_HasLoLayerTxPduIdOfTxSduCfg()                                                         (TRUE != FALSE)
#define CanTp_HasNAsOfTxSduCfg()                                                                    (TRUE != FALSE)
#define CanTp_HasNBsOfTxSduCfg()                                                                    (TRUE != FALSE)
#define CanTp_HasNCsOfTxSduCfg()                                                                    (TRUE != FALSE)
#define CanTp_HasPduRTxSduIdOfTxSduCfg()                                                            (TRUE != FALSE)
#define CanTp_HasRxFcAddressOfTxSduCfg()                                                            (TRUE != FALSE)
#define CanTp_HasRxFcPduIdOfTxSduCfg()                                                              (TRUE != FALSE)
#define CanTp_HasRxSduCfgIdxOfTxSduCfg()                                                            (TRUE != FALSE)
#define CanTp_HasRxSduCfgUsedOfTxSduCfg()                                                           (TRUE != FALSE)
#define CanTp_HasSduMetadataLengthOfTxSduCfg()                                                      (TRUE != FALSE)
#define CanTp_HasTransmitCancellationOfTxSduCfg()                                                   (TRUE != FALSE)
#define CanTp_HasTxAddressOfTxSduCfg()                                                              (TRUE != FALSE)
#define CanTp_HasTxAddressingFormatOfTxSduCfg()                                                     (TRUE != FALSE)
#define CanTp_HasTxMaxPayloadLengthOfTxSduCfg()                                                     (TRUE != FALSE)
#define CanTp_HasTxPaddingActivationOfTxSduCfg()                                                    (TRUE != FALSE)
#define CanTp_HasTxPduConfirmationPduIdOfTxSduCfg()                                                 (TRUE != FALSE)
#define CanTp_HasTxTaTypeOfTxSduCfg()                                                               (TRUE != FALSE)
#define CanTp_HasTxSduCfgInd()                                                                      (TRUE != FALSE)
#define CanTp_HasTxSduSnv2Hdl()                                                                     (TRUE != FALSE)
#define CanTp_HasTxSduCfgIdxOfTxSduSnv2Hdl()                                                        (TRUE != FALSE)
#define CanTp_HasTxSduCfgUsedOfTxSduSnv2Hdl()                                                       (TRUE != FALSE)
#define CanTp_HasTxSemaphores()                                                                     (TRUE != FALSE)
#define CanTp_HasTxState()                                                                          (TRUE != FALSE)
#define CanTp_HasPCConfig()                                                                         (TRUE != FALSE)
#define CanTp_HasCalcBSOfPCConfig()                                                                 (TRUE != FALSE)
#define CanTp_HasCompatibilityVersionOfPCConfig()                                                   (TRUE != FALSE)
#define CanTp_HasRxPduMapOfPCConfig()                                                               (TRUE != FALSE)
#define CanTp_HasRxSduCfgIndOfPCConfig()                                                            (TRUE != FALSE)
#define CanTp_HasRxSduCfgOfPCConfig()                                                               (TRUE != FALSE)
#define CanTp_HasRxSduSnv2HdlOfPCConfig()                                                           (TRUE != FALSE)
#define CanTp_HasRxStateOfPCConfig()                                                                (TRUE != FALSE)
#define CanTp_HasSizeOfCalcBSOfPCConfig()                                                           (TRUE != FALSE)
#define CanTp_HasSizeOfRxPduMapOfPCConfig()                                                         (TRUE != FALSE)
#define CanTp_HasSizeOfRxSduCfgIndOfPCConfig()                                                      (TRUE != FALSE)
#define CanTp_HasSizeOfRxSduCfgOfPCConfig()                                                         (TRUE != FALSE)
#define CanTp_HasSizeOfRxSduSnv2HdlOfPCConfig()                                                     (TRUE != FALSE)
#define CanTp_HasSizeOfRxStateOfPCConfig()                                                          (TRUE != FALSE)
#define CanTp_HasSizeOfTxSduCfgIndOfPCConfig()                                                      (TRUE != FALSE)
#define CanTp_HasSizeOfTxSduCfgOfPCConfig()                                                         (TRUE != FALSE)
#define CanTp_HasSizeOfTxSduSnv2HdlOfPCConfig()                                                     (TRUE != FALSE)
#define CanTp_HasSizeOfTxSemaphoresOfPCConfig()                                                     (TRUE != FALSE)
#define CanTp_HasSizeOfTxStateOfPCConfig()                                                          (TRUE != FALSE)
#define CanTp_HasTxSduCfgIndOfPCConfig()                                                            (TRUE != FALSE)
#define CanTp_HasTxSduCfgOfPCConfig()                                                               (TRUE != FALSE)
#define CanTp_HasTxSduSnv2HdlOfPCConfig()                                                           (TRUE != FALSE)
#define CanTp_HasTxSemaphoresOfPCConfig()                                                           (TRUE != FALSE)
#define CanTp_HasTxStateOfPCConfig()                                                                (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCIncrementDataMacros  CanTp Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define CanTp_IncCalcBS(Index)                                                                      CanTp_GetCalcBS(Index)++
#define CanTp_IncRxState(Index)                                                                     CanTp_GetRxState(Index)++
#define CanTp_IncTxSemaphores(Index)                                                                CanTp_GetTxSemaphores(Index)++
#define CanTp_IncTxState(Index)                                                                     CanTp_GetTxState(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  CanTpPCDecrementDataMacros  CanTp Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define CanTp_DecCalcBS(Index)                                                                      CanTp_GetCalcBS(Index)--
#define CanTp_DecRxState(Index)                                                                     CanTp_GetRxState(Index)--
#define CanTp_DecTxSemaphores(Index)                                                                CanTp_GetTxSemaphores(Index)--
#define CanTp_DecTxState(Index)                                                                     CanTp_GetTxState(Index)--
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

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanTpLTDataSwitches  CanTp Data Switches  (LINK)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CANTP_LTCONFIG                                                                              STD_OFF  /**< Deactivateable: 'CanTp_LTConfig' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
/** 
  \}
*/ 


/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanTpPBDataSwitches  CanTp Data Switches  (POST_BUILD)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CANTP_PBCONFIG                                                                              STD_OFF  /**< Deactivateable: 'CanTp_PBConfig' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define CANTP_LTCONFIGIDXOFPBCONFIG                                                                 STD_OFF  /**< Deactivateable: 'CanTp_PBConfig.LTConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define CANTP_PCCONFIGIDXOFPBCONFIG                                                                 STD_OFF  /**< Deactivateable: 'CanTp_PBConfig.PCConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
/** 
  \}
*/ 


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


#endif /* CANTP_CFG_H */
