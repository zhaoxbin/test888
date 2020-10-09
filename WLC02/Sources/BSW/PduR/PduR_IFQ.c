/**********************************************************************************************************************
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
 *         File:  PduR_IFQ.c
 *      Project:  Gw_AsrPduRCfg5
 *       Module:  MICROSAR PDU Router
 *    Generator:  Configurator 5
 *
 *  Description:  Vector implementation of AUTOSAR PDU Router
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */
/* PRQA  S 4304 EOF */ /* MD_MSR_AutosarBoolean */
/* *INDENT-ON* */

#define PDUR_IFQ_SOURCE
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_IFQ.h"
#include "SchM_PduR.h"
#if (PDUR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#define PduR_Core_MemCpyRamToRam(d, s, l)    VStdMemCpyRamToRam((d), (s), (l))

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define PDUR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_19.1 */

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_IsQueueFull
 *********************************************************************************************************************/
/*! \brief      Returns if the queue is full.
 *  \details    -
 *  \param[in]  interfaceFifoQueueRomIdx  id of the interface fifo queue
 *  \return     true                      queue is full
 *              false                     queue is not full
 *  \pre        -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueFull(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_IsQueueEmpty
 *********************************************************************************************************************/
/*! \brief      Returns if the queue is empty.
 *  \details    -
 *  \param[in]  interfaceFifoQueueRomIdx  id of the interface fifo queue
 *  \return     true                      queue is empty
 *              false                     queue is not empty
 *  \pre        -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueEmpty(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_IncrementReadIdx
 *********************************************************************************************************************/
/*! \brief      Increments the read Idx with wrap around.
 *  \details    -
 *  \param[in]  interfaceFifoQueueRomIdx  id of the interface fifo queue
 *  \pre        -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementReadIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_IncrementWriteIdx
 *********************************************************************************************************************/
/*! \brief      Increments the write Idx with wrap around.
 *  \details    -
 *  \param[in]  interfaceFifoQueueRomIdx  id of the interface fifo queue
 *  \pre        -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementWriteIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx);
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_IFQ_Init(void)
{
  PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx;
  for(interfaceFifoQueueRomIdx = 0u; interfaceFifoQueueRomIdx < PduR_GetSizeOfInterfaceFifoQueueRom(); interfaceFifoQueueRomIdx++)
  {
    PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);

    PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue);  /* SBSW_PDUR_CSL02 */
    PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue); /* SBSW_PDUR_CSL02 */
    PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, FALSE);                                        /* SBSW_PDUR_CSL02 */
  }
}
#endif

/**********************************************************************************************************************
 * PduR_IFQ_PutFifo
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
 *********************************************************************************************************************/
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_IFQ_PutFifo(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  if(PduR_IFQ_IsQueueFull(interfaceFifoQueueRomIdx))
  {
    retVal = E_NOT_OK;
  }
  else
  {
    PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);
    PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType interfaceFifoQueueElementRamWriteIdx = PduR_GetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);

    PduR_InterfaceFifoQueueArrayRamEndIdxOfInterfaceFifoQueueRomType offset = (interfaceFifoQueueElementRamWriteIdx - startIdxOfQueue) * PduR_GetMaxPduLengthOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);

    PduR_SetActualLengthOfInterfaceFifoQueueElementRam(interfaceFifoQueueElementRamWriteIdx, pduLength); /* SBSW_PDUR_CSL03 */
    PduR_Core_MemCpyRamToRam(PduR_GetAddrInterfaceFifoQueueArrayRam(PduR_GetInterfaceFifoQueueArrayRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx)) + offset, sduDataPtr, pduLength);   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_PDUR_MEM_CPY_FIFOMGR */
    PduR_IFQ_IncrementWriteIdx(interfaceFifoQueueRomIdx);
    retVal = E_OK;
  }

  PDUR_DUMMY_STATEMENT(rmDestRomIdx);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return retVal;
}
#endif

/**********************************************************************************************************************
 * PduR_IFQ_IsQueueFull
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueFull(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx)
{
  return PduR_IsFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);
}
#endif

/**********************************************************************************************************************
 * PduR_IFQ_IsQueueEmpty
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
LOCAL_INLINE FUNC(boolean, PDUR_CODE) PduR_IFQ_IsQueueEmpty(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx)
{
  return (PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx) == PduR_GetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx))
          && !PduR_IFQ_IsQueueFull(interfaceFifoQueueRomIdx);
}
#endif

/**********************************************************************************************************************
 * PduR_IFQ_IncrementReadIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementReadIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx)
{
  PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType localReadIdx = PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);
  localReadIdx++;

  if(localReadIdx >= PduR_GetInterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx))
  {
    PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx)); /* SBSW_PDUR_CSL03 */
  }
  else
  {
    PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, localReadIdx); /* SBSW_PDUR_CSL03 */
  }

  PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, FALSE); /* SBSW_PDUR_CSL03 */
}
#endif

/**********************************************************************************************************************
 * PduR_IFQ_IncrementWriteIdx
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_IFQ_IncrementWriteIdx(PduR_InterfaceFifoQueueRomIterType interfaceFifoQueueRomIdx)
{
  PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType localWriteIdx = PduR_GetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);
  localWriteIdx++;

  if(localWriteIdx >= PduR_GetInterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx))
  {
    PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx)); /* SBSW_PDUR_CSL03 */
  }
  else
  {
    PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, localWriteIdx);
  }

  if(PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx) == PduR_GetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx))
  {
    PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, TRUE); /* SBSW_PDUR_CSL03 */
  }
}
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetNextElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_IFQ_GetNextElement(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  if(PduR_IFQ_IsQueueEmpty(interfaceFifoQueueRomIdx))
  {
    retVal = E_NOT_OK;
  }
  else
  {
    PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);
    PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType interfaceFifoQueueElementRamReadIdx = PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);

    PduR_InterfaceFifoQueueArrayRamEndIdxOfInterfaceFifoQueueRomType offset = (interfaceFifoQueueElementRamReadIdx - startIdxOfQueue) * PduR_GetMaxPduLengthOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);

    info->SduDataPtr = PduR_GetAddrInterfaceFifoQueueArrayRam(PduR_GetInterfaceFifoQueueArrayRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx)) + offset; /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    info->SduLength  = PduR_GetActualLengthOfInterfaceFifoQueueElementRam(PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx)); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    *rmDestRomIdx = PduR_GetRmDestRomIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
    retVal = E_OK;
  }

  return retVal;
}
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_RemoveElement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_IFQ_RemoveElement(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  if(!PduR_IFQ_IsQueueEmpty(interfaceFifoQueueRomIdx)) /* COV_PDUR_FATAL_ERROR */
  {
    PduR_IFQ_IncrementReadIdx(interfaceFifoQueueRomIdx);
  }
}
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_FlushQueue
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_IFQ_FlushQueue(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));
  PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);

  PduR_SetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue);  /* SBSW_PDUR_CSL03 */
  PduR_SetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, startIdxOfQueue); /* SBSW_PDUR_CSL03 */
  PduR_SetFifoFullOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx, FALSE);                                        /* SBSW_PDUR_CSL03 */
}
#endif

#if (PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetFillLevel
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(uint16, PDUR_CODE) PduR_IFQ_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx) /* COV_PDUR_NO_DEFERRED_IF_ROUTING */
{
  uint16 fillLevel = 0;
  PduR_InterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRomType interfaceFifoQueueRomIdx = PduR_GetInterfaceFifoQueueRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  PduR_InterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRamType  readIdx         = PduR_GetInterfaceFifoQueueElementRamReadIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);
  PduR_InterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRamType writeIdx        = PduR_GetInterfaceFifoQueueElementRamWriteIdxOfInterfaceFifoQueueRam(interfaceFifoQueueRomIdx);
  PduR_InterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRomType startIdxOfQueue = PduR_GetInterfaceFifoQueueElementRamStartIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);
  PduR_InterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRomType   endIdxOfQueue   = PduR_GetInterfaceFifoQueueElementRamEndIdxOfInterfaceFifoQueueRom(interfaceFifoQueueRomIdx);

  if(readIdx < writeIdx)
  {
    fillLevel = (writeIdx - readIdx);
  }
  else if(writeIdx < readIdx)
  {
    fillLevel = (endIdxOfQueue - readIdx) + (writeIdx - startIdxOfQueue);
  }
  else /* (readIdx == writeIdx) */
  {
    if(PduR_IFQ_IsQueueFull(interfaceFifoQueueRomIdx)) /* COV_PDUR_NON_EMPTY_QUEUE */
    {
      fillLevel = (endIdxOfQueue - startIdxOfQueue);
    }
    else
    {
      fillLevel = 0;
    }
  }

  return fillLevel;
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: PduR_IFQ.c
 *********************************************************************************************************************/
