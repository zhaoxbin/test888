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
/**        \file  CanIf.c
 *        \brief  CAN Interface source file.
 *
 *      \details  This file contains the implementation of the AUTOSAR CAN Interface module.
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

#define CANIF_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
 
/* ECO_IGNORE_BLOCK_BEGIN */
/* \trace SPEC-1880, SPEC-3742, SPEC-1915, SPEC-1891, SPEC-1914, SPEC-1932, SPEC-1929 */
#include "CanIf.h"

#include "CanIf_Cbk.h"

/* \trace SPEC-1225, SPEC-1859, SPEC-1891 */
/* Can.h with implied Can_Cfg.h is already included in file CanIf_Cfg.h */

#if !defined (CANIF_AVOID_VSTDLIB_COPY)
/* For VStdLib / CanIf.h/CanIf_Cfg.h has to be included before       */
/* possibility to explicitely avoid usage of VStdLib copy algorithm  */
# include "vstdlib.h"

/* Check if VStdlib is system                                        */
#  if defined (VSTD_HL_USE_VSTD_RAMMEMCPY) /* COV_CANIF_ONLY_VECTOR_VSTDLIB_USED */
/* Copy algorithm is available                                       */
#   define CANIF_USES_VSTDLIB_COPY      STD_ON
#  endif
#endif

#if !defined (CANIF_USES_VSTDLIB_COPY)
# define CANIF_USES_VSTDLIB_COPY      STD_OFF
#endif

#if (CANIF_TRCV_HANDLING == STD_ON)
# include "CanIf_CanTrcv.h"
#endif

/* \trace SPEC-3741, SPEC-1838 */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif


#include "SchM_CanIf.h"

#if (CANIF_BUS_MIRRORING_SUPPORT == STD_ON)
# include "Mirror_Cbk.h"
#endif

/* ECO_IGNORE_BLOCK_END */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
 
/* CanIf_Cbk.h version check */
#if (CANIF_CBK_MAJOR_VERSION != 0x05u)
# error "Vendor specific major version number of CanIf.c and CanIf_Cbk.h are inconsistent!"
#endif

#if (CANIF_CBK_MINOR_VERSION != 0x05u)
# error "Vendor specific minor version number of CanIf.c and CanIf_Cbk.h are inconsistent!"
#endif

#if (CANIF_CBK_PATCH_VERSION != 0x00u)
# error "Vendor specific patch version number of CanIf.c and CanIf_Cbk.h are inconsistent!"
#endif

/* CanIf_Types.h version check */
#if (CANIF_TYPES_MAJOR_VERSION != 0x06u)
# error "Vendor specific major version number of CanIf.c and CanIf_Types.h are inconsistent!"
#endif

#if (CANIF_TYPES_MINOR_VERSION != 0x17u)
# error "Vendor specific minor version number of CanIf.c and CanIf_Types.h are inconsistent!"
#endif

#if (CANIF_TYPES_PATCH_VERSION != 0x00u)
# error "Vendor specific patch version number of CanIf.c and CanIf_Types.h are inconsistent!"
#endif

/* CanIf.h version check */
#if (CANIF_API_MAJOR_VERSION != 0x06u)
# error "Vendor specific major version number of CanIf.c and CanIf.h are inconsistent!"
#endif

#if (CANIF_API_MINOR_VERSION != 0x19u)
# error "Vendor specific minor version number of CanIf.c and CanIf.h are inconsistent!"
#endif

#if (CANIF_API_PATCH_VERSION != 0x00u)
# error "Vendor specific patch version number of CanIf.c and CanIf.h are inconsistent!"
#endif

#if (CANIF_CPU_TYPE_SET_IN_ECUC_MODULE != CPU_TYPE)
# error "Invalid configuration! CPUType configured in EcuC-module differs from \"CPU_TYPE\" set in \"Platform_Types.h\"."
#endif

/* Check the compatibility version of generator */
# if (CANIF_CFG5_GENERATOR_COMPATIBILITY_VERSION != CANIF_GENDATA_COMPATIBILITY_VERSION)
#  error "Module CanIf: Source and Generated Header files are inconsistent! Please check the version of the generator."
# endif

/**********************************************************************************************************************
 *  COMPATIBILITY / DEFAULTS
 *********************************************************************************************************************/
 
/* ESCAN00084557 */
#if defined (CANIF_RX_PASS_STATIC_DLC)    /* COV_CANIF_FEATURE_DISCONTINUED */
# if (CANIF_RX_PASS_STATIC_DLC == STD_ON)
#  error "Feature CANIF_RX_PASS_STATIC_DLC is NOT supported by CAN interface anymore."
# endif
#endif

/* WakeUp Validation without WakeUp support not acceptable */
#if (CANIF_WAKEUP_VALIDATION == STD_ON)
# if (CANIF_WAKEUP_SUPPORT == STD_OFF)
#  error "Invalid configuration: Wake up validation (CANIF_WAKEUP_VALIDATION) is activated without activating wake up support (CANIF_WAKEUP_SUPPORT)"
# endif
#endif

#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
# if (CANIF_TRCV_MAPPING == STD_ON)
#  error "Invalid configuration: One channel optimization not possible with transceiver mapping"
# endif
#endif  

#if (CANIF_WAKEUP_VALIDATION == STD_OFF)
# if (CANIF_WAKEUP_VALID_ALL_RX_MSGS == STD_ON)
#  error "Invalid configuration"
# endif
#endif

#if (CANIF_PN_TRCV_HANDLING == STD_ON)
# if (CANIF_TRCV_HANDLING == STD_OFF)
#  error "Invalid configuration: Partial networking transceiver handling (CANIF_PN_TRCV_HANDLING) is enabled while transceiver handling is disabled (CANIF_TRCV_HANDLING)"
# endif
#endif /* (CANIF_PN_TRCV_HANDLING == STD_ON) */

#if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
#  error "Invalid configuration: One channel optimization not possible if multiple CAN drivers are used"
# endif
#endif

#if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
# if (CANIF_TRANSMIT_CANCELLATION == STD_ON)
# error "HW Tx-cancellation is NOT supported in combination with Tx-Buffer Type FIFO!"
# endif
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS / LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
 
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
/*! \def Define CANIF_PN_WU_FLAG_GET
 * Mask to check whether TxPduId is marked as PnWuTxPdu or not.
 */
# define CANIF_PN_WU_FLAG_GET                   0x80u

#endif /* (CANIF_PN_WU_TX_PDU_FILTER == STD_ON) */

/*! \def Define CANIF_WU_VALIDATION_NM_FLAG_GET
 * Mask to check whether RxPduId is a network message. This information is
 * necessary for WakeupValdation
 */
#define CANIF_WU_VALIDATION_NM_FLAG_GET         0x80u
#define CANIF_WU_VALIDATION_NM_MASK_OUT         0x7Fu

#if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
/* coded in CANIF_CFG_RX_CANID */
# define CANIF_MASKCODE_RANGE   0x20000000u /* changed due to ESCAN00075241 */
# define CANIF_FDFLAG           0x40000000u
/* coded in CANIF_CFG_RX_MASK */
# define CANIF_STOP_FLAG        0x40000000u
# define CANIF_RANGE_FLAG       0x20000000u
#else
/* coded in CANIF_CFG_RX_CANID */
# define CANIF_MASKCODE_RANGE   0x2000u /* changed due to ESCAN00075241 */
# define CANIF_FDFLAG           0x4000u
/* coded in CANIF_CFG_RX_MASK */
# define CANIF_STOP_FLAG        0x4000u
# define CANIF_RANGE_FLAG       0x2000u
#endif


/* J1939 specific constants
 *  DA == Destination Address
 *  SA == Source Address
 *  INV == inverted
 *  ADDR == address
 *  RQST == request
 *  PGN == Parameter Group Number
 *  PDU1 -> 4.BYTE == SA, 3.BYTE == DA, possible values: 0..EF
 *  PDU2 -> 4.BYTE == SA, 3.BYTE == part of PGN
 *  */
#define CANIF_J1939_NULL_ADDR                 0xFEu
#define CANIF_J1939_BROADCAST_ADDR            0xFFu
#define CANIF_J1939_DATA_PAGE_MASK            0x03000000u
#define CANIF_J1939_PGN_MASK                  0x03FF0000u
#define CANIF_J1939_AC_PGN                    0x00EE0000u
#define CANIF_J1939_MIN_PDU2_MASK             0x00F00000u
#define CANIF_J1939_DA_MASK                   0x0000FF00u
#define CANIF_J1939_INV_DA_MASK               0xFFFF00FFu
#define CANIF_J1939_SA_MASK                   0x000000FFu
#define CANIF_J1939_INV_SA_MASK               0xFFFFFF00u
#define CANIF_J1939_RQST_PGN                  0x00EA0000u
#define CANIF_J1939_ACKM_ACKADDR_POS          4u
#define CANIF_J1939_ACKM_PGN                  0x00E80000u





/* ParameterList: uint8 Hrh, PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc, Can_IdType CanId */
#if ((CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON) || (CANIF_META_DATA_RX_SUPPORT == STD_ON) || (CANIF_RX_INDICATION_TYPE_IV_IS_USED == STD_ON))
# define CanIf_Indirect_HlIndication(hrh, pduid, cansduptr, candlc, canid)     CanIf_HlIndication((hrh), (pduid), (cansduptr), (candlc), (canid)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#else
# define CanIf_Indirect_HlIndication(hrh, pduid, cansduptr, candlc, canid)     CanIf_HlIndication((hrh), (pduid), (cansduptr), (candlc)) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif


/* generated types */

#define CanIf_ControllerType                               CanIf_CtrlStatesIdxOfTxPduConfigType
#define CanIf_RxIndFctListIdxType                          CanIf_RxIndicationFctListIdxOfRxPduConfigType
#define CanIf_TxConfFctListIdxType                         CanIf_TxConfirmationFctListIdxOfTxPduConfigType
#define CanIf_TxPduQueueType                               CanIf_TxPduQueueIndexStartIdxOfControllerConfigType
#define CanIf_CanTrcvFctTblIdx                             CanIf_CanTrcvFctTblIdxOfTransceiverUpToLowMapType


#define  CanIf_AnyIdxType uint32_least


/* \trace SPEC-5228 */
#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
# define CANIF_CHANNEL_CANTYPE_FIRST
# define CANIF_CHANNEL_CANTYPE_ONLY                   void
# define CANIF_CHANNEL_CANPARA_ONLY
# define CANIF_CHANNEL_CANPARA_FIRST
# define CANIF_CHANNEL_CANPARA_FIRST_LOCAL
# define CanIf_Controller_Value                       0u
# define CANIF_CHANNEL_CANTYPE_LOCAL
# define CANIF_WUCHANNEL_CANTYPE_LOCAL
# define CanIf_Controller_Value_Local                 0u
# define CanIf_WU_Controller_Value_Local              0u
# define CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE     CanIf_GetMaxTrcvHandleIdPlusOne()
#else
# define CANIF_CHANNEL_CANTYPE_FIRST                  CanIf_ControllerType ControllerId,
# define CANIF_CHANNEL_CANTYPE_ONLY                   CanIf_ControllerType ControllerId
# define CANIF_CHANNEL_CANPARA_ONLY                   ControllerId
# define CANIF_CHANNEL_CANPARA_FIRST                  ControllerId,
# define CANIF_CHANNEL_CANPARA_FIRST_LOCAL            controller,
# define CanIf_Controller_Value                       ControllerId
# define CANIF_CHANNEL_CANTYPE_LOCAL                  CanIf_ControllerType controller;
# define CANIF_WUCHANNEL_CANTYPE_LOCAL                CanIf_ControllerType wuController;
# define CanIf_Controller_Value_Local                 controller
# define CanIf_WU_Controller_Value_Local              wuController
# define CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE     CanIf_GetMaxTrcvHandleIdPlusOne()
#endif

# define CANIF_CFG_MAX_CONTROLLER                     CanIf_GetSizeOfCtrlStates()
# define CANIF_CFG_TX_CONTROLLER(index)               CanIf_GetCtrlStatesIdxOfTxPduConfig(index) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/* MAX valid TransceiverId with which the transceiver indication functions may be called */
#if (CANIF_TRCV_MAPPING == STD_ON)
# define CANIF_CFG_MAX_CANTRCV_TRCVHANDLEIDPLUSONE    CanIf_GetSizeOfTransceiverUpToUpperMap()
#else
# define CANIF_CFG_MAX_CANTRCV_TRCVHANDLEIDPLUSONE    CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE
#endif

#if (CANIF_TRCV_HANDLING == STD_ON)
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
#  define CanIf_TrcvIdUpper                     0u
# else
#  define CanIf_TrcvIdUpper                     TransceiverId
# endif
#endif

#define CANIF_CFG_GENERATORCOMPATIBILITYVERSION            CanIf_GetGeneratorCompatibilityVersion()
#define CANIF_CFG_MAGICNUMBER                              CanIf_GetFinalMagicNumber()

#define CANIF_CFG_MAX_MAILBOXES                            CanIf_GetSizeOfMailBoxConfig()
#define CANIF_CFG_MAX_TXPDUS                               CanIf_GetSizeOfTxPduConfig()
#define CANIF_CFG_MAX_ULTXPDUS                             CanIf_GetSizeOfUlTxPduId2InternalTxPduId()
                                                           
#define CANIF_CFG_MAX_TXCONFIRMATIONS                      CanIf_GetSizeOfTxConfirmationFctList()
#define CANIF_CFG_MAX_RXPDUS                               CanIf_GetSizeOfRxPduConfig()
#define CANIF_CFG_MAX_ULRXPDUS                             CanIf_GetSizeOfUlRxPduId2InternalRxPduId()

#define CANIF_CFG_MAX_RXINDICATIONS                        CanIf_GetSizeOfRxIndicationFctList()
#define CANIF_CFG_MAX_WAKEUPSOURCES                        CanIf_GetMaxWakeUpSources()

/* PRQA S 3453 CANIF_FUNCTION_LIKE_MACRO */ /* MD_MSR_FctLikeMacro */

/* USAGE: Only if  CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON */
/* IN: Index get by CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX() */
/* OUT: CanIf-internal hxh-offset in order to be able to calculate the CanDrv specific hxh-index. For calculation just
   subtract the offset from the CanIf specific one which e.g. retrieved via CANIF_CFG_TX_HTH(). */
#define CANIF_CFG_MULTIPLECANDRV_HXHOFFSET(index)          CanIf_GetHxhOffset(index)

/* Access to table: CanIf_CanIfCtrlId2MappedTxBuffersConfig */
/* IN: CanIf-internal CAN channel handle ID */
/* OUT: Start-index for corresponding CAN channel into table CanIf_MappedTxBuffersConfig */
#define CANIF_CFG_CTRL_STARTIDX2MAPPEDTXBUFFERS(index)     CanIf_GetMappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfig(index)
/* IN: CanIf-internal CAN channel handle ID */
/* OUT: Stop-index for corresponding CAN channel into table CanIf_MappedTxBuffersConfig */
#define CANIF_CFG_CTRL_STOPIDX2MAPPEDTXBUFFERS(index)      CanIf_GetMappedTxBuffersConfigEndIdxOfCanIfCtrlId2MappedTxBuffersConfig(index)

/* Access to table: CanIf_MappedTxBuffersConfig */
/* IN: Index retrieved via macros: CANIF_CFG_CTRL_STARTIDX2MAPPEDTXBUFFERS / CANIF_CFG_CTRL_STOPIDX2MAPPEDTXBUFFERS */
/* OUT: Index into table CanIf_MailboxConfig */
#define CANIF_CFG_MAPPEDTXBUFFERS(index)                   CanIf_GetMailBoxConfigIdxOfMappedTxBuffersConfig(index)

/* TRUE: CAN driver index valid, FALSE CAN driver index NOT valid
 * Only relevant in PBS-configurations! FALSE only makes sense in PBS-configurations, where a CAN driver may be disabled in an identity.
 * Only if this one returns TRUE any CAN driver function may be read from table "CanIf_CanDrvFctTbl" */
#define CANIF_CFG_IS_CANDRVINDEXVALID(index)               CanIf_IsCanDrvFctTblUsedOfCanChannelIdUpToLowMap(index)  /* Input: CanIfChannel, Output: TRUE / FALSE */
#define CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(index)        CanIf_GetCanDrvFctTblIdxOfCanChannelIdUpToLowMap(index)  /* Input: CanIfChannel, Output: CanDriverIndex  */

/* J1939(Nm) configuration */
#define CANIF_CFG_CTRLJ1939DYNADDRSUPPORT(index)           CanIf_GetJ1939DynAddrSupportOfCtrlConfig(index)
/* NOTE: The value returned from following table may only be used if the CAN channel (== index) was verified with following condition
 * "CANIF_CFG_CTRLJ1939DYNADDRSUPPORT(index) != CANIF_J1939_DYN_ADDR_DISABLED"
 * ONLY if this condition is TRUE the value returned from following table may be used! */
#define CANIF_CFG_CTRLID2J1939DYNADDROFFSET(index)         CanIf_GetJ1939DynAddrOffsetOfCtrlConfig(index)


#if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
# define CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(index)      CanIf_GetChannelIndexOfCanChannelIdUpToLowMap(index) /* Input:CanIfChannel Output:CanChannelIndex */
# define CANIF_GET_CANSETCTRLMODEFCT(index)                CanIf_GetSetControllerModeFctOfCanDrvFctTbl(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(index))
#else
# define CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(index)      (index)
# define canSetCtrlModeFct                                 Can_SetControllerMode
#endif

 
#if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
# define CANIF_GET_CANCANCELTXFCT(index)                   CanIf_GetCancelTxFctOfCanDrvFctTbl(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(index))
#else
# define canCancelTxFct                                    Can_CancelTx
#endif

#define CANIF_CFG_RX_RXINDICATION(index)                   CanIf_GetRxIndicationFctListIdxOfRxPduConfig(index)
#define CANIF_CFG_RX_DLC(index)                            CanIf_GetDlcOfRxPduConfig(index)
#define CANIF_CFG_RX_UPPERPDUID(index)                     CanIf_GetUpperPduIdOfRxPduConfig(index)
#define CANIF_CFG_RX_MASK(index)                           CanIf_GetRxPduMaskOfRxPduConfig(index)
#define CANIF_CFG_RX_CANID(index)                          CanIf_GetRxPduCanIdOfRxPduConfig(index)
#define CANIF_CFG_RX_RXMETADATALENGTH(index)               CanIf_GetRxMetaDataLengthOfRxPduConfig(index)
#define CANIF_CFG_RX_MSGTYPE(index)                        CanIf_GetMsgTypeOfRxPduConfig(index)
#define CANIF_CFG_RX_MAXVALIDRXDLC                         CanIf_GetMaxValidRxDlc()
/* IN: Internal CanIfRxPduId to access table CanIf_RxPduConfig[] */
/* OUT: TRUE: data checksum Rx-PDU, FALSE: None data checksum Rx-PDU */
#define CANIF_CFG_RX_ISDATACHECKSUMPDU(index)              CanIf_IsIsDataChecksumRxPduOfRxPduConfig(index)
/* IN: Internal CanIfRxPduId to access table CanIf_RxPduConfig[] */
/* OUT: TRUE:  ReceptionMode  Rx-PDU, FALSE: None ReceptionMode  Rx-PDU */
#define CANIF_CFG_RX_ISRECEPTIONMODEPDU(index)             CanIf_IsPduRxModeUsedOfRxPduConfig(index)
/* IN: Internal CanIfRxPduId to access table CanIf_RxPduConfig[] */
/* OUT: Index to access the array CanIf_PduReceptionMode[] */
#define CANIF_CFG_RX_PDURECEPTIONMODEIDX(Index)            CanIf_GetPduRxModeIdxOfRxPduConfig(Index)
/* IN: External CanIfRxPduId */
/* OUT: Internal CanIfRxPduId */
#define CANIF_CFG_EXTRXPDUID2INTRXPDUID(index)             CanIf_GetRxPduConfigIdxOfUlRxPduId2InternalRxPduId(index)
/* IN: Internal CanIfRxPduId */
/* OUT: External CanIfRxPduId */
#define CANIF_CFG_INTRXPDUID2EXTRXPDUID(index)             CanIf_GetCanIfRxPduIdOfRxPduConfig(index)


/* Read/write-access to variable CanIf_PduReceptionMode[] */
#define CANIF_VAR_SET_PDU_RECEPTION_MODE(Index, Value)     CanIf_SetPduRxMode(Index, Value)
#define CANIF_VAR_GET_PDU_RECEPTION_MODE(Index)            CanIf_GetPduRxMode(Index)

/* NOTE: Please see description of "CANIF_CFG_CTRLID2J1939DYNADDROFFSET" before usage! */
#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
# define CANIF_VAR_J1939RXADDR_LOOKUP(ch, addr)            CanIf_GetJ1939RxAddr_Lookup(addr)
# define CANIF_VAR_SET_J1939RXADDR_LOOKUP(ch, addr, value) CanIf_SetJ1939RxAddr_Lookup((addr), (value))
#else
# define CANIF_VAR_J1939RXADDR_LOOKUP(ch, addr)            CanIf_GetJ1939RxAddr_Lookup(CANIF_CFG_CTRLID2J1939DYNADDROFFSET(ch) + (addr))
# define CANIF_VAR_SET_J1939RXADDR_LOOKUP(ch, addr, value) CanIf_SetJ1939RxAddr_Lookup((CANIF_CFG_CTRLID2J1939DYNADDROFFSET(ch) + (addr)), (value))
#endif

/* Access to table: CanIf_TxPduConfig */
#define CANIF_CFG_TX_CANID(index)                          CanIf_GetCanIdOfTxPduConfig(index)
#define CANIF_CFG_TX_HTH(index)                            CanIf_GetMailBoxConfigIdxOfTxPduConfig(index)
#define CANIF_CFG_TX_TXCONFIRMATION(index)                 CanIf_GetTxConfirmationFctListIdxOfTxPduConfig(index)
#define CANIF_CFG_TX_UPPERLAYERTXPDUID(index)              CanIf_GetUpperLayerTxPduIdOfTxPduConfig(index)
#define CANIF_CFG_TX_TXMETADATALENGTH(index)               CanIf_GetTxMetaDataLengthOfTxPduConfig(index)
#define CANIF_CFG_TX_DLC(index)                            CanIf_GetDlcOfTxPduConfig(index)
#define CANIF_CFG_TX_CANIDTXMASK(index)                    CanIf_GetCanIdTxMaskOfTxPduConfig(index)
/* IN: Internal CanIfTxPduId to access table: CanIf_TxPduConfig[] */
/* OUT: TRUE: data checksum Tx-PDU, FALSE: None data checksum Tx-PDU */
#define CANIF_CFG_TX_ISDATACHECKSUMPDU(index)              CanIf_IsIsDataChecksumTxPduOfTxPduConfig(index)

#define CANIF_CFG_TXPDUID2INTTXPDUID(index)                CanIf_GetUlTxPduId2InternalTxPduId(index)
#define CANIF_CFG_TX_QUEUEINDEX(index)                     CanIf_GetTxQueueIdxOfTxPduQueueIndex(index)

/* Access to table: CanIf_TxBufferFifoConfig */
/* IN: Index get by CANIF_CFG_MAILBOX_TXBUFFERIDX() in case of CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE() == FIFO. This applies for all CANIF_CFG_TXBUFFERFIFO_* access-macros. */
/* OUT: Access-index into variable CanIf_TxBufferFifoBase[] */
#define CANIF_CFG_TXBUFFERFIFO_BUFFERBASEIDX(index)        CanIf_GetTxBufferFifoBaseIdxOfTxBufferFifoConfig(index)
/* OUT: Access-start-index into variable CanIf_TxFifoQueueBase[] */
#define CANIF_CFG_TXBUFFERFIFO_QUEUEBASESTARTIDX(index)    CanIf_GetTxFifoQueueBaseStartIdxOfTxBufferFifoConfig(index)
#define CANIF_CFG_TXBUFFERFIFO_QUEUEBASEENDIDX(index)      CanIf_GetTxFifoQueueBaseEndIdxOfTxBufferFifoConfig(index)
/* OUT: Access-start-index into variable CanIf_TxFifoQueueData[] */
#define CANIF_CFG_TXBUFFFERFIFO_QUEUEDATASTARTIDX(index)   CanIf_GetTxFifoQueueDataStartIdxOfTxBufferFifoConfig(index)
/* OUT: Size of FIFO (== how many Tx-PDUs may be stored at all) */
#define CANIF_CFG_TXBUFFERFIFO_QUEUESIZE(index)            CanIf_GetTxFifoQueueBaseLengthOfTxBufferFifoConfig(index)
/* OUT: Size of one FIFO payload element [bytes] (== how many data bytes can be stored within one FIFO-queue-element) */
#define CANIF_CFG_TXBUFFERFIFO_SIZEOFONEPAYLOADEL(index)   CanIf_GetSizeOfOnePayloadElOfTxBufferFifoConfig(index)

/* Read-access to variable CanIf_TxBufferFifoBase[] */
/* Possible values for field: eWriteIdx, eReadIdx, eQueueCounter */
#define CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(index, field)    CanIf_GetTxBufferFifoBase(index).field
/* Read-access to variable CanIf_TxFifoQueueBase[] */
/* Possible values for field: eQueued, eBaseParams (includes: eCanId, eSduLength) */
#define CANIF_VAR_TXBUFFERFIFO_QUEUEBASE(index, field)     CanIf_GetTxFifoQueueBase(index).field
/* Read/write/address-access to variable CanIf_TxFifoQueueData[] */
#define CANIF_VAR_TXBUFFERFIFO_QUEUEDATA(index)            CanIf_GetTxFifoQueueData(index)
#define CANIF_VAR_SET_TXBUFFERFIFO_QUEUEDATA(index)        CanIf_SetTxFifoQueueData(index)
#define CANIF_ADDR_VAR_TXBUFFERFIFO_QUEUEDATA(index)       CanIf_GetAddrTxFifoQueueData(index)
/* Read/write/address-access to variable CanIf_TxQueueIndex2FifoEl[] */
#define CANIF_VAR_TXBUFFERFIFO_QUEUEIDX2FIFOEL(index)      CanIf_GetTxQueueIndex2FifoEl(index)
#define CANIF_VAR_SET_TXBUFFERFIFO_QUEUEIDX2FIFOEL(index, value)  CanIf_SetTxQueueIndex2FifoEl(index, value)
/* Get size of buffer size */
#define CANIF_CFG_SIZEOF_FIFO_BUFFER                       CanIf_GetSizeOfTxFifoQueueData()

/* Access to table: CanIf_TxBufferPrioByCanIdByteQueueConfig */
/* IN: Index get by CANIF_CFG_MAILBOX_TXBUFFERIDX() in case of CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE() == PRIO_BY_CANID and CANIF_BITQUEUE == STD_OFF.
 * This applies for all CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_* access-macros. */
/* OUT: Access-index into variable CanIf_TxBufferPrioByCanIdBase: QueueCounter */


#define CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_BUFFERBASEIDX(index)            CanIf_GetTxBufferPrioByCanIdBaseIdxOfTxBufferPrioByCanIdByteQueueConfig(index)
/* OUT: Size of buffer (== how many Tx-PDUs may be stored at all) */
#define CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_QUEUESIZE(index)                CanIf_GetTxBufferPrioByCanIdByteQueueMappedTxPdusLengthOfTxBufferPrioByCanIdByteQueueConfig(index)
/* OUT: Start-index into table CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus with Tx-PDUs mapped to Tx-buffer (CanIf-internal Tx-PDU-Ids for access into CanIf_TxPduConfig[]) */
#define CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_STARTIDX2MAPPEDTXPDUS(index)    CanIf_GetTxBufferPrioByCanIdByteQueueMappedTxPdusStartIdxOfTxBufferPrioByCanIdByteQueueConfig(index)
/* OUT: Stop-index into table CanIf_TxBufferPrioByCanIdByteQueueMappedTxPdus with Tx-PDUs mapped to Tx-buffer (CanIf-internal Tx-PDU-Ids for access into CanIf_TxPduConfig[]) */
#define CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_STOPIDX2MAPPEDTXPDUS(index)     CanIf_GetTxBufferPrioByCanIdByteQueueMappedTxPdusEndIdxOfTxBufferPrioByCanIdByteQueueConfig(index)
/* OUT: Index into table CanIf_TxPduConfig. */
#define CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_MAPPEDTXPDUS(index)             CanIf_GetTxPduConfigIdxOfTxBufferPrioByCanIdByteQueueMappedTxPdus(index)

/* IN: Index get by CANIF_CFG_MAILBOX_TXBUFFERIDX() in case of CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE() == PRIO_BY_CANID and CANIF_BITQUEUE == STD_ON/STD_OFF.
 * This applies for all CANIF_CFG_TXBUFFERPRIOBYCANID_* access-macros. */
/* Read-access to variable CanIf_TxBufferPrioByCanIdBase[] */
/* Possible values for field: eQueueCounter */
#define CANIF_VAR_TXBUFFERPRIOBYCANID_BUFFERBASE(index, field)                 CanIf_GetTxBufferPrioByCanIdBase(index).field

/* Access to table: CanIf_TxBufferPrioByCanIdBitQueueConfig */
/* IN: Index get by CANIF_CFG_MAILBOX_TXBUFFERIDX() in case of CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE() == PRIO_BY_CANID and CANIF_BITQUEUE == STD_ON.
 * This applies for all CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_* access-macros. */
/* OUT: Access-index into variable CanIf_TxBufferPrioByCanIdBase: QueueCounter. */
#define CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_BUFFERBASEIDX(index)             CanIf_GetTxBufferPrioByCanIdBaseIdxOfTxBufferPrioByCanIdBitQueueConfig(index)
/* OUT: Start-index into variable: CanIf_TxQueueFlags */
#define CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUESTARTIDX(index)             CanIf_GetTxQueueFlagsStartIdxOfTxBufferPrioByCanIdBitQueueConfig(index)
#define CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUESTOPIDX(index)              CanIf_GetTxQueueFlagsEndIdxOfTxBufferPrioByCanIdBitQueueConfig(index)
#define CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_BITPOS2TXPDUIDOFFSET(index)      CanIf_GetBitPos2TxPduIdOffsetOfTxBufferPrioByCanIdBitQueueConfig(index)


/* NOTE: Please see description of "CANIF_CFG_CTRLID2J1939DYNADDROFFSET" before usage! */
#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
# define CANIF_VAR_J1939TXADDR_LOOKUP(ch, addr)            CanIf_GetJ1939TxAddr_Lookup(addr)
# define CANIF_VAR_SET_J1939TXADDR_LOOKUP(ch, addr, value) CanIf_SetJ1939TxAddr_Lookup((addr), (value))
#else
# define CANIF_VAR_J1939TXADDR_LOOKUP(ch, addr)            CanIf_GetJ1939TxAddr_Lookup(CANIF_CFG_CTRLID2J1939DYNADDROFFSET(ch) + (addr))
# define CANIF_VAR_SET_J1939TXADDR_LOOKUP(ch, addr, value) CanIf_SetJ1939TxAddr_Lookup((CANIF_CFG_CTRLID2J1939DYNADDROFFSET(ch) + (addr)), (value))
#endif

/* Access to table: CanIf_MailboxConfig  */
#define CANIF_CFG_MAILBOX_PDUIDFIRST(index)                CanIf_GetPduIdFirstOfMailBoxConfig(index)
#define CANIF_CFG_MAILBOX_PDUIDLAST(index)                 CanIf_GetPduIdLastOfMailBoxConfig(index)
#define CANIF_CFG_MAILBOX_MAILBOXTYPE(index)               CanIf_GetMailBoxTypeOfMailBoxConfig(index)
#define CANIF_CFG_MAILBOX_CONTROLLER(index)                CanIf_GetCtrlStatesIdxOfMailBoxConfig(index)
#define CANIF_CFG_MAILBOX_TXBUFFERIDX(index)               CanIf_GetTxBufferCfgIdxOfMailBoxConfig(index)
#define CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(index)      CanIf_GetTxBufferHandlingTypeOfMailBoxConfig(index)
#define CANIF_CFG_MAILBOX_HASTXBUFFER(index)               CanIf_IsTxBufferCfgUsedOfMailBoxConfig(index)

#define CANIF_CFG_WAKEUP_WAKEUPSOURCE(index)               CanIf_GetWakeUpSourceOfWakeUpConfig(index)
#define CANIF_CFG_WAKEUP_WAKEUPTARGETMODULE(index)         CanIf_GetWakeUpTargetModuleOfWakeUpConfig(index)
#define CANIF_CFG_WAKEUP_WAKEUPTARGETADDRESS(index)        CanIf_GetWakeUpTargetAddressOfWakeUpConfig(index)
#define CANIF_CFG_WAKEUP_CONTROLLER(index)                 CanIf_GetControllerOfWakeUpConfig(index)

#define CANIF_CFG_TRCVUPTOLOWMAP_DRIVERINDEX(index)        CanIf_GetCanTrcvFctTblIdxOfTransceiverUpToLowMap(index)
#define CANIF_CFG_TRCVUPTOLOWMAP_CHANNELINDEX(index)       CanIf_GetChannelIndexOfTransceiverUpToLowMap(index)

#define CanIf_GetCanTrcv_SetOpModeFctMap(index)            CanIf_GetSetOpModeFctOfCanTrcvFctTbl(index)
#define CanIf_GetCanTrcv_GetOpModeFctMap(index)            CanIf_GetGetOpModeFctOfCanTrcvFctTbl(index)
#define CanIf_GetCanTrcv_GetBusWuReasonFctMap(index)       CanIf_GetGetBusWuReasonFctOfCanTrcvFctTbl(index)
#define CanIf_GetCanTrcv_SetWakeupModeFctMap(index)        CanIf_GetSetWakeupModeFctOfCanTrcvFctTbl(index)
#define CanIf_GetCanTrcv_CheckWakeupFctMap(index)          CanIf_GetCheckWakeupFctOfCanTrcvFctTbl(index)

#define CanIf_GetCanTrcv_ClearTrcvWufFlagFctMap(index)     CanIf_GetClearTrcvWufFlagFctOfCanTrcvFctTbl(index)
#define CanIf_GetCanTrcv_CheckWakeFlagFctMap(index)        CanIf_GetCheckWakeFlagFctOfCanTrcvFctTbl(index)


#define CANIF_CFG_RXDHRANDOMNUMBER1(index)                 CanIf_GetRxDHRandomNumber1OfCtrlConfig(index)
#define CANIF_CFG_RXDHRANDOMNUMBER2(index)                 CanIf_GetRxDHRandomNumber2OfCtrlConfig(index)

#define CANIF_CFG_RXDHADJUST(index)                        CanIf_GetRxDHAdjust(index)
#define CANIF_CFG_RXDHADJUSTCOUNT                          CanIf_GetSizeOfRxDHAdjust()

#define CANIF_CFG_STAT2DYN_INDIRECTION(index)                                       CanIf_GetTxPduStatic2DynamicIndirection(index)
#define CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_QUEUEIDX2DATASTARTSTOP(index)     CanIf_GetTxQueueIndex2DataStartStopIdxOfTxPduQueueIndex(index)
/* Access to table: CanIf_TxQueueIndex2DataStartStop in order to redirect into variable CanIf_TxQueueData in case of static FD-queue */
#define CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_DATASTARTIDX(index)               CanIf_GetTxQueueDataStartIdxOfTxQueueIndex2DataStartStop(CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_QUEUEIDX2DATASTARTSTOP(index))
#define CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_MAXDATALENGTH(index)              CanIf_GetTxQueueDataLengthOfTxQueueIndex2DataStartStop(CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_QUEUEIDX2DATASTARTSTOP(index))

#define CANIF_CFG_ISFEATUREPNWUTXPDUFILTERENABLED(index)   CanIf_IsFeaturePnWuTxPduFilterEnabledOfCtrlConfig(index)
#define CANIF_CFG_TRCVTOCTRLMAP(index)                     CanIf_GetTrcvToCtrlMap(index)
#define CANIF_CFG_TRCVUPTOUPPERMAP(index)                  CanIf_GetTransceiverUpToUpperMap(index)

/* Access to variable: CanIf_TxQueue */
/* Possible values for field: eQueued, eQueueParams (Includes: eSdu[], eBaseParams (Includes: eCanId, eSduLength))  */
#define CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(index, field)                      CanIf_GetTxQueue(index).field
/* Access to variable: CanIf_TxQueueData (static FD-queue) */
#define CANIF_VAR_TXBUFFERPRIOBYCANID_STATFDQUEUE_QUEUEDATA(index)             CanIf_GetTxQueueData(index)
#define CANIF_ADDR_VAR_TXBUFFERPRIOBYCANID_STATFDQUEUE_QUEUEDATA(index)        CanIf_GetAddrTxQueueData(index)
/* Access to variable: CanIf_TxQueueFlags */
#define CANIF_VAR_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUEFLAGS(index)                CanIf_GetTxQueueFlags(index)
#define CANIF_VAR_SET_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUEFLAGS(index, value)     CanIf_SetTxQueueFlags((index), (value))
/* Access to variable: CanIf_DynTxId */
#define CANIF_VAR_DYNTXID(index)                                               CanIf_GetDynTxId(index)

#define CANIF_CFG_RXINDICATION_FUNCTION(index)             CanIf_GetRxIndicationFctOfRxIndicationFctList(index)
#define CANIF_CFG_RXINDICATION_FUNCTIONLAYOUT(index)       CanIf_GetRxIndicationLayoutOfRxIndicationFctList(index)
#define CANIF_CFG_TXCONFIRMATION(index)                    CanIf_GetTxConfirmationFctList(index)

#define CANIF_CFG_BUSOFFNOTIFICATION()                     CanIf_GetBusOffNotificationFctPtr()
#define CANIF_CFG_WAKEUPVALIDATION()                       CanIf_GetWakeUpValidationFctPtr()
#define CANIF_CFG_CTRLMODEINDICATIONFCT()                  CanIf_GetCtrlModeIndicationFctPtr()

/* FEAT-598: (Extended) RAM-check indications */
#define CANIF_CFG_RAMCHECKCORRUPTMAILBOXINDFCT()           CanIf_GetRamCheckCorruptMailboxIndFctPtr()
#define CANIF_CFG_RAMCHECKCORRUPTCONTROLLERINDFCT()        CanIf_GetRamCheckCorruptControllerIndFctPtr()


#define CANIF_CFG_TRCVMODEINDICATIONFCT()                  CanIf_GetTrcvModeIndicationFctPtr()
#define CANIF_CFG_CHECKTRCVWAKEFLAGINDICATIONFCT()         CanIf_GetCheckTrcvWakeFlagIndicationFctPtr()
#define CANIF_CFG_CLEARTRCVWUFFLAGINDICATIONFCT()          CanIf_GetClearTrcvWufFlagIndicationFctPtr()
#define CANIF_CFG_CONFIRMPNAVAILABILITYFCT()               CanIf_GetConfirmPnAvailabilityFctPtr()


#define CanIf_SetCtrlMode(index, value)                    CanIf_SetCtrlModeOfCtrlStates((index), (value))
#define CanIf_GetCtrlMode(index)                           CanIf_GetCtrlModeOfCtrlStates(index)

#define CanIf_SetChannelMode(index, value)                 CanIf_SetPduModeOfCtrlStates((index), (value))
#define CanIf_GetChannelMode(index)                        CanIf_GetPduModeOfCtrlStates(index)

#define CanIf_SetPnWuTxPduFilterActive(index, value)       CanIf_SetPnWuTxPduFilterActiveOfCtrlStates((index), (value))
#define CanIf_IsPnWuTxPduFilterActive(index)               CanIf_IsPnWuTxPduFilterActiveOfCtrlStates(index)

#define CanIf_SetTxConfState(index, value)                 CanIf_SetTxConfStateOfCtrlStates((index), (value))
#define CanIf_GetTxConfState(index)                        CanIf_GetTxConfStateOfCtrlStates(index)

#define CanIf_SetWakeUpValidationState(index, value)       CanIf_SetWakeUpValidationStateOfCtrlStates((index), (value))
#define CanIf_GetWakeUpValidationState(index)              CanIf_GetWakeUpValidationStateOfCtrlStates(index)

#define CanIf_ChangeMirroring(index, value)                CanIf_SetBusMirroringActiveOfCtrlStates((index), (value))
#define CanIf_IsMirroringEnabled(index)                    CanIf_IsBusMirroringActiveOfCtrlStates(index)

/* FEAT-1429 */
#define CanIf_SetTxQueueCounter(index, value)              (CanIf_GetTxBufferPrioByCanIdBase(index).eQueueCounter = (value))
#define CanIf_GetTxQueueCounter(index)                     (CanIf_GetTxBufferPrioByCanIdBase(index).eQueueCounter)
#define CanIf_IncTxQueueCounter(index)                     (++CanIf_GetTxBufferPrioByCanIdBase(index).eQueueCounter)
#define CanIf_DecTxQueueCounter(index)                     (--CanIf_GetTxBufferPrioByCanIdBase(index).eQueueCounter)


#define CanIf_GetCan_WriteFctMap(index)                    CanIf_GetWriteFctOfCanDrvFctTbl(index)
#define CanIf_GetCan_CheckWakeupFctMap(index)              CanIf_GetCheckWakeupFctOfCanDrvFctTbl(index)
#define CanIf_GetCan_CheckBaudrateFctMap(index)            CanIf_GetCheckBaudrateFctOfCanDrvFctTbl(index)
#define CanIf_GetCan_ChangeBaudrateFctMap(index)           CanIf_GetChangeBaudrateFctOfCanDrvFctTbl(index)
#define CanIf_GetCan_SetBaudrateFctMap(index)              CanIf_GetSetBaudrateFctOfCanDrvFctTbl(index)
/* FEAT-598: (Extended) RAM-check APIs (only Multiple CanDrv) */
#define CanIf_GetCan_RamCheckExecuteFctMap(index)          CanIf_GetRamCheckExecuteFctOfCanDrvFctTbl(index)
#define CanIf_GetCan_RamCheckEnableMailboxFctMap(index)    CanIf_GetRamCheckEnableMailboxFctOfCanDrvFctTbl(index)
#define CanIf_GetCan_RamCheckEnableControllerFctMap(index) CanIf_GetRamCheckEnableControllerFctOfCanDrvFctTbl(index)

#define CanIf_GetCan_GetControllerErrorStateFctMap(index)      CanIf_GetGetControllerErrorStateFctOfCanDrvFctTbl(index)      
#define CanIf_GetCan_GetControllerRxErrorCounterFctMap(index)  CanIf_GetGetControllerRxErrorCounterOfCanDrvFctTbl(index)     
#define CanIf_GetCan_GetControllerTxErrorCounterFctMap(index)  CanIf_GetGetControllerTxErrorCounterOfCanDrvFctTbl(index) 

/* PRQA L: CANIF_FUNCTION_LIKE_MACRO */

#define CanIf_EnterCritical(area)     SchM_Enter_CanIf_##area()  /* PRQA S 0342 */ /*  MD_MSR_Rule20.10_0342 */
#define CanIf_LeaveCritical(area)     SchM_Exit_CanIf_##area()   /* PRQA S 0342 */ /*  MD_MSR_Rule20.10_0342 */

#define CANIF_NOP      ((uint8)0xFFu)

#if (CANIF_BITQUEUE == STD_ON)
# if ( CPU_TYPE == CPU_TYPE_8 ) /* COV_CANIF_UNSUPPORTED */
#  define kCanTxQueueShift     3u
#  define elemStartBitIdx      7u
# elif ( CPU_TYPE == CPU_TYPE_16 ) /* COV_CANIF_UNSUPPORTED */
#  define kCanTxQueueShift     4u
#  define elemStartBitIdx      15u
# else /* CPU_TYPE_32 || CPU_TYPE_64 */
#  define kCanTxQueueShift     5u
#  define elemStartBitIdx      31u
# endif



/* mask used to get the flag index from the handle */
# define kCanTxQueueMask      (((uint8)1u << kCanTxQueueShift) - (uint8)1u)
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
 
#define CANIF_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

CONST(uint8, CANIF_CONST) CanIf_MainVersion         = (uint8)CANIF_SW_MAJOR_VERSION;
CONST(uint8, CANIF_CONST) CanIf_SubVersion          = (uint8)CANIF_SW_MINOR_VERSION;
CONST(uint8, CANIF_CONST) CanIf_ReleaseVersion      = (uint8)CANIF_SW_PATCH_VERSION;

#define CANIF_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define CANIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
/***********************************************************************************************************************
 *  CanIf_TxQueueTreatment()
 **********************************************************************************************************************/
/*! \brief       Checks if queued PDUs have to be transmitted.
 *  \details     Called out of CanIf_TxConfirmation(), CanIf_CancelTxConfirmation(), CanIf_CancelTxNotification().
 *  \param[in]   hth: Index of the hardware transmit handle. Parameter must be smaller than CANIF_CFG_MAX_MAILBOXES.
 *  \return      E_OK: Any Tx-PDU transmitted.
 *               E_NOT_OK: No Tx-PDU transmitted.
 *  \pre         Must be called with entered critical section in order to secure the Tx-queue.
 *               Must only be called for "hth" to which any Tx-buffer is mapped.        
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON || CANIF_TRANSMIT_BUFFER_FIFO == STD_ON
 **********************************************************************************************************************/
CANIF_LOCAL FUNC(Std_ReturnType, CANIF_CODE) CanIf_TxQueueTreatment(CanIf_HwHandleType hth);


/***********************************************************************************************************************
 *  CanIf_TxQueueTransmit()
 **********************************************************************************************************************/
/*! \brief       Transmits a Tx-PDU and removes it from the Tx-queue.
 *  \details     Called out of CanIf_TxQueueTreatment().
 *  \param[in]   PduId: Internal Tx-PDU ID. Parameter must be smaller than CANIF_CFG_MAX_TXPDUS. 
 *  \return      E_OK: Can_Write returned with E_OK or BUSY.
 *               E_NOT_OK: Can_Write returned with E_NOT_OK.
 *  \pre         Must be called with entered critical section in order to secure Tx-queue.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON || CANIF_TRANSMIT_BUFFER_FIFO == STD_ON
 **********************************************************************************************************************/
CANIF_LOCAL FUNC(Std_ReturnType, CANIF_CODE) CanIf_TxQueueTransmit(PduIdType PduId);


/***********************************************************************************************************************
 *  CanIf_ClearQueue()
 **********************************************************************************************************************/
/*! \brief       Initializes and resets the Tx-queue.
 *  \details     This API initializes the Tx-queue for CAN channel given by CANIF_CHANNEL_CANTYPE_ONLY. 
 *               Called out of CanIf_SetControllerMode(), CanIf_ControllerBusOff(), CanIf_SetPduMode(), CanIf_Init().
 *  \param[in]   CANIF_CHANNEL_CANTYPE_ONLY: Index of CAN channel. Parameter must be smaller than CANIF_CFG_MAX_CONTROLLER.
 *  \pre         Check if parameter is in range from 0 to CANIF_CFG_MAX_CONTROLLER-1.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON OR CANIF_TRANSMIT_BUFFER_FIFO == STD_ON
 *  \note        The validity of parameter value is NOT checked
 **********************************************************************************************************************/
CANIF_LOCAL FUNC(void, CANIF_CODE) CanIf_ClearQueue(CANIF_CHANNEL_CANTYPE_ONLY);
#endif


#if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
/**********************************************************************************************************************
 *  CanIf_SetPrioByCanIdTxPduAsQueued()
 **********************************************************************************************************************/
/*! \brief       Sets the flag "is buffered".
 *  \details     This API sets the flag of the corresponding TxPdu and returns if it was set before.
 *               Called out of CanIf_Transmit(), CanIf_CancelTxConfirmation().
 *  \param[in]   PduId: Internal Tx-PDU ID for which the "is buffered" flag is set. Parameter must be smaller than CANIF_CFG_MAX_TXPDUS.
 *  \return      E_OK: PduId was not already buffered.
 *               E_NOT_OK: PduId was already buffered.
 *  \pre         Check if a PrioByCanId transmit buffer is assigned to the TxPdu.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON
 *  \note        The validity of parameter value is NOT checked.
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPrioByCanIdTxPduAsQueued(PduIdType PduId);


/**********************************************************************************************************************
 *  CanIf_ClearPrioByCanIdTxPduAsQueued()
 **********************************************************************************************************************/
/*! \brief       Resets the flag "is buffered".
 *  \details     This API resets the flag of the corresponding TxPdu and returns if it was reset before.
 *               Called out of CanIf_Transmit(), CanIf_CancelTransmit(), CanIf_TxQueueTransmit(), CanIf_CancelTransmit().
 *  \param[in]   PduId: Internal Tx-PDU ID for which the "is buffered" flag is reset. Parameter must be smaller than CANIF_CFG_MAX_TXPDUS.
 *  \return      E_OK: PduId was not already buffered.
 *               E_NOT_OK: PduId was already buffered.
 *  \pre         Check if a PrioByCanId transmit buffer is assigned to the TxPdu.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON
 *  \note        The validity of parameter value is NOT checked.
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(Std_ReturnType, CANIF_CODE) CanIf_ClearPrioByCanIdTxPduAsQueued(PduIdType PduId);
#endif


#if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
# if  (CANIF_CANCEL_SUPPORT_API == STD_ON)
/**********************************************************************************************************************
 *  CanIf_InitSubInitFifoQueue()
 **********************************************************************************************************************/
/*! \brief       Resets the flag "is buffered".
 *  \details     This API resets the flag for the complete Fifo buffer. Called out of CanIf_Init().
 *  \param[in]   -
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      CANIF_TRANSMIT_BUFFER_FIFO == STD_ON && CANIF_CANCEL_SUPPORT_API == STD_ON   
 **********************************************************************************************************************/  
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_InitSubInitFifoQueue(void);
# endif
#endif


#if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
  /**********************************************************************************************************************
 *  CanIf_TransmitSubCheckFiFoQueueEmpty()
 **********************************************************************************************************************/
/*! \brief       Checks if the FIFO corresponding to the Tx PDU ID is empty.
 *  \details     Called out of CanIf_Transmit().
 *  \param[in]   CanTxPduId: Internal Tx-PDU ID to be checked. Parameter must be smaller than CANIF_CFG_MAX_TXPDUS.
 *  \return      E_OK:     Buffer is empty.
 *               E_NOT_OK: Buffer is not still empty.
 *  \pre         CanTxPduId must be mapped to a Tx-Buffer of handling type: FIFO
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANIF_TRANSMIT_BUFFER_FIFO == STD_ON
 **********************************************************************************************************************/  
CANIF_LOCAL_INLINE FUNC(boolean, CANIF_CODE) CanIf_TransmitSubCheckFiFoQueueEmpty(PduIdType CanTxPduId);
#endif


/***********************************************************************************************************************
 *  CanIf_HlIndication()
 **********************************************************************************************************************/
/*! \brief       Reports a received message to upper layer.
 *  \details     Additionally it handles: wake-up validation state, DLC check, meta data. Called out of CanIf_RxIndication().
 *  \param[in]   Hrh: hardware receive handle. Parameter must be smaller than CANIF_CFG_MAX_MAILBOXES.
 *  \param[in]   PduId: Internal Rx-PDU ID. Parameter must be smaller than CANIF_CFG_MAX_RXPDUS.
 *  \param[in]   CanSduPtr: pointer to Rx-data
 *  \param[in]   CanDlc: length of Rx-data
 *  \param[in]   CanId: CAN identifier (depends on configuration)
 *  \pre         -
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
#if ((CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON) || (CANIF_META_DATA_RX_SUPPORT == STD_ON) || (CANIF_RX_INDICATION_TYPE_IV_IS_USED == STD_ON))
/* static void CanIf_HlIndication(CanIf_HwHandleType Hrh, PduIdType PduId, const uint8 *CanSduPtr, uint8 CanDlc, Can_IdType CanId); */
CANIF_LOCAL FUNC(void, CANIF_CODE) CanIf_HlIndication(CanIf_HwHandleType  Hrh, PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc, Can_IdType CanId);
#else
CANIF_LOCAL FUNC(void, CANIF_CODE) CanIf_HlIndication(CanIf_HwHandleType  Hrh, PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc);
#endif


/***********************************************************************************************************************
 *  CanIf_HlTxConfirmation()
 **********************************************************************************************************************/
/*! \brief       Reports the confirmation for a successful transmission.
 *  \details     Called out of CanIf_TxConfirmation(), CanIf_Transmit().
 *  \param[in]   CanTxPduId: Internal Tx-PDU ID. Parameter must be smaller than CANIF_CFG_MAX_TXPDUS.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE only for different Tx-PDUs (CanTxPduId).
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANIF_LOCAL FUNC(void, CANIF_CODE) CanIf_HlTxConfirmation(PduIdType CanTxPduId);


#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
/***********************************************************************************************************************
 *  CanIf_TransmitSubHandleTxPduFilter()
 **********************************************************************************************************************/
/*! \brief       Verifies whether the requested Tx-PDU may be transmitted or NOT.
 *  \details     While the PN filter is active only dedicated Tx PDUs are transmitted. Called out of CanIf_Transmit().
 *  \param[in]   CANIF_CHANNEL_CANTYPE_FIRST: Index of CAN channel. Parameter must be smaller than CANIF_CFG_MAX_CONTROLLER.
 *  \param[in]   CanTxPduId: Internal Tx-PDU ID. Parameter must be smaller than CANIF_CFG_MAX_TXPDUS.
 *  \return      CANIF_DO_TRANSMIT: Tx-PDU may be transmitted.
 *               CANIF_DO_NOT_TRANSMIT: Tx-PDU may be NOT transmitted.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANIF_PN_WU_TX_PDU_FILTER == STD_ON
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(CanIf_TransmitStateType, CANIF_CODE) CanIf_TransmitSubHandleTxPduFilter(CANIF_CHANNEL_CANTYPE_FIRST CONST(PduIdType, AUTOMATIC) CanTxPduId);
#endif


#if (CANIF_META_DATA_TX_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  CanIf_TransmitSubHandleMetaData()
 **********************************************************************************************************************/
/*! \brief       Extracts for a meta data Tx-PDU the meta data from passed payload and adapts the CAN identifier accordingly.
 *  \details     Called out of CanIf_Transmit().
 *  \param[in]   PduInfoPtr: PDU Info Pointer for payload including the meta data.
 *  \param[in]   localPduPtr: Pointer to Tx-PDU data (length, CAN identifier, handle ID) to be transmitted.
 *  \pre         All members of PduInfoPtr and localPduPtr except localPduPtr->length must have valid values. No parameter values are checked.
 *               Consistency of PduInfoPtr must be ensured. Hence this API must be called protected with critical area.
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANIF_META_DATA_TX_SUPPORT == STD_ON
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_TransmitSubHandleMetaData(P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_MSG_VAR) PduInfoPtr, P2VAR(Can_PduType, AUTOMATIC, AUTOMATIC) localPduPtr);
#endif


#if (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  CanIf_TransmitSubJ1939DynAddr()
 **********************************************************************************************************************/
/*! \brief       Modifies the CAN identifier according to J1939 specification.
 *  \details     Called out of CanIf_Transmit().
 *  \param[in]   CANIF_CHANNEL_CANTYPE_FIRST: Index of CAN channel. Parameter must be smaller than CANIF_CFG_MAX_CONTROLLER.
 *  \param[in]   localPduPtr: Pointer to PDU data.
 *  \return      E_OK: Modification of CAN identifier succeeded.
 *               E_NOT_OK: Modification of CAN identifier failed. In this case the processing of PDU must be cancelled.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) && (CANIF_EXTENDEDID_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(Std_ReturnType, CANIF_CODE) CanIf_TransmitSubJ1939DynAddr(CANIF_CHANNEL_CANTYPE_FIRST P2VAR(Can_PduType, AUTOMATIC, AUTOMATIC)localPduPtr);
# endif
#endif


#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
/***********************************************************************************************************************
 *  CanIf_TransmitSubHandleTxResBusy()
 **********************************************************************************************************************/
/*! \brief       Handles the Tx-queue.
 *  \details     Called out of CanIf_Transmit().
 *  \param[in]   localPduPtr: Pointer to PDU data.
 *  \return      E_OK: PDU was successfully buffered.
 *               E_NOT_OK: PDU could not be buffered.
 *  \pre         Due to write access to Tx-buffer this API must be called protected with critical area!
 *  \context     ANY
 *  \reentrant   TRUE (only for a different (localPduPtr->swPduHandle))
 *  \synchronous TRUE
 *  \config      CANIF_TRANSMIT_BUFFER == STD_ON
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(Std_ReturnType, CANIF_CODE) CanIf_TransmitSubHandleTxResBusy(P2CONST(Can_PduType, AUTOMATIC, AUTOMATIC) localPduPtr);
#endif


#if (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  CanIf_RxIndicationSubJ1939DynAddr()
 **********************************************************************************************************************/
/*! \brief       Modifies the CAN identifier according to J1939 specification.
 *  \details     Called out of CanIf_RxIndicationAsr403().
 *  \param[in]   rxSearchParams: Parameters needed for J1939 dynamic addressing.
 *  \return      E_OK: Modification of CAN identifier succeeded.
 *               E_NOT_OK: Modification of CAN identifier failed. In this case the processing of PDU must be cancelled.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) && (CANIF_EXTENDEDID_SUPPORT == STD_ON)
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(Std_ReturnType, CANIF_CODE) CanIf_RxIndicationSubJ1939DynAddr(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams);
# endif
#endif


#if (CANIF_SEARCH_ALGORITHM == CANIF_BINARY)
/***********************************************************************************************************************
 *  CanIf_RxIndicationSubBinarySearch()
 **********************************************************************************************************************/
/*! \brief       Searches for a matched Rx-message according to binary search algorithm.
 *  \details     Called out of CanIf_RxIndicationAsr403().
 *  \param[in]   rxSearchParams: Parameters needed for search.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANIF_SEARCH_ALGORITHM == CANIF_BINARY
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubBinarySearch(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams);


/***********************************************************************************************************************
 *  CanIf_RxIndicationSubBinarySearchSubCheckMsgType()
 **********************************************************************************************************************/
/*! \brief       Checks the message type for a matched Rx-message according to binary search algorithm.
 *  \details     Called out of CanIf_RxIndicationSubBinarySearch().
 *  \param[in]   rxSearchParams: Parameters needed for message type check.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (CANIF_SEARCH_ALGORITHM == CANIF_BINARY) && (CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON)
  **********************************************************************************************************************/
# if (CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON)
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubBinarySearchSubCheckMsgType(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams);
# endif
#endif


#if (CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH)
/***********************************************************************************************************************
 *  CanIf_RxIndicationSubDoubleHashSearch()
 **********************************************************************************************************************/
/*! \brief       Searches for a matched Rx-message according to double-hash search algorithm.
 *  \details     Called out of CanIf_RxIndicationAsr403().
 *  \param[in]   rxSearchParams: Parameters needed for search.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubDoubleHashSearch(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams);
#endif


#if (CANIF_SEARCH_ALGORITHM == CANIF_LINEAR)
/***********************************************************************************************************************
 *  CanIf_RxIndicationSubLinearSearch()
 **********************************************************************************************************************/
/*! \brief       Searches for a matched Rx-message according to linear search algorithm.
 *  \details     Called out of CanIf_RxIndicationAsr403().
 *  \param[in]   rxSearchParams: Parameters needed for search.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      CANIF_SEARCH_ALGORITHM == CANIF_LINEAR
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubLinearSearch(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams);
#endif


/***********************************************************************************************************************
 *  CanIf_RxIndicationSubReceptionPduMode()
 **********************************************************************************************************************/
/*! \brief       Checks if FD format and PDU reception mode match.
 *  \details     Is called out from CanIf_RxIndicationSubRangeSearch() and CanIf_RxIndicationAsr403().
 *  \param[in]   rxSearchParams: Parameters needed for search.
 *  \return      CANIF_NO_NOTIFICATION: RxPduId did not match regarding FD format and PDU reception mode.
 *               CANIF_TX_RX_NOTIFICATION: RxPduId did match regarding FD format and PDU reception mode.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_RxIndicationSubReceptionPduMode(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams);


/***********************************************************************************************************************
 *  CanIf_RxIndicationSubRangeSearch()
 **********************************************************************************************************************/
/*! \brief       Searches for a matched Rx-range.
 *  \details     This API uses the search algorithm linear. Called out of CanIf_RxIndicationAsr403().
 *  \param[in]   rxSearchParams: Parameters needed for search.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubRangeSearch(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams);


#if ((CANIF_WAKEUP_VALIDATION == STD_ON) && (CANIF_WAKEUP_VALID_ALL_RX_MSGS == STD_ON))
/***********************************************************************************************************************
 *  CanIf_RxIndicationSubWakeupValidation()
 **********************************************************************************************************************/
/*! \brief       Handles the wake-up validation state.
 *  \details     Called out of CanIf_RxIndicationAsr403().
 *  \param[in]   rxSearchParams: Required parameters.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (CANIF_WAKEUP_VALIDATION == STD_ON) && (CANIF_WAKEUP_VALID_ALL_RX_MSGS == STD_ON)
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubWakeupValidation(P2CONST(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams);
#endif


/***********************************************************************************************************************
 *  CanIf_TransmitSubWrite()
 **********************************************************************************************************************/
/*! \brief       Tries to transmit  a Tx-PDU via CAN driver. In case of CAN driver is busy and the Tx-PDU is mapped
 *               to a Tx-buffer the Tx-PDU is buffered otherwise discarded.
 *  \details     Called out of CanIf_Transmit().
 *  \param[in]   localPduPtr: Pointer to Tx-PDU data (length, CAN identifier, handle ID) to be transmitted.
 *  \return      E_OK: PDU was successfuly handled. 
 *               E_NOT_OK: It was not possible to write the PDU to CAN driver or to buffer it.
 *  \pre         Must be called in context of entered CANIF_EXCLUSIVE_AREA_4.
 *  \context     ANY
 *  \reentrant   TRUE (only for a different (localPduPtr->swPduHandle))
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC (Std_ReturnType, CANIF_CODE) CanIf_TransmitSubWrite(P2CONST(Can_PduType, AUTOMATIC, AUTOMATIC) localPduPtr);


/***********************************************************************************************************************
 *  CanIf_RxIndicationSubBasicCan()
 **********************************************************************************************************************/
/*! \brief       Handles the reception if a Rx-PDU which is mapped to a BasicCAN HW-object.
 *  \details     Called out of CanIf_RxIndicationAsr403().
 *  \param[in]   rxSearchParamsPtr: Pointer to parameters needed for search.
 *  \pre         Must only be called if Hrh is of type: BasicCAN.
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubBasicCan(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams);


/***********************************************************************************************************************
 *  CanIf_HlIndicationSubULCall()
 **********************************************************************************************************************/
/*! \brief       Calls the uppper layer during reception.
 *  \details     Called out of CanIf_HlIndication().
 *  \param[in]   PduId: Internal Rx-PDU ID. Parameter must be smaller than CANIF_CFG_MAX_RXPDUS.
 *  \param[in]   CanSduPtr: pointer to Rx-data
 *  \param[in]   CanDlc: length of Rx-data
 *  \param[in]   CanId: CAN identifier (depends on configuration)
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/  
#if (CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON) || (CANIF_RX_INDICATION_TYPE_IV_IS_USED == STD_ON)
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_HlIndicationSubULCall(PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc, Can_IdType CanId);
#else
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_HlIndicationSubULCall(PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc);
#endif


/***********************************************************************************************************************
 *  CanIf_SetControllerModeSubSwitch()
 **********************************************************************************************************************/
/*! \brief       Sets the controllermode.
 *  \details     Called out of CanIf_SetControllerMode().
 *  \param[in]   CANIF_CHANNEL_CANTYPE_FIRST: Index of CAN channel. Parameter must be smaller than CANIF_CFG_MAX_CONTROLLER.
 *  \param[in]   ControllerMode: target controller mode
 *  \return      E_OK: Modification was successfull.
 *               E_NOT_OK: Buffer does not fit meta data.  
 *  \pre         Must be called in context of entered CANIF_EXCLUSIVE_AREA_0
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous FALSE
 *  \config      -
 **********************************************************************************************************************/ 
CANIF_LOCAL_INLINE FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerModeSubSwitch(CANIF_CHANNEL_CANTYPE_FIRST CanIf_ControllerModeType ControllerMode);


#if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
/***********************************************************************************************************************
 *  CanIf_TxBufferPrioByCanIdQueuePdu()
 **********************************************************************************************************************/
/*! \brief       Stores a PDU within the Tx-buffer of type: PRIO_BY_CANID
 *  \details     Called out of CanIf_TransmitSubHandleTxResBusy().
 *  \param[in]   PduInfoPtr:  Contains length, PduId and datapointer.
 *  \pre         Must be called within entered CANIF_EXCLUSIVE_AREA_1 or CANIF_EXCLUSIVE_AREA_4
 *  \context     ANY
 *  \reentrant   TRUE (only for a different (PduInfoPtr->swPduHandle))
 *  \synchronous TRUE
 *  \config      CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON
 **********************************************************************************************************************/ 
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_TxBufferPrioByCanIdQueuePdu(P2CONST(Can_PduType, AUTOMATIC, CANIF_CBK_DRV_VAR) PduInfoPtr);
#endif

#define CANIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*
 * 1. Dim. -> CanIf_GetPduModeType
 * 2. Dim. -> CanIf_SetPduModeType
 *
 * typedef enum {
 * CANIF_SET_OFFLINE = 0,
 * CANIF_SET_RX_OFFLINE,
 * CANIF_SET_RX_ONLINE,
 * CANIF_SET_TX_OFFLINE,
 * CANIF_SET_TX_ONLINE,
 * CANIF_SET_ONLINE,
 * CANIF_SET_TX_OFFLINE_ACTIVE
 *} CanIf_SetPduModeType;
 *
 */
CANIF_LOCAL CONST(uint8, CANIF_CONST) CanIfState[CANIF_NO_MODE_PDU_GET_MODE_TYPE_END][CANIF_NO_MODE_PDU_SET_MODE_TYPE_END] = /* PRQA S 1514, 3218 */ /* MD_CanIf_Rule8.9, MD_CanIf_Rule8.9 */ 
{
  /* actual state CANIF_GET_OFFLINE: */  
  { 
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_GET_RX_ONLINE),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_GET_TX_ONLINE),
    (uint8)(CANIF_GET_ONLINE),
    (uint8)(CANIF_GET_OFFLINE_ACTIVE)
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
,   (uint8)(CANIF_GET_ONLINE_WAKF),        /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_TX_ONLINE_WAKF)      /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  },
  
  /* actual state CANIF_GET_RX_ONLINE: */  
  {
    (uint8)(CANIF_GET_OFFLINE),
    (uint8)(CANIF_GET_OFFLINE),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_GET_ONLINE),
    (uint8)(CANIF_GET_ONLINE),
    (uint8)(CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE)
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
,   (uint8)(CANIF_GET_ONLINE_WAKF),             /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_ONLINE_WAKF)              /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  },
  
  /* actual state CANIF_GET_TX_ONLINE: */  
  {
    (uint8)(CANIF_GET_OFFLINE),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_GET_ONLINE),
    (uint8)(CANIF_GET_OFFLINE),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_GET_ONLINE),
    (uint8)(CANIF_GET_OFFLINE_ACTIVE)
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
,   (uint8)(CANIF_GET_ONLINE_WAKF),   /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_TX_ONLINE_WAKF) /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  },
    
  /* actual state CANIF_GET_ONLINE: */  
  {
    (uint8)(CANIF_GET_OFFLINE),
    (uint8)(CANIF_GET_TX_ONLINE),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_GET_RX_ONLINE),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) 
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
,   (uint8)(CANIF_GET_ONLINE_WAKF),             /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_ONLINE_WAKF)              /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  },
    
  /* actual state CANIF_GET_OFFLINE_ACTIVE: */  
  { 
    (uint8)(CANIF_GET_OFFLINE),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE),
    (uint8)(CANIF_GET_OFFLINE),
    (uint8)(CANIF_GET_TX_ONLINE),
    (uint8)(CANIF_GET_ONLINE),
    (uint8)(CANIF_NOP)
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
,   (uint8)(CANIF_GET_ONLINE_WAKF),              /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_TX_ONLINE_WAKF)            /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  },
        
  /* actual state CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE: */  
  {
    (uint8)(CANIF_GET_OFFLINE),
    (uint8)(CANIF_GET_OFFLINE_ACTIVE),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_GET_RX_ONLINE),
    (uint8)(CANIF_GET_ONLINE),
    (uint8)(CANIF_GET_ONLINE),
    (uint8)(CANIF_NOP)
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
,   (uint8)(CANIF_GET_ONLINE_WAKF),    /* CANIF_SET_ONLINE_WAKF */
    (uint8)(CANIF_GET_ONLINE_WAKF)     /* CANIF_SET_TX_ONLINE_WAKF */
#endif
  }
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
,
  /* actual state CANIF_GET_ONLINE_WAKF: */
  {
    (uint8)(CANIF_GET_OFFLINE),
    (uint8)(CANIF_GET_TX_ONLINE_WAKF),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_GET_RX_ONLINE),
    (uint8)(CANIF_GET_ONLINE),
    (uint8)(CANIF_GET_ONLINE),
    (uint8)(CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_NOP)
  },
  /* actual state CANIF_GET_TX_ONLINE_WAKF: */
  {
    (uint8)(CANIF_GET_OFFLINE),
    (uint8)(CANIF_NOP),
    (uint8)(CANIF_GET_ONLINE_WAKF),
    (uint8)(CANIF_GET_OFFLINE),
    (uint8)(CANIF_GET_TX_ONLINE),
    (uint8)(CANIF_GET_ONLINE),
    (uint8)(CANIF_GET_OFFLINE_ACTIVE),
    (uint8)(CANIF_GET_ONLINE_WAKF),
    (uint8)(CANIF_NOP)
  }
#endif
};

#if (CANIF_BITQUEUE == STD_ON)
/* lookup table for setting the flags in the queue */
CANIF_LOCAL CONST(CanIf_TxQueueFlagType, CANIF_CONST) CanShiftLookUp[1u << kCanTxQueueShift] =
{
  (CanIf_TxQueueFlagType)0x00000001u, (CanIf_TxQueueFlagType)0x00000002u, (CanIf_TxQueueFlagType)0x00000004u, (CanIf_TxQueueFlagType)0x00000008u,
  (CanIf_TxQueueFlagType)0x00000010u, (CanIf_TxQueueFlagType)0x00000020u, (CanIf_TxQueueFlagType)0x00000040u, (CanIf_TxQueueFlagType)0x00000080u
# if ( CPU_TYPE > CPU_TYPE_8 ) /* COV_CANIF_PLATFORM_DEPENDENCY */
,  (CanIf_TxQueueFlagType)0x00000100u, (CanIf_TxQueueFlagType)0x00000200u, (CanIf_TxQueueFlagType)0x00000400u, (CanIf_TxQueueFlagType)0x00000800u,
   (CanIf_TxQueueFlagType)0x00001000u, (CanIf_TxQueueFlagType)0x00002000u, (CanIf_TxQueueFlagType)0x00004000u, (CanIf_TxQueueFlagType)0x00008000u
# endif
# if ( CPU_TYPE > CPU_TYPE_16 ) /* COV_CANIF_PLATFORM_DEPENDENCY */
,  (CanIf_TxQueueFlagType)0x00010000u, (CanIf_TxQueueFlagType)0x00020000u, (CanIf_TxQueueFlagType)0x00040000u, (CanIf_TxQueueFlagType)0x00080000u,
   (CanIf_TxQueueFlagType)0x00100000u, (CanIf_TxQueueFlagType)0x00200000u, (CanIf_TxQueueFlagType)0x00400000u, (CanIf_TxQueueFlagType)0x00800000u,
   (CanIf_TxQueueFlagType)0x01000000u, (CanIf_TxQueueFlagType)0x02000000u, (CanIf_TxQueueFlagType)0x04000000u, (CanIf_TxQueueFlagType)0x08000000u,
   (CanIf_TxQueueFlagType)0x10000000u, (CanIf_TxQueueFlagType)0x20000000u, (CanIf_TxQueueFlagType)0x40000000u, (CanIf_TxQueueFlagType)0x80000000u
# endif
};
#endif 

#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define CANIF_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if (CANIF_USE_INIT_POINTER == STD_ON)
P2CONST(CanIf_ConfigType, CANIF_VAR_INIT, CANIF_XCFG) CanIf_ConfigDataPtr = NULL_PTR; /* UREQ00035484 */

# if (CANIF_DEV_ERROR_DETECT == STD_ON)
CANIF_LOCAL VAR(boolean, CANIF_VAR_INIT) CanIf_SystemInit = FALSE;
# endif
# endif /* CANIF_USE_INIT_POINTER == STD_ON */


#define CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS / GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#define CANIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
/**********************************************************************************************************************
 *  CanIf_TransmitSubCheckFiFoQueueEmpty()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(boolean, CANIF_CODE) CanIf_TransmitSubCheckFiFoQueueEmpty(PduIdType CanTxPduId)
{
  boolean  retVal = FALSE;
  CanIf_AnyIdxType txBufferCfgIdx;
  CanIf_AnyIdxType hth;
  /* #100 Has PDU a buffer and is it handled as FIFO? */
  hth = CANIF_CFG_TX_HTH(CanTxPduId);
  txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(hth);
  /* #110 Only if the FIFO is empty at all, the Tx-PDU may be transmitted directly otherwise the Tx-PDU must be queued into FIFO in order to ensure FIFO-behavior. */
  if (CANIF_VAR_TXBUFFERFIFO_BUFFERBASE((CANIF_CFG_TXBUFFERFIFO_BUFFERBASEIDX(txBufferCfgIdx)), eQueueCounter) == 0u)
  {
    /* NO */
    retVal = TRUE;
  }
  return retVal;
}
#endif

#if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
# if (CANIF_CANCEL_SUPPORT_API == STD_ON) 
/**********************************************************************************************************************
 *  CanIf_InitSubInitFifoQueue()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 ********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_InitSubInitFifoQueue(void)
{
  CanIf_AnyIdxType counter;
  /* #100 Iterate over all CanIf_TxQueueIndex2FifoEl and set them invalid */
  for(counter = 0; counter < CanIf_GetSizeOfTxQueueIndex2FifoEl(); counter++)
  {
    CANIF_VAR_SET_TXBUFFERFIFO_QUEUEIDX2FIFOEL((counter), CANIF_NO_ENTRY_IN_TX_FIFO);  /* SBSW_CANIF_15 */
  }
  /* #200 Iterate over all CanIf_TxFifoQueueBase and set them "not queued" */
  for(counter = 0; counter < CanIf_GetSizeOfTxFifoQueueBase(); counter++)
  {
    CANIF_VAR_TXBUFFERFIFO_QUEUEBASE( counter, eQueued) = 0;                           /* SBSW_CANIF_15 */
  }
}
# endif
#endif

#if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
/**********************************************************************************************************************
 *  CanIf_SetPrioByCanIdTxPduAsQueued()
 **********************************************************************************************************************/
/*!
 *
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
CANIF_LOCAL_INLINE FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPrioByCanIdTxPduAsQueued(PduIdType PduId)
{
# if (CANIF_BITQUEUE == STD_ON)
  CanIf_AnyIdxType  queueElementIdx;
  uint8         elementBitIdx;
  PduIdType     queueBitPos;
# endif  
  uint8 errorId;
  CanIf_AnyIdxType txBufferCfgIdx;
  Std_ReturnType retval = E_NOT_OK;
  errorId = CANIF_E_NO_ERROR;
  txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(CANIF_CFG_TX_HTH(PduId));
  /* #100 BitQueue */
# if (CANIF_BITQUEUE == STD_ON)
  /* #110 Compute the elementIdx and the element bit position */
  queueBitPos  =  (PduIdType)(PduId - CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_BITPOS2TXPDUIDOFFSET(txBufferCfgIdx));
  queueElementIdx = (((uint16_least)queueBitPos) >> kCanTxQueueShift) + CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUESTARTIDX(txBufferCfgIdx); /* PRQA S 2842 */ /* MD_CanIf_Dir4.1_2842 */ 
  elementBitIdx  = (uint8)(queueBitPos & kCanTxQueueMask);
  /* #120 Is flag already set for given PduId ?*/
  if( (CANIF_VAR_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUEFLAGS(queueElementIdx) & CanShiftLookUp[elementBitIdx]) == (CanIf_TxQueueFlagType)0 ) /* PRQA S 2842 */ /* MD_CanIf_Dir4.1_2842 */ 
  {  
#  if (CANIF_DEV_ERROR_DETECT == STD_ON)
    if (queueElementIdx >= CanIf_GetSizeOfTxQueueFlags()) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_FATAL;
    }
    else
#  endif      
    {
      /* #130 If not already set do it now and increment counter */
      CANIF_VAR_SET_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUEFLAGS(queueElementIdx, (CANIF_VAR_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUEFLAGS(queueElementIdx) | CanShiftLookUp[elementBitIdx]));  /* SBSW_CANIF_20 */
      CanIf_IncTxQueueCounter(CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_BUFFERBASEIDX(txBufferCfgIdx)); /* SBSW_CANIF_25 */
      retval = E_OK;
    }
  }
  /* #200 ByteQueue */
# else
  /* #210 Is flag already set for given PduId? */
  if (CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueued) == 0u)
  {
    /* #220 If not already set do it now and increment counter */
    CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueued) = 1u; /* SBSW_CANIF_6 */
    CanIf_IncTxQueueCounter(CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_BUFFERBASEIDX(txBufferCfgIdx) ); /* SBSW_CANIF_25 */
    retval = E_OK;
  }
# endif
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */ /* COV_CANIF_GENDATA_FAILURE */
  {
    CanIf_Det_ReportError(CANIF_INIT_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;  
}

/**********************************************************************************************************************
 *  CanIf_ClearPrioByCanIdTxPduAsQueued()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(Std_ReturnType, CANIF_CODE) CanIf_ClearPrioByCanIdTxPduAsQueued(PduIdType PduId)
{
# if (CANIF_BITQUEUE == STD_ON)
  CanIf_AnyIdxType  queueElementIdx;
  uint8         elementBitIdx;
  PduIdType     queueBitPos;
# endif  
  uint8 errorId;
  CanIf_AnyIdxType txBufferCfgIdx;
  Std_ReturnType retval = E_NOT_OK;
  errorId = CANIF_E_NO_ERROR;
  txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(CANIF_CFG_TX_HTH(PduId));
  /* #100 BitQueue */
# if (CANIF_BITQUEUE == STD_ON)
  /* #110 Compute the elementIdx and the element bit position */
  queueBitPos  =  (PduIdType)(PduId - CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_BITPOS2TXPDUIDOFFSET(txBufferCfgIdx));
  queueElementIdx = (((uint16_least)queueBitPos) >> kCanTxQueueShift) + CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUESTARTIDX(txBufferCfgIdx); /* PRQA S 2842 */ /* MD_CanIf_Dir4.1_2842 */
  elementBitIdx  = (uint8)(queueBitPos & kCanTxQueueMask);
  /* #120 Is flag set for given PduId ?*/
  if( (CANIF_VAR_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUEFLAGS(queueElementIdx) & CanShiftLookUp[elementBitIdx]) != (CanIf_TxQueueFlagType)0 ) /* PRQA S 2842 */ /* MD_CanIf_Dir4.1_2842 */ 
  {
#  if (CANIF_DEV_ERROR_DETECT == STD_ON)
    if (queueElementIdx >= CanIf_GetSizeOfTxQueueFlags()) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_FATAL;
    }
    else
#  endif          
    {
      /* #130 If set clear it and decrement counter */
      CANIF_VAR_SET_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUEFLAGS(queueElementIdx, (CANIF_VAR_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUEFLAGS(queueElementIdx) & (~CanShiftLookUp[elementBitIdx]))); /* SBSW_CANIF_20 */
      CanIf_DecTxQueueCounter(CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_BUFFERBASEIDX(txBufferCfgIdx));  /* SBSW_CANIF_25 */
      retval = E_OK;
    }
  }
  /* #200 ByteQueue */
# else    
  /* #210 Is flag set for given PduId ?*/
  if (CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueued) == 1u)
  {
    /* #220 If set clear it and decrement counter */
    CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueued) = 0u; /* SBSW_CANIF_6 */
    CanIf_DecTxQueueCounter(CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_BUFFERBASEIDX(txBufferCfgIdx)); /* SBSW_CANIF_25 */
    retval = E_OK;
  }
# endif
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */ /* COV_CANIF_GENDATA_FAILURE */
  {
    CanIf_Det_ReportError(CANIF_INIT_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;  
}
#endif


#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
/**********************************************************************************************************************
 *  CanIf_ClearQueue()
 **********************************************************************************************************************/
/*!
 *
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
 **********************************************************************************************************************/
CANIF_LOCAL FUNC(void, CANIF_CODE) CanIf_ClearQueue(CANIF_CHANNEL_CANTYPE_ONLY)
{ 
  CanIf_AnyIdxType idx2MappedTxBufferCfg;
  CanIf_AnyIdxType hth;
# if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
  CanIf_AnyIdxType txBufferBaseIdx;
#  if (CANIF_BITQUEUE == STD_ON)  
  CanIf_AnyIdxType TxQueueFlagsIdx;
#  else
  CanIf_AnyIdxType MappedTxPdusIdx;
  CanIf_AnyIdxType TxPduId;      
#  endif    
# endif
# if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
  CanIf_AnyIdxType txBufferFifoBaseIdx;
#  if (CANIF_CANCEL_SUPPORT_API == STD_ON)  
  CanIf_AnyIdxType txFifoQueueBaseStartIdx;
  CanIf_TxBufferSizeType readIdx;
  CanIf_TxBufferSizeType counter;
#  endif  
# endif  
  CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_1);
  /* #100 Get all HTHs with configured Tx-buffer of affected CAN-channel */
  for(idx2MappedTxBufferCfg = CANIF_CFG_CTRL_STARTIDX2MAPPEDTXBUFFERS(CanIf_Controller_Value); idx2MappedTxBufferCfg < CANIF_CFG_CTRL_STOPIDX2MAPPEDTXBUFFERS(CanIf_Controller_Value); idx2MappedTxBufferCfg++ ) 
  {
    CanIf_AnyIdxType txBufferCfgIdx;
    hth = CANIF_CFG_MAPPEDTXBUFFERS(idx2MappedTxBufferCfg); /* hth to access CanIf_MailBoxConfig[] */
    txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(hth);
    /* #110 Clear the Tx-buffer dependent on it's Tx-buffer handling type */
    switch (CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(hth))
    {
# if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
      case CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID:
#  if (CANIF_BITQUEUE == STD_ON)
        /* #200 Clearing of PRIO_BY_CANID: BIT_QUEUE */
        for( TxQueueFlagsIdx = CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUESTARTIDX(txBufferCfgIdx); TxQueueFlagsIdx < CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUESTOPIDX(txBufferCfgIdx); TxQueueFlagsIdx++)
        {
          CANIF_VAR_SET_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUEFLAGS(TxQueueFlagsIdx, 0);  /* SBSW_CANIF_26 */
        }
        txBufferBaseIdx = CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_BUFFERBASEIDX(txBufferCfgIdx);
# else
        /* #300 Clearing of PRIO_BY_CANID: BYTE_QUEUE */
        for (MappedTxPdusIdx = CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_STARTIDX2MAPPEDTXPDUS(txBufferCfgIdx); MappedTxPdusIdx < CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_STOPIDX2MAPPEDTXPDUS(txBufferCfgIdx); MappedTxPdusIdx++)
        {
          TxPduId =  CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_MAPPEDTXPDUS(MappedTxPdusIdx);
          CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(TxPduId), eQueued) = 0;  /* SBSW_CANIF_28 */
        }
        txBufferBaseIdx = CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_BUFFERBASEIDX(txBufferCfgIdx);
# endif  
        /* #400  Set QueueCounter to 0 */
        CanIf_SetTxQueueCounter(txBufferBaseIdx, 0);  /* SBSW_CANIF_27 */
        break;
# endif  
# if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
      case CANIF_TXBUFFER_HANDLINGTYPE_FIFO:
        /* #500 Clearing of FIFO */
        txBufferFifoBaseIdx = CANIF_CFG_TXBUFFERFIFO_BUFFERBASEIDX((txBufferCfgIdx));
        
        /* #520 In case of CANIF_CANCEL_SUPPORT_API == STD_ON and module is just initialized, re-set all indirections in CanIf_TxQueueIndex2FifoEl and the flags for TxFifoQueueBase */
#  if (CANIF_CANCEL_SUPPORT_API == STD_ON)
        if(CanIf_GetCtrlMode(CanIf_Controller_Value) != CANIF_CS_UNINIT)
        {
          readIdx = CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx);
          counter =  CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eQueueCounter);
          txFifoQueueBaseStartIdx = CANIF_CFG_TXBUFFERFIFO_QUEUEBASESTARTIDX(txBufferCfgIdx);
        
          while(counter > 0u)
          {
            CANIF_VAR_SET_TXBUFFERFIFO_QUEUEIDX2FIFOEL(CANIF_CFG_TX_QUEUEINDEX(CANIF_VAR_TXBUFFERFIFO_QUEUEBASE((readIdx + txFifoQueueBaseStartIdx), eTxPduId)), CANIF_NO_ENTRY_IN_TX_FIFO); /* SBSW_CANIF_35 */
            CANIF_VAR_TXBUFFERFIFO_QUEUEBASE((readIdx + txFifoQueueBaseStartIdx), eQueued) = 0;  /* SBSW_CANIF_34 */

            readIdx++;
            if(readIdx == CANIF_CFG_TXBUFFERFIFO_QUEUESIZE(txBufferCfgIdx)) 
            {
              readIdx = 0;
            }
            counter--;
          }
        }
#  endif
        /* #530 Set ReadIdx, WriteIdx and QueueCounter to 0 */
        CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eWriteIdx) = 0;      /* SBSW_CANIF_33 */
        CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx) = 0;       /* SBSW_CANIF_33 */
        CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eQueueCounter) = 0;  /* SBSW_CANIF_33 */

        break;
# endif            
      default:  /* COV_CANIF_GENDATA_FAILURE */
        break;
    }
  }
  CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_1);
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif  /* ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)) */

/* \trace SPEC-1829 */
/***********************************************************************************************************************
 *  CanIf_Init()
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_Init(P2CONST(CanIf_ConfigType, AUTOMATIC, CANIF_XCFG) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  CANIF_CHANNEL_CANTYPE_LOCAL
  uint8 errorId = CANIF_E_NO_ERROR;

  /* \trace SPEC-1966 automatically supported due to only one valid configuration supported */
  /* Store the initialization pointer */
#if (CANIF_USE_INIT_POINTER == STD_ON)
  CanIf_ConfigDataPtr = ConfigPtr;

  /* ----- Development Error Checks --------------------------------------- */
# if ((CANIF_DEV_ERROR_DETECT == STD_ON ) || (CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME))
  /* #10 Check if parameter ConfigPtr is valid */
  if (CanIf_ConfigDataPtr == NULL_PTR)
  {
#  if (CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME)
    EcuM_BswErrorHook((uint16) CANIF_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
#  else
    errorId = CANIF_E_PARAM_POINTER;
#  endif
    }
    else
# endif
# if (CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME)
  /* UREQ00035482 */
  /* #20 Check generator version */
  if(CANIF_CFG_GENERATORCOMPATIBILITYVERSION != CANIF_GENDATA_COMPATIBILITY_VERSION)
  {
    EcuM_BswErrorHook((uint16) CANIF_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION);
  }
  /* #30 Check the magic number */
  else if (CANIF_CFG_MAGICNUMBER != CANIF_MAGIC_NUMBER)
  {
    /* UREQ00035483 */
    EcuM_BswErrorHook((uint16) CANIF_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
  else
# endif
#else
  CANIF_DUMMY_STATEMENT(ConfigPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
  /* #40 Check the size of type Can_IdType */
# if (CANIF_EXTENDEDID_SUPPORT != STD_ON)
  if (sizeof (Can_IdType) != 2u) /* PRQA S 2742 */ /* MD_CanIf_Rule14.3_GenData */ /* COV_CANIF_GENDATA_FAILURE */
  {
    errorId = CANIF_E_INVALID_CANIDTYPESIZE; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  if (sizeof (Can_IdType) != 4u) /* PRQA S 2742 */ /* MD_CanIf_Rule14.3_GenData */ /* COV_CANIF_GENDATA_FAILURE */
  {
    errorId = CANIF_E_INVALID_CANIDTYPESIZE; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# endif
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
  else
  /*  ESCAN00092230 FEAT-2004: Release of FEAT-912 (Support of several CAN Drivers in one ECU configuration) */
  if ( CanIf_GetSizeOfCanChannelIdUpToLowMap() < CANIF_CFG_MAX_CONTROLLER) /* PRQA S 2742 */ /* MD_CanIf_Rule14.3_GenData */ /* COV_CANIF_GENDATA_FAILURE */
  {
    errorId = CANIF_E_FATAL; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# endif
  else
#endif
  {
    /* #100 Initialize all dynamic Tx-PDUs */
#if (CANIF_SETDYNAMICTXID_API == STD_ON)
    PduIdType DynamicPduId;
    PduIdType CanPduId;
    for(CanPduId = 0; CanPduId < CANIF_CFG_MAX_TXPDUS; CanPduId++)
    {
      DynamicPduId = CANIF_CFG_STAT2DYN_INDIRECTION(CanPduId);
      if(DynamicPduId < CanIf_GetSizeOfDynTxId())
      {
        CANIF_VAR_DYNTXID(DynamicPduId) = CANIF_CFG_TX_CANID(CanPduId);  /* SBSW_CANIF_14 */
      }
    }
#endif
    /* #110 Run through all CAN channels and initialize them */
#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
    for (controller = 0; controller < CANIF_CFG_MAX_CONTROLLER; controller++)
#endif
    {
#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
      /* \trace SPEC-3665 */
      /* #120 Initialize the Tx-queue */
      /* ESCAN00087530 after CanIf_ClearQueue() in state CANIF_CS_UNINIT, WriteIdx, ReadIdx and QueueCounter are initialized */
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION==STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
      CanIf_ClearQueue();
# else
      CanIf_ClearQueue(CanIf_Controller_Value_Local);
# endif
#endif
      /* \trace SPEC-3750, SPEC-3755, SPEC-3752 */
      /* #130 Initialize controller mode */
      CanIf_SetCtrlMode(CanIf_Controller_Value_Local, CANIF_CS_STOPPED);  /* SBSW_CANIF_3 */
      /* #140 Initialize PDU mode */
      CanIf_SetChannelMode(CanIf_Controller_Value_Local, CANIF_GET_OFFLINE); /* SBSW_CANIF_3 */
#if (CANIF_WAKEUP_VALIDATION == STD_ON)
      /* \trace SPEC-3754 */
      /* #150 Initialize wake-up validation state */
      CanIf_SetWakeUpValidationState(CanIf_Controller_Value_Local, CANIF_WUVALIDATION_ARMED); /* SBSW_CANIF_3 */
#endif
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
      /* #160 Initialize the Tx-filter state */
      CanIf_SetPnWuTxPduFilterActive(CanIf_Controller_Value_Local, FALSE); /* SBSW_CANIF_3 */
#endif

#if (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON)
      /* #170 Initialize the Tx-confirmation state */
      CanIf_SetTxConfState(CanIf_Controller_Value_Local, CANIF_NO_NOTIFICATION); /* SBSW_CANIF_3 */
#endif

#if (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
      {
        uint8 index;
        
        /* #180 Initialize the dynamic address lookup table (only for J1939Nm channel) */
        if(CANIF_CFG_CTRLJ1939DYNADDRSUPPORT(CanIf_Controller_Value_Local) != CANIF_J1939_DYN_ADDR_DISABLED )
        {
          for(index = 0; index < 0xFFu; index++)
          {
            CANIF_VAR_SET_J1939RXADDR_LOOKUP(CanIf_Controller_Value_Local, index, CANIF_J1939_NULL_ADDR);  /* SBSW_CANIF_17 */
            CANIF_VAR_SET_J1939TXADDR_LOOKUP(CanIf_Controller_Value_Local, index, CANIF_J1939_NULL_ADDR);  /* SBSW_CANIF_17 */
          }
          CANIF_VAR_SET_J1939RXADDR_LOOKUP(CanIf_Controller_Value_Local, 0xFFu, CANIF_J1939_BROADCAST_ADDR); /* SBSW_CANIF_17 */
          CANIF_VAR_SET_J1939TXADDR_LOOKUP(CanIf_Controller_Value_Local, 0xFFu, CANIF_J1939_BROADCAST_ADDR); /* SBSW_CANIF_17 */
        }
      }
# endif  /* (CANIF_EXTENDEDID_SUPPORT == STD_ON) */
#endif /* (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED)  */

#if (CANIF_BUS_MIRRORING_SUPPORT == STD_ON)
      /* #190 Initialize mirroring to disabled */
      CanIf_ChangeMirroring(CanIf_Controller_Value_Local, FALSE); /* SBSW_CANIF_3 */
#endif /* CANIF_BUS_MIRRORING_SUPPORT == STD_ON */
    } /* FOR-loop: Run through all channels */
#if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
# if (CANIF_CANCEL_SUPPORT_API == STD_ON) 
    /* #200 Initialize SW-cancellation part of FIFO */
    CanIf_InitSubInitFifoQueue();
# endif      
#endif     
#if (CANIF_SET_PDU_RECEPTION_MODE_SUPPORT == STD_ON)
    {
      CanIf_PduRxModeIterType index;
      /* #300 Set the reception mode to default value */
      for(index = 0; index < CanIf_GetSizeOfPduRxMode(); index++)
      {
        CANIF_VAR_SET_PDU_RECEPTION_MODE(index, CANIF_RMT_RECEIVE_STOP); /* SBSW_CANIF_23 */
      }
    }
#endif
#if ((CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON))
    CanIf_SystemInit = TRUE;  /* ESCAN00083271 */
#endif
  }
  /* ----- Development Error Report --------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */ /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
  {
    CanIf_Det_ReportError(CANIF_INIT_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */


/***********************************************************************************************************************
 *  CanIf_SetControllerModeSubSwitch()
 **********************************************************************************************************************/
/*! Internal comment removed.
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
 *
 *
 *
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerModeSubSwitch(CANIF_CHANNEL_CANTYPE_FIRST CanIf_ControllerModeType ControllerMode)
{
  Std_ReturnType retval;
#if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
  CanIf_Can_SetControllerModeFctType canSetCtrlModeFct;
  /* if(CANIF_MULTIPLE_CANDRV_SUPPORT == STD_OFF) canSetCtrlModeFct is defined to Can_SetControllerMode */
  canSetCtrlModeFct = CANIF_GET_CANSETCTRLMODEFCT(CanIf_Controller_Value);
#endif
  retval = E_NOT_OK;
    
  /* #100 Do the switch based on the desired target controller mode */
  switch (ControllerMode)
  {
    case CANIF_CS_STOPPED:
      /* #200 Transition to STOP: Transition possible from any mode */
      /* \trace SPEC-3763 */
      switch(CanIf_GetCtrlMode(CanIf_Controller_Value))
      {
        case CANIF_CS_SLEEP:
          /* #210 Set CAN driver to WAKEUP if currently in SLEEP mode */
          /* CAN Driver transition to WakeUp and Stop required if WakeUp is initiated by application */
          /* \trace SPEC-1845, SPEC-1996 */
          if (canSetCtrlModeFct((uint8)CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), CAN_T_WAKEUP) == CAN_OK) /* SBSW_CANIF_41 */ /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
          {
            retval = E_OK;
          }
          break;

        case CANIF_CS_STARTED:
          /* \trace SPEC-5124 */          
          /* \trace SPEC-1845, SPEC-1996 */
          /* #220 Request CAN driver to STOP if currently in START mode */
          if (canSetCtrlModeFct((uint8)CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), CAN_T_STOP) == CAN_OK) /* SBSW_CANIF_41 */ /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
          {
#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
            /* \trace SPEC-3764 */
            /*#230 If CAN driver confirms the request clear the Tx-queue */
            CanIf_ClearQueue(CANIF_CHANNEL_CANPARA_ONLY);
#endif            
            retval = E_OK;
          }
          break;

        /* \trace SPEC-3753 */
        case CANIF_CS_STOPPED:
          /* \trace SPEC-1845, SPEC-1996 */
          /* #240 Request CAN driver to STOP if currently in STOP mode */
          if (canSetCtrlModeFct((uint8)CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), CAN_T_STOP) == CAN_OK) /* SBSW_CANIF_41 */ /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
          {
            retval = E_OK;
          }
          break;

        default:
          /* CAN Interface in invalid mode */
          /* retval already set to E_NOT_OK as default */
          break;
      }
      break;
    case CANIF_CS_STARTED:  
      /* #300 Transition to START: Transition only possible from STOP mode */
      /* \trace SPEC-3757 */
      
      switch(CanIf_GetCtrlMode(CanIf_Controller_Value))
      {
        case CANIF_CS_STOPPED:
          /* \trace SPEC-1845, SPEC-1996 */
          /* #310 Request CAN driver to START if currently in STOP mode */
          if (canSetCtrlModeFct((uint8)CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), CAN_T_START) == CAN_OK) /* SBSW_CANIF_41 */ /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
          {
            retval = E_OK;
          }
          break;
          
        case CANIF_CS_STARTED:
          /* \trace SPEC-1845, SPEC-1996 */
          /* #320 Request CAN driver to START if currently in START mode */
          if (canSetCtrlModeFct((uint8)CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), CAN_T_START) == CAN_OK) /* SBSW_CANIF_41 */ /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
          {
            retval = E_OK;
          }
          break;
          
        default:
          /* retval already set to E_NOT_OK as default */
          break;
      }
      break;
    case CANIF_CS_SLEEP:
      /* #400 Transition to SLEEP: Transition only possible from STOP mode */
      /* CanIf_ControllerMode is now CANIF_CS_STOPPED unless an error occurred -> E_NOT_OK still set in case of incomplete transition */
      /* \trace SPEC-3759 */

      switch(CanIf_GetCtrlMode(CanIf_Controller_Value))
      {
        case CANIF_CS_STOPPED:
          /* \trace SPEC-1845, SPEC-1996 */
          /* #410 Request CAN driver to SLEEP if currently in STOP mode */
          if (canSetCtrlModeFct((uint8)CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), CAN_T_SLEEP) == CAN_OK) /* SBSW_CANIF_41 */ /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
          {
#if (CANIF_WAKEUP_VALIDATION == STD_ON)
            /* ESCAN00079059 Reset of stored wake-up validation event moved to this place */
            /* CANIF756 */
            /* #420 Reset the wake-up validation state */
            CanIf_SetWakeUpValidationState(CanIf_Controller_Value, CANIF_WUVALIDATION_ARMED); /* SBSW_CANIF_3 */
#endif
            retval = E_OK;
          }
          break;
          
        case CANIF_CS_SLEEP:
          if (canSetCtrlModeFct((uint8)CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), CAN_T_SLEEP) == CAN_OK)  /* SBSW_CANIF_41 */ /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
          {
            retval = E_OK;
          }
          break;
          
        default:
          /* Transition not allowed */
          /* E_NOT_OK already set */
          break;
      }
      break;
    default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      /* \trace SPEC-21340 */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
      CanIf_Det_ReportError(CANIF_SETCONTROLLERMODE_API, CANIF_E_PARAM_CTRLMODE);
#endif
      break;
    }
    return retval;
} /* PRQA S 6030 */ /* MD_MSR_STCYC */


/* \trace SPEC-1830 */
/***********************************************************************************************************************
 *  CanIf_SetControllerMode()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerMode(uint8 ControllerId, CanIf_ControllerModeType ControllerMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* \trace SPEC-3751 */
  Std_ReturnType retval = E_NOT_OK;
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    /* \trace SPEC-1997 */
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
# if ((CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON) && (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CanIf_Controller_Value))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
# endif
  else
#endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* return E_NOT_OK if controller is in state CANIF_CS_UNINIT */

#if (CANIF_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do mode transition only if CAN channel is initialized */
    if (CanIf_GetCtrlMode(CanIf_Controller_Value) != CANIF_CS_UNINIT)
#endif
    {
      /* return E_NOT_OK if requested device mode already active */
      /* #110 Perform mode transition only within critical section */
      CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_0);
      retval = CanIf_SetControllerModeSubSwitch(CANIF_CHANNEL_CANPARA_FIRST ControllerMode);
      CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_0);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_SETCONTROLLERMODE_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

#if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  /* \trace SPEC-3751 */
  return retval;
}  /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */

/* \trace SPEC-1916 */
/***********************************************************************************************************************
 *  CanIf_GetControllerMode()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerMode(uint8 ControllerId, P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) ControllerModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    /* \trace SPEC-1998 */
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  /* #40 Check if parameter ControllerModePtr is valid */
  else if (ControllerModePtr == NULL_PTR)
  {
    /* \trace SPEC-5232 */
    errorId = CANIF_E_PARAM_POINTER;
  }
  else
#endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  {
    /* \trace SPEC-5065 */
    /* #100 Retrieve the actual mode */
    *ControllerModePtr = CanIf_GetCtrlMode(CanIf_Controller_Value); /* SBSW_CANIF_4 */
    retval = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_GETCONTROLLERMODE_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

#if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  return retval;
}

#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
/***********************************************************************************************************************
 *  CanIf_TransmitSubHandleTxPduFilter()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(CanIf_TransmitStateType, CANIF_CODE) CanIf_TransmitSubHandleTxPduFilter(CANIF_CHANNEL_CANTYPE_FIRST CONST(PduIdType, AUTOMATIC) CanTxPduId)
{
  CanIf_TransmitStateType pnTxState;
  uint8 pnPduLength;
  pnTxState = CANIF_DO_TRANSMIT;

  /* Get the DLC, can include PnWuFlag */
  pnPduLength = CANIF_CFG_TX_DLC(CanTxPduId);

  /* #100 Determine basing on state of Tx-PDU filter of corresponding CAN channel whether the Tx-PDU may be transmitted or NOT */
  if (CANIF_CFG_ISFEATUREPNWUTXPDUFILTERENABLED(CanIf_Controller_Value)) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
  {
    /* CANIF750 */
    if (CanIf_IsPnWuTxPduFilterActive(CanIf_Controller_Value))
    {
      if ((pnPduLength & CANIF_PN_WU_FLAG_GET) == 0u)
      {
        /* TxPdu does not pass the PnWuFilter -> transmission not allowed */
        pnTxState = CANIF_DO_NOT_TRANSMIT;
      }
    }
  }

  return pnTxState;
}
#endif /* (CANIF_PN_WU_TX_PDU_FILTER == STD_ON) */


#if (CANIF_META_DATA_TX_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  CanIf_TransmitSubHandleMetaData()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_TransmitSubHandleMetaData(P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_MSG_VAR) PduInfoPtr, P2VAR(Can_PduType, AUTOMATIC, AUTOMATIC) localPduPtr)
{
  uint8 startPos;
  uint8 endPos;
  Can_IdType localId;

  /* #100 Tx-PDU has meta data configured? */
  if(CANIF_CFG_TX_TXMETADATALENGTH(localPduPtr->swPduHandle) > 0u)
  {
    localId = 0;
    endPos = (uint8)(PduInfoPtr->SduLength); /* ESCAN00074166 */

    /* #200 Extract the meta data from the payload according to configuration */
    if (PduInfoPtr->SduLength >= CANIF_CFG_TX_TXMETADATALENGTH(localPduPtr->swPduHandle)) /* Not applicable if the DLC is too short */
    {
      startPos =  (uint8)((PduInfoPtr->SduLength) - 1u);  /* DLC - 1 */
      endPos = (uint8)(endPos - CANIF_CFG_TX_TXMETADATALENGTH(localPduPtr->swPduHandle)); /* DLC - MetaDataLength */

      /* #210 Calculate the CAN identifier from extracted meta data */
      while(startPos > endPos) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
      {
        localId |= PduInfoPtr->SduDataPtr[startPos];
        localId = localId << 8;
        startPos--;
      }
      localId |= PduInfoPtr->SduDataPtr[startPos];

      /* #220 Adapt the CAN identifier of Tx-PDU according to calculated one from meta data */
      localPduPtr->id = (Can_IdType)(((localPduPtr->id & CANIF_CFG_TX_CANIDTXMASK(localPduPtr->swPduHandle)) | (localId & (Can_IdType)(~CANIF_CFG_TX_CANIDTXMASK(localPduPtr->swPduHandle))))); /* SBSW_CANIF_9 */
    }
    /* #300 Reduce the Tx-length of PDU by length of extracted meta data */
    localPduPtr->length = endPos; /* SBSW_CANIF_9 */
  }
  else
  /* #400 Not meta data Tx-PDU: Set up the Tx-length of PDU */  
  {
    localPduPtr->length = (uint8)(PduInfoPtr->SduLength); /* SBSW_CANIF_9 */
  }
}
#endif /* (CANIF_META_DATA_TX_SUPPORT == STD_ON) */

#if (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
/***********************************************************************************************************************
 *  CanIf_TransmitSubJ1939DynAddr()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
CANIF_LOCAL_INLINE FUNC(Std_ReturnType, CANIF_CODE) CanIf_TransmitSubJ1939DynAddr(CANIF_CHANNEL_CANTYPE_FIRST P2VAR(Can_PduType, AUTOMATIC, AUTOMATIC)localPduPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
  Std_ReturnType retVal = E_OK;

  /* #100 Do J1939-conform address conversion only for J1939Nm CAN channel */
  if( CANIF_CFG_CTRLJ1939DYNADDRSUPPORT(CanIf_Controller_Value) != CANIF_J1939_DYN_ADDR_DISABLED )
  {
    uint8 da;   /* destinationAddress */
    uint8 sa;   /* sourceAddress */
    uint8 sa_t; /* sourceAddress transformed with lookup table */

    /* #110 Distinguish between standard and extended CAN identifier */
    if(((localPduPtr)->id & CANIF_EXT_CANID_MASK) == CANIF_EXT_CANID_MASK) /* ext. ID */
    {
      /* #200 Extended CAN identifier: */
      if ((((localPduPtr)->id & CANIF_J1939_DATA_PAGE_MASK) != CANIF_J1939_DATA_PAGE_MASK) && (((localPduPtr)->id & CANIF_J1939_PGN_MASK) != CANIF_J1939_AC_PGN))
      {
        /* #210 Destination and source addresses are substituted with J1939 format but not for address claimed */
        if (((localPduPtr)->id & CANIF_J1939_MIN_PDU2_MASK) < CANIF_J1939_MIN_PDU2_MASK)  /* PDU Format 1 (second byte < 0xF0) */
        {
          da = (uint8)(((localPduPtr)->id & CANIF_J1939_DA_MASK) >> 8);
          da = CANIF_VAR_J1939TXADDR_LOOKUP(CanIf_Controller_Value, da);
          if (da == CANIF_J1939_NULL_ADDR)
          {
            errorId = CANIF_E_INVALID_DA;
            retVal = E_NOT_OK;
          }
          (localPduPtr)->id = (Can_IdType)(((localPduPtr)->id & CANIF_J1939_INV_DA_MASK) | (((Can_IdType)da) << 8u)); /* SBSW_CANIF_9 */
          if (((localPduPtr)->id & CANIF_J1939_PGN_MASK) == CANIF_J1939_ACKM_PGN)  /* Acknowledgement message, exchange address in data */
          {
            uint8 ackAddr = CANIF_VAR_J1939TXADDR_LOOKUP(CanIf_Controller_Value, (localPduPtr)->sdu[CANIF_J1939_ACKM_ACKADDR_POS]);
            if (ackAddr == CANIF_J1939_NULL_ADDR)
            {
              errorId = CANIF_E_INVALID_DA;
              retVal = E_NOT_OK;
            }
            if ((localPduPtr)->length > CANIF_J1939_ACKM_ACKADDR_POS)
            {
              (localPduPtr)->sdu[CANIF_J1939_ACKM_ACKADDR_POS] = ackAddr;  /* SBSW_CANIF_29 */
            }
            else
            {
              /* data buffer does not fit */
              errorId = CANIF_E_CONFIG;
              retVal  = E_NOT_OK;
            }
          }
        }

        sa = (uint8)((localPduPtr)->id & CANIF_J1939_SA_MASK);
        sa_t = CANIF_VAR_J1939TXADDR_LOOKUP(CanIf_Controller_Value, sa);

        if ((sa == CANIF_J1939_BROADCAST_ADDR) || ((sa != CANIF_J1939_NULL_ADDR) && (sa_t == CANIF_J1939_NULL_ADDR)) || ((sa == CANIF_J1939_NULL_ADDR) && (((localPduPtr)->id & CANIF_J1939_PGN_MASK) != CANIF_J1939_RQST_PGN))) /* invalid SA or NULL SA for anything but Request */
        {
          errorId = CANIF_E_INVALID_SA;
          retVal = E_NOT_OK;
        }
        (localPduPtr)->id = (Can_IdType)(((localPduPtr)->id & CANIF_J1939_INV_SA_MASK) | sa_t); /* SBSW_CANIF_9 */
      }
    }
#  if (CANIF_J1939_DYN_ADDR_SUPPORT == CANIF_J1939_DYN_ADDR_MIXED_CANID) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
    else
    {
      /* #300 Standard CAN identifier: */
      if( CANIF_CFG_CTRLJ1939DYNADDRSUPPORT(CanIf_Controller_Value) != CANIF_J1939_DYN_ADDR_EXT_CANID )
      {
        /* #310 Only source address is substituted */
        sa = (uint8)((localPduPtr)->id & CANIF_J1939_SA_MASK);
        sa = CANIF_VAR_J1939TXADDR_LOOKUP(CanIf_Controller_Value, sa);
        if (sa == CANIF_J1939_NULL_ADDR)
        {
          errorId = CANIF_E_INVALID_SA;
          retVal = E_NOT_OK;
        }
        (localPduPtr)->id = (Can_IdType)(((localPduPtr)->id & CANIF_J1939_INV_SA_MASK) | sa); /* SBSW_CANIF_9 */
      }
    }
#  endif /* CANIF_J1939_DYN_ADDR_SUPPORT == CANIF_J1939_DYN_ADDR_MIXED_CANID */
  }

#  if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_TRANSMIT_API, errorId);
  }
#  else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif

  return retVal;
} /* PRQA S 6030, 6080 */ /*  MD_MSR_STCYC, MD_MSR_STMIF */
# endif /* (CANIF_EXTENDEDID_SUPPORT == STD_ON) */
#endif /*  (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) */


#if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
/***********************************************************************************************************************
 *  CanIf_TxBufferPrioByCanIdQueuePdu()
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/  
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_TxBufferPrioByCanIdQueuePdu(P2CONST(Can_PduType, AUTOMATIC, CANIF_CBK_DRV_VAR) PduInfoPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanIf_AnyIdxType queueindex = CANIF_CFG_TX_QUEUEINDEX(PduInfoPtr->swPduHandle);
# if (CANIF_USES_VSTDLIB_COPY == STD_OFF)
  PduLengthType i;
# endif

  /* ----- Implementation ----------------------------------------------- */

  /* #100 Store the CAN identifier of the Tx-PDU */
# if((CANIF_SETDYNAMICTXID_API == STD_ON) || (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) || (CANIF_META_DATA_TX_SUPPORT == STD_ON)) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
  CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(queueindex, eQueueParams.eBaseParams.eCanId) = PduInfoPtr->id; /* SBSW_CANIF_6 */
# endif
  /* #110 Store the data length of the Tx-PDU */
  CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(queueindex, eQueueParams.eBaseParams.eSduLength) = PduInfoPtr->length; /* SBSW_CANIF_6 */

  /* #120 Store the payload of the Tx-PDU */
# if (CANIF_USES_VSTDLIB_COPY == STD_ON)
#  if (CANIF_STATIC_FD_TXQUEUE == STD_ON)
  VStdMemCpyRamToRam(CANIF_ADDR_VAR_TXBUFFERPRIOBYCANID_STATFDQUEUE_QUEUEDATA(CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_DATASTARTIDX(PduInfoPtr->swPduHandle)), PduInfoPtr->sdu, PduInfoPtr->length);  /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_CANIF_18 */
#  else
  VStdMemCpyRamToRam(CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(queueindex, eQueueParams.eSdu), PduInfoPtr->sdu, PduInfoPtr->length); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_CANIF_7 */
#  endif /* (CANIF_STATIC_FD_TXQUEUE == STD_ON) */
# else
  for (i = 0; i < PduInfoPtr->length; i++)
  {
#  if (CANIF_STATIC_FD_TXQUEUE == STD_ON)
    CanIf_SetTxQueueData((CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_DATASTARTIDX(PduInfoPtr->swPduHandle))+i, PduInfoPtr->sdu[i]); /* SBSW_CANIF_40 */
#  else
    CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(queueindex, eQueueParams.eSdu[i]) = PduInfoPtr->sdu[i]; /* SBSW_CANIF_6 */
#  endif
  }
# endif /* (CANIF_USES_VSTDLIB_COPY == STD_ON) */
}
#endif


#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
/***********************************************************************************************************************
 *  CanIf_TransmitSubHandleTxResBusy()
 **********************************************************************************************************************/
/*!
 *
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
 *
 *
 *
 */
CANIF_LOCAL_INLINE FUNC (Std_ReturnType, CANIF_CODE) CanIf_TransmitSubHandleTxResBusy(P2CONST(Can_PduType, AUTOMATIC, AUTOMATIC) localPduPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval; 
  CanIf_AnyIdxType hth;
  uint8 errorId;

# if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
  CanIf_TxBufferSizeType writeIdx;
  CanIf_AnyIdxType queueDataStartIdx;
  CanIf_AnyIdxType txBufferCfgIdx;
  CanIf_AnyIdxType txBufferFifoBaseIdx;
  CanIf_AnyIdxType txFifoQueueBaseStartIdx;
# endif
  errorId = CANIF_E_NO_ERROR;
  retval = E_NOT_OK;
  hth = CANIF_CFG_TX_HTH(localPduPtr->swPduHandle);
  /* #100 Is TxPDU a BasicCAN-PDU and has it a buffer? */
  if (CANIF_CFG_MAILBOX_HASTXBUFFER(hth)) /* COV_CANIF_NO_TX_BUFFER */
  {
    /* \trace SPEC-1233, SPEC-1232 */

# if (CANIF_DEV_ERROR_DETECT == STD_ON)
    if ((localPduPtr->sdu == NULL_PTR) && (localPduPtr->length != 0u))
    {
      errorId = CANIF_E_PARAM_POINTER;
    }
    else
# endif
    {
# if ((CANIF_USES_VSTDLIB_COPY != STD_ON) && (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
      PduLengthType i;
# endif
      switch (CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(hth))
      {
# if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
        /* #200 Do PrioByCan queue handling */
        case CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID:
          /* #210 PDU length fits */
#  if (CANIF_STATIC_FD_TXQUEUE == STD_ON)
          if(localPduPtr->length <= CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_MAXDATALENGTH(localPduPtr->swPduHandle))
#  else
          if(localPduPtr->length <= CANIF_STATIC_BUFFER_SIZE)
#  endif
          {
            /* #220 Queue information */
            CanIf_TxBufferPrioByCanIdQueuePdu(localPduPtr); /* SBSW_CANIF_5 */
 
            /* #230 Set queue flag for current PDU and return E_OK */
            (void)CanIf_SetPrioByCanIdTxPduAsQueued(localPduPtr->swPduHandle);
            retval = E_OK;
          }
          else
          /* #240 PDU length does not fit */
          {
#  if (CANIF_DEV_ERROR_DETECT == STD_ON)
            errorId = CANIF_E_PARAM_DLC;
#  endif
            retval = E_NOT_OK;
          }
          break;
# endif
# if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
        /* #300 Do FIFO queue handling */
        case CANIF_TXBUFFER_HANDLINGTYPE_FIFO:
          txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(hth);
          /* #310 Buffer element size big enough to record the data? */
          if(localPduPtr->length <= CANIF_CFG_TXBUFFERFIFO_SIZEOFONEPAYLOADEL(txBufferCfgIdx))
          {
            txBufferFifoBaseIdx = CANIF_CFG_TXBUFFERFIFO_BUFFERBASEIDX((txBufferCfgIdx));
            /* #400 One element of the FIFO free?*/
            if (CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eQueueCounter) < CANIF_CFG_TXBUFFERFIFO_QUEUESIZE(txBufferCfgIdx))
            {
              /* #410 Evaluate FIFO-WriteIdx */
              txFifoQueueBaseStartIdx = CANIF_CFG_TXBUFFERFIFO_QUEUEBASESTARTIDX(txBufferCfgIdx);
              writeIdx = CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eWriteIdx);
              /* #420 Store length of Tx-PDU at FIFO-WriteIdx */
              CANIF_VAR_TXBUFFERFIFO_QUEUEBASE((writeIdx + txFifoQueueBaseStartIdx), eBaseParams.eSduLength) = localPduPtr->length; /* SBSW_CANIF_34 */
#  if ((CANIF_SETDYNAMICTXID_API == STD_ON) || (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) || (CANIF_META_DATA_TX_SUPPORT == STD_ON)) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
              /* #430 Store CanId of Tx-PDU at FIFO-WriteIdx */
              CANIF_VAR_TXBUFFERFIFO_QUEUEBASE((writeIdx + txFifoQueueBaseStartIdx), eBaseParams.eCanId) = localPduPtr->id;         /* SBSW_CANIF_34 */
#  endif  
              /* #440 Store the PDU ID of the Tx-PDU at FIFO-WriteIdx */
              CANIF_VAR_TXBUFFERFIFO_QUEUEBASE((writeIdx + txFifoQueueBaseStartIdx), eTxPduId) = localPduPtr->swPduHandle;          /* SBSW_CANIF_34 */
              /* #450 Evaluate the startindex into the CanIf_TxFifoQueueData */
              queueDataStartIdx = ((uint32_least)writeIdx * (uint32_least)CANIF_CFG_TXBUFFERFIFO_SIZEOFONEPAYLOADEL(txBufferCfgIdx)) + CANIF_CFG_TXBUFFFERFIFO_QUEUEDATASTARTIDX(txBufferCfgIdx);
#  if (CANIF_DEV_ERROR_DETECT == STD_ON)
              /* #460 Check if the actual writeindex + length does not write out of bounds */
              if ((queueDataStartIdx + localPduPtr->length) >  CANIF_CFG_SIZEOF_FIFO_BUFFER) /* COV_CANIF_GENDATA_FAILURE */
              {
                errorId = CANIF_E_FATAL;
                retval = E_NOT_OK;
              }
              else
#  endif
              {
                /* #470 Store data of Tx-PDU at FIFO-WriteIdx */
#  if (CANIF_USES_VSTDLIB_COPY == STD_ON)
                VStdMemCpyRamToRam(CANIF_ADDR_VAR_TXBUFFERFIFO_QUEUEDATA(queueDataStartIdx), localPduPtr->sdu, localPduPtr->length); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_CANIF_32 */
#  else
                for (i = 0u; i < localPduPtr->length; i++)
                {
                  CanIf_SetTxFifoQueueData((queueDataStartIdx+i), localPduPtr->sdu[i]);                                              /* SBSW_CANIF_32 */
                }
#  endif         
#  if CANIF_CANCEL_SUPPORT_API == STD_ON    
                /* #480 Set that the buffered Tx-PDU is valid at FIFO-WriteIdx */
                CANIF_VAR_TXBUFFERFIFO_QUEUEBASE((writeIdx + txFifoQueueBaseStartIdx), eQueued) = 1;   /* SBSW_CANIF_34 */
                /* #490 Set the reference to CanIf_TxQueueIndex2FifoEl */
                CANIF_VAR_SET_TXBUFFERFIFO_QUEUEIDX2FIFOEL(CANIF_CFG_TX_QUEUEINDEX(localPduPtr->swPduHandle), writeIdx );  /* SBSW_CANIF_36 */
#  endif
                /* #500 Increment the FIFO-counter */
                (CANIF_VAR_TXBUFFERFIFO_BUFFERBASE( txBufferFifoBaseIdx, eQueueCounter))++; /* SBSW_CANIF_37 */
                
                /* #510 Increment the FIFO-WriteIdx. */
                (CANIF_VAR_TXBUFFERFIFO_BUFFERBASE( txBufferFifoBaseIdx, eWriteIdx))++; /* SBSW_CANIF_37 */
                if(CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eWriteIdx) == (CANIF_CFG_TXBUFFERFIFO_QUEUESIZE(txBufferCfgIdx)))
                {
                  /* If WriteIdx equals the QueueSize reset it to 0. */
                  CANIF_VAR_TXBUFFERFIFO_BUFFERBASE( txBufferFifoBaseIdx, eWriteIdx) = 0; /* SBSW_CANIF_37 */
                }
                retval = E_OK;
              }
            }
#  if (CANIF_DEV_ERROR_DETECT == STD_ON)                          
            else
            {
              errorId = CANIF_E_FULL_TX_BUFFER_FIFO;
            }
#  endif                        
          }
          else
          {
          /* #600 Do not buffer, return with E_NOT_OK */
#  if (CANIF_DEV_ERROR_DETECT == STD_ON)
            errorId = CANIF_E_PARAM_DLC;
#  endif
            retval = E_NOT_OK;
          }
          break;
# endif            
      default: /* COV_CANIF_GENDATA_FAILURE */
        break; 
      }
    }/* Development error check SduDataPtr == NULL_PTR */
  } 
  else
  {
    /* #110 PduId has no Tx Buffer: Reject the Tx-request */
    retval = E_NOT_OK;
  }
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_TRANSMIT_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif /* ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)) */


/***********************************************************************************************************************
 *  CanIf_TransmitSubWrite()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
CANIF_LOCAL_INLINE FUNC (Std_ReturnType, CANIF_CODE) CanIf_TransmitSubWrite(P2CONST(Can_PduType, AUTOMATIC, AUTOMATIC) localPduPtr)
{
  Std_ReturnType  retval;
  Can_ReturnType txResult;
#if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
  boolean doCanWrite;
#endif
#if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
  txResult = CAN_BUSY;
  doCanWrite = TRUE;
  if( CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(CANIF_CFG_TX_HTH(localPduPtr->swPduHandle)) == CANIF_TXBUFFER_HANDLINGTYPE_FIFO)
  {
    /* #100 If Tx-PDU is mapped to Tx-buffer of handling type FIFO it must only be transmitted directly if FIFO is empty */
    doCanWrite = CanIf_TransmitSubCheckFiFoQueueEmpty(localPduPtr->swPduHandle);
  }
  if (doCanWrite == TRUE)
#endif  
  {
    /* #200 Pass the request to the CAN driver */
#if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
    {
      CanIf_Can_WriteFctType canWriteFct;
      Can_HwHandleType canDrvHth;
                   
      canWriteFct = CanIf_GetCan_WriteFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CANIF_CFG_TX_CONTROLLER(localPduPtr->swPduHandle)));
      canDrvHth = (Can_HwHandleType)(CANIF_CFG_TX_HTH(localPduPtr->swPduHandle) - CANIF_CFG_MULTIPLECANDRV_HXHOFFSET(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CANIF_CFG_TX_CONTROLLER(localPduPtr->swPduHandle))));
                    
      txResult = canWriteFct(canDrvHth, (P2CONST(Can_PduType, AUTOMATIC, CANIF_VAR_STACK))localPduPtr); /* SBSW_CANIF_46 */
    }
#else
    txResult = Can_Write((CanIf_HwHandleType)CANIF_CFG_TX_HTH(localPduPtr->swPduHandle), (P2CONST(Can_PduType, AUTOMATIC, CANIF_VAR_STACK))localPduPtr); /* SBSW_CANIF_5 */
#endif
  }
  if (txResult == CAN_BUSY)
  {
#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
    /* #300 CAN driver is busy, do the queueing according to the selected queueing method */
    /* \trace SPEC-3668 */
    retval = CanIf_TransmitSubHandleTxResBusy(localPduPtr); /* SBSW_CANIF_5 */
#else
    retval = E_NOT_OK;  /* ESCAN00092426 */
#endif /* ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)) */
  }
  else if (txResult == CAN_NOT_OK)
  {
    /* #400 CAN driver reports FAILED: Reject the Tx-request */
    retval = E_NOT_OK;
  }
  else
  {
    /* \trace SPEC-1903 */
   /* #500 CAN driver reports SUCCEEDED: */
    /* ESCAN00066390 - start */
#if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
    /* #510 If a Tx-PDU mapped to a PRIO_BY_CANID-Tx-buffer was transmitted do clear the corresponding queue flag */
    if(CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(CANIF_CFG_TX_HTH(localPduPtr->swPduHandle)) == CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID) /* COV_CANIF_NO_TX_BUFFER */
    {
      (void)CanIf_ClearPrioByCanIdTxPduAsQueued(localPduPtr->swPduHandle);
    }
#endif
    /* ESCAN00066390 - end */
    retval = E_OK;
  } /* txResult == CAN_OK */
  return retval;
}


/***********************************************************************************************************************
 *  CanIf_Transmit()
 **********************************************************************************************************************/
/*!
 *
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
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Transmit(PduIdType CanTxPduId, P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_MSG_VAR)PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK;
  uint8 errorId = CANIF_E_NO_ERROR;
#if (CANIF_DATA_CHECKSUM_TX_SUPPORT == STD_ON)    
  uint8 txPduDataWithChecksum[CANIF_CFG_MAXTXDLC_PLUS_DATACHECKSUM];
#endif
  Can_PduType     localPdu;
#if CANIF_SETDYNAMICTXID_API == STD_ON
  PduIdType     DynamicPduId;
#endif
  CANIF_CHANNEL_CANTYPE_LOCAL
    
  /* ----- Development Error Checks ------------------------------------- */
#if ((CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON))
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
#endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON) */
#if ((CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME) || (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))
# if (CANIF_DEV_ERROR_DETECT == STD_ON) 
  /* #10 Check if parameter CanTxPduId is valid if a CanTxPduId indirection is done. */
  if (CanTxPduId >= CANIF_CFG_MAX_ULTXPDUS)
  {
    /* \trace SPEC-2007 */
    errorId = CANIF_E_INVALID_TXPDUID;
  }
  else
# endif
  {
    /* for PB and LT configurations the TxPduId order between CanIf and higher layers may differ and needs to be indirected */
    CanTxPduId = CANIF_CFG_TXPDUID2INTTXPDUID(CanTxPduId); /* PRQA S 1338 */ /* MD_CanIf_Rule17.8 */
#endif
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
    /* #20 Check if parameter CanTxPduId is valid. */
    if (CanTxPduId >= CANIF_CFG_MAX_TXPDUS)
    {
      /* \trace SPEC-2007 */
      errorId = CANIF_E_INVALID_TXPDUID;
    }
    else
#endif        
    {
#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
      /* Determine the CAN controller channel */
      controller = CANIF_CFG_TX_CONTROLLER(CanTxPduId);
#endif

#if (CANIF_DEV_ERROR_DETECT == STD_ON)
      /* #30 Check if parameter PduInfoPtr is valid. */
      if (PduInfoPtr == NULL_PTR)
      {
        /* \trace SPEC-2003 */
        errorId = CANIF_E_PARAM_POINTER;
      }
      /* #40 Check if CAN channel is initialized. */
      else if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
      {
        errorId = CANIF_E_UNINIT;
        /* retval default E_NOT_OK  */
      }
      else
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#  if (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
      /* #50 Check if corresponding CanDrv is available in current identity. */
      if (!CANIF_CFG_IS_CANDRVINDEXVALID(CanIf_Controller_Value_Local))
      {
        errorId = CANIF_E_PARAM_CONTROLLERID;
      }
      else
#  endif
# endif
#endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) */
      {
        
        /* ----- Implementation ----------------------------------------------- */
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
        CanIf_TransmitStateType pnTxState;
#endif

#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
        /* Check whether transmission is allowed or not */
        pnTxState = CanIf_TransmitSubHandleTxPduFilter(CANIF_CHANNEL_CANPARA_FIRST_LOCAL CanTxPduId);
        if (pnTxState == CANIF_DO_TRANSMIT)
#endif
        {
          /* #120 Process only if CAN channel is active */
          if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_STARTED)
          {
            /* Check PDU mode */
            /* \trace SPEC-1849, SPEC-3854, SPEC-3765, SPEC-1850 */
            if ((CanIf_GetChannelMode(CanIf_Controller_Value_Local) == CANIF_GET_ONLINE) ||
              (CanIf_GetChannelMode(CanIf_Controller_Value_Local) == CANIF_GET_TX_ONLINE)
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
              || (CanIf_GetChannelMode(CanIf_Controller_Value_Local) == CANIF_GET_ONLINE_WAKF)
              || (CanIf_GetChannelMode(CanIf_Controller_Value_Local) == CANIF_GET_TX_ONLINE_WAKF)
#endif
              )
            {
              /* \trace SPEC-1227 */
              /* #130 Process the Tx-request only within critical section */
              CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_4);

              /* #140 Depending on type of Tx-PDU (dynamic / static) get the CAN identifier */
#if (CANIF_SETDYNAMICTXID_API == STD_ON)
              DynamicPduId = CANIF_CFG_STAT2DYN_INDIRECTION(CanTxPduId);
              if(DynamicPduId != CanIf_TxPduHnd_INVALID)
              {
                (localPdu).id = CANIF_VAR_DYNTXID(DynamicPduId);
              }
              else
              {
                (localPdu).id = CANIF_CFG_TX_CANID(CanTxPduId);
              }
#else
              (localPdu).id = CANIF_CFG_TX_CANID(CanTxPduId);
#endif

              localPdu.sdu = (PduInfoPtr->SduDataPtr);
              localPdu.swPduHandle = (CanTxPduId);

#if (CANIF_META_DATA_TX_SUPPORT == STD_ON)
              /* #150 Handle meta data of Tx-PDU (only if configured) */
              CanIf_TransmitSubHandleMetaData(PduInfoPtr, &localPdu); /* SBSW_CANIF_5 */
#else
              localPdu.length = (uint8)(PduInfoPtr->SduLength);
#endif
  
              /* Tx object is FullCAN (will not be queued) - do direct Tx */
              /* no Tx Buffer -                              do always direct Tx */
              /* (const Can_PduType*) cast required (No Compiler abstraction, target is on stack (RAM)
              * const to mark it read-only / CA cast (-> to get the const )
              * */
              /* \trace SPEC-2006, SPEC-1845, SPEC-1917 */ /* UREQ00000014, B50a */
#if (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
# if  (CANIF_EXTENDEDID_SUPPORT == STD_ON)
              /* #160 Adapt the CAN identifier according to J1939 specification (only if configured) */
              retval = CanIf_TransmitSubJ1939DynAddr(CANIF_CHANNEL_CANPARA_FIRST_LOCAL &localPdu); /* SBSW_CANIF_5 */
              if (retval == E_OK)
# endif
#endif
              {
#if (CANIF_DATA_CHECKSUM_TX_SUPPORT == STD_ON)
                /* #170 Is data checksum Tx-PDU? (only if configured) */
                if (CANIF_CFG_TX_ISDATACHECKSUMPDU(CanTxPduId))
                {
                  /* #180 Calculate data checksum. */
                  CanIf_TransmitSubDataChecksumTxAppend(&localPdu, &txPduDataWithChecksum[0]); /* SBSW_CANIF_31 */

                  /* #190 Adapt that Tx-PDU is transmitted including checksum. */
                  localPdu.sdu = (P2VAR(uint8, TYPEDEF, CAN_APPL_VAR))(&txPduDataWithChecksum[0]);
                }
#endif /* (CANIF_DATA_CHECKSUM_TX_SUPPORT == STD_ON) */
                retval = CanIf_TransmitSubWrite(&localPdu); /* SBSW_CANIF_5 */
              }
              /* \trace SPEC-1227 */
              CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_4);
            } /* Check PDU mode */
            /* \trace SPEC-1848 */
            else if ((CanIf_GetChannelMode(CanIf_Controller_Value_Local) == CANIF_GET_OFFLINE_ACTIVE) ||
                    (CanIf_GetChannelMode(CanIf_Controller_Value_Local) == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE))
            {
              retval = E_OK;
              /* \trace SPEC-5215 */
              /* #200 If current mode is Tx-passive call the Tx-confirmation */
              CanIf_HlTxConfirmation(CanTxPduId);
            }
            else /* CANIF_GET_OFFLINE or CANIF_GET_RX_ONLINE */
            {
              /* \trace SPEC-3673 */
              /* default retval = E_NOT_OK */
              errorId = CANIF_E_STOPPED;
            }
          } /* if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_STARTED) */
          /* \trace SPEC-5339 */
          else if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_STOPPED)
          {
            /* If current mode is STOP do report DET */
            errorId = CANIF_E_STOPPED;
          }
          else
          {
            /*  CtrlMode here can only be CANIF_CS_SLEEP, transmit is not allowed */
            /* default retval = E_NOT_OK; */
          }
        }
      }
    }
#if ((CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME) || (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))     
  } 
#endif  
  /* ----- Development Error Report --------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_TRANSMIT_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  
  return retval;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  CanIf_HlTxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
CANIF_LOCAL FUNC(void, CANIF_CODE) CanIf_HlTxConfirmation(PduIdType CanTxPduId)
{

  /* ----- Local Variables ---------------------------------------------- */
  /* conform to requirement \trace SPEC-1877 */
  CanIf_TxConfFctListIdxType index;
  PduIdType upperLayerTxPduId;
  CanIf_TxConfirmationFctType txConfirmationFct;

  /* ----- Implementation ----------------------------------------------- */
  
  /* #100 Get the Tx-confirmation function */
  index = CANIF_CFG_TX_TXCONFIRMATION(CanTxPduId);

  /* #110 Convert the CanIf internal TxPduId to the upper layer one */
  upperLayerTxPduId = CANIF_CFG_TX_UPPERLAYERTXPDUID(CanTxPduId);

  txConfirmationFct = CANIF_CFG_TXCONFIRMATION(index);

  if (txConfirmationFct != NULL_PTR)
  {
    /* #120 If configured, call the Tx-confirmation function */
      txConfirmationFct(upperLayerTxPduId);  /* SBSW_CANIF_11 */   
  }
}


/* \trace SPEC-3686 */
/**********************************************************************************************************************
 *  CanIf_TxConfirmation()
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
 */
FUNC(void, CANIF_CODE) CanIf_TxConfirmation(PduIdType CanTxPduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* \trace SPEC-3701 */
  /* ----- Development Error Checks ------------------------------------- */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif
  /* #20 Check if parameter CanTxPduId is valid */
  if (CanTxPduId >=  CANIF_CFG_MAX_TXPDUS)
  {
    /* \trace SPEC-3700 */
    errorId = CANIF_E_PARAM_LPDU;
  }
  /* #30 Check if corresponding CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CANIF_CFG_TX_CONTROLLER(CanTxPduId)) == CANIF_CS_UNINIT )
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#  if (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CANIF_CFG_TX_CONTROLLER(CanTxPduId)))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#  endif  
# endif
  else
#endif
  {
    /* \trace SPEC-3703 */
    /* ----- Implementation ----------------------------------------------- */
    /* #100 Process only if CAN channel is active */
    if (CanIf_GetCtrlMode(CANIF_CFG_TX_CONTROLLER(CanTxPduId)) == CANIF_CS_STARTED)
    {
      if ( (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(CanTxPduId)) == CANIF_GET_ONLINE) ||
             (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(CanTxPduId)) == CANIF_GET_TX_ONLINE)
# if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
        || (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(CanTxPduId)) == CANIF_GET_ONLINE_WAKF)
        || (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(CanTxPduId)) == CANIF_GET_TX_ONLINE_WAKF)
# endif
         )
      {
#if ((CANIF_PN_WU_TX_PDU_FILTER == STD_ON) || (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON))
        CANIF_CHANNEL_CANTYPE_LOCAL
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
        controller = CANIF_CFG_TX_CONTROLLER(CanTxPduId);
# endif
#endif

#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
        /* CANIF751 */
        /* #110 Deactivate Tx-PDU-filter */
        CanIf_SetPnWuTxPduFilterActive(CanIf_Controller_Value_Local, FALSE); /* SBSW_CANIF_8 */
#endif

#if (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON)
        /* \trace SPEC-9981 */
        /* #120 Log that any Tx-confirmation occurred */
        CanIf_SetTxConfState(CanIf_Controller_Value_Local, CANIF_TX_RX_NOTIFICATION);  /* SBSW_CANIF_8 */
#endif


#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
        {
          CanIf_AnyIdxType hth;
          hth = CANIF_CFG_TX_HTH(CanTxPduId);
          /* \trace SPEC-3676 */
          /* Check if Tx-queue is affected (BasicCAN Tx-PDU which has a buffer) */
          if (CANIF_CFG_MAILBOX_HASTXBUFFER(hth)) /* COV_CANIF_NO_TX_BUFFER */
          {
            /* #130 If transmission of a BasicCAN PDU, which has a buffer, was confirmed, handle the Tx-queue (critical section is used) */
            /* \trace SPEC-1227 */
            CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_2);
            /* \trace SPEC-5275, SPEC-1231 */
            
            /* parameter hth out of CanTxPduId */
            (void)CanIf_TxQueueTreatment((CanIf_HwHandleType)hth);
            /* \trace SPEC-1227 */ /* lock over queue handling + write call (driver does not expect direct call inbetween) */
            CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_2);
          }
        }
#endif
        /* \trace SPEC-3666 */
        /* #140 Inform upper layer about transmitted PDU */
        CanIf_HlTxConfirmation(CanTxPduId);
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_TXCONFIRMATION_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


#if  (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  CanIf_RxIndicationSubJ1939DynAddr()
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
 */
CANIF_LOCAL_INLINE FUNC(Std_ReturnType, CANIF_CODE) CanIf_RxIndicationSubJ1939DynAddr(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams)
{
  /* ----- Local Variables ---------------------------------------------- */
  CANIF_CHANNEL_CANTYPE_LOCAL
  uint8 errorId = CANIF_E_NO_ERROR;
  Std_ReturnType retVal = E_OK;

#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CanIf_Controller_Value_Local = CANIF_CFG_MAILBOX_CONTROLLER(rxSearchParams->eHrh);
#  endif

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Do J1939-conform address conversion only for J1939Nm CAN channel */
  if( CANIF_CFG_CTRLJ1939DYNADDRSUPPORT(CanIf_Controller_Value_Local) != CANIF_J1939_DYN_ADDR_DISABLED )
  {
    uint8 da;   /* destinationAddress */
    uint8 sa;   /* sourceAddress */
    uint8 sa_t; /* sourceAddress transformed with lookup table */

    /* #110 Distinguish between standard and extended CAN identifier */
    if(((rxSearchParams->eCanId) & CANIF_EXT_CANID_MASK) == CANIF_EXT_CANID_MASK) /* ext. ID */
    {
      /* #200 Extended CAN identifier: */
      if ((((rxSearchParams->eCanId) & CANIF_J1939_DATA_PAGE_MASK) != CANIF_J1939_DATA_PAGE_MASK) && (((rxSearchParams->eCanId) & CANIF_J1939_PGN_MASK) != CANIF_J1939_AC_PGN))   /* J1939 format and not AddressClaimed */
      {
        /* #210 Destination and source addresses are substituted with J1939 format but not for address claimed (critical section is used)*/
        /* Critical section is required to ensure consistency for the pair: da and sa_t */
        CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_7);

        if (((rxSearchParams->eCanId) & CANIF_J1939_MIN_PDU2_MASK) < CANIF_J1939_MIN_PDU2_MASK)  /* PDU Format 1 (second byte < 0xF0) */
        {
          da = (uint8)(((rxSearchParams->eCanId) & CANIF_J1939_DA_MASK) >> 8);
          da = CANIF_VAR_J1939RXADDR_LOOKUP(CanIf_Controller_Value_Local, da);
          if (da == CANIF_J1939_NULL_ADDR)
          {
            errorId = CANIF_E_INVALID_DA;
            retVal = E_NOT_OK;
          }
          (rxSearchParams->eCanId) = (Can_IdType)(((rxSearchParams->eCanId) & CANIF_J1939_INV_DA_MASK) | (((Can_IdType)da) << 8u));  /* SBSW_CANIF_9 */
        }

        sa = (uint8)((rxSearchParams->eCanId) & CANIF_J1939_SA_MASK);
        sa_t = CANIF_VAR_J1939RXADDR_LOOKUP(CanIf_Controller_Value_Local, sa);

        CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_7);

        if ((sa == CANIF_J1939_BROADCAST_ADDR) || ((sa != CANIF_J1939_NULL_ADDR) && (sa_t == CANIF_J1939_NULL_ADDR)) || ((sa == CANIF_J1939_NULL_ADDR) && (((rxSearchParams->eCanId) & CANIF_J1939_PGN_MASK) != CANIF_J1939_RQST_PGN))) /* invalid SA or NULL SA for anything but Request */
        {
          errorId = CANIF_E_INVALID_SA;
          retVal = E_NOT_OK;
        }
        (rxSearchParams->eCanId) = (Can_IdType)(((rxSearchParams->eCanId) & CANIF_J1939_INV_SA_MASK) | sa_t); /* SBSW_CANIF_9 */
      }
    }
#  if (CANIF_J1939_DYN_ADDR_SUPPORT == CANIF_J1939_DYN_ADDR_MIXED_CANID)
    else
    {
      /* #300 Standard CAN identifier: */
      if( CANIF_CFG_CTRLJ1939DYNADDRSUPPORT(CanIf_Controller_Value_Local) == CANIF_J1939_DYN_ADDR_MIXED_CANID )
      {
        /* #310 Only source address is substituted */
        sa = (uint8)((rxSearchParams->eCanId) & CANIF_J1939_SA_MASK);
        sa = CANIF_VAR_J1939RXADDR_LOOKUP(CanIf_Controller_Value_Local, sa);
        if (sa == CANIF_J1939_NULL_ADDR)
        {
          errorId = CANIF_E_INVALID_SA;
          retVal = E_NOT_OK;
        }
        (rxSearchParams->eCanId) = (Can_IdType)(((rxSearchParams->eCanId) & CANIF_J1939_INV_SA_MASK) | sa); /* SBSW_CANIF_9 */
      }
    }
#  endif /* CANIF_J1939_DYN_ADDR_SUPPORT == CANIF_J1939_DYN_ADDR_MIXED_CANID */
  }

#  if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, errorId);
  }
#  else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif
#endif


#if (CANIF_SEARCH_ALGORITHM == CANIF_BINARY)
/**********************************************************************************************************************
 *  CanIf_RxIndicationSubBinarySearch()
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
 */
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubBinarySearch(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams)
{
  /* ----- Local Variables ---------------------------------------------- */
  PduIdType firstRxPduId;
  PduIdType lastRxPduId;
  PduIdType midRxPduId;
  PduIdType resultId;
  /* init resultId */
  resultId = CanIf_RxPduHnd_INVALID;

  /* ----- Implementation ----------------------------------------------- */

  /* #100 Determine the search range */
  firstRxPduId = CANIF_CFG_MAILBOX_PDUIDFIRST(rxSearchParams->eHrh);
  lastRxPduId = rxSearchParams->eRxPduId;

  /* #110 Run through the whole search range */
  while (firstRxPduId <= lastRxPduId)   /* COV_CANIF_GENDATA_FAILURE */
  {
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
    sint32 diffId;
# else
    sint16 diffId;
# endif
    /* #120 Calculate the middle of the search range */
    midRxPduId = (PduIdType)((lastRxPduId + firstRxPduId) >> 1);

    /* #130 Calculate the difference of CAN identifiers: the one to be looked for and the "middle" one */
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
    diffId = (sint32)rxSearchParams->eCanId - (sint32)CANIF_CFG_RX_CANID(midRxPduId);
# else
    diffId = (sint16)rxSearchParams->eCanId - (sint16)CANIF_CFG_RX_CANID(midRxPduId);
# endif

    /* #140 Determine from the calculated difference: if and where to search the next */
    if (diffId == 0)
    {
      resultId = midRxPduId;
      break;
    }
    else if (diffId > 0)
    {
      lastRxPduId = midRxPduId;
    }
    else
    {
      firstRxPduId = midRxPduId;
    }

    /* #150 If only two objects left do verify them for matching */
    if((lastRxPduId - firstRxPduId) < 2u)
    {
      if(rxSearchParams->eCanId == CANIF_CFG_RX_CANID(firstRxPduId))
      {
        resultId = firstRxPduId;
        break; /* PRQA S 0771 */ /* MD_CanIf_Rule15.4 */
      }
      else if(rxSearchParams->eCanId == CANIF_CFG_RX_CANID(lastRxPduId))
      {
        resultId = lastRxPduId;
        break; /* PRQA S 0771 */ /* MD_CanIf_Rule15.4 */
      }
      else
      {
        break; /* PRQA S 0771 */ /* MD_CanIf_Rule15.4 */
      }
    }
  } /* while (first <= last)*/

  if (resultId != CanIf_RxPduHnd_INVALID)
  {
    /* #160 If matched Tx-PDU found verify the message type regarding FD format (only if configured) */
# if (CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON)
    /* Set for possible match-candidate */
    rxSearchParams->eRxPduIdMatch = resultId; /* SBSW_CANIF_9 */
    CanIf_RxIndicationSubBinarySearchSubCheckMsgType(rxSearchParams); /* SBSW_CANIF_5 */
# else
    /* \trace SPEC-3677, SPEC-1230 */
    rxSearchParams->eRxPduIdMatch = resultId; /* SBSW_CANIF_9 */
    rxSearchParams->eContinueSearch = FALSE; /* no range search necessary */ /* SBSW_CANIF_9 */
# endif
  }
}

 
# if (CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON)
/**********************************************************************************************************************
 *  CanIf_RxIndicationSubBinarySearchSubCheckMsgType()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 * NOTE:
 * - rxSearchParams->eContinueSearch == FALSE -> signals match FOUND otherwise NOT found
 * - Within rxSearchParams->eRxPduIdMatch already possible match-candidate is stored. If NO message-type-match found then this one must be set to CanIf_RxPduHnd_INVALID!
 */
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubBinarySearchSubCheckMsgType(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams)
{
  /* #100 Verify the message type regarding FD format */
  if ((CANIF_CFG_RX_MSGTYPE(rxSearchParams->eRxPduIdMatch) == CANIF_MSG_TYPE_CAN) || (CANIF_CFG_RX_MSGTYPE(rxSearchParams->eRxPduIdMatch) == rxSearchParams->eRxMsgType))
  {
    /* \trace SPEC-3677, SPEC-1230 */
    /* eRxPduIdMatch already set correctly */
    rxSearchParams->eContinueSearch = FALSE; /* no range search necessary */ /* SBSW_CANIF_9 */
  }
  else
  {
    /* #110 If message type does NOT match verify the "neighbours" for matching of CAN identifier and message type (only if configured) */
    if(rxSearchParams->eRxPduIdMatch < CANIF_CFG_MAILBOX_PDUIDLAST(rxSearchParams->eHrh)) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
    {
      /* Verify the UPPER neighbor: CAN identifier */
      if(rxSearchParams->eCanId == CANIF_CFG_RX_CANID(rxSearchParams->eRxPduIdMatch + 1u)) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
      {
        /* Verify the UPPER neighbor: message type */
        /* There must not be two different Rx-PDUs configured with the same CAN ID and the same FD identifier but who knows -> redundant validation */
        if(CANIF_CFG_RX_MSGTYPE(rxSearchParams->eRxPduIdMatch + 1u) == rxSearchParams->eRxMsgType) /* COV_CANIF_GENDATA_FAILURE */
        {
          rxSearchParams->eRxPduIdMatch = rxSearchParams->eRxPduIdMatch + 1u; /* SBSW_CANIF_9 */
          rxSearchParams->eContinueSearch = FALSE; /* no range search necessary */ /* SBSW_CANIF_9 */
        }
      }
    }

    if(rxSearchParams->eContinueSearch == TRUE) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
    {
      if(rxSearchParams->eRxPduIdMatch > CANIF_CFG_MAILBOX_PDUIDFIRST(rxSearchParams->eHrh) )
      {
        /* Verify the LOWER neighbor: CAN identifier */
        if(rxSearchParams->eCanId == CANIF_CFG_RX_CANID(rxSearchParams->eRxPduIdMatch - 1u)) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
        {
          /* Verify the LOWER neighbor: message type */
          /* There must not be two different Rx-PDUs configured with the same CAN ID and the same FD identifier but who knows -> redundant validation */
          if(CANIF_CFG_RX_MSGTYPE(rxSearchParams->eRxPduIdMatch - 1u) == rxSearchParams->eRxMsgType) /* COV_CANIF_GENDATA_FAILURE */
          {
            rxSearchParams->eRxPduIdMatch = rxSearchParams->eRxPduIdMatch - 1u; /* SBSW_CANIF_9 */
            rxSearchParams->eContinueSearch = FALSE; /* no range search necessary */ /* SBSW_CANIF_9 */
          }
        }
      }
    }

    /* Verify whether any match found? */
    if (rxSearchParams->eContinueSearch == TRUE)
    {
      /* NO match found */
      rxSearchParams->eRxPduIdMatch = CanIf_RxPduHnd_INVALID; /* SBSW_CANIF_9 */
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* (CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON) */
#endif /* CANIF_SEARCH_ALGORITHM == CANIF_BINARY */


#if (CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH)
/**********************************************************************************************************************
 *  CanIf_RxIndicationSubDoubleHashSearch()
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
 */
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubDoubleHashSearch(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams)
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_IdType hash1;
  Can_IdType hash2;
  uint16_least dhCalcRxPduId; /* ESCAN00087755 */
  uint8 errorId = CANIF_E_NO_ERROR; /* ESCAN00087755 */

  /* ----- Implementation ----------------------------------------------- */
  /* \trace SPEC-3746 */
  /* \trace SPEC-1911 */
  /* #100 Calculate the RxPduId basing on received CAN identifier and the double hash numbers */
  hash1 = (rxSearchParams->eCanId ^ (Can_IdType)CANIF_CFG_RXDHRANDOMNUMBER1(CANIF_CFG_MAILBOX_CONTROLLER(rxSearchParams->eHrh))) % (Can_IdType)CANIF_CFG_RXDHADJUSTCOUNT;
  hash2 = (rxSearchParams->eCanId ^ (Can_IdType)CANIF_CFG_RXDHRANDOMNUMBER2(CANIF_CFG_MAILBOX_CONTROLLER(rxSearchParams->eHrh))) % (Can_IdType)CANIF_CFG_RXDHADJUSTCOUNT;
  dhCalcRxPduId = (uint16_least)CANIF_CFG_RXDHADJUST(hash1) + (uint16_least)CANIF_CFG_RXDHADJUST(hash2);

  if (dhCalcRxPduId >= CANIF_CFG_MAX_RXPDUS) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
  {
    /* #110 If calculated RxPduId exceeds the number of configured Rx-PDUs reduce the calculated one by number of Rx-PDUs */
    rxSearchParams->eRxPduId = (PduIdType)(dhCalcRxPduId - CANIF_CFG_MAX_RXPDUS); /* SBSW_CANIF_9 */
  }
  else
  {
    rxSearchParams->eRxPduId = (PduIdType)(dhCalcRxPduId); /* SBSW_CANIF_9 */
  }

  /* #120 Verify the CAN identifier for matching */
  if (CANIF_CFG_RX_CANID(rxSearchParams->eRxPduId) == rxSearchParams->eCanId)
  {
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
    /* #10 Check if the matched RxPduId calculated via double hash is in valid range (== matches the corresponding CAN channel, ESCAN00087755). */
    if ((rxSearchParams->eRxPduId >= CANIF_CFG_MAILBOX_PDUIDFIRST(rxSearchParams->eHrh)) && (rxSearchParams->eRxPduId <= CANIF_CFG_MAILBOX_PDUIDLAST(rxSearchParams->eHrh))) /* COV_CANIF_GENDATA_FAILURE */
# endif
    {
      /* #130 If CAN identifier matches verify the message type regarding FD format (only if configured) */
# if (CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON)
      if ((CANIF_CFG_RX_MSGTYPE(rxSearchParams->eRxPduId) == CANIF_MSG_TYPE_CAN) || (CANIF_CFG_RX_MSGTYPE(rxSearchParams->eRxPduId) == rxSearchParams->eRxMsgType))
# endif
      {
        /* \trace SPEC-3677 */ /* ID matches - Pdu identified */
        rxSearchParams->eRxPduIdMatch = rxSearchParams->eRxPduId;  /* SBSW_CANIF_9 */
        rxSearchParams->eContinueSearch = FALSE; /* no range search necessary */ /* SBSW_CANIF_9 */
      }
# if (CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON)
      else
      {
        /* #140 If message type does NOT match verify the CAN identifier and message type of the lower neighbour one (only if configured) */
        /* Make sure that eRxPduId does not point on the last Basic CAN ID with decided CAN Identifier, increment does not effect pointer on range */
        if(rxSearchParams->eRxPduId > CANIF_CFG_MAILBOX_PDUIDFIRST(rxSearchParams->eHrh))
        {
          rxSearchParams->eRxPduId--;  /* for double hash the hash hits always for the msg with the higher prio if the CAN ID exist for two times */ /* SBSW_CANIF_9 */
          if ((CANIF_CFG_RX_CANID(rxSearchParams->eRxPduId) & (~CANIF_FDFLAG)) == rxSearchParams->eCanId) /* Fix of ESCAN00092931 */
          {
            if(CANIF_CFG_RX_MSGTYPE(rxSearchParams->eRxPduId) == rxSearchParams->eRxMsgType) /* COV_CANIF_GENDATA_FAILURE */
            {
              /* \trace SPEC-3677 */ /* ID matches - Pdu identified */
              rxSearchParams->eRxPduIdMatch = rxSearchParams->eRxPduId; /* SBSW_CANIF_9 */
              rxSearchParams->eContinueSearch = FALSE; /* no range search necessary */ /* SBSW_CANIF_9 */
            }
          }
        }
      }
# endif
    }
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* #20 The RxPduId calculated via double hash algorithm is NOT in valid range. Report this error. */
      errorId = CANIF_E_INVALID_DOUBLEHASH_CALC;
    }
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* COV_CANIF_GENDATA_FAILURE */
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH */


#if (CANIF_SEARCH_ALGORITHM == CANIF_LINEAR)
/**********************************************************************************************************************
 *  CanIf_RxIndicationSubLinearSearch()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubLinearSearch(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
{
  /* \trace SPEC-3746 */
  /* \trace SPEC-1911 */
  /* Basic CAN message */
  /* Checked for invalid RxPduId earlier */

  /* ----- Implementation ----------------------------------------------- */

  /* #100 Run linear through whole search area until the first Rx-range */
  while (((CANIF_CFG_RX_MASK(rxSearchParams->eRxPduId) & CANIF_RANGE_FLAG) != CANIF_RANGE_FLAG)) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
  {
    /* #110 Check the CAN identifier for matching */
    if (CANIF_CFG_RX_CANID(rxSearchParams->eRxPduId) == rxSearchParams->eCanId)
    {
      /* #120 If CAN identifier matches verify the message type regarding FD format (only if configured) */
# if (CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON)
      if ((CANIF_CFG_RX_MSGTYPE(rxSearchParams->eRxPduId)  == CANIF_MSG_TYPE_CAN) || (CANIF_CFG_RX_MSGTYPE(rxSearchParams->eRxPduId) == rxSearchParams->eRxMsgType))
# endif
      {
        /* ID matches - Pdu identified */ /* \trace SPEC-3677 */
        rxSearchParams->eRxPduIdMatch = rxSearchParams->eRxPduId; /* SBSW_CANIF_9 */
        rxSearchParams->eContinueSearch = FALSE; /* no range search necessary */ /* SBSW_CANIF_9 */
        break;
      }
    }

    if ((CANIF_CFG_RX_MASK(rxSearchParams->eRxPduId) & CANIF_STOP_FLAG) != 0u)  /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
    {
      /* #130 If search range completed do break the search */
      rxSearchParams->eContinueSearch = FALSE; /* no range search necessary */ /* SBSW_CANIF_9 */
      break; /* PRQA S 0771 */ /* MD_CanIf_Rule15.4 */
    }
    else
    {
      rxSearchParams->eRxPduId--; /* SBSW_CANIF_9 */
    }
  }
}
#endif /* CANIF_SEARCH_ALGORITHM == CANIF_LINEAR */


/**********************************************************************************************************************
 *  CanIf_RxIndicationSubReceptionPduMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
CANIF_LOCAL_INLINE FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_RxIndicationSubReceptionPduMode(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams)
{
  CanIf_NotifStatusType retVal;
#if (CANIF_SET_PDU_RECEPTION_MODE_SUPPORT == STD_ON) || (CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON)
  retVal = CANIF_NO_NOTIFICATION;
#endif
#if (CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON)
  /* #100 Check the message type regarding FD format (only if configured) */ 
  if ((CANIF_CFG_RX_MSGTYPE(rxSearchParams->eRxPduId)  == CANIF_MSG_TYPE_CAN) || (CANIF_CFG_RX_MSGTYPE(rxSearchParams->eRxPduId) == rxSearchParams->eRxMsgType))
#endif
  {
#if (CANIF_SET_PDU_RECEPTION_MODE_SUPPORT == STD_ON)
    /* #200 Check the PDU reception mode */
    if (CANIF_CFG_RX_ISRECEPTIONMODEPDU(rxSearchParams->eRxPduId))
    {
      if (CANIF_VAR_GET_PDU_RECEPTION_MODE(CANIF_CFG_RX_PDURECEPTIONMODEIDX(rxSearchParams->eRxPduId)) == CANIF_RMT_RECEIVE_STOP)
#endif
      {
        /* #210 CAN ID matches - Pdu Id identified - break the search */
        rxSearchParams->eRxPduIdMatch = rxSearchParams->eRxPduId; /* SBSW_CANIF_9 */
        retVal = CANIF_TX_RX_NOTIFICATION;
      }
#if (CANIF_SET_PDU_RECEPTION_MODE_SUPPORT == STD_ON)
    }
    else
    /* #300 CAN ID matches - Pdu Id identified - break the search (no PduReceptioMode PDU) */            
    {
      rxSearchParams->eRxPduIdMatch = rxSearchParams->eRxPduId; /* SBSW_CANIF_9 */
      retVal = CANIF_TX_RX_NOTIFICATION;
    }
#endif
  }  
  return retVal;
}


/**********************************************************************************************************************
 *  CanIf_RxIndicationSubRangeSearch()
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
 *
 */
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubRangeSearch(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams) /* COV_CANIF_NO_RANGE_SEARCH */
{
  /* #100 Run linear through Rx-range search area until the last Rx-range */
  while ((CANIF_CFG_RX_MASK(rxSearchParams->eRxPduId) & (CANIF_STOP_FLAG | CANIF_RANGE_FLAG)) == CANIF_RANGE_FLAG)  /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
  {
    /* #110 Handle code-mask Rx-range */
    if ((CANIF_CFG_RX_CANID(rxSearchParams->eRxPduId) & CANIF_MASKCODE_RANGE) == CANIF_MASKCODE_RANGE) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_RxPDU */
    {
      if (CANIF_CFG_RX_CANID(rxSearchParams->eRxPduId) == ((rxSearchParams->eCanId & (CANIF_CFG_RX_MASK(rxSearchParams->eRxPduId) )) | CANIF_MASKCODE_RANGE )) /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      {
        /* #120 Check the message type regarding FD format and PDU reception mode */
        if (CanIf_RxIndicationSubReceptionPduMode(rxSearchParams) == CANIF_TX_RX_NOTIFICATION)  /* PRQA S 2991, 2995 */ /* MD_CanIf_Rule14.3_RxPDU */ /* SBSW_CANIF_5 */ /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
        {
          break; /* PRQA S 0771 */ /* MD_CanIf_Rule15.4 */
        }
      }
    }
    else
    /* #130 Handle upper-lower CAN identifier Rx-range */
    {
      if ((rxSearchParams->eCanId >= CANIF_CFG_RX_CANID(rxSearchParams->eRxPduId)) && (rxSearchParams->eCanId <= ((CANIF_CFG_RX_MASK(rxSearchParams->eRxPduId) & ~(CANIF_STOP_FLAG | CANIF_RANGE_FLAG)))))
      {
        /* #140 Check the message type regarding FD format and PDU reception mode */
        if (CanIf_RxIndicationSubReceptionPduMode(rxSearchParams) == CANIF_TX_RX_NOTIFICATION) /* PRQA S 2991, 2995 */ /* MD_CanIf_Rule14.3_RxPDU */ /* SBSW_CANIF_5 */ /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
        {
          break; /* PRQA S 0771 */ /* MD_CanIf_Rule15.4 */
        }
      }
    }
    rxSearchParams->eRxPduId--; /* SBSW_CANIF_9 */
  } /* while-loop */

  /* #200 Process the last / if only one Rx-range is configured separately */
  if ((CANIF_CFG_RX_MASK(rxSearchParams->eRxPduId) & (CANIF_STOP_FLAG | CANIF_RANGE_FLAG)) == (CANIF_STOP_FLAG | CANIF_RANGE_FLAG)) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
  {
    /* #210 Handle code-mask Rx-range */
    if ((CANIF_CFG_RX_CANID(rxSearchParams->eRxPduId) & CANIF_MASKCODE_RANGE) == CANIF_MASKCODE_RANGE) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_RxPDU */
    {
      /* End flag for Search algorithm is set, this means no more messages to search for */
      if (CANIF_CFG_RX_CANID(rxSearchParams->eRxPduId) == ((rxSearchParams->eCanId & CANIF_CFG_RX_MASK(rxSearchParams->eRxPduId)) | CANIF_MASKCODE_RANGE )) /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      {
        /* #220 Check the message type regarding FD format and PDU reception mode */
        (void)CanIf_RxIndicationSubReceptionPduMode(rxSearchParams);  /* SBSW_CANIF_5 */
      }
    }
    else
    /* #230 Handle upper-lower CAN identifier Rx-range */
    {
      /* End flag for Search algorithm is set, this means no more messages to search for */
      if ((rxSearchParams->eCanId >= CANIF_CFG_RX_CANID(rxSearchParams->eRxPduId)) && (rxSearchParams->eCanId <= ((CANIF_CFG_RX_MASK(rxSearchParams->eRxPduId) & ~(CANIF_STOP_FLAG | CANIF_RANGE_FLAG)))))
      {
        /* #240 Check the message type regarding FD format and PDU reception mode */
        (void)CanIf_RxIndicationSubReceptionPduMode(rxSearchParams);  /* SBSW_CANIF_5 */
      }
    }
  }
} /* PRQA S 6030 */ /* MD_MSR_STCYC */


#if ((CANIF_WAKEUP_VALIDATION == STD_ON) && (CANIF_WAKEUP_VALID_ALL_RX_MSGS == STD_ON))
/**********************************************************************************************************************
 *  CanIf_RxIndicationSubWakeupValidation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubWakeupValidation(P2CONST(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams)
{
  CANIF_CHANNEL_CANTYPE_LOCAL
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  /* Acquire controller from CanIf_Mailbox struct */
  controller = CANIF_CFG_MAILBOX_CONTROLLER(rxSearchParams->eHrh);
# else
  CANIF_DUMMY_STATEMENT(rxSearchParams); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_STARTED)
  {
    /* \trace SPEC-21407 */ /* All messages will be used for validation only in controller mode STARTED */
    /* #100 If CAN channel is active set validation state to DETECTED (only if configured) */
    CanIf_SetWakeUpValidationState(CanIf_Controller_Value_Local, CANIF_WUVALIDATION_DETECTED); /* SBSW_CANIF_19 */
  }
}
#endif /* ((CANIF_WAKEUP_VALIDATION == STD_ON) && (CANIF_WAKEUP_VALID_ALL_RX_MSGS == STD_ON)) */


/**********************************************************************************************************************
 *  CanIf_RxIndicationSubBasicCan()
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
 */
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_RxIndicationSubBasicCan(P2VAR(CanIf_RxSearchParamsType, AUTOMATIC, AUTOMATIC) rxSearchParams) /* COV_CANIF_FULLCAN */
{
  rxSearchParams->eContinueSearch = TRUE; /* SBSW_CANIF_9 */
  /* #10 Check if not only ranges are configured */
  if((CANIF_CFG_RX_MASK(rxSearchParams->eRxPduId) & CANIF_RANGE_FLAG) != CANIF_RANGE_FLAG) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
  {
#if (CANIF_SEARCH_ALGORITHM == CANIF_BINARY)
    /* #100 Binary search */
    CanIf_RxIndicationSubBinarySearch(rxSearchParams); /* SBSW_CANIF_5 */
#endif /* CANIF_SEARCH_ALGORITHM == CANIF_BINARY */

#if (CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH)
    /* #200 DoubleHash search */
    CanIf_RxIndicationSubDoubleHashSearch(rxSearchParams); /* SBSW_CANIF_5 */
#endif /* CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH */

#if (CANIF_SEARCH_ALGORITHM == CANIF_LINEAR)
    /* #300 Linear search */
    CanIf_RxIndicationSubLinearSearch(rxSearchParams); /* SBSW_CANIF_5 */
#endif /* CANIF_SEARCH_ALGORITHM == CANIF_LINEAR */
#if (CANIF_SET_PDU_RECEPTION_MODE_SUPPORT == STD_ON)
    /* #400 Match found */
    if(rxSearchParams->eRxPduIdMatch != CanIf_RxPduHnd_INVALID)
    {
      /* #410 Check the PDU reception mode */
      if (CANIF_CFG_RX_ISRECEPTIONMODEPDU(rxSearchParams->eRxPduIdMatch))
      {
        /* #420 If Pdu reception mode for matched PDU is CANIF_RMT_IGNORE_CONTINUE, match will be discarded */
        if (CANIF_VAR_GET_PDU_RECEPTION_MODE(CANIF_CFG_RX_PDURECEPTIONMODEIDX(rxSearchParams->eRxPduIdMatch)) == CANIF_RMT_IGNORE_CONTINUE)
        {
          rxSearchParams->eRxPduIdMatch = CanIf_RxPduHnd_INVALID; /* SBSW_CANIF_9 */
          /* #430 If ranges are defined at all, range search will continue */
          if((CANIF_CFG_RX_MASK(CANIF_CFG_MAILBOX_PDUIDFIRST(rxSearchParams->eHrh)) & CANIF_STOP_FLAG) == 0u) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
          {
            rxSearchParams->eContinueSearch = TRUE; /* SBSW_CANIF_9 */
          }
        }
      }
    }
#endif                  
    /* Ranges will be checked for all search algorithms */
    /* \trace SPEC-1911, SPEC-1844, SPEC-3704 */

#if (CANIF_SEARCH_ALGORITHM != CANIF_LINEAR) || (CANIF_SET_PDU_RECEPTION_MODE_SUPPORT == STD_ON)
    /* for doubleHash/binary search the RxPduId is still set on CANIF_CFG_MAILBOX(rxSearchParams.eHrh, ePduIdLast) */
    /* RxPduId needs to be set on CANIF_CFG_MAILBOX_PDUIDFIRST(rxSearchParams->eHrh) - 1 if Ranges are available */
    rxSearchParams->eRxPduId = CANIF_CFG_MAILBOX_PDUIDFIRST(rxSearchParams->eHrh); /* SBSW_CANIF_9 */
    if((CANIF_CFG_RX_MASK(rxSearchParams->eRxPduId) & CANIF_STOP_FLAG) == 0u) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
    {
      rxSearchParams->eRxPduId--; /* SBSW_CANIF_9 */
    }
    else
    {
      rxSearchParams->eContinueSearch = FALSE; /* no ranges defined */ /* SBSW_CANIF_9 */
    }
#endif /* CANIF_SEARCH_ALGORITHM != CANIF_LINEAR */
  } /* ESCAN00079651 */

  /* #500 Search for Rx-ranges separately */
  if (rxSearchParams->eContinueSearch == TRUE) /* Range processing */ /* COV_CANIF_NO_RANGE_SEARCH */
  {
    CanIf_RxIndicationSubRangeSearch(rxSearchParams);  /* SBSW_CANIF_5 */
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/* \trace SPEC-1836, SPEC-1228, SPEC-1931, SPEC-1235 */
/**********************************************************************************************************************
 *  CanIf_RxIndicationAsr403()
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
 *
 *
 */
FUNC(void, CANIF_CODE) CanIf_RxIndicationAsr403(CanIf_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR)CanSduPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  CanIf_RxSearchParamsType rxSearchParams;
#if (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
  Std_ReturnType j1939DynAddrRetVal;
# endif  
#endif
  uint8 errorId = CANIF_E_NO_ERROR;

  
  /* ----- Development Error Checks ------------------------------------- */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif
  /* #20 Check if parameter CanSduPtr is valid */
  if (CanSduPtr == NULL_PTR)
  {
    /* \trace SPEC-3714 */
    errorId = CANIF_E_PARAM_POINTER;
  }
  /* #30 Check if parameter CanDlc is valid */
  else if (CanDlc > CANIF_CFG_RX_MAXVALIDRXDLC) /* ESCAN00076432 */
  {
    /* \trace SPEC-3715 */
    errorId = CANIF_E_PARAM_DLC;
  }
# if (CANIF_EXTENDEDID_SUPPORT != STD_ON)
  /* #40 Check if parameter CanId is valid */
  else if ((CanId & (~CANIF_FDFLAG)) > 0x7FFu)
  {
    /* \trace SPEC-3698 */
    errorId = CANIF_E_PARAM_CANID;
  }
# endif
  /* #50 Check if parameter Hrh is valid */
  else if (Hrh >= CANIF_CFG_MAX_MAILBOXES)
  {
    /* \trace SPEC-3697 */
    errorId = CANIF_E_PARAM_HRH;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */

#if (CANIF_BUS_MIRRORING_SUPPORT == STD_ON)
    /* #100 Report CAN frame to mirror module, if mirroring is enabled for the CAN controller */
    if(CanIf_IsMirroringEnabled(CANIF_CFG_MAILBOX_CONTROLLER(Hrh)))
    {
      Mirror_ReportCanFrame(CANIF_CFG_MAILBOX_CONTROLLER(Hrh), CanId, CanDlc, CanSduPtr); /* SBSW_CANIF_5 */
    }
#endif /* CANIF_BUS_MIRRORING_SUPPORT == STD_ON */

#if (CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON) || (CANIF_META_DATA_RX_SUPPORT == STD_ON)
    /* #110 Determine the message type */
    if ((CanId & CANIF_FDFLAG) == CANIF_FDFLAG)
    {
      rxSearchParams.eRxMsgType = CANIF_MSG_TYPE_FD_CAN;
    }
    else
    {
      rxSearchParams.eRxMsgType = CANIF_MSG_TYPE_NO_FD_CAN;
    }
#endif /* CANIF_RX_SEARCH_CONSIDER_MSG_TYPE == STD_ON || CANIF_META_DATA_RX_SUPPORT == STD_ON */

    /* #120 Remove FD-flag from CAN identifier */
    CanId = (CanId & (~CANIF_FDFLAG)); /* The FD Flag is no part of the CAN ID */ /* PRQA S 1338 */ /* MD_CanIf_Rule17.8 */
    rxSearchParams.eCanId = CanId;
    rxSearchParams.eHrh = Hrh;

#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
    /* FEAT-2076 ESCAN00091870 */
    /* #130 Deactivate Tx-PDU-filter */
    CanIf_SetPnWuTxPduFilterActive(CANIF_CFG_MAILBOX_CONTROLLER(Hrh), FALSE); /* SBSW_CANIF_8 */
#endif  

#if ((CANIF_WAKEUP_VALIDATION == STD_ON) && (CANIF_WAKEUP_VALID_ALL_RX_MSGS == STD_ON))
    /* #140 Handle wake-up validation state (only if configured)) */
    CanIf_RxIndicationSubWakeupValidation(&rxSearchParams); /* SBSW_CANIF_5 */
#endif

#if (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
    /* #150 Adapt the CAN identifier according to J1939 specification (only if configured) */
    j1939DynAddrRetVal = CanIf_RxIndicationSubJ1939DynAddr(&rxSearchParams); /* SBSW_CANIF_5 */
    if (j1939DynAddrRetVal == E_OK)
# endif        
#endif
    {
      /* #200 Do search only if any Rx-PDU or range is configured. */
      if (CANIF_CFG_MAX_RXPDUS != 0u) /* PRQA S 2741 */ /* MD_CanIf_Rule14.3_GenData */ /* COV_CANIF_GENDATA_FAILURE */
      {
        rxSearchParams.eRxPduId = CANIF_CFG_MAILBOX_PDUIDLAST(Hrh);
        /* check if PduId is valid */
        if (rxSearchParams.eRxPduId != CanIf_RxPduHnd_INVALID) /* PRQA S 2991, 2995 */ /* MD_CanIf_Rule14.3_RxPDU */ /* COV_CANIF_GENDATA_FAILURE */
        {
          rxSearchParams.eRxPduIdMatch = CanIf_RxPduHnd_INVALID;

          /* #300 If FullCAN then nothing to search required */
          if (CANIF_CFG_MAILBOX_MAILBOXTYPE(Hrh) == CANIF_RxFullCANMailbox) /* COV_CANIF_FULLCAN */
          {
            /* #310 Check the message type regarding FD format and PDU reception mode */
            (void)CanIf_RxIndicationSubReceptionPduMode(&rxSearchParams);  /* SBSW_CANIF_5 */
          }
          else if (CANIF_CFG_MAILBOX_MAILBOXTYPE(Hrh) == CANIF_RxBasicCANMailbox) /* COV_CANIF_GENDATA_FAILURE */
          /* BASIC-CAN */
          /* #320 If BasicCAN search for matching using: linear, binary or double hash algorithm (dependent on configuration) */
          {
            CanIf_RxIndicationSubBasicCan(&rxSearchParams); /* SBSW_CANIF_5 */
          } /* else if BASIC-CAN */
          else
          {
            /* Hrh does not belong to Rx Mailbox, returns without an indication */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)           
            errorId = CANIF_E_CONFIG;
#endif
          }

          /* #330 Matched Rx-PDU found? */
          if (rxSearchParams.eRxPduIdMatch != CanIf_RxPduHnd_INVALID) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
          {
#if (CANIF_DATA_CHECKSUM_RX_SUPPORT == STD_ON)
            Std_ReturnType localRetVal;

            if (CANIF_CFG_RX_ISDATACHECKSUMPDU(rxSearchParams.eRxPduIdMatch))
            {
# if ((CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME) || (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))
              /* for PB and LT configurations the RxPduId order between CanIf and higher layers may differ and needs to be indirected */
              PduIdType CanIfRxPduId = CANIF_CFG_INTRXPDUID2EXTRXPDUID(rxSearchParams.eRxPduIdMatch);
# else
              PduIdType CanIfRxPduId = rxSearchParams.eRxPduIdMatch;  
# endif                
              /* #400 Data checksum Rx-PDU: Verify the checksum. (only if configured) */
              /* Note: Explicitly the CanId of received message is used (Not the manipulated one in case of J1939 dynamic address support). */
              localRetVal = CanIf_RxIndicationSubDataChecksumRxVerify(CanIfRxPduId, CanId, CanDlc, CanSduPtr); /* SBSW_CANIF_5 */
            }
            else
            {
              /* #410 None data checksum Rx-PDU: Verification passed. (only if configured) */
              localRetVal = E_OK;
            }

            /* #420 Data checksum verification passed? (only if configured) */
            if (localRetVal == E_OK)
#endif /* (CANIF_DATA_CHECKSUM_RX_SUPPORT == STD_ON) */
            {
#if (CANIF_META_DATA_RX_SUPPORT == STD_ON)
              /* #430 Restore FD-flag in CAN identifier */
              if (rxSearchParams.eRxMsgType == CANIF_MSG_TYPE_FD_CAN)
              {
                rxSearchParams.eCanId |= CANIF_FDFLAG;
              }
#endif
              /* #440 Report received Rx-PDU to upper layer */
              CanIf_Indirect_HlIndication(Hrh, rxSearchParams.eRxPduIdMatch, CanSduPtr, CanDlc, rxSearchParams.eCanId); /* SBSW_CANIF_10 */
            }
          }
        } /* if (RxPduId != CanIf_RxPduHnd_INVALID) */
      } /* if (CANIF_CFG_MAX_RXPDUS != 0)  */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  CanIf_HlIndicationSubULCall()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
#if (CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON) || (CANIF_RX_INDICATION_TYPE_IV_IS_USED == STD_ON)
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_HlIndicationSubULCall(PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc, Can_IdType CanId)
#else
CANIF_LOCAL_INLINE FUNC(void, CANIF_CODE) CanIf_HlIndicationSubULCall(PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc )
#endif
{
  CanIf_RxIndFctListIdxType index;
  index = CANIF_CFG_RX_RXINDICATION(PduId);

  /* #100 Report received message to upper layer */
#if (CANIF_RX_INDICATION_TYPE_I_IS_USED == STD_ON)
  if (CANIF_CFG_RXINDICATION_FUNCTIONLAYOUT(index) == CanIf_SimpleRxIndicationLayout)
  {
    /* #200 CanIf_SimpleRxIndicationLayout API */
    CanIf_SimpleRxIndicationFctType rxIndicationFct;
    rxIndicationFct = CANIF_CFG_RXINDICATION_FUNCTION(index).eSimpleRxIndicationType;
    if (rxIndicationFct != NULL_PTR)
    {
      /* \trace SPEC-1885 */
      /* CA cast (-> to get the const ) */
      /* CANIF_APPL_VAR -> located in CAN Driver */
      rxIndicationFct(CANIF_CFG_RX_UPPERPDUID(PduId), (P2CONST(uint8, AUTOMATIC, CANIF_UL_STANDARD_VAR))CanSduPtr); /* SBSW_CANIF_12 */
    }
  } 
  else
#endif

#if (CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON)
  if (CANIF_CFG_RXINDICATION_FUNCTIONLAYOUT(index) == CanIf_NmOsekRxIndicationLayout)
  {
    /* #300 CanIf_NmOsekRxIndicationLayout API */
    CanIf_NmOsekRxIndicationFctType rxIndicationFct;
    rxIndicationFct = CANIF_CFG_RXINDICATION_FUNCTION(index).eNmOsekRxIndicationType;
    if (rxIndicationFct != NULL_PTR)
    {
      /* \trace SPEC-1841, SPEC-1885 */
      /* CA cast (-> to get the const ) */
      /* CANIF_APPL_VAR -> located in CAN Driver */
      rxIndicationFct(CANIF_CFG_RX_UPPERPDUID(PduId), (P2CONST(uint8, AUTOMATIC, CANIF_UL_OSEKNM_VAR))CanSduPtr, CanId); /* SBSW_CANIF_12 */
    }
  }
  else
#endif

#if (CANIF_RX_INDICATION_TYPE_IV_IS_USED == STD_ON)
  if (CANIF_CFG_RXINDICATION_FUNCTIONLAYOUT(index) == CanIf_CddRxIndicationLayout)
  {
    /* #400 CanIf_CddRxIndicationLayout API */
    CanIf_CddRxIndicationFctType rxIndicationFct;
    PduInfoType pduinfo;
    /* cast from CANIF_CBK_DRV_VAR to AUTOSAR_COMSTACKDATA --> has to be resolved in compiler abstraction configuration */
    /* const to non-const cast is not avoidable */
    pduinfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA))CanSduPtr; /* PRQA S 0311 */ /* MD_CanIf_Rule11.8 */
    /* CANIF262: Currently received DLC value is passed to upper layer */
    pduinfo.SduLength = CanDlc;

    rxIndicationFct = CANIF_CFG_RXINDICATION_FUNCTION(index).eCddRxIndicationType;
    if (rxIndicationFct != NULL_PTR)
    {
      /* \trace SPEC-1885 */
      /* CA cast (-> to get the const ) */
      /* CANIF_APPL_VAR -> located in CAN Driver */
      rxIndicationFct(CANIF_CFG_RX_UPPERPDUID(PduId), (P2CONST(PduInfoType, AUTOMATIC, CANIF_UL_ADVANCED_VAR))&pduinfo, CanId); /* SBSW_CANIF_12 */
    }
  } 
  else
#endif

  if (CANIF_CFG_RXINDICATION_FUNCTIONLAYOUT(index) == CanIf_AdvancedRxIndicationLayout) /* PRQA S 2004 */ /* MD_MSR_EmptyClause */
  {
    /* #500 CanIf_AdvancedRxIndicationLayout API */
    CanIf_AdvancedRxIndicationFctType rxIndicationFct;
    PduInfoType pduinfo;
    /* cast from CANIF_CBK_DRV_VAR to AUTOSAR_COMSTACKDATA --> has to be resolved in compiler abstraction configuration */
    /* const to non-const cast is not avoidable */
    pduinfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, AUTOSAR_COMSTACKDATA))CanSduPtr; /* PRQA S 0311 */ /* MD_CanIf_Rule11.8 */
    /* CANIF262: Currently received DLC value is passed to upper layer */
    pduinfo.SduLength = CanDlc;

    rxIndicationFct = CANIF_CFG_RXINDICATION_FUNCTION(index).eAdvancedRxIndicationType;
    if (rxIndicationFct != NULL_PTR)
    {
      /* \trace SPEC-1841, SPEC-1885 */
      /* CA cast (-> to get the const ) */
      /* PTR to Stack -> AUTOMATIC */
      rxIndicationFct(CANIF_CFG_RX_UPPERPDUID(PduId), (P2CONST(PduInfoType, AUTOMATIC, CANIF_UL_ADVANCED_VAR))&pduinfo); /* SBSW_CANIF_12 */
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  CanIf_HlIndication()
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
 *
 */
#if ((CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON) || (CANIF_META_DATA_RX_SUPPORT == STD_ON) || (CANIF_RX_INDICATION_TYPE_IV_IS_USED == STD_ON))
/* static void CanIf_HlIndication(uint8 Hrh, PduIdType PduId, const uint8 *CanSduPtr, uint8 CanDlc, Can_IdType CanId) */
CANIF_LOCAL FUNC(void, CANIF_CODE) CanIf_HlIndication(CanIf_HwHandleType  Hrh, PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc, Can_IdType CanId)
#else
/* static void CanIf_HlIndication(uint8 Hrh, PduIdType PduId, const uint8 *CanSduPtr, uint8 CanDlc) */
CANIF_LOCAL FUNC(void, CANIF_CODE) CanIf_HlIndication(CanIf_HwHandleType  Hrh, PduIdType PduId, P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR) CanSduPtr, uint8 CanDlc)
#endif
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
  CANIF_CHANNEL_CANTYPE_LOCAL

#if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(Hrh); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#else
  /* Determine the channel from Hrh */
  controller = CANIF_CFG_MAILBOX_CONTROLLER(Hrh);
#endif

  /* ----- Development Error Checks ------------------------------------- */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  /* #10 Check if CAN channel is valid */
  if (CanIf_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER)
  {
    errorId = CANIF_E_CONFIG;
  } 
  else
# endif /* CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF */
  /* #20 Check if CAN channel is initialized */
  if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
  {
    /* \trace SPEC-3718, SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else 
#endif /* CANIF_DEV_ERROR_DETECT == STD_ON */
  {

    /* ----- Implementation ----------------------------------------------- */
    /* \trace SPEC-3711 */
    /* #100 Process only if CAN channel is active */
    if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_STARTED)
    {
#if (CANIF_WAKEUP_VALIDATION == STD_ON)
# if (CANIF_WAKEUP_VALID_ALL_RX_MSGS != STD_ON)
     /* CANIF741 */
#  if (CANIF_WAKEUP_VALID_ONLY_NM_RX_MSGS == STD_ON)
      if((uint8)(CANIF_CFG_RX_DLC(PduId) & CANIF_WU_VALIDATION_NM_FLAG_GET) != 0u)
#  endif
      {
        /* \trace SPEC-21407 */ /* Only ECUs receive list will validate an Rx event / Controller mode: Started, PduMode: Don't care */
        /* #110 Set wake-up validation state to DETECTED (only if configured) */
        CanIf_SetWakeUpValidationState(CanIf_Controller_Value_Local, CANIF_WUVALIDATION_DETECTED); /* SBSW_CANIF_3 */
      }
# endif
#endif

      if ( (CanIf_GetChannelMode(CanIf_Controller_Value_Local) == CANIF_GET_ONLINE) || /* \trace SPEC-1849, SPEC-1850 */
           (CanIf_GetChannelMode(CanIf_Controller_Value_Local) == CANIF_GET_RX_ONLINE) || /* \trace SPEC-3855 */
           (CanIf_GetChannelMode(CanIf_Controller_Value_Local) == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE)
# if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
        || (CanIf_GetChannelMode(CanIf_Controller_Value_Local) == CANIF_GET_ONLINE_WAKF)
# endif
         )
      {
#if (CANIF_DLC_CHECK == STD_ON)
        /* #120 Check if parameter CanDlc is valid */
        /* DLC check - if configured DLC == 0 the following condition is always false and DLC check is deactivated */
        /* \trace SPEC-1846, SPEC-3672 */
        if (CanDlc < (uint8)(CANIF_CFG_RX_DLC(PduId) & CANIF_WU_VALIDATION_NM_MASK_OUT) )
        {
          /* \trace SPEC-1900 */
          /* Notification to DET */
          errorId = CANIF_E_INVALID_DLC;
        } 
        else 
        /* \trace SPEC-1964 */
#endif
        {
          /* #130 Handle meta data of Rx-PDU: Copy payload of received Rx-PDU into local buffer and add CAN identifier or parts of it to it (only if meta data Rx-PDU) */
#if (CANIF_META_DATA_RX_SUPPORT == STD_ON)
          uint8 CanSduLocal[CANIF_CFG_MAXRXDLC_PLUS_MAXMETADATA];
          uint8_least i;
          uint8_least j;
          if ((CANIF_CFG_RX_RXMETADATALENGTH(PduId) > 0u) && ((CanDlc + CANIF_CFG_RX_RXMETADATALENGTH(PduId)) > CANIF_CFG_MAXRXDLC_PLUS_MAXMETADATA))
          {
            errorId = CANIF_E_INVALID_DLC_METADATA;
          }
          else
          {
            if(CANIF_CFG_RX_RXMETADATALENGTH(PduId) > 0u)
            {
# if (CANIF_USES_VSTDLIB_COPY == STD_ON)
              VStdMemCpyRamToRam(CanSduLocal, CanSduPtr, CanDlc); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */ /* SBSW_CANIF_7 */
              i = CanDlc;
# else          
              for (i = 0; i < CanDlc; i++)
              {
                CanSduLocal[i] = CanSduPtr[i];  /* copy received data on local data buffer */  /* SBSW_CANIF_16 */
              }
# endif
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
              {
                Can_IdType CanIdLocal;
                CanIdLocal = CanId;

                for (j = 0; j < CANIF_CFG_RX_RXMETADATALENGTH(PduId); j++)
                {
                  CanSduLocal[i] = (uint8)(CanIdLocal & 0x000000FFu);   /* SBSW_CANIF_16 */
                  i++;
                  CanIdLocal = CanIdLocal >> 8;
                }
              }
# else
              {
                Can_IdType CanIdLocal;
                uint8_least shiftCounter;
                CanIdLocal = CanId;
                shiftCounter = 0;
                for (j = 0; j < CANIF_CFG_RX_RXMETADATALENGTH(PduId); j++)
                {
                  if (shiftCounter < 2u)  /* MetaDataLength is max 4 */
                  {
                    CanSduLocal[i] = (uint8)(CanIdLocal & 0x00FFu);   /* SBSW_CANIF_16 */
                    CanIdLocal = CanIdLocal >> 8u;
                    shiftCounter++;
                  }
                  else
                  {
                    CanSduLocal[i] = 0x00;   /* SBSW_CANIF_16 */
                  }
                  i++;
                }
              }
# endif
# if (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
#  if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
              /* #140 If the received message is a acknowledgment message the address in the data is changed */
              if ((CanId & CANIF_J1939_PGN_MASK) == CANIF_J1939_ACKM_PGN)
              {
                uint8 ackAddr = CANIF_VAR_J1939RXADDR_LOOKUP(CanIf_Controller_Value_Local, CanSduPtr[CANIF_J1939_ACKM_ACKADDR_POS]);
                if (ackAddr == CANIF_J1939_NULL_ADDR)
                {
                  errorId = CANIF_E_INVALID_DA;
                }
                CanSduLocal[CANIF_J1939_ACKM_ACKADDR_POS] = ackAddr;  /* SBSW_CANIF_30 */
              }
#  endif            
# endif
              CanSduPtr =  CanSduLocal; /* PRQA S 1338 */ /* MD_CanIf_Rule17.8 */
              CanDlc = (uint8)i; /* increment DLC */ /* PRQA S 1338 */ /* MD_CanIf_Rule17.8 */
            }
#endif 
            /* #150 Check if Rx-indication function is valid */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
            if ( CANIF_CFG_RX_RXINDICATION(PduId) >= CANIF_CFG_MAX_RXINDICATIONS )
            {
              errorId = CANIF_E_CONFIG;
            } 
            else
#endif
            {
              /* #160 Report received message to upper layer */
#if (CANIF_SUPPORT_NMOSEK_INDICATION == STD_ON) || (CANIF_RX_INDICATION_TYPE_IV_IS_USED == STD_ON)
# if (CANIF_META_DATA_RX_SUPPORT == STD_ON)
              /* #170 Remove FD-flag from CAN identifier */
              CanId = (CanId & (~CANIF_FDFLAG)); /* The FD Flag is no part of the CAN ID */ /* PRQA S 1338 */ /* MD_CanIf_Rule17.8 */
# endif
              CanIf_HlIndicationSubULCall(PduId, CanSduPtr, CanDlc, CanId); /* SBSW_CANIF_5 */
#else
              CanIf_HlIndicationSubULCall(PduId, CanSduPtr, CanDlc); /* SBSW_CANIF_5 */
#endif  
            }
#if (CANIF_META_DATA_RX_SUPPORT == STD_ON)
          }

#endif
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_RXINDICATION_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

} /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */


/* \trace SPEC-1912, SPEC-3725 */
/**********************************************************************************************************************
 *  CanIf_ControllerBusOff()
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
 */
FUNC(void, CANIF_CODE) CanIf_ControllerBusOff(uint8 ControllerId)
{
  /* conform to requirement \trace SPEC-1877 */

  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
  CanIf_BusOffNotificationFctType busoffnotificationFct = CANIF_CFG_BUSOFFNOTIFICATION();

  /* ----- Development Error Checks ------------------------------------- */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    /* \trace SPEC-3717 */
    errorId = CANIF_E_PARAM_CONTROLLER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    
    /* #30 Verify if affected CAN channel is initialized */
    /* \trace SPEC-3705 */
    if (CanIf_GetCtrlMode(CanIf_Controller_Value) != CANIF_CS_UNINIT)
    {
      /* #100 Deactivate the communication via the affected CAN channel (controller and PDU mode) */
      /* ESCAN00051423, avoids ESCAN00051329 */
      /* Explicitely cast to void as return value cannot be used here */
      (void)CanIf_SetPduMode(CanIf_Controller_Value, CANIF_SET_TX_OFFLINE);

      /* Set CAN Interface to Stopped mode, CAN Controller is BusOff */
      /* ASR4 CANController is already in STOP -> only internal variable must be set */
      /* \trace SPEC-3761, SPEC-1965 */
      CanIf_SetCtrlMode(CanIf_Controller_Value, CANIF_CS_STOPPED);  /* SBSW_CANIF_3 */

#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))      
      /* #110 Clear the Tx-queue */
      CanIf_ClearQueue(CANIF_CHANNEL_CANPARA_ONLY);
#endif    

#if (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON)
      /* #120 Reset the Tx-confirmation state */
      /* \trace SPEC-9980 */
      /* TxConfirmationState is reset always when CAN controller is stopped
      * - BusOff
      * - Going to _SLEEP
      * - CanIf_InitController() is called */
      CanIf_SetTxConfState(CanIf_Controller_Value, CANIF_NO_NOTIFICATION); /* SBSW_CANIF_3 */
#endif

      /* #130 Verify if notification function to upper layer is configured */
      if (busoffnotificationFct != NULL_PTR)
      {
        /* #140 Call BusOff notification function */
        /* \trace SPEC-5346 */
        busoffnotificationFct(CanIf_Controller_Value);  /* SBSW_CANIF_13 */
      }
    }
    else
    {
      /* \trace SPEC-3709, SPEC-5238 */
      errorId = CANIF_E_UNINIT;
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CONTROLLERBUSOFF_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

#if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
    CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/* \trace SPEC-1832 */
/**********************************************************************************************************************
 *  CanIf_SetPduMode()
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
 *
 *
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPduMode(uint8 ControllerId, CanIf_PduSetModeType PduModeRequest)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK;
  uint8 errorId = CANIF_E_NO_ERROR; 

  /* ----- Development Error Checks ------------------------------------- */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    /* \trace SPEC-3537 */
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  /* #40 Check if PduModeRequest is valid */
  else if(PduModeRequest >= CANIF_NO_MODE_PDU_SET_MODE_TYPE_END)
  {
    errorId = CANIF_E_PARAM_PDU_MODE;
  }
  else
#endif
  {
    /* ----- Implementation --------------------------------------------- */

    /* #100 Change PDU mode only if CAN channel is in STARTED mode */
    if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_STARTED)
    {
      /* #110 Process PDU mode change within critical section */
      retval = E_OK;
      CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_3);

      /* #120 Do allow PDU mode transitions only if required */
      if(CanIfState[CanIf_GetChannelMode(CanIf_Controller_Value)][PduModeRequest] != CANIF_NOP)
      {
        switch (PduModeRequest)
        {
          case CANIF_SET_OFFLINE:
          case CANIF_SET_TX_OFFLINE:
          case CANIF_SET_TX_OFFLINE_ACTIVE:
            switch(CanIf_GetChannelMode(CanIf_Controller_Value))
            {
              case CANIF_GET_TX_ONLINE:
              case CANIF_GET_ONLINE:
              /* \trace SPEC-1849, SPEC-3765 */
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON) /* ESCAN00057578 */
              case CANIF_GET_TX_ONLINE_WAKF:
              case CANIF_GET_ONLINE_WAKF:
#endif
#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
                /* #130 If Tx-direction is deactivated clear the Tx-queue */
                CanIf_ClearQueue(CANIF_CHANNEL_CANPARA_ONLY);
#endif                  
                break;
              default: /* COV_CANIF_GENDATA_FAILURE */
                break;
            }
            /* #140 In case of any WAKF-mode is left disable the wake-up Tx-filter */
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
            CanIf_SetPnWuTxPduFilterActive(CanIf_Controller_Value, FALSE);  /* SBSW_CANIF_3 */
#endif
            break;
          case CANIF_SET_ONLINE:
          case CANIF_SET_TX_ONLINE:
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
            CanIf_SetPnWuTxPduFilterActive(CanIf_Controller_Value, FALSE);  /* SBSW_CANIF_3 */
#endif
            break;
#if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
          case CANIF_SET_ONLINE_WAKF:
          case CANIF_SET_TX_ONLINE_WAKF:
            /* CANIF752 */
            /* #150 In case of WAKF-mode is requested AND the corresponding channel requires the Tx-filter enable it */
            if(CANIF_CFG_ISFEATUREPNWUTXPDUFILTERENABLED(CanIf_Controller_Value)) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
            {
              /* CANIF749 */
              CanIf_SetPnWuTxPduFilterActive(CanIf_Controller_Value, TRUE);  /* SBSW_CANIF_3 */
            }
            break;
#endif
          default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
            break;
        }
        /* Get the next valid state by reading the table: CanIfState */
        /* #160 Determine and set the requested PDU-mode */
        CanIf_SetChannelMode(CanIf_Controller_Value, (CanIf_PduGetModeType)CanIfState[CanIf_GetChannelMode(CanIf_Controller_Value)][PduModeRequest]); /* PRQA S 4342 */ /* MD_CanIf_Rule10.5_4342 */ /* SBSW_CANIF_3 */
      }
      CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_3);
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_SETPDUMODE_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION==STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */


/* \trace SPEC-1835 */
/**********************************************************************************************************************
 *  CanIf_GetPduMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetPduMode(uint8 ControllerId, P2VAR(CanIf_PduGetModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) PduModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    /* \trace SPEC-3555 */
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if channel is initialized */
  else if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  /* #40 Check if parameter PduModePtr is valid */
  else if (PduModePtr == NULL_PTR)
  {
    /* \trace SPEC-5236 */
    errorId = CANIF_E_PARAM_POINTER;
  }
  else
#endif /* CANIF_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation --------------------------------------------- */

    /* #100 Get the actual PDU mode */
    *PduModePtr = CanIf_GetChannelMode(CanIf_Controller_Value); /* SBSW_CANIF_9 */
    retval = E_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_GETPDUMODE_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

#if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
/**********************************************************************************************************************
 *  CanIf_TxQueueTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
CANIF_LOCAL FUNC(Std_ReturnType, CANIF_CODE) CanIf_TxQueueTransmit( PduIdType PduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_PduType localPdu;
  Can_ReturnType txResult;
  Std_ReturnType retval;
  CanIf_AnyIdxType hth;
  
  uint8 errorId = CANIF_E_NO_ERROR;
  
# if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
  CanIf_AnyIdxType txBufferCfgIdx;
  CanIf_AnyIdxType txFifoQueueBaseStartIdx;
  CanIf_AnyIdxType txBufferFifoBaseIdx;
# endif  

  retval = E_NOT_OK;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
/* #10 Check if parameter PduId is valid. */
  if (PduId >= CANIF_CFG_MAX_TXPDUS)
  {
    /* \trace SPEC-2007 */
    errorId = CANIF_E_INVALID_TXPDUID;
  }
  else
# endif        
/* ----- Implementation ----------------------------------------------- */
  {
    hth = CANIF_CFG_TX_HTH(PduId);
# if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
    txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(hth);
# endif

    switch (CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(hth))
    {
# if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
      case CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID:
        /* #100 Prepare the Tx-PDU to be transmitted (CAN identifier, DLC, payload) */
#  if((CANIF_SETDYNAMICTXID_API == STD_ON) || (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) || (CANIF_META_DATA_TX_SUPPORT == STD_ON)) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
        (localPdu).id = CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueueParams.eBaseParams.eCanId);
#  else 
        (localPdu).id = CANIF_CFG_TX_CANID(PduId);
#  endif
        (localPdu).length = (uint8)CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueueParams.eBaseParams.eSduLength);
#  if(CANIF_STATIC_FD_TXQUEUE == STD_ON)
        (localPdu).sdu = CANIF_ADDR_VAR_TXBUFFERPRIOBYCANID_STATFDQUEUE_QUEUEDATA(CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_DATASTARTIDX(PduId));
#  else
        (localPdu).sdu = CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(PduId), eQueueParams.eSdu);
#  endif
        (localPdu).swPduHandle = (PduId);
        break;
# endif                    
# if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
      case CANIF_TXBUFFER_HANDLINGTYPE_FIFO:
        txBufferFifoBaseIdx = CANIF_CFG_TXBUFFERFIFO_BUFFERBASEIDX(txBufferCfgIdx);
        txFifoQueueBaseStartIdx = CANIF_CFG_TXBUFFERFIFO_QUEUEBASESTARTIDX(txBufferCfgIdx);
      
#  if((CANIF_SETDYNAMICTXID_API == STD_ON) || (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) || (CANIF_META_DATA_TX_SUPPORT == STD_ON)) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
        (localPdu).id = CANIF_VAR_TXBUFFERFIFO_QUEUEBASE( (CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx  ) + txFifoQueueBaseStartIdx ), eBaseParams.eCanId );
#  else 
        (localPdu).id = CANIF_CFG_TX_CANID(PduId);
#  endif
        (localPdu).length = CANIF_VAR_TXBUFFERFIFO_QUEUEBASE( (CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx  ) + txFifoQueueBaseStartIdx ), eBaseParams.eSduLength );
        (localPdu).sdu = CANIF_ADDR_VAR_TXBUFFERFIFO_QUEUEDATA((CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx) * (uint32)CANIF_CFG_TXBUFFERFIFO_SIZEOFONEPAYLOADEL(txBufferCfgIdx)) + CANIF_CFG_TXBUFFFERFIFO_QUEUEDATASTARTIDX(txBufferCfgIdx));
        (localPdu).swPduHandle = (PduId);
          break;
# endif            
      default: /* COV_CANIF_GENDATA_FAILURE */
        break; 
    }
      /* \trace SPEC-1845 */
  
      /* #110 Pass the Tx-request to CAN driver */
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
    {
      CanIf_Can_WriteFctType canWriteFct;
      Can_HwHandleType canDrvHth;
      
      canWriteFct = CanIf_GetCan_WriteFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CANIF_CFG_TX_CONTROLLER(PduId)));
      canDrvHth = (Can_HwHandleType)(hth - CANIF_CFG_MULTIPLECANDRV_HXHOFFSET(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CANIF_CFG_TX_CONTROLLER(PduId))));

      txResult = canWriteFct(canDrvHth, &localPdu); /* SBSW_CANIF_47 */ /* PRQA S 2972 */ /* MD_CanIf_Rule9.1 */
    }
# else
    txResult = Can_Write((CanIf_HwHandleType)hth, &localPdu);  /* SBSW_CANIF_5 */  /* PRQA S 2972 */ /* MD_CanIf_Rule9.1 */
# endif

    if (txResult == CAN_OK)
    {
      /* \trace SPEC-1897 */
      /* #120 If the Tx-request succeeds, remove the Tx-PDU from Tx-queue */
      switch (CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(hth))
      {
# if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
        case CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID:    
          (void)CanIf_ClearPrioByCanIdTxPduAsQueued(PduId);
          break;
# endif

# if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
        case CANIF_TXBUFFER_HANDLINGTYPE_FIFO:
          txBufferFifoBaseIdx = CANIF_CFG_TXBUFFERFIFO_BUFFERBASEIDX(txBufferCfgIdx);
#  if (CANIF_CANCEL_SUPPORT_API == STD_ON)
          CANIF_VAR_TXBUFFERFIFO_QUEUEBASE(( CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx)+CANIF_CFG_TXBUFFERFIFO_QUEUEBASESTARTIDX( txBufferCfgIdx)), eQueued) = 0; /* SBSW_CANIF_38 */
          CANIF_VAR_SET_TXBUFFERFIFO_QUEUEIDX2FIFOEL(CANIF_CFG_TX_QUEUEINDEX(PduId), CANIF_NO_ENTRY_IN_TX_FIFO); /* SBSW_CANIF_36 */
#  endif  
          CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx)++; /* SBSW_CANIF_37 */
          if(CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx) == CANIF_CFG_TXBUFFERFIFO_QUEUESIZE(txBufferCfgIdx)) 
          {
            CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx) = 0; /* SBSW_CANIF_37 */
          }
          CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eQueueCounter)--; /* SBSW_CANIF_37 */
          break;
# endif        
        default: /* COV_CANIF_GENDATA_FAILURE */
          break;
      }
      retval = E_OK;
    } 
    else if (txResult == CAN_BUSY) /* PRQA S 2004 */ /* MD_MSR_EmptyClause */
    {
      /* also ok due to confirmation queue handling may be interrupted by CanIf_Transmit() or just a cancel request */
      retval = E_OK;
    }
  }
  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CANCELTRANSMIT_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
}
#endif


#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
/**********************************************************************************************************************
 *  CanIf_TxQueueTreatment()
 *********************************************************************************************************************/
/*!
 *
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
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANIF_LOCAL FUNC(Std_ReturnType, CANIF_CODE) CanIf_TxQueueTreatment(CanIf_HwHandleType hth)
{
  /* ----- Local Variables ---------------------------------------------- */
# if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
#  if (CANIF_BITQUEUE == STD_ON)
  /* FOR-loop: count variable */
  sint16_least queueElementIdx; 
  /* FOR-loop: stores the end-condition, improves performance */
  sint16_least queueEndElementIdx;
  sint8_least elementBitIdx;
  CanIf_TxQueueFlagType  elem;
  PduIdType PduId;
#  else
  CanIf_AnyIdxType idx2MappedTxPdus;
#  endif
  CanIf_AnyIdxType txBufferPrioByCanIdBaseIdx;
# endif
# if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
  CanIf_AnyIdxType txBufferFifoBaseIdx;  
  CanIf_AnyIdxType txBufferFifoQueueBaseStartIdx;
  CanIf_TxBufferSizeType txBufferFifoActReadIdx;
# endif    
  Std_ReturnType retval;
  CanIf_AnyIdxType txBufferCfgIdx;

  retval = E_NOT_OK; /* default nothing to send */
  /* ----- Implementation ----------------------------------------------- */

  txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(hth);
  /* #100 To which type of buffer belongs the HTH to? */
  switch (CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(hth))
  {
# if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
    case CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID:
#  if (CANIF_BITQUEUE == STD_ON)
      /* #200 PRIO_BY_CANID: BIT_QUEUE-handling: */
      txBufferPrioByCanIdBaseIdx = CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_BUFFERBASEIDX(txBufferCfgIdx);
       /* #210 Anything buffered? */ 
      if (CanIf_GetTxQueueCounter(txBufferPrioByCanIdBaseIdx) != 0u)
      {
        /* Get the end-condition of the following FOR-loop */
        queueEndElementIdx = (sint16_least)(CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUESTARTIDX(txBufferCfgIdx));
        /* process from last to first */
        /* #220 Compute the next buffered PDU ID with the highest priority */
        for(queueElementIdx = (((sint16_least)CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUESTOPIDX(txBufferCfgIdx)) - (sint16_least)1); queueElementIdx >= queueEndElementIdx; queueElementIdx--)
        { 
          elem = CANIF_VAR_TXBUFFERPRIOBYCANIDBITQUEUE_QUEUEFLAGS((uint16_least)queueElementIdx);
          if(elem != (CanIf_TxQueueFlagType)0) /* is there any flag set in the queue element? */
          {
            /* iterate through all flags and request transmission for highest priority PDU */
            for(elementBitIdx = (sint8_least)elemStartBitIdx; elementBitIdx >= (sint8_least)0; elementBitIdx--)
            { 
              if( ( elem & CanShiftLookUp[elementBitIdx] ) != (CanIf_TxQueueFlagType)0)
              {
                PduId = ((((PduIdType)queueElementIdx - (PduIdType)queueEndElementIdx) << kCanTxQueueShift) + (PduIdType)elementBitIdx) + (PduIdType)CANIF_CFG_TXBUFFERPRIOBYCANIDBITQUEUE_BITPOS2TXPDUIDOFFSET(txBufferCfgIdx);
                /* #230 Call CanIf_TxQueueTransmit() for the corresponding TxPdu ID */
                retval = CanIf_TxQueueTransmit(PduId);
                break;
              }
            }
            /* transmission has been requested for the buffered PDU ID with the highest priority */
            break;
          }
        }
      }
#  else
      /* #300 PRIO_BY_CANID: BYTE_QUEUE handling: */
      txBufferPrioByCanIdBaseIdx = CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_BUFFERBASEIDX(txBufferCfgIdx);
       
      /* #310 Anything buffered? */
      if (CanIf_GetTxQueueCounter(txBufferPrioByCanIdBaseIdx) != 0u)
      {
        /* #320 Compute the next buffered PDU ID with the highest priority */  
        for (idx2MappedTxPdus = ((CanIf_AnyIdxType)CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_STOPIDX2MAPPEDTXPDUS(txBufferCfgIdx)-1u); idx2MappedTxPdus >= CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_STARTIDX2MAPPEDTXPDUS(txBufferCfgIdx); idx2MappedTxPdus--)     
        {
          CanIf_AnyIdxType TxPduId;
          TxPduId = CANIF_CFG_TXBUFFERPRIOBYCANIDBYTEQUEUE_MAPPEDTXPDUS(idx2MappedTxPdus);
          
          if (CANIF_VAR_TXBUFFERPRIOBYCANID_QUEUE(CANIF_CFG_TX_QUEUEINDEX(TxPduId), eQueued) != 0u)
          {
            /* Send and remove from queue */
            /* #330 Call CanIf_TxQueueTransmit() for the corresponding TxPdu ID */
            retval = CanIf_TxQueueTransmit((PduIdType)TxPduId);
            break;
          }
        }
      }
#  endif
      break;
# endif  
# if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
    case CANIF_TXBUFFER_HANDLINGTYPE_FIFO:
      /* #400 FIFO buffer handling */
      txBufferFifoBaseIdx = CANIF_CFG_TXBUFFERFIFO_BUFFERBASEIDX(txBufferCfgIdx);
      txBufferFifoQueueBaseStartIdx = CANIF_CFG_TXBUFFERFIFO_QUEUEBASESTARTIDX(txBufferCfgIdx);
      /* #410 Anything buffered? */
      if (CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eQueueCounter) != 0u)
      {
#  if (CANIF_CANCEL_SUPPORT_API == STD_ON)
        /* #420 Some entries in CanIf_TxFifoQueueBase may be cancelled */
        txBufferFifoActReadIdx = CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx);
        /* #430 Repeat until a queued element is found or the queue is empty */
        while ((CANIF_VAR_TXBUFFERFIFO_QUEUEBASE((txBufferFifoActReadIdx + txBufferFifoQueueBaseStartIdx), eQueued) == 0u) && ((CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eQueueCounter)) != 0u)) 
        {
          /* #440 Decrement ReadIdx and manage the underflow */
          CANIF_VAR_TXBUFFERFIFO_BUFFERBASE( txBufferFifoBaseIdx, eReadIdx) ++;  /* SBSW_CANIF_37 */

          if(CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx) == CANIF_CFG_TXBUFFERFIFO_QUEUESIZE(txBufferCfgIdx)) 
          {
            CANIF_VAR_TXBUFFERFIFO_BUFFERBASE( txBufferFifoBaseIdx, eReadIdx) = 0; /* SBSW_CANIF_37 */
          }
          
          /* #450 Decrement the FIFO-counter */
          CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eQueueCounter)--; /* SBSW_CANIF_37 */
          
          /* #460 Update the FIFO-ReadIdx */
          txBufferFifoActReadIdx = CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx);
        }
        /* #500 Is FIFO already empty? */
        if (CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eQueueCounter) != 0u)
#  endif  
        {
          /* #510 If any valid Tx-PDU within the FIFO found, transmit it. */
          txBufferFifoActReadIdx = CANIF_VAR_TXBUFFERFIFO_BUFFERBASE(txBufferFifoBaseIdx, eReadIdx);
          retval = CanIf_TxQueueTransmit(CANIF_VAR_TXBUFFERFIFO_QUEUEBASE((txBufferFifoActReadIdx + txBufferFifoQueueBaseStartIdx), eTxPduId));
        }
      }
      break;
# endif            
    default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
      break;
  }
  return retval;
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif


/* \trace CANIF-3550 */
#if (CANIF_VERSION_INFO_API == STD_ON)
/* \trace SPEC-1896 */
/**********************************************************************************************************************
 *  CanIf_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, CANIF_CODE) CanIf_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_VAR) VersionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter VersionInfo is valid */
  if (VersionInfo == NULL_PTR)
  {
    /* \trace SPEC-5235 */
    errorId = CANIF_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation --------------------------------------------- */

    /* \trace SPEC-3552 */
    /* #100 Get the version information: vendor ID, module ID, SW version */
    VersionInfo->vendorID         = CANIF_VENDOR_ID; /* SBSW_CANIF_9 */
    VersionInfo->moduleID         = CANIF_MODULE_ID; /* SBSW_CANIF_9 */
    VersionInfo->sw_major_version = CANIF_SW_MAJOR_VERSION; /* SBSW_CANIF_9 */
    VersionInfo->sw_minor_version = CANIF_SW_MINOR_VERSION; /* SBSW_CANIF_9 */
    VersionInfo->sw_patch_version = CANIF_SW_PATCH_VERSION; /* SBSW_CANIF_9 */
  }

  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_GETVERSIONINFO_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif


/**********************************************************************************************************************
 *  CanIf_InitMemory
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, CANIF_CODE) CanIf_InitMemory(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  CANIF_CHANNEL_CANTYPE_LOCAL
  
  /* ----- Implementation ----------------------------------------------- */
#if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #100 Initialize the configuration pointer */
  CanIf_ConfigDataPtr = NULL_PTR;

# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  CanIf_SystemInit = FALSE; /* ESCAN00083271 */
# endif
#endif /* CANIF_USE_INIT_POINTER == STD_ON */

# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  for (controller = 0; controller < (sizeof(CanIf_CtrlStates) / sizeof(CanIf_CtrlStatesType)); controller++)
# endif
  {
    /* #110 Run through all CAN channels and set the state to UNINIT */
    CanIf_SetCtrlMode(CanIf_Controller_Value_Local, CANIF_CS_UNINIT);  /* SBSW_CANIF_24 */
  } /* FOR-loop all CAN channels */
}


#if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
# if (CANIF_TRANSMIT_BUFFER_FIFO == STD_OFF)
#  if (CANIF_TRANSMIT_CANCELLATION == STD_ON)
/* \trace SPEC-3716 */
/**********************************************************************************************************************
 *  CanIf_CancelTxConfirmation()
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
 *
 */
FUNC(void, CANIF_CODE) CanIf_CancelTxConfirmation(PduIdType CanTxPduId, P2CONST(Can_PduType, AUTOMATIC, CANIF_CBK_DRV_VAR) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#    if (CANIF_DEV_ERROR_DETECT == STD_ON)
#     if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
#     endif
  /* #20 Check if parameter PduInfoPtr is valid */
  if (PduInfoPtr == NULL_PTR)
  {
    errorId = CANIF_E_PARAM_POINTER;
  }
  /* #30 Check if parameter PduInfoPtr->swPduHandle is valid */
  else if (PduInfoPtr->swPduHandle >= CANIF_CFG_MAX_TXPDUS)
  {
    /* \trace SPEC-3712 */
    errorId = CANIF_E_PARAM_LPDU;
  }
  /* #40 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CANIF_CFG_TX_CONTROLLER(PduInfoPtr->swPduHandle)) == CANIF_CS_UNINIT )
  {
    /* \trace SPEC-3708, SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
#     if ((CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON) && (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))
  /* #50 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CANIF_CFG_TX_CONTROLLER(PduInfoPtr->swPduHandle)))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#     endif
  else
#    endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Is TxPDU a BasicCAN-PDU and has it a buffer? */
    if (CANIF_CFG_MAILBOX_HASTXBUFFER(CANIF_CFG_TX_HTH(PduInfoPtr->swPduHandle))) /* COV_CANIF_GENDATA_FAILURE */
    {
      /* #110 Verify the DLC of cancelled Tx-PDU (only if FD-Tx-queue is configured) */
#    if(CANIF_STATIC_FD_TXQUEUE == STD_ON)
      if(PduInfoPtr->length <= CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_MAXDATALENGTH(PduInfoPtr->swPduHandle))
#    else
      if(PduInfoPtr->length <= CANIF_STATIC_BUFFER_SIZE)
#    endif
      {
        /* #120 Check if cancelled Tx-PDU is already buffered in Tx-queue (critical section is used) */
        CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_1);
        if (CanIf_SetPrioByCanIdTxPduAsQueued(PduInfoPtr->swPduHandle) == E_OK)
        {
          CanIf_TxBufferPrioByCanIdQueuePdu(PduInfoPtr); /* SBSW_CANIF_5 */
        }
        else
        {
          /* #130 Newer Tx-PDU is already buffered, discard the cancelled one */
        }
        CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_1);
      }
#    if ((CANIF_STATIC_FD_TXQUEUE == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_ON))
      else
      {
        errorId = CANIF_E_PARAM_DLC;
      }
#    endif
      /* #140 Trigger the transmission of the queue */
      CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_2);
      (void)CanIf_TxQueueTreatment((CanIf_HwHandleType)CANIF_CFG_TX_HTH(PduInfoPtr->swPduHandle));
      CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_2); /* lock over queue handling + write call (driver does not expect direct call inbetween) */
    }
    else
    {
      /* FullCANs won't be cancelled */
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#    if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CANCELTXCONFIRMATION_API, errorId);
  }
#    else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#    endif
  CANIF_DUMMY_STATEMENT(CanTxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#  endif
# endif
#endif


/* \trace SPEC-4718 */
#if (CANIF_CANCEL_SUPPORT_API == STD_ON)
/* \trace SPEC-4715 */
/**********************************************************************************************************************
 *  CanIf_CancelTransmit()
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
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CancelTransmit(PduIdType CanTxPduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_OK;
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ((CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON))
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    retval = E_NOT_OK;
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON) */
# if ((CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME) || (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))
#  if (CANIF_DEV_ERROR_DETECT == STD_ON) 
  /* #20 Check if parameter CanTxPduId is valid if a CanTxPduId indirection is done. */
  if (CanTxPduId >= CANIF_CFG_MAX_ULTXPDUS)
  {
    retval = E_NOT_OK;
    /* \trace SPEC-2007 */
    errorId = CANIF_E_INVALID_TXPDUID;
  }
  else
#  endif
  {
    /* for PB and LT configurations the TxPduId order between CanIF and higher layers may differ and needs to be indirected */
    CanTxPduId = CANIF_CFG_TXPDUID2INTTXPDUID(CanTxPduId); /* PRQA S 1338 */ /* MD_CanIf_Rule17.8 */
# endif
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
    /* #30 Check if parameter CanTxPduId is valid */
    if (CanTxPduId >= CANIF_CFG_MAX_TXPDUS)
    {
      retval = E_NOT_OK;
      /* \trace SPEC-2007 */
      errorId = CANIF_E_INVALID_TXPDUID;
    }
    else
# endif        
    {
      {
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
        /* #40 Check if CAN channel is initialized */
        if (CanIf_GetCtrlMode(CANIF_CFG_TX_CONTROLLER(CanTxPduId)) == CANIF_CS_UNINIT)
        {
          retval = E_NOT_OK;
          errorId = CANIF_E_UNINIT;
        }
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#   if (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
        /* #50 Check if corresponding CanDrv is available in current identity */
        else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CANIF_CFG_TX_CONTROLLER(CanTxPduId)))
        {
          retval = E_NOT_OK; /* ESCAN00093796 */
          errorId = CANIF_E_PARAM_CONTROLLERID;
        }
#   endif
#  endif
        else
# endif /* CANIF_DEV_ERROR_DETECT == STD_ON */
        {
          
          /* ----- Implementation ----------------------------------------------- */
          CanIf_AnyIdxType  hth;
# if  (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
          CANIF_CHANNEL_CANTYPE_LOCAL
          controller = CANIF_CFG_TX_CONTROLLER(CanTxPduId);
# endif
          hth = CANIF_CFG_TX_HTH(CanTxPduId);
          {
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
            Can_HwHandleType canDrvHth;
            CanIf_Can_CancelTxFctType canCancelTxFct;
            canCancelTxFct = CANIF_GET_CANCANCELTXFCT(CanIf_Controller_Value_Local);
            
            canDrvHth = (Can_HwHandleType)(hth - CANIF_CFG_MULTIPLECANDRV_HXHOFFSET(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CanIf_Controller_Value_Local)));

            if (canCancelTxFct != NULL_PTR)
# endif
            {
# if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
              /* #100 Check if it is a buffered Tx-PDU */
              if (CANIF_CFG_MAILBOX_HASTXBUFFER(hth)) /* COV_CANIF_NO_TX_BUFFER */
              {
                /* #200 Cancel the Tx-PDU from Tx-buffer (critical section is used) */
                CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_1);
                /* #210 Do handle depending on corresponding Tx-buffer handling type */
                switch (CANIF_CFG_MAILBOX_TXBUFFERHANDLINGTYPE(hth))
                {
#  if (CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON)
                  /* #300 PRIOBYCANID buffer handling */
                  case CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID:
                    (void)CanIf_ClearPrioByCanIdTxPduAsQueued(CanTxPduId);
                    break;
#  endif
#  if (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON)
                  /* #400 FIFO buffer handling */
                  case CANIF_TXBUFFER_HANDLINGTYPE_FIFO:
                    {
                      CanIf_AnyIdxType queueindex;
                      CanIf_AnyIdxType txBufferCfgIdx;
                      queueindex = CANIF_CFG_TX_QUEUEINDEX(CanTxPduId);
                      txBufferCfgIdx = CANIF_CFG_MAILBOX_TXBUFFERIDX(hth);
                  
                      /* #410 Set the flag in CanIf_TxQueueIndex2FifoEl to invalid if set */
                      if(CANIF_VAR_TXBUFFERFIFO_QUEUEIDX2FIFOEL(queueindex) != CANIF_NO_ENTRY_IN_TX_FIFO)
                      {
                        CANIF_VAR_TXBUFFERFIFO_QUEUEBASE((CANIF_VAR_TXBUFFERFIFO_QUEUEIDX2FIFOEL(queueindex) + CANIF_CFG_TXBUFFERFIFO_QUEUEBASESTARTIDX(txBufferCfgIdx)), eQueued) = 0; /* set Fifo position to invalid */ /* SBSW_CANIF_39 */
                        CANIF_VAR_SET_TXBUFFERFIFO_QUEUEIDX2FIFOEL(queueindex, CANIF_NO_ENTRY_IN_TX_FIFO); /* SBSW_CANIF_36 */
                      }
                    }
                    break;
#  endif
                default: /* COV_CANIF_GENDATA_FAILURE */
                    break;
                }
                /* ESCAN00054772 */
                CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_1);
                /* #220 Cancel the Tx-PDU from CAN driver */
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
                canCancelTxFct(canDrvHth, CanTxPduId); /* SBSW_CANIF_43 */  
#  else
                canCancelTxFct((CanIf_HwHandleType)hth, CanTxPduId);
#  endif
              }
              else
              {
                /* #120 FullCAN or BasicCAN without buffer: Cancel the Tx-PDU from CAN driver */
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
                canCancelTxFct(canDrvHth, CanTxPduId); /* SBSW_CANIF_43 */  
#  else
                canCancelTxFct((CanIf_HwHandleType)hth, CanTxPduId);
#  endif                
              }
# else  /* CANIF_TRANSMIT_BUFFER */
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
              canCancelTxFct(canDrvHth, CanTxPduId); /* SBSW_CANIF_43 */  
#  else
              canCancelTxFct((CanIf_HwHandleType)hth, CanTxPduId);
#  endif
# endif /* CANIF_TRANSMIT_BUFFER */
            }
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
            else  /* if (canCancelTxFct != NULL_PTR) */
            {
              retval = E_NOT_OK;
            }
# endif
          }
        }
      }
    }
# if ((CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME) || (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))
  }
# endif
  
  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CANCELTRANSMIT_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif /* CANIF_CANCEL_SUPPORT_API == STD_ON */


#if (CANIF_CANCEL_SUPPORT_API == STD_ON)
/**********************************************************************************************************************
 *  CanIf_CancelTxNotification()
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
 */
FUNC(void, CANIF_CODE) CanIf_CancelTxNotification(PduIdType PduId, CanIf_CancelResultType IsCancelled)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter PduId is valid */
  if (PduId >=  CANIF_CFG_MAX_TXPDUS)
  {
    errorId = CANIF_E_PARAM_LPDU;
  }
  /* #30 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CANIF_CFG_TX_CONTROLLER(PduId)) == CANIF_CS_UNINIT)
  {
    errorId = CANIF_E_UNINIT;
  }
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#   if (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CANIF_CFG_TX_CONTROLLER(PduId)))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#   endif 
#  endif
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Process only if CAN channel is active */
    if (CanIf_GetCtrlMode(CANIF_CFG_TX_CONTROLLER(PduId)) == CANIF_CS_STARTED)
    {
      if ( (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(PduId)) == CANIF_GET_ONLINE) ||
           (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(PduId)) == CANIF_GET_TX_ONLINE)
# if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
         || (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(PduId)) == CANIF_GET_ONLINE_WAKF)
         || (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(PduId)) == CANIF_GET_TX_ONLINE_WAKF)
# endif
       )
      {
#if ((CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID == STD_ON) || (CANIF_TRANSMIT_BUFFER_FIFO == STD_ON))
        if (CANIF_CFG_MAILBOX_HASTXBUFFER(CANIF_CFG_TX_HTH(PduId))) /* COV_CANIF_NO_TX_BUFFER */
        {
          /* \trace SPEC-1227 */
          /* #110 If Tx-queue is affected send queued messages directly */
          CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_2);
          (void)CanIf_TxQueueTreatment((CanIf_HwHandleType)CANIF_CFG_TX_HTH(PduId));
          /* \trace SPEC-1227 */ /* lock over queue handling + write call (driver does not expect direct call inbetween) */
          CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_2);
        }
# endif
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_TXNOTIFICATION_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CANIF_DUMMY_STATEMENT(IsCancelled); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif


/* \trace SPEC-3595 */
#if (CANIF_TRCV_HANDLING == STD_ON) 
/* \trace SPEC-1933 */
/**********************************************************************************************************************
 *  CanIf_SetTrcvMode()
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
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTrcvMode(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  CANIF_CHANNEL_CANTYPE_LOCAL
# endif

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter TransceiverId is valid */
  if (TransceiverId >= CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE)
  {
    /* \trace SPEC-5064 */
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  if (CANIF_TRCV_MAPPING == STD_ON)
  /* #30 Check if parameter TransceiverId is valid if transceiver mapping is active */
  if (TransceiverId >= CanIf_GetSizeOfTransceiverUpToLowMap())  /* COV_CANIF_GENDATA_FAILURE */
  {
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  endif      
# endif
  {
# if(CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
    /* #40 Check if a CAN channel is mapped to transceiver channel */
    CanIf_Controller_Value_Local = CANIF_CFG_TRCVTOCTRLMAP(TransceiverId);
    if (CanIf_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_CONTROLLER;
    }
    else
#  endif
    if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
    {
      errorId = CANIF_E_UNINIT;
    }
    /* #50 Check if parameter TransceiverMode is valid */
    else if ((TransceiverMode != CANTRCV_TRCVMODE_NORMAL) &&
             (TransceiverMode != CANTRCV_TRCVMODE_STANDBY) &&
             (TransceiverMode != CANTRCV_TRCVMODE_SLEEP))
    {
      /* \trace SPEC-5213 */
      errorId = CANIF_E_PARAM_TRCVMODE; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    else
# endif /* CANIF_DEV_ERROR_DETECT */
    {
      /* ----- Implementation ----------------------------------------------- */

      /* #100 If several transceiver drivers are configured, convert TransceiverId to the driver specific one */
# if (CANIF_TRCV_MAPPING == STD_ON)
      uint8                           lowIndex;
      CanIf_CanTrcvFctTblIdx          lowAddress;
      CanIf_CanTrcv_SetOpModeFctType  lowFct;

      lowIndex   = CANIF_CFG_TRCVUPTOLOWMAP_CHANNELINDEX(TransceiverId);
      lowAddress = CANIF_CFG_TRCVUPTOLOWMAP_DRIVERINDEX(TransceiverId);

      lowFct = CanIf_GetCanTrcv_SetOpModeFctMap(lowAddress);

      if (lowFct != NULL_PTR)
      {
        /* \trace SPEC-1967 */
        /* #110 Pass the request to the transceiver driver */
        retval = lowFct(lowIndex, TransceiverMode);  /* SBSW_CANIF_22 */
      }
# else
      /* \trace SPEC-3586, SPEC-1967 */
      retval = CanTrcv_SetOpMode(TransceiverId, TransceiverMode);
# endif
    }
  } /* Valid TransceiverId */

  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_SETTRCVMODE_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

/* \trace SPEC-3596 */

#if (CANIF_TRCV_HANDLING == STD_ON)

/* \trace SPEC-1937 */
/**********************************************************************************************************************
 *  CanIf_GetTrcvMode()
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
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvMode(P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) TransceiverModePtr, uint8 TransceiverId )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  CANIF_CHANNEL_CANTYPE_LOCAL
# endif

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter TransceiverId is valid */
  if (TransceiverId >= CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE)
  {
    /* \trace SPEC-3593 */
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  if (CANIF_TRCV_MAPPING == STD_ON)
  /* #30 Check if parameter TransceiverId is valid if transceiver mapping is active */
  if (TransceiverId >= CanIf_GetSizeOfTransceiverUpToLowMap()) /* COV_CANIF_GENDATA_FAILURE */
  {
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  endif  
# endif
  {
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
    CanIf_Controller_Value_Local = CANIF_CFG_TRCVTOCTRLMAP(TransceiverId);
    /* #40 Check if a CAN channel is mapped to transceiver channel */
    if (CanIf_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_CONTROLLER;
    }
    else
#  endif
    /* #50 Check if parameter TransceiverModePtr is valid */
    if (TransceiverModePtr == NULL_PTR)
    {
      /* \trace SPEC-5227 */
      errorId = CANIF_E_PARAM_POINTER;
    }
    /* #60 Check if corresponding CAN channel is initialized */
    else if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
    {
      /* \trace SPEC-5238 */
      errorId = CANIF_E_UNINIT;
    }
    else
# endif /* CANIF_DEV_ERROR_DETECT */
    {
      /* ----- Implementation ----------------------------------------------- */

      /* #100 If several transceiver drivers are configured, convert TransceiverId to the driver specific one */
# if (CANIF_TRCV_MAPPING == STD_ON)
      uint8                           lowIndex;
      CanIf_CanTrcvFctTblIdx          lowAddress;
      CanIf_CanTrcv_GetOpModeFctType  lowFct;

      lowIndex   = CANIF_CFG_TRCVUPTOLOWMAP_CHANNELINDEX(TransceiverId);
      lowAddress = CANIF_CFG_TRCVUPTOLOWMAP_DRIVERINDEX(TransceiverId);
      lowFct = CanIf_GetCanTrcv_GetOpModeFctMap(lowAddress);

      if (lowFct != NULL_PTR)
      {
        /* \trace SPEC-1967 */
        /* #110 Pass the request to the transceiver driver */
        retval = lowFct(lowIndex, TransceiverModePtr); /* SBSW_CANIF_44 */
      }
# else
      /* \trace SPEC-3594, SPEC-1967 */
      retval = CanTrcv_GetOpMode(TransceiverId, TransceiverModePtr);  /* SBSW_CANIF_21 */
# endif
    }
  } /* Valid TransceiverId */

  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_GETTRCVMODE_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif


/* \trace SPEC-3600 */
#if (CANIF_TRCV_HANDLING == STD_ON)
/* \trace SPEC-1934 */
/**********************************************************************************************************************
 *  CanIf_GetTrcvWakeupReason()
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
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvWakeupReason(uint8 TransceiverId, P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANIF_APPL_STATE_VAR) TrcvWuReasonPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  CANIF_CHANNEL_CANTYPE_LOCAL
# endif

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter TransceiverId is valid */
  if (TransceiverId >= CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE)
  {
    /* \trace SPEC-5057 */
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  if (CANIF_TRCV_MAPPING == STD_ON)
  /* #30 Check if parameter TransceiverId is valid if transceiver mapping is active */
  if (TransceiverId >= CanIf_GetSizeOfTransceiverUpToLowMap()) /* COV_CANIF_GENDATA_FAILURE */
  {
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  endif              
# endif
  {
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
    CanIf_Controller_Value_Local = CANIF_CFG_TRCVTOCTRLMAP(TransceiverId);
    /* #40 Check if a CAN channel is mapped to transceiver channel */
    if (CanIf_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_CONTROLLER;
    }
    else
#  endif
    /* #50 Check if parameter TrcvWuReasonPtr is valid */
    if (TrcvWuReasonPtr == NULL_PTR)
    {
      /* \trace SPEC-5221 */
      errorId = CANIF_E_PARAM_POINTER;
    }
    /* #60 Check if corresponding CAN channel is initialized */
    else if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
    {
      /* \trace SPEC-5238 */
      errorId = CANIF_E_UNINIT;
    }
    else
# endif /* CANIF_DEV_ERROR_DETECT */
    {
      /* ----- Implementation ----------------------------------------------- */

      /* #100 If several transceiver drivers are configured, convert TransceiverId to the driver specific one */
# if (CANIF_TRCV_MAPPING == STD_ON)
      uint8                                 lowIndex;
      CanIf_CanTrcvFctTblIdx                lowAddress;
      CanIf_CanTrcv_GetBusWuReasonFctType   lowFct;

      lowIndex   = CANIF_CFG_TRCVUPTOLOWMAP_CHANNELINDEX(TransceiverId);
      lowAddress = CANIF_CFG_TRCVUPTOLOWMAP_DRIVERINDEX(TransceiverId);

      /* #110 Pass the request to the transceiver driver */
      lowFct = CanIf_GetCanTrcv_GetBusWuReasonFctMap(lowAddress);

      if (lowFct != NULL_PTR)
      {
        /* \trace SPEC-1967 */
        retval = lowFct(lowIndex, TrcvWuReasonPtr); /* SBSW_CANIF_44 */
      }
# else
      /* \trace SPEC-3598, SPEC-1967 */
      retval = CanTrcv_GetBusWuReason(TransceiverId, TrcvWuReasonPtr); /* SBSW_CANIF_21 */
# endif
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_GETTRCVWAKEUPREASON_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif


/* \trace SPEC-3603 */
#if (CANIF_TRCV_HANDLING == STD_ON)
/* \trace SPEC-3680 */
/**********************************************************************************************************************
 *  CanIf_SetTrcvWakeupMode()
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
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTrcvWakeupMode(uint8 TransceiverId, CanTrcv_TrcvWakeupModeType TrcvWakeupMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  CANIF_CHANNEL_CANTYPE_LOCAL
# endif

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  { 
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter TransceiverId is valid */
  if (TransceiverId >= CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE)
  {
    /* \trace SPEC-5055 */
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  if (CANIF_TRCV_MAPPING == STD_ON)
  /* #30 Check if parameter TransceiverId is valid if transceiver mapping is active */
  if (TransceiverId >= CanIf_GetSizeOfTransceiverUpToLowMap()) /* COV_CANIF_GENDATA_FAILURE */
  {
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  endif      
# endif
  {
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
    CanIf_Controller_Value_Local = CANIF_CFG_TRCVTOCTRLMAP(TransceiverId);
    /* #40 Check if a CAN channel is mapped to transceiver channel */
    if (CanIf_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_CONTROLLER;
    }
    else
#  endif
    /* #50 Check if parameter TrcvWakeupMode is valid */
    if ((TrcvWakeupMode != CANTRCV_WUMODE_ENABLE) &&   
        (TrcvWakeupMode != CANTRCV_WUMODE_DISABLE) &&
        (TrcvWakeupMode != CANTRCV_WUMODE_CLEAR))
    {
      /* \trace SPEC-5049 */
      errorId = CANIF_E_PARAM_TRCVWAKEUPMODE; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    /* #60 Check if corresponding CAN channel is initialized */
    else if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
    {
      /* \trace SPEC-5238 */
      errorId = CANIF_E_UNINIT;
    }
    else
# endif /* CANIF_DEV_ERROR_DETECT */
    {
      /* ----- Implementation ----------------------------------------------- */

      /* #100 If several transceiver drivers are configured, convert TransceiverId to the driver specific one */
# if (CANIF_TRCV_MAPPING == STD_ON)
      uint8                                 lowIndex;
      CanIf_CanTrcvFctTblIdx                lowAddress;
      CanIf_CanTrcv_SetWakeupModeFctType    lowFct;

      lowIndex   = CANIF_CFG_TRCVUPTOLOWMAP_CHANNELINDEX(TransceiverId);
      lowAddress = CANIF_CFG_TRCVUPTOLOWMAP_DRIVERINDEX(TransceiverId);
      lowFct = CanIf_GetCanTrcv_SetWakeupModeFctMap(lowAddress);

      /* #110 Pass the request to the transceiver driver */
      if (lowFct != NULL_PTR)
      {
        /* \trace SPEC-1967 */
        retval = lowFct(lowIndex, TrcvWakeupMode); /* SBSW_CANIF_22 */
      }
# else
      /* \trace SPEC-3602, SPEC-1967 */
      retval = CanTrcv_SetWakeupMode(TransceiverId, TrcvWakeupMode);
# endif
    }
  } /* Valid TransceiverId */

  /* ----- Development Error Report ------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_SETTRCVWAKEUPMODE_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif


/* \trace SPEC-21399 */
#if (CANIF_TRCV_HANDLING == STD_ON)
/* CANIF764, \trace SPEC-5333 */
/**********************************************************************************************************************
 *  CanIf_TrcvModeIndication()
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
 */
FUNC(void, CANIF_CODE) CanIf_TrcvModeIndication(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
  CANIF_CHANNEL_CANTYPE_LOCAL
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* \trace SPEC-5303, NOTE: check the given parameter explicitly -> CASE "CanIfOptimizeOneController" is enabled but NO trcv channel
   * is mapped to CAN channel.
   * */
  /* #20 Check if parameter TransceiverId is valid (consider transceiver mapping if configured) */
  if (TransceiverId >= CANIF_CFG_MAX_CANTRCV_TRCVHANDLEIDPLUSONE)
  {
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
# endif
  {
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
#  if (CANIF_TRCV_MAPPING == STD_ON)
    CanIf_TrcvIdUpper = CANIF_CFG_TRCVUPTOUPPERMAP(TransceiverId); /* PRQA S 1338 */ /* MD_CanIf_Rule17.8 */
#  endif /* CANIF_TRCV_MAPPING == STD_ON */
    CanIf_Controller_Value_Local = CANIF_CFG_TRCVTOCTRLMAP(CanIf_TrcvIdUpper);
# endif /* CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF */

# if(CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
#   if(CANIF_TRCV_MAPPING == STD_ON)
    /* #30 Check if parameter TransceiverId is valid (consider transceiver mapping if configured) */
    if (CanIf_TrcvIdUpper >= CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_TRCV;
    } 
    else
#   endif /* CANIF_TRCV_MAPPING == STD_ON */
    /* #40 Check if a CAN channel is mapped to transceiver channel */
    if (CanIf_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_CONTROLLER;
    }
    else
#  endif /* CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF */
    /* #50 Check if corresponding CAN channel is initialized */
    if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
    {
      errorId = CANIF_E_UNINIT;
    }
    else
# endif
    {
# if (CANIF_DEV_ERROR_DETECT == STD_OFF)
      /* \trace SPEC-5334 */
      if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) != CANIF_CS_UNINIT)
# endif
      {
        /* \trace SPEC-5335 */
        /* #100 Notify the upper layer about the mode transition, if configured */
        CanIf_TrcvModeIndicationFctType  trcvModeIndicationFct;
        trcvModeIndicationFct = CANIF_CFG_TRCVMODEINDICATIONFCT();
        if (trcvModeIndicationFct != NULL_PTR)
        {
          trcvModeIndicationFct(CanIf_TrcvIdUpper, TransceiverMode);  /* SBSW_CANIF_13 */
        }
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_TRCVMODEINDICATION_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(TransceiverId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (CANIF_TRCV_HANDLING == STD_ON) */


#if ((CANIF_TRCV_HANDLING == STD_ON) && (CANIF_PN_TRCV_HANDLING == STD_ON))
/* \trace SPEC-9957 */

/**********************************************************************************************************************
 *  CanIf_ConfirmPnAvailability()
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
 */
FUNC(void, CANIF_CODE) CanIf_ConfirmPnAvailability(uint8 TransceiverId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  CANIF_CHANNEL_CANTYPE_LOCAL
# endif

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* NOTE: check the given parameter explicitly -> CASE "CanIfOptimizeOneController" is enabled but NO trcv channel
   * is mapped to CAN channel.
   * */
  /* #20 Check if parameter TransceiverId is valid (consider transceiver mapping if configured) */
  if (TransceiverId >= CANIF_CFG_MAX_CANTRCV_TRCVHANDLEIDPLUSONE)
  {
    /* \trace SPEC-21351 */
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
# endif
  {
# if (CANIF_TRCV_MAPPING == STD_ON)
    CanIf_TrcvIdUpper = CANIF_CFG_TRCVUPTOUPPERMAP(TransceiverId); /* PRQA S 1338 */ /* MD_CanIf_Rule17.8 */
# endif

# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
    CanIf_Controller_Value_Local = CANIF_CFG_TRCVTOCTRLMAP(CanIf_TrcvIdUpper);
#   if (CANIF_TRCV_MAPPING == STD_ON)
    /* #30 Check if parameter TransceiverId is valid (consider transceiver mapping if configured) */
    if (CanIf_TrcvIdUpper >= CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_TRCV;
    }
    else
#   endif /* CANIF_TRCV_MAPPING == STD_ON */
    /* #40 Check if a CAN channel is mapped to transceiver channel */
    if (CanIf_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_CONTROLLER;
    }
    else
#  endif /* CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF */
    /* \trace SPEC-5238, SPEC-21337 */
    /* #50 Check if corresponding CAN channel is initialized */
    if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
    {
      errorId = CANIF_E_UNINIT;
    }
    else
# endif
    {
      /* ----- Implementation ----------------------------------------------- */
      /* CANIF753 */
      /* #100 If configured notify the upper layer about the PN availability */
      CanIf_ConfirmPnAvailabilityFctType cbkFct;
      cbkFct = CANIF_CFG_CONFIRMPNAVAILABILITYFCT();

      if (cbkFct != NULL_PTR)
      { 
        cbkFct(CanIf_TrcvIdUpper); /* SBSW_CANIF_13 */
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CONFIRMPNAVAILABILITY_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(TransceiverId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif  
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ((CANIF_TRCV_HANDLING == STD_ON) && (CANIF_PN_TRCV_HANDLING == STD_ON)) */


#if ((CANIF_TRCV_HANDLING == STD_ON) && (CANIF_PN_TRCV_HANDLING == STD_ON))
/* CANIF762 */
/**********************************************************************************************************************
 *  CanIf_ClearTrcvWufFlagIndication()
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
 */
FUNC(void, CANIF_CODE) CanIf_ClearTrcvWufFlagIndication(uint8 TransceiverId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  CANIF_CHANNEL_CANTYPE_LOCAL
# endif
    
  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* \trace SPEC-21321, NOTE: check the given parameter explicitly -> CASE "CanIfOptimizeOneController" is enabled but NO trcv channel
  * is mapped to CAN channel.
  * */
  /* #20 Check if parameter TransceiverId is valid (consider transceiver mapping if configured) */
  if (TransceiverId >= CANIF_CFG_MAX_CANTRCV_TRCVHANDLEIDPLUSONE)
  {
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
# endif
  {
# if (CANIF_TRCV_MAPPING == STD_ON)
    CanIf_TrcvIdUpper = CANIF_CFG_TRCVUPTOUPPERMAP(TransceiverId); /* PRQA S 1338 */ /* MD_CanIf_Rule17.8 */
# endif

# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
    CanIf_Controller_Value_Local = CANIF_CFG_TRCVTOCTRLMAP(CanIf_TrcvIdUpper);
#   if (CANIF_TRCV_MAPPING == STD_ON)
    /* #30 Check if parameter TransceiverId is valid (consider transceiver mapping if configured) */
    if (CanIf_TrcvIdUpper >= CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_TRCV;
    }
    else
#   endif /* CANIF_TRCV_MAPPING == STD_ON */
    /* #40 Check if a CAN channel is mapped to transceiver channel */
    if (CanIf_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_CONTROLLER;
    }
    else
#  endif /* CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF */
    /* \trace SPEC-21345, SPEC-5238 */
      /* #50 Check if corresponding CAN channel is initialized */
    if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
    {
      errorId = CANIF_E_UNINIT;
    }
    else
# endif
    {
      
      /* ----- Implementation ----------------------------------------------- */

      /* CANIF757 */
      /* #100 If configured notify the upper layer that WufFlag was cleared */
      CanIf_ClearTrcvWufFlagIndicationFctType cbkFct;
      cbkFct = CANIF_CFG_CLEARTRCVWUFFLAGINDICATIONFCT();

      if (cbkFct != NULL_PTR)
      {
        cbkFct(CanIf_TrcvIdUpper);  /* SBSW_CANIF_13 */
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CLEARTRCVWUFFLAGINDICATION_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(TransceiverId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ((CANIF_TRCV_HANDLING == STD_ON) && (CANIF_PN_TRCV_HANDLING == STD_ON)) */


#if ((CANIF_TRCV_HANDLING == STD_ON) && (CANIF_PN_TRCV_HANDLING == STD_ON))
/* CANIF763 */
/**********************************************************************************************************************
 *  CanIf_CheckTrcvWakeFlagIndication()
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
 */
FUNC(void, CANIF_CODE) CanIf_CheckTrcvWakeFlagIndication(uint8 TransceiverId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  CANIF_CHANNEL_CANTYPE_LOCAL
# endif
    
  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* \trace SPEC-21324, NOTE: check the given parameter explicitly -> CASE "CanIfOptimizeOneController" is enabled but NO trcv channel
  * is mapped to CAN channel.
  * */
  /* #20 Check if parameter TransceiverId is valid (consider transceiver mapping if configured) */
  if (TransceiverId >= CANIF_CFG_MAX_CANTRCV_TRCVHANDLEIDPLUSONE)
  {
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
# endif
  {
# if (CANIF_TRCV_MAPPING == STD_ON)
    CanIf_TrcvIdUpper = CANIF_CFG_TRCVUPTOUPPERMAP(TransceiverId); /* PRQA S 1338 */ /* MD_CanIf_Rule17.8 */
# endif

# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
    CanIf_Controller_Value_Local = CANIF_CFG_TRCVTOCTRLMAP(CanIf_TrcvIdUpper);
#   if (CANIF_TRCV_MAPPING == STD_ON)
    /* #30 Check if parameter TransceiverId is valid (consider transceiver mapping if configured) */
    if (CanIf_TrcvIdUpper >= CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_TRCV;
    }
    else
#   endif /* CANIF_TRCV_MAPPING == STD_ON */
    /* #40 Check if a CAN channel is mapped to transceiver channel */
    if (CanIf_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_CONTROLLER;
    }
    else
#  endif /* CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF */
    /* \trace SPEC-21350, SPEC-5238 */
    /* #50 Check if corresponding CAN channel is initialized */
    if (CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
    {
      errorId = CANIF_E_UNINIT;
    }
    else
# endif /* CANIF_DEV_ERROR_DETECT == STD_ON */
    {
      /* ----- Implementation ----------------------------------------------- */
      /* CANIF759 */
      /* #100 If configured notify the upper layer that wake flag was checked */
      CanIf_CheckTrcvWakeFlagIndicationFctType cbkFct;
      cbkFct = CANIF_CFG_CHECKTRCVWAKEFLAGINDICATIONFCT();

      if (cbkFct != NULL_PTR)
      {
        cbkFct(CanIf_TrcvIdUpper);  /* SBSW_CANIF_13 */
      }
    }
  }

  /* ----- Development Error Report ------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CHECKTRCVWAKEFLAGINDICATION_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(TransceiverId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif  
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ((CANIF_TRCV_HANDLING == STD_ON) && (CANIF_PN_TRCV_HANDLING == STD_ON)) */


#if ((CANIF_TRCV_HANDLING == STD_ON) && (CANIF_PN_TRCV_HANDLING == STD_ON))
/* CANIF763 */
/**********************************************************************************************************************
 *  CanIf_ClearTrcvWufFlag()
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
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ClearTrcvWufFlag(uint8 TransceiverId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  CANIF_CHANNEL_CANTYPE_LOCAL
# endif

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter TransceiverId is valid */
  if (TransceiverId >= CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE)
  {
    /* \trace SPEC-21406 */
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  if (CANIF_TRCV_MAPPING == STD_ON)
  /* #30 Check if parameter TransceiverId is valid if transceiver mapping is active */
  if (TransceiverId >= CanIf_GetSizeOfTransceiverUpToLowMap()) /* COV_CANIF_GENDATA_FAILURE */
  {
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  endif      
# endif
  {
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
    CanIf_Controller_Value_Local = CANIF_CFG_TRCVTOCTRLMAP(TransceiverId);
    /* #40 Check if a CAN channel is mapped to transceiver channel */
    if (CanIf_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_CONTROLLER;
    }
    else
#  endif
    /* #50 Check if corresponding CAN channel is initialized */
    if(CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
    {
      /* CANIF767 */
      errorId = CANIF_E_UNINIT;
    }
    else
# endif
    {
      /* ----- Implementation ----------------------------------------------- */

      /* #100 If several transceiver drivers are configured, convert TransceiverId to the driver specific one */
# if (CANIF_TRCV_MAPPING == STD_ON)
      /* \trace SPEC-9964 */
      uint8                                  TrcvChannelId;
      CanIf_CanTrcvFctTblIdx                 TrcvDriverId;
      CanIf_CanTrcv_ClearTrcvWufFlagFctType  lowFct;

      /* Get transceiver IDs */
      TrcvChannelId = CANIF_CFG_TRCVUPTOLOWMAP_CHANNELINDEX(TransceiverId);
      TrcvDriverId = CANIF_CFG_TRCVUPTOLOWMAP_DRIVERINDEX(TransceiverId);

      /* get the corresponding transceiver API */
      lowFct = CanIf_GetCanTrcv_ClearTrcvWufFlagFctMap(TrcvDriverId);

      if (lowFct != (CanIf_CanTrcv_ClearTrcvWufFlagFctType)NULL_PTR)
      {
        /* #110 Pass the request to the transceiver driver */
        retval = lowFct(TrcvChannelId);  /* SBSW_CANIF_22 */
      }
      else
      {
        errorId = CANIF_E_PARAM_TRCV;
        /* retval is already set to E_NOT_OK */
      }
# else
      /* \trace SPEC-9964 */
      retval = CanTrcv_ClearTrcvWufFlag(TransceiverId);
# endif
    }
  } /* Valid TransceiverId */

  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CLEARTRCVWUFFLAG_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ((CANIF_TRCV_HANDLING == STD_ON) && (CANIF_PN_TRCV_HANDLING == STD_ON)) */


#if ((CANIF_TRCV_HANDLING == STD_ON) && (CANIF_PN_TRCV_HANDLING == STD_ON))
/* CANIF761 */
/**********************************************************************************************************************
 *  CanIf_CheckTrcvWakeFlag()
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
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckTrcvWakeFlag(uint8 TransceiverId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
  CANIF_CHANNEL_CANTYPE_LOCAL
# endif

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter TransceiverId is valid */
  if (TransceiverId >= CANIF_CFG_MAX_TRANSCEIVERHANDLEIDPLUSONE)
  {
    /* \trace SPEC-21413 */
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  if (CANIF_TRCV_MAPPING == STD_ON)
  if (TransceiverId >= CanIf_GetSizeOfTransceiverUpToLowMap()) /* COV_CANIF_GENDATA_FAILURE */
  {
    errorId = CANIF_E_PARAM_TRCV;
  }
  else
#  endif               
# endif
  {
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
    CanIf_Controller_Value_Local = CANIF_CFG_TRCVTOCTRLMAP(TransceiverId);
    /* #30 Check if a CAN channel is mapped to transceiver channel */
    if (CanIf_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
    {
      errorId = CANIF_E_PARAM_CONTROLLER;
    }
    else
#  endif
    /* #40 Check if corresponding CAN channel is initialized */
    if(CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
    {
      /* CANIF768 */
      errorId = CANIF_E_UNINIT;
    }
    else
# endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) */
    {
      /* ----- Implementation ----------------------------------------------- */
      /* #100 If several transceiver drivers are configured, convert TransceiverId to the driver specific one */
# if (CANIF_TRCV_MAPPING == STD_ON)
      /* \trace SPEC-9961 */
      uint8                               TrcvChannelId;
      CanIf_CanTrcvFctTblIdx              TrcvDriverId;
      CanIf_CanTrcv_CheckWakeFlagFctType  lowFct;

      /* Get transceiver IDs */
      TrcvChannelId = CANIF_CFG_TRCVUPTOLOWMAP_CHANNELINDEX(TransceiverId);
      TrcvDriverId = CANIF_CFG_TRCVUPTOLOWMAP_DRIVERINDEX(TransceiverId);

      /* get the corresponding transceiver API */
      lowFct = CanIf_GetCanTrcv_CheckWakeFlagFctMap(TrcvDriverId);

      if (lowFct != (CanIf_CanTrcv_CheckWakeFlagFctType)NULL_PTR)
      {
        /* #110 Pass the request to the transceiver driver */
        retval = lowFct(TrcvChannelId);  /* SBSW_CANIF_22 */
      }
      else
      {
        errorId = CANIF_E_PARAM_TRCV;
        /* retval is already set to E_NOT_OK */
      }
# else
      retval = CanTrcv_CheckWakeFlag(TransceiverId);
# endif /* (CANIF_TRCV_MAPPING == STD_ON) */
    }
  } /* Valid TransceiverId */

  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CHECKTRCVWAKEFLAG_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ((CANIF_TRCV_HANDLING == STD_ON) && (CANIF_PN_TRCV_HANDLING == STD_ON)) */


/* \trace SPEC-1898, SPEC-3681 */
#if (CANIF_WAKEUP_SUPPORT == STD_ON)
/* \trace SPEC-1910 */
/**********************************************************************************************************************
 *  CanIf_CheckWakeup()
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
 *
 *
 *
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* \trace SPEC-5345 */
  Std_ReturnType retval = E_OK; /* WakeUp request will be accepted */
  
  uint8 errorId = CANIF_E_NO_ERROR;
  Std_ReturnType localRetval;
  EcuM_WakeupSourceType wokenUpSources;
  uint8 numWUsrc;
  wokenUpSources = 0u;
       
  /* ----- Development Error Checks ------------------------------------- */
# if ((CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON))
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    retval = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif

  /* ----- Implementation ----------------------------------------------- */
  {
    /* #100 Run through all configured wake-up sources */
    /* Find the first WakeUp Source which pretends to be the responsible */
    for (numWUsrc = 0u; numWUsrc < CANIF_CFG_MAX_WAKEUPSOURCES; numWUsrc++)
    {
      EcuM_WakeupSourceType                 wuSrc;
      CanIf_WakeUpTargetType                wuTrgtmodule;
      uint8                                 wuTrgtaddress;
      CANIF_WUCHANNEL_CANTYPE_LOCAL

      /* #110 Acquire wake-up source information: wake-up source value, module (CAN / transceiver), channel ID */
      wuSrc         = CANIF_CFG_WAKEUP_WAKEUPSOURCE(numWUsrc);
      wuTrgtmodule  = CANIF_CFG_WAKEUP_WAKEUPTARGETMODULE(numWUsrc);
      wuTrgtaddress = CANIF_CFG_WAKEUP_WAKEUPTARGETADDRESS(numWUsrc);
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION==STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
      /* Find the correct CAN Controller */
      /* indirect check of wake-up-source -> \trace SPEC-3687 */
      wuController = CANIF_CFG_WAKEUP_CONTROLLER(numWUsrc);
# endif
      /* Initialize localRetval for WakeUpSources which are not handled by CanIf */
      localRetval = E_NOT_OK;
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
      /* DET error occurred other sources will be checked return value will be E_NOT_OK */
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
      /* #120 Check the CAN channel parameter */
      if (CanIf_WU_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
      {
        retval = E_NOT_OK;
        /* \trace SPEC-3687 */
        errorId = CANIF_E_PARAM_WAKEUPSOURCE;
      }
      else
#  endif /* CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF */
      /* #130 Check if CAN channel is initialized */
      if (CanIf_GetCtrlMode(CanIf_WU_Controller_Value_Local) == CANIF_CS_UNINIT)
      {
        retval = E_NOT_OK;
        /* \trace SPEC-5238 */
        errorId = CANIF_E_UNINIT;
      }
      else
# endif /* CANIF_DEV_ERROR_DETECT == STD_ON */
      {
        /* #140 Is it the wake-up source which shall be checked for wake-up? */
        if ((WakeupSource & wuSrc) != 0u)
        {
          /* \trace SPEC-5284 */
          /* #150 Process only if CAN channel is either in SLEEP or in STOP */
          if ((CanIf_GetCtrlMode(CanIf_WU_Controller_Value_Local) == CANIF_CS_SLEEP) || (CanIf_GetCtrlMode(CanIf_WU_Controller_Value_Local) == CANIF_CS_STOPPED))
          {
            /* #200 If it is a wake-up source of a CAN channel pass the request to the corresponding CAN channel */
            if (wuTrgtmodule == CANIF_WAKEUPREQUEST_CAN)
            {
              /* \trace SPEC-3684, SPEC-1967 */
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#  if (CANIF_DEV_ERROR_DETECT == STD_ON)
              if (wuTrgtaddress >= CanIf_GetSizeOfCanChannelIdUpToLowMap()) /* COV_CANIF_GENDATA_FAILURE */
              {
                errorId = CANIF_E_PARAM_CONTROLLERID;
                retval = E_NOT_OK;
              }
              else                  
#   if(CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON)
              /* #210 Check if corresponding CanDrv is available in current identity */
              if (!CANIF_CFG_IS_CANDRVINDEXVALID(wuTrgtaddress))
              {
                errorId = CANIF_E_PARAM_WAKEUPSOURCE;
                retval = E_NOT_OK;
              }
              else
#   endif                  
#  endif
              {
                CanIf_Can_CheckWakeupFctType canCheckWakeupFct;
                canCheckWakeupFct = CanIf_GetCan_CheckWakeupFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(wuTrgtaddress));
                if (canCheckWakeupFct != NULL_PTR)
                {
                  localRetval = canCheckWakeupFct(CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(wuTrgtaddress));  /* SBSW_CANIF_41 */
                }
              }
# else /* CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON */
              localRetval = Can_CheckWakeup(wuTrgtaddress);
# endif /* CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON */
            } /* wuTrgtmodule == CANIF_WAKEUPREQUEST_CAN */
# if (CANIF_TRCV_HANDLING == STD_ON)
            /* #300 If it is wake-up source of a transceiver channel pass the request to the corresponding transceiver channel */
            else if (wuTrgtmodule == CANIF_WAKEUPREQUEST_TRCV)
            {
#  if (CANIF_TRCV_MAPPING == STD_ON) /* more than one transceiver respectively controller */
              /* Indirection here */
              uint8                                 lowIndex;
              CanIf_CanTrcvFctTblIdx                lowAddress;
              CanIf_CanTrcv_CheckWakeupFctType   lowFct;
#   if (CANIF_DEV_ERROR_DETECT == STD_ON)                        
              if (wuTrgtaddress >= CanIf_GetSizeOfTransceiverUpToLowMap()) /* COV_CANIF_GENDATA_FAILURE */
              {
                errorId = CANIF_E_PARAM_TRCV;
                retval = E_NOT_OK;
              }
              else                  
#   endif                  
              {
                lowIndex   = CANIF_CFG_TRCVUPTOLOWMAP_CHANNELINDEX(wuTrgtaddress); /* get the call-parameter for the transceiver-function */
                lowAddress = CANIF_CFG_TRCVUPTOLOWMAP_DRIVERINDEX(wuTrgtaddress);
       
                /* get the corresponding transceiver-function */
                lowFct = CanIf_GetCanTrcv_CheckWakeupFctMap(lowAddress);
       
                if (lowFct != NULL_PTR)
                {
                  /* call the corresponding transceiver function */
                  /* \trace SPEC-1967 */
                  localRetval = lowFct(lowIndex);  /* SBSW_CANIF_22 */
                }
              }
#  else  /* CANIF_TRCV_MAPPING -> only one transceiver respectively one controller */
              /* \trace SPEC-3684, SPEC-1967 */
              localRetval = CanTrcv_CheckWakeup(wuTrgtaddress);
#  endif /* (CANIF_TRCV_MAPPING == STD_ON) */
            } /* wuTrgtmodule == CANIF_WAKEUPREQUEST_TRCV */
# endif /* CANIF_TRCV_HANDLING == STD_ON */
            else
            {
              /* CANIF_WAKEUPREQUEST_NONE nothing to do */
            }
  
            /* localRetval is E_OK if the requested source is responsible for the wakeup */
            if (localRetval == E_OK)
            {
              /* #400 Mark if the wake-up request was confirmed by CAN channel / transceiver channel */
              wokenUpSources |= wuSrc;
            }
          } /* CAN controller in CANIF_CS_SLEEP || CANIF_CS_STOPPED? */
          else
          {
            /* != CANIF_CS_SLEEP || CANIF_CS_STOPPED */
            /* \trace SPEC-5284 */
            retval = E_NOT_OK;
            /* Report DET error */
            errorId = CANIF_E_NOT_SLEEP;
          }
        } /* ValidWakeUpSource? */
      } /* DET Error occurred */
    } /* WakeUp-Source FOR-Loop */
  } /* (CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON) */

  /* \trace SPEC-5278, SPEC-5345 */
  if (wokenUpSources == 0u)
  {
    /* #500 If no wake-up sources were confirmed return E_NOT_OK */
    retval = E_NOT_OK;
  }

  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CHECKWAKEUP_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
  } /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
#endif /* CANIF_WAKEUP_SUPPORT */


/* \trace SPEC-1936, SPEC-3693, SPEC-5234 */
#if (CANIF_WAKEUP_VALIDATION == STD_ON)
/* \trace SPEC-1902 */
/**********************************************************************************************************************
 *  CanIf_CheckValidation()
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
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckValidation(EcuM_WakeupSourceType WakeupSource)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_OK;
  uint8 errorId = CANIF_E_NO_ERROR;
  EcuM_WakeupSourceType wokenUpSources;
  uint8  numWUsrc;       
  wokenUpSources = 0u;
  
  /* ----- Development Error Checks ------------------------------------- */
# if ((CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON))
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    retval = E_NOT_OK;
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON) */
  {
    /* ----- Implementation ----------------------------------------------- */
    
    /* #100 Run through all configured wake-up sources */
    for (numWUsrc = 0u; numWUsrc < CANIF_CFG_MAX_WAKEUPSOURCES; numWUsrc++)
    {
      EcuM_WakeupSourceType                 wuSrc;
      CANIF_WUCHANNEL_CANTYPE_LOCAL

      /* #110 Acquire wake-up source information: wake-up source value, module (CAN / transceiver), channel ID */
      wuSrc         = CANIF_CFG_WAKEUP_WAKEUPSOURCE(numWUsrc);
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
      /* Find the correct CAN Controller */
      /* indirect check of wake-up source -> \trace SPEC-3690 */
      wuController  = CANIF_CFG_WAKEUP_CONTROLLER(numWUsrc);
# endif
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
      /* DET error occurred other sources will be checked return value will be E_NOT_OK */
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
      /* #120 Check the CAN channel parameter */
      if (CanIf_WU_Controller_Value_Local >= CANIF_CFG_MAX_CONTROLLER) /* COV_CANIF_GENDATA_FAILURE */
      {
        retval = E_NOT_OK;
        /* \trace SPEC-3690 */
        errorId = CANIF_E_PARAM_WAKEUPSOURCE;
      }
      else
#  endif
      /* #130 Check if CAN channel is initialized */
      if (CanIf_GetCtrlMode(CanIf_WU_Controller_Value_Local) == CANIF_CS_UNINIT)
      {
        retval = E_NOT_OK;
        /* \trace SPEC-5238 */
        errorId = CANIF_E_UNINIT;
      }
      else
# endif /* CANIF_DEV_ERROR_DETECT */
      {

        /* #140 Is it the wake-up source which shall be validated? */
        if ((WakeupSource & wuSrc) != 0u)
        {
          /* #150 Determine whether the passed wake-up source was validated */
          if ( CanIf_GetWakeUpValidationState(CanIf_WU_Controller_Value_Local) == CANIF_WUVALIDATION_DETECTED )
          {
            /* We detected a wake up validation */
            /* #160 Store the wake-up source if it was validated */
            wokenUpSources |= wuSrc;
          }
        } /* ValidWakeUpSource */
        else
        {
          /* Invalid wake up source passed / or no wake up occurred */
          /* Nothing to do */
        }
      } /* DET Error occurred */

      /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
      if (errorId != CANIF_E_NO_ERROR)
      {
        CanIf_Det_ReportError(CANIF_CHECKVALIDATIONUP_API, errorId);
      }
# endif
    } /* WakeUp-Source Loop */
  } /* (CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON) */

  if (wokenUpSources != 0u) /* ESCAN00085941 */
  {
    /* \trace SPEC-1905 */
    /* #200 Only if any wakeup source was validated successfully notify the upper layer */
    CanIf_WakeUpValidationFctType wakeupValidationFct;
    wakeupValidationFct = CANIF_CFG_WAKEUPVALIDATION();
    if (wakeupValidationFct != NULL_PTR)
    {
      wakeupValidationFct(wokenUpSources & WakeupSource); /* SBSW_CANIF_13 */  /* ESCAN00090296 */
    }
  }

# if (CANIF_DEV_ERROR_REPORT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CHECKVALIDATIONUP_API, errorId);
  }
#  endif
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
#endif /* (CANIF_WAKEUP_SUPPORT == STD_ON) && (CANIF_WAKEUP_VALIDATION == STD_ON) */


/* \trace SPEC-3588 */
#if (CANIF_SETDYNAMICTXID_API == STD_ON)
/* \trace SPEC-1899 */
/**********************************************************************************************************************
 *  CanIf_SetDynamicTxId()
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
 */
FUNC(void, CANIF_CODE) CanIf_SetDynamicTxId(PduIdType CanTxPduId, Can_IdType CanId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
  CANIF_CHANNEL_CANTYPE_LOCAL
  PduIdType dynamicPduId;

  /* ----- Development Error Checks ------------------------------------- */
# if ((CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON))
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON) */

# if ((CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME) || (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))
#  if (CANIF_DEV_ERROR_DETECT == STD_ON) 
  /* #20 Check if parameter CanTxPduId is valid if a CanTxPduId indirection is done.*/
  if (CanTxPduId >= CANIF_CFG_MAX_ULTXPDUS)
  {
    /* \trace SPEC-2007 */
    errorId = CANIF_E_INVALID_TXPDUID;
  }
  else
#  endif
  {
    /* for PB and LT configurations the TxPduId order between CanIf and higher layers may differ and needs to be indirected */
    CanTxPduId = CANIF_CFG_TXPDUID2INTTXPDUID(CanTxPduId); /* PRQA S 1338 */ /* MD_CanIf_Rule17.8 */ /* ESCAN00075868 */
# endif      
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
    /* #30 Check if parameter CanTxPduId is valid. */
    if (CanTxPduId >= CANIF_CFG_MAX_TXPDUS)
    {
      /* \trace SPEC-2007 */
      errorId = CANIF_E_INVALID_TXPDUID;
    }
    else
# endif        
    {

# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
      /* Collect configuration data */
      controller = CANIF_CFG_TX_CONTROLLER(CanTxPduId);
# endif
      dynamicPduId = CANIF_CFG_STAT2DYN_INDIRECTION(CanTxPduId);

# if (CANIF_DEV_ERROR_DETECT == STD_ON)
      /* #40 Check if the ID of corresponding dynamic PDU is valid */
      if (dynamicPduId >= CanIf_GetSizeOfDynTxId()) /* COV_CANIF_GENDATA_FAILURE */
      {
        /* no ASR-requirement, just verify the dynamicPduId */
        errorId = CANIF_E_INVALID_TXPDUID;
      }
#  if (CANIF_EXTENDEDID_SUPPORT != STD_ON)
      /* #50 Check if parameter CanId is valid */
      else if ((CanId & (~CANIF_FDFLAG)) > 0x7FFu)
      {
        /* \trace SPEC-3596 */
        errorId = CANIF_E_PARAM_CANID;
      }
#  endif
      /* #60 Check if CAN channel is initialized */
      else if(CanIf_GetCtrlMode(CanIf_Controller_Value_Local) == CANIF_CS_UNINIT)
      {
        /* \trace SPEC-5238 */
        errorId = CANIF_E_UNINIT;
      }
      else
# endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) */
      {
        /* ----- Implementation ----------------------------------------------- */
        /* \trace SPEC-3589 */
# if (CANIF_DEV_ERROR_DETECT == STD_OFF)
        /* #100 Process only if corresponding CAN channel is initialized */
        if(CanIf_GetCtrlMode(CanIf_Controller_Value_Local) != CANIF_CS_UNINIT)
# endif
        {
          /* \trace SPEC-5271 preemptive call of CanTransmit */
          CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_5);
          /* \trace SPEC-1906 identifier extension flag will be passed */
          /* #110 Set the CAN identifier (protected by critical section) */
          CANIF_VAR_DYNTXID(dynamicPduId) = CanId;  /* SBSW_CANIF_14 */
          CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_5);
        }
      } /* (CANIF_DEV_ERROR_DETECT == STD_ON) */
    } /* (CANIF_DEV_ERROR_DETECT == STD_ON) && (CANIF_USE_INIT_POINTER == STD_ON) */
# if ((CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME) || (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))      
  }
# endif  
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_SETDYNAMICTXID_API_ID, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* (CANIF_SETDYNAMICTXID_API == STD_ON) */


/* \trace SPEC-5307, SPEC-5308 */
/**********************************************************************************************************************
 *  CanIf_ControllerModeIndication()
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
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, CANIF_CODE) CanIf_ControllerModeIndication(uint8 ControllerId, CanIf_ControllerModeType ControllerMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    /* \trace SPEC-5302 */
    errorId = CANIF_E_PARAM_CONTROLLER;
  }
  /* #30 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
#endif
    {
#if (CANIF_DEV_ERROR_DETECT == STD_OFF)
    /* \trace SPEC-5305 */
    /* #100 Process only if CAN channel is initialized */
    if (CANIF_CS_UNINIT != CanIf_GetCtrlMode(CanIf_Controller_Value))
#endif
    {
      /* pointer to callback function */
      CanIf_CtrlModeIndicationFctType cbkFct;

      /* outer "switch" -> indication mode changed (call parameter of the function */
      /* inner "switch" -> actual mode */
      switch(ControllerMode)
      {
        case CANIF_CS_STOPPED:
          /* #200 Transition to STOP confirmed */
          switch(CanIf_GetCtrlMode(CanIf_Controller_Value))
          {
            case CANIF_CS_STARTED:
            case CANIF_CS_SLEEP:
              /* \trace SPEC-5347, SPEC-5340 */
              /* #210 Set the internal mode to STOP if currently in START or SLEEP mode */
              CanIf_SetCtrlMode(CanIf_Controller_Value, CANIF_CS_STOPPED); /* SBSW_CANIF_3 */
#if (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON)
              /* \trace SPEC-9980 */
              /* TxConfirmationState is reset always when CAN controller is stopped
              * - BusOff
              * - Going to _SLEEP
              * - CanIf_InitController() is called */
              /* #220 Reset the Tx-confirmation state */
              CanIf_SetTxConfState(CanIf_Controller_Value, CANIF_NO_NOTIFICATION); /* SBSW_CANIF_3 */
#endif
              break;
            case CANIF_CS_STOPPED:
              /* #230 Do nothing if currently in STOP mode */
              /* Change to STOP confirmed */
              /* CANIF713 nothing to do */
              break;
            default: /* COV_CANIF_GENDATA_FAILURE */
              /* not defined in ASR4-specification */
              break;
          }
          break;
        case CANIF_CS_STARTED:
          /* #300 Transition to START confirmed */
          switch(CanIf_GetCtrlMode(CanIf_Controller_Value))
          {
            case CANIF_CS_STOPPED:
              /* \trace SPEC-5351 */
              /* #310 Set the internal mode to START if currently in STOP mode */
              CanIf_SetCtrlMode(CanIf_Controller_Value, CANIF_CS_STARTED);  /* SBSW_CANIF_3 */
              break;
            case CANIF_CS_STARTED:
              /* \trace SPEC-5341 */
              /* #320 If currently in START nothing to do */
              break;
            case CANIF_CS_SLEEP:
              /* \trace SPEC-5340 */
              /* #330 If currently in SLEEP then transition is not allowed. Do nothing. */
              break;
            default: /* COV_CANIF_GENDATA_FAILURE */
              /* not defined in ASR4-specification */
              break;
          }
          break;
        case CANIF_CS_SLEEP:
          /* #400 Transition to SLEEP confirmed */
          switch(CanIf_GetCtrlMode(CanIf_Controller_Value))
          {
            case CANIF_CS_STOPPED:
            case CANIF_CS_SLEEP:
              /* \trace SPEC-5348, SPEC-5344 */
              /* #410 Set the internal mode to SLEEP if currently in STOP / SLEEP mode */
              CanIf_SetCtrlMode(CanIf_Controller_Value, CANIF_CS_SLEEP);  /* SBSW_CANIF_3 */
              break;
            case CANIF_CS_STARTED:
              /* #420 If currently in START mode then transition is not allowed. Do nothing. */
              break;
            default: /* COV_CANIF_GENDATA_FAILURE */
              /* not defined in ASR4-specification  */
              break;
          }
          break;
        default:
          /* not defined in ASR4-specification  */
          break;
      }
      /* \trace SPEC-5331 */
      /* #500 Inform the upper layer about the mode transition */
      cbkFct = CANIF_CFG_CTRLMODEINDICATIONFCT();

      /* check if the callback function is available  */
      if (cbkFct != NULL_PTR)
      {
        /* call the callback function */
        cbkFct(CanIf_Controller_Value, ControllerMode);  /* SBSW_CANIF_13 */
      }
    } /* (CANIF_CS_UNINIT == CanIf_GetCtrlMode(Controller)) */
  }

  /* ----- Development Error Report ------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_CONTROLLERMODEINDICATION_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif  
#endif
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */


/* \trace SPEC-9975, SPEC-9978, CANIF738 */
#if (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  CanIf_GetTxConfirmationState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_GetTxConfirmationState(uint8 ControllerId)
{
  /* ----- Local Variables ---------------------------------------------- */
  CanIf_NotifStatusType retval = CANIF_NO_NOTIFICATION; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
#  if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_OFF) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  /* #20 Check if parameter ControllerId is valid */
  if (CanIf_Controller_Value >= CANIF_CFG_MAX_CONTROLLER)
  {
    /* \trace SPEC-9977 */
    errorId = CANIF_E_PARAM_CONTROLLER;
  }
  else
#  endif
  /* #30 Check if CAN channel is initialized */
  if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    /* CANIF735 */
    errorId = CANIF_E_UNINIT;
  }
  else
# endif /* (CANIF_DEV_ERROR_DETECT == STD_ON) */
  {
    
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Get the Tx confirmation state */
    retval = CanIf_GetTxConfState(CanIf_Controller_Value);
  }

  /* ----- Development Error Report ------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_GETTXCONFIRMATIONSTATE_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

# if (CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
}
#endif /* (CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT == STD_ON) */


/* CANIF 784 */  /* CANIF 780 */
#if (CANIF_CHANGE_BAUDRATE_SUPPORT == STD_ON)
/* CANIF775 */
/**********************************************************************************************************************
 *  CanIf_CheckBaudrate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckBaudrate(uint8 ControllerId, CONST(uint16, CANIF_CONST) Baudrate)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    /* CANIF778 */
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    errorId = CANIF_E_UNINIT;
  }
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#   if (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CanIf_Controller_Value))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#   endif
#  endif
  else
# endif
  {
    /* CANIF 786 */
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Pass the request to the CAN driver */
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
    CanIf_Can_CheckBaudrateFctType canCheckBaudrateFct;
    canCheckBaudrateFct = CanIf_GetCan_CheckBaudrateFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CanIf_Controller_Value));
    if (canCheckBaudrateFct != NULL_PTR)
    {
      retval = canCheckBaudrateFct(CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), Baudrate); /* SBSW_CANIF_41 */
    }
# else  
    retval = Can_CheckBaudrate(CanIf_Controller_Value, Baudrate);
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_BAUDRATECHECK_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
 
  return retval;  
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/* CANIF776 */
/**********************************************************************************************************************
 *  CanIf_ChangeBaudrate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ChangeBaudrate(uint8 ControllerId, CONST(uint16, CANIF_CONST) Baudrate)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    /* CANIF782 */
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    errorId = CANIF_E_UNINIT;
  }
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#   if (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CanIf_Controller_Value))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#   endif
#  endif
  else
# endif
  {
    /* \trace SPEC-21349 */
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Pass the request to the CAN driver */
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
    CanIf_Can_ChangeBaudrateFctType canChangeBaudrateFct;
    canChangeBaudrateFct = CanIf_GetCan_ChangeBaudrateFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CanIf_Controller_Value));
    if (canChangeBaudrateFct != NULL_PTR)
    {
      retval = canChangeBaudrateFct(CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), Baudrate); /* SBSW_CANIF_41 */
    }
# else
    retval = Can_ChangeBaudrate(CanIf_Controller_Value, Baudrate);
# endif  
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_BAUDRATECHANGE_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  
  return retval;  
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* CANIF_CHANGE_BAUDRATE_SUPPORT == STD_ON */


#if (CANIF_SET_BAUDRATE_API == STD_ON)
/* CANIF867 */
/**********************************************************************************************************************
 *  CanIf_SetBaudrate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetBaudrate(uint8 ControllerId, uint16 BaudRateConfigID)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    /* SWS_CANIF_869 */
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    errorId = CANIF_E_UNINIT;
  }
#  if ((CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON) && (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CanIf_Controller_Value))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#  endif
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* SWS_CANIF_00868 */
    /* #100 Pass the request to the CAN driver */
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
    CanIf_Can_SetBaudrateFctType canSetBaudrateFct;
    canSetBaudrateFct = CanIf_GetCan_SetBaudrateFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CanIf_Controller_Value));
    if (canSetBaudrateFct != NULL_PTR)
    {
      retval = canSetBaudrateFct(CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), BaudRateConfigID); /* SBSW_CANIF_41 */
    }
# else
    retval = Can_SetBaudrate(CanIf_Controller_Value, BaudRateConfigID);
# endif    
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_BAUDRATESET_API, errorId);
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;  
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif


#if (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) /* COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR */
# if (CANIF_EXTENDEDID_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  CanIf_SetAddressTableEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, CANIF_CODE) CanIf_SetAddressTableEntry(uint8 ControllerId, uint8 intAddr, uint8 busAddr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
  uint8 oldBusAddr;
  
/* ----- Development Error Report --------------------------------------- */
#  if (CANIF_DEV_ERROR_DETECT == STD_ON)
#   if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
#   endif
  /* #20 Check if parameter ControllerId is valid */
  if (CANIF_CFG_CTRLJ1939DYNADDRSUPPORT(CanIf_Controller_Value) == CANIF_J1939_DYN_ADDR_DISABLED)
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  else
#  endif  
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Adapt the dynamic address lookup table (critical section is used) */
    CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_6);

    oldBusAddr = CANIF_VAR_J1939TXADDR_LOOKUP(CanIf_Controller_Value, intAddr);
    if (oldBusAddr != CANIF_J1939_NULL_ADDR)
    {
      CANIF_VAR_SET_J1939RXADDR_LOOKUP(CanIf_Controller_Value, oldBusAddr, CANIF_J1939_NULL_ADDR); /* SBSW_CANIF_17 */
    }
    CANIF_VAR_SET_J1939RXADDR_LOOKUP(CanIf_Controller_Value, busAddr, intAddr); /* SBSW_CANIF_17 */
    CANIF_VAR_SET_J1939TXADDR_LOOKUP(CanIf_Controller_Value, intAddr, busAddr); /* SBSW_CANIF_17 */

    CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_6);
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_SETADDRESSTABLEENTRY_API, errorId);
  }
#  else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}


/**********************************************************************************************************************
 *  CanIf_ResetAddressTableEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, CANIF_CODE) CanIf_ResetAddressTableEntry(uint8 ControllerId, uint8 intAddr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#  if (CANIF_DEV_ERROR_DETECT == STD_ON)
#   if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
#   endif
  /* #20 Check if parameter ControllerId is valid */
  if (CANIF_CFG_CTRLJ1939DYNADDRSUPPORT(CanIf_Controller_Value) == CANIF_J1939_DYN_ADDR_DISABLED)
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8 busAddr;

    /* #100 Reset the dynamic address lookup table (critical section is used) */
    CanIf_EnterCritical(CANIF_EXCLUSIVE_AREA_6);

    busAddr = CANIF_VAR_J1939TXADDR_LOOKUP(CanIf_Controller_Value, intAddr);
    
    CANIF_VAR_SET_J1939RXADDR_LOOKUP(CanIf_Controller_Value, busAddr, CANIF_J1939_NULL_ADDR); /* SBSW_CANIF_17 */
    CANIF_VAR_SET_J1939TXADDR_LOOKUP(CanIf_Controller_Value, intAddr, CANIF_J1939_NULL_ADDR); /* SBSW_CANIF_17 */

    CanIf_LeaveCritical(CANIF_EXCLUSIVE_AREA_6);
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_RESETADDRESSTABLEENTRY_API, errorId);
  }
#  else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
# endif /* (CANIF_EXTENDEDID_SUPPORT == STD_ON) */
#endif  /* (CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED) */


#if (CANIF_EXTENDED_RAM_CHECK_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  CanIf_RamCheckCorruptMailbox()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, CANIF_CODE) CanIf_RamCheckCorruptMailbox(uint8 ControllerId, CanIf_HwHandleType HwHandle) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR; 
  CanIf_RamCheckCorruptMailboxIndFctType ramCheckCorruptMailboxIndFct = CANIF_CFG_RAMCHECKCORRUPTMAILBOXINDFCT();

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Verify if function pointer is valid */
  if (ramCheckCorruptMailboxIndFct != NULL_PTR)
  {
    /* #20 Call application notification function */ 
    ramCheckCorruptMailboxIndFct(ControllerId, HwHandle); /* SBSW_CANIF_13 */
  }
  else
  {
    errorId = CANIF_E_CONFIG;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */
  {
    CanIf_Det_ReportError(CANIF_RAMCHECKCORRUPTMAILBOX_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif     
}
  

/**********************************************************************************************************************
 *  CanIf_RamCheckCorruptController()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */  
FUNC(void, CANIF_CODE) CanIf_RamCheckCorruptController(uint8 ControllerId) /* COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR; 
  CanIf_RamCheckCorruptControllerIndFctType ramCheckCorruptControllerIndFct = CANIF_CFG_RAMCHECKCORRUPTCONTROLLERINDFCT();

  /* ----- Implementation ----------------------------------------------- */
  
  /* #10 Verify if function pointer is valid */
  if (ramCheckCorruptControllerIndFct != NULL_PTR)
  {
    /* #20 Call application notification function */ 
    ramCheckCorruptControllerIndFct(ControllerId); /* SBSW_CANIF_13 */
  }
  else
  {
    errorId = CANIF_E_CONFIG;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */
  {
    CanIf_Det_ReportError(CANIF_RAMCHECKCORRUPTCONTROLLER_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}


/**********************************************************************************************************************
 *  CanIf_RamCheckExecute()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */  
FUNC(void, CANIF_CODE) CanIf_RamCheckExecute(uint8 ControllerId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
  CanIf_Can_RamCheckExecuteFctType can_RamCheckExecuteFct;
# endif
    
  /* ----- Development Error Checks --------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    errorId = CANIF_E_UNINIT;
  }
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#   if (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CanIf_Controller_Value))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#   endif
#  endif
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Call CAN driver to execute extended RAM check */
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
    can_RamCheckExecuteFct = CanIf_GetCan_RamCheckExecuteFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CanIf_Controller_Value));
  
    if(can_RamCheckExecuteFct != NULL_PTR)
    {
      can_RamCheckExecuteFct(CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value)); /* SBSW_CANIF_41 */
    }
    else
    {
      errorId = CANIF_E_CONFIG; 
    }
# else
    Can_RamCheckExecute(CanIf_Controller_Value);
# endif
  }
  
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */
  {
    CanIf_Det_ReportError(CANIF_RAMCHECKEXECUTE_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  CanIf_RamCheckEnableMailbox()
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */  
FUNC(void, CANIF_CODE) CanIf_RamCheckEnableMailbox(uint8 ControllerId, CanIf_HwHandleType HwHandle)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
  CanIf_Can_RamCheckEnableMailboxFctType can_RamCheckEnableMailboxFct;
# endif

  /* ----- Development Error Checks --------------------------------------- */  
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    errorId = CANIF_E_UNINIT;
  }
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#   if (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CanIf_Controller_Value))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#   endif
#  endif
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Call CAN driver to enable the referred mailbox */
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
    can_RamCheckEnableMailboxFct = CanIf_GetCan_RamCheckEnableMailboxFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CanIf_Controller_Value));
  
    if (can_RamCheckEnableMailboxFct != NULL_PTR)
    {
      can_RamCheckEnableMailboxFct((Can_HwHandleType)HwHandle);  /* SBSW_CANIF_13 */
    }
    else
    {
      errorId = CANIF_E_CONFIG;
    }
# else
    Can_RamCheckEnableMailbox(HwHandle);
# endif
  }
    
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */
  {
    CanIf_Det_ReportError(CANIF_RAMCHECKENABLEMAILBOX_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  CanIf_RamCheckEnableController()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */  
FUNC(void, CANIF_CODE) CanIf_RamCheckEnableController(uint8 ControllerId)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
  CanIf_Can_RamCheckEnableControllerFctType can_RamCheckEnableControllerFct;
# endif
  
  /* ----- Development Error Checks --------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if CAN channel is initialized */
  else if (CanIf_GetCtrlMode(CanIf_Controller_Value) == CANIF_CS_UNINIT)
  {
    errorId = CANIF_E_UNINIT;
  }
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#   if(CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CanIf_Controller_Value))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#   endif
#  endif
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Call CAN driver to enable the referred controller */
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
    can_RamCheckEnableControllerFct = CanIf_GetCan_RamCheckEnableControllerFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CanIf_Controller_Value));
  
    if (can_RamCheckEnableControllerFct != NULL_PTR)
    {
      can_RamCheckEnableControllerFct(CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value)); /* SBSW_CANIF_41 */
    }
    else
    {
      errorId = CANIF_E_CONFIG;
    }
# else
    Can_RamCheckEnableController(CanIf_Controller_Value);
# endif
  }
    
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */
  {
    CanIf_Det_ReportError(CANIF_RAMCHECKENABLECONTROLLER_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif   
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif  /* (CANIF_EXTENDED_RAM_CHECK_SUPPORT == STD_ON) */


#if (CANIF_SET_PDU_RECEPTION_MODE_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  CanIf_SetPduReceptionMode()
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
 */  
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPduReceptionMode(PduIdType id, CanIf_ReceptionModeType mode) 
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval  = E_NOT_OK;
  uint8 errorId = CANIF_E_NO_ERROR;
  CanIf_AnyIdxType CanIfRxPduId;

  /* ----- Development Error Checks ------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    /* \trace SPEC-5238 */
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
# endif
# if ((CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME) || (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))
#  if (CANIF_DEV_ERROR_DETECT == STD_ON)   
  /* #20 Check if parameter id is valid */
  if (id >= CANIF_CFG_MAX_ULRXPDUS)
  {
    /* \trace SPEC-2007 */
    errorId = CANIF_E_INVALID_RXPDUID;
  }
  else
#  endif      
# endif
  {
# if ((CANIF_CONFIG_VARIANT == CANIF_CFGVAR_POSTBUILDTIME) || (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON))
    /* for PB and LT configurations the RxPduId order between CanIf and higher layers may differ and needs to be indirected */
    CanIfRxPduId = CANIF_CFG_EXTRXPDUID2INTRXPDUID(id);
# else
    CanIfRxPduId = id;
# endif
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
    /* #30 Check if parameter CanIfRxPduId is valid */
    if (CanIfRxPduId >= CANIF_CFG_MAX_RXPDUS)
    {
      /* \trace SPEC-2007 */
      errorId = CANIF_E_INVALID_RXPDUID;
    }
    /* #40 Check if parameter mode is valid */
    else if ((mode != CANIF_RMT_RECEIVE_STOP) && (mode != CANIF_RMT_IGNORE_CONTINUE))
    {
      errorId = CANIF_E_INVALID_PDURECEPTIONMODE; /* PRQA S 2880 */ /* MD_MSR_Unreachable */
    }
    else
# endif
    {
      
      /* ----- Implementation ----------------------------------------------- */

      /* #100 Is for this CanIfRxPduId the reception mode adjustable? */
      if (CANIF_CFG_RX_ISRECEPTIONMODEPDU(CanIfRxPduId))
      {
        /* #110 Set the reception mode */
        CANIF_VAR_SET_PDU_RECEPTION_MODE(CANIF_CFG_RX_PDURECEPTIONMODEIDX(CanIfRxPduId), mode); /* SBSW_CANIF_42 */
        retval = E_OK;
      }
# if (CANIF_DEV_ERROR_DETECT == STD_ON)        
      else
      {
        errorId = CANIF_E_INVALID_RXPDUID;
      }
# endif
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */
  {
    CanIf_Det_ReportError(CANIF_SETPDURECEPTIONMODE_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif  /* (CANIF_SET_PDU_RECEPTION_MODE_SUPPORT == STD_ON) */


# if (CANIF_BUS_MIRRORING_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  CanIf_GetControllerErrorState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */  
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerErrorState(uint8 ControllerId, P2VAR(Can_ErrorStateType, AUTOMATIC, CANIF_APPL_STATE_VAR) ErrorStatePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
  CanIf_Can_GetControllerErrorStateFctType can_GetControllerErrorStateFct;
# endif

  /* ----- Development Error Checks --------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if parameter ErrorStatePtr is valid */
  else if(ErrorStatePtr == NULL_PTR)
  {
    errorId = CANIF_E_PARAM_POINTER;
  }
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#   if(CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CanIf_Controller_Value))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#   endif
#  endif
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Request the error state of the CAN controller */
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
    can_GetControllerErrorStateFct = CanIf_GetCan_GetControllerErrorStateFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CanIf_Controller_Value));
  
    if (can_GetControllerErrorStateFct != NULL_PTR)
    {
      retval = can_GetControllerErrorStateFct(CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), ErrorStatePtr); /* SBSW_CANIF_45 */
    }
    else
    {
      errorId = CANIF_E_CONFIG;
    }
# else
    retval = Can_GetControllerErrorState(CanIf_Controller_Value, ErrorStatePtr); /* SBSW_CANIF_5 */
# endif
  }
    
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */
  {
    CanIf_Det_ReportError(CANIF_GETCONTROLLERERRORSTATE_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif   
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  CanIf_GetControllerRxErrorCounter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */  
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerRxErrorCounter(uint8 ControllerId, P2VAR(uint8, AUTOMATIC, CANIF_APPL_STATE_VAR) RxErrorCounterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
  CanIf_Can_GetControllerRxErrorCounterFctType can_GetControllerRxErrorCounterFct;
# endif

  /* ----- Development Error Checks --------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if parameter RxErrorCounterPtr is valid */
  else if(RxErrorCounterPtr == NULL_PTR)
  {
    errorId = CANIF_E_PARAM_POINTER;
  }
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#   if(CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CanIf_Controller_Value))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#   endif
#  endif
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Request the Rx error counter of the CAN controller */
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
    can_GetControllerRxErrorCounterFct = CanIf_GetCan_GetControllerRxErrorCounterFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CanIf_Controller_Value));
  
    if (can_GetControllerRxErrorCounterFct != NULL_PTR)
    {
      retval = can_GetControllerRxErrorCounterFct(CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), RxErrorCounterPtr); /* SBSW_CANIF_45 */
    }
    else
    {
      errorId = CANIF_E_CONFIG;
    }
# else
    retval = Can_GetControllerRxErrorCounter(CanIf_Controller_Value, RxErrorCounterPtr); /* SBSW_CANIF_5 */
# endif
  }
    
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */
  {
    CanIf_Det_ReportError(CANIF_GETCONTROLLERRXERRORCOUNTER_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif   
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  CanIf_GetControllerTxErrorCounter()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */  
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerTxErrorCounter(uint8 ControllerId, P2VAR(uint8, AUTOMATIC, CANIF_APPL_STATE_VAR) TxErrorCounterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
  CanIf_Can_GetControllerTxErrorCounterFctType can_GetControllerTxErrorCounterFct;
# endif

  /* ----- Development Error Checks --------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  /* #30 Check if parameter TxErrorCounterPtr is valid */
  else if(TxErrorCounterPtr == NULL_PTR)
  {
    errorId = CANIF_E_PARAM_POINTER;
  }
#  if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#   if(CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
  /* #40 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CanIf_Controller_Value))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#   endif
#  endif
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Request the Tx error counter of the CAN controller */
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
    can_GetControllerTxErrorCounterFct = CanIf_GetCan_GetControllerTxErrorCounterFctMap(CANIF_CFG_CTRLUPTOLOWMAP_DRIVERINDEX(CanIf_Controller_Value));
  
    if (can_GetControllerTxErrorCounterFct != NULL_PTR)
    {
      retval = can_GetControllerTxErrorCounterFct(CANIF_CFG_CTRLUPTOLOWMAP_CHANNELINDEX(CanIf_Controller_Value), TxErrorCounterPtr); /* SBSW_CANIF_45 */
    }
    else
    {
      errorId = CANIF_E_CONFIG;
    }
# else
    retval = Can_GetControllerTxErrorCounter(CanIf_Controller_Value, TxErrorCounterPtr); /* SBSW_CANIF_5 */
# endif
  }
    
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */
  {
    CanIf_Det_ReportError(CANIF_GETCONTROLLERTXERRORCOUNTER_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif   
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  CanIf_EnableBusMirroring()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */  
FUNC(Std_ReturnType, CANIF_CODE) CanIf_EnableBusMirroring(uint8 ControllerId, boolean MirroringActive)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval  = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks --------------------------------------- */
# if (CANIF_DEV_ERROR_DETECT == STD_ON)
#  if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
#  endif
  /* #20 Check if parameter ControllerId is valid */
  if (ControllerId >= CANIF_CFG_MAX_CONTROLLER)
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Change mirroring of the CAN controller */
    CanIf_ChangeMirroring(CanIf_Controller_Value, MirroringActive); /* SBSW_CANIF_3 */
    retval = E_OK;
  }
 
  /* ----- Development Error Report --------------------------------------- */
# if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR) /* PRQA S 2992, 2996 */ /* MD_CanIf_Rule14.3_ErrorId */
  {
    CanIf_Det_ReportError(CANIF_ENABLEBUSMIRRORING_API, errorId); /* PRQA S 2880 */ /* MD_MSR_Unreachable */
  }
# else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if ((CANIF_ONE_CONTROLLER_OPTIMIZATION == STD_ON) && (CANIF_DEV_ERROR_DETECT == STD_OFF)) /* COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED */
  CANIF_DUMMY_STATEMENT(ControllerId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif   
  return retval;
}


/**********************************************************************************************************************
 *  Appl_GenericConfirmation()
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
 */  
FUNC(Can_ReturnType, CANIF_CODE) Appl_GenericConfirmation(uint8 Controller, Can_PduInfoPtrType DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (CANIF_DEV_ERROR_DETECT == STD_ON)
# if (CANIF_USE_INIT_POINTER == STD_ON)
  /* #10 Check if CanIf is initialized at all */
  if (CanIf_SystemInit == FALSE)
  {
    errorId = CANIF_E_UNINIT;
  }
  else
# endif
  /* #20 Check if parameter DataPtr is valid */
  if(DataPtr == NULL_PTR)
  {
    errorId = CANIF_E_PARAM_POINTER;
  }
  /* #30 Check if canTxPduId (=DataPtr->swPduHandle) is valid */
  else if (DataPtr->swPduHandle >=  CANIF_CFG_MAX_TXPDUS)
  {
    errorId = CANIF_E_PARAM_LPDU;
  }
  /* #40 Check if corresponding CAN controller is initialized */
  else if (CanIf_GetCtrlMode(CANIF_CFG_TX_CONTROLLER(DataPtr->swPduHandle)) == CANIF_CS_UNINIT )
  {
    errorId = CANIF_E_UNINIT;
  }
# if (CANIF_MULTIPLE_CANDRV_SUPPORT == STD_ON)
#  if (CANIF_POSTBUILD_VARIANT_SUPPORT == STD_ON) 
  /* #50 Check if corresponding CanDrv is available in current identity */
  else if (!CANIF_CFG_IS_CANDRVINDEXVALID(CANIF_CFG_TX_CONTROLLER(DataPtr->swPduHandle)))
  {
    errorId = CANIF_E_PARAM_CONTROLLERID;
  }
#  endif  
# endif
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */

    /* #100 Process only if CAN controller is active */
    if (CanIf_GetCtrlMode(CANIF_CFG_TX_CONTROLLER(DataPtr->swPduHandle)) == CANIF_CS_STARTED)
    {
      if ( (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(DataPtr->swPduHandle)) == CANIF_GET_ONLINE) ||
             (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(DataPtr->swPduHandle)) == CANIF_GET_TX_ONLINE)
# if (CANIF_PN_WU_TX_PDU_FILTER == STD_ON)
        || (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(DataPtr->swPduHandle)) == CANIF_GET_ONLINE_WAKF)
        || (CanIf_GetChannelMode(CANIF_CFG_TX_CONTROLLER(DataPtr->swPduHandle)) == CANIF_GET_TX_ONLINE_WAKF)
# endif
         )
      {
        /* #200 Report CAN frame to mirror module, if mirroring is enabled for the CAN controller */
        if(CanIf_IsMirroringEnabled(CANIF_CFG_TX_CONTROLLER(DataPtr->swPduHandle)))
        {
          Mirror_ReportCanFrame(CANIF_CFG_TX_CONTROLLER(DataPtr->swPduHandle), DataPtr->id, DataPtr->length, DataPtr->sdu); /* SBSW_CANIF_5 */
        }
      }
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (CANIF_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANIF_E_NO_ERROR)
  {
    CanIf_Det_ReportError(CANIF_APPL_GENERICCONFIRMATION_API, errorId);
  }
#else
  CANIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CANIF_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return CAN_OK; /* Higher layer confirmation will be called afterwards (CanIf_TxConfirmation()) by the CAN driver */
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* CANIF_BUS_MIRRORING_SUPPORT == STD_ON */


#define CANIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  MISRA JUSTIFICATIONS
 *********************************************************************************************************************/
 
/* Justification for module-specific MISRA deviations:

MD_CanIf_Rule8.9:
  Reason: Definition of CanIfState in global section because of better over-view.
  Risk: Name conflict.
  Prevention: Compiler optimize and check for name conflicts.

MD_CanIf_Rule9.1:
  Reason: The variable is set depending on the configuration, so a default value of the variable is not possible.
  Risk: Undefined value of the variable.
  Prevention: Code inspection and test of the different configurations in the component test.  

MD_CanIf_Rule10.5_4342:
  Reason: The different mode types are abstracted with the enum CanIf_PduGetModeType/ CanIf_PduSetModeType.
          But a lookup table CanIfState from a basic unsigned data type is used to get a requested mode.
          This leads to a runtime efficient code.
  Risk: Inconsistency between mode types in CanIf_PduGetModeType/ CanIf_PduSetModeType enum and CanIfState lookup table.
  Prevention: Code inspection and test of the different configurations in the component test. 

MD_CanIf_Rule11.1:
  Reason: Cast to different pointer type required to avoid compiler warning due to usage of a union of function pointer types.
  Risk: None due to fact that function pointer are used.
  Prevention: Test of the different variants in the component test.

MD_CanIf_Rule11.8:
  Reason: Pointer cast to P2VAR is necessary to avoid compiler warning because "SduDataPtr" within "PduInfoType" is defined
          as P2VAR while "CanSduPtr" is P2CONST.
  Risk: CAN data could be modified after cast to P2VAR.
  Prevention: Code inspection and test of the different variants in the component test.

MD_CanIf_Rule14.3_ErrorId:
  Reason: Usage of defined API pattern.
  Risk: Statements in this 'if' block are not executed.
  Prevention: Code inspection and test of the different configurations in the component test.

MD_CanIf_Rule14.3_GenData:
  Reason: Configuration related constant data.
  Risk: Statements in the 'if' or 'else' block are not executed.
  Prevention: Code inspection and test of the different configurations in the component test.

MD_CanIf_Rule14.3_RxPDU:
  Reason: Configuration related Rx-PDU constant data. 
  Risk: Statements in the 'if' or 'else' block are not executed.
  Prevention: Code inspection and test of the different configurations in the component test.

MD_CanIf_Rule15.4:
  Reason: More than one break statement is used to terminate the loop during the search algorithm.
          This leads to more efficient code which is easier to read and maintain.
  Risk: Relevant fragments of code not executed.
  Prevention: Code inspection.

MD_CanIf_Rule17.8:
  Reason: The direct modification of the function parameter leads to more efficient code which is easier to read and maintain.
  Risk: Incorrect expectation of the value of the modified function parameter.    
  Prevention: Code inspection and test of the different configurations in the component test.

MD_CanIf_Dir4.1_2842:
  Reason: Possible out of bounds read access.
  Risk: Wrong data access.
  Prevention: Test of the different configurations in the component test.

*/

/**********************************************************************************************************************
 *  SBSW JUSTIFICATIONS
 *********************************************************************************************************************/

/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_CANIF_1
\DESCRIPTION Access to txPduDataWithChecksumPtr with index which is based on DLC
\COUNTERMEASURE \N Index is checked during runtime not to exceed the bounds of txPduDataWithChecksumPtr. Performed check: (PduInfoPtr->SduLength) > CANIF_CFG_MAXTXDLC_PLUS_DATACHECKSUM.

\ID SBSW_CANIF_2
\DESCRIPTION Function call via function pointer. Function is read out of CanIf_DataChecksumRxErrFctPtr
\COUNTERMEASURE \S For the generated function declared by CanIf_DataChecksumRxErrFctPtr, it must be secured that a valid function callout is provided with valid signature. 
                   Please see SMI-746 within the Safety Manual of the CAN interface.
                   The Callout function is optional, if no Callout is parametrized CanIf_DataChecksumRxErrFctPtr is defined as NULL_PTR, nothing to do.

\ID SBSW_CANIF_3
\DESCRIPTION Access to CanIf_CtrlMode, CanIf_ChannelMode, CanIf_WakeUpValidationState, CanIf_PnWuTxPduFilterActive, CanIf_TxConfState, 
             CanIf_BusMirroringActive with index controlled by CANIF_CFG_MAX_CONTROLLER which is mapped to the CanIf_GetSizeOfCtrlStates()
             which is provided by ComStackLib
\COUNTERMEASURE \N Qualified use-case CSL01/CSL03 of ComStackLib

\ID SBSW_CANIF_4
\DESCRIPTION Write access to dereferenced pointer ControllerModePtr
\COUNTERMEASURE \N The caller of the function CanIf_GetControllerMode must ensure that the pointer passed to the
                   parameter ControllerModePtr is able to record a value of the type CanIf_ControllerModeType

\ID SBSW_CANIF_5
\DESCRIPTION Function call with referenced local variable/structure respectively passed-through parameter. 
\COUNTERMEASURE \N Pointer references stack variable and is therefor always valid. For passed-through datapointer the caller ensures that the 
                   pointer is valid.

\ID SBSW_CANIF_6   
\DESCRIPTION Access to CanIf_TxQueue via PduId which is  indirected over CanIf_TxPduQueueIndex.
\COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib. Pdu is passed through, caller ensures that PduId is valid.
                   For API CanIf_CancelTxConfirmation() which is called from outside, the PduId is checked via CSL01 with reference value "CanIf_GetSizeOfTxPduConfig()".

\ID SBSW_CANIF_7
\DESCRIPTION VStdMemCpy function call with parameter destination buffer pointer and length. 
\COUNTERMEASURE \N  CanIf_TransmitSubHandleTxResBusy(): runtime check -> localPduPtr->length vs. CANIF_STATIC_BUFFER_SIZE 
                    CanIf_HlIndication(): runtime check -> (CanDlc + CANIF_CFG_RX_RXMETADATALENGTH(PduId)) vs. CANIF_CFG_MAXRXDLC_PLUS_MAXMETADATA
                    CanIf_CancelTxConfirmation():  runtime check -> PduInfoPtr->length vs. CANIF_STATIC_BUFFER_SIZE
                    The array for buffering the data is dimensioned with CANIF_STATIC_BUFFER_SIZE or CANIF_CFG_MAXRXDLC_PLUS_MAXMETADATA respectively.

\ID SBSW_CANIF_8
\DESCRIPTION Access to CanIf_PnWuTxPduFilterActive, CanIf_TxConfState with index controller which is indirected from  Hrh/CanTxPduId via 
                    CanIf_GetCtrlStatesIdxOfMailBoxConfig()/CanIf_GetCtrlStatesIdxOfTxPduConfig(). Hrh is checked via CanIf_GetSizeOfMailBoxConfig(),
                    CanTxPduId is checked via CanIf_GetSizeOfTxPduConfig().
\COUNTERMEASURE \N Qualified use-case CSL01/CSL03 of ComStackLib                    
                    
\ID SBSW_CANIF_9
\DESCRIPTION Write access to the content of an object that is referenced by a pointer parameter.
\COUNTERMEASURE \N Caller ensures validity of pointer parameter.

\ID SBSW_CANIF_10
\DESCRIPTION Function call CanIf_Indirect_HlIndication(). CanSduPtr is just forwarded without modification.
\COUNTERMEASURE \N Caller of CanIf_RxIndication ensures that CanSduPtr is valid.

\ID SBSW_CANIF_11
\DESCRIPTION Function call via function pointer. Function is indirected with CanTxPduId over CanIf_TxPduConfig and CanIf_TxConfirmationFctList 
\COUNTERMEASURE \S For the generated function list CanIf_TxConfirmationFctList, it must be secured that a valid function callback is provided with valid signature
                The assurance to get a valid function pointer is a qualified use-case CSL03 of ComStackLib

\ID SBSW_CANIF_12
\DESCRIPTION Function call via function pointer. Function is indirected with CanRxPduId over CanIf_RxPduConfig and CanIf_RxIndicationFctList. Data pointer 
             CanSduPtr is defined as pointer to const, so no write access is possible.
\COUNTERMEASURE \S For the generated function list CanIf_RxIndicationFctList, it must be secured that a valid function callback is provided with the vailid signature.
                   The assurance to get a valid function pointer is a qualified use-case CSL03 of ComStackLib

\ID SBSW_CANIF_13
\DESCRIPTION Function call via function pointer
\COUNTERMEASURE \S  For the generated functions CanIf_BusOffNotificationFctPtr, CanIf_CtrlModeIndicationFctPtr, CanIf_TrcvModeIndicationFctPtr, CanIf_ConfirmPnAvailabilityFctPtr,
                    CanIf_ClearTrcvWufFlagIndicationFctPtr, CanIf_CheckTrcvWakeFlagIndicationFctPtr, CanIf_WakeUpValidationFctPtr, CanIf_RamCheckCorruptControllerIndFctPtr,
                    CanIf_RamCheckCorruptMailboxIndFctPtr it must be secured that a valid function callback is provided with the valid signature.

\ID SBSW_CANIF_14
\DESCRIPTION Access to CanIf_DynTxId via PDU ID which is  indirected over CanIf_TxPduStatic2DynamicIndirection
\COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_CANIF_15
\DESCRIPTION Write access to variable CanIf_TxQueueIndex2FifoEl, CanIf_TxFifoQueueBase with index counter.
\COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib.

\ID SBSW_CANIF_16
\DESCRIPTION Write access to local variable with index. 
\COUNTERMEASURE \N Index is checked during runtime to not exceed range of variable

\ID SBSW_CANIF_17
\DESCRIPTION Write access to CanIf_J1939RxAddr_Lookup/CanIf_J1939TxAddr_Lookup with indirected index
\COUNTERMEASURE \N Qualified use-case with SATURATION-strategy

\ID SBSW_CANIF_18
\DESCRIPTION VStdMemCpy function call with parameter destination buffer pointer and length. 
\COUNTERMEASURE \N  CanIf_TransmitSubHandleTxResBusy(): runtime check -> localPduPtr->length vs. CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_MAXDATALENGTH(localPduPtr->swPduHandle) 
                    CanIf_CancelTxConfirmation():  runtime check -> localPduPtr->length vs. CANIF_CFG_TXBUFFERPRIOBYCANID_STATFDQUEUE_MAXDATALENGTH(localPduPtr->swPduHandle) 
                    Qualified use-case CSL02 of ComStackLib (union of messages and RAM array). "swPduHandle" is verified to be valid by caller of function.

\ID SBSW_CANIF_19
\DESCRIPTION Write access to WakeUpValidationStateOfCtrlStates with index controller which is indirected from HRH
\COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib         

\ID SBSW_CANIF_20
\DESCRIPTION Write access to CanIf_TxQueueFlags with queueElementIdx
\COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib:  queueElementIdx is checked against CanIf_GetSizeOfTxQueueFlags() at runtime.

\ID SBSW_CANIF_21
\DESCRIPTION Function call with parameter data pointer. The data pointer is passed through the function with the same type.
\COUNTERMEASURE \N The compiler ensures that no memory violation occurs.

\ID SBSW_CANIF_22
\DESCRIPTION Function call via function pointer. Function is indirected with TransceiverId over CanIf_CanTrcvFctTbl.
\COUNTERMEASURE \N The assurance to get a valid function pointer is a qualified use-case CSL03 of ComStackLib

\ID SBSW_CANIF_23
\DESCRIPTION Write access to CanIf_PduRxMode with "index".
\COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib.

\ID SBSW_CANIF_24
\DESCRIPTION Initialization write-access to CanIf_CtrlMode with index which is limited by sizeof of corresponding type and corresponding variable. Hence NO out-of-bounce access can occur.
\COUNTERMEASURE \N Verified with review and the compiler ensures that no memory violation occurs.

\ID SBSW_CANIF_25
\DESCRIPTION Write access to CanIf_TxBufferPrioByCanIdBase.  PduId -> CanIf_GetMailBoxConfigIdxOfTxPduConfig -> CanIf_GetTxBufferCfgIdxOfMailBoxConfig ->
\                  CanIf_GetTxBufferPrioByCanIdBaseIdxOfTxBufferPrioByCanIdBitQueueConfig/CanIf_GetTxBufferPrioByCanIdBaseIdxOfTxBufferPrioByCanIdByteQueueConfig
\COUNTERMEASURE \N TxPduId is checked against CanIf_GetSizeOfTxPduConfig. The following indirections are ensured via qualified use-case CSL03 of ComStackLib.
                   
\ID SBSW_CANIF_26
\DESCRIPTION Write access to CanIf_TxQueueFlags. ControllerId -> CanIf_GetMappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfig ->
                   CanIf_GetMailBoxConfigIdxOfMappedTxBuffersConfig -> CanIf_GetTxBufferCfgIdxOfMailBoxConfig -> CanIf_GetTxQueueFlagsStartIdxOfTxBufferPrioByCanIdBitQueueConfig ->
                   CanIf_SetTxQueueFlags
\COUNTERMEASURE \N ControllerId is checked against CanIf_GetSizeOfCtrlStates. The following indirections are ensured via qualified use-case CSL03 of ComStackLib.
                   
\ID SBSW_CANIF_27
\DESCRIPTION Write access to CanIf_TxBufferPrioByCanIdBase. ControllerId -> CanIf_GetMappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfig ->
                   CanIf_GetMailBoxConfigIdxOfMappedTxBuffersConfig -> CanIf_GetTxBufferCfgIdxOfMailBoxConfig ->
                   CanIf_GetTxBufferPrioByCanIdBaseIdxOfTxBufferPrioByCanIdByteQueueConfig -> CanIf_SetTxQueueCounter
\COUNTERMEASURE \N ControllerId is checked against CanIf_GetSizeOfCtrlStates. The following indirections are ensured via qualified use-case CSL03 of ComStackLib.
                  
\ID SBSW_CANIF_28
\DESCRIPTION Write access to CanIf_TxQueue. ControllerId ->  CanIf_GetMappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfig ->
                   CanIf_GetMailBoxConfigIdxOfMappedTxBuffersConfig -> CanIf_GetTxBufferCfgIdxOfMailBoxConfig ->
                   CanIf_GetTxBufferPrioByCanIdByteQueueMappedTxPdusStartIdxOfTxBufferPrioByCanIdByteQueueConfig ->
                   CanIf_GetTxPduConfigIdxOfTxBufferPrioByCanIdByteQueueMappedTxPdus -> CanIf_GetTxQueueIdxOfTxPduQueueIndex -> CanIf_GetTxQueue
\COUNTERMEASURE \N ControllerId is checked against CanIf_GetSizeOfCtrlStates. The following indirections are ensured via qualified use-case CSL03 of ComStackLib.

\ID SBSW_CANIF_29
\DESCRIPTION Write access sdu pointer with index CANIF_J1939_ACKM_ACKADDR_POS
\COUNTERMEASURE \N The code checks at runtime the buffer length against CANIF_J1939_ACKM_ACKADDR_POS.

\ID SBSW_CANIF_30
\DESCRIPTION Write access CanSduLocal with index CANIF_J1939_ACKM_ACKADDR_POS
\COUNTERMEASURE \M Verify that: CANIF_CFG_MAXRXDLC_PLUS_MAXMETADATA > CANIF_J1939_ACKM_ACKADDR_POS

\ID SBSW_CANIF_31
\DESCRIPTION Function call with referenced pointer on local RAM array txPduDataWithChecksum.
\COUNTERMEASURE \N Runtime check: PduInfoPtr->SduLength is checked against CANIF_CFG_MAXTXDLC_PLUS_DATACHECKSUM. txPduDataWithChecksum 
                   is dimensioned with CANIF_CFG_MAXTXDLC_PLUS_DATACHECKSUM, the index to write on txPduDataWithChecksum is controlled 
                   by PduInfoPtr->SduLength.

\ID SBSW_CANIF_32
\DESCRIPTION Write access to CanIf_TxFifoQueueData with index (queueDataStartIdx + DLC) 
\COUNTERMEASURE \N  A runtime check ensures that (queueDataStartIdx + DLC) does not exceed the bounds of CanIf_TxFifoQueueData via a check against CanIf_GetSizeOfTxFifoQueueData().

\ID SBSW_CANIF_33
\DESCRIPTION Write access to CanIf_TxBufferFifoBase with index txBufferFifoBaseIdx.
             ControllerId -> CanIf_GetMappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfig -> CanIf_GetMailBoxConfigIdxOfMappedTxBuffersConfig -> CanIf_GetTxBufferCfgIdxOfMailBoxConfig ->
             CanIf_GetTxBufferFifoBaseIdxOfTxBufferFifoConfig
\COUNTERMEASURE \N ControllerId is checked against CanIf_GetSizeOfCtrlStates by caller function. The following indirections are ensured via qualified use-case CSL03 of ComStackLib.

\ID SBSW_CANIF_34
\DESCRIPTION Write access to CanIf_TxFifoQueueBase with index (readIdx/writeIdx + txFifoQueueBaseStartIdx).
             ControllerId -> CanIf_GetMappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfig -> CanIf_GetMailBoxConfigIdxOfMappedTxBuffersConfig -> CanIf_GetTxBufferCfgIdxOfMailBoxConfig ->
             CanIf_GetTxFifoQueueBaseStartIdxOfTxBufferFifoConfig -> txFifoQueueBaseStartIdx
\COUNTERMEASURE \N  ControllerId is checked against CanIf_GetSizeOfCtrlStates by caller function. The following indirections to get txFifoQueueBaseStartIdx are ensured via qualified use-case CSL03
             of ComStackLib. readIdx/writeIdx is checked against the macro CanIf_GetTxFifoQueueBaseLengthOfTxBufferFifoConfig while writing CanIf_TxBufferFifoBase.
             For (CanIf_GetTxFifoQueueBaseLengthOfTxBufferFifoConfig + CanIf_GetTxFifoQueueBaseStartIdxOfTxBufferFifoConfig) a qualified CSL03 use-case of ComStackLib ensures that the index is
             valid to access CanIf_TxFifoQueueBase.

\ID SBSW_CANIF_35
\DESCRIPTION Write access to CanIf_TxQueueIndex2FifoEl with index. CanIf_GetTxFifoQueueBase -> CanIf_GetTxQueueIdxOfTxPduQueueIndex -> CanIf_SetTxQueueIndex2FifoEl.
\COUNTERMEASURE \N  The input parameter for CanIf_GetTxFifoQueueBase() is ensured with SBSW_CANIF_34. The following indirections to get the index for CanIf_SetTxQueueIndex2FifoEl are ensured via
             qualified use-case CSL03 of ComStackLib.
             
\ID SBSW_CANIF_36
\DESCRIPTION Write access to CanIf_TxQueueIndex2FifoEl with index. CanTxPduId/PduId/localPduPtr->swPduHandle -> CanIf_GetTxQueueIdxOfTxPduQueueIndex -> CanIf_SetTxQueueIndex2FifoEl.
\COUNTERMEASURE \N The input parameter CanTxPduId/PduId/localPduPtr->swPduHandle is checked against CanIf_GetSizeOfTxPduConfig(). The following indirections to get the index for CanIf_SetTxQueueIndex2FifoEl are ensured via
             qualified use-case CSL03 of ComStackLib. 

\ID SBSW_CANIF_37
\DESCRIPTION Write access to CanIf_TxBufferFifoBase with index txBufferFifoBaseIdx. 
             CanTxPduId/PduId -> CanIf_GetMailBoxConfigIdxOfTxPduConfig -> CanIf_GetTxBufferCfgIdxOfMailBoxConfig -> CanIf_GetTxBufferFifoBaseIdxOfTxBufferFifoConfig.
\COUNTERMEASURE \N The input parameter CanTxPduId/PduId is checked by caller respectively in corresponding function against CanIf_GetSizeOfTxPduConfig(). The following indirections to get the index for CanIf_TxBufferFifoBase are ensured via
             qualified use-case CSL03 of ComStackLib.
             
\ID SBSW_CANIF_38
\DESCRIPTION Write access to CanIf_TxFifoQueueBase with index (readIdx + txFifoQueueBaseStartIdx).
             readIdx: 
             PduId -> CanIf_GetMailBoxConfigIdxOfTxPduConfig -> CanIf_GetTxBufferCfgIdxOfMailBoxConfig -> CanIf_GetTxBufferFifoBaseIdxOfTxBufferFifoConfig -> CanIf_GetTxBufferFifoBase (.eReadIdx)
             txFifoQueueBaseStartIdx: 
             PduId -> CanIf_GetMailBoxConfigIdxOfTxPduConfig -> CanIf_GetTxBufferCfgIdxOfMailBoxConfig -> CanIf_GetTxFifoQueueBaseStartIdxOfTxBufferFifoConfig
\COUNTERMEASURE \N PduId is checked against CanIf_GetSizeOfTxPduConfig. readIdx is checked against the macro CanIf_GetTxFifoQueueBaseLengthOfTxBufferFifoConfig while writing CanIf_TxBufferFifoBase.
             The index to access CanIf_TxBufferFifoBase is ensured via qualified use-case CSL03 of ComStackLib.
             The indirections to get txFifoQueueBaseStartIdx are ensured via qualified use-case CSL03 of ComStackLib.
             For (CanIf_GetTxFifoQueueBaseLengthOfTxBufferFifoConfig + CanIf_GetTxFifoQueueBaseStartIdxOfTxBufferFifoConfig) a qualified CSL03 use-case of ComStackLib ensures that the index is
             valid to access CanIf_TxFifoQueueBase.
             
\ID SBSW_CANIF_39
\DESCRIPTION Write access to CanIf_TxFifoQueueBase with index (FifoQueueBaseIdx + txFifoQueueBaseStartIdx).
             FifoQueueBaseIdx: 
             CanTxPduId -> CanIf_GetTxQueueIdxOfTxPduQueueIndex -> CanIf_GetTxQueueIndex2FifoEl
             txFifoQueueBaseStartIdx: 
             CanTxPduId -> CanIf_GetMailBoxConfigIdxOfTxPduConfig -> CanIf_GetTxBufferCfgIdxOfMailBoxConfig  -> CanIf_GetTxFifoQueueBaseStartIdxOfTxBufferFifoConfig
\COUNTERMEASURE \N CanTxPduId -> is checked against CanIf_GetSizeOfTxPduConfig. Qualified use-case CSL03 ensures that for each TxQueueIndex2FifoEl/TxFifoQueueBaseStartIdx pair calculated with the same valid
             CanTxPduId does not violate the bounds of CanIf_TxFifoQueueBase.
             
\ID SBSW_CANIF_40             
\DESCRIPTION Write access to CanIf_TxQueueData with index ( TxQueueDataStartIdxOfTxQueueIndex2DataStartStop + DLC ).
\COUNTERMEASURE \N  CanTxPduId/PduInfoPtr->swPduHandle -> checked against CanIf_GetSizeOfTxPduConfig. DLC is checked against TxQueueDataLengthOfTxQueueIndex2DataStartStop. Qualified use-case CSL03 ensures that
             ( TxQueueDataStartIdx() + TxQueueDataLength() ) do not violate the bounds of CanIf_TxQueueData.             
             
\ID SBSW_CANIF_41
\DESCRIPTION In case of feature "CANIF_MULTIPLE_CANDRV_SUPPORT" is active: \
             Function call via function pointer. Function is indirected with CanIf_Controller_Value/wuTrgtaddress over CanIf_CanDrvFctTbl. CanIf_Controller_Value/wuTrgtaddress is indirected \
             about CanIf_CanChannelIdUpToLowMap[].
\COUNTERMEASURE \N The assurance to get a valid function pointer is a qualified use-case CSL03 of ComStackLib.
             To ensure the indirection via CanIf_CanChannelIdUpToLowMap[], during CanIf_Init() there is a check that CANIF_CFG_MAX_CONTROLLER fits the dimension   \
             of CanIf_CanChannelIdUpToLowMap[]. For the index wuTrgtaddress, a runtimecheck ensures that wuTrgtaddress fits CanIf_GetSizeOfCanChannelIdUpToLowMap.

\ID SBSW_CANIF_42         
\DESCRIPTION Write access to CanIf_PduRxMode with index PduRxModeIdx.
             CanIfRxPduId -> CanIf_GetPduRxModeIdxOfRxPduConfig
\COUNTERMEASURE \N The input parameter CanIfRxPduId is checked against CanIf_GetSizeOfRxPduConfig(). The following indirection is ensured via qualified use-case CSL03 of ComStackLib.             

\ID SBSW_CANIF_43
\DESCRIPTION In case of feature "CANIF_MULTIPLE_CANDRV_SUPPORT" is active: \
             Function call via function pointer. Function is indirected with parameter CanIf_Controller_Value_Local via CanIf_GetCanDrvFctTblIdxOfCanChannelIdUpToLowMap to CanIf_CanDrvFctTbl.
             CanIf_Controller_Value_Local is indirected from CanTxPduId via CanIf_GetCtrlStatesIdxOfTxPduConfig().
             During CanIf_Init() there is a check that dimension of CanIf_CtrlStates[] fits the dimension of CanIf_CanChannelIdUpToLowMap[].
             The parameter CanTxPduId is checked against CanIf_GetSizeOfTxPduConfig(). 
\COUNTERMEASURE \N The indirections to get the function pointer are ensured by the qualified use-cases CSL01 and CSL03 of ComStackLib.

\ID SBSW_CANIF_44
\DESCRIPTION Function call via function pointer: Access to CanIf_CanTrcvFctTbl via indirection over CanIf_TransceiverUpToLowMap with TransceiverId.
             Function call with parameter data pointer: The data pointer is passed through the function with the same type.
\COUNTERMEASURE \N Function call via function pointer: The DET check of the function verifes that the TransceiverId is smaller than the size of CanIf_TransceiverUpToLowMap[],
                                                       to ensure the indirection with TransceiverId into CanIf_TransceiverUpToLowMap[].
                                                       The following indirection to get a valid function pointer is ensured via qualified use-case CSL03 of ComStackLib.
                   Function call with parameter data pointer: The caller ensures that the passed-through pointer parameter is valid.

\ID SBSW_CANIF_45  
\DESCRIPTION Function call via function pointer: Access to CanIf_CanDrvFctTbl via indirection over CanIf_CanChannelIdUpToLowMap with CanIf_Controller_Value.
             Function call with parameter data pointer: The data pointer is passed through the function with the same type.
\COUNTERMEASURE \N Function call via function pointer: CanIf_Init() makes the boundry check against CANIF_CFG_MAX_CONTROLLER for CanIf_CanChannelIdUpToLowMap[], 
                                                       to ensure the indirection with CanIf_Controller_Value into CanIf_CanChannelIdUpToLowMap[].
                                                       The following indirection to get a valid function pointer is ensured via qualified use-case CSL03 of ComStackLib.
                   Function call with parameter data pointer: The caller ensures that the passed-through pointer parameter is valid.

\ID SBSW_CANIF_46
\DESCRIPTION Function call via function pointer: Access to CanIf_CanDrvFctTbl via indirection over CanIf_GetCanDrvFctTblIdxOfCanChannelIdUpToLowMap with CanIf_Controller_Value.
                                                 CanIf_Controller_Value_Local is derived from CanTxPduId via CanIf_GetCtrlStatesIdxOfTxPduConfig.
             Function call with parameter data pointer: The data pointer is passed through the function with the same type.
\COUNTERMEASURE \N Function call via function pointer: CanIf_Init() makes a check that the dimension of CanIf_CtrlStates[] fits the dimension of CanIf_CanChannelIdUpToLowMap[], 
                                                       to ensure the indirection with CanIf_Controller_Value into CanIf_GetCanDrvFctTblIdxOfCanChannelIdUpToLowMap[].
                                                       The DET check of the function verifes that the CanTxPduId is smaller than the size of CanIf_GetCtrlStatesIdxOfTxPduConfig[],
                                                       to ensure the indirection with CanTxPduId into CanIf_GetCtrlStatesIdxOfTxPduConfig[].
                                                       The following indirection to get a valid function pointer is ensured via qualified use-case CSL03 of ComStackLib.
                   Function call with parameter data pointer: The caller ensures that the passed-through pointer parameter is valid.

\ID SBSW_CANIF_47
\DESCRIPTION Function call via function pointer: Access to CanIf_CanDrvFctTbl via indirection over CanIf_GetCanDrvFctTblIdxOfCanChannelIdUpToLowMap with CanIf_Controller_Value.
                                                 CanIf_Controller_Value_Local is derived from CanTxPduId via CanIf_GetCtrlStatesIdxOfTxPduConfig.
             Function call with parameter data pointer: The data pointer references a local structure.
\COUNTERMEASURE \N Function call via function pointer: CanIf_Init() makes a check that the dimension of CanIf_CtrlStates[] fits the dimension of CanIf_CanChannelIdUpToLowMap[], 
                                                       to ensure the indirection with CanIf_Controller_Value into CanIf_GetCanDrvFctTblIdxOfCanChannelIdUpToLowMap[].
                                                       The DET check of the function verifes that the CanTxPduId is smaller than the size of CanIf_GetCtrlStatesIdxOfTxPduConfig[],
                                                       to ensure the indirection with CanTxPduId into CanIf_GetCtrlStatesIdxOfTxPduConfig[].
                                                       The following indirection to get a valid function pointer is ensured via qualified use-case CSL03 of ComStackLib.
                   Function call with parameter data pointer: Data pointer references a stack variable and is therefore always valid.
            
SBSW_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  COVERAGE JUSTIFICATIONS
 *********************************************************************************************************************/
 
/* START_COVERAGE_JUSTIFICATION

\ID COV_CANIF_GENDATA_FAILURE
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT X
  \ACCEPT Tx tx tx
  \REASON The condition checks for generated data failures, that cannot be simulated. The code is verified by code inspection.

\ID COV_CANIF_NOT_APPLICABLE_FOR_EACH_CONFIG
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX tx xx
  \REASON It is not possible to vary the several parameter within one configuration. It will be secured by inspection that both decisions are covered,
          for minimum one time, over all configurations.

\ID COV_CANIF_UNSUPPORTED
  \ACCEPT XF
  \ACCEPT X
  \REASON The feature is not possible in conjunction with SafeBSW. A MSSV plug-in enforces this configuration.          

\ID COV_CANIF_UNSUPPORTED_J1939_DYN_ADDR
  \ACCEPT XF
  \ACCEPT TF tf xf tf
  \ACCEPT TF tf tf xf tf tf tf
  \REASON CANIF_J1939_DYN_ADDR_SUPPORT != CANIF_J1939_DYN_ADDR_DISABLED not supported yet in conjunction with SafeBSW. A MSSV plug-in enforces this configuration.

\ID COV_CANIF_FEATURE_DISCONTINUED
  \ACCEPT XF
  \REASON Feature is not still supported, with this define check it is ensured that is not enabled by accident, for example with old generator.   

\ID COV_CANIF_FILTER_RULE
  \ACCEPT XF
  \ACCEPT TX
  \REASON Define is not a preprocessor instruction, its used for filtering the component and must not still exist during compile time. Usage in case of SafeBSW-project is prohibited by an error-directive.
  
\ID COV_CANIF_PLATFORM_DEPENDENCY
  \ACCEPT TX
  \REASON Only 32 bit and 64 bit platforms are supported. A MSSV plug-in enforces this configuration. 

\ID COV_CANIF_ONE_CHANNEL_OPTIMIZATION_UNSUPPORTED
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF xf tf
  \ACCEPT XF tf tf
  \ACCEPT XF xf xf
  \REASON The feature is not possible in conjunction with SafeBSW. A MSSV plug-in enforces this configuration.

\ID COV_CANIF_NO_RANGE_SEARCH
  \ACCEPT X
  \ACCEPT XF
  \REASON Never called/true for configurations without defined ranges. It will be secured by inspection that both decisions are covered,\
          for minimum one time, over all configurations.
  
\ID COV_CANIF_NO_TX_BUFFER
  \ACCEPT TX
  \ACCEPT XF
  \REASON Always true/false if no Tx buffer is configured. It will be secured by inspection that both decisions are covered,
          for minimum one time, over all configurations

\ID COV_CANIF_FULLCAN
  \ACCEPT XF 
  \ACCEPT TX 
  \ACCEPT X 
  \REASON Always true/false if no/only FullCAN is configured. It will be secured by inspection that both decisions are covered,
          for minimum one time, over all configurations

\ID COV_CANIF_COMPATIBILITY
  \ACCEPT TX
  \REASON The condition checks whether a switch is defined and conditionally assigns a default value. This is used to ensure compatibility to future generator changes.
          The correctness is ensured by code review.

\ID COV_CANIF_MIXED_ID
  \ACCEPT TX
  \REASON The feature is platform specific.  

\ID COV_CANIF_REDEFINITION_PROTECTION
  \ACCEPT TX
  \ACCEPT XF
  \REASON For special requirements this defines may be defined from outside.

\ID COV_CANIF_ONLY_VECTOR_VSTDLIB_USED
  \ACCEPT TX
  \REASON This define is always set if VECTOR Vstdlib is used.

END_COVERAGE_JUSTIFICATION */ 

/**********************************************************************************************************************
 *  END OF FILE: CanIf.c
 *********************************************************************************************************************/
