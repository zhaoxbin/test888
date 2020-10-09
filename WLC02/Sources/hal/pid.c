/*
 * pid.c
 *
 *  Created on: 2019Äê7ÔÂ15ÈÕ
 *      Author: jiangxl
 */

#include "global.h"
#include "Cpu.h"
#include "Qi_Spec.h"
#include "systemDef.h"
#include "hal.h"
#include "ftm_hw_access.h"

//static uint32     	prevFreqHz;
//static uint16     	prevDutyDiv;
//static uint8		oscillate_cnt = 0;
static sint8      	sControlError;
//static sint8      	presControlError  = 0;
//static sint16      	MinDutyDiv;
//static sint16      	MaxDutyDiv;
//static uint32		FrequencyHz;

uint16				VpwmPeriod;

static uint32		DutyPercent;

PidType				adjustType;

sint16 				scaleValue;
sint8 				adjustValue;


uint32 FitRange(uint32 value, uint32 limitLow, uint32 limitHigh)
{
   if(value > limitHigh)
   {
     value = limitHigh;
   }
   else if(value < limitLow)
   {
     value = limitLow;
   }
   return value;

}


void CalculateNewFrequency(uint8 controlError)
{

	//

	uint16		tmp;

	sControlError = (sint8)controlError;

	if(sControlError != 0)
	{


	/*if(FrequencyHz == MAX_FREQUENCY_INDEX)
	{
      //oscillate_cnt = 0;

		if((prevDutyDiv != MaxDutyDiv) || (sControlError < 0))
		{
			adjustType = PID_Boundary_Duty;
		}
		else
		{
			adjustType = PID_Freq;
		}
	}*/

	//presControlError = sControlError;


		adjustValue      = (sint8)(sControlError/PID_SCALE);


		if(sControlError>0)
			adjustValue =(sint8) (adjustValue +1);
		else
			adjustValue = (sint8)(adjustValue -1);


	//if(adjustType == PID_Boundary_Duty)
	//{
	//	scaleValue = ((sint16)adjustValue*(sint16)DUTY_SCALE);
	//	prevDutyDiv = FitRange((prevDutyDiv - scaleValue), MaxDutyDiv, MinDutyDiv);
	//}
	//else //for frequency

		{


			tmp = 1;//FREQ_SCALE;


			if((adjustValue != 1) && (adjustValue != -1))
			{
				scaleValue = ((sint16)adjustValue*(sint16)tmp);
			}
			else
			{
				scaleValue = adjustValue;
			}
			VpwmPeriod = FitRange((VpwmPeriod + scaleValue), 100, 208);

		}
		//HAL_SetPwmPeriod((uint32_t)VpwmPeriod);
		//FTM_DRV_UpdatePwmPeriod(INST_FLEXTIMER_PWM1, FTM_PWM_UPDATE_IN_TICKS, VpwmPeriod, TRUE);

		FTM_DRV_SetMod(g_ftmBase[INST_FLEXTIMER_PWM1],VpwmPeriod);
		FTM_DRV_SetSoftwareTriggerCmd(g_ftmBase[INST_FLEXTIMER_PWM1], true);
		//bNewMessage = FALSE;
		//bNewMessage = FALSE;
		//bNewMessage = FALSE;
		//HAL_EnablePower();

	}

}


void ResetPID()
{

	adjustType        = PID_Freq;
	VpwmPeriod			= 150;
	DutyPercent			= DP_DUTY_PER;

	FTM_DRV_SetMod(g_ftmBase[INST_FLEXTIMER_PWM1],VpwmPeriod);
	FTM_DRV_SetSoftwareTriggerCmd(g_ftmBase[INST_FLEXTIMER_PWM1], true);

}




