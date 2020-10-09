/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  CDD_CoreTypes.h
 *        \brief  Public data type definition interface of CDD
 *
 *      \details  MICROSAR CDD based on AR 4.0.3
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/
#if !defined(CDD_CORETYPES_H)
# define CDD_CORETYPES_H
/* ----------------------------------------------
 ~&&&   Versions
---------------------------------------------- */
#define CDD_VAR_INIT            /* initialized global/static variables */
#define CDD_VAR_NOINIT          /* uninitialized global/static variables */

#define CDD_CODE                /* code */
#define CDD_CONST               /* global/static constants */
#define CDD_CAL_PRM             /* calibrateable constants */
#define CDD_APPL_CODE           /* callback functions outside of CDD */
#define CDD_APPL_CONST          /* constants outside CDD */ 
#define CDD_APPL_DATA           /* variables/buffers outside of CDD */
#define CDD_CALLOUT_CODE        /* callback functions outside of CDD but part of CDD (callouts) */
#define CDD_VAR_INIT            /* initialized global/static variables */
#define CDD_VAR_NOINIT          /* uninitialized global/static variables */
#define CDD_VAR_PBCFG           /* global/static variable for PostBuildLoadable */
#define CDD_PBCFG               /* global/static constants for PostBuildLoadable */




/*! The constant (ROM) data is located in the non-loadable ROM memory area */
#  define CDD_CONST_PBCFG                                            CDD_CONST
/*! The variable (RAM) data is located in the non-loadable RAM memory area */
#  define CDD_RAM_PBCFG                                              CDD_VAR_NOINIT


/* ----------------------------------------------
 ~&&&   Function-like macros
---------------------------------------------- */
/* Data type templates */


#  define CDD_PB_RAM_DATA_DECL(dataType, dataName, dataSize)         dataType dataName[dataSize];


#  define CDD_NET_TOBJ_ADDBUFFER_SIZE                                3u

# if (CDD_MEMMGR_SUPPORT_ENABLED == STD_ON)
typedef uint8 CDD_MemMgrOpResultType;
typedef CDD_MemMgrOpResultType CDD_ReturnReadMemoryType;
typedef CDD_MemMgrOpResultType CDD_ReturnWriteMemoryType;
# endif /* (CDD_MEMMGR_SUPPORT_ENABLED == STD_ON) */
/*******************************
 ***  CDD common types
 *******************************/
/*! AR base data type for eventually processed parallel requests (not supported yet) */
typedef uint8                                                   CDD_IdContextType;
typedef uint8                                                   CDD_IdThreadType;
/*! Generic ANSI-C bit type for structure data types */
typedef unsigned int                                            CDD_BitForStructType;
/*! AR base data type for diagnostic message item type */
typedef uint8                                                   CDD_MsgItemType;
/*! AR base data type for a pointer to a readable and writable diagnostic message buffer located in the pre-compile CDD RAM area */
typedef P2VAR(CDD_MsgItemType, TYPEDEF, CDD_VAR_NOINIT)         CDD_MsgType;
/*! Base data type for a pointer to a read-only diagnostic message buffer located in the pre-compile CDD RAM area */
typedef P2CONST(CDD_MsgItemType, TYPEDEF, CDD_VAR_NOINIT)       CDD_ReadOnlyMsgType;
/*! Base data type for a non changeable pointer to a readable and writable diagnostic message buffer located in the pre-compile CDD RAM area */
typedef CONSTP2VAR(CDD_MsgItemType, TYPEDEF, CDD_VAR_NOINIT)    CDD_ConstMsgType;
/*! Base data type for a non changeable pointer to a readable diagnostic message buffer located in the pre-compile CDD RAM area */
typedef CONSTP2CONST(CDD_MsgItemType, TYPEDEF, CDD_VAR_NOINIT)  CDD_ConstReadOnlyMsgType;
/*! Base data type for a non changeable pointer to a readable and writeable diagnostic message buffer located in the post-build loadable CDD RAM area */
typedef CONSTP2VAR(CDD_MsgItemType, TYPEDEF, DCM_RAM_PBCFG)     CDD_PbConstMsgType;
/*! Base data type for a pointer to a readable and writable diagnostic message buffer located outside of the CDDs RAM area (i.e. within another BSW or application code) */
typedef P2VAR(CDD_MsgItemType, TYPEDEF, CDD_APPL_DATA)          CDD_ApplMsgType;

/*! AR data type for a diagnostic message length */
typedef uint32                                                  CDD_MsgLenType;

/*! Data type for an abstract pointer to a readable and writable CDD global RAM area of unknown data type */
typedef P2VAR(void, TYPEDEF, CDD_VAR_NOINIT)                    CDD_GenericCDDRamNoInitPtrType;
/*! Data type for an abstract pointer to a read-only CDD global RAM area of unknown data type */
typedef P2CONST(void, TYPEDEF, CDD_VAR_NOINIT)                  CDD_GenericCDDConstRamNoInitPtrType;

/*! Base data type for a pointer to a readable and writable 8bit data on the function stack */
typedef P2VAR(uint8, TYPEDEF, AUTOMATIC)                        CDD_Ptr2LocalU8Type;
/*! Base data type for a pointer to a readable and writable 16bit data on the function stack */
typedef P2VAR(uint16, TYPEDEF, AUTOMATIC)                       CDD_Ptr2LocalU16Type;
/*! Base data type for a pointer to a readable and writable CDD_MsgLenType data defined globally */
typedef P2VAR(CDD_MsgLenType, TYPEDEF, CDD_VAR_NOINIT)          CDD_MsgLenPtrType;

/*! Base data type for a pointer to a readable and writable 8bit data defined globally */
typedef P2VAR(uint8, TYPEDEF, CDD_VAR_NOINIT)                   CDD_Uint8VarDataPtrType;
/*! Base data type for a pointer to a readable and writable 16bit data defined globally */
typedef P2VAR(uint16, TYPEDEF, CDD_VAR_NOINIT)                  CDD_Uint16VarDataPtrType;
/*! Base data type for a pointer to a readable and writable 32bit data defined globally */
typedef P2VAR(uint32, TYPEDEF, CDD_VAR_NOINIT)                  CDD_Uint32VarDataPtrType;

/*! Base data type for a non changeable pointer to a constant (ROM) 8bit data defined globally */
typedef CONSTP2CONST(uint8, TYPEDEF, CDD_CONST)                 CDD_Uint8ConstDataConstPtrType;
/*! Base data type for a non changeable pointer to a constant (ROM) 16bit data defined globally */
typedef CONSTP2CONST(uint16, TYPEDEF, CDD_CONST)                CDD_Uint16ConstDataConstPtrType;
/*! Base data type for a non changeable pointer to a constant (ROM) 32bit data defined globally */
typedef CONSTP2CONST(uint32, TYPEDEF, CDD_CONST)                CDD_Uint32ConstDataConstPtrType;
/*! Base data type for a non changeable pointer to a constant but calibratable 32bit data defined globally */
typedef CONSTP2CONST(uint32, TYPEDEF, CDD_CAL_PRM)              CDD_Uint32CalibDataConstPtrType;

/*! Base data type for a pointer to a constant (ROM) 8bit data defined globally */
typedef P2CONST(uint8, TYPEDEF, CDD_CONST)                      CDD_Uint8ConstDataPtrType;
/*! Base data type for a pointer to a constant (ROM) 16bit data defined globally */
typedef P2CONST(uint16, TYPEDEF, CDD_CONST)                      CDD_Uint16ConstDataPtrType;
/*! Base data type for a pointer to a constant (ROM) 32bit data defined globally */
typedef P2CONST(uint32, TYPEDEF, CDD_CONST)                     CDD_Uint32ConstDataPtrType;
/*! Base data type for a pointer to a constant but calibratable 32bit data defined globally */
typedef P2CONST(uint32, TYPEDEF, CDD_CAL_PRM)                   CDD_Uint32CalibDataPtrType;

/*! Deprecated: An obsolete pre AR4.x CDD specific return data type (now using Std_ReturnType) */
typedef Std_ReturnType                                          CDD_StatusType;

/*! A definition of a range of uint16 values */
//typedef CDD_UtiPairType(uint16, uint16) CDD_UtiU16RangeType;
/*! Data type for DET error codes */
typedef uint8                                                  CDD_DetErrorCodeType;

/*! Data type for DET API IDs */
typedef uint8 CDD_DetApiIdType;
/*! Data type for critical error detection API IDs */
typedef uint8 CDD_ExtendedSidType;
/*! Zero based reference to a USDT diagnostic client connection configuration entry (0..31) */
typedef uint8        CDD_NetConnRefMemType;
typedef uint8_least  CDD_NetConnRefOptType;

/*! Zero based reference to a diagnostic protocol configuration entry (0..31) */
typedef uint8        CDD_NetProtRefMemType;
typedef uint8_least  CDD_NetProtRefOptType;
/*! Base data type for a diagnostic state (e.g. session, security access) identification (0..31) */
typedef uint8       CDD_StateIndexMemType;
typedef uint8_least CDD_StateIndexOptType;
typedef uint16 CDD_TmrTimerCntrMemType;
typedef uint16_least CDD_TmrTimerCntrOptType;
typedef CDD_MsgLenType CDD_DiagBufferIndexType;

typedef Std_ReturnType CDD_NetTransmissionResultType;
typedef uint8 CDD_DiagApplNotificationType;
typedef uint8 CDD_DiagProcessorStateType;
typedef uint16 CANID;

/*! Diagnostic application timing (P2) pair */
struct CDD_DIAGP2TIMINGSTYPE_TAG
{
  CDD_TmrTimerCntrMemType P2;     /*!< The P2 time (in CDD_MainFunction ticks) */
  CDD_TmrTimerCntrMemType P2Star; /*!< The P2* time (in CDD_MainFunction ticks) */
};
typedef struct CDD_DIAGP2TIMINGSTYPE_TAG CDD_DiagP2TimingsType;

/*! Additional information about a request */
struct CDDMSGADDINFO_TAG
{
  CDD_BitForStructType reqType               :1; /*!< Specifies the diagnostic request type (0 - physical, 1 - functional) */
  CDD_BitForStructType suppressPosResponse   :1; /*!< Represents the SPRMIB state at request time and during service processing (e.g. after P2 timeout)( 0 - do not suppress positive response, 1 - do suppress positive response) */
};
typedef struct CDDMSGADDINFO_TAG CDD_MsgAddInfoType;

/*! Context information of a diagnostic request */
struct CDD_MSGCONTEXT_TAG
{
  CDD_MsgLenType                reqDataLen;    /*!< Remaining request data length (decremented on each diagnostic service request data evaluation stage) */
  CDD_MsgLenType                resDataLen;    /*!< Current response data length (incremented on each diagnostic service response data provision stage) */
  CDD_MsgLenType                resMaxDataLen; /*!< Remaining buffer size for response data (contains the maximum buffer size left after any response data has been added at a given stage) */
  CDD_MsgLenType                reqBufSize;    /*!< Size of request buffer */
  CDD_MsgLenType                resBufSize;    /*!< Size of response buffer */
  CDD_MsgType                   reqData;       /*!< Points to the request data buffer to be evaluated or passed to the application, depending on the request data evaluation stage */
  CDD_MsgType                   resData;       /*!< Points to the response data buffer to be written or passed to the application to provide data at, depending on the response data provision stage */
  CDD_DiagBufferIndexType       reqIndex;      /*!< Index to the next request data byte to be evaluated or passed to the application, depending on the request data evaluation stage */
  CDD_DiagBufferIndexType       resIndex;      /*!< Index to the next response data byte to be written or passed to the application to provide data at, depending on the response data provision stage */
  CDD_DiagBufferIndexType       resProtHeadLen;/*!< Keeps track of the already provided response protocol header */
  CDD_MsgAddInfoType            msgAddInfo;    /*!< Additional diagnostic request message information */
  PduIdType                     rxPduId;       /*!< The CDDRxPduId on which the diagnostic request is received */
  PduIdType                     TxPduId;       /*!< The CDDRxPduId on which the diagnostic request is received */
  CDD_IdContextType             idContext;     /*!< Specifies the CDD instance for multi-server purposes */
  CDD_IdThreadType              threadId;      /*!< Specifies the CDD thread-id for parallel service processing */
  CANID                         RxCanid;
};

typedef struct CDD_MSGCONTEXT_TAG CDD_MsgContextType;

typedef P2VAR(CDD_MsgContextType, TYPEDEF, CDD_VAR_NOINIT) CDD_MsgContextPtrType;
typedef P2CONST(CDD_MsgContextType, TYPEDEF, CDD_VAR_NOINIT) CDD_ReadOnlyMsgContextPtrType;

/*! Generic diagnostic data container descriptor */
struct CDD_DIAGDATACONTEXTTYPE_TAG
{
  CDD_MsgType     Buffer;    /*!< Points to the beginning of a data buffer */
  CDD_MsgLenType  Size;      /*!< Specifies the total size of the referenced buffer */
  CDD_MsgLenType  Usage;     /*!< Keeps track of the used space in the referenced buffer */
  CDD_MsgLenType  AvailLen;  /*!< Remaining number of bytes that can be written */
};
typedef struct CDD_DIAGDATACONTEXTTYPE_TAG CDD_DiagDataContextType;
typedef P2VAR(CDD_DiagDataContextType, TYPEDEF, CDD_VAR_NOINIT) CDD_DiagDataContextPtrType;
typedef P2CONST(CDD_DiagDataContextType, TYPEDEF, CDD_VAR_NOINIT) CDD_DiagDataContextConstPtrType;
typedef uint8 CDD_NegativeResponseCodeType;

/*! Generic pointer to a diagnostic ErrorCode (NRC) in CDD related RAM */
typedef P2VAR(CDD_NegativeResponseCodeType, TYPEDEF, CDD_VAR_NOINIT) CDD_NegativeResponseCodePtrType;


#endif /* !defined(CDD_CORETYPES_H) */
/* ********************************************************************************************************************
 * END OF FILE: CDD_CoreTypes.h
 * ******************************************************************************************************************** */
