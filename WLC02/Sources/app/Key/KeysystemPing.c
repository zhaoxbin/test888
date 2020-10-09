/*
 * systemPing.c
 *
 *  Created on: 2019Äê7ÔÂ3ÈÕ
 *      Author: jiangxl
 */

#include "Cpu.h"
#include "global.h"
#include "hal.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"
#include "Qi_spec.h"
#include "systemDef.h"

static uint8_t  sigStrength;
static boolean  bStartSigTimer;


/*=================================================================
                  Timing Spec.
1)T_PING:  Primary Celll current amplitude reashes 50% -> START of a Packet
2)T_FIRST: START of the first packet -> END of the first packet
====================================================================*/

void SPingEntry(EventId eventId, uint8_t eventParam)
{

	Coils CoilIndex;

	SetKeyChargeSts(KChargeNoCharge);
	ResetPID();
	InitFodLossValue();
	//bStatePing = FALSE;

	CoilIndex = HAL_GetKeyCoilSel();
	if(HAL_GetKeyCoilObjSts() == TRUE)
	{
		SelectCoils(CoilIndex);

		//SelectCoils(CoilOne);
		//SelectCoils(CoilTwo);
		HAL_EnablePower();
		StartKeyTimer1(100);

		bStartSigTimer = TRUE;
	}

}


void SPingExit()
{
	StopAllKeyTimers();
}



boolean SPingAction(EventInfo* pEvtInfo)
{
//  Packet  newPacket;
	if(IsKeyTimer1Expired())
	{

		pEvtInfo->eventId = EvtTimeOut;
//	  gTerminateCode = PING_TIME_OUT;
//		#if 1
//    if(Fod(StatePing))
//    {
//       pEvtInfo->eventId = EvtUnsafe;
//       pEvtInfo->param1 = UnsafePingFOD;
//    }
//		#endif
		//LED_RED_TOGGLE;//PA3
//    ResetPreRxDetectFlag();
		return TRUE;
	}

	if(bNewMessage)
	{
		bNewMessage = FALSE;
		if(RxPacket[0] == HEADER_SIGNAL_STRENGTH)
		{
			pEvtInfo->eventId = EvtMsgSigStrength;
			pEvtInfo->param1  = RxPacket[1];
			sigStrength =  RxPacket[1];
		}
		else if(RxPacket[0] == HEADER_END_POWER_TRANSFER)
		{
			pEvtInfo->eventId = EvtMsgEPT;
			pEvtInfo->param1  = RxPacket[1];
		}
		else
		{
			pEvtInfo->eventId = EvtMsgUnexpected;
		}
		//variable_clear();
		return TRUE;
	} //if(bNewMessage)
	return FALSE;

}


