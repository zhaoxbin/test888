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
 *             File:  Rte_Communication_Read_APP.h
 *           Config:  WLC.dpa
 *      ECU-Project:  WLC
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Application header file for SW-C <Communication_Read_APP>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_COMMUNICATION_READ_APP_H
# define _RTE_COMMUNICATION_READ_APP_H

# ifndef RTE_CORE
#  ifdef RTE_APPLICATION_HEADER_FILE
#   error Multiple application header files included.
#  endif
#  define RTE_APPLICATION_HEADER_FILE
#  ifndef RTE_PTR2ARRAYBASETYPE_PASSING
#   define RTE_PTR2ARRAYBASETYPE_PASSING
#  endif
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_Communication_Read_APP_Type.h"
# include "Rte_DataHandleType.h"

# ifndef RTE_CORE

#  include "Com.h"


# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_CGW_03_CRC_CGW_03_CRC (0U)
#  define Rte_InitValue_CGW_03_MsgCntr_CGW_03_MsgCntr (0U)
#  define Rte_InitValue_CGW_WLC_CRC_CGW_WLC_CRC (0U)
#  define Rte_InitValue_CGW_WLC_MsgCntr_CGW_WLC_MsgCntr (0U)
#  define Rte_InitValue_ComfEna_ComfEna (0U)
#  define Rte_InitValue_ComfEna_ASIL_ComfEna_ASIL (0U)
#  define Rte_InitValue_Day_Day (0U)
#  define Rte_InitValue_Hr_Hr (0U)
#  define Rte_InitValue_ImobEnaReq_ImobEnaReq (0U)
#  define Rte_InitValue_Min_Min (0U)
#  define Rte_InitValue_Mth_Mth (0U)
#  define Rte_InitValue_Sec_Sec (0U)
#  define Rte_InitValue_UsrData0_WLC_UsrData0_WLC (0U)
#  define Rte_InitValue_UsrData1_WLC_UsrData1_WLC (0U)
#  define Rte_InitValue_UsrData2_WLC_UsrData2_WLC (0U)
#  define Rte_InitValue_UsrData3_WLC_UsrData3_WLC (0U)
#  define Rte_InitValue_UsrData4_WLC_UsrData4_WLC (0U)
#  define Rte_InitValue_UsrData5_WLC_UsrData5_WLC (0U)
#  define Rte_InitValue_VehOdometer_VehOdometer (0U)
#  define Rte_InitValue_VehSpd_VehSpd (0U)
#  define Rte_InitValue_VehState_VehState (0U)
#  define Rte_InitValue_VehState_ASIL_VehState_ASIL (0U)
#  define Rte_InitValue_WLCChrgFctEnaReq_WLCChrgFctEnaReq (0U)
#  define Rte_InitValue_WLCChrgRate_WLCChrgRate (0U)
#  define Rte_InitValue_WLCChrgSts_WLCChrgSts (0U)
#  define Rte_InitValue_WLCCtrlSts_WLCCtrlSts (0U)
#  define Rte_InitValue_WLCFailSts_WLCFailSts (0U)
#  define Rte_InitValue_WLCImobSts_WLCImobSts (0U)
#  define Rte_InitValue_WLCMuteViaHW_WLCMuteViaHW (FALSE)
#  define Rte_InitValue_WLC_01_CRC_WLC_01_CRC (0U)
#  define Rte_InitValue_WLC_01_MsgCntr_WLC_01_MsgCntr (0U)
#  define Rte_InitValue_WLC_02_CRC_WLC_02_CRC (0U)
#  define Rte_InitValue_WLC_02_MsgCntr_WLC_02_MsgCntr (0U)
#  define Rte_InitValue_Yr_Yr (0U)
# endif


# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData0_WLC_UsrData0_WLC(UsrData0_WLC data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData1_WLC_UsrData1_WLC(UsrData1_WLC data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData2_WLC_UsrData2_WLC(UsrData2_WLC data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData3_WLC_UsrData3_WLC(UsrData3_WLC data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData4_WLC_UsrData4_WLC(UsrData4_WLC data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_UsrData5_WLC_UsrData5_WLC(UsrData5_WLC data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCChrgRate_WLCChrgRate(WLCChrgRate data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCChrgSts_WLCChrgSts(WLCChrgSts data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCCtrlSts_WLCCtrlSts(WLCCtrlSts data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCFailSts_WLCFailSts(WLCFailSts data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCImobSts_WLCImobSts(WLCImobSts data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLCMuteViaHW_WLCMuteViaHW(WLCMuteViaHW data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLC_01_CRC_WLC_01_CRC(WLC_01_CRC data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLC_01_MsgCntr_WLC_01_MsgCntr(WLC_01_MsgCntr data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLC_02_MsgCntr_WLC_02_MsgCntr(WLC_02_MsgCntr data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(uint8, RTE_CODE) Rte_Mode_Communication_Read_APP_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(uint8, RTE_CODE) Rte_Mode_Communication_Read_APP_DcmControlDtcSetting_DcmControlDtcSetting(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(uint8, RTE_CODE) Rte_Mode_Communication_Read_APP_DcmEcuReset_DcmEcuReset(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_CGW_03_CRC_CGW_03_CRC Rte_Read_Communication_Read_APP_CGW_03_CRC_CGW_03_CRC
#  define Rte_Read_Communication_Read_APP_CGW_03_CRC_CGW_03_CRC(data) (Com_ReceiveSignal(ComConf_ComSignal_CGW_03_CRC_oCGW_03_oNIO_ES6_RF_CAN_SR_V3_0_bd877a03_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_CGW_03_MsgCntr_CGW_03_MsgCntr Rte_Read_Communication_Read_APP_CGW_03_MsgCntr_CGW_03_MsgCntr
#  define Rte_Read_Communication_Read_APP_CGW_03_MsgCntr_CGW_03_MsgCntr(data) (Com_ReceiveSignal(ComConf_ComSignal_CGW_03_MsgCntr_oCGW_03_oNIO_ES6_RF_CAN_SR_V3_0_3e603ff9_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_CGW_WLC_CRC_CGW_WLC_CRC Rte_Read_Communication_Read_APP_CGW_WLC_CRC_CGW_WLC_CRC
#  define Rte_Read_Communication_Read_APP_CGW_WLC_CRC_CGW_WLC_CRC(data) (Com_ReceiveSignal(ComConf_ComSignal_CGW_WLC_CRC_oCGW_WLC_oNIO_ES6_RF_CAN_SR_V3_0_67a87047_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_CGW_WLC_MsgCntr_CGW_WLC_MsgCntr Rte_Read_Communication_Read_APP_CGW_WLC_MsgCntr_CGW_WLC_MsgCntr
#  define Rte_Read_Communication_Read_APP_CGW_WLC_MsgCntr_CGW_WLC_MsgCntr(data) (Com_ReceiveSignal(ComConf_ComSignal_CGW_WLC_MsgCntr_oCGW_WLC_oNIO_ES6_RF_CAN_SR_V3_0_2e39b55e_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_ComfEna_ComfEna Rte_Read_Communication_Read_APP_ComfEna_ComfEna
#  define Rte_Read_Communication_Read_APP_ComfEna_ComfEna(data) (Com_ReceiveSignal(ComConf_ComSignal_ComfEna_oCGW_02_oNIO_ES6_RF_CAN_SR_V3_0_1a60ba8c_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_ComfEna_ASIL_ComfEna_ASIL Rte_Read_Communication_Read_APP_ComfEna_ASIL_ComfEna_ASIL
#  define Rte_Read_Communication_Read_APP_ComfEna_ASIL_ComfEna_ASIL(data) (Com_ReceiveSignal(ComConf_ComSignal_ComfEna_ASIL_oCGW_03_oNIO_ES6_RF_CAN_SR_V3_0_daac19b6_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_Day_Day Rte_Read_Communication_Read_APP_Day_Day
#  define Rte_Read_Communication_Read_APP_Day_Day(data) (Com_ReceiveSignal(ComConf_ComSignal_Day_oCGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_76626f65_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_Hr_Hr Rte_Read_Communication_Read_APP_Hr_Hr
#  define Rte_Read_Communication_Read_APP_Hr_Hr(data) (Com_ReceiveSignal(ComConf_ComSignal_Hr_oCGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_f5c3e99f_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_ImobEnaReq_ImobEnaReq Rte_Read_Communication_Read_APP_ImobEnaReq_ImobEnaReq
#  define Rte_Read_Communication_Read_APP_ImobEnaReq_ImobEnaReq(data) (Com_ReceiveSignal(ComConf_ComSignal_ImobEnaReq_oCGW_02_oNIO_ES6_RF_CAN_SR_V3_0_a2f30745_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_Min_Min Rte_Read_Communication_Read_APP_Min_Min
#  define Rte_Read_Communication_Read_APP_Min_Min(data) (Com_ReceiveSignal(ComConf_ComSignal_Min_oCGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_c05ffcb3_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_Mth_Mth Rte_Read_Communication_Read_APP_Mth_Mth
#  define Rte_Read_Communication_Read_APP_Mth_Mth(data) (Com_ReceiveSignal(ComConf_ComSignal_Mth_oCGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_a0768b21_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_Sec_Sec Rte_Read_Communication_Read_APP_Sec_Sec
#  define Rte_Read_Communication_Read_APP_Sec_Sec(data) (Com_ReceiveSignal(ComConf_ComSignal_Sec_oCGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_48a1d09a_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_VehOdometer_VehOdometer Rte_Read_Communication_Read_APP_VehOdometer_VehOdometer
#  define Rte_Read_Communication_Read_APP_VehOdometer_VehOdometer(data) (Com_ReceiveSignal(ComConf_ComSignal_VehOdometer_oCDC_IC_01_oNIO_ES6_RF_CAN_SR_V3_0_c4f897da_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_VehSpd_VehSpd Rte_Read_Communication_Read_APP_VehSpd_VehSpd
#  define Rte_Read_Communication_Read_APP_VehSpd_VehSpd(data) (Com_ReceiveSignal(ComConf_ComSignal_VehSpd_oBCU_04_oNIO_ES6_RF_CAN_SR_V3_0_91cf0813_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_VehState_VehState Rte_Read_Communication_Read_APP_VehState_VehState
#  define Rte_Read_Communication_Read_APP_VehState_VehState(data) (Com_ReceiveSignal(ComConf_ComSignal_VehState_oCGW_02_oNIO_ES6_RF_CAN_SR_V3_0_70d412f9_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_VehState_ASIL_VehState_ASIL Rte_Read_Communication_Read_APP_VehState_ASIL_VehState_ASIL
#  define Rte_Read_Communication_Read_APP_VehState_ASIL_VehState_ASIL(data) (Com_ReceiveSignal(ComConf_ComSignal_VehState_ASIL_oCGW_03_oNIO_ES6_RF_CAN_SR_V3_0_3e049202_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_WLCChrgFctEnaReq_WLCChrgFctEnaReq Rte_Read_Communication_Read_APP_WLCChrgFctEnaReq_WLCChrgFctEnaReq
#  define Rte_Read_Communication_Read_APP_WLCChrgFctEnaReq_WLCChrgFctEnaReq(data) (Com_ReceiveSignal(ComConf_ComSignal_WLCChrgFctEnaReq_oCDC_WLC_oNIO_ES6_RF_CAN_SR_V3_0_e37de241_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Read_Yr_Yr Rte_Read_Communication_Read_APP_Yr_Yr
#  define Rte_Read_Communication_Read_APP_Yr_Yr(data) (Com_ReceiveSignal(ComConf_ComSignal_Yr_oCGW_TCU_01_oNIO_ES6_RF_CAN_SR_V3_0_cdf9e710_Rx, (data))) /* PRQA S 3453 */ /* MD_MSR_19.7 */


/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Write_UsrData0_WLC_UsrData0_WLC Rte_Write_Communication_Read_APP_UsrData0_WLC_UsrData0_WLC
#  define Rte_Write_UsrData1_WLC_UsrData1_WLC Rte_Write_Communication_Read_APP_UsrData1_WLC_UsrData1_WLC
#  define Rte_Write_UsrData2_WLC_UsrData2_WLC Rte_Write_Communication_Read_APP_UsrData2_WLC_UsrData2_WLC
#  define Rte_Write_UsrData3_WLC_UsrData3_WLC Rte_Write_Communication_Read_APP_UsrData3_WLC_UsrData3_WLC
#  define Rte_Write_UsrData4_WLC_UsrData4_WLC Rte_Write_Communication_Read_APP_UsrData4_WLC_UsrData4_WLC
#  define Rte_Write_UsrData5_WLC_UsrData5_WLC Rte_Write_Communication_Read_APP_UsrData5_WLC_UsrData5_WLC
#  define Rte_Write_WLCChrgRate_WLCChrgRate Rte_Write_Communication_Read_APP_WLCChrgRate_WLCChrgRate
#  define Rte_Write_WLCChrgSts_WLCChrgSts Rte_Write_Communication_Read_APP_WLCChrgSts_WLCChrgSts
#  define Rte_Write_WLCCtrlSts_WLCCtrlSts Rte_Write_Communication_Read_APP_WLCCtrlSts_WLCCtrlSts
#  define Rte_Write_WLCFailSts_WLCFailSts Rte_Write_Communication_Read_APP_WLCFailSts_WLCFailSts
#  define Rte_Write_WLCImobSts_WLCImobSts Rte_Write_Communication_Read_APP_WLCImobSts_WLCImobSts
#  define Rte_Write_WLCMuteViaHW_WLCMuteViaHW Rte_Write_Communication_Read_APP_WLCMuteViaHW_WLCMuteViaHW
#  define Rte_Write_WLC_01_CRC_WLC_01_CRC Rte_Write_Communication_Read_APP_WLC_01_CRC_WLC_01_CRC
#  define Rte_Write_WLC_01_MsgCntr_WLC_01_MsgCntr Rte_Write_Communication_Read_APP_WLC_01_MsgCntr_WLC_01_MsgCntr
#  define Rte_Write_WLC_02_CRC_WLC_02_CRC Rte_Write_Communication_Read_APP_WLC_02_CRC_WLC_02_CRC
#  define Rte_Write_Communication_Read_APP_WLC_02_CRC_WLC_02_CRC(data) (RTE_E_OK) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Write_WLC_02_MsgCntr_WLC_02_MsgCntr Rte_Write_Communication_Read_APP_WLC_02_MsgCntr_WLC_02_MsgCntr


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Mode_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f Rte_Mode_Communication_Read_APP_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f
#  define Rte_Mode_DcmControlDtcSetting_DcmControlDtcSetting Rte_Mode_Communication_Read_APP_DcmControlDtcSetting_DcmControlDtcSetting
#  define Rte_Mode_DcmEcuReset_DcmEcuReset Rte_Mode_Communication_Read_APP_DcmEcuReset_DcmEcuReset


# endif /* !defined(RTE_CORE) */


# define Communication_Read_APP_START_SEC_CODE
# include "Communication_Read_APP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_ComReadandWrite_Runnable ComReadandWrite_Runnable
#  define RTE_RUNNABLE_DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_BootloaderVersion_ReadData DataServices_DcmDspData_BootloaderVersion_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_BootloaderVersion_ReadDataLength DataServices_DcmDspData_BootloaderVersion_ReadDataLength
#  define RTE_RUNNABLE_DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_ConfigurarionFingerprint_ReadData DataServices_DcmDspData_ConfigurarionFingerprint_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_ConfigurarionFingerprint_WriteData DataServices_DcmDspData_ConfigurarionFingerprint_WriteData
#  define RTE_RUNNABLE_DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_ECUConfigurarion_ReadData DataServices_DcmDspData_ECUConfigurarion_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_ECUConfigurarion_WriteData DataServices_DcmDspData_ECUConfigurarion_WriteData
#  define RTE_RUNNABLE_DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_ECUManufacturingDate_ReadData DataServices_DcmDspData_ECUManufacturingDate_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_ECUProgrammingDate_ReadData DataServices_DcmDspData_ECUProgrammingDate_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_ECUSerialNumber_ReadData DataServices_DcmDspData_ECUSerialNumber_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_NFCFunction_ConditionCheckRead DataServices_DcmDspData_NFCFunction_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_NFCFunction_ReadData DataServices_DcmDspData_NFCFunction_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_NFCFunction_ReadDataLength DataServices_DcmDspData_NFCFunction_ReadDataLength
#  define RTE_RUNNABLE_DataServices_DcmDspData_NFCFunction_WriteData DataServices_DcmDspData_NFCFunction_WriteData
#  define RTE_RUNNABLE_DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_ReadActiveDiagSession_ReadData DataServices_DcmDspData_ReadActiveDiagSession_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_ReadFingerprint_ReadData DataServices_DcmDspData_ReadFingerprint_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_RepairShopFingerPrint_ReadData DataServices_DcmDspData_RepairShopFingerPrint_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_RepairShopFingerPrint_WriteData DataServices_DcmDspData_RepairShopFingerPrint_WriteData
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemName_ConditionCheckRead DataServices_DcmDspData_SystemName_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemName_ReadData DataServices_DcmDspData_SystemName_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemName_ReadDataLength DataServices_DcmDspData_SystemName_ReadDataLength
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSESVNumber_ReadData DataServices_DcmDspData_SystemSESVNumber_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSESVNumber_ReadDataLength DataServices_DcmDspData_SystemSESVNumber_ReadDataLength
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSHV_ConditionCheckRead DataServices_DcmDspData_SystemSHV_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSHV_ReadData DataServices_DcmDspData_SystemSHV_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSHV_ReadDataLength DataServices_DcmDspData_SystemSHV_ReadDataLength
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_SystemSupplierIdData_ReadData DataServices_DcmDspData_SystemSupplierIdData_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VIN_ConditionCheckRead DataServices_DcmDspData_VIN_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_VIN_ReadData DataServices_DcmDspData_VIN_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VIN_WriteData DataServices_DcmDspData_VIN_WriteData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrationBaseline_ReadData DataServices_DcmDspData_VM_CalibrationBaseline_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrationBaseline_WriteData DataServices_DcmDspData_VM_CalibrationBaseline_WriteData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_SoftwarBaseline_ReadData DataServices_DcmDspData_VM_SoftwarBaseline_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_SofwarePartNumber_ReadData DataServices_DcmDspData_VM_SofwarePartNumber_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_SparepartNumber_ReadData DataServices_DcmDspData_VM_SparepartNumber_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_SparepartNumber_WriteData DataServices_DcmDspData_VM_SparepartNumber_WriteData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_Specialdatabaseline_ReadData DataServices_DcmDspData_VM_Specialdatabaseline_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength
#  define RTE_RUNNABLE_DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_DcmDspData_WLCCtrlSts_ReadData DataServices_DcmDspData_WLCCtrlSts_ReadData
#  define RTE_RUNNABLE_DataServices_DcmDspData_WLCCtrlSts_ReadDataLength DataServices_DcmDspData_WLCCtrlSts_ReadDataLength
#  define RTE_RUNNABLE_DataServices_DcmDspData_WLCCtrlSts_WriteData DataServices_DcmDspData_WLCCtrlSts_WriteData
#  define RTE_RUNNABLE_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData
#  define RTE_RUNNABLE_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData
#  define RTE_RUNNABLE_DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_Diag_VM_HardwareBaseline_ReadData DataServices_Diag_VM_HardwareBaseline_ReadData
#  define RTE_RUNNABLE_DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead
#  define RTE_RUNNABLE_DataServices_Diag_VM_HardwarePartNumber_ReadData DataServices_Diag_VM_HardwarePartNumber_ReadData
#  define RTE_RUNNABLE_ModeChange_Full_Comm_Entry_Runnable ModeChange_Full_Comm_Entry_Runnable
#  define RTE_RUNNABLE_SecurityAccess_Level_01_CompareKey SecurityAccess_Level_01_CompareKey
#  define RTE_RUNNABLE_SecurityAccess_Level_01_GetSeed SecurityAccess_Level_01_GetSeed
#  define RTE_RUNNABLE_SecurityAccess_Level_02_CompareKey SecurityAccess_Level_02_CompareKey
#  define RTE_RUNNABLE_SecurityAccess_Level_02_GetSeed SecurityAccess_Level_02_GetSeed
#  define RTE_RUNNABLE_SecurityAccess_Level_04_CompareKey SecurityAccess_Level_04_CompareKey
#  define RTE_RUNNABLE_SecurityAccess_Level_04_GetSeed SecurityAccess_Level_04_GetSeed
# endif

FUNC(void, Communication_Read_APP_CODE) ComReadandWrite_Runnable(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_BootloaderVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_BootloaderVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_BootloaderVersion_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_WriteData(P2CONST(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data25ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_WriteData(P2CONST(Dcm_Data25ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUManufacturingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUManufacturingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUProgrammingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUProgrammingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUSerialNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUSerialNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data10ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_WriteData(P2CONST(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadActiveDiagSession_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadActiveDiagSession_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data1ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_WriteData(P2CONST(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemName_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemName_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemName_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data8ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemName_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData(P2CONST(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSupplierIdData_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSupplierIdData_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data8ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data17ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_WriteData(P2CONST(Dcm_Data17ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData(P2CONST(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_WriteData(P2CONST(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData(P2CONST(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_WriteData(P2CONST(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data1ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_WriteData(P2CONST(Dcm_Data1ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwareBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwareBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(void, Communication_Read_APP_CODE) ModeChange_Full_Comm_Entry_Runnable(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_01_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_01_CompareKey(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_01_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_01_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_02_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_02_CompareKey(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_02_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_02_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_04_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_04_CompareKey(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_04_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_04_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

# define Communication_Read_APP_STOP_SEC_CODE
# include "Communication_Read_APP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_DataServices_DcmDspData_BootloaderVersion_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_BootloaderVersion_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_ConfigurarionFingerprint_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_ConfigurarionFingerprint_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_ECUConfigurarion_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_ECUConfigurarion_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_ECUDiagDatabaseVersion_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_ECUDiagDatabaseVersion_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_ECUManufacturingDate_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_ECUManufacturingDate_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_ECUProgrammingDate_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_ECUProgrammingDate_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_ECUSerialNumber_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_ECUSerialNumber_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_NFCFunction_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_NFCFunction_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_ReadActiveDiagSession_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_ReadActiveDiagSession_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_ReadFingerprint_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_ReadFingerprint_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_RepairShopFingerPrint_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_RepairShopFingerPrint_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_SystemName_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_SystemName_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_SystemSESVNumber_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_SystemSESVNumber_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_SystemSHV_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_SystemSHV_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_SystemSupplierIdData_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_SystemSupplierIdData_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_VIN_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_VIN_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_VM_CalibrationBaseline_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_VM_CalibrationBaseline_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_VM_FOTASpecialPartNumber_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_VM_FOTASpecialPartNumber_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_VM_SoftwarBaseline_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_VM_SoftwarBaseline_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_VM_SofwarePartNumber_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_VM_SofwarePartNumber_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_VM_SparepartNumber_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_VM_SparepartNumber_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_VM_Specialdatabaseline_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_VM_Specialdatabaseline_E_NOT_OK (1U)

#  define RTE_E_DataServices_DcmDspData_WLCCtrlSts_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_DcmDspData_WLCCtrlSts_E_NOT_OK (1U)

#  define RTE_E_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_E_NOT_OK (1U)

#  define RTE_E_DataServices_Diag_VM_HardwareBaseline_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_Diag_VM_HardwareBaseline_E_NOT_OK (1U)

#  define RTE_E_DataServices_Diag_VM_HardwarePartNumber_DCM_E_PENDING (10U)

#  define RTE_E_DataServices_Diag_VM_HardwarePartNumber_E_NOT_OK (1U)

#  define RTE_E_SecurityAccess_Level_01_DCM_E_COMPARE_KEY_FAILED (11U)

#  define RTE_E_SecurityAccess_Level_01_DCM_E_PENDING (10U)

#  define RTE_E_SecurityAccess_Level_01_E_NOT_OK (1U)

#  define RTE_E_SecurityAccess_Level_02_DCM_E_COMPARE_KEY_FAILED (11U)

#  define RTE_E_SecurityAccess_Level_02_DCM_E_PENDING (10U)

#  define RTE_E_SecurityAccess_Level_02_E_NOT_OK (1U)

#  define RTE_E_SecurityAccess_Level_04_DCM_E_COMPARE_KEY_FAILED (11U)

#  define RTE_E_SecurityAccess_Level_04_DCM_E_PENDING (10U)

#  define RTE_E_SecurityAccess_Level_04_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_COMMUNICATION_READ_APP_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3451:  MISRA rule: 8.8
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
