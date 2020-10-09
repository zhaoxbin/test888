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
/*!        \file  CanTp_Types.h
 *        \brief  CanTp type definitions
 *
 *      \details  CanTp definitions of structs and enumerations and simple types.
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
#if !defined (CANTP_TYPES_H)
#define CANTP_TYPES_H


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ComStack_Types.h"
#include "CanTp_Cfg.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* --- AUTOSAR Version Selection ----------------------------------------------------------------------------------- */
#if defined (MSR_PDUR_API_AR_VERSION)                                                                                  /* COV_CANTP_EXCLUDED_FEATURES XF */
/* use module independent definition to override / set PduR version */
# undef  CANTP_PDUR_API_AR_VERSION                                                                                     /* PRQA S 0841 */ /* MD_CanTp_0841 */
# define CANTP_PDUR_API_AR_VERSION        MSR_PDUR_API_AR_VERSION
#endif

#if defined (CANTP_PDUR_API_AR_VERSION)                                                                                /* COV_CANTP_EXCLUDED_FEATURES TX */
# if   (CANTP_PDUR_API_AR_VERSION == 0x403)                                                                            /* COV_CANTP_EXCLUDED_FEATURES XF */
#  define CANTP_PDUR_API_403_ENABLED             STD_ON
#  define CANTP_PDUR_API_412_ENABLED             STD_OFF
# elif (CANTP_PDUR_API_AR_VERSION == 0x412)                                                                            /* COV_CANTP_EXCLUDED_FEATURES TX */
#  define CANTP_PDUR_API_403_ENABLED             STD_OFF
#  define CANTP_PDUR_API_412_ENABLED             STD_ON
# else
#  error "Not supported PduR version! No PduR BSWMD file in your MSR project?"
# endif
#else
# error "Missing CANTP_PDUR_API_AR_VERSION! Mixing new BSW with old generation tool?"
#endif


/* --- Constants Required by Type Definitions ---------------------------------------------------------------------- */
#if !defined (CANTP_TX_QUEUE_SIZE)                                                                                     /* COV_CANTP_EXCLUDED_FEATURES TX */
# define CANTP_TX_QUEUE_SIZE                     4u         /* transmit queue size; must be a power of 2             */
#else
# if ((CANTP_TX_QUEUE_SIZE & (CANTP_TX_QUEUE_SIZE - 1)) != 0)                                                          /* COV_CANTP_EXCLUDED_FEATURES XX xx xx xx */
/* e.g. size=4: 0x0100 & 0x00FF = 0x0000 ---> ok     */
/*      size=6: 0x0110 & 0x0101 = 0x0100 ---> not ok */
#  error "CANTP_TX_QUEUE_SIZE must be a power of 2 (2, 4, 8, 16...)"
# endif
#endif


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* --- Enumerations ------------------------------------------------------------------------------------------------ */
/* Frame Type */
typedef uint8                                    CanTp_FrameType;
#define CANTP_FRAME_SF                           (0x00u)
#define CANTP_FRAME_FF                           (0x01u)
#define CANTP_FRAME_CF                           (0x02u)
#define CANTP_FRAME_FC                           (0x03u)
#define CANTP_FRAME_INVALID                      (0x04u)

/* Initialization Status */
typedef uint8                                    CanTp_InitStatusType;
#define CANTP_STATUS_NOT_INITIALIZED             CANTP_OFF
#define CANTP_STATUS_INITIALIZED                 CANTP_ON
#define CANTP_STATUS_SHUTDOWN                    CANTP_STATUS_NOT_INITIALIZED

/* Tx States */
typedef uint8                                    CanTp_TxChannelStateType;
#define CANTP_TXSTATE_IDLE                       (0x00u)  /* must be zero due to optimization */
#define CANTP_TXSTATE_WAIT_FC                    (0x01u)
#define CANTP_TXSTATE_WAIT_STMIN_INTERN          (0x02u)
#define CANTP_TXSTATE_WAIT_STMIN_APPL            (0x03u)
#define CANTP_TXSTATE_TRANSMIT_ANY               (0x10u)  /* bit mask for pending transmission */
#define CANTP_TXSTATE_TRANSMIT_ANY_MASK          (0xEFu)  /* inverted bit mask for pending transmission */
#define CANTP_TXSTATE_TRANSMIT_SF                (0x11u)
#define CANTP_TXSTATE_TRANSMIT_FF                (0x12u)
#define CANTP_TXSTATE_TRANSMIT_CF                (0x13u)
#define CANTP_TXSTATE_WAIT_TXCONF_ANY            (0x20u)  /* bit mask for pending Tx Confirmation */
#define CANTP_TXSTATE_WAIT_TXCONF_SF             (0x21u)
#define CANTP_TXSTATE_WAIT_TXCONF_FF             (0x22u)
#define CANTP_TXSTATE_WAIT_TXCONF_CF             (0x23u)
#define CANTP_TXSTATE_WAIT_BUFFER_ANY            (0x40u)  /* bit mask for buffer request */
#define CANTP_TXSTATE_WAIT_BUFFER_SF             (0x41u)
#define CANTP_TXSTATE_WAIT_BUFFER_FF             (0x42u)
#define CANTP_TXSTATE_WAIT_BUFFER_CF             (0x43u)

/* Rx States */
typedef uint8                                    CanTp_RxChannelStateType;
#define CANTP_RXSTATE_IDLE                       (0x00u)  /* must be zero due to optimization */
#define CANTP_RXSTATE_WAIT_CF                    (0x01u)
#define CANTP_RXSTATE_WAIT_NEXT_FCWAIT           (0x02u)
#define CANTP_RXSTATE_TRANSMIT_FC_ANY            (0x10u)  /* bit mask for pending transmission */
#define CANTP_RXSTATE_TRANSMIT_FC_ANY_MASK       (0xEFu)  /* inverted bit mask for pending transmission */
#define CANTP_RXSTATE_TRANSMIT_FC_CTS            (0x11u)
#define CANTP_RXSTATE_TRANSMIT_FC_WT             (0x12u)
#define CANTP_RXSTATE_TRANSMIT_FC_OVFL           (0x13u)
#define CANTP_RXSTATE_WAIT_TXCONFFC_ANY          (0x20u)  /* bit mask for pending Tx Confirmation */
#define CANTP_RXSTATE_WAIT_TXCONFFC_CTS          (0x21u)
#define CANTP_RXSTATE_WAIT_TXCONFFC_WT           (0x22u)
#define CANTP_RXSTATE_WAIT_TXCONFFC_OVFL         (0x23u)
#define CANTP_RXSTATE_WAIT_BUFFER_ANY            (0x40u)  /* bit mask for buffer request */
#define CANTP_RXSTATE_WAIT_BUFFER_SF             (0x41u)
#define CANTP_RXSTATE_WAIT_BUFFER_FF             (0x42u)
#define CANTP_RXSTATE_WAIT_BUFFER_CF             (0x43u)

/* Direction */
typedef uint8                                    CanTp_DirectionType;
#define CANTP_DIR_NONE                           (CanTp_DirectionType)(0x01u)
#define CANTP_DIR_TX                             (CanTp_DirectionType)(0x02u)
#define CANTP_DIR_RX                             (CanTp_DirectionType)(0x03u)

/* Notification Result (depends on AUTOSAR version) */
#if (CANTP_PDUR_API_403_ENABLED == STD_ON)                                                                             /* COV_CANTP_EXCLUDED_FEATURES XF */
typedef  NotifResultType                         CanTp_NotificationType;
# define CANTP_NOTIFY_OK                         (NotifResultType)NTFRSLT_OK
# define CANTP_NOTIFY_NOT_OK                     (NotifResultType)NTFRSLT_E_NOT_OK
# define CANTP_NOTIFY_TIMEOUT_A                  (NotifResultType)NTFRSLT_E_TIMEOUT_A
# define CANTP_NOTIFY_TIMEOUT_B                  (NotifResultType)NTFRSLT_E_TIMEOUT_BS
# define CANTP_NOTIFY_TIMEOUT_C                  (NotifResultType)NTFRSLT_E_TIMEOUT_CR
# define CANTP_NOTIFY_WRONG_SN                   (NotifResultType)NTFRSLT_E_WRONG_SN
# define CANTP_NOTIFY_INVALID_FS                 (NotifResultType)NTFRSLT_E_INVALID_FS
# define CANTP_NOTIFY_UNEXP_PDU                  (NotifResultType)NTFRSLT_E_UNEXP_PDU
# define CANTP_NOTIFY_WFT_OVERRUN                (NotifResultType)NTFRSLT_E_WFT_OVRN
# define CANTP_NOTIFY_NO_BUFFER                  (NotifResultType)NTFRSLT_E_NO_BUFFER
# define CANTP_NOTIFY_CANCEL_OK                  (NotifResultType)NTFRSLT_E_CANCELATION_OK
# define CANTP_NOTIFY_CANCEL_NOT_OK              (NotifResultType)NTFRSLT_E_CANCELATION_NOT_OK
# define CANTP_NOTIFY_NORESULT                   (NotifResultType)(0x80u)  /* additional definition to control PduR notification in CanTp_RxInit() */
#else
typedef  Std_ReturnType                          CanTp_NotificationType;
# define CANTP_NOTIFY_OK                         (Std_ReturnType)E_OK
# define CANTP_NOTIFY_NOT_OK                     (Std_ReturnType)E_NOT_OK
# define CANTP_NOTIFY_TIMEOUT_A                  (Std_ReturnType)E_NOT_OK
# define CANTP_NOTIFY_TIMEOUT_B                  (Std_ReturnType)E_NOT_OK
# define CANTP_NOTIFY_TIMEOUT_C                  (Std_ReturnType)E_NOT_OK
# define CANTP_NOTIFY_WRONG_SN                   (Std_ReturnType)E_NOT_OK
# define CANTP_NOTIFY_INVALID_FS                 (Std_ReturnType)E_NOT_OK
# define CANTP_NOTIFY_UNEXP_PDU                  (Std_ReturnType)E_NOT_OK
# define CANTP_NOTIFY_WFT_OVERRUN                (Std_ReturnType)E_NOT_OK
# define CANTP_NOTIFY_NO_BUFFER                  (Std_ReturnType)E_NOT_OK
# define CANTP_NOTIFY_CANCEL_OK                  (Std_ReturnType)E_NOT_OK
# define CANTP_NOTIFY_CANCEL_NOT_OK              (Std_ReturnType)E_NOT_OK
# define CANTP_NOTIFY_NORESULT                   (Std_ReturnType)(0x80u)  /* additional definition to control PduR notification in CanTp_RxInit() */
#endif

/* Buffer Result (cast from enum to uint8) */
typedef uint8                                    CanTp_BufferStateType;
#define CANTP_BUFREQ_OK                          (CanTp_BufferStateType)BUFREQ_OK
#define CANTP_BUFREQ_E_NOT_OK                    (CanTp_BufferStateType)BUFREQ_E_NOT_OK
#define CANTP_BUFREQ_E_BUSY                      (CanTp_BufferStateType)BUFREQ_E_BUSY
#define CANTP_BUFREQ_E_OVFL                      (CanTp_BufferStateType)BUFREQ_E_OVFL


/* --- Basic Types ------------------------------------------------------------------------------------------------- */
/* Vector specific types */
typedef unsigned int    CanTp_BitType;
typedef uint16          CanTp_WFTmaxType;
typedef uint16          CanTp_TimerType;
typedef uint8           CanTp_AddressingFormatType;


/* --- Structs ----------------------------------------------------------------------------------------------------- */
/*! Rx State Machine data */
typedef struct sCanTp_RxStateType
{
  CanTp_FrameType                   FrameType;          /*!< frame type currently processed */
  volatile CanTp_RxChannelStateType ChannelState;       /*!< current channel state */
  CanTp_TimerType                   Timer;              /*!< channel timer & channel activation (!=0 means active) */
  PduLengthType                     DataLength;         /*!< length of complete message */
  PduLengthType                     DataIndex;          /*!< index within complete message */
  PduLengthType                     ProvidedBufferSize; /*!< size of currently available buffer */
  PduIdType                         RxHdl;              /*!< Rx Sdu handle, to which this state data is related to */
  CanTp_WFTmaxType                  WFTCounter;         /*!< wait frame counter */
  CanTp_BufferStateType             BufferState;        /*!< status of buffer provision */
  uint8                             BlocksizeCounter;   /*!< Block Size for next FC and for CF counting */
  uint8                             Payload[CANTP_MAX_PAYLOAD_LENGTH]; /*!< local buffer for payload of current frame */
  uint8                             PayloadLength;      /*!< number of payload bytes in local buffer */
  uint8                             InitalDLC;          /*!< DLC of the FF against which the subsequent CFs must be checked */
  uint8                             ExpectedSN;         /*!< expected SN in next CF */
#if (( CANTP_ONLY_NOTIFY_INFORMED_APPL == STD_ON ) || ( CANTP_RC == STD_ON ))
  uint8                             ApplState;          /*!< Application notification state */
#endif
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
  uint8                             SduMetadata[CANTP_MAX_SDU_METADATA_LENGTH];   /*!< local buffer for SDU metadata */
  uint8                             SduMetadataLength;                            /*!< number of SDU metadata bytes */
# if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
  uint8                             FcPduMetadata[CANTP_MAX_PDU_METADATA_LENGTH]; /*!< local buffer for fc-PDU metadata */
  uint8                             FcPduMetadataLength;                          /*!< number of fc-PDU metadata bytes */
# endif
#endif
} CanTp_RxStateType;


/*! Tx State Machine data */
typedef struct sCanTp_TxStateType
{
  CanTp_TimerType                   Timer;              /*!< channel timer & channel activation (!=0 means active) */
  PduLengthType                     DataLength;         /*!< length of complete message */
  PduLengthType                     DataIndex;          /*!< index within complete message (exact byte) */
  PduIdType                         TxHdl;              /*!< Tx Sdu handle, to which this state data is related to */
#if (CANTP_STMIN_BY_APPL == STD_ON)
  PduIdType                         TxSduSnv;           /*!< Symbolic name value of the Tx connection */
#endif
  volatile CanTp_TxChannelStateType ChannelState;       /*!< current channel state */
  CanTp_BufferStateType             BufferState;        /*!< status of buffer provision */
  uint8                             STmin;              /*!< STmin from last FC */
  uint8                             STminTimer;         /*!< timer for end of STmin */
  uint8                             BlocksizeCounter;   /*!< current value for CF counting */
#if (CANTP_USE_ONLY_FIRST_FC == STD_ON)
  uint8                             BS;                 /*!< block size from first FC */
#endif
  uint8                             Payload[CANTP_MAX_PAYLOAD_LENGTH]; /*!< local buffer for payload of current frame */
  uint8                             PayloadLength;      /*!< number of payload bytes in local buffer */
  uint8                             SeqNumber;          /*!< SN for next CF */
#if (CANTP_USE_ONLY_FIRST_FC == STD_ON)
  boolean                           FirstFCReceived;    /*!< FALSE: next FC is the first FC; TRUE: first FC have already been received */
#endif
  uint8                             FCLength;           /*!< length of FC which have been received before TxConf (0 = no FC received) */
  uint8                             FCData[4];          /*!< data of FC received before TxConf (only valid if FCLength > 0) */
#if (CANTP_GENERIC_CONNECTIONS == STD_ON)
  uint8                             SduMetadata[CANTP_MAX_SDU_METADATA_LENGTH];     /*!< local buffer for SDU metadata */
  uint8                             SduMetadataLength;                              /*!< number of SDU metadata bytes */
# if (CANTP_MAX_PDU_METADATA_LENGTH != 0)
  uint8                             DataPduMetadata[CANTP_MAX_PDU_METADATA_LENGTH]; /*!< local buffer for data-PDU metadata */
  uint8                             DataPduMetadataLength;                          /*!< number of data-PDU metadata bytes */
# endif
#endif
} CanTp_TxStateType;


/*! Dynamic FlowControl Parameters */
typedef struct sCanTp_DynFCParameterType
{
  uint8                  BS;           /*!< BlockSize which have been set by ChangeParam API */
  uint8                  STmin;        /*!< STmin which have been set by ChangeParam API     */
} CanTp_DynFCParameterType;


/*! Transmit Semaphore */
typedef struct sTxSemaphoreType
{
  PduIdType            Handle;         /*!< SduHdl which currently holds the semaphore (if semaphore is free: CANTAP_INVALID_HDL) */
  CanTp_DirectionType  Direction;      /*!< Communication direction: Rx or Tx */
} CanTp_TxSemaphoreType;


/*! Transmit Queue Entries */
typedef struct sTxQueueEntrype
{
  PduIdType              PduId;                                                           /*!< Tx Id for CanIf_Transmit */
  PduIdType              SduHandle;                                                       /*!< Handle for TxSemaphore locking */
  CanTp_DirectionType    SduDirection;                                                    /*!< Direction for TxSemaphore locking */
  PduLengthType          SduLength;                                                       /*!< SduLength for CanIf_Transmit */
  uint8                  SduData[CANTP_MAX_FRAME_LENGTH + CANTP_MAX_PDU_METADATA_LENGTH]; /*!< SduData for CanIf_Transmit (contains payload and PDU metadata) */
} CanTp_TxQueueEntryType;


/*! Transmit Queue */
typedef struct sTxQueueType
{
  CanTp_TxQueueEntryType  Entries[CANTP_TX_QUEUE_SIZE];         /*!< Tx queue entries */
  uint8                   ReadPos;                              /*!< next entry to be read */
  uint8                   WritePos;                             /*!< next entry to be written */
} CanTp_TxQueueType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* CANTP_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: CanTp_Types.h
 *********************************************************************************************************************/
