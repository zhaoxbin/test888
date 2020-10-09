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
/*! \addtogroup Dem_API
 *  \{
 *  \file       Dem_Cbk.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Callback API declarations of the MICROSAR Dem.
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

#if !defined (DEM_CBK_H)
#define DEM_CBK_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Dem.h"

#if (DEM_CFG_USE_NVM == STD_ON)
# include "NvM.h"
#endif

/* ********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_API_Public
 * \{
 */

/* ****************************************************************************
 * Dem_NvM_InitAdminData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for administrative data
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is not initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitAdminData(
  void
  );

/* ****************************************************************************
 * Dem_NvM_InitStatusData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for event status data
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is not initialized
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitStatusData(
  void
  );

#if (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON)
/* ****************************************************************************
 * Dem_NvM_InitDebounceData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for persisted debounce values
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is not initialized
 * \config        DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitDebounceData(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON) && (DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON)
/* ****************************************************************************
 * Dem_NvM_InitEventAvailableData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for persisted event availability
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is not initialized
 * \config        (DEM_CFG_SUPPORT_EVENTAVAILABLE == STD_ON)
 *                && (DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitEventAvailableData(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_NvM_InitObdFreezeFrameData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for freeze frame data
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is not initialized
 * \config        (DEM_CFG_SUPPORT_OBDII == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitObdFreezeFrameData(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_NvM_InitObdPermanentData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for permanent DTCs
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is not initialized
 * \config        (DEM_CFG_SUPPORT_OBDII == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitObdPermanentData(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/* ****************************************************************************
 * Dem_NvM_InitObdIumprData
 *****************************************************************************/
/*!
 * \brief         Initializes the NvBlock for ratio data
 *
 * \details       This function is supposed to be called by the NvM in order to
 *                (re)initialize the data in case the non-volatile memory has
 *                never been stored, or was corrupted.
 *                (See NvMBlockDescriptor/NvMInitBlockCallback)
 *                It can also be used to force a reinitialization of the Dem
 *                data triggered by the application (e.g. after a new software
 *                version has been flashed to the ECU). In the latter case,
 *                make sure the function is not called while the Dem is active.
 *
 * \return        E_OK
 *
 * \pre           Dem is not initialized
 * \config        (DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitObdIumprData(
  void
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON)
/* ****************************************************************************
* Dem_NvM_InitDtrData
*****************************************************************************/
/*!
* \brief         Initializes the NvBlock for Dtr data
*
* \details       This function is supposed to be called by the NvM in order to
*                (re)initialize the data in case the non-volatile memory has
*                never been stored, or was corrupted.
*                (See NvMBlockDescriptor/NvMInitBlockCallback)
*                It can also be used to force a reinitialization of the Dem
*                data triggered by the application (e.g. after a new software
*                version has been flashed to the ECU). In the latter case,
*                make sure the function is not called while the Dem is active.
*
* \return        E_OK
*
* \pre           Dem is not initialized
* \config        DEM_CFG_SUPPORT_DTR == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     FALSE
*****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitDtrData(
  void
  );
#endif

#if (DEM_FEATURE_NEED_AGING_DATA == STD_ON)
/* ****************************************************************************
* Dem_NvM_InitAgingData
*****************************************************************************/
/*!
* \brief         Initializes the NvBlock for Aging Counter data
*
* \details       This function is supposed to be called by the NvM in order to
*                (re)initialize the data in case the non-volatile memory has
*                never been stored, or was corrupted.
*                (See NvMBlockDescriptor/NvMInitBlockCallback)
*                It can also be used to force a reinitialization of the Dem
*                data triggered by the application (e.g. after a new software
*                version has been flashed to the ECU). In the latter case,
*                make sure the function is not called while the Dem is active.
*
* \return        E_OK
*
* \pre           Dem is not initialized
* \config        DEM_FEATURE_NEED_AGING_DATA == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     FALSE
*****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_InitAgingData(
  void
  );
#endif

#if ((DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF))
/* ****************************************************************************
 * Dem_NvM_JobFinished
 *****************************************************************************/
/*!
 * \brief         Notifies the Dem module about a completed NV operation
 *
 * \details       This function has to be called by the NvM after a write
 *                operation has finished.
 *                (See NvMBlockDescriptor/NvMSingleBlockCallback)
 *
 * \param[in]     ServiceId
 *                Service identifier
 * \param[in]     JobResult
 *                Result of the NV job
 *
 * \return        E_OK
 *
 * \pre           -
 * \config        (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_SUPPORT_NVM_POLLING == STD_OFF)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_NvM_JobFinished(
  uint8 ServiceId,
  NvM_RequestResultType JobResult
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \}
 */
#endif /* DEM_CBK_H */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Cbk.h
 *********************************************************************************************************************/
