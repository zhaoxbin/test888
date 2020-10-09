
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  Dcm_Callout_Stubs.c
      Project:  Vector Basic Runtime System for MICROSAR4
       Module:  BrsMain

  \brief Description:  File for implementation of DCM callouts.
                       This file is a template only - please implement the callouts according to your needs.

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
 ----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
  ----------------------------  ------------  -------------------------------------------------------------------------
  Benjamin Walter               visbwa        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
 ----------------------------------------------------------------------------------------------------------------------
  01.00.00  2015-07-14  visbwa  Initial creation for usage with StartApplication
  01.00.01  2016-06-22  visbwa  Added sample code information block
  01.00.02  2016-08-29  visbwa  Added Dcm_DiagnosticService_0x38()
  01.00.03  2017-08-31  visbwa  Added callouts for Dcm_DiagnosticService 0x00, 0xB2, 0xB6 and 0xB7
  01.00.04  2017-12-06  visbwa  Reworked sample/example code disclaimer
  01.00.05  2019-02-01  visbwa  Added support for DCM ASR Version 4.2.2
**********************************************************************************************************************/

/**********************************************************************************************************************
*  EXAMPLE CODE ONLY
*  -------------------------------------------------------------------------------------------------------------------
*  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
*  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
*  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
*  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
*  according to the state of the art before their use.
*********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Dcm.h"
#include "Dcm_Cfg.h"
#include "canif.h"
#include "Crc_Cfg.h"
#include"Crc.h"
#include"Appl_Nm.h"
#include "hal.h"
/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/
#define DCM_START_SEC_CALLOUT_CODE
#include "MemMap.h"
//uint8 Crcsourcedata[7];
//boolean gCanNMWakeupFlag;
gCanNMSleepFlag,gCanapp;

uint8 gCanNMData;
typedef union MessageCRC
{
	char data;
	struct b
	{
		char othersignal  :4;
		char MessageCount :4;
	} bb;
}MessageCRCdata;

MessageCRCdata Crcsourcedata[7];
MessageCRCdata Crcsourcedata2[7];
FUNC(void, CANIF_CODE) CanIf_TransmitSubDataChecksumTxAppend(P2CONST(Can_PduType, AUTOMATIC, CANIF_VAR_STACK) txPduInfoPtr, P2VAR(uint8, AUTOMATIC, CANIF_VAR_STACK) txPduDataWithChecksumPtr)
{
    uint8 i;

    for(i=0;i<txPduInfoPtr->length;i++)
    {
    	txPduDataWithChecksumPtr[i]=txPduInfoPtr->sdu[i];
    }

   if(txPduInfoPtr->id==0x340)
   {
		for(i=0;i<txPduInfoPtr->length-1;i++)
		{
			if(i==0)
			{
				Crcsourcedata[i].bb.othersignal=txPduDataWithChecksumPtr[i+1];
			}
			else
			{
				Crcsourcedata[i].data=txPduDataWithChecksumPtr[i+1];
			}
		}

		Crcsourcedata[0].bb.MessageCount++;
		//txPduDataWithChecksumPtr[1]|=Crcsourcedata[1].bb.MessageCount++;
		 txPduDataWithChecksumPtr[0]=Crc_CalculateCRC8 ((uint8 *)Crcsourcedata, txPduInfoPtr->length-1, 0xFF, 1);
		txPduDataWithChecksumPtr[1]=Crcsourcedata[0].data;

   }

   if(txPduInfoPtr->id==0x3e3)
   {
		for(i=0;i<txPduInfoPtr->length-1;i++)
		{
			if(i==0)
			{
				Crcsourcedata2[i].bb.othersignal=txPduDataWithChecksumPtr[i+1];
			}
			else
			{
				Crcsourcedata2[i].data=txPduDataWithChecksumPtr[i+1];
			}
		}

		Crcsourcedata2[0].bb.MessageCount++;

		 txPduDataWithChecksumPtr[0]=Crc_CalculateCRC8 ((uint8 *)Crcsourcedata2, txPduInfoPtr->length-1, 0xFF, 1);
		 txPduDataWithChecksumPtr[1]=Crcsourcedata2[0].data;
   }




}
FUNC(Std_ReturnType, CANIF_CODE) CanIf_RxIndicationSubDataChecksumRxVerify(PduIdType CanIfRxPduId, Can_IdType CanId, uint8 CanDlc, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR)CanSduPtr)
{

}
/*Function: 通过这个回调函数可以知道网络管理的状态。
 * 也可以通过调用下面这个函数返回网络管理的状态
 * Nm_GetState (const NetworkHandleType nmNetworkHandle,Nm_StateType * const nmStatePtr,Nm_ModeType * const nmModePtr )
 * 网络管理的状态如下：
 *  NM_STATE_BUS_SLEEP
 *  NM_STATE_PREPARE_BUS_SLEEP
 *  NM_STATE_READY_SLEEP
 *  NM_STATE_NORMAL_OPERATION
 *
 */
extern int NmgotoNormalFlg;
FUNC( void, NM_CODE ) WLC_CANNM_StateChangeNotification( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle,
                                                         CONST( Nm_StateType, AUTOMATIC) nmPreviousState,
                                                         CONST( Nm_StateType, AUTOMATIC ) nmCurrentState )
{
 uint8 i;
 if(nmCurrentState==NM_STATE_BUS_SLEEP)//
 {
 // i=1;
  HAL_CanSleepTJA1043();
 }

 if(nmCurrentState==NM_STATE_REPEAT_MESSAGE)
 {
  i=5;
  NmgotoNormalFlg=1;
 }

 if(nmCurrentState==NM_STATE_NORMAL_OPERATION)
 {
  i=4;
  //gCanNMWakeupFlag= TRUE;
 }

 if(nmCurrentState==NM_STATE_PREPARE_BUS_SLEEP)
 {
  i=2;
 }

 if(nmCurrentState==NM_STATE_READY_SLEEP)
 {
  i=3;
 }



}
FUNC(void, DCM_CALLOUT_CODE) CallbackUDSsecurity(Dcm_SecLevelType formerState, Dcm_SecLevelType newState)
{


}
/**********************************************************************************************************************
  PART 1 - STATIC PART
   These Callouts are announced within Dcm_Core.h.
   The existence is configuration specific
**********************************************************************************************************************/
FUNC(void, DCM_CALLOUT_CODE) Dcm_Confirmation(Dcm_IdContextType idContext
                                             ,PduIdType dcmRxPduId
                                             ,Dcm_ConfirmationStatusType status)
{
}

#if (DCM_DIAG_JUMPTOFBL_ENABLED   == STD_ON) || \
    (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SetProgConditions(Dcm_ProgConditionsPtrType progConditions)
{
  /* This Callout is called during first call of Dcm_Mainfunction().
     If it returns DCM_E_NOT_OK, a Det-Error would be hit (0x35,0x00,0xf0,0x06) */
  return DCM_E_OK;
}
#endif

#if (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
FUNC(Dcm_EcuStartModeType, DCM_CALLOUT_CODE) Dcm_GetProgConditions(Dcm_ProgConditionsPtrType progConditions)
{
  return DCM_E_NOT_OK;
}
#endif

#if (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
# if (DCM_SVC_23_SUPPORT_ENABLED == STD_ON)
FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(Dcm_OpStatusType OpStatus
                                                               ,uint8  MemoryIdentifier
                                                               ,uint32 MemoryAddress
                                                               ,uint32 MemorySize
                                                               ,Dcm_MsgType MemoryData
                                                               ,Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return DCM_E_NOT_OK;
}
# endif

# if (DCM_SVC_3D_SUPPORT_ENABLED == STD_ON)
FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(Dcm_OpStatusType OpStatus
                                                                 ,uint8  MemoryIdentifier
                                                                 ,uint32 MemoryAddress
                                                                 ,uint32 MemorySize
                                                                 ,Dcm_MsgType MemoryData
                                                                 ,Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return DCM_E_NOT_OK;
}
# endif

#else
# if (DCM_SVC_23_SUPPORT_ENABLED == STD_ON)
FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(Dcm_OpStatusType OpStatus
                                                               ,uint8  MemoryIdentifier
                                                               ,uint32 MemoryAddress
                                                               ,uint32 MemorySize
                                                               ,Dcm_MsgType MemoryData)
{
  return DCM_E_NOT_OK;
}
# endif

# if (DCM_SVC_3D_SUPPORT_ENABLED == STD_ON)
FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(Dcm_OpStatusType OpStatus
                                                                 ,uint8  MemoryIdentifier
                                                                 ,uint32 MemoryAddress
                                                                 ,uint32 MemorySize
                                                                 ,Dcm_MsgType MemoryData)
{
  return DCM_E_NOT_OK;
}
# endif
#endif /*DCM_DCM_AR_VERSION_422*/

/**********************************************************************************************************************
  PART 2 - DYNAMIC PART
   These Callouts are announced within Dcm_Lcfg.h.
   The existence is configuration specific
**********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x00(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}

#if (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x34(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x35(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x36(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x37(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext, Dcm_NegativeResponseCodePtrType ErrorCode)
{
  *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return E_NOT_OK;
}

#else
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x34(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x35(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x36(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x37(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
#endif /*DCM_DCM_AR_VERSION_422*/

FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0x38(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB2(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB6(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DiagnosticService_0xB7(Dcm_OpStatusType opStatus, Dcm_MsgContextPtrType pMsgContext)
{
  return E_NOT_OK;
}

/**********************************************************************************************************************
  END of User implementation area
**********************************************************************************************************************/
#define DCM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"
