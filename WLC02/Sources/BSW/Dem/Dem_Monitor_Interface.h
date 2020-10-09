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
 *  \defgroup   Dem_Monitor Monitor Status
 *  \{
 *  \file       Dem_Monitor_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
 *  \details    Public interface of subcomponent Monitor
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

#if !defined (DEM_MONITOR_INTERFACE_H)
#define DEM_MONITOR_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Monitor_Types.h"
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
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Monitor_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_Monitor_TestMonitorStatusTF
 *****************************************************************************/
/*!
 * \brief         Tests whether the 'Test Failed' bit of the monitor status is set.
 *
 * \details       Tests whether the 'Test Failed' bit of the monitor status is set.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        TRUE
 *                TF bit is set.
 * \return        FALSE
 *                TF bit is not set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Monitor_TestMonitorStatusTF(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );

/* ****************************************************************************
 * Dem_Monitor_TestMonitorStatusTNCTOC
 *****************************************************************************/
/*!
 * \brief         Tests whether the 'Test Not Completed This Operation Cycle'
 *                bit of the monitor status is set.
 *
 * \details       Tests whether the 'Test Not Completed This Operation Cycle'
 *                bit of the monitor status is set.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        TRUE
 *                TNCTOC bit is set.
 * \return        FALSE
 *                TNCTOC bit is not set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Monitor_TestMonitorStatusTNCTOC(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );

/* ****************************************************************************
 * Dem_Monitor_SetMonitorStatusTF
 *****************************************************************************/
/*!
 * \brief         Sets the 'Test Failed' bit of the monitor status.
 *
 * \details       Sets the 'Test Failed' bit of the monitor status.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        Monitor status with 'Test Failed' bit set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_SetMonitorStatusTF(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );

/* ****************************************************************************
 * Dem_Monitor_SetMonitorStatusTNCTOC
 *****************************************************************************/
/*!
 * \brief         Sets the 'Test Not Completed This Operation Cycle' bit of the
 *                monitor status.
 *
 * \details       Sets the 'Test Not Completed This Operation Cycle' bit of the
 *                monitor status.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        Monitor status with 'Test Not Completed This Operation Cycle'
 *                bit set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_SetMonitorStatusTNCTOC(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );

/* ****************************************************************************
 * Dem_Monitor_ResetMonitorStatusTF
 *****************************************************************************/
/*!
 * \brief         Resets the 'Test Failed' bit of the monitor status.
 *
 * \details       Resets the 'Test Failed' bit of the monitor status.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        Monitor status with 'Test Failed' bit reset.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_ResetMonitorStatusTF(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Monitor_ResetMonitorStatusTNCTOC
 *****************************************************************************/
/*!
 * \brief         Resets the 'Test Not Completed This Operation Cycle' bit of the
 *                monitor status.
 *
 * \details       Resets the 'Test Not Completed This Operation Cycle' bit of the
 *                monitor status.
 *
 * \param[in]     MonitorStatus
 *                The Monitor status.
 *
 * \return        Monitor status with 'Test Not Completed This Operation Cycle'
 *                bit reset.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_ResetMonitorStatusTNCTOC(
  CONST(Dem_MonitorStatusType, AUTOMATIC)  MonitorStatus
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Monitor_ResetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Set the monitor status in satellite data object to its
 *                initial value.
 *
 * \details       Set the monitor status bits from the given satellite data
 *                object to their initial value and return a new satellite data.
 *
 * \param[in]     SatelliteDataValue
 *                The data object to read from.
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
Dem_Monitor_ResetMonitorStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_Monitor_GetMonitorStatus
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
Dem_Monitor_GetMonitorStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  );

/* ****************************************************************************
 * Dem_Monitor_SetMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Store the MonitorStatus in the SatelliteDataValue.
 *
 * \details       Update the MonitorStatus bits in the packed
 *                SatelliteDataValue and return the resulting SatelliteData.
 *
 * \param[in]     SatelliteDataValue
 *                The existing SatelliteDataValue.
 * \param[in]     MonitorStatusBits
 *                The MonitorStatus bitfield (with the AUTOSAR defined bits
 *                DEM_MONITOR_STATUS_TF, DEM_MONITOR_STATUS_TNCTOC).
 *
 * \return        Resulting SatelliteDataValue.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_Monitor_SetMonitorStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue,
  CONST(Dem_MonitorStatusType, AUTOMATIC)      MonitorStatusBits
  );

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
 * \defgroup Dem_Monitor_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Cfg_GlobalTriggerOnMonitorStatusFPtr
 *****************************************************************************/
/*!
 * \brief         Get the global notification function for
 *                TriggerOnMonitorStatus.
 *
 * \details       Get the global notification function for
 *                TriggerOnMonitorStatus.
 *
 * \return        Function pointer to call
 *                NULL_PTR if no such notification is configured
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_GlobalTriggerOnMonitorStatusFPtrType, DEM_CODE)
Dem_Cfg_GlobalTriggerOnMonitorStatusFPtr(
  void
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"     

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PUBLIC FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_Monitor_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_Monitor_CalculateMonitorStatus
 *****************************************************************************/
/*!
 * \brief         Calculate and update the MonitorStatus from MonitorTrigger.
 *
 * \details       Evaluate the MonitorTrigger value to set or reset the related
 *                monitor status bit value in the MonitorStatusValue, and
 *                return the new MonitorStatusValue.
 *
 * \param[in]     MonitorStatusValue
 *                The existing MonitorStatusValue.
 * \param[in]     MonitorTrigger
 *                The monitor result reported by the application monitor.
 *
 * \return        Resulting MonitorStatusValue.
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_Monitor_CalculateMonitorStatus(
  CONST(Dem_MonitorStatusType, AUTOMATIC)   MonitorStatusValue,
  CONST(Dem_EventStatusType, AUTOMATIC)     MonitorTrigger
  );

/* ****************************************************************************
 * Dem_Monitor_ResetTNCTOC
 *****************************************************************************/
/*!
 * \brief         Set the TNCTOC status in the satellite data object 
 *
 * \details       Set the monitor status bits from the given satellite data
 *                object to include the TNCTOC flag, and return a new satellite
 *                data.
 *
 * \param[in]     SatelliteDataValue
 *                The data object to read from.
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
Dem_Monitor_ResetTNCTOC(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MONITOR_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Monitor_Interface.h
 *********************************************************************************************************************/
