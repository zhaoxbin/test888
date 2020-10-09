#include <hal.h>
#include <Nfc.h>

typedef void (*NioWlc_Raw_P2p_Cb)(uint32_t status, char* msg, uint32_t len);

uint32_t NioWlc_nfc_set_raw_p2p_msg(char *msg, uint32_t len);/*need callback*/
uint32_t NioWlc_nfc_start_raw_p2p(NioWlc_Raw_P2p_Cb cb);
uint32_t NioWlc_nfc_stop_raw_p2p(void);

void P2P_RAW_Next(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *pRsp, unsigned short *pRsp_size);
