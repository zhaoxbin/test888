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
/*! \ingroup    Dem_Event
 *  \defgroup   Dem_EventInternalStatus EventInternal Status
 *  \{
 *  \file       Dem_EventInternalStatus_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the EventInternalStatus subcomponent
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

#if !defined (DEM_EVENTINTERNALSTATUS_INTERFACE_H)
#define DEM_EVENTINTERNALSTATUS_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_EventInternalStatus_Types.h"
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

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_EventInternalStatus_Properties Properties
 * \{
 */

/* Internal status bit 'event suppressed' ---------------------------------- */

/* ****************************************************************************
 * Dem_EventInternalStatus_TestAvailabilityChanged
 *****************************************************************************/
/*!
 * \brief         Test if event availability changed is set in the internal status
 *
 * \details       Test if event availability changed is set in the internal status
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestAvailabilityChanged(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* ****************************************************************************
 * Dem_EventInternalStatus_SetAvailabilityChanged
 *****************************************************************************/
/*!
 * \brief         Set event availability changed in the internal status.
 *
 * \details       Set event availability changed in the internal status.
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetAvailabilityChanged(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* ****************************************************************************
 * Dem_EventInternalStatus_ResetAvailabilityChanged
 *****************************************************************************/
/*!
 * \brief         Reset event availability changed in the internal status
 *
 * \details       Reset event availability changed in the internal status.
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag reset.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetAvailabilityChanged(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* Internal status bit 'event available' ----------------------------------- */

/* ****************************************************************************
 * Dem_EventInternalStatus_TestEventDisconnected
 *****************************************************************************/
/*!
 * \brief         Test if event disconnected is set in the internal status
 *
 * \details       Test if event disconnected is set in the internal status
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* ****************************************************************************
 * Dem_EventInternalStatus_SetEventDisconnected
 *****************************************************************************/
/*!
 * \brief         Set event disconnected in the internal status
 *
 * \details       Set event disconnected in the internal status. Only has an
 *                effect if event availability is supported
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) || (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_ResetEventDisconnected
 *****************************************************************************/
/*!
 * \brief         Reset event disconnected in the internal status
 *
 * \details       Reset event disconnected in the internal status. Only has an
 *                effect if event availability is supported
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag reset.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *             || DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );
#endif

/* Internal status bit 'DTC disabled by PB selectable' --------------------- */

/* ****************************************************************************
 * Dem_EventInternalStatus_TestAvailableInVariant
 *****************************************************************************/
/*!
 * \brief         Test if event available in variant is set in the internal status
 *
 * \details       Test if event available in variant is set in the internal status
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestAvailableInVariant(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_SetAvailableInVariant
 *****************************************************************************/
/*!
 * \brief         Set event available in variant in the internal status
 *
 * \details       Set event available in variant in the internal status
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag set.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetAvailableInVariant(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_TestSimilarConditions
 *****************************************************************************/
/*!
 * \brief         Test if similar conditions is set in the internal status
 *
 * \details       Test if similar conditions is set in the internal status
 *
 * \param[in]     ExtendedStatus
 *                Extended status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
);
#endif

#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
/* ****************************************************************************
* Dem_EventInternalStatus_SetSimilarConditions
*****************************************************************************/
/*!
 * \brief         Set similar conditions in the extended status
 *
 * \details       Set similar conditions in the extended status
 *
 * \param[in]     ExtendedStatus
 *                Extended status byte
 *
 * \return        Extended status with similar condition flag set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_EventInternalStatus_SetSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
);
#endif

/* ****************************************************************************
* Dem_EventInternalStatus_ResetSimilarConditions
*****************************************************************************/
/*!
 * \brief         Reset similar conditions in the extended status
 *
 * \details       Reset similar conditions in the extended status
 *
 * \param[in]     ExtendedStatus
 *                Extended status byte
 *
 * \return        Extended status with similar condition flag reset
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
);

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_GetMilGroupTripCountRaw
 *****************************************************************************/
/*!
 * \brief         Get the trip count of the MIL group
 *
 * \details       Get the trip count of the MIL group. There is additional
 *                information encoded in the value, so it cannot be used
 *                directly
 *
 * \param[in]     MilGroupIndex
 *                Unique handle of the MIL group
 *
 * \return        Trip count of the MIL group (raw)
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_MIL_GROUPS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EventInternalStatus_GetMilGroupTripCountRaw(
  CONST(uint16, AUTOMATIC)  MilGroupIndex
  );
#endif

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_SetMilGroupTripCount
 *****************************************************************************/
/*!
 * \brief         Set the trip count of the MIL group
 *
 * \details       Set the trip count of the MIL group.
 *
 * \param[in]     MilGroupIndex
 *                Unique handle of the MIL group
 * \param[in]     TripCount
 *                New trip count
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_MIL_GROUPS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventInternalStatus_SetMilGroupTripCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex,
  CONST(uint8, AUTOMATIC)  TripCount
  );
#endif

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_GetMilGroupPendingCount
 *****************************************************************************/
/*!
 * \brief         Get the number of pending events of the MIL group
 *
 * \details       Get the number of pending events of the MIL group
 *
 * \param[in]     MilGroupIndex
 *                Unique handle of the MIL group
 *
 * \return        The number of pending events of the MIL group
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_MIL_GROUPS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EventInternalStatus_GetMilGroupPendingCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_SetMilGroupPendingCount
 *****************************************************************************/
/*!
 * \brief         Set the number of pending events of the MIL group
 *
 * \details       Set the number of pending events of the MIL group
 *
 * \param[in]     MilGroupIndex
 *                Unique handle of the MIL group
 * \param[in]     PendingCount
 *                New number of pending events of the MIL group
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_MIL_GROUPS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventInternalStatus_SetMilGroupPendingCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex,
  CONST(uint16, AUTOMATIC)  PendingCount
  );                                                                                                                   /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

/* Qualify status bit 'confirmedDTC' --------------------------------------- */
#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_Test_QualifyStatus_CDTC
 *****************************************************************************/
/*!
 * \brief         Test Confirmed DTC qualified state of event qualification status
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current qualify status of the event
 *
 * \return        TRUE
 *                The CDTC bit is qualified
 * \return        FALSE
 *                The CDTC bit is not qualified
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_Test_QualifyStatus_CDTC(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_Set_QualifyStatus_CDTC
 *****************************************************************************/
/*!
 * \brief         Set Confirmed DTC qualified state of event qualification status.
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current event qualify status
 *
 * \return        Event qualify status with flag set for CDTC.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
  Dem_EventInternalStatus_Set_QualifyStatus_CDTC(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_Reset_QualifyStatus_CDTC
 *****************************************************************************/
/*!
 * \brief         Reset Confirmed DTC qualified state of event qualification status.
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current event qualify status
 *
 * \return        Event qualify status with flag reset for CDTC.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Reset_QualifyStatus_CDTC(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );
#endif

/* Qualify status bit 'warningIndicatorRequested' -------------------------- */
#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_Test_QualifyStatus_WIR
 *****************************************************************************/
/*!
 * \brief         Test Warning Indicator Requested qualified state 
 *                of event qualification status
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current qualify status of the event
 *
 * \return        TRUE
 *                The WIR bit is qualified
 * \return        FALSE
 *                The WIR bit is not qualified
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_Test_QualifyStatus_WIR(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_Set_QualifyStatus_WIR
 *****************************************************************************/
/*!
 * \brief         Set Warning Indicator Requested qualified state 
 *                of event qualification status.
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current event qualify status
 *
 * \return        Event qualify status with flag set for WIR.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Set_QualifyStatus_WIR(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_EventInternalStatus_Reset_QualifyStatus_WIR
 *****************************************************************************/
/*!
 * \brief         Reset Warning Indicator Requested qualified state 
 *                of event qualification status.
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current event qualify status
 *
 * \return        Event qualify status with flag reset for WIR.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Reset_QualifyStatus_WIR(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
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
 * \defgroup Dem_EventInternalStatus_Private Private Methods
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
 * \defgroup Dem_EventInternalStatus_Public Public Methods
 * \{
 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_EVENTINTERNALSTATUS_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EventInternalStatus_Interface.h
 *********************************************************************************************************************/
