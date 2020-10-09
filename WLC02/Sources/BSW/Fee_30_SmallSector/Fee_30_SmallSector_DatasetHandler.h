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
 *          \file  Fee_30_SmallSector_DatasetHandler.h
 *         \brief  Fee Sub-component DatasetHandler header file
 *
 *       \details  DatasetHandler sub-component is responsible for management and initialization of dataset relevant data.
 *                 DatasetHandler provides public services to other FEE sub-components to access block dataset data.
 *
 *********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/

#ifndef FEE_30_SMALLSECTOR_DATASET_HANDLER_H
# define FEE_30_SMALLSECTOR_DATASET_HANDLER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "Fee_30_SmallSector.h"
# include "Fee_30_SmallSector_InstanceHandler.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef enum
{
  DATASET_ERASE_PATTERN_1 = 0,
  DATASET_ERASE_PATTERN_2
}Fee_30_SmallSector_Dh_ErasePatternType;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
  Fee_30_SmallSector_30_SmallSector_Dh_Init()
**********************************************************************************************************************/
/*!
 * \brief      Initializes dataset relevant data
 * \details    Initializes dataset relevant data
 * \param[in]  BlockNumber
 * \param[in]  DataLength
 * \param[in]  NumberOfInstances
 * \param[in]  BlockStartAddress
 * \param[in]  AddressAlignment
 * \pre        Module is initialized
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace DSGN-Fee22974
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_Init(uint16 BlockNumber, uint16 DataLength,
        uint8 NumberOfInstances, Fee_30_SmallSector_AddressType BlockStartAddress, uint16 AddressAlignment);

/**********************************************************************************************************************
  Fee_30_SmallSector_30_SmallSector_Dh_GetDataLength()
**********************************************************************************************************************/
/*!
 * \brief      Returns data length of one instance contained in current dataset
 * \details    Returns data length of one instance contained in current dataset
 * \return     DataLength
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_GetDataLength(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_GetFirstInstanceAddress()
 **********************************************************************************************************************/
/*!
 * \brief      Returns start address of first instance in dataset
 * \details    Returns start address of first instance in dataset
 * \return     FirstInstanceStartAddress
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_GetFirstInstanceAddress(void);

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_GetLastSectorIndex()
 **********************************************************************************************************************/
/*!
 * \brief      Calculates index of last Flash sector in dataset
 * \details    Calculates index of last Flash sector in dataset
 * \return     LastSectorIndex
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (sint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_GetLastSectorIndex(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_PrepareNextInstance()
**********************************************************************************************************************/
/*!
 * \brief      Prepares properties of next instance to read and stores values in Instance object
 * \details    Calculates addresses of next instance and resets all other values in order to prepare for ReadManagement job
 * \param[in]  Instance
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_PrepareNextInstance(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_EraseSector()
**********************************************************************************************************************/
/*!
 * \brief      Erases Flash sector specified by sector index
 * \details    Erases Flash sector of current dataset specified by sector index
 * \return     E_OK: Erase request to FLS driver was successful
 * \return     E_NOT_OK: Erase request to FLS driver failed
 * \param[in]  index of current dataset's sector to be erased
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_EraseSector(uint16 sectorIndex);

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_WriteErasePattern()
**********************************************************************************************************************/
/*!
 * \brief      Writes the static pattern
 * \details    Writes the static pattern which is addressed by the input parameter
 * \param[in]  pattern - specifies the pattern which is accessed
 * \return     E_OK: Write request to FLS driver was successful
 * \return     E_NOT_OK: Write request to FLS driver was rejected
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_WriteErasePattern(Fee_30_SmallSector_Dh_ErasePatternType pattern);

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_ReadErasePattern()
**********************************************************************************************************************/
/*!
 * \brief      Reads content of the erase pattern
 * \details    Reads content of the erase pattern which is addressed by the input parameter
 * \param[in]  pattern - specifies the pattern which is accessed
 * \return     E_OK: Read request to FLS driver was successful
 * \return     E_NOT_OK: Read request to FLS driver was rejected
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_ReadErasePattern(Fee_30_SmallSector_Dh_ErasePatternType pattern);

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_BlankCheckErasePattern()
**********************************************************************************************************************/
/*!
 * \brief      Performs blank check on content of the erase pattern
 * \details    Performs blank check on content of the erase pattern which is addressed by the input parameter
 * \param[in]  pattern - specifies the pattern which is accessed
 * \return     E_OK: BlankCheck request to FLS driver was successful
 * \return     E_NOT_OK: BlankCheck request to FLS driver was rejected
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_BlankCheckErasePattern(Fee_30_SmallSector_Dh_ErasePatternType pattern);

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_CheckErasePattern()
 **********************************************************************************************************************/
/*!
 * \brief      Checks if first page of dataset is erased/blank
 * \details    Performs either BlankCheck or Read on first page of dataset, which is reserved for the ErasePattern
 * \return     E_OK: BlankCheck/Read request to FLS driver was successful
 * \return     E_NOT_OK: BlankCheck/Read request to FLS driver was rejected
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_CheckErasePattern(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_30_SmallSector_Dh_IsLastInstance()
**********************************************************************************************************************/
/*!
 * \brief      Checks if passed instance is last instance in dataset
 * \details    Checks if passed instance is last instance in dataset
 * \param[in]  Instance
 * \return     TRUE: Instance is last instance index in dataset
 * \return     FALSE: Instance is not last instance index in dataset
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_IsLastInstance(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
 Fee_30_SmallSector_Dh_IsFirstInstanceAndBlank()
 **********************************************************************************************************************/
/*!
 * \brief      Checks if passed instance is first instance in dataset and if it's status is blank
 * \details    Checks if passed instance is first instance in dataset and if it's status is blank
 * \param[in]  Instance
 * \return     TRUE: Instance is first instance in dataset and blank
 * \return     FALSE: else
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_IsFirstInstanceAndBlank(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_IsErasePatternBlank()
**********************************************************************************************************************/
/*!
 * \brief      Checks if recently read erase pattern only contains the erased value
 * \details    Checks if recently read erase pattern only contains the erased value
 * \return     TRUE: Erase pattern is blank
 * \return     FALSE: Erase pattern is not blank
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_IsErasePatternBlank(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Dh_IsErasePatternValid()
**********************************************************************************************************************/
/*!
 * \brief      Checks if recently read erase pattern only contains the correct pattern value
 * \details    Checks if recently read erase pattern only contains the correct pattern value
 * \return     TRUE: Erase pattern is valid
 * \return     FALSE: Erase pattern is not valid
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Dh_IsErasePatternValid(void);


# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h"

#endif /* FEE_30_SMALLSECTOR_DATASET_HANDLER_H */

/* PRQA L:LongInfixName */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_DatasetHandler.h
 *********************************************************************************************************************/
