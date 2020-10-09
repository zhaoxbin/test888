/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: PduR
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: PduR_CanTp.h
 *   Generation Time: 2020-02-04 16:15:32
 *           Project: WLC - Version 1.0
 *          Delivery: CBD1900162_D00
 *      Tool Version: DaVinci Configurator (beta) 5.19.29
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 ! BETA VERSION                                                                                                       !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 ! This version of DaVinci Configurator Pro and/or the related Basic Software Package is BETA software.               !
 ! BETA Software is basically operable, but not sufficiently tested, verified and/or qualified for use in series      !
 ! production and/or in vehicles operating on public or non-public roads.                                             !
 ! In particular, without limitation, BETA Software may cause unpredictable ECU behavior, may not provide all         !
 ! functions necessary for use in series production and/or may not comply with quality requirements which are         !
 ! necessary according to the state of the art. BETA Software must not be used in series production.                  !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**********************************************************************************************************************/

#if !defined (PDUR_CANTP_H)
# define PDUR_CANTP_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR_Cfg.h"

/**********************************************************************************************************************
 * GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/* \trace SPEC-629 */

#define PDUR_START_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */



/**********************************************************************************************************************
 * PduR_CanTpRxIndication
 *********************************************************************************************************************/
/*!
 * \brief    The function is called by the CanTp to indicate the complete reception of a CanTp I-PDU or to\n
 *           report an error that occurred during reception. The PDU Router evaluates the CanTp I-PDU handle and\n
 *           performs appropriate handle and port conversion. The call is routed to an upper Tp module using the\n
 *           appropriate I-PDU handle of the destination layer.
 * \param    id                              ID of the received CanTp I-PDU
 * \param    result                          Result of the TP reception\n
 *           E_OK                            The TP transmission has been completed successfully.\n
 *           E_NOT_OK                        The PDU Router is in the PDUR_UNINIT state\n
 *                                           or the CanTpTxPduId is not valid\n
 *                                           or the CanTpTxPduId is not forwarded in this identity\n
 *                                           or the request was not accepted by the destination upper layer.\n
 * \return   none
 * \pre      PduR_Init() is executed successfully.
 * \context  This function can be called on interrupt and task level and has not to be interrupted by other\n
 *           PduR_CanTpRxIndication calls for the same CanTpRxPduId.
 * \trace    DSGN-PduR_TP_Forwarding
 * \trace    SPEC-666, SPEC-674, SPEC-38409
 * \note     The function is called by CanTp.
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanTpRxIndication(PduIdType id, Std_ReturnType result);

/**********************************************************************************************************************
 * PduR_CanTpTxConfirmation
 *********************************************************************************************************************/
/*!
 * \brief    The function is called by the CanTp to confirm the complete transmission of a CanTp I-PDU or to\n
 *           report an error that occurred during reception. The PDU Router evaluates the CanTp I-PDU handle and\n
 *           performs appropriate handle and port conversion.The call is routed to an upper Tp module using the\n
 *           appropriate I-PDU handle of the destination layer.
 * \param    id                              ID of the transmitted CanTp I-PDU
 * \param    result                          Result of the TP transmission\n
 *           E_OK                            The TP transmission has been completed successfully.\n
 *           E_NOT_OK                        The PDU Router is in the PDUR_UNINIT state\n
 *                                           or the CanTpTxPduId is not valid\n
 *                                           or the CanTpTxPduId is not forwarded in this identity\n
 *                                           or the request was not accepted by the destination upper layer.\n
 * \return   none
 * \pre      PduR_Init() is executed successfully.
 * \context  This function can be called on interrupt and task level and has not to be interrupted by other\n
 *           PduR_CanTpTxConfirmation calls for the same CanTpTxPduId.
 * \trace    DSGN-PduR_TP_Forwarding
 * \trace    SPEC-666
 * \note     The function is called by CanTp.
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_CanTpTxConfirmation(PduIdType id, Std_ReturnType result);

/**********************************************************************************************************************
 * PduR_CanTpStartOfReception
 *********************************************************************************************************************/
/*!
 * \brief    This function will be called by the CanTp at the start of a I-PDU reception.\n
 *           The I-PDU might be fragmented into multiple N-PDUs\n
 *           (FF with one or more following CFs) or might consist of a single N-PDU (SF).\n
 *           The PDU Router evaluates the CanTp I-PDU handle and identifies the destination(s) of the PDU.\n
 *           The call is routed to an upper Tp or gateway module using the appropriate I-PDU handle of the\n
 *           destination layer.
 * \param    id                ID of the CanTp I-PDU that will be received
 * \param    info              Pointer to the buffer with meta data if the meta data feature is used (SduDataPtr) \n 
 *                             length empty (use configured length) \n
 * \param    TpSduLength       Length of the entire the CanTp SDU which will be received
 * \param    bufferSizePtr     Pointer to the receive buffer in the receiving module.\n
 *                             This parameter will be used to compute Block Size (BS) in the transport protocol module.
 * \return   BufReq_ReturnType\n
 *           BUFREQ_OK         Connection has been accepted. bufferSizePtr indicates the available receive buffer.\n
 *           BUFREQ_E_NOT_OK   The PDU Router is in the PDUR_UNINIT state\n
 *                             or the id is not valid\n
 *                             or the id is not forwarded in this identity\n
 *                             or the request was not accepted by the destination layer.\n
 *                             or no buffer is available.\n
 * \pre      PduR_Init() is executed successfully.
 * \context  This function can be called on interrupt and task level and has not to be interrupted by other\n
 *           PduR_CanTpStartOfReception calls for the same id.
 * \trace    DSGN-PduR_TP_Forwarding
 * \trace    SPEC-666, SPEC-1096, SPEC-2020085, SPEC-38410
 * \note     The function is called by CanTp.
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpStartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);

/**********************************************************************************************************************
 * PduR_CanTpCopyRxData
 *********************************************************************************************************************/
/*!
 * \brief    This function is called by the CanTp if data has to be to copied to the receiving module.\n
 *           Each call to this function copies the next part of the received data.\n
 *           Several calls may be made during transportation of an I-PDU.\n
 *           The PDU Router evaluates the CanTp I-PDU handle and identifies the destination(s) of the PDU.\n
 *           The call is routed to an upper Tp or gateway module using the appropriate I-PDU handle of the\n
 *           destination layer.
 * \param    id                ID of the CanTp I-PDU that will be received
 * \param    info              Pointer to the buffer (SduDataPtr) and its length (SduLength)\n
 *                             containing the data to be copied by PDU Router module in case of gateway\n
 *                             or upper layer module in case of reception.\n
 *                             A copy size of 0 can be used to poll the available buffer size.
 * \param    bufferSizePtr     Available receive buffer after data has been copied.
 * \return   BufReq_ReturnType\n
 *           BUFREQ_OK         Buffer request accomplished successful\n
 *           BUFREQ_E_NOT_OK   The PDU Router is in the PDUR_UNINIT state\n
 *                             or the id is not valid\n
 *                             or the id is not forwarded in this identity\n
 *                             or the infois not valid\n
 *                             or the request was not accepted by the destination layer\n
 *                             or no buffer is available.\n
 *           BUFREQ_E_OVFL     The upper TP module is not able to receive the number of bytes.\n
 *                             The request was not accepted by the destination layer.
 * \pre      PduR_Init() is executed successfully.
 * \context  This function can be called on interrupt and task level and has not to be interrupted by other\n
 *           PduR_CanTpCopyRxData calls for the same id.
 * \trace    DSGN-PduR_TP_Forwarding
 * \trace    SPEC-666, SPEC-1096, SPEC-2020085, SPEC-38432
 * \note     The function is called by CanTp.
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);

/**********************************************************************************************************************
 * PduR_CanTpCopyTxData
 *********************************************************************************************************************/
/*!
 * \brief    This function is called by the CanTp to query the transmit data of an I-PDU segment.\n
 *           Each call to this function copies the next part of the transmit data.\n
 *           The PDU Router evaluates the CanTp I-PDU handle and identifies the destination(s) of the PDU.
 *           The call is routed to an upper Tp or gateway module using the appropriate I-PDU handle of the\n
 *           destination layer.
 * \param    id                ID of the CanTp I-PDU that will be transmitted
 * \param    info              Pointer to the destination buffer and the number of bytes to copy.\n
 *                             In case of gateway the PDU Router module will copy otherwise the source \n
 *                             upper layer module will copy the data. If not enough transmit data is available,\n
 *                             no data is copied.\n
 *                             A copy size of 0 can be used to poll the available Tx data.
 * \param    retry             retry not supported yet. Is not used.
 * \param    availableDataPtr  Indicates the remaining number of bytes that are available in the PduR Tx buffer.\n
 *                             availableDataPtr can be used by TP modules that support dynamic payload lengths\n
 *                             (e.g. Iso FrTp) to determine the size of the following CFs.
 * \return   BufReq_ReturnType\n
 *           BUFREQ_OK         The data has been copied to the transmit buffer successful\n
 *           BUFREQ_E_BUSY     Request could not be fulfilled, because the required amount of \n
 *                             Tx data is not available. The LoTp module can either retry the request \n
 *           BUFREQ_E_NOT_OK   The PDU Router is in the PDUR_UNINIT state\n
 *                             or the id is not valid\n
 *                             or the id is not forwarded in this identity\n
 *                             or the info pointer is not valid\n
 *                             or the request was not accepted by the destination layer\n
 *                             or the request length to copy is greater than the remaining buffer size.
 * \pre      PduR_Init() is executed successfully.
 * \context  This function can be called on interrupt and task level and has not to be interrupted by other\n
 *           PduR_CanTpCopyTxData calls for the same id.
 * \trace    DSGN-PduR_TP_Forwarding
 * \trace    SPEC-666, SPEC-1096, SPEC-2020085, SPEC-38401
 * \note     The function is called by CanTp.
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr);






#define PDUR_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* PDUR_CANTP_H */


/**********************************************************************************************************************
 * GLOBAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/*  module specific MISRA deviations:
    MD_PduR_3451:   MISRA rule: 8.8
    Reason:         The global identifier has been declared in more than one file. the function declaration has to be in
                    the PduR_<Module>.h. Affected APIs are CancelReceive, CancelTransmit and ChangeParameter.
    Risk:           no risk.
    Prevention:     To avoid a duplicate declaration uns the BSW-Module "use-Tag" flag.
*/

/**********************************************************************************************************************
 * END OF FILE: PduR_CanTp.h
 *********************************************************************************************************************/

