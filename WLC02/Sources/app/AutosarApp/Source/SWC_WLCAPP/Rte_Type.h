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
 *             File:  Rte_Type.h
 *           Config:  D:/Auto/Demo/WLCProject/WLC.dpa
 *        SW-C Type:  SWC_WLCAPP
 *  Generation Time:  2020-09-22 21:25:06
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Header file containing user defined AUTOSAR types and RTE structures (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_TYPE_H
# define _RTE_TYPE_H

# include "Rte.h"


/**********************************************************************************************************************
 * Data type definitions
 *********************************************************************************************************************/

# define Rte_TypeDef_dtRef_const_VOID
typedef const void * dtRef_const_VOID;

# define Rte_TypeDef_DataArrayType_uint8_1
typedef uint8 DataArrayType_uint8_1[1];

# define Rte_TypeDef_DataArrayType_uint8_2
typedef uint8 DataArrayType_uint8_2[2];

# define Rte_TypeDef_DataArrayType_uint8_3
typedef uint8 DataArrayType_uint8_3[3];

# define Rte_TypeDef_DataArrayType_uint8_6
typedef uint8 DataArrayType_uint8_6[6];

# define Rte_TypeDef_ComM_ModeType
typedef uint8 ComM_ModeType;

# define Rte_TypeDef_Dem_EventStatusType
typedef uint8 Dem_EventStatusType;

# define Rte_TypeDef_Dem_OperationCycleStateType
typedef uint8 Dem_OperationCycleStateType;

# define Rte_TypeDef_NvM_RequestResultType
typedef uint8 NvM_RequestResultType;

# define Rte_TypeDef_NvM_ServiceIdType
typedef uint8 NvM_ServiceIdType;


# ifndef RTE_SUPPRESS_UNUSED_DATATYPES
/**********************************************************************************************************************
 * Unused Data type definitions
 *********************************************************************************************************************/

#  define Rte_TypeDef_CGW_03_CRC
typedef uint8 CGW_03_CRC;

#  define Rte_TypeDef_CGW_03_MsgCntr
typedef uint8 CGW_03_MsgCntr;

#  define Rte_TypeDef_CGW_WLC_CRC
typedef uint8 CGW_WLC_CRC;

#  define Rte_TypeDef_CGW_WLC_MsgCntr
typedef uint8 CGW_WLC_MsgCntr;

#  define Rte_TypeDef_Day
typedef uint8 Day;

#  define Rte_TypeDef_Hr
typedef uint8 Hr;

#  define Rte_TypeDef_Min
typedef uint8 Min;

#  define Rte_TypeDef_Sec
typedef uint8 Sec;

#  define Rte_TypeDef_UsrData0_WLC
typedef uint8 UsrData0_WLC;

#  define Rte_TypeDef_UsrData1_WLC
typedef uint8 UsrData1_WLC;

#  define Rte_TypeDef_UsrData2_WLC
typedef uint8 UsrData2_WLC;

#  define Rte_TypeDef_UsrData3_WLC
typedef uint8 UsrData3_WLC;

#  define Rte_TypeDef_UsrData4_WLC
typedef uint8 UsrData4_WLC;

#  define Rte_TypeDef_UsrData5_WLC
typedef uint8 UsrData5_WLC;

#  define Rte_TypeDef_VehOdometer
typedef uint32 VehOdometer;

#  define Rte_TypeDef_VehSpd
typedef uint16 VehSpd;

#  define Rte_TypeDef_WLCMuteViaHW
typedef boolean WLCMuteViaHW;

#  define Rte_TypeDef_WLC_01_CRC
typedef uint8 WLC_01_CRC;

#  define Rte_TypeDef_WLC_01_MsgCntr
typedef uint8 WLC_01_MsgCntr;

#  define Rte_TypeDef_WLC_02_CRC
typedef uint8 WLC_02_CRC;

#  define Rte_TypeDef_WLC_02_MsgCntr
typedef uint8 WLC_02_MsgCntr;

#  define Rte_TypeDef_Yr
typedef uint8 Yr;

#  define Rte_TypeDef_dtRef_VOID
typedef void * dtRef_VOID;

#  define Rte_TypeDef_ComfEna
typedef uint8 ComfEna;

#  define Rte_TypeDef_ComfEna_ASIL
typedef uint8 ComfEna_ASIL;

#  define Rte_TypeDef_ImobEnaReq
typedef uint8 ImobEnaReq;

#  define Rte_TypeDef_Mth
typedef uint8 Mth;

#  define Rte_TypeDef_VehState
typedef uint8 VehState;

#  define Rte_TypeDef_VehState_ASIL
typedef uint8 VehState_ASIL;

#  define Rte_TypeDef_WLCChrgFctEnaReq
typedef uint8 WLCChrgFctEnaReq;

#  define Rte_TypeDef_WLCChrgRate
typedef uint8 WLCChrgRate;

#  define Rte_TypeDef_WLCChrgSts
typedef uint8 WLCChrgSts;

#  define Rte_TypeDef_WLCCtrlSts
typedef uint8 WLCCtrlSts;

#  define Rte_TypeDef_WLCFailSts
typedef uint8 WLCFailSts;

#  define Rte_TypeDef_WLCImobSts
typedef uint8 WLCImobSts;

#  define Rte_TypeDef_DataArray_Type_2
typedef uint8 DataArray_Type_2[2];

#  define Rte_TypeDef_Dcm_Data10ByteType
typedef uint8 Dcm_Data10ByteType[10];

#  define Rte_TypeDef_Dcm_Data11ByteType
typedef uint8 Dcm_Data11ByteType[11];

#  define Rte_TypeDef_Dcm_Data12ByteType
typedef uint8 Dcm_Data12ByteType[12];

#  define Rte_TypeDef_Dcm_Data17ByteType
typedef uint8 Dcm_Data17ByteType[17];

#  define Rte_TypeDef_Dcm_Data1ByteType
typedef uint8 Dcm_Data1ByteType[1];

#  define Rte_TypeDef_Dcm_Data25ByteType
typedef uint8 Dcm_Data25ByteType[25];

#  define Rte_TypeDef_Dcm_Data2ByteType
typedef uint8 Dcm_Data2ByteType[2];

#  define Rte_TypeDef_Dcm_Data3ByteType
typedef uint8 Dcm_Data3ByteType[3];

#  define Rte_TypeDef_Dcm_Data4ByteType
typedef uint8 Dcm_Data4ByteType[4];

#  define Rte_TypeDef_Dcm_Data6ByteType
typedef uint8 Dcm_Data6ByteType[6];

#  define Rte_TypeDef_Dcm_Data8ByteType
typedef uint8 Dcm_Data8ByteType[8];

#  define Rte_TypeDef_Dem_MaxDataValueType
typedef uint8 Dem_MaxDataValueType[6];

#  define Rte_TypeDef_ComM_InhibitionStatusType
typedef uint8 ComM_InhibitionStatusType;

#  define Rte_TypeDef_ComM_UserHandleType
typedef uint8 ComM_UserHandleType;

#  define Rte_TypeDef_Dem_DTCGroupType
typedef uint32 Dem_DTCGroupType;

#  define Rte_TypeDef_Dem_DTCStatusMaskType
typedef uint8 Dem_DTCStatusMaskType;

#  define Rte_TypeDef_Dem_EventIdType
typedef uint16 Dem_EventIdType;

#  define Rte_TypeDef_Dem_OperationCycleIdType
typedef uint8 Dem_OperationCycleIdType;

#  define Rte_TypeDef_Dem_RatioIdType
typedef uint16 Dem_RatioIdType;

#  define Rte_TypeDef_EcuM_TimeType
typedef uint32 EcuM_TimeType;

#  define Rte_TypeDef_EcuM_UserType
typedef uint8 EcuM_UserType;

#  define Rte_TypeDef_NvM_BlockIdType
typedef uint16 NvM_BlockIdType;

#  define Rte_TypeDef_TimeInMicrosecondsType
typedef uint32 TimeInMicrosecondsType;

#  define Rte_TypeDef_BswM_ESH_Mode
typedef uint8 BswM_ESH_Mode;

#  define Rte_TypeDef_BswM_ESH_RunRequest
typedef uint8 BswM_ESH_RunRequest;

#  define Rte_TypeDef_Dcm_CommunicationModeType
typedef uint8 Dcm_CommunicationModeType;

#  define Rte_TypeDef_Dcm_ConfirmationStatusType
typedef uint8 Dcm_ConfirmationStatusType;

#  define Rte_TypeDef_Dcm_ControlDtcSettingType
typedef uint8 Dcm_ControlDtcSettingType;

#  define Rte_TypeDef_Dcm_DiagnosticSessionControlType
typedef uint8 Dcm_DiagnosticSessionControlType;

#  define Rte_TypeDef_Dcm_EcuResetType
typedef uint8 Dcm_EcuResetType;

#  define Rte_TypeDef_Dcm_NegativeResponseCodeType
typedef uint8 Dcm_NegativeResponseCodeType;

#  define Rte_TypeDef_Dcm_OpStatusType
typedef uint8 Dcm_OpStatusType;

#  define Rte_TypeDef_Dcm_ProtocolType
typedef uint8 Dcm_ProtocolType;

#  define Rte_TypeDef_Dcm_RequestKindType
typedef uint8 Dcm_RequestKindType;

#  define Rte_TypeDef_Dcm_SecLevelType
typedef uint8 Dcm_SecLevelType;

#  define Rte_TypeDef_Dcm_SesCtrlType
typedef uint8 Dcm_SesCtrlType;

#  define Rte_TypeDef_Dem_DTCFormatType
typedef uint8 Dem_DTCFormatType;

#  define Rte_TypeDef_Dem_DTCKindType
typedef uint8 Dem_DTCKindType;

#  define Rte_TypeDef_Dem_DTCOriginType
typedef uint16 Dem_DTCOriginType;

#  define Rte_TypeDef_Dem_DTCSeverityType
typedef uint8 Dem_DTCSeverityType;

#  define Rte_TypeDef_Dem_DTRControlType
typedef uint8 Dem_DTRControlType;

#  define Rte_TypeDef_Dem_DebounceResetStatusType
typedef uint8 Dem_DebounceResetStatusType;

#  define Rte_TypeDef_Dem_DebouncingStateType
typedef uint8 Dem_DebouncingStateType;

#  define Rte_TypeDef_Dem_IndicatorStatusType
typedef uint8 Dem_IndicatorStatusType;

#  define Rte_TypeDef_Dem_InitMonitorReasonType
typedef uint8 Dem_InitMonitorReasonType;

#  define Rte_TypeDef_Dem_IumprDenomCondIdType
typedef uint8 Dem_IumprDenomCondIdType;

#  define Rte_TypeDef_Dem_IumprDenomCondStatusType
typedef uint8 Dem_IumprDenomCondStatusType;

#  define Rte_TypeDef_Dem_IumprReadinessGroupType
typedef uint8 Dem_IumprReadinessGroupType;

#  define Rte_TypeDef_Dem_MonitorStatusType
typedef uint8 Dem_MonitorStatusType;

#  define Rte_TypeDef_Dem_UdsStatusByteType
typedef uint8 Dem_UdsStatusByteType;

#  define Rte_TypeDef_EcuM_BootTargetType
typedef uint8 EcuM_BootTargetType;

#  define Rte_TypeDef_EcuM_ModeType
typedef uint8 EcuM_ModeType;

#  define Rte_TypeDef_EcuM_ShutdownCauseType
typedef uint8 EcuM_ShutdownCauseType;

#  define Rte_TypeDef_EcuM_StateType
typedef uint8 EcuM_StateType;

# endif

#endif /* _RTE_TYPE_H */
