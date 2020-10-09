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
 *             File:  Rte_Communication_Read_APP_Type.h
 *           Config:  WLC.dpa
 *      ECU-Project:  WLC
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Application types header file for SW-C <Communication_Read_APP>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_COMMUNICATION_READ_APP_TYPE_H
# define _RTE_COMMUNICATION_READ_APP_TYPE_H

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

# include "Rte_Type.h"

# ifndef RTE_CORE

/**********************************************************************************************************************
 * Range, Invalidation, Enumeration and Bit Field Definitions
 *********************************************************************************************************************/

#  ifndef RELEASED
#   define RELEASED (0U)
#  endif

#  ifndef REQUESTED
#   define REQUESTED (1U)
#  endif

#  ifndef Cx0_Comfort_not_enabled
#   define Cx0_Comfort_not_enabled (0U)
#  endif

#  ifndef Cx1_Comfort_enabled
#   define Cx1_Comfort_enabled (1U)
#  endif

#  ifndef Cx2_Reserved
#   define Cx2_Reserved (2U)
#  endif

#  ifndef Cx3_Invalid
#   define Cx3_Invalid (3U)
#  endif

#  ifndef DCM_E_POSITIVERESPONSE
#   define DCM_E_POSITIVERESPONSE (0U)
#  endif

#  ifndef DCM_E_GENERALREJECT
#   define DCM_E_GENERALREJECT (16U)
#  endif

#  ifndef DCM_E_SERVICENOTSUPPORTED
#   define DCM_E_SERVICENOTSUPPORTED (17U)
#  endif

#  ifndef DCM_E_SUBFUNCTIONNOTSUPPORTED
#   define DCM_E_SUBFUNCTIONNOTSUPPORTED (18U)
#  endif

#  ifndef DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT
#   define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT (19U)
#  endif

#  ifndef DCM_E_RESPONSETOOLONG
#   define DCM_E_RESPONSETOOLONG (20U)
#  endif

#  ifndef DCM_E_BUSYREPEATREQUEST
#   define DCM_E_BUSYREPEATREQUEST (33U)
#  endif

#  ifndef DCM_E_CONDITIONSNOTCORRECT
#   define DCM_E_CONDITIONSNOTCORRECT (34U)
#  endif

#  ifndef DCM_E_REQUESTSEQUENCEERROR
#   define DCM_E_REQUESTSEQUENCEERROR (36U)
#  endif

#  ifndef DCM_E_NORESPONSEFROMSUBNETCOMPONENT
#   define DCM_E_NORESPONSEFROMSUBNETCOMPONENT (37U)
#  endif

#  ifndef DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION
#   define DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION (38U)
#  endif

#  ifndef DCM_E_REQUESTOUTOFRANGE
#   define DCM_E_REQUESTOUTOFRANGE (49U)
#  endif

#  ifndef DCM_E_SECURITYACCESSDENIED
#   define DCM_E_SECURITYACCESSDENIED (51U)
#  endif

#  ifndef DCM_E_INVALIDKEY
#   define DCM_E_INVALIDKEY (53U)
#  endif

#  ifndef DCM_E_EXCEEDNUMBEROFATTEMPTS
#   define DCM_E_EXCEEDNUMBEROFATTEMPTS (54U)
#  endif

#  ifndef DCM_E_REQUIREDTIMEDELAYNOTEXPIRED
#   define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED (55U)
#  endif

#  ifndef DCM_E_UPLOADDOWNLOADNOTACCEPTED
#   define DCM_E_UPLOADDOWNLOADNOTACCEPTED (112U)
#  endif

#  ifndef DCM_E_TRANSFERDATASUSPENDED
#   define DCM_E_TRANSFERDATASUSPENDED (113U)
#  endif

#  ifndef DCM_E_GENERALPROGRAMMINGFAILURE
#   define DCM_E_GENERALPROGRAMMINGFAILURE (114U)
#  endif

#  ifndef DCM_E_WRONGBLOCKSEQUENCECOUNTER
#   define DCM_E_WRONGBLOCKSEQUENCECOUNTER (115U)
#  endif

#  ifndef DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING
#   define DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING (120U)
#  endif

#  ifndef DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION
#   define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION (126U)
#  endif

#  ifndef DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION
#   define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION (127U)
#  endif

#  ifndef DCM_E_RPMTOOHIGH
#   define DCM_E_RPMTOOHIGH (129U)
#  endif

#  ifndef DCM_E_RPMTOOLOW
#   define DCM_E_RPMTOOLOW (130U)
#  endif

#  ifndef DCM_E_ENGINEISRUNNING
#   define DCM_E_ENGINEISRUNNING (131U)
#  endif

#  ifndef DCM_E_ENGINEISNOTRUNNING
#   define DCM_E_ENGINEISNOTRUNNING (132U)
#  endif

#  ifndef DCM_E_ENGINERUNTIMETOOLOW
#   define DCM_E_ENGINERUNTIMETOOLOW (133U)
#  endif

#  ifndef DCM_E_TEMPERATURETOOHIGH
#   define DCM_E_TEMPERATURETOOHIGH (134U)
#  endif

#  ifndef DCM_E_TEMPERATURETOOLOW
#   define DCM_E_TEMPERATURETOOLOW (135U)
#  endif

#  ifndef DCM_E_VEHICLESPEEDTOOHIGH
#   define DCM_E_VEHICLESPEEDTOOHIGH (136U)
#  endif

#  ifndef DCM_E_VEHICLESPEEDTOOLOW
#   define DCM_E_VEHICLESPEEDTOOLOW (137U)
#  endif

#  ifndef DCM_E_THROTTLE_PEDALTOOHIGH
#   define DCM_E_THROTTLE_PEDALTOOHIGH (138U)
#  endif

#  ifndef DCM_E_THROTTLE_PEDALTOOLOW
#   define DCM_E_THROTTLE_PEDALTOOLOW (139U)
#  endif

#  ifndef DCM_E_TRANSMISSIONRANGENOTINNEUTRAL
#   define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL (140U)
#  endif

#  ifndef DCM_E_TRANSMISSIONRANGENOTINGEAR
#   define DCM_E_TRANSMISSIONRANGENOTINGEAR (141U)
#  endif

#  ifndef DCM_E_BRAKESWITCH_NOTCLOSED
#   define DCM_E_BRAKESWITCH_NOTCLOSED (143U)
#  endif

#  ifndef DCM_E_SHIFTERLEVERNOTINPARK
#   define DCM_E_SHIFTERLEVERNOTINPARK (144U)
#  endif

#  ifndef DCM_E_TORQUECONVERTERCLUTCHLOCKED
#   define DCM_E_TORQUECONVERTERCLUTCHLOCKED (145U)
#  endif

#  ifndef DCM_E_VOLTAGETOOHIGH
#   define DCM_E_VOLTAGETOOHIGH (146U)
#  endif

#  ifndef DCM_E_VOLTAGETOOLOW
#   define DCM_E_VOLTAGETOOLOW (147U)
#  endif

#  ifndef DCM_E_VMSCNC_0
#   define DCM_E_VMSCNC_0 (240U)
#  endif

#  ifndef DCM_E_VMSCNC_1
#   define DCM_E_VMSCNC_1 (241U)
#  endif

#  ifndef DCM_E_VMSCNC_2
#   define DCM_E_VMSCNC_2 (242U)
#  endif

#  ifndef DCM_E_VMSCNC_3
#   define DCM_E_VMSCNC_3 (243U)
#  endif

#  ifndef DCM_E_VMSCNC_4
#   define DCM_E_VMSCNC_4 (244U)
#  endif

#  ifndef DCM_E_VMSCNC_5
#   define DCM_E_VMSCNC_5 (245U)
#  endif

#  ifndef DCM_E_VMSCNC_6
#   define DCM_E_VMSCNC_6 (246U)
#  endif

#  ifndef DCM_E_VMSCNC_7
#   define DCM_E_VMSCNC_7 (247U)
#  endif

#  ifndef DCM_E_VMSCNC_8
#   define DCM_E_VMSCNC_8 (248U)
#  endif

#  ifndef DCM_E_VMSCNC_9
#   define DCM_E_VMSCNC_9 (249U)
#  endif

#  ifndef DCM_E_VMSCNC_A
#   define DCM_E_VMSCNC_A (250U)
#  endif

#  ifndef DCM_E_VMSCNC_B
#   define DCM_E_VMSCNC_B (251U)
#  endif

#  ifndef DCM_E_VMSCNC_C
#   define DCM_E_VMSCNC_C (252U)
#  endif

#  ifndef DCM_E_VMSCNC_D
#   define DCM_E_VMSCNC_D (253U)
#  endif

#  ifndef DCM_E_VMSCNC_E
#   define DCM_E_VMSCNC_E (254U)
#  endif

#  ifndef DCM_INITIAL
#   define DCM_INITIAL (0U)
#  endif

#  ifndef DCM_PENDING
#   define DCM_PENDING (1U)
#  endif

#  ifndef DCM_CANCEL
#   define DCM_CANCEL (2U)
#  endif

#  ifndef DCM_FORCE_RCRRP_OK
#   define DCM_FORCE_RCRRP_OK (3U)
#  endif

#  ifndef DCM_FORCE_RCRRP_NOT_OK
#   define DCM_FORCE_RCRRP_NOT_OK (64U)
#  endif

#  ifndef Cx0_Disable
#   define Cx0_Disable (0U)
#  endif

#  ifndef Cx1_Enable_AID1
#   define Cx1_Enable_AID1 (1U)
#  endif

#  ifndef Cx2_Enable_AID2
#   define Cx2_Enable_AID2 (2U)
#  endif

#  ifndef Cx0_Unknown
#   define Cx0_Unknown (0U)
#  endif

#  ifndef Cx1_January
#   define Cx1_January (1U)
#  endif

#  ifndef Cx2_February
#   define Cx2_February (2U)
#  endif

#  ifndef Cx3_March
#   define Cx3_March (3U)
#  endif

#  ifndef Cx4_April
#   define Cx4_April (4U)
#  endif

#  ifndef Cx5_May
#   define Cx5_May (5U)
#  endif

#  ifndef Cx6_June
#   define Cx6_June (6U)
#  endif

#  ifndef Cx7_July
#   define Cx7_July (7U)
#  endif

#  ifndef Cx8_August
#   define Cx8_August (8U)
#  endif

#  ifndef Cx9_September
#   define Cx9_September (9U)
#  endif

#  ifndef CxA_October
#   define CxA_October (10U)
#  endif

#  ifndef CxB_November
#   define CxB_November (11U)
#  endif

#  ifndef CxC_December
#   define CxC_December (12U)
#  endif

#  ifndef CxD_Reserved
#   define CxD_Reserved (13U)
#  endif

#  ifndef CxE_Reserved
#   define CxE_Reserved (14U)
#  endif

#  ifndef CxF_Invalid
#   define CxF_Invalid (15U)
#  endif

#  ifndef Cx0_Parked_vehicle_Off_
#   define Cx0_Parked_vehicle_Off_ (0U)
#  endif

#  ifndef Cx1_Driver_present_On_
#   define Cx1_Driver_present_On_ (1U)
#  endif

#  ifndef Cx2_Driving
#   define Cx2_Driving (2U)
#  endif

#  ifndef Cx3_Software_update
#   define Cx3_Software_update (3U)
#  endif

#  ifndef Cx4_Reserved
#   define Cx4_Reserved (4U)
#  endif

#  ifndef Cx5_Reserved
#   define Cx5_Reserved (5U)
#  endif

#  ifndef Cx6_Reserved
#   define Cx6_Reserved (6U)
#  endif

#  ifndef Cx7_Reserved
#   define Cx7_Reserved (7U)
#  endif

#  ifndef Cx8_Reserved
#   define Cx8_Reserved (8U)
#  endif

#  ifndef Cx9_Reserved
#   define Cx9_Reserved (9U)
#  endif

#  ifndef CxA_Reserved
#   define CxA_Reserved (10U)
#  endif

#  ifndef CxB_Reserved
#   define CxB_Reserved (11U)
#  endif

#  ifndef CxC_Reserved
#   define CxC_Reserved (12U)
#  endif

#  ifndef Cx0_Disable_WLC_charging_function
#   define Cx0_Disable_WLC_charging_function (0U)
#  endif

#  ifndef Cx1_Enable_WLC_charging_function
#   define Cx1_Enable_WLC_charging_function (1U)
#  endif

#  ifndef Cx2_No_operation
#   define Cx2_No_operation (2U)
#  endif

#  ifndef Cx0_Not_started_
#   define Cx0_Not_started_ (0U)
#  endif

#  ifndef Cx1_Power_Requested_
#   define Cx1_Power_Requested_ (1U)
#  endif

#  ifndef Cx2_Power_Reduced_
#   define Cx2_Power_Reduced_ (2U)
#  endif

#  ifndef Cx3_Reserved
#   define Cx3_Reserved (3U)
#  endif

#  ifndef Cx0_WLC_stopped
#   define Cx0_WLC_stopped (0U)
#  endif

#  ifndef Cx1_WLC_on_going
#   define Cx1_WLC_on_going (1U)
#  endif

#  ifndef Cx2_Charge_complete
#   define Cx2_Charge_complete (2U)
#  endif

#  ifndef Cx0_WLC_enabled
#   define Cx0_WLC_enabled (0U)
#  endif

#  ifndef Cx1_WLC_disabled
#   define Cx1_WLC_disabled (1U)
#  endif

#  ifndef Cx0_No_failure
#   define Cx0_No_failure (0U)
#  endif

#  ifndef Cx1_Over_temperature
#   define Cx1_Over_temperature (1U)
#  endif

#  ifndef Cx2_Under_voltage
#   define Cx2_Under_voltage (2U)
#  endif

#  ifndef Cx3_Over_voltage
#   define Cx3_Over_voltage (3U)
#  endif

#  ifndef Cx4_Internal_error
#   define Cx4_Internal_error (4U)
#  endif

#  ifndef Cx5_Foreign_object_existing
#   define Cx5_Foreign_object_existing (5U)
#  endif

#  ifndef Cx6_Unknown_error
#   define Cx6_Unknown_error (6U)
#  endif

#  ifndef Cx7_Smartphone_no_response_or_error
#   define Cx7_Smartphone_no_response_or_error (7U)
#  endif

#  ifndef Cx8_Conductive_Device_Detected
#   define Cx8_Conductive_Device_Detected (8U)
#  endif

#  ifndef Cx1_Enable
#   define Cx1_Enable (1U)
#  endif

# endif /* RTE_CORE */


/**********************************************************************************************************************
 * Definitions for Mode Management
 *********************************************************************************************************************/
# ifndef RTE_MODETYPE_DcmCommunicationControl
#  define RTE_MODETYPE_DcmCommunicationControl
typedef uint8 Rte_ModeType_DcmCommunicationControl;
# endif
# ifndef RTE_MODETYPE_DcmControlDtcSetting
#  define RTE_MODETYPE_DcmControlDtcSetting
typedef uint8 Rte_ModeType_DcmControlDtcSetting;
# endif
# ifndef RTE_MODETYPE_DcmDiagnosticSessionControl
#  define RTE_MODETYPE_DcmDiagnosticSessionControl
typedef uint8 Rte_ModeType_DcmDiagnosticSessionControl;
# endif
# ifndef RTE_MODETYPE_DcmEcuReset
#  define RTE_MODETYPE_DcmEcuReset
typedef uint8 Rte_ModeType_DcmEcuReset;
# endif

# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM (0U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM (0U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM (1U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM (1U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM (2U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM (2U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORMAL (3U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORMAL
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORMAL (3U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM (4U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM (4U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM (5U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM (5U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM (6U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM (6U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM (7U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM (7U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM (8U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM (8U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM (9U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM (9U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM (10U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM (10U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM (11U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM (11U)
# endif
# define RTE_TRANSITION_Communication_Read_APP_DcmCommunicationControl (12U)
# ifndef RTE_TRANSITION_DcmCommunicationControl
#  define RTE_TRANSITION_DcmCommunicationControl (12U)
# endif

# define RTE_MODE_Communication_Read_APP_DcmControlDtcSetting_ENABLEDTCSETTING (0U)
# ifndef RTE_MODE_DcmControlDtcSetting_ENABLEDTCSETTING
#  define RTE_MODE_DcmControlDtcSetting_ENABLEDTCSETTING (0U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmControlDtcSetting_DISABLEDTCSETTING (1U)
# ifndef RTE_MODE_DcmControlDtcSetting_DISABLEDTCSETTING
#  define RTE_MODE_DcmControlDtcSetting_DISABLEDTCSETTING (1U)
# endif
# define RTE_TRANSITION_Communication_Read_APP_DcmControlDtcSetting (2U)
# ifndef RTE_TRANSITION_DcmControlDtcSetting
#  define RTE_TRANSITION_DcmControlDtcSetting (2U)
# endif

# define RTE_MODE_Communication_Read_APP_DcmDiagnosticSessionControl_DEFAULT_SESSION (1U)
# ifndef RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION
#  define RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION (1U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmDiagnosticSessionControl_PROGRAMMING_SESSION (2U)
# ifndef RTE_MODE_DcmDiagnosticSessionControl_PROGRAMMING_SESSION
#  define RTE_MODE_DcmDiagnosticSessionControl_PROGRAMMING_SESSION (2U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmDiagnosticSessionControl_EXTENDED_SESSION (3U)
# ifndef RTE_MODE_DcmDiagnosticSessionControl_EXTENDED_SESSION
#  define RTE_MODE_DcmDiagnosticSessionControl_EXTENDED_SESSION (3U)
# endif
# define RTE_TRANSITION_Communication_Read_APP_DcmDiagnosticSessionControl (255U)
# ifndef RTE_TRANSITION_DcmDiagnosticSessionControl
#  define RTE_TRANSITION_DcmDiagnosticSessionControl (255U)
# endif

# define RTE_MODE_Communication_Read_APP_DcmEcuReset_NONE (0U)
# ifndef RTE_MODE_DcmEcuReset_NONE
#  define RTE_MODE_DcmEcuReset_NONE (0U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmEcuReset_HARD (1U)
# ifndef RTE_MODE_DcmEcuReset_HARD
#  define RTE_MODE_DcmEcuReset_HARD (1U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmEcuReset_KEYONOFF (2U)
# ifndef RTE_MODE_DcmEcuReset_KEYONOFF
#  define RTE_MODE_DcmEcuReset_KEYONOFF (2U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmEcuReset_SOFT (3U)
# ifndef RTE_MODE_DcmEcuReset_SOFT
#  define RTE_MODE_DcmEcuReset_SOFT (3U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmEcuReset_JUMPTOBOOTLOADER (4U)
# ifndef RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER
#  define RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER (4U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER (5U)
# ifndef RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER
#  define RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER (5U)
# endif
# define RTE_MODE_Communication_Read_APP_DcmEcuReset_EXECUTE (6U)
# ifndef RTE_MODE_DcmEcuReset_EXECUTE
#  define RTE_MODE_DcmEcuReset_EXECUTE (6U)
# endif
# define RTE_TRANSITION_Communication_Read_APP_DcmEcuReset (7U)
# ifndef RTE_TRANSITION_DcmEcuReset
#  define RTE_TRANSITION_DcmEcuReset (7U)
# endif

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_COMMUNICATION_READ_APP_TYPE_H */
