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
 *  \file       Dem_MemState_Implementation.h
 *  \brief      Encapsulate global data stored for an event memory.
 *  \details    Implementation file for MemState subcomponent which encapsulate global data stored for an event memory.
 *              This includes handling chronology for event entries, tracking occupancy, overflow status, update state
 *              etc.
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

#if !defined (DEM_MEMSTATE_IMPLEMENTATION_H)
#define DEM_MEMSTATE_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemState_Interface.h"
                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Implementation.h"
#include "Dem_Cfg_Definitions.h"
#include "Dem_MemoryEntry_Implementation.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Number of stored entries in primary memory */
DEM_LOCAL VAR(uint8, DEM_VAR_NOINIT)                    Dem_MemState_PrimaryCurrentCount;

#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
/*! Number of stored entries in secondary memory */
DEM_LOCAL VAR(uint8, DEM_VAR_NOINIT)                    Dem_MemState_SecondaryCurrentCount;
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/*! Number of permanent DTCs */
DEM_LOCAL VAR(uint8, DEM_VAR_NOINIT)          Dem_MemState_PermanentCurrentCount;
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/*! Number of stored time-series entries */
DEM_LOCAL VAR(uint8, DEM_VAR_NOINIT)          Dem_MemState_TimeSeriesCurrentCount;                                               /* PRQA S 3218 */ /* MD_DEM_8.7 */
#endif

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DEM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Current time stamp, used to establish a chronological ordering */
DEM_LOCAL VAR(uint32, DEM_VAR_NOINIT)         Dem_MemState_CurrentTimestamp;

#define DEM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */     

#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */     

/*! MemoryInfo for the primary memory */
DEM_LOCAL CONST(Dem_MemState_MemoryInfoType, DEM_CONST) Dem_MemState_PrimaryInfo =                                               /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  &Dem_Cfg_PrimaryChronology[0],
  &Dem_MemState_PrimaryCurrentCount,
  DEM_CFG_MEMORY_PRIMARY_INDEX,
  DEM_CFG_GLOBAL_PRIMARY_FIRST,
  DEM_CFG_GLOBAL_PRIMARY_LAST,
  DEM_CFG_GLOBAL_PRIMARY_SIZE,
  DEM_CFG_MEMORYID_PRIMARY
};

#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
/*! MemoryInfo for the secondary memory */
DEM_LOCAL CONST(Dem_MemState_MemoryInfoType, DEM_CONST) Dem_MemState_SecondaryInfo =                                             /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  &Dem_Cfg_SecondaryChronology[0],
  &Dem_MemState_SecondaryCurrentCount,
  DEM_CFG_MEMORY_SECONDARY_INDEX,
  DEM_CFG_GLOBAL_SECONDARY_FIRST,
  DEM_CFG_GLOBAL_SECONDARY_LAST,
  DEM_CFG_GLOBAL_SECONDARY_SIZE,
  DEM_CFG_MEMORYID_SECONDARY
};
#endif

#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
/*! MemoryInfo for the time series memory */
DEM_LOCAL CONST(Dem_MemState_MemoryInfoType, DEM_CONST) Dem_MemState_TimeSeriesInfo =                                            /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  &Dem_Cfg_TimeSeriesChronology[0],
  &Dem_MemState_TimeSeriesCurrentCount,
  DEM_CFG_MEMORY_TIME_SERIES_INDEX,
  DEM_CFG_GLOBAL_PRIMARY_FIRST,
  DEM_CFG_GLOBAL_PRIMARY_LAST,
  DEM_CFG_GLOBAL_TIMESERIES_SNAPSHOTS_SIZE,
  DEM_CFG_MEMORYID_TIMESERIES
};
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/*! MemoryInfo for the permanent memory */
DEM_LOCAL CONST(Dem_MemState_MemoryInfoType, DEM_CONST) Dem_MemState_PermanentInfo =                                            /* PRQA S 3218 */ /* MD_DEM_8.7 */
{
  NULL_PTR,
  &Dem_MemState_PermanentCurrentCount,
  DEM_CFG_MEMORY_PERMANENT_INDEX,
  DEM_CFG_GLOBAL_PRIMARY_FIRST,
  DEM_CFG_GLOBAL_PRIMARY_LAST,
  DEM_CFG_GLOBAL_PERMANENT_SIZE,
  DEM_CFG_MEMORYID_PERMANENT
};
#endif

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_MemState_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_MemState_UpdateGetState
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_UpdateGetState(                                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  return Dem_Cfg_GetMemoryCommitNumber(MemoryIndex);
}

/* ****************************************************************************
 % Dem_MemState_SetCurrentTimestamp
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_SetCurrentTimestamp(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint32, AUTOMATIC)  CurrentTimeStamp
  )
{
  Dem_MemState_CurrentTimestamp = CurrentTimeStamp;
}

/* ****************************************************************************
 % Dem_MemState_GetCurrentTimestamp
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MemState_GetCurrentTimestamp(                                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return Dem_MemState_CurrentTimestamp;
}

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_MemState_SetMemoryOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_SetMemoryOverflow(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(uint8, AUTOMATIC)  MemoryOverflow
  )
{
  Dem_Cfg_AdminData.MemoryOverflow = MemoryOverflow;
}
#endif

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_MemState_GetMemoryOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_GetMemoryOverflow(                                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return Dem_Cfg_AdminData.MemoryOverflow;
}
#endif

/* ****************************************************************************
 % Dem_MemState_MemoryGetId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_MemoryGetId(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return MemoryInfo->MemoryId;
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetChronology
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_MemoryGetChronology(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(uint8, AUTOMATIC)  ChronoIndex
  )
{
  return (MemoryInfo->ChronoPtr)[ChronoIndex];
}

/* ****************************************************************************
 % Dem_MemState_MemorySetChronology
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_MemorySetChronology(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(uint8, AUTOMATIC)  ChronoIndex,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (ChronoIndex >= Dem_MemState_MemoryGetMaxSize(MemoryInfo))                                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    (MemoryInfo->ChronoPtr)[ChronoIndex] = MemoryIndex;                                                                          /* SBSW_DEM_ARRAY_WRITE_MEMORYCHRONOLOGY */
  }
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetFirstIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_MemoryGetFirstIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return MemoryInfo->FirstMemoryIndex;
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetLastIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_MemoryGetLastIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
#if(DEM_CFG_SUPPORT_PERMANENT == STD_ON)
  Dem_Internal_AssertReturnValue(MemoryInfo->MemoryId != DEM_CFG_MEMORYID_PERMANENT, DEM_E_INCONSISTENT_STATE, MemoryInfo->FirstMemoryIndex);
#endif
  return (Dem_Cfg_MemoryIndexType)(MemoryInfo->FirstMemoryIndex + MemoryInfo->MaxSize);
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetMaxSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_MemoryGetMaxSize(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return MemoryInfo->MaxSize;
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetCurrentSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_MemoryGetCurrentSize(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return *(MemoryInfo->SizePtr);
}

/* ****************************************************************************
 % Dem_MemState_MemorySetCurrentSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_MemorySetCurrentSize(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(uint8, AUTOMATIC)  Size
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (Size > Dem_MemState_MemoryGetMaxSize(MemoryInfo))                                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
    *(MemoryInfo->SizePtr) = Dem_MemState_MemoryGetMaxSize(MemoryInfo);                                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
#endif
  {
    *(MemoryInfo->SizePtr) = Size;                                                                                               /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  }
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetFirstEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemState_MemoryGetFirstEvent(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return MemoryInfo->FirstEvent;
}

/* ****************************************************************************
 % Dem_MemState_MemoryGetLastEvent
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemState_MemoryGetLastEvent(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo
  )
{
  return MemoryInfo->LastEvent;
}

/* ****************************************************************************
 % Dem_MemState_GetFirstValidEventMemoryBlockIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_GetFirstValidEventBlockIndex(                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  return Dem_Cfg_MemoryPrimaryIndex();
}

/* ****************************************************************************
 % Dem_MemState_GetFirstInvalidEventMemoryBlockIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Cfg_MemoryIndexType, DEM_CODE)
Dem_MemState_GetFirstInvalidEventBlockIndex(                                                                                     /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  void
  )
{
  Dem_Cfg_MemoryIndexType lReturnValue;
  lReturnValue = (Dem_Cfg_MemoryIndexType)
                 ( Dem_Cfg_MemoryPrimaryIndex() 
                 + Dem_Cfg_GlobalPrimaryMaxCount()
                 + Dem_Cfg_GlobalSecondaryMaxCount());

  return lReturnValue;
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
 * \addtogroup Dem_MemState_Private
 * \{
 */

/* ****************************************************************************
 % Dem_MemState_SetCommitStarted
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_SetCommitStarted(
  CONST(uint8, AUTOMATIC)  MemoryState
  )
{
   uint8 lMemoryState;
   lMemoryState = (uint8)(MemoryState | DEM_MEMSTATE_COMMIT_STARTED);
   return lMemoryState;
}

/* ****************************************************************************
 % Dem_MemState_SetCommitFinished
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemState_SetCommitFinished(
  CONST(uint8, AUTOMATIC)  MemoryState
  )
{
   uint8 lMemoryState;
   lMemoryState = (uint8)((MemoryState + 1) & DEM_MEMSTATE_COMMIT_FINISHED);
   return lMemoryState;
}

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
 * \addtogroup Dem_MemState_Public
 * \{
 */

/* ****************************************************************************
 % Dem_MemState_TestCommitStarted
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemState_TestCommitStarted(
  CONST(uint8, AUTOMATIC)  MemoryState
  )
{
  boolean lCommitStarted;
  if ((MemoryState & DEM_MEMSTATE_COMMIT_STARTED) != 0x00)
  {
    lCommitStarted = TRUE;
  }
  else
  {
    lCommitStarted = FALSE;
  }
  return lCommitStarted;
}

/* ****************************************************************************
 % Dem_MemState_MemoryInfoInit
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
 */
DEM_LOCAL_INLINE FUNC(Dem_MemState_MemoryInfoPtrType, DEM_CODE)
Dem_MemState_MemoryInfoInit(
  CONST(uint8, AUTOMATIC)  MemoryId                                                                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  Dem_MemState_MemoryInfoPtrType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MemoryId)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
  if (MemoryId == DEM_CFG_MEMORYID_PERMANENT)
  {
    lReturnValue = &Dem_MemState_PermanentInfo;
  }
  else
#endif
#if (DEM_FEATURE_NEED_TIME_SERIES == STD_ON)
  if (MemoryId == DEM_CFG_MEMORYID_TIMESERIES)
  {
    lReturnValue = &Dem_MemState_TimeSeriesInfo;
  }
  else
#endif
#if (DEM_CFG_SUPPORT_SECONDARY == STD_ON)
  if (MemoryId == DEM_CFG_MEMORYID_SECONDARY)
  {
    lReturnValue = &Dem_MemState_SecondaryInfo;
  }
  else
#endif
  {
    lReturnValue = &Dem_MemState_PrimaryInfo;
  }
  return lReturnValue;
}

/* ****************************************************************************
 % Dem_MemState_MemoryUpdateInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_MemoryUpdateInit(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (MemoryIndex >= Dem_Cfg_GetSizeOfMemoryCommitNumber())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_SetMemoryCommitNumber(MemoryIndex, DEM_MEMORY_INIT_COMMIT_NUMBER);                                                   /* SBSW_DEM_ARRAY_WRITE_MEMORYCOMMITNUMBER */
  }
}

/* ****************************************************************************
 % Dem_MemState_MemoryUpdateStart
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_MemoryUpdateStart(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (MemoryIndex >= Dem_Cfg_GetSizeOfMemoryCommitNumber())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_SetMemoryCommitNumber(MemoryIndex,                                                                                   /* SBSW_DEM_ARRAY_WRITE_MEMORYCOMMITNUMBER */
                                  Dem_MemState_SetCommitStarted(
                                  Dem_Cfg_GetMemoryCommitNumber(MemoryIndex)));       
  }
}

/* ****************************************************************************
 % Dem_MemState_MemoryUpdateFinish
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_MemoryUpdateFinish(
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (MemoryIndex >= Dem_Cfg_GetSizeOfMemoryCommitNumber())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    Dem_Cfg_SetMemoryCommitNumber(MemoryIndex,                                                                                   /* SBSW_DEM_ARRAY_WRITE_MEMORYCOMMITNUMBER */
                                  Dem_MemState_SetCommitFinished(
                                  Dem_Cfg_GetMemoryCommitNumber(MemoryIndex)));    
  }
}

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_MemState_SetOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_SetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  uint8 lOldOverflow;
  uint8 lNewOverflow;

  lOldOverflow = Dem_MemState_GetMemoryOverflow();
  lNewOverflow = (uint8)(lOldOverflow | ((uint8)(1U << MemoryId)));
  if (lOldOverflow != lNewOverflow)
  {
    Dem_MemState_SetMemoryOverflow(lNewOverflow);
  }
}
#endif

#if (DEM_FEATURE_NEED_OVFLIND == STD_ON)
/* ****************************************************************************
 % Dem_MemState_ResetOverflow
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_ResetOverflow(
  CONST(uint8, AUTOMATIC)  MemoryId
  )
{
  uint8 lOldOverflow;
  uint8 lNewOverflow;

  lOldOverflow = Dem_MemState_GetMemoryOverflow();
  lNewOverflow = (uint8)(lOldOverflow & ((uint8)~((uint8)(1U << MemoryId))));
  if (lOldOverflow != lNewOverflow)
  {
    Dem_MemState_SetMemoryOverflow(lNewOverflow);
  }
}
#endif

/* ****************************************************************************
 % Dem_MemState_MemoryUpdateIndex
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_MemoryUpdateIndex(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)  MemoryIndex
  )
{
  uint8 lChronoIterator;
  Dem_Cfg_MemoryIndexType lTempIndex;

  /* Store the global timestamp to the entry, and update it */
  Dem_MemoryEntry_SetTimestamp(Dem_MemoryEntry_GetId(MemoryIndex), Dem_MemState_GetCurrentTimestamp());
  Dem_MemState_SetCurrentTimestamp(Dem_MemState_GetCurrentTimestamp() + 1);

  /* move downwards the chronology moving all entries, until the updated element is overwritten */
  lChronoIterator = (uint8)(Dem_MemState_MemoryGetCurrentSize(MemoryInfo) - 1);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lTempIndex = Dem_MemState_MemoryGetChronology(MemoryInfo, lChronoIterator);                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  while (lTempIndex != MemoryIndex)
  {
    uint8 lSwap;

    lSwap = lTempIndex;
    --lChronoIterator;
    lTempIndex = Dem_MemState_MemoryGetChronology(MemoryInfo, lChronoIterator);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    Dem_MemState_MemorySetChronology(MemoryInfo, lChronoIterator, lSwap);                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
    if ((lChronoIterator == 0) && (lTempIndex != MemoryIndex))
    {
      /* chronology is inconsistent */
      Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                          /* SBSW_DEM_POINTER_RUNTIME_CHECK */
      break;
    }
#endif
  }

  Dem_MemState_MemorySetChronology(MemoryInfo, (uint8)(Dem_MemState_MemoryGetCurrentSize(MemoryInfo) - 1), MemoryIndex);         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */

/* ****************************************************************************
 % Dem_MemState_SortEntryIntoChronologicalList
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemState_SortEntryIntoChronologicalList(
  CONST(Dem_MemState_MemoryInfoPtrType, AUTOMATIC)  MemoryInfo,
  CONST(Dem_Cfg_MemoryIndexType, AUTOMATIC)    MemoryIndex,
  CONST(uint32, AUTOMATIC)                     Timestamp
  )
{
  uint8 lSortedIndex;
  for ( lSortedIndex = Dem_MemState_MemoryGetCurrentSize(MemoryInfo);                                                            /* PRQA S 3415 */ /* MD_DEM_12.4_cf */ /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
        (lSortedIndex > 0)
         && (Dem_MemoryEntry_GetTimestamp(Dem_MemoryEntry_GetId(
             Dem_MemState_MemoryGetChronology(MemoryInfo, (uint8)(lSortedIndex - 1))))                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
             > Timestamp);
       --lSortedIndex
    )
  {
    Dem_MemState_MemorySetChronology(
      MemoryInfo,                                                                                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      lSortedIndex,
      Dem_MemState_MemoryGetChronology(MemoryInfo, (uint8)(lSortedIndex - 1)));                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  Dem_MemState_MemorySetChronology(MemoryInfo, lSortedIndex, MemoryIndex);                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
}

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMSTATE_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemState_Implementation.h
 *********************************************************************************************************************/
