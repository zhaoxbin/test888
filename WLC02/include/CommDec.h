/*
 * CommDec.h
 *
 *  Created on: 2019Äê7ÔÂ8ÈÕ
 *      Author: jiangxl
 */

#ifndef COMMDEC_H_
#define COMMDEC_H_

#include "defines.h"
#include "SystemDef.h"

void variable_clear(void);
uint16 GetCommUsDelay(void);
DEC_DETECT_NUMTypeDef CodeDecoder();
DEC_RESULT_TypeDef CommDecoder(uint8 *packet);


#endif /* COMMDEC_H_ */
