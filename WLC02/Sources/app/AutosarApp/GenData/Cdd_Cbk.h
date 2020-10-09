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
 *            Module: Cdd
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Cdd_Cbk.h
 *   Generation Time: 2020-09-01 20:49:57
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



#if !defined (CDD_CBK_H)
# define CDD_CBK_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
# include "ComStack_Types.h"



/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
#ifndef CDD_USE_DUMMY_STATEMENT
#define CDD_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/EcuC/EcucGeneral/DummyStatement */
#endif
#ifndef CDD_DUMMY_STATEMENT
#define CDD_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CDD_DUMMY_STATEMENT_CONST
#define CDD_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CDD_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define CDD_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef CDD_ATOMIC_VARIABLE_ACCESS
#define CDD_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef CDD_PROCESSOR_RH850_1649
#define CDD_PROCESSOR_RH850_1649
#endif
#ifndef CDD_COMP_GREENHILLS
#define CDD_COMP_GREENHILLS
#endif
#ifndef CDD_GEN_GENERATOR_MSR
#define CDD_GEN_GENERATOR_MSR
#endif
#ifndef CDD_CPUTYPE_BITORDER_LSB2MSB
#define CDD_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef CDD_CONFIGURATION_VARIANT_PRECOMPILE
#define CDD_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef CDD_CONFIGURATION_VARIANT_LINKTIME
#define CDD_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef CDD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define CDD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef CDD_CONFIGURATION_VARIANT
#define CDD_CONFIGURATION_VARIANT CDD_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef CDD_POSTBUILD_VARIANT_SUPPORT
#define CDD_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


#define CDD_COMIF  STD_OFF
#define CDD_COMIF_RX  STD_OFF
#define CDD_COMIF_TX  STD_OFF
#define CDD_COMIF_TRIGGERTRANSMIT  STD_OFF

#define CDD_PDUR_UL_COMIF  STD_OFF
#define CDD_PDUR_UL_COMIF_TRIGGERTRANSMIT  STD_OFF

#define CDD_PDUR_UL_COMTP  STD_ON

#define CDD_PDUR_LL_COMIF  STD_OFF
#define CDD_PDUR_LL_COMIF_TRIGGERTRANSMIT  STD_OFF

#define CDD_PDUR_LL_COMTP  STD_OFF

#define CDD_SOADUL_COMIF_RX  STD_OFF
#define CDD_SOADUL_COMIF_TRIGGERTRANSMIT  STD_OFF
#define CDD_SOADUL_COMIF_TXCONFIRMATION   STD_OFF

#define CDD_SOADUL_COMTP_RX  STD_OFF
#define CDD_SOADUL_COMTP_TX  STD_OFF





/**
 * \defgroup CddHandleIdsPduRUpperLayerRx Handle IDs of handle space PduRUpperLayerRx.
 * \brief CddPduRUpperLayerContribution Rx PDUs
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define CddConf_CddPduRUpperLayerRxPdu_CDC_WLC_NFC_Pdu_CANTP          0
#define CddConf_CddPduRUpperLayerRxPdu_IMOB_CGW_WLC_oNIO_ES6_RF_CDDasCanTp 2
#define CddConf_CddPduRUpperLayerRxPdu_WLC_DEVLP_02_oNIO_ES6_RF_CAN_CDDasCanTp 1
/**\} */

/**
 * \defgroup CddHandleIdsPduRUpperLayerTx Handle IDs of handle space PduRUpperLayerTx.
 * \brief CddPduRUpperLayerContribution Tx PDUs
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define CddConf_CddPduRUpperLayerTxPdu_IMOB_WLC_CGW_oNIO_ES6_RF_CAN_CDDAsCanTp 1
#define CddConf_CddPduRUpperLayerTxPdu_WLC_CDC_NFC_oNIO_ES6_RF_CAN_CDDAsCanTp 2
#define CddConf_CddPduRUpperLayerTxPdu_WLC_DEVLP_01_oNIO_ES6_RF_CAN_CDDasCanTp 0
/**\} */

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
# define CDD_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */
/*lint -restore */





/*! \defgroup ProvidedCddCddTransportProtocol Provided Cdd transport protocol interface to PduR
    \brief    These services have to be provided by the Cdd if the CDD is an upper layer for the PduR. */
/*\{*/

/**********************************************************************************************************************
  Cdd_StartOfReception
**********************************************************************************************************************/
/*! \brief       The function call indicates the reception start of a segmented PDU.
    \param[in]   id             id of the TP CddPduRUpperLayerRxPdu.
    \param[in]   info           Pointer to a PduInfoType structure containing the payload data
    \param[in]   TpSduLength    length of the entire the TP SDU that will be received.
    \param[out]  bufferSizePtr  length of the available receive buffer in Cdd.\n
                                This parameter is used e.g. in CanTp to calculate the Block Size (BS).
    \return      a BufReq_ReturnType constant of ComStackTypes.h.
    \pre         The Cdd is initialized and active.
    \context     This function can be called on interrupt and task level and has not to be interrupted by other\n
                 Cdd_StartOfReception calls for the same id.
    \note        The function is called by the PduR.
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, CDD_CODE) Cdd_StartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, CDD_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, CDD_APPL_DATA) bufferSizePtr);

/**********************************************************************************************************************
  Cdd_CopyRxData
**********************************************************************************************************************/
/*! \brief       This function is called to trigger the copy process of a segmented PDU.\n
                 The function can be called several times and\n
                 each call to this function copies parts of the received data.\n
    \param[in]   id             id of the TP CddPduRUpperLayerRxPdu.
    \param[in]   info           a PduInfoType pointing to the data to be copied in the Cdd data buffer.
    \param[out]  bufferSizePtr  available receive buffer after data has been copied.
    \return      a BufReq_ReturnType constant of ComStackTypes.h.      
    \pre         The Cdd is initialized and active.
    \context     This function can be called on interrupt and task level and has not to be interrupted by other\n
                 Cdd_CopyRxData calls for the same id.
    \note        The function is called by the PduR.
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, CDD_CODE) Cdd_CopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, CDD_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, CDD_APPL_DATA) bufferSizePtr);

/**********************************************************************************************************************
  Cdd_TpRxIndication
**********************************************************************************************************************/
/*! \brief       The function is called to indicate the complete receiption of a Cdd TP SDU
                 or to report an error that occurred during reception.
    \param[in]   id             id of the TP CddPduRUpperLayerRxPdu.
    \param[in]   result         a Std_ReturnType to indicate the result of the reception.
    \return      none
    \pre         The Cdd is initialized and active.
    \context     This function can be called on interrupt and task level and has not to be interrupted by other\n
                 Cdd_TpRxIndication calls for the same id.
    \note        The function is called by the PduR.
**********************************************************************************************************************/
FUNC(void, CDD_CODE) Cdd_TpRxIndication(PduIdType id, Std_ReturnType result);

/**********************************************************************************************************************
  Cdd_CopyTxData
**********************************************************************************************************************/
/*! \brief       This function is called to request transmit data of a TP CddPduRUpperLayerTxPdu\n
                 The function can be called several times and\n
                 each call to this function copies the next part of the data to be transmitted.\n
    \param[in]   id             id of the TP CddPduRUpperLayerTxPdu.
    \param[in]   info           a PduInfoType pointing to the destination buffer.
    \param[in]   retry          NULL_PTR to indicate a successful copy process\n
                                or a RetryInfoType containing a TpDataStateType constant of ComStackTypes.h.
    \param       availableDataPtr   Indicates the remaining number of bytes that are available in the TX buffer.\n
                                availableDataPtr can be used by TP modules that support dynamic payload lengths\n
                                (e.g. Iso FrTp) to determine the size of the following CFs.
    \return      a BufReq_ReturnType constant of ComStackTypes.h.
    \pre         The Cdd is initialized and active.
    \context     This function can be called on interrupt and task level and has not to be interrupted by other\n
                 Cdd_CopyTxData calls for the same id.
    \note        The function is called by the PduR.
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, CDD_CODE) Cdd_CopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, CDD_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, CDD_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, CDD_APPL_DATA) availableDataPtr);

/**********************************************************************************************************************
  Cdd_TpTxConfirmation
**********************************************************************************************************************/
/*! \brief       The function is called to confirm a successful transmission of a TP CddPduRUpperLayerTxPdu\n
                 or to report an error that occurred during transmission.
    \param[in]   id             id of the TP CddPduRUpperLayerTxPdu.
    \param[in]   result         a Std_ReturnType to indicate the result of the transmission.
    \return      none
    \pre         The Cdd is initialized and active.
    \context     This function can be called on interrupt and task level and has not to be interrupted by other\n
                 Cdd_TpTxConfirmation calls for the same id.
    \note        The function is called by the PduR.
**********************************************************************************************************************/
FUNC(void, CDD_CODE) Cdd_TpTxConfirmation(PduIdType id, Std_ReturnType result);

/*\}*/


# define CDD_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"    /* PRQA S 5087 */       /* MD_MSR_MemMap */
/*lint -restore */

#endif  /* CDD_CBK_H */
/**********************************************************************************************************************
  END OF FILE: Cdd_Cbk.h
**********************************************************************************************************************/


