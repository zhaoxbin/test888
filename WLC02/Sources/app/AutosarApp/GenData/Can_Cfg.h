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
 *            Module: Can
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Can_Cfg.h
 *   Generation Time: 2020-06-20 15:53:44
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

/**********************************************************************************************************************
 * WARNING: This code has been generated with reduced-severity errors. 
 * The created output files contain errors that have been ignored. Usage of the created files can lead to unpredictable behavior of the embedded code.
 * Usage of the created files happens at own risk!
 * 
 * [Warning] CAN02002 - An invalid value is configured 
 * - [Reduced Severity due to User-Defined Parameter] CanBaudrateClock has to be set according to CanCpuClockRef and hardware settings.
 * Erroneous configuration elements:
 * /ActiveEcuC/Can/CanConfigSet/CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593/CanControllerBaudrateConfig[0:CanBaudrateClock](value=40000) (DefRef: /MICROSAR/Can_Sh2Rscan/Can/CanConfigSet/CanController/CanControllerBaudrateConfig/CanBaudrateClock)
 *********************************************************************************************************************/
/* -----------------------------------------------------------------------------
    Generator Info
 ----------------------------------------------------------------------------- 
  Name:     MICROSAR Can Sh2Rscan driver generator
  Version:  5.02.00
  MSN:      Can
  Origin:   CAN
  Descrip:  MICROSAR Can driver generator
  JavaPack: com.vector.cfg.gen.DrvCan_Sh2RscanAsr
 ----------------------------------------------------------------------------- */

#if !defined(CAN_CFG_H)
#define CAN_CFG_H

/* CAN222, CAN389, CAN365, CAN366, CAN367 */
/* CAN022, CAN047, CAN388, CAN397, CAN390, CAN392  */

/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2 */

/* -----------------------------------------------------------------------------
    Includes
 ----------------------------------------------------------------------------- */

#include "ComStack_Types.h"

#include "Can_GeneralTypes.h" /* CAN435 */

#include "EcuM_Cbk.h"

#if defined (CAN_LCFG_SOURCE) || defined (C_DRV_INTERNAL) /* ESCAN00070085 */
# include "Os.h"
#endif

/* -----------------------------------------------------------------------------
    General Switches for CAN module
 ----------------------------------------------------------------------------- */

#ifndef CAN_USE_DUMMY_STATEMENT
#define CAN_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/EcuC/EcucGeneral/DummyStatement */
#endif
#ifndef CAN_DUMMY_STATEMENT
#define CAN_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CAN_DUMMY_STATEMENT_CONST
#define CAN_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CAN_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define CAN_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef CAN_ATOMIC_VARIABLE_ACCESS
#define CAN_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef CAN_CPU_F1KM
#define CAN_CPU_F1KM
#endif
#ifndef CAN_PROCESSOR_RH850_1649
#define CAN_PROCESSOR_RH850_1649
#endif
#ifndef CAN_COMP_GREENHILLS
#define CAN_COMP_GREENHILLS
#endif
#ifndef CAN_GEN_GENERATOR_MSR
#define CAN_GEN_GENERATOR_MSR
#endif
#ifndef CAN_CPUTYPE_BITORDER_LSB2MSB
#define CAN_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef CAN_CONFIGURATION_VARIANT_PRECOMPILE
#define CAN_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef CAN_CONFIGURATION_VARIANT_LINKTIME
#define CAN_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef CAN_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define CAN_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef CAN_CONFIGURATION_VARIANT
#define CAN_CONFIGURATION_VARIANT CAN_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef CAN_POSTBUILD_VARIANT_SUPPORT
#define CAN_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/* -----------------------------------------------------------------------------
    General Switches from old v_cfg.h
 ----------------------------------------------------------------------------- */
#if !defined(V_GEN_GENERATOR5)
# define V_GEN_GENERATOR5 /* need by LL */
#endif
#if !defined(V_ENABLE_CAN_ASR_ABSTRACTION)
# define V_ENABLE_CAN_ASR_ABSTRACTION /* ATK */
#endif
#define CAN_GEN_COM_STACK_LIB

#if !defined( V_OSTYPE_AUTOSAR )
# define V_OSTYPE_AUTOSAR
#endif

#if (CPU_TYPE == CPU_TYPE_32)
# if !defined( C_CPUTYPE_32BIT )
#  define C_CPUTYPE_32BIT
# endif
#endif
#if (CPU_TYPE == CPU_TYPE_16)
# if !defined( C_CPUTYPE_16BIT )
#  define C_CPUTYPE_16BIT
# endif
#endif
#if (CPU_TYPE == CPU_TYPE_8)
# if !defined( C_CPUTYPE_8BIT )
#  define C_CPUTYPE_8BIT
# endif
#endif
#if (CPU_BIT_ORDER == LSB_FIRST)
# if !defined( C_CPUTYPE_BITORDER_LSB2MSB )
#  define C_CPUTYPE_BITORDER_LSB2MSB
# endif
#endif
#if (CPU_BIT_ORDER == MSB_FIRST)
# if !defined( C_CPUTYPE_BITORDER_MSB2LSB )
#  define C_CPUTYPE_BITORDER_MSB2LSB
# endif
#endif
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
# if !defined( C_CPUTYPE_LITTLEENDIAN )
#  define C_CPUTYPE_LITTLEENDIAN
# endif
#endif
#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
# if !defined( C_CPUTYPE_BIGENDIAN )
#  define C_CPUTYPE_BIGENDIAN
# endif
#endif

#if !defined( V_DISABLE_USE_DUMMY_FUNCTIONS )
# define V_DISABLE_USE_DUMMY_FUNCTIONS
#endif
#if !defined( V_ENABLE_USE_DUMMY_STATEMENT )
# define V_ENABLE_USE_DUMMY_STATEMENT
#endif

#if !defined( V_CPU_RH850 )
# define V_CPU_RH850
#endif

#if !defined( C_PROCESSOR_F1KM )
# define C_PROCESSOR_F1KM
#endif
#if !defined( V_PROCESSOR_F1KM )
# define V_PROCESSOR_F1KM
#endif

#if !defined( C_COMP_GHS_RH850_RSCAN )
#define C_COMP_GHS_RH850_RSCAN
#endif
#if !defined( V_COMP_GHS )
# define V_COMP_GHS
#endif
#if !defined( V_COMP_GHS_RH850 )
# define V_COMP_GHS_RH850
#endif

#if !defined( V_SUPPRESS_EXTENDED_VERSION_CHECK )
# define V_SUPPRESS_EXTENDED_VERSION_CHECK
#endif

/* -----------------------------------------------------------------------------
    Version defines
 ----------------------------------------------------------------------------- */

/* CAN024, CAN023 */
#define CAN_ASR_VERSION              0x0400u
#define CAN_GEN_BASE_CFG5_VERSION    0x0103u
#define CAN_GEN_BASESASR_VERSION     0x0407u
#define CAN_GEN_SH2RSCANASR_VERSION              0x0302u
#define CAN_MICROSAR_VERSION         CAN_MSR403

/* -----------------------------------------------------------------------------
    Hardcoded defines
 ----------------------------------------------------------------------------- */

#define CAN_INSTANCE_ID           0

#define CAN_RX_BASICCAN_TYPE                 0u
#define CAN_RX_FULLCAN_TYPE                  1u
#define CAN_TX_BASICCAN_TYPE                 2u
#define CAN_TX_FULLCAN_TYPE                  3u
#define CAN_UNUSED_CAN_TYPE                  4u
#define CAN_TX_BASICCAN_MUX_TYPE             5u
#define CAN_TX_BASICCAN_FIFO_TYPE            6u

#define CAN_INTERRUPT                        0u
#define CAN_POLLING                          1u

#define kCanChannelNotUsed                     CAN_NO_CANIFCHANNELID 

#define CAN_NONE                             0u
/* RAM check (also  none) */
#define CAN_NOTIFY_ISSUE                     1u
#define CAN_NOTIFY_MAILBOX                   2u
#define CAN_EXTENDED                         3u
/* Interrupt lock (also  none) */
#define CAN_DRIVER                           1u
#define CAN_APPL                             2u
#define CAN_BOTH                             3u
/* Overrun Notification (als none,appl) */
#define CAN_DET                              1u
/* CAN FD Support */
#define CAN_BRS                              1u
#define CAN_FULL                             2u
/* CAN FD Configuration */
#define CAN_FD_RXONLY                        2u /* FD Baudrate exist (RX) */
#define CAN_FD_RXTX                          1u /* FD Baudrate also used for TX */
/* Generic Confirmation */
#define CAN_API1                             1u
#define CAN_API2                             2u

#define CAN_OS_TICK2MS(tick)     OS_TICKS2MS_SystemTimer((tick))     /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define CAN_OS_COUNTER_ID        SystemTimer

/* -----------------------------------------------------------------------------
    Defines / Switches
 ----------------------------------------------------------------------------- */

/* Version and Issue detection */
#define CAN_VERSION_INFO_API                 STD_OFF   /* CAN106_Conf */
#define CAN_DEV_ERROR_DETECT                 STD_ON   /* CAN064_Conf */
#define CAN_DEV_ERROR_REPORT                 STD_ON
#define CAN_SAFE_BSW                         STD_OFF

/* Interrupt / Polling */
#define CAN_TX_PROCESSING                    CAN_INTERRUPT   /* CAN318_Conf */
#define CAN_RX_PROCESSING                    CAN_INTERRUPT   /* CAN317_Conf */
#define CAN_BUSOFF_PROCESSING                CAN_INTERRUPT   /* CAN314_Conf */
#define CAN_WAKEUP_PROCESSING                CAN_POLLING   /* CAN319_Conf */
#define CAN_INDIVIDUAL_PROCESSING            STD_OFF
#define CAN_INTERRUPT_USED                   STD_ON
#define CAN_NESTED_INTERRUPTS                STD_OFF
#define C_ENABLE_OSEK_OS_INTCAT2
#define C_DISABLE_ISRVOID
#define CAN_INTLOCK                          CAN_DRIVER

/* Tx Handling */
#define CAN_MULTIPLEXED_TX_MAX               1u
#define CAN_CANCEL_SUPPORT_API               STD_OFF
#define CAN_TRANSMIT_BUFFER                  STD_ON
#define CAN_MULTIPLEXED_TRANSMISSION         STD_OFF   /* CAN095_Conf */
#define CAN_TX_HW_FIFO                       STD_OFF
#define CAN_HW_TRANSMIT_CANCELLATION         STD_OFF   /* CAN069_Conf */
#define CAN_IDENTICAL_ID_CANCELLATION        STD_OFF   /* CAN378_Conf */
#define CAN_MULTIPLE_BASICCAN_TX             STD_OFF

/* Rx Handling */
#define CAN_MULTIPLE_BASICCAN                STD_OFF
#define CAN_RX_QUEUE                         STD_OFF
#define CAN_OVERRUN_NOTIFICATION             CAN_DET

/* Sleep Wakeup */
#define CAN_SLEEP_SUPPORT                    STD_ON
#define CAN_WAKEUP_SUPPORT                   STD_ON   /* CAN330_Conf */

/* Hardware loop check */
#define CAN_HARDWARE_CANCELLATION            STD_ON
#define CAN_TIMEOUT_DURATION                 10uL   /* CAN113_Conf */
#define CAN_LOOP_MAX                         4u

/* Appl calls */
#define CAN_HW_LOOP_SUPPORT_API              STD_OFF
#define CAN_GENERIC_PRECOPY                  STD_OFF
#define CAN_GENERIC_CONFIRMATION             STD_OFF
#define CAN_GENERIC_PRETRANSMIT              STD_OFF
#define CAN_USE_OS_INTERRUPT_CONTROL         STD_ON

/* Optimization */
#define CAN_RX_FULLCAN_OBJECTS               STD_OFF
#define CAN_TX_FULLCAN_OBJECTS               STD_OFF
#define CAN_RX_BASICCAN_OBJECTS              STD_ON
#define CAN_EXTENDED_ID                      STD_OFF
#define CAN_MIXED_ID                         STD_OFF
#define CAN_ONE_CONTROLLER_OPTIMIZATION      STD_ON
#define CAN_CHANGE_BAUDRATE_API              STD_OFF   /* CAN460_Conf */
#define CAN_FD_HW_BUFFER_OPTIMIZATION        STD_ON

/* CAN FD */
#define CAN_SET_BAUDRATE_API                 STD_OFF   /* CAN482_Conf */
#define CAN_FD_SUPPORT                       CAN_NONE

/* Other */
#define CAN_COMMON_CAN                       STD_OFF
#define CAN_RAM_CHECK                        CAN_NONE
#define CAN_REINIT_START                     STD_OFF
#define CAN_GET_STATUS                       STD_OFF
#define CAN_RUNTIME_MEASUREMENT_SUPPORT      STD_OFF
#define CAN_PROTECTED_MODE                   STD_OFF
#define CAN_MIRROR_MODE                      STD_OFF
#define CAN_SILENT_MODE                      STD_OFF
#define CAN_CHECK_WAKEUP_CAN_RET_TYPE        STD_OFF
/* -----------------------------------------------------------------------------
    Channel And Mailbox
 ----------------------------------------------------------------------------- */
#ifndef C_DRV_INTERNAL
# ifndef kCanNumberOfChannels
#  define kCanNumberOfChannels               1u
# endif
# ifndef kCanNumberOfHwChannels
#  define kCanNumberOfHwChannels             1u
# endif
#endif
#ifndef kCanNumberOfUsedChannels /* ATK only */
# define kCanNumberOfUsedChannels            1u
#endif

#define kCanPhysToLogChannelIndex_0 

#define kCanNumberOfPhysChannels             1u

/* -----------------------------------------------------------------------------
    Symbolic Name Values for Controller, HardwareObject and Baudrates
 ----------------------------------------------------------------------------- */
/* These definitions can change at Link-time and Post-build configuration time. Use them wisely. */



/**
 * \defgroup CanHandleIdsactivated Handle IDs of handle space activated.
 * \brief controllers by CanControllerActivation
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define CanConf_CanController_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593      0u
/**\} */
#define CanConf_CN_NIO_ES6_RF_CAN_SR_V3_0_91fc07e0_Rx 1u
#define CanConf_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_Tx 0u

#define CanConf_ControllerBaudrateConfig_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593_CanControllerBaudrateConfig 0u

#define CanConf_MemorySection_RxBuffer 2u
#define CanConf_MemorySection_RxFifo 1u
#define CanConf_MemorySection_TxBuffer_CT_NIO_ES6_RF_CAN_SR_V3_0_a63ca593 0u



/* -----------------------------------------------------------------------------
    Types
 ----------------------------------------------------------------------------- */
/* HW specific BEGIN */

#define kCanBaseAdr                          0xFFD00000uL
#define kCanIntcRxFifoBaseAdr                0xFFFEEA2EuL
#define kCanIntcGErrorBaseAdr                0xFFFEEA2CuL
#define kCanIntcChTxBaseAdr                  0xFFFEEA34uL
#define kCanIntcChErrorBaseAdr               0xFFFEEA30uL
#define kCanIntcChWakeupBaseAdr              0xFFFFB04AuL

#define kCanMaxPhysChannels                  8u
#define kCanMaxRxFifos                       8u
#define kCanMaxTxFifos                       3u
#define kCanMaxTxBuf                         32u
#define kCanMaxRxBuf                         128u
#define kCanMaxPoolBuf                       1024u
#define kCanMaxRules                         1024u
#define kCanNumberOfSharedReg16              1u
#define kCanLogToPhys                        0u

#define C_ENABLE_IF_RSCAN_FD_V3
#define C_ENABLE_INT_LAYOUT_TWOGLOBAL_THREELOCAL
#define C_ENABLE_BUSWAKEUP_SUPPORT
#define C_ENABLE_SINGLE_PHYS_CHANNEL_OPTIMIZATION
#define C_DISABLE_ALTERNATIVE_CLOCK_SOURCE

typedef struct tCanLLCanIntOldTag
{
  uint8 Err;
  uint8 Tx;
  uint8 Wup;
} tCanLLCanIntOld;

typedef struct tCanTmpMsgObjTag
{
  uint32 Id;
  uint32 Dlc;
  uint32 Fd;
  union
  { /* PRQA S 0750 */ /* MD_Can_Union */
    uint8     bData[8];
    uint16    wData[4];
    uint32    iData[2];
  } u;
} tCanTmpMsgObj;

#if (defined(CAN_LCFG_SOURCE) || defined(C_DRV_INTERNAL)) && (CAN_USE_OS_INTERRUPT_CONTROL == STD_ON)
typedef ISRType Can_ExternalISRType;
#else
typedef uint32 Can_ExternalISRType;
#endif
 
/* HW specific END */ 

typedef VAR(uint8, TYPEDEF) CanChannelHandle;

#if defined (CAN_LCFG_SOURCE) || defined (C_DRV_INTERNAL)
typedef TickType Can_ExternalTickType;
#else
typedef uint32 Can_ExternalTickType;
#endif

typedef VAR(Can_ExternalTickType, TYPEDEF) Can_LoopTimeout_dim_type[CAN_LOOP_MAX+1u];




/* -----------------------------------------------------------------------------
    CONST Declarations
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    VAR Declarations
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    Hw specific
 ----------------------------------------------------------------------------- */
/* HW specific BEGIN */

/* HW specific END */


/**********************************************************************************************************************
  ComStackLib
**********************************************************************************************************************/
/* Can_GlobalConfig: CAN354_Conf */
/* Can_ConfigType: CAN413 */

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanPCDataSwitches  Can Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CAN_ACTIVESENDOBJECT                                          STD_ON
#define CAN_PDUOFACTIVESENDOBJECT                                     STD_ON
#define CAN_STATEOFACTIVESENDOBJECT                                   STD_ON
#define CAN_BASEDLL_GENERATORVERSION                                  STD_ON
#define CAN_CANIFCHANNELID                                            STD_ON
#define CAN_CHANNELDATA                                               STD_ON
#define CAN_FIFOPROCCOUNTOFCHANNELDATA                                STD_ON
#define CAN_FRSTARTINDEXOFCHANNELDATA                                 STD_ON
#define CAN_FRTOTALCOUNTOFCHANNELDATA                                 STD_ON
#define CAN_RXBCMASKOFCHANNELDATA                                     STD_ON
#define CAN_RXBCSTARTINDEXOFCHANNELDATA                               STD_ON
#define CAN_RXBCSTOPINDEXOFCHANNELDATA                                STD_ON
#define CAN_TXINTMASKOFCHANNELDATA                                    STD_ON
#define CAN_CONTROLLERCONFIG                                          STD_ON
#define CAN_CANCONTROLLERDEFAULTBAUDRATEIDXOFCONTROLLERCONFIG         STD_ON
#define CAN_CANCONTROLLERDEFAULTBAUDRATEOFCONTROLLERCONFIG            STD_ON
#define CAN_MAILBOXRXBASICENDIDXOFCONTROLLERCONFIG                    STD_ON
#define CAN_MAILBOXRXBASICLENGTHOFCONTROLLERCONFIG                    STD_ON
#define CAN_MAILBOXRXBASICSTARTIDXOFCONTROLLERCONFIG                  STD_ON
#define CAN_MAILBOXRXBASICUSEDOFCONTROLLERCONFIG                      STD_ON
#define CAN_MAILBOXRXFULLENDIDXOFCONTROLLERCONFIG                     STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxRxFullEndIdx' Reason: 'the optional indirection is deactivated because MailboxRxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXRXFULLLENGTHOFCONTROLLERCONFIG                     STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxRxFullLength' Reason: 'the optional indirection is deactivated because MailboxRxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXRXFULLSTARTIDXOFCONTROLLERCONFIG                   STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxRxFullStartIdx' Reason: 'the optional indirection is deactivated because MailboxRxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXRXFULLUSEDOFCONTROLLERCONFIG                       STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxRxFullUsed' Reason: 'the optional indirection is deactivated because MailboxRxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXTXBASICENDIDXOFCONTROLLERCONFIG                    STD_ON
#define CAN_MAILBOXTXBASICLENGTHOFCONTROLLERCONFIG                    STD_ON
#define CAN_MAILBOXTXBASICSTARTIDXOFCONTROLLERCONFIG                  STD_ON
#define CAN_MAILBOXTXBASICUSEDOFCONTROLLERCONFIG                      STD_ON
#define CAN_MAILBOXTXFULLENDIDXOFCONTROLLERCONFIG                     STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxTxFullEndIdx' Reason: 'the optional indirection is deactivated because MailboxTxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXTXFULLLENGTHOFCONTROLLERCONFIG                     STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxTxFullLength' Reason: 'the optional indirection is deactivated because MailboxTxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXTXFULLSTARTIDXOFCONTROLLERCONFIG                   STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxTxFullStartIdx' Reason: 'the optional indirection is deactivated because MailboxTxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXTXFULLUSEDOFCONTROLLERCONFIG                       STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxTxFullUsed' Reason: 'the optional indirection is deactivated because MailboxTxFullUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXUNUSEDENDIDXOFCONTROLLERCONFIG                     STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxUnusedEndIdx' Reason: 'the optional indirection is deactivated because MailboxUnusedUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXUNUSEDLENGTHOFCONTROLLERCONFIG                     STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxUnusedLength' Reason: 'the optional indirection is deactivated because MailboxUnusedUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXUNUSEDSTARTIDXOFCONTROLLERCONFIG                   STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxUnusedStartIdx' Reason: 'the optional indirection is deactivated because MailboxUnusedUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_MAILBOXUNUSEDUSEDOFCONTROLLERCONFIG                       STD_OFF  /**< Deactivateable: 'Can_ControllerConfig.MailboxUnusedUsed' Reason: 'the optional indirection is deactivated because MailboxUnusedUsedOfControllerConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define CAN_RXBASICHWSTARTOFCONTROLLERCONFIG                          STD_ON
#define CAN_RXBASICHWSTOPOFCONTROLLERCONFIG                           STD_ON
#define CAN_RXFULLHWSTARTOFCONTROLLERCONFIG                           STD_ON
#define CAN_RXFULLHWSTOPOFCONTROLLERCONFIG                            STD_ON
#define CAN_TXBASICHWSTARTOFCONTROLLERCONFIG                          STD_ON
#define CAN_TXBASICHWSTOPOFCONTROLLERCONFIG                           STD_ON
#define CAN_TXFULLHWSTARTOFCONTROLLERCONFIG                           STD_ON
#define CAN_TXFULLHWSTOPOFCONTROLLERCONFIG                            STD_ON
#define CAN_UNUSEDHWSTARTOFCONTROLLERCONFIG                           STD_ON
#define CAN_UNUSEDHWSTOPOFCONTROLLERCONFIG                            STD_ON
#define CAN_CONTROLLERDATA                                            STD_ON
#define CAN_BUSOFFCOUNTEROFCONTROLLERDATA                             STD_ON
#define CAN_BUSOFFTRANSITIONREQUESTOFCONTROLLERDATA                   STD_ON
#define CAN_CANINTERRUPTCOUNTEROFCONTROLLERDATA                       STD_ON
#define CAN_CANINTERRUPTOLDSTATUSOFCONTROLLERDATA                     STD_ON
#define CAN_ISBUSOFFOFCONTROLLERDATA                                  STD_ON
#define CAN_ISWAKEUPOFCONTROLLERDATA                                  STD_ON
#define CAN_LASTINITOBJECTOFCONTROLLERDATA                            STD_ON
#define CAN_LOGSTATUSOFCONTROLLERDATA                                 STD_ON
#define CAN_LOOPTIMEOUTOFCONTROLLERDATA                               STD_ON
#define CAN_MODETRANSITIONREQUESTOFCONTROLLERDATA                     STD_ON
#define CAN_RAMCHECKTRANSITIONREQUESTOFCONTROLLERDATA                 STD_ON
#define CAN_RXTMPBUFOFCONTROLLERDATA                                  STD_ON
#define CAN_FINALMAGICNUMBER                                          STD_OFF  /**< Deactivateable: 'Can_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define CAN_INITDATAHASHCODE                                          STD_OFF  /**< Deactivateable: 'Can_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define CAN_INITFILTERRULES                                           STD_ON
#define CAN_CODEOFINITFILTERRULES                                     STD_ON
#define CAN_MASKOFINITFILTERRULES                                     STD_ON
#define CAN_INITOBJECTBAUDRATE                                        STD_ON
#define CAN_INITOBJECTBITTIMING                                       STD_ON
#define CAN_INITOBJECTBITTIMINGDATA                                   STD_ON
#define CAN_INITOBJECTCANFDCONFIG                                     STD_ON
#define CAN_INITOBJECTSTARTINDEX                                      STD_ON
#define CAN_MAILBOX                                                   STD_ON
#define CAN_ACTIVESENDOBJECTOFMAILBOX                                 STD_ON
#define CAN_CONTROLLERCONFIGIDXOFMAILBOX                              STD_ON
#define CAN_HWHANDLEOFMAILBOX                                         STD_ON
#define CAN_IDVALUEOFMAILBOX                                          STD_ON
#define CAN_MAILBOXSIZEOFMAILBOX                                      STD_ON
#define CAN_MAILBOXTYPEOFMAILBOX                                      STD_ON
#define CAN_MAXDATALENOFMAILBOX                                       STD_ON
#define CAN_MEMORYSECTIONSINDEXOFMAILBOX                              STD_ON
#define CAN_MEMORYSECTIONINFO                                         STD_ON
#define CAN_MEMORYSECTIONSTARTOFMEMORYSECTIONINFO                     STD_ON
#define CAN_MEMORYSECTIONOBJECTS                                      STD_ON
#define CAN_HWHANDLEOFMEMORYSECTIONOBJECTS                            STD_ON
#define CAN_MAILBOXELEMENTOFMEMORYSECTIONOBJECTS                      STD_ON
#define CAN_MAILBOXHANDLEOFMEMORYSECTIONOBJECTS                       STD_ON
#define CAN_OSISRID                                                   STD_ON
#define CAN_ISRSTATUSIDOFOSISRID                                      STD_ON
#define CAN_ISRTXIDOFOSISRID                                          STD_ON
#define CAN_ISRWAKEUPIDOFOSISRID                                      STD_ON
#define CAN_PLATFORMDLL_GENERATORVERSION                              STD_ON
#define CAN_RXFIFODATA                                                STD_ON
#define CAN_CONTROLLEROFRXFIFODATA                                    STD_ON
#define CAN_FIFODEPTHOFRXFIFODATA                                     STD_ON
#define CAN_FILTERSTARTINDEXOFRXFIFODATA                              STD_ON
#define CAN_FILTERSTOPINDEXOFRXFIFODATA                               STD_ON
#define CAN_SIZEOFACTIVESENDOBJECT                                    STD_ON
#define CAN_SIZEOFCANIFCHANNELID                                      STD_ON
#define CAN_SIZEOFCHANNELDATA                                         STD_ON
#define CAN_SIZEOFCONTROLLERCONFIG                                    STD_ON
#define CAN_SIZEOFCONTROLLERDATA                                      STD_ON
#define CAN_SIZEOFINITFILTERRULES                                     STD_ON
#define CAN_SIZEOFINITOBJECTBAUDRATE                                  STD_ON
#define CAN_SIZEOFINITOBJECTBITTIMING                                 STD_ON
#define CAN_SIZEOFINITOBJECTBITTIMINGDATA                             STD_ON
#define CAN_SIZEOFINITOBJECTCANFDCONFIG                               STD_ON
#define CAN_SIZEOFINITOBJECTSTARTINDEX                                STD_ON
#define CAN_SIZEOFMAILBOX                                             STD_ON
#define CAN_SIZEOFMEMORYSECTIONINFO                                   STD_ON
#define CAN_SIZEOFMEMORYSECTIONOBJECTS                                STD_ON
#define CAN_SIZEOFOSISRID                                             STD_ON
#define CAN_SIZEOFRXFIFODATA                                          STD_ON
#define CAN_SIZEOFWAKEUPSOURCEREF                                     STD_ON
#define CAN_WAKEUPSOURCEREF                                           STD_ON
#define CAN_PCCONFIG                                                  STD_ON
#define CAN_ACTIVESENDOBJECTOFPCCONFIG                                STD_ON
#define CAN_BASEDLL_GENERATORVERSIONOFPCCONFIG                        STD_ON
#define CAN_CANIFCHANNELIDOFPCCONFIG                                  STD_ON
#define CAN_CHANNELDATAOFPCCONFIG                                     STD_ON
#define CAN_CONTROLLERCONFIGOFPCCONFIG                                STD_ON
#define CAN_CONTROLLERDATAOFPCCONFIG                                  STD_ON
#define CAN_FINALMAGICNUMBEROFPCCONFIG                                STD_OFF  /**< Deactivateable: 'Can_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define CAN_INITDATAHASHCODEOFPCCONFIG                                STD_OFF  /**< Deactivateable: 'Can_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define CAN_INITFILTERRULESOFPCCONFIG                                 STD_ON
#define CAN_INITOBJECTBAUDRATEOFPCCONFIG                              STD_ON
#define CAN_INITOBJECTBITTIMINGDATAOFPCCONFIG                         STD_ON
#define CAN_INITOBJECTBITTIMINGOFPCCONFIG                             STD_ON
#define CAN_INITOBJECTCANFDCONFIGOFPCCONFIG                           STD_ON
#define CAN_INITOBJECTSTARTINDEXOFPCCONFIG                            STD_ON
#define CAN_MAILBOXOFPCCONFIG                                         STD_ON
#define CAN_MEMORYSECTIONINFOOFPCCONFIG                               STD_ON
#define CAN_MEMORYSECTIONOBJECTSOFPCCONFIG                            STD_ON
#define CAN_OSISRIDOFPCCONFIG                                         STD_ON
#define CAN_PLATFORMDLL_GENERATORVERSIONOFPCCONFIG                    STD_ON
#define CAN_RXFIFODATAOFPCCONFIG                                      STD_ON
#define CAN_SIZEOFACTIVESENDOBJECTOFPCCONFIG                          STD_ON
#define CAN_SIZEOFCANIFCHANNELIDOFPCCONFIG                            STD_ON
#define CAN_SIZEOFCHANNELDATAOFPCCONFIG                               STD_ON
#define CAN_SIZEOFCONTROLLERCONFIGOFPCCONFIG                          STD_ON
#define CAN_SIZEOFCONTROLLERDATAOFPCCONFIG                            STD_ON
#define CAN_SIZEOFINITFILTERRULESOFPCCONFIG                           STD_ON
#define CAN_SIZEOFINITOBJECTBAUDRATEOFPCCONFIG                        STD_ON
#define CAN_SIZEOFINITOBJECTBITTIMINGDATAOFPCCONFIG                   STD_ON
#define CAN_SIZEOFINITOBJECTBITTIMINGOFPCCONFIG                       STD_ON
#define CAN_SIZEOFINITOBJECTCANFDCONFIGOFPCCONFIG                     STD_ON
#define CAN_SIZEOFINITOBJECTSTARTINDEXOFPCCONFIG                      STD_ON
#define CAN_SIZEOFMAILBOXOFPCCONFIG                                   STD_ON
#define CAN_SIZEOFMEMORYSECTIONINFOOFPCCONFIG                         STD_ON
#define CAN_SIZEOFMEMORYSECTIONOBJECTSOFPCCONFIG                      STD_ON
#define CAN_SIZEOFOSISRIDOFPCCONFIG                                   STD_ON
#define CAN_SIZEOFRXFIFODATAOFPCCONFIG                                STD_ON
#define CAN_SIZEOFWAKEUPSOURCEREFOFPCCONFIG                           STD_ON
#define CAN_WAKEUPSOURCEREFOFPCCONFIG                                 STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  CanPCMinNumericValueDefines  Can Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define CAN_MIN_PDUOFACTIVESENDOBJECT                                 0u
#define CAN_MIN_STATEOFACTIVESENDOBJECT                               0u
#define CAN_MIN_BUSOFFCOUNTEROFCONTROLLERDATA                         0u
#define CAN_MIN_BUSOFFTRANSITIONREQUESTOFCONTROLLERDATA               0u
#define CAN_MIN_CANINTERRUPTCOUNTEROFCONTROLLERDATA                   0u
#define CAN_MIN_LASTINITOBJECTOFCONTROLLERDATA                        0u
#define CAN_MIN_LOGSTATUSOFCONTROLLERDATA                             0u
#define CAN_MIN_MODETRANSITIONREQUESTOFCONTROLLERDATA                 0u
#define CAN_MIN_RAMCHECKTRANSITIONREQUESTOFCONTROLLERDATA             0u
/** 
  \}
*/ 

/** 
  \defgroup  CanPCMaxNumericValueDefines  Can Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define CAN_MAX_PDUOFACTIVESENDOBJECT                                 255u
#define CAN_MAX_STATEOFACTIVESENDOBJECT                               65535u
#define CAN_MAX_BUSOFFCOUNTEROFCONTROLLERDATA                         255u
#define CAN_MAX_BUSOFFTRANSITIONREQUESTOFCONTROLLERDATA               255u
#define CAN_MAX_CANINTERRUPTCOUNTEROFCONTROLLERDATA                   255u
#define CAN_MAX_LASTINITOBJECTOFCONTROLLERDATA                        255u
#define CAN_MAX_LOGSTATUSOFCONTROLLERDATA                             255u
#define CAN_MAX_MODETRANSITIONREQUESTOFCONTROLLERDATA                 255u
#define CAN_MAX_RAMCHECKTRANSITIONREQUESTOFCONTROLLERDATA             255u
/** 
  \}
*/ 

/** 
  \defgroup  CanPCNoReferenceDefines  Can No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define CAN_NO_CANIFCHANNELID                                         255u
#define CAN_NO_FIFOPROCCOUNTOFCHANNELDATA                             255u
#define CAN_NO_FRSTARTINDEXOFCHANNELDATA                              255u
#define CAN_NO_FRTOTALCOUNTOFCHANNELDATA                              255u
#define CAN_NO_RXBCMASKOFCHANNELDATA                                  255u
#define CAN_NO_RXBCSTARTINDEXOFCHANNELDATA                            255u
#define CAN_NO_RXBCSTOPINDEXOFCHANNELDATA                             255u
#define CAN_NO_TXINTMASKOFCHANNELDATA                                 255u
#define CAN_NO_CANCONTROLLERDEFAULTBAUDRATEIDXOFCONTROLLERCONFIG      255u
#define CAN_NO_CANCONTROLLERDEFAULTBAUDRATEOFCONTROLLERCONFIG         65535u
#define CAN_NO_MAILBOXRXBASICENDIDXOFCONTROLLERCONFIG                 255u
#define CAN_NO_MAILBOXRXBASICSTARTIDXOFCONTROLLERCONFIG               255u
#define CAN_NO_MAILBOXTXBASICENDIDXOFCONTROLLERCONFIG                 255u
#define CAN_NO_MAILBOXTXBASICSTARTIDXOFCONTROLLERCONFIG               255u
#define CAN_NO_RXBASICHWSTARTOFCONTROLLERCONFIG                       255u
#define CAN_NO_RXBASICHWSTOPOFCONTROLLERCONFIG                        255u
#define CAN_NO_RXFULLHWSTARTOFCONTROLLERCONFIG                        255u
#define CAN_NO_RXFULLHWSTOPOFCONTROLLERCONFIG                         255u
#define CAN_NO_TXBASICHWSTARTOFCONTROLLERCONFIG                       255u
#define CAN_NO_TXBASICHWSTOPOFCONTROLLERCONFIG                        255u
#define CAN_NO_TXFULLHWSTARTOFCONTROLLERCONFIG                        255u
#define CAN_NO_TXFULLHWSTOPOFCONTROLLERCONFIG                         255u
#define CAN_NO_UNUSEDHWSTARTOFCONTROLLERCONFIG                        255u
#define CAN_NO_UNUSEDHWSTOPOFCONTROLLERCONFIG                         255u
/** 
  \}
*/ 

/** 
  \defgroup  CanPCEnumExistsDefines  Can Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define CAN_EXISTS_RX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX              STD_ON
#define CAN_EXISTS_RX_FULLCAN_TYPE_MAILBOXTYPEOFMAILBOX               STD_OFF
#define CAN_EXISTS_TX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX              STD_ON
#define CAN_EXISTS_TX_FULLCAN_TYPE_MAILBOXTYPEOFMAILBOX               STD_OFF
#define CAN_EXISTS_UNUSED_CAN_TYPE_MAILBOXTYPEOFMAILBOX               STD_OFF
#define CAN_EXISTS_TX_BASICCAN_MUX_TYPE_MAILBOXTYPEOFMAILBOX          STD_OFF
#define CAN_EXISTS_TX_BASICCAN_FIFO_TYPE_MAILBOXTYPEOFMAILBOX         STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  CanPCEnumDefines  Can Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define CAN_RX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX                     0x00u
#define CAN_TX_BASICCAN_TYPE_MAILBOXTYPEOFMAILBOX                     0x02u
/** 
  \}
*/ 

/** 
  \defgroup  CanPCIsReducedToDefineDefines  Can Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define CAN_ISDEF_CANIFCHANNELID                                      STD_OFF
#define CAN_ISDEF_FIFOPROCCOUNTOFCHANNELDATA                          STD_OFF
#define CAN_ISDEF_FRSTARTINDEXOFCHANNELDATA                           STD_OFF
#define CAN_ISDEF_FRTOTALCOUNTOFCHANNELDATA                           STD_OFF
#define CAN_ISDEF_RXBCMASKOFCHANNELDATA                               STD_OFF
#define CAN_ISDEF_RXBCSTARTINDEXOFCHANNELDATA                         STD_OFF
#define CAN_ISDEF_RXBCSTOPINDEXOFCHANNELDATA                          STD_OFF
#define CAN_ISDEF_TXINTMASKOFCHANNELDATA                              STD_OFF
#define CAN_ISDEF_CANCONTROLLERDEFAULTBAUDRATEIDXOFCONTROLLERCONFIG   STD_OFF
#define CAN_ISDEF_CANCONTROLLERDEFAULTBAUDRATEOFCONTROLLERCONFIG      STD_OFF
#define CAN_ISDEF_MAILBOXRXBASICENDIDXOFCONTROLLERCONFIG              STD_OFF
#define CAN_ISDEF_MAILBOXRXBASICLENGTHOFCONTROLLERCONFIG              STD_OFF
#define CAN_ISDEF_MAILBOXRXBASICSTARTIDXOFCONTROLLERCONFIG            STD_OFF
#define CAN_ISDEF_MAILBOXRXBASICUSEDOFCONTROLLERCONFIG                STD_OFF
#define CAN_ISDEF_MAILBOXTXBASICENDIDXOFCONTROLLERCONFIG              STD_OFF
#define CAN_ISDEF_MAILBOXTXBASICLENGTHOFCONTROLLERCONFIG              STD_OFF
#define CAN_ISDEF_MAILBOXTXBASICSTARTIDXOFCONTROLLERCONFIG            STD_OFF
#define CAN_ISDEF_MAILBOXTXBASICUSEDOFCONTROLLERCONFIG                STD_OFF
#define CAN_ISDEF_RXBASICHWSTARTOFCONTROLLERCONFIG                    STD_OFF
#define CAN_ISDEF_RXBASICHWSTOPOFCONTROLLERCONFIG                     STD_OFF
#define CAN_ISDEF_RXFULLHWSTARTOFCONTROLLERCONFIG                     STD_OFF
#define CAN_ISDEF_RXFULLHWSTOPOFCONTROLLERCONFIG                      STD_OFF
#define CAN_ISDEF_TXBASICHWSTARTOFCONTROLLERCONFIG                    STD_OFF
#define CAN_ISDEF_TXBASICHWSTOPOFCONTROLLERCONFIG                     STD_OFF
#define CAN_ISDEF_TXFULLHWSTARTOFCONTROLLERCONFIG                     STD_OFF
#define CAN_ISDEF_TXFULLHWSTOPOFCONTROLLERCONFIG                      STD_OFF
#define CAN_ISDEF_UNUSEDHWSTARTOFCONTROLLERCONFIG                     STD_OFF
#define CAN_ISDEF_UNUSEDHWSTOPOFCONTROLLERCONFIG                      STD_OFF
#define CAN_ISDEF_CODEOFINITFILTERRULES                               STD_OFF
#define CAN_ISDEF_MASKOFINITFILTERRULES                               STD_OFF
#define CAN_ISDEF_INITOBJECTBAUDRATE                                  STD_OFF
#define CAN_ISDEF_INITOBJECTBITTIMING                                 STD_OFF
#define CAN_ISDEF_INITOBJECTBITTIMINGDATA                             STD_OFF
#define CAN_ISDEF_INITOBJECTCANFDCONFIG                               STD_OFF
#define CAN_ISDEF_INITOBJECTSTARTINDEX                                STD_OFF
#define CAN_ISDEF_ACTIVESENDOBJECTOFMAILBOX                           STD_OFF
#define CAN_ISDEF_CONTROLLERCONFIGIDXOFMAILBOX                        STD_OFF
#define CAN_ISDEF_HWHANDLEOFMAILBOX                                   STD_OFF
#define CAN_ISDEF_IDVALUEOFMAILBOX                                    STD_OFF
#define CAN_ISDEF_MAILBOXSIZEOFMAILBOX                                STD_OFF
#define CAN_ISDEF_MAILBOXTYPEOFMAILBOX                                STD_OFF
#define CAN_ISDEF_MAXDATALENOFMAILBOX                                 STD_OFF
#define CAN_ISDEF_MEMORYSECTIONSINDEXOFMAILBOX                        STD_OFF
#define CAN_ISDEF_MEMORYSECTIONSTARTOFMEMORYSECTIONINFO               STD_OFF
#define CAN_ISDEF_HWHANDLEOFMEMORYSECTIONOBJECTS                      STD_OFF
#define CAN_ISDEF_MAILBOXELEMENTOFMEMORYSECTIONOBJECTS                STD_OFF
#define CAN_ISDEF_MAILBOXHANDLEOFMEMORYSECTIONOBJECTS                 STD_OFF
#define CAN_ISDEF_ISRSTATUSIDOFOSISRID                                STD_OFF
#define CAN_ISDEF_ISRTXIDOFOSISRID                                    STD_OFF
#define CAN_ISDEF_ISRWAKEUPIDOFOSISRID                                STD_OFF
#define CAN_ISDEF_CONTROLLEROFRXFIFODATA                              STD_OFF
#define CAN_ISDEF_FIFODEPTHOFRXFIFODATA                               STD_OFF
#define CAN_ISDEF_FILTERSTARTINDEXOFRXFIFODATA                        STD_OFF
#define CAN_ISDEF_FILTERSTOPINDEXOFRXFIFODATA                         STD_OFF
#define CAN_ISDEF_WAKEUPSOURCEREF                                     STD_OFF
#define CAN_ISDEF_ACTIVESENDOBJECTOFPCCONFIG                          STD_ON
#define CAN_ISDEF_CANIFCHANNELIDOFPCCONFIG                            STD_ON
#define CAN_ISDEF_CHANNELDATAOFPCCONFIG                               STD_ON
#define CAN_ISDEF_CONTROLLERCONFIGOFPCCONFIG                          STD_ON
#define CAN_ISDEF_CONTROLLERDATAOFPCCONFIG                            STD_ON
#define CAN_ISDEF_INITFILTERRULESOFPCCONFIG                           STD_ON
#define CAN_ISDEF_INITOBJECTBAUDRATEOFPCCONFIG                        STD_ON
#define CAN_ISDEF_INITOBJECTBITTIMINGDATAOFPCCONFIG                   STD_ON
#define CAN_ISDEF_INITOBJECTBITTIMINGOFPCCONFIG                       STD_ON
#define CAN_ISDEF_INITOBJECTCANFDCONFIGOFPCCONFIG                     STD_ON
#define CAN_ISDEF_INITOBJECTSTARTINDEXOFPCCONFIG                      STD_ON
#define CAN_ISDEF_MAILBOXOFPCCONFIG                                   STD_ON
#define CAN_ISDEF_MEMORYSECTIONINFOOFPCCONFIG                         STD_ON
#define CAN_ISDEF_MEMORYSECTIONOBJECTSOFPCCONFIG                      STD_ON
#define CAN_ISDEF_OSISRIDOFPCCONFIG                                   STD_ON
#define CAN_ISDEF_RXFIFODATAOFPCCONFIG                                STD_ON
#define CAN_ISDEF_WAKEUPSOURCEREFOFPCCONFIG                           STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  CanPCEqualsAlwaysToDefines  Can Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define CAN_EQ2_CANIFCHANNELID                                        
#define CAN_EQ2_FIFOPROCCOUNTOFCHANNELDATA                            
#define CAN_EQ2_FRSTARTINDEXOFCHANNELDATA                             
#define CAN_EQ2_FRTOTALCOUNTOFCHANNELDATA                             
#define CAN_EQ2_RXBCMASKOFCHANNELDATA                                 
#define CAN_EQ2_RXBCSTARTINDEXOFCHANNELDATA                           
#define CAN_EQ2_RXBCSTOPINDEXOFCHANNELDATA                            
#define CAN_EQ2_TXINTMASKOFCHANNELDATA                                
#define CAN_EQ2_CANCONTROLLERDEFAULTBAUDRATEIDXOFCONTROLLERCONFIG     
#define CAN_EQ2_CANCONTROLLERDEFAULTBAUDRATEOFCONTROLLERCONFIG        
#define CAN_EQ2_MAILBOXRXBASICENDIDXOFCONTROLLERCONFIG                
#define CAN_EQ2_MAILBOXRXBASICLENGTHOFCONTROLLERCONFIG                
#define CAN_EQ2_MAILBOXRXBASICSTARTIDXOFCONTROLLERCONFIG              
#define CAN_EQ2_MAILBOXRXBASICUSEDOFCONTROLLERCONFIG                  
#define CAN_EQ2_MAILBOXTXBASICENDIDXOFCONTROLLERCONFIG                
#define CAN_EQ2_MAILBOXTXBASICLENGTHOFCONTROLLERCONFIG                
#define CAN_EQ2_MAILBOXTXBASICSTARTIDXOFCONTROLLERCONFIG              
#define CAN_EQ2_MAILBOXTXBASICUSEDOFCONTROLLERCONFIG                  
#define CAN_EQ2_RXBASICHWSTARTOFCONTROLLERCONFIG                      
#define CAN_EQ2_RXBASICHWSTOPOFCONTROLLERCONFIG                       
#define CAN_EQ2_RXFULLHWSTARTOFCONTROLLERCONFIG                       
#define CAN_EQ2_RXFULLHWSTOPOFCONTROLLERCONFIG                        
#define CAN_EQ2_TXBASICHWSTARTOFCONTROLLERCONFIG                      
#define CAN_EQ2_TXBASICHWSTOPOFCONTROLLERCONFIG                       
#define CAN_EQ2_TXFULLHWSTARTOFCONTROLLERCONFIG                       
#define CAN_EQ2_TXFULLHWSTOPOFCONTROLLERCONFIG                        
#define CAN_EQ2_UNUSEDHWSTARTOFCONTROLLERCONFIG                       
#define CAN_EQ2_UNUSEDHWSTOPOFCONTROLLERCONFIG                        
#define CAN_EQ2_CODEOFINITFILTERRULES                                 
#define CAN_EQ2_MASKOFINITFILTERRULES                                 
#define CAN_EQ2_INITOBJECTBAUDRATE                                    
#define CAN_EQ2_INITOBJECTBITTIMING                                   
#define CAN_EQ2_INITOBJECTBITTIMINGDATA                               
#define CAN_EQ2_INITOBJECTCANFDCONFIG                                 
#define CAN_EQ2_INITOBJECTSTARTINDEX                                  
#define CAN_EQ2_ACTIVESENDOBJECTOFMAILBOX                             
#define CAN_EQ2_CONTROLLERCONFIGIDXOFMAILBOX                          
#define CAN_EQ2_HWHANDLEOFMAILBOX                                     
#define CAN_EQ2_IDVALUEOFMAILBOX                                      
#define CAN_EQ2_MAILBOXSIZEOFMAILBOX                                  
#define CAN_EQ2_MAILBOXTYPEOFMAILBOX                                  
#define CAN_EQ2_MAXDATALENOFMAILBOX                                   
#define CAN_EQ2_MEMORYSECTIONSINDEXOFMAILBOX                          
#define CAN_EQ2_MEMORYSECTIONSTARTOFMEMORYSECTIONINFO                 
#define CAN_EQ2_HWHANDLEOFMEMORYSECTIONOBJECTS                        
#define CAN_EQ2_MAILBOXELEMENTOFMEMORYSECTIONOBJECTS                  
#define CAN_EQ2_MAILBOXHANDLEOFMEMORYSECTIONOBJECTS                   
#define CAN_EQ2_ISRSTATUSIDOFOSISRID                                  
#define CAN_EQ2_ISRTXIDOFOSISRID                                      
#define CAN_EQ2_ISRWAKEUPIDOFOSISRID                                  
#define CAN_EQ2_CONTROLLEROFRXFIFODATA                                
#define CAN_EQ2_FIFODEPTHOFRXFIFODATA                                 
#define CAN_EQ2_FILTERSTARTINDEXOFRXFIFODATA                          
#define CAN_EQ2_FILTERSTOPINDEXOFRXFIFODATA                           
#define CAN_EQ2_WAKEUPSOURCEREF                                       
#define CAN_EQ2_ACTIVESENDOBJECTOFPCCONFIG                            Can_ActiveSendObject
#define CAN_EQ2_CANIFCHANNELIDOFPCCONFIG                              Can_CanIfChannelId
#define CAN_EQ2_CHANNELDATAOFPCCONFIG                                 Can_ChannelData
#define CAN_EQ2_CONTROLLERCONFIGOFPCCONFIG                            Can_ControllerConfig
#define CAN_EQ2_CONTROLLERDATAOFPCCONFIG                              Can_ControllerData
#define CAN_EQ2_INITFILTERRULESOFPCCONFIG                             Can_InitFilterRules
#define CAN_EQ2_INITOBJECTBAUDRATEOFPCCONFIG                          Can_InitObjectBaudrate
#define CAN_EQ2_INITOBJECTBITTIMINGDATAOFPCCONFIG                     Can_InitObjectBitTimingData
#define CAN_EQ2_INITOBJECTBITTIMINGOFPCCONFIG                         Can_InitObjectBitTiming
#define CAN_EQ2_INITOBJECTCANFDCONFIGOFPCCONFIG                       Can_InitObjectCanFdConfig
#define CAN_EQ2_INITOBJECTSTARTINDEXOFPCCONFIG                        Can_InitObjectStartIndex
#define CAN_EQ2_MAILBOXOFPCCONFIG                                     Can_Mailbox
#define CAN_EQ2_MEMORYSECTIONINFOOFPCCONFIG                           Can_MemorySectionInfo
#define CAN_EQ2_MEMORYSECTIONOBJECTSOFPCCONFIG                        Can_MemorySectionObjects
#define CAN_EQ2_OSISRIDOFPCCONFIG                                     Can_OsIsrId
#define CAN_EQ2_RXFIFODATAOFPCCONFIG                                  Can_RxFifoData
#define CAN_EQ2_WAKEUPSOURCEREFOFPCCONFIG                             Can_WakeupSourceRef
/** 
  \}
*/ 

/** 
  \defgroup  CanPCSymbolicInitializationPointers  Can Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define Can_Config_Ptr                                                NULL_PTR  /**< symbolic identifier which shall be used to initialize 'Can' */
/** 
  \}
*/ 

/** 
  \defgroup  CanPCInitializationSymbols  Can Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define Can_Config                                                    NULL_PTR  /**< symbolic identifier which could be used to initialize 'Can */
/** 
  \}
*/ 

/** 
  \defgroup  CanPCGeneral  Can General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define CAN_CHECK_INIT_POINTER                                        STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define CAN_FINAL_MAGIC_NUMBER                                        0x501Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of Can */
#define CAN_INDIVIDUAL_POSTBUILD                                      STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'Can' is not configured to be postbuild capable. */
#define CAN_INIT_DATA                                                 CAN_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define CAN_INIT_DATA_HASH_CODE                                       -1893185136  /**< the precompile constant to validate the initialization structure at initialization time of Can with a hashcode. The seed value is '0x501Eu' */
#define CAN_USE_ECUM_BSW_ERROR_HOOK                                   STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define CAN_USE_INIT_POINTER                                          STD_OFF  /**< STD_ON if the init pointer Can shall be used. */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanLTDataSwitches  Can Data Switches  (LINK)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CAN_LTCONFIG                                                  STD_OFF  /**< Deactivateable: 'Can_LTConfig' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanPBDataSwitches  Can Data Switches  (POST_BUILD)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CAN_PBCONFIG                                                  STD_OFF  /**< Deactivateable: 'Can_PBConfig' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define CAN_LTCONFIGIDXOFPBCONFIG                                     STD_OFF  /**< Deactivateable: 'Can_PBConfig.LTConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define CAN_PCCONFIGIDXOFPBCONFIG                                     STD_OFF  /**< Deactivateable: 'Can_PBConfig.PCConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
/** 
  \}
*/ 



/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanPCGetConstantDuplicatedRootDataMacros  Can Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define Can_GetActiveSendObjectOfPCConfig()                           Can_ActiveSendObject  /**< the pointer to Can_ActiveSendObject */
#define Can_GetBaseDll_GeneratorVersionOfPCConfig()                   0x0103u
#define Can_GetCanIfChannelIdOfPCConfig()                             Can_CanIfChannelId  /**< the pointer to Can_CanIfChannelId */
#define Can_GetChannelDataOfPCConfig()                                Can_ChannelData  /**< the pointer to Can_ChannelData */
#define Can_GetControllerConfigOfPCConfig()                           Can_ControllerConfig  /**< the pointer to Can_ControllerConfig */
#define Can_GetControllerDataOfPCConfig()                             Can_ControllerData  /**< the pointer to Can_ControllerData */
#define Can_GetInitFilterRulesOfPCConfig()                            Can_InitFilterRules  /**< the pointer to Can_InitFilterRules */
#define Can_GetInitObjectBaudrateOfPCConfig()                         Can_InitObjectBaudrate  /**< the pointer to Can_InitObjectBaudrate */
#define Can_GetInitObjectBitTimingDataOfPCConfig()                    Can_InitObjectBitTimingData  /**< the pointer to Can_InitObjectBitTimingData */
#define Can_GetInitObjectBitTimingOfPCConfig()                        Can_InitObjectBitTiming  /**< the pointer to Can_InitObjectBitTiming */
#define Can_GetInitObjectCanFdConfigOfPCConfig()                      Can_InitObjectCanFdConfig  /**< the pointer to Can_InitObjectCanFdConfig */
#define Can_GetInitObjectStartIndexOfPCConfig()                       Can_InitObjectStartIndex  /**< the pointer to Can_InitObjectStartIndex */
#define Can_GetMailboxOfPCConfig()                                    Can_Mailbox  /**< the pointer to Can_Mailbox */
#define Can_GetMemorySectionInfoOfPCConfig()                          Can_MemorySectionInfo  /**< the pointer to Can_MemorySectionInfo */
#define Can_GetMemorySectionObjectsOfPCConfig()                       Can_MemorySectionObjects  /**< the pointer to Can_MemorySectionObjects */
#define Can_GetOsIsrIdOfPCConfig()                                    Can_OsIsrId  /**< the pointer to Can_OsIsrId */
#define Can_GetPlatformDll_GeneratorVersionOfPCConfig()               0x0302u
#define Can_GetRxFifoDataOfPCConfig()                                 Can_RxFifoData  /**< the pointer to Can_RxFifoData */
#define Can_GetSizeOfActiveSendObjectOfPCConfig()                     1u  /**< the number of accomplishable value elements in Can_ActiveSendObject */
#define Can_GetSizeOfCanIfChannelIdOfPCConfig()                       1u  /**< the number of accomplishable value elements in Can_CanIfChannelId */
#define Can_GetSizeOfChannelDataOfPCConfig()                          1u  /**< the number of accomplishable value elements in Can_ChannelData */
#define Can_GetSizeOfControllerConfigOfPCConfig()                     1u  /**< the number of accomplishable value elements in Can_ControllerConfig */
#define Can_GetSizeOfInitFilterRulesOfPCConfig()                      1u  /**< the number of accomplishable value elements in Can_InitFilterRules */
#define Can_GetSizeOfInitObjectBaudrateOfPCConfig()                   1u  /**< the number of accomplishable value elements in Can_InitObjectBaudrate */
#define Can_GetSizeOfInitObjectBitTimingDataOfPCConfig()              1u  /**< the number of accomplishable value elements in Can_InitObjectBitTimingData */
#define Can_GetSizeOfInitObjectBitTimingOfPCConfig()                  1u  /**< the number of accomplishable value elements in Can_InitObjectBitTiming */
#define Can_GetSizeOfInitObjectCanFdConfigOfPCConfig()                1u  /**< the number of accomplishable value elements in Can_InitObjectCanFdConfig */
#define Can_GetSizeOfInitObjectStartIndexOfPCConfig()                 2u  /**< the number of accomplishable value elements in Can_InitObjectStartIndex */
#define Can_GetSizeOfMailboxOfPCConfig()                              2u  /**< the number of accomplishable value elements in Can_Mailbox */
#define Can_GetSizeOfMemorySectionInfoOfPCConfig()                    1u  /**< the number of accomplishable value elements in Can_MemorySectionInfo */
#define Can_GetSizeOfMemorySectionObjectsOfPCConfig()                 32u  /**< the number of accomplishable value elements in Can_MemorySectionObjects */
#define Can_GetSizeOfOsIsrIdOfPCConfig()                              1u  /**< the number of accomplishable value elements in Can_OsIsrId */
#define Can_GetSizeOfRxFifoDataOfPCConfig()                           1u  /**< the number of accomplishable value elements in Can_RxFifoData */
#define Can_GetSizeOfWakeupSourceRefOfPCConfig()                      1u  /**< the number of accomplishable value elements in Can_WakeupSourceRef */
#define Can_GetWakeupSourceRefOfPCConfig()                            Can_WakeupSourceRef  /**< the pointer to Can_WakeupSourceRef */
/** 
  \}
*/ 

/** 
  \defgroup  CanPCGetDuplicatedRootDataMacros  Can Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define Can_GetSizeOfControllerDataOfPCConfig()                       Can_GetSizeOfControllerConfigOfPCConfig()  /**< the number of accomplishable value elements in Can_ControllerData */
/** 
  \}
*/ 

/** 
  \defgroup  CanPCGetDataMacros  Can Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define Can_GetPduOfActiveSendObject(Index)                           (Can_GetActiveSendObjectOfPCConfig()[(Index)].PduOfActiveSendObject)
#define Can_GetStateOfActiveSendObject(Index)                         (Can_GetActiveSendObjectOfPCConfig()[(Index)].StateOfActiveSendObject)
#define Can_GetCanIfChannelId(Index)                                  (Can_GetCanIfChannelIdOfPCConfig()[(Index)])
#define Can_GetFifoProcCountOfChannelData(Index)                      (Can_GetChannelDataOfPCConfig()[(Index)].FifoProcCountOfChannelData)
#define Can_GetFrStartIndexOfChannelData(Index)                       (Can_GetChannelDataOfPCConfig()[(Index)].FrStartIndexOfChannelData)
#define Can_GetFrTotalCountOfChannelData(Index)                       (Can_GetChannelDataOfPCConfig()[(Index)].FrTotalCountOfChannelData)
#define Can_GetRxBcMaskOfChannelData(Index)                           (Can_GetChannelDataOfPCConfig()[(Index)].RxBcMaskOfChannelData)
#define Can_GetRxBcStartIndexOfChannelData(Index)                     (Can_GetChannelDataOfPCConfig()[(Index)].RxBcStartIndexOfChannelData)
#define Can_GetRxBcStopIndexOfChannelData(Index)                      (Can_GetChannelDataOfPCConfig()[(Index)].RxBcStopIndexOfChannelData)
#define Can_GetTxIntMaskOfChannelData(Index)                          (Can_GetChannelDataOfPCConfig()[(Index)].TxIntMaskOfChannelData)
#define Can_GetCanControllerDefaultBaudrateIdxOfControllerConfig(Index) (Can_GetControllerConfigOfPCConfig()[(Index)].CanControllerDefaultBaudrateIdxOfControllerConfig)
#define Can_GetCanControllerDefaultBaudrateOfControllerConfig(Index)  (Can_GetControllerConfigOfPCConfig()[(Index)].CanControllerDefaultBaudrateOfControllerConfig)
#define Can_GetMailboxRxBasicEndIdxOfControllerConfig(Index)          (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxRxBasicEndIdxOfControllerConfig)
#define Can_GetMailboxRxBasicLengthOfControllerConfig(Index)          (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxRxBasicLengthOfControllerConfig)
#define Can_GetMailboxRxBasicStartIdxOfControllerConfig(Index)        (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxRxBasicStartIdxOfControllerConfig)
#define Can_GetMailboxTxBasicEndIdxOfControllerConfig(Index)          (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxTxBasicEndIdxOfControllerConfig)
#define Can_GetMailboxTxBasicLengthOfControllerConfig(Index)          (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxTxBasicLengthOfControllerConfig)
#define Can_GetMailboxTxBasicStartIdxOfControllerConfig(Index)        (Can_GetControllerConfigOfPCConfig()[(Index)].MailboxTxBasicStartIdxOfControllerConfig)
#define Can_GetRxBasicHwStartOfControllerConfig(Index)                (Can_GetControllerConfigOfPCConfig()[(Index)].RxBasicHwStartOfControllerConfig)
#define Can_GetRxBasicHwStopOfControllerConfig(Index)                 (Can_GetControllerConfigOfPCConfig()[(Index)].RxBasicHwStopOfControllerConfig)
#define Can_GetRxFullHwStartOfControllerConfig(Index)                 (Can_GetControllerConfigOfPCConfig()[(Index)].RxFullHwStartOfControllerConfig)
#define Can_GetRxFullHwStopOfControllerConfig(Index)                  (Can_GetControllerConfigOfPCConfig()[(Index)].RxFullHwStopOfControllerConfig)
#define Can_GetTxBasicHwStartOfControllerConfig(Index)                (Can_GetControllerConfigOfPCConfig()[(Index)].TxBasicHwStartOfControllerConfig)
#define Can_GetTxBasicHwStopOfControllerConfig(Index)                 (Can_GetControllerConfigOfPCConfig()[(Index)].TxBasicHwStopOfControllerConfig)
#define Can_GetTxFullHwStartOfControllerConfig(Index)                 (Can_GetControllerConfigOfPCConfig()[(Index)].TxFullHwStartOfControllerConfig)
#define Can_GetTxFullHwStopOfControllerConfig(Index)                  (Can_GetControllerConfigOfPCConfig()[(Index)].TxFullHwStopOfControllerConfig)
#define Can_GetUnusedHwStartOfControllerConfig(Index)                 (Can_GetControllerConfigOfPCConfig()[(Index)].UnusedHwStartOfControllerConfig)
#define Can_GetUnusedHwStopOfControllerConfig(Index)                  (Can_GetControllerConfigOfPCConfig()[(Index)].UnusedHwStopOfControllerConfig)
#define Can_GetBusOffCounterOfControllerData(Index)                   (Can_GetControllerDataOfPCConfig()[(Index)].BusOffCounterOfControllerData)
#define Can_GetBusOffTransitionRequestOfControllerData(Index)         (Can_GetControllerDataOfPCConfig()[(Index)].BusOffTransitionRequestOfControllerData)
#define Can_GetCanInterruptCounterOfControllerData(Index)             (Can_GetControllerDataOfPCConfig()[(Index)].CanInterruptCounterOfControllerData)
#define Can_GetCanInterruptOldStatusOfControllerData(Index)           (Can_GetControllerDataOfPCConfig()[(Index)].CanInterruptOldStatusOfControllerData)
#define Can_IsIsBusOffOfControllerData(Index)                         ((Can_GetControllerDataOfPCConfig()[(Index)].IsBusOffOfControllerData) != FALSE)
#define Can_IsIsWakeupOfControllerData(Index)                         ((Can_GetControllerDataOfPCConfig()[(Index)].IsWakeupOfControllerData) != FALSE)
#define Can_GetLastInitObjectOfControllerData(Index)                  (Can_GetControllerDataOfPCConfig()[(Index)].LastInitObjectOfControllerData)
#define Can_GetLogStatusOfControllerData(Index)                       (Can_GetControllerDataOfPCConfig()[(Index)].LogStatusOfControllerData)
#define Can_GetLoopTimeoutOfControllerData(Index)                     (Can_GetControllerDataOfPCConfig()[(Index)].LoopTimeoutOfControllerData)
#define Can_GetModeTransitionRequestOfControllerData(Index)           (Can_GetControllerDataOfPCConfig()[(Index)].ModeTransitionRequestOfControllerData)
#define Can_GetRamCheckTransitionRequestOfControllerData(Index)       (Can_GetControllerDataOfPCConfig()[(Index)].RamCheckTransitionRequestOfControllerData)
#define Can_GetRxTmpBufOfControllerData(Index)                        (Can_GetControllerDataOfPCConfig()[(Index)].RxTmpBufOfControllerData)
#define Can_GetCodeOfInitFilterRules(Index)                           (Can_GetInitFilterRulesOfPCConfig()[(Index)].CodeOfInitFilterRules)
#define Can_GetMaskOfInitFilterRules(Index)                           (Can_GetInitFilterRulesOfPCConfig()[(Index)].MaskOfInitFilterRules)
#define Can_GetInitObjectBaudrate(Index)                              (Can_GetInitObjectBaudrateOfPCConfig()[(Index)])
#define Can_GetInitObjectBitTiming(Index)                             (Can_GetInitObjectBitTimingOfPCConfig()[(Index)])
#define Can_GetInitObjectBitTimingData(Index)                         (Can_GetInitObjectBitTimingDataOfPCConfig()[(Index)])
#define Can_GetInitObjectCanFdConfig(Index)                           (Can_GetInitObjectCanFdConfigOfPCConfig()[(Index)])
#define Can_GetInitObjectStartIndex(Index)                            (Can_GetInitObjectStartIndexOfPCConfig()[(Index)])
#define Can_GetActiveSendObjectOfMailbox(Index)                       (Can_GetMailboxOfPCConfig()[(Index)].ActiveSendObjectOfMailbox)
#define Can_GetControllerConfigIdxOfMailbox(Index)                    (Can_GetMailboxOfPCConfig()[(Index)].ControllerConfigIdxOfMailbox)
#define Can_GetHwHandleOfMailbox(Index)                               (Can_GetMailboxOfPCConfig()[(Index)].HwHandleOfMailbox)
#define Can_GetIDValueOfMailbox(Index)                                (Can_GetMailboxOfPCConfig()[(Index)].IDValueOfMailbox)
#define Can_GetMailboxSizeOfMailbox(Index)                            (Can_GetMailboxOfPCConfig()[(Index)].MailboxSizeOfMailbox)
#define Can_GetMailboxTypeOfMailbox(Index)                            (Can_GetMailboxOfPCConfig()[(Index)].MailboxTypeOfMailbox)
#define Can_GetMaxDataLenOfMailbox(Index)                             (Can_GetMailboxOfPCConfig()[(Index)].MaxDataLenOfMailbox)
#define Can_GetMemorySectionsIndexOfMailbox(Index)                    (Can_GetMailboxOfPCConfig()[(Index)].MemorySectionsIndexOfMailbox)
#define Can_GetMemorySectionStartOfMemorySectionInfo(Index)           (Can_GetMemorySectionInfoOfPCConfig()[(Index)].MemorySectionStartOfMemorySectionInfo)
#define Can_GetHwHandleOfMemorySectionObjects(Index)                  (Can_GetMemorySectionObjectsOfPCConfig()[(Index)].HwHandleOfMemorySectionObjects)
#define Can_GetMailboxElementOfMemorySectionObjects(Index)            (Can_GetMemorySectionObjectsOfPCConfig()[(Index)].MailboxElementOfMemorySectionObjects)
#define Can_GetMailboxHandleOfMemorySectionObjects(Index)             (Can_GetMemorySectionObjectsOfPCConfig()[(Index)].MailboxHandleOfMemorySectionObjects)
#define Can_GetIsrStatusIdOfOsIsrId(Index)                            (Can_GetOsIsrIdOfPCConfig()[(Index)].IsrStatusIdOfOsIsrId)
#define Can_GetIsrTxIdOfOsIsrId(Index)                                (Can_GetOsIsrIdOfPCConfig()[(Index)].IsrTxIdOfOsIsrId)
#define Can_GetIsrWakeupIdOfOsIsrId(Index)                            (Can_GetOsIsrIdOfPCConfig()[(Index)].IsrWakeupIdOfOsIsrId)
#define Can_GetControllerOfRxFifoData(Index)                          (Can_GetRxFifoDataOfPCConfig()[(Index)].ControllerOfRxFifoData)
#define Can_GetFifoDepthOfRxFifoData(Index)                           (Can_GetRxFifoDataOfPCConfig()[(Index)].FifoDepthOfRxFifoData)
#define Can_GetFilterStartIndexOfRxFifoData(Index)                    (Can_GetRxFifoDataOfPCConfig()[(Index)].FilterStartIndexOfRxFifoData)
#define Can_GetFilterStopIndexOfRxFifoData(Index)                     (Can_GetRxFifoDataOfPCConfig()[(Index)].FilterStopIndexOfRxFifoData)
#define Can_GetWakeupSourceRef(Index)                                 ((EcuM_WakeupSourceType)Can_GetWakeupSourceRefOfPCConfig()[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  CanPCGetDeduplicatedDataMacros  Can Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define Can_GetBaseDll_GeneratorVersion()                             Can_GetBaseDll_GeneratorVersionOfPCConfig()
#define Can_IsMailboxRxBasicUsedOfControllerConfig(Index)             (((boolean)(Can_GetMailboxRxBasicLengthOfControllerConfig(Index) != 0u)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Can_Mailbox */
#define Can_IsMailboxTxBasicUsedOfControllerConfig(Index)             (((boolean)(Can_GetMailboxTxBasicLengthOfControllerConfig(Index) != 0u)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Can_Mailbox */
#define Can_GetPlatformDll_GeneratorVersion()                         Can_GetPlatformDll_GeneratorVersionOfPCConfig()
#define Can_GetSizeOfActiveSendObject()                               Can_GetSizeOfActiveSendObjectOfPCConfig()
#define Can_GetSizeOfCanIfChannelId()                                 Can_GetSizeOfCanIfChannelIdOfPCConfig()
#define Can_GetSizeOfChannelData()                                    Can_GetSizeOfChannelDataOfPCConfig()
#define Can_GetSizeOfControllerConfig()                               Can_GetSizeOfControllerConfigOfPCConfig()
#define Can_GetSizeOfControllerData()                                 Can_GetSizeOfControllerDataOfPCConfig()
#define Can_GetSizeOfInitFilterRules()                                Can_GetSizeOfInitFilterRulesOfPCConfig()
#define Can_GetSizeOfInitObjectBaudrate()                             Can_GetSizeOfInitObjectBaudrateOfPCConfig()
#define Can_GetSizeOfInitObjectBitTiming()                            Can_GetSizeOfInitObjectBitTimingOfPCConfig()
#define Can_GetSizeOfInitObjectBitTimingData()                        Can_GetSizeOfInitObjectBitTimingDataOfPCConfig()
#define Can_GetSizeOfInitObjectCanFdConfig()                          Can_GetSizeOfInitObjectCanFdConfigOfPCConfig()
#define Can_GetSizeOfInitObjectStartIndex()                           Can_GetSizeOfInitObjectStartIndexOfPCConfig()
#define Can_GetSizeOfMailbox()                                        Can_GetSizeOfMailboxOfPCConfig()
#define Can_GetSizeOfMemorySectionInfo()                              Can_GetSizeOfMemorySectionInfoOfPCConfig()
#define Can_GetSizeOfMemorySectionObjects()                           Can_GetSizeOfMemorySectionObjectsOfPCConfig()
#define Can_GetSizeOfOsIsrId()                                        Can_GetSizeOfOsIsrIdOfPCConfig()
#define Can_GetSizeOfRxFifoData()                                     Can_GetSizeOfRxFifoDataOfPCConfig()
#define Can_GetSizeOfWakeupSourceRef()                                Can_GetSizeOfWakeupSourceRefOfPCConfig()
/** 
  \}
*/ 

/** 
  \defgroup  CanPCSetDataMacros  Can Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define Can_SetPduOfActiveSendObject(Index, Value)                    Can_GetActiveSendObjectOfPCConfig()[(Index)].PduOfActiveSendObject = (Value)
#define Can_SetStateOfActiveSendObject(Index, Value)                  Can_GetActiveSendObjectOfPCConfig()[(Index)].StateOfActiveSendObject = (Value)
#define Can_SetBusOffCounterOfControllerData(Index, Value)            Can_GetControllerDataOfPCConfig()[(Index)].BusOffCounterOfControllerData = (Value)
#define Can_SetBusOffTransitionRequestOfControllerData(Index, Value)  Can_GetControllerDataOfPCConfig()[(Index)].BusOffTransitionRequestOfControllerData = (Value)
#define Can_SetCanInterruptCounterOfControllerData(Index, Value)      Can_GetControllerDataOfPCConfig()[(Index)].CanInterruptCounterOfControllerData = (Value)
#define Can_SetCanInterruptOldStatusOfControllerData(Index, Value)    Can_GetControllerDataOfPCConfig()[(Index)].CanInterruptOldStatusOfControllerData = (Value)
#define Can_SetIsBusOffOfControllerData(Index, Value)                 Can_GetControllerDataOfPCConfig()[(Index)].IsBusOffOfControllerData = (Value)
#define Can_SetIsWakeupOfControllerData(Index, Value)                 Can_GetControllerDataOfPCConfig()[(Index)].IsWakeupOfControllerData = (Value)
#define Can_SetLastInitObjectOfControllerData(Index, Value)           Can_GetControllerDataOfPCConfig()[(Index)].LastInitObjectOfControllerData = (Value)
#define Can_SetLogStatusOfControllerData(Index, Value)                Can_GetControllerDataOfPCConfig()[(Index)].LogStatusOfControllerData = (Value)
#define Can_SetLoopTimeoutOfControllerData(Index, Value)              Can_GetControllerDataOfPCConfig()[(Index)].LoopTimeoutOfControllerData = (Value)
#define Can_SetModeTransitionRequestOfControllerData(Index, Value)    Can_GetControllerDataOfPCConfig()[(Index)].ModeTransitionRequestOfControllerData = (Value)
#define Can_SetRamCheckTransitionRequestOfControllerData(Index, Value) Can_GetControllerDataOfPCConfig()[(Index)].RamCheckTransitionRequestOfControllerData = (Value)
#define Can_SetRxTmpBufOfControllerData(Index, Value)                 Can_GetControllerDataOfPCConfig()[(Index)].RxTmpBufOfControllerData = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  CanPCHasMacros  Can Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define Can_HasActiveSendObject()                                     (TRUE != FALSE)
#define Can_HasPduOfActiveSendObject()                                (TRUE != FALSE)
#define Can_HasStateOfActiveSendObject()                              (TRUE != FALSE)
#define Can_HasBaseDll_GeneratorVersion()                             (TRUE != FALSE)
#define Can_HasCanIfChannelId()                                       (TRUE != FALSE)
#define Can_HasChannelData()                                          (TRUE != FALSE)
#define Can_HasFifoProcCountOfChannelData()                           (TRUE != FALSE)
#define Can_HasFrStartIndexOfChannelData()                            (TRUE != FALSE)
#define Can_HasFrTotalCountOfChannelData()                            (TRUE != FALSE)
#define Can_HasRxBcMaskOfChannelData()                                (TRUE != FALSE)
#define Can_HasRxBcStartIndexOfChannelData()                          (TRUE != FALSE)
#define Can_HasRxBcStopIndexOfChannelData()                           (TRUE != FALSE)
#define Can_HasTxIntMaskOfChannelData()                               (TRUE != FALSE)
#define Can_HasControllerConfig()                                     (TRUE != FALSE)
#define Can_HasCanControllerDefaultBaudrateIdxOfControllerConfig()    (TRUE != FALSE)
#define Can_HasCanControllerDefaultBaudrateOfControllerConfig()       (TRUE != FALSE)
#define Can_HasMailboxRxBasicEndIdxOfControllerConfig()               (TRUE != FALSE)
#define Can_HasMailboxRxBasicLengthOfControllerConfig()               (TRUE != FALSE)
#define Can_HasMailboxRxBasicStartIdxOfControllerConfig()             (TRUE != FALSE)
#define Can_HasMailboxRxBasicUsedOfControllerConfig()                 (TRUE != FALSE)
#define Can_HasMailboxTxBasicEndIdxOfControllerConfig()               (TRUE != FALSE)
#define Can_HasMailboxTxBasicLengthOfControllerConfig()               (TRUE != FALSE)
#define Can_HasMailboxTxBasicStartIdxOfControllerConfig()             (TRUE != FALSE)
#define Can_HasMailboxTxBasicUsedOfControllerConfig()                 (TRUE != FALSE)
#define Can_HasRxBasicHwStartOfControllerConfig()                     (TRUE != FALSE)
#define Can_HasRxBasicHwStopOfControllerConfig()                      (TRUE != FALSE)
#define Can_HasRxFullHwStartOfControllerConfig()                      (TRUE != FALSE)
#define Can_HasRxFullHwStopOfControllerConfig()                       (TRUE != FALSE)
#define Can_HasTxBasicHwStartOfControllerConfig()                     (TRUE != FALSE)
#define Can_HasTxBasicHwStopOfControllerConfig()                      (TRUE != FALSE)
#define Can_HasTxFullHwStartOfControllerConfig()                      (TRUE != FALSE)
#define Can_HasTxFullHwStopOfControllerConfig()                       (TRUE != FALSE)
#define Can_HasUnusedHwStartOfControllerConfig()                      (TRUE != FALSE)
#define Can_HasUnusedHwStopOfControllerConfig()                       (TRUE != FALSE)
#define Can_HasControllerData()                                       (TRUE != FALSE)
#define Can_HasBusOffCounterOfControllerData()                        (TRUE != FALSE)
#define Can_HasBusOffTransitionRequestOfControllerData()              (TRUE != FALSE)
#define Can_HasCanInterruptCounterOfControllerData()                  (TRUE != FALSE)
#define Can_HasCanInterruptOldStatusOfControllerData()                (TRUE != FALSE)
#define Can_HasIsBusOffOfControllerData()                             (TRUE != FALSE)
#define Can_HasIsWakeupOfControllerData()                             (TRUE != FALSE)
#define Can_HasLastInitObjectOfControllerData()                       (TRUE != FALSE)
#define Can_HasLogStatusOfControllerData()                            (TRUE != FALSE)
#define Can_HasLoopTimeoutOfControllerData()                          (TRUE != FALSE)
#define Can_HasModeTransitionRequestOfControllerData()                (TRUE != FALSE)
#define Can_HasRamCheckTransitionRequestOfControllerData()            (TRUE != FALSE)
#define Can_HasRxTmpBufOfControllerData()                             (TRUE != FALSE)
#define Can_HasInitFilterRules()                                      (TRUE != FALSE)
#define Can_HasCodeOfInitFilterRules()                                (TRUE != FALSE)
#define Can_HasMaskOfInitFilterRules()                                (TRUE != FALSE)
#define Can_HasInitObjectBaudrate()                                   (TRUE != FALSE)
#define Can_HasInitObjectBitTiming()                                  (TRUE != FALSE)
#define Can_HasInitObjectBitTimingData()                              (TRUE != FALSE)
#define Can_HasInitObjectCanFdConfig()                                (TRUE != FALSE)
#define Can_HasInitObjectStartIndex()                                 (TRUE != FALSE)
#define Can_HasMailbox()                                              (TRUE != FALSE)
#define Can_HasActiveSendObjectOfMailbox()                            (TRUE != FALSE)
#define Can_HasControllerConfigIdxOfMailbox()                         (TRUE != FALSE)
#define Can_HasHwHandleOfMailbox()                                    (TRUE != FALSE)
#define Can_HasIDValueOfMailbox()                                     (TRUE != FALSE)
#define Can_HasMailboxSizeOfMailbox()                                 (TRUE != FALSE)
#define Can_HasMailboxTypeOfMailbox()                                 (TRUE != FALSE)
#define Can_HasMaxDataLenOfMailbox()                                  (TRUE != FALSE)
#define Can_HasMemorySectionsIndexOfMailbox()                         (TRUE != FALSE)
#define Can_HasMemorySectionInfo()                                    (TRUE != FALSE)
#define Can_HasMemorySectionStartOfMemorySectionInfo()                (TRUE != FALSE)
#define Can_HasMemorySectionObjects()                                 (TRUE != FALSE)
#define Can_HasHwHandleOfMemorySectionObjects()                       (TRUE != FALSE)
#define Can_HasMailboxElementOfMemorySectionObjects()                 (TRUE != FALSE)
#define Can_HasMailboxHandleOfMemorySectionObjects()                  (TRUE != FALSE)
#define Can_HasOsIsrId()                                              (TRUE != FALSE)
#define Can_HasIsrStatusIdOfOsIsrId()                                 (TRUE != FALSE)
#define Can_HasIsrTxIdOfOsIsrId()                                     (TRUE != FALSE)
#define Can_HasIsrWakeupIdOfOsIsrId()                                 (TRUE != FALSE)
#define Can_HasPlatformDll_GeneratorVersion()                         (TRUE != FALSE)
#define Can_HasRxFifoData()                                           (TRUE != FALSE)
#define Can_HasControllerOfRxFifoData()                               (TRUE != FALSE)
#define Can_HasFifoDepthOfRxFifoData()                                (TRUE != FALSE)
#define Can_HasFilterStartIndexOfRxFifoData()                         (TRUE != FALSE)
#define Can_HasFilterStopIndexOfRxFifoData()                          (TRUE != FALSE)
#define Can_HasSizeOfActiveSendObject()                               (TRUE != FALSE)
#define Can_HasSizeOfCanIfChannelId()                                 (TRUE != FALSE)
#define Can_HasSizeOfChannelData()                                    (TRUE != FALSE)
#define Can_HasSizeOfControllerConfig()                               (TRUE != FALSE)
#define Can_HasSizeOfControllerData()                                 (TRUE != FALSE)
#define Can_HasSizeOfInitFilterRules()                                (TRUE != FALSE)
#define Can_HasSizeOfInitObjectBaudrate()                             (TRUE != FALSE)
#define Can_HasSizeOfInitObjectBitTiming()                            (TRUE != FALSE)
#define Can_HasSizeOfInitObjectBitTimingData()                        (TRUE != FALSE)
#define Can_HasSizeOfInitObjectCanFdConfig()                          (TRUE != FALSE)
#define Can_HasSizeOfInitObjectStartIndex()                           (TRUE != FALSE)
#define Can_HasSizeOfMailbox()                                        (TRUE != FALSE)
#define Can_HasSizeOfMemorySectionInfo()                              (TRUE != FALSE)
#define Can_HasSizeOfMemorySectionObjects()                           (TRUE != FALSE)
#define Can_HasSizeOfOsIsrId()                                        (TRUE != FALSE)
#define Can_HasSizeOfRxFifoData()                                     (TRUE != FALSE)
#define Can_HasSizeOfWakeupSourceRef()                                (TRUE != FALSE)
#define Can_HasWakeupSourceRef()                                      (TRUE != FALSE)
#define Can_HasPCConfig()                                             (TRUE != FALSE)
#define Can_HasActiveSendObjectOfPCConfig()                           (TRUE != FALSE)
#define Can_HasBaseDll_GeneratorVersionOfPCConfig()                   (TRUE != FALSE)
#define Can_HasCanIfChannelIdOfPCConfig()                             (TRUE != FALSE)
#define Can_HasChannelDataOfPCConfig()                                (TRUE != FALSE)
#define Can_HasControllerConfigOfPCConfig()                           (TRUE != FALSE)
#define Can_HasControllerDataOfPCConfig()                             (TRUE != FALSE)
#define Can_HasInitFilterRulesOfPCConfig()                            (TRUE != FALSE)
#define Can_HasInitObjectBaudrateOfPCConfig()                         (TRUE != FALSE)
#define Can_HasInitObjectBitTimingDataOfPCConfig()                    (TRUE != FALSE)
#define Can_HasInitObjectBitTimingOfPCConfig()                        (TRUE != FALSE)
#define Can_HasInitObjectCanFdConfigOfPCConfig()                      (TRUE != FALSE)
#define Can_HasInitObjectStartIndexOfPCConfig()                       (TRUE != FALSE)
#define Can_HasMailboxOfPCConfig()                                    (TRUE != FALSE)
#define Can_HasMemorySectionInfoOfPCConfig()                          (TRUE != FALSE)
#define Can_HasMemorySectionObjectsOfPCConfig()                       (TRUE != FALSE)
#define Can_HasOsIsrIdOfPCConfig()                                    (TRUE != FALSE)
#define Can_HasPlatformDll_GeneratorVersionOfPCConfig()               (TRUE != FALSE)
#define Can_HasRxFifoDataOfPCConfig()                                 (TRUE != FALSE)
#define Can_HasSizeOfActiveSendObjectOfPCConfig()                     (TRUE != FALSE)
#define Can_HasSizeOfCanIfChannelIdOfPCConfig()                       (TRUE != FALSE)
#define Can_HasSizeOfChannelDataOfPCConfig()                          (TRUE != FALSE)
#define Can_HasSizeOfControllerConfigOfPCConfig()                     (TRUE != FALSE)
#define Can_HasSizeOfControllerDataOfPCConfig()                       (TRUE != FALSE)
#define Can_HasSizeOfInitFilterRulesOfPCConfig()                      (TRUE != FALSE)
#define Can_HasSizeOfInitObjectBaudrateOfPCConfig()                   (TRUE != FALSE)
#define Can_HasSizeOfInitObjectBitTimingDataOfPCConfig()              (TRUE != FALSE)
#define Can_HasSizeOfInitObjectBitTimingOfPCConfig()                  (TRUE != FALSE)
#define Can_HasSizeOfInitObjectCanFdConfigOfPCConfig()                (TRUE != FALSE)
#define Can_HasSizeOfInitObjectStartIndexOfPCConfig()                 (TRUE != FALSE)
#define Can_HasSizeOfMailboxOfPCConfig()                              (TRUE != FALSE)
#define Can_HasSizeOfMemorySectionInfoOfPCConfig()                    (TRUE != FALSE)
#define Can_HasSizeOfMemorySectionObjectsOfPCConfig()                 (TRUE != FALSE)
#define Can_HasSizeOfOsIsrIdOfPCConfig()                              (TRUE != FALSE)
#define Can_HasSizeOfRxFifoDataOfPCConfig()                           (TRUE != FALSE)
#define Can_HasSizeOfWakeupSourceRefOfPCConfig()                      (TRUE != FALSE)
#define Can_HasWakeupSourceRefOfPCConfig()                            (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  CanPCIncrementDataMacros  Can Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define Can_IncPduOfActiveSendObject(Index)                           Can_GetPduOfActiveSendObject(Index)++
#define Can_IncStateOfActiveSendObject(Index)                         Can_GetStateOfActiveSendObject(Index)++
#define Can_IncBusOffCounterOfControllerData(Index)                   Can_GetBusOffCounterOfControllerData(Index)++
#define Can_IncBusOffTransitionRequestOfControllerData(Index)         Can_GetBusOffTransitionRequestOfControllerData(Index)++
#define Can_IncCanInterruptCounterOfControllerData(Index)             Can_GetCanInterruptCounterOfControllerData(Index)++
#define Can_IncCanInterruptOldStatusOfControllerData(Index)           Can_GetCanInterruptOldStatusOfControllerData(Index)++
#define Can_IncLastInitObjectOfControllerData(Index)                  Can_GetLastInitObjectOfControllerData(Index)++
#define Can_IncLogStatusOfControllerData(Index)                       Can_GetLogStatusOfControllerData(Index)++
#define Can_IncLoopTimeoutOfControllerData(Index)                     Can_GetLoopTimeoutOfControllerData(Index)++
#define Can_IncModeTransitionRequestOfControllerData(Index)           Can_GetModeTransitionRequestOfControllerData(Index)++
#define Can_IncRamCheckTransitionRequestOfControllerData(Index)       Can_GetRamCheckTransitionRequestOfControllerData(Index)++
#define Can_IncRxTmpBufOfControllerData(Index)                        Can_GetRxTmpBufOfControllerData(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  CanPCDecrementDataMacros  Can Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define Can_DecPduOfActiveSendObject(Index)                           Can_GetPduOfActiveSendObject(Index)--
#define Can_DecStateOfActiveSendObject(Index)                         Can_GetStateOfActiveSendObject(Index)--
#define Can_DecBusOffCounterOfControllerData(Index)                   Can_GetBusOffCounterOfControllerData(Index)--
#define Can_DecBusOffTransitionRequestOfControllerData(Index)         Can_GetBusOffTransitionRequestOfControllerData(Index)--
#define Can_DecCanInterruptCounterOfControllerData(Index)             Can_GetCanInterruptCounterOfControllerData(Index)--
#define Can_DecCanInterruptOldStatusOfControllerData(Index)           Can_GetCanInterruptOldStatusOfControllerData(Index)--
#define Can_DecLastInitObjectOfControllerData(Index)                  Can_GetLastInitObjectOfControllerData(Index)--
#define Can_DecLogStatusOfControllerData(Index)                       Can_GetLogStatusOfControllerData(Index)--
#define Can_DecLoopTimeoutOfControllerData(Index)                     Can_GetLoopTimeoutOfControllerData(Index)--
#define Can_DecModeTransitionRequestOfControllerData(Index)           Can_GetModeTransitionRequestOfControllerData(Index)--
#define Can_DecRamCheckTransitionRequestOfControllerData(Index)       Can_GetRamCheckTransitionRequestOfControllerData(Index)--
#define Can_DecRxTmpBufOfControllerData(Index)                        Can_GetRxTmpBufOfControllerData(Index)--
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  CanPCIterableTypes  Can Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate Can_ActiveSendObject */
typedef uint8_least Can_ActiveSendObjectIterType;

/**   \brief  type used to iterate Can_CanIfChannelId */
typedef uint8_least Can_CanIfChannelIdIterType;

/**   \brief  type used to iterate Can_ChannelData */
typedef uint8_least Can_ChannelDataIterType;

/**   \brief  type used to iterate Can_ControllerConfig */
typedef uint8_least Can_ControllerConfigIterType;

/**   \brief  type used to iterate Can_InitFilterRules */
typedef uint8_least Can_InitFilterRulesIterType;

/**   \brief  type used to iterate Can_InitObjectBaudrate */
typedef uint8_least Can_InitObjectBaudrateIterType;

/**   \brief  type used to iterate Can_InitObjectBitTiming */
typedef uint8_least Can_InitObjectBitTimingIterType;

/**   \brief  type used to iterate Can_InitObjectBitTimingData */
typedef uint8_least Can_InitObjectBitTimingDataIterType;

/**   \brief  type used to iterate Can_InitObjectCanFdConfig */
typedef uint8_least Can_InitObjectCanFdConfigIterType;

/**   \brief  type used to iterate Can_InitObjectStartIndex */
typedef uint8_least Can_InitObjectStartIndexIterType;

/**   \brief  type used to iterate Can_Mailbox */
typedef uint8_least Can_MailboxIterType;

/**   \brief  type used to iterate Can_MemorySectionInfo */
typedef uint8_least Can_MemorySectionInfoIterType;

/**   \brief  type used to iterate Can_MemorySectionObjects */
typedef uint8_least Can_MemorySectionObjectsIterType;

/**   \brief  type used to iterate Can_OsIsrId */
typedef uint8_least Can_OsIsrIdIterType;

/**   \brief  type used to iterate Can_RxFifoData */
typedef uint8_least Can_RxFifoDataIterType;

/**   \brief  type used to iterate Can_WakeupSourceRef */
typedef uint8_least Can_WakeupSourceRefIterType;

/** 
  \}
*/ 

/** 
  \defgroup  CanPCIterableTypesWithSizeRelations  Can Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate Can_ControllerData */
typedef Can_ControllerConfigIterType Can_ControllerDataIterType;

/** 
  \}
*/ 

/** 
  \defgroup  CanPCValueTypes  Can Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for Can_PduOfActiveSendObject */
typedef PduIdType Can_PduOfActiveSendObjectType;

/**   \brief  value based type definition for Can_StateOfActiveSendObject */
typedef uint16 Can_StateOfActiveSendObjectType;

/**   \brief  value based type definition for Can_BaseDll_GeneratorVersion */
typedef uint16 Can_BaseDll_GeneratorVersionType;

/**   \brief  value based type definition for Can_CanIfChannelId */
typedef uint8 Can_CanIfChannelIdType;

/**   \brief  value based type definition for Can_FifoProcCountOfChannelData */
typedef uint8 Can_FifoProcCountOfChannelDataType;

/**   \brief  value based type definition for Can_FrStartIndexOfChannelData */
typedef uint8 Can_FrStartIndexOfChannelDataType;

/**   \brief  value based type definition for Can_FrTotalCountOfChannelData */
typedef uint8 Can_FrTotalCountOfChannelDataType;

/**   \brief  value based type definition for Can_RxBcMaskOfChannelData */
typedef uint8 Can_RxBcMaskOfChannelDataType;

/**   \brief  value based type definition for Can_RxBcStartIndexOfChannelData */
typedef uint8 Can_RxBcStartIndexOfChannelDataType;

/**   \brief  value based type definition for Can_RxBcStopIndexOfChannelData */
typedef uint8 Can_RxBcStopIndexOfChannelDataType;

/**   \brief  value based type definition for Can_TxIntMaskOfChannelData */
typedef uint8 Can_TxIntMaskOfChannelDataType;

/**   \brief  value based type definition for Can_CanControllerDefaultBaudrateIdxOfControllerConfig */
typedef uint8 Can_CanControllerDefaultBaudrateIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_CanControllerDefaultBaudrateOfControllerConfig */
typedef uint16 Can_CanControllerDefaultBaudrateOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxRxBasicEndIdxOfControllerConfig */
typedef uint8 Can_MailboxRxBasicEndIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxRxBasicLengthOfControllerConfig */
typedef uint8 Can_MailboxRxBasicLengthOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxRxBasicStartIdxOfControllerConfig */
typedef uint8 Can_MailboxRxBasicStartIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxRxBasicUsedOfControllerConfig */
typedef boolean Can_MailboxRxBasicUsedOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxTxBasicEndIdxOfControllerConfig */
typedef uint8 Can_MailboxTxBasicEndIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxTxBasicLengthOfControllerConfig */
typedef uint8 Can_MailboxTxBasicLengthOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxTxBasicStartIdxOfControllerConfig */
typedef uint8 Can_MailboxTxBasicStartIdxOfControllerConfigType;

/**   \brief  value based type definition for Can_MailboxTxBasicUsedOfControllerConfig */
typedef boolean Can_MailboxTxBasicUsedOfControllerConfigType;

/**   \brief  value based type definition for Can_RxBasicHwStartOfControllerConfig */
typedef uint8 Can_RxBasicHwStartOfControllerConfigType;

/**   \brief  value based type definition for Can_RxBasicHwStopOfControllerConfig */
typedef uint8 Can_RxBasicHwStopOfControllerConfigType;

/**   \brief  value based type definition for Can_RxFullHwStartOfControllerConfig */
typedef uint8 Can_RxFullHwStartOfControllerConfigType;

/**   \brief  value based type definition for Can_RxFullHwStopOfControllerConfig */
typedef uint8 Can_RxFullHwStopOfControllerConfigType;

/**   \brief  value based type definition for Can_TxBasicHwStartOfControllerConfig */
typedef uint8 Can_TxBasicHwStartOfControllerConfigType;

/**   \brief  value based type definition for Can_TxBasicHwStopOfControllerConfig */
typedef uint8 Can_TxBasicHwStopOfControllerConfigType;

/**   \brief  value based type definition for Can_TxFullHwStartOfControllerConfig */
typedef uint8 Can_TxFullHwStartOfControllerConfigType;

/**   \brief  value based type definition for Can_TxFullHwStopOfControllerConfig */
typedef uint8 Can_TxFullHwStopOfControllerConfigType;

/**   \brief  value based type definition for Can_UnusedHwStartOfControllerConfig */
typedef uint8 Can_UnusedHwStartOfControllerConfigType;

/**   \brief  value based type definition for Can_UnusedHwStopOfControllerConfig */
typedef uint8 Can_UnusedHwStopOfControllerConfigType;

/**   \brief  value based type definition for Can_BusOffCounterOfControllerData */
typedef uint8 Can_BusOffCounterOfControllerDataType;

/**   \brief  value based type definition for Can_BusOffTransitionRequestOfControllerData */
typedef uint8 Can_BusOffTransitionRequestOfControllerDataType;

/**   \brief  value based type definition for Can_CanInterruptCounterOfControllerData */
typedef uint8 Can_CanInterruptCounterOfControllerDataType;

/**   \brief  value based type definition for Can_IsBusOffOfControllerData */
typedef boolean Can_IsBusOffOfControllerDataType;

/**   \brief  value based type definition for Can_IsWakeupOfControllerData */
typedef boolean Can_IsWakeupOfControllerDataType;

/**   \brief  value based type definition for Can_LastInitObjectOfControllerData */
typedef uint8 Can_LastInitObjectOfControllerDataType;

/**   \brief  value based type definition for Can_LogStatusOfControllerData */
typedef uint8 Can_LogStatusOfControllerDataType;

/**   \brief  value based type definition for Can_ModeTransitionRequestOfControllerData */
typedef uint8 Can_ModeTransitionRequestOfControllerDataType;

/**   \brief  value based type definition for Can_RamCheckTransitionRequestOfControllerData */
typedef uint8 Can_RamCheckTransitionRequestOfControllerDataType;

/**   \brief  value based type definition for Can_CodeOfInitFilterRules */
typedef uint8 Can_CodeOfInitFilterRulesType;

/**   \brief  value based type definition for Can_MaskOfInitFilterRules */
typedef uint8 Can_MaskOfInitFilterRulesType;

/**   \brief  value based type definition for Can_InitObjectBaudrate */
typedef uint16 Can_InitObjectBaudrateType;

/**   \brief  value based type definition for Can_InitObjectBitTiming */
typedef uint32 Can_InitObjectBitTimingType;

/**   \brief  value based type definition for Can_InitObjectBitTimingData */
typedef uint32 Can_InitObjectBitTimingDataType;

/**   \brief  value based type definition for Can_InitObjectCanFdConfig */
typedef uint32 Can_InitObjectCanFdConfigType;

/**   \brief  value based type definition for Can_InitObjectStartIndex */
typedef uint8 Can_InitObjectStartIndexType;

/**   \brief  value based type definition for Can_ActiveSendObjectOfMailbox */
typedef uint8 Can_ActiveSendObjectOfMailboxType;

/**   \brief  value based type definition for Can_ControllerConfigIdxOfMailbox */
typedef uint8 Can_ControllerConfigIdxOfMailboxType;

/**   \brief  value based type definition for Can_HwHandleOfMailbox */
typedef uint8 Can_HwHandleOfMailboxType;

/**   \brief  value based type definition for Can_IDValueOfMailbox */
typedef uint8 Can_IDValueOfMailboxType;

/**   \brief  value based type definition for Can_MailboxSizeOfMailbox */
typedef uint8 Can_MailboxSizeOfMailboxType;

/**   \brief  value based type definition for Can_MailboxTypeOfMailbox */
typedef uint8 Can_MailboxTypeOfMailboxType;

/**   \brief  value based type definition for Can_MaxDataLenOfMailbox */
typedef uint8 Can_MaxDataLenOfMailboxType;

/**   \brief  value based type definition for Can_MemorySectionsIndexOfMailbox */
typedef uint8 Can_MemorySectionsIndexOfMailboxType;

/**   \brief  value based type definition for Can_MemorySectionStartOfMemorySectionInfo */
typedef uint8 Can_MemorySectionStartOfMemorySectionInfoType;

/**   \brief  value based type definition for Can_HwHandleOfMemorySectionObjects */
typedef uint8 Can_HwHandleOfMemorySectionObjectsType;

/**   \brief  value based type definition for Can_MailboxElementOfMemorySectionObjects */
typedef uint8 Can_MailboxElementOfMemorySectionObjectsType;

/**   \brief  value based type definition for Can_MailboxHandleOfMemorySectionObjects */
typedef uint8 Can_MailboxHandleOfMemorySectionObjectsType;

/**   \brief  value based type definition for Can_PlatformDll_GeneratorVersion */
typedef uint16 Can_PlatformDll_GeneratorVersionType;

/**   \brief  value based type definition for Can_ControllerOfRxFifoData */
typedef uint8 Can_ControllerOfRxFifoDataType;

/**   \brief  value based type definition for Can_FifoDepthOfRxFifoData */
typedef uint8 Can_FifoDepthOfRxFifoDataType;

/**   \brief  value based type definition for Can_FilterStartIndexOfRxFifoData */
typedef uint8 Can_FilterStartIndexOfRxFifoDataType;

/**   \brief  value based type definition for Can_FilterStopIndexOfRxFifoData */
typedef uint8 Can_FilterStopIndexOfRxFifoDataType;

/**   \brief  value based type definition for Can_SizeOfActiveSendObject */
typedef uint8 Can_SizeOfActiveSendObjectType;

/**   \brief  value based type definition for Can_SizeOfCanIfChannelId */
typedef uint8 Can_SizeOfCanIfChannelIdType;

/**   \brief  value based type definition for Can_SizeOfChannelData */
typedef uint8 Can_SizeOfChannelDataType;

/**   \brief  value based type definition for Can_SizeOfControllerConfig */
typedef uint8 Can_SizeOfControllerConfigType;

/**   \brief  value based type definition for Can_SizeOfControllerData */
typedef uint8 Can_SizeOfControllerDataType;

/**   \brief  value based type definition for Can_SizeOfInitFilterRules */
typedef uint8 Can_SizeOfInitFilterRulesType;

/**   \brief  value based type definition for Can_SizeOfInitObjectBaudrate */
typedef uint8 Can_SizeOfInitObjectBaudrateType;

/**   \brief  value based type definition for Can_SizeOfInitObjectBitTiming */
typedef uint8 Can_SizeOfInitObjectBitTimingType;

/**   \brief  value based type definition for Can_SizeOfInitObjectBitTimingData */
typedef uint8 Can_SizeOfInitObjectBitTimingDataType;

/**   \brief  value based type definition for Can_SizeOfInitObjectCanFdConfig */
typedef uint8 Can_SizeOfInitObjectCanFdConfigType;

/**   \brief  value based type definition for Can_SizeOfInitObjectStartIndex */
typedef uint8 Can_SizeOfInitObjectStartIndexType;

/**   \brief  value based type definition for Can_SizeOfMailbox */
typedef uint8 Can_SizeOfMailboxType;

/**   \brief  value based type definition for Can_SizeOfMemorySectionInfo */
typedef uint8 Can_SizeOfMemorySectionInfoType;

/**   \brief  value based type definition for Can_SizeOfMemorySectionObjects */
typedef uint8 Can_SizeOfMemorySectionObjectsType;

/**   \brief  value based type definition for Can_SizeOfOsIsrId */
typedef uint8 Can_SizeOfOsIsrIdType;

/**   \brief  value based type definition for Can_SizeOfRxFifoData */
typedef uint8 Can_SizeOfRxFifoDataType;

/**   \brief  value based type definition for Can_SizeOfWakeupSourceRef */
typedef uint8 Can_SizeOfWakeupSourceRefType;

/**   \brief  value based type definition for Can_WakeupSourceRef */
typedef uint8 Can_WakeupSourceRefType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  CanPCStructTypes  Can Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in Can_ActiveSendObject */
typedef struct sCan_ActiveSendObjectType
{
  Can_StateOfActiveSendObjectType StateOfActiveSendObject;  /**< send state like cancelled or send activ */
  Can_PduOfActiveSendObjectType PduOfActiveSendObject;  /**< buffered PduId for confirmation or cancellation */
} Can_ActiveSendObjectType;

/**   \brief  type used in Can_ChannelData */
typedef struct sCan_ChannelDataType
{
  Can_FifoProcCountOfChannelDataType FifoProcCountOfChannelData;  /**< Maximum number FIFO messages processed per event */
  Can_FrStartIndexOfChannelDataType FrStartIndexOfChannelData;  /**< Start index of used receive rules (FullCAN + BasicCAN) */
  Can_FrTotalCountOfChannelDataType FrTotalCountOfChannelData;  /**< Number of used receive rules (FullCAN + BasicCAN) */
  Can_RxBcMaskOfChannelDataType RxBcMaskOfChannelData;  /**< Bitmask of Rx BasicCAN objects (receive FIFO buffer 7-0) */
  Can_RxBcStartIndexOfChannelDataType RxBcStartIndexOfChannelData;  /**< Start index of used receive FIFO buffers */
  Can_RxBcStopIndexOfChannelDataType RxBcStopIndexOfChannelData;  /**< Stop index of used receive FIFO buffers */
  Can_TxIntMaskOfChannelDataType TxIntMaskOfChannelData;  /**< Bitmask of Tx interrupt objects (local transmit buffer 31-0) */
} Can_ChannelDataType;

/**   \brief  type used in Can_ControllerConfig */
typedef struct sCan_ControllerConfigType
{
  Can_CanControllerDefaultBaudrateOfControllerConfigType CanControllerDefaultBaudrateOfControllerConfig;
  Can_CanControllerDefaultBaudrateIdxOfControllerConfigType CanControllerDefaultBaudrateIdxOfControllerConfig;
  Can_MailboxRxBasicEndIdxOfControllerConfigType MailboxRxBasicEndIdxOfControllerConfig;  /**< the end index of the 0:n relation pointing to Can_Mailbox */
  Can_MailboxRxBasicLengthOfControllerConfigType MailboxRxBasicLengthOfControllerConfig;  /**< the number of relations pointing to Can_Mailbox */
  Can_MailboxRxBasicStartIdxOfControllerConfigType MailboxRxBasicStartIdxOfControllerConfig;  /**< the start index of the 0:n relation pointing to Can_Mailbox */
  Can_MailboxTxBasicEndIdxOfControllerConfigType MailboxTxBasicEndIdxOfControllerConfig;  /**< the end index of the 0:n relation pointing to Can_Mailbox */
  Can_MailboxTxBasicLengthOfControllerConfigType MailboxTxBasicLengthOfControllerConfig;  /**< the number of relations pointing to Can_Mailbox */
  Can_MailboxTxBasicStartIdxOfControllerConfigType MailboxTxBasicStartIdxOfControllerConfig;  /**< the start index of the 0:n relation pointing to Can_Mailbox */
  Can_RxBasicHwStartOfControllerConfigType RxBasicHwStartOfControllerConfig;
  Can_RxBasicHwStopOfControllerConfigType RxBasicHwStopOfControllerConfig;
  Can_RxFullHwStartOfControllerConfigType RxFullHwStartOfControllerConfig;
  Can_RxFullHwStopOfControllerConfigType RxFullHwStopOfControllerConfig;
  Can_TxBasicHwStartOfControllerConfigType TxBasicHwStartOfControllerConfig;
  Can_TxBasicHwStopOfControllerConfigType TxBasicHwStopOfControllerConfig;
  Can_TxFullHwStartOfControllerConfigType TxFullHwStartOfControllerConfig;
  Can_TxFullHwStopOfControllerConfigType TxFullHwStopOfControllerConfig;
  Can_UnusedHwStartOfControllerConfigType UnusedHwStartOfControllerConfig;
  Can_UnusedHwStopOfControllerConfigType UnusedHwStopOfControllerConfig;
} Can_ControllerConfigType;

/**   \brief  type used in Can_ControllerData */
typedef struct sCan_ControllerDataType
{
  Can_BusOffCounterOfControllerDataType BusOffCounterOfControllerData;  /**< Counter to determine forced busoff recovery */
  Can_BusOffTransitionRequestOfControllerDataType BusOffTransitionRequestOfControllerData;  /**< CAN state request for each controller: ContinueBusOffRecovery=0x00, FinishBusOffRecovery=0x01 */
  Can_CanInterruptCounterOfControllerDataType CanInterruptCounterOfControllerData;  /**< CAN interrupt disable counter for each controller */
  Can_IsBusOffOfControllerDataType IsBusOffOfControllerData;  /**< CAN state for each controller: busoff occur */
  Can_IsWakeupOfControllerDataType IsWakeupOfControllerData;  /**< CAN state for each controller: wakeup occur */
  Can_LastInitObjectOfControllerDataType LastInitObjectOfControllerData;  /**< last set baudrate for reinit */
  Can_LogStatusOfControllerDataType LogStatusOfControllerData;  /**< CAN state for each controller: UNINIT=0x00, START=0x01, STOP=0x02, INIT=0x04, INCONSISTENT=0x08, WARNING =0x10, PASSIVE=0x20, BUSOFF=0x40, SLEEP=0x80 */
  Can_ModeTransitionRequestOfControllerDataType ModeTransitionRequestOfControllerData;  /**< CAN state request for each controller: INIT=0x00, SLEEP=0x01, WAKEUP=0x02, STOP+INIT=0x03, START=0x04, START+INIT=0x05, NONE=0x06 */
  Can_RamCheckTransitionRequestOfControllerDataType RamCheckTransitionRequestOfControllerData;  /**< CAN state request for each controller: kCanSuppressRamCheck=0x01, kCanExecuteRamCheck=0x00 */
  tCanLLCanIntOld CanInterruptOldStatusOfControllerData;  /**< last CAN interrupt status for restore interrupt for each controller */
  Can_LoopTimeout_dim_type LoopTimeoutOfControllerData;  /**< hw loop timeout for each controller */
  tCanTmpMsgObj RxTmpBufOfControllerData;  /**< Temporary buffer for received messages */
} Can_ControllerDataType;

/**   \brief  type used in Can_InitFilterRules */
typedef struct sCan_InitFilterRulesType
{
  Can_CodeOfInitFilterRulesType CodeOfInitFilterRules;  /**< Initialization value for the receive rule ID register */
  Can_MaskOfInitFilterRulesType MaskOfInitFilterRules;  /**< Initialization value for the receive rule mask register */
} Can_InitFilterRulesType;

/**   \brief  type used in Can_Mailbox */
typedef struct sCan_MailboxType
{
  Can_ActiveSendObjectOfMailboxType ActiveSendObjectOfMailbox;
  Can_ControllerConfigIdxOfMailboxType ControllerConfigIdxOfMailbox;  /**< the index of the 1:1 relation pointing to Can_ControllerConfig */
  Can_HwHandleOfMailboxType HwHandleOfMailbox;
  Can_IDValueOfMailboxType IDValueOfMailbox;
  Can_MailboxSizeOfMailboxType MailboxSizeOfMailbox;
  Can_MailboxTypeOfMailboxType MailboxTypeOfMailbox;
  Can_MaxDataLenOfMailboxType MaxDataLenOfMailbox;
  Can_MemorySectionsIndexOfMailboxType MemorySectionsIndexOfMailbox;
} Can_MailboxType;

/**   \brief  type used in Can_MemorySectionInfo */
typedef struct sCan_MemorySectionInfoType
{
  Can_MemorySectionStartOfMemorySectionInfoType MemorySectionStartOfMemorySectionInfo;
} Can_MemorySectionInfoType;

/**   \brief  type used in Can_MemorySectionObjects */
typedef struct sCan_MemorySectionObjectsType
{
  Can_HwHandleOfMemorySectionObjectsType HwHandleOfMemorySectionObjects;
  Can_MailboxElementOfMemorySectionObjectsType MailboxElementOfMemorySectionObjects;
  Can_MailboxHandleOfMemorySectionObjectsType MailboxHandleOfMemorySectionObjects;
} Can_MemorySectionObjectsType;

/**   \brief  type used in Can_OsIsrId */
typedef struct sCan_OsIsrIdType
{
  Can_ExternalISRType IsrStatusIdOfOsIsrId;  /**< Status ISR ID */
  Can_ExternalISRType IsrTxIdOfOsIsrId;  /**< Tx ISR ID */
  Can_ExternalISRType IsrWakeupIdOfOsIsrId;  /**< Wakeup ISR ID */
} Can_OsIsrIdType;

/**   \brief  type used in Can_RxFifoData */
typedef struct sCan_RxFifoDataType
{
  Can_ControllerOfRxFifoDataType ControllerOfRxFifoData;  /**< Logical index of the controller the FIFO is used on */
  Can_FifoDepthOfRxFifoDataType FifoDepthOfRxFifoData;  /**< Initialization value for the depth of the FIFO buffer */
  Can_FilterStartIndexOfRxFifoDataType FilterStartIndexOfRxFifoData;  /**< Start index for filters in Can_InitFilterRules */
  Can_FilterStopIndexOfRxFifoDataType FilterStopIndexOfRxFifoData;  /**< Stop index for filters in Can_InitFilterRules */
} Can_RxFifoDataType;

/** 
  \}
*/ 

/** 
  \defgroup  CanPCRootPointerTypes  Can Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to Can_ActiveSendObject */
typedef P2VAR(Can_ActiveSendObjectType, TYPEDEF, CAN_VAR_NOINIT) Can_ActiveSendObjectPtrType;

/**   \brief  type used to point to Can_CanIfChannelId */
typedef P2CONST(Can_CanIfChannelIdType, TYPEDEF, CAN_CONST) Can_CanIfChannelIdPtrType;

/**   \brief  type used to point to Can_ChannelData */
typedef P2CONST(Can_ChannelDataType, TYPEDEF, CAN_CONST) Can_ChannelDataPtrType;

/**   \brief  type used to point to Can_ControllerConfig */
typedef P2CONST(Can_ControllerConfigType, TYPEDEF, CAN_CONST) Can_ControllerConfigPtrType;

/**   \brief  type used to point to Can_ControllerData */
typedef P2VAR(Can_ControllerDataType, TYPEDEF, CAN_VAR_NOINIT) Can_ControllerDataPtrType;

/**   \brief  type used to point to Can_InitFilterRules */
typedef P2CONST(Can_InitFilterRulesType, TYPEDEF, CAN_CONST) Can_InitFilterRulesPtrType;

/**   \brief  type used to point to Can_InitObjectBaudrate */
typedef P2CONST(Can_InitObjectBaudrateType, TYPEDEF, CAN_CONST) Can_InitObjectBaudratePtrType;

/**   \brief  type used to point to Can_InitObjectBitTiming */
typedef P2CONST(Can_InitObjectBitTimingType, TYPEDEF, CAN_CONST) Can_InitObjectBitTimingPtrType;

/**   \brief  type used to point to Can_InitObjectBitTimingData */
typedef P2CONST(Can_InitObjectBitTimingDataType, TYPEDEF, CAN_CONST) Can_InitObjectBitTimingDataPtrType;

/**   \brief  type used to point to Can_InitObjectCanFdConfig */
typedef P2CONST(Can_InitObjectCanFdConfigType, TYPEDEF, CAN_CONST) Can_InitObjectCanFdConfigPtrType;

/**   \brief  type used to point to Can_InitObjectStartIndex */
typedef P2CONST(Can_InitObjectStartIndexType, TYPEDEF, CAN_CONST) Can_InitObjectStartIndexPtrType;

/**   \brief  type used to point to Can_Mailbox */
typedef P2CONST(Can_MailboxType, TYPEDEF, CAN_CONST) Can_MailboxPtrType;

/**   \brief  type used to point to Can_MemorySectionInfo */
typedef P2CONST(Can_MemorySectionInfoType, TYPEDEF, CAN_CONST) Can_MemorySectionInfoPtrType;

/**   \brief  type used to point to Can_MemorySectionObjects */
typedef P2CONST(Can_MemorySectionObjectsType, TYPEDEF, CAN_CONST) Can_MemorySectionObjectsPtrType;

/**   \brief  type used to point to Can_OsIsrId */
typedef P2CONST(Can_OsIsrIdType, TYPEDEF, CAN_CONST) Can_OsIsrIdPtrType;

/**   \brief  type used to point to Can_RxFifoData */
typedef P2CONST(Can_RxFifoDataType, TYPEDEF, CAN_CONST) Can_RxFifoDataPtrType;

/**   \brief  type used to point to Can_WakeupSourceRef */
typedef P2CONST(Can_WakeupSourceRefType, TYPEDEF, CAN_CONST) Can_WakeupSourceRefPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  CanPCRootValueTypes  Can Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in Can_PCConfig */
typedef struct sCan_PCConfigType
{
  uint8 Can_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} Can_PCConfigType;

typedef Can_PCConfigType Can_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  Can_CanIfChannelId
**********************************************************************************************************************/
/** 
  \var    Can_CanIfChannelId
  \brief  indirection table Can to CanIf controller ID
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_CanIfChannelIdType, CAN_CONST) Can_CanIfChannelId[1];
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_ChannelData
**********************************************************************************************************************/
/** 
  \var    Can_ChannelData
  \brief  Controller specific information
  \details
  Element           Description
  FifoProcCount     Maximum number FIFO messages processed per event
  FrStartIndex      Start index of used receive rules (FullCAN + BasicCAN)
  FrTotalCount      Number of used receive rules (FullCAN + BasicCAN)
  RxBcMask          Bitmask of Rx BasicCAN objects (receive FIFO buffer 7-0)
  RxBcStartIndex    Start index of used receive FIFO buffers
  RxBcStopIndex     Stop index of used receive FIFO buffers
  TxIntMask         Bitmask of Tx interrupt objects (local transmit buffer 31-0)
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_ChannelDataType, CAN_CONST) Can_ChannelData[1];
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_ControllerConfig
**********************************************************************************************************************/
/** 
  \var    Can_ControllerConfig
  \brief  Global configuration for all controllers
  \details
  Element                            Description
  CanControllerDefaultBaudrate   
  CanControllerDefaultBaudrateIdx
  MailboxRxBasicEndIdx               the end index of the 0:n relation pointing to Can_Mailbox
  MailboxRxBasicLength               the number of relations pointing to Can_Mailbox
  MailboxRxBasicStartIdx             the start index of the 0:n relation pointing to Can_Mailbox
  MailboxTxBasicEndIdx               the end index of the 0:n relation pointing to Can_Mailbox
  MailboxTxBasicLength               the number of relations pointing to Can_Mailbox
  MailboxTxBasicStartIdx             the start index of the 0:n relation pointing to Can_Mailbox
  RxBasicHwStart                 
  RxBasicHwStop                  
  RxFullHwStart                  
  RxFullHwStop                   
  TxBasicHwStart                 
  TxBasicHwStop                  
  TxFullHwStart                  
  TxFullHwStop                   
  UnusedHwStart                  
  UnusedHwStop                   
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_ControllerConfigType, CAN_CONST) Can_ControllerConfig[1];
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitFilterRules
**********************************************************************************************************************/
/** 
  \var    Can_InitFilterRules
  \brief  Rx BasicCAN acceptance filters
  \details
  Element    Description
  Code       Initialization value for the receive rule ID register
  Mask       Initialization value for the receive rule mask register
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_InitFilterRulesType, CAN_CONST) Can_InitFilterRules[1];
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectBaudrate
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectBaudrate
  \brief  baudrates ('InitStruct' as index)
*/ 
#define CAN_START_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_InitObjectBaudrateType, CAN_CONST) Can_InitObjectBaudrate[1];
#define CAN_STOP_SEC_CONST_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectBitTiming
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectBitTiming
  \brief  Initialization values for the channel nominal bit rate configuration registers
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_InitObjectBitTimingType, CAN_CONST) Can_InitObjectBitTiming[1];
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectBitTimingData
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectBitTimingData
  \brief  Initialization values for the channel data bit rate configuration registers
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_InitObjectBitTimingDataType, CAN_CONST) Can_InitObjectBitTimingData[1];
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectCanFdConfig
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectCanFdConfig
  \brief  Initialization values for the channel CAN FD configuration registers
*/ 
#define CAN_START_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_InitObjectCanFdConfigType, CAN_CONST) Can_InitObjectCanFdConfig[1];
#define CAN_STOP_SEC_CONST_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_InitObjectStartIndex
**********************************************************************************************************************/
/** 
  \var    Can_InitObjectStartIndex
  \brief  Start index of 'InitStruct' / baudratesets (controllers as index)
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_InitObjectStartIndexType, CAN_CONST) Can_InitObjectStartIndex[2];
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_Mailbox
**********************************************************************************************************************/
/** 
  \var    Can_Mailbox
  \brief  mailbox configuration (over all controllers)
  \details
  Element                Description
  ActiveSendObject   
  ControllerConfigIdx    the index of the 1:1 relation pointing to Can_ControllerConfig
  HwHandle           
  IDValue            
  MailboxSize        
  MailboxType        
  MaxDataLen         
  MemorySectionsIndex
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_MailboxType, CAN_CONST) Can_Mailbox[2];
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_MemorySectionInfo
**********************************************************************************************************************/
/** 
  \var    Can_MemorySectionInfo
  \brief  Memory section description
  \details
  Element               Description
  MemorySectionStart
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_MemorySectionInfoType, CAN_CONST) Can_MemorySectionInfo[1];
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_MemorySectionObjects
**********************************************************************************************************************/
/** 
  \var    Can_MemorySectionObjects
  \brief  Memory section objects description
  \details
  Element           Description
  HwHandle      
  MailboxElement
  MailboxHandle 
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_MemorySectionObjectsType, CAN_CONST) Can_MemorySectionObjects[32];
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_OsIsrId
**********************************************************************************************************************/
/** 
  \var    Can_OsIsrId
  \brief  OS ISR IDs of the the channel specific interrupts
  \details
  Element        Description
  IsrStatusId    Status ISR ID
  IsrTxId        Tx ISR ID
  IsrWakeupId    Wakeup ISR ID
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_OsIsrIdType, CAN_CONST) Can_OsIsrId[1];
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_RxFifoData
**********************************************************************************************************************/
/** 
  \var    Can_RxFifoData
  \brief  Rx BasicCan FIFO specific information
  \details
  Element             Description
  Controller          Logical index of the controller the FIFO is used on
  FifoDepth           Initialization value for the depth of the FIFO buffer
  FilterStartIndex    Start index for filters in Can_InitFilterRules
  FilterStopIndex     Stop index for filters in Can_InitFilterRules
*/ 
#define CAN_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_RxFifoDataType, CAN_CONST) Can_RxFifoData[1];
#define CAN_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_WakeupSourceRef
**********************************************************************************************************************/
/** 
  \var    Can_WakeupSourceRef
  \brief  wakeup Source for channel
*/ 
#define CAN_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Can_WakeupSourceRefType, CAN_CONST) Can_WakeupSourceRef[1];
#define CAN_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_ActiveSendObject
**********************************************************************************************************************/
/** 
  \var    Can_ActiveSendObject
  \brief  temporary data for TX object
  \details
  Element    Description
  State      send state like cancelled or send activ
  Pdu        buffered PduId for confirmation or cancellation
*/ 
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Can_ActiveSendObjectType, CAN_VAR_NOINIT) Can_ActiveSendObject[1];
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Can_ControllerData
**********************************************************************************************************************/
/** 
  \var    Can_ControllerData
  \brief  struct for all controller related variable data
  \details
  Element                      Description
  BusOffCounter                Counter to determine forced busoff recovery
  BusOffTransitionRequest      CAN state request for each controller: ContinueBusOffRecovery=0x00, FinishBusOffRecovery=0x01
  CanInterruptCounter          CAN interrupt disable counter for each controller
  IsBusOff                     CAN state for each controller: busoff occur
  IsWakeup                     CAN state for each controller: wakeup occur
  LastInitObject               last set baudrate for reinit
  LogStatus                    CAN state for each controller: UNINIT=0x00, START=0x01, STOP=0x02, INIT=0x04, INCONSISTENT=0x08, WARNING =0x10, PASSIVE=0x20, BUSOFF=0x40, SLEEP=0x80
  ModeTransitionRequest        CAN state request for each controller: INIT=0x00, SLEEP=0x01, WAKEUP=0x02, STOP+INIT=0x03, START=0x04, START+INIT=0x05, NONE=0x06
  RamCheckTransitionRequest    CAN state request for each controller: kCanSuppressRamCheck=0x01, kCanExecuteRamCheck=0x00
  CanInterruptOldStatus        last CAN interrupt status for restore interrupt for each controller
  LoopTimeout                  hw loop timeout for each controller
  RxTmpBuf                     Temporary buffer for received messages
*/ 
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Can_ControllerDataType, CAN_VAR_NOINIT) Can_ControllerData[1];
#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/* -----------------------------------------------------------------------------
    UserConfigFile
 ----------------------------------------------------------------------------- */
/* User Config File Start */

/* User Config File End */



#endif  /* CAN_CFG_H */
/**********************************************************************************************************************
  END OF FILE: Can_Cfg.h
**********************************************************************************************************************/
 

