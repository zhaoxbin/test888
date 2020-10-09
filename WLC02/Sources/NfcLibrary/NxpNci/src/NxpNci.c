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

#include <NxpNci.h>
#include <Nfc_settings.h>
#include <hal.h>


#define MAX_NCI_FRAME_SIZE    256
#define MAX(x,y)    (x > y ? x : y)

#define MAX_VAILD_PACKET_COUNT (15)
#define INDEX_HS_PAYLOAD_LENGTH (23)
#define INDEX_HS_OOBDATA_START (60)

static uint8_t gNfcController_generation = 0;
static uint8_t gNextTag_Protocol = PROT_UNDETERMINED;

uint8_t gOOBData_From_MobileDevice[MAX_OOB_DATALENGTH] = {0x00};
int gOOBData_len = 0;

static bool NxpNci_CheckDevPres(void)
{
    uint8_t NCICoreReset[] = {0x20, 0x00, 0x01, 0x01};
    uint8_t Answer[6];
    uint16_t NbBytes = 0;

    hal_Send(NCICoreReset, sizeof(NCICoreReset), &NbBytes);
#ifdef NCI_DEBUG
    NCI_UART_MESSAGE("\n \rNCI >> ");
    NCI_BUFFER_PRINT(NCICoreReset, NbBytes);
#endif
    if (NbBytes != sizeof(NCICoreReset)) return NXPNCI_ERROR;


    hal_Receive(Answer, sizeof(Answer), &NbBytes, 0);
    if ((NbBytes == 0) || (Answer[0] != 0x40) || (Answer[1] != 0x00)) return NXPNCI_ERROR;
#ifdef NCI_DEBUG
    NCI_UART_MESSAGE("\n \rNCI << ");
    NCI_BUFFER_PRINT( Answer, NbBytes);
#endif

    return NXPNCI_SUCCESS;
}
static bool NxpNci_WaitForReception(uint8_t *pRBuff, uint16_t RBuffSize, uint16_t *pBytesread, uint32_t timeout)
{
    hal_Receive(pRBuff, RBuffSize, pBytesread, timeout);
    if (*pBytesread == 0) return NXPNCI_ERROR;

#ifdef NCI_DEBUG
    NCI_UART_MESSAGE("\n \rNCI << ");
    NCI_BUFFER_PRINT(pRBuff, *pBytesread);
#endif

    return NXPNCI_SUCCESS;
}
static bool NxpNci_HostTransceive(uint8_t *pTBuff, uint16_t TbuffLen, uint8_t *pRBuff, uint16_t RBuffSize, uint16_t *pBytesread)
{
#ifdef Except
	hal_Clear(pRBuff, RBuffSize, pBytesread);
	*pBytesread = 0;
#endif

    hal_Send(pTBuff, TbuffLen, pBytesread);

#ifdef NCI_DEBUG
    NCI_UART_MESSAGE("\n \rNCI >> ");
    NCI_BUFFER_PRINT(pTBuff, TbuffLen);
#endif

    if (*pBytesread != TbuffLen) return NXPNCI_ERROR;


    hal_Receive(pRBuff, RBuffSize, pBytesread, TIMEOUT_1S);
    if (*pBytesread == 0) return NXPNCI_ERROR;

#ifdef NCI_DEBUG
    NCI_UART_MESSAGE("\n \rNCI << ");
    NCI_BUFFER_PRINT(pRBuff, *pBytesread);
#endif

    return NXPNCI_SUCCESS;
}

static bool NxpNci_ClearReception(uint8_t *pRBuff, uint16_t RBuffSize, uint16_t *pBytesread)
{
	hal_Clear(pRBuff, RBuffSize, pBytesread);

    return NXPNCI_SUCCESS;
}

static void NxpNci_FillInterfaceInfo(NxpNci_RfIntf_t* pRfIntf, uint8_t* pBuf)
{
    uint8_t i;

    switch(pRfIntf->ModeTech)
    {
    case (MODE_POLL | TECH_PASSIVE_NFCA):
                    memcpy(pRfIntf->Info.NFC_APP.SensRes, &pBuf[0], 2);
    pRfIntf->Info.NFC_APP.NfcIdLen = pBuf[2];
    memcpy(pRfIntf->Info.NFC_APP.NfcId, &pBuf[3], pRfIntf->Info.NFC_APP.NfcIdLen);
    pRfIntf->Info.NFC_APP.SelResLen = pBuf[3+pBuf[2]];
    if(pRfIntf->Info.NFC_APP.SelResLen == 1) pRfIntf->Info.NFC_APP.SelRes[0] = pBuf[3+pBuf[2]+1];
    break;

    case (MODE_POLL | TECH_PASSIVE_NFCB):
                    pRfIntf->Info.NFC_BPP.SensResLen = pBuf[0];
    memcpy(pRfIntf->Info.NFC_BPP.SensRes, &pBuf[1], pRfIntf->Info.NFC_BPP.SensResLen);
    break;

    case (MODE_POLL | TECH_PASSIVE_NFCF):
                    pRfIntf->Info.NFC_FPP.BitRate = pBuf[0];
    pRfIntf->Info.NFC_FPP.SensResLen = pBuf[1];
    memcpy(pRfIntf->Info.NFC_FPP.SensRes, &pBuf[2], pRfIntf->Info.NFC_FPP.SensResLen);
    break;

    case (MODE_POLL | TECH_PASSIVE_15693):
                    pRfIntf->Info.NFC_VPP.AFI = pBuf[0];
    pRfIntf->Info.NFC_VPP.DSFID = pBuf[1];
    for(i=0; i<8; i++) pRfIntf->Info.NFC_VPP.ID[7-i] = pBuf[2+i];
    break;

    default:
        break;
    }
}

void NxpNci_ProcessCardMode(NxpNci_RfIntf_t RfIntf)
{
    uint8_t Answer[MAX_NCI_FRAME_SIZE];
    uint16_t AnswerSize;

    /* Reset Card emulation state */
    T4T_NDEF_EMU_Reset();

    while(NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_2S) == NXPNCI_SUCCESS)
    {
        /* is RF_DEACTIVATE_NTF ? */
        if((Answer[0] == 0x61) && (Answer[1] == 0x06))
        {
            /* Come back to discovery state */
            break;
        }
        /* is DATA_PACKET ? */
        else if((Answer[0] == 0x00) && (Answer[1] == 0x00))
        {
            /* DATA_PACKET */
            uint8_t Cmd[MAX_NCI_FRAME_SIZE];

            uint16_t CmdSize;

            T4T_NDEF_EMU_Next(&Answer[3], Answer[2], &Cmd[3], (unsigned short *) &CmdSize);

            Cmd[0] = 0x00;
            Cmd[1] = (CmdSize & 0xFF00) >> 8;
            Cmd[2] = CmdSize & 0x00FF;

            NxpNci_HostTransceive(Cmd, CmdSize+3, Answer, sizeof(Answer), &AnswerSize);
        }
    }
}

bool NxpNci_CardModeReceive (unsigned char *pData, unsigned char *pDataSize)
{
    bool status = NXPNCI_ERROR;
    uint8_t Ans[MAX_NCI_FRAME_SIZE];
    uint16_t AnsSize;

    NxpNci_WaitForReception(Ans, sizeof(Ans), &AnsSize, TIMEOUT_2S);

    /* Is data packet ? */
    if ((Ans[0] == 0x00) && (Ans[1] == 0x00))
    {
        *pDataSize = Ans[2];
        memcpy(pData, &Ans[3], *pDataSize);
        status = NXPNCI_SUCCESS;
    }

    return status;
}

bool NxpNci_CardModeSend (unsigned char *pData, unsigned char DataSize)
{
    bool status;
    uint8_t Cmd[MAX_NCI_FRAME_SIZE];
    uint8_t Ans[MAX_NCI_FRAME_SIZE];
    uint16_t AnsSize;

    /* Compute and send DATA_PACKET */
    Cmd[0] = 0x00;
    Cmd[1] = 0x00;
    Cmd[2] = DataSize;
    memcpy(&Cmd[3], pData, DataSize);
    //status = NxpNci_HostSend(Cmd, DataSize+3);
    status = NxpNci_HostTransceive(Cmd, DataSize+3, Ans, sizeof(Ans), &AnsSize);

    return status;
}

/*
 * 函数名称：NFC_Get_OOBDdataLen
 * 函数功能：获取的蓝牙OOB数据长度
 * 形式参数：无
 * 返回参数：数据长度
 */
int NFC_Get_OOBDataLen(void)
{
	return gOOBData_len;
}


NxpNci_P2P_Results NxpNci_ProcessP2pMode(NxpNci_RfIntf_t RfIntf,NFC_P2PMode p2p_mode)
{
    uint8_t Answer[MAX_NCI_FRAME_SIZE] = {0x00};
    uint16_t AnswerSize = 0;
    bool restart;
    uint8_t NCILlcpSymm[] = {0x00, 0x00, 0x02, 0x00, 0x00};
    uint8_t NCIRestartDiscovery[] = {0x21, 0x06, 0x01, 0x03};
    uint8_t Cmd[MAX_NCI_FRAME_SIZE] = {0x00};
    uint16_t CmdSize = 0;
    NxpNci_P2P_Results flag_error = NxpNci_P2P_Results_None;
    uint8_t valid_packet_count = 0;

    if(p2p_mode == NFC_P2PMode_BT_WithOOB)
    {
    	P2P_NDEF_Reset_CH();
    }
    else
    {
    	/* Reset P2P_NDEF state */
    	P2P_NDEF_Reset_SNEP();
    }


    /* Is Initiator mode ? */
    if((RfIntf.ModeTech & MODE_LISTEN) != MODE_LISTEN)
    {
        /* Initiate communication (SYMM PDU) */
        NxpNci_HostTransceive(NCILlcpSymm, sizeof(NCILlcpSymm), Answer, sizeof(Answer), &AnswerSize);
    }

    /* Get frame from remote peer */
    while(NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_1S) == NXPNCI_SUCCESS)
    {
        /* 根据NCI规范判断是否为数据消息 */
    	/* 采用静态连接，其连接ID默认为0；预留字节为0 */
        if((Answer[0] == 0x00) && (Answer[1] == 0x00))
        {

#ifdef P2P_RAW
			P2P_RAW_Next(&Answer[3], Answer[2], &Cmd[3], (unsigned short *) &CmdSize);
#else
			if(p2p_mode == NFC_P2PMode_BT_WithOOB)
			{
				P2P_NDEF_Next_CH(&Answer[3], Answer[2], &Cmd[3], (unsigned short *) &CmdSize);
			}
			else
			{
				P2P_NDEF_Next_SNEP(&Answer[3], Answer[2], &Cmd[3], (unsigned short *) &CmdSize);
			}

#endif

            if(CmdSize == LLCP_SNEP_ACK_OK)
			{
            	flag_error = NxpNci_P2P_Results_WithoutOOB_OK;

				break;
			}

            if(CmdSize == LLCP_CH_ACK_OK )
			{

				/* 保存得到的OOB数据 */
				if(Answer[INDEX_HS_PAYLOAD_LENGTH] <= MAX_OOB_DATALENGTH)
				{
					//notification require ack
					gOOBData_From_MobileDevice[0] = 0x02;
					//BT
					gOOBData_From_MobileDevice[1] = 0x01;
					//withOOB
					gOOBData_From_MobileDevice[2] = 0x04;

					memcpy(&gOOBData_From_MobileDevice[3],&Answer[INDEX_HS_OOBDATA_START],Answer[INDEX_HS_PAYLOAD_LENGTH]);

					gOOBData_len = 3 + Answer[INDEX_HS_PAYLOAD_LENGTH]-2;

					flag_error = NxpNci_P2P_Results_WithOOB_OK;
				}
				else
				{
					flag_error = NxpNci_P2P_Results_HS_OOBDATA_OVERSIZE;
				}

				break;
			}

			/* LLCP链路去激活 */
			if(CmdSize == LLCP_DISC_ACK_OK)
			{
				flag_error = NxpNci_P2P_Results_LLCPDEACTIVE;

				break;
			}

			/* 连接被拒绝 */
			if(CmdSize == LLCP_DM_ACK_OK)
			{
				flag_error = NxpNci_P2P_Results_LLCPREFUSED;

				break;
			}

			valid_packet_count ++;
			if(valid_packet_count > MAX_VAILD_PACKET_COUNT)
			{
				flag_error = NxpNci_P2P_Results_COUNTOVER;

				break;
			}

            /* 采用静态连接，连接ID为0 */
            Cmd[0] = 0x00;
            /* 预留字节设定为0 */
            //Cmd[1] = (CmdSize & 0xFF00) >> 8;
            Cmd[1] = 0x00;
            Cmd[2] = CmdSize & 0x00FF;

            NxpNci_HostTransceive(Cmd, CmdSize+3, Answer, sizeof(Answer), &AnswerSize);
        }
        /* is CORE_INTERFACE_ERROR_NTF ?*/
        else if ((Answer[0] == 0x60) && (Answer[1] == 0x08))
        {
        	flag_error = NxpNci_P2P_Results_NOTDATAPACKET;

            break;
        }
        /* is RF_DEACTIVATE_NTF ? */
        else if((Answer[0] == 0x61) && (Answer[1] == 0x06))
        {
        	flag_error = NxpNci_P2P_Results_NOTDATAPACKET;

            /* Come back to discovery state */
            break;
        }
        /* is RF_DISCOVERY_NTF ? */
        else if((Answer[0] == 0x61) && ((Answer[1] == 0x05) || (Answer[1] == 0x03)))
        {
        	flag_error = NxpNci_P2P_Results_NOTDATAPACKET;

        	break;

            restart = false;
            do{
                if((Answer[6] & MODE_LISTEN) != MODE_LISTEN) restart = true;
                NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_100MS);

                /* 单独增加 */
                if((Answer[0] == 0x61) && (Answer[1] == 0x06))
                {
                	restart = false;
                	break;
                }
            }
            while (AnswerSize != 0);
            if(restart)
            {
                NxpNci_HostTransceive(NCIRestartDiscovery, sizeof(NCIRestartDiscovery), Answer, sizeof(Answer), &AnswerSize);
            }
        }
    }

    if(p2p_mode == NFC_P2PMode_BT_WithOOB)
    {
    	if(flag_error != NxpNci_P2P_Results_WithOOB_OK	)
    	{
    		valid_packet_count = 0;
    		P2P_NDEF_Reset_SNEP();

    		NxpNci_HostTransceive(NCILlcpSymm, sizeof(NCILlcpSymm), Answer, sizeof(Answer), &AnswerSize);
			while(NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_1S) == NXPNCI_SUCCESS)
			{
				if((Answer[0] == 0x00) && (Answer[1] == 0x00))
				{
					P2P_NDEF_Next_SNEP(&Answer[3], Answer[2], &Cmd[3], (unsigned short *) &CmdSize);

					/* LLCP链路去激活 */
					if(CmdSize == LLCP_DISC_ACK_OK)
					{
						flag_error = NxpNci_P2P_Results_LLCPDEACTIVE;

						break;
					}

					/* 得到正确的snep响应 */
					if(CmdSize == LLCP_SNEP_ACK_OK)
					{
						flag_error = NxpNci_P2P_Results_WithoutOOB_OK;

						break;
					}

					valid_packet_count ++;
					if(valid_packet_count > 10)
					{
						flag_error = NxpNci_P2P_Results_COUNTOVER;

						break;
					}

					Cmd[0] = 0x00;
					Cmd[1] = 0x00;
					Cmd[2] = CmdSize & 0x00FF;

					NxpNci_HostTransceive(Cmd, CmdSize+3, Answer, sizeof(Answer), &AnswerSize);
				}
				else if((Answer[0] == 0x60) && (Answer[1] == 0x08))
				{
					flag_error = NxpNci_P2P_Results_NOTDATAPACKET;

					break;
				}
				else if((Answer[0] == 0x61) && (Answer[1] == 0x06))
				{
					flag_error = NxpNci_P2P_Results_NOTDATAPACKET;

					break;
				}

			}
    	}
    }

    /* Is Initiator mode ? */
    if((RfIntf.ModeTech & MODE_LISTEN) != MODE_LISTEN)
    {
        /* Communication ended, restart discovery loop */
        NxpNci_HostTransceive(NCIRestartDiscovery, sizeof(NCIRestartDiscovery), Answer, sizeof(Answer), &AnswerSize);
        NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_100MS);
    }

    return flag_error;
}


/*
 * 读卡器模式
 */
bool NxpNci_ReaderTagCmd (unsigned char *pCommand, unsigned char CommandSize, unsigned char *pAnswer, unsigned int *pAnswerSize)
{
	bool status = NXPNCI_ERROR;
    uint8_t Cmd[32];
	uint8_t Ans[320]={0x00,};//256
	uint16_t AnsSize = 0;
	unsigned int total_size = 0;

	/* Compute and send DATA_PACKET */
	Cmd[0] = 0x00;
	Cmd[1] = 0x00;
	Cmd[2] = CommandSize;
	memcpy(&Cmd[3], pCommand, CommandSize);
	NxpNci_HostTransceive(Cmd, CommandSize+3, Ans, sizeof(Ans), &AnsSize);

	/* Wait for Answer */
	status = NxpNci_WaitForReception(Ans, sizeof(Ans), &AnsSize, TIMEOUT_1S);

	if(NXPNCI_ERROR == status)
	{
		return status;
	}

	if ((Ans[0] == 0x00) && (Ans[1] == 0x00))
	{
		/* NCI数据消息完整的一帧，未分组 */
		*pAnswerSize = Ans[2];

		memcpy(pAnswer, &Ans[3], *pAnswerSize);

		status = NXPNCI_SUCCESS;
	}
	else if((Ans[0] == 0x10) && (Ans[1] == 0x00))
	{
		memcpy(&pAnswer[total_size], &Ans[3], Ans[2]);

		/* NCI消息分段与重组 */
		total_size += AnsSize-3;
		AnsSize = 0;

		do
		{
			status = NxpNci_WaitForReception(Ans, sizeof(Ans), &AnsSize, TIMEOUT_1S);

			if(NXPNCI_SUCCESS == status)
			{
				memcpy(&pAnswer[total_size], &Ans[3], Ans[2]);

				total_size += AnsSize-3;
				AnsSize = 0;
			}
			else
			{
				break;
			}
		}while((Ans[0] == 0x10) && (Ans[1] == 0x00));


		if(NXPNCI_SUCCESS == status)
		{
			*pAnswerSize = total_size;

			status = NXPNCI_SUCCESS;

			return status;
		}
		else
		{
			return status;
		}
	}
	else
	{
		status = NXPNCI_ERROR;
		return status;
	}

	return status;
}

static uint8_t NxpNci_T3TretrieveIDm (void)
{
	uint8_t NCIPollingCmdT3T[] = {0x21, 0x08, 0x04, 0x12, 0xFC, 0x00, 0x01};
	uint8_t Answer[MAX_NCI_FRAME_SIZE];
	uint16_t AnswerSize;

	NxpNci_HostTransceive(NCIPollingCmdT3T, sizeof(NCIPollingCmdT3T), Answer, sizeof(Answer), &AnswerSize);
	NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_100MS);
	if ((Answer[0] == 0x61) && (Answer[1] == 0x08) && (Answer[3] == 0x00))
	{
		RW_NDEF_T3T_SetIDm(&Answer[6]);
	}
	else
	{
		return NXPNCI_ERROR;
	}
	return NXPNCI_SUCCESS;
}

static NxpNci_RW_NDEF_Results NxpNci_ReadNdef(NxpNci_RfIntf_t RfIntf)
{
	uint8_t Answer[MAX_NCI_FRAME_SIZE];
	uint16_t AnswerSize = 0;
    uint8_t Cmd[MAX_NCI_FRAME_SIZE];
    uint16_t CmdSize = 0;
    NxpNci_RW_NDEF_Results retVal_ReadNDEF = NxpNci_RW_NDEF_Results_None;
    //uint8_t Nfc_T4_Rats[] = {0x00,0x00,0x02,0xE0,0x80};

	RW_NDEF_Reset(RfIntf.Protocol);

	/* In case of T3T tag, retrieve card IDm for further operation */
	if (RfIntf.Protocol == PROT_T3T) NxpNci_T3TretrieveIDm();


	while(1)
	{
		RW_NDEF_Read_Next(&Answer[3], Answer[2], &Cmd[3], (unsigned short *) &CmdSize);
		if(CmdSize == RW_NDEF_T4T_OPERATION_NONE)
		{
			retVal_ReadNDEF = NxpNci_READNDEF_Results_NotOK;
			break;
		}
		else if(CmdSize == RW_NDEF_T4T_FAULT_OVERSIZE)
		{
			retVal_ReadNDEF = NxpNci_READNDEF_Results_NotEnoughBuffer;
			break;
		}
		else if(CmdSize == RW_NDEF_T4T_READ_FINSH)
		{
			retVal_ReadNDEF = NxpNci_READNDEF_Results_Finished;
			break;
		}
		else
		{
			/* Compute and send DATA_PACKET */
			Cmd[0] = 0x00;
			//Cmd[1] = (CmdSize & 0xFF00) >> 8;
			Cmd[1] = 0x00;
			Cmd[2] = CmdSize & 0x00FF;

			NxpNci_HostTransceive(Cmd, CmdSize+3, Answer, sizeof(Answer), &AnswerSize);
	        NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_100MS);
		}
	}

	return retVal_ReadNDEF;
}

static void NxpNci_WriteNdef(NxpNci_RfIntf_t RfIntf)
{
	uint8_t Answer[MAX_NCI_FRAME_SIZE];
	uint16_t AnswerSize;
    uint8_t Cmd[MAX_NCI_FRAME_SIZE];
    uint16_t CmdSize = 0;

	RW_NDEF_Reset(RfIntf.Protocol);

	/* In case of T3T tag, retrieve card IDm for further operation */
	if (RfIntf.Protocol == PROT_T3T) NxpNci_T3TretrieveIDm();

	while(1)
	{
		RW_NDEF_Write_Next(&Answer[3], Answer[2], &Cmd[3], (unsigned short *) &CmdSize);
		if(CmdSize == 0)
		{
			/* End of the Write operation */
			break;
		}
		else
		{
			/* Compute and send DATA_PACKET */
			Cmd[0] = 0x00;
			Cmd[1] = (CmdSize & 0xFF00) >> 8;
			Cmd[2] = CmdSize & 0x00FF;

			NxpNci_HostTransceive(Cmd, CmdSize+3, Answer, sizeof(Answer), &AnswerSize);
	        NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_2S);
		}
	}
}

static void NxpNci_PresenceCheck(NxpNci_RfIntf_t RfIntf)
{
    uint8_t Answer[MAX_NCI_FRAME_SIZE];
    uint16_t AnswerSize;

    uint8_t NCIPresCheckT1T[] = {0x00, 0x00, 0x07, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t NCIPresCheckT2T[] = {0x00, 0x00, 0x02, 0x30, 0x00};
    uint8_t NCIPresCheckT3T[] = {0x21, 0x08, 0x04, 0x12, 0xFC, 0x00, 0x01};
    uint8_t NCIPresCheckIsoDep[] = {0x2F, 0x11, 0x00};
    uint8_t NCIPresCheckIso15693[] = {0x00, 0x00, 0x03, 0x26, 0x01, 0x00};
    uint8_t NCIDeactivate[] = {0x21, 0x06, 0x01, 0x01};
    uint8_t NCISelectMIFARE[] = {0x21, 0x04, 0x03, 0x01, 0x80, 0x80};

    switch (RfIntf.Protocol) {
    case PROT_T1T:
        do
        {
            //SLEEP(500);
            NxpNci_HostTransceive(NCIPresCheckT1T, sizeof(NCIPresCheckT1T), Answer, sizeof(Answer), &AnswerSize);
            NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_1S);
        } while ((Answer[0] == 0x00) && (Answer[1] == 0x00));
        break;

    case PROT_T2T:
        do
        {
            //SLEEP(500);
            NxpNci_HostTransceive(NCIPresCheckT2T, sizeof(NCIPresCheckT2T), Answer, sizeof(Answer), &AnswerSize);
            NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_1S);
        } while ((Answer[0] == 0x00) && (Answer[1] == 0x00) && (Answer[2] == 0x11));
        break;

    case PROT_T3T:
        do
        {
            //SLEEP(500);
            NxpNci_HostTransceive(NCIPresCheckT3T, sizeof(NCIPresCheckT3T), Answer, sizeof(Answer), &AnswerSize);
            NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_1S);
        } while ((Answer[0] == 0x61) && (Answer[1] == 0x08) && (Answer[3] == 0x00));
        break;

    case PROT_ISODEP:
        do
        {
            //SLEEP(500);
            NxpNci_HostTransceive(NCIPresCheckIsoDep, sizeof(NCIPresCheckIsoDep), Answer, sizeof(Answer), &AnswerSize);
            NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_1S);
        } while ((Answer[0] == 0x6F) && (Answer[1] == 0x11) && (Answer[2] == 0x01) && (Answer[3] == 0x01));
        break;

    case PROT_ISO15693:
        do
        {
            //SLEEP(500);
            NxpNci_HostTransceive(NCIPresCheckIso15693, sizeof(NCIPresCheckIso15693), Answer, sizeof(Answer), &AnswerSize);
            NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_1S);
        } while ((Answer[0] == 0x00) && (Answer[1] == 0x00));
        break;

    case PROT_MIFARE:
        do
        {
            //SLEEP(500);
            /* Deactivate target */
            NxpNci_HostTransceive(NCIDeactivate, sizeof(NCIDeactivate), Answer, sizeof(Answer), &AnswerSize);
            NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_1S);
            /* Reactivate target */
            NxpNci_HostTransceive(NCISelectMIFARE, sizeof(NCISelectMIFARE), Answer, sizeof(Answer), &AnswerSize);
            NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_1S);
        } while ((Answer[0] == 0x61) && (Answer[1] == 0x05));
        break;

    default:
        /* Nothing to do */
        break;
    }
}

NxpNci_RW_NDEF_Results NxpNci_ProcessReaderMode(NxpNci_RfIntf_t RfIntf, NxpNci_RW_Operation_t Operation)
{
	NxpNci_RW_NDEF_Results retVal_ProcessReaderMode = NxpNci_RW_NDEF_Results_None;

	switch (Operation)
	{
	case READ_NDEF:
		retVal_ProcessReaderMode = NxpNci_ReadNdef(RfIntf);
		break;

	case WRITE_NDEF:
		NxpNci_WriteNdef(RfIntf);
		break;

	case PRESENCE_CHECK:
		NxpNci_PresenceCheck(RfIntf);
		break;

	default:
		break;
	}

	return retVal_ProcessReaderMode;
}

bool NxpNci_Connect(void)
{
    uint8_t i = 10;
    uint8_t NCICoreInit[] = {0x20, 0x01, 0x00};
    uint8_t Answer[MAX_NCI_FRAME_SIZE] = {0x00};
    uint16_t AnswerSize = 0;
    uint8_t NCICore_Config_Get_TOTAL_DURATION[] = {0x20, 0x03, 0x02,0x01,0x00};
    uint8_t NCICore_Config_Set_TOTAL_DURATION[] = {0x20, 0x02,0x05 ,0x01,0x00,0x02,0x32,0x00};
    /* 开启NCI属性扩展功能 */
    //uint8_t NCICore_PROPRIETARY_ACT_CMD[] = {0x2f, 0x02, 0x00};

    //uint8_t NCICore_ConfigEXT_Get[] = {0x20, 0x03, 0x07,0x03,0xa0,0x40,0xa0,0x41,0xa0,0x42};
    uint8_t NCIDiscoverMap[] = {0x21, 0x00,16,0x05,0x01,0x01,0x01,0x02,0x01,0x01,0x03,0x01,0x01,0x04,0x01,0x02,0x80,0x01,0x80};

    /* Reset NFC Device */
    hal_NFCC_Reset();

    /* Loop until NXPNCI answers */
    while(NxpNci_CheckDevPres() != NXPNCI_SUCCESS)
    {
        if(i-- == 0) return NXPNCI_ERROR;
        hal_Sleep(TIMEOUT_1S);
#ifdef Except

        NxpNci_ClearReception(Answer,sizeof(Answer),&AnswerSize);
        if ((Answer[0] == 0x40) && (Answer[1] == 0x00) && (Answer[3] == 0x00))
        {
        	break;
        }
#endif
    }

    NxpNci_HostTransceive(NCICoreInit, sizeof(NCICoreInit), Answer, sizeof(Answer), &AnswerSize);
    if ((Answer[0] != 0x40) || (Answer[1] != 0x01) || (Answer[3] != 0x00))
	{
#ifdef Except

    	memset(Answer,0x00,sizeof(Answer));
    	AnswerSize = 0;

        NxpNci_ClearReception(Answer,sizeof(Answer),&AnswerSize);
        if((Answer[0] != 0x40) || (Answer[1] != 0x01) || (Answer[3] != 0x00))
        {
        	return NXPNCI_ERROR;
        }
#else
        return NXPNCI_ERROR;
#endif
	}

    /* Retrieve NXP-NCI NFC Controller generation */
    if (Answer[17+Answer[8]] == 0x08) gNfcController_generation = 1;
    else if (Answer[17+Answer[8]] == 0x10) gNfcController_generation = 2;


    /* 配置TOTAL_DURATION：做成仅在卡识别、IMMO下进行配置 */
    NxpNci_HostTransceive(NCICore_Config_Set_TOTAL_DURATION, sizeof(NCICore_Config_Set_TOTAL_DURATION), Answer, sizeof(Answer), &AnswerSize);
    NxpNci_HostTransceive(NCICore_Config_Get_TOTAL_DURATION, sizeof(NCICore_Config_Get_TOTAL_DURATION), Answer, sizeof(Answer), &AnswerSize);
    if ((Answer[0] != 0x40) || (Answer[1] != 0x03) || (Answer[3] != 0x00) || (Answer[7] != 0x32) || (Answer[8] != 0x00))
    {
#ifdef Except

    	memset(Answer,0x00,sizeof(Answer));
    	AnswerSize = 0;

        NxpNci_ClearReception(Answer,sizeof(Answer),&AnswerSize);
        if((Answer[0] != 0x40) || (Answer[1] != 0x03) || (Answer[3] != 0x00) || (Answer[7] != 0x32) || (Answer[8] != 0x00))
        {
        	return NXPNCI_ERROR;
        }
#else
        return NXPNCI_ERROR;
#endif
    }

/*
    NxpNci_HostTransceive(NCICore_PROPRIETARY_ACT_CMD, sizeof(NCICore_PROPRIETARY_ACT_CMD), Answer, sizeof(Answer), &AnswerSize);
    if ((Answer[0] != 0x4F) || (Answer[1] != 0x02) || (Answer[3] != 0x00))
    {
#ifdef Except

    	memset(Answer,0x00,sizeof(Answer));
    	AnswerSize = 0;

        NxpNci_ClearReception(Answer,sizeof(Answer),&AnswerSize);
        if((Answer[0] != 0x4F) || (Answer[1] != 0x02) || (Answer[3] != 0x00))
        {
        	return NXPNCI_ERROR;
        }
#else
        return NXPNCI_ERROR;
#endif
    }

    NxpNci_HostTransceive(NCICore_ConfigEXT_Get, sizeof(NCICore_ConfigEXT_Get), Answer, sizeof(Answer), &AnswerSize);
*/



	NxpNci_HostTransceive(NCIDiscoverMap, sizeof(NCIDiscoverMap), Answer, sizeof(Answer), &AnswerSize);
	if ((Answer[0] != 0x41) || (Answer[1] != 0x00) || (Answer[3] != 0x00))
	{
		return NXPNCI_ERROR;
	}

    return NXPNCI_SUCCESS;
}

bool NxpNci_ConfigureSettings(void)
{
    uint8_t Answer[MAX_NCI_FRAME_SIZE] = {0x00};
    uint16_t AnswerSize = 0 ;
    uint8_t NCICoreReset[] = {0x20, 0x00, 0x01, 0x00};
    uint8_t NCICoreInit[] = {0x20, 0x01, 0x00};
#if NXP_TVDD_CONF
    uint8_t *NxpNci_CONF;
    uint16_t NxpNci_CONF_size = 0;
#endif
    bool isResetRequired = false;

    /* Apply settings according definition of Nfc_settings.h header file */

#if NXP_CORE_CONF
    if (sizeof(NxpNci_CORE_CONF) != 0)
    {
        isResetRequired = true;
        NxpNci_HostTransceive(NxpNci_CORE_CONF, sizeof(NxpNci_CORE_CONF), Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] != 0x40) || (Answer[1] != 0x02) || (Answer[3] != 0x00) || (Answer[4] != 0x00)) return NXPNCI_ERROR;
    }
#endif

#if NXP_CORE_CONF_EXTN
    if (sizeof(NxpNci_CORE_CONF_EXTN) != 0)
    {
        isResetRequired = true;
        NxpNci_HostTransceive(NxpNci_CORE_CONF_EXTN, sizeof(NxpNci_CORE_CONF_EXTN), Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] != 0x40) || (Answer[1] != 0x02) || (Answer[3] != 0x00) || (Answer[4] != 0x00)) return NXPNCI_ERROR;
    }
#endif

#if NXP_CORE_STANDBY
    if (sizeof(NxpNci_CORE_STANDBY) != 0)
    {
        isResetRequired = true;
        NxpNci_HostTransceive(NxpNci_CORE_STANDBY, sizeof(NxpNci_CORE_STANDBY), Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] != 0x4F) || (Answer[1] != 0x00) || (Answer[3] != 0x00)) return NXPNCI_ERROR;
    }
#endif

#if NXP_CLK_CONF
    if (sizeof(NxpNci_CLK_CONF) != 0)
    {
        isResetRequired = true;
        NxpNci_HostTransceive(NxpNci_CLK_CONF, sizeof(NxpNci_CLK_CONF), Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] != 0x40) || (Answer[1] != 0x02) || (Answer[3] != 0x00) || (Answer[4] != 0x00)) return NXPNCI_ERROR;
    }

#endif

#if NXP_TVDD_CONF
    if(gNfcController_generation == 1)
    {
        NxpNci_CONF = NxpNci_TVDD_CONF_1stGen;
        NxpNci_CONF_size = sizeof(NxpNci_TVDD_CONF_1stGen);
    }
    else if(gNfcController_generation == 2)
    {
        NxpNci_CONF = NxpNci_TVDD_CONF_2ndGen;
        NxpNci_CONF_size = sizeof(NxpNci_TVDD_CONF_2ndGen);
    }
    if (NxpNci_CONF_size != 0)
    {
        isResetRequired = true;
        NxpNci_HostTransceive(NxpNci_CONF, NxpNci_CONF_size, Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] != 0x40) || (Answer[1] != 0x02) || (Answer[3] != 0x00) || (Answer[4] != 0x00)) return NXPNCI_ERROR;
    }
#endif

    if(isResetRequired)
    {
        /* Reset the NFC Controller to insure new settings apply */
        NxpNci_HostTransceive(NCICoreReset, sizeof(NCICoreReset), Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] != 0x40) || (Answer[1] != 0x00) || (Answer[3] != 0x00)) return NXPNCI_ERROR;
        NxpNci_HostTransceive(NCICoreInit, sizeof(NCICoreInit), Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] != 0x40) || (Answer[1] != 0x01) || (Answer[3] != 0x00)) return NXPNCI_ERROR;
    }

    return NXPNCI_SUCCESS;
}

bool NxpNci_ConfigureMode(unsigned char mode)
{
    uint8_t Command[MAX_NCI_FRAME_SIZE] = {0x00};
    uint8_t Answer[MAX_NCI_FRAME_SIZE] = {0x00};
    uint16_t AnswerSize = 0;
    uint8_t Item = 0;

    uint8_t NCIDiscoverMap[] = {0x21, 0x00};
	/* CARDEMU */
    const uint8_t DM_CARDEMU[] = {0x4, 0x2, 0x2};
    const uint8_t R_CARDEMU[] = {0x1, 0x3, 0x0, 0x1, 0x4};
	/* P2P */
    const uint8_t DM_P2P[] = {0x5, 0x3, 0x3};
    const uint8_t R_P2P[] = {0x1, 0x3, 0x0, 0x1, 0x5};
    uint8_t NCISetConfig_NFC[] = {0x20, 0x02, 0x1F, 0x02, 0x29, 0x0D, 0x46, 0x66, 0x6D, 0x01, 0x01, 0x11, 0x03, 0x02, 0x00, 0x01, 0x04, 0x01, 0xFA, 0x61, 0x0D, 0x46, 0x66, 0x6D, 0x01, 0x01, 0x11, 0x03, 0x02, 0x00, 0x01, 0x04, 0x01, 0xFA};

    uint8_t NCIRouting[] = {0x21, 0x01, 0x07, 0x00, 0x01};
    uint8_t NCISetConfig_NFCA_SELRSP[] = {0x20, 0x02, 0x04, 0x01, 0x32, 0x01, 0x00};

    if(mode == 0) return NXPNCI_SUCCESS;

    /* Building Discovery Map command */
    Item = 0;
    if (mode == NXPNCI_MODE_CARDEMU)
    {
        memcpy(&Command[4+(3*Item)], DM_CARDEMU, sizeof(DM_CARDEMU));
        Item++;
    }else if (mode == NXPNCI_MODE_P2P)
    {
        memcpy(&Command[4+(3*Item)], DM_P2P, sizeof(DM_P2P));
        Item++;
    }

    if (Item != 0)
    {
        memcpy(Command, NCIDiscoverMap, sizeof(NCIDiscoverMap));
        Command[2] = 1 + (Item*3);
        Command[3] = Item;
        NxpNci_HostTransceive(Command, 3 + Command[2], Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] != 0x41) || (Answer[1] != 0x00) || (Answer[3] != 0x00)) return NXPNCI_ERROR;
    }

    /* Configuring routing */
    Item = 0;
    if (mode == NXPNCI_MODE_CARDEMU)
    {
        memcpy(&Command[5+(5*Item)], R_CARDEMU, sizeof(R_CARDEMU));
        Item++;
    }else if (mode == NXPNCI_MODE_P2P)
    {
        memcpy(&Command[5+(5*Item)], R_P2P, sizeof(R_P2P));
        Item++;
    }

    if (Item != 0)
    {
        memcpy(Command, NCIRouting, sizeof(NCIRouting));
        Command[2] = 2 + (Item*5);
        Command[4] = Item;
        NxpNci_HostTransceive(Command, 3 + Command[2] , Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] != 0x41) || (Answer[1] != 0x01) || (Answer[3] != 0x00)) return NXPNCI_ERROR;
    }

    /* Setting NFCA SEL_RSP */
    if (mode == NXPNCI_MODE_CARDEMU)
    {
        NCISetConfig_NFCA_SELRSP[6] += 0x20;
    } else if (mode == NXPNCI_MODE_P2P)
    {
        NCISetConfig_NFCA_SELRSP[6] += 0x40;
    }

    if (NCISetConfig_NFCA_SELRSP[6] != 0x00)
    {
        NxpNci_HostTransceive(NCISetConfig_NFCA_SELRSP, sizeof(NCISetConfig_NFCA_SELRSP), Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] != 0x40) || (Answer[1] != 0x02) || (Answer[3] != 0x00)) return NXPNCI_ERROR;
    }

    /* Setting LLCP support */
    if (mode == NXPNCI_MODE_P2P)
    {
        NxpNci_HostTransceive(NCISetConfig_NFC, sizeof(NCISetConfig_NFC), Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] != 0x40) || (Answer[1] != 0x02) || (Answer[3] != 0x00)) return NXPNCI_ERROR;
    }

    return NXPNCI_SUCCESS;
}

bool NxpNci_StartDiscovery(const unsigned char *pTechTab, unsigned char TechTabSize)
{
    uint8_t Buffer[MAX_NCI_FRAME_SIZE] = {0x00};
    uint8_t Answer[MAX_NCI_FRAME_SIZE] = {0x00};
    uint16_t AnswerSize = 0;
    uint8_t i;


    Buffer[0] = 0x21;
    Buffer[1] = 0x03;
    Buffer[2] = (TechTabSize * 2) + 1;
    Buffer[3] = TechTabSize;
    for (i=0; i<TechTabSize; i++)
    {
        Buffer[(i*2)+4] = pTechTab[i];
        Buffer[(i*2)+5] = 0x01;
    }

    NxpNci_HostTransceive(Buffer, (TechTabSize * 2) + 4, Answer, sizeof(Answer), &AnswerSize);
    if ((Answer[0] != 0x41) || (Answer[1] != 0x03) || (Answer[3] != 0x00))
    {
#ifdef Except

    	memset(Answer,0x00,sizeof(Answer));
    	AnswerSize = 0;

        NxpNci_ClearReception(Answer,sizeof(Answer),&AnswerSize);
        if((Answer[0] != 0x41) || (Answer[1] != 0x03) || (Answer[3] != 0x00))
        {
        	return NXPNCI_ERROR;
        }
#else
        return NXPNCI_ERROR;
#endif
    }


    return NXPNCI_SUCCESS;
}


/*********************************************************
 * 函数名称：NxpNci_StopDiscovery
 * 功能描述：NCF3340停止搜索
 * 形参：discovery_result[in]：上一次的搜索结果
 * 返回值：NXPNCI_ERROR，操作失败；
 * 	         ：NXPNCI_SUCCESS，操作成功
 ********************************************************/
bool NxpNci_StopDiscovery(unsigned char last_discovery_result)
{

    uint8_t NCIStopDiscovery[] = {0x21, 0x06, 0x01, 0x00};
    uint8_t Answer[MAX_NCI_FRAME_SIZE] = {0x00};
    uint16_t AnswerSize = 0;

    /* 去激活并响应 */
    NxpNci_HostTransceive(NCIStopDiscovery, sizeof(NCIStopDiscovery), Answer, sizeof(Answer), &AnswerSize);
    if((AnswerSize == 0) || (Answer[0] != 0x41) || (Answer[1] != 0x06) || (Answer[3] != 0x00))
    {
    	return NXPNCI_ERROR;
    }

    if(last_discovery_result)
    {
    	/* 需要等待去激活的通知消息 */
    	NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_1S);
    	if((AnswerSize == 0) || (Answer[0] != 0x61) || (Answer[1] != 0x06) || (Answer[3] != 0x00))
    	{
#ifdef Except
			memset(Answer,0x00,sizeof(Answer));
			AnswerSize = 0;

			NxpNci_ClearReception(Answer,sizeof(Answer),&AnswerSize);
			if((AnswerSize == 0) || (Answer[0] != 0x61) || (Answer[1] != 0x06) || (Answer[3] != 0x00))
			{
				return NXPNCI_ERROR;
			}
#else
        return NXPNCI_ERROR;
#endif
    	}
    }
    else
    {
    	;
    }



    NxpNci_ClearReception(Answer,sizeof(Answer),&AnswerSize);


    return NXPNCI_SUCCESS;
}

bool NxpNci_WaitForDiscoveryNotification(NxpNci_RfIntf_t *pRfIntf, unsigned int mode)
{
#if 0
	unsigned char  TEST_Ppolling[1] = {0x00
	                                          //MODE_LISTEN | TECH_PASSIVE_NFCA
	                                          //,MODE_LISTEN | TECH_PASSIVE_NFCF
	                                          //,MODE_LISTEN | TECH_ACTIVE_NFCA
	                                          //,MODE_LISTEN | TECH_ACTIVE_NFCF
	};
	unsigned char  TEST_P2P[2] = {
		                                          MODE_LISTEN | TECH_PASSIVE_NFCA
		                                          ,MODE_LISTEN | TECH_PASSIVE_NFCF
		                                          //,MODE_LISTEN | TECH_ACTIVE_NFCA
		                                          //,MODE_LISTEN | TECH_ACTIVE_NFCF
		};
#endif

    uint8_t NCIRfDiscoverSelect[] = {0x21, 0x04, 0x03, 0x01, PROT_ISODEP, INTF_ISODEP};
    uint8_t Answer[MAX_NCI_FRAME_SIZE] = {0x00};
    uint16_t AnswerSize = 0;
    uint8_t polling_timeout_cntr = 0;
    uint32_t single_wait_timeout = 0;
    uint8_t retry_count = 0;
    uint8_t ret = 0;
#ifdef P2P_SUPPORT
    uint8_t NCIRestartDiscovery[] = {0x21, 0x06, 0x01, 0x03};
    uint8_t saved_NTF[7];

wait:
#endif


	if(NXPNCI_MODE_P2P == mode)
	{
		/* 连接超时时间为5min */
		single_wait_timeout = TIMEOUT_5S;

		retry_count = 2;//NFC_P2P_MAX_RETRY_60s

	}
	else
	{
		single_wait_timeout = TIMEOUT_5S;//TIMEOUT_100MS

		retry_count = 0;//NFC_RW_MAX_RETRY_500ms
	}

	do
    {
        //if(NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_INFINITE) == NXPNCI_ERROR) return NXPNCI_ERROR;

        if (NXPNCI_ERROR == NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize,TIMEOUT_5S ))//single_wait_timeout
		{
			return NXPNCI_ERROR;
		}
#if 0
        if (NXPNCI_ERROR == NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize,single_wait_timeout ))
		{
        	if(NXPNCI_MODE_P2P == mode)
        	{
				NxpNci_StopDiscovery(0);
				ret = NxpNci_StartDiscovery(TEST_Ppolling,1);
				NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize,TIMEOUT_100MS );
				ret = NxpNci_StopDiscovery(1);

				AnswerSize = 0;
				ret = NxpNci_StartDiscovery(TEST_P2P,2);
				NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize,TIMEOUT_5S );
				if((Answer[0] != 0x61) || ((Answer[1] != 0x05) && (Answer[1] != 0x03)))
				{
					return NXPNCI_ERROR;
				}
				else
				{
					break;
				}
        	}
        	else
        	{
        		return NXPNCI_ERROR;
        	}
		};
#endif

        /*
		if(polling_timeout_cntr++ > 0)//retry_count
		{
			return NXPNCI_ERROR;
		}
		*/

    }while ((Answer[0] != 0x61) || ((Answer[1] != 0x05) && (Answer[1] != 0x03)));

    gNextTag_Protocol = PROT_UNDETERMINED;

    /* Is RF_INTF_ACTIVATED_NTF ? */
    if (Answer[1] == 0x05)
    {
        pRfIntf->Interface = Answer[4];
        pRfIntf->Protocol = Answer[5];
        pRfIntf->ModeTech = Answer[6];
        pRfIntf->MoreTags = false;
        NxpNci_FillInterfaceInfo(pRfIntf, &Answer[10]);
        return NXPNCI_SUCCESS;
		if (mode == NXPNCI_MODE_P2P)
		{
	        /* Verifying if not a P2P device also presenting T4T emulation */
	        if ((pRfIntf->Interface == INTF_ISODEP) && (pRfIntf->Protocol == PROT_ISODEP) && ((pRfIntf->ModeTech & MODE_LISTEN) != MODE_LISTEN))
	        {
	            memcpy(saved_NTF, Answer, sizeof(saved_NTF));
	            while(1)
	            {
	                /* Restart the discovery loop */ 
	                NxpNci_HostTransceive(NCIRestartDiscovery, sizeof(NCIRestartDiscovery), Answer, sizeof(Answer), &AnswerSize);
	                NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_100MS);

	                /* Wait for discovery */
	                do NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_1S);
	                while ((AnswerSize == 4) && (Answer[0] == 0x60) && (Answer[1] == 0x07));

	                if ((AnswerSize != 0) && (Answer[0] == 0x61) && (Answer[1] == 0x05))
	                {
	                    /* Is same device detected ? */
	                    if (memcmp(saved_NTF, Answer, sizeof(saved_NTF)) == 0) break;
	                    /* Is P2P detected ? */
	                    if (Answer[5] == PROT_NFCDEP)
	                    {
	                        pRfIntf->Interface = Answer[4];
	                        pRfIntf->Protocol = Answer[5];
	                        pRfIntf->ModeTech = Answer[6];
	                        pRfIntf->MoreTags = false;
	                        NxpNci_FillInterfaceInfo(pRfIntf, &Answer[10]);
	                        break;
	                    }
	                }
	                else
	                {
	                    if (AnswerSize != 0)
	                    {
	                        /* Restart the discovery loop */ 
	                        NxpNci_HostTransceive(NCIRestartDiscovery, sizeof(NCIRestartDiscovery), Answer, sizeof(Answer), &AnswerSize);
	                        NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_100MS);
	                    }
	                    goto wait;
	                }
	            }
	        }
		}
    }
    else /* RF_DISCOVER_NTF */
    {
        pRfIntf->Interface = INTF_UNDETERMINED;
        pRfIntf->Protocol = Answer[4];
        pRfIntf->ModeTech = Answer[5];
        pRfIntf->MoreTags = true;

        /* Get next NTF for further activation */
        do {
            if(NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_500MS) == NXPNCI_ERROR)    return NXPNCI_ERROR;
        } while ((Answer[0] != 0x61) || (Answer[1] != 0x03));
        gNextTag_Protocol = Answer[4];

        /* Remaining NTF ? */
        while(Answer[AnswerSize-1] == 0x02) NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_500MS);

        /* In case of multiple cards, select the first one */
        NCIRfDiscoverSelect[4] = pRfIntf->Protocol;
        if (pRfIntf->Protocol == PROT_ISODEP) NCIRfDiscoverSelect[5] = INTF_ISODEP;
        else if (pRfIntf->Protocol == PROT_NFCDEP) NCIRfDiscoverSelect[5] = INTF_NFCDEP;
        else if (pRfIntf->Protocol == PROT_MIFARE) NCIRfDiscoverSelect[5] = INTF_TAGCMD;
        else NCIRfDiscoverSelect[5] = INTF_FRAME;

        /* 发现Id也要实际填写--20200316新增 */
        NCIRfDiscoverSelect[3] = 0x02;

        if(NXPNCI_MODE_P2P == mode)
		{
        	NCIRfDiscoverSelect[4] = PROT_NFCDEP;
        	NCIRfDiscoverSelect[5] = INTF_NFCDEP;
		}
        else
        {
			NCIRfDiscoverSelect[4] = PROT_ISODEP;
			NCIRfDiscoverSelect[5] = INTF_ISODEP;
        }

        NxpNci_HostTransceive(NCIRfDiscoverSelect, sizeof(NCIRfDiscoverSelect), Answer, sizeof(Answer), &AnswerSize);
        if ((Answer[0] == 0x41) && (Answer[1] == 0x04) && (Answer[3] == 0x00))
        //if ((Answer[0] == 0x41) || (Answer[1] == 0x04) || (Answer[3] == 0x00))
        {
            NxpNci_WaitForReception(Answer, sizeof(Answer), &AnswerSize, TIMEOUT_500MS);//TIMEOUT_100MS
            if ((Answer[0] == 0x61) && (Answer[1] == 0x05))
            //if ((Answer[0] == 0x61) || (Answer[1] == 0x05))
            {
                pRfIntf->Interface = Answer[4];
                pRfIntf->Protocol = Answer[5];
                pRfIntf->ModeTech = Answer[6];
                NxpNci_FillInterfaceInfo(pRfIntf, &Answer[10]);
            }
            else
            {
            	return NXPNCI_ERROR;
            }
        }
        else
        {
        	return NXPNCI_ERROR;
        }
    }

    /* In case of unknown target align protocol information */
    if (pRfIntf->Interface == INTF_UNDETERMINED) pRfIntf->Protocol = PROT_UNDETERMINED;

    return NXPNCI_SUCCESS;
}

/*********************************************
函数名称：NxpNci_Lpcd_SampleAgc
功能描述：LPCD的AGC值采样
输入参数：agc_val[out]：采样到的AGC值
输出参数：NXPNCI_SUCCESS：采样成功
      NXPNCI_ERROR：采样失败
特殊声明：当返回值为NXPNCI_SUCCESS时，需要读取采样到的AGC值
*********************************************/
bool NxpNci_Lpcd_SampleAgc(uint16_t *agc_val)
{
	uint8_t NCICoreReset[] = {0x20, 0x00, 0x01, 0x01};
	uint8_t NCICoreInit[] = {0x20, 0x01, 0x00};
	uint8_t NCIAntennaTestCmdAgc[] = {0x2F, 0x3D, 0x04, 0x02, 0xC8, 0x60, 0x03};
	//uint8_t NCIAntennaTestCmdAgcNfcLd[] = {0x2F, 0x3D, 0x04, 0x04, 0x20, 0x08, 0x20};
	uint8_t Answer[32];
	uint16_t AnswerSize = 0;
	uint16_t agc_tmp = 0x00;

	if(agc_val == NULL)
	{
		return NXPNCI_ERROR;
	}

	hal_NFCC_Reset();

	/* antenna test cmd with agc only */
	NxpNci_HostTransceive(NCICoreReset, sizeof(NCICoreReset), Answer, sizeof(Answer), &AnswerSize);
	if ((Answer[0] != 0x40) || (Answer[1] != 0x00) || (Answer[3] != 0x00))
	{
		return NXPNCI_ERROR;
#ifdef Except

		memset(Answer,0x00,sizeof(Answer));
		AnswerSize = 0;

		NxpNci_ClearReception(Answer,sizeof(Answer),&AnswerSize);
		if((Answer[0] != 0x40) || (Answer[1] != 0x00) || (Answer[3] != 0x00))
		{
			return NXPNCI_ERROR;
		}
#else
		return NXPNCI_ERROR;
#endif
	}

    NxpNci_HostTransceive(NCICoreInit, sizeof(NCICoreInit), Answer, sizeof(Answer), &AnswerSize);
    if ((Answer[0] != 0x40) || (Answer[1] != 0x01) || (Answer[3] != 0x00))
	{
    	return NXPNCI_ERROR;
#ifdef Except

    	memset(Answer,0x00,sizeof(Answer));
    	AnswerSize = 0;

        NxpNci_ClearReception(Answer,sizeof(Answer),&AnswerSize);
        if((Answer[0] != 0x40) || (Answer[1] != 0x01) || (Answer[3] != 0x00))
        {
        	return NXPNCI_ERROR;
        }
#else
        return NXPNCI_ERROR;
#endif
	}

	NxpNci_HostTransceive(NCIAntennaTestCmdAgc, sizeof(NCIAntennaTestCmdAgc), Answer, sizeof(Answer), &AnswerSize);
	if ((Answer[0] != 0x4F) || (Answer[1] != 0x3D) || (Answer[3] != 0x00)) return NXPNCI_ERROR;
	if(AnswerSize == 8)
	{

		agc_tmp = (Answer[5] & 0x03) << 8;
		*agc_val = agc_tmp | Answer[4];
	}
	else
	{
		return NXPNCI_ERROR;
	}

	return NXPNCI_SUCCESS;
}
