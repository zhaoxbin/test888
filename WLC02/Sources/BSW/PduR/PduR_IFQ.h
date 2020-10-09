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
 *         File:  PduR_IFQ.h
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
#if !defined (PDUR_IFQ_H)
# define PDUR_IFQ_H

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
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
  PduR_IFQ_Init
**********************************************************************************************************************/
/*! \brief       This function initializes the interface fifo queue administration values.
 *  \details     -
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 ********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_IFQ_Init(void);
# endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_PutFifo
 *********************************************************************************************************************/
/*! \brief      Writes a Pdu to the queue.
 *  \details    -
 *  \param[in]  rmGDestRomIdx             id of the global destination Pdu to be queued
 *  \param[in]  rmDestRomIdx              Index to the destination Pdu to be queued
 *  \param[in]  pduLength                 Pdu length
 *  \param[in]  sduDataPtr                pointer to the Pdu's data
 *  \return     true                      write to the queue was successful
 *              false                     write to the queue was not successful
 *  \pre        -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_IFQ_PutFifo(PduR_RmGDestRomIterType rmGDestRomIdx, PduR_RmDestRomIterType rmDestRomIdx, PduLengthType pduLength, SduDataPtrType sduDataPtr);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetNextElement
 *********************************************************************************************************************/
/*! \brief      Get the pointer to the next Pdu in the queue
 *  \details    -
 *  \param[in]  rmGDestRomIdx             id of the global destination Pdu to be queued
 *  \param[out] rmDestRomIdx              Index to the destination Pdu to be queued
 *  \param[out] info                      pointer to the Pdu's data
 *  \return     true                      next Pdu was read successfully
 *              false                     no Pdu could be found. The queue is empty.
 *  \pre        -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_IFQ_GetNextElement(PduR_RmGDestRomIterType rmGDestRomIdx, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA) rmDestRomIdx, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_RemoveElement
 *********************************************************************************************************************/
/*! \brief      Removes the oldest Pdu from the queue
 *  \details    -
 *  \param[in]  rmGDestRomIdx  id of the global destination Pdu to be queued
 *  \pre        -
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_IFQ_RemoveElement(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_FlushQueue
 *********************************************************************************************************************/
/*! \brief      Flushes and resets the queue
 *  \details    -
 *  \param[in]  rmGDestRomIdx  id of the global destination Pdu to be queued
 *  \pre        -
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_IFQ_FlushQueue(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

#if(PDUR_INTERFACEFIFOQUEUEROM == STD_ON)
/**********************************************************************************************************************
 * PduR_IFQ_GetFillLevel
 *********************************************************************************************************************/
/*! \brief      Gets the fill level of the queue
 *  \details    -
 *  \param[in]  rmGDestRomIdx  id of the global destination Pdu to be queued
 *  \return     the fill level
 *  \pre        -
 *********************************************************************************************************************/
FUNC(uint16, PDUR_CODE) PduR_IFQ_GetFillLevel(PduR_RmGDestRomIterType rmGDestRomIdx);
#endif

# define PDUR_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */
#endif /* PDUR_IFQ_H */
/**********************************************************************************************************************
 *  END OF FILE: PduR_IFQ.h
 *********************************************************************************************************************/
