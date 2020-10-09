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
 *  \defgroup   Dem_Queue Master Queue
 *  \{
 *  \file       Dem_Queue_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    
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

#if !defined (DEM_QUEUE_INTERFACE_H)
#define DEM_QUEUE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Queue_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Queue_Properties Properties
 * \{
 */

#if (DEM_FEATURE_NEED_PID01_CALCULATION  == STD_ON)
/* ****************************************************************************
 * Dem_Queue_SetPid01UpdateFlag
 *****************************************************************************/
/*!
 * \brief         Set the update flag for PID01
 *
 * \details       Set the update flag for PID01
 *
 * \param[in]     UpdateFlag
 *                Value to set
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID01_CALCULATION  == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Queue_SetPid01UpdateFlag(
  CONST(uint16, AUTOMATIC)  UpdateFlag
  );
#endif

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
 * \defgroup Dem_Queue_Private Private Methods
 * \{
 */

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
 * \defgroup Dem_Queue_Public Public Methods
 * \{
 */
/* ****************************************************************************
 * Dem_Timer_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the timer functionality
 *
 * \details       This function initializes all global variables required for
 *                timer handling, e.g. engine run time.
 *
 * \pre           May only be called during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Timer_Init(
  void
  );

/* ****************************************************************************
 * Dem_Timer_MainFunction
 *****************************************************************************/
/*!
 * \brief         Processes timer calculations
 *
 * \details       This function processes global timers, e.g. for engine run
 *                times. Must be called cyclically according to the configured
 *                cycle time.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_ENGINE_RUN_TIME == STD_ON ||
 *                DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Timer_MainFunction(
  void
  );

                                                                    /* Queue */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_Queue_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-Initializes Dem queue states
 *
 * \details       This function initializes all global variables encoding queue
 *                states. Queued elements are qualification of events, e.g.
 *                FDCTRIP and PASSED<->FAILED toggles, as well as changes to a
 *                cycle state.
 *
 * \pre           May be called only during pre-initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_PreInit(
  void
  );

/* ****************************************************************************
 * Dem_Queue_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the Dem queue states
 *
 * \details       This function initializes all global variables required to
 *                defer asynchronous requests to be processed on the Dem task
 *                function.
 *
 * \pre           May be called only during initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_Init(
  void
  );

/* ****************************************************************************
 * Dem_Queue_ProcessIumpr
 *****************************************************************************/
/*!
 * \brief         Performs IUMPR calculation
 *
 * \details       This function checks if the numerator and denominator must be
 *                incremented for any ratio, and performs all necessary
 *                increments.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_ProcessIumpr(
  void
  );

/* ****************************************************************************
 * Dem_Queue_ProcessOdometer
 *****************************************************************************/
/*!
 * \brief         Processes all tasks related to odometer updates
 *
 * \details       This function fetches the current odometer data and updates
 *                odometer related statistic data, e.g. PIDs or the permanent
 *                memory activation.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_ProcessOdometer(
  void
  );

/* ****************************************************************************
 * Dem_Queue_CalculatePid01
 *****************************************************************************/
/*!
 * \brief         Calculates PID 0x01
 *
 * \details       Calculates PID 0x01 in case major monitors and PID01 are
 *                supported.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_CalculatePid01(
  void
  );

#if (DEM_CFG_SUPPORT_PID4D == STD_ON)
/* ****************************************************************************
 * Dem_Queue_CalculatePid4D
 *****************************************************************************/
/*!
 * \brief         Calculates PID 0x4D
 *
 * \details       Calculates PID 0x4D
 *
 * \param[in]     EngineRunTimeTicks
 *                Current engine run time since engine start
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PID4D == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_CalculatePid4D(
  CONST(uint32, AUTOMATIC)  EngineRunTimeTicks
  );
#endif

#if (DEM_CFG_SUPPORT_PID4E == STD_ON)
/* ****************************************************************************
 * Dem_Queue_CalculatePid4E
 *****************************************************************************/
/*!
 * \brief         Calculates PID 0x4E
 *
 * \details       Calculates PID 0x4E
 *
 * \param[in]     EngineRunTimeTicks
 *                Current engine run time since engine start
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PID4E == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_CalculatePid4E(
  CONST(uint32, AUTOMATIC)  EngineRunTimeTicks
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Queue_CalculateB1Counter
 *****************************************************************************/
/*!
 * \brief         Calculates the B1 counter
 *
 * \details       Calculates the B1 counter
 *
 * \param[in]     EngineRunTimeTicks
 *                Current engine run time since engine start
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_CalculateB1Counter(
  CONST(uint32, AUTOMATIC)  EngineRunTimeTicks
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Queue_ProcessContinuousMiCounter
 *****************************************************************************/
/*!
 * \brief         Calculates the Continuous MI counter
 *
 * \details       Calculates the Continuous MI counter
 *
 * \param[in]     EngineRunTimeTicks
 *                Current engine run time since engine start
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_ProcessContinuousMiCounter(
  CONST(uint32, AUTOMATIC)  EngineRunTimeTicks
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Queue_ProcessAgingTimer
 *****************************************************************************/
/*!
 * \brief         Calculates the 200h aging timer
 *
 * \details       This function processes aging of WWH-OBD DTCs after 200h of
 *                engine run time
 *
 * \param[in]     EngineRunTimeTicks
 *                Current engine run time since engine start
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_ProcessAgingTimer(
  CONST(uint32, AUTOMATIC)  EngineRunTimeTicks
  );
#endif

/* ****************************************************************************
 * Dem_Queue_ProcessEngineRuntime
 *****************************************************************************/
/*!
 * \brief         Processes all tasks related to engine runtime
 *
 * \details       This function processes all engine runtime data related
 *                tasks, e.g. for PID 0x4D, PID 0x4E, DTC aging or B1Counter
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_ProcessEngineRuntime(
  void
  );

/* ****************************************************************************
 * Dem_Queue_ProcessTimeSeries
 *****************************************************************************/
/*!
 * \brief         Processes all tasks related to time series snapshot records
 *
 * \details       Each time the related timers have expired time series snapshot
 *                data is collected and stored into ring buffers.
 *                Furthermore the storage of future samples is triggered for
 *                all events which have allocated a time series entry.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Queue_ProcessTimeSeries(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_QUEUE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Queue_Interface.h
 *********************************************************************************************************************/
