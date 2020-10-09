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
/*! \ingroup    Dem_ClientAccess
 *  \defgroup   Dem_ClientData ClientData
 *  \{
 *  \file       Dem_ClientData_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
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

#if !defined (DEM_CLIENTDATA_INTERFACE_H)
#define DEM_CLIENTDATA_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ClientData_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_ClientData_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_ClientData_GetDTCSelector()
 *****************************************************************************/
/*!
 * \brief         Get the DTC selector of a client.
 *
 * \details       Get the DTC selector of a client.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        The DTCSelector handle reserved for the Client. If no such
 *                selector exists, this function returns DEM_DTCSELECTOR_INVALID.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_HandleType, DEM_CODE)
Dem_ClientData_GetDTCSelector(
  CONST(uint8, AUTOMATIC)  ClientId
  );

#if (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_ClientData_GetFilterId()
 *****************************************************************************/
/*!
 * \brief         Get the filter of a client.
 *
 * \details       Get the filter of a client.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        The filter handle reserved for the Client. If no such
 *                filter exists, this function returns DEM_FILTER_INVALID.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON || 
 *                DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FilterData_HandleType, DEM_CODE)
Dem_ClientData_GetFilterId(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_ClientData_GetFreezeFrameIteratorId()
 *****************************************************************************/
/*!
 * \brief         Get the FreezeFrameIterator of a client.
 *
 * \details       Get the FreezeFrameIterator of a client.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        The FreezeFrameIterator handle reserved for the Client. If no
 *                such FreezeFrameIterator exists, this function returns
 *                DEM_CFG_FREEZEFRAMEITERATOR_INVALID.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON || 
 *                DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_FreezeFrameIterator_HandleType, DEM_CODE)
Dem_ClientData_GetFreezeFrameIteratorId(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientData_GetReadoutBufferId()
 *****************************************************************************/
/*!
 * \brief         Get the readout buffer of a client.
 *
 * \details       Get the readout buffer of a client.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        The readout buffer handle reserved for the Client. If no
 *                such readout buffer exists, this function returns
 *                DEM_CFG_READOUTBUFFER_INVALID.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_HandleType, DEM_CODE)
Dem_ClientData_GetReadoutBufferId(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

/* ****************************************************************************
 * Dem_ClientData_GetClearDTCStatus()
 *****************************************************************************/
/*!
 * \brief         Get the ClearDTC status of a client.
 *
 * \details       Get the ClearDTC status of a client.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        The clearDTC handle reserved for the Client. If no such
 *                handle exists, this function returns DEM_CLEARDTC_HANDLE_INVALID.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_HandleType, DEM_CODE)
Dem_ClientData_GetClearDTCStatus(
  CONST(uint8, AUTOMATIC)  ClientId
  );

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_ClientData_GetNodeId()
 *****************************************************************************/
/*!
 * \brief         Get the node of a client.
 *
 * \details       Get the node of a client.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        The node handle reserved for the Client. If no such
 *                handle exists, this function returns DEM_CFG_NMNODEID_INVALID.
 *
 * \pre           DEM_CFG_SUPPORT_J1939 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_ClientData_GetNodeId(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

 /* ********************************************************************************************************************
  *  SUBCOMPONENT API FUNCTION DECLARATIONS
  *********************************************************************************************************************/

 /* ********************************************************************************************************************
  *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
  *********************************************************************************************************************/

#endif /* DEM_CLIENTDATA_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClientData_Interface.h
 *********************************************************************************************************************/
