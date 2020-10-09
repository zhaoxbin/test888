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
 *  \defgroup   Dem_DTCSelector DTCSelector
 *  \{
 *  \file       Dem_DTCSelector_Interface.h
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

#if !defined (DEM_DTCSELECTOR_INTERFACE_H)
#define DEM_DTCSELECTOR_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_DTCSelector_Types.h"
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
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_DTCSelector_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_DTCSelector_GetGroupId()
 *****************************************************************************/
/*!
 * \brief         Get the GroupId stored in the selector object
 *
 * \details       Get the GroupId stored in the selector object
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 *
 * \return        one of
 *                 - DEM_DTCSELECTOR_GROUP_ALL_DTCS
 *                 - DEM_DTCSELECTOR_GROUP_EMISSION_RELATED
 *                 - DEM_DTCSELECTOR_GROUP_WWH_OBD_ALL_DTC
 *                if DEM_DTCSELECTOR_SELECTION_ALL_DTCS was selected
 * \return        DEM_DTCSELECTOR_GROUP_INVALID if no group was selected.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_GroupIdType, DEM_CODE)
Dem_DTCSelector_GetGroupId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

#if (DEM_CFG_CLEAR_GROUP_DTCS == STD_ON)
 /* ****************************************************************************
  * Dem_DTCSelector_GetGroupMask()
  *****************************************************************************/
 /*!
  * \brief         Get the Group mask stored in the selector object
  *
  * \details       Get the GroupMask stored in the selector object
  *
  * \param[in]     DTCSelectorId
  *                The object to read from.
  *
  * \return        The GroupMask stored in the selector object.
  * \return        DEM_CFG_GROUPMASK_NONE if no group was selected.
  *
  * \pre           -
  * \config        DEM_CFG_CLEAR_GROUP_DTCS == STD_ON
  *
  * \context       TASK|ISR2
  * \synchronous   TRUE
  * \reentrant     TRUE
  *****************************************************************************/
 DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
 Dem_DTCSelector_GetGroupMask(
   CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
   );
#endif

/* ****************************************************************************
 * Dem_DTCSelector_GetEventId()
 *****************************************************************************/
/*!
 * \brief         Get the EventId stored in the selector object
 *
 * \details       Get the EventId stored in the selector object
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 *
 * \return        The EventId stored in the selector object.
 * \return        DEM_EVENT_INVALID if no event was selected
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCSelector_GetEventId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_GetMemoryId()
 *****************************************************************************/
/*!
 * \brief         Get the MemoryId stored in the selector object
 *
 * \details       Get the MemoryId stored in the selector object
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 *
 * \return        The MemoryId stored in the selector object.
 *                DEM_CFG_MEMORYID_INVALID if no selection was requested
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_GetMemoryId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_GetSelectionResult()
 *****************************************************************************/
/*!
 * \brief         Get the result of the last selection
 *
 * \details       Get the result of the last selection
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 *
 * \return        DEM_DTCSELECTOR_SELECTION_INVALID
 *                Error, no DTC or group was selected
 * \return        DEM_DTCSELECTOR_SELECTION_DTC
 *                A DTC was selected
 * \return        DEM_DTCSELECTOR_SELECTION_GROUP
 *                A DTC group was selected
 * \return        DEM_DTCSELECTOR_SELECTION_WRONG_MEMORY
 *                The DTC or group does not belong to the selected memory
 * \return        DEM_DTCSELECTOR_SELECTION_WRONG_DTC
 *                The selected number does not map to a DTC or DTC group
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_ResultType, DEM_CODE)
Dem_DTCSelector_GetSelectionResult(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_GetSelectionArguments
 *****************************************************************************/
/*!
 * \brief         Returns the original arguments of the selection.
 *
 * \details       Returns the original arguments of the selection.
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 *
 * \return        DTC selection arguments.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_RequestType, DEM_CODE) Dem_DTCSelector_GetSelectionArguments(
  CONST(uint8, AUTOMATIC)  DTCSelectorId
  );

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
 * \defgroup Dem_DTCSelector_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_DTCSelector_InitDefault()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector.
 *
 * \details       Initializes a selector, the selector does not contain a
 *                selection afterwards.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitDefault(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_SelectDTC()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector from DTC information.
 *
 * \details       Initializes a selector based on the passed DTC number information.
 *
 * \param[in]     DTCSelectorId
 *                The object to read from.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     MemoryId
 *                The event memory handle
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_SelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId
  );

/* ****************************************************************************
 * Dem_DTCSelector_LockSelectDTC()
 *****************************************************************************/
/*!
 * \brief         Locks access to the API Dem_SelectDTC
 *
 * \details       Incrementing internal counter for active asynchronous 
 *                operations that require Dem_SelectDTC in the selector object  
 *
 * \param[in]     DTCSelectorId
 *                Handle for DTC Selector
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_LockSelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_ReleaseSelectDTC()
 *****************************************************************************/
/*!
 * \brief         Releases access to the API Dem_SelectDTC
 *
 * \details       Decrementing internal counter for active asynchronous 
 *                operations that require Dem_SelectDTC in the selector object 
 *
 * \param[in]     DTCSelectorId
 *                Handle for DTC Selector
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_ReleaseSelectDTC(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

/* ****************************************************************************
 * Dem_DTCSelector_TestSelectDTCLocked()
 *****************************************************************************/
/*!
 * \brief         Tests if access to API Dem_SelectDTC is allowed
 *
 * \details       Tests if internal counter stored in the selector object is 
 *                equal 0 or not. 
 *
 * \param[in]     DTCSelectorId
 *                Handle for DTC Selector
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
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCSelector_TestSelectDTCLocked(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );

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
 * \defgroup Dem_DTCSelector_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_DTCSelector_SetSelectionData()
 *****************************************************************************/
/*!
 * \brief         Stores input parameters to the valid DTC selector.
 *
 * \details       Checks if passed selector handle is valid and stores input 
 *                parameters to the valid DTC selector.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     MemoryId
 *                The event memory handle to store in the selection
 * \param[in]     DTCSelectionType
 *                The type for selection data
 * \param[in]     DTCSelectionResult
 *                The result of a DTC selection
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_SetSelectionData(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_DTCSelector_SelectionType, AUTOMATIC) DTCSelectionType,
  CONST(Dem_DTCSelector_ResultType, AUTOMATIC) DTCSelectionResult
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DTCSelector_SetSelectionData_ActiveAsyncOps()
 *****************************************************************************/
/*!
 * \brief         Stores input parameter to the valid DTC selector.
 *
 * \details       Checks if passed selector handle is valid and stores input
 *                parameter to the valid DTC selector.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     ActiveAsyncOps
 *                The number of active asynchronous operations requiring Dem_SelectDTC()
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_SetSelectionData_ActiveAsyncOps(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint8, AUTOMATIC)  ActiveAsyncOps
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DTCSelector_GetSelectionData()
 *****************************************************************************/
/*!
 * \brief         Return pointer to a DTC selector table entry.
 *
 * \details       Return pointer to a DTC selector table entry.
 *
 * \param[in]     DTCSelectorId
 *                The selector to read.

 * \return        Pointer to DTC selector table entry
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_DataPtrType, DEM_CODE)
Dem_DTCSelector_GetSelectionData(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_DTCSelector_InitGroupId()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector with a group id selection.
 *
 * \details       Initializes a selector with a group id selection.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     MemoryId
 *                The event memory handle to store in the selection
 * \param[in]     GroupId
 *                The group id to store in the selection
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitGroupId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_DTCSelector_GroupIdType, AUTOMATIC)  GroupId
  );

/* ****************************************************************************
 * Dem_DTCSelector_InitGroupMask()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector with a group mask selection.
 *
 * \details       Initializes a selector with a group mask selection.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     MemoryId
 *                The event memory handle to store in the selection
 * \param[in]     GroupMask
 *                The group mask to store in the selection
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitGroupMask(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  GroupMask
  );

/* ****************************************************************************
 * Dem_DTCSelector_InitEventId()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector with an event id selection.
 *
 * \details       Initializes a selector with an event id selection.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     MemoryId
 *                The event memory handle to store in the selection
 * \param[in]     EventId
 *                The event id to store in the selection
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitEventId(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

/* ****************************************************************************
 * Dem_DTCSelector_InitInvalid()
 *****************************************************************************/
/*!
 * \brief         Initialize a selector with an invalid selection
 *
 * \details       Initialize a selector with an invalid selection. The different 
 *                invalid states are used to calculate the corresponding negative
 *                return value of API Dem_GetDTCSelectionResult.
 *
 * \param[in]     DTCSelectorId
 *                The selector to modify.
 * \param[in]     DTCNumber
 *                The DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     DTCOrigin
 *                The event memory of the requested DTC or group of DTC.
 * \param[in]     SelectorState
 *                Possible invalid states are 'Initialization', 'Wrong Origin' or 
 *                'No Match'
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_DTCSelector_InitInvalid(
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelectorId,
  CONST(uint32, AUTOMATIC)  DTCNumber,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(Dem_DTCOriginType, AUTOMATIC)  DTCOrigin,
  CONST(Dem_DTCSelector_ResultType, AUTOMATIC)  SelectorState
  );

/* ****************************************************************************
 * Dem_DTCSelector_FindGroupMaskFromUdsDtc
 *****************************************************************************/
/*!
 * \brief         Find a DTC group mask in the configuration tables.
 *
 * \details       Find a DTC group mask in the configuration tables.
 *
 * \param[in]     DTC
 *                DTC number
 *
 * \return        The group mask matching the passed DTC group number.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_FindGroupMaskFromUdsDtc(
  CONST(uint32, AUTOMATIC)  DTC
  );

/* ****************************************************************************
 * Dem_DTCSelector_TestForAllDtc
 *****************************************************************************/
/*!
 * \brief         Test whether a DTC number encodes an 'AllDTC' mask.
 *
 * \details       Test whether a DTC number encodes an 'AllDTC' mask.
 *
 * \param[in]     DTC
 *                DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 *
 * \return        DEM_DTCSELECTOR_GROUP_ALL_DTCS
 *                The DTC matches the ALL DTC group
 * \return        DEM_DTCSELECTOR_GROUP_EMISSION_RELATED
 *                The DTC matches the emission related DTCs group
 * \return        DEM_DTCSELECTOR_GROUP_WWH_OBD_ALL_DTC
 *                The DTC matches the WWH-OBD ALL DTC group
 * \return        DEM_DTCSELECTOR_GROUP_INVALID if no 'all DTC' group matches
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_GroupIdType, DEM_CODE)
Dem_DTCSelector_TestForAllDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat
  );

/* ****************************************************************************
 * Dem_DTCSelector_TestForGroupDtc
 *****************************************************************************/
/*!
 * \brief         Test if a DTC number encodes a specific DTC group (not
 *                ALLDTCs).
 *
 * \details       Test if a DTC number encodes a specific DTC group (not
 *                ALLDTCs).
 *
 * \param[in]     DTC
 *                DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 *
 * \return        DEM_CFG_GROUPMASK_NONE if the DTC does not matches a DTC group,
 *                otherwise this function returns the configured group mask
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_DTCSelector_TestForGroupDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat
  );

/* ****************************************************************************
 * Dem_DTCSelector_TestForSingleDtc
 *****************************************************************************/
/*!
 * \brief         Test if a DTC number encodes a specific DTC
 *
 * \details       Test if a DTC number encodes a specific DTC. If so,
 *                this function initializes the DTCSelector.
 *
 * \param[in]     DTC
 *                DTC number
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 * \param[in]     MemoryId
 *                The event memory handle
 *
 * \return        DEM_EVENT_INVALID if the DTC has not matched a DTC, otherwise
 *                this function returns the matching EventId
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_DTCSelector_TestForSingleDtc(
  CONST(uint32, AUTOMATIC)  DTC,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(uint8, AUTOMATIC)  MemoryId
  );

/* ****************************************************************************
 * Dem_DTCSelector_TestForSupportedMemoryId()
 *****************************************************************************/
/*!
 * \brief         Test if memory id is valid in context of DTC selection.
 *
 * \details       Test if memory id is valid in context of DTC selection.
 *
 * \param[in]     MemoryId
 *                The event memory handle
 *
 * \return        TRUE   The MemoryId is supported
 * \return        FALSE  The MemoryId is not supported
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_DTCSelector_TestForSupportedMemoryId(
  CONST(uint8, AUTOMATIC) MemoryId
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_DTCSELECTOR_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTCSelector_Interface.h
 *********************************************************************************************************************/
