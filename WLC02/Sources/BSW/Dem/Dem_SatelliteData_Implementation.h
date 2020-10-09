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
/*! \addtogroup Dem_SatelliteData
 *  \{
 *  \file       Dem_SatelliteData_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of SatelliteData subcomponent
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

#if !defined (DEM_SATELLITEDATA_IMPLEMENTATION_H)
#define DEM_SATELLITEDATA_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_SatelliteData_Interface.h"
#include "Dem_Prestore_Implementation.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Monitor_Interface.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
#define DEM_SATELLITEDATA_SHARED_STATUS_BYTESIZE DEM_1BYTE

#define DEM_SATELLITEDATA_MONITOR_STATUS         DEM_NBIT(DEM_SATELLITEDATA_MONITOR_STATUS_SIZE, DEM_SATELLITEDATA_MONITOR_STATUS_POS)  /*!< Bit mask for monitor status bit(s) */
#define DEM_SATELLITEDATA_MONITOR_STATUS_MASK    DEM_NBIT_MASK(DEM_SATELLITEDATA_MONITOR_STATUS_SIZE, DEM_SATELLITEDATA_MONITOR_STATUS_POS, DEM_SATELLITEDATA_SHARED_STATUS_BYTESIZE)  /*!< Negated bit mask for monitor status bit(s) */
#if ( ((DEM_SATELLITEDATA_MONITOR_STATUS & DEM_MONITOR_STATUS_TF) != DEM_MONITOR_STATUS_TF) \
   || ((DEM_SATELLITEDATA_MONITOR_STATUS & DEM_MONITOR_STATUS_TNCTOC) != DEM_MONITOR_STATUS_TNCTOC) )
# error "Satellite's monitor status definition is not compatible"
#endif

#define DEM_SATELLITEDATA_SIMILARCONDITION_STATUS         DEM_NBIT(DEM_SATELLITEDATA_SIMILARCONDITION_STATUS_SIZE, DEM_SATELLITEDATA_SIMILARCONDITION_STATUS_POS)  /*!< Bit mask for similar condition status bit(s) */
#define DEM_SATELLITEDATA_SIMILARCONDITION_STATUS_MASK    DEM_NBIT_MASK(DEM_SATELLITEDATA_SIMILARCONDITION_STATUS_SIZE, DEM_SATELLITEDATA_SIMILARCONDITION_STATUS_POS, DEM_SATELLITEDATA_SHARED_STATUS_BYTESIZE)  /*!< Negated bit mask for similar condition bit(s) */

#define DEM_SATELLITEDATA_DEBOUNCE_STATUS        DEM_NBIT(DEM_SATELLITEDATA_DEBOUNCE_STATUS_SIZE, DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS)  /*!< Bit mask for debounce status bit(s) */
#define DEM_SATELLITEDATA_DEBOUNCE_STATUS_MASK   DEM_NBIT_MASK(DEM_SATELLITEDATA_DEBOUNCE_STATUS_SIZE, DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS, DEM_SATELLITEDATA_SHARED_STATUS_BYTESIZE)  /*!< Negated bit mask for debounce status bit(s) */

#define DEM_SATELLITEDATA_PRESTOREFF_STATUS         DEM_NBIT(DEM_SATELLITEDATA_PRESTOREFF_STATUS_SIZE, DEM_SATELLITEDATA_PRESTOREFF_STATUS_POS)  /*!< Bit mask for prestore freeze frame status bit */
#define DEM_SATELLITEDATA_PRESTOREFF_STATUS_MASK    DEM_NBIT_MASK(DEM_SATELLITEDATA_PRESTOREFF_STATUS_SIZE, DEM_SATELLITEDATA_PRESTOREFF_STATUS_POS, DEM_SATELLITEDATA_SHARED_STATUS_BYTESIZE)  /*!< Negated bit mask for prestore freeze frame status bit(s) */

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
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \addtogroup Dem_SatelliteData_Properties
 * \{
 */

#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_SatelliteData_SetSimilarConditionStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetSimilarConditionStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_SatelliteData_DataType lReturnValue;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteData;
  lReturnValue.Data.SharedStatus =  (uint8)(lReturnValue.Data.SharedStatus | DEM_SATELLITEDATA_SIMILARCONDITION_STATUS);
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_SatelliteData_ResetSimilarConditionStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_ResetSimilarConditionStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  Dem_SatelliteData_DataType lReturnValue;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteData;
#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
  lReturnValue.Data.SharedStatus = (uint8)(lReturnValue.Data.SharedStatus & ~DEM_SATELLITEDATA_SIMILARCONDITION_STATUS);
#endif
  return lReturnValue;
}

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 % Dem_SatelliteData_GetPrestoreActionsQueued
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Prestore_QueueActionType, DEM_CODE)
Dem_SatelliteData_GetPrestoreActionsQueued(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  )
{
  return (Dem_Prestore_QueueActionType)(SatelliteExtendedData.Data.SharedData & DEM_SATELLITEDATA_PRESTOREFF_STATUS);
}
#endif

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 % Dem_SatelliteData_QueuePrestoreFF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_SatelliteData_QueuePrestoreFF(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  )
{
  Dem_SatelliteData_ExtendedDataType lReturnValue;                                                                               /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteExtendedData;
    lReturnValue.Data.SharedData = ((lReturnValue.Data.SharedData & ~DEM_SATELLITEDATA_PRESTOREFF_STATUS)
                                    | Dem_Prestore_PrestoreFF);
  return lReturnValue;
}
#endif

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 % Dem_SatelliteData_DequeuePrestoreActions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_SatelliteData_DequeuePrestoreActions(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  )
{
  Dem_SatelliteData_ExtendedDataType lReturnValue;                                                                               /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteExtendedData;
  lReturnValue.Data.SharedData = (lReturnValue.Data.SharedData & ~DEM_SATELLITEDATA_PRESTOREFF_STATUS);
  return lReturnValue;
}
#endif

#if ((DEM_CFG_SUPPORT_MULTIPLE_SATELLITES == STD_ON) && (DEM_CFG_SUPPORT_PRESTORED_FF == STD_ON))
/* ****************************************************************************
 % Dem_SatelliteData_QueueClearPrestoredFF
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_ExtendedDataType, DEM_CODE)
Dem_SatelliteData_QueueClearPrestoredFF(
  CONST(Dem_SatelliteData_ExtendedDataType, AUTOMATIC)  SatelliteExtendedData
  )
{
  Dem_SatelliteData_ExtendedDataType lReturnValue;                                                                               /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteExtendedData;
  lReturnValue.Data.SharedData = ((lReturnValue.Data.SharedData & ~DEM_SATELLITEDATA_PRESTOREFF_STATUS)
                                 | Dem_Prestore_Clear);
  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_SatelliteData_TestSimilarConditionStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_SatelliteData_TestSimilarConditionStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
  return (boolean)((SatelliteData.Data.SharedStatus & DEM_SATELLITEDATA_SIMILARCONDITION_STATUS) != 0);
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SatelliteData)                                                                                /* PRQA S 3112, 3199 */ /* MD_DEM_14.2, MD_DEM_3199 */
  return TRUE;
#endif
}

/* ****************************************************************************
 % Dem_SatelliteData_SetDebounceStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetDebounceStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData,
  CONST(Dem_Debounce_StatusType, AUTOMATIC) DebounceStatus
  )
{
  Dem_SatelliteData_DataType lReturnValue;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteData;
  lReturnValue.Data.SharedStatus =  (uint8)(
      (lReturnValue.Data.SharedStatus & DEM_SATELLITEDATA_DEBOUNCE_STATUS_MASK)
    | (DebounceStatus & DEM_SATELLITEDATA_DEBOUNCE_STATUS) );
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteData_GetDebounceStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_SatelliteData_GetDebounceStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  return (uint8)(SatelliteData.Data.SharedStatus & DEM_SATELLITEDATA_DEBOUNCE_STATUS);
}

/* ****************************************************************************
 % Dem_SatelliteData_SetDebounceData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetDebounceData(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData,
  CONST(Dem_Debounce_DataType, AUTOMATIC) DebounceData
  )
{
  Dem_SatelliteData_DataType lReturnValue;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteData;
  lReturnValue.Data.DebounceData = DebounceData;
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteData_GetDebounceData
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Debounce_DataType, DEM_CODE)
Dem_SatelliteData_GetDebounceData(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteData
  )
{
  return SatelliteData.Data.DebounceData;
}

/* ****************************************************************************
 % Dem_SatelliteData_SetMonitorStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetMonitorStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue,
  CONST(Dem_MonitorStatusType, AUTOMATIC)       MonitorStatusBits
  )
{
  Dem_SatelliteData_DataType lReturnValue;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lReturnValue = SatelliteDataValue;
  lReturnValue.Data.SharedStatus = (uint8)(
      (lReturnValue.Data.SharedStatus & DEM_SATELLITEDATA_MONITOR_STATUS_MASK)
    | (MonitorStatusBits & DEM_SATELLITEDATA_MONITOR_STATUS) );
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteData_GetMonitorStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_MonitorStatusType, DEM_CODE)
Dem_SatelliteData_GetMonitorStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  )
{
  return (Dem_MonitorStatusType)(SatelliteDataValue.Data.SharedStatus & DEM_SATELLITEDATA_MONITOR_STATUS);
}

/* ****************************************************************************
 % Dem_SatelliteData_SetQueueState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_SetQueueStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue,
  CONST(Dem_EventQueue_StatusType, AUTOMATIC) QueueStatus
  )
{
  Dem_SatelliteData_DataType lReturnValue;                                                                                       /* PRQA S 0759 */ /* MD_MSR_18.4 */

  lReturnValue = SatelliteDataValue;
  lReturnValue.Data.QueueStatus = QueueStatus;

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_SatelliteData_GetQueueStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventQueue_StatusType, DEM_CODE)
Dem_SatelliteData_GetQueueStatus(
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)  SatelliteDataValue
  )
{
  return SatelliteDataValue.Data.QueueStatus;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_SatelliteData_Public
 * \{
 */

/* ****************************************************************************
 % Dem_SatelliteData_GetInitValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_SatelliteData_DataType, DEM_CODE)
Dem_SatelliteData_GetInitValue(
  void
  )
{
  Dem_SatelliteData_DataType lSatelliteData;                                                                                     /* PRQA S 0759 */ /* MD_MSR_18.4 */
  lSatelliteData.Raw = 0;
  lSatelliteData = Dem_SatelliteData_SetMonitorStatus(lSatelliteData, DEM_MONITOR_STATUS_INITIAL);
  return lSatelliteData;
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_SATELLITEDATA_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteData_Implementation.h
 *********************************************************************************************************************/
