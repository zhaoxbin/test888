/* ###################################################################
**     Filename    : main.c
**     Processor   : S32K14x
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"
#include "hal.h"
#include "systemTask.h"
#include "systemTimers.h"
#include "osif.h"
#include "NFC_Inerface.h"
#include "interrupt.h"

#include "EEEPROM_data_def.h"
#include "EEEPROM_io_ctl.h"

  volatile int exit_code = 0;


uint8			RxPacket[16] ={0};    //
boolean			bNewMessage = FALSE;
uint8			CommDlyCnt[2] = {0};
uint8			gCountOptConfig;
boolean			gExt;

uint8 			gMaxPower;
uint8 			gWindowSize;

uint16 			ginitCurrent;

uint32			freq;

uint8			test_val;

boolean			gCanNMWakeupFlag;
//extern boolean	bNfcNoblocking;

uint8	gTestResp_Data[8];
__attribute__ ((section(".eeeprom"))) eeerom_data_t eeerom_data;

//static uint16_t vbat, vrail, cur;

/* User includes (#include below this line is not maintained by Processor Expert) */

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
	uint8 i;
  /* Write your local variable definition here */

	uint8_t NCICoreReset[] = {0x20, 0x00, 0x01, 0x01};
	uint8_t Answer[66];
	uint16_t NbBytes = 0;
	uint8_t NCICoreInit[] = {0x20, 0x01, 0x00};

	NxpNci_RfIntf_t RfInterface;


  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

    /* Stop if the previous reset was caused by the Watchdog */


  /* Write your code here */
    HAL_Init();
#if 0
    if(POWER_SYS_GetResetSrcStatusCmd(RCM, RCM_WATCH_DOG) == true)
    {
    	HAL_KickWatchDog();
    	/*
    	 *  使能WDOG超时中断
    	 */
    	INT_SYS_InstallHandler(WDOG_EWM_IRQn, WDOG_ISR, (isr_t *)0);
    	INT_SYS_EnableIRQ(WDOG_EWM_IRQn);
    	/*
    	 *  WDOG初始化以及使能
    	 */
    	WDOG_DRV_Init(INST_WATCHDOG1, &watchdog1_Config0);

    }
#endif

    KeyChargeStateInit();
    KeyChargeSelectionEntry();
    SysStateInit();
    SysStateOffEntry();
    InitMeasurement();
    HAL_DisablePower();
    UartTDRDInit();

    ResetChargeFlag();
    HAL_CanParamsInit();

    HAL_UartSendCommand(PChargeDisable);
    bNfcNoblocking = TRUE;

	gTestResp_Data[0] = 0x0;
	gTestResp_Data[1] = 0x1;
	gTestResp_Data[2] = 0x1;
    gTestResp_Data[3] = 0x0;
    gTestResp_Data[4] = 0xAA;
    gTestResp_Data[5] = 0xAA;
    gTestResp_Data[6] = 0x0;

    //HAL_KeyCoilDetStart(CoilOne);
  /* For example: for(;;) { } */
    while(1)
    {


    	//NxpNci_WaitForDiscoveryNotification(&RfInterface,3);
    	AppTask_Poll();

    	/*
    	hal_NFCC_Reset();


		//SendCANData(TX_MAILBOX, 0x555, ciphertext, 8UL);
		hal_Send(NCICoreReset, sizeof(NCICoreReset), &NbBytes);

		if (NbBytes != sizeof(NCICoreReset))
		{
			//hal_Sleep(TIMEOUT_1S);
		}


		hal_Receive(Answer, sizeof(Answer), &NbBytes, 500000);
		if ((NbBytes == 0) || (Answer[0] != 0x40) || (Answer[1] != 0x00))
		{
			hal_Sleep(TIMEOUT_1S);
		}

		hal_Send(NCICoreInit, sizeof(NCICoreInit), &NbBytes);
		if (NbBytes != sizeof(NCICoreInit))
		{
			hal_Sleep(TIMEOUT_1S);
		}
		hal_Receive(Answer, sizeof(Answer), &NbBytes, 500000);
		if ((NbBytes == 0) || (Answer[0] != 0x40) || (Answer[1] != 0x01))
		{
			hal_Sleep(TIMEOUT_1S);
		}

		NbBytes = 0;
		memset(Answer,0x00,sizeof(Answer));
		*/
    	//if(IsTimer1Expired())
    	//{
    	//	//HAL_SetPwmPeriod(24000000/freq);
    	//	HAL_SetPwmFreq(freq);
    	//	HAL_EnablePower();
    	//	HAL_DetectObject();
    	//	// PTB3 toggle for timing test
    	//	//PINS_DRV_TogglePins(COIL1_EN_GPIO, 1 << COIL1_EN_PIN);
    	//	StartTimer1(500);
    	//	if(freq<190000)
    	//	{
    	//		freq += 500;
    	//	}
    	//	else
    	//	{
    	//		freq = 120000;
    	//	}

    	//}

    	//ST_WaitMs(500);
    	//HAL_EnablePower();
    	//ST_WaitMs(500);
    	//HAL_DisablePower();
    	//vbat  = HAL_GetBatteryVoltage();
    	//vrail = HAL_GetVrailVoltage();
    	//cur   = HAL_GetInputCurrent();
    	//vbat = HAL_GetTemp5();
    	//vbat = HAL_GetTemp6();
    	//vbat = HAL_GetTemp7();


    }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/
