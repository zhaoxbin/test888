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
 *  \defgroup   Dem_StorageCondition Storage Condition
 *  \{
 *  \file       Dem_StorageCondition_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Interface of the StorageCondition subcomponent
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

#if !defined (DEM_STORAGECONDITION_INTERFACE_H)
#define DEM_STORAGECONDITION_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
#include "Dem_StorageCondition_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \defgroup Dem_StorageCondition_Properties Properties
 * \{
 */

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GetGlobalStorageConditionCount
 *****************************************************************************/
/*!
 * \brief         Get the number of configured storage conditions
 *
 * \details       Get the number of configured storage conditions
 *
 * \return        The number of configured storage conditions
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_StorageCondition_GetGlobalStorageConditionCount(
  void
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
 * \defgroup Dem_StorageCondition_Private Private Methods
 * \{
 */

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GetStorageConditionActive
 *****************************************************************************/
/*!
 * \brief         Get current activation state of storage condition
 *
 * \details       Get current activation state of storage condition
 *
 * \param[in]     StorageCondition
 *                Unique handle of the storage condition
 *
 * \return        Activation state of storage condition
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_GetStorageConditionActive(
  CONST(uint8, AUTOMATIC)  StorageCondition
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_SetStorageConditionActive
 *****************************************************************************/
/*!
 * \brief         Set current activation status of storage condition
 *
 * \details       Set current activation status of storage condition
 *
 * \param[in]     StorageCondition
 *                Unique handle of the storage condition
 * \param[in]     ActiveStatus
 *                New activation state of the storage condition
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_SetStorageConditionActive(
  CONST(uint8, AUTOMATIC)  StorageCondition,
  CONST(boolean, AUTOMATIC)  ActiveStatus
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GetStorageConditionGroupCounter
 *****************************************************************************/
/*!
 * \brief         Get current internal counter of storage condition group
 *
 * \details       Get current internal counter of storage condition group
 *
 * \param[in]     StorageConditionGroup
 *                Unique handle of the storage condition group
 *
 * \return        Internal counter of storage condition group
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_StorageCondition_GetStorageConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  StorageConditionGroup
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_SetStorageConditionGroupCounter
 *****************************************************************************/
/*!
 * \brief         Set current internal counter of storage condition group
 *
 * \details       Set current internal counter of storage condition group
 *
 * \param[in]     StorageConditionGroup
 *                Unique handle of the storage condition group
 * \param[in]     Counter
 *                New internal counter of the storage condition group
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_SetStorageConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  StorageConditionGroup,
  CONST(uint8, AUTOMATIC)  Counter
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GetEventStorageConditionGroup
 *****************************************************************************/
/*!
 * \brief         Get the storage condition group for an event
 *
 * \details       Get the storage condition group for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [1..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        Storage condition group for the event
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_StorageCondition_GetEventStorageConditionGroup(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GetStorageConditionInitValue
*****************************************************************************/
/*!
 * \brief         Get the initial value of storage condition
 *
 * \details       Get the initial value of storage condition
 *
 * \param[in]     StorageCondition
 *                Unique handle of the storage condition.
 *
 * \return        The initial value of storage condition
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_StorageCondition_GetStorageConditionInitValue(
  CONST(uint8, AUTOMATIC)  StorageCondition
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GroupIterExists
 *****************************************************************************/
/*!
 * \brief         Test if the iterator points to a valid element
 *
 * \details       Test if the iterator points to a valid element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        TRUE
 *                Dem_StorageCondition_GroupIterGet() will return a valid element
 *                on this iterator
 * \return        FALSE
 *                Dem_StorageCondition_GroupIterGet() is undefined on this iterator
 *
 * \pre           IterPtr has been initialized
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_GroupIterExists(
  CONSTP2CONST(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GroupIterGet
 *****************************************************************************/
/*!
 * \brief         Get the element pointed to by the iterator
 *
 * \details       Get the element pointed to by the iterator
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \return        Handle to Storage condition group descriptor table
 *
 * \pre           IterPtr has been initialized
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_StorageCondition_GroupIterGet(
  CONSTP2CONST(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GroupIterInit
*****************************************************************************/
/*!
 * \brief         Init the iterator
 *
 * \details       Initializes the iterator to enumerate storage condition groups
 *                referencing given storage condition
 *
 * \param[in]     StorageCondition
 *                Unique handle of the storage condition.
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_GroupIterInit(
  CONST(uint8, AUTOMATIC) StorageCondition,
  CONSTP2VAR(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_GroupIterNext
*****************************************************************************/
/*!
 * \brief         Move the iterator to the next element
 *
 * \details       Move the iterator to the next element
 *
 * \param[in]     IterPtr
 *                Pointer to the iterator
 *
 * \pre           IterPtr has been initialized
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_GroupIterNext(
  CONSTP2VAR(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

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
 * \defgroup Dem_StorageCondition_Public Public Methods
 * \{
 */

/* ****************************************************************************
 * Dem_StorageCondition_PreInit
 *****************************************************************************/
/*!
 * \brief         Enables all storage conditions
 *
 * \details       Enables all storage conditions and set all storage condition 
 *                groups active
 *
 * \pre           May only be called during Dem preinitialization
 * \config        -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_PreInit(
  void
  ); 

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_Init
 *****************************************************************************/
/*!
 * \brief         Initializes the storage conditions and storage condition groups
 *
 * \details       Initializes the storage conditions and storage condition groups
 *
 * \pre           May only be called during Dem initialization
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_Init(
  void
  );
#endif

/* ****************************************************************************
 * Dem_StorageCondition_TestEventStorageConditionsFulfilled
 *****************************************************************************/
/*!
 * \brief         Tests whether the storage conditions are fulfilled for an event
 *
 * \details       Tests whether the storage conditions are fulfilled for an event
 *
 * \param[in]     EventId
 *                Unique handle of the Event.
 *                The EventId must be in range [0..Dem_Cfg_GlobalEventCount()[.
 *
 * \return        TRUE
 *                The storage conditions are fulfilled
 * \return        FALSE
 *                The storage conditions are not fulfilled
 *
 * \pre           -
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_TestEventStorageConditionsFulfilled(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  );

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_SetStorageConditionFulfilled
 *****************************************************************************/
/*!
 * \brief         Sets the storage condition
 *
 * \details       Sets the storage condition
 *
 * \param[in]     StorageCondition
 *                Unique handle of the storage condition.
 *                The StorageCondition must be in range [1..Dem_StorageCondition_GetGlobalStorageConditionCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_SetStorageConditionFulfilled(
  CONST(uint8, AUTOMATIC)  StorageCondition
  );                                                                                                                             /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 * Dem_StorageCondition_ResetStorageConditionFulfilled
 *****************************************************************************/
/*!
 * \brief         Clears the storage condition
 *
 * \details       Clears the storage condition
 *
 * \param[in]     StorageCondition
 *                Unique handle of the storage condition.
 *                The StorageCondition must be in range [1..Dem_StorageCondition_GetGlobalStorageConditionCount()[.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_ResetStorageConditionFulfilled(
  CONST(uint8, AUTOMATIC)  StorageCondition
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_STORAGECONDITION_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_StorageCondition_Interface.h
 *********************************************************************************************************************/
