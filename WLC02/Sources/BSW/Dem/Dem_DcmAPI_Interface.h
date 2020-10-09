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
 *  \defgroup   Dem_DcmAPI Diagnostic Communication Manager interface
 *  \{
 *  \file       Dem_DcmAPI_Interface.h
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

#if !defined (DEM_DCMAPI_INTERFACE_H)
#define DEM_DCMAPI_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DcmAPI_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DcmAPI_Public Public Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_SetDTCFilter
 *****************************************************************************/
/*!
 * \brief         Initialize the Dcm DTC filter with the given criteria.
 *
 * \details       Initializes the Dcm DTC filter with the given criteria.
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[in]     DTCStatusMask
 *                Requested status bits according to ISO14229-1
 *                0x04, 0x08 and 0x0C filter in chronologic order
 *                0x00 reports all DTCs, 0x01..0xFF apply the mask
 * \param[in]     DTCFormat
 *                The DTC format
 * \param[in]     DTCOrigin
 *                The external identifier of the event memory
 * \param[in]     FilterWithSeverity
 *                Select severity as filter criterion
 * \param[in]     DTCSeverityMask
 *                Severity filter (conditional)
 * \param[in]     FilterForFaultDetectionCounter
 *                Select fault detection counter as filter criterion
 *
 * \return        E_OK
 *                The filter parameters were accepted
 * \return        E_NOT_OK
 *                Wrong filter selected
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTCFilter(
  uint8  ClientId,
  uint8  DTCStatusMask,
  Dem_DTCFormatType  DTCFormat,                                                                                                  /* PRQA S 3206 */ /* MD_DEM_3206 */
  Dem_DTCOriginType  DTCOrigin,
  boolean  FilterWithSeverity,                                                                                                   /* PRQA S 3206 */ /* MD_DEM_3206 */
  Dem_DTCSeverityType  DTCSeverityMask,                                                                                          /* PRQA S 3206 */ /* MD_DEM_3206 */
  boolean  FilterForFaultDetectionCounter
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetNumberOfFilteredDTC
 *****************************************************************************/
/*!
 * \brief         Calculate the number of DTCs matching the filter criteria.
 *
 * \details       Calculates the number of DTCs matching the filter criteria.
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[out]    NumberOfFilteredDTC
 *                Pointer to receive the DTC count
 *
 * \return        E_OK
 *                The number of matching DTCs was returned
 * \return        E_NOT_OK
 *                Filter was not set
 * \return        DEM_PENDING
 *                Counting is currently in progress - not used
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           The Dcm filter has to be initialized by Dem_SetDTCFilter
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfFilteredDTC(
  uint8 ClientId,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredDTC
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetNextFilteredDTC
 *****************************************************************************/
/*!
 * \brief         Iterate the next matching DTC.
 *
 * \details       Iterates the next matching DTC.
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[out]    DTC
 *                Pointer to receive the UDS/OBD DTC number
 * \param[out]    DTCStatus
 *                Pointer to receive the DTC status
 *
 * \return        E_OK
 *                The next filtered element was returned
 * \return        E_NOT_OK
 *                Filter was not set
 * \return        DEM_NO_SUCH_ELEMENT
 *                No further element was found, iteration is complete
 * \return        DEM_PENDING
 *                Filtering is currently in progress - not used
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           The Dcm filter has to be initialized by Dem_SetDTCFilter
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFilteredDTC(
  uint8 ClientId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCStatus
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetNextFilteredDTCAndFDC
 *****************************************************************************/
/*!
 * \brief         Iterate the next DTC matching the filter criteria.
 *
 * \details       Iterates the next DTC matching the filter criteria. This
 *                function also retrieves the DTC's fault detection counter.
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[out]    DTC
 *                Pointer to receive the UDS/OBD DTC number
 * \param[out]    DTCFaultDetectionCounter
 *                Pointer to receive the fault detection counter
 *
 * \return        E_OK
 *                The next filtered element was returned
 * \return        E_NOT_OK
 *                Filter was not set
 * \return        DEM_NO_SUCH_ELEMENT
 *                No further element was found, iteration is complete
 * \return        DEM_PENDING
 *                Filtering is currently in progress - not used
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           The Dcm filter has to be initialized by Dem_SetDTCFilter
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFilteredDTCAndFDC(
  uint8 ClientId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  P2VAR(sint8, AUTOMATIC, DEM_DCM_DATA)  DTCFaultDetectionCounter
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetNextFilteredDTCAndSeverity
 *****************************************************************************/
/*!
 * \brief         Iterate the next DTC matching the filter criteria.
 *
 * \details       Iterates the next DTC matching the filter criteria. This
 *                function also retrieves the DTC's Status, Severity and
 *                Functional Unit.
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[out]    DTC
 *                Pointer to receive the UDS/OBD DTC number
 * \param[out]    DTCStatus
 *                Pointer to receive the DTC status
 * \param[out]    DTCSeverity
 *                Pointer to receive the DTC severity
 * \param[out]    DTCFunctionalUnit
 *                Pointer to receive the DTC functional unit
 *
 * \return        E_OK
 *                The next filtered element was returned
 * \return        E_NOT_OK
 *                Filter was not set
 * \return        DEM_NO_SUCH_ELEMENT
 *                No further element was found, iteration is complete
 * \return        DEM_PENDING
 *                Filtering is currently in progress - not used
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           The Dcm filter has to be initialized by Dem_SetDTCFilter
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFilteredDTCAndSeverity(
  uint8 ClientId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCStatus,
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_DCM_DATA)  DTCSeverity,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCFunctionalUnit
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_SetFreezeFrameRecordFilter
 *****************************************************************************/
/*!
 * \brief         Sets a freeze frame record filter with the given criteria.
 *
 * \details       Sets a freeze frame record filter with the given criteria.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[in]     DTCFormat
 *                Defines the output-format of the requested DTC values.
 * \param[out]    NumberOfFilteredRecords
 *                Pointer to receive the number of stored snapshot records
 *
 * \return        E_OK
 *                The filter is accepted
 * \return        E_NOT_OK
 *                Wrong filter selected
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetFreezeFrameRecordFilter(
  uint8                                   ClientId,
  Dem_DTCFormatType                       DTCFormat,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords
);
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetNextFilteredRecord
 *****************************************************************************/
/*!
 * \brief         Iterate the next snapshot record number matching the filter.
 *
 * \details       Iterates the next snapshot record number matching the filter,
 *                that was set by calling Dem_SetFreezeFrameRecordFilter.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    DTC
 *                Pointer to receive the DTC value in respective format of the
 *                filter returned by this function. If the return value of the
 *                function is other than E_OK this parameter does not contain
 *                valid data.
 * \param[out]    RecordNumber
 *                Pointer to receive the Freeze frame record number of the
 *                reported DTC (relative addressing). If the return value of
 *                the function is other than E_OK this parameter does not
 *                contain valid data.
 *
 * \return        E_OK
 *                Returned next filtered element.
 * \return        DEM_NO_SUCH_ELEMENT
 *                No further element (matching the filter criteria) found,
 *                iteration is complete.
 * \return        DEM_PENDING
 *                Never returned by this implementation
 * \return        E_NOT_OK
 *                Precondition violated.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           The record filter has been initialized by
 *                Dem_SetFreezeFrameRecordFilter.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFilteredRecord(
  uint8                                   ClientId,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)   RecordNumber
);
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetStatusOfDTC
 *****************************************************************************/
/*!
 * \brief         Get the current Uds status of a DTC
 *
 * \details       Returns the current Uds status of the DTC selected by Dem_SelectDTC
 *
 * \param[in]     ClientId
 *                The client to query.
 *
 * \param[out]    DTCStatus
 *                Pointer to receive the Uds status
 *
 * \return        E_OK
 *                The requested status is stored in DTCStatus
 * \return        DEM_WRONG_DTC
 *                DTC does not exist in selected origin
 *                OR a DTC group or all DTCs is selected
 *                OR DTC is suppressed
 * \return        DEM_WRONG_DTCORIGIN
 *                Selected origin does not exist
 * \return        E_NOT_OK
 *                No DTC is selected
 * \return        DEM_PENDING
 *                Never returned by this implementation
 * \return        DEM_NO_SUCH_ELEMENT
 *                The selected DTC does not support a status
 *                (in case that permanent memory was selected as origin)
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetStatusOfDTC(
  uint8  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCStatus
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetDTCStatusAvailabilityMask
 *****************************************************************************/
/*!
 * \brief         Get the supported UDS DTC status availability mask.
 *
 * \details       Returns the supported UDS DTC status availability mask.
 *
 * \param[in]     ClientId
 *                The client to query.
 *
 * \param[out]    DTCStatusMask
 *                Pointer to receive the status availability mask
 *
 * \return        E_OK
 *                The DTCStatusMask was returned
 * \return        E_NOT_OK
 *                The DTCStatusMask was not returned
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 * \trace         CREQ-112951
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCStatusAvailabilityMask(
  uint8  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCStatusMask
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetDTCByOccurrenceTime
 *****************************************************************************/
/*!
 * \brief         Get the DTC based on occurrence time.
 *
 * \details       Returns DTC based on occurrence time.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[in]     DTCRequest
 *                The requested type of the DTC:
 *                - DEM_FIRST_FAILED_DTC: first failed DTC
 *                - DEM_MOST_RECENT_FAILED_DTC: most recent failed DTC
 *                - DEM_FIRST_DET_CONFIRMED_DTC: first detected confirmed DTC
 *                - DEM_MOST_REC_DET_CONFIRMED_DTC: most recently detected
 *                  confirmed DTC 
 * \param[out]    DTC
 *                Receives the DTC value in UDS format returned by the
 *                function. If the return value of the function is other than
 *                E_OK this parameter does not contain valid data.
 *
 * \return        E_OK
 *                Get of DTC was successful, the function returns a valid DTC.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested DTC is not stored.
 * \return        E_NOT_OK
 *                The call was not successful (e.g. not supported by
 *                configuration).
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCByOccurrenceTime(
uint8                                   ClientId,
Dem_DTCRequestType                      DTCRequest,
P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC
);
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetTranslationType
 *****************************************************************************/
/*!
 * \brief         Get the UDS DTC format.
 *
 * \details       Returns the UDS DTC format.
 *
 * \param[in]     ClientId
 *                The client to query.
 *
 * \return        The configured DTC format.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 * \trace         CREQ-112935
 *****************************************************************************/
FUNC(Dem_DTCTranslationFormatType, DEM_CODE)
Dem_GetTranslationType(
  uint8  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetSeverityOfDTC
 *****************************************************************************/
/*!
 * \brief         Get the severity of a DTC
 *
 * \details       Returns the severity of the DTC selected by Dem_SelectDTC
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[out]    DTCSeverity
 *                Pointer to receive the DTC severity
 *
 * \return        E_OK
 *                The requested severity is stored in DTCSeverity
 * \return        DEM_WRONG_DTC
 *                A DTC group or all DTCs is selected
 *                OR DTC is suppressed
 * \return        DEM_WRONG_DTCORIGIN
 *                Selected origin does not exist
 * \return        E_NOT_OK
 *                No DTC is selected
 * \return        DEM_PENDING
 *                Never returned by this implementation
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSeverityOfDTC(
  uint8  ClientId,
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_DCM_DATA)  DTCSeverity
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetDTCSeverityAvailabilityMask
 *****************************************************************************/
/*!
 * \brief         Gets the DTC Severity availability mask
 *
 * \details       Returns the severity availability mask
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[out]    DTCSeverityMask
 *                The supported severity mask.
 *
 * \return        E_OK
 *                DTCSeverityMask value is valid
 * \return        E_NOT_OK
 *                API call is invalid
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 * \trace         CREQ-112952
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCSeverityAvailabilityMask(
  uint8  ClientId,
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_DCM_DATA)  DTCSeverityMask
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetFunctionalUnitOfDTC
 *****************************************************************************/
/*!
 * \brief         Get the functional unit of a DTC.
 *
 * \details       Returns the functional unit of the DTC selected by Dem_SelectDTC
 *
 * \param[in]     ClientId
 *                The client to query
 *
 * \param[out]    DTCFunctionalUnit
 *                Pointer to receive the DTC functional unit
 *
 * \return        E_OK
 *                The requested functional unit is stored in DTCFunctionalUnit
 * \return        DEM_WRONG_DTC
 *                A DTC group or all DTCs is selected
 *                OR DTC is suppressed
 * \return        DEM_WRONG_DTCORIGIN
 *                Selected origin does not exist
 * \return        E_NOT_OK
 *                No DTC is selected
 * \return        DEM_PENDING
 *                Never returned by this implementation
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetFunctionalUnitOfDTC(
  uint8  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DTCFunctionalUnit
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DisableDTCRecordUpdate
 *****************************************************************************/
/*!
 * \brief         Prepare a memory entry for readout by the Dcm.
 *
 * \details       Disables the event memory update of a specific DTC (only one
 *                at one time).
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                Event memory update was successfully disabled
 * \return        DEM_WRONG_DTC
 *                Selected DTC value in selected format does not exist.
 * \return        DEM_WRONG_DTCORIGIN
 *                Selected DTCOrigin does not exist.
 * \return        DEM_PENDING
 *                Disabling the DTC record update is currently in progress.
 *                The caller shall call this function again at a later moment.
 * \return        E_NOT_OK
 *                Required conditions for the respective API call are not
 *                fulfilled.
 *                The request is rejected due to invalid argument or state if
 *                Development Error Checks are active.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Requires a preceding DTC selection by Dem_SelectDTC
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DisableDTCRecordUpdate(
  uint8  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_EnableDTCRecordUpdate
 *****************************************************************************/
/*!
 * \brief         Release a previously prepared memory entry.
 *
 * \details       Enables the event memory update of the DTC disabled by
 *                Dem_DisableDTCRecordUpdate() before.
 *                A call to Dem_SelectDTC is NOT required.
 *                A call to Dem_DisableDTCRecordUpdate is NOT required.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                Event memory update was successfully enabled
 * \return        E_NOT_OK
 *                The request is rejected due to invalid arguments or state if
 *                Development Error Checks are active.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Requires all asynchronous actions following the previous call
 *                of Dem_DisableDTCRecordUpdate() must internally have been
 *                completed.
 *                The arguments of a Dem_SelectDTC call preceding the
 *                Dem_EnableDTCRecordUpdate need not match the arguments of the
 *                Dem_SelectDTC call preceding Dem_DisableDTCRecordUpdate.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_EnableDTCRecordUpdate(
  uint8  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_SelectFreezeFrameData
 *****************************************************************************/
/*!
 * \brief         Sets the filter to be used by Dem_GetNextFreezeFrameData and
 *                Dem_GetSizeOfFreezeFrameSelection.
 *
 * \details       Sets the filter to be used by Dem_GetNextFreezeFrameData and
 *                Dem_GetSizeOfFreezeFrameSelection.
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[in]     RecordNumber
 *                This parameter is a unique identifier for a freeze-frame
 *                record as defined in ISO 15031-5 and ISO 14229-1. This
 *                record number is unique per DTC (relative addressing).
 *                The value 0xFF indicates all snapshot records. 
 *                The value 0x00 indicates the DTC-specific OBD freeze frame.
 *
 * \return        E_OK
 *                Selection was successfully processed.
 * \return        E_NOT_OK
 *                The request is rejected due to invalid arguments or state if
 *                Development Error Checks are active.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Previous selection by Dem_SelectDTC is required. 
 *                Record updates have to be disabled for the selected DTC by 
 *                Dem_DisableDTCRecordUpdate.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different clients
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SelectFreezeFrameData(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint8, AUTOMATIC)  RecordNumber
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetNextFreezeFrameData
 *****************************************************************************/
/*!
 * \brief         Reads the snapshot data
 *
 * \details       Gets the snapshot data data for the DTC and record selected by
 *                Dem_SelectDTC and Dem_SelectFreezeFrameData. 
 *                The function stores the data in the provided DestBuffer.
 *                
 * \param[in]     ClientId
 *                The client to query
 * \param[out]    DestBuffer
 *                Pointer to receive the snapshot data
 * \param[in,out] BufSize
 *                In: Size of Buffer. Must be large enough to hold the data.
 *                Out: Number of written bytes.
 *
 * \return        E_OK
 *                Size and buffer successfully returned.
 * \return        DEM_BUFFER_TOO_SMALL
 *                provided buffer size too small
 * \return        DEM_PENDING
 *                Disabling DTC record update is not completed,no valid readout 
 *                buffer provided.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available.
 * \return        E_NOT_OK
 *                Selection function is not called.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Previous selection by Dem_SelectDTC and Dem_SelectFreezeFrameData
 *                required.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFreezeFrameData(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetSizeOfFreezeFrameSelection
 *****************************************************************************/
/*!
 * \brief         Get the size of a formatted snapshot record stored for a DTC
 *                (19 04).
 *
 * \details       Gets the size of a formatted snapshot record stored for a DTC
 *                (19 04).
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[out]    SizeOfFreezeFrame
 *                Pointer to receive the size in bytes
 *
 * \return        E_OK
 *                The requested data was returned
 * \return        E_NOT_OK
 *                Selection function is not called.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available
 * \return        DEM_PENDING
 *                Disabling DTC record update is not completed,no valid readout 
 *                buffer provided.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Previous selection by Dem_SelectDTC and Dem_SelectFreezeFrameData
 *                required.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfFreezeFrameSelection(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfFreezeFrame
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_SelectExtendedDataRecord
 *****************************************************************************/
/*!
 * \brief         Sets the filter to be used by Dem_GetNextExtendedDataRecord and
 *                Dem_GetSizeOfExtendedDataRecordSelection.
 *
 * \details       Sets the filter to be used by Dem_GetNextExtendedDataRecord and
 *                Dem_GetSizeOfExtendedDataRecordSelection.
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[in]     ExtendedDataNumber
 *                Identification/Number of requested extended data record.
 *                Additionally the values 0xFE and 0xFF are explicitly allowed
 *                to request the overall size of all OBD records / all records.
 *
 * \return        E_OK
 *                If selection is accepted
 *                E_NOT_OK
 *                If selection is not accepted
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Previous selection by Dem_SelectDTC is required.
 *                Record updates have to be disabled for the selected DTC by
 *                Dem_DisableDTCRecordUpdate.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_SelectExtendedDataRecord(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint8, AUTOMATIC)  ExtendedDataNumber
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetNextExtendedDataRecord
 *****************************************************************************/
/*!
 * \brief         Read an extended data record stored for a DTC.
 *
 * \details       Reads an extended data record stored for a DTC. If the record
 *                is currently not stored, the function returns BufSize 0.
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[out]    DestBuffer
 *                Pointer to receive the extended record data
 * \param[in,out] BufSize
 *                In: Size of Buffer. Must be large enough to hold the data
 *                Out: Number of written bytes
 *
 * \return        E_OK
 *                Size and buffer successfully returned.
 * \return        E_NOT_OK
 *                Selection function is not called.
 * \return        DEM_BUFFER_TOO_SMALL
 *                Provided buffer size too small.
 * \return        DEM_PENDING
 *                Disabling DTC record update is not completed,no valid readout 
 *                buffer provided.
 * \return        DEM_NO_SUCH_ELEMENT
 *                The requested record is not available.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Previous selection by Dem_SelectDTC and Dem_SelectExtendedDataRecord
 *                required.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextExtendedDataRecord(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_GetSizeOfExtendedDataRecordSelection
 *****************************************************************************/
/*!
 * \brief         Gets the size of a formatted extended data record stored for
 *                a DTC.
 *
 * \details       This function returns the size of the formatted extended data
 *                record, including the record number.
 *
 * \param[in]     ClientId
 *                The client to query
 * \param[out]    SizeOfExtendedDataRecord
 *                Pointer to receive the size in bytes
 *
 * \return        E_OK
 *                The requested data was returned
 * \return        E_NOT_OK
 *                Selection function is not called.
 * \return        DEM_PENDING
 *                Disabling DTC record update is not completed,no valid readout 
 *                buffer provided.
 * \return        DEM_NO_SUCH_ELEMENT
 *                Record number is not supported by configuration and 
 *                therefore invalid
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Previous selection by Dem_SelectDTC and Dem_SelectExtendedDataRecord
 *                required.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds.
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfExtendedDataRecordSelection(
  CONST(uint8, AUTOMATIC)  ClientId,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  SizeOfExtendedDataRecord
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DisableDTCSetting
 *****************************************************************************/
/*!
 * \brief         Disable DTC setting (UDS 0x85)
 *
 * \details       Completely disables the the storage of all events and
 *                UDS status byte updates. (UDS 0x85).
 *
 * \param[in]     ClientId
 *                The client to query
 *
 * \return        E_OK
 *                DTC setting for all DTCs was disabled.
 * \return        DEM_PENDING
 *                Operation is currently in progress. The caller shall call this
 *                function again at a later moment.
 *                Not used by this implementation.
 * \return        E_NOT_OK
 *                The request is rejected due to invalid argument or state if 
 *                Development Error Checks are active.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DisableDTCSetting(
  uint8  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_EnableDTCSetting
 *****************************************************************************/
/*!
 * \brief         Enable the DTC setting (UDS 0x85)
 *
 * \details       Re-enables the storage of all events and UDS status byte
 *                (UDS 0x85) after Dem_DisableDTCSetting was called.
 *
 * \param[in]     ClientId
 *                The client to query
 *
 * \return        E_OK
 *                DTC setting for all DTCs was enabled.
 * \return        DEM_PENDING
 *                Operation is currently in progress. The caller shall call this
 *                function again at a later moment.
 *                Not used by this implementation.
 * \return        E_NOT_OK
 *                The request is rejected due to invalid argument or state if 
 *                Development Error Checks are active.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_EnableDTCSetting(
    uint8  ClientId
  );
#endif

                                                    /* Dcm <-> Dem : OBD DTR */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_DTR == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DcmGetDTRData
 *****************************************************************************/
/*!
 * \brief         Gets the DTR data for a OBDMID / TID combination
 *
 * \details       Gets the DTR data for a OBDMID / TID combination
 *
 * \param[in]     Obdmid
 *                OBDMID
 * \param[in]     TIDindex
 *                TID index
 * \param[out]    TIDvalue
 *                TID value
 * \param[out]    UaSID
 *                Unit and Scaling ID
 * \param[out]    Testvalue
 *                Test Value
 * \param[out]    Lowlimvalue
 *                Lower Limit
 * \param[out]    Upplimvalue
 *                Upper Limit
 *
 * \return        E_OK
 *                The data was successfully copied
 * \return        E_NOT_OK
 *                The requested data was not copied
 *
 * \config           DEM_CFG_SUPPORT_DTR == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetDTRData(
  uint8 Obdmid,
  uint8 TIDindex,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) TIDvalue,                                                                                /* PRQA S 3673 */ /* MD_DEM_16.7 */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) UaSID,                                                                                   /* PRQA S 3673 */ /* MD_DEM_16.7 */
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) Testvalue,                                                                              /* PRQA S 3673 */ /* MD_DEM_16.7 */
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) Lowlimvalue,                                                                            /* PRQA S 3673 */ /* MD_DEM_16.7 */
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA) Upplimvalue                                                                             /* PRQA S 3673 */ /* MD_DEM_16.7 */
  );
#endif

                                                   /* Dcm <-> Dem : OBD MIDs */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_DTR == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DcmGetAvailableOBDMIDs
 *****************************************************************************/
/*!
 * \brief         Gets the supported Mid Mask for an availability OBDMID
 *
 * \details       Gets the supported Mid Mask for an availability OBDMID
 *
 * \param[in]     Obdmid
 *                Availability OBDMID
 * \param[out]    Obdmidvalue
 *                Supported Mid Mask
 *
 * \return        E_OK
 *                The data was successfully copied
 * \return        E_NOT_OK
 *                The requested data was not copied
 *
 * \config           DEM_CFG_SUPPORT_DTR == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetAvailableOBDMIDs(
  uint8 Obdmid,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  Obdmidvalue                                                                            /* PRQA S 3673 */ /* MD_DEM_16.7 */
  );
#endif

#if (DEM_CFG_SUPPORT_DTR == STD_ON) && (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DcmGetNumTIDsOfOBDMID
 *****************************************************************************/
/*!
 * \brief         Gets the number of TIDs for a MID
 *
 * \details         Gets the number of TIDs for a MID
 *
 * \param[in]     Obdmid
 *                OBDMID
 * \param[out]    numberOfTIDs
 *                Number of TIDs for OBDMID
 *
 * \return        E_OK
 *                DTR data was successfully copied
 * \return        E_NOT_OK
 *                DTR data was not copied
 *
 * \config           DEM_CFG_SUPPORT_DTR == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetNumTIDsOfOBDMID(
  uint8 Obdmid,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA) numberOfTIDs
  );
#endif


                                                                 /* DTC Data */
/* ------------------------------------------------------------------------- */
#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_DcmGetOBDFreezeFrameData
 *****************************************************************************/
/*!
 * \brief         Read the OBD freeze frame via UDS protocol (19 05).
 *
 * \details       Reads the OBD freeze frame via UDS protocol (19 05).
 *
 * \param[out]    DTC
 *                Pointer to receive the DTC number
 * \param[out]    DestBuffer
 *                Pointer to receive the snapshot data
 * \param[in,out] BufSize
 *                In: Size of Buffer. Must be large enough to hold the data.
 *                Out: Number of written bytes.
 *
 * \return        E_OK
 *                DTC and OBD freeze frame have been returned
 * \return        E_NOT_OK
 *                No DTC and OBD freeze frame data available
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetOBDFreezeFrameData(
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  BufSize
  );
#endif

                                                         /* OBD Freeze Frame */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_DcmReadDataOfOBDFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Get the requested PID data (Mode02)
 *
 * \details       Returns the requested PID data.
 *
 * \param[in]     PID
 *                The PID number
 * \param[in]     DataElementIndexOfPID
 *                The index of the data element
 * \param[out]    DestBuffer
 *                Pointer to the output buffer
 * \param[in,out] BufSize
 *                In: Size of Buffer. Must be large enough to hold the data.
 *                Out: Number of written bytes.
 *
 * \return        E_OK
 *                The data was successfully copied
 * \return        E_NOT_OK
 *                The requested data was not copied
 *
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfOBDFreezeFrame(
  uint8  PID,
  uint8  DataElementIndexOfPID,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  DestBuffer,
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  BufSize
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 * Dem_DcmGetDTCOfOBDFreezeFrame
 *****************************************************************************/
/*!
 * \brief         Returns the DTC holding the OBD Freeze Frame
 *
 * \details       Returns the DTC holding the OBD Freeze Frame (Mode02)
 *
 * \param[in]     FrameNumber
 *                The FreezeFrame number for which the DTC shall be returned.
 *                Only 0x00 is allowed.
 * \param[out]    DTC
 *                Pointer to receive the DTC number
 *
 * \return        E_OK
 *                DTC is returned successfully
 * \return        E_NOT_OK
 *                Operation failed. DTC can not be returned.
 *
 * \config        DEM_CFG_SUPPORT_OBDII == STD_ON && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetDTCOfOBDFreezeFrame(
  uint8  FrameNumber,
  P2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC
  );
#endif

                                                                 /* OBD PIDs */
/* ------------------------------------------------------------------------- */

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID01 == STD_ON)
/* ****************************************************************************
 * Dem_DcmReadDataOfPID01
 *****************************************************************************/
/*!
 * \brief         Provides the monitoring status since DTCs cleared
 *
 * \details       supported - 0 == FALSE; 1 == TRUE
 *                ready     - 0 == TRUE/NA; 1 == FALSE
 *                Byte 0
 *                  bit 0...6 - # of DTCs stored in this ECU
 *                  bit 7 - Malfunction Indicator Lamp (MIL) Status
 *                Byte 1
 *                  bit 0 - Misfire monitoring supported
 *                  bit 1 - Fuel system monitoring supported
 *                  bit 2 - Comprehensive component monitoring supported
 *                  bit 3 - Compression ignition monitoring supported
 *                  bit 4 - Misfire monitoring ready
 *                  bit 5 - Fuel system monitoring ready
 *                  bit 6 - Comprehensive component monitoring ready
 *                  bit 7 - reserved
 *                Byte 2
 *                  bit 0 - Catalyst monitoring supported
 *                  bit 1 - Heated catalyst monitoring supported
 *                  bit 2 - Evaporative system monitoring supported
 *                  bit 3 - Secondary air system monitoring supported
 *                  bit 4 - reserved
 *                  bit 5 - Oxygen sensor monitoring supported
 *                  bit 6 - Oxygen sensor heater monitoring
 *                  bit 7 - EGR system monitoring supported
 *                Byte3
 *                  bit 0 - Catalyst monitoring ready
 *                  bit 1 - Heated catalyst monitoring ready
 *                  bit 2 - Evaporative system monitoring ready
 *                  bit 3 - Secondary air system monitoring ready
 *                  bit 4 - reserved
 *                  bit 5 - Oxygen sensor monitoring ready
 *                  bit 6 - Oxygen sensor heater monitoring ready
 *                  bit 7 - EGR system monitoring ready
 *
 * \param[out]    PID01value
 *                Buffer with size of four bytes to receive the PID data
 *
 * \return        E_OK
 *                PID01 is provided successfully
 * \return        E_NOT_OK
 *                Operation failed. PID01 can not be provided.
 *
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *                && DEM_CFG_SUPPORT_PID01 == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID01(                                                                                                          /* PRQA S 3451 */ /* MD_DEM_8.8_dcm */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID01value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID1C == STD_ON)
/* ****************************************************************************
 * Dem_DcmReadDataOfPID1C
 *****************************************************************************/
/*!
 * \brief         Returns the configured OBD requirements id
 *
 * \details       Returns the configured OBD requirements id
 *
 * \param[out]    PID1Cvalue
 *                Pointer to receive the PID data
 *
 * \return        E_OK
 *                PID1C is provided successfully
 * \return        E_NOT_OK
 *                Operation failed. PID1C can not be provided.
 *
 *
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *                && DEM_CFG_SUPPORT_PID1C == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID1C(                                                                                                          /* PRQA S 3451 */ /* MD_DEM_8.8_dcm */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID1Cvalue                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID21 == STD_ON)
/* ****************************************************************************
 * Dem_DcmReadDataOfPID21
 *****************************************************************************/
/*!
 * \brief         Returns the distance travelled with MIL on
 *
 * \details       The value is latched at 0xFFFF
 *
 * \param[out]    PID21value
 *                Buffer with size of two bytes to receive the PID data
 *
 * \return        E_OK
 *                PID21 is provided successfully
 * \return        E_NOT_OK
 *                Operation failed. PID21 can not be provided.
 *
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *                && DEM_CFG_SUPPORT_PID21 == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID21(                                                                                                          /* PRQA S 3451 */ /* MD_DEM_8.8_dcm */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID21value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID30 == STD_ON)
/* ****************************************************************************
 * Dem_DcmReadDataOfPID30
 *****************************************************************************/
/*!
 * \brief         Returns the number of Warm-Up cycles since last clear.
 *
 * \details       The value is latched at 0xFF
 *
 * \param[out]    PID30value
 *                Pointer to receive the PID data
 *
 * \return        E_OK
 *                PID30 is provided successfully
 * \return        E_NOT_OK
 *                Operation failed. PID30 can not be provided.
 *
 * \config        DEM_FEATURE_NEED_OBD ==STD_ON
 *                && DEM_CFG_SUPPORT_PID30 == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID30(                                                                                                          /* PRQA S 3451 */ /* MD_DEM_8.8_dcm */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID30value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID31 == STD_ON)
/* ****************************************************************************
 * Dem_DcmReadDataOfPID31
 *****************************************************************************/
/*!
 * \brief         Returns the driven distance since last fault memory clear.
 *
 * \details       The value is latched at 0xFFFF
 *
 * \param[out]    PID31value
 *                Buffer with size of two bytes to receive the PID data
 *
 * \return        E_OK
 *                PID31 is provided successfully
 * \return        E_NOT_OK
 *                Operation failed. PID31 can not be provided.
 *
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *                && DEM_CFG_SUPPORT_PID31 == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID31(                                                                                                          /* PRQA S 3451 */ /* MD_DEM_8.8_dcm */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID31value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID41 == STD_ON)
/* ****************************************************************************
 * Dem_DcmReadDataOfPID41
 *****************************************************************************/
/*!
 * \brief         Returns the monitoring status for this driving cycle
 *
 * \details       enabled   - 0 == FALSE; 1 == TRUE
 *                ready     - 0 == TRUE; 1 == FALSE
 *                Byte 0
 *                  bit 0...7 - reserved
 *                Byte 1
 *                  bit 0 - Misfire monitoring enabled
 *                  bit 1 - Fuel system monitoring enabled
 *                  bit 2 - Comprehensive component monitoring enabled
 *                  bit 3 - reserved
 *                  bit 4 - Misfire monitoring completed
 *                  bit 5 - Fuel system monitoring completed
 *                  bit 6 - Comprehensive component monitoring complete
 *                  bit 7 - reserved
 *                Byte 2
 *                  bit 0 - Catalyst monitoring
 *                  bit 1 - Heated catalyst monitoring
 *                  bit 2 - Evaporative system monitoring
 *                  bit 3 - Secondary air system monitoring
 *                  bit 4 - A/C system refrigerant monitoring
 *                  bit 5 - Oxygen sensor monitoring
 *                  bit 6 - Oxygen sensor heater monitoring
 *                  bit 7 - EGR system monitoring
 *                Byte3
 *                  bit 0 - Catalyst monitoring completed
 *                  bit 1 - Heated catalyst monitoring completed
 *                  bit 2 - Evaporative system monitoring completed
 *                  bit 3 - Secondary air system monitoring completed
 *                  bit 4 - A/C system refrigerant monitoring completed
 *                  bit 5 - Oxygen sensor monitoring completed
 *                  bit 6 - Oxygen sensor heater monitoring completed
 *                  bit 7 - EGR system monitoring completed
 *
 * \param[out]    PID41value
 *                Buffer with size of four bytes to receive the PID data
 *
 * \return        E_OK
 *                PID41 is provided successfully
 * \return        E_NOT_OK
 *                Operation failed. PID41 can not be provided.
 *
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *                && DEM_CFG_SUPPORT_PID41 == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID41(                                                                                                          /* PRQA S 3451 */ /* MD_DEM_8.8_dcm */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID41value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID4D == STD_ON)
/* ****************************************************************************
 * Dem_DcmReadDataOfPID4D
 *****************************************************************************/
/*!
 * \brief         Returns the engine run time while MIL is active.
 *
 * \details       The value is latched at 0xFFFF
 *
 * \param[out]    PID4Dvalue
 *                Buffer with size of two bytes to receive the PID data
 *
 * \return        E_OK
 *                PID4D is provided successfully
 * \return        E_NOT_OK
 *                Operation failed. PID4D can not be provided.
 *
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *                && DEM_CFG_SUPPORT_PID4D == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID4D(                                                                                                          /* PRQA S 3451 */ /* MD_DEM_8.8_dcm */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID4Dvalue                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_FEATURE_NEED_OBD == STD_ON) && (DEM_CFG_SUPPORT_PID4E == STD_ON)
/* ****************************************************************************
 * Dem_DcmReadDataOfPID4E
 *****************************************************************************/
/*!
 * \brief         Returns the engine run time since DTCs cleared.
 *
 * \details       The returned value is latched at 0xFFFF
 *
 * \param[out]    PID4Evalue
 *                Buffer with size of two bytes to receive the PID data
 *
 * \return        E_OK
 *                PID4E is provided successfully
 * \return        E_NOT_OK
 *                Operation failed. PID4E can not be provided.
 *
 * \config        DEM_FEATURE_NEED_OBD == STD_ON
 *                && DEM_CFG_SUPPORT_PID4E == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID4E(                                                                                                          /* PRQA S 3451 */ /* MD_DEM_8.8_dcm */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID4Evalue                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PID91 == STD_ON)
/* ****************************************************************************
 * Dem_DcmReadDataOfPID91
 *****************************************************************************/
/*!
 * \brief         Returns the WWH-OBD ECU OBD System Information.
 *
 * \details       Byte 0
 *                  bit 0...3 - Activation Mode
 *                  bit 4...7 - reserved
 *                Byte 1,2
 *                  Continuous MI counter 1h/bit
 *                Byte 3,4
 *                  Highest ECU B1 counter 1h/bit
 *
 * \param[out]    PID91value
 *                Buffer with size of five bytes to receive the PID data
 *
 * \return        E_OK
 *                PID91 is provided successfully
 * \return        E_NOT_OK
 *                Operation failed. PID91 can not be provided.
 *
 * \config           DEM_CFG_SUPPORT_WWHOBD == STD_ON
 *                && DEM_CFG_SUPPORT_PID91 == STD_ON
 *                && DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmReadDataOfPID91(                                                                                                          /* PRQA S 3451 */ /* MD_DEM_8.8_dcm */
  P2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  PID91value                                                                              /* PRQA S 1330 */ /* MD_DEM_16.4_dcm */
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DCMAPI_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DcmAPI_Interface.h
 *********************************************************************************************************************/
