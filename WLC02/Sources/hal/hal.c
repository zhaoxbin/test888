/*
 * hal.c
 *
 *  Created on: 2019年6月28日
 *      Author: jiangxl
 */

#include "defines.h"
#include "Cpu.h"
#include "flexTimer_pwm1.h"
#include "flexTimer_mc1.h"
#include "ftm_hw_access.h"
#include "interrupt.h"
#include "hal.h"
#include "pins_driver.h"
#include "flash_driver.h"
#include "S32K144.h"
#include "systemDef.h"
#include "systemTimers.h"
#include "canCom1.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "EEEPROM_data_def.h"
#include "EEEPROM_io_ctl.h"
#include "Rte_Communication_Read_APP.h"
#include "global.h"
#include "Qi_spec.h"
#include "NvM_Cfg.h"
#include"NvM_PrivateCfg.h"
#include "math.h"
#define EEE_SIZE  	0x02u	// EEEROM size 4096 bytes
#define EEE_BACKUP	0x08u	// EEEROM backup 65535 bytes

//extern __attribute__ ((section(".eeeprom"))) eeerom_data_t eeerom_data;

static uint16 current_offset;			//
static uint16_t ApCurrent;
uint16 CurTemp;
uint16 Cur;
#define RX_MSG_ID   (2UL)
uint8 EEE_data[32]={0};
lpi2c_master_state_t lpi2cMasterState;

flash_ssd_config_t flashSSDConfig;
flash_ssd_config_t pSSDConfig;
Coils selectCoilIndex=0;
uint8 SelsigStrength;
uint8 maxSigStrength = 0;
boolean bStatePing;

extern NM_WLC_0X538 		NM_WLC_Params;
extern WLC_01_0X3E3 		WLC_01_Params;
extern WLC_02_0X340 		WLC_02_Params;

extern CGW_03_0x10C 		CGW_03_Params;
extern CGW_WLC_0x3BE 		CGW_WLC_Params;
extern CGW_02_0x2C3 		CGW_02_Params;
extern CGW_TCU_01_0x3B2 	CGW_TCU_01_Params;
extern CDC_IC_01_0x3AA		CDC_IC_01_Params;
extern BCU_04_0x5B			BCU_04_Params;
extern CDC_WLC_0x2BA		CDC_WLC_Params;
extern CDC_BTWIFI_Command	CdcBtWifiCmd;
extern WLC_DEVLP_02_0x4BC	WLCDevlpCommand;

extern WLC_DEVLP_02_0x4BC	WLCDevlpOldCommand;

uint8	LpuartRxData;
boolean	bNfcNoblocking;
uint8_t data[8] ;
status_t HAL_NVM_Init(void)
 {
	 status_t ret = STATUS_SUCCESS;

	/*
	* initialize the FLASH module/driver
	*/
	 ret = FLASH_DRV_Init(&Flash1_InitConfig0, &pSSDConfig);


#if ((FEATURE_FLS_HAS_FLEX_NVM == 1u) & (FEATURE_FLS_HAS_FLEX_RAM == 1u))
    /* Config FlexRAM as EEPROM if it is currently used as traditional RAM */
    if (pSSDConfig.EEESize == 0u)
    {

        /* Configure FlexRAM as EEPROM and FlexNVM as EEPROM backup region,
         * DEFlashPartition will be failed if the IFR region isn't blank.
         * Refer to the device document for valid EEPROM Data Size Code
         * and FlexNVM Partition Code. For example on S32K144:
         * - EEEDataSizeCode = 0x02u: EEPROM size = 4 Kbytes
         * - DEPartitionCode = 0x08u: EEPROM backup size = 64 Kbytes */
        ret = FLASH_DRV_DEFlashPartition(&pSSDConfig, 0x02u, 0x08u, 0x0u, false, true);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Re-initialize the driver to update the new EEPROM configuration */
        ret = FLASH_DRV_Init(&Flash1_InitConfig0, &pSSDConfig);
        DEV_ASSERT(STATUS_SUCCESS == ret);

        /* Make FlexRAM available for EEPROM */
        ret = FLASH_DRV_SetFlexRamFunction(&pSSDConfig, EEE_ENABLE, 0x00u, NULL);
        DEV_ASSERT(STATUS_SUCCESS == ret);
    }
    else    /* FLexRAM is already configured as EEPROM */
    {
        /* Make FlexRAM available for EEPROM, make sure that FlexNVM and FlexRAM
         * are already partitioned successfully before */
        ret = FLASH_DRV_SetFlexRamFunction(&pSSDConfig, EEE_ENABLE, 0x00u, NULL);
        DEV_ASSERT(STATUS_SUCCESS == ret);
    }
#endif /* (FEATURE_FLS_HAS_FLEX_NVM == 1u) & (FEATURE_FLS_HAS_FLEX_RAM == 1u) */

	 return ret;
 }
void ftmTimerISR(void)
{

}
void HAL_Init(void)
{
	ftm_state_t ftmStateStruct;
    int i;
	//status_t ret;
	/*
	 * Clock初始化
	 */
	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
                   g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

    HAL_NVM_Init();
   // FLASH_DRV_Init(&Flash1_InitConfig0, &flashSSDConfig);
    /*
     * Pin初始化
     */
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);

    PINS_DRV_SetPinIntSel(VDEMOD_GPIO,VDEMOD_PIN,PORT_INT_EITHER_EDGE);

    PINS_DRV_SetPinsDirection(TEST16_GPIO, (1 << TEST16_PIN));
    PINS_DRV_SetPins(TEST16_GPIO, (1 << TEST16_PIN));
	/*
	 *  初始化GPIO，设置方向为输出和初始值
	 */
	//PINS_DRV_SetPinsDirection(TEST_GPIO0, (1 << TEST_PIN0));
	//PINS_DRV_SetPins(TEST_GPIO0, (1 << TEST_PIN0));

	PINS_DRV_SetPinsDirection(COIL1_EN_GPIO, (1 << COIL1_EN_PIN));
	//PINS_DRV_SetPins(COIL1_EN_GPIO, (1 << COIL1_EN_PIN));
	PINS_DRV_ClearPins(COIL1_EN_GPIO, (1 << COIL1_EN_PIN));

	PINS_DRV_SetPinsDirection(COIL2_EN_GPIO, (1 << COIL2_EN_PIN));
	PINS_DRV_ClearPins(COIL2_EN_GPIO, (1 << COIL2_EN_PIN));

	//PINS_DRV_SetPins(COIL2_EN_GPIO, (1 << COIL2_EN_PIN));

    /*
     *  DMA初始化
     */

    EDMA_DRV_Init(&dmaController1_State,
        			  &dmaController1_InitConfig0,
    				  edmaChnStateArray,
    				  edmaChnConfigArray,
    				  EDMA_CONFIGURED_CHANNELS_COUNT);
    /*
     *  ADC初始化
     */

    ADC_DRV_ConfigConverter(INST_ADCONV1, &adConv1_ConvConfig0);


    /*
     * PWM初始化
     */
    FTM_DRV_Init(INST_FLEXTIMER_PWM1, &flexTimer_pwm1_InitConfig, &ftmStateStruct );
    FTM_DRV_InitPwm(INST_FLEXTIMER_PWM1, &flexTimer_pwm1_PwmConfig);



    /*
     * UART 初始化
     */
#ifdef LPCD_TEST
#else
    LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0);
    LPUART1->CTRL |= 0x002C0000;

#endif

    /*
     * CAN 初始化
     */
    HAL_CANInit();
    HAL_CANEn_Config(TRUE);			// configure CAN Transceiver EN High
    HAL_CANSTBEn_Config(TRUE);		// configure CAN Transceiver STB_EN High
    PINS_DRV_ClearPins(CAN_WAKE_GPIO, (1 << CAN_WAKE_PIN));

#ifdef LPCD_TEST
#else
    HAL_SetNvmBlcokAddress();
    BSW_init();
#endif

    /*  LPIT (used for sleep)*/
	LPIT_DRV_Init(INST_LPIT1, &lpit1_InitConfig);
	LPIT_DRV_InitChannel(INST_LPIT1, 0, &lpit1_ChnConfig0);


    /*
     * 1ms counter初始化
     */
#ifdef LPCD_TEST
#else
    FTM_DRV_Init(INST_FLEXTIMER_MC1, &flexTimer_mc1_InitConfig,	&ftmStateStruct);
    FTM_DRV_InitCounter(INST_FLEXTIMER_MC1, &flexTimer_mc1_TimerConfig);
    FTM_DRV_CounterStart(INST_FLEXTIMER_MC1);


    ///增加 10ms  定时器
#if 0
      FTM_DRV_Init(INST_FLEXTIMER_MC2, &flexTimer_mc2_InitConfig, &ftmStateStruct);

      /* Setup the counter to trigger an interrupt every 10 ms */
      FTM_DRV_InitCounter(INST_FLEXTIMER_MC2, &flexTimer_mc2_TimerConfig);
      /* Start the counter */
      FTM_DRV_CounterStart(INST_FLEXTIMER_MC2);
#endif

#endif


	/*
	 * I2C
	 */
	//INT_SYS_SetPriority(LPI2C0_Master_IRQn, 0x5U);
	LPI2C_DRV_MasterInit(INST_LPI2C1, &lpi2c1_MasterConfig0, &lpi2cMasterState);

	/*
	 * wdg
	 */


	/* Initialize WDG  */
	WDOG_DRV_Init(INST_WATCHDOG1, &watchdog1_Config0);

	WDOG_DRV_Trigger(INST_WATCHDOG1);

    /*
     * INT初始化
     */
	INT_SYS_SetPriority(CAN1_ORed_IRQn, 0x1U);
	INT_SYS_SetPriority(CAN1_Error_IRQn, 0x1U);
	INT_SYS_SetPriority(CAN1_ORed_0_15_MB_IRQn, 0x1U);


	INT_SYS_SetPriority(FTM1_Ovf_Reload_IRQn, 0x0U);
    INT_SYS_InstallHandler(FTM1_Ovf_Reload_IRQn, &FTM1_Ovf_Reload_IRQHandler, (isr_t *)0);
    INT_SYS_EnableIRQ(FTM1_Ovf_Reload_IRQn);

    INT_SYS_SetPriority(LPUART1_RxTx_IRQn, 0x0U);

/////
#if 0
    /* Install handler for the Timer overflow interrupt and enable it */
    INT_SYS_SetPriority(FTM2_Ovf_Reload_IRQn, 0x0U);
    INT_SYS_InstallHandler(FTM2_Ovf_Reload_IRQn, &FTM2_Ovf_Reload_IRQHandler, (isr_t*) 0U);
    INT_SYS_EnableIRQ(FTM2_Ovf_Reload_IRQn);
#endif

#ifdef LPCD_TEST
#else
    INT_SYS_InstallHandler(LPUART1_RxTx_IRQn, &LPUART1_RxTx_IRQHandler, (isr_t *)0);
    INT_SYS_EnableIRQ(LPUART1_RxTx_IRQn);
#endif
    INT_SYS_SetPriority(PORTC_IRQn, 0x0U);
#ifdef LPCD_TEST
#else
    INT_SYS_InstallHandler(PORTC_IRQn, &PORTC_IRQHandler, (isr_t *)0);
    INT_SYS_EnableIRQ(PORTC_IRQn);
#endif

    /* zb int */
    INT_SYS_EnableIRQGlobal();

 /*   if(flashSSDConfig.EEESize==0)
    {
    	ret = FLASH_DRV_DEFlashPartition(&flashSSDConfig, EEE_SIZE, EEE_BACKUP, 0x0u, false, true);
    	DEV_ASSERT(STATUS_SUCCESS == ret);
    	ret = FLASH_DRV_Init(&Flash1_InitConfig0, &flashSSDConfig);
    	DEV_ASSERT(STATUS_SUCCESS == ret);
    	ret = FLASH_DRV_SetFlexRamFunction(&flashSSDConfig, EEE_ENABLE, 0x00u, NULL);
   	    DEV_ASSERT(STATUS_SUCCESS == ret);
    }
*/
}

void HAL_KickWatchDog()
{
	WDOG_DRV_Trigger(INST_WATCHDOG1);
}

void hal_Sleep(uint32_t duration_microsec)
{

    LPIT_DRV_StopTimerChannels(GPT_INSTANCE, GPT_SLEEP_CHANNEL_MASK);
    LPIT_DRV_SetTimerPeriodByUs(GPT_INSTANCE, GPT_SLEEP_CHANNEL, duration_microsec);
    LPIT_DRV_StartTimerChannels(GPT_INSTANCE, GPT_SLEEP_CHANNEL_MASK);
    while(!LPIT_DRV_GetInterruptFlagTimerChannels(GPT_INSTANCE, GPT_SLEEP_CHANNEL_MASK))
    {
    	bNfcNoblocking = FALSE;				// nfc blocking
    	AppTask_Poll();						// call task_poll
    } //block until expired
    LPIT_DRV_StopTimerChannels(GPT_INSTANCE, GPT_SLEEP_CHANNEL_MASK);
    LPIT_DRV_ClearInterruptFlagTimerChannels(GPT_INSTANCE, GPT_SLEEP_CHANNEL_MASK);
}


void hal_NFCC_Reset(void)
{
	/* 2019-12-10 add by zhaobin */
	PINS_DRV_WritePin(BASE_VEN, PIN_VEN, 1);
	hal_Sleep(TIMEOUT_50MS);

	PINS_DRV_WritePin(BASE_VEN, PIN_VEN, 0);
	hal_Sleep(TIMEOUT_50MS);
	PINS_DRV_WritePin(BASE_VEN, PIN_VEN, 1);
	hal_Sleep(TIMEOUT_50MS);
}

uint8_t hal_i2c_Write(const uint8_t *pbuff, uint16_t buffLen)
{
	/* Send a packet of data to the bus slave */
	//LPI2C_DRV_MasterSendDataBlocking(INST_LPI2C1, buffer, TRANSFER_SIZE, true, OSIF_WAIT_FOREVER);

	LPI2C_DRV_MasterSendDataBlocking(INST_LPI2C1, pbuff, buffLen, 1, 1000);
	return SUCCESS;
}

void hal_Send(const uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytesSent)
{
	uint8_t status = ERROR;

	status = hal_i2c_Write(pBuffer, BufferLen);

	if(status == ERROR)
	{
		*pBytesSent = 0;
	}
	else
	{
		*pBytesSent = BufferLen;
	}
}




uint8_t hal_IRQ_Check(void)
{
	uint32_t pinValue = (PINS_DRV_ReadPins(BASE_IRQ)& (1<<PIN_IRQ));
	if(pinValue == 0) return 0;
	else return 1;
}

uint8_t hal_WaitForRx(uint32_t timeout)
{
	if (timeout == 0)
	{
		while ((hal_IRQ_Check() == 0));
	} else
	{
		uint32_t to = timeout;
		while ((hal_IRQ_Check()== 0))
		{
			hal_Sleep(5000);//100
			to -= 5000;//100
			if((to <= 0)||(to > timeout))
			{
				bNfcNoblocking= TRUE;
				return ERROR;
			}
		}
	}
	bNfcNoblocking = TRUE;
	return SUCCESS;
}

uint8_t hal_i2c_Read(uint8_t *pBuff, uint16_t buffLen, uint16_t *pBytesRead)
{
	uint16_t NCISize;
	uint8_t buffRx1[4]={0x00};
	uint8_t buffRx2[320];//256
	int16_t to = TIMEOUT_100MS;//300

	LPI2C_DRV_MasterReceiveDataBlocking(INST_LPI2C1, buffRx1, 3, 1, 1000);
	NCISize=buffRx1[2];
	LPI2C_DRV_MasterReceiveDataBlocking(INST_LPI2C1, buffRx2, NCISize, 1, 1000);

	/* 2020.1.18 增加的异常处理  */
	if(NCISize+3 > buffLen)
	{
		return ERROR;
	}

	memcpy(pBuff,&buffRx1[0],3);
	memcpy(&pBuff[3],&buffRx2[0],NCISize);
	*pBytesRead = NCISize + 3;


	//check that the IRQ pin has gone low, timeout is 100 micro
	/*while ((hal_IRQ_Check()== 1))
	{
			hal_Sleep(TIMEOUT_10MS);//10
			to -= TIMEOUT_10MS;//10
			if( (to <= 0) || (to >= TIMEOUT_100MS))
			{
 				bNfcNoblocking= TRUE;
				return ERROR;
			}
	}

	bNfcNoblocking= TRUE;
	*/
	return SUCCESS;
}

void hal_Receive(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytes, uint32_t timeout)
{
	if (hal_WaitForRx(timeout) == ERROR)
		*pBytes = 0;
	else
	{
		hal_i2c_Read(pBuffer, BufferLen, pBytes);
	}
}

/**************************
函数名称：hal_Clear
功能描述：不等待直接读取寄存器中的数值
输入参数：pBuffer[out]：存放数据的缓存区
	 ：   BufferLen[out]：缓冲区大小
	 ： pBytes[out]：读取到的数据长度
输出参数：无
**************************/
void hal_Clear(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytes)
{
#ifdef SPI
		hal_spi_Read(pBuffer, BufferLen, pBytes);
#endif
#ifdef I2C
		hal_i2c_Read(pBuffer, BufferLen, pBytes);
#endif
}


/*add CAN Driver init
 *
 */
void HAL_CANInit()
{

	   FLEXCAN_DRV_Init(INST_CANCOM1, &canCom1_State, &canCom1_InitConfig0);

/*	    flexcan_data_info_t dataInfo =
	    {
	            .data_length = 8U,
	            .msg_id_type = FLEXCAN_MSG_ID_STD,
	            .enable_brs  = true,
	            .fd_enable   = false,
	            .fd_padding  = 0U
	    };*/
	    flexcan_data_info_t dataInfo =
	    {
	            .data_length = 8U,
	            .msg_id_type = FLEXCAN_MSG_ID_STD,
	            .enable_brs  = true,
	            .fd_enable   = false,
	            .fd_padding  = 0U
	    };
	    /* Configure RX message buffer with index RX_MSG_ID and RX_MAILBOX */
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 0, &dataInfo, 0x505);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 1, &dataInfo, 0x638);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 2, &dataInfo, 0x601);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 3, &dataInfo, 0x4bc);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 4, &dataInfo, 0x4af);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 5, &dataInfo, 0x3be);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 6, &dataInfo, 0x3b2);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 7, &dataInfo, 0x3aa);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 8, &dataInfo, 0x2c3);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 9, &dataInfo, 0x2ba);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 10, &dataInfo, 0x10c);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 11, &dataInfo, 0x5b);
	    FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, 12, &dataInfo, 0x27);

	    FLEXCAN_DRV_InstallEventCallback(INST_CANCOM1,FlexCanRxTxIntruptcallback1,NULL);

}


/*
 *
 */
void HAL_SetPwmPeriod(uint32_t newPeriod)
{
	FTM_DRV_UpdatePwmPeriod(INST_FLEXTIMER_PWM1, FTM_PWM_UPDATE_IN_TICKS, newPeriod, TRUE);
}

uint16 vraila_adcval;

static sint16 HAL_CovertAdcCntToCelsisusDegree(uint16 adcValue)
{
	uint32 dwTemp;
	float32 dbtemp;

	//Convert temperature ADC counts to resistor value
	// Formula: Rt/(Rt+Rtop) = adccnt/(1<<ADC_BITS)
	//       => Rt = Rtop*adccnt/((1<<ADC_BITS)-adccnt)
	dwTemp = adcValue;
	dwTemp *= HAL_TEMPERATURE_TOP_R;
	dwTemp /= ((1UL<<ADC_BITS) - 1UL - adcValue);

	//Calculate temperature
	//Rt = R*exp(B*(1/T1-1/T2))
	//where T1 = HAL_TEMPERATURE_RESISTANCE_ROOM, Rt is the resistor value in HAL_TEMPERATURE_RESISTANCE_ROOM
	//      T2 = measured temperature, R is the resistor value in measured temperature.
	//      B  = HAL_TEMPERATURE_B
	//  =>  T2 = 1/(1/T1 - log(Rt/R)/B) = 1/(1/T1 + log(R/Rt)/B)
	dbtemp = dwTemp / HAL_TEMPERATURE_RESISTANCE_ROOM;
	dbtemp = log(dbtemp);
	dbtemp /= HAL_TEMPERATURE_B;
	dbtemp += (1.0 / HAL_TEMPERATURE_ROOM);
	dbtemp = 1.0 / dbtemp;
	dbtemp -= HAL_TEMPERATURE_K;  //convert to celsius degree

	return (sint16)dbtemp;
}


uint16 HAL_GetAdcSampleData(ADC_CHANNEL_TYPE adc_channel)
{
	uint32 ret=0;
	uint16 ADC_result;
	//uint16 i, j;

	switch(adc_channel)
	{
	case KeyCurrentSense:
		ADC_DRV_ConfigChan(INST_ADCONV1,0, &AdcKeyCurrentChannel);		//Input Current
		break;
	case RailA5VSense:
		ADC_DRV_ConfigChan(INST_ADCONV1,0, &AdcRailA5VChannel);		//Rail 5V ADC0_10
		break;
	case Temp5Sense:
		ADC_DRV_ConfigChan(INST_ADCONV1,0, &AdcTemp5Channel);		//TEMP5 ADC0_5
		break;
	case Temp6Sense:
		ADC_DRV_ConfigChan(INST_ADCONV1,0, &AdcTemp6Channel);		//TEMP6 ADC0_4
		break;
	case Temp7Sense:
		ADC_DRV_ConfigChan(INST_ADCONV1,0, &AdcTemp7Channel);		//TEMP6 ADC0_6
		break;
	case InputVbatSense:
		ADC_DRV_ConfigChan(INST_ADCONV1,0, &AdcVbatChannel);		//TEMP6 ADC0_3
		break;
	default:
		break;
	}
	/*
	 *  等待ADC转换完成
	 */
	ADC_DRV_WaitConvDone(INST_ADCONV1);
	/*
	 *  ADC转换延时
	 */
	//for(i = 0; i<0xFFFF; i++)
	//{
//	 	for(j = 0; j < 5; j++);
	//}
	//for(i = 0; i<0xFFFF; i++)
	//{
	// 	for(j = 0; j < 5; j++);
	//}


	/*
	 *  ADC转换成功则利用串口输出ADC转换结果
	 */
	ADC_DRV_GetChanResult(INST_ADCONV1, 0, &ADC_result);


	switch(adc_channel)
	{
	case KeyCurrentSense:		// amplify =  0.015*100 = 1.5, so  I=ADC/1.5
		ret = ADC_result *2*3300;
		ret /=3;
		ret /= 4096;
		break;

	case RailA5VSense:
		ret = ADC_result *ADC_REF_VOL;
		ret = ret>>ADC_BITS;
		ret *= HAL_RAIL_SENSE_MULTI_U;
		ret >>= HAL_RAIL_SENSE_SHIFT_BITS;
		//vraila_adcval = ADC_result;
		break;

	case Temp5Sense:
	case Temp6Sense:
	case Temp7Sense:
		//ret = ADC_result;
		ret = HAL_CovertAdcCntToCelsisusDegree(ADC_result);
		break;

	case InputVbatSense:
		//ADC值转换为mv
		ret = ADC_result *ADC_REF_VOL ;
		ret = ret>>ADC_BITS;
		//根据分压比计算出vbat
		ret *= HAL_BATTERY_SENSE_MULTI_U;
		ret >>= HAL_BATTERY_SENE_SHIFT_BITS;

		//ret = ADC_result * 2532;
		//ret /= vraila_adcval;
		//ret *= 20;
		//ret *= 5095;
		//ret /= 332;
		//ret /= 182;

		break;

	default:
		break;

	}

	return (uint16)ret;

}


uint16 HAL_GetBatteryVoltage(void)
{

	return HAL_GetAdcSampleData(InputVbatSense);

}

void HAL_GetCurrentOffset()
{
	current_offset = HAL_GetAdcSampleData(KeyCurrentSense);
}

uint16 HAL_GetInputCurrent(void)
{

	CurTemp = HAL_GetAdcSampleData(KeyCurrentSense);

	if(CurTemp>current_offset)
	{
		Cur = CurTemp - current_offset;
	}
	else
	{
		Cur = 0;
	}
	return Cur;
}


uint16 HAL_GetTemp5(void)
{
	return HAL_GetAdcSampleData(Temp5Sense);
}

uint16 HAL_GetTemp6(void)
{
	return HAL_GetAdcSampleData(Temp6Sense);
}

uint16 HAL_GetTemp7(void)
{

	return HAL_GetAdcSampleData(Temp7Sense);
}

uint16 HAL_GetVrailVoltage(void)
{

	return HAL_GetAdcSampleData(RailA5VSense);
}


static uint16 GetMaxValue(uint8 loops)
{
	uint8 i;
	uint16 currentValue;
	uint16 maxValue;
	maxValue = 0;
	for(i = 0; i < loops; i++ )
	{
		//urrentValue = GetInstantValue(type);
		currentValue = HAL_GetInputCurrent();
		if(currentValue > maxValue)
		{
			maxValue = currentValue;
		}
	}
	return maxValue;
}

uint16 HAL_GetPingCurrent()
{

	uint16 MaxCurrent;

	uint32	tmp;

	tmp = PWM_MCLOCK/HAL_AP_FREQUENCY;

	//HAL_SetPwmFreq(HAL_AP_FREQUENCY);
	HAL_SetPwmPeriod(tmp);

	HAL_EnablePower();

	MaxCurrent = GetMaxValue(LOOP_NUMER);//,CurrentMeasurement);

	HAL_DisablePower();

	return MaxCurrent;
}


void HAL_EnablePower()
{
	//uint8_t index;
	//ftm_pwm_param_t param;

	/*for (index = 0U; index < flexTimer_pwm1_PwmConfig.nNumCombinedPwmChannels; index++)

	{

		FTM_DRV_EnablePwmChannelOutputs(g_ftmBase[INST_FLEXTIMER_PWM1],
				flexTimer_pwm1_PwmConfig.pwmCombinedChannelConfig[index].hwChannelId);

		FTM_DRV_EnablePwmChannelOutputs(g_ftmBase[INST_FLEXTIMER_PWM1],
				flexTimer_pwm1_PwmConfig.pwmCombinedChannelConfig[index].hwChannelId+1);
	}*/

	g_ftmBase[INST_FLEXTIMER_PWM1]->SC |= FTM_SC_PWMEN0_MASK | FTM_SC_PWMEN1_MASK | FTM_SC_PWMEN6_MASK | FTM_SC_PWMEN7_MASK;


}


void HAL_DisablePower()
{
	//uint8_t index;
	//ftm_pwm_param_t param;

	/*for (index = 0U; index < flexTimer_pwm1_PwmConfig.nNumCombinedPwmChannels; index++)

	{

		FTM_DRV_DisablePwmChannelOutputs(g_ftmBase[INST_FLEXTIMER_PWM1],
				flexTimer_pwm1_PwmConfig.pwmCombinedChannelConfig[index].hwChannelId);

		FTM_DRV_DisablePwmChannelOutputs(g_ftmBase[INST_FLEXTIMER_PWM1],
				flexTimer_pwm1_PwmConfig.pwmCombinedChannelConfig[index].hwChannelId+1);
	}
	*/

	g_ftmBase[INST_FLEXTIMER_PWM1]->SC &= ~(FTM_SC_PWMEN0_MASK | FTM_SC_PWMEN1_MASK | FTM_SC_PWMEN6_MASK | FTM_SC_PWMEN7_MASK);
	//FTM_DRV_DisablePwm(INST_FLEXTIMER_PWM1, &flexTimer_pwm1_PwmConfig);
}

boolean HAL_DetectObject()
{
	uint32 tmp;
	tmp = PWM_MCLOCK/HAL_AP_FREQUENCY;
	//SetPwmDutyDiv(AP_FREQ_DIV, AP_DUTY_DIV);
	//HAL_SetPwmFreq(HAL_AP_FREQUENCY);
	HAL_SetPwmPeriod(tmp);
	HAL_EnablePower();
	ST_WaitMs(2);
	ApCurrent = HAL_GetInputCurrent();
	HAL_DisablePower();

	if(ApCurrent > HAL_AP_CURRENT_THRC )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

void HAL_Coil1En_Config(boolean conf)
{
	if(conf==TRUE)
	{
		PINS_DRV_SetPins(COIL1_EN_GPIO, (1 << COIL1_EN_PIN));
	}
	else
	{
		PINS_DRV_ClearPins(COIL1_EN_GPIO, (1 << COIL1_EN_PIN));
	}

}

void HAL_Coil2En_Config(boolean conf)
{
	if(conf==TRUE)
	{
		PINS_DRV_SetPins(COIL2_EN_GPIO, (1 << COIL2_EN_PIN));
	}
	else
	{
		PINS_DRV_ClearPins(COIL2_EN_GPIO, (1 << COIL2_EN_PIN));
	}

}

void DeselectAllCoils()
{
	HAL_Coil2En_Config(FALSE);
	HAL_Coil1En_Config(FALSE);
}


void SelectCoils(uint8 index)
{

	if(index == CoilOne)
	{
		HAL_Coil2En_Config(FALSE);
		HAL_Coil1En_Config(TRUE);
	}
	else if(index == CoilTwo)
	{
		HAL_Coil1En_Config(FALSE);
		HAL_Coil2En_Config(TRUE);
	}

}

void HAL_KeyCoilSelInit()
{
	StartSysTimer2(T_PING + TIME_MARGIN);
	selectCoilIndex = CoilOne;
	//SelectCoils(CoilOne);
	maxSigStrength = 0;
	bStatePing = FALSE;
	//HAL_EnablePower();
}

void HAL_KeyCoilDetStart(Coils index)
{
	//StartTimer2(T_PING + TIME_MARGIN);
	SelectCoils(index);
	HAL_EnablePower();

}

CoilsSts HAL_GetKeyCoilDet(Coils index)
{
	CoilsSts retSts;

	retSts = CoilSelNotFinished;

	if(IsSysTimer2Expired() || bNewMessage)
	{
		if(bNewMessage)      //received a message successfully
		{
			bNewMessage = FALSE;
			if(RxPacket[0] == HEADER_SIGNAL_STRENGTH)
			{
				bStatePing = TRUE;
				SelsigStrength = RxPacket[1];
			}
		}

		if(maxSigStrength < SelsigStrength)
		{
			maxSigStrength = SelsigStrength;
			selectCoilIndex = index;
		}
		HAL_DisablePower();
		retSts = CoilSelFinishedOne;

	}
	//	if(index==CoilTwo)
	//	{
	//		retSts = CoilSelFinishedAll;
	//	}
	//	else
	//	{
	//		retSts = CoilSelFinishedOne;
	//	}
	//	StartTimer2(T_PING + TIME_MARGIN);


		//ST_WaitMs(20);

	return retSts;
}

boolean HAL_GetKeyCoilObjSts()
{
	return bStatePing;
}

uint8	HAL_GetKeyCoilSel()
{
	return selectCoilIndex;
}

void HAL_ConfigVbatSW(boolean flag)
{
	if(flag)
	{
		PINS_DRV_SetPins(VBATSW_EN_GPIO,VBATSW_EN_PIN);
	}
	else
	{
		PINS_DRV_ClearPins(VBATSW_EN_GPIO,VBATSW_EN_PIN);
	}

}

void HAL_UartSendCommand(uint8 command)
{
	//LPUART_DRV_SendData(INST_LPUART1,&command,1);
	LPUART1->DATA  = command;
	LPUART1->CTRL |= 0x00800000;
}

uint8 HAL_UartRecvSts()
{
	PWctStatus receive_data;

	receive_data = GetUartRcvData();
	//LPUART_DRV_ReceiveData(INST_LPUART1,&receive_data,1);

	return receive_data;
}

boolean HAL_GetMuteSts()
{
	uint8	PinInVal;
	boolean	MuteVal;

	PinInVal =	PINS_DRV_ReadPins(PTA);
	MuteVal = (PinInVal>>6) & 0x01;

	return MuteVal;
}

void HAL_CANEn_Config(boolean conf)
{
	if(conf==TRUE)
	{
		PINS_DRV_SetPins(CAN_EN_GPIO, (1 << CAN_EN_PIN));
	}
	else
	{
		PINS_DRV_ClearPins(CAN_EN_GPIO, (1 << CAN_EN_PIN));
	}
}

void HAL_CANSTBEn_Config(boolean conf)
{
	if(conf==TRUE)
	{
		PINS_DRV_SetPins(CAN_STBEN_GPIO, (1 << CAN_STBEN_PIN));
	}
	else
	{
		PINS_DRV_ClearPins(CAN_STBEN_GPIO, (1 << CAN_STBEN_PIN));
	}
}

void HAL_GetCanParams()
{

	Rte_Read_CGW_03_CRC_CGW_03_CRC(&CGW_03_Params.CGW_03_CRC);
	Rte_Read_CGW_03_MsgCntr_CGW_03_MsgCntr(&CGW_03_Params.CGW_03_MsgCntr);
	Rte_Read_ComfEna_ASIL_ComfEna_ASIL(&CGW_03_Params.ComfEna_ASIL);
	Rte_Read_VehState_ASIL_VehState_ASIL(&CGW_03_Params.VehState_ASIL);

	Rte_Read_CGW_WLC_CRC_CGW_WLC_CRC(&CGW_WLC_Params.CGW_WLC_CRC);
	Rte_Read_CGW_WLC_MsgCntr_CGW_WLC_MsgCntr(&CGW_WLC_Params.CGW_WLC_MsgCntr);

	Rte_Read_ComfEna_ComfEna(&CGW_02_Params.Comf_Ena);
	Rte_Read_ImobEnaReq_ImobEnaReq(&CGW_02_Params.ImobEnaReq);
	Rte_Read_VehState_VehState(&CGW_02_Params.VehState);

	Rte_Read_Yr_Yr(&CGW_TCU_01_Params.Yr);
	Rte_Read_Mth_Mth(&CGW_TCU_01_Params.Mth);
	Rte_Read_Day_Day(&CGW_TCU_01_Params.Day);
	Rte_Read_Hr_Hr(&CGW_TCU_01_Params.Hr);
	Rte_Read_Min_Min(&CGW_TCU_01_Params.Min);
	Rte_Read_Sec_Sec(&CGW_TCU_01_Params.Sec);

	Rte_Read_VehOdometer_VehOdometer(&CDC_IC_01_Params.VehOdometer);

	Rte_Read_VehSpd_VehSpd(&BCU_04_Params.VehSpd);

	Rte_Read_WLCChrgFctEnaReq_WLCChrgFctEnaReq(&CDC_WLC_Params.WLCChrgFctEnaReq);

}

void HAL_SetCanParams()
{

	Rte_Write_UsrData0_WLC_UsrData0_WLC(0xff);//NM_WLC_Params.UsrData0_WLC);
//	Rte_Write_UsrData1_WLC_UsrData1_WLC(gCanNMData);//NM_WLC_Params.UsrData1_WLC);
	Rte_Write_UsrData2_WLC_UsrData2_WLC(0xff);//NM_WLC_Params.UsrData2_WLC);
	Rte_Write_UsrData3_WLC_UsrData3_WLC(0xff);//NM_WLC_Params.UsrData3_WLC);
	Rte_Write_UsrData4_WLC_UsrData4_WLC(0xff);//NM_WLC_Params.UsrData4_WLC);
	Rte_Write_UsrData5_WLC_UsrData5_WLC(0xff);//NM_WLC_Params.UsrData5_WLC);
	Rte_Write_WLCChrgRate_WLCChrgRate(WLC_01_Params.WLCChrgRate);
	Rte_Write_WLCChrgSts_WLCChrgSts(WLC_01_Params.WLCChrgSts);
	Rte_Write_WLCCtrlSts_WLCCtrlSts(WLC_01_Params.WLCCtrlSts);
	Rte_Write_WLCFailSts_WLCFailSts(WLC_01_Params.WLCFailSts);
	Rte_Write_WLCMuteViaHW_WLCMuteViaHW(WLC_01_Params.WLCMuteViaHW);
	//Rte_Write_WLC_01_CRC_WLC_01_CRC(WLC_01_Params.WLC_01_CRC);
//	Rte_Write_WLC_01_MsgCntr_WLC_01_MsgCntr(WLC_01_Params.WLC_01_MsgCntr);
	//Rte_Write_WLC_02_CRC_WLC_02_CRC(WLC_02_Params.WLC_02_CRC);
//	Rte_Write_WLC_02_MsgCntr_WLC_02_MsgCntr(WLC_02_Params.WLC_02_MsgCntr);
	Rte_Write_WLCImobSts_WLCImobSts(WLC_02_Params.WLCImobSts);

	if(IsSysTimer8Expired())
	{
	//	//WLC_01_Params.WLCChrgRate = 2;
//		WLC_01_Params.WLC_01_MsgCntr++;
		RestartSysTimer8();
	}

	if(IsSysTimer7Expired())
	{
//		WLC_02_Params.WLC_02_MsgCntr++;
		RestartSysTimer7();
	}

}

void HAL_CanParamsInit()
{

	NM_WLC_Params.ActvWakeup_WLC = 0;
	NM_WLC_Params.NetMngtCoorn_WLC = 0;
	NM_WLC_Params.NetMngtCoorrSleepRdy_WLC = 0;
	NM_WLC_Params.PtlNetInfo_WLC = 0;
	NM_WLC_Params.RepMsgReq_WLC = 0;
	NM_WLC_Params.ResdBit1_WLC = 0;
	NM_WLC_Params.ResdBit2_WLC = 0;
	NM_WLC_Params.ScrNodId_WLC = 0;
	NM_WLC_Params.UsrData0_WLC = 0;
	NM_WLC_Params.UsrData1_WLC = 0;
	NM_WLC_Params.UsrData2_WLC = 0;
	NM_WLC_Params.UsrData3_WLC = 0;
	NM_WLC_Params.UsrData4_WLC = 0;
	NM_WLC_Params.UsrData5_WLC = 0;

	WLC_01_Params.WLCChrgRate = 0;
	WLC_01_Params.WLCChrgSts = 0;
	WLC_01_Params.WLCCtrlSts = 0;
	WLC_01_Params.WLCFailSts = FailTypeNoFailure;
	WLC_01_Params.WLCMuteViaHW = 1;
	//WLC_01_Params.WLC_01_CRC = 0;
	//WLC_01_Params.WLC_01_MsgCntr = 0;

	WLC_02_Params.WLCImobSts = Disable;
	//WLC_02_Params.WLC_02_CRC = 0;
	//WLC_02_Params.WLC_02_MsgCntr = 0;

	CGW_03_Params.CGW_03_CRC = 0;
	CGW_03_Params.CGW_03_MsgCntr = 0;
	CGW_03_Params.ComfEna_ASIL = 0;
	CGW_03_Params.VehState_ASIL = 0;

	CGW_WLC_Params.CGW_WLC_CRC = 0;
	CGW_WLC_Params.CGW_WLC_MsgCntr = 0;

	CGW_02_Params.Comf_Ena = 0;
	CGW_02_Params.ImobEnaReq = 0;
	CGW_02_Params.VehState = 0;

	CGW_TCU_01_Params.Yr 	= 0;
	CGW_TCU_01_Params.Mth 	= 0;
	CGW_TCU_01_Params.Day 	= 0;
	CGW_TCU_01_Params.Hr 	= 0;
	CGW_TCU_01_Params.Min 	= 0;
	CGW_TCU_01_Params.Sec 	= 0;

	CDC_IC_01_Params.VehOdometer 	= 0;
	BCU_04_Params.VehSpd 			= 0;
	CDC_WLC_Params.WLCChrgFctEnaReq = 0;

	CdcBtWifiCmd.CdcBtReq 			= 0;
	CdcBtWifiCmd.CdcWifiReq 		= 0;
	CdcBtWifiCmd.CdcNotifBt 		= 0x0;
	CdcBtWifiCmd.CdcNotifWifi 		= 0x0;

}

void HAL_updateLpcdCaliVal()
{
	INT_SYS_DisableIRQGlobal();

	//EEE_data[0] =  NFC_Task_LPCD_Cail();			// Get lpcd calib value

	//EEE_Write_ByteArray(&EEE_data[0],eeerom_data.user_data,32);		// write data into EEEPROM

	EEE_Write_Byte(EEE_data[0], &eeerom_data.lpcd_calib_Initval);
	INT_SYS_EnableIRQGlobal();
}

void HAL_RWEEPROM(uint8* source,uint8* target,uint16 size)
{
	uint16 offset = 0;
	for (uint16 i=0;i<size;i++)
	{
		while ((FTFC-> FSTAT & FTFC_FSTAT_CCIF_MASK) == 0){}
		*(target+offset) = *(source+offset);
		offset += 1;
	}
}

void HAL_CanSleepTJA1043()
{
    HAL_CANEn_Config(TRUE);			// configure CAN Transceiver EN High
    HAL_CANSTBEn_Config(FALSE);		// configure CAN Transceiver STB_EN low
}
uint8 HAL_ReadPinEn()
{
	uint8	PinInVal;
	boolean	MuteVal;

	PinInVal =	PINS_DRV_ReadPins(PTA);
	MuteVal = (PinInVal>>11) & 0x01;

	return MuteVal;
}

uint8 HAL_ReadPinSTB()
{
	uint8	PinInVal;
	boolean	MuteVal;

	PinInVal =	PINS_DRV_ReadPins(PTE);
	MuteVal = (PinInVal>>1) & 0x01;

	return MuteVal;
}
uint8 HAL_ReadPinRXD()
{
	uint8	PinInVal;
	boolean	MuteVal;

	PinInVal =	PINS_DRV_ReadPins(PTA);
	MuteVal = (PinInVal>>12) & 0x01;

	return MuteVal;
}

uint8 Dio_ReadChannel(uint8 channel)
{
	//		LevelSTB=1;
	//LevelRXD=0;
uint8 ret;
 if(channel==1)//PinRXD
 {

 }

 if(channel==2)//PinSTB
 {

 }

 return ret;
}
uint8 Dio_WriteChannel(uint8 channel,uint8 value)
{

}

uint32 HAL_ReadEEPROMMemory(uint8* DataBuf,uint32 LocalAddress, uint32 Length)
{
	uint32 ret = 0;
	uint8* TempAddr = (uint8*)LocalAddress;

	while(Length)
	{
		if((DataBuf == NULL) || (TempAddr == NULL))
		{
			break;
		}
		* DataBuf = * TempAddr;
		DataBuf++;
		TempAddr++;
		Length--;
	}
	return ret;
}

uint32 NvMblcokAddress[NVM_TOTAL_NUM_OF_NVRAM_BLOCKS];
void HAL_SetNvmBlcokAddress()
{
	uint8 i;

	NvMblcokAddress[1]=0x14000000;//S32K 模拟EEPROM 的起始地址，0x14000000----0x14000F80
	for(i=2;i<NVM_TOTAL_NUM_OF_NVRAM_BLOCKS;i++)
	{
		NvMblcokAddress[i]=NvMblcokAddress[i-1]+NvM_BlockDescriptorTable_at[i-1].NvBlockLength_u16+NvM_BlockDescriptorTable_at[i-1].CrcSettings*2;
	}
}


uint32 HAL_GetNvmBlockAddress(uint8 blockid)
{

 return NvMblcokAddress[blockid];
}
