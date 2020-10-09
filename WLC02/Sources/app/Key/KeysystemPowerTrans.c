/*
 * systemPowerTrans.c
 *
 *  Created on: 2019Äê7ÔÂ3ÈÕ
 *      Author: jiangxl
 */

#include "global.h"
#include "Cpu.h"

#include "Qi_spec.h"
#include "systemDef.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"
#include "hal.h"
#include "ftm_hw_access.h"

/*=================================================================
                  Timing Spec.
1)T_TIMEOUT:  START of Configuration Packet -> START of the first Control Error Packet
2)T_TIMEOUT:  START of preceding Control Error Packet -> START of a Control Error  Packet

3)T_POWER:    START of Configuration Packet -> START of the first Received Power Packet
4)T_POWER:    START of preceding Received Power Packet -> START of a Received Power Packet


2)T_MAX:  Start of a packet -> correctly receive that packet
====================================================================*/
//static uint8_t	chargeStatus;
static uint8_t  controlError = 0;
static uint8_t  receivedPower ;//= 0;
static uint8_t  holdOffTime   = T_DELAY_MIN;
static uint8_t  bFirstMessage;// = FALSE;

static uint16_t actCurrent;
static uint16_t actVol;
//static boolean  firstDpm;

//static uint8_t  ovCurrentCounter;

//static boolean  preRxDetectFlag = FALSE;
//static uint8_t  msCounter;     //10 mins
//static boolean  startFlag;

//static boolean  upFlag;
//static uint8_t  upCounter;

//uint32			FrequencyHz;

//static sint8      	sControlError;
//static sint8      	presControlError  = 0;
//static sint16      	MinDutyDiv;
//static sint16      	MaxDutyDiv;
//static uint32		FrequencyHz;

uint16				VpwmPeriod;

//static uint32		DutyPercent;

PidType				adjustType;

static uint16	period;
sint8	sControlError;


void SPowerTransEntry(EventId eventId, uint8_t eventParam)
{

  StartKeyTimer1(T_TIMEOUT);
  //StartTimer1(T_TIMEOUT - TIMER3_DELAY);
  StartKeyTimer2(T_POWER);
  //InitLEDs();

  bFirstMessage = TRUE;
  actCurrent = 0;
  actVol = 0;
//  ovCurrentCounter = 0;

//  msCounter = TIMER_MSCOUNT;
//  startFlag = FALSE;
//  firstDpm = TRUE;

//  upFlag   = TRUE;
//  upCounter = 0;
  period = PWM_MCLOCK/HAL_AP_FREQUENCY;

  SetKeyChargeSts(KChargeOnCharging);


}

void SPowerTransExit()
{
	StopAllKeyTimers();
}

boolean SPowerTransAction(EventInfo* pEvtInfo)
{
	Packet	newPacket;
	//uint8   packetHeader;
	//uint8   message;

	if(IsKeyTimer1Expired() )//Control Error TimeOut
	{
		pEvtInfo->eventId = EvtTimeOut;
        //gTerminateCode = CE_TIME_OUT;
        return TRUE;
	}

	if(IsKeyTimer2Expired())//Receive Power TimeOut
	{
		pEvtInfo->eventId = EvtTimeOut;
		//gTerminateCode = RPP_TIME_OUT;
		return TRUE;
	}

	if(GetAvgRevPower())
	{
	//	if(Fod(StatePowerTrans))
	//	{
	//		pEvtInfo->eventId = EvtObjectDetected;
	//		pEvtInfo->param1  = UnsafeFOD;
	//		return TRUE;
	//	}
	}

	if(IsKeyTimer3Expired())      //tDelay is expired and the new Operatinf Point can be adjusted
	{
		StopKeyTimer3();
		{
			CalculateNewFrequency(controlError);
			/*if(controlError!=0)
			{
				sControlError = (sint8)controlError;
				period += sControlError/PID_SCALE;
				//HAL_SetPwmPeriod(period);
				//FTM_DRV_UpdatePwmPeriod(INST_FLEXTIMER_PWM1, FTM_PWM_UPDATE_IN_TICKS, period, FALSE);
				FTM_DRV_SetMod(g_ftmBase[INST_FLEXTIMER_PWM1],period);
				FTM_DRV_SetSoftwareTriggerCmd(g_ftmBase[INST_FLEXTIMER_PWM1], true);
			}*/
		}
		bNewMessage = FALSE;
	}

	if(bNewMessage)      //received the message successfully
	{
		bNewMessage = FALSE;

		if(RxPacket[0] == HEADER_CONTROL_ERROR)
		{
			RestartKeyTimer1();                  //restart the timer for detecting T_TIMEOUT
			StartKeyTimer3(holdOffTime);      //to start adjust frequen after holdoff time
			controlError = RxPacket[1];
			StopKeyTimer4();

			//CalculateNewFrequency(controlError);

		}
		else if(RxPacket[0]== HEADER_RECEIVED_POWER)
		{
			RestartKeyTimer2();          //restart the timer for detecting T_POWER
			receivedPower = RxPacket[1];
			//delayMs_hd(4); 				//delay 4ms
			StartAvgRevPower();
		}
		else if(RxPacket[0] == HEADER_END_POWER_TRANSFER)
		{
			pEvtInfo->eventId = EvtMsgEPT;
			pEvtInfo->param1 = RxPacket[1];
			return TRUE;
		}

		if(bFirstMessage)
		{
			bFirstMessage = FALSE;
			if(newPacket.header == HEADER_POWER_CONTROL_HOLD_OFF)
			{
				pEvtInfo->eventId = EvtMsgUnexpected;
				return TRUE;
			}
		}
	}

  return FALSE;

}


uint16 GetActCurrent()
{
   return actCurrent;
}

uint16 GetActVol()
{
   return actVol;
}

//uint8 GetchargeStatus()
//{
//   return chargeStatus;
//}

//void ResetPreRxDetectFlag()
//{
//   preRxDetectFlag = FALSE;
//}


void SPowerTansSetHoldOfftime(uint8_t holdOffTimeMsg)
{
  holdOffTime = holdOffTimeMsg;
}

uint8_t GetRecvPower()
{
  return receivedPower;
}

uint8_t GetControlError()
{
  return controlError;
}




