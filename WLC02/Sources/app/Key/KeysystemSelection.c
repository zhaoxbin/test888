/*
 * systemSelection.c
 *
 *  Created on: 2019Äê7ÔÂ3ÈÕ
 *      Author: jiangxl
 */

#include "Cpu.h"
#include "hal.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"


static uint8_t   APCounter =0;


void SSelectionEntry(EventId eventId, uint8_t eventParam)
{
	SetKeyChargeSts(KChargeNoCharge);
	StopAllKeyTimers();
	APCounter =0;
	StartKeyTimer1(5);   //not much delay to do the first object detection, after that
	// PTB3 toggle for timing test
	//PINS_DRV_TogglePins(COIL1_EN_GPIO, 1 << COIL1_EN_PIN);

}


void SSelectionExit()
{
  StopAllKeyTimers();
}




//Callback by GetEvent
//every 500ms to detect if any object exsits

boolean SSelectionAction(EventInfo* pEvtInfo)
{
	//boolean bDet;


	pEvtInfo->eventId = EvtObjectDetected;
	return TRUE;

/*
	if(IsTimer1Expired()) //software  object detected
	{
		// PTB3 toggle for timing test
		//PINS_DRV_TogglePins(COIL1_EN_GPIO, 1 << COIL1_EN_PIN);

		StopTimer1();
 		APCounter++;
 		//PINS_DRV_TogglePins(COIL1_EN_GPIO, 1 << COIL1_EN_PIN);
 		//bDet = HAL_DetectObject();
 		//PINS_DRV_TogglePins(COIL1_EN_GPIO, 1 << COIL1_EN_PIN);
		//if(bDet)
 		if(HAL_DetectObject())
		{
			pEvtInfo->eventId = EvtObjectDetected;
			return TRUE;
		}
		else
		{
			HAL_DisablePower();
			StartTimer1(300);      //detect object every 300ms		24
			// PTB3 toggle for timing test
			//PINS_DRV_TogglePins(COIL1_EN_GPIO, 1 << COIL1_EN_PIN);
			if(APCounter > 2)
			{
				APCounter = 0;
				pEvtInfo->eventId = EvtObjectDetected;
				return TRUE;
			}
		}
	}

	return FALSE;
*/
}







