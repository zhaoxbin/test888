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
 *            Module: PduR
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: PduR_Cfg.h
 *   Generation Time: 2020-02-04 16:15:32
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

#if !defined (PDUR_CFG_H)
# define PDUR_CFG_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR_Types.h"

/**********************************************************************************************************************
 * GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#ifndef PDUR_USE_DUMMY_STATEMENT
#define PDUR_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/EcuC/EcucGeneral/DummyStatement */
#endif
#ifndef PDUR_DUMMY_STATEMENT
#define PDUR_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef PDUR_DUMMY_STATEMENT_CONST
#define PDUR_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef PDUR_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define PDUR_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef PDUR_ATOMIC_VARIABLE_ACCESS
#define PDUR_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef PDUR_PROCESSOR_RH850_1649
#define PDUR_PROCESSOR_RH850_1649
#endif
#ifndef PDUR_COMP_GREENHILLS
#define PDUR_COMP_GREENHILLS
#endif
#ifndef PDUR_GEN_GENERATOR_MSR
#define PDUR_GEN_GENERATOR_MSR
#endif
#ifndef PDUR_CPUTYPE_BITORDER_LSB2MSB
#define PDUR_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef PDUR_CONFIGURATION_VARIANT_PRECOMPILE
#define PDUR_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef PDUR_CONFIGURATION_VARIANT_LINKTIME
#define PDUR_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef PDUR_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define PDUR_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef PDUR_CONFIGURATION_VARIANT
#define PDUR_CONFIGURATION_VARIANT PDUR_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef PDUR_POSTBUILD_VARIANT_SUPPORT
#define PDUR_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif



#define PDUR_DEV_ERROR_DETECT STD_OFF  /**< /ActiveEcuC/PduR/PduRGeneral[0:PduRSafeBswChecks] || /ActiveEcuC/PduR/PduRGeneral[0:PduRDevErrorDetect] */
#define PDUR_DEV_ERROR_REPORT STD_OFF  /**< /ActiveEcuC/PduR/PduRGeneral[0:PduRDevErrorDetect] */

#define PDUR_METADATA_SUPPORT STD_OFF  /**< /ActiveEcuC/PduR/PduRGeneral[0:PduRMetaDataSupport] */
#define PDUR_VERSION_INFO_API STD_ON  /**< /ActiveEcuC/PduR/PduRGeneral[0:PduRVersionInfoApi] */

#define PDUR_ERROR_NOTIFICATION STD_OFF

#define PDUR_MAIN_FUNCTION STD_OFF

#define PDUR_MULTICORE STD_OFF /**< /ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] */

#define PduR_PBConfigIdType uint32

 
 /*  DET Error define list  */ 
#define PDUR_FCT_CANIFRXIND 0x01u 
#define PDUR_FCT_CANIFTX 0x09u 
#define PDUR_FCT_CANIFTXCFM 0x02u 
#define PDUR_FCT_CANNMRXIND 0x11u 
#define PDUR_FCT_CANNMTX 0x19u 
#define PDUR_FCT_CANNMTXCFM 0x12u 
#define PDUR_FCT_CANNMTT 0x13u 
#define PDUR_FCT_CANTPRXIND 0x05u 
#define PDUR_FCT_CANTPTX 0x09u 
#define PDUR_FCT_CANTPTXCFM 0x08u 
#define PDUR_FCT_CANTPSOR 0x06u 
#define PDUR_FCT_CANTPCPYRX 0x04u 
#define PDUR_FCT_CANTPCPYTX 0x07u 
#define PDUR_FCT_COMTX 0x89u 
#define PDUR_FCT_DCMTX 0x99u 
#define PDUR_FCT_CDDTX 0xC9u 
 /*   PduR_CanIfIfRxIndication  PduR_CanIfTransmit  PduR_CanIfTxConfirmation  PduR_CanNmIfRxIndication  PduR_CanNmTransmit  PduR_CanNmTxConfirmation  PduR_CanNmTriggerTransmit  PduR_CanTpTpRxIndication  PduR_CanTpTransmit  PduR_CanTpTxConfirmation  PduR_CanTpStartOfReception  PduR_CanTpCopyRxData  PduR_CanTpCopyTxData  PduR_ComTransmit  PduR_DcmTransmit  PduR_CddTransmit  */ 



/**
 * \defgroup PduRHandleIdsIfRxDest Handle IDs of handle space IfRxDest.
 * \brief Communication interface Rx destination PDUs
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define PduRConf_PduRDestPdu_BCU_04_oNIO_ES6_RF_CAN_SR_V3_0_b06c3b94_Rx_3ec2fcac_Rx 0u
#define PduRConf_PduRDestPdu_CDC_IC_01_oNIO_ES6_RF_CAN_SR_V3_0_7ab33239_Rx_3feaaad3_Rx 1u
#define PduRConf_PduRDestPdu_CDC_WLC_oNIO_ES6_RF_CAN_SR_V3_0_cbd6c32f_Rx_8b049bb0_Rx 2u
#define PduRConf_PduRDestPdu_CGW_02_oNIO_ES6_RF_CAN_SR_V3_0_371b1f5e_Rx_f115c878_Rx 3u
#define PduRConf_PduRDestPdu_CGW_03_oNIO_ES6_RF_CAN_SR_V3_0_2fb1cd3a_Rx_8f6b5f25_Rx 4u
#define PduRConf_PduRDestPdu_CGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_9e3e6b3d_Rx_ece35bb2_Rx 5u
#define PduRConf_PduRDestPdu_CGW_WLC_oNIO_ES6_RF_CAN_SR_V3_0_57df1db7_Rx_8b01a8ad_Rx 6u
/**\} */

/**
 * \defgroup PduRHandleIdsIfRxSrc Handle IDs of handle space IfRxSrc.
 * \brief Communication interface Rx source PDUs
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define PduRConf_PduRSrcPdu_PduRSrcPdu_3ec2fcac                       0u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_3feaaad3                       1u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_8b01a8ad                       6u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_8b049bb0                       2u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_8f6b5f25                       4u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_ece35bb2                       5u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_f115c878                       3u
/**\} */

/**
 * \defgroup PduRHandleIdsIfTpTxSrc Handle IDs of handle space IfTpTxSrc.
 * \brief Communication interface and transport protocol Tx PDUs
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define PduRConf_PduRSrcPdu_PduRSrcPdu_2                              1u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_2f5fea6f                       3u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_3                              5u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_4                              6u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_9febb8af                       2u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_19a519a0                       4u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_cd65fdce                       0u
/**\} */

/**
 * \defgroup PduRHandleIdsIfTxDest Handle IDs of handle space IfTxDest.
 * \brief Communication interface Tx destination PDUs
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define PduRConf_PduRDestPdu_NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx_9febb8af_Tx 0u
#define PduRConf_PduRDestPdu_WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_49299080_Tx 1u
#define PduRConf_PduRDestPdu_WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_60d6e62c_Tx 2u
/**\} */

/**
 * \defgroup PduRHandleIdsTpRxDest Handle IDs of handle space TpRxDest.
 * \brief Transport protocol Rx destination PDUs
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define PduRConf_PduRDestPdu_DIAG_REQ_AllECU_oNIO_ES6_RF_CAN_SR_V3_0_5b04e722_Rx_392782f6_Rx 1u
#define PduRConf_PduRDestPdu_DIAG_REQ_WLC_oNIO_ES6_RF_CAN_SR_V3_0_af2d88ff_Rx_eddf36be_Rx 2u
#define PduRConf_PduRDestPdu_PduRDestPdu                              0u
#define PduRConf_PduRDestPdu_PduRDestPdu_1                            3u
#define PduRConf_PduRDestPdu_PduRDestPdu_5                            4u
/**\} */

/**
 * \defgroup PduRHandleIdsTpRxSrc Handle IDs of handle space TpRxSrc.
 * \brief Transport protocol Rx source PDUs
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define PduRConf_PduRSrcPdu_PduRSrcPdu                                0u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_1                              3u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_5                              4u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_392782f6                       1u
#define PduRConf_PduRSrcPdu_PduRSrcPdu_eddf36be                       2u
/**\} */

/**
 * \defgroup PduRHandleIdsTpTxDest Handle IDs of handle space TpTxDest.
 * \brief Transport protocol Tx PDUs
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define PduRConf_PduRDestPdu_DIAG_RESP_WLC_oNIO_ES6_RF_CAN_SR_V3_0_ebfde8b0_Tx 0u
#define PduRConf_PduRDestPdu_PduRDestPdu_2                            1u
#define PduRConf_PduRDestPdu_PduRDestPdu_3                            2u
#define PduRConf_PduRDestPdu_PduRDestPdu_4                            3u
/**\} */


/* User Config File Start */

/* User Config File End */


/**********************************************************************************************************************
 * GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif  /* PDUR_CFG_H */
/**********************************************************************************************************************
 * END OF FILE: PduR_Cfg.h
 *********************************************************************************************************************/

