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
/*! \addtogroup Dem_DTCReadoutBuffer
 *  \{
 *  \file       Dem_DTCReadoutBuffer_Types.h
 *  \brief      Diagnostic Event Manager (Dem) Type and Macro definition file
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

#if !defined (DEM_DTCREADOUTBUFFER_TYPES_H)
#define DEM_DTCREADOUTBUFFER_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_SnapshotEntry_Types.h"
#include "Dem_ExtendedEntry_Types.h"
#include "Dem_Cfg_Types.h"
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
/*!
 * \defgroup  Dem_DTCReadoutBuffer_HandleType Dem_DTCReadoutBuffer_HandleType
 * \{
 */
/*! This used for DTCReadoutBuffer handles. */
typedef uint8 Dem_DTCReadoutBuffer_HandleType;

/*!
 * \}
 */

/*!
 * \defgroup  Dem_DTCReadoutBuffer_StatusType Dem_DTCReadoutBuffer_StatusType
 * \{
 */
/*! This type is used to encode the result of a DTC selection */
typedef uint8 Dem_DTCReadoutBuffer_StatusType;

/*!
 * \}
 */

/*! Iterator for extended data record types. */
typedef struct
{
  Dem_ExtendedEntry_IterType ExtendedEntryIter;      /*!< Iterator for the extended entries */
  Dem_EventIdType            EventId;                /*!< Event Id */
  Dem_MemoryEntry_HandleType MemoryEntryId;          /*!< Memory entry handle */
  uint8                      ExtendedEntryIndex;     /*!< Extended entry index */
  uint8                      ExtendedDataNumber;     /*!< The selected extended data number */
  boolean                    ExtendedRecordSelected; /*!< Specifies whether a record is selected or not */
} Dem_DTCReadoutBuffer_ExtendedDataIteratorType;

/*! Identifies a snapshot source */
typedef enum
{
  Dem_DTCReadoutBuffer_SnapshotSource_Obd,        /*!< OBD snapshot */
  Dem_DTCReadoutBuffer_SnapshotSource_Srec,       /*!< Snapshot record source */                                                 /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
  Dem_DTCReadoutBuffer_SnapshotSource_Tmc_Fast,   /*!< Tmc 0x10 <= RecordId <= 0x2F */                                           /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
  Dem_DTCReadoutBuffer_SnapshotSource_Tmc_Normal, /*!< Tmc 0x30 <= RecordId <= 0x4F */                                           /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
  Dem_DTCReadoutBuffer_SnapshotSource_Global,      /*!< Global Snapshot record source */                                         /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
  Dem_DTCReadoutBuffer_SnapshotSource_Invalid     /*!< Not initialize or end of list identifier */                               /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
} Dem_DTCReadoutBuffer_SnapshotSourceType;                                                                                       /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/*! Iterator for snapshot record types. */
typedef struct
{
  Dem_SnapshotEntry_IterType SnapshotEntryIter;   /*!< Iterator for the snapshot entries */
  uint8 RecordNumber;                             /*!< The selected extended data number */
  Dem_DTCReadoutBuffer_SnapshotSourceType Source; /*!< The source of the snapshot */
  Dem_Cfg_ComplexIterType SourceIterator;         /*!< Iterator for the different sources */
  boolean SnapshotSelected;                       /*!< Specifies whether a snapshot is selected or not */
} Dem_DTCReadoutBuffer_SnapshotDataIteratorType;

/*! Pointer to iterator for snapshot record types. */
typedef P2VAR(Dem_DTCReadoutBuffer_SnapshotDataIteratorType, TYPEDEF, AUTOMATIC) Dem_DTCReadoutBuffer_SnapshotDataIteratorPtrType; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
/*! Pointer to iterator for extended data record types. */
typedef P2VAR(Dem_DTCReadoutBuffer_ExtendedDataIteratorType, TYPEDEF, AUTOMATIC) Dem_DTCReadoutBuffer_ExtendedDataIteratorPtrType; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
/*! Pointer to const iterator for snapshot data record types. */
typedef P2CONST(Dem_DTCReadoutBuffer_SnapshotDataIteratorType, TYPEDEF, AUTOMATIC) Dem_DTCReadoutBuffer_SnapshotDataIteratorConstPtrType; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
/*! Pointer to const iterator for extended data record types. */
typedef P2CONST(Dem_DTCReadoutBuffer_ExtendedDataIteratorType, TYPEDEF, AUTOMATIC) Dem_DTCReadoutBuffer_ExtendedDataIteratorConstPtrType; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

#endif /* DEM_DTCREADOUTBUFFER_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCReadoutBuffer_Types.h
 *********************************************************************************************************************/
