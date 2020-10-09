/*
 *
 *  Demo:
 *  主要用途：PC端向开发板发送CAN 多帧数据，开发板向PC回复相同的多帧数据
 *
 *
 *
 */

#include "CDDNIO.h"
#include "NFC_Inerface.h"
#include "systemStatus.h"
#include "systemTimers.h"

uint8 	DataFromCGW[200];
uint16 	Testgetlen=0;
uint16	TestSendLen = 0;
uint8	DataToCGW[8];

CDC_BTWIFI_Command		CdcBtWifiCmd;
WLC_DEVLP_02_0x4BC		WLCDevlpCommand;
WLC_DEVLP_02_0x4BC		WLCDevlpOldCommand;

#define ENV_DEMO_NUM 1

/**********************************************************************************************************************
 *  WLC_Value_SetDatatoCGW()
 *********************************************************************************************************************/
/*!

 * 当回调函数WLC_Value_GetDatafromCGW()  返回值为1  时，调用WLC_Value_SetDatatoCGW() 回调函数
 * 用户需要 WLC_Value_SetDatatoCGW() 函数中填充数据
 *参数：
 *    Data:     存放数据的指针
 *    *length:   写入数据的总长度
 *    *CANID
 *********************************************************************************************************************/

FUNC(Std_ReturnType, CDDNIO_CODE) WLC_Value_SetDatatoCGW(CDD_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data,uint16* CANID,uint8* length)
{

        uint8 i=0;

/*
       for(i=0;i<Testgetlen;i++)
       {

    	   DataToCGW[i]=DataFromCGW[i];
       }
*/
        if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x01))			// Command BT Enable/Disable
        {
        	TestSendLen = 0x3;
        	DataToCGW[0] = 0x01;										// Response
        	DataToCGW[1] = 0x01;										// BT
        	DataToCGW[2] = 0x00;										// OK
        }
        else if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x02))		// Command WIFI Enable/Disable
        {
        	TestSendLen = 0x3;
        	DataToCGW[0] = 0x01;										// Response
        	DataToCGW[1] = 0x02;										// WIFI
        	DataToCGW[2] = 0x00;										// OK
        }


		*length=TestSendLen;  //
		*CANID=WLC_CDC_NFC;
		for(i=0;i<*length;i++)
		{
			Data[i]=DataToCGW[i];
			// Data[i]=DataFromCGW[i];
		}


}

/**********************************************************************************************************************
 *  WLC_Value_GetDatafromCGW()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *返回值： 1  表示需要向CGW反馈信息
 *         2  表示不需要向CGW反馈信息
 *
 *pduid   wifi/bt
 *        Immob
 *
 *
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, CDDNIO_CODE) WLC_Value_GetDatafromCGW(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 length,uint16 rxcanid)
{
    Std_ReturnType value;
	/*


	*/
  	uint16 i;

  	value = 0;

  	Testgetlen=length;
    for(i=0;i<length;i++)
  	{
	  DataFromCGW[i]=*Data++;
  	}

    if(rxcanid==CDC_WLC_NFC)
    {
    	if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x01) && (DataFromCGW[2]==0x00))			// Command		BT		Enable
    	{
    		CdcBtWifiCmd.CdcBtReq = 0x01;
    	}
    	else if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x01) && (DataFromCGW[2]==0x01))		// Command		BT		Disable
    	{
    		CdcBtWifiCmd.CdcBtReq = 0x0;
    	}
    	else if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x02) && (DataFromCGW[2]==0x00))		// Command		WIFI	Enable
    	{
    		CdcBtWifiCmd.CdcWifiReq = 0x1;
    	}
    	else if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x02) && (DataFromCGW[2]==0x01))		// Command		WIFI	Disable
    	{
    		CdcBtWifiCmd.CdcWifiReq = 0x0;
    	}


    	value = 1;					// Need send response
    }

    if(rxcanid==CDC_WLC_NFC)
    {
		if((DataFromCGW[0]==0x03) && (DataFromCGW[1]==0x01) && (DataFromCGW[2]==0x00))		// Notification		BT		OK
		{
			CdcBtWifiCmd.CdcNotifBt = 0x1;
		}
		else if((DataFromCGW[0]==0x03) && (DataFromCGW[1]==0x01) && (DataFromCGW[2]==0x00))		// Notification		BT		OK
		{
			CdcBtWifiCmd.CdcNotifWifi = 0x1;
		}
    }

    //if((rxcanid==0x4BC))
    //{
    	//value=1;

    //}

    /*
     * This code for EMC test mode
     *
     */

    if(rxcanid==0x4BC)
    {
    	if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x00) && (DataFromCGW[2]==0x00))		// Command		AllClose		Enable
    	{
    		WLCDevlpCommand.TestModeForEMC = TestMode_AllClose;			// AllClose mode
    		gTestResp_Data[0] = 0x2;
    		gTestResp_Data[1] = 0x0;
    		gTestResp_Data[2] = 0x0;
    		gTestResp_Data[6] = ENV_DEMO_NUM;				// #1
    		//StartSysTimer9(500);
    	}
    	else if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x01) && (DataFromCGW[2]==0x00))		// Command		SleepMode		Enable
    	{
    		WLCDevlpCommand.TestModeForEMC = TestMode_Sleep;			// sleep mode
    		gTestResp_Data[0] = 0x2;
    		gTestResp_Data[1] = 0x1;
    		gTestResp_Data[2] = 0x0;
    		gTestResp_Data[6] = ENV_DEMO_NUM;				// #1
    		//StartSysTimer9(500);
    	}
    	else if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x02) && (DataFromCGW[2]==0x00))
    	{
    		WLCDevlpCommand.TestModeForEMC = TestMode_Ping;			// Ping mode
    		gTestResp_Data[0] = 0x2;
    		gTestResp_Data[1] = 0x2;
    		gTestResp_Data[2] = 0x0;
    		gTestResp_Data[6] = ENV_DEMO_NUM;				// #1
    		//StartSysTimer9(500);
    	}
    	else if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x03) && (DataFromCGW[2]==0x00))
    	{
    		WLCDevlpCommand.TestModeForEMC = TestMode_PhoneCharge;	// Phone Charge mode
    		gTestResp_Data[0] = 0x2;
    		gTestResp_Data[1] = 0x3;
    		//gTestResp_Data[2] = 0x0;
    		gTestResp_Data[6] = ENV_DEMO_NUM;				// #1
    		//StartSysTimer9(500);
    	}
    	else if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x04) && (DataFromCGW[2]==0x00))
    	{
    		WLCDevlpCommand.TestModeForEMC = TestMode_PingNFC;		// NFC Ping
    		gTestResp_Data[0] = 0x2;
    		gTestResp_Data[1] = 0x4;
    		gTestResp_Data[2] = 0x0;
    		gTestResp_Data[6] = ENV_DEMO_NUM;				// #1
    		//StartSysTimer9(500);
    	}
    	else if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x05) && (DataFromCGW[2]==0x00))
    	{
    		WLCDevlpCommand.TestModeForEMC = TestMode_NFCP2P;		// NFC P2P
    		gTestResp_Data[0] = 0x2;
    		gTestResp_Data[1] = 0x5;
    		//gTestResp_Data[2] = 0x0;
    		gTestResp_Data[6] = ENV_DEMO_NUM;				// #1
    		//StartSysTimer9(500);
    	}
    	else if((DataFromCGW[0]==0x00) && (DataFromCGW[1]==0x06) && (DataFromCGW[2]==0x00))
    	{
    		WLCDevlpCommand.TestModeForEMC = TestMode_KeyCharge;	// Key Charge
    		gTestResp_Data[0] = 0x2;
    		gTestResp_Data[1] = 0x6;
    		//gTestResp_Data[2] = 0x0;
    		gTestResp_Data[6] = ENV_DEMO_NUM;				// #1
    		//StartSysTimer9(500);
    	}
		if(WLCDevlpOldCommand.TestModeForEMC!=WLCDevlpCommand.TestModeForEMC)
		{
			StartSysTimer9(500);
			WLCDevlpOldCommand.TestModeForEMC = WLCDevlpCommand.TestModeForEMC;
			gTestResp_Data[2] = 0x1;
		}
    }


   return value;

}

uint16	GetCanTpDataLength()
{
	return Testgetlen;
}


