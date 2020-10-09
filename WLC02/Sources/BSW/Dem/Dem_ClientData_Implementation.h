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
/*! \addtogroup Dem_ClientData
 *  \{
 *  \file       Dem_ClientData_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) Implementation file
 *  \details    -
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

#if !defined (DEM_CLIENTDATA_IMPLEMENTATION_H)
#define DEM_CLIENTDATA_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_ClientData_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg_Definitions.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */


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
 *  SUBCOMPONENT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/*!
 * \addtogroup Dem_ClientData_Properties
 * \{
 */

/* ****************************************************************************
 % Dem_ClientData_GetDTCSelector()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_HandleType, DEM_CODE)
Dem_ClientData_GetDTCSelector(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  Dem_DTCSelector_HandleType lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = (Dem_DTCSelector_HandleType) Dem_Cfg_GetSelectorIndexOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CFG_DTCSELECTOR_INVALID;
  }

  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_ClientData_GetFilterId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_HandleType, DEM_CODE)
Dem_ClientData_GetFilterId(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  Dem_FilterData_HandleType lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = (Dem_FilterData_HandleType) Dem_Cfg_GetFilterIndexOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CFG_FILTER_INVALID;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_ClientData_GetFreezeFrameIteratorId
*****************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FreezeFrameIterator_HandleType, DEM_CODE)
Dem_ClientData_GetFreezeFrameIteratorId(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  Dem_FreezeFrameIterator_HandleType lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = (Dem_FreezeFrameIterator_HandleType)Dem_Cfg_GetFreezeFrameIteratorIndexOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CFG_FREEZEFRAMEITERATOR_INVALID;
  }

  return lReturnValue;
}
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_ClientData_GetReadoutBufferId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_HandleType, DEM_CODE)
Dem_ClientData_GetReadoutBufferId(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  Dem_DTCReadoutBuffer_HandleType lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = (Dem_DTCReadoutBuffer_HandleType) Dem_Cfg_GetReadoutBufferIndexOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CFG_READOUTBUFFER_INVALID;
  }

  return lReturnValue;
}
#endif

/* ****************************************************************************
 % Dem_ClientData_GetClearDTCStatus()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_HandleType, DEM_CODE)
Dem_ClientData_GetClearDTCStatus(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  Dem_ClearDTC_HandleType lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = (Dem_ClearDTC_HandleType)Dem_Cfg_GetClearDTCIndexOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CLEARDTC_HANDLE_INVALID;
  }

  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 % Dem_ClientData_GetNodeId()
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_ClientData_GetNodeId(
  CONST(uint8, AUTOMATIC)  ClientId
  )
{
  uint16 lReturnValue;

  if (ClientId < Dem_Cfg_GetSizeOfClientTable())
  {
    lReturnValue = Dem_Cfg_GetNmNodeIdOfClientTable(ClientId);
  }
  else
  {
    lReturnValue = DEM_CFG_NMNODEID_INVALID;
  }

  return lReturnValue;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* DEM_CLIENTDATA_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClientData_Implementation.h
 *********************************************************************************************************************/
