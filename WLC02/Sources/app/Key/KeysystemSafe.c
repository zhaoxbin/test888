/*
 * systemSafe.c
 *
 *  Created on: 2019年7月3日
 *      Author: jiangxl
 */
#include "Cpu.h"
#include "hal.h"
#include "systemDef.h"
#include "Qi_spec.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"


static UnsafeCode  unsafeCode;
static EventId  evtId;

void SSafeEntry(EventId eventId, uint8_t eventParam)
{
	//RemovePowerTransfer();
	HAL_DisablePower();
	//InitLEDs();
	StopAllKeyTimers();
	unsafeCode = eventParam;
	evtId = eventId;
	ResetFodCounter();
	if(unsafeCode == UnsafeFOD || unsafeCode == UnsafePingFOD)
	{
      //StartTimer1(3000);
      //SetBuzzer(ToneAlways);
		StartKeyTimer1(350);
        StartKeyTimer2(3000);
        //SetBuzzer(ToneAlways);
        SetKeyChargeSts(KChargePowerTransferFOD);
	}
	else if(unsafeCode == UnsafeOverCurrent )
	{
		StartKeyTimer1(350);
		SetKeyChargeSts(KChargeOCP);
	}

//  InitSoftwarePing();

  #ifdef _I2C_MONITOR
  gTerminateCode = (BYTE)(unsafeCode + 15);
  SetI2CData(StatePowerTrans);
  #endif

}


void SSafeExit( )
{
  StopAllKeyTimers();
}

boolean IsRxDetected()
{
    boolean bOverCurrent = TRUE;
    uint16 current;
    current = HAL_GetPingCurrent();
    if((unsafeCode == UnsafePingFOD)&&(evtId == EvtUnsafe))
    {
        if(current < FOD_OUT_CURRENT_THRC)
        {
           bOverCurrent = FALSE;
        }
    }
    else
    {
        if(current < FOD2_OUT_CURRENT_THRC)

    	//if(current < DETECT_CURRENT_THRC)
        {
           bOverCurrent = FALSE;
        }
    }
    return bOverCurrent;
}


static boolean IsOverCurrent()
{
    boolean bOverCurrent = TRUE;

    if(IsKeyTimer1Expired())
    {
        RestartKeyTimer1();

        bOverCurrent = IsRxDetected();//电流最大值小于电流采样阈值bOverCurrent = 0
    }

    if(IsKeyTimer2Expired() || !bOverCurrent )
    {
        //StopBuzzer();   //不过流，则关闭蜂鸣器
    }

    return bOverCurrent;
}


boolean SSafeAction(EventInfo* pEvtInfo)
{
	//EventInfo evtInfo;

	switch(unsafeCode)
 	{
 	//case UnsafeOverCurrent:
	//	//SetLEDs(LED_OverCurrent);
	//	if(IsOverCurrent())
	//	{
	//		return FALSE;
	//	}
	//	break;

	case UnsafePingFOD:
	case UnsafeFOD:
		//SetLEDs(LED_FOD);
		if(IsOverCurrent())
		{
			return FALSE;
		}
		break;

  //OverVoltage, OverCoiltemperature and OverIcTemperature are rechecked by SafetyMonitor

	case UnsafeOverVoltage:
		//SetLEDs(LED_OverVoltage);
		break;

	case UnsafeOverCoilTemperature:
		//SetLEDs(LED_OverCoilTemperature);
		break;

	case UnsafeOverIcTemperature:
		//SetLEDs(LED_OverIcTemperature);
		break;

	default:
		//SetLEDs(LED_Standby);
		//pEvtInfo->eventId = EvtRestart;
		//return TRUE;
		break;

	}


	//if(!SafetyMonitor(&evtInfo))   //make sure ALL are good now, then exit the safe state
	//{
	//	pEvtInfo->eventId = EvtRestart;
		//SetLEDs(LED_Standby);
	//	return TRUE;
	//}


	return FALSE;

}

