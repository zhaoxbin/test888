/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Rte.c
 *           Config:  WLC.dpa
 *      ECU-Project:  WLC
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  RTE implementation file
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0781, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_Rte_0781, MD_MSR_1.1_857 */

#define RTE_CORE
#include "Os.h" /* PRQA S 0828, 0883 */ /* MD_MSR_1.1_828, MD_Rte_Os */
#include "Rte_Type.h"
#include "Rte_Main.h"

#include "Rte_BswM.h"
#include "Rte_ComM.h"
#include "Rte_Communication_Read_APP.h"
#include "Rte_Dcm.h"
#include "Rte_DemMaster_0.h"
#include "Rte_DemSatellite_0.h"
#include "Rte_Det.h"
#include "Rte_EcuM.h"
#include "Rte_NvM.h"
#include "Rte_Os_OsCore0_swc.h"
#include "Rte_SWC_WLCAPP.h"
#include "SchM_BswM.h"
#include "SchM_Can.h"
#include "SchM_CanIf.h"
#include "SchM_CanNm.h"
#include "SchM_CanSM.h"
#include "SchM_CanTp.h"
#include "SchM_Com.h"
#include "SchM_ComM.h"
#include "SchM_Dcm.h"
#include "SchM_Dem.h"
#include "SchM_Det.h"
#include "SchM_Dio.h"
#include "SchM_EcuM.h"
#include "SchM_Fee_30_SmallSector.h"
#include "SchM_Fls.h"
#include "SchM_Mcu.h"
#include "SchM_Nm.h"
#include "SchM_NvM.h"
#include "SchM_PduR.h"

#include "Rte_Hook.h"

#include "Com.h"
#if defined(IL_ASRCOM_VERSION)
# define RTE_USE_COM_TXSIGNAL_RDACCESS
#endif

#include "Rte_Cbk.h"

//S32K 相关
#include "cpu.h"
#include "flash_driver.h"
#include "hal.h"
//
/* AUTOSAR 3.x compatibility */
#if !defined (RTE_LOCAL)
# define RTE_LOCAL static
#endif


/**********************************************************************************************************************
 * API for enable / disable interrupts global
 *********************************************************************************************************************/

#if defined(osDisableGlobalKM) && !defined(RTE_DISABLE_ENHANCED_INTERRUPT_LOCK_API)
# define Rte_DisableAllInterrupts() osDisableGlobalKM()   /* MICROSAR OS */
#else
# define Rte_DisableAllInterrupts() DisableAllInterrupts()   /* AUTOSAR OS */
#endif

#if defined(osEnableGlobalKM) && !defined(RTE_DISABLE_ENHANCED_INTERRUPT_LOCK_API)
# define Rte_EnableAllInterrupts() osEnableGlobalKM()   /* MICROSAR OS */
#else
# define Rte_EnableAllInterrupts() EnableAllInterrupts()   /* AUTOSAR OS */
#endif

/**********************************************************************************************************************
 * API for enable / disable interrupts up to the systemLevel
 *********************************************************************************************************************/

#if defined(osDisableLevelKM) && !defined(RTE_DISABLE_ENHANCED_INTERRUPT_LOCK_API)
# define Rte_DisableOSInterrupts() osDisableLevelKM()   /* MICROSAR OS */
#else
# define Rte_DisableOSInterrupts() SuspendOSInterrupts()   /* AUTOSAR OS */
#endif

#if defined(osEnableLevelKM) && !defined(RTE_DISABLE_ENHANCED_INTERRUPT_LOCK_API)
# define Rte_EnableOSInterrupts() osEnableLevelKM()   /* MICROSAR OS */
#else
# define Rte_EnableOSInterrupts() ResumeOSInterrupts()   /* AUTOSAR OS */
#endif


/**********************************************************************************************************************
 * Buffers for unqueued S/R
 *********************************************************************************************************************/

#define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

VAR(BswM_ESH_RunRequest, RTE_VAR_NOINIT) Rte_BswM_Provide_BswMRteModeRequestPort_requestedMode; /* PRQA S 0850, 3408, 1504 */ /* MD_MSR_19.8, MD_Rte_3408, MD_MSR_8.10 */

#define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * TxAck/ModeSwitchAck Flags
 *********************************************************************************************************************/


#define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

VAR(Rte_AckFlagsType, RTE_VAR_NOINIT) Rte_AckFlags; /* PRQA S 0850 */ /* MD_MSR_19.8 */

#define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define Rte_AckFlagsInit() (Rte_MemClr(&Rte_AckFlags, sizeof(Rte_AckFlagsType)))

#define RTE_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

FUNC(void, RTE_CODE) Rte_MemClr(P2VAR(void, AUTOMATIC, RTE_VAR_NOINIT) ptr, uint32_least num); /* PRQA S 0850, 3447, 3408 */ /* MD_MSR_19.8, MD_Rte_3447, MD_Rte_3408 */

#define RTE_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define RTE_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Helper functions for mode management
 *********************************************************************************************************************/
FUNC(uint8, RTE_CODE) Rte_GetInternalModeIndex_Dcm_DcmCommunicationControl(Dcm_CommunicationModeType mode) /* PRQA S 3408 */ /* MD_Rte_3408 */
{
  uint8 ret;

  if (mode == 0U)
  {
    ret = 10U;
  }
  else if (mode == 1U)
  {
    ret = 7U;
  }
  else if (mode == 2U)
  {
    ret = 1U;
  }
  else if (mode == 3U)
  {
    ret = 4U;
  }
  else if (mode == 4U)
  {
    ret = 9U;
  }
  else if (mode == 5U)
  {
    ret = 6U;
  }
  else if (mode == 6U)
  {
    ret = 0U;
  }
  else if (mode == 7U)
  {
    ret = 3U;
  }
  else if (mode == 8U)
  {
    ret = 11U;
  }
  else if (mode == 9U)
  {
    ret = 8U;
  }
  else if (mode == 10U)
  {
    ret = 2U;
  }
  else if (mode == 11U)
  {
    ret = 5U;
  }
  else
  {
    ret = 12U;
  }

  return ret;
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */

FUNC(uint8, RTE_CODE) Rte_GetInternalModeIndex_Dcm_DcmControlDtcSetting(Dcm_ControlDtcSettingType mode) /* PRQA S 3408 */ /* MD_Rte_3408 */
{
  uint8 ret;

  if (mode == 0U)
  {
    ret = 1U;
  }
  else if (mode == 1U)
  {
    ret = 0U;
  }
  else
  {
    ret = 2U;
  }

  return ret;
}

FUNC(uint8, RTE_CODE) Rte_GetInternalModeIndex_Dcm_DcmDiagnosticSessionControl(Dcm_DiagnosticSessionControlType mode) /* PRQA S 3408 */ /* MD_Rte_3408 */
{
  uint8 ret;

  if (mode == 1U)
  {
    ret = 0U;
  }
  else if (mode == 2U)
  {
    ret = 2U;
  }
  else if (mode == 3U)
  {
    ret = 1U;
  }
  else
  {
    ret = 3U;
  }

  return ret;
}

FUNC(uint8, RTE_CODE) Rte_GetInternalModeIndex_Dcm_DcmEcuReset(Dcm_EcuResetType mode) /* PRQA S 3408 */ /* MD_Rte_3408 */
{
  uint8 ret;

  if (mode == 0U)
  {
    ret = 5U;
  }
  else if (mode == 1U)
  {
    ret = 1U;
  }
  else if (mode == 2U)
  {
    ret = 4U;
  }
  else if (mode == 3U)
  {
    ret = 6U;
  }
  else if (mode == 4U)
  {
    ret = 2U;
  }
  else if (mode == 5U)
  {
    ret = 3U;
  }
  else if (mode == 6U)
  {
    ret = 0U;
  }
  else
  {
    ret = 7U;
  }

  return ret;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#define RTE_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Data structures for mode management
 *********************************************************************************************************************/

VAR(BswM_ESH_Mode, RTE_VAR_NOINIT) Rte_ModeMachine_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode; /* PRQA S 3408 */ /* MD_Rte_3408 */

VAR(Dcm_CommunicationModeType, RTE_VAR_NOINIT) Rte_ModeMachine_Dcm_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f; /* PRQA S 3408 */ /* MD_Rte_3408 */
VAR(Dcm_ControlDtcSettingType, RTE_VAR_NOINIT) Rte_ModeMachine_Dcm_DcmControlDtcSetting_DcmControlDtcSetting; /* PRQA S 3408 */ /* MD_Rte_3408 */
VAR(Dcm_DiagnosticSessionControlType, RTE_VAR_NOINIT) Rte_ModeMachine_Dcm_DcmDiagnosticSessionControl_DcmDiagnosticSessionControl; /* PRQA S 3408 */ /* MD_Rte_3408 */
VAR(Dcm_EcuResetType, RTE_VAR_NOINIT) Rte_ModeMachine_Dcm_DcmEcuReset_DcmEcuReset; /* PRQA S 3408 */ /* MD_Rte_3408 */

#define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/**********************************************************************************************************************
 * Timer handling
 *********************************************************************************************************************/

#if defined OS_US2TICKS_SystemTimer
# define RTE_USEC_SystemTimer OS_US2TICKS_SystemTimer
#else
# define RTE_USEC_SystemTimer(val) ((TickType)RTE_CONST_USEC_SystemTimer_##val) /* PRQA S 0342 */ /* MD_MSR_19.13_0342 */
#endif

#if defined OS_MS2TICKS_SystemTimer
# define RTE_MSEC_SystemTimer OS_MS2TICKS_SystemTimer
#else
# define RTE_MSEC_SystemTimer(val) ((TickType)RTE_CONST_MSEC_SystemTimer_##val) /* PRQA S 0342 */ /* MD_MSR_19.13_0342 */
#endif

#if defined OS_SEC2TICKS_SystemTimer
# define RTE_SEC_SystemTimer OS_SEC2TICKS_SystemTimer
#else
# define RTE_SEC_SystemTimer(val)  ((TickType)RTE_CONST_SEC_SystemTimer_##val) /* PRQA S 0342 */ /* MD_MSR_19.13_0342 */
#endif

#define RTE_CONST_MSEC_SystemTimer_0 (0UL)
#define RTE_CONST_MSEC_SystemTimer_10 (10UL)
#define RTE_CONST_MSEC_SystemTimer_20 (20UL)
#define RTE_CONST_MSEC_SystemTimer_5 (5UL)


/**********************************************************************************************************************
 * Internal definitions
 *********************************************************************************************************************/

#define RTE_TASK_TIMEOUT_EVENT_MASK   ((EventMaskType)0x01)
#define RTE_TASK_WAITPOINT_EVENT_MASK ((EventMaskType)0x02)

/**********************************************************************************************************************
 * RTE life cycle API
 *********************************************************************************************************************/

#define RTE_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

FUNC(void, RTE_CODE) Rte_MemClr(P2VAR(void, AUTOMATIC, RTE_VAR_NOINIT) ptr, uint32_least num)
{
  P2VAR(uint8, AUTOMATIC, RTE_VAR_NOINIT) dst = (P2VAR(uint8, AUTOMATIC, RTE_VAR_NOINIT))ptr;
  uint32_least i;
  for (i = 0; i < num; i++)
  {
    dst[i] = 0;
  }
}

FUNC(void, RTE_CODE) SchM_Init(void)
{
  /* activate the tasks */
  (void)ActivateTask(OsTask_BSW_SCHM); /* PRQA S 3417 */ /* MD_Rte_Os */

  /* activate the alarms used for TimingEvents */
  (void)SetRelAlarm(Rte_Al_TE2_OsTask_BSW_SCHM_0_10ms, RTE_MSEC_SystemTimer(0) + (TickType)1, RTE_MSEC_SystemTimer(10)); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)SetRelAlarm(Rte_Al_TE2_OsTask_BSW_SCHM_0_20ms, RTE_MSEC_SystemTimer(0) + (TickType)1, RTE_MSEC_SystemTimer(20)); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)SetRelAlarm(Rte_Al_TE2_OsTask_BSW_SCHM_0_5ms, RTE_MSEC_SystemTimer(0) + (TickType)1, RTE_MSEC_SystemTimer(5)); /* PRQA S 3417 */ /* MD_Rte_Os */

}

FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  /* set default values for internal data */
  Rte_BswM_Provide_BswMRteModeRequestPort_requestedMode = 0U;

  /* reset Tx Ack Flags */
  Rte_AckFlagsInit();
  Rte_AckFlags.Rte_ModeSwitchAck_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode_Ack = 1;
  Rte_AckFlags.Rte_ModeSwitchAck_Dcm_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_Ack = 1;
  Rte_AckFlags.Rte_ModeSwitchAck_Dcm_DcmControlDtcSetting_DcmControlDtcSetting_Ack = 1;
  Rte_AckFlags.Rte_ModeSwitchAck_Dcm_DcmDiagnosticSessionControl_DcmDiagnosticSessionControl_Ack = 1;
  Rte_AckFlags.Rte_ModeSwitchAck_Dcm_DcmEcuReset_DcmEcuReset_Ack = 1;

  /* mode management initialization part 1 */

  Rte_ModeMachine_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode = RTE_MODE_BswM_ESH_Mode_STARTUP;

  Rte_ModeMachine_Dcm_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f = RTE_MODE_Dcm_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM;

  Rte_ModeMachine_Dcm_DcmControlDtcSetting_DcmControlDtcSetting = RTE_MODE_Dcm_DcmControlDtcSetting_ENABLEDTCSETTING;

  Rte_ModeMachine_Dcm_DcmDiagnosticSessionControl_DcmDiagnosticSessionControl = RTE_MODE_Dcm_DcmDiagnosticSessionControl_DEFAULT_SESSION;

  Rte_ModeMachine_Dcm_DcmEcuReset_DcmEcuReset = RTE_MODE_Dcm_DcmEcuReset_NONE;

  /* activate the tasks */
  (void)ActivateTask(OsTask_APP); /* PRQA S 3417 */ /* MD_Rte_Os */

  /* activate the alarms used for TimingEvents */
  (void)SetRelAlarm(Rte_Al_TE_OsTask_APP_0_10ms, RTE_MSEC_SystemTimer(0) + (TickType)1, RTE_MSEC_SystemTimer(10)); /* PRQA S 3417 */ /* MD_Rte_Os */

  return RTE_E_OK;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Stop(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  /* deactivate alarms */
  (void)CancelAlarm(Rte_Al_TE_OsTask_APP_0_10ms); /* PRQA S 3417 */ /* MD_Rte_Os */

  return RTE_E_OK;
}

FUNC(void, RTE_CODE) SchM_Deinit(void)
{
  /* deactivate alarms */
  (void)CancelAlarm(Rte_Al_TE2_OsTask_BSW_SCHM_0_10ms); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)CancelAlarm(Rte_Al_TE2_OsTask_BSW_SCHM_0_20ms); /* PRQA S 3417 */ /* MD_Rte_Os */
  (void)CancelAlarm(Rte_Al_TE2_OsTask_BSW_SCHM_0_5ms); /* PRQA S 3417 */ /* MD_Rte_Os */

}

FUNC(void, RTE_CODE) Rte_InitMemory(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
}

FUNC(void, RTE_CODE) SchM_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
  versioninfo->vendorID = RTE_VENDOR_ID;
  versioninfo->moduleID = RTE_MODULE_ID;
  versioninfo->sw_major_version = RTE_SW_MAJOR_VERSION;
  versioninfo->sw_minor_version = RTE_SW_MINOR_VERSION;
  versioninfo->sw_patch_version = RTE_SW_PATCH_VERSION;
}


/**********************************************************************************************************************
 * Internal/External Tx connections
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_BswM_Provide_BswMRteModeRequestPort_requestedMode(BswM_ESH_RunRequest data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  Rte_BswM_Provide_BswMRteModeRequestPort_requestedMode = *(&data);

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData0_WLC_UsrData0_WLC(UsrData0_WLC data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_UsrData0_WLC_oNM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_9b82ce18_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData1_WLC_UsrData1_WLC(UsrData1_WLC data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_UsrData1_WLC_oNM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_1b72d907_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData2_WLC_UsrData2_WLC(UsrData2_WLC data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_UsrData2_WLC_oNM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_4113e667_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData3_WLC_UsrData3_WLC(UsrData3_WLC data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_UsrData3_WLC_oNM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_c1e3f178_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData4_WLC_UsrData4_WLC(UsrData4_WLC data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_UsrData4_WLC_oNM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_f5d198a7_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData5_WLC_UsrData5_WLC(UsrData5_WLC data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_UsrData5_WLC_oNM_WLC_oNIO_ES6_RF_CAN_SR_V3_0_75218fb8_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCChrgRate_WLCChrgRate(WLCChrgRate data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_WLCChrgRate_oWLC_01_oNIO_ES6_RF_CAN_SR_V3_0_b69382aa_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCChrgSts_WLCChrgSts(WLCChrgSts data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_WLCChrgSts_oWLC_01_oNIO_ES6_RF_CAN_SR_V3_0_eda08377_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCCtrlSts_WLCCtrlSts(WLCCtrlSts data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_WLCCtrlSts_oWLC_01_oNIO_ES6_RF_CAN_SR_V3_0_a083bd17_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCFailSts_WLCFailSts(WLCFailSts data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_WLCFailSts_oWLC_01_oNIO_ES6_RF_CAN_SR_V3_0_882ea33c_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCImobSts_WLCImobSts(WLCImobSts data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_WLCImobSts_oWLC_02_oNIO_ES6_RF_CAN_SR_V3_0_77a54935_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCMuteViaHW_WLCMuteViaHW(WLCMuteViaHW data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_WLCMuteViaHW_oWLC_01_oNIO_ES6_RF_CAN_SR_V3_0_990775ce_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLC_01_CRC_WLC_01_CRC(WLC_01_CRC data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_WLC_01_CRC_oWLC_01_oNIO_ES6_RF_CAN_SR_V3_0_705754f3_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLC_01_MsgCntr_WLC_01_MsgCntr(WLC_01_MsgCntr data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_WLC_01_MsgCntr_oWLC_01_oNIO_ES6_RF_CAN_SR_V3_0_c3fc8f8f_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLC_02_MsgCntr_WLC_02_MsgCntr(WLC_02_MsgCntr data) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  ret |= Com_SendSignal(ComConf_ComSignal_WLC_02_MsgCntr_oWLC_02_oNIO_ES6_RF_CAN_SR_V3_0_15588e7e_Tx, (&data)); /* PRQA S 0850 */ /* MD_MSR_19.8 */

  return ret;
} /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */


/**********************************************************************************************************************
 * Internal/External Rx connections
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_ESH_PostRunRequest_0_requestedMode(P2VAR(BswM_ESH_RunRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data) /* PRQA S 0850, 3673, 1505, 3206 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10, MD_Rte_3206 */
{
  *data = 0U;

  return RTE_E_UNCONNECTED;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_ESH_PostRunRequest_1_requestedMode(P2VAR(BswM_ESH_RunRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data) /* PRQA S 0850, 3673, 1505, 3206 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10, MD_Rte_3206 */
{
  *data = 0U;

  return RTE_E_UNCONNECTED;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_ESH_RunRequest_0_requestedMode(P2VAR(BswM_ESH_RunRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data) /* PRQA S 0850, 3673, 1505 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  *(data) = Rte_BswM_Provide_BswMRteModeRequestPort_requestedMode;

  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Request_ESH_RunRequest_1_requestedMode(P2VAR(BswM_ESH_RunRequest, AUTOMATIC, RTE_BSWM_APPL_VAR) data) /* PRQA S 0850, 3673, 1505, 3206 */ /* MD_MSR_19.8, MD_Rte_Qac, MD_MSR_8.10, MD_Rte_3206 */
{
  *data = 0U;

  return RTE_E_UNCONNECTED;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 * Internal C/S connections
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_CheckNFCAntenna_RequestResults(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data7ByteType, AUTOMATIC, RTE_DCM_APPL_VAR) DcmDspRoutineRequestResOutSignal, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_DCM_APPL_VAR) ErrorCode) /* PRQA S 0850, 1505, 3206, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3206, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_UNCONNECTED; /* PRQA S 3197 */ /* MD_Rte_3197 */

  OpStatus = OpStatus;
  DcmDspRoutineRequestResOutSignal = DcmDspRoutineRequestResOutSignal;
  ErrorCode = ErrorCode;

  return ret;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_CheckNFCAntenna_Start(uint8 DcmDspStartRoutineInSignal, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_DCM_APPL_VAR) ErrorCode) /* PRQA S 0850, 1505, 3206, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3206, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_UNCONNECTED; /* PRQA S 3197 */ /* MD_Rte_3197 */

  DcmDspStartRoutineInSignal = DcmDspStartRoutineInSignal;
  OpStatus = OpStatus;
  ErrorCode = ErrorCode;

  return ret;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_CheckProgrammingPreCondition_Start(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_DCM_APPL_VAR) ErrorCode) /* PRQA S 0850, 1505, 3206, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3206, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_UNCONNECTED; /* PRQA S 3197 */ /* MD_Rte_3197 */
  ret=RTE_E_OK;
  OpStatus = OpStatus;
  ErrorCode = ErrorCode;

  return ret;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DemMaster_0_CBReadData_DemDataElementClass_StartApplication_ReadData(P2VAR(DataArrayType_uint8_2, AUTOMATIC, RTE_DEMMASTER_0_APPL_VAR) Data) /* PRQA S 0850, 1505, 3206, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3206, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_UNCONNECTED; /* PRQA S 3197 */ /* MD_Rte_3197 */

  uint8 testdata[2];
  Data = testdata;

  return ret;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DemSatellite_0_CBReadData_DemDataClass_LV_Battary_Voltage_ReadData(P2VAR(DataArrayType_uint8_1, AUTOMATIC, RTE_DEMSATELLITE_0_APPL_VAR) Data) /* PRQA S 0850, 1505, 3206, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3206, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_UNCONNECTED; /* PRQA S 3197 */ /* MD_Rte_3197 */
  uint8 testdata;
 // Data = Data;
  Data = testdata;
  return ret;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DemSatellite_0_CBReadData_DemDataClass_Timestamp_ReadData(P2VAR(DataArrayType_uint8_6, AUTOMATIC, RTE_DEMSATELLITE_0_APPL_VAR) Data) /* PRQA S 0850, 1505, 3206, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3206, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_UNCONNECTED; /* PRQA S 3197 */ /* MD_Rte_3197 */

  uint8 testdata[6];
  Data = testdata;

  return ret;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DemSatellite_0_CBReadData_DemDataClass_Vehicle_Speed_ReadData(P2VAR(DataArrayType_uint8_2, AUTOMATIC, RTE_DEMSATELLITE_0_APPL_VAR) Data) /* PRQA S 0850, 1505, 3206, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3206, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_UNCONNECTED; /* PRQA S 3197 */ /* MD_Rte_3197 */

  //Data = Data;


  return ret;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DemSatellite_0_CBReadData_DemDataElementClass_StartApplication_ReadData(P2VAR(DataArrayType_uint8_2, AUTOMATIC, RTE_DEMSATELLITE_0_APPL_VAR) Data) /* PRQA S 0850, 1505, 3206, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3206, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_UNCONNECTED; /* PRQA S 3197 */ /* MD_Rte_3197 */

  Data = Data;

  return ret;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DemSatellite_0_CBReadData_OccurrenceCounter_OccurenceCounter_ReadData(P2VAR(DataArrayType_uint8_1, AUTOMATIC, RTE_DEMSATELLITE_0_APPL_VAR) Data) /* PRQA S 0850, 1505, 3206, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3206, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_UNCONNECTED; /* PRQA S 3197 */ /* MD_Rte_3197 */

  Data = Data;

  return ret;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_DemSatellite_0_CBReadData_OdometerValue_OdometerValue_ReadData(P2VAR(DataArrayType_uint8_3, AUTOMATIC, RTE_DEMSATELLITE_0_APPL_VAR) Data) /* PRQA S 0850, 1505, 3206, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3206, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_UNCONNECTED; /* PRQA S 3197 */ /* MD_Rte_3197 */

  Data = Data;

  return ret;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_NvM_NvM_RpNotifyJobEnd_StartApplication_NvMBlock1_JobFinished(NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult) /* PRQA S 0850, 1505, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_OK; /* PRQA S 3197 */ /* MD_Rte_3197 */

  NvM_RpNotifyJobEnd_StartApplication_NvMBlock1_JobFinished(ServiceId, JobResult);

  return ret;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_NvM_NvM_RpNotifyJobEnd_StartApplication_NvMBlock2_JobFinished(NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult) /* PRQA S 0850, 1505, 3673 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_Qac */
{
  Std_ReturnType ret = RTE_E_OK; /* PRQA S 3197 */ /* MD_Rte_3197 */

  NvM_RpNotifyJobEnd_StartApplication_NvMBlock2_JobFinished(ServiceId, JobResult);

  return ret;
}


/**********************************************************************************************************************
 * Exclusive area access
 *********************************************************************************************************************/

FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_PWR_MODE_PSC_PROTECTION(void)
{
  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */
  SuspendAllInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
}

FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_PWR_MODE_PSC_PROTECTION(void)
{
  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */
  ResumeAllInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
}


FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_REGISTER_PROTECTION(void)
{
  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */
  SuspendAllInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
}

FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_REGISTER_PROTECTION(void)
{
  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */
  ResumeAllInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
}


FUNC(void, RTE_CODE) SchM_Enter_Mcu_MCU_VARIABLE_PROTECTION(void)
{
  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */
  SuspendAllInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
}

FUNC(void, RTE_CODE) SchM_Exit_Mcu_MCU_VARIABLE_PROTECTION(void)
{
  /* RteAnalyzer(ExclusiveArea, ALL_INTERRUPT_BLOCKING) */
  ResumeAllInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
}



/**********************************************************************************************************************
 * Mode Switch API (Rte_Switch)
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode(BswM_ESH_Mode nextMode) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  BswM_ESH_Mode currentMode;
  SuspendOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  currentMode = Rte_ModeMachine_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode;
  if (nextMode >= 5U)
  {
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    ret = RTE_E_LIMIT;
  }
  else if (currentMode >= 5U)
  {
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    ret = RTE_E_LIMIT;
  }
  else
  {
    Rte_ModeMachine_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode = nextMode;
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  return ret;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 * Mode reading API (Rte_Mode)
 *********************************************************************************************************************/

FUNC(BswM_ESH_Mode, RTE_CODE) Rte_Mode_BswM_Notification_ESH_ModeNotification_BswM_MDGP_ESH_Mode(void) /* PRQA S 3408 */ /* MD_Rte_3408 */
{
  BswM_ESH_Mode curMode;
  curMode = Rte_ModeMachine_BswM_Switch_ESH_ModeSwitch_BswM_MDGP_ESH_Mode;
  return curMode;
}


/**********************************************************************************************************************
 * Mode Switch API (Rte_Switch)
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_ComM_UM_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_currentMode(ComM_ModeType nextMode) /* PRQA S 0850, 1505, 3206 */ /* MD_MSR_19.8, MD_MSR_8.10, MD_Rte_3206 */
{
  Std_ReturnType ret = RTE_E_OK;

  nextMode = nextMode;

  return ret;
}


/**********************************************************************************************************************
 * Mode reading API (Rte_Mode)
 *********************************************************************************************************************/

FUNC(uint8, RTE_CODE) Rte_Mode_Communication_Read_APP_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f(void) /* PRQA S 3408 */ /* MD_Rte_3408 */
{
  uint8 curMode;
  curMode = Rte_ModeMachine_Dcm_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
  return curMode;
}

FUNC(uint8, RTE_CODE) Rte_Mode_Communication_Read_APP_DcmControlDtcSetting_DcmControlDtcSetting(void) /* PRQA S 3408 */ /* MD_Rte_3408 */
{
  uint8 curMode;
  curMode = Rte_ModeMachine_Dcm_DcmControlDtcSetting_DcmControlDtcSetting;
  return curMode;
}

FUNC(uint8, RTE_CODE) Rte_Mode_Communication_Read_APP_DcmEcuReset_DcmEcuReset(void) /* PRQA S 3408 */ /* MD_Rte_3408 */
{
  uint8 curMode;
  curMode = Rte_ModeMachine_Dcm_DcmEcuReset_DcmEcuReset;
  return curMode;
}


/**********************************************************************************************************************
 * Transmission/Mode Switch Acknowledgement handling (Rte_Feedback/Rte_SwitchAck)
 *********************************************************************************************************************/
//系统复位定位在这里 boot
#define FL_EEPROM_BOOT_FLG_ADDRESS	0x14000FF0ul
//#define FL_EXT_PROG_REQUEST_RECEIVED   ((uint32)0xA5B5F705ul)
uint32 FL_EXT_PROG_REQUEST_RECEIVED = 0xA5B5F705;
extern flash_ssd_config_t pSSDConfig;
FUNC(Std_ReturnType, RTE_CODE) Rte_SwitchAck_Dcm_DcmEcuReset_DcmEcuReset(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
  Std_ReturnType ret = RTE_E_TRANSMIT_ACK;

 FLASH_DRV_EEEWrite(&pSSDConfig, FL_EEPROM_BOOT_FLG_ADDRESS,4,(uint8*)&FL_EXT_PROG_REQUEST_RECEIVED);

 SystemSoftwareReset();
  return ret;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 * Mode Switch API (Rte_Switch)
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f(Dcm_CommunicationModeType nextMode) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  uint8 internalIndexNextMode = Rte_GetInternalModeIndex_Dcm_DcmCommunicationControl(nextMode);
  uint8 internalIndexCurrentMode;
  Dcm_CommunicationModeType currentMode;
  SuspendOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  currentMode = Rte_ModeMachine_Dcm_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f;
  internalIndexCurrentMode = Rte_GetInternalModeIndex_Dcm_DcmCommunicationControl(currentMode);
  if (internalIndexNextMode >= 12U)
  {
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    ret = RTE_E_LIMIT;
  }
  else if (internalIndexCurrentMode >= 12U)
  {
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    ret = RTE_E_LIMIT;
  }
  else
  {
    Rte_ModeMachine_Dcm_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f = nextMode;
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  return ret;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_DcmControlDtcSetting_DcmControlDtcSetting(Dcm_ControlDtcSettingType nextMode) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  uint8 internalIndexNextMode = Rte_GetInternalModeIndex_Dcm_DcmControlDtcSetting(nextMode);
  uint8 internalIndexCurrentMode;
  Dcm_ControlDtcSettingType currentMode;
  SuspendOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  currentMode = Rte_ModeMachine_Dcm_DcmControlDtcSetting_DcmControlDtcSetting;
  internalIndexCurrentMode = Rte_GetInternalModeIndex_Dcm_DcmControlDtcSetting(currentMode);
  if (internalIndexNextMode >= 2U)
  {
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    ret = RTE_E_LIMIT;
  }
  else if (internalIndexCurrentMode >= 2U)
  {
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    ret = RTE_E_LIMIT;
  }
  else
  {
    Rte_ModeMachine_Dcm_DcmControlDtcSetting_DcmControlDtcSetting = nextMode;
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  return ret;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_DcmDiagnosticSessionControl_DcmDiagnosticSessionControl(Dcm_DiagnosticSessionControlType nextMode) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  uint8 internalIndexNextMode = Rte_GetInternalModeIndex_Dcm_DcmDiagnosticSessionControl(nextMode);
  uint8 internalIndexCurrentMode;
  Dcm_DiagnosticSessionControlType currentMode;
  SuspendOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  currentMode = Rte_ModeMachine_Dcm_DcmDiagnosticSessionControl_DcmDiagnosticSessionControl;
  internalIndexCurrentMode = Rte_GetInternalModeIndex_Dcm_DcmDiagnosticSessionControl(currentMode);
  if (internalIndexNextMode >= 3U)
  {
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    ret = RTE_E_LIMIT;
  }
  else if (internalIndexCurrentMode >= 3U)
  {
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    ret = RTE_E_LIMIT;
  }
  else
  {
    Rte_ModeMachine_Dcm_DcmDiagnosticSessionControl_DcmDiagnosticSessionControl = nextMode;
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  return ret;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_DcmEcuReset_DcmEcuReset(Dcm_EcuResetType nextMode) /* PRQA S 0850, 1505 */ /* MD_MSR_19.8, MD_MSR_8.10 */
{
  Std_ReturnType ret = RTE_E_OK;

  uint8 internalIndexNextMode = Rte_GetInternalModeIndex_Dcm_DcmEcuReset(nextMode);
  uint8 internalIndexCurrentMode;
  Dcm_EcuResetType currentMode;
  SuspendOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  currentMode = Rte_ModeMachine_Dcm_DcmEcuReset_DcmEcuReset;
  internalIndexCurrentMode = Rte_GetInternalModeIndex_Dcm_DcmEcuReset(currentMode);
  if (internalIndexNextMode >= 7U)
  {
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    ret = RTE_E_LIMIT;
  }
  else if (internalIndexCurrentMode >= 7U)
  {
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    ret = RTE_E_LIMIT;
  }
  else
  {
    Rte_ModeMachine_Dcm_DcmEcuReset_DcmEcuReset = nextMode;
    Rte_AckFlags.Rte_ModeSwitchAck_Dcm_DcmEcuReset_DcmEcuReset_Ack = 1;
    ResumeOSInterrupts(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  return ret;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */


/**********************************************************************************************************************
 * Task bodies for RTE controlled tasks
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Task:     OsTask_APP
 * Priority: 10
 * Schedule: NON
 *********************************************************************************************************************/
TASK(OsTask_APP) /* PRQA S 3408, 1503 */ /* MD_Rte_3408, MD_MSR_14.1 */
{
  EventMaskType ev;


  /* call runnable */
  ComControl_Init1_Runnable();

  /* call runnable */
  GetCurrentComMod_Runnable();

  /* call runnable */
  GetRequestedComMod_Runnable();

  /* call runnable */
  GetMaxComMod_Runnable();

  /* call runnable */
  RequestComModeFull_Runnable();

  /* call runnable */
  RequestComModeNOFull_Runnable();

  /* call runnable */
  DemStart();

  for(;;)
  {
    (void)WaitEvent(Rte_Ev_Cyclic_OsTask_APP_0_10ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)GetEvent(OsTask_APP, &ev); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)ClearEvent(ev & (Rte_Ev_Cyclic_OsTask_APP_0_10ms)); /* PRQA S 3417 */ /* MD_Rte_Os */

    if ((ev & Rte_Ev_Cyclic_OsTask_APP_0_10ms) != (EventMaskType)0)
    {
      /* call runnable */
      ComReadandWrite_Runnable();

      /* call runnable */
      DTCProcessRunable();
    }
  }
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 * Task:     OsTask_BSW_SCHM
 * Priority: 0
 * Schedule: FULL
 *********************************************************************************************************************/
TASK(OsTask_BSW_SCHM) /* PRQA S 3408, 1503 */ /* MD_Rte_3408, MD_MSR_14.1 */
{
  EventMaskType ev;

  for(;;)
  {
    (void)WaitEvent(Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_10ms | Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_20ms | Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_5ms); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)GetEvent(OsTask_BSW_SCHM, &ev); /* PRQA S 3417 */ /* MD_Rte_Os */
    (void)ClearEvent(ev & (Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_10ms | Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_20ms | Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_5ms)); /* PRQA S 3417 */ /* MD_Rte_Os */

    if ((ev & Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_10ms) != (EventMaskType)0)
    {
      /* call runnable */
      BswM_MainFunction();

      /* call schedulable entity */
      CanNm_MainFunction();

      /* call schedulable entity */
      CanSM_MainFunction();
    }

    if ((ev & Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_5ms) != (EventMaskType)0)
    {
      /* call schedulable entity */
      CanTp_MainFunction();
    }

    if ((ev & Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_10ms) != (EventMaskType)0)
    {
      /* call schedulable entity */
      Can_MainFunction_BusOff();

      /* call schedulable entity */
      Can_MainFunction_Mode();

      /* call schedulable entity */
      Can_MainFunction_Wakeup();
    }

    if ((ev & Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_20ms) != (EventMaskType)0)
    {
      /* call runnable */
      ComM_MainFunction_0();
    }

    if ((ev & Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_10ms) != (EventMaskType)0)
    {
      /* call schedulable entity */
      Com_MainFunctionRx();

      /* call schedulable entity */
      Com_MainFunctionTx();

      /* call runnable */
      Dcm_MainFunction();

      /* call runnable */
      Dem_MasterMainFunction();

      /* call runnable */
      Dem_SatelliteMainFunction();

      /* call runnable */
      EcuM_MainFunction();
    }

    if ((ev & Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_5ms) != (EventMaskType)0)
    {
      /* call schedulable entity */
      Fee_30_SmallSector_MainFunction();
    }

    if ((ev & Rte_Ev_Cyclic2_OsTask_BSW_SCHM_0_10ms) != (EventMaskType)0)
    {
      /* call runnable */
      NvM_MainFunction();

      /* call schedulable entity */
      Fls_MainFunction();
    }
  }
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#define RTE_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_0781:  MISRA rule: 5.6
     Reason:     The name is being used as a structure/union member as well as being a label, tag or ordinary identifier.
                 The compliance to this rule is under user's control.
     Risk:       Ambiguous identifiers can lead to compiler errors / warnings.
     Prevention: Verified during compile time. If the compiler reports an error or warning, the user has to rename the objects leading to the violation.

   MD_Rte_3197:  MISRA rule: -
     Reason:     The variable is not written by the code in all possible code variants. Due to this, the variable is initialized.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_3206:  MISRA rule: -
     Reason:     The parameter's are not used by the code in all possible code variants.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_3408:  MISRA rule: 8.8
     Reason:     For the purpose of monitoring during calibration or debugging it is necessary to use non-static declarations.
                 This is covered in the MISRA C compliance section of the Rte specification.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_3447:  MISRA rule: 8.8
     Reason:     For the purpose of monitoring during calibration or debugging it is necessary to use non-static declarations.
                 This is covered in the MISRA C compliance section of the Rte specification.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_Os:
     Reason:     This justification is used as summary justification for all deviations caused by the MICROSAR OS
                 which is for testing of the RTE. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_Qac:
     Reason:     This justification is used as summary justification for all deviations caused by wrong analysis tool results.
                 The used analysis tool QAC 7.0 sometimes creates wrong messages. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

*/
