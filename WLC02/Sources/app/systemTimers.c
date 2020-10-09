/*
 * systemTimers.c
 *
 *  Created on: 2019Äê6ÔÂ28ÈÕ
 *      Author: jiangxl
 */


#include "Cpu.h"
#include "hal.h"

#include "systemTimers.h"


volatile static uint16_t  SysmsGenTimeoutPeriod1;// = 0;
volatile static uint16_t  SysmsGenStartPoint1;// = 0;
volatile static boolean   bSysStartTimer1;// = FALSE;

volatile static uint16_t  SysmsGenTimeoutPeriod2;// = 0;
volatile static uint16_t  SysmsGenStartPoint2;// = 0;
volatile static boolean   bSysStartTimer2;// = FALSE;

volatile static uint16_t  SysmsGenTimeoutPeriod3;// = 0;
volatile static uint16_t  SysmsGenStartPoint3;// = 0;
volatile static boolean   bSysStartTimer3;// = FALSE;

volatile static uint16_t  SysmsGenTimeoutPeriod4;// = 0;
volatile static uint16_t  SysmsGenStartPoint4;// = 0;
volatile static boolean   bSysStartTimer4;// = FALSE;

volatile static uint16_t  SysmsGenTimeoutPeriod5;// = 0;
volatile static uint16_t  SysmsGenStartPoint5;// = 0;
volatile static boolean   bSysStartTimer5;// = FALSE;


volatile static uint16_t  SysmsGenTimeoutPeriod6;// = 0;
volatile static uint16_t  SysmsGenStartPoint6;// = 0;
volatile static boolean   bSysStartTimer6;// = FALSE;

volatile static uint16_t  SysmsGenTimeoutPeriod7;// = 0;
volatile static uint16_t  SysmsGenStartPoint7;// = 0;
volatile static boolean   bSysStartTimer7;// = FALSE;

volatile static uint16_t  SysmsGenTimeoutPeriod8;// = 0;
volatile static uint16_t  SysmsGenStartPoint8;// = 0;
volatile static boolean   bSysStartTimer8;// = FALSE;

volatile static uint16_t  SysmsGenTimeoutPeriod9;// = 0;
volatile static uint16_t  SysmsGenStartPoint9;// = 0;
volatile static boolean   bSysStartTimer9;// = FALSE;

volatile static uint16_t  SysmsGenTimeoutPeriod10;// = 0;
volatile static uint16_t  SysmsGenStartPoint10;// = 0;
volatile static boolean   bSysStartTimer10;// = FALSE;

volatile static uint16_t  KeymsGenTimeoutPeriod1;// = 0;
volatile static uint16_t  KeymsGenStartPoint1;// = 0;
volatile static boolean   bKeyStartTimer1;// = FALSE;

volatile static uint16_t  KeymsGenTimeoutPeriod2;// = 0;
volatile static uint16_t  KeymsGenStartPoint2;// = 0;
volatile static boolean   bKeyStartTimer2;// = FALSE;

volatile static uint16_t  KeymsGenTimeoutPeriod3;// = 0;
volatile static uint16_t  KeymsGenStartPoint3;// = 0;
volatile static boolean   bKeyStartTimer3;// = FALSE;

volatile static uint16_t  KeymsGenTimeoutPeriod4;// = 0;
volatile static uint16_t  KeymsGenStartPoint4;// = 0;
volatile static boolean   bKeyStartTimer4;// = FALSE;


volatile static uint16_t gST_wTimerTick;
volatile static uint16_t gST_wUsTimerTick;


void ST_TimerUpdate(void)
{
	gST_wUsTimerTick++;
	if(gST_wUsTimerTick%100==0)
	{
		gST_wTimerTick++;
	}
}

uint16_t ST_GetTimerTick(void)
{
	return gST_wTimerTick;
}

uint16_t ST_GetUsTimerTick(void)
{
	return gST_wUsTimerTick;
}

void ST_AddTickTimer(uint16_t wTicks)
{
	//uint8 sts = HAL_DisableIRQ();
	gST_wTimerTick += wTicks;
	//HAL_RestoreIRQ(sts);
}

uint16_t ST_GetElapasedTime(uint16_t wLastTick)
{
	uint16_t ticks = ST_GetTimerTick();
	uint16_t wElapsedTime;

	if (ticks >= wLastTick)
	{
		wElapsedTime = ticks - wLastTick;
	}
	else
	{
	    //counter wrap
		wElapsedTime = ticks + (65536UL - wLastTick);
	}

	return wElapsedTime;
}

void ST_WaitMs(uint16_t wNumMs)
{
	uint16_t ticks = ST_GetTimerTick();

	while (ST_GetElapasedTime(ticks) < wNumMs)
	{
	    //Kick the watch dog
		HAL_KickWatchDog();

	}
}


void StopAllKeyTimers()
{
  bKeyStartTimer1 = FALSE;
  bKeyStartTimer2 = FALSE;
  bKeyStartTimer3 = FALSE;
  bKeyStartTimer4 = FALSE;
}

//================== Key Timer1 ===========================

void StopKeyTimer1()
{
  bKeyStartTimer1= FALSE;
}

void StartKeyTimer1(uint16_t msTimeOutPeriod)
{
  KeymsGenTimeoutPeriod1 = msTimeOutPeriod;
  KeymsGenStartPoint1 = ST_GetTimerTick();
  bKeyStartTimer1 = TRUE;
}

void RestartKeyTimer1()
{
  KeymsGenStartPoint1 = ST_GetTimerTick();
}


boolean IsKeyTimer1Expired()
{

  if(bKeyStartTimer1)
  {
    if(ST_GetElapasedTime(KeymsGenStartPoint1) > KeymsGenTimeoutPeriod1)
    {
      return TRUE;
    }
  }

  return FALSE;
}

//================== Key Timer2 ===========================

void StopKeyTimer2()
{
  bKeyStartTimer2= FALSE;
}

void StartKeyTimer2(uint16_t msTimeOutPeriod)
{
  KeymsGenTimeoutPeriod2 = msTimeOutPeriod;
  KeymsGenStartPoint2 = ST_GetTimerTick();
  bKeyStartTimer2 = TRUE;
}

void RestartKeyTimer2()
{
  KeymsGenStartPoint2 = ST_GetTimerTick();
}


boolean IsKeyTimer2Expired()
{

  if(bKeyStartTimer2)
  {
    if(ST_GetElapasedTime(KeymsGenStartPoint2) > KeymsGenTimeoutPeriod2)
    {
      return TRUE;
    }
  }

  return FALSE;
}

//================== Key Timer3 ===========================

void StopKeyTimer3()
{
  bKeyStartTimer3= FALSE;
}

void StartKeyTimer3(uint16_t msTimeOutPeriod)
{
  KeymsGenTimeoutPeriod3 = msTimeOutPeriod;
  KeymsGenStartPoint3 = ST_GetTimerTick();
  bKeyStartTimer3 = TRUE;
}

void RestartKeyTimer3()
{
  KeymsGenStartPoint3 = ST_GetTimerTick();
}

boolean IsKeyTimer3Expired()
{

  if(bKeyStartTimer3)
  {
    if(ST_GetElapasedTime(KeymsGenStartPoint3) > KeymsGenTimeoutPeriod3)
    {
      return TRUE;
    }
  }

  return FALSE;
}

//================== Key Timer4 ===========================

void StopKeyTimer4()
{
  bKeyStartTimer4= FALSE;
}

void StartKeyTimer4(uint16_t msTimeOutPeriod)
{
  KeymsGenTimeoutPeriod4 = msTimeOutPeriod;
  KeymsGenStartPoint4 = ST_GetTimerTick();
  bKeyStartTimer4 = TRUE;
}

void RestartKeyTimer4()
{
  KeymsGenStartPoint4 = ST_GetTimerTick();
}


boolean IsKeyTimer4Expired()
{

  if(bKeyStartTimer4)
  {
    if(ST_GetElapasedTime(KeymsGenStartPoint4) > KeymsGenTimeoutPeriod4)
    {
      return TRUE;
    }
  }

  return FALSE;
}


void StopAllSysTimers()
{
  bSysStartTimer1 = FALSE;
  bSysStartTimer2 = FALSE;
  bSysStartTimer3 = FALSE;
  bSysStartTimer4 = FALSE;
  bSysStartTimer5 = FALSE;
}

//================== Sys Timer1 ===========================

void StopSysTimer1()
{
  bSysStartTimer1= FALSE;
}

void StartSysTimer1(uint16_t msTimeOutPeriod)
{
  SysmsGenTimeoutPeriod1 = msTimeOutPeriod;
  SysmsGenStartPoint1 = ST_GetTimerTick();
  bSysStartTimer1 = TRUE;
}

void RestartSysTimer1()
{
  SysmsGenStartPoint1 = ST_GetTimerTick();
}

boolean IsSysTimer1Expired()
{
  if(bSysStartTimer1)
  {
    if(ST_GetElapasedTime(SysmsGenStartPoint1) > SysmsGenTimeoutPeriod1)
    {
      return TRUE;
    }
  }

  return FALSE;
}

//================== Sys Timer2 ===========================

void StopSysTimer2()
{
  bSysStartTimer2 = FALSE;
}

void StartSysTimer2(uint16_t msTimeOutPeriod)
{
  SysmsGenTimeoutPeriod2 = msTimeOutPeriod;
  SysmsGenStartPoint2 = ST_GetTimerTick();
  bSysStartTimer2 = TRUE;
}

void RestartSysTimer2()
{
  SysmsGenStartPoint2 = ST_GetTimerTick();
}

boolean IsSysTimer2Expired()
{
  if(bSysStartTimer2)
  {
    if(ST_GetElapasedTime(SysmsGenStartPoint2) > SysmsGenTimeoutPeriod2)
    {
      return TRUE;
    }
  }

  return FALSE;
}

//================== Sys Timer3 ===========================

void StopSysTimer3()
{
  bSysStartTimer3= FALSE;
}

void StartSysTimer3(uint16_t msTimeOutPeriod)
{
  SysmsGenTimeoutPeriod3 = msTimeOutPeriod;
  SysmsGenStartPoint3 = ST_GetTimerTick();
  bSysStartTimer3 = TRUE;
}

void RestartSysTimer3()
{
  SysmsGenStartPoint3 = ST_GetTimerTick();
}

boolean IsSysTimer3Expired()
{
  if(bSysStartTimer3)
  {
    if(ST_GetElapasedTime(SysmsGenStartPoint3) > SysmsGenTimeoutPeriod3)
    {
      return TRUE;
    }
  }

  return FALSE;
}

//================== Sys Timer4 ===========================

void StopSysTimer4()
{
  bSysStartTimer4= FALSE;
}

void StartSysTimer4(uint16_t msTimeOutPeriod)
{
  SysmsGenTimeoutPeriod4 = msTimeOutPeriod;
  SysmsGenStartPoint4 = ST_GetTimerTick();
  bSysStartTimer4 = TRUE;
}

void RestartSysTimer4()
{
  SysmsGenStartPoint4 = ST_GetTimerTick();
}

boolean IsSysTimer4Expired()
{
  if(bSysStartTimer4)
  {
    if(ST_GetElapasedTime(SysmsGenStartPoint4) > SysmsGenTimeoutPeriod4)
    {
      return TRUE;
    }
  }

  return FALSE;
}

//================== Sys Timer5 ===========================

void StopSysTimer5()
{
  bSysStartTimer5= FALSE;
}

void StartSysTimer5(uint16_t msTimeOutPeriod)
{
  SysmsGenTimeoutPeriod5 = msTimeOutPeriod;
  SysmsGenStartPoint5 = ST_GetTimerTick();
  bSysStartTimer5 = TRUE;
}

void RestartSysTimer5()
{
  SysmsGenStartPoint5 = ST_GetTimerTick();
}

boolean IsSysTimer5Expired()
{
  if(bSysStartTimer5)
  {
    if(ST_GetElapasedTime(SysmsGenStartPoint5) > SysmsGenTimeoutPeriod5)
    {
      return TRUE;
    }
  }

  return FALSE;
}

//================== Sys Timer6 ===========================

void StopSysTimer6()
{
  bSysStartTimer6= FALSE;
}

void StartSysTimer6(uint16_t msTimeOutPeriod)
{
  SysmsGenTimeoutPeriod6 = msTimeOutPeriod;
  SysmsGenStartPoint6 = ST_GetTimerTick();
  bSysStartTimer6 = TRUE;
}

void RestartSysTimer6()
{
  SysmsGenStartPoint6 = ST_GetTimerTick();
}

boolean IsSysTimer6Expired()
{
  if(bSysStartTimer6)
  {
    if(ST_GetElapasedTime(SysmsGenStartPoint6) > SysmsGenTimeoutPeriod6)
    {
      return TRUE;
    }
  }

  return FALSE;
}

//================== Sys Timer7 ===========================

void StopSysTimer7()
{
  bSysStartTimer7= FALSE;
}

void StartSysTimer7(uint16_t msTimeOutPeriod)
{
  SysmsGenTimeoutPeriod7 = msTimeOutPeriod;
  SysmsGenStartPoint7 = ST_GetTimerTick();
  bSysStartTimer7 = TRUE;
}

void RestartSysTimer7()
{
  SysmsGenStartPoint7 = ST_GetTimerTick();
}

boolean IsSysTimer7Expired()
{
  if(bSysStartTimer7)
  {
    if(ST_GetElapasedTime(SysmsGenStartPoint7) > SysmsGenTimeoutPeriod7)
    {
      return TRUE;
    }
  }

  return FALSE;
}

//================== Sys Timer8 ===========================

void StopSysTimer8()
{
  bSysStartTimer8= FALSE;
}

void StartSysTimer8(uint16_t msTimeOutPeriod)
{
  SysmsGenTimeoutPeriod8 = msTimeOutPeriod;
  SysmsGenStartPoint8 = ST_GetTimerTick();
  bSysStartTimer8 = TRUE;
}

void RestartSysTimer8()
{
  SysmsGenStartPoint8 = ST_GetTimerTick();
}

boolean IsSysTimer8Expired()
{
  if(bSysStartTimer8)
  {
    if(ST_GetElapasedTime(SysmsGenStartPoint8) > SysmsGenTimeoutPeriod8)
    {
      return TRUE;
    }
  }

  return FALSE;
}


//================== Sys Timer9 ===========================

void StopSysTimer9()
{
  bSysStartTimer9= FALSE;
}

void StartSysTimer9(uint16_t msTimeOutPeriod)
{
  SysmsGenTimeoutPeriod9 = msTimeOutPeriod;
  SysmsGenStartPoint9 = ST_GetTimerTick();
  bSysStartTimer9 = TRUE;
}

void RestartSysTimer9()
{
  SysmsGenStartPoint9 = ST_GetTimerTick();
}

boolean IsSysTimer9Expired()
{
  if(bSysStartTimer9)
  {
    if(ST_GetElapasedTime(SysmsGenStartPoint9) > SysmsGenTimeoutPeriod9)
    {
      return TRUE;
    }
  }

  return FALSE;
}


//================== Sys Timer10 ===========================

void StopSysTimer10()
{
  bSysStartTimer10 = FALSE;
}

void StartSysTimer10(uint16_t msTimeOutPeriod)
{
  SysmsGenTimeoutPeriod10 = msTimeOutPeriod;
  SysmsGenStartPoint10 = ST_GetTimerTick();
  bSysStartTimer10 = TRUE;
}

void RestartSysTimer10()
{
  SysmsGenStartPoint10 = ST_GetTimerTick();
}

boolean IsSysTimer10Expired()
{
  if(bSysStartTimer10)
  {
    if(ST_GetElapasedTime(SysmsGenStartPoint10) > SysmsGenTimeoutPeriod10)
    {
      return TRUE;
    }
  }

  return FALSE;
}


