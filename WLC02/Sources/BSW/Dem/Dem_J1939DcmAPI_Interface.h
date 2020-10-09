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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_J1939DcmAPI J1939Dcm interface
 *  \{
 *  \file       Dem_J1939DcmAPI_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    
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

#if !defined (DEM_J1939DCMAPI_INTERFACE_H)
#define DEM_J1939DCMAPI_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_J1939DcmAPI_Types.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
# define DEM_START_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_J1939DcmAPI_Private Private Methods
 * \{
 */

/*!
 * \}
 */
# define DEM_STOP_SEC_CODE
# include "MemMap.h"                                                                                                             /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_J1939DcmAPI_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON)
/* ****************************************************************************
 * Dem_J1939DcmClearDTC
 *****************************************************************************/
/*!
 * \brief         Clear the J1939 DTCs.
 *
 * \details       Clears the J1939 DTCs.
 *
 * \param[in]     DTCTypeFilter
 *                DEM_J1939DTC_CLEAR_ACTIVE
 *                All active DTCs shall be cleared.
 *                DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE
 *                All previously active DTCs shall be cleared.
 *                DEM_J1939DTC_CLEAR_ACTIVE_AND_PREVIOUSLY_ACTIVE
 *                All active and previously active DTCs shall be cleared.
 * \param[in]     DTCOrigin
 *                The external identifier of the event memory.
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                DTC successfully cleared
 * \return        DEM_WRONG_DTC
 *                DTC value not existing (in this format)
 * \return        DEM_WRONG_DTCORIGIN
 *                Wrong DTC origin
 * \return        DEM_CLEAR_FAILED
 *                DTC clearing failed
 * \return        DEM_CLEAR_MEMORY_ERROR
 *                The clear operation has completed, but the NV synchronization
 *                has failed
 * \return        DEM_PENDING
 *                The clear operation was started and is currently processed
 * \return        DEM_CLEAR_BUSY
 *                Another clear operation is currently processing
 *
 * \config        DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmClearDTC(
  Dem_J1939DcmSetClearFilterType  DTCTypeFilter,
  Dem_DTCOriginType  DTCOrigin,
  uint8  ClientId
);
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_J1939DcmFirstDTCwithLampStatus
 *****************************************************************************/
/*!
 * \brief         Initialize the filter mechanism to the first event in the
 *                primary memory.
 *
 * \details       Initializes the filter mechanism to the first event in the
 *                primary memory.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \config           DEM_CFG_SUPPORT_J1939_DM31 == STD_ON
 *                && DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(void, DEM_CODE)
Dem_J1939DcmFirstDTCwithLampStatus(
  uint8  ClientId
);
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_J1939DcmGetNextDTCwithLampStatus
 *****************************************************************************/
/*!
 * \brief         Get the next filtered J1939 DTC for DM31 including current
 *                LampStatus.
 *
 * \details       Return the next filtered J1939 DTC for DM31 including current
 *                LampStatus.
 *
 * \param[out]    LampStatus
 *                Pointer to the LampStatus buffer.
 * \param[out]    J1939DTC
 *                Pointer to the J1939DTC buffer.
 * \param[out]    OccurrenceCounter
 *                Pointer to the OccurrenceCounter buffer.
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                A matching DTC was returned.
 * \return        DEM_NO_SUCH_ELEMENT
 *                No further element was found, iteration is complete.
 * \return        DEM_PENDING
 *                Never returned by this implementation.
 *
 * \config           DEM_CFG_SUPPORT_J1939_DM31 == STD_ON
 *                && DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 * \pre           A filter has been initialized using
 *                Dem_J1939DcmFirstDTCwithLampStatus
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextDTCwithLampStatus(
  P2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_J1939DCM_DATA)  LampStatus,
  P2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter,
  uint8  ClientId
);
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_J1939DcmSetDTCFilter
 *****************************************************************************/
/*!
 * \brief         Initialize the filter criteria for the J1939 DTC filter
 *                mechanism.
 *
 * \details       This function sets up the filter parameters to iterate all
 *                matching DTCs. If the filter is valid, the node specific
 *                lamp status is returned immediately, according to J1939.
 *                format:
 *                HighByte
 *                 bits 7,6 - Malfunction Indicator Lamp Status
 *                 bits 5,4 - Red Stop Lamp Status
 *                 bits 3,2 - Amber Warning Lamp Status
 *                 bits 1,0 - Protect Lamp Status
 *                LowByte
 *                 bits 7,6 - Flash Malfunction Indicator Lamp
 *                 bits 5,4 - Flash Red Stop Lamp
 *                 bits 3,2 - Flash Amber Warning Lamp
 *                 bits 1,0 - Flash Protect Lamp
 *
 * \param[in]     DTCStatusFilter
 *                DTC status to filter.
 * \param[in]     DTCKind
 *                DTC kind to filter.
 * \param[in]     DTCOrigin
 *                The external identifier of the event memory.
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    LampStatus
 *                Pointer to receive the Lamp status for the requested node.
 *
 * \return        E_OK
 *                The filter parameters were accepted.
 * \return        E_NOT_OK
 *                The filter could not be set.
 *
 * \config        DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmSetDTCFilter(
  Dem_J1939DcmDTCStatusFilterType  DTCStatusFilter,
  Dem_DTCKindType  DTCKind,
  Dem_DTCOriginType  DTCOrigin,
  uint8  ClientId,
  P2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_J1939DCM_DATA)  LampStatus
);
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_J1939DcmGetNumberOfFilteredDTC
 *****************************************************************************/
/*!
 * \brief         Calculate the number of DTCs matching the filter criteria.
 *
 * \details       Calculates the number of DTCs matching the filter criteria.
 *
 * \param[out]    NumberOfFilteredDTC
 *                Pointer to receive the DTC count.
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                The number of matching DTCs was returned.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The number of matching DTCs could not be calculated.
 * \return        DEM_PENDING
 *                Never returned by this implementation.
 *
 * \config        DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 * \pre           The filter has to be initialized by Dem_J1939DcmSetDTCFilter
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNumberOfFilteredDTC(
  P2VAR(uint16, AUTOMATIC, DEM_J1939DCM_DATA)  NumberOfFilteredDTC,
  uint8  ClientId
);
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_J1939DcmGetNextFilteredDTC
 *****************************************************************************/
/*!
 * \brief         Get the next matching DTC.
 *
 * \details       Returns the next matching DTC.
 *
 * \param[out]    J1939DTC
 *                Pointer to receive the J1939 DTC number.
 * \param[out]    OccurrenceCounter
 *                Pointer to receive the occurrence counter.
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                The next filtered element was returned
 * \return        DEM_NO_SUCH_ELEMENT
 *                No further element was found, iteration is complete
 * \return        DEM_PENDING
 *                Never returned by this implementation.
 *
 * \config        DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 * \pre           The filter has to be initialized by Dem_J1939DcmSetDTCFilter
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextFilteredDTC(
  P2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter,
  uint8  ClientId
);
#endif

#if (DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON) || (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_J1939DcmSetFreezeFrameFilter
 *****************************************************************************/
/*!
 * \brief         Initialize the filter criteria for freeze frame access.
 *
 * \details       Initializes the filter criteria for freeze frame access.
 *
 * \param[in]     FreezeFrameKind
 *                DEM_J1939DCM_FREEZEFRAME
 *                Set the filter for J1939 Freeze Frame data.
 *                DEM_J1939DCM_EXPANDED_FREEZEFRAME
 *                Set the filter for J1939 Expanded Freeze Frame data.
 *                DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME
 *                Not supported, DM24 message is handled by J1939Dcm.
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                The filter parameters were accepted.
 * \return        E_NOT_OK
 *                Filter could not be set.
 *
 * \config           DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON
 *                || DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmSetFreezeFrameFilter(
  Dem_J1939DcmSetFreezeFrameFilterType  FreezeFrameKind,
  uint8  ClientId
);
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_J1939DcmGetNextFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Get the next J1939DTC and Freeze Frame matching the
 *                filter criteria.
 *
 * \details       Returns the next J1939DTC and Freeze Frame matching the
 *                filter criteria.
 *
 * \param[out]    J1939DTC
 *                Pointer to the J1939DTC buffer.
 * \param[out]    OccurrenceCounter
 *                Pointer to the OccurrenceCounter buffer.
 * \param[out]    DestBuffer
 *                Pointer to the output buffer.
 * \param[in,out] BufSize
 *                In: Available space in the receiving buffer.
 *                Out: Number of written bytes.
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                The next filtered element was returned.
 * \return        DEM_NO_SUCH_ELEMENT
 *                No further element was found, iteration is complete.
 * \return        DEM_PENDING
 *                The operation was started and is currently processed.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer is not large enough.
 *
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 * \pre           A filter has been initialized using Dem_J1939DcmSetFreezeFrameFilter
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextFreezeFrame(
  P2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  DestBuffer,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  BufSize,
  uint8  ClientId
);
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_J1939DcmGetNextSPNInFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Get the SPNs that are stored in the J1939 FreezeFrame(s).
 *
 * \details       This function does nothing as the data is directly provided 
 *                from J1939Dcm.
 *
 * \param[out]    SPNSupported
 *                Pointer to receive the SPN number.
 * \param[out]    SPNDataLength
 *                Pointer to receive the data length.
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        DEM_NO_SUCH_ELEMENT always
 *
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 * \pre           A filter has been initialized using
 *                Dem_J1939DcmSetFreezeFrameFilter
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextSPNInFreezeFrame(
  P2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  SPNSupported,
  P2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  SPNDataLength, 
  uint8  ClientId
);
#endif

#if (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON)
/* ****************************************************************************
 * Dem_J1939DcmReadDiagnosticReadiness1
 *****************************************************************************/
/*!
 * \brief         Report the value of Diagnostic Readiness 1 (DM5)
 *
 * \details       Returns the value of Diagnostic Readiness 1 (DM5)
 *
 * \param[out]    DataValue
 *                Pointer to receive the DM5 data.
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                Operation was successful.
 * \return        E_NOT_OK
 *                Operation failed.
 *
 * \config        DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmReadDiagnosticReadiness1(
  P2VAR(Dem_J1939DcmDiagnosticReadiness1Type, AUTOMATIC, DEM_J1939DCM_DATA)  DataValue,
  uint8  ClientId
);
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_J1939DCMAPI_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_J1939DcmAPI_Interface.h
 *********************************************************************************************************************/
