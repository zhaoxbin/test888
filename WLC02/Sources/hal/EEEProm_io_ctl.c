/*
 * EEEProm_io_ctl.c
 *
 *  Created on: 2020Äê2ÔÂ20ÈÕ
 *      Author: jiangxl
 */

#include "defines.h"
#include "Cpu.h"

int EEE_Write_Byte(uint8 data, uint8* target)
{
	while ((FTFC-> FSTAT & FTFC_FSTAT_CCIF_MASK) == 0){}
	*target=data;
	return 0;
}


int EEE_Write_ByteArray(uint8* source,uint8* target,uint16 size)
{
	uint16 cycles=size/4;
	uint16 remain=size%4;
	uint16 offset=0;
	for (uint16 i=0;i<cycles;i++)
	{
		while ((FTFC-> FSTAT & FTFC_FSTAT_CCIF_MASK) == 0){}
		*(uint16*)(target+offset)=*(uint16*)(source+offset);
		offset+=4;
	}

	for (uint16 i=0;i<remain;i++)
	{
			while ((FTFC-> FSTAT & FTFC_FSTAT_CCIF_MASK) == 0){}
			*(target+offset)=*(uint8*)(source+offset);
			offset+=1;
		}

	return 0;
}


int EEE_Write_int32(int data, int* target)
{
	while ((FTFC-> FSTAT & FTFC_FSTAT_CCIF_MASK) == 0){}
	*target=data;
	return 0;
}


int EEE_Write_float(float data, float* target)
{
	while ((FTFC-> FSTAT & FTFC_FSTAT_CCIF_MASK) == 0){}
	*target=data;
	return 0;
}


int EEE_Write_double(double data, double* target)
{
	while ((FTFC-> FSTAT & FTFC_FSTAT_CCIF_MASK) == 0){}
	return 0;
}

