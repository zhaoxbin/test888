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

typedef enum
{
	RW_NDEF_T4T_OPERATION_NONE = 0,
	RW_NDEF_T4T_FAULT_OVERSIZE = 10000,
	RW_NDEF_T4T_READ_FINSH = 10001
}RW_NDEF_T4T_OPERATION_TYPE;

void RW_NDEF_T4T_Reset(void);
void RW_NDEF_T4T_Read_Next(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *Rsp, unsigned short *pRsp_size);
void RW_NDEF_T4T_Write_Next(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *Rsp, unsigned short *pRsp_size);
int RW_NDEF_T4T_Get_KeyLen(void);
