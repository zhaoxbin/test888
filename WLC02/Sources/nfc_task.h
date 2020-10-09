/***********************************************
 *文件名称:nfc_task.h
 *引用头文件:"Nfc.h"
 *功能描述:描述NFC的功能函数
 *备注说明:无
 *创建者:赵斌
 *审核者:
 *创建日期:2020-01-10
 **********************************************/

#ifndef NFC_TASK
#define NFC_TASK


/*****************标准头文件**********************/


/*****************自定义头文件********************/
#include "Nfc.h"
#include "NxpNci.h"

/*****************宏定义************************/


/*****************数据结构***********************/
/* NFC天线测试时使用 */
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


//P2P配对模式
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

/* 放在Nfc.h中 */
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

//IMMO的配对方式
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

//EMC的配对方式
typedef enum
{
	NFC_Task_EMC_Mode_EnablePing = 0,
	NFC_Task_EMC_Mode_EnableCommunication,
	NFC_Task_EMC_Mode_DisablePing,
	NFC_Task_EMC_Mode_DisableCommunication
}NFC_Task_EMC_Mode;

//EMC的配对方式
typedef enum
{
	NFC_Task_EMC_Results_None = 0,
	NFC_Task_EMC_Results_Succeed,
	NFC_Task_EMC_Results_Failed
}NFC_Task_EMC_Results;


/*****************全局变量***********************/
extern uint8_t gImmo_Data[2200];
extern uint16_t gLPCD_CailValue;
#ifdef LPCD_TEST
extern uint8_t ZB_LPCD_TEST[8];
#endif
extern int Immo_DataIndex;

/*****************函数声明***********************/
/*********************************************
函数名称：NFC_Task_Tag
功能描述：NFC的卡识别任务
输入参数：无
输出参数：NxpNci_TAG_Results：卡识别执行的结果
特殊声明：无
**********************************************/
extern NxpNci_TAG_Results NFC_Task_Tag(void);


/*********************************************
函数名称：NFC_Task_P2P
功能描述：NFC的P2P任务
输入参数：mode[in]：P2P配对模式
      pair_data[in]：呆配对的参数信息（如：蓝牙MAC地址、WIFI的SSID等信息）
      len[in]:配对数据的长度
输出参数：NxpNci_P2P_Results：P2P配对结果
特殊声明：蓝牙数据的结构体为struct bt_info
      wifi数据的结构体为wifi_info
	       当蓝牙配对，且返回值为NxpNci_P2P_Results_HSACKOK时，需要读取gOOBData_From_MobileDevice的数据
**********************************************/
extern NxpNci_P2P_Results NFC_Task_P2P(NFC_P2P_PairingMode mode,void *pair_data,int len);


/*********************************************
函数名称：NFC_Task_IMM0
功能描述：NFC的IMMO任务
输入参数：immo_type[in]:immo的类别
	    ： Time_CGW[in]：CGW的时间
	   ： Time_CGW_Len[in]：CGW的时间戳长度
	    ：gImmo_Data[out]：immo操作后返回的数据
输出参数：NxpNci_RW_NDEF_Results：IMMO执行的结果
特殊声明：当返回结果为NfcTask_IMMO_Results_ReadNDEF_OK，需读取NdefBuffer_IMMO的数据
*********************************************/
extern int Get_ImmoDataLen(void);
extern NxpNci_RW_NDEF_Results NFC_Task_IMM0(NFC_Task_IMMO_Type immo_type,unsigned char *Current_Time_CGW,uint8_t Time_CGW_Len);


/*********************************************
函数名称：NFC_Task_LPCD_Cail
功能描述：NFC的LPCD校准任务
输入参数：cail_agc_val[out]：读取到的校准值
输出参数：NxpNci_LPCD_Cail_Results：LPCD校准执行的结果
特殊声明：当LPCD执行成功的时候，需要读取校准值
*********************************************/
extern NxpNci_LPCD_Cail_Results NFC_Task_LPCD_Cail(uint16_t *cail_agc_val);


/*********************************************
函数名称：NFC_Task_LPCD_Detect
功能描述：NFC的LPCD检测任务
输入参数：campare_agc_val[in]：待比较的agc值
输出参数：NxpNci_LPCD_Detect_Results：LPCD检测执行的结果
特殊声明：无
*********************************************/
extern NxpNci_LPCD_Detect_Results NFC_Task_LPCD_Detect(uint16_t *campare_agc_val);

/* NFC天线测试时使用 */
extern uint32_t NFC_Tag_init(void);
extern uint32_t NFC_Tag_Discovery(void);


/*********************************************
函数名称：NFC_Task_EMCTest
功能描述：NFC的EMC测试任务
输入参数：Emc_NFC_mode[in]：EMC的NFC测试模式
输出参数：NFC_Task_EMC_Results:反馈测试结果
特殊声明：无
*********************************************/
extern NFC_Task_EMC_Results NFC_Task_EMCTest(NFC_Task_EMC_Mode Emc_NFC_mode);

#endif
