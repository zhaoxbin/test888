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

#include <Nfc.h>

#define NxpNci_Disconnect() hal_NFCC_Reset();
#ifdef CARDEMU_SUPPORT
#include <T4T_NDEF_emu.h>
#endif

#ifdef P2P_SUPPORT
#include <P2P_NDEF.h>
#endif

#ifdef RW_SUPPORT
#include "RW_NDEF.h"
#include "RW_NDEF_T1T.h"
#include "RW_NDEF_T2T.h"
#include "RW_NDEF_T3T.h"
#include "RW_NDEF_T4T.h"
#endif

#define NFC_P2P_MAX_RETRY_60s (10)
#define NFC_RW_MAX_RETRY_500ms (5)
#define MAX_OOB_DATALENGTH	(80)

/*
typedef enum
{
	NxpNci_P2P_Results_None = 0,
	NxpNci_P2P_Results_SNEPACKOK,
	NxpNci_P2P_Results_NOTDATAPACKET,
	NxpNci_P2P_Results_LLCPDEACTIVE,
	NxpNci_P2P_Results_LLCPREFUSED,
	NxpNci_P2P_Results_HSACKOK,
	NxpNci_P2P_Results_COUNTOVER,
}NxpNci_P2P_Results;
*/

extern uint8_t gOOBData_From_MobileDevice[MAX_OOB_DATALENGTH];
extern int gOOBData_len;
extern int NFC_Get_OOBDataLen(void);
