/*
 * systemTask.c
 *
 *  Created on: 2019年6月28日
 *      Author: jiangxl
 */


#include "defines.h"
#include "cpu.h"
#include "hal.h"
#include "systemTimers.h"
#include "systemStatus.h"
#include "systemSmSetting.h"
#include "canCom1.h"

#include "flexcan_driver.h"

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
#include "Rte_NvM.h"
#include "SchM_Fee_30_SmallSector.h"
#include "SchM_Fls.h"
#include "Rte_Os_OsCore0_swc.h"

#include "Rte_SWC_WLCAPP.h"

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
#include "SchM_NvM.h"
#include "Rte_Hook.h"

#include "Com.h"
#include "Can.h"
#include "Canif.h"
#include "CDDNIO.h"
#if defined(IL_ASRCOM_VERSION)
# define RTE_USE_COM_TXSIGNAL_RDACCESS
#endif

#include "Rte_Cbk.h"

#include "Rte_Communication_Read_APP.h"
#include "nm.h"
#include "NvM.h"
#include "Rte_SWC_WLCAPP_Type.h"
#include "dem_lcfg.h"
#include "flash_driver.h"

#include "Dem_Memory_Interface.h"
#include "Dcm_CoreCbk.h"
//#include "BsWM_Private_Cfg.h"
#define NUM_1MS_COUNTS_FOR_10MS         10U
#define NUM_10MS_COUNTS_FOR_100MS       10U
#define NUM_100MS_COUNTS_FOR_1SEC       10U
#define NUM_1SEC_COUNTS_FOR_1MIN        60U
#  define Rte_Call_PpNvMOdometerCtApMySwc_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)arg1, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#define MaxEntry   18
StateId KeycurrentState,KeynextState;

EventInfo eventInfo;
StateTransit* pStateTransit;

SysStateId SyscurrentState,SysnextState;

SysEventInfo SyseventInfo;
SysStateTransit* SyspStateTransit;

//boolean	bNfcNoblocking;
NM_WLC_0X538 		NM_WLC_Params;
WLC_01_0X3E3 		WLC_01_Params;
WLC_02_0X340 		WLC_02_Params;

CGW_03_0x10C 		CGW_03_Params;
CGW_WLC_0x3BE 		CGW_WLC_Params;
CGW_02_0x2C3 		CGW_02_Params;
CGW_TCU_01_0x3B2 	CGW_TCU_01_Params;
CDC_IC_01_0x3AA		CDC_IC_01_Params;
BCU_04_0x5B			BCU_04_Params;
CDC_WLC_0x2BA		CDC_WLC_Params;
CDC_BTWIFI_Command	CdcBtWifiCmd;
WLC_DEVLP_02_0x4BC	WLCDevlpCommand;


int Count5;
int Count20;

int CounttestWake;
int CounttestWake1;
extern ComM_ModeType MaxMod;
extern ComM_ModeType GetRequestedComMode;
extern ComM_ModeType GetCurrentComMode;
typedef struct
{
	uint16 w1msCount;
	uint16 w10msCount;
	uint16 w100msCount;
	uint16 w1secCount;
	uint16 w1minCount;
} TIMER_DATA;

//APP_ERROR_TYPE gApp_error = APP_SUCCESS;
boolean GetKeyEvent(StateId KeycurrentState, EventInfo* pEventInfo)
{
	boolean ret = FALSE;

//	if(SafetyMonitor(pEventInfo))
//    {
//       ret = TRUE;		//1?±?°2è??à2a
//    }
    //LED_TEST_TOGGLE;
    if((*(SM_Table[KeycurrentState].hStateAction))(pEventInfo))
    {
       ret = TRUE;
    }

    return ret;
}

static void KeyChargeRun()
{
	uint8_t i;

	if(GetKeyEvent(KeycurrentState, &eventInfo))
	{
		if((KeycurrentState < StateCount)&&(eventInfo.eventId < EventCount))
		{
			pStateTransit = SM_Table[KeycurrentState].pStateTransit;               //Get current state's transaction table 'StateTrans'
			i=0;
			while(pStateTransit[i].eventId != EvtNull)
			{
				if(pStateTransit[i].eventId == eventInfo.eventId)                 //search for the state transition for the current event
				{
					KeynextState = pStateTransit[i].nextState;
					if(KeynextState != KeycurrentState)                                 //if the state changes, call exit function of current state, and entry function of next state
					{
						(*SM_Table[KeycurrentState].hStateExit)();
						(*SM_Table[KeynextState].hStateEntry)(eventInfo.eventId, eventInfo.param1);
						KeycurrentState = KeynextState;
					}
					break;
				}
				i++;
			}//for
		}// if((currentState < StateCount)&&(eventInfo.eventId < EventCount))
	}//if(GetEvent(...))
}

boolean GetSysEvent(SysStateId SyscurrentState, SysEventInfo* pEventInfo)
{
	boolean ret = FALSE;


    //LED_TEST_TOGGLE;
    if((*(Sys_SM_Table[SyscurrentState].SyshStateAction))(pEventInfo))
    {
       ret = TRUE;
    }

	/*if(SyscurrentState!=SysStateFault)
	{
		if(SafetyMonitor(pEventInfo))
		{
			ret = TRUE;		//1?±?°2è??à2a
		}
	}*/

    return ret;
}

static void SystemStsRun()
{
	//uint8_t i;

	if(GetSysEvent(SyscurrentState, &SyseventInfo))
	{
		switch(SyseventInfo.SyseventId)
		{
		case EvtSysTransNext:
	    	   SysnextState = (SysStateId) SyseventInfo.Sysparam1;
	           break;

	       //case EvtFod:
	       //case Evtprotect:
	       //case EvtInternalError:
		case EvtSysUnsafe:
			SysnextState = SysStateFault;
			break;
		case EvtSysChargeDone:
		case EvtSysSearchKey:
			SysnextState = SysStatePause;
			break;
		default:
			break;

		}
	}
	
	
	if(SysnextState != SyscurrentState) //if the state changes, call exit function of current state, and entry function of next state
	{
		(*Sys_SM_Table[SyscurrentState].SyshStateExit)();
		(*Sys_SM_Table[SysnextState].SyshStateEntry)(SyseventInfo.SyseventId, SyseventInfo.Sysparam1);
		SyscurrentState = SysnextState;
	}
	
}
uint8 Wakupflg=0,wakeup2=0;

extern flash_ssd_config_t pSSDConfig;

uint32 adminAndStatusSize=0;
uint32 MemoryEntryStartAddress=0;

void BswNvMReadAll(void)
{
	uint8 RequestResultPtr,i=0;
/*
	NvM_ReadAll();
	{
		do
		{
		  Fls_MainFunction();
		  Fee_30_SmallSector_MainFunction();
		  Fls_MainFunction();
		  NvM_MainFunction();
		  NvM_GetErrorStatus (0,  &RequestResultPtr);
		}
	//	while(1);
		while( RequestResultPtr == NVM_REQ_PENDING);


		if ( RequestResultPtr != NVM_REQ_OK )
		{
		 // CANoeAPI_WriteString("NvM_ReadAll() not finished with NVM_REQ_OK!");
		}
	}
*/


	HAL_ReadEEPROMMemory((uint8*)&Dem_Cfg_GetAdminData(), 0x14000000, Dem_Cfg_MemoryDataSize[0]);
	HAL_ReadEEPROMMemory((uint8*)&Dem_Cfg_GetStatusData(),0x14000000+Dem_Cfg_MemoryDataSize[0], Dem_Cfg_MemoryDataSize[1]);
	adminAndStatusSize=0x14000000+Dem_Cfg_MemoryDataSize[0]+Dem_Cfg_MemoryDataSize[1];
	for( i=0;i<MaxEntry;i++)
	{
		MemoryEntryStartAddress=adminAndStatusSize+i*Dem_Cfg_MemoryDataSize[2];
		HAL_ReadEEPROMMemory((uint8*)Dem_Cfg_MemoryEntry[i],MemoryEntryStartAddress, Dem_Cfg_MemoryDataSize[2]);
		if(((Dem_Cfg_MemoryEntry[i]->EventId)>22) ||(Dem_Cfg_MemoryEntry[i]->EventId<1))
		{
			Dem_MementryInitFromApp(i);
		}
	}


}

void BswNvMWriteAll(void)
{
	uint8 i=0,j=0;
/*
	uint8 RequestResultPtr;

	NvM_WriteAll();
	{
		do
		{
		  Fls_MainFunction();
		  Fee_30_SmallSector_MainFunction();
		  Fls_MainFunction();
		  NvM_MainFunction();
		  NvM_GetErrorStatus (0,  &RequestResultPtr);
		}
		while(1);
	//	while( RequestResultPtr == NVM_REQ_PENDING);
		if ( RequestResultPtr != NVM_REQ_OK )
		{
		 // CANoeAPI_WriteString("NvM_ReadAll() not finished with NVM_REQ_OK!");
		}
	}

	*/     //FLASH_DRV_EEEWrite(&pSSDConfig, TargetAddress, Length, SourceAddressPtr);
	//Dem_Cfg_MemoryDataSize   Dem_Cfg_MemoryEntry
	/*
	 *
	 */


	FLASH_DRV_EEEWrite(&pSSDConfig, 0x14000000,                           Dem_Cfg_MemoryDataSize[0], (uint8*)&Dem_Cfg_GetAdminData());
	FLASH_DRV_EEEWrite(&pSSDConfig, 0x14000000+Dem_Cfg_MemoryDataSize[0], Dem_Cfg_MemoryDataSize[1], (uint8*)&Dem_Cfg_GetStatusData());
	adminAndStatusSize=0x14000000+Dem_Cfg_MemoryDataSize[0]+Dem_Cfg_MemoryDataSize[1];


	for( i=0;i<MaxEntry;i++)
	{
		if(((Dem_Cfg_MemoryEntry[i]->EventId)<22)&&((Dem_Cfg_MemoryEntry[i]->EventId)>0))
		{
			if((Dem_Cfg_MemoryEntry[i]->EventId)<18)
			{
				j=Dem_Cfg_MemoryEntry[i]->EventId;
			}
			else
			{
				j=Dem_Cfg_MemoryEntry[i]->EventId-3;
			}

			if(j<=MaxEntry)
			{
				MemoryEntryStartAddress=adminAndStatusSize+(j-1)*Dem_Cfg_MemoryDataSize[2];
				FLASH_DRV_EEEWrite(&pSSDConfig, MemoryEntryStartAddress, Dem_Cfg_MemoryDataSize[2], (uint8*)Dem_Cfg_MemoryEntry[j-1]);
			}
			else //超限
			{

			}
		}

	}

	/*
	    for( i=0;i<MaxEntry;i++)
		{

			if(((Dem_Cfg_MemoryEntry[i]->EventId)<22)&&((Dem_Cfg_MemoryEntry[i]->EventId)>0))
			{
				MemoryEntryStartAddress=adminAndStatusSize+i*Dem_Cfg_MemoryDataSize[2];
				FLASH_DRV_EEEWrite(&pSSDConfig, MemoryEntryStartAddress, Dem_Cfg_MemoryDataSize[2], (uint8*)Dem_Cfg_MemoryEntry[i]);
			}
			else  //超限，不需要保存，没写
			{

			}

		}
		*/
}
void wakupprocess()
{
	 Can_MainFunction_Wakeup();
	//CanInterruptWakeup();

}
uint8  tempData[64],i,k;
Can_PduType pdu;
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

    //    tCanMsgObj64          BufRf;             /*!< RFID, RFPTR, RFFDSTS, RFDF[] */

       // driverState->mbs[mb_idx].mb_message
        /* Get pdu */
		Wakupflg++;
		if(Wakupflg>1)
		{
			Wakupflg=2;
		}
		if(wakeup2==0)
		{
			wakeup2=1;
			Can_MainFunction_Wakeup();


			Can_SetControllerMode(0, CAN_T_START);
			CanIf_SetPduMode( 0, CANIF_SET_RX_ONLINE );//CANIF_SET_TX_ONLINE
			CanIf_SetPduMode( 0, CANIF_SET_TX_ONLINE );
			Dcm_ComM_FullComModeEntered(0);
		}
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
		wakeup2=3;
		CanInterruptTx();

		// CanIf_TxConfirmation(Can_Cntrl[Controller].TxPduHandles[buffIdx]);
	}

}
void BSW_init(void)
{
    EcuM_Init();
    EcuM_StartupTwo();
    CDDEX_Init();
    DemStart();
   // ComControl_Init1_Runnable();
     //   RequestComModeFull_Runnable();
}
static void AppTask_5msHandle(void)
{
	  CanTp_MainFunction();

	  ComReadandWrite_Runnable();

	  Fee_30_SmallSector_MainFunction();//5ms
}


static void AppTask_20msHandle(void)
{
	   ComM_MainFunction_0();
}

int data,j,receivestatus;
int wake1flg=0;
flexcan_msgbuff_t recvBuff;//这里需要把这些变量定义为全局变量，如果放在局部变量的话，调试的时候一旦从上位机向板子发送数据板子就发生未知的中断跳转。
static void AppTask_1msHandle(uint16 wNumTicks)
{
#if 1
	Count5++;
	Count20++;
	CounttestWake++;
	CounttestWake1++;
	if(Count5>5)
	{
		AppTask_5msHandle();
		Count5=0;
	}

	if(Count20>20)
	{
		AppTask_20msHandle();
		Count20=0;
	}
	j++;
	if(j>12)
	{
		j=0;
	}
	//for(j=0;i<13;i++)
	{
		receivestatus=FLEXCAN_DRV_Receive(INST_CANCOM1, j, &recvBuff);
		if(0==receivestatus)
		{

		}
		else
		{
			 data=recvBuff.data[0];
		}
		 if(recvBuff.msgId==0x601 )
		 {

           data=recvBuff.data[0];
		 }
	}
/*
	if(CounttestWake>10000 && (wake1flg==0) )
	{
		Nm_NetworkRequest(0);
		//RequestComModeFull_Runnable();
		CounttestWake=0;
		wake1flg=1;

	}
	else
	{
	//	RequestComModeNOFull_Runnable();
	}
*/
	if(CounttestWake1>20000)
	{
		//Dem_MementryInitFromApp(0);
		//Dem_MementryInitFromApp(1);
		//Nm_NetworkRelease(0);
		CounttestWake1=0;
		// NvM_WriteAll();
		//RequestComModeNOFull_Runnable();
		//Rte_Call_PpNvMOdometerCtApMySwc_WriteBlock(NULL_PTR);
		DTCProcessRunable();

		for(k=1;k<3;k++)
		{
			Rte_Call_PpNvMOdometerCtApMySwc_WriteBlock(k);
		}
		BswNvMWriteAll();
		//Rte_Call_PpDiagnosticMonitor_DEM_EVENT_StartApplication_SetEventStatus(DEM_EVENT_STATUS_FAILED);
	//	BswNvMWriteAll();
		//CounttestWake=0;

	}



	if(CounttestWake>20000 )
	{
		CounttestWake=0;
		wake1flg=0;
	}
#endif

#if 1
	if(GetChargeFlag()==1)
	{
		KeyChargeRun();
	}
#endif


/*
    flexcan_msgbuff_t recvBuff;


    FLEXCAN_DRV_Receive(0, 0, &recvBuff);


    while(FLEXCAN_DRV_GetTransferStatus(INST_CANCOM1, 0) == STATUS_BUSY);

    if(recvBuff.msgId == 1)
    {

      //  PINS_DRV_TogglePins(GPIO_PORT, (1 << LED0));
    }

*/
}

static void AppTask_10msHandle(uint16 wNumTicks)
{

	    int i;
	    //flexcan_msgbuff_t recvBuff;
		for(i=0;i<13;i++)
		{
	//		 FLEXCAN_DRV_Receive(0, i, &recvBuff);
		}

#if 1


	      if(Wakupflg==1)
	      {
	    	////  Can_MainFunction_Wakeup();
	    	//  RequestComModeFull_Runnable();
	    	  Wakupflg=2;
	      }

	      if((Wakupflg>=2) &&
	         ((CGW_02_Params.VehState==Driver_present)||
	          (CGW_02_Params.VehState==Driving)||
			  (CGW_02_Params.VehState==Parked && CGW_02_Params.Comf_Ena==COMFENA)))
	      {
	    	  Nm_NetworkRequest(0);
	    	//  RequestComModeFull_Runnable();
	    	  gCanNMWakeupFlag= TRUE;
	      }
	     // else if((CGW_02_Params.VehState==Parked) && (CGW_02_Params.Comf_Ena==ComfNotEna)&&(wake1flg==0))
	      else if((CGW_02_Params.VehState==Parked) && (CGW_02_Params.Comf_Ena==ComfNotEna))
	      {
	    	  Nm_NetworkRelease(0);
	    	//  wake1flg=1;
	    	//  RequestComModeNOFull_Runnable();//如果调用这个，从 Prepare bus sleep---> repeat 时，不会快发，只有慢发
	      }

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

		      NvM_MainFunction();//10ms
		      Fls_MainFunction();//10ms
		      /* call runnable */
		      EcuM_MainFunction();
		//      CanTrcv_30_Tja1040_MainFunction();
		      CDDEX_MainFunction();
#endif
#if 1

		      HAL_GetCanParams();
		      HAL_SetCanParams();

		      if(bNfcNoblocking)
		      {
		    	  MeasureAll();
		    	  SystemStsRun();
		      }
#endif
}

static void AppTask_100msHandle(void)
{
	//HAL_KickWatchDog();
	WDOG_DRV_Trigger(INST_WATCHDOG1);
}

static void AppTask_1secHandler(void)
{

}

static void AppTask_1minHandler(void)
{


}

AppTask_Timer10Task()
{
	if(wakeup2==2)
	{
	//	Can_SetControllerMode(0, CAN_T_START);
	}
}

void AppTask_Poll(void)
{
    static TIMER_DATA TimerData;
    static uint16 wAppLastTimerTicks;

	uint16 wSecondsToAdd;
	uint16 wNumTicks;

	wNumTicks = ST_GetElapasedTime(wAppLastTimerTicks);
	wAppLastTimerTicks += wNumTicks;
	wAppLastTimerTicks &= 0xffffu;

	if (wNumTicks)
	{
		// 1 ms Tick
		if (1U <= wNumTicks)
		{
			TimerData.w1msCount += wNumTicks;

			AppTask_1msHandle(wNumTicks);

			// 10 MS Tick
			if (NUM_1MS_COUNTS_FOR_10MS <= TimerData.w1msCount)
			{
				wNumTicks = TimerData.w1msCount;
				TimerData.w10msCount += (TimerData.w1msCount / NUM_1MS_COUNTS_FOR_10MS);
				TimerData.w1msCount %= NUM_1MS_COUNTS_FOR_10MS;

				AppTask_10msHandle(wNumTicks);

				// 100 MS Tick
				if (NUM_10MS_COUNTS_FOR_100MS <= TimerData.w10msCount)
				{
					TimerData.w100msCount += (TimerData.w10msCount / NUM_10MS_COUNTS_FOR_100MS);
					TimerData.w10msCount %= NUM_10MS_COUNTS_FOR_100MS;

					AppTask_100msHandle();

					// 1 SEC Tick
					if (NUM_100MS_COUNTS_FOR_1SEC <= TimerData.w100msCount)
					{
						wSecondsToAdd = (TimerData.w100msCount / NUM_100MS_COUNTS_FOR_1SEC);
						TimerData.w100msCount %= NUM_100MS_COUNTS_FOR_1SEC;
						TimerData.w1secCount += wSecondsToAdd;

						AppTask_1secHandler();

						if (NUM_1SEC_COUNTS_FOR_1MIN <= TimerData.w1secCount)
						{
							TimerData.w1minCount += (TimerData.w1secCount / NUM_1SEC_COUNTS_FOR_1MIN);
							TimerData.w1secCount %= NUM_1SEC_COUNTS_FOR_1MIN;

							AppTask_1minHandler();
						}
					}
				}
			}
		}
	}
}

void KeyChargeStateInit()
{

	KeycurrentState = StateSelection;
}

void KeyChargeSelectionEntry()
{
	(*SM_Table[StateSelection].hStateEntry)(eventInfo.eventId, eventInfo.param1);
}

void SysStateInit()
{

	SyscurrentState = SysStateOff;
}

void SysStateOffEntry()
{
	(*(Sys_SM_Table[SysStateOff].SyshStateEntry))(SyseventInfo.SyseventId, SyseventInfo.Sysparam1);
}
