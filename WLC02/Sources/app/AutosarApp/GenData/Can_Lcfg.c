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
 *            Module: Can
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Can_Lcfg.c
 *   Generation Time: 2020-06-20 15:53:45
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
 * [Warning] CAN02002 - An invalid value is configured 
 * - [Reduced Severity due to User-Defined Parameter] CanBaudrateClock has to be set according to CanCpuClockRef and hardware settings.
 * Erroneous configuration elements:
 * /ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593/CanControllerBaudrateConfig[0:CanBaudrateClock](value=40000) (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanController/CanControllerBaudrateConfig/CanBaudrateClock)
 *********************************************************************************************************************/

#define CAN_LCFG_SOURCE

/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2 */

/* -----------------------------------------------------------------------------
    Includes
 ----------------------------------------------------------------------------- */

#include "Can_Cfg.h"

/* -----------------------------------------------------------------------------
    Hw specific
 ----------------------------------------------------------------------------- */


/**********************************************************************************************************************
  ComStackLib
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
  Can_CanIfChannelId
**********************************************************************************************************************/
/** 
  \var    Can_CanIfChannelId
  \brief  indirection table Can to CanIf controller ID
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_CanIfChannelIdType, CAN_CONST) Can_CanIfChannelId[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     CanIfChannelId      Comment */
  /*     0 */              0u   /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593] */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_ChannelData
**********************************************************************************************************************/
/** 
  \var    Can_ChannelData
  \brief  Controller specific information
  \details
  Element           Description
  FifoProcCount     Maximum number FIFO messages processed per event
  FrStartIndex      Start index of used receive rules (FullCAN + BasicCAN)
  FrTotalCount      Number of used receive rules (FullCAN + BasicCAN)
  RxBcMask          Bitmask of Rx BasicCAN objects (receive FIFO buffer 7-0)
  RxBcStartIndex    Start index of used receive FIFO buffers
  RxBcStopIndex     Stop index of used receive FIFO buffers
  TxIntMask         Bitmask of Tx interrupt objects (local transmit buffer 31-0)
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_ChannelDataType, CAN_CONST) Can_ChannelData[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    FifoProcCount  FrStartIndex  FrTotalCount  RxBcMask  RxBcStartIndex  RxBcStopIndex  TxIntMask        Comment */
  { /*     0 */          255u,           0u,           1u,    0x01u,             0u,            1u,     0x01u }   /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_ControllerConfig
**********************************************************************************************************************/
/** 
  \var    Can_ControllerConfig
  \brief  Global configuration for all controllers
  \details
  Element                            Description
  CanControllerDefaultBaudrate   
  CanControllerDefaultBaudrateIdx
  MailboxRxBasicEndIdx               the end index of the 0:n relation pointing to Can_Mailbox
  MailboxRxBasicLength               the number of relations pointing to Can_Mailbox
  MailboxRxBasicStartIdx             the start index of the 0:n relation pointing to Can_Mailbox
  MailboxTxBasicEndIdx               the end index of the 0:n relation pointing to Can_Mailbox
  MailboxTxBasicLength               the number of relations pointing to Can_Mailbox
  MailboxTxBasicStartIdx             the start index of the 0:n relation pointing to Can_Mailbox
  RxBasicHwStart                 
  RxBasicHwStop                  
  RxFullHwStart                  
  RxFullHwStop                   
  TxBasicHwStart                 
  TxBasicHwStop                  
  TxFullHwStart                  
  TxFullHwStop                   
  UnusedHwStart                  
  UnusedHwStop                   
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_ControllerConfigType, CAN_CONST) Can_ControllerConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    CanControllerDefaultBaudrate  CanControllerDefaultBaudrateIdx  MailboxRxBasicEndIdx                                                                                                                                                         MailboxRxBasicLength                                                                                                                                                         MailboxRxBasicStartIdx                                                                                                                                                         MailboxTxBasicEndIdx                                                                                                                                                         MailboxTxBasicLength                                                                                                                                                         MailboxTxBasicStartIdx                                                                                                                                                         RxBasicHwStart  RxBasicHwStop  RxFullHwStart  RxFullHwStop  TxBasicHwStart  TxBasicHwStop  TxFullHwStart  TxFullHwStop  UnusedHwStart  UnusedHwStop        Comment                                          Referable Keys */
  { /*     0 */                         500u,                              0u,                   2u  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanController) */,                   1u  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanController) */,                     1u  /* RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanController) */,                   1u  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanController) */,                   1u  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanController) */,                     0u  /* TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanController) */,             0u,            1u,            1u,           1u,             0u,            1u,            1u,           1u,            0u,           0u }   /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593] */  /* [/ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitFilterRules
**********************************************************************************************************************/
/** 
  \var    Can_InitFilterRules
  \brief  Rx BasicCAN acceptance filters
  \details
  Element    Description
  Code       Initialization value for the receive rule ID register
  Mask       Initialization value for the receive rule mask register
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitFilterRulesType, CAN_CONST) Can_InitFilterRules[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Code   Mask         Comment */
  { /*     0 */ 0x00u, 0x00u }   /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - CanFilterMask (CN_NIO_ES6_RF_CAN_SR_V3_0_91fc07e0_Rx)] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectBaudrate
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectBaudrate
  \brief  baudrates ('InitStruct' as index)
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitObjectBaudrateType, CAN_CONST) Can_InitObjectBaudrate[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     InitObjectBaudrate      Comment */
  /*     0 */                500u   /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - CanControllerBaudrateConfig] */
};
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectBitTiming
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectBitTiming
  \brief  Initialization values for the channel nominal bit rate configuration registers
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitObjectBitTimingType, CAN_CONST) Can_InitObjectBitTiming[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     InitObjectBitTiming      Comment */
  /*     0 */          0x030A1804u   /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - CanControllerBaudrateConfig] */
};
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectBitTimingData
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectBitTimingData
  \brief  Initialization values for the channel data bit rate configuration registers
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitObjectBitTimingDataType, CAN_CONST) Can_InitObjectBitTimingData[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     InitObjectBitTimingData      Comment */
  /*     0 */              0x033A0004u   /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - CanControllerBaudrateConfig - dummy entry] */
};
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectCanFdConfig
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectCanFdConfig
  \brief  Initialization values for the channel CAN FD configuration registers
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitObjectCanFdConfigType, CAN_CONST) Can_InitObjectCanFdConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     InitObjectCanFdConfig      Comment */
  /*     0 */            0x40000000u   /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - CanControllerBaudrateConfig - dummy entry] */
};
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectStartIndex
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectStartIndex
  \brief  Start index of 'InitStruct' / baudratesets (controllers as index)
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_InitObjectStartIndexType, CAN_CONST) Can_InitObjectStartIndex[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     InitObjectStartIndex      Comment */
  /*     0 */                    0u,  /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593] */
  /*     1 */                    1u   /* [stop index] */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_Mailbox
**********************************************************************************************************************/
/** 
  \var    Can_Mailbox
  \brief  mailbox configuration (over all controllers)
  \details
  Element                Description
  ActiveSendObject   
  ControllerConfigIdx    the index of the 1:1 relation pointing to Can_ControllerConfig
  HwHandle           
  IDValue            
  MailboxSize        
  MailboxType        
  MaxDataLen         
  MemorySectionsIndex
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_MailboxType, CAN_CONST) Can_Mailbox[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    ActiveSendObject  ControllerConfigIdx                                                                         HwHandle  IDValue  MailboxSize  MailboxType                                MaxDataLen  MemorySectionsIndex        Comment                                             Referable Keys */
  { /*     0 */               0u,                  0u  /* /ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 */,       0u,   0x00u,          1u, CAN_TX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX,        64u,                  0u },  /* [CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_Tx] */  /* [/ActiveEcuC/Can/CanConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_Tx (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanHardwareObject), /ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593, TX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanController)] */
  { /*     1 */               0u,                  0u  /* /ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 */,       0u,   0x00u,          4u, CAN_RX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX,         8u,                 32u }   /* [CN_NIO_ES6_RF_CAN_SR_V3_0_91fc07e0_Rx] */  /* [/ActiveEcuC/Can/CanConfigSet/CN_NIO_ES6_RF_CAN_SR_V3_0_91fc07e0_Rx (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanHardwareObject), /ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593, RX_BASICCAN_TYPE/ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanController)] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_MemorySectionInfo
**********************************************************************************************************************/
/** 
  \var    Can_MemorySectionInfo
  \brief  Memory section description
  \details
  Element               Description
  MemorySectionStart
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_MemorySectionInfoType, CAN_CONST) Can_MemorySectionInfo[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MemorySectionStart        Comment */
  { /*     0 */                 0u }   /* [MemorySection: TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_MemorySectionObjects
**********************************************************************************************************************/
/** 
  \var    Can_MemorySectionObjects
  \brief  Memory section objects description
  \details
  Element           Description
  HwHandle      
  MailboxElement
  MailboxHandle 
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_MemorySectionObjectsType, CAN_CONST) Can_MemorySectionObjects[32] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    HwHandle  MailboxElement  MailboxHandle        Comment */
  { /*     0 */       0u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_Tx] */
  { /*     1 */       1u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*     2 */       2u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*     3 */       3u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*     4 */       4u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*     5 */       5u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*     6 */       6u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*     7 */       7u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*     8 */       8u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*     9 */       9u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    10 */      10u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    11 */      11u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    12 */      12u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    13 */      13u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    14 */      14u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    15 */      15u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    16 */      16u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    17 */      17u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    18 */      18u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    19 */      19u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    20 */      20u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    21 */      21u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    22 */      22u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    23 */      23u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    24 */      24u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    25 */      25u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    26 */      26u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    27 */      27u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    28 */      28u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    29 */      29u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    30 */      30u,             0u,            0u },  /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
  { /*    31 */      31u,             0u,            0u }   /* [TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - Reserved] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_OsIsrId
**********************************************************************************************************************/
/** 
  \var    Can_OsIsrId
  \brief  OS ISR IDs of the the channel specific interrupts
  \details
  Element        Description
  IsrStatusId    Status ISR ID
  IsrTxId        Tx ISR ID
  IsrWakeupId    Wakeup ISR ID
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_OsIsrIdType, CAN_CONST) Can_OsIsrId[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    IsrStatusId     IsrTxId     IsrWakeupId           Comment */
 // { /*     0 */ CanIsrStatus_0, CanIsrTx_0, CanIsrWakeup_0 }   /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_RxFifoData
**********************************************************************************************************************/
/** 
  \var    Can_RxFifoData
  \brief  Rx BasicCan FIFO specific information
  \details
  Element             Description
  Controller          Logical index of the controller the FIFO is used on
  FifoDepth           Initialization value for the depth of the FIFO buffer
  FilterStartIndex    Start index for filters in Can_InitFilterRules
  FilterStopIndex     Stop index for filters in Can_InitFilterRules
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_RxFifoDataType, CAN_CONST) Can_RxFifoData[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Controller  FifoDepth  FilterStartIndex  FilterStopIndex        Comment */
  { /*     0 */         0u,     0x01u,               0u,              1u }   /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 - CN_NIO_ES6_RF_CAN_SR_V3_0_91fc07e0_Rx] */
};
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_WakeupSourceRef
**********************************************************************************************************************/
/** 
  \var    Can_WakeupSourceRef
  \brief  wakeup Source for channel
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Can_WakeupSourceRefType, CAN_CONST) Can_WakeupSourceRef[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     WakeupSourceRef      Comment */
  /*     0 */              32u   /* [CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593] */
};
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_ActiveSendObject
**********************************************************************************************************************/
/** 
  \var    Can_ActiveSendObject
  \brief  temporary data for TX object
  \details
  Element    Description
  State      send state like cancelled or send activ
  Pdu        buffered PduId for confirmation or cancellation
*/ 
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Can_ActiveSendObjectType, CAN_VAR_NOINIT) Can_ActiveSendObject[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_ControllerData
**********************************************************************************************************************/
/** 
  \var    Can_ControllerData
  \brief  struct for all controller related variable data
  \details
  Element                      Description
  BusOffCounter                Counter to determine forced busoff recovery
  BusOffTransitionRequest      CAN state request for each controller: ContinueBusOffRecovery=0x00, FinishBusOffRecovery=0x01
  CanInterruptCounter          CAN interrupt disable counter for each controller
  IsBusOff                     CAN state for each controller: busoff occur
  IsWakeup                     CAN state for each controller: wakeup occur
  LastInitObject               last set baudrate for reinit
  LogStatus                    CAN state for each controller: UNINIT=0x00, START=0x01, STOP=0x02, INIT=0x04, INCONSISTENT=0x08, WARNING =0x10, PASSIVE=0x20, BUSOFF=0x40, SLEEP=0x80
  ModeTransitionRequest        CAN state request for each controller: INIT=0x00, SLEEP=0x01, WAKEUP=0x02, STOP+INIT=0x03, START=0x04, START+INIT=0x05, NONE=0x06
  RamCheckTransitionRequest    CAN state request for each controller: kCanSuppressRamCheck=0x01, kCanExecuteRamCheck=0x00
  CanInterruptOldStatus        last CAN interrupt status for restore interrupt for each controller
  LoopTimeout                  hw loop timeout for each controller
  RxTmpBuf                     Temporary buffer for received messages
*/ 
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Can_ControllerDataType, CAN_VAR_NOINIT) Can_ControllerData[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/




