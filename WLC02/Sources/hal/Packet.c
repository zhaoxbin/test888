/*
 * Packet.c
 *
 *  Created on: 2019Äê7ÔÂ8ÈÕ
 *      Author: jiangxl
 */

#include "global.h"
#include "Cpu.h"
#include "Qi_Spec.h"
#include "SystemDef.h"

//static uint8 gExt;
//static uint8 gMaxPower;
//static uint8 gCountOptConfig;
//static uint8 gWindowSize;


void GetPacketMessage()
{
	uint8 powerClass;
    uint8 maxPowerMsg;

    if(RxPacket[0] == HEADER_IDENTIFICATION)
    {
        gExt = (uint8)(RxPacket[4]&0x80);
    }
    else if(RxPacket[0] == HEADER_CONFIGURATION)
    {
    	maxPowerMsg = (uint8)(RxPacket[1]&0x3F);
    	powerClass = (uint8)(RxPacket[1]&0xC0);
    	if(powerClass)    //power class is bigger than 0, only calculate power class =1,
    	{
    		gMaxPower = (uint8)(maxPowerMsg*5);
    	}
    	else      //power class is 0, in Qi1.1
    	{
    		gMaxPower = (uint8)(maxPowerMsg>>1);
    	}

    	gCountOptConfig = (uint8)(RxPacket[3]&0x7);
    	gWindowSize = (uint8)((RxPacket[4]) >> 3);
    }
    //else if(RxPacket[0] == HEADER_PROPRIETARY_0X48)
    //{
      //gRxVoltageH = RxPacket[1];
      //gRxVoltageL = RxPacket[2];
      //gRxCurrentH = RxPacket[3];
      //gRxCurrentL = RxPacket[4];
    //}
}

