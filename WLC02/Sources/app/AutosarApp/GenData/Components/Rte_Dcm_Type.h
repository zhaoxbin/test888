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
 *             File:  Rte_Dcm_Type.h
 *           Config:  WLC.dpa
 *      ECU-Project:  WLC
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Application types header file for SW-C <Dcm>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_DCM_TYPE_H
# define _RTE_DCM_TYPE_H

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

# include "Rte_Type.h"

# ifndef RTE_CORE

/**********************************************************************************************************************
 * Range, Invalidation, Enumeration and Bit Field Definitions
 *********************************************************************************************************************/

#  ifndef DCM_ENABLE_RX_TX_NORM
#   define DCM_ENABLE_RX_TX_NORM (0U)
#  endif

#  ifndef DCM_ENABLE_RX_DISABLE_TX_NORM
#   define DCM_ENABLE_RX_DISABLE_TX_NORM (1U)
#  endif

#  ifndef DCM_DISABLE_RX_ENABLE_TX_NORM
#   define DCM_DISABLE_RX_ENABLE_TX_NORM (2U)
#  endif

#  ifndef DCM_DISABLE_RX_TX_NORMAL
#   define DCM_DISABLE_RX_TX_NORMAL (3U)
#  endif

#  ifndef DCM_ENABLE_RX_TX_NM
#   define DCM_ENABLE_RX_TX_NM (4U)
#  endif

#  ifndef DCM_ENABLE_RX_DISABLE_TX_NM
#   define DCM_ENABLE_RX_DISABLE_TX_NM (5U)
#  endif

#  ifndef DCM_DISABLE_RX_ENABLE_TX_NM
#   define DCM_DISABLE_RX_ENABLE_TX_NM (6U)
#  endif

#  ifndef DCM_DISABLE_RX_TX_NM
#   define DCM_DISABLE_RX_TX_NM (7U)
#  endif

#  ifndef DCM_ENABLE_RX_TX_NORM_NM
#   define DCM_ENABLE_RX_TX_NORM_NM (8U)
#  endif

#  ifndef DCM_ENABLE_RX_DISABLE_TX_NORM_NM
#   define DCM_ENABLE_RX_DISABLE_TX_NORM_NM (9U)
#  endif

#  ifndef DCM_DISABLE_RX_ENABLE_TX_NORM_NM
#   define DCM_DISABLE_RX_ENABLE_TX_NORM_NM (10U)
#  endif

#  ifndef DCM_DISABLE_RX_TX_NORM_NM
#   define DCM_DISABLE_RX_TX_NORM_NM (11U)
#  endif

#  ifndef DCM_RES_POS_OK
#   define DCM_RES_POS_OK (0U)
#  endif

#  ifndef DCM_RES_POS_NOT_OK
#   define DCM_RES_POS_NOT_OK (1U)
#  endif

#  ifndef DCM_RES_NEG_OK
#   define DCM_RES_NEG_OK (2U)
#  endif

#  ifndef DCM_RES_NEG_NOT_OK
#   define DCM_RES_NEG_NOT_OK (3U)
#  endif

#  ifndef DCM_ENUM_ENABLEDTCSETTING
#   define DCM_ENUM_ENABLEDTCSETTING (0U)
#  endif

#  ifndef DCM_ENUM_DISABLEDTCSETTING
#   define DCM_ENUM_DISABLEDTCSETTING (1U)
#  endif

#  ifndef DCM_ENUM_DEFAULT_SESSION
#   define DCM_ENUM_DEFAULT_SESSION (1U)
#  endif

#  ifndef DCM_ENUM_PROGRAMMING_SESSION
#   define DCM_ENUM_PROGRAMMING_SESSION (2U)
#  endif

#  ifndef DCM_ENUM_EXTENDED_SESSION
#   define DCM_ENUM_EXTENDED_SESSION (3U)
#  endif

#  ifndef DCM_ENUM_NONE
#   define DCM_ENUM_NONE (0U)
#  endif

#  ifndef DCM_ENUM_HARD
#   define DCM_ENUM_HARD (1U)
#  endif

#  ifndef DCM_ENUM_KEYONOFF
#   define DCM_ENUM_KEYONOFF (2U)
#  endif

#  ifndef DCM_ENUM_SOFT
#   define DCM_ENUM_SOFT (3U)
#  endif

#  ifndef DCM_ENUM_JUMPTOBOOTLOADER
#   define DCM_ENUM_JUMPTOBOOTLOADER (4U)
#  endif

#  ifndef DCM_ENUM_JUMPTOSYSSUPPLIERBOOTLOADER
#   define DCM_ENUM_JUMPTOSYSSUPPLIERBOOTLOADER (5U)
#  endif

#  ifndef DCM_ENUM_EXECUTE
#   define DCM_ENUM_EXECUTE (6U)
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

#  ifndef DCM_OBD_ON_CAN
#   define DCM_OBD_ON_CAN (0U)
#  endif

#  ifndef DCM_OBD_ON_FLEXRAY
#   define DCM_OBD_ON_FLEXRAY (1U)
#  endif

#  ifndef DCM_OBD_ON_IP
#   define DCM_OBD_ON_IP (2U)
#  endif

#  ifndef DCM_UDS_ON_CAN
#   define DCM_UDS_ON_CAN (3U)
#  endif

#  ifndef DCM_UDS_ON_FLEXRAY
#   define DCM_UDS_ON_FLEXRAY (4U)
#  endif

#  ifndef DCM_UDS_ON_IP
#   define DCM_UDS_ON_IP (5U)
#  endif

#  ifndef DCM_NO_ACTIVE_PROTOCOL
#   define DCM_NO_ACTIVE_PROTOCOL (12U)
#  endif

#  ifndef DCM_SUPPLIER_1
#   define DCM_SUPPLIER_1 (240U)
#  endif

#  ifndef DCM_SUPPLIER_2
#   define DCM_SUPPLIER_2 (241U)
#  endif

#  ifndef DCM_SUPPLIER_3
#   define DCM_SUPPLIER_3 (242U)
#  endif

#  ifndef DCM_SUPPLIER_4
#   define DCM_SUPPLIER_4 (243U)
#  endif

#  ifndef DCM_SUPPLIER_5
#   define DCM_SUPPLIER_5 (244U)
#  endif

#  ifndef DCM_SUPPLIER_6
#   define DCM_SUPPLIER_6 (245U)
#  endif

#  ifndef DCM_SUPPLIER_7
#   define DCM_SUPPLIER_7 (246U)
#  endif

#  ifndef DCM_SUPPLIER_8
#   define DCM_SUPPLIER_8 (247U)
#  endif

#  ifndef DCM_SUPPLIER_9
#   define DCM_SUPPLIER_9 (248U)
#  endif

#  ifndef DCM_SUPPLIER_10
#   define DCM_SUPPLIER_10 (249U)
#  endif

#  ifndef DCM_SUPPLIER_11
#   define DCM_SUPPLIER_11 (250U)
#  endif

#  ifndef DCM_SUPPLIER_12
#   define DCM_SUPPLIER_12 (251U)
#  endif

#  ifndef DCM_SUPPLIER_13
#   define DCM_SUPPLIER_13 (252U)
#  endif

#  ifndef DCM_SUPPLIER_14
#   define DCM_SUPPLIER_14 (253U)
#  endif

#  ifndef DCM_SUPPLIER_15
#   define DCM_SUPPLIER_15 (254U)
#  endif

#  ifndef DCM_REQ_KIND_NONE
#   define DCM_REQ_KIND_NONE (0U)
#  endif

#  ifndef DCM_REQ_KIND_EXTERNAL
#   define DCM_REQ_KIND_EXTERNAL (1U)
#  endif

#  ifndef DCM_REQ_KIND_ROE
#   define DCM_REQ_KIND_ROE (2U)
#  endif

#  ifndef DCM_SEC_LEV_LOCKED
#   define DCM_SEC_LEV_LOCKED (0U)
#  endif

#  ifndef DCM_SEC_LEV_L1
#   define DCM_SEC_LEV_L1 (1U)
#  endif

#  ifndef DCM_SEC_LEV_L2
#   define DCM_SEC_LEV_L2 (2U)
#  endif

#  ifndef DCM_SEC_LEV_L4
#   define DCM_SEC_LEV_L4 (4U)
#  endif

#  ifndef DCM_DEFAULT_SESSION
#   define DCM_DEFAULT_SESSION (1U)
#  endif

#  ifndef DCM_PROGRAMMING_SESSION
#   define DCM_PROGRAMMING_SESSION (2U)
#  endif

#  ifndef DCM_EXTENDED_DIAGNOSTIC_SESSION
#   define DCM_EXTENDED_DIAGNOSTIC_SESSION (3U)
#  endif

# endif /* RTE_CORE */


/**********************************************************************************************************************
 * Definitions for Mode Management
 *********************************************************************************************************************/
# ifndef RTE_MODETYPE_DcmCommunicationControl
#  define RTE_MODETYPE_DcmCommunicationControl
typedef Dcm_CommunicationModeType Rte_ModeType_DcmCommunicationControl;
# endif
# ifndef RTE_MODETYPE_DcmControlDtcSetting
#  define RTE_MODETYPE_DcmControlDtcSetting
typedef Dcm_ControlDtcSettingType Rte_ModeType_DcmControlDtcSetting;
# endif
# ifndef RTE_MODETYPE_DcmDiagnosticSessionControl
#  define RTE_MODETYPE_DcmDiagnosticSessionControl
typedef Dcm_DiagnosticSessionControlType Rte_ModeType_DcmDiagnosticSessionControl;
# endif
# ifndef RTE_MODETYPE_DcmEcuReset
#  define RTE_MODETYPE_DcmEcuReset
typedef Dcm_EcuResetType Rte_ModeType_DcmEcuReset;
# endif

# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM (0U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM (0U)
# endif
# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM (1U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM (1U)
# endif
# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM (2U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM (2U)
# endif
# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORMAL (3U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORMAL
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORMAL (3U)
# endif
# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM (4U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM (4U)
# endif
# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM (5U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM (5U)
# endif
# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM (6U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM (6U)
# endif
# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM (7U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM (7U)
# endif
# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM (8U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM (8U)
# endif
# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM (9U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM (9U)
# endif
# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM (10U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM (10U)
# endif
# define RTE_MODE_Dcm_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM (11U)
# ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM
#  define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM (11U)
# endif
# define RTE_TRANSITION_Dcm_DcmCommunicationControl (12U)
# ifndef RTE_TRANSITION_DcmCommunicationControl
#  define RTE_TRANSITION_DcmCommunicationControl (12U)
# endif

# define RTE_MODE_Dcm_DcmControlDtcSetting_ENABLEDTCSETTING (0U)
# ifndef RTE_MODE_DcmControlDtcSetting_ENABLEDTCSETTING
#  define RTE_MODE_DcmControlDtcSetting_ENABLEDTCSETTING (0U)
# endif
# define RTE_MODE_Dcm_DcmControlDtcSetting_DISABLEDTCSETTING (1U)
# ifndef RTE_MODE_DcmControlDtcSetting_DISABLEDTCSETTING
#  define RTE_MODE_DcmControlDtcSetting_DISABLEDTCSETTING (1U)
# endif
# define RTE_TRANSITION_Dcm_DcmControlDtcSetting (2U)
# ifndef RTE_TRANSITION_DcmControlDtcSetting
#  define RTE_TRANSITION_DcmControlDtcSetting (2U)
# endif

# define RTE_MODE_Dcm_DcmDiagnosticSessionControl_DEFAULT_SESSION (1U)
# ifndef RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION
#  define RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION (1U)
# endif
# define RTE_MODE_Dcm_DcmDiagnosticSessionControl_PROGRAMMING_SESSION (2U)
# ifndef RTE_MODE_DcmDiagnosticSessionControl_PROGRAMMING_SESSION
#  define RTE_MODE_DcmDiagnosticSessionControl_PROGRAMMING_SESSION (2U)
# endif
# define RTE_MODE_Dcm_DcmDiagnosticSessionControl_EXTENDED_SESSION (3U)
# ifndef RTE_MODE_DcmDiagnosticSessionControl_EXTENDED_SESSION
#  define RTE_MODE_DcmDiagnosticSessionControl_EXTENDED_SESSION (3U)
# endif
# define RTE_TRANSITION_Dcm_DcmDiagnosticSessionControl (255U)
# ifndef RTE_TRANSITION_DcmDiagnosticSessionControl
#  define RTE_TRANSITION_DcmDiagnosticSessionControl (255U)
# endif

# define RTE_MODE_Dcm_DcmEcuReset_NONE (0U)
# ifndef RTE_MODE_DcmEcuReset_NONE
#  define RTE_MODE_DcmEcuReset_NONE (0U)
# endif
# define RTE_MODE_Dcm_DcmEcuReset_HARD (1U)
# ifndef RTE_MODE_DcmEcuReset_HARD
#  define RTE_MODE_DcmEcuReset_HARD (1U)
# endif
# define RTE_MODE_Dcm_DcmEcuReset_KEYONOFF (2U)
# ifndef RTE_MODE_DcmEcuReset_KEYONOFF
#  define RTE_MODE_DcmEcuReset_KEYONOFF (2U)
# endif
# define RTE_MODE_Dcm_DcmEcuReset_SOFT (3U)
# ifndef RTE_MODE_DcmEcuReset_SOFT
#  define RTE_MODE_DcmEcuReset_SOFT (3U)
# endif
# define RTE_MODE_Dcm_DcmEcuReset_JUMPTOBOOTLOADER (4U)
# ifndef RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER
#  define RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER (4U)
# endif
# define RTE_MODE_Dcm_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER (5U)
# ifndef RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER
#  define RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER (5U)
# endif
# define RTE_MODE_Dcm_DcmEcuReset_EXECUTE (6U)
# ifndef RTE_MODE_DcmEcuReset_EXECUTE
#  define RTE_MODE_DcmEcuReset_EXECUTE (6U)
# endif
# define RTE_TRANSITION_Dcm_DcmEcuReset (7U)
# ifndef RTE_TRANSITION_DcmEcuReset
#  define RTE_TRANSITION_DcmEcuReset (7U)
# endif

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_DCM_TYPE_H */
