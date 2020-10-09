/*
 * systemIdConfig.c
 *
 *  Created on: 2019Äê7ÔÂ3ÈÕ
 *      Author: jiangxl
 */

#include "Cpu.h"
#include "global.h"
#include "Qi_spec.h"
#include "systemDef.h"
#include "hal.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"

/*=================================================================
                  Timing Spec.
1)T_NEXT:  END of preceding packet -> START of a next packet
2)T_MAX:  START of a packet -> END of that packet
====================================================================*/



static uint8	nextPacketHeaderExpected;

static boolean  bInIdentificationStage;
static uint8  	countOpConfigPacket;
static boolean  bStartIdTimer;

void SIdentConfigEntry(EventId  eventId, uint8_t eventParam)
{

  countOpConfigPacket = 0;
//  ResetFodCounter();

  if(GetCodeEPT() == EPTC_RECONFIGURE)
  {
     bStartIdTimer = FALSE;
     bInIdentificationStage = FALSE;
     StartKeyTimer1(T_NEXT + T_MAX);
  }

  else
  {
     SPowerTansSetHoldOfftime(T_DELAY_MIN); //initialize hold off time
     StartKeyTimer1(T_NEXT + TIME_MARGIN); //header  //time out of not receiveing any packet,adding 20ms of margin
     bStartIdTimer = TRUE;
     bInIdentificationStage = TRUE;
     nextPacketHeaderExpected = HEADER_IDENTIFICATION;
  }

}


void SIdentConfigExit()
{
  StopKeyTimer1();
}

boolean SIdentConfigAction(EventInfo* pEvtInfo)
{
	//Packet  newPacket;

  //timeout for not receiving any packet

	if(IsKeyTimer1Expired() || IsKeyTimer2Expired())
	{
		pEvtInfo->eventId = EvtTimeOut;
		//gTerminateCode = CONFIG_TIME_OUT;
		return TRUE;
	}


	if(bStartIdTimer)
	{
		if(RxPacket[0]  == HEADER_IDENTIFICATION )
		{
			//StartTimer2(T_MAX);
			StopKeyTimer1();
			StartKeyTimer2(T_MAX);
			bStartIdTimer = FALSE;
			StartKeyTimer1(T_CONFIG);
		}
	}

  //TODO: time out T_MAX from start of a packet

	if(bNewMessage)
	{
		//#ifdef COMMTEST
		//LED_BLUE_TOGGLE;
		//#endif

		bNewMessage = FALSE;
		StartKeyTimer2(T_NEXT + T_MAX);
    //StopTimer2();
    //GetPacket(&newPacket);

    /*
    //check Qi TIming
    if( newPacket.timeStartToEnd > T_MAX)
    {
      pEvtInfo->eventId = EvtTimeOut;
      return TRUE;
    }*/

		if(RxPacket[0]  == HEADER_END_POWER_TRANSFER)
		{
			pEvtInfo->eventId = EvtMsgEPT;
			pEvtInfo->param1 = RxPacket[1];
			return TRUE;
		}
    //check the packet sequence
		if(bInIdentificationStage)
		{
			if(RxPacket[0] !=  nextPacketHeaderExpected)
			{
				pEvtInfo->eventId = EvtMsgUnexpected;
				return TRUE;
			}
			if(RxPacket[0] == HEADER_IDENTIFICATION)
			{
				if(gExt)
				{
					nextPacketHeaderExpected = HEADER_EXTENDED_IDENTIFICATION;
				}
				else
				{
				//	LED_TEST_TOGGLE;    //PD4
					bInIdentificationStage = FALSE;
				}
			}
			if(RxPacket[0] == HEADER_EXTENDED_IDENTIFICATION)
			{
				bInIdentificationStage = FALSE;
				StartKeyTimer1(T_CONFIG);
			}
		}
		else
		{
			if(RxPacket[0] == HEADER_POWER_CONTROL_HOLD_OFF)
			{
				uint8 holdOffTime = RxPacket[1];
				if((holdOffTime < T_DELAY_MIN) || (holdOffTime > T_DELAY_MAX))
				{
					pEvtInfo->eventId = EvtMsgWrongValue;
					return TRUE;
				}
				else
				{
					SPowerTansSetHoldOfftime(holdOffTime);
					countOpConfigPacket++;
				}
			}
			else if(RxPacket[0] == HEADER_CONFIGURATION)
			{
				StopKeyTimer1();
				if(gCountOptConfig != countOpConfigPacket)
				{
					pEvtInfo->eventId = EvtMsgWrongValue;
				}
				else
				{
					pEvtInfo->eventId = EvtMsgConfig;
				}
				return TRUE;
			}
			else if(RxPacket[0] > HEADER_POWER_CONTROL_HOLD_OFF)
			{
				countOpConfigPacket++;
			}
		}//if(bInIdentificationStage)... else
	}//if(IsPacketMessageNew())
	return FALSE;

}


