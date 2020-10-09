#ifndef _APP_DEMO_HEAD_
#define _APP_DEMO_HEAD_





void BSW_Init(void);
void APPTask_50ms(void);
void APPTask_20ms(void);
void APPTask_10ms(void);
void APPTask_5ms(void);
void APPTask_1ms(void);
void APPCANMail0_4Receive(void);

void ACU_CanLowInit(void);


void FlexCanRxTxIntruptcallback1(uint8_t instance,
                 flexcan_event_type_t eventType,
                 uint32_t buffIdx,
                 struct FlexCANState *driverState);        /*!< IRQ handler callback function. */

#endif







