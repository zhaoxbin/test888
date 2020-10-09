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
/*! \addtogroup Dem_SnapshotEntry
 *  \{
 *  \file       Dem_SnapshotEntry_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Encapsulates the list of snapshot record buffers stored in the memory entry
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

#if !defined (DEM_SNAPSHOTENTRY_TYPES_H)
#define DEM_SNAPSHOTENTRY_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_MemoryEntry_Fwd.h"

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
/*! Snapshot entry handle */
struct Dem_SnapshotEntry_Handle_s
{
  Dem_Cfg_SRecIndexType         SnapshotIteratorIndex;  /*!< snapshot record index */
  Dem_EventIdType               EventId;                /*!< event Id */
  Dem_MemoryEntry_HandleType    MemoryEntryId;          /*!< memory entry handle */
  uint8                         SnapshotEntryIndex;     /*!< snapshot entry index */
#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)
  boolean                       GlobalSnapshotReported;  /*!< Indicating if global snapshot reported for current memory entry */
#endif
};

/*! Snapshot entry handle type */
typedef struct Dem_SnapshotEntry_Handle_s Dem_SnapshotEntry_IterType;

typedef P2VAR(Dem_SnapshotEntry_IterType, TYPEDEF, AUTOMATIC) Dem_SnapshotEntry_IterPtrType;

#endif /* DEM_SNAPSHOTENTRY_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SnapshotEntry_Types.h
 *********************************************************************************************************************/
