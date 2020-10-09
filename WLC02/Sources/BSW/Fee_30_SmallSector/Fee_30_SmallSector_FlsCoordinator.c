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
 *        \file  Fee_30_SmallSector_FlsCoordinator.c
 *        \brief  FlsCoordinator provides FLS specific services to all FEE sub-components
 *
 *      \details  FlsCoordinator provides FLS interface to all FEE sub-components. FlsCoordinator is responsible for
 *                PollingMode and Callback notifications of Flash driver.
 *
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Fee_30_SmallSector.h"
#include "Fee_30_SmallSector_FlsCoordinator.h"
#include "Fee_30_SmallSector_PartitionHandler.h"

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#ifndef FEE_30_SMALLSECTOR_LOCAL /* COV_FEE_30_SMALLSECTOR_COMPATIBILITY */
# define FEE_30_SMALLSECTOR_LOCAL static
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#if (FEE_30_SMALLSECTOR_FLS_POLLING_MODE == STD_OFF)
# define FEE_30_SMALLSECTOR_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

FEE_30_SMALLSECTOR_LOCAL VAR(MemIf_JobResultType, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Fls_GlobalJobResult;

# define FEE_30_SMALLSECTOR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_GetJobResultFromFlash()
**********************************************************************************************************************/
/*!
 * \brief      Returns current job result of active FLS module
 * \details    Returns current job result of active FLS module by calling FLS's GetJobResult service.
 *             This service is used by Fee_30_SmallSector_JobEndNotification and by Fee_30_SmallSector_Fls_GetJobResult() in case of
 *             FLS Polling Mode enabled.
 * \return     Job result of FLS
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Fls_GetJobResultFromFlash(void);

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_SetResultPending()
**********************************************************************************************************************/
/*!
 * \brief      Initializes JobResult variable in case of callback mode
 * \details    Initializes JobResult variable in case of callback mode
 * \pre        -
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Fls_SetResultPending(void);

# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_GetJobResultFromFlash()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Fls_GetJobResultFromFlash(void)
{
  return Fee_30_SmallSector_Ph_GetFlsApiPtr()->GetJobResult(); /* SBSW_FEE_30_SMALLSECTOR_31 */
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_SetResultPending()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FEE_30_SMALLSECTOR_LOCAL FUNC(void, FEE_30_SMALLSECTOR_PRIVATE_CODE) Fee_30_SmallSector_Fls_SetResultPending(void)
{
#if (FEE_30_SMALLSECTOR_FLS_POLLING_MODE == STD_OFF)
  Fee_30_SmallSector_Fls_GlobalJobResult = MEMIF_JOB_PENDING;
#endif
}

# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#define FEE_30_SMALLSECTOR_START_SEC_CODE
#include "MemMap.h"     /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_Read()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_Read(Fee_30_SmallSector_AddressType Address,
    Fee_30_SmallSector_DataPtr BufferPtr, uint16 Length)
{
  Fee_30_SmallSector_Fls_SetResultPending(); /* PRQA S 2987 */ /* MD_FEE_30_SMALLSECTOR_SideEffects */
  return Fee_30_SmallSector_Ph_GetFlsApiPtr()->Read(Address, BufferPtr, Length); /* SBSW_FEE_30_SMALLSECTOR_31 */
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_Write()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_Write(Fee_30_SmallSector_AddressType Address,
    Fee_30_SmallSector_ConstDataPtr BufferPtr, uint16 Length)
{
  Fee_30_SmallSector_Fls_SetResultPending(); /* PRQA S 2987 */ /* MD_FEE_30_SMALLSECTOR_SideEffects */
  return Fee_30_SmallSector_Ph_GetFlsApiPtr()->Write(Address, BufferPtr, Length); /* SBSW_FEE_30_SMALLSECTOR_31 */
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_Compare()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_Compare(Fee_30_SmallSector_AddressType Address,
    Fee_30_SmallSector_ConstDataPtr BufferPtr, uint16 Length)
{
  Fee_30_SmallSector_Fls_SetResultPending(); /* PRQA S 2987 */ /* MD_FEE_30_SMALLSECTOR_SideEffects */
  return Fee_30_SmallSector_Ph_GetFlsApiPtr()->Compare(Address, BufferPtr, Length); /* SBSW_FEE_30_SMALLSECTOR_31 */
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_Erase()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_Erase(Fee_30_SmallSector_AddressType Address, uint16 Length)
{
  Fee_30_SmallSector_Fls_SetResultPending(); /* PRQA S 2987 */ /* MD_FEE_30_SMALLSECTOR_SideEffects */
  return Fee_30_SmallSector_Ph_GetFlsApiPtr()->Erase(Address, Length); /* SBSW_FEE_30_SMALLSECTOR_31 */
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_BlankCheck()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_BlankCheck(Fee_30_SmallSector_AddressType Address, uint16 Length)
{
  Fee_30_SmallSector_Fls_SetResultPending(); /* PRQA S 2987 */ /* MD_FEE_30_SMALLSECTOR_SideEffects */
  return Fee_30_SmallSector_Ph_GetFlsApiPtr()->BlankCheck(Address, Length); /* SBSW_FEE_30_SMALLSECTOR_31 */
}

#if (FEE_30_SMALLSECTOR_FLS_POLLING_MODE == STD_OFF)
/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_SetCurrentFlsJobResult()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_SetCurrentFlsJobResult(void)
{
  Fee_30_SmallSector_Fls_GlobalJobResult = Fee_30_SmallSector_Fls_GetJobResultFromFlash();
}
#endif

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_GetJobResult()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC (MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_GetJobResult(void)
{
#if (FEE_30_SMALLSECTOR_FLS_POLLING_MODE == STD_ON)
  /* #10 FEE module polls FLS module */
  return Fee_30_SmallSector_Fls_GetJobResultFromFlash();

#else
  /* #20 FLS module reports job result to FEE via callback services */
  return Fee_30_SmallSector_Fls_GlobalJobResult;

#endif
}

/**********************************************************************************************************************
  Fee_30_SmallSector_Fls_GetStatus()
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC (MemIf_StatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Fls_GetStatus(void)
{
  return Fee_30_SmallSector_Ph_GetFlsApiPtr()->GetStatus(); /* SBSW_FEE_30_SMALLSECTOR_31 */
}



#define FEE_30_SMALLSECTOR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* SBSW_JUSTIFICATION_BEGIN
    \ID SBSW_FEE_30_SMALLSECTOR_31
      \DESCRIPTION Function pointer from function pointer structure is called
      \COUNTERMEASURE \N  The compiler performs type check and therefore assures that valid function pointer is called.
                          Reference of pointer structure is retrieved by array access in Fee_30_SmallSector_PartitionHandler.c.
                          Used index Fee_30_SmallSector_Ph_PartitionIndex is never out of bounds, because it is initialized with
                          maximum value FEE_30_SMALLSECTOR_NUMBER_OF_PARTITIONS - 1, which also initializes the size of accessed
                          array Fee_30_SmallSector_PartitionConfigList.
SBSW_JUSTIFICATION_END */
