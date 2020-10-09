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
 *              File: PduR_Lcfg.c
 *   Generation Time: 2020-09-01 20:49:57
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

#define PDUR_LCFG_SOURCE

/**********************************************************************************************************************
 * MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_Fm.h"
#include "PduR_IFQ.h"
#include "PduR_Sm.h"
#include "PduR_RmIf.h"
#include "PduR_RmTp.h"
#include "PduR_RmTp_TxInst.h"
#include "SchM_PduR.h"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/* Include headers with callbacks */
#include "PduR_CanIf.h"
#include "PduR_CanNm.h"
#include "PduR_CanTp.h"
#include "PduR_Com.h"
#include "PduR_Dcm.h"
#include "PduR_Cdd.h"


/**********************************************************************************************************************
 * LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/* Exclusive Area Wrapper functions */
static FUNC(void, PDUR_CODE) PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0(void);
static FUNC(void, PDUR_CODE) PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0(void);
  
/**********************************************************************************************************************
 * LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL DATA
 *********************************************************************************************************************/
/* \trace SPEC-663, SPEC-661 */

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  PduR_ExclusiveAreaRom
**********************************************************************************************************************/
/** 
  \var    PduR_ExclusiveAreaRom
  \brief  PduR Exclusive Area Locks
  \details
  Element    Description
  Lock       Lock function
  Unlock     Unlock function
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_ExclusiveAreaRomType, PDUR_CONST) PduR_ExclusiveAreaRom[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Lock                                        Unlock                                           Referable Keys */
  { /*     0 */ PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0, PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0 }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRLock_PduRExclusiveArea] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_MmRom
**********************************************************************************************************************/
/** 
  \var    PduR_MmRom
  \brief  Module manager: Contains all function pointers of the bordering modules.
  \details
  Element                       Description
  CoreManagerRomIdx             the index of the 1:1 relation pointing to PduR_CoreManagerRom
  MaskedBits                    contains bitcoded the boolean data of PduR_LoIfOfMmRom, PduR_LoTpOfMmRom, PduR_RmGDestRomUsedOfMmRom, PduR_UpIfOfMmRom, PduR_UpTpOfMmRom
  RmGDestRomEndIdx              the end index of the 0:n relation pointing to PduR_RmGDestRom
  RmGDestRomStartIdx            the start index of the 0:n relation pointing to PduR_RmGDestRom
  UpTpCopyRxDataFctPtr          Transport protocol CopyRxData function pointers
  UpTpCopyTxDataFctPtr          Transport protocol CopyTxData function pointers
  UpIfRxIndicationFctPtr        Upper layer communication interface Rx indication function pointers.
  UpIfTxConfirmationFctPtr      Upper layer communication interface Tx confimation function pointers
  UpTpStartOfReceptionFctPtr    Transport protocol StartOfReception function pointers
  UpTpTpRxIndicationFctPtr      Transport protocol TpRxIndication function pointers
  UpTpTpTxConfirmationFctPtr    Transport protocol TpTxConfimation function pointers
  LoIfTransmitFctPtr            Lower layer If transmit function pointers
  LoTpTransmitFctPtr            Lower layer Tp transmit function pointers
  UpIfTriggerTransmitFctPtr     Upper layer trigger transmit function pointers
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_MmRomType, PDUR_CONST) PduR_MmRom[6] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    CoreManagerRomIdx  MaskedBits  RmGDestRomEndIdx  RmGDestRomStartIdx  UpTpCopyRxDataFctPtr  UpTpCopyTxDataFctPtr  UpIfRxIndicationFctPtr  UpIfTxConfirmationFctPtr  UpTpStartOfReceptionFctPtr  UpTpTpRxIndicationFctPtr  UpTpTpTxConfirmationFctPtr  LoIfTransmitFctPtr  LoTpTransmitFctPtr  UpIfTriggerTransmitFctPtr        Comment                        Referable Keys */
  { /*     0 */                0u,      0x14u,               2u,                 0u, NULL_PTR            , NULL_PTR            , NULL_PTR              , NULL_PTR                , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , CanIf_Transmit    , NULL_PTR          , NULL_PTR                  },  /* [BswModule: CanIf] */  /* [/ActiveEcuC/PduR/CanIf, /ActiveEcuC/PduR] */
  { /*     1 */                0u,      0x14u,               3u,                 2u, NULL_PTR            , NULL_PTR            , NULL_PTR              , NULL_PTR                , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , CanNm_Transmit    , NULL_PTR          , NULL_PTR                  },  /* [BswModule: CanNm] */  /* [/ActiveEcuC/PduR/CanNm, /ActiveEcuC/PduR] */
  { /*     2 */                0u,      0x0Cu,               7u,                 3u, NULL_PTR            , NULL_PTR            , NULL_PTR              , NULL_PTR                , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , NULL_PTR          , CanTp_Transmit    , NULL_PTR                  },  /* [BswModule: CanTp] */  /* [/ActiveEcuC/PduR/CanTp, /ActiveEcuC/PduR] */
  { /*     3 */                0u,      0x05u,              10u,                 7u, Cdd_CopyRxData      , Cdd_CopyTxData      , NULL_PTR              , NULL_PTR                , Cdd_StartOfReception      , Cdd_TpRxIndication      , Cdd_TpTxConfirmation      , NULL_PTR          , NULL_PTR          , NULL_PTR                  },  /* [BswModule: Cdd]   */  /* [/ActiveEcuC/PduR/Cdd, /ActiveEcuC/PduR] */
  { /*     4 */                0u,      0x06u,              17u,                10u, NULL_PTR            , NULL_PTR            , Com_RxIndication      , Com_TxConfirmation      , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , NULL_PTR          , NULL_PTR          , Com_TriggerTransmit       },  /* [BswModule: Com]   */  /* [/ActiveEcuC/PduR/Com, /ActiveEcuC/PduR] */
  { /*     5 */                0u,      0x05u,              19u,                17u, Dcm_CopyRxData      , Dcm_CopyTxData      , NULL_PTR              , NULL_PTR                , Dcm_StartOfReception      , Dcm_TpRxIndication      , Dcm_TpTxConfirmation      , NULL_PTR          , NULL_PTR          , NULL_PTR                  }   /* [BswModule: Dcm]   */  /* [/ActiveEcuC/PduR/Dcm, /ActiveEcuC/PduR] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmDestRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmDestRom
  \brief  PduR RoutiongPathManager destPdu Table
  \details
  Element          Description
  RmGDestRomIdx    the index of the 1:1 relation pointing to PduR_RmGDestRom
  RmSrcRomIdx      the index of the 1:1 relation pointing to PduR_RmSrcRom
  RoutingType      Type of the Routing (API Forwarding, Gateway).
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmDestRomType, PDUR_CONST) PduR_RmDestRom[19] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RmGDestRomIdx  RmSrcRomIdx  RoutingType                                                 Comment                                                                                    Referable Keys */
  { /*     0 */            7u,          7u, PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu]                                                     */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CDC_WLC_NFC_CDDroute_RX/PduRSrcPdu, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CDC_WLC_NFC_CDDroute_RX/PduRDestPdu] */
  { /*     1 */            8u,         10u, PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_1]                                                   */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/IMOB_CGW_WLC_PduRRoutingPath/PduRSrcPdu_1, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/IMOB_CGW_WLC_PduRRoutingPath/PduRDestPdu_1] */
  { /*     2 */            1u,         16u, PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_60d6e62c_Tx]                      */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_3e708b41_Tx/PduRSrcPdu_19a519a0, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_3e708b41_Tx/WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_60d6e62c_Tx] */
  { /*     3 */            4u,         13u, PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_2]                                                   */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/IMOB_WLC_CGW_oNIO_ES6_RF_CAN/PduRSrcPdu_2, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/IMOB_WLC_CGW_oNIO_ES6_RF_CAN/PduRDestPdu_2] */
  { /*     4 */            0u,         15u, PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_49299080_Tx]                      */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_0b9d3d12_Tx/PduRSrcPdu_2f5fea6f, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_0b9d3d12_Tx/WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_49299080_Tx] */
  { /*     5 */            5u,         17u, PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_3]                                                   */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_CDC_NFC_oNIO_ES6_RF_CAN_PduRRoutingPath_Tx/PduRSrcPdu_3, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_CDC_NFC_oNIO_ES6_RF_CAN_PduRRoutingPath_Tx/PduRDestPdu_3] */
  { /*     6 */           17u,          8u, PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: DIAG_REQ_AllECU_oNIO_ES6_RF_CAN_SR_V3_0_5b04e722_Rx_392782f6_Rx] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DIAG_REQ_AllECU_oNIO_ES6_RF_CAN_SR_V3_0_5b04e722_Rx/PduRSrcPdu_392782f6, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DIAG_REQ_AllECU_oNIO_ES6_RF_CAN_SR_V3_0_5b04e722_Rx/DIAG_REQ_AllECU_oNIO_ES6_RF_CAN_SR_V3_0_5b04e722_Rx_392782f6_Rx] */
  { /*     7 */           10u,          0u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: BCU_04_oNIO_ES6_RF_CAN_SR_V3_0_b06c3b94_Rx_3ec2fcac_Rx]          */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/BCU_04_oNIO_ES6_RF_CAN_SR_V3_0_b06c3b94_Rx/PduRSrcPdu_3ec2fcac, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/BCU_04_oNIO_ES6_RF_CAN_SR_V3_0_b06c3b94_Rx/BCU_04_oNIO_ES6_RF_CAN_SR_V3_0_b06c3b94_Rx_3ec2fcac_Rx] */
  { /*     8 */           11u,          1u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: CDC_IC_01_oNIO_ES6_RF_CAN_SR_V3_0_7ab33239_Rx_3feaaad3_Rx]       */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CDC_IC_01_oNIO_ES6_RF_CAN_SR_V3_0_7ab33239_Rx/PduRSrcPdu_3feaaad3, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CDC_IC_01_oNIO_ES6_RF_CAN_SR_V3_0_7ab33239_Rx/CDC_IC_01_oNIO_ES6_RF_CAN_SR_V3_0_7ab33239_Rx_3feaaad3_Rx] */
  { /*     9 */            6u,         18u, PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_4]                                                   */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_DEVLP_01_oNIO_ES6_RF_CAN_PduRRoutingPath/PduRSrcPdu_4, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_DEVLP_01_oNIO_ES6_RF_CAN_PduRRoutingPath/PduRDestPdu_4] */
  { /*    10 */            9u,         11u, PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_5]                                                   */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_DEVLP_02_oNIO_ES6_RF_CAN_PduRRoutingPath/PduRSrcPdu_5, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_DEVLP_02_oNIO_ES6_RF_CAN_PduRRoutingPath/PduRDestPdu_5] */
  { /*    11 */           16u,          6u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: CGW_WLC_oNIO_ES6_RF_CAN_SR_V3_0_57df1db7_Rx_8b01a8ad_Rx]         */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_WLC_oNIO_ES6_RF_CAN_SR_V3_0_57df1db7_Rx/PduRSrcPdu_8b01a8ad, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_WLC_oNIO_ES6_RF_CAN_SR_V3_0_57df1db7_Rx/CGW_WLC_oNIO_ES6_RF_CAN_SR_V3_0_57df1db7_Rx_8b01a8ad_Rx] */
  { /*    12 */           12u,          2u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: CDC_WLC_oNIO_ES6_RF_CAN_SR_V3_0_cbd6c32f_Rx_8b049bb0_Rx]         */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CDC_WLC_oNIO_ES6_RF_CAN_SR_V3_0_cbd6c32f_Rx/PduRSrcPdu_8b049bb0, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CDC_WLC_oNIO_ES6_RF_CAN_SR_V3_0_cbd6c32f_Rx/CDC_WLC_oNIO_ES6_RF_CAN_SR_V3_0_cbd6c32f_Rx_8b049bb0_Rx] */
  { /*    13 */           14u,          4u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: CGW_03_oNIO_ES6_RF_CAN_SR_V3_0_2fb1cd3a_Rx_8f6b5f25_Rx]          */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_03_oNIO_ES6_RF_CAN_SR_V3_0_2fb1cd3a_Rx/PduRSrcPdu_8f6b5f25, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_03_oNIO_ES6_RF_CAN_SR_V3_0_2fb1cd3a_Rx/CGW_03_oNIO_ES6_RF_CAN_SR_V3_0_2fb1cd3a_Rx_8f6b5f25_Rx] */
  { /*    14 */            2u,         14u, PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx_9febb8af_Tx]          */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx/PduRSrcPdu_9febb8af, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx/NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx_9febb8af_Tx] */
  { /*    15 */            3u,         12u, PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: DIAG_RESP_WLC_oNIO_ES6_RF_CAN_SR_V3_0_ebfde8b0_Tx]               */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DIAG_RESP_WLC_oNIO_ES6_RF_CAN_SR_V3_0_7db09b81_Tx/PduRSrcPdu_cd65fdce, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DIAG_RESP_WLC_oNIO_ES6_RF_CAN_SR_V3_0_7db09b81_Tx/DIAG_RESP_WLC_oNIO_ES6_RF_CAN_SR_V3_0_ebfde8b0_Tx] */
  { /*    16 */           15u,          5u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: CGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_9e3e6b3d_Rx_ece35bb2_Rx]      */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_9e3e6b3d_Rx/PduRSrcPdu_ece35bb2, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_9e3e6b3d_Rx/CGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_9e3e6b3d_Rx_ece35bb2_Rx] */
  { /*    17 */           18u,          9u, PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: DIAG_REQ_WLC_oNIO_ES6_RF_CAN_SR_V3_0_af2d88ff_Rx_eddf36be_Rx]    */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DIAG_REQ_WLC_oNIO_ES6_RF_CAN_SR_V3_0_af2d88ff_Rx/PduRSrcPdu_eddf36be, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DIAG_REQ_WLC_oNIO_ES6_RF_CAN_SR_V3_0_af2d88ff_Rx/DIAG_REQ_WLC_oNIO_ES6_RF_CAN_SR_V3_0_af2d88ff_Rx_eddf36be_Rx] */
  { /*    18 */           13u,          3u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM }   /* [PduRDestPdu: CGW_02_oNIO_ES6_RF_CAN_SR_V3_0_371b1f5e_Rx_f115c878_Rx]          */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_02_oNIO_ES6_RF_CAN_SR_V3_0_371b1f5e_Rx/PduRSrcPdu_f115c878, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_02_oNIO_ES6_RF_CAN_SR_V3_0_371b1f5e_Rx/CGW_02_oNIO_ES6_RF_CAN_SR_V3_0_371b1f5e_Rx_f115c878_Rx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmGDestRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmGDestRom
  \brief  PduR RoutiongPathManager global destPdu Table
  \details
  Element                  Description
  DestHnd                  handle to be used as parameter for the StartOfReception, CopyRxData, Transmit or RxIndication function call.
  Direction                Direction of this Pdu: Rx or Tx
  MmRomIdx                 the index of the 1:1 relation pointing to PduR_MmRom
  PduRDestPduProcessing    Is Processing Type of destination PDU.
  RmDestRomIdx             the index of the 0:1 relation pointing to PduR_RmDestRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmGDestRomType, PDUR_CONST) PduR_RmGDestRom[19] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    DestHnd                                                                                Direction                      MmRomIdx  PduRDestPduProcessing                             RmDestRomIdx        Comment                                                                                Referable Keys */
  { /*     0 */                    CanIfConf_CanIfTxPduCfg_WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_1dd10da5_Tx, PDUR_TX_DIRECTIONOFRMGDESTROM,       0u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,           4u },  /* [Globale PduRDestPdu: WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_49299080_Tx]          */  /* [/ActiveEcuC/EcuC/EcucPduCollection/WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_49299080_Tx, /ActiveEcuC/PduR/CanIf] */
  { /*     1 */                    CanIfConf_CanIfTxPduCfg_WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_adb4aee2_Tx, PDUR_TX_DIRECTIONOFRMGDESTROM,       0u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,           2u },  /* [Globale PduRDestPdu: WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_60d6e62c_Tx]          */  /* [/ActiveEcuC/EcuC/EcucPduCollection/WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_60d6e62c_Tx, /ActiveEcuC/PduR/CanIf] */
  { /*     2 */                  CanNmConf_CanNmUserDataTxPdu_NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_fd222ddc, PDUR_TX_DIRECTIONOFRMGDESTROM,       1u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,          14u },  /* [Globale PduRDestPdu: NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx]          */  /* [/ActiveEcuC/EcuC/EcucPduCollection/NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx, /ActiveEcuC/PduR/CanNm] */
  { /*     3 */                                            CanTpConf_CanTpTxNSdu_CanTpTxNSdu_fab217f5, PDUR_TX_DIRECTIONOFRMGDESTROM,       2u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,          15u },  /* [Globale PduRDestPdu: DIAG_RESP_WLC_oNIO_ES6_RF_CAN_SR_V3_0_ebfde8b0_Tx]   */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DIAG_RESP_WLC_oNIO_ES6_RF_CAN_SR_V3_0_ebfde8b0_Tx, /ActiveEcuC/PduR/CanTp] */
  { /*     4 */                                                 CanTpConf_CanTpTxNSdu_CanTpTxNSdu_001, PDUR_TX_DIRECTIONOFRMGDESTROM,       2u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,           3u },  /* [Globale PduRDestPdu: IMOB_WLC_CGW_oNIO_ES6_RF_CAN_CDDAsCanTp_001]         */  /* [/ActiveEcuC/EcuC/EcucPduCollection/IMOB_WLC_CGW_oNIO_ES6_RF_CAN_CDDAsCanTp_001, /ActiveEcuC/PduR/CanTp] */
  { /*     5 */                                                     CanTpConf_CanTpTxNSdu_CanTpTxNSdu, PDUR_TX_DIRECTIONOFRMGDESTROM,       2u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,           5u },  /* [Globale PduRDestPdu: WLC_CDC_NFC_oNIO_ES6_RF_CAN_CDDAsCanTp_001]          */  /* [/ActiveEcuC/EcuC/EcucPduCollection/WLC_CDC_NFC_oNIO_ES6_RF_CAN_CDDAsCanTp_001, /ActiveEcuC/PduR/CanTp] */
  { /*     6 */                                                 CanTpConf_CanTpTxNSdu_CanTpTxNSdu_002, PDUR_TX_DIRECTIONOFRMGDESTROM,       2u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,           9u },  /* [Globale PduRDestPdu: WLC_DEVLP_01_oNIO_ES6_RF_CAN_CDDasCanTp_001]         */  /* [/ActiveEcuC/EcuC/EcucPduCollection/WLC_DEVLP_01_oNIO_ES6_RF_CAN_CDDasCanTp_001, /ActiveEcuC/PduR/CanTp] */
  { /*     7 */                                  CddConf_CddPduRUpperLayerRxPdu_CDC_WLC_NFC_Pdu_CANTP, PDUR_RX_DIRECTIONOFRMGDESTROM,       3u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,           0u },  /* [Globale PduRDestPdu: CDC_WLC_NFC_Pdu_CANTP]                               */  /* [/ActiveEcuC/EcuC/EcucPduCollection/CDC_WLC_NFC_Pdu_CANTP, /ActiveEcuC/PduR/Cdd] */
  { /*     8 */                    CddConf_CddPduRUpperLayerRxPdu_IMOB_CGW_WLC_oNIO_ES6_RF_CDDasCanTp, PDUR_RX_DIRECTIONOFRMGDESTROM,       3u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,           1u },  /* [Globale PduRDestPdu: IMOB_CGW_WLC_oNIO_ES6_RF_CDDasCanTp]                 */  /* [/ActiveEcuC/EcuC/EcucPduCollection/IMOB_CGW_WLC_oNIO_ES6_RF_CDDasCanTp, /ActiveEcuC/PduR/Cdd] */
  { /*     9 */                CddConf_CddPduRUpperLayerRxPdu_WLC_DEVLP_02_oNIO_ES6_RF_CAN_CDDasCanTp, PDUR_RX_DIRECTIONOFRMGDESTROM,       3u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,          10u },  /* [Globale PduRDestPdu: WLC_DEVLP_02_oNIO_ES6_RF_CAN_CDDasCanTp]             */  /* [/ActiveEcuC/EcuC/EcucPduCollection/WLC_DEVLP_02_oNIO_ES6_RF_CAN_CDDasCanTp, /ActiveEcuC/PduR/Cdd] */
  { /*    10 */                            ComConf_ComIPdu_BCU_04_oNIO_ES6_RF_CAN_SR_V3_0_aafda74c_Rx, PDUR_RX_DIRECTIONOFRMGDESTROM,       4u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,           7u },  /* [Globale PduRDestPdu: BCU_04_oNIO_ES6_RF_CAN_SR_V3_0_aafda74c_Rx]          */  /* [/ActiveEcuC/EcuC/EcucPduCollection/BCU_04_oNIO_ES6_RF_CAN_SR_V3_0_aafda74c_Rx, /ActiveEcuC/PduR/Com] */
  { /*    11 */                         ComConf_ComIPdu_CDC_IC_01_oNIO_ES6_RF_CAN_SR_V3_0_d7bf39a5_Rx, PDUR_RX_DIRECTIONOFRMGDESTROM,       4u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,           8u },  /* [Globale PduRDestPdu: CDC_IC_01_oNIO_ES6_RF_CAN_SR_V3_0_d7bf39a5_Rx]       */  /* [/ActiveEcuC/EcuC/EcucPduCollection/CDC_IC_01_oNIO_ES6_RF_CAN_SR_V3_0_d7bf39a5_Rx, /ActiveEcuC/PduR/Com] */
  { /*    12 */                           ComConf_ComIPdu_CDC_WLC_oNIO_ES6_RF_CAN_SR_V3_0_d2878c96_Rx, PDUR_RX_DIRECTIONOFRMGDESTROM,       4u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,          12u },  /* [Globale PduRDestPdu: CDC_WLC_oNIO_ES6_RF_CAN_SR_V3_0_d2878c96_Rx]         */  /* [/ActiveEcuC/EcuC/EcucPduCollection/CDC_WLC_oNIO_ES6_RF_CAN_SR_V3_0_d2878c96_Rx, /ActiveEcuC/PduR/Com] */
  { /*    13 */                            ComConf_ComIPdu_CGW_02_oNIO_ES6_RF_CAN_SR_V3_0_a943b009_Rx, PDUR_RX_DIRECTIONOFRMGDESTROM,       4u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,          18u },  /* [Globale PduRDestPdu: CGW_02_oNIO_ES6_RF_CAN_SR_V3_0_a943b009_Rx]          */  /* [/ActiveEcuC/EcuC/EcucPduCollection/CGW_02_oNIO_ES6_RF_CAN_SR_V3_0_a943b009_Rx, /ActiveEcuC/PduR/Com] */
  { /*    14 */                            ComConf_ComIPdu_CGW_03_oNIO_ES6_RF_CAN_SR_V3_0_0cc82007_Rx, PDUR_RX_DIRECTIONOFRMGDESTROM,       4u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,          13u },  /* [Globale PduRDestPdu: CGW_03_oNIO_ES6_RF_CAN_SR_V3_0_0cc82007_Rx]          */  /* [/ActiveEcuC/EcuC/EcucPduCollection/CGW_03_oNIO_ES6_RF_CAN_SR_V3_0_0cc82007_Rx, /ActiveEcuC/PduR/Com] */
  { /*    15 */                        ComConf_ComIPdu_CGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_49a017d3_Rx, PDUR_RX_DIRECTIONOFRMGDESTROM,       4u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,          16u },  /* [Globale PduRDestPdu: CGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_49a017d3_Rx]      */  /* [/ActiveEcuC/EcuC/EcucPduCollection/CGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_49a017d3_Rx, /ActiveEcuC/PduR/Com] */
  { /*    16 */                           ComConf_ComIPdu_CGW_WLC_oNIO_ES6_RF_CAN_SR_V3_0_4780465a_Rx, PDUR_RX_DIRECTIONOFRMGDESTROM,       4u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,          11u },  /* [Globale PduRDestPdu: CGW_WLC_oNIO_ES6_RF_CAN_SR_V3_0_4780465a_Rx]         */  /* [/ActiveEcuC/EcuC/EcucPduCollection/CGW_WLC_oNIO_ES6_RF_CAN_SR_V3_0_4780465a_Rx, /ActiveEcuC/PduR/Com] */
  { /*    17 */ DcmConf_DcmDslProtocolRx_DIAG_REQ_AllECU_oNIO_ES6_RF_CAN_SR_V3_0_88b0846e_Rx_ec64cedc, PDUR_RX_DIRECTIONOFRMGDESTROM,       5u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,           6u },  /* [Globale PduRDestPdu: DIAG_REQ_AllECU_oNIO_ES6_RF_CAN_SR_V3_0_88b0846e_Rx] */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DIAG_REQ_AllECU_oNIO_ES6_RF_CAN_SR_V3_0_88b0846e_Rx, /ActiveEcuC/PduR/Dcm] */
  { /*    18 */    DcmConf_DcmDslProtocolRx_DIAG_REQ_WLC_oNIO_ES6_RF_CAN_SR_V3_0_499b8fdc_Rx_83001690, PDUR_RX_DIRECTIONOFRMGDESTROM,       5u, PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM,          17u }   /* [Globale PduRDestPdu: DIAG_REQ_WLC_oNIO_ES6_RF_CAN_SR_V3_0_499b8fdc_Rx]    */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DIAG_REQ_WLC_oNIO_ES6_RF_CAN_SR_V3_0_499b8fdc_Rx, /ActiveEcuC/PduR/Dcm] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmSrcRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmSrcRom
  \brief  PduR RoutiongManager SrcPdu Table
  \details
  Element              Description
  MaskedBits           contains bitcoded the boolean data of PduR_TriggerTransmitSupportedOfRmSrcRom, PduR_TxConfirmationSupportedOfRmSrcRom
  MmRomIdx             the index of the 1:1 relation pointing to PduR_MmRom
  RmDestRomLength      the number of relations pointing to PduR_RmDestRom
  RmDestRomStartIdx    the start index of the 1:n relation pointing to PduR_RmDestRom
  SrcHnd               handle to be used as parameter for the TxConfirmation or TriggerTransmit function call.
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmSrcRomType, PDUR_CONST) PduR_RmSrcRom[19] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MaskedBits  MmRomIdx  RmDestRomLength  RmDestRomStartIdx  SrcHnd                                                                                     Comment                                       Referable Keys */
  { /*     0 */      0x00u,       0u,              1u,                7u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_3ec2fcac] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/BCU_04_oNIO_ES6_RF_CAN_SR_V3_0_b06c3b94_Rx/PduRSrcPdu_3ec2fcac] */
  { /*     1 */      0x00u,       0u,              1u,                8u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_3feaaad3] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CDC_IC_01_oNIO_ES6_RF_CAN_SR_V3_0_7ab33239_Rx/PduRSrcPdu_3feaaad3] */
  { /*     2 */      0x00u,       0u,              1u,               12u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_8b049bb0] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CDC_WLC_oNIO_ES6_RF_CAN_SR_V3_0_cbd6c32f_Rx/PduRSrcPdu_8b049bb0] */
  { /*     3 */      0x00u,       0u,              1u,               18u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_f115c878] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_02_oNIO_ES6_RF_CAN_SR_V3_0_371b1f5e_Rx/PduRSrcPdu_f115c878] */
  { /*     4 */      0x00u,       0u,              1u,               13u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_8f6b5f25] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_03_oNIO_ES6_RF_CAN_SR_V3_0_2fb1cd3a_Rx/PduRSrcPdu_8f6b5f25] */
  { /*     5 */      0x00u,       0u,              1u,               16u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_ece35bb2] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_9e3e6b3d_Rx/PduRSrcPdu_ece35bb2] */
  { /*     6 */      0x00u,       0u,              1u,               11u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_8b01a8ad] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CGW_WLC_oNIO_ES6_RF_CAN_SR_V3_0_57df1db7_Rx/PduRSrcPdu_8b01a8ad] */
  { /*     7 */      0x00u,       2u,              1u,                0u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu]          */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/CDC_WLC_NFC_CDDroute_RX/PduRSrcPdu] */
  { /*     8 */      0x00u,       2u,              1u,                6u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_392782f6] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DIAG_REQ_AllECU_oNIO_ES6_RF_CAN_SR_V3_0_5b04e722_Rx/PduRSrcPdu_392782f6] */
  { /*     9 */      0x00u,       2u,              1u,               17u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_eddf36be] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DIAG_REQ_WLC_oNIO_ES6_RF_CAN_SR_V3_0_af2d88ff_Rx/PduRSrcPdu_eddf36be] */
  { /*    10 */      0x00u,       2u,              1u,                1u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_1]        */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/IMOB_CGW_WLC_PduRRoutingPath/PduRSrcPdu_1] */
  { /*    11 */      0x00u,       2u,              1u,               10u,                                                            PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_5]        */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_DEVLP_02_oNIO_ES6_RF_CAN_PduRRoutingPath/PduRSrcPdu_5] */
  { /*    12 */      0x00u,       5u,              1u,               15u, DcmConf_DcmDslProtocolTx_DIAG_RESP_WLC_oNIO_ES6_RF_CAN_SR_V3_0_7db09b81_Tx_237b1533 },  /* [PduRSrcPdu: PduRSrcPdu_cd65fdce] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DIAG_RESP_WLC_oNIO_ES6_RF_CAN_SR_V3_0_7db09b81_Tx/PduRSrcPdu_cd65fdce] */
  { /*    13 */      0x00u,       3u,              1u,                3u,              CddConf_CddPduRUpperLayerTxPdu_IMOB_WLC_CGW_oNIO_ES6_RF_CAN_CDDAsCanTp },  /* [PduRSrcPdu: PduRSrcPdu_2]        */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/IMOB_WLC_CGW_oNIO_ES6_RF_CAN/PduRSrcPdu_2] */
  { /*    14 */      0x02u,       4u,              1u,               14u,                          ComConf_ComIPdu_NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx },  /* [PduRSrcPdu: PduRSrcPdu_9febb8af] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx/PduRSrcPdu_9febb8af] */
  { /*    15 */      0x01u,       4u,              1u,                4u,                          ComConf_ComIPdu_WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_0b9d3d12_Tx },  /* [PduRSrcPdu: PduRSrcPdu_2f5fea6f] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_0b9d3d12_Tx/PduRSrcPdu_2f5fea6f] */
  { /*    16 */      0x01u,       4u,              1u,                2u,                          ComConf_ComIPdu_WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_3e708b41_Tx },  /* [PduRSrcPdu: PduRSrcPdu_19a519a0] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_3e708b41_Tx/PduRSrcPdu_19a519a0] */
  { /*    17 */      0x00u,       3u,              1u,                5u,               CddConf_CddPduRUpperLayerTxPdu_WLC_CDC_NFC_oNIO_ES6_RF_CAN_CDDAsCanTp },  /* [PduRSrcPdu: PduRSrcPdu_3]        */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_CDC_NFC_oNIO_ES6_RF_CAN_PduRRoutingPath_Tx/PduRSrcPdu_3] */
  { /*    18 */      0x00u,       3u,              1u,                9u,              CddConf_CddPduRUpperLayerTxPdu_WLC_DEVLP_01_oNIO_ES6_RF_CAN_CDDasCanTp }   /* [PduRSrcPdu: PduRSrcPdu_4]        */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_DEVLP_01_oNIO_ES6_RF_CAN_PduRRoutingPath/PduRSrcPdu_4] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmTransmitFctPtr
**********************************************************************************************************************/
/** 
  \var    PduR_RmTransmitFctPtr
  \brief  Internal routing manager Transmit functions.
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmTransmitFctPtrType, PDUR_CONST) PduR_RmTransmitFctPtr[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RmTransmitFctPtr                  Referable Keys */
  /*     0 */ PduR_RmIf_RoutePdu           ,  /* [PduR_RmIf_RoutePdu] */
  /*     1 */ PduR_RmTp_Transmit_MultiDest    /* [PduR_RmTp_Transmit_MultiDest] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_Tx2Lo
**********************************************************************************************************************/
/** 
  \var    PduR_Tx2Lo
  \brief  Contains all informations to route a Pdu from a upper layer to a lower layer module, or to cancel a transmission
  \details
  Element                Description
  RmTransmitFctPtrIdx    the index of the 1:1 relation pointing to PduR_RmTransmitFctPtr
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_Tx2LoType, PDUR_CONST) PduR_Tx2Lo[7] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RmTransmitFctPtrIdx        Referable Keys */
  { /*     0 */                  1u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/DIAG_RESP_WLC_oNIO_ES6_RF_CAN_SR_V3_0_7db09b81_Tx/PduRSrcPdu_cd65fdce] */
  { /*     1 */                  1u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/IMOB_WLC_CGW_oNIO_ES6_RF_CAN/PduRSrcPdu_2] */
  { /*     2 */                  0u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx/PduRSrcPdu_9febb8af] */
  { /*     3 */                  0u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_0b9d3d12_Tx/PduRSrcPdu_2f5fea6f] */
  { /*     4 */                  0u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_3e708b41_Tx/PduRSrcPdu_19a519a0] */
  { /*     5 */                  1u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_CDC_NFC_oNIO_ES6_RF_CAN_PduRRoutingPath_Tx/PduRSrcPdu_3] */
  { /*     6 */                  1u }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/WLC_DEVLP_01_oNIO_ES6_RF_CAN_PduRRoutingPath/PduRSrcPdu_4] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_TxIf2Up
**********************************************************************************************************************/
/** 
  \var    PduR_TxIf2Up
  \brief  This table contains all routing information to perform the Tx handling of an interface routing. Used in the &lt;LLIf&gt;_TriggerTransmit and &lt;LLIf&gt;_TxConfirmation
  \details
  Element          Description
  RmGDestRomIdx    the index of the 1:1 relation pointing to PduR_RmGDestRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_TxIf2UpType, PDUR_CONST) PduR_TxIf2Up[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RmGDestRomIdx        Referable Keys */
  { /*     0 */            2u },  /* [/ActiveEcuC/EcuC/EcucPduCollection/NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx] */
  { /*     1 */            0u },  /* [/ActiveEcuC/EcuC/EcucPduCollection/WLC_01_oNIO_ES6_RF_CAN_SR_V3_0_49299080_Tx] */
  { /*     2 */            1u }   /* [/ActiveEcuC/EcuC/EcucPduCollection/WLC_02_oNIO_ES6_RF_CAN_SR_V3_0_60d6e62c_Tx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_Initialized
**********************************************************************************************************************/
/** 
  \var    PduR_Initialized
  \brief  Initialization state of PduR. TRUE, if PduR_Init() has been called, else FALSE
*/ 
#define PDUR_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(PduR_InitializedType, PDUR_VAR_ZERO_INIT) PduR_Initialized = FALSE;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define PDUR_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/


#define PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if(PDUR_USE_INIT_POINTER == STD_ON)
P2CONST(PduR_PBConfigType, PDUR_VAR_ZERO_INIT, PDUR_PBCFG) PduR_ConfigDataPtr = (const PduR_PBConfigType *) NULL_PTR;
#endif

#define PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */
  
/**********************************************************************************************************************
 * LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/
#define PDUR_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "MemMap.h"

/* Exclusive Area Wrapper functions */

/**********************************************************************************************************************
 * PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0
 *********************************************************************************************************************/
/*!
 * \internal
 * -  enter the EA  
 * \endinternal
 *********************************************************************************************************************/
static FUNC(void, PDUR_CODE) PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0(void)
{
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
}


/**********************************************************************************************************************
 * PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0
 *********************************************************************************************************************/
/*!
 * \internal
 * -  exit the EA  
 * \endinternal
 *********************************************************************************************************************/
static FUNC(void, PDUR_CODE) PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0(void)
{
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();
}


/* Upper Layer Interface APIs */

/**********************************************************************************************************************
 * PduR_ComTransmit
 *********************************************************************************************************************/
/*!
 * \internal
 * - call upper layer Transmit function. 
 * \endinternal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_ComTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
  Std_ReturnType retVal = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if (PDUR_TX2LO == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_UpTransmit(id, info); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_TX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}


/**********************************************************************************************************************
 * PduR_DcmTransmit
 *********************************************************************************************************************/
/*!
 * \internal
 * - call upper layer Transmit function. 
 * \endinternal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
  Std_ReturnType retVal = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if (PDUR_TX2LO == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_UpTransmit(id, info); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_TX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}


/**********************************************************************************************************************
 * PduR_CddTransmit
 *********************************************************************************************************************/
/*!
 * \internal
 * - call upper layer Transmit function. 
 * \endinternal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_CddTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
  Std_ReturnType retVal = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if (PDUR_TX2LO == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_UpTransmit(id, info); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_TX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}


/* Communication Interface APIs */

/**********************************************************************************************************************
 * PduR_CanIfRxIndication
 *********************************************************************************************************************/
/*!
 * \internal
 * -  call internal general IfRxIndication function.  
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanIfRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_RXIF2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  PduR_LoIfRxIndication(RxPduId, info);  /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_IFRXIND, PDUR_E_PDU_ID_INVALID);
#endif
  PDUR_DUMMY_STATEMENT(RxPduId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}


/**********************************************************************************************************************
 * PduR_CanIfTxConfirmation
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general communication interface TxConfirmation function.
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanIfTxConfirmation(PduIdType TxPduId) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)
  PduR_LoIfTxConfirmation(TxPduId);
#endif
  PDUR_DUMMY_STATEMENT(TxPduId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}



/**********************************************************************************************************************
 * PduR_CanNmRxIndication
 *********************************************************************************************************************/
/*!
 * \internal
 * -  call internal general IfRxIndication function.  
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanNmRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_RXIF2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  PduR_LoIfRxIndication(RxPduId, info);  /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_IFRXIND, PDUR_E_PDU_ID_INVALID);
#endif
  PDUR_DUMMY_STATEMENT(RxPduId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}



/**********************************************************************************************************************
 * PduR_CanNmTriggerTransmit
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general TriggerTransmit function.  
 * \endinternal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_CanNmTriggerTransmit(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  return PduR_LoIfTriggerTransmit(TxPduId, info); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
}


/* Transport Protocol APIs */

/**********************************************************************************************************************
 * PduR_CanTpStartOfReception
 *********************************************************************************************************************/
 /*!
 * \internal
 * - call transport protocoll StartOfReception function.  
 * \endinternal
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpStartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr) /* COV_PDUR_WRAPPER_FUNC */
{
  // BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
	BufReq_ReturnType retVal = BUFREQ_OK;
#if (PDUR_RXTP2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_LoTpStartOfReception(id, info, TpSduLength, bufferSizePtr); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_SOR, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(TpSduLength);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}


/**********************************************************************************************************************
 * PduR_CanTpCopyRxData
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general CopyRxData.
 * \endinternal
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr) /* COV_PDUR_WRAPPER_FUNC */
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if (PDUR_RXTP2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_LoTpCopyRxData(id, info, bufferSizePtr); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_CPYRX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);  			/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  
  return retVal;
}


/**********************************************************************************************************************
 * PduR_CanTpCopyTxData
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general CopyTxData.
 * \endinternal
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr) /* COV_PDUR_WRAPPER_FUNC */
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if(PDUR_TXTP2SRC == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_LoTpCopyTxData(id, info, retry, availableDataPtr); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_CPYTX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     				/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);  					/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(retry);  				/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(availableDataPtr);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  
  return retVal;
}


/**********************************************************************************************************************
 * PduR_CanTpRxIndication
 *********************************************************************************************************************/
/*!
 * \internal
 * - call Tp RxIndication function.
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanTpRxIndication(PduIdType id, Std_ReturnType result) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_RXTP2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  PduR_LoTpRxIndication(id, result);
#else
  PduR_Det_ReportError(PDUR_FCT_TPRXIND, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}


/**********************************************************************************************************************
 * PduR_CanTpTxConfirmation
 *********************************************************************************************************************/
/*!
 * \internal
 * - call Tp TxConfirmation function 
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanTpTxConfirmation(PduIdType id, Std_ReturnType result) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_TXTP2SRC == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  PduR_LoTpTxConfirmation(id, result);
#else
  PduR_Det_ReportError(PDUR_FCT_TPTXCFM, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}


/* CancelReceive global without UseTag API */

/* ChangeParameter global without UseTag  API */

/* Communication Interface / Transport Protocol APIs */

/* Communication Interface / Transport Protocol APIs */

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/


#define PDUR_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "MemMap.h"

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR
    \DESCRIPTION    The API is called with an Id and a pointer.
                    The API call is forwarded using a function pointer which is read using ComStackLib macros.
                    
    \COUNTERMEASURE \N The function pointer is read using the passed Id (and ComStackLib macros). 
                       The Id is a SNV provided by the lower layer. 
                       It is checked at runtime if it is in the valid range.
                       The pointer is provided by the lower layer and is assumed to be valid. It is passed as is to the corresponding function. 

  \ID SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_ONLY
    \DESCRIPTION    The API is called with an Id.
                    The API call is forwarded using a function pointer which is read using ComStackLib macros.
                    
    \COUNTERMEASURE \R The function pointer is read using the passed Id (and ComStackLib macros). 
                       The Id is a SNV provided by the lower layer. 
                       It is checked at runtime if it is in the valid range.
                       
  \ID SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY
    \DESCRIPTION    The API call is forwarded to an internal function.
    \COUNTERMEASURE \N The parameter are checked in the called function.

 SBSW_JUSTIFICATION_END */
 
 /* COV_JUSTIFICATION_BEGIN
 
  \ID COV_PDUR_WRAPPER_FUNC
    \ACCEPT X
    \REASON Each neighbouring module call the same internal function. The call is covered by an other module. 
    
  \ID COV_PDUR_RX_OR_TX_ONLY_CONFIG
    \ACCEPT TX
    \REASON The API is mandatory if this Bsw module exists. In case of Rx or Tx only configs the API call is not forwarded to the internal function. 
 
 COV_JUSTIFICATION_END */
 

/**********************************************************************************************************************
 * END OF FILE: PduR_Lcfg.c
 *********************************************************************************************************************/

