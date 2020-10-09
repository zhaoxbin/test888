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
/*! \ingroup    Dem_DTC
 *  \defgroup   Dem_DTCInternalStatus DTC Internal Status
 *  \{
 *  \file       Dem_DTCInternalStatus_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interfaces of DTCInternalStatus subcomponent
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

#if !defined (DEM_DTCINTERNALSTATUS_INTERFACE_H)
#define DEM_DTCINTERNALSTATUS_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCInternalStatus_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DTCInternalStatus_Properties Properties
 * \{
 */
/* ****************************************************************************
 * Dem_DTCInternalStatus_CombinedGroupGetInternalStatus
 *****************************************************************************/
/*!
 * \brief         Get current internal status of the combined group
 *
 * \details       Get current internal status of the combined group
 *
 * \param[in]     GroupId
 *                Unique handle of the combined group
 *
 * \return        Current internal status of the combined group
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_CombinedGroupGetInternalStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId
  );

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTCInternalStatus_CombinedGroupSetInternalStatus
 *****************************************************************************/
/*!
 * \brief         Set current internal status of the combined group
 *
 * \details       Set current internal status of the combined group
 *
 * \param[in]     GroupId
 *                Unique handle of the combined group
 * \param[in]     Status
 *                New internal status the combined group
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCInternalStatus_CombinedGroupSetInternalStatus(
  CONST(Dem_Cfg_CombinedGroupIndexType, AUTOMATIC) GroupId,
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC) Status
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

/* ****************************************************************************
 * Dem_DTCInternalStatus_GetStoredStatus
 *****************************************************************************/
/*!
 * \brief         Get the stored status from internal status byte
 *
 * \details       Get the stored status from internal status byte.
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        The stored status (Dem_Esm_StoredStatus)
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCInternal_StoredStatusType, DEM_CODE)
Dem_DTCInternalStatus_GetStoredStatus(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* ****************************************************************************
 * Dem_DTCInternalStatus_SetStoredStatus
 *****************************************************************************/
/*!
 * \brief         Set the stored status in the internal status byte
 *
 * \details       Set the stored status in the internal status byte.
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 * \param[in]     StoredStatus
 *                The new storage status to set
 *
 * \return        Internal status byte with modified stored status.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_SetStoredStatus(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC) InternalStatus,
  CONST(Dem_DTCInternal_StoredStatusType, AUTOMATIC) StoredStatus
  );

/* Internal status bit 'DTC suppressed' ------------------------------------ */

/* ****************************************************************************
 * Dem_DTCInternalStatus_TestDtcSuppressed
 *****************************************************************************/
/*!
 * \brief         Test if DTC suppressed is set in the internal status
 *
 * \details       -
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCInternalStatus_TestDtcSuppressed(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC) InternalStatus
  );

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_DTCInternalStatus_SetDtcSuppressed
 *****************************************************************************/
/*!
 * \brief         Set DTC suppressed in the internal status
 *
 * \details       -
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag set.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_SetDtcSuppressed(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC) InternalStatus
  );
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_DTCInternalStatus_ResetDtcSuppressed
 *****************************************************************************/
/*!
 * \brief         Reset DTC suppressed in the internal status
 *
 * \details       -
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag reset.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_ResetDtcSuppressed(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC) InternalStatus
  );
#endif

/* Internal status bit 'event already crossed FDC threshold in this cycle' - */

/* ****************************************************************************
 * Dem_DTCInternalStatus_TestFdcToc
 *****************************************************************************/
/*!
 * \brief         Test if event fdc max this cycle is set in the internal status
 *
 * \details       Test if event fdc max this cycle is set in the internal status
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 * \config        -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCInternalStatus_TestFdcToc(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* ****************************************************************************
 * Dem_DTCInternalStatus_SetFdcToc
 *****************************************************************************/
/*!
 * \brief         Set event fdc max this cycle in the internal status
 *
 * \details       Set event fdc max this cycle in the internal status. Only
 *                has an effect if maximum fdc calculation is supported
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_SetFdcToc(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* ****************************************************************************
 * Dem_DTCInternalStatus_ResetFdcToc
 *****************************************************************************/
/*!
 * \brief         Reset event fdc max this cycle in the internal status
 *
 * \details       Reset event fdc max this cycle in the internal status. Only
 *                has an effect if maximum fdc calculation is supported
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag reset.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTC_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_ResetFdcToc(
  CONST(Dem_DTC_InternalStatusType, AUTOMATIC) InternalStatus
  );

/* Extended Status bit 'TestPassedSinceLastClear' ---------------------------*/
#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_DTCInternalStatus_TestExtendedStatus_TPSLC
 *****************************************************************************/
/*!
 * \brief         Test test passed since last clear state of extended status of event
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current extended status of the event
 *
 * \return        TRUE
 *                The TPSLC bit is set
 * \return        FALSE
 *                The TPSLC bit is cleared
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCInternalStatus_TestExtendedStatus_TPSLC(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  Status
  );
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_DTCInternalStatus_SetExtendedStatus_TPSLC
 *****************************************************************************/
/*!
 * \brief         Set test passed since last clear state of extended status of event
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current extended status of the event
 *
 * \return        Event extended status with flag set for TPSLC.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_DTCInternalStatus_SetExtendedStatus_TPSLC(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  Status
  );
#endif

#if (DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON)
/* ****************************************************************************
 * Dem_DTCInternalStatus_Reset_ExtendedStatus_TPSLC
 *****************************************************************************/
/*!
 * \brief         Reset test passed since last clear state of extended status of event
 *
 * \details       -
 *
 * \param[in]     Status
 *                Current extended status of the event
 *
 * \return        Event extended status with flag cleared for TPSLC.
 *
 * \pre           -
 * \config        DEM_FEATURE_NEED_PID01_CALCULATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_ExtendedStatusType, DEM_CODE)
Dem_DTCInternalStatus_Reset_ExtendedStatus_TPSLC(
  CONST(Dem_Event_ExtendedStatusType, AUTOMATIC)  Status
  );
#endif
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DTCInternalStatus_Private Private Methods
 * \{
 */

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DTCInternalStatus_Public Public Methods
 * \{
 */

/* Internal status bit 'user controlled warning indicator' ----------------- */

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON) || (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
/* ****************************************************************************
 * Dem_DTCInternalStatus_TestUserControlledWir
 *****************************************************************************/
/*!
 * \brief         Test if user controlled WIR is set in the internal status
 *
 * \details       Test if user controlled WIR is set in the internal status
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        TRUE
 *                Flag is set
 * \return        FALSE
 *                Flag is not set
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON
 *             || DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCInternalStatus_TestUserControlledWir(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );
#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 * Dem_DTCInternalStatus_SetUserControlledWir
 *****************************************************************************/
/*!
 * \brief         Set user controlled WIR in the internal status
 *
 * \details       Set user controlled WIR in the internal status.
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag set
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_SetUserControlledWir(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );
#endif

#if (DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON)
/* ****************************************************************************
 * Dem_DTCInternalStatus_ResetUserControlledWir
 *****************************************************************************/
/*!
 * \brief         Reset user controlled WIR in the internal status
 *
 * \details       Reset user controlled WIR in the internal status.
 *
 * \param[in]     InternalStatus
 *                Internal status byte
 *
 * \return        InternalStatus with flag reset
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_USER_CONTROLLED_WIR == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_Event_InternalStatusType, DEM_CODE)
Dem_DTCInternalStatus_ResetUserControlledWir(
  CONST(Dem_Event_InternalStatusType, AUTOMATIC) InternalStatus
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DTCINTERNALSTATUS_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCInternalStatus_Interface.h
 *********************************************************************************************************************/
