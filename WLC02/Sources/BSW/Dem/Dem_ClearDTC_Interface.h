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
/*! \ingroup    Dem_ClientData
 *  \defgroup   Dem_ClearDTC ClearDTC
 *  \{
 *  \file       Dem_ClearDTC_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) Interface declaration file
 *  \details    Public interface of ClearDTC subcomponent
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

#if !defined (DEM_CLEARDTC_INTERFACE_H)
#define DEM_CLEARDTC_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ClearDTC_Types.h"
#include "Dem_ClearTask_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_ClearDTC_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_ClearDTC_GetClearStatus()
 *****************************************************************************/
/*!
 * \brief         Get the status of a clear operation.
 *
 * \details       -
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to modify.
 *
 * \return        The status of the clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_StatusType, DEM_CODE) Dem_ClearDTC_GetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  );

/* ****************************************************************************
 * Dem_ClearDTC_TestClearWwhObdAllDTCsAllowed()
 *****************************************************************************/
/*!
 * \brief         Test if clearing of all WWH-OBD related DTCs is allowed.
 *
 * \details       Test if clearing of all WWH-OBD related DTCs is allowed.
 *
 * \return        TRUE
 *                Clearing WWH-OBD DTCs is allowed
 * \return        FALSE
 *                Clearing WWH-OBD DTCs is not allowed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) Dem_ClearDTC_TestClearWwhObdAllDTCsAllowed(
  void
  );

/* ****************************************************************************
 * Dem_ClearDTC_TestClearObdAllDTCsAllowed()
 *****************************************************************************/
/*!
 * \brief         Test if clearing of all OBD related DTCs is allowed.
 *
 * \details       Test if clearing of all OBD related DTCs is allowed.
 *
 * \return        TRUE
 *                Clearing OBD DTCs is allowed
 * \return        FALSE
 *                Clearing OBD DTCs is not allowed
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) Dem_ClearDTC_TestClearObdAllDTCsAllowed(
  void
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
 * \defgroup Dem_ClearDTC_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_ClearDTC_SetClearData()
 *****************************************************************************/
/*!
 * \brief         Set the data of a clear operation.
 *
 * \details       Set the data of a clear operation.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle of the data to be modified.
 * \param[in]     ClearDTCData
 *                The clear data to be set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_SetClearData(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_ClearDTC_DataType, AUTOMATIC)  ClearDTCData
  );

/* ****************************************************************************
 * Dem_ClearDTC_GetClearData()
 *****************************************************************************/
/*!
 * \brief         Get the data of a clear operation.
 *
 * \details       Get the data of a clear operation.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to read.

 * \return        The data of the clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_DataType, DEM_CODE) Dem_ClearDTC_GetClearData(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  );

/* ****************************************************************************
 * Dem_ClearDTC_SetClearStatus()
 *****************************************************************************/
/*!
 * \brief         Set the status of a clear operation.
 *
 * \details       Set the status of a clear operation.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to modify.
 * \param[in]     ClearDTCStatus
 *                The ClearDTCStatus to set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_SetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_ClearDTC_StatusType, AUTOMATIC)  ClearDTCStatus
  );

/* ****************************************************************************
 * Dem_ClearDTC_GetClearSelector()
 *****************************************************************************/
/*!
 * \brief         Get the DTCSelector of a clear operation.
 *
 * \details       Get the DTCSelector of a clear operation.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to read.
 *
 * \return        The DTCSelector of the clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_DTCSelector_HandleType, DEM_CODE) Dem_ClearDTC_GetClearSelector(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  );

/* ****************************************************************************
 * Dem_ClearDTC_CallStartNotifications()
 *****************************************************************************/
/*!
 * \brief         Call all clear start notification callbacks.
 *
 * \details       Call all clear start notification callbacks.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_CallStartNotifications(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_ClearDTC_CallEndNotifications()
 *****************************************************************************/
/*!
 * \brief         Call all clear end notification callbacks.
 *
 * \details       Call all clear end notification callbacks.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_CallEndNotifications(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/* ****************************************************************************
 * Dem_ClearDTC_StartClearOperation()
 *****************************************************************************/
/*!
 * \brief         Try to start a clear DTC operation
 *
 * \details       Starts a clear operation
 *
 * \param[in]     ClearRequest
 *                The ClearDTC request
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 *
 * \return        DEM_PENDING
 *                The Clear DTC operation was started
 * \return        DEM_CLEAR_BUSY
 *                Another Clear DTC operation is active
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearOperation(
  CONST(Dem_ClearTask_ClearRequestConstPtrType, AUTOMATIC)  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  );

/* ****************************************************************************
 * Dem_ClearDTC_StartClearEvent()
 *****************************************************************************/
/*!
 * \brief         Start clear DTC for a single event
 *
 * \details       Initializes a clear DTC handler to process clearing a single
 *                event
 *
 * \param[in]     ClearRequest
 *                Pointer to clear request structure
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 *
 * \return        Status of the started clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearEvent(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  );

/* ****************************************************************************
 * Dem_ClearDTC_StartClearAllDTCs()
 *****************************************************************************/
/*!
 * \brief         Start clear DTC for a single event
 *
 * \details       Initializes a clear DTC handler to process clearing a single
 *                event
 *
 * \param[in]     ClearRequest
 *                Pointer to clear request structure
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 *
 * \return        Status of the started clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_ClearDTC_StatusType, DEM_CODE) Dem_ClearDTC_StartClearAllDTCs(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  );

/* ****************************************************************************
 * Dem_ClearDTC_StartClearGroup()
 *****************************************************************************/
/*!
 * \brief         Start clear DTC for a single event
 *
 * \details       Initializes a clear DTC handler to process clearing a single
 *                event
 *
 * \param[in]     ClearRequest
 *                Pointer to clear request structure
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 *
 * \return        Status of the started clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearGroup(
  Dem_ClearTask_ClearRequestPtrType  ClearRequest,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
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
 * \defgroup Dem_ClearDTC_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_ClearDTC_Init()
 *****************************************************************************/
/*!
 * \brief         Initialize the clear DTC subcomponent.
 *
 * \details       Initializes the subcomponent. All clear operations are idle
 *                after initialization.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_Init(
  void
  );

/* ****************************************************************************
 % Dem_ClearDTC_StartClear()
 *****************************************************************************/
/*!
 * \brief         Start clear DTC for a single event
 *
 * \details       Initializes a clear DTC handler to process clearing a single
 *                event
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to modify.
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 *
 * \return        Status of the started clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClear(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector
  );

#if (DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON)
/* ****************************************************************************
 * Dem_ClearDTC_StartClearJ1939()
 *****************************************************************************/
/*!
 * \brief         Start clear J1939 DTCs
 *
 * \details       Initializes a clear DTC handler to process clearing J1939 DTCs
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to modify.
 * \param[in]     DTCSelector
 *                The selector holding the selected DTC to clear
 * \param[in]     DTCTypeFilter
 *                The type of DTCs to be cleared
 * \param[in]     Node
 *                The node to be cleared
 *
 * \return        Status of the started clear operation
 *
 * \config        DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC_StartClearJ1939(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle,
  CONST(Dem_DTCSelector_HandleType, AUTOMATIC)  DTCSelector,
  CONST(uint8, AUTOMATIC)  DTCTypeFilter,
  CONST(uint8, AUTOMATIC)  Node
  );
#endif

/* ****************************************************************************
 * Dem_ClearDTC_ResetClearStatus()
 *****************************************************************************/
/*!
 * \brief         Reset the clear status.
 *
 * \details       Clears the status of the ClearDTCHandle to IDLE. 
 *                This operation will fail if the current state is not final.
 *                
 *                The use-case of this API is to allow clients to clear the
 *                final clear result, distinguishing between a result poll and
 *                a new clear request.
 *
 * \param[in]     ClearDTCHandle
 *                The ClearDTC handle to modify.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_ResetClearStatus(
  CONST(Dem_ClearDTC_HandleType, AUTOMATIC)  ClearDTCHandle
  );

/* ****************************************************************************
 * Dem_ClearDTC_NotifyClearResult()
 *****************************************************************************/
/*!
 * \brief         Notification after clear has finished.
 *
 * \details       Notification callback to report the end of a clear operation.
 *
 * \param[in]     QueueClearState
 *                The notified state.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different DTCSelectorId
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) Dem_ClearDTC_NotifyClearResult(
  CONST(uint8, AUTOMATIC)  QueueClearState
  );

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_CLEARDTC_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClearDTC_Interface.h
 *********************************************************************************************************************/
