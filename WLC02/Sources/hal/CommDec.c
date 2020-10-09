/*
 * CommDec.c
 *
 *  Created on: 2019年7月5日
 *      Author: jiangxl
 */

//******************************************************************************
//  Wireless Power----power Transmitter
//  Author:  jiangxiaoliang(jiangxiaoliang@semi.crmicro.com)
//  Company: Dis co.
//  Date:    April 2016
//******************************************************************************
#include "Cpu.h"
#include "defines.h"
#include "global.h"
#include "systemDef.h"

//static BYTE number_detect=0;										// 解出的码元个数
//static BYTE data_detect=0;											// number_detect=1				data_detect=0 -> "0"		data_detect=1 -> "1"
																								// number_detect=2				0 -> "0""0"  1 -> "0""1"  2 -> "1""0"  3 -> "1""1"

//static BYTE judge = 0;													//		  CommDlyCnt[3]   [2]    [1]       [0]
																								//		 ______________         ______              _
																								//		|              |       |      |            |
																								//		|              |       |      |            |
																								// ___|              |_______|      |____________|
																								//                   ^       ^      ^            ^
																								//                   |       |      |            |
																								//       judge =     3       2      1            0
																								//
static uint8 data_method = 0;										// 0:Preamble  1:Header  2:Message  3:Checksum

uint8 preamble=0;
uint8 Header=0;
//unsigned char Message[16]={0};
uint8 ByteMessage=0;
uint8 checksum=1;
uint8 receive_counter=0;

//unsigned char data_temp = 0;
//unsigned char data_detect_old = 0xFF;	//前一刻数据

//unsigned short xor_temp =0;

//unsigned char checkout=0;
//unsigned short checkrow =0;

char message_numb = 0;				//Message个数
char message_count = 0;				//Message计数
//BYTE packet_count=0;
//BYTE out_count=0;

//static uint16 CommUsCountD=0;
static uint16 CommUsDelay=0;
//static BYTE CommDlyCnt[2]={0};
//static BYTE PacketNum=0;

DEC_DETECT_NUMTypeDef LastCode;

#if 1
uint16 GetCommUsDelay()
{
	return CommUsDelay;
}

#if 1
void variable_clear()
{
	data_method = 0;   // 0为preamble，1为Header，2为Message，3为checksum
	receive_counter = 0;
	preamble = 0;
	Header = 0;
	CommDlyCnt[0] = 0;
	CommDlyCnt[1] = 0;
	ByteMessage = 0;
	checksum =1;
	message_numb = 0;
	message_count = 0;
}
#endif

DEC_DETECT_NUMTypeDef CodeDecoder()
{
	if(CommDlyCnt[0] > LONG_1K_TWO)		//当前值大于1K两倍阈值
	{// 错误信号
		LastCode = CODE_DECODER_NULL;
		variable_clear();
		return CODE_DECODER_NULL;
	}
	else if((data_method == 0)&&((CommDlyCnt[0] > LONG_1K_MAX)||(CommDlyCnt[0] < LONG_2K_MIN)))
	{ // 如果处于preamble，当前值大于1K最大阈值或者小于2K最小阈值，判断为错误信号
		LastCode = CODE_DECODER_NULL;
		variable_clear();
		return CODE_DECODER_NULL;
	}
	else if(CommDlyCnt[0]>LONG_1K_MIN && (CommDlyCnt[0]<LONG_1K_MAX))	//介于1K阈值判断范围内
	{ //确定的0值
		LastCode = CODE_DECODER_0;
		//GPIOC->ODR ^= GPIO_PIN_3;
		return CODE_DECODER_0;
	}
	else if((CommDlyCnt[0]<LONG_2K_MAX) && (CommDlyCnt[0]>LONG_2K_MIN))	//介于2K阈值判断范围内
	{ //确定为1的半个值
		if((CommDlyCnt[1] < LONG_2K_MAX) && (CommDlyCnt[1]>LONG_2K_MIN))	//
		{
			LastCode = CODE_DECODER_1;
			CommDlyCnt[0] = 0;
			CommDlyCnt[1] = 0;
//			GPIOC->ODR ^= GPIO_PIN_3;
			return CODE_DECODER_1;	//判断为1个码元
		}
		else
		{
				return CODE_DECODER_NULL;
		}
	}
	return CODE_DECODER_NULL;
}

#if 1
DEC_RESULT_TypeDef CommDecoder(uint8 *packet)
{
//	char error = 0;
	int i;


	if(CODE_DECODER_NULL != CodeDecoder())
	{
				// data_method:0为preamble，1为Header，2为Message，3为checksum
		switch(data_method)
		{
			case 0: // preamble
				if(LastCode == CODE_DECODER_0)	//如果检测到"0"
				{
					if((preamble&0x7F)==0x7F)
					{ //preamble满足7个"1"码元
						data_method = 1;		//跳转到Header
					}
					else
					{		//如果不满足7个"1"
						preamble = 0;				//清除数据
					}
				}
				else if(LastCode == CODE_DECODER_1)		//如果检测到"1"
				{
					preamble = (preamble << 1) + 1;
				}
				break;
			case 1: // 1为Header
				receive_counter++;
								//计算message的长度
				if(receive_counter == 10)
				{
					if(LastCode==CODE_DECODER_1)						//判断Stop
					{
						data_method = 2;		// 跳转到Message
						checksum = 1;
					}
					else
					{
						variable_clear();
					}

					if(Header < 0x20)
					{
						message_numb = 1;
					}
					else if(Header < 0x80)
					{
						message_numb = Header/16;
					}
					else if(Header < 0xE0)
					{
						message_numb = Header/8 - 8;
					}
					else
					{
						message_numb = Header/4 - 36;
					}
//					PacketNum = 0;
					packet[0] = Header;			//将Header存入缓存
//					PacketNum++;
					receive_counter = 0;
				}
				else if(receive_counter<9)
				{
					if(LastCode==CODE_DECODER_0)
					{
						Header = Header>>1;
					}
					else if(LastCode==CODE_DECODER_1)
					{
						Header = Header>>1 | 0x80;
						checksum += 1;
					}
				}
				else if(receive_counter==9)
				{
					if(LastCode!=(checksum&0x01))
					{
						variable_clear();
					}
				}
				break;
			case 2: //Message
				if((receive_counter == 0)&&(LastCode != CODE_DECODER_0))		// first "0"
				{
					variable_clear();
				}
				else if(receive_counter < 9)
				{
					if(LastCode == CODE_DECODER_1)
					{
						//Message[message_count] += (1 << (receive_counter-1));
						ByteMessage += 1 << (receive_counter-1);
//						checkout++;
						checksum++;
					}
				}
				else if(receive_counter == 9)
				{
					if(LastCode != (checksum&0x01))
					{
						variable_clear();
					}
				}


				if(receive_counter == 10)
				{
					if(LastCode != CODE_DECODER_1)		// stop bit
					{
						variable_clear();
					}
					else
					{
						//Message[message_count] += (1 << receive_counter);
						packet[message_count+1] = ByteMessage;
						receive_counter = 0;
						ByteMessage = 0;
						checksum = 1;
						message_count++;

//						if(message_count==6)
//						{
//							ByteMessage = ByteMessage;
//						}

						if(message_count >= message_numb)
						{
							data_method = 3;
							message_count = 0;
						}
					}
				}
				else
				{
					receive_counter++;
				}
				break;
			case 3://checksum
				if((receive_counter == 0)&&(LastCode != CODE_DECODER_0))
				{
//					error = 1;
					variable_clear();
				}
				else if(receive_counter < 9)
				{
					if(LastCode == CODE_DECODER_1)
					{
						//checksum += (1 << receive_counter);
						ByteMessage += 1<<(receive_counter-1);
//						checkout++;
						checksum++;
					}
				}
				else if(receive_counter == 9)
				{
					if(LastCode != (checksum&0x01))
					{
						//checksum += (1 << receive_counter);
						variable_clear();
					}
				}

				if(receive_counter == 10)
				{
					if(LastCode != CODE_DECODER_1)		// stop bit
					{
						variable_clear();
					}
					else
					{
						packet[message_numb+1] = ByteMessage;
						data_method = 4;
						ByteMessage = packet[0];
						for(i = 1; i < message_numb+1; i++)
						{
							ByteMessage ^= packet[i];
						}

						if(ByteMessage == packet[message_numb+1])
						{ //校验通过
							return DECODER_SUCCESS;
						}
						else
						{ //校验失败
							return DECODER_SUCCESS_CHECKSUMFAIL;
						}

						checksum = 1;
					}
					receive_counter = 0;
				}
				else
				{
					receive_counter++;
				}
				break;

//			case 4:
//				ByteMessage = packet[0];
//				for(i = 1; i < message_numb+1; i++)
//				{
//					ByteMessage ^= packet[i];
//				}
//
//				if(ByteMessage == packet[message_numb+1])
//				{ //校验通过
//					return DECODER_SUCCESS;
//				}
//				else
//				{ //校验失败
//					return DECODER_SUCCESS_CHECKSUMFAIL;
//				}

//			break;

			default: //error
//				error = 1;
				variable_clear();
				break;
		}
	}
	return DECODER_FAIL;

}

#endif

#endif

#if 0

/***********************************************/
/*  COMM Interrupt Handler                     */
/*                                             */
/***********************************************/

@near @interrupt void EXTI3 (void)
{
	WORD tmp;
//  disableInterrupts();
	//GPIO_Init(GPIOD,GPIO_PIN_5,GPIO_MODE_OUT_PP_LOW_FAST);//将PD5配置为输出模式，用来清IO中断
	//GPIO_Init(GPIOD,GPIO_PIN_5,GPIO_MODE_IN_PU_IT);				//将PD5配置为输入中断模式
	tmp = GetUsCount();

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
	#if 1
	if(DECODER_SUCCESS==CommDecoder(RxPacket))
	{
		variable_clear();
		DecoderFinish = 1;
		GPIOC->ODR ^= GPIO_PIN_3;		// TEST_PIN, if decode successfully, toggle pc3
	}
	#endif
}

#endif

