



#include "EcuM.h"
#define RTE_CORE

#include "Rte_Type.h"
#include "Rte_Main.h"

#include "Rte_BswM.h"
#include "Rte_ComM.h"
#include "Rte_Dcm.h"
#include "Rte_DemMaster_0.h"
#include "Rte_DemSatellite_0.h"
#include "Rte_Det.h"
#include "Rte_EcuM.h"
#include "Rte_Os_OsCore0_swc.h"
#include "SchM_BswM.h"
#include "SchM_Can.h"
#include "SchM_CanIf.h"
#include "SchM_CanNm.h"
#include "SchM_CanSM.h"
#include "SchM_CanTp.h"
#include "SchM_Com.h"
#include "SchM_ComM.h"
#include "SchM_Dcm.h"
#include "SchM_Dem.h"
#include "SchM_Det.h"
#include "SchM_Dio.h"
#include "SchM_EcuM.h"
#include "SchM_Mcu.h"
#include "SchM_Nm.h"
#include "SchM_PduR.h"

#include "Rte_Hook.h"

#include "Com.h"
#include "Can.h"

#if defined(IL_ASRCOM_VERSION)
# define RTE_USE_COM_TXSIGNAL_RDACCESS
#endif

#include "Rte_Cbk.h"



#define DS1_PORT   PTB
#define DS1        14          /* pin PB[14] - LED DS3  on LFGTWSEM core board */

#define CAN_STB_PORT PTI


uint8 varTest_S_Sig1;
uint8 varTest_S_Sig2;
uint8 varTest_S_Sig3;
uint8 varTest_S_Sig4;
uint8 varTest_S_Sig5;
uint8 varTest_S_Sig6;


uint8 varTest_R_Sig1;
uint8 varTest_R_Sig2;

uint8 varTest_R_Sig3;
uint8 RxNum=0;


#define  CAN_TRANSCV_ENABLE(chn)     PINS_DRV_ClearPins(CAN_STB_PORT, (1 << (chn)))

#define  CAN_TRANSCV_DISABLE(chn)    PINS_DRV_SetPins(CAN_STB_PORT, (1 << (chn)))

/*LED DS1 on ACU board is indicated as ECU running state.*/
void ACU_RunIndTask(void )
{

//	PINS_DRV_TogglePins(DS1_PORT, (1 << DS1));
}


/*This function do low layer init. of all the 8 channels.*/
void ACU_CanLowInit(void)
{
	flexcan_data_info_t  nmRxMb;
	/*CAN transceiver enable*/
	CAN_TRANSCV_ENABLE(0);

	/*Can low layer driver init.*/
    FLEXCAN_DRV_Init(INST_CANCOM1, &canCom1_State, &canCom1_InitConfig0);
//    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1,5,&nmRxMb,0x1B000000);

    flexcan_data_info_t dataInfo =
    {
            .data_length = 8U,
            .msg_id_type = FLEXCAN_MSG_ID_STD,
            .enable_brs  = false,
            .fd_enable   = false,
            .fd_padding  = 0U
    };

   // RxNum=CANIF_CFG_MAILBOX_PDUIDLAST(1);  通过去读取这个宏定义来定多少个接收邮箱，发送邮箱要在这个基础上增加，不然错误的

   FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 0, &dataInfo, 0x210);
   FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 1, &dataInfo, 0x610);//先测试，后面再改
   FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 2, &dataInfo, 0x614);//先测试，后面再改
   //FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 3, &dataInfo, 0x610);//先测试，后面再改

    FLEXCAN_DRV_InstallEventCallback(INST_CANCOM1,FlexCanRxTxIntruptcallback1,NULL);
}

void FlexCanRxTxIntruptcallback1(uint8_t instance,
                flexcan_event_type_t eventType,
                uint32_t buffIdx,
                struct FlexCANState *driverState)
{
	//state->callback(instance, FLEXCAN_EVENT_RX_COMPLETE, mb_idx, state);
	//state->callback(instance, FLEXCAN_EVENT_TX_COMPLETE, mb_idx, state);


# if defined(C_ENABLE_CAN_FD_FULL)


#endif
	if(eventType==FLEXCAN_EVENT_RX_COMPLETE)
	{
        uint8  tempData[64],i;
        Can_PduType pdu;
    //    tCanMsgObj64          BufRf;             /*!< RFID, RFPTR, RFFDSTS, RFDF[] */

       // driverState->mbs[mb_idx].mb_message
        /* Get pdu */

        for(i=0;i<64;i++)
        {
        	tempData[i]=driverState->mbs[buffIdx].mb_message->data[i];
        }
        pdu.length=driverState->mbs[buffIdx].mb_message->dataLen;
        pdu.id=driverState->mbs[buffIdx].mb_message->msgId;
        pdu.sdu = tempData;///* mailbox ID to hardware object ID */

        CanInterruptRxFifo(pdu);
     //   CanIf_RxIndication(CAN_HWOBJ_CFG(CAN_MBID_TO_HWOBJ(Controller,buffIdx)).CanObjectId,
     //   		pdu.id, pdu.length, pdu.sdu);


     //   CanNm_RxIndication(0,pdu.id,pdu.length,pdu.sdu);
	}

	if(eventType==FLEXCAN_EVENT_TX_COMPLETE)
	{
		CanInterruptTx();

		// CanIf_TxConfirmation(Can_Cntrl[Controller].TxPduHandles[buffIdx]);
	}

}

void BSW_Init(void)
{


	//    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 1, &dataInfo, 0x70D);


	    EcuM_Init();
	    EcuM_StartupTwo();
	    ComControl_Init_Runnable();

}

/******************************************************************************/
/*
 * Brief               <Task_10ms>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
void APPTask_10ms(void)
{
	  /* call runnable */
	      BswM_MainFunction();

	      /* call schedulable entity */
	      CanNm_MainFunction();

	      /* call schedulable entity */
	      CanSM_MainFunction();

	      /* call schedulable entity */
//	      Can_MainFunction_BusOff();

	      /* call schedulable entity */
	      Can_MainFunction_Mode();

	      /* call schedulable entity */
//	      Can_MainFunction_Wakeup();

	      /* call schedulable entity */
	      Com_MainFunctionRx();

	      /* call schedulable entity */
	      Com_MainFunctionTx();

	      /* call runnable */
	      Dcm_MainFunction();

	      /* call runnable */
	      Dem_MasterMainFunction();

	      /* call runnable */
	      Dem_SatelliteMainFunction();

	      /* call runnable */
	      EcuM_MainFunction();

}
/******************************************************************************/
/*
 * Brief               <Task_1ms>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
void APPTask_1ms(void)
{

}
/******************************************************************************/
/*
 * Brief               <APPCANMail0_4Receive>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
void APPCANMail0_4Receive(void)
{
	   flexcan_msgbuff_t recvBuff;
       uint8 i;
       status_t result;

		   for(i=0;i<3;i++)
		   {
			  //FLEXCAN_DRV_Receive(INST_CANCOM1, i, &recvBuff);
			   result = FLEXCAN_DRV_ReceiveBlocking(
					   INST_CANCOM1,
			       i,
				   &recvBuff,
			       2);
		   }

}

/******************************************************************************/
/*
 * Brief               <Task_5ms>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
void APPTask_5ms(void)
{
	 /* call schedulable entity */
	      CanTp_MainFunction();

	     Runnable_Signal_Process();
}

/******************************************************************************/
/*
 * Brief               <Task_20ms>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
void APPTask_20ms(void)
{
	  /* call runnable */
	      ComM_MainFunction_0();

	     // Runnable_Signal_Process();
}
/******************************************************************************/
/*
 * Brief               <Task_50ms>
 * Param-Name[in]      <None>
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>
 * PreCondition        <None>
 * CallByAPI           <None>
 */
/******************************************************************************/
void APPTask_50ms(void)
{
	 /* call runnable */
	  Dio_Control_Runnable();
}











