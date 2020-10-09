/*
 * systemStatusStandby.c
 *
 *  Created on: 2020年1月10日
 *      Author: jiangxl
 */


#include "Cpu.h"
#include "hal.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"

//zb add-2020.3.11
#include "NFC_Inerface.h"
#include "CDDNIO.h"

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
//
//static uint8_t   APCounter =0;

#ifndef LPCD_TEST
NxpNci_LPCD_Cail_Results retVal_nfctask_lpcdcail = NxpNci_LPCD_Cail_Results_None;
NxpNci_LPCD_Detect_Results retVal_nfctask_lpcddetect = NxpNci_LPCD_Detect_Results_None;

uint16_t gLPCD_CailValue = 0x0000;
#endif



void SysStandbyEntry(SysEventId eventId, uint8_t eventParam)
{
    KeyChargeStateInit();
    KeyChargeSelectionEntry();
    WLC_01_Params.WLCChrgRate = 0;			//Charge rate not started

#if 1
    static int NFC_Flag_LPCD_Cail = 0;

    /* LPCD校准只做一次 */

	if(NFC_Flag_LPCD_Cail == 0)
	{
		NFC_Flag_LPCD_Cail = 1;

		//retVal_nfctask_lpcdcail = NFC_Task_LPCD_Cail(&gLPCD_CailValue);
#ifdef LPCD_TEST
		ZB_LPCD_TEST[2]=(gLPCD_CailValue&0x0300)>>8;
		ZB_LPCD_TEST[3]=gLPCD_CailValue&0x00FF;
#endif
	}
#endif

}


void SysStandbyExit()
{


}


boolean SysStandbyAction(SysEventInfo* pEvtInfo)
{
	uint8 ret;
	//uint16 nfc_can_id = 0x0011;

	ret = FALSE;

	//retVal_nfctask_lpcddetect = NFC_Task_LPCD_Detect(&gLPCD_CailValue);
#ifdef LPCD_TEST
	if((NxpNci_LPCD_Detect_Results_Error != retVal_nfctask_lpcddetect) && (NxpNci_LPCD_Detect_Results_InvalidPara != retVal_nfctask_lpcddetect))
	{
		ZB_LPCD_TEST[1] = 0x00;
		CDDEX_SendCanFrameTo(WLC_DEVLP_01, ZB_LPCD_TEST,8);
	}

#endif

	WLC_01_Params.WLCChrgRate = 0;			//Charge rate not started

	//if(NxpNci_LPCD_Detect_Results_FoundObject == retVal_nfctask_lpcddetect)
	{
		if((CDC_WLC_Params.WLCChrgFctEnaReq) && (HAL_GetMuteSts()==0) &&
					(((CGW_02_Params.VehState==Parked)&&(CGW_02_Params.Comf_Ena==COMFENA))||
							(CGW_02_Params.VehState==Driver_present)||
							(CGW_02_Params.VehState==Driving)))
		{
			WLC_01_Params.WLCCtrlSts = 0;
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateCharge;
			ret = TRUE;
		}

	}

	if((CGW_02_Params.ImobEnaReq==ImobEnaAID1) || (CGW_02_Params.ImobEnaReq==ImobEnaAID2))
	{
		pEvtInfo->SyseventId= EvtSysTransNext;
		pEvtInfo->Sysparam1 = SysStateNfc;
		ret = TRUE;
	}
	else if(CdcBtWifiCmd.CdcBtReq || CdcBtWifiCmd.CdcWifiReq)
	{
		pEvtInfo->SyseventId= EvtSysTransNext;
		pEvtInfo->Sysparam1 = SysStateNfc;
		ret = TRUE;
	}
	else if(((CGW_02_Params.VehState==Parked)&&(CGW_02_Params.Comf_Ena==ComfNotEna))||
					(CGW_02_Params.VehState==Software_Update))		// Parked or software updated or go to sleep
	{
		pEvtInfo->SyseventId= EvtSysTransNext;
		pEvtInfo->Sysparam1 = SysStateOff;
		ret = TRUE;
	}


	if(IsSysTimer10Expired())				// First Device Detected, wait 3s to change fail status 8 to 0
	{
		StopSysTimer10();
		SetDevCheckFlag(FALSE);				// WLC Fail status flag reset
		SetObjDetFlag(TRUE);				//
	}


	return ret;

}

