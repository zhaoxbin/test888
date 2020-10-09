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
/*! \addtogroup Dem_FilterData
 *  \{
 *  \file       Dem_FilterData_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of FilterData subcomponent
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

#if !defined (DEM_FILTERDATA_IMPLEMENTATION_H)
#define DEM_FILTERDATA_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_FilterData_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Com_Implementation.h"
#include "Dem_DTCReporting_Implementation.h"
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_Cfg_Definitions.h"
#include "Dem_Event_Implementation.h"
#include "Dem_DTC_Implementation.h"
#include "Dem_Memory_Implementation.h"
#include "Dem_UDSStatus_Implementation.h"
#include "Dem_Indicator_Implementation.h"

                                                  /* Subcomponents callbacks */
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \defgroup  Dem_FilterData_FilterFlags  Macros encoding the filter flags of a filter.
 * \{
 */
#define DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK                   (0x01U) /*!< Status mask is used for filtering */
#define DEM_FILTERDATA_FILTERFLAGS_USEFDC                          (0x02U) /*!< FDC is used for filtering */
#define DEM_FILTERDATA_FILTERFLAGS_USESEVERITY                     (0x04U) /*!< Severity is used for filtering */
#define DEM_FILTERDATA_FILTERFLAGS_USEFORMATOBD                    (0x08U) /*!< DTCFormat OBD is used for filtering */
#define DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT          (0x10U) /*!< Filtering for emsission relevant DTCs */

#define DEM_FILTERDATA_FILTERFLAGS_INITIAL                         (0x00U) /*!< Initial value of filter flags */

/*! The inverse of DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK */
#define DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK_MASK              DEM_BIT_MASK(0, DEM_1BYTE)

/*! The inverse of DEM_FILTERDATA_FILTERFLAGS_USEFDC */
#define DEM_FILTERDATA_FILTERFLAGS_USEFDC_MASK                     DEM_BIT_MASK(1, DEM_1BYTE)

/*! The inverse of DEM_FILTERDATA_FILTERFLAGS_USESEVERITY */
#define DEM_FILTERDATA_FILTERFLAGS_USESEVERITY_MASK                DEM_BIT_MASK(2, DEM_1BYTE)

/*! The inverse of DEM_FILTERDATA_FILTERFLAGS_DTCFORMATOBD */
#define DEM_FILTERDATA_FILTERFLAGS_USEFORMATOBD_MASK               DEM_BIT_MASK(3, DEM_1BYTE)

/*! The inverse of DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT */
#define DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT_MASK     DEM_BIT_MASK(4, DEM_1BYTE)
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/
/* Marker for already filtered events for DTC Filter ------------ */
/*! Size of bitfield of already filtered events */
#define DEM_FILTERDATA_FILTEREDEVENTS_SIZE(NumEvents)         (uint16)(((NumEvents)+7)/8)                                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Index of event in bitfield of already filtered events */
#define DEM_FILTERDATA_FILTEREDEVENTS_INDEX(EventId)          (uint16)((EventId)/8)                                              /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Bitmask for bitfield of already filtered events */
#define DEM_FILTERDATA_FILTEREDEVENTS_MASK(EventId)           (uint8)(0x01u << ((uint8)((EventId) % 8)))                         /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_FilterData_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_FilterData_TestFilterSet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_TestFilterSet(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC) FilterId,
  CONST(Dem_FilterData_FilterType, DEM_CODE) Filter
  )
{
  return (boolean)(Dem_FilterData_GetState(FilterId) == Filter);
}

/* ****************************************************************************
 % Dem_FilterData_TestUseStatusMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_TestUseStatusMask(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return (boolean)((Dem_Cfg_GetFilterInfoTable(FilterId).FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK) != 0);
}

/* ****************************************************************************
 % Dem_FilterData_TestUseFdc()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_TestUseFdc(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return (boolean)((Dem_Cfg_GetFilterInfoTable(FilterId).FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USEFDC) != 0);
}

/* ****************************************************************************
 % Dem_FilterData_TestUseSeverity()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_TestUseSeverity(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return (boolean)((Dem_Cfg_GetFilterInfoTable(FilterId).FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USESEVERITY) != 0);
}

/* ****************************************************************************
 % Dem_FilterData_TestUseFormatOBD()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_TestUseFormatOBD(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return (boolean)((Dem_Cfg_GetFilterInfoTable(FilterId).FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USEFORMATOBD) != 0);
}

/* ****************************************************************************
 % Dem_FilterData_TestFilterEmissionRelevant()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_TestFilterEmissionRelevant(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return (boolean)((Dem_Cfg_GetFilterInfoTable(FilterId).FilterFlags & DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT) != 0);
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_FilterData_Private
 * \{
 */

/* ****************************************************************************
 % Dem_FilterData_SetFilterData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_FilterData_SetFilterData(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_FilterData_InfoType, AUTOMATIC)  FilterData
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (FilterId >= Dem_Cfg_GetSizeOfFilterInfoTable())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetFilterInfoTable(FilterId, FilterData);                                                                            /* SBSW_DEM_ARRAY_WRITE_FILTERINFOTABLE */
  }  
}

/* ****************************************************************************
 % Dem_FilterData_GetFilterData()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_InfoType, DEM_CODE) 
Dem_FilterData_GetFilterData(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_Cfg_GetFilterInfoTable(FilterId);
}

/* ****************************************************************************
 % Dem_FilterData_GetState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_FilterType, DEM_CODE)
Dem_FilterData_GetState(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC) FilterId
  )
{
  return Dem_FilterData_GetFilterData(FilterId).FilterState;
}

/* ****************************************************************************
 % Dem_FilterData_GetEventId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_FilterData_GetEventId(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_FilterData_GetFilterData(FilterId).Iterator.EventIndex;
}

/* ****************************************************************************
 % Dem_FilterData_GetChronoIter()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_GetChronoIter(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_FilterData_GetFilterData(FilterId).Iterator.ChronoIter;
}

/* ****************************************************************************
 % Dem_FilterData_GetStatusMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_GetStatusMask(                                                                                                    /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_FilterData_GetFilterData(FilterId).StatusMask;
}

/* ****************************************************************************
 % Dem_FilterData_GetFDC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(sint8, DEM_CODE)
Dem_FilterData_GetFDC(                                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_FilterData_GetFilterData(FilterId).FaultDetectionCounter;
}

/* ****************************************************************************
 % Dem_FilterData_GetMemoryId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_GetMemoryId(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_FilterData_GetFilterData(FilterId).MemoryId;
}

/* ****************************************************************************
 % Dem_FilterData_GetSeverityMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSeverityType, DEM_CODE)
Dem_FilterData_GetSeverityMask(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_FilterData_GetFilterData(FilterId).SeverityMask;
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_GetDTCFilteringStrategy()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_DTCFilteringStrategyType, DEM_CODE)
Dem_FilterData_GetDTCFilteringStrategy(                                                                                          /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_FilterData_GetFilterData(FilterId).FilterDtcStrategy;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_GetDTCFilterFunction()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_FuncPtrType, DEM_CODE)
Dem_FilterData_GetDTCFilterFunction(                                                                                             /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_DTCFilteringStrategyType, AUTOMATIC)  DTCFilteringStrategy
  )
{
  Dem_FilterData_FuncPtrType lDTCFilterFunction;

  switch (DTCFilteringStrategy)
  {
  case Dem_FilterData_FilterChronological:
    lDTCFilterFunction = Dem_FilterData_FilterMemoryChrono;
    break;
  case Dem_FilterData_FilterEventBased:
    lDTCFilterFunction = Dem_FilterData_FilterMemoryByEvent;
    break;
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  case Dem_FilterData_FilterEventBased_PermanentMemory:
    lDTCFilterFunction = Dem_FilterData_FilterPermanentByEvent;
    break;
#endif
  default:
    lDTCFilterFunction = Dem_FilterData_FilterMemoryByEvent;
    break;
    
  }
  return lDTCFilterFunction;
}
#endif

/* ****************************************************************************
 % Dem_FilterData_GetNodeId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_GetNodeId(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_FilterData_GetFilterData(FilterId).NodeId;
}

/* ****************************************************************************
 % Dem_FilterData_GetDTCStatusFilterType()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_J1939DcmDTCStatusFilterType, DEM_CODE)
Dem_FilterData_GetDTCStatusFilterType(                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  return Dem_FilterData_GetFilterData(FilterId).DTCStatusFilterType;
}

/* ****************************************************************************
 % Dem_FilterData_SetState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_SetState(                                                                                                         /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC) FilterId,
  CONST(Dem_FilterData_FilterType, AUTOMATIC) NewState
  )
{
  Dem_FilterData_InfoType lFilterData;

  lFilterData = Dem_FilterData_GetFilterData(FilterId);
  lFilterData.FilterState = NewState;
  Dem_FilterData_SetFilterData(FilterId, lFilterData);
}

/* ****************************************************************************
 % Dem_FilterData_SetFDC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_SetFDC(                                                                                                           /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(sint8, AUTOMATIC)  FDC
  )
{
  Dem_FilterData_InfoType lFilterData;

  lFilterData = Dem_FilterData_GetFilterData(FilterId);
  lFilterData.FaultDetectionCounter = FDC;
  Dem_FilterData_SetFilterData(FilterId, lFilterData);
}

/* ****************************************************************************
 % Dem_FilterData_SetUseStatusMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_SetUseStatusMask(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags | DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK);
}

/* ****************************************************************************
 % Dem_FilterData_ResetUseStatusMask()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_ResetUseStatusMask(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USESTATUSMASK_MASK);
}

/* ****************************************************************************
 % Dem_FilterData_SetUseFdc()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_SetUseFdc(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags | DEM_FILTERDATA_FILTERFLAGS_USEFDC);
}

/* ****************************************************************************
 % Dem_FilterData_ResetUseFdc()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_ResetUseFdc(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USEFDC_MASK);
}

/* ****************************************************************************
 % Dem_FilterData_SetUseSeverity()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_SetUseSeverity(                                                                                                   /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags | DEM_FILTERDATA_FILTERFLAGS_USESEVERITY);
}

/* ****************************************************************************
 % Dem_FilterData_ResetUseSeverity()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_ResetUseSeverity(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USESEVERITY_MASK);
}

/* ****************************************************************************
 % Dem_FilterData_SetUseFormatOBD()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_SetUseFormatOBD(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags | DEM_FILTERDATA_FILTERFLAGS_USEFORMATOBD);
}

/* ****************************************************************************
 % Dem_FilterData_ResetUseFormatOBD()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_ResetUseFormatOBD(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags & DEM_FILTERDATA_FILTERFLAGS_USEFORMATOBD_MASK);
}

/* ****************************************************************************
 % Dem_FilterData_SetFilterEmissionRelevant()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_SetFilterEmissionRelevant(                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags | DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT);
}

/* ****************************************************************************
 % Dem_FilterData_ResetFilterEmissionRelevant()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_FilterData_ResetFilterEmissionRelevant(                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  FilterFlags
  )
{
  return (uint8) (FilterFlags & DEM_FILTERDATA_FILTERFLAGS_FILTEREMISSIONRELEVANT_MASK);
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_ResetReportedEvents()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_ResetReportedEvents(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
#if (DEM_FEATURE_NEED_REPORT_CHRONOLOGICALLY == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (FilterId >= Dem_Cfg_GetSizeOfReportedEventsOfFilter())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    uint16_least lBitfieldIterator;
    for (lBitfieldIterator = 0;
         lBitfieldIterator < DEM_BITFIELDS_IN_REPORTEDEVENTBUFFER;
         lBitfieldIterator++)
    {
      (Dem_Cfg_GetReportedEventsOfFilter(FilterId))[lBitfieldIterator] = 0;                                                      /* SBSW_DEM_ARRAY_WRITE_REPORTEDEVENTSOFFILTER */
    }
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FilterId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_SetEventReported()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_SetEventReported(                                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
#if (DEM_FEATURE_NEED_REPORT_CHRONOLOGICALLY == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (FilterId >= Dem_Cfg_GetSizeOfReportedEventsOfFilter())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    /* identified an Event which matches the filter criteria, mark event as reported */
    Dem_Com_SetBitInBitfield(Dem_Cfg_GetReportedEventsOfFilter(FilterId),                                                        /* SBSW_DEM_POINTER_FORWARD_REPORTED_EVENTS_OF_FILTER */
                             DEM_BITFIELDS_IN_REPORTEDEVENTBUFFER, 
                             EventId);
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FilterId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_TestEventReported()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_TestEventReported(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
  boolean lEventReported;
  lEventReported = FALSE;                                                                                                        /* PRQA S 3198 */ /* MD_DEM_3198_na */

#if (DEM_FEATURE_NEED_REPORT_CHRONOLOGICALLY == STD_ON)
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (FilterId >= Dem_Cfg_GetSizeOfReportedEventsOfFilter())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    /* Check whether bit in the corresponding bit field is set */
    lEventReported = Dem_Com_TestBitInBitfield(Dem_Cfg_GetReportedEventsOfFilter(FilterId),                                      /* SBSW_DEM_POINTER_FORWARD_REPORTED_EVENTS_OF_FILTER */                                                
                                               DEM_BITFIELDS_IN_REPORTEDEVENTBUFFER,
                                               EventId);
  }
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(FilterId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif

  return lEventReported;
}
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_InitDTCFilter()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_FilterData_InitDTCFilter(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  StatusMask
  )
{
  Std_ReturnType lReturnValue;
  Dem_FilterData_InfoType lFilterData;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StatusMask)                                                                                   /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lFilterData = Dem_FilterData_GetFilterData(FilterId);

  switch (MemoryId)
  {
  case DEM_CFG_MEMORYID_PRIMARY:
    lFilterData.MemoryId = MemoryId;
    if ( (StatusMask == 0x04) || (StatusMask == 0x08) || (StatusMask == 0x0C) )
    { /* reporting shall be in chronological order */
      lFilterData.Iterator.ChronoIter = DEM_EVENT_INVALID;
      lFilterData.FilterDtcStrategy = Dem_FilterData_FilterChronological;
    }
    else
    { /* report by event id, set first event index */
      lFilterData.Iterator.EventIndex = Dem_Cfg_GlobalPrimaryFirst();
      lFilterData.FilterDtcStrategy = Dem_FilterData_FilterEventBased;
    }
    lReturnValue = E_OK;
    break;

#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
  case DEM_CFG_MEMORYID_SECONDARY:
    lFilterData.MemoryId = MemoryId;
    if ( (StatusMask == 0x04) || (StatusMask == 0x08) || (StatusMask == 0x0C) )
    { /* reporting shall be in chronological order */
      lFilterData.Iterator.ChronoIter = DEM_EVENT_INVALID;
      lFilterData.FilterDtcStrategy = Dem_FilterData_FilterChronological;
    }
    else
    { /* report by event id, set first event index */
      lFilterData.Iterator.EventIndex = Dem_Cfg_GlobalSecondaryFirst();
      lFilterData.FilterDtcStrategy = Dem_FilterData_FilterEventBased;
    }
    lReturnValue = E_OK;
    break;
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  case DEM_CFG_MEMORYID_PERMANENT:
    lFilterData.MemoryId = MemoryId;
    /* report by event id, set max number of permanent memory entries */
    lFilterData.Iterator.PermanentIndex = Dem_Cfg_GlobalPermanentMaxCount();
    lFilterData.FilterDtcStrategy = Dem_FilterData_FilterEventBased_PermanentMemory;
    lReturnValue = E_OK;
    break;
#endif

  default:
    lReturnValue = E_NOT_OK;
    break;
  }

  Dem_FilterData_SetFilterData(FilterId, lFilterData); 

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_InitFilterFlagsAndMasks()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_InitFilterFlagsAndMasks(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  StatusMask,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(boolean, AUTOMATIC)  FilterForOBD,
  CONST(boolean, AUTOMATIC)  FilterWithSeverity,
  CONST(Dem_DTCSeverityType, AUTOMATIC)  SeverityMask,
  CONST(boolean, AUTOMATIC)  FilterForFDC
  )
{
  Dem_FilterData_InfoType lFilterData;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DTCFormat)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lFilterData = Dem_FilterData_GetFilterData(FilterId);

  /* Check if filter shall ignore Dtc status or not */
  if (StatusMask == 0x00)
  {
    lFilterData.FilterFlags = Dem_FilterData_ResetUseStatusMask(lFilterData.FilterFlags);
  }
  else
  {
    lFilterData.StatusMask = StatusMask & Dem_Cfg_GlobalStatusMask();
    lFilterData.FilterFlags = Dem_FilterData_SetUseStatusMask(lFilterData.FilterFlags);
  }

  /* Check if filter shall use severity */
  if (FilterWithSeverity == TRUE)
  {
    lFilterData.SeverityMask = SeverityMask & Dem_Cfg_GlobalSeverityMask();
    lFilterData.FilterFlags = Dem_FilterData_SetUseSeverity(lFilterData.FilterFlags);
  }
  else
  {
    lFilterData.FilterFlags = Dem_FilterData_ResetUseSeverity(lFilterData.FilterFlags);
  }

  /* Check if filter shall use fault detection counter */
  if (FilterForFDC == TRUE)
  {
    lFilterData.FilterFlags = Dem_FilterData_SetUseFdc(lFilterData.FilterFlags);
  }
  else
  {
    lFilterData.FilterFlags = Dem_FilterData_ResetUseFdc(lFilterData.FilterFlags);
  }

  /* Check if filtering for emission relevant DTCs was requested */
  if (FilterForOBD == TRUE)
  {
    lFilterData.FilterFlags = Dem_FilterData_SetFilterEmissionRelevant(lFilterData.FilterFlags);
  }
  else
  {
    lFilterData.FilterFlags = Dem_FilterData_ResetFilterEmissionRelevant(lFilterData.FilterFlags);
  }

  /* Check if output format of DTCs shall be OBD */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if (DTCFormat == DEM_DTC_FORMAT_OBD)
  {
    lFilterData.FilterFlags = Dem_FilterData_SetUseFormatOBD(lFilterData.FilterFlags);
  }
  else
  {
    lFilterData.FilterFlags = Dem_FilterData_ResetUseFormatOBD(lFilterData.FilterFlags);
  }
#endif
  Dem_FilterData_SetFilterData(FilterId, lFilterData); 
 }                                                                                                                                /* PRQA S 6050, 6060 */ /* MD_MSR_STCAL, MD_MSR_STPAR */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_FilterForEventMatch
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Std_ReturnType, DEM_CODE)
Dem_FilterData_FilterForEventMatch(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  uint8    lEventStatus;

  if (Dem_Cfg_EventUdsDtc(EventId) == DEM_CFG_DTC_UDS_INVALID)
  {
    return E_NOT_OK;
  }
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  if (EventId != Dem_Cfg_GetMasterEvent(EventId))
  {
    return E_NOT_OK;
  }
# endif
  if ( (Dem_DTC_TestDtcAvailableInVariant(EventId) == FALSE)                                                                     /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || ((Dem_DTC_TestDtcAvailable(EventId) == FALSE)
      && (Dem_DTC_TestStoredStatus(EventId) == FALSE))
    || ( (Dem_DTC_TestDtcSuppression(EventId) == TRUE)
# if (DEM_CFG_REPORT_SUPPRESSED_DTCS_IN_19_0A == STD_ON)
      && ((Dem_FilterData_TestUseStatusMask(FilterId) == TRUE)
        ||(Dem_FilterData_GetMemoryId(FilterId) != DEM_CFG_MEMORYID_PRIMARY))
# endif
       ))
  {
    /* Suppressed DTCs are skipped */
    return E_NOT_OK;
  }
# if (DEM_FEATURE_NEED_OBD == STD_ON)
  if ( (Dem_FilterData_TestUseFormatOBD(FilterId) == TRUE)                                                                       /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    || (Dem_FilterData_TestFilterEmissionRelevant(FilterId) == TRUE))
  {
    /* Filter specifically for OBD DTCs */
    if (Dem_Cfg_EventObdRelated(EventId) == FALSE)
    { 
      /* skip non-OBD DTCs */
      return E_NOT_OK;
    }
  }
  else
  { 
    /* Do not filter for OBD DTCs, all DTCs pass */
    if ( (Dem_DTCReporting_TestObdHideOccurrences() == TRUE)                                                                     /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
      && (Dem_Cfg_EventSignificance(EventId) == DEM_CFG_EVENT_SIGNIFICANCE_OCCURRENCE)
      && (Dem_Cfg_EventObdRelated(EventId) == TRUE))
    { 
      /* Special case - skip Dependent OBD DTCs */
      return E_NOT_OK;
    }
  }
# endif

  lEventStatus = Dem_DTC_ApplyExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));

  if ( (Dem_FilterData_TestUseStatusMask(FilterId) == TRUE)
    && ((Dem_FilterData_GetStatusMask(FilterId) & lEventStatus) == 0))
  {
    /* Skip DTCs not matching the requested status mask */
    return E_NOT_OK;
  }

  if ( (Dem_FilterData_TestUseSeverity(FilterId) == TRUE)
    && ((Dem_FilterData_GetSeverityMask(FilterId) & Dem_Cfg_EventSeverity(EventId)) == 0))
  { /* Skip DTCs not matching the requested severity */
    return E_NOT_OK;
  }

  if (Dem_FilterData_TestUseFdc(FilterId) == TRUE)
  {
    Std_ReturnType lGetFdcReturnValue;
    sint8 lFdc;

    lGetFdcReturnValue = Dem_DTC_GetFaultDetectionCounter(EventId, &lFdc);                                                       /* SBSW_DEM_POINTER_FORWARD_STACK */

    if (lGetFdcReturnValue != E_OK)
    { /* If FDC cannot be retrieved, the DTC does not match */
      return E_NOT_OK;
    }

    if ( (lFdc <= 0)
      || (lFdc == 0x7f))
    { /* skip passed, passing and qualified failed DTCs */
      return E_NOT_OK;
    }
    else
    {
      /* store the matching FDC for later */
      Dem_FilterData_SetFDC(FilterId, lFdc);
    }
  }

  /* If all tests pass, keep this DTC for processing */
  return E_OK;
}                                                                                                                                /* PRQA S 2006, 6010, 6030, 6050, 6080 */ /* MD_DEM_14.7, MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) 
/* ****************************************************************************
 % Dem_FilterData_FilterMemoryByEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_FilterData_FilterMemoryByEvent(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  Dem_EventIdType lEventId;
  Dem_EventIdType lReturnValue;

  lEventId = Dem_FilterData_GetEventId(FilterId);
  lReturnValue = DEM_EVENT_INVALID;

  /* if last EventId is not valid or was still analyzed skip the filtering */
  if (lEventId != DEM_EVENT_INVALID)
  {
    Dem_FilterData_InfoType lFilterData;
    Dem_EventIdType lEventIdLast;

    lEventIdLast = Dem_Memory_GetLastEvent(Dem_FilterData_GetMemoryId(FilterId));
    /* iterate through the EventIds and check filter criteria */
    for (; lEventId <= lEventIdLast; lEventId++)
    {
# if (DEM_FEATURE_NEED_REPORT_CHRONOLOGICALLY == STD_ON)
      /* take event into account if it was not reported before */
      if (Dem_FilterData_TestEventReported(FilterId, lEventId) == FALSE)
# endif
      {
        /* EventId was not reported before, proceed */
        if (Dem_FilterData_FilterForEventMatch(FilterId, lEventId) == E_OK)
        {
          /* identified an Event which matches the filter criteria */
          lReturnValue = lEventId;
          break;
        }
      }
    }

    lFilterData = Dem_FilterData_GetFilterData(FilterId);

    if (lEventId >= lEventIdLast)
    { /* last EventId has been processed */
      lFilterData.Iterator.EventIndex = DEM_EVENT_INVALID;
    }
    else
    { /* write back the next event to process */
      lFilterData.Iterator.EventIndex = (Dem_EventIdType)(lEventId + 1);
    }

    Dem_FilterData_SetFilterData(FilterId, lFilterData); 
  }
  /* else lReturnValue = DEM_EVENT_INVALID initially set */

  return lReturnValue;
}                                                                                                                                /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if ((DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON))
/* ****************************************************************************
 % Dem_FilterData_FilterPermanentByEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_FilterData_FilterPermanentByEvent(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  Dem_FilterData_InfoType lFilterData;
  uint8 lPermanentIndex;
  Dem_EventIdType lPermanentEventId;

  lFilterData = Dem_FilterData_GetFilterData(FilterId);
  lPermanentIndex = lFilterData.Iterator.PermanentIndex;
  lPermanentEventId = DEM_EVENT_INVALID;

  /* if last EventId is not valid or was still analysed skip the filtering */
  while (lPermanentIndex != 0)
  {
    --lPermanentIndex;

    if (DEM_ESM_TEST_PERMANENT_VISIBLE(Dem_Mem_PermanentGetStatus(lPermanentIndex)) == TRUE)
    { /* Visible Event identified, return it and stop processing */
      lPermanentEventId = Dem_Mem_PermanentGetEvent(lPermanentIndex);
      if (lPermanentEventId != DEM_EVENT_INVALID)
      {
        if  ((Dem_Event_TestMilSupport(lPermanentEventId) == TRUE) && (Dem_DTC_TestDtcSuppressed(lPermanentEventId) == FALSE))    /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        {
          break;
        }
        else
        {
          /*Invalidate return value for this entry*/
          lPermanentEventId = DEM_EVENT_INVALID;
        }
      }
    }
  }

  /* store current position in permanent memory */
  lFilterData.Iterator.PermanentIndex = lPermanentIndex;
  Dem_FilterData_SetFilterData(FilterId, lFilterData);

  return lPermanentEventId;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_FilterMemoryChrono
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(Dem_EventIdType, DEM_CODE)
Dem_FilterData_FilterMemoryChrono(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  Dem_EventIdType lEventId;
  Dem_FilterData_InfoType lFilterData;

# if (DEM_FEATURE_NEED_REPORT_CHRONOLOGICALLY == STD_ON)
  uint8 lMemoryId;
  uint8 lStoredChronoIter;
  Dem_Memory_AllocMemEntriesIterType lStoredEventsIter;

  lStoredChronoIter = Dem_FilterData_GetChronoIter(FilterId);
  lEventId = DEM_EVENT_INVALID;
  lMemoryId = Dem_FilterData_GetMemoryId(FilterId);
    
  if (lStoredChronoIter == 0)
  {
    /* index set to 0 indicates that the filter was reset */
    Dem_Memory_AllocMemEntriesChrono_IterInit(lMemoryId, &lStoredEventsIter);                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
  }
  else
  {
    /* last stored index loaded, set and increment it*/
    Dem_Memory_AllocMemEntriesChrono_IterResume(lMemoryId, lStoredChronoIter, &lStoredEventsIter);                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
  }

  for (; Dem_Memory_AllocMemEntriesChrono_IterExists(&lStoredEventsIter) == TRUE;                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_Memory_AllocMemEntriesChrono_IterNext(&lStoredEventsIter))                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    /* Get EventId for current index and marker if event was reported before */
    lEventId = 
        Dem_MemoryEntry_GetEventId(Dem_MemoryEntry_GetId(
        Dem_Memory_AllocMemEntriesChrono_IterGetMemoryIndex(&lStoredEventsIter)));                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    /* verify that a valid EventId was returned */
    if (Dem_Event_TestValidHandle(lEventId) == TRUE)
    {
      /* EventId was not reported before, proceed */
      if (Dem_FilterData_FilterForEventMatch(FilterId, lEventId) == E_OK)
      {
        /* identified an Event which matches the filter criteria, mark event as reported */
        Dem_FilterData_SetEventReported(FilterId, lEventId);
        break;
      }
      else
      { /* No filter match, continue with loop */
        lEventId = DEM_EVENT_INVALID;
      }
    }
  }
  Dem_Memory_AllocMemEntriesChrono_IterNext(&lStoredEventsIter);                                                                 /* SBSW_DEM_CALL_ITERATOR_POINTER */
  lFilterData = Dem_FilterData_GetFilterData(FilterId);
  /* If end of chrono stack is reached, switch to filter by event id */
  if (Dem_Memory_AllocMemEntriesChrono_IterExists(&lStoredEventsIter) == FALSE)                                                  /* SBSW_DEM_CALL_ITERATOR_POINTER */
  {
    lFilterData.Iterator.EventIndex = Dem_Memory_GetFirstEvent(Dem_FilterData_GetMemoryId(FilterId));
    lFilterData.FilterDtcStrategy = Dem_FilterData_FilterEventBased;
    Dem_FilterData_SetFilterData(FilterId, lFilterData);

    if (lEventId == DEM_EVENT_INVALID)
    { /* no valid match, proceed with filtering by EventId */
      lEventId = Dem_FilterData_FilterMemoryByEvent(FilterId);
    }
  }
  else
  {
    /* store current position of chrono stack */
    lFilterData.Iterator.ChronoIter = Dem_Memory_AllocMemEntriesChrono_IterGet(&lStoredEventsIter);                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
    Dem_FilterData_SetFilterData(FilterId, lFilterData);
  }
# else
  lFilterData = Dem_FilterData_GetFilterData(FilterId);

  lFilterData.Iterator.EventIndex = Dem_Memory_GetFirstEvent(Dem_FilterData_GetMemoryId(FilterId));
  lFilterData.FilterDtcStrategy = Dem_FilterData_FilterEventBased;
  Dem_FilterData_SetFilterData(FilterId, lFilterData);
  lEventId = Dem_FilterData_FilterMemoryByEvent(FilterId);
# endif
  return lEventId;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_CountMatchesInPermanentMemory
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_FilterData_CountMatchesInPermanentMemory(
  void
  )
{
  uint16 lNumberOfEvents;

  lNumberOfEvents = 0;

# if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  {
    uint8 lPermanentIndex;
    lPermanentIndex = Dem_Cfg_GlobalPermanentMaxCount();

    /* scan the permanent memory for visible events */
    while (lPermanentIndex != 0)
    {
      --lPermanentIndex;
      if (DEM_ESM_TEST_PERMANENT_VISIBLE(Dem_Mem_PermanentGetStatus(lPermanentIndex)) == TRUE)
      {
        if ( (Dem_Mem_PermanentGetEvent(lPermanentIndex) != DEM_EVENT_INVALID)                                                   /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
          && (Dem_Event_TestMilSupport(Dem_Mem_PermanentGetEvent(lPermanentIndex)) == TRUE)
          && (Dem_DTC_TestDtcSuppressed(Dem_Mem_PermanentGetEvent(lPermanentIndex)) == FALSE))
        {
          ++lNumberOfEvents;
        }
      }
    }
  }
# endif

  return lNumberOfEvents;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_CountMatchesInEventMemory
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_FilterData_CountMatchesInEventMemory(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  uint16 lNumberOfEvents;
  Dem_EventIdType lEventId;
  uint8 lMemoryId;

  lNumberOfEvents = 0;
  lMemoryId = Dem_FilterData_GetMemoryId(FilterId);

  if (Dem_Memory_GetFirstEvent(lMemoryId) != DEM_EVENT_INVALID)                                                                  /* PRQA S 3355, 3358 */ /* MD_DEM_13.7, MD_DEM_13.7 */
  {
    /* at least one event is available which may match the filter criteria */
    for (lEventId = Dem_Memory_GetFirstEvent(lMemoryId);
          lEventId <= Dem_Memory_GetLastEvent(lMemoryId);
          ++lEventId)
    {
      if (Dem_FilterData_FilterForEventMatch(FilterId, lEventId) == E_OK)
      {
        ++lNumberOfEvents;
      }
    }
  }
  return lNumberOfEvents;
}
#endif

#if ( (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) || (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON) )
/* ****************************************************************************
 % Dem_FilterData_TestEventMatchesJ1939DTCFilter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_TestEventMatchesJ1939DTCFilter(
  CONST(Dem_J1939DcmDTCStatusFilterType, AUTOMATIC)  DTCStatusFilterType,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  boolean lEventMatch;
  lEventMatch = FALSE;

  /* Does the event support a J1939Dtc */
  if (Dem_Cfg_EventJ1939Dtc(EventId) != DEM_CFG_DTC_J1939_INVALID)
  {
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    /* don't match dependent combined events */
    if (Dem_Cfg_GetMasterEvent(EventId) == EventId)
# endif
    {
      if (Dem_DTC_TestDtcSuppressed(EventId) == FALSE)
      {
        uint8 lEventStatus;
        Dem_Cfg_EventJ1939NodeIterType lNodeIter;

        /* filter event only if it is linked to the requested node */
        for (Dem_Cfg_EventJ1939NodeIterInit(EventId, &lNodeIter);                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE;                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
             Dem_Cfg_EventJ1939NodeIterNext(&lNodeIter))                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          if (NodeId == Dem_Cfg_EventJ1939NodeIterGet(&lNodeIter))                                                               /* SBSW_DEM_CALL_ITERATOR_POINTER */
          {
            break;
          }
        }
        if (Dem_Cfg_EventJ1939NodeIterExists(&lNodeIter) == TRUE)                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
        {
          lEventStatus = Dem_DTC_ApplyExternalOnlyStatus(EventId, Dem_DTC_GetDTCStatus(EventId));

          switch (DTCStatusFilterType)
          {
          case DEM_FILTERDATA_J1939FILTER_ACTIVE:
            if (DEM_DTC_TEST_J1939_STATUS_ADTC(lEventStatus) == TRUE)
            {
              lEventMatch = TRUE;
            }
            break;

          case DEM_FILTERDATA_J1939FILTER_PREVIOUSLY_ACTIVE:
            if (DEM_DTC_TEST_J1939_STATUS_PADTC(lEventStatus) == TRUE)
            {
              lEventMatch = TRUE;
            }
            break;

          case DEM_FILTERDATA_J1939FILTER_PENDING:
            if (Dem_UDSStatus_Test_PDTC(lEventStatus) == TRUE)
            {
              lEventMatch = TRUE;
            }
            break;

          case DEM_FILTERDATA_J1939FILTER_CURRENTLY_ACTIVE:
            if (Dem_UDSStatus_Test_TF(lEventStatus) == TRUE)
            {
              lEventMatch = TRUE;
            }
            break;

          default:
            /* lEventMatch == FALSE already set */
            break;
          }
        }
      }
    }
  }

  return lEventMatch;
}                                                                                                                                /* PRQA S 6030, 6050, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) || (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON) */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_FilterData_Public
 * \{
 */

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) )
/* ****************************************************************************
 % Dem_FilterData_InitDefault()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_FilterData_InitDefault(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  Dem_FilterData_InfoType lFilterData;
  lFilterData = Dem_FilterData_GetFilterData(FilterId);

  lFilterData.FilterState = DEM_FILTERDATA_FILTER_INIT;
  lFilterData.MemoryId = DEM_CFG_MEMORYID_INVALID;
  lFilterData.Iterator.EventIndex = DEM_EVENT_INVALID;
# if (DEM_CFG_SUPPORT_DCM == STD_ON)
  lFilterData.StatusMask = 0x00;
  lFilterData.SeverityMask = DEM_SEVERITY_NO_SEVERITY;
  lFilterData.FaultDetectionCounter = 0x00;
  lFilterData.FilterDtcStrategy = Dem_FilterData_FilterEventBased;
# endif
# if ( (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) )
  lFilterData.NodeId = DEM_CFG_J1939_NODE_INVALID;
  lFilterData.DTCStatusFilterType = 0;
# endif

  Dem_FilterData_SetFilterData(FilterId, lFilterData);
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_SetDTCFilter()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_FilterData_SetDTCFilter(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  DTCStatusMask,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(boolean, AUTOMATIC)  FilterForOBD,
  CONST(boolean, AUTOMATIC)  FilterWithSeverity,
  CONST(Dem_DTCSeverityType, AUTOMATIC)  DTCSeverityMask,
  CONST(boolean, AUTOMATIC)  FilterForFDC
  )
{
  Std_ReturnType lReturnValue;

  lReturnValue = Dem_FilterData_InitDTCFilter(FilterId, MemoryId, DTCStatusMask);

  if (lReturnValue == E_OK)
  {
    /* Clear list of identified and reported events */
    Dem_FilterData_ResetReportedEvents(FilterId);

    Dem_FilterData_SetState(FilterId, DEM_FILTERDATA_FILTER_DTC);
    Dem_FilterData_InitFilterFlagsAndMasks(FilterId,
                                           DTCStatusMask,
                                           DTCFormat,
                                           FilterForOBD,
                                           FilterWithSeverity,
                                           DTCSeverityMask,
                                           FilterForFDC);
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6060 */ /* MD_MSR_STPAR */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_GetNextFilteredDTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_FilterData_GetNextFilteredDTC(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lNextEvent;

  lNextEvent = Dem_FilterData_GetDTCFilterFunction(Dem_FilterData_GetDTCFilteringStrategy(FilterId))(FilterId);                 /* SBSW_DEM_CALL_DTCFILTER_FPTR */

  if (lNextEvent == DEM_EVENT_INVALID)
  {
    lReturnValue = DEM_NO_SUCH_ELEMENT;
  }
  else
  {
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
    if (Dem_FilterData_TestUseFormatOBD(FilterId) == TRUE)
    {
      FilterResult->DTC = (uint32)(((uint32)Dem_Cfg_EventObdDtc(lNextEvent)) << 8);                                              /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    else
#endif
    {
      FilterResult->DTC = Dem_Cfg_EventUdsDtc(lNextEvent);                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }

    FilterResult->DTCStatus = (uint8)(Dem_DTC_ApplyExternalOnlyStatus(                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      lNextEvent,
      Dem_DTC_GetDTCStatus(lNextEvent)) & Dem_Cfg_GlobalStatusMask()
    );

    if (Dem_FilterData_TestUseFdc(FilterId) == TRUE)
    {
      FilterResult->FDC = Dem_FilterData_GetFDC(FilterId);                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }

    if (Dem_FilterData_TestUseSeverity(FilterId) == TRUE)
    {
      FilterResult->Severity = Dem_Cfg_EventSeverity(lNextEvent);                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      FilterResult->FunctionalUnit = Dem_Cfg_EventFunctionalUnit(lNextEvent);                                                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
    lReturnValue = E_OK;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_CountMatchingDTCs
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_FilterData_CountMatchingDTCs(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  uint16                      lNumberOfEvents;

  switch (Dem_FilterData_GetMemoryId(FilterId))
  {
  case DEM_CFG_MEMORYID_PERMANENT:
    lNumberOfEvents = Dem_FilterData_CountMatchesInPermanentMemory();
    break;

  case DEM_CFG_MEMORYID_PRIMARY:
  case DEM_CFG_MEMORYID_SECONDARY:
    lNumberOfEvents = Dem_FilterData_CountMatchesInEventMemory(FilterId);
    break;

  default:
    /* no other supported memory can contain DTCs */
    lNumberOfEvents = 0;
    break;
  }

  return lNumberOfEvents;
}   
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_SetFirstDTCWithLampStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_FilterData_SetFirstDTCWithLampStatus(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  NodeId
  )
{
  Dem_FilterData_InfoType lFilterData;

  lFilterData = Dem_FilterData_GetFilterData(FilterId);
  lFilterData.Iterator.EventIndex = Dem_Cfg_GlobalPrimaryFirst();
  lFilterData.NodeId = NodeId;

  lFilterData.FilterState = DEM_FILTERDATA_FILTER_J1939DTCLAMP;
  
  Dem_FilterData_SetFilterData(FilterId, lFilterData);  
}   
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_GetNextDTCWithLampStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_FilterData_GetNextDTCWithLampStatus(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
  )
{
  Dem_FilterData_InfoType lFilterData;
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;

  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lFilterData = Dem_FilterData_GetFilterData(FilterId);
  lEventId = lFilterData.Iterator.EventIndex;

  /* if last EventId is not valid or was still analyzed skip the filtering */
  if (lEventId != DEM_EVENT_INVALID)
  {
    Dem_EventIdType lEventIdLast;

    lEventIdLast = Dem_Cfg_GlobalPrimaryLast();
    /* iterate through the EventIds and check filter criteria */
    for (; lEventId <= lEventIdLast; lEventId++)
    {
      if (Dem_Cfg_EventJ1939Dtc(lEventId) == DEM_CFG_DTC_J1939_INVALID)
      { /* Don't match non-J1939 events */
        continue;                                                                                                                /* PRQA S 0770 */ /* MD_DEM_14.5 */
      }
      if (Dem_DTC_TestDtcSuppressed(lEventId) == TRUE)
      { /* Don't match suppressed events */
        continue;                                                                                                                /* PRQA S 0770 */ /* MD_DEM_14.5 */
      }
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
      if (lEventId != Dem_Cfg_GetMasterEvent(lEventId))
      { /* Don't match dependent combined events */
        continue;                                                                                                                /* PRQA S 0770 */ /* MD_DEM_14.5 */
      }
# endif

      /*Get lamp status*/
      lReturnValue = Dem_Indicator_CalculateEventJ1939LampStatus(lEventId, lFilterData.NodeId, FilterResult);                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      if (lReturnValue == E_OK)
      {
        /* Get OCC and DTC */
        FilterResult->DTC = Dem_Cfg_EventJ1939Dtc(lEventId);                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
        FilterResult->OccurrenceCounter = Dem_Util_J1939OccurrenceCounter(lEventId);                                             /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

        break;
      }
    }

    if (lEventId > lEventIdLast)
    { /* last EventId has been processed */
      lFilterData.Iterator.EventIndex = DEM_EVENT_INVALID;
    }
    else
    { /* write back the EventId (which was raised by 1 for the next repetition) */
      lFilterData.Iterator.EventIndex = (Dem_EventIdType)(lEventId + 1);
    }

    Dem_FilterData_SetFilterData(FilterId, lFilterData);
  } /* (lEventId != DEM_EVENT_INVALID) */
  /* else return value DEM_NO_SUCH_ELEMENT initially set */

  return lReturnValue;
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_SetJ1939DTCFilter()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_FilterData_SetJ1939DTCFilter(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_J1939DcmDTCStatusFilterType, AUTOMATIC)  DTCStatusFilter,
  CONST(Dem_DTCKindType, AUTOMATIC)  DTCKind,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONSTP2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_J1939DCM_DATA)  LampStatus
  )
{
  Std_ReturnType lReturnValue;
  Dem_FilterData_InfoType lFilterData;

  lReturnValue = E_OK;
  lFilterData = Dem_FilterData_GetFilterData(FilterId);

  if (DTCKind == DEM_DTC_KIND_ALL_DTCS)
  {
    uint8 lDTCStatusFilterType;

    /* Set the first index dependent on the requested DTC status and configuration */
    switch (DTCStatusFilter)
    {
      case DEM_J1939DTC_PENDING:
        lDTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_PENDING;
        break;
      case DEM_J1939DTC_ACTIVE:
        lDTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_ACTIVE;
        break;
      case DEM_J1939DTC_PREVIOUSLY_ACTIVE:
        lDTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_PREVIOUSLY_ACTIVE;
        break;
      case DEM_J1939DTC_CURRENTLY_ACTIVE:
        lDTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_CURRENTLY_ACTIVE;
        break;
      default:
        lDTCStatusFilterType = 0;
        lReturnValue = E_NOT_OK;
        break;
    }

    if (lReturnValue == E_OK)
    {
      lFilterData.DTCStatusFilterType = lDTCStatusFilterType;

      /* Dispatch the Event target */
      switch (MemoryId)
      {
        case DEM_CFG_MEMORYID_PRIMARY:
          lFilterData.MemoryId = MemoryId;
          lFilterData.Iterator.EventIndex = Dem_Cfg_GlobalPrimaryFirst();
          break;

# if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
        case DEM_CFG_MEMORYID_SECONDARY:
          lFilterData.MemoryId = MemoryId;
          lFilterData.Iterator.EventIndex = Dem_Cfg_GlobalSecondaryFirst();
          break;
# endif

        default:
          lReturnValue = E_NOT_OK;
          break;
      }

      if (lReturnValue == E_OK)
        lFilterData.NodeId = NodeId;

        /* calculate node related lamp status */
      *LampStatus = Dem_Indicator_CalculateGlobalJ1939LampStatus(NodeId);                                                        /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    }
  }
  else /* DTCKind != DEM_DTC_KIND_ALL_DTCS */
  { /* Wrong filter */ 
    lReturnValue = E_NOT_OK;
  }

  lFilterData.FilterState = DEM_FILTERDATA_FILTER_J1939DTC;

  Dem_FilterData_SetFilterData(FilterId, lFilterData); 
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6060 */ /* MD_MSR_STCAL, MD_MSR_STPAR */
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_GetNumberOfFilteredJ1939DTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_FilterData_GetNumberOfFilteredJ1939DTC(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  )
{
  uint16 lNumberOfFilteredDTC;
  Dem_EventIdType lEventId;
  Dem_FilterData_InfoType lFilterData;

  lFilterData = Dem_FilterData_GetFilterData(FilterId);
  lNumberOfFilteredDTC = 0;

  /* iterate through the EventIds and check filter criteria */
  for (lEventId = Dem_Memory_GetFirstEvent(lFilterData.MemoryId);
       lEventId <= Dem_Memory_GetLastEvent(lFilterData.MemoryId);
       lEventId++)
  {
    if (Dem_FilterData_TestEventMatchesJ1939DTCFilter(lFilterData.DTCStatusFilterType, lFilterData.NodeId, lEventId) == TRUE)
    {
      lNumberOfFilteredDTC++;
    }
  }

  return lNumberOfFilteredDTC;
}   
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_GetNextFilteredJ1939DTC
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_FilterData_GetNextFilteredJ1939DTC(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
  )
{
  Std_ReturnType lReturnValue;
  Dem_EventIdType lEventId;
  Dem_FilterData_InfoType lFilterData;

  lFilterData = Dem_FilterData_GetFilterData(FilterId);
  lReturnValue = DEM_NO_SUCH_ELEMENT;
  lEventId = lFilterData.Iterator.EventIndex;

  /* if last EventId is not valid or was still analyzed skip the filtering */
  if (lEventId != DEM_EVENT_INVALID)
  {
    Dem_EventIdType lEventIdLast;

    lEventIdLast = Dem_Memory_GetLastEvent(lFilterData.MemoryId);

    /* iterate through the EventIds and check filter criteria */
    for (; lEventId <= lEventIdLast; ++lEventId)
    {
      if (Dem_FilterData_TestEventMatchesJ1939DTCFilter(lFilterData.DTCStatusFilterType, lFilterData.NodeId, lEventId) == TRUE)
      {
        /* identified an Event which matches the filter criteria */
        break;
      }
    }

    if (lEventId > lEventIdLast)
    { /* last EventId has been processed */
      lFilterData.Iterator.EventIndex = DEM_EVENT_INVALID;
    }
    else
    { /* write back the EventId ( which was raised by 1 for the next repetition) */
      lFilterData.Iterator.EventIndex = (Dem_EventIdType)(lEventId + 1);
      /* Only EventIds with a valid DTC number should be processed here, so the EventId->DTC mapping will return always a valid DTC number */
      FilterResult->DTC = Dem_Cfg_EventJ1939Dtc(lEventId);                                                                       /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      FilterResult->OccurrenceCounter = Dem_Util_J1939OccurrenceCounter(lEventId);                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
      lReturnValue = E_OK;
    }

    Dem_FilterData_SetFilterData(FilterId, lFilterData);  
  }
  /* else lReturnValue = DEM_NO_SUCH_ELEMENT initially set */
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON)
/* ****************************************************************************
 % Dem_FilterData_GetDiagnosticReadiness
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_FilterData_GetDiagnosticReadiness(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONSTP2VAR(Dem_J1939DcmDiagnosticReadiness1Type, AUTOMATIC, DEM_J1939DCM_DATA)  DiagnosticReadiness
  )
{
  Dem_FilterData_InfoType lFilterData;
  uint8 lNumberOfFilteredDTC;
  Dem_EventIdType lEventId;

  DiagnosticReadiness->OBDCompliance = Dem_Cfg_GlobalObdRequirements();                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DiagnosticReadiness->ContinuouslyMonitoredSystemsSupport_Status = 0;                                                           /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DiagnosticReadiness->NonContinuouslyMonitoredSystemsSupport = 0;                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  DiagnosticReadiness->NonContinuouslyMonitoredSystemsStatus = 0;                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

  /* set DTC filter for active DTCs */
  lFilterData = Dem_FilterData_GetFilterData(FilterId);
  lFilterData.DTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_ACTIVE;
  lFilterData.NodeId = NodeId;
  
  /* get number of active DTCs */
  lNumberOfFilteredDTC = 0;
  for (lEventId = Dem_Cfg_GlobalPrimaryFirst();
       lEventId <= Dem_Cfg_GlobalPrimaryLast();
       ++lEventId)
  {
    if (Dem_FilterData_TestEventMatchesJ1939DTCFilter(lFilterData.DTCStatusFilterType, lFilterData.NodeId, lEventId) == TRUE)
    {
      lNumberOfFilteredDTC++;
      if (lNumberOfFilteredDTC == 250)
      {
        break;
      }
    }
  }
  DiagnosticReadiness->ActiveTroubleCodes = lNumberOfFilteredDTC;                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

  /* set DTC filter for previously active DTCs */
  lFilterData.DTCStatusFilterType = DEM_FILTERDATA_J1939FILTER_PREVIOUSLY_ACTIVE;

  /* get number of previously active DTCs */
  lNumberOfFilteredDTC = 0;
  for (lEventId = Dem_Cfg_GlobalPrimaryFirst();
        lEventId <= Dem_Cfg_GlobalPrimaryLast();
        ++lEventId)
  {
    if (Dem_FilterData_TestEventMatchesJ1939DTCFilter(lFilterData.DTCStatusFilterType, lFilterData.NodeId, lEventId) == TRUE)
    {
      lNumberOfFilteredDTC++;
      if (lNumberOfFilteredDTC == 250)
      {
        break;
      }
    }
  }
  DiagnosticReadiness->PreviouslyActiveDiagnosticTroubleCodes = lNumberOfFilteredDTC;                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  Dem_FilterData_SetFilterData(FilterId, lFilterData);
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_FILTERDATA_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_FilterData_Implementation.h
 *********************************************************************************************************************/
