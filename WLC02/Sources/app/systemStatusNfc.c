/*
 * systemStatusNfc.c
 *
 *  Created on: 2020年1月10日
 *      Author: jiangxl
 */


#include "Cpu.h"
#include "hal.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"
#include "CDDNIO.h"

#include "NFC_Inerface.h"
//#include "ndef_bt_wifi.h"
//#include "nfc_task.h"

extern uint8 		DataFromCGW[200];
uint8 				NotificationData[8];

uint8 		OobDataLength;
uint8		CdcBtReqEnable, CdcBtReqDisable;
uint8		CdcWifiReqEnable, CdcWifiReqDisable;
NxpNci_P2P_Results		NfcOpSts = NxpNci_P2P_Results_None;

CGW_02_0x2C3 		CGW_02_Params;
WLC_02_0X340 		WLC_02_Params;
NFC_IMMO_Results	NfcImoSts;
NFC_Task_IMMO_Type	NfcImoType;
CDC_BTWIFI_Command	CdcBtWifiCmd;
WLC_DEVLP_02_0x4BC		WLCDevlpCommand;

NxpNci_RW_NDEF_Results retVal_nfctask_immo = NxpNci_RW_NDEF_Results_None;




//uint16_t gLPCD_CailValue = 0x0000;
boolean		bImobAuthKeyDataSendFlag = FALSE;
boolean		bBtWithOobNotifSendFlag = FALSE;
boolean		bWifiWithoutOobNotifSendFlag = FALSE;
uint8		NotifRetryCnt = 0;

CGW_TCU_01_0x3B2 	CGW_TCU_01_Params ;
NFC_Task_EMC_Results EMC_NFC_Result = NFC_Task_EMC_Results_None;


void SysNfcEntry(SysEventId eventId, uint8_t eventParam)
{
	uint8_t i = 0;


	struct bt_info bt_info;
	struct wifi_info wifi_info;

	bImobAuthKeyDataSendFlag = FALSE;
	bBtWithOobNotifSendFlag = FALSE;
	bWifiWithoutOobNotifSendFlag = FALSE;
	NotifRetryCnt = 0;

#ifdef Nio_OOBData


	bt_info.bt_oob[5] = 0xE8;
	bt_info.bt_oob[4] = 0x07;
	bt_info.bt_oob[3] = 0xBF;
	bt_info.bt_oob[2] = 0x19;
	bt_info.bt_oob[1] = 0x62;
	bt_info.bt_oob[0] = 0x38;


#else

	bt_info.mac[5] = 0xE8;
	bt_info.mac[4] = 0x07;
	bt_info.mac[3] = 0xBF;
	bt_info.mac[2] = 0x19;
	bt_info.mac[1] = 0x62;
	bt_info.mac[0] = 0x38;
	bt_info.ClassOfDev[0] = 0x08;
	bt_info.ClassOfDev[1] = 0x04;
	bt_info.ClassOfDev[2] = 0x36;
	for(i = 0;i < 16;i ++)
	{
		bt_info.HashValue[i] = i+1;
	}
	for(i = 0;i < 16;i ++)
	{
		bt_info.RandomizerValue[i] = 0xff - i;
	}
	bt_info.UserfriendlyName = "NextEV_Bluetooth";
#endif

#ifdef Nio_OOBData
#if 0
	memset(wifi_info.wifi_oob,0x00,sizeof(wifi_info.wifi_oob));
	wifi_info.wifi_oob[0] = 0x10;
	wifi_info.wifi_oob[1] = 0x0e;


	//index
	wifi_info.wifi_oob[4] = 0x10;
	wifi_info.wifi_oob[5] = 0x26;
	wifi_info.wifi_oob[6] = 0x00;
	wifi_info.wifi_oob[7] = 0x01;
	wifi_info.wifi_oob[8] = 0x01;

	//ssid
	wifi_info.wifi_oob[9] = 0x10;
	wifi_info.wifi_oob[10] = 0x45;
	wifi_info.wifi_oob[11] = 0x00;
	wifi_info.wifi_oob[12] = strlen("Teme Sales Dpt.");
	memcpy(&wifi_info.wifi_oob[13],"Teme Sales Dpt.",strlen("Teme Sales Dpt.") );

	//key
	wifi_info.wifi_oob[13+strlen("Teme Sales Dpt.")] = 0x10;
	wifi_info.wifi_oob[14+strlen("Teme Sales Dpt.")] = 0x27;
	wifi_info.wifi_oob[15+strlen("Teme Sales Dpt.")] = 0x00;
	wifi_info.wifi_oob[16+strlen("Teme Sales Dpt.")] = strlen("12345678");
	memcpy(&wifi_info.wifi_oob[17+strlen("Teme Sales Dpt.")],"12345678",strlen("12345678") );

	wifi_info.wifi_oob[2] = 0x00;
	wifi_info.wifi_oob[3] = 17+strlen("Teme Sales Dpt.")+strlen("12345678")-4;
#endif
#else
	wifi_info.network_index = 0x01;
	wifi_info.ssid = "Teme Sales Dpt.";
	wifi_info.password = "12345678";
	wifi_info.auth = WIFI_AUTH_WPA2_PERSONAL;
	wifi_info.crypt = WIFI_CRYPT_AES;
	memset(wifi_info.mac,0x00,sizeof(wifi_info.mac));
#endif

#if 0
	CGW_TCU_01_Params.Yr = 0x14;
	CGW_TCU_01_Params.Mth = 0x03;
	CGW_TCU_01_Params.Day = 0x13;
	CGW_TCU_01_Params.Hr = 0x0d;
	CGW_TCU_01_Params.Min = 0x24;
	CGW_TCU_01_Params.Sec = 0x14;
#endif
/*
	CGW_TCU_01_Params.Yr = 0x14;
	CGW_TCU_01_Params.Mth = 0x03;
	CGW_TCU_01_Params.Day = 0x14;
	CGW_TCU_01_Params.Hr = 0x0f;
	CGW_TCU_01_Params.Min = 0x00;
	CGW_TCU_01_Params.Sec =0x00;*/
	if(CGW_02_Params.ImobEnaReq==ImobEnaAID1)
	{
		WLC_02_Params.WLCImobSts = Enable;
 		retVal_nfctask_immo = NFC_Task_IMM0(NFC_Task_IMMO_Type_EnableAID1,(uint8_t *)&CGW_TCU_01_Params,6);
	}
	else if(CGW_02_Params.ImobEnaReq==ImobEnaAID2)
	{
		WLC_02_Params.WLCImobSts = Enable;
		retVal_nfctask_immo = NFC_Task_IMM0(NFC_Task_IMMO_Type_EnableAID2,(uint8_t *)&CGW_TCU_01_Params,6);
	}
	else if(CdcBtWifiCmd.CdcBtReq)
	{
#ifdef Nio_OOBData
	NfcOpSts = NFC_Task_P2P(NFC_P2PMode_Pairing_BT_Enable,&DataFromCGW[3],GetCanTpDataLength()-3);
	//NfcOpSts = NFC_Task_P2P(NFC_P2PMode_Pairing_BT_Enable,&bt_info,6);
#else
	NfcOpSts = NFC_Task_P2P(NFC_P2PMode_Pairing_BT_Enable,&bt_info,0);
#endif

	}
	//else if(!CdcBtWifiCmd.CdcBtReq)
	//{
		//NfcOpSts = NFC_Task_P2P(NFC_P2PMode_Pairing_BT_Disable,&gOOBData_From_MobileDevice[0],OobDataLength);
	//}

	if(CdcBtWifiCmd.CdcWifiReq)
	{
#ifdef Nio_OOBData
	NfcOpSts = NFC_Task_P2P(NFC_P2PMode_Pairing_WIFI_Enable,&DataFromCGW[3],GetCanTpDataLength()-3);
#else
	NfcOpSts = NFC_Task_P2P(NFC_P2PMode_Pairing_BT_Enable,&bt_info,0);
#endif
	}
	//else if(!CdcBtWifiCmd.CdcWifiReq)
	//{
		//NfcOpSts = NFC_Task_P2P(NFC_P2PMode_Pairing_WIFI_Disable,&gOOBData_From_MobileDevice[0],OobDataLength);
	//}

	if(WLCDevlpCommand.TestModeForEMC==TestMode_PingNFC)
	{
		EMC_NFC_Result =  NFC_Task_EMCTest(NFC_Task_EMC_Mode_EnablePing);
	}
	else if(WLCDevlpCommand.TestModeForEMC==TestMode_NFCP2P)
	{
		EMC_NFC_Result =  NFC_Task_EMCTest(NFC_Task_EMC_Mode_EnableCommunication);
	}

}


void SysNfcExit()
{
	StopAllSysTimers();
	CdcBtWifiCmd.CdcNotifBt = 0x0;
	NotifRetryCnt = 0;				// clear retry count

	hal_NFCC_Reset();
	bNfcNoblocking= TRUE;

	retVal_nfctask_immo = NxpNci_RW_NDEF_Results_None;
	NfcOpSts = NxpNci_P2P_Results_None;
}


boolean SysNfcAction(SysEventInfo* pEvtInfo)
{
	boolean ret;
	uint16 retLen = 0;
	uint8	nfcNotifSts;

	ret = FALSE;



	//if((CGW_02_Params.ImobEnaReq==ImobEnaAID1) || (CGW_02_Params.ImobEnaReq==ImobEnaAID2))
	{

		switch(retVal_nfctask_immo)
		{
		//case NxpNci_READNDEF_Results_Finished:
		case NFC_Task_IMMO_APDU_Results_ReadCarKey_OK:
			/* NdefBuffer_IMMO数据作为返回值 */
			if(!bImobAuthKeyDataSendFlag)
			{
			   /* 获取数据长度 */
				//蔚来
				retLen = Get_ImmoDataLen();
				//自测
				//retLen = RW_NDEF_T4T_Get_KeyLen();

				//蔚来
				CDDEX_SendCanFrameTo(IMOB_WLC_CGW, &gImmo_Data[0],retLen);
				//自测
				//CDDEX_SendCanFrameTo(IMOB_WLC_CGW, &NdefBuffer_IMMO[0],retLen);
				bImobAuthKeyDataSendFlag = TRUE;
			}
			if(CGW_02_Params.ImobEnaReq==ImobDisable)
			{
				WLC_02_Params.WLCImobSts = Disable;
				pEvtInfo->SyseventId= EvtSysTransNext;
				pEvtInfo->Sysparam1 = SysStateStandby;
				ret = TRUE;
			}
			break;

		case NfcTask_IMMO_Results_NotFoundEndpoint:
			/* 获取数据长度 */
			//retLen = RW_NDEF_T4T_Get_KeyLen();
			if(CGW_02_Params.ImobEnaReq==ImobDisable)
			{
				WLC_02_Params.WLCImobSts = Disable;
				pEvtInfo->SyseventId= EvtSysTransNext;
				pEvtInfo->Sysparam1 = SysStateStandby;
				ret = TRUE;
			}

			break;
		case NxpNci_READNDEF_Results_DisableOK:
			if(CGW_02_Params.ImobEnaReq==ImobDisable)
			{
				WLC_02_Params.WLCImobSts = Disable;
				pEvtInfo->SyseventId= EvtSysTransNext;
				pEvtInfo->Sysparam1 = SysStateStandby;
				ret = TRUE;
			}
			break;

		case NfcTask_IMMO_Results_InternalError:
			if(CGW_02_Params.ImobEnaReq==ImobDisable)
			{		
				WLC_02_Params.WLCImobSts = Disable;
				pEvtInfo->SyseventId= EvtSysTransNext;
				pEvtInfo->Sysparam1 = SysStateStandby;
				ret = TRUE;
			}
			break;
		default:
			break;
		}

	}



	switch(NfcOpSts)
	{
	case NxpNci_P2P_Results_WithOOB_OK:
		retLen = NFC_Get_OOBDataLen();
		nfcNotifSts = NotificationBTHandler(&gOOBData_From_MobileDevice[0], retLen);
		//if((nfcNotifSts==1)&&(!CdcBtWifiCmd.CdcBtReq))		// received notification acknowledge
		if(nfcNotifSts==1)
		{
			CdcBtWifiCmd.CdcBtReq = 0;
			CdcBtWifiCmd.CdcNotifBt = 0x0;				// clear notification BT flag
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}
		else if(nfcNotifSts==2)							// after retry 3 times, close NFC and go into standby
		{
			CdcBtWifiCmd.CdcBtReq = 0;					// manual close BT require
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}
/*
		if(!bBtWithOobNotifSendFlag)
		{
			//Notification data proceeded in NFC task for RAM use reduce
			//NotificationData[0] = 0x2;			// Notification require ACK
			//NotificationData[1] = 0x01;			// BT
			//NotificationData[2] = 0x04;			// With OOB
			//for(i=0;i<retLen;i++)
			//{
			//	NotificationData[3+i] = gOOBData_From_MobileDevice[i];
			//}

			retLen = NFC_Get_OOBDataLen();

			CDDEX_SendCanFrameTo(WLC_CDC_NFC, &gOOBData_From_MobileDevice[0],retLen);
			StartSysTimer1(300);
			bBtWithOobNotifSendFlag = TRUE;
		}
		else
		{
			if(CdcBtWifiCmd.CdcNotifBt)			// received Notification Ack from CDC
			{
				if(!CdcBtWifiCmd.CdcBtReq)		// wait CDC disable BT command
				{
					CdcBtWifiCmd.CdcNotifBt = 0x0;				// clear notification BT flag
					pEvtInfo->SyseventId= EvtSysTransNext;
					pEvtInfo->Sysparam1 = SysStateStandby;
					ret = TRUE;
				}
			}
			else if(IsSysTimer1Expired())			// if have not received Notification ACK from CDC, Retry
			{
				if(NotifRetryCnt<2)					// < 3 times retry
				{
					NotifRetryCnt++;
					bBtWithOobNotifSendFlag = FALSE;
				}
				else								// >= 3 times,
				{
					//StopSysTimer1();
					if(!CdcBtWifiCmd.CdcBtReq)				// ????? 是否需要判断还需要实测
					{
						NotifRetryCnt = 0;				// clear retry count
						pEvtInfo->SyseventId= EvtSysTransNext;
						pEvtInfo->Sysparam1 = SysStateStandby;
						ret = TRUE;
					}
				}
			}
		}
*/
		//WlcCgwNotificationHandler(BTWithOOB);
		break;
	case NFC_P2P_Results_BT_WithoutOOB_OK:

		NotificationData[0] = 0x2;			// Notification require ACK
		NotificationData[1] = 0x01;			// BT
		NotificationData[2] = 0x05;			// With OOB
		nfcNotifSts = NotificationBTHandler(&NotificationData[0], 3);
		//if((nfcNotifSts==1)&&(!CdcBtWifiCmd.CdcBtReq))		// received notification acknowledge
		if(nfcNotifSts==1)
		{
			CdcBtWifiCmd.CdcBtReq = 0;					// manual close BT require
			CdcBtWifiCmd.CdcNotifBt = 0x0;				// clear notification BT flag
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}
		else if(nfcNotifSts==2)							// after retry 3 times, close NFC and go into standby
		{
			CdcBtWifiCmd.CdcBtReq = 0;					// manual close BT require
			NotifRetryCnt = 0;
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}

		break;
	case NFC_P2P_Results_InternalError:
		CdcBtWifiCmd.CdcBtReq = 0;					// manual close BT require
		CdcBtWifiCmd.CdcWifiReq = 0;
		pEvtInfo->SyseventId= EvtSysTransNext;
		pEvtInfo->Sysparam1 = SysStateStandby;
		ret = TRUE;

		break;
		
	case NFC_P2P_Results_BT_Pairing_Failed:
		NotificationData[0] = 0x2;			// Notification require ACK
		NotificationData[1] = 0x01;			// BT
		NotificationData[2] = 0x03;			// Failure
		NotificationData[3] = 0x03;			// Connection Timeout
		NotificationBTHandler(&NotificationData[0], 4);
		//if(!CdcBtWifiCmd.CdcBtReq)		// received notification acknowledge
		{
			CdcBtWifiCmd.CdcBtReq = 0;
			CdcBtWifiCmd.CdcNotifBt = 0x0;				// clear notification BT flag
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}
		break;
	case NFC_P2P_Results_BT_Connection_Failed:
		NotificationData[0] = 0x2;			// Notification require ACK
		NotificationData[1] = 0x01;			// BT
		NotificationData[2] = 0x03;			// Failure
		NotificationData[3] = 0x03;			// Connection Timeout
		nfcNotifSts = NotificationBTHandler(&NotificationData[0], 4);
		if(nfcNotifSts!=0)
		{
			CdcBtWifiCmd.CdcNotifBt = 0x0;				// clear notification BT flag
			CdcBtWifiCmd.CdcBtReq = 0;					// manual close BT require
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}

		break;
	case NFC_P2P_Results_BT_Detection_Failed:
		NotificationData[0] = 0x2;			// Notification require ACK
		NotificationData[1] = 0x01;			// BT
		NotificationData[2] = 0x03;			// Failure
		NotificationData[3] = 0x02;			// Detection Timeout
		nfcNotifSts = NotificationBTHandler(&NotificationData[0], 4);
		if(nfcNotifSts!=0)
		{
			CdcBtWifiCmd.CdcNotifBt = 0x0;				// clear notification BT flag
			CdcBtWifiCmd.CdcBtReq = 0;					// manual close BT require
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}
		break;
	case NFC_P2P_Results_WIFI_WithoutOOB_OK:
		NotificationData[0] = 0x2;			// Notification require ACK
		NotificationData[1] = 0x02;			// WIFI
		NotificationData[2] = 0x06;			// Without OOB
		nfcNotifSts = NotificationWIFIHandler(&NotificationData[0], 3);
		//if((nfcNotifSts==1)&&(!CdcBtWifiCmd.CdcWifiReq))		// received notification acknowledge
		if(nfcNotifSts==1)
		{
			CdcBtWifiCmd.CdcWifiReq = 0;
			CdcBtWifiCmd.CdcNotifWifi = 0x0;				// clear notification WiFi flag
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}
		else if(nfcNotifSts==2)							// after retry 3 times, close NFC and go into standby
		{
			CdcBtWifiCmd.CdcWifiReq = 0;					// manual close WIFI require
			NotifRetryCnt = 0;
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}

		break;
	case NFC_P2P_Results_WIFI_Pairing_Failed:
		NotificationData[0] = 0x2;			// Notification require ACK
		NotificationData[1] = 0x02;			// WIFI
		NotificationData[2] = 0x03;			// Failure
		NotificationData[3] = 0x03;			// Connection Timeout
		NotificationWIFIHandler(&NotificationData[0], 4);

		//if(!CdcBtWifiCmd.CdcWifiReq)
		{
			CdcBtWifiCmd.CdcWifiReq = 0;
			CdcBtWifiCmd.CdcNotifWifi = 0x0;				// clear notification WiFi flag
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}
		break;
	case NFC_P2P_Results_WIFI_Connection_Failed:
		NotificationData[0] = 0x2;			// Notification require ACK
		NotificationData[1] = 0x02;			// WIFI
		NotificationData[2] = 0x03;			// Failure
		NotificationData[3] = 0x03;			// Connection Timeout
		nfcNotifSts = NotificationWIFIHandler(&NotificationData[0], 4);
		if(nfcNotifSts!=0)
		{
			CdcBtWifiCmd.CdcNotifWifi = 0x0;				// clear notification WIFI flag
			CdcBtWifiCmd.CdcWifiReq = 0;					// manual close WIFI require
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}

		break;
	case NFC_P2P_Results_WIFI_Detection_Failed:
		NotificationData[0] = 0x2;			// Notification require ACK
		NotificationData[1] = 0x01;			// BT
		NotificationData[2] = 0x03;			// Failure
		NotificationData[3] = 0x02;			// Detection Timeout
		nfcNotifSts = NotificationBTHandler(&NotificationData[0], 4);
		if(nfcNotifSts!=0)
		{
			CdcBtWifiCmd.CdcNotifBt = 0x0;				// clear notification BT flag
			CdcBtWifiCmd.CdcWifiReq = 0;					// manual close BT require
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;
		}
		break;

	default:
		break;

	}
#if 0
	switch(EMC_NFC_Result)
	{
		case NFC_Task_EMC_Results_Succeed:
			//WLCDevlpCommand.TestModeForEMC = TestMode_Invalid;
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			gTestResp_Data[2] = 0x0;
			ret = TRUE;

			break;
		case NFC_Task_EMC_Results_Failed:

			//WLCDevlpCommand.TestModeForEMC = TestMode_Invalid;
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			gTestResp_Data[2] = 0x1;
			ret = TRUE;

			break;
		case NFC_Task_EMC_Results_None:
			//WLCDevlpCommand.TestModeForEMC = TestMode_Invalid;
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;

			break;
		default:
			//WLCDevlpCommand.TestModeForEMC = TestMode_Invalid;
			pEvtInfo->SyseventId= EvtSysTransNext;
			pEvtInfo->Sysparam1 = SysStateStandby;
			ret = TRUE;

			break;
	}

#endif

	if(((CGW_02_Params.VehState==Parked)&&(CGW_02_Params.Comf_Ena==ComfNotEna))||
				(CGW_02_Params.VehState==Software_Update))		// Parked or software updated or go to sleep
	{
		pEvtInfo->SyseventId= EvtSysTransNext;
		pEvtInfo->Sysparam1 = SysStateOff;
		ret = TRUE;
	}
	//if((WLCDevlpCommand.TestModeForEMC==TestMode_AllClose) ||
	//		(WLCDevlpCommand.TestModeForEMC==TestMode_Sleep) ||
	//		(WLCDevlpCommand.TestModeForEMC==TestMode_Ping) ||
	//		(WLCDevlpCommand.TestModeForEMC==TestMode_PhoneCharge) ||
	//		(WLCDevlpCommand.TestModeForEMC==TestMode_KeyCharge))
	//{
	//	pEvtInfo->SyseventId= EvtSysTransNext;
	//	pEvtInfo->Sysparam1 = SysStateStandby;
	//	ret = TRUE;
	//}


	return ret;

}

uint8 NotificationBTHandler(uint8* data, uint16 len)
{
	uint8	retVal;
	retVal = 0;

	if(!bBtWithOobNotifSendFlag)
	{
		CDDEX_SendCanFrameTo(WLC_CDC_NFC, data,len);
		StartSysTimer1(300);
		bBtWithOobNotifSendFlag = TRUE;
	}
	else
	{
		if(CdcBtWifiCmd.CdcNotifBt)			// received Notification Ack from CDC
		{
			retVal = 1;						// 1 -> stand for received notification acknowledge
			//if(!CdcBtWifiCmd.CdcBtReq)		// wait CDC disable BT command
			//{
			//	CdcBtWifiCmd.CdcNotifBt = 0x0;				// clear notification BT flag
				//pEvtInfo->SyseventId= EvtSysTransNext;
				//pEvtInfo->Sysparam1 = SysStateStandby;
			//	retVal = TRUE;
			//}
		}
		else if(IsSysTimer1Expired())			// if have not received Notification ACK from CDC, Retry
		{
			if(NotifRetryCnt<2)					// < 3 times retry
			{
				NotifRetryCnt++;
				bBtWithOobNotifSendFlag = FALSE;
			}
			else								// >= 3 times,
			{
				retVal = 2;							// 2 -> stand for no notification acknowledge after 3 times retry
				//StopSysTimer1();
				//if(!CdcBtWifiCmd.CdcBtReq)				// ????? 是否需要判断还需要实测
				//{
				//	NotifRetryCnt = 0;				// clear retry count
					//pEvtInfo->SyseventId= EvtSysTransNext;
					//pEvtInfo->Sysparam1 = SysStateStandby;
				//	retVal = TRUE;
				//}
			}
		}
	}
	return retVal;
}

uint8 NotificationWIFIHandler(uint8* data, uint16 len)
{
	uint8	retVal;
	retVal = 0;

	if(!bWifiWithoutOobNotifSendFlag)
	{
		CDDEX_SendCanFrameTo(WLC_CDC_NFC, data,len);
		StartSysTimer1(300);
		bWifiWithoutOobNotifSendFlag = TRUE;
	}
	else
	{
		if(CdcBtWifiCmd.CdcNotifWifi)			// received Notification Ack from CDC
		{
			retVal = 1;						// 1 -> stand for received notification acknowledge
			//if(!CdcBtWifiCmd.CdcBtReq)		// wait CDC disable BT command
			//{
			//	CdcBtWifiCmd.CdcNotifBt = 0x0;				// clear notification BT flag
				//pEvtInfo->SyseventId= EvtSysTransNext;
				//pEvtInfo->Sysparam1 = SysStateStandby;
			//	retVal = TRUE;
			//}
		}
		else if(IsSysTimer1Expired())			// if have not received Notification ACK from CDC, Retry
		{
			if(NotifRetryCnt<2)					// < 3 times retry
			{
				NotifRetryCnt++;
				bWifiWithoutOobNotifSendFlag = FALSE;
			}
			else								// >= 3 times,
			{
				retVal = 2;							// 2 -> stand for no notification acknowledge after 3 times retry
				//StopSysTimer1();
				//if(!CdcBtWifiCmd.CdcBtReq)				// ????? 是否需要判断还需要实测
				//{
				//	NotifRetryCnt = 0;				// clear retry count
					//pEvtInfo->SyseventId= EvtSysTransNext;
					//pEvtInfo->Sysparam1 = SysStateStandby;
				//	retVal = TRUE;
				//}
			}
		}
	}
	return retVal;
}




