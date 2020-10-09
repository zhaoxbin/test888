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
 *  \defgroup   Dem_Esm Event State Manager
 *  \{
 *  \file       Dem_Esm_Interface.h
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

#if !defined (DEM_ESM_INTERFACE_H)
#define DEM_ESM_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Esm_Types.h"

#include "Dem_Debounce_Types.h"
#include "Dem_DTC_Types.h"
#include "Dem_Event_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Esm_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Util_SeverityWwhObdDtcClass
 *****************************************************************************/
/*!
 * \brief         Maps the given severity to the WWH-OBD DTC Class
 *
 * \details       This function maps the given severity to the WWH-OBD DTC
 *                Class
 *                DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS -> 0x00
 *                DEM_SEVERITY_WWHOBD_CLASS_C        -> 0x01
 *                DEM_SEVERITY_WWHOBD_CLASS_B2       -> 0x02
 *                DEM_SEVERITY_WWHOBD_CLASS_B1       -> 0x03
 *                DEM_SEVERITY_WWHOBD_CLASS_A        -> 0x04
 *
 * \param[in]     Severity
 *                The severity byte
 *
 * \return        The WWH-OBD DTC Class
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Util_SeverityWwhObdDtcClass(
  CONST(Dem_DTCSeverityType, AUTOMATIC)  Severity
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) || (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON)
/* ****************************************************************************
 * Dem_Util_J1939OccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Gets an event's occurrence counter for J1939 reporting.
 *
 * \details       Gets an event's occurrence counter for J1939 reporting
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Occurrence counter value in J1939 format
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON ||
 *                DEM_CFG_SUPPORT_J1939_DM31 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Util_J1939OccurrenceCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if ( (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) || (DEM_FEATURE_NEED_PID41_MMONLY_CALCULATION == STD_ON) )
/* ****************************************************************************
 * Dem_Util_SetReadinessGroupSupported
 *****************************************************************************/
/*!
 * \brief         Sets OBD Readiness Group to supported or not supported
 *
 * \details       Sets bit corresponding to readiness group in readiness supported mask
 *                (0 = not supported, 1= Supported)
 *
 * \param[in]     Supported
 *                TRUE    Readiness group is set to supported
 *                FALSE   Readiness group is set to not supported
 * \param[in]     ReadinessGroup
 *                OBD Readiness Group
 * \param[in,out] PidSupportedMask
 *                OBD Readiness supported mask
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON ||
 *                DEM_FEATURE_NEED_PID41_MMONLY_CALCULATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Util_SetReadinessGroupSupported(
  CONST(boolean, AUTOMATIC)  Supported,
  CONST(uint8, AUTOMATIC)  ReadinessGroup,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  PidSupportedMask
  );
#endif
#if ( (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) || (DEM_FEATURE_NEED_PID41_MMONLY_CALCULATION == STD_ON) )
/* ****************************************************************************
 * Dem_Util_SetReadinessGroupCompleted
 *****************************************************************************/
/*!
 * \brief         Sets OBD Readiness Group completion state
 *
 * \details       Sets bit corresponding to readiness group in given readiness
 *                supported mask to complete or not complete
 *                (0 = completed, 1 = not complete)
 *
 * \param[in]     Completed
 *                TRUE    Readiness group is set to completed
 *                FALSE   Readiness group is set to not completed
 * \param[in]     ReadinessGroup
 *                OBD Readiness Group
 * \param[in,out] PidSupportedMask
 *                OBD Readiness supported mask
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON ||
 *                DEM_FEATURE_NEED_PID41_MMONLY_CALCULATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Util_SetReadinessGroupCompleted(
  CONST(boolean, AUTOMATIC)  Completed,
  CONST(uint8, AUTOMATIC)  ReadinessGroup,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  PidSupportedMask
  );
#endif

#if (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_Util_SetReadinessGroupDisabled
 *****************************************************************************/
/*!
 * \brief         Disable OBD Readiness Group
 *
 * \details       Sets bit corresponding to readiness group Pid41DisabledMask
 *                (0 = enabled, 1= disabled)
 *
 * \param[in]     ReadinessGroup
 *                OBD Readiness Group
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Util_SetReadinessGroupDisabled(
  CONST(uint8, AUTOMATIC)  ReadinessGroup
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Esm_AddAgingTime
 *****************************************************************************/
/*!
 * \brief         Calculates target aging time
 *
 * \details       This function increments and wraps the timer value avoiding
 *                overflow and 'magic numbers'.
 *
 * \param[in]     CurrentTime
 *                Current value of the aging timer
 * \param[in]     DeltaValue
 *                Value by which CurrentTime is incremented.
 *
 * \return        Value of (CurrentTime + DeltaValue) mod X
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_Esm_AddAgingTime(
  CONST(uint32, AUTOMATIC)  CurrentTime,
  CONST(uint16, AUTOMATIC)  DeltaValue
  );
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/* ****************************************************************************
 * Dem_Esm_EventCreateTimeSeriesEntry
*****************************************************************************/
/*!
 * \brief         Allocate a time series entry
 *
 * \details       This function tries to allocate a time series entry for
 *                the given event. This can displace existing time series
 *                entries if all time series entries are occupied.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TIME_SERIES == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Esm_EventCreateTimeSeriesEntry(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif



#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Esm_IncrementQualifiedActiveEventCount
 *****************************************************************************/
/*!
 * \brief         Handles the increment of the qualified active DTC count.
 *
 * \details       This function calculates the qualified active DTC counter
 *                when an event transitions from not active to qualified active.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Esm_IncrementQualifiedActiveEventCount(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Esm_DecrementQualifiedActiveEventCount
 *****************************************************************************/
/*!
 * \brief         Handles the decrement of the qualified active DTC count.
 *
 * \details       This function calculates the qualified active DTC counter
 *                when an event transitions from qualified active to a state
 *                with TF == 0.
 *                If the counter reaches 0 this will start healing of the B1
 *                counter, and ContinousMI counter if activation mode 4 is not
 *                active.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     StartB1Healing
 *                Flag to control if B1 counter needs to heal
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Esm_DecrementQualifiedActiveEventCount(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  StartB1Healing
  );
#endif


#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_Esm_ResetIumprFidPending
 *****************************************************************************/
/*!
 * \brief         Reset pending FID status of all ratios
 *
 * \details       Reset pending FID status of all ratios
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_IUMPR == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Esm_ResetIumprFidPending(
  void
  );
#endif

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_Esm_RatioQueueAsync
 *****************************************************************************/
/*!
 * \brief         Queue ratio processing for an event
 *
 * \details       This function will set up IUMPR processing of the event's
 *                ratio, if the numerator has not been incremented yet.
 *
 * \param[in]     RatioIndex
 *                Unique handle of the Ratio
 *
 * \pre           Must be called within critical section 'DiagMonitor'
 * \config        DEM_FEATURE_NEED_IUMPR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Esm_RatioQueueAsync(
  CONST(Dem_RatioIdIndexType, AUTOMATIC)  RatioIndex
  );
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_RESTART_DCY_ON_CLEAR_DTC == STD_ON)
/* ****************************************************************************
 * Dem_Esm_PreOnClear_AllDtc
 *****************************************************************************/
/*!
 * \brief         Restarts the DCY before Clear DTC is processed
 *
 * \details       This function is called before ClearAllDTC is processed.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the event memory
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON &&
 *                DEM_CFG_SUPPORT_RESTART_DCY_ON_CLEAR_DTC == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Esm_PreOnClear_AllDtc(
  CONST(uint8, AUTOMATIC)  MemoryId
  );
#endif

/* ****************************************************************************
 * Dem_Esm_PostOnClear_AllDtc
 *****************************************************************************/
/*!
 * \brief         Clears global statistics after Clear DTC was processed
 *
 * \details       This function is called when ClearAllDTC was finished.
 *                It clears all global statistic data which is cleared only
 *                on ClearAllDTC requests.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the event memory
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Esm_PostOnClear_AllDtc(
  CONST(uint8, AUTOMATIC)  MemoryId
  );

/* ****************************************************************************
 * Dem_Esm_PostOnClear_Always
 *****************************************************************************/
/*!
 * \brief         Clears global OBD statistics after Clear DTC was processed
 *
 * \details       This function is called after a ClearDTC request was processed.
 *                It clears all global statistic data which is cleared with
 *                all clear requests.
 *
 * \param[in]     MemoryId
 *                Unique identifier of the event memory
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Esm_PostOnClear_Always(
  CONST(uint8, AUTOMATIC)  MemoryId
  );



#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_Esm_SetPid01ReadinessState
 *****************************************************************************/
/*!
 * \brief         Marks the PID01 information of the given readiness group to
 *                be updated
 *
 * \details       Marks the PID01 information of the given readiness group to
 *                be updated
 *
 * \param[in]     State
 *                Current readiness state as 16 bit bitmap
 *
 * \param[in]     ReadinessGroup
 *                Identifier for readiness group 
 *
 * \return        New readiness state
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Esm_SetPid01ReadinessState(
  CONST(uint16, AUTOMATIC) State,
  CONST(uint8, AUTOMATIC) ReadinessGroup
  );
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_Esm_ResetPid01ReadinessState
 *****************************************************************************/
/*!
 * \brief         Removes the mark for updating the PID01 information of the
 *                given readiness group
 *
 * \details       Removes the mark for updating the PID01 information of the
 *                given readiness group
 *
 * \param[in]     State
 *                Current readiness state as 16 bit bitmap
 *
 * \param[in]     ReadinessGroup
 *                Identifier for readiness group
 *
 * \return        New readiness state
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Esm_ResetPid01ReadinessState(
  CONST(uint16, AUTOMATIC) State,
  CONST(uint8, AUTOMATIC) ReadinessGroup
  );
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_Esm_TestPid01ReadinessState
 *****************************************************************************/
/*!
 * \brief         Tests if PID01 information of the given readiness group has
 *                to be updated
 *
 * \details       Tests if PID01 information of the given readiness group has
 *                to be updated
 *
 * \param[in]     State
 *                Current readiness state as 16 bit bitmap
 *
 * \param[in]     ReadinessGroup
 *                Identifier for readiness group 
 *
 * \return        TRUE
 *                PID01 information of given readiness group has to be updated
 * \return        FALSE
 *                PID01 information of given readiness group doesn't have to 
 *                be updated
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Esm_TestPid01ReadinessState(
  CONST(uint16, AUTOMATIC) State,
  CONST(uint8, AUTOMATIC) ReadinessGroup
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_ESM_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Esm_Interface.h
 *********************************************************************************************************************/
