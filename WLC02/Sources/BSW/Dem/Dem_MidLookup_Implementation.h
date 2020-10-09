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
/*!  Project    MICROSAR Diagnostic Event Manager (Dem)
 *
 *  \addtogroup Dem_MidLookup
 *  \{
 *  \file       Dem_MidLookup_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of MidLookup subcomponent
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

#if !defined (DEM_MIDLOOKUP_IMPLEMENTATION_H)
#define DEM_MIDLOOKUP_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MidLookup_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Dtr_Implementation.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Maximum number of 'supported MID' bitmasks (MIDs 0x00, 0x20, ...) */
#define DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS  (0x08U)

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/*! Visibility change of DTR(s) is pending. Used to serialize recalculation of MID visibilty when TIDs change visibility. */
DEM_LOCAL volatile VAR(boolean, DEM_VAR_NOINIT)  Dem_MidLookup_VisibilityChanged;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"


#define DEM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/*! 'supported MID' values (MIDS 0x00, 0x20, ...) */
DEM_LOCAL VAR(uint32, DEM_VAR_NOINIT)  Dem_MidLookup_SupportedMidMask[DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS];
#endif

#define DEM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/*! DTR lookup cache to improve performance of TID lookup. */
DEM_LOCAL VAR(Dem_MidLookup_CacheType, DEM_VAR_NOINIT)  Dem_MidLookup_Cache;                                                     /* PRQA S 3218 */ /* MD_DEM_8.7 */
#endif

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/*!
 * \addtogroup Dem_MidLookup_Private
 * \{
 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetMidValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetMidValue(
  CONST(uint16, AUTOMATIC) MidHandle
  )
{
  uint8 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MidHandle)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetMidOfMidTable(MidHandle);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetMidTidValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetMidTidValue(
  CONST(uint16, AUTOMATIC) MidHandle
  )
{
  uint8 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MidHandle)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetTidOfMidTable(MidHandle);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetMidDtrId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_MidLookup_GetMidDtrId(
  CONST(uint16, AUTOMATIC) MidHandle
  )
{
  DTRIdType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(MidHandle)                                                                                    /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetDtrTableIdxOfMidTable(MidHandle);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_MidIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_MidIterExists(
  CONSTP2CONST(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_MidIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_MidIterGet(
  CONSTP2CONST(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (uint8)(IterPtr->mIdx);
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_MidIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_MidIterInit(
  CONST(uint16, AUTOMATIC) MidTableStartIndex,
  CONSTP2VAR(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx = MidTableStartIndex;                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetSizeOfDtrTable();                                                                                /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_MidIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_MidIterNext(
  CONSTP2VAR(Dem_ComplexIterType, AUTOMATIC, AUTOMATIC) IterPtr
  )
{
  IterPtr->mIdx += 1;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_MidLookup_Private
 * \{
 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_TestAvailabilityMid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_TestAvailabilityMid(
  CONST(uint8, AUTOMATIC) Mid
  )
{  
  return (boolean)((Mid % 32U) == 0);
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetSupportedMidIndexOfMid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetSupportedMidIndexOfMid(
  CONST(uint8, AUTOMATIC) Mid
  )
{
  return (uint8)((Mid-1) / 32U);
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetSupportedMidBitPositionOfMid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MidLookup_GetSupportedMidBitPositionOfMid(
  CONST(uint8, AUTOMATIC) Mid
  )
{
  return (uint8)(32U - (Mid % 32U));
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetInitialSupportedMidMask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetInitialSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex
  )
{
  uint32 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SupportedMidIndex)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_Cfg_GetSupportedMidMaskOfSupportedMidsTable(SupportedMidIndex);
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_GetSupportedMidMask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex
  )
{
  uint32 lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SupportedMidIndex)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = Dem_MidLookup_SupportedMidMask[SupportedMidIndex];
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_SetSupportedMidMask
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_SetSupportedMidMask(
  CONST(uint8, AUTOMATIC) SupportedMidIndex,
  CONST(uint32, AUTOMATIC) SupportedMidValue
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SupportedMidIndex)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(SupportedMidValue)                                                                            /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (SupportedMidIndex >= DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_MidLookup_SupportedMidMask[SupportedMidIndex] = SupportedMidValue;                                                       /* SBSW_DEM_ARRAY_WRITE_SUPPORTEDMIDMASK */
  }
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_TestVisibilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_TestVisibilityChanged(
  void
  )
{
  boolean lReturnValue;
  lReturnValue = Dem_MidLookup_VisibilityChanged;
  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_SetVisibilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_SetVisibilityChanged(
  void
  )
{
  Dem_MidLookup_VisibilityChanged = TRUE;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_ResetVisibilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_ResetVisibilityChanged(
  void
  )
{
  Dem_MidLookup_VisibilityChanged = FALSE;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_IsMidSupported
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_IsMidSupported(
  CONST(uint8, AUTOMATIC)  Mid
  )
{
  boolean lMidSupported;
  uint8 lSupportedMidIndex;
  uint8 lSupportedMidBitPosition;

  lSupportedMidIndex = Dem_MidLookup_GetSupportedMidIndexOfMid(Mid);
  lSupportedMidBitPosition = Dem_MidLookup_GetSupportedMidBitPositionOfMid(Mid);

  if ((Dem_MidLookup_TestAvailabilityMid(Mid) == FALSE)
     && (DEM_TEST_BIT(Dem_MidLookup_GetSupportedMidMask(lSupportedMidIndex), lSupportedMidBitPosition) == TRUE))
  {
    lMidSupported = TRUE;
  }
  else
  {
    lMidSupported = FALSE;
  }
  return lMidSupported;
}
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
 % Dem_MidLookup_FindHandleOfMid
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
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MidLookup_FindHandleOfMid(
  CONST(uint8, AUTOMATIC) Mid
  )
{
  uint16 lMidHandle;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Mid)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */

  if (Mid == Dem_MidLookup_Cache.Mid)
  {
    lMidHandle = Dem_MidLookup_Cache.MidHandle;
  }
  else
  {
    uint8 lMid;
    uint8 lSupportedMidIndex;
    Dem_ComplexIterType lMidIter;

    lMid = 0x00;
    lMidHandle = 0x00;
    lSupportedMidIndex = Dem_MidLookup_GetSupportedMidIndexOfMid(Mid);
    DEM_IGNORE_UNUSED_VARIABLE(lSupportedMidIndex)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */

    for (Dem_MidLookup_MidIterInit(Dem_Cfg_GetStartIdxMidTableOfSupportedMidsTable(lSupportedMidIndex), &lMidIter);              /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterExists(&lMidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterNext(&lMidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      if (lMid < Mid)
      {
        lMidHandle = Dem_MidLookup_MidIterGet(&lMidIter);                                                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
        lMid = Dem_MidLookup_GetMidValue(lMidHandle);
      }
      else
      {
        break;
      }
    }

    Dem_MidLookup_Cache.Mid = Mid;
    Dem_MidLookup_Cache.MidHandle = lMidHandle;
  }
  return lMidHandle;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* *********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 **********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_MidLookup_Public
 * \{
 */

/* ****************************************************************************
 % Dem_MidLookup_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_Init(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  uint8 lSupportedMidIndex;

  Dem_MidLookup_Cache.MidHandle = 0;
  Dem_MidLookup_Cache.Mid = Dem_MidLookup_GetMidValue(0);

  for (lSupportedMidIndex = 0;
       lSupportedMidIndex < (uint8) Dem_Cfg_GetSizeOfSupportedMidsTable();
       ++lSupportedMidIndex)
  {
    Dem_MidLookup_SetSupportedMidMask(lSupportedMidIndex, Dem_MidLookup_GetInitialSupportedMidMask(lSupportedMidIndex));
  }

  for (lSupportedMidIndex = (uint8) Dem_Cfg_GetSizeOfSupportedMidsTable();
       lSupportedMidIndex < DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS;                                                             /* PRQA S 3356, 3359 */ /* MD_DEM_3356, MD_DEM_3359 */
       ++lSupportedMidIndex)
  {                                                                                                                              /* PRQA S 3201 */ /* MD_DEM_COMSTACKLIB */
    Dem_MidLookup_SetSupportedMidMask(lSupportedMidIndex, 0);
  }
#endif
}

/* ****************************************************************************
 % Dem_MidLookup_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_PreInit(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_MidLookup_ResetVisibilityChanged();
#endif
}

/* ****************************************************************************
 % Dem_MidLookup_UpdateMidVisibility
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
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_UpdateMidVisibility(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  if (Dem_MidLookup_TestVisibilityChanged() == TRUE)
  {
    Dem_ComplexIterType lMidIter;
    boolean lVisible;
    uint8 lMid;
    uint8 lLastMid;
    uint8 lSupportedMidIndex;
    uint8 lSupportedMidBitIndex;
    uint16 lMaxSupportedMidIndex;
    uint32 lSupportedMid;

    Dem_MidLookup_ResetVisibilityChanged();

    lVisible = FALSE;
    lMid = 0;

    for (lSupportedMidIndex = 0;
         lSupportedMidIndex < DEM_MIDLOOKUP_MAX_NUMBER_SUPPORTED_MIDS;
         ++lSupportedMidIndex)
    {
      Dem_MidLookup_SetSupportedMidMask(lSupportedMidIndex, 0);
    }

    lSupportedMidIndex = 0;
    lSupportedMidBitIndex = 0;

    for (Dem_MidLookup_MidIterInit(0, &lMidIter);                                                                                /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterExists(&lMidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterNext(&lMidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint8 lMidIndex;

      lLastMid = lMid;
      lMidIndex = Dem_MidLookup_MidIterGet(&lMidIter);                                                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
      lMid = Dem_MidLookup_GetMidValue(lMidIndex);

      if (lMid != lLastMid)
      {
        lSupportedMidIndex = Dem_MidLookup_GetSupportedMidIndexOfMid(lMid);
        lSupportedMidBitIndex = Dem_MidLookup_GetSupportedMidBitPositionOfMid(lMid);
        lVisible = FALSE;
      }

      if (lVisible == FALSE)
      {
        DTRIdType lDtrId;

        lDtrId = Dem_MidLookup_GetMidDtrId(lMidIndex);
        if (Dem_Dtr_TestDtrVisibility(lDtrId) == TRUE)
        {
          lVisible = TRUE;
          lSupportedMid = Dem_MidLookup_GetSupportedMidMask(lSupportedMidIndex);
          lSupportedMid = DEM_SET_BIT(lSupportedMid, lSupportedMidBitIndex);
          Dem_MidLookup_SetSupportedMidMask(lSupportedMidIndex, lSupportedMid);
        }
      }
    }

    lMaxSupportedMidIndex = lSupportedMidIndex;
    for (lSupportedMidIndex = 0; lSupportedMidIndex < lMaxSupportedMidIndex; ++lSupportedMidIndex)
    {
      lSupportedMid = Dem_MidLookup_GetSupportedMidMask(lSupportedMidIndex);
      lSupportedMid = DEM_SET_BIT(lSupportedMid, 0);
      Dem_MidLookup_SetSupportedMidMask(lSupportedMidIndex, lSupportedMid);
    }
  }
#endif
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_MidLookup_NotifyVisibilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MidLookup_NotifyVisibilityChanged(
  void
  )
{
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_MidLookup_SetVisibilityChanged();
#endif
}


/* ****************************************************************************
 % Dem_MidLookup_IsSupportedMid
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MidLookup_IsSupportedMid(
  CONST(uint8, AUTOMATIC)  Mid
  )
{
  return (boolean)((Mid % 32U) == 0);
}

/* ****************************************************************************
 % Dem_MidLookup_GetSupportedMidValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint32, DEM_CODE)
Dem_MidLookup_GetSupportedMidValue(
  CONST(uint8, AUTOMATIC)  Mid
  )
{
  uint32 lReturnValue;
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  uint8 lSupportedMidIndex;
#endif

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Mid)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_MidLookup_UpdateMidVisibility();

  if (Dem_MidLookup_IsSupportedMid(Mid) == TRUE)
  {
    /* +1: one arbitrary Mid in the range of the SupportedMid */
    lSupportedMidIndex = Dem_MidLookup_GetSupportedMidIndexOfMid(Mid + 1);
  }
  else
  {
    lSupportedMidIndex = Dem_MidLookup_GetSupportedMidIndexOfMid(Mid);
  }
  lReturnValue = Dem_MidLookup_GetSupportedMidMask(lSupportedMidIndex);
#else
  lReturnValue = 0UL;
#endif
  return lReturnValue;
}


/* ****************************************************************************
 % Dem_MidLookup_GetTidCountOfMid
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
 */
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_MidLookup_GetTidCountOfMid(
  CONST(uint8, AUTOMATIC)  Mid,                                                                                                  /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  TidCount                                                                           /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_False */
  )
{
  Std_ReturnType lReturnValue;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Mid)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(TidCount)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
   
  lReturnValue = E_NOT_OK;

  /* ----- Implementation ------------------------------------------------ */
#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  Dem_MidLookup_UpdateMidVisibility();

  if (Dem_MidLookup_IsMidSupported(Mid) == TRUE)
  {
    uint16 lMidHandle;
    uint8 lNumberOfTIDs;
    Dem_ComplexIterType lMidIter;

    lMidHandle = Dem_MidLookup_FindHandleOfMid(Mid);
    lNumberOfTIDs = 0;

    for (Dem_MidLookup_MidIterInit(lMidHandle, &lMidIter);                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterExists(&lMidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterNext(&lMidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint8 lMid;

      lMidHandle = Dem_MidLookup_MidIterGet(&lMidIter);                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
      lMid = Dem_MidLookup_GetMidValue(lMidHandle);

      if (lMid == Mid)
      {
        DTRIdType lDtrId;

        lDtrId = Dem_MidLookup_GetMidDtrId(lMidHandle);
        if (Dem_Dtr_TestDtrVisibility(lDtrId) == TRUE)
        {
          lNumberOfTIDs++;
        }
      }
      else
      {
        break;
      }
    }

    *TidCount = lNumberOfTIDs;                                                                                                   /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
    lReturnValue = E_OK;
  }
#endif

  return lReturnValue;
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/* ****************************************************************************
 % Dem_MidLookup_FindDtrId
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
DEM_LOCAL_INLINE FUNC(DTRIdType, DEM_CODE)
Dem_MidLookup_FindDtrId(
  CONST(uint8, AUTOMATIC) Mid,                                                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONST(uint8, AUTOMATIC) TidIndex,                                                                                              /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC)  Tid                                                                                   /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_False */
  )
{
  DTRIdType lReturnValue;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Mid)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(TidIndex)                                                                                     /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Tid)                                                                                          /* PRQA S 3112 */ /* MD_DEM_14.2 */

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
  if (Dem_MidLookup_IsMidSupported(Mid) == TRUE)
  {
    uint16 lMidHandle;
    uint8 lTidIndex;
    Dem_ComplexIterType lMidIter;

    lReturnValue = DEM_DTR_INVALIDDTRID;
    lMidHandle = Dem_MidLookup_FindHandleOfMid(Mid);
    lTidIndex = 0;

    for (Dem_MidLookup_MidIterInit(lMidHandle, &lMidIter);                                                                       /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterExists(&lMidIter) == TRUE;                                                                         /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_MidLookup_MidIterNext(&lMidIter))                                                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint8 lMid;

      lMidHandle = Dem_MidLookup_MidIterGet(&lMidIter);                                                                          /* SBSW_DEM_CALL_ITERATOR_POINTER */
      lMid = Dem_MidLookup_GetMidValue(lMidHandle);

      if (lMid == Mid)
      {
        DTRIdType lDtrId;

        lDtrId = Dem_MidLookup_GetMidDtrId(lMidHandle);
        if (Dem_Dtr_TestDtrVisibility(lDtrId) == TRUE)
        {
          if (lTidIndex == TidIndex)
          {
            lReturnValue = lDtrId;
            *Tid = Dem_MidLookup_GetMidTidValue(lMidHandle);                                                                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
            break;
          }
          lTidIndex++;
        }
      }
      else
      {
        break;                                                                                                                   /* PRQA S 0771 */ /* MD_DEM_14.6_opt */
      }
    }
  }
  else
#endif
  {
    lReturnValue = DEM_DTR_INVALIDDTRID;
  }

  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050, 6060, 6080 */ /* MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR, MD_MSR_STMIF */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_MIDLOOKUP_IMPLEMENTATION_H */
/*!
 * \}
 */
/* *********************************************************************************************************************
 *  END OF FILE: Dem_MidLookup_Implementation.h
 **********************************************************************************************************************/
