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
/*! \addtogroup Dem_MemPermanent
 *  \{
 *  \file       Dem_MemPermanent_Implementation.h
 *  \brief      Diagnostic Event Manager (Dem) header file.
 *  \details    Implementation of the Permanent Memory subcomponent which manages storage of permanent DTCs.
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
 *  Friederike Schulze            visfrs        Vector Informatik GmbH
 *  Aswin Vijayamohanan Nair      visavi        Vector Informatik GmbH
 *  Fabian Wild                   viszfa        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_MEMPERMANENT_IMPLEMENTATION_H)
#define DEM_MEMPERMANENT_IMPLEMENTATION_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_MemPermanent_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_Data_Interface.h"
#include "Dem_MemState_Implementation.h"
#include "Dem_Event_Interface.h"
#include "Dem_EventInternalStatus_Interface.h"
#include "Dem_Nvm_Implementation.h"
#include "Dem_DTC_Interface.h"
#include "Dem_UDSStatus_Implementation.h"

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
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/
#define DEM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/*! Number of stored entries in confirmed chronology */
DEM_LOCAL VAR(boolean, DEM_VAR_NOINIT)                    Dem_MemPermanent_ConfirmedChronoOverflow;                              /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#define DEM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


#define DEM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/*! Number of stored entries in confirmed chronology */
DEM_LOCAL VAR(uint16, DEM_VAR_NOINIT)                    Dem_MemPermanent_ConfirmedChronoCurrentCount;                           /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
#endif

#define DEM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*!
 * \addtogroup Dem_MemPermanent_Properties
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyGetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(Dem_EventIdType, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyGetEventId(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex
  )
{
  return Dem_Cfg_GetStatusData().ConfirmedChronology[ConfirmedChronologyIndex];
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologySetEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetEventId(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex,
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
# if (DEM_DEV_RUNTIME_CHECKS == STD_ON)
  if (ConfirmedChronologyIndex >= Dem_Cfg_ConfirmedChronologyMaxCount())
  {
    Dem_Error_RunTimeCheckFailed(__FILE__, __LINE__);                                                                            /* SBSW_DEM_POINTER_RUNTIME_CHECK */
  }
  else
# endif
  {
    Dem_Cfg_GetStatusData().ConfirmedChronology[ConfirmedChronologyIndex] = EventId;                                                  /* SBSW_DEM_ARRAY_WRITE_STATUSDATA_CONFIRMEDCHRONOLOGY */
  }
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologySetOverflown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetOverflown( 
  void
  )
{
  Dem_MemPermanent_ConfirmedChronoOverflow = TRUE;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyResetOverflown
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyResetOverflown(
  void
  )
{
  Dem_MemPermanent_ConfirmedChronoOverflow = FALSE;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyGetCurrentSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(uint16, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyGetCurrentSize(void)
{
  return Dem_MemPermanent_ConfirmedChronoCurrentCount;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologySetCurrentSize
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologySetCurrentSize(
  CONST(uint16, AUTOMATIC)  Size
  )
{
  Dem_MemPermanent_ConfirmedChronoCurrentCount = Size;
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
 * \addtogroup Dem_MemPermanent_Private
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_PermanentFillUpAddEvent
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
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_PermanentFillUpAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;
  uint8 lPermanentIndex;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);


  lPermanentIndex = Dem_Data_PermanentEntryFind(EventId);
  if (Dem_MemState_MemoryGetMaxSize(lMemoryInfo) == lPermanentIndex)                                                             /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  {
    uint8 lPermanentState;
    uint8 lQualifyState;

    lPermanentIndex = Dem_Data_PermanentEntryFind(DEM_EVENT_INVALID);
    lPermanentState = DEM_ESM_PERMANENT_NONE;
    lQualifyState = Dem_Event_GetQualifyStatus(EventId);

    Dem_Mem_PermanentSetEvent(lPermanentIndex, EventId);
    lPermanentState = DEM_ESM_SET_PERMANENT_STATE(lPermanentState, DEM_ESM_PERMANENT_ACTIVE);

    /* Only a qualified WIR is immediately visible */
    if (Dem_EventInternalStatus_Test_QualifyStatus_WIR(lQualifyState) == TRUE)
    {
      lPermanentState = DEM_ESM_SET_PERMANENT_VISIBLE(lPermanentState);
    }

    Dem_MemState_MemorySetCurrentSize(lMemoryInfo, Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) + 1);                          /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
    Dem_Mem_PermanentSetStatus(lPermanentIndex, lPermanentState);
    Dem_Nvm_SetSingleBlockState(Dem_Nvm_GetSingleBlockId(DEM_NVM_BLOCKTYPE_PERMANENT),
      DEM_NVM_BLOCKSTATE_DIRTYIMMEDIATE);
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif 

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_PermanentFillUpFromPrimary
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
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_PermanentFillUpFromPrimary(
  void
  )
{
  Dem_EventIdType lEventId;
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);

  /* scan for events which support the MIL. */
  for (lEventId = Dem_MemState_MemoryGetFirstEvent(lMemoryInfo);                                                                 /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* PRQA S 3415 */ /* MD_DEM_12.4_cf */
       (lEventId <= Dem_MemState_MemoryGetLastEvent(lMemoryInfo));                                                               /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
       ++lEventId)
  {
# if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
    /* Only process master events (subevents are handled with the master) */
    if (Dem_Cfg_GetMasterEvent(lEventId) != lEventId)
    {
      continue;                                                                                                                  /* PRQA S 0770 */ /* MD_DEM_14.5 */
    }
# endif

    if (Dem_Event_TestMilSupport(lEventId) == TRUE)
    {
      if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() < Dem_Cfg_ConfirmedChronologyMaxCount())
      {
        if (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(lEventId)) == TRUE)
        { /* Confirmed event found */
          Dem_MemPermanent_ConfirmedChronoAddEvent(lEventId, TRUE);
        }
      }
      else
      {
        if (Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) >= Dem_MemState_MemoryGetMaxSize(lMemoryInfo))                        /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
        {
          /*Confirmed chronology and permanent memory are full*/
          break;                                                                                                                 /* PRQA S 0771 */ /* MD_DEM_14.6_opt */
        }
      }

      if (Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) < Dem_MemState_MemoryGetMaxSize(lMemoryInfo))                           /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
      {
        if (Dem_UDSStatus_Test_WIR(Dem_DTC_GetDTCStatus(lEventId)) == TRUE)
        {
          Dem_MemPermanent_PermanentFillUpAddEvent(lEventId);
        }
      }
      else
      {
        if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() >= Dem_Cfg_ConfirmedChronologyMaxCount())
        {
          /*Confirmed chronology and permanent memory are full*/
          break;                                                                                                                 /* PRQA S 0771 */ /* MD_DEM_14.6_opt */
        }
      }
    }
  }
  if (lEventId >  Dem_MemState_MemoryGetLastEvent(lMemoryInfo))                                                                  /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  {
    /*All primary events have been evaluated*/
    if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() < Dem_Cfg_ConfirmedChronologyMaxCount())
    {
      /* Chronology has still empty entries - remember confirmed chronology is not overflown*/
      Dem_MemPermanent_ConfirmedChronologyResetOverflown();
    }
  }
}                                                                                                                                /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#endif 

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyEventStored
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyEventStored(
  CONST(Dem_EventIdType, AUTOMATIC)  Event
  )
{
  boolean lEventStored;
  uint16 lChronoIndex;
  lChronoIndex = 0;
  lEventStored = FALSE;
  while (lChronoIndex < Dem_MemPermanent_ConfirmedChronologyGetCurrentSize())
  {
    if (Event == Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIndex))
    {
      lEventStored = TRUE;
      break;
    }
    lChronoIndex++;
  }
  return lEventStored;
}
#endif 

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_PermanentFillUpFromConfirmedChronology
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
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_MemPermanent_PermanentFillUpFromConfirmedChronology(void)
{
  Std_ReturnType lReturnValue;
  uint16 lChronoIndex;
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);
  lChronoIndex = 0;
  lReturnValue = E_NOT_OK;

  while (lChronoIndex < Dem_MemPermanent_ConfirmedChronologyGetCurrentSize())
  {
    Dem_EventIdType lEventCandidate;
    lEventCandidate = Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIndex);

    if (Dem_UDSStatus_Test_WIR(Dem_DTC_GetDTCStatus(lEventCandidate)) == TRUE)
    {
      Dem_MemPermanent_PermanentFillUpAddEvent(lEventCandidate);

      if (Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) >= Dem_MemState_MemoryGetMaxSize(lMemoryInfo))                          /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
      {
        /* Permanent memory is completely filled up */
        lReturnValue = E_OK;
        break;
      }
    }
    lChronoIndex++;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif 

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronoFreeEntry
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoFreeEntry(
  CONST(uint16, AUTOMATIC)  ConfirmedChronologyIndex
  )
{
  Dem_EventIdType lTempEventId;
  uint16 lChronoIterator;

  Dem_Internal_AssertReturnVoid(ConfirmedChronologyIndex < Dem_MemPermanent_ConfirmedChronologyGetCurrentSize(), 
    DEM_E_INCONSISTENT_STATE)

  lChronoIterator = Dem_MemPermanent_ConfirmedChronologyGetCurrentSize();
  --lChronoIterator;
  Dem_MemPermanent_ConfirmedChronologySetCurrentSize(lChronoIterator);

  lTempEventId = Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIterator);
  Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIterator, DEM_EVENT_INVALID);
  while (lChronoIterator != ConfirmedChronologyIndex)
  {
    /* go backwards through the chronological list and move down all entries, until the entry to delete is overwritten */
    Dem_EventIdType lSwap;

    lSwap = lTempEventId;

    --lChronoIterator;
    lTempEventId = Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIterator);
    Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIterator, lSwap);
    Dem_Nvm_SetStatusBlockChanged();
  }
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
 * \addtogroup Dem_MemPermanent_Public
 * \{
 */
#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyInit
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyInit(
  void
  )
{
  uint16 lConfirmedChronologyIndex;
  lConfirmedChronologyIndex = Dem_Cfg_ConfirmedChronologyMaxCount();
  while (lConfirmedChronologyIndex != 0)
  {
    lConfirmedChronologyIndex--;
    Dem_MemPermanent_ConfirmedChronologySetEventId(lConfirmedChronologyIndex, DEM_EVENT_INVALID);
  }
  /* Initiliaze with worst case sceanrio */
  Dem_MemPermanent_ConfirmedChronoOverflow = FALSE;
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronologyRestore
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
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronologyRestore(void)
{
  uint16 lConfirmedChronoIndex;
  Dem_EventIdType lEventId;
  Dem_MemState_MemoryInfoPtrType lMemoryInfo; 

  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);

  /*Initialize current size of chronology*/
  Dem_MemPermanent_ConfirmedChronologySetCurrentSize(0);
  

  /*Start at the end of the chronology array*/
  lConfirmedChronoIndex = Dem_Cfg_ConfirmedChronologyMaxCount();
  while (lConfirmedChronoIndex != 0)
  {
    --lConfirmedChronoIndex;
    lEventId = Dem_MemPermanent_ConfirmedChronologyGetEventId(lConfirmedChronoIndex);

    if (lEventId != DEM_EVENT_INVALID)
    {
      if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() == 0)
      {
        Dem_MemPermanent_ConfirmedChronologySetCurrentSize(lConfirmedChronoIndex + 1);
      }

      if ( (Dem_Cfg_GetMasterEvent(lEventId) != lEventId)                                                                         /* PRQA S 3415 */ /* MD_DEM_12.4_cf */ /* COV_DEM_GENERATED_EVENTID */
        || (lMemoryInfo->FirstEvent > lEventId)
        || (lMemoryInfo->LastEvent < lEventId) )
      {
        /*The configuration has changed somehow, event no longer belongs to primary memory - remove entry */
        Dem_MemPermanent_ConfirmedChronoFreeEntry(lConfirmedChronoIndex);
      }
      else
      {
        if (Dem_UDSStatus_Test_CDTC(Dem_DTC_GetDTCStatus(lEventId)) == FALSE)
        {
          /*Confirmed bit no longer set - remove entry */
          Dem_MemPermanent_ConfirmedChronoFreeEntry(lConfirmedChronoIndex);
        }
      }
    }
    else
    {
      if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() != 0)
      {
        /*There is an empty entry in the chronology although we already found a newer event -> fix chronology by clear of this entry*/
        Dem_MemPermanent_ConfirmedChronoFreeEntry(lConfirmedChronoIndex);
      }
    }
  } /*End while*/
}                                                                                                                                /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronoFreeEvent
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
 *
 */
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoFreeEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId
  )
{
  Dem_EventIdType lTempEventId;
  Dem_EventIdType lSwap;
  uint16 lChronoIterator;
  boolean lEventFound;
  lEventFound = FALSE;

  lChronoIterator = 0;
  lTempEventId = Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIterator);

  if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() > 1)
  {
    /* Go forwards through the chronological list and search for the event to free.
    If found shift all entries one entry backwards beginning at the entry to free  */
    do
    {
      lSwap = Dem_MemPermanent_ConfirmedChronologyGetEventId(lChronoIterator + 1);
      if ((lTempEventId == EventId) || (lEventFound == TRUE))
      {
        lEventFound = TRUE;
        Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIterator, lSwap);
      }
      lTempEventId = lSwap;
      ++lChronoIterator;
    }
    while (lChronoIterator < (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() -1));
    
    if ((lSwap == EventId) || (lEventFound == TRUE))
    {
      /* Free last entry */
      Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIterator, DEM_EVENT_INVALID);
      if (lEventFound == FALSE)
      {
        lEventFound = TRUE;
      }
    }
  }
  else
  {
    if (lTempEventId == EventId)
    {
     /* Just free the one existing entry */
      lEventFound = TRUE;
      Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIterator, DEM_EVENT_INVALID);
    }
  }

  if (lEventFound == TRUE)
  {
    if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() > 0)
    {
      Dem_MemPermanent_ConfirmedChronologySetCurrentSize(Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() - 1);
    }
    else
    {
      Dem_Internal_AssertAlways(DEM_E_INCONSISTENT_STATE);                                                                       /* PRQA S 3112 */ /* MD_DEM_14.2 */
    }
  }

}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_ConfirmedChronoAddEvent
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
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_MemPermanent_ConfirmedChronoAddEvent(
  CONST(Dem_EventIdType, AUTOMATIC)  ConfirmedEvent,
  CONST(boolean, AUTOMATIC) SearchExistingEvent
  )
{
  uint16 lChronoIndex;
  boolean lEventStored;

  lEventStored = FALSE;
  if (SearchExistingEvent == TRUE)
  {
    lEventStored = Dem_MemPermanent_ConfirmedChronologyEventStored(ConfirmedEvent);
  }

  if (lEventStored == FALSE)
  {
    lChronoIndex = Dem_MemPermanent_ConfirmedChronologyGetCurrentSize();
    if (Dem_MemPermanent_ConfirmedChronologyGetCurrentSize() < Dem_Cfg_ConfirmedChronologyMaxCount())
    {
      Dem_MemPermanent_ConfirmedChronologySetCurrentSize(lChronoIndex + 1);
      Dem_MemPermanent_ConfirmedChronologySetEventId(lChronoIndex, ConfirmedEvent);
      Dem_Nvm_SetStatusBlockChanged();
    }
    else
    {
      /*Confirmed chronology overflow -> Configuration error: Size of confirmed chronology is too small*/
      Dem_MemPermanent_ConfirmedChronoOverflow = TRUE;
    }
  }
}
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* ****************************************************************************
 % Dem_MemPermanent_FillUp
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
Dem_MemPermanent_FillUp(
  void
  )
{
  Dem_MemState_MemoryInfoPtrType lMemoryInfo;
  Std_ReturnType lReturnValue;
  lMemoryInfo = Dem_MemState_MemoryInfoInit(DEM_CFG_MEMORYID_PERMANENT);

  if (Dem_MemState_MemoryGetCurrentSize(lMemoryInfo) < Dem_MemState_MemoryGetMaxSize(lMemoryInfo))                               /* SBSW_DEM_CALL_MEMORYINFO_POINTER */ /* SBSW_DEM_CALL_MEMORYINFO_POINTER */
  {
    lReturnValue = Dem_MemPermanent_PermanentFillUpFromConfirmedChronology();

    if ((lReturnValue == E_NOT_OK) && (Dem_MemPermanent_ConfirmedChronoOverflow == TRUE))
    {
      Dem_MemPermanent_PermanentFillUpFromPrimary();
    }
  }
}                                                                                                                                /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
#endif 
/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* DEM_MEMPERMANENT_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_MemPermanent_Implementation.h
 *********************************************************************************************************************/
