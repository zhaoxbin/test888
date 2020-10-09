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
/*! \ingroup    Dem_Satellite
 *  \defgroup   Dem_SatelliteData Satellite Data
 *  \{
 *  \file       Dem_SatelliteData_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of SatelliteData subcomponent
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

#if !defined (DEM_SATELLITEDATA_INTERFACE_H)
#define DEM_SATELLITEDATA_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Dem_Prestore_Interface.h"
                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_SatelliteData_Types.h"

/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_SatelliteData_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_SatelliteData_TestSimilarConditionStatus
 *****************************************************************************/
/*!
 * \brief         Reads the similar condition status from the given satellite data object.
 *
 * \details       Reads the similar condition status from the given satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to read from.
 *
 * \return        TRUE
 *                Similar conditions not supported or similar conditions set
 *                FALSE
 *                Similar conditions not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteData_TestSimilarConditionStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_SatelliteData_SetSimilarConditionStatus
 *****************************************************************************/
/*!
 * \brief         Set the similar condition status in the satellite data object.
 *
 * \details       Set the similar condition status in the satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to modify
 *
 * \return        The modified satellite data object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetSimilarConditionStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );
#endif

/* ****************************************************************************
 * Dem_SatelliteData_ResetSimilarConditionStatus
 *****************************************************************************/
/*!
 * \brief         Reset the similar condition status in the satellite data object.
 *
 * \details       Reset the similar condition status in the satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to modify
 *
 * \return        The modified satellite data object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_ResetSimilarConditionStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_SatelliteData_SetDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Set the given debounce status into the satellite data object.
 *
 * \details       Set the given debounce status into the satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to modify
 *
 * \param[in]     DebounceStatus
 *                The data to write to SatelliteData.
 *
 * \return        The modified satellite data object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetDebounceStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData,
  CONST(Dem_Debounce_StatusType, AUTOMATIC) DebounceStatus
  );

/* ****************************************************************************
 * Dem_SatelliteData_GetDebounceStatus
 *****************************************************************************/
/*!
 * \brief         Reads the debounce status from the given satellite data object.
 *
 * \details       Reads the debounce status from the given satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to read from.
 *
 * \return        The requested data.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_SatelliteData_GetDebounceStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_SatelliteData_SetDebounceData
 *****************************************************************************/
/*!
 * \brief         Set the given debounce data into the satellite data object.
 *
 * \details       Set the given debounce data into the satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to modify.
 *
 * \param[in]     DebounceData
 *                The data to write to SatelliteData.
 *
 * \return        The modified satellite data object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetDebounceData(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData,
  CONST(Dem_Debounce_DataType, AUTOMATIC)  DebounceData
  );

/* ****************************************************************************
 * Dem_SatelliteData_GetDebounceData
 *****************************************************************************/
/*!
 * \brief         Reads the debounce data from the given satellite data object.
 *
 * \details       Reads the debounce data from the given satellite data object.
 *
 * \param[in]     SatelliteData
 *                The data object to read from.
 *
 * \return        The requested data.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Debounce_DataType, DEM_CODE)
Dem_SatelliteData_GetDebounceData(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  );

/* ****************************************************************************
 * Dem_SatelliteData_SetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Update the monitor status into the satellite data object.
 *
 * \details       Update the monitor status into the satellite data object.
 *
 * \param[in]     SatelliteDataValue
 *                The SatelliteData value to modify.
 *
 * \param[in]     MonitorStatusBits
 *                The data to write to SatelliteData.
 *
 * \return        The new SatelliteData value.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetMonitorStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue,
  CONST(Dem_MonitorStatusType, AUTOMATIC)       MonitorStatusBits
  );

/* ****************************************************************************
 * Dem_SatelliteData_GetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Reads the monitor status from the given satellite data object.
 *
 * \details       Reads the monitor status from the given satellite data object.
 *
 * \param[in]     SatelliteDataValue
 *                The data object to read from.
 *
 * \return        The MonitorStatus.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_SatelliteData_GetMonitorStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  );

/* ****************************************************************************
 * Dem_SatelliteData_SetQueueStatus
 *****************************************************************************/
/*!
 * \brief         Update the queue status into the satellite data object.
 *
 * \details       Update the queue status into the satellite data object.
 *
 * \param[in]     SatelliteDataValue
 *                The SatelliteData value to modify.
 *
 * \param[in]     QueueStatus
 *                The data to write to SatelliteData.
 *
 * \return        The new SatelliteData value.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetQueueStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue,
  CONST(Dem_EventQueue_StatusType, AUTOMATIC)  QueueStatus
  );

/* ****************************************************************************
 * Dem_SatelliteData_GetQueueStatus
 *****************************************************************************/
/*!
 * \brief         Reads the queue status from the given satellite data object.
 *
 * \details       Reads the queue status from the given satellite data object.
 *
 * \param[in]     SatelliteDataValue
 *                The data object to read from.
 *
 * \return        The requested data.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_SatelliteData_GetQueueStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  );

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 * Dem_SatelliteData_GetPrestoreActionsQueued
 *****************************************************************************/
/*!
 * \brief         Reads the queued actions from the given satellite extended data object.
 *
 * \details       Reads the queued actions from the given satellite extended data object.
 *
 * \param[in]     SatelliteExtendedData
 *                The data object to read from.
 *
 * \return        The requested data.
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *                && DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Prestore_QueueActionType, DEM_CODE)
Dem_SatelliteData_GetPrestoreActionsQueued(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  );
#endif

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 * Dem_SatelliteData_QueuePrestoreFF
 *****************************************************************************/
/*!
 * \brief         Stores the action to prestore a freeze frame in the given 
 *                satellite extended data object.
 *
 * \details       Stores the action to prestore a freeze frame in the given 
 *                satellite extended data object.
 *
 * \param[in]     SatelliteExtendedData
 *                The data object to read from.
 *
 * \return        The new extended satellite data.
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *                && DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_SatelliteData_QueuePrestoreFF(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  );
#endif

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 * Dem_SatelliteData_QueueClearPrestoredFF
 *****************************************************************************/
/*!
 * \brief         Stores the action to clear prestored freeze frames in the given 
 *                satellite extended data object.
 *
 * \details       Stores the action to clear prestored freeze frames in the given 
 *                satellite extended data object.
 *
 * \param[in]     SatelliteExtendedData
 *                The data object to read from.
 *
 * \return        The new extended satellite data.
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *                && DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_SatelliteData_QueueClearPrestoredFF(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  );
#endif

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 * Dem_SatelliteData_DequeuePrestoreActions
 *****************************************************************************/
/*!
 * \brief         Clears all prestore actions in the given 
 *                satellite extended data object.
 *
 * \details       Clears all prestore actions in the given 
 *                satellite extended data object.
 *
 * \param[in]     SatelliteExtendedData
 *                The data object to read from.
 *
 * \return        The new extended satellite data.
 *
 * \pre           -
 *
 * \config        DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *                && DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_SatelliteData_DequeuePrestoreActions(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  );
#endif

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
 * \defgroup Dem_SatelliteData_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_SatelliteData_GetInitValue
 *****************************************************************************/
/*!
 * \brief         Initialize the satellite data.
 *
 * \details       Initialize the satellite data.
 *
 * \return        The initialized data object.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_GetInitValue(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_SATELLITEDATA_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteData_Interface.h
 *********************************************************************************************************************/
