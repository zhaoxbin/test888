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
/*! \addtogroup Dem_Prestore
 *  \{
 *  \file       Dem_Prestore_Types.h
 *  \brief      Stores and manages 'prestored freezeframes'.
 *  \details    - Stores the snapshot data for an event, in order to freeze that data set when the event qualifies 'failed' later.
 *              - Manage the prestored data in a FIFO list. The data sets are discarded once the event reports a qualified result,
 *                or the queue overflows.
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

#if !defined (DEM_PRESTORE_TYPES_H)
#define DEM_PRESTORE_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \defgroup  Dem_Prestored_InvalidHandles  Macros encoding invalid index values
 * Macros encoding invalid index values
 * \{
 */
/*! Invalid index into Dem_Cfg_Prestorage array - this is the maximum *index* with a buffer at that location. */
# define DEM_PRESTORE_INVALID_BUFFER_ENTRY                                     (Dem_Cfg_GlobalPrestorageSize())
/*! Invalid index into Dem_Cfg_PrestorageIndex array, typically used for 'this event has no prestore memory configured'. */
# define DEM_PRESTORE_NOT_CONFIGURED_FOR_EVENT                                 DEM_G_GLOBAL_PRESTORED_EVENT_COUNT
/*!
 * \}
 */

/*! Handle for prestorage actions set on satellite, read on master*/
enum Dem_Prestore_QueueAction
{
  Dem_Prestore_Initial = 0,
  Dem_Prestore_PrestoreFF,
  Dem_Prestore_Clear
};

typedef enum Dem_Prestore_QueueAction Dem_Prestore_QueueActionType;

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#endif /* DEM_PRESTORE_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Prestore_Types.h
 *********************************************************************************************************************/
