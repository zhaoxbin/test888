/* ********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 */
/*! \addtogroup Dem_Scheduler
 *  \{
 *  \file       Dem_Scheduler_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of Scheduler subcomponent
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Savas Ates                    vissat        Vector Informatik GmbH
 *  Anna Bosch                    visanh        Vector Informatik GmbH
 *  Stefan Huebner                vishrs        Vector Informatik GmbH
 *  Thomas Dedler                 visdth        Vector Informatik GmbH
 *  Alexander Ditte               visade        Vector Informatik GmbH
 *  Matthias Heil                 vismhe        Vector Informatik GmbH
 *  Erik Jeglorz                  visejz        Vector Informatik GmbH
 *  Friederike Hitzler            visfrs        Vector Informatik GmbH
 *  Aswin Vijayamohanan Nair      visavi        Vector Informatik GmbH
 *  Fabian Wild                   viszfa        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_SCHEDULER_IMPLEMENTATION_H)
#define DEM_SCHEDULER_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Scheduler_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Com_Implementation.h"
#include "Dem_DtrIF_Interface.h"
#include "Dem_ClearTask_Interface.h"
#include "Dem_EventQueue_Interface.h"
#include "Dem_EnableCondition_Interface.h"
#include "Dem_ClientAccess_Interface.h"
#include "Dem_Error_Interface.h"
#include "Dem_OperationCycle_Interface.h"
#include "Dem_Nvm_Interface.h"
#include "Dem_Event_Interface.h"
#include "Dem_Queue_Interface.h"
#include "Dem_Prestore_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

DEM_LOCAL volatile VAR(uint32, DEM_VAR_NOINIT) Dem_Scheduler_ScheduledMultipleInvocationTasks;
DEM_LOCAL volatile VAR(uint32, DEM_VAR_NOINIT) Dem_Scheduler_ScheduledSingleInvocationTasks;

#define DEM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_Scheduler_Properties
 * \{
 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_Scheduler_Private
 * \{
 */

/* ****************************************************************************
 % Dem_Scheduler_GetAndClearScheduledTasks
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Scheduler_GetAndClearScheduledTasks(
  void
  )
{
  uint32 lScheduledTasks;
  do
  {
    lScheduledTasks = Dem_Scheduler_ScheduledSingleInvocationTasks;
    if (lScheduledTasks == 0)
    {
      break;
    }
  }
  while (Dem_Com_SyncCompareAndSwap(&Dem_Scheduler_ScheduledSingleInvocationTasks, lScheduledTasks, 0) == FALSE);                /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
  return lScheduledTasks;
}

/* ****************************************************************************
 % Dem_Scheduler_CallTask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_CallTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  )
{
  switch (TaskId)
  {
  case Dem_Scheduler_Task_Dtr:
    Dem_DtrIF_MainFunction();
    break;
  case Dem_Scheduler_Task_Prestorage:
    Dem_Prestore_MainFunction();
    break;
  case Dem_Scheduler_Task_ClearTask:
    Dem_ClearTask_MainFunction();
    break;
  case Dem_Scheduler_Task_Event:
    Dem_Event_MainFunction();
    break;
  case Dem_Scheduler_Task_TimeSeries:
    Dem_Queue_ProcessTimeSeries();
    break;
  case Dem_Scheduler_Task_FilterEventData:
    Dem_ClientAccess_FillDTCReadoutBufferData();
    break;
  case Dem_Scheduler_Task_EnableCondition:
    Dem_EnableCondition_MainFunction();
    break;
  case Dem_Scheduler_Task_EventQueue:
    Dem_EventQueueCore_MainFunction();
    break;
  case Dem_Scheduler_Task_OperationCycle:
    Dem_OperationCycle_MainFunction();
    break;
  case Dem_Scheduler_Task_IUMPR:
    Dem_Queue_ProcessIumpr();
    break;
  case Dem_Scheduler_Task_Odometer:
    Dem_Queue_ProcessOdometer();
    break;
  case Dem_Scheduler_Task_EngineRuntime:
    Dem_Queue_ProcessEngineRuntime();
    break;
  case Dem_Scheduler_Task_PID01:
    Dem_Queue_CalculatePid01();
    break;
  case Dem_Scheduler_Task_NvM:
    Dem_Nvm_MainFunction();
    break;
  default:
    Dem_Internal_AssertAlways(DEM_E_PARAM_CONFIG)
    break;
  }
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \addtogroup Dem_Scheduler_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Scheduler_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_Init(
  void
  )
{
  Dem_Scheduler_ScheduledMultipleInvocationTasks = 0U;
  Dem_Scheduler_ScheduledSingleInvocationTasks = 0U;
}

/* ****************************************************************************
 % Dem_Scheduler_MainFunction
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_MainFunction(
  void
  )
{
  uint32 lActiveTasks;
  uint8 lCurrentTask;
  
  lActiveTasks = (uint32)(Dem_Scheduler_ScheduledMultipleInvocationTasks | Dem_Scheduler_GetAndClearScheduledTasks());
  lCurrentTask = 0;

  while (lActiveTasks != 0)
  {
    while (DEM_TEST_BIT(lActiveTasks, 0) == FALSE)
    {
      lActiveTasks = (uint32)(lActiveTasks >> 1);
      ++lCurrentTask;
    }

    Dem_Scheduler_CallTask((Dem_Scheduler_TaskIdType)lCurrentTask);

    lActiveTasks = (uint32)(lActiveTasks >> 1);
    ++lCurrentTask;
  }
}

/* ****************************************************************************
 % Dem_Scheduler_EnableTask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_EnableTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  )
{
  Dem_Com_SyncSetBitInBitfield(&Dem_Scheduler_ScheduledMultipleInvocationTasks, 1, (Dem_HandleType)TaskId);                      /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
}

/* ****************************************************************************
 % Dem_Scheduler_EnableTaskOnce
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_EnableTaskOnce(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  )
{
  Dem_Com_SyncSetBitInBitfield(&Dem_Scheduler_ScheduledSingleInvocationTasks, 1, (Dem_HandleType)TaskId);                        /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
}

/* ****************************************************************************
 % Dem_Scheduler_DisableTask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_DisableTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  )
{
  Dem_Com_SyncResetBitInBitfield(&Dem_Scheduler_ScheduledMultipleInvocationTasks, 1, (Dem_HandleType)TaskId);                    /* SBSW_DEM_POINTER_FORWARD_GLOBAL */
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_SCHEDULER_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Scheduler_Implementation.h
 *********************************************************************************************************************/
