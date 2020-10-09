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
/*! \addtogroup Dem_EventInternalStatus
 *  \{
 *  \file       Dem_EventInternalStatus_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of the EventInternalStatus subcomponent
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

#if !defined (DEM_EVENTINTERNALSTATUS_TYPES_H)
#define DEM_EVENTINTERNALSTATUS_TYPES_H

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

/*!
 * \defgroup  Dem_EventInternalStatusBitSizes  Macros encoding bit sizes for event internal status
 * Macros encoding bit sizes for event internal status
 * \{
 */
#define DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED_SIZE        1  /*!< bit size of event suppressed */
#define DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT_SIZE          1  /*!< bit size of event disconnected */
#define DEM_EVENTINTERNALSTATUS_AVAILABLEINVARIANT_SIZE          1  /*!< bit size of event available in active variant */
/*!
 * \}
 */


/*!
 * \defgroup  Dem_EventInternalStatusBitPosition  Macros encoding bit position for internal status
 * Macros encoding bit position for internal status
 * \{
 */
#define DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT_POS           3  /*!< bit start position of event disconnected */
#define DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED_POS         4  /*!< bit start position of event suppressed */
#define DEM_EVENTINTERNALSTATUS_AVAILABLEINVARIANT_POS           6  /*!< bit start position of event available in active variant */


/*!
 * \}
 */

/*! Required byte size of event internal status */
#define DEM_EVENT_INTERNAL_STATUS_BYTESIZE         DEM_1BYTE

/*!
 * \defgroup  Dem_EventInternalStatusBitMasks  Macros encoding bit masks for internal status
 * Macros encoding bit masks for internal status
 * \{
 */

#define DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED             DEM_BIT(DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED_POS)  /*!< Bit mask for event suppressed bit(s) */
#define DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED_MASK        DEM_BIT_MASK(DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED_POS, DEM_EVENT_INTERNAL_STATUS_BYTESIZE)  /*!< Negated bit mask for event suppressed bit(s) */

#define DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT               DEM_BIT(DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT_POS)  /*!< Bit mask for event disconnected bit(s) */
#define DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT_MASK          DEM_BIT_MASK(DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT_POS, DEM_EVENT_INTERNAL_STATUS_BYTESIZE)  /*!< Negated bit mask for event disconnected bit(s) */

#define DEM_EVENTINTERNALSTATUS_AVAILABLEINVARIANT               DEM_BIT(DEM_EVENTINTERNALSTATUS_AVAILABLEINVARIANT_POS)  /*!< Bit mask for event available in active variant bit(s) */
#define DEM_EVENTINTERNALSTATUS_AVAILABLEINVARIANT_MASK          DEM_BIT_MASK(DEM_EVENTINTERNALSTATUS_AVAILABLEINVARIANT_POS, DEM_EVENT_INTERNAL_STATUS_BYTESIZE)  /*!< Negated bit mask for event available in active variant bit(s) */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_ExtendedDtcStatusClearMask  Macros encoding status masks to reset extended DTC status bits
 * Macros encoding status masks to set extended DTC status bits
 * \{
 */
#define DEM_EXT_STATUS_TPSLC_MASK                DEM_BIT_MASK(0, DEM_1BYTE)  /*!< Byte mask to reset test passed sincle last clear */
#define DEM_EXT_STATUS_SIMILAR_CONDITIONS_MASK   DEM_BIT_MASK(1, DEM_1BYTE)  /*!< Byte mask to reset similar conditions */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Esm_ExtendedDtcStatus  Macros encoding extended DTC status values
 * Macros encoding extended DTC status values
 * \{
 */
#define DEM_EXT_STATUS_TPSLC                     (0x01U)  /*!< DTC test passed since last clear */
#define DEM_EXT_STATUS_SIMILAR_CONDITIONS        (0x02U)  /*!< Similar conditions fulfilled */
/*!
 * \}
 */

/*! Extended DTC status after re-initialization */
#define DEM_EXT_STATUS_INITIALIZE                (0x00U)

/*! Qualification status 'all unqualified' */
#define DEM_QUALIFICATION_STATUS_ALL_UNQUALIFIED (0x77U)
/*! Qualification status 'all qualified' */
#define DEM_QUALIFICATION_STATUS_ALL_QUALIFIED   (0xFFU)


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Type to store the internal status of an event */
typedef uint8 Dem_Event_InternalStatusType;
/*! Type to store the extended status of an event */
typedef uint8 Dem_Event_ExtendedStatusType;
/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/



#endif /* DEM_EVENTINTERNALSTATUS_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EventInternalStatus_Types.h
 *********************************************************************************************************************/
