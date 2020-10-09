

#include "CDDNIO.h"

/*! Number of available buffers */
# define CDD_NET_NUM_BUFFERS                                                    1u
/*! Maximum number of ComM channels to keep ECU awake */
# define CDD_NET_MAX_NUM_COMM_CHANNELS                                          1u
/*! Maximum number of ComM channels CDD communicates over */
# define CDD_NET_MAX_NUM_CHANNELS                                               1u
/*! Maximum number of parallel running connections */
# define CDD_NET_MAX_NUM_TRANSP_OBJECTS                                         1u
# define CDD_NUM_THREADS                                                        1u
# define CDD_PbCfgNetBufferInfo                                      CDD_CfgNetBufferInfo
# define CDD_PbRamNetTransportObject                                 (CDD_SingletonContext.Network.TransportObject)
# define CDD_PbRamNetBufferContext                                   (CDD_SingletonContext.Network.BufferContext)
#  define CDD_NetCfgGetRxPduInfo(comVariant)                         CDD_CfgNetRxPduInfo
# define CDD_NetCfgGetConnIdOfRxPduId(comVariant, rxPduId)           (CDD_NetCfgGetRxPduInfo(comVariant)[(rxPduId)].ConnRef)                         /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CDD_NetGetConnIdOfRxPduId(rxPduId)                           (CDD_NetCfgGetConnIdOfRxPduId(0, (rxPduId)))             /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/*! Control thread specific data of the sub-component diagnostic kernel */
struct CDD_DIAGTHREADCONTEXTTYPE_TAG
{
  CDD_MsgContextType               MsgContext;            /*!< The diagnostic service/sub-service processor message context */
  CDD_CfgNetTObjHandleMemType      TObjHdl;               /*!< The transport object handle of the diagnostic request in processing */
  CDD_DiagP2TimingsType            P2Timings;             /*!< Currently active set of the P2/P2* timings */
  CDD_NetTransmissionResultType    TxStatus;              /*!< Transports the (RCR-RP and final) USDT response transmission result to the CDD_DiagTaskWorker() */
  CDD_DiagApplNotificationType     ApplNotification;      /*!< Application notification level reached for current diagnostic request (Valid values: CDD_DIAG_APPL_NOTIFICATION_*) */
  volatile CDD_DiagProcessorStateType State;              /*!< Keeps track of the diagnostic kernel processing state per diagnostic request */
  CDD_NegativeResponseCodeType     ErrorRegister;         /*!< Keeps the NRC for the current diagnostic service in processing */
  uint8                            SidIndex;              /*!< Reference to CDD_CfgDiagServiceInfo[] entry */
# if (CDD_DIAG_RCRRP_LIMIT_ENABLED == STD_ON)
  uint8                            NumRcrRpTimeouts;      /*!< Keeps track of the number of RCR-RPs sent for the current diagnostic service processing */
# endif
# if (CDD_DIAG_SERVICE_DISPATCHER_ENABLED == STD_ON)
  boolean                          ProcessServiceExtern;  /*!< Diagnostic service dispatching */
# endif
  boolean                          DoSuppressResponse;    /*!< Used dedicated flag instead of "NRC 0x11 and func_req" combination with the same effect, because of possible application confirmation functions! */
# if (CDD_NET_INTERNAL_REQ_ENABLED == STD_ON)
  boolean                          IsInternRequest;       /*!< Specifies whether current request in processing is internal i.e. send via CDD_ProcessVirtualRequest() or internal CDD_NetRxIndInternal() API (TRUE - internal, FALSE - external (normal)) */
# endif
};
typedef struct CDD_DIAGTHREADCONTEXTTYPE_TAG CDD_DiagThreadContextType;

/*! Data container with all thread specific elements (i.e. for parallel Diagnostic service handling)  */
struct CDD_THREADCONTEXTTYPE_TAG
{
  CDD_DiagThreadContextType   Diag;           /*!< Diagnostic kernel sub-component per-thread memory */
};
typedef struct CDD_THREADCONTEXTTYPE_TAG CDD_ThreadContextType;
typedef P2VAR(CDD_ThreadContextType, TYPEDEF, CDD_VAR_NOINIT) CDD_ThreadContextPtrType;
typedef P2CONST(CDD_CfgNetBufferInfoType, TYPEDEF, DCM_CONST_PBCFG) CDD_PbCfgNetBufferInfoPtrType;
typedef P2VAR(CDD_NetTransportObjectType, TYPEDEF, DCM_VAR_NOINIT) CDD_NetTransportObjectPtrType;
typedef P2VAR(CDD_NetBufferContextType, TYPEDEF, DCM_VAR_NOINIT) CDD_NetBufferContextPtrType;
typedef P2CONST(CDD_CfgDidMgrSignalOpClassInfoType, TYPEDEF, DCM_CONST)  CDD_DidMgrSignalOpClassInfoPtrType;


CDDNIO_LOCAL VAR(CDD_ThreadContextType, CDD_VAR_NOINIT)    CDD_ThreadContext[CDD_NUM_THREADS];   

// test by jiangxl 2020-03-05
//FUNC(void, CDDNIO_CODE) CDDEX_Init(void);
CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_Txpduidset(uint16 canid);
CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_Rxcanidset(uint8 pduid);
CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_TaskWorker(void);
CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_TaskRx(void);
CDDNIO_LOCAL_INLINE FUNC(void, CDDNIO_CODE) CDDEX_WorkerProcessNewRequest(void);
CDDNIO_LOCAL_INLINE FUNC(void, CDDNIO_CODE) CDDEX_WorkerDoRepeat(void);
CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_ProcessingDone(void);
CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_TaskTx(void);
CDDNIO_LOCAL_INLINE FUNC(void, CDDNIO_CODE) CDDEX_TxStartFinalResponse(void);
CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_NetTaskTx(void);
CDDNIO_LOCAL_INLINE FUNC(CDD_PbCfgNetBufferInfoPtrType, CDDNIO_CODE) CDD_NetGetBufferInfo(CDD_CfgNetBufferRefOptType index);
CDDNIO_LOCAL_INLINE FUNC(CDD_NetTransportObjectPtrType, CDDNIO_CODE) CDD_NetGetTransportObject();
CDDNIO_LOCAL_INLINE FUNC(CDD_PbCfgNetBufferInfoPtrType, CDDNIO_CODE) CDD_NetGetBufferInfo(CDD_CfgNetBufferRefOptType index);
CDDNIO_LOCAL_INLINE FUNC(CDD_NetBufferContextPtrType, CDDNIO_CODE) CDD_NetGetBufferContext(CDD_CfgNetBufferRefOptType index);
CDDNIO_LOCAL_INLINE FUNC(CDD_DidMgrSignalOpClassInfoPtrType, CDDNIO_CODE) CDD_CfgDidMgrSignalOpClassInfoGetEntryOrNull(CDD_CfgDidMgrSignalOpClassRefOptType opInfoRef);


//uint16 DataFromCGW[200];
//uint16 DataToCGW[200];
//uint16 Testgetlen=0;
uint8  CDD_TSK_EV_DIAG_WORK_NEW_REQ=0;
uint8  CDD_TSK_EV_DIAG_WORK_REPEAT=0;
uint8  CDD_TSK_EV_DIAG_TX_SEND_LINEAR=0;
uint8  CDD_TSK_EV_NET_TX_SEND_USDT=0;



CDDNIO_LOCAL_INLINE FUNC(CDD_DidMgrSignalOpClassInfoPtrType, CDDNIO_CODE) CDD_CfgDidMgrSignalOpClassInfoGetEntryOrNull(
                                                                        CDD_CfgDidMgrSignalOpClassRefOptType opInfoRef)
{
  CDD_DidMgrSignalOpClassInfoPtrType lDidSignalOpInfo;

  {
    lDidSignalOpInfo = &CDD_CfgDidMgrSignalOpClassInfo[opInfoRef];
  }

  return lDidSignalOpInfo;
}

																		
/**********************************************************************************************************************
 *  WLC_Value_SetDatatoCGW()
 *********************************************************************************************************************/
/*!

 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
/*
FUNC(Std_ReturnType, CDDNIO_CODE) WLC_Value_SetDatatoCGW(CDD_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data,uint16* CANID,uint8* length)
{

        uint8 i=0;

#if 0
       for(i=0;i<Testgetlen;i++)
       {

    	   DataToCGW[i]=DataFromCGW[i];
       }
#endif

#if 0
		*length=Testgetlen;
		*CANID=0x4bb;
		for(i=0;i<*length;i++)
		{
      //   Data[i]=DataToCGW[i];
			 Data[i]=DataFromCGW[i];
		}


}
#endif
/**********************************************************************************************************************
 *  WLC_Value_GetDatafromCGW()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *返回值： 1  表示需要向CGW反馈信息
 *         2  表示不需要向CGW反馈信息
 *
 *pduid   wifi/bt
 *        Immob
 *
 *
 *
 *********************************************************************************************************************/
/*
FUNC(Std_ReturnType, CDDNIO_CODE) WLC_Value_GetDatafromCGW(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 length,uint16 rxcanid)
{
    Std_ReturnType value;

  	uint16 i;
  	Testgetlen=length;
    for(i=0;i<length;i++)
  	{
	  DataFromCGW[i]=*Data++;
  	}

    if(rxcanid==0x4bc)
    {
    	value=1;

    }

   return value;

}
*/

/**********************************************************************************************************************
 *  CDDEX_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

FUNC(void, CDDNIO_CODE) CDDEX_Init(void)
{
	CDD_PbCfgNetBufferInfoPtrType lBufferInfo;
	lBufferInfo = CDD_NetGetBufferInfo(0);

	CDD_ThreadContext[0].Diag.MsgContext.reqData = &(lBufferInfo->BufferPtr[0]); // the request data buffer //接收得到的数据																							 /* SBSW_DCM_PARAM_PTR_WRITE */
	CDD_ThreadContext[0].Diag.MsgContext.resData = &(lBufferInfo->BufferPtr[0]); // response data buffer	  //发送数据																							/* SBSW_DCM_PARAM_PTR_WRITE */
	CDD_ThreadContext[0].Diag.MsgContext.reqDataLen = 0;						//	接收数据和发送数据都指向  同一个数组																			   /* SBSW_DCM_PARAM_PTR_WRITE */
	CDD_ThreadContext[0].Diag.MsgContext.resDataLen = 0u;																													   /* SBSW_DCM_PARAM_PTR_WRITE */
	CDD_ThreadContext[0].Diag.MsgContext.reqBufSize = lBufferInfo->Size;																									   /* SBSW_DCM_PARAM_PTR_WRITE */
	CDD_ThreadContext[0].Diag.MsgContext.resBufSize = lBufferInfo->Size;																									   /* SBSW_DCM_PARAM_PTR_WRITE */
	CDD_ThreadContext[0].Diag.MsgContext.resMaxDataLen = lBufferInfo->Size; 																								   /* SBSW_DCM_PARAM_PTR_WRITE */
	CDD_ThreadContext[0].Diag.MsgContext.resProtHeadLen = 0;																												   /* SBSW_DCM_PARAM_PTR_WRITE */
	CDD_ThreadContext[0].Diag.MsgContext.reqIndex = 0u; 																													   /* SBSW_DCM_PARAM_PTR_WRITE */
	CDD_ThreadContext[0].Diag.MsgContext.resIndex = 0u;   


}

/**********************************************************************************************************************
 *  CDDEX_MainFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

FUNC(void, CDDNIO_CODE) CDDEX_MainFunction(void)
{
  CDDEX_TaskWorker();
}


/**********************************************************************************************************************
 *  CDDEX_TaskWorker()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/


CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_TaskWorker(void)
{

	
	if(CDD_TSK_EV_DIAG_WORK_NEW_REQ==1)
	{
		CDDEX_WorkerProcessNewRequest();
	}

	
/*	if(CDD_TSK_EV_DIAG_WORK_REPEAT==1)
 	{
		CDDEX_WorkerDoRepeat();

 	}*/
	if(CDD_TSK_EV_DIAG_TX_SEND_LINEAR==1)
	{
		CDDEX_TaskTx();
	}
	

}
/**********************************************************************************************************************
 *  CDD_TaskRx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_TaskRx(void)
{




}

/**********************************************************************************************************************
 *  CDDEX_WorkerProcessNewRequest()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

CDDNIO_LOCAL_INLINE FUNC(void, CDDNIO_CODE) CDDEX_WorkerProcessNewRequest(void)
{
	CDD_NetTransportObjectPtrType pTranspObj;
	CDD_MsgContextPtrType 		pMsgContext;
	uint8 datalen;
	uint16 canid;
	CDD_OpStatusType OpStatus=0;
	 Std_ReturnType lresult=0;
	 CDD_DidMgrSignalOpClassInfoPtrType pSignalOpClassInfo;
	 
//	pSignalOpClassInfo = CDD_CfgDidMgrSignalOpClassInfoGetEntryOrNull(pDidOpTypeContext->Base.SignalOpClassInfoRef);
	pTranspObj=CDD_NetGetTransportObject();
	pMsgContext = &(CDD_ThreadContext[0].Diag.MsgContext);
	pMsgContext->reqDataLen = pTranspObj->RxLength; 	//数据接收完毕，启动接收任务，将总长度赋值给这个变量																								/* SBSW_DCM_PARAM_PTR_WRITE */
	pMsgContext->rxPduId = pTranspObj->RxPduId; 																									   /* SBSW_DCM_PARAM_PTR_WRITE */
	CDDEX_Rxcanidset(pMsgContext->rxPduId);
	lresult=((OpFuncGetDataFromCGW)CDD_CfgDidMgrSignalOpClassInfo[1].OpFunc)(pMsgContext->reqData,pMsgContext->reqDataLen,pMsgContext->RxCanid);//执行回调函数，读取从CGW发来的数据
	//CDD_CfgopClassInfo[1].OpFunc(pMsgContext->reqData,pMsgContext->reqDataLen,pMsgContext->rxPduId);
	//pMsgContext->reqIndex += pMsgContext->reqDataLen;
	if(lresult==1)//需要向CGW反馈信息，启动发送
	{
	  CDDEX_ProcessingDone();
	  lresult=((OpFuncSetDatatoCGW)CDD_CfgDidMgrSignalOpClassInfo[0].OpFunc)(OpStatus,pMsgContext->resData,&canid,&datalen);
	  CDDEX_Txpduidset(canid);
	  pMsgContext->resDataLen +=datalen;

	}
	CDD_TSK_EV_DIAG_WORK_NEW_REQ=0;

}
/*
*CDDEX_Txpduidset
*
*
*
*
*
*/
CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_Txpduidset(uint16 canid)
{  
    CDD_MsgContextPtrType 		pMsgContext;
	pMsgContext = &(CDD_ThreadContext[0].Diag.MsgContext);

		switch(canid)
		{
		 case 0x28:
			pMsgContext->TxPduId=1;
			break;
		 case 0x4ae:
			pMsgContext->TxPduId=5;
			break;
		 case 0x4bb:
			pMsgContext->TxPduId=6;
			break;

		}

}
/*
*CDDEX_Rxcanidset
*
*
*
*RxCanid
*
*/
CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_Rxcanidset(uint8 pduid)
{

	   CDD_MsgContextPtrType 		pMsgContext;
		pMsgContext = &(CDD_ThreadContext[0].Diag.MsgContext);

		switch(pduid)
		{
		 case 0:
			pMsgContext->RxCanid=0x4AF;
			break;
		 case 1:
			pMsgContext->RxCanid=0x4BC;
			break;
		 case 2:
			pMsgContext->RxCanid=0x27;
			break;

		}

}
/**********************************************************************************************************************
 *  CDDEX_WorkerDoRepeat()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 FUNC(Std_ReturnType, CDDNIO_CODE) WLC_Value_GetDatafromCGW(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 length) ;
 *
 FUNC(Std_ReturnType, CDDNIO_CODE) WLC_Value_SetDatatoCGW(CDD_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data,uint16* CANID,uint8* length) ;
 *
 *********************************************************************************************************************/

CDDNIO_LOCAL_INLINE FUNC(void, CDDNIO_CODE) CDDEX_WorkerDoRepeat(void)
{
    Std_ReturnType lresult;
	CDD_OpStatusType OpStatus=0;
	uint8 datalen;
	uint16 canid;

	CDD_MsgContextPtrType 		pMsgContext;
	pMsgContext = &(CDD_ThreadContext[0].Diag.MsgContext);

	//lresult=CDD_CfgopClassInfo[1].OpFunc(pMsgContext->reqData,pMsgContext->reqDataLen);//执行回调函数，读取从CGW发来的数据

	//pMsgContext->reqIndex += pMsgContext->reqDataLen;
	if(lresult==1)//需要向CGW反馈信息，启动发送
	{
	  CDDEX_ProcessingDone();
	//  lresult=CDD_CfgopClassInfo[0].OpFunc(OpStatus,pMsgContext->resData,&canid,&datalen);
	  CDDEX_Txpduidset(canid);
	  pMsgContext->resDataLen +=datalen;
	  CDD_TSK_EV_DIAG_WORK_REPEAT=0;
	}
}

/**********************************************************************************************************************
 *  CDDEX_ProcessingDone()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_ProcessingDone(void)
{

	CDD_TSK_EV_DIAG_TX_SEND_LINEAR=1;

}
/**********************************************************************************************************************
 *  CDDEX_SendCanFrameTo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

FUNC(void, CDDNIO_CODE) CDDEX_SendCanFrameTo(uint16 Canid,uint8 * dataprt,uint16 datalen)
{

  uint16 i;
  CDD_MsgContextPtrType 	  pMsgContext;
  pMsgContext = &(CDD_ThreadContext[0].Diag.MsgContext);

  	for(i=0;i<datalen;i++)
	{

		pMsgContext->resData[i]=dataprt[i];
		pMsgContext->resDataLen++;

	}
	CDDEX_Txpduidset(Canid);
	CDD_TSK_EV_DIAG_TX_SEND_LINEAR=1;

}

/**********************************************************************************************************************
 *  CDDEX_TaskTx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_TaskTx(void)
{

   CDDEX_TxStartFinalResponse();

}
/**********************************************************************************************************************
 *  CDDEX_TxStartFinalResponse()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

CDDNIO_LOCAL_INLINE FUNC(void, CDDNIO_CODE) CDDEX_TxStartFinalResponse(void)
{
	Std_ReturnType lStdResult ;

	CDD_NetTransportObjectPtrType pTranspObj;
	CDD_PbCfgNetBufferInfoPtrType lBufferInfo;
    CDD_MsgContextPtrType 		pMsgContext;
	pTranspObj=CDD_NetGetTransportObject();
	pMsgContext = &(CDD_ThreadContext[0].Diag.MsgContext);

    lBufferInfo = CDD_NetGetBufferInfo(0);
	pTranspObj->BuffInfo.SduDataPtr = lBufferInfo->BufferPtr;
	pTranspObj->BuffInfo.SduLength = (PduLengthType)(pMsgContext->resDataLen);																					
	pTranspObj->BuffPos = 0u;    
	lStdResult = PduR_DcmTransmit(pMsgContext->TxPduId ,&pTranspObj->BuffInfo);  

	pMsgContext->resDataLen=0;//清楚，下次长度从0开始
	CDD_TSK_EV_DIAG_TX_SEND_LINEAR=0;


}
/**********************************************************************************************************************
 *  CDDEX_NetTaskTx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

CDDNIO_LOCAL FUNC(void, CDDNIO_CODE) CDDEX_NetTaskTx(void)
{



}

/**********************************************************************************************************************
 *  CDD_NetGetBufferInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/


CDDNIO_LOCAL_INLINE FUNC(CDD_PbCfgNetBufferInfoPtrType, CDDNIO_CODE) CDD_NetGetBufferInfo(CDD_CfgNetBufferRefOptType index)
{
  CDD_PbCfgNetBufferInfoPtrType lResult;


  {
    lResult = &CDD_PbCfgNetBufferInfo[index];
  }

  return lResult;
}

/**********************************************************************************************************************
 *  CDD_NetGetBufferInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

FUNC(BufReq_ReturnType, CDD_CODE) Cdd_CopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, CDD_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, CDD_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, CDD_APPL_DATA) availableDataPtr)
{
	BufReq_ReturnType lResult;

	CDD_NetTransportObjectPtrType pTranspObj;
	pTranspObj=CDD_NetGetTransportObject();

	CDD_UtiMemCopySafe(&(pTranspObj->BuffInfo.SduDataPtr[pTranspObj->BuffPos])
										  ,info->SduDataPtr
										  ,0u
										  ,info->SduLength
										  ,info->SduLength);                                                                                                             /* SBSW_DCM_PARAM_PTR_FORWARD */
	/* Update Tx-buffer read progress */
	pTranspObj->BuffPos += (CDD_CfgNetBufferSizeMemType)(info->SduLength);                                                                           /* SBSW_DCM_PARAM_PTR_WRITE */
	/* Report remaining amount of data in the Tx-buffer */
	*availableDataPtr = (PduLengthType)(pTranspObj->BuffInfo.SduLength - pTranspObj->BuffPos);                                                       /* SBSW_DCM_PARAM_PTR_WRITE */
	lResult = BUFREQ_OK;

}
/**********************************************************************************************************************
 *  Cdd_CopyRxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

FUNC(BufReq_ReturnType, CDD_CODE) Cdd_CopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, CDD_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, CDD_APPL_DATA) bufferSizePtr)
{
	BufReq_ReturnType lResult;


	CDD_NetTransportObjectPtrType pTranspObj;
	pTranspObj=CDD_NetGetTransportObject();

	CDD_PbCfgNetBufferInfoPtrType lBufferInfo;

    lBufferInfo = CDD_NetGetBufferInfo(0);

     CDD_UtiMemCopySafe(info->SduDataPtr
                        ,lBufferInfo->BufferPtr
                        ,pTranspObj->BuffPos
                        ,lBufferInfo->Size
                        ,info->SduLength);                                                                                                       /* SBSW_DCM_POINTER_WRITE_BUFFERINFO */
    
    /* #60 Update the transport object's buffer-copy-progress */
    pTranspObj->BuffPos += (CDD_CfgNetBufferSizeMemType)(info->SduLength);                                                                       /* SBSW_DCM_PARAM_PTR_WRITE */

    /* #70 Report the remaining available DCM buffer size to the XxxTp */
    *bufferSizePtr = (PduLengthType)(pTranspObj->RxLength) - (PduLengthType)(pTranspObj->BuffPos);                                               /* SBSW_DCM_PARAM_PTR_WRITE */
    lResult = BUFREQ_OK;



}
/**********************************************************************************************************************
 *  Cdd_StartOfReception()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

FUNC(BufReq_ReturnType, CDD_CODE) Cdd_StartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, CDD_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, CDD_APPL_DATA) bufferSizePtr)
{

    BufReq_ReturnType lResult = BUFREQ_E_NOT_OK;


	CDD_NetTransportObjectPtrType pTranspObj;
	
	pTranspObj = CDD_NetGetTransportObject();


      /* #50 If the transport object is allocated as a new one: */
    
        CDD_PbCfgNetBufferInfoPtrType lBufferInfo;

     //   pTranspObj->BufferHdl = Dcm_NetGetProtObjOfConnection(lConnId)->RxTxBufferRef;                                                               /* SBSW_DCM_POINTER_WRITE_ALLOCATEDTOBJ */
        lBufferInfo = CDD_NetGetBufferInfo(0);

        /* #60 If the request message length fits the Rx-buffer associated with the DcmRxPduId: */
        if(TpSduLength <= lBufferInfo->Size)
        {
          CDD_NetBufferContextPtrType pBufferContext;

          /* #70 Prepare for positive result or NRC 0x21 response: */
          pBufferContext = CDD_NetGetBufferContext(pTranspObj->BufferHdl);
          /* Prepare result to be reported for the available Rx-buffer size */
          *bufferSizePtr = lBufferInfo->Size;                                                                                                        /* SBSW_DCM_PARAM_PTR_WRITE */

          /* Initialize the transport object */
          pTranspObj->RxPduId  = id;                                                                                                            /* SBSW_DCM_POINTER_WRITE_ALLOCATEDTOBJ */
          //pTranspObj->ConnId   = (CDD_NetConnRefMemType)lConnId;                                                                                     /* SBSW_DCM_POINTER_WRITE_ALLOCATEDTOBJ */

          /* Set up Rx message context */
          pTranspObj->RxLength = (CDD_CfgNetBufferSizeMemType)TpSduLength;/* safe cast, since tpSduLength <= bufferSize = value fits Dcm_CfgNetBufferSizeMemType */ /* SBSW_DCM_POINTER_WRITE_ALLOCATEDTOBJ */
          pTranspObj->BuffPos  = 0u; /* start writing from the buffer begin */                                                                       /* SBSW_DCM_POINTER_WRITE_ALLOCATEDTOBJ */
       //   pTranspObj->State    = DCM_NET_TOBJ_STATE_ONRX;                                                                                            /* SBSW_DCM_POINTER_WRITE_ALLOCATEDTOBJ */
                                                                                                        /* SBSW_DCM_POINTER_WRITE_ALLOCATEDTOBJ */
            /* #90 Lock the buffer and allow further request reception */
          pTranspObj->RxData = lBufferInfo->BufferPtr;                                                                                             /* SBSW_DCM_POINTER_WRITE_ALLOCATEDTOBJ */                                                                        /* SBSW_DCM_POINTER_WRITE_BUFFERCONTEXT */
          lResult = BUFREQ_OK;
          
        }
        else
        {
          /* #110 Otherwise, reject the message reception with the result "message too long" */
          lResult = BUFREQ_E_OVFL;
        }
    
}
/**********************************************************************************************************************
 *  Cdd_TpRxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

FUNC(void, CDD_CODE) Cdd_TpRxIndication(PduIdType id, Std_ReturnType result)
{
	CDD_TSK_EV_DIAG_WORK_NEW_REQ=1;
}
/**********************************************************************************************************************
 *  Cdd_TpTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

FUNC(void, CDD_CODE) Cdd_TpTxConfirmation(PduIdType id, Std_ReturnType result)
{

}

/**********************************************************************************************************************
 *  CDDtGetTransportObject()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/

CDDNIO_LOCAL_INLINE FUNC(CDD_NetTransportObjectPtrType, CDDNIO_CODE) CDD_NetGetTransportObject()
{
  CDD_NetTransportObjectPtrType lResult;


  {
    lResult = &CDD_PbRamNetTransportObject[0];
  }

  return lResult;
}
/**********************************************************************************************************************
 *  CDD_NetGetBufferContext()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/


CDDNIO_LOCAL_INLINE FUNC(CDD_NetBufferContextPtrType, CDDNIO_CODE) CDD_NetGetBufferContext(CDD_CfgNetBufferRefOptType index)
{


  CDD_NetBufferContextPtrType lResult;


  {
    lResult = &CDD_PbRamNetBufferContext[index];
  }

  return lResult;


}





