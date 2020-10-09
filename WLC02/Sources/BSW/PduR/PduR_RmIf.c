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
 *         File:  PduR_RmIf.c
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

/**********************************************************************************************************************
 * LOCAL MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */
/* PRQA  S 3453 EOF */ /* MD_MSR_FctLikeMacro */
/* PRQA  S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA  S 4304 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA  S 4404 EOF */ /* MD_MSR_AutosarBoolean */
/* *INDENT-ON* */

#define PDUR_RMIF_SOURCE
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_Fm.h"
#include "PduR_McQ.h"
#include "PduR_Lock.h"
#include "PduR_RmIf.h"
#if (PDUR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
#define PduR_Core_MemCpyRamToRam(d, s, l)    VStdMemCpyRamToRam((d), (s), (l))
#define PduR_Core_MemCpyRomToRam(d, s, l)    VStdMemCpyRomToRam((d), (s), (l))

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define PDUR_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

#if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_TruncateDlc
 *********************************************************************************************************************/
/*! \brief      Truncates the Pdu length to the configured Pdu length if larger.
 *  \details    -
 *  \param[in]  rmGDest           routing manager indirection Idx.
 *  \param[in]  info              contains the data pointer and its length.
 *  \pre        -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(PduLengthType, PDUR_CODE) PduR_RmIf_TruncateDlc(PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_FifoHandling
 *********************************************************************************************************************/
/*! \brief      Perform D-Fifo and TT-Fifo buffer and transmission handling
 *  \details    -
 *  \param[in]  rmDest   routing manager indirection Idx.
 *  \param[in]  rmGDest  routing manager indirection Idx to global destination Pdu table.
 *  \param[in]  info     Info pointer contains data and length
 *  \pre        -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_FifoHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON )
/**********************************************************************************************************************
   PduR_RmIf_RxIndicationNoBuffer
**********************************************************************************************************************/
/*! \brief       This function processes the 'No-buffer-gateway-routing'
 *  \details     -
 *  \param[in]   rmDestIdx         ID of the received gateway I-PDU
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
**********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_RxIndicationNoBuffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
   PduR_RmIf_Forward2Buffer
**********************************************************************************************************************/
/*! \brief       The function forwards the If Pdu to the corresponding buffer handling function.
 *  \details     -
 *  \param[in]   rmDestIdx         ID of the received gateway I-PDU
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-1096, SPEC-2020151
**********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_Forward2Buffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_SingleBufferHandling
 *********************************************************************************************************************/
/*! \brief     This function processes 'Single-buffer-routings'
 *  \details   -
 *  \param[in] rmDest         routing manager indirection Idx.
 *  \param[in] rmGDest        routing manager indirection Idx to global destination Pdu table.
 *  \param[in] info           Info pointer contains data and max Pdu length.
 *  \pre       -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_SingleBufferHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if( (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
  PduR_RmIf_MultipleSourceHandler_Transmit
**********************************************************************************************************************/
/*!  \brief       This function transmits the Pdu to the destination module and does N:1 handling if required
 *   \details     -
 *   \param[in]   rmDestRomIdx              ID of the destination Pdu
 *   \param[in]   info                      Pointer to the destination buffer and the number of bytes to copy.
 *   \param[in]   useLock                   shall the 'transmissionActive' Flag be set and considered for this transmission
 *   \return      Std_ReturnType            Result of the multiple transmission.
 *                            E_OK          The transmission was successfully .\n
 *                            E_NOT_OK      The transmission fails.
 *   \pre         -
 *   \context     TASK|ISR1|ISR2
 *   \reentrant   TRUE
 *   \synchronous TRUE
**********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, boolean useLock);
#endif

#if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmIf_TxConfirmation
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to indicate the complete transmission of a communication interface I-PDU.
 *  \details     -
 *  \param[in]   rmGDestRomIdx           ID of the transmitted GwIf I-PDU
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
***********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx);
#endif

#if(PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmIf_TriggerTransmit
**********************************************************************************************************************/
/*! \brief           This function returns the next Pdu from the buffer for TriggerTransmit dataprovision routings
 *  \details         -
 *  \param[in]       rmDestIdx         ID of the GwIf I-PDU that will be transmitted.
 *  \param[in,out]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \return          Std_ReturnType    E_OK:     The SDU has been copied and the SduLength indicates
 *                                           the number of copied bytes.
 *                                     E_NOT_OK: The SDU has not been copied and the SduLength has not been set.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       SPEC-1096, SPEC-2020151
**********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_TriggerTransmit(PduR_RmDestRomIterType rmDestIdx, CONSTP2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmIf_ProcessNoBufferedGwRouting
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to process no buffered gateway If Pdus
 *  \details     -
 *  \param[in]   rmDestIdx         ID of the GwIf I-PDU that will be transmitted.
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \return      Std_ReturnType    E_OK:     The SDU has been copied and the SduLength indicates
 *                                           the number of copied bytes.
 *                                 E_NOT_OK: The SDU has not been copied and the SduLength has not been set.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
**********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessNoBufferedGwRouting(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
  PduR_RmIf_ProcessBufferedRouting
**********************************************************************************************************************/
/*! \brief       The function is called by the PduR to process buffered If Pdus
 *  \details     -
 *  \param[in]   rmSrcIdx          Source Id.
 *  \param[in]   rmDestIdx         Destintaion Id.
 *  \param[in]   rmGDestRomIdx     G Dest Rom Table Id.
 *  \param[in]   info              Payload information of the received I-PDU (pointer to data and data length).
 *  \return      Std_ReturnType    E_OK:     The SDU has been copied and the SduLength indicates
 *                                           the number of copied bytes.
 *                                 E_NOT_OK: The SDU has not been copied and the SduLength has not been set.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
**********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessBufferedRouting(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestIdx, PduR_RmGDestRomIterType rmGDestRomIdx,
                                                                              P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if ((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_QAL_Put
 *********************************************************************************************************************/
/*! \brief      This function writes the Pdu to the Fifo. It calls the corresponding implementation specific function.
 *  \details    -
 *  \param[in]  rmDestRomIdx         routing manager indirection Idx.
 *  \param[in]  rmGDestRomIdx        routing manager indirection Idx to global destination Pdu table.
 *  \param[in]  pduLength            length to copy.
 *  \param[in]  sduDataPtr           data pointer.
 *  \pre        -
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_QAL_Put(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr);
#endif

#if ((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_QAL_Get
 *********************************************************************************************************************/
/*! \brief       Get the next element from the queue if available
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
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_QAL_Get(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_QAL_Remove
 *********************************************************************************************************************/
/*! \brief       Remove the oldest element from the queue
 *  \details     -
 *  \param[in]   rmGDestRomIdx         global destination Pdu Idx.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_QAL_Remove(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if ((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) && (PDUR_DEFERREDEVENTCACHEROM == STD_ON))
/**********************************************************************************************************************
 * PduR_QAL_GetFillLevel
 *********************************************************************************************************************/
/*! \brief       Get the fill level of the queue.
 *  \details     -
 *  \param[in]   rmGDestRomIdx       global destination Pdu Idx.
 *  \return                          Fill level of the queue
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(uint16, PDUR_CODE) PduR_QAL_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

# if (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_QAL_Flush
 *********************************************************************************************************************/
/*! \brief       This function flushes the FIFO queue.
 *  \details     -
 *  \param[in]   rmGDestRomIdx  routing manager indirection Idx.
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_QAL_Flush(PduR_RmGDestRomIterType rmGDestRomIdx);
# endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * PduR_RmIf_SingleBuffer_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if (PDUR_EXISTS_SINGLE_BUFFER_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
FUNC(void, PDUR_CODE) PduR_RmIf_SingleBuffer_Init(void)
{
  PduR_RmGDestRomIterType rmGDestRomIdx;
  for(rmGDestRomIdx = 0u; rmGDestRomIdx < PduR_GetSizeOfRmGDestRom(); rmGDestRomIdx++)
  {
    if(PduR_IsRmBufferedIfPropertiesRomUsedOfRmGDestRom(rmGDestRomIdx) && PduR_IsSingleBufferRomUsedOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx)))        /* COV_PDUR_FEATURE_ALWAYS_TRUE */ /* PRQA S 2995, 2996, 2991 */ /* MD_PduR_2995_2996, MD_PduR_2995_2996, MD_PduR_2991 */
    {
      PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx);
      PduR_SingleBufferRomIdxOfRmBufferedIfPropertiesRomType singleBufferRomIdx = PduR_GetSingleBufferRomIdxOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx);

      PduR_Core_MemCpyRomToRam(PduR_GetAddrSingleBufferArrayRam(PduR_GetSingleBufferArrayRamStartIdxOfSingleBufferRom(singleBufferRomIdx)), PduR_GetAddrSingleBufferInitValuesRom(PduR_GetSingleBufferInitValuesRomStartIdxOfSingleBufferRom(singleBufferRomIdx)), PduR_GetSingleBufferArrayRamLengthOfSingleBufferRom(singleBufferRomIdx));   /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_PDUR_MEM_CPY_FIFOMGR */
      PduR_SetActualLengthOfSingleBufferRam(singleBufferRomIdx, PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRomIdx));    /* SBSW_PDUR_CSL01 */
    }
  }
}
#endif

#if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_InitDestPduState
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_InitDestPduState(void)
{
  PduR_RmBufferedIfPropertiesRomIterType rmBufferedIfPropertiesRamIdx;
  for(rmBufferedIfPropertiesRamIdx = 0u; rmBufferedIfPropertiesRamIdx < PduR_GetSizeOfRmBufferedIfPropertiesRam(); rmBufferedIfPropertiesRamIdx++)
  {
# if (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
    if(PduR_IsSingleBufferRomUsedOfRmBufferedIfPropertiesRom(rmBufferedIfPropertiesRamIdx)) /* COV_PDUR_ONLY_TT_SINGLE_BUFFER */ /* PRQA S 2991, 2995 */ /* MD_PduR_2991, MD_PduR_2995_2996*/
    {
      PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRamIdx, PDUR_RM_TX_ACTIVE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);    /* SBSW_PDUR_CSL01 */
    }
# endif
# if ((PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) && (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
    else
# endif
# if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
    {
      PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRamIdx, PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);    /* SBSW_PDUR_CSL01 */
    }
# endif
  }
}
#endif

#if((PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_MultipleSourceHandler_Transmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_Transmit(PduR_RmDestRomIterType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, boolean useLock)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_Lock_LockRoutingPathByDestPdu(rmDestRomIdx);
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
    {
      PduR_RmGDestNto1InfoRamIdxOfRmGDestRomType rmGDestNto1InfoIdx = PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx);

      if(!PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx))    /* COV_PDUR_NTO1_GW_ONLY_ROUTINGPATHS */
      {
        PduR_SetRmDestRomIdxOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, (PduR_RmDestRomIdxOfRmGDestNto1InfoRamType) rmDestRomIdx); /* SBSW_PDUR_CSL03 */
        PduR_SetTransmissionActiveOfRmGDestNto1InfoRam(rmGDestNto1InfoIdx, useLock);    /* SBSW_PDUR_CSL03 */

        retVal = PduR_GetLoIfTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
        if(retVal != E_OK)
        {
          PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
        }
      }
    }
    else
# endif
    {
      retVal = PduR_GetLoIfTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }
  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);

  PDUR_DUMMY_STATEMENT(useLock);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return retVal;
}
#endif

#if ((PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON) || (PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_MultipleSourceHandler_TriggerTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_TriggerTransmit(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  {
    PduR_RmDestRomIterType rmDestRomIdx;

    if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK)     /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_NO_NTO1_ROUTINGPATHS */
    {
# if (PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
      if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM)       /* COV_PDUR_FATAL_ERROR */
      {
        retVal = PduR_RmIf_TriggerTransmit(rmDestRomIdx, info); /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
      else
# endif
# if (PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON)
      if(PduR_IsTriggerTransmitSupportedOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx)))       /* COV_PDUR_FATAL_ERROR */
      {
        retVal = PduR_GetUpIfTriggerTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx))) (PduR_GetSrcHndOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx)), info);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
      else
# endif
      {
        PduR_Det_ReportError(PDUR_RMIF_MULTIPLESOURCEHANDLER_TRIGGERTRANSMIT, PDUR_E_PDU_ID_INVALID);
      }
    }
    else
    {
      PduR_Det_ReportError(PDUR_RMIF_MULTIPLESOURCEHANDLER_TRIGGERTRANSMIT, PDUR_E_PDU_ID_INVALID);
    }
  }
  return retVal;
}
#endif

#if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) && (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_MultipleSourceHandler_CancelTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_CancelTransmit(PduR_RmDestRomIterType rmDestRomIdx)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  PduR_Lock_LockRoutingPathByDestPdu(rmDestRomIdx);
  {
    PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    if(PduR_IsRmGDestNto1InfoRamUsedOfRmGDestRom(rmGDestRomIdx))
    {
      PduR_RmDestRomIterType lastTxdRmDestRomIdx;
      Std_ReturnType foundSrcPdu = PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &lastTxdRmDestRomIdx);  /* SBSW_PDUR_STACK_VARIABLE */

      if(PduR_IsTransmissionActiveOfRmGDestNto1InfoRam(PduR_GetRmGDestNto1InfoRamIdxOfRmGDestRom(rmGDestRomIdx)) && (foundSrcPdu == E_OK) && (rmDestRomIdx == lastTxdRmDestRomIdx))   /* COV_PDUR_ROBUSTNESS */
      {
        retVal = PduR_GetLoIfCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
      else
      {
        PduR_Det_ReportError(PDUR_RMIF_MULTIPLESOURCEHANDLER_CANCELTRANSMIT, PDUR_E_UNEXPECTED_CALL);
      }
    }
    else
# endif
    {
      retVal = PduR_GetLoIfCancelTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx));       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    }
  }
  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestRomIdx);
  return retVal;
}
#endif

#if (PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_MultipleSourceHandler_TxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_MultipleSourceHandler_TxConfirmation(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx)
{
  PduR_RmDestRomIterType rmDestRomIdx;

  /* #10 Get RmDest index of GDestPdu. If index is ambiguous, call DET */
  if(PduR_Rm_GetSrcDestPdu(rmGDestRomIdx, &rmDestRomIdx) == E_OK)       /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_NO_NTO1_ROUTINGPATHS */
  {
# if (PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    /* #20 Reset RAM variables which hold the N:1 routing information */
    PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
# endif
# if ((PDUR_TXCONFIRMATIONSUPPORTEDOFRMSRCROM == STD_ON) && ((PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) || ((PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) && (PDUR_MCQBUFFERROM == STD_ON))))
    {
      PduR_RmSrcRomIdxOfRmDestRomType rmSrcRomIdx = PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx);

      /* #30 If upper layer requires a Tx Confirmation */
      if(PduR_IsTxConfirmationSupportedOfRmSrcRom(rmSrcRomIdx)) /* COV_PDUR_FEATURE_ALWAYS_TRUE */
      {
        switch (PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx))
        {
#  if (PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
            /* #40 If Processing type is immediate, call upper layer IF confirmation */
          case PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM:       /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
            PduR_GetUpIfTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcRomIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcRomIdx));   /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
            break;
#  endif
#  if ((PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) && (PDUR_MCQBUFFERROM == STD_ON))
            /* #50 Otherwise if processing is of type DEFERRED and routing type is not IF-buffered */
          case PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM:
#   if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
            if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) != PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM)
#   endif
            {
              /* Destination core in this context is the core of the SrcPdu */
              PduR_CoreManagerRomIdxOfMmRomType destCoreIdx = PduR_GetCoreManagerRomIdxOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx)));
              PduR_CoreManagerRomIdxOfMmRomType srcCoreIdx = PduR_GetCoreManagerRomIdxOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx));

              /* #60 Write Tx Confirmation into multicore queue if queue is not full, otherwise call DET */
              if(PduR_McQ_WriteTxConfirmation(PduR_GetMcQBufferRomIdxOfSrcCoreRom(PduR_GetSrcCoreRomStartIdxOfCoreManagerRom(destCoreIdx) + srcCoreIdx), rmSrcRomIdx) == E_NOT_OK)
              {
                PduR_Det_ReportError(PDUR_FCT_RMIF_TXCONF, PDUR_E_MCQ_QUEUE_OVERFLOW);
              }
            }
            break;
#  endif
          default:     /* COV_PDUR_MISRA */
            /* Nothing to do: This should never be reached */
            break;
        }
      }
    }
# endif

# if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)
    /* #70 If Routing Type is IF-Buffered, indicate the complete transmission */
    if(PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx) == PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM) /* COV_PDUR_FEATURE_ALWAYS_TRUE */
    {
      PduR_RmIf_TxConfirmation(rmGDestRomIdx);
    }
# endif
  }
  else
  {
    PduR_Det_ReportError(PDUR_RMIF_MULTIPLESOURCEHANDLER_TXCONFIRMATION, PDUR_E_PDU_ID_INVALID);
  }
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_SingleBufferHandling
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_SingleBufferHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  (void) PduR_QAL_Put(rmGDest, rmDest, info->SduLength, info->SduDataPtr); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */

  switch (PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDest))
  {
# if (PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
    case PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM: /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
    {
      PduInfoType queuedPduInfo;
      PduR_RmDestRomIterType rmDestRomIdx;

      if(PduR_QAL_Get(rmGDest, &rmDestRomIdx, &queuedPduInfo) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_FATAL_ERROR */
      {
        if(E_OK != PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &queuedPduInfo, FALSE))    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
        {
          PduR_Det_ReportError(PDUR_RMIF_SINGLEBUFFERHANDLING, PDUR_E_PDU_INSTANCES_LOST);
        }
      }
      break;
    }
# endif
# if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
    case PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM:
    {
      /* Set this state to idle so it gets triggered in the mainfunction */
      PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
#  if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
      PduR_EvC_WriteDeferredEventCache(rmDest, rmGDest);
#  endif
      break;
    }
# endif
    default:       /* COV_PDUR_MISRA */
      /* Nothing to do: This should never be reached */
      break;
  }

  PDUR_DUMMY_STATEMENT(rmDest);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}       /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_FifoHandling
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_FifoHandling(PduR_RmDestRomIterType rmDest, PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  boolean triggerTransmission = TRUE;

  if(PduR_QAL_Put(rmGDest, rmDest, info->SduLength, info->SduDataPtr) != E_OK) /* SBSW_PDUR_STACK_VARIABLE */
  {
    PduR_QAL_Flush(rmGDest);
    PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
    PduR_Det_ReportError(PDUR_FCT_RMIF_FQ, PDUR_E_PDU_INSTANCES_LOST);

# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
    PduR_Rm_MultipleSourceHandler_Reset(rmGDest);
# endif

# if (PDUR_ERROR_NOTIFICATION == STD_ON)        /* COV_PDUR_ERROR_NOTIFICATION */
    ErrorNotificationQueueOverflow(PduR_GetDestHndOfRmGDestRom(rmGDest));
# endif

    if(PduR_QAL_Put(rmGDest, rmDest, info->SduLength, info->SduDataPtr) != E_OK)       /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_FATAL_ERROR */
    {
      triggerTransmission = FALSE;
    }
  }

  if((triggerTransmission == TRUE) && (PduR_GetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest)) == PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM)) /* COV_PDUR_ONLY_DIRECT_BUFFER */
  {
    switch (PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDest))
    {
# if (PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
      case PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM: /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
      {
        PduInfoType destPduInfo;
        PduR_RmDestRomIterType rmDestRomIdx;
        PduR_RmBufferedIfPropertiesRomIdxOfRmGDestRomType rmBufferedIfPropertiesRomIdx = PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest);

        if(PduR_QAL_Get(rmGDest, &rmDestRomIdx, &destPduInfo) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_FATAL_ERROR */
        {
          if(E_OK != PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &destPduInfo, TRUE))    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
          {
            PduR_QAL_Flush(rmGDest);
            PduR_Det_ReportError(PDUR_FCT_RMIF_FQ, PDUR_E_PDU_INSTANCES_LOST);
          }
          else
          {
            PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(rmBufferedIfPropertiesRomIdx, PDUR_RM_TX_ACTIVE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
          }
        }
        break;
      }
# endif
# if (PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON)
      case PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM:
      {
#  if (PDUR_DEFERREDEVENTCACHEROM == STD_ON)
        if(PduR_QAL_GetFillLevel(rmGDest) == 1u)
        {/* Only trigger the Pdu once for the first queued element on the destination core */
          PduR_EvC_WriteDeferredEventCache(rmDest, rmGDest);
        }
#  endif
        break;
      }
# endif
      default:       /* COV_PDUR_MISRA */
        /* Nothing to do: This should never be reached */
        break;
    }
  }
}
#endif

/**********************************************************************************************************************
 * PduR_RmIf_SingleBuffer_Put
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_SingleBuffer_Put(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr)  /* PRQA S 3673 */ /* MD_MSR_Rule8.13 */
{
  PduR_SingleBufferRomIdxOfRmBufferedIfPropertiesRomType singleBufferRomIdx = PduR_GetSingleBufferRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  PduR_Core_MemCpyRamToRam(PduR_GetAddrSingleBufferArrayRam(PduR_GetSingleBufferArrayRamStartIdxOfSingleBufferRom(singleBufferRomIdx)), sduDataPtr, pduLength);   /* PRQA S 0315, 3673 */ /* MD_MSR_VStdLibCopy, MD_MSR_Rule8.13 */ /* SBSW_PDUR_MEM_CPY_FIFOMGR */
  PduR_SetActualLengthOfSingleBufferRam(singleBufferRomIdx, pduLength);    /* SBSW_PDUR_CSL01 */

  PDUR_DUMMY_STATEMENT(rmDestRomIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return E_OK;
}
#endif

/**********************************************************************************************************************
 * PduR_RmIf_SingleBuffer_Get
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_SingleBuffer_Get(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  PduR_SingleBufferRomIdxOfRmBufferedIfPropertiesRomType singleBufferRomIdx = PduR_GetSingleBufferRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

  info->SduDataPtr = PduR_GetAddrSingleBufferArrayRam(PduR_GetSingleBufferArrayRamStartIdxOfSingleBufferRom(singleBufferRomIdx)); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  info->SduLength = PduR_GetActualLengthOfSingleBufferRam(singleBufferRomIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  *rmDestRomIdx = PduR_GetRmDestRomIdxOfSingleBufferRom(singleBufferRomIdx); /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
  return E_OK;
}
#endif

#if(PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_RxIndicationNoBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_RxIndicationNoBuffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  PduR_Lock_LockRoutingPathByDestPdu(rmDestIdx);
  if(E_OK != PduR_RmIf_MultipleSourceHandler_Transmit(rmDestIdx, info, FALSE))  /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
  {
    PduR_Det_ReportError(PDUR_FCT_RMIF_FQ, PDUR_E_PDU_INSTANCES_LOST);
  }
  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestIdx);
}
#endif

#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_Forward2Buffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_Forward2Buffer(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  PduR_RmGDestRomIdxOfRmDestRomType rmGDest = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
  PduInfoType destPduInfo;
  PduR_Lock_LockRoutingPathByDestPdu(rmDestIdx);
  destPduInfo.SduDataPtr = info->SduDataPtr;
  destPduInfo.SduLength = PduR_RmIf_TruncateDlc(rmGDest, info);     /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */

  switch (PduR_GetQueueTypeOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx))))
  {
# if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
    case PDUR_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM:
      PduR_RmIf_SingleBufferHandling(rmDestIdx, rmGDest, &destPduInfo);       /* SBSW_PDUR_STACK_VARIABLE */
      break;
# endif
# if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
    case PDUR_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM:
      PduR_RmIf_FifoHandling(rmDestIdx, rmGDest, &destPduInfo);     /* SBSW_PDUR_STACK_VARIABLE */
      break;
# endif
    default:   /* COV_PDUR_MISRA */
      /* Nothing to do: This should never be reached */
      break;
  }

  PduR_Lock_UnlockRoutingPathByDestPdu(rmDestIdx);
}
#endif

#if((PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_RoutePdu
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_RoutePdu(PduR_RmSrcRomIterType rmSrcIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  {
    /* ----- Implementation ----------------------------------------------- */
    PduR_RmDestRomIterType rmDestIdx;

# if (PDUR_SMDATAPLANEROM == STD_ON)
    /* #10 Call switching manager filter function if configured */
    if(PduR_IsSmSrcRomUsedOfRmSrcRom(rmSrcIdx))
    {
      PduR_SmSrcRomIdxOfRmSrcRomType smSrcRomIdx = PduR_GetSmSrcRomIdxOfRmSrcRom(rmSrcIdx);
      PduR_GetSmSrcFilterFctPtr(PduR_GetSmSrcFilterFctPtrIdxOfSmSrcRom(smSrcRomIdx)) (smSrcRomIdx, info);       /* SBSW_PDUR_CSL03 */
    }
# endif

    /* #20 For each destination of 1:N Routing */
    for(rmDestIdx = PduR_GetRmDestRomStartIdxOfRmSrcRom(rmSrcIdx); rmDestIdx < PduR_GetRmDestRomEndIdxOfRmSrcRom(rmSrcIdx); rmDestIdx++)
    {
# if (PDUR_RPGROM == STD_ON)
      /* #30 If Routing path group is enabled */
      if((!PduR_IsRmDestRpgRomUsedOfRmDestRom(rmDestIdx)) || (0u != PduR_GetEnabledCntOfRmDestRpgRam(PduR_GetRmDestRpgRomIdxOfRmDestRom(rmDestIdx))))
# endif
      {
# if (PDUR_SMDATAPLANEROM == STD_ON)
        PduR_RmGDestRomIterType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
        PduR_FilterReturnType filterResult = PDUR_FILTER_PASS;
        /* #40 If Switching manager destination filter function passes or is not configured */
        if(PduR_IsSmGDestRomUsedOfRmGDestRom(rmGDestRomIdx))
        {
          PduR_SmGDestRomIdxOfRmGDestRomType smGDestRomIdx = PduR_GetSmGDestRomIdxOfRmGDestRom(rmGDestRomIdx);
          filterResult = PduR_GetSmGDestFilterFctPtr(PduR_GetSmGDestFilterFctPtrIdxOfSmGDestRom(smGDestRomIdx)) (smGDestRomIdx, info);  /* SBSW_PDUR_CSL03 */
        }
        if(filterResult == PDUR_FILTER_PASS)
# endif
        {
# if (PDUR_MCQBUFFERROM == STD_ON)
          PduR_CoreManagerRomIdxOfMmRomType destCoreIdx = PduR_GetCoreManagerRomIdxOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx)));
          PduR_CoreManagerRomIdxOfMmRomType srcCoreIdx = PduR_GetCoreManagerRomIdxOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestIdx)));

          /* #50 In IF-cross-core routing use case, write data into multicore queue and return E_OK. Call DET, if queue is already full and return E_NOT_OK */
          if((srcCoreIdx != destCoreIdx)
#  if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
             && (PduR_GetRoutingTypeOfRmDestRom(rmDestIdx) != PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM)
#  endif
            )   /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
          {
            if(PduR_McQ_WriteData(PduR_GetMcQBufferRomIdxOfSrcCoreRom(PduR_GetSrcCoreRomStartIdxOfCoreManagerRom(destCoreIdx) + srcCoreIdx), (PduR_RmDestRomEndIdxOfRmSrcRomType) rmDestIdx, info) == E_OK)     /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
            {
              retVal &= E_OK;
            }
            else
            {
              PduR_Det_ReportError(PDUR_FCT_MULTIIFRXIND, PDUR_E_MCQ_QUEUE_OVERFLOW);
              retVal &= E_NOT_OK;
            }
          }
          /* #60 otherwise, call destination Indication function and return it's result */
          else
# endif
          {
            retVal &= PduR_RmIf_DispatchIfDestPdu((PduR_RmDestRomEndIdxOfRmSrcRomType) rmDestIdx, info);        /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR */
          }
        }
      }
      /* #70 Otherwise return E_OK */
    }
  }

  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(retVal); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}
#endif

#if((PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON) || (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_DispatchIfDestPdu
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_DispatchIfDestPdu(PduR_RmDestRomEndIdxOfRmSrcRomType rmDestRomIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  PduR_RmGDestRomIdxOfRmDestRomType rmGDestRomIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

  switch (PduR_GetRoutingTypeOfRmDestRom(rmDestRomIdx))
  {
# if (PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
    case PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM:
      PduR_GetUpIfRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), info);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      retVal = E_OK;
      break;
# endif
# if (PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM == STD_ON)
    case PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM:
      retVal = PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, info, !PduR_IsRmDestRomUsedOfRmGDestRom(rmGDestRomIdx));  /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      break;
# endif
# if (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)
    case PDUR_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM:
      retVal = PduR_RmIf_ProcessNoBufferedGwRouting(rmDestRomIdx, info);        /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      break;
# endif
# if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
    case PDUR_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM:
      retVal = PduR_RmIf_ProcessBufferedRouting(PduR_GetRmSrcRomIdxOfRmDestRom(rmDestRomIdx), rmDestRomIdx, rmGDestRomIdx, info);       /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      break;
# endif
    default:   /* COV_PDUR_MISRA */
      /* Nothing to do: This should never be reached */
      break;
  }

  return retVal;
}
#endif

#if (PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_ProcessNoBufferedGwRouting
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessNoBufferedGwRouting(PduR_RmDestRomIterType rmDestIdx, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* Check parameter 'info' */
  if(info == NULL_PTR)  /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(info->SduDataPtr == NULL_PTR) /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
    PduR_RmIf_RxIndicationNoBuffer(rmDestIdx, info);    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    retVal = E_OK;
  }
/* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)        /* COV_PDUR_CROSSCORE_ROUTINGS_ONLY */
  {
    PduR_Det_ReportError(PDUR_FCT_MULTIIFRXIND, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}
#endif

#if (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_ProcessBufferedRouting
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_ProcessBufferedRouting(PduR_RmSrcRomIterType rmSrcIdx, PduR_RmDestRomIterType rmDestIdx, PduR_RmGDestRomIterType rmGDestRomIdx,
                                                                              P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* Check parameter 'info' */
  if(info == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(info->SduDataPtr == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
# if (PDUR_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM == STD_ON)
    if((PduR_GetPduLengthHandlingStrategyOfRmDestRom(rmDestIdx) == PDUR_SHORTEN_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM)
       || (info->SduLength <= PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))))
# endif
    {
# if (PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM == STD_ON)
      if(PduR_IsTriggerTransmitSupportedOfRmSrcRom(rmSrcIdx))
      {
        uint8 sduData[PDUR_MAX_TRIGGER_TRANSMIT_PDU_SIZE] = { 0u };
        PduInfoType pduInfo;
        pduInfo.SduDataPtr = sduData;
        pduInfo.SduLength = PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx));

        retVal &= PduR_GetUpIfTriggerTransmitFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx), &pduInfo);        /* SBSW_PDUR_CSL03 */
        PduR_RmIf_Forward2Buffer(rmDestIdx, &pduInfo);  /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
      }
      else
# endif
      {
        PduR_RmIf_Forward2Buffer(rmDestIdx, info);      /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
        retVal &= E_OK;
      }

# if ((PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM == STD_ON) && (PDUR_TXCONFIRMATIONSUPPORTEDOFRMSRCROM == STD_ON))
      if(PduR_GetPduRDestPduProcessingOfRmGDestRom(rmGDestRomIdx) == PDUR_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM)   /* COV_PDUR_FEATURE_ALWAYS_TRUE */
      {
        /* Call upper layer confirmation immediately */
        if(PduR_IsTxConfirmationSupportedOfRmSrcRom(rmSrcIdx))
        {
          PduR_GetUpIfTxConfirmationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmSrcRom(rmSrcIdx)) (PduR_GetSrcHndOfRmSrcRom(rmSrcIdx));       /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
        }
      }
# endif
    }
  }
/* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_MULTIIFRXIND, errorId);
  }
# endif
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(rmSrcIdx);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(rmGDestRomIdx);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_TriggerTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_RmIf_TriggerTransmit(PduR_RmDestRomIterType rmDestIdx, CONSTP2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  Std_ReturnType retVal = E_NOT_OK;     /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = PDUR_E_NO_ERROR;      /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* ----- Development Error Checks ------------------------------------- */
# if (PDUR_DEV_ERROR_DETECT == STD_ON)  /* COV_PDUR_VAR_DEV_ERROR_DETECT */
  /* Check parameter 'info' */
  if(info == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else if(info->SduDataPtr == NULL_PTR)
  {
    errorId = PDUR_E_PARAM_POINTER;
  }
  else
# endif
  {
    PduR_Lock_LockRoutingPathByDestPdu(rmDestIdx);
    {
      PduR_RmGDestRomIterType rmGDestIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestIdx);
      PduInfoType queuedPduInfo;
      PduR_RmDestRomIterType rmDestRomIdx;

      if(PduR_QAL_Get(rmGDestIdx, &rmDestRomIdx, &queuedPduInfo) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_FATAL_ERROR */
      {
        if(info->SduLength >= queuedPduInfo.SduLength)
        {
          info->SduLength = queuedPduInfo.SduLength; /* SBSW_PDUR_VALID_PTR_ENSURED_BY_CALLING_FUNCTION */
          PduR_Core_MemCpyRamToRam(info->SduDataPtr, queuedPduInfo.SduDataPtr, queuedPduInfo.SduLength);  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_PDUR_MEM_CPY_FIFOMGR */
          retVal = E_OK;
        }
      }
    }
    PduR_Lock_UnlockRoutingPathByDestPdu(rmDestIdx);
  }
  /* ----- Development Error Report --------------------------------------- */
# if (PDUR_DEV_ERROR_REPORT == STD_ON)
  if(errorId != PDUR_E_NO_ERROR)
  {
    PduR_Det_ReportError(PDUR_FCT_RMIF_TXTT, errorId);
  }
# else
  PDUR_DUMMY_STATEMENT(errorId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
# endif
  return retVal;
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_TxConfirmation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation(PduR_RmGDestRomIdxOfTxIf2UpType rmGDestRomIdx)
{
  PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
  {
    PduR_GetFctPtrOfRmIf_TxConfirmation_StateHandler(PduR_GetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) ((PduR_RmGDestRomIterType) rmGDestRomIdx);  /* SBSW_PDUR_CSL03 */
  }
  PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
}
#endif

#if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_TxConfirmation_StateHandler_RM_TX_ACTIVE
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation_StateHandler_RM_TX_ACTIVE(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduInfoType destPduInfo;
  PduR_RmDestRomIterType rmDestRomIdx;

  PduR_QAL_Remove(rmGDestRomIdx);

  if(PduR_QAL_Get(rmGDestRomIdx, &rmDestRomIdx, &destPduInfo) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */
  {
    if(E_OK != PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &destPduInfo, TRUE))    /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
    {
      PduR_QAL_Flush(rmGDestRomIdx);
      PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
      PduR_Det_ReportError(PDUR_FCT_RMIF_TXCONF, PDUR_E_PDU_INSTANCES_LOST);
    }
  }
  else
  {
    PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
  }
}       /* PRQA S 6050 */ /* MD_MSR_STCAL */
#endif

#if(PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_TxConfirmation_StateHandler_RM_TX_IDLE
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_TxConfirmation_StateHandler_RM_TX_IDLE(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_QAL_Flush(rmGDestRomIdx);
  PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */

# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
  PduR_Rm_MultipleSourceHandler_Reset(rmGDestRomIdx);
# endif
  PduR_Det_ReportError(PDUR_FCT_RMIF_TXCONF, PDUR_E_PDU_INSTANCES_LOST);
}
#endif

#if(PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON)
/**********************************************************************************************************************
 * PduR_RmIf_TruncateDlc
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(PduLengthType, PDUR_CODE) PduR_RmIf_TruncateDlc(PduR_RmGDestRomIdxOfRmDestRomType rmGDest, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  /* if the length is shorter or equal use the provided length */
  PduLengthType dataLengthcopy = info->SduLength;
  /* MaxPduLength of no buffer routings is set to the maximum allowed value for this datatype, thus disabling this check */
  if(info->SduLength > PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest)))
  {
    /* if the provided length is greater than the maximum buffer size the value is truncated to this value. */
    dataLengthcopy = PduR_GetMaxPduLengthOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDest));
  }
  PDUR_DUMMY_STATEMENT(rmGDest);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  return dataLengthcopy;
}
#endif

/**********************************************************************************************************************
 * PduR_QAL_Put
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
#if ((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_QAL_Put(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr)
{
  return PduR_GetPutFctPtrOfQueueFctPtrRom(PduR_GetQueueFctPtrRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx, rmDestRomIdx, pduLength, sduDataPtr); /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
}
#endif

#if ((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) || (PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
/**********************************************************************************************************************
 * PduR_QAL_Get
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(Std_ReturnType, PDUR_CODE) PduR_QAL_Get(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  return PduR_GetGetFctPtrOfQueueFctPtrRom(PduR_GetQueueFctPtrRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx, rmDestRomIdx, info); /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
}
#endif

#if (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_QAL_Remove
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_QAL_Remove(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_GetRemoveFctPtrOfQueueFctPtrRom(PduR_GetQueueFctPtrRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx); /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
}
#endif

#if ((PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) && (PDUR_DEFERREDEVENTCACHEROM == STD_ON))
/**********************************************************************************************************************
 * PduR_QAL_GetFillLevel
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(uint16, PDUR_CODE) PduR_QAL_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  return PduR_GetGetFillLevelFctPtrOfQueueFctPtrRom(PduR_GetQueueFctPtrRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx); /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
}
#endif

#if (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
/**********************************************************************************************************************
 * PduR_QAL_Flush
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, PDUR_CODE) PduR_QAL_Flush(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  PduR_GetFlushFctPtrOfQueueFctPtrRom(PduR_GetQueueFctPtrRomIdxOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx))) (rmGDestRomIdx); /* SBSW_PDUR_API_CALL_FORWARDING_ID_ONLY */
}
#endif

#if((PDUR_MAIN_FUNCTION == STD_ON) && (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_MainFunction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_MainFunction(PduR_RmGDestRomIterType rmGDestRomIdx)
{
  /* #10 If Pdu is a deferred IF-Pdu and processing is required */
  if(PduR_IsRmBufferedIfPropertiesRomUsedOfRmGDestRom(rmGDestRomIdx)
      && (PduR_GetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx)) == PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM))      /* COV_PDUR_ROBUSTNESS */
  {
    PduR_Lock_LockRoutingPathByGDestPdu(rmGDestRomIdx);
    {
      switch (PduR_GetDirectionOfRmGDestRom(rmGDestRomIdx))
      {
# if(PDUR_EXISTS_TX_DIRECTIONOFRMGDESTROM == STD_ON)    /* COV_PDUR_VAR_NO_RX_ONLY_CONFIG */
          /* #20 If direction of global dest Pdu is TX */
        case PDUR_TX_DIRECTIONOFRMGDESTROM:
        {
          PduInfoType destPduInfo;
          PduR_RmDestRomIterType rmDestRomIdx;

          /* #30 Get buffered PduInfo and trigger the transmission on the destination buses */
          if(PduR_QAL_Get(rmGDestRomIdx, &rmDestRomIdx, &destPduInfo) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */ /* COV_PDUR_ROBUSTNESS */
          {
            Std_ReturnType retValTramsmit = E_NOT_OK;   /* PRQA S 2981 */ /* MD_MSR_RetVal */

#  if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
            if(PduR_GetQueueTypeOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx)) == PDUR_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM)      /* COV_PDUR_FEATURE_ALWAYS_TRUE */ /* PRQA S 2995, 2996, 2991 */ /* MD_PduR_2995_2996, MD_PduR_2995_2996, MD_PduR_2991 */
            {
              retValTramsmit = PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &destPduInfo, FALSE);     /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
              PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_ACTIVE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
              if(retValTramsmit != E_OK)
              {
                PduR_Det_ReportError(PDUR_FCT_MAINFUNCTION_TX, PDUR_E_PDU_INSTANCES_LOST);
                PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
              }
            }
#  endif
#  if((PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON) && (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
            else
#  endif
#  if (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
            {
              retValTramsmit = PduR_RmIf_MultipleSourceHandler_Transmit(rmDestRomIdx, &destPduInfo, TRUE);      /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */ /* PRQA S 2880 */ /* MD_PduR_2880 */
              /* #40 Reset routing if transmit failed and release the TxBuffer */
              if(retValTramsmit == E_OK)
              {
                PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_ACTIVE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
              }
              else
              {
                PduR_QAL_Flush(rmGDestRomIdx);
                PduR_Det_ReportError(PDUR_FCT_MAINFUNCTION_TX, PDUR_E_PDU_INSTANCES_LOST);
                PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestRomIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);      /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
              }
            }
#  endif
          }
          break;
        }
# endif
# if((PDUR_EXISTS_RX_DIRECTIONOFRMGDESTROM == STD_ON) && (PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON))
          /* #50 If direction of global dest Pdu is RX, get buffered PduInfo and call upper layer IF Rx Indication function */
        case PDUR_RX_DIRECTIONOFRMGDESTROM:
        {
          PduInfoType destPduInfo;
          PduR_RmDestRomIterType rmDestRomIdx;

          while(PduR_QAL_Get(rmGDestRomIdx, &rmDestRomIdx, &destPduInfo) == E_OK) /* SBSW_PDUR_STACK_VARIABLE */
          {
            PduR_GetUpIfRxIndicationFctPtrOfMmRom(PduR_GetMmRomIdxOfRmGDestRom(rmGDestRomIdx)) (PduR_GetDestHndOfRmGDestRom(rmGDestRomIdx), &destPduInfo);        /* SBSW_PDUR_API_CALL_FORWARDING_ID_AND_PTR */
            PduR_QAL_Remove(rmGDestRomIdx);
          }
          break;
        }
# endif
        default:       /* COV_PDUR_MISRA */
          /* Will never be reached */
          break;
      }
    }
    PduR_Lock_UnlockRoutingPathByGDestPdu(rmGDestRomIdx);
  }
}       /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if ((PDUR_RPGROM == STD_ON) && (PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM == STD_ON))
/**********************************************************************************************************************
 * PduR_RmIf_DisableRoutingAction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_RmIf_DisableRoutingAction(PduR_RmDestRomIterType rmDestRomIdx)
{
  PduR_RmGDestRomIterType rmGDestIdx = PduR_GetRmGDestRomIdxOfRmDestRom(rmDestRomIdx);

  switch (PduR_GetQueueTypeOfRmBufferedIfPropertiesRom(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestIdx)))
  {
# if(PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
    case PDUR_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM:
      {
        PDUR_DUMMY_STATEMENT(rmGDestIdx);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
      }
      break;
# endif
# if(PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM == STD_ON)
    case PDUR_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM:
      PduR_QAL_Flush(rmGDestIdx);
      PduR_SetIfSmStateOfRmBufferedIfPropertiesRam(PduR_GetRmBufferedIfPropertiesRomIdxOfRmGDestRom(rmGDestIdx), PDUR_RM_TX_IDLE_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM);    /* SBSW_PDUR_IDX_PARAM_INTERNAL_FUNCTION */
      break;
# endif
    default:   /* COV_PDUR_MISRA */
      /* Nothing to do: This should never be reached */
      break;
  }

# if(PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM == STD_ON)
  PduR_Rm_MultipleSourceHandler_Reset(rmGDestIdx);
# endif
}
#endif

#define PDUR_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */   /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: PduR_RmIf.c
 *********************************************************************************************************************/
