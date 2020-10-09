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
 *  \file       Dem_Scheduler_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of Scheduler subcomponent
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

#if !defined (DEM_SCHEDULER_TYPES_H)
#define DEM_SCHEDULER_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Task Handle, in order of priority */
enum Dem_Scheduler_TaskId
{
  Dem_Scheduler_Task_Dtr,
  Dem_Scheduler_Task_Prestorage,
  Dem_Scheduler_Task_ClearTask,
  Dem_Scheduler_Task_Event,
  Dem_Scheduler_Task_TimeSeries,
  Dem_Scheduler_Task_FilterEventData,
  Dem_Scheduler_Task_EnableCondition,
  Dem_Scheduler_Task_EventQueue,
  Dem_Scheduler_Task_OperationCycle,
  Dem_Scheduler_Task_IUMPR,
  Dem_Scheduler_Task_Odometer,
  Dem_Scheduler_Task_EngineRuntime,
  Dem_Scheduler_Task_PID01,
  Dem_Scheduler_Task_NvM,
  Dem_Scheduler_Task_Invalid
};

typedef enum Dem_Scheduler_TaskId Dem_Scheduler_TaskIdType;

#endif /* DEM_SCHEDULER_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Scheduler_Types.h
 *********************************************************************************************************************/
