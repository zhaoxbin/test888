/*
 * systemDef.h
 *
 *  Created on: 2019年7月5日
 *      Author: jiangxl
 */

#ifndef SYSTEMDEF_H_
#define SYSTEMDEF_H_

#include "defines.h"

//#define _I2C_MONITOR
//#define COMMTEST
//#define RWPT_C0702_TX_1_3


#define BIT0         	0x01
#define BIT1         	0x02
#define BIT2         	0x04
#define BIT3         	0x08
#define BIT4         	0x10
#define BIT5         	0x20
#define BIT6         	0x40
#define BIT7         	0x80


#define PWM_MCLOCK		24000000

//#define FCK_PSC            16000
#define VOL_AVERAGE_NUMER  40
#define CUR_AVERAGE_NUMER  40
//#define DPCUR_AVERAGE_NUMER  40
#define TEMP_AVERAGE_NUMER 2
#define FOD_AVERAGE_NUMER 10

#define Oscillate_Num         3

/*
#define MIN_FREQUENCY_DIV     145//123  //16000kHz/110kHz = 145  16000K/130K=123
#define MIN_FREQUENCY_INDEX   0//22    //130kHz
#define MAX_FREQUENCY_INDEX   66//45   //(123 - FREQ_INDEX)=( 16000K/78) 205.1K  (145 - FREQ_INDEX)=( 16000K/78) 205.1K

#define MIN_DUTY              231//161  //(256-162)/256 = 37.109% (256-231)/256 = 9.77%
#define MAX_DUTY              128//147  //(256-147)/256 = 42.578% (256-238)/256 = 50%

#define AVERAGE_NUMER         16
#define PID_SCALE             8
#define FREQ_SCALE            1
#define DUTY_SCALE            1
*/
// ===========       ObjectDetect.c =======================================================
#define FOD_COUNTER_MAX                       3

#define AP_CURRENT_THRC                       280
#define FOD_IN_CURRENT_THRC                   310//140
#define FOD_OUT_CURRENT_THRC                  1500//280//120
#define FOD2_OUT_CURRENT_THRC                 1500//270//80

#define MEASURE_TIME 1   //1 ms
#define PWMCLOSE_DELAY   0
#define PWMSTART_DELAY   0

#define LOOP_NUMER         16


//===========         measurement settigns, used in measure.c    ============================================================

#define VOLTAGE_MEASURE_INTERVAL          200    //ms
#define CURRENT_MEASURE_INTERVAL          100//30     //ms
#define TEMPERATURE_MEASURE_INTERVAL      500    //ms

#define PING_TIME_OUT                      40
#define CONFIG_TIME_OUT                    41
#define CE_TIME_OUT                        42
#define RPP_TIME_OUT                       43

//===========         Limit settigns, used in safety.c    ============================================================
#define FIRST_DPM_FREQ                   3
#define NEXT_DPM_FREQ                    1

#define CURRENT_LOW_LIMIT               3000     //mA
#define CURRENT_HIGH_LIMIT              4000     //mA
#define VOLTAGE_LOW_LIMIT               17500    //mv
#define VOLTAGE_HIGH_LIMIT              18000    //mV
#define UNDERVOL_LOW_LIMIT				8500
#define UNDERVOL_HIGH_LIMIT				9000

#define TEMPERATURE_COIL5_ADC_LOW_LIMIT  75//2179// 40 degree   // 1027 // 80 degree  //2179// 40 degree
#define TEMPERATURE_COIL5_ADC_UP_LIMIT   85//1838 //50 degree   //838  // 90 degree  //1838 //50 degree

#define TEMPERATURE_COIL6_ADC_LOW_LIMIT  75//2179//40 degree    //1027 // 80 degree  //2179//40 degree
#define TEMPERATURE_COIL6_ADC_UP_LIMIT   85//1838//50 degree    //838  // 90 degree  //1838//50 degree

#define TEMPERATURE_COIL7_ADC_LOW_LIMIT  75//1528//60 degree    //1027 // 80 degree  //1528//60 degree
#define TEMPERATURE_COIL7_ADC_UP_LIMIT   85//1257//70 degree    //838  // 90 degree  //1257//70 degree


//#define TEMPERATURE_IC_ADC_LOW_LIMIT    2358    //1.9*4095/3.3v    63
//#define TEMPERATURE_IC_ADC_UP_LIMIT     3100      //2.5v*4095/3.3v = 3100   150

#define DPM_LOW_LIMIT                   11000//4200    //mv
//#define DPM_MID_MIMIT                   18000//4400
#define DPM_HIGH_LIMIT                  11300//4700    //mV 4900

// ===========       StatePing.c =======================================================
#define TPING   75

// ===========       StateTerminate.c =======================================================
//the timer counter is 16bit, maxmium is 64000ms, so combine the loop to make a long delay (>64s)
#define TIME_OUT_CHARGE_COMPLETE                60000           //
#define TIME_OUT_CHARGE_COMPLETE_LOOP           5

#define TIME_OUT_TERMINATE                      200           //1 seconds 1000

/*******************************************************************************

 Led
*********************************************************************************/
#define FAST				200			//200ms,	5Hz
#define MED					400			//400ms,	2.5Hz
#define SLOW				500		  //1000ms,	1Hz

#define DPM_LOW_LIMIT                   11000//4200    //mv
//#define DPM_MID_MIMIT                   18000//4400
#define DPM_HIGH_LIMIT                  11300//4700    //mV 4900

#define TIMER_MSCOUNT    30
#define TIMER3_DELAY     300
#define COMM_CURRENT_THRC 25

#define MAX_NUMER   16


// Pid.c
#define DP_FREQ_HZ	160000
#define DP_DUTY_PER 0x6000

#define MAX_FREQUENCY_INDEX		210000
#define MIN_FREQUENCY_INDEX		110000

#define PID_SCALE             20//16
#define FREQ_SCALE            300			// pid step Frequency/control Error = 0.3KHz/1
#define DUTY_SCALE            1

/*
#define  MAX_NUMBER 10
#define       i2cNull1          0   // 未用
#define       i2cTemperature    1   // NTC温度
#define       i2cTxVoltageH      2    // Tx电压
#define       i2cTxVoltageL      3    // Tx电压
#define       i2cTxCurrentH      4    // Tx电流
#define       i2cTxCurrentL      5    // Tx电流
#define       i2cRxVoltageH     6  // Rx电压
#define       i2cRxVoltageL     7    // Rx电压
#define       i2cRxCurrentH     8    // Rx电流高4位
#define       i2cRxCurrentL     9    // RX电流低8位
#define       i2cErrorPacket    10    // 错误包
#define       i2cPowerPacket    11   // 功率包
#define       i2cFreqIndex      12    // Tx频率表地址
#define       i2cFodPowerH      13    // fod power 高4位
#define       i2cFodPowerL      14    // fod power 低8位
#define       i2cNull2          15   // 未用
*/
/**
typedef enum
{
  PID_Duty,
  PID_Freq
}PidType;
*/
typedef enum
{
	i2cTemperature,			  //0
	i2cNull1,	  //1  NTC温度
	i2cTxVoltageH,		//2  Tx电压
	i2cTxVoltageL,		//3  Tx电压
	i2cTxCurrentH,		//4  Tx电流
	i2cTxCurrentL,		//5  Tx电流
	i2cErrorPacket,		//6 错误包
	i2cFodPowerH,		  //7 FOD Power高8位
	i2cMaxPower,		  //8  Rx电压
	i2cPowerPacket,		//9 功率包
	i2cTxPowerH,		  //10  TP高8位
	i2cTxPowerL,		  //11  TP低8位
	i2cFreqIndex,			//12 Tx频率表地址
	i2cadjustType,		//13 PID调节类型
	i2cNull2,   		  //14
	i2cFodPowerL      //15 FOD Power低8位
} I2CSTATUS;
/*******************************************************************************

DecodeCode
*********************************************************************************/
typedef enum {
  DECODER_FAIL 									= (uint8)0x00, /*!< Decoder Failed */
  DECODER_SUCCESS 							= (uint8)0x01, /*!< Decoder Succeed */
  DECODER_SUCCESS_CHECKSUMFAIL 	= (uint8)0x02 /*!< Decoder Message With CheckSum Failed */
} DEC_RESULT_TypeDef;

typedef enum{
	CODE_DECODER_0 = 0,						// "0"
	CODE_DECODER_1,						// "1"
	CODE_DECODER_01,					// "0""1"
	CODE_DECODER_10,					// "1""0"
	CODE_DECODER_NULL 				// No Code
} DEC_DETECT_NUMTypeDef;

														//us count的单位为10，所以以下参数都/10
#define LONG_1K_TWO		105			// 500*2.1/10
#define LONG_1K_MIN		38			// 500*0.85/10
#define LONG_1K_MAX		62			// 500*1.25/10
#define LONG_2K_MIN		10			// 250*0.65/10
#define LONG_2K_MAX		39			// 250*1.35/10


typedef struct
{
	uint8 header;
	uint8 message;                         //to save memory usage, only store the messages whose sizes are one byte
	uint8 msgSize;
	uint8 timeEndToStart;                 //time between End of last packet to Start of current packet
	uint8 timeStartToEnd;                  //time between Start of current packet to End of current packet
}Packet;



typedef enum
{

  VoltageMeasurement,
  VoltageUnderMeasurement,
  //IcTempMeasurement,
  Coil5TempMeasurement,
  Coil6TempMeasurement,
  Coil7TempMeasurement,
  CurrentMeasurement,
  CountMeasurementType
}MeasurementType;


typedef enum
{
  UnsafeOverCurrent,
  UnsafeOverVoltage,
  UnsafeOverCoilTemperature,
  UnsafeOverIcTemperature,
  UnsafeFOD,
  UnsafePingFOD,
  UnsafeCount
}UnsafeCode;

typedef enum
{
	SysUnsafeOV,
	SysUnsafeUV,
	SysUnsafeOTC5,
	SysUnsafeOTC6,
	SysUnsafeOTC7,
	SysUnsafeOC,
	SysUnsafePOV,
	SysUnsafePUV,
	SysUnsafePOT,
	SysUnsafePOC,
  SysUnsafeCount
}SysUnsafeCode;


typedef enum
{
  PID_Freq,
  PID_Normal_Duty,
  PID_Boundary_Duty
}PidType;

typedef enum
{
  LED_Standby,
  LED_FOD,
  LED_OverCurrent,
  LED_OverVoltage,
  LED_OverCoilTemperature,
  LED_OverIcTemperature,
  LED_DPM,
  LED_Charging,
  LED_ChargeCompleted,

  LED_StartCharge,
  LED_Electric,
  LED_Count
}LED_Code;

typedef enum
{
  GENERIC,
  GENERIC_OPT1,
  GENERIC_OPT2,
  GENERIC_OPT3
}LEDType;

typedef enum
{
  DPM_Start,
  DPM_Stop,
  Normal
}DPMType;

#endif /* SYSTEMDEF_H_ */
