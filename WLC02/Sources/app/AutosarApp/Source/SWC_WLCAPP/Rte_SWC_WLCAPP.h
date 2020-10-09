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
 *             File:  Rte_SWC_WLCAPP.h
 *           Config:  D:/Auto/Demo/WLCProject/WLC.dpa
 *        SW-C Type:  SWC_WLCAPP
 *  Generation Time:  2020-09-23 21:26:59
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Application header file for SW-C <SWC_WLCAPP> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SWC_WLCAPP_H
# define _RTE_SWC_WLCAPP_H

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

# include "Rte_SWC_WLCAPP_Type.h"
# include "Rte_DataHandleType.h"


/**********************************************************************************************************************
 * Component Data Structures and Port Data Structures
 *********************************************************************************************************************/

struct Rte_CDS_SWC_WLCAPP
{
  /* dummy entry */
  uint8 _dummy;
};

# define RTE_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONSTP2CONST(struct Rte_CDS_SWC_WLCAPP, RTE_CONST, RTE_CONST) Rte_Inst_SWC_WLCAPP; /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

typedef P2CONST(struct Rte_CDS_SWC_WLCAPP, TYPEDEF, RTE_CONST) Rte_Instance;


# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_A4814BDemEventParameter_003_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_A48249DemEventParameter_004_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_A48368DemEventParameter_005_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_A48468DemEventParameter_006_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_E70200DemEventParameter_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_E70568DemEventParameter_007_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_E70600DemEventParameter_008_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_E70887DemEventParameter_009_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_E70987DemEventParameter_010_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_E70A87DemEventParameter_011_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_E70B29DemEventParameter_012_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_E70C29DemEventParameter_013_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_E70D29DemEventParameter_014_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_E70E87DemEventParameter_015_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_E70F87DemEventParameter_016_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_Event_F00617DemEventParameter_002_SetEventStatus(Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_F00616Event_SetEventStatus(Dem_EventStatusType ErrorStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_PpDemOpCycle_PowerCycle_SetOperationCycleState(Dem_OperationCycleStateType CycleState); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_PpDiagnosticMonitor_DEM_EVENT_StartApplication_SetEventStatus(Dem_EventStatusType ErrorStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_PpPS_StartApplication_NvMBlock1_WriteBlock(dtRef_const_VOID SrcPtr); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_PpPS_StartApplication_NvMBlock2_WriteBlock(dtRef_const_VOID SrcPtr); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetCurrentComMode(P2VAR(ComM_ModeType, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) ComMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetMaxComMode(P2VAR(ComM_ModeType, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) ComMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetRequestedComMode(P2VAR(ComM_ModeType, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) ComMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_SWC_WLCAPP_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_RequestComMode(ComM_ModeType ComMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (C/S invocation)
 *********************************************************************************************************************/
# define Rte_Call_Event_A4814BDemEventParameter_003_SetEventStatus Rte_Call_SWC_WLCAPP_Event_A4814BDemEventParameter_003_SetEventStatus
# define Rte_Call_Event_A48249DemEventParameter_004_SetEventStatus Rte_Call_SWC_WLCAPP_Event_A48249DemEventParameter_004_SetEventStatus
# define Rte_Call_Event_A48368DemEventParameter_005_SetEventStatus Rte_Call_SWC_WLCAPP_Event_A48368DemEventParameter_005_SetEventStatus
# define Rte_Call_Event_A48468DemEventParameter_006_SetEventStatus Rte_Call_SWC_WLCAPP_Event_A48468DemEventParameter_006_SetEventStatus
# define Rte_Call_Event_E70200DemEventParameter_SetEventStatus Rte_Call_SWC_WLCAPP_Event_E70200DemEventParameter_SetEventStatus
# define Rte_Call_Event_E70568DemEventParameter_007_SetEventStatus Rte_Call_SWC_WLCAPP_Event_E70568DemEventParameter_007_SetEventStatus
# define Rte_Call_Event_E70600DemEventParameter_008_SetEventStatus Rte_Call_SWC_WLCAPP_Event_E70600DemEventParameter_008_SetEventStatus
# define Rte_Call_Event_E70887DemEventParameter_009_SetEventStatus Rte_Call_SWC_WLCAPP_Event_E70887DemEventParameter_009_SetEventStatus
# define Rte_Call_Event_E70987DemEventParameter_010_SetEventStatus Rte_Call_SWC_WLCAPP_Event_E70987DemEventParameter_010_SetEventStatus
# define Rte_Call_Event_E70A87DemEventParameter_011_SetEventStatus Rte_Call_SWC_WLCAPP_Event_E70A87DemEventParameter_011_SetEventStatus
# define Rte_Call_Event_E70B29DemEventParameter_012_SetEventStatus Rte_Call_SWC_WLCAPP_Event_E70B29DemEventParameter_012_SetEventStatus
# define Rte_Call_Event_E70C29DemEventParameter_013_SetEventStatus Rte_Call_SWC_WLCAPP_Event_E70C29DemEventParameter_013_SetEventStatus
# define Rte_Call_Event_E70D29DemEventParameter_014_SetEventStatus Rte_Call_SWC_WLCAPP_Event_E70D29DemEventParameter_014_SetEventStatus
# define Rte_Call_Event_E70E87DemEventParameter_015_SetEventStatus Rte_Call_SWC_WLCAPP_Event_E70E87DemEventParameter_015_SetEventStatus
# define Rte_Call_Event_E70F87DemEventParameter_016_SetEventStatus Rte_Call_SWC_WLCAPP_Event_E70F87DemEventParameter_016_SetEventStatus
# define Rte_Call_Event_F00617DemEventParameter_002_SetEventStatus Rte_Call_SWC_WLCAPP_Event_F00617DemEventParameter_002_SetEventStatus
# define Rte_Call_F00616Event_SetEventStatus Rte_Call_SWC_WLCAPP_F00616Event_SetEventStatus
# define Rte_Call_PpDemOpCycle_PowerCycle_SetOperationCycleState Rte_Call_SWC_WLCAPP_PpDemOpCycle_PowerCycle_SetOperationCycleState
# define Rte_Call_PpDiagnosticMonitor_DEM_EVENT_StartApplication_SetEventStatus Rte_Call_SWC_WLCAPP_PpDiagnosticMonitor_DEM_EVENT_StartApplication_SetEventStatus
# define Rte_Call_PpPS_StartApplication_NvMBlock1_WriteBlock Rte_Call_SWC_WLCAPP_PpPS_StartApplication_NvMBlock1_WriteBlock
# define Rte_Call_PpPS_StartApplication_NvMBlock2_WriteBlock Rte_Call_SWC_WLCAPP_PpPS_StartApplication_NvMBlock2_WriteBlock
# define Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetCurrentComMode Rte_Call_SWC_WLCAPP_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetCurrentComMode
# define Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetMaxComMode Rte_Call_SWC_WLCAPP_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetMaxComMode
# define Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetRequestedComMode Rte_Call_SWC_WLCAPP_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetRequestedComMode
# define Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_RequestComMode Rte_Call_SWC_WLCAPP_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_RequestComMode




# define SWC_WLCAPP_START_SEC_CODE
# include "SWC_WLCAPP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *
 * Runnable Entity Name: CBReadData_DemDataClass_LV_Battary_Voltage_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <CBReadData_DemDataClass_LV_Battary_Voltage>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType CBReadData_DemDataClass_LV_Battary_Voltage_ReadData(uint8 *Data)
 *     Argument Data: uint8* is of type DataArrayType_uint8_1
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_CSDataServices_DemDataClass_LV_Battary_Voltage_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_CBReadData_DemDataClass_LV_Battary_Voltage_ReadData CBReadData_DemDataClass_LV_Battary_Voltage_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_LV_Battary_Voltage_ReadData(P2VAR(uint8, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_LV_Battary_Voltage_ReadData(P2VAR(DataArrayType_uint8_1, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CBReadData_DemDataClass_Timestamp_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <CBReadData_DemDataClass_Timestamp>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType CBReadData_DemDataClass_Timestamp_ReadData(uint8 *Data)
 *     Argument Data: uint8* is of type DataArrayType_uint8_6
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_CSDataServices_DemDataClass_Timestamp_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_CBReadData_DemDataClass_Timestamp_ReadData CBReadData_DemDataClass_Timestamp_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_Timestamp_ReadData(P2VAR(uint8, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_Timestamp_ReadData(P2VAR(DataArrayType_uint8_6, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CBReadData_DemDataClass_Vehicle_Speed_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <CBReadData_DemDataClass_Vehicle_Speed>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType CBReadData_DemDataClass_Vehicle_Speed_ReadData(uint8 *Data)
 *     Argument Data: uint8* is of type DataArrayType_uint8_2
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_CSDataServices_DemDataClass_Vehicle_Speed_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_CBReadData_DemDataClass_Vehicle_Speed_ReadData CBReadData_DemDataClass_Vehicle_Speed_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_Vehicle_Speed_ReadData(P2VAR(uint8, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_Vehicle_Speed_ReadData(P2VAR(DataArrayType_uint8_2, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CBReadData_OccurrenceCounter_OccurenceCounter_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <CBReadData_OccurrenceCounter_OccurenceCounter>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType CBReadData_OccurrenceCounter_OccurenceCounter_ReadData(uint8 *Data)
 *     Argument Data: uint8* is of type DataArrayType_uint8_1
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_CSDataServices_OccurrenceCounter_OccurenceCounter_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_CBReadData_OccurrenceCounter_OccurenceCounter_ReadData CBReadData_OccurrenceCounter_OccurenceCounter_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_OccurrenceCounter_OccurenceCounter_ReadData(P2VAR(uint8, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_OccurrenceCounter_OccurenceCounter_ReadData(P2VAR(DataArrayType_uint8_1, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CBReadData_OdometerValue_OdometerValue_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <CBReadData_OdometerValue_OdometerValue>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType CBReadData_OdometerValue_OdometerValue_ReadData(uint8 *Data)
 *     Argument Data: uint8* is of type DataArrayType_uint8_3
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_CSDataServices_OdometerValue_OdometerValue_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_CBReadData_OdometerValue_OdometerValue_ReadData CBReadData_OdometerValue_OdometerValue_ReadData
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_OdometerValue_OdometerValue_ReadData(P2VAR(uint8, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_OdometerValue_OdometerValue_ReadData(P2VAR(DataArrayType_uint8_3, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif

/**********************************************************************************************************************
 *
 * Runnable Entity Name: ComControl_Init1_Runnable
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetCurrentComMode(ComM_ModeType *ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_NOT_OK
 *   Std_ReturnType Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetMaxComMode(ComM_ModeType *ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_NOT_OK
 *   Std_ReturnType Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetRequestedComMode(ComM_ModeType *ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_NOT_OK
 *   Std_ReturnType Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_RequestComMode(ComM_ModeType ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_MODE_LIMITATION, RTE_E_ComM_UserRequest_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_ComControl_Init1_Runnable ComControl_Init1_Runnable
FUNC(void, SWC_WLCAPP_CODE) ComControl_Init1_Runnable(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DTCProcessRunable
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_Event_A4814BDemEventParameter_003_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_A48249DemEventParameter_004_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_A48368DemEventParameter_005_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_A48468DemEventParameter_006_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_E70200DemEventParameter_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_E70568DemEventParameter_007_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_E70600DemEventParameter_008_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_E70887DemEventParameter_009_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_E70987DemEventParameter_010_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_E70A87DemEventParameter_011_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_E70B29DemEventParameter_012_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_E70C29DemEventParameter_013_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_E70D29DemEventParameter_014_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_E70E87DemEventParameter_015_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_E70F87DemEventParameter_016_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_Event_F00617DemEventParameter_002_SetEventStatus(Dem_EventStatusType EventStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DiagnosticMonitor_E_NOT_OK
 *   Std_ReturnType Rte_Call_F00616Event_SetEventStatus(Dem_EventStatusType ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_F00616Event_E_NOT_OK
 *   Std_ReturnType Rte_Call_PpDiagnosticMonitor_DEM_EVENT_StartApplication_SetEventStatus(Dem_EventStatusType ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_PiDiagnosticMonitor_DEM_EVENT_StartApplication_E_NOT_OK
 *   Std_ReturnType Rte_Call_PpPS_StartApplication_NvMBlock1_WriteBlock(dtRef_const_VOID SrcPtr)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_PiPS_StartApplication_NvMBlock1_E_NOT_OK
 *   Std_ReturnType Rte_Call_PpPS_StartApplication_NvMBlock2_WriteBlock(dtRef_const_VOID SrcPtr)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_PiPS_StartApplication_NvMBlock2_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DTCProcessRunable DTCProcessRunable
FUNC(void, SWC_WLCAPP_CODE) DTCProcessRunable(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, SWC_WLCAPP_CODE) DTCProcessRunable_Record(NIO_DTC_Type test_type);


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DemStart
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_PpDemOpCycle_PowerCycle_SetOperationCycleState(Dem_OperationCycleStateType CycleState)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_PiDemOpCycle_PowerCycle_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_DemStart DemStart
FUNC(void, SWC_WLCAPP_CODE) DemStart(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: GetCurrentComMod_Runnable
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetCurrentComMode(ComM_ModeType *ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_GetCurrentComMod_Runnable GetCurrentComMod_Runnable
FUNC(void, SWC_WLCAPP_CODE) GetCurrentComMod_Runnable(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: GetMaxComMod_Runnable
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetMaxComMode(ComM_ModeType *ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_GetMaxComMod_Runnable GetMaxComMod_Runnable
FUNC(void, SWC_WLCAPP_CODE) GetMaxComMod_Runnable(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: GetRequestedComMod_Runnable
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetRequestedComMode(ComM_ModeType *ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_GetRequestedComMod_Runnable GetRequestedComMod_Runnable
FUNC(void, SWC_WLCAPP_CODE) GetRequestedComMod_Runnable(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: NvM_RpNotifyJobEnd_StartApplication_NvMBlock1_JobFinished
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <JobFinished> of PortPrototype <PpNvM_RpNotifyJobEnd_StartApplication_NvMBlock1>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void NvM_RpNotifyJobEnd_StartApplication_NvMBlock1_JobFinished(NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_NvM_RpNotifyJobEnd_StartApplication_NvMBlock1_JobFinished NvM_RpNotifyJobEnd_StartApplication_NvMBlock1_JobFinished
FUNC(void, SWC_WLCAPP_CODE) NvM_RpNotifyJobEnd_StartApplication_NvMBlock1_JobFinished(NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: NvM_RpNotifyJobEnd_StartApplication_NvMBlock2_JobFinished
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <JobFinished> of PortPrototype <PpNvM_RpNotifyJobEnd_StartApplication_NvMBlock2>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void NvM_RpNotifyJobEnd_StartApplication_NvMBlock2_JobFinished(NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult)
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_NvM_RpNotifyJobEnd_StartApplication_NvMBlock2_JobFinished NvM_RpNotifyJobEnd_StartApplication_NvMBlock2_JobFinished
FUNC(void, SWC_WLCAPP_CODE) NvM_RpNotifyJobEnd_StartApplication_NvMBlock2_JobFinished(NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RequestComModeFull_Runnable
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_RequestComMode(ComM_ModeType ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_MODE_LIMITATION, RTE_E_ComM_UserRequest_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_RequestComModeFull_Runnable RequestComModeFull_Runnable
FUNC(void, SWC_WLCAPP_CODE) RequestComModeFull_Runnable(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RequestComModeNOFull_Runnable
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_RequestComMode(ComM_ModeType ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_MODE_LIMITATION, RTE_E_ComM_UserRequest_E_NOT_OK
 *
 *********************************************************************************************************************/

# define RTE_RUNNABLE_RequestComModeNOFull_Runnable RequestComModeNOFull_Runnable
FUNC(void, SWC_WLCAPP_CODE) RequestComModeNOFull_Runnable(void); /* PRQA S 0850 */ /* MD_MSR_19.8 */

# define SWC_WLCAPP_STOP_SEC_CODE
# include "SWC_WLCAPP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

# define RTE_E_CSDataServices_DemDataClass_LV_Battary_Voltage_E_NOT_OK (1U)

# define RTE_E_CSDataServices_DemDataClass_Timestamp_E_NOT_OK (1U)

# define RTE_E_CSDataServices_DemDataClass_Vehicle_Speed_E_NOT_OK (1U)

# define RTE_E_CSDataServices_OccurrenceCounter_OccurenceCounter_E_NOT_OK (1U)

# define RTE_E_CSDataServices_OdometerValue_OdometerValue_E_NOT_OK (1U)

# define RTE_E_ComM_UserRequest_E_MODE_LIMITATION (2U)

# define RTE_E_ComM_UserRequest_E_NOT_OK (1U)

# define RTE_E_DiagnosticMonitor_E_NOT_OK (1U)

# define RTE_E_F00616Event_E_NOT_OK (1U)

# define RTE_E_PiDemOpCycle_PowerCycle_E_NOT_OK (1U)

# define RTE_E_PiDiagnosticMonitor_DEM_EVENT_StartApplication_E_NOT_OK (1U)

# define RTE_E_PiPS_StartApplication_NvMBlock1_E_NOT_OK (1U)

# define RTE_E_PiPS_StartApplication_NvMBlock2_E_NOT_OK (1U)

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_SWC_WLCAPP_H */
