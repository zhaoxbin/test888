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
 *              File: Dcm_Lcfg.h
 *   Generation Time: 2020-09-27 09:06:40
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



#if !defined(DCM_LCFG_H)
# define DCM_LCFG_H
/* ----------------------------------------------
 ~&&&   Includes
---------------------------------------------- */
# include "Dem.h"
# include "Dem_Dcm.h"
/* ----------------------------------------------
 ~&&&   Versions
---------------------------------------------- */

/*! Implementation version */
# define DCM_LCFG_MAJOR_VERSION                                                11u
# define DCM_LCFG_MINOR_VERSION                                                 6u
# define DCM_LCFG_PATCH_VERSION                                                 0u
/* ----------------------------------------------
 ~&&&   Switches
---------------------------------------------- */
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
/*! Specifies whether the Dcm_CfgDidMgrOpInfoIoControlType structure is required */
#if (DCM_DIDMGR_OPTYPE_IO_RETCTRL2ECU_ENABLED == STD_ON) || \
    (DCM_DIDMGR_IODID_EXEC_PRECOND_LIMIT_ENABLED == STD_ON) || \
    (DCM_DIDMGR_IO_MASKRECORD_ENABLED == STD_ON)
# define DCM_DIDMGR_OP_INFO_IOCONTROL_ENABLED                        STD_ON
#else
# define DCM_DIDMGR_OP_INFO_IOCONTROL_ENABLED                        STD_OFF
#endif
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Function-like macros
---------------------------------------------- */
# define Dcm_ModeOnComControlModeChange(channelId, mode)                       ((void)(Rte_Switch_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f(mode))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/* ----------------------------------------------
 ~&&&   Typedefs Exported Level 2
---------------------------------------------- */
# if (DCM_MODEMGR_SUPPORT_ENABLED == STD_ON) /* COV_DCM_SUPPORT_ALWAYS TX */
/*! Mode-rule handler function prototype */
typedef P2FUNC(boolean, DCM_CODE, Dcm_ModeRuleFuncType) (Dcm_Ptr2LocalU8Type modeRuleRef /* OUT: The result NRC */);
# endif /* (DCM_MODEMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_OBDUDSIDMGR_SUPPORT_ENABLED == STD_ON)
typedef uint8       Dcm_ObdIdMgrHandleMemType;
typedef uint8_least Dcm_ObdIdMgrHandleOptType;
# endif /* (DCM_OBDUDSIDMGR_SUPPORT_ENABLED == STD_ON) */
/*! Base data type for a thread */
typedef uint8        Dcm_ThreadIdMemType;
typedef uint8_least  Dcm_ThreadIdOptType;
/* ----------------------------------------------
 ~&&&   Typedefs
---------------------------------------------- */

/*! Depends on the largest configured buffer size */
typedef uint16 Dcm_CfgNetBufferSizeMemType;
/*! Depends on the largest configured buffer size */
typedef uint16_least Dcm_CfgNetBufferSizeOptType;
/*! Function pointer prototype for a protocol activation notification */
typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_NetProtocolIndicationFuncType) (Dcm_ProtocolType newProtocol /* IN: new ProtocolId */);

/*! Diagnostic protocol related notification functions */
struct DCM_CFGNETPROTOCOLNOTIFICATIONINFOTYPE_TAG
{
  Dcm_NetProtocolIndicationFuncType    StartFunc;  /*!< Pointer to a function of kind Xxx_StartProtocol() */
};
typedef struct DCM_CFGNETPROTOCOLNOTIFICATIONINFOTYPE_TAG Dcm_CfgNetProtocolNotificationInfoType;
/*! Zero based reference to a USDT buffer configuration entry (0..31) */
typedef uint8        Dcm_CfgNetBufferRefMemType;
typedef uint8_least  Dcm_CfgNetBufferRefOptType;

/*! Zero based reference to a ComM channel map entry (0..255) */
typedef uint8        Dcm_CfgNetNetIdRefMemType;
typedef uint8_least  Dcm_CfgNetNetIdRefOptType;

/*! Zero based reference to a USDT message transport object (0..31) */
typedef uint8        Dcm_CfgNetTObjHandleMemType;
typedef uint8_least  Dcm_CfgNetTObjHandleOptType;

/*! Zero based reference to a UUDT message transport object (0..255) */
typedef uint8        Dcm_CfgNetPTxObjHandleMemType;
typedef uint8_least  Dcm_CfgNetPTxObjHandleOptType;

/*! Diagnostic protocol priority (0..255) */
typedef uint8        Dcm_CfgNetProtPrioType;

/*! Diagnostic protocol maximum length (0..65535) */
typedef uint16       Dcm_CfgNetProtLengthType;

/*! Zero based reference to a UUDT message DcmTxPduId configuration entry (0..255) */
typedef uint8        Dcm_CfgNetPerTxPduIdRefMemType;
typedef uint8_least  Dcm_CfgNetPerTxPduIdRefOptType;

/*! Diagnostic client connection properties (Valid values: DCM_NET_CONN_PROP_*) */
typedef uint8        Dcm_CfgNetConnPropertiesType;

/*! Diagnostic client connection UUDT frame size (0..4294967295) */
typedef PduLengthType Dcm_UudtFrameSizeType;

/*! Configuration of a USDT buffer */
struct DCM_CFGNETBUFFERINFOTYPE_TAG
{
  Dcm_PbConstMsgType            BufferPtr;  /*!< Pointer to a USDT buffer */
  Dcm_CfgNetBufferSizeMemType   Size;       /*!< Size of this specific USDT buffer */
};
typedef struct DCM_CFGNETBUFFERINFOTYPE_TAG Dcm_CfgNetBufferInfoType;

/*! Configuration of a DcmRxPduId */
struct DCM_CFGNETRXPDUINFOTYPE_TAG
{
  boolean                   IsFuncReq;  /*!< Functional request message: FALSE = physical, TRUE = functional */
  Dcm_NetConnRefMemType     ConnRef;    /*!< Reference to Dcm_CfgNetConnectionInfo[] entry */
};
typedef struct DCM_CFGNETRXPDUINFOTYPE_TAG Dcm_CfgNetRxPduInfoType;

/*! Configuration of a diagnostic client connection */
struct DCM_CFGNETCONNECTIONTYPE_TAG
{
  uint16                          ClientSrcAddr;          /*!< Diagnostic client's unique source address (identifier) */
#if (DCM_NET_PERIODIC_TX_ENABLED == STD_ON)
  Dcm_TmrTimerCntrMemType         PeriodicTxConfTimeout;  /*!< Diagnostic client specific periodic message transmission confirmation timeout (0 - if no periodic message used) */
  Dcm_UudtFrameSizeType           UudtFrameSize;          /*!< Diagnostic client specific UUDT frame size */
#endif
  PduIdType                       TxPduIdMain;            /*!< PduR's PduId of the main diagnostic response */
  Dcm_CfgNetNetIdRefMemType       NetworkIdRef;           /*!< Reference to Dcm_CfgNetConnComMChannelMap[] entry */
  Dcm_NetProtRefMemType           ProtRef;                /*!< Reference to Dcm_PbCfgNetProtocolInfo[] entry */
#if (DCM_NET_PERIODIC_TX_ENABLED == STD_ON)
  Dcm_CfgNetPerTxPduIdRefMemType  PeriodicTxRef;          /*!< Reference to Dcm_PbCfgNetPerTxPduIdInfo[] entry */
  Dcm_CfgNetPTxObjHandleMemType   NumPeriodicTxPduIds;    /*!< Number of periodic messages of the diagnostic client (0 = none) */
#endif
#if (DCM_NET_CONN_ECU_ADDRESS_ENABLED == STD_ON)
  uint8                           EcuAddress;             /*!< ECU network address */
#endif
#if (DCM_NET_CONN_PROPERTIES_ENABLED == STD_ON)
  Dcm_CfgNetConnPropertiesType    Properties;             /*!< Diagnostic client specific properties (Any combination of DCM_NET_CONN_PROP_*) */
#endif
};
typedef struct DCM_CFGNETCONNECTIONTYPE_TAG Dcm_CfgNetConnectionInfoType;

/*! Configuration of a diagnostic client protocol */
struct DCM_CFGNETPROTOCOLTYPE_TAG
{
  Dcm_DiagP2TimingsType       SrvAdjTime;         /*!< The P2 times to be used for all diagnostic clients associated with this diagnostic protocol */
  Dcm_CfgNetProtLengthType    MaxLength;          /*!< Maximum allowed request/response length for all connections within this diagnostic protocol */
  Dcm_ProtocolType            Id;                 /*!< The diagnostic protocol name (e.g. UDS_ON_CAN) */
#if (DCM_NET_PROTOCOL_PRIORITISATION_ENABLED == STD_ON)
  Dcm_CfgNetProtPrioType      Priority;           /*!< The priority of all connections associated with this diagnostic protocol (0 - highest, 255 - lowest) */
#endif
  boolean                     HasRespPendOnBoot;  /*!< Specifies whether RCR-RP shall be sent prior jump to the boot-loader (TRUE - do send RCR-RP prior jump to FBL, FALSE - do not send) */
  Dcm_CfgNetBufferRefMemType  RxTxBufferRef;      /*!< Reference to Dcm_PbCfgNetBufferInfo[] entry */
#if (DCM_DEM_CLIENTID_ENABLED == STD_ON)
  uint8                       DemClientId;        /*!< The DEM client ID */
#endif
  uint8                       ThreadId;           /*!< The active Thread ID */
};
typedef struct DCM_CFGNETPROTOCOLTYPE_TAG Dcm_CfgNetProtocolInfoType;
typedef uint8  Dcm_NetTransportObjectStateType;
typedef uint16 Dcm_NetTransportObjectFlagType;
typedef uint8  Dcm_NetResponseType;
typedef uint8  Dcm_NetComMStateType;

/*! Control data of the USDT message buffers (main and additional) */
struct DCM_NETBUFFERCONTEXTTYPE_TAG
{
  volatile uint8  IsInUseCnt; /*!< Usage counter (0 - not in use, >0 - buffer in use from at least one user) */
};
typedef struct DCM_NETBUFFERCONTEXTTYPE_TAG Dcm_NetBufferContextType;

/*! Transport object control data */
struct DCM_NETTRANSPORTOBJECTTYPE_TAG
{
  Dcm_ReadOnlyMsgType             RxData;                                  /*!< Pointer to the buffer to store the request data (can be the main buffer or an additional buffer) */
  Dcm_NetTransportObjectFlagType  Flags;                                   /*!< Control flags of a transport object (Multiple combination of DCM_NET_TOBJ_FLAG_*) */
  Dcm_CfgNetBufferSizeMemType     RxLength;                                /*!< The diagnostic request length */
  Dcm_CfgNetBufferSizeMemType     BuffPos;                                 /*!< Keeps track of where to copy the next received diagnostic message data portion */
  PduIdType                       RxPduId;                                 /*!< DcmRxPduId used to allocate the transport object */
  Dcm_NetResponseType             ResType;                                 /*!< The diagnostic response type (e.g. RCR-RP, final (not-)paged etc.) */
  Dcm_CfgNetTObjHandleMemType     Handle;                                  /*!< The transport object ID */
  Dcm_NetConnRefMemType           ConnId;                                  /*!< Reference to Dcm_PbCfgNetConnectionInfo[] entry */
  Dcm_CfgNetBufferRefMemType      BufferHdl;                               /*!< Reference to Dcm_PbRamNetBufferContext[] entry */
  volatile Dcm_NetTransportObjectStateType State;                          /*!< State of the transport object (Valid values: DCM_NET_TOBJ_STATE_*) */
  Dcm_MsgItemType                 AddBuffer[DCM_NET_TOBJ_ADDBUFFER_SIZE];  /*!< Temporary buffer for NRC 0x78 and 0x21 responses and 0x3E 0x80 functional requests (optional sepcific cause code) */
  PduInfoType                     BuffInfo;                                /*!< PduR transmission data information exchange */
};
typedef struct DCM_NETTRANSPORTOBJECTTYPE_TAG Dcm_NetTransportObjectType;

/*! ComM channel related control information */
struct DCM_NETCOMMCONTEXT_TAG
{
  Dcm_NetComMStateType   ComState;            /*!< The current state of the ComM channel (FullCom/SilentCom/NoCom) */
  Dcm_NetConnRefMemType  RegisteredNetworks;  /*!< Number of active USDT diagnostic client connections on certain ComM channel */
};
typedef struct DCM_NETCOMMCONTEXT_TAG Dcm_NetComMContextType;

#if (DCM_NET_PERIODIC_TX_ENABLED == STD_ON)
typedef uint8       Dcm_NetPerTxObjStateMemType;
typedef uint8_least Dcm_NetPerTxObjStateOptType;

/*! Periodic message (UUDT) transport object control data */
struct DCM_NETPERIODICTXOBJECTTYPE_TAG
{
  PduInfoType                          TxPduInfo;                               /*!< PduR transmission data information exchange */
  volatile Dcm_TmrTimerCntrMemType     Timer;                                   /*!< Message transmission deadline monitor (can be changed within an ISR) */
  Dcm_MsgItemType                      TxBuffer[DCM_NET_PERIODIC_BUFFER_SIZE];  /*!< Periodic message data buffer */
  volatile Dcm_NetPerTxObjStateMemType State;                                   /*!< Periodic message state (Free, Reserved, Queued, Sent) */
  uint16                               Did;                                     /*!< The periodic Did assigned with the message */
};
typedef struct DCM_NETPERIODICTXOBJECTTYPE_TAG Dcm_NetPeriodicTxObjectType;
#endif
#if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
/*! Network sub-component post-build-variant (selectable/loadable) related configuration data */
struct DCM_NETVARIANTINFOTYPE_TAG
{
  P2CONST(Dcm_CfgNetRxPduInfoType, AUTOMATIC, DCM_PBCFG)       RxPduIdTable;              /*!< Pointer to the DcmRxPdus' configuration */
  P2CONST(Dcm_CfgNetConnectionInfoType, AUTOMATIC, DCM_PBCFG)  ConnectionTable;           /*!< Pointer to the diagnostic clients' connections */
  P2CONST(Dcm_CfgNetProtocolInfoType, AUTOMATIC, DCM_PBCFG)    ProtocolTable;             /*!< Pointer to the diagnostic protocols' configuration */
  P2CONST(Dcm_CfgNetNetIdRefMemType, AUTOMATIC, DCM_PBCFG)     NetConnComMChannelMap;     /*!< Pointer to the diagnostic client related ComM channel map */
  P2CONST(NetworkHandleType, AUTOMATIC, DCM_PBCFG)             NetworkHandleLookUpTable;  /*!< Pointer to the ComM channel look-up table */
  P2CONST(NetworkHandleType, AUTOMATIC, DCM_PBCFG)             NetAllComMChannelMap;      /*!< Pointer to the map of all related to DCM ComM channels */
# if (DCM_NET_COMCTRL_ALLNET_SUPPORT_ENABLED == STD_ON)
  P2CONST(NetworkHandleType, AUTOMATIC, DCM_PBCFG)             ComCtrlChannelListAll;     /*!< Pointer to the list of all ComM channels to be used for SID 0x28 with SubNetType=AllChannels */
# endif

  P2CONST(Dcm_NetConnRefMemType, AUTOMATIC, DCM_PBCFG)         TxPduIdMap;                /*!< Pointer to the USDT DcmTxPduId to client connection map */
  P2CONST(Dcm_CfgNetPTxObjHandleMemType, AUTOMATIC, DCM_PBCFG) PerTxPduIdMap;             /*!< Pointer to the UUDT DcmTxPduId to periodic message transport object map */
  P2CONST(PduIdType, AUTOMATIC, DCM_PBCFG)                     PerTxPduIdTable;           /*!< Pointer to the list of all UUDT DcmTxPduIds */
# if (DCM_NET_MONITOR_FOREIGN_N_TA_ENABLED == STD_ON)
  P2CONST(PduIdType, AUTOMATIC, DCM_PBCFG)                     CanTp2DcmRxPduIdMap;       /*!< Pointer to the CanTpRxPduId to DcmRxPduId map */
# endif

  PduIdType                     NumRxPduIds;         /*!< Number of DcmRxPduIds */
  PduIdType                     NumTxPduIds;         /*!< Number of DcmTxPduIds */
# if (DCM_NET_MONITOR_FOREIGN_N_TA_ENABLED == STD_ON)
  PduIdType                     CanTpRxPduIdMin;     /*!< Lowest CanTpRxPduId */
  PduIdType                     CanTpRxPduIdMax;     /*!< Highest CanTpRxPduId */
  PduIdType                     NumCanTpRxPduIds;    /*!< Number of used CanTpRcPduIds (0 - none are used, >0 - at least one used) */
# endif
  NetworkHandleType             NumComMChannels;     /*!< Number of all ComM channels related to diagnostic clients */
  NetworkHandleType             NumAllComMChannels;  /*!< Number of all ComM channels managed by DCM */
  Dcm_CfgNetPTxObjHandleMemType NumPerTxObjects;     /*!< Maximum number of periodic message transport objects over all diagnostic client connections */
  Dcm_NetConnRefMemType         NumConnections;      /*!< Number of diagnostic client connections */
  Dcm_NetProtRefMemType         NumProtocols;        /*!< Number of diagnostic protocols */
  Dcm_CfgNetBufferRefMemType    NumBuffers;          /*!< Number of USDT buffers */
  Dcm_CfgNetTObjHandleMemType   NumTranspObjects;    /*!< Number of USDT transport objects */
};
typedef struct DCM_NETVARIANTINFOTYPE_TAG Dcm_CfgNetVariantInfoType;
#endif

#if (DCM_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
/*! Network sub-component post-build-loadable reallocatable shared RAM data */
struct DCM_NETRAMVARIANTINFOTYPE_TAG
{
# if (DCM_NET_PERIODIC_TX_ENABLED == STD_ON)
  P2VAR(Dcm_NetPeriodicTxObjectType, AUTOMATIC, DCM_RAM_PBCFG) PeriodicTxObjects;  /*!< Pointer to the pool of periodic (UUDT) message transport objects */
# endif
  P2VAR(Dcm_NetComMContextType, AUTOMATIC, DCM_RAM_PBCFG)      ComMContexts;       /*!< Pointer to the pool of ComM channels' control states */
  P2VAR(Dcm_CfgNetTObjHandleMemType, AUTOMATIC, DCM_RAM_PBCFG) ConnId2TObjIdMap;   /*!< Pointer to the USDT diagnostic client connection to USDT message transport object allocation map */
  P2VAR(Dcm_NetTransportObjectType, AUTOMATIC, DCM_RAM_PBCFG)  TranspObjects;      /*!< Pointer to the pool of USDT message transport objects */
  P2VAR(Dcm_NetBufferContextType, AUTOMATIC, DCM_RAM_PBCFG)    BufferContexts;     /*!< Pointer to the pool of USDT message buffers' control states */
# if (DCM_MODE_COMMCTRL_ENABLED == STD_ON)
  P2VAR(Dcm_CommunicationModeType, AUTOMATIC, DCM_RAM_PBCFG)   ComCtrlChannels;    /*!< Pointer to the pool of ComM channels' communication state */
# endif
};
typedef struct DCM_NETRAMVARIANTINFOTYPE_TAG Dcm_CfgNetRamVariantInfoType;

/*! Network sub-component post-build-loadable reallocatable shared configuration data */
struct DCM_NETROMVARIANTINFOTYPE_TAG
{
  P2CONST(Dcm_CfgNetBufferInfoType, AUTOMATIC, DCM_PBCFG)  BufferInfo;  /*!< Pointer to the USDT buffer configuration */
};
typedef struct DCM_NETROMVARIANTINFOTYPE_TAG Dcm_CfgNetRomVariantInfoType;
#endif
/*! Depends on the mode rule table size */
typedef uint8 Dcm_CfgModeMgrRuleRefMemType;
/*! Depends on the mode rule table size */
typedef uint8_least Dcm_CfgModeMgrRuleRefOptType;
/*! Depends on the state group with largest number of states */
typedef uint8 Dcm_CfgStateGroupMemType;
/*! Depends on the state group with largest number of states */
typedef uint8_least Dcm_CfgStateGroupOptType;
/*! Depends on the total number of diagnostic service state/mode filters */
typedef uint8 Dcm_CfgStateRefMemType;
/*! Depends on the total number of diagnostic service state/mode filters */
typedef uint8_least Dcm_CfgStateRefOptType;
/*! Depends on the total number of security fixed byte values in non-default security levels */
typedef uint8 Dcm_CfgStateSecurityFixedByteRefMemType;
/*! Depends on the total number of security fixed byte values in non-default security levels */
typedef uint8_least Dcm_CfgStateSecurityFixedByteRefOptType;
/*! Depends on the how many Fixed byte sets are configured per a security level */
typedef uint8 Dcm_CfgStateVsgSecurityFixedByteInfoRefMemType;
/*! Depends on the how many Fixed byte sets are configured per a security level */
typedef uint8_least Dcm_CfgStateVsgSecurityFixedByteInfoRefOptType;
/*! A diagnostic entity diagnostic state related execution pre-conditions package */
struct DCM_CFGSTATEPRECONDITIONTYPE_TAG
{
  Dcm_CfgStateGroupMemType Session;   /*!< Diagnostic session pre-condition(s) (Bitmap) */
#if (DCM_STATE_SECURITY_ENABLED == STD_ON)
  Dcm_CfgStateGroupMemType Security;  /*!< Security access pre-condition(s) (Bitmap) */
#endif
};
typedef struct DCM_CFGSTATEPRECONDITIONTYPE_TAG Dcm_CfgStateDiagStateInfoType;

/*! A diagnostic entity complete execution pre-conditions package */
struct DCM_CFGSTATEPRECONDITIONINFOTYPE_TAG
{
#if (DCM_MODEMGR_CHECK_SUPPORT_ENABLED == STD_ON)
  Dcm_CfgModeMgrRuleRefMemType         ModeRuleRef;   /*!< Reference to Dcm_CfgModeMgrRules[] entry */
#endif
  Dcm_CfgStateDiagStateInfoType        States;        /*!< A diagnostic state related pre-condition package */
};
typedef struct DCM_CFGSTATEPRECONDITIONINFOTYPE_TAG Dcm_CfgStatePreconditionInfoType;

/*! Diagnostic session configuration package */
struct DCM_CFGSTATESESSIONINFOTYPE_TAG
{
  Dcm_DiagP2TimingsType                     P2ServerTime;   /*!< Diagnostic session specific P2 timings */
  Rte_ModeType_DcmDiagnosticSessionControl  Mode;           /*!< The diagnostic session state related mode of the mode declaration group DcmDiagnosticSession */
  uint8                                     Value;          /*!< The diagnostic session state ID (i.e. the sub-function of SID 0x10) */
};
typedef struct DCM_CFGSTATESESSIONINFOTYPE_TAG Dcm_CfgStateSessionInfoType;

/*! Security access level configuration package */
struct DCM_CFGSTATESECURITYINFOTYPE_TAG
{
#if (DCM_STATE_SEC_RETRY_ENABLED == STD_ON)
  Dcm_TmrTimerCntrMemType          DelayTimeInvKey;    /*!< The delay time in case of received invalid key (always >0: specific time) */
# if (DCM_STATE_SEC_DELAY_ON_BOOT_ENABLED == STD_ON)
  Dcm_TmrTimerCntrMemType          DelayTimeOnBoot;    /*!< The delay time each time the ECU (re-)starts (i.e. after reset or power down) */
# endif
  Dcm_TmrTimerCntrMemType          ReloadTime;         /*!< The delay time to be used when a Xxx_GetAttemptCounter API fails to report the stored attempt counter value (0: infinity/no delay (see ReloadOnZeroDelay), >0: specific time) */
  boolean                          ReloadOnZeroDelay;  /*!< Determines the meaning of the "ReloadTime == 0": TRUE - the delay time is infinity, FALSE - no delay time required */
  uint8                            NumAttempts;        /*!< The maximum number of attempts to send a valid key */
#endif
  uint8                            Value;              /*!< The security access level state ID (i.e. equals to "(seed/key sub-function ID + 1) / 2" */
#if (DCM_MODE_SECURITY_ACCESS_ENABLED == STD_ON)
  Rte_ModeType_DcmSecurityAccess   Mode;               /*!< The security access level state related mode of the mode declaration group DcmSecurityAccess */
#endif
};
typedef struct DCM_CFGSTATESECURITYINFOTYPE_TAG Dcm_CfgStateSecurityInfoType;

/*! Function pointer prototype for a diagnostic state transition notification */
typedef P2FUNC(void, DCM_CALLOUT_CODE, Dcm_StateChangeIndicationFuncType)(uint8 formerStateId /* IN: former state ID */
                                                                         ,uint8 newStateId /* IN: new state ID */);

/*! Diagnostic state transition notification item configuration package */
struct DCM_CFGSTATENOTIFICATIONINFOTYPE_TAG
{
  Dcm_StateChangeIndicationFuncType      OnChgFunc; /*!< Pointer to a function of kind <UserDefined function per ECUC>() */
};
typedef struct DCM_CFGSTATENOTIFICATIONINFOTYPE_TAG Dcm_CfgStateNotificationInfoType;
typedef P2CONST(Dcm_CfgStateNotificationInfoType, TYPEDEF, DCM_CONST) Dcm_CfgStateNotificationInfoPtrType;
/*! Depends on the size of Dcm_CfgDidMgrDidOpInfo table */
typedef uint8 Dcm_CfgDidMgrOpHandleMemType;
/*! Depends on the size of Dcm_CfgDidMgrDidOpInfo table */
typedef uint8_least Dcm_CfgDidMgrOpHandleOptType;
/*! Depends on the size of Dcm_CfgDidMgrDidOpClassInfo table */
typedef uint8 Dcm_CfgDidMgrDidOpClassHandleMemType;
/*! Depends on the size of Dcm_CfgDidMgrDidOpClassInfo table */
typedef uint8_least Dcm_CfgDidMgrDidOpClassHandleOptType;
/*! Depends on the size of Dcm_CfgDidMgrDidInfo table */
typedef uint8 Dcm_CfgDidMgrDidInfoRefType;
/*! Depends on the size of Dcm_CfgDidMgrDidOpInfo table */
typedef uint8 Dcm_CfgDidMgrAbstractOpRefType;
/*! Depends on the size of the table Dcm_CfgDidMgrOpInfoIoControl */
typedef uint8 Dcm_CfgDidMgrCombinedOpRefType;
/*! Depends on the number of the defined dynamic DIDs */
typedef uint8 Dcm_CfgDidMgrDynDidHandleMemType;
/*! Depends on the number of the defined dynamic DIDs */
typedef uint8_least Dcm_CfgDidMgrDynDidHandleOptType;
/*! Depends on the summation of max number of elements (static DIDs) of all defined dynamic DIDs */
typedef uint8 Dcm_CfgDidMgrDynDidSrcItemIdxMemType;
/*! Depends on the summation of max number of elements (static DIDs) of all defined dynamic DIDs */
typedef uint8_least Dcm_CfgDidMgrDynDidSrcItemIdxOptType;
/*! Depends on the number of IO DIDs */
typedef uint8 Dcm_CfgDidMgrIoDidHandleMemType;
/*! Depends on the number of IO DIDs */
typedef uint8_least Dcm_CfgDidMgrIoDidHandleOptType;
/*! Depends on the size of Dcm_CfgDidMgrSignalOpClassInfo table */
typedef uint8 Dcm_CfgDidMgrSignalOpClassRefMemType;
/*! Depends on the size of Dcm_CfgDidMgrSignalOpClassInfo table */
typedef uint8_least Dcm_CfgDidMgrSignalOpClassRefOptType;
/*! Depends on the maximum number of signals register to a DID */
typedef uint8 Dcm_CfgDidMgrSignalIterMemType;
/*! Depends on the maximum number of signals register to a DID */
typedef uint8_least Dcm_CfgDidMgrSignalIterOptType;
/*! Depends on the size in bytes of the largest control enable mask record either internally or externally */
typedef uint8 Dcm_CfgDidMgrIoDidCemrLengthMemType;
/*! Depends on the size in bytes of the largest control enable mask record either internally or externally */
typedef uint8_least Dcm_CfgDidMgrIoDidCemrLengthOptType;
/*! Depends on the size of DcmCfg_SupportedDIDInfoPool table */
typedef uint8 Dcm_CfgDidMgrSupportedDIDRefType;
/*! Always generated as uint16 */
typedef uint16 Dcm_DidMgrDidLengthType;
/*! Always generated as uint16 */
typedef uint16 Dcm_CfgDidMgrSignalLengthType;
/*! If any paged DID is enalbed, it shall be mapped to Dcm_DidMgrDidLengthType. Otherwise, it shall be mapped to Dcm_CfgNetBufferSizeMemType */
typedef Dcm_CfgNetBufferSizeMemType Dcm_CfgDidMgrOptimizedDidLengthType;
/*! depends on the number of IO DIDs with S/R Interface */
typedef uint8 Dcm_CfgDidMgrIoCtrlSRHandlersRefMemType;
/*! depends on the number of IO DIDs with S/R Interface */
typedef uint8_least Dcm_CfgDidMgrIoCtrlSRHandlersRefOptType;
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
typedef Dcm_DidOpType     Dcm_DidMgrOpMemType;
typedef Dcm_DidOpOptType  Dcm_DidMgrOpOptType;
typedef uint8             Dcm_DidMgrOpCallMemType;
typedef uint8_least       Dcm_DidMgrOpCallOptType;
typedef uint16            Dcm_DidMgrOpClassType;
typedef uint8             Dcm_DidMgrRoEEventIdType;

typedef uint8 Dcm_DidMgrIoDidCemrHandlingType;

typedef P2VAR(Dcm_DidMgrDidLengthType,TYPEDEF,DCM_VAR_NOINIT) Dcm_DidMgrDidLengthPtrType;

typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_DidMgrOpFuncType) (void);

/*! Information about a DID */
struct DCM_DIDMGRDIDINFOTYPE_TAG
{
  Dcm_CfgDidMgrOptimizedDidLengthType  MinLength;      /*!< Minimum length (concrete length for static DIDs) */
  Dcm_CfgDidMgrOptimizedDidLengthType  MaxLength;      /*!< Maximum length (concrete length for static DIDs) */
  Dcm_CfgDidMgrOptimizedDidLengthType  ReservedLength; /*!< Required buffer space to read the DID if needed - otherwise set to 0 */
  Dcm_CfgDidMgrOpHandleMemType         OpBaseIdx;      /*!< Base index of the associated operations */
#if (DCM_DIDMGR_OP_INFO_ANY_ENABLED == STD_ON)
  Dcm_CfgDidMgrAbstractOpRefType       OpRef;          /*!< Reference to operation information table */
#endif
  Dcm_DidMgrOpMemType                  Operations;     /*!< Bitmap of allowed operations */
};
typedef struct DCM_DIDMGRDIDINFOTYPE_TAG Dcm_CfgDidMgrDidInfoType;

#if (DCM_DIDMGR_SR_IO_CONTROL_ENABLED == STD_ON)
# if (DCM_DIDMGR_SR_IO_SHORT_TERM_ADJUSTMENT_ENABLED == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_DidMgrIoCtrlReqCtrlStateWriteFuncType)(Dcm_ReadOnlyMsgType reqData);
# endif
typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_DidMgrIoCtrlReqUnderCtrlReadFuncType)(P2VAR(uint32, AUTOMATIC, DCM_VAR_NOINIT) underControl);
typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_DidMgrIoCtrlReqUnderCtrlWriteFuncType)(uint32 underControl);
typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_DidMgrIoCtrlReqIoOpReqWriteFuncType)(uint8 ioOperation
                                                                                 ,uint32 cemr);
typedef P2FUNC(boolean, DCM_CODE, Dcm_DidMgrIoCtrlResIsUpdatedFuncType)(void);
typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_DidMgrIoCtrlResReadFuncType)(P2VAR(Dcm_IOOperationResponseType, AUTOMATIC, DCM_VAR_NOINIT) ioResponse);

/*! Struct of SR IO-Control handlers */
struct DCM_DIDMGRIOCTRLSRHANDLERSTYPE
{
# if (DCM_DIDMGR_SR_IO_SHORT_TERM_ADJUSTMENT_ENABLED == STD_ON)
  Dcm_DidMgrIoCtrlReqCtrlStateWriteFuncType  IoCtrlReqCtrlStateWrite;    /*!< Handler to transfer data for short term adjustment */
# endif
  Dcm_DidMgrIoCtrlReqUnderCtrlReadFuncType   IoCtrlReqUnderControlRead;  /*!< Handler to read underControl parameter */
  Dcm_DidMgrIoCtrlReqUnderCtrlWriteFuncType  IoCtrlReqUnderControlWrite; /*!< Handler to write underControl parameter */
  Dcm_DidMgrIoCtrlReqIoOpReqWriteFuncType    IoCtrlReqIoOpReqWrite;      /*!< Handler to transfer new IO operation and CEMR */
  Dcm_DidMgrIoCtrlResIsUpdatedFuncType       IoCtrlResIsUpdated;         /*!< Handler to check if isUpdate flag for response is set */
  Dcm_DidMgrIoCtrlResReadFuncType            IoCtrlResRead;              /*!< Handler to read response data and clear isUpdate flag */
};
typedef struct DCM_DIDMGRIOCTRLSRHANDLERSTYPE Dcm_DidMgrIoCtrlSRHandlersType;
typedef P2CONST(Dcm_DidMgrIoCtrlSRHandlersType, TYPEDEF, DCM_CONST) Dcm_DidMgrIoCtrlSRHandlersPtrType;
typedef CONSTP2CONST(Dcm_DidMgrIoCtrlSRHandlersType, TYPEDEF, DCM_CONST) Dcm_DidMgrIoCtrlSRHandlersConstPtrType;
#endif

/*! Information about a DID operation */
struct DCM_DIDMGRDIDOPINFOTYPE_TAG
{
  Dcm_CfgStateRefMemType                 ExecCondRef;   /*!< Reference to execution conditions */
  Dcm_CfgDidMgrDidOpClassHandleMemType   OpTypeBaseIdx; /*!< Base index for operation types */
  Dcm_DidMgrOpCallMemType                CallTypes;     /*!< Bitmap of supported operation types */
};
typedef struct DCM_DIDMGRDIDOPINFOTYPE_TAG Dcm_CfgDidMgrDidOpInfoType;

/*! Information about a DID operation class */
struct DCM_CFGDIDMGRDIDOPCLASSINFOTYPE_TAG
{
  Dcm_CfgDidMgrSignalOpClassRefMemType  OpClassRef; /*!< Reference to a signal operation class information */
};
typedef struct DCM_CFGDIDMGRDIDOPCLASSINFOTYPE_TAG Dcm_CfgDidMgrDidOpClassInfoType;

/*! Information about a signal operation class */
struct DCM_CFGDIDMGRSIGNALOPCLASSINFOTYPE_TAG
{
  Dcm_DidMgrOpFuncType           OpFunc;    /*!< Generic operation function pointer that will be casted to the concrete operation at run-time */
  Dcm_CfgDidMgrSignalLengthType  MinLength; /*!< Minimum length of the signal */
  Dcm_CfgDidMgrSignalLengthType  MaxLength; /*!< Maximum length of the signal */
  Dcm_DidMgrOpClassType          FuncClass; /*!< Operation function class */
};
typedef struct DCM_CFGDIDMGRSIGNALOPCLASSINFOTYPE_TAG Dcm_CfgDidMgrSignalOpClassInfoType;

#if (DCM_DIDMGR_OP_INFO_IOCONTROL_ENABLED == STD_ON)
/*! Information about an IO control operation */
struct DCM_CFGDIDMGRIOCONTROLINFOTYPE_TAG
{
# if (DCM_DIDMGR_OPTYPE_IO_RETCTRL2ECU_ENABLED == STD_ON)
  Dcm_CfgDidMgrDidOpClassHandleMemType  RetCtrlToEcuOpRef;    /*!< Reference to ReturnControlToECU operation */
# endif
# if (DCM_DIDMGR_IODID_EXEC_PRECOND_LIMIT_ENABLED == STD_ON)
  Dcm_CfgStateRefMemType                CtrlExecCondRef;      /*!< Reference to execution conditions */
# endif
# if (DCM_DIDMGR_IO_MASKRECORD_ENABLED == STD_ON)
  Dcm_CfgDidMgrIoDidCemrLengthMemType   CtrlEnblMaskLength;   /*!< Length of the CEMR */
  Dcm_DidMgrIoDidCemrHandlingType       CtrlEnblMaskHandling; /*!< The type of an IO DID control enable mask record handling */
# endif
};
typedef struct DCM_CFGDIDMGRIOCONTROLINFOTYPE_TAG Dcm_CfgDidMgrOpInfoIoControlType;
#endif

#if (DCM_DIDMGR_OP_INFO_DEFINE_ENABLED == STD_ON)
/*! Operation information for definition of DynDID */
struct DCM_CFGDIDMGRDYNDEFINEINFOTYPE_TAG
{
# if (DCM_DIDMGR_PERIODICDYNDID_ENABLED == STD_ON)
  uint16                                  Did;             /*!< DID number */
# endif
# if (DCM_DIDMGR_DYNDID_CLR_ON_STATE_CHG_ENABLED == STD_ON)
  Dcm_CfgStateRefMemType                  ReadExecCondRef; /*!< Reference to execution conditions */
# endif
  Dcm_CfgDidMgrDynDidSrcItemIdxMemType    SrcItemRef;      /*!< Reference to the first source item */
  uint8                                   NumItems;        /*!< Total number of source items */
};
typedef struct DCM_CFGDIDMGRDYNDEFINEINFOTYPE_TAG Dcm_CfgDidMgrOpInfoDefineType;
#endif

#if (DCM_DIDMGR_OP_INFO_COMBINED_ENABLED == STD_ON)
/*! Combined operation information for IO control and response on event */
struct DCM_CFGDIDMGROPINFOCOMBINEDTYPE_TAG
{
  Dcm_CfgDidMgrCombinedOpRefType OpRefIoControl; /*!< Reference to IO control operation information */
  Dcm_CfgDidMgrCombinedOpRefType OpRefRoE;       /*!< Reference to response on event operation information */
};
typedef struct DCM_CFGDIDMGROPINFOCOMBINEDTYPE_TAG Dcm_CfgDidMgrOpInfoCombinedType;
#endif

#if (DCM_DIDMGR_RANGE_SUPPORT_ENABLED == STD_ON)
typedef Dcm_UtiU16RangeType Dcm_CfgDidMgrDidRangeType;
#endif

#if (DCM_DIDMGR_OP_INFO_ROE_ENABLED == STD_ON)
/*! Operation info for response on event */
struct DCM_CFGDIDMGROPROETYPE_TAG
{
  Dcm_DidMgrRoEEventIdType EventId; /*!< The event ID */
};
typedef struct DCM_CFGDIDMGROPROETYPE_TAG Dcm_CfgDidMgrOpInfoRoEType;
#endif
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
typedef uint8 Dcm_CfgRidMgrOpHandleMemType;
typedef uint8_least Dcm_CfgRidMgrOpHandleOptType;
typedef uint8 Dcm_CfgRidMgrSupportedRIDRefType;
typedef uint8 Dcm_CfgRidMgrRoutineInfoByteMemType;
typedef uint8 Dcm_CfgRidMgrInfoHandleMemType;
typedef uint8_least Dcm_CfgRidMgrInfoHandleOptType;
# if (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON)
typedef uint8   Dcm_RidMgrOpType;
typedef uint8   Dcm_RidMgrOpCallType;
/*! Dedicated RID data length data type: all service ports do use 16bit length parameter */
typedef uint16  Dcm_RidMgrRidLengthType;
typedef P2VAR(Dcm_RidMgrRidLengthType, TYPEDEF, DCM_VAR_NOINIT) Dcm_RidMgrRidLengthPtrType;

/*!
 * Generic routine operation function prototype
 * \return DCM_E_OK             - Operation finished with success. Do not call again
 * \return DCM_E_NOT_OK         - Operation failed. Take the NRC from ErrorCode. Do not call again
 * \return DCM_E_PENDING        - Requested job not yet finished, call again.
 * \return DCM_E_FORCE_RCRRP    - Send immediately a RCR-RP response. Call again once transmission confirmed (with or without success)
 */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RidMgrOpFuncType)(void);

/*! Routine identifier related configuration package */
struct DCM_RIDMGRRIDINFOTYPE_TAG
{
  Dcm_CfgRidMgrOpHandleMemType         OpBaseIdx;          /*!< Reference to Dcm_CfgRidMgrOpInfo[] entry */
  Dcm_CfgStateRefMemType               ExecCondRef;        /*!< Execution pre-condition reference */
  Dcm_RidMgrOpType                     Operations;         /*!< Supported RID operations (Valid values: any combination of DCM_RIDMGR_OP_) */
  Dcm_CfgRidMgrRoutineInfoByteMemType  RoutineInfoByte;    /*!< The routine info byte if supported */
};
typedef struct DCM_RIDMGRRIDINFOTYPE_TAG Dcm_CfgRidMgrRidInfoType;

/*! Routine identifier operation related configuration package */
struct DCM_RIDMGROPINFOTYPE_TAG
{
  Dcm_RidMgrOpFuncType         OpFunc;          /*!< Pointer to the function implementation */
  Dcm_RidMgrRidLengthType      ReqMinLength;    /*!< Minimum request length without the only possible last dynamic length signal (does not include RID + SF) */
  Dcm_RidMgrRidLengthType      ReqMaxLength;    /*!< Maximum request length with the only possible last dynamic length signal (does not include RID + SF) */
  Dcm_RidMgrRidLengthType      ResMinLength;    /*!< Minimum response length without the only possible last dynamic length signal (does not include RID + SF) */
  Dcm_RidMgrRidLengthType      ResMaxLength;    /*!< Maximum response length with the only possible last dynamic length signal (does not include RID + SF) */
  Dcm_RidMgrOpCallType         OpType;          /*!< Function prototype descriptor (Valid values: one of DCM_RIDMGR_OPTYPE_ but not DCM_RIDMGR_OPTYPE_NONE) */
};
typedef struct DCM_RIDMGROPINFOTYPE_TAG Dcm_CfgRidMgrOpInfoType;
typedef P2CONST(Dcm_CfgRidMgrOpInfoType, TYPEDEF, DCM_CONST)   Dcm_RidMgrOpInfoPtrType;
# endif /* (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON) */
typedef uint8 Dcm_CfgMemMgrMemAddrType;
typedef uint32 Dcm_CfgMemMgrReqAddrType;
typedef uint32 Dcm_CfgMemMgrReqSizeType;
typedef uint8 Dcm_CfgMemMgrStateRefType;
typedef uint8 Dcm_CfgMemMgrMemMapIdxMemType;
typedef uint8_least Dcm_CfgMemMgrMemMapIdxOptType;
# if (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON)
/*! Memory manager related configuration package, describes a memory block and the characteristic of the memory block */
struct DCM_CFGMEMMGRMEMMAPINFOTYPE_TAG
{
  Dcm_CfgMemMgrStateRefType    ExecCondRefs[DCM_MEMMGR_NUM_MEMORY_OPERATIONS]; /*!< Reference to the Dcm_CfgStatePreconditions[] entry */
  Dcm_CfgMemMgrMemAddrType     StartAddr;                                      /*!< Start address of the memory block */
  Dcm_CfgMemMgrMemAddrType     EndAddr;                                        /*!< End address of the memory block */
};
typedef struct DCM_CFGMEMMGRMEMMAPINFOTYPE_TAG Dcm_CfgMemMgrMemMapInfoType;
typedef P2CONST(Dcm_CfgMemMgrMemMapInfoType, TYPEDEF, DCM_CONST) Dcm_CfgMemMgrMemMapInfoPtrType;

/*! MID related configuration package */
struct DCM_CFGMEMMGRMEMIDINFOTYPE_TAG
{
  Dcm_CfgMemMgrMemMapInfoPtrType MemMapTable;  /*!< Pointer to the memory map table */
  Dcm_CfgMemMgrMemMapIdxMemType  Size;         /*!< Size of the memory map table */
};
typedef struct DCM_CFGMEMMGRMEMIDINFOTYPE_TAG Dcm_CfgMemMgrMemIdInfoType;
typedef P2VAR(Dcm_CfgMemMgrMemIdInfoType, TYPEDEF, AUTOMATIC)   Dcm_CfgMemMgrMemIdInfoPtrType;
typedef P2CONST(Dcm_CfgMemMgrMemIdInfoType, TYPEDEF, AUTOMATIC) Dcm_CfgMemMgrMemIdInfoConstPtrType;
# endif /* (DCM_MEMMGR_SUPPORT_ENABLED == STD_ON) */
/*! Forward declaration of DCM_CONTEXTTYPE_TAG */
struct DCM_CONTEXTTYPE_TAG;
typedef struct DCM_CONTEXTTYPE_TAG Dcm_ContextType;
typedef P2VAR(Dcm_ContextType, TYPEDEF, DCM_VAR_NOINIT) Dcm_ContextPtrType;
/*! Diagnostic request indication notification function handler pointer type (for all Xxx_Indication()) */
typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_DiagIndicationFuncType) (Dcm_MsgItemType sid     /* IN: SID */
                                                                     ,Dcm_ReadOnlyMsgType reqData /* IN: Request data (behind SID byte) */
                                                                     ,uint16 reqDataLen /* IN: Request data length  */
                                                                     ,uint8 reqType  /* IN: Request type (0 - physical, 1- functional) */
                                                                     ,uint16 srcAddr /* IN: Tester SourceAddress */
                                                                     ,Dcm_NegativeResponseCodePtrType nrc /* OUT: ErrorCode */);

/*! Diagnostic response confirmation notification function handler pointer type (for all Xxx_Confirmation()) */
typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_DiagConfirmationFuncType) (Dcm_MsgItemType sid /* IN: SID */
                                                                       ,uint8 reqType  /* IN: Request type (0 - physical, 1- functional) */
                                                                       ,uint16 srcAddr /* IN: Tester SourceAddress */
                                                                       ,Dcm_ConfirmationStatusType confStatus /* IN: Confirmation status */);

/*
 * Diagnostic service handler "class" members:
 */

/*! Constructor (initialization) function prototype */
typedef P2FUNC(void, DCM_CODE, Dcm_DiagSvcInitFuncType) (void);
/*!
 * Processor function prototype
 * \return DCM_E_OK             - Operation finished with success. Do not call again
 * \return DCM_E_NOT_OK         - Operation failed. Take the NRC from ErrorCode. Do not call again
 * \return DCM_E_PENDING        - Requested job not yet finished, call again.
 * \return DCM_E_FORCE_RCRRP    - Send immediately a RCR-RP response. Call again once transmission confirmed (with or without success)
 * \return DCM_E_STOP_REPEATER  - Do not call again.
 * \return DCM_E_PROCESSINGDONE - Depricated return value, equivalent to DCM_E_OK. Shall not be used by any application service processor!
 */
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_DiagSvcProcessorFuncType) (Dcm_ContextPtrType              pContext    /* IN: pContext */
                                                                               ,Dcm_OpStatusType                OpStatus    /* IN: OpStatus */
                                                                               ,Dcm_MsgContextPtrType           pMsgContext /* IN,OUT: pMsgContext */
                                                                               ,Dcm_NegativeResponseCodePtrType ErrorCode   /* OUT: ErrorCode */);
/*! Post-Processor (fast and normal types) function prototype */
typedef P2FUNC(void, DCM_CALLOUT_CODE, Dcm_DiagSvcConfirmationFuncType) (Dcm_ContextPtrType         pContext   /* IN,OUT: pContext */
                                                                        ,Dcm_ConfirmationStatusType confStatus /* IN: Confirmation status */);

/*!
 * Paged-data provider function prototype
 * \return DCM_E_OK                 - Operation finished with success. Do not call again
 * \return DCM_E_NOT_OK             - Operation failed. Take the NRC from ErrorCode. Do not call again
 * \return DCM_E_PENDING            - Some data written/commited. Call again to fill in more data
 * \return DCM_E_BUFFERTOOLOW       - Maximum available space used but was not enough. Call again when some additional free space available
 * \return DCM_E_DATA_READY_PADDING - No more data to be provided. Do not call again. If needed, switch to padding-byte data provider
 */
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_DiagSvcUpdateFuncType) (Dcm_ContextPtrType              pContext      /* IN: Pointer to the context */
                                                                            ,Dcm_OpStatusType                OpStatus      /* IN: OpStatus */
                                                                            ,Dcm_DiagDataContextPtrType      pDataContext  /* IN,OUT: paged-data descriptor */
                                                                            ,Dcm_NegativeResponseCodePtrType ErrorCode     /* OUT: ErrorCode */);
/*! Paged-data job cancelation notification function prototype */
typedef P2FUNC(void, DCM_CALLOUT_CODE, Dcm_DiagSvcCancelFuncType) (Dcm_ContextPtrType pContext /* IN: Pointer to the context */
                                                                  ,Dcm_DiagDataContextPtrType pDataContext /* IN,OUT: paged-data descriptor */);

/*! Diagnostic service properties container in bitmap form (Valid values: DCM_DIAG_SVC_CFG_PROP_*) */
typedef uint8 DcmCfg_DiagServicePropertiesType;

/*! Configuration of a diagnostic service handler */
struct DCM_CFGDIAGSERVICEINFOTYPE_TAG
{
  Dcm_DiagSvcProcessorFuncType      ProcFunc;         /*!< Pointer to the processor function (e.g. Dcm_Service10Processor() or any application specific function name) */
#if (DCM_DIAG_SERVICE_DISPATCHER_ENABLED == STD_ON)
  Dcm_DiagSvcProcessorFuncType      AltProcFunc;      /*!< Pointer to the alternative processor function */
#endif
  DcmCfg_DiagServicePropertiesType  Props;            /*!< Diagnostic service properties (Any combination of DCM_DIAG_SVC_CFG_PROP_*) */
  uint8                             MinLength;        /*!< Minimum request length (excluding the SID byte) to be verified prior calling the service processor (0 - no restrictions, >0 - particular minimum length) */
  uint8                             ConfFuncRef;      /*!< Reference to the Dcm_CfgDiagSvcPostProcessors[] entry */
  uint8                             FastConfFuncRef;  /*!< Reference to the Dcm_CfgDiagSvcPostProcessors[] entry (if exist, fast post-processors are located right behind the normal post-processor) */
#if (DCM_PAGED_BUFFER_ENABLED == STD_ON)
  uint8                             UpdateFuncRef;    /*!< Reference to the Dcm_CfgDiagSvcUpdaters[] entry */
  uint8                             CancelFuncRef;    /*!< Reference to the Dcm_CfgDiagSvcCancellers[] entry */
#endif
};
typedef struct DCM_CFGDIAGSERVICEINFOTYPE_TAG Dcm_CfgDiagServiceInfoType;

/*! Configuration of diagnostic request notification handlers */
struct DCM_CFGDIAGSERVICENOFICATIONINFOTYPE_TAG
{
  Dcm_DiagIndicationFuncType      IndFunc;  /*!< Points to a Xxx_Indication() callout (NULL_PTR - means last pair element in a list) */
  Dcm_DiagConfirmationFuncType    ConfFunc; /*!< Points to a Xxx_Confirmation) callout (NULL_PTR - means last pair element in a list) */
};
typedef struct DCM_CFGDIAGSERVICENOFICATIONINFOTYPE_TAG Dcm_CfgDiagNotificationInfoType;
typedef P2CONST(Dcm_CfgDiagNotificationInfoType, TYPEDEF, DCM_CONST) Dcm_CfgDiagNotificationInfoPtrType;
/*! Depends on the total number of configuration variants */
typedef uint8 Dcm_CfgVarMgrDiagVariantIdMemType;
/*! Depends on the total number of configuration variants */
typedef uint8_least Dcm_CfgVarMgrDiagVariantIdOptType;
/*! Depends on the total number of diagnostic variants */
typedef uint8 Dcm_CfgVarMgrBitSetBaseType;
/*! A set of variants */
typedef Dcm_CfgVarMgrBitSetBaseType Dcm_CfgVarMgrBitSetType[1];
#if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
/* Pointer to a particular network configuration variant */
typedef P2CONST(Dcm_CfgNetVariantInfoType, TYPEDEF, DCM_CONST_PBCFG)  Dcm_CfgVarMgrComVariantType;
#endif

#if (DCM_DIAG_MULTI_SVC_TABLE_ENABLED == STD_ON)
/*! Configuration of the common variant data between network and diagnostic services variant information */
struct DCM_CFGVARMGRBRIDGEVARIANTTYPE_TAG
{
  P2CONST(Dcm_CfgDiagSvc2ProtMapMemType, AUTOMATIC, DCM_CONST_PBCFG) Svc2ProtocolMap; /*!< Points to the "diagnostic service to protocol map" for a particual DCM variant (criterion): Dcm_CfgDiagSvcId2ProtMap[] */
};
typedef struct DCM_CFGVARMGRBRIDGEVARIANTTYPE_TAG Dcm_CfgVarMgrBridgeVariantType;
#endif

#if (DCM_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
/*! Configuration of the common for all PBL variants RAM area */
struct DCM_CFGVARMGRRAMVARIANTTYPE_TAG
{
  Dcm_CfgNetRamVariantInfoType  NetworkRam; /*!< Relocatable RAM for the network sub-component */
};
typedef struct DCM_CFGVARMGRRAMVARIANTTYPE_TAG Dcm_CfgVarMgrRamVariantType;
typedef P2CONST(Dcm_CfgVarMgrRamVariantType, TYPEDEF, DCM_CONST_PBCFG) Dcm_CfgVarMgrRamVariantPtrType;
# if (DCM_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
/*! Diagnostic sub-component post-build-loadable reallocatable shared configuration data */
struct DCM_DIAGROMVARIANTINFOTYPE_TAG
{
  P2CONST(Dcm_CfgVarMgrBitSetType, AUTOMATIC, DCM_CONST_PBCFG) VariantFilter; /*!< Bitset for enabled variants */
};
typedef struct DCM_DIAGROMVARIANTINFOTYPE_TAG Dcm_CfgDiagRomVariantInfoType;
# endif

/*! Configuration of the common ROM (CONST) area for all PBL variants */
struct DCM_CFGVARMGRROMVARIANTTYPE_TAG
{
  Dcm_CfgNetRomVariantInfoType  NetworkRom; /*!< Relocatable ROM for the network sub-component */
# if (DCM_VARMGR_MULTI_SVC_ANY_ENABLED == STD_ON)
  Dcm_CfgDiagRomVariantInfoType DiagRom;    /*!< Relocatable ROM for the diagnostic sub-component */
# endif
};
typedef struct DCM_CFGVARMGRROMVARIANTTYPE_TAG Dcm_CfgVarMgrRomVariantType;
typedef P2CONST(Dcm_CfgVarMgrRomVariantType, TYPEDEF, DCM_CONST_PBCFG) Dcm_CfgVarMgrRomVariantPtrType;
#endif
/*! Container for all PBS/PBL (PBX) variant configuration parameters (a single criterion package): (network-, diagnostic- and common-(bridge)-variant data) */
struct DCM_CONFIGTYPE_TAG
{
#if (DCM_VARMGR_SUPPORT_ENABLED == STD_ON)
# if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
  Dcm_CfgVarMgrComVariantType       ComVariant;       /*!< Contains all network sub-component related variant information (called COM-criteria) */
# endif
# if (DCM_DIAG_MULTI_SVC_TABLE_ENABLED == STD_ON)
  Dcm_CfgVarMgrBridgeVariantType    BridgeVariant;    /*!< Contains all common/shared data (bridge) between COM and CFG variants */
# endif
# if (DCM_VARMGR_MULTI_SVC_ANY_ENABLED == STD_ON)
  Dcm_CfgVarMgrDiagVariantIdMemType DiagVariantId;    /*!< Identifier for the variant */
# endif
# if (DCM_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
  Dcm_CfgVarMgrRamVariantPtrType    RamVariant;       /*!< Relocatable PB RAM */
  Dcm_CfgVarMgrRomVariantPtrType    RomVariant;       /*!< Relocatable PB ROM */
# endif
  /* Generally required elements */
# if (DCM_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
  uint16                            GenOutputType;    /*!< Generator Output Compatibility Version */
  uint16                            FinalMagicNumber; /*!< Configuration structure magic number   */
# endif
#else
  uint8 NoConfig;                                     /*!< In case of PBS with single variant (DCm optimizes the code for pre-compile variant), still a configuration struct is expected by the software environment */
#endif
};
typedef struct DCM_CONFIGTYPE_TAG Dcm_ConfigType;

typedef P2CONST(Dcm_ConfigType, TYPEDEF, DCM_CONST_PBCFG) Dcm_ConfigPtrType;
# if (DCM_SVC_01_SUPPORT_ENABLED == STD_ON)
/*! Function pointer prototype for a PID handler */
typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_Svc01OpFuncType)(Dcm_MsgType Data);

/*! Diagnostic service 0x01 configuration data */
struct DCM_CFGSVC01DATAINFOTYPE_TAG
{
  Dcm_Svc01OpFuncType  OpFunc;    /*!< Pointer to the PID handler */
  uint16               ResLength; /*!< Response data length without PID */
};
typedef struct DCM_CFGSVC01DATAINFOTYPE_TAG Dcm_CfgSvc01ServiceInfoType;
typedef P2CONST(Dcm_CfgSvc01ServiceInfoType, TYPEDEF, DCM_CONST) Dcm_CfgSvc01ServiceInfoPtrType;
# endif /* (DCM_SVC_01_SUPPORT_ENABLED == STD_ON) */
typedef uint8 Dcm_CfgSvc06Mid2TidRefMemType;
typedef uint8_least Dcm_CfgSvc06Mid2TidRefOptType;
# if (DCM_SVC_06_SUPPORT_ENABLED == STD_ON) && (DCM_OBDIDMGR_OBDMID_SUPPORT_BY_DCM_ENABLED == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_Svc06MidTidOpFuncType) (Dcm_OpStatusType opStatus          /* opStatus */
                                                                         ,Dcm_Uint16VarDataPtrType testValue /* testValue */
                                                                         ,Dcm_Uint16VarDataPtrType minValue  /* minValue */
                                                                         , Dcm_Uint16VarDataPtrType maxValue /* maxValue */
                                                                         , Dcm_Uint8VarDataPtrType status    /* status */);

/*! Information type for MIDs and TIDs */
struct DCM_CFGSVC06SERVICEINFOTYPE_TAG
{
  Dcm_Svc06MidTidOpFuncType  OpFunc; /*!< Pointer to the Mid Tid handler */
  uint8                      Uasid;  /*!< Unit and scaling identifier to be put on the tester response */
  uint8                      Tid;    /*!< Tester identifier to be put on the tester response */
};
typedef struct DCM_CFGSVC06SERVICEINFOTYPE_TAG Dcm_CfgSvc06MidTidInfoType;
typedef P2CONST(Dcm_CfgSvc06MidTidInfoType, TYPEDEF, DCM_CONST) Dcm_CfgSvc06MidTidInfoPtrType;
# endif /* (DCM_SVC_06_SUPPORT_ENABLED == STD_ON) && (DCM_OBDIDMGR_OBDMID_SUPPORT_BY_DCM_ENABLED == STD_ON) */
# if (DCM_SVC_08_SUPPORT_ENABLED == STD_ON)
/*! Function pointer prototype for a Request-Control handler */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_Svc08OpFuncType) (Dcm_MsgType resData, Dcm_ReadOnlyMsgType reqData);

/*! Diagnostic service 0x08 configuration data */
struct DCM_CFGSVC08SERVICEINFOTYPE_TAG
{
  Dcm_Svc08OpFuncType OpFunc;     /*!< Pointer to the Request-Control handler */
  uint16              ReqLength;  /*!< Request data length without TID */
  uint16              ResLength;  /*!< Response data length without TID */
};
typedef struct DCM_CFGSVC08SERVICEINFOTYPE_TAG Dcm_CfgSvc08ServiceInfoType;
typedef P2CONST(Dcm_CfgSvc08ServiceInfoType, TYPEDEF, DCM_CONST)  Dcm_CfgSvc08ServiceInfoPtrType;
# endif /* (DCM_SVC_08_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_09_SUPPORT_ENABLED == STD_ON)
/*! Function pointer prototype for a VID handler */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_Svc09OpFuncType) (Dcm_OpStatusType opStatus
                                                                   ,Dcm_MsgType DataValueBuffer
#if (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
                                                                   ,Dcm_Uint8VarDataPtrType DataValueBufferSize
#endif
                                                                   );

/*! Diagnostic service 0x09 configuration data */
struct DCM_CFGSVC09SERVICEINFOTYPE_TAG
{
  Dcm_Svc09OpFuncType OpFunc;     /*!< Pointer to the VID handler */
  uint8               ResLength;  /*!< Response data length without VID */
};
typedef struct DCM_CFGSVC09SERVICEINFOTYPE_TAG Dcm_CfgSvc09ServiceInfoType;
typedef P2CONST(Dcm_CfgSvc09ServiceInfoType, TYPEDEF, DCM_CONST) Dcm_CfgSvc09ServiceInfoPtrType;
# endif /* (DCM_SVC_09_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_10_SUPPORT_ENABLED == STD_ON) /* COV_DCM_SUPPORT_ALWAYS TX */
/*! Diagnostic service 0x10 sub-function (diagnostic session) configuration data */
struct DCM_CFGSVC10SUBFUNCINFOTYPE_TAG
{
  Dcm_Svc10P2TimingsType   ResponseTime;    /*!< P2 timings to be reported in the positive response */
#if (DCM_SVC_10_JMP2BOOT_ENABLED == STD_ON)
  Dcm_Svc10SessionBootType BootType;        /*!< Bootloader interaction type (Valid values: DCM_SVC10_BOOT_TYPE_*) */
#endif
};
typedef struct DCM_CFGSVC10SUBFUNCINFOTYPE_TAG Dcm_CfgSvc10SubFuncInfoType;
# endif /* (DCM_SVC_10_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_11_SUPPORT_ENABLED == STD_ON)
/*! Diagnostic service 0x11 sub-function information */
struct DCM_CFGSVC11SUBFUNCINFOTYPE_TAG
{
  Dcm_DiagSvcProcessorFuncType      SubSvcFunc; /*!< The sub function processor */
};
typedef struct DCM_CFGSVC11SUBFUNCINFOTYPE_TAG Dcm_CfgSvc11SubFuncInfoType;
# endif /* (DCM_SVC_11_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_19_SUPPORT_ENABLED == STD_ON)
/*! Diagnostic service 0x19 sub-function configuration data */
struct DCM_CFGSVC19SUBFUNCINFOTYPE_TAG
{
  Dcm_DiagSvcProcessorFuncType      SubSvcFunc; /*!< Pointer to the sub-function handler */
  uint8                             ReqLength;  /*!< Diagnostic service request length (sub-function and data): 0 - dynamic length, !=0 - concrete length (no ISO 14229-1 SF is longer than 255 bytes) */
};
typedef struct DCM_CFGSVC19SUBFUNCINFOTYPE_TAG Dcm_CfgSvc19SubFuncInfoType;
# endif /* (DCM_SVC_19_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_27_SUPPORT_ENABLED == STD_ON)
typedef uint8 Dcm_Svc27OpClassType;

/*! Generic function pointer prototype for a Get-Seed handler */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_Svc27GetSeedFuncType)(void);

/*! Function pointer prototype for a Compare-Key handler */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_Svc27CompareKeyFuncType)(Dcm_ReadOnlyMsgType reqData
                                                                          ,Dcm_OpStatusType opStatus
                                                                          ,Dcm_NegativeResponseCodePtrType nrc);

#if (DCM_STATE_SEC_ATT_CNTR_EXT_STORAGE_ENABLED == STD_ON)
/*! Function pointer prototype for a Get-Security-Attempt-Counter handler */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_Svc27GetAttemptCntrFuncType)(Dcm_OpStatusType opStatus
                                                                              ,P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) attemptCount);

/*! Function pointer prototype for a Set-Security-Attempt-Counter handler */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_Svc27SetAttemptCntrFuncType)(Dcm_OpStatusType opStatus
                                                                              ,uint8 attemptCount);
#endif

/*! Diagnostic service 0x27 sub-function configuration data */
struct DCM_CFGSVC27SUBFUNCINFOTYPE_TAG
{
  Dcm_CfgNetBufferSizeMemType       ReqLength;   /*!< Request length (for seed: SF + ADR_size, for key: SF + key_size) */
};
typedef struct DCM_CFGSVC27SUBFUNCINFOTYPE_TAG Dcm_CfgSvc27SubFuncInfoType;

/*! Security level specific configuration data */
struct DCM_CFGSVC27SECLEVELINFOTYPE_TAG
{
  Dcm_Svc27GetSeedFuncType         GetSeedFunc;         /*!< Pointer to the Get-Seed handler */
  Dcm_Svc27CompareKeyFuncType      CompareKeyFunc;      /*!< Pointer to the Compare-Key handler */
#if (DCM_STATE_SEC_ATT_CNTR_EXT_STORAGE_ENABLED == STD_ON)
  Dcm_Svc27GetAttemptCntrFuncType  GetAttemptCntrFunc;  /*!< Pointer to the Get-Security-Attempt-Counter handler */
  Dcm_Svc27SetAttemptCntrFuncType  SetAttemptCntrFunc;  /*!< Pointer to the Set-Security-Attempt-Counter handler */
#endif
  Dcm_CfgNetBufferSizeMemType      SeedResLength;       /*!< Seed response length */
  Dcm_Svc27OpClassType             GetSeedFuncClass;    /*!< Get-Seed function prototyp descriptor */
};
typedef struct DCM_CFGSVC27SECLEVELINFOTYPE_TAG Dcm_CfgSvc27SecLevelInfoType;
# endif /* (DCM_SVC_27_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_28_SUPPORT_ENABLED == STD_ON)
/*! Diagnostic service 0x28 sub-function configuration data */
struct DCM_CFGSVC28SUBFUNCINFOTYPE_TAG
{
  Dcm_DiagSvcProcessorFuncType      SubSvcFunc; /*!< Pointer to the sub-function handler */
  uint8                             ReqLength;  /*!< Diagnostic service request length (sub-function and data): 0 - dynamic length, !=0 - concrete length (no ISO 14229-1 SF is longer than 255 bytes) */
};
typedef struct DCM_CFGSVC28SUBFUNCINFOTYPE_TAG Dcm_CfgSvc28SubFuncInfoType;
# endif /* (DCM_SVC_28_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON)
/*! Diagnostic service 0x2C sub-function configuration data */
struct DCM_CFGSVC2CSUBFUNCINFOTYPE_TAG
{
  Dcm_DiagSvcProcessorFuncType SubSvcFunc;   /*!< The sub function processor */
  Dcm_CfgNetBufferSizeMemType  MinReqLength; /*!< Minimum length of a request */
};
typedef struct DCM_CFGSVC2CSUBFUNCINFOTYPE_TAG Dcm_CfgSvc2CSubFuncInfoType;
# endif /* (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON) */
# if (DCM_SVC_85_SUPPORT_ENABLED == STD_ON)
#if (DCM_DEM_API_430_ENABLED == STD_ON)
typedef P2FUNC(Std_ReturnType, DEM_CODE, Dcm_DemControlDtcSettingFuncType) (uint8 ClientId);
#else
typedef P2FUNC(Dem_ReturnControlDTCSettingType, DEM_CODE, Dcm_DemControlDtcSettingFuncType) (Dem_DTCGroupType DTCGroup, Dem_DTCKindType DTCKind);
#endif

/*! Diagnostic service 0x85 sub-function configuration data */
struct DCM_CFGSVC85SUBFUNCINFOTYPE_TAG
{
  Dcm_DemControlDtcSettingFuncType  DemFunc;  /*!< Pointer to the corresponding DTCsetting state Dem API (e.g. Dem_DcmDisableDTCSetting) */
  Rte_ModeType_DcmControlDtcSetting Mode;     /*!< The corresponding mode of the DTCsetting state (Valid values: RTE_MODE_DcmControlDtcSetting_*) */
};
typedef struct DCM_CFGSVC85SUBFUNCINFOTYPE_TAG Dcm_CfgSvc85SubFuncInfoType;
# endif /* (DCM_SVC_85_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Module internal API function declarations
---------------------------------------------- */
# define DCM_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DidMgrDidNoOp()
 *********************************************************************************************************************/
/*! \brief          Does nothing.
 *  \details        Placeholder for a signal operation which requires no action.
 *  \return         DCM_E_OK
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrDidNoOp(void);

#if (DCM_DIDMGR_NVM_READ_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DidMgrReadNvMSignal()
 *********************************************************************************************************************/
/*! \brief          Handler to read out a NvRam Block.
 *  \details        -
 *  \param[in]      opStatus    The operation status
 *  \param[out]     data        Response data buffer
 *  \param[in]      blockId     Id of the NvRam block
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrNvMReadSignal(Dcm_OpStatusType opStatus
                                                      ,Dcm_MsgType      data
                                                      ,uint16           blockId);
#endif

#if (DCM_DIDMGR_NVM_WRITE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_DidMgrNvMWriteSignal()
 *********************************************************************************************************************/
/*! \brief          Handler to write a NvRam block.
 *  \details        -
 *  \param[in]      data         Request data buffer
 *  \param[in]      opStatus     The operation status
 *  \param[out]     errorCode    The NRC
 *  \param[in]      blockId      Id of the NvRam block
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrNvMWriteSignal(Dcm_ReadOnlyMsgType             data
                                                       ,Dcm_OpStatusType                opStatus
                                                       ,Dcm_NegativeResponseCodePtrType errorCode
                                                       ,uint16                          blockId);
#endif

#if (DCM_DIDMGR_SR_IO_CONTROL_ENABLED == STD_ON)
/**********************************************************************************************************************
*  Dcm_DidMgrIoCtrlSRHandler_Control()
*********************************************************************************************************************/
/*! \brief          Handler for IO Dids with S/R Interface.
 *  \details        Handler for IO Dids with S/R Interface and operation type resetToDefault (0x01), freezeCurrentState(0x02)
 *                  or shortTermAdjustment (0x03)
 *  \param[in]      srEntryIndex    Index to table with corresponding RTE S/R callouts
 *  \param[in]      ioOperation     IO Operation type (InputOutputControlParameter of Service 0x02F)
 *  \param[in]      reqData         Request data containing the controlState in case of IO Operation shortTermAdjustment (0x03)
 *  \param[in]      opStatus        The operation status
 *  \param[in]      cemr            Control Enable Mask Record
 *  \param[out]     errorCode       The NRC
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
*********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrIoCtrlSRHandler_Control(Dcm_CfgDidMgrIoCtrlSRHandlersRefOptType srEntryIndex
                                                                ,uint8                                   ioOperation
                                                                ,Dcm_ReadOnlyMsgType                     reqData
                                                                ,Dcm_OpStatusType                        opStatus
                                                                ,uint32                                  cemr
                                                                ,Dcm_NegativeResponseCodePtrType         errorCode);
#endif

#if (DCM_DIDMGR_SR_IO_CONTROL_ENABLED == STD_ON)
/**********************************************************************************************************************
*  Dcm_DidMgrIoCtrlSRHandler_Reset()
*********************************************************************************************************************/
/*! \brief          Handler for IO Dids with S/R Interface.
 *  \details        Handler for IO Dids with S/R Interface and operation type retrunControlToEcu (0x00)
 *  \param[in]      srEntryIndex    Index to table with corresponding RTE S/R callouts
 *  \param[in]      cemr            Control Enable Mask Record
 *  \param[out]     errorCode       The NRC
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
*********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrIoCtrlSRHandler_Reset(Dcm_CfgDidMgrIoCtrlSRHandlersRefOptType srEntryIndex
                                                              ,uint32                                  cemr
                                                              ,Dcm_NegativeResponseCodePtrType         errorCode);
#endif
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_OBDUDSIDMGR_SUPPORT_ENABLED == STD_ON)
#if (DCM_VARMGR_MULTI_SVC_ANY_ENABLED == STD_ON) && \
    (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ObdIdMgrGetDidAvailabilityMask()
 *********************************************************************************************************************/
/*! \brief          OBD availability DID (AID) mask value provider.
 *  \details        Calculates the 32bit mask value for PBS/PBL/CALIBRATABLE_OBD and pre-compile
 *  \param[in]      DidLookUpRefStart    The index of the first element in the DID look-up table the AID shall report.
 *  \param[in]      DidLookUpRefEnd      The index of the last element in the DID look-up table the AID shall report.
 *  \param[in]      maskValue            The offline generated/calibratable mask value
 *  \return         The 32 bit bitmap value
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(uint32, DCM_CODE) Dcm_ObdIdMgrGetDidAvailabilityMask(uint16 DidLookUpRefStart
                                                         ,uint16 DidLookUpRefEnd
                                                         ,Dcm_ObdIdMgrMaskValueTableType maskValue);
#else
/* Just return the offline calculated/calibrated mask */
# define Dcm_ObdIdMgrGetDidAvailabilityMask(DidLookUpRefStart, DidLookUpRefEnd, maskValue) (maskValue)                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif

#if (DCM_VARMGR_MULTI_SVC_ANY_ENABLED == STD_ON) && \
    (DCM_RIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ObdIdMgrGetRidAvailabilityMask()
 *********************************************************************************************************************/
/*! \brief          OBD availability RID (AID) mask value provider.
 *  \details        Calculates the 32bit mask value for PBS/PBL/CALIBRATABLE_OBD and pre-compile
 *  \param[in]      RidLookUpRefStart    The index of the first element in the RID look-up table the AID shall report.
 *  \param[in]      RidLookUpRefEnd      The index of the last element in the RID look-up table the AID shall report.
 *  \param[in]      maskValue            The offline generated/calibratable mask value
 *  \return         The 32 bit bitmap value
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(uint32, DCM_CODE) Dcm_ObdIdMgrGetRidAvailabilityMask(uint16 RidLookUpRefStart
                                                         ,uint16 RidLookUpRefEnd
                                                         ,Dcm_ObdIdMgrMaskValueTableType maskValue);
#else
/* Just return the offline calculated/calibrated mask */
# define Dcm_ObdIdMgrGetRidAvailabilityMask(RidLookUpRefStart, RidLookUpRefEnd, maskValue) (maskValue)                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif

#if (DCM_OBDUDSIDMGR_UDSMID_SUPPORT_BY_DCM_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ObdIdMgrReadUdsMid()
 *********************************************************************************************************************/
/*! \brief          OBD Service "supported ID" reader.
 *  \details        -
 *  \param[in]      handle      The handle
 *  \param[in]      opStatus    The operation status
 *  \param[in]      pDataContext Pointer to the data context
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_ObdIdMgrReadUdsMid(Dcm_ObdIdMgrHandleMemType handle
                                                     ,Dcm_OpStatusType opStatus
                                                     ,Dcm_DiagDataContextPtrType pDataContext);
#endif
# endif /* (DCM_OBDUDSIDMGR_SUPPORT_ENABLED == STD_ON) */
/***********************************************************************************************************************
 *  Dcm_Service27Init()
***********************************************************************************************************************/
/*! \brief         Initializes service 0x27 processing.
 *  \details       -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \pre           -
***********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_Service27Init(void);
# if (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON)
#if (DCM_DIDMGR_DYNDID_SRCITEM_CHECK_COND_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_Svc2CDefMgrConditionCheckRead()
 *********************************************************************************************************************/
/*! \brief          Common DynDID check read condition operation.
 *  \details        -
 *  \param[in]      dynDidHandle    DynDID reference to be read
 *  \param[in]      opStatus        Current operation status
 *  \param[out]     errorCode       Returns an error if any
 *  \return         Next action to perform
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc2CDefMgrConditionCheckRead(Dcm_CfgDidMgrDynDidHandleMemType dynDidHandle
                                                                ,Dcm_OpStatusType opStatus
                                                                ,Dcm_NegativeResponseCodePtrType errorCode);
#endif
/**********************************************************************************************************************
 *  Dcm_Svc2CDefMgrRead()
 *********************************************************************************************************************/
/*! \brief          Common DynDID reader operation.
 *  \details        -
 *  \param[in]      dynDidHandle    DynDID reference to be read
 *  \param[in]      opStatus        Current operation status
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \return         Next action to perform
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc2CDefMgrRead(Dcm_CfgDidMgrDynDidHandleMemType dynDidHandle
                                                  ,Dcm_OpStatusType opStatus
                                                  ,Dcm_DiagDataContextPtrType pDataContext);

/**********************************************************************************************************************
 *  Dcm_Svc2CDefMgrReadDataLength()
 *********************************************************************************************************************/
/*! \brief          Common DynDID reader operation.
 *  \details        -
 *  \param[in]      dynDidHandle    DynDID reference to be read
 *  \param[out]     dataLength      Returns the current DynDID length
 *  \return         Next action to perform
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Svc2CDefMgrReadDataLength(Dcm_CfgDidMgrDynDidHandleMemType dynDidHandle
                                                            ,Dcm_DidMgrDidLengthPtrType dataLength);
# endif /* (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   Call-back function declarations
---------------------------------------------- */
# define DCM_START_SEC_CALLOUT_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
#if (DCM_PAGED_BUFFER_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_PagedBufferDataPadding()
 *********************************************************************************************************************/
/*! \brief          A sub-function utility of readDtcInfo.
 *  \details        This function is used for data padding.
 *  \param[in]      pContext              Pointer to the context
 *  \param[in]      opStatus              The operation status
 *  \param[in,out]  pDataContext          Pointer to the data context
 *  \param[out]     ErrorCode             The NRC
 *  \return         DCM_E_BUFFERTOOLOW    Enforce transmission of the current part
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_PagedBufferDataPadding(Dcm_ContextPtrType              pContext
                                                                 ,Dcm_OpStatusType                opStatus
                                                                 ,Dcm_DiagDataContextPtrType      pDataContext
                                                                 ,Dcm_NegativeResponseCodePtrType ErrorCode);
#endif
/***********************************************************************************************************************
 *  CallbackUDSsecurity()
***********************************************************************************************************************/
/*! \brief         This function will be called at a security access level state transition.
 *  \details       -
 *  \param[in]     formerState  Specifies the former security access level ID (source state of transition)
 *  \param[in]     newState     Specifies the new security access level ID (target state of transition)
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 *  \note          The function argument values have the same definition as the ones returned by the API
 *                 Dcm_GetSecurityLevel().
***********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) CallbackUDSsecurity(Dcm_SecLevelType formerState, Dcm_SecLevelType newState);
/***********************************************************************************************************************
 *  Dcm_Service10Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK           Job processing finished, send positive response
 *  \return        DCM_E_PENDING      Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service10Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service11Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK           Job processing finished, send positive response
 *  \return        DCM_E_PENDING      Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service11Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service14Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK           Job processing finished, send positive response
 *  \return        DCM_E_PENDING      Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service14Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service19Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK           Job processing finished, send positive response
 *  \return        DCM_E_PENDING      Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service19Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service22Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK           Job processing finished, send positive response
 *  \return        DCM_E_PENDING      Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service22Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service27Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK           Job processing finished, send positive response
 *  \return        DCM_E_PENDING      Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service27Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service28Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK           Job processing finished, send positive response
 *  \return        DCM_E_PENDING      Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service28Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service2EProcessor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK           Job processing finished, send positive response
 *  \return        DCM_E_PENDING      Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service2EProcessor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service31Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK           Job processing finished, send positive response
 *  \return        DCM_E_PENDING      Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service31Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service3EProcessor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK           Job processing finished, send positive response
 *  \return        DCM_E_PENDING      Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service3EProcessor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service85Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK           Job processing finished, send positive response
 *  \return        DCM_E_PENDING      Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        DCM_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service85Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service10PostProcessor()
***********************************************************************************************************************/
/*! \brief         Finalizes the service processing.
 *  \details       Triggers a mode switch, performs a state transition or executes other actions depending on the
 *                 concrete diagnostic service.
 *  \param[in]     pContext  Pointer to the context
 *  \param[in]     status    The post-processing status
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Service10PostProcessor(Dcm_ContextPtrType pContext, Dcm_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  Dcm_Service10FastPostProcessor()
***********************************************************************************************************************/
/*! \brief         Finalizes the service processing.
 *  \details       Processes time critical diagnostic service specific operations immediately after confirmation of
 *                 service processing.
 *  \param[in]     pContext  Pointer to the context
 *  \param[in]     status    The post-processing status
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Service10FastPostProcessor(Dcm_ContextPtrType pContext, Dcm_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  Dcm_Service11PostProcessor()
***********************************************************************************************************************/
/*! \brief         Finalizes the service processing.
 *  \details       Triggers a mode switch, performs a state transition or executes other actions depending on the
 *                 concrete diagnostic service.
 *  \param[in]     pContext  Pointer to the context
 *  \param[in]     status    The post-processing status
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Service11PostProcessor(Dcm_ContextPtrType pContext, Dcm_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  Dcm_Service11FastPostProcessor()
***********************************************************************************************************************/
/*! \brief         Finalizes the service processing.
 *  \details       Processes time critical diagnostic service specific operations immediately after confirmation of
 *                 service processing.
 *  \param[in]     pContext  Pointer to the context
 *  \param[in]     status    The post-processing status
 *  \context       ISR1|ISR2
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Service11FastPostProcessor(Dcm_ContextPtrType pContext, Dcm_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  Dcm_Service19PostProcessor()
***********************************************************************************************************************/
/*! \brief         Finalizes the service processing.
 *  \details       Triggers a mode switch, performs a state transition or executes other actions depending on the
 *                 concrete diagnostic service.
 *  \param[in]     pContext  Pointer to the context
 *  \param[in]     status    The post-processing status
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Service19PostProcessor(Dcm_ContextPtrType pContext, Dcm_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  Dcm_Service27PostProcessor()
***********************************************************************************************************************/
/*! \brief         Finalizes the service processing.
 *  \details       Triggers a mode switch, performs a state transition or executes other actions depending on the
 *                 concrete diagnostic service.
 *  \param[in]     pContext  Pointer to the context
 *  \param[in]     status    The post-processing status
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Service27PostProcessor(Dcm_ContextPtrType pContext, Dcm_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  Dcm_Service28PostProcessor()
***********************************************************************************************************************/
/*! \brief         Finalizes the service processing.
 *  \details       Triggers a mode switch, performs a state transition or executes other actions depending on the
 *                 concrete diagnostic service.
 *  \param[in]     pContext  Pointer to the context
 *  \param[in]     status    The post-processing status
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Service28PostProcessor(Dcm_ContextPtrType pContext, Dcm_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  Dcm_Service85PostProcessor()
***********************************************************************************************************************/
/*! \brief         Finalizes the service processing.
 *  \details       Triggers a mode switch, performs a state transition or executes other actions depending on the
 *                 concrete diagnostic service.
 *  \param[in]     pContext  Pointer to the context
 *  \param[in]     status    The post-processing status
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Service85PostProcessor(Dcm_ContextPtrType pContext, Dcm_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  Dcm_Service19Updater()
***********************************************************************************************************************/
/*! \brief         Provides service specific data to the paged buffer.
 *  \details       -
 *  \param[in]     pContext                  Pointer to the context
 *  \param[in]     opStatus                  The operation status
 *  \param[in,out] pDataContext              Pointer to the data context
 *  \param[out]    ErrorCode                 Negative response code
 *  \return        DCM_E_OK                  Operation finished with success. Do not call again
 *  \return        DCM_E_NOT_OK              Operation failed. Take the NRC from ErrorCode. Do not call again
 *  \return        DCM_E_PENDING             Some data written/commited. Call again to fill in more data
 *  \return        DCM_E_BUFFERTOOLOW        Maximum available space used but was not enough.
 *                                           Call again when some additional free space available
 *  \return        DCM_E_DATA_READY_PADDING  No more data to be provided.
 *                                           Do not call again. If needed, switch to padding-byte data provider
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service19Updater(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_DiagDataContextPtrType pDataContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_RepeaterDeadEnd()
***********************************************************************************************************************/
/*! \brief         Dummy repeater proxy.
 *  \details       -
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *  \param[out]    ErrorCode            Negative response code
 *  \return        DCM_E_STOP_REPEATER  Stops the repeater proxy
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_RepeaterDeadEnd(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service11_01Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic sub-service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic sub-service, configured to be
 *                 handled by a CDD, is received. All of the relevant diagnostic request parameter information is
 *                 forwarded by DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSubService/DcmDsdSubServiceFnc.
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *                                      The pointers in pMsgContext points behind the sub-function.
 *  \param[out]    ErrorCode            Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK             Job processing finished, send positive response
 *  \return        DCM_E_PENDING        Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP    (Vendor extension) Forces a RCR-RP response.
 *                                      The call out will called again once the response is sent. The OpStatus parameter
 *                                      will contain the transmission result
 *  \return        DCM_E_STOP_REPEATER  Stops the repeater proxy
 *  \return        DCM_E_NOT_OK         Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service11_01Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service11_03Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic sub-service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic sub-service, configured to be
 *                 handled by a CDD, is received. All of the relevant diagnostic request parameter information is
 *                 forwarded by DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSubService/DcmDsdSubServiceFnc.
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *                                      The pointers in pMsgContext points behind the sub-function.
 *  \param[out]    ErrorCode            Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK             Job processing finished, send positive response
 *  \return        DCM_E_PENDING        Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP    (Vendor extension) Forces a RCR-RP response.
 *                                      The call out will called again once the response is sent. The OpStatus parameter
 *                                      will contain the transmission result
 *  \return        DCM_E_STOP_REPEATER  Stops the repeater proxy
 *  \return        DCM_E_NOT_OK         Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service11_03Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service19_01Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic sub-service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic sub-service, configured to be
 *                 handled by a CDD, is received. All of the relevant diagnostic request parameter information is
 *                 forwarded by DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSubService/DcmDsdSubServiceFnc.
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *                                      The pointers in pMsgContext points behind the sub-function.
 *  \param[out]    ErrorCode            Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK             Job processing finished, send positive response
 *  \return        DCM_E_PENDING        Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP    (Vendor extension) Forces a RCR-RP response.
 *                                      The call out will called again once the response is sent. The OpStatus parameter
 *                                      will contain the transmission result
 *  \return        DCM_E_STOP_REPEATER  Stops the repeater proxy
 *  \return        DCM_E_NOT_OK         Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service19_01Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service19_02Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic sub-service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic sub-service, configured to be
 *                 handled by a CDD, is received. All of the relevant diagnostic request parameter information is
 *                 forwarded by DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSubService/DcmDsdSubServiceFnc.
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *                                      The pointers in pMsgContext points behind the sub-function.
 *  \param[out]    ErrorCode            Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK             Job processing finished, send positive response
 *  \return        DCM_E_PENDING        Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP    (Vendor extension) Forces a RCR-RP response.
 *                                      The call out will called again once the response is sent. The OpStatus parameter
 *                                      will contain the transmission result
 *  \return        DCM_E_STOP_REPEATER  Stops the repeater proxy
 *  \return        DCM_E_NOT_OK         Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service19_02Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service19_06Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic sub-service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic sub-service, configured to be
 *                 handled by a CDD, is received. All of the relevant diagnostic request parameter information is
 *                 forwarded by DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSubService/DcmDsdSubServiceFnc.
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *                                      The pointers in pMsgContext points behind the sub-function.
 *  \param[out]    ErrorCode            Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK             Job processing finished, send positive response
 *  \return        DCM_E_PENDING        Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP    (Vendor extension) Forces a RCR-RP response.
 *                                      The call out will called again once the response is sent. The OpStatus parameter
 *                                      will contain the transmission result
 *  \return        DCM_E_STOP_REPEATER  Stops the repeater proxy
 *  \return        DCM_E_NOT_OK         Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service19_06Processor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service19_0AProcessor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic sub-service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic sub-service, configured to be
 *                 handled by a CDD, is received. All of the relevant diagnostic request parameter information is
 *                 forwarded by DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSubService/DcmDsdSubServiceFnc.
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *                                      The pointers in pMsgContext points behind the sub-function.
 *  \param[out]    ErrorCode            Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK             Job processing finished, send positive response
 *  \return        DCM_E_PENDING        Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP    (Vendor extension) Forces a RCR-RP response.
 *                                      The call out will called again once the response is sent. The OpStatus parameter
 *                                      will contain the transmission result
 *  \return        DCM_E_STOP_REPEATER  Stops the repeater proxy
 *  \return        DCM_E_NOT_OK         Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service19_0AProcessor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  Dcm_Service28_XXProcessor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic sub-service request.
 *  \details       DCM calls a function of this kind as soon as a supported diagnostic sub-service, configured to be
 *                 handled by a CDD, is received. All of the relevant diagnostic request parameter information is
 *                 forwarded by DCM through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/Dcm/DcmConfigSet/DcmDsd/DcmDsdServiceTable/DcmDsdService/DcmDsdSubService/DcmDsdSubServiceFnc.
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *                                      The pointers in pMsgContext points behind the sub-function.
 *  \param[out]    ErrorCode            Negative response code in case return value is DCM_E_NOT_OK
 *  \return        DCM_E_OK             Job processing finished, send positive response
 *  \return        DCM_E_PENDING        Job processing is not yet finished
 *  \return        DCM_E_FORCE_RCRRP    (Vendor extension) Forces a RCR-RP response.
 *                                      The call out will called again once the response is sent. The OpStatus parameter
 *                                      will contain the transmission result
 *  \return        DCM_E_STOP_REPEATER  Stops the repeater proxy
 *  \return        DCM_E_NOT_OK         Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Service28_XXProcessor(Dcm_ContextPtrType pContext, Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode);
# define DCM_STOP_SEC_CALLOUT_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   ROM 8-Bit
---------------------------------------------- */
# define DCM_START_SEC_CONST_8
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*! TxPduId to DCM connection map */
extern CONST(Dcm_NetConnRefMemType, DCM_CONST) Dcm_CfgNetTxPduInfo[1];
/*! Map of DCM relevant network handles */
extern CONST(Dcm_CfgNetNetIdRefMemType, DCM_CONST) Dcm_CfgNetConnComMChannelMap[1];
/*! Service 0x28 list of channels for the all-comm-channel parameter */
extern CONST(Dcm_CfgNetNetIdRefMemType, DCM_CONST) Dcm_CfgNetComCtrlChannelListAll[2];
/*! Look up table of DCM service identifiers */
extern CONST(uint8, DCM_CONST) Dcm_CfgDiagSvcIdLookUpTable[12];
/*! Service 0x10 look up table  */
extern CONST(uint8, DCM_CONST) Dcm_CfgSvc10SubFuncLookUpTable[4];
/*! Service 0x11 look up table  */
extern CONST(uint8, DCM_CONST) Dcm_CfgSvc11SubFuncLookUpTable[3];
/*! Service 0x19 look up table  */
extern CONST(uint8, DCM_CONST) Dcm_CfgSvc19SubFuncLookUpTable[5];
/*! Service 0x27 look up table  */
extern CONST(uint8, DCM_CONST) Dcm_CfgSvc27SubFuncLookUpTable[7];
/*! Service 0x28 look up table  */
extern CONST(uint8, DCM_CONST) Dcm_CfgSvc28SubFuncLookUpTable[5];
/*! Service 0x28 look up table  */
extern CONST(uint8, DCM_CONST) Dcm_CfgSvc28MessageTypeLookUpTable[4];
/*! Service 0x28 network ID lookup */
extern CONST(uint8, DCM_CONST) Dcm_CfgSvc28SubNetIdLookUp[3];
/*! Service 0x3E look up table  */
extern CONST(uint8, DCM_CONST) Dcm_CfgSvc3ESubFuncLookUpTable[2];
/*! Look up table of service 0x85 */
extern CONST(uint8, DCM_CONST) Dcm_CfgSvc85SubFuncLookUpTable[3];
# define DCM_STOP_SEC_CONST_8
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   ROM 16-Bit
---------------------------------------------- */
# define DCM_START_SEC_CONST_16
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*! DID look up table  */
extern CONST(uint16, DCM_CONST) Dcm_CfgDidMgrDidLookUpTable[29];
/*! RID look up table  */
extern CONST(uint16, DCM_CONST) Dcm_CfgRidMgrRidLookUpTable[3];
# define DCM_STOP_SEC_CONST_16
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   ROM of unspecified size
---------------------------------------------- */
# define DCM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*! DCM buffer descriptor */
extern CONST(Dcm_CfgNetBufferInfoType, DCM_CONST) Dcm_CfgNetBufferInfo[1];
/*! RxPduId map */
extern CONST(Dcm_CfgNetRxPduInfoType, DCM_CONST) Dcm_CfgNetRxPduInfo[2];
/*! DCM connection descriptor */
extern CONST(Dcm_CfgNetConnectionInfoType, DCM_CONST) Dcm_CfgNetConnectionInfo[1];
/*! DCM protocol descriptor */
extern CONST(Dcm_CfgNetProtocolInfoType, DCM_CONST) Dcm_CfgNetProtocolInfo[1];
/*! Map of all relevant for DCM network handles */
extern CONST(NetworkHandleType, DCM_CONST) Dcm_CfgNetAllComMChannelMap[1];
/*! Look up table of DCM relevant network handles */
extern CONST(NetworkHandleType, DCM_CONST) Dcm_CfgNetNetworkHandleLookUpTable[2];
/*! Diagnostic service execution conditions */
extern CONST(Dcm_CfgStatePreconditionInfoType, DCM_CONST) Dcm_CfgStatePreconditions[9];
/*! Session state properties */
extern CONST(Dcm_CfgStateSessionInfoType, DCM_CONST) Dcm_CfgStateSessionInfo[3];
/*! Security Access state properties */
extern CONST(Dcm_CfgStateSecurityInfoType, DCM_CONST) Dcm_CfgStateSecurityInfo[3];
/*! Security state change notification(s) */
extern CONST(Dcm_CfgStateNotificationInfoType, DCM_CONST) Dcm_CfgStateSecurityNotificationInfo[2];
/*! DID properties */
extern CONST(Dcm_CfgDidMgrDidInfoType, DCM_CONST) Dcm_CfgDidMgrDidInfo[28];
/*! DID operation properties */
extern CONST(Dcm_CfgDidMgrDidOpInfoType, DCM_CONST) Dcm_CfgDidMgrDidOpInfo[40];
/*! DID operation classes */
extern CONST(Dcm_CfgDidMgrDidOpClassInfoType, DCM_CONST) Dcm_CfgDidMgrDidOpClassInfo[77];
/*! DID signal operation classes */
extern CONST(Dcm_CfgDidMgrSignalOpClassInfoType, DCM_CONST) Dcm_CfgDidMgrSignalOpClassInfo[76];
/*! RID properties */
extern CONST(Dcm_CfgRidMgrRidInfoType, DCM_CONST) Dcm_CfgRidMgrRidInfo[2];
/*! RID operation properties */
extern CONST(Dcm_CfgRidMgrOpInfoType, DCM_CONST) Dcm_CfgRidMgrOpInfo[3];
/*! DCM service initializers */
extern CONST(Dcm_DiagSvcInitFuncType, DCM_CONST) Dcm_CfgDiagSvcInitializers[2];
/*! DCM service properties */
extern CONST(Dcm_CfgDiagServiceInfoType, DCM_CONST) Dcm_CfgDiagServiceInfo[12];
/*! Indirection from diag service info to execution pre conditions */
extern CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgDiagSvcIdExecPrecondTable[11];
/*! DCM service post processors */
extern CONST(Dcm_DiagSvcConfirmationFuncType, DCM_CONST) Dcm_CfgDiagSvcPostProcessors[9];
/*! DCM service paged buffer updater */
extern CONST(Dcm_DiagSvcUpdateFuncType, DCM_CONST) Dcm_CfgDiagSvcUpdaters[3];
/*! DCM service paged buffer canceller */
extern CONST(Dcm_DiagSvcCancelFuncType, DCM_CONST) Dcm_CfgDiagSvcCancellers[1];
/*! Service 0x10 sub-service properties table  */
extern CONST(Dcm_CfgSvc10SubFuncInfoType, DCM_CONST) Dcm_CfgSvc10SubFuncInfo[3];
/*! Indirection from service 0x10 sub functions to execution pre conditions */
extern CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc10SubFuncExecPrecondTable[3];
/*! Service 0x11 sub-service properties table  */
extern CONST(Dcm_CfgSvc11SubFuncInfoType, DCM_CONST) Dcm_CfgSvc11SubFuncInfo[2];
/*! Indirection from service 0x11 sub functions to execution pre conditions */
extern CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc11SubFuncExecPrecondTable[2];
/*! Service 0x19 sub-service properties table  */
extern CONST(Dcm_CfgSvc19SubFuncInfoType, DCM_CONST) Dcm_CfgSvc19SubFuncInfo[4];
/*! Indirection from service 0x19 sub functions to execution pre conditions */
extern CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc19SubFuncExecPrecondTable[4];
/*! Service 0x27 sub-service properties table  */
extern CONST(Dcm_CfgSvc27SubFuncInfoType, DCM_CONST) Dcm_CfgSvc27SubFuncInfo[6];
/*! Service 0x27 security level properties table  */
extern CONST(Dcm_CfgSvc27SecLevelInfoType, DCM_CONST) Dcm_CfgSvc27SecLevelInfo[3];
/*! Indirection from service 0x27 sub functions to execution pre conditions */
extern CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc27SubFuncExecPrecondTable[6];
/*! Service 0x28 sub-service properties table  */
extern CONST(Dcm_CfgSvc28SubFuncInfoType, DCM_CONST) Dcm_CfgSvc28SubFuncInfo[4];
/*! Indirection from service 0x28 sub functions to execution pre conditions */
extern CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc28SubFuncExecPrecondTable[4];
/*! Service 0x28 network ID to ComM channel map */
extern CONST(NetworkHandleType, DCM_CONST) Dcm_CfgSvc28SubNetIdMap[2];
/*! Indirection from service 0x3E sub functions to execution pre conditions */
extern CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc3ESubFuncExecPrecondTable[1];
/*! Indirection from service 0x85 sub functions to execution pre conditions */
extern CONST(Dcm_CfgStateRefMemType, DCM_CONST) Dcm_CfgSvc85SubFuncExecPrecondTable[2];
/*! DCM service 0x85 properties */
extern CONST(Dcm_CfgSvc85SubFuncInfoType, DCM_CONST) Dcm_CfgSvc85SubFuncInfo[2];
# define DCM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
#endif /* !defined(DCM_LCFG_H) */
/* ********************************************************************************************************************
 * END OF FILE: Dcm_Lcfg.h
 * ******************************************************************************************************************** */

