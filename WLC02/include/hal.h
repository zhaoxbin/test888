/*
 * hal.h
 *
 *  Created on: 2019Äê6ÔÂ28ÈÕ
 *      Author: jiangxl
 */

#ifndef HAL_H_
#define HAL_H_

#include "defines.h"
#include "Cpu.h"
#include "S32K144.h"
#include "systemStatus.h"
#include "systemDef.h"

//nfc
#include "lpi2c1.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

//ADC
#define ADC_REF_VOL         3300UL
#define ADC_BITS              12U

#define HAL_TEMPERATURE_TOP_R				5110.0	//ohm
#define HAL_TEMPERATURE_RESISTANCE_ROOM		10000.0	//ohm
#define HAL_TEMPERATURE_ROOM				(273.15+25.0)	//25 degrees Celsius
#define HAL_TEMPERATURE_B					3380//3610.0	//B25/85
#define HAL_TEMPERATURE_K					273.15

#define HAL_RAIL_SENSE_SHIFT_BITS           10   //shift for better resolution
#define HAL_RAIL_SENSE_UP_RESISTOR     16200.0   //ohm
#define HAL_RAIL_SENSE_DOWN_RESISTOR    2000.0   //ohm
#define HAL_RAIL_SENSE_MULTI_F      ((HAL_RAIL_SENSE_UP_RESISTOR+HAL_RAIL_SENSE_DOWN_RESISTOR)*(1UL<<HAL_RAIL_SENSE_SHIFT_BITS))
#define HAL_RAIL_SENSE_MULTI_U      ((uint32)(HAL_RAIL_SENSE_MULTI_F/HAL_RAIL_SENSE_DOWN_RESISTOR))


#define HAL_BATTERY_SENE_SHIFT_BITS         10      //shift for better resolution
#define HAL_BATTERY_SENSE_UP_RESISTOR     220000//16200//16200.0   //ohm
#define HAL_BATTERY_SENSE_DOWN_RESISTOR    33200//2550//2550.0   //ohm
#define HAL_BATTERY_SENSE_MULTI_F      ((HAL_BATTERY_SENSE_UP_RESISTOR+HAL_BATTERY_SENSE_DOWN_RESISTOR)*(1UL<<HAL_BATTERY_SENE_SHIFT_BITS))
#define HAL_BATTERY_SENSE_MULTI_U      ((uint32)(HAL_BATTERY_SENSE_MULTI_F/(HAL_BATTERY_SENSE_DOWN_RESISTOR)))


#define HAL_INPUT_CURRENT_SENSE_SHIFT_BITS   10     //shift for better resolution
#define HAL_INPUT_CURRENT_SENSE_RESISTOR   0.015   //ohm
#define HAL_INPUT_CURRENT_AMPLIFY_MULTI     100.0   //current sensor gain
#define HAL_INPUT_CURRENT_MULTI_COEFF_U     ((uint32)((1UL<<HAL_INPUT_CURRENT_SENSE_SHIFT_BITS)/(HAL_INPUT_CURRENT_SENSE_RESISTOR*HAL_INPUT_CURRENT_AMPLIFY_MULTI)))

#define HAL_AP_CURRENT_THRC 1500//130
#define HAL_AP_FREQUENCY    140000//130000//150000


#define TEST_GPIO0		PTD
#define TEST_PIN0		0U

#define COIL1_EN_GPIO	PTD
#define COIL1_EN_PIN	5U
#define COIL2_EN_GPIO	PTB
#define COIL2_EN_PIN	3U
#define VDEMOD_GPIO		PORTC
#define VDEMOD_PIN		17

#define TEST16_GPIO		PORTC
#define TEST16_PIN		16

#define VBATSW_EN_GPIO	PTE
#define VBATSW_EN_PIN	11U

#define CAN_EN_GPIO		PTA
#define CAN_EN_PIN		11U
#define CAN_STBEN_GPIO	PTE
#define CAN_STBEN_PIN	1U
#define CAN_WAKE_GPIO	PTE
#define CAN_WAKE_PIN	6U
#define ISF_CLEAR		24

//nfc
#define PIN_IRQ 1
#define BASE_IRQ PTA
#define PORT_IRQ PORTA


#define PIN_VEN 0
#define BASE_VEN PTA
#define PORT_VEN PORTA

#define GPT_SLEEP_CHANNEL         1
#define GPT_SLEEP_CHANNEL_MASK    (1UL << GPT_SLEEP_CHANNEL)
#define GPT_INSTANCE INST_LPIT1

#define MAX_TIMER 0xFFFFFFFF
#define TIMEOUT_1MS   1000
#define TIMEOUT_10MS  10000
#define TIMEOUT_50MS  50000
#define TIMEOUT_100MS 100000
#define TIMEOUT_500MS 500000
#define TIMEOUT_1S    1000000
#define TIMEOUT_2S    2000000
#define TIMEOUT_5S    5000000
#define TIMEOUT_INFINITE 0

#define SUCCESS 0
#define ERROR 1
#define NXPNCI_SUCCESS 0
#define NXPNCI_ERROR 1


typedef enum
{
	KeyCurrentSense,
	RailA5VSense,
	Temp5Sense,
	Temp6Sense,
	Temp7Sense,
	InputVbatSense,
	AdcChannelTotal
} ADC_CHANNEL_TYPE;


typedef enum
{
	CoilOne,
	CoilTwo,
	CoilsCount
}Coils;

typedef enum
{
	CoilSelNotFinished,
	CoilSelFinishedOne,
	CoilSelFinishedAll,
	CoilsSelOpCnt
}CoilsSts;

//nfc
extern lpi2c_master_state_t lpi2cMasterState;

//zb 2020-03-21
extern boolean	bNfcNoblocking;

Coils GetMaxStrengthCoil(void);

void HAL_Init(void);
void HAL_SetPwmPeriod(uint32_t newPeriod);
void HAL_CANInit();
uint16 HAL_GetAdcSampleData(ADC_CHANNEL_TYPE adc_channel);
uint16 HAL_GetBatteryVoltage(void);
uint16 HAL_GetInputCurrent(void);
void HAL_GetCurrentOffset(void);
uint16 HAL_GetTemp5(void);
uint16 HAL_GetTemp6(void);
uint16 HAL_GetTemp7(void);
uint16 HAL_GetVrailVoltage(void);

uint16 HAL_GetPingCurrent(void);

void HAL_ToggleGpio(GPIO_Type * const base, pins_channel_type_t pins);

void HAL_EnablePower(void);
void HAL_DisablePower(void);
void HAL_SetPwmFreq(uint32_t FrequencyHz);

boolean HAL_DetectObject(void);
void HAL_Coil1En_Config(boolean conf);
void HAL_Coil2En_Config(boolean conf);

void HAL_KeyCoilSelInit(void);
void HAL_KeyCoilDetStart(Coils index);
CoilsSts HAL_GetKeyCoilDet(Coils index);

void GetPacketMessage(void);


void CalculateNewFrequency(uint8 controlError);
//boolean CalculateNewFrequency(uint8 controlError);
void ResetPID(void);
//uint16 GetNewFreq(void);
//uint16 GetNewDuty(void);

void GetPacketMessage(void);


boolean DetectObject(void);
uint16 GetTransmitterPower(void);
boolean GetAvgRevPower(void);
void StartAvgRevPower(void);
boolean Fod(StateId KeycurrentState);
void InitFodLossValue(void);
uint16 GetSubPower(void);
void ResetFodCounter(void);


//boolean SafetyMonitor(EventInfo* pEvtInfo);
boolean SafetyMonitor(SysEventInfo* pEvtInfo);

uint16 GetFilteredMeasurement(MeasurementType type);

void MeasureAll(void);

uint16 GetInstantValue(MeasurementType type);
void InitMeasurement(void);
uint16 FilterMeasurement(uint16 average, uint16 newValue);

uint32 FitRange(uint32 value, uint32 limitLow, uint32 limitHigh);


void SelectCoils(uint8 index);
void DeselectAllCoils(void);

void HAL_UartSendCommand(uint8 command);
uint8 HAL_UartRecvSts(void);

void HAL_CANSTBEn_Config(boolean conf);
void HAL_CANEn_Config(boolean conf);
void HAL_GetCanParams(void);
void HAL_SetCanParams(void);
void HAL_CanParamsInit(void);
boolean HAL_GetMuteSts(void);

void UartTDRDInit(void);
uint8	GetUartRcvFlag(void);
uint8	GetUartRcvData(void);

/* NFC */
void hal_Sleep(uint32_t duration_microsec);
void hal_NFCC_Reset(void);
uint8_t hal_i2c_Write(const uint8_t *pbuff, uint16_t buffLen);
void hal_Send(const uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytesSent);
uint8_t hal_IRQ_Check(void);
uint8_t hal_WaitForRx(uint32_t timeout);
uint8_t hal_i2c_Read(uint8_t *pBuff, uint16_t buffLen, uint16_t *pBytesRead);
void hal_Receive(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytes, uint32_t timeout);
extern void hal_Clear(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytes);

void HAL_RWEEPROM(uint8* source,uint8* target,uint16 size);
void HAL_CanSleepTJA1043(void);
void HAL_KickWatchDog(void);
uint8 Dio_ReadChannel(uint8 channel);
uint8 Dio_WriteChannel(uint8 channel,uint8 value);
uint8 HAL_ReadPinEn(void);
uint8 HAL_ReadPinSTB(void);
uint8 HAL_ReadPinRXD(void);
status_t HAL_NVM_Init(void);
uint32 HAL_ReadEEPROMMemory(uint8* DataBuf,uint32 LocalAddress, uint32 Length);
void HAL_SetNvmBlcokAddress(void);
uint32 HAL_GetNvmBlockAddress(uint8 blockid);

#endif /* HAL_H_ */
