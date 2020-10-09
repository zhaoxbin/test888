/***********************************************
 *�ļ�����:nfc_task.h
 *����ͷ�ļ�:"Nfc.h"
 *��������:����NFC�Ĺ��ܺ���
 *��ע˵��:��
 *������:�Ա�
 *�����:
 *��������:2020-01-10
 **********************************************/

#ifndef NFC_TASK
#define NFC_TASK


/*****************��׼ͷ�ļ�**********************/


/*****************�Զ���ͷ�ļ�********************/
#include "Nfc.h"
#include "NxpNci.h"

/*****************�궨��************************/


/*****************���ݽṹ***********************/
/* NFC���߲���ʱʹ�� */
typedef enum
{
	DiscoveryResult_OpError = 0,
	DiscoveryResult_NotFound,
	DiscoveryResult_FoundTag,
	DiscoveryResult_NotIdentify
}NFC_TAG_DISCOVERY_RESULTS;


typedef enum
{
	NfcTask_Tag_Results_None = 0,
	NfcTask_Tag_Results_NciConnet_Fail,
	NfcTask_Tag_Results_NciDiscovery_Fail,
	NfcTask_Tag_Results_FoundTag,
	NfcTask_Tag_Results_NotFoundTag,
	NfcTask_Tag_Results_FoundTag_T1,
	NfcTask_Tag_Results_FoundTag_T2,
	NfcTask_Tag_Results_FoundTag_T3,
	NfcTask_Tag_Results_FoundTag_T4a,
	NfcTask_Tag_Results_FoundTag_T4b,
	NfcTask_Tag_Results_FoundTag_M1,
	NfcTask_Tag_Results_NotIdentify
}NxpNci_TAG_Results;


//P2P���ģʽ
typedef enum
{
	NFC_P2PMode_Pairing_BT_Enable = 0,
	NFC_P2PMode_Pairing_BT_Disable ,
	NFC_P2PMode_Pairing_WIFI_Enable,
	NFC_P2PMode_Pairing_WIFI_Disable
}NFC_P2P_PairingMode;
/*
typedef enum
{
	NFC_P2PMode_Pairing_BT = 0,
	NFC_P2PMode_Pairing_WIFI
}NFC_P2P_PairingMode;
*/

/* ����Nfc.h�� */
/*
typedef enum
{
	NxpNci_P2P_Results_None = 0,
	NxpNci_P2P_Results_SNEPACKOK,
	NxpNci_P2P_Results_NOTDATAPACKET,
	NxpNci_P2P_Results_LLCPDEACTIVE,
	NxpNci_P2P_Results_LLCPREFUSED,
	NxpNci_P2P_Results_HSACKOK,
	NxpNci_P2P_Results_HS_OOBDATA_OVERSIZE,
	NxpNci_P2P_Results_COUNTOVER,
	NfcTask_P2P_Results_NfcMode_Fail,
	NfcTask_P2P_Results_PairingMode_Fail,
	NfcTask_P2P_Results_SetMessage_Fail,
	NfcTask_P2P_Results_NciConnet_Fail,
	NfcTask_P2P_Results_NciConfigureSet_Fail,
	NfcTask_P2P_Results_NciConfigureMode_Fail,
	NfcTask_P2P_Results_NciDiscovery_Fail,
	NfcTask_P2P_Results_NotFoundEndpoint,
	NfcTask_P2P_Results_Interface_Fail,
}NxpNci_P2P_Results;


typedef enum
{
	NxpNci_RW_NDEF_Results_None = 0,
	NfcTask_IMMO_Results_NciConnet_Fail,
	NfcTask_IMMO_Results_NciDiscovery_Fail,
	NfcTask_IMMO_Results_NotFoundEndpoint,
	NfcTask_IMMO_Results_NFCTypeWrong,
	NfcTask_IMMO_Results_ReadNDEF_OK,
	NfcTask_IMMO_Results_ReadNDEF_Fail
}NxpNci_RW_NDEF_Results;
*/

//IMMO����Է�ʽ
typedef enum
{
	NFC_Task_IMMO_Type_EnableAID1 = 0,
	NFC_Task_IMMO_Type_EnableAID2,
	NFC_Task_IMMO_Type_Disable
}NFC_Task_IMMO_Type;

/*
typedef enum
{
	NFC_Task_IMMO_Type_AID1 = 0,
	NFC_Task_IMMO_Type_AID2
}NFC_Task_IMMO_Type;
*/

typedef enum
{
	NxpNci_LPCD_Cail_Results_None = 0,
	NxpNci_LPCD_Cail_Results_InvalidPara,
	NxpNci_LPCD_Cail_Results_ConnectFail,
	NxpNci_LPCD_Cail_Results_Success,
	NxpNci_LPCD_Cail_Results_Fail
}NxpNci_LPCD_Cail_Results;


typedef enum
{
	NxpNci_LPCD_Detect_Results_None = 0,
	NxpNci_LPCD_Detect_Results_InvalidPara,
	NxpNci_LPCD_Detect_Results_FoundObject,
	NxpNci_LPCD_Detect_Results_NotFoundObject,
	NxpNci_LPCD_Detect_Results_NotFinish,
	NxpNci_LPCD_Detect_Results_Error
}NxpNci_LPCD_Detect_Results;

//EMC����Է�ʽ
typedef enum
{
	NFC_Task_EMC_Mode_EnablePing = 0,
	NFC_Task_EMC_Mode_EnableCommunication,
	NFC_Task_EMC_Mode_DisablePing,
	NFC_Task_EMC_Mode_DisableCommunication
}NFC_Task_EMC_Mode;

//EMC����Է�ʽ
typedef enum
{
	NFC_Task_EMC_Results_None = 0,
	NFC_Task_EMC_Results_Succeed,
	NFC_Task_EMC_Results_Failed
}NFC_Task_EMC_Results;


/*****************ȫ�ֱ���***********************/
extern uint8_t gImmo_Data[2200];
extern uint16_t gLPCD_CailValue;
#ifdef LPCD_TEST
extern uint8_t ZB_LPCD_TEST[8];
#endif
extern int Immo_DataIndex;

/*****************��������***********************/
/*********************************************
�������ƣ�NFC_Task_Tag
����������NFC�Ŀ�ʶ������
�����������
���������NxpNci_TAG_Results����ʶ��ִ�еĽ��
������������
**********************************************/
extern NxpNci_TAG_Results NFC_Task_Tag(void);


/*********************************************
�������ƣ�NFC_Task_P2P
����������NFC��P2P����
���������mode[in]��P2P���ģʽ
      pair_data[in]������ԵĲ�����Ϣ���磺����MAC��ַ��WIFI��SSID����Ϣ��
      len[in]:������ݵĳ���
���������NxpNci_P2P_Results��P2P��Խ��
�����������������ݵĽṹ��Ϊstruct bt_info
      wifi���ݵĽṹ��Ϊwifi_info
	       ��������ԣ��ҷ���ֵΪNxpNci_P2P_Results_HSACKOKʱ����Ҫ��ȡgOOBData_From_MobileDevice������
**********************************************/
extern NxpNci_P2P_Results NFC_Task_P2P(NFC_P2P_PairingMode mode,void *pair_data,int len);


/*********************************************
�������ƣ�NFC_Task_IMM0
����������NFC��IMMO����
���������immo_type[in]:immo�����
	    �� Time_CGW[in]��CGW��ʱ��
	   �� Time_CGW_Len[in]��CGW��ʱ�������
	    ��gImmo_Data[out]��immo�����󷵻ص�����
���������NxpNci_RW_NDEF_Results��IMMOִ�еĽ��
���������������ؽ��ΪNfcTask_IMMO_Results_ReadNDEF_OK�����ȡNdefBuffer_IMMO������
*********************************************/
extern int Get_ImmoDataLen(void);
extern NxpNci_RW_NDEF_Results NFC_Task_IMM0(NFC_Task_IMMO_Type immo_type,unsigned char *Current_Time_CGW,uint8_t Time_CGW_Len);


/*********************************************
�������ƣ�NFC_Task_LPCD_Cail
����������NFC��LPCDУ׼����
���������cail_agc_val[out]����ȡ����У׼ֵ
���������NxpNci_LPCD_Cail_Results��LPCDУ׼ִ�еĽ��
������������LPCDִ�гɹ���ʱ����Ҫ��ȡУ׼ֵ
*********************************************/
extern NxpNci_LPCD_Cail_Results NFC_Task_LPCD_Cail(uint16_t *cail_agc_val);


/*********************************************
�������ƣ�NFC_Task_LPCD_Detect
����������NFC��LPCD�������
���������campare_agc_val[in]�����Ƚϵ�agcֵ
���������NxpNci_LPCD_Detect_Results��LPCD���ִ�еĽ��
������������
*********************************************/
extern NxpNci_LPCD_Detect_Results NFC_Task_LPCD_Detect(uint16_t *campare_agc_val);

/* NFC���߲���ʱʹ�� */
extern uint32_t NFC_Tag_init(void);
extern uint32_t NFC_Tag_Discovery(void);


/*********************************************
�������ƣ�NFC_Task_EMCTest
����������NFC��EMC��������
���������Emc_NFC_mode[in]��EMC��NFC����ģʽ
���������NFC_Task_EMC_Results:�������Խ��
������������
*********************************************/
extern NFC_Task_EMC_Results NFC_Task_EMCTest(NFC_Task_EMC_Mode Emc_NFC_mode);

#endif
