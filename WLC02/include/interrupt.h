/*
 * interrupt.h
 *
 *  Created on: 2019Äê6ÔÂ28ÈÕ
 *      Author: jiangxl
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


void FTM2_Ovf_Reload_IRQHandler(void);
 void FTM1_Ovf_Reload_IRQHandler(void);
 void PORTC_IRQHandler(void);
 void LPUART1_RxTx_IRQHandler(void);
 void WDOG_ISR(void);

#endif /* INTERRUPT_H_ */
