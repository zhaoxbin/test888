/*
 * EEEPROM_io_ctl.h
 *
 *  Created on: 2020Äê2ÔÂ20ÈÕ
 *      Author: jiangxl
 */

#ifndef EEEPROM_IO_CTL_H_
#define EEEPROM_IO_CTL_H_

int EEE_Write_Byte(uint8 data, uint8* target);
int EEE_Write_ByteArray(uint8* source,uint8* target,uint16 size);
int EEE_Write_int32(int data, int* target);
int EEE_Write_float(float data, float* target);
int EEE_Write_double(double data, double* target);




#endif /* EEEPROM_IO_CTL_H_ */
