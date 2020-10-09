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
 *              File: CanNm_Cfg.c
 *   Generation Time: 2020-09-25 15:12:53
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


#define CANNM_CFG_SOURCE

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2_0779 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "CanNm_Cfg.h"

#include "PduR_Cfg.h"

#include "CanIf_Cfg.h"

#include "Nm.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
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
  GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
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
CONST(CanNm_ChannelConfigType, CANNM_CONST) CanNm_ChannelConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RepeatMessageTime  ComControlEnabled  NodeDetectionEnabled  NodeIdEnabled  ChannelId                                                  ImmediateNmCycleTime  ImmediateNmTransmissions  MsgCycleTime  MsgTimeoutTime  PduCbvPosition    PduNidPosition    RemoteSleepIndTime  TimeoutTime  WaitBusSleepTime        Referable Keys */
  { /*     0 */              345u,              TRUE,                 TRUE,          TRUE, NmConf_NmChannelConfig_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f,                   5u,                       5u,          64u,             6u, CANNM_PDU_BYTE_1, CANNM_PDU_BYTE_0,                 0u,        200u,             201u }   /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */
};
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
CONST(CanNm_PbChannelConfigType, CANNM_CONST) CanNm_PbChannelConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MsgCycleOffset  NodeId  RxMessageDataEndIdx  RxMessageDataLength  RxMessageDataStartIdx  RxMessageData_CBVIdx  RxMessageData_NIDIdx  RxMessageData_UserDataEndIdx  RxMessageData_UserDataLength  RxMessageData_UserDataStartIdx  TxMessageDataEndIdx  TxMessageDataLength  TxMessageDataStartIdx  TxMessageData_CBVIdx  TxMessageData_NIDIdx  TxMessageData_UserDataEndIdx  TxMessageData_UserDataLength  TxMessageData_UserDataStartIdx  TxPduId                                                             TxUserDataPduId                                                                    Referable Keys */
  { /*     0 */             0u,    56u,                  8u,                  8u,                    0u,                   1u,                   0u,                           8u,                           6u,                             2u,                  8u,                  8u,                    0u,                   1u,                   0u,                           8u,                           6u,                             2u, CanIfConf_CanIfTxPduCfg_NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_76bbfea6_Tx, PduRConf_PduRDestPdu_NM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9357dd65_Tx_9febb8af_Tx }   /* [/ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d] */
};
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
CONST(CanNm_SysToNmChIndType, CANNM_CONST) CanNm_SysToNmChInd[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     SysToNmChInd  */
  /*     0 */            0u
};
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
VAR(CanNm_CommStateUType, CANNM_VAR_NOINIT) CanNm_CommState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_CoordReadyToSleepStateUType, CANNM_VAR_NOINIT) CanNm_CoordReadyToSleepState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_ImmediateNmMsgCountUType, CANNM_VAR_NOINIT) CanNm_ImmediateNmMsgCount;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_MsgConfirmationFlagUType, CANNM_VAR_NOINIT) CanNm_MsgConfirmationFlag;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_MsgIndicationFlagUType, CANNM_VAR_NOINIT) CanNm_MsgIndicationFlag;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_MsgRequestUType, CANNM_VAR_NOINIT) CanNm_MsgRequest;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_MsgTimeoutTimerUType, CANNM_VAR_NOINIT) CanNm_MsgTimeoutTimer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_MsgTimerUType, CANNM_VAR_NOINIT) CanNm_MsgTimer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_NetworkRestartFlagUType, CANNM_VAR_NOINIT) CanNm_NetworkRestartFlag;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_NmStateUType, CANNM_VAR_NOINIT) CanNm_NmState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_RepeatMsgBitIndFlagUType, CANNM_VAR_NOINIT) CanNm_RepeatMsgBitIndFlag;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_RepeatMsgReqFlagUType, CANNM_VAR_NOINIT) CanNm_RepeatMsgReqFlag;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_RepeatMsgTimerUType, CANNM_VAR_NOINIT) CanNm_RepeatMsgTimer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_RxMessageDataType, CANNM_VAR_NOINIT) CanNm_RxMessageData[8];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d, /ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d_NID] */
  /*     1 */  /* [/ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d, /ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d_CBV] */
  /*     2 */  /* [/ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d, /ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d_UserData] */
  /*   ... */  /* [/ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d, /ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d_UserData] */
  /*     7 */  /* [/ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d, /ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d_UserData] */

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
VAR(CanNm_TimeoutTimerUType, CANNM_VAR_NOINIT) CanNm_TimeoutTimer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_TxControlStateUType, CANNM_VAR_NOINIT) CanNm_TxControlState;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_TxControlStateRequestUType, CANNM_VAR_NOINIT) CanNm_TxControlStateRequest;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

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
VAR(CanNm_TxMessageDataType, CANNM_VAR_NOINIT) CanNm_TxMessageData[8];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d, /ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d_NID] */
  /*     1 */  /* [/ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d, /ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d_CBV] */
  /*     2 */  /* [/ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d, /ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d_UserData] */
  /*   ... */  /* [/ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d, /ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d_UserData] */
  /*     7 */  /* [/ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d, /ActiveEcuC/CanNm/CanNmGlobalConfig/NIO_ES6_RF_CAN_SR_V3_0_CAN_40361c2d_UserData] */

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
VAR(CanNm_WaitBusSleepTimerUType, CANNM_VAR_NOINIT) CanNm_WaitBusSleepTimer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/ComM/ComMConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f] */

#define CANNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



/**********************************************************************************************************************
  END OF FILE: CanNm_Cfg.c
**********************************************************************************************************************/

