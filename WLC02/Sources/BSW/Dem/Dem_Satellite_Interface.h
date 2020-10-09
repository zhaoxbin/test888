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
/*!
 *  \defgroup   Dem_Satellite Dem Satellite Functionality
 *  \{
 *  \file       Dem_Satellite_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of Satellite subcomponent
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

#if !defined (DEM_SATELLITE_INTERFACE_H)
#define DEM_SATELLITE_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Satellite_Types.h"
#include "Dem_SatelliteInfo_Interface.h"
#include "Dem_SatelliteData_Interface.h"
#include "Dem_Debounce_Interface.h"
#include "Dem_EnableCondition_Interface.h"
#include "Dem_Prestore_Interface.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Satellite_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Satellite_GetEventId
 *****************************************************************************/
/*!
 * \brief         Get the global Event Id from the Monitor Id.
 *
 * \details       Get the global Event Id from the satellite specific Event Id.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The global Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_Satellite_GetEventId(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_Satellite_GetApplicationId
 *****************************************************************************/
/*!
 * \brief         Get the application Id of a satellite
 *
 * \details       Get the application Id of a satellite
 *
 * \param[in]     SatelliteId
 *                Unique handle of the Satellite.
 *                The SatelliteId must be in range [1..Dem_Cfg_GlobalSatelliteCount()[.
 *
 * \return        The application Id of the given satellite
 *
 * \pre           -
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Satellite_ApplicationType, DEM_CODE)
Dem_Satellite_GetApplicationId(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId                                                                            /* PRQA S 3206 */ /* MD_DEM_3206 */
  );

#if (DEM_DEV_ERROR_DETECT == STD_ON)     
/* ****************************************************************************
 * Dem_Satellite_CheckEventApplicationId
 *****************************************************************************/
/*!
 * \brief         Check whether the event can be processed in the current
 *                execution context
 *
 * \details       Checks whether the given event is configured to be processed
 *                on the current OS application. In single partition 
 *                configurations, this is always the case.
 *
 * \param[in]     EventId
 *                Global Event Id
 *
 * \return        TRUE
 *                The event can be processed
 * \return        FALSE
 *                The event belongs to a different OS application
 *
 * \pre           -
 * \config        DEM_DEV_ERROR_DETECT == STD_ON
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_CheckEventApplicationId(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  );
#endif

#if (DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR == STD_ON)
/* ****************************************************************************
 * Dem_Satellite_SetDebounceLoResTimer
 *****************************************************************************/
/*!
 * \brief         Sets a new low resolution timer for the passed Satellite Id
 *
 * \details       Sets a new low resolution timer for the passed Satellite Id
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 * \param[in]     LoResTimer
 *                New low resolution timer
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR == STD_ON
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_SetDebounceLoResTimer(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Cfg_DebounceLoResTimerType, AUTOMATIC)  LoResTimer
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Satellite_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Satellite_GetSatelliteInfo
 *****************************************************************************/
/*!
 * \brief         Reads the satellite status of the given satellite.
 *
 * \details       Reads the satellite status of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \return        The satellite status of the satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteInfo_Type, DEM_CODE)
Dem_Satellite_GetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_SetSatelliteInfo
 *****************************************************************************/
/*!
 * \brief         Writes the satellite status of the given satellite.
 *
 * \details       Writes the satellite status of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \param[in]     NewSatelliteInfo
 *                The modified data to write
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC)  NewSatelliteInfo
  );

/* ****************************************************************************
 * Dem_SatelliteSat_SyncSetSatelliteInfo
 *****************************************************************************/
/*!
 * \brief         Writes the satellite status of the given satellite.
 *
 * \details       Write is only performed, if the current data content is
 *                identical to the the given parameter 'OldSatelliteInfo'.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \param[in]     OldSatelliteInfo
 *                The data before modification
 *                (returned by Dem_Satellite_GetSatelliteInfo()).
 *
 * \param[in]     NewSatelliteInfo
 *                The modified data to write.
 *
 * \return        TRUE
 *                Satellite status was successfully written
 * \return        FALSE
 *                Satellite status could not be written due to modification
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) OldSatelliteInfo,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) NewSatelliteInfo
  );

/* ****************************************************************************
 * Dem_SatelliteCore_SyncSetSatelliteInfo
 *****************************************************************************/
/*!
 * \brief         Writes the satellite status.
 *
 * \details       Write is only performed, if the current data content is
 *                identical to the the given parameter 'OldSatelliteInfo'.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \param[in]     OldSatelliteInfo
 *                The data before modification
 *                (returned by Dem_Satellite_GetSatelliteInfo()).
 *
 * \param[in]     NewSatelliteInfo
 *                The modified data to write.
 *
 * \return        TRUE
 *                Satellite status was successfully written
 * \return        FALSE
 *                Satellite status could not be written due to modification
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_SyncSetSatelliteInfo(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) OldSatelliteInfo,
  CONST(Dem_SatelliteInfo_Type, AUTOMATIC) NewSatelliteInfo
  );

/* ****************************************************************************
 * Dem_Satellite_GetSatelliteData
 *****************************************************************************/
/*!
 * \brief         Reads the satellite data of the given event.
 *
 * \details       Reads the satellite data of the given event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The satellite data of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_GetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 * Dem_Satellite_GetSatelliteExtendedData
 *****************************************************************************/
/*!
 * \brief         Reads the satellite extended data of the given event.
 *
 * \details       Reads the satellite extended data of the given event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The satellite extended data of the event
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *                && DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_Satellite_GetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );
#endif

/* ****************************************************************************
 * Dem_SatelliteSat_SetSatelliteData
 *****************************************************************************/
/*!
 * \brief         Writes the satellite data of the given event.
 *
 * \details       Writes the satellite data of the given event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \param[in]     NewSatelliteData
 *                The modified data to write
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  );

/* ****************************************************************************
 * Dem_SatelliteSat_SetSatelliteExtendedData
 *****************************************************************************/
/*!
 * \brief         Writes the satellite extended data of the given event.
 *
 * \details       Writes the satellite extended data of the given event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \param[in]     NewSatelliteExtendedData
 *                The modified data to write
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  NewSatelliteExtendedData
  );



/* ****************************************************************************
 * Dem_SatelliteSat_SyncSetSatelliteData
 *****************************************************************************/
/*!
 * \brief         Tries to write the satellite data of the given event to the
 *                communication buffer.
 *
 * \details       Write is only performed, if the current communication buffer
 *                content is identical to the the given parameter
 *                'OldSatelliteData'.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id whose data is updated
 *
 * \param[in]     OldSatelliteData
 *                The data before modification
 *                (returned by Dem_Satellite_GetSatelliteData()).
 *
 * \param[in]     NewSatelliteData
 *                The modified data to write.
 *
 * \return        TRUE
 *                Either Satellite data was successfully written
 *                Or MonitorId / SatelliteId are out of bounds to avoid
 *                endless loops
 * \return        FALSE
 *                Satellite data could not be written due to modification
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */


#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 * Dem_SatelliteSat_SyncSetSatelliteExtendedData
 *****************************************************************************/
/*!
 * \brief         Tries to write the satellite extended data of the given event to the
 *                communication buffer.
 *
 * \details       Write is only performed, if the current communication buffer
 *                content is identical to the the given parameter
 *                'OldSatelliteExtendedData'.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id whose data is updated
 *
 * \param[in]     OldSatelliteExtendedData
 *                The data before modification
 *                (returned by Dem_Satellite_GetSatelliteData()).
 *
 * \param[in]     NewSatelliteExtendedData
 *                The modified data to write.
 *
 * \return        TRUE
 *                Either Satellite extended data was successfully written
 *                Or MonitorId / SatelliteId are out of bounds to avoid
 *                endless loops
 * \return        FALSE
 *                Satellite extended data could not be written due to modification
 *
 * \pre           -
 * \config        (DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) 
 *                && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteSat_SyncSetSatelliteExtendedData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  OldSatelliteExtendedData,
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  NewSatelliteExtendedData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

/* ****************************************************************************
 * Dem_SatelliteCore_SyncSetSatelliteData
 *****************************************************************************/
/*!
 * \brief         Tries to write the satellite data of the given event to the
 *                communication buffer.
 *
 * \details       Write is only performed, if the current communication buffer
 *                content is identical to the the given parameter
 *                'OldSatelliteData'.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id whose data is updated
 *
 * \param[in]     OldSatelliteData
 *                The data before modification
 *                (returned by Dem_Satellite_GetSatelliteData()).
 *
 * \param[in]     NewSatelliteData
 *                The modified data to write.
 *
 * \return        TRUE
 *                Either Satellite data was successfully written
 *                Or MonitorId / SatelliteId are out of bounds to avoid
 *                endless loops
 * \return        FALSE
 *                Satellite data could not be written due to modification
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_SyncSetSatelliteData(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_SatelliteSat_SetEventQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Sets the event queue update flag of the given satellite.
 *
 * \details       Sets the update flag of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetEventQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_Satellite_TestSimilarConditionsChanged
 *****************************************************************************/
/*!
 * \brief         Test if reported similar conditions differs from current state.
 *
 * \details       Test if reported similar conditions differs from current state.
 *
 * \param[in]     OldSatelliteData
 *                Satellite data before the update
 * \param[in]     NewSatelliteData
 *                Satellite data after the update
 *
 * \return        TRUE
 *                Similar condition changed.
 * \return        FALSE
 *                Similar condition did not changed.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_TestSimilarConditionsChanged(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_SatelliteSat_SetInitState
 *****************************************************************************/
/*!
 * \brief         Set the initialization state of the Satellite.
 *
 * \details       Set the initialization state of the Satellite.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 * \param[in]     InitState
 *                The initialization state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetInitState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(uint8, AUTOMATIC) InitState
  );

/* ****************************************************************************
 * Dem_Satellite_TestMonitorQualificationNeeded
 *****************************************************************************/
/*!
 * \brief         Test whether a monitor qualification is needed.
 *
 * \details       Test whether a monitor qualification is needed.
 *
 * \param[in]     OldSatelliteData
 *                Satellite data before the update
 * \param[in]     NewSatelliteData
 *                Satellite data after update
 * \param[in]     DebounceInfoPtr
 *                The debounce object to read from.
 *
 * \return        TRUE
 *                Monitor qualification needed
 * \return        FALSE
 *                Monitor qualification not needed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_TestMonitorQualificationNeeded(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData,
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC) DebounceInfoPtr
  );
  
/* ****************************************************************************
 * Dem_Satellite_UpdateSatelliteData
 *****************************************************************************/
/*!
 * \brief         Update the queue state of an event
 *
 * \details       Update the queue state of an event based on the reported
 *                change stored in the given debounce object.
 *
 * \param[in]     OldSatelliteData
 *                The current satellite data
 * \param[in]     DebounceInfoPtr
 *                The debounce object to read from.
 *
 * \return        SatelliteData with the changes applied
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_UpdateSatelliteData(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)  DebounceInfoPtr
  );

/* ****************************************************************************
 * Dem_Satellite_UpdateSimilarConditions
 *****************************************************************************/
/*!
 * \brief         Update the similar condition state of an event
 *
 * \details       Update the similar condition state of an event
 *
 * \param[in]     OldSatelliteData
 *                The current satellite data
 * \param[in]     MonitorTrigger
 *                The monitor result
 *
 * \return        SatelliteData with the changes applied
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Satellite_UpdateSimilarConditions(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_EventStatusType, AUTOMATIC)         MonitorTrigger
  );

/* ****************************************************************************
 * Dem_Satellite_UpdateRatio
 *****************************************************************************/
/*!
 * \brief         Queue a test completed trigger for an attached ratio
 *
 * \details       Queue a test completed trigger for an attached ratio, if the
 *                ratio is of type 'Observer'
 *
 * \param[in]     EventId
 *                Unique handle of the Event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different EventId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Satellite_UpdateRatio(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_Satellite_TestQueueStatusUpdated
 *****************************************************************************/
/*!
 * \brief         Test whether a new queue entry was created
 *
 * \details       Test whether a new queue entry was created
 *
 * \param[in]     OldSatelliteData
 *                Satellite data before the update
 * \param[in]     NewSatelliteData
 *                Satellite data after the update
 *
 * \return        TRUE
 *                The queue state in the satellite data was created 
 * \return        FALSE
 *                The queue state in the satellite data was not changed or an
 *                existing state was updated
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Satellite_TestQueueStatusUpdated(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  OldSatelliteData,
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  NewSatelliteData
  );

/* ****************************************************************************
 * Dem_SatelliteSat_UpdateMonitorTrigger
 *****************************************************************************/
/*!
 * \brief         Processes asynchronous monitor reports.
 *
 * \details       This function processes event debouncing and queues
 *                qualified test results.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id whose data is updated
 *
 * \param[in]     MonitorTrigger
 *                The monitor result
 *
 * \return        E_OK
 *                The monitor result was processed
 * \return        E_NOT_OK
 *                The monitor result was discarded.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different events
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_SatelliteSat_UpdateMonitorTrigger(
  CONST(Dem_Satellite_IdType, AUTOMATIC)        SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC) MonitorId,
  CONST(Dem_EventStatusType, AUTOMATIC)         MonitorTrigger
  );

#if (DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON)
/* ****************************************************************************
 * Dem_SatelliteSat_ProcessTimeBasedDebouncing
 *****************************************************************************/
/*!
 * \brief         Processes the timer based debouncing of an event.
 *
 * \details       Updates the debouncing state and monitor status of the event
 *                using time based debouncing.
 *                Any resulting event processing is deferred to the
 *                context of the Dem task.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           The given SatelliteId is the ID of the caller satellite.
 * \config        DEM_FEATURE_NEED_DEBOUNCE_TIME == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_ProcessTimeBasedDebouncing(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT API PUBLIC FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Satellite_Public Public Methods
 * \{
 */
#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 * Dem_SatelliteSat_SetPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Sets the prestorage update flag of the given satellite.
 *
 * \details       Sets the prestorage update flag of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON
 *                && DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_SetPrestoreQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );
#endif

/* ****************************************************************************
 * Dem_SatelliteSat_FreezeDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Pauses the debouncing of an event.
 *
 * \details       Pauses the debouncing of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_FreezeDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_FreezeDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Pauses the debouncing of an event.
 *
 * \details       Pauses the debouncing of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteCore_FreezeDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_GetDebouncingState
 *****************************************************************************/
/*!
 * \brief         Calculates the debouncing state of an event.
 *
 * \details       Calculates the debouncing state of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The debouncing state of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Dem_DebouncingStateType, DEM_CODE)
Dem_SatelliteSat_GetDebouncingState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_ReportMonitorTrigger
 *****************************************************************************/
/*!
 * \brief         Processes the monitor result of an event.
 *
 * \details       Checks for valid event reporting conditions and triggers the
 *                updating of the monitor status in case of valid conditions.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report
 *
 * \param[in]     MonitorTrigger
 *                Monitor result reported for the Event
 *
 * \return        E_OK
 *                The monitor result was successfully processed
 * \return        E_NOT_OK
 *                The monitor result was rejected due to unfulfilled reporting
 *                conditions
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_SatelliteSat_ReportMonitorTrigger(
  CONST(Dem_EventIdType, AUTOMATIC)     EventId,
  CONST(Dem_EventStatusType, AUTOMATIC) MonitorTrigger
  );

/* ****************************************************************************
 * Dem_SatelliteSat_ResetEventStatus
 *****************************************************************************/
/*!
 * \brief         Reset the event status of an event.
 *
 * \details       Checks for valid reset conditions and triggers the
 *                updating of the monitor status in case of valid conditions.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report
 *
 * \return        E_OK
 *                The reset request was accepted
 * \return        E_NOT_OK
 *                The monitor result was rejected due to unfulfilled conditions
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_SatelliteSat_ResetEventStatus(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 * Dem_SatelliteSat_UpdatePrestore
 *****************************************************************************/
/*!
 * \brief         Updates the queued prestore action of an event.
 *
 * \details       Enqueues the prestorage of an freeze frame or the clear of an 
 *                already prestored freeze frame. A previously queued action is
 *                dequeued.
 *
 * \param[in]     EventId
 *                Unique handle of the Event to report
 *
 * \param[in]     NewPrestoreAction
 *                Handle of prestore action to queue
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON
 *                && DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_SatelliteSat_UpdatePrestore(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_Prestore_QueueActionType, AUTOMATIC)  NewPrestoreAction
  );
#endif

/* ****************************************************************************
 * Dem_SatelliteSat_MainFunction
 *****************************************************************************/
/*!
 * \brief         Processes all deferred operations.
 *
 * \details       This function is the task function of the Dem module.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \pre           The given SatelliteId is the ID of the caller satellite.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_MainFunction(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_ResetDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Resets the debouncing of an event.
 *
 * \details       Resets the debouncing of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_ResetDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_ResetDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Resets the debouncing of an event.
 *
 * \details       Resets the debouncing of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_ResetDebounceStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_ClearEvent
 *****************************************************************************/
/*!
 * \brief         Resets the debouncing, the monitor status and all queued
 *                actions for an event.
 *
 * \details       Resets the debouncing, the monitor status and all queued
 *                actions for an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_ClearEvent(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_RestartEvent
 *****************************************************************************/
/*!
 * \brief         Resets the debouncing and all queued actions for an event.
 *                Sets the TestNotCompletedThisCycle flag of the monitor status.
 *
 * \details       Resets the debouncing and all queued actions for an event.
 *                Sets the TestNotCompletedThisCycle flag of the monitor status.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_RestartEvent(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );


/* ****************************************************************************
 * Dem_SatelliteCore_TestAndClearEventQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Gets and resets the update flag of the given satellite.
 *
 * \details       Gets and resets the update flag of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 *
 * \return        The update flag of the satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_TestAndClearEventQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_SatelliteCore_TestAndClearPrestoreQueueUpdated
 *****************************************************************************/
/*!
 * \brief         Gets and resets the update flag of the given satellite.
 *
 * \details       Gets and resets the update flag of the given satellite.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 *
 * \return        The update flag of the satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteCore_TestAndClearPrestoreQueueUpdated(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_Satellite_PeekEventQueueStatus
 *****************************************************************************/
/*!
 * \brief         Gets the queue status of an event.
 *
 * \details       Gets the queue status of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The queue status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_Satellite_PeekEventQueueStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 * Dem_Satellite_PeekPrestoreActionQueue
 *****************************************************************************/
/*!
 * \brief         Gets the queued prestore action of an event.
 *
 * \details       Gets the queued prestore action of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The queued prestore action of the event
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON 
 *                && DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Prestore_QueueActionType, DEM_CODE)
Dem_Satellite_PeekPrestoreActionQueue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );
#endif

/* ****************************************************************************
 * Dem_SatelliteCore_ConsumeEventQueueStatus
 *****************************************************************************/
/*!
 * \brief         Gets and resets the queue status of an event.
 *
 * \details       Gets and resets the queue status of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The old satellite data
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteCore_ConsumeEventQueueStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 * Dem_Satellite_ConsumePrestoreActionQueue
 *****************************************************************************/
/*!
 * \brief         Gets and resets the queued prestore action of an event.
 *
 * \details       Gets and resets the queued prestore action of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        Handle of queued prestore action
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON 
 *                && DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Prestore_QueueActionType, DEM_CODE)
Dem_Satellite_ConsumePrestoreActionQueue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );
#endif

/* ****************************************************************************
 * Dem_SatelliteCore_MemoryInit
 *****************************************************************************/
/*!
 * \brief         Un-Initializes the satellite.
 *
 * \details       Un-Initializes the satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_MemoryInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_PreInit
 *****************************************************************************/
/*!
 * \brief         Pre-Initializes the satellite.
 *
 * \details       Pre-Initializes the satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_PreInit(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_SatelliteSat_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the satellite.
 *
 * \details       Initializes the satellite.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteSat_Init(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_Satellite_GetFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Reads the fault detection counter of an event.
 *
 * \details       Reads the fault detection counter of an event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 * \param[out]    FaultDetectionCounter
 *                Pointer receiving the current fault detection counter
 *
 * \return        E_OK
 *                The FDC was stored into FaultDetectionCounter
 * \return        DEM_E_NO_FDC_AVAILABLE
 *                The debouncing for the event is done within the application,
 *                but no callback was configured to read the FDC.
 * \return        E_NOT_OK
 *                The request was rejected, e.g. due to variant coding (see
 *                Dem_SetEventAvailable() )
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_Satellite_GetFaultDetectionCounter(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONSTP2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)  FaultDetectionCounter
  );

/* ****************************************************************************
 * Dem_Satellite_GetMaxFaultDetectionCounter
 *****************************************************************************/
/*!
 * \brief         Gets the maximum fault detection counter of an event.
 *
 * \details       This function retrieves the maximum value of the FDC in
 *                the current operation cycle. In case of monitor internal
 *                debouncing, this function returns an estimate based on the
 *                event's UDS status byte.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The maximum FDC this operation cycle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_Satellite_GetMaxFaultDetectionCounter(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
/* ****************************************************************************
 * Dem_SatelliteCore_RestoreDebounceValue
 *****************************************************************************/
/*!
 * \brief         Restores the given debouncing value of an event.
 *
 * \details       Value is restored, if
 *                 - the given debouncing value is not qualified
 *                 - the debouncing value is qualified and the reached
 *                   threshold equals the ExpectedThreshold.
 *
 *                Otherwise Value is not restored.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \param[in]     Value
 *                The value to be restored
 *
 * \param[in]     ExpectedThreshold
 *                Specifies whether the negative threshold is expected to be
 *                reached (TRUE), or the positive one (FALSE).
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_SatelliteCore_RestoreDebounceValue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId,
  CONST(sint16, AUTOMATIC) Value,
  CONST(boolean, AUTOMATIC) ExpectedThreshold
  );
#endif

/* ****************************************************************************
 * Dem_Satellite_GetDebounceValue
 *****************************************************************************/
/*!
 * \brief         Gets the debounce data of the given event.
 *
 * \details       -
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The current debounce data of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Debounce_DataType, DEM_CODE)
Dem_Satellite_GetDebounceValue(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );

/* ****************************************************************************
 * Dem_Satellite_GetInitState
 *****************************************************************************/
/*!
 * \brief         Get the Dem initialization state.
 *
 * \details       Get the Dem initialization state.
 *
 * \param[in]     SatelliteId
 *                Satellite Index
 * \return        The current initialization state
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Satellite_GetInitState(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId
  );

/* ****************************************************************************
 * Dem_Satellite_GetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Gets the monitor status of the given event.
 *
 * \details       Gets the monitor status of the given event.
 *
 * \param[in]     SatelliteId
 *                Index of the satellite associated with the event
 *
 * \param[in]     MonitorId
 *                Satellite specific Event Id
 *
 * \return        The current monitor status of the event
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Satellite_GetMonitorStatus(
  CONST(Dem_Satellite_IdType, AUTOMATIC)  SatelliteId,
  CONST(Dem_Satellite_MonitorIdType, AUTOMATIC)  MonitorId
  );


/* ****************************************************************************
 * Dem_Satellite_GetCurrentSatelliteId
 *****************************************************************************/
/*!
 * \brief         Identify the current satellite context.
 *
 * \details       Get the satellite id of the satellite corresponding to the
 *                current OS application.
 *
 * \return        The satellite id of the satellite corresponding to the
 *                current OS application.
 *
 * \pre           OS applications must be started.
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Satellite_IdType, DEM_CODE)
Dem_Satellite_GetCurrentSatelliteId(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_SATELLITE_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Satellite_Interface.h
 *********************************************************************************************************************/
