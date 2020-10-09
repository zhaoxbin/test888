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
/*! \addtogroup Dem_ExtendedEntry
 *  \{
 *  \file       Dem_ExtendedEntry_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Encapsulates the list of extended data record buffers stored in the memory entry
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

#if !defined (DEM_EXTENDEDENTRY_IMPLEMENTATION_H)
#define DEM_EXTENDEDENTRY_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ExtendedEntry_Interface.h"
#include "Dem_MemoryEntry_Implementation.h"

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

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_ExtendedEntry_Properties
 * \{
 */

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
 * \addtogroup Dem_ExtendedEntry_Private
 * \{
 */

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
 * \addtogroup Dem_ExtendedEntry_Public
 * \{
 */
#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_ExtendedEntry_IterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtendedEntry_IterInit(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONSTP2VAR(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  IterPtr->mIdx = Dem_Cfg_GetDataCollectionTableEdr2CollIndStartIdxOfExtendedDataTable(                                          /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
                                                                  Dem_Cfg_GetExtendedDataTableIdxOfEventTable(EventId));
    
  IterPtr->mEndIdx = Dem_Cfg_GetDataCollectionTableEdr2CollIndEndIdxOfExtendedDataTable(                                         /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
                                                                  Dem_Cfg_GetExtendedDataTableIdxOfEventTable(EventId));
}
#endif /* (DEM_CFG_SUPPORT_ERECS == STD_ON) */

#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_ExtendedEntry_IterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtendedEntry_IterNext(
  CONSTP2VAR(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  IterPtr->mIdx += 1;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif /* (DEM_CFG_SUPPORT_ERECS == STD_ON) */

#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_ExtendedEntry_IterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ExtendedEntry_IterExists(
  CONSTP2CONST(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif /* (DEM_CFG_SUPPORT_ERECS == STD_ON) */

#if (DEM_CFG_SUPPORT_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_ExtendedEntry_IterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Cfg_ERecIndexType, DEM_CODE)
Dem_ExtendedEntry_IterGet(
  CONSTP2CONST(Dem_ExtendedEntry_IterType, AUTOMATIC, AUTOMATIC)  IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (Dem_Cfg_ERecIndexType) Dem_Cfg_GetDataCollectionTableEdr2CollInd(IterPtr->mIdx);
}
#endif /* (DEM_CFG_SUPPORT_ERECS == STD_ON) */

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_ExtendedEntry_IteratorGetExtendedRecordDataConstPtr
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_ConstSharedDataPtrType, DEM_CODE)
Dem_ExtendedEntry_IteratorGetExtendedRecordDataConstPtr(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  )
{
  if (MemoryEntryId == DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
  return Dem_MemoryEntry_GetExtendedRecordDataConstPtr(MemoryEntryId, ExtendedEntryIndex);
}
#endif /* (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) */

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_ExtendedEntry_IteratorIsExtendedRecordStored
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ExtendedEntry_IteratorIsExtendedRecordStored(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  )
{
  boolean lExtendedRecordIsStored;

  lExtendedRecordIsStored = FALSE;
  if (MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    uint8 lMask;

    lMask = (uint8)(1u << ExtendedEntryIndex);
    if ((Dem_MemoryEntry_GetExtendedHeader(MemoryEntryId) & lMask) != 0)
    {
      lExtendedRecordIsStored = TRUE;
    }
  }
  else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }

  return lExtendedRecordIsStored;
}
#endif /* (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) */

#if (DEM_CFG_SUPPORT_USER_ERECS == STD_ON)
/* ****************************************************************************
 % Dem_ExtendedEntry_IteratorUpdateExtendedEntry
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ExtendedEntry_IteratorUpdateExtendedEntry(
  CONST(Dem_MemoryEntry_HandleType, AUTOMATIC)  MemoryEntryId,
  CONST(uint8, AUTOMATIC)  ExtendedEntryIndex
  )
{
  if (MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID)
  {
    uint8 lMask;

    lMask = (uint8)(1u << ExtendedEntryIndex);
    Dem_MemoryEntry_SetExtendedHeader(MemoryEntryId,
                              (uint8)(Dem_MemoryEntry_GetExtendedHeader(MemoryEntryId) | lMask));
  }
  else
  {
    Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);
  }
}
#endif /* (DEM_CFG_SUPPORT_USER_ERECS == STD_ON) */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_EXTENDEDENTRY_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ExtendedEntry_Implementation.h
 *********************************************************************************************************************/
