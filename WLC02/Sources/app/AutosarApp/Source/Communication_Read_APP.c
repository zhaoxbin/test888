/**********************************************************************************************************************
 *  FILE REQUIRES USER MODIFICATIONS
 *  Template Scope: sections marked with Start and End comments
 *  -------------------------------------------------------------------------------------------------------------------
 *  This file includes template code that must be completed and/or adapted during BSW integration.
 *  The template code is incomplete and only intended for providing a signature and an empty implementation.
 *  It is neither intended nor qualified for use in series production without applying suitable quality measures.
 *  The template code must be completed as described in the instructions given within this file and/or in the.
 *  Technical Reference..
 *  The completed implementation must be tested with diligent care and must comply with all quality requirements which.
 *  are necessary according to the state of the art before its use..
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Communication_Read_APP.c
 *           Config:  D:/Auto/Demo/WLCProject/WLC.dpa
 *        SW-C Type:  Communication_Read_APP
 *  Generation Time:  2020-09-23 07:01:53
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  C-Code implementation template for SW-C <Communication_Read_APP>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* PRQA S 0777, 0779 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************
 *
 * Data Types:
 * ===========
 * BswM_ESH_RunRequest
 *   uint8 represents integers with a minimum value of 0 and a maximum value of 255.
 *      The order-relation on uint8 is: x < y if y - x is positive.
 *      uint8 has a lexical representation consisting of a finite-length sequence 
 *      of decimal digits (#x30-#x39).
 *      
 *      For example: 1, 0, 126, +10.
 *
 * Dcm_NegativeResponseCodeType
 *   uint8 represents integers with a minimum value of 0 and a maximum value of 255.
 *      The order-relation on uint8 is: x < y if y - x is positive.
 *      uint8 has a lexical representation consisting of a finite-length sequence 
 *      of decimal digits (#x30-#x39).
 *      
 *      For example: 1, 0, 126, +10.
 *
 * Dcm_OpStatusType
 *   uint8 represents integers with a minimum value of 0 and a maximum value of 255.
 *      The order-relation on uint8 is: x < y if y - x is positive.
 *      uint8 has a lexical representation consisting of a finite-length sequence 
 *      of decimal digits (#x30-#x39).
 *      
 *      For example: 1, 0, 126, +10.
 *
 *********************************************************************************************************************/

#include "Rte_Communication_Read_APP.h" /* PRQA S 0857 */ /* MD_MSR_1.1_857 */

#include "EEEPROM_data_def.h"
#include "EEEPROM_io_ctl.h"
#include "hal.h"

//__attribute__ ((section(".eeeprom"))) eeerom_data_t eeerom_data;


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Used AUTOSAR Data Types
 *
 **********************************************************************************************************************
 *
 * Primitive Types:
 * ================
 * CGW_03_CRC: Integer in interval [0...255]
 * CGW_03_MsgCntr: Integer in interval [0...15]
 * CGW_WLC_CRC: Integer in interval [0...255]
 * CGW_WLC_MsgCntr: Integer in interval [0...15]
 * Day: Integer in interval [0...31]
 * Hr: Integer in interval [0...23]
 * Min: Integer in interval [0...59]
 * Sec: Integer in interval [0...59]
 * UsrData0_WLC: Integer in interval [0...255]
 * UsrData1_WLC: Integer in interval [0...255]
 * UsrData2_WLC: Integer in interval [0...255]
 * UsrData3_WLC: Integer in interval [0...255]
 * UsrData4_WLC: Integer in interval [0...255]
 * UsrData5_WLC: Integer in interval [0...255]
 * VehOdometer: Integer in interval [0...16777214]
 * VehSpd: Integer in interval [0...8191]
 * WLCMuteViaHW: Boolean
 * WLC_01_CRC: Integer in interval [0...255]
 * WLC_01_MsgCntr: Integer in interval [0...15]
 * WLC_02_CRC: Integer in interval [0...255]
 * WLC_02_MsgCntr: Integer in interval [0...15]
 * Yr: Integer in interval [0...255]
 * uint16: Integer in interval [0...65535] (standard type)
 * uint8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * BswM_ESH_RunRequest: Enumeration of integer in interval [0...255] with enumerators
 *   RELEASED (0U)
 *   REQUESTED (1U)
 * ComfEna: Enumeration of integer in interval [0...3] with enumerators
 *   Cx0_Comfort_not_enabled (0U)
 *   Cx1_Comfort_enabled (1U)
 *   Cx2_Reserved (2U)
 *   Cx3_Invalid (3U)
 * ComfEna_ASIL: Enumeration of integer in interval [0...3] with enumerators
 *   Cx0_Comfort_not_enabled (0U)
 *   Cx1_Comfort_enabled (1U)
 *   Cx2_Reserved (2U)
 *   Cx3_Invalid (3U)
 * Dcm_NegativeResponseCodeType: Enumeration of integer in interval [0...254] with enumerators
 *   DCM_E_POSITIVERESPONSE (0U)
 *   DCM_E_GENERALREJECT (16U)
 *   DCM_E_SERVICENOTSUPPORTED (17U)
 *   DCM_E_SUBFUNCTIONNOTSUPPORTED (18U)
 *   DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT (19U)
 *   DCM_E_RESPONSETOOLONG (20U)
 *   DCM_E_BUSYREPEATREQUEST (33U)
 *   DCM_E_CONDITIONSNOTCORRECT (34U)
 *   DCM_E_REQUESTSEQUENCEERROR (36U)
 *   DCM_E_NORESPONSEFROMSUBNETCOMPONENT (37U)
 *   DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION (38U)
 *   DCM_E_REQUESTOUTOFRANGE (49U)
 *   DCM_E_SECURITYACCESSDENIED (51U)
 *   DCM_E_INVALIDKEY (53U)
 *   DCM_E_EXCEEDNUMBEROFATTEMPTS (54U)
 *   DCM_E_REQUIREDTIMEDELAYNOTEXPIRED (55U)
 *   DCM_E_UPLOADDOWNLOADNOTACCEPTED (112U)
 *   DCM_E_TRANSFERDATASUSPENDED (113U)
 *   DCM_E_GENERALPROGRAMMINGFAILURE (114U)
 *   DCM_E_WRONGBLOCKSEQUENCECOUNTER (115U)
 *   DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING (120U)
 *   DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION (126U)
 *   DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION (127U)
 *   DCM_E_RPMTOOHIGH (129U)
 *   DCM_E_RPMTOOLOW (130U)
 *   DCM_E_ENGINEISRUNNING (131U)
 *   DCM_E_ENGINEISNOTRUNNING (132U)
 *   DCM_E_ENGINERUNTIMETOOLOW (133U)
 *   DCM_E_TEMPERATURETOOHIGH (134U)
 *   DCM_E_TEMPERATURETOOLOW (135U)
 *   DCM_E_VEHICLESPEEDTOOHIGH (136U)
 *   DCM_E_VEHICLESPEEDTOOLOW (137U)
 *   DCM_E_THROTTLE_PEDALTOOHIGH (138U)
 *   DCM_E_THROTTLE_PEDALTOOLOW (139U)
 *   DCM_E_TRANSMISSIONRANGENOTINNEUTRAL (140U)
 *   DCM_E_TRANSMISSIONRANGENOTINGEAR (141U)
 *   DCM_E_BRAKESWITCH_NOTCLOSED (143U)
 *   DCM_E_SHIFTERLEVERNOTINPARK (144U)
 *   DCM_E_TORQUECONVERTERCLUTCHLOCKED (145U)
 *   DCM_E_VOLTAGETOOHIGH (146U)
 *   DCM_E_VOLTAGETOOLOW (147U)
 *   DCM_E_VMSCNC_0 (240U)
 *   DCM_E_VMSCNC_1 (241U)
 *   DCM_E_VMSCNC_2 (242U)
 *   DCM_E_VMSCNC_3 (243U)
 *   DCM_E_VMSCNC_4 (244U)
 *   DCM_E_VMSCNC_5 (245U)
 *   DCM_E_VMSCNC_6 (246U)
 *   DCM_E_VMSCNC_7 (247U)
 *   DCM_E_VMSCNC_8 (248U)
 *   DCM_E_VMSCNC_9 (249U)
 *   DCM_E_VMSCNC_A (250U)
 *   DCM_E_VMSCNC_B (251U)
 *   DCM_E_VMSCNC_C (252U)
 *   DCM_E_VMSCNC_D (253U)
 *   DCM_E_VMSCNC_E (254U)
 * Dcm_OpStatusType: Enumeration of integer in interval [0...64] with enumerators
 *   DCM_INITIAL (0U)
 *   DCM_PENDING (1U)
 *   DCM_CANCEL (2U)
 *   DCM_FORCE_RCRRP_OK (3U)
 *   DCM_FORCE_RCRRP_NOT_OK (64U)
 * ImobEnaReq: Enumeration of integer in interval [0...3] with enumerators
 *   Cx0_Disable (0U)
 *   Cx1_Enable_AID1 (1U)
 *   Cx2_Enable_AID2 (2U)
 *   Cx3_Invalid (3U)
 * Mth: Enumeration of integer in interval [0...15] with enumerators
 *   Cx0_Unknown (0U)
 *   Cx1_January (1U)
 *   Cx2_February (2U)
 *   Cx3_March (3U)
 *   Cx4_April (4U)
 *   Cx5_May (5U)
 *   Cx6_June (6U)
 *   Cx7_July (7U)
 *   Cx8_August (8U)
 *   Cx9_September (9U)
 *   CxA_October (10U)
 *   CxB_November (11U)
 *   CxC_December (12U)
 *   CxD_Reserved (13U)
 *   CxE_Reserved (14U)
 *   CxF_Invalid (15U)
 * VehState: Enumeration of integer in interval [0...15] with enumerators
 *   Cx0_Parked_vehicle_Off_ (0U)
 *   Cx1_Driver_present_On_ (1U)
 *   Cx2_Driving (2U)
 *   Cx3_Software_update (3U)
 *   Cx4_Reserved (4U)
 *   Cx5_Reserved (5U)
 *   Cx6_Reserved (6U)
 *   Cx7_Reserved (7U)
 *   Cx8_Reserved (8U)
 *   Cx9_Reserved (9U)
 *   CxA_Reserved (10U)
 *   CxB_Reserved (11U)
 *   CxC_Reserved (12U)
 *   CxD_Reserved (13U)
 *   CxE_Reserved (14U)
 *   CxF_Invalid (15U)
 * VehState_ASIL: Enumeration of integer in interval [0...15] with enumerators
 *   Cx0_Parked_vehicle_Off_ (0U)
 *   Cx1_Driver_present_On_ (1U)
 *   Cx2_Driving (2U)
 *   Cx3_Software_update (3U)
 *   Cx4_Reserved (4U)
 *   Cx5_Reserved (5U)
 *   Cx6_Reserved (6U)
 *   Cx7_Reserved (7U)
 *   Cx8_Reserved (8U)
 *   Cx9_Reserved (9U)
 *   CxA_Reserved (10U)
 *   CxB_Reserved (11U)
 *   CxC_Reserved (12U)
 *   CxD_Reserved (13U)
 *   CxE_Reserved (14U)
 *   CxF_Invalid (15U)
 * WLCChrgFctEnaReq: Enumeration of integer in interval [0...3] with enumerators
 *   Cx0_Disable_WLC_charging_function (0U)
 *   Cx1_Enable_WLC_charging_function (1U)
 *   Cx2_No_operation (2U)
 *   Cx3_Invalid (3U)
 * WLCChrgRate: Enumeration of integer in interval [0...3] with enumerators
 *   Cx0_Not_started_ (0U)
 *   Cx1_Power_Requested_ (1U)
 *   Cx2_Power_Reduced_ (2U)
 *   Cx3_Reserved (3U)
 * WLCChrgSts: Enumeration of integer in interval [0...3] with enumerators
 *   Cx0_WLC_stopped (0U)
 *   Cx1_WLC_on_going (1U)
 *   Cx2_Charge_complete (2U)
 *   Cx3_Invalid (3U)
 * WLCCtrlSts: Enumeration of integer in interval [0...3] with enumerators
 *   Cx0_WLC_enabled (0U)
 *   Cx1_WLC_disabled (1U)
 *   Cx2_Reserved (2U)
 *   Cx3_Invalid (3U)
 * WLCFailSts: Enumeration of integer in interval [0...15] with enumerators
 *   Cx0_No_failure (0U)
 *   Cx1_Over_temperature (1U)
 *   Cx2_Under_voltage (2U)
 *   Cx3_Over_voltage (3U)
 *   Cx4_Internal_error (4U)
 *   Cx5_Foreign_object_existing (5U)
 *   Cx6_Unknown_error (6U)
 *   Cx7_Smartphone_no_response_or_error (7U)
 *   Cx8_Conductive_Device_Detected (8U)
 *   Cx9_Reserved (9U)
 *   CxA_Reserved (10U)
 *   CxB_Reserved (11U)
 *   CxC_Reserved (12U)
 *   CxD_Reserved (13U)
 *   CxE_Reserved (14U)
 *   CxF_Invalid (15U)
 * WLCImobSts: Enumeration of integer in interval [0...3] with enumerators
 *   Cx0_Disable (0U)
 *   Cx1_Enable (1U)
 *   Cx2_Reserved (2U)
 *   Cx3_Invalid (3U)
 *
 * Array Types:
 * ============
 * Dcm_Data10ByteType: Array with 10 element(s) of type uint8
 * Dcm_Data11ByteType: Array with 11 element(s) of type uint8
 * Dcm_Data12ByteType: Array with 12 element(s) of type uint8
 * Dcm_Data17ByteType: Array with 17 element(s) of type uint8
 * Dcm_Data1ByteType: Array with 1 element(s) of type uint8
 * Dcm_Data25ByteType: Array with 25 element(s) of type uint8
 * Dcm_Data2ByteType: Array with 2 element(s) of type uint8
 * Dcm_Data3ByteType: Array with 3 element(s) of type uint8
 * Dcm_Data4ByteType: Array with 4 element(s) of type uint8
 * Dcm_Data6ByteType: Array with 6 element(s) of type uint8
 * Dcm_Data8ByteType: Array with 8 element(s) of type uint8
 *
 *********************************************************************************************************************/


#define Communication_Read_APP_START_SEC_CODE
#include "Communication_Read_APP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: ComReadandWrite_Runnable_doc
 *********************************************************************************************************************/
WLCChrgRate data1;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Communication_Read_APP_CODE) ComReadandWrite_Runnable(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ComReadandWrite_Runnable
 *********************************************************************************************************************/
     //data1=1;
	 //Rte_Write_WLCChrgRate_WLCChrgRate( data1);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_BootloaderVersion_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_BootloaderVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_BootloaderVersion_ReadData (returns application error)
 *********************************************************************************************************************/

	//F1 50

	Data[0] = 0x01;
	Data[1] = 0x02;
	Data[2] = 0x03;

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_BootloaderVersion_ReadDataLength_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_BootloaderVersion_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_BootloaderVersion_ReadDataLength (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ConfigurarionFingerprint_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ConfigurarionFingerprint_ReadData (returns application error)
 *********************************************************************************************************************/

	// F1 01
	// No need in SPEC

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ConfigurarionFingerprint_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ConfigurarionFingerprint_WriteData (returns application error)
 *********************************************************************************************************************/

	// F1 5C
	// No need in SPEC

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUConfigurarion_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUConfigurarion_ReadData (returns application error)
 *********************************************************************************************************************/
	// F1 01
	// No need in SPEC

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUConfigurarion_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUConfigurarion_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUConfigurarion_WriteData (returns application error)
 *********************************************************************************************************************/

	// F1 01
	// No need in SPEC

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData (returns application error)
 *********************************************************************************************************************/

	// F1 9E
	Data[0] = 0x01;			// Major version
	Data[1] = 0x01;			// Middle Version
	Data[2] = 0x03;			// Minor version

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUManufacturingDate_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUManufacturingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUManufacturingDate_ReadData (returns application error)
 *********************************************************************************************************************/

	// F1 8B
	/*
	Data[0] = 0x20;
	Data[1] = 0x09;
	Data[2] = 0x29;
	*/

	HAL_RWEEPROM(&eeerom_data.Did_F18B[0],&Data[0],3);		// Read Data from EEEPROM


  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUProgrammingDate_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUProgrammingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUProgrammingDate_ReadData (returns application error)
 *********************************************************************************************************************/

	//F1 99
	Data[0] = 0x20;
	Data[1] = 0x09;
	Data[2] = 0x30;

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
 *     Argument Data: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_ECUSerialNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_ECUSerialNumber_E_NOT_OK
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUSerialNumber_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ECUSerialNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ECUSerialNumber_ReadData (returns application error)
 *********************************************************************************************************************/

	//F1 8C
	Data[0] = 0x30;
	Data[1] = 0x34;
	Data[2] = 0x30;
	Data[3] = 0x34;
	Data[4] = 0x36;
	Data[5] = 0x39;
	Data[6] = 0x30;
	Data[7] = 0x30;
	Data[8] = 0x33;
	Data[9] = 0x39;
  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_NFCFunction_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_NFCFunction_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_NFCFunction_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_NFCFunction_ReadData (returns application error)
 *********************************************************************************************************************/
	//FD 22
	Data[0] = 0x00;
	Data[1] = 0x00;

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_NFCFunction_ReadDataLength_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_NFCFunction_ReadDataLength (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_NFCFunction_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_NFCFunction_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_NFCFunction_WriteData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ReadActiveDiagSession_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadActiveDiagSession_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ReadActiveDiagSession_ReadData (returns application error)
 *********************************************************************************************************************/
	// F1 86
	Dcm_SesCtrlType lSession;
	(void)Dcm_GetSesCtrlType(&lSession); /* This API always returns E_OK */

	Data[0] = lSession;

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ReadFingerprint_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_ReadFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_ReadFingerprint_ReadData (returns application error)
 *********************************************************************************************************************/

	// F1 5B
	/*
	Data[0] = 0x20;			// BCD
	Data[1] = 0x06;
	Data[2] = 0x05;			//
	Data[3] = 0xA3;			// Hex
	Data[4] = 0xB5;
	Data[5] = 0x83;
	Data[6] = 0xC2;
	Data[7] = 0xFE;
	Data[8] = 0x02;
	Data[9] = 0x00;
	Data[10] = 0x00;
	Data[11] = 0x01;
	*/

	HAL_RWEEPROM(&eeerom_data.Did_F15B[0],&Data[0],12);		// Read Data from EEEPROM

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_RepairShopFingerPrint_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_RepairShopFingerPrint_ReadData (returns application error)
 *********************************************************************************************************************/

	HAL_RWEEPROM(&eeerom_data.Did_F198[0],&Data[0],12);		// Read Data from EEEPROM
	//F1 98
	//uint8 i;
	//for(i=0;i<12;i++)
	//{
	//	while ((FTFC-> FSTAT & FTFC_FSTAT_CCIF_MASK) == 0){}
	//	Data[i] = eeerom_data.Did_F198[i];
	//}

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_RepairShopFingerPrint_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_RepairShopFingerPrint_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_RepairShopFingerPrint_WriteData (returns application error)
 *********************************************************************************************************************/

	// F1 98
	//uint8 i;
	//for(i=0;i<12;i++)
	//{
	//	eeerom_data.Did_F198[i] = ErrorCode[i];
	//}
	//HAL_RWEEPROM(&ErrorCode[0],&eeerom_data.Did_F198[0],12);		// Write Data to EEEPROM
	HAL_RWEEPROM(&Data[0],&eeerom_data.Did_F198[0],12);		// Write Data to EEEPROM


  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemName_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemName_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemName_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemName_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemName_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemName_ReadData (returns application error)
 *********************************************************************************************************************/


	//F1 97---WLC
	Data[0] = 0x57;
	Data[1] = 0x4C;
	Data[2] = 0x43;
	Data[3] = 0x20;
	Data[4] = 0x20;
	Data[5] = 0x20;
	Data[6] = 0x20;
	Data[7] = 0x20;

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemName_ReadDataLength_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemName_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemName_ReadDataLength (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSESVNumber_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSESVNumber_ReadData (returns application error)
 *********************************************************************************************************************/

	//F1 95
	Data[0] = 0x20;
	Data[1] = 0x20;
	Data[2] = 0x09;
	Data[3] = 0x30;
	Data[4] = 0x00;
	Data[5] = 0x01;


	//HAL_RWEEPROM(&eeerom_data.Did_F195[0],&Data[0],SysSupplier_SWVerNum_SIZE);

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSESVNumber_ReadDataLength_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSESVNumber_ReadDataLength (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSESVNumber_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_SystemSESVNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSESVNumber_WriteData(const uint8 *Data, uint16 DataLength, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSESVNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSESVNumber_E_NOT_OK
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSESVNumber_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSESVNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSESVNumber_WriteData (returns application error)
 *********************************************************************************************************************/

	//HAL_RWEEPROM(&ErrorCode[0],&eeerom_data.Did_F195[0],SysSupplier_SWVerNum_SIZE);		// Write Data to EEEPROM

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData (returns application error)
 *********************************************************************************************************************/
	//FD 30
	Data[0] = 0x20;
	Data[1] = 0x20;
	Data[2] = 0x09;
	Data[3] = 0x30;
	Data[4] = 0x00;
	Data[5] = 0x01;

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSHV_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSHV_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSHV_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSHV_ReadData (returns application error)
 *********************************************************************************************************************/

	//F1 93
	Data[0] = 0x20;
	Data[1] = 0x20;
	Data[2] = 0x09;
	Data[3] = 0x30;
	Data[4] = 0x00;
	Data[5] = 0x01;


	//HAL_RWEEPROM(&eeerom_data.Did_F193[0],&Data[0],SysSupplier_HWVerNum_SIZE);


  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSHV_ReadDataLength_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSHV_ReadDataLength (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_SystemSHV_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_SystemSHV>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_SystemSHV_WriteData(const uint8 *Data, uint16 DataLength, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_SystemSHV_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_SystemSHV_E_NOT_OK
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSHV_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSHV_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSHV_WriteData (returns application error)
 *********************************************************************************************************************/

	//HAL_RWEEPROM(&ErrorCode[0],&eeerom_data.Did_F193[0],SysSupplier_HWVerNum_SIZE);		// Write Data to EEEPROM

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSupplierIdData_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_SystemSupplierIdData_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_SystemSupplierIdData_ReadData (returns application error)
 *********************************************************************************************************************/

	// F1 8A
	Data[0] = 0x56;			// "V"
	Data[1] = 0x35;			// "5"
	Data[2] = 0x31;			// "1"
	Data[3] = 0x33;			// "3"
	Data[4] = 0x36;			// "6"
	Data[5] = 0x34;			// "4"
	Data[6] = 0x20;			// 空格
	Data[7] = 0x20;			// 空格


	//HAL_RWEEPROM(&eeerom_data.Did_F18A[0],&Data[0],SysSupplier_ID_SIZE);

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VIN_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VIN_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VIN_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VIN_ReadData (returns application error)
 *********************************************************************************************************************/

	// F190 Read

	//uint8 i;
	//for(i=0;i<17;i++)
	//{
	//	Data[i] = eeerom_data.Did_F190[i];
	//}
	HAL_RWEEPROM(&eeerom_data.Did_F190[0],&Data[0],17);		// Read Data from EEEPROM


  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VIN_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VIN_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VIN_WriteData (returns application error)
 *********************************************************************************************************************/

	// F190 Write
	//uint8 i;
	//for(i=0;i<17;i++)
	//{
	//	eeerom_data.Did_F190[i] = ErrorCode[i];
	//}
	HAL_RWEEPROM(&Data[0],&eeerom_data.Did_F190[0],17);		// Write Data to EEEPROM


  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
 *     Argument Data: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_CalibrarionPartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrationBaseline_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrationBaseline_ReadData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrationBaseline_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_CalibrationBaseline_WriteData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SoftwarBaseline_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SoftwarBaseline_ReadData (returns application error)
 *********************************************************************************************************************/
	//F1 19
	Data[0] = 0x30;
	Data[1] = 0x31;

	//HAL_RWEEPROM(&eeerom_data.Did_F119[0],&Data[0],VehManuf_SWBaseLine_SIZE);

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_SoftwarBaseline_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_VM_SoftwarBaseline>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_SoftwarBaseline_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_SoftwarBaseline_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_SoftwarBaseline_E_NOT_OK
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SoftwarBaseline_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SoftwarBaseline_WriteData (returns application error)
 *********************************************************************************************************************/

	//HAL_RWEEPROM(&Data[0],&eeerom_data.Did_F119[0],VehManuf_SWBaseLine_SIZE);		// Write Data to EEEPROM

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SofwarePartNumber_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SofwarePartNumber_ReadData (returns application error)
 *********************************************************************************************************************/
	//F1 18
	Data[0] = 0x50;
	Data[1] = 0x30;
	Data[2] = 0x30;
	Data[3] = 0x36;
	Data[4] = 0x31;
	Data[5] = 0x35;
	Data[6] = 0x35;
	Data[7] = 0x34;
	Data[8] = 0x20;
	Data[9] = 0x41;
	Data[10] = 0x48;


	//HAL_RWEEPROM(&eeerom_data.Did_F118[0],&Data[0],VehManuf_SWPartNum_SIZE);


  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DataServices_DcmDspData_VM_SofwarePartNumber_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_DcmDspData_VM_SofwarePartNumber>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DataServices_DcmDspData_VM_SofwarePartNumber_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data4ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_DcmDspData_VM_SofwarePartNumber_DCM_E_PENDING
 *   RTE_E_DataServices_DcmDspData_VM_SofwarePartNumber_E_NOT_OK
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SofwarePartNumber_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SofwarePartNumber_WriteData (returns application error)
 *********************************************************************************************************************/
	//HAL_RWEEPROM(&Data[0],&eeerom_data.Did_F118[0],VehManuf_SWPartNum_SIZE);		// Write Data to EEEPROM
  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SparepartNumber_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SparepartNumber_ReadData (returns application error)
 *********************************************************************************************************************/
	//F1 87

	HAL_RWEEPROM(&eeerom_data.Did_F187[0],&Data[0],11);		// Read Data from EEEPROM

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SparepartNumber_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_SparepartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_SparepartNumber_WriteData (returns application error)
 *********************************************************************************************************************/

	HAL_RWEEPROM(&Data[0],&eeerom_data.Did_F187[0],11);		// Write Data to EEEPROM

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_Specialdatabaseline_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_Specialdatabaseline_ReadData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_WLCCtrlSts_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_WLCCtrlSts_ReadData (returns application error)
 *********************************************************************************************************************/
	//41 01
	Data[0] = 0x00;

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_WLCCtrlSts_ReadDataLength_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_WLCCtrlSts_ReadDataLength (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_WLCCtrlSts_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_DcmDspData_WLCCtrlSts_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_DcmDspData_WLCCtrlSts_WriteData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_VM_HardwareBaseline_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwareBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_VM_HardwareBaseline_ReadData (returns application error)
 *********************************************************************************************************************/
	//F1 11

	Data[0] = 0x00;
	Data[1] = 0x01;

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_VM_HardwarePartNumber_ReadData_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) DataServices_Diag_VM_HardwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DataServices_Diag_VM_HardwarePartNumber_ReadData (returns application error)
 *********************************************************************************************************************/
	//F1 10
	Data[0] = 0x52;
	Data[1] = 0x30;
	Data[2] = 0x30;
	Data[3] = 0x31;
	Data[4] = 0x30;
	Data[5] = 0x31;
	Data[6] = 0x31;
	Data[7] = 0x31;
	Data[8] = 0x20;
	Data[9] = 0x41;
	Data[10] = 0x4D;

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ModeChange_Full_Comm_Entry_Runnable
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * This runnable is never executed by the RTE.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: ModeChange_Full_Comm_Entry_Runnable_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Communication_Read_APP_CODE) ModeChange_Full_Comm_Entry_Runnable(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: ModeChange_Full_Comm_Entry_Runnable
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_01_CompareKey_doc
 *********************************************************************************************************************/

unsigned char crc8Fun(unsigned char *data, int length)
{

	unsigned char t_crc;
	int f, b;
	t_crc = 0xFF;
	for (f = 0; f < length; f++)
	{
				t_crc ^= data[f];
				for (b = 0; b < 8; b++)
				{
					if ((t_crc & 0x80) != 0)
					{
						t_crc <<= 1;
						t_crc ^= 0x11D;
					}
					else
					{
						t_crc <<= 1;
					}
				}
	}
	return ~t_crc;
}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
uint8 GlobalSeed[6];
uint8 Keytem[4];
uint32 bl_extds_seed= 0xbeafdada;
FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_01_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_01_CompareKey (returns application error)
 *********************************************************************************************************************/
		int seedlength = 6;
		unsigned char buf_byte[6];
		unsigned char crc_byte[7];
        uint8 ret;
		GlobalSeed[4] = 0x98;//high byte of secret code(example)
		GlobalSeed[5] = 0x7D;//low byte of secret code(example)
		buf_byte[0] = GlobalSeed[0];
		buf_byte[1] = GlobalSeed[1];
		buf_byte[2] = GlobalSeed[2];
		buf_byte[3] = GlobalSeed[3];
		buf_byte[4] = GlobalSeed[4];
		buf_byte[5] = GlobalSeed[5];

		crc_byte[0] = crc8Fun(buf_byte,seedlength);
		buf_byte[0] = crc_byte[0];
		crc_byte[1] = crc8Fun(buf_byte,seedlength);
		buf_byte[0] = GlobalSeed[0];
		buf_byte[1] = crc_byte[1];
		crc_byte[2] = crc8Fun(buf_byte, seedlength);
		buf_byte[1] = GlobalSeed[1];
		buf_byte[2] = crc_byte[2];
		crc_byte[3] = crc8Fun(buf_byte, seedlength);
		buf_byte[2] = GlobalSeed[2];
		buf_byte[3] = crc_byte[3];
		crc_byte[4] = crc8Fun(buf_byte, seedlength);
		buf_byte[3] = GlobalSeed[3];
		buf_byte[4] = crc_byte[4];
		crc_byte[5] = crc8Fun(buf_byte, seedlength);
		buf_byte[4] = GlobalSeed[4];
		buf_byte[5] = crc_byte[5];
		crc_byte[6] = crc8Fun(buf_byte, seedlength);

		if (crc_byte[3] == 0 && crc_byte[4] == 0 && crc_byte[5] == 0 && crc_byte[6] == 0)
		{
			Keytem[0] = crc_byte[1];
			Keytem[1] = crc_byte[2];
			Keytem[2] = crc_byte[3];
			Keytem[3] = crc_byte[4];
		}
		else
		{
			Keytem[0] = crc_byte[3];
			Keytem[1] = crc_byte[4];
			Keytem[2] = crc_byte[5];
			Keytem[3] = crc_byte[6];
		}
		if((Key[0]==Keytem[0])&&
				Key[1]==Keytem[1]&&
				Key[2]==Keytem[2]&&
				Key[3]==Keytem[3])
		{
			ret= RTE_E_OK;
		}
		else
		{    //修改   错误的密钥   第一次  35  第二次35  第三次 36
			 ret=RTE_E_SecurityAccess_Level_02_DCM_E_COMPARE_KEY_FAILED;
			//ret= RTE_E_INVALID;
		}
	//	*sizeKey = 4;
	// If the return value is false the flash tool stops


   return ret;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_01_GetSeed_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_01_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_01_GetSeed (returns application error)
 *********************************************************************************************************************/

	uint32 u32Seed; /* intentional not initialized to use the stack random value 用RAM随机数*/
	uint32 u32Time;


	//u32Time = (uint32)ST_GetTimerTick();
	bl_extds_seed = bl_extds_seed ^ u32Seed ^ u32Time ^ 0x95774321;

	bl_extds_seed=bl_extds_seed | 0x10000000;

	if(bl_extds_seed==0xffffffff)
	{
		bl_extds_seed= 0x73573321;
	}



	Seed[0] = (uint8)(bl_extds_seed>>24);
	Seed[1] = (uint8)(bl_extds_seed>>16);
	Seed[2] = (uint8)(bl_extds_seed>>8);
	Seed[3] = (uint8)(bl_extds_seed);

	GlobalSeed[0]=Seed[0];
	GlobalSeed[1]=Seed[1];
	GlobalSeed[2]=Seed[2];
	GlobalSeed[3]=Seed[3];
  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_02_CompareKey_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_02_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_02_CompareKey (returns application error)
 *********************************************************************************************************************/

	int seedlength = 6;
	unsigned char buf_byte[6];
	unsigned char crc_byte[7];
    uint8 ret;
	GlobalSeed[4] = 0x53;//high byte of secret code(example)
	GlobalSeed[5] = 0x1F;//low byte of secret code(example)
	buf_byte[0] = GlobalSeed[0];
	buf_byte[1] = GlobalSeed[1];
	buf_byte[2] = GlobalSeed[2];
	buf_byte[3] = GlobalSeed[3];
	buf_byte[4] = GlobalSeed[4];
	buf_byte[5] = GlobalSeed[5];

	crc_byte[0] = crc8Fun(buf_byte,seedlength);
	buf_byte[0] = crc_byte[0];
	crc_byte[1] = crc8Fun(buf_byte,seedlength);
	buf_byte[0] = GlobalSeed[0];
	buf_byte[1] = crc_byte[1];
	crc_byte[2] = crc8Fun(buf_byte, seedlength);
	buf_byte[1] = GlobalSeed[1];
	buf_byte[2] = crc_byte[2];
	crc_byte[3] = crc8Fun(buf_byte, seedlength);
	buf_byte[2] = GlobalSeed[2];
	buf_byte[3] = crc_byte[3];
	crc_byte[4] = crc8Fun(buf_byte, seedlength);
	buf_byte[3] = GlobalSeed[3];
	buf_byte[4] = crc_byte[4];
	crc_byte[5] = crc8Fun(buf_byte, seedlength);
	buf_byte[4] = GlobalSeed[4];
	buf_byte[5] = crc_byte[5];
	crc_byte[6] = crc8Fun(buf_byte, seedlength);

	if (crc_byte[3] == 0 && crc_byte[4] == 0 && crc_byte[5] == 0 && crc_byte[6] == 0)
	{
		Keytem[0] = crc_byte[1];
		Keytem[1] = crc_byte[2];
		Keytem[2] = crc_byte[3];
		Keytem[3] = crc_byte[4];
	}
	else
	{
		Keytem[0] = crc_byte[3];
		Keytem[1] = crc_byte[4];
		Keytem[2] = crc_byte[5];
		Keytem[3] = crc_byte[6];
	}
	if((Key[0]==Keytem[0])&&
			Key[1]==Keytem[1]&&
			Key[2]==Keytem[2]&&
			Key[3]==Keytem[3])
	{
		ret= RTE_E_OK;
	}
	else
	{
         ret=RTE_E_SecurityAccess_Level_02_DCM_E_COMPARE_KEY_FAILED;
	//	ret= RTE_E_INVALID;
	}
//	*sizeKey = 4;
// If the return value is false the flash tool stops


return ret;


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_02_GetSeed_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_02_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_02_GetSeed (returns application error)
 *********************************************************************************************************************/

	uint32 u32Seed; /* intentional not initialized to use the stack random value 用RAM随机数*/
	uint32 u32Time;


	//u32Time = (uint32)ST_GetTimerTick();
	bl_extds_seed = bl_extds_seed ^ u32Seed ^ u32Time ^ 0x95774321;

	bl_extds_seed=bl_extds_seed | 0x10000000;

	if(bl_extds_seed==0xffffffff)
	{
		bl_extds_seed= 0x73573321;
	}



	Seed[0] = (uint8)(bl_extds_seed>>24);
	Seed[1] = (uint8)(bl_extds_seed>>16);
	Seed[2] = (uint8)(bl_extds_seed>>8);
	Seed[3] = (uint8)(bl_extds_seed);

	GlobalSeed[0]=Seed[0];
	GlobalSeed[1]=Seed[1];
	GlobalSeed[2]=Seed[2];
	GlobalSeed[3]=Seed[3];
    return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_04_CompareKey_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_04_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_04_CompareKey (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_04_GetSeed_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, Communication_Read_APP_CODE) SecurityAccess_Level_04_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_Level_04_GetSeed (returns application error)
 *********************************************************************************************************************/

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define Communication_Read_APP_STOP_SEC_CODE
#include "Communication_Read_APP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/



#if 0
/***  Start of saved code (symbol: documentation area:DataServices_Diag_VM_HardwarePartNumber_WriteData_doc)  */


/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: documentation area:DataServices_Diag_VM_HardwareBaseline_WriteData_doc)  */


/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: runnable implementation:DataServices_DcmDspData_VM_SoftwarBaseline_WriteData)  */

  return RTE_E_OK;

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: runnable implementation:DataServices_DcmDspData_SystemSESVNumber_WriteData)  */

  return RTE_E_OK;

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: runnable implementation:DataServices_DcmDspData_VM_SofwarePartNumber_WriteData)  */

  return RTE_E_OK;

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: documentation area:DataServices_DcmDspData_VM_SoftwarBaseline_WriteData_doc)  */


/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: documentation area:DataServices_DcmDspData_VM_Specialdatabaseline_WriteData_doc)  */


/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: documentation area:DataServices_DcmDspData_VM_SofwarePartNumber_WriteData_doc)  */


/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: runnable implementation:DataServices_DcmDspData_VM_Specialdatabaseline_WriteData)  */

  return RTE_E_OK;

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: runnable implementation:DataServices_Diag_VM_HardwareBaseline_WriteData)  */

  return RTE_E_OK;

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: runnable implementation:DataServices_Diag_VM_HardwarePartNumber_WriteData)  */

  return RTE_E_OK;

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: documentation area:DataServices_DcmDspData_SystemSESVNumber_WriteData_doc)  */


/***  End of saved code  ************************************************************************************/
#endif


#if 0
/***  Start of saved code (symbol: runnable implementation:DataServices_DcmDspData_SystemSHV_WriteData)  ****/

  return RTE_E_OK;

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: documentation area:DataServices_DcmDspData_SystemSHV_WriteData_doc)  *****/


/***  End of saved code  ************************************************************************************/
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
