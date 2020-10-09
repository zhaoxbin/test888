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
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  CanTp_Cbk.h
 *        \brief  CanTp callback definitions
 *
 *      \details  Function prototypes of CanTp callback and notification functions.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/
#if !defined (CANTP_CBK_H)
#define CANTP_CBK_H


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "CanTp.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CANTP_START_SEC_CODE
#include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* --- Mandatory Callbacks from CanIf ------------------------------------------------------------------------------ */
/**********************************************************************************************************************
 *  CanTp_RxIndication()
 *********************************************************************************************************************/
/*! \brief         Notifies the CanTp of the reception of a CAN frame
 *  \details       This function is called by the CAN Interface after a successful reception of an N-PDU.
 *  \param[in]     RxPduId                Rx N-PDU Id of the CAN message, which has been received.
 *  \param[in]     PduInfoPtr             Pointer to received N-PDU payload and metadata (if configured).
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \pre           -
 *  \trace         CREQ-102806
 *********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr);

/**********************************************************************************************************************
 *  CanTp_TxConfirmation()
 *********************************************************************************************************************/
/*! \brief         Notifies the CanTp of the successful transmission of a CAN frame
 *  \details       This function is called by the CAN Interface to confirm the successful transmission of an N-PDU.
 *  \param[in]     TxPduId                Tx N-PDU Id of the CAN message, which has been transmitted.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \pre           A CanTp frame has been transmitted before through CanIf_Transmit()
 *  \trace         CREQ-102807, CREQ-102808
 *********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_TxConfirmation(PduIdType TxPduId);


/* --- Optional Call-back Functions -------------------------------------------------------------------------------- */
#if (CANTP_STMIN_BY_APPL == STD_ON)
/**********************************************************************************************************************
 *  CanTp_StopSeparationTime()
 *********************************************************************************************************************/
/*! \brief         Notifies the CanTp that STmin expired
 *  \details       This function is called by an application CDD in case STmin handling is not done by the CanTp.
 *  \param[in]     CanTpTxSduId              Tx N-SDU Id of connection for which STmin expired.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \config        This API is only available if CANTP_STMIN_BY_APPL = STD_ON
 *  \pre           The notification function "Appl_CanTpStartSeparationTime()" must have been called before and must have
 *                 returned 'TRUE' (i.e. the application accepted to do the STmin handling).
 *  \trace         DSGN-CanTp24743
 *********************************************************************************************************************/
FUNC(void, CANTP_CODE) CanTp_StopSeparationTime(PduIdType CanTpTxSduId);
#endif


/* --- Optional Call-out Functions --------------------------------------------------------------------------------- */
#if (CANTP_APPL_RX_SF_INDICATION == STD_ON)
/**********************************************************************************************************************
 *  Appl_CanTpRxSFIndication()
 *********************************************************************************************************************/
/*! \brief         Indicates reception of a single frame
 *  \details       The function is called upon successful reception of a single frame N-PDU before the call of
 *                 PduR_CanTpStartOfReception().
 *  \param[in]     PduRRxPduId            PduId of the connection, which is defined by the PduR; the same Id is used
 *                                        for calls to PduR_CanTpRxIndication().
 *  \param[in]     PduInfoPtr             Pointer to received N-PDU data.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \config        This call-out is only available if CANTP_APPL_RX_SF_INDICATION is set to STD_ON by user config.
 *  \pre           -
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) Appl_CanTpRxSFIndication(PduIdType PduRRxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr);
#endif

#if (CANTP_APPL_RX_FF_INDICATION == STD_ON)
/**********************************************************************************************************************
 *  Appl_CanTpRxFFIndication()
 *********************************************************************************************************************/
/*! \brief         Indicates reception of a first frame
 *  \details       The function is called upon successful reception of a first frame N-PDU before the call of
 *                 PduR_CanTpStartOfReception().
 *  \param[in]     PduRRxPduId            PduId of the connection, which is defined by the PduR; the same Id is used
 *                                        for calls to PduR_CanTpRxIndication().
 *  \param[in]     PduInfoPtr             Pointer to received N-PDU data.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \config        This call-out is only available if CANTP_APPL_RX_FF_INDICATION is set to STD_ON by user config.
 *  \pre           -
 **********************************************************************************************************************/
FUNC(void, CANTP_CODE) Appl_CanTpRxFFIndication(PduIdType PduRRxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr);
#endif

#if (CANTP_APPL_RX_CF_INDICATION == STD_ON)
/**********************************************************************************************************************
 *  Appl_CanTpRxCFIndication()
 *********************************************************************************************************************/
/*! \brief         Indicates reception of a consecutive frame
 *  \details       The function is called upon successful reception of a consecutive frame N-PDU before the call of
 *                 PduR_CanTpStartOfReception().
 *  \param[in]     PduRRxPduId            PduId of the connection, which is defined by the PduR; the same Id is used
 *                                        for calls to PduR_CanTpRxIndication().
 *  \param[in]     PduInfoPtr             Pointer to received N-PDU data.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \config        This call-out is only available if CANTP_APPL_RX_CF_INDICATION is set to STD_ON by user config.
 *  \pre           -
 *********************************************************************************************************************/
FUNC(void, CANTP_CODE) Appl_CanTpRxCFIndication(PduIdType PduRRxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr);
#endif

#if (CANTP_APPL_FRAME_TRANSMISSION == STD_ON)
/**********************************************************************************************************************
 *  Appl_CanTpFrameTransmission()
 *********************************************************************************************************************/
/*! \brief         Indicates a successful N-PDU transmission request
 *  \details       The function is called if transmission of a CANTP N-PDU has successfully been started (CanIf_Transmit()
 *                 has been called and returned E_OK).
 *  \param[in]     CanIfTxPduId           PduId of the transmitted CAN message, which is defined by the CanIf; the same
 *                                        Id is used for calls to CanIf_Transmit().
 *  \param[in]     PduInfoPtr             Pointer to transmitted N-PDU data.
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \config        This call-out is only available if CANTP_APPL_FRAME_TRANSMISSION is set to STD_ON by user config.
 *  \pre           -
 *********************************************************************************************************************/
FUNC(void, CANTP_CODE) Appl_CanTpFrameTransmission(PduIdType CanIfTxPduId, P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) PduInfoPtr);
#endif

#if (CANTP_APPL_FRAME_CONFIRMATION == STD_ON)
/**********************************************************************************************************************
 *  Appl_CanTpFrameTransmission()
 *********************************************************************************************************************/
/*! \brief         Indicates successfully completed transmission of an N-PDU
 *  \details       Function is called if a CANTP N-PDU has successfully been transmitted (at the beginning of
 *                 CanTp_TxConfirmation()).
 *  \param[in]     CanIfTxPduId           PduId of the transmitted CAN message, which is defined by the CanIf; the same
 *                                        Id used for calls to CanIf_Transmit().
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different handles
 *  \synchronous   TRUE
 *  \config        This call-out is only available if CANTP_APPL_FRAME_CONFIRMATION is set to STD_ON by user config.
 *  \pre           -
 *********************************************************************************************************************/
FUNC(void, CANTP_CODE) Appl_CanTpFrameTxConfirmation(PduIdType CanIfTxPduId);
#endif

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"                                                                                                    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* CANTP_CBK_H */

/*********************************************************************************************************************
 *  END OF FILE: CanTp_Cbk.h
 ********************************************************************************************************************/

