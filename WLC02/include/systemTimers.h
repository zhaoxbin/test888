/*
 * systemTimers.h
 *
 *  Created on: 2019Äê6ÔÂ28ÈÕ
 *      Author: jiangxl
 */

#ifndef SYSTEMTIMERS_H_
#define SYSTEMTIMERS_H_

#include "defines.h"

void ST_TimerUpdate(void);
uint16_t ST_GetTimerTick(void);
uint16_t ST_GetUsTimerTick(void);
void ST_AddTickTimer(uint16_t wTicks);
uint16_t ST_GetElapasedTime(uint16_t wLastTick);
void ST_WaitMs(uint16_t wNumMs);

void StopAllKeyTimers(void);
void StopKeyTimer1(void);
void StartKeyTimer1(uint16_t msTimeOutPeriod);
void RestartKeyTimer1(void);
boolean IsKeyTimer1Expired(void);
void StopKeyTimer2(void);
void StartKeyTimer2(uint16_t msTimeOutPeriod);
void RestartKeyTimer2(void);
boolean IsKeyTimer2Expired(void);

void StopKeyTimer3(void);
void StartKeyTimer3(uint16_t msTimeOutPeriod);
void RestartKeyTimer3(void);
boolean IsKeyTimer3Expired(void);

void StopKeyTimer4(void);
void StartKeyTimer4(uint16_t msTimeOutPeriod);
void RestartKeyTimer4(void);
boolean IsKeyTimer4Expired(void);


void StopAllSysTimers(void);
void StopSysTimer1(void);
void StartSysTimer1(uint16_t msTimeOutPeriod);
void RestartSysTimer1(void);
boolean IsSysTimer1Expired(void);
void StopSysTimer2(void);
void StartSysTimer2(uint16_t msTimeOutPeriod);
void RestartSysTimer2(void);
boolean IsSysTimer2Expired(void);

void StopSysTimer3(void);
void StartSysTimer3(uint16_t msTimeOutPeriod);
void RestartSysTimer3(void);
boolean IsSysTimer3Expired(void);

void StopSysTimer4(void);
void StartSysTimer4(uint16_t msTimeOutPeriod);
void RestartSysTimer4(void);
boolean IsSysTimer4Expired(void);

void StopSysTimer5(void);
void StartSysTimer5(uint16_t msTimeOutPeriod);
void RestartSysTimer5(void);
boolean IsSysTimer5Expired(void);

void StopSysTimer6(void);
void StartSysTimer6(uint16_t msTimeOutPeriod);
void RestartSysTimer6(void);
boolean IsSysTimer6Expired(void);

void StopSysTimer7(void);
void StartSysTimer7(uint16_t msTimeOutPeriod);
void RestartSysTimer7(void);
boolean IsSysTimer7Expired(void);

void StopSysTimer8(void);
void StartSysTimer8(uint16_t msTimeOutPeriod);
void RestartSysTimer8(void);
boolean IsSysTimer8Expired(void);

void StopSysTimer9(void);
void StartSysTimer9(uint16_t msTimeOutPeriod);
void RestartSysTimer9(void);
boolean IsSysTimer9Expired(void);

void StopSysTimer10(void);
void StartSysTimer10(uint16_t msTimeOutPeriod);
void RestartSysTimer10(void);
boolean IsSysTimer10Expired(void);

#endif /* SYSTEMTIMERS_H_ */
