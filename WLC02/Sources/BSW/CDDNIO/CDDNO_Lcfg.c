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
 *            Module: CDD
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CDD_Lcfg.c
 *   Generation Time: 2020-02-07 22:17:22
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



#define CDD_LCFG_SOURCE
/* ----------------------------------------------
 ~&&&   Includes
---------------------------------------------- */
                                                                                                                                                     /* PRQA S 1533 EOF */ /* MD_CDD_ObjectOnlyAccessedOnce */
#include "CDDNIO.h"
#include "PduR_CDD.h"
/* ----------------------------------------------
 ~&&&   Defines
---------------------------------------------- */
#if (CDD_DIDMGR_NVM_READ_ENABLED == STD_ON) || \
    (CDD_DIDMGR_NVM_WRITE_ENABLED == STD_ON)
# if defined(NVM_VENDOR_ID)
#  if (NVM_VENDOR_ID == 30u)
/* Only Vector NvM supports this feature up to now */
#   define CDD_GetCDDNvMBlockId(blockId)                             (uint16)(NvM_GetCDDBlockId(blockId))                                            /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro */ /* Macro is more efficient! */
#  endif
# endif

/* Default NvM handle offset */
# if !defined(CDD_GetCDDNvMBlockId)
#  define CDD_GetCDDNvMBlockId(blockId)                              (uint16)(blockId)                                                               /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro */ /* Macro is more efficient! */
# endif
#endif
/* ----------------------------------------------
 ~&&&   Call-back function declarations
---------------------------------------------- */
#define CDD_START_SEC_CALLOUT_CODE
/*! CDD protocol descriptor */
CDDNIO_LOCAL VAR(CDD_MsgItemType, CDD_VAR_NOINIT) CDD_CfgNetBuffer_000[2200];
#define CDD_STOP_SEC_VAR_NO_INIT_8
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*! TxPduId to CDD connection map */
CONST(CDD_NetConnRefMemType, CDD_CONST) CDD_CfgNetTxPduInfo[1]=
{
    0u
};
/*! Map of CDD relevant network handles */
CONST(CDD_CfgNetNetIdRefMemType, CDD_CONST) CDD_CfgNetConnComMChannelMap[1]=
{
    0u
};
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CDD_CfgNetBufferInfoType, CDD_CONST) CDD_CfgNetBufferInfo[1]=
{
   { CDD_CfgNetBuffer_000, 300u}
};
/*! RxPduId map */
CONST(CDD_CfgNetRxPduInfoType, CDD_CONST) CDD_CfgNetRxPduInfo[2]=
{
   { TRUE, 0u}
  ,{ FALSE, 0u}
};
/*! CDD connection descriptor */
CONST(CDD_CfgNetConnectionInfoType, CDD_CONST) CDD_CfgNetConnectionInfo[1]=
{
   { 0x0000u,0, 0u,0u}
};
/*! CDD protocol descriptor */
CONST(CDD_CfgNetProtocolInfoType, CDD_CONST) CDD_CfgNetProtocolInfo[1]=
{
   { {    0u,   0u},4095u, 3u,TRUE,0u,0, 0u}
};
/*! Map of all relevant for CDD network handles */
/*! DID operation properties */

/*! DID operation classes */

/*! DID signal operation classes */
CONST(CDD_CfgDidMgrSignalOpClassInfoType, CDD_CONST) CDD_CfgDidMgrSignalOpClassInfo[2]=
{
   { ((CDD_DidMgrOpFuncType)(WLC_Value_SetDatatoCGW))} /* DID: 0x1000 */ /* PRQA S 0313 */ /* MD_CDD_0313 */
  ,{ ((CDD_DidMgrOpFuncType)(WLC_Value_GetDatafromCGW))} /* DID: 0x1000 */ /* PRQA S 0313 */ /* MD_CDD_0313 */
};

/*lint -restore */
/* ********************************************************************************************************************
 * END OF FILE: CDD_Lcfg.c
 * ******************************************************************************************************************** */

