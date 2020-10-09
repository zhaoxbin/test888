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
 *         \file  Fee_30_SmallSector_Cbk.h
 *        \brief  FEE callback header provides callback services of FEE module to Flash driver
 *
 *      \details  FEE callback header provides callback services of FEE module to Flash driver. These services are called
 *                by Flash driver upon job end if Polling Mode is deactivated. In case the Flash driver finishes a job
 *                successfully Fee_30_SmallSector_JobEndNotification() is called. On the other hand, in case of erroneous job end
 *                Fee_30_SmallSector_JobErrorNotification() is called.
 *
 *********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/
#ifndef FEE_30_SMALLSECTOR_CBK_H
# define FEE_30_SMALLSECTOR_CBK_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define FEE_30_SMALLSECTOR_CBK_MAJOR_VERSION    (2)
# define FEE_30_SMALLSECTOR_CBK_MINOR_VERSION    (1)
# define FEE_30_SMALLSECTOR_CBK_PATCH_VERSION    (0)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 *  Fee_30_SmallSector_JobEndNotification()
 *********************************************************************************************************************/
/*!
 * \brief      Sets the FEE internal job result of Flash driver
 * \details    Sets the FEE internal job result of Flash driver in case of successful job ending
 * \pre        FEE_30_SMALLSECTOR_FLS_POLLING_MODE is disabled
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-109016
 * \trace DSGN-Fee22976
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_JobEndNotification(void);

/**********************************************************************************************************************
 *  Fee_30_SmallSector_JobErrorNotification()
 *********************************************************************************************************************/
/*!
 * \brief      Sets the FEE internal job result of Flash driver
 * \details    Sets the FEE internal job result of Flash driver in case of erroneous job ending
 * \pre        FEE_30_SMALLSECTOR_FLS_POLLING_MODE is disabled
 * \context    TASK
 * \reentrant  FALSE
 * \synchronous TRUE
 * \trace CREQ-109017
 * \trace DSGN-Fee22976
 */
FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_JobErrorNotification(void);

# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h"

#endif /* FEE_30_SMALLSECTOR_CBK_H */
/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Cbk.h
 *********************************************************************************************************************/
