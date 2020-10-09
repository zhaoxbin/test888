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
 *           Config:  D:/Auto/Demo/WLCProject/WLC.dpa
 *        SW-C Type:  Communication_Read_APP
 *  Generation Time:  2020-09-02 09:29:13
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Application header file for SW-C <Communication_Read_APP> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_COMMUNICATION_READ_APP_H
# define _RTE_COMMUNICATION_READ_APP_H

# ifdef RTE_APPLICATION_HEADER_FILE
#  error Multiple application header files included.
# endif
# define RTE_APPLICATION_HEADER_FILE
# ifndef RTE_PTR2ARRAYBASETYPE_PASSING
#  define RTE_PTR2ARRAYBASETYPE_PASSING
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_Communication_Read_APP_Type.h"
# include "Rte_DataHandleType.h"


/**********************************************************************************************************************
 * Component Data Structures and Port Data Structures
 *********************************************************************************************************************/

struct Rte_CDS_Communication_Read_APP
{
  /* dummy entry */
  uint8 _dummy;
};

# define RTE_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONSTP2CONST(struct Rte_CDS_Communication_Read_APP, RTE_CONST, RTE_CONST) Rte_Inst_Communication_Read_APP; /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

typedef P2CONST(struct Rte_CDS_Communication_Read_APP, TYPEDEF, RTE_CONST) Rte_Instance;


/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

# define Rte_InitValue_CGW_03_CRC_CGW_03_CRC (0U)
# define Rte_InitValue_CGW_03_MsgCntr_CGW_03_MsgCntr (0U)
# define Rte_InitValue_CGW_WLC_CRC_CGW_WLC_CRC (0U)
# define Rte_InitValue_CGW_WLC_MsgCntr_CGW_WLC_MsgCntr (0U)
# define Rte_InitValue_ComfEna_ComfEna (0U)
# define Rte_InitValue_ComfEna_ASIL_ComfEna_ASIL (0U)
# define Rte_InitValue_Day_Day (0U)
# define Rte_InitValue_Hr_Hr (0U)
# define Rte_InitValue_ImobEnaReq_ImobEnaReq (0U)
# define Rte_InitValue_Min_Min (0U)
# define Rte_InitValue_Mth_Mth (0U)
# define Rte_InitValue_Sec_Sec (0U)
# define Rte_InitValue_UsrData0_WLC_UsrData0_WLC (0U)
# define Rte_InitValue_UsrData1_WLC_UsrData1_WLC (0U)
# define Rte_InitValue_UsrData2_WLC_UsrData2_WLC (0U)
# define Rte_InitValue_UsrData3_WLC_UsrData3_WLC (0U)
# define Rte_InitValue_UsrData4_WLC_UsrData4_WLC (0U)
# define Rte_InitValue_UsrData5_WLC_UsrData5_WLC (0U)
# define Rte_InitValue_VehOdometer_VehOdometer (0U)
# define Rte_InitValue_VehSpd_VehSpd (0U)
# define Rte_InitValue_VehState_VehState (0U)
# define Rte_InitValue_VehState_ASIL_VehState_ASIL (0U)
# define Rte_InitValue_WLCChrgFctEnaReq_WLCChrgFctEnaReq (0U)
# define Rte_InitValue_WLCChrgRate_WLCChrgRate (0U)
# define Rte_InitValue_WLCChrgSts_WLCChrgSts (0U)
# define Rte_InitValue_WLCCtrlSts_WLCCtrlSts (0U)
# define Rte_InitValue_WLCFailSts_WLCFailSts (0U)
# define Rte_InitValue_WLCImobSts_WLCImobSts (0U)
# define Rte_InitValue_WLCMuteViaHW_WLCMuteViaHW (FALSE)
# define Rte_InitValue_WLC_01_CRC_WLC_01_CRC (0U)
# define Rte_InitValue_WLC_01_MsgCntr_WLC_01_MsgCntr (0U)
# define Rte_InitValue_WLC_02_CRC_WLC_02_CRC (0U)
# define Rte_InitValue_WLC_02_MsgCntr_WLC_02_MsgCntr (0U)
# define Rte_InitValue_Yr_Yr (0U)


# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_CGW_03_CRC_CGW_03_CRC(P2VAR(CGW_03_CRC, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_CGW_03_MsgCntr_CGW_03_MsgCntr(P2VAR(CGW_03_MsgCntr, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_CGW_WLC_CRC_CGW_WLC_CRC(P2VAR(CGW_WLC_CRC, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_CGW_WLC_MsgCntr_CGW_WLC_MsgCntr(P2VAR(CGW_WLC_MsgCntr, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_ComfEna_ComfEna(P2VAR(ComfEna, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_ComfEna_ASIL_ComfEna_ASIL(P2VAR(ComfEna_ASIL, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_Day_Day(P2VAR(Day, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_Hr_Hr(P2VAR(Hr, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_ImobEnaReq_ImobEnaReq(P2VAR(ImobEnaReq, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_Min_Min(P2VAR(Min, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_Mth_Mth(P2VAR(Mth, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_Sec_Sec(P2VAR(Sec, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_VehOdometer_VehOdometer(P2VAR(VehOdometer, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_VehSpd_VehSpd(P2VAR(VehSpd, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_VehState_VehState(P2VAR(VehState, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_VehState_ASIL_VehState_ASIL(P2VAR(VehState_ASIL, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_WLCChrgFctEnaReq_WLCChrgFctEnaReq(P2VAR(WLCChrgFctEnaReq, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Communication_Read_APP_Yr_Yr(P2VAR(Yr, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
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
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLC_02_CRC_WLC_02_CRC(WLC_02_CRC data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_Communication_Read_APP_WLC_02_MsgCntr_WLC_02_MsgCntr(WLC_02_MsgCntr data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(uint8, RTE_CODE) Rte_Mode_Communication_Read_APP_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(uint8, RTE_CODE) Rte_Mode_Communication_Read_APP_DcmControlDtcSetting_DcmControlDtcSetting(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(uint8, RTE_CODE) Rte_Mode_Communication_Read_APP_DcmEcuReset_DcmEcuReset(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
# define Rte_Read_CGW_03_CRC_CGW_03_CRC Rte_Read_Communication_Read_APP_CGW_03_CRC_CGW_03_CRC
# define Rte_Read_CGW_03_MsgCntr_CGW_03_MsgCntr Rte_Read_Communication_Read_APP_CGW_03_MsgCntr_CGW_03_MsgCntr
# define Rte_Read_CGW_WLC_CRC_CGW_WLC_CRC Rte_Read_Communication_Read_APP_CGW_WLC_CRC_CGW_WLC_CRC
# define Rte_Read_CGW_WLC_MsgCntr_CGW_WLC_MsgCntr Rte_Read_Communication_Read_APP_CGW_WLC_MsgCntr_CGW_WLC_MsgCntr
# define Rte_Read_ComfEna_ComfEna Rte_Read_Communication_Read_APP_ComfEna_ComfEna
# define Rte_Read_ComfEna_ASIL_ComfEna_ASIL Rte_Read_Communication_Read_APP_ComfEna_ASIL_ComfEna_ASIL
# define Rte_Read_Day_Day Rte_Read_Communication_Read_APP_Day_Day
# define Rte_Read_Hr_Hr Rte_Read_Communication_Read_APP_Hr_Hr
# define Rte_Read_ImobEnaReq_ImobEnaReq Rte_Read_Communication_Read_APP_ImobEnaReq_ImobEnaReq
# define Rte_Read_Min_Min Rte_Read_Communication_Read_APP_Min_Min
# define Rte_Read_Mth_Mth Rte_Read_Communication_Read_APP_Mth_Mth
# define Rte_Read_Sec_Sec Rte_Read_Communication_Read_APP_Sec_Sec
# define Rte_Read_VehOdometer_VehOdometer Rte_Read_Communication_Read_APP_VehOdometer_VehOdometer
# define Rte_Read_VehSpd_VehSpd Rte_Read_Communication_Read_APP_VehSpd_VehSpd
# define Rte_Read_VehState_VehState Rte_Read_Communication_Read_APP_VehState_VehState
# define Rte_Read_VehState_ASIL_VehState_ASIL Rte_Read_Communication_Read_APP_VehState_ASIL_VehState_ASIL
# define Rte_Read_WLCChrgFctEnaReq_WLCChrgFctEnaReq Rte_Read_Communication_Read_APP_WLCChrgFctEnaReq_WLCChrgFctEnaReq
# define Rte_Read_Yr_Yr Rte_Read_Communication_Read_APP_Yr_Yr


/**********************************************************************************************************************
 * Rte_Write_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
# define Rte_Write_UsrData0_WLC_UsrData0_WLC Rte_Write_Communication_Read_APP_UsrData0_WLC_UsrData0_WLC
# define Rte_Write_UsrData1_WLC_UsrData1_WLC Rte_Write_Communication_Read_APP_UsrData1_WLC_UsrData1_WLC
# define Rte_Write_UsrData2_WLC_UsrData2_WLC Rte_Write_Communication_Read_APP_UsrData2_WLC_UsrData2_WLC
# define Rte_Write_UsrData3_WLC_UsrData3_WLC Rte_Write_Communication_Read_APP_UsrData3_WLC_UsrData3_WLC
# define Rte_Write_UsrData4_WLC_UsrData4_WLC Rte_Write_Communication_Read_APP_UsrData4_WLC_UsrData4_WLC
# define Rte_Write_UsrData5_WLC_UsrData5_WLC Rte_Write_Communication_Read_APP_UsrData5_WLC_UsrData5_WLC
# define Rte_Write_WLCChrgRate_WLCChrgRate Rte_Write_Communication_Read_APP_WLCChrgRate_WLCChrgRate
# define Rte_Write_WLCChrgSts_WLCChrgSts Rte_Write_Communication_Read_APP_WLCChrgSts_WLCChrgSts
# define Rte_Write_WLCCtrlSts_WLCCtrlSts Rte_Write_Communication_Read_APP_WLCCtrlSts_WLCCtrlSts
# define Rte_Write_WLCFailSts_WLCFailSts Rte_Write_Communication_Read_APP_WLCFailSts_WLCFailSts
# define Rte_Write_WLCImobSts_WLCImobSts Rte_Write_Communication_Read_APP_WLCImobSts_WLCImobSts
# define Rte_Write_WLCMuteViaHW_WLCMuteViaHW Rte_Write_Communication_Read_APP_WLCMuteViaHW_WLCMuteViaHW
# define Rte_Write_WLC_01_CRC_WLC_01_CRC Rte_Write_Communication_Read_APP_WLC_01_CRC_WLC_01_CRC
# define Rte_Write_WLC_01_MsgCntr_WLC_01_MsgCntr Rte_Write_Communication_Read_APP_WLC_01_MsgCntr_WLC_01_MsgCntr
# define Rte_Write_WLC_02_CRC_WLC_02_CRC Rte_Write_Communication_Read_APP_WLC_02_CRC_WLC_02_CRC
# define Rte_Write_WLC_02_MsgCntr_WLC_02_MsgCntr Rte_Write_Communication_Read_APP_WLC_02_MsgCntr_WLC_02_MsgCntr


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
# define Rte_Mode_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f Rte_Mode_Communication_Read_APP_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f
# define Rte_Mode_DcmControlDtcSetting_DcmControlDtcSetting Rte_Mode_Communication_Read_APP_DcmControlDtcSetting_DcmControlDtcSetting
# define Rte_Mode_DcmEcuReset_DcmEcuReset Rte_Mode_Communication_Read_APP_DcmEcuReset_DcmEcuReset




# define Communication_Read_APP_START_SEC_CODE
# include "Communication_Read_APP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *
 * Runnable Entity Name: ComReadandWrite_Runnable
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_CGW_03_CRC_CGW_03_CRC(CGW_03_CRC *data)
 *   Std_ReturnType Rte_Read_CGW_03_MsgCntr_CGW_03_MsgCntr(CGW_03_MsgCntr *data)
 *   Std_ReturnType Rte_Read_CGW_WLC_CRC_CGW_WLC_CRC(CGW_WLC_CRC *data)
 *   Std_ReturnType Rte_Read_CGW_WLC_MsgCntr_CGW_WLC_MsgCntr(CGW_WLC_MsgCntr *data)
 *   Std_ReturnType Rte_Read_ComfEna_ComfEna(ComfEna *data)
 *   Std_ReturnType Rte_Read_ComfEna_ASIL_ComfEna_ASIL(ComfEna_ASIL *data)
 *   Std_ReturnType Rte_Read_Day_Day(Day *data)
 *   Std_ReturnType Rte_Read_Hr_Hr(Hr *data)
 *   Std_ReturnType Rte_Read_ImobEnaReq_ImobEnaReq(ImobEnaReq *data)
 *   Std_ReturnType Rte_Read_Min_Min(Min *data)
 *   Std_ReturnType Rte_Read_Mth_Mth(Mth *data)
 *   Std_ReturnType Rte_Read_Sec_Sec(Sec *data)
 *   Std_ReturnType Rte_Read_VehOdometer_VehOdometer(VehOdometer *data)
 *   Std_ReturnType Rte_Read_VehSpd_VehSpd(VehSpd *data)
 *   Std_ReturnType Rte_Read_VehState_VehState(VehState *data)
 *   Std_ReturnType Rte_Read_VehState_ASIL_VehState_ASIL(VehState_ASIL *data)
 *   Std_ReturnType Rte_Read_WLCChrgFctEnaReq_WLCChrgFctEnaReq(WLCChrgFctEnaReq *data)
 *   Std_ReturnType Rte_Read_Yr_Yr(Yr *data)
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_UsrData0_WLC_UsrData0_WLC(UsrData0_WLC data)
 *   Std_ReturnType Rte_Write_UsrData1_WLC_UsrData1_WLC(UsrData1_WLC data)
 *   Std_ReturnType Rte_Write_UsrData2_WLC_UsrData2_WLC(UsrData2_WLC data)
 *   Std_ReturnType Rte_Write_UsrData3_WLC_UsrData3_WLC(UsrData3_WLC data)
 *   Std_ReturnType Rte_Write_UsrData4_WLC_UsrData4_WLC(UsrData4_WLC data)
 *   Std_ReturnType Rte_Write_UsrData5_WLC_UsrData5_WLC(UsrData5_WLC data)
 *   Std_ReturnType Rte_Write_WLCChrgRate_WLCChrgRate(WLCChrgRate data)
 *   Std_ReturnType Rte_Write_WLCChrgSts_WLCChrgSts(WLCChrgSts data)
 *   Std_ReturnType Rte_Write_WLCCtrlSts_WLCCtrlSts(WLCCtrlSts data)
 *   Std_ReturnType Rte_Write_WLCFailSts_WLCFailSts(WLCFailSts data)
 *   Std_ReturnType Rte_Write_WLCImobSts_WLCImobSts(WLCImobSts data)
 *   Std_ReturnType Rte_Write_WLCMuteViaHW_WLCMuteViaHW(WLCMuteViaHW data)
 *   Std_ReturnType Rte_Write_WLC_01_CRC_WLC_01_CRC(WLC_01_CRC data)
 *   Std_ReturnType Rte_Write_WLC_01_MsgCntr_WLC_01_MsgCntr(WLC_01_MsgCntr data)
 *   Std_ReturnType Rte_Write_WLC_02_CRC_WLC_02_CRC(WLC_02_CRC data)
 *   Std_ReturnType Rte_Write_WLC_02_MsgCntr_WLC_02_MsgCntr(WLC_02_MsgCntr data)
 *
 * Mode Interfaces:
 * ================
 *   uint8 Rte_Mode_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f(void)
 *   Modes of Rte_ModeType_DcmCommunicationControl:
 *   - RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM
 *   - RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM
 *   - RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM
 *   - RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM
 *   - RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORMAL
 *   - RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM
 *   - RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM
 *   - RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM
 *   - RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM
 *   - RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM
 *   - RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM
 *   - RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM
 *   - RTE_TRANSITION_DcmCommunicationControl
 *   uint8 Rte_Mode_DcmControlDtcSetting_DcmControlDtcSetting(void)
 *   Modes of Rte_ModeType_DcmControlDtcSetting:
 *   - RTE_MODE_DcmControlDtcSetting_DISABLEDTCSETTING
 *   - RTE_MODE_DcmControlDtcSetting_ENABLEDTCSETTING
 *   - RTE_TRANSITION_DcmControlDtcSetting
 *   uint8 Rte_Mode_DcmEcuReset_DcmEcuReset(void)
 *   Modes of Rte_ModeType_DcmEcuReset:
 *   - RTE_MODE_DcmEcuReset_EXECUTE
 *   - RTE_MODE_DcmEcuReset_HARD
 *   - RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER
 *   - RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER
 *   - RTE_MODE_DcmEcuReset_KEYONOFF
 *   - RTE_MODE_DcmEcuReset_NONE
 *   - RTE_MODE_DcmEcuReset_SOFT
 *   - RTE_TRANSITION_DcmEcuReset
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_ComReadandWrite_Runnable ComReadandWrite_Runnable
FUNC(void, Communication_Read_APP_CODE) ComReadandWrite_Runnable(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_BootloaderVersion>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_BootloaderVersion_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_BootloaderVersion_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_BootloaderVersion_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_BootloaderVersion>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_BootloaderVersion_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data3ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_BootloaderVersion_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_BootloaderVersion_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_BootloaderVersion_ReadData DataServices_DcmDspData_BootloaderVersion_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_BootloaderVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_BootloaderVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_BootloaderVersion_ReadDataLength
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadDataLength> of PortPrototype <DataServices_DcmDspData_BootloaderVersion>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_BootloaderVersion_ReadDataLength(Dcm_OpStatusType OpStatus, uint16 *DataLength)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_BootloaderVersion_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_BootloaderVersion_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_BootloaderVersion_ReadDataLength DataServices_DcmDspData_BootloaderVersion_ReadDataLength
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_BootloaderVersion_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_ConfigurarionFingerprint>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ConfigurarionFingerprint_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ConfigurarionFingerprint_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ConfigurarionFingerprint_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_ConfigurarionFingerprint>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ConfigurarionFingerprint_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data12ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ConfigurarionFingerprint_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ConfigurarionFingerprint_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ConfigurarionFingerprint_ReadData DataServices_DcmDspData_ConfigurarionFingerprint_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ConfigurarionFingerprint_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_ConfigurarionFingerprint>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ConfigurarionFingerprint_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data12ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ConfigurarionFingerprint_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ConfigurarionFingerprint_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ConfigurarionFingerprint_WriteData DataServices_DcmDspData_ConfigurarionFingerprint_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_WriteData(P2CONST(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_ECUConfigurarion>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUConfigurarion_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUConfigurarion_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ECUConfigurarion_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_ECUConfigurarion>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ECUConfigurarion_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data25ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUConfigurarion_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUConfigurarion_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ECUConfigurarion_ReadData DataServices_DcmDspData_ECUConfigurarion_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data25ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ECUConfigurarion_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_ECUConfigurarion>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ECUConfigurarion_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data25ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUConfigurarion_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUConfigurarion_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ECUConfigurarion_WriteData DataServices_DcmDspData_ECUConfigurarion_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_WriteData(P2CONST(Dcm_Data25ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_ECUDiagDatabaseVersion>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUDiagDatabaseVersion_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUDiagDatabaseVersion_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_ECUDiagDatabaseVersion>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data3ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUDiagDatabaseVersion_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUDiagDatabaseVersion_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_ECUManufacturingDate>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUManufacturingDate_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUManufacturingDate_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ECUManufacturingDate_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_ECUManufacturingDate>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ECUManufacturingDate_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data3ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUManufacturingDate_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUManufacturingDate_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ECUManufacturingDate_ReadData DataServices_DcmDspData_ECUManufacturingDate_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUManufacturingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUManufacturingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_ECUProgrammingDate>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUProgrammingDate_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUProgrammingDate_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ECUProgrammingDate_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_ECUProgrammingDate>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ECUProgrammingDate_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data3ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUProgrammingDate_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUProgrammingDate_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ECUProgrammingDate_ReadData DataServices_DcmDspData_ECUProgrammingDate_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUProgrammingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUProgrammingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_ECUSerialNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUSerialNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUSerialNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ECUSerialNumber_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_ECUSerialNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ECUSerialNumber_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data10ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUSerialNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUSerialNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ECUSerialNumber_ReadData DataServices_DcmDspData_ECUSerialNumber_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUSerialNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUSerialNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data10ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_NFCFunction_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_NFCFunction>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_NFCFunction_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_NFCFunction_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_NFCFunction_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_NFCFunction_ConditionCheckRead DataServices_DcmDspData_NFCFunction_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_NFCFunction_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_NFCFunction>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_NFCFunction_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data2ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_NFCFunction_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_NFCFunction_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_NFCFunction_ReadData DataServices_DcmDspData_NFCFunction_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_NFCFunction_ReadDataLength
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadDataLength> of PortPrototype <DataServices_DcmDspData_NFCFunction>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_NFCFunction_ReadDataLength(Dcm_OpStatusType OpStatus, uint16 *DataLength)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_NFCFunction_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_NFCFunction_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_NFCFunction_ReadDataLength DataServices_DcmDspData_NFCFunction_ReadDataLength
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_NFCFunction_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_NFCFunction>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_NFCFunction_WriteData(const uint8 *Data, uint16 DataLength, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data2ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_NFCFunction_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_NFCFunction_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_NFCFunction_WriteData DataServices_DcmDspData_NFCFunction_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_WriteData(P2CONST(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_ReadActiveDiagSession>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ReadActiveDiagSession_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ReadActiveDiagSession_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ReadActiveDiagSession_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_ReadActiveDiagSession>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ReadActiveDiagSession_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data1ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ReadActiveDiagSession_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ReadActiveDiagSession_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ReadActiveDiagSession_ReadData DataServices_DcmDspData_ReadActiveDiagSession_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadActiveDiagSession_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadActiveDiagSession_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data1ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_ReadFingerprint>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ReadFingerprint_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ReadFingerprint_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_ReadFingerprint_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_ReadFingerprint>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_ReadFingerprint_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data12ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ReadFingerprint_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ReadFingerprint_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_ReadFingerprint_ReadData DataServices_DcmDspData_ReadFingerprint_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_RepairShopFingerPrint>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_RepairShopFingerPrint_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_RepairShopFingerPrint_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_RepairShopFingerPrint_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_RepairShopFingerPrint>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_RepairShopFingerPrint_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data12ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_RepairShopFingerPrint_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_RepairShopFingerPrint_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_RepairShopFingerPrint_ReadData DataServices_DcmDspData_RepairShopFingerPrint_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_RepairShopFingerPrint_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_RepairShopFingerPrint>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_RepairShopFingerPrint_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data12ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_RepairShopFingerPrint_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_RepairShopFingerPrint_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_RepairShopFingerPrint_WriteData DataServices_DcmDspData_RepairShopFingerPrint_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_WriteData(P2CONST(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemName_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_SystemName>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemName_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemName_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemName_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemName_ConditionCheckRead DataServices_DcmDspData_SystemName_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemName_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemName_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_SystemName>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemName_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data8ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemName_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemName_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemName_ReadData DataServices_DcmDspData_SystemName_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemName_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemName_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data8ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemName_ReadDataLength
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadDataLength> of PortPrototype <DataServices_DcmDspData_SystemName>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemName_ReadDataLength(Dcm_OpStatusType OpStatus, uint16 *DataLength)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemName_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemName_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemName_ReadDataLength DataServices_DcmDspData_SystemName_ReadDataLength
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemName_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_SystemSESVNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSESVNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSESVNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSESVNumber_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_SystemSESVNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSESVNumber_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data6ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSESVNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSESVNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSESVNumber_ReadData DataServices_DcmDspData_SystemSESVNumber_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSESVNumber_ReadDataLength
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadDataLength> of PortPrototype <DataServices_DcmDspData_SystemSESVNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSESVNumber_ReadDataLength(Dcm_OpStatusType OpStatus, uint16 *DataLength)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSESVNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSESVNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSESVNumber_ReadDataLength DataServices_DcmDspData_SystemSESVNumber_ReadDataLength
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data6ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadDataLength> of PortPrototype <DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength(Dcm_OpStatusType OpStatus, uint16 *DataLength)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData(const uint8 *Data, uint16 DataLength, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data6ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData(P2CONST(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSHV_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_SystemSHV>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSHV_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSHV_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSHV_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSHV_ConditionCheckRead DataServices_DcmDspData_SystemSHV_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSHV_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_SystemSHV>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSHV_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data6ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSHV_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSHV_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSHV_ReadData DataServices_DcmDspData_SystemSHV_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSHV_ReadDataLength
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadDataLength> of PortPrototype <DataServices_DcmDspData_SystemSHV>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSHV_ReadDataLength(Dcm_OpStatusType OpStatus, uint16 *DataLength)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSHV_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSHV_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSHV_ReadDataLength DataServices_DcmDspData_SystemSHV_ReadDataLength
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_SystemSupplierIdData>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSupplierIdData_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSupplierIdData_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSupplierIdData_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_SystemSupplierIdData>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSupplierIdData_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data8ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSupplierIdData_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSupplierIdData_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_SystemSupplierIdData_ReadData DataServices_DcmDspData_SystemSupplierIdData_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSupplierIdData_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSupplierIdData_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data8ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VIN_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_VIN>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VIN_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VIN_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VIN_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VIN_ConditionCheckRead DataServices_DcmDspData_VIN_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VIN_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_VIN>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VIN_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data17ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VIN_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VIN_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VIN_ReadData DataServices_DcmDspData_VIN_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data17ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VIN_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_VIN>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VIN_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data17ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VIN_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VIN_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VIN_WriteData DataServices_DcmDspData_VIN_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_WriteData(P2CONST(Dcm_Data17ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_VM_CalibrarionPartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_VM_CalibrarionPartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data11ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_VM_CalibrarionPartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data11ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData(P2CONST(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_VM_CalibrationBaseline>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_CalibrationBaseline_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_CalibrationBaseline_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_CalibrationBaseline_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_VM_CalibrationBaseline>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_CalibrationBaseline_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data2ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_CalibrationBaseline_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_CalibrationBaseline_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrationBaseline_ReadData DataServices_DcmDspData_VM_CalibrationBaseline_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_CalibrationBaseline_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_VM_CalibrationBaseline>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_CalibrationBaseline_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data2ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_CalibrationBaseline_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_CalibrationBaseline_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_CalibrationBaseline_WriteData DataServices_DcmDspData_VM_CalibrationBaseline_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_WriteData(P2CONST(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_VM_FOTASpecialPartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_FOTASpecialPartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_FOTASpecialPartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_VM_FOTASpecialPartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data11ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_FOTASpecialPartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_FOTASpecialPartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_VM_FOTASpecialPartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data11ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_FOTASpecialPartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_FOTASpecialPartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData(P2CONST(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_VM_SoftwarBaseline>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_SoftwarBaseline_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_SoftwarBaseline_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_SoftwarBaseline_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_VM_SoftwarBaseline>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_SoftwarBaseline_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data2ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_SoftwarBaseline_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_SoftwarBaseline_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_SoftwarBaseline_ReadData DataServices_DcmDspData_VM_SoftwarBaseline_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_VM_SofwarePartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_SofwarePartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_SofwarePartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_SofwarePartNumber_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_VM_SofwarePartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_SofwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data11ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_SofwarePartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_SofwarePartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_SofwarePartNumber_ReadData DataServices_DcmDspData_VM_SofwarePartNumber_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_VM_SparepartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_SparepartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_SparepartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_SparepartNumber_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_VM_SparepartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_SparepartNumber_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data11ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_SparepartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_SparepartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_SparepartNumber_ReadData DataServices_DcmDspData_VM_SparepartNumber_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_SparepartNumber_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_VM_SparepartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_SparepartNumber_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data11ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_SparepartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_SparepartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_SparepartNumber_WriteData DataServices_DcmDspData_VM_SparepartNumber_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_WriteData(P2CONST(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_VM_Specialdatabaseline>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_Specialdatabaseline_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_Specialdatabaseline_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_Specialdatabaseline_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_VM_Specialdatabaseline>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_Specialdatabaseline_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_Specialdatabaseline_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_Specialdatabaseline_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_Specialdatabaseline_ReadData DataServices_DcmDspData_VM_Specialdatabaseline_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadDataLength> of PortPrototype <DataServices_DcmDspData_VM_Specialdatabaseline>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength(Dcm_OpStatusType OpStatus, uint16 *DataLength)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_Specialdatabaseline_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_Specialdatabaseline_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_DcmDspData_WLCCtrlSts>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_WLCCtrlSts_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_WLCCtrlSts_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_WLCCtrlSts_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_DcmDspData_WLCCtrlSts>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_WLCCtrlSts_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data1ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_WLCCtrlSts_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_WLCCtrlSts_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_WLCCtrlSts_ReadData DataServices_DcmDspData_WLCCtrlSts_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data1ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_WLCCtrlSts_ReadDataLength
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadDataLength> of PortPrototype <DataServices_DcmDspData_WLCCtrlSts>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_WLCCtrlSts_ReadDataLength(Dcm_OpStatusType OpStatus, uint16 *DataLength)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_WLCCtrlSts_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_WLCCtrlSts_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_WLCCtrlSts_ReadDataLength DataServices_DcmDspData_WLCCtrlSts_ReadDataLength
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_WLCCtrlSts_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_WLCCtrlSts>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_WLCCtrlSts_WriteData(const uint8 *Data, uint16 DataLength, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data1ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_WLCCtrlSts_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_WLCCtrlSts_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_DcmDspData_WLCCtrlSts_WriteData DataServices_DcmDspData_WLCCtrlSts_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_WriteData(P2CONST(Dcm_Data1ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_DCM_E_PENDING
 *   RTE_E_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_DCM_E_PENDING
 *   RTE_E_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_DCM_E_PENDING
 *   RTE_E_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_Diag_VM_HardwareBaseline>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_Diag_VM_HardwareBaseline_DCM_E_PENDING
 *   RTE_E_DataServices_Diag_VM_HardwareBaseline_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_Diag_VM_HardwareBaseline_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_Diag_VM_HardwareBaseline>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_Diag_VM_HardwareBaseline_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data2ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_Diag_VM_HardwareBaseline_DCM_E_PENDING
 *   RTE_E_DataServices_Diag_VM_HardwareBaseline_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_Diag_VM_HardwareBaseline_ReadData DataServices_Diag_VM_HardwareBaseline_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwareBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwareBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_Diag_VM_HardwarePartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_Diag_VM_HardwarePartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_Diag_VM_HardwarePartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_Diag_VM_HardwarePartNumber_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_Diag_VM_HardwarePartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_Diag_VM_HardwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data11ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_Diag_VM_HardwarePartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_Diag_VM_HardwarePartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DataServices_Diag_VM_HardwarePartNumber_ReadData DataServices_Diag_VM_HardwarePartNumber_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ModeChange_Full_Comm_Entry_Runnable
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * This runnable is never executed by the RTE.
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_ModeChange_Full_Comm_Entry_Runnable ModeChange_Full_Comm_Entry_Runnable
FUNC(void, Communication_Read_APP_CODE) ModeChange_Full_Comm_Entry_Runnable(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SecurityAccess_Level_01_CompareKey
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <CompareKey> of PortPrototype <SecurityAccess_Level_01>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SecurityAccess_Level_01_CompareKey(const uint8 *Key, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Key: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SecurityAccess_Level_01_DCM_E_COMPARE_KEY_FAILED
 *   RTE_E_SecurityAccess_Level_01_DCM_E_PENDING
 *   RTE_E_SecurityAccess_Level_01_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_SecurityAccess_Level_01_CompareKey SecurityAccess_Level_01_CompareKey
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_01_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_01_CompareKey(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SecurityAccess_Level_01_GetSeed
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <GetSeed> of PortPrototype <SecurityAccess_Level_01>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SecurityAccess_Level_01_GetSeed(Dcm_OpStatusType OpStatus, uint8 *Seed, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Seed: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SecurityAccess_Level_01_DCM_E_PENDING
 *   RTE_E_SecurityAccess_Level_01_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_SecurityAccess_Level_01_GetSeed SecurityAccess_Level_01_GetSeed
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_01_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_01_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SecurityAccess_Level_02_CompareKey
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <CompareKey> of PortPrototype <SecurityAccess_Level_02>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SecurityAccess_Level_02_CompareKey(const uint8 *Key, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Key: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SecurityAccess_Level_02_DCM_E_COMPARE_KEY_FAILED
 *   RTE_E_SecurityAccess_Level_02_DCM_E_PENDING
 *   RTE_E_SecurityAccess_Level_02_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_SecurityAccess_Level_02_CompareKey SecurityAccess_Level_02_CompareKey
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_02_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_02_CompareKey(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SecurityAccess_Level_02_GetSeed
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <GetSeed> of PortPrototype <SecurityAccess_Level_02>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SecurityAccess_Level_02_GetSeed(Dcm_OpStatusType OpStatus, uint8 *Seed, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Seed: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SecurityAccess_Level_02_DCM_E_PENDING
 *   RTE_E_SecurityAccess_Level_02_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_SecurityAccess_Level_02_GetSeed SecurityAccess_Level_02_GetSeed
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_02_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_02_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SecurityAccess_Level_04_CompareKey
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <CompareKey> of PortPrototype <SecurityAccess_Level_04>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SecurityAccess_Level_04_CompareKey(const uint8 *Key, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Key: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SecurityAccess_Level_04_DCM_E_COMPARE_KEY_FAILED
 *   RTE_E_SecurityAccess_Level_04_DCM_E_PENDING
 *   RTE_E_SecurityAccess_Level_04_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_SecurityAccess_Level_04_CompareKey SecurityAccess_Level_04_CompareKey
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_04_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_04_CompareKey(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SecurityAccess_Level_04_GetSeed
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <GetSeed> of PortPrototype <SecurityAccess_Level_04>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SecurityAccess_Level_04_GetSeed(Dcm_OpStatusType OpStatus, uint8 *Seed, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Seed: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SecurityAccess_Level_04_DCM_E_PENDING
 *   RTE_E_SecurityAccess_Level_04_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_SecurityAccess_Level_04_GetSeed SecurityAccess_Level_04_GetSeed
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_04_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_04_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

# define Communication_Read_APP_STOP_SEC_CODE
# include "Communication_Read_APP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

# define RTE_E_DataServices_DcmDspData_BootloaderVersion_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_BootloaderVersion_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_ConfigurarionFingerprint_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_ConfigurarionFingerprint_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_ECUConfigurarion_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_ECUConfigurarion_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_ECUDiagDatabaseVersion_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_ECUDiagDatabaseVersion_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_ECUManufacturingDate_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_ECUManufacturingDate_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_ECUProgrammingDate_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_ECUProgrammingDate_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_ECUSerialNumber_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_ECUSerialNumber_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_NFCFunction_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_NFCFunction_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_ReadActiveDiagSession_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_ReadActiveDiagSession_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_ReadFingerprint_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_ReadFingerprint_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_RepairShopFingerPrint_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_RepairShopFingerPrint_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_SystemName_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_SystemName_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_SystemSESVNumber_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_SystemSESVNumber_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_SystemSHV_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_SystemSHV_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_SystemSupplierIdData_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_SystemSupplierIdData_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_VIN_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_VIN_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_VM_CalibrationBaseline_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_VM_CalibrationBaseline_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_VM_FOTASpecialPartNumber_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_VM_FOTASpecialPartNumber_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_VM_SoftwarBaseline_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_VM_SoftwarBaseline_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_VM_SofwarePartNumber_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_VM_SofwarePartNumber_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_VM_SparepartNumber_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_VM_SparepartNumber_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_VM_Specialdatabaseline_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_VM_Specialdatabaseline_E_NOT_OK (1U)

# define RTE_E_DataServices_DcmDspData_WLCCtrlSts_DCM_E_PENDING (10U)

# define RTE_E_DataServices_DcmDspData_WLCCtrlSts_E_NOT_OK (1U)

# define RTE_E_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_DCM_E_PENDING (10U)

# define RTE_E_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_E_NOT_OK (1U)

# define RTE_E_DataServices_Diag_VM_HardwareBaseline_DCM_E_PENDING (10U)

# define RTE_E_DataServices_Diag_VM_HardwareBaseline_E_NOT_OK (1U)

# define RTE_E_DataServices_Diag_VM_HardwarePartNumber_DCM_E_PENDING (10U)

# define RTE_E_DataServices_Diag_VM_HardwarePartNumber_E_NOT_OK (1U)

# define RTE_E_SecurityAccess_Level_01_DCM_E_COMPARE_KEY_FAILED (11U)

# define RTE_E_SecurityAccess_Level_01_DCM_E_PENDING (10U)

# define RTE_E_SecurityAccess_Level_01_E_NOT_OK (1U)

# define RTE_E_SecurityAccess_Level_02_DCM_E_COMPARE_KEY_FAILED (11U)

# define RTE_E_SecurityAccess_Level_02_DCM_E_PENDING (10U)

# define RTE_E_SecurityAccess_Level_02_E_NOT_OK (1U)

# define RTE_E_SecurityAccess_Level_04_DCM_E_COMPARE_KEY_FAILED (11U)

# define RTE_E_SecurityAccess_Level_04_DCM_E_PENDING (10U)

# define RTE_E_SecurityAccess_Level_04_E_NOT_OK (1U)

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_COMMUNICATION_READ_APP_H */
