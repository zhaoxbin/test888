/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Os
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Alarm_Lcfg.c
 *   Generation Time: 2020-09-01 09:22:55
 *           Project: WLC - Version 1.0
 *          Delivery: CBD1900162_D00
 *      Tool Version: DaVinci Configurator (beta) 5.19.29
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 ! BETA VERSION                                                                                                       !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 ! This version of DaVinci Configurator Pro and/or the related Basic Software Package is BETA software.               !
 ! BETA Software is basically operable, but not sufficiently tested, verified and/or qualified for use in series      !
 ! production and/or in vehicles operating on public or non-public roads.                                             !
 ! In particular, without limitation, BETA Software may cause unpredictable ECU behavior, may not provide all         !
 ! functions necessary for use in series production and/or may not comply with quality requirements which are         !
 ! necessary according to the state of the art. BETA Software must not be used in series production.                  !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**********************************************************************************************************************/

/* PRQA S 0777, 0779, 0828 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2, MD_MSR_Dir1.1 */

#define OS_ALARM_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Alarm_Lcfg.h"
#include "Os_Alarm.h"

/* Os kernel module dependencies */
#include "Os_Application_Lcfg.h"
#include "Os_Cfg.h"
#include "Os_Common.h"
#include "Os_Counter_Lcfg.h"
#include "Os_Counter.h"
#include "Os_Task_Lcfg.h"
#include "Os_Timer.h"

/* Os hal dependencies */


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic alarm data: Rte_Al_TE2_OsTask_BSW_SCHM_0_10ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_10ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE2_OsTask_BSW_SCHM_0_20ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_20ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE2_OsTask_BSW_SCHM_0_5ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_5ms_Dyn;

/*! Dynamic alarm data: Rte_Al_TE_OsTask_APP_0_10ms */
OS_LOCAL VAR(Os_AlarmType, OS_VAR_NOINIT) OsCfg_Alarm_Rte_Al_TE_OsTask_APP_0_10ms_Dyn;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Alarm configuration data: Rte_Al_TE2_OsTask_BSW_SCHM_0_10ms */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_10ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_10ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERPIT_2_COUNTER(OsCfg_Counter_SystemTimer),
    //  /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ OS_APPID2MASK(SystemApplication_OsCore0),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_BSW_SCHM,
  /* .Mask  = */ Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_10ms
};

/*! Alarm configuration data: Rte_Al_TE2_OsTask_BSW_SCHM_0_20ms */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_20ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_20ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERPIT_2_COUNTER(OsCfg_Counter_SystemTimer),
 //     /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ OS_APPID2MASK(SystemApplication_OsCore0),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_BSW_SCHM,
  /* .Mask  = */ Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_20ms
};

/*! Alarm configuration data: Rte_Al_TE2_OsTask_BSW_SCHM_0_5ms */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_5ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_5ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERPIT_2_COUNTER(OsCfg_Counter_SystemTimer),
  //    /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ OS_APPID2MASK(SystemApplication_OsCore0),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_BSW_SCHM,
  /* .Mask  = */ Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_5ms
};

/*! Alarm configuration data: Rte_Al_TE_OsTask_APP_0_10ms */
CONST(Os_AlarmSetEventConfigType, OS_CONST) OsCfg_Alarm_Rte_Al_TE_OsTask_APP_0_10ms =
{
  /* .Alarm = */
  {
    /* .Job                   = */
    {
      /* .Dyn      = */ OS_ALARM_CASTDYN_ALARM_2_JOB(OsCfg_Alarm_Rte_Al_TE_OsTask_APP_0_10ms_Dyn),
      /* .Counter  = */ OS_COUNTER_CASTCONFIG_TIMERPIT_2_COUNTER(OsCfg_Counter_SystemTimer),
  //    /* .Callback = */ Os_AlarmActionSetEvent
    },
    /* .Autostart             = */
    {
      /* .AlarmTime        = */ 0uL, /* 0.0 sec */
      /* .Cycle            = */ 0uL, /* 0.0 sec */
      /* .ApplicationModes = */ OS_APPMODE_NONE,
      /* .AlarmMode        = */ OS_ALARMMODE_ABSOLUTE
    },
    /* .AccessingApplications = */ OS_APPID2MASK(SystemApplication_OsCore0),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore0
  },
  /* .Task  = */ &OsCfg_Task_OsTask_APP,
  /* .Mask  = */ Rte_Ev_Cyclic_OsTask_APP_0_10ms
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Object reference table for alarms. */
CONSTP2CONST(Os_AlarmConfigType, OS_CONST, OS_CONST) OsCfg_AlarmRefs[OS_ALARMID_COUNT + 1] =  /* PRQA S 4521 */ /* MD_Os_Rule10.1_4521 */
{
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_10ms),
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_20ms),
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE2_OsTask_BSW_SCHM_0_5ms),
  OS_ALARM_CASTCONFIG_ALARMSETEVENT_2_ALARM(OsCfg_Alarm_Rte_Al_TE_OsTask_APP_0_10ms),
  NULL_PTR
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: Os_Alarm_Lcfg.c
 *********************************************************************************************************************/
