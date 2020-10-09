/*
 * systemTask.h
 *
 *  Created on: 2019Äê6ÔÂ28ÈÕ
 *      Author: jiangxl
 */

#ifndef SYSTEMTASK_H_
#define SYSTEMTASK_H_




void AppTask_Timer10Task(void);
void AppTask_Poll(void);
void KeyChargeStateInit(void);
void KeyChargeSelectionEntry(void);
//boolean GetEvent(StateId currentState, EventInfo* pEventInfo);
//void KeyChargeRun(void);

void SysStateInit();
void SysStateOffEntry();

void BSW_init(void);
void FlexCanRxTxIntruptcallback1(uint8_t instance,
                flexcan_event_type_t eventType,
                uint32_t buffIdx,
                struct FlexCANState *driverState);
void wakupprocess();
void BswNvMReadAll(void);
void BswNvMWriteAll(void);
#endif /* SYSTEMTASK_H_ */
