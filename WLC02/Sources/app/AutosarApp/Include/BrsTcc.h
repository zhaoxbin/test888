
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  BrsTcc.h
      Project:  Vector Basic Runtime System
       Module:  BrsTcc

  \brief Description:  Header of static Test Control Center code.

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

#ifndef _BRSTCC_H_
#define _BRSTCC_H_

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "BrsMain.h"

#ifndef _MICROSOFT_C_VTT_
  #include "BrsHw.h"
#endif

#if defined (BRS_ENABLE_TCC_TCM_SUPPORT) && !defined (COMSTACK_TYPES_H)
typedef uint8 PduIdType;
typedef uint8 PduLengthType;
typedef uint8* SduDataPtrType;

typedef struct
{
  SduDataPtrType SduDataPtr;
  PduLengthType SduLength;
}PduInfoType;
#endif /*BRS_ENABLE_TCC_TCM_SUPPORT && !COMSTACK_TYPES_H*/

#include "BrsTccCfg.h"

/* Normally, this define is generated from TGF into _Tgf_Compiler_Cfg.h */
/* if necessary, you can setup Compiler_Cfg.h changes in here */
#ifndef BRSTCC_DATA
  #define BRSTCC_DATA
#endif

/**********************************************************************************************************************
  MODULE VERSION
**********************************************************************************************************************/
/*
 * Description: This is the BrsHw main and bug fix version. The version numbers are BCD coded. 
 *              E.g. a main version of 1.23 is coded with 0x0123, a bug fix version of 9 is coded 0x09.
 */
#define BRSTCC_VERSION        0x0102u
#define BRSTCC_BUGFIX_VERSION 0x02u

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
#if defined (BRS_ENABLE_TCC_COMIF_SUPPORT) || defined (BRS_ENABLE_TCC_TCM_SUPPORT)
/* TCC Service Ids
   Ids to be used to demultiplex the TCC message. */
#define BRSTCC_FCT_RDBI   0x22 /* Read data by ID */
#define BRSTCC_FCT_RMBA   0x23 /* Read memory by address */
#define BRSTCC_FCT_WDBI   0x2e /* Write date by ID */
#define BRSTCC_FCT_WMBA   0x2d /* Write memory by address */
#define BRSTCC_FCT_STR    0x31 /* Start routine */
#define BRSTCC_FCT_STP    0x32 /* Stop routine */
#define BRSTCC_FCT_RRR    0x33 /* Return routine results */

# if defined (BRSHW_CYCLES_PER_DELAY_LOOP)
  #define BRSTCC_MEASURE_CYCLES_PER_DELAY_LOOP_ENABLE  STD_OFF /* user config switch: set to STD_ON to enable
                                                                  TCM_CLK_OUT pin toggle measurement. */
# endif

#define BRSTCC_DELAY_CYCLES(usec)  (uint32)(usec * BRS_TIMEBASE_CLOCK) /* number of CPU cycles to achieve delay in usec */

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
  brsTccBuffer
**********************************************************************************************************************/
/** \brief    The global tcc buffer.
    \note     The buffer is used by the BrsTcc and Tcc Application.
    \warning  Refer to http://wiki.vi.vector.int/wiki-pes/TestControlCenter
**********************************************************************************************************************/
#define START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"

extern uint8 brsTccBuffer[8];

#define STOP_SEC_VAR
#include "MemMap.h"

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
  BrsTcc_Init
**********************************************************************************************************************/
/** \brief    This function initializes the BrcTcc.
    \param    none
    \return   none
    \pre      none
    \context  The function must be called on task level and has not to be interrupted
              by other administrative function calls.
    \note     The function is called by the BrsAsrMain module (BrsAsrMainInit()).
    \warning  BrsTcc_Init shall not pre-empt any BrsTcc function.
**********************************************************************************************************************/
void BrsTcc_Init(void);

/***********************************************************************************************************************
 *  BrsTccSendResponse
 **********************************************************************************************************************/
/** \brief    This function triggers a transmission request on the communication hardware abstraction layer.
    \param    none
    \return   none
    \pre      brsTccBuffer has to be prepared with the data to be transmitted.
    \note     The function is used by the Tcc Application.
 **********************************************************************************************************************/
void BrsTccSendResponse(void);

/**********************************************************************************************************************
  BrsTccSendNegResponse
**********************************************************************************************************************/
/** \brief    This function triggers a transmission request on the communication hardware abstraction layer of a negative Tcc response.
    \param    ErrorCode  TccErrorCodes
    \return   none
    \pre      A Tcc command has been failed.
    \context  The function must be called in the context of the BrsTcc_RxIndication.
    \note     The function is used by the Tcc Application.
**********************************************************************************************************************/
void BrsTccSendNegResponse(uint8 errorCode);

/**********************************************************************************************************************
  BrsTccSendPosResponse
**********************************************************************************************************************/
/** \brief    This function triggers a transmission request on the communication hardware abstraction layer of a positive Tcc response.
    \param    none
    \return   none
    \pre      The BrsTcc has been initialized and
              the respone data has to be filled into the brsTccBuffer.
    \context  The function must be called in the context of the BrsTcc_RxIndication.
    \note     The function is used by the Tcc Application.
**********************************************************************************************************************/
void BrsTccSendPosResponse(void);

void BrsTcc_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, BRSTCC_DATA) PduInfoPtr);

void BrsTcc_TxConfirmation(PduIdType TxPduId);

Std_ReturnType BrsTcc_TriggerTransmit(PduIdType TxPduId, CONSTP2VAR(PduInfoType, AUTOMATIC, BRSTCC_DATA) PduInfoPtr);

#if defined (BRSHW_CYCLES_PER_DELAY_LOOP)
/**********************************************************************************************************************
  BrsTcc_Delay
**********************************************************************************************************************/
/** \brief    This function implements a dummy loop for waiting specified time in microseconds.
    \param    none
    \return   nobe
    \pre      BRSHW_CYCLES_PER_DELAY_LOOP is defined in BrsHw.
    \context  The function is called by TcmDriver during I2C communication.
    \note     BRSHW_CYCLES_PER_DELAY_LOOP needs to be calibrated when changing compiler optimisation, clock frequency 
              or switching to another microcontroller platform. Use BrsTcc_MeasureCyclesPerDelayLoopInMSec() then.
**********************************************************************************************************************/
void BrsTcc_Delay(int usec);

/**********************************************************************************************************************
  BrsTcc_MeasureCyclesPerDelayLoopInMSec
**********************************************************************************************************************/
/** \brief    This function cyclically alternates TCM_CLK pin using BrsTcc_Delay in endless loop to enable measurement.
              One half cycle time of signal toogle in msec: _|<-->|____|----|_ (e.g. 6 ms)
    \param    none
    \return   never - endless loop inside!
    \pre      BrsHw clocks and ports have been initialized. BRSHW_CYCLES_PER_DELAY_LOOP is defined in BrsHw.
              BRSTCC_MEASURE_CYCLES_PER_DELAY_LOOP_ENABLE is defined as STD_ON
    \context  The function must be called in the context of the BrsAsrMainInit().
    \note     The function is used by user for measurement only. 
**********************************************************************************************************************/
void BrsTcc_MeasureCyclesPerDelayLoopInMSec(void);
#endif /*BRSHW_CYCLES_PER_DELAY_LOOP*/

#define STOP_SEC_CODE
#include "MemMap.h"

#endif /*BRS_ENABLE_TCC_COMIF_SUPPORT || BRS_ENABLE_TCC_TCM_SUPPORT*/

#endif /*_BRSTCC_H_*/
