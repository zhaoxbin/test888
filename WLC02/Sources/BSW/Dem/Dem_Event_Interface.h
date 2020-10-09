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
 *  \defgroup   Dem_Event Interface for Events
 *  \{
 *  \file       Dem_Event_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of the Event subcomponent
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

#if !defined (DEM_EVENT_INTERFACE_H)
#define DEM_EVENT_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Event_Types.h"

/* ------------------------------------------------------------------------- */
#include "Dem_DTC_Types.h"
#include "Dem_DTCInternalStatus_Types.h"


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

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \defgroup Dem_Event_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Event_TestValidHandle
 *****************************************************************************/
/*!
 * \brief         Test whether a handle is a valid event ID
 *
 * \details       This function tests whether a handle is in the valid range
 *                of EventIds. This function does not consider calibration or
 *                runtime-availability.
 *
 * \param[in]     EventId
 *                Handle to test against range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                EventId is valid
 * \return        FALSE
 *                EventId is not valid
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestValidHandle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_Event_TestMilSupport
 *****************************************************************************/
/*!
 * \brief         Returns if the event supports the Mil indicator.
 *
 * \details       Returns if the event supports the Mil indicator.
 *
 * \param[in]     EventId
 *                Unique handle of the event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The MIL is supported.
 *                FALSE
 *                The MIL is not supported.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestMilSupport(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_Event_GetInternalStatus
 *****************************************************************************/
/*!
 * \brief         Get current internal status of the event
 *
 * \details       Get current internal status of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \return        Current internal status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_Event_GetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_Event_SetInternalStatus
 *****************************************************************************/
/*!
 * \brief         Set current internal status value of the event
 *
 * \details       Set current internal status value of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     Status
 *                New internal status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) Status
  );

/* ****************************************************************************
 * Dem_Event_GetExtendedStatus
 *****************************************************************************/
/*!
 * \brief         Get current extended status of the event
 *
 * \details       Get current extended status of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \return        Current extended status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_ExtendedStatusType, DEM_CODE)
Dem_Event_GetExtendedStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_Event_SetExtendedStatus
 *****************************************************************************/
/*!
 * \brief         Set current extended status value of the event
 *
 * \details       Set current extended status value of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     Status
 *                New extended status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetExtendedStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_DTC_ExtendedStatusType, AUTOMATIC) Status
  );

#if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
/* ****************************************************************************
 * Dem_Event_GetTripCount
 *****************************************************************************/
/*!
 * \brief         Get current trip count of the event
 *
 * \details       Get current trip count of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \return        Current trip count of the event
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_GetTripCount(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );
#endif

#if (DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON)
/* ****************************************************************************
 * Dem_Event_SetTripCount
 *****************************************************************************/
/*!
 * \brief         Set current trip count of the event
 *
 * \details       Set current trip count of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     TripCount
 *                New trip count of the event
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_TRIPCOUNTER == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetTripCount(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(uint8, AUTOMATIC) TripCount
  );
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_Event_GetQualifyStatus
 *****************************************************************************/
/*!
 * \brief         Get current qualification status of the event
 *
 * \details       Get current qualification status of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \return        Current qualification status of the event
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_GetQualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_Event_SetQualifyStatus
 *****************************************************************************/
/*!
 * \brief         Set current qualification status of the event
 *
 * \details       Set current qualification status of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     Status
 *                New qualification status of the event
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetQualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(uint8, AUTOMATIC) Status
  );
#endif

/* ****************************************************************************
 * Dem_Event_GetUDSStatus
 *****************************************************************************/
/*!
 * \brief         Get current UDS status of the event
 *
 * \details       Get current UDS status of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 *
 * \return        Current UDS status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_Event_GetUDSStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_Event_SetUDSStatus
 *****************************************************************************/
/*!
 * \brief         Set current UDS status value of the event
 *
 * \details       Set current UDS status value of the event
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     Status
 *                New UDS status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetUDSStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_UDSStatus_Type, AUTOMATIC) Status
  );

/* ****************************************************************************
 * Dem_Event_GetExternalUDSStatus
 *****************************************************************************/
/*!
 * \brief         Get the current external UDS status of the event
 *
 * \details       Get the current external UDS status of the event. 
 *                In case of OBD the non-qualified status bits are masked out.
 *
 * \param[in]     EventId
 *                Unique handle of the event
 * \param[in]     EventStatus
 *                The current internal event status of the event
 *
 * \return        Current external UDS status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_UDSStatus_Type, DEM_CODE)
Dem_Event_GetExternalUDSStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_UDSStatus_Type, AUTOMATIC)  EventStatus
  );


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
 * \defgroup Dem_Event_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Event_TestSimilarConditions
 *****************************************************************************/
/*!
 * \brief         Test if similar conditions are fullfilled for event.
 *
 * \details       Test if similar conditions are fullfilled for event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                Similar conditions are supported, event is OBD related and
 *                the external status bit for similar conditions is set.
 * \return        FALSE
 *                Otherwise.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestSimilarConditions(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_IMMEDIATEHEAL == STD_ON)
/* ****************************************************************************
 * Dem_Event_Passed_ProcessHealing
 *****************************************************************************/
/*!
 * \brief         Process event healing for events with healing target 0.
 *
 * \details       Tests if an event has healed with healing target 0 and
 *                processes the actions resulting from healing. This function
 *                has no effect when called for events with healing target != 0.
 *
 * \param[in]     EventContext
 *                Event processing context
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_IMMEDIATEHEAL == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Passed_ProcessHealing(
  CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
  );
#endif

/* ****************************************************************************
 * Dem_Event_TestConfirmed
 *****************************************************************************/
/*!
 * \brief         Tests if an event has confirmed (completed tripping)
 *
 * \details       -
 *
 * \param[in]     EventContext
 *                Event processing context
 *
 * \return        TRUE
 *                Event is confirmed
 * \return        FALSE
 *                Event is not yet confirmed
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestConfirmed(
  CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC)  EventContext
  );

/* ****************************************************************************
 * Dem_Event_OpCycleStart
 *****************************************************************************/
/*!
 * \brief         Processes the start of the event's operation cycle
 *
 * \details       Processes the start of the event's operation cycle: Reset
 *                status bits and debouncing.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_OpCycleStart(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_ProcessHealing
 *****************************************************************************/
/*!
 * \brief         Processes an event's healing conditions
 *
 * \details       Processes the healing counter. If the healing conditions
 *                configured for the event are fulfilled, the event is healed.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     EventStatus
 *                Current event status of the event
 *
 * \return        Modified event status based on the status passed
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_ProcessHealing(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  EventStatus
  );

/* ****************************************************************************
 * Dem_Event_OpCycleEnd_Healing
 *****************************************************************************/
/*!
 * \brief         Processes healing at the end of the event's operation cycle
 *
 * \details       Processes healing at the end of the event's operation cycle
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     EventStatus
 *                Current event status
 *
 * \return        TRUE if the event has fulfilled the preconditions to start aging
 *                FALSE if the event is blocked from aging
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_OpCycleEnd_Healing(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  EventStatus
  );

/* ****************************************************************************
 * Dem_Event_OpCycleEnd
 *****************************************************************************/
/*!
 * \brief         Processes the end of the event's operation cycle
 *
 * \details       Processes actions performed at the end of the event's operation
 *                cycle, i.e. healing, aging start condition.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     OldDtcStatus
 *                Dtc status before cycle restart
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_OpCycleEnd(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  OldDtcStatus
  );

/* ****************************************************************************
 * Dem_Event_InitEventContext
 *****************************************************************************/
/*!
 * \brief         Initialize context of event's status report processing.
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[out]    EventContext
 *                Event processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitEventContext(
CONST(Dem_EventIdType, AUTOMATIC)  EventId,
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
);

/* ****************************************************************************
 * Dem_Event_CalculateStatusOnFailed
 *****************************************************************************/
/*!
 * \brief         Update of event's storage independent UDS status bits on 
 *                'Failed' status report
 *
 * \details       -
 *
 * \param[in,out] EventContext
 *                Event processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventContext->EventId or same EventContext
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_CalculateStatusOnFailed(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
);

/* ****************************************************************************
 * Dem_Event_CalculateFailedEffects
 *****************************************************************************/
/*!
 * \brief         Calculate storage independent event triggers on 'Failed' status report.
 *
 * \details       Calculate event triggers from changed, storage independent 
 *                UDS status bits on 'Failed' status report.
 *
 * \param[in,out] EventContext
 *                Event processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventContext->EventId or same EventContext
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_CalculateFailedEffects(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
);                                                      

/* ****************************************************************************
 * Dem_Event_CalculateStatusOnFailed_OnStorage
 *****************************************************************************/
/*!
 * \brief         Update of event's storage dependent UDS status bits on 
 *                'Failed' status report
 *
 * \details       -
 *
 * \param[in,out] EventContext
 *                Event processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventContext->EventId or same EventContext
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_CalculateStatusOnFailed_OnStorage(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
);                                                                                                                               /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Event_CalculateFailedEffects_OnStorage
 *****************************************************************************/
/*!
 * \brief         Calculate storage depending event triggers on 'Failed' status report.
 *
 * \details       Among others, process reaching pending state, confirmation 
 *                on reaching event's or Mil group's (if configured) trip count
*                 target and warning indicator requests.
 *
 * \param[in,out] EventContext
 *                Event processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_CalculateFailedEffects_OnStorage(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
);                                                                                                                               /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Event_ProcessFailedEffects
 *****************************************************************************/
/*!
 * \brief         Process storage depending event triggers on 'Failed' status report.
 *
 * \details       Process event's warning indicator requests. Enable user indicator
 *                and special indicator (id configured). If Mil indicator is 
 *                requested, store 'Permanent DTC'.
 *
 * \param[in,out] EventContext
 *                Event processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_ProcessFailedEffects(
CONSTP2CONST(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
);

/* ****************************************************************************
 * Dem_Event_CalculateStatusOnPassed
 *****************************************************************************/
/*!
 * \brief         Update of event's UDS status bits on 'Passed' status report
 *
 * \details       -
 *
 * \param[in,out] EventContext
 *                Event processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventContext->EventId or same EventContext
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_CalculateStatusOnPassed(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
);

/* ****************************************************************************
 * Dem_Event_Passed_CalcEventEffects
 *****************************************************************************/
/*!
 * \brief         Calculate event triggers on 'Passed' status report.
 *
 * \details       -
 *
 * \param[in,out] EventContext
 *                Event processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventContext->EventId or same EventContext
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Passed_CalcEventEffects(
CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
);

/* ****************************************************************************
 * Dem_Event_ProcessPassedEffects
 *****************************************************************************/
/*!
 * \brief         Process event triggers on 'Passed' status report.
 *
 * \details       Process event healing (among others).
 *
 * \param[in,out] EventContext
 *                Event processing context
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_ProcessPassedEffects(
  CONSTP2VAR(Dem_Event_ContextType, AUTOMATIC, AUTOMATIC) EventContext
  );

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_Event_QualifyStatus
 *****************************************************************************/
/*!
 * \brief         Process qualification status of an event.
 *
 * \details       In case the DCY is not already qualified, this masks the
 *                confirmed and WIR bits of the event status. These are
 *                restored once the DCY qualifies later.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     Effects
 *                Trigger flags
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
  Dem_Event_QualifyStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  Effects
  );
#endif

/* ****************************************************************************
 * Dem_Event_InitAvailableNV
 *****************************************************************************/
/*!
 * \brief         Initializes the event availability from NV Ram
 *
 * \details       Initializes the event availability from NV Ram
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitAvailableNV(
  void
  );

/* ****************************************************************************
 * Dem_Event_InitQualification
 *****************************************************************************/
/*!
 * \brief         Initializes the qualification states
 *
 * \details       Initializes the qualification states
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitQualification(
  void
  );

/* ****************************************************************************
 * Dem_Event_InitEventInternalStatus
 *****************************************************************************/
/*!
 * \brief         Initializes the internal event status of a given event
 *
 * \details       Initializes the internal event status of a given event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitEventInternalStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_InitStatus_ResetStoredOnlyBits
 *****************************************************************************/
/*!
 * \brief         Reset the stored-only bits in the UDS status.
 *
 * \details       Reset the stored-only bits in the UDS status.
 *
 * \param[in]     EventStatus
 *                Current UDS status of the event.
 * \return        Updated value of the EventStatus
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_InitStatus_ResetStoredOnlyBits(
  CONST(Dem_UDSStatus_Type, AUTOMATIC) EventStatus
  );

#if (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
/* ****************************************************************************
 * Dem_Event_InitStatus_AgedEvent
 *****************************************************************************/
/*!
 * \brief         Initialize aged events.
 *
 * \details       For aged events, reset in the UDS status the relevant bits
 *                and perform or start healing.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     EventStatus
 *                Current UDS status of the event.
 * \return        Updated value of the EventStatus
 *
 * \pre           May be called only during module initialization
 * \config        (DEM_CFG_AGING_RETAIN_MEMORY_ENTRY == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_InitStatus_AgedEvent(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_UDSStatus_Type, AUTOMATIC) EventStatus
  );
#endif

/* ****************************************************************************
 * Dem_Event_InitStatus_AgingEvent
 *****************************************************************************/
/*!
 * \brief         Initialize aging events.
 *
 * \details       For aging events, reset in the UDS status the relevant bits
 *                and perform or start healing.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     EventStatus
 *                Current UDS status of the event.
 * \return        Updated value of the EventStatus
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Event_InitStatus_AgingEvent(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_UDSStatus_Type, AUTOMATIC) EventStatus
  );

/* ****************************************************************************
 * Dem_Event_InitStatus_UpdateIndicators
 *****************************************************************************/
/*!
 * \brief         Update the indicator enable count.
 *
 * \details       Update the indicator enable count.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitStatus_UpdateIndicators(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

#if (DEM_FEATURE_NEED_INDICATORS == STD_ON) && (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 * Dem_Event_InitStatus_UpdateMilGroups
 *****************************************************************************/
/*!
 * \brief         Update the MIL group pending event count.
 *
 * \details       Update the MIL group pending event count.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           May be called only during module initialization
 * \config        (DEM_FEATURE_NEED_INDICATORS == STD_ON)
 *                && (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitStatus_UpdateMilGroups(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );
#endif

/* ****************************************************************************
 * Dem_Event_InitEventStatus
 *****************************************************************************/
/*!
 * \brief         Initializes the event status of a given event
 *
 * \details       Initializes the event status of a given event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitEventStatus(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_Event_ProcessEventAvailable
 *****************************************************************************/
/*!
 * \brief         Process event availability changes
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_ProcessEventAvailable(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
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
 * \defgroup Dem_Event_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Event_TestEventMayAge
 *****************************************************************************/
/*!
 * \brief         Tests whether an event may age
 *
 * \details       Tests whether an event may age
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     EventStatus
 *                Current event status of the event
 *
 * \return        TRUE
 *                The event may age
 * \return        FALSE
 *                The event may not age
 *
 * \pre           -
 *
 * \config        DEM_FEATURE_NEED_HEALING == STD_ON 
 *                  && DEM_FEATURE_NEED_AGING_AFTER_HEALING == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_TestEventMayAge(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  EventStatus
  );

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_Event_Disconnect_Normal
 *****************************************************************************/
/*!
 * \brief         Marks a normal event unavailable
 *
 * \details       This function sets the event unavailable if it is not stored.
 *
 *                Do not call directly, use Dem_Event_Disconnect instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           Must be called in critical section DiagMonitor
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Disconnect_Normal(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_Event_Disconnect
 *****************************************************************************/
/*!
 * \brief         Marks an event unavailable
 *
 * \details       This function sets an event unavailable, if its state allows
 *                to do so.
 *
 *                In case the event is set unavailable, its event status byte
 *                is changed to 0x00 and the FiM is informed.
 *
 *                Otherwise, this function returns E_NOT_OK.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        E_OK
 *                The event was set to unavailable
 * \return        E_NOT_OK
 *                The event was not set to unavailable
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_Disconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_Event_Reconnect_Normal
 *****************************************************************************/
/*!
 * \brief         Marks a normal event available
 *
 * \details       This function sets the event available.
 *
 *                Do not call directly, use Dem_Event_Reconnect instead.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Reconnect_Normal(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_Event_TestEventAvailable
 *****************************************************************************/
/*!
 * \brief         Tests if an Event is available based on runtime calibration
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event is available
 * \return        FALSE
 *                The event is not available
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestEventAvailable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_Event_TestEventSuppressed
 *****************************************************************************/
/*!
 * \brief         Tests if an event can be considered for reporting API
 *
 * \details       Tests all options due to which an event has to be excluded
 *                from reporting API, based on an individual event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event is currently suppressed
 * \return        FALSE
 *                The event is currently not suppressed
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_IUMPR == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestEventSuppressed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON) \
 || (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_Event_TestEventUnavailable
 *****************************************************************************/
/*!
 * \brief         Tests if an event is unavailable
 *
 * \details       Tests all options due to which an event can be set 
 *                unavailable, based on an individual event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event is currently unavailable
 * \return        FALSE
 *                The event is currently available
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
 *                || (DEM_FEATURE_NEED_PID41_CALCULATION == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestEventUnavailable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_FEATURE_NEED_EVENTAVAILABLE_DEFAULT == STD_ON) \
 || (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
/* ****************************************************************************
 * Dem_Event_SetDisconnectedBit
 *****************************************************************************/
/*!
 * \brief         Set an event's disconnected bit
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     IsDisconnected
 *                TRUE: Set disconnected bit to TRUE
 *                FALSE: Set disconnected bit to FALSE
 *
 * \pre           Must be called within critical section DiagMonitor
 * \config        (DEM_FEATURE_NEED_EVENTAVAILABLE_DEFAULT == STD_ON)
 *                || (DEM_FEATURE_NEED_EVENTAVAILABLE_NV == STD_ON)
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetDisconnectedBit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  IsDisconnected
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_Event_MayDisconnect
 *****************************************************************************/
/*!
 * \brief         Tests precondition for event disconnect
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \return        TRUE
 *                The event may be disconnected
 * \return        FALSE
 *                The event may not be disconnected
 * \pre           Must be called within critical section DiagMonitor
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_MayDisconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_Event_Reconnect
 *****************************************************************************/
/*!
 * \brief         Marks an event available
 *
 * \details       This function sets an event available.
 *
 *                In case the event is set available, its event status byte is
 *                changed to 0x50 and the FiM is informed.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Reconnect(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );
#endif

/* ****************************************************************************
 * Dem_Event_ProcessFdc
 *****************************************************************************/
/*!
 * \brief         Process the event's FDC trip actions
 *
 * \details       This function processes the stored triggers from debounce
 *                values passing the FDC trip threshold.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     FdcThresholdExceeded
 *                FDC Storage threshold was exceeded
 * \param[in]     FdcMaximumExceeded
 *                FDC Maximum (this cycle) was exceeded
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_ProcessFdc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  FdcThresholdExceeded,
  CONST(boolean, AUTOMATIC)  FdcMaximumExceeded
  );

/* ****************************************************************************
 * Dem_Event_Passed
 *****************************************************************************/
/*!
 * \brief         Process the event's queued qualified passed result
 *
 * \details       This function processes a passed result stored on the
 *                event queue, for events using the QUEUED mechanism. The
 *                triggers resulting from the status bit changes are calculated
 *                within this function, based on the current event status.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Event_Passed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_Healed
 *****************************************************************************/
/*!
 * \brief         Heals an event
 *
 * \details       Resets all warning indicator requests from the given event.
 *                This can modify the global indicator state if the indicator
 *                is no longer requested at all.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     EventStatus
 *                Current event status of the event
 *
 * \return        Modified event status based on the status passed
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_Event_Healed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  EventStatus
  );

/* ****************************************************************************
 * Dem_Event_Failed
 *****************************************************************************/
/*!
 * \brief         Process the event's queued qualified failed result
 *
 * \details       This function processes a failed result stored on the
 *                event queue.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Event_Failed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_OpCycle
 *****************************************************************************/
/*!
 * \brief         Updates an event's state due to operation cycle change
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: CycleStatus - encoding of cycle modification
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Event_OpCycle(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );

/* ****************************************************************************
 * Dem_Event_ResetTestFailed
 *****************************************************************************/
/*!
 * \brief         Resets the 'TestFailed' bit
 *
 * \details       Resets the 'TestFailed' bit
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_ResetTestFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF)
/* ****************************************************************************
 * Dem_Event_Aged
 *****************************************************************************/
/*!
 * \brief         Updates an event due to aging
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: none
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Aged(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );
#endif

/* ****************************************************************************
 * Dem_Event_Cleared
 *****************************************************************************/
/*!
 * \brief         Clears an event's state in volatile RAM
 *
 * \details       Clears an event's state in volatile RAM
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: none
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Cleared(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF) \
 && (DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON)
/* ****************************************************************************
 * Dem_Event_Displaced
 *****************************************************************************/
/*!
 * \brief         Updates an event's status due to displacement
 *
 * \details       Do not call this function directly, it is part of
 *                Dem_DTC_Displaced
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: none
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_OFF 
 *             && DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Displaced(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );
#endif

#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/* ****************************************************************************
 * Dem_Event_Displaced_Vcc
 *****************************************************************************/
/*!
 * \brief         Updates an event's status due to displacement
 *
 * \details       Do not call this function directly, it is part of
 *                Dem_DTC_Displaced_Vcc
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: SI30 - Status Indicator byte
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Displaced_Vcc(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );
#endif

/* ****************************************************************************
 * Dem_Event_GetEventUDSStatus
 *****************************************************************************/
/*!
 * \brief         Gets the current event status
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    EventUDSStatus
 *                Pointer receiving the event Uds status
 *
 * \return        E_OK
 *                EventUDSStatus now contains the event status
 *
 * \return        E_NOT_OK
 *                The request was rejected due to variant coding
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_GetEventUDSStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA)  EventUDSStatus
  );

/* ****************************************************************************
 * Dem_Event_GetEventFailed
 *****************************************************************************/
/*!
 * \brief         Gets Bit0 (TestFailed) of the current event status
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    EventFailed
 *                Pointer receiving Bit0
 *
 * \return        E_OK
 *                EventFailed now contains Bit0
 *
 * \return        E_NOT_OK
 *                The request was rejected due to variant coding
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_GetEventFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventFailed
  );

/* ****************************************************************************
 * Dem_Event_GetEventTested
 *****************************************************************************/
/*!
 * \brief         Gets Bit6 (TestNotCompletedThisOperationCycle) of the current event status
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    EventTested
 *                Pointer receiving Bit6
 *
 * \return        E_OK
 *                EventTested now contains Bit6
 *
 * \return        E_NOT_OK
 *                The request was rejected due to variant coding
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Event_GetEventTested(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventTested
  );

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_Event_CycleQualifyDcy
 *****************************************************************************/
/*!
 * \brief         Updates an event's state due to dcy qualification
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in,out] ArgPtr
 *                Arguments: none
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_Event_CycleQualifyDcy(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );
#endif

/* ****************************************************************************
 * Dem_Event_TestLatchedTestFailed
 *****************************************************************************/
/*!
 * \brief         Tests whether an event's latched failed restriction applies
 *
 * \details       -
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The event is latched at TestFailed
 * \return        FALSE
 *                The event is not latched, process it normally
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Event_TestLatchedTestFailed(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_InitNvData
 *****************************************************************************/
/*!
 * \brief         Initializes the event status processing sub-component
 *
 * \details       Initializes the event status processing sub-component
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_InitNvData(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Event_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the event status processing sub-component
 *
 * \details       Initializes the event status processing sub-component
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_Init(
  void
  );

/* ****************************************************************************
 * Dem_Event_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-Initializes the Dem events
 *
 * \details       Pre-Initializes the Dem events
 *
 * \pre           May be called only during module pre-initialization
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_PreInit(
  void
  );

/* ****************************************************************************
 * Dem_Event_MainFunction
 *****************************************************************************/
/*!
 * \brief         Process queued event availability changes
 *
 * \details       Process queued event availability changes
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_Event_SetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Stored the event's aging counter inside the dedicated aging
 *                counter array.
 *
 * \details       Stored the event's aging counter inside the dedicated aging
 *                counter array.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \param[in]     AgingCounter
 *                The aging counter to be stored.
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Event_SetAgingCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint16, AUTOMATIC) AgingCounter
  );

/* ****************************************************************************
 * Dem_Event_GetAgingCounter
 *****************************************************************************/
/*!
 * \brief         Retrieve the event's aging counter stored in the dedicated 
 *                aging counter array.
 *
 * \details       Retrieve the event's aging counter stored in the dedicated 
 *                aging counter array.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The aging counter of the event.
 *
 * \pre           -
 *
 * \context       TASK/ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Event_GetAgingCounter(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
* Dem_Event_TestHighPriorReadinessGroup
*****************************************************************************/
/*!
* \brief         Test if EventId belongs to a high prior readiness group
*
* \details       Test if EventId belongs to readiness group misfire or fuel system
*
* \param[in]     EventId
*                Unique handle of the Event.
*                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
*
* \return        TRUE
*                Major monitors are supported and readiness group of event is
*                FLSYS_NONCONT, FLSYS or MISF
* \return        FALSE
*                Major monitors are not supported or readiness group of event is
*                other than FLSYS_NONCONT, FLSYS or MISF
*
* \pre           -
*
* \context       TASK
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL FUNC(boolean, DEM_CODE)
Dem_Event_TestHighPriorReadinessGroup(                                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
CONST(Dem_EventIdType, AUTOMATIC)  EventId
);
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_EVENT_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Event_Interface.h
 *********************************************************************************************************************/
