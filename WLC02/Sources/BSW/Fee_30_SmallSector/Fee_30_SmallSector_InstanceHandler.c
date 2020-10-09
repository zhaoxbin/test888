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
 *        \file  Fee_30_SmallSector_InstanceHandler.c
 *         \brief  Fee Sub-component InstanceHandler source file
 *
 *       \details  InstanceHandler sub-component is responsible for management and initialization of instance relevant
 *                 data. InstanceHandler provides public services to other FEE sub-components to create instance objects
 *                 and access their data.
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

#include "Fee_30_SmallSector_InstanceHandler.h"
#include "Fee_30_SmallSector_PartitionHandler.h"
#include "Fee_30_SmallSector_FlsCoordinator.h"
#include "hal.h"
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_CYCLE_COUNTER_BIT_MASK  (0x3U)

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#ifndef FEE_30_SMALLSECTOR_LOCAL /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL static
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(uint8, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_ReadBuffer[FEE_30_SMALLSECTOR_MAX_READ_SIZE];
FEE_30_SMALLSECTOR_LOCAL VAR(uint8, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_WriteBuffer[FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT];

#define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define FEE_30_SMALLSECTOR_START_SEC_CONST_8BIT
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL CONST(uint8, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_ValidManagementValue = 0xF0u;
FEE_30_SMALLSECTOR_LOCAL CONST(uint8, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_InvalidManagementValue = 0x0Fu;

#define FEE_30_SMALLSECTOR_STOP_SEC_CONST_8BIT
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_CODE
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_IsValidManagement()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if passed ManagementByte is one of valid management byte values
 * \details    Checks if passed ManagementByte is one of valid management byte values
 * \param[in]  ManagementByte
 * \return     TRUE: ManagementByte is valid
 * \return     FALSE: ManagementByte is not valid
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(boolean, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ih_IsValidManagement(uint8 ManagementByte);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_IsInvalidManagement()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if passed ManagementByte is one of invalid management byte values
 * \details    Checks if passed ManagementByte is one of invalid management byte values
 * \param[in]  ManagementByte
 * \return     TRUE: ManagementByte is invalid
 * \return     FALSE: ManagementByte is not invalid. Doesn't have to be "valid" either.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(boolean, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ih_IsInvalidManagement(uint8 ManagementByte);

#if (FEE_30_SMALLSECTOR_CORRECT_SINGLE_BIT_FLIPS == STD_ON)
/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_HasEvenParity()
 *********************************************************************************************************************/
/*!
 * \brief      Checks if passed nibble has even parity
 * \details    Checks if passed nibble has even parity
 * \param[in]  ManagementNibble
 * \return     TRUE: Nibble has even parity
 * \return     FALSE: Nibble has odd parity
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(boolean, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ih_HasEvenParity(uint8 ManagementNibble);
#endif

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_FillBufferWithStaticPattern()
 *********************************************************************************************************************/
/*!
 * \brief      Fills temporary buffer with configured static pattern value
 * \details    Fills temporary buffer (write buffer) with FEE_30_SMALLSECTOR_STATIC_PATTERN
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ih_FillBufferWithStaticPattern(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_FillBufferWithErasedValue()
 *********************************************************************************************************************/
/*!
 * \brief      Fills temporary buffer with configured erase value
 * \details    Fills temporary buffer (write buffer) with Flash's erase value
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ih_FillBufferWithErasedValue(void);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_IsValidManagement()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(boolean, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ih_IsValidManagement(uint8 ManagementByte)
{
  return (ManagementByte == Fee_30_SmallSector_Ih_ValidManagementValue) ? TRUE : FALSE;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_IsInvalidManagement()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(boolean, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ih_IsInvalidManagement(uint8 ManagementByte)
{
  return (ManagementByte == Fee_30_SmallSector_Ih_InvalidManagementValue) ? TRUE : FALSE;
}

#if (FEE_30_SMALLSECTOR_CORRECT_SINGLE_BIT_FLIPS == STD_ON)
/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_HasEvenParity()
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
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(boolean, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ih_HasEvenParity(uint8 ManagementNibble)
{
  boolean retVal;

  uint8 MgmtNibble = ManagementNibble;

  /* #10 All bits of an 8bit integer can be seen as: (a b c d e f g h) */

  /* #11 Only the lower nibble of ManagementNibble character is considered */
  MgmtNibble = MgmtNibble & 0x0Fu;
  /* #12 ManagementNibble = (0 0 0 0 e f g h) */

  MgmtNibble ^= (uint8) (MgmtNibble >> 2u);
  /* #13 ManagementNibble = (0 0 0 0 e f eg hf) - "eg" means the bit has the value "e XOR g" */

  MgmtNibble ^= (uint8) (MgmtNibble >> 1u);
  /* #14 ManagementNibble = (0 0 0 0 e ef efg efgh) */
  /* #15 All bits of the original word are XOR'd together and accumulated in the least-significant bit */

  /* #16 If the least-significant bit is zero, the original word "ManagementNibble" has even parity, */
  /* #17 otherwise odd parity */
  if ((MgmtNibble & 0x01u) == 0x00u)
  {
    retVal = TRUE;
  }
  else
  {
    retVal = FALSE;
  }

  return retVal;
}
#endif


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_FillBufferWithStaticPattern()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ih_FillBufferWithStaticPattern(void)
{
  uint8 LoopCounter;

  for (LoopCounter = 0u; LoopCounter < FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT; LoopCounter++)
  {
    Fee_30_SmallSector_Ih_WriteBuffer[LoopCounter] = FEE_30_SMALLSECTOR_STATIC_PATTERN; /* SBSW_FEE_30_SMALLSECTOR_22 */
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_FillBufferWithErasedValue()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Ih_FillBufferWithErasedValue(void)
{
  uint8 LoopCounter;

  for (LoopCounter = 0u; LoopCounter < FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT; LoopCounter++)
  {
    Fee_30_SmallSector_Ih_WriteBuffer[LoopCounter] = Fee_30_SmallSector_Ph_GetFlsEraseValue(); /* SBSW_FEE_30_SMALLSECTOR_22 */
  }
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_IsLastPageNecessary()
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
 */
FUNC(boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_IsLastPageNecessary(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  /* #10 Check if an additional last page needs to be written */
  /* #11 This depends on instance's data length: */
  /* #12 If (DataLength + MgmtSize) % PageSize != 0 not all of the payload bytes fit exactly to the pages */
  /* #13 For example: PageSize = 4, MgmtSize = 1, DataLength = 5 */
  /* #14     First page:       |     Second page:  */
  /* #15 Mgmt + 3 Data bytes   | 2 Data bytes + 2 padding bytes */
  return ((Fee_30_SmallSector_Ih_GetInstanceDataLength(Instance) + FEE_30_SMALLSECTOR_MANAGEMENT_SIZE) % Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()) != 0u; /* SBSW_FEE_30_SMALLSECTOR_29 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_CreateInstance()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_CreateInstance(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance,
        Fee_30_SmallSector_AddressType InstanceStartAddress, uint16 DataLength)
{
  Instance->StartAddress = InstanceStartAddress; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->WP2Address = InstanceStartAddress + Fee_30_SmallSector_Ph_GetPartitionWriteAlignment(); /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->MgmtAddress = InstanceStartAddress + (((Fee_30_SmallSector_AddressType) 2u) * ((Fee_30_SmallSector_AddressType) Fee_30_SmallSector_Ph_GetPartitionWriteAlignment())); /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->DataLength = DataLength; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->MgmtValue = Fee_30_SmallSector_Ph_GetFlsEraseValue(); /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->WP1State = FEE_30_SMALLSECTOR_PATTERN_INIT; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->WP2State = FEE_30_SMALLSECTOR_PATTERN_INIT; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->InstanceStatus = INSTANCE_STATUS_ERASED; /* SBSW_FEE_30_SMALLSECTOR_21 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_InitInstance()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_InitInstance(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance)
{
  Instance->StartAddress = 0x0000U; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->WP2Address = 0x0000U; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->MgmtAddress = 0x0000U; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->DataLength = 0x0000U; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->WP1State = FEE_30_SMALLSECTOR_PATTERN_INIT; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->WP2State = FEE_30_SMALLSECTOR_PATTERN_INIT; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->MgmtValue = 0x00U; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->InstanceStatus = INSTANCE_STATUS_ERASED; /* SBSW_FEE_30_SMALLSECTOR_21 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetInstanceStartAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetInstanceStartAddress(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  return Instance->StartAddress;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetEndPatternAddress()
 *********************************************************************************************************************/
/*!
*  Internal comment removed.
 *
 *
*/
FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetEndPatternAddress(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  return Instance->WP2Address;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetManagementAddress()
 *********************************************************************************************************************/
/*!
*  Internal comment removed.
 *
 *
*/
FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetManagementAddress(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  return Instance->MgmtAddress;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetInstanceDataLength()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetInstanceDataLength(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  return Instance->DataLength;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetInstanceStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Fee_30_SmallSector_Ih_InstanceStatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetInstanceStatus(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  return Instance->InstanceStatus;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetMgmtValue()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(uint8, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetMgmtValue(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  return Instance->MgmtValue;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetWP1State()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetWP1State(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  return Instance->WP1State;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetWP2State()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetWP2State(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  return Instance->WP2State;
}


/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_StoreMgmtValueFromBuffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_StoreMgmtValueFromBuffer(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance)
{
  /* #10 Store management value in instance object */
  Instance->MgmtValue = Fee_30_SmallSector_Ih_ReadBuffer[2u * Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()]; /* SBSW_FEE_30_SMALLSECTOR_21 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_SetInstanceStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetInstanceStatus(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance, Fee_30_SmallSector_Ih_InstanceStatusType status)
{
  Instance->InstanceStatus = status; /* SBSW_FEE_30_SMALLSECTOR_21 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_SetWP1State()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetWP1State(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance, Fee_30_SmallSector_StaticPatternState state)
{
  Instance->WP1State = state; /* SBSW_FEE_30_SMALLSECTOR_21 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_SetWP2State()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetWP2State(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance, Fee_30_SmallSector_StaticPatternState state)
{
  Instance->WP2State = state; /* SBSW_FEE_30_SMALLSECTOR_21 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_PrepareNextInstanceProperties()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_PrepareNextInstanceProperties(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance,
        Fee_30_SmallSector_AddressType StartAddress)
{
  /* #10 All relevant instances addresses are calculated based on input StartAddress */
  Instance->StartAddress = StartAddress; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->WP2Address = StartAddress + Fee_30_SmallSector_Ph_GetPartitionWriteAlignment(); /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->MgmtAddress = StartAddress + (((Fee_30_SmallSector_AddressType) 2u) * ((Fee_30_SmallSector_AddressType) Fee_30_SmallSector_Ph_GetPartitionWriteAlignment())); /* SBSW_FEE_30_SMALLSECTOR_21 */

  /* #20 Length parameters of instance are not modified, because they're still the same */

  /* #30 The following values are reset, because they need to be determined by Layer 3 ReadManagement job */
  Instance->MgmtValue = Fee_30_SmallSector_Ph_GetFlsEraseValue(); /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->WP1State = FEE_30_SMALLSECTOR_PATTERN_INIT; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->WP2State = FEE_30_SMALLSECTOR_PATTERN_INIT; /* SBSW_FEE_30_SMALLSECTOR_21 */
  Instance->InstanceStatus = INSTANCE_STATUS_ERASED; /* SBSW_FEE_30_SMALLSECTOR_21 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_SetManagementValuesAccordingToStatus()
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
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetManagementValuesAccordingToStatus(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance)
{
  /* #5 Service is only called after Instance's status was set */
  /* #6 Service is only called with Instance object whose status is either */
  /* #7 INSTANCE_STATUS_OK or INSTANCE_STATUS_INVALID */
  if (Fee_30_SmallSector_Ih_GetInstanceStatus(Instance) == INSTANCE_STATUS_OK) /* SBSW_FEE_30_SMALLSECTOR_29 */
  {
    /* #10 Management Byte are set with valid values for a WRITE job */
    Instance->MgmtValue = Fee_30_SmallSector_Ih_ValidManagementValue; /* SBSW_FEE_30_SMALLSECTOR_21 */
  }
  else /* #20 status == INSTANCE_STATUS_INVALID */
  {
    /* #21 Management Bytes are set with invalid values for an INVALIDATE job */
    Instance->MgmtValue = Fee_30_SmallSector_Ih_InvalidManagementValue; /* SBSW_FEE_30_SMALLSECTOR_21 */
  }
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_SetNegativeJobResultAccordingToStatus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetNegativeJobResultAccordingToStatus(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  MemIf_JobResultType retVal;

  /* #20 Service is never called with positive instance status (INSTANCE_STATUS_OK) */
  switch (Fee_30_SmallSector_Ih_GetInstanceStatus(Instance)) /* SBSW_FEE_30_SMALLSECTOR_29 */
  {
    case INSTANCE_STATUS_INVALID:
    case INSTANCE_STATUS_ERASED:
      retVal = MEMIF_BLOCK_INVALID;
      break;
    default:
      retVal = MEMIF_BLOCK_INCONSISTENT;
      break;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_DetermineInstanceStatus()
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
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_DetermineInstanceStatus(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance)
{
  Fee_30_SmallSector_Ih_InstanceStatusType status;
  uint8 mgmtValue = Fee_30_SmallSector_Ih_GetMgmtValue(Instance); /* SBSW_FEE_30_SMALLSECTOR_29 */
  Fee_30_SmallSector_StaticPatternState wp1State = Fee_30_SmallSector_Ih_GetWP1State(Instance); /* SBSW_FEE_30_SMALLSECTOR_29 */
  Fee_30_SmallSector_StaticPatternState wp2State = Fee_30_SmallSector_Ih_GetWP2State(Instance); /* SBSW_FEE_30_SMALLSECTOR_29 */

  /* #10 Instance's status is set according to management information */

  /* #20 Entire instance is blank --> Status: ERASED */
  if ((wp1State == FEE_30_SMALLSECTOR_PATTERN_BLANK) &&
      (wp2State == FEE_30_SMALLSECTOR_PATTERN_BLANK)
  )
  {
    status = INSTANCE_STATUS_ERASED;
  }
  /* #30 Both static patterns are valid */
  else if ( (wp1State == FEE_30_SMALLSECTOR_PATTERN_VALID) &&
            (wp2State == FEE_30_SMALLSECTOR_PATTERN_VALID) )
  {

    /* #31 Management value is equal to the valid value --> Status: OK */
    if (Fee_30_SmallSector_Ih_IsValidManagement(mgmtValue) == TRUE)
    {
      status = INSTANCE_STATUS_OK;
    }
    /* #32 Management value is equal to the invalid value --> Status: INVALID */
    else if (Fee_30_SmallSector_Ih_IsInvalidManagement(mgmtValue) == TRUE)
    {
      status = INSTANCE_STATUS_INVALID;
    }
    /* #33 Instance is assumed to be INCONSISTENT in every other case */
    else
    {
      status = INSTANCE_STATUS_INCONSISTENT;
    }

  }
  /* #40 Static pattern pages are neither completely valid or blank --> Status: INCONSISTENT */
  else
  {
    status = INSTANCE_STATUS_INCONSISTENT;
  }

  Instance->InstanceStatus = status; /* SBSW_FEE_30_SMALLSECTOR_21 */
}


#if (FEE_30_SMALLSECTOR_CORRECT_SINGLE_BIT_FLIPS == STD_ON)
/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_CorrectSingleBitFlips()
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
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_CorrectSingleBitFlips(Fee_30_SmallSector_Ih_BufferPointerType ManagementByte)
{
  uint8 correctNibble;
  uint8 LowerNibble = (*ManagementByte) & 0x0Fu;
  uint8 HigherNibbleInverted = (   (uint8)( ~(*ManagementByte) )   ) >> 4u;
  uint8 XorLowerHigherNibble = LowerNibble ^ HigherNibbleInverted;

  if (LowerNibble != HigherNibbleInverted)
  {
    /* #10 Lower Nibble and inverted higher nibble do not match, thus at least one single bit flip occurred */

    if ((XorLowerHigherNibble & (XorLowerHigherNibble - 1u)) == 0u)
    {
      /* #20 Difference of bit flips between LowerNibble and HigherNibble is one. Most likely exactly */
      /* #21 one bit flip occurred, but for example it is also possible that in one nibble two bit flips */
      /* #22 and in the other nibble one bit flip occurred. This case is ignored. */

      /* #23 In the next step, the nibble with valid (even) parity is determined, because it is assumed that */
      /* #24 this nibble does not contain any bit flips */
      if (Fee_30_SmallSector_Ih_HasEvenParity(LowerNibble) == TRUE)
      {
        correctNibble = LowerNibble;
      }
      else
      {
        correctNibble = HigherNibbleInverted;
      }

      /* #25 Correct nibble was found. Depending on invalidation bit in nibble, either valid management byte or */
      /* #26 invalid management byte is retrieved */
      if ((correctNibble & 4u) == 0u)
      {
        /* #30 Invalidation bit is not set */
        *ManagementByte = Fee_30_SmallSector_Ih_ValidManagementValue; /* SBSW_FEE_30_SMALLSECTOR_23 */
      }
      else
      {
        /* #31 Invalidation bit is set */
        *ManagementByte = Fee_30_SmallSector_Ih_InvalidManagementValue; /* SBSW_FEE_30_SMALLSECTOR_23 */
      }
    }
  }
}
#endif

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetStartPatternFromBuffer()
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
 *
 *
 *
 */
FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetStartPatternFromBuffer(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  uint16 LoopCounter;
  Fee_30_SmallSector_StaticPatternState retVal = FEE_30_SMALLSECTOR_PATTERN_INIT;
  boolean isPatternValid = FALSE;
  boolean isPatternBlank = FALSE;

  /* #10 Get status of start pattern: */
  /* #11 If entire start pattern is equal to value of static pattern, status PATTERN_VALID is returned */
  /* #12 If entire start pattern is equal to erase value of flash, status PATTERN_BLANK is returned */
  /* #13 Otherwise PATTERN_INCONSISTENT is returned */
  for (LoopCounter = 0; LoopCounter < Fee_30_SmallSector_Ph_GetPartitionWriteAlignment(); LoopCounter++)
  {
    /* #20 Check if current value matches with the static pattern */
    if (Fee_30_SmallSector_Ih_ReadBuffer[LoopCounter] == FEE_30_SMALLSECTOR_STATIC_PATTERN)
    {
      isPatternValid = TRUE;
      retVal = FEE_30_SMALLSECTOR_PATTERN_VALID;
    }
    /* #30 Check if current value matches with erase value of FLS */
    else if (Fee_30_SmallSector_Ih_ReadBuffer[LoopCounter] == Fee_30_SmallSector_Ph_GetFlsEraseValue())
    {
      isPatternBlank = TRUE;
      retVal = FEE_30_SMALLSECTOR_PATTERN_BLANK;
    }
    else
    {
      /* #40 Set both parameters, because this indicates that the pattern is inconsistent */
      isPatternBlank = TRUE;
      isPatternValid = TRUE;
      break;
    }
  }

  /* #50 Pattern contains both valid and blank bytes, thus it's inconsistent */
  if ((isPatternValid != isPatternBlank) == FALSE)
  {
    retVal = FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT;
  }

  /* #60 Return pattern's state depending on current state, because not all combinations are allowed: */
  /* #61 If pattern was already detected to be inconsistent (by previous BlankCheck), it's not allowed to set the pattern to BLANK */
  if (Fee_30_SmallSector_Ih_GetWP1State(Instance) == FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT) /* SBSW_FEE_30_SMALLSECTOR_29 */
  {
    if (retVal == FEE_30_SMALLSECTOR_PATTERN_BLANK)
    {
      /* #70 Pattern status is not changed from INCONSISTENT */
      retVal = FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT;
    }
    /* #80 Else: It's not necessary to change retVal, because it's either VALID or INCONSISTENT here */
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_GetEndPatternFromBuffer()
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
 *
 *
 *
 */
FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetEndPatternFromBuffer(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  uint16 LoopCounter;
  Fee_30_SmallSector_StaticPatternState retVal = FEE_30_SMALLSECTOR_PATTERN_INIT;
  boolean isPatternValid = FALSE;
  boolean isPatternBlank = FALSE;

  /* #10 Get status of end pattern: */
  /* #11 If entire end pattern is equal to value of static pattern, status PATTERN_VALID is returned */
  /* #12 If entire end pattern is equal to erase value of flash, status PATTERN_BLANK is returned */
  /* #13 Otherwise PATTERN_INCONSISTENT is returned */
  for (LoopCounter = Fee_30_SmallSector_Ph_GetPartitionWriteAlignment(); LoopCounter < (2u * Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()); LoopCounter++)
  {
    /* #20 Check if current value matches with the static pattern */
    if (Fee_30_SmallSector_Ih_ReadBuffer[LoopCounter] == FEE_30_SMALLSECTOR_STATIC_PATTERN)
    {
      isPatternValid = TRUE;
      retVal = FEE_30_SMALLSECTOR_PATTERN_VALID;
    }
    /* #30 Check if current value matches with erase value of FLS */
    else if (Fee_30_SmallSector_Ih_ReadBuffer[LoopCounter] == Fee_30_SmallSector_Ph_GetFlsEraseValue())
    {
      isPatternBlank = TRUE;
      retVal = FEE_30_SMALLSECTOR_PATTERN_BLANK;
    }
    else
    {
      /* #40 Set both parameters, because this indicates that the pattern is inconsistent */
      isPatternBlank = TRUE;
      isPatternValid = TRUE;
      break;
    }
  }

  /* #50 Pattern contains both valid and blank bytes, thus it's inconsistent */
  if ((isPatternValid != isPatternBlank) == FALSE)
  {
    retVal = FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT;
  }

  /* #60 Return pattern's state depending on current state, because not all combinations are allowed: */
  /* #61 If pattern was already detected to be inconsistent (by previous BlankCheck), it's not allowed to set the pattern to BLANK */
  if (Fee_30_SmallSector_Ih_GetWP2State(Instance) == FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT) /* SBSW_FEE_30_SMALLSECTOR_29 */
  {
    if (retVal == FEE_30_SMALLSECTOR_PATTERN_BLANK)
    {
      /* #70 Pattern status is not changed from INCONSISTENT */
      retVal = FEE_30_SMALLSECTOR_PATTERN_INCONSISTENT;
    }
    /* #80 Else: It's not necessary to change retVal, because it's either VALID or INCONSISTENT here */
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_BlankCheckStartPattern()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_BlankCheckStartPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  return Fee_30_SmallSector_Fls_BlankCheck(Fee_30_SmallSector_Ih_GetInstanceStartAddress(Instance), Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()); /* SBSW_FEE_30_SMALLSECTOR_29 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_BlankCheckEndPattern()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_BlankCheckEndPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  return Fee_30_SmallSector_Fls_BlankCheck(Fee_30_SmallSector_Ih_GetEndPatternAddress(Instance), Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()); /* SBSW_FEE_30_SMALLSECTOR_29 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_ReadAllMgmt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_ReadAllMgmt(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance)
{
  /* #10 Read both write patterns and management byte */
  uint16 readLength = (uint16) Fee_30_SmallSector_AlignValue( ((((uint32) 2u) * ((uint32) Fee_30_SmallSector_Ph_GetPartitionWriteAlignment())) + ((uint32) FEE_30_SMALLSECTOR_MANAGEMENT_SIZE)), Fee_30_SmallSector_Ph_GetPartitionReadAlignment() );
  return Fee_30_SmallSector_Fls_Read(Fee_30_SmallSector_Ih_GetInstanceStartAddress(Instance), Fee_30_SmallSector_Ih_ReadBuffer, readLength); /* SBSW_FEE_30_SMALLSECTOR_29 */ /* SBSW_FEE_30_SMALLSECTOR_27 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_ReadData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_ReadData(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
                                                    Fee_30_SmallSector_Ih_BufferPointerType DataBufferPtr,
                                                    uint16 BlockOffset,
                                                    uint16 ReadLength,uint16 blockid)
{
  /* #10 Only data contained in instance is read. No management bytes are read */
  Fee_30_SmallSector_AddressType readAddress ;//= Fee_30_SmallSector_Ih_GetManagementAddress(Instance) + FEE_30_SMALLSECTOR_MANAGEMENT_SIZE + BlockOffset; /* SBSW_FEE_30_SMALLSECTOR_29 */
  readAddress=HAL_GetNvmBlockAddress(blockid);
  return Fee_30_SmallSector_Fls_Read(readAddress, DataBufferPtr, ReadLength); /* SBSW_FEE_30_SMALLSECTOR_28 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_WriteStartPattern()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteStartPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
    Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter)
{

  /* #10 Prepare write buffer with static pattern value */
  /* #11 Amount of data bytes depend on write alignment */
  Fee_30_SmallSector_Ih_FillBufferWithStaticPattern();

  /* #20 Save write parameters for compare job */
  CompareParameter->Fee_30_SmallSector_Ih_CompareAddress = Fee_30_SmallSector_Ih_GetInstanceStartAddress(Instance); /* SBSW_FEE_30_SMALLSECTOR_25 */ /* SBSW_FEE_30_SMALLSECTOR_29 */
  CompareParameter->Fee_30_SmallSector_Ih_CompareBufferPtr = Fee_30_SmallSector_Ih_WriteBuffer; /* SBSW_FEE_30_SMALLSECTOR_25 */
  CompareParameter->Fee_30_SmallSector_Ih_CompareLength = Fee_30_SmallSector_Ph_GetPartitionWriteAlignment(); /* SBSW_FEE_30_SMALLSECTOR_25 */

  return Fee_30_SmallSector_Fls_Write(Fee_30_SmallSector_Ih_GetInstanceStartAddress(Instance), Fee_30_SmallSector_Ih_WriteBuffer, Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()); /* SBSW_FEE_30_SMALLSECTOR_29 */ /* SBSW_FEE_30_SMALLSECTOR_27 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_WriteManagementPage()
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
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteManagementPage(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
        Fee_30_SmallSector_UserJobParameterType UserJobParameter, Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter)
{
  uint16 LoopCounter;
  uint16 FillLength = Fee_30_SmallSector_Ph_GetPartitionWriteAlignment() - (uint16) FEE_30_SMALLSECTOR_MANAGEMENT_SIZE;

  /* #10 Prepare write buffer with erased value */
  Fee_30_SmallSector_Ih_FillBufferWithErasedValue();

  /* #20 Store management byte to first position in write buffer */
  Fee_30_SmallSector_Ih_WriteBuffer[0] = Fee_30_SmallSector_Ih_GetMgmtValue(Instance); /* SBSW_FEE_30_SMALLSECTOR_24 */ /* SBSW_FEE_30_SMALLSECTOR_29 */

  /* #30 Reduce FillLength if instance's data length is smaller than PageSize - ManagementSize */
  /* #31 That's because the management page can be filled with data bytes only if enough data bytes are available */
  /* #32 Some padding bytes will be necessary if DataLength < PageSize - ManagementSize */
  if (Fee_30_SmallSector_Ih_GetInstanceDataLength(Instance) < FillLength) /* SBSW_FEE_30_SMALLSECTOR_29 */
  {
    FillLength = Fee_30_SmallSector_Ih_GetInstanceDataLength(Instance); /* SBSW_FEE_30_SMALLSECTOR_29 */
  }

  /* #40 Fill remaining bytes of this page with payload bytes in case of a write job */
  /* #41 Invalidate and EraseImmediate jobs do not provide a DataBuffer, thus the management page is filled with padding bytes */
  if (UserJobParameter.JobType == FEE_30_SMALLSECTOR_WRITE_JOB)
  {
    for (LoopCounter = 0; LoopCounter < FillLength; LoopCounter++)
    {
      Fee_30_SmallSector_Ih_WriteBuffer[FEE_30_SMALLSECTOR_MANAGEMENT_SIZE + LoopCounter] = UserJobParameter.DataBufferPtr[LoopCounter]; /* SBSW_FEE_30_SMALLSECTOR_26 */
    }
  }

  /* #50 Save write parameters for compare job */
  CompareParameter->Fee_30_SmallSector_Ih_CompareAddress = Fee_30_SmallSector_Ih_GetManagementAddress(Instance); /* SBSW_FEE_30_SMALLSECTOR_25 */ /* SBSW_FEE_30_SMALLSECTOR_29 */
  CompareParameter->Fee_30_SmallSector_Ih_CompareBufferPtr = Fee_30_SmallSector_Ih_WriteBuffer; /* SBSW_FEE_30_SMALLSECTOR_25 */
  CompareParameter->Fee_30_SmallSector_Ih_CompareLength = Fee_30_SmallSector_Ph_GetPartitionWriteAlignment(); /* SBSW_FEE_30_SMALLSECTOR_25 */

  return Fee_30_SmallSector_Fls_Write(Fee_30_SmallSector_Ih_GetManagementAddress(Instance), Fee_30_SmallSector_Ih_WriteBuffer, Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()); /* SBSW_FEE_30_SMALLSECTOR_29 */ /* SBSW_FEE_30_SMALLSECTOR_27 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_WritePayload()
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
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WritePayload(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
        Fee_30_SmallSector_UserJobParameterType UserJobParameter, Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter)
{
  uint16 pageSize;// = Fee_30_SmallSector_Ph_GetPartitionWriteAlignment();
  /* #10 No internal buffer is used for writing the remaining payload bytes */
  Fee_30_SmallSector_AddressType startAddress ;//= //Fee_30_SmallSector_Ih_GetManagementAddress(Instance) + pageSize; /* SBSW_FEE_30_SMALLSECTOR_29 */
  uint16 BufferIndex=0;
  uint16 length;
  length=UserJobParameter.Length;
  startAddress=HAL_GetNvmBlockAddress(UserJobParameter.Blockid);
  return Fee_30_SmallSector_Fls_Write(startAddress, &(UserJobParameter.DataBufferPtr[BufferIndex]), length ); /* SBSW_FEE_30_SMALLSECTOR_28 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_WriteLastPage()
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
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteLastPage(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
    Fee_30_SmallSector_UserJobParameterType UserJobParameter, Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter)
{
  uint16 LoopCounter;
  uint16 BufferIndex;
  Fee_30_SmallSector_AddressType startAddress;
  uint16 PageSize = Fee_30_SmallSector_Ph_GetPartitionWriteAlignment();

  /* #10 Calculate the amount of data bytes which need to be written to last page */
  uint16 ResidualLength = (uint16) (Fee_30_SmallSector_Ih_GetInstanceDataLength(Instance) +  FEE_30_SMALLSECTOR_MANAGEMENT_SIZE) % PageSize; /* SBSW_FEE_30_SMALLSECTOR_29 */

  /* #11 In case ResidualLength == 0, no PayloadPages have been written and DataLength is aligned to page boundary */
  /* #12 This will always happen if DataLength = (2 * PageSize) - MgmtSize */
  if (ResidualLength == 0u)
  {
    /* #13 One full page will be written */
    ResidualLength = PageSize;
  }

  /* #20 Calculate index in user buffer of residual data bytes */
  BufferIndex = Fee_30_SmallSector_Ih_GetInstanceDataLength(Instance) - ResidualLength; /* SBSW_FEE_30_SMALLSECTOR_29 */

  /* #30 Calculate start address for last page: MgmtAddress + ManagementSize + AlreadyWrittenBytes */
  startAddress = Fee_30_SmallSector_Ih_GetManagementAddress(Instance) + FEE_30_SMALLSECTOR_MANAGEMENT_SIZE + BufferIndex; /* SBSW_FEE_30_SMALLSECTOR_29 */


  /* #50 Prepare write buffer with erased value */
  Fee_30_SmallSector_Ih_FillBufferWithErasedValue();

  /* #60 Store remaining payload bytes in write buffer */
  for (LoopCounter = 0; LoopCounter < ResidualLength; LoopCounter++)
  {
    Fee_30_SmallSector_Ih_WriteBuffer[LoopCounter] = UserJobParameter.DataBufferPtr[BufferIndex]; /* SBSW_FEE_30_SMALLSECTOR_26 */
    BufferIndex++;
  }

  /* #70 Save write parameters for compare job */
  CompareParameter->Fee_30_SmallSector_Ih_CompareAddress = startAddress; /* SBSW_FEE_30_SMALLSECTOR_25 */
  CompareParameter->Fee_30_SmallSector_Ih_CompareBufferPtr = Fee_30_SmallSector_Ih_WriteBuffer; /* SBSW_FEE_30_SMALLSECTOR_25 */
  CompareParameter->Fee_30_SmallSector_Ih_CompareLength = PageSize; /* SBSW_FEE_30_SMALLSECTOR_25 */

  return Fee_30_SmallSector_Fls_Write(startAddress, Fee_30_SmallSector_Ih_WriteBuffer, PageSize); /* SBSW_FEE_30_SMALLSECTOR_28 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_WriteEndPattern()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteEndPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
    Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter)
{

  /* #10 Prepare write buffer with static pattern value */
  /* #11 Amount of data bytes depend on write alignment */
  Fee_30_SmallSector_Ih_FillBufferWithStaticPattern();

  /* #20 Save write parameters for compare job */
  CompareParameter->Fee_30_SmallSector_Ih_CompareAddress = Fee_30_SmallSector_Ih_GetEndPatternAddress(Instance); /* SBSW_FEE_30_SMALLSECTOR_25 */ /* SBSW_FEE_30_SMALLSECTOR_29 */
  CompareParameter->Fee_30_SmallSector_Ih_CompareBufferPtr = Fee_30_SmallSector_Ih_WriteBuffer; /* SBSW_FEE_30_SMALLSECTOR_25 */
  CompareParameter->Fee_30_SmallSector_Ih_CompareLength = Fee_30_SmallSector_Ph_GetPartitionWriteAlignment(); /* SBSW_FEE_30_SMALLSECTOR_25 */

  return Fee_30_SmallSector_Fls_Write(Fee_30_SmallSector_Ih_GetEndPatternAddress(Instance), Fee_30_SmallSector_Ih_WriteBuffer, Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()); /* SBSW_FEE_30_SMALLSECTOR_29 */ /* SBSW_FEE_30_SMALLSECTOR_27 */
}

/**********************************************************************************************************************
 *  Fee_30_SmallSector_Ih_VerifyData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_VerifyData(Fee_30_SmallSector_Ih_CompareParameterType CompareParameter)
{
  return Fee_30_SmallSector_Fls_Compare(CompareParameter.Fee_30_SmallSector_Ih_CompareAddress, CompareParameter.Fee_30_SmallSector_Ih_CompareBufferPtr,
          CompareParameter.Fee_30_SmallSector_Ih_CompareLength); /* SBSW_FEE_30_SMALLSECTOR_28 */
}


#define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA L:LongInfixName */

/* SBSW_JUSTIFICATION_BEGIN
    \ID SBSW_FEE_30_SMALLSECTOR_21
      \DESCRIPTION The function writes to the object member referenced by parameter Instance of structure type
                   Fee_30_SmallSector_Ih_InstanceType.
      \COUNTERMEASURE \N The caller has to provide a valid reference to a parameter of type Fee_30_SmallSector_Ih_InstanceType

    \ID SBSW_FEE_30_SMALLSECTOR_22
      \DESCRIPTION Array write access of parameter Fee_30_SmallSector_Ih_WriteBuffer in for-loop at index 0 to 'FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT - 1'.
      \COUNTERMEASURE \N Array write access is not critical because both the upper limit of the for-loop and the size
                         of the array parameter is determined by #define FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT. The lower limit (0)
                         of the for-loop is legitimate as well.

    \ID SBSW_FEE_30_SMALLSECTOR_23
      \DESCRIPTION The function Fee_30_SmallSector_Ih_CorrectSingleBitFlips writes to the object referenced by parameter ManagementByte
      \COUNTERMEASURE \T TCASE-391754
                         The test ensures that single bit flip correction of management byte at valid addresses is performed.
                         The caller has to ensure that the parameter referenced by ManagementByte is valid.

    \ID SBSW_FEE_30_SMALLSECTOR_24
      \DESCRIPTION Array parameter Fee_30_SmallSector_Ih_WriteBuffer is accessed at index 0
      \COUNTERMEASURE \N Index 0 is always valid for accessing an array.

    \ID SBSW_FEE_30_SMALLSECTOR_25
      \DESCRIPTION The function writes to the object member referenced by parameter CompareParameter of structure type
                   Fee_30_SmallSector_Ih_CompareParameterType.
      \COUNTERMEASURE \N The compiler performs type check and therefore assures that write access to member of
                         referenced parameter CompareParameter is valid.

    \ID SBSW_FEE_30_SMALLSECTOR_26
      \DESCRIPTION Array Fee_30_SmallSector_Ih_WriteBuffer of size FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT is accessed with max index equal to
                   any configured partition's write alignment.
      \COUNTERMEASURE \M [CM_FEE_30_SMALLSECTOR_1]

    \ID SBSW_FEE_30_SMALLSECTOR_27
      \DESCRIPTION Address of first element of local array parameter is passed to a function
      \COUNTERMEASURE \N Reference to local parameter is valid

    \ID SBSW_FEE_30_SMALLSECTOR_28
      \DESCRIPTION Function is called with pointer to a data buffer
      \COUNTERMEASURE \N Caller ensures that pointer passed to service is valid

    \ID SBSW_FEE_30_SMALLSECTOR_29
      \DESCRIPTION Function is called with pointer to an instance object of type Fee_30_SmallSector_Ih_InstanceConstPointerType or Fee_30_SmallSector_Ih_InstanceVarPointerType
      \COUNTERMEASURE \N Instance parameter is passed to function via input parameter, thus caller ensures that parameter referenced
                         by pointer is valid.
SBSW_JUSTIFICATION_END */


/*
\CM CM_FEE_30_SMALLSECTOR_1 Verify that size of all configured write alignments is equal or smaller than FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT.
 */

