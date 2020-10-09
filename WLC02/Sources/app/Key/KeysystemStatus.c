/*
 * KeysystemStatus.c
 *
 *  Created on: 2020��2��10��
 *      Author: jiangxl
 */


#include "Cpu.h"
#include "global.h"
#include "Qi_spec.h"
#include "systemDef.h"
#include "hal.h"
#include "systemTask.h"
#include "systemStatus.h"
#include "systemTimers.h"



KWctStatus KChrgSts;



KWctStatus GetKeyChargeSts()
{
	return KChrgSts;
}


void SetKeyChargeSts(KWctStatus chrgsts)
{
	KChrgSts = chrgsts;
}


