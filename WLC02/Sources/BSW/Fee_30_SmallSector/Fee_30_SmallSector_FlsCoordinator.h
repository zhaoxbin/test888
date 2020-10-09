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
 *        \file  Fee_30_SmallSector_FlsCoordinator.h
 *        \brief  FlsCoordinator provides FLS specific services to all FEE sub-components
 *
 *      \details  FlsCoordinator provides FLS interface to all FEE sub-components. FlsCoordinator is responsible for
 *                PollingMode and Callback notifications of Flash driver.
 *
 *********************************************************************************************************************/


#ifndef FEE_30_SMALLSECTOR_FLS_COORDINATOR_H
# define FEE_30_SMALLSECTOR_FLS_COORDINATOR_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "MemIf_Types.h"


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_Read()
**********************************************************************************************************************/
/*!
 * \brief      Reads Length bytes from Address in Flash to BufferPtr
 * \details    Reads Length bytes from Address in Flash to BufferPtr
 * \param[in]  Address
 * \param[in]  BufferPtr
 * \param[in]  Length
 * \return     E_OK: Read request was accepted by Flash driver
 * \return     E_NOT_OK: Read request was rejected by Flash driver
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_Read(Fee_30_SmallSector_AddressType Address,
    Fee_30_SmallSector_DataPtr BufferPtr, uint16 Length);

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_Write()
**********************************************************************************************************************/
/*!
 * \brief      Writes Length bytes from Buffer pointed to by BufferPtr to Flash at Address
 * \details    Writes Length bytes from Buffer pointed to by BufferPtr to Flash at Address
 * \param[in]  Address
 * \param[in]  BufferPtr
 * \param[in]  Length
 * \return     E_OK: Write request was accepted by Flash driver
 * \return     E_NOT_OK: Write request was rejected by Flash driver
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_Write(Fee_30_SmallSector_AddressType Address,
    Fee_30_SmallSector_ConstDataPtr BufferPtr, uint16 Length);

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_Compare()
**********************************************************************************************************************/
/*!
 * \brief      Compares Length bytes from Flash at Address with Buffer pointed to by BufferPtr
 * \details    Compares Length bytes from Flash at Address with Buffer pointed to by BufferPtr
 * \param[in]  Address
 * \param[in]  BufferPtr
 * \param[in]  Length
 * \return     E_OK: Compare request was accepted by Flash driver
 * \return     E_NOT_OK: Compare request was rejected by Flash driver
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_Compare(Fee_30_SmallSector_AddressType Address,
    Fee_30_SmallSector_ConstDataPtr BufferPtr, uint16 Length);

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_Erase()
**********************************************************************************************************************/
/*!
 * \brief      Erases Length bytes in Flash at Address
 * \details    Erases Length bytes in Flash at Address
 * \param[in]  Address
 * \param[in]  Length
 * \return     E_OK: Erase request was accepted by Flash driver
 * \return     E_NOT_OK: Erase request was rejected by Flash driver
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_Erase(Fee_30_SmallSector_AddressType Address, uint16 Length);

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_BlankCheck()
**********************************************************************************************************************/
/*!
 * \brief      Performs blank check on Length bytes in Flash at Address
 * \details    Performs blank check on Length bytes in Flash at Address
 * \param[in]  Address
 * \param[in]  Length
 * \return     E_OK: BlankCheck request was accepted by Flash driver
 * \return     E_NOT_OK: BlankCheck request was rejected by Flash driver
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous FALSE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_BlankCheck(Fee_30_SmallSector_AddressType Address, uint16 Length);

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_SetCurrentFlsJobResult()
**********************************************************************************************************************/
/*!
 * \brief      Sets job result of FLS module
 * \details    Sets current job result of FLS module upon call of FEE's callback functions by FLS driver.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_SetCurrentFlsJobResult(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_GetJobResult()
**********************************************************************************************************************/
/*!
 * \brief      Returns current job result of active FLS module
 * \details    Returns current job result of active FLS module. Service distinguishes between Polling Mode and
 *             callback service usage.
 * \return     Job result of FLS
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_GetJobResult(void);


/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_GetStatus()
**********************************************************************************************************************/
/*!
 * \brief      Returns current status of active FLS module
 * \details    Returns current status of active FLS module.
 * \return     Status of FLS
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_GetStatus(void);


# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* FEE_30_SMALLSECTOR_FLS_COORDINATOR_H */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_FlsCoordinator.h
 *********************************************************************************************************************/
