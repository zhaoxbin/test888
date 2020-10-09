/***********************************************
 *�ļ�����:nfc_interface.h
 *����ͷ�ļ�:"Nfc.h"
 *��������:����NFC�Ĺ��ܺ���
 *��ע˵��:��
 *������:�Ա�
 *�����:
 *��������:2020-01-10
 **********************************************/

#ifndef NFC_INTERFACE_H_
#define NFC_INTERFACE_H_


/*****************��׼ͷ�ļ�**********************/


/*****************�Զ���ͷ�ļ�********************/
#include "ndef_bt_wifi.h"
#include "nfc_task.h"

/*****************�궨��************************/
//#define MAX_OOB_DATASIZE (200)
#define MAX_IMMO_DATA    (200)


/*****************���ݽṹ***********************/




/*
//P2P��Խ��
typedef enum
{
	NFC_P2P_Results_None = 0,
	// ����ֵ״̬ΪWithoob_ok����Ҫ��ȡgOOBData_From_MobileDevice������
	NFC_P2P_Results_BT_WithOOB_OK,
	NFC_P2P_Results_BT_WithoutOOB_OK,
	NFC_P2P_Results_BT_Pairing_Failed,
	NFC_P2P_Results_BT_Connection_Failed,
	NFC_P2P_Results_BT_Detection_Failed,
	NFC_P2P_Results_WIFI_WithoutOOB_OK,
	NFC_P2P_Results_WIFI_Pairing_Failed,
	NFC_P2P_Results_WIFI_Connection_Failed,
	NFC_P2P_Results_WIFI_Detection_Failed,
}NFC_P2P_Results;
*/




//IMMOִ�еĽ��
typedef enum
{
	NFC_IMMO_Results_None = 0,
	/* ����ֵ״̬ΪNFC_IMMO_Results_OK����Ҫ��ȡgImmo_Data������ */
	NFC_IMMO_Results_OK,
	NFC_IMMO_Results_Failed
	
}NFC_IMMO_Results;





/*****************ȫ�ֱ���***********************/



/*****************��������***********************/


/*********************************************
�������ƣ�NFC_Task_P2P
����������NFC��P2P����
���������mode[in]��P2P���ģʽ
          pair_oob_data[in]������ԵĲ�����Ϣ���磺����MAC��ַ��WIFI��SSID����Ϣ��
		  datalen[in]: ���ݳ���
���������NFC_P2P_Results��P2P��Խ��
�����������������ݵĽṹ��Ϊstruct bt_info
          wifi���ݵĽṹ��Ϊwifi_info
	      ��������ԣ��ҷ���ֵΪNFC_P2P_Results_BT_WithOOB_OKʱ����Ҫ��ȡgOOBData_From_MobileDevice������
**********************************************/
//extern NFC_P2P_Results NFC_Task_P2P(NFC_P2P_PairingMode mode,void *pair_oob_data,uint8_t datalen);


/*********************************************
�������ƣ�NFC_Task_IMM0
����������NFC��IMMO����
���������immo_type[in]:immo�����
	    ��gImmo_Data[out]��immo�����󷵻ص�����
���������NFC_IMMO_Results��IMMOִ�еĽ��
���������������ؽ��ΪNFC_IMMO_Results_OK�����ȡgImmo_Data������
*********************************************/
//extern NFC_IMMO_Results NFC_Task_IMM0(NFC_Task_IMMO_Type immo_type);


/*********************************************
�������ƣ�NFC_Task_LPCD_Cail
����������NFC��LPCDУ׼����
���������cail_agc_val[out]����ȡ����У׼ֵ
���������NxpNci_LPCD_Cail_Results��LPCDУ׼ִ�еĽ��
������������LPCDִ�гɹ���ʱ����Ҫ��ȡУ׼ֵ
*********************************************/
//extern NxpNci_LPCD_Cail_Results NFC_Task_LPCD_Cail(uint16_t *cail_agc_val);


/*********************************************
�������ƣ�NFC_Task_LPCD_Detect
����������NFC��LPCD�������
���������campare_agc_val[in]�����Ƚϵ�agcֵ
���������NxpNci_LPCD_Detect_Results��LPCD���ִ�еĽ��
������������
*********************************************/
//extern NxpNci_LPCD_Detect_Results NFC_Task_LPCD_Detect(uint16_t *campare_agc_val);



#endif
