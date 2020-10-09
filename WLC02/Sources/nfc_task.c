/*
*         Copyright (c), NXP Semiconductors Caen / France
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "nfc_task.h"
#include <ndef_helper.h>
#include "uart.h"
#include "raw_p2p.h"
#include "ndef_bt_wifi.h"
#include <RW_NDEF.h>

//#define DEBUG_DELAY_TICK	1
#define NFC_LPCD_CALIB_CYCLES (8)
#define NFC_LPCD_DELTA (10)

#define NFC_LPCD_DETECT_COUNT (4)//10
#define NFC_LPCD_DETECT_ONLINE_COUNT (2)//7

#define NFC_IMMO_APDU_NOTFOUNDFILE 0

typedef enum
{
	LPCD_Single_Detecet_None = 0,
	LPCD_Single_Detecet_InvalidPara,
	LPCD_Single_Detecet_SampleFail,
	LPCD_Single_Detecet_OverRange,
	LPCD_Single_Detecet_NotOverRange,

}LPCD_Single_Detecet;

/* Discovery loop configuration according to the targeted modes of operation */
#if 0
const unsigned char DiscoveryTechnologies_P2P[7] = {
    MODE_POLL | TECH_PASSIVE_NFCA,
    MODE_POLL | TECH_PASSIVE_NFCF,
    /* Only one POLL ACTIVE mode can be enabled, if both are defined only NFCF applies */
    MODE_POLL | TECH_ACTIVE_NFCA,
    //MODE_POLL | TECH_ACTIVE_NFCF,
    MODE_LISTEN | TECH_PASSIVE_NFCA,
    MODE_LISTEN | TECH_PASSIVE_NFCF,
    MODE_LISTEN | TECH_ACTIVE_NFCA,
    MODE_LISTEN | TECH_ACTIVE_NFCF,
};
#else
const unsigned char  DiscoveryTechnologies_P2P[] = {
                                          MODE_LISTEN | TECH_PASSIVE_NFCA
                                          ,MODE_LISTEN | TECH_PASSIVE_NFCF
                                          //,MODE_LISTEN | TECH_ACTIVE_NFCA
                                          //,MODE_LISTEN | TECH_ACTIVE_NFCF
};
#endif

const unsigned char DiscoveryTechnologies_CardEmu[2] = {
    MODE_LISTEN | TECH_PASSIVE_NFCA,
    MODE_LISTEN | TECH_PASSIVE_NFCB,
};

#ifdef HW_Test
const unsigned char  DiscoveryTechnologies_F[] =
{
		MODE_POLL | TECH_PASSIVE_NFCA
		//,MODE_POLL | TECH_PASSIVE_NFCB
		//MODE_POLL | TECH_PASSIVE_NFCF
		//,MODE_POLL | TECH_PASSIVE_15693
};
#else
const unsigned char  DiscoveryTechnologies_Tag[] =
{
		MODE_POLL | TECH_PASSIVE_NFCA,
		MODE_POLL | TECH_PASSIVE_NFCB,
		MODE_POLL | TECH_PASSIVE_NFCF
		//,MODE_POLL | TECH_PASSIVE_15693
};
#endif


const unsigned char  DiscoveryTechnologies_IMMO[] =
{
		MODE_POLL | TECH_PASSIVE_NFCA
		//MODE_POLL | TECH_PASSIVE_NFCB,
		//MODE_POLL | TECH_PASSIVE_NFCF
};


/* Initialize NDEF without MAC address and with wrong payload size */
char NDEF_RECORD_BT[64] = { 0xDA,   /* MB/ME/CF/1/IL/TNF */
         0x20,   /* TYPE LENGTH */
         0x08,   /* PAYLOAD LENTGH */
         0x01,
         'a','p','p','l','i','c','a','t','i','o','n','/','v','n','d',0x2e,
         'b','l','u','e','t','o','o','t','h',0x2e,
         'e','p',0x2e,
         'o','o','b','0',
         0x08,0x00};/* 与《Bluetooth Secure Simple Pairing Using NFC》 */

uint8_t gImmo_Data[2200] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07};
//uint16_t gLPCD_CailValue = 0x0000;
#ifdef LPCD_TEST
uint8_t ZB_LPCD_TEST[8]={0xF1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
#endif
int Immo_DataIndex = 0;
//CGW_TCU_01_0x3B2 	CGW_TCU_01_Params;
/* Mode configuration according to the targeted modes of operation */
uint32_t nfc_mode = NXPNCI_MODE_CARDEMU;
uint32_t nfc_mode_change = 0;
uint32_t nfc_set_mode(uint32_t mode)
{
	if (mode != NXPNCI_MODE_CARDEMU && mode != NXPNCI_MODE_P2P)
		return 1;

	if (mode != nfc_mode)
		nfc_mode_change = 1;

	nfc_mode = mode;
	return 0;		
}

void NdefPull_Cb(unsigned char *pNdefMessage, unsigned short NdefMessageSize)
{
    unsigned char *pNdefRecord = pNdefMessage;
    NdefRecord_t NdefRecord;
    unsigned char save;

    if (pNdefMessage == NULL)
    {
    	UART_MESSAGE("\n\r--- Issue during NDEF message reception (check provisioned buffer size) \n\r");
        return;
    }

    while (pNdefRecord != NULL)
    {
    	UART_MESSAGE("\n\r--- NDEF record received:\n\r");

        NdefRecord = DetectNdefRecordType(pNdefRecord);

        switch(NdefRecord.recordType)
        {
        case MEDIA_VCARD:
            {
                save = NdefRecord.recordPayload[NdefRecord.recordPayloadSize];
                NdefRecord.recordPayload[NdefRecord.recordPayloadSize] = '\0';
                UART_MESSAGE_1STR("vCard:\n\r%s\n\r", NdefRecord.recordPayload);
                NdefRecord.recordPayload[NdefRecord.recordPayloadSize] = save;
            }
            break;

        case WELL_KNOWN_SIMPLE_TEXT:
            {
                save = NdefRecord.recordPayload[NdefRecord.recordPayloadSize];
                NdefRecord.recordPayload[NdefRecord.recordPayloadSize] = '\0';
                UART_MESSAGE_1STR("   Text record: %s\n\r", &NdefRecord.recordPayload[NdefRecord.recordPayload[0]+1]);
                NdefRecord.recordPayload[NdefRecord.recordPayloadSize] = save;
            }
            break;

        case WELL_KNOWN_SIMPLE_URI:
            {
                save = NdefRecord.recordPayload[NdefRecord.recordPayloadSize];
                NdefRecord.recordPayload[NdefRecord.recordPayloadSize] = '\0';
                UART_MESSAGE_2STR("   URI record: %s%s\n\r", ndef_helper_UriHead(NdefRecord.recordPayload[0]), &NdefRecord.recordPayload[1]);
                NdefRecord.recordPayload[NdefRecord.recordPayloadSize] = save;
            }
            break;

        case MEDIA_HANDOVER_WIFI:
            {
                unsigned char index = 0, i;

                UART_MESSAGE ("\n\r--- Received WIFI credentials:\n\r");
                if ((NdefRecord.recordPayload[index] == 0x10) && (NdefRecord.recordPayload[index+1] == 0x0e)) index+= 4;
                while(index < NdefRecord.recordPayloadSize)
                {
                    if (NdefRecord.recordPayload[index] == 0x10)
                    {
                    	if (NdefRecord.recordPayload[index+1] == 0x45) {UART_MESSAGE ("- SSID = "); for(i=0;i<NdefRecord.recordPayload[index+3];i++) UART_MESSAGE_1("%x ", NdefRecord.recordPayload[index+4+i]); UART_MESSAGE ("\n\r");}
						else if (NdefRecord.recordPayload[index+1] == 0x03) UART_MESSAGE_1STR("- Authenticate Type = %s\n\r", ndef_helper_WifiAuth(NdefRecord.recordPayload[index+5]));
						else if (NdefRecord.recordPayload[index+1] == 0x0f) UART_MESSAGE_1STR("- Encryption Type = %s\n\r", ndef_helper_WifiEnc(NdefRecord.recordPayload[index+5]));
						else if (NdefRecord.recordPayload[index+1] == 0x27) {UART_MESSAGE ("- Network key = "); for(i=0;i<NdefRecord.recordPayload[index+3];i++) UART_MESSAGE("#"); UART_MESSAGE ("\n\r");}
						index += 4 + NdefRecord.recordPayload[index+3];
                    }
                    else continue;
                }
            }
            break;

        case WELL_KNOWN_HANDOVER_SELECT:
        	UART_MESSAGE_2("\n\r   Handover select version %d.%d", NdefRecord.recordPayload[0] >> 4, NdefRecord.recordPayload[0] & 0xF);
            break;

        case WELL_KNOWN_HANDOVER_REQUEST:
        	UART_MESSAGE_2("\n\r   Handover request version %d.%d\n\r", NdefRecord.recordPayload[0] >> 4, NdefRecord.recordPayload[0] & 0xF);
            break;

        case MEDIA_HANDOVER_BT:
        	print_buf("\n\r   BT Handover payload = ", NdefRecord.recordPayload, NdefRecord.recordPayloadSize);
            break;

        case MEDIA_HANDOVER_BLE:
        	print_buf("\n\r   BLE Handover payload = ", NdefRecord.recordPayload, NdefRecord.recordPayloadSize);
            break;

        case MEDIA_HANDOVER_BLE_SECURE:
        	print_buf("\n\r   BLE secure Handover payload = ", NdefRecord.recordPayload, NdefRecord.recordPayloadSize);
            break;

        default:
        	UART_MESSAGE("\n\r   Unsupported NDEF record, cannot parse");
        	return;
            break;
        }
        pNdefRecord = GetNextRecord(pNdefRecord);
    }

    UART_MESSAGE("\n\r");
}

const char NDEF_MESSAGE[] = { 0xD1,   // MB/ME/CF/1/IL/TNF
        0x01,   // TYPE LENGTH
        0x07,   // PAYLOAD LENTGH
        'T',    // TYPE
        0x02,   // Status
        'e', 'n', // Language
        'T', 'e', 's', 't' };


void NdefPush_Cb(unsigned char *pNdefRecord, unsigned short NdefRecordSize) {
	UART_MESSAGE("\nNDEF Record sent\n\r");
}

#if defined CARDEMU_SUPPORT
#ifdef CARDEMU_RAW_EXCHANGE
void PICC_ISO14443_4_scenario (void)
{
    unsigned char OK[] = {0x90, 0x00};
    unsigned char Cmd[256];
    unsigned char CmdSize;

    while (1)
    {
        if(NxpNci_CardModeReceive(Cmd, &CmdSize) == NFC_SUCCESS)
        {
            if ((CmdSize >= 2) && (Cmd[0] == 0x00))
            {
            	switch (Cmd[1])
            	{
            	case 0xA4:
            		UART_MESSAGE("\n\rSelect File received\n\r");
            		break;

            	case 0xB0:
            		UART_MESSAGE("\n\rRead Binary received\n\r");
            		break;

            	case 0xD0:
            		UART_MESSAGE("\n\rWrite Binary received\n\r");
            		break;

            	default:
            		break;
            	}

                NxpNci_CardModeSend(OK, sizeof(OK));
            }
        }
        else
        {
        	UART_MESSAGE("\n\rEnd of transaction\n\r");
            return;
        }
    }
}
#endif // if defined CARDEMU_SUPPORT
#endif

/* Test function for nfcNio APIs*/
static void NioWlc_test_raw_p2p_cb(uint32_t status, char* msg, uint32_t len)
{
	UART_MESSAGE_2("\nP2P msg sent, status=%d, len=%d\n\r", status, len);
	if (len)
		UART_MESSAGE_1STR("received: %s\n\r", msg);
}

bool NioWlc_test_raw_p2p(void)
{
	char * msg = "hello, this is NioWlc\n";

	NioWlc_nfc_set_raw_p2p_msg(msg, strlen(msg)+1);
	NioWlc_nfc_start_raw_p2p(&NioWlc_test_raw_p2p_cb);

	return 0;
}

static void NioWlc_test_cb(uint32_t mode, uint32_t status)
{
	UART_MESSAGE_2("\nNDEF Record sent, mode=%d, status=%d\n\r", mode, status);
}

bool NioWlc_test_cardemu(void)
{
/* wifi */
	struct wifi_info wifi_info;
	struct bt_info bt_info;

	static int mode = 4;

	mode++;

	if (mode == 5) /*wifi*/
	{
		UART_MESSAGE("\n\rWIFI mode\n\r");
#ifdef Nio_OOBData
#else
		wifi_info.ssid = "nfctest";
		wifi_info.password = "12345678";
		wifi_info.auth = WIFI_AUTH_WPA2_PERSONAL;
		wifi_info.crypt = WIFI_CRYPT_AES;
#endif

		NioWlc_nfc_set_wifi_info(&wifi_info,0);
		NioWlc_nfc_start_wifi_paring(&NioWlc_test_cb);
		//mode = 1;
	}else if (mode == 10)
	{
		UART_MESSAGE("\n\rBT mode\n\r");
#ifdef Nio_OOBData
		bt_info.bt_oob[5] = 0x22;
		bt_info.bt_oob[4] = 0x22;
		bt_info.bt_oob[3] = 0x22;
		bt_info.bt_oob[2] = 0x38;
		bt_info.bt_oob[1] = 0x47;
		bt_info.bt_oob[0] = 0x34;

		NioWlc_nfc_set_bt_info(&bt_info,6);
#else
		bt_info.mac[5] = 0x22;
		bt_info.mac[4] = 0x22;
		bt_info.mac[3] = 0x22;
		bt_info.mac[2] = 0x38;
		bt_info.mac[1] = 0x47;
		bt_info.mac[0] = 0x34;

		NioWlc_nfc_set_bt_info(&bt_info,0);
#endif

		NioWlc_nfc_start_bt_paring(&NioWlc_test_cb);
		mode = 0;
	}
	return 0;
}

#ifdef DEBUG_DELAY_TICK
#define ARM_CM_DEMCR (*(uint32_t *)0xE000EDFC)
#define ARM_CM_DWT_CTRL (*(uint32_t *)0xE0001000)
#define ARM_CM_DWT_CYCCNT (*(uint32_t *)0xE0001004)
static cm_dwt_init()
{
	if(ARM_CM_DWT_CTRL != 0)
	{
		ARM_CM_DEMCR |= 1<<24;
		ARM_CM_DWT_CYCCNT = 0;
		ARM_CM_DWT_CTRL |= 1<<0;
	}
}
#endif

/*********************************************
函数名称：NFC_Task_P2P
功能描述：NFC的P2P任务
输入参数：mode[in]：P2P配对模式
      pair_data[in]：待配对的参数信息（如：蓝牙MAC地址、WIFI的SSID等信息）
      len[in]:配对数据的长度
输出参数：NxpNci_P2P_Results：P2P配对结果
特殊声明：蓝牙数据的结构体为struct bt_info
      wifi数据的结构体为wifi_info
	       当蓝牙配对，且返回值为NxpNci_P2P_Results_HSACKOK时，需要读取gOOBData_From_MobileDevice的数据
**********************************************/
NxpNci_P2P_Results NFC_Task_P2P(NFC_P2P_PairingMode mode,void *pair_data,int len)
{
    NxpNci_RfIntf_t RfInterface;

	struct bt_info *bt_info;
	struct wifi_info *wifi_info ;
	NxpNci_P2P_Results retVal_task_nfc = NxpNci_P2P_Results_None;

#ifdef DEBUG_DELAY_TICK
	cm_dwt_init();
#endif

	nfc_mode = NXPNCI_MODE_P2P;

	if((pair_data == NULL) || (len < 0) || (len > 200))
	{
		retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_InvalidPara

		return retVal_task_nfc;
	}
	else
	{
		if(mode == NFC_P2PMode_Pairing_BT_Enable)
		{
			bt_info = (struct bt_info *)pair_data;
		}
		else if(mode == NFC_P2PMode_Pairing_WIFI_Enable)
		{
			wifi_info = (struct wifi_info *)pair_data;
		}
		else if((mode == NFC_P2PMode_Pairing_BT_Disable) || (mode == NFC_P2PMode_Pairing_BT_Disable))
		{
			retVal_task_nfc = NFC_P2P_Results_DisableOK;
			return retVal_task_nfc;
		}
		else
		{
			retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_PairingMode_Fail
			return retVal_task_nfc;
		}
	}

	if (nfc_mode == NXPNCI_MODE_P2P)
	{
#ifdef P2P_RAW
		UART_MESSAGE("NXPNCI_MODE_P2P mode\n\r");
		NioWlc_test_raw_p2p();
#else


		if(mode == NFC_P2PMode_Pairing_BT_Enable)
		{

			NioWlc_nfc_request_bt_info(bt_info,len);//NioWlc_nfc_request_bt_info(bt_info,len);
			NioWlc_nfc_set_bt_info(bt_info,len);

			if(P2P_NDEF_SetMessage_CH((unsigned char *) record_ch.buffer, (uint8_t)record_ch.length , *NdefPush_Cb) == false)
			{
				retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_SetMessage_Fail
				return retVal_task_nfc;
			}

			if(P2P_NDEF_SetMessage_SNEP((unsigned char *) record_snep.buffer, (uint8_t)record_snep.length , *NdefPush_Cb) == false)
			{
				retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_SetMessage_Fail
				return retVal_task_nfc;
			}
		}
		else if(mode == NFC_P2PMode_Pairing_WIFI_Enable)
		{
			NioWlc_nfc_set_wifi_info(wifi_info,len);

			if(P2P_NDEF_SetMessage_SNEP((unsigned char *) record_snep.buffer, (uint8_t)record_snep.length , *NdefPush_Cb) == false)
			{
				retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_SetMessage_Fail
				return retVal_task_nfc;
			}
		}
		else
		{
			retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_PairingMode_Fail
			return retVal_task_nfc;
		}

		P2P_NDEF_RegisterPullCallback(&NdefPull_Cb);

#endif
	}
	else if (nfc_mode == NXPNCI_MODE_CARDEMU)
	{
		//NioWlc_test_cardemu();
		retVal_task_nfc = NFC_P2P_Results_InternalError;
		return retVal_task_nfc;
	}
	else
	{
		retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_NfcMode_Fail
		return retVal_task_nfc;
	}

    /* Open connection to NXPNCI device */
    if (NxpNci_Connect() == NFC_ERROR)
    {
    	retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_NciConnet_Fail
        return retVal_task_nfc;
    }

    if (NxpNci_ConfigureSettings() == NFC_ERROR)
    {
    	retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_NciConfigureSet_Fail
    	return retVal_task_nfc;
    }

    if (NxpNci_ConfigureMode(nfc_mode) == NFC_ERROR)
    {
    	retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_NciConfigureMode_Fail
    	return retVal_task_nfc;
    }

    /* Start Discovery */
	if (nfc_mode == NXPNCI_MODE_P2P)
	{
		if (NxpNci_StartDiscovery(DiscoveryTechnologies_P2P,sizeof(DiscoveryTechnologies_P2P)) != NFC_SUCCESS)
	    {
			retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_NciDiscovery_Fail
			return retVal_task_nfc;
	    }
	}
	else if (nfc_mode == NXPNCI_MODE_CARDEMU)
	{
	    if (NxpNci_StartDiscovery(DiscoveryTechnologies_CardEmu,sizeof(DiscoveryTechnologies_CardEmu)) != NFC_SUCCESS)
	    {
	    	retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_NciDiscovery_Fail
	    	return retVal_task_nfc;
	    }
	}
	else
	{
		retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_NfcMode_Fail
		return retVal_task_nfc;
	}


        /* Wait until a peer is discovered */
        //while(NxpNci_WaitForDiscoveryNotification(&RfInterface, nfc_mode) != NFC_SUCCESS);

	if(NxpNci_WaitForDiscoveryNotification(&RfInterface, nfc_mode) != NFC_SUCCESS)
	{
		//retVal_task_nfc = NfcTask_P2P_Results_NotFoundEndpoint;

		if(NFC_P2PMode_Pairing_BT_Enable == mode )
		{
			retVal_task_nfc = NFC_P2P_Results_BT_Detection_Failed;
		}
		else if(NFC_P2PMode_Pairing_WIFI_Enable == mode)
		{
			retVal_task_nfc = NFC_P2P_Results_WIFI_Detection_Failed;
		}
		else
		{
			retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_PairingMode_Fail
		}

		return retVal_task_nfc;
	}

	if(nfc_mode == NXPNCI_MODE_CARDEMU)
	{
		retVal_task_nfc = NFC_P2P_Results_InternalError;
		return retVal_task_nfc;

		/* Is activated from remote T4T ? */
		if ((RfInterface.Interface == INTF_ISODEP) && ((RfInterface.ModeTech & MODE_MASK) == MODE_LISTEN))
		{
			NxpNci_ProcessCardMode(RfInterface);
		}
	}
	else if(nfc_mode == NXPNCI_MODE_P2P)
	{
		if (RfInterface.Interface == INTF_NFCDEP)
		{
			/*
			if ((RfInterface.ModeTech & MODE_LISTEN) == MODE_LISTEN)
				UART_MESSAGE("\n\r - P2P TARGET MODE: Activated from remote Initiator\n\r");
			else
				UART_MESSAGE("\n\r - P2P INITIATOR MODE: Remote Target activated\n\r");
			*/

			if(mode == NFC_P2PMode_Pairing_BT_Enable)
			{
				retVal_task_nfc = NxpNci_ProcessP2pMode(RfInterface,NFC_P2PMode_BT_WithoutOOB);//NFC_P2PMode_BT_WithOOB

				if(NxpNci_P2P_Results_WithOOB_OK == retVal_task_nfc )
				{
					;
				}
				else if(NxpNci_P2P_Results_WithoutOOB_OK == retVal_task_nfc)
				{
					retVal_task_nfc = NFC_P2P_Results_BT_WithoutOOB_OK;
				}
				else
				{
					retVal_task_nfc = NFC_P2P_Results_BT_Pairing_Failed;
				}
			}
			else if(mode == NFC_P2PMode_Pairing_WIFI_Enable)
			{
				retVal_task_nfc = NxpNci_ProcessP2pMode(RfInterface,NFC_P2PMode_WIFI_WithoutOOB);

				if(NxpNci_P2P_Results_WithoutOOB_OK != retVal_task_nfc )
				{
					retVal_task_nfc = NFC_P2P_Results_WIFI_Pairing_Failed;
				}
				else
				{
					retVal_task_nfc = NFC_P2P_Results_WIFI_WithoutOOB_OK;
				}
			}
			else
			{
				retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_PairingMode_Fail
				return retVal_task_nfc;
			}
		}
		else
		{
			retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_Interface_Fail
			return retVal_task_nfc;
		}
	}
	else
	{
		retVal_task_nfc = NFC_P2P_Results_InternalError;//NfcTask_P2P_Results_NfcMode_Fail
		return retVal_task_nfc;
	}

	return retVal_task_nfc;
}


/*********************************************
函数名称：NFC_Task_Tag
功能描述：NFC的卡识别任务
输入参数：无
输出参数：NxpNci_TAG_Results：卡识别执行的结果
特殊声明：无
**********************************************/
NxpNci_TAG_Results NFC_Task_Tag(void)
{
	//NxpNci_TAG_Results retVal_Task_Tag = NfcTask_Tag_Results_None;
	NxpNci_RfIntf_t RfInterface_Tag;

	if (NxpNci_Connect() == NFC_ERROR)
	{
		return NfcTask_Tag_Results_NciConnet_Fail;
	}


	if (NxpNci_StartDiscovery(DiscoveryTechnologies_Tag,sizeof(DiscoveryTechnologies_Tag)) != NFC_SUCCESS)
	{
		NxpNci_StopDiscovery(StopDiscovery_last_none);
		return NfcTask_Tag_Results_NciDiscovery_Fail;
	}

	if(NFC_SUCCESS==NxpNci_WaitForDiscoveryNotification(&RfInterface_Tag,NXPNCI_MODE_RW))
	{
		/* T1 */
		if((RfInterface_Tag.Protocol == PROT_T1T) \
				&& ((RfInterface_Tag.Info.NFC_APP.SensRes[0] & 0x3f)== 0x00) \
				&& (RfInterface_Tag.Info.NFC_APP.SensRes[1] == 0x0c))
		{
			/* 手机无法模拟出该类型，因此一旦是T1，则一定为标签 */
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			return NfcTask_Tag_Results_FoundTag_T1;
		}


		/* T2 ，只考虑b3设置为0的情况*/
		/*
		if((RfInterface_Tag.Protocol == PROT_T2T) \
				&& (RfInterface_Tag.Info.NFC_APP.SensRes[0]== 0x44) \
				&& (RfInterface_Tag.Info.NFC_APP.SensRes[1]== 0x00) \
				&& ((RfInterface_Tag.Info.NFC_APP.SelRes[0] & 0x60) == 0x00))
		*/
		/* T2标签--SensRes[0]=0x04,SensRes[1]=0x0,即NFCID1长度为4字节，且 SelRes[0]的bit3置高，即0x08*/
		if(RfInterface_Tag.Protocol == PROT_T2T)
		{
			/* 手机无法模拟出该类型，因此一旦是T2，则一定为标签 */
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			return NfcTask_Tag_Results_FoundTag_T2;
		}

		/* T3 */
		/* 需要关注RfInterface_Tag.Info.NFC_FPP.SensRes[0]和[1]，手机可以模拟T3卡，但支持NFC-DEP */

		if((RfInterface_Tag.Protocol == PROT_T3T) \
				&& (RfInterface_Tag.Info.NFC_FPP.SensRes[2] != 0x01) \
				&& (RfInterface_Tag.Info.NFC_FPP.SensRes[3] != 0xfe))
		{
			// 手机可以模拟出该类型，但协议为NFC-DEP且NFCID2[0]和[1]有区别
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			return NfcTask_Tag_Results_FoundTag_T3;
		}

		/* T4A,只考虑b3设置为0的情况 */
		if((RfInterface_Tag.Protocol == PROT_ISODEP) \
				&& (RfInterface_Tag.ModeTech == TECH_PASSIVE_NFCA) \
						&& (RfInterface_Tag.Info.NFC_APP.NfcIdLen== 0x07) \
						&& ((RfInterface_Tag.Info.NFC_APP.SelRes[0] & 0x60) == 0x20))
			/* 华为钱包手机模拟的T4A卡，它的SensRes[0] = 0x08/0x04 SensRes[1] = 0x00 ，即NFCID1的长度不同,难道手机模拟出来的长度和卡不一样？后续待确认*/
		{
			/* 暂时认为NFCID长度为4的是手机模拟，长度为7是标签 */
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			return NfcTask_Tag_Results_FoundTag_T4a;
		}

		/* T2(Miffare):通常的M1卡 */
		if((RfInterface_Tag.Protocol == PROT_MIFARE) \
								/* 有一些M1卡的SensRes[0]为0x02 */
								&& ((RfInterface_Tag.Info.NFC_APP.SensRes[0] & 0xc0) == 0x00 )\
								&& (RfInterface_Tag.Info.NFC_APP.SensRes[1]== 0x00) \
								&& ((RfInterface_Tag.Info.NFC_APP.SelRes[0] & 0x08) == 0x08))
			/* NFCID1长度为4字节 */
			/* SelRes的b3为任意值 */
		{
			/* 手机可以模拟出该类型，暂时无法区分出卡和手机 */
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			return NfcTask_Tag_Results_FoundTag_M1;
		}

		/* T4B：目前就手机可以模拟成T4B，将此种情况滤除，不进入卡保护 */
		if((RfInterface_Tag.Protocol == PROT_ISODEP) \
				&& (RfInterface_Tag.ModeTech == TECH_PASSIVE_NFCB))
		{
			/* 目前就手机可以模拟成T4B，将此种情况滤除，不进入卡保护 */
			NxpNci_StopDiscovery(StopDiscovery_last_none);

			return NfcTask_Tag_Results_NotFoundTag;
		}

		return NfcTask_Tag_Results_NotIdentify;
	}

	NxpNci_StopDiscovery(StopDiscovery_last_none);
	return NfcTask_Tag_Results_NotFoundTag;
}

/**************************
函数名称：NFC_Tag_init
功能描述：NFC标签初始化
输入参数：无
输出参数：NFC_SUCCESS:初始化成功
	   NFC_ERROR：初始化失败
**************************/
uint32_t NFC_Tag_init(void)
{
	if (NxpNci_Connect() == NFC_ERROR)
	{
		return NFC_ERROR;
	}

	return NFC_SUCCESS;
}

/**************************
函数名称：NFC_Tag_Discovery
功能描述：NFC标签识别
输入参数：无
输出参数：NFC_SUCCESS:初始化成功
	   NFC_ERROR：初始化失败
**************************/
uint32_t NFC_Tag_Discovery(void)
{
	NxpNci_RfIntf_t RfInterface_Tag;



#ifdef HW_Test
	if (NxpNci_StartDiscovery(DiscoveryTechnologies_F,sizeof(DiscoveryTechnologies_F)) != NFC_SUCCESS)
	{
		return DiscoveryResult_OpError;
	}

	if(NFC_SUCCESS==NxpNci_WaitForDiscoveryNotification(&RfInterface_Tag,NXPNCI_MODE_RW))
	{


		if((RfInterface_Tag.Protocol == PROT_T1T))
		{
			return DiscoveryResult_FoundTag;
		}
		else
		{

		   return DiscoveryResult_NotIdentify;
		}
	}

	return DiscoveryResult_NotFound;

#else

	if (NxpNci_StartDiscovery(DiscoveryTechnologies_Tag,sizeof(DiscoveryTechnologies_Tag)) != NFC_SUCCESS)
	{
		NxpNci_StopDiscovery(StopDiscovery_last_none);
		return DiscoveryResult_OpError;
	}

	if(NFC_SUCCESS==NxpNci_WaitForDiscoveryNotification(&RfInterface_Tag,NXPNCI_MODE_RW))
	{

		/* T1 */
		if((RfInterface_Tag.Protocol == PROT_T1T) \
				&& ((RfInterface_Tag.Info.NFC_APP.SensRes[0] & 0x3f)== 0x00) \
				&& (RfInterface_Tag.Info.NFC_APP.SensRes[1] == 0x0c))
		{
			/* 手机无法模拟出该类型，因此一旦是T1，则一定为标签 */
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			return DiscoveryResult_FoundTag;
		}


		/* T2 ，只考虑b3设置为0的情况*/
		/*
		if((RfInterface_Tag.Protocol == PROT_T2T) \
				&& (RfInterface_Tag.Info.NFC_APP.SensRes[0]== 0x44) \
				&& (RfInterface_Tag.Info.NFC_APP.SensRes[1]== 0x00) \
				&& ((RfInterface_Tag.Info.NFC_APP.SelRes[0] & 0x60) == 0x00))
		*/
		/* T2标签--SensRes[0]=0x04,SensRes[1]=0x0,即NFCID1长度为4字节，且 SelRes[0]的bit3置高，即0x08*/
		if(RfInterface_Tag.Protocol == PROT_T2T)
		{
			/* 手机无法模拟出该类型，因此一旦是T2，则一定为标签 */
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			return DiscoveryResult_FoundTag;
		}

		/* T3 */
		/* 需要关注RfInterface_Tag.Info.NFC_FPP.SensRes[0]和[1]，手机可以模拟T3卡，但支持NFC-DEP */

		if((RfInterface_Tag.Protocol == PROT_T3T) \
				&& (RfInterface_Tag.Info.NFC_FPP.SensRes[2] != 0x01) \
				&& (RfInterface_Tag.Info.NFC_FPP.SensRes[3] != 0xfe))
		{
			// 手机可以模拟出该类型，但协议为NFC-DEP且NFCID2[0]和[1]有区别
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			return DiscoveryResult_FoundTag;
		}

		/* T4A,只考虑b3设置为0的情况 */
		if((RfInterface_Tag.Protocol == PROT_ISODEP) \
				&& (RfInterface_Tag.ModeTech == TECH_PASSIVE_NFCA) \
						&& (RfInterface_Tag.Info.NFC_APP.NfcIdLen== 0x07) \
						&& ((RfInterface_Tag.Info.NFC_APP.SelRes[0] & 0x60) == 0x20))
			/* 华为钱包手机模拟的T4A卡，它的SensRes[0] = 0x08/0x04 SensRes[1] = 0x00 ，即NFCID1的长度不同,难道手机模拟出来的长度和卡不一样？后续待确认*/
		{
			/* 暂时认为NFCID长度为4的是手机模拟，长度为7是标签 */
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			return DiscoveryResult_FoundTag;
		}

		/* T2(Miffare):通常的M1卡 */
		if((RfInterface_Tag.Protocol == PROT_MIFARE) \
								/* 有一些M1卡的SensRes[0]为0x02 */
								&& ((RfInterface_Tag.Info.NFC_APP.SensRes[0] & 0xc0) == 0x00 )\
								&& (RfInterface_Tag.Info.NFC_APP.SensRes[1]== 0x00) \
								&& ((RfInterface_Tag.Info.NFC_APP.SelRes[0] & 0x08) == 0x08))
			/* NFCID1长度为4字节 */
			/* SelRes的b3为任意值 */
		{
			/* 手机可以模拟出该类型，暂时无法区分出卡和手机 */
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			return DiscoveryResult_FoundTag;
		}

		/* T4B：目前就手机可以模拟成T4B，将此种情况滤除，不进入卡保护 */
		if((RfInterface_Tag.Protocol == PROT_ISODEP) \
				&& (RfInterface_Tag.ModeTech == TECH_PASSIVE_NFCB))
		{
			/* 目前就手机可以模拟成T4B，将此种情况滤除，不进入卡保护 */
			NxpNci_StopDiscovery(StopDiscovery_last_none);

			return DiscoveryResult_NotFound;
		}

	}

	NxpNci_StopDiscovery(StopDiscovery_last_none);
	return DiscoveryResult_NotFound;
#endif
}


/*********************************************
函数名称：Get_ImmoDataLen
功能描述：获取IMMO的数据长度
输入参数：无
输出参数：获取IMMO的数据长度
特殊声明：
*********************************************/
int Get_ImmoDataLen(void)
{
	return Immo_DataIndex;
}

/*********************************************
函数名称：NFC_Task_IMMO_APDU
功能描述：NFC芯片与NFC_Device交换数据
输入参数：immo_type[in]:immo的类别
	    ： Time_CGW[in]：CGW的时间
	    ： Time_CGW_Len[in]：CGW的时间戳长度
	    ：immo_data[out]：immo操作后返回的数据
输出参数：NxpNci_RW_NDEF_Results：IMMO执行的结果
特殊声明：当返回结果为NfcTask_IMMO_Results_ReadNDEF_OK，需读取NdefBuffer_IMMO的数据
*********************************************/
static NxpNci_RW_NDEF_Results NFC_Task_IMMO_APDU(NFC_Task_IMMO_Type immo_type,unsigned char *Current_Time_CGW,uint8_t Time_CGW_Len)
{
	NxpNci_RW_NDEF_Results ret_IMMO_APDU = NxpNci_RW_NDEF_Results_None;
	bool retVal_ReaderTagCmd = NXPNCI_ERROR;

	unsigned char Rsp[1024] = {0x00};
	unsigned int RspSize = 0;
	unsigned char NFC_IMMO_Select_AID1[] = {0x00, 0xA4, 0x04, 0x00, 0x07, 0xF2, 0x18, 0xC2, 0xDA, 0xFB,0xC1,0x10};
	unsigned char NFC_IMMO_Select_AID2[] = {0x00, 0xA4, 0x04, 0x00, 0x07, 0xF2, 0x18, 0xC2, 0xDA, 0xFB,0xC1,0x20};


	//unsigned char time[6] = {0x14,0x03,0x11,0x0b,0x00,0x00};
	unsigned char time[6] = {0x00};
	unsigned char NFC_IMMO_Read[12] = {0x00,0xB0,0x00,0x00,0x06};

	unsigned char Response_OK[2] = {0x90, 0x00};
	unsigned char Response_NotFoundFile[2] = {0x6a, 0x82};

	if((NULL == Current_Time_CGW ) ||(6 != Time_CGW_Len))
	{
		ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_IMMOTypeWrong;

		return ret_IMMO_APDU;
	}

	if(NFC_Task_IMMO_Type_EnableAID1 == immo_type)
	{
		retVal_ReaderTagCmd = NxpNci_ReaderTagCmd(NFC_IMMO_Select_AID1, sizeof(NFC_IMMO_Select_AID1), Rsp, &RspSize);
	}
	else if(NFC_Task_IMMO_Type_EnableAID2 == immo_type)
	{
		retVal_ReaderTagCmd = NxpNci_ReaderTagCmd(NFC_IMMO_Select_AID2, sizeof(NFC_IMMO_Select_AID2), Rsp, &RspSize);
	}
	else
	{
		ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_IMMOTypeWrong;

		return ret_IMMO_APDU;
	}

	if(NXPNCI_ERROR == retVal_ReaderTagCmd)
	{
		ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_ReaderTag_Fail;

		return ret_IMMO_APDU;
	}

	if (0 != memcmp(&Rsp[RspSize -2], Response_OK, 2))
	{
		ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_SelectAID_Fail;

		return ret_IMMO_APDU;
	}

	RspSize = 0;
	Immo_DataIndex = 0;
	//实际需要使用时间戳

	memcpy(time,Current_Time_CGW,6);
	memcpy(&NFC_IMMO_Read[5],time,sizeof(time));
	NFC_IMMO_Read[11] = 0x00;

	/*
	if(NFC_Task_IMMO_Type_EnableAID1 == immo_type)
	{
		retVal_ReaderTagCmd = NxpNci_ReaderTagCmd(NFC_IMMO_Read, sizeof(NFC_IMMO_Read), Rsp, &RspSize);

		if((NXPNCI_ERROR == retVal_ReaderTagCmd) ||(RspSize < 2))
		{
			ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_ReaderTag_Fail;

			return ret_IMMO_APDU;
		}

		if(NFC_IMMO_APDU_NOTFOUNDFILE == memcmp(&Rsp[RspSize -2], Response_NotFoundFile, 2))
		{
			ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_ReaderTag_Fail;

			return ret_IMMO_APDU;
		}

		if((RspSize -2) > sizeof(gImmo_Data))
		{
			ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_NotEnoughBuffer;

			return ret_IMMO_APDU;
		}
		else
		{
			memcpy(&gImmo_Data[Immo_DataIndex], Rsp, RspSize -2);

			Immo_DataIndex += RspSize-2;

			ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_ReadCarKey_OK;
			return ret_IMMO_APDU;
		}
	}
	*/


	do
	{
		retVal_ReaderTagCmd = NxpNci_ReaderTagCmd(NFC_IMMO_Read, sizeof(NFC_IMMO_Read), Rsp, &RspSize);

		if((NXPNCI_ERROR == retVal_ReaderTagCmd) ||(RspSize < 2))
		{
			ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_ReaderTag_Fail;

			return ret_IMMO_APDU;
		}

		if(NFC_IMMO_APDU_NOTFOUNDFILE == memcmp(&Rsp[RspSize -2], Response_NotFoundFile, 2))
		{
			ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_ReaderTag_Fail;

			return ret_IMMO_APDU;
		}


		// immo_data
		if((RspSize -2) > sizeof(gImmo_Data))
		{
			ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_NotEnoughBuffer;

			return ret_IMMO_APDU;
		}
		else
		{
			memcpy(&gImmo_Data[Immo_DataIndex], Rsp, RspSize -2);

			Immo_DataIndex += RspSize-2;
		}

	}while(0 != memcmp(&Rsp[RspSize -2], Response_OK, 2));

	ret_IMMO_APDU = NFC_Task_IMMO_APDU_Results_ReadCarKey_OK;
	return ret_IMMO_APDU;
}

/*********************************************
函数名称：NFC_Task_IMM0
功能描述：NFC的IMMO任务
输入参数：immo_type[in]:immo的类别
	    ： Time_CGW[in]：CGW的时间
	    ： Time_CGW_Len[in]：CGW的时间戳长度
	    ：immo_data[out]：immo操作后返回的数据
输出参数：NxpNci_RW_NDEF_Results：IMMO执行的结果
特殊声明：当返回结果为NfcTask_IMMO_Results_ReadNDEF_OK，需读取NdefBuffer_IMMO的数据
*********************************************/
NxpNci_RW_NDEF_Results NFC_Task_IMM0(NFC_Task_IMMO_Type immo_type,unsigned char *Current_Time_CGW,uint8_t Time_CGW_Len)
{
	NxpNci_RfIntf_t RfInterface_IMMO;
	NxpNci_RW_NDEF_Results retVal_immo = NxpNci_RW_NDEF_Results_None;
	int *test;
	test = NULL;

	if(NFC_Task_IMMO_Type_Disable == immo_type)
	{
		/*  */
		//hal_NFCC_Reset();
		retVal_immo = NxpNci_READNDEF_Results_DisableOK;
		return retVal_immo;
	}

	if((NULL == Current_Time_CGW ) ||(6 != Time_CGW_Len))
	{
		retVal_immo = NfcTask_IMMO_Results_InternalError;

		return retVal_immo;
	}

	if (NxpNci_Connect() == NFC_ERROR)
	{
		retVal_immo = NfcTask_IMMO_Results_InternalError;//NfcTask_IMMO_Results_NciConnet_Fail
		return retVal_immo;
	}

	if (NxpNci_StartDiscovery(DiscoveryTechnologies_IMMO,sizeof(DiscoveryTechnologies_IMMO)) != NFC_SUCCESS)
	{
		NxpNci_StopDiscovery(StopDiscovery_last_none);

		retVal_immo = NfcTask_IMMO_Results_InternalError;//NfcTask_IMMO_Results_NciDiscovery_Fail
		return retVal_immo;
	}

	if(NFC_SUCCESS==NxpNci_WaitForDiscoveryNotification(&RfInterface_IMMO,NXPNCI_MODE_RW))
	{

		/* T4A,只考虑b3设置为0的情况 */
		if((RfInterface_IMMO.Protocol == PROT_ISODEP) \
				&& (RfInterface_IMMO.ModeTech == TECH_PASSIVE_NFCA) \
				&& (RfInterface_IMMO.Interface == INTF_ISODEP)\
						)
			/* 华为钱包手机模拟的T4A卡，它的SensRes[0] = 0x08/0x04 SensRes[1] = 0x00 ，即NFCID1的长度不同,难道手机模拟出来的长度和卡不一样？后续待确认*/
		{
			retVal_immo = NFC_Task_IMMO_APDU(immo_type,Current_Time_CGW,Time_CGW_Len);
			if(retVal_immo != NFC_Task_IMMO_APDU_Results_ReadCarKey_OK)
			{
				retVal_immo = NfcTask_IMMO_Results_InternalError;
			}


			/*读取卡片中的NDEF数据  */
			/*retVal_immo = NxpNci_ProcessReaderMode(RfInterface_IMMO,READ_NDEF);
			if(retVal_immo != NxpNci_READNDEF_Results_Finished)
			{
				retVal_immo = NfcTask_IMMO_Results_InternalError;
			}*/

			//RW_NDEF_SetMessage(test_array, sizeof(test_array), test);


			//写入相关数据
			//retVal_immo = NxpNci_ProcessReaderMode(RfInterface_IMMO,WRITE_NDEF);

			//读取相关数据，进行验证
			//retVal_immo = NxpNci_ProcessReaderMode(RfInterface_IMMO,READ_NDEF);


			/* 暂时认为NFCID长度为4的是手机模拟，长度为7是标签 */
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			return retVal_immo;
		}
		else
		{
			NxpNci_StopDiscovery(StopDiscovery_last_ok);

			retVal_immo = NfcTask_IMMO_Results_InternalError;//NfcTask_IMMO_Results_NFCTypeWrong
			return retVal_immo;
		}
	}

	NxpNci_StopDiscovery(StopDiscovery_last_none);

	retVal_immo = NfcTask_IMMO_Results_NotFoundEndpoint;
	return retVal_immo;
}

/*********************************************
函数名称：NFC_Task_LPCD_Cail
功能描述：NFC的LPCD校准任务
输入参数：cail_agc_val[out]：读取到的校准值
输出参数：NxpNci_LPCD_Cail_Results：LPCD校准执行的结果
特殊声明：当LPCD执行成功的时候，需要读取校准值
*********************************************/
NxpNci_LPCD_Cail_Results NFC_Task_LPCD_Cail(uint16_t *cail_agc_val)
{
	uint8_t index = 0;
	uint32_t calib_sum = 0;
	uint16_t sample_agc_value = 0;
	NxpNci_LPCD_Cail_Results retVal_LPCD_Cail = NxpNci_LPCD_Cail_Results_None;

	if(cail_agc_val == NULL)
	{
		retVal_LPCD_Cail = NxpNci_LPCD_Cail_Results_InvalidPara;
		return retVal_LPCD_Cail;
	}

	if (NxpNci_Connect() == NFC_ERROR)
	{
		retVal_LPCD_Cail = NxpNci_LPCD_Cail_Results_ConnectFail;
		return retVal_LPCD_Cail;
	}

	for(index = 0; index < NFC_LPCD_CALIB_CYCLES; index++)
	{
		if(NxpNci_Lpcd_SampleAgc(&sample_agc_value)!=NFC_SUCCESS)
		{
			retVal_LPCD_Cail = NxpNci_LPCD_Cail_Results_Fail;
			return retVal_LPCD_Cail;
		}

		calib_sum += sample_agc_value;
	}

	*cail_agc_val = calib_sum / NFC_LPCD_CALIB_CYCLES;

	//XMJ_CAN_1[2]=(lpcd_calib_agc_val&0x0300)>>8;
	//XMJ_CAN_1[3]=lpcd_calib_agc_val&0x00FF;

	retVal_LPCD_Cail = NxpNci_LPCD_Cail_Results_Success;
	return retVal_LPCD_Cail;
}


/*********************************************
函数名称：NFC_Task_LPCD_SingleDetect
功能描述：NFC的LPCD单次检测任务
输入参数：campare_agc_val[in]：待比较的agc值
输出参数：NxpNci_LPCD_Cail_Results：LPCD校准执行的结果
特殊声明：当LPCD执行成功的时候，需要读取校准值
*********************************************/
static LPCD_Single_Detecet NFC_Task_LPCD_SingleDetect(uint16_t *campare_agc_val)
{
	/* get calibraton value */
	uint16_t sample_agc_val = 0;
	LPCD_Single_Detecet retVal_LPCD_SingleDetect = LPCD_Single_Detecet_None;

	if(campare_agc_val == NULL)
	{
		retVal_LPCD_SingleDetect = LPCD_Single_Detecet_InvalidPara;
		return retVal_LPCD_SingleDetect;
	}

	if(NxpNci_Lpcd_SampleAgc(&sample_agc_val) == NFC_SUCCESS)
	{
		//return retVal_LPCD_SingleDetect;

#ifdef LPCD_TEST
		ZB_LPCD_TEST[4]=(sample_agc_val&0x0300)>>8;
		ZB_LPCD_TEST[5]=sample_agc_val&0x00FF;
#endif


		if(sample_agc_val >= *campare_agc_val)
		{
			if((sample_agc_val - *campare_agc_val) >= NFC_LPCD_DELTA)
			{
				retVal_LPCD_SingleDetect = LPCD_Single_Detecet_OverRange;
				return retVal_LPCD_SingleDetect;
			}
		}

		if(sample_agc_val < *campare_agc_val)
		{
			if((*campare_agc_val - sample_agc_val) >= NFC_LPCD_DELTA)
			{
				retVal_LPCD_SingleDetect = LPCD_Single_Detecet_OverRange;
				return retVal_LPCD_SingleDetect;
			}
		}

		retVal_LPCD_SingleDetect = LPCD_Single_Detecet_NotOverRange;
		return retVal_LPCD_SingleDetect;
	}


	retVal_LPCD_SingleDetect = LPCD_Single_Detecet_SampleFail;
	return retVal_LPCD_SingleDetect;
}


/*********************************************
函数名称：NFC_Task_LPCD_Detect
功能描述：NFC的LPCD检测任务
输入参数：campare_agc_val[in]：待比较的agc值
输出参数：NxpNci_LPCD_Detect_Results：LPCD检测执行的结果
特殊声明：无
*********************************************/
NxpNci_LPCD_Detect_Results NFC_Task_LPCD_Detect(uint16_t *campare_agc_val)
{
	LPCD_Single_Detecet retVal_LPCD_SingleDetect = LPCD_Single_Detecet_None;
	NxpNci_LPCD_Detect_Results retVal_LPCD_Detect = NxpNci_LPCD_Detect_Results_None;
	static uint8_t lpcd_cnt = 0;
	static uint8_t online_cnt = 0;

	if(campare_agc_val == NULL)
	{
		retVal_LPCD_Detect = NxpNci_LPCD_Detect_Results_InvalidPara;

		return retVal_LPCD_Detect;
	}


	retVal_LPCD_SingleDetect = NFC_Task_LPCD_SingleDetect(campare_agc_val);
	//return retVal_LPCD_Detect;
	if((retVal_LPCD_SingleDetect == LPCD_Single_Detecet_OverRange) || (retVal_LPCD_SingleDetect == LPCD_Single_Detecet_NotOverRange))
	{
		lpcd_cnt++;

		if(retVal_LPCD_SingleDetect == LPCD_Single_Detecet_OverRange)
	    {
			online_cnt++;
		}

		if(lpcd_cnt >= NFC_LPCD_DETECT_COUNT)
		{
			if(online_cnt >= NFC_LPCD_DETECT_ONLINE_COUNT)
			{
				lpcd_cnt = 0;
				online_cnt = 0;
				retVal_LPCD_Detect = NxpNci_LPCD_Detect_Results_FoundObject;
				return retVal_LPCD_Detect;

		    }
		    else
			{
		    	lpcd_cnt = 0;
		    	online_cnt = 0;
		    	retVal_LPCD_Detect = NxpNci_LPCD_Detect_Results_NotFoundObject;
		    	return retVal_LPCD_Detect;
		    }

		}
		else
		{
			retVal_LPCD_Detect = NxpNci_LPCD_Detect_Results_NotFinish;
			return retVal_LPCD_Detect;
		}
	 }



	retVal_LPCD_Detect = NxpNci_LPCD_Detect_Results_Error;

	return retVal_LPCD_Detect;

}


/*********************************************
函数名称：NFC_Task_EMCTest
功能描述：NFC的EMC测试任务
输入参数：Emc_NFC_mode[in]：EMC的NFC测试模式
输出参数：NFC_Task_EMC_Results:反馈测试结果
特殊声明：无
*********************************************/
NFC_Task_EMC_Results NFC_Task_EMCTest(NFC_Task_EMC_Mode Emc_NFC_mode)
{
	NFC_Task_EMC_Results retVal = NFC_Task_EMC_Results_None;
	NxpNci_RW_NDEF_Results retVal_RW = NxpNci_RW_NDEF_Results_None;
	NxpNci_RfIntf_t RfInterface_EMCTest;

	switch(Emc_NFC_mode)
	{
		case NFC_Task_EMC_Mode_DisablePing:
			retVal = NFC_Task_EMC_Results_Succeed;
			break;
		case NFC_Task_EMC_Mode_DisableCommunication:
			retVal = NFC_Task_EMC_Results_Succeed;
			break;
		case NFC_Task_EMC_Mode_EnablePing:
			if (NxpNci_Connect() == NFC_ERROR)
			{
				retVal = NFC_Task_EMC_Results_Failed;
				return retVal;
			}

			if (NxpNci_StartDiscovery(DiscoveryTechnologies_IMMO,sizeof(DiscoveryTechnologies_IMMO)) != NFC_SUCCESS)
			{
				//NxpNci_StopDiscovery(StopDiscovery_last_none);

				retVal = NFC_Task_EMC_Results_Failed;
			}
			else
			{
				retVal = NFC_Task_EMC_Results_Succeed;
			}

			break;
		case NFC_Task_EMC_Mode_EnableCommunication:
			if (NxpNci_Connect() == NFC_ERROR)
			{
				retVal = NFC_Task_EMC_Results_Failed;
				return retVal;
			}

			if (NxpNci_StartDiscovery(DiscoveryTechnologies_IMMO,sizeof(DiscoveryTechnologies_IMMO)) != NFC_SUCCESS)
			{
				NxpNci_StopDiscovery(StopDiscovery_last_none);

				retVal = NFC_Task_EMC_Results_Failed;
				return retVal;
			}

			if(NFC_SUCCESS == NxpNci_WaitForDiscoveryNotification(&RfInterface_EMCTest,NXPNCI_MODE_RW))
			{

				/* T4A,只考虑b3设置为0的情况 */
				if((RfInterface_EMCTest.Protocol == PROT_ISODEP) \
						&& (RfInterface_EMCTest.ModeTech == TECH_PASSIVE_NFCA) \
						&& (RfInterface_EMCTest.Interface == INTF_ISODEP)\
								)
				{
					/*读取卡片中的NDEF数据  */
					retVal_RW = NxpNci_ProcessReaderMode(RfInterface_EMCTest,READ_NDEF);
					if(retVal_RW != NxpNci_READNDEF_Results_Finished)
					{
						retVal = NFC_Task_EMC_Results_Failed;
					}
					else
					{
						retVal = NFC_Task_EMC_Results_Succeed;
					}


					/* 暂时认为NFCID长度为4的是手机模拟，长度为7是标签 */
					NxpNci_StopDiscovery(StopDiscovery_last_ok);

				}
				else
				{
					NxpNci_StopDiscovery(StopDiscovery_last_ok);

					retVal = NFC_Task_EMC_Results_Failed;
				}
			}
			else
			{
				retVal = NFC_Task_EMC_Results_Failed;
			}


			break;
		default:
			retVal = NFC_Task_EMC_Results_Failed;
			break;
	}

	return retVal;
}
