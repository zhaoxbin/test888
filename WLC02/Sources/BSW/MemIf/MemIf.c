/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  MemIf.c
 *        \brief  Memory Interface source file
 *
 *      \details  The Memory Abstraction Interface provides uniform access to services of underlying
 *                Memory Hardware abstraction (MemHwA) modules, i.e. EEPROM Abstraction (EA) and
 *                Flash EEPROM Emulation (FEE). The appropriate MemHwA module is selected by a device index.
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h" /* \trace SPEC-23073 */
#include "MemIf.h"

/**********************************************************************************************************************
 *  VERSION CHECK  \trace SPEC-38543
 *********************************************************************************************************************/

#if ((MEMIF_SW_MAJOR_VERSION != (3U)) \
  || (MEMIF_SW_MINOR_VERSION != (3U)) )
# error "Version numbers of MemIf.c and MemIf.h are inconsistent!"
#endif

#if ((MEMIF_TYPES_SW_MAJOR_VERSION != (3U)) \
  || (MEMIF_TYPES_SW_MINOR_VERSION != (3U)) )
# error "Version numbers of MemIf.c and MemIf_Types.h are inconsistent!"
#endif

#if ((MEMIF_CFG_MAJOR_VERSION != (5U)) \
  || (MEMIF_CFG_MINOR_VERSION != (2U)) )
# error "Version numbers of MemIf.c and MemIf_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (MEMIF_LOCAL) /* COV_MEMIF_COMPATIBILITY */
# define MEMIF_LOCAL static
#endif

#if !defined (MEMIF_LOCAL_INLINE) /* COV_MEMIF_COMPATIBILITY */
# define MEMIF_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define MEMIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  MemIf_DetChkDeviceIndex()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if device index passed to MemIf is in range
 * \details    Checks if device index passed to MemIf is in range
 * \param[in]  DeviceIndex
 * \return     E_OK: DeviceIndex is valid
 * \return     E_NOT_OK: DeviceIndex is out of range
 * \pre        Pre-compile switch MEMIF_DEV_ERROR_DETECT is enabled
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
MEMIF_LOCAL_INLINE FUNC(Std_ReturnType, MEMIF_PRIVATE_CODE) MemIf_DetChkDeviceIndex(uint8 DeviceIndex);
#endif

/**********************************************************************************************************************
 *  MemIf_IsBitSet()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if Status is set in Mask
 * \details    Checks if Status is set in Mask
 * \param[in]  Mask
 * \param[in]  Status
 * \return     E_OK: Status bit is set
 * \return     E_NOT_OK: Status bit is not set
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
MEMIF_LOCAL FUNC(Std_ReturnType, MEMIF_PRIVATE_CODE) MemIf_IsBitSet(uint8 Mask, MemIf_StatusType Status);


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
 *  MemIf_DetChkDeviceIndex()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
MEMIF_LOCAL_INLINE FUNC(Std_ReturnType, MEMIF_PRIVATE_CODE) MemIf_DetChkDeviceIndex(uint8 DeviceIndex)
{
  return (Std_ReturnType) ((DeviceIndex >= MemIf_NumberOfDevices) ? E_NOT_OK : E_OK);
}
#endif

/**********************************************************************************************************************
 *  MemIf_IsBitSet()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
MEMIF_LOCAL FUNC(Std_ReturnType, MEMIF_PRIVATE_CODE) MemIf_IsBitSet(uint8 Mask, MemIf_StatusType Status)
{
  return ((Mask & (1u << (uint8)Status)) > 0) ? E_OK : E_NOT_OK;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  MemIf_Read()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Read(uint8 DeviceIndex, uint16 Blockid,uint16 BlockNumber, uint16 BlockOffset, MemIf_DataPtr_pu8 DataBufferPtr, uint16 Length)
{
  /* ----- Local Variables ------------------------------------------------------------------------------*/
  Std_ReturnType retVal = E_NOT_OK; /* \trace SPEC-38549 */
  uint8 errorId = MEMIF_E_NO_ERROR;

  /* ----- Development Error Detection ------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {
  /* ----- Implementation -------------------------------------------------------------------------------*/
    retVal = MemIf_MemHwaApis[DeviceIndex].Read(Blockid,BlockNumber, BlockOffset, DataBufferPtr, Length); /* SBSW_MEMIF_02 */
  }

  /* ----- Development Error Report ---------------------------------------------------------------------*/
  /* \trace SPEC-38551 */
#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_READ, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId); /* SBSW_MEMIF_03 */ /* PRQA S 3200, 3335 */ /* MD_MSR_14.2 */
#endif

  return retVal;
}


/**********************************************************************************************************************
 *  MemIf_Write()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Write(uint8 DeviceIndex,  uint16 Blockid,uint16 BlockNumber, MemIf_DataPtr_pu8 DataBufferPtr)
{
  /* ----- Local Variables ------------------------------------------------------------------------------*/
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MEMIF_E_NO_ERROR;

  /* ----- Development Error Detection ------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {
  /* ----- Implementation -------------------------------------------------------------------------------*/
    retVal = MemIf_MemHwaApis[DeviceIndex].Write(Blockid,BlockNumber, DataBufferPtr); /* SBSW_MEMIF_02 */
  }

  /* ----- Development Error Report ---------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_WRITE, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId); /* SBSW_MEMIF_03 */ /* PRQA S 3200, 3335 */ /* MD_MSR_14.2 */
#endif

  return retVal;
}


/**********************************************************************************************************************
 *  MemIf_InvalidateBlock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_InvalidateBlock(uint8  DeviceIndex,uint16 Blockid, uint16 BlockNumber)
{
  /* ----- Local Variables ------------------------------------------------------------------------------*/
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MEMIF_E_NO_ERROR;

  /* ----- Development Error Detection ------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {
  /* ----- Implementation -------------------------------------------------------------------------------*/
    retVal = MemIf_MemHwaApis[DeviceIndex].InvalidateBlock(Blockid,BlockNumber); /* SBSW_MEMIF_02 */
  }

  /* ----- Development Error Report ---------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_INVALIDATE, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId); /* SBSW_MEMIF_03 */ /* PRQA S 3200, 3335 */ /* MD_MSR_14.2 */
#endif

  return retVal;
}


/**********************************************************************************************************************
 *  MemIf_EraseImmediateBlock()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_EraseImmediateBlock(uint8  DeviceIndex, uint16 Blockid,uint16 BlockNumber)
{
  /* ----- Local Variables ------------------------------------------------------------------------------*/
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = MEMIF_E_NO_ERROR;

  /* ----- Development Error Detection ------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {
  /* ----- Implementation -------------------------------------------------------------------------------*/
    retVal = MemIf_MemHwaApis[DeviceIndex].EraseImmediateBlock(Blockid,BlockNumber); /* SBSW_MEMIF_02 */
  }

  /* ----- Development Error Report ---------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_ERASE, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId); /* SBSW_MEMIF_03 */ /* PRQA S 3200, 3335 */ /* MD_MSR_14.2 */
#endif

  return retVal;
}


/**********************************************************************************************************************
 *  MemIf_Cancel()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */FUNC(void, MEMIF_CODE) MemIf_Cancel(uint8 DeviceIndex)
{
  /* ----- Local Variables ------------------------------------------------------------------------------*/
  uint8 errorId = MEMIF_E_NO_ERROR;

  /* ----- Development Error Detection ------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {
  /* ----- Implementation -------------------------------------------------------------------------------*/
    MemIf_MemHwaApis[DeviceIndex].Cancel(); /* SBSW_MEMIF_02 */
  }

  /* ----- Development Error Report ---------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_CANCEL, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId); /* SBSW_MEMIF_03 */ /* PRQA S 3200, 3335 */ /* MD_MSR_14.2 */
#endif

}


/**********************************************************************************************************************
 *  MemIf_GetStatus()
 *********************************************************************************************************************/
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
 */
 FUNC(MemIf_StatusType, MEMIF_CODE) MemIf_GetStatus(uint8 DeviceIndex)
{
  /* ----- Local Variables ------------------------------------------------------------------------------*/
  uint8 errorId = MEMIF_E_NO_ERROR;
  MemIf_StatusType retVal = MEMIF_UNINIT;

  uint8 MemIf_LoopCounter;
  uint8 MemIf_StatusMask = 0;

  /* ----- Development Error Detection ------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if DeviceIndex is out of bounds. BroadcastId (0xFF) is a valid input. */
  if ( (DeviceIndex != MEMIF_BROADCAST_ID) && (DeviceIndex >= MemIf_NumberOfDevices) )
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif

  /* ----- Implementation -------------------------------------------------------------------------------*/
  if(MEMIF_BROADCAST_ID == DeviceIndex)
  {

    /* #20 Get status of all configured MemHwA modules */
    for (MemIf_LoopCounter = 0; MemIf_LoopCounter < MemIf_NumberOfDevices; MemIf_LoopCounter++)
    {
      /* #25 Store each status to status mask */
      MemIf_StatusMask |= (uint8) ((uint8)1u << (uint8) MemIf_MemHwaApis[MemIf_LoopCounter].GetStatus()); /* SBSW_MEMIF_02 */
    }

    /* #30 Check if UNINIT-bit is set */
    if (MemIf_IsBitSet(MemIf_StatusMask, MEMIF_UNINIT) == E_OK)
    {
      retVal = MEMIF_UNINIT;
    }
    /* #31 Check if BUSY-bit is set */
    else if (MemIf_IsBitSet(MemIf_StatusMask, MEMIF_BUSY) == E_OK)
    {
      retVal = MEMIF_BUSY;
    }
    /* #32 Check if BUSY_INTERNAL-bit is set */
    else if (MemIf_IsBitSet(MemIf_StatusMask, MEMIF_BUSY_INTERNAL) == E_OK)
    {
      retVal = MEMIF_BUSY_INTERNAL;
    }
    /* #33 All MemHwA modules are MEMIF_IDLE */
    else
    {
      retVal = MEMIF_IDLE;
    }

  }
  else
  /* #40 Get status of MemHwA module indexed by DeviceIndex */
  {
    retVal = MemIf_MemHwaApis[DeviceIndex].GetStatus(); /* SBSW_MEMIF_02 */
  }

  /* #50 Report development error if configured */
  /* ----- Development Error Report ---------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_GET_STATUS, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId); /* SBSW_MEMIF_03 */ /* PRQA S 3200, 3335 */ /* MD_MSR_14.2 */
#endif

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  MemIf_GetJobResult()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(MemIf_JobResultType, MEMIF_CODE) MemIf_GetJobResult(uint8 DeviceIndex)
{
  /* ----- Local Variables ------------------------------------------------------------------------------*/
  uint8 errorId = MEMIF_E_NO_ERROR;
  MemIf_JobResultType retVal = MEMIF_JOB_FAILED;

  /* ----- Development Error Detection ------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (MemIf_DetChkDeviceIndex(DeviceIndex) == E_NOT_OK)
  {
    errorId = MEMIF_E_PARAM_DEVICE;
  }
  else
#endif
  {
  /* ----- Implementation -------------------------------------------------------------------------------*/
    retVal = MemIf_MemHwaApis[DeviceIndex].GetJobResult(); /* SBSW_MEMIF_02 */
  }

  /* ----- Development Error Report ---------------------------------------------------------------------*/
#if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_GET_JOB_RESULT, errorId);
  }
#else
  MEMIF_DUMMY_STATEMENT(errorId); /* SBSW_MEMIF_03 */ /* PRQA S 3200, 3335 */ /* MD_MSR_14.2 */
#endif

  return retVal;
}


#if (MEMIF_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  MemIf_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
void MemIf_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, MEMIF_APPL_DATA) VersionInfoPtr)
{
  /* ----- Local Variables ------------------------------------------------------------------------------*/
  uint8 errorId = MEMIF_E_NO_ERROR;

  /* ----- Development Error Detection ------------------------------------------------------------------*/
# if (MEMIF_DEV_ERROR_DETECT == STD_ON)
  if (VersionInfoPtr == NULL_PTR)
  {
    errorId = MEMIF_E_PARAM_POINTER;
  }
  else
# endif
  {
  /* ----- Implementation -------------------------------------------------------------------------------*/
    VersionInfoPtr->vendorID         = MEMIF_VENDOR_ID; /* SBSW_MEMIF_01 */
    VersionInfoPtr->moduleID         = MEMIF_MODULE_ID; /* SBSW_MEMIF_01 */
    VersionInfoPtr->sw_major_version = MEMIF_SW_MAJOR_VERSION; /* SBSW_MEMIF_01 */
    VersionInfoPtr->sw_minor_version = MEMIF_SW_MINOR_VERSION; /* SBSW_MEMIF_01 */
    VersionInfoPtr->sw_patch_version = MEMIF_SW_PATCH_VERSION; /* SBSW_MEMIF_01 */
  }

  /* ----- Development Error Report ---------------------------------------------------------------------*/
# if (MEMIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != MEMIF_E_NO_ERROR)
  {
    (void)Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, MEMIF_SID_VERSION_INFO, errorId);
  }
# else
  MEMIF_DUMMY_STATEMENT(errorId); /* SBSW_MEMIF_03 */ /* PRQA S 3200, 3335 */ /* MD_MSR_14.2 */
# endif

}
#endif /* MEMIF_VERSION_INFO_API */


/**********************************************************************************************************************
 *  MemIf_SetMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, MEMIF_CODE) MemIf_SetMode(MemIf_ModeType Mode)
{
  uint8 MemIf_LoopCounter;

  for(MemIf_LoopCounter = 0; MemIf_LoopCounter < MemIf_NumberOfDevices; MemIf_LoopCounter++)
  {
    MemIf_MemHwaApis[MemIf_LoopCounter].SetMode(Mode); /* SBSW_MEMIF_02 */
  }
}


#define MEMIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* START_COVERAGE_JUSTIFICATION
    \ID COV_MEMIF_COMPATIBILITY
      \ACCEPT XF
      \ACCEPT TX
      \REASON [COV_MSR_COMPATIBILITY]
END_COVERAGE_JUSTIFICATION */

/* SBSW_JUSTIFICATION_BEGIN
   \ID SBSW_MEMIF_01
     \DESCRIPTION The function Ea_GetVersionInfo writes to the object referenced by parameter VersionInfoPtr
     \COUNTERMEASURE \N The caller ensures that the pointers passed to the parameters VersionInfoPtr is valid.
   \ID SBSW_MEMIF_02
      \DESCRIPTION Function pointer from function pointer structure is called
      \COUNTERMEASURE \N  The compiler performs type check and therefore assures that valid function pointer is called.
                          Reference of pointer structure is retrieved by array access. Used index DeviceIndex is checked by DET for being valid.
   \ID SBSW_MEMIF_03
      \DESCRIPTION Implicit function call of MEMIF_DUMMY_STATEMENT
      \COUNTERMEASURE \N Macro MEMIF_DUMMY_STATEMENT is defined empty. It's used to prevent the compiler from reporting warnings due to unused parameters.

    \ID SBSW_MEMIF_04
      \DESCRIPTION Fee or Ea function is called
      \COUNTERMEASURE \N  The compiler performs type check and therefore assures that valid function is called.
SBSW_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: MemIf.c
 *********************************************************************************************************************/
