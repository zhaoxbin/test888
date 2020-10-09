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
 *         File:  PduR_RmIf.h
 *      Project:  Gw_AsrPduRCfg5
 *       Module:  MICROSAR PDU Router
 *    Generator:  Configurator 5
 *
 *  Description:  Vector implementation of AUTOSAR PDU Router
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/
#if !defined (PDUR_RMIF_H)
# define PDUR_RMIF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "PduR_Types.h"
# include "PduR_Cfg.h"
# include "PduR_Lcfg.h"

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
# define PDUR_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_19.1 */

# if (PDUR_EXISTS_SINGLE_BUFFER_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_SingleBuffer_Init
 *********************************************************************************************************************/
/*! \brief       This function initializes the single buffer with default values
 *  \details     -
 *  \pre         PduR_InitMemory() has been executed, if the start up code does not initialize variables.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        The function must be called on task level and has not to be interrupted
 *               by other administrative function calls.
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_SingleBuffer_Init(void);
# endif

# if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_InitDestPduState
**********************************************************************************************************************/
/*! \brief       Initialize FiFo Routing State for communication interface routing.
 *  \details     -
 *  \pre         PduR_InitMemory() has been executed, if the startup code does not initialise variables.
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_InitDestPduState(void);
# endif

# if((PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
  PduR_RmIf_RoutePdu
**********************************************************************************************************************/
/*! \brief       This function calls the corresponding destination function for each PduRDestPdu.
 *  \details     -
 *  \param[in]   rmSrcIdx          ID of the received GwIf I-PDU
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_RoutePdu(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
# endif

# if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmIf_TxConfirmation_StateHandler_RM_TX_ACTIVE
**********************************************************************************************************************/
/*! \brief       This function handles the TxConfirmation in the corresponding state
 *  \details     -
 *  \param[in]   rmGDestRomIdx           Index for the RmGDestRom table
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
***********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation_StateHandler_RM_TX_ACTIVE(PduR_RmGDestRomIterType rmGDestRomIdx);
# endif

# if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmIf_TxConfirmation_StateHandler_RM_TX_IDLE
**********************************************************************************************************************/
/*! \brief       This function handles the TxConfirmation in the corresponding state
 *  \details     -
 *  \param[in]   rmGDestRomIdx           Index for the RmGDestRom table
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
***********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation_StateHandler_RM_TX_IDLE(PduR_RmGDestRomIterType rmGDestRomIdx);
# endif

# if((PDUR_MAIN_FUNCTION == STD_ON) && (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_MainFunction
 *********************************************************************************************************************/
/*!
 * \brief        Process deferred If Pdus in context of cyclic MainFunction
 * \details      -
 * \param[in]    rmGDestRomIdx            internal RmGDestRom index
 * \pre         -
 * \context      TASK
 * \reentrant    TRUE
 * \synchronous  TRUE
**********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_MainFunction(PduR_RmGDestRomIterType rmGDestRomIdx);
# endif

# if((PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
  PduR_RmIf_DispatchIfDestPdu
**********************************************************************************************************************/
/*! \brief       This funtion forwards the received Pdu to the corresponding destination function.
 *  \details     -
 *  \param[in]   rmDestRomIdx      RmDestRom Handle
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \return      Std_ReturnType    E_OK:     The SDU has been routed successfully.
 *                                 E_NOT_OK: The SDU has not been routed successfully.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_DispatchIfDestPdu(PduR_RmDestRomEndIdxOfRmSrcRomType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
# endif

# if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) && (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_MultipleSourceHandler_CancelTransmit
 *********************************************************************************************************************/
/*! \brief        This function is called by the PduR to cancel the transmission on the destination buses
 *  \details      -
 *  \param[in]    rmDestRomIdx           ID of the destination Pdu
 *  \return       Std_ReturnType         E_OK:     cancellation successful
 *                                       E_NOT_OK: cancellation not successful
 *  \pre          -
 *  \context      TASK|ISR1|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 **********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_CancelTransmit(PduR_RmDestRomIterType rmDestRomIdx);
# endif

# if ((PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON) || (PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
 /**********************************************************************************************************************
  PduR_RmIf_MultipleSourceHandler_TriggerTransmit
**********************************************************************************************************************/
/*! \brief       This function returns the next available Pdu if available.
 *  \details     -
 *  \param[in]   rmGDestRomIdx     ID of the transmitted GwIf I-PDU
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \return      Std_ReturnType    E_OK:     The SDU has been copied and the SduLength indicates the number of copied bytes.
 *                                 E_NOT_OK: The SDU has not been copied and the SduLength has not been set.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
***********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_TriggerTransmit(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
# endif

# if (PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)
/**********************************************************************************************************************
  PduR_RmIf_MultipleSourceHandler_TxConfirmation
**********************************************************************************************************************/
/*! \brief        The function is called by the PduR to indicate the complete transmission of a communication interface I-PDU.
 *  \details      -
 *   \param[in]   rmGDestRomIdx           ID of the transmitted GwIf I-PDU
 *   \pre         -
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
 **********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_TxConfirmation(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx);
# endif

#if ((PDUR_RPGROM == STD_ON) && (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_DisableRoutingAction
 *********************************************************************************************************************/
/*! \brief      This function flushes the Interface queue if the queue is in use while the RoutingPathGroup
 *              is disabled.
 *  \details    -
 *  \param[in]  rmDestRomIdx  Gateway Id used for state handling.
 *  \pre        -
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_DisableRoutingAction(PduR_RmDestRomIterType rmDestRomIdx);
#endif

#if (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_SingleBuffer_Put
 *********************************************************************************************************************/
/*! \brief      This function writes the Pdu to the single buffer
 *  \details    -
 *  \param[in]  rmDestRomIdx         routing manager indirection Idx.
 *  \param[in]  rmGDestRomIdx        routing manager indirection Idx to global destination Pdu table.
 *  \param[in]  pduLength            length to copy.
 *  \param[in]  sduDataPtr           data pointer.
 *  \return     E_OK                 This function will always return E_OK. The return value is only required for the correct data type for the function pointer table.
 *  \pre        -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_SingleBuffer_Put(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr);
#endif

#if (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_SingleBuffer_Get
 *********************************************************************************************************************/
/*! \brief       This function gets the Pdu from the single buffer
 *  \details     -
 *  \param[in]   rmGDestRomIdx       global destination Pdu Idx.
 *  \param[out]  rmDestRomIdx        read destination Pdu Idx from the queue
 *  \param[out]  info                read data from the queue
 *  \return      E_OK                A Pdu could be read and will be returned via the pointers
 *               E_NOT_OK            No Pdu could be read.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_SingleBuffer_Get(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

# define PDUR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */
#endif /* PDUR_RMIF_H */
/**********************************************************************************************************************
 *  END OF FILE: PduR_RmIf.h
 *********************************************************************************************************************/
