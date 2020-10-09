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
/*! \addtogroup Dem_StorageCondition
 *  \{
 *  \file       Dem_StorageCondition_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Implementation of the StorageCondition subcomponent
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

#if !defined (DEM_STORAGECONDITION_IMPLEMENTATION_H)
#define DEM_STORAGECONDITION_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_StorageCondition_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg_Definitions.h"
#include "Dem_Error_Implementation.h"
#include "Dem_MemCopy.h"

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_StorageCondition_Properties
 * \{
 */

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GetGlobalStorageConditionCount
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_StorageCondition_GetGlobalStorageConditionCount(
  void
  )
{
  return DEM_CFG_GLOBAL_STORAGE_COND_COUNT;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_StorageCondition_Private
 * \{
 */

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GetStorageConditionActive
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_GetStorageConditionActive(
  CONST(uint8, AUTOMATIC)  StorageCondition
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageCondition)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return Dem_Cfg_GetStorageConditionState(StorageCondition);
# else
  return TRUE;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_SetStorageConditionActive
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_SetStorageConditionActive(
  CONST(uint8, AUTOMATIC)  StorageCondition,
  CONST(boolean, AUTOMATIC)  ActiveStatus
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(ActiveStatus)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageCondition)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
#  if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (StorageCondition >= Dem_Cfg_GetSizeOfStorageConditionState())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#  endif
  {
    Dem_Cfg_SetStorageConditionState(StorageCondition, ActiveStatus);                                                            /* SBSW_DEM_ARRAY_WRITE_STORAGECONDITIONSTATE */
  }
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GetStorageConditionGroupCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_StorageCondition_GetStorageConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  StorageConditionGroup
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageConditionGroup)                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return Dem_Cfg_GetStorageConditionGroupCounter(StorageConditionGroup);
# else
  return 0;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_SetStorageConditionGroupCounter
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_SetStorageConditionGroupCounter(
  CONST(uint16, AUTOMATIC)  StorageConditionGroup,
  CONST(uint8, AUTOMATIC)  Counter
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageConditionGroup)                                                                        /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(Counter)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
#  if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (StorageConditionGroup >= Dem_Cfg_GetSizeOfStorageConditionGroupCounter())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#  endif
  {
    Dem_Cfg_SetStorageConditionGroupCounter(StorageConditionGroup, Counter);                                                     /* SBSW_DEM_ARRAY_WRITE_STORAGECONDITIONGROUPCOUNTER */
  }
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GetEventStorageConditionGroup
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_StorageCondition_GetEventStorageConditionGroup(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return Dem_Cfg_GetStorageConditionGroupTableIdxOfEventTable(EventId);
# else
  return DEM_STORAGECONDITION_NO_STORAGE_CONDITION_GROUP;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GetStorageConditionInitValue
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_StorageCondition_GetStorageConditionInitValue(
  CONST(uint8, AUTOMATIC) StorageCondition
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageCondition)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return Dem_Cfg_GetInitValueOfStorageConditionInitTable(StorageCondition);
# else
  return TRUE;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GroupIterExists
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_GroupIterExists(
  CONSTP2CONST(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                            /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return (boolean)(IterPtr->mIdx < IterPtr->mEndIdx);
# else
  return FALSE;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GroupIterGet
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_StorageCondition_GroupIterGet(
  CONSTP2CONST(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                            /* PRQA S 3206 */ /* MD_DEM_3206 */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  return Dem_Cfg_GetStorageConditionGroupTableInd(IterPtr->mIdx);
# else
  return 0;
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GroupIterInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_GroupIterInit(
  CONST(uint8, AUTOMATIC)  StorageCondition,                                                                                     /* PRQA S 3206 */ /* MD_DEM_3206 */
  CONSTP2VAR(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                              /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_False */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(StorageCondition)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  IterPtr->mIdx = Dem_Cfg_GetStorageConditionGroupTableIndStartIdxOfStorageConditionTable(StorageCondition);                     /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
  IterPtr->mEndIdx = Dem_Cfg_GetStorageConditionGroupTableIndEndIdxOfStorageConditionTable(StorageCondition);                    /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# endif
}
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_GroupIterNext
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_GroupIterNext(
  CONSTP2VAR(Dem_StorageCondition_EventStorageConditionGroupIterType, AUTOMATIC, AUTOMATIC) IterPtr                              /* PRQA S 3206, 3673 */ /* MD_DEM_3206, MD_DEM_16.7_False */
  )
{
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(IterPtr)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  IterPtr->mIdx += 1;                                                                                                            /* SBSW_DEM_POINTER_WRITE_ARGUMENT */
# endif
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_StorageCondition_Public
 * \{
 */

/* ****************************************************************************
 % Dem_StorageCondition_PreInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_PreInit(
  void
  )
{
#if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetStorageConditionState(0),                                                              /* PRQA S 0310, 0312, 0602, 3109 */ /* MD_DEM_11.4_cpy, MD_DEM_11.5, MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_MEMSET_STORAGECONDITIONSTATE */
             TRUE,
             Dem_Cfg_GetSizeOfStorageConditionState()*sizeof(Dem_Cfg_GetStorageConditionState(0)));

  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetStorageConditionGroupCounter(0),                                                       /* PRQA S 0310, 0312, 0602, 3109 */ /* MD_DEM_11.4_cpy, MD_DEM_11.5, MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_MEMSET_STORAGECONDITIONGROUPCOUNTER */
             0,
             Dem_Cfg_GetSizeOfStorageConditionGroupCounter()*sizeof(Dem_Cfg_GetStorageConditionGroupCounter(0)));
#endif
}

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_Init
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_Init(
  void
  )
{
  uint8 lStorageCondition;
  /* Initialize storage condition group counter */
# if (DEM_CFG_HAS_STORAGE_CONDITIONS == STD_ON)
  Dem_MemSet((Dem_DataPtrType)&Dem_Cfg_GetStorageConditionGroupCounter(0),                                                       /* PRQA S 0310, 0312, 0602, 3109 */ /* MD_DEM_11.4_cpy, MD_DEM_11.5, MD_DEM_20.2, MD_MSR_14.3 */ /* SBSW_DEM_MEMSET_STORAGECONDITIONGROUPCOUNTER */
    0,
    Dem_Cfg_GetSizeOfStorageConditionGroupCounter()*sizeof(Dem_Cfg_GetStorageConditionGroupCounter(0)));
# endif

  for (lStorageCondition = 0; lStorageCondition < Dem_StorageCondition_GetGlobalStorageConditionCount(); ++lStorageCondition)
  {
    uint8 lStorageConditionInitState;
    Dem_StorageCondition_EventStorageConditionGroupIterType lStorageConditionIter;

    lStorageConditionInitState = Dem_StorageCondition_GetStorageConditionInitValue(lStorageCondition);

    if (lStorageConditionInitState == FALSE)
    {
      for (Dem_StorageCondition_GroupIterInit(lStorageCondition, &lStorageConditionIter);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_StorageCondition_GroupIterExists(&lStorageConditionIter) == TRUE;                                                    /* SBSW_DEM_CALL_ITERATOR_POINTER */
        Dem_StorageCondition_GroupIterNext(&lStorageConditionIter))                                                              /* SBSW_DEM_CALL_ITERATOR_POINTER */
      {
        uint16 lStorageConditionGroup;

        lStorageConditionGroup = Dem_StorageCondition_GroupIterGet(&lStorageConditionIter);                                      /* SBSW_DEM_CALL_ITERATOR_POINTER */

        Dem_StorageCondition_SetStorageConditionGroupCounter(lStorageConditionGroup, 
          (uint8)(Dem_StorageCondition_GetStorageConditionGroupCounter(lStorageConditionGroup) + 1));
      }
    }
    Dem_StorageCondition_SetStorageConditionActive(lStorageCondition, lStorageConditionInitState);
  }
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/* ****************************************************************************
 % Dem_StorageCondition_TestEventStorageConditionsFulfilled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_StorageCondition_TestEventStorageConditionsFulfilled(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
  boolean lStorageConditionsSatisfied;
  uint16 lStorageConditionGroup;

  lStorageConditionGroup = Dem_StorageCondition_GetEventStorageConditionGroup(EventId);
  if (lStorageConditionGroup != DEM_STORAGECONDITION_NO_STORAGE_CONDITION_GROUP)
  {
    if (Dem_StorageCondition_GetStorageConditionGroupCounter(lStorageConditionGroup) > 0)
    {
      lStorageConditionsSatisfied = FALSE;
    }
    else
    {
      lStorageConditionsSatisfied = TRUE;
    }
  }
  else
  {
    lStorageConditionsSatisfied = TRUE;
  }

  return lStorageConditionsSatisfied;
#else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(EventId)                                                                                      /* PRQA S 3112 */ /* MD_DEM_14.2 */
  return TRUE;
#endif
}

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_SetStorageConditionFulfilled
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_SetStorageConditionFulfilled(
  CONST(uint8, AUTOMATIC)  StorageCondition
  )
{
/* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */

  if (Dem_StorageCondition_GetStorageConditionActive(StorageCondition) == FALSE)
  {
    Dem_StorageCondition_EventStorageConditionGroupIterType lStorageConditionIter;
    for (Dem_StorageCondition_GroupIterInit(StorageCondition, &lStorageConditionIter);                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_StorageCondition_GroupIterExists(&lStorageConditionIter) == TRUE;                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_StorageCondition_GroupIterNext(&lStorageConditionIter))                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint16 lStorageConditionGroup;

      lStorageConditionGroup = Dem_StorageCondition_GroupIterGet(&lStorageConditionIter);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
      if (Dem_StorageCondition_GetStorageConditionGroupCounter(lStorageConditionGroup) > 0)
# endif
      {
        Dem_StorageCondition_SetStorageConditionGroupCounter(lStorageConditionGroup,
          (uint8)(Dem_StorageCondition_GetStorageConditionGroupCounter(lStorageConditionGroup) - 1));
      }
    }
    Dem_StorageCondition_SetStorageConditionActive(StorageCondition, TRUE);
  }

  Dem_LeaveCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: StateManager */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_STORAGE_CONDITIONS == STD_ON)
/* ****************************************************************************
 % Dem_StorageCondition_ResetStorageConditionFulfilled
  *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_StorageCondition_ResetStorageConditionFulfilled(
  CONST(uint8, AUTOMATIC)  StorageCondition
  )
{
/* >>>> -------------------------------- Enter Critical Section: StateManager */
  Dem_EnterCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */

  if (Dem_StorageCondition_GetStorageConditionActive(StorageCondition) == TRUE)
  {
    Dem_StorageCondition_EventStorageConditionGroupIterType lStorageConditionIter;
    for (Dem_StorageCondition_GroupIterInit(StorageCondition, &lStorageConditionIter);                                           /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_StorageCondition_GroupIterExists(&lStorageConditionIter) == TRUE;                                                   /* SBSW_DEM_CALL_ITERATOR_POINTER */
         Dem_StorageCondition_GroupIterNext(&lStorageConditionIter))                                                             /* SBSW_DEM_CALL_ITERATOR_POINTER */
    {
      uint16 lStorageConditionGroup;

      lStorageConditionGroup = Dem_StorageCondition_GroupIterGet(&lStorageConditionIter);                                        /* SBSW_DEM_CALL_ITERATOR_POINTER */
      Dem_StorageCondition_SetStorageConditionGroupCounter(lStorageConditionGroup,
        (uint8)(Dem_StorageCondition_GetStorageConditionGroupCounter(lStorageConditionGroup) + 1));
    }
    Dem_StorageCondition_SetStorageConditionActive(StorageCondition, FALSE);
  }

  Dem_LeaveCritical_StateManager();                                                                                              /* PRQA S 3109 */ /* MD_MSR_14.3 */
/* <<<< -------------------------------- Leave Critical Section: StateManager */
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#endif /* DEM_STORAGECONDITION_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_StorageCondition_Implementation.h
 *********************************************************************************************************************/
