/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         \file  Fee_30_SmallSector_PartitionHandler.c
 *        \brief  Fee Sub-component PartitionHandler source file
 *
 *      \details  PartitionHandler is responsible for management and initialization of partition relevant data.
 *                PartitionHandler provides public services to other FEE sub-components to access partition relevant data.
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

#define FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector_PartitionHandler.h"

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#ifndef FEE_30_SMALLSECTOR_LOCAL /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL static
#endif

#define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR (uint16, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ph_PartitionIndex;

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_CODE
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_FindBlockNumberInList()
**********************************************************************************************************************/
/*! \brief     Checks if a certain BlockNumber is contained in a certain Partition
 * \details    Checks if BlockNumber is contained in Partition PartitionIndex is pointing to
 * \param[in]  PartitionIndex
 * \param[in]  BlockNumber
 * \return     E_OK: BlockNumber is contained in partition
 * \return     E_NOT_OK: BlockNumber is not contained in partition
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ph_FindBlockNumberInList(uint16 PartitionIndex, uint16 BlockNumber);

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_CleanBlockNumber()
**********************************************************************************************************************/
/*! \brief     Returns clean BlockNumber
 * \details    Returns BlockNumber without DatasetIndex part
 * \param[in]  BlockNumber
 * \return     BlockNumber
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (uint16, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ph_CleanBlockNumber(uint16 BlockNumber);


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_FindBlockNumberInList()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ph_FindBlockNumberInList(uint16 PartitionIndex, uint16 BlockNumber)
{
  uint16 i;
  Std_ReturnType retVal = E_NOT_OK;

  /* #10 Iterate over all blocks in certain partition */
  for (i = 0; i < FEE_30_SMALLSECTOR_MAX_BLOCKS_PER_PARTITION; i++)
  {
    /* #20 Check if BlockNumber is contained in current partition */
    if (Fee_30_SmallSector_PartitionConfigList[PartitionIndex].BlockNumberList[i] == BlockNumber)
    {
      retVal = E_OK;
      break;
    }
  }

  return retVal;
}


/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_CleanBlockNumber()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (uint16, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ph_CleanBlockNumber(uint16 BlockNumber)
{

  return BlockNumber & (0xFFFFu - (((uint16) 1u << ((uint16) Fee_30_SmallSector_DatasetSelectionBits)) - (uint16) 1u));
}


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_Init()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_Init(uint16 BlockNumber)
{
  uint16 LoopCounter;
  /* #10 PartitionIndex has to be initialized with Partition BlockNumber is contained in */
  for (LoopCounter = 0; LoopCounter < FEE_30_SMALLSECTOR_NUMBER_OF_PARTITIONS; LoopCounter++) /* COV_FEE_30_SMALLSECTOR_CONDITION_ALWAYS_TRUE */
  {
    if (Fee_30_SmallSector_Ph_FindBlockNumberInList(LoopCounter, Fee_30_SmallSector_Ph_CleanBlockNumber(BlockNumber)) == E_OK)
    {
      /* #20 Partition, which contains BlockNumber, was found. Index is stored */
      Fee_30_SmallSector_Ph_PartitionIndex = LoopCounter;
      break;
    }
  }
}


/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetPartitionStartAddress()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetPartitionStartAddress(void)
{
  return Fee_30_SmallSector_PartitionConfigList[Fee_30_SmallSector_Ph_PartitionIndex].PartitionStartAddress;
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetPartitionWriteAlignment(void)
{
  return Fee_30_SmallSector_PartitionConfigList[Fee_30_SmallSector_Ph_PartitionIndex].PartitionWriteAlignment;
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetPartitionAddressAlignment()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetPartitionAddressAlignment(void)
{
  return Fee_30_SmallSector_PartitionConfigList[Fee_30_SmallSector_Ph_PartitionIndex].PartitionAddressAlignment;
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetPartitionReadAlignment()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetPartitionReadAlignment(void)
{
  return Fee_30_SmallSector_PartitionConfigList[Fee_30_SmallSector_Ph_PartitionIndex].PartitionReadAlignment;
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetFlsApiPtr()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Fee_30_SmallSector_FlsApiPtrType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetFlsApiPtr(void)
{
  return Fee_30_SmallSector_PartitionConfigList[Fee_30_SmallSector_Ph_PartitionIndex].FlsApiPtr;
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetFlsEraseValue()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (uint8, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetFlsEraseValue(void)
{
  return Fee_30_SmallSector_PartitionConfigList[Fee_30_SmallSector_Ph_PartitionIndex].FlsEraseValue;
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetBlankCheckApi()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetBlankCheckApi(void)
{
  return Fee_30_SmallSector_PartitionConfigList[Fee_30_SmallSector_Ph_PartitionIndex].BlankCheckApiEnabled;
}


#define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* START_COVERAGE_JUSTIFICATION
    \ID COV_FEE_30_SMALLSECTOR_CONDITION_ALWAYS_TRUE
    \ACCEPT TX
    \REASON Condition "LoopCounter < FEE_30_SMALLSECTOR_NUMBER_OF_PARTITIONS" is never false in TscStandard.
            'break' in if-clause prevents loop condition from getting false because even if last partition
            contains BlockNumber, LoopCounter will not exceed the condition. Only invalid BlockNumbers are able to
            trigger this condition, and only if DET is disabled, since DET checks validity of BlockNumber before.
END_COVERAGE_JUSTIFICATION */


/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_PartitionHandler.c
 *********************************************************************************************************************/
