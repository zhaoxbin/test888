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
 *             File:  Rte_Dcm.h
 *           Config:  WLC.dpa
 *      ECU-Project:  WLC
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Application header file for SW-C <Dcm>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_DCM_H
# define _RTE_DCM_H

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

# include "Rte_Dcm_Type.h"
# include "Rte_DataHandleType.h"


# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f(Dcm_CommunicationModeType nextMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_DcmControlDtcSetting_DcmControlDtcSetting(Dcm_ControlDtcSettingType nextMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_DcmDiagnosticSessionControl_DcmDiagnosticSessionControl(Dcm_DiagnosticSessionControlType nextMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_DcmEcuReset_DcmEcuReset(Dcm_EcuResetType nextMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_SwitchAck_Dcm_DcmEcuReset_DcmEcuReset(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_CheckNFCAntenna_RequestResults(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_DCM_APPL_VAR) DcmDspRoutineRequestResOutSignal, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_DCM_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
# else
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_CheckNFCAntenna_RequestResults(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data7ByteType, AUTOMATIC, RTE_DCM_APPL_VAR) DcmDspRoutineRequestResOutSignal, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_DCM_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
# endif
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_CheckNFCAntenna_Start(uint8 DcmDspStartRoutineInSignal, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_DCM_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Dcm_RoutineServices_CheckProgrammingPreCondition_Start(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_DCM_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Switch_<p>_<m>
 *********************************************************************************************************************/
#  define Rte_Switch_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f Rte_Switch_Dcm_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_DcmCommunicationControl_ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f
#  define Rte_Switch_DcmControlDtcSetting_DcmControlDtcSetting Rte_Switch_Dcm_DcmControlDtcSetting_DcmControlDtcSetting
#  define Rte_Switch_DcmDiagnosticSessionControl_DcmDiagnosticSessionControl Rte_Switch_Dcm_DcmDiagnosticSessionControl_DcmDiagnosticSessionControl
#  define Rte_Switch_DcmEcuReset_DcmEcuReset Rte_Switch_Dcm_DcmEcuReset_DcmEcuReset


/**********************************************************************************************************************
 * Rte_Feedback_<p>_<m> (mode switch acknowledge)
 *********************************************************************************************************************/
#  define Rte_SwitchAck_DcmEcuReset_DcmEcuReset Rte_SwitchAck_Dcm_DcmEcuReset_DcmEcuReset


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead DataServices_DcmDspData_BootloaderVersion_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_BootloaderVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_BootloaderVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_BootloaderVersion_ReadData DataServices_DcmDspData_BootloaderVersion_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_BootloaderVersion_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_BootloaderVersion_ReadDataLength DataServices_DcmDspData_BootloaderVersion_ReadDataLength
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead DataServices_DcmDspData_ConfigurarionFingerprint_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ConfigurarionFingerprint_ReadData DataServices_DcmDspData_ConfigurarionFingerprint_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ConfigurarionFingerprint_WriteData(P2CONST(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ConfigurarionFingerprint_WriteData DataServices_DcmDspData_ConfigurarionFingerprint_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead DataServices_DcmDspData_ECUConfigurarion_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUConfigurarion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUConfigurarion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data25ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ECUConfigurarion_ReadData DataServices_DcmDspData_ECUConfigurarion_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUConfigurarion_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUConfigurarion_WriteData(P2CONST(Dcm_Data25ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ECUConfigurarion_WriteData DataServices_DcmDspData_ECUConfigurarion_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead DataServices_DcmDspData_ECUDiagDatabaseVersion_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData DataServices_DcmDspData_ECUDiagDatabaseVersion_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead DataServices_DcmDspData_ECUManufacturingDate_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUManufacturingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUManufacturingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ECUManufacturingDate_ReadData DataServices_DcmDspData_ECUManufacturingDate_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead DataServices_DcmDspData_ECUProgrammingDate_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUProgrammingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUProgrammingDate_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data3ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ECUProgrammingDate_ReadData DataServices_DcmDspData_ECUProgrammingDate_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead DataServices_DcmDspData_ECUSerialNumber_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUSerialNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ECUSerialNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data10ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ECUSerialNumber_ReadData DataServices_DcmDspData_ECUSerialNumber_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_NFCFunction_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_NFCFunction_ConditionCheckRead DataServices_DcmDspData_NFCFunction_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_NFCFunction_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_NFCFunction_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_NFCFunction_ReadData DataServices_DcmDspData_NFCFunction_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_NFCFunction_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_NFCFunction_ReadDataLength DataServices_DcmDspData_NFCFunction_ReadDataLength
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_NFCFunction_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_NFCFunction_WriteData(P2CONST(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_NFCFunction_WriteData DataServices_DcmDspData_NFCFunction_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead DataServices_DcmDspData_ReadActiveDiagSession_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ReadActiveDiagSession_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ReadActiveDiagSession_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data1ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ReadActiveDiagSession_ReadData DataServices_DcmDspData_ReadActiveDiagSession_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead DataServices_DcmDspData_ReadFingerprint_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ReadFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_ReadFingerprint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_ReadFingerprint_ReadData DataServices_DcmDspData_ReadFingerprint_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead DataServices_DcmDspData_RepairShopFingerPrint_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_RepairShopFingerPrint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_RepairShopFingerPrint_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_RepairShopFingerPrint_ReadData DataServices_DcmDspData_RepairShopFingerPrint_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_RepairShopFingerPrint_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_RepairShopFingerPrint_WriteData(P2CONST(Dcm_Data12ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_RepairShopFingerPrint_WriteData DataServices_DcmDspData_RepairShopFingerPrint_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemName_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemName_ConditionCheckRead DataServices_DcmDspData_SystemName_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemName_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemName_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data8ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemName_ReadData DataServices_DcmDspData_SystemName_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemName_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemName_ReadDataLength DataServices_DcmDspData_SystemName_ReadDataLength
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead DataServices_DcmDspData_SystemSESVNumber_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSESVNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSESVNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSESVNumber_ReadData DataServices_DcmDspData_SystemSESVNumber_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSESVNumber_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSESVNumber_ReadDataLength DataServices_DcmDspData_SystemSESVNumber_ReadDataLength
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_ReadDataLength
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData(P2CONST(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData DataServices_DcmDspData_SystemSFBLIntegrationVersionNumber_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSHV_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSHV_ConditionCheckRead DataServices_DcmDspData_SystemSHV_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSHV_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSHV_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data6ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSHV_ReadData DataServices_DcmDspData_SystemSHV_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSHV_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSHV_ReadDataLength DataServices_DcmDspData_SystemSHV_ReadDataLength
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead DataServices_DcmDspData_SystemSupplierIdData_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSupplierIdData_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_SystemSupplierIdData_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data8ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_SystemSupplierIdData_ReadData DataServices_DcmDspData_SystemSupplierIdData_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VIN_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VIN_ConditionCheckRead DataServices_DcmDspData_VIN_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VIN_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VIN_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data17ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VIN_ReadData DataServices_DcmDspData_VIN_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VIN_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VIN_WriteData(P2CONST(Dcm_Data17ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VIN_WriteData DataServices_DcmDspData_VIN_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead DataServices_DcmDspData_VM_CalibrarionPartNumber_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData DataServices_DcmDspData_VM_CalibrarionPartNumber_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData(P2CONST(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData DataServices_DcmDspData_VM_CalibrarionPartNumber_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead DataServices_DcmDspData_VM_CalibrationBaseline_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_CalibrationBaseline_ReadData DataServices_DcmDspData_VM_CalibrationBaseline_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_CalibrationBaseline_WriteData(P2CONST(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_CalibrationBaseline_WriteData DataServices_DcmDspData_VM_CalibrationBaseline_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead DataServices_DcmDspData_VM_FOTASpecialPartNumber_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData DataServices_DcmDspData_VM_FOTASpecialPartNumber_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData(P2CONST(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData DataServices_DcmDspData_VM_FOTASpecialPartNumber_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead DataServices_DcmDspData_VM_SoftwarBaseline_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_SoftwarBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_SoftwarBaseline_ReadData DataServices_DcmDspData_VM_SoftwarBaseline_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead DataServices_DcmDspData_VM_SofwarePartNumber_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_SofwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_SofwarePartNumber_ReadData DataServices_DcmDspData_VM_SofwarePartNumber_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead DataServices_DcmDspData_VM_SparepartNumber_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_SparepartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_SparepartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_SparepartNumber_ReadData DataServices_DcmDspData_VM_SparepartNumber_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_SparepartNumber_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_SparepartNumber_WriteData(P2CONST(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_SparepartNumber_WriteData DataServices_DcmDspData_VM_SparepartNumber_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead DataServices_DcmDspData_VM_Specialdatabaseline_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_Specialdatabaseline_ReadData DataServices_DcmDspData_VM_Specialdatabaseline_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength DataServices_DcmDspData_VM_Specialdatabaseline_ReadDataLength
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead DataServices_DcmDspData_WLCCtrlSts_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_WLCCtrlSts_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_WLCCtrlSts_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data1ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_WLCCtrlSts_ReadData DataServices_DcmDspData_WLCCtrlSts_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_WLCCtrlSts_ReadDataLength(Dcm_OpStatusType OpStatus, P2VAR(uint16, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) DataLength); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_WLCCtrlSts_ReadDataLength DataServices_DcmDspData_WLCCtrlSts_ReadDataLength
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_WLCCtrlSts_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_DcmDspData_WLCCtrlSts_WriteData(P2CONST(Dcm_Data1ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, uint16 DataLength, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_DcmDspData_WLCCtrlSts_WriteData DataServices_DcmDspData_WLCCtrlSts_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData DataServices_Diag_RWDI_LightOnOffCounter_LightOnOffCounter_Value_WriteData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead DataServices_Diag_VM_HardwareBaseline_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_Diag_VM_HardwareBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_Diag_VM_HardwareBaseline_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data2ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_Diag_VM_HardwareBaseline_ReadData DataServices_Diag_VM_HardwareBaseline_ReadData
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead DataServices_Diag_VM_HardwarePartNumber_ConditionCheckRead
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_Diag_VM_HardwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) DataServices_Diag_VM_HardwarePartNumber_ReadData(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data11ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Data); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_DataServices_Diag_VM_HardwarePartNumber_ReadData DataServices_Diag_VM_HardwarePartNumber_ReadData
#  define Rte_Call_RoutineServices_CheckNFCAntenna_RequestResults Rte_Call_Dcm_RoutineServices_CheckNFCAntenna_RequestResults
#  define Rte_Call_RoutineServices_CheckNFCAntenna_Start Rte_Call_Dcm_RoutineServices_CheckNFCAntenna_Start
#  define Rte_Call_RoutineServices_CheckProgrammingPreCondition_Start Rte_Call_Dcm_RoutineServices_CheckProgrammingPreCondition_Start
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_01_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_01_CompareKey(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_SecurityAccess_Level_01_CompareKey SecurityAccess_Level_01_CompareKey
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_01_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_01_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_SecurityAccess_Level_01_GetSeed SecurityAccess_Level_01_GetSeed
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_02_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_02_CompareKey(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_SecurityAccess_Level_02_CompareKey SecurityAccess_Level_02_CompareKey
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_02_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_02_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_SecurityAccess_Level_02_GetSeed SecurityAccess_Level_02_GetSeed
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_04_CompareKey(P2CONST(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_04_CompareKey(P2CONST(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_DATA) Key, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_SecurityAccess_Level_04_CompareKey SecurityAccess_Level_04_CompareKey
#  define RTE_START_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_04_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  else
FUNC(Std_ReturnType, RTE_COMMUNICATION_READ_APP_APPL_CODE) SecurityAccess_Level_04_GetSeed(Dcm_OpStatusType OpStatus, P2VAR(Dcm_Data4ByteType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_COMMUNICATION_READ_APP_APPL_VAR) ErrorCode); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
#  endif
#  define RTE_STOP_SEC_COMMUNICATION_READ_APP_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_SecurityAccess_Level_04_GetSeed SecurityAccess_Level_04_GetSeed


# endif /* !defined(RTE_CORE) */


# define Dcm_START_SEC_CODE
# include "Dcm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_Dcm_MainFunction Dcm_MainFunction
#  define RTE_RUNNABLE_GetActiveProtocol Dcm_GetActiveProtocol
#  define RTE_RUNNABLE_GetRequestKind Dcm_GetRequestKind
#  define RTE_RUNNABLE_GetSecurityLevel Dcm_GetSecurityLevel
#  define RTE_RUNNABLE_GetSesCtrlType Dcm_GetSesCtrlType
#  define RTE_RUNNABLE_ResetToDefaultSession Dcm_ResetToDefaultSession
#  define RTE_RUNNABLE_SetActiveDiagnostic Dcm_SetActiveDiagnostic
# endif

FUNC(void, Dcm_CODE) Dcm_MainFunction(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetActiveProtocol(P2VAR(Dcm_ProtocolType, AUTOMATIC, RTE_DCM_APPL_VAR) ActiveProtocol); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetRequestKind(uint16 TesterSourceAddress, P2VAR(Dcm_RequestKindType, AUTOMATIC, RTE_DCM_APPL_VAR) RequestKind); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSecurityLevel(P2VAR(Dcm_SecLevelType, AUTOMATIC, RTE_DCM_APPL_VAR) SecLevel); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSesCtrlType(P2VAR(Dcm_SesCtrlType, AUTOMATIC, RTE_DCM_APPL_VAR) SesCtrlType); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(Std_ReturnType, Dcm_CODE) Dcm_ResetToDefaultSession(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(Std_ReturnType, Dcm_CODE) Dcm_SetActiveDiagnostic(boolean active); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */

# define Dcm_STOP_SEC_CODE
# include "Dcm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_DCMServices_E_NOT_OK (1U)

#  define RTE_E_DCMServices_E_OK (0U)

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

#  define RTE_E_RoutineServices_CheckNFCAntenna_DCM_E_FORCE_RCRRP (12U)

#  define RTE_E_RoutineServices_CheckNFCAntenna_DCM_E_PENDING (10U)

#  define RTE_E_RoutineServices_CheckNFCAntenna_E_NOT_OK (1U)

#  define RTE_E_RoutineServices_CheckProgrammingPreCondition_DCM_E_FORCE_RCRRP (12U)

#  define RTE_E_RoutineServices_CheckProgrammingPreCondition_DCM_E_PENDING (10U)

#  define RTE_E_RoutineServices_CheckProgrammingPreCondition_E_NOT_OK (1U)

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

#endif /* _RTE_DCM_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3451:  MISRA rule: 8.8
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
