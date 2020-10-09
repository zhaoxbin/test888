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
 *          \file  Fee_30_SmallSector_BlockHandler.h
 *         \brief  Fee Sub-component BlockHandler header file
 *
 *       \details  BlockHandler sub-component is responsible for management and initialization of block relevant data.
 *                 BlockHandler provides public services to other FEE sub-components to access block relevant data.
 *
 *********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/

#ifndef FEE_30_SMALLSECTOR_BLOCK_HANDLER_H
# define FEE_30_SMALLSECTOR_BLOCK_HANDLER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "Fee_30_SmallSector.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
  Fee_30_SmallSector_Bh_Init()
**********************************************************************************************************************/
/*!
 * \brief       Initializes Block Handler
 * \details     BlockIndex and AbsoluteBlockAddress are initialized
 * \param[in]   BlockNumber
 * \param[in]   PartitionStartAddress
 * \pre         Module is uninitialized
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Bh_Init(uint16 BlockNumber, Fee_30_SmallSector_AddressType PartitionStartAddress);

/**********************************************************************************************************************
  Fee_30_SmallSector_Bh_GetBlockStartAddress()
**********************************************************************************************************************/
/*!
 * \brief      Returns start address of block
 * \details    Returns absolute start address of block in Flash
 * \return     AbsoluteBlockAddress
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Bh_GetBlockStartAddress(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Bh_GetDataLength()
**********************************************************************************************************************/
/*!
 * \brief      Returns data length
 * \details    Returns data length of single instance entity of block
 * \param[in]  BlockNumber
 * \return     DataLength of a single instance
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Bh_GetDataLength(uint16 BlockNumber);

/**********************************************************************************************************************
  Fee_30_SmallSector_Bh_GetNrOfInstances()
**********************************************************************************************************************/
/*!
 * \brief      Returns number of instances
 * \details    Returns number of instances configured for current block
 * \param[in]  BlockNumber
 * \return     NumberOfInstances
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint8, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Bh_GetNrOfInstances(uint16 BlockNumber);

#if (FEE_30_SMALLSECTOR_DEV_ERROR_DETECT == STD_ON)
/**********************************************************************************************************************
  Fee_30_SmallSector_Bh_GetNrOfDatasets()
**********************************************************************************************************************/
/*!
 * \brief      Returns number of datasets
 * \details    Returns number of datasets configured for current block
 * \param[in]  BlockNumber
 * \return     NumberOfDatasets
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint8, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Bh_GetNrOfDatasets(uint16 BlockNumber);

/**********************************************************************************************************************
  Fee_30_SmallSector_Bh_GetDatasetIndex()
**********************************************************************************************************************/
/*!
 * \brief      Returns dataset index of BlockNumber
 * \details    Returns dataset index of BlockNumber
 * \return     DatasetIndex
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Bh_GetDatasetIndex(uint16 BlockNumber);

/**********************************************************************************************************************
  Fee_30_SmallSector_Bh_IsImmediateData()
**********************************************************************************************************************/
/*!
 * \brief      Returns if the block is configured for immediate data
 * \details    Returns if the block is configured for immediate data
 * \param[in]  BlockNumber
 * \return     IsImmediateData
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Bh_IsImmediateData(uint16 BlockNumber);
#endif

/**********************************************************************************************************************
  Fee_30_SmallSector_Bh_HasVerificationEnabled()
**********************************************************************************************************************/
/*!
 * \brief      Returns if the block is configured to verify written data
 * \details    Returns if the block is configured to verify written data
 * \return     HasVerificationEnabled
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Bh_HasVerificationEnabled(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Bh_GetBlockIndex()
**********************************************************************************************************************/
/*!
 * \brief      Calculates block index from BlockNumber
 * \details    Calculates block index from BlockNumber by removing DatasetSelectionBits from BlockNumber
 * \param[in]  BlockNumber
 * \return     BlockIndex
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Bh_GetBlockIndex(uint16 BlockNumber);

# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h"

#endif /* FEE_30_SMALLSECTOR_BLOCK_HANDLER_H */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_BlockHandler.h
 *********************************************************************************************************************/
