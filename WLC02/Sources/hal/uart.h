/*
   (c) NXP B.V. 2009-2014. All rights reserved.

   Disclaimer
   1. The NXP Software/Source Code is provided to Licensee "AS IS" without any
      warranties of any kind. NXP makes no warranties to Licensee and shall not
      indemnify Licensee or hold it harmless for any reason related to the NXP
      Software/Source Code or otherwise be liable to the NXP customer. The NXP
      customer acknowledges and agrees that the NXP Software/Source Code is
      provided AS-IS and accepts all risks of utilizing the NXP Software under
      the conditions set forth according to this disclaimer.

   2. NXP EXPRESSLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING,
      BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
      FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT OF INTELLECTUAL PROPERTY
      RIGHTS. NXP SHALL HAVE NO LIABILITY TO THE NXP CUSTOMER, OR ITS
      SUBSIDIARIES, AFFILIATES, OR ANY OTHER THIRD PARTY FOR ANY DAMAGES,
      INCLUDING WITHOUT LIMITATION, DAMAGES RESULTING OR ALLEGDED TO HAVE
      RESULTED FROM ANY DEFECT, ERROR OR OMMISSION IN THE NXP SOFTWARE/SOURCE
      CODE, THIRD PARTY APPLICATION SOFTWARE AND/OR DOCUMENTATION, OR AS A
      RESULT OF ANY INFRINGEMENT OF ANY INTELLECTUAL PROPERTY RIGHT OF ANY
      THIRD PARTY. IN NO EVENT SHALL NXP BE LIABLE FOR ANY INCIDENTAL,
      INDIRECT, SPECIAL, EXEMPLARY, PUNITIVE, OR CONSEQUENTIAL DAMAGES
      (INCLUDING LOST PROFITS) SUFFERED BY NXP CUSTOMER OR ITS SUBSIDIARIES,
      AFFILIATES, OR ANY OTHER THIRD PARTY ARISING OUT OF OR RELATED TO THE NXP
      SOFTWARE/SOURCE CODE EVEN IF NXP HAS BEEN ADVISED OF THE POSSIBILITY OF
      SUCH DAMAGES.

   3. NXP reserves the right to make changes to the NXP Software/Sourcecode any
      time, also without informing customer.

   4. Licensee agrees to indemnify and hold harmless NXP and its affiliated
      companies from and against any claims, suits, losses, damages,
      liabilities, costs and expenses (including reasonable attorney's fees)
      resulting from Licensee's and/or Licensee customer's/licensee's use of the
      NXP Software/Source Code.

 */
#ifndef UART_HEADER
#define UART_HEADER

#include <status.h>
#include "hal.h"

/*! @brief Function Declarations */
void uart_init();
void uart_console_init(void);
char sci_a_getchar(void);
void sci_a_putchar(uint8_t ch);
int  sci_a_getchar_present(void);
void sci_wait_tx(void);
uint8_t buffer_printing(uint8_t *pbuff, uint16_t buffSize);
void Sample_App_Log(const uint8_t toSend[],
					uint32_t var1,
                    uint32_t var2,
					uint32_t var3,
					uint32_t var4);
void Sample_App_String_Log(const uint8_t toSend[],
		const	uint8_t *var1,
		const	uint8_t *var2,
		const	uint8_t *var3,
		const	uint8_t *var4);

/*! @brief Macro Defines */
#ifdef UART_PRINTING
#define UART_MESSAGE(str)                    Sample_App_Log((const uint8_t* )str, 0U, 0U, 0U, 0U)
#define UART_MESSAGE_1(str, v1)              Sample_App_Log((const uint8_t* )str, v1, 0U, 0U, 0U)
#define UART_MESSAGE_2(str, v1, v2)          Sample_App_Log((const uint8_t* )str, v1, v2, 0U, 0U)
#define UART_MESSAGE_1STR(str, s1)           Sample_App_String_Log((const uint8_t* )str,(const uint8_t* ) s1, 0U, 0U, 0U)
#define UART_MESSAGE_2STR(str, s1, s2)       Sample_App_String_Log((const uint8_t* )str,(const uint8_t* ) s1, (const uint8_t* )s2, 0U, 0U)
#define print_buf(x,y,z)  {int loop; UART_MESSAGE(x); for(loop=0;loop<z;loop++) UART_MESSAGE_1("%x ", y[loop]); UART_MESSAGE("\n\r");}
#else
#define UART_MESSAGE(str)
#define UART_MESSAGE_1(str, v1)
#define UART_MESSAGE_2(str, v1, v2)
#define UART_MESSAGE_1STR(str, s1)
#define UART_MESSAGE_2STR(str, s1, s2)
#define print_buf(x,y,z)
#endif

#ifdef NCI_DEBUG
#define NCI_UART_MESSAGE(str)                    Sample_App_Log((const uint8_t* )str, 0U, 0U, 0U, 0U)
#define NCI_UART_MESSAGE_1(str, v1)              Sample_App_Log((const uint8_t* )str, v1, 0U, 0U, 0U)
#define NCI_BUFFER_PRINT(buff,size)	buffer_printing(buff, size)
#endif


#define errorMsg "UART Connection timed out"
#define E_OK 1
#define E_NOT_OK 0
#define TX_BUF_SIZE     0x1000U

#endif //UART_HEADER
