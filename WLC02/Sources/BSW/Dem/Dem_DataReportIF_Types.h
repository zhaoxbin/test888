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
/*! \addtogroup Dem_DataReportIF
 *  \{
 *  \file       Dem_DataReportIF_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    
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

#if !defined (DEM_DATAREPORTIF_TYPES_H)
#define DEM_DATAREPORTIF_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_Data_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*! Data byte value substituted when callbacks fail to retrieve data */
#define DEM_DATAREPORTIF_INVALID_DATA_PATTERN            (0xffU)

/*! Source from where OBDII FreezeFrame shall be copied */
#define DEM_DATAREPORTIF_SOURCE_OBDII_FF_BUFFER            (0x00U)  /*!< Copy data from OBDII FreezeFrame buffer */
#define DEM_DATAREPORTIF_SOURCE_OBDII_FF_READOUTBUFFER     (0x01U)  /*!< Copy data from ReadoutBuffer */

/*!
 * \defgroup  Dem_DataReportIF_DataElementType Macros encoding data element kind
 * \{
 */
#define DEM_DATAREPORTIF_DATAELEMENT_INTERNAL               (0x00U)  /*!< Internally calculated data element */
#define DEM_DATAREPORTIF_DATAELEMENT_EXTERNAL               (0x01U)  /*!< Externally retrieved data element */
#define DEM_DATAREPORTIF_DATAELEMENT_INVALID                (0xffU)  /*!< Invalid data element kind */
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Union Type for OBD FreezeFrame buffer and OBD ReadOutBuffer */
union Dem_DataReportIF_BufferIndex
{                                                                                                                                /* PRQA S 0750 */ /* MD_MSR_18.4 */
  Dem_DTCReadoutBuffer_HandleType  ReadoutBufferId;        /*!< Index to OBD ReadOutBuffer */           
  uint8                            FreezeFrameIndex;       /*!< Index to OBD FreezeFrame buffer */  
};

/*! Index Type for OBD FreezeFrame buffer and OBD ReadOutBuffer */
typedef union Dem_DataReportIF_BufferIndex Dem_DataReportIF_BufferIndexType;

/*! Structure for DID data readout */
struct Dem_DataReportIF_CopyDidInfoType_s
{
  Dem_Data_DestinationBufferPtrType  DestinationBuffer; /*!< destination buffer context */
  Dem_ConstSharedDataPtrType         SourceBuffer;  /*!< source buffer providing the DID data */
  Dem_MemoryEntry_HandleType         MemoryEntryId;  /*< Id of memory entry holding the DTC data */
  Dem_EventIdType                    EventId;  /*!< EventId for which data is collected */
  uint16                             ReadIndex;  /*!< Current read index from the source buffer */
};

/*! Type for DID data readout */
typedef struct Dem_DataReportIF_CopyDidInfoType_s Dem_DataReportIF_CopyDidInfoType;
/*! Pointer to type for DID data readout */
typedef P2VAR(Dem_DataReportIF_CopyDidInfoType, TYPEDEF, AUTOMATIC) Dem_DataReportIF_CopyDidInfoPtrType;
/*! Non-writable pointer to type for DID data readout */
typedef P2CONST(Dem_DataReportIF_CopyDidInfoType, TYPEDEF, AUTOMATIC) Dem_DataReportIF_ConstCopyDidInfoPtrType;

#endif /* DEM_DATAREPORTIF_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DataReportIF_Types.h
 *********************************************************************************************************************/
