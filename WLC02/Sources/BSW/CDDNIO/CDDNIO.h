#if !defined(CDDNIO_H)
# define CDDNIO_H



#include "ComStack_Types.h"
#include "CDDNIO_cfg.h"
#include "CDD_CoreTypes.h"
#include "CDDNIO_Lcfg.h"

#  define CDDNIO_LOCAL                                                  static
#  define CDDNIO_CODE                /* code */
#  define CDDNIO_LOCAL_INLINE                                           LOCAL_INLINE

# define CDD_UtiMemCopy(srcPtr, tgtPtr, length)                      {CDD_CfgNetBufferSizeOptType memIter; for(memIter = 0u; memIter < (CDD_CfgNetBufferSizeOptType)(length); ++memIter) {(tgtPtr)[memIter] = (srcPtr)[memIter];}} /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
typedef uint8 CDD_CommunicationModeType;


struct CDD_NETCONTEXTTYPE_TAG
{
  CDD_PB_RAM_DATA_DECL(CDD_NetBufferContextType, BufferContext, CDD_NET_NUM_BUFFERS)                  /*!< Control states of the USDT message buffers (main and additional) */
  CDD_PB_RAM_DATA_DECL(CDD_NetTransportObjectType, TransportObject, CDD_NET_MAX_NUM_TRANSP_OBJECTS)   /*!< Transport objects for simultaneous servicing of multiple clients */
  CDD_PB_RAM_DATA_DECL(CDD_NetComMContextType, ComMContext, CDD_NET_MAX_NUM_COMM_CHANNELS)            /*!< Control states of ComM status notifications per CDD related com-channel (i.e. channel on which CDD communicates with a client */
#if (CDD_NET_PERIODIC_TX_ENABLED == STD_ON)
  CDD_NetPeriodicTxContextType  PeriodicTxContext;                                                    /*!< Composition relation to the periodic message transmitter */
#endif
  CDD_PB_RAM_DATA_DECL(CDD_CfgNetTObjHandleMemType, ConnId2TObjIdMap, CDD_NET_MAX_NUM_CONNECTIONS)    /*!< A map of type <key = connectionId, value = TransportObject>. Used for fast transport object allocation */
#if (CDD_MODE_COMMCTRL_ENABLED == STD_ON)
  CDD_PB_RAM_DATA_DECL(CDD_CommunicationModeType, ComCtrlChannels, CDD_NET_MAX_NUM_ALL_COMM_CHANNELS) /*!< Communication state [Rx/Tx][On/Off] of each ComM channel known to CDD */
#endif
#if (CDD_NET_MULTI_PROTOCOL_ENABLED == STD_ON)
  CDD_NetProtRefMemType         ActiveProtocol;                                                       /*!< The protocol handle last activated */
#endif
  CDD_NetConnRefMemType         NumActiveConnections;                                                 /*!< Current number of simultaneously serviced clients/connections */
  CDD_NetConnRefMemType         SessionConnection;                                                    /*!< Owner (client) of the non-default session last started */                                                /*!< Guard for prevention of CDDs automatic ComM diag-activate signal notification (this state is managed by the application) */
#if (CDD_NET_RX_BLOCKING_ENABLED == STD_ON)
  boolean                       RxAllowed;                                                            /*!< Guard for global blocking of any request reception */
#endif
#if (CDD_NET_KEEP_ALIVE_TIME_ENABLED == STD_ON)
  boolean                       KeepAlive;                                                            /*!< Guard for prevention of diag-inactive notifications from CDD to ComM (e.g. in the default-session) */
#endif
};
typedef struct CDD_NETCONTEXTTYPE_TAG CDD_NetContextType;


struct CDD_SINGLETONCONTEXTTYPE_TAG
{
  CDD_NetContextType         Network;   /*!< Network sub-component shared memory */
};
typedef struct CDD_SINGLETONCONTEXTTYPE_TAG CDD_SingletonContextType;


CDDNIO_LOCAL VAR(CDD_SingletonContextType, CDD_VAR_NOINIT) CDD_SingletonContext;


FUNC(void, CDDNIO_CODE) CDDEX_MainFunction(void);
FUNC(void, CDDNIO_CODE) CDDEX_SendCanFrameTo(uint16 Canid,uint8 * dataprt,uint16 datalen);
FUNC(Std_ReturnType, CDDNIO_CODE) WLC_Value_SetDatatoCGW(CDD_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data,uint16* CANID,uint8* length) ;
FUNC(Std_ReturnType, CDDNIO_CODE) WLC_Value_GetDatafromCGW(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 length,uint16 rxcanid) ;


typedef P2FUNC(Std_ReturnType, CDDNIO_CODE, OpFuncGetDataFromCGW)(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 length,uint16 rxcanid) ;

typedef P2FUNC(Std_ReturnType, CDDNIO_CODE, OpFuncSetDatatoCGW)(CDD_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data,uint16* CANID,uint8* length) ;


CDDNIO_LOCAL_INLINE FUNC(void, CDDNIO_CODE) CDD_UtiMemCopySafe(CDD_ConstReadOnlyMsgType sourcePtr
                                                         ,CDD_ConstMsgType targetPtr
                                                         ,CDD_MsgLenType targetPos
                                                         ,CDD_MsgLenType targetSize
                                                         ,CDD_MsgLenType length);







CDDNIO_LOCAL_INLINE FUNC(void, CDDNIO_CODE) CDD_UtiMemCopySafe(CDD_ConstReadOnlyMsgType sourcePtr
                                                         ,CDD_ConstMsgType targetPtr
                                                         ,CDD_MsgLenType targetPos
                                                         ,CDD_MsgLenType targetSize
                                                         ,CDD_MsgLenType length)
{

CDD_UtiMemCopy(sourcePtr, &(targetPtr[targetPos]), length)	   ;

}


FUNC(void, CDDNIO_CODE) CDDEX_Init(void);

#endif 

