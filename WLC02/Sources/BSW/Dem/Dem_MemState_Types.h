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
/*! \addtogroup Dem_MemState
 *  \{
 *  \file       Dem_MemState_Types.h
 *  \brief      Encapsulate global data stored for an event memory.
 *  \details    File contains type definitions for MemState subcomponent which encapsulate global data stored for an 
 *              event memory. This includes handling chronology for event entries, tracking occupancy, overflow status,
 *              update state etc.
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

#if !defined (DEM_MEMSTATE_TYPES_H)
#define DEM_MEMSTATE_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*! Set flag in memory state which indicate an ongoing commit */
#define DEM_MEMSTATE_COMMIT_STARTED                   (0x80U) 
/*! Reset flag in memory state which indicate an ongoing commit */
#define DEM_MEMSTATE_COMMIT_FINISHED                  (0x7FU)

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Pointer to a chronology list */
typedef CONSTP2VAR(uint8, TYPEDEF, DEM_VAR_NOINIT) Dem_MemState_ChronoStackPtrType;
/*! Pointer to memory size variable */
typedef CONSTP2VAR(uint8, TYPEDEF, DEM_VAR_NOINIT) Dem_MemState_CurrentSizePtrType;

/*! Event Memory management data */
struct Dem_MemState_MemoryInfoType_s
{
  Dem_MemState_ChronoStackPtrType  ChronoPtr;  /*!< Pointer to the chronology list of the memory if available and null pointer otherwise */
  Dem_MemState_CurrentSizePtrType  SizePtr;  /*!< Pointer to the current size variable */
  Dem_Cfg_MemoryIndexType          FirstMemoryIndex;  /*!< First memory block index belonging to the memory */
  Dem_EventIdType                  FirstEvent;  /*!< First event id belonging to the memory */
  Dem_EventIdType                  LastEvent;  /*!< Last event Id belonging to the memory */
  uint8                            MaxSize;  /*!< Maximum number of memory entries or slots for the memory */
  uint8                            MemoryId;  /*!< Handle to identify the event memory */
};

/*! Event Memory management data type */
typedef struct Dem_MemState_MemoryInfoType_s                      Dem_MemState_MemoryInfoType;
/*! Pointer to Event Memory management data */
typedef P2CONST(Dem_MemState_MemoryInfoType, TYPEDEF, DEM_CONST)  Dem_MemState_MemoryInfoPtrType;

#endif /* DEM_MEMSTATE_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemState_Types.h
 *********************************************************************************************************************/
