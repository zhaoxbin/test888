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

#ifdef P2P_SUPPORT
#include <stddef.h>
#include <P2P_NDEF.h>


/* Well-known LLCP SAP Values */
#define SAP_SDP         1
#define SAP_SNEP        4

/* SNEP codes */
/* 版本号  */
#define SNEP_VER10      0x10

/* SNEP请求消息 */
#define SNEP_PUT        0x02

/* SNEP响应消息 */
#define SNEP_SUCCESS    0x81


/* LLCP PDU Types */
#define SYMM            0x0
#define PAX             0x1
#define AGF             0x2
#define UI              0x3
#define CONNECT         0x4
#define DISC            0x5
#define CC              0x6
#define DM              0x7
#define FRMR            0x8
#define SNL             0x9
#define reservedA       0xA
#define reservedB       0xB
#define I               0xC
#define RR              0xD
#define RNR             0xE
#define reservedF       0xF

/* LLCP PDU */
#define VERSION     1
#define MIUX        2
#define WKS         3
#define LTO         4
#define RW          5
#define SN          6

const unsigned char SNEP_PUT_SUCCESS[] = {SNEP_VER10, SNEP_SUCCESS, 0x00, 0x00, 0x00, 0x00};
const unsigned char LLCP_CONNECT_SNEP[] = {0x11, 0x20};
const unsigned char LLCP_I_SNEP_PUT_HEADER[] = {SNEP_VER10, SNEP_PUT, 0x00, 0x00, 0x00, 0x00};
const unsigned char LLCP_SYMM[] = {0x00, 0x00};
/*  */
const unsigned char LLCP_SNL[] = {0x06, 0x41,0x08,0x14,0x01,'u','r','n',':','n','f','c',':','s','n',':','h','a','n','d','o','v','e','r'};
//const unsigned char LLCP_CONNECT_CH[] = {0x00,0x00};//小米9:0x41三星0x45
const unsigned char LLCP_CONNECT_CH[] = {0x05, 0x20,0x06,0x13,'u','r','n',':','n','f','c',':','s','n',':','h','a','n','d','o','v','e','r'};

unsigned char *pNdefMessage_SNEP;
unsigned short NdefMessage_SNEP_size = 0;

unsigned char *pNdefMessage_CH;
unsigned short NdefMessage_CH_size = 0;

/* Defines the number of symmetry exchanges is expected before initiating the NDEF push (to allow a remote phone to beam an NDEF message first) */
#define NDEF_PUSH_DELAY_COUNT    2

/* Defines at which frequency the symmetry is exchanged (in micro) */
#define SYMM_FREQ    500

#define LLCP_AGF_HEADER_SIZE 2

typedef enum
{
    Idle,
    Initial,
    DelayingPush,
    SnepClientConnecting,
    SnepClientConnected,
    NdefMsgSent,
	SdpRequesting,
	HandoverStartConnect,
	HandoverConnected,
} P2P_SnepClient_state_t;

typedef struct
{
    unsigned char Dsap;
    unsigned char Pdu;
    unsigned char Ssap;
    unsigned char Version;
    unsigned short Miux;
    unsigned short Wks;
    unsigned char Lto;
    unsigned char Rw;
    unsigned char Sn[30];
} P2P_NDEF_LlcpHeader_t;

typedef void P2P_NDEF_Callback_t (unsigned char*, unsigned short);

static P2P_SnepClient_state_t eP2P_SnepClient_State = Initial;
static P2P_NDEF_Callback_t *pP2P_NDEF_PushCb = NULL;
static P2P_NDEF_Callback_t *pP2P_NDEF_PullCb = NULL;
static unsigned short P2P_SnepClient_DelayCount = NDEF_PUSH_DELAY_COUNT;

static void ParseLlcp(unsigned char *pBuf, unsigned short BufSize, P2P_NDEF_LlcpHeader_t *pLlcpHeader)
{
    uint8_t i = 2;

    pLlcpHeader->Dsap = pBuf[0] >> 2;
    pLlcpHeader->Pdu = ((pBuf[0] & 3) << 2) + (pBuf[1] >> 6);
    pLlcpHeader->Ssap = pBuf[1] & 0x3F;

	//UART_MESSAGE_1("ParseLlcp pLlcpHeader.Dsap = %d\n\r", pLlcpHeader->Dsap);
	//UART_MESSAGE_1("ParseLlcp pLlcpHeader.Pdu = %d\n\r", pLlcpHeader->Pdu);
	//UART_MESSAGE_1("ParseLlcp pLlcpHeader.Ssap = %d\n\r", pLlcpHeader->Ssap);
	//UART_MESSAGE_2("ParseLlcp i=%d BufSize=%d\n\r", i, BufSize);
    while(i<BufSize)
    {
        switch (pBuf[i])
        {
        case VERSION:
            pLlcpHeader->Version = pBuf[i+2];
            break;
        case MIUX:
            pLlcpHeader->Miux = (pBuf[i+2] << 8) + pBuf[i+3];
            break;
        case WKS:
            pLlcpHeader->Wks = (pBuf[i+2] << 8) + pBuf[i+3];
            break;
        case LTO:
            pLlcpHeader->Lto = pBuf[i+2];
            break;
        case RW:
            pLlcpHeader->Rw = pBuf[i+2];
            break;
        case SN:
            memcpy(pLlcpHeader->Sn, &pBuf[i+2], pBuf[i+1] < sizeof(pLlcpHeader->Sn) ? pBuf[i+1] : sizeof(pLlcpHeader->Sn));
            break;
        default:
            break;
        }
        i += pBuf[i+1]+2;
    }
}

static void FillLlcp(P2P_NDEF_LlcpHeader_t LlcpHeader, unsigned char *pBuf)
{
    pBuf[0] = (LlcpHeader.Ssap << 2) + ((LlcpHeader.Pdu >> 2) & 3);
    pBuf[1] = (LlcpHeader.Pdu << 6) + LlcpHeader.Dsap;
}

bool P2P_NDEF_SetMessage_SNEP(unsigned char *pMessage, unsigned short Message_size, void *pCb)
{
    if (Message_size <= P2P_NDEF_MAX_NDEF_MESSAGE_SIZE)
    {
    	pNdefMessage_SNEP = pMessage;
    	NdefMessage_SNEP_size = Message_size;
        //pP2P_NDEF_PushCb = (P2P_NDEF_Callback_t*) pCb;
        return true;
    }
    else
    {
    	NdefMessage_SNEP_size = 0;
        pP2P_NDEF_PushCb = NULL;
        return false;
    }
}

bool P2P_NDEF_SetMessage_CH(unsigned char *pMessage, unsigned short Message_size, void *pCb)
{
    if (Message_size <= P2P_NDEF_MAX_NDEF_MESSAGE_SIZE)
    {
    	pNdefMessage_CH = pMessage;
    	NdefMessage_CH_size = Message_size;
        //pP2P_NDEF_PushCb = (P2P_NDEF_Callback_t*) pCb;
        return true;
    }
    else
    {
    	NdefMessage_CH_size = 0;
    	pP2P_NDEF_PushCb = NULL;
        return false;
    }
}


void P2P_NDEF_RegisterPullCallback(void *pCb)
{
    pP2P_NDEF_PullCb = (P2P_NDEF_Callback_t*) pCb;
}

void P2P_NDEF_Reset_SNEP(void)
{
    if (NdefMessage_SNEP_size != 0)
    {
        eP2P_SnepClient_State = Initial;
    }
    else
    {
        eP2P_SnepClient_State = Idle;
    }
}

void P2P_NDEF_Reset_CH(void)
{
    if (NdefMessage_CH_size != 0)
    {
        eP2P_SnepClient_State = Initial;
    }
    else
    {
        eP2P_SnepClient_State = Idle;
    }
}

void P2P_NDEF_Next_SNEP(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *pRsp, unsigned short *pRsp_size)
{
    P2P_NDEF_LlcpHeader_t LlcpHeader;
    
    /* Initialize answer */
    *pRsp_size = 0;

    ParseLlcp(pCmd, Cmd_size, &LlcpHeader);

	//UART_MESSAGE_1("LlcpHeader.Pdu = %d\n\r", LlcpHeader.Pdu);
    switch (LlcpHeader.Pdu)
    {
    case CONNECT:
        /* Is connection from SNEP Client ? */
        if ((LlcpHeader.Dsap == SAP_SNEP) || (memcmp(LlcpHeader.Sn, "urn:nfc:sn:snep", 15) == 0))
        {
            /* Only accept the connection is application is registered for NDEF reception */
            if(pP2P_NDEF_PullCb != NULL)
            {
                LlcpHeader.Pdu = CC;
                FillLlcp(LlcpHeader, pRsp);
                *pRsp_size = 2;
            }
        }
        else
        {
            /* Refuse any other connection request */
            LlcpHeader.Pdu = DM;
            FillLlcp(LlcpHeader, pRsp);
            *pRsp_size = 2;
        }
        break;

    case I:
        /* Is SNEP PUT ? */
        if ((pCmd[3] == SNEP_VER10) && (pCmd[4] == SNEP_PUT))
        {
            /* Notify application of the NDEF reception */
        	/*  */
            if(pP2P_NDEF_PullCb != NULL) pP2P_NDEF_PullCb(&pCmd[9], pCmd[8]);

            /* Acknowledge the PUT request */
            LlcpHeader.Pdu = I;
            FillLlcp(LlcpHeader, pRsp);
            pRsp[2] = (pCmd[2] >> 4) + 1; // N(R)
            memcpy(&pRsp[3], SNEP_PUT_SUCCESS, sizeof(SNEP_PUT_SUCCESS));
            *pRsp_size = 9;
        }
        else if((pCmd[3] == SNEP_VER10) && (pCmd[4] == SNEP_SUCCESS))
        {
        	 /* SNEP响应成功 */
        	*pRsp_size = LLCP_SNEP_ACK_OK;
        }
        break;

    case CC:
        /* Connection to remote SNEP server completed, send NDEF message inside SNEP PUT request */
        eP2P_SnepClient_State = SnepClientConnected;

        break;
    case RR:
		memcpy(pRsp, LLCP_SYMM, sizeof(LLCP_SYMM));
		*pRsp_size = sizeof(LLCP_SYMM);

		break;

	/* 去激活LLC链路 */
	case DISC:
		*pRsp_size = LLCP_DISC_ACK_OK;

		break;

	/* 连接被拒绝 */
	case DM:
		*pRsp_size = LLCP_DM_ACK_OK;
		break;

	/* 收到LLC PDU错误的消息 */
	case FRMR:
		*pRsp_size = LLCP_DM_ACK_OK;
		break;
    default:
        break;

    }

    /* No answer was set */
    if (*pRsp_size == 0)
    {
        switch(eP2P_SnepClient_State)
        {
        case Initial:
            if((pP2P_NDEF_PullCb == NULL) || (NDEF_PUSH_DELAY_COUNT == 0))
            {
                memcpy(pRsp, LLCP_CONNECT_SNEP, sizeof(LLCP_CONNECT_SNEP));
                *pRsp_size = sizeof(LLCP_CONNECT_SNEP);
                eP2P_SnepClient_State = SnepClientConnecting;
            }
            else
            {
                P2P_SnepClient_DelayCount = 1;
                eP2P_SnepClient_State = DelayingPush;
                /* Wait then send a SYMM */
                hal_Sleep(SYMM_FREQ*TIMEOUT_1MS);
                memcpy(pRsp, LLCP_SYMM, sizeof(LLCP_SYMM));
                *pRsp_size = sizeof(LLCP_SYMM);
            }
            break;

        case DelayingPush:
            if(P2P_SnepClient_DelayCount == NDEF_PUSH_DELAY_COUNT)
            {
                memcpy(pRsp, LLCP_CONNECT_SNEP, sizeof(LLCP_CONNECT_SNEP));
                *pRsp_size = sizeof(LLCP_CONNECT_SNEP);
                eP2P_SnepClient_State = SnepClientConnecting;
            }
            else
            {
                P2P_SnepClient_DelayCount++;
                /* Wait then send a SYMM */
                //hal_Sleep(1000*TIMEOUT_1MS);
                hal_Sleep(SYMM_FREQ*TIMEOUT_1MS);
                memcpy(pRsp, LLCP_SYMM, sizeof(LLCP_SYMM));
                *pRsp_size = sizeof(LLCP_SYMM);
            }
            break;

        case SnepClientConnected:
            LlcpHeader.Pdu = I;
            FillLlcp(LlcpHeader, pRsp);
            pRsp[2] = 0x00; // N(S)=0,N(R)=0
            /* LLCP层的SDU对应SNEP层的PDU */
            pRsp[3] = SNEP_VER10;
            pRsp[4] = SNEP_PUT;
            /* 4字节的负载长度 */
            pRsp[5] = 0;
            pRsp[6] = 0;
            pRsp[7] = 0;
            pRsp[8] = (unsigned char) NdefMessage_SNEP_size;
            memcpy(&pRsp[9], pNdefMessage_SNEP, NdefMessage_SNEP_size);
            *pRsp_size = 9 + NdefMessage_SNEP_size;
            eP2P_SnepClient_State = NdefMsgSent;

            /* Notify application of the NDEF push */
            //if(pP2P_NDEF_PushCb != NULL) pP2P_NDEF_PushCb(pNdefMessage, NdefMessage_size);
            break;

        default:
            /* Wait then send a SYMM */
            hal_Sleep(SYMM_FREQ*TIMEOUT_1MS);
            memcpy(pRsp, LLCP_SYMM, sizeof(LLCP_SYMM));
            *pRsp_size = sizeof(LLCP_SYMM);
            break;
        }
    }
}

void P2P_NDEF_Next_CH(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *pRsp, unsigned short *pRsp_size)
{
    P2P_NDEF_LlcpHeader_t LlcpHeader;
    uint8_t LlcpHeader_agf_pdu;
	uint8_t length_agf = 0;
	uint8_t flag_foundSNL = 0;
	uint8_t flag_foundCH = 0;

    /* Initialize answer */
    *pRsp_size = 0;

    ParseLlcp(pCmd, Cmd_size, &LlcpHeader);

	//UART_MESSAGE_1("LlcpHeader.Pdu = %d\n\r", LlcpHeader.Pdu);
    switch (LlcpHeader.Pdu)
    {
    case CONNECT:
        /* Is connection from SNEP Client ? */
        if ((LlcpHeader.Dsap == SAP_SNEP) || (memcmp(LlcpHeader.Sn, "urn:nfc:sn:snep", 15) == 0))
        {
            /* Only accept the connection is application is registered for NDEF reception */
            if(pP2P_NDEF_PullCb != NULL)
            {
                LlcpHeader.Pdu = CC;
                FillLlcp(LlcpHeader, pRsp);
                *pRsp_size = 2;
            }
        }
        else
        {
            /* Refuse any other connection request */
            LlcpHeader.Pdu = DM;
            FillLlcp(LlcpHeader, pRsp);
            *pRsp_size = 2;
        }
        break;

    case I:
        /* Is SNEP PUT ? */
        if ((pCmd[3] == SNEP_VER10) && (pCmd[4] == SNEP_PUT))
        {
            /* Notify application of the NDEF reception */
        	/*  */
            if(pP2P_NDEF_PullCb != NULL) pP2P_NDEF_PullCb(&pCmd[9], pCmd[8]);

            /* Acknowledge the PUT request */
            LlcpHeader.Pdu = I;
            FillLlcp(LlcpHeader, pRsp);
            pRsp[2] = (pCmd[2] >> 4) + 1; // N(R)
            memcpy(&pRsp[3], SNEP_PUT_SUCCESS, sizeof(SNEP_PUT_SUCCESS));
            *pRsp_size = 9;
        }
        else if((pCmd[3] == SNEP_VER10) && (pCmd[4] == SNEP_SUCCESS))
        {
        	 /* SNEP响应成功 */
        	*pRsp_size = LLCP_SNEP_ACK_OK;
        }

        if((pCmd[6] == 'H') || (pCmd[7] == 's'))
		{
			*pRsp_size = LLCP_CH_ACK_OK;
			/*
			LlcpHeader.Pdu = RR;//
			FillLlcp(LlcpHeader, pRsp);
			pRsp[2] = 0x01; // ,N(R)=1
			*pRsp_size = 3;*/

			/* 进行SNEP的连接 */
			//eP2P_SnepClient_State = SnepClientConnected;//InitiatePush
		}

        break;

    case CC:

        eP2P_SnepClient_State = HandoverConnected;

        break;

    case RR:
		memcpy(pRsp, LLCP_SYMM, sizeof(LLCP_SYMM));
		*pRsp_size = sizeof(LLCP_SYMM);

		break;

	/* 去激活LLC链路 */
	case DISC:
		*pRsp_size = LLCP_DISC_ACK_OK;

		break;

	/* 连接被拒绝 */
	case DM:
		*pRsp_size = LLCP_DM_ACK_OK;
		break;

	/* 收到LLC PDU错误的消息 */
	case FRMR:
		*pRsp_size = LLCP_DM_ACK_OK;
		break;

	case SNL:
		/* 是否为SDRES */
		if(pCmd[2] == 0x09)
		{
			if(pCmd[3] == 0x02)
			{
				memcpy(pRsp, LLCP_CONNECT_CH, sizeof(LLCP_CONNECT_CH));
				LlcpHeader.Pdu = CONNECT;
				LlcpHeader.Dsap = 0x20;
				LlcpHeader.Ssap = pCmd[5] & 0x3f;//0x11
				FillLlcp(LlcpHeader, pRsp);
				*pRsp_size = sizeof(LLCP_CONNECT_CH);

				eP2P_SnepClient_State = HandoverStartConnect;
			}
		}

		break;

	case AGF:
		/* 目前只接收长度小于255的消息 */
		/* LLC PDU本身的2字节长度+负载长度 */
		length_agf = pCmd[3] + 2;

		LlcpHeader_agf_pdu = ((pCmd[4] & 3) << 2) + (pCmd[5] >> 6);

		while(length_agf+LLCP_AGF_HEADER_SIZE <= Cmd_size)
		{
			if(LlcpHeader_agf_pdu == SNL)
			{
				flag_foundSNL = 1;
				break;
			}

			if(LlcpHeader_agf_pdu == I)
			{
				flag_foundCH = 1;
				break;
			}

			LlcpHeader_agf_pdu = ((pCmd[4+ length_agf] & 3) << 2) + (pCmd[5+ length_agf] >> 6);

			/* 下一个PDU的负载长度 */
			length_agf += pCmd[3 + length_agf];
			/* 本身的字节长度 */
			length_agf += 2;
		}

		if(flag_foundSNL == 1)
		{
			flag_foundSNL = 0;

			/* type 是不是sdres；总长度为2+length_agf */
			if(pCmd[2+length_agf-4 ] == 0x09)
			{
				memcpy(pRsp, LLCP_CONNECT_CH, sizeof(LLCP_CONNECT_CH));
				LlcpHeader.Pdu = CONNECT;
				/* 远端节点的DSAP为0x20，元旦节点的SSAP为本地注册的handover服务 */
				LlcpHeader.Dsap = 0x20;
				LlcpHeader.Ssap = pCmd[2+length_agf-1] & 0x3f;
				/* 利用远端节点的dsap和ssap */
				FillLlcp(LlcpHeader, pRsp);
				*pRsp_size = sizeof(LLCP_CONNECT_CH);

				eP2P_SnepClient_State = HandoverStartConnect;
			}
		}

		if(flag_foundCH == 1)
		{
			flag_foundCH = 0;

			/*  */
			if((pCmd[3 + 21+7] == 'H') || (pCmd[3 + 21+8] == 's'))
			{
				*pRsp_size = LLCP_CH_ACK_OK;
			}

		}

		break;
    default:
        break;

    }

    /* No answer was set */
    if (*pRsp_size == 0)
    {
        switch(eP2P_SnepClient_State)
        {
        case Initial:
            if((pP2P_NDEF_PullCb == NULL) || (NDEF_PUSH_DELAY_COUNT == 0))
            {
                memcpy(pRsp, LLCP_SNL, sizeof(LLCP_SNL));
                *pRsp_size = sizeof(LLCP_SNL);

                //memcpy(pRsp, LLCP_CONNECT_CH, sizeof(LLCP_CONNECT_CH));
                //*pRsp_size = sizeof(LLCP_CONNECT_CH);
                eP2P_SnepClient_State = SdpRequesting;
            }
            else
            {
                P2P_SnepClient_DelayCount = 1;
                eP2P_SnepClient_State = DelayingPush;
                /* Wait then send a SYMM */
                hal_Sleep(SYMM_FREQ*TIMEOUT_1MS);
                memcpy(pRsp, LLCP_SYMM, sizeof(LLCP_SYMM));
                *pRsp_size = sizeof(LLCP_SYMM);
            }
            break;

        case DelayingPush:
            if(P2P_SnepClient_DelayCount == NDEF_PUSH_DELAY_COUNT)
            {
                memcpy(pRsp, LLCP_SNL, sizeof(LLCP_SNL));
                *pRsp_size = sizeof(LLCP_SNL);

                //memcpy(pRsp, LLCP_CONNECT_CH, sizeof(LLCP_CONNECT_CH));
				//*pRsp_size = sizeof(LLCP_CONNECT_CH);
                eP2P_SnepClient_State = SdpRequesting;
            }
            else
            {
                P2P_SnepClient_DelayCount++;
                /* Wait then send a SYMM */
                //hal_Sleep(1000*TIMEOUT_1MS);
                hal_Sleep(SYMM_FREQ*TIMEOUT_1MS);
                memcpy(pRsp, LLCP_SYMM, sizeof(LLCP_SYMM));
                *pRsp_size = sizeof(LLCP_SYMM);
            }
            break;

        case HandoverConnected:
            LlcpHeader.Pdu = I;
            FillLlcp(LlcpHeader, pRsp);
            pRsp[2] = 0x00; // N(S)=0,N(R)=0
            memcpy(&pRsp[3], pNdefMessage_CH, NdefMessage_CH_size);
            *pRsp_size = 3 + NdefMessage_CH_size;
            eP2P_SnepClient_State = NdefMsgSent;

            /* Notify application of the NDEF push */
            //if(pP2P_NDEF_PushCb != NULL) pP2P_NDEF_PushCb(pNdefMessage, NdefMessage_size);
            break;

        default:
            /* Wait then send a SYMM */
            hal_Sleep(SYMM_FREQ*TIMEOUT_1MS);
            memcpy(pRsp, LLCP_SYMM, sizeof(LLCP_SYMM));
            *pRsp_size = sizeof(LLCP_SYMM);
            break;
        }
    }
}

#endif
