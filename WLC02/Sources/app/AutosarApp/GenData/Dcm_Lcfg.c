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
 *            Module: Dcm
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Dcm_Lcfg.c
 *   Generation Time: 2020-09-27 09:06:39
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



#define DCM_LCFG_SOURCE
/* ----------------------------------------------
 ~&&&   Includes
---------------------------------------------- */
                                                                                                                                                     /* PRQA S 1533 EOF */ /* MD_Dcm_ObjectOnlyAccessedOnce */
#include "Dcm.h"
#include "Rte_Dcm.h"
#include "Dcm_Int.h"
#include "PduR_Dcm.h"
#include "ComM_Dcm.h"
/* ----------------------------------------------
 ~&&&   Defines
---------------------------------------------- */
#if (DCM_DIDMGR_NVM_READ_ENABLED == STD_ON) || \
    (DCM_DIDMGR_NVM_WRITE_ENABLED == STD_ON)
# if defined(NVM_VENDOR_ID)
#  if (NVM_VENDOR_ID == 30u)
/* Only Vector NvM supports this feature up to now */
#   define Dcm_GetDcmNvMBlockId(blockId)                             (uint16)(NvM_GetDcmBlockId(blockId))                                            /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro */ /* Macro is more efficient! */
#  endif
# endif

/* Default NvM handle offset */
# if !defined(Dcm_GetDcmNvMBlockId)
#  define Dcm_GetDcmNvMBlockId(blockId)                              (uint16)(blockId)                                                               /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro */ /* Macro is more efficient! */
# endif
#endif
/* ----------------------------------------------
 ~&&&   Call-back function declarations
---------------------------------------------- */
#define DCM_START_SEC_CALLOUT_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/***********************************************************************************************************************
 *  Dcm_RidMgr_FD04_Start()
***********************************************************************************************************************/
/*! \brief         Wraps RIDs execution interface.
 *  \details       Converts uint8 arrays to other signal types required by the RID execution interface and vice versa.
 *  \param[in]     OpStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *  \param[in,out] DataLength         IN: Concrete length of the dynamic request signal
 *                                    OUT: Concrete length of the dynamic response Signal
 *  \param[out]    ErrorCode          Negative response code
 *  \return        E_OK               The operation is finished
 *  \return        DCM_E_PENDING      The operation is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  Forces a RCR-RP response
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        E_NOT_OK           The operation has failed. A concrete NRC shall be set, otherwise the DCM sends NRC
 *                                    0x22
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_RidMgr_FD04_Start(Dcm_OpStatusType OpStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_RidMgrRidLengthPtrType DataLength, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_ServiceNoPostProcessor()
***********************************************************************************************************************/
/*! \brief         Dummy post-processor
 *  \details       This post-processor is called for diagnostic services which do not require any post processing.
 *  \param[in]     pContext  Pointer to the context
 *  \param[in]     status    The post-processing status
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
DCM_LOCAL FUNC(void, DCM_CALLOUT_CODE) Dcm_ServiceNoPostProcessor(Dcm_ContextPtrType pContext, Dcm_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  Dcm_ServiceNoUpdater()
***********************************************************************************************************************/
/*! \brief         Realizes a dummy paged buffer updater.
 *  \details       This function is never called.
 *  \param[in]     pContext      Pointer to the context
 *  \param[in]     opStatus      The operation status
 *  \param[in,out] pDataContext  Pointer to the data context
 *  \param[out]    ErrorCode     Negative response code
 *  \return        DCM_E_NOT_OK  Operation failed. Take the NRC from ErrorCode. Do not call again
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
DCM_LOCAL FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ServiceNoUpdater(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_DiagDataContextPtrType pDataContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_ServiceNoCancel()
***********************************************************************************************************************/
/*! \brief         Dummy service cancellation.
 *  \details       -
 *  \param[in,out] pDataContext  Pointer to the data context
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
DCM_LOCAL FUNC(void, DCM_CALLOUT_CODE) Dcm_ServiceNoCancel(Dcm_ContextPtrType pContext, Dcm_DiagDataContextPtrType pDataContext);
#define DCM_STOP_SEC_CALLOUT_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   Uninitialized RAM 8-Bit
---------------------------------------------- */
#define DCM_START_SEC_VAR_NO_INIT_8
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*! DCM protocol descriptor */
DCM_LOCAL VAR(Dcm_MsgItemType, DCM_VAR_NOINIT) Dcm_CfgNetBuffer_000[300];
#define DCM_STOP_SEC_VAR_NO_INIT_8
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   ROM 8-Bit
---------------------------------------------- */
#define DCM_START_SEC_CONST_8
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*! TxPduId to DCM connection map */
CONST(Dcm_NetConnRefMemType, DCM_CONST) Dcm_CfgNetTxPduInfo[1]=
{
    0u
};
/*! Map of DCM relevant network handles */
CONST(Dcm_CfgNetNetIdRefMemType, DCM_CONST) Dcm_CfgNetConnComMChannelMap[1]=
{
    0u
};
/*! Service 0x28 list of channels for the all-comm-channel parameter */
CONST(Dcm_CfgNetNetIdRefMemType, DCM_CONST) Dcm_CfgNetComCtrlChannelListAll[2]=
{
   1u
  , 0u
};
/*! Look up table of DCM service identifiers */
CONST(uint8, DCM_CONST) Dcm_CfgDiagSvcIdLookUpTable[12]=
{
   11u
  ,0x10u
  ,0x11u
  ,0x14u
  ,0x19u
  ,0x22u
  ,0x27u
  ,0x28u
  ,0x2Eu
  ,0x31u
  ,0x3Eu
  ,0x85u
};
/*! Service 0x10 look up table  */
CONST(uint8, DCM_CONST) Dcm_CfgSvc10SubFuncLookUpTable[4]=
{
   3u
  ,0x01u
  ,0x02u
  ,0x03u
};
/*! Service 0x11 look up table  */
CONST(uint8, DCM_CONST) Dcm_CfgSvc11SubFuncLookUpTable[3]=
{
   2u
  ,0x01u
  ,0x03u
};
/*! Service 0x19 look up table  */
CONST(uint8, DCM_CONST) Dcm_CfgSvc19SubFuncLookUpTable[5]=
{
   4u
  ,0x01u
  ,0x02u
  ,0x06u
  ,0x0Au
};
/*! Service 0x27 look up table  */
CONST(uint8, DCM_CONST) Dcm_CfgSvc27SubFuncLookUpTable[7]=
{
   6u
  ,0x01u
  ,0x02u
  ,0x03u
  ,0x04u
  ,0x07u
  ,0x08u
};
/*! Service 0x28 look up table  */
CONST(uint8, DCM_CONST) Dcm_CfgSvc28SubFuncLookUpTable[5]=
{
   4u
  ,0x00u
  ,0x01u
  ,0x02u
  ,0x03u
};
/*! Service 0x28 look up table  */
CONST(uint8, DCM_CONST) Dcm_CfgSvc28MessageTypeLookUpTable[4]=
{
   3u
  ,0x01u
  ,0x02u
  ,0x03u
};
/*! Service 0x28 network ID lookup */
CONST(uint8, DCM_CONST) Dcm_CfgSvc28SubNetIdLookUp[3]=
{
   2u
  ,0x00u
  ,0x0Fu
};
/*! Service 0x3E look up table  */
CONST(uint8, DCM_CONST) Dcm_CfgSvc3ESubFuncLookUpTable[2]=
{
   1u
  ,0x00u
};
/*! Look up table of service 0x85 */
CONST(uint8, DCM_CONST) Dcm_CfgSvc85SubFuncLookUpTable[3]=
{
   2u
  ,0x01u
  ,0x02u
};
#define DCM_STOP_SEC_CONST_8
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   ROM 16-Bit
---------------------------------------------- */
#define DCM_START_SEC_CONST_16
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*! DID look up table  */
CONST(uint16, DCM_CONST) Dcm_CfgDidMgrDidLookUpTable[29]=
{
   28u
  ,0x1000u
  ,0x4101u
  ,0xF101u
  ,0xF110u
  ,0xF111u
  ,0xF118u
  ,0xF119u
  ,0xF120u
  ,0xF130u
  ,0xF131u
  ,0xF139u
  ,0xF150u
  ,0xF15Bu
  ,0xF15Cu
  ,0xF186u
  ,0xF187u
  ,0xF18Au
  ,0xF18Bu
  ,0xF18Cu
  ,0xF190u
  ,0xF193u
  ,0xF195u
  ,0xF197u
  ,0xF198u
  ,0xF199u
  ,0xF19Eu
  ,0xFD22u
  ,0xFD30u
};
/*! RID look up table  */
CONST(uint16, DCM_CONST) Dcm_CfgRidMgrRidLookUpTable[3]=
{
   2u
  ,0x0203u
  ,0xFD04u
};
#define DCM_STOP_SEC_CONST_16
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   ROM of unspecified size
---------------------------------------------- */
#define DCM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*! DCM buffer descriptor */
CONST(Dcm_CfgNetBufferInfoType, DCM_CONST) Dcm_CfgNetBufferInfo[1]=
{
   { Dcm_CfgNetBuffer_000, 300u}
};
/*! RxPduId map */
CONST(Dcm_CfgNetRxPduInfoType, DCM_CONST) Dcm_CfgNetRxPduInfo[2]=
{
   { TRUE, 0u}
  ,{ FALSE, 0u}
};
/*! DCM connection descriptor */
CONST(Dcm_CfgNetConnectionInfoType, DCM_CONST) Dcm_CfgNetConnectionInfo[1]=
{
   { 0x0000u,PduRConf_PduRSrcPdu_PduRSrcPdu_cd65fdce, 0u,0u}
};
/*! DCM protocol descriptor */
CONST(Dcm_CfgNetProtocolInfoType, DCM_CONST) Dcm_CfgNetProtocolInfo[1]=
{
   { {    0u,   0u},4095u, 3u,TRUE,0u,DemConf_DemClient_DemClient, 0u}
};
/*! Map of all relevant for DCM network handles */
CONST(NetworkHandleType, DCM_CONST) Dcm_CfgNetAllComMChannelMap[1]=
{
   ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f
};
/*! Look up table of DCM relevant network handles */
CONST(NetworkHandleType, DCM_CONST) Dcm_CfgNetNetworkHandleLookUpTable[2]=
{
   1u
  ,ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f
};
/*! Diagnostic service execution conditions */
CONST(Dcm_CfgStatePreconditionInfoType, DCM_CONST) Dcm_CfgStatePreconditions[9]=
{
   { { 0x07u,0x0Fu}}
  ,{ { 0x06u,0x0Fu}}
  ,{ { 0x05u,0x0Fu}}
  ,{ { 0x04u,0x0Fu}}
  ,{ { 0x02u,0x0Fu}}
  ,{ { 0x05u,0x04u}}
  ,{ { 0x06u,0x02u}}
  ,{ { 0x05u,0x02u}}
  ,{ { 0x04u,0x06u}}
};
/*! Session state properties */
CONST(Dcm_CfgStateSessionInfoType, DCM_CONST) Dcm_CfgStateSessionInfo[3]=
{
   { {    5u, 500u},RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION,0x01u}
  ,{ {    5u, 500u},RTE_MODE_DcmDiagnosticSessionControl_PROGRAMMING_SESSION,0x02u}
  ,{ {    5u, 500u},RTE_MODE_DcmDiagnosticSessionControl_EXTENDED_SESSION,0x03u}
};
/*! Security Access state properties */
CONST(Dcm_CfgStateSecurityInfoType, DCM_CONST) Dcm_CfgStateSecurityInfo[3]=
{
   { 1000u,1000u,   0u,FALSE, 3u,0x01u} /* SecLvl: Level_01 */
  ,{ 1000u,1000u,   0u,FALSE, 3u,0x02u} /* SecLvl: Level_02 */
  ,{ 1000u,   0u,   0u,FALSE, 3u,0x04u} /* SecLvl: Level_04 */
};
/*! Security state change notification(s) */
CONST(Dcm_CfgStateNotificationInfoType, DCM_CONST) Dcm_CfgStateSecurityNotificationInfo[2]=
{
   { CallbackUDSsecurity}
  ,{ NULL_PTR}
};
/*! DID properties */
CONST(Dcm_CfgDidMgrDidInfoType, DCM_CONST) Dcm_CfgDidMgrDidInfo[28]=
{
   {    4u,   4u,   4u,   0u,0x03u} /* DID: 0x1000 */
  ,{    0u,   1u,   1u,   2u,0x03u} /* DID: 0x4101 */
  ,{   25u,  25u,  25u,   4u,0x03u} /* DID: 0xF101 */
  ,{   11u,  11u,  11u,   6u,0x01u} /* DID: 0xF110 */
  ,{    2u,   2u,   2u,   7u,0x01u} /* DID: 0xF111 */
  ,{   11u,  11u,  11u,   8u,0x01u} /* DID: 0xF118 */
  ,{    2u,   2u,   2u,   9u,0x01u} /* DID: 0xF119 */
  ,{   11u,  11u,  11u,  10u,0x03u} /* DID: 0xF120 */
  ,{   11u,  11u,  11u,  12u,0x03u} /* DID: 0xF130 */
  ,{    2u,   2u,   2u,  14u,0x03u} /* DID: 0xF131 */
  ,{    0u,   4u,   4u,  16u,0x01u} /* DID: 0xF139 */
  ,{    0u,   3u,   3u,  17u,0x01u} /* DID: 0xF150 */
  ,{   12u,  12u,  12u,  18u,0x01u} /* DID: 0xF15B */
  ,{   12u,  12u,  12u,  19u,0x03u} /* DID: 0xF15C */
  ,{    1u,   1u,   1u,  21u,0x01u} /* DID: 0xF186 */
  ,{   11u,  11u,  11u,  22u,0x03u} /* DID: 0xF187 */
  ,{    8u,   8u,   8u,  24u,0x01u} /* DID: 0xF18A */
  ,{    3u,   3u,   3u,  25u,0x01u} /* DID: 0xF18B */
  ,{   10u,  10u,  10u,  26u,0x01u} /* DID: 0xF18C */
  ,{   17u,  17u,  17u,  27u,0x03u} /* DID: 0xF190 */
  ,{    0u,   6u,   6u,  29u,0x01u} /* DID: 0xF193 */
  ,{    0u,   6u,   6u,  30u,0x01u} /* DID: 0xF195 */
  ,{    0u,   8u,   8u,  31u,0x01u} /* DID: 0xF197 */
  ,{   12u,  12u,  12u,  32u,0x03u} /* DID: 0xF198 */
  ,{    3u,   3u,   3u,  34u,0x01u} /* DID: 0xF199 */
  ,{    3u,   3u,   3u,  35u,0x01u} /* DID: 0xF19E */
  ,{    0u,   2u,   2u,  36u,0x03u} /* DID: 0xFD22 */
  ,{    0u,   6u,   6u,  38u,0x03u} /* DID: 0xFD30 */
};
/*! DID operation properties */
CONST(Dcm_CfgDidMgrDidOpInfoType, DCM_CONST) Dcm_CfgDidMgrDidOpInfo[40]=
{
   {    0u,   0u,0x05u} /* DID: 0x1000 */
  ,{    0u,   2u,0x01u} /* DID: 0x1000 */
  ,{    0u,   3u,0x07u} /* DID: 0x4101 */
  ,{    2u,   6u,0x01u} /* DID: 0x4101 */
  ,{    2u,   7u,0x05u} /* DID: 0xF101 */
  ,{    5u,   9u,0x01u} /* DID: 0xF101 */
  ,{    0u,  10u,0x05u} /* DID: 0xF110 */
  ,{    0u,  12u,0x05u} /* DID: 0xF111 */
  ,{    2u,  14u,0x05u} /* DID: 0xF118 */
  ,{    2u,  16u,0x05u} /* DID: 0xF119 */
  ,{    2u,  18u,0x05u} /* DID: 0xF120 */
  ,{    5u,  20u,0x01u} /* DID: 0xF120 */
  ,{    0u,  21u,0x05u} /* DID: 0xF130 */
  ,{    0u,  23u,0x01u} /* DID: 0xF130 */
  ,{    0u,  24u,0x05u} /* DID: 0xF131 */
  ,{    0u,  26u,0x01u} /* DID: 0xF131 */
  ,{    2u,  27u,0x07u} /* DID: 0xF139 */
  ,{    0u,  30u,0x07u} /* DID: 0xF150 */
  ,{    6u,  33u,0x05u} /* DID: 0xF15B */
  ,{    2u,  35u,0x05u} /* DID: 0xF15C */
  ,{    5u,  37u,0x01u} /* DID: 0xF15C */
  ,{    0u,  38u,0x05u} /* DID: 0xF186 */
  ,{    2u,  40u,0x05u} /* DID: 0xF187 */
  ,{    7u,  42u,0x01u} /* DID: 0xF187 */
  ,{    2u,  43u,0x05u} /* DID: 0xF18A */
  ,{    2u,  45u,0x05u} /* DID: 0xF18B */
  ,{    2u,  47u,0x05u} /* DID: 0xF18C */
  ,{    2u,  49u,0x05u} /* DID: 0xF190 */
  ,{    5u,  51u,0x01u} /* DID: 0xF190 */
  ,{    2u,  52u,0x07u} /* DID: 0xF193 */
  ,{    2u,  55u,0x07u} /* DID: 0xF195 */
  ,{    2u,  58u,0x07u} /* DID: 0xF197 */
  ,{    2u,  61u,0x05u} /* DID: 0xF198 */
  ,{    7u,  63u,0x01u} /* DID: 0xF198 */
  ,{    2u,  64u,0x05u} /* DID: 0xF199 */
  ,{    2u,  66u,0x05u} /* DID: 0xF19E */
  ,{    2u,  68u,0x07u} /* DID: 0xFD22 */
  ,{    2u,  71u,0x01u} /* DID: 0xFD22 */
  ,{    0u,  72u,0x07u} /* DID: 0xFD30 */
  ,{    0u,  75u,0x01u} /* DID: 0xFD30 */
};
/*! DID operation classes */
CONST(Dcm_CfgDidMgrDidOpClassInfoType, DCM_CONST) Dcm_CfgDidMgrDidOpClassInfo[77]=
{
   {  0u}
  ,{  1u}
  ,{  2u}
  ,{  3u}
  ,{  4u}
  ,{  5u}
  ,{  6u}
  ,{  7u}
  ,{  8u}
  ,{  9u}
  ,{ 10u}
  ,{ 11u}
  ,{ 12u}
  ,{ 13u}
  ,{ 14u}
  ,{ 15u}
  ,{ 16u}
  ,{ 17u}
  ,{ 18u}
  ,{ 19u}
  ,{ 20u}
  ,{ 21u}
  ,{ 22u}
  ,{ 23u}
  ,{ 24u}
  ,{ 25u}
  ,{ 26u}
  ,{ 27u}
  ,{ 28u}
  ,{ 29u}
  ,{ 30u}
  ,{ 31u}
  ,{ 32u}
  ,{ 33u}
  ,{ 34u}
  ,{ 35u}
  ,{ 36u}
  ,{ 37u}
  ,{ 38u}
  ,{ 39u}
  ,{ 40u}
  ,{ 41u}
  ,{ 42u}
  ,{ 43u}
  ,{ 44u}
  ,{ 45u}
  ,{ 46u}
  ,{ 47u}
  ,{ 48u}
  ,{ 49u}
  ,{ 50u}
  ,{ 51u}
  ,{ 52u}
  ,{ 53u}
  ,{ 54u}
  ,{ 55u}
  ,{ 56u}
  ,{ 57u}
  ,{ 58u}
  ,{ 59u}
  ,{ 60u}
  ,{ 61u}
  ,{ 62u}
  ,{ 63u}
  ,{ 64u}
  ,{ 65u}
  ,{ 66u}
  ,{ 67u}
  ,{ 68u}
  ,{ 69u}
  ,{ 70u}
  ,{ 71u}
  ,{ 72u}
  ,{ 73u}
  ,{ 74u}
  ,{ 75u}
  ,{ 76u}
};
/*! DID signal operation classes */
CONST(Dcm_CfgDidMgrSignalOpClassInfoType, DCM_CONST) Dcm_CfgDidMgrSignalOpClassInfo[76]=
{
   { ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData)),   4u,   4u,0x0002u} /* DID: 0x1000 */ /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0x1000 */ /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData)),   4u,   4u,0x1002u} /* DID: 0x1000 */ /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_WLCCtrlSts_ReadData)),   0u,   1u,0x0002u} /* DID: 0x4101 */                           /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_WLCCtrlSts_ReadDataLength)),   0u,   0u,0x0102u} /* DID: 0x4101 */                     /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0x4101 */                 /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_WLCCtrlSts_WriteData)),   0u,   1u,0x1004u} /* DID: 0x4101 */                          /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ECUConfigurarion_ReadData)),  25u,  25u,0x0002u} /* DID: 0xF101 */                     /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF101 */           /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ECUConfigurarion_WriteData)),  25u,  25u,0x1002u} /* DID: 0xF101 */                    /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_Diag_VM_HardwarePartNumber_ReadData)),  11u,  11u,0x0002u} /* DID: 0xF110 */                      /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF110 */            /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_Diag_VM_HardwareBaseline_ReadData)),   2u,   2u,0x0002u} /* DID: 0xF111 */                        /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF111 */              /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_SofwarePartNumber_ReadData)),  11u,  11u,0x0002u} /* DID: 0xF118 */                 /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF118 */       /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_SoftwarBaseline_ReadData)),   2u,   2u,0x0002u} /* DID: 0xF119 */                   /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF119 */         /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData)),  11u,  11u,0x0002u} /* DID: 0xF120 */             /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF120 */   /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData)),  11u,  11u,0x1002u} /* DID: 0xF120 */            /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData)),  11u,  11u,0x0002u} /* DID: 0xF130 */             /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF130 */   /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData)),  11u,  11u,0x1002u} /* DID: 0xF130 */            /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_CalibrationBaseline_ReadData)),   2u,   2u,0x0002u} /* DID: 0xF131 */               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF131 */     /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_CalibrationBaseline_WriteData)),   2u,   2u,0x1002u} /* DID: 0xF131 */              /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_Specialdatabaseline_ReadData)),   0u,   4u,0x0002u} /* DID: 0xF139 */               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength)),   0u,   0u,0x0102u} /* DID: 0xF139 */         /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF139 */     /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_BootloaderVersion_ReadData)),   0u,   3u,0x0002u} /* DID: 0xF150 */                    /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_BootloaderVersion_ReadDataLength)),   0u,   0u,0x0102u} /* DID: 0xF150 */              /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF150 */          /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ReadFingerprint_ReadData)),  12u,  12u,0x0002u} /* DID: 0xF15B */                      /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF15B */            /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ConfigurarionFingerprint_ReadData)),  12u,  12u,0x0002u} /* DID: 0xF15C */             /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF15C */   /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ConfigurarionFingerprint_WriteData)),  12u,  12u,0x1002u} /* DID: 0xF15C */            /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ReadActiveDiagSession_ReadData)),   1u,   1u,0x0002u} /* DID: 0xF186 */                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF186 */      /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_SparepartNumber_ReadData)),  11u,  11u,0x0002u} /* DID: 0xF187 */                   /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF187 */         /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VM_SparepartNumber_WriteData)),  11u,  11u,0x1002u} /* DID: 0xF187 */                  /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSupplierIdData_ReadData)),   8u,   8u,0x0002u} /* DID: 0xF18A */                 /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF18A */       /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ECUManufacturingDate_ReadData)),   3u,   3u,0x0002u} /* DID: 0xF18B */                 /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF18B */       /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ECUSerialNumber_ReadData)),  10u,  10u,0x0002u} /* DID: 0xF18C */                      /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF18C */            /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VIN_ReadData)),  17u,  17u,0x0002u} /* DID: 0xF190 */                                  /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VIN_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF190 */                        /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_VIN_WriteData)),  17u,  17u,0x1002u} /* DID: 0xF190 */                                 /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSHV_ReadData)),   0u,   6u,0x0002u} /* DID: 0xF193 */                            /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSHV_ReadDataLength)),   0u,   0u,0x0102u} /* DID: 0xF193 */                      /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSHV_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF193 */                  /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSESVNumber_ReadData)),   0u,   6u,0x0002u} /* DID: 0xF195 */                     /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSESVNumber_ReadDataLength)),   0u,   0u,0x0102u} /* DID: 0xF195 */               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF195 */           /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemName_ReadData)),   0u,   8u,0x0002u} /* DID: 0xF197 */                           /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemName_ReadDataLength)),   0u,   0u,0x0102u} /* DID: 0xF197 */                     /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemName_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF197 */                 /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_RepairShopFingerPrint_ReadData)),  12u,  12u,0x0002u} /* DID: 0xF198 */                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF198 */      /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_RepairShopFingerPrint_WriteData)),  12u,  12u,0x1002u} /* DID: 0xF198 */               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ECUProgrammingDate_ReadData)),   3u,   3u,0x0002u} /* DID: 0xF199 */                   /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF199 */         /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData)),   3u,   3u,0x0002u} /* DID: 0xF19E */               /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xF19E */     /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_NFCFunction_ReadData)),   0u,   2u,0x0002u} /* DID: 0xFD22 */                          /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_NFCFunction_ReadDataLength)),   0u,   0u,0x0102u} /* DID: 0xFD22 */                    /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_NFCFunction_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xFD22 */                /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_NFCFunction_WriteData)),   0u,   2u,0x1004u} /* DID: 0xFD22 */                         /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData)),   0u,   6u,0x0002u} /* DID: 0xFD30 */   /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength)),   0u,   0u,0x0102u} /* DID: 0xFD30 */ /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead)),   0u,   0u,0x0201u} /* DID: 0xFD30 */ /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_DidMgrOpFuncType)(Rte_Call_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData)),   0u,   6u,0x1004u} /* DID: 0xFD30 */  /* PRQA S 0313 */ /* MD_Dcm_0313 */
};
/*! RID properties */
CONST(Dcm_CfgRidMgrRidInfoType, DCM_CONST) Dcm_CfgRidMgrRidInfo[2]=
{
   {    0u,   1u,0x01u, 0u} /* RID: 0x0203 */
  ,{    1u,   8u,0x05u, 0u} /* RID: 0xFD04 */
};
/*! RID operation properties */
CONST(Dcm_CfgRidMgrOpInfoType, DCM_CONST) Dcm_CfgRidMgrOpInfo[3]=
{
   { ((Dcm_RidMgrOpFuncType)(Rte_Call_RoutineServices_CheckProgrammingPreCondition_Start)),   0u,   0u,   0u,   0u, 0u} /* RID: 0x0203 */            /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_RidMgrOpFuncType)(Dcm_RidMgr_FD04_Start)),   1u,   1u,   0u,   0u, 9u} /* RID: 0xFD04 */                                                  /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_RidMgrOpFuncType)(Rte_Call_RoutineServices_CheckNFCAntenna_RequestResults)),   0u,   0u,   7u,   7u, 3u} /* RID: 0xFD04 */                /* PRQA S 0313 */ /* MD_Dcm_0313 */
};
/*! DCM service initializers */
CONST(Dcm_DiagSvcInitFuncType, DCM_CONST) Dcm_CfgDiagSvcInitializers[2]=
{
   Dcm_Service27Init
  ,NULL_PTR /* end marker */
};
/*! DCM service properties */
CONST(Dcm_CfgDiagServiceInfoType, DCM_CONST) Dcm_CfgDiagServiceInfo[12]=
{
   { Dcm_Service10Processor,0x01u, 1u,   1u,   2u, 0u, 0u} /* SID: 0x10 */
  ,{ Dcm_Service11Processor,0x01u, 1u,   3u,   4u, 0u, 0u} /* SID: 0x11 */
  ,{ Dcm_Service14Processor,0x00u, 3u,   0u,   0u, 0u, 0u} /* SID: 0x14 */
  ,{ Dcm_Service19Processor,0x01u, 1u,   5u,   0u, 2u, 0u} /* SID: 0x19 */
  ,{ Dcm_Service22Processor,0x00u, 2u,   0u,   0u, 0u, 0u} /* SID: 0x22 */
  ,{ Dcm_Service27Processor,0x03u, 1u,   6u,   0u, 0u, 0u} /* SID: 0x27 */
  ,{ Dcm_Service28Processor,0x01u, 1u,   7u,   0u, 0u, 0u} /* SID: 0x28 */
  ,{ Dcm_Service2EProcessor,0x00u, 3u,   0u,   0u, 0u, 0u} /* SID: 0x2E */
  ,{ Dcm_Service31Processor,0x01u, 3u,   0u,   0u, 0u, 0u} /* SID: 0x31 */
  ,{ Dcm_Service3EProcessor,0x01u, 1u,   0u,   0u, 0u, 0u} /* SID: 0x3E */
  ,{ Dcm_Service85Processor,0x01u, 1u,   8u,   0u, 0u, 0u} /* SID: 0x85 */
  ,{ Dcm_RepeaterDeadEnd,0x00u, 0u,   0u,   0u, 0u, 0u} /* Dcm_RepeaterDeadEnd */
};
/*! Indirection from diag service info to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgDiagSvcIdExecPrecondTable[11]=
{
      0u /* SID: 0x10 */
  ,   0u /* SID: 0x11 */
  ,   0u /* SID: 0x14 */
  ,   0u /* SID: 0x19 */
  ,   0u /* SID: 0x22 */
  ,   1u /* SID: 0x27 */
  ,   0u /* SID: 0x28 */
  ,   0u /* SID: 0x2E */
  ,   0u /* SID: 0x31 */
  ,   0u /* SID: 0x3E */
  ,   0u /* SID: 0x85 */
};
/*! DCM service post processors */
CONST(Dcm_DiagSvcConfirmationFuncType, DCM_CONST) Dcm_CfgDiagSvcPostProcessors[9]=
{
   Dcm_ServiceNoPostProcessor
  ,Dcm_Service10PostProcessor
  ,Dcm_Service10FastPostProcessor
  ,Dcm_Service11PostProcessor
  ,Dcm_Service11FastPostProcessor
  ,Dcm_Service19PostProcessor
  ,Dcm_Service27PostProcessor
  ,Dcm_Service28PostProcessor
  ,Dcm_Service85PostProcessor
};
/*! DCM service paged buffer updater */
CONST(Dcm_DiagSvcUpdateFuncType, DCM_CONST) Dcm_CfgDiagSvcUpdaters[3]=
{
   Dcm_ServiceNoUpdater
  ,Dcm_PagedBufferDataPadding
  ,Dcm_Service19Updater
};
/*! DCM service paged buffer canceller */
CONST(Dcm_DiagSvcCancelFuncType, DCM_CONST) Dcm_CfgDiagSvcCancellers[1]=
{
   Dcm_ServiceNoCancel
};
/*! Service 0x10 sub-service properties table  */
CONST(Dcm_CfgSvc10SubFuncInfoType, DCM_CONST) Dcm_CfgSvc10SubFuncInfo[3]=
{
   { { 50u, 500u}, 0u} /* Session ID: 0x01 */
  ,{ { 50u, 500u}, 2u} /* Session ID: 0x02 */
  ,{ { 50u, 500u}, 0u} /* Session ID: 0x03 */
};
/*! Indirection from service 0x10 sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc10SubFuncExecPrecondTable[3]=
{
      0u /* Session ID: 0x01 */
  ,   1u /* Session ID: 0x02 */
  ,   0u /* Session ID: 0x03 */
};
/*! Service 0x11 sub-service properties table  */
CONST(Dcm_CfgSvc11SubFuncInfoType, DCM_CONST) Dcm_CfgSvc11SubFuncInfo[2]=
{
   { Dcm_Service11_01Processor} /* SF: 0x01 */
  ,{ Dcm_Service11_03Processor} /* SF: 0x03 */
};
/*! Indirection from service 0x11 sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc11SubFuncExecPrecondTable[2]=
{
      1u /* SF: 0x01 */
  ,   1u /* SF: 0x03 */
};
/*! Service 0x19 sub-service properties table  */
CONST(Dcm_CfgSvc19SubFuncInfoType, DCM_CONST) Dcm_CfgSvc19SubFuncInfo[4]=
{
   { Dcm_Service19_01Processor, 2u} /* SF: 0x01 */
  ,{ Dcm_Service19_02Processor, 2u} /* SF: 0x02 */
  ,{ Dcm_Service19_06Processor, 5u} /* SF: 0x06 */
  ,{ Dcm_Service19_0AProcessor, 1u} /* SF: 0x0A */
};
/*! Indirection from service 0x19 sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc19SubFuncExecPrecondTable[4]=
{
      2u /* SF: 0x01 */
  ,   2u /* SF: 0x02 */
  ,   2u /* SF: 0x06 */
  ,   2u /* SF: 0x0A */
};
/*! Service 0x27 sub-service properties table  */
CONST(Dcm_CfgSvc27SubFuncInfoType, DCM_CONST) Dcm_CfgSvc27SubFuncInfo[6]=
{
   {    1u} /* SF: 0x01 */                                                                                                                           /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{    5u} /* SF: 0x02 */                                                                                                                           /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{    1u} /* SF: 0x03 */                                                                                                                           /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{    5u} /* SF: 0x04 */                                                                                                                           /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{    1u} /* SF: 0x07 */                                                                                                                           /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{    5u} /* SF: 0x08 */                                                                                                                           /* PRQA S 0313 */ /* MD_Dcm_0313 */
};
/*! Service 0x27 security level properties table  */
CONST(Dcm_CfgSvc27SecLevelInfoType, DCM_CONST) Dcm_CfgSvc27SecLevelInfo[3]=
{
   { ((Dcm_Svc27GetSeedFuncType)(Rte_Call_SecurityAccess_Level_01_GetSeed)),Rte_Call_SecurityAccess_Level_01_CompareKey,   4u, 0u} /* SecLvl: Level_01 */ /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_Svc27GetSeedFuncType)(Rte_Call_SecurityAccess_Level_02_GetSeed)),Rte_Call_SecurityAccess_Level_02_CompareKey,   4u, 0u} /* SecLvl: Level_02 */ /* PRQA S 0313 */ /* MD_Dcm_0313 */
  ,{ ((Dcm_Svc27GetSeedFuncType)(Rte_Call_SecurityAccess_Level_04_GetSeed)),Rte_Call_SecurityAccess_Level_04_CompareKey,   4u, 0u} /* SecLvl: Level_04 */ /* PRQA S 0313 */ /* MD_Dcm_0313 */
};
/*! Indirection from service 0x27 sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc27SubFuncExecPrecondTable[6]=
{
      1u /* SF: 0x01 */
  ,   1u /* SF: 0x02 */
  ,   3u /* SF: 0x03 */
  ,   3u /* SF: 0x04 */
  ,   4u /* SF: 0x07 */
  ,   4u /* SF: 0x08 */
};
/*! Service 0x28 sub-service properties table  */
CONST(Dcm_CfgSvc28SubFuncInfoType, DCM_CONST) Dcm_CfgSvc28SubFuncInfo[4]=
{
   { Dcm_Service28_XXProcessor, 2u} /* SF: 0x00 */
  ,{ Dcm_Service28_XXProcessor, 2u} /* SF: 0x01 */
  ,{ Dcm_Service28_XXProcessor, 2u} /* SF: 0x02 */
  ,{ Dcm_Service28_XXProcessor, 2u} /* SF: 0x03 */
};
/*! Indirection from service 0x28 sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc28SubFuncExecPrecondTable[4]=
{
      1u /* SF: 0x00 */
  ,   1u /* SF: 0x01 */
  ,   1u /* SF: 0x02 */
  ,   1u /* SF: 0x03 */
};
/*! Service 0x28 network ID to ComM channel map */
CONST(NetworkHandleType, DCM_CONST) Dcm_CfgSvc28SubNetIdMap[2]=
{
   DCM_SVC_28_NETWORK_ALL
  ,DCM_SVC_28_NETWORK_CURRENT
};
/*! Indirection from service 0x3E sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc3ESubFuncExecPrecondTable[1]=
{
      0u /* SF: 0x00 */
};
/*! Indirection from service 0x85 sub functions to execution pre conditions */
CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc85SubFuncExecPrecondTable[2]=
{
      0u /* SF: 0x01 */
  ,   0u /* SF: 0x02 */
};
/*! DCM service 0x85 properties */
CONST(Dcm_CfgSvc85SubFuncInfoType, DCM_CONST) Dcm_CfgSvc85SubFuncInfo[2]=
{
   { Dem_EnableDTCSetting,RTE_MODE_DcmControlDtcSetting_ENABLEDTCSETTING} /* SF: 0x01 */
  ,{ Dem_DisableDTCSetting,RTE_MODE_DcmControlDtcSetting_DISABLEDTCSETTING} /* SF: 0x02 */
};
#define DCM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   Module call-out implementations
---------------------------------------------- */
#define DCM_START_SEC_CALLOUT_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/***********************************************************************************************************************
 *  Dcm_RidMgr_FD04_Start()
***********************************************************************************************************************/
/* Implements CDD Dcm_RidMgr<XXX>() */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_RidMgr_FD04_Start(Dcm_OpStatusType OpStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_RidMgrRidLengthPtrType DataLength, Dcm_NegativeResponseCodePtrType ErrorCode) /* PRQA S 3673 */ /* MD_Dcm_APIStd_3673 */
{
  uint8 dataInDcmDspStartRoutineInSignal;

  dataInDcmDspStartRoutineInSignal = ((uint8)(Dcm_DiagGetReqDataAsU8Rel(pMsgContext, 0u)))                                                           /* PRQA S 2985 */ /* MD_Dcm_Redundant_2985 */;

  DCM_IGNORE_UNREF_PARAM(DataLength);                                                                                                                /* PRQA S 3112 */ /* MD_Dcm_3112 */

  return Rte_Call_RoutineServices_CheckNFCAntenna_Start(dataInDcmDspStartRoutineInSignal
                                                       , OpStatus
                                                       , ErrorCode
                                                       );                                                                                            /* SBSW_DCM_GEN_COMB_PARAM_PTR_FORWARD */
}
/***********************************************************************************************************************
 *  Dcm_ServiceNoPostProcessor()
***********************************************************************************************************************/
/* Implements CDD Dcm_ServiceNoPostProcessor() */
DCM_LOCAL FUNC(void, DCM_CALLOUT_CODE) Dcm_ServiceNoPostProcessor(Dcm_ContextPtrType pContext, Dcm_ConfirmationStatusType status)                    /* PRQA S 3673 */ /* MD_Dcm_APIStd_3673 */
{
  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_Dcm_3112 */
  DCM_IGNORE_UNREF_PARAM(status);                                                                                                                    /* PRQA S 3112 */ /* MD_Dcm_3112 */
}
/***********************************************************************************************************************
 *  Dcm_ServiceNoUpdater()
***********************************************************************************************************************/
/* Implements CDD Dcm_ServiceNoUpdater() */
DCM_LOCAL FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ServiceNoUpdater(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_DiagDataContextPtrType pDataContext, Dcm_NegativeResponseCodePtrType ErrorCode) /* PRQA S 3673 */ /* MD_Dcm_APIStd_3673 */
{
  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_Dcm_3112 */
  DCM_IGNORE_UNREF_PARAM(opStatus);                                                                                                                  /* PRQA S 3112 */ /* MD_Dcm_3112 */
  DCM_IGNORE_UNREF_PARAM(pDataContext);                                                                                                              /* PRQA S 3112 */ /* MD_Dcm_3112 */
  DCM_IGNORE_UNREF_PARAM(ErrorCode);                                                                                                                 /* PRQA S 3112 */ /* MD_Dcm_3112 */
  return E_NOT_OK;
}
/***********************************************************************************************************************
 *  Dcm_ServiceNoCancel()
***********************************************************************************************************************/
/* Implements CDD Dcm_ServiceNoCancel() */
DCM_LOCAL FUNC(void, DCM_CALLOUT_CODE) Dcm_ServiceNoCancel(Dcm_ContextPtrType pContext, Dcm_DiagDataContextPtrType pDataContext)                     /* PRQA S 3673 */ /* MD_Dcm_Design_3673 */
{
  DCM_IGNORE_UNREF_PARAM(pContext);                                                                                                                  /* PRQA S 3112 */ /* MD_Dcm_3112 */
  DCM_IGNORE_UNREF_PARAM(pDataContext);                                                                                                              /* PRQA S 3112 */ /* MD_Dcm_3112 */
  /* nothing to do */
}
#define DCM_STOP_SEC_CALLOUT_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"                                                                                                                                  /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ********************************************************************************************************************
 * END OF FILE: Dcm_Lcfg.c
 * ******************************************************************************************************************** */

