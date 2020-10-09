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


#include <hal.h>

#define P2P_NDEF_MAX_NDEF_MESSAGE_SIZE 240

/* LLCP链接的特殊反馈 */
#define LLCP_SNEP_ACK_OK (0xff)
#define LLCP_DISC_ACK_OK (0xfe)
#define LLCP_DM_ACK_OK 	 (0xfd)
#define LLCP_CH_ACK_OK 	 (0xfc)

void P2P_NDEF_Reset_SNEP(void);
void P2P_NDEF_Reset_CH(void);
void P2P_NDEF_Next_SNEP(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *Rsp, unsigned short *pRsp_size);
void P2P_NDEF_Next_CH(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *Rsp, unsigned short *pRsp_size);
