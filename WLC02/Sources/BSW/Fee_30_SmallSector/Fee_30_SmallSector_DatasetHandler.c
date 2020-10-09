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
 *          \file  Fee_30_SmallSector_DatasetHandler.c
 *         \brief  Fee Sub-component DatasetHandler source file
 *
 *       \details  DatasetHandler sub-component is responsible for management and initialization of dataset relevant data.
 *                 DatasetHandler provides public services to other FEE sub-components to access block dataset data.
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

#include "Fee_30_SmallSector_DatasetHandler.h"
#include "Fee_30_SmallSector_PartitionHandler.h"
#include "Fee_30_SmallSector_FlsCoordinator.h"

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#ifndef FEE_30_SMALLSECTOR_LOCAL /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL static
#endif

typedef struct
{
  Fee_30_SmallSector_AddressType DatasetStartAddress;
  Fee_30_SmallSector_AddressType FirstInstanceAddress;
  Fee_30_SmallSector_AddressType ErasePattern2Address;
  uint16 DatasetSize;
  uint16 AlignedInstanceSize;
  uint16 DataLength;
  uint8 NumberOfInstances;
  uint8 DatasetIndex;
} Fee_30_SmallSector_Dh_DatasetType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(Fee_30_SmallSector_Dh_DatasetType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Dh_DatasetInfo;

FEE_30_SMALLSECTOR_LOCAL VAR(uint8, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Dh_TempBuffer[FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT];

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_CODE
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_GetDatasetIndex()
 **********************************************************************************************************************/
/*!
 * \brief      Returns dataset index
 * \details    Calculates and returns dataset index from BlockNumber
 * \param[in]  BlockNumber
 * \return     Dataset index
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (uint8, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Dh_GetDatasetIndex(uint16 BlockNumber);

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_CalcIndexOfCurrentInstance()
 **********************************************************************************************************************/
/*!
 * \brief      Calculates instance index related to passed instance start address
 * \details    Calculates instance index in current dataset related to passed instance start address
 * \param[in]  InstanceHeaderAddress
 * \return     InstanceIndex
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (uint8, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Dh_CalcIndexOfCurrentInstance(Fee_30_SmallSector_AddressType InstanceStartAddress);

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_GetAddressFromInstanceIndex()
 **********************************************************************************************************************/
/*!
 * \brief      Calculates start address of instance from instance index
 * \details    Calculates start address of instance related to passed instance index
 * \param[in]  IndexOfActiveInstance
 * \return     InstanceStartAddress
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Dh_GetAddressFromInstanceIndex(uint8 IndexOfActiveInstance);

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_GetAlignedSizeOfInstance()
 **********************************************************************************************************************/
/*!
 * \brief      Returns aligned size of one instance contained in current dataset
 * \details    Returns aligned size of one instance contained in current dataset.
 *             Aligned size includes Management length, Data length and number of padding bytes
 * \return     Size of instance
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (uint16, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Dh_GetAlignedSizeOfInstance(void);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_GetDatasetIndex()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (uint8, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Dh_GetDatasetIndex(uint16 BlockNumber)
{
  return (uint8) (BlockNumber & (((uint16) 1u << ((uint16) Fee_30_SmallSector_DatasetSelectionBits)) - (uint16) 1u));
}

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_CalcIndexOfCurrentInstance()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (uint8, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Dh_CalcIndexOfCurrentInstance(Fee_30_SmallSector_AddressType InstanceStartAddress)
{
  return (uint8) ((InstanceStartAddress - Fee_30_SmallSector_Dh_DatasetInfo.DatasetStartAddress - Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()) / Fee_30_SmallSector_Dh_GetAlignedSizeOfInstance());
}

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_GetAddressFromInstanceIndex()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Dh_GetAddressFromInstanceIndex(uint8 IndexOfActiveInstance)
{
  /* #10 InstanceStartAddress = DatasetStartAddress + ErasePatternSize + (InstanceIndex * AlignedInstanceSize) */
  return Fee_30_SmallSector_Dh_DatasetInfo.DatasetStartAddress + (Fee_30_SmallSector_AddressType) Fee_30_SmallSector_Ph_GetPartitionWriteAlignment() +
            ((Fee_30_SmallSector_AddressType) IndexOfActiveInstance * ((Fee_30_SmallSector_AddressType) Fee_30_SmallSector_Dh_GetAlignedSizeOfInstance()));
}

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_GetAlignedSizeOfInstance()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC (uint16, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Dh_GetAlignedSizeOfInstance(void)
{
  return Fee_30_SmallSector_Dh_DatasetInfo.AlignedInstanceSize;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_Init()
 **********************************************************************************************************************/
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
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_Init(uint16 BlockNumber, uint16 DataLength,
        uint8 NumberOfInstances, Fee_30_SmallSector_AddressType BlockStartAddress, uint16 AddressAlignment)
{
  uint16 WriteAlignment = Fee_30_SmallSector_Ph_GetPartitionWriteAlignment();
  /* #10 InstanceSize: align( 2*WriteAlignment + MANAGEMENT_SIZE + DataLength, WriteAlignment) */
  Fee_30_SmallSector_Dh_DatasetInfo.AlignedInstanceSize = (uint16) Fee_30_SmallSector_AlignValue(((uint32) 2u * (uint32) WriteAlignment) + (uint32) FEE_30_SMALLSECTOR_MANAGEMENT_SIZE + (uint32) DataLength, WriteAlignment);
  /* #20 DatasetSize: align( 2*WriteAlignment + (InstanceSize * NrOfInstances), AddressAlignment) */
  Fee_30_SmallSector_Dh_DatasetInfo.DatasetSize = (uint16) Fee_30_SmallSector_AlignValue((uint32) (((uint32) 2u * (uint32) WriteAlignment) + ((uint32) Fee_30_SmallSector_Dh_DatasetInfo.AlignedInstanceSize * (uint32) NumberOfInstances)), AddressAlignment);
  /* #30 DatasetIndex is encoded in the dataset selection bits within the block number */
  Fee_30_SmallSector_Dh_DatasetInfo.DatasetIndex = Fee_30_SmallSector_Dh_GetDatasetIndex(BlockNumber);
  /* #40 First ErasePattern is stored at DatasetStartAddress */
  Fee_30_SmallSector_Dh_DatasetInfo.DatasetStartAddress = BlockStartAddress + (((Fee_30_SmallSector_AddressType) Fee_30_SmallSector_Dh_DatasetInfo.DatasetSize) * ((Fee_30_SmallSector_AddressType) Fee_30_SmallSector_Dh_DatasetInfo.DatasetIndex));
  /* #50 First instance starts in second page of dataset */
  Fee_30_SmallSector_Dh_DatasetInfo.FirstInstanceAddress = Fee_30_SmallSector_Dh_DatasetInfo.DatasetStartAddress + WriteAlignment;
  /* #60 Second ErasePattern is stored within very last page of dataset's last FLS sector */
  Fee_30_SmallSector_Dh_DatasetInfo.ErasePattern2Address = (Fee_30_SmallSector_Dh_DatasetInfo.DatasetStartAddress + Fee_30_SmallSector_Dh_DatasetInfo.DatasetSize) - WriteAlignment;
  Fee_30_SmallSector_Dh_DatasetInfo.DataLength = DataLength;
  Fee_30_SmallSector_Dh_DatasetInfo.NumberOfInstances = NumberOfInstances;
}

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_GetDataLength()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_GetDataLength(void)
{
  return Fee_30_SmallSector_Dh_DatasetInfo.DataLength;
}

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_GetFirstInstanceAddress()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_GetFirstInstanceAddress(void)
{
  return Fee_30_SmallSector_Dh_DatasetInfo.FirstInstanceAddress;
}

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_GetLastSectorIndex()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (sint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_GetLastSectorIndex(void)
{
  /* #10 Index = (DatasetSize / SectorSize) - 1 */
  /* #11 Index is zero based */
  uint16 index = (Fee_30_SmallSector_Dh_DatasetInfo.DatasetSize / Fee_30_SmallSector_Ph_GetPartitionAddressAlignment()) - (uint16) 1u;
  return (sint16) index;
}

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_PrepareNextInstance()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_PrepareNextInstance(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance)
{
  /* #10 This function is never called with Instance being the last instance of a dataset! */
  uint8 nextInstanceIndex;
  Fee_30_SmallSector_AddressType NewStartAddress;

  /* #20 Index of subsequent instance is retrieved based on current instance object */
  nextInstanceIndex = (uint8) (1u + Fee_30_SmallSector_Dh_CalcIndexOfCurrentInstance(Fee_30_SmallSector_Ih_GetInstanceStartAddress(Instance))); /* SBSW_FEE_30_SMALLSECTOR_112 */

  /* #30 Start address of subsequent instance is calculated */
  NewStartAddress = Fee_30_SmallSector_Dh_GetAddressFromInstanceIndex(nextInstanceIndex);

  /* #40 Update instance object with new addresses and reset other values, e.g. write pattern states */
  Fee_30_SmallSector_Ih_PrepareNextInstanceProperties(Instance, NewStartAddress); /* SBSW_FEE_30_SMALLSECTOR_111 */
}

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_EraseSector()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_EraseSector(uint16 sectorIndex)
{
  /* #10 Calculate sector's start address according to sectorIndex */
  /* #11 SectorAddress = DatasetStartAddress + (SectorSize * SectorIndex) */
  Fee_30_SmallSector_AddressType sectorAddress = Fee_30_SmallSector_Dh_DatasetInfo.DatasetStartAddress + (((Fee_30_SmallSector_AddressType) Fee_30_SmallSector_Ph_GetPartitionAddressAlignment()) * ((Fee_30_SmallSector_AddressType) sectorIndex));

  return Fee_30_SmallSector_Fls_Erase(sectorAddress, Fee_30_SmallSector_Ph_GetPartitionAddressAlignment());
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_WriteErasePattern()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_WriteErasePattern(Fee_30_SmallSector_Dh_ErasePatternType pattern)
{
  /* #10 Initialize TempBuffer with static erase pattern */
  uint8 LoopCounter;
  /* #20 Either ErasePattern1 or ErasePattern2 is addressed */
  Fee_30_SmallSector_AddressType address = ((pattern == DATASET_ERASE_PATTERN_1) ? Fee_30_SmallSector_Dh_DatasetInfo.DatasetStartAddress : Fee_30_SmallSector_Dh_DatasetInfo.ErasePattern2Address);

  for (LoopCounter = 0u; LoopCounter < FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT; LoopCounter++)
  {
    Fee_30_SmallSector_Dh_TempBuffer[LoopCounter] = FEE_30_SMALLSECTOR_STATIC_PATTERN; /* SBSW_FEE_30_SMALLSECTOR_113 */
  }

  /* #30 Write static pattern value to ErasePattern addressed by pattern parameter */
  return Fee_30_SmallSector_Fls_Write(address, Fee_30_SmallSector_Dh_TempBuffer, Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()); /* SBSW_FEE_30_SMALLSECTOR_27 */
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_ReadErasePattern()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_ReadErasePattern(Fee_30_SmallSector_Dh_ErasePatternType pattern)
{
  /* #10 Either ErasePattern1 or ErasePattern2 is addressed */
  Fee_30_SmallSector_AddressType address = ((pattern == DATASET_ERASE_PATTERN_1) ? Fee_30_SmallSector_Dh_DatasetInfo.DatasetStartAddress : Fee_30_SmallSector_Dh_DatasetInfo.ErasePattern2Address);

  /* #20 Perform read job for requested pattern */
  return Fee_30_SmallSector_Fls_Read(address, Fee_30_SmallSector_Dh_TempBuffer, Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()); /* SBSW_FEE_30_SMALLSECTOR_27 */
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_BlankCheckErasePattern()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_BlankCheckErasePattern(Fee_30_SmallSector_Dh_ErasePatternType pattern)
{
  /* #10 Either ErasePattern1 or ErasePattern2 is addressed */
  Fee_30_SmallSector_AddressType address = ((pattern == DATASET_ERASE_PATTERN_1) ? Fee_30_SmallSector_Dh_DatasetInfo.DatasetStartAddress : Fee_30_SmallSector_Dh_DatasetInfo.ErasePattern2Address);

  /* #20 Perform blank check job for requested pattern */
  return Fee_30_SmallSector_Fls_BlankCheck(address, Fee_30_SmallSector_Ph_GetPartitionWriteAlignment());
}

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_CheckErasePattern()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_CheckErasePattern(void)
{
  /* #10 Service needs to distinguish between two cases: BlankCheck API is provided or not */
  Std_ReturnType retVal;

  if (Fee_30_SmallSector_Ph_GetBlankCheckApi() == TRUE)
  {
    /* #20 Perform BlankCheck on first page of Dataset, which contains the ErasePattern */
    retVal = Fee_30_SmallSector_Dh_BlankCheckErasePattern(DATASET_ERASE_PATTERN_1);
  }
  else
  {
    /* #30 Read content of first page, which contains the ErasePattern */
    retVal = Fee_30_SmallSector_Dh_ReadErasePattern(DATASET_ERASE_PATTERN_1);
  }
  return retVal;
}

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_IsLastInstance()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_IsLastInstance(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  /* #10 Index of current instance is calculated based on passed Instance object */
  uint8 IndexOfInstance = Fee_30_SmallSector_Dh_CalcIndexOfCurrentInstance(Fee_30_SmallSector_Ih_GetInstanceStartAddress(Instance)); /* SBSW_FEE_30_SMALLSECTOR_112 */

  /* #20 NumberOfInstances is reduced by (1u), because instance indexes are zero based */
  return ((IndexOfInstance == (Fee_30_SmallSector_Dh_DatasetInfo.NumberOfInstances - 1u)) ? TRUE : FALSE);
}

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_IsFirstInstanceAndBlank()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_IsFirstInstanceAndBlank(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  /* #10 Index of current instance is calculated based on passed Instance object */
  uint8 IndexOfInstance = Fee_30_SmallSector_Dh_CalcIndexOfCurrentInstance(Fee_30_SmallSector_Ih_GetInstanceStartAddress(Instance)); /* SBSW_FEE_30_SMALLSECTOR_112 */

  /* #20 Check if Instance is blank */
  boolean IsBlank = (boolean) (Fee_30_SmallSector_Ih_GetInstanceStatus(Instance) == INSTANCE_STATUS_ERASED); /* SBSW_FEE_30_SMALLSECTOR_112 */

  /* #30 Return true, if Instance is both blank and the first instance of the dataset (index == 0) at the same time */
  return (((IndexOfInstance == 0u) && (IsBlank == TRUE)) ? TRUE : FALSE);
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_IsErasePatternBlank()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_IsErasePatternBlank(void)
{
  boolean retVal = TRUE;
  uint16 LoopCounter;

  /* #10 Content of read buffer needs only to be checked if no BlankCheck API is provided by the FLS driver, because only in this case a Read is performed */
  if (Fee_30_SmallSector_Ph_GetBlankCheckApi() == FALSE)
  {
    /* #20 Check every element of recently read erase pattern for Flash's erase value */
    for (LoopCounter = 0; LoopCounter < Fee_30_SmallSector_Ph_GetPartitionWriteAlignment(); LoopCounter++)
    {
      if (Fee_30_SmallSector_Dh_TempBuffer[LoopCounter] != Fee_30_SmallSector_Ph_GetFlsEraseValue())
      {
        /* #30 Return false in case erase pattern is not completely blank/erased */
        retVal = FALSE;
        break;
      }
    }
  }

  return retVal;
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_IsErasePatternValid()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_IsErasePatternValid(void)
{
  boolean retVal = TRUE;
  uint16 LoopCounter;

  /* #10 Iterate over all bytes within the recently read page */
  for (LoopCounter = 0; LoopCounter < Fee_30_SmallSector_Ph_GetPartitionWriteAlignment(); LoopCounter++)
  {
    if (Fee_30_SmallSector_Dh_TempBuffer[LoopCounter] != FEE_30_SMALLSECTOR_STATIC_PATTERN)
    {
      /* #20 Return false in case erase pattern content does not match with static pattern value */
      retVal = FALSE;
      break;
    }
  }

  return retVal;
}

#define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA L:LongInfixName */

/* SBSW_JUSTIFICATION_BEGIN
    \ID SBSW_FEE_30_SMALLSECTOR_111
      \DESCRIPTION Function is called with pointer to an instance object of type Fee_30_SmallSector_Ih_InstanceVarPointerType
      \COUNTERMEASURE \N Instance parameter is passed to function via input parameter, thus caller ensures that parameter referenced
                         by pointer is valid.

    \ID SBSW_FEE_30_SMALLSECTOR_112
      \DESCRIPTION Function is called with pointer to an instance object of type Fee_30_SmallSector_Ih_InstanceConstPointerType
      \COUNTERMEASURE \N Instance parameter is passed to function via input parameter, thus caller ensures that parameter referenced
                         by pointer is valid.

    \ID SBSW_FEE_30_SMALLSECTOR_113
      \DESCRIPTION Write access of array parameter Fee_30_SmallSector_Dh_TempBuffer from index 0 to index 'FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT - 1'
      \COUNTERMEASURE \N No out of bounds access possible because parameter Fee_30_SmallSector_Dh_TempBuffer is initialized with size equal to
                         definition of 'FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT'.
SBSW_JUSTIFICATION_END */
/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_DatasetHandler.c
 *********************************************************************************************************************/
