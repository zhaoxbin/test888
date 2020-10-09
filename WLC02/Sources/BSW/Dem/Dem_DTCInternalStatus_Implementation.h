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
/*! \addtogroup Dem_DTCInternalStatus
 *  \{
 *  \file       Dem_DTCInternalStatus_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of DTCInternalStatus subcomponent
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

#if !defined (DEM_DTCINTERNALSTATUS_IMPLEMENTATION_H)
#define DEM_DTCINTERNALSTATUS_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCInternalStatus_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */


                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \defgroup  Dem_DTCInternalStatusBitSizes  Macros encoding bit sizes for DTC internal status
 * Macros encoding bit sizes for event internal status
 * \{
 */
#define DEM_DTCINTERNALSTATUS_STORED_STATUS_SIZE               2  /*!< bit size of stored status */
#define DEM_DTCINTERNALSTATUS_FDC_TOC_SIZE                     1  /*!< bit size of FDC trip this cycle */
#define DEM_DTCINTERNALSTATUS_SUPPRESSED_DTC_SIZE              1  /*!< bit size of DTC suppressed */
#define DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR_SIZE         1  /*!< bit size of user controlled WIR */
/*!
 * \}
 */
/*! Required byte size of DTC internal status, operates on same byte as event internal status */
#define DEM_DTC_INTERNAL_STATUS_BYTESIZE         DEM_EVENT_INTERNAL_STATUS_BYTESIZE

/*!
 * \defgroup  Dem_DTCInternalStatusBitMasks  Macros encoding bit masks for internal status
 * Macros encoding bit masks for internal status
 * \{
 */

#define DEM_DTCINTERNALSTATUS_STORED_STATUS                    DEM_NBIT(DEM_DTCINTERNALSTATUS_STORED_STATUS_SIZE, DEM_DTCINTERNALSTATUS_STORED_STATUS_POS)  /*!< Bit mask for stored status bit(s) */
#define DEM_DTCINTERNALSTATUS_STORED_STATUS_MASK               DEM_NBIT_MASK(DEM_DTCINTERNALSTATUS_STORED_STATUS_SIZE, DEM_DTCINTERNALSTATUS_STORED_STATUS_POS, DEM_DTC_INTERNAL_STATUS_BYTESIZE)  /*!< Negated bit mask for stored status bit(s) */

#define DEM_DTCINTERNALSTATUS_SUPPRESSED_DTC                   DEM_BIT(DEM_DTCINTERNALSTATUS_SUPPRESSED_DTC_POS)  /*!< Bit mask for DTC suppressed bit(s) */
#define DEM_DTCINTERNALSTATUS_SUPPRESSED_DTC_MASK              DEM_BIT_MASK(DEM_DTCINTERNALSTATUS_SUPPRESSED_DTC_POS, DEM_DTC_INTERNAL_STATUS_BYTESIZE)  /*!< Negated bit mask for DTC suppressed bit(s) */

#define DEM_DTCINTERNALSTATUS_FDC_TOC                          DEM_BIT(DEM_DTCINTERNALSTATUS_FDC_TOC_POS)  /*!< Bit mask for fault detection counter threshold this cycle bit(s) */
#define DEM_DTCINTERNALSTATUS_FDC_TOC_MASK                     DEM_BIT_MASK(DEM_DTCINTERNALSTATUS_FDC_TOC_POS, DEM_DTC_INTERNAL_STATUS_BYTESIZE)  /*!< Negated bit mask for fault detection counter threshold this cycle bit(s) */

#define DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR              DEM_BIT(DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR_POS)  /*!< Bit mask for user controlled warning indicator request bit(s) */
#define DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR_MASK         DEM_BIT_MASK(DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR_POS, DEM_EVENT_INTERNAL_STATUS_BYTESIZE)  /*!< Negated bit mask for user controlled warning indicator request bit(s) */

/*!
 * \}
 */

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
 * \addtogroup Dem_DTCInternalStatus_Properties
 * \{
 */
/* ****************************************************************************
 % Dem_DTCInternalStatus_CombinedGroupGetInternalStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId                                                                      /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(GroupId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
  return Dem_Cfg_GetCombinedGroupInternalStatus(GroupId);
#else
  return 0;
#endif
}

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTCInternalStatus_CombinedGroupSetInternalStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC)  GroupId,
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  Status
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (GroupId >= Dem_Cfg_GetSizeOfCombinedGroupInternalStatus())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_SetCombinedGroupInternalStatus(GroupId, Status);                                                                     /* SBSW_DEM_ARRAY_WRITE_COMBINEDGROUPINTERNALSTATUS */
  }
}
#endif

/* ****************************************************************************
 % Dem_DTCInternalStatus_GetStoredStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTCInternal_StoredStatusType, DEM_CODE)
Dem_DTCInternalStatus_GetStoredStatus(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  return (Dem_DTCInternal_StoredStatusType)(InternalStatus & DEM_DTCINTERNALSTATUS_STORED_STATUS);
}

/* ****************************************************************************
 % Dem_DTCInternalStatus_SetStoredStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_SetStoredStatus(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus,
  CONST(Dem_DTCInternal_StoredStatusType, AUTOMATIC)  StoredStatus
  )
{
  return (Dem_DTC_InternalStatusType)
    ((InternalStatus & DEM_DTCINTERNALSTATUS_STORED_STATUS_MASK) | ((Dem_DTC_InternalStatusType)StoredStatus & DEM_DTCINTERNALSTATUS_STORED_STATUS));
}

/* Internal status bit 'DTC suppressed' ------------------------------------ */

/* ****************************************************************************
 % Dem_DTCInternalStatus_TestDtcSuppressed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCInternalStatus_TestDtcSuppressed(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(InternalStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
  return (boolean)((InternalStatus & DEM_DTCINTERNALSTATUS_SUPPRESSED_DTC) != 0);
#else
  return FALSE;
#endif
}

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_DTCInternalStatus_SetDtcSuppressed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_SetDtcSuppressed(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  return (Dem_DTC_InternalStatusType)(InternalStatus | DEM_DTCINTERNALSTATUS_SUPPRESSED_DTC);
}
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 % Dem_DTCInternalStatus_ResetDtcSuppressed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_ResetDtcSuppressed(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  return (Dem_DTC_InternalStatusType)(InternalStatus & DEM_DTCINTERNALSTATUS_SUPPRESSED_DTC_MASK);
}
#endif

/* Internal status bit 'event crossed FDC threshold in this cycle' --------- */

/* ****************************************************************************
 % Dem_DTCInternalStatus_TestFdcToc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCInternalStatus_TestFdcToc(                                                                                              /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(InternalStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
#if (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON)
  return (boolean)((InternalStatus & DEM_DTCINTERNALSTATUS_FDC_TOC) != 0);
#else
  return FALSE;
#endif
}

/* ****************************************************************************
 % Dem_DTCInternalStatus_SetFdcToc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_SetFdcToc(                                                                                               /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
#if (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON)
  return (Dem_DTC_InternalStatusType)(InternalStatus | DEM_DTCINTERNALSTATUS_FDC_TOC);
#else
  return InternalStatus;
#endif
}

/* ****************************************************************************
 % Dem_DTCInternalStatus_ResetFdcToc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_ResetFdcToc(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
#if (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON)
  return (Dem_DTC_InternalStatusType)(InternalStatus & DEM_DTCINTERNALSTATUS_FDC_TOC_MASK);
#else
  return InternalStatus;
#endif
}

/* Extended Status bit 'TestPassedSinceLastClear' ----------------------------------------------- */
#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
 /* ****************************************************************************
 % Dem_DTCInternalStatus_TestExtendedStatus_TPSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCInternalStatus_TestExtendedStatus_TPSLC(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  Status
  )
{
  return  (((Status) & DEM_EXT_STATUS_TPSLC) != 0);
}
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
 % Dem_DTCInternalStatus_SetExtendedStatus_TPSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_DTCInternalStatus_SetExtendedStatus_TPSLC(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  Status
  )
{
  return  ((Status) | DEM_EXT_STATUS_TPSLC);
}
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
 % Dem_DTCInternalStatus_Reset_ExtendedStatus_TPSLC()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_DTCInternalStatus_Reset_ExtendedStatus_TPSLC(                                                                                /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  Status
  )
{
  return  ((Dem_Event_ExtendedStatusType)((Status) & DEM_EXT_STATUS_TPSLC_MASK));
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
 * \addtogroup Dem_DTCInternalStatus_Private
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
 * \addtogroup Dem_DTCInternalStatus_Public
 * \{
 */

/* Internal status bit 'user controlled warning indicator' ----------------- */

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) || (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 % Dem_DTCInternalStatus_TestUserControlledWir
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCInternalStatus_TestUserControlledWir(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus                                                                 /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(InternalStatus)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
  return (boolean)((InternalStatus & DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR) != 0);
# else
  return FALSE;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 % Dem_DTCInternalStatus_SetUserControlledWir
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_SetUserControlledWir(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  return (Dem_Event_InternalStatusType)(InternalStatus | DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR);
}
#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 % Dem_DTCInternalStatus_ResetUserControlledWir
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_ResetUserControlledWir(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC)  InternalStatus
  )
{
  return (Dem_Event_InternalStatusType)(InternalStatus & DEM_DTCINTERNALSTATUS_USER_CONTROLLED_WIR_MASK);
}
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DTCINTERNALSTATUS_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCInternalStatus_Implementation.h
 *********************************************************************************************************************/
