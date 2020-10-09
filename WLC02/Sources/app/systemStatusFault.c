/*
 * systemStatusFault.c
 *
 *  Created on: 2020Äê1ÔÂ10ÈÕ
 *      Author: jiangxl
 */


#include "Cpu.h"
#include "hal.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"

static SysUnsafeCode  	SysunsafeCode;
WLC_01_0X3E3 			WLC_01_Params;
CGW_02_0x2C3 			CGW_02_Params;

void SysFaultEntry(SysEventId eventId, uint8_t eventParam)
{

	//StopAllSysTimers();
	HAL_DisablePower();				// stop key charge
	HAL_UartSendCommand(PChargeDisable);			// stop phone charge
	SysunsafeCode = eventParam;

	switch(SysunsafeCode)
	{
	case SysUnsafeOV:
		WLC_01_Params.WLCFailSts = FailTypeOverVol;
		break;
	case SysUnsafeUV:
		WLC_01_Params.WLCFailSts = FailTypeUnderVol;
		break;
	case SysUnsafeOTC5:
	case SysUnsafeOTC6:
	case SysUnsafeOTC7:
		WLC_01_Params.WLCFailSts = FailTypeOverTemp;
		gTestResp_Data[3] = 0x1;
		break;
	case SysUnsafeOC:
		break;
	case SysUnsafePOV:
	case SysUnsafePUV:
	case SysUnsafePOT:
	case SysUnsafePOC:

		break;
	default:
		break;
	}

}


void SysFaultExit()
{

	WLC_01_Params.WLCFailSts = FailTypeNoFailure;
}


boolean SysFaultAction(SysEventInfo* pEvtInfo)
{

	SysEventInfo evtInfo;

	if(!SafetyMonitor(&evtInfo))
	{
		gTestResp_Data[3] = 0x0;
		pEvtInfo->SyseventId= EvtSysTransNext;
		pEvtInfo->Sysparam1 = SysStateStandby;
		return TRUE;
	}

	if(((CGW_02_Params.VehState==Parked)&&(CGW_02_Params.Comf_Ena==ComfNotEna))||
					(CGW_02_Params.VehState==Software_Update))		// Parked or software updated or go to sleep
	{
		pEvtInfo->SyseventId= EvtSysTransNext;
		pEvtInfo->Sysparam1 = SysStateOff;
		return TRUE;
	}

	return FALSE;

}


