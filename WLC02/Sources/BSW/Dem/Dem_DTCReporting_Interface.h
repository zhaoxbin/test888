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
 *  \defgroup   Dem_DTCReporting DTCReporting
 *  \{
 *  \file       Dem_DTCReporting_Interface.h
 *  \brief      DTC Reporting Settings
 *  \details    Global Settings regarding DTC reports
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

#if !defined (DEM_DTCREPORTING_INTERFACE_H)
#define DEM_DTCREPORTING_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCReporting_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DTCReporting_Properties Properties
 * \{
 */

#if (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON) || (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DTCReporting_TestObdHideOccurrences
 *****************************************************************************/
/*!
 * \brief         Test flag HideOBDOccurrences 
 *
 * \details       Test flag HideOBDOccurrences 
 *
 * \return        TRUE
 *                Flag HideOBDOccurrences is set
 * \return        TRUE
 *                Flag HideOBDOccurrences is not set
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON ||
 *                DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCReporting_TestObdHideOccurrences(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON)
/* ****************************************************************************
 * Dem_DTCReporting_SetObdHideOccurrences
 *****************************************************************************/
/*!
 * \brief         Set flag HideOBDOccurrences 
 *
 * \details       Set flag HideOBDOccurrences 
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReporting_SetObdHideOccurrences(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON)
/* ****************************************************************************
 * Dem_DTCReporting_ResetObdHideOccurrences
 *****************************************************************************/
/*!
 * \brief         Reset flag HideOBDOccurrences 
 *
 * \details       Reset flag HideOBDOccurrences 
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCReporting_ResetObdHideOccurrences(
  void
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DTCREPORTING_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCReporting_Interface.h
 *********************************************************************************************************************/
