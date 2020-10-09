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

#include "uart.h"


/*
 * 	These functions provide basic uart printing helpers
 * */

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

//const lpuart_user_config_t lpuart1_InitConfig0;
/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

static uint32_t Sample_App_atoi(const uint32_t nump,
                              const uint32_t radix);
static uint8_t Sample_App_PrintVar(const uint32_t VarToPrint,
                                          const char mask);

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

static uint32_t Sample_App_atoi(const uint32_t nump,
                              const uint32_t radix)
{
    uint32_t ua, ub, uc = 0U, nlen, numInts = 0U, ind;

    if((16U == radix) && (0x0FU >= nump))
    {
        sci_a_putchar('0');
    }
    if(0U == nump)
    {
        sci_a_putchar('0');
        nlen = 1U;
    }
    else
    {
        ua = nump;
        while (ua != 0U)
        {
            ua /= (uint32_t)radix;
            numInts++;
        }
        nlen = numInts;
        while(numInts > 0U)
        {
            ua = nump;
            for(ind = 0U; ind < numInts; ind++)
            {
                ub = (uint32_t)ua / (uint32_t)radix;
                uc = (uint32_t)ua - ((uint32_t)ub * (uint32_t)radix);
                if (uc < 10U)
                {
                    uc = uc + 48U; /* 48 in ASCII is '0'; for 0..9 conversions */
                }
                else
                {
                    uc = (uc - 10U) + 65U; /* 65 in ASCII is 'A'; for HEX (A..F) conversions */
                }
                ua = ub;
            }
            sci_a_putchar((char)uc);
            numInts--;
        }
    }

    return nlen;
}

static uint8_t Sample_App_PrintVar(const uint32_t VarToPrint,
                                           const char mask)
{
	uint8_t status;

    switch(mask)
    {
        case 'd':
            (void) Sample_App_atoi(VarToPrint, 10U);
            status = E_OK;
            break;
        case 'x':
            (void) Sample_App_atoi(VarToPrint, 16U);
            status = E_OK;
            break;
        default:
        	status = E_NOT_OK;
            break;
    }

    return status;
}

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
void uart_init(){
	LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0);
	INT_SYS_SetPriority(LPUART1_RxTx_IRQn, 0x4U);
}

/**
@brief   Print a formated string to the UART, add a CR to the end of the string
@details

@return number of characters printed
@retval None

@pre None
@post None
*/
void Sample_App_Log(const uint8_t toSend[],
                    uint32_t var1,
					uint32_t var2,
					uint32_t var3,
					uint32_t var4)
{


    uint32_t ind = 0U;
    uint8_t status;
    uint8_t ctr = 0U;

    while('\0' != toSend[ind])
    {
        if('%' == toSend[ind])
        {
            switch(ctr)
            {
                case 0U:
                	status = Sample_App_PrintVar(var1, toSend[ind+1U]);
                    break;
                case 1U:
                	status = Sample_App_PrintVar(var2, toSend[ind+1U]);
                    break;
                case 2U:
                	status = Sample_App_PrintVar(var3, toSend[ind+1U]);
                    break;
                case 3U:
                	status = Sample_App_PrintVar(var4, toSend[ind+1U]);
                    break;
                default:
                	status = E_NOT_OK;
                    break;
            }
            if(E_OK == status)
            {
                ind += 2U;
                ctr++;
            }
            else
            {
                sci_a_putchar(toSend[ind]);
                ind++;
            }
        }
        else
        {
            sci_a_putchar(toSend[ind]);
            ind++;
        }
    }
}
void Sample_App_String_Log(const uint8_t toSend[],
                    const uint8_t *var1,
					const uint8_t *var2,
					const uint8_t *var3,
					const uint8_t *var4)
{


    uint32_t ind = 0U;
    uint8_t status;
    uint8_t ctr = 0U;
    while('\0' != toSend[ind])
    {
        if('%' == toSend[ind])
        {
            switch(ctr)
            {
                case 0U:
                    UART_MESSAGE(var1);
                    status = E_OK;
                    break;
                case 1U:
                    UART_MESSAGE(var2);
                    status = E_OK;
                    break;
                case 2U:
                    UART_MESSAGE(var3);
                    status = E_OK;
                    break;
                case 3U:
                    UART_MESSAGE(var4);
                    status = E_OK;
                    break;
                default:
                	status = E_NOT_OK;
                    break;
            }
            if(E_OK == status)
            {
                ind += 2U;
                ctr++;
            }
            else
            {
                sci_a_putchar(toSend[ind]);
                ind++;
            }
        }
        else
        {
            sci_a_putchar(toSend[ind]);
            ind++;
        }
    }
}

#ifdef NCI_DEBUG
uint8_t buffer_printing(uint8_t *pbuff, uint16_t buffSize)
{
	uint16_t loopCounter=0;
	if(buffSize<3){
		return NFC_ERROR;
	}

	for(loopCounter=0;loopCounter<pbuff[2]+3;loopCounter++){
		UART_MESSAGE_1(" %x", pbuff[loopCounter]);
	}
	return SUCCESS;
}
#endif

void sci_a_putchar (uint8_t ch){
	uint32_t bytesRemaining;
	LPUART_DRV_SendDataBlocking(INST_LPUART1, &(ch), 1,1000);
	/*check if uart is busy */
	LPUART_DRV_GetTransmitStatus(INST_LPUART1, &bytesRemaining);
	if (bytesRemaining != 0)
	{
		LPUART_DRV_SendDataBlocking(INST_LPUART1, (uint8_t *)errorMsg, sizeof(errorMsg),1000);
	}
}
