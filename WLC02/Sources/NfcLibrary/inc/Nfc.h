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
#ifndef NFC_H
#define NFC_H
#include "stdbool.h"
/***** NFC dedicated interface ****************************************/

/*
 * Status code definition used as API returned values
 */
#define NFC_SUCCESS          0
#define NFC_ERROR            1

/*
 * Flag definition used as Interface values
 */
#define INTF_UNDETERMINED    0x0
#define INTF_FRAME           0x1
#define INTF_ISODEP          0x2
#define INTF_NFCDEP          0x3
#define INTF_TAGCMD          0x80

/*
 * Flag definition used as Protocol values
 */
#define PROT_UNDETERMINED    0x0
#define PROT_T1T             0x1
#define PROT_T2T             0x2
#define PROT_T3T             0x3
#define PROT_ISODEP          0x4
#define PROT_NFCDEP          0x5
#define PROT_ISO15693        0x6
#define PROT_MIFARE          0x80

/*
 * Flag definition used as Mode values
 */
#define MODE_POLL            0x00
#define MODE_LISTEN          0x80
#define MODE_MASK            0xF0

/*
 * Flag definition used as Technologies values
 */
#define TECH_PASSIVE_NFCA    0
#define TECH_PASSIVE_NFCB    1
#define TECH_PASSIVE_NFCF    2
#define TECH_ACTIVE_NFCA     3
#define TECH_ACTIVE_NFCF     5
#define TECH_PASSIVE_15693   6

/*
 * Flag definition used for NFC library configuration
 */
#define NXPNCI_MODE_CARDEMU    (1<<0)
#define NXPNCI_MODE_P2P        (1<<1)
#define NXPNCI_MODE_RW         (1<<2)

/*
 * Definition of operations handled when processing Reader mode
 */
typedef enum
{
    READ_NDEF,
    WRITE_NDEF,
    PRESENCE_CHECK
} NxpNci_RW_Operation_t;

/*
 * Definition of discovered remote device properties information
 */
/* POLL passive type A */
typedef struct
{
    unsigned char SensRes[2];
    unsigned char NfcIdLen;
    unsigned char NfcId[10];
    unsigned char SelResLen;
    unsigned char SelRes[1];
} NxpNci_RfIntf_info_APP_t;

/* POLL passive type B */
typedef struct
{
    unsigned char SensResLen;
    unsigned char SensRes[12];
} NxpNci_RfIntf_info_BPP_t;

/* POLL passive type F */
typedef struct
{
    unsigned char BitRate;
    unsigned char SensResLen;
    unsigned char SensRes[18];
} NxpNci_RfIntf_info_FPP_t;

/* POLL passive type ISO15693 */
typedef struct
{
    unsigned char AFI;
    unsigned char DSFID;
    unsigned char ID[8];
} NxpNci_RfIntf_info_VPP_t;

typedef union
{
    NxpNci_RfIntf_info_APP_t NFC_APP;
    NxpNci_RfIntf_info_BPP_t NFC_BPP;
    NxpNci_RfIntf_info_FPP_t NFC_FPP;
    NxpNci_RfIntf_info_VPP_t NFC_VPP;
} NxpNci_RfIntf_Info_t;

/*
 * Definition of discovered remote device properties
 */
typedef struct
{
    unsigned char Interface;
    unsigned char Protocol;
    unsigned char ModeTech;
    bool MoreTags;
    NxpNci_RfIntf_Info_t Info;
} NxpNci_RfIntf_t;

typedef enum
{
	StopDiscovery_last_none = 0,
	StopDiscovery_last_ok

}NFC_STOPDISCOVERY_PARAS;

/*
 * Definition of P2P Types(Nio Fury)
 */
typedef enum
{
	NFC_P2PMode_BT_WithOOB = 0,
	NFC_P2PMode_BT_WithoutOOB,
	NFC_P2PMode_WIFI_WithoutOOB,

}NFC_P2PMode;

/*
 * Definition of results of P2P_Next Types
 */
typedef enum
{
	NxpNci_P2P_Results_None = 0,
	NxpNci_P2P_Results_WithoutOOB_OK,
	NxpNci_P2P_Results_NOTDATAPACKET,
	NxpNci_P2P_Results_LLCPDEACTIVE,
	NxpNci_P2P_Results_LLCPREFUSED,
	NxpNci_P2P_Results_WithOOB_OK,
	NxpNci_P2P_Results_HS_OOBDATA_OVERSIZE,
	NxpNci_P2P_Results_COUNTOVER,
	NfcTask_P2P_Results_InvalidPara,
	NfcTask_P2P_Results_NfcMode_Fail,
	NfcTask_P2P_Results_PairingMode_Fail,
	NfcTask_P2P_Results_SetMessage_Fail,
	NfcTask_P2P_Results_NciConnet_Fail,
	NfcTask_P2P_Results_NciConfigureSet_Fail,
	NfcTask_P2P_Results_NciConfigureMode_Fail,
	NfcTask_P2P_Results_NciDiscovery_Fail,
	NfcTask_P2P_Results_NotFoundEndpoint,
	NfcTask_P2P_Results_Interface_Fail,
	NFC_P2P_Results_InternalError,
	NFC_P2P_Results_DisableOK,
	NFC_P2P_Results_BT_WithoutOOB_OK,
	NFC_P2P_Results_BT_Pairing_Failed,
	NFC_P2P_Results_BT_Connection_Failed,
	NFC_P2P_Results_BT_Detection_Failed,
	NFC_P2P_Results_WIFI_WithoutOOB_OK,
	NFC_P2P_Results_WIFI_Pairing_Failed,
	NFC_P2P_Results_WIFI_Connection_Failed,
	NFC_P2P_Results_WIFI_Detection_Failed,
}NxpNci_P2P_Results;


/*
 * Definition of results of NDEF Types
 */
typedef enum
{
	NxpNci_RW_NDEF_Results_None = 0,
	NxpNci_READNDEF_Results_NotOK,
	NxpNci_READNDEF_Results_NotEnoughBuffer,
	NxpNci_READNDEF_Results_Finished,
	NxpNci_READNDEF_Results_DisableOK,


	NFC_Task_IMMO_APDU_Results_IMMOTypeWrong,
	NFC_Task_IMMO_APDU_Results_ReaderTag_Fail,
	NFC_Task_IMMO_APDU_Results_SelectAID_Fail,
	NFC_Task_IMMO_APDU_Results_ReadCarKey_Fail,
	NFC_Task_IMMO_APDU_Results_NotEnoughBuffer,
	NFC_Task_IMMO_APDU_Results_ReadCarKey_OK,
	NFC_Task_IMMO_APDU_Results_DisableOK,

	NfcTask_IMMO_Results_NciConnet_Fail,
	NfcTask_IMMO_Results_NciDiscovery_Fail,
	NfcTask_IMMO_Results_NotFoundEndpoint,
	NfcTask_IMMO_Results_NFCTypeWrong,
	NfcTask_IMMO_Results_InternalError,


}NxpNci_RW_NDEF_Results;

/**********************************************************************/


/***** NFC dedicated API **********************************************/

/*
 * Open connection to the NXP-NCI device
 * return NFC_SUCCESS or NFC_ERROR
 */
bool NxpNci_Connect(void);

/*
 * Close connection to the NXP-NCI device
 * return NFC_SUCCESS or NFC_ERROR
 */
bool NxpNci_Disconnect(void);

/*
 * Configure NXP-NCI device settings
 * Related settings are defined in Nfc_settings.h header file
 * To be called after NxpNci_Connect() and prior to NxpNci_ConfigureMode() APIs
 * return NFC_SUCCESS or NFC_ERROR
 */
bool NxpNci_ConfigureSettings(void);

/*
 * Configure NXP-NCI device mode
 * - mode: specifies which modes to be configured (see NXPNCI_MODE_xxx flags)
 * return NFC_SUCCESS or NFC_ERROR
 */
bool NxpNci_ConfigureMode(unsigned char mode);

/*
 * Start NFC Discovery loop for remote NFC device detection
 * - pTechTab: list of NFC technologies to look for (see TECH_xxx_xxx flags)
 * \param TechTabSize: number of items in the list
 * return NFC_SUCCESS or NFC_ERROR
 */
bool NxpNci_StartDiscovery(const unsigned char *pTechTab, unsigned char TechTabSize);

/*
 * Stop NFC Discovery loop
 * return NFC_SUCCESS or NFC_ERROR
 */
bool NxpNci_StopDiscovery(unsigned char last_discovery_result);

/*
 * Wait until remote NFC device is discovered
 * - pRfIntf: filled with discovered NFC remote device properties
 * return NFC_SUCCESS or NFC_ERROR
 */
bool NxpNci_WaitForDiscoveryNotification(NxpNci_RfIntf_t *pRfIntf, unsigned int mode);

/**********************************************************************/


/***** Card Emulation dedicated APIs **********************************/
#ifdef CARDEMU_SUPPORT
#ifndef NO_NDEF_SUPPORT
/*
 * Register NDEF message to be exposed to remote NFC reader Device
 * - pMessage: pointer to the NDEF message
 * - Message_size: NDEF message size
 * - pCb: pointer to function to be called back when tag has been written
 * return NFC_SUCCESS or NFC_ERROR
 */
bool T4T_NDEF_EMU_SetMessage(unsigned char *pMessage, unsigned short Message_size, void *pCb);
#endif

/*
 * Expose the previously registered NDEF message to discovered remote NFC reader (function is blocking until the remote reader is lost):
 * - RfIntf: discovered NFC device properties
  */
void NxpNci_ProcessCardMode(NxpNci_RfIntf_t RfIntf);

/*
 * Perform RAW reception of data from the remote reader
 * - pData: pointer to buffer for getting the data
 * - pDataSize: received data size
 * return NFC_SUCCESS or NFC_ERROR
 */
bool NxpNci_CardModeReceive (unsigned char *pData, unsigned char *pDataSize);

/*
 * Perform RAW transmission of data from the remote reader
 * - pData: pointer to data to transmit
 * - DataSize: size of data to transmit
 * return NFC_SUCCESS or NFC_ERROR
 */
bool NxpNci_CardModeSend (unsigned char *pData, unsigned char DataSize);
#endif
/**********************************************************************/


/***** P2P dedicated APIs *********************************************/
#ifdef P2P_SUPPORT
//#define P2P_RAW
#include <raw_p2p.h>
/*
 * Register NDEF message to be sent to remote NFC Peer to peer Device
 * - pMessage: pointer to the NDEF message
 * - Message_size: NDEF message size
 * - pCb: pointer to function to be called back when tag has been sent
 * return NFC_SUCCESS or NFC_ERROR
 */
bool P2P_NDEF_SetMessage_SNEP(unsigned char *pMessage, unsigned short Message_size, void *pCb);

bool P2P_NDEF_SetMessage_CH(unsigned char *pMessage, unsigned short Message_size, void *pCb);
/*
 * Register function called when NDEF message is received from remote NFC Peer to peer Device
 * - pCb: pointer to function to be called back when NDEF message has been received
 */
void P2P_NDEF_RegisterPullCallback(void *pCb);

/* Process P2P operation (function is blocking until the remote peer is lost):
 *  ¤ SNEP server to allow receiving NDEF message from remote NFC P2P device
 *  ¤ SNEP client to send previously registered NDEF message
 * - RfIntf: discovered NFC device properties
 */
NxpNci_P2P_Results NxpNci_ProcessP2pMode(NxpNci_RfIntf_t RfIntf,NFC_P2PMode p2p_mode);
#endif
/**********************************************************************/

/***** IMMO dedicated APIs *********************************************/
bool NxpNci_ReaderTagCmd (unsigned char *pCommand, unsigned char CommandSize, unsigned char *pAnswer, unsigned int *pAnswerSize);
NxpNci_RW_NDEF_Results NxpNci_ProcessReaderMode(NxpNci_RfIntf_t RfIntf, NxpNci_RW_Operation_t Operation);
/**********************************************************************/

/***** LPCD dedicated APIs *********************************************/
bool NxpNci_Lpcd_SampleAgc(uint16_t *agc_val);

#endif
