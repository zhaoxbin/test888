/***********************************************
 *文件名称:nfc_interface.h
 *引用头文件:"Nfc.h"
 *功能描述:描述NFC的功能函数
 *备注说明:无
 *创建者:赵斌
 *审核者:
 *创建日期:2020-01-10
 **********************************************/

#ifndef NFC_INTERFACE_H_
#define NFC_INTERFACE_H_


/*****************标准头文件**********************/


/*****************自定义头文件********************/
#include "ndef_bt_wifi.h"
#include "nfc_task.h"

/*****************宏定义************************/
//#define MAX_OOB_DATASIZE (200)
#define MAX_IMMO_DATA    (200)


/*****************数据结构***********************/




/*
//P2P配对结果
typedef enum
{
	NFC_P2P_Results_None = 0,
	// 返回值状态为Withoob_ok，需要读取gOOBData_From_MobileDevice的数据
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




//IMMO执行的结果
typedef enum
{
	NFC_IMMO_Results_None = 0,
	/* 返回值状态为NFC_IMMO_Results_OK，需要读取gImmo_Data的数据 */
	NFC_IMMO_Results_OK,
	NFC_IMMO_Results_Failed
	
}NFC_IMMO_Results;





/*****************全局变量***********************/



/*****************函数声明***********************/


/*********************************************
函数名称：NFC_Task_P2P
功能描述：NFC的P2P任务
输入参数：mode[in]：P2P配对模式
          pair_oob_data[in]：待配对的参数信息（如：蓝牙MAC地址、WIFI的SSID等信息）
		  datalen[in]: 数据长度
输出参数：NFC_P2P_Results：P2P配对结果
特殊声明：蓝牙数据的结构体为struct bt_info
          wifi数据的结构体为wifi_info
	      当蓝牙配对，且返回值为NFC_P2P_Results_BT_WithOOB_OK时，需要读取gOOBData_From_MobileDevice的数据
**********************************************/
//extern NFC_P2P_Results NFC_Task_P2P(NFC_P2P_PairingMode mode,void *pair_oob_data,uint8_t datalen);


/*********************************************
函数名称：NFC_Task_IMM0
功能描述：NFC的IMMO任务
输入参数：immo_type[in]:immo的类别
	    ：gImmo_Data[out]：immo操作后返回的数据
输出参数：NFC_IMMO_Results：IMMO执行的结果
特殊声明：当返回结果为NFC_IMMO_Results_OK，需读取gImmo_Data的数据
*********************************************/
//extern NFC_IMMO_Results NFC_Task_IMM0(NFC_Task_IMMO_Type immo_type);


/*********************************************
函数名称：NFC_Task_LPCD_Cail
功能描述：NFC的LPCD校准任务
输入参数：cail_agc_val[out]：读取到的校准值
输出参数：NxpNci_LPCD_Cail_Results：LPCD校准执行的结果
特殊声明：当LPCD执行成功的时候，需要读取校准值
*********************************************/
//extern NxpNci_LPCD_Cail_Results NFC_Task_LPCD_Cail(uint16_t *cail_agc_val);


/*********************************************
函数名称：NFC_Task_LPCD_Detect
功能描述：NFC的LPCD检测任务
输入参数：campare_agc_val[in]：待比较的agc值
输出参数：NxpNci_LPCD_Detect_Results：LPCD检测执行的结果
特殊声明：无
*********************************************/
//extern NxpNci_LPCD_Detect_Results NFC_Task_LPCD_Detect(uint16_t *campare_agc_val);



#endif
