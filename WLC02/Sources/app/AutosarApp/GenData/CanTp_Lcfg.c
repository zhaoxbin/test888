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
 *              File: CanTp_Lcfg.c
 *   Generation Time: 2020-03-24 15:59:26
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

#define CANTP_LCFG_SOURCE

/* -----------------------------------------------------------------------------
    &&&~ Include files
 ----------------------------------------------------------------------------- */

#include "CanTp_Lcfg.h"
#if (CANTP_LOLAYER_CANIF == STD_ON)
# include "CanIf.h"
#endif
#include "PduR_CanTp.h"
/* -----------------------------------------------------------------------------
    &&&~ Data definitions
 ----------------------------------------------------------------------------- */



/**********************************************************************************************************************
 *  LOCAL DATA
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
 *  GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CanTp_RxPduMap
**********************************************************************************************************************/
/** 
  \var    CanTp_RxPduMap
  \details
  Element                Description
  RxSduCfgIndEndIdx      the end index of the 0:n relation pointing to CanTp_RxSduCfgInd
  RxSduCfgIndStartIdx    the start index of the 0:n relation pointing to CanTp_RxSduCfgInd
  TxSduCfgIndEndIdx      the end index of the 0:n relation pointing to CanTp_TxSduCfgInd
  TxSduCfgIndStartIdx    the start index of the 0:n relation pointing to CanTp_TxSduCfgInd
*/ 
#define CANTP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanTp_RxPduMapType, CANTP_CONST) CanTp_RxPduMap[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxSduCfgIndEndIdx  RxSduCfgIndStartIdx  TxSduCfgIndEndIdx                     TxSduCfgIndStartIdx                    */
  { /*     0 */                1u,                  0u,                                   1u,                                     0u },
  { /*     1 */                2u,                  1u,                                   2u,                                     1u },
  { /*     2 */                3u,                  2u,                                   3u,                                     2u },
  { /*     3 */                4u,                  3u,                                   4u,                                     3u },
  { /*     4 */                5u,                  4u, CANTP_NO_TXSDUCFGINDENDIDXOFRXPDUMAP, CANTP_NO_TXSDUCFGINDSTARTIDXOFRXPDUMAP }
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTp_RxSduCfg
**********************************************************************************************************************/
/** 
  \var    CanTp_RxSduCfg
  \details
  Element                     Description
  LoLayerTxFcPduId        
  PduRRxSduId             
  RxPduId                 
  TxFcPduConfirmationPduId
  NAr                     
  NBr                     
  NCr                     
  RxTaType                
  STmin                   
  TxSduCfgIdx                 the index of the 0:1 relation pointing to CanTp_TxSduCfg
*/ 
#define CANTP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanTp_RxSduCfgType, CANTP_CONST) CanTp_RxSduCfg[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    LoLayerTxFcPduId                                                              PduRRxSduId                              RxPduId                                     TxFcPduConfirmationPduId                        NAr  NBr  NCr  RxTaType                             STmin  TxSduCfgIdx                           Comment                            Referable Keys */
  { /*     0 */ CanIfConf_CanIfTxPduCfg_WLC_DEVLP_01_oNIO_ES6_RF_CAN_SR_V3_0_163e9779_Tx    , PduRConf_PduRSrcPdu_PduRSrcPdu_5       , CanTpConf_CanTpRxNPdu_CanTpRxNPdu_2       , CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu_002     , 15u, 14u, 31u,   CANTP_PHYSICAL_RXTATYPEOFRXSDUCFG,   20u,                             0u },  /* [CanTpRxNSdu_002]      */  /* [CanTpRxNSdu_002, 3] */
  { /*     1 */ CANTP_INVALID_HDL                                                           , PduRConf_PduRSrcPdu_PduRSrcPdu_392782f6, CanTpConf_CanTpRxNPdu_CanTpRxNPdu_210b33f5, CANTP_INVALID_HDL                             , 11u, 21u, 11u, CANTP_FUNCTIONAL_RXTATYPEOFRXSDUCFG,    0u, CANTP_NO_TXSDUCFGIDXOFRXSDUCFG },  /* [CanTpRxNSdu_585bdea6] */  /* [CanTpRxNSdu_585bdea6, 4] */
  { /*     2 */ CanIfConf_CanIfTxPduCfg_WLC_CDC_NFC_oNIO_ES6_RF_CAN_SR_V3_0_f65364a2_Tx     , PduRConf_PduRSrcPdu_PduRSrcPdu         , CanTpConf_CanTpRxNPdu_CanTpRxNPdu         , CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu         , 15u, 14u, 31u,   CANTP_PHYSICAL_RXTATYPEOFRXSDUCFG,   20u,                             1u },  /* [CanTpRxNSdu]          */  /* [CanTpRxNSdu, 0] */
  { /*     3 */ CanIfConf_CanIfTxPduCfg_IMOB_WLC_CGW_oNIO_ES6_RF_CAN_SR_V3_0_4f44c7a2_Tx    , PduRConf_PduRSrcPdu_PduRSrcPdu_1       , CanTpConf_CanTpRxNPdu_CanTpRxNPdu_1       , CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu_001     , 15u, 14u, 31u,   CANTP_PHYSICAL_RXTATYPEOFRXSDUCFG,   20u,                             2u },  /* [CanTpRxNSdu_001]      */  /* [CanTpRxNSdu_001, 2] */
  { /*     4 */ CanIfConf_CanIfTxPduCfg_DIAG_RESP_WLC_Tp_oNIO_ES6_RF_CAN_SR_V3_0_00ce42fa_Tx, PduRConf_PduRSrcPdu_PduRSrcPdu_eddf36be, CanTpConf_CanTpRxNPdu_CanTpRxNPdu_9b5d64b0, CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu_9b5d64b0, 15u, 14u, 31u,   CANTP_PHYSICAL_RXTATYPEOFRXSDUCFG,   20u,                             3u }   /* [CanTpRxNSdu_fab217f5] */  /* [CanTpRxNSdu_fab217f5, 1] */
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTp_RxSduCfgInd
**********************************************************************************************************************/
/** 
  \var    CanTp_RxSduCfgInd
  \brief  the indexes of the 1:1 sorted relation pointing to CanTp_RxSduCfg
*/ 
#define CANTP_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanTp_RxSduCfgIndType, CANTP_CONST) CanTp_RxSduCfgInd[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RxSduCfgInd      Referable Keys */
  /*     0 */           2u,  /* [0] */
  /*     1 */           4u,  /* [1] */
  /*     2 */           3u,  /* [2] */
  /*     3 */           0u,  /* [3] */
  /*     4 */           1u   /* [4] */
};
#define CANTP_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTp_RxSduSnv2Hdl
**********************************************************************************************************************/
/** 
  \var    CanTp_RxSduSnv2Hdl
  \details
  Element        Description
  RxSduCfgIdx    the index of the 0:1 relation pointing to CanTp_RxSduCfg
*/ 
#define CANTP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanTp_RxSduSnv2HdlType, CANTP_CONST) CanTp_RxSduSnv2Hdl[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxSduCfgIdx        Comment */
  { /*     0 */          0u },  /* [CanTpRxNSdu_002] */
  { /*     1 */          1u },  /* [CanTpRxNSdu_585bdea6] */
  { /*     2 */          2u },  /* [CanTpRxNSdu] */
  { /*     3 */          3u },  /* [CanTpRxNSdu_001] */
  { /*     4 */          4u }   /* [CanTpRxNSdu_fab217f5] */
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTp_TxSduCfg
**********************************************************************************************************************/
/** 
  \var    CanTp_TxSduCfg
  \details
  Element                   Description
  LoLayerTxPduId        
  PduRTxSduId           
  RxFcPduId             
  TxPduConfirmationPduId
  RxSduCfgIdx               the index of the 0:1 relation pointing to CanTp_RxSduCfg
*/ 
#define CANTP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanTp_TxSduCfgType, CANTP_CONST) CanTp_TxSduCfg[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    LoLayerTxPduId                                                                PduRTxSduId                                                             RxFcPduId                                       TxPduConfirmationPduId                      RxSduCfgIdx        Comment                            Referable Keys */
  { /*     0 */ CanIfConf_CanIfTxPduCfg_WLC_DEVLP_01_oNIO_ES6_RF_CAN_SR_V3_0_163e9779_Tx    , PduRConf_PduRDestPdu_PduRDestPdu_4                                    , CanTpConf_CanTpRxFcNPdu_CanTpRxFcNPdu_001     , CanTpConf_CanTpTxNPdu_CanTpTxNPdu_2       ,          0u },  /* [CanTpTxNSdu_002]      */  /* [CanTpTxNSdu_002, 3] */
  { /*     1 */ CanIfConf_CanIfTxPduCfg_WLC_CDC_NFC_oNIO_ES6_RF_CAN_SR_V3_0_f65364a2_Tx     , PduRConf_PduRDestPdu_PduRDestPdu_3                                    , CanTpConf_CanTpRxFcNPdu_CanTpRxFcNPdu         , CanTpConf_CanTpTxNPdu_CanTpTxNPdu         ,          2u },  /* [CanTpTxNSdu]          */  /* [CanTpTxNSdu, 0] */
  { /*     2 */ CanIfConf_CanIfTxPduCfg_IMOB_WLC_CGW_oNIO_ES6_RF_CAN_SR_V3_0_4f44c7a2_Tx    , PduRConf_PduRDestPdu_PduRDestPdu_2                                    , CanTpConf_CanTpRxFcNPdu_CanTpRxFcNPdu_01      , CanTpConf_CanTpTxNPdu_CanTpTxNPdu_1       ,          3u },  /* [CanTpTxNSdu_001]      */  /* [CanTpTxNSdu_001, 2] */
  { /*     3 */ CanIfConf_CanIfTxPduCfg_DIAG_RESP_WLC_Tp_oNIO_ES6_RF_CAN_SR_V3_0_00ce42fa_Tx, PduRConf_PduRDestPdu_DIAG_RESP_WLC_oNIO_ES6_RF_CAN_SR_V3_0_ebfde8b0_Tx, CanTpConf_CanTpRxFcNPdu_CanTpRxFcNPdu_b9a7b042, CanTpConf_CanTpTxNPdu_CanTpTxNPdu_b9a7b042,          4u }   /* [CanTpTxNSdu_fab217f5] */  /* [CanTpTxNSdu_fab217f5, 1] */
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTp_TxSduCfgInd
**********************************************************************************************************************/
/** 
  \var    CanTp_TxSduCfgInd
  \brief  the indexes of the 1:1 sorted relation pointing to CanTp_TxSduCfg
*/ 
#define CANTP_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanTp_TxSduCfgIndType, CANTP_CONST) CanTp_TxSduCfgInd[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     TxSduCfgInd      Referable Keys */
  /*     0 */           1u,  /* [0] */
  /*     1 */           3u,  /* [1] */
  /*     2 */           2u,  /* [2] */
  /*     3 */           0u   /* [3] */
};
#define CANTP_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTp_TxSduSnv2Hdl
**********************************************************************************************************************/
/** 
  \var    CanTp_TxSduSnv2Hdl
  \details
  Element        Description
  TxSduCfgIdx    the index of the 0:1 relation pointing to CanTp_TxSduCfg
*/ 
#define CANTP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(CanTp_TxSduSnv2HdlType, CANTP_CONST) CanTp_TxSduSnv2Hdl[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxSduCfgIdx        Comment */
  { /*     0 */          0u },  /* [CanTpTxNSdu_002] */
  { /*     1 */          1u },  /* [CanTpTxNSdu] */
  { /*     2 */          2u },  /* [CanTpTxNSdu_001] */
  { /*     3 */          3u }   /* [CanTpTxNSdu_fab217f5] */
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTp_CalcBS
**********************************************************************************************************************/
#define CANTP_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(CanTp_CalcBSType, CANTP_VAR_NOINIT) CanTp_CalcBS[5];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define CANTP_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTp_RxState
**********************************************************************************************************************/
#define CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(CanTp_RxStateType, CANTP_VAR_NOINIT) CanTp_RxState[5];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTp_TxSemaphores
**********************************************************************************************************************/
#define CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(CanTp_TxSemaphoreType, CANTP_VAR_NOINIT) CanTp_TxSemaphores[4];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTp_TxState
**********************************************************************************************************************/
#define CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(CanTp_TxStateType, CANTP_VAR_NOINIT) CanTp_TxState[4];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
 * FUNCTIONS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/




