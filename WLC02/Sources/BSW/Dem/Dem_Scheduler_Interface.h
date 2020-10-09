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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_Scheduler Scheduler
 *  \{
 *  \file       Dem_Scheduler_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of Scheduler subcomponent
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

#if !defined (DEM_SCHEDULER_INTERFACE_H)
#define DEM_SCHEDULER_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Scheduler_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Scheduler_Properties Properties
 * \{
 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Scheduler_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Scheduler_GetAndClearScheduledTasks
 *****************************************************************************/
/*!
 * \brief         Consume the 'scheduled once' task bitmask
 *
 * \details       Atomically fetches the currently 'scheduled once' task bitmap
 *                and clears it
 *
 * \return        The current 'scheduled once' task bitmap
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Scheduler_GetAndClearScheduledTasks(
  void
  );

/* ****************************************************************************
 * Dem_Scheduler_CallTask
 *****************************************************************************/
/*!
 * \brief         Call the given worker task
 *
 * \details       Call the given worker task
 *
 * \param[in]     TaskId
 *                Handle of the worker task
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_CallTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Scheduler_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Scheduler_Init
 *****************************************************************************/
/*!
 * \brief         Init asynchronous tasks.
 *
 * \details       Init asynchronous tasks.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_Init(
  void
  );

/* ****************************************************************************
 * Dem_Scheduler_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process asynchronous tasks.
 *
 * \details       This function performs asynchronous tasks.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_Scheduler_EnableTask
 *****************************************************************************/
/*!
 * \brief         Enable asynchronous task.
 *
 * \details       Schedules the given task
 *
 * \param[in]     TaskId
 *                Handle of the worker task
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_EnableTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  );


/* ****************************************************************************
 * Dem_Scheduler_EnableTaskOnce
 *****************************************************************************/
/*!
 * \brief         Enable asynchronous task.
 *
 * \details       Schedules the given task and disables it afterwards.
 *
 * \param[in]     TaskId
 *                Handle of the worker task
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_EnableTaskOnce(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  );

/* ****************************************************************************
 * Dem_Scheduler_DisableTask
 *****************************************************************************/
/*!
 * \brief         Disable asynchronous task.
 *
 * \details       Stops scheduling of the given task.
 *
 * \param[in]     TaskId
 *                Handle of the worker task
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Scheduler_DisableTask(
  CONST(Dem_Scheduler_TaskIdType, AUTOMATIC) TaskId
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_SCHEDULER_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Scheduler_Interface.h
 *********************************************************************************************************************/
