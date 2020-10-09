/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* STARTSINGLE_OF_MULTIPLE */

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
 *  -----------------------------------------------------------------------------------------------------------------*/
/*  \file         Can.c / Can_Irq.c / Can_Local.h
 *  \brief        Can source file
 *  \details      Implementation of the CAN driver
 *
 *********************************************************************************************************************/

 /*********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#if !defined(CAN_LOCAL_H)
#define  CAN_LOCAL_H

/***************************************************************************/
/* Include                                                                 */
/***************************************************************************/
/* \trace SPEC-1583 */
#include "SchM_Can.h"
#include "Can.h"         /* include also all needed types */

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_COREVERSION           != 0x0800u) /* \trace SPEC-1699 */
# error "Header file are inconsistent!"
#endif
#if (CAN_RELEASE_COREVERSION   != 0x00u)
# error "Header file are inconsistent!"
#endif
#if (DRVCAN_SH2RSCANASR_VERSION         != 0x0606u)
# error "Source and header files are inconsistent!"
#endif
#if (DRVCAN_SH2RSCANASR_RELEASE_VERSION != 0x00u)
# error "Source and header files are inconsistent!"
#endif
#if (CAN_GEN_SH2RSCANASR_VERSION        != 0x0302u)
# error "Static code and generated data are inconsistent!"
#endif

/* PRQA S 3453 EOF */ /* MD_MSR_FctLikeMacro */

/***************************************************************************/
/* compatibility defines                                                   */
/***************************************************************************/
#if defined(C_ENABLE_MIXED_ID) || defined(C_ENABLE_EXTENDED_ID)
# define CAN_ID_IDE_MASK            0x80000000UL
# define CAN_ID_FD_MASK             0x40000000UL /* \trace SPEC-50553 */
# define CAN_ID_MASK                0x1FFFFFFFUL
# define CAN_ID_MASK_STD            0x000007FFUL
# define CAN_ID_UNUSED_MASK         0x20000000UL
#else
# define CAN_ID_IDE_MASK            0x0000U
# define CAN_ID_FD_MASK             0x4000U /* \trace SPEC-50553 */
# define CAN_ID_MASK                0x07FFU
# define CAN_ID_MASK_STD            0x07FFU
# define CAN_ID_UNUSED_MASK         0x3800U
#endif
#define kCanAllChannels  ((CanChannelHandle)0xFFU)

#if !defined(C_DRV_INTERNAL) /* COV_CAN_INTERNAL */
# error "Can_Local.h should only be included by Can.c"
#endif
/* real amount of controllers in this system (LT and PB) */
#define kCanNumberOfChannels  Can_GetControllerMax()
/* if kCanNumberOfChannels used to declare a table/dimension this table has to be generated to be also Link-Time-capable */
/*  -> see ESCAN00028069 controller-amount has to be Link-Time-capable */
/* real amount of controllers in this system (LT and PB) */
#define kCanNumberOfHwChannels  kCanNumberOfChannels

#if defined( C_SINGLE_RECEIVE_CHANNEL )
/* have to be done here to avoid declaration of "channel" in Can.h */
# define channel                                ((CanChannelHandle)0)
# define canHwChannel                           ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STARTINDEX(ch)       ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STOPINDEX(ch)        ((CanChannelHandle)0)
#else
# define channel                                Controller
# define canHwChannel                           Controller
# define CAN_HL_HW_CHANNEL_STARTINDEX(ch)       (ch)
# define CAN_HL_HW_CHANNEL_STOPINDEX(ch)        (ch)
#endif
#if !defined(CAN_TRANSITION_CHECK) /* COV_CAN_COMPATIBILITY */
# define CAN_TRANSITION_CHECK STD_ON /* default may be deactivated by user configuration */
#endif
#if !defined(CAN_REINIT_START) /* COV_CAN_COMPATIBILITY */
# define CAN_REINIT_START STD_OFF
#endif

#if !defined(CAN_OS_TICK2MS) /* COV_CAN_COMPATIBILITY */
# error "CAN_OS_TICK2MS() should be defined to OS_TICKS2MS_<counterShortName>() macro from OS"
#endif
#if !defined(CAN_OS_COUNTER_ID) /* COV_CAN_COMPATIBILITY */
# error "CAN_OS_COUNTER_ID should be defined to 'counterShortName' from OS"
#endif

#if !defined(CAN_ID_MASK_IN_GENERIC_CALLOUT) /* COV_CAN_COMPATIBILITY */
# define CAN_ID_MASK_IN_GENERIC_CALLOUT (CAN_ID_IDE_MASK | CAN_ID_FD_MASK | CAN_ID_MASK)
/* May be changed to mask out FD-bit: (CAN_ID_IDE_MASK | CAN_ID_MASK) */
#endif


/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
/* for variable Can_ActiveSendState */
#define kCanBufferFree              (uint8)0xFF     /* mark objects as free */
#define kCanBufferCancel            (uint8)0xFE     /* mark object as currently cancelling */
#define kCanBufferCancelSw          (uint8)0xFD
#define kCanBufferSend              (uint8)0x01     /* occupied send object */

/* HL return values */
#define kCanFailed                  (uint8)0x00     /* similar to CAN_NOT_OK but value may differ --> converted in HL (LL only use kCan...) */
#define kCanOk                      (uint8)0x01     /* similar to CAN_OK */
#define kCanRequested               (uint8)0x03

#define kCanFalse                   kCanFailed
#define kCanTrue                    kCanOk

#define Can_GetControllerMax()                        Can_GetSizeOfControllerData()
#define Can_GetCanToCanIfChannelMapping(Index)        Can_GetCanIfChannelId((Index))

/* ControllerConfig */
#define Can_GetCanControllerDefaultBaudrate(logCh)    Can_GetCanControllerDefaultBaudrateOfControllerConfig(logCh)
#define Can_GetCanControllerDefaultBaudrateIdx(logCh) Can_GetCanControllerDefaultBaudrateIdxOfControllerConfig(logCh)
#if !defined(Can_GetMailboxRxBasicLengthOfControllerConfig) /* If no Object is available ComStackLib do not generate start-stop index */
# define Can_GetMailboxRxBasicLengthOfControllerConfig(logCh) 0u
# define Can_GetMailboxRxBasicStartIdxOfControllerConfig(logCh) 0u
# define Can_GetMailboxRxBasicEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_GetRxBasicHandleMax(logCh)                Can_GetMailboxRxBasicLengthOfControllerConfig(logCh)
#define Can_GetRxBasicHandleStart(logCh)              (Can_HwHandleType)Can_GetMailboxRxBasicStartIdxOfControllerConfig(logCh)
#define Can_GetRxBasicHandleStop(logCh)               (Can_HwHandleType)Can_GetMailboxRxBasicEndIdxOfControllerConfig(logCh)
#define Can_GetRxBasicHwStart(logCh)                  Can_GetRxBasicHwStartOfControllerConfig(logCh)
#define Can_GetRxBasicHwStop(logCh)                   Can_GetRxBasicHwStopOfControllerConfig(logCh)
#if !defined(Can_GetMailboxRxFullLengthOfControllerConfig)
# define Can_GetMailboxRxFullLengthOfControllerConfig(logCh) 0u
# define Can_GetMailboxRxFullStartIdxOfControllerConfig(logCh) 0u
# define Can_GetMailboxRxFullEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_GetRxFullHandleMax(logCh)                 Can_GetMailboxRxFullLengthOfControllerConfig(logCh)
#define Can_GetRxFullHandleStart(logCh)               (Can_HwHandleType)Can_GetMailboxRxFullStartIdxOfControllerConfig(logCh)
#define Can_GetRxFullHandleStop(logCh)                (Can_HwHandleType)Can_GetMailboxRxFullEndIdxOfControllerConfig(logCh)
#define Can_GetRxFullHwStart(logCh)                   Can_GetRxFullHwStartOfControllerConfig(logCh)
#define Can_GetRxFullHwStop(logCh)                    Can_GetRxFullHwStopOfControllerConfig(logCh)
#if !defined(Can_GetMailboxTxBasicLengthOfControllerConfig) /* COV_CAN_GENDATA_FAILURE */
# define Can_GetMailboxTxBasicLengthOfControllerConfig(logCh) 0u
# define Can_GetMailboxTxBasicStartIdxOfControllerConfig(logCh) 0u
# define Can_GetMailboxTxBasicEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_GetTxBasicHandleMax(logCh)                Can_GetMailboxTxBasicLengthOfControllerConfig(logCh)
#define Can_GetTxBasicHandleStart(logCh)              (Can_HwHandleType)Can_GetMailboxTxBasicStartIdxOfControllerConfig(logCh)
#define Can_GetTxBasicHandleStop(logCh)               (Can_HwHandleType)Can_GetMailboxTxBasicEndIdxOfControllerConfig(logCh)
#define Can_GetTxBasicHwStart(logCh)                  Can_GetTxBasicHwStartOfControllerConfig(logCh)
#define Can_GetTxBasicHwStop(logCh)                   Can_GetTxBasicHwStopOfControllerConfig(logCh)
#if !defined(Can_GetMailboxTxFullLengthOfControllerConfig)
# define Can_GetMailboxTxFullLengthOfControllerConfig(logCh) 0u
# define Can_GetMailboxTxFullStartIdxOfControllerConfig(logCh) 0u
# define Can_GetMailboxTxFullEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_GetTxFullHandleMax(logCh)                 Can_GetMailboxTxFullLengthOfControllerConfig(logCh)
#define Can_GetTxFullHandleStart(logCh)               (Can_HwHandleType)Can_GetMailboxTxFullStartIdxOfControllerConfig(logCh)
#define Can_GetTxFullHandleStop(logCh)                (Can_HwHandleType)Can_GetMailboxTxFullEndIdxOfControllerConfig(logCh)
#define Can_GetTxFullHwStart(logCh)                   Can_GetTxFullHwStartOfControllerConfig(logCh)
#define Can_GetTxFullHwStop(logCh)                    Can_GetTxFullHwStopOfControllerConfig(logCh)
#if !defined(Can_GetMailboxUnusedLengthOfControllerConfig)  /* COV_CAN_GENDATA_FAILURE */
# define Can_GetMailboxUnusedLengthOfControllerConfig(logCh) 0u
# define Can_GetMailboxUnusedStartIdxOfControllerConfig(logCh) 0u
# define Can_GetMailboxUnusedEndIdxOfControllerConfig(logCh) 0u
#endif
#define Can_GetUnusedHandleMax(logCh)                 Can_GetMailboxUnusedLengthOfControllerConfig(logCh)
#define Can_GetUnusedHandleStart(logCh)               (Can_HwHandleType)Can_GetMailboxUnusedStartIdxOfControllerConfig(logCh)
#define Can_GetUnusedHandleStop(logCh)                (Can_HwHandleType)Can_GetMailboxUnusedEndIdxOfControllerConfig(logCh)
#define Can_GetUnusedHwStart(logCh)                   Can_GetUnusedHwStartOfControllerConfig(logCh)
#define Can_GetUnusedHwStop(logCh)                    Can_GetUnusedHwStopOfControllerConfig(logCh)

/* Mailbox */
/* GetMailboxSize: logical size of mailbox - use LL specific generated data to get hardware object size if needed */
#define Can_GetMailboxSize(htrh)                      Can_GetMailboxSizeOfMailbox(htrh)
#define Can_GetMailboxHwHandle(htrh)                  Can_GetHwHandleOfMailbox(htrh)
#define Can_GetMailboxIDValue(htrh)                   Can_GetIDValueOfMailbox(htrh)
#define Can_GetMailboxType(htrh)                      Can_GetMailboxTypeOfMailbox(htrh)
#define Can_GetMailboxDataLen(htrh)                   Can_GetMaxDataLenOfMailbox(htrh)
#define Can_GetMailboxFdPadding(htrh)                 Can_GetFdPaddingOfMailbox(htrh)
#define Can_GetMailboxController(htrh)                (CanChannelHandle)Can_GetControllerConfigIdxOfMailbox(htrh)
#define Can_GetMailboxActiveSendObject(htrh)          Can_GetActiveSendObjectOfMailbox(htrh)
#define Can_GetMailboxActiveSendData(htrh)            Can_GetActiveSendDataOfMailbox(htrh)
#define Can_GetMailboxMemSecObjIndex(htrh)            Can_GetMemorySectionsIndexOfMailbox(htrh)
#define Can_IsMailboxIndivPolling(htrh)               Can_IsIsIndivPollingOfMailbox(htrh)
#define Can_GetMailboxTxHwFifo(htrh)                  Can_GetTxHwFifoOfMailbox(htrh)

/* MemorySectionInfo */
#define Can_GetMemSecAddress(memSec)                  Can_GetMemoryStartAddressOfMemorySectionInfo(memSec)
#define Can_GetMemSecStartIndex(memSec)               Can_GetMemorySectionStartOfMemorySectionInfo(memSec)

/* MemorySectionObjects */
#define Can_GetMemSecObjHwHandle(memSecObj)           Can_GetHwHandleOfMemorySectionObjects(memSecObj)
#define Can_GetMemSecObjMailboxElement(memSecObj)     Can_GetMailboxElementOfMemorySectionObjects(memSecObj)
#define Can_GetMemSecObjMailboxHandle(memSecObj)      Can_GetMailboxHandleOfMemorySectionObjects(memSecObj)
#define Can_IsMemSecObjIndivPolling(memSecObj)        Can_IsIsIndivPollingOfMemorySectionObjects(memSecObj)

/* VAR */
#define Can_GetLastInitObject(Index)                   Can_GetLastInitObjectOfControllerData(Index)
#define Can_SetLastInitObject(Index, Value)            Can_SetLastInitObjectOfControllerData(Index, Value)
#define Can_GetCanInterruptOldStatus(Index)            Can_GetCanInterruptOldStatusOfControllerData(Index)
#define Can_SetCanInterruptOldStatus(Index, Value)     Can_SetCanInterruptOldStatusOfControllerData(Index, Value)
#define Can_GetCanInterruptCounter(Index)              Can_GetCanInterruptCounterOfControllerData(Index)
#define Can_SetCanInterruptCounter(Index, Value)       Can_SetCanInterruptCounterOfControllerData(Index, Value)
#define Can_IsIsWakeup(Index)                          Can_IsIsWakeupOfControllerData(Index)
#define Can_SetIsWakeup(Index, Value)                  Can_SetIsWakeupOfControllerData(Index, Value)
#define Can_IsIsBusOff(Index)                          Can_IsIsBusOffOfControllerData(Index)
#define Can_SetIsBusOff(Index, Value)                  Can_SetIsBusOffOfControllerData(Index, Value)
#define Can_GetBusOffCounter(Index)                    Can_GetBusOffCounterOfControllerData(Index)
#define Can_SetBusOffCounter(Index, Value)             Can_SetBusOffCounterOfControllerData(Index, Value)
#define Can_DecBusOffCounter(Index)                    Can_DecBusOffCounterOfControllerData(Index)
#define Can_GetModeTransitionRequest(Index)            Can_GetModeTransitionRequestOfControllerData(Index)
#define Can_SetModeTransitionRequest(Index, Value)     Can_SetModeTransitionRequestOfControllerData(Index, Value)
#define Can_GetBusOffTransitionRequest(Index)          Can_GetBusOffTransitionRequestOfControllerData(Index)
#define Can_SetBusOffTransitionRequest(Index, Value)   Can_SetBusOffTransitionRequestOfControllerData(Index, Value)
#define Can_GetRamCheckTransitionRequest(Index)        Can_GetRamCheckTransitionRequestOfControllerData(Index)
#define Can_SetRamCheckTransitionRequest(Index, Value) Can_SetRamCheckTransitionRequestOfControllerData(Index, Value)
/* controller states */
#define Can_GetLogStatus(Index)                        Can_GetLogStatusOfControllerData(Index)
#define Can_SetLogStatus(Index, Value)                 Can_SetLogStatusOfControllerData(Index, Value)
#define Can_GetCanLoopTimeout(ch, Index)               (Can_GetLoopTimeoutOfControllerData(ch))[(Index)]
#define Can_GetMirrorModeState(Index)                  Can_GetMirrorModeStateOfControllerData(Index)
#define Can_SetMirrorModeState(Index, Value)           Can_SetMirrorModeStateOfControllerData(Index, Value)
#define Can_GetSilentModeState(Index)                  Can_GetSilentModeStateOfControllerData(Index)
#define Can_SetSilentModeState(Index, Value)           Can_SetSilentModeStateOfControllerData(Index, Value)
/* ActiveSend */
#define Can_GetActiveSendPdu(Index)                    Can_GetPduOfActiveSendObject(Index)
#define Can_SetActiveSendPdu(Index, Value)             Can_SetPduOfActiveSendObject(Index, Value)
#define Can_GetActiveSendState(Index)                  Can_GetStateOfActiveSendObject(Index)
#define Can_SetActiveSendState(Index, Value)           Can_SetStateOfActiveSendObject(Index, Value)
#define Can_GetActiveSendPduInfo(Index)                Can_GetPduInfoOfActiveSendObject(Index)
#define Can_GetActiveSendId(Index)                     (Can_GetPduInfoOfActiveSendObject(Index)).id
#define Can_SetActiveSendId(Index, Value)              (Can_GetPduInfoOfActiveSendObject(Index)).id = (Value)
#define Can_GetActiveSendLength(Index)                 (Can_GetPduInfoOfActiveSendObject(Index)).length
#define Can_SetActiveSendLength(Index, Value)          (Can_GetPduInfoOfActiveSendObject(Index)).length = (Value)
#define Can_GetActiveSendSdu(Index)                    (Can_GetPduInfoOfActiveSendObject(Index)).sdu
#define Can_SetActiveSendSdu(Index, Value)             (Can_GetPduInfoOfActiveSendObject(Index)).sdu = (Value)
#define Can_GetActiveSendSwPduHandle(Index)            (Can_GetPduInfoOfActiveSendObject(Index)).swPduHandle
#define Can_SetActiveSendSwPduHandle(Index, Value)     (Can_GetPduInfoOfActiveSendObject(Index)).swPduHandle = (Value)
/* Use already ComStackLib name #define Can_GetActiveSendData(Index)                   Can_GetActiveSendData(Index) */
/* TxHwFifo */
#define Can_GetTxHwFifoWriteIndex(fifo)                Can_GetWriteIndexOfTxHwFifo(fifo)
#define Can_SetTxHwFifoWriteIndex(fifo, Value)         Can_SetWriteIndexOfTxHwFifo(fifo, Value)
#define Can_IncTxHwFifoWriteIndex(fifo)                Can_IncWriteIndexOfTxHwFifo(fifo)
#define Can_GetTxHwFifoReadIndex(fifo)                 Can_GetReadIndexOfTxHwFifo(fifo)
#define Can_SetTxHwFifoReadIndex(fifo, Value)          Can_SetReadIndexOfTxHwFifo(fifo, Value)
#define Can_IncTxHwFifoReadIndex(fifo)                 Can_IncReadIndexOfTxHwFifo(fifo)
#define Can_GetTxHwFifoFillCount(fifo)                 Can_GetFillCountOfTxHwFifo(fifo)
#define Can_SetTxHwFifoFillCount(fifo, Value)          Can_SetFillCountOfTxHwFifo(fifo, Value)
#define Can_IncTxHwFifoFillCount(fifo)                 Can_IncFillCountOfTxHwFifo(fifo)
#define Can_DecTxHwFifoFillCount(fifo)                 Can_DecFillCountOfTxHwFifo(fifo)

# define Can_GetRxTmpBuf(logCh)                        Can_GetRxTmpBufOfControllerData(logCh)
# define Can_GetRxFcCount(logCh)                       (vuint8) Can_GetRxFullHandleMax(logCh)
# if defined(C_ENABLE_TX_HW_FIFO)
#  define Can_IsTxFifo(htrh)                           (Can_GetMailboxType(htrh) == CAN_TX_BASICCAN_FIFO_TYPE_MAILBOXTYPEOFMAILBOX)
#  define Can_GetTxHwToMbHandle(logCh, Index)          Can_GetMemSecObjMailboxHandle(Can_GetMemSecStartIndex((logCh) << 1) + (Index))
#  define Can_GetTxFifoHwToMbHandle(logCh, Index)      Can_GetMemSecObjMailboxHandle(Can_GetMemSecStartIndex(((logCh) << 1) + 1u) + (Index))
# else
#  define Can_GetTxHwToMbHandle(logCh, Index)          Can_GetMemSecObjMailboxHandle(Can_GetMemSecStartIndex(logCh) + (Index))
# endif

/***************************************************************************/
/* Default switches                                                        */
/* Automatic define settings, depending on user configuration in can_cfg.h */
/***************************************************************************/
# define C_HL_ENABLE_OVERRUN_IN_STATUS

# define C_HL_DISABLE_HW_RANGES_FILTER

# define C_HL_ENABLE_IDTYPE_IN_ID

/* Specify the ID tables which contain the ID type */
# define C_LL_RX_IDTYPE_TABLE      CanRxId0
# define C_LL_TX_IDTYPE_TABLE      CanTxId0

# define C_HL_DISABLE_DUMMY_FCT_CALL

# define C_HL_DISABLE_TX_MSG_DESTROYED

# define C_HL_DISABLE_CANCEL_IN_HW_TASK

# define C_HL_DISABLE_HW_EXIT_TRANSMIT

# define C_HL_DISABLE_ADJUST_RXHANDLE

# define C_HL_DISABLE_REJECT_UNWANTED_IDTYPE

# define C_HL_DISABLE_REJECT_REMOTE_FRAME

# define C_HL_DISABLE_REJECT_REMOTE_FRAME_FULLCAN

# define C_HL_ENABLE_REJECT_ILLEGAL_DLC

# define C_HL_DISABLE_COPROCESSOR_SUPPORT

# define C_HL_DISABLE_AVOID_REENTRANT_APPLCANCANCELNOTIFICATION

# define C_ENABLE_TX_ACTUAL_MACROS

# define CAN_HL_HW_LAYOUT_TXBASIC_FIRST

# if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
#  define C_ENABLE_RSCAN_FD_LAYOUT
# else
#  if defined(C_ENABLE_CAN_FD_USED)
#   define C_ENABLE_RSCAN_FD_LAYOUT
#  endif
# endif

/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/
# define CAN_CAST_ADDR(val)                      (val)

# if defined(C_ENABLE_SINGLE_PHYS_CHANNEL_OPTIMIZATION)
#  define C_SINGLE_PHYS_CHANNEL
#  define mCanLogToPhys(ch)                      kCanLogToPhys
#   define mCanIntcChTxAdr(ch)                   kCanIntcChTxBaseAdr
#   define mCanIntcChErrorAdr(ch)                kCanIntcChErrorBaseAdr
#   define mCanIntcChWakeupAdr(ch)               kCanIntcChWakeupBaseAdr
# else
#  define C_MULTIPLE_PHYS_CHANNEL
#  define mCanLogToPhys(ch)                      Can_GetLogToPhys(ch)
#  define mCanIntcChTxAdr(ch)                    Can_GetIntcChTxBaseAdrOfIntcAddresses(ch)
#  define mCanIntcChErrorAdr(ch)                 Can_GetIntcChErrorBaseAdrOfIntcAddresses(ch)
#  define mCanIntcChWakeupAdr(ch)                Can_GetIntcChWakeupBaseAdrOfIntcAddresses(ch)
# endif

# define kCanNumberOfUsedCanRxIdTables           1u
# define kCanNumberOfUsedCanTxIdTables           1u

/* macros to set DLC and ID in RX-,TX-structures */
# define MK_RX_RANGE_MASK_IDSTD0(id)             (MK_STDID0(id))
# define MK_RX_RANGE_CODE_IDSTD0(id)             (MK_STDID0(id))
# define MK_RX_RANGE_MASK_IDEXT0(id)             (MK_EXTID0(id) & ~kCanIdTypeExt)
# define MK_RX_RANGE_CODE_IDEXT0(id)             (MK_EXTID0(id))

/* converts an ID to register format */
# define MK_STDID0(id)                           ((id) & kCanStdIdMask)
# define MK_EXTID0(id)                           (((id) & kCanExtIdMask) | kCanIdTypeExt)

/* converts a DLC to register format */
# define MK_TX_DLC(dlc)                          ((tCanDlc)((dlc) & kCanDlcLogMask))
# define MK_TX_DLC_EXT(dlc)                      ((tCanDlc)((dlc) & kCanDlcLogMask))

/* extracts a DLC from register format to logical format */
# define XT_TX_DLC(dlc_raw)                      ((vuint8)(dlc_raw))

/* converts a DLC to the corresponding register value */
# define CanActualDLCToReg(dlc)                  ((kCanRegSize) (((kCanRegSize) (dlc)) << 28))

/* converts a register value to the corresponding DLC */
# define CanRegToActualDLC(reg)                  ((vuint8) ((reg) >> 28))

# define CanRxActualIdRaw0(rxStruct)             ((tCanRxId0)  ((rxStruct)->pChipMsgObj->Id))
/* macros for CAN message access within ApplCanMsgReceived() or PreCopy() function */
# if defined(C_ENABLE_EXTENDED_ID)
#  define CanRxActualIdExtHi(rxStruct)           ((vuint8)   ((((rxStruct)->pChipMsgObj->Id) >> 24) & 0x1Fu))               /* return code has to be vuint8     */
#  define CanRxActualIdExtMidHi(rxStruct)        ((vuint8)    (((rxStruct)->pChipMsgObj->Id) >> 16))                        /* return code has to be vuint8     */
#  define CanRxActualIdExtMidLo(rxStruct)        ((vuint8)    (((rxStruct)->pChipMsgObj->Id) >> 8 ))                        /* return code has to be vuint8     */
#  define CanRxActualIdExtLo(rxStruct)           ((vuint8)     ((rxStruct)->pChipMsgObj->Id))                               /* return code has to be vuint8     */
# endif
# define CanRxActualIdType(rxStruct)             ((tCanIdType)(((rxStruct)->pChipMsgObj->Id) & kCanIdTypeExt))              /* return code has to be tCanIdType */
# define CanRxActualExtId(rxStruct)              ((vuint32)   (((rxStruct)->pChipMsgObj->Id) & kCanExtIdMask))              /* return code has to be vuint32    */
# define CanRxActualStdId(rxStruct)              ((vuint16)   (((rxStruct)->pChipMsgObj->Id) & kCanStdIdMask))              /* return code has to be vuint16    */
# define CanRxActualData(rxStruct, i)            ((vuint8)     ((rxStruct)->pChipData[i]))                                  /* return code has to be vuint8     */
# define CanRxActualDLC(rxStruct)                CAN_DLC2LEN(CanRegToActualDLC((rxStruct)->pChipMsgObj->Dlc))               /* return code has to be vuint8     */
# if defined(C_ENABLE_CAN_FD_USED)
#  define CanRxActualFdType(rxStruct)            ((tCanFdType)(((rxStruct)->pChipMsgObj->Fd) & kCanFdTypeFd))
# endif

/* macros for CAN message access within GenericConfirmation() function */
# define CanTxActualIdType(txConfStruct)         CanRxActualIdType(txConfStruct)
# define CanTxActualExtId(txConfStruct)          CanRxActualExtId(txConfStruct)
# define CanTxActualStdId(txConfStruct)          CanRxActualStdId(txConfStruct)
# define CanTxActualData(txConfStruct, i)        CanRxActualData((txConfStruct), (i))
# define CanTxActualDLC(txConfStruct)            CanRxActualDLC(txConfStruct)
# if defined(C_ENABLE_CAN_FD_USED)
#  define CanTxActualFdType(txConfStruct)        CanRxActualFdType(txConfStruct)
# endif

# if defined(C_MULTIPLE_RECEIVE_CHANNEL)
#  define CanRxActualErrorCounter(ch)            ((vuint8) ((Can->ChCtrl[mCanLogToPhys(ch)].SR & kCanRecMask) >> 16))
#  define CanTxActualErrorCounter(ch)            ((vuint8) ((Can->ChCtrl[mCanLogToPhys(ch)].SR & kCanTecMask) >> 24))
# else
#  define CanRxActualErrorCounter()              ((vuint8) ((Can->ChCtrl[mCanLogToPhys(0)].SR & kCanRecMask) >> 16))
#  define CanTxActualErrorCounter()              ((vuint8) ((Can->ChCtrl[mCanLogToPhys(0)].SR & kCanTecMask) >> 24))
# endif

/* macros for CAN message access within PreTransmit() function */
# if defined( C_ENABLE_CAN_FD_USED )
#  define CanTxWriteActId(txStruct, id)          { ((txStruct).pChipMsgObj->Id) = MK_STDID0(id); ((txStruct).pChipMsgObj->Fd) = kCanFdTypeClassic | kCanFdBrsTypeFalse; }
#  if defined(C_ENABLE_EXTENDED_ID)
#   define CanTxWriteActExtId(txStruct, id)      { ((txStruct).pChipMsgObj->Id) = MK_EXTID0(id); ((txStruct).pChipMsgObj->Fd) = kCanFdTypeClassic | kCanFdBrsTypeFalse; }
#  endif
#   define CanTxWriteActFdId(txStruct, id)       { ((txStruct).pChipMsgObj->Id) = MK_STDID0(id); ((txStruct).pChipMsgObj->Fd) = kCanFdTypeFd | kCanFdBrsTypeTrue; }
#   if defined(C_ENABLE_EXTENDED_ID)
#    define CanTxWriteActFdExtId(txStruct, id)   { ((txStruct).pChipMsgObj->Id) = MK_EXTID0(id); ((txStruct).pChipMsgObj->Fd) = kCanFdTypeFd | kCanFdBrsTypeTrue; }
#   endif
# else
#  define CanTxWriteActId(txStruct, id)          { ((txStruct).pChipMsgObj->Id) = MK_STDID0(id); }
#  if defined(C_ENABLE_EXTENDED_ID)
#   define CanTxWriteActExtId(txStruct, id)      { ((txStruct).pChipMsgObj->Id) = MK_EXTID0(id); }
#  endif
# endif
# define CanTxWriteActDLC(txStruct, len)         { ((txStruct).pChipMsgObj->Dlc) = CanActualDLCToReg(CAN_LEN2DLC(len)); }


#define CAN_HL_MIN(x, y) (((x)>(y)) ? (y) : (x)) /* COV_CAN_GENDATA_FAILURE */
#define CAN_HL_MAX(x, y) (((x)<(y)) ? (y) : (x)) /* COV_CAN_GENDATA_FAILURE */

/***************************************************************************************************/
/* Macros for dummy statements */
#if !defined(CAN_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
#  define CAN_DUMMY_STATEMENT(x) (x) = (x) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# else
#  define CAN_DUMMY_STATEMENT(x)
# endif
#endif
#if !defined(CAN_DUMMY_STATEMENT_CONST) /* COV_CAN_COMPATIBILITY */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
#  define CAN_DUMMY_STATEMENT_CONST(x) (void)(x)
# else
#  define CAN_DUMMY_STATEMENT_CONST(x)
# endif
#endif

/***************************************************************************************************/
/* Macros for DET and assertions */
#if (CAN_DEV_ERROR_REPORT == STD_ON) /* \trace SPEC-1404, SPEC-1696 */
/* \trace SPEC-1725, SPEC-1403, SPEC-1568 */
# define Can_CallDetReportError(api, err) ((void) Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, (api), (err)))
# define assertHardware(a, b, c)  if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertInternal(a, b, c)  if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertUser(a, b, c)      if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define assertGen(a, b, c)       if (!(a)) {Can_CallDetReportError(CAN_HW_ACCESS_ID, (c));}
# define C_ENABLE_HARDWARE_CHECK
# define C_ENABLE_INTERNAL_CHECK
# define C_ENABLE_USER_CHECK
# define C_ENABLE_GEN_CHECK
#else
# define Can_CallDetReportError(api, err)
# define assertHardware(a, b, c)
# define assertInternal(a, b, c)
# define assertUser(a, b, c)
# define assertGen(a, b, c)
#endif

/***************************************************************************************************/
/* Macros for Critical Area 0 abstraction */

#define CanDeclareGlobalInterruptOldStatus
/* CAN_EXCLUSIVE_AREA_0 called only by LL code */
#define CanSingleGlobalInterruptDisable()     SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0()
#define CanSingleGlobalInterruptRestore()     SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0()
#define CanGlobalInterruptDisable()           SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0()
#define CanGlobalInterruptRestore()           SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0()
#define CanNestedGlobalInterruptDisable()     SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0()
#define CanNestedGlobalInterruptRestore()     SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0()

/***************************************************************************************************/
/* Macros for LL-HLL compatibility */
#if defined(C_ENABLE_SLEEP_WAKEUP)
# define APPL_CAN_WAKEUP(ch)   (CanHL_WakeUpHandling( CAN_CHANNEL_CANPARA_ONLY ))
# define CAN_WAKEUP(ch)              ((void) Can_SetControllerMode((uint8)(ch), CAN_T_WAKEUP))
#endif


/***************************************************************************/
/* error codes                                                             */
/***************************************************************************/





/***************************************************************************/
/* CAN-Hardware Data Definitions                                           */
/***************************************************************************/
# define kCanMaxPhysChannelsCell         8u
# define kCanMaxRxFifosCell              8u
# define kCanMaxTxFifosCell              3u /* per channel */
# define kCanMaxRxBufCell                128u
# define kCanNumberOfSharedReg8Cell      2u
# define kCanNumberOfSharedReg16Cell     4u
# if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
#  define kCanMaxTxBufCell               32u /* per channel */
#  define kCanNumberOfSharedRegTxCell    8u
#  define kCanTxSize                     vuint32
# else
#  define kCanMaxTxBufCell               16u /* per channel */
#  define kCanNumberOfSharedRegTxCell    4u
#  define kCanTxSize                     vuint16
# endif
# define kCanMaxRuleAccessCell           16u
# define kCanMaxRamTestAccessCell        64u
# define kCanRegSize                     vuint32
# define kCanRegSizeCast                 kCanRegSize

# define pBufRm(idx)                     (tCanBufPtr)&(Can->BufRm[idx]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define pBufRf(idx)                     (tCanBufPtr)&(Can->BufRf[idx]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define pBufCf(pch, idx)                (tCanBufPtr)&(Can->BufCfCh[pch].BufCf[idx]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define pBufTm(pch, idx)                (tCanBufPtr)&(Can->BufTmCh[pch].BufTm[idx]) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define mTHAR0(idx)                     Can->THA[idx].THAR0 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define mTHAR1(idx)                     Can->THA[idx].THAR1 /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define mRuleCode(idx)                  Can->Rule[idx].Code /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define mRuleMask(idx)                  Can->Rule[idx].Mask /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define mRuleBuf(idx)                   Can->Rule[idx].Buf /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define mRuleFifo(idx)                  Can->Rule[idx].Fifo /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# define mCRAMTR(idx)                    Can->CRAMTR[idx] /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

typedef volatile struct        /* channel control and status */
{
  volatile vuint32      BCFG;                                  /*!< CmCFG/CmNCFG */
  volatile vuint32      CR;                                    /*!< CmCTR */
  volatile vuint32      SR;                                    /*!< CmSTS */
  volatile vuint16      EF;                                    /*!< CmERFLL */
  volatile vuint16      CRC;                                   /*!< CmERFLH */
} tCanChCtrl;

# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
typedef volatile struct        /* channel control and status for CAN-FD */
{
  volatile vuint32      BCFG;                                  /*!< CmDCFG */
  volatile vuint32      FDCFG;                                 /*!< CmFDCFG */
  volatile vuint32      CR;                                    /*!< CmFDCTR */
  volatile vuint32      SR;                                    /*!< CmFDSTS */
  volatile vuint32      CRC;                                   /*!< CmFDCRC */
  volatile vuint32      Unused04[3];
} tCanChCtrlFd;
# endif

typedef volatile struct        /* fifo control */
{
  volatile vuint32      TRFCR[kCanMaxTxFifosCell];             /*!< CFCCk */
} tCanChFC;

typedef volatile struct        /* fifo status */
{
  volatile kCanRegSize  TRFSR[kCanMaxTxFifosCell];             /*!< CFSTSk */
} tCanChFS;

typedef volatile struct        /* fifo pointer control */
{
  volatile kCanRegSize  TRFPCR[kCanMaxTxFifosCell];            /*!< CFPCTRk */
} tCanChFPC;

typedef volatile struct        /* buffer control */
{
  volatile vuint8       TBCR[kCanMaxTxBufCell];                /*!< TMCp */
} tCanChBC;

typedef volatile struct        /* buffer status */
{
  volatile vuint8       TBSR[kCanMaxTxBufCell];                /*!< TMSTSp */
} tCanChBS;

typedef volatile struct        /* receive rule */
{
  volatile vuint32      Code;      /* A - ID code           */ /*!< GAFLIDj */
  volatile vuint32      Mask;      /* B - ID mask           */ /*!< GAFLMj  */
  volatile vuint32      Buf;       /* C - DLC, label, buf   */ /*!< GAFLP0j */
  volatile vuint32      Fifo;      /* D - fifo              */ /*!< GAFLP1j */
} tCanRule;

typedef volatile struct        /* transmit history access */
{
# if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
  volatile kCanRegSize  THAR0;                                 /*!< THLACC0m */
  volatile kCanRegSize  THAR1;                                 /*!< THLACC1m */
# else
  volatile kCanRegSize  THAR0;                                 /*!< THLACCm */
# endif
} tCanTHA;

# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
typedef volatile struct        /* mailbox with max PLS of 64 */
{
  volatile vuint32      Id;        /* ID                    */ /*!< RFIDx / CFIDk / TMIDp  */
  volatile vuint32      Dlc;       /* DLC, label, TS        */ /*!< RFPTRx / CFPTRk / TMPTRp */
  volatile vuint32      Fd;        /* FDF, BRS, ESI         */ /*!< RFFDSTSx / CFFDCSTSk / TMFDCTRp */
  union                                                        /*!< RFDFdx / CFDFdk / TMDFbp */
  { /* PRQA S 0750 */ /* MD_Can_Union */
    volatile vuint8     bData[64]; /* data                  */
    volatile vuint16    wData[32]; /* data                  */
    volatile vuint32    iData[16]; /* data                  */
  } u;
  volatile vuint32      Unused07[13];
} tCanMsgObj64;

#  if defined(C_ENABLE_IF_RSCAN_FD) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_EMBEDDED */
typedef volatile struct        /* mailbox with max PLS of 20 */
{
  volatile vuint32      Id;        /* ID                    */ /*!< RMIDq / TMIDp */
  volatile vuint32      Dlc;       /* DLC, label, TS        */ /*!< RMPTRq / TMPTRp */
  volatile vuint32      Fd;        /* FDF, BRS, ESI         */ /*!< RMFDSTSq / TMFDCTRp */
  union                                                        /*!< RMDFbq / TMDFbp */
  { /* PRQA S 0750 */ /* MD_Can_Union */
    volatile vuint8     bData[20]; /* data                  */
    volatile vuint16    wData[10]; /* data                  */
    volatile vuint32    iData[5];  /* data                  */
  } u;
} tCanMsgObj20;

typedef volatile struct        /* transmit buffer */
{
  tCanMsgObj20          BufTm[kCanMaxTxBufCell];               /*!< TMID, TMPTR, TMDF[] */
} tCanBufTm;
#  else
typedef volatile struct        /* transmit buffer */
{
  tCanMsgObj64          BufTm[kCanMaxTxBufCell];               /*!< TMID, TMPTR, TMDF[] */
} tCanBufTm;
#  endif

typedef volatile struct        /* transmit / receive FIFOs */
{
  tCanMsgObj64          BufCf[kCanMaxTxFifosCell];             /*!< CFID, CFPTR, CFDF[] */
} tCanBufCf;
# else
typedef volatile struct        /* mailbox with max PLS of 8 */
{
  volatile vuint32      Id;        /* A - ID                */ /*!< RMIDq / RFIDx / CFIDk / TMIDp */
  volatile kCanRegSize  Dlc;       /* B - DLC, label, TS    */ /*!< RMPTRq / RFPTRx / CFPTRk / TMPTRp */
  union                                                        /*!< RMDF[0/1]q / RFDF[0/1]x / CFDF[0/1]k / TMDF[0/1]p */
  { /* PRQA S 0750 */ /* MD_Can_Union */
    volatile vuint8     bData[8];  /* C,D - data            */
    volatile vuint16    wData[4];  /* C,D - data            */
    volatile vuint32    iData[2];  /* C,D - data            */
  } u;
} tCanMsgObj8;

typedef volatile struct        /* transmit / receive FIFOs */
{
  tCanMsgObj8           BufCf[kCanMaxTxFifosCell];             /* CFID, CFPTR, CFDF[0/1] */
} tCanBufCf;

typedef volatile struct        /* transmit buffer */
{
  tCanMsgObj8           BufTm[kCanMaxTxBufCell];               /* TMID, TMPTR, TMDF[0/1] */
} tCanBufTm;
# endif


typedef volatile struct
{
  /* control and status */
  tCanChCtrl            ChCtrl[kCanMaxPhysChannelsCell];       /*!< CmCFG/CmNCFG, CmCTR, CmSTS, CmERFL */
  volatile kCanRegSize  Unused01[1];
  volatile vuint32      CGCFG;                                 /*!< GCFG */
  volatile vuint32      CGCR;                                  /*!< GCTR */
  volatile kCanRegSize  CGSR;                                  /*!< GSTS */
  volatile kCanRegSize  CGEF;                                  /*!< GERFL */
  volatile kCanRegSize  CTS;                                   /*!< GTSC */
  /* receive rules */
  volatile kCanRegSize  CRECR;                                 /*!< GAFLECTR */
  volatile kCanRegSize  CRNCFG[kCanNumberOfSharedReg8Cell];    /*!< GAFLCFG[0/1] */
  /* rx buffers */
  volatile kCanRegSize  CRBNUM;                                /*!< RMNB */
  volatile kCanRegSize  CRBRCF[kCanNumberOfSharedReg16Cell];   /*!< RMND[0/1/2/3] */
  /* fifos */
  volatile kCanRegSize  CRFCR[kCanMaxRxFifosCell];             /*!< RFCCx */
  volatile kCanRegSize  CRFSR[kCanMaxRxFifosCell];             /*!< RFSTSx */
  volatile kCanRegSize  CRFPCR[kCanMaxRxFifosCell];            /*!< RFPCTRx */
  tCanChFC              ChFC[kCanMaxPhysChannelsCell];         /*!< CFCCk */
  tCanChFS              ChFS[kCanMaxPhysChannelsCell];         /*!< CFSTSk */
  tCanChFPC             ChFPC[kCanMaxPhysChannelsCell];        /*!< CFPCTRk */
  volatile kCanRegSize  CFESR;                                 /*!< FESTS */
  volatile kCanRegSize  CFFSR;                                 /*!< FFSTS */
  volatile kCanRegSize  CFMLSR;                                /*!< FMSTS */
  volatile kCanRegSize  CRFISR;                                /*!< RFISTS */
  volatile kCanRegSize  CTRFRISR;                              /*!< CFRISTS */
  volatile kCanRegSize  CTRFTISR;                              /*!< CFTISTS */
  /* tx buffers */
  tCanChBC              ChBC[kCanMaxPhysChannelsCell];         /*!< TMCp */
  tCanChBS              ChBS[kCanMaxPhysChannelsCell];         /*!< TMSTSp */
  volatile kCanRegSize  CTBTRSR[kCanNumberOfSharedRegTxCell];  /*!< TMTRSTSy */
  volatile kCanRegSize  CTBARSR[kCanNumberOfSharedRegTxCell];  /*!< TMTARSTSy */
  volatile kCanRegSize  CTBTCSR[kCanNumberOfSharedRegTxCell];  /*!< TMTCSTSy */
  volatile kCanRegSize  CTBASR[kCanNumberOfSharedRegTxCell];   /*!< TMTASTSy */
  volatile kCanRegSize  CTBIER[kCanNumberOfSharedRegTxCell];   /*!< TMIECy */
# if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
  volatile vuint32      Unused0x[24];
# endif
  /* tx queue */
  volatile kCanRegSize  TQCR[kCanMaxPhysChannelsCell];         /*!< TXQCCm */
  volatile kCanRegSize  TQSR[kCanMaxPhysChannelsCell];         /*!< TXQSTSm */
  volatile kCanRegSize  TQPCR[kCanMaxPhysChannelsCell];        /*!< TXQPCTRm */
  /* tx history */
  volatile kCanRegSize  THCR[kCanMaxPhysChannelsCell];         /*!< THLCCm */
  volatile kCanRegSize  THSR[kCanMaxPhysChannelsCell];         /*!< THLSTSm */
  volatile kCanRegSize  THPCR[kCanMaxPhysChannelsCell];        /*!< THLPCTRm */
  /* tx interrupt status, global test */
  volatile kCanRegSize  CGTINTSTS[kCanNumberOfSharedReg8Cell]; /*!< GTINTSTS[0/1] */
  volatile kCanRegSize  CGTCFG;                                /*!< GTSTCFG */
  volatile kCanRegSize  CGTCR;                                 /*!< GTSTCTR */
# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
  volatile kCanRegSize  Unused02;
  /* global CAN-FD config */
  volatile kCanRegSize  CGFDCFG;                               /*!< GFDCFG */
  volatile kCanRegSize  CGCRCCFG;                              /*!< GCRCCFG */
# else
  volatile kCanRegSize  Unused02[3];
# endif
  volatile kCanRegSize  CGTPUR;                                /*!< GLOCKK */
# if defined(C_ENABLE_IF_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN */
  volatile kCanRegSize  Unused03[32];
# endif
# if defined(C_ENABLE_IF_RSCAN_FD) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD */
  volatile kCanRegSize  Unused03[31];
  volatile kCanRegSize  CGRMCFG;                               /*!< CFDGRMCFG */
# endif
# if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
  volatile kCanRegSize  Unused03[52];
# endif
# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
  /* channel control and status for CAN-FD */
  tCanChCtrlFd          ChCtrlFd[kCanMaxPhysChannelsCell];     /*!< CmDCFG, CmFDCFG, CmFDCTR, CmFDSTS, CmFDCRC */
#  if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
  volatile vuint32      Unused05[512];
  /* receive rules */
  tCanRule              Rule[kCanMaxRuleAccessCell];           /*!< GAFLIDj, GAFLMj, GAFLP0j, GAFLP1j */
  volatile vuint32      Unused06[960];
  /* mailbox access */
  tCanMsgObj64          BufRm[kCanMaxRxBufCell];               /*!< RMID, RMPTR, RMFDSTS, RMDF[] */
  tCanMsgObj64          BufRf[kCanMaxRxFifosCell];             /*!< RFID, RFPTR, RFFDSTS, RFDF[] */
  tCanBufCf             BufCfCh[kCanMaxPhysChannelsCell];      /*!< CFID, CFPTR, CFFDCSTS, CFDF[] */
  volatile vuint32      Unused08[1024];
  tCanBufTm             BufTmCh[kCanMaxPhysChannelsCell];      /*!< TMID, TMPTR, TMFDCTR, TMDF[] */
  tCanTHA               THA[kCanMaxPhysChannelsCell];          /*!< THLACC0m, THLACC1m */
  volatile vuint32      Unused09[240];
#  else
  volatile vuint32      Unused05[640];
  /* receive rules */
  tCanRule              Rule[kCanMaxRuleAccessCell];           /*!< GAFLIDj, GAFLMj, GAFLP0j, GAFLP1j */
  volatile vuint32      Unused06[960];
  /* mailbox access */
  tCanMsgObj20          BufRm[kCanMaxRxBufCell];               /*!< RMID, RMPTR, RMFDSTS, RMDF[] */
  tCanMsgObj64          BufRf[kCanMaxRxFifosCell];             /*!< RFID, RFPTR, RFFDSTS, RFDF[] */
  tCanBufCf             BufCfCh[kCanMaxPhysChannelsCell];      /*!< CFID, CFPTR, CFFDCSTS, CFDF[] */
  tCanBufTm             BufTmCh[kCanMaxPhysChannelsCell];      /*!< TMID, TMPTR, TMFDCTR, TMDF[] */
  volatile vuint32      Unused08[1024];
  tCanTHA               THA[kCanMaxPhysChannelsCell];          /*!< THLACCm */
  volatile vuint32      Unused09[248];
#  endif
# else
  /* receive rules */
  tCanRule              Rule[kCanMaxRuleAccessCell];           /*!< GAFLIDj, GAFLMj, GAFLP0j, GAFLP1j */
  /* mailbox access */
  tCanMsgObj8           BufRm[kCanMaxRxBufCell];               /*!< RMID, RMPTR, RMDF[0/1] */
  tCanMsgObj8           BufRf[kCanMaxRxFifosCell];             /*!< RFID, RFPTR, RFDF[0/1] */
  tCanBufCf             BufCfCh[kCanMaxPhysChannelsCell];      /*!< CFID, CFPTR, CFDF[0/1] */
  tCanBufTm             BufTmCh[kCanMaxPhysChannelsCell];      /*!< TMID, TMPTR, TMDF[0/1] */
  tCanTHA               THA[kCanMaxPhysChannelsCell];          /*!< THLACCm */
  volatile kCanRegSize  Unused04[56];
# endif
  /* ram test */
  volatile vuint32      CRAMTR[kCanMaxRamTestAccessCell];      /*!< RPGACCr */
} tCanCell;

V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanCell) tCanCellPtr;
# define Can ((tCanCellPtr) CAN_CAST_ADDR(kCanBaseAdr))

# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanMsgObj64) tCanBufPtr;
#  if (CAN_SAFE_BSW == STD_ON)
V_DEF_VAR_TYPE(V_NONE, tCanMsgObj64) tCanDummyBuf;
#  endif
# else
V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanMsgObj8) tCanBufPtr;
#  if (CAN_SAFE_BSW == STD_ON)
V_DEF_VAR_TYPE(V_NONE, tCanMsgObj8) tCanDummyBuf;
#  endif
# endif

# if defined(C_ENABLE_LL_CAN_INTCTRL)
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_TX_POLLING) 
typedef volatile struct
{
  volatile vuint8       Tx;                      /* lower channel Tx ICR     */
  volatile vuint8       uTx;                     /* upper channel Tx ICR     */
} tCanIntcChTxObj;

V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanIntcChTxObj) tCanIntcChTxPtr;
#  endif

#  if !defined(C_ENABLE_ERROR_POLLING) 
typedef volatile struct
{
  volatile vuint8       Err;                     /* lower channel error ICR  */
  volatile vuint8       uErr;                    /* upper channel error ICR  */
} tCanIntcChErrObj;

V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanIntcChErrObj) tCanIntcChErrPtr;
#  endif

#  if ((defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_RX_BASICCAN_POLLING)) && defined(C_ENABLE_RX_BASICCAN_OBJECTS)) 
typedef volatile struct
{
  volatile vuint8       RF;                      /* lower receive FIFO ICR   */
  volatile vuint8       uRF;                     /* upper receive FIFO ICR   */
} tCanIntcRxFifoObj;

V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanIntcRxFifoObj) tCanIntcRxFifoPtr;
#   define CanIntcRxFifo ((tCanIntcRxFifoPtr) CAN_CAST_ADDR(kCanIntcRxFifoBaseAdr))
#  endif

#  if (!defined(C_ENABLE_ERROR_POLLING) && defined(C_ENABLE_OVERRUN) && defined(C_ENABLE_RX_BASICCAN_OBJECTS)) 
typedef volatile struct
{
  volatile vuint8       GErr;                    /* lower global error ICR   */
  volatile vuint8       uGErr;                   /* upper global error ICR   */
} tCanIntcGErrObj;

V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanIntcGErrObj) tCanIntcGErrPtr;
#   define CanIntcGErr ((tCanIntcGErrPtr) CAN_CAST_ADDR(kCanIntcGErrorBaseAdr))
#  endif
# endif /* C_ENABLE_LL_CAN_INTCTRL */

# if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
#  if (defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL) || (defined(C_ENABLE_WAKEUP_POLLING) && !defined(C_ENABLE_LL_CAN_WAKEUP_INTCB))) 
typedef volatile struct
{
  volatile vuint8       Wup;                     /* lower channel wakeup ICR */
  volatile vuint8       uWup;                    /* upper channel wakeup ICR */
} tCanIntcChWupObj;

V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanIntcChWupObj) tCanIntcChWupPtr;
#  endif
# endif /* C_ENABLE_LL_WAKEUP_SUPPORT */

/***************************************************************************/
/* Special switches need by CAN driver                                     */
/***************************************************************************/

/***************************************************************************/
/* Defines / data types / structures / unions                              */
/***************************************************************************/

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
# if( kCanNumberOfUsedCanRxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id); \
                                   (paraStruct)->idRaw4 = MK_STDID4(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id); \
                                   (paraStruct)->idRaw4 = MK_EXTID4(id)
# elif ( kCanNumberOfUsedCanRxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id)
# elif ( kCanNumberOfUsedCanRxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id)
# elif ( kCanNumberOfUsedCanRxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id)
# else
#  define SET_PARASTRUCT_IDRAW_RX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id)
#  define SET_PARASTRUCT_IDRAW_RX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id)
# endif
#endif

#if( kCanNumberOfUsedCanTxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id); \
                                   (paraStruct)->idRaw4 = MK_STDID4(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id); \
                                   (paraStruct)->idRaw4 = MK_EXTID4(id)
#elif ( kCanNumberOfUsedCanTxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id); \
                                   (paraStruct)->idRaw3 = MK_STDID3(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id); \
                                   (paraStruct)->idRaw3 = MK_EXTID3(id)
#elif ( kCanNumberOfUsedCanTxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id); \
                                   (paraStruct)->idRaw2 = MK_STDID2(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id); \
                                   (paraStruct)->idRaw2 = MK_EXTID2(id)
#elif ( kCanNumberOfUsedCanTxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id); \
                                   (paraStruct)->idRaw1 = MK_STDID1(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id); \
                                   (paraStruct)->idRaw1 = MK_EXTID1(id)
#else
# define SET_PARASTRUCT_IDRAW_TX_STD(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_STDID0(id)
# define SET_PARASTRUCT_IDRAW_TX_EXT(paraStruct, id) \
                                   (paraStruct)->idRaw0 = MK_EXTID0(id)
#endif

/***************************************************************************/
/* Core - LowLevel API                                                     */
/***************************************************************************/
typedef struct sCanRxInfoStruct
{
  CanChipMsgPtr     pChipMsgObj;
  CanChipDataPtr    pChipData;
  CanObjectHandle   localMailboxHandle; 
  Can_IdType               localId; 
  uint8                    localDlc;
  /* LL specific part */
} tCanRxInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxInfoStruct, VAR_NOINIT) CanRxInfoStructPtr;

typedef struct sCanTxConfInfoStruct
{
  CanChipMsgPtr     pChipMsgObj;
  CanChipDataPtr    pChipData;
  /* LL specific part */
} tCanTxConfInfoStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanTxConfInfoStruct, VAR_NOINIT) CanTxConfInfoStructPtr;

typedef struct sCanInitParaStruct
{
  CanInitHandle     initObject;
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   hwObjHandle;
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
  tCanRxId0                idRaw0;
# if( kCanNumberOfUsedCanRxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
  tCanRxId1                idRaw1;
# endif
# if( kCanNumberOfUsedCanRxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
  tCanRxId2                idRaw2;
# endif
# if( kCanNumberOfUsedCanRxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
  tCanRxId3                idRaw3;
# endif
# if( kCanNumberOfUsedCanRxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
  tCanRxId4                idRaw4;
# endif
  tCanIdType               idType;
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK)
  uint8                    doRamCheck;
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  uint8                    isChRamCheckFail;
# endif
#endif
  uint8                    isInitOk;
  /* LL specific part */
} tCanInitParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanInitParaStruct, VAR_NOINIT) CanInitParaStructPtr;

#define TxDataPtr Can_SduPtrType /* CBD compatibility */
typedef struct sCanTxTransmissionParaStruct
{
  /* logical formats */
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   mailboxElement; /* logical index within the mailbox for muxTx or FIFO element */
  CanObjectHandle   hwObjHandle;    /* set to the initial hwHandle by core but has to be modified by LL in case of muxTx or FIFO */
  CanObjectHandle   activeSendObject; /* index of the logical Tx mailbox (Tx * Element) */
  tCanTxId0                idRaw0;
#if( kCanNumberOfUsedCanTxIdTables > 1 ) /* COV_CAN_COMPATIBILITY */
  tCanTxId1                idRaw1;
#endif
#if( kCanNumberOfUsedCanTxIdTables > 2 ) /* COV_CAN_COMPATIBILITY */
  tCanTxId2                idRaw2;
#endif
#if( kCanNumberOfUsedCanTxIdTables > 3 ) /* COV_CAN_COMPATIBILITY */
  tCanTxId3                idRaw3;
#endif
#if( kCanNumberOfUsedCanTxIdTables > 4 ) /* COV_CAN_COMPATIBILITY */
  tCanTxId4                idRaw4;
#endif
  tCanDlc                  dlcRaw;
  TxDataPtr                CanMemCopySrcPtr;
#if defined( C_ENABLE_CAN_FD_USED )
  tCanFdType               fdType;
  tCanFdBrsType            fdBrsType;
  uint8                    messageLen;
  uint8                    frameLen;
  uint8                    paddingVal;
#endif
  Can_PduType              pdu;
  /* LL specific part */
  tCanBufPtr               Buf;
} tCanTxTransmissionParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanTxTransmissionParaStruct, VAR_NOINIT) CanTxTransmissionParaStructPtr;

typedef struct sCanRxBasicParaStruct
{
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   hwObjHandle;
#if !defined( C_HL_ENABLE_OVERRUN_IN_STATUS ) && defined( C_ENABLE_OVERRUN )
#endif
  tCanRxInfoStruct         rxStruct;
  /* LL specific part */
} tCanRxBasicParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxBasicParaStruct, VAR_NOINIT) CanRxBasicParaStructPtr;

typedef struct sCanRxFullParaStruct
{
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   hwObjHandle;
  tCanRxInfoStruct         rxStruct;
  /* LL specific part */
} tCanRxFullParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanRxFullParaStruct, VAR_NOINIT) CanRxFullParaStructPtr;

#if defined( C_ENABLE_CANCEL_IN_HW ) || defined( C_ENABLE_CANCEL_SUPPORT_API )
typedef struct
{
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   mailboxElement; /* logical index within the mailbox for muxTx or FIFO element */
  CanObjectHandle   hwObjHandle;    /* set to the initial hwHandle by core but has to be modified by LL in case of muxTx or FIFO */
  CanObjectHandle   activeSendObject; /* index of the logical mailbox + muxTx or FIFO element 0..n */
  CanTransmitHandle   canHandleCurTxObj;
} tCanTxCancellationParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanTxCancellationParaStruct, VAR_NOINIT) CanTxCancellationParaStructPtr;
#endif

typedef struct
{
  CanObjectHandle   mailboxHandle;
  CanObjectHandle   mailboxElement; /* logical index within the mailbox for muxTx or FIFO element */
  CanObjectHandle   hwObjHandle;    /* set to the initial hwHandle by core but has to be modified by LL in case of muxTx or FIFO */
  CanObjectHandle   activeSendObject; /* index of the logical mailbox + muxTx or FIFO element 0..n */
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
  CanTxConfInfoStructPtr   txStructConf;
#endif
  #if defined( C_ENABLE_CANCEL_IN_HW )
  vuint8                   txBufferStatus;
  #endif
} tCanTxConfirmationParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanTxConfirmationParaStruct, VAR_NOINIT) CanTxConfirmationParaStructPtr;

typedef struct sCanTaskParaStruct
{
  CanObjectHandle mailboxHandle;
  CanObjectHandle hwObjHandle;
  /* LL specific part */
} tCanTaskParaStruct;
V_DEF_P2VAR_TYPE(V_NONE, tCanTaskParaStruct, VAR_NOINIT) CanTaskParaStructPtr;
    
/***************************************************************************/
/* module global variable declaration                                      */
/***************************************************************************/

/***************************************************************************/
/* External Declarations                                                   */
/***************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***************************************************************************/
/* local function prototypes (only internal usage)                         */
/***************************************************************************/
#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  CanLL_InitBegin()
 *********************************************************************************************************************/
/*! \brief         Starts the channel initialization
 *  \details       Called by CanHL_ReInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanHL_ReInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBegin( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
/**********************************************************************************************************************
 *  CanLL_InitBeginIsRegisterCorrupt()
 *********************************************************************************************************************/
/*! \brief         Performs the channel register RAM check
 *  \details       Called by CanHL_ReInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanHL_ReInit()
 *  \return        kCanFalse           No corrupt register RAM found
 *                 kCanTrue            Register RAM is considered corrupt or failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginIsRegisterCorrupt( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
#endif

/**********************************************************************************************************************
 *  CanLL_InitBeginSetRegisters()
 *********************************************************************************************************************/
/*! \brief         Performs the channel register initialization
 *  \details       Called by CanHL_ReInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanHL_ReInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitMailboxTx()
 *********************************************************************************************************************/
/*! \brief         Initializes a transmit mailbox
 *  \details       Called by CanHL_ReInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanHL_ReInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxTx( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

# if (defined( C_ENABLE_CAN_RAM_CHECK ))
/**********************************************************************************************************************
 *  CanLL_InitMailboxTxDeactivate()
 *********************************************************************************************************************/
/*! \brief         Deactivates a transmit mailbox if it is considered corrupt by the RAM check
 *  \details       Called by CanHL_ReInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanHL_ReInit()
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMailboxTxDeactivate( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
# endif


#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxFullCan()
 *********************************************************************************************************************/
/*! \brief         Initializes a receive FullCAN mailbox
 *  \details       Called by CanHL_ReInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanHL_ReInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxRxFullCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */


#endif

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxBasicCan()
 *********************************************************************************************************************/
/*! \brief         Initializes a receive BasicCAN mailbox
 *  \details       Called by CanHL_ReInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanHL_ReInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxRxBasicCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

#endif


/**********************************************************************************************************************
 *  CanLL_InitEndSetRegisters()
 *********************************************************************************************************************/
/*! \brief         Finishes the channel register initialization
 *  \details       Called by CanHL_ReInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanHL_ReInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitEndSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitEnd()
 *********************************************************************************************************************/
/*! \brief         Finishes the channel initialization
 *  \details       Called by CanHL_ReInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanHL_ReInit()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitEnd( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CAN_RAM_CHECK )
/**********************************************************************************************************************
 *  CanLL_InitIsMailboxCorrupt()
 *********************************************************************************************************************/
/*! \brief         Performs the mailbox RAM check
 *  \details       Called by CanHL_ReInit()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] initPara            Pointer to local variables of CanHL_ReInit()
 *  \return        kCanFalse           Mailbox is not corrupt
 *                 kCanTrue            Mailbox is considered corrupt or failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_InitIsMailboxCorrupt( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara );
/* CODE CATEGORY 4 END */
#endif


/**********************************************************************************************************************
 *  CanLL_InitPowerOn()
 *********************************************************************************************************************/
/*! \brief         Performs the hardware specific global module initialization
 *  \details       Called by Can_Init()
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitPowerOn( void );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitPowerOnChannelSpecific()
 *********************************************************************************************************************/
/*! \brief         Performs the channel dependent hardware specific global module initialization
 *  \details       Called by Can_Init()
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitPowerOnChannelSpecific( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitMemoryPowerOn()
 *********************************************************************************************************************/
/*! \brief         Performs the platform specific memory initialization
 *  \details       Called by Can_InitMemory()
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMemoryPowerOn( void );
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CANCEL_IN_HW )
/**********************************************************************************************************************
 *  CanLL_TxCancelInHw()
 *********************************************************************************************************************/
/*! \brief         Performs cancellation of the transmission in hardware
 *  \details       Called by cancellation
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txCancellationPara  Pointer to local variables of cancellation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 3 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxCancellationParaStructPtr txCancellationPara);
/* CODE CATEGORY 3 END */
#endif



/**********************************************************************************************************************
 *  CanLL_TxBegin()
 *********************************************************************************************************************/
/*! \brief         Performs start of the transmission
 *  \details       Called by transmission to prepare the mailbox
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_TxSetMailbox()
 *********************************************************************************************************************/
/*! \brief         Sets mailbox data for transmission
 *  \details       Called by transmission to set the control part of the mailbox (e.g. ID, DLC)
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxSetMailbox(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */


/**********************************************************************************************************************
 *  CanLL_TxCopyToCan()
 *********************************************************************************************************************/
/*! \brief         Sets mailbox data for transmission
 *  \details       Called by transmission to set the data part of the mailbox
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_TxStart()
 *********************************************************************************************************************/
/*! \brief         Triggers the mailbox to start the transmission
 *  \details       Called by transmission to start transmission
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxStart(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_TxEnd()
 *********************************************************************************************************************/
/*! \brief         Performs end handling of the transmission
 *  \details       Called by transmission to finish transmission
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of transmission
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
/* CODE CATEGORY 1 END */

#if defined( C_ENABLE_TX_POLLING )
/**********************************************************************************************************************
 *  CanLL_TxIsGlobalConfPending()
 *********************************************************************************************************************/
/*! \brief         Checks whether any confirmation is pending (messages were sent or canceled in hardware)
 *  \details       Called by task to get the global pending information
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanTrue            Confirmation is pending
 *                 kCanFalse           No pending confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxIsGlobalConfPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_TxProcessPendings()
 *********************************************************************************************************************/
/*! \brief         Confirmation handling for a dedicated transmission mailbox
 *  \details       Called by task to check the pending confirmation of a transmission mailbox and start the handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txPara              Pointer to local variables of confirmation task
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara);
/* CODE CATEGORY 2 END */
#endif

/**********************************************************************************************************************
 *  CanLL_TxConfBegin()
 *********************************************************************************************************************/
/*! \brief         Performs start of confirmation
 *  \details       Called by confirmation
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txConfPara          Pointer to local variables of confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara);
/* CODE CATEGORY 1 END */

#if defined( C_ENABLE_CANCEL_IN_HW )
/**********************************************************************************************************************
 *  CanLL_TxConfIsMsgTransmitted()
 *********************************************************************************************************************/
/*! \brief         Checks if a message is transmitted
 *  \details       Called by confirmation
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txConfPara          Pointer to local variables of confirmation
 *  \return        kCanTrue            Message is transmitted
 *                 kCanFalse           Message is not transmitted
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxConfIsMsgTransmitted(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara);
/* CODE CATEGORY 1 END */
#endif

#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
/**********************************************************************************************************************
 *  CanLL_TxConfSetTxConfStruct()
 *********************************************************************************************************************/
/*! \brief         Sets confirmation struct
 *  \details       Called by confirmation to set confirmation data struct
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txConfPara          Pointer to local variables of confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfSetTxConfStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara);
/* CODE CATEGORY 1 END */
#endif

/**********************************************************************************************************************
 *  CanLL_TxConfEnd()
 *********************************************************************************************************************/
/*! \brief         Performs confirmation end handling
 *  \details       Called by confirmation
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] txConfPara          Pointer to local variables of confirmation
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara);
/* CODE CATEGORY 1 END */


#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_RxBasicMsgReceivedBegin()
 *********************************************************************************************************************/
/*! \brief         Performs BasicCAN receive begin
 *  \details       Called by reception to begin BasicCAN reception handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of BasicCAN reception
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara,Can_PduType pdu);
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicReleaseObj()
 *********************************************************************************************************************/
/*! \brief         Releases a BasicCAN mailbox
 *  \details       Called by reception to release a BasicCAN mailbox
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of BasicCAN reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara);
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicMsgReceivedEnd()
 *********************************************************************************************************************/
/*! \brief         Performs BasicCAN receive end
 *  \details       Called by reception to finish BasicCAN reception handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of BasicCAN reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara);
/* CODE CATEGORY 1 END */

# if defined( C_ENABLE_RX_BASICCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_RxBasicIsGlobalIndPending()
 *********************************************************************************************************************/
/*! \brief         Checks weather any BasicCAN indication is pending (messages were received)
 *  \details       Called by task to get the overall reception state
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanTrue            Indication is pending
 *                 kCanFalse           No indication is pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicProcessPendings()
 *********************************************************************************************************************/
/*! \brief         Reception handling for a dedicated BasicCAN mailbox
 *  \details       Called by task to check the pending indication of a BasicCAN mailbox and start the handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] taskPara            Pointer to local variables of reception task
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara);
/* CODE CATEGORY 2 END */
# endif
#endif

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_RxFullMsgReceivedBegin()
 *********************************************************************************************************************/
/*! \brief         Performs FullCAN receive begin
 *  \details       Called by reception to begin FullCAN reception handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of FullCAN reception
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxFullMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara);
/* CODE CATEGORY 1 END */


/**********************************************************************************************************************
 *  CanLL_RxFullReleaseObj()
 *********************************************************************************************************************/
/*! \brief         Releases a FullCAN mailbox
 *  \details       Called by reception to release a FullCAN mailbox
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of FullCAN reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara);
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxFullMsgReceivedEnd()
 *********************************************************************************************************************/
/*! \brief         Performs FullCAN receive end
 *  \details       Called by reception to finish FullCAN reception handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] rxBasicPara         Pointer to local variables of FullCAN reception
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara);
/* CODE CATEGORY 1 END */


/**********************************************************************************************************************
 *  CanLL_RxFullIsGlobalIndPending()
 *********************************************************************************************************************/
/*! \brief         Checks weather any FullCAN indication is pending (messages were received)
 *  \details       Called by task to get the overall reception state
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanTrue            Indication is pending
 *                 kCanFalse           No indication is pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxFullIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_RxFullProcessPendings()
 *********************************************************************************************************************/
/*! \brief         Reception handling for a dedicated FullCAN mailbox
 *  \details       Called by task to check the pending indication of a FullCAN mailbox and start the handling
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] taskPara            Pointer to local variables of reception task
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara);
/* CODE CATEGORY 2 END */

#endif

/**********************************************************************************************************************
 *  CanLL_ErrorHandlingBegin()
 *********************************************************************************************************************/
/*! \brief         Performs error handling begin
 *  \details       Called by error handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ErrorHandlingBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_BusOffOccured()
 *********************************************************************************************************************/
/*! \brief         Checks wheather a BusOff event occured
 *  \details       Called by error handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanTrue            BusOff occured
 *                 kCanFalse           No BusOff occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_BusOffOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */

#if defined( C_ENABLE_OVERRUN ) && defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_RxBasicCanOverrun()
 *********************************************************************************************************************/
/*! \brief         Checks wheather a BasicCAN overrun event occured
 *  \details       Called by error handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanTrue            Overrun occured
 *                 kCanFalse           No Overrun occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicCanOverrun(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
#endif


/**********************************************************************************************************************
 *  CanLL_ErrorHandlingEnd()
 *********************************************************************************************************************/
/*! \brief         Performs error handling end
 *  \details       Called by error handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ErrorHandlingEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */

#if defined( C_ENABLE_EXTENDED_STATUS )
/**********************************************************************************************************************
 *  CanLL_GetStatusBegin()
 *********************************************************************************************************************/
/*! \brief         Prepares the status information
 *  \details       Called by GetStatus API
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 3 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_GetStatusBegin(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 3 END */
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP ) && defined( C_ENABLE_WAKEUP_POLLING )
/**********************************************************************************************************************
 *  CanLL_WakeUpOccured()
 *********************************************************************************************************************/
/*! \brief         Checks whether a wakeup event occured
 *  \details       Called by wakeup handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanTrue            Wakeup occured
 *                 kCanFalse           No wakeup occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_WakeUpOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP )
/**********************************************************************************************************************
 *  CanLL_WakeUpHandling()
 *********************************************************************************************************************/
/*! \brief         Performs wakeup handling
 *  \details       Called by wakeup handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WakeUpHandling(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif

/**********************************************************************************************************************
 *  CanLL_ModeTransition()
 *********************************************************************************************************************/
/*! \brief         Performs a mode change in hardware
 *  \details       Called by mode handler
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in]     mode                Mode to be set
 *  \param[in]     busOffRecovery      BusOff recovery treatment (continue or force abortion)
 *  \param[in]     doRamCheck          RamCheck treatment (perform or not)
 *  \return        kCanOk              Successfully completed
 *                 kCanRequested       Mode not yet reached
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
**********************************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 mode, vuint8 busOffRecovery, vuint8 ramCheck);
/* CODE CATEGORY 4 END */



#if defined( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL )
/************************************************************************************************************
 *  CanLL_CanInterruptDisable()
 ***********************************************************************************************************/
/*! \brief         Disables CAN interrupts.
 *  \details       Stores current state and disables the individual CAN interrupt sources.
 *  \param[in]     canHwChannel              Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInterruptOldFlagPtr  Pointer to global variable that holds the interrupt state
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptDisable(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOldPtr localInterruptOldFlagPtr);
/* CODE CATEGORY 1 END */

/************************************************************************************************************
 *  CanLL_CanInterruptRestore()
 ***********************************************************************************************************/
/*! \brief         Restores CAN interrupts.
 *  \details       Restores the previous state of the individual CAN interrupt sources.
 *  \param[in]     canHwChannel              Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInterruptOldFlag     Global variable that holds the interrupt state
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptRestore(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOld localInterruptOldFlag);
/* CODE CATEGORY 1 END */
#endif

#if defined(C_ENABLE_LL_CAN_INTCTRL) && defined(C_ENABLE_LL_WAKEUP_SUPPORT) && !defined(C_ENABLE_WAKEUP_POLLING)
/************************************************************************************************************
 *  CanLL_CanWakeupInterruptDisable()
 ***********************************************************************************************************/
/*! \brief         Disables the CAN wakeup interrupt.
 *  \details       Disables the CAN wakeup interrupt source in hardware and stored software state.
 *  \param[in]     canHwChannel              Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInterruptOldFlagPtr  Pointer to global variable that holds the interrupt state
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanWakeupInterruptDisable(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOldPtr localInterruptOldFlagPtr);
/* CODE CATEGORY 4 END */

/************************************************************************************************************
 *  CanLL_CanWakeupInterruptEnable()
 ***********************************************************************************************************/
/*! \brief         Enables the CAN wakeup interrupt.
 *  \details       Enables the CAN wakeup interrupt source in hardware and stored software state.
 *  \param[in]     canHwChannel              Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] localInterruptOldFlagPtr  Pointer to global variable that holds the interrupt state
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanWakeupInterruptEnable(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOldPtr localInterruptOldFlagPtr);
/* CODE CATEGORY 4 END */
#endif

#if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL) && defined(C_ENABLE_WAKEUP_POLLING)
/************************************************************************************************************
 *  CanLL_CanWakeupOccurred()
 ***********************************************************************************************************/
/*! \brief         Checks whether a CAN wakeup event occurred.
 *  \details       Checks the wakeup interrupt request flag in hardware.
 *  \param[in]     canHwChannel        Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanOk              Wakeup occured
 *                 kCanFailed          No wakeup occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CanWakeupOccurred(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif

#if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL)
/************************************************************************************************************
 *  CanLL_ClearCanWakeupInterruptFlag()
 ***********************************************************************************************************/
/*! \brief         Clears previous CAN wakeup events.
 *  \details       Clears the wakeup interrupt request flag in hardware.
 *  \param[in]     canHwChannel        Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ClearCanWakeupInterruptFlag(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif

#if !defined(C_ENABLE_INTC_ACCESS_BY_APPL) 
# if defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
#  if defined(C_ENABLE_LL_CAN_INTCTRL)
/************************************************************************************************************
 *  CanLL_OsIsInterruptSourceEnabled()
 ***********************************************************************************************************/
/*! \brief         Returns the enable status of an interrupt source.
 *  \details       Retrieves the interrupt status from the operating system.
 *  \param[in]     IsrId               ISR identifier
 *  \return        true                Interrupt source is enabled
 *                 false               Interrupt source is disabled
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, boolean, STATIC_CODE) CanLL_OsIsInterruptSourceEnabled(Can_ExternalISRType IsrId);
/* CODE CATEGORY 1 END */

/************************************************************************************************************
 *  CanLL_OsRestoreInterruptSource()
 ***********************************************************************************************************/
/*! \brief         Restores the previous status of an interrupt source.
 *  \details       Uses the operating system to enable an interrupt source if it was enabled previously.
 *  \param[in]     IsrId               ISR identifier
 *  \param[in]     OldFlag             Previous state of the interrupt source
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_OsRestoreInterruptSource(Can_ExternalISRType IsrId, boolean OldFlag);
/* CODE CATEGORY 1 END */
#  endif

#  if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL) && defined(C_ENABLE_WAKEUP_POLLING)
/************************************************************************************************************
 *  CanLL_OsIsInterruptPending()
 ***********************************************************************************************************/
/*! \brief         Returns the pending status of an interrupt.
 *  \details       Retrieves the interrupt status from the operating system.
 *  \param[in]     IsrId               ISR identifier
 *  \return        true                Interrupt is pending
 *                 false               Interrupt is not pending
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, boolean, STATIC_CODE) CanLL_OsIsInterruptPending(Can_ExternalISRType IsrId);
/* CODE CATEGORY 4 END */
#  endif
# endif
#endif

/************************************************************************************************************
 *  CanLL_InitPowerOnModeTransitions()
 ***********************************************************************************************************/
/*! \brief         Internal function, called by module initialization.
 *  \details       Performs global mode transitions.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitPowerOnModeTransitions(void);
/* CODE CATEGORY 4 END */

/************************************************************************************************************
 *  CanLL_InitPowerOnGlobalInit()
 ***********************************************************************************************************/
/*! \brief         Internal function, called by module initialization.
 *  \details       Initializes the shared resources of RSCAN.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitPowerOnGlobalInit(void);
/* CODE CATEGORY 4 END */

/************************************************************************************************************
 *  CanLL_InitPowerOnRuleAndFifoInit()
 ***********************************************************************************************************/
/*! \brief         Internal function, called by module initialization.
 *  \details       Initializes the RSCAN acceptance filter rules and FIFO buffers.
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitPowerOnRuleAndFifoInit(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/************************************************************************************************************
 *  CanLL_InitPowerOnRulePageUpdate()
 ***********************************************************************************************************/
/*! \brief         Internal function, called by module initialization.
 *  \details       Checks the receive rule write index and updates the page if necessary.
 *  \param[in]     canFilterRulesIndexPtr  Current receive rule write index
 *  \param[in]     canFilterRulesPagePtr   Current receive rule page
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitPowerOnRulePageUpdate(CanVarPtr8 canFilterRulesIndexPtr, CanVarPtr8 canFilterRulesPagePtr);
/* CODE CATEGORY 4 END */
#endif

/************************************************************************************************************
 *  CanLL_WriteReg32()
 ***********************************************************************************************************/
/*! \brief         Internal function, writes values to CAN registers and performs a RamCheck.
 *  \details       Writes and verifies initialization values to channel registers.
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in,out] regPtr              Pointer to register
 *  \param[in]     val                 Value to be written
 *  \param[in,out] initPara            Pointer to local variables of CanHL_ReInit()
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WriteReg32(CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr32 regPtr, vuint32 val, CanInitParaStructPtr initPara);
/* CODE CATEGORY 4 END */

/************************************************************************************************************
 *  CanLL_WriteRegGlobal32()
 ***********************************************************************************************************/
/*! \brief         Internal function, writes values to CAN registers and performs a RamCheck.
 *  \details       Writes and verifies initialization values to global registers.
 *  \param[in,out] regPtr              Pointer to register
 *  \param[in]     val                 Value to be written
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WriteRegGlobal32(CanChipMsgPtr32 regPtr, vuint32 val);
/* CODE CATEGORY 4 END */

/************************************************************************************************************
 *  CanLL_ModeWait()
 ***********************************************************************************************************/
/*! \brief         Internal function, waits until a channel mode transition is succesfully completed.
 *  \details       Waits synchronously until the channel status register indicates the expected mode.
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \param[in]     PhysChannel         Physical channel index
 *  \param[in]     Mode                Mode transition
 *  \param[in]     Loop                Identifier for HW loop
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ModeWait(CAN_CHANNEL_CANTYPE_FIRST CanChannelHandle PhysChannel, vuint8 Mode, vuint8 Loop);
/* CODE CATEGORY 4 END */

/************************************************************************************************************
 *  CanLL_GlobalModeWait()
 ***********************************************************************************************************/
/*! \brief         Internal function, waits until a global mode transition is succesfully completed.
 *  \details       Waits synchronously until the global status register indicates the expected mode.
 *  \param[in]     Mode                Mode transition
 *  \param[in]     Loop                Identifier for HW loop
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_GlobalModeWait(vuint8 Mode, vuint8 Loop);
/* CODE CATEGORY 4 END */

/************************************************************************************************************
 *  CanLL_ChannelTransitionReset()
 ***********************************************************************************************************/
/*! \brief         Internal function, performs a transition to channel reset mode.
 *  \details       Waits synchronously until the mode is reached.
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ChannelTransitionReset(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

#if defined(C_ENABLE_SLEEP_WAKEUP)
/************************************************************************************************************
 *  CanLL_ChannelTransitionSleep()
 ***********************************************************************************************************/
/*! \brief         Internal function, performs a transition to channel stop mode and enables the wakeup interrupt.
 *  \details       Waits synchronously until the mode is reached.
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ChannelTransitionSleep(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif

/************************************************************************************************************
 *  CanLL_ChannelTransitionStart()
 ***********************************************************************************************************/
/*! \brief         Internal function, performs a transition to channel communication mode.
 *  \details       Waits synchronously until the mode is reached.
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ChannelTransitionStart(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */

#if defined(C_ENABLE_SILENT_MODE)
/************************************************************************************************************
 *  CanLL_ChannelTransitionHalt()
 ***********************************************************************************************************/
/*! \brief         Internal function, performs a transition to channel halt mode.
 *  \details       Waits synchronously until the mode is reached.
 *  \param[in]     channel             Index of the CAN channel (only if multiple channels are used)
 *  \return        kCanOk              Successfully completed
 *                 kCanFailed          Failure occured
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ChannelTransitionHalt(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif


#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
/************************************************************************************************************
 *  CanLL_IsGlobalRegisterCorrupt()
 ***********************************************************************************************************/
/*! \brief         Internal function, performs the global part of extended CAN RAM test.
 *  \details       Checks the global RSCAN control registers.
 *  \return        kCanTrue            Register RAM is corrupt
 *                 kCanFalse           Register RAM is not corrupt
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_IsGlobalRegisterCorrupt(void);
/* CODE CATEGORY 4 END */
#endif

#if (CAN_SAFE_BSW == STD_ON)
/************************************************************************************************************
 *  CanLL_CheckGeneratedData()
 ***********************************************************************************************************/
/*! \brief         Internal function, checks the generated data for SafeBSW.
 *  \details       Validation of the generated data against constant values that are verfied by user review.
 *  \return        kCanOk              Data is valid
 *                 kCanFailed          Data is invalid
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 ***********************************************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckGeneratedData(void);
/* CODE CATEGORY 4 END */
#endif


# if (CAN_HW_LOOP_SUPPORT_API == STD_OFF)
/************************************************************************************************************
 *  ApplCanTimerLoop()
 ***********************************************************************************************************/
/*! \brief         Time out monitoring
 *  \details       Service function to check (against generated maximum loop value) whether a hardware loop shall be continued or broken.
 *  \param[in]     Controller  CAN controller on which the hardware observation takes place. \n
 *                             (only if not using "Optimize for one controller")
 *  \param[in]     source      Source for the hardware observation.
 *  \return        CAN_NOT_OK  when loop shall be broken (observation stops) \n
 *                             CAN_NOT_OK should only be used in case of a time out occurs due to a hardware issue. \n
 *                             After this an appropriate error handling is needed (see chapter Hardware Loop Check / Time out Monitoring).
 *  \return        CAN_OK      when loop shall be continued (observation continues)
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         Please refer to chapter "Hardware Loop Check".
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) ApplCanTimerLoop(CAN_CHANNEL_CANTYPE_FIRST uint8 source);
# endif

/************************************************************************************************************
 *  CanHL_ModeTransition()
 ***********************************************************************************************************/
/*! \brief         Request mode transition
 *  \details       Handle/Request transition and wait asynchronous-short time.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller         CAN controller (Controller must be in valid range). \n
 *                                    (only if not using "Optimize for one controller") \n
 *  \param[in]     transitionRequest  transition request used to switch mode (kCanModeInit, kCanModeSleep, kCanModeWakeupStopReinit, \n
 *                                    kCanModeStopReinit, kCanModeStopReinitFast, kCanModeStart, kCanModeStartReinit, kCanModeSilent, \n
 *                                    kCanModeResetBusOffStart, kCanModeResetBusOffEnd). \n
 *  \param[in]     busOffRecovery     handling of the busoff behaviour (kCanFinishBusOffRecovery, kCanContinueBusOffRecovery). \n
 *  \param[in]     doRamCheck         do a RAM check while reinit or not (kCanExecuteRamCheck, kCanSuppressRamCheck). \n
 *  \return        kCanFailed         transition rejected
 *  \return        kCanRequested      transition requested but is ongoing asynchronous
 *  \return        kCanOk             transition finished successful
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_ModeTransition(CAN_CHANNEL_CANTYPE_FIRST uint8 transitionRequest, uint8 busOffRecovery, uint8 doRamCheck);

/************************************************************************************************************
 *  CanHL_NotifyTransition()
 ***********************************************************************************************************/
/*! \brief         notify about sucessful mode transition
 *  \details       notify to upper layer.
 *                 Called by Can_SetControllerMode().
 *  \param[in]     Controller         CAN controller (Controller must be in valid range). \n
 *                                    (only if not using "Optimize for one controller") \n
 *  \param[in]     canState           CAN controller mode to be switched to (CAN_STATUS_STOP, CAN_STATUS_START, CAN_STATUS_SLEEP). \n
 *  \param[in]     canIfState         CAN controller mode to be switched to (CANIF_CS_STOPPED, CANIF_CS_STARTED, CANIF_CS_SLEEP). \n
 *  \param[in]     transitionState    transition request state (kCanFailed, kCanRequested, kCanOk). \n
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_NotifyTransition(CAN_CHANNEL_CANTYPE_FIRST uint8 canState, CanIf_ControllerModeType canIfState, uint8 transitionState);

#if defined(C_ENABLE_CANCEL_IN_HW)
/************************************************************************************************************
 *  CanHL_IsHigherCanIdPrio()
 ***********************************************************************************************************/
/*! \brief         check CAN ID priority
 *  \details       compare two CAN IDs and check if first one is of higher priority.
 *  \param[in]     CanId1        first CAN ID for compare
 *  \param[in]     CanId2        second CAN ID for compare
 *  \return        CAN_OK        first CAN ID has higher priority
 *  \return        CAN_NOT_OK    first CAN ID has no higher priority
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_IsHigherCanIdPrio(Can_IdType CanId1, Can_IdType CanId2);
#endif

/************************************************************************************************************
 *  CanHL_WritePrepare()
 ***********************************************************************************************************/
/*! \brief         TX preparation
 *  \details       Search for BasicCAN object handle to transmit (Multiplexed TX) and backup data for cancel TX object if necessary.
 *                 calculate txPara member activeSendObject, and mailboxElement
 *                 Called by Can_Write().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in,out] txPara           mailbox information
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WritePrepare(CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);

#if defined(C_ENABLE_CANCEL_IN_HW) || \
   (defined(C_ENABLE_TX_HW_FIFO) && defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2) )
/************************************************************************************************************
 *  CanHL_WriteSavePduInfo()
 ***********************************************************************************************************/
/*! \brief         Save PduInfo before send
 *  \details       Cancellation or TxHwFifo need to save send data to get this information in confirmation context.
 *  \param[in,out] txPara                    mailbox information
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WriteSavePduInfo(CanTxTransmissionParaStructPtr txPara);
#endif

#if defined(C_ENABLE_CANCEL_IN_HW)
/************************************************************************************************************
 *  CanHL_WritePrepareCancelTx()
 ***********************************************************************************************************/
/*! \brief         TX cancellation
 *  \details       Cancel the BasicCAN TX object or store message data for later cancelation
 *                 Called by CanHL_WritePrepare().
 *  \param[in]     Controller                CAN controller. \n
 *                                           (only if not using "Optimize for one controller")
 *  \param[in,out] txPara                    mailbox information
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WritePrepareCancelTx(CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);
#endif

/************************************************************************************************************
 *  CanHL_WriteStart()
 ***********************************************************************************************************/
/*! \brief         TX start
 *  \details       Write ID, DLC and Data to FullCAN or BasicCAN object and set transmit request
 *                 Called by Can_Write().
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in,out] txPara          mailbox information
 *  \return        CAN_NOT_OK      transmission failed.
 *  \return        CAN_OK          transmission successful.
 *  \return        CAN_BUSY        transition object busy - repeat it.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WriteStart(CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara);

/************************************************************************************************************
 *  CanHL_GetActiveSendObject()
 ***********************************************************************************************************/
/*! \brief         Convert Handle
 *  \details       Hardware to logical Handle conversion.
 *  \param[in]     mailboxHandle   Handle to mailbox object
 *  \param[in]     mailboxElement  mailbox element
 *  \return        logical handle for the given hardware mailbox
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_GetActiveSendObject(Can_HwHandleType mailboxHandle, Can_HwHandleType mailboxElement);

#if defined(C_ENABLE_CANCEL_IN_HW) || \
   (defined(C_ENABLE_TX_HW_FIFO) && defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2) )
/************************************************************************************************************
 *  CanHL_GetActiveSendData()
 ***********************************************************************************************************/
/*! \brief         Convert Handle
 *  \details       Hardware to logical Handle conversion.
 *  \param[in]     mailboxHandle   Handle to mailbox object
 *  \param[in]     mailboxElement  mailbox element
 *  \return        start index in the data buffer for the given mailbox
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint16, STATIC_CODE) CanHL_GetActiveSendData(Can_HwHandleType mailboxHandle, uint8 mailboxElement);
#endif

#if defined(C_ENABLE_CAN_RAM_CHECK)
/************************************************************************************************************
 *  CanHL_RamCheckMailboxNotification()
 ***********************************************************************************************************/
/*! \brief         RAM check
 *  \details       Notify upper layer in case of an HW issue and deactivate controller.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \param[in]     htrh             Hrh or Hth of the hardware object
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

/************************************************************************************************************
 *  CanHL_InitBegin()
 ***********************************************************************************************************/
/*! \brief         Start Initialization
 *  \details       LL implementation see token CanLL_InitBegin description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitBegin(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);

#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_InitTxFullCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize TX FullCAN
 *  \details       LL implementation see token CanLL_InitTxObj description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara          include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxFullCAN(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

/************************************************************************************************************
 *  CanHL_InitTxBasicCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize TX BasicCAN
 *  \details       LL implementation see token CanLL_InitTxObj description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxBasicCAN(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);


#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/************************************************************************************************************
 *  CanHL_InitRxFullCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize RX FullCAN
 *  \details       LL implementation see token CanLL_InitFullCANObj description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxFullCAN(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/************************************************************************************************************
 *  CanHL_InitRxBasicCAN()
 ***********************************************************************************************************/
/*! \brief         Initialize RX BasicCAN
 *  \details       LL implementation see token CanLL_InitBasicCANObj description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxBasicCAN(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);
#endif

/************************************************************************************************************
 *  CanHL_InitEnd_InitMode()
 ***********************************************************************************************************/
/*! \brief         End Initialization
 *  \details       LL implementation see token CanLL_InitEnd_InitMode description.
 *                 Called by CanHL_ReInit().
 *  \param[in]     Controller       CAN controller. \n
 *                                  (only if not using "Optimize for one controller")
 *  \param[in]     initPara         include controller and all LL specific settings.
 *  \return        errorId
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_InitMode(CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara);

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/************************************************************************************************************
 *  CanHL_RxBasicCanPolling()
 ***********************************************************************************************************/
/*! \brief         RX BasicCAN polling
 *  \details       RX BasicCAN polling handling.
 *                 Called by Can_MainFunctionRead().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicCanPolling(CAN_HW_CHANNEL_CANTYPE_ONLY);
# endif
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/************************************************************************************************************
 *  CanHL_RxFullCanPolling()
 ***********************************************************************************************************/
/*! \brief         RX FullCAN polling
 *  \details       RX FullCAN polling handling.
 *                 Called by Can_MainFunctionRead().
 *  \param[in]     Controller    CAN controller.
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullCanPolling(CAN_HW_CHANNEL_CANTYPE_ONLY);
# endif
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/************************************************************************************************************
 *  CanHL_RxMsgReceivedNotification()
 ***********************************************************************************************************/
/*! \brief         RX notification
 *  \details       RX queue and notification handling for BasicCAN and FullCAN reception.
 *                 Called by CanHL_BasicCanMsgReceived(),CanHL_FullCanMsgReceived().
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxStructPtr     include general rx info and all LL specific data.
 *  \return        errorId         error identifier reporting to DET
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANTYPE_FIRST CanRxInfoStructPtr rxStructPtr);
#endif

#if defined(C_ENABLE_RX_QUEUE)
/************************************************************************************************************
 *  CanHL_RxQueueExecution()
 ***********************************************************************************************************/
/*! \brief         RX queue
 *  \details       RX queue execution and notification.
 *                 Called by Can_MainFunction_Read().
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxQueueExecution(void);
#endif

#if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */
/************************************************************************************************************
 *  CanHL_TxConfirmationPolling()
 ***********************************************************************************************************/
/*! \brief         TX Confirmation intermediate call
 *  \details       intermediate call to do interrupt locks between polling call from LL and HL handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     mailboxHandle   mailbox handle
 *  \param[in]     mailboxElement  index of the mailboxElement (muxTx, FIFO)
 *  \param[in]     hwObjHandle     hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_TxConfirmationPolling(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle mailboxHandle, CanObjectHandle mailboxElement, CanObjectHandle hwObjHandle);
#endif

/************************************************************************************************************
 *  CanHL_TxConfirmation()
 ***********************************************************************************************************/
/*! \brief         TX Confirmation handling
 *  \details       Called for a transmit or cancel event. Finish transmission by free send mailbox and call confirmation. \n
 *                 Called for FullCAN and BasicCAN handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     mailboxHandle   mailbox handle
 *  \param[in]     mailboxElement  index of the mailboxElement (muxTx, FIFO)
 *  \param[in]     hwObjHandle     transmitted hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_TxConfirmation(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle mailboxHandle, CanObjectHandle mailboxElement, CanObjectHandle hwObjHandle);

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/************************************************************************************************************
 *  CanHL_BasicCanMsgReceivedPolling()
 ***********************************************************************************************************/
/*! \brief         RX Indication intermediate call
 *  \details       intermediate call to do interrupt locks between polling call from LL and HL handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_BasicCanMsgReceivedPolling(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle);
# endif

/************************************************************************************************************
 *  CanHL_BasicCanMsgReceived()
 ***********************************************************************************************************/
/*! \brief         Handle reception
 *  \details       Receive BasicCAN data and call indication function.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_BasicCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle,Can_PduType pdu);
#endif

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/************************************************************************************************************
 *  CanHL_FullCanMsgReceivedPolling()
 ***********************************************************************************************************/
/*! \brief         RX Indication intermediate call
 *  \details       intermediate call to do interrupt locks between polling call from LL and HL handling.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_FullCanMsgReceivedPolling(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle);
#endif

/************************************************************************************************************
 *  CanHL_FullCanMsgReceived()
 ***********************************************************************************************************/
/*! \brief         Handle reception
 *  \details       Receive FullCAN data and call indication function.
 *  \param[in]     Controller      CAN controller. \n
 *                                 (only if not using "Optimize for one controller")
 *  \param[in]     rxMailboxHandle mailbox handle
 *  \param[in]     hwObjHandle     received hardware handle
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_FullCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle);
#endif

/************************************************************************************************************
 *  CanHL_ErrorHandling()
 ***********************************************************************************************************/
/*! \brief         BUSOFF handling
 *  \details       Handler for bus off situation.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_ErrorHandling(CAN_HW_CHANNEL_CANTYPE_ONLY);

# if defined(C_ENABLE_SLEEP_WAKEUP)
/************************************************************************************************************
 *  CanHL_WakeUpHandling()
 ***********************************************************************************************************/
/*! \brief         WAKUP handling
 *  \details       Handler for WAKEUP event. Call EcuM for notification. Will be called in case of WAKEUP occurred.
 *  \param[in]     Controller    CAN controller. \n
 *                               (only if not using "Optimize for one controller")
 *  \pre           -
 *  \context       ANY
 *  \reentrant     FALSE
 *  \synchronous   TRUE
***********************************************************************************************************/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WakeUpHandling(CAN_CHANNEL_CANTYPE_ONLY);
# endif

#if defined(C_ENABLE_CANCEL_TX_IN_HW) 
#endif

/************************************************************************************************************
 *  CanHL_ReInit()
 ***********************************************************************************************************/
/*! \brief         Initialization of controller specific CAN hardware.
 *  \details       Initialization of the CAN controller hardware registers and CAN driver variables. \n
 *                 after that the controller is fully initialized and can be swtiched to "STOP Mode".
 *  \param[in]     Controller            CAN controller. \n
 *                                       (only if not using "Optimize for one controller")
 *  \param[in]     doRamCheck            RAM check exectuion (kCanExecuteRamCheck, kCanSuppressRamCheck).
 *  \return        error                 return kCanFailed in case of issue or kCanOk if initialization pass.
 *  \pre           controller is ready to be configured (INIT mode).
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \notes         no mode change must be done inside. No CAN bus depended hardware loops allowed.
***********************************************************************************************************/
V_DEF_FUNC(CAN_STATIC, uint8, STATIC_CODE) CanHL_ReInit(CAN_HW_CHANNEL_CANTYPE_FIRST uint8 doRamCheck);

#define CAN_STOP_SEC_STATIC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* CAN_LOCAL_H */

/* End of channel */



/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

