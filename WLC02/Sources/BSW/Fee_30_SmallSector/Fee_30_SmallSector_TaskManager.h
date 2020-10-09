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
 *        \file  Fee_30_SmallSector_TaskManager.h
 *       \brief  Fee Sub-component TaskManager source file
 *
 *     \details  TaskManager is responsible for processing asynchronous sub-components in correct order by calling the
 *               appropriate execution services. TaskManager is also responsible for canceling all active sub-components
 *               in case Fee_30_SmallSector_Cancel was called by user.
 *
 *********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/
#ifndef FEE_30_SMALLSECTOR_TASKMANAGER_H
# define FEE_30_SMALLSECTOR_TASKMANAGER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "Fee_30_SmallSector.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

typedef P2FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE, Fee_30_SmallSector_Tm_ExecuteServicePointerType)(void);
typedef P2FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE, Fee_30_SmallSector_Tm_CancelServicePointerType)(void);

# define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_Init()
**********************************************************************************************************************/
/*!
 * \brief      Initializes TaskManager
 * \details    Initializes TaskManager by clearing job stack and cancel stack
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Tm_Init (void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_AddTask()
**********************************************************************************************************************/
/*!
 * \brief      Adds passed execution and cancel services to job stack and cancel stack
 * \details    Adds passed execution and cancel services to job stack and cancel stack
 * \param[in]  ExecuteService
 * \param[in]  CancelService
 * \param[in]  Layer
 * \return     E_OK: Services were added correctly
 * \return     E_NOT_OK: Adding services failed. Stack position (layer) is not empty.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Tm_AddTask (Fee_30_SmallSector_Tm_ExecuteServicePointerType ExecuteService,
        Fee_30_SmallSector_Tm_CancelServicePointerType CancelService, uint8 Layer);

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_RemoveTask()
**********************************************************************************************************************/
/*!
 * \brief      Removes services from job stack and cancel stack
 * \details    Removes execution and cancel services from certain layer in job stack and cancel stack
 * \param[in]  ExecuteService
 * \param[in]  CancelService
 * \param[in]  Layer
 * \return     E_OK: Services were removed correctly
 * \return     E_NOT_OK: Containing services in stacks differ from passed services. No service was removed.
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Tm_RemoveTask (Fee_30_SmallSector_Tm_ExecuteServicePointerType ExecuteService,
        Fee_30_SmallSector_Tm_CancelServicePointerType CancelService, uint8 Layer);

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_ExecuteTask()
**********************************************************************************************************************/
/*!
 * \brief      Calls most recent execution service in job stack
 * \details    Calls service in job stack which was put there last
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Tm_ExecuteTask (void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Tm_CancelTasks()
**********************************************************************************************************************/
/*!
 * \brief      Calls all cancel services in cancel stack
 * \details    Calls all cancel services in cancel stack beginning with lowest layer (layer 3)
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Tm_CancelTasks (void);


# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h"

#endif /* FEE_30_SMALLSECTOR_TASKMANAGER_H */
/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_TaskManager.h
 *********************************************************************************************************************/
