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
/*! \ingroup Dem_Satellite
 *  \addtogroup Dem_SatelliteData
 *  \{
 *  \file       Dem_SatelliteData_Types.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Public types of SatelliteData subcomponent
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

#if !defined (DEM_SATELLITEDATA_TYPES_H)
#define DEM_SATELLITEDATA_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_Com_Types.h"
#include "Dem_EventQueue_Types.h"
#include "Dem_DebounceBase_Fwd.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*Bit mapping within SharedStatus in Dem_SatelliteData_Data*/

/*! The first monitor status bit within SharedStatus in Dem_SatelliteData_Data */
#define DEM_SATELLITEDATA_MONITOR_STATUS_POS     0

/*! The number of monitor status bits within SharedStatus in Dem_SatelliteData_Data  */
#define DEM_SATELLITEDATA_MONITOR_STATUS_SIZE    2

/*! The first similar condition status bit within SharedStatus in Dem_SatelliteData_Data */
#define DEM_SATELLITEDATA_SIMILARCONDITION_STATUS_POS     3

/*! The number of similar condition status bits within SharedStatus in Dem_SatelliteData_Data  */
#define DEM_SATELLITEDATA_SIMILARCONDITION_STATUS_SIZE    1

/*! The first debounce status bit within SharedStatus in Dem_SatelliteData_Data  */
#define DEM_SATELLITEDATA_DEBOUNCE_STATUS_POS    4

/*! The number of debounce status bits within SharedStatus in Dem_SatelliteData_Data  */
#define DEM_SATELLITEDATA_DEBOUNCE_STATUS_SIZE   4

/*Bit mapping within SharedData in Dem_SatelliteData_ExtendedData*/

/*! The first monitor status bit within SharedStatus in Dem_SatelliteData_ExtendedData */
#define DEM_SATELLITEDATA_PRESTOREFF_STATUS_POS     0

/*! The number of monitor status bits within SharedStatus in Dem_SatelliteData_ExtendedData  */
#define DEM_SATELLITEDATA_PRESTOREFF_STATUS_SIZE    2

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! The data of a single satellite element related to an event for synchronisation with Dem master.  */
struct Dem_SatelliteData_Data_s
{
  Dem_Debounce_DataType       DebounceData;     /*!< The debounce data. */
  Dem_EventQueue_StatusType   QueueStatus;      /*!< The queue status of this element. */
  uint8                       SharedStatus;     /*!< packed DebounceStatus and MonitorStatus. */
};

/*! Extended data for an event on satellite for synchronisation with Dem master.  */
struct Dem_SatelliteData_ExtendedData_s
{
  uint32 SharedData;     /*!< packed triggers related to event specific operations. */
};


/*! Converts between a Dem_SatelliteData_ExtendedDataType and a raw data type. */
union Dem_SatelliteData_ExtendedData_u
{                                                                                                                                /* PRQA S 0750 */ /* MD_MSR_18.4 */
  volatile struct Dem_SatelliteData_ExtendedData_s Data;     /*!< The detailed data type. */
  volatile Dem_Com_ProcessorWordType Raw;                 /*!< The raw data type intended for queue communication. */
};

/*! Converts between a Dem_SatelliteData_ExtendedDataType and a raw data type. */
typedef union Dem_SatelliteData_ExtendedData_u Dem_SatelliteData_ExtendedDataType;

/*! Converts between a Dem_SatelliteData_DataType and a raw data type. */
union Dem_SatelliteData_Data_u
{                                                                                                                                /* PRQA S 0750 */ /* MD_MSR_18.4 */
  volatile struct Dem_SatelliteData_Data_s Data;     /*!< The detailed data type. */
  volatile Dem_Com_ProcessorWordType Raw;            /*!< The raw data type intended for queue communication. */
};

/*! Converts between a Dem_SatelliteData_DataType and a raw data type. */
typedef union Dem_SatelliteData_Data_u Dem_SatelliteData_DataType;
/*! Reference to modifiable SatelliteData object. */
typedef P2VAR(Dem_SatelliteData_DataType, DEM_VAR_NOINIT, TYPEDEF) Dem_SatelliteData_DataPtrType;
/*! Reference to non-modifiable SatelliteData object. */
typedef P2CONST(Dem_SatelliteData_DataType, DEM_VAR_NOINIT, TYPEDEF) Dem_SatelliteData_ConstDataPtrType;

/*! Data type which performs compile time checks */
struct Dem_SatelliteData_DataSizeCheck_s
{
  /*! Check that Dem_SatelliteData_Data_s fits into one word (uint32). */
  unsigned int Dem_SatelliteData_VerifySizeOfSatelliteData :
    (sizeof(struct Dem_SatelliteData_Data_s) <= sizeof(Dem_Com_ProcessorWordType) ? 1 : -1);
};

#endif /* DEM_SATELLITEDATA_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_SatelliteData_Types.h
 *********************************************************************************************************************/
