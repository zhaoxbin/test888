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
/*! \ingroup    Dem_Shared
 *  \defgroup   Dem_API API
 *  \{
 *  \file       Dem_API_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of API subcomponent
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

#if !defined (DEM_API_INTERFACE_H)
#define DEM_API_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_API_Types.h"
#include "Dem_Satellite_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_API_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_MasterMainFunctionTimer
 *****************************************************************************/
/*!
 * \brief         Cyclic DemMaster timer task.
 *
 * \details       This function creates the time base for the DemMaster module.
 *
 *                Call this function in a cyclic manner, with the configured
 *                cycle time. The run-time of this function is as minimal as
 *                possible, so it can be called on a higher priority task with
 *                minimal impact.
 *
 * \pre           DemMaster has been pre-initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MasterMainFunctionTimer(
  void
  );

/* ****************************************************************************
 * Dem_MasterMainFunctionWorker
 *****************************************************************************/
/*!
 * \brief         Cyclic DemMaster worker task.
 *
 * \details       This function processes the asynchronous status changes, e.g.
 *                storing event data into the event memory, clearing the event
 *                memory and processing operation cycle changes.
 *
 *                The run-time of this function can be high depending on the
 *                configuration, and the API calls that happen to coincide.
 *
 * \pre           DemMaster has been pre-initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MasterMainFunctionWorker(
  void
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
 * \defgroup Dem_API_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_SatellitePreInit
 *****************************************************************************/
/*!
 * \brief         Initializes DemSatellite basic functionality.
 *
 * \details       This function performs the first half of initialization.
 *                After calling this function, the Dem enters a pre-initialized
 *                state in which basic functionality is available.
 *                From now on Dem_SetEventStatus is supported to allow reporting
 *                results by BSW modules for events assigned to this satellite
 *                during the initialization phase.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \pre           The DemMaster must have been pre-initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_SatellitePreInit(
  Dem_SatelliteInfoType SatelliteId
  );

/* ****************************************************************************
 * Dem_MasterPreInit
 *****************************************************************************/
/*!
 * \brief         Initializes DemMaster basic functionality.
 *
 * \details       Initializes DemMaster basic functionality.
 *
 *                In multiple configuration use-cases (Post-Build Selectable),
 *                initialization has to provide a preliminary configuration.
 *                This preliminary configuration may be replaced during the
 *                final configuration in Dem_Init()
 *
 * \param[in]     ConfigPtr
 *                A pointer to the configuration data.
 *
 *                In multiple configuration use cases, a valid configuration
 *                must be provided here.
 *
 *                NULL_PTR is valid in the PRE-COMPILE configuration variant.
 *
 * \pre           The Dem may not have been initialized yet. Call this API first.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MasterPreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );

/* ****************************************************************************
 * Dem_PreInit
 *****************************************************************************/
/*!
 * \brief         Initializes basic functionality of DemMaster and DemSatellites.
 *
 * \details       This function performs the first half of initialization.
 *                After calling this function, the Dem enters a pre-initialized
 *                state in which basic functionality is available.
 *                Dem_SetEventStatus is supported to allow reporting results
 *                by BSW modules during the initialization phase.
 *
 *                In multiple configuration use-cases (Post-Build Selectable),
 *                initialization has to provide a preliminary configuration.
 *                This preliminary configuration may be replaced during the
 *                final configuration in Dem_Init().
 *
 *                This function pre-initializes both the DemMaster and the
 *                DemSatellite.
 *
 * \param[in]     ConfigPtr
 *                A pointer to the configuration data.
 *
 *                In multiple configuration use cases, a valid configuration
 *                must be provided here.
 *
 *                NULL_PTR is valid in the PRE-COMPILE configuration variant.
 *
 * \pre           This API can be used only in configurations with a single
 *                DemSatellite.
 * \pre           The Dem may not have been initialized yet. Call this prior to
 *                Dem_Init().
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_PreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );

/* ****************************************************************************
 * Dem_SatelliteInit
 *****************************************************************************/
/*!
 * \brief         Initializes functionality beyond the basic set.
 *
 * \details       This function initializes the local Dem Satellite variables
 *                required to provide the Dem services not already available
 *                Dem_PreInit().
 *
 *                During this initialization, the non-volatile data content
 *                is accessed to initialize derived state.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \pre           The respective DemSatellite has been pre-initialized.
 * \pre           NvM has restored all non-volatile data used by the Dem.
 * \pre           DemMaster has been initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_SatelliteInit(
    Dem_SatelliteInfoType  SatelliteId
  );

/* ****************************************************************************
 * Dem_MasterInit
 *****************************************************************************/
/*!
 * \brief         Initialize the DemMaster.
 *
 * \details       This function initializes the Dem variables required to
 *                provide the Dem services processed on the DemMaster.
 *
 *                During this initialization, the non-volatile data content
 *                is validated and the Dem assumes ownership of the respective
 *                RAM areas.
 *
 *                Depending on configuration, some event status changes trigger
 *                automatically from this initialization. These will not cause
 *                notification callbacks.
 *
 * \param[in]     ConfigPtr
 *                A pointer to the final configuration data.
 *                Pass NULL_PTR to keep the configuration data passed to
 *                Dem_PreInit().
 *
 * \pre           All DemSatellites have been pre-initialized.
 * \pre           NvM has restored all non-volatile data used by the Dem.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MasterInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );


/* ****************************************************************************
 * Dem_Init
 *****************************************************************************/
/*!
 * \brief         Initialize the DemMaster and DemSatellite.
 *
 * \details       This function initializes the local Dem Satellite variables
 *                required to provide the Dem services not already available
 *                Dem_PreInit(), and to provide the Dem services processed on
 *                the DemMaster.
 *
 *                During this initialization, the non-volatile data content
 *                is validated and the Dem assumes ownership of the respective
 *                RAM areas.
 *
 *                Depending on configuration, some event status changes trigger
 *                automatically from this initialization. These will not cause
 *                notification callbacks.
 *
 * \param[in]     ConfigPtr
 *                A pointer to the final configuration data.
 *                Pass NULL_PTR to keep the configuration data passed to
 *                Dem_PreInit().
 *
 * \pre           This API can be used only in configurations with a single
 *                DemSatellite.
 * \pre           NvM has restored all non-volatile data used by the Dem.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_Init(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_INIT_DATA)  ConfigPtr
  );

/* ****************************************************************************
 * Dem_Shutdown
 *****************************************************************************/
/*!
 * \brief         Shut down the Dem functionality.
 *
 * \details       When this function is called, the Dem will return into the
 *                basic initialization mode. This means
 *                Dem_ReportErrorStatus() is still available, but most other
 *                functions are not.
 *
 *                The Dem will mark modified non-volatile data structures,
 *                expecting NvN_WriteAll() following the shutdown. The Dem
 *                will no longer modify the RAM mirror areas configured for
 *                NV synchronization.
 *
 * \pre           Dem_PostRunRequested() returns FALSE.
 *
 * \context       TASK, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_Shutdown(
  void
  );

/* ****************************************************************************
 * Dem_MasterMainFunction
 *****************************************************************************/
/*!
 * \brief         Wrapper to call both timer and worker task.
 *
 * \details       Wrapper to call both timer and worker task.
 *
 * \pre           DemMaster has been pre-initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MasterMainFunction(                                                                                                          /* PRQA S 3451 */ /* MD_DEM_8.8_schm */
  void
  );

/* ****************************************************************************
 * Dem_SatelliteMainFunction
 *****************************************************************************/
/*!
 * \brief         Cyclic DemSatellite timer task.
 *
 * \details       This function creates the time base for a DemSatellite.
 *
 *                Call this function in a cyclic manner, with the configured
 *                cycle time. The run-time of this function is as minimal as
 *                possible, so it can be called on a higher priority task with
 *                minimal impact.
 *
 * \pre           DemSatellite has been pre-initialized.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_SatelliteMainFunction(                                                                                                       /* PRQA S 3451 */ /* MD_DEM_8.8_schm */
  void
  );

#if (DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON)
/* ****************************************************************************
 % Dem_RequestNvSynchronization
 *****************************************************************************/
/*!
 * \brief         Initiate NV synchronization.
 *
 * \details       This function causes the Dem to actively write all modified
 *                NV data blocks into non-volatile memory.
 *
 *                In normal operation, the Dem only synchronizes all data with
 *                the non-volatile storage on shutdown. This relies on the
 *                NvM_WriteAll() mechanism. It can be beneficial to force
 *                a complete NV synchronization more often, e.g. once per
 *                ignition cycle if the ECU does not power down when turning
 *                ignition off.
 *
 *                The NV synchronization is an asynchronous background process
 *                that will eventually store all blocks into non volatile
 *                memory. The Dem can be shut down during this time as normal,
 *                as long as the result of Dem_PostRunRequested() is
 *                respected.
 *
 *                This mechanism does not replace the DemClearDTCBehavior
 *                setting, or using NvM_WriteAll(). It is a complementary
 *                measure to reduce the impact of power loss.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard.
 *
 * \return        E_OK
 *                Request processed successfully
 *
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_NVM_APPL_SYNCHRONIZE == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_RequestNvSynchronization(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_VERSION_INFO == STD_ON)
/* ****************************************************************************
 * Dem_GetVersionInfo
 *****************************************************************************/
/*!
 * \brief         Get the version information of this module.
 *
 * \details       This function writes the module version information, module
 *                ID and vendor ID into the passed structure. The version
 *                information is decimal coded.
 *
 * \param[out]    versioninfo
 *                Pointer to a struct receiving the version information
 *
 * \pre           versioninfo may not be NULL_PTR.
 * \config        DEM_CFG_SUPPORT_VERSION_INFO == STD_ON
 *
 * \context       TASK|ISR2, from any partition
 * \synchronous   TRUE
 * \reentrant     TRUE
 * \trace         CREQ-102945
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DEM_APPL_DATA)  versioninfo
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_SetEventAvailable
 *****************************************************************************/
/*!
 * \brief         Change event configuration.
 *
 * \details       This function changes if events are present or not in a
 *                given configuration. The main use case is related to variant
 *                coding, this is a run-time option to change the event
 *                configuration.
 *
 *                Events that are set 'unavailable' cause
 *                all Event based APIs (but Dem_SetEventAvailable()) to
 *                return E_NOT_OK and perform no action.
 *                DTC based API will not find unavailable events, to the point
 *                that such DTCs are suppressed once all related events are
 *                unavailable.
 *
 *                For all status calculations, an 'unavailable' event has UDS
 *                status 0x00 (passed and tested). When an unavailable event is
 *                set 'available' again, its status is initialized to 0x50
 *                (not tested).
 *
 *                An event that is already failed or stored can not be
 *                disconnected. Such events need to be cleared first, see
 *                Dem_ClearDTC().
 *
 *                Variant coding can be achieved using PostBuild Selectable
 *                when the event availability is known statically based on few
 *                ECU configurations.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \param[in]     AvailableStatus
 *                TRUE: Event is available
 *                FALSE: Event is not available
 *
 * \return        E_OK
 *                The request was processed successfully
 *
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or state.
 *
 * \pre           If DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON, the Dem must
 *                be initialized. Otherwise this API is available after
 *                pre-initialization.
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE (for different EventIds)
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEventAvailable(
  Dem_EventIdType  EventId,
  boolean  AvailableStatus
  );
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_SetDTCSuppression
 *****************************************************************************/
/*!
 * \brief         Suppress a DTC.
 *
 * \details       This function suppresses DTCs such, that Dcm will not report
 *                the DTC for any reason. The internal processing of the event
 *                continues as usual.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \param[in]     SuppressionStatus
 *                TRUE: Suppress the DTC
 *                FALSE: Lift suppression of the DTC
 *
 * \return        E_OK
 *                The request was processed successfully
 *
 * \return        E_NOT_OK
 *                No DTC was selected before the call or invalid parameters
 *                are passed to the function (only if DET is enabled).
 *
 * \return        DEM_WRONG_DTC
 *                The selected DTC does not exist in the selected origin
 *                or no single DTC has been selected
 *
 * \return        DEM_WRONG_DTCORIGIN
 *                The selected DTC Origin does not exist.
 *
 * \return        DEM_PENDING
 *                Never returned by this implementation
 *
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC.
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTCSuppression(
  uint8  ClientId,
  boolean  SuppressionStatus
  );
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_GetDTCSuppression
 *****************************************************************************/
/*!
 * \brief         Retrieve suppression state.
 *
 * \details       This function retrieves the current suppression state of 
 *                the selected DTC.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \param[out]    SuppressionStatus
 *                Pointer to receive the suppression state of the DTC.
 *
 * \return        E_OK
 *                The suppression state of the DTC was stored in 
 *                SuppressionStatus.
 *
 * \return        E_NOT_OK
 *                No DTC was selected before the call or invalid parameters 
 *                are passed to the function (only if Det is enabled)
 *
 * \return        DEM_WRONG_DTC
 *                The selected DTC does not exist in the selected origin
 *                or no single DTC has been selected
 *
 * \return        DEM_WRONG_DTCORIGIN
 *                The requested DTC Origin does not exist.
 *
 * \return        DEM_PENDING
 *                Never returned by this implementation
 *
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC.
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCSuppression(
  uint8  ClientId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  SuppressionStatus
  );
#endif


#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_SetEnableCondition
 *****************************************************************************/
/*!
 * \brief         Set state of enable conditions.
 *
 * \details       Each event may have assigned several enable conditions. If
 *                any enable conditions referenced by the event is disabled,
 *                event reports are not processed (Dem_SetEventStatus(),
 *                Dem_ReportErrorStatus()).
 *
 *                Depending on DemDebounceBehavior, the debouncing of events
 *                with a disabled precondition is either paused or reset.
 *                Once all enable conditions are fulfilled again, the monitor
 *                will be notified.
 *
 *                During the pre-initialization phase, all enable conditions
 *                are ignored. Starting with Dem_Init() the configured
 *                initialization values for the enable conditions apply.
 *
 * \param[in]     EnableCondition
 *                Unique handle of the EnableCondition
 *
 * \param[in]     ConditionFulfilled
 *                TRUE: Enable condition is fulfilled
 *                FALSE: Enable condition is not fulfilled
 *
 * \return        E_OK
 *                The request was processed successfully
 *
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           RTE is active (if RTE is used).
 * \config        DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEnableCondition(
  uint8  EnableCondition,
  boolean  ConditionFulfilled
  );
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_SetStorageCondition
 *****************************************************************************/
/*!
 * \brief         Set state of storage conditions.
 *
 * \details       Each event may have assigned several storage conditions. If
 *                any storage condition referenced by the event is disabled,
 *                the event is not stored into the event memory.
 *
 *                Depending on configuration, this will have an effect on the
 *                Status bits modified, e.g. ConfirmedDTC is not set in case
 *                DemResetConfirmedBitOnOverflow = TRUE.
 *
 * \param[in]     StorageCondition
 *                Unique handle of the StorageCondition
 *
 * \param[in]     ConditionFulfilled
 *                TRUE: Storage condition is fulfilled
 *                FALSE: Storage condition is not fulfilled
 *
 * \return        E_OK
 *                Request processed successfully
 *
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetStorageCondition(
  uint8  StorageCondition,
  boolean  ConditionFulfilled
  );
#endif

/* ****************************************************************************
 * Dem_ReportErrorStatus
 *****************************************************************************/
/*!
 * \brief         API to report a monitor result.
 *
 * \details       This API is the application interface to report monitor
 *                results.
 *
 *                The monitor status is updated synchronously. This can cause
 *                notification function to be called, e.g. to the FiM module.
 *                The event UDS status is processed on task level.
 *
 *                If enable conditions are not set for the reported event,
 *                the report is discarded.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report.
 *
 * \param[in]     EventStatus
 *                Monitor result reported for the Event. Valid values are
 *                 - DEM_EVENT_STATUS_PASSED
 *                 - DEM_EVENT_STATUS_FAILED
 *
 *                If monitor internal debouncing is disabled for the given EventId
 *                the following values are also allowed:
 *                 - DEM_EVENT_STATUS_PREPASSED
 *                 - DEM_EVENT_STATUS_PREFAILED
 *
 *                If monitor internal debouncing is enabled for the given EventId
 *                the following value is allowed:
 *                 - DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED
 *
 *                If similar conditions are used the following values
 *                are also allowed:
 *                 - DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED
 *                 - DEM_EVENT_STATUS_FAILED_CONDITIONS_NOT_FULFILLED
 *
 *                If similar conditions are used and monitor internal debouncing
 *                is enabled for the given EventId the following values are also
 *                allowed:
 *                 - DEM_EVENT_STATUS_PREPASSED_CONDITIONS_NOT_FULFILLED
 *                 - DEM_EVENT_STATUS_PREFAILED_CONDITIONS_NOT_FULFILLED
 *
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 * \synchronous   TRUE for monitor status, FALSE for event status
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_ReportErrorStatus(
  Dem_EventIdType  EventId,
  Dem_EventStatusType  EventStatus
  );

/* ****************************************************************************
 * Dem_SetEventStatus
 *****************************************************************************/
/*!
 * \brief         API to report a monitor result.
 *
 * \details       This API is the application interface to report monitor
 *                results. It can be invoked via RTE_CALL interface, as
 *                Operation of port interface 'DiagnosticMonitor'.
 *
 *                The monitor status is updated synchronously. This can cause
 *                notification function to be called, e.g. to the FiM module.
 *                The event UDS status is processed on task level.
 *
 *                If enable conditions are not set for the reported event,
 *                the report is discarded.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report.
 *
 * \param[in]     EventStatus
 *                Monitor result reported for the Event. Valid values are
 *                 - DEM_EVENT_STATUS_PASSED
 *                 - DEM_EVENT_STATUS_FAILED
 *
 *                If monitor internal debouncing is disabled for the given EventId
 *                the following values are also allowed:
 *                 - DEM_EVENT_STATUS_PREPASSED
 *                 - DEM_EVENT_STATUS_PREFAILED
 *
 *                If monitor internal debouncing is enabled for the given EventId
 *                the following value is allowed:
 *                 - DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED
 *
 *                If similar conditions are used the following values
 *                are also allowed:
 *                 - DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED
 *                 - DEM_EVENT_STATUS_FAILED_CONDITIONS_NOT_FULFILLED
 *
 *                If similar conditions are used and monitor internal debouncing
 *                is enabled for the given EventId the following values are also
 *                allowed:
 *                 - DEM_EVENT_STATUS_PREPASSED_CONDITIONS_NOT_FULFILLED
 *                 - DEM_EVENT_STATUS_PREFAILED_CONDITIONS_NOT_FULFILLED
 *
 * \return        E_OK
 *                The test result was processed successfully
 *
 * \return        E_NOT_OK
 *                The test result was rejected, e.g. due to enable conditions
 *                or variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 * \synchronous   TRUE for monitor status, FALSE for event status
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEventStatus(
  Dem_EventIdType  EventId,
  Dem_EventStatusType  EventStatus
  );

/* ****************************************************************************
 * Dem_ResetEventStatus
 *****************************************************************************/
/*!
 * \brief         SWC API to reset an events failed bit.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticMonitor'.
 *
 *                Dem_ResetEventStatus() resets the failed bit of an event
 *                that can not be tested in this operation cycle. If the event
 *                has already completed a test, the request is rejected.
 *
 *                The Dem module will not treat resetting the event failed bit
 *                as a trigger to start aging of an event.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to reset.
 *
 * \return        E_OK
 *                The request was processed successfully
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. the event had already
 *                completed testing, or due to variant coding
 *                (see Dem_SetEventAvailable() )
 *
 * \pre           RTE is started (if RTE is used).
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_ResetEventStatus(
  Dem_EventIdType  EventId
  );

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_PrestoreFreezeFrame
 *****************************************************************************/
/*!
 * \brief         SWC API to immediately store snapshot data.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticMonitor'.
 *
 *                Dem_PrestoreFreezeFrame() stores the snapshot data for
 *                an event, in order to freeze that data set when the event
 *                qualifies 'failed' later. If a prestored record already
 *                exists, the Dem will update it's contents.
 *
 *                Normally, the Dem collects the configured DID data for an
 *                event during the storage processing on the Dem task function.
 *                This function can be used to close the timing gap between the
 *                event report and the Dem task invocation, e.g. if the DID
 *                data changes rapidly.
 *
 *                The prestored data is managed in a seperate buffer. The data sets
 *                are discarded once the event reports a qualified result, or
 *                the queue overflows.
 *                Also see Dem_ClearPrestoredFreezeFrame to actively free a
 *                prestored data set.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \return        E_OK
 *                The data was collected successfully (if processed synchronously).
 *                Prestore freeze frame request accepted (if processed asynchronously).
 *
 * \return        E_NOT_OK
 *                No data was collected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 *
 * \pre           RTE is started (if RTE is used).
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 *
 * \synchronous   TRUE if called from partition same as Dem master
 *                FALSE if called from partition other than Dem master
 *
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_PrestoreFreezeFrame(
  Dem_EventIdType  EventId
  );
#endif

#if (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
/* ****************************************************************************
 * Dem_ClearPrestoredFreezeFrame
 *****************************************************************************/
/*!
 * \brief         SWC API to clear prestored data.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticMonitor'.
 *
 *                Dem_ClearPrestoredFreezeFrame() is not used for memory
 *                management, so its use is optional. The Dem automatically
 *                frees prestored data on use, or overflow. Call this API when
 *                the prestored data is no longer relevant and you want the
 *                Dem to ignore it.
 *
 *                If no prestored data exists, this function does nothing.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \return        E_OK
 *                Prestore data cleared (if processed synchronously).
 *                Clear prestore data request accepted (if processed asynchronously).
 *
 * \return        E_NOT_OK
 *                No prestore data cleared, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 *
 * \pre           RTE is started (if RTE is used).
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 *
 * \synchronous   TRUE if called from partition same as Dem master
 *                FALSE if called from partition other than Dem master
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearPrestoredFreezeFrame(
  Dem_EventIdType  EventId
  );
#endif

/* ****************************************************************************
 * Dem_ResetEventDebounceStatus
 *****************************************************************************/
/*!
 * \brief         SWC API to control the Dem internal event debouncing.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticMonitor'.
 *
 *                Depending on DebounceResetStatus and the EventId's configured
 *                debouncing algorithm, this API performs the following:
 *
 *                Time Based Debouncing:
 *                DEM_DEBOUNCE_STATUS_FREEZE: If the debounce timer is active,
 *                it is paused without modifying its current value. Otherwise
 *                this has no effect. The timer will continue if the monitor
 *                reports another PREFAILED or PREPASSED in the same direction.
 *
 *                DEM_DEBOUNCE_STATUS_RESET: The debounce timer is stopped and
 *                Its value is set to 0.
 *
 *                Counter Based Debouncing:
 *                DEM_DEBOUNCE_STATUS_FREEZE: This has no effect.
 *
 *                DEM_DEDOUNCE_STATUS_RESET: This will set the current value
 *                of the debounce counter back to 0.
 *
 *                Monitor Internal Debouncing:
 *                The API returns E_NOT_OK in either case.
 *
 * \attention     The operations Dem_SetEventStatus(),
 *                Dem_ResetEventStatus(), Dem_PrestoreFreezeFrame(),
 *                Dem_ClearPrestoredFreezeFrame() and
 *                Dem_ResetEventDebounceStatus() are not reentrant
 *                for the same EventId.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report.
 *
 * \param[in]     DebounceResetStatus
 *                DEM_DEBOUNCE_STATUS_RESET: Reset debouncing
 *                DEM_DEBOUNCE_STATUS_FREEZE: Freeze debouncing
 *
 * \return        E_OK
 *                The request was processed successfully
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           Dem has been pre-initialized.
 *
 * \context       TASK|ISR2, from the respective satellite partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_ResetEventDebounceStatus(
  Dem_EventIdType  EventId,
  Dem_DebounceResetStatusType  DebounceResetStatus
  );

/* ****************************************************************************
 * Dem_GetDebouncingOfEvent
 *****************************************************************************/
/*!
 * \brief         SWC API to read the debouncing status of an event.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 * \param[out]    DebouncingState
 *                Pointer receiving the current debouncing status
 *
 * \return        E_OK
 *                The debouncing status was stored into DebouncingState
 * \return        E_NOT_OK if
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           RTE is active (if RTE is used).
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDebouncingOfEvent(
  Dem_EventIdType  EventId,
  P2VAR(Dem_DebouncingStateType, AUTOMATIC, DEM_APPL_DATA)  DebouncingState
  );

/* ****************************************************************************
 * Dem_SetOperationCycleState
 *****************************************************************************/
/*!
 *  \brief        Start and Stop operation cycles.
 *
 *  \details      This function is used to report operation cycle changes to
 *                the Dem.
 *
 *                Usually, starting an operation cycle will reset
 *                *ThisOperationCycle status bits and the debouncing state.
 *                Ending an operation cycle tests for healing and aging
 *                conditions and processes related statistics.
 *
 *                Starting the OBD driving cycle will qualify it (if it is not
 *                yet qualified), ending the OBD driving cycle will restart it
 *                if the cycle is qualified.
 *
 *                Starting the OBD warm-up cycle can be delayed to the restart
 *                of the OBD driving cycle by configuration.
 *
 *                Starting the OBD hybrid ignition cycle will not have an
 *                effect on events, that cycle is only processed for internal
 *                statistics.
 *
 *                There is no difference between restarting an operation cycle
 *                and stopping then starting the same cycle. The latter will
 *                result in the exact same run-time behavior.
 *
 *                The processing queue for operation cycle changes is limited,
 *                this API will reject cycle state changes beyond a
 *                START-STOP or STOP-START double transition.
 *
 * \param[in]     OperationCycleId
 *                Identifier of the Cycle to change state
 *
 * \param[in]     CycleState
 *                DEM_CYCLE_STATE_START: Start a stopped cycle, or restart an
 *                                       active cycle.
 *                DEM_CYCLE_STATE_END:   Stop an active cycle.
 *
 * \return        E_OK
 *                Request was queued successfully
 *
 * \return        E_NOT_OK
 *                Only in case of detected development errors or in special
 *                case for OBD Driving cycle (Driving cycle qualification already
 *                queued, but not processed, and requested again).
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE (for different CycleIds)
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetOperationCycleState(
  uint8  OperationCycleId,
  Dem_OperationCycleStateType  CycleState
  );

/* ****************************************************************************
 * Dem_GetOperationCycleState
 *****************************************************************************/
/*!
 * \brief         Get the state of a specific operation cycle.
 *
 * \details       Get the state of a specific operation cycle.
 *
 * \param[in]     OperationCycleId
 *                Identifier of the Cycle of which to get the state
 *
 * \param[out]    CycleState
 *                The current state of the requested operation cycle.
 *                DEM_CYCLE_STATE_START: Cycle is started
 *                DEM_CYCLE_STATE_END:   Cycle is stopped
 *
 * \return        E_OK
 *                Request was successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetOperationCycleState(
  uint8  OperationCycleId,
  P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_APPL_DATA)  CycleState
  );

/* ****************************************************************************
 * Dem_GetIndicatorStatus
 *****************************************************************************/
/*!
 * \brief         Get current status of an indicator.
 *
 * \details       Calculates the accumulated status of an indicator.
 *
 *                Depending on the indicator and configuration, this includes
 *                the correct priorization of multiple concurrent requests,
 *                e.g. in J1939 you receive the same status that is reported
 *                in the DM messages.
 *
 * \param[in]     IndicatorId
 *                Unique identifier of the indicator
 *
 * \param[out]    IndicatorStatus
 *                The current status of the indicator
 *
 * \return        E_OK
 *                Request processed successfully
 *
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetIndicatorStatus(
  uint8  IndicatorId,
  P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA)  IndicatorStatus
  );

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 * Dem_GetWIRStatus
 *****************************************************************************/
/*!
 * \brief         Get state of Warning Indicator Request Bit override.
 *
 * \details       Check whether the WIR bit is latched for the event, or if its
 *                state is currently controlled by the Dem module.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[out]    WIRStatus
 *                TRUE:  WIR status is currently latched by user
 *                FALSE: WIR status is currently controlled by Dem
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard.
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetWIRStatus(
  Dem_EventIdType EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) WIRStatus
  );
#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 * Dem_SetWIRStatus
 *****************************************************************************/
/*!
 * \brief         Control Warning Indicator Request Bit override.
 *
 * \details       The Dem module controls the state of bit7 (RequestWarningInd)
 *                based on event healing. There are use-cases that require
 *                to keep the bit7 state alive longer than the normal healing
 *                algorithm does, e.g. because a fault reaction is disabled
 *                only with the next ignition cycle.
 *
 *                This function allows implementing such use-cases, without
 *                complicating the normal healing algorithm. Once a monitor
 *                calls this API with WIRStatus = TRUE, the WIR bit is active
 *                and remains active until this state is revoked by calling
 *                the API again, with WIRStatus = FALSE.
 *
 *                The related event will still heal bit7 as normal. Releasing
 *                the WIR latch will only result in WIR = FALSE if the event
 *                has healed.
 *
 *                During an active ControlDTCSetting (UDS service 0x85) the
 *                override state cannot be changed. In this case the API will
 *                return E_NOT_OK and the caller has to retry the operation
 *                later.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 * \param[in]     WIRStatus
 *                TRUE:  Latch WIR-bit to TRUE
 *                FALSE: Release the latch
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments, state or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE (for different EventIds)
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetWIRStatus(
  Dem_EventIdType EventId,
  boolean WIRStatus
  );
#endif

/* ****************************************************************************
 * Dem_SelectDTC
 *****************************************************************************/
/*!
 * \brief         Selects a DTC or DTC group as target for further operations.
 *
 * \details       The Dem provides a range of APIs controlling and accessing
 *                event memory and its behavior or configuration and states.
 *                Many of those APIs follow a 'select and request' mechanism.
 *                Initially a client selects a DTC or a group of DTCs and then
 *                calls APIs working on the active selection. A selection is
 *                client local and remains until a new selection is made.
 *
 *                If the API Dem_SelectDTC is called, the Dem uses the selected
 *                DTC or group of DTC in the requested DTCOrigin and DTCFormat
 *                as target for the following API calls:
 *                - Dem_GetStatusOfDTC
 *                - Dem_GetSeverityOfDTC
 *                - Dem_GetFunctionalUnitOfDTC
 *                - Dem_ClearDTC
 *                - Dem_DisableDTCRecordUpdate
 *                - Dem_EnableDTCRecordUpdate
 *                - Dem_GetDTCSelectionResult.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[in]     DTC
 *                Defines the DTC in respective format that is selected. If the
 *                DTC fits to a DTC group number, the DTC group is selected.
 * \param[in]     DTCFormat
 *                Defines the input-format of the provided DTC value.
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 *
 * \return        E_OK
 *                Always. Use API Dem_GetDTCSelectionResult for the result of
 *                this selection.
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SelectDTC(
  uint8              ClientId,
  uint32             DTC,
  Dem_DTCFormatType  DTCFormat,
  Dem_DTCOriginType  DTCOrigin
  );

/* ****************************************************************************
 * Dem_GetDTCSelectionResult
 *****************************************************************************/
/*!
 * \brief         Returns the result of API Dem_SelectDTC.
 *
 * \details       This function returns the result of a preceding
 *                call of API Dem_SelectDTC. It is no precondition to
 *                call this API for subsequent operations on the
 *                selected DTCs.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                The preceding DTC selection was successful.
 *
 * \return        DEM_STATUS_WRONG_DTC
 *                The requested DTC does not match the given DTC Origin.
 *
 * \return        DEM_STATUS_WRONG_DTCORIGIN
 *                The requested DTC Origin is not supported by configuration.
 *
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCSelectionResult(
  uint8 ClientId
  );

/* ****************************************************************************
 * Dem_GetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         API to read the monitor status.
 *
 * \details       This API reads the current monitor status of an event.
 *
 *                Dem_GetMonitorStatus() is part of the RTE interface, but
 *                may be called directly as well.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    MonitorStatus
 *                Pointer receiving the monitor status:
 *                Bit0:  DEM_MONITOR_STATUS_TF (TestFailed)
 *                Bit1:  DEM_MONITOR_STATUS_TNCTOC (TestNotCompletedThisOpCycle)
 *
 * \return        E_OK
 *                MonitorStatus now contains the event status.
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable()).
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetMonitorStatus(
  Dem_EventIdType  EventId,
  P2VAR(Dem_MonitorStatusType, AUTOMATIC, DEM_APPL_DATA)  MonitorStatus
  );

/* ****************************************************************************
 * Dem_GetEventUdsStatus
 * Dem_GetEventStatus
 *****************************************************************************/
/*!
 * \brief         API to read the UDS event status.
 *
 * \details       This API reads the current event status byte of an event.
 *                The status byte is encoded as described in ISO 14229, without
 *                applying the status availability mask.
 *
 *                Dem_GetEventUdsStatus() is part of the RTE interface, but
 *                may be called directly as well.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    UDSStatusByte
 *                Pointer receiving the event status:
 *                Bit0:  DEM_UDS_STATUS_TF
 *                Bit1:  DEM_UDS_STATUS_TFTOC
 *                Bit2:  DEM_UDS_STATUS_PDTC
 *                Bit3:  DEM_UDS_STATUS_CDTC
 *                Bit4:  DEM_UDS_STATUS_TNCSLC
 *                Bit5:  DEM_UDS_STATUS_TFSLC
 *                Bit6:  DEM_UDS_STATUS_TNCTOC
 *                Bit7:  DEM_UDS_STATUS_WIR
 *
 * \return        E_OK
 *                EventUdsStatus now contains the event status.
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable()).
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventUdsStatus(
  Dem_EventIdType  EventId,
  P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA)  UDSStatusByte
  );
#define Dem_GetEventStatus                          Dem_GetEventUdsStatus

/* ****************************************************************************
 * Dem_GetEventFailed
 *****************************************************************************/
/*!
 * \brief         API to read the event status bit 0.
 *
 * \details       This API returns bit0 of the current events status.
 *
 *                Dem_GetEventFailed() is part of the RTE interface, but
 *                may be called directly as well.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    EventFailed
 *                Pointer receiving the current failed bit:
 *                TRUE if bit0 is set, FALSE otherwise
 *
 * \return        E_OK
 *                EventFailed now contains the event status.
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable()).
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventFailed(
  Dem_EventIdType  EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventFailed
  );

/* ****************************************************************************
 * Dem_GetEventTested
 *****************************************************************************/
/*!
 * \brief         SWC API to read the negated event status bit 6.
 *
 * \details       This API returns TRUE in 'EventTested' if the event has
 *                completed a test in this operation cycle, FALSE otherwise.
 *                This corresponds to the negated status bit6.
 *
 *                Dem_GetEventTested() is part of the RTE interface, but
 *                may be called directly as well.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \param[out]    EventTested
 *                Pointer receiving the current tested bit
 *
 * \return        E_OK
 *                EventTested now contains the event status
 *
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable())
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventTested(
  Dem_EventIdType  EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  EventTested
  );

/* ****************************************************************************
 * Dem_GetEventFreezeFrameDataEx
 *****************************************************************************/
/*!
 * \brief         SWC API to read the stored snapshot data of an event.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 *                Dem_GetEventFreezeFrameDataEx() copies data from the stored
 *                snapshot data of an event into DestBuffer, following no
 *                particular format and contains no header-information like
 *                RecordNumber or DataId.
 *
 *                Only the DID data actually stored in the event storage is
 *                returned here. If the Dcm adds additional parts to a DID,
 *                these will be missing.
 *
 *                The record number 0xff is a magic value used to read the most
 *                recently stored record. This is only supported in case record
 *                numbers are calculated (DemTypeOfFreezeFrameRecordNumeration).
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[in]     RecordNumber
 *                SnapshotRecord number to read. Contrary to usual usage, 0xFF
 *                returns the most recently stored record.
 * \param[in]     DataId
 *                Return only the data of this DID.
 * \param[out]    DestBuffer
 *                Buffer to receive the data.
 * \param[in,out] BufSize
 *                In: Size of the buffer.
 *                Out: Number of bytes written.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is currently not stored for the requested event.
 *                or
 *                the requested RecordNumber is not supported for the given
 *                event
 *                or
 *                the requested data identifier is not supported within the
 *                requested record (freeze frame).
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *                or
 *                the requested data is currently not accessible (e.g. in case
 *                of asynchronous preempted data retrieval from application).
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer is too small.
 *
 * \pre           RTE is active (if RTE is used).
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventFreezeFrameDataEx(
  Dem_EventIdType  EventId,
  uint8  RecordNumber,
  uint16  DataId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  );

/* ****************************************************************************
 * Dem_GetEventExtendedDataRecordEx
 *****************************************************************************/
/*!
 * \brief         SWC API to read the extended record data of an event.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 *                Dem_GetEventExtendedDataRecordEx() copies extended data
 *                available or stored for an event into the passed buffer.
 *                This is particularly useful to retrieve statistic data, like
 *                occurrence counter or aging counter - if these are mapped to
 *                an extended data record.
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[in]     RecordNumber
 *                Extended DataRecord number to read. The record numbers 0xfe
 *                and 0xff are reserved.
 * \param[out]    DestBuffer
 *                Buffer to receive the data.
 * \param[in,out] BufSize
 *                In:  Size of the buffer.
 *                Out: Number of bytes written.
 *
 * \return        E_OK
 *                The requested data was copied to the destination buffer.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The data is not currently stored for the requested event
 *                or
 *                the requested data was not copied due to an undefined
 *                RecordNumber for the given event.
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *                or
 *                the requested data is currently not accessible (e.g. in case
 *                of asynchronous preempted data retrieval from application).
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer is too small.
 *
 * \pre           RTE is active (if RTE is used).
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventExtendedDataRecordEx(
  Dem_EventIdType  EventId,
  uint8  RecordNumber,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  BufSize
  );

#if (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON)
/* ****************************************************************************
 * Dem_GetEventMemoryOverflow
 *****************************************************************************/
/*!
 * \brief         Test if an event memory overflowed.
 *
 * \details       This function reports if a DTC was displaced from the given
 *                event memory because the event memory was completely full at
 *                the time. This includes the case of DTCs that did not enter
 *                the event memory for the same reason.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling module.
 * \param[in]     DTCOrigin
 *                Identifier of the event memory concerned:
 *                DEM_DTC_ORIGIN_PRIMARY_MEMORY
 *                DEM_DTC_ORIGIN_PERMANENT_MEMORY
 *                DEM_DTC_ORIGIN_SECONDARY_MEMORY
 * \param[out]    OverflowIndication
 *                Pointer to receive the overflow status:
 *                TRUE: Memory 'DTCOrigin' overflowed
 *                FALSE: Memory 'DTCOrigin' didn't overflow
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OVFLIND_API == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventMemoryOverflow(
uint8  ClientId,
Dem_DTCOriginType  DTCOrigin,
P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  OverflowIndication
);
#endif

#if (DEM_CFG_SUPPORT_OVFLIND_API == STD_ON)
/* ****************************************************************************
 * Dem_GetNumberOfEventMemoryEntries
 *****************************************************************************/
/*!
 * \brief         Gets the number of events currently stored.
 *
 * \details       This function reports the number of event entries occupied
 *                by events. This does not necessarily correspond to the DTC
 *                count read by Dcm due to event combination and other effects
 *                like post-building the OBD relevance of a DTC stored in OBD
 *                permanent memory.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling module.
 * \param[in]     DTCOrigin
 *                Identifier of the event memory concerned:
 *                DEM_DTC_ORIGIN_PRIMARY_MEMORY
 *                DEM_DTC_ORIGIN_PERMANENT_MEMORY
 *                DEM_DTC_ORIGIN_SECONDARY_MEMORY
 * \param[out]    NumberOfEventMemoryEntries
 *                Pointer to receive the event count
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OVFLIND_API == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfEventMemoryEntries(
uint8  ClientId,
Dem_DTCOriginType  DTCOrigin,                                                                                                  /* PRQA S 1330 */ /* MD_DEM_16.4_rte */
P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  NumberOfEventMemoryEntries
);
#endif

/* ****************************************************************************
 * Dem_GetEventIdOfDTC
 *****************************************************************************/
/*!
 * \brief         Get the EventId of a DTC.
 *
 * \details       Returns the EventId of the DTC selected by Dem_SelectDTC.
 *
 * \param[in]     ClientId
 *                The client to query
 *
 * \param[out]    EventId
 *                Pointer to receive the EventId
 *
 * \return        E_OK
 *                The requested EventId is stored in EventId
 * \return        DEM_WRONG_DTC
 *                DTC does not exist in the selected origin
 *                OR a DTC group or all DTCs is selected
 *                OR DTC is suppressed
 * \return        DEM_WRONG_DTCORIGIN
 *                Selected origin does not exist
 * \return        E_NOT_OK
 *                No DTC is selected
 * \return        DEM_PENDING
 *                Never returned by this implementation
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventIdOfDTC(
  uint8  ClientId,
  P2VAR(Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA)  EventId
  );

                                               /* Service Interface ClearDTC */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_ClearDTC
 *****************************************************************************/
/*!
 * \brief         Clear DTC memory.
 *
 * \details       Clearing of a DTC clears the stored event data from the event
 *                memory, resets the event status byte and debouncing state.
 *
 *                There are a variety of configuration settings that further
 *                control the behavior of this function:
 *                Configuration option DemClearDTCBehavior controls if the
 *                clear operation is complete when the RAM contents are
 *                cleared, or if the NV-RAM content must be cleared as well.
 *                (NVRAM is updated in all cases.)
 *
 *                Using configuration option DemClearDTCLimitation the API can
 *                be restricted to DTC groups.
 *
 * \param[in]     ClientId
 *                The client to query
 *
 * \return        E_OK
 *                Clearing is completed for the requested DTC(s).
 * \return        DEM_E_WRONG_DTC
 *                The requested DTC is not valid in the context of DTCFormat
 *                and DTCOrigin
 * \return        DEM_E_WRONG_DTCORIGIN
 *                The requested DTC origin is not available
 * \return        DEM_E_FAILED
 *                The clear operation could not be completed
 * \return        DEM_E_CLEAR_MEMORY_ERROR
 *                The clear operation has completed in RAM, but synchronization
 *                to Nv-Ram has failed
 * \return        DEM_E_PENDING
 *                The clear operation is in progress.
 * \return        DEM_E_CLEAR_BUSY
 *                Another clear operation is currently in progress.
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_ClearDTC(
  uint8  ClientId
  );

                                                                      /* DTR */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_SetDTR
 *****************************************************************************/
/*!
 * \brief         Reports a DTR result with lower and upper limit.
 *
 * \details       Reports a DTR result with lower and upper limit.
 *                Depending on the reported control value and the configured
 *                DTR attributes the DTR values are either ignored, processed
 *                or reset.
 *
 * \param[in]     DTRId
 *                Unique handle of the DTR
 * \param[in]     TestResult
 *                Test Result
 * \param[in]     LowerLimit
 *                Lower Limit
 * \param[in]     UpperLimit
 *                Upper Limit
 * \param[in]     Ctrlval
 *                Dtr Control Value
 *
 * \return        E_OK
 *                Report of DTR result was succesful
 * \return        E_NOT_OK
 *                Report of DTR result failed (or no support for DTR)
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTR(
  uint16 DTRId,
  sint32 TestResult,
  sint32 LowerLimit,
  sint32 UpperLimit,
  Dem_DTRControlType Ctrlval
  );


/* ****************************************************************************
 * Dem_UpdateAvailableOBDMIDs
 *****************************************************************************/
/*!
 * \brief         Requests the update of the available OBD MIDs.
 *
 * \details       As the visibility status of Dtrs can change during runtime
 *                and therefore MIDs might also not be visible anymore
 *                the application can trigger the update of the available
 *                OBD MIDs.
 *
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                not used
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_UpdateAvailableOBDMIDs(
  void
  );


#if (DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_GetEventEnableCondition
 *****************************************************************************/
/*!
 * \brief         Query if the events preconditions are fulfilled.
 *
 * \details       This API is an easy way for a monitor to verify (some of)
 *                its preconditions, as these tend to coincide with the
 *                Dem enable conditions for this event.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[out]    ConditionFulfilled
 *                TRUE: All enable conditions are fulfilled
 *                FALSE: At least one enable condition is not fulfilled
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_ENABLE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE: AR4.0.3, AR4.1.2 FALSE: AR4.2.1
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventEnableCondition(
  Dem_EventIdType  EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  ConditionFulfilled
  );
#endif

#if (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON)
/* ****************************************************************************
 * Dem_SetHideObdOccurrences
 *****************************************************************************/
/*!
 * \brief         Select Dependent Secondary ECU DTCs visibility mode
 *
 * \details       In primary ECUs, DTCs received from dependent secondary ECUs
 *                can optionally appear in enhanced diagnostic requests (most
 *                subservices of UDS service 0x19).
 *
 *                To select whether a DTC is in fact a dependent secondary ECU
 *                DTC, this logic uses the DemEventSignificance configuration
 *                option.
 *
 *                While the display mode is set to 'hide', all DTCs configured
 *                to support the MIL and marked with significance 'OCCURRENCE'
 *                are omitted from UDS responses that are unrelated to OBD.
 *                Otherwise, all DTCs are reported disregarding the setting of
 *                DemEventSignificance.
 *
 *                The behavior can be changed at any time, using this API. It
 *                is recommended to synchronize changing this setting with
 *                the Dcm service processing to avoid incomplete diagnostic
 *                responses.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[in]     DoHide
 *                TRUE (default):  Hide 'Occurrence' DTCs
 *                FALSE: Show all DTCs
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetHideObdOccurrences(
  boolean DoHide
  );
#endif

#if (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON)
/* ****************************************************************************
 * Dem_GetHideObdOccurrences
 *****************************************************************************/
/*!
 * \brief         Read the current setting for displaying Dependent Secondary
 *                ECU DTCs in Dcm responses
 *
 * \details       Read the current setting for displaying Dependent Secondary
 *                ECU DTCs in Dcm responses
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    IsHidden
 *                Pointer to variable receiving the display mode.
 *                TRUE:  'Occurrence' DTCs are omitted
 *                FALSE: All DTCs are included
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetHideObdOccurrences(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  IsHidden
  );
#endif

                                                   /* Interface EcuM <-> Dem */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_InitMemory
 *****************************************************************************/
/*!
 * \brief         Initialize statically initialized RAM variables
 *
 * \details       Normally the complier start-up code initializes statically
 *                initialized RAM variables of the form
 *                    static var = value;
 *                This function can be used instead, if this task is omitted
 *                from the start-up code.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \pre           The Dem may not have been initialized yet. Call this prior to
 *                Dem_PreInit().
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_InitMemory(
  void
  );

                                                              /* Cyclic task */
/* ------------------------------------------------------------------------- */
 
/* ****************************************************************************
 * Dem_MainFunctionTimer
 *****************************************************************************/
/*!
 * \brief         Cyclic Dem timer task
 *
 * \details       This function creates the time base for the Dem module.
 *
 *                Call this function in a cyclic manner, with the configured
 *                cycle time. The run-time of this function is as minimal as
 *                possible, so it can be called on a higher priority task with
 *                minimal impact.
 *
 *                If the Dem module is not initialized, calling this function
 *                has no effect.
 *
 * \pre           Dem has been pre-initialized
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MainFunctionTimer(
  void
);

/* ****************************************************************************
 * Dem_MainFunctionWorker
 *****************************************************************************/
/*!
 * \brief         Cyclic Dem worker task
 *
 * \details       This function processes the asynchronous status changes, e.g.
 *                storing event data into the event memory, clearing the event
 *                memory and processing operation cycle changes.
 *
 *                The run-time of this function can be high depending on the
 *                configuration, and the API calls that happen to coincide.
 *
 *                If the Dem module is not initialized, calling this function
 *                has no effect.
 *
 * \pre           Dem has been pre-initialized
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MainFunctionWorker(
  void
);

/* ****************************************************************************
 * Dem_MainFunction
 *****************************************************************************/
/*!
 * \brief         Cyclic Dem task
 *
 * \details       The AUTOSAR conforming way for the Dem asynchronous status
 *                processing and time base. In case the resulting run-time is
 *                too high to guarantee the cycle time, please refer to the
 *                configuration option DemGeneral/DemSupportSplitTasks
 *
 *                This function is basically a wrapper that calls both
 *                Dem_MainFunctionTimer() and Dem_MainFunctionWorker(),
 *                in this order.
 *
 * \pre           Dem has been pre-initialized
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_MainFunction(
  void
);

                                      /* Service Interface DiagnosticMonitor */
/* ------------------------------------------------------------------------- */

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 * Dem_SetEventDisabled
 *****************************************************************************/
/*!
 * \brief         SWC API to disable an event for the PID 0x41 computation
 *
 * \details       SWC API to disable an event for the PID 0x41 computation in the 
 *                current driving cycle
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *
 * \return        E_OK
 *                Event disabled
 *                E_NOT_OK 
 *                Event disabling failed OR 
 *                'Major Monitor' AND 'Comprehensive Component always complete' disabled
 *                
 *
 * \pre           RTE is started (if RTE is used)
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEventDisabled(
  Dem_EventIdType  EventId
  );
#endif

                                         /* Service Interface DiagnosticInfo */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_GetDTCOfEvent
 *****************************************************************************/
/*!
 * \brief         API to read the DTC number for the given EventId
 *
 * \details       This function retrieves the configured DTC number of an event
 *                from the configuration. Since the configuration is not known
 *                until full initialization, this API cannot be called prior
 *                to Dem_Init().
 *
 *                Dem_GetEventTested() is part of the RTE interface, but
 *                but may be called directly as well.

 * \param[in]     EventId
 *                Unique handle of the Event
 * \param[in]     DTCFormat
 *                DEM_DTC_FORMAT_OBD or DEM_DTC_FORMAT_UDS to select which
 *                DTC number is requested
 * \param[out]    DTCOfEvent
 *                Pointer receiving the DTC number

 * \return        E_OK
 *                The request was successful, DTCOfEvent now contains the DTC
 *                value.
 * \return        DEM_E_NO_DTC_AVAILABLE
 *                The event has no DTC in the requested format.
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 * \trace         CREQ-123114
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCOfEvent(
  Dem_EventIdType  EventId,
  Dem_DTCFormatType  DTCFormat,
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  DTCOfEvent
  );

/* ****************************************************************************
 * Dem_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         SWC API to read the fault detection counter of an event
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'DiagnosticInfo'.
 *
 *                For events that are debounced within the Dem (counter based
 *                and time based debouncing), the internal debouncing state
 *                is converted to an UDS FaultDetectionCounter value in
 *                range [-128..127].
 *
 *                For events that are debounced in application, the configured
 *                callback is invoked to read the current FDC.
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 * \param[out]    FaultDetectionCounter
 *                Pointer receiving the current fault detection counter.
 *
 * \return        E_OK
 *                The FDC was stored into FaultDetectionCounter
 * \return        DEM_E_NO_FDC_AVAILABLE
 *                The event is debounced within the application, but no
 *                callback was configured to read the FDC.
 * \return        E_NOT_OK if
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           RTE is active (if RTE is used)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetFaultDetectionCounter(
  Dem_EventIdType  EventId,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
  );
                                         /* Service Interface IUMPRNumerator */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_RepIUMPRFaultDetect
 *****************************************************************************/
/*!
 * \brief         SWC API to report that an asymmetrical monitor is able to
 *                detect a fault
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'IUMPRNumerator'.
 *
 *                For Ratios with DemRatioKind = API a qualified 'passed' test
 *                result is not sufficient to indicate that the monitor could
 *                also have detected a malfunction. This API is used to pass
 *                this information to the Dem module.
 *
 *                Ratios with DemRatioKind = OBSERVER are not allowed to use
 *                this API.
 *
 * \param[in]     RatioID
 *                Unique handle of the Ratio, which is equal to the EventId
 *                associated with the Ratio.
 *
 * \return        E_OK
 *                The monitor status was accepted
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to invalid arguments or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           RTE is active (if RTE is used)
 * \config        DEM_CFG_SUPPORT_IUMPR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_RepIUMPRFaultDetect(
  Dem_RatioIdType  RatioID
  );
#endif /* (DEM_CFG_SUPPORT_IUMPR == STD_ON) */

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_IUMPRLockNumerators
 *****************************************************************************/
/*!
 * \brief         SWC API to lock all numerators for the currenty DCY
 *
 * \details       If this API is called, numerators are not incremented until
 *                the end ot the current OBD driving cycle.
 *                There is no way to reset but the restart of the current DCY.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \return        E_OK
 *                The numerators were locked successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           RTE is active (if RTE is used)
 * \config        DEM_CFG_SUPPORT_IUMPR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_IUMPRLockNumerators(
  void
  );
#endif /* (DEM_CFG_SUPPORT_IUMPR == STD_ON) */
                                       /* Service Interface IUMPRDenumerator */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_RepIUMPRDenLock
 *****************************************************************************/
/*!
 * \brief         SWC API to report preconditions of function specific
 *                denominators
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'IUMPRDenominator'.
 *
 *                After this function is called, increments of Denominator and
 *                Numerator are blocked. This is only valid for Ratios of
 *                DemIUMPRDenGroup PHYS_API.
 *
 * \attention     The operations Dem_RepIUMPRDenLock() and
 *                Dem_RepIUMPRDenRelease() are not reentrant for the same
 *                RatioId.
 *
 * \param[in]     RatioID
 *                Unique handle of the Ratio, which is equal to the EventId
 *                associated with the Ratio.
 *
 * \return        E_OK
 *                The Ratio was locked successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           RTE is active (if RTE is used)
 * \config        DEM_CFG_SUPPORT_IUMPR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_RepIUMPRDenLock(
  Dem_RatioIdType  RatioID
  );
#endif /* (DEM_CFG_SUPPORT_IUMPR == STD_ON) */

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_RepIUMPRDenRelease
 *****************************************************************************/
/*!
 * \brief         SWC API to report preconditions of function specific
 *                denominators
 *
 * \attention     The operations Dem_RepIUMPRDenLock() and
 *                Dem_RepIUMPRDenRelease() are not reentrant for the same
 *                RatioId.
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'IUMPRDenominator'.
 *
 *                After this function is called, increments of Denominator and
 *                Numerator are enabled. This is only valid for Ratios of
 *                DemIUMPRDenGroup PHYS_API.
 *
 * \param[in]     RatioID
 *                Unique handle of the Ratio, which is equal to the EventId
 *                associated with the Ratio.
 *
 * \return        E_OK
 *                The ratio was unlocked successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or
 *                variant coding (see Dem_SetEventAvailable() )
 *
 * \pre           RTE is active (if RTE is used)
 * \config        DEM_CFG_SUPPORT_IUMPR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different RatioIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_RepIUMPRDenRelease(
  Dem_RatioIdType  RatioID
  );
#endif /* (DEM_CFG_SUPPORT_IUMPR == STD_ON) */

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_SetIUMPRDenCondition
 *****************************************************************************/
/*!
 * \brief         SWC API to report preconditions of common denominator groups
 *
 * \details       This API is intended to be called via RTE_CALL interface,
 *                as Operation of port interface 'IUMPRDenominatorCondition'.
 *
 *                Dem_SetIUMPRDenCondition() sets the denominator status
 *                for all RatioIds using the denominator group indicated by
 *                ConditionId. This basically does the same as
 *                Dem_RepIUMPRDenLock() and Dem_RepIUMPRDenRelease(),
 *                but for groups of RatioIds.
 *
 * \param[in]     ConditionId
 *                The denominator group for which the conditions are reported.
 * \param[in]     ConditionStatus
 *                The new status of the given ConditionId
 *
 * \return        E_OK
 *                The new condition status was accepted
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           RTE is active (if RTE is used)
 * \config        DEM_CFG_SUPPORT_IUMPR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ConditionIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetIUMPRDenCondition(
     Dem_IumprDenomCondIdType ConditionId,
     Dem_IumprDenomCondStatusType ConditionStatus
  );
#endif /* (DEM_CFG_SUPPORT_IUMPR == STD_ON) */


/* Service Interface IUMPRData */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_SetIUMPRFilter
 *****************************************************************************/
/*!
 * \brief         SWC API to set the IUMPR readiness group filter
 *
 * \details       Initializes the readiness group filter for the retrieving APIs
 *                Dem_GetNextIUMPRRatioDataAndDTC() and
 *                Dem_GetCurrentIUMPRRatioDataAndDTC()
 *
 * \param[in]     IumprReadinessGroup
 *                The readiness group which shall be set for filtering
 *
 * \param[in]     DTCOrigin
 *                Identifier of the event memory concerned:
 *                DEM_DTC_ORIGIN_PRIMARY_MEMORY
 *                DEM_DTC_ORIGIN_SECONDARY_MEMORY
 *
 * \return        E_OK
 *                The filter was accepted
 * \return        E_NOT_OK
 *                The filter was not accepted or in case of detected development
 *                errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_IUMPR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetIUMPRFilter(
  Dem_IumprReadinessGroupType IumprReadinessGroup,
  Dem_DTCOriginType  DTCOrigin
  );
#endif /* (DEM_CFG_SUPPORT_IUMPR == STD_ON) */

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_GetNumberOfFilteredIUMPR
 *****************************************************************************/
/*!
 * \brief         SWC API to retrieve the number of filtered IUMPRs
 *
 * \details       Returns the number of IUMPRs matching the filter criteria
 *
 * \param[out]    NumberOfFilteredRatios
 *                The number of ratios matching the filter criteria
 *
 * \return        E_OK
 *                The number of filtered ratios was read successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_IUMPR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfFilteredIUMPR(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  NumberOfFilteredRatios
  );
#endif /* (DEM_CFG_SUPPORT_IUMPR == STD_ON) */

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_GetIUMPRGeneralData
 *****************************************************************************/
/*!
 * \brief         SWC API to retrieve general IUMPR data
 *
 * \details       This API copies the respective values to the provided
 *                pointer locations.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    GeneralDenominator
 *                Value of general denominator
 * \param[out]    IgnitionCycles
 *                Number of ignition cycles
 * \param[out]    IgnitionCyclesHybrid
 *                Number of additional ignition cycles for hybrid vehicles
 *
 * \return        E_OK
 *                The general IUMPR data was read successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_IUMPR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetIUMPRGeneralData(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  GeneralDenominator,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  IgnitionCycles,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  IgnitionCyclesHybrid
  );
#endif /* (DEM_CFG_SUPPORT_IUMPR == STD_ON) */

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_GetNextIUMPRRatioDataAndDTC
 *****************************************************************************/
/*!
 * \brief         SWC API to retrieve the next ratio specific IUMPR data set
 *
 * \details       This function moves the internal iterator to the next Ratio
 *                and copies its DTC numbers as well as Denominator and
 *                Numerator values into the given pointer locations.
 *
 *                If no more Ratios are available (i.e. the iteration has
 *                completed) the function returns E_NOT_OK.
 *
 *                To read the current Ratio again, use
 *                Dem_GetCurrentIUMPRRatioDataAndDTC()
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    UdsDtcNumber
 *                UDS DTC to identify the ratio
 * \param[out]    ObdDtcNumber
 *                OBD DTC to identify the ratio
 * \param[out]    Denominator
 *                The current value of the denominator
 * \param[out]    Numerator
 *                The current value of the numerator
 *
 * \return        E_OK
 *                The ratio specific IUMPR data was read successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments, the
 *                iteration has not started (see Dem_GetIUMPRGeneralData() )
 *                or all Ratios were enumerated.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_IUMPR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextIUMPRRatioDataAndDTC(
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  UdsDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  ObdDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Denominator,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Numerator
  );
#endif /* (DEM_CFG_SUPPORT_IUMPR == STD_ON) */

#if (DEM_CFG_SUPPORT_IUMPR == STD_ON)
/* ****************************************************************************
 * Dem_GetCurrentIUMPRRatioDataAndDTC
 *****************************************************************************/
/*!
 * \brief         SWC API to retrieve the current ratio specific IUMPR data set
 *
 * \details       This function copies the current Ratios DTC numbers as well
 *                as Denominator and Numerator values into the given pointer
 *                locations. This works only if
 *                Dem_GetNextIUMPRRatioDataAndDTC() has already moved the
 *                internal iterator to a valid Ratio.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    UdsDtcNumber
 *                UDS DTC to identify the ratio
 * \param[out]    ObdDtcNumber
 *                OBD DTC to identify the ratio
 * \param[out]    Denominator
 *                The current value of the denominator
 * \param[out]    Numerator
 *                The current value of the numerator
 *
 * \return        E_OK
 *                The ratio specific IUMPR data was read successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments, the
 *                iteration has not returned a valid Ratio yet (see
 *                Dem_GetIUMPRGeneralData() and
 *                Dem_GetNextIUMPRRatioDataAndDTC() ) or the event became 
 *                unavailable or suppressed during the iteration
 *                
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_IUMPR == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetCurrentIUMPRRatioDataAndDTC(
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)  UdsDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  ObdDtcNumber,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Denominator,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)  Numerator
  );
#endif /* (DEM_CFG_SUPPORT_IUMPR == STD_ON) */

                                         /* Service Interface EventAvailable */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 * Dem_GetEventAvailable
 *****************************************************************************/
/*!
 * \brief         Get event configuration
 *
 * \details       This function returns if an events is present or not in a
 *                given configuration. The main use case is related to variant
 *                coding, this is a run-time way to check if an event is
 *                currently removed (see Dem_SetEventAvailable()
 *
 *                Variant coding can be achieved using PostBuild Selectable
 *                when the event availability is known statically based on few
 *                ECU configurations.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 * \param[out]    AvailableStatus
 *                TRUE: Event is available
 *                FALSE: Event is not available
 *
 * \return        E_OK
 *                The request was processed successfully
 * \return        E_NOT_OK
 *                The request was rejected due to invalid arguments or state.
 *                In this case, AvailableStatus will not be initialized.
 *
 * \pre           If DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON, the Dem must
 *                be initialized. Otherwise this API is available after
 *                pre-initialization.
 * \config        DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE (for different EventIds)
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetEventAvailable(
  Dem_EventIdType  EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  AvailableStatus
  );
#endif /* (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) */

                                        /* Service Interface EnableCondition */
/* ------------------------------------------------------------------------- */
                                               /* Permanent Fault Code Cycle */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* ****************************************************************************
 * Dem_SetPfcCycleQualified
 *****************************************************************************/
/*!
 * \brief         Report the pfc conditions
 *
 * \details       This API must be called once per driving cycle when the pfc
 *                conditions are met.
 *                The former API name 'Dem_SetPfcCycle' can still be used.
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON &&
 *                DEM_CFG_SUPPORT_PERMANENT == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetPfcCycleQualified(
  void
  );
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENT == STD_ON) */

/* Compatibility define */
#define Dem_SetPfcCycle                          Dem_SetPfcCycleQualified

                                             /* Permanent Storage Activation */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
/* ****************************************************************************
 * Dem_EnablePermanentStorage
 *****************************************************************************/
/*!
 * \brief         Activates permanent storage
 *
 * \details       For production purposes the permanent storage can be delayed
 *                for some time. This API is used to activate the permanent
 *                storage.
 *
 *                If the permanent storage is not enabled actively, the Dem
 *                will enable it when receiving a configured odometer value.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON &&
 *                DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_EnablePermanentStorage(
  void
  );
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON) */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON)
/* ****************************************************************************
 * Dem_GetPermanentStorageState
 *****************************************************************************/
/*!
 * \brief         Get state of permanent storage
 *
 * \details       Reads the activation state of the permanent DTC storage. If
 *                this returns TRUE via the out parameter isEnabled, permanent
 *                DTC handling is active.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    isEnabled
 *                Pointer to the variable receiving the activation state
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON &&
 *                DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetPermanentStorageState(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  isEnabled
  );
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON) */

                                                               /* B1 Counter */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 % Dem_GetB1Counter
 *****************************************************************************/
/*!
 * \brief         Read the B1 counter value
 *
 * \details       The Dem module supports the global B1 counter variant defined
 *                in the GTR. This API returns its current value.
 *
 * \param[out]    B1Counter
 *                Pointer to the variable receiving the B1 counter value
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetB1Counter(
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  B1Counter
  );
#endif /* (DEM_CFG_SUPPORT_WWHOBD == STD_ON) */

                                                                /* PID Data */
/* ------------------------------------------------------------------------- */
#if ((DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)) && (DEM_CFG_SUPPORT_PID01 == STD_ON)
/* ****************************************************************************
 * Dem_ReadDataOfPID01
 *****************************************************************************/
/*!
 * \brief         Read the monitoring status since DTCs cleared
 *
 * \details       Copies the 4 bytes of PID01, formatted this way:
 *                supported - 0 == FALSE; 1 == TRUE
 *                ready     - 0 == TRUE; 1 == FALSE
 *
 *                Byte 0
 *                  bit 0...6 - # of DTCs stored in this ECU
 *                  bit 7 - Malfunction Indicator Lamp (MIL) Status
 *
 *                Byte 1
 *                  bit 0 - Misfire monitoring supported
 *                  bit 1 - Fuel system monitoring supported
 *                  bit 2 - Comprehensive component monitoring supported
 *                  bit 3 - Compression ignition monitoring supported
 *                  bit 4 - Misfire monitoring ready
 *                  bit 5 - Fuel system monitoring ready
 *                  bit 6 - Comprehensive component monitoring ready
 *                  bit 7 - reserved
 *
 *                Byte 2
 *                  bit 0 - Catalyst monitoring supported
 *                  bit 1 - Heated catalyst monitoring supported
 *                  bit 2 - Evaporative system monitoring supported
 *                  bit 3 - Secondary air system monitoring supported
 *                  bit 4 - reserved
 *                  bit 5 - Oxygen sensor monitoring supported
 *                  bit 6 - Oxygen sensor heater monitoring
 *                  bit 7 - EGR system monitoring supported
 *
 *                Byte3
 *                  bit 0 - Catalyst monitoring ready
 *                  bit 1 - Heated catalyst monitoring ready
 *                  bit 2 - Evaporative system monitoring ready
 *                  bit 3 - Secondary air system monitoring ready
 *                  bit 4 - reserved
 *                  bit 5 - Oxygen sensor monitoring ready
 *                  bit 6 - Oxygen sensor heater monitoring ready
 *                  bit 7 - EGR system monitoring ready
 *
 * \param[out]    PID01value
 *                Pointer to the buffer receiving the current PID01 value
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 * \config        ((DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)) &&
 *                (DEM_CFG_SUPPORT_PID01 == STD_ON)
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_ReadDataOfPID01(
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID01value
  );
#endif /* ((DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)) && (DEM_CFG_SUPPORT_PID01 == STD_ON) */

                                                     /* Extension to Autosar */
/* ------------------------------------------------------------------------- */

/* ****************************************************************************
 * Dem_PostRunRequested
 *****************************************************************************/
/*!
 * \brief         Test whether the Dem can be shut down safely
 *
 * \details       This function must be polled after leaving RUN mode (all
 *                application monitors have been stopped). Due to pending NvM
 *                activity, data loss is possible if Dem_Shutdown is called
 *                while this function still returns TRUE.
 *
 *                This situation only occurs if the dem has to persist two
 *                data changes for the same Event. Basically, the first change
 *                needs to complete the writing process before the Dem can
 *                finalize its state to allow shutdown. Until that time, the
 *                Dem, NvM and the memory stack need to continue running.
 *
 *                As soon as the NvM finishes writing the current Dem data
 *                block, this function will return FALSE. The delay time to
 *                enable shutdown only depends on the write time of that one
 *                data block.
 *
 *                This API is a MICROSAR extension to the AUTOSAR standard
 *
 * \param[out]    IsRequested
 *                TRUE:  Shutdown is not possible without data loss.
 *                FALSE: Shutdown is possible.
 *
 * \return        E_OK
 *                Request processed successfully
 * \return        E_NOT_OK
 *                Only in case of detected development errors
 *
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_PostRunRequested(
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  IsRequested
  );



FUNC(void, DEM_CODE)
Dem_MementryInitFromApp(
		Dem_Cfg_MemoryIndexType index
  );
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_API_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_API_Interface.h
 *********************************************************************************************************************/
