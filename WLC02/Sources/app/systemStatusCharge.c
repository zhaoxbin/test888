/*
 * systemStatusCharge.c
 *
 *  Created on: 2020Äê1ÔÂ10ÈÕ
 *      Author: jiangxl
 */


#include "Cpu.h"
#include "hal.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"
#include "Qi_spec.h"

static uint8	bChargeFlag=0;
PWctStatus 		PChargeSts;
KWctStatus 		KChargeSts;

CGW_02_0x2C3 	CGW_02_Params;
CGW_WLC_0x3BE 		CGW_WLC_Params;
CDC_WLC_0x2BA		CDC_WLC_Params;
WLC_01_0X3E3 		WLC_01_Params;
WLC_02_0X340 		WLC_02_Params;
CDC_BTWIFI_Command		CdcBtWifiCmd;
WLC_DEVLP_02_0x4BC	WLCDevlpCommand;

boolean			ChargeMuteflag;
boolean			PosDetFlag;
uint8			posdetcnt;
Coils			KeyCoilIndex;

boolean			bFailStsFlag;
boolean			bDeviceDetFlag;
boolean			bObjDetFlag;
boolean			bPchargeFirstDet;

uint8 GetChargeFlag()
{
	return bChargeFlag;
}

void ResetChargeFlag()
{
	bChargeFlag = 0;
}

void SetDevCheckFlag(uint8 flag)
{
	bDeviceDetFlag = flag;
}

void SetObjDetFlag(uint8 flag)
{
	bObjDetFlag = flag;
}

void SysChargeEntry(SysEventId eventId, uint8_t eventParam)
{
	//bDeviceDetFlag = FALSE;
	bPchargeFirstDet = TRUE;
	bChargeFlag = 0;
	ChargeMuteflag = FALSE;
	PosDetFlag = FALSE;
	posdetcnt = 0;
#if 1
	ResetPID();
	HAL_KeyCoilSelInit();			//Start Coil Selection Timer
	KeyCoilIndex = CoilOne;
	HAL_KeyCoilDetStart(KeyCoilIndex);
#endif

	//if(!bDeviceDetFlag)
	//{
		//WLC_01_Params.WLCFailSts = FailTypeDevDetected;				// LPCD has detected Object existed
		//bDeviceDetFlag = TRUE;
		//StartSysTimer5(3000);
	//}
	//else
	//{
	//	WLC_01_Params.WLCFailSts = FailTypeNoFailure;				// No failure
	//}

}


void SysChargeExit()
{
	HAL_DisablePower();				// stop key charge
	HAL_UartSendCommand(PChargeDisable);			// stop phone charge
	ResetChargeFlag();			// reset Object detection flag
	//StopAllSysTimers();		// System Timer3 use for Fail status=8, no need to clear timer4 when change status
	StopSysTimer1();
	StopSysTimer2();
	StopSysTimer3();
	StopSysTimer4();
	if(bDeviceDetFlag && bObjDetFlag)
	{
		StartSysTimer10(3000);							// When disable charge function, restart timer 3s for fail status = 8
		bObjDetFlag = FALSE;
	}
}

boolean SysChargeAction(SysEventInfo* pEvtInfo)
{
	uint8 ret;
	ret = FALSE;
	CoilsSts KeyCoilSel;

	if(!PosDetFlag)									//Check object position first
	{
		KeyCoilSel = HAL_GetKeyCoilDet(KeyCoilIndex);
		if(CoilSelFinishedOne == KeyCoilSel)
		{
			if(KeyCoilIndex==CoilOne)			// Coil One detect finished
			{
				StopSysTimer2();
				StartSysTimer4(5);
				posdetcnt++;
			}
			else if(KeyCoilIndex==CoilTwo)
			{
				PosDetFlag = TRUE;
				if(TRUE==HAL_GetKeyCoilObjSts())
				{
					bChargeFlag = 1;
				    KeyChargeStateInit();
				    KeyChargeSelectionEntry();

				    WLC_01_Params.WLCFailSts = FailTypeDevDetected;				// Object detected on Key coils
				    StartSysTimer5(3000);
				}
				else
				{
					HAL_UartSendCommand(PChargeEnable);
					bChargeFlag = 2;
				}
				StartSysTimer3(3000);
			}
		}
		if(IsSysTimer4Expired())
		{
			StartSysTimer2(T_PING + TIME_MARGIN);
			KeyCoilIndex = CoilTwo;
			HAL_KeyCoilDetStart(KeyCoilIndex);
			StopSysTimer4();
		}
	}
	else
	{

		if((bChargeFlag==0) && (PosDetFlag==TRUE))
		{
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}

		if(IsSysTimer3Expired())
		{
			//StartSysTimer3(1000);
			RestartSysTimer3();

			PChargeSts = HAL_UartRecvSts();
			KChargeSts = GetKeyChargeSts();

			if(bChargeFlag==1)
			{
				switch(KChargeSts)
				{
				case KChargeNoCharge:
					bChargeFlag = 0;
					WLC_01_Params.WLCChrgSts = 0;				// Charge stopped
					pEvtInfo->SyseventId= EvtSysTransNext;
					pEvtInfo->Sysparam1 = SysStateStandby;
					//pEvtInfo->Sysparam1 = SysStateOff;
					//NFC_Task_LPCD_Cail();
					if(bDeviceDetFlag)
					{
						WLC_01_Params.WLCFailSts = FailTypeNoFailure;				// No failure
					}
					gTestResp_Data[2] = 0x1;
					ret = TRUE;
					break;
				case KChargeOnCharging:
					WLC_01_Params.WLCChrgRate = 0;				// Charge rate power requested
					WLC_01_Params.WLCChrgSts = 1;				// Charge ongoing
					if(!bDeviceDetFlag)
					{
						WLC_01_Params.WLCFailSts = FailTypeDevDetected;				// Object detected on Key coils
						//StartSysTimer5(3000);
					}
					else
					{
						WLC_01_Params.WLCFailSts = FailTypeNoFailure;				// No failure
					}
					gTestResp_Data[2] = 0x0;
					break;
				case KChargePowerTransferFOD:
					//pEvtInfo->SyseventId= EvtSysTransNext;
					//pEvtInfo->Sysparam1 = SysStateFault;
					//ret = TRUE;
					break;
				case KChargeRxChargeComplete:
					WLC_01_Params.WLCChrgSts = 2;				// Charge Completed
					break;
				default:
					WLC_01_Params.WLCChrgSts = 0;				// Charge stopped
					break;
				}
			}
			else if(bChargeFlag==2)
			{
				switch(PChargeSts)
				{
				case PChargeNoCharge:
					//bChargeFlag = 0;
					WLC_01_Params.WLCChrgSts = 0;				// Charge stopped
					HAL_UartSendCommand(PChargeDisable);

					if(bDeviceDetFlag)
					{
						WLC_01_Params.WLCFailSts = FailTypeNoFailure;				// No failure
					}
					gTestResp_Data[2] = 0x1;
					//NFC_Task_LPCD_Cail();
					//if(WLCDevlpCommand.TestModeForEMC!=TestMode_PhoneCharge)
					{
						pEvtInfo->SyseventId= EvtSysTransNext;
						pEvtInfo->Sysparam1 = SysStateStandby;
						ret = TRUE;
					}
					break;
				case PChargeOnCharging:
					WLC_01_Params.WLCChrgRate = 0;				// Charge rate power requested
					WLC_01_Params.WLCChrgSts = 1;				// Charge ongoing
					if(!bDeviceDetFlag)
					{
						//WLC_01_Params.WLCFailSts = FailTypeNoFailure;				// No failure
						WLC_01_Params.WLCFailSts = FailTypeDevDetected;				// Object detected on Key coils
						if(bPchargeFirstDet)
						{
							StartSysTimer5(3000);
							bPchargeFirstDet = FALSE;
						}
					}
					else
					{
						WLC_01_Params.WLCFailSts = FailTypeNoFailure;				// No failure
					}
					gTestResp_Data[2] = 0x0;
					break;

				case PChargeOVP:
					//if(!bDeviceDetFlag)
					{
						WLC_01_Params.WLCFailSts = FailTypeOverVol;					// Over Voltage
					}
					//HAL_UartSendCommand(0);
					//pEvtInfo->SyseventId= EvtSysTransNext;
					//pEvtInfo->Sysparam1 = SysStateFault;
					//pEvtInfo->SyseventId = EvtSysUnsafe;
					//pEvtInfo->Sysparam1 = SysUnsafePOV;
					//ret = TRUE;
					break;
				case PChargeUVP:
					//if(!bDeviceDetFlag)
					{
						WLC_01_Params.WLCFailSts = FailTypeUnderVol;				// Under Voltage
					}
					//HAL_UartSendCommand(0);
					//pEvtInfo->SyseventId= EvtSysTransNext;
					//pEvtInfo->Sysparam1 = SysStateFault;
					//pEvtInfo->SyseventId = EvtSysUnsafe;
					//pEvtInfo->Sysparam1 = SysUnsafePUV;
					//ret = TRUE;
					break;
				case PChargeOCP:
					//HAL_UartSendCommand(0);
					//pEvtInfo->SyseventId= EvtSysTransNext;
					//pEvtInfo->Sysparam1 = SysStateFault;
					//pEvtInfo->SyseventId = EvtSysUnsafe;
					//pEvtInfo->Sysparam1 = SysUnsafePOC;
					//ret = TRUE;
					break;
				case PChargeOTP:
					//if(!bDeviceDetFlag)
					{
						WLC_01_Params.WLCFailSts = FailTypeOverTemp;				// Over temperature
					}
					//HAL_UartSendCommand(0);
					//pEvtInfo->SyseventId= EvtSysTransNext;
					//pEvtInfo->Sysparam1 = SysStateFault;
					//pEvtInfo->SyseventId = EvtSysUnsafe;
					//pEvtInfo->Sysparam1 = SysUnsafePOT;
					//ret = TRUE;
					break;
				case PChargeInternalErr:
					HAL_UartSendCommand(PChargeDisable);
					//if(!bDeviceDetFlag)
					{
						WLC_01_Params.WLCFailSts = FailTypeInternalErr;				// Internal Error
					}
					pEvtInfo->SyseventId= EvtSysTransNext;
					pEvtInfo->Sysparam1 = SysStateStandby;
					ret = TRUE;
					break;
				case PChargePreFOD:
				case PChargePowerTransferFOD:
					//if(!bDeviceDetFlag)
					{
						WLC_01_Params.WLCFailSts = FailTypeFodExist;				// FOD existed
					}
					//HAL_UartSendCommand(0);
					//pEvtInfo->SyseventId= EvtSysTransNext;
					//pEvtInfo->Sysparam1 = SysStateFault;
					//ret = TRUE;
					break;
				case PChargeRxChargeComplete:
					WLC_01_Params.WLCChrgSts = 2;				// Charge Completed
					//pEvtInfo->SyseventId= EvtSysTransNext;
					//pEvtInfo->Sysparam1 = SysStatePause;
					break;
				default:
					WLC_01_Params.WLCChrgSts = 0;				// Charge stopped
					break;

				}
			}
		}

	}

	//if((WLCDevlpCommand.TestModeForEMC==TestMode_AllClose) ||
	//		(WLCDevlpCommand.TestModeForEMC==TestMode_Sleep) ||
	//		(WLCDevlpCommand.TestModeForEMC==TestMode_PingNFC) ||
	//		(WLCDevlpCommand.TestModeForEMC==TestMode_NFCP2P))
	//{
	//	pEvtInfo->SyseventId= EvtSysTransNext;
	//	pEvtInfo->Sysparam1 = SysStateOff;
	//	ret = TRUE;
	//}
#if 1

	if((CGW_02_Params.ImobEnaReq==ImobEnaAID1) || (CGW_02_Params.ImobEnaReq==ImobEnaAID2) || CdcBtWifiCmd.CdcBtReq || CdcBtWifiCmd.CdcWifiReq)
	{
		bChargeFlag = 0;
		pEvtInfo->SyseventId= EvtSysTransNext;
		pEvtInfo->Sysparam1 = SysStateNfc;
		ret = TRUE;
	}


	if((FALSE==ChargeMuteflag) && (HAL_GetMuteSts()==1))
	{
		ChargeMuteflag = TRUE;
		StopSysTimer3();					// Stop check charge status
		if(bChargeFlag==1)
		{
			KeyChargeStateInit();
			KeyChargeSelectionEntry();
			HAL_DisablePower();			// Disable key charge
			bChargeFlag = 4;			// 4 = Key charge mute state
		}
		else if(bChargeFlag==2)
		{
			HAL_UartSendCommand(PChargeDisable);		// Disable phone charge
			bChargeFlag = 5;			// 5 = Phone charge mute state
		}
			//pEvtInfo->SyseventId= EvtSysTransNext;
			//pEvtInfo->Sysparam1 = SysStateStandby;
			//ret = TRUE;
		WLC_01_Params.WLCChrgSts = 0;				// Charge stopped

	}
	else if((TRUE==ChargeMuteflag) && (HAL_GetMuteSts()==0))
	{
		if(bChargeFlag==4)
		{
	//		    KeyChargeStateInit();
	//		    KeyChargeSelectionEntry();
			bChargeFlag = 1;			// 1 Key charge unmute state
		}
		else if(bChargeFlag==5)
		{
			HAL_UartSendCommand(PChargeEnable);		// Enable phone charge
			bChargeFlag = 2;			// 5 Phone charge mute state
		}
		ChargeMuteflag = FALSE;
		StartSysTimer3(500);				// start check charge status
	}


	if(((CGW_02_Params.VehState==Parked)&&(CGW_02_Params.Comf_Ena==ComfNotEna))||
			(CGW_02_Params.VehState==Software_Update))		// Parked or software updated or go to sleep
	{
		bChargeFlag = 0;
		pEvtInfo->SyseventId= EvtSysTransNext;
		pEvtInfo->Sysparam1 = SysStateOff;
		ret = TRUE;
	}

	if(CDC_WLC_Params.WLCChrgFctEnaReq==0)				// Disable Charge function
	{
		WLC_01_Params.WLCCtrlSts = 1;
		bChargeFlag = 0;
		pEvtInfo->SyseventId= EvtSysTransNext;
		pEvtInfo->Sysparam1 = SysStateStandby;
		ret = TRUE;
		bDeviceDetFlag = TRUE;				// if HMI disable charge function, set fail status not equal to 8

	}



	if(HAL_GetMuteSts()==0)
	{
		WLC_01_Params.WLCMuteViaHW = 1;		// Not muted
	}
	else
	{
		WLC_01_Params.WLCMuteViaHW = 0;		// Muted
	}


	if(IsSysTimer5Expired())				// First Device Detected, wait 3s to change fail status 8 to 0
	{
		StopSysTimer5();
		bDeviceDetFlag = TRUE;//FALSE;
		WLC_01_Params.WLCFailSts = FailTypeNoFailure;				// No failure
	}
#endif

	return ret;

}


