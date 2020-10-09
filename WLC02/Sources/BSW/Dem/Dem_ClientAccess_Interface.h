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
 *  \defgroup   Dem_ClientAccess ClientAccess
 *  \{
 *  \file       Dem_ClientAccess_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
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
 *  Alexander Ditte               visade        V33ector Informatik GmbH
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

#if !defined (DEM_CLIENTACCESS_INTERFACE_H)
#define DEM_CLIENTACCESS_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ClientAccess_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \defgroup Dem_ClientAccess_Public Public Methods
 * \{
 */


/* ****************************************************************************
 * Dem_ClientAccess_MemoryIdFromOrigin
 *****************************************************************************/
/*!
 * \brief         Map a DTC origin to a memory ID
 *
 * \details       Map a DTC origin to a memory ID
 *
 * \param[in]     DTCOrigin
 *                The external identifier of the event memory
 *
 * \return        The resulting memory id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_ClientAccess_MemoryIdFromOrigin(
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  );

/* ****************************************************************************
 * Dem_ClientAccess_GlobalClientCount
 *****************************************************************************/
/*!
 * \brief         Get the number of configured clients
 *
 * \details       Get the number of configured clients
 *
 * \return        The number of configured clients
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE) 
Dem_ClientAccess_GlobalClientCount(
  void
  );
 
/* ****************************************************************************
 * Dem_ClientAccess_TestSelectorValid
 *****************************************************************************/
/*!
 * \brief         Test if the client has a valid selector.
 *
 * \details       Test if the client has a valid selector.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                Client has a valid selector
 * \return        FALSE
 *                Client doesn't have a valid selector
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestSelectorValid(
  CONST(uint8, AUTOMATIC)  ClientId
  );

/* ****************************************************************************
 * Dem_ClientAccess_SelectDTC
 *****************************************************************************/
/*!
 * \brief         Selects a DTC or DTC group as target for further operations.
 *
 * \details       For the given ClientId store the DTC, DTCFormat and
 *                DTCOriging for later use by the following API calls:
 *                - Dem_GetStatusOfDTC
 *                - Dem_GetSeverityOfDTC
 *                - Dem_GetFunctionalUnitOfDTC
 *                - Dem_ClearDTC
 *                - Dem_DisableDTCRecordUpdate
 *                - Dem_EnableDTCRecordUpdate
 *                - Dem_GetDTCSelectionResult.
 *                The stored values may be invalid for the current
 *                configuration - they need a check before use!
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[in]     DTC
 *                Defines the DTC in respective format that is selected. If the
 *                DTC fits to a DTC group number, the DTC group is selected.
 * \param[in]     DTCFormat
 *                Defines the input-format of the provided DTC value.
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_ClientAccess_SelectDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  );

/* ****************************************************************************
 * Dem_ClientAccess_GetSelectionResult
 *****************************************************************************/
/*!
 * \brief         Returns the result of operation DTC selection.
 *
 * \details       For the given ClientId return the result of the asynchronous operation
 *                on API Dem_SelectDTC.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        DTC selection result.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_ResultType, DEM_CODE) 
Dem_ClientAccess_GetSelectionResult(
  CONST(uint8, AUTOMATIC)  ClientId
  );

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 % Dem_ClientAccess_GetSelectedMemoryId
 *****************************************************************************/
/*!
 * \brief         Returns the selected Memory Id
 *
 * \details       For the given ClientId return the memory Id selected by
 *                Dem_SelectDTC.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        Selected Memory Id
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE) 
Dem_ClientAccess_GetSelectedMemoryId(
  CONST(uint8, AUTOMATIC) ClientId
  );
#endif

/* ****************************************************************************
 % Dem_ClientAccess_GetSelectedEventId
 *****************************************************************************/
/*!
 * \brief         Returns the selected Event Id
 *
 * \details       For the given ClientId return the Event Id selected by
 *                Dem_SelectDTC.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        Selected Event Id
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE) 
Dem_ClientAccess_GetSelectedEventId(
  CONST(uint8, AUTOMATIC) ClientId
  );

/* ****************************************************************************
 % Dem_ClientAccess_TestSelectDTCLocked
 *****************************************************************************/
/*!
 * \brief         Tests if access to API Dem_SelectDTC is allowed
 *
 * \details       Verifies if for the given ClientId Dem_SelectDTC is granted
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                API access is locked
 *
 * \return        FALSE
 *                API access is granted
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) 
Dem_ClientAccess_TestSelectDTCLocked(
  CONST(uint8, AUTOMATIC) ClientId
  );

#if (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_TestFilterValid
 *****************************************************************************/
/*!
 * \brief         Test if the client has a valid filter.
 *
 * \details       Test if the client has a valid filter.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                Client has a valid filter
 * \return        FALSE
 *                Client doesn't have a valid filter
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON ||
 *                DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestFilterValid(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif


#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_SetDTCFilter
 *****************************************************************************/
/*!
 * \brief         Initializes a DTC filter with the given criteria.
 *
 * \details       For the given ClientId set up a DTC filter with the given criteria.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[in]     DTCStatusMask
 *                The status byte mask for DTC status byte filtering.
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     FilterWithSeverity
 *                Defines if severity information is used for filtering.
 * \param[in]     DTCSeverityMask
 *                The severity mask for severity filtering (only evaluated
 *                if severity information is used for filtering)
 * \param[in]     FilterForFDC
 *                Defines if FDC information is used for filtering.
 *
 * \return        E_OK
 *                Filter was accepted
 *                E_NOT_OK
 *                Filter was not accepted or no filter available for client
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_ClientAccess_SetDTCFilter(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint8, AUTOMATIC)  DTCStatusMask,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(boolean, AUTOMATIC)  FilterWithSeverity,
  CONST(Dem_DTCSeverityType, AUTOMATIC)  DTCSeverityMask,
  CONST(boolean, AUTOMATIC)  FilterForFDC
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_GetNextFilteredDTC
 *****************************************************************************/
/*!
 * \brief         Get the next matching event
 *
 * \details       Get the next event matching the filter criteria set with 
 *                Dem_ClientAccess_SetDTCFilter
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    FilterResult
 *                Pointer to receive the next matching event
 *                FilterResult->EventId : The matching event
 *                FilterResult->FDC : The matching FDC, updated only when
 *                                    FilterForFDC is TRUE
 *                FilterResult->Severity : The matching severity, updated only
 *                                    when FilterWithSeverity is true
 *
 * \return        E_OK
 *                Matching element returned in FilterResult
 * \return        E_NOT_OK
 *                Filter was not set or no filter available for client
 * \return        E_DEM_NO_SUCH_ELEMENT
 *                No more matching elements, FilterResult not modified
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_ClientAccess_GetNextFilteredDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
 /* ****************************************************************************
 * Dem_ClientAccess_TestDTCFilterSet
 *****************************************************************************/
/*!
 * \brief         Test if a DTC filter has been set.
 *
 * \details       Test if a DTC filter has been set for the given ClientId.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                A DTC filter has been set
 * \return        FALSE
 *                No DTC filter has been set
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) 
Dem_ClientAccess_TestDTCFilterSet(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_TestDTCFilterWithFDCSet
 *****************************************************************************/
/*!
 * \brief         Test if a DTC filter with FDC filtering has been set.
 *
 * \details       Test if a DTC filter with FDC filtering has been set for 
 *                the given ClientId.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                A DTC filter with FDC filtering has been set
 * \return        FALSE
 *                No DTC filter with FDC filtering has been set
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) 
Dem_ClientAccess_TestDTCFilterWithFDCSet(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
* Dem_ClientAccess_TestDTCFilterWithSeveritySet
*****************************************************************************/
/*!
* \brief         Test if a DTC filter with severity filtering has been set.
*
* \details       Test if a DTC filter with severity filtering has been set
*                for the given ClientId.
*
* \param[in]     ClientId
*                Unique client id, assigned to the instance of the calling
*                module.
*
* \return        TRUE
*                A DTC filter with severity filtering has been set
* \return        FALSE
*                No DTC filter with severity filtering has been set
*
* \config        DEM_CFG_SUPPORT_DCM == STD_ON
* \pre           -
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE for different ClientIds
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) 
Dem_ClientAccess_TestDTCFilterWithSeveritySet(
  CONST(uint8, AUTOMATIC)  ClientId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
 /* ****************************************************************************
 * Dem_ClientAccess_TestJ1939DTCFilterSet
 *****************************************************************************/
/*!
 * \brief         Test if a J1939 DTC filter has been set.
 *
 * \details       Test if a J1939 DTC filter has been set for the given ClientId.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                A J1939 DTC filter has been set
 * \return        FALSE
 *                No J1939 DTC filter has been set
 *
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestJ1939DTCFilterSet(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
 /* ****************************************************************************
 * Dem_ClientAccess_TestJ1939DTCFilterWithLampStatusSet
 *****************************************************************************/
/*!
 * \brief         Test if a 'J1939 DTC with lamp status' filter has been set.
 *
 * \details       Test if a 'J1939 DTC with lamp status' filter has been set 
 *                for the given ClientId.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                A 'J1939 DTC with lamp status' filter has been set
 * \return        FALSE
 *                No 'J1939 DTC with lamp status' filter has been set
 *
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestJ1939DTCFilterWithLampStatusSet(
  CONST(uint8, AUTOMATIC)  ClientId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
 /* ****************************************************************************
 * Dem_ClientAccess_TestJ1939FreezeFrameFilterSet
 *****************************************************************************/
/*!
 * \brief         Test if a J1939 freeze frame filter has been set.
 *
 * \details       Test if a J1939 freeze frame filter has been set for the 
 *                given ClientId.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                A J1939 freeze frame filter has been set
 * \return        FALSE
 *                No J1939 freeze frame filter has been set
 *
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestJ1939FreezeFrameFilterSet(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

/* ****************************************************************************
 * Dem_ClientAccess_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the buffers for all clients.
 *
 * \details       Initialize the DTC selector and filter for all clients.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_ClientAccess_Init(
  void
  );

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_TestReadoutBufferValid
 *****************************************************************************/
/*!
 * \brief         Test if the client has a valid readout buffer.
 *
 * \details       Test if the client has a valid readout buffer.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                Client has a valid readout buffer
 * \return        FALSE
 *                Client doesn't have a valid readout buffer
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestReadoutBufferValid(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_GetReadoutBuffer
 *****************************************************************************/
/*!
 * \brief         Return the readout buffer handle for the client
 *
 * \details       Return the readout buffer handle for the client
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        The readout buffer handle for the client
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCReadoutBuffer_HandleType, DEM_CODE)
Dem_ClientAccess_GetReadoutBuffer(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_TestDTCRecordUpdateRequested
 *****************************************************************************/
/*!
 * \brief         Test if the DTC record update was requested
 *
 * \details       Test if the DTC record update was requested for the
 *                given ClientId.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                The DTC record update was requested
 * \return        FALSE
 *                The DTC record update  was requested
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestDTCRecordUpdateRequested(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_TestDTCRecordUpdateDisabled
 *****************************************************************************/
/*!
 * \brief         Test if the DTC record update is disabled
 *
 * \details       Test if the DTC record update is disabled for the
 *                given ClientId.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                The DTC record update is disabled
 * \return        FALSE
 *                The DTC record update is enabled
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestDTCRecordUpdateDisabled(
  CONST(uint8, AUTOMATIC)  ClientId
  );                                                                                                                   /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_TestSnapshotRecordSelected
 *****************************************************************************/
/*!
 * \brief         Test if a snapshot record is selected
 *
 * \details       Test if a snapshot record is selected for the given 
 *                ClientId.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                A snapshot record is selected
 * \return        FALSE
 *                No snapshot record is selected
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestSnapshotRecordSelected(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_TestExtendedRecordSelected
 *****************************************************************************/
/*!
 * \brief         Test if an extended data record is selected
 *
 * \details       Test if an extended data record is selected for the given
 *                ClientId.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                An extended data record is selected
 * \return        FALSE
 *                No extended data record is selected
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestExtendedRecordSelected(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_DisableDTCRecordUpdate
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
 *                Event memory update successfully disabled
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
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_ClientAccess_DisableDTCRecordUpdate(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_EnableDTCRecordUpdate
 *****************************************************************************/
/*!
 * \brief         Release a previously prepared memory entry.
 *
 * \details       Releases the memory entry previously locked by
 *                Dem_DisableDTCRecordUpdate.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        E_OK
 *                The memory entry has been released.
 * \return        DEM_PENDING
 *                The asynchronous call Dem_DisableDTCRecordUpdate has not
 *                finished yet.
 * \return        E_NOT_OK
 *                There was no memory entry to release.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_ClientAccess_EnableDTCRecordUpdate(
  CONST(uint8, AUTOMATIC) ClientId
  );
#endif

/* ****************************************************************************
 * Dem_ClientAccess_FillDTCReadoutBufferData
 *****************************************************************************/
/*!
 * \brief         Copy the memory entry contents into the ReadoutBuffer.
 *
 * \details       For all clients with ReadoutBuffer state QUEUED:
 *                copy the memory entry contents into the ReadoutBuffer.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_ClientAccess_FillDTCReadoutBufferData(
  void
  );

/* ****************************************************************************
 * Dem_ClientAccess_ClearDTC
 *****************************************************************************/
/*!
 * \brief         Clear the selected DTC/DTC Group/All DTCs
 *
 * \details       Clear the selected DTC/DTC Group/All DTCs
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        Status of the clear request
 *
 * \pre           A DTC selection is available
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_ClientAccess_ClearDTC(
  CONST(uint8, AUTOMATIC) ClientId
  );
  
#if (DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON) 
/* ****************************************************************************
 * Dem_ClientAccess_J1939ClearDTC
 *****************************************************************************/
/*!
 * \brief         Clear the selected J1939 DTCs
 *
 * \details       Clear the selected J1939 DTCs
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[in]     DTCTypeFilter
 *                The type of DTCs to be cleared
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 *
 * \return        Status of the clear request
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_ClientAccess_J1939ClearDTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(uint8, AUTOMATIC)  DTCTypeFilter,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin
  );
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939 == STD_ON) )
/* ****************************************************************************
 * Dem_ClientAccess_TestFreezeFrameIteratorValid
 *****************************************************************************/
/*!
 * \brief         Test if the client has a valid freeze frame iterator.
 *
 * \details       Test if the client has a valid freeze frame iterator.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                Client has a valid freeze frame iterator
 * \return        FALSE
 *                Client doesn't have a valid freeze frame iterator
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON ||
 *                DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestFreezeFrameIteratorValid(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_TestFreezeFrameFilterSet
 *****************************************************************************/
/*!
 * \brief         Test if a freeze frame filter has been set.
 *
 * \details       Test if a freeze frame filter has been set for the given 
 *                ClientId.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                A freeze frame filter has been set
 * \return        FALSE
 *                No freeze frame filter has been set
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestFreezeFrameFilterSet(
  CONST(uint8, AUTOMATIC)  ClientId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_ClientAccess_StartFreezeFrameIterator
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
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && ((DEM_CFG_SUPPORT_SRECS == STD_ON) 
 *                   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE  FUNC(Std_ReturnType, DEM_CODE)
Dem_ClientAccess_StartFreezeFrameIterator(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONSTP2VAR(uint16, AUTOMATIC, DEM_DCM_DATA)  NumberOfFilteredRecords
);
#endif

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) \
   && ((DEM_CFG_SUPPORT_SRECS == STD_ON) || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON)))
/* ****************************************************************************
 * Dem_ClientAccess_GetNextFreezeFrameRecord
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
 * \return        TRUE
 *                Returned next filtered element.
 * \return        FALSE
 *                No further element (matching the filter criteria) found,
 *                iteration is complete.
 *
 * \config        (DEM_CFG_SUPPORT_DCM == STD_ON)
 *                && ((DEM_CFG_SUPPORT_SRECS == STD_ON) 
 *                   || (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
 * \pre           The record filter has been initialized by
 *                Dem_SetFreezeFrameRecordFilter.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_GetNextFreezeFrameRecord(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC,                                                                              /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
  CONSTP2VAR(uint8, AUTOMATIC, DEM_DCM_DATA)  RecordNumber                                                                       /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7 */
);
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_GetDTCByOccurrenceTime
 *****************************************************************************/
/*!
 * \brief         Get a DTC based on occurrence time.
 *
 * \details       Returns a DTC based on occurrence time.
 *
 * \param[in]     DTCRequest
 *                The requested occurrence time of the DTC:
 *                - DEM_FIRST_FAILED_DTC: first failed DTC
 *                - DEM_MOST_RECENT_FAILED_DTC: most recent failed DTC
 *                - DEM_FIRST_DET_CONFIRMED_DTC: first detected confirmed DTC
 *                - DEM_MOST_REC_DET_CONFIRMED_DTC: most recently detected
 *                  confirmed DTC 
 * \param[out]    DTC
 *                Receives the DTC value in UDS format returned by the
 *                function. If the return value of the function is other than
 *                OK this parameter does not contain valid data. Validity of 
 *                this pointer has to be guaranteed by the caller.
 *
 * \return        TRUE
 *                Get of DTC was successful.
 * \return        FALSE
 *                The call was not successful, no DTC is available for the
 *                given occurrence time.
 *
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 * \pre           Arguments are checked and valid.
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_GetDTCByOccurrenceTime(
  CONST(Dem_DTCRequestType, AUTOMATIC)  DTCRequest,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_DCM_DATA)  DTC
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_FilterNumberMemory
 *****************************************************************************/
/*!
 * \brief         Fetch number of DTCs matching the client specific filter settings.
 *
 * \details       Fetch number of DTCs matching the client specific filter settings.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        Number of DTCs matching the filter criteria
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_ClientAccess_FilterNumberMemory(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_EventChangeDtcSuppression
 *****************************************************************************/
/*!
 * \brief         Suppress event or release event suppression as requested by the client 
 *
 * \details       Suppress event or release event suppression as requested by the client 
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.

 * \param[in]     SuppressionStatus
 *                TRUE: Suppress the DTC
 *                FALSE: Lift suppression of the DTC
 *
 * \return        E_OK
 *                The suppression was changed successfully
 * \return        E_NOT_OK
 *                The request was rejected because no valid event was found for
 *                the given ClientId
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_ClientAccess_EventChangeDtcSuppression(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(boolean, AUTOMATIC)  SuppressionStatus
  );
#endif

#if (DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_EventRetrieveDtcSuppression
 *****************************************************************************/
/*!
 * \brief         Suppress event or release event suppression as requested by the client 
 *
 * \details       Suppress event or release event suppression as requested by the client 
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.

 * \param[out]    SuppressionStatus
 *                Pointer to receive the suppression state of the DTC.
 *
 * \return        E_OK
 *                The suppression state was retrieved successfully
 * \return        E_NOT_OK
 *                The request was rejected because no valid event was found for
 *                the given ClientId
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DTCSUPPRESSION == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_ClientAccess_EventRetrieveDtcSuppression(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(boolean, AUTOMATIC, DEM_APPL_DATA)  SuppressionStatus
  );
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_TestNodeValid
 *****************************************************************************/
/*!
 * \brief         Test if the client has a valid node.
 *
 * \details       Test if the client has a valid node.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        TRUE
 *                Client has a valid node
 * \return        FALSE
 *                Client doesn't have a valid node
 *
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClientAccess_TestNodeValid(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_GetNode
 *****************************************************************************/
/*!
 * \brief         Return the node for the client
 *
 * \details       Return the node for the client
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        The node for the client
 *
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_ClientAccess_GetNode(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_SetFirstDTCWithLampStatus
 *****************************************************************************/
/*!
 * \brief         Initializes a 'First DTC with lamp status' filter for the 
 *                given client
 *
 * \details       Initializes a 'First DTC with lamp status' filter for the 
 *                given client
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ClientAccess_SetFirstDTCWithLampStatus(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_GetNextDTCwithLampStatus
 *****************************************************************************/
/*!
 * \brief         Filters the next J1939 DTC with lamp status.
 *
 * \details       Filters the next J1939 DTC with lamp status.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    LampStatus
 *                Pointer to the LampStatus buffer.
 * \param[out]    J1939DTC
 *                Pointer to the J1939DTC .
 * \param[out]    OccurrenceCounter
 *                Pointer to the OccurrenceCounter buffer.
 *
 * \return        E_OK
 *                Matching DTC with required attributes returned.
 * \return        DEM_NO_SUCH_ELEMENT
 *                No matching DTC returned.
 *
 * \pre           J1939 iteration has been started by Dem_J1939DcmFirstDTCwithLampStatus
 * \config        DEM_CFG_SUPPORT_J1939_DM31 == STD_ON || DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_ClientAccess_GetNextDTCwithLampStatus(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_J1939DCM_DATA)  LampStatus,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_SetJ1939DTCFilter
 *****************************************************************************/
/*!
 * \brief         Initializes a J1939 DTC filter with the given criteria.
 *
 * \details       For the given ClientId set up a J1939 DTC filter with the 
 *                given criteria.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[in]     DTCStatusFilter
 *                The filter type defining the DTCs to be filtered.
 * \param[in]     DTCKind
 *                DTC kind to filter.
 * \param[in]     DTCOrigin
 *                The external identifier of the event memory.
 * \param[out]    LampStatus
 *                Pointer to receive the Lamp status for the node assigned to 
 *                the client.
 *
 * \return        E_OK
 *                Filter was accepted
 *                E_NOT_OK
 *                Filter was not accepted or no filter available for client
 *
 * \config        DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_ClientAccess_SetJ1939DTCFilter(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(Dem_J1939DcmDTCStatusFilterType, AUTOMATIC)  DTCStatusFilter,
  CONST(Dem_DTCKindType, AUTOMATIC)  DTCKind,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONSTP2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_J1939DCM_DATA)  LampStatus
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_GetNumberOfFilteredJ1939DTC
 *****************************************************************************/
/*!
 * \brief         Fetch number of DTCs matching the client specific J1939 DTC 
 *                filter settings.
 *
 * \details       Fetch number of DTCs matching the client specific J1939 DTC 
 *                filter settings.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 *
 * \return        Number of DTCs matching the J1939 DTC filter criteria
 *
 * \pre           J1939 iteration has been started by Dem_J1939DcmSetDTCFilter
 * \config        DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_ClientAccess_GetNumberOfFilteredJ1939DTC(
  CONST(uint8, AUTOMATIC)  ClientId
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_GetNextFilteredJ1939DTC
 *****************************************************************************/
/*!
 * \brief         Get the next matching DTC
 *
 * \details       Get the next DTC matching the J1939 DTC filter criteria
 *                set with Dem_ClientAccess_SetJ1939DTCFilter
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    J1939DTC
 *                Pointer to the J1939DTC .
 * \param[out]    OccurrenceCounter
 *                Pointer to the OccurrenceCounter buffer.
 *
 * \return        E_OK
 *                Matching DTC with required attributes returned.
 * \return        DEM_NO_SUCH_ELEMENT
 *                No matching DTC returned.
 *
 * \config        DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 * \pre           J1939 iteration has been started by Dem_J1939DcmSetDTCFilter
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_ClientAccess_GetNextFilteredJ1939DTC(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_ReadDiagnosticReadiness
 *****************************************************************************/
/*!
 * \brief         Get the diagnostic readiness for the given client
 *
 * \details       Get the diagnostic readiness for the given client
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    DiagnosticReadiness
 *                Pointer to the the diagnostic readiness value.
 *
 * \return        E_OK
 *                Diagnostic readiness was written to output value.
 * \return        E_NOT_OK
 *                Diagnostic readiness couldn't be read.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_ClientAccess_ReadDiagnosticReadiness(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(Dem_J1939DcmDiagnosticReadiness1Type, AUTOMATIC, DEM_J1939DCM_DATA)  DiagnosticReadiness
  );
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_SetJ1939FreezeFrameIterator
 *****************************************************************************/
/*!
 * \brief         Sets a J1939 freeze frame record filter with the given 
 *                criteria.
 *
 * \details       Sets a J1939 freeze frame record filter with the given 
 *                criteria.
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[in]     FreezeFrameKind
 *                Freeze frame kind
 *
 * \return        E_OK
 *                The filter is accepted
 * \return        E_NOT_OK
 *                Wrong filter selected
 *
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_ClientAccess_SetJ1939FreezeFrameIterator(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONST(Dem_J1939DcmSetFreezeFrameFilterType, AUTOMATIC) FreezeFrameKind
  );
#endif

#if (DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON)
/* ****************************************************************************
 * Dem_ClientAccess_GetNextJ1939FreezeFrame
 *****************************************************************************/
/*!
 * \brief         Get the next matching J1939 freeze frame record.
 *
 * \details       Get the next J1939 freeze frame record matching the filter
 *                set with Dem_ClientAccess_SetJ1939FreezeFrameIterator
 *
 * \param[in]     ClientId
 *                Unique client id, assigned to the instance of the calling
 *                module.
 * \param[out]    J1939DTC
 *                Pointer to the J1939DTC .
 * \param[out]    OccurrenceCounter
 *                Pointer to the OccurrenceCounter buffer.
 * \param[out]    DestBuffer
 *                Buffer to receive the J1939 freeze frame data.
 * \param[in,out] BufSize
 *                In:  Buffer size
 *                Out: Number of bytes written
 *
 * \return        E_OK
 *                Matching J1939 freeze frame with required attributes returned.
 * \return        DEM_NO_SUCH_ELEMENT
 *                No matching J1939 freeze frame returned.
 * \return        DEM_PENDING
 *                The operation was started and is currently processed.
 * \return        DEM_BUFFER_TOO_SMALL
 *                The provided buffer is not large enough.
 *
 * \config        DEM_FEATURE_NEED_J1939_FREEZEFRAME == STD_ON
 * \pre           J1939 iteration has been started by Dem_J1939DcmSetFreezeFrameFilter
 *
 * \context       TASK|ISR2, from the master partition only
 * \synchronous   FALSE
 * \reentrant     TRUE for different ClientIDs
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_ClientAccess_GetNextJ1939FreezeFrame(
  CONST(uint8, AUTOMATIC)  ClientId,
  CONSTP2VAR(uint32, AUTOMATIC, DEM_J1939DCM_DATA)  J1939DTC,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  OccurrenceCounter,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  DestBuffer,
  CONSTP2VAR(uint8, AUTOMATIC, DEM_J1939DCM_DATA)  BufSize 
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_CLIENTACCESS_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClientAccess_Interface.h
 *********************************************************************************************************************/
