/* \trace SPEC-1878 */

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
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  CanIf_Cbk.h
 *        \brief  CAN Interface callback functions header file.
 *
 *      \details  This file contains the declaration of the callback function prototypes of the AUTOSAR 
 *                CAN Interface module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Ruediger Naas                 visrna        Vector Informatik GmbH
 *  Eugen Stripling               visseu        Vector Informatik GmbH
 *  Carsten Gauglitz              visgaz        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  05.00.00  2012-07-02  visrna  ESCAN00060132 Support ASR 4.0 Rev 3
 *  05.01.00  2015-03-26  visseu  ESCAN00080296 FEAT-427: SafeBSW Step I
 *  05.02.00  2015-11-30  visrna  ESCAN00086059 FEAT-1429: Gateway Optimization
 *  05.02.01  2016-10-10  visrna  ESCAN00092243 Rework of  Doxygen comments
 *  05.03.00  2017-08-04  visseu  ESCAN00096180 FEAT-2946 - Supporting 3rd party communication MCAL CAN driver according to AR 4.2
 *  05.04.00  2018-10-31  visgaz  STORYC-6847   MISRA-C:2012: If_AsrIfCan
 *                                STORYC-7095   Adapt to new template
 *  05.05.00  2018-11-29  visgaz  STORYC-7176   Remove Parameter CanIfMultipleBasicCANTxObjects
 *********************************************************************************************************************/

#if !defined (CANIF_CBK_H)
# define CANIF_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
 
# include "CanIf_Cfg.h"
/* CanIf_Types.h  is included by CanIf_Cfg.h */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# define CANIF_CBK_MAJOR_VERSION   0x05u
# define CANIF_CBK_MINOR_VERSION   0x05u
# define CANIF_CBK_PATCH_VERSION   0x00u

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
# define CANIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* \trace SPEC-3696 */

/***********************************************************************************************************************
 *  CanIf_TxConfirmation()
 **********************************************************************************************************************/
/*! \brief       Confirmation for successful transmission.
 *  \details     -
 *  \param[in]   CanTxPduId: Internal ID of successful transmitted PDU.
 *  \pre         -
 *  \context     TASK/ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 *  \note        This function has the service id 0x13.
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_TxConfirmation(PduIdType CanTxPduId);

/***********************************************************************************************************************
 *  CanIf_RxIndicationAsr403()
 **********************************************************************************************************************/
/*! \brief       Indication about a received CAN message [ASR4.0.3].
 *  \details     This functions looks for if received CAN message matches one of the configured ones. If yes then the configured upper layer is notified.
 *  \param[in]   Hrh: Handle of hardware object
 *  \param[in]   CanId: CAN identifier of received message
 *  \param[in]   CanDlc: DLC of received message
 *  \param[in]   CanSduPtr: Pointer to data of received message
 *  \pre         -
 *  \context     TASK/ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 *  \note        This function has the service id 0x14.
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_RxIndicationAsr403(CanIf_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR)CanSduPtr);

/* void CanIf_CancelTxConfirmation(const Can_PduType *PduInfoPtr); */
# if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
#  if (CANIF_TRANSMIT_BUFFER_FIFO == STD_OFF)
#   if (CANIF_TRANSMIT_CANCELLATION == STD_ON)
/***********************************************************************************************************************
 *  CanIf_CancelTxConfirmation()
 **********************************************************************************************************************/
/*! \brief       The call of this API indicates about a canceled Tx message by the CAN driver.
 *  \details     -
 *  \param[in]   CanTxPduId: Handle of hardware object
 *  \param[in]   PduInfoPtr: Pointer to parameters of canceled Tx message
 *  \pre         -
 *  \context     TASK/ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANIF_TRANSMIT_BUFFER == STD_ON and CANIF_TRANSMIT_CANCELLATION == STD_ON
 *  \note        This function has the service id 0x15.
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_CancelTxConfirmation(PduIdType CanTxPduId, P2CONST(Can_PduType, AUTOMATIC, CANIF_CBK_DRV_VAR) PduInfoPtr);
#   endif
#  endif
# endif

/***********************************************************************************************************************
 *  CanIf_ControllerBusOff()
 **********************************************************************************************************************/
/*! \brief       Indication about an occurred BusOff-event
 *  \details     -
 *  \param[in]   ControllerId: ID of CAN channel for which the BusOff-event occurred
 *  \pre         -
 *  \context     TASK/ISR
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 *  \note        This function has the service id 0x16.
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_ControllerBusOff(uint8 ControllerId);

/* NON AUTOSAR callback functions */

# if (CANIF_CANCEL_SUPPORT_API == STD_ON)
/***********************************************************************************************************************
 *  CanIf_CancelTxNotification()
 **********************************************************************************************************************/
/*! \brief       CAN Interface is notified about a canceled PDU.
 *  \details     The confirmation is NOT passed to upper layers. Next message from Tx-queue is transmitted.
 *               Used for trigger-purpose to fill the free HW-object, after calling of CanIf_CancelTransmit().
 *  \param[in]   PduId: ID of canceled Tx-message
 *  \param[in]   IsCancelled: TRUE: Tx-message (PduId) was canceled, FALSE: Tx-message (PduId) was NOT canceled (it was transmitted)
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 *  \note        This function has the service id 0x16.
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_CancelTxNotification(PduIdType PduId, CanIf_CancelResultType IsCancelled);
# endif

# define CANIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* CANIF_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: CanIf_Cbk.h
 *********************************************************************************************************************/
