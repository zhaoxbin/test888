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
 *  \addtogroup Dem_API
 *  \{
 *  \file       Dem_API_Types.h
 *  \brief      Diagnostic Event Manager (Dem) Type and Macro definition file
 *  \details    Public types of API subcomponent
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

#if !defined (DEM_API_TYPES_H)
#define DEM_API_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

                                                    /* Service API and C API */
/* ------------------------------------------------------------------------- */

/*!
 * \defgroup  Dem_Api_InvalidValues Macros encoding invalid values for API parameter verification
 * Macros encoding invalid values for API parameter verification
 * \{
 */
#define DEM_DTC_MAX_VALUE                        ((uint32)(0x00ffffffUL))      /*< Largest 'DTC' value for any format */


#define DEM_DTC_FORMAT_INVALID                   ((Dem_DTCFormatType)(0x03U))  /*!< First out of range value of Dem_DTCFormatType */
#define DEM_DTC_ORIGIN_INVALID                   ((Dem_DTCOriginType)(0x06U))  /*!< First out of range value of Dem_DTCOriginType */
#define DEM_DTC_KIND_INVALID                     ((Dem_DTCKindType)(0x03U))    /*!< First out of range value of Dem_DTCKindType */

#define DEM_EVENT_STATUS_INVALID                 ((Dem_EventStatusType)(0x09U))  /*!< First out of range value of Dem_EventStatusType */
#define DEM_DEBOUNCE_STATUS_INVALID              ((Dem_DebounceResetStatusType)(0x02U))  /*!< First out of range value of Dem_DebounceResetStatusType */
#define DEM_CYCLE_STATE_INVALID                  ((Dem_OperationCycleStateType)(0x02U))  /*!< First out of range value of Dem_OperationCycleStateType */
#define DEM_IUMPR_DEN_COND_INVALID               ((Dem_IumprDenomCondIdType)(0x05U))  /*!< First out of range value of Dem_IumprDenomCondIdType */
#define DEM_IUMPR_READINESS_GROUP_INVALID        ((Dem_IumprReadinessGroupType)(0x11U))  /*!< First out of range value of Dem_IumprReadinessGroupType */
#define DEM_J1939_CLEAR_FILTER_INVALID           ((Dem_J1939DcmSetClearFilterType)(0x03U))  /*!< First out of range value of Dem_J1939DcmSetClearFilterType */
#define DEM_J1939_FILTER_FREEZEFRAME_INVALID     ((Dem_J1939DcmSetFreezeFrameFilterType)(0x03U))  /*!< First out of range value of Dem_J1939DcmSetFreezeFrameFilterType */
#define DEM_J1939_FILTER_DTC_INVALID             ((Dem_J1939DcmDTCStatusFilterType)(0x05U))  /*!< First out of range value of Dem_J1939DcmDTCStatusFilterType */
/*!
 * \}
 */

#endif /* DEM_API_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_API_Types.h
 *********************************************************************************************************************/
