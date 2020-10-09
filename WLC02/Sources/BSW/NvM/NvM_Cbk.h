/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NvM_Cbk.h
 *    Component:  MemService_AsrNvM
 *       Module:  NvM
 *    Generator:  -
 *
 *  Description:  This file declares callback functions NvM_JobEndNotification and NvM_JobErrorNotification
 *
 *********************************************************************************************************************/

/* Do not modify this file! */

/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
#if (!defined NVM_CBK_H_)
#define NVM_CBK_H_

/**********************************************************************************************************************
 * VERSION IDENTIFICATION
 *********************************************************************************************************************/
#define NVM_CBK_MAJOR_VERSION    (5u)
#define NVM_CBK_MINOR_VERSION    (8u)
#define NVM_CBK_PATCH_VERSION    (0u)

/**********************************************************************************************************************
 * CALLBACK FUNCTIONS
 *********************************************************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h"

/* Callbacks are public, i.e. they will be called from outside of the NvM.
* Usually this means "from far away" (another segment)
*/

/**********************************************************************************************************************
 * NvM_JobEndNotification
 *********************************************************************************************************************/
/*! \brief If invoked, it will set the current pending job's result to NVM_REQ_OK.
 *  \details The function does nothing in case the NvM is running in polling mode! (empty function)
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_JobEndNotification(void);

/**********************************************************************************************************************
 * NvM_JobErrorNotification
 *********************************************************************************************************************/
/*! \brief If invoked, it will check the underlying module's job result and set current NvM pending job's result accordingly.
 *  \details The function does nothing in case the NvM is running in polling mode! (empty function)
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_JobErrorNotification(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif
/*---- End of File ---------------------------------------------------------*/
