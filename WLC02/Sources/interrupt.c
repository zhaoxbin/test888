/*
 * interrupt.c
 *
 *  Created on: 2019年6月28日
 *      Author: jiangxl
 */



//#include "Cpu.h"
//#include "defines.h"
#include "global.h"
#include "SystemDef.h"
#include "flexTimer_mc1.h"
//#include "interrupt.h"
#include "systemTimers.h"
#include "hal.h"
#include "CommDec.h"
#include "pins_driver.h"


static uint16 CommUsCountD=0;
static uint16 CommUsDelay=0;
uint8	LpuartRxData,bUartRcvFlag;

/*
void FTM2_Ovf_Reload_IRQHandler(void)
{


	AppTask_Timer10Task();
	FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_MC2,
  			(uint32_t) FTM_TIME_OVER_FLOW_FLAG);



}
*/

void FTM1_Ovf_Reload_IRQHandler(void)
{
	ST_TimerUpdate();

	// PTB3 toggle for 1ms test
	//PINS_DRV_TogglePins(COIL1_EN_GPIO, 1 << COIL1_EN_PIN);

	FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_MC1,
  			(uint32_t) FTM_TIME_OVER_FLOW_FLAG);



}

/*
 *  PTC16/PTC17 use as demodulation port
 */
void PORTC_IRQHandler(void)
{

	uint16 tmp;

	PINS_DRV_ClearPinIntFlagCmd(VDEMOD_GPIO, VDEMOD_PIN);
	//PINS_DRV_ClearPortIntFlagCmd(VDEMOD_GPIO);

	tmp = ST_GetUsTimerTick();

	CommUsDelay = tmp-CommUsCountD;
	CommUsCountD = tmp;

	if(CommUsDelay>3)				// 去毛刺，小于30us的间隔被识别为毛刺，不予理会
	{
	//		CommDlyCnt[3] = CommDlyCnt[2];
	//		CommDlyCnt[2] = CommDlyCnt[1];
		CommDlyCnt[1] = CommDlyCnt[0];
		CommDlyCnt[0] = CommUsDelay;
	}
	//  enableInterrupts();

	if(DECODER_SUCCESS==CommDecoder(RxPacket))
	{
		bNewMessage = TRUE;
		GetPacketMessage();
			//ED_RED_ON;
		variable_clear();
			//DecoderFinish = 1;
			//GPIOC->ODR ^= GPIO_PIN_3;		// TEST_PIN, if decode successfully, toggle pc3

	}

}


void LPUART1_RxTx_IRQHandler(void)
{
        //unsigned char rev = 0;

	 if((LPUART1->STAT & LPUART_STAT_RDRF_MASK)>>LPUART_STAT_RDRF_SHIFT)
	 {
		 LpuartRxData = LPUART1->DATA;
		 bUartRcvFlag = TRUE;
	 }

	 if((LPUART1->STAT & LPUART_STAT_TDRE_MASK)>>LPUART_STAT_TDRE_SHIFT)
	 {
		 LPUART1->CTRL &=~0x00800000;
	 }

}

void UartTDRDInit()
{
	bUartRcvFlag = FALSE;
	LpuartRxData = 0;
}

uint8	GetUartRcvFlag()
{
	return bUartRcvFlag;
}


uint8	GetUartRcvData()
{
	bUartRcvFlag = FALSE;
	return LpuartRxData;
}


/* WatchDog IRQ handler */
void WDOG_ISR()
{

	//ResetPID();
	//HAL_DisablePower();				// stop key charge
	//HAL_UartSendCommand(PChargeDisable);			// stop phone charge

}
