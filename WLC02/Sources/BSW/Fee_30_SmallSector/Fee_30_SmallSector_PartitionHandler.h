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
 *         \file  Fee_30_SmallSector_PartitionHandler.h
 *        \brief  Fee Sub-component PartitionHandler header file
 *
 *      \details  PartitionHandler is responsible for management and initialization of partition relevant data.
 *                PartitionHandler provides public services to other sub-components to access partition relevant data.
 *
 *********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/

#ifndef FEE_30_SMALLSECTOR_PARTITION_HANDLER_H
# define FEE_30_SMALLSECTOR_PARTITION_HANDLER_H

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
  Fee_30_SmallSector_Ph_Init()
**********************************************************************************************************************/
/*!
 * \brief       Initializes Partition Handler
 * \details     Local parameter Fee_30_SmallSector_Ph_PartitionIndex is initialized with index of partition that holds the current BlockNumber
 * \param[in]   BlockNumber
 * \pre         Module is uninitialized
 * \context     TASK
 * \reentrant   FALSE
 * \synchronous TRUE
 * \trace DSGN-Fee23152
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_Init(uint16 BlockNumber);

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetPartitionStartAddress()
**********************************************************************************************************************/
/*!
 * \brief      Returns partition start address
 * \details    Returns partition start address belonging to partition, in which current block number is contained
 * \return     Partition start address
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetPartitionStartAddress(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetPartitionWriteAlignment()
**********************************************************************************************************************/
/*!
 * \brief      Returns write alignment of partition
 * \details    Returns write alignment, belonging to partition in which current block number is contained
 * \return     Partition write alignment
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetPartitionWriteAlignment(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetPartitionAddressAlignment()
**********************************************************************************************************************/
/*!
 * \brief      Returns address alignment of partition
 * \details    Returns address alignment, belonging to partition in which current block number is contained
 * \return     Partition address alignment
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetPartitionAddressAlignment(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetPartitionReadAlignment()
**********************************************************************************************************************/
/*!
 * \brief      Returns read alignment of partition
 * \details    Returns read alignment, belonging to partition in which current block number is contained
 * \return     Partition read alignment
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetPartitionReadAlignment(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetFlsApiPtr()
**********************************************************************************************************************/
/*!
 * \brief      Returns reference to APIs of FLS driver
 * \details    Returns reference to APIs of FLS driver which is related to current BlockNumber via configured partition
 * \return     FLS API Pointer
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_FlsApiPtrType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetFlsApiPtr(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetFlsEraseValue()
**********************************************************************************************************************/
/*!
 * \brief      Returns erase value of FLS driver
 * \details    Returns erase value of FLS driver which is related to current BlockNumber via configured partition
 * \return     Fls Erase Value
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint8, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetFlsEraseValue(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Ph_GetBlankCheckApi()
**********************************************************************************************************************/
/*!
 * \brief      Returns if referenced FLS module provides a blank check API
 * \details    Returns if referenced FLS module provides a blank check API
 * \return     TRUE: BlankCheck API provided
 *             FALSE: No BlankCheck API provided
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ph_GetBlankCheckApi(void);

# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h"

#endif /* FEE_30_SMALLSECTOR_PARTITION_HANDLER_H */

/* PRQA L:LongInfixName */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_PartitionHandler.h
 *********************************************************************************************************************/
