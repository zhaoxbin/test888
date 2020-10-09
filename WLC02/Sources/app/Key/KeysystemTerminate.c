/*
 * systemTerminate.c
 *
 *  Created on: 2019Äê7ÔÂ3ÈÕ
 *      Author: jiangxl
 */

#include "global.h"
#include "Cpu.h"
#include "hal.h"
#include "systemDef.h"
#include "Qi_spec.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"


static uint8  codeEPT;
static uint8  timeoutCnt;//=0;
static boolean bIsObjectDetected = TRUE;

//Evevnt EvtMsgTerminate, EvtMsgUnexpected, EvtMsgWrongValue, EvtTimeout1 and EvtTimeout2 all can end up to this state

void STerminateEntry(EventId eventId, uint8_t eventParam)
{
	if(eventParam != EPTC_RECONFIGURE)
	{
		//RemovePowerTransfer();
		HAL_DisablePower();
	}
	StopAllKeyTimers();
  //ResetMessage();
	timeoutCnt =1;
	StartKeyTimer1(TIME_OUT_TERMINATE);


	codeEPT = EPTC_UNKNOWN;       //if event is not EvtMsgTerminate, set codeEPT to be EPTC_UNKNOWN
	if(eventId == EvtMsgEPT)
	{
		codeEPT = eventParam;
//    if(eventParam != EPTC_RECONFIGURE)
//    {
//        InitSoftwarePing();
//    }
		if(codeEPT == EPTC_CHARGE_COMPLETE ||
				codeEPT == EPTC_NO_RESPONSE    ||
				codeEPT == EPTC_OVER_TEMPERATURE )
		{
			timeoutCnt = TIME_OUT_CHARGE_COMPLETE_LOOP;
			StartKeyTimer1(TIME_OUT_CHARGE_COMPLETE);
			StartKeyTimer2(350); // start Detecting Rx  every 350 ms
			SetKeyChargeSts(KChargeRxChargeComplete);
		}
		else if(codeEPT == EPTC_INTERNAL_FAULT ||
				codeEPT == EPTC_BATTERY_FAILURE )
		{
			StartKeyTimer2(350);
			SetKeyChargeSts(KChargeRxBatteryFailure);
		}
	}
	else
	{

	}

}

void STerminateExit()
{
	StopAllKeyTimers();
}


boolean STerminateAction(EventInfo* pEvtInfo)
{
	pEvtInfo->param1 = 0;
	switch(codeEPT)
	{
	case EPTC_RECONFIGURE:
	{
		pEvtInfo->eventId = EvtReconfig;
		return TRUE;
	}
	break;

	case EPTC_NO_RESPONSE:
    case EPTC_CHARGE_COMPLETE:
    case EPTC_OVER_TEMPERATURE:
    {
    	bIsObjectDetected = TRUE;
        if(codeEPT == EPTC_CHARGE_COMPLETE)
        {
          //SetLEDs(LED_ChargeCompleted);
        }
        else if((codeEPT == EPTC_OVER_TEMPERATURE) || (codeEPT == EPTC_NO_RESPONSE))
        {
           //SetLEDs(LED_OverCoilTemperature);
        }

        if(IsKeyTimer2Expired())
        {
            RestartKeyTimer2();
            bIsObjectDetected = (boolean)IsRxDetected();
            RestartKeyTimer2();
        }

        if(IsKeyTimer1Expired())
        {
            timeoutCnt--;
            StartKeyTimer1(TIME_OUT_CHARGE_COMPLETE);
        }

        if(timeoutCnt == 0 || !bIsObjectDetected)
        {
          //SetLEDs(LED_Standby);
          pEvtInfo->eventId = EvtRestart;
          return TRUE;
        }

    }
    break;

    case EPTC_INTERNAL_FAULT:
    case EPTC_BATTERY_FAILURE:
    {
    	bIsObjectDetected = TRUE;
//       SetLEDs(LED_OverCurrent);
        if(IsKeyTimer2Expired())
        {
            RestartKeyTimer2();
            bIsObjectDetected = (boolean)IsRxDetected();
            RestartKeyTimer2();
        }

        if(!bIsObjectDetected)
        {
          //SetLEDs(LED_Standby);
          pEvtInfo->eventId = EvtRestart;
          return TRUE;
        }

    }
    break;

    case EPTC_UNKNOWN:
    case EPTC_OVER_VOLTAGE:
    case EPTC_OVER_CURRENT:
    default:
    {
    	if(IsKeyTimer1Expired())
    	{
    		pEvtInfo->eventId = EvtRestart;
    		return TRUE;
    	}
    }
    break;

	}

	return FALSE;

}


uint8 GetCodeEPT()
{
   return codeEPT;
}

void SetCodeEPT()
{
   codeEPT = EPTC_UNKNOWN;
}






