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
 *  \defgroup   Dem_Indicator Indicator
 *  \{
 *  \file       Dem_Indicator_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Manages the User and Special indicator states
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

#if !defined (DEM_INDICATOR_INTERFACE_H)
#define DEM_INDICATOR_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Indicator_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Indicator_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Indicator_TestHasIndicator
 *****************************************************************************/
/*!
 * \brief         Test, if the event has configured any indicator.
 *
 * \details       Test, if the event has configured any indicator.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \return        TRUE
 *                The event has configured a user- or a special indicator.
 * \return        FALSE
 *                The event has no indicators configured.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Indicator_TestHasIndicator(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_GetQualifiedActiveEventCount
 *****************************************************************************/
/*!
 * \brief         Get the number of qualified active and failed events for the
 *                WWH-OBD DTC class
 *
 * \details       Get the number of qualified active and failed events for the
 *                WWH-OBD DTC class
 *
 * \param[in]     WwhObdDtcClass
 *                Unique handle of the WWH-OBD DTC class
 *
 * \return        The number of qualified active and failed events
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Indicator_GetQualifiedActiveEventCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_SetQualifiedActiveEventCount
 *****************************************************************************/
/*!
 * \brief         Set the number of qualified active and failed events for the
 *                WWH-OBD DTC class
 *
 * \details       Set the number of qualified active and failed events for the
 *                WWH-OBD DTC class
 *
 * \param[in]     WwhObdDtcClass
 *                Unique handle of the WWH-OBD DTC class
 * \param[in]     QualifiedActiveEventCount
 *                The new number of qualified active and failed events
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetQualifiedActiveEventCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass,
  CONST(Dem_EventIdType, AUTOMATIC)  QualifiedActiveEventCount
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_GetDtcClassMILCount
 *****************************************************************************/
/*!
 * \brief         Get the number of MIL requests for the WWHO-OBD DTC class
 *
 * \details       Get the number of MIL requests for the WWHO-OBD DTC class
 *
 * \param[in]     WwhObdDtcClass
 *                Unique handle of the WWH-OBD DTC class
 *
 * \return        The number of MIL requests
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Indicator_GetDtcClassMILCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass
  );
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_SetDtcClassMILCount
 *****************************************************************************/
/*!
 * \brief         Set the number of MIL requests for the WWH-OBD DTC class
 *
 * \details       Set the number of MIL requests for the WWH-OBD DTC class
 *
 * \param[in]     WwhObdDtcClass
 *                Unique handle of the WWH-OBD DTC class
 * \param[in]     DtcClassMILCount
 *                The new number of MIL requests
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetDtcClassMILCount(
  CONST(uint8, AUTOMATIC)  WwhObdDtcClass,
  CONST(Dem_EventIdType, AUTOMATIC)  DtcClassMILCount
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
 * \defgroup Dem_Indicator_Private Private Methods
 * \{
 */


/* ****************************************************************************
 * Dem_Indicator_SetGlobalIndicatorState
 *****************************************************************************/
/*!
 * \brief         Sets the global indicator state.
 *
 * \details       Sets the global indicator state.
 *
 * \param[in]     IndicatorId
 *                Unique handle of the indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the NmNode
 * \param[in]     IndicatorState
 *                Indicator state to set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetGlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint8, AUTOMATIC)  IndicatorState
  );

/* ****************************************************************************
 * Dem_Indicator_GetGlobalIndicatorState
 *****************************************************************************/
/*!
 * \brief         Gets the global indicator state.
 *
 * \details       Gets the global indicator state.
 *
 * \param[in]     IndicatorId
 *                Unique handle of the indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the NmNode
 *
 * \return        The indicator state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_GetGlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  );

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_J1939PriorityOfIndicatorState
 *****************************************************************************/
/*!
 * \brief         Gets the priority of an indicator state.
 *
 * \details       Gets the priority of an indicator state.
 *
 * \param[in]     ConfigIndicatorState
 *                The state of a J1939 related indicator.
 *
 * \return        The priority value associated with the indicator state
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939PriorityOfIndicatorState(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  );
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_J1939IndicatorStateFromPriority
 *****************************************************************************/
/*!
 * \brief         Gets the indicator state from a priority value.
 *
 * \details       Gets the indicator state from a priority value.
 *
 * \param[in]     Priority
 *                The priority of a J1939 indicator state
 *
 * \return        The indicator state associated with the priority value
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939IndicatorStateFromPriority(
  CONST(uint8, AUTOMATIC)  Priority
  );
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_J1939GlobalIndicatorState
 *****************************************************************************/
/*!
 * \brief         Gets the accumulated global indicator state over all nodes
 *
 * \details       Gets the accumulated global indicator state over all nodes
 *
 * \param[in]     IndicatorId
 *                Unique handle of the indicator
 *
 * \return        Current indicator state of the indicator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939GlobalIndicatorState(
  CONST(uint8, AUTOMATIC)  IndicatorId
  );
#endif

#if (DEM_CFG_SUPPORT_PID21 == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_GlobalMilStateDisable
 *****************************************************************************/
/*!
 * \brief         Hook function called when the MIL is deactivated
 *
 * \details       The Mil status has changed from On to Off, the current
 *                Odometer value (relative) may be reset
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PID21 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_GlobalMilStateDisable(
  void
  );
#endif

/* ****************************************************************************
 * Dem_Indicator_GetEventCountContinuous
 *****************************************************************************/
/*!
 * \brief         Get the number of events requesting the indicator in continuous
 *                mode, relative to the J1939 node
 *
 * \details       Get the number of events requesting the indicator in continuous
 *                mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 *
 * \return        The number of events requesting the indicator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountContinuous(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  );

/* ****************************************************************************
 * Dem_Indicator_SetEventCountContinuous
 *****************************************************************************/
/*!
 * \brief         Set the number of events requesting the indicator in continuous
 *                mode, relative to the J1939 node
 *
 * \details       Set the number of events requesting the indicator in continuous
 *                mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 * \param[in]     ActiveEventCount
 *                New number of events
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountContinuous(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint16, AUTOMATIC)  ActiveEventCount
  );

/* ****************************************************************************
 * Dem_Indicator_GetEventCountBlinking
 *****************************************************************************/
/*!
 * \brief         Get the number of events requesting the indicator in blinking
 *                mode, relative to the J1939 node
 *
 * \details       Get the number of events requesting the indicator in blinking
 *                mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 *
 * \return        The number of events requesting the indicator
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountBlinking(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  );

/* ****************************************************************************
 * Dem_Indicator_SetEventCountBlinking
 *****************************************************************************/
/*!
 * \brief         Set the number of events requesting the indicator in blinking
 *                mode, relative to the J1939 node
 *
 * \details       Set the number of events requesting the indicator in blinking
 *                mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 * \param[in]     ActiveEventCount
 *                New number of events
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountBlinking(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint16, AUTOMATIC)  ActiveEventCount
  );

/* ****************************************************************************
 * Dem_Indicator_GetEventCountFastFlash
 *****************************************************************************/
/*!
 * \brief         Get the number of events requesting the indicator in 'fast
 *                flash' mode, relative to the J1939 node
 *
 * \details       Get the number of events requesting the indicator in 'fast
 *                flash' mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 *
 * \return        The number of events requesting the indicator in 'fast flash'
 *                mode
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountFastFlash(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  );

/* ****************************************************************************
 * Dem_Indicator_SetEventCountFastFlash
 *****************************************************************************/
/*!
 * \brief         Set the number of events requesting the indicator in 'fast
 *                flash' mode, relative to the J1939 node
 *
 * \details       Set the number of events requesting the indicator in 'fast
 *                flash' mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 * \param[in]     ActiveEventCount
 *                New number of events requesting the indicator in 'fast flash'
 *                mode
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountFastFlash(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint16, AUTOMATIC)  ActiveEventCount
  );

/* ****************************************************************************
 * Dem_Indicator_GetEventCountSlowFlash
 *****************************************************************************/
/*!
 * \brief         Get the number of events requesting the indicator in 'slow
 *                flash' mode, relative to the J1939 node
 *
 * \details       Get the number of events requesting the indicator in 'slow
 *                flash' mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 *
 * \return        The number of events requesting the indicator in 'slow flash'
 *                mode
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_Indicator_GetEventCountSlowFlash(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex
  );

/* ****************************************************************************
 * Dem_Indicator_SetEventCountSlowFlash
 *****************************************************************************/
/*!
 * \brief         Set the number of events requesting the indicator in 'slow
 *                flash' mode, relative to the J1939 node
 *
 * \details       Set the number of events requesting the indicator in 'slow
 *                flash' mode, relative to the J1939 node
 *
 * \param[in]     IndicatorId
 *                Unique handle of indicator
 * \param[in]     NmNodeIndex
 *                Unique handle of the J1939 node
 * \param[in]     ActiveEventCount
 *                New number of events requesting the indicator in 'slow flash'
 *                mode
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_SetEventCountSlowFlash(
  CONST(uint8, AUTOMATIC)  IndicatorId,
  CONST(uint8, AUTOMATIC)  NmNodeIndex,
  CONST(uint16, AUTOMATIC)  ActiveEventCount
  );

#if (((DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)) \
    && (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON))
/* ****************************************************************************
 * Dem_Indicator_J1939LampStatus
 *****************************************************************************/
/*!
 * \brief         Maps indicator behavior to J1939 lamp status
 *
 * \details       This function maps the internal indicator behavior to the
 *                external lamp status bit mask used by J1939.
 *
 *                The J1939 representation is not bit-shifted for a specific
 *                indicator. To use the returned value in DM messages the
 *                caller needs to shift the result to the correct position
 *                first.
 *
 *                The state map only includes states used by J1939 indicators,
 *                other indicators states will not work with this function.
 *
 * \param[in]     ConfigIndicatorState
 *                The state of a J1939 related indicator.
 *
 * \return        J1939 lamp status of the passed indicator state.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON ||
 *                 DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) 
 *                && DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939LampStatus(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  );
#endif

#if (((DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)) \
    && (DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON))
/* ****************************************************************************
 * Dem_Indicator_J1939FlashLampStatus
 *****************************************************************************/
/*!
 * \brief         Maps indicator behavior to J1939 flash lamp status
 *
 * \details       This function maps the internal indicator behavior to the
 *                external flash lamp bit mask used by J1939.
 *
 *                The J1939 representation is not bit-shifted for a specific
 *                indicator. To use the returned value in DM messages the
 *                caller needs to shift the result to the correct position
 *                first.
 *
 *                The state map only includes states used by J1939 indicators,
 *                other indicators states will not work with this function.
 *
 * \param[in]     ConfigIndicatorState
 *                The state of a J1939 related indicator.
 *
 * \return        J1939 flash amp status of the passed indicator state.
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON ||
 *                 DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) 
 *                && DEM_FEATURE_NEED_SPECIAL_INDICATORS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_J1939FlashLampStatus(
  CONST(uint8, AUTOMATIC)  ConfigIndicatorState
  );
#endif

/* ****************************************************************************
 * Dem_Indicator_UpdateGlobalUserIndicatorStates
 *****************************************************************************/
/*!
 * \brief         Update the global indicator state of a user defined indicator
 *
 * \details       Update the global indicator state of a user defined indicator
 *
 * \param[in]     IndicatorId
 *                Unique handle of the user defined indicator
 *
 * \pre           IndicatorId must be a user defined indicator
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateGlobalUserIndicatorStates(
  CONST(uint8, AUTOMATIC)  IndicatorId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

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
 * \defgroup Dem_Indicator_Public Public Methods
 * \{
 */

#if (DEM_FEATURE_NEED_REPORTED_MIL_STATE == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_TestMilReportedActive
 *****************************************************************************/
/*!
 * \brief         Returns if the MIL is considered as active.
 *
 * \details       The MIL is always considered as active (for reporting in 
 *                PID 0x01, PID 0x21 and PID 0x4D), if it is continuous (or 
 *                continuous blinking). 
 *                In configurations with 'Report Blinking Mil As Active' 
 *                enabled, the Mil is also considered as active, if it is only
 *                blinking. 
 *
 * \return        TRUE
 *                The MIL is considered as active.
 * \return        FALSE
 *                The MIL is not considered as active
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_REPORTED_MIL_STATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Indicator_TestMilReportedActive(
  void
  );
#endif

#if (DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_UpdatePIDsMilEnabled
 *****************************************************************************/
/*!
 * \brief         Hook function called when the MIL is activated
 *
 * \details       If the Mil status has changed from Off to On the current
 *                Odometer value (absolute) is set as base value and the
 *                Engine Run Time is set to 0
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_GLOBAL_MIL_STATE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdatePIDsMilEnabled(
  void
  );
#endif

/* ****************************************************************************
 * Dem_Indicator_UserIndicatorEnable
 *****************************************************************************/
/*!
 * \brief         Updates user-defined indicator counters
 *
 * \details       Adds the event's contribution to the indicator states.
 *                Basically this adds 1 to each indicators continuous or
 *                blinking count, if the indicator is enabled by the given
 *                event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UserIndicatorEnable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Indicator_SpecialIndicatorEnable
 *****************************************************************************/
/*!
 * \brief         Updates special indicator counters
 *
 * \details       Add the event's contribution to the indicator states.
 *                Basically this adds 1 from each indicators continuous,
 *                blinking, fast flash or slow flash count, if the indicator
 *                is enabled by the given event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The handle of a modified special handled indicator, otherwise
 *                DEM_CFG_SPECIAL_INDICATOR_NONE
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_SpecialIndicatorEnable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Indicator_UserIndicatorDisable
 *****************************************************************************/
/*!
 * \brief         Update user-defined indicator counters
 *
 * \details       Removes the event's contribution to the indicator states.
 *                Basically this subtracts 1 from each indicators continuous or
 *                blinking count, if the indicator is enabled by the given
 *                event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UserIndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Indicator_SpecialIndicatorDisable
 *****************************************************************************/
/*!
 * \brief         Updates special indicator counters
 *
 * \details       Removes the event's contribution to the indicator states.
 *                Basically this subtracts 1 from each indicators continuous or
 *                blinking count, if the indicator is enabled by the given
 *                event.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        The handle of a modified special handled indicator, otherwise
 *                DEM_CFG_SPECIAL_INDICATOR_NONE
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Indicator_SpecialIndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 ! Dem_Indicator_GlobalIndicatorActivationMode
 *****************************************************************************/
/*!
 * \brief         Gets the current Activation Mode.
 *
 * \details       Gets the current Activation Mode.
 *
 * \return        The current activation mode
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_IndicatorStatusType, DEM_CODE)
Dem_Indicator_GlobalIndicatorActivationMode(
  void
  );
#endif

/* ****************************************************************************
 * Dem_Indicator_IndicatorDisable
 *****************************************************************************/
/*!
 * \brief         Decrement indicator counters and update global indicator states
 *
 * \details       Update user indicators and special indicator
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_IndicatorDisable(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Indicator_IndicatorEnable
 *****************************************************************************/
/*!
 * \brief         Increment indicator counters and update global indicator states
 *
 * \details       Update user indicators and special indicator
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_IndicatorEnable(
CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
);

/* ****************************************************************************
 * Dem_Indicator_InitWwhObdStatistics
 *****************************************************************************/
/*!
 * \brief         Initializes the WWHOBD Dtc class related statistics
 *
 * \details       Initializes the WWHOBD Dtc class related statistics
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_InitWwhObdStatistics(
  void
  );

/* ****************************************************************************
 * Dem_Indicator_InitSpecialIndicator
 *****************************************************************************/
/*!
 * \brief         Initializes the OBD and J1939 special indicator
 *
 * \details       Initializes the OBD and J1939 special indicator
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_InitSpecialIndicator(
  void
  );

/* ****************************************************************************
 * Dem_Indicator_InitUserIndicator
 *****************************************************************************/
/*!
 * \brief         Initializes user indicators
 *
 * \details       Initializes user indicators
 *
 * \pre           May be called only during module initialization
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_InitUserIndicator(
  void
  );


/* ****************************************************************************
 * Dem_Indicator_GetIndicatorStatus
 *****************************************************************************/
/*!
 * \brief         Gets the current indicator status
 *
 * \details       Gets the current indicator status
 *
 * \param[in]     IndicatorId
 *                Unique identifier of the indicator
 *
 * \return        The current indicator status
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_IndicatorStatusType, DEM_CODE)
Dem_Indicator_GetIndicatorStatus(
  CONST(uint8, AUTOMATIC)  IndicatorId
  );

/* ****************************************************************************
 * Dem_Indicator_UpdateGlobalSpecialIndicatorStates
 *****************************************************************************/
/*!
 * \brief         Update the global indicator state of a special indicator
 *
 * \details       This function updates the global states of one of the special
 *                indicators red stop lamp, amber warning lamp, malfunction
 *                indicator lamp and the protect lamp.
 *
 * \param[in]     IndicatorId
 *                Unique handle of the special indicator
 *
 * \pre           IndicatorId must be a special indicator
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateGlobalSpecialIndicatorStates(
  CONST(uint8, AUTOMATIC)  IndicatorId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Indicator_UpdateGlobalUserIndicatorForEvent
 *****************************************************************************/
/*!
 * \brief         Updates all global user indicators for an event
 *
 * \details       Updates all global user indicators for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_UpdateGlobalUserIndicatorForEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */


/* ****************************************************************************
 * Dem_Indicator_Init
 *****************************************************************************/
/*!
 * \brief         Initialize indicators.
 *
 * \details       If indicators are configured, initialize all indicator state counters.
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Indicator_Init(void);


#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_CalculateGlobalJ1939LampStatus
 *****************************************************************************/
/*!
 * \brief         Calculate the node specific J1939 lamp status and return it.
 *
 * \details       Calculate the node specific J1939 lamp status based on red stop lamp,
 *                amber warning lamp, malfunction indicator lamp and the protect lamp.
 *
 * \param[in]     NodeId
 *                The node Id.
 * \return        The node specific J1939 lamp status.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_J1939DcmLampStatusType, DEM_CODE)
Dem_Indicator_CalculateGlobalJ1939LampStatus(
  CONST(uint8, AUTOMATIC)  NodeId
);
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_Indicator_CalculateEventJ1939LampStatus
 *****************************************************************************/
/*!
 * \brief         Calculate the event specific J1939 lamp status.
 *
 * \details       Calculate the event specific J1939 lamp status if the event 
 *                is configured for the requested NodeId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 * \param[in]     NodeId
 *                The node Id.
 * \param[out]    FilterResult
 *                Pointer to receive the next matching event.
 *                FilterResult->LampStatus : 
 *                              The lamp status of the matching event.
 *                Ignore other member of FilterResult
 *
 * \return        E_OK
 *                Event is configured for the requested node identifier.
 *                DEM_NO_SUCH_ELEMENT
 *                Event is not configured for the requested node identifier.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939_DM31 == STD_ON or
 *                DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_Indicator_CalculateEventJ1939LampStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
);
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_INDICATOR_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Indicator_Interface.h
 *********************************************************************************************************************/
