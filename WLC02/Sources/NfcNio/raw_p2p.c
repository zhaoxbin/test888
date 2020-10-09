#include <hal.h>
#include <Nfc.h>
#include <raw_p2p.h>

static NioWlc_Raw_P2p_Cb p2p_cb;

//#define DEBUG_DELAY_TICK	1

#ifdef DEBUG_DELAY_TICK
#define ARM_CM_DWT_CYCCNT (*(uint32_t *)0xE0001004)
#endif

#define MAX_NCI_FRAME_SIZE    256
#define MAX_P2P_MSG_SIZE (MAX_NCI_FRAME_SIZE - 3)
static char raw_msg_send[MAX_P2P_MSG_SIZE] = "This is a test";
static uint32_t raw_msg_send_len = 0;

char raw_msg_get[MAX_P2P_MSG_SIZE];
uint32_t raw_msg_get_len = 0;

static uint32_t NioWlc_nfc_raw_p2p_callback(void)
{
	if (p2p_cb != NULL)
	{
		p2p_cb(1, raw_msg_get, raw_msg_get_len);

		return NXPNCI_SUCCESS;
	}

	return NXPNCI_ERROR;
}

static bool NxpNci_set_p2p_msg(char *msg, unsigned int len)
{
	if(msg != NULL && len < MAX_P2P_MSG_SIZE){
		raw_msg_send_len = len;
		memcpy(raw_msg_send, msg, len);
		return NXPNCI_SUCCESS;
	}
	return NXPNCI_ERROR;
}

uint32_t NioWlc_nfc_set_raw_p2p_msg(char *msg, uint32_t len)
{
#ifdef DEBUG_DELAY_TICK
	uint32_t tick_out = 0;
	uint32_t tick_in = ARM_CM_DWT_CYCCNT;
#endif

	uint32_t ret = NxpNci_set_p2p_msg(msg, len);

#ifdef DEBUG_DELAY_TICK
	tick_out = ARM_CM_DWT_CYCCNT;
	UART_MESSAGE_1("\NioWlc_nfc_set_raw_p2p_msg, run cycle=%d\n\r", tick_out-tick_in);
#endif
	return ret;
}

uint32_t NioWlc_nfc_start_raw_p2p(NioWlc_Raw_P2p_Cb cb)
{
#ifdef DEBUG_DELAY_TICK
	uint32_t tick_out = 0;
	uint32_t tick_in = ARM_CM_DWT_CYCCNT;
#endif

	p2p_cb = cb;

#ifdef DEBUG_DELAY_TICK
	tick_out = ARM_CM_DWT_CYCCNT;
	UART_MESSAGE_1("\NioWlc_nfc_start_raw_p2p, run cycle=%d\n\r", tick_out-tick_in);
#endif

	return 0;
}
uint32_t NioWlc_nfc_stop_raw_p2p(void)
{
	return 0;
}

void P2P_RAW_Next(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *pRsp, unsigned short *pRsp_size)
{
	memcpy(pRsp, pCmd, Cmd_size);
	pRsp[Cmd_size] = '\0';
	UART_MESSAGE_1STR("received: %s\n\r", pRsp);
	strcpy(raw_msg_get, (char *)pRsp);
	raw_msg_get_len = strlen(raw_msg_get);
	NioWlc_nfc_raw_p2p_callback();

	memcpy(pRsp, raw_msg_send, raw_msg_send_len);
	*pRsp_size = raw_msg_send_len;
}

