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
 *           Config:  WLC.dpa
 *      ECU-Project:  WLC
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Application header file for SW-C <SWC_WLCAPP>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SWC_WLCAPP_H
# define _RTE_SWC_WLCAPP_H

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

# include "Rte_SWC_WLCAPP_Type.h"
# include "Rte_DataHandleType.h"


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_DEMSATELLITE_0_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_DEMSATELLITE_0_APPL_CODE) Dem_SetEventStatus(Dem_EventIdType parg0, Dem_EventStatusType EventStatus); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_DEMSATELLITE_0_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_Event_A4814BDemEventParameter_003_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)4, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_A48249DemEventParameter_004_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)5, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_A48368DemEventParameter_005_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)6, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_A48468DemEventParameter_006_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)7, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_E70200DemEventParameter_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)1, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_E70568DemEventParameter_007_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)8, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_E70600DemEventParameter_008_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)9, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_E70887DemEventParameter_009_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)10, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_E70987DemEventParameter_010_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)11, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_E70A87DemEventParameter_011_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)12, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_E70B29DemEventParameter_012_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)13, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_E70C29DemEventParameter_013_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)14, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_E70D29DemEventParameter_014_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)15, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_E70E87DemEventParameter_015_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)16, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_E70F87DemEventParameter_016_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)17, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_Event_F00617DemEventParameter_002_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)3, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_F00616Event_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)2, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_DEMMASTER_0_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_DEMMASTER_0_APPL_CODE) Dem_SetOperationCycleState(Dem_OperationCycleIdType parg0, Dem_OperationCycleStateType CycleState); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_DEMMASTER_0_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PpDemOpCycle_PowerCycle_SetOperationCycleState(arg1) (Dem_SetOperationCycleState((Dem_OperationCycleIdType)2, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_PpDiagnosticMonitor_DEM_EVENT_StartApplication_SetEventStatus(arg1) (Dem_SetEventStatus((Dem_EventIdType)21, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_NVM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_NVM_APPL_CODE) NvM_WriteBlock(NvM_BlockIdType parg0, dtRef_const_VOID SrcPtr); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_NVM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_PpPS_StartApplication_NvMBlock1_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)5, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Rte_Call_PpPS_StartApplication_NvMBlock2_WriteBlock(arg1) (NvM_WriteBlock((NvM_BlockIdType)6, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_GetCurrentComMode(ComM_UserHandleType parg0, P2VAR(ComM_ModeType, AUTOMATIC, RTE_COMM_APPL_VAR) ComMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetCurrentComMode(arg1) (ComM_GetCurrentComMode((ComM_UserHandleType)0, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_GetMaxComMode(ComM_UserHandleType parg0, P2VAR(ComM_ModeType, AUTOMATIC, RTE_COMM_APPL_VAR) ComMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetMaxComMode(arg1) (ComM_GetMaxComMode((ComM_UserHandleType)0, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_GetRequestedComMode(ComM_UserHandleType parg0, P2VAR(ComM_ModeType, AUTOMATIC, RTE_COMM_APPL_VAR) ComMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_GetRequestedComMode(arg1) (ComM_GetRequestedComMode((ComM_UserHandleType)0, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define RTE_START_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
FUNC(Std_ReturnType, RTE_COMM_APPL_CODE) ComM_RequestComMode(ComM_UserHandleType parg0, ComM_ModeType ComMode); /* PRQA S 0850 */ /* MD_MSR_19.8 */
#  define RTE_STOP_SEC_COMM_APPL_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  define Rte_Call_UR_CN_NIO_ES6_RF_CAN_SR_V3_0_e01a4c57_RequestComMode(arg1) (ComM_RequestComMode((ComM_UserHandleType)0, arg1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */


# endif /* !defined(RTE_CORE) */


# define SWC_WLCAPP_START_SEC_CODE
# include "SWC_WLCAPP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

# ifndef RTE_CORE
#  define RTE_RUNNABLE_CBReadData_DemDataClass_LV_Battary_Voltage_ReadData CBReadData_DemDataClass_LV_Battary_Voltage_ReadData
#  define RTE_RUNNABLE_CBReadData_DemDataClass_Timestamp_ReadData CBReadData_DemDataClass_Timestamp_ReadData
#  define RTE_RUNNABLE_CBReadData_DemDataClass_Vehicle_Speed_ReadData CBReadData_DemDataClass_Vehicle_Speed_ReadData
#  define RTE_RUNNABLE_CBReadData_OccurrenceCounter_OccurenceCounter_ReadData CBReadData_OccurrenceCounter_OccurenceCounter_ReadData
#  define RTE_RUNNABLE_CBReadData_OdometerValue_OdometerValue_ReadData CBReadData_OdometerValue_OdometerValue_ReadData
#  define RTE_RUNNABLE_ComControl_Init1_Runnable ComControl_Init1_Runnable
#  define RTE_RUNNABLE_DTCProcessRunable DTCProcessRunable
#  define RTE_RUNNABLE_DemStart DemStart
#  define RTE_RUNNABLE_GetCurrentComMod_Runnable GetCurrentComMod_Runnable
#  define RTE_RUNNABLE_GetMaxComMod_Runnable GetMaxComMod_Runnable
#  define RTE_RUNNABLE_GetRequestedComMod_Runnable GetRequestedComMod_Runnable
#  define RTE_RUNNABLE_NvM_RpNotifyJobEnd_StartApplication_NvMBlock1_JobFinished NvM_RpNotifyJobEnd_StartApplication_NvMBlock1_JobFinished
#  define RTE_RUNNABLE_NvM_RpNotifyJobEnd_StartApplication_NvMBlock2_JobFinished NvM_RpNotifyJobEnd_StartApplication_NvMBlock2_JobFinished
#  define RTE_RUNNABLE_RequestComModeFull_Runnable RequestComModeFull_Runnable
#  define RTE_RUNNABLE_RequestComModeNOFull_Runnable RequestComModeNOFull_Runnable
# endif

# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_LV_Battary_Voltage_ReadData(P2VAR(uint8, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_LV_Battary_Voltage_ReadData(P2VAR(DataArrayType_uint8_1, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_Timestamp_ReadData(P2VAR(uint8, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_Timestamp_ReadData(P2VAR(DataArrayType_uint8_6, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_Vehicle_Speed_ReadData(P2VAR(uint8, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_DemDataClass_Vehicle_Speed_ReadData(P2VAR(DataArrayType_uint8_2, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_OccurrenceCounter_OccurenceCounter_ReadData(P2VAR(uint8, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_OccurrenceCounter_OccurenceCounter_ReadData(P2VAR(DataArrayType_uint8_1, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_OdometerValue_OdometerValue_ReadData(P2VAR(uint8, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# else
FUNC(Std_ReturnType, SWC_WLCAPP_CODE) CBReadData_OdometerValue_OdometerValue_ReadData(P2VAR(DataArrayType_uint8_3, AUTOMATIC, RTE_SWC_WLCAPP_APPL_VAR) Data); /* PRQA S 0850 */ /* MD_MSR_19.8 */
# endif
FUNC(void, SWC_WLCAPP_CODE) ComControl_Init1_Runnable(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, SWC_WLCAPP_CODE) DTCProcessRunable(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, SWC_WLCAPP_CODE) DTCProcessRunable_Record(NIO_DTC_Type test_type);
FUNC(void, SWC_WLCAPP_CODE) DemStart(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, SWC_WLCAPP_CODE) GetCurrentComMod_Runnable(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, SWC_WLCAPP_CODE) GetMaxComMod_Runnable(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, SWC_WLCAPP_CODE) GetRequestedComMod_Runnable(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, SWC_WLCAPP_CODE) NvM_RpNotifyJobEnd_StartApplication_NvMBlock1_JobFinished(NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, SWC_WLCAPP_CODE) NvM_RpNotifyJobEnd_StartApplication_NvMBlock2_JobFinished(NvM_ServiceIdType ServiceId, NvM_RequestResultType JobResult); /* PRQA S 0850 */ /* MD_MSR_19.8 */
FUNC(void, SWC_WLCAPP_CODE) RequestComModeFull_Runnable(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */
FUNC(void, SWC_WLCAPP_CODE) RequestComModeNOFull_Runnable(void); /* PRQA S 0850, 3451 */ /* MD_MSR_19.8, MD_Rte_3451 */

# define SWC_WLCAPP_STOP_SEC_CODE
# include "SWC_WLCAPP_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_CSDataServices_DemDataClass_LV_Battary_Voltage_E_NOT_OK (1U)

#  define RTE_E_CSDataServices_DemDataClass_Timestamp_E_NOT_OK (1U)

#  define RTE_E_CSDataServices_DemDataClass_Vehicle_Speed_E_NOT_OK (1U)

#  define RTE_E_CSDataServices_OccurrenceCounter_OccurenceCounter_E_NOT_OK (1U)

#  define RTE_E_CSDataServices_OdometerValue_OdometerValue_E_NOT_OK (1U)

#  define RTE_E_ComM_UserRequest_E_MODE_LIMITATION (2U)

#  define RTE_E_ComM_UserRequest_E_NOT_OK (1U)

#  define RTE_E_DiagnosticMonitor_E_NOT_OK (1U)

#  define RTE_E_F00616Event_E_NOT_OK (1U)

#  define RTE_E_PiDemOpCycle_PowerCycle_E_NOT_OK (1U)

#  define RTE_E_PiDiagnosticMonitor_DEM_EVENT_StartApplication_E_NOT_OK (1U)

#  define RTE_E_PiPS_StartApplication_NvMBlock1_E_NOT_OK (1U)

#  define RTE_E_PiPS_StartApplication_NvMBlock2_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_SWC_WLCAPP_H */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_3451:  MISRA rule: 8.8
     Reason:     Schedulable entities are declared by the RTE and also by the BSW modules.
     Risk:       No functional risk.
     Prevention: Not required.

*/
