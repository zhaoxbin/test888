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
/*! \addtogroup Dem_Satellite
 *  \addtogroup Dem_Debounce
 *  \addtogroup Dem_DebounceBase
 *  \{
 *  \file       Dem_DebounceBase_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of DebounceBase subcomponent
 **********************************************************************************************************************/

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

#if !defined (DEM_DEBOUNCEBASE_TYPES_H)
#define DEM_DEBOUNCEBASE_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Own module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DebounceBase_Fwd.h"

                                                           /* Required types */
/* ------------------------------------------------------------------------- */
#include "Dem_SatelliteData_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! debounce algorithm management data type */
typedef struct Dem_DebounceBase_InfoType_s Dem_DebounceBase_InfoType;

/*! Pointer to debounce algorithm management data */
typedef P2VAR(Dem_DebounceBase_InfoType, TYPEDEF, AUTOMATIC) Dem_DebounceBase_InfoPtrType;

/*! Non-writable pointer to debounce algorithm management data */
typedef P2CONST(Dem_DebounceBase_InfoType, TYPEDEF, AUTOMATIC) Dem_DebounceBase_ConstInfoPtrType;

/*! debouncing function pointer for functions without return value */
typedef P2FUNC(void, DEM_CODE, Dem_DebounceBase_VoidFunctionPtr)(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)
  );

/*! debouncing function pointer for functions without return value */
typedef P2FUNC(void, DEM_CODE, Dem_DebounceBase_UpdateMaxFunctionPtr)(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)
  );

/*! debouncing function pointer for functions with boolean return value */
typedef P2FUNC(boolean, DEM_CODE, Dem_DebounceBase_BoolFunctionPtr)(
  CONST(Dem_DebounceBase_InfoPtrType, AUTOMATIC)
  );

/*! debouncing function pointer to commit debouncing result */
typedef P2FUNC(Dem_SatelliteData_DataType, DEM_CODE, Dem_DebounceBase_ResultFunctionPtr)(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC),
  CONST(Dem_SatelliteData_DataType, AUTOMATIC)
  );

/*! debouncing function pointer for functions with debouncing state return value */
typedef P2FUNC(Dem_DebouncingStateType, DEM_CODE, Dem_DebounceBase_StateFunctionPtr)(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC)
  );

/*! debouncing function pointer for functions returning an FDC value */
typedef P2FUNC(Std_ReturnType, DEM_CODE, Dem_DebounceBase_GetFDCFunctionPtr)(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC),
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)
  );

/*! debouncing function pointer to restoring a debounce value */
typedef P2FUNC(Dem_SatelliteData_DataType, DEM_CODE, Dem_DebounceBase_RestoreFunctionPtr)(
  CONST(Dem_DebounceBase_ConstInfoPtrType, AUTOMATIC),
  CONST(Dem_SatelliteData_DataType, AUTOMATIC),
  CONST(sint16, AUTOMATIC),
  CONST(boolean, AUTOMATIC)
  );

/*! debouncing function pointer table */
struct Dem_DebounceFunctionTable_s
{
  Dem_DebounceBase_BoolFunctionPtr       Calculate;                    /*!< debouncing calculation function */
  Dem_DebounceBase_VoidFunctionPtr       Freeze;                       /*!< freeze debouncing function */
  Dem_DebounceBase_VoidFunctionPtr       Reset;                        /*!< reset debouncing function */
  Dem_DebounceBase_StateFunctionPtr      GetDebouncingState;           /*!< get the current debouncing state */
  Dem_DebounceBase_UpdateMaxFunctionPtr  UpdateDebounceValueMax;       /*!< updates the maximum debouncing value.*/
  Dem_DebounceBase_UpdateMaxFunctionPtr  ResetDebounceValueMax;        /*!< resets the maximum debouncing value.*/
  Dem_DebounceBase_GetFDCFunctionPtr     GetFaultDetectionCounter;     /*!< Returns the fault detection counter. */
  Dem_DebounceBase_GetFDCFunctionPtr     GetMaxFaultDetectionCounter;  /*!< Returns the maximum fault detection counter. */
  Dem_DebounceBase_ResultFunctionPtr     GetDebouncingResult;          /*!< Update and return debouncing result*/
  Dem_DebounceBase_RestoreFunctionPtr    RestoreDebounceValue;         /*!< debouncing result function */
};

/*! debouncing function pointer table type */
typedef struct Dem_DebounceFunctionTable_s Dem_DebounceFunctionTableType;
/*! Non-writable pointer to debouncing function pointer table */
typedef P2CONST(Dem_DebounceFunctionTableType, TYPEDEF, DEM_CONST) Dem_DebounceFunctionTablePtrType;


/*! debounce algorithm management data.
 * Data common to all debounce algorithms.
 * \pure */
struct Dem_DebounceBase_InfoType_s
{
  Dem_DebounceFunctionTablePtrType FunctionTable;       /*!< Function pointer table for the debouncing type */
  Dem_EventIdType EventId;                              /*!< debounced event id */
  Dem_EventStatusType MonitorTrigger;                   /*!< Reported/Effective status of the application monitor */
  uint8 State;                                          /*!< See Dem_DebounceBase_InfoState for flag definitions */
};


#endif /* DEM_DEBOUNCEBASE_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DebounceBase_Types.h
 *********************************************************************************************************************/
