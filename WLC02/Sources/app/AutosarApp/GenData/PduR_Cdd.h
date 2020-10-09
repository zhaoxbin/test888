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
 *              File: PduR_Cdd.h
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

#if !defined (PDUR_CDD_H)
# define PDUR_CDD_H

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
 * PduR_CddTransmit
 *********************************************************************************************************************/
/*!
 * \brief    The function serves to request the transmission of an upper layer I-PDU.\n
 *           The PDU Router evaluates the Cdd I-PDU handle and identifies the destination(s) of the PDU.\n
 *           The call is routed to a lower IF module using the appropriate I-PDU handle of the destination layer.
 * \param    id                ID of the Cdd I-PDU to be transmitted
 * \param    info              Payload information of the I-PDU (pointer to data and data length)
 * \return   Std_ReturnType\n
 *           E_OK              The request was accepted by the PDU Router and by the destination layer.\n
 *           E_NOT_OK          The PDU Router is in the PDUR_UNINIT state\n
 *                             or the CddTxPduId is not valid\n
 *                             or the CddTxPduId is not forwarded in this identity\n
 *                             or the info is not valid\n
 *                             or the request was not accepted by the destination layer.\n
 * \pre      PduR_Init() is executed successfully.
 * \context  This function can be called on interrupt and task level and has not to be interrupted by other\n
 *           PduR_CddTransmit calls for the same CddTxPduId.
 * \trace    DSGN-PduR_TP_Forwarding
 * \trace    SPEC-666, SPEC-679, SPEC-686, SPEC-1827, SPEC-1096, SPEC-2020085, SPEC-38411
 * \note     The function is called by Cdd.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_CddTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);








#define PDUR_STOP_SEC_CODE
# include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* PDUR_CDD_H */


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
 * END OF FILE: PduR_Cdd.h
 *********************************************************************************************************************/

