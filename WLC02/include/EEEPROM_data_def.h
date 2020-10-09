/*
 * EEEPROM_data_def.h
 *
 *  Created on: 2020Äê2ÔÂ20ÈÕ
 *      Author: jiangxl
 */

#include "defines.h"

#ifndef EEEPROM_DATA_DEF_H_
#define EEEPROM_DATA_DEF_H_

#define USER_DATA_SIZE			127u
#define Read_Finger_SIZE		12u
#define VehManufPartNum_SIZE 	11u
#define ECU_ManufDate_SIZE 		3u
#define ECU_SerialNum_SIZE 		10u
#define VIN_SIZE 				17u
#define RepairShopFP_SIZE		12u

typedef struct
{
	uint8 lpcd_calib_Initval;			// 0
	uint8 user_data[USER_DATA_SIZE];	// 127 bytes reserved for wct1013 parameters
	uint8 Did_F15B[Read_Finger_SIZE];
	uint8 Did_F187[VehManufPartNum_SIZE];
	uint8 Did_F18B[ECU_ManufDate_SIZE];
	uint8 Did_F18C[ECU_SerialNum_SIZE];
	uint8 Did_F190[VIN_SIZE];				// VIN
	uint8 Did_F198[RepairShopFP_SIZE];		// Repair Shop FingerPrint
} eeerom_data_t;

extern __attribute__ ((section(".eeeprom"))) eeerom_data_t eeerom_data;

#endif /* EEEPROM_DATA_DEF_H_ */
