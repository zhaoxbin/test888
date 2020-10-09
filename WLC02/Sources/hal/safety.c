/*
 * safety.c
 *
 *  Created on: 2019Äê7ÔÂ15ÈÕ
 *      Author: jiangxl
 */
#include "global.h"
#include "Cpu.h"
#include "Qi_Spec.h"
#include "systemDef.h"
#include "hal.h"
#include "systemTimers.h"



#define TOTAL_SAFETY_TYPE       (CountMeasurementType)
//static DPMType dpmType = Normal;

typedef struct
{
  boolean			bIsOver;
  uint16        	lowLimit;
  uint16        	upLimit;
  SysUnsafeCode  	SysunsafeCode;
}DetectContext;

static  DetectContext  SafetyDectectTable[TOTAL_SAFETY_TYPE] = //must  be the same order defined in enum MeasurementType
{
  {FALSE,		VOLTAGE_LOW_LIMIT,              	VOLTAGE_HIGH_LIMIT,             	SysUnsafeOV},
  {FALSE,   	UNDERVOL_LOW_LIMIT,             	UNDERVOL_HIGH_LIMIT,            	SysUnsafeUV},
  {FALSE,       TEMPERATURE_COIL5_ADC_LOW_LIMIT, 	TEMPERATURE_COIL5_ADC_UP_LIMIT,  	SysUnsafeOTC5},
  {FALSE,       TEMPERATURE_COIL6_ADC_LOW_LIMIT, 	TEMPERATURE_COIL6_ADC_UP_LIMIT,  	SysUnsafeOTC6},
  {FALSE,       TEMPERATURE_COIL7_ADC_LOW_LIMIT, 	TEMPERATURE_COIL7_ADC_UP_LIMIT,  	SysUnsafeOTC7},
  {FALSE,       CURRENT_LOW_LIMIT,              	CURRENT_HIGH_LIMIT,             	SysUnsafeOC}
};


static boolean IsOver(sint16 value, MeasurementType type)
{

	boolean bOver = SafetyDectectTable[type].bIsOver;

	if(bOver)
	{
		switch(type)
		{
		case VoltageUnderMeasurement:
			if( value > (sint16)SafetyDectectTable[type].upLimit)
			{
				bOver = FALSE;
			}
			break;
		case VoltageMeasurement:
		case CurrentMeasurement:
			if(value < (sint16)SafetyDectectTable[type].lowLimit)
			{
				bOver = FALSE;
			}
			break;
		case Coil5TempMeasurement:
		case Coil6TempMeasurement:
		case Coil7TempMeasurement:
			//if(GetChargeFlag()==1)
			{
				if( value < (sint16)SafetyDectectTable[type].lowLimit)
				{
					bOver = FALSE;
				}
			}
			break;

		default:
			break;
		}
	}
	else
	{
		switch(type)
		{
		case VoltageUnderMeasurement:
			if(value < (sint16)SafetyDectectTable[type].lowLimit)
			{
				bOver = TRUE;
			}
			break;
		case VoltageMeasurement:
		case CurrentMeasurement:
			if(value > (sint16)SafetyDectectTable[type].upLimit)
			{
				bOver = TRUE;
			}
			break;

		case Coil5TempMeasurement:
		case Coil6TempMeasurement:
		case Coil7TempMeasurement:
			//if(GetChargeFlag()==1)
			{
				if(value > (sint16)SafetyDectectTable[type].upLimit)
				{
					bOver = TRUE;
				}
			}
			break;
		default:
			break;
		}
	}

	SafetyDectectTable[type].bIsOver = bOver;
	return bOver;
}


boolean SafetyMonitor(SysEventInfo* pEvtInfo)
{

	MeasurementType type;
	SysUnsafeCode 	SysunSafeCode;

	for(type=(MeasurementType)0; type<TOTAL_SAFETY_TYPE;type++)
	{
    //if(IsOver((SWORD)GetFilteredMeasurement(type), type))

		if(IsOver((sint16)GetFilteredMeasurement(type), type))
		{
			SysunSafeCode =  SafetyDectectTable[type].SysunsafeCode;
			pEvtInfo->SyseventId = EvtSysUnsafe;
			pEvtInfo->Sysparam1 = SysunSafeCode;
			return TRUE;
		}
	}

	return FALSE;
}









