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
 *  \defgroup   Dem_ClearTask Clear Task
 *  \{
 *  \file       Dem_ClearTask_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of ClearTask subcomponent
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

#if !defined (DEM_CLEARTASK_INTERFACE_H)
#define DEM_CLEARTASK_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ClearTask_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_ClearTask_Properties Properties
 * \{
 */

/* ****************************************************************************
 * Dem_ClearTask_GetClearClient()
 *****************************************************************************/
/*!
 * \brief         Get the client of the current clear operation.
 *
 * \details       Get the client of the current clear operation.
 *
 * \return        The client of the clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE) 
Dem_ClearTask_GetClearClient(
  void
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
 * \defgroup Dem_ClearTask_Public Public Methods
 * \{
 */


/* ****************************************************************************
 * Dem_ClearTask_Init()
 *****************************************************************************/
/*!
 * \brief         Initialize the subcomponent
 *
 * \details       Initializes the subcomponent
 *
 * \pre           Only call during the initialization phase
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ClearTask_Init(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_MainFunction()
 *****************************************************************************/
/*!
 * \brief         Process the current clear requests
 *
 * \details       Process the current clear requests
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ClearTask_MainFunction(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_TryNewClear()
 *****************************************************************************/
/*!
 * \brief         Try to start a clear DTC operation
 *
 * \details       Starts a clear operation
 *
 * \param[in]     ClearRequest
 *                The ClearDTC request
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClearTask_TryNewClear(
  CONST(Dem_ClearTask_ClearRequestConstPtrType, AUTOMATIC)  ClearRequest
  );

# if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_ClearTask_NotifyClearCompleted()
 *****************************************************************************/
/*!
 * \brief         Notify all cleared blocks are persisted in NV
 *
 * \details       Notify all cleared blocks are persisted in NV
 *
 * \pre           -
 * \config        (DEM_CFG_USE_NVM ==STD_ON)
 *                && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ClearTask_NotifyClearCompleted(
  void
  );
#endif

# if (DEM_CFG_USE_NVM == STD_ON) && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_ClearTask_NotifyClearWriteError()
 *****************************************************************************/
/*!
 * \brief         Notify write error occurred while writing a cleared block
 *
 * \details       Notify write error occurred while writing a cleared block
 *
 * \pre           -
 * \config        (DEM_CFG_USE_NVM ==STD_ON)
 *                && (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ClearTask_NotifyClearWriteError(
  void
  );
#endif

#if (DEM_CFG_NOTIFY_CLEAR_ALLOWED == STD_ON)
/* ****************************************************************************
* Dem_ClearTask_ClearEventAllowed
*****************************************************************************/
/*!
* \brief         Calls user defined clear allowed callback
*
* \details       This function calls a user defined clear allowed callback
*                and handles the related error conditions.
*
* \param[in]     EventId
*                Unique handle of the Event.
*                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
*
* \return        TRUE
*                The event may be cleared
* \return        FALSE
*                The application does not allow clearing
*
* \pre           RTE is started
* \config        DEM_CFG_NOTIFY_CLEAR_ALLOWED == STD_ON
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClearTask_ClearEventAllowed(
CONST(Dem_EventIdType, AUTOMATIC)  EventId
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
 * \defgroup Dem_ClearTask_Private Private Methods
 * \{
 */

/* ****************************************************************************
 * Dem_ClearTask_GetClearMemoryId()
 *****************************************************************************/
/*!
 * \brief         Get the memory id of the current clear operation.
 *
 * \details       Get the memory id of the current clear operation.
 *
 * \return        The memory id of the current clear operation.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE) 
Dem_ClearTask_GetClearMemoryId(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_SetClearMemory()
 *****************************************************************************/
/*!
 * \brief         Set the memory id of the current clear operation.
 *
 * \details       Set the memory id of the current clear operation.
 *
 * \param[in]     MemoryId
 *                The new memory id of the current clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_ClearTask_SetClearMemory(
  CONST(uint8, AUTOMATIC) MemoryId
  );

/* ****************************************************************************
 * Dem_ClearTask_GetClearGroup()
 *****************************************************************************/
/*!
 * \brief         Get the clear group of the current clear operation.
 *
 * \details       Get the clear group of the current clear operation.
 *
 * \return        The clear group of the current clear operation.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE) 
Dem_ClearTask_GetClearGroup(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_GetClearEvent()
 *****************************************************************************/
/*!
 * \brief         Get the clear event of the current clear operation.
 *
 * \details       Get the clear event of the current clear operation.
 *
 * \return        The clear event of the current clear operation.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE) 
Dem_ClearTask_GetClearEvent(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_SetClearEvent()
 *****************************************************************************/
/*!
 * \brief         Set the clear event of the current clear operation.
 *
 * \details       Set the clear event of the current clear operation.
 *
 * \param[in]     EventId
 *                The new clear event of the current clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_ClearTask_SetClearEvent(
  CONST(Dem_EventIdType, AUTOMATIC) EventId
  );

/* ****************************************************************************
 * Dem_ClearTask_GetClearCode()
 *****************************************************************************/
/*!
 * \brief         Get the clear code of the current clear operation.
 *
 * \details       Get the clear code of the current clear operation.
 *
 * \return        The clear code of the current clear operation.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE) 
Dem_ClearTask_GetClearCode(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_GetClearMask()
 *****************************************************************************/
/*!
 * \brief         Get the clear mask of the current clear operation.
 *
 * \details       Get the clear mask of the current clear operation.
 *
 * \return        The clear mask of the current clear operation.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE) 
Dem_ClearTask_GetClearMask(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_GetClearNodeIndex()
 *****************************************************************************/
/*!
 * \brief         Get the clear node of the current clear operation.
 *
 * \details       Get the clear node of the current clear operation.
 *
 * \return        The clear node of the current clear operation.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE) 
Dem_ClearTask_GetClearNodeIndex(
  void
  );

#if (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_ClearTask_TestClearWriteErrors()
 *****************************************************************************/
/*!
 * \brief         Test the write errors flag of the current clear operation.
 *
 * \details       Test the write errors flag of the current clear operation.
 *
 * \return        TRUE
 *                The write errors flag was set
 * \return        FALSE
 *                The write errors flag was not set
 *
 * \pre           -
 * \config        DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE) 
Dem_ClearTask_TestClearWriteErrors(
  void
  );
#endif

#if (DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON)
/* ****************************************************************************
 * Dem_ClearTask_SetClearWriteErrors()
 *****************************************************************************/
/*!
 * \brief         Set the write errors flag of the current clear operation.
 *
 * \details       Set the write errors flag of the current clear operation.
 *
 * \pre           -
 * \config        DEM_CFG_CLEAR_NV_END_RESPONSE == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_ClearTask_SetClearWriteErrors(
  void
  );
#endif

/* ****************************************************************************
 * Dem_ClearTask_ResetClearWriteErrors()
 *****************************************************************************/
/*!
 * \brief         Reset the write errors flag of the current clear operation.
 *
 * \details       Reset the write errors flag of the current clear operation.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_ClearTask_ResetClearWriteErrors(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_ProcessClearSingleDtc
 *****************************************************************************/
/*!
 * \brief         Clears a single dtc
 *
 * \details       This function clears a single DTC and manages the related
 *                API state transitions.
 *
 * \return        TRUE
 *                The event was cleared
 * \return        FALSE
 *                The event was not cleared, clearing was forbidden by the
 *                application
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_ClearTask_ProcessClearSingleDtc(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_DTCCleared
 *****************************************************************************/
/*!
 * \brief         Clear the DTC and update global state of clear progress.
 *
 * \details       Clear the DTC and update global state of clear progress.
 *
 * \param[in]     EventIterator
 *                Master id of the DTC that shall be cleared.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_ClearTask_DTCCleared(
  CONST(uint16, AUTOMATIC) EventIterator
  );

/* ****************************************************************************
 * Dem_ClearTask_ProcessClearDtcGroup
 *****************************************************************************/
/*!
 * \brief         Process UDS clear dtc group requests
 *
 * \details       The function processes clearing for the events in range
 *                [FirstEventId, LastEventId] (inclusive interval) that match
 *                the ClearDTC parameters.
 *
 * \param[in]     FirstEventId
 *                Numerically smallest eventid belonging to the range
 * \param[in]     LastEventId
 *                Numerically largest eventid belonging to the range
 *
 * \pre           The global clear DTC context must have been initialized
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_ClearTask_ProcessClearDtcGroup(
  CONST(uint16, AUTOMATIC)  FirstEventId,
  CONST(uint16, AUTOMATIC)  LastEventId
  );

#if (DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON)
/* ****************************************************************************
 * Dem_ClearTask_ProcessClearJ1939Dtc
 *****************************************************************************/
/*!
 * \brief         Process J1939 clear dtc requests
 *
 * \details       The function processes clearing for the events in range
 *                [FirstEventId, LastEventId] (inclusive interval) that match
 *                the J1939 ClearDTC parameters.
 *
 * \param[in]     FirstEventId
 *                Numerically smallest eventid belonging to the range
 * \param[in]     LastEventId
 *                Numerically largest eventid belonging to the range
 *
 * \pre           The global clear DTC context must have been initialized
 * \config        DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_ClearTask_ProcessClearJ1939Dtc(
  CONST(uint16, AUTOMATIC)  FirstEventId,
  CONST(uint16, AUTOMATIC)  LastEventId
  );
#endif

/* ****************************************************************************
 ! Dem_ClearTask_ProcessClearDtc
 *****************************************************************************/
/*!
 * \brief         Processes clear dtc requests
 *
 * \details       This function processes clear DTC requests. Group clear is
 *                optionally distributed across multiple tasks, single clear
 *                is processed immediately.
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_ClearTask_ProcessClearDtc(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_GetClearState()
 *****************************************************************************/
/*!
 * \brief         Get the status of the current clear operation.
 *
 * \details       Get the status of the current clear operation.
 *
 * \return        The status of the clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE) 
Dem_ClearTask_GetClearState(
  void
  );

/* ****************************************************************************
 * Dem_ClearTask_SetClearState()
 *****************************************************************************/
/*!
 * \brief         Set the status of the current clear operation.
 *
 * \details       Set the status of the current clear operation.
 *
 * \param[in]     State
 *                The new status of the current clear operation
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different ClearDTCHandle
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE) 
Dem_ClearTask_SetClearState(
  CONST(uint8, AUTOMATIC) State
  );

/*!
* \}
*/
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_CLEARTASK_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_ClearTask_Interface.h
 *********************************************************************************************************************/
