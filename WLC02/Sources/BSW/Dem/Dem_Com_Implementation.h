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
/*! \addtogroup Dem_Communication
 *  \{
 *  \file       Dem_Com_Implementation.h
 *  \brief      Implementation file for the MICROSAR Dem
 *  \details    Implementation of communication subcomponent
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

#if !defined (DEM_COM_IMPLEMENTATION_H)
#define DEM_COM_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Com_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */

                                                   /* Subcomponents callbacks*/
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"

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
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \addtogroup Dem_Communication_Private
 * \{
 */

/* ****************************************************************************
 % Dem_Com_GetBitfieldWordIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Dem_HandleType, DEM_CODE)
Dem_Com_GetBitfieldWordIndex(
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  Dem_HandleType lReturnValue;

  lReturnValue = (Dem_HandleType)(BitPosition / DEM_COM_BITS_PER_WORD);

  return lReturnValue;
}

/* ****************************************************************************
 % Dem_Com_GetBitfieldBitIndex
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(uint8, DEM_CODE)
Dem_Com_GetBitfieldBitIndex(
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  uint8 lReturnValue;

  lReturnValue = (uint8)(BitPosition % DEM_COM_BITS_PER_WORD);

  return lReturnValue;
}

#if (DEM_CFG_SUPPORT_USER_CAS == STD_OFF)
/* ****************************************************************************
 % Dem_Com_DefaultSyncCompareAndSwap
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Com_DefaultSyncCompareAndSwap(
 volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) AddressPtr,
 CONST(Dem_Com_ProcessorWordType, AUTOMATIC) OldValue,
 CONST(Dem_Com_ProcessorWordType, AUTOMATIC) NewValue
 )
{
  boolean lReturnValue;

/* >>>> -------------------------------- Enter Critical Section: CrossCoreComm */
  Dem_EnterCritical_CrossCoreComm();

  if (*AddressPtr == OldValue)
  {
    *AddressPtr = NewValue;                                                                                                      /* SBSW_DEM_POINTER_WRITE_ARGUMENT */                                                                                           
    lReturnValue = TRUE;
  }
  else
  {
    lReturnValue = FALSE;
  }

  Dem_LeaveCritical_CrossCoreComm();
/* <<<< -------------------------------- Leave Critical Section: CrossCoreComm */

  return lReturnValue;
}
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_Communication_Public
 * \{
 */

/* ****************************************************************************
 % Dem_Com_SyncCompareAndSwap
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Com_SyncCompareAndSwap(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) AddressPtr,
  CONST(Dem_Com_ProcessorWordType, AUTOMATIC) OldValue,
  CONST(Dem_Com_ProcessorWordType, AUTOMATIC) NewValue
  )
{
#if (DEM_CFG_SUPPORT_USER_CAS == STD_ON)
  return ApplDem_SyncCompareAndSwap(AddressPtr, OldValue, NewValue);                                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#else
  return Dem_Com_DefaultSyncCompareAndSwap(AddressPtr, OldValue, NewValue);                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
#endif
}

/* ****************************************************************************
 % Dem_Com_TestBitInBitfield
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_Com_TestBitInBitfield(                                                                                                       /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  volatile CONSTP2CONST(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  Dem_Com_ProcessorWordType lBitMask;
  boolean lIsBitSet;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BitfieldSize)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */

  Dem_Internal_AssertReturnValue(Dem_Com_GetBitfieldWordIndex(BitPosition) < BitfieldSize, DEM_E_INCONSISTENT_STATE, TRUE)

  lBitMask = DEM_BIT(Dem_Com_GetBitfieldBitIndex(BitPosition));
  lIsBitSet = (boolean)((BitfieldPtr[Dem_Com_GetBitfieldWordIndex(BitPosition)] & lBitMask) != 0);

  return lIsBitSet;
}

/* ****************************************************************************
 % Dem_Com_SyncSetBitInBitfield
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_SyncSetBitInBitfield(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  volatile P2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) lWordPtr;
  Dem_Com_ProcessorWordType lOldValue;
  Dem_Com_ProcessorWordType lNewValue;
  Dem_Com_ProcessorWordType lBitMask;
  Dem_HandleType lWordIndex;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BitfieldSize)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lWordIndex = Dem_Com_GetBitfieldWordIndex(BitPosition);

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lWordIndex >= BitfieldSize)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    lWordPtr = &BitfieldPtr[lWordIndex];
    lBitMask = DEM_BIT(Dem_Com_GetBitfieldBitIndex(BitPosition));
    do
    {
      lOldValue = *lWordPtr;
      lNewValue = (lOldValue | lBitMask);
    }
    while (Dem_Com_SyncCompareAndSwap(lWordPtr, lOldValue, lNewValue) == FALSE);                                                 /* SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP */
  }
}

/* ****************************************************************************
 % Dem_Com_SyncResetBitInBitfield
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_SyncResetBitInBitfield(
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  volatile P2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) lWordPtr;
  Dem_Com_ProcessorWordType lOldValue;
  Dem_Com_ProcessorWordType lNewValue;
  Dem_Com_ProcessorWordType lBitMask;
  Dem_HandleType lWordIndex;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BitfieldSize)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */

  lWordIndex = Dem_Com_GetBitfieldWordIndex(BitPosition);

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lWordIndex >= BitfieldSize)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    lWordPtr = &BitfieldPtr[lWordIndex];
    lBitMask = (Dem_Com_ProcessorWordType) (~(DEM_BIT(Dem_Com_GetBitfieldBitIndex(BitPosition))));
    do
    {
      lOldValue = *lWordPtr;
      lNewValue = (lOldValue & lBitMask);
    } while (Dem_Com_SyncCompareAndSwap(lWordPtr, lOldValue, lNewValue) == FALSE);                                               /* SBSW_DEM_CALL_SYNC_COMPARE_AND_SWAP */
  }
}

/* ****************************************************************************
 % Dem_Com_SetBitInBitfield
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_SetBitInBitfield(                                                                                                        /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  Dem_Com_ProcessorWordType lBitMask;
  Dem_HandleType lWordPosition;
  volatile P2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) lWordPtr;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BitfieldSize)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lWordPosition = Dem_Com_GetBitfieldWordIndex(BitPosition);

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lWordPosition >= BitfieldSize)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    lBitMask = DEM_BIT(Dem_Com_GetBitfieldBitIndex(BitPosition));
    lWordPtr = &BitfieldPtr[lWordPosition];
    *lWordPtr |= lBitMask;                                                                                                       /* SBSW_DEM_POINTER_WRITE_BIT_POSITION */
  }
}

/* ****************************************************************************
 % Dem_Com_ResetBitInBitfield
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_Com_ResetBitInBitfield(                                                                                                      /* PRQA S 3219 */ /* MD_DEM_14.1_ACCESSOR */
  volatile CONSTP2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) BitfieldPtr,
  CONST(Dem_HandleType, AUTOMATIC) BitfieldSize,
  CONST(Dem_HandleType, AUTOMATIC) BitPosition
  )
{
  Dem_Com_ProcessorWordType lBitMask;
  Dem_HandleType lWordPosition;
  volatile P2VAR(Dem_Com_ProcessorWordType, DEM_VAR_UNCACHED, AUTOMATIC) lWordPtr;

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(BitfieldSize)                                                                                 /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lWordPosition = Dem_Com_GetBitfieldWordIndex(BitPosition);

#if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (lWordPosition >= BitfieldSize)
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
#endif
  {
    lBitMask = (Dem_Com_ProcessorWordType) (~(DEM_BIT(Dem_Com_GetBitfieldBitIndex(BitPosition))));
    lWordPtr = &BitfieldPtr[lWordPosition];
    *lWordPtr &= lBitMask;                                                                                                       /* SBSW_DEM_POINTER_WRITE_BIT_POSITION */
  }
}

/*!
 * \}
 */

#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_COM_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Com_Implementation.h
 *********************************************************************************************************************/
