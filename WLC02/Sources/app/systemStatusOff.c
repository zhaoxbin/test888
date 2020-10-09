/*
 * systemStatusOff.c
 *
 *  Created on: 2020?2?9?
 *      Author: jiangxl
 */


#include "Cpu.h"
#include "hal.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"
#include "Nm.h"
#include "Rte_SWC_WLCAPP.h"
#include "NFC_Inerface.h"
#include "CDDNIO.h"
//
//static uint8_t   APCounter =0;
//extern boolean	gCanNMWakeupFlag;
extern boolean	gCanNMSleepFlag;
boolean			SleepHandleFlag;
CGW_02_0x2C3 	CGW_02_Params;

uint8* appnmStatePtr;
uint8* appnmModePtr;

//#ifndef LPCD_TEST
//NxpNci_LPCD_Cail_Results retVal_nfctask_lpcdcail = NxpNci_LPCD_Cail_Results_None;
//#endif

void SysOffEntry(SysEventId eventId, uint8_t eventParam)
{
	HAL_CanParamsInit();
	SetDevCheckFlag(FALSE);				// WLC Fail status flag reset
	SetObjDetFlag(TRUE);
	gCanNMWakeupFlag = FALSE;
	gCanNMSleepFlag = FALSE;
	SleepHandleFlag = FALSE;
#if 0
	 static int NFC_Flag_LPCD_Cail = 0;

	    /* LPCD?????? */

	if(NFC_Flag_LPCD_Cail == 0)
	{
		NFC_Flag_LPCD_Cail = 1;

		retVal_nfctask_lpcdcail = NFC_Task_LPCD_Cail(&gLPCD_CailValue);
	#ifdef LPCD_TEST
			ZB_LPCD_TEST[2]=(gLPCD_CailValue&0x0300)>>8;
			ZB_LPCD_TEST[3]=gLPCD_CailValue&0x00FF;
	#endif
	}
#endif
	StartSysTimer6(5000);			// Can sleep system after wake up
	StartSysTimer7(100);
	StartSysTimer8(1000);

}


void SysOffExit()
{


}

int NmgotoNormalFlg=0;
//extern int CounttestWake;
boolean SysOffAction(SysEventInfo* pEvtInfo)
{
	uint8 ret;

	ret = FALSE;

#if 1
	if((CGW_02_Params.VehState==Parked)&&(CGW_02_Params.Comf_Ena!=COMFENA))	// Parked and Not comfortable
	{
		if(IsSysTimer6Expired())
		{
			if(!SleepHandleFlag)
			{
			//	RequestComModeNOFull_Runnable();
			//Nm_NetworkRelease(0);
			//	WLC_Runnable();//???????,???
				SleepHandleFlag = TRUE;
			}
		//Nm_GetState(0,appnmStatePtr,appnmModePtr);//??appnmStatePtr  appnmModePtr  ????????
		//if(appnmModePtr==NM_MODE_BUS_SLEEP)

		}
	}
	else
	{
	//	if(NmgotoNormalFlg==1)//????????????,???????,???NM ?Normal??
		{

		//	RequestComModeFull_Runnable();
			NmgotoNormalFlg=0;
		}
#endif


#if 1
	// for key charge coil switch test, directly turn into charge state
		if(gCanNMWakeupFlag)
		{
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			//pEvtInfo->Sysparam1 = SysStateCharge;
			ret = TRUE;
		}

#endif
	}


	return ret;

}







