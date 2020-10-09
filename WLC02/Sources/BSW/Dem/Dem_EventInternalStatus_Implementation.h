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
/*! \addtogroup Dem_EventInternalStatus
 *  \{
 *  \file       Dem_EventInternalStatus_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of EventInternalStatus subcomponent
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

#if !defined (DEM_EVENTINTERNALSTATUS_IMPLEMENTATION_H)
#define DEM_EVENTINTERNALSTATUS_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_EventInternalStatus_Interface.h"
                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_UDSStatus_Implementation.h"
                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
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
 * \addtogroup Dem_EventInternalStatus_Properties
 * \{
 */

/* Internal status bit 'event available' ----------------------------------- */

/* ****************************************************************************
 % Dem_EventInternalStatus_TestEventDisconnected
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(InternalStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
  return (boolean)((InternalStatus & DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT) != 0);
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_EventInternalStatus_SetEventDisconnected
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
  return (Dem_Event_InternalStatusType)(InternalStatus | DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT);
#else
  return InternalStatus;
#endif
}

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON) || (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_ResetEventDisconnected
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetEventDisconnected(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  return (Dem_Event_InternalStatusType)(InternalStatus & DEM_EVENTINTERNALSTATUS_DISCONNECTED_EVENT_MASK);
}
#endif

/* Internal status bit 'event suppressed' ---------------------------------- */

/* ****************************************************************************
 % Dem_EventInternalStatus_TestAvailabilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestAvailabilityChanged(                                                                                 /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(InternalStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return (boolean)((InternalStatus & DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED) != 0);
}

/* ****************************************************************************
 % Dem_EventInternalStatus_SetAvailabilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetAvailabilityChanged(                                                                                  /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  return (Dem_Event_InternalStatusType)(InternalStatus | DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED);
}

/* ****************************************************************************
 % Dem_EventInternalStatus_ResetAvailabilityChanged
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetAvailabilityChanged(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  return (Dem_Event_InternalStatusType)(InternalStatus & DEM_EVENTINTERNALSTATUS_AVAILABILITY_CHANGED_MASK);
}


/* Internal status bit 'DTC disabled by PB selectable' --------------------- */

/* ****************************************************************************
 % Dem_EventInternalStatus_TestAvailableInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestAvailableInVariant(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(InternalStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_ISCONST_AVAILABLEINVARIANT != STD_ON) && (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  return (boolean)((InternalStatus & DEM_EVENTINTERNALSTATUS_AVAILABLEINVARIANT) != 0);
#else
  return TRUE;
#endif
}

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_SetAvailableInVariant
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_SetAvailableInVariant(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
# if (DEM_CFG_ISCONST_AVAILABLEINVARIANT != STD_ON)
  return (Dem_Event_InternalStatusType)(InternalStatus | DEM_EVENTINTERNALSTATUS_AVAILABLEINVARIANT);
# else
  return InternalStatus;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_TestSimilarConditions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_TestSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
  )
{
  return (boolean)((ExtendedStatus & DEM_EXT_STATUS_SIMILAR_CONDITIONS) != 0);
}
#endif

#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_SetSimilarConditions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_EventInternalStatus_SetSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
  )
{
  return (Dem_Event_ExtendedStatusType)(ExtendedStatus | DEM_EXT_STATUS_SIMILAR_CONDITIONS);
}
#endif

/* ****************************************************************************
 % Dem_EventInternalStatus_ResetSimilarConditions
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_EventInternalStatus_ResetSimilarConditions(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  ExtendedStatus
  )
{
  Dem_Event_ExtendedStatusType lReturnValue;
  lReturnValue = ExtendedStatus;
#if (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON)
  lReturnValue = (Dem_Event_ExtendedStatusType)(lReturnValue & DEM_EXT_STATUS_SIMILAR_CONDITIONS_MASK);
#endif
  return lReturnValue;
}

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_GetMilGroupTripCountRaw
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_EventInternalStatus_GetMilGroupTripCountRaw(
  CONST(uint16, AUTOMATIC)  MilGroupIndex
  )
{
  return (Dem_Cfg_StatusData.MilGroupTripCount[MilGroupIndex]);
}
#endif

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_SetMilGroupTripCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventInternalStatus_SetMilGroupTripCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex,
  CONST(uint8, AUTOMATIC)  TripCount
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (MilGroupIndex >= Dem_Cfg_GlobalMilGroupCount())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_StatusData.MilGroupTripCount[MilGroupIndex] = TripCount;                                                             /* SBSW_DEM_ARRAY_WRITE_STATUSDATA_MILGROUPTRIPCOUNT */
  }
}
#endif

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_GetMilGroupPendingCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_EventInternalStatus_GetMilGroupPendingCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex
  )
{
  return Dem_Cfg_StatusData.MilGroupActiveEvents[MilGroupIndex];
}
#endif

#if (DEM_FEATURE_NEED_MIL_GROUPS == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_SetMilGroupPendingCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_EventInternalStatus_SetMilGroupPendingCount(
  CONST(uint16, AUTOMATIC)  MilGroupIndex,
  CONST(uint16, AUTOMATIC)  PendingCount
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if ( (MilGroupIndex >= Dem_Cfg_GlobalMilGroupCount())
    || (PendingCount > 0xffU) )
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_StatusData.MilGroupActiveEvents[MilGroupIndex] = (uint8)PendingCount;                                                /* SBSW_DEM_ARRAY_WRITE_STATUSDATA_MILGROUPACTIVEEVENTS */
  }
}
#endif

/* Qualify status bit 'confirmedDTC' --------------------------------------- */
#if (DEM_FEATURE_NEED_OBD == STD_ON)
 /* ****************************************************************************
 % Dem_EventInternalStatus_Test_QualifyStatus_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_Test_QualifyStatus_CDTC(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_CDTC) != 0);
}
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_Set_QualifyStatus_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Set_QualifyStatus_CDTC(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (Dem_Event_InternalStatusType)((Status) | DEM_UDS_STATUS_CDTC);
}
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_Reset_QualifyStatus_CDTC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Reset_QualifyStatus_CDTC(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (Dem_Event_InternalStatusType)((Status) & DEM_UDS_STATUS_CDTC_MASK);
}
#endif

/* Qualify status bit 'warningIndicatorRequested' -------------------------- */
#if (DEM_FEATURE_NEED_OBD == STD_ON)
 /* ****************************************************************************
 % Dem_EventInternalStatus_Test_QualifyStatus_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_EventInternalStatus_Test_QualifyStatus_WIR(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (boolean)(((Status) & DEM_UDS_STATUS_WIR) != 0);
}
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_Set_QualifyStatus_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Set_QualifyStatus_WIR(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (Dem_Event_InternalStatusType)((Status) | DEM_UDS_STATUS_WIR);
}
#endif

#if (DEM_FEATURE_NEED_OBD == STD_ON)
/* ****************************************************************************
 % Dem_EventInternalStatus_Reset_QualifyStatus_WIR()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_EventInternalStatus_Reset_QualifyStatus_WIR(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  Status
  )
{
  return (Dem_Event_InternalStatusType)((Status)& DEM_UDS_STATUS_WIR_MASK);
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

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#endif /* DEM_EVENTINTERNALSTATUS_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_EventInternalStatus_Implementation.h
 *********************************************************************************************************************/
