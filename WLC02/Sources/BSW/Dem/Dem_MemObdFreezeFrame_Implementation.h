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
/*! \addtogroup Dem_MemObdFreezeFrame
 *  \{
 *  \file       Dem_MemObdFreezeFrame_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the Obd Freeze Frame Memory subcomponent which manages storage and erasing of the 
 *              legislative Obd Freeze Frame
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
 *  Friederike Schulze            visfrs        Vector Informatik GmbH
 *  Aswin Vijayamohanan Nair      visavi        Vector Informatik GmbH
 *  Fabian Wild                   viszfa        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMOBDFREEZEFRAME_IMPLEMENTATION_H)
#define DEM_MEMOBDFREEZEFRAME_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemObdFreezeFrame_Interface.h"

/* ------------------------------------------------------------------------- */
#include "Dem_MemState_Implementation.h"
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_UDSStatus_Implementation.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"
#include "Dem_Memory_Interface.h"
#include "Dem_Event_Interface.h"
#include "Dem_DTC_Interface.h"

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
 * \addtogroup Dem_MemObdFreezeFrame_Properties
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_FreezeFrameGetVisibility
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameGetVisibility(
  CONST(uint8, AUTOMATIC)  Index
  )
{
  return Dem_Cfg_FreezeFrameData[Index].IsVisible;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_FreezeFrameSetVisibility
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameSetVisibility(
  CONST(uint8, AUTOMATIC)  Index,
  CONST(boolean, AUTOMATIC)  Visible
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (Index >= Dem_Cfg_GlobalObdIIFFCount())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_FreezeFrameData[Index].IsVisible = Visible;                                                                          /* SBSW_DEM_ARRAY_WRITE_FREEZEFRAMEDATA */
  }
}
#endif
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
 * \addtogroup Dem_MemObdFreezeFrame_Private
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_SelectNewestLowPrioFF
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectNewestLowPrioFF(
  CONST(boolean, AUTOMATIC)  SelectVisible
  )
{
  uint8 lBestCandidate;
  uint8 lFreezeFrameIndex;
  uint32 lHighestTimestamp;

  lBestCandidate = Dem_Cfg_GlobalObdIIFFCount();
  lFreezeFrameIndex = Dem_Cfg_GlobalObdIIFFCount();
  lHighestTimestamp = 0;


  while (lFreezeFrameIndex != 0U)
  {
    Dem_EventIdType lEventId;

    lFreezeFrameIndex--;
    lEventId = Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex);

    if (Dem_MemObdFreezeFrame_FreezeFrameTestVisible(lFreezeFrameIndex) == SelectVisible)
    {
      if ((Dem_Event_TestHighPriorReadinessGroup(lEventId) == FALSE)                                                             /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        && (Dem_Mem_FreezeFrameGetTimestamp(lFreezeFrameIndex) > lHighestTimestamp))
      {
        lBestCandidate = lFreezeFrameIndex;
        lHighestTimestamp = Dem_Mem_FreezeFrameGetTimestamp(lFreezeFrameIndex);
      }
      else
      {
        /* no candidate found, lBestCandidate is still Dem_Cfg_GlobalObdIIFFCount()*/
      }
    }
  }
  return lBestCandidate;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_GetEventOfObdFF
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemObdFreezeFrame_GetEventOfObdFF(
CONST(uint8, AUTOMATIC)  Index
)
{
  Dem_EventIdType lEventId;
  if (Index < Dem_Cfg_GlobalObdIIFFCount())
  {
    lEventId = Dem_Cfg_FreezeFrameData[Index].EventId;
  }
  else
  {
    lEventId = DEM_EVENT_INVALID;
  }
  return lEventId;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_FreezeFrameTestVisible
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameTestVisible(
  CONST(uint8, AUTOMATIC) Index
  )
{
  boolean IsFFVisible;
# if (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON)
  IsFFVisible = Dem_MemObdFreezeFrame_FreezeFrameGetVisibility(Index);
#else
  IsFFVisible = TRUE;
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Index);                                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */
#endif
  return IsFFVisible;
}
#endif
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
 * \addtogroup Dem_MemObdFreezeFrame_Public
 * \{
 */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_SelectFFDisplaceIndex
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
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectFFDisplaceIndex(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(boolean, AUTOMATIC)  DisplacePendingFreezeFrame
  )
{
  uint8 lBestCandidate;
# if (DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON)
  boolean lReplaceMisfireOrFuelSys;
#endif

  lBestCandidate = Dem_Cfg_GlobalObdIIFFCount();
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(DisplacePendingFreezeFrame);                                                                  /* PRQA S 3112 */ /* MD_DEM_14.2 */
  if (Dem_Event_TestHighPriorReadinessGroup(EventId) == TRUE)
  {
    lBestCandidate = Dem_MemObdFreezeFrame_SelectNewestLowPrioFF(FALSE);
    if (lBestCandidate == Dem_Cfg_GlobalObdIIFFCount())
    {
      lBestCandidate = Dem_MemObdFreezeFrame_SelectNewestLowPrioFF(TRUE);
    }
# if (DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON)
    lReplaceMisfireOrFuelSys = TRUE;
#endif
  }
# if (DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON)
  else
  {
    lReplaceMisfireOrFuelSys = FALSE;
  }
  if ( (lBestCandidate == Dem_Cfg_GlobalObdIIFFCount())                                                                          /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
    && (DisplacePendingFreezeFrame == TRUE)
    )
  {
    /* All OBD freeze frame slots occupied by high prio monitors */
    lBestCandidate = Dem_Mem_FindDisplaceablePendingFreezeFrame(lReplaceMisfireOrFuelSys);
  }
#endif  
  return lBestCandidate;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame
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
DEM_LOCAL FUNC(uint8, DEM_CODE)
Dem_MemObdFreezeFrame_SelectHighestPriorFreezeFrame(
  void
  )
{

  uint8 lBestCandidate;
  uint8 lFreezeFrameIndex;
  uint32 lLowestTimestamp;

  lBestCandidate = Dem_Cfg_GlobalObdIIFFCount();
  lLowestTimestamp = 0xFFFFFFFFU;

  for (lFreezeFrameIndex = 0; lFreezeFrameIndex < Dem_Cfg_GlobalObdIIFFCount(); lFreezeFrameIndex++)
  {
    if (Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex) == DEM_EVENT_INVALID)
    { /* Freeze Frame slot not in use, continue with next slot */
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }

    if (Dem_MemObdFreezeFrame_FreezeFrameTestVisible(lFreezeFrameIndex) == FALSE)
    { /* Freeze Frame not visible, continue with next slot */
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }

    if (Dem_Cfg_EventObdRelated(Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex)) == FALSE)
    { /* Event of stored Freeze Frame is not OBD related (anymore), continue with next slot */
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }

    if (Dem_Event_TestHighPriorReadinessGroup(Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex)) == TRUE)
    {
      if ((Dem_Event_TestHighPriorReadinessGroup(Dem_MemObdFreezeFrame_GetEventOfObdFF(lBestCandidate)) == FALSE)                /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
        || (Dem_Mem_FreezeFrameGetTimestamp(lFreezeFrameIndex) < lLowestTimestamp))
      {/* current candidate has higher prio readiness group than best candidate
          or has same prio readiness group but is older than best candidate or 
          best candidate is not set yet -> set new best candidate and continue 
          with next slot */
        lBestCandidate = lFreezeFrameIndex;
        lLowestTimestamp = Dem_Mem_FreezeFrameGetTimestamp(lBestCandidate);
      }
    }
    /* Best candidate has low prio readiness group or is not set yet */
    else if (Dem_Event_TestHighPriorReadinessGroup(Dem_MemObdFreezeFrame_GetEventOfObdFF(lBestCandidate)) == FALSE)
    {
      if (Dem_Mem_FreezeFrameGetTimestamp(lFreezeFrameIndex) < lLowestTimestamp)
      { /* current and best candidate have the same priority so if timestamp of current index is older than best candidate-> set new best candidate and continue with next slot */
        lBestCandidate = lFreezeFrameIndex;
        lLowestTimestamp = Dem_Mem_FreezeFrameGetTimestamp(lBestCandidate);
      }
    }
    else
    {
      /* no candidate found, lBestCandidate is still Dem_Cfg_GlobalObdIIFFCount()*/
    }
  }

  return lBestCandidate;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_FreezeFrameSetVisible
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameSetVisible(
  CONST(uint8, AUTOMATIC)  Index
  )
{
  Dem_MemObdFreezeFrame_FreezeFrameSetVisibility(Index, TRUE);
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_FreezeFrameResetVisible
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameResetVisible(
  CONST(uint8, AUTOMATIC)  Index
  )
{
  Dem_MemObdFreezeFrame_FreezeFrameSetVisibility(Index, FALSE);
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
% Dem_MemObdFreezeFrame_FreezeFrameFreeEntry
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_FreezeFrameFreeEntry(
  CONST(uint8, AUTOMATIC) Index
  )
{
  Dem_Mem_FreezeFrameSetEvent(Index, DEM_EVENT_INVALID);
}
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_ON) \
  && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON))
/* ****************************************************************************
% Dem_MemObdFreezeFrame_SetFFOfEventVisible
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemObdFreezeFrame_SetFFOfEventVisible(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  )
{
  uint8 lFreezeFrameIndex;
  Dem_EventIdType lMasterEventId;

  lFreezeFrameIndex = Dem_Cfg_GlobalObdIIFFCount();
  lMasterEventId = Dem_Cfg_GetMasterEvent(EventId);

  while (lFreezeFrameIndex != 0U)
  {
    lFreezeFrameIndex--;

    if (Dem_MemObdFreezeFrame_GetEventOfObdFF(lFreezeFrameIndex) == lMasterEventId)
    {
      Dem_MemObdFreezeFrame_FreezeFrameSetVisible(lFreezeFrameIndex);
    }
  }
}
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMOBDFREEZEFRAME_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemObdFreezeFrame_Implementation.h
 *********************************************************************************************************************/
