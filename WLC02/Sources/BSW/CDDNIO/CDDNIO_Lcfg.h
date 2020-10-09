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
 *              File: CDD_Lcfg.h
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



#if !defined(CDDNIO_LCFG_H)
# define CDDNIO_LCFG_H
/* ----------------------------------------------
 ~&&&   Includes
---------------------------------------------- */

/* ----------------------------------------------
 ~&&&   Versions
---------------------------------------------- */

/*! Implementation version */
# define CDD_LCFG_MAJOR_VERSION                                                11u
# define CDD_LCFG_MINOR_VERSION                                                 6u
# define CDD_LCFG_PATCH_VERSION                                                 0u
/* ----------------------------------------------
 ~&&&   Switches
---------------------------------------------- */
# if (CDD_DIDMGR_SUPPORT_ENABLED == STD_ON)
/*! Specifies whether the CDD_CfgDidMgrOpInfoIoControlType structure is required */
#if (CDD_DIDMGR_OPTYPE_IO_RETCTRL2ECU_ENABLED == STD_ON) || \
    (CDD_DIDMGR_IODID_EXEC_PRECOND_LIMIT_ENABLED == STD_ON) || \
    (CDD_DIDMGR_IO_MASKRECORD_ENABLED == STD_ON)
# define CDD_DIDMGR_OP_INFO_IOCONTROL_ENABLED                        STD_ON
#else
# define CDD_DIDMGR_OP_INFO_IOCONTROL_ENABLED                        STD_OFF
#endif
# endif /* (CDD_DIDMGR_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Typedefs Exported Level 2
---------------------------------------------- */
# if (CDD_MODEMGR_SUPPORT_ENABLED == STD_ON) /* COV_CDD_SUPPORT_ALWAYS TX */
/*! Mode-rule handler function prototype */
/* ----------------------------------------------
 ~&&&   Typedefs
---------------------------------------------- */
typedef uint8 CDD_OpStatusType;
typedef uint8 CDD_ProtocolType;

typedef uint8       CDD_DidOpMemType;
typedef uint8_least CDD_DidOpOptType;

typedef CDD_DidOpMemType CDD_DidOpType;
typedef uint8 CDD_ConfirmationStatusType;
typedef uint8 CDD_ControlDtcSettingType;
typedef uint8 CDD_DiagnosticSessionControlType;
typedef uint8 CDD_EcuResetType;
typedef uint8 CDD_RequestKindType;
typedef uint8 CDD_SecLevelType;
typedef uint8 CDD_SesCtrlType;
/*! Depends on the largest configured buffer size */
typedef uint16 CDD_CfgNetBufferSizeMemType;
/*! Depends on the largest configured buffer size */
typedef uint16_least CDD_CfgNetBufferSizeOptType;
/*! Function pointer prototype for a protocol activation notification */
typedef P2FUNC(Std_ReturnType, CDD_CODE, CDD_NetProtocolIndicationFuncType) (CDD_ProtocolType newProtocol /* IN: new ProtocolId */);

/*! Diagnostic protocol related notification functions */
struct CDD_CFGNETPROTOCOLNOTIFICATIONINFOTYPE_TAG
{
  CDD_NetProtocolIndicationFuncType    StartFunc;  /*!< Pointer to a function of kind Xxx_StartProtocol() */
};
typedef struct CDD_CFGNETPROTOCOLNOTIFICATIONINFOTYPE_TAG CDD_CfgNetProtocolNotificationInfoType;
/*! Zero based reference to a USDT buffer configuration entry (0..31) */
typedef uint8        CDD_CfgNetBufferRefMemType;
typedef uint8_least  CDD_CfgNetBufferRefOptType;

/*! Zero based reference to a ComM channel map entry (0..255) */
typedef uint8        CDD_CfgNetNetIdRefMemType;
typedef uint8_least  CDD_CfgNetNetIdRefOptType;

/*! Zero based reference to a USDT message transport object (0..31) */
typedef uint8        CDD_CfgNetTObjHandleMemType;
typedef uint8_least  CDD_CfgNetTObjHandleOptType;

/*! Zero based reference to a UUDT message transport object (0..255) */
typedef uint8        CDD_CfgNetPTxObjHandleMemType;
typedef uint8_least  CDD_CfgNetPTxObjHandleOptType;

/*! Diagnostic protocol priority (0..255) */
typedef uint8        CDD_CfgNetProtPrioType;

/*! Diagnostic protocol maximum length (0..65535) */
typedef uint16       CDD_CfgNetProtLengthType;

/*! Zero based reference to a UUDT message CDDTxPduId configuration entry (0..255) */
typedef uint8        CDD_CfgNetPerTxPduIdRefMemType;
typedef uint8_least  CDD_CfgNetPerTxPduIdRefOptType;

/*! Diagnostic client connection properties (Valid values: CDD_NET_CONN_PROP_*) */
typedef uint8        CDD_CfgNetConnPropertiesType;

/*! Diagnostic client connection UUDT frame size (0..4294967295) */
typedef PduLengthType CDD_UudtFrameSizeType;

/*! Configuration of a USDT buffer */
struct CDD_CFGNETBUFFERINFOTYPE_TAG
{
  CDD_PbConstMsgType            BufferPtr;  /*!< Pointer to a USDT buffer */
  CDD_CfgNetBufferSizeMemType   Size;       /*!< Size of this specific USDT buffer */
};
typedef struct CDD_CFGNETBUFFERINFOTYPE_TAG CDD_CfgNetBufferInfoType;

/*! Configuration of a CDDRxPduId */
struct CDD_CFGNETRXPDUINFOTYPE_TAG
{
  boolean                   IsFuncReq;  /*!< Functional request message: FALSE = physical, TRUE = functional */
  CDD_NetConnRefMemType     ConnRef;    /*!< Reference to CDD_CfgNetConnectionInfo[] entry */
};
typedef struct CDD_CFGNETRXPDUINFOTYPE_TAG CDD_CfgNetRxPduInfoType;

/*! Configuration of a diagnostic client connection */
struct CDD_CFGNETCONNECTIONTYPE_TAG
{
  uint16                          ClientSrcAddr;          /*!< Diagnostic client's unique source address (identifier) */
  PduIdType                       TxPduIdMain;            /*!< PduR's PduId of the main diagnostic response */
  CDD_CfgNetNetIdRefMemType       NetworkIdRef;           /*!< Reference to CDD_CfgNetConnComMChannelMap[] entry */
  CDD_NetProtRefMemType           ProtRef;                /*!< Reference to CDD_PbCfgNetProtocolInfo[] entry */
};
typedef struct CDD_CFGNETCONNECTIONTYPE_TAG CDD_CfgNetConnectionInfoType;

/*! Configuration of a diagnostic client protocol */
struct CDD_CFGNETPROTOCOLTYPE_TAG
{
  CDD_DiagP2TimingsType       SrvAdjTime;         /*!< The P2 times to be used for all diagnostic clients associated with this diagnostic protocol */
  CDD_CfgNetProtLengthType    MaxLength;          /*!< Maximum allowed request/response length for all connections within this diagnostic protocol */
  CDD_ProtocolType            Id;                 /*!< The diagnostic protocol name (e.g. UDS_ON_CAN) */
  boolean                     HasRespPendOnBoot;  /*!< Specifies whether RCR-RP shall be sent prior jump to the boot-loader (TRUE - do send RCR-RP prior jump to FBL, FALSE - do not send) */
  CDD_CfgNetBufferRefMemType  RxTxBufferRef;      /*!< Reference to CDD_PbCfgNetBufferInfo[] entry */
  uint8                       ThreadId;           /*!< The active Thread ID */
};
typedef struct CDD_CFGNETPROTOCOLTYPE_TAG CDD_CfgNetProtocolInfoType;
typedef uint8  CDD_NetTransportObjectStateType;
typedef uint16 CDD_NetTransportObjectFlagType;
typedef uint8  CDD_NetResponseType;
typedef uint8  CDD_NetComMStateType;

/*! Control data of the USDT message buffers (main and additional) */
struct CDD_NETBUFFERCONTEXTTYPE_TAG
{
  volatile uint8  IsInUseCnt; /*!< Usage counter (0 - not in use, >0 - buffer in use from at least one user) */
};
typedef struct CDD_NETBUFFERCONTEXTTYPE_TAG CDD_NetBufferContextType;

/*! Transport object control data */
struct CDD_NETTRANSPORTOBJECTTYPE_TAG
{
  CDD_ReadOnlyMsgType             RxData;                                  /*!< Pointer to the buffer to store the request data (can be the main buffer or an additional buffer) */
  CDD_NetTransportObjectFlagType  Flags;                                   /*!< Control flags of a transport object (Multiple combination of CDD_NET_TOBJ_FLAG_*) */
  CDD_CfgNetBufferSizeMemType     RxLength;                                /*!< The diagnostic request length */
  CDD_CfgNetBufferSizeMemType     BuffPos;                                 /*!< Keeps track of where to copy the next received diagnostic message data portion */
  PduIdType                       RxPduId;                                 /*!< CDDRxPduId used to allocate the transport object */
  CDD_NetResponseType             ResType;                                 /*!< The diagnostic response type (e.g. RCR-RP, final (not-)paged etc.) */
  CDD_CfgNetTObjHandleMemType     Handle;                                  /*!< The transport object ID */
  CDD_NetConnRefMemType           ConnId;                                  /*!< Reference to CDD_PbCfgNetConnectionInfo[] entry */
  CDD_CfgNetBufferRefMemType      BufferHdl;                               /*!< Reference to CDD_PbRamNetBufferContext[] entry */
  volatile CDD_NetTransportObjectStateType State;                          /*!< State of the transport object (Valid values: CDD_NET_TOBJ_STATE_*) */
  CDD_MsgItemType                 AddBuffer[CDD_NET_TOBJ_ADDBUFFER_SIZE];  /*!< Temporary buffer for NRC 0x78 and 0x21 responses and 0x3E 0x80 functional requests (optional sepcific cause code) */
  PduInfoType                     BuffInfo;                                /*!< PduR transmission data information exchange */
};
typedef struct CDD_NETTRANSPORTOBJECTTYPE_TAG CDD_NetTransportObjectType;

/*! ComM channel related control information */
struct CDD_NETCOMMCONTEXT_TAG
{
  CDD_NetComMStateType   ComState;            /*!< The current state of the ComM channel (FullCom/SilentCom/NoCom) */
  CDD_NetConnRefMemType  RegisteredNetworks;  /*!< Number of active USDT diagnostic client connections on certain ComM channel */
};
typedef struct CDD_NETCOMMCONTEXT_TAG CDD_NetComMContextType;



/*! Depends on the mode rule table size */
typedef uint8 CDD_CfgModeMgrRuleRefMemType;
/*! Depends on the mode rule table size */
typedef uint8_least CDD_CfgModeMgrRuleRefOptType;
/*! Depends on the state group with largest number of states */
typedef uint8 CDD_CfgStateGroupMemType;
/*! Depends on the state group with largest number of states */
typedef uint8_least CDD_CfgStateGroupOptType;
/*! Depends on the total number of diagnostic service state/mode filters */
typedef uint8 CDD_CfgStateRefMemType;
/*! Depends on the total number of diagnostic service state/mode filters */
typedef uint8_least CDD_CfgStateRefOptType;
/*! Depends on the total number of security fixed byte values in non-default security levels */
typedef uint8 CDD_CfgStateSecurityFixedByteRefMemType;
/*! Depends on the total number of security fixed byte values in non-default security levels */
typedef uint8_least CDD_CfgStateSecurityFixedByteRefOptType;
/*! Depends on the how many Fixed byte sets are configured per a security level */
typedef uint8 CDD_CfgStateVsgSecurityFixedByteInfoRefMemType;
/*! Depends on the how many Fixed byte sets are configured per a security level */
typedef uint8_least CDD_CfgStateVsgSecurityFixedByteInfoRefOptType;
/*! A diagnostic entity diagnostic state related execution pre-conditions package */
struct CDD_CFGSTATEPRECONDITIONTYPE_TAG
{
  CDD_CfgStateGroupMemType Session;   /*!< Diagnostic session pre-condition(s) (Bitmap) */
#if (CDD_STATE_SECURITY_ENABLED == STD_ON)
  CDD_CfgStateGroupMemType Security;  /*!< Security access pre-condition(s) (Bitmap) */
#endif
};
typedef struct CDD_CFGSTATEPRECONDITIONTYPE_TAG CDD_CfgStateDiagStateInfoType;

/*! A diagnostic entity complete execution pre-conditions package */
struct CDD_CFGSTATEPRECONDITIONINFOTYPE_TAG
{
#if (CDD_MODEMGR_CHECK_SUPPORT_ENABLED == STD_ON)
  CDD_CfgModeMgrRuleRefMemType         ModeRuleRef;   /*!< Reference to CDD_CfgModeMgrRules[] entry */
#endif
  CDD_CfgStateDiagStateInfoType        States;        /*!< A diagnostic state related pre-condition package */
};
typedef struct CDD_CFGSTATEPRECONDITIONINFOTYPE_TAG CDD_CfgStatePreconditionInfoType;




/*! Function pointer prototype for a diagnostic state transition notification */
typedef P2FUNC(void, CDD_CALLOUT_CODE, CDD_StateChangeIndicationFuncType)(uint8 formerStateId /* IN: former state ID */
                                                                         ,uint8 newStateId /* IN: new state ID */);

/*! Diagnostic state transition notification item configuration package */
struct CDD_CFGSTATENOTIFICATIONINFOTYPE_TAG
{
  CDD_StateChangeIndicationFuncType      OnChgFunc; /*!< Pointer to a function of kind <UserDefined function per ECUC>() */
};
typedef struct CDD_CFGSTATENOTIFICATIONINFOTYPE_TAG CDD_CfgStateNotificationInfoType;
typedef P2CONST(CDD_CfgStateNotificationInfoType, TYPEDEF, CDD_CONST) CDD_CfgStateNotificationInfoPtrType;
/*! Depends on the size of CDD_CfgDidMgrDidOpInfo table */
typedef uint8 CDD_CfgDidMgrOpHandleMemType;
/*! Depends on the size of CDD_CfgDidMgrDidOpInfo table */
typedef uint8_least CDD_CfgDidMgrOpHandleOptType;
/*! Depends on the size of CDD_CfgDidMgrDidOpClassInfo table */
typedef uint8 CDD_CfgDidMgrDidOpClassHandleMemType;
/*! Depends on the size of CDD_CfgDidMgrDidOpClassInfo table */
typedef uint8_least CDD_CfgDidMgrDidOpClassHandleOptType;
/*! Depends on the size of CDD_CfgDidMgrDidInfo table */
typedef uint8 CDD_CfgDidMgrDidInfoRefType;
/*! Depends on the size of CDD_CfgDidMgrDidOpInfo table */
typedef uint8 CDD_CfgDidMgrAbstractOpRefType;
/*! Depends on the size of the table CDD_CfgDidMgrOpInfoIoControl */
typedef uint8 CDD_CfgDidMgrCombinedOpRefType;
/*! Depends on the number of the defined dynamic DIDs */
typedef uint8 CDD_CfgDidMgrDynDidHandleMemType;
/*! Depends on the number of the defined dynamic DIDs */
typedef uint8_least CDD_CfgDidMgrDynDidHandleOptType;
/*! Depends on the summation of max number of elements (static DIDs) of all defined dynamic DIDs */
typedef uint8 CDD_CfgDidMgrDynDidSrcItemIdxMemType;
/*! Depends on the summation of max number of elements (static DIDs) of all defined dynamic DIDs */
typedef uint8_least CDD_CfgDidMgrDynDidSrcItemIdxOptType;
/*! Depends on the number of IO DIDs */
typedef uint8 CDD_CfgDidMgrIoDidHandleMemType;
/*! Depends on the number of IO DIDs */
typedef uint8_least CDD_CfgDidMgrIoDidHandleOptType;
/*! Depends on the size of CDD_CfgDidMgrSignalOpClassInfo table */
typedef uint8 CDD_CfgDidMgrSignalOpClassRefMemType;
/*! Depends on the size of CDD_CfgDidMgrSignalOpClassInfo table */
typedef uint8_least CDD_CfgDidMgrSignalOpClassRefOptType;
/*! Depends on the maximum number of signals register to a DID */
typedef uint8 CDD_CfgDidMgrSignalIterMemType;
/*! Depends on the maximum number of signals register to a DID */
typedef uint8_least CDD_CfgDidMgrSignalIterOptType;
/*! Depends on the size in bytes of the largest control enable mask record either internally or externally */
typedef uint8 CDD_CfgDidMgrIoDidCemrLengthMemType;
/*! Depends on the size in bytes of the largest control enable mask record either internally or externally */
typedef uint8_least CDD_CfgDidMgrIoDidCemrLengthOptType;
/*! Depends on the size of CDDCfg_SupportedDIDInfoPool table */
typedef uint8 CDD_CfgDidMgrSupportedDIDRefType;
/*! Always generated as uint16 */
typedef uint16 CDD_DidMgrDidLengthType;
/*! Always generated as uint16 */
typedef uint16 CDD_CfgDidMgrSignalLengthType;
/*! If any paged DID is enalbed, it shall be mapped to CDD_DidMgrDidLengthType. Otherwise, it shall be mapped to CDD_CfgNetBufferSizeMemType */
typedef CDD_CfgNetBufferSizeMemType CDD_CfgDidMgrOptimizedDidLengthType;
/*! depends on the number of IO DIDs with S/R Interface */
typedef uint8 CDD_CfgDidMgrIoCtrlSRHandlersRefMemType;
/*! depends on the number of IO DIDs with S/R Interface */
typedef uint8_least CDD_CfgDidMgrIoCtrlSRHandlersRefOptType;
# if (CDD_DIDMGR_SUPPORT_ENABLED == STD_ON)
typedef CDD_DidOpType     CDD_DidMgrOpMemType;
typedef CDD_DidOpOptType  CDD_DidMgrOpOptType;
typedef uint8             CDD_DidMgrOpCallMemType;
typedef uint8_least       CDD_DidMgrOpCallOptType;
typedef uint16            CDD_DidMgrOpClassType;
typedef uint8             CDD_DidMgrRoEEventIdType;

typedef uint8 CDD_DidMgrIoDidCemrHandlingType;

typedef P2VAR(CDD_DidMgrDidLengthType,TYPEDEF,CDD_VAR_NOINIT) CDD_DidMgrDidLengthPtrType;

typedef P2FUNC(Std_ReturnType, CDD_APPL_CODE, CDD_DidMgrOpFuncType) (void);

/*! Information about a DID */
struct CDD_DIDMGRDIDINFOTYPE_TAG
{
  CDD_CfgDidMgrOptimizedDidLengthType  MinLength;      /*!< Minimum length (concrete length for static DIDs) */
  CDD_CfgDidMgrOptimizedDidLengthType  MaxLength;      /*!< Maximum length (concrete length for static DIDs) */
  CDD_CfgDidMgrOptimizedDidLengthType  ReservedLength; /*!< Required buffer space to read the DID if needed - otherwise set to 0 */
  CDD_CfgDidMgrOpHandleMemType         OpBaseIdx;      /*!< Base index of the associated operations */
#if (CDD_DIDMGR_OP_INFO_ANY_ENABLED == STD_ON)
  CDD_CfgDidMgrAbstractOpRefType       OpRef;          /*!< Reference to operation information table */
#endif
  CDD_DidMgrOpMemType                  Operations;     /*!< Bitmap of allowed operations */
};
typedef struct CDD_DIDMGRDIDINFOTYPE_TAG CDD_CfgDidMgrDidInfoType;

#if (CDD_DIDMGR_SR_IO_CONTROL_ENABLED == STD_ON)
# if (CDD_DIDMGR_SR_IO_SHORT_TERM_ADJUSTMENT_ENABLED == STD_ON)
typedef P2FUNC(Std_ReturnType, CDD_CODE, CDD_DidMgrIoCtrlReqCtrlStateWriteFuncType)(CDD_ReadOnlyMsgType reqData);
# endif
typedef P2FUNC(Std_ReturnType, CDD_CODE, CDD_DidMgrIoCtrlReqUnderCtrlReadFuncType)(P2VAR(uint32, AUTOMATIC, CDD_VAR_NOINIT) underControl);
typedef P2FUNC(Std_ReturnType, CDD_CODE, CDD_DidMgrIoCtrlReqUnderCtrlWriteFuncType)(uint32 underControl);
typedef P2FUNC(Std_ReturnType, CDD_CODE, CDD_DidMgrIoCtrlReqIoOpReqWriteFuncType)(uint8 ioOperation
                                                                                 ,uint32 cemr);
typedef P2FUNC(boolean, CDD_CODE, CDD_DidMgrIoCtrlResIsUpdatedFuncType)(void);
typedef P2FUNC(Std_ReturnType, CDD_CODE, CDD_DidMgrIoCtrlResReadFuncType)(P2VAR(CDD_IOOperationResponseType, AUTOMATIC, CDD_VAR_NOINIT) ioResponse);

/*! Struct of SR IO-Control handlers */
struct CDD_DIDMGRIOCTRLSRHANDLERSTYPE
{
# if (CDD_DIDMGR_SR_IO_SHORT_TERM_ADJUSTMENT_ENABLED == STD_ON)
  CDD_DidMgrIoCtrlReqCtrlStateWriteFuncType  IoCtrlReqCtrlStateWrite;    /*!< Handler to transfer data for short term adjustment */
# endif
  CDD_DidMgrIoCtrlReqUnderCtrlReadFuncType   IoCtrlReqUnderControlRead;  /*!< Handler to read underControl parameter */
  CDD_DidMgrIoCtrlReqUnderCtrlWriteFuncType  IoCtrlReqUnderControlWrite; /*!< Handler to write underControl parameter */
  CDD_DidMgrIoCtrlReqIoOpReqWriteFuncType    IoCtrlReqIoOpReqWrite;      /*!< Handler to transfer new IO operation and CEMR */
  CDD_DidMgrIoCtrlResIsUpdatedFuncType       IoCtrlResIsUpdated;         /*!< Handler to check if isUpdate flag for response is set */
  CDD_DidMgrIoCtrlResReadFuncType            IoCtrlResRead;              /*!< Handler to read response data and clear isUpdate flag */
};
typedef struct CDD_DIDMGRIOCTRLSRHANDLERSTYPE CDD_DidMgrIoCtrlSRHandlersType;
typedef P2CONST(CDD_DidMgrIoCtrlSRHandlersType, TYPEDEF, CDD_CONST) CDD_DidMgrIoCtrlSRHandlersPtrType;
typedef CONSTP2CONST(CDD_DidMgrIoCtrlSRHandlersType, TYPEDEF, CDD_CONST) CDD_DidMgrIoCtrlSRHandlersConstPtrType;
#endif

/*! Information about a DID operation */
struct CDD_DIDMGRDIDOPINFOTYPE_TAG
{
  CDD_CfgStateRefMemType                 ExecCondRef;   /*!< Reference to execution conditions */
  CDD_CfgDidMgrDidOpClassHandleMemType   OpTypeBaseIdx; /*!< Base index for operation types */
  CDD_DidMgrOpCallMemType                CallTypes;     /*!< Bitmap of supported operation types */
};
typedef struct CDD_DIDMGRDIDOPINFOTYPE_TAG CDD_CfgDidMgrDidOpInfoType;

/*! Information about a DID operation class */
struct CDD_CFGDIDMGRDIDOPCLASSINFOTYPE_TAG
{
  CDD_CfgDidMgrSignalOpClassRefMemType  OpClassRef; /*!< Reference to a signal operation class information */
};
typedef struct CDD_CFGDIDMGRDIDOPCLASSINFOTYPE_TAG CDD_CfgDidMgrDidOpClassInfoType;

/*! Information about a signal operation class */
struct CDD_CFGDIDMGRSIGNALOPCLASSINFOTYPE_TAG
{
  CDD_DidMgrOpFuncType           OpFunc;    /*!< Generic operation function pointer that will be casted to the concrete operation at run-time */
};
typedef struct CDD_CFGDIDMGRSIGNALOPCLASSINFOTYPE_TAG CDD_CfgDidMgrSignalOpClassInfoType;

#if (CDD_DIDMGR_OP_INFO_IOCONTROL_ENABLED == STD_ON)
/*! Information about an IO control operation */
struct CDD_CFGDIDMGRIOCONTROLINFOTYPE_TAG
{
# if (CDD_DIDMGR_OPTYPE_IO_RETCTRL2ECU_ENABLED == STD_ON)
  CDD_CfgDidMgrDidOpClassHandleMemType  RetCtrlToEcuOpRef;    /*!< Reference to ReturnControlToECU operation */
# endif
# if (CDD_DIDMGR_IODID_EXEC_PRECOND_LIMIT_ENABLED == STD_ON)
  CDD_CfgStateRefMemType                CtrlExecCondRef;      /*!< Reference to execution conditions */
# endif
# if (CDD_DIDMGR_IO_MASKRECORD_ENABLED == STD_ON)
  CDD_CfgDidMgrIoDidCemrLengthMemType   CtrlEnblMaskLength;   /*!< Length of the CEMR */
  CDD_DidMgrIoDidCemrHandlingType       CtrlEnblMaskHandling; /*!< The type of an IO DID control enable mask record handling */
# endif
};
typedef struct CDD_CFGDIDMGRIOCONTROLINFOTYPE_TAG CDD_CfgDidMgrOpInfoIoControlType;
#endif

#if (CDD_DIDMGR_OP_INFO_DEFINE_ENABLED == STD_ON)
/*! Operation information for definition of DynDID */
struct CDD_CFGDIDMGRDYNDEFINEINFOTYPE_TAG
{
# if (CDD_DIDMGR_PERIODICDYNDID_ENABLED == STD_ON)
  uint16                                  Did;             /*!< DID number */
# endif
# if (CDD_DIDMGR_DYNDID_CLR_ON_STATE_CHG_ENABLED == STD_ON)
  CDD_CfgStateRefMemType                  ReadExecCondRef; /*!< Reference to execution conditions */
# endif
  CDD_CfgDidMgrDynDidSrcItemIdxMemType    SrcItemRef;      /*!< Reference to the first source item */
  uint8                                   NumItems;        /*!< Total number of source items */
};
typedef struct CDD_CFGDIDMGRDYNDEFINEINFOTYPE_TAG CDD_CfgDidMgrOpInfoDefineType;
#endif

#if (CDD_DIDMGR_OP_INFO_COMBINED_ENABLED == STD_ON)
/*! Combined operation information for IO control and response on event */
struct CDD_CFGDIDMGROPINFOCOMBINEDTYPE_TAG
{
  CDD_CfgDidMgrCombinedOpRefType OpRefIoControl; /*!< Reference to IO control operation information */
  CDD_CfgDidMgrCombinedOpRefType OpRefRoE;       /*!< Reference to response on event operation information */
};
typedef struct CDD_CFGDIDMGROPINFOCOMBINEDTYPE_TAG CDD_CfgDidMgrOpInfoCombinedType;
#endif

#if (CDD_DIDMGR_RANGE_SUPPORT_ENABLED == STD_ON)
typedef CDD_UtiU16RangeType CDD_CfgDidMgrDidRangeType;
#endif

#if (CDD_DIDMGR_OP_INFO_ROE_ENABLED == STD_ON)
/*! Operation info for response on event */
struct CDD_CFGDIDMGROPROETYPE_TAG
{
  CDD_DidMgrRoEEventIdType EventId; /*!< The event ID */
};
typedef struct CDD_CFGDIDMGROPROETYPE_TAG CDD_CfgDidMgrOpInfoRoEType;
#endif
# endif /* (CDD_DIDMGR_SUPPORT_ENABLED == STD_ON) */
typedef uint8 CDD_CfgRidMgrOpHandleMemType;
typedef uint8_least CDD_CfgRidMgrOpHandleOptType;
typedef uint8 CDD_CfgRidMgrSupportedRIDRefType;
typedef uint8 CDD_CfgRidMgrRoutineInfoByteMemType;
typedef uint8 CDD_CfgRidMgrInfoHandleMemType;
typedef uint8_least CDD_CfgRidMgrInfoHandleOptType;
# if (CDD_RIDMGR_SUPPORT_ENABLED == STD_ON)
typedef uint8   CDD_RidMgrOpType;
typedef uint8   CDD_RidMgrOpCallType;
/*! Dedicated RID data length data type: all service ports do use 16bit length parameter */
typedef uint16  CDD_RidMgrRidLengthType;
typedef P2VAR(CDD_RidMgrRidLengthType, TYPEDEF, CDD_VAR_NOINIT) CDD_RidMgrRidLengthPtrType;

/*!
 * Generic routine operation function prototype
 * \return CDD_E_OK             - Operation finished with success. Do not call again
 * \return CDD_E_NOT_OK         - Operation failed. Take the NRC from ErrorCode. Do not call again
 * \return CDD_E_PENDING        - Requested job not yet finished, call again.
 * \return CDD_E_FORCE_RCRRP    - Send immediately a RCR-RP response. Call again once transmission confirmed (with or without success)
 */
typedef P2FUNC(Std_ReturnType, CDD_APPL_CODE, CDD_RidMgrOpFuncType)(void);

/*! Routine identifier related configuration package */
struct CDD_RIDMGRRIDINFOTYPE_TAG
{
  CDD_CfgRidMgrOpHandleMemType         OpBaseIdx;          /*!< Reference to CDD_CfgRidMgrOpInfo[] entry */
  CDD_CfgStateRefMemType               ExecCondRef;        /*!< Execution pre-condition reference */
  CDD_RidMgrOpType                     Operations;         /*!< Supported RID operations (Valid values: any combination of CDD_RIDMGR_OP_) */
  CDD_CfgRidMgrRoutineInfoByteMemType  RoutineInfoByte;    /*!< The routine info byte if supported */
};
typedef struct CDD_RIDMGRRIDINFOTYPE_TAG CDD_CfgRidMgrRidInfoType;

/*! Routine identifier operation related configuration package */
struct CDD_RIDMGROPINFOTYPE_TAG
{
  CDD_RidMgrOpFuncType         OpFunc;          /*!< Pointer to the function implementation */
  CDD_RidMgrRidLengthType      ReqMinLength;    /*!< Minimum request length without the only possible last dynamic length signal (does not include RID + SF) */
  CDD_RidMgrRidLengthType      ReqMaxLength;    /*!< Maximum request length with the only possible last dynamic length signal (does not include RID + SF) */
  CDD_RidMgrRidLengthType      ResMinLength;    /*!< Minimum response length without the only possible last dynamic length signal (does not include RID + SF) */
  CDD_RidMgrRidLengthType      ResMaxLength;    /*!< Maximum response length with the only possible last dynamic length signal (does not include RID + SF) */
  CDD_RidMgrOpCallType         OpType;          /*!< Function prototype descriptor (Valid values: one of CDD_RIDMGR_OPTYPE_ but not CDD_RIDMGR_OPTYPE_NONE) */
};
typedef struct CDD_RIDMGROPINFOTYPE_TAG CDD_CfgRidMgrOpInfoType;
typedef P2CONST(CDD_CfgRidMgrOpInfoType, TYPEDEF, CDD_CONST)   CDD_RidMgrOpInfoPtrType;
# endif /* (CDD_RIDMGR_SUPPORT_ENABLED == STD_ON) */
typedef uint8 CDD_CfgMemMgrMemAddrType;
typedef uint32 CDD_CfgMemMgrReqAddrType;
typedef uint32 CDD_CfgMemMgrReqSizeType;
typedef uint8 CDD_CfgMemMgrStateRefType;
typedef uint8 CDD_CfgMemMgrMemMapIdxMemType;
typedef uint8_least CDD_CfgMemMgrMemMapIdxOptType;
# if (CDD_MEMMGR_SUPPORT_ENABLED == STD_ON)
/*! Memory manager related configuration package, describes a memory block and the characteristic of the memory block */
struct CDD_CFGMEMMGRMEMMAPINFOTYPE_TAG
{
  CDD_CfgMemMgrStateRefType    ExecCondRefs[CDD_MEMMGR_NUM_MEMORY_OPERATIONS]; /*!< Reference to the CDD_CfgStatePreconditions[] entry */
  CDD_CfgMemMgrMemAddrType     StartAddr;                                      /*!< Start address of the memory block */
  CDD_CfgMemMgrMemAddrType     EndAddr;                                        /*!< End address of the memory block */
};
typedef struct CDD_CFGMEMMGRMEMMAPINFOTYPE_TAG CDD_CfgMemMgrMemMapInfoType;
typedef P2CONST(CDD_CfgMemMgrMemMapInfoType, TYPEDEF, CDD_CONST) CDD_CfgMemMgrMemMapInfoPtrType;

/*! MID related configuration package */
struct CDD_CFGMEMMGRMEMIDINFOTYPE_TAG
{
  CDD_CfgMemMgrMemMapInfoPtrType MemMapTable;  /*!< Pointer to the memory map table */
  CDD_CfgMemMgrMemMapIdxMemType  Size;         /*!< Size of the memory map table */
};
typedef struct CDD_CFGMEMMGRMEMIDINFOTYPE_TAG CDD_CfgMemMgrMemIdInfoType;
typedef P2VAR(CDD_CfgMemMgrMemIdInfoType, TYPEDEF, AUTOMATIC)   CDD_CfgMemMgrMemIdInfoPtrType;
typedef P2CONST(CDD_CfgMemMgrMemIdInfoType, TYPEDEF, AUTOMATIC) CDD_CfgMemMgrMemIdInfoConstPtrType;
# endif /* (CDD_MEMMGR_SUPPORT_ENABLED == STD_ON) */
/*! Forward declaration of CDD_CONTEXTTYPE_TAG */
struct CDD_CONTEXTTYPE_TAG;
typedef struct CDD_CONTEXTTYPE_TAG CDD_ContextType;
typedef P2VAR(CDD_ContextType, TYPEDEF, CDD_VAR_NOINIT) CDD_ContextPtrType;
/*! Diagnostic request indication notification function handler pointer type (for all Xxx_Indication()) */
typedef P2FUNC(Std_ReturnType, CDD_CODE, CDD_DiagIndicationFuncType) (CDD_MsgItemType sid     /* IN: SID */
                                                                     ,CDD_ReadOnlyMsgType reqData /* IN: Request data (behind SID byte) */
                                                                     ,uint16 reqDataLen /* IN: Request data length  */
                                                                     ,uint8 reqType  /* IN: Request type (0 - physical, 1- functional) */
                                                                     ,uint16 srcAddr /* IN: Tester SourceAddress */
                                                                     ,CDD_NegativeResponseCodePtrType nrc /* OUT: ErrorCode */);

/*! Diagnostic response confirmation notification function handler pointer type (for all Xxx_Confirmation()) */
typedef P2FUNC(Std_ReturnType, CDD_CODE, CDD_DiagConfirmationFuncType) (CDD_MsgItemType sid /* IN: SID */
                                                                       ,uint8 reqType  /* IN: Request type (0 - physical, 1- functional) */
                                                                       ,uint16 srcAddr /* IN: Tester SourceAddress */
                                                                       ,CDD_ConfirmationStatusType confStatus /* IN: Confirmation status */);

/*
 * Diagnostic service handler "class" members:
 */

/*! Constructor (initialization) function prototype */
typedef P2FUNC(void, CDD_CODE, CDD_DiagSvcInitFuncType) (void);
/*!
 * Processor function prototype
 * \return CDD_E_OK             - Operation finished with success. Do not call again
 * \return CDD_E_NOT_OK         - Operation failed. Take the NRC from ErrorCode. Do not call again
 * \return CDD_E_PENDING        - Requested job not yet finished, call again.
 * \return CDD_E_FORCE_RCRRP    - Send immediately a RCR-RP response. Call again once transmission confirmed (with or without success)
 * \return CDD_E_STOP_REPEATER  - Do not call again.
 * \return CDD_E_PROCESSINGDONE - Depricated return value, equivalent to CDD_E_OK. Shall not be used by any application service processor!
 */
typedef P2FUNC(Std_ReturnType, CDD_CALLOUT_CODE, CDD_DiagSvcProcessorFuncType) (CDD_ContextPtrType              pContext    /* IN: pContext */
                                                                               ,CDD_OpStatusType                OpStatus    /* IN: OpStatus */
                                                                               ,CDD_MsgContextPtrType           pMsgContext /* IN,OUT: pMsgContext */
                                                                               ,CDD_NegativeResponseCodePtrType ErrorCode   /* OUT: ErrorCode */);
/*! Post-Processor (fast and normal types) function prototype */
typedef P2FUNC(void, CDD_CALLOUT_CODE, CDD_DiagSvcConfirmationFuncType) (CDD_ContextPtrType         pContext   /* IN,OUT: pContext */
                                                                        ,CDD_ConfirmationStatusType confStatus /* IN: Confirmation status */);

/*!
 * Paged-data provider function prototype
 * \return CDD_E_OK                 - Operation finished with success. Do not call again
 * \return CDD_E_NOT_OK             - Operation failed. Take the NRC from ErrorCode. Do not call again
 * \return CDD_E_PENDING            - Some data written/commited. Call again to fill in more data
 * \return CDD_E_BUFFERTOOLOW       - Maximum available space used but was not enough. Call again when some additional free space available
 * \return CDD_E_DATA_READY_PADDING - No more data to be provided. Do not call again. If needed, switch to padding-byte data provider
 */
typedef P2FUNC(Std_ReturnType, CDD_CALLOUT_CODE, CDD_DiagSvcUpdateFuncType) (CDD_ContextPtrType              pContext      /* IN: Pointer to the context */
                                                                            ,CDD_OpStatusType                OpStatus      /* IN: OpStatus */
                                                                            ,CDD_DiagDataContextPtrType      pDataContext  /* IN,OUT: paged-data descriptor */
                                                                            ,CDD_NegativeResponseCodePtrType ErrorCode     /* OUT: ErrorCode */);
/*! Paged-data job cancelation notification function prototype */
typedef P2FUNC(void, CDD_CALLOUT_CODE, CDD_DiagSvcCancelFuncType) (CDD_ContextPtrType pContext /* IN: Pointer to the context */
                                                                  ,CDD_DiagDataContextPtrType pDataContext /* IN,OUT: paged-data descriptor */);

/*! Diagnostic service properties container in bitmap form (Valid values: CDD_DIAG_SVC_CFG_PROP_*) */
typedef uint8 CDDCfg_DiagServicePropertiesType;

/*! Configuration of a diagnostic service handler */
struct CDD_CFGDIAGSERVICEINFOTYPE_TAG
{
  CDD_DiagSvcProcessorFuncType      ProcFunc;         /*!< Pointer to the processor function (e.g. CDD_Service10Processor() or any application specific function name) */
#if (CDD_DIAG_SERVICE_DISPATCHER_ENABLED == STD_ON)
  CDD_DiagSvcProcessorFuncType      AltProcFunc;      /*!< Pointer to the alternative processor function */
#endif
  CDDCfg_DiagServicePropertiesType  Props;            /*!< Diagnostic service properties (Any combination of CDD_DIAG_SVC_CFG_PROP_*) */
  uint8                             MinLength;        /*!< Minimum request length (excluding the SID byte) to be verified prior calling the service processor (0 - no restrictions, >0 - particular minimum length) */
  uint8                             ConfFuncRef;      /*!< Reference to the CDD_CfgDiagSvcPostProcessors[] entry */
  uint8                             FastConfFuncRef;  /*!< Reference to the CDD_CfgDiagSvcPostProcessors[] entry (if exist, fast post-processors are located right behind the normal post-processor) */
#if (CDD_PAGED_BUFFER_ENABLED == STD_ON)
  uint8                             UpdateFuncRef;    /*!< Reference to the CDD_CfgDiagSvcUpdaters[] entry */
  uint8                             CancelFuncRef;    /*!< Reference to the CDD_CfgDiagSvcCancellers[] entry */
#endif
};
typedef struct CDD_CFGDIAGSERVICEINFOTYPE_TAG CDD_CfgDiagServiceInfoType;

/*! Configuration of diagnostic request notification handlers */
struct CDD_CFGDIAGSERVICENOFICATIONINFOTYPE_TAG
{
  CDD_DiagIndicationFuncType      IndFunc;  /*!< Points to a Xxx_Indication() callout (NULL_PTR - means last pair element in a list) */
  CDD_DiagConfirmationFuncType    ConfFunc; /*!< Points to a Xxx_Confirmation) callout (NULL_PTR - means last pair element in a list) */
};
typedef struct CDD_CFGDIAGSERVICENOFICATIONINFOTYPE_TAG CDD_CfgDiagNotificationInfoType;
typedef P2CONST(CDD_CfgDiagNotificationInfoType, TYPEDEF, CDD_CONST) CDD_CfgDiagNotificationInfoPtrType;
/*! Depends on the total number of configuration variants */
typedef uint8 CDD_CfgVarMgrDiagVariantIdMemType;
/*! Depends on the total number of configuration variants */
typedef uint8_least CDD_CfgVarMgrDiagVariantIdOptType;
/*! Depends on the total number of diagnostic variants */
typedef uint8 CDD_CfgVarMgrBitSetBaseType;
/*! A set of variants */
typedef CDD_CfgVarMgrBitSetBaseType CDD_CfgVarMgrBitSetType[1];
#if (CDD_VARMGR_MULTI_COM_ENABLED == STD_ON)
/* Pointer to a particular network configuration variant */
typedef P2CONST(CDD_CfgNetVariantInfoType, TYPEDEF, CDD_CONST_PBCFG)  CDD_CfgVarMgrComVariantType;
#endif

#if (CDD_DIAG_MULTI_SVC_TABLE_ENABLED == STD_ON)
/*! Configuration of the common variant data between network and diagnostic services variant information */
struct CDD_CFGVARMGRBRIDGEVARIANTTYPE_TAG
{
  P2CONST(CDD_CfgDiagSvc2ProtMapMemType, AUTOMATIC, CDD_CONST_PBCFG) Svc2ProtocolMap; /*!< Points to the "diagnostic service to protocol map" for a particual CDD variant (criterion): CDD_CfgDiagSvcId2ProtMap[] */
};
typedef struct CDD_CFGVARMGRBRIDGEVARIANTTYPE_TAG CDD_CfgVarMgrBridgeVariantType;
#endif

#if (CDD_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
/*! Configuration of the common for all PBL variants RAM area */
struct CDD_CFGVARMGRRAMVARIANTTYPE_TAG
{
  CDD_CfgNetRamVariantInfoType  NetworkRam; /*!< Relocatable RAM for the network sub-component */
};
typedef struct CDD_CFGVARMGRRAMVARIANTTYPE_TAG CDD_CfgVarMgrRamVariantType;
typedef P2CONST(CDD_CfgVarMgrRamVariantType, TYPEDEF, CDD_CONST_PBCFG) CDD_CfgVarMgrRamVariantPtrType;
# if (CDD_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
/*! Diagnostic sub-component post-build-loadable reallocatable shared configuration data */
struct CDD_DIAGROMVARIANTINFOTYPE_TAG
{
  P2CONST(CDD_CfgVarMgrBitSetType, AUTOMATIC, CDD_CONST_PBCFG) VariantFilter; /*!< Bitset for enabled variants */
};
typedef struct CDD_DIAGROMVARIANTINFOTYPE_TAG CDD_CfgDiagRomVariantInfoType;
# endif

/*! Configuration of the common ROM (CONST) area for all PBL variants */
struct CDD_CFGVARMGRROMVARIANTTYPE_TAG
{
  CDD_CfgNetRomVariantInfoType  NetworkRom; /*!< Relocatable ROM for the network sub-component */
# if (CDD_VARMGR_MULTI_SVC_ANY_ENABLED == STD_ON)
  CDD_CfgDiagRomVariantInfoType DiagRom;    /*!< Relocatable ROM for the diagnostic sub-component */
# endif
};
typedef struct CDD_CFGVARMGRROMVARIANTTYPE_TAG CDD_CfgVarMgrRomVariantType;
typedef P2CONST(CDD_CfgVarMgrRomVariantType, TYPEDEF, CDD_CONST_PBCFG) CDD_CfgVarMgrRomVariantPtrType;
#endif
/*! Container for all PBS/PBL (PBX) variant configuration parameters (a single criterion package): (network-, diagnostic- and common-(bridge)-variant data) */
struct CDD_CONFIGTYPE_TAG
{
#if (CDD_VARMGR_SUPPORT_ENABLED == STD_ON)
# if (CDD_VARMGR_MULTI_COM_ENABLED == STD_ON)
  CDD_CfgVarMgrComVariantType       ComVariant;       /*!< Contains all network sub-component related variant information (called COM-criteria) */
# endif
# if (CDD_DIAG_MULTI_SVC_TABLE_ENABLED == STD_ON)
  CDD_CfgVarMgrBridgeVariantType    BridgeVariant;    /*!< Contains all common/shared data (bridge) between COM and CFG variants */
# endif
# if (CDD_VARMGR_MULTI_SVC_ANY_ENABLED == STD_ON)
  CDD_CfgVarMgrDiagVariantIdMemType DiagVariantId;    /*!< Identifier for the variant */
# endif
# if (CDD_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
  CDD_CfgVarMgrRamVariantPtrType    RamVariant;       /*!< Relocatable PB RAM */
  CDD_CfgVarMgrRomVariantPtrType    RomVariant;       /*!< Relocatable PB ROM */
# endif
  /* Generally required elements */
# if (CDD_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
  uint16                            GenOutputType;    /*!< Generator Output Compatibility Version */
  uint16                            FinalMagicNumber; /*!< Configuration structure magic number   */
# endif
#else
  uint8 NoConfig;                                     /*!< In case of PBS with single variant (CDD optimizes the code for pre-compile variant), still a configuration struct is expected by the software environment */
#endif
};
typedef struct CDD_CONFIGTYPE_TAG CDD_ConfigType;

typedef P2CONST(CDD_ConfigType, TYPEDEF, CDD_CONST_PBCFG) CDD_ConfigPtrType;
# if (CDD_SVC_01_SUPPORT_ENABLED == STD_ON)
/*! Function pointer prototype for a PID handler */
typedef P2FUNC(Std_ReturnType, CDD_CODE, CDD_Svc01OpFuncType)(CDD_MsgType Data);


                                                            
/*! Generic function pointer prototype for a Get-Seed handler */
typedef P2FUNC(Std_ReturnType, CDD_APPL_CODE, CDD_Svc27GetSeedFuncType)(void);

/*! Function pointer prototype for a Compare-Key handler */
typedef P2FUNC(Std_ReturnType, CDD_APPL_CODE, CDD_Svc27CompareKeyFuncType)(CDD_ReadOnlyMsgType reqData
                                                                          ,CDD_OpStatusType opStatus
                                                                          ,CDD_NegativeResponseCodePtrType nrc);

#if (CDD_STATE_SEC_ATT_CNTR_EXT_STORAGE_ENABLED == STD_ON)
/*! Function pointer prototype for a Get-Security-Attempt-Counter handler */
typedef P2FUNC(Std_ReturnType, CDD_APPL_CODE, CDD_Svc27GetAttemptCntrFuncType)(CDD_OpStatusType opStatus
                                                                              ,P2VAR(uint8, AUTOMATIC, CDD_VAR_NOINIT) attemptCount);

/*! Function pointer prototype for a Set-Security-Attempt-Counter handler */
typedef P2FUNC(Std_ReturnType, CDD_APPL_CODE, CDD_Svc27SetAttemptCntrFuncType)(CDD_OpStatusType opStatus
                                                                              ,uint8 attemptCount);
#endif

/*! Diagnostic service 0x27 sub-function configuration data */
struct CDD_CFGSVC27SUBFUNCINFOTYPE_TAG
{
  CDD_CfgNetBufferSizeMemType       ReqLength;   /*!< Request length (for seed: SF + ADR_size, for key: SF + key_size) */
};
typedef struct CDD_CFGSVC27SUBFUNCINFOTYPE_TAG CDD_CfgSvc27SubFuncInfoType;

/*! Security level specific configuration data */
struct CDD_CFGSVC27SECLEVELINFOTYPE_TAG
{
  CDD_Svc27GetSeedFuncType         GetSeedFunc;         /*!< Pointer to the Get-Seed handler */
  CDD_Svc27CompareKeyFuncType      CompareKeyFunc;      /*!< Pointer to the Compare-Key handler */
#if (CDD_STATE_SEC_ATT_CNTR_EXT_STORAGE_ENABLED == STD_ON)
  CDD_Svc27GetAttemptCntrFuncType  GetAttemptCntrFunc;  /*!< Pointer to the Get-Security-Attempt-Counter handler */
  CDD_Svc27SetAttemptCntrFuncType  SetAttemptCntrFunc;  /*!< Pointer to the Set-Security-Attempt-Counter handler */
#endif
  CDD_CfgNetBufferSizeMemType      SeedResLength;       /*!< Seed response length */
  CDD_Svc27OpClassType             GetSeedFuncClass;    /*!< Get-Seed function prototyp descriptor */
};
typedef struct CDD_CFGSVC27SECLEVELINFOTYPE_TAG CDD_CfgSvc27SecLevelInfoType;
# endif /* (CDD_SVC_27_SUPPORT_ENABLED == STD_ON) */
# if (CDD_SVC_2C_SUPPORT_ENABLED == STD_ON)
/*! Diagnostic service 0x2C sub-function configuration data */
struct CDD_CFGSVC2CSUBFUNCINFOTYPE_TAG
{
  CDD_DiagSvcProcessorFuncType SubSvcFunc;   /*!< The sub function processor */
  CDD_CfgNetBufferSizeMemType  MinReqLength; /*!< Minimum length of a request */
};
typedef struct CDD_CFGSVC2CSUBFUNCINFOTYPE_TAG CDD_CfgSvc2CSubFuncInfoType;
# endif /* (CDD_SVC_2C_SUPPORT_ENABLED == STD_ON) */
# if (CDD_SVC_85_SUPPORT_ENABLED == STD_ON)
#if (CDD_DEM_API_430_ENABLED == STD_ON)
typedef P2FUNC(Std_ReturnType, DEM_CODE, CDD_DemControlDtcSettingFuncType) (uint8 ClientId);
#else
typedef P2FUNC(Dem_ReturnControlDTCSettingType, DEM_CODE, CDD_DemControlDtcSettingFuncType) (Dem_DTCGroupType DTCGroup, Dem_DTCKindType DTCKind);
#endif

/*! Diagnostic service 0x85 sub-function configuration data */
struct CDD_CFGSVC85SUBFUNCINFOTYPE_TAG
{
  CDD_DemControlDtcSettingFuncType  DemFunc;  /*!< Pointer to the corresponding DTCsetting state Dem API (e.g. Dem_CDDDisableDTCSetting) */     /*!< The corresponding mode of the DTCsetting state (Valid values: RTE_MODE_CDDControlDtcSetting_*) */
};
typedef struct CDD_CFGSVC85SUBFUNCINFOTYPE_TAG CDD_CfgSvc85SubFuncInfoType;
# endif /* (CDD_SVC_85_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Module internal API function declarations
---------------------------------------------- */
# define CDD_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
# if (CDD_DIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  CDD_DidMgrDidNoOp()
 *********************************************************************************************************************/
/*! \brief          Does nothing.
 *  \details        Placeholder for a signal operation which requires no action.
 *  \return         CDD_E_OK
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CODE) CDD_DidMgrDidNoOp(void);

#if (CDD_DIDMGR_NVM_READ_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  CDD_DidMgrReadNvMSignal()
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
FUNC(Std_ReturnType, CDD_CODE) CDD_DidMgrNvMReadSignal(CDD_OpStatusType opStatus
                                                      ,CDD_MsgType      data
                                                      ,uint16           blockId);
#endif

#if (CDD_DIDMGR_NVM_WRITE_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  CDD_DidMgrNvMWriteSignal()
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
FUNC(Std_ReturnType, CDD_CODE) CDD_DidMgrNvMWriteSignal(CDD_ReadOnlyMsgType             data
                                                       ,CDD_OpStatusType                opStatus
                                                       ,CDD_NegativeResponseCodePtrType errorCode
                                                       ,uint16                          blockId);
#endif

#if (CDD_DIDMGR_SR_IO_CONTROL_ENABLED == STD_ON)
/**********************************************************************************************************************
*  CDD_DidMgrIoCtrlSRHandler_Control()
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
FUNC(Std_ReturnType, CDD_CODE) CDD_DidMgrIoCtrlSRHandler_Control(CDD_CfgDidMgrIoCtrlSRHandlersRefOptType srEntryIndex
                                                                ,uint8                                   ioOperation
                                                                ,CDD_ReadOnlyMsgType                     reqData
                                                                ,CDD_OpStatusType                        opStatus
                                                                ,uint32                                  cemr
                                                                ,CDD_NegativeResponseCodePtrType         errorCode);
#endif

#if (CDD_DIDMGR_SR_IO_CONTROL_ENABLED == STD_ON)
/**********************************************************************************************************************
*  CDD_DidMgrIoCtrlSRHandler_Reset()
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
FUNC(Std_ReturnType, CDD_CODE) CDD_DidMgrIoCtrlSRHandler_Reset(CDD_CfgDidMgrIoCtrlSRHandlersRefOptType srEntryIndex
                                                              ,uint32                                  cemr
                                                              ,CDD_NegativeResponseCodePtrType         errorCode);
#endif
# endif /* (CDD_DIDMGR_SUPPORT_ENABLED == STD_ON) */
# if (CDD_OBDUDSIDMGR_SUPPORT_ENABLED == STD_ON)
#if (CDD_VARMGR_MULTI_SVC_ANY_ENABLED == STD_ON) && \
    (CDD_DIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  CDD_ObdIdMgrGetDidAvailabilityMask()
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
FUNC(uint32, CDD_CODE) CDD_ObdIdMgrGetDidAvailabilityMask(uint16 DidLookUpRefStart
                                                         ,uint16 DidLookUpRefEnd
                                                         ,CDD_ObdIdMgrMaskValueTableType maskValue);
#else
/* Just return the offline calculated/calibrated mask */
# define CDD_ObdIdMgrGetDidAvailabilityMask(DidLookUpRefStart, DidLookUpRefEnd, maskValue) (maskValue)                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif

#if (CDD_VARMGR_MULTI_SVC_ANY_ENABLED == STD_ON) && \
    (CDD_RIDMGR_SUPPORT_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  CDD_ObdIdMgrGetRidAvailabilityMask()
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
FUNC(uint32, CDD_CODE) CDD_ObdIdMgrGetRidAvailabilityMask(uint16 RidLookUpRefStart
                                                         ,uint16 RidLookUpRefEnd
                                                         ,CDD_ObdIdMgrMaskValueTableType maskValue);
#else
/* Just return the offline calculated/calibrated mask */
# define CDD_ObdIdMgrGetRidAvailabilityMask(RidLookUpRefStart, RidLookUpRefEnd, maskValue) (maskValue)                                               /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif

#if (CDD_OBDUDSIDMGR_UDSMID_SUPPORT_BY_CDD_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  CDD_ObdIdMgrReadUdsMid()
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
FUNC(Std_ReturnType, CDD_CODE) CDD_ObdIdMgrReadUdsMid(CDD_ObdIdMgrHandleMemType handle
                                                     ,CDD_OpStatusType opStatus
                                                     ,CDD_DiagDataContextPtrType pDataContext);
#endif
# endif /* (CDD_OBDUDSIDMGR_SUPPORT_ENABLED == STD_ON) */
/***********************************************************************************************************************
 *  CDD_Service27Init()
***********************************************************************************************************************/
/*! \brief         Initializes service 0x27 processing.
 *  \details       -
 *  \context       TASK
 *  \reentrant     TRUE
 *  \pre           -
***********************************************************************************************************************/
FUNC(void, CDD_CODE) CDD_Service27Init(void);
# if (CDD_SVC_2C_SUPPORT_ENABLED == STD_ON)
#if (CDD_DIDMGR_DYNDID_SRCITEM_CHECK_COND_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  CDD_Svc2CDefMgrConditionCheckRead()
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
FUNC(Std_ReturnType, CDD_CODE) CDD_Svc2CDefMgrConditionCheckRead(CDD_CfgDidMgrDynDidHandleMemType dynDidHandle
                                                                ,CDD_OpStatusType opStatus
                                                                ,CDD_NegativeResponseCodePtrType errorCode);
#endif
/**********************************************************************************************************************
 *  CDD_Svc2CDefMgrRead()
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
FUNC(Std_ReturnType, CDD_CODE) CDD_Svc2CDefMgrRead(CDD_CfgDidMgrDynDidHandleMemType dynDidHandle
                                                  ,CDD_OpStatusType opStatus
                                                  ,CDD_DiagDataContextPtrType pDataContext);

/**********************************************************************************************************************
 *  CDD_Svc2CDefMgrReadDataLength()
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
FUNC(Std_ReturnType, CDD_CODE) CDD_Svc2CDefMgrReadDataLength(CDD_CfgDidMgrDynDidHandleMemType dynDidHandle
                                                            ,CDD_DidMgrDidLengthPtrType dataLength);
# endif /* (CDD_SVC_2C_SUPPORT_ENABLED == STD_ON) */
# define CDD_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   Call-back function declarations
---------------------------------------------- */
# define CDD_START_SEC_CALLOUT_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
#if (CDD_PAGED_BUFFER_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  CDD_PagedBufferDataPadding()
 *********************************************************************************************************************/
/*! \brief          A sub-function utility of readDtcInfo.
 *  \details        This function is used for data padding.
 *  \param[in]      pContext              Pointer to the context
 *  \param[in]      opStatus              The operation status
 *  \param[in,out]  pDataContext          Pointer to the data context
 *  \param[out]     ErrorCode             The NRC
 *  \return         CDD_E_BUFFERTOOLOW    Enforce transmission of the current part
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_PagedBufferDataPadding(CDD_ContextPtrType              pContext
                                                                 ,CDD_OpStatusType                opStatus
                                                                 ,CDD_DiagDataContextPtrType      pDataContext
                                                                 ,CDD_NegativeResponseCodePtrType ErrorCode);
#endif
/***********************************************************************************************************************
 *  CDD_Service10Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK           Job processing finished, send positive response
 *  \return        CDD_E_PENDING      Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        CDD_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service10Processor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service11Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK           Job processing finished, send positive response
 *  \return        CDD_E_PENDING      Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        CDD_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service11Processor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service14Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK           Job processing finished, send positive response
 *  \return        CDD_E_PENDING      Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        CDD_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service14Processor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service19Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK           Job processing finished, send positive response
 *  \return        CDD_E_PENDING      Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        CDD_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service19Processor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service22Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK           Job processing finished, send positive response
 *  \return        CDD_E_PENDING      Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        CDD_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service22Processor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service27Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK           Job processing finished, send positive response
 *  \return        CDD_E_PENDING      Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        CDD_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service27Processor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service2EProcessor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK           Job processing finished, send positive response
 *  \return        CDD_E_PENDING      Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        CDD_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service2EProcessor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service3EProcessor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK           Job processing finished, send positive response
 *  \return        CDD_E_PENDING      Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        CDD_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service3EProcessor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service85Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic service, configured to be handled
 *                 by a CDD, is received. All of the relevant diagnostic request parameter information is forwarded by
 *                 CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSidTabFnc.
 *  \param[in]     pContext           Pointer to the context
 *  \param[in]     opStatus           The operation status
 *  \param[in,out] pMsgContext        Message-related information for one diagnostic protocol identifier
 *                                    The pointers in pMsgContext points behind the SID.
 *  \param[out]    ErrorCode          Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK           Job processing finished, send positive response
 *  \return        CDD_E_PENDING      Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP  (Vendor extension) Forces a RCR-RP response.
 *                                    The call out will called again once the response is sent. The OpStatus parameter
 *                                    will contain the transmission result
 *  \return        CDD_E_NOT_OK       Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service85Processor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service10PostProcessor()
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
FUNC(void, CDD_CALLOUT_CODE) CDD_Service10PostProcessor(CDD_ContextPtrType pContext, CDD_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  CDD_Service10FastPostProcessor()
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
FUNC(void, CDD_CALLOUT_CODE) CDD_Service10FastPostProcessor(CDD_ContextPtrType pContext, CDD_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  CDD_Service11PostProcessor()
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
FUNC(void, CDD_CALLOUT_CODE) CDD_Service11PostProcessor(CDD_ContextPtrType pContext, CDD_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  CDD_Service11FastPostProcessor()
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
FUNC(void, CDD_CALLOUT_CODE) CDD_Service11FastPostProcessor(CDD_ContextPtrType pContext, CDD_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  CDD_Service19PostProcessor()
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
FUNC(void, CDD_CALLOUT_CODE) CDD_Service19PostProcessor(CDD_ContextPtrType pContext, CDD_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  CDD_Service27PostProcessor()
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
FUNC(void, CDD_CALLOUT_CODE) CDD_Service27PostProcessor(CDD_ContextPtrType pContext, CDD_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  CDD_Service85PostProcessor()
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
FUNC(void, CDD_CALLOUT_CODE) CDD_Service85PostProcessor(CDD_ContextPtrType pContext, CDD_ConfirmationStatusType status);
/***********************************************************************************************************************
 *  CDD_Service19Updater()
***********************************************************************************************************************/
/*! \brief         Provides service specific data to the paged buffer.
 *  \details       -
 *  \param[in]     pContext                  Pointer to the context
 *  \param[in]     opStatus                  The operation status
 *  \param[in,out] pDataContext              Pointer to the data context
 *  \param[out]    ErrorCode                 Negative response code
 *  \return        CDD_E_OK                  Operation finished with success. Do not call again
 *  \return        CDD_E_NOT_OK              Operation failed. Take the NRC from ErrorCode. Do not call again
 *  \return        CDD_E_PENDING             Some data written/commited. Call again to fill in more data
 *  \return        CDD_E_BUFFERTOOLOW        Maximum available space used but was not enough.
 *                                           Call again when some additional free space available
 *  \return        CDD_E_DATA_READY_PADDING  No more data to be provided.
 *                                           Do not call again. If needed, switch to padding-byte data provider
 *  \context       TASK
 *  \reentrant     FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service19Updater(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_DiagDataContextPtrType pDataContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_RepeaterDeadEnd()
***********************************************************************************************************************/
/*! \brief         Dummy repeater proxy.
 *  \details       -
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *  \param[out]    ErrorCode            Negative response code
 *  \return        CDD_E_STOP_REPEATER  Stops the repeater proxy
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_RepeaterDeadEnd(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service11_01Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic sub-service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic sub-service, configured to be
 *                 handled by a CDD, is received. All of the relevant diagnostic request parameter information is
 *                 forwarded by CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSubService/CDDDsdSubServiceFnc.
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *                                      The pointers in pMsgContext points behind the sub-function.
 *  \param[out]    ErrorCode            Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK             Job processing finished, send positive response
 *  \return        CDD_E_PENDING        Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP    (Vendor extension) Forces a RCR-RP response.
 *                                      The call out will called again once the response is sent. The OpStatus parameter
 *                                      will contain the transmission result
 *  \return        CDD_E_STOP_REPEATER  Stops the repeater proxy
 *  \return        CDD_E_NOT_OK         Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service11_01Processor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service19_01Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic sub-service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic sub-service, configured to be
 *                 handled by a CDD, is received. All of the relevant diagnostic request parameter information is
 *                 forwarded by CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSubService/CDDDsdSubServiceFnc.
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *                                      The pointers in pMsgContext points behind the sub-function.
 *  \param[out]    ErrorCode            Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK             Job processing finished, send positive response
 *  \return        CDD_E_PENDING        Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP    (Vendor extension) Forces a RCR-RP response.
 *                                      The call out will called again once the response is sent. The OpStatus parameter
 *                                      will contain the transmission result
 *  \return        CDD_E_STOP_REPEATER  Stops the repeater proxy
 *  \return        CDD_E_NOT_OK         Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service19_01Processor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service19_02Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic sub-service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic sub-service, configured to be
 *                 handled by a CDD, is received. All of the relevant diagnostic request parameter information is
 *                 forwarded by CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSubService/CDDDsdSubServiceFnc.
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *                                      The pointers in pMsgContext points behind the sub-function.
 *  \param[out]    ErrorCode            Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK             Job processing finished, send positive response
 *  \return        CDD_E_PENDING        Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP    (Vendor extension) Forces a RCR-RP response.
 *                                      The call out will called again once the response is sent. The OpStatus parameter
 *                                      will contain the transmission result
 *  \return        CDD_E_STOP_REPEATER  Stops the repeater proxy
 *  \return        CDD_E_NOT_OK         Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service19_02Processor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
/***********************************************************************************************************************
 *  CDD_Service19_06Processor()
***********************************************************************************************************************/
/*! \brief         Processes a received diagnostic sub-service request.
 *  \details       CDD calls a function of this kind as soon as a supported diagnostic sub-service, configured to be
 *                 handled by a CDD, is received. All of the relevant diagnostic request parameter information is
 *                 forwarded by CDD through the pMsgContext function parameter.
 *                 The concrete name of the callout is defined by the configuration
 *                 parameter/CDD/CDDConfigSet/CDDDsd/CDDDsdServiceTable/CDDDsdService/CDDDsdSubService/CDDDsdSubServiceFnc.
 *  \param[in]     pContext             Pointer to the context
 *  \param[in]     opStatus             The operation status
 *  \param[in,out] pMsgContext          Message-related information for one diagnostic protocol identifier
 *                                      The pointers in pMsgContext points behind the sub-function.
 *  \param[out]    ErrorCode            Negative response code in case return value is CDD_E_NOT_OK
 *  \return        CDD_E_OK             Job processing finished, send positive response
 *  \return        CDD_E_PENDING        Job processing is not yet finished
 *  \return        CDD_E_FORCE_RCRRP    (Vendor extension) Forces a RCR-RP response.
 *                                      The call out will called again once the response is sent. The OpStatus parameter
 *                                      will contain the transmission result
 *  \return        CDD_E_STOP_REPEATER  Stops the repeater proxy
 *  \return        CDD_E_NOT_OK         Job processing finished, send NRC from the ErrorCode
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           -
***********************************************************************************************************************/
FUNC(Std_ReturnType, CDD_CALLOUT_CODE) CDD_Service19_06Processor(CDD_ContextPtrType pContext, CDD_OpStatusType opStatus, CDD_MsgContextPtrType pMsgContext, CDD_NegativeResponseCodePtrType ErrorCode);
# define CDD_STOP_SEC_CALLOUT_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   ROM 8-Bit
---------------------------------------------- */
# define CDD_START_SEC_CONST_8
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*! TxPduId to CDD connection map */
extern CONST(CDD_NetConnRefMemType, CDD_CONST) CDD_CfgNetTxPduInfo[1];
/*! Map of CDD relevant network handles */
extern CONST(CDD_CfgNetNetIdRefMemType, CDD_CONST) CDD_CfgNetConnComMChannelMap[1];
/*! Look up table of CDD service identifiers */
extern CONST(uint8, CDD_CONST) CDD_CfgDiagSvcIdLookUpTable[10];
/*! Service 0x10 look up table  */
extern CONST(uint8, CDD_CONST) CDD_CfgSvc10SubFuncLookUpTable[4];
/*! Service 0x11 look up table  */
extern CONST(uint8, CDD_CONST) CDD_CfgSvc11SubFuncLookUpTable[2];
/*! Service 0x19 look up table  */
extern CONST(uint8, CDD_CONST) CDD_CfgSvc19SubFuncLookUpTable[4];
/*! Service 0x27 look up table  */
extern CONST(uint8, CDD_CONST) CDD_CfgSvc27SubFuncLookUpTable[5];
/*! Service 0x3E look up table  */
extern CONST(uint8, CDD_CONST) CDD_CfgSvc3ESubFuncLookUpTable[2];
/*! Look up table of service 0x85 */
extern CONST(uint8, CDD_CONST) CDD_CfgSvc85SubFuncLookUpTable[3];
# define CDD_STOP_SEC_CONST_8
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   ROM 16-Bit
---------------------------------------------- */
# define CDD_START_SEC_CONST_16
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*! DID look up table  */
extern CONST(uint16, CDD_CONST) CDD_CfgDidMgrDidLookUpTable[24];
# define CDD_STOP_SEC_CONST_16
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/* ----------------------------------------------
 ~&&&   ROM of unspecified size
---------------------------------------------- */
# define CDD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
/*! CDD buffer descriptor */
extern CONST(CDD_CfgNetBufferInfoType, CDD_CONST) CDD_CfgNetBufferInfo[1];
/*! RxPduId map */
extern CONST(CDD_CfgNetRxPduInfoType, CDD_CONST) CDD_CfgNetRxPduInfo[2];
/*! CDD connection descriptor */
extern CONST(CDD_CfgNetConnectionInfoType, CDD_CONST) CDD_CfgNetConnectionInfo[1];
/*! CDD protocol descriptor */
extern CONST(CDD_CfgNetProtocolInfoType, CDD_CONST) CDD_CfgNetProtocolInfo[1];
/*! Map of all relevant for CDD network handles */
extern CONST(NetworkHandleType, CDD_CONST) CDD_CfgNetAllComMChannelMap[1];
/*! Look up table of CDD relevant network handles */
extern CONST(NetworkHandleType, CDD_CONST) CDD_CfgNetNetworkHandleLookUpTable[2];
/*! Diagnostic service execution conditions */
extern CONST(CDD_CfgStatePreconditionInfoType, CDD_CONST) CDD_CfgStatePreconditions[2];
/*! Session state properties */
/*! DID properties */
extern CONST(CDD_CfgDidMgrDidInfoType, CDD_CONST) CDD_CfgDidMgrDidInfo[23];
/*! DID operation properties */
extern CONST(CDD_CfgDidMgrDidOpInfoType, CDD_CONST) CDD_CfgDidMgrDidOpInfo[37];
/*! DID operation classes */
extern CONST(CDD_CfgDidMgrDidOpClassInfoType, CDD_CONST) CDD_CfgDidMgrDidOpClassInfo[64];
/*! DID signal operation classes */
extern CONST(CDD_CfgDidMgrSignalOpClassInfoType, CDD_CONST) CDD_CfgDidMgrSignalOpClassInfo[2];
/*! CDD service initializers */
extern CONST(CDD_DiagSvcInitFuncType, CDD_CONST) CDD_CfgDiagSvcInitializers[2];
/*! CDD service properties */
extern CONST(CDD_CfgDiagServiceInfoType, CDD_CONST) CDD_CfgDiagServiceInfo[10];
/*! Indirection from diag service info to execution pre conditions */
extern CONST(CDD_CfgStateRefMemType, CDD_CONST) CDD_CfgDiagSvcIdExecPrecondTable[9];
/*! CDD service post processors */
/*! CDD service paged buffer updater */
extern CONST(CDD_DiagSvcUpdateFuncType, CDD_CONST) CDD_CfgDiagSvcUpdaters[3];
/*! CDD service paged buffer canceller */
extern CONST(CDD_DiagSvcCancelFuncType, CDD_CONST) CDD_CfgDiagSvcCancellers[1];
/*! Service 0x10 sub-service properties table  */
/*! Indirection from service 0x10 sub functions to execution pre conditions */
extern CONST(CDD_CfgStateRefMemType, CDD_CONST) CDD_CfgSvc10SubFuncExecPrecondTable[3];
/*! Service 0x11 sub-service properties table  */
/*! Indirection from service 0x11 sub functions to execution pre conditions */
extern CONST(CDD_CfgStateRefMemType, CDD_CONST) CDD_CfgSvc11SubFuncExecPrecondTable[1];
/*! Service 0x19 sub-service properties table  */
/*! Indirection from service 0x19 sub functions to execution pre conditions */
extern CONST(CDD_CfgStateRefMemType, CDD_CONST) CDD_CfgSvc19SubFuncExecPrecondTable[3];
/*! Service 0x27 sub-service properties table  */
/*! Indirection from service 0x27 sub functions to execution pre conditions */
extern CONST(CDD_CfgStateRefMemType, CDD_CONST) CDD_CfgSvc27SubFuncExecPrecondTable[4];
/*! Indirection from service 0x3E sub functions to execution pre conditions */
extern CONST(CDD_CfgStateRefMemType, CDD_CONST) CDD_CfgSvc3ESubFuncExecPrecondTable[1];
/*! Indirection from service 0x85 sub functions to execution pre conditions */
extern CONST(CDD_CfgStateRefMemType, CDD_CONST) CDD_CfgSvc85SubFuncExecPrecondTable[2];
/*! CDD service 0x85 properties */
extern CONST(CDD_CfgSvc85SubFuncInfoType, CDD_CONST) CDD_CfgSvc85SubFuncInfo[2];
# define CDD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*lint -restore */
#endif /* !defined(CDD_LCFG_H) */
#endif
/* ********************************************************************************************************************
 * END OF FILE: CDD_Lcfg.h
 * ******************************************************************************************************************** */

