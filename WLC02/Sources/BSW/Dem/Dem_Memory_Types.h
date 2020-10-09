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
/*! \addtogroup Dem_Memory
 *  \{
 *  \file       Dem_Memory_Types.h
 *  \brief      Abstraction for multiple event memories.
 *  \details    Facade for all memory related tasks.
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

#if !defined (DEM_MEMORY_TYPES_H)
#define DEM_MEMORY_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_MemState_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Invalid memory index used for 'no index available' */
#define DEM_MEM_INVALID_MEMORY_INDEX             Dem_Cfg_GlobalNvBlockCount()

/*! Initial transaction number of NV transaction state  */
#define DEM_MEMORY_INIT_COMMIT_NUMBER                                          (0x00U)

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
struct Dem_Memory_AllocMemEntriesIterType_s
{
  uint8_least mIdx;    /*!< Current iterator position */
  uint8_least mEndIdx; /*!< Iterator end position */
  Dem_MemState_MemoryInfoPtrType mMemoryInfoPtr; /*!< Pointer to Event Memory management data */
};

/*! Iterator for iterations over all event memory entries in chronological order*/
typedef struct Dem_Memory_AllocMemEntriesIterType_s Dem_Memory_AllocMemEntriesIterType;

struct Dem_Memory_ComplexIterType_s
{
  uint8_least mIdx;    /*!< Current iterator position */
  uint8_least mEndIdx; /*!< Iterator end position */
};

/*! Type for iterations over all event memory entries (Primary and User Defined) */
typedef struct Dem_Memory_ComplexIterType_s Dem_Memory_AllEventMemEntriesIterType;
/*! Type for iterations over memory entries of one memory*/
typedef struct Dem_Memory_ComplexIterType_s Dem_Memory_MemEntryIterType;


#endif /* DEM_MEMORY_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Memory_Types.h
 *********************************************************************************************************************/
