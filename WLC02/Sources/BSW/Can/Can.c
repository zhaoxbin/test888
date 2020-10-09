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

/* \trace SPEC-1570 */
/***************************************************************************/
/* Include files                                                           */
/***************************************************************************/
/* ECO_IGNORE_BLOCK_BEGIN */
#define C_DRV_INTERNAL /* compatibility */
#define CAN_SOURCE     /* testability */
#define __CAN_SRC__       /* compatibility RTM not aware of multi driver instance */ /* PRQA S 0602,0603 */ /* MD_Can_ModuleDefine */
#if !defined(__CAN_SRC__) /* driver use ORGANI without infix */ /* COV_CAN_INTERNAL */
# define __CAN_SRC__      /* for all MSR module (used by RTM) */ /* PRQA S 0602,0603 */ /* MD_Can_ModuleDefine */
#endif

/* \trace SPEC-1408, SPEC-1590, SPEC-1588 */
/* \trace SPEC-1392 */
#include "CanIf_Cbk.h"   /* for callback declaration */
/* \trace SPEC-1707 */
#include "CanIf.h"       /* for version check */
#include "Can_Local.h"    /* have to be last include due to channel define will lead to problems */

#include "flexcan_driver.h"

#if (CAN_DEV_ERROR_REPORT == STD_ON)
/* \trace SPEC-1596 */
# include "Det.h"
#endif

#if !defined(CAN_AMD_RUNTIME_MEASUREMENT) /* COV_CAN_COMPATIBILITY */
# define CAN_AMD_RUNTIME_MEASUREMENT STD_OFF
#endif
#if (CAN_AMD_RUNTIME_MEASUREMENT == STD_ON) /* COV_CAN_AMD_RUNTIME_MEASUREMENT */
# include "AmdRtm.h"
#endif

#if !defined(CAN_RUNTIME_MEASUREMENT_SUPPORT) /* COV_CAN_COMPATIBILITY */
# define CAN_RUNTIME_MEASUREMENT_SUPPORT STD_OFF
#endif
#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
/* AR4-328 */
# define C_ENABLE_RUNTIME_MEASUREMENT_SUPPORT
# include "Rtm.h"
#endif

#include "vstdlib.h"

/* ECO_IGNORE_BLOCK_END */

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_COREVERSION           != 0x0800u) /* \trace SPEC-1699 */
# error "Source and Header file are inconsistent!"
#endif
#if (CAN_RELEASE_COREVERSION   != 0x00u)
# error "Source and Header file are inconsistent!"
#endif
#if defined(CAN_GEN_BASE_CFG5_VERSION) /* COV_CAN_COMPATIBILITY */
# if (CAN_GEN_BASE_CFG5_VERSION         != 0x0103u)
#  error "Source and Generated Header file are inconsistent!"
# endif
#else
# error "No CAN_GEN_BASE_CFG5_VERSION is defined"
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

/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/
#if defined(CAN_USE_NO_VECTOR_IF) /* for testability */
# define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#else
# if defined(CANIF_VENDOR_ID) /* COV_CAN_COMPATIBILITY */
#  if (CANIF_VENDOR_ID == 0x001E) /* COV_CAN_COMPATIBILITY */
#   define CAN_USE_VECTOR_IF
#   if defined(IF_ASRIFCAN_VERSION) /* COV_CAN_COMPATIBILITY */
#    if (IF_ASRIFCAN_VERSION < 0x0410) /* COV_CAN_COMPATIBILITY */
#     define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#    endif
#   endif
#  else
#   define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
#  endif
# else
#  define CAN_USE_CRITICALSECTION_OVER_CONFIRMATION
# endif
#endif
/* Compatibility to CBD */
/* instead of direct canCanInterruptCounter[] use Can_GetCanInterruptCounter(Index) abstraction for ComStackLib */

#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
# define CanHookBegin_Can_Init()                              Rtm_Start(RtmConf_RtmMeasurementPoint_Can_Init)
# define CanHookEnd_Can_Init()                                Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_Init)
# define CanHookBegin_Can_SetControllerMode()                 Rtm_Start(RtmConf_RtmMeasurementPoint_Can_SetControllerMode)
# define CanHookEnd_Can_SetControllerMode()                   Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_SetControllerMode)
# define CanHookBegin_Can_Write()                             Rtm_Start(RtmConf_RtmMeasurementPoint_Can_Write)
# define CanHookEnd_Can_Write()                               Rtm_Stop(RtmConf_RtmMeasurementPoint_Can_Write)

#else /* BRS runtime measurement */
# define CanHookBegin_Can_Init()
# define CanHookEnd_Can_Init()
# define CanHookBegin_Can_SetControllerMode() \

# define CanHookEnd_Can_SetControllerMode() \

# define CanHookBegin_Can_Write() \

# define CanHookEnd_Can_Write() \

#endif

# define CanHookBegin_CanHL_ReInit() \

# define CanHookEnd_CanHL_ReInit() \

#define CanHookBegin_CanHL_TxConfirmation() \

#define CanHookEnd_CanHL_TxConfirmation() \

#define CanHookBegin_CanHL_BasicCanMsgReceived() \

#define CanHookEnd_CanHL_BasicCanMsgReceived() \

#define CanHookBegin_CanHL_FullCanMsgReceived() \

#define CanHookEnd_CanHL_FullCanMsgReceived() \

#define CanHookBegin_Can_MainFunction_Write() \

#define CanHookEnd_Can_MainFunction_Write() \

#define CanHookBegin_Can_MainFunction_Read() \

#define CanHookEnd_Can_MainFunction_Read() \

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

#define kCanCrIntMaskBusoff            0x00000800u /*!< Set the Busoff Entry Interrupt Enable bit in the Channel Control Register */
#define kCanCrIntMaskCancel            0x00010000u /*!< Set the Transmit Abort Interrupt Enable bit in the Channel Control Register */
#define kCanCrListenOnlyMode           0x03000000u /*!< Enable listen only mode in the Channel Control Register */
#if defined(C_ENABLE_IMMEDIATE_BUSOFF_RECOVERY)
# define kCanCrHaltAtBusoff            0x00200000u /*!< Set the Busoff behavior to halt mode at entry in the Channel Control Register (BOM=01) */
#else
# define kCanCrHaltAtBusoff            0x00400000u /*!< Set the Busoff behavior to halt mode at end in the Channel Control Register (BOM=10) (Default) */
#endif
#define kCanSrMaskBusoff               0x00000010u /*!< Busoff mask for reading access to Channel Status Register */
#define kCanSrMaskPassive              0x00000008u /*!< Error passive mask for reading access to Channel Status Register */
#define kCanSrMaskRec                  0x00FF0000u /*!< Transmit error counter mask for reading access to Channel Status Register */
#define kCanSrMaskTec                  0xFF000000u /*!< Receive error counter mask for reading access to Channel Status Register */
#define kCanEfMaskBusoff               0x0008u     /*!< Busoff Entry Flag mask for reading access to Channel Error Flag Register */
#define kCanEfMaskBusoffClear          0x7FF7u     /*!< Mask to clear the Busoff Entry Flag by writing mask to Channel Error Flag Register */

#if defined(C_ENABLE_ALTERNATIVE_CLOCK_SOURCE)
# define kCanGlobCfg                   0x00000010u /*!< Set CAN Clock Source Select to 1 in the Global Configuration Register */
#else
# define kCanGlobCfg                   0x00000000u /*!< Set CAN Clock Source Select to 0 in the Global Configuration Register (Default) */
#endif
#define kCanIntMaskMessageLost         0x00000200u /*!< Set FIFO Message Lost Interrupt Enable in the Global Control Register */
#define kCanSrMaskRamIst               0x00000008u /*!< Mask to read CAN RAM Initilization Status Flag from Global Status Register */
#if defined (C_ENABLE_ECC_TX_ERROR)
# if (kCanMaxPhysChannels == 1u)
#  define kCanEfMaskEccError           0x00010000u /*!< Mask to read ECC Error Flag for all used channels from Global Error Flag Register */
#  define kCanEfMaskEccErrorClear      0xFFFEFFFFu /*!< Mask to clear ECC Error Flag for all used channels by writing mask to the Global Error Flag Register */
# elif (kCanMaxPhysChannels == 2u)
#  define kCanEfMaskEccError           0x00030000u /*!< Mask to read ECC Error Flag for all used channels from Global Error Flag Register */
#  define kCanEfMaskEccErrorClear      0xFFFCFFFFu /*!< Mask to clear ECC Error Flag for all used channels by writing mask to the Global Error Flag Register */
# elif (kCanMaxPhysChannels == 3u)
#  define kCanEfMaskEccError           0x00070000u /*!< Mask to read ECC Error Flag for all used channels from Global Error Flag Register */
#  define kCanEfMaskEccErrorClear      0xFFF8FFFFu /*!< Mask to clear ECC Error Flag for all used channels by writing mask to the Global Error Flag Register */
# elif (kCanMaxPhysChannels == 4u)
#  define kCanEfMaskEccError           0x000F0000u /*!< Mask to read ECC Error Flag for all used channels from Global Error Flag Register */
#  define kCanEfMaskEccErrorClear      0xFFF0FFFFu /*!< Mask to clear ECC Error Flag for all used channels by writing mask to the Global Error Flag Register */
# elif (kCanMaxPhysChannels == 5u)
#  define kCanEfMaskEccError           0x001F0000u /*!< Mask to read ECC Error Flag for all used channels from Global Error Flag Register */
#  define kCanEfMaskEccErrorClear      0xFFE0FFFFu /*!< Mask to clear ECC Error Flag for all used channels by writing mask to the Global Error Flag Register */
# elif (kCanMaxPhysChannels == 6u) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
#  define kCanEfMaskEccError           0x003F0000u /*!< Mask to read ECC Error Flag for all used channels from Global Error Flag Register */
#  define kCanEfMaskEccErrorClear      0xFFC0FFFFu /*!< Mask to clear ECC Error Flag for all used channels by writing mask to the Global Error Flag Register */
# elif (kCanMaxPhysChannels == 7u) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
#  define kCanEfMaskEccError           0x007F0000u /*!< Mask to read ECC Error Flag for all used channels from Global Error Flag Register */
#  define kCanEfMaskEccErrorClear      0xFF80FFFFu /*!< Mask to clear ECC Error Flag for all used channels by writing mask to the Global Error Flag Register */
# elif (kCanMaxPhysChannels == 8u) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
#  define kCanEfMaskEccError           0x00FF0000u /*!< Mask to read ECC Error Flag for all used channels from Global Error Flag Register */
#  define kCanEfMaskEccErrorClear      0xFF00FFFFu /*!< Mask to clear ECC Error Flag for all used channels by writing mask to the Global Error Flag Register */
# endif
#endif
#define kCanHwRamTestEnable            0x00000004u /*!< Enable the RAM Test in Global Test Control Register */
#define kCanHwRamTestDisable           0x00000000u /*!< Disable the RAM Test in Global Test Control Register */
#define kCanProtectionUnlockData1      0x00007575u /*!< First key to write to Global Lock Key Register to release the protection of the test mode */
#define kCanProtectionUnlockData2      0x00008A8Au /*!< Second key to write to Global Lock Key Register to release the protection of the test mode */

#define kCanRuleWrite                  0x00000100u /*!< Set the Receive Rule Table Write Enable to enabled in the Receive Rule Entry Control Register */
#define kCanRuleReceive                0x00000000u /*!< Set the Receive Rule Table Write Enable to disabled in the Receive Rule Entry Control Register */
#define kCanRuleUseBuf                 0x00008000u /*!< Set Receive Buffer Enable in the Receive Rule Pointer Register */
#define kCanRuleStdMustMatch           0xC00007FFu /*!< Set the IDE Mask, RTR Mask and ID Mask in the Receive Rule Mask Register, to compare a STD ID */
#define kCanRuleExtMustMatch           0xDFFFFFFFu /*!< Set the IDE Mask, RTR Mask and ID Mask in the Receive Rule Mask Register, to compare a EXT ID */
#define kCanRuleHeader                 0xC0000000u /*!< Set the IDE Mask and the RTR Mask in the Receive Rule Mask Register */
#define kCanRuleHeaderClrMask          0x1FFFFFFFu /*!< Clear IDE and RTR Mask in the Receive Rule Mask Register */
#define kCanRuleIndexMask              0x000Fu     /*!< Mask to convert filter index to register index */
#define kCanRulePageMask               0xFFF0u     /*!< Mask to convert filter index to filter page */
#define kCanRulePageShiftVal           4u          /*!< Value to shift converted filter page */

#define kCanZero                       0u          /*!< Define zero */
#define kCanOne                        1u          /*!< Define one  */
#define kCanOne8                       0xFFu       /*!<  8bit Mask */
#define kCanOne16                      0xFFFFu     /*!< 16bit Mask */
#define kCanOne32                      0xFFFFFFFFu /*!< 32bit Mask */
#define kCanDlcMask                    0xF0000000u /*!< Mask for the DLC bits in the Transmit Buffer Pointer Register */
#define kCanFdCfgMask                  0x00000007u /*!< Mask for the FDF, BRS and ESI bits in the Transmit Buffer CAN FD Configuration Register */
#define kCanRxFifoMask                 0x000000FFu /*!< Receive FIFO Buffer Interrupt Request Status Flag Mask for the Receive FIFO Buffer Interrupt Flag Status Register */

#define kCanModeMask                   0xFFFFFFF8u /*!< Mode Select Mask for the Channel Control Register */
#define kCanModeBits                   0x00000007u /*!< Mask to read the Mode Bits from the Channel Status Register */
#define kCanOperationMode              0x00000000u /*!< Set mode select to communication mode in the global/channel control register */
#define kCanResetMode                  0x00000001u /*!< Set mode select to reset mode in the global/channel control register */
#define kCanTestMode                   0x00000002u /*!< Set mode select to test mode in the global control register */
#define kCanHaltMode                   0x00000002u /*!< Set mode select to halt mode in the channel control register */
#define kCanStopMode                   0x00000005u /*!< Set mode select to stop mode in the global/channel control register */

#define kCanCrTxBufReq                 0x01u       /*!< Set Transmit Request in the Transmit Buffer Control Register */
#define kCanCrTxBufCancel              0x02u       /*!< Set Transmit Abort Request in the Transmit Buffer Control Register */
#define kCanSrTxBufMaskPending         0x06u       /*!< Mask to read whether an action has been completed in the Transmit Buffer Status Register */
#define kCanSrTxBufMaskComplete        0x04u       /*!< Mask to read whether a transmission is completed in the Transmit Buffer Status Register */
#define kCanSrTxBufMaskCancel          0x02u       /*!< Mask to read whether a transmission abort request has was present in the Transmit Buffer Status Register */
#define kCanSrTxBufMaskFree            0x1Fu       /*!< Mask to read whether the transmission buffer is free in the Transmit Buffer Status Register */
#define kCanSrTxBufMaskAReq            0x10u       /*!< Mask to read whether a transmission abort request is pending in the Transmit Buffer Status Register */
#define kCanSrTxBufMaskTReq            0x08u       /*!< Mask to read whether a transmission request is pending in the Transmit Buffer Status Register */

#define kCanCrFifoEnable               0x00000001u /*!< Set Transmit/Receive FIFO Buffer Enable in the (Transmit/)Receive FIFO Buffer Configuration and Control Register */
#define kCanCrRxFifoSet                0x00001000u /*!< Set Transmit/Receive FIFO interrupt request for each message in the (Transmit/)Receive FIFO Buffer Configuration and Control Register */
#define kCanCrRxFifoIntEnable          0x00000002u /*!< Set Receive FIFO Receive Interrupt Enable in the Receive FIFO Buffer Configuration and Control Register */
#define kCanSrFifoEmpty                0x00000001u /*!< Mask to read, whether the Transmit/Receive FIFO buffer contains unread messages, from the (Transmit/)Receive FIFO Buffer Status Register */
#define kCanSrFifoFull                 0x00000002u /*!< Mask to read, whether the Transmit/Receive FIFO buffer is full, from the (Transmit/)Receive FIFO Buffer Status Register */
#define kCanSrFifoOverrun              0x00000004u /*!< Mask to read, whether a Transmit/Receive FIFO message is lost, from the (Transmit/)Receive FIFO Buffer Status Register */
#define kCanSrRxFifoIntFlag            0x00000008u /*!< Mask to read, whether a Receive FIFO interrupt request is present, from the Receive FIFO Buffer Status Register */
#define kCanSrTxFifoIntFlag            0x00000010u /*!< Mask to read, whether the Transmit FIFO interrupt request is present, from the Transmit/Receive FIFO Buffer Status Register */
#define kCanSrFifoMsgCount             0x0000FF00u /*!< Mask to read the number of messages stored in the transmit/receive FIFO buffer from the (Transmit/)Receive FIFO Buffer Status Register */
#define kCanPcrFifoPC                  0x000000FFu /*!< Value to move the FIFO pointer in the (Transmit/)Receive FIFO Pointer Control Register */

/* INTC */
#define kCanIntcEIMK                   ((vuint8) 0x80u)    /*!< Enables the interrupt processing in the EI Level Interrupt Control Registers */
#define kCanIntcEIMKNeg                ((vuint8) 0x7Fu)    /*!< Disables the interrupt processing in the EI Level Interrupt Control Registers */
#define kCanIntcEIRF                   ((vuint8) 0x10u)    /*!< Compare value to determine whether the interrupt request flag is set in the EI Level Interrupt Control Registers */
#define kCanIntcEIRFNeg                ((vuint8) 0xEFu)    /*!< Clears the interrupt request flag in the EI Level Interrupt Control Registers */

/* RAM check */
#define CanLL_WriteRegRegSize          CanLL_WriteReg32
#define CanLL_WriteRegGlobalRegSize    CanLL_WriteRegGlobal32
#define CanMemCheckValuesRegSize       CanMemCheckValues32bit


/*!< Bitmaks for register RamCheck */
# if defined(C_ENABLE_IF_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN */
#  define kCanRamCheckMaskCGCFG        0xFFFFFF1Fu
# else
#  if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
#   define kCanRamCheckMaskCGCFG       0xFFFFFF3Fu
#  else
#   define kCanRamCheckMaskCGCFG       0xFFFFFFDFu
#  endif
# endif
# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
#  define kCanRamCheckMaskCGCR         0x00000F00u
# else
#  define kCanRamCheckMaskCGCR         0x00000700u
# endif
# if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
#  define kCanRamCheckMaskCRECR        0x0000013Fu
# else
#  define kCanRamCheckMaskCRECR        0x0000011Fu
# endif
# if (kCanMaxPhysChannels == 1u)
#  define kCanRamCheckMaskCRNCFG0      0xFF000000u
# elif (kCanMaxPhysChannels == 2u)
#  define kCanRamCheckMaskCRNCFG0      0xFFFF0000u
# elif (kCanMaxPhysChannels == 3u)
#  define kCanRamCheckMaskCRNCFG0      0xFFFFFF00u
# elif (kCanMaxPhysChannels >= 4u) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
#  define kCanRamCheckMaskCRNCFG0      0xFFFFFFFFu
# endif
# if (kCanMaxPhysChannels == 5u)
#  define kCanRamCheckMaskCRNCFG1      0xFF000000u
# elif (kCanMaxPhysChannels == 6u)
#  define kCanRamCheckMaskCRNCFG1      0xFFFF0000u
# elif (kCanMaxPhysChannels == 7u) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
#  define kCanRamCheckMaskCRNCFG1      0xFFFFFF00u
# elif (kCanMaxPhysChannels == 8u) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
#  define kCanRamCheckMaskCRNCFG1      0xFFFFFFFFu
# endif
# if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
#  define kCanRamCheckMaskCRBNUM       0x000007FFu
# else
#  if defined(C_ENABLE_CAN_FD_USED)
#   define kCanRamCheckMaskCRBNUM      0x000003FFu
#  else
#   define kCanRamCheckMaskCRBNUM      0x000000FFu
#  endif
# endif
# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
#  define kCanRamCheckMaskCRFCR        0x0000F772u
# if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
#  define kCanRamCheckMaskTRFCR        0xFFFFFF76u
# else
#  define kCanRamCheckMaskTRFCR        0xFFFFF776u
# endif
# else
#  define kCanRamCheckMaskCRFCR        0x0000F702u
#  define kCanRamCheckMaskTRFCR        0xFFFFF706u
# endif
# if defined(C_ENABLE_IF_RSCAN_FD) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD */
#  define kCanRamCheckMaskCGRMCFG      0x00000001u
# endif
# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
#  define kCanRamCheckMaskCGFDCFG      0x00000301u
#  define kCanRamCheckMaskCGCRCCFG     0x00000001u
# endif
# define kCanRamCheckMaskRuleCode      0xFFFFFFFFu
# define kCanRamCheckMaskRuleMask      0xDFFFFFFFu
# if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
#  define kCanRamCheckMaskRuleBuf      0xFFFFFF0Fu
# else
#  define kCanRamCheckMaskRuleBuf      0xFFFFFF00u
# endif
# if (kCanMaxPhysChannels == 1u)
#  define kCanRamCheckMaskRuleFifo     0x000007FFu
# elif (kCanMaxPhysChannels == 2u)
#  define kCanRamCheckMaskRuleFifo     0x00003FFFu
# elif (kCanMaxPhysChannels == 3u)
#  define kCanRamCheckMaskRuleFifo     0x0001FFFFu
# elif (kCanMaxPhysChannels == 4u)
#  define kCanRamCheckMaskRuleFifo     0x000FFFFFu
# elif (kCanMaxPhysChannels == 5u)
#  define kCanRamCheckMaskRuleFifo     0x007FFFFFu
# elif (kCanMaxPhysChannels == 6u) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
#  define kCanRamCheckMaskRuleFifo     0x03FFFFFFu
# elif (kCanMaxPhysChannels == 7u) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
#  define kCanRamCheckMaskRuleFifo     0x1FFFFFFFu
# elif (kCanMaxPhysChannels == 8u) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
#  define kCanRamCheckMaskRuleFifo     0xFFFFFFFFu
# endif
# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
#  define kCanRamCheckMaskBCFG         0x1F7FFBFFu
#  define kCanRamCheckMaskFDBCFG       0x077F00FFu
#  if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
#   define kCanRamCheckMaskFDCFG       0x777F0707u
#  else
#   define kCanRamCheckMaskFDCFG       0x3F7F0707u
#  endif
#  define kCanRamCheckMaskCR           0x00EFFF00u
# else
#  define kCanRamCheckMaskBCFG         0x037F03FFu
#  define kCanRamCheckMaskCR           0x00E1FF00u
# endif


/* *********************************************************************** */
/* Compatibility                                                           */
/* *********************************************************************** */
#define tCanIntCnt                     vuint8
#define tCanLoopRet                    Can_ReturnType


 tCanBufPtr               SendBuf;    //发送数据

 volatile uint8 Framedata=0xff,Framedata2=0xff,seq1=0,seq2=0,counter1=0,counter2=0;
/* *********************************************************************** */
/* SafeBSW check (LL)                                                      */
/* *********************************************************************** */
#if (CAN_SAFE_BSW == STD_ON)
# if !(CAN_SLEEP_SUPPORT == STD_ON)                                                         || \
     !defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST)                                               || \
     ((CAN_GET_STATUS == STD_ON) && !defined(C_ENABLE_EXTENDED_STATUS))                     || \
     !defined(C_HL_ENABLE_OVERRUN_IN_STATUS)                                                || \
     (defined(C_ENABLE_RX_FULLCAN_OBJECTS) && !defined(C_ENABLE_RX_FULLCAN_POLLING))        || \
     (defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL))
#  error "SafeBSW: An unsupported feature is active!"
# endif
#endif

/* *********************************************************************** */
/* MISRA deviations                                                        */
/* *********************************************************************** */
/* PRQA S 0303 EOF */ /* MD_Can_HwAccess */

/***************************************************************************/
/* macros                                                                  */
/***************************************************************************/
/* PRQA S 3453 FctLikeMacroLabel */ /* MD_MSR_FctLikeMacro */

/* for LL compatibility */
/* hw handles */
#define CAN_HL_HW_TX_NORMAL_INDEX(hwch)     (Can_GetTxBasicHwStart(hwch)) 
#if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST) /* COV_CAN_HW_LAYOUT_TXBASIC_FIRST */
# define CAN_HL_HW_TX_STARTINDEX(hwch)      (Can_GetTxBasicHwStart(hwch))
#endif
#define CAN_HL_HW_TX_FULL_STARTINDEX(hwch)  (Can_GetTxFullHwStart(hwch))
#define CAN_HL_HW_UNUSED_STARTINDEX(hwch)   (Can_GetUnusedHwStart(hwch))
#define CAN_HL_HW_RX_FULL_STARTINDEX(hwch)  (Can_GetRxFullHwStart(hwch))
#define CAN_HL_HW_RX_BASIC_STARTINDEX(hwch) (Can_GetRxBasicHwStart(hwch))
#if defined(CAN_HL_HW_LAYOUT_TXBASIC_FIRST) /* COV_CAN_HW_LAYOUT_TXBASIC_FIRST */
# define CAN_HL_HW_TX_STOPINDEX(hwch)       (Can_GetTxFullHwStop(hwch))
#endif
#define CAN_HL_HW_TX_FULL_STOPINDEX(hwch)   (Can_GetTxFullHwStop(hwch))
#define CAN_HL_HW_UNUSED_STOPINDEX(hwch)    (Can_GetUnusedHwStop(hwch))
#define CAN_HL_HW_RX_FULL_STOPINDEX(hwch)   (Can_GetRxFullHwStop(hwch))
#define CAN_HL_HW_RX_BASIC_STOPINDEX(hwch)  (Can_GetRxBasicHwStop(hwch))
/* mailbox handles */
#define CAN_HL_MB_RX_FULL_STARTINDEX(hwch)  (Can_GetRxFullHandleStart(hwch))
#define CAN_HL_MB_RX_BASIC_STARTINDEX(hwch) (Can_GetRxBasicHandleStart(hwch))
#define CAN_HL_MB_TX_FULL_STARTINDEX(hwch)  (Can_GetTxFullHandleStart(hwch))
#define CAN_HL_MB_TX_BASIC_STARTINDEX(hwch) (Can_GetTxBasicHandleStart(hwch))
#define CAN_HL_MB_RX_FULL_STOPINDEX(hwch)   (Can_GetRxFullHandleStop(hwch))
#define CAN_HL_MB_RX_BASIC_STOPINDEX(hwch)  (Can_GetRxBasicHandleStop(hwch))
#define CAN_HL_MB_TX_FULL_STOPINDEX(hwch)   (Can_GetTxFullHandleStop(hwch))
#define CAN_HL_MB_TX_BASIC_STOPINDEX(hwch)  (Can_GetTxBasicHandleStop(hwch))

#if defined(C_ENABLE_CAN_RAM_CHECK)
# if !defined(CAN_RAM_CHECK_MAILBOX_RESULT) /* May be defined by test suite to stimulate RAM_CHECK failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_MAILBOX_RESULT(ch, initParaPtr) CanLL_InitIsMailboxCorrupt((initParaPtr))
#  else
#   define CAN_RAM_CHECK_MAILBOX_RESULT(ch, initParaPtr) CanLL_InitIsMailboxCorrupt((ch), (initParaPtr))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_FINISHED_CTP) /* May be defined by test suite to check RAM_CHECK finished / executed */
#  define CAN_RAM_CHECK_FINISHED_CTP(ch)
# endif
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
# if !defined(CAN_RAM_CHECK_BEGIN_REG_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_BEGIN_REG_RESULT(ch, initParaPtr) CanLL_InitBeginIsRegisterCorrupt((initParaPtr))
#  else
#   define CAN_RAM_CHECK_BEGIN_REG_RESULT(ch, initParaPtr) CanLL_InitBeginIsRegisterCorrupt((ch), (initParaPtr))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_END_REG_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   define CAN_RAM_CHECK_END_REG_RESULT(ch, initParaPtr) CanLL_InitEndIsRegisterCorrupt((initParaPtr))
#  else
#   define CAN_RAM_CHECK_END_REG_RESULT(ch, initParaPtr) CanLL_InitEndIsRegisterCorrupt((ch), (initParaPtr))
#  endif
# endif
# if !defined(CAN_RAM_CHECK_READ_BACK_RESULT) /* May be defined by test suite to stimulate RAM_CHECK_EXTENDED failure */
#  define CAN_RAM_CHECK_READ_BACK_RESULT(ch)
# endif
#endif

#define CanHL_IsStart(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_START) == CAN_STATUS_START)
#define CanHL_IsSleep(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_SLEEP) == CAN_STATUS_SLEEP)
#define CanHL_IsStop(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_STOP) == CAN_STATUS_STOP)
#define CanHL_IsBusOff(ch) (Can_IsIsBusOff(ch))
#define CanHL_IsControllerInit(ch) ((Can_GetLogStatus(ch) & CAN_STATUS_INIT) == CAN_STATUS_INIT)

#if defined(C_ENABLE_CAN_FD_USED) /* also for BRS because DLC may be bigger than 8 and will be checked by CanIf */
# define CAN_DLC2LEN(dlc) (Can_DlcToFrameLenght[((uint8)(dlc)) & ((uint8)0xFu)])
# define CAN_LEN2DLC(length) ((uint8)Can_MessageLengthToDlc[(length)])
#else
# define CAN_DLC2LEN(dlc) (dlc)
# define CAN_LEN2DLC(length) (length)
#endif
#if defined(C_ENABLE_CAN_FD_FULL)
# define CAN_MAX_DATALEN_OBJ(Index) Can_GetMailboxDataLen(Index)
#else
# define CAN_MAX_DATALEN_OBJ(Index) 8u
#endif
#define CanHL_IsFdMessage(id) (((id) & (Can_IdType)CAN_ID_FD_MASK) == (Can_IdType)CAN_ID_FD_MASK) /* \trace SPEC-60432, SPEC-50586 */
#define CanHL_IsFdTxBrs(ch)   (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(ch)) == CAN_FD_RXTX) /* \trace SPEC-60432, SPEC-50586 */

/* PRQA L:FctLikeMacroLabel */

/* PRQA S 3453 QAC_CanLL_FctLikeMacro */ /* MD_MSR_FctLikeMacro */

#if defined(C_SINGLE_PHYS_CHANNEL)
# define canPhysChannel                      kCanLogToPhys
#endif

/* creates a 32bit mask for a single bit */
#define CanLL_SL32(num) \
  ((vuint32) (((vuint32)0x00000001u)<<((vuint8)(num)&0x1Fu)))

/* creates a 16bit mask for a single bit */
#define CanLL_SL16(num) \
  ((vuint16) (((vuint16)0x0001u)<<((vuint8)(num)&0x0Fu)))

/* creates a 8bit mask for a single bit */
#define CanLL_SL8(num) \
  ((vuint8) (((vuint8)0x01u)<<((vuint8)(num)&0x07u)))

/* creates a mask for a single bit within a shared register */
#define CanLL_SLRS(num) \
  CanLL_SL32(num)

/* returns the registerindex for a bit in a shared register */
#define CanLL_BitIndex(num) \
  (((num)>>5)&0x03u)

/* creates a mask to clear a bit in a shared register */
#define CanLL_ClearBitRS(num) \
  ((kCanRegSizeCast) ~CanLL_SLRS(num))

/* creates a mask to set a bit in a shared register */
#define CanLL_SetBitRS(num) \
  ((kCanRegSizeCast) CanLL_SLRS(num))

/* returns the registerindex of a channel dependent byte in a shared register */
#define CanLL_ByteIndex(pch) \
  (((pch)>>2)&0x01u)

/* creates a mask for a channel dependent word in a tx register */
#if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
# define CanLL_TxMaskWord(pch) \
  ((kCanRegSize)kCanOne32)
#else
# define CanLL_TxMaskWord(pch) \
  ((kCanRegSize)(((kCanRegSize)0x0000FFFFu)<<(((pch)&0x01u)<<4)))
#endif

/* returns a channel dependent word from a tx register */
#if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
# define CanLL_TxSharedRegToWord(pch, val) \
  ((kCanTxSize)(val))
#else
# define CanLL_TxSharedRegToWord(pch, val) \
  ((kCanTxSize)(((kCanRegSize)(val))>>(((pch)&0x01u)<<4)))
#endif

/* returns a tx register value for a channel dependent word */
#if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
# define CanLL_TxWordToSharedReg(pch, val) \
  ((kCanRegSize)(val))
#else
# define CanLL_TxWordToSharedReg(pch, val) \
  ((kCanRegSize)(((kCanRegSize)(val))<<(((pch)&0x01u)<<4)))
#endif

/* returns the tx registerindex of a channel dependent word */
#if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
# define CanLL_TxWordIndex(pch) \
  ((pch)&0x07u)
#else
# define CanLL_TxWordIndex(pch) \
  (((pch)>>1)&0x03u)
#endif

/* creates a mask for a single bit within kCanTxSize */
#if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
# define CanLL_SLTS(num) \
  CanLL_SL32(num)
#else
# define CanLL_SLTS(num) \
  CanLL_SL16(num)
#endif

/* creates a mask to clear a channel dependent word in a tx register */
#define CanLL_TxMaskWordClear(pch) \
  ((kCanRegSize) ~CanLL_TxMaskWord(pch))

/* creates a mask to clear a bit within kCanTxSize */
#define CanLL_ClearBitTS(num) \
  ((kCanTxSize) ~CanLL_SLTS(num))

/* creates a mask to set a bit within kCanTxSize */
#define CanLL_SetBitTS(num) \
  ((kCanTxSize) CanLL_SLTS(num))

/* returns a shared register value for a channel dependent byte */
#define CanLL_FilterListConfig(pch, val) \
  (kCanRegSize)(((kCanRegSize)(val)) << (24u-(((pch)&0x03u)<<3)))

/* requests a mode on a logical channel */
#define CanLL_ModeReq_Log(ch, mode) \
  (Can->ChCtrl[mCanLogToPhys(ch)].CR = ((Can->ChCtrl[mCanLogToPhys(ch)].CR & kCanModeMask) | (mode)))

/* checks the mode on a logical channel */
#define CanLL_ModeCheck_Log(ch, mode) \
  ((Can->ChCtrl[mCanLogToPhys(ch)].SR & kCanModeBits) == (mode))

/* requests a mode on a physical channel */
#define CanLL_ModeReq_Phys(pch, mode) \
  (Can->ChCtrl[pch].CR = ((Can->ChCtrl[pch].CR & kCanModeMask) | (mode)))

/* checks the mode on a physical channel */
#define CanLL_ModeCheck_Phys(pch, mode) \
  ((Can->ChCtrl[pch].SR & kCanModeBits) == (mode))

/* requests a global mode */
#define CanLL_GlobalModeReq(mode) \
  (Can->CGCR = ((Can->CGCR & kCanModeMask) | (mode)))

/* checks the global mode (also checks if RAMIST==0) */
#define CanLL_GlobalModeCheck(mode) \
  (Can->CGSR == (mode))

/* interrupt controller access */
#if defined(C_ENABLE_LL_CAN_INTCTRL) || defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL)
# if defined(C_ENABLE_INTC_ACCESS_BY_APPL)

#  define CanLL_IntcIntEnable(id, reg) \
  ApplCanWriteIcr8((vuint32)(&(reg)), (vuint8)(ApplCanReadIcr8((vuint32)(&(reg))) & kCanIntcEIMKNeg))

#  define CanLL_IntcIntEnableLoc(reg) \
  ((reg) &= kCanIntcEIMKNeg)

#  define CanLL_IntcIntDisable(id, reg) \
  ApplCanWriteIcr8((vuint32)(&(reg)), (vuint8)(ApplCanReadIcr8((vuint32)(&(reg))) | kCanIntcEIMK))

#  define CanLL_IntcIntDisableLoc(reg) \
  ((reg) |= kCanIntcEIMK)

#  define CanLL_IntcIntFlag(id, reg) \
  ((ApplCanReadIcr8((vuint32)(&(reg))) & kCanIntcEIRF) == kCanIntcEIRF)

#  define CanLL_IntcIntClear(id, reg) \
  ApplCanWriteIcr8((vuint32)(&(reg)), (vuint8)(ApplCanReadIcr8((vuint32)(&(reg))) & kCanIntcEIRFNeg))

#  define CanLL_IntcIntSave(id, dst, src) \
  ((dst) = ApplCanReadIcr8((vuint32)(&(src))))

#  define CanLL_IntcIntRestore(id, dst, src) \
  ApplCanWriteIcr8((vuint32)(&(dst)), (vuint8)(src))

# elif defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)

#  define CanLL_IntcIntEnable(id, reg) \
  (void)osEnableInterruptSource((id), TRUE)

#  define CanLL_IntcIntEnableLoc(reg) \
  ((reg) = TRUE)

#  define CanLL_IntcIntDisable(id, reg) \
  (void)osDisableInterruptSource(id)

#  define CanLL_IntcIntDisableLoc(reg) \
  ((reg) = FALSE)

#  define CanLL_IntcIntFlag(id, reg) \
  (CanLL_OsIsInterruptPending(id) == TRUE)

#  define CanLL_IntcIntClear(id, reg) \
  (void)osClearPendingInterrupt(id)

#  define CanLL_IntcIntSave(id, dst, src) \
  ((dst) = (vuint8)CanLL_OsIsInterruptSourceEnabled(id))

#  define CanLL_IntcIntRestore(id, dst, src) \
  CanLL_OsRestoreInterruptSource((id), (boolean)(src))

# else /* C_ENABLE_INTC_ACCESS_BY_DRIVER */

/* configures a ICR to enable the interrupt source */
#  define CanLL_IntcIntEnable(id, reg) \
  ((reg) &= kCanIntcEIMKNeg)

/* configures the status-var to enable the interrupt source */
#  define CanLL_IntcIntEnableLoc(reg) \
  ((reg) &= kCanIntcEIMKNeg)

/* configures a ICR to disable the interrupt source */
#  define CanLL_IntcIntDisable(id, reg) \
  ((reg) |= kCanIntcEIMK)

/* configures the status-var to disable the interrupt source */
#  define CanLL_IntcIntDisableLoc(reg) \
  ((reg) |= kCanIntcEIMK)

/* is true if the interrupt request flag is set within a ICR */
#  define CanLL_IntcIntFlag(id, reg) \
  (((reg) & kCanIntcEIRF) == kCanIntcEIRF)

/* clears the interrupt request flag within a ICR */
#  define CanLL_IntcIntClear(id, reg) \
  ((reg) &= kCanIntcEIRFNeg)

/* saves interrupt status from a ICR (src) to a status-var (dst) */
#  define CanLL_IntcIntSave(id, dst, src) \
  ((dst) = (src))

/* restores interrupt status from a status-var (src) to a ICR (dst) */
#  define CanLL_IntcIntRestore(id, dst, src) \
  ((dst) = (src))

# endif /* C_ENABLE_INTC_ACCESS_BY_* */
#endif /* C_ENABLE_LL_CAN_INTCTRL || C_ENABLE_LL_CAN_WAKEUP_INTCTRL */

/*
|<DataModelStart>| CanLL_HwIsSleep
Relation_Context:
# CanLL_HwIsSleep() #
Relation:
Wakeup, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#if defined(C_ENABLE_SLEEP_WAKEUP)
# define CanLL_HwIsSleep(hwCh) \
  (CanLL_ModeCheck_Log((hwCh), kCanStopMode))
#else
# define CanLL_HwIsSleep(hwCh) \
  (kCanFalse != kCanFalse)
#endif /* C_ENABLE_SLEEP_WAKEUP */

/*
|<DataModelStart>| CanLL_HwIsStop
Relation_Context:
# Can_GetStatus() #
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_HwIsStop(hwCh) \
  (CanLL_ModeCheck_Log((hwCh), kCanResetMode) || CanLL_ModeCheck_Log((hwCh), kCanHaltMode))

/*
|<DataModelStart>| CanLL_HwIsBusOff
Relation_Context:
# CanLL_ModeTransition() #
# Can_GetStatus() #
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_HwIsBusOff(hwCh) \
	 0
  ///((Can->ChCtrl[mCanLogToPhys(hwCh)].SR & kCanSrMaskBusoff) == kCanSrMaskBusoff)

/*
|<DataModelStart>| CanLL_HwWasBusOff
Relation_Context:
# CanLL_BusOffOcured() #
Relation:
OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
#define CanLL_HwWasBusOff(hwCh) \
  ((Can->ChCtrl[mCanLogToPhys(hwCh)].EF & kCanEfMaskBusoff) == kCanEfMaskBusoff)

#if defined(C_ENABLE_EXTENDED_STATUS)
/*
|<DataModelStart>| CanLL_HwIsPassive
Relation_Context:
# Can_GetStatus() #
Relation:
CanGetStatus, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
# define CanLL_HwIsPassive(hwCh) \
	0
 // ((Can->ChCtrl[mCanLogToPhys(hwCh)].SR & kCanSrMaskPassive) == kCanSrMaskPassive)

/*
|<DataModelStart>| CanLL_HwIsWarning
Relation_Context:
# Can_GetStatus() #
Relation:
CanGetStatus, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
# if defined(C_MULTIPLE_RECEIVE_CHANNEL)
#  define CanLL_HwIsWarning(hwCh) \
  (((CanRxActualErrorCounter(hwCh) >= (96u)) && (CanRxActualErrorCounter(hwCh) < (128u))) || \
   ((CanTxActualErrorCounter(hwCh) >= (96u)) && (CanTxActualErrorCounter(hwCh) < (128u))))
# else
#  define CanLL_HwIsWarning(hwCh) \
  (((CanRxActualErrorCounter() >= (96u)) && (CanRxActualErrorCounter() < (128u))) || \
   ((CanTxActualErrorCounter() >= (96u)) && (CanTxActualErrorCounter() < (128u))))
# endif
#endif /* C_ENABLE_EXTENDED_STATUS */

#if defined(C_MULTIPLE_RECEIVE_CHANNEL)
# define CanLL_ApplCanTimerStart(loop)   ApplCanTimerStart(channel, loop)
# define CanLL_ApplCanTimerEnd(loop)     ApplCanTimerEnd(channel, loop)
# define CanLL_ApplCanTimerLoop(loop)    ApplCanTimerLoop(channel, loop)
#else
# define CanLL_ApplCanTimerStart(loop)   ApplCanTimerStart(loop)
# define CanLL_ApplCanTimerEnd(loop)     ApplCanTimerEnd(loop)
# define CanLL_ApplCanTimerLoop(loop)    ApplCanTimerLoop(loop)
#endif /* C_MULTIPLE_RECEIVE_CHANNEL */

#if defined(C_ENABLE_HW_LOOP_TIMER)
# define CanLL_CanTimerStart(loop)       CanLL_ApplCanTimerStart(loop)
# define CanLL_CanTimerEnd(loop)         CanLL_ApplCanTimerEnd(loop)
# define CanLL_CanTimerLoop(loop)        CanLL_ApplCanTimerLoop(loop)
#else /* C_ENABLE_HW_LOOP_TIMER */
# define CanLL_CanTimerStart(loop)
# define CanLL_CanTimerEnd(loop)
# define CanLL_CanTimerLoop(loop)        CAN_OK
#endif /* C_ENABLE_HW_LOOP_TIMER */




#if (CAN_RUNTIME_MEASUREMENT_SUPPORT == STD_ON)
# define CanLL_RtmStart(point)           Rtm_Start(RtmConf_RtmMeasurementPoint_##point) /* PRQA S 0342 */ /* MD_Can_Concatenation_LL */
# define CanLL_RtmStop(point)            Rtm_Stop(RtmConf_RtmMeasurementPoint_##point)  /* PRQA S 0342 */ /* MD_Can_Concatenation_LL */
#else
# define CanLL_RtmStart(point)
# define CanLL_RtmStop(point)
#endif

/* PRQA L:QAC_CanLL_FctLikeMacro */

/***************************************************************************/
/* Constants                                                               */
/***************************************************************************/
#define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* BR:012 */
V_DEF_CONST(V_NONE, uint8, CONST) Can_MainVersion         = (uint8)CAN_SW_MAJOR_VERSION; /* PRQA S 3408 */ /* MD_Can_ExternalScope */
V_DEF_CONST(V_NONE, uint8, CONST) Can_SubVersion          = (uint8)CAN_SW_MINOR_VERSION; /* PRQA S 3408 */ /* MD_Can_ExternalScope */
V_DEF_CONST(V_NONE, uint8, CONST) Can_ReleaseVersion      = (uint8)CAN_SW_PATCH_VERSION; /* PRQA S 3408 */ /* MD_Can_ExternalScope */


#if defined(C_ENABLE_CAN_FD_USED)
V_DEF_CONST(CAN_STATIC, uint8, CONST) Can_DlcToFrameLenght[16] =
{
  0u,  1u,  2u,  3u,
  4u,  5u,  6u,  7u,
  8u, 12u, 16u, 20u,
 24u, 32u, 48u, 64u
};
V_DEF_CONST(CAN_STATIC, uint8, CONST) Can_MessageLengthToDlc[65] =
{
/* 00..07 */  0u,  1u,  2u,  3u,  4u,  5u,  6u,  7u,
/* 08..15 */  8u,  9u,  9u,  9u,  9u, 10u, 10u, 10u,
/* 16..23 */ 10u, 11u, 11u, 11u, 11u, 12u, 12u, 12u,
/* 24..31 */ 12u, 13u, 13u, 13u, 13u, 13u, 13u, 13u,
/* 32..39 */ 13u, 14u, 14u, 14u, 14u, 14u, 14u, 14u,
/* 40..47 */ 14u, 14u, 14u, 14u, 14u, 14u, 14u, 14u,
/* 48..55 */ 14u, 15u, 15u, 15u, 15u, 15u, 15u, 15u,
/* 56..63 */ 15u, 15u, 15u, 15u, 15u, 15u, 15u, 15u,
/* 64     */ 15u
};
#endif

/* Global constants with CAN driver main and subversion */

#if defined(C_ENABLE_CAN_RAM_CHECK) 
/* ROM CATEGORY 4 START */
V_DEF_CONST(CAN_STATIC, vuint32, CONST) CanMemCheckValues32bit[3] = /* PRQA S 3218 */ /* MD_Can_GlobalScope */
{
  0xAAAAAAAAUL, 0x55555555UL, 0x00000000UL
};
/* ROM CATEGORY 4 END */
#endif

#define CAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***************************************************************************/
/* global data definitions                                                 */
/***************************************************************************/
#define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED  /*---------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/***************************************************************************************/
/* local data definitions   (need also INFIX because STATIC may be defined to nothing) */
/***************************************************************************************/
/* \trace SPEC-1585 */
/*! Semaphore to block reentrancy for Can_MainFunction_Read() */
V_DEF_VAR(CAN_STATIC, uint8, VAR_NOINIT) canIsRxTaskLocked;
#if defined(C_ENABLE_RX_QUEUE)
V_DEF_VAR(CAN_STATIC, uint16, VAR_NOINIT) canRxQueueMaxDataSize; /* PRQA S 3218 */ /* MD_Can_GlobalScope */
#endif

# if defined(C_ENABLE_LL_CAN_INTCTRL)
/* RAM CATEGORY 1 START */
V_DEF_VAR(CAN_STATIC, tCanLLCanGlobalIntOld, VAR_NOINIT) canInterruptOldFlag;
/* RAM CATEGORY 1 END */
# endif
#if defined(C_ENABLE_GLOBAL_INIT_POST_PROCESS)
/* RAM CATEGORY 4 START */
V_DEF_VAR(CAN_STATIC, vuint8, VAR_NOINIT) CanAddFilterRulesStartPage;
/* RAM CATEGORY 4 END */
/* RAM CATEGORY 4 START */
V_DEF_VAR(CAN_STATIC, vuint8, VAR_NOINIT) CanAddFilterRulesStartIndex;
/* RAM CATEGORY 4 END */
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
/* RAM CATEGORY 4 START */
V_DEF_VAR(CAN_STATIC, vuint8, VAR_NOINIT) canIsCellCorrupt;
/* RAM CATEGORY 4 END */
#endif
#if (CAN_SAFE_BSW == STD_ON)
/* RAM CATEGORY 4 START */
V_DEF_VAR(CAN_STATIC, tCanDummyBuf, VAR_NOINIT) CanLL_DummyBuf; /* PRQA S 3218 */ /* MD_Can_GlobalScope */
/* RAM CATEGORY 4 END */
#endif

#define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED  /*----------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* ! Mark module to be initialized (used to check double/none initialization) */
V_DEF_VAR(CAN_STATIC, uint8, VAR_INIT) canConfigInitFlag = CAN_STATUS_UNINIT;
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/* not static because of debug/test usage */
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER)
# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! Pointer to the current configuration */
V_DEF_P2CONST (V_NONE, Can_ConfigType, VAR_INIT, CONST_PBCFG) Can_ConfigDataPtr = NULL_PTR; /* UREQ00035484 */ /* PRQA S 3408 */ /* MD_Can_ExternalScope */
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#else
# define CAN_START_SEC_CONST_UNSPECIFIED  /*--------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*! Pointer to the current configuration */
V_DEF_CONSTP2CONST(V_NONE, Can_ConfigType, CONST, CONST_PBCFG) Can_ConfigDataPtr = NULL_PTR; /* PRQA S 3408,1514 */ /* MD_Can_ExternalScope */
# define CAN_STOP_SEC_CONST_UNSPECIFIED  /*---------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

/***************************************************************************/
/*  Safe Check                                                             */
/***************************************************************************/
#if !defined(CAN_SAFE_BSW) /* COV_CAN_COMPATIBILITY */
# define CAN_SAFE_BSW   STD_OFF
#else
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
#  if (CAN_DEV_ERROR_DETECT == STD_OFF) || (CAN_AMD_RUNTIME_MEASUREMENT == STD_ON) /* COV_CAN_SAFE_BSW_EXCLUSION */
#   error "Unsupported Feature activated for SafeBSW"
#  endif
# endif
#endif

/***************************************************************************/
/*  Error Check                                                            */
/***************************************************************************/
#if (CAN_TRANSMIT_BUFFER == STD_OFF) && defined(C_ENABLE_CANCEL_IN_HW)
# error "C_ENABLE_CANCEL_IN_HW need CAN_TRANSMIT_BUFFER == STD_ON (no FIFO buffering but PRIO_BY_CANID in CanIf) -> check Generated data"
#endif
#if !defined(C_ENABLE_SLEEP_WAKEUP)
# if (CAN_SLEEP_SUPPORT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON)
#  error "C_ENABLE_SLEEP_WAKEUP organified but generated like supported"
# endif
#endif
#if (CAN_WAKEUP_SUPPORT == STD_ON) && (CAN_SLEEP_SUPPORT == STD_OFF)
# error "activated CAN_WAKEUP_SUPPORT need activated CAN_SLEEP_SUPPORT"
#endif
#if defined(C_ENABLE_HW_LOOP_TIMER)
# if (CAN_LOOP_MAX == 0)
#  error "CAN_LOOP_MAX should not be generated as 0"
# endif
#else
# if (CAN_HARDWARE_CANCELLATION == STD_ON)
#  error "C_ENABLE_HW_LOOP_TIMER organified but generated like supported"
# endif
#endif
#if defined(C_ENABLE_CANCEL_IN_HW)
#else
# if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
#  error "C_ENABLE_CANCEL_IN_HW organified but generated like supported"
# endif
#endif
#if (CAN_MIRROR_MODE == STD_ON) && (!defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2) || (CAN_GENERIC_PRECOPY == STD_OFF))
# error "CAN_MIRROR_MODE need CAN_GENERIC_CONFIRMATION with CAN_API2 and CAN_GENERIC_PRECOPY as STD_ON"
#endif
#if (CAN_MULTIPLE_BASICCAN_TX == STD_ON)
# if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
/* cancellation does not work in CanHL_WritePrepareCancelTx for multiple BasicCAN messages, and is not useful for FIFO queue in CanIf (normally combined with multiple BCAN)*/
# error "CAN_MULTIPLE_BASICCAN_TX and CAN_HW_TRANSMIT_CANCELLATION are STD_ON but this combination is not supported"
# endif
#endif

#if ((kCanMaxPhysChannels > kCanMaxPhysChannelsCell)           || /* CM_CAN_LL04 */ \
     (kCanMaxRxFifos > kCanMaxRxFifosCell)                     || /* CM_CAN_LL05 */ \
     (kCanMaxTxBuf > kCanMaxTxBufCell)                         || /* CM_CAN_LL06 */ \
     (kCanMaxTxFifos > kCanMaxTxFifosCell)                     || /* CM_CAN_LL07 */ \
     (kCanMaxRxBuf > kCanMaxRxBufCell)                         ||                   \
     (kCanNumberOfSharedReg16 > ((kCanMaxPhysChannels+1)>>1)))    /* CM_CAN_LL08 */
# error "Configuration exceeds RSCAN limitations, check the derivative data!"
#endif

#if ((kCanBaseAdr == 0u)                                       || \
     (kCanMaxPhysChannels == 0u)                               || \
     (kCanMaxRxFifos == 0u)                                    || \
     (kCanMaxTxBuf == 0u)                                      || \
     (kCanMaxTxFifos == 0u)                                    || \
     (kCanMaxRxBuf == 0u)                                      || \
     (kCanNumberOfSharedReg16 == 0u))
# error "General configuration error!"
#endif

# if defined(C_ENABLE_LL_CAN_INTCTRL)
#  if ((kCanIntcRxFifoBaseAdr == 0u)                           || \
       (kCanIntcGErrorBaseAdr == 0u))
#   error "Interrupt control register address configuration error!"
#  endif
# endif

#if !defined(C_ENABLE_IF_RSCAN) && !defined(C_ENABLE_IF_RSCAN_FD) && !defined(C_ENABLE_IF_RSCAN_FD_V3)
# error "CAN interface is not defined!"
#endif
# if defined(C_ENABLE_IF_RSCAN) && defined(C_ENABLE_IF_RSCAN_FD)
#  error "Configuration of CAN interface is ambiguous!"
# endif
# if defined(C_ENABLE_IF_RSCAN) && defined(C_ENABLE_IF_RSCAN_FD_V3)
#  error "Configuration of CAN interface is ambiguous!"
# endif
# if defined(C_ENABLE_IF_RSCAN_FD) && defined(C_ENABLE_IF_RSCAN_FD_V3)
#  error "Configuration of CAN interface is ambiguous!"
# endif
# if defined(C_ENABLE_CAN_FD_USED)
#  if defined(C_ENABLE_IF_RSCAN)
#   error "Usage of CAN-FD requires a RSCAN-FD hardware interface, check the configuration or used derivative!"
#  endif
# endif

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
# if !defined(C_ENABLE_RX_FULLCAN_POLLING)
#  error "Rx FullCANs cannot be processed in interrupt context!"
# endif
#endif

#if defined(C_ENABLE_NESTED_INTERRUPTS)
# if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2)
#  error "Nesting of category 2 CAN interrupts must not be enabled by the driver!"
# endif
# if defined(C_ENABLE_ISRVOID)
#  error "Nesting of void-void CAN interrupts must not be enabled by the driver!"
# endif
#endif


# if defined(C_ENABLE_SLEEP_WAKEUP)
#  if !defined(C_ENABLE_BUSWAKEUP_SUPPORT)
#   error "Sleep/Wakeup functionality is not supported for this derivative!"
#  endif
# endif

#if defined(C_ENABLE_TX_HW_FIFO)
# if defined(C_ENABLE_CANCEL_IN_HW)
#  error "'Hardware (Transmit) Cancellation' is not supported if Tx Fifos are enabled!"
# endif
#endif


/***************************************************************************/
/*  Functions                                                              */
/***************************************************************************/
#define CAN_START_SEC_STATIC_CODE  /*--------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define CanHL_ApplCanTimerStart( timerIdx )  ApplCanTimerStart( timerIdx );
#  define CanHL_ApplCanTimerEnd( timerIdx )    ApplCanTimerEnd( timerIdx );
# else
#  define CanHL_ApplCanTimerStart( timerIdx )  ApplCanTimerStart( channel, (timerIdx) );
#  define CanHL_ApplCanTimerEnd( timerIdx )    ApplCanTimerEnd( channel, (timerIdx) );
# endif
# define CanHL_ApplCanTimerLoop( timerIdx )   if (ApplCanTimerLoop(CAN_CHANNEL_CANPARA_FIRST (timerIdx)) != CAN_OK) \
                                              { \
                                                break; \
                                              }

# if (CAN_HW_LOOP_SUPPORT_API == STD_OFF)
/* Internal handling of HW loops (like AutoSar) - otherwise ApplCanTimer... is defined an implemented by Application */
/****************************************************************************
| NAME:             ApplCanTimerStart
****************************************************************************/
/* Used as macro to save runtime and code */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
/* \trace SPEC-1640 */
#    define ApplCanTimerStart(source)     ((void)GetCounterValue( CAN_OS_COUNTER_ID, &Can_GetCanLoopTimeout(0, (source)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  else
#    define ApplCanTimerStart(ch, source) ((void)GetCounterValue( CAN_OS_COUNTER_ID, &Can_GetCanLoopTimeout((ch), (source)))) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif
/****************************************************************************
| NAME:             ApplCanTimerLoop
****************************************************************************/
/*
|<DataModelStart>| ApplCanTimerLoop
Relation_Context:
# from mode transition + any LL #
HardwareLoopCheck, HardwareCancelByAppl
Relation:
DevErrorDetect, OneChOpt
HardwareLoopCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) ApplCanTimerLoop( CAN_CHANNEL_CANTYPE_FIRST uint8 source )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  uint8 errorId;
  uint8 apiId;
  errorId = CAN_E_NO_ERROR;
  apiId = CAN_HW_ACCESS_ID;
  retval = CAN_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and source is valid (no INIT check because may be used inside power on INIT) */
  if (source > CAN_LOOP_MAX) /* CM_CAN_HL22 */
  {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    TickType elapsedTime;
    TickType startTime;
    /* #110 Calculate the elapsed since time the start of this hardware loop (identified by parameter source). */
    /* Get start time (set by ApplCanTimerStart - temporary variable because GetElapsedValue modify original data */
    startTime = Can_GetCanLoopTimeout(channel, source);
    /* Get elapsed time - from start time to now */
    /* #120 Throw DET error when GetElapsedValue() failed */
    if ( GetElapsedValue( CAN_OS_COUNTER_ID, &startTime, &elapsedTime ) != (StatusType)E_OK ) /* SBSW_CAN_HL37 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_TIMEOUT_DET;
    }
    else
    {
      /* #130 Check if time out occurs for HW loop checks (none mode transition) \trace SPEC-1594 */
      if ( (TickType)CAN_OS_TICK2MS( elapsedTime ) < (TickType)CAN_TIMEOUT_DURATION ) /* COV_CAN_HARDWARE_FAILURE */
      { /* no time out occur return OK */
        retval = CAN_OK;
      }
#  if defined(C_ENABLE_HW_LOOP_TIMER)
      else
      { /* Mode Change synchronous & HW loop check */
        /* #140 Throw DET error and set hardware cancellation flag */
        if (source < CAN_LOOP_MAX) /* COV_CAN_HARDWARE_FAILURE */
        { 
          errorId = CAN_E_TIMEOUT_DET;
        }
      }
#  endif
    }
    CAN_DUMMY_STATEMENT(startTime); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)  
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(apiId, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(apiId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/****************************************************************************
| NAME:             ApplCanTimerEnd
****************************************************************************/
/* Used as macro to save runtime and code */
/* because of possible nested timers .. timer has to be reset */
#  define ApplCanTimerEnd ApplCanTimerStart
# endif /* (CAN_HW_LOOP_SUPPORT_API == STD_OFF) */



/****************************************************************************
| NAME:             CanHL_ReInit
****************************************************************************/
/*
|<DataModelStart>| CanHL_ReInit
Relation_Context:
# from CanHL_ModeTransition() #
Wakeup, OneChOpt, ChannelAmount
Relation:
DevErrorDetect, OneChOpt, ChannelAmount
DevErrorDetect, Variant, ChannelAmount
RamCheck
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport
Wakeup, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(CAN_STATIC, uint8, STATIC_CODE) CanHL_ReInit( CAN_HW_CHANNEL_CANTYPE_FIRST uint8 doRamCheck )
{ /* \trace SPEC-1719, SPEC-1589, SPEC-1346, SPEC-1565 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanInitParaStruct initPara;
  CanHookBegin_CanHL_ReInit();
  errorId = CAN_E_NO_ERROR;
  initPara.isInitOk = kCanOk;
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and Config pointer is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1718 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1713 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { /* \trace SPEC-1713 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 initialization controller states and initialization objects --- */
    initPara.initObject = Can_GetLastInitObject(channel);
#if defined(C_ENABLE_CAN_RAM_CHECK)
    initPara.doRamCheck = doRamCheck;
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    initPara.isChRamCheckFail = kCanFalse;
#endif
    /* #110 clean up status (do not activate communication and let SLEEP and initialization to detect ram-check request) */
#if defined(C_ENABLE_CAN_RAM_CHECK) && !defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    if (doRamCheck == kCanExecuteRamCheck)
    { /* #112 standard RAM check will be performed so delete old status CAN_DEACTIVATE_CONTROLLER but leave CAN_STATUS_INIT (info about PowerOn) */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)CAN_STATUS_INIT);  /* SBSW_CAN_HL02 */
    }
    else
#endif
    { /* #114 extended RAM check may be performed so delete old status except CAN_DEACTIVATE_CONTROLLER and CAN_STATUS_INIT */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & ((uint8)(CAN_DEACTIVATE_CONTROLLER) | (uint8)((uint8)CAN_STATUS_INIT)));  /* SBSW_CAN_HL02 */
    }
    /* #125 begin initialization CanHL_InitBegin() */
 ////////   initPara.isInitOk &= CanHL_InitBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */ /* PRQA S 2986 */ /* MD_Can_ConstValue */
    /* #130 block invalid hardware access (silent check) */
    if (initPara.isInitOk == kCanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
    {
#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
      /* #140 do TX FullCAN initialization CanHL_InitTxFullCAN()*/
   /////   initPara.isInitOk &= CanHL_InitTxFullCAN(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */
#endif
      /* #150 do TX BasicCAN initialization CanHL_InitTxBasicCAN() */
      initPara.isInitOk &= CanHL_InitTxBasicCAN(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */
#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
      /* #170 do RX FullCAN initialization CanHL_InitRxFullCAN() */
////      initPara.isInitOk &= CanHL_InitRxFullCAN(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */
#endif
#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
      /* #180 do RX BasicCAN initialization CanHL_InitRxBasicCAN() */
      initPara.isInitOk &= CanHL_InitRxBasicCAN(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */
#endif
      /* #190 end initialization CanHL_InitEnd_InitMode() */
 //////     initPara.isInitOk &= CanHL_InitEnd_InitMode(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &initPara); /* SBSW_CAN_HL31 */ /* PRQA S 2986 */ /* MD_Can_ConstValue */
#if defined(C_ENABLE_CAN_RAM_CHECK)
      if (doRamCheck == kCanExecuteRamCheck)
      { 
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
        /* #200 extended RamChecks new issue occur - notify corrupt register / deactivate controller */
        if (initPara.isChRamCheckFail == kCanTrue) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        {
          CanIf_RamCheckCorruptController((uint8)Can_GetCanToCanIfChannelMapping(channel));
          Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL02 */
        }
# else
        if( (Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) == CAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
        { /* #210 standard RAM check issue occur - call Appl_CanRamCheckFailed() (any mailbox fail) */
          if (Appl_CanRamCheckFailed((uint8)channel) != CAN_DEACTIVATE_CONTROLLER)
          { /* #220 let the application decide if communication stay disabled as set by RAM check or not */
            Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)(~(CAN_DEACTIVATE_CONTROLLER))); /* Application decide to activate communication in case RAM_CHECK failed */  /* SBSW_CAN_HL02 */
          }
        }
# endif
        CAN_RAM_CHECK_FINISHED_CTP(channel)
      }
#endif
    }
    if (initPara.isInitOk == kCanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
    { /* #280 set controller init flag when no issue occure before */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) | (CAN_STATUS_INIT)); /* SBSW_CAN_HL02 */
    }
    else
    { /* #275 set error when issue occure before */
      Can_SetLogStatus(channel, /* CAN_STATUS_UNINIT | */ (Can_GetLogStatus(channel) & (uint8)(CAN_DEACTIVATE_CONTROLLER))); /* SBSW_CAN_HL02 */
      errorId = CAN_E_UNINIT;
    }
#if defined(C_ENABLE_SLEEP_WAKEUP)
    if (Can_IsIsWakeup(channel)) /* \trace SPEC-15124 */ /* COV_CAN_HARDWARE_FAILURE */
    { /* #290 notify EcuM in case controller WAKEUP while initialization (LL: check before) \trace SPEC-15124 */
      Can_SetIsWakeup(channel, FALSE); /* SBSW_CAN_HL09 */
      EcuM_SetWakeupEvent(Can_GetWakeupSourceRef(channel));
    }
#endif
  } /* controller active in multiple ECU configuration */

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_INITCTR_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if !defined(C_ENABLE_CAN_RAM_CHECK)
  CAN_DUMMY_STATEMENT(doRamCheck); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_CanHL_ReInit();
  return initPara.isInitOk;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/****************************************************************************
| NAME:             CanHL_ModeTransition
****************************************************************************/
/*
|<DataModelStart>| CanHL_ModeTransition
Relation_Context:
# from Can_Init #
ChannelAmount
# from Can_Mainfunction_BusOff, CanHL_ErrorHandling #
StatusPolling, ChannelAmount
# from Can_ChangeBaudrate #
ChannelAmount
# from Can_SetBaudrate #
ChannelAmount
# from Can_SetControllerMode #
Wakeup
RamCheck
# from Can_RamCheckExecute #
RamCheck
# from Can_RamCheckEnableController #
RamCheck
Relation:
OneChOpt, HardwareLoopCheck, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_ModeTransition( CAN_CHANNEL_CANTYPE_FIRST uint8 transitionRequest, uint8 busOffRecovery, uint8 doRamCheck )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 transitionState;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 request transition in LL */
  transitionState = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
  if(transitionState != kCanOk) /* COV_CAN_TRANSITION_REQUEST */
  { /* #20 first request fail so start Loop that wait short time for transition \trace SPEC-1642, SPEC-1635, SPEC-1630 */
    CanHL_ApplCanTimerStart((uint8)CAN_LOOP_MAX); /* SBSW_CAN_HL38 */
    do
    { /* #30 HW check mode reached (LL) */
      transitionState = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
      CanHL_ApplCanTimerLoop((uint8)CAN_LOOP_MAX); /* COV_CAN_TRANSITION_REQUEST */
    } while ( transitionState != kCanOk ); /* COV_CAN_TRANSITION_REQUEST */
    CanHL_ApplCanTimerEnd ((uint8)CAN_LOOP_MAX); /* SBSW_CAN_HL38 */
  }
  if ( transitionState == kCanRequested ) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_TRANSITION_REQUEST */
  {
    /* #50 transition requested so remember request to repeat it asynchronous */
    Can_SetModeTransitionRequest(channel, transitionRequest); /* SBSW_CAN_HL01 */
    Can_SetBusOffTransitionRequest(channel, busOffRecovery); /* SBSW_CAN_HL01 */
    Can_SetRamCheckTransitionRequest(channel, doRamCheck); /* SBSW_CAN_HL01 */
  }
  return transitionState;
}

/****************************************************************************
| NAME:             CanHL_NotifyTransition
****************************************************************************/
/*
|<DataModelStart>| CanHL_NotifyTransition
Relation_Context:
# from Can_SetControllerMode() #
Wakeup
RamCheck
Relation:
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_NotifyTransition( CAN_CHANNEL_CANTYPE_FIRST uint8 canState, CanIf_ControllerModeType canIfState, uint8 transitionState )
{
  /* #10 if mode changed successful */
  if ( transitionState == kCanOk ) /* COV_CAN_TRANSITION_REQUEST */
  {
    /* #20 transition finished change internal state */
    Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | canState)); /* SBSW_CAN_HL02 */
    /* #30 remove transition request */
    Can_SetModeTransitionRequest(channel, kCanModeNone); /* SBSW_CAN_HL01 */
    /* #40 call notification CanIf_ControllerModeIndication() \trace SPEC-1726, SPEC-1644, SPEC-60446 */
    CanIf_ControllerModeIndication( (uint8)Can_GetCanToCanIfChannelMapping(channel), canIfState );
  }
  CAN_DUMMY_STATEMENT(transitionState); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}

#if defined(C_ENABLE_CANCEL_IN_HW)
/****************************************************************************
| NAME:             CanHL_IsHigherCanIdPrio
****************************************************************************/
/*
|<DataModelStart>| CanHL_IsHigherCanIdPrio
Relation_Context:
# from CanHL_WritePrepare #
HwCancelTx, MultiplexedTx, IdenticalIdCancel
Relation:
IDType
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_IsHigherCanIdPrio( Can_IdType CanId1, Can_IdType CanId2 )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval = CAN_NOT_OK;
  Can_IdType tmpCanId1, tmpCanId2;
  tmpCanId1 = CanId1;
  tmpCanId2 = CanId2;
  /* ----- Implementation ----------------------------------------------- */
# if defined(C_ENABLE_MIXED_ID)
  /* #10 take care about mixed Extended and Standard ID format (shift Standard ID to match Extended format) */
  if (((tmpCanId1) & CAN_ID_IDE_MASK) == CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    tmpCanId1 = tmpCanId1 & (Can_IdType)(CAN_ID_MASK);
  } else {
    tmpCanId1 = (Can_IdType)(((tmpCanId1) & CAN_ID_MASK_STD) << 18);
  }
  if (((tmpCanId2) & CAN_ID_IDE_MASK) == CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    tmpCanId2 = tmpCanId2 & (Can_IdType)(CAN_ID_MASK);
  } else {
    tmpCanId2 = (Can_IdType)(((tmpCanId2) & CAN_ID_MASK_STD) << 18);
  }
# else
  /* #20 mask out unused bits */
  tmpCanId1 = tmpCanId1 & (Can_IdType)CAN_ID_MASK;
  tmpCanId2 = tmpCanId2 & (Can_IdType)CAN_ID_MASK;
# endif
  /* #30 compare CAN ID priority */
  if(tmpCanId1 < tmpCanId2)
  {
    retval = CAN_OK;
  }
  return retval;
}
#endif

/****************************************************************************
| NAME:             CanHL_WritePrepare
****************************************************************************/
/*
|<DataModelStart>| CanHL_WritePrepare
Relation_Context:
# from Can_Write() #
Relation:
TxFullCANSupport
MultiplexedTx, TxHwFifo
MultiplexedTx, HwCancelTx, IdenticalIdCancel
ChannelAmount
OneChOpt
TxBasicAmount
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WritePrepare( CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 calculate logical TX mailbox handle for FullCAN or for BasicCAN (Multiplexed TX) as start value */
  txPara->mailboxElement = 0u; /* PRQA S 2982 */ /* MD_MSR_RetVal */ /* SBSW_CAN_HL42 */
  txPara->activeSendObject = CanHL_GetActiveSendObject(txPara->mailboxHandle, 0u); /* SBSW_CAN_HL42 */
#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
  if ( Can_GetMailboxType(txPara->mailboxHandle) != CAN_TX_FULLCAN_TYPE ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#endif
  { /* #20 BasicCAN preparation - search for hardware and logical transmit handle and do cancellation */
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_ENABLE_TX_HW_FIFO) || defined(C_ENABLE_CANCEL_IN_HW)
    CanObjectHandle mailboxElement_max;
    mailboxElement_max = Can_GetMailboxSize(txPara->mailboxHandle); /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    /* \trace SPEC-1677, SPEC-1672, SPEC-1679, SPEC-1673, SPEC-1671 */
# if defined(C_ENABLE_TX_HW_FIFO)
    if (Can_GetMailboxType(txPara->mailboxHandle) == CAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* #25 in case of FIFO object set logical TX mailbox handle to write index + element start  */
       txPara->mailboxElement = (CanObjectHandle)Can_GetTxHwFifoWriteIndex(Can_GetMailboxTxHwFifo(txPara->mailboxHandle)); /* SBSW_CAN_HL42 */
       txPara->activeSendObject += txPara->mailboxElement; /* SBSW_CAN_HL42 */
    }
    else
# endif
    { /* #27 if normal or Mux Tx search from first to last element 0..1 or 0..3 for free object or one to be cancelled */
      CanObjectHandle mailboxElementFound;
      CanObjectHandle activeSendObjectFound;
      mailboxElementFound = mailboxElement_max;
      activeSendObjectFound = mailboxElement_max;
      for (txPara->mailboxElement = 0u; txPara->mailboxElement < mailboxElement_max; txPara->mailboxElement++) /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */
      { /* #30 over all multiplexed TX objects: find free mailbox or mailbox with identical ID */
# if (CAN_IDENTICAL_ID_CANCELLATION == STD_ON) && defined(C_ENABLE_CANCEL_IN_HW)
        if ( ((txPara->pdu.id) == Can_GetActiveSendId(txPara->activeSendObject) ) && (Can_GetActiveSendState(txPara->activeSendObject) != kCanBufferFree) )
        { /* #40 Identical ID: priority 1 - cancel identical (also when free is available) */
          mailboxElementFound = txPara->mailboxElement;
          activeSendObjectFound = txPara->activeSendObject;
          break;
        }
        if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferFree)
        { /* #50 Identical ID: priority 2 - find free mailbox (no cancellation) */
          mailboxElementFound = txPara->mailboxElement; /* do not break ... next may be identical ID */
          activeSendObjectFound = txPara->activeSendObject;
        }
# else
        if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferFree)
        { /* #60 None Identical ID: else priority 1 - find free mailbox (no cancellation) */
          mailboxElementFound = txPara->mailboxElement;
          activeSendObjectFound = txPara->activeSendObject;
          break;
        }
# endif
        txPara->activeSendObject++; /* SBSW_CAN_HL42 */
      }
# if defined(C_ENABLE_CANCEL_IN_HW)
      if (mailboxElementFound == mailboxElement_max)
      { /* #70 No free nor identical ID found but hardware cancellation is on - search for lowest prio message to cancel */
        Can_IdType lowestPrioId = txPara->pdu.id;
        txPara->activeSendObject = CanHL_GetActiveSendObject(txPara->mailboxHandle, 0u); /* SBSW_CAN_HL42 */
        for (txPara->mailboxElement = 0u; txPara->mailboxElement < mailboxElement_max; txPara->mailboxElement++) /* SBSW_CAN_HL42 */ /* SBSW_CAN_HL42 */
        {
          if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferSend)
          { /* #80 mailbox with send request found: check for priority and remember the lowest that could be cancelled */
            if (CanHL_IsHigherCanIdPrio(lowestPrioId, Can_GetActiveSendId(txPara->activeSendObject)) == CAN_OK)
            {
              lowestPrioId = Can_GetActiveSendId(txPara->activeSendObject);
              mailboxElementFound = txPara->mailboxElement;
              activeSendObjectFound = txPara->activeSendObject;
            }
          }
          txPara->activeSendObject++; /* SBSW_CAN_HL42 */
        }
      }
# endif
      if (mailboxElementFound == mailboxElement_max)
      { /* #90 no free or cancel mailbox found: return values set to valid element or to found element and cancel */
        txPara->mailboxElement = 0u; /* SBSW_CAN_HL42 */
        txPara->activeSendObject = CanHL_GetActiveSendObject(txPara->mailboxHandle, 0u); /* SBSW_CAN_HL42 */
      }
      else
      {
        txPara->mailboxElement = mailboxElementFound; /* SBSW_CAN_HL42 */
        txPara->activeSendObject = activeSendObjectFound; /* SBSW_CAN_HL42 */
# if defined(C_ENABLE_CANCEL_IN_HW) /* \trace SPEC-1674 */
        CanHL_WritePrepareCancelTx(CAN_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
# endif
      }
    } /* normal or mux tx */
#endif
  } /* end BasicCAN handling */
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  /* #200 no special FullCAN handling needed */
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if defined(C_ENABLE_CANCEL_IN_HW) || \
   (defined(C_ENABLE_TX_HW_FIFO) && defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2) )
/****************************************************************************
| NAME:             CanHL_WriteSavePduInfo
****************************************************************************/
/*
|<DataModelStart>| CanHL_WriteSavePduInfo
Relation_Context:
# from CanHL_WritePrepareCancelTx #
HwCancelTx
# from CanHL_WriteStart #
TxHwFifo, GenericConfirmation
Relation:
DevErrorDetect
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WriteSavePduInfo( CanTxTransmissionParaStructPtr txPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
    /* #10 Get buffer to store data */
    uint16 activeSendData;
    activeSendData = CanHL_GetActiveSendData(txPara->mailboxHandle, txPara->mailboxElement);
    /* #20 SDU pointer may be a null pointer in case the DLC is 0 - so do not copy data in this case */
    if(txPara->pdu.sdu != NULL_PTR)
    {
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      if(Can_GetSizeOfActiveSendData() >= (activeSendData + txPara->pdu.length)) /* CM_CAN_HL20 */ /* COV_CAN_GENDATA_FAILURE */
# endif
      {
        /* #25 copy data with VStdLib optimized copy routine */
        VStdMemCpy((void*)&Can_GetActiveSendData(activeSendData), (void*)txPara->pdu.sdu, txPara->pdu.length); /* SBSW_CAN_HL22 */ /* PRQA S 0314,0316 */ /* MD_Can_PointerVoidCast */
      }
    }
    /* #30 copy ID, DLC and pointer to data (also pdu as part of PduInfo struct) */
    Can_SetActiveSendId(txPara->activeSendObject, txPara->pdu.id); /* SBSW_CAN_HL23 */
    Can_SetActiveSendLength(txPara->activeSendObject, txPara->pdu.length); /* SBSW_CAN_HL23 */
    Can_SetActiveSendSdu(txPara->activeSendObject, &Can_GetActiveSendData(activeSendData)); /* SBSW_CAN_HL23 */
    Can_SetActiveSendSwPduHandle(txPara->activeSendObject, txPara->pdu.swPduHandle); /* SBSW_CAN_HL23 */
}
#endif

#if defined(C_ENABLE_CANCEL_IN_HW)
/****************************************************************************
| NAME:             CanHL_WritePrepareCancelTx
****************************************************************************/
/*
|<DataModelStart>| CanHL_WritePrepareCancelTx
Relation_Context:
# from CanHL_WritePrepare #
HwCancelTx
Relation:
DevErrorDetect
CanFdSupport
MultiplexedTx, IdenticalIdCancel
OneChOpt
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WritePrepareCancelTx( CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferFree)
  { /* #10 free buffer found: backup ID, DLC, data, PDU for possible cancellation - as parameter to IF */
    CanHL_WriteSavePduInfo(txPara); /* SBSW_CAN_HL49 */
  }
  else if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferSend) /* COV_IMPLICITE_TXCANCEL */
  { /* #20 occupied buffer found (lower ID or Identical - found before): cancel it */
    /* \trace SPEC-1747, SPEC-15133, SPEC-1685, SPEC-1690, SPEC-1692, SPEC-1676, SPEC-1683, SPEC-15126 */
    tCanTxCancellationParaStruct txCancellationPara;
    txCancellationPara.mailboxHandle = txPara->mailboxHandle;
    txCancellationPara.hwObjHandle = txPara->hwObjHandle; 
    txCancellationPara.mailboxElement = txPara->mailboxElement;
    txCancellationPara.activeSendObject = txPara->activeSendObject;
    txCancellationPara.canHandleCurTxObj = kCanBufferCancel;
    /* #30 HW cancel mailbox (LL) */
    CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txCancellationPara); /* SBSW_CAN_HL47 */
    Can_SetActiveSendState(txPara->activeSendObject, kCanBufferCancel); /* SBSW_CAN_HL41 */
    /* #40 do not notify IF about successful cancellation because of recursion will not work! Hardware support not possible in this case */
  }
  else
  { /* avoid MISRA warning (if else if without ending else) */
    /* \trace SPEC-1754 */
  }
}
#endif

/****************************************************************************
| NAME:             CanHL_WriteStart
****************************************************************************/
/*
|<DataModelStart>| Can_WriteStart
Relation_Context:
# from Can_Write #
Relation:
GenericPreTransmit
TxHwFifo, GenericConfirmation
IDType
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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

V_DEF_FUNC(CAN_LOCAL_INLINE, Can_ReturnType, STATIC_CODE) CanHL_WriteStart( CAN_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval = CAN_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 free TX mailbox found so start transmission \trace SPEC-1744 */
  if (Can_GetActiveSendState(txPara->activeSendObject) == kCanBufferFree)
  {
    uint8 llretval;
    /* #20 remember PDU and send state to use it in Confirmation function \trace SPEC-1675 */
    Can_SetActiveSendPdu(txPara->activeSendObject, txPara->pdu.swPduHandle); /* SBSW_CAN_HL05 */
    Can_SetActiveSendState(txPara->activeSendObject, kCanBufferSend); /* SBSW_CAN_HL04 */
#if defined(C_ENABLE_PRETRANSMIT_FCT)
    /* call pretransmit function ----------------------------------------------- */
    Appl_GenericPreTransmit( (uint8)channel, &(txPara->pdu) );  /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL24 */
#endif
#if defined(C_ENABLE_TX_HW_FIFO)
    if (Can_GetMailboxType(txPara->mailboxHandle) == CAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* #30 in case of FIFO and GenericConfirmation API2 remember also data for confirmation function */
      uint16 txHwFifo;
# if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
      CanHL_WriteSavePduInfo(txPara); /* SBSW_CAN_HL49 */
# endif
      /* #40 set Fifo to next element (writing) */
      SchM_Enter_Can_CAN_EXCLUSIVE_AREA_7();
      txHwFifo = Can_GetMailboxTxHwFifo(txPara->mailboxHandle);
# if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      if (txHwFifo >= (uint16)Can_GetSizeOfTxHwFifo()) /* CM_CAN_HL32 */ /* COV_CAN_GENDATA_FAILURE */
      {
        txHwFifo = 0u;
      }
# endif
      Can_IncTxHwFifoFillCount(txHwFifo); /* SBSW_CAN_HL50 */
      if (Can_GetTxHwFifoWriteIndex(txHwFifo) < ((uint16)Can_GetMailboxSize(txPara->mailboxHandle) - (uint16)1u) )
      {
        Can_IncTxHwFifoWriteIndex(txHwFifo); /* SBSW_CAN_HL50 */
      }
      else
      {
        Can_SetTxHwFifoWriteIndex(txHwFifo,0); /* SBSW_CAN_HL50 */
      }
      SchM_Exit_Can_CAN_EXCLUSIVE_AREA_7();
    }
#endif
    /* #50 HW prepare transmission */
    CanLL_TxBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    /* #60 Set ID, ID type and DLC in HW register depend on ID type */
   // txPara->dlcRaw = MK_TX_DLC(CAN_LEN2DLC(txPara->pdu.length)); /* SBSW_CAN_HL42 */
    txPara->dlcRaw = txPara->pdu.length; //
#if defined(C_ENABLE_EXTENDED_ID)
# if defined(C_ENABLE_MIXED_ID)
    if ( ((txPara->pdu.id) & CAN_ID_IDE_MASK) != CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      SET_PARASTRUCT_IDRAW_TX_STD(txPara, txPara->pdu.id); /* SBSW_CAN_HL42 */
    } //SET_PARASTRUCT_IDRAW_TX_STD 这个宏定义txPara->idRaw0
    else
# endif
    {
      SET_PARASTRUCT_IDRAW_TX_EXT(txPara, txPara->pdu.id); /* SBSW_CAN_HL42 */
    }
#else
    {
      SET_PARASTRUCT_IDRAW_TX_STD(txPara, txPara->pdu.id); /* SBSW_CAN_HL42 */ /* PRQA S 4491 */ /* MD_Can_IntegerCast */
    }
#endif
    /* set id, dlc in hardware */
    CanLL_TxSetMailbox(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    if(txPara->pdu.sdu != NULL_PTR)
    { /* #70 Set CAN data in HW register (LL) - only when data pointer is not null \trace SPEC-1680, SPEC-1572, SPEC-1678, SPEC-60421 */
      txPara->CanMemCopySrcPtr = txPara->pdu.sdu; /* SBSW_CAN_HL42 */
      CanLL_TxCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    }
    /* #80 HW start transmission (LL) */
    llretval = CanLL_TxStart(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    if (llretval == kCanFailed) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
    { /* #90 transmit request wasn't successful in LL part - free mailbox */
      retval = CAN_NOT_OK; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
      Can_SetActiveSendState(txPara->activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
    }



      flexcan_data_info_t dataInfo =
      {
              .data_length = 8,
              .msg_id_type = 0,//标准帧
              .enable_brs  = false,
              .fd_enable   = false,
              .fd_padding  = 0U
      };

      //mbId = CAN_MB_ID(HwObjId);

       dataInfo.data_length=txPara->dlcRaw;
      // FLEXCAN_DRV_Send(txPara->hwObjHandle, txPara.pdu.swPduHandle, &dataInfo, txPara.Buf->Id, txPara.Buf->u.bData);
 //      FLEXCAN_DRV_Send(txPara->hwObjHandle, txPara->pdu.swPduHandle+4, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);

       // test by jiangxl 2020-03-05
       //FLEXCAN_DRV_Send(txPara->hwObjHandle, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);
     //  if((data==txPara->Buf->u.bData[0])&&((txPara->pdu.id==0x340)||(txPara->pdu.id==0x3e3)))

       /*
       if(txPara->pdu.id==0x340)
       {
    	//   FLEXCAN_DRV_Send(1, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);


    	   switch(seq1)
    	   {
			   case 0:

					  if((Framedata==txPara->Buf->u.bData[0]))
					  {
						  counter1++;
						  FLEXCAN_DRV_Send(1, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);
					  }
					  else
					  {
						  FLEXCAN_DRV_Send(1, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);
					  }
					  Framedata=txPara->Buf->u.bData[0];
					  seq1=1;
					  break;
			   case 1:
					  if((Framedata==txPara->Buf->u.bData[0]))
					  {
						  counter1++;
						  FLEXCAN_DRV_Send(1, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);
					  }
					  else
					  {
						  FLEXCAN_DRV_Send(1, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);
					  }
					  Framedata=txPara->Buf->u.bData[0];
					  seq1=0;
				  break;
    	   }
       }
       else if(txPara->pdu.id==0x3e3)
       {

    	   switch(seq2)
    	   {
			   case 0:
				  if((Framedata2==txPara->Buf->u.bData[0]))
				  {
					  counter2++;
					  FLEXCAN_DRV_Send(1, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);
				  }
				  else
				  {
					  FLEXCAN_DRV_Send(1, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);
				  }
				  Framedata2=txPara->Buf->u.bData[0];
				   seq2=1;
				   break;
			   case 1:
				  if((Framedata2==txPara->Buf->u.bData[0]))
				  {
					  counter2++;
					  FLEXCAN_DRV_Send(1, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);
				  }
				  else
				  {
					  FLEXCAN_DRV_Send(1, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);
				  }
				  Framedata2=txPara->Buf->u.bData[0];
				  seq2=0;
				  break;
    	   }
       }
       else
       {
    	   FLEXCAN_DRV_Send(1, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);
       }
        */


       FLEXCAN_DRV_Send(1, 13, &dataInfo, txPara->Buf->Id, txPara->Buf->u.bData);

    /* HW finish transmission (LL) */
    CanLL_TxEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST txPara); /* SBSW_CAN_HL49 */
    CAN_DUMMY_STATEMENT(llretval); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
  else
  { /* #200 no free TX mailbox found so return busy - also in case cancellation (BasicCAN) was possible \trace SPEC-1754, SPEC-1764, SPEC-1747 */
    retval = CAN_BUSY;
  }
  return retval;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

/****************************************************************************
| NAME:             CanHL_GetActiveSendObject
****************************************************************************/
/*
|<DataModelStart>| CanHL_GetActiveSendObject
Relation_Context:
# from CanHL_InitXXX() #
Wakeup, OneChOpt, ChannelAmount
# from CanHL_WritePrepare #
# from CanHL_TxTaskCancelationHandling #
HwCancelTx
# from CanHL_CleanUpSendState #
# from Can_CancelTx #
TransmitCancellationAPI
# from CanHL_TxConfirmation #
Relation:
DevErrorDetect
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, CanObjectHandle, STATIC_CODE) CanHL_GetActiveSendObject( Can_HwHandleType mailboxHandle, Can_HwHandleType mailboxElement )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle activeSendObject;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 get logical handle from generated indirection table */
  activeSendObject = (CanObjectHandle) Can_GetMailboxActiveSendObject(mailboxHandle) + mailboxElement;
#if (CAN_SAFE_BSW == STD_ON)
  if (activeSendObject >= (Can_HwHandleType)Can_GetSizeOfActiveSendObject()) /* CM_CAN_HL03 */ /* COV_CAN_GENDATA_FAILURE */
  { /* #20 secure SilentBSW */
    activeSendObject = ((Can_HwHandleType)Can_GetSizeOfActiveSendObject() - (Can_HwHandleType)1u);
# if (CAN_DEV_ERROR_REPORT == STD_ON)  
    Can_CallDetReportError(CAN_WRITE_ID, CAN_E_PARAM_HANDLE);
# endif
  }
#endif
  return activeSendObject;
}

#if defined(C_ENABLE_CANCEL_IN_HW) || \
   (defined(C_ENABLE_TX_HW_FIFO) && defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2) )
/****************************************************************************
| NAME:             CanHL_GetActiveSendData
****************************************************************************/
/*
|<DataModelStart>| CanHL_GetActiveSendData
Relation_Context:
HwCancelTx, TxHwFifo
# from CanHL_WritePrepare #
# from CanHL_TxTaskCancelationHandling #
HwCancelTx
# from Can_CancelTx #
TransmitCancellationAPI
# from CanHL_TxConfirmation #
Relation:
DevErrorDetect
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint16, STATIC_CODE) CanHL_GetActiveSendData( Can_HwHandleType mailboxHandle, uint8 mailboxElement )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 activeSendData;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 get logical handle from generated indirection table */
  activeSendData = (uint16) (Can_GetMailboxActiveSendData(mailboxHandle) + ((uint16)mailboxElement * (uint16)Can_GetMailboxDataLen(mailboxHandle)));
#if (CAN_SAFE_BSW == STD_ON)
  if ((activeSendData + Can_GetMailboxDataLen(mailboxHandle)) > Can_GetSizeOfActiveSendData()) /* CM_CAN_HL20 */ /* COV_CAN_GENDATA_FAILURE */
  { /* #20 secure SilentBSW */
    activeSendData = 0u;
# if (CAN_DEV_ERROR_REPORT == STD_ON)  
    Can_CallDetReportError(CAN_WRITE_ID, CAN_E_PARAM_HANDLE);
# endif
  }
#endif
  return activeSendData;
}
#endif

#if defined(C_ENABLE_CAN_RAM_CHECK)
/****************************************************************************
| NAME:             CanHL_RamCheckMailboxNotification
****************************************************************************/
/*
|<DataModelStart>| CanHL_RamCheckMailboxNotification
Relation_Context:
# CanHL_InitXXX() #
Wakeup, OneChOpt, ChannelAmount, RamCheck
Relation:
TxFullCANSupport
RxFullCANSupport
RxBasicCANSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RamCheckMailboxNotification( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */ /* COV_CAN_RAM_CHECK_NO_STIMULATION */
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 deactivate mailbox */
  Can_SetMailboxState(initPara->mailboxHandle, kCanFailed); /* SBSW_CAN_HL34 */
  /* #20 deactivate controller */
  Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL02 */
  /* #30 notify application about corrupt mailbox */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  CanIf_RamCheckCorruptMailbox((uint8)Can_GetCanToCanIfChannelMapping(channel), initPara->mailboxHandle);
# else
#  if defined(C_ENABLE_NOTIFY_CORRUPT_MAILBOX) /* with Mailbox Notification */
  Appl_CanCorruptMailbox((uint8)channel, (initPara->hwObjHandle));
#  endif
# endif
}
#endif

/****************************************************************************
| NAME:             CanHL_InitBegin
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitBegin
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount
Relation:
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitBegin( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanFailed; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  if (CanLL_InitBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara) == kCanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL31 */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
  {
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    /* #20 Execute pattern RamCheck */
    if (initPara->doRamCheck == kCanExecuteRamCheck)
    {
      initPara->isChRamCheckFail |= CAN_RAM_CHECK_BEGIN_REG_RESULT(channel, initPara); /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL31 */ /* COV_CAN_HARDWARE_FAILURE */
    } 
#endif
    /* #30 Initialize controller registers (Begin section) */
    initOk = CanLL_InitBeginSetRegisters(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
  }
  return initOk;
}

#if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_InitTxFullCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitTxFullCAN
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount, TxFullCANSupport
Relation:
RamCheck
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxFullCAN( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;
  CanObjectHandle activeSendObject;
# if defined(C_ENABLE_CAN_RAM_CHECK)
  uint8 isMbRamCheckFail;
# endif
  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanOk;
  /* #10 iterate over all FullCAN TX */
  for (initPara->mailboxHandle = Can_GetTxFullHandleStart(canHwChannel); initPara->mailboxHandle < Can_GetTxFullHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */
  { /* #20 initialize FullCAN TX mailboxes */
    initPara->hwObjHandle = Can_GetMailboxHwHandle(initPara->mailboxHandle); /* SBSW_CAN_HL36 */
    activeSendObject = CanHL_GetActiveSendObject(initPara->mailboxHandle, 0u);
    Can_SetActiveSendState(activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
# if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #30 RAM check for FullCAN TX mailboxes */
    isMbRamCheckFail = kCanFalse;
    if (initPara->doRamCheck == kCanExecuteRamCheck)
    {
      isMbRamCheckFail = CAN_RAM_CHECK_MAILBOX_RESULT(channel, initPara); /* SBSW_CAN_HL31 */ /* COV_CAN_HARDWARE_FAILURE */
    } 
# endif
    /* TX initialization */
    mailboxState = CanLL_InitMailboxTx(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
# if defined(C_ENABLE_CAN_RAM_CHECK)
    if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
    { /* PowerOn */
      Can_SetMailboxState(initPara->mailboxHandle, mailboxState); /* SBSW_CAN_HL34 */
    }
    if( (isMbRamCheckFail == kCanTrue) || (Can_GetMailboxState(initPara->mailboxHandle) == kCanFailed) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CanLL_InitMailboxTxDeactivate(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      if (isMbRamCheckFail == kCanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      }
    }
# endif
  }
  return initOk;
}
#endif

/****************************************************************************
| NAME:             CanHL_InitTxBasicCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitTxBasicCAN
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount
Relation:
MultiplexedTx, TxHwFifo
TxHwFifo, GenericConfirmation, IfTxBuffer
TxBasicAmount
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitTxBasicCAN( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;
  CanObjectHandle activeSendObject;
#if defined(C_ENABLE_CAN_RAM_CHECK)
  uint8 isMbRamCheckFail;
#endif

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanOk;
  initPara->mailboxHandle = Can_GetTxBasicHandleStart(canHwChannel); /* SBSW_CAN_HL36 */
#if defined(C_ENABLE_MULTIPLE_BASICCAN_TX)
  for (; initPara->mailboxHandle < Can_GetTxBasicHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL36 */
#endif
  { /* #10 iterate over all logical BasicCAN TX */
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_ENABLE_TX_HW_FIFO) 
    CanObjectHandle activeSendObjectStop;
#endif
    initPara->hwObjHandle = Can_GetMailboxHwHandle(initPara->mailboxHandle); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */ /* SBSW_CAN_HL36 */
    activeSendObject = CanHL_GetActiveSendObject(initPara->mailboxHandle, 0u);
#if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_ENABLE_TX_HW_FIFO) 
    activeSendObjectStop = activeSendObject + Can_GetMailboxSize(initPara->mailboxHandle);
    for (; activeSendObject < activeSendObjectStop; activeSendObject++)
#endif
    { /* #20 initialize BasicCAN TX mailboxes */
      Can_SetActiveSendState(activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
    }
# if defined(C_ENABLE_TX_HW_FIFO)
    if (Can_GetMailboxType(initPara->mailboxHandle) == CAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* #25 initialize TxHwFifo index and fill state */
      uint16 txHwFifo;
      txHwFifo = Can_GetMailboxTxHwFifo(initPara->mailboxHandle);
#  if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      if (txHwFifo >= (uint16)Can_GetSizeOfTxHwFifo()) /* CM_CAN_HL32 */ /* COV_CAN_GENDATA_FAILURE */
      {
        txHwFifo = 0u;
        initOk = kCanFailed;
      }
#  endif
      Can_SetTxHwFifoWriteIndex(txHwFifo, 0u); /* SBSW_CAN_HL50 */
      Can_SetTxHwFifoReadIndex(txHwFifo, 0u); /* SBSW_CAN_HL50 */
      Can_SetTxHwFifoFillCount(txHwFifo, 0u); /* SBSW_CAN_HL50 */
    }
# endif
#if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #30 RAM check for BasicCAN TX mailboxes */
    isMbRamCheckFail = kCanFalse;
    if (initPara->doRamCheck == kCanExecuteRamCheck)
    {
      isMbRamCheckFail = CAN_RAM_CHECK_MAILBOX_RESULT(channel, initPara); /* COV_CAN_HARDWARE_FAILURE */ /* SBSW_CAN_HL31 */
    } 
#endif
    /* TX initialization */
    mailboxState = CanLL_InitMailboxTx(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
#if defined(C_ENABLE_CAN_RAM_CHECK)
    if( (Can_GetLogStatus(channel) & CAN_STATUS_INIT) != CAN_STATUS_INIT )
    { /* PowerOn */
      Can_SetMailboxState(initPara->mailboxHandle, mailboxState); /* SBSW_CAN_HL34 */
    }
    if( (isMbRamCheckFail == kCanTrue) || (Can_GetMailboxState(initPara->mailboxHandle) == kCanFailed) ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    { /* #45 deactivate corrupt mailbox */
      CanLL_InitMailboxTxDeactivate(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      if (isMbRamCheckFail == kCanTrue)
      {  /* #50 notify application about corrupt mailbox and deactivate controller */
        CanHL_RamCheckMailboxNotification(CAN_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
      }
    }
#endif
  }
  return initOk;
}


#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
/****************************************************************************
| NAME:             CanHL_InitRxFullCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitRxFullCAN
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount, RxFullCANSupport
Relation:
RamCheck
IDType
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxFullCAN( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanOk;
  for (initPara->mailboxHandle = Can_GetRxFullHandleStart(canHwChannel); initPara->mailboxHandle < Can_GetRxFullHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */
  { /* #10 iterate over all FullCAN RX mailboxes */
    initPara->hwObjHandle=Can_GetMailboxHwHandle(initPara->mailboxHandle); /* SBSW_CAN_HL36 */
    /* #30 set ID for FullCAN RX mailboxes (LL) */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
    if ( (Can_GetMailboxIDValue(initPara->mailboxHandle) & CAN_ID_IDE_MASK) != CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */
    {
      initPara->idType = kCanIdTypeStd; /* SBSW_CAN_HL36 */
      SET_PARASTRUCT_IDRAW_RX_STD(initPara, Can_GetMailboxIDValue(initPara->mailboxHandle)); /* SBSW_CAN_HL36 */ /* PRQA S 4491 */ /* MD_Can_IntegerCast */
    }
    else
#  endif
    {
      initPara->idType = kCanIdTypeExt; /* SBSW_CAN_HL36 */ /* PRQA S 2880 */ /* MD_MSR_Unreachable */
      SET_PARASTRUCT_IDRAW_RX_EXT(initPara, Can_GetMailboxIDValue(initPara->mailboxHandle)); /* SBSW_CAN_HL36 */
    }
# else
    initPara->idType = kCanIdTypeStd; /* SBSW_CAN_HL36 */
    SET_PARASTRUCT_IDRAW_RX_STD(initPara, Can_GetMailboxIDValue(initPara->mailboxHandle)); /* SBSW_CAN_HL36 */ /* PRQA S 4491 */ /* MD_Can_IntegerCast */
# endif
    /* #40 initialize FullCAN RX mailboxes */
    mailboxState = CanLL_InitMailboxRxFullCan(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985 */ /* MD_Can_ConstValue */

  }
  return initOk;
}
#endif

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/****************************************************************************
| NAME:             CanHL_InitRxBasicCAN
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitRxBasicCAN
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount, RxBasicCANSupport
Relation:
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitRxBasicCAN( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;
  uint8 mailboxState;

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanOk;
  for (initPara->mailboxHandle = Can_GetRxBasicHandleStart(canHwChannel); initPara->mailboxHandle < Can_GetRxBasicHandleStop(canHwChannel); initPara->mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */ /* SBSW_CAN_HL36 */ /* SBSW_CAN_HL36 */
  { /* #10 iterate over all BasicCAN RX mailboxes */
    initPara->hwObjHandle = Can_GetMailboxHwHandle(initPara->mailboxHandle); /* SBSW_CAN_HL36 */
    /* #30 initialize BasicCAN RX mailboxes */
  //  mailboxState = CanLL_InitMailboxRxBasicCan(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
    mailboxState = 1;
    initOk &= mailboxState; /* all mailboxes OK - otherwise return fail */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
  }
  return initOk;
}
#endif

/****************************************************************************
| NAME:             CanHL_InitEnd_InitMode
****************************************************************************/
/*
|<DataModelStart>| CanHL_InitEnd_InitMode
Relation_Context:
# CanHL_ReInit() #
Wakeup, OneChOpt, ChannelAmount
Relation:
RamCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_InitEnd_InitMode( CAN_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 initOk;

  /* ----- Implementation ----------------------------------------------- */
  initOk = kCanOk;

  /* #20 HW specific initialization end */
  initOk &= CanLL_InitEndSetRegisters(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara); /* SBSW_CAN_HL31 */
  initOk &= CanLL_InitEnd( CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST initPara ); /* SBSW_CAN_HL31 */
  return initOk;
}

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_RxBasicCanPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_RxBasicCanPolling
Relation_Context:
# from Can_MainFunction_Read #
RxBasicCANSupport, RxPolling
Relation:
IndividualPolling
OneChOpt
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxBasicCanPolling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  tCanTaskParaStruct taskPara;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check global pending flag (over all mailboxes - if available) */
  if(CanLL_RxBasicIsGlobalIndPending(CAN_HW_CHANNEL_CANPARA_ONLY) == kCanTrue) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
  {
    /* #20 loop over all BasicCAN mailboxes */
    for (taskPara.mailboxHandle = Can_GetRxBasicHandleStart(canHwChannel); taskPara.mailboxHandle < Can_GetRxBasicHandleStop(canHwChannel); taskPara.mailboxHandle++) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
    { /* loop over all BasicCAN mailboxes with gap */
      taskPara.hwObjHandle = Can_GetMailboxHwHandle(taskPara.mailboxHandle);
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
      /* #30 check individual polling flag */
      if ( Can_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
      {
        /* #40 call LL handling */
        CanLL_RxBasicProcessPendings(CAN_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
      }
    }
  }
}
# endif /* C_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_RxFullCanPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_RxFullCanPolling
Relation_Context:
# from Can_MainFunction_Read #
RxFullCANSupport, RxPolling
Relation:
IndividualPolling
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxFullCanPolling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  tCanTaskParaStruct taskPara;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check global pending flag (over all mailboxes - if available) */
  if(CanLL_RxFullIsGlobalIndPending(CAN_HW_CHANNEL_CANPARA_ONLY) == kCanTrue) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
  {
    /* #20 loop over all FullCAN mailboxes */
    for (taskPara.mailboxHandle = Can_GetRxFullHandleStart(canHwChannel); taskPara.mailboxHandle < Can_GetRxFullHandleStop(canHwChannel); taskPara.mailboxHandle++ ) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
    {
      taskPara.hwObjHandle = Can_GetMailboxHwHandle(taskPara.mailboxHandle);
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
      /* #30 check individual polling flag */
      if ( Can_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
      {
        /* #40 call LL handling */
        CanLL_RxFullProcessPendings(CAN_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
      }
    }
  }
}
# endif /* C_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
/****************************************************************************
| NAME:             CanHL_RxMsgReceivedNotification
****************************************************************************/
/*
|<DataModelStart>| CanHL_RxMsgReceivedNotification
Relation_Context:
# from CanHL_FullCanMsgReceived #
RxFullCANSupport
# from CanHL_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
RxQueue, GenericPreCopy, MirrorMode
RxQueue, DevErrorDetect
RxQueue, CanFdSupport
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(CAN_LOCAL_INLINE, uint8, STATIC_CODE) CanHL_RxMsgReceivedNotification( CAN_CHANNEL_CANTYPE_FIRST CanRxInfoStructPtr rxStructPtr ) /* PRQA S 3673 */ /* MD_Can_NoneConstParameterPointer */
{
  /* ----- Local Variables ---------------------------------------------- */
# if !defined(C_ENABLE_RX_QUEUE) && (CAN_GENERIC_PRECOPY == STD_ON)
  Can_ReturnType generic_retval;
# endif
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 RX queue */
# if defined(C_ENABLE_RX_QUEUE)
  /**************************** RxQueue handling **********************************/
    /* #20 EXCLUSIVE_AREA_4 secure RxQueue data handling */
  SchM_Enter_Can_CAN_EXCLUSIVE_AREA_4();
  if (Can_GetRxQueueInfo().Count < Can_GetSizeOfRxQueueBuffer()) /* COV_CAN_GENDATA_FAILURE */
  { /* #30 Queue not full: */
    /* #45 copy HRH, ID, DLC and data to RX queue */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).Hrh = rxStructPtr->localMailboxHandle; /* SBSW_CAN_HL18 */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).id  = rxStructPtr->localId; /* SBSW_CAN_HL18 */
    Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).dlc = rxStructPtr->localDlc; /* SBSW_CAN_HL18 */

#  if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (canRxQueueMaxDataSize < rxStructPtr->localDlc) /* CM_CAN_HL17 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_DLC;
    }
    else
#  endif
    {
      /* #46 copy data with VStdLib optimized copy routine */
      VStdMemCpy((void*)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().WriteIndex).data, (void*)rxStructPtr->pChipData, rxStructPtr->localDlc); /* SBSW_CAN_HL19 */ /* PRQA S 0312,0314,0316 */ /* MD_Can_NoneVolatilePointerCast,MD_Can_PointerVoidCast,MD_Can_PointerVoidCast */
    }
      /* #47 increase pointer to next queue element */
    Can_GetRxQueueInfo().Count++; /* SBSW_CAN_HL55 */
    if (Can_GetRxQueueInfo().WriteIndex < ((uint16)Can_GetSizeOfRxQueueBuffer() - (uint16)1u) )
    {
      Can_GetRxQueueInfo().WriteIndex++; /* SBSW_CAN_HL55 */
    }
    else
    {
      Can_GetRxQueueInfo().WriteIndex = 0u; /* CM_CAN_HL24 */ /* SBSW_CAN_HL55 */
    }
  }
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  else 
  { /* #50 Queue full: last message will be lost -> overrun in queue do not change ReadIndex to override latest message because inconsistency problem (currently reading queue) */
    errorId = CAN_E_RXQUEUE;
  }
#  endif
  SchM_Exit_Can_CAN_EXCLUSIVE_AREA_4();
# else /* C_ENABLE_RX_QUEUE */
  /* #100 no RX queue */
  /* -------------------------- Interface + APPL Notifications --- */
    /* #110 call Appl_GenericPrecopy() depend on configuration and if mirror mode is active */
#  if (CAN_GENERIC_PRECOPY == STD_ON)
#   if defined(C_ENABLE_MIRROR_MODE)
  if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
  { /* do not call Appl_GenericPrecopy() in case mirror mode was disabled */
    generic_retval = CAN_OK;
  }
  else
#   endif
  {
    generic_retval = Appl_GenericPrecopy((uint8)channel, (rxStructPtr->localId & CAN_ID_MASK_IN_GENERIC_CALLOUT), rxStructPtr->localDlc, (Can_DataPtrType)rxStructPtr->pChipData);  /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL07 */
  }
  if (generic_retval == CAN_OK) /* \trace SPEC-15119 */
#  endif
  { /* #120 call CanIf_RxIndication() if mirror mode is no active or Appl_GenericPrecopy() return OK \trace SPEC-1726, SPEC-1688, SPEC-1687, SPEC-1687 */
    CanIf_RxIndication(rxStructPtr->localMailboxHandle, rxStructPtr->localId, rxStructPtr->localDlc, (Can_DataPtrType)rxStructPtr->pChipData); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL07 */
  }
# endif
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return errorId;
}
#endif

#if defined(C_ENABLE_RX_QUEUE)
/****************************************************************************
| NAME:             CanHL_RxQueueExecution
****************************************************************************/
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
/*
|<DataModelStart>| CanHL_RxQueueExecution
Relation_Context:
# from Can_Mainfunction_Read #
RxQueue
Relation:
GenericPreCopy, OneChOpt, DevErrorDetect
GenericPreCopy, MirrorMode
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_RxQueueExecution( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Execute RxQueue (over all channels) */
  while ( Can_GetRxQueueInfo().Count != (uint16)0 )
  { /* #20 over all filled RxQueue elements */
# if (CAN_GENERIC_PRECOPY == STD_ON)
    Can_ReturnType generic_retval;
    CAN_CHANNEL_CANTYPE_LOCAL
    generic_retval = CAN_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).Hrh);
#   if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    { /* #30 Check controller is valid */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#   endif
#  endif
#  if defined(C_ENABLE_MIRROR_MODE)
    if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
    { /* #40 MirrorMode: only when mirror is activated for this controller */
      generic_retval = CAN_OK;
    }
    else
#  endif
    { /* #50 call Appl_GenericPrecopy() */
      generic_retval = Appl_GenericPrecopy( (uint8)channel,
                (Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).id & CAN_ID_MASK_IN_GENERIC_CALLOUT),
                Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).dlc,
                (Can_DataPtrType)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).data ); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL06 */
    }
    if (generic_retval == CAN_OK)
# endif
    { /* #60 call CanIf_RxIndication() if Appl_GenericPrecopy() return OK or no generic precopy is used \trace SPEC-1726, SPEC-1688, SPEC-1687, SPEC-1687 */
      CanIf_RxIndication( Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).Hrh, /* SBSW_CAN_HL06 */
              Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).id,
              Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).dlc,
              (Can_DataPtrType)Can_GetRxQueueBuffer(Can_GetRxQueueInfo().ReadIndex).data ); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */
    }
    /* #70 EXCLUSIVE_AREA_4 secure RxQueue handling */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_4();
    /* #80 get next RxQueue element pointer */
    if (Can_GetRxQueueInfo().ReadIndex >= ((uint16)Can_GetSizeOfRxQueueBuffer() - (uint16)1u) ) /* CM_CAN_HL25 */
    {
      Can_GetRxQueueInfo().ReadIndex = 0u; /* CM_CAN_HL25 */ /* SBSW_CAN_HL55 */
    }
    else
    {
      Can_GetRxQueueInfo().ReadIndex++; /* SBSW_CAN_HL55 */
    }
    Can_GetRxQueueInfo().Count--; /* SBSW_CAN_HL55 */
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_4();
  }
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_READ_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}
#endif

#if defined(C_ENABLE_CANCEL_TX_IN_HW) 
#endif

/* PRQA S 3673 QAC_CanLL_LocalFunctions */ /* MD_Can_NoneConstParameterPointer */

/**********************************************************************************************************************
 *  CanLL_InitBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitBegin
Relation_Context:
# CanHL_InitBegin() #
OneChOpt, ChannelAmount
Relation:
Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBegin( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Implementation ----------------------------------------------- */
#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
# if !defined(C_ENABLE_WAKEUP_POLLING)
#  if defined(C_ENABLE_LL_CAN_INTCTRL)
  /* #10 disable the wakeup interrupt */
  CanLL_CanWakeupInterruptDisable(CAN_HW_CHANNEL_CANPARA_FIRST &Can_GetCanInterruptOldStatus(canHwChannel)); /* SBSW_CAN_LL15 */
#  endif
#  if defined(C_ENABLE_LL_CAN_INTCB)
  /* ApplCanWakeupInterruptDisable has to disable the wakeup interrupt */
  ApplCanWakeupInterruptDisable(canHwChannel);
#  endif
# endif
#endif

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (kCanOk);
}
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
/**********************************************************************************************************************
 *  CanLL_InitBeginIsRegisterCorrupt
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitBeginIsRegisterCorrupt
Relation_Context:
# CanHL_InitBegin() #
OneChOpt, ChannelAmount, RamCheck
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginIsRegisterCorrupt( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 canRegCheckFailed;
  vuint8 idx;
  # if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel = mCanLogToPhys(canHwChannel);
  # endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 assume the register RAM is not corrupt */
  canRegCheckFailed = kCanFalse;

  /* PRQA S 2985 QAC_CanLL_InitBeginIsRegisterCorrupt */ /* MD_Can_ConstValue */
  /* #20 iterate test patterns */
  for (idx=0u; idx<3u; idx++)
  {
    /* #30 write pattern to registers */
    /* CiBCFG/CmCFG,(CmNCFG) */
    Can->ChCtrl[canPhysChannel].BCFG = (CanMemCheckValues32bit[idx] & kCanRamCheckMaskBCFG); /* SBSW_CAN_LL02 */
# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
    /* -/CmDCFG */
    Can->ChCtrlFd[canPhysChannel].BCFG = (CanMemCheckValues32bit[idx] & kCanRamCheckMaskFDBCFG); /* SBSW_CAN_LL02 */
    /* -/CmFDCFG */
    Can->ChCtrlFd[canPhysChannel].FDCFG = (CanMemCheckValues32bit[idx] & kCanRamCheckMaskFDCFG); /* SBSW_CAN_LL02 */
# endif
    /* CiCR/CmCTR - omit (-/CRCT(0),(ROM(0)), (-/TR*(000)), TSTM/CTMS(00), TSTE/CTME(0), RTBO/RTBO(0), STP/CSLPR(0), MODE/CHMDC(01) */
    Can->ChCtrl[canPhysChannel].CR = ((CanMemCheckValues32bit[idx] & kCanRamCheckMaskCR) | kCanResetMode); /* SBSW_CAN_LL02 */
    /* C?TBIER/TMIECy */
    Can->CTBIER[CanLL_TxWordIndex(canPhysChannel)] = 
      ((Can->CTBIER[CanLL_TxWordIndex(canPhysChannel)] & CanLL_TxMaskWordClear(canPhysChannel)) | (CanMemCheckValuesRegSize[idx] & CanLL_TxMaskWord(canPhysChannel))); /* SBSW_CAN_LL02 */

    /* #40 verify register contents */
    if (   ((Can->ChCtrl[canPhysChannel].BCFG & kCanRamCheckMaskBCFG) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskBCFG))
# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
        || ((Can->ChCtrlFd[canPhysChannel].BCFG & kCanRamCheckMaskFDBCFG) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskFDBCFG))
        || ((Can->ChCtrlFd[canPhysChannel].FDCFG & kCanRamCheckMaskFDCFG) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskFDCFG))
# endif
        || ((Can->ChCtrl[canPhysChannel].CR & kCanRamCheckMaskCR) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskCR))
        || ((Can->CTBIER[CanLL_TxWordIndex(canPhysChannel)] & CanLL_TxMaskWord(canPhysChannel)) != (CanMemCheckValuesRegSize[idx] & CanLL_TxMaskWord(canPhysChannel)))
       ) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
    {
      canRegCheckFailed = kCanTrue;
    }
  } /* iterate test patterns */
  /* PRQA L:QAC_CanLL_InitBeginIsRegisterCorrupt */

  /* #50 check if unsupported Tx features are disabled */
  /* CiTQCR/TXQCCm */
  if (Can->TQCR[canPhysChannel] != kCanZero) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
  {
    canRegCheckFailed = kCanTrue;
  }

  /* CiTHCR/THLCCm */
  if (Can->THCR[canPhysChannel] != kCanZero) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
  {
    canRegCheckFailed = kCanTrue;
  }

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (canRegCheckFailed);
}
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_CAN_RAM_CHECK_EXTENDED */

/**********************************************************************************************************************
 *  CanLL_InitBeginSetRegisters
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitBeginSetRegisters
Relation_Context:
# CanHL_InitBegin() #
OneChOpt, ChannelAmount
Relation:
OneChOpt
ChannelAmount
StatusPolling
TxPolling, IndividualPolling, HwCancelTx
RxFullCANSupport, LLDerivative
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitBeginSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint32 canTmpReg32;
  kCanRegSize canTmpRegRs;
#if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel = mCanLogToPhys(canHwChannel);
#endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 set bit rate and CAN-FD configuration registers */
  CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &Can->ChCtrl[canPhysChannel].BCFG, Can_GetInitObjectBitTiming(initPara->initObject), initPara); /* SBSW_CAN_LL02 */
#if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
  CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &Can->ChCtrlFd[canPhysChannel].BCFG, Can_GetInitObjectBitTimingData(initPara->initObject), initPara); /* SBSW_CAN_LL02 */
  CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &Can->ChCtrlFd[canPhysChannel].FDCFG, Can_GetInitObjectCanFdConfig(initPara->initObject), initPara); /* SBSW_CAN_LL02 */
#endif

  /* #20 set control register */
  canTmpReg32 = kCanCrHaltAtBusoff | kCanResetMode;
#if !defined(C_ENABLE_ERROR_POLLING)
  canTmpReg32 |= kCanCrIntMaskBusoff;
#endif
#if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#else
# if defined(C_ENABLE_CANCEL_IN_HW)
  canTmpReg32 |= kCanCrIntMaskCancel;
# endif
#endif
  CanLL_WriteReg32(CAN_CHANNEL_CANPARA_FIRST &Can->ChCtrl[canPhysChannel].CR, canTmpReg32, initPara); /* SBSW_CAN_LL02 */

  /* #30 set transmit buffer interrupt enable configuration register */
  canTmpRegRs = ((Can->CTBIER[CanLL_TxWordIndex(canPhysChannel)] & CanLL_TxMaskWordClear(canPhysChannel)) |
                 CanLL_TxWordToSharedReg(canPhysChannel, Can_GetTxIntMaskOfChannelData(canHwChannel))); /* PRQA S 2985 */ /* MD_Can_ConstValue */
  CanLL_WriteRegRegSize(CAN_CHANNEL_CANPARA_FIRST &Can->CTBIER[CanLL_TxWordIndex(canPhysChannel)], canTmpRegRs, initPara); /* SBSW_CAN_LL02 */

  /* message status, transmission & cancel requests for transmit buffers / transmit FIFO buffers and error flags were cleared by channel reset */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
  /* #40 reset receive buffer new data registers */
  Can->CRBRCF[0] = ((kCanRegSizeCast) ~Can_GetRxFcMask0OfChannelData(canHwChannel)); /* SBSW_CAN_LL06 */ /* PRQA S 4399 */ /* MD_Can_IntegerCast */
# if (kCanNumberOfSharedReg16 > 1u)
  Can->CRBRCF[1] = ((kCanRegSizeCast) ~Can_GetRxFcMask1OfChannelData(canHwChannel)); /* SBSW_CAN_LL06 */ /* PRQA S 4399 */ /* MD_Can_IntegerCast */
# endif
# if (kCanNumberOfSharedReg16 > 2u)
  Can->CRBRCF[2] = ((kCanRegSizeCast) ~Can_GetRxFcMask2OfChannelData(canHwChannel)); /* SBSW_CAN_LL06 */ /* PRQA S 4399 */ /* MD_Can_IntegerCast */
# endif
# if (kCanNumberOfSharedReg16 > 3u) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_SHARED_REG */
  Can->CRBRCF[3] = ((kCanRegSizeCast) ~Can_GetRxFcMask3OfChannelData(canHwChannel)); /* SBSW_CAN_LL06 */ /* PRQA S 4399 */ /* MD_Can_IntegerCast */
# endif
#endif
  /* receive FIFO buffers are reset in Rx BasicCAN specific initialization */

  return (kCanOk);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitMailboxTx
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxTx
Relation_Context:
# CanHL_InitTxFullCAN() #
OneChOpt, ChannelAmount
# CanHL_InitTxBasicCAN() #
OneChOpt, ChannelAmount
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxTx( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (kCanOk);
}
/* CODE CATEGORY 4 END */

# if (defined( C_ENABLE_CAN_RAM_CHECK ))
/**********************************************************************************************************************
 *  CanLL_InitMailboxTxDeactivate
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxTxDeactivate
Relation_Context:
# CanHL_InitTxFullCAN() #
OneChOpt, ChannelAmount
# CanHL_InitTxBasicCAN() #
OneChOpt, ChannelAmount
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMailboxTxDeactivate( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 4 END */
# endif


#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxFullCan
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxRxFullCan
Relation_Context:
# CanHL_InitRxFullCAN() #
OneChOpt, ChannelAmount, RxFullCANSupport
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxRxFullCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (kCanOk);
}
/* CODE CATEGORY 4 END */


#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_InitMailboxRxBasicCan
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMailboxRxBasicCan
Relation_Context:
# CanHL_InitRxBasicCAN() #
Wakeup, OneChOpt, ChannelAmount, RxBasicCANSupport
Relation:
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitMailboxRxBasicCan( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 retVal = kCanFailed; /* PRQA S 2981 */ /* MD_Can_RedundantInit */

  /* ----- Implementation ----------------------------------------------- */
# if (CAN_SAFE_BSW == STD_ON)
  if (initPara->hwObjHandle < kCanMaxRxFifos) /* CM_CAN_LL05 */
# endif
  {
    /* #10 disable receive FIFO buffer to clear pending messages */
    Can->CRFCR[initPara->hwObjHandle] &= ((kCanRegSize) ~kCanCrFifoEnable); /* SBSW_CAN_LL03 */ /* PRQA S 4399 */ /* MD_Can_IntegerCast */
    /* #20 delete receive FIFO buffer interrupt and overrun flags */
    Can->CRFSR[initPara->hwObjHandle] &= ((kCanRegSize) ~(kCanSrRxFifoIntFlag | kCanSrFifoOverrun)); /* SBSW_CAN_LL03 */ /* PRQA S 4399 */ /* MD_Can_IntegerCast */
    /* #30 re-enable receive FIFO buffer */
    Can->CRFCR[initPara->hwObjHandle] |= kCanCrFifoEnable; /* SBSW_CAN_LL03 */

    retVal = kCanOk;
  }

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (retVal);
}
/* CODE CATEGORY 4 END */

#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */


/**********************************************************************************************************************
 *  CanLL_InitEndSetRegisters
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitEndSetRegisters
Relation_Context:
# CanHL_InitEnd_InitMode() #
Wakeup, OneChOpt, ChannelAmount
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitEndSetRegisters( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (kCanOk);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitEnd
Relation_Context:
# CanHL_InitEnd_InitMode() #
OneChOpt
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitEnd( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (kCanOk);
}
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CAN_RAM_CHECK )
/**********************************************************************************************************************
 *  CanLL_InitIsMailboxCorrupt
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitIsMailboxCorrupt
Relation_Context:
# CanHL_InitXXX() #
Wakeup, OneChOpt, ChannelAmount
TxFullCANSupport, RamCheck
RxFullCANSupport, RamCheck
RxBasicCANSupport, RamCheck
Relation:
TxHwFifo, DevErrorDetect
TxHwFifo, CanFdSupport
CanFdSupport
MultiplexedTx
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_InitIsMailboxCorrupt( CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanInitParaStructPtr initPara )
{
  /* ----- Local Variables ---------------------------------------------- */
  tCanBufPtr Buf;
  CanObjectHandle mailboxElement = kCanZero;
  vuint8 idx;

  /* assume the mailbox is not corrupt */
  vuint8 canMailboxCheckFailed = kCanFalse;

  /* ----- Implementation ----------------------------------------------- */
# if defined(C_ENABLE_TX_HW_FIFO)
  /* #10 if the mailbox is realized by a transmit buffer */
  if (!Can_IsTxFifo(initPara->mailboxHandle)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# endif
  {
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
    /* #20 iterate mailbox elements */
    for (; mailboxElement < Can_GetMailboxSize(initPara->mailboxHandle); mailboxElement++)
# endif
    {
# if (CAN_SAFE_BSW == STD_ON)
      if ((initPara->hwObjHandle + mailboxElement) >= kCanMaxTxBuf) /* CM_CAN_LL06 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
      {
        canMailboxCheckFailed = kCanTrue;
      }
      else
# endif
      {
        Buf = pBufTm(mCanLogToPhys(canHwChannel), (initPara->hwObjHandle + mailboxElement)); /* PRQA S 0310, 2985 */ /* MD_Can_PointerCast, MD_Can_ConstValue */

        /* #30 iterate test patterns */
        for (idx=0u; idx<3u; idx++)
        {
          /* #40 write pattern to mailbox registers */
          Buf->Id         =  CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
          Buf->Dlc        = (CanMemCheckValues32bit[idx] & kCanDlcMask); /* SBSW_CAN_LL08 */
# if defined(C_ENABLE_CAN_FD_USED)
          Buf->Fd         = (CanMemCheckValues32bit[idx] & kCanFdCfgMask); /* SBSW_CAN_LL08 */
# endif
          Buf->u.iData[0] =  CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
          Buf->u.iData[1] =  CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
# if defined(C_ENABLE_CAN_FD_FULL)
          Buf->u.iData[2] =  CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
          Buf->u.iData[3] =  CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
          Buf->u.iData[4] =  CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
# endif
          /* #50 verify mailbox register contents */
          if (   (Buf->Id         !=  CanMemCheckValues32bit[idx]                 )
              || (Buf->Dlc        != (CanMemCheckValues32bit[idx] & kCanDlcMask)  )
# if defined(C_ENABLE_CAN_FD_USED)
              || (Buf->Fd         != (CanMemCheckValues32bit[idx] & kCanFdCfgMask))
# endif
              || (Buf->u.iData[0] !=  CanMemCheckValues32bit[idx]                 )
              || (Buf->u.iData[1] !=  CanMemCheckValues32bit[idx]                 )
# if defined(C_ENABLE_CAN_FD_FULL)
              || (Buf->u.iData[2] !=  CanMemCheckValues32bit[idx]                 )
              || (Buf->u.iData[3] !=  CanMemCheckValues32bit[idx]                 )
              || (Buf->u.iData[4] !=  CanMemCheckValues32bit[idx]                 )
# endif
             ) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
          {
            canMailboxCheckFailed = kCanTrue; /* the mailbox is corrupt */
          }

# if defined(C_ENABLE_CAN_FD_FULL)
#  if defined(C_ENABLE_IF_RSCAN_FD) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_EMBEDDED */
          if (   ((initPara->hwObjHandle + mailboxElement) == 0u) /* PRQA S 2985 */ /* MD_Can_ConstValue */
              || ((initPara->hwObjHandle + mailboxElement) == 3u) /* PRQA S 2985 */ /* MD_Can_ConstValue */
             )
#  endif
          {
            /* #60 write pattern to additional mailbox data registers */
            Buf->u.iData[5] =  CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
            Buf->u.iData[6] =  CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
            Buf->u.iData[7] =  CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
            Buf->u.iData[8] =  CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
            Buf->u.iData[9] =  CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
            Buf->u.iData[10] = CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
            Buf->u.iData[11] = CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
            Buf->u.iData[12] = CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
            Buf->u.iData[13] = CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
            Buf->u.iData[14] = CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */
            Buf->u.iData[15] = CanMemCheckValues32bit[idx]; /* SBSW_CAN_LL08 */

            /* #70 verify additional mailbox data register contents */
            if (   (Buf->u.iData[5] !=  CanMemCheckValues32bit[idx])
                || (Buf->u.iData[6] !=  CanMemCheckValues32bit[idx])
                || (Buf->u.iData[7] !=  CanMemCheckValues32bit[idx])
                || (Buf->u.iData[8] !=  CanMemCheckValues32bit[idx])
                || (Buf->u.iData[9] !=  CanMemCheckValues32bit[idx])
                || (Buf->u.iData[10] != CanMemCheckValues32bit[idx])
                || (Buf->u.iData[11] != CanMemCheckValues32bit[idx])
                || (Buf->u.iData[12] != CanMemCheckValues32bit[idx])
                || (Buf->u.iData[13] != CanMemCheckValues32bit[idx])
                || (Buf->u.iData[14] != CanMemCheckValues32bit[idx])
                || (Buf->u.iData[15] != CanMemCheckValues32bit[idx])
               ) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
            {
              canMailboxCheckFailed = kCanTrue; /* the mailbox is corrupt */
            }
          }
# endif
        } /* iterate test patterns */
      }
    } /* iterate mailbox elements */
  }

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (canMailboxCheckFailed);
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_CAN_RAM_CHECK */


/**********************************************************************************************************************
 *  CanLL_InitPowerOn
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitPowerOn
Relation_Context:
# from Can_Init #
Relation:
DevErrorDetect
RamCheck
CanFdSupport
CanFdConfiguration
CanCrcConfiguration
Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount, OneChOpt
StatusPolling, RxBasicCANSupport, Overrun
HardwareLoopCheck, OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitPowerOn(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  CAN_CHANNEL_CANTYPE_LOCAL
  vuint8 retVal = kCanOk; /* PRQA S 2981 */ /* MD_Can_RedundantInit */
#if defined(C_ENABLE_IF_RSCAN_FD) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  vuint8 idx;
# endif
#endif


  /*
   *
   * 主要的作用是将  CAN 控制器设置为  kCanOperationMode 启动CAN 控制器
   */
  retVal =kCanOk;
#if 0   /* DELETE */
  /* ----- Implementation ----------------------------------------------- */
#if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  channel = 0;
#endif

  /* #10 transit via global stop mode to global reset mode */
 ///// CanLL_InitPowerOnModeTransitions();

#if (CAN_SAFE_BSW == STD_ON)
  /* #20 check the generated data */
 /// retVal = CanLL_CheckGeneratedData();
  retVal =kCanOk;
  if (retVal == kCanOk) /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2991, 2995 */ /* MD_Can_SafeCheck_LL */
#endif
  {
#if defined(C_ENABLE_IF_RSCAN_FD) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD */
    /* #30 check and set global interface mode select register */
# if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    canIsCellCorrupt = kCanFalse;

//    for (idx=0u; idx<3u; idx++)
//    {
      /* -/CFDGRMCFG */
//      Can->CGRMCFG = (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCGRMCFG); /* SBSW_CAN_LL01 */
 //     if ((Can->CGRMCFG & kCanRamCheckMaskCGRMCFG) != (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCGRMCFG)) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
 //     {
  //      canIsCellCorrupt = kCanTrue;
  //    }
  //  }
# endif /* C_ENABLE_CAN_RAM_CHECK_EXTENDED */

# if defined(C_ENABLE_CAN_FD_USED)
    /* select CAN-FD mode */
 //   CanLL_WriteRegGlobal32(&Can->CGRMCFG, kCanOne); /* SBSW_CAN_LL01 */
# else
    /* select classical CAN mode */
   // CanLL_WriteRegGlobal32(&Can->CGRMCFG, kCanZero); /* SBSW_CAN_LL01 */
# endif
#endif


#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    /* #40 perform the global register RAM pattern check */
# if defined(C_ENABLE_IF_RSCAN_FD) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD */
    if (canIsCellCorrupt == kCanFalse) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
# endif
    {
      canIsCellCorrupt = CanLL_IsGlobalRegisterCorrupt();
    }
#endif /* C_ENABLE_CAN_RAM_CHECK_EXTENDED */


    /* #50 set global registers */
#if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
# if defined(C_ENABLE_CAN_FD_CONFIGURATION) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_FD_CONFIGURATION */
    CanLL_WriteRegGlobal32(&Can->CGFDCFG, (vuint32)C_ENABLE_CAN_FD_CONFIGURATION); /* SBSW_CAN_LL01 */
# endif
# if defined(C_ENABLE_CAN_CRC_CONFIGURATION) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_CRC_CONFIGURATION */
    CanLL_WriteRegGlobal32(&Can->CGCRCCFG, (vuint32)C_ENABLE_CAN_CRC_CONFIGURATION); /* SBSW_CAN_LL01 */
# endif
#endif
    CanLL_WriteRegGlobal32(&Can->CGCFG, kCanGlobCfg); /* SBSW_CAN_LL01 */

    /* #60 configure filter rules, receive buffers, receive and transmit FIFO buffers */
    CanLL_InitPowerOnGlobalInit();

#if defined(C_ENABLE_LL_CAN_INTCTRL)
# if !defined(C_ENABLE_ERROR_POLLING) || ((defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_RX_BASICCAN_POLLING))) 
    canInterruptOldFlag.GErrCnt = kCanZero;    /* counter for interrupt disable/restore on shared sources */
# endif
#endif /* C_ENABLE_LL_CAN_INTCTRL */


    /* #70 set global control register and transit to global operation mode */
#if !defined(C_ENABLE_ERROR_POLLING) && ((defined(C_ENABLE_RX_BASICCAN_OBJECTS) && defined(C_ENABLE_OVERRUN)))
    CanLL_WriteRegGlobal32(&Can->CGCR, (kCanOperationMode | kCanIntMaskMessageLost)); /* SBSW_CAN_LL01 */
#else
    CanLL_WriteRegGlobal32(&Can->CGCR, kCanOperationMode); /* SBSW_CAN_LL01 */
#endif

    if (!CanLL_GlobalModeCheck(kCanOperationMode)) /* COV_CAN_LL_MODE_CHECK */
    {
      if (!CanLL_GlobalModeCheck(kCanOperationMode)) /* COV_CAN_LL_MODE_CHECK */
      {
        CanLL_GlobalModeWait(kCanOperationMode, kCanLoopGlobalInit);
      }
    }

#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    /* #80 notify corrupt global register RAM */
    if (canIsCellCorrupt == kCanTrue) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      Appl_CanRamCheckCorruptCell();
    }
#endif /* C_ENABLE_CAN_RAM_CHECK_EXTENDED */
  }

#endif   /* DELETE */



  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (retVal);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitPowerOnChannelSpecific
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitPowerOnChannelSpecific
Relation_Context:
# from Can_Init #
Relation:
ChannelAmount, OneChOpt
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_InitPowerOnChannelSpecific(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (kCanOk);
}
/* CODE CATEGORY 4 END */

/**********************************************************************************************************************
 *  CanLL_InitMemoryPowerOn
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_InitMemoryPowerOn
Relation_Context:
# from Can_InitMemory #
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitMemoryPowerOn(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
}
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_CANCEL_IN_HW )
/**********************************************************************************************************************
 *  CanLL_TxCancelInHw
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxCancelInHw
Relation_Context:
# from Can_CancelTx #
TransmitCancellationAPI, TxFullCANSupport, HwCancelTx
# from CanHL_WritePrepareCancelTx #
Relation:
OneChOpt
MultiplexedTx
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 3 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxCancellationParaStructPtr txCancellationPara)
{
  /* ----- Implementation ----------------------------------------------- */
  {
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
    txCancellationPara->hwObjHandle += txCancellationPara->mailboxElement; /* SBSW_CAN_LL11 */
# endif
    /* #10 set transmission cancellation request */
# if (CAN_SAFE_BSW == STD_ON)
    if (txCancellationPara->hwObjHandle < kCanMaxTxBuf) /* CM_CAN_LL06 */
# endif
    {
      Can->ChBC[mCanLogToPhys(canHwChannel)].TBCR[txCancellationPara->hwObjHandle] |= kCanCrTxBufCancel; /* SBSW_CAN_LL04 */
    }
  }

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 3 END */
#endif



/**********************************************************************************************************************
 *  CanLL_TxBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxBegin
Relation_Context:
# from Can_Write #
Relation:
TxHwFifo, DevErrorDetect
MultiplexedTx
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 initialize the pointer to the mailbox */
# if defined(C_ENABLE_TX_HW_FIFO)
  if (Can_IsTxFifo(txPara->mailboxHandle)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
  {
#  if (CAN_SAFE_BSW == STD_ON)
    if (txPara->hwObjHandle >= kCanMaxTxFifos) /* CM_CAN_LL07 */
    {
      txPara->Buf = &CanLL_DummyBuf; /* SBSW_CAN_LL11 */
    }
    else
#  endif
    {
    //  txPara->Buf = pBufCf(mCanLogToPhys(canHwChannel), txPara->hwObjHandle); /* SBSW_CAN_LL11 */
    	txPara->Buf =&SendBuf;
    }
  }
  else
# endif
  {
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
    txPara->hwObjHandle += txPara->mailboxElement; /* SBSW_CAN_LL11 */
# endif
# if (CAN_SAFE_BSW == STD_ON)
    if (txPara->hwObjHandle >= kCanMaxTxBuf) /* CM_CAN_LL06 */
    {
      txPara->Buf = &CanLL_DummyBuf; /* SBSW_CAN_LL11 */
    }
    else
# endif
    {
    	txPara->Buf =&SendBuf;
   //   txPara->Buf = pBufTm(mCanLogToPhys(canHwChannel), txPara->hwObjHandle); /* SBSW_CAN_LL11 */ /* PRQA S 0310 */ /* MD_Can_PointerCast */
    }
  }

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_TxSetMailbox
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxSetMailbox
Relation_Context:
# from Can_Write #
Relation:
IDType
OneChOpt
CanFdSupport
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxSetMailbox(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 set the mailbox control registers */
  txPara->Buf->Id = txPara->idRaw0; /* SBSW_CAN_LL08 */
 // txPara->Buf->Dlc = CanActualDLCToReg(txPara->dlcRaw); /* SBSW_CAN_LL08 */
  txPara->Buf->Dlc = txPara->dlcRaw;
#  if defined(C_ENABLE_CAN_FD_USED)
  txPara->Buf->Fd = (vuint32)(txPara->fdType | txPara->fdBrsType); /* SBSW_CAN_LL08 */ /* PRQA S 4391 */ /* MD_Can_IntegerCast */
#  endif

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */


/**********************************************************************************************************************
 *  CanLL_TxCopyToCan
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxCopyToCan
Relation_Context:
# from Can_Write #
Relation:
OneChOpt
CanFdSupport, DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxCopyToCan(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara)
{
  /* ----- Local Variables ---------------------------------------------- */
  tCanTmpData CanLL_TxTmpBuf; /* PRQA S 0759 */ /* MD_Can_Union */
# if defined(C_ENABLE_CAN_FD_FULL)
  vuint8 canCount;
# endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 copy the transmit data to a temporary buffer and set the mailbox data registers */
#  if defined(C_ENABLE_CAN_FD_FULL)
#   if (CAN_SAFE_BSW == STD_ON)
  if ((txPara->messageLen <= 64u) && (txPara->frameLen <= 64u)) /* CM_CAN_LL10 */
#   endif
  {
    for (canCount = 0; canCount < txPara->messageLen; canCount++) /* CM_CAN_LL10 */
    {
      CanLL_TxTmpBuf.bData[canCount] = txPara->CanMemCopySrcPtr[canCount]; /* SBSW_CAN_LL09 */
    }
    for (canCount = txPara->messageLen; canCount < txPara->frameLen; canCount++) /* CM_CAN_LL10 */
    {
      CanLL_TxTmpBuf.bData[canCount] = txPara->paddingVal; /* SBSW_CAN_LL09 */
    }

    if (txPara->frameLen > 8u)
    {
      /* only discrete values that are dividable by 4 */
      for (canCount = 0; canCount < (txPara->frameLen >> 2); canCount++) /* CM_CAN_LL10 */
      {
        txPara->Buf->u.iData[canCount] = CanLL_TxTmpBuf.iData[canCount]; /* SBSW_CAN_LL08 */
      }
    }
    else
    {
      txPara->Buf->u.iData[0] = CanLL_TxTmpBuf.iData[0]; /* SBSW_CAN_LL08 */
      txPara->Buf->u.iData[1] = CanLL_TxTmpBuf.iData[1]; /* SBSW_CAN_LL08 */
    }
  }
#  else
  CanLL_TxTmpBuf.bData[0] = txPara->CanMemCopySrcPtr[0]; /* SBSW_CAN_LL09 */
  CanLL_TxTmpBuf.bData[1] = txPara->CanMemCopySrcPtr[1]; /* SBSW_CAN_LL09 */
  CanLL_TxTmpBuf.bData[2] = txPara->CanMemCopySrcPtr[2]; /* SBSW_CAN_LL09 */
  CanLL_TxTmpBuf.bData[3] = txPara->CanMemCopySrcPtr[3]; /* SBSW_CAN_LL09 */
  txPara->Buf->u.iData[0] = CanLL_TxTmpBuf.iData[0]; /* SBSW_CAN_LL08 */
  CanLL_TxTmpBuf.bData[4] = txPara->CanMemCopySrcPtr[4]; /* SBSW_CAN_LL09 */
  CanLL_TxTmpBuf.bData[5] = txPara->CanMemCopySrcPtr[5]; /* SBSW_CAN_LL09 */
  CanLL_TxTmpBuf.bData[6] = txPara->CanMemCopySrcPtr[6]; /* SBSW_CAN_LL09 */
  CanLL_TxTmpBuf.bData[7] = txPara->CanMemCopySrcPtr[7]; /* SBSW_CAN_LL09 */
  txPara->Buf->u.iData[1] = CanLL_TxTmpBuf.iData[1]; /* SBSW_CAN_LL08 */
#  endif

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_TxStart
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxStart
Relation_Context:
# from Can_Write #
Relation:
CanFdSupport, IDType
OneChOpt
TxHwFifo, DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxStart(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 retVal = kCanOk;
# if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel = mCanLogToPhys(canHwChannel);
# endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 set transmission request */
# if defined(C_ENABLE_TX_HW_FIFO)
  if (Can_IsTxFifo(txPara->mailboxHandle)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
  {
#  if (CAN_SAFE_BSW == STD_ON)
    if (txPara->hwObjHandle >= kCanMaxTxFifos) /* CM_CAN_LL07 */
    {
      retVal = kCanFailed;
    }
    else
#  endif
    {//启动发送
  ///    Can->ChFPC[canPhysChannel].TRFPCR[txPara->hwObjHandle] = kCanPcrFifoPC; /* SBSW_CAN_LL05 */
    }
  }
  else
# endif
  {
    {
# if (CAN_SAFE_BSW == STD_ON)
      if (txPara->hwObjHandle >= kCanMaxTxBuf) /* CM_CAN_LL06 */
      {
        retVal = kCanFailed;
      }
      else
# endif
      {
   ///     Can->ChBC[canPhysChannel].TBCR[txPara->hwObjHandle] |= kCanCrTxBufReq; /* SBSW_CAN_LL04 */
      }
    }
  }

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (retVal);
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_TxEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxEnd
Relation_Context:
# from Can_Write #
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxTransmissionParaStructPtr txPara)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(txPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

#if defined( C_ENABLE_TX_POLLING )
/**********************************************************************************************************************
 *  CanLL_TxIsGlobalConfPending
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxIsGlobalConfPending
Relation_Context:
# from Can_MainFunction_Write #
TxPolling, TxFullCANSupport
Relation:
OneChOpt
ChannelAmount
TxHwFifo, OneChOpt
TxHwFifo, HwCancelTx
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxIsGlobalConfPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
# if !defined(C_ENABLE_TX_HW_FIFO)
  /* ----- Local Variables ---------------------------------------------- */
#  if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel = mCanLogToPhys(canHwChannel);
#  endif
  vuint8 retVal = kCanFalse;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check the transmit buffer status registers for transmission events */
  if (   ((Can->CTBTCSR[CanLL_TxWordIndex(canPhysChannel)] & CanLL_TxMaskWord(canPhysChannel)) != 0u)
#  if defined(C_ENABLE_CANCEL_IN_HW)
      || ((Can->CTBASR[CanLL_TxWordIndex(canPhysChannel)] & CanLL_TxMaskWord(canPhysChannel)) != 0u)
#  endif
     ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG TF tf xf */
  {
    retVal = kCanTrue;
  }

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (retVal);
# else
  /* #20 perform no global check for pending events if transmit FIFO buffers are in use */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (kCanTrue);
# endif
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_TxProcessPendings
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxProcessPendings
Relation_Context:
# from Can_MainFunction_Write #
TxPolling, TxFullCANSupport
Relation:
TxHwFifo
OneChOpt
MultiplexedTx
TxBasicAmount
TxFullAmount
ChannelAmount
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara)
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle mailboxElement = kCanZero;
# if defined(C_ENABLE_TX_HW_FIFO)
  vuint8 canCount;
  vuint8 requestCount;
  vuint8 pendingCount;
# endif
# if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel = mCanLogToPhys(canHwChannel);
# endif

  /* ----- Implementation ----------------------------------------------- */
# if defined(C_ENABLE_TX_HW_FIFO)
  if (Can_IsTxFifo(taskPara->mailboxHandle)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
  {
    /* #10 confirmation handling for each transmitted message or configured limit in case of a transmit FIFO buffer */
    canCount = Can_GetFifoProcCountOfChannelData(canHwChannel);
    requestCount = (vuint8)Can_GetTxHwFifoFillCount(Can_GetMailboxTxHwFifo(taskPara->mailboxHandle));
    pendingCount = (vuint8)((Can->ChFS[canPhysChannel].TRFSR[taskPara->hwObjHandle] & kCanSrFifoMsgCount) >> 8);
    while (((requestCount - pendingCount) > 0u) && (canCount > 0u)) /* COV_CAN_LL_MANUAL TF tf tx */
    {
      canCount--;
      CanHL_TxConfirmationPolling(CAN_HW_CHANNEL_CANPARA_FIRST taskPara->mailboxHandle, kCanZero, taskPara->hwObjHandle);
      requestCount = (vuint8)Can_GetTxHwFifoFillCount(Can_GetMailboxTxHwFifo(taskPara->mailboxHandle));
      pendingCount = (vuint8)((Can->ChFS[canPhysChannel].TRFSR[taskPara->hwObjHandle] & kCanSrFifoMsgCount) >> 8);
    }
  }
  else
# endif
  {
    /* #20 confirmation handling for each mailbox element in case of a transmit buffer */
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
    for (; mailboxElement < Can_GetMailboxSize(taskPara->mailboxHandle); mailboxElement++)
# endif
    {
      if ((Can->ChBS[canPhysChannel].TBSR[taskPara->hwObjHandle + mailboxElement] & kCanSrTxBufMaskPending) != 0u) /* COV_CAN_LL_NOT_IN_ALL_CONFIG TX */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
      {
        CanHL_TxConfirmationPolling(CAN_HW_CHANNEL_CANPARA_FIRST taskPara->mailboxHandle, mailboxElement, taskPara->hwObjHandle + mailboxElement); /* PRQA S 2985 */ /* MD_Can_ConstValue */
      }
    }
  }
}
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_TX_POLLING */

/**********************************************************************************************************************
 *  CanLL_TxConfBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxConfBegin
Relation_Context:
# from CanHL_TxConfirmation #
Relation:
ChannelAmount, OneChOpt
OneChOpt
TxHwFifo
DevErrorDetect
HwCancelTx
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara)
{
  /* ----- Local Variables ---------------------------------------------- */
# if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel = mCanLogToPhys(canHwChannel);
# endif

  /* ----- Implementation ----------------------------------------------- */
#if defined(C_ENABLE_TX_HW_FIFO)
  if (!Can_IsTxFifo(txConfPara->mailboxHandle)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
#endif
  {
#if (CAN_SAFE_BSW == STD_ON)
    if (txConfPara->hwObjHandle < kCanMaxTxBuf) /* CM_CAN_LL06 */
#endif
    {
#if defined(C_ENABLE_CANCEL_IN_HW)
      txConfPara->txBufferStatus = Can->ChBS[canPhysChannel].TBSR[txConfPara->hwObjHandle]; /* SBSW_CAN_LL11 */
#endif
      /* #10 clear the result status flag for transmit buffers */
      Can->ChBS[canPhysChannel].TBSR[txConfPara->hwObjHandle] &= ((vuint8) ~kCanSrTxBufMaskPending); /* SBSW_CAN_LL04 */
    }
  }

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

#if defined( C_ENABLE_CANCEL_IN_HW )
/**********************************************************************************************************************
 *  CanLL_TxConfIsMsgTransmitted
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxConfIsMsgTransmitted
Relation_Context:
# from CanHL_TxConfirmation #
HwCancelTx
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_TxConfIsMsgTransmitted(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 retVal = kCanFalse;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 evaluate the transmit buffer result status flag for transmission completion */
  if ((txConfPara->txBufferStatus & kCanSrTxBufMaskComplete) != 0u)
  {
    retVal = kCanTrue;
  }

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (retVal);
}
/* CODE CATEGORY 1 END */
#endif

#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
/**********************************************************************************************************************
 *  CanLL_TxConfSetTxConfStruct
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxConfSetTxConfStruct
Relation_Context:
# from CanHL_TxConfirmation #
GenericConfirmation
Relation:
OneChOpt
DevErrorDetect
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfSetTxConfStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  tCanBufPtr Buf;

  /* ----- Implementation ----------------------------------------------- */
# if (CAN_SAFE_BSW == STD_ON)
  if (txConfPara->hwObjHandle >= kCanMaxTxBuf) /* CM_CAN_LL06 */
  {
    Buf = &CanLL_DummyBuf;
  }
  else
# endif
  {
    Buf = pBufTm(mCanLogToPhys(canHwChannel), txConfPara->hwObjHandle); /* PRQA S 0310 */ /* MD_Can_PointerCast */
  }

  /* #10 set pointers in the transmit structure */
  txConfPara->txStructConf->pChipMsgObj = (CanChipMsgPtr)(Buf); /* SBSW_CAN_LL11 */ /* PRQA S 0310 */ /* MD_Can_PointerCast */
  txConfPara->txStructConf->pChipData = (CanChipDataPtr)&(Buf->u.bData[0]); /* SBSW_CAN_LL11 */
}
/* CODE CATEGORY 1 END */
#endif

/**********************************************************************************************************************
 *  CanLL_TxConfEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_TxConfEnd
Relation_Context:
# from CanHL_TxConfirmation #
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_TxConfEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTxConfirmationParaStructPtr txConfPara)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(txConfPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */


#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_RxBasicMsgReceivedBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxBasicMsgReceivedBegin
Relation_Context:
# from CanHL_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
OneChOpt, CanFdSupport
DevErrorDetect
ChannelAmount
EccRxReject
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara,Can_PduType pdu)
{
  /* ----- Local Variables ---------------------------------------------- */
  tCanBufPtr Buf;
# if defined(C_ENABLE_CAN_FD_FULL)
  vuint8 canCount;
  vuint8 canDlc;
# endif
  vuint8 retVal = kCanOk;
  vuint8  i;
  vuint32   id,id2;

  /* ----- Implementation ----------------------------------------------- */
# if (CAN_SAFE_BSW == STD_ON)
  if (rxBasicPara->hwObjHandle >= kCanMaxRxFifos) /* CM_CAN_LL05 */
  {
    retVal = kCanFailed;
  }
  else
# endif
  {
    //Buf = pBufRf(rxBasicPara->hwObjHandle);
/*
 * 刚开始在这里停顿了很长时间，一直在找问题，最后问题出现在这里。空指针！！！！！
  id=pdu.id;
   Buf->Dlc=pdu.length;
   Buf->Id=pdu.id;
   id2=Buf->Id;
   for(i=0;i<8;i++)
   {
	   Buf->u.bData[i]=pdu.sdu[i];
   }
*/
   /* #10 delete interrupt flag of the receive FIFO buffer */
  ///////  Can->CRFSR[rxBasicPara->hwObjHandle] &= ((kCanRegSize) ~kCanSrRxFifoIntFlag); /* SBSW_CAN_LL03 */ /* PRQA S 4399 */ /* MD_Can_IntegerCast */

    /* #20 copy mailbox contents to temporary buffer */
    Can_GetRxTmpBuf(canHwChannel).Id           = pdu.id; /* SBSW_CAN_LL10 */
    Can_GetRxTmpBuf(canHwChannel).Dlc          = pdu.length; /* SBSW_CAN_LL10 */
# if defined(C_ENABLE_CAN_FD_USED)
    Can_GetRxTmpBuf(canHwChannel).Fd           = Buf->Fd; /* SBSW_CAN_LL10 */
# endif
# if defined(C_ENABLE_CAN_FD_FULL)
    canDlc = CanRegToActualDLC(Can_GetRxTmpBuf(canHwChannel).Dlc);
    if (canDlc > 8u)
    {
      /* only discrete values that are dividable by 4 */
      for (canCount = 0u; canCount < (CAN_DLC2LEN(canDlc) >> 2); canCount++) /* CM_CAN_LL10 */
      {
        Can_GetRxTmpBuf(canHwChannel).u.iData[canCount] = Buf->u.iData[canCount]; /* SBSW_CAN_LL10 */
      }
    }
    else
# endif
    {

     // Can_GetRxTmpBuf(canHwChannel).u.iData[0] = Buf->u.iData[0]; /* SBSW_CAN_LL10 */
     // Can_GetRxTmpBuf(canHwChannel).u.iData[1] = Buf->u.iData[1]; /* SBSW_CAN_LL10 */
    	for(i=0;i<pdu.length;i++)
    	{
    		Can_GetRxTmpBuf(canHwChannel).u.bData[i]=pdu.sdu[i];
    	}
    }

    /* #30 point to next message in the receive FIFO buffer */
///////    Can->CRFPCR[rxBasicPara->hwObjHandle] = kCanPcrFifoPC; /* SBSW_CAN_LL03 */

    /* #40 set pointers in the receive structure */
    rxBasicPara->rxStruct.pChipMsgObj = (CanChipMsgPtr)&(Can_GetRxTmpBuf(canHwChannel)); /* SBSW_CAN_LL11 */
    rxBasicPara->rxStruct.pChipData = (CanChipDataPtr)&(Can_GetRxTmpBuf(canHwChannel).u.bData[0]); /* SBSW_CAN_LL11 */

# if defined(C_ENABLE_CAN_FD_USED)
    /* #50 discard CAN-FD messages if not enabled for the init object */
    if ((Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_NONE) && ((Can_GetRxTmpBuf(canHwChannel).Fd & kCanFdTypeFd) == kCanFdTypeFd)) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      retVal = kCanFailed;
    }
# endif
  }

# if defined(C_ENABLE_ECC_RX_REJECT)
  /* #60 discard messages in case of uncorrectable RAM errors */
  if (ApplCanEccRxReject(canHwChannel) == kCanTrue)
  {
    retVal = kCanFailed;
  }
# endif

  return (retVal);
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicReleaseObj
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxBasicReleaseObj
Relation_Context:
# from CanHL_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(rxBasicPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicMsgReceivedEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxBasicMsgReceivedEnd
Relation_Context:
# from CanHL_BasicCanMsgReceived #
RxBasicCANSupport
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxBasicParaStructPtr rxBasicPara)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(rxBasicPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

# if defined( C_ENABLE_RX_BASICCAN_POLLING )
/**********************************************************************************************************************
 *  CanLL_RxBasicIsGlobalIndPending
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxBasicIsGlobalIndPending
Relation_Context:
# from CanHL_RxBasicCanPolling #
RxBasicCANSupport, RxPolling
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 retVal = kCanFalse;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check the FIFO empty status register for reception events */
  if (((Can->CFESR & kCanRxFifoMask) & Can_GetRxBcMaskOfChannelData(canHwChannel)) != Can_GetRxBcMaskOfChannelData(canHwChannel))
  {
    retVal = kCanTrue;
  }

  return (retVal);
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_RxBasicProcessPendings
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxBasicProcessPendings
Relation_Context:
# from CanHL_RxBasicCanPolling #
RxBasicCANSupport, RxPolling
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxBasicProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 canCount = Can_GetFifoProcCountOfChannelData(canHwChannel);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 call the reception handling for each message till the receive FIFO buffer is empty or the configured limit is reached */
  while (((Can->CRFSR[taskPara->hwObjHandle] & kCanSrFifoEmpty) == 0u) && (canCount > 0u)) /* COV_CAN_LL_MANUAL TF tf tx */
  {
    canCount--;
    CanHL_BasicCanMsgReceivedPolling(CAN_HW_CHANNEL_CANPARA_FIRST taskPara->mailboxHandle, taskPara->hwObjHandle);
  }
}
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_RxFullMsgReceivedBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxFullMsgReceivedBegin
Relation_Context:
# from CanHL_FullCanMsgReceived #
RxFullCANSupport
Relation:
HardwareLoopCheck
CanFdSupport
DevErrorDetect
RxFullAmount
ChannelAmount
CanFdSupport #, dlc -> dlc implicite variance in db file#
EccRxReject
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxFullMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara)
{
  /* ----- Local Variables ---------------------------------------------- */
  tCanBufPtr Buf;
# if defined(C_ENABLE_HW_LOOP_TIMER)
  tCanLoopRet canHwLoopRetVal;
# endif
# if defined(C_ENABLE_CAN_FD_FULL)
  vuint8 canCount;
  vuint8 canDlc;
# endif
  vuint8 retVal = kCanOk;

  /* ----- Implementation ----------------------------------------------- */
# if (CAN_SAFE_BSW == STD_ON)
  if (CanLL_BitIndex(rxFullPara->hwObjHandle) >= kCanNumberOfSharedReg16) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_SHARED_REG XF */ /* CM_CAN_LL08 */ /* PRQA S 2992, 2996 */ /* MD_Can_ConstValue */
  {
    retVal = kCanFailed; /* PRQA S 2880 */ /* MD_Can_ConstValue */
  }
  else
# endif
  {
    Buf = pBufRm(rxFullPara->hwObjHandle); /* PRQA S 0310 */ /* MD_Can_PointerCast */

    /* #10 clear the new data flag of the receive buffer */
    Can->CRBRCF[CanLL_BitIndex(rxFullPara->hwObjHandle)] = CanLL_ClearBitRS(rxFullPara->hwObjHandle); /* SBSW_CAN_LL06 */

    /* #20 copy mailbox contents to temporary buffer */
    Can_GetRxTmpBuf(canHwChannel).Id           = Buf->Id; /* SBSW_CAN_LL10 */
    Can_GetRxTmpBuf(canHwChannel).Dlc          = Buf->Dlc; /* SBSW_CAN_LL10 */
# if defined(C_ENABLE_CAN_FD_USED)
    Can_GetRxTmpBuf(canHwChannel).Fd           = Buf->Fd; /* SBSW_CAN_LL10 */
# endif
# if defined(C_ENABLE_CAN_FD_FULL)
    canDlc = CanRegToActualDLC(Can_GetRxTmpBuf(canHwChannel).Dlc);
    if (canDlc > 8u)
    {
      /* only discrete values that are dividable by 4 */
      for (canCount = 0u; canCount < (CAN_DLC2LEN(canDlc) >> 2); canCount++) /* CM_CAN_LL10 */
      {
        Can_GetRxTmpBuf(canHwChannel).u.iData[canCount] = Buf->u.iData[canCount]; /* SBSW_CAN_LL10 */
      }
    }
    else
# endif
    {
      Can_GetRxTmpBuf(canHwChannel).u.iData[0] = Buf->u.iData[0]; /* SBSW_CAN_LL10 */
      Can_GetRxTmpBuf(canHwChannel).u.iData[1] = Buf->u.iData[1]; /* SBSW_CAN_LL10 */
    }

    /* Two conditions lead to a situation where the complete flag is set here:
        1) a new message was received while copying the mailbox contents to the temporary SW buffer
        2) the flag could not be cleared in the first place as HW copying to the mailbox was in progress

        The process of copying the data to the SW buffer is repeated until this flag is 0
        -> copied data is consistent (as flag cannot be cleared when hw copying is still in
          progress and is set to 1 when the copying of a new message starts (see HW manual)
        -> always the newest data is indicated

        Since most overruns will not be detected (only chance is here while accessing the
        HW buffer), there is no notification of an overrun in this case either
    */
    /* #30 repeat these actions if a new message was received during the copy process */
    if ((Can->CRBRCF[CanLL_BitIndex(rxFullPara->hwObjHandle)] & CanLL_SLRS(rxFullPara->hwObjHandle)) != 0u) /* COV_CAN_LL_NOT_IN_ALL_CONFIG XF */
    {
      CanLL_CanTimerStart(kCanLoopRxFcProcess); /* SBSW_CAN_LL12 */
      do
      {
        /* clear the new data flag of the receive buffer */
        Can->CRBRCF[CanLL_BitIndex(rxFullPara->hwObjHandle)] = CanLL_ClearBitRS(rxFullPara->hwObjHandle); /* SBSW_CAN_LL06 */

        /* copy mailbox contents to temporary buffer */
        Can_GetRxTmpBuf(canHwChannel).Id           = Buf->Id; /* SBSW_CAN_LL10 */
        Can_GetRxTmpBuf(canHwChannel).Dlc          = Buf->Dlc; /* SBSW_CAN_LL10 */
# if defined(C_ENABLE_CAN_FD_USED)
        Can_GetRxTmpBuf(canHwChannel).Fd           = Buf->Fd; /* SBSW_CAN_LL10 */
# endif
# if defined(C_ENABLE_CAN_FD_FULL)
        canDlc = CanRegToActualDLC(Can_GetRxTmpBuf(canHwChannel).Dlc);
        if (canDlc > 8u) /* COV_CAN_LL_NOT_IN_ALL_CONFIG XF */
        {
          /* only discrete values that are dividable by 4 */
          for (canCount = 0u; canCount < (CAN_DLC2LEN(canDlc) >> 2); canCount++) /* CM_CAN_LL10 */
          {
            Can_GetRxTmpBuf(canHwChannel).u.iData[canCount] = Buf->u.iData[canCount]; /* SBSW_CAN_LL10 */
          }
        }
        else
# endif
        {
          Can_GetRxTmpBuf(canHwChannel).u.iData[0] = Buf->u.iData[0]; /* SBSW_CAN_LL10 */
          Can_GetRxTmpBuf(canHwChannel).u.iData[1] = Buf->u.iData[1]; /* SBSW_CAN_LL10 */
        }

# if defined(C_ENABLE_HW_LOOP_TIMER)
        canHwLoopRetVal = CanLL_CanTimerLoop(kCanLoopRxFcProcess);
      } while ((canHwLoopRetVal != CAN_NOT_OK) && ((Can->CRBRCF[CanLL_BitIndex(rxFullPara->hwObjHandle)] & CanLL_SLRS(rxFullPara->hwObjHandle)) != 0u)); /* COV_CAN_LL_NOT_IN_ALL_CONFIG XF tx xf */
# else
      } while ((Can->CRBRCF[CanLL_BitIndex(rxFullPara->hwObjHandle)] & CanLL_SLRS(rxFullPara->hwObjHandle)) != 0u); /* COV_CAN_LL_NOT_IN_ALL_CONFIG XF */
# endif
      CanLL_CanTimerEnd(kCanLoopRxFcProcess); /* SBSW_CAN_LL12 */

# if defined(C_ENABLE_HW_LOOP_TIMER)
      /* #40 discard the message if it is inconsistent */
      if (canHwLoopRetVal == CAN_NOT_OK) /* COV_CAN_LL_NOT_IN_ALL_CONFIG XF */
      {
        Can->CRBRCF[CanLL_BitIndex(rxFullPara->hwObjHandle)] = CanLL_ClearBitRS(rxFullPara->hwObjHandle); /* SBSW_CAN_LL06 */
        retVal = kCanFailed;
      }
# endif
    }

    /* #50 set pointers in the receive structure */
    rxFullPara->rxStruct.pChipMsgObj = (CanChipMsgPtr)&(Can_GetRxTmpBuf(canHwChannel)); /* SBSW_CAN_LL11 */
    rxFullPara->rxStruct.pChipData = (CanChipDataPtr)&(Can_GetRxTmpBuf(canHwChannel).u.bData[0]); /* SBSW_CAN_LL11 */

# if defined(C_ENABLE_CAN_FD_USED)
    /* #60 discard CAN-FD messages if not enabled for the init object */
    if ((Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_NONE) && ((Can_GetRxTmpBuf(canHwChannel).Fd & kCanFdTypeFd) == kCanFdTypeFd)) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      retVal = kCanFailed;
    }
# endif
  }

# if defined(C_ENABLE_ECC_RX_REJECT)
  /* #70 discard messages in case of uncorrectable RAM errors */
  if (ApplCanEccRxReject(canHwChannel) == kCanTrue)
  {
    retVal = kCanFailed;
  }
# endif

  return (retVal);
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* CODE CATEGORY 1 END */


/**********************************************************************************************************************
 *  CanLL_RxFullReleaseObj
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxFullReleaseObj
Relation_Context:
# from CanHL_FullCanMsgReceived #
RxFullCANSupport
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
 V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(rxFullPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_RxFullMsgReceivedEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxFullMsgReceivedEnd
Relation_Context:
# from CanHL_FullCanMsgReceived #
RxFullCANSupport
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanRxFullParaStructPtr rxFullPara)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(rxFullPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */


# if defined( C_ENABLE_RX_FULLCAN_POLLING ) /* COV_CAN_RX_FULLCAN_POLLING */
/**********************************************************************************************************************
 *  CanLL_RxFullIsGlobalIndPending
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxFullIsGlobalIndPending
Relation_Context:
# from CanHL_RxFullCanPolling #
RxFullCANSupport, RxPolling
Relation:
OneChOpt
LLDerivative
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxFullIsGlobalIndPending(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 retVal = kCanFalse;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check the receive buffer new data registers for reception events */
  if (   ((Can->CRBRCF[0] & (kCanRegSizeCast)Can_GetRxFcMask0OfChannelData(canHwChannel)) != 0u)
#if (kCanNumberOfSharedReg16 > 1u)
      || ((Can->CRBRCF[1] & (kCanRegSizeCast)Can_GetRxFcMask1OfChannelData(canHwChannel)) != 0u)
#endif
#if (kCanNumberOfSharedReg16 > 2u)
      || ((Can->CRBRCF[2] & (kCanRegSizeCast)Can_GetRxFcMask2OfChannelData(canHwChannel)) != 0u)
#endif
#if (kCanNumberOfSharedReg16 > 3u) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_SHARED_REG */
      || ((Can->CRBRCF[3] & (kCanRegSizeCast)Can_GetRxFcMask3OfChannelData(canHwChannel)) != 0u)
#endif
     ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG */
  {
    retVal = kCanTrue;
  }

  return (retVal);
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_RxFullProcessPendings
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxFullIsGlobalIndPending
Relation_Context:
# from CanHL_RxFullCanPolling #
RxFullCANSupport, RxPolling
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_RxFullProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST CanTaskParaStructPtr taskPara)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call the reception handling if the mailbox received a new message */
  if ((Can->CRBRCF[CanLL_BitIndex(taskPara->hwObjHandle)] & CanLL_SLRS(taskPara->hwObjHandle)) != 0u)
  {
    CanHL_FullCanMsgReceivedPolling(CAN_HW_CHANNEL_CANPARA_FIRST taskPara->mailboxHandle, taskPara->hwObjHandle);
  }
}
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_RX_FULLCAN_POLLING */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */


/**********************************************************************************************************************
 *  CanLL_ErrorHandlingBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_ErrorHandlingBegin
Relation_Context:
# from CanHL_ErrorHandling() #
StatusPolling
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ErrorHandlingBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 2 END */

/**********************************************************************************************************************
 *  CanLL_BusOffOccured
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_BusOffOccured
Relation_Context:
# from CanHL_ErrorHandling() #
StatusPolling
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_BusOffOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 retVal = kCanFalse;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check if a busoff occurred and clear the corresponding flag in hardware */
  if (CanLL_HwWasBusOff(canHwChannel)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
  {
    Can->ChCtrl[mCanLogToPhys(canHwChannel)].EF = kCanEfMaskBusoffClear; /* SBSW_CAN_LL02 */
    retVal = kCanTrue;
  }

  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  return (retVal);
}
/* CODE CATEGORY 2 END */

#if defined( C_ENABLE_OVERRUN ) && defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/**********************************************************************************************************************
 *  CanLL_RxBasicCanOverrun
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_RxBasicCanOverrun
Relation_Context:
# from CanHL_ErrorHandling() #
StatusPolling, Overrun, RxBasicCANSupport
Relation:
OneChOpt
MultipleBasicCanObjects, ChannelAmount
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_RxBasicCanOverrun(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  CanObjectHandle mailboxHandle;
  CanObjectHandle hwObjHandle;
  vuint8 retVal = kCanFalse;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check if a receive FIFO buffer overrun occurred and clear the corresponding flags in hardware */
  if (((Can->CFMLSR & kCanRxFifoMask) & Can_GetRxBcMaskOfChannelData(canHwChannel)) != 0u)
  {
    mailboxHandle = CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel);
# if defined(C_ENABLE_MULTIPLE_BASICCAN)
    for (; mailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel); mailboxHandle++)
# endif
    {
      hwObjHandle = Can_GetMailboxHwHandle(mailboxHandle);
# if (CAN_SAFE_BSW == STD_ON)
      if (hwObjHandle < kCanMaxRxFifos) /* CM_CAN_LL05 */ /* COV_CAN_GENDATA_FAILURE */
# endif
      {
        Can->CRFSR[hwObjHandle] &= ((kCanRegSize) ~kCanSrFifoOverrun); /* SBSW_CAN_LL03 */ /* PRQA S 4399 */ /* MD_Can_IntegerCast */
      }
    }
    retVal = kCanTrue;
  }

  return (retVal);
}
/* CODE CATEGORY 2 END */
#endif


/**********************************************************************************************************************
 *  CanLL_ErrorHandlingEnd
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_ErrorHandlingEnd
Relation_Context:
# from CanHL_ErrorHandling() #
StatusPolling
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ErrorHandlingEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_AND_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 2 END */

#if defined( C_ENABLE_EXTENDED_STATUS )
/**********************************************************************************************************************
 *  CanLL_GetStatusBegin
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_GetStatusBegin
Relation_Context:
# from Can_GetStatus
CanGetStatus
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 3 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_GetStatusBegin(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary */
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 3 END */
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP ) && defined( C_ENABLE_WAKEUP_POLLING )
/**********************************************************************************************************************
 *  CanLL_WakeUpOccured
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_WakeUpOccured
Relation_Context:
# from Can_MainFunction_Wakeup #
WakeupPolling, Wakeup
Relation:
Wakeup, OneChOpt, IntLock, Wakeup
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 2 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_WakeUpOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 retVal = kCanFalse;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check if a wake-up event occured */
  if (CanLL_HwIsSleep(canHwChannel) &&
      (
#  if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL)
        (CanLL_CanWakeupOccurred(CAN_HW_CHANNEL_CANPARA_ONLY) == kCanOk) /* PRQA S 3415 */ /* MD_Can_RuntimeOptimization_LL */
#  endif
#  if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL) && defined(C_ENABLE_LL_CAN_WAKEUP_INTCB)
        ||
#  endif
#  if defined(C_ENABLE_LL_CAN_WAKEUP_INTCB)
        (ApplCanWakeupOccurred(canHwChannel) == CAN_OK) /* PRQA S 3415 */ /* MD_Can_RuntimeOptimization_LL */
#  endif
      )
     )
  {
    retVal = kCanTrue;
  }

  return (retVal);
}
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP )
/**********************************************************************************************************************
 *  CanLL_WakeUpHandling
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_WakeUpHandling
Relation_Context:
# from Can_MainFunction_Wakeup #
WakeupPolling, Wakeup
# from Wakeup Interrupt #
Relation:
OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WakeUpHandling(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call wakeup transition handling */
  CAN_WAKEUP(channel);
  /* #20 call wakeup indication */
  APPL_CAN_WAKEUP(channel);
}
/* CODE CATEGORY 4 END */
#endif

/**********************************************************************************************************************
 *  CanLL_ModeTransition
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_ModeTransition
Relation_Context:
# from CanHL_ModeTransition() #
Wakeup, OneChOpt, HardwareLoopCheck, ChannelAmount
RamCheck, OneChOpt, HardwareLoopCheck, ChannelAmount
# from Can_Mainfunction_Mode() #
ChannelAmount
Relation:
OneChOpt, Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount
OneChOpt, Wakeup, ReInitStart
OneChOpt, Wakeup, SilentMode
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_STATIC, vuint8, STATIC_CODE) CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANTYPE_FIRST vuint8 mode, vuint8 busOffRecovery, vuint8 ramCheck)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 retVal = kCanFailed;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 no actions necessary for ResetBusOffStart transition */
  if (mode == kCanModeResetBusOffStart)
  {
    retVal = kCanOk;
  }
  else
  {
    /* #20 perform no transition if the hardware is currently in BusOff state and the recovery shall be continued */
    if ((busOffRecovery == kCanContinueBusOffRecovery) && CanLL_HwIsBusOff(canHwChannel)) /* COV_CAN_LL_NOT_IN_ALL_CONFIG XF tf xf */
    {
      retVal = kCanRequested;
    }
    else
    {
      /* #30 transit to channel reset mode *   //CanLL_ChannelTransitionReset 函数作用  主要实现将CAN 控制器 设置为 kCanResetMode*/
      if (CanLL_ChannelTransitionReset(CAN_CHANNEL_CANPARA_ONLY) == kCanOk) /* COV_CAN_LL_MODE_CHECK */ /* PRQA S 2991, 2995 */ /* MD_Can_ConstValue */
      {
        /* #40 transit to target mode */
        switch(mode)
        {
          case kCanModeStopReinitFast:
          case kCanModeStopReinit:
#if defined(C_ENABLE_SLEEP_WAKEUP)
          case kCanModeWakeupStopReinit:
            /* CanHL_ReInit() also disables the wakeup interrupt */
#endif
            retVal = CanHL_ReInit(CAN_CHANNEL_CANPARA_FIRST ramCheck);
            break;

#if defined(C_ENABLE_SLEEP_WAKEUP)
          //CanLL_ChannelTransitionSleep  模式控制，暂时设为空
          case kCanModeSleep:
            retVal = CanLL_ChannelTransitionSleep(CAN_CHANNEL_CANPARA_ONLY);
            break;
#endif /* C_ENABLE_SLEEP_WAKEUP */

          case kCanModeResetBusOffEnd:
#if (CAN_REINIT_START == STD_ON) 
          case kCanModeStartReinit:
#endif
            if (CanHL_ReInit(CAN_CHANNEL_CANPARA_FIRST ramCheck) == kCanOk) /* COV_CAN_GENDATA_FAILURE */
            {
              retVal = CanLL_ChannelTransitionStart(CAN_CHANNEL_CANPARA_ONLY);
            } /* else retVal is kCanFailed */
            break;

#if (CAN_REINIT_START == STD_OFF) 
          case kCanModeStart:
            retVal = CanLL_ChannelTransitionStart(CAN_CHANNEL_CANPARA_ONLY);
            break;
#endif

#if defined(C_ENABLE_SILENT_MODE)
          case kCanModeSilent:
            if (CanLL_ChannelTransitionHalt(CAN_CHANNEL_CANPARA_ONLY) == kCanOk) /* COV_CAN_LL_MODE_CHECK */ /* PRQA S 2991, 2995 */ /* MD_Can_ConstValue */
            {
          //    Can->ChCtrl[mCanLogToPhys(canHwChannel)].CR |= kCanCrListenOnlyMode; /* SBSW_CAN_LL02 */
              retVal = CanLL_ChannelTransitionStart(CAN_CHANNEL_CANPARA_ONLY);
            } /* else retVal is kCanFailed */
            break;
#endif

          default:
            /* retVal is kCanFailed */
            break;
        }
      } /* else retVal is kCanFailed */
    }
  }

  return (retVal);
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
/* CODE CATEGORY 4 END */






#if defined( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL )
/**********************************************************************************************************************
 *  CanLL_CanInterruptDisable
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_CanInterruptDisable
Relation_Context:
# from Can_DisableControllerInterrupts #
IndividualPolling
TxPolling
RxPolling
StatusPolling
IntLock
Relation:
Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount, Overrun, CanInterruptControl, IntcAccessByAppl
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptDisable(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOldPtr localInterruptOldFlagPtr)
{
# if defined(C_ENABLE_LL_CAN_INTCTRL)
  /* ----- Local Variables ---------------------------------------------- */
#  if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
  vuint8 canDummy = 0; /* PRQA S 2981 */ /* MD_Can_RedundantInit */
#   if defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_TX_POLLING)
  tCanIntcChTxPtr CanIntcChTx = (tCanIntcChTxPtr)mCanIntcChTxAdr(canHwChannel);
#   endif
#   if !defined(C_ENABLE_ERROR_POLLING)
  tCanIntcChErrPtr CanIntcChErr = (tCanIntcChErrPtr)mCanIntcChErrorAdr(canHwChannel);
#   endif
#   if defined(C_ENABLE_LL_WAKEUP_SUPPORT) && !defined(C_ENABLE_WAKEUP_POLLING)
  tCanIntcChWupPtr CanIntcChWup = (tCanIntcChWupPtr)mCanIntcChWakeupAdr(canHwChannel);
#   endif
#  endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 if the interrupts of no other channels are currently disabled */
  if (canInterruptOldFlag.GErrCnt == kCanZero) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
#  if (defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_RX_BASICCAN_POLLING)) && defined(C_ENABLE_RX_BASICCAN_OBJECTS)
    /* #20 save current status and disable global receive FIFO interrupt */
    CanLL_IntcIntSave(CanIsrRxFifo, canInterruptOldFlag.RF, CanIntcRxFifo->RF);
    CanLL_IntcIntDisable(CanIsrRxFifo, CanIntcRxFifo->RF); /* SBSW_CAN_LL13 */
#   if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
    CanLL_IntcIntSave(CanIsrRxFifo, canDummy, CanIntcRxFifo->RF); /* PRQA S 2982 */ /* MD_Can_DummyRead_LL */
#   endif
#  endif
#  if !defined(C_ENABLE_ERROR_POLLING) && defined(C_ENABLE_OVERRUN) && defined(C_ENABLE_RX_BASICCAN_OBJECTS)
    /* #30 save current status and disable global error interrupt */
    CanLL_IntcIntSave(CanIsrGlobalStatus, canInterruptOldFlag.GErr, CanIntcGErr->GErr);
    CanLL_IntcIntDisable(CanIsrGlobalStatus, CanIntcGErr->GErr); /* SBSW_CAN_LL13 */
#   if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
    CanLL_IntcIntSave(CanIsrGlobalStatus, canDummy, CanIntcGErr->GErr); /* PRQA S 2982 */ /* MD_Can_DummyRead_LL */
#   endif
#  endif
  }
  canInterruptOldFlag.GErrCnt++;
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_TX_POLLING)
  /* #40 save current status and disable channel Tx interrupt */
  CanLL_IntcIntSave(Can_GetIsrTxIdOfOsIsrId(canHwChannel), (*(localInterruptOldFlagPtr)).Tx, CanIntcChTx->Tx); /* SBSW_CAN_LL14 */
  CanLL_IntcIntDisable(Can_GetIsrTxIdOfOsIsrId(canHwChannel), CanIntcChTx->Tx); /* SBSW_CAN_LL13 */
#   if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
  CanLL_IntcIntSave(Can_GetIsrTxIdOfOsIsrId(canHwChannel), canDummy, CanIntcChTx->Tx); /* PRQA S 2982 */ /* MD_Can_DummyRead_LL */
#   endif
#  endif
#  if !defined(C_ENABLE_ERROR_POLLING)
  /* #50 save current status and disable channel error interrupt */
  CanLL_IntcIntSave(Can_GetIsrStatusIdOfOsIsrId(canHwChannel), (*(localInterruptOldFlagPtr)).Err, CanIntcChErr->Err); /* SBSW_CAN_LL14 */
  CanLL_IntcIntDisable(Can_GetIsrStatusIdOfOsIsrId(canHwChannel), CanIntcChErr->Err); /* SBSW_CAN_LL13 */
#   if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
  CanLL_IntcIntSave(Can_GetIsrStatusIdOfOsIsrId(canHwChannel), canDummy, CanIntcChErr->Err); /* PRQA S 2982 */ /* MD_Can_DummyRead_LL */
#   endif
#  endif
#  if defined(C_ENABLE_LL_WAKEUP_SUPPORT) && !defined(C_ENABLE_WAKEUP_POLLING)
  /* #60 save current status and disable channel wakeup interrupt */
  CanLL_IntcIntSave(Can_GetIsrWakeupIdOfOsIsrId(canHwChannel), (*(localInterruptOldFlagPtr)).Wup, CanIntcChWup->Wup); /* SBSW_CAN_LL14 */
  CanLL_IntcIntDisable(Can_GetIsrWakeupIdOfOsIsrId(canHwChannel), CanIntcChWup->Wup); /* SBSW_CAN_LL13 */
#   if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
  CanLL_IntcIntSave(Can_GetIsrWakeupIdOfOsIsrId(canHwChannel), canDummy, CanIntcChWup->Wup); /* PRQA S 2982 */ /* MD_Can_DummyRead_LL */
#   endif
#  endif

#  if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
  /* #70 synchronize processor pipeline */
  /* insertion of SYNCP in combination with dummy reading the INTC-related registers above ensures
     compliance to the RH850 usage notes regarding synchronization of subsequent instructions */
  CanLL_SYNCP(); /* SBSW_CAN_LL18 */ /* PRQA S 1006 */ /* MD_Can_Assembler_LL */

  CAN_DUMMY_STATEMENT(canDummy); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
# endif /* C_ENABLE_LL_CAN_INTCTRL */
  CAN_DUMMY_STATEMENT(localInterruptOldFlagPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */

/**********************************************************************************************************************
 *  CanLL_CanInterruptRestore
 *********************************************************************************************************************/
/*
|<DataModelStart>| CanLL_CanInterruptRestore
Relation_Context:
# from Can_EnableControllerInterrupts #
IndividualPolling
TxPolling
RxPolling
StatusPolling
Relation:
Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount, Overrun, IntcAccessByAppl, CanInterruptControl
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanInterruptRestore(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOld localInterruptOldFlag)
{
# if defined(C_ENABLE_LL_CAN_INTCTRL)
  /* ----- Local Variables ---------------------------------------------- */
#  if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
#   if defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_TX_POLLING)
  tCanIntcChTxPtr CanIntcChTx = (tCanIntcChTxPtr)mCanIntcChTxAdr(canHwChannel);
#   endif
#   if !defined(C_ENABLE_ERROR_POLLING)
  tCanIntcChErrPtr CanIntcChErr = (tCanIntcChErrPtr)mCanIntcChErrorAdr(canHwChannel);
#   endif
#   if defined(C_ENABLE_LL_WAKEUP_SUPPORT) && !defined(C_ENABLE_WAKEUP_POLLING)
  tCanIntcChWupPtr CanIntcChWup = (tCanIntcChWupPtr)mCanIntcChWakeupAdr(canHwChannel);
#   endif
#  endif

  /* ----- Implementation ----------------------------------------------- */
  canInterruptOldFlag.GErrCnt--;
  /* #10 if the interrupts of no other channels are currently disabled */
  if (canInterruptOldFlag.GErrCnt == kCanZero) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
#  if (defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_RX_BASICCAN_POLLING)) && defined(C_ENABLE_RX_BASICCAN_OBJECTS)
    /* #20 restore previous status of global receive FIFO interrupt */
    CanLL_IntcIntRestore(CanIsrRxFifo, CanIntcRxFifo->RF, canInterruptOldFlag.RF); /* SBSW_CAN_LL13 */
#  endif
#  if !defined(C_ENABLE_ERROR_POLLING) && defined(C_ENABLE_OVERRUN) && defined(C_ENABLE_RX_BASICCAN_OBJECTS)
    /* #30 restore previous status of global error interrupt */
    CanLL_IntcIntRestore(CanIsrGlobalStatus, CanIntcGErr->GErr, canInterruptOldFlag.GErr); /* SBSW_CAN_LL13 */
#  endif
  }
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_TX_POLLING)
  /* #40 restore previous status of channel Tx interrupt */
  CanLL_IntcIntRestore(Can_GetIsrTxIdOfOsIsrId(canHwChannel), CanIntcChTx->Tx, localInterruptOldFlag.Tx); /* SBSW_CAN_LL13 */
#  endif
#  if !defined(C_ENABLE_ERROR_POLLING)
  /* #50 restore previous status of channel error interrupt */
  CanLL_IntcIntRestore(Can_GetIsrStatusIdOfOsIsrId(canHwChannel), CanIntcChErr->Err, localInterruptOldFlag.Err); /* SBSW_CAN_LL13 */
#  endif
#  if defined(C_ENABLE_LL_WAKEUP_SUPPORT) && !defined(C_ENABLE_WAKEUP_POLLING)
  /* #60 restore previous status of channel wakeup interrupt */
  CanLL_IntcIntRestore(Can_GetIsrWakeupIdOfOsIsrId(canHwChannel), CanIntcChWup->Wup, localInterruptOldFlag.Wup); /* SBSW_CAN_LL13 */
#  endif
# endif /* C_ENABLE_LL_CAN_INTCTRL */
  CAN_DUMMY_STATEMENT(localInterruptOldFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_HW_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 1 END */
#endif

#if defined(C_ENABLE_LL_CAN_INTCTRL) && defined(C_ENABLE_LL_WAKEUP_SUPPORT) && !defined(C_ENABLE_WAKEUP_POLLING)
/****************************************************************************
| NAME:             CanLL_CanWakeupInterruptDisable()
****************************************************************************/
/*
|<DataModelStart>| CanLL_CanWakeupInterruptDisable
Relation_Context:
# from CanLL_InitBegin #
Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount
Relation:
IntcAccessByAppl, CanInterruptControl, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanWakeupInterruptDisable(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOldPtr localInterruptOldFlagPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
# if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
  tCanIntcChWupPtr CanIntcChWup = (tCanIntcChWupPtr)mCanIntcChWakeupAdr(canHwChannel);
# endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 disable wakeup interrupt in hardware and saved interrupt status */
  CanLL_IntcIntDisable(Can_GetIsrWakeupIdOfOsIsrId(canHwChannel), CanIntcChWup->Wup); /* SBSW_CAN_LL13 */
  CanLL_IntcIntDisableLoc((*(localInterruptOldFlagPtr)).Wup); /* SBSW_CAN_LL14 */
}
/* CODE CATEGORY 4 END */

/****************************************************************************
| NAME:             CanLL_CanWakeupInterruptEnable()
****************************************************************************/
/*
|<DataModelStart>| CanLL_CanWakeupInterruptEnable
Relation_Context:
# from CanLL_ChannelTransitionSleep #
ChannelAmount, HardwareLoopCheck, Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling
Relation:
IntcAccessByAppl, CanInterruptControl, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_CanWakeupInterruptEnable(CAN_HW_CHANNEL_CANTYPE_FIRST tCanLLCanIntOldPtr localInterruptOldFlagPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
# if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
  tCanIntcChWupPtr CanIntcChWup = (tCanIntcChWupPtr)mCanIntcChWakeupAdr(canHwChannel);
# endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 if channel interrupts are currently enabled */
  if (Can_GetCanInterruptCounter(canHwChannel) == (tCanIntCnt)0) /* COV_CAN_LL_NOT_IN_ALL_CONFIG XF */
  {
    /* #20 enable wakeup interrupt in hardware */
    CanLL_IntcIntEnable(Can_GetIsrWakeupIdOfOsIsrId(canHwChannel), CanIntcChWup->Wup); /* SBSW_CAN_LL13 */
  }
  /* #30 if channel interrupts are currently disabled */
  else
  {
    /* #40 enable wakeup interrupt in saved interrupt status */
    CanLL_IntcIntEnableLoc((*(localInterruptOldFlagPtr)).Wup); /* SBSW_CAN_LL14 */
  }
}
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_LL_CAN_INTCTRL && C_ENABLE_LL_WAKEUP_SUPPORT && !C_ENABLE_WAKEUP_POLLING */

#if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL) && defined(C_ENABLE_WAKEUP_POLLING)
/****************************************************************************
| NAME:             CanLL_CanWakeupOccurred()
****************************************************************************/
/*
|<DataModelStart>| CanLL_CanWakeupInterruptEnable
Relation_Context:
# from CanLL_ChannelTransitionSleep #
ChannelAmount, HardwareLoopCheck, Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling
Relation:
IntcAccessByAppl, CanInterruptControl, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CanWakeupOccurred(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
# if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
  tCanIntcChWupPtr CanIntcChWup = (tCanIntcChWupPtr)mCanIntcChWakeupAdr(canHwChannel);
# endif
  vuint8 retVal = kCanFailed;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 get status of wakeup interrupt request flag */
  if (CanLL_IntcIntFlag(Can_GetIsrWakeupIdOfOsIsrId(canHwChannel), CanIntcChWup->uWup))
  {
    retVal = kCanOk;
  }

  return (retVal);
}
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_LL_CAN_WAKEUP_INTCTRL && C_ENABLE_WAKEUP_POLLING */

#if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL)
/****************************************************************************
| NAME:             CanLL_ClearCanWakeupInterruptFlag()
****************************************************************************/
/*
|<DataModelStart>| CanLL_ClearCanWakeupInterruptFlag
Relation_Context:
# from CanLL_ChannelTransitionSleep #
Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount
Relation:
IntcAccessByAppl, CanInterruptControl, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ClearCanWakeupInterruptFlag(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
# if defined(C_ENABLE_INTC_ACCESS_BY_APPL) || !defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
  tCanIntcChWupPtr CanIntcChWup = (tCanIntcChWupPtr)mCanIntcChWakeupAdr(canHwChannel);
# endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 clear wakeup interrupt request flag */
  CanLL_IntcIntClear(Can_GetIsrWakeupIdOfOsIsrId(canHwChannel), CanIntcChWup->uWup); /* SBSW_CAN_LL13 */
}
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_LL_CAN_WAKEUP_INTCTRL */

#if defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
# if !defined(C_ENABLE_INTC_ACCESS_BY_APPL) 
#  if defined(C_ENABLE_LL_CAN_INTCTRL)
/****************************************************************************
| NAME:             CanLL_OsIsInterruptSourceEnabled()
****************************************************************************/
/*
|<DataModelStart>| CanLL_OsIsInterruptSourceEnabled
Relation_Context:
# from CanLL_CanInterruptDisable #
Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount, CanInterruptControl, IntcAccessByAppl, IntLock, Overrun
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, boolean, STATIC_CODE) CanLL_OsIsInterruptSourceEnabled(Can_ExternalISRType IsrId)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 retrieve interrupt enable status */
  (void)osIsInterruptSourceEnabled(IsrId, &retVal); /* SBSW_CAN_LL16 */
  return retVal;
}
/* CODE CATEGORY 1 END */

/****************************************************************************
| NAME:             CanLL_OsRestoreInterruptSource()
****************************************************************************/
/*
|<DataModelStart>| CanLL_OsRestoreInterruptSource
Relation_Context:
# from CanLL_CanInterruptRestore #
Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount, IntLock, CanInterruptControl
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_OsRestoreInterruptSource(Can_ExternalISRType IsrId, boolean OldFlag)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 if interrupt was previously enabled */
  if (OldFlag==TRUE) /* COV_CAN_LL_NOT_IN_ALL_CONFIG TX */
  {
    /* #20 enable interrupt */
    (void)osEnableInterruptSource(IsrId, FALSE);
  }
}
/* CODE CATEGORY 1 END */
#  endif

#  if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL) && defined(C_ENABLE_WAKEUP_POLLING)
/****************************************************************************
| NAME:             CanLL_OsIsInterruptPending()
****************************************************************************/
/*
|<DataModelStart>| CanLL_OsIsInterruptPending
Relation_Context:
# from CanLL_CanWakeupOccurred #
Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount, IntLock, CanInterruptControl
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, boolean, STATIC_CODE) CanLL_OsIsInterruptPending(Can_ExternalISRType IsrId)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 retrieve interrupt pending status */
  (void)osIsInterruptPending(IsrId, &retVal); /* SBSW_CAN_LL16 */
  return retVal;
}
/* CODE CATEGORY 4 END */
#  endif
# endif
#endif


/****************************************************************************
| NAME:             CanLL_InitPowerOnModeTransitions()
****************************************************************************/
/*
|<DataModelStart>| CanLL_InitPowerOnModeTransitions
Relation_Context:
# from CanLL_InitPowerOn #
Relation:
HardwareLoopCheck, OneChOpt
EccConfiguration
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitPowerOnModeTransitions(void)
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_HW_LOOP_TIMER)
  CAN_CHANNEL_CANTYPE_LOCAL
#endif

  /* ----- Implementation ----------------------------------------------- */
#if defined(C_ENABLE_HW_LOOP_TIMER) && defined(C_MULTIPLE_RECEIVE_CHANNEL)
  channel = 0;
#endif



}
/* CODE CATEGORY 4 END */

/****************************************************************************
| NAME:             CanLL_InitPowerOnGlobalInit()
****************************************************************************/
/*
|<DataModelStart>| CanLL_InitPowerOnGlobalInit
Relation_Context:
# from CanLL_InitPowerOn #
Relation:
OneChOpt
LLDerivative
Variant, OneChOpt, ChannelAmount, OneChOpt
Variant, OneChOpt, RxFullCANSupport, ChannelAmount
TxHwFifo, TxBasicAmount, ChannelAmount
GlobalInitPostProcess
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitPowerOnGlobalInit(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  CAN_CHANNEL_CANTYPE_LOCAL
#if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel;
#endif
  vuint8 canFcObjTmp;
  vuint8 canPhysChannelIndex;
  vuint8 canFifoIndex;

  /* ----- Implementation ----------------------------------------------- */
  canFcObjTmp = kCanZero;

  /* #10 clear receive rule settings */
  CanLL_WriteRegGlobalRegSize(&Can->CRNCFG[0], kCanZero); /* SBSW_CAN_LL02 */
#if (kCanMaxPhysChannels > 4)
  CanLL_WriteRegGlobalRegSize(&Can->CRNCFG[1], kCanZero); /* SBSW_CAN_LL02 */
#endif

  /* #20 clear shared buffer assignments */
  for (canFifoIndex = 0; canFifoIndex < kCanMaxRxFifos; canFifoIndex++) /* CM_CAN_LL05 */
  {
    CanLL_WriteRegGlobalRegSize(&Can->CRFCR[canFifoIndex], kCanZero); /* SBSW_CAN_LL03 */
  }
  for (canPhysChannelIndex = 0; canPhysChannelIndex < kCanMaxPhysChannels; canPhysChannelIndex++) /* CM_CAN_LL04 */
  {
    for (canFifoIndex = 0; canFifoIndex < kCanMaxTxFifos; canFifoIndex++) /* CM_CAN_LL07 */
    {
      CanLL_WriteRegGlobal32(&Can->ChFC[canPhysChannelIndex].TRFCR[canFifoIndex], kCanZero); /* SBSW_CAN_LL05 */
    }
  }

#if defined(C_MULTIPLE_RECEIVE_CHANNEL)
  /* #30 iterate logical channels */
  for (channel = 0; channel < kCanNumberOfChannels; channel++)
#endif
  {
    /* #40 if channel is used in selected identity */
#if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_GetCanIfChannelId(channel) != CAN_NO_CANIFCHANNELID) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#endif
    {
#if defined(C_MULTIPLE_PHYS_CHANNEL)
      canPhysChannel = mCanLogToPhys(channel);
#endif

      /* #50 transit to channel reset mode */
      CanLL_ModeReq_Phys(canPhysChannel, kCanResetMode); /* SBSW_CAN_LL02 */
      if (!CanLL_ModeCheck_Phys(canPhysChannel, kCanResetMode)) /* COV_CAN_LL_MODE_CHECK */
      {
        CanLL_ModeWait(CAN_CHANNEL_CANPARA_FIRST canPhysChannel, kCanResetMode, kCanLoopGlobalInit);
      }

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
      /* #60 prepare receive buffer layout configuration */
      canFcObjTmp += Can_GetRxFcCount(channel); /* PRQA S 2986 */ /* MD_Can_ConstValue */
#endif

      /* #70 clear transmit buffer linkage by transmit queue */
      CanLL_WriteRegGlobalRegSize(&Can->TQCR[canPhysChannel], kCanZero); /* SBSW_CAN_LL02 */
      /* tx buffer linkage by transmit / receive FIFOs has already been cleared */

#if defined(C_ENABLE_TX_HW_FIFO)
      /* #80 configure transmit FIFO objects */
      for (canFifoIndex = kCanZero; canFifoIndex < Can_GetTxFifoCountOfChannelData(channel); canFifoIndex++) /* CM_CAN_LL07 */
      {
        CanLL_WriteRegGlobal32(&Can->ChFC[canPhysChannel].TRFCR[canFifoIndex], Can_GetTxFifoData(Can_GetTxFifoStartIndexOfChannelData(channel) + canFifoIndex)); /* SBSW_CAN_LL05 */
      }
#endif

      /* #90 initialize filter rules and receive FIFO buffers */
      CanLL_InitPowerOnRuleAndFifoInit(CAN_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
    } /* if channel is used in selected identity */
  } /* iterate logical channels */

  /* #100 configure receive buffer layout and finish the global initialization */
#if defined(C_ENABLE_CAN_FD_FULL)
  CanLL_WriteRegGlobalRegSize(&Can->CRBNUM, ((((kCanRegSize)Can_GetRxBufferPayloadStorageSize()) << 8) | canFcObjTmp)); /* SBSW_CAN_LL01 */
#else
  CanLL_WriteRegGlobalRegSize(&Can->CRBNUM, canFcObjTmp); /* SBSW_CAN_LL01 */
#endif

#if defined(C_ENABLE_GLOBAL_INIT_POST_PROCESS)
  ApplCanGlobalInitPostProcessing();
#endif

  /* receiving (disable rule write access) */
  CanLL_WriteRegGlobalRegSize(&Can->CRECR, kCanRuleReceive); /* SBSW_CAN_LL01 */
}
/* CODE CATEGORY 4 END */

/****************************************************************************
| NAME:             CanLL_InitPowerOnRuleAndFifoInit()
****************************************************************************/
/*
|<DataModelStart>| CanLL_InitPowerOnRuleAndFifoInit
Relation_Context:
# from CanLL_InitPowerOnGlobalInit #
OneChOpt, Variant, ChannelAmount
Relation:
OneChOpt, RxFullCANSupport, RxBasicCANSupport, TxHwFifo, ChannelAmount
RxFullCANSupport, ChannelAmount, IDType
RxBasicCANSupport, MultipleBasicCanObjects, ChannelAmount
RxBasicCANSupport, CanFdSupport
RxBasicCANSupport, DevErrorDetect
GlobalInitPostProcess, RxFullCANSupport, RxBasicCANSupport
OneChOpt, RxFullCANSupport, RxBasicCANSupport, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitPowerOnRuleAndFifoInit(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_MULTIPLE_PHYS_CHANNEL)
# if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS) || defined(C_ENABLE_TX_HW_FIFO)
  CanChannelHandle canPhysChannel;
# endif
#endif
#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS) || defined(C_ENABLE_TX_HW_FIFO)
  CanObjectHandle hwObjHandle;
#endif
#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS)
  CanObjectHandle mailboxHandle;
  kCanRegSize canTmpRegRs;
  vuint8 canFilterRulesIndex;
  vuint8 canFilterRulesPage;
#endif
#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
  vuint8 canLogHwFifoHandle;
  vuint8 canFilterRulesBcIndex;
  vuint8 canFilterRulesBcStartIndex;
  vuint8 canFilterRulesBcStopIndex;
#endif

  /* ----- Implementation ----------------------------------------------- */
#if defined(C_MULTIPLE_PHYS_CHANNEL)
# if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS) || defined(C_ENABLE_TX_HW_FIFO)
  canPhysChannel = mCanLogToPhys(channel);
# endif
#endif

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS)
  /* #10 configure filter rule layout */
  canTmpRegRs = (Can->CRNCFG[CanLL_ByteIndex(canPhysChannel)] | CanLL_FilterListConfig(canPhysChannel, Can_GetFrTotalCountOfChannelData(channel)));
  CanLL_WriteRegGlobalRegSize(&Can->CRNCFG[CanLL_ByteIndex(canPhysChannel)], canTmpRegRs); /* SBSW_CAN_LL02 */

  canFilterRulesIndex = (vuint8) (Can_GetFrStartIndexOfChannelData(channel) & kCanRuleIndexMask);
  canFilterRulesPage = (vuint8) ((Can_GetFrStartIndexOfChannelData(channel) & kCanRulePageMask) >> kCanRulePageShiftVal);
  CanLL_WriteRegGlobalRegSize(&Can->CRECR, (kCanRegSize)(kCanRuleWrite | canFilterRulesPage)); /* SBSW_CAN_LL01 */ /* PRQA S 4391 */ /* MD_Can_IntegerCast */
#endif

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
  /* #20 iterate receive FullCAN objects */
  for (mailboxHandle=CAN_HL_MB_RX_FULL_STARTINDEX(channel); mailboxHandle<CAN_HL_MB_RX_FULL_STOPINDEX(channel); mailboxHandle++)
  {
    hwObjHandle = Can_GetMailboxHwHandle(mailboxHandle);

    /* #30 initialize filter rules for FullCAN objects */
    CanLL_InitPowerOnRulePageUpdate(&canFilterRulesIndex, &canFilterRulesPage); /* SBSW_CAN_LL16 */ /* CM_CAN_LL09 */

# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
    if ((Can_GetMailboxIDValue(mailboxHandle) & CAN_ID_IDE_MASK) != CAN_ID_IDE_MASK) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* PRQA S 2991, 2995 */ /* MD_Can_ConstValue */
    {
      CanLL_WriteRegGlobal32(&mRuleCode(canFilterRulesIndex), MK_STDID0(Can_GetMailboxIDValue(mailboxHandle))); /* SBSW_CAN_LL07 */ /* PRQA S 4491 */ /* MD_Can_IntegerCast */
      CanLL_WriteRegGlobal32(&mRuleMask(canFilterRulesIndex), kCanRuleStdMustMatch); /* SBSW_CAN_LL07 */
    }
    else
#  endif
    {
      CanLL_WriteRegGlobal32(&mRuleCode(canFilterRulesIndex), MK_EXTID0(Can_GetMailboxIDValue(mailboxHandle))); /* SBSW_CAN_LL07 */ /* PRQA S 2880 */ /* MD_Can_ConstValue */
      CanLL_WriteRegGlobal32(&mRuleMask(canFilterRulesIndex), kCanRuleExtMustMatch); /* SBSW_CAN_LL07 */
    }
# else
    {
      CanLL_WriteRegGlobal32(&mRuleCode(canFilterRulesIndex), MK_STDID0(Can_GetMailboxIDValue(mailboxHandle))); /* SBSW_CAN_LL07 */ /* PRQA S 4491 */ /* MD_Can_IntegerCast */
      CanLL_WriteRegGlobal32(&mRuleMask(canFilterRulesIndex), kCanRuleStdMustMatch); /* SBSW_CAN_LL07 */
    }
# endif
    /* store messages in global rx buffers */
    CanLL_WriteRegGlobal32(&mRuleBuf(canFilterRulesIndex), (kCanRuleUseBuf | (((vuint32)(hwObjHandle)) << 8))); /* SBSW_CAN_LL07 */
    CanLL_WriteRegGlobal32(&mRuleFifo(canFilterRulesIndex), kCanZero); /* SBSW_CAN_LL07 */
    canFilterRulesIndex++;
  }
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
  /* #40 iterate receive BasicCAN objects */
  mailboxHandle = CAN_HL_MB_RX_BASIC_STARTINDEX(channel);
  hwObjHandle = Can_GetMailboxHwHandle(mailboxHandle);
# if defined(C_ENABLE_MULTIPLE_BASICCAN)
  for (; mailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(channel); mailboxHandle++)
# endif
  {
# if (CAN_SAFE_BSW == STD_ON)
    if (hwObjHandle < kCanMaxRxFifos) /* CM_CAN_LL05 */ /* COV_CAN_GENDATA_FAILURE */
# endif
    {
      /* #50 initialize filter rules for BasicCAN objects */
      canLogHwFifoHandle = (vuint8)hwObjHandle;
      canFilterRulesBcStartIndex = Can_GetFilterStartIndexOfRxFifoData(canLogHwFifoHandle);
      canFilterRulesBcStopIndex = Can_GetFilterStopIndexOfRxFifoData(canLogHwFifoHandle);
      for (canFilterRulesBcIndex=canFilterRulesBcStartIndex; canFilterRulesBcIndex<canFilterRulesBcStopIndex; canFilterRulesBcIndex++)
      {
        CanLL_InitPowerOnRulePageUpdate(&canFilterRulesIndex, &canFilterRulesPage); /* SBSW_CAN_LL16 */ /* CM_CAN_LL09 */

        CanLL_WriteRegGlobal32(&mRuleCode(canFilterRulesIndex), ((vuint32) Can_GetCodeOfInitFilterRules(canFilterRulesBcIndex))); /* SBSW_CAN_LL07 */
        CanLL_WriteRegGlobal32(&mRuleMask(canFilterRulesIndex), ((vuint32) (kCanRuleHeader | Can_GetMaskOfInitFilterRules(canFilterRulesBcIndex)))); /* SBSW_CAN_LL07 */
        /* store messages in global rx fifos */
        CanLL_WriteRegGlobal32(&mRuleBuf(canFilterRulesIndex), kCanZero); /* SBSW_CAN_LL07 */
        CanLL_WriteRegGlobal32(&mRuleFifo(canFilterRulesIndex), CanLL_SL32(hwObjHandle)); /* SBSW_CAN_LL07 */ /* PRQA S 2985 */ /* MD_Can_ConstValue */
        canFilterRulesIndex++;
      }

      /* #60 configure receive FIFO objects */
# if defined(C_ENABLE_CAN_FD_FULL)
      canTmpRegRs = (kCanCrRxFifoSet | ((kCanRegSize)((kCanRegSize)Can_GetFifoDepthOfRxFifoData(canLogHwFifoHandle) << 8)) | ((kCanRegSize)((kCanRegSize)Can_GetFifoPayloadStorageSizeOfRxFifoData(canLogHwFifoHandle) << 4)));
# else
      canTmpRegRs = (kCanCrRxFifoSet | ((kCanRegSize)((kCanRegSize)Can_GetFifoDepthOfRxFifoData(canLogHwFifoHandle) << 8)));
# endif
# if defined(C_ENABLE_INDIVIDUAL_POLLING) || !defined(C_ENABLE_RX_BASICCAN_POLLING)
#  if defined(C_ENABLE_INDIVIDUAL_POLLING)
      if (!Can_IsMailboxIndivPolling(mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
      {
        canTmpRegRs |= kCanCrRxFifoIntEnable;
      }
# endif
      CanLL_WriteRegGlobalRegSize(&Can->CRFCR[hwObjHandle], canTmpRegRs); /* SBSW_CAN_LL03 */
    }
# if defined(C_ENABLE_MULTIPLE_BASICCAN)
    hwObjHandle++;
# endif
  }
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_GLOBAL_INIT_POST_PROCESS)
  /* #70 prepare global post processing information */
# if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS)
  CanLL_InitPowerOnRulePageUpdate(&canFilterRulesIndex, &canFilterRulesPage); /* SBSW_CAN_LL16 */
  CanAddFilterRulesStartPage = canFilterRulesPage;
  CanAddFilterRulesStartIndex = canFilterRulesIndex;
# else
  CanLL_WriteRegGlobalRegSize(&Can->CRECR, kCanRuleWrite); /* SBSW_CAN_LL01 */
  CanAddFilterRulesStartPage = 0;
  CanAddFilterRulesStartIndex = 0;
# endif
#endif

#if !defined(C_ENABLE_RX_FULLCAN_OBJECTS) && !defined(C_ENABLE_RX_BASICCAN_OBJECTS)
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}
/* CODE CATEGORY 4 END */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS) || defined(C_ENABLE_RX_BASICCAN_OBJECTS)
/****************************************************************************
| NAME:             CanLL_InitPowerOnRulePageUpdate()
****************************************************************************/
/*
|<DataModelStart>| CanLL_InitPowerOnRulePageUpdate
Relation_Context:
# from CanLL_InitPowerOnRuleAndFifoInit #
RxFullCANSupport, RxBasicCANSupport
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_InitPowerOnRulePageUpdate(CanVarPtr8 canFilterRulesIndexPtr, CanVarPtr8 canFilterRulesPagePtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 if receive rule write index exceeds current page */
  if (*canFilterRulesIndexPtr >= kCanMaxRuleAccessCell) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */ /* CM_CAN_LL09 */
  {
    /* #20 switch to next page and reset write index */
    (*canFilterRulesPagePtr)++; /* SBSW_CAN_LL11 */
    CanLL_WriteRegGlobalRegSize(&Can->CRECR, (kCanRegSize)(kCanRuleWrite | (*canFilterRulesPagePtr))); /* SBSW_CAN_LL01 */ /* PRQA S 4391 */ /* MD_Can_IntegerCast */
    (*canFilterRulesIndexPtr) = 0; /* SBSW_CAN_LL11 */
  }
}
/* CODE CATEGORY 4 END */
#endif

/****************************************************************************
| NAME:             CanLL_WriteReg32()
****************************************************************************/
/*
|<DataModelStart>| CanLL_WriteReg32
Relation_Context:
# CanLL_InitBeginSetRegisters() #
RamCheck
Relation:
RamCheck, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WriteReg32(CAN_CHANNEL_CANTYPE_FIRST CanChipMsgPtr32 regPtr, vuint32 val, CanInitParaStructPtr initPara)
{
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  /* ----- Local Variables ---------------------------------------------- */
  volatile vuint32 readBack;
  vuint8 result = kCanFalse; /* PRQA S 2981 */ /* MD_Can_TestCode_LL */
#endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 write register */
  *regPtr = val; /* SBSW_CAN_LL17 */

#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  if (initPara->doRamCheck == kCanExecuteRamCheck)
  {
    /* #20 read register */
    readBack = *regPtr;

    /* #30 mark as corrupt if value differs */
    if (readBack != val) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
    {
      result = kCanTrue; /* PRQA S 2982 */ /* MD_Can_TestCode_LL */
    }
    CAN_RAM_CHECK_READ_BACK_RESULT(channel)
    initPara->isChRamCheckFail |= result; /* SBSW_CAN_LL11 */
  }
# else
  CAN_DUMMY_STATEMENT(initPara); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
}
/* CODE CATEGORY 4 END */

/****************************************************************************
| NAME:             CanLL_WriteRegGlobal32()
****************************************************************************/
/*
|<DataModelStart>| CanLL_WriteRegGlobal32
Relation_Context:
# CanLL_InitPowerOnGlobalInit() #
CanFdSupport
CanFdConfiguration
# CanLL_InitPowerOnRuleAndFifoInit() #
RamCheck
Relation:
RamCheck
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_WriteRegGlobal32(CanChipMsgPtr32 regPtr, vuint32 val)
{
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  /* ----- Local Variables ---------------------------------------------- */
  volatile vuint32 readBack;
#endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 write register value */
  *regPtr = val; /* SBSW_CAN_LL17 */

#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  /* #20 read register */
  readBack = *regPtr;

  /* #30 mark global register RAM as corrupt if value differs */
  if (readBack != val) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
  {
    canIsCellCorrupt = kCanTrue;
  }
#endif
}
/* CODE CATEGORY 4 END */

/****************************************************************************
| NAME:             CanLL_ModeWait()
****************************************************************************/
/*
|<DataModelStart>| CanLL_ModeWait
Relation_Context:
# CanLL_InitPowerOnGlobalInit() #
ChannelAmount, OneChOpt
# CanLL_ChannelTransitionReset() #
ChannelAmount
# CanLL_ChannelTransitionSleep() #
ChannelAmount
# CanLL_ChannelTransitionStart() #
ChannelAmount, RamCheck
# CanLL_ChannelTransitionHalt() #
ChannelAmount
Relation:
HardwareLoopCheck
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_ModeWait(CAN_CHANNEL_CANTYPE_FIRST CanChannelHandle PhysChannel, vuint8 Mode, vuint8 Loop)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 wait until channel mode transition is completed successfully */
  CanLL_CanTimerStart(Loop); /* SBSW_CAN_LL12 */
#if defined(C_ENABLE_HW_LOOP_TIMER)
  while ((!CanLL_ModeCheck_Phys(PhysChannel, Mode)) && (CanLL_CanTimerLoop(Loop) != CAN_NOT_OK)) /* PRQA S 3415 */ /* MD_Can_RuntimeOptimization_LL */
#else
  while (!CanLL_ModeCheck_Phys(PhysChannel, Mode))
#endif
  {
    ;
  }
  CanLL_CanTimerEnd(Loop); /* SBSW_CAN_LL12 */

#if !defined(C_ENABLE_HW_LOOP_TIMER)
  CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(Loop); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}
/* CODE CATEGORY 4 END */

/****************************************************************************
| NAME:             CanLL_GlobalModeWait()
****************************************************************************/
/*
|<DataModelStart>| CanLL_GlobalModeWait
Relation_Context:
# CanLL_InitPowerOn() #
# CanLL_InitPowerOnModeTransitions() #
Relation:
HardwareLoopCheck, OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanLL_GlobalModeWait(vuint8 Mode, vuint8 Loop)
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_HW_LOOP_TIMER)
  CAN_CHANNEL_CANTYPE_LOCAL
#endif

  /* ----- Implementation ----------------------------------------------- */
#if defined(C_ENABLE_HW_LOOP_TIMER) && defined(C_MULTIPLE_RECEIVE_CHANNEL)
  channel = 0;
#endif

  /* #10 wait until global mode transition is completed successfully */
  CanLL_CanTimerStart(Loop); /* SBSW_CAN_LL12 */
#if defined(C_ENABLE_HW_LOOP_TIMER)
  while ((!CanLL_GlobalModeCheck(Mode)) && (CanLL_CanTimerLoop(Loop) != CAN_NOT_OK)) /* PRQA S 3415 */ /* MD_Can_RuntimeOptimization_LL */
#else
  while (!CanLL_GlobalModeCheck(Mode)) /* COV_CAN_LL_MODE_CHECK */
#endif
  {
    ;
  }
  CanLL_CanTimerEnd(Loop); /* SBSW_CAN_LL12 */

#if !defined(C_ENABLE_HW_LOOP_TIMER)
  CAN_DUMMY_STATEMENT(Loop); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}
/* CODE CATEGORY 4 END */

/****************************************************************************
| NAME:             CanLL_ChannelTransitionReset()
****************************************************************************/
/*
|<DataModelStart>| CanLL_ChannelTransitionReset
Relation_Context:
# CanLL_ModeTransition() #
OneChOpt
Relation:
OneChOpt, ChannelAmount
HardwareLoopCheck, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ChannelTransitionReset(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel = mCanLogToPhys(canHwChannel);
#endif
  vuint8 retVal = kCanFailed; /* PRQA S 2981 */ /* MD_Can_RedundantInit */



  retVal = kCanOk;
#if 0  /*DELETE  主要实现将CAN 控制器 设置为 kCanResetMode*/
  /* ----- Implementation ----------------------------------------------- */
  /* #10 request transition to channel reset mode */
  CanLL_ModeReq_Phys(canPhysChannel, kCanResetMode); /* SBSW_CAN_LL02 */
  /* #20 wait for completion of the transition */
  if (!CanLL_ModeCheck_Phys(canPhysChannel, kCanResetMode)) /* COV_CAN_LL_MODE_CHECK */
  {
    CanLL_ModeWait(CAN_CHANNEL_CANPARA_FIRST canPhysChannel, kCanResetMode, kCanLoopChannelTransition);
  }

#if defined(C_ENABLE_HW_LOOP_TIMER)
  if (CanLL_ModeCheck_Phys(canPhysChannel, kCanResetMode))
#endif
  {
    retVal = kCanOk;
  }
#endif
  return (retVal);
}
/* CODE CATEGORY 4 END */

#if defined(C_ENABLE_SLEEP_WAKEUP)
/****************************************************************************
| NAME:             CanLL_ChannelTransitionSleep()
****************************************************************************/
/*
|<DataModelStart>| CanLL_ChannelTransitionSleep
Relation_Context:
# CanLL_ModeTransition() #
OneChOpt
Wakeup
Relation:
OneChOpt, ChannelAmount
HardwareLoopCheck, Wakeup, WakeupPolling, IntLock, RxBasicCANSupport, RxPolling, RxFullCANSupport, TxPolling, IndividualPolling, StatusPolling, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ChannelTransitionSleep(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
# if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel = mCanLogToPhys(canHwChannel);
# endif
  vuint8 retVal = kCanFailed; /* PRQA S 2981 */ /* MD_Can_RedundantInit */

  retVal = kCanOk;
#if 0
  /* ----- Implementation ----------------------------------------------- */
  /* #10 request transition to channel stop mode (deactivate clock) */
  CanLL_ModeReq_Phys(canPhysChannel, kCanStopMode); /* SBSW_CAN_LL02 */
  /* #20 wait for completion of the transition */
  if (!CanLL_ModeCheck_Phys(canPhysChannel, kCanStopMode)) /* COV_CAN_LL_MODE_CHECK */
  {
    CanLL_ModeWait(CAN_CHANNEL_CANPARA_FIRST canPhysChannel, kCanStopMode, kCanLoopChannelTransition);
  }

# if defined(C_ENABLE_HW_LOOP_TIMER)
  if (CanLL_ModeCheck_Phys(canPhysChannel, kCanStopMode))
# endif
  {
    /* #30 enable the wakeup interrupt if the transition was successful */
#  if defined(C_ENABLE_LL_CAN_WAKEUP_INTCTRL)
    CanLL_ClearCanWakeupInterruptFlag(CAN_HW_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* QAC false positive */
#  endif
#  if !defined(C_ENABLE_WAKEUP_POLLING) && defined(C_ENABLE_LL_CAN_INTCTRL)
    /* enable the wakeup interrupt by driver */
    CanLL_CanWakeupInterruptEnable(CAN_HW_CHANNEL_CANPARA_FIRST &Can_GetCanInterruptOldStatus(canHwChannel)); /* SBSW_CAN_LL15 */
#  endif
#  if defined(C_ENABLE_LL_CAN_INTCB) || defined(C_ENABLE_LL_CAN_WAKEUP_INTCB)
    /* ApplCanWakeupInterruptEnable always has to clear the wakeup interrupt request and then - only in interrupt configurations - enable the interrupt */
    ApplCanWakeupInterruptEnable(canHwChannel);
#  endif
    retVal = kCanOk;
  }

#endif
  return (retVal);
}
/* CODE CATEGORY 4 END */
#endif /* C_ENABLE_SLEEP_WAKEUP */

/****************************************************************************
| NAME:             CanLL_ChannelTransitionStart()
****************************************************************************/
/*
|<DataModelStart>| CanLL_ChannelTransitionStart
Relation_Context:
# CanLL_ModeTransition() #
OneChOpt
ReInitStart
SilentMode
Relation:
RamCheck, ChannelAmount, OneChOpt, HardwareLoopCheck, TxHwFifo, TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ChannelTransitionStart(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel = mCanLogToPhys(canHwChannel);
#endif
#if defined(C_ENABLE_TX_HW_FIFO)
  CanObjectHandle hwObjHandle;
#endif
  vuint8 retVal = kCanFailed; /* PRQA S 2981 */ /* MD_Can_RedundantInit */

  retVal = kCanOk;
#if 0
  /* ----- Implementation ----------------------------------------------- */
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
  if (canIsCellCorrupt == kCanFalse) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
#endif
  {
    /* #10 request transition to channel operation mode */
    CanLL_ModeReq_Phys(canPhysChannel, kCanOperationMode); /* SBSW_CAN_LL02 */
    /* #20 wait for completion of the transition */
    CanLL_ModeWait(CAN_CHANNEL_CANPARA_FIRST canPhysChannel, kCanOperationMode, kCanLoopChannelTransition);

#if defined(C_ENABLE_HW_LOOP_TIMER)
    if (CanLL_ModeCheck_Phys(canPhysChannel, kCanOperationMode))
#endif
    {
#if defined(C_ENABLE_TX_HW_FIFO)
      /* #30 enable transmit FIFO buffers if the transition was successful */
      for (hwObjHandle = kCanZero; hwObjHandle < Can_GetTxFifoCountOfChannelData(channel); hwObjHandle++) /* CM_CAN_LL07 */
      {
        Can->ChFC[canPhysChannel].TRFCR[hwObjHandle] |= kCanCrFifoEnable; /* SBSW_CAN_LL05 */
      }
#endif
      retVal = kCanOk;
    }
  }
#endif


  return (retVal);
}
/* CODE CATEGORY 4 END */

#if defined(C_ENABLE_SILENT_MODE)
/****************************************************************************
| NAME:             CanLL_ChannelTransitionHalt()
****************************************************************************/
/*
|<DataModelStart>| CanLL_ChannelTransitionHalt
Relation_Context:
# CanLL_ModeTransition() #
OneChOpt, SilentMode
Relation:
OneChOpt, ChannelAmount
HardwareLoopCheck, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_ChannelTransitionHalt(CAN_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel = mCanLogToPhys(canHwChannel);
#endif
  vuint8 retVal = kCanFailed; /* PRQA S 2981 */ /* MD_Can_RedundantInit */


  retVal = kCanOk;
#if 0
  /* ----- Implementation ----------------------------------------------- */
  /* #10 request transition to channel halt mode */
  CanLL_ModeReq_Phys(canPhysChannel, kCanHaltMode); /* SBSW_CAN_LL02 */
  /* #20 wait for completion of the transition */
  CanLL_ModeWait(CAN_CHANNEL_CANPARA_FIRST canPhysChannel, kCanHaltMode, kCanLoopChannelTransition);

#if defined(C_ENABLE_HW_LOOP_TIMER)
  if (CanLL_ModeCheck_Phys(canPhysChannel, kCanHaltMode))
#endif
  {
    retVal = kCanOk;
  }
#endif

  return (retVal);
}
/* CODE CATEGORY 4 END */
#endif


#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
/****************************************************************************
| NAME:             CanLL_IsGlobalRegisterCorrupt()
****************************************************************************/
/*
|<DataModelStart>| CanLL_IsGlobalRegisterCorrupt
Relation_Context:
# from CanLL_InitPowerOn #
Relation:
CanFdSupport
CanFdConfiguration
CanCrcConfiguration
LLDerivative
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_IsGlobalRegisterCorrupt(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 canGlobalRegCheckFailed;
  vuint8 idx;
  vuint8 canPhysChannelIndex;
  vuint8 canFifoIndex;
  vuint8 canFilterRulesIndex;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 assume the global register RAM is not corrupt */
  canGlobalRegCheckFailed = kCanFalse;

  /* PRQA S 2985 QAC_CanLL_IsGlobalRegisterCorrupt */ /* MD_Can_ConstValue */
  /* #20 iterate test patterns */
  for (idx=0u; idx<3u; idx++)
  {
    /* #30 verify global registers */
    /* CGCFG/GCFG */
    Can->CGCFG = (CanMemCheckValues32bit[idx] & kCanRamCheckMaskCGCFG); /* SBSW_CAN_LL01 */
    /* CGCR/GCTR - omit (-/TSWR(0)), TSCR/TSRST(0), GSTP/GSLPR(0), GMODE/GMDC(01) */
    Can->CGCR = ((CanMemCheckValues32bit[idx] & kCanRamCheckMaskCGCR) | kCanResetMode); /* SBSW_CAN_LL01 */
# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
#  if defined(C_ENABLE_CAN_FD_CONFIGURATION) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_FD_CONFIGURATION */
    /* -/CFDGFDCFG */
    Can->CGFDCFG = (CanMemCheckValues32bit[idx] & kCanRamCheckMaskCGFDCFG); /* SBSW_CAN_LL01 */
#  endif
#  if defined(C_ENABLE_CAN_CRC_CONFIGURATION) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_CRC_CONFIGURATION */
    /* -/CFDGCRCCFG */
    Can->CGCRCCFG = (CanMemCheckValues32bit[idx] & kCanRamCheckMaskCGCRCCFG); /* SBSW_CAN_LL01 */
#  endif
# endif
    /* CRECR/GAFLECTR */
    Can->CRECR = (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCRECR); /* SBSW_CAN_LL01 */
    /* CRNCFG?/GAFLCFG? */
    Can->CRNCFG[0] = (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCRNCFG0); /* SBSW_CAN_LL02 */
# if (kCanMaxPhysChannels > 4)
    Can->CRNCFG[1] = (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCRNCFG1); /* SBSW_CAN_LL02 */
# endif
    /* CRBNUM/RMNB */
    Can->CRBNUM = (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCRBNUM); /* SBSW_CAN_LL01 */

    if (   ((Can->CGCFG & kCanRamCheckMaskCGCFG) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskCGCFG))
        || ((Can->CGCR & kCanRamCheckMaskCGCR) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskCGCR))
# if defined(C_ENABLE_RSCAN_FD_LAYOUT) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_RSCAN_FD_LAYOUT */
#  if defined(C_ENABLE_CAN_FD_CONFIGURATION) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_FD_CONFIGURATION */
        || ((Can->CGFDCFG & kCanRamCheckMaskCGFDCFG) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskCGFDCFG))
#  endif
#  if defined(C_ENABLE_CAN_CRC_CONFIGURATION) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_CRC_CONFIGURATION */
        || ((Can->CGCRCCFG & kCanRamCheckMaskCGCRCCFG) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskCGCRCCFG))
#  endif
# endif
        || ((Can->CRECR & kCanRamCheckMaskCRECR) != (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCRECR))
        || ((Can->CRNCFG[0] & kCanRamCheckMaskCRNCFG0) != (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCRNCFG0))
# if (kCanMaxPhysChannels > 4)
        || ((Can->CRNCFG[1] & kCanRamCheckMaskCRNCFG1) != (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCRNCFG1))
# endif
        || ((Can->CRBNUM & kCanRamCheckMaskCRBNUM) != (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCRBNUM))
       ) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
    {
      canGlobalRegCheckFailed = kCanTrue;
    }

    /* #40 verify receive FIFO buffer configuration and control registers */
    for (canFifoIndex=0; canFifoIndex<kCanMaxRxFifos; canFifoIndex++) /* CM_CAN_LL05 */
    {
      /* CRFCRm/RFCCx - omit RFE/RFE(0) */
      Can->CRFCR[canFifoIndex] = (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCRFCR); /* SBSW_CAN_LL03 */
      if ((Can->CRFCR[canFifoIndex] & kCanRamCheckMaskCRFCR) != (CanMemCheckValuesRegSize[idx] & kCanRamCheckMaskCRFCR)) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
      {
        canGlobalRegCheckFailed = kCanTrue;
      }
    }

    /* #50 verify transmit/receive FIFO buffer configuration and control registers */
    for (canPhysChannelIndex = 0; canPhysChannelIndex < kCanMaxPhysChannels; canPhysChannelIndex++)
    {
      for (canFifoIndex=0; canFifoIndex<kCanMaxTxFifos; canFifoIndex++) /* CM_CAN_LL07 */
      {
        /* CiTRFCRk/CFCCk - omit TRFE/CFE(0) */
        Can->ChFC[canPhysChannelIndex].TRFCR[canFifoIndex] = (CanMemCheckValues32bit[idx] & kCanRamCheckMaskTRFCR); /* SBSW_CAN_LL05 */
        if ((Can->ChFC[canPhysChannelIndex].TRFCR[canFifoIndex] & kCanRamCheckMaskTRFCR) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskTRFCR)) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
        {
          canGlobalRegCheckFailed = kCanTrue;
        }
      }
    }

    /* #60 verify receive rule related registers */
    Can->CRECR = kCanRuleWrite | kCanZero; /* SBSW_CAN_LL01 */

    for (canFilterRulesIndex=0; canFilterRulesIndex<kCanMaxRuleAccessCell; canFilterRulesIndex++) /* CM_CAN_LL09 */
    {
      /* CREjA,CREjB,CREjC,CREjD/GAFLIDj,GAFLMj,GAFLP0j,(GAFLP1j) */
      mRuleCode(canFilterRulesIndex) = (CanMemCheckValues32bit[idx] & kCanRamCheckMaskRuleCode); /* SBSW_CAN_LL07 */
      mRuleMask(canFilterRulesIndex) = (CanMemCheckValues32bit[idx] & kCanRamCheckMaskRuleMask); /* SBSW_CAN_LL07 */
      mRuleBuf(canFilterRulesIndex) = (CanMemCheckValues32bit[idx] & kCanRamCheckMaskRuleBuf); /* SBSW_CAN_LL07 */
      mRuleFifo(canFilterRulesIndex) = (CanMemCheckValues32bit[idx] & kCanRamCheckMaskRuleFifo); /* SBSW_CAN_LL07 */

      if (   ((mRuleCode(canFilterRulesIndex) & kCanRamCheckMaskRuleCode) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskRuleCode))
          || ((mRuleMask(canFilterRulesIndex) & kCanRamCheckMaskRuleMask) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskRuleMask))
          || ((mRuleBuf(canFilterRulesIndex) & kCanRamCheckMaskRuleBuf) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskRuleBuf))
          || ((mRuleFifo(canFilterRulesIndex) & kCanRamCheckMaskRuleFifo) != (CanMemCheckValues32bit[idx] & kCanRamCheckMaskRuleFifo))
         ) /* COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK */
      {
        canGlobalRegCheckFailed = kCanTrue;
      }
    }
  } /* iterate test patterns */
  /* PRQA L:QAC_CanLL_IsGlobalRegisterCorrupt */

  /* explicitely set CGCR */
  Can->CGCR = kCanResetMode; /* SBSW_CAN_LL01 */

  return (canGlobalRegCheckFailed);
}
/* CODE CATEGORY 4 END */
#endif

#if (CAN_SAFE_BSW == STD_ON)
/****************************************************************************
| NAME:             CanLL_CheckGeneratedData()
****************************************************************************/
/*
|<DataModelStart>| CanLL_CheckGeneratedData
Relation_Context:
# from CanLL_InitPowerOn #
DevErrorDetect
Relation:
CanFdSupport, OneChOpt, ChannelAmount, Variant, TxHwFifo, TxBasicAmount
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC(CAN_LOCAL_INLINE, vuint8, STATIC_CODE) CanLL_CheckGeneratedData(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  CAN_CHANNEL_CANTYPE_LOCAL
  CanChannelHandle physChannelIndex;
  vuint8 retVal = kCanOk;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 check the data field size of CanLL_RxTmpBuf */
# if defined(C_ENABLE_CAN_FD_FULL)
  if ((sizeof(Can_GetRxTmpBuf(0).u.iData) / sizeof(Can_GetRxTmpBuf(0).u.iData[0])) < 16u) /* PRQA S 2742 */ /* MD_Can_SafeCheck_LL */ /* CM_CAN_LL11 */ /* COV_CAN_GENDATA_FAILURE */
# else
  if ((sizeof(Can_GetRxTmpBuf(0).u.iData) / sizeof(Can_GetRxTmpBuf(0).u.iData[0])) < 2u) /* PRQA S 2742 */ /* MD_Can_SafeCheck_LL */ /* CM_CAN_LL11 */ /* COV_CAN_GENDATA_FAILURE */
# endif
  {
    retVal = kCanFailed; /* PRQA S 2880 */ /* MD_Can_SafeCheck_LL */
  }
  else
  {
# if defined(C_MULTIPLE_RECEIVE_CHANNEL)
    /* #20 iterate active controllers */
    for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
    {
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
      if (Can_GetCanIfChannelId(channel) != CAN_NO_CANIFCHANNELID) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
# endif
      {
#if defined(C_ENABLE_TX_HW_FIFO)
        /* #30 check the amount of used transmit FIFO buffers */
        if (Can_GetTxFifoCountOfChannelData(channel) > kCanMaxTxFifos) /* CM_CAN_LL07 */ /* COV_CAN_GENDATA_FAILURE */
        {
          retVal = kCanFailed;
        }
        else
#endif
        {
          /* #40 check the physical channel index */
          physChannelIndex = mCanLogToPhys(channel);
          if (physChannelIndex >= kCanMaxPhysChannels) /* CM_CAN_LL04 */ /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2992, 2996 */ /* MD_Can_SafeCheck_LL */
          {
            retVal = kCanFailed; /* PRQA S 2880 */ /* MD_Can_SafeCheck_LL */
          }
# if defined(C_MULTIPLE_RECEIVE_CHANNEL)
          else
          {
            /* #50 check the mapping of the physical channel to the controller */
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
            if (Can_GetPhysToLogChannel(physChannelIndex) != channel) /* CM_CAN_LL04 */ /* COV_CAN_GENDATA_FAILURE */
            {
              retVal = kCanFailed;
            }
#  else
            switch (physChannelIndex)
            {
#   if defined(kCanPhysToLogChannelIndex_0) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
              case 0:
                if (kCanPhysToLogChannelIndex_0 != channel) /* CM_CAN_LL04 */ /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2992, 2996 */ /* MD_Can_SafeCheck_LL */
                {
                  retVal = kCanFailed; /* PRQA S 2880 */ /* MD_Can_SafeCheck_LL */
                }
                break;
#   endif
#   if defined(kCanPhysToLogChannelIndex_1) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
              case 1:
                if (kCanPhysToLogChannelIndex_1 != channel) /* CM_CAN_LL04 */ /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2992, 2996 */ /* MD_Can_SafeCheck_LL */
                {
                  retVal = kCanFailed; /* PRQA S 2880 */ /* MD_Can_SafeCheck_LL */
                }
                break;
#   endif
#   if defined(kCanPhysToLogChannelIndex_2) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
              case 2:
                if (kCanPhysToLogChannelIndex_2 != channel) /* CM_CAN_LL04 */ /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2992, 2996 */ /* MD_Can_SafeCheck_LL */
                {
                  retVal = kCanFailed; /* PRQA S 2880 */ /* MD_Can_SafeCheck_LL */
                }
                break;
#   endif
#   if defined(kCanPhysToLogChannelIndex_3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
              case 3:
                if (kCanPhysToLogChannelIndex_3 != channel) /* CM_CAN_LL04 */ /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2992, 2996 */ /* MD_Can_SafeCheck_LL */
                {
                  retVal = kCanFailed; /* PRQA S 2880 */ /* MD_Can_SafeCheck_LL */
                }
                break;
#   endif
#   if defined(kCanPhysToLogChannelIndex_4) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
              case 4:
                if (kCanPhysToLogChannelIndex_4 != channel) /* CM_CAN_LL04 */ /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2992, 2996 */ /* MD_Can_SafeCheck_LL */
                {
                  retVal = kCanFailed; /* PRQA S 2880 */ /* MD_Can_SafeCheck_LL */
                }
                break;
#   endif
#   if defined(kCanPhysToLogChannelIndex_5) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
              case 5:
                if (kCanPhysToLogChannelIndex_5 != channel) /* CM_CAN_LL04 */ /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2992, 2996 */ /* MD_Can_SafeCheck_LL */
                {
                  retVal = kCanFailed; /* PRQA S 2880 */ /* MD_Can_SafeCheck_LL */
                }
                break;
#   endif
#   if defined(kCanPhysToLogChannelIndex_6) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
              case 6:
                if (kCanPhysToLogChannelIndex_6 != channel) /* CM_CAN_LL04 */ /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2992, 2996 */ /* MD_Can_SafeCheck_LL */
                {
                  retVal = kCanFailed; /* PRQA S 2880 */ /* MD_Can_SafeCheck_LL */
                }
                break;
#   endif
#   if defined(kCanPhysToLogChannelIndex_7) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_PHYS_CHANNELS */
              case 7:
                if (kCanPhysToLogChannelIndex_7 != channel) /* CM_CAN_LL04 */ /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2992, 2996 */ /* MD_Can_SafeCheck_LL */
                {
                  retVal = kCanFailed; /* PRQA S 2880 */ /* MD_Can_SafeCheck_LL */
                }
                break;
#   endif
              default:/* COV_CAN_GENDATA_FAILURE */
                retVal = kCanFailed;
                break;
            }
#  endif
          }
# endif
        }
      }
    } /* iterate active controllers */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (retVal != kCanOk) /* COV_CAN_GENDATA_FAILURE */ /* PRQA S 2992, 2996 */ /* MD_Can_SafeCheck_LL */
  {
    Can_CallDetReportError(CAN_INIT_ID, CAN_E_GENDATA); /* PRQA S 2880 */ /* MD_Can_SafeCheck_LL */
  }
# endif

  return (retVal);
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* CODE CATEGORY 4 END */
#endif

/* PRQA L:QAC_CanLL_LocalFunctions */

#if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */
/****************************************************************************
| NAME:             CanHL_TxConfirmationPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_TxConfirmationPolling
Relation_Context:
# from CanLL_TxProcessPendings #
TxPolling
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_TxConfirmationPolling( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle mailboxHandle, CanObjectHandle mailboxElement, CanObjectHandle hwObjHandle )
{
  /* #10 Lock CAN controller interrupts. (avoid nested call of confirmation (individual polling) and CancelTx interrupt confirmation out of Can interrupt like TP) */
  Can_DisableControllerInterrupts((uint8)channel);
  /* #20 call CanHL_TxConfirmation() for handling */
  CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, mailboxElement, hwObjHandle);
  Can_EnableControllerInterrupts((uint8)channel);
}
#endif

/****************************************************************************
| NAME:             CanHL_TxConfirmation
****************************************************************************/
/*
|<DataModelStart>| CanHL_TxConfirmation
Relation_Context:
# from CanHL_TxConfirmationPolling #
# from Tx Interrupt #
TxPolling, IndividualPolling
Relation:
TxHwFifo, GenericConfirmation
DevErrorDetect, TxPolling, OneChOpt
TransmitCancellationAPI
GenericConfirmation, IfTxBuffer
HwCancelTx
GenericConfirmation, MirrorMode
GenericConfirmation, IDType
GenericConfirmation, CanFdSupport
HwCancelTx, TransmitCancellationAPI, GenericConfirmation
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 *
 *
 *
 *
 */
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_TxConfirmation( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle mailboxHandle, CanObjectHandle mailboxElement, CanObjectHandle hwObjHandle )
{
  /* \trace SPEC-1574 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanTxConfirmationParaStruct txConfPara;
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
  tCanTxConfInfoStruct txConfInfoStruct;
#endif
  CanHookBegin_CanHL_TxConfirmation();
  errorId = CAN_E_NO_ERROR; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  txConfPara.mailboxHandle = mailboxHandle;
  txConfPara.mailboxElement = mailboxElement; /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
  txConfPara.hwObjHandle = hwObjHandle; /* PRQA S 2983 */ /* MD_MSR_DummyStmt */
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
  txConfPara.txStructConf = &txConfInfoStruct;
#endif
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING */
  /* #10 Check if parameter controller and hwObjHandle is valid (only for Interrupt system, polling do this by caller) */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if ( 
#  if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
       ((txConfPara.mailboxHandle < Can_GetTxFullHandleStart(canHwChannel)) || (txConfPara.mailboxHandle >= Can_GetTxFullHandleStop(canHwChannel))) &&
#  endif
       ((txConfPara.mailboxHandle < Can_GetTxBasicHandleStart(canHwChannel)) || (txConfPara.mailboxHandle >= Can_GetTxBasicHandleStop(canHwChannel))) ) /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    PduIdType tmp_pdu;
#if defined(C_ENABLE_CANCEL_SUPPORT_API)
    uint8_least tmp_state;
#endif
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    Can_ReturnType generic_retval;
#endif
#if defined(C_ENABLE_TX_HW_FIFO)
    uint16 txHwFifo;
#endif
#if (defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON)) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    /* #100 EXCLUSIVE_AREA_3 needed to avoid another can_write while interface send out of queue (first send out of queue avoid inversion) or call GenericConfirmation2 (data consistency) */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_3();
#endif
#if defined(C_ENABLE_TX_HW_FIFO)
    if (Can_GetMailboxType(txConfPara.mailboxHandle) == CAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* #110 in case of Fifo element get the read index */
      SchM_Enter_Can_CAN_EXCLUSIVE_AREA_7();
      txHwFifo = Can_GetMailboxTxHwFifo(txConfPara.mailboxHandle);
#  if (CAN_SAFE_BSW == STD_ON) /* COV_CAN_SAFE_BSW */
      if (txHwFifo >= (uint16)Can_GetSizeOfTxHwFifo()) /* CM_CAN_HL32 */ /* COV_CAN_GENDATA_FAILURE */
      {
        txHwFifo = 0u;
      }
#  endif
      txConfPara.mailboxElement = (CanObjectHandle)Can_GetTxHwFifoReadIndex(txHwFifo);
      /* #115 get next Fifo element read index */
      if (Can_GetTxHwFifoReadIndex(txHwFifo) < ((uint16)Can_GetMailboxSize(txConfPara.mailboxHandle) - (uint16)1u) ) /* CM_CAN_HL25 */
      {
        Can_IncTxHwFifoReadIndex(txHwFifo); /* SBSW_CAN_HL50 */
      }
      else
      {
        Can_SetTxHwFifoReadIndex(txHwFifo, 0u); /* SBSW_CAN_HL50 */
      }
      Can_DecTxHwFifoFillCount(txHwFifo); /* SBSW_CAN_HL50 */
      SchM_Exit_Can_CAN_EXCLUSIVE_AREA_7();
    }
#endif
    txConfPara.activeSendObject = CanHL_GetActiveSendObject(txConfPara.mailboxHandle, txConfPara.mailboxElement); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
    {
      /* #120 Pre Release HW transmit object (LL) */
#if defined(Debug_AUTOSAR)
      CanLL_TxConfBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfPara); /* SBSW_CAN_HL45 */
#endif
      /* #130 Remember PDU for confirmation parameter */
     // tmp_pdu   = Can_GetActiveSendPdu(txConfPara.activeSendObject);
      tmp_pdu   = Can_GetActiveSendPdu(0);
#if defined(C_ENABLE_CANCEL_SUPPORT_API)
      /* #140 Remember SEND STATE which may be modified due to new transmit call in indication */
      tmp_state = (uint8_least)Can_GetActiveSendState(txConfPara.activeSendObject);
#endif
#if defined(C_ENABLE_CANCEL_TX_IN_HW) /* cancel interrupt occur */
      /* #150 If the message was successfully transmitted (without cancellation) (LL): */
      if (CanLL_TxConfIsMsgTransmitted(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfPara) == kCanTrue) /* SBSW_CAN_HL45 */
#endif
      { /* #200 Set send state to free to allow next TX out of confirmation or direct (reload queue) */
        /* #210 Notify the application by call Appl_GenericConfirmation() and CanIf_TxConfirmation() */
        /*      - Appl_GenericConfirmation() if configured and mirror mode is active
                and afterwards depend of return value
                - CanIf_TxConfirmation() if generic confirmation return OK, or no generic is used, and TX is not cancelled */
#if defined(CAN_ENABLE_GENERIC_CONFIRMATION_API1)
        Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
        if (Appl_GenericConfirmation( tmp_pdu ) == CAN_OK)
#elif defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
# if defined(C_ENABLE_MIRROR_MODE)
        if (Can_GetMirrorModeState(channel) == CDDMIRROR_INACTIVE)
        { /* MirrorMode is inactive so call the following CanIf_TxConfirmation() */
          Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
          generic_retval = CAN_OK;
        }
        else
# endif
        { /* #230 For generic confirmation with API2 copy PDU data as parameter for Appl_GenericConfirmation() */
# if defined(C_ENABLE_TX_HW_FIFO)
          if (Can_GetMailboxType(txConfPara.mailboxHandle) == CAN_TX_BASICCAN_FIFO_TYPE) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          { /* #240 in case of FIFO get data out of Fifo storage */
            Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */ /* release after copy data to avoid data inconsistency */
            /* call Appl_GenericConfirmation() and in case of CAN_OK also the following CanIf_TxConfirmation() */
            generic_retval = Appl_GenericConfirmation( (uint8)channel, &Can_GetActiveSendPduInfo(txConfPara.activeSendObject) ); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL25 */
          }
          else
# endif
          {/* #250 in case of none FIFO get data out of CAN cell buffer (LL txStructConf) */
            Can_PduType canPdu;
            CanLL_TxConfSetTxConfStruct(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfPara); /* SBSW_CAN_HL45 */
            canPdu.sdu = (Can_SduPtrType) txConfPara.txStructConf->pChipData; /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */
            canPdu.length = CanTxActualDLC(txConfPara.txStructConf);
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
            if ( CanTxActualIdType(txConfPara.txStructConf) == kCanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
            { /* Mixed ID */
              canPdu.id = (Can_IdType)CanTxActualStdId(txConfPara.txStructConf); /* PRQA S 4391 */ /* MD_Can_IntegerCast */
            }
            else
#  endif  /* pure Extended ID */
            { /* Extended ID */
              canPdu.id = (Can_IdType)(CanTxActualExtId(txConfPara.txStructConf) | CAN_ID_IDE_MASK);
            }
# else    /* Standard ID */
            canPdu.id = CanTxActualStdId(txConfPara.txStructConf);
# endif
# if defined(C_ENABLE_CAN_FD_USED)
            if ( CanTxActualFdType(txConfPara.txStructConf) == kCanFdTypeFd )
            {
              canPdu.id |= (Can_IdType)CAN_ID_FD_MASK;
            }
# endif
            canPdu.id &= CAN_ID_MASK_IN_GENERIC_CALLOUT;
            canPdu.swPduHandle = tmp_pdu;
            Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */ /* release after copy data to avoid data inconsistency */
            /* call Appl_GenericConfirmation() and in case of CAN_OK also the following CanIf_TxConfirmation() */
            generic_retval = Appl_GenericConfirmation( (uint8)channel, &canPdu ); /* PRQA S 0312 */ /* MD_Can_NoneVolatilePointerCast */ /* SBSW_CAN_HL32 */
          }
        }
        /* #300 Appl_GenericConfirmation() decide to call Indication */
        if (generic_retval == CAN_OK)
#else /* no generic confirmation */
        Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
#endif
        {
#if defined(C_ENABLE_CANCEL_SUPPORT_API)
          /* #310 If TX is SW cancelled call CanIf_CancelTxNotification() */
          if (tmp_state == kCanBufferCancelSw) /* COV_CAN_CANCEL_SW_STIMULATION */
          {
            CanIf_CancelTxNotification(tmp_pdu, FALSE);
          }
          else
#endif  /* #320 otherwise call CanIf_TxConfirmation() */
          {
            CanIf_TxConfirmation(tmp_pdu); /* \trace SPEC-1726, SPEC-1571 */
          }
        }
#if (defined(CAN_ENABLE_GENERIC_CONFIRMATION_API1) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)) && (CAN_TRANSMIT_BUFFER == STD_ON)
        /* #350 otherwise no CanIf_TxConfirmation() will be called so call CanIf_CancelTxNotification() just to notify IF to restart sending out of Queue */
        else
        {
# if defined(C_ENABLE_CANCEL_SUPPORT_API)
          CanIf_CancelTxNotification( tmp_pdu, FALSE );
# else
#  error "When using Generic Confirmation and Transmit buffer (If) the Cancel-support-api (if) has to be activated"
# endif
        }
#endif
      }
#if defined(C_ENABLE_CANCEL_TX_IN_HW)
      /* #400 otherwise mailbox is cancelled successful */
      else
      {
#  if defined(C_ENABLE_CANCEL_SUPPORT_API)
        if (tmp_state == kCanBufferCancelSw) /* COV_CAN_CANCEL_SW_STIMULATION */
        { /* #410 free active PDU to allow next TX out of confirmation or direct (reload queue) */
          Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree); /* SBSW_CAN_HL04 */
          /* #420 SW cancellation: just call CanIf_CancelTxNotification() (no interrupt lock used here! - worst case can_write came in between and a unnecessary cancellation appear) */
          CanIf_CancelTxNotification( tmp_pdu, TRUE );
        }
        else
#  endif
        {
#  if defined(C_ENABLE_CANCEL_IN_HW) /* COV_CAN_CANCEL_IN_HW TX */
          /* always CancelSW when only FullCAN TX is cancelled so never called */
#   if (CAN_DEV_ERROR_DETECT == STD_ON)
          /* #440 Check send state is not free now, to secure that ActiveSendPduInfo is already set before used */
          if (Can_GetActiveSendState(txConfPara.activeSendObject) == kCanBufferFree) /* COV_CAN_HARDWARE_FAILURE */
          {
            errorId = CAN_E_PARAM_HANDLE;
          }
          else
#   endif
          { /* #450 EXCLUSIVE_AREA_3 -> no call to upper layer here */
            SchM_Enter_Can_CAN_EXCLUSIVE_AREA_3();
            /* #460 free active PDU to allow next TX out of confirmation or direct (reload queue) */
            Can_SetActiveSendState(txConfPara.activeSendObject, kCanBufferFree);  /* SBSW_CAN_HL04 */          
            /* #470 call CanIf_CancelTxConfirmation() to re trigger queue \trace SPEC-1726, SPEC-1725, SPEC-1684, SPEC-1689 */
            CanIf_CancelTxConfirmation( Can_GetActiveSendSwPduHandle(txConfPara.activeSendObject), &Can_GetActiveSendPduInfo(txConfPara.activeSendObject) ); /* SBSW_CAN_HL25 */
            SchM_Exit_Can_CAN_EXCLUSIVE_AREA_3();
          }
#  endif
        }
      }
#endif
      /* #500 Post release HW transmit object (LL) */
      CanLL_TxConfEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txConfPara); /* SBSW_CAN_HL45 */
    }

#if (defined(CAN_USE_CRITICALSECTION_OVER_CONFIRMATION) && (CAN_TRANSMIT_BUFFER == STD_ON)) || defined(CAN_ENABLE_GENERIC_CONFIRMATION_API2)
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_3();
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
# if !defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING */
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_TXCNF_ID, errorId);
  }
# endif
#endif
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CanHookEnd_CanHL_TxConfirmation();
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
# if defined(C_ENABLE_RX_BASICCAN_POLLING) /* COV_CAN_RX_BASICCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_BasicCanMsgReceivedPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_BasicCanMsgReceivedPolling
Relation_Context:
# from CanLL_RxBasicProcessPendings #
RxBasicCANSupport
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_BasicCanMsgReceivedPolling( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle )
{
  /* #10 Lock CAN controller interrupts. */
  Can_DisableControllerInterrupts((uint8)channel);
  /* #20 call CanHL_BasicCanMsgReceived() for handling */
 /////// CanHL_BasicCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxMailboxHandle, hwObjHandle );
  Can_EnableControllerInterrupts((uint8)channel);
}
#endif

/****************************************************************************
| NAME:             CanHL_BasicCanMsgReceived
****************************************************************************/
/*
|<DataModelStart>| CanHL_BasicCanMsgReceived
Relation_Context:
# from CanHL_BasicCanMsgReceivedPolling #
RxBasicCANSupport
# from Rx Interrupt #
Relation:
DevErrorDetect, RxPolling, OneChOpt
RamCheck
Overrun
IDType
CanFdSupport
DevErrorDetect, RxPolling, IndividualPolling
ChannelAmount
RxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_BasicCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle,Can_PduType pdu )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanRxBasicParaStruct rxBasicPara;
  CanHookBegin_CanHL_BasicCanMsgReceived();
  errorId = CAN_E_NO_ERROR;
  rxBasicPara.mailboxHandle = rxMailboxHandle;
  rxBasicPara.hwObjHandle = hwObjHandle;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON) && !defined(C_ENABLE_RX_BASICCAN_POLLING)
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit (already checked in polling task - do it only for interrupt) */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif 
  {
    /* ----- Implementation ----------------------------------------------- */

	/*
	 *
	 * CanLL_RxBasicMsgReceivedBegin  在这个函数里面主要完成从CAN 底层控制器读取到数据
	 */
    /* #25 receive handling begin CanLL_RxBasicMsgReceivedBegin() \trace SPEC-1682, SPEC-1694 */
    if (CanLL_RxBasicMsgReceivedBegin(CAN_CHANNEL_CANPARA_FIRST &rxBasicPara,pdu) == kCanOk) /* SBSW_CAN_HL26 */ /* COV_CAN_RxBasicMsgReceivedBegin */
//	if (CanLL_RxBasicMsgReceivedBegin(CAN_CHANNEL_CANPARA_FIRST &rxBasicPara,pdu) == kCanFailed)//测试调试错误用
    {
# if defined(C_ENABLE_CAN_RAM_CHECK)
      /* -------------------------- RAM check failed --- */
      if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* COV_CAN_HARDWARE_FAILURE */
# endif
      { /* #30 RAM CHECK pass so continue reception */
# if defined(C_ENABLE_OVERRUN)
#  if !defined(C_HL_ENABLE_OVERRUN_IN_STATUS) /* COV_CAN_OVERRUN_IN_STATUS */
#  endif
# endif
        /* \trace SPEC-1346 */
        {
          /* -------------------------- Get DLC and Data Pointer --- */
          /* #60 get ID, DLC and data from HW \trace SPEC-1691, SPEC-1693 */
        //  rxBasicPara.rxStruct.localDlc = CanRxActualDLC((&(rxBasicPara.rxStruct)));
        	rxBasicPara.rxStruct.localDlc = rxBasicPara.rxStruct.pChipMsgObj->Dlc;  //NXP can
          /* -------------------------- Get ID  &  reject unwanted ID type --- */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
          if ( CanRxActualIdType((&(rxBasicPara.rxStruct))) == kCanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          { /* mixed - standard ID */
            rxBasicPara.rxStruct.localId = (Can_IdType)CanRxActualStdId((&(rxBasicPara.rxStruct)));
          }
          else
#  endif 
          { /* mixed or pure - extended ID */
            rxBasicPara.rxStruct.localId = (Can_IdType)(CanRxActualExtId((&(rxBasicPara.rxStruct))) | CAN_ID_IDE_MASK);
          }
          {
# else 
          { /* pure - standard ID */
            rxBasicPara.rxStruct.localId = CanRxActualStdId((&(rxBasicPara.rxStruct)));
# endif
# if defined(C_ENABLE_CAN_FD_USED)
            if ( CanRxActualFdType((&(rxBasicPara.rxStruct))) == kCanFdTypeFd )
            { /* \trace SPEC-60428 */
              rxBasicPara.rxStruct.localId |= (Can_IdType)CAN_ID_FD_MASK;
            }
            /* DLC is not bigger than expected length (8) for CLASSIC CAN msg (additional to HashTag 145) */
            if ((CanRxActualFdType((&(rxBasicPara.rxStruct))) != kCanFdTypeFd) && (rxBasicPara.rxStruct.localDlc > 8u)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_E_PARAM_DLC;
            }
            else
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if (!defined(C_ENABLE_RX_BASICCAN_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING))
            /* #140 Check HRH is BasicCAN (already checked in polling task - do it only for interrupt) */
            if ( (rxBasicPara.mailboxHandle < Can_GetRxBasicHandleStart(canHwChannel)) ||
                 (rxBasicPara.mailboxHandle >= Can_GetRxBasicHandleStop(canHwChannel)) ) /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* CM_CAN_HL18 */ /* COV_CAN_GENDATA_FAILURE */
            {
              errorId = CAN_E_PARAM_HANDLE;
            } 
            else
#  endif
# endif
            /* #145 DLC is not bigger than expected length from mailbox (MAX over all PDU for this mailbox) */
            if (rxBasicPara.rxStruct.localDlc > CAN_MAX_DATALEN_OBJ(rxBasicPara.mailboxHandle)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_E_PARAM_DLC;
            }
            else
            {
              /* -------------------------- Notification --- */
              /* #150 RX queue and notification handling CanHL_RxMsgReceivedNotification() */
              rxBasicPara.rxStruct.localMailboxHandle = rxBasicPara.mailboxHandle;
              errorId = CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANPARA_FIRST &(rxBasicPara.rxStruct)); /* SBSW_CAN_HL26 */
            }
          }
        }
      }
    }
    /* #160 receive handling end CanHL_RxBasicMsgReceivedEnd() */
    CanLL_RxBasicReleaseObj(CAN_CHANNEL_CANPARA_FIRST &rxBasicPara); /* SBSW_CAN_HL26 */
    CanLL_RxBasicMsgReceivedEnd(CAN_CHANNEL_CANPARA_FIRST &rxBasicPara); /* SBSW_CAN_HL26 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_RXINDI_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanHookEnd_CanHL_BasicCanMsgReceived();
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

#if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
# if defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
/****************************************************************************
| NAME:             CanHL_FullCanMsgReceivedPolling
****************************************************************************/
/*
|<DataModelStart>| CanHL_FullCanMsgReceivedPolling
Relation_Context:
# from CanLL_RxFullProcessPendings #
RxFullCANSupport, RxPolling
Relation:
OneChOpt
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_FullCanMsgReceivedPolling( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle )
{
  /* #10 Lock CAN controller interrupts. */
  Can_DisableControllerInterrupts((uint8)channel);
  /* #20 call CanHL_FullCanMsgReceived() for handling */
  CanHL_FullCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxMailboxHandle, hwObjHandle );
  Can_EnableControllerInterrupts((uint8)channel);
}
# endif

/****************************************************************************
| NAME:             CanHL_FullCanMsgReceived
****************************************************************************/
/*
|<DataModelStart>| CanHL_FullCanMsgReceived
Relation_Context:
# from CanLL_FullCanMsgReceivedPolling #
RxFullCANSupport
# from Rx Interrupt #
Relation:
OneChOpt
DevErrorDetect, RxPolling, OneChOpt
RamCheck
Overrun
IDType
CanFdSupport
DevErrorDetect, RxPolling, IndividualPolling
ChannelAmount
RxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_FullCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxMailboxHandle, CanObjectHandle hwObjHandle ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  tCanRxFullParaStruct rxFullPara;
  CanHookBegin_CanHL_FullCanMsgReceived();
  errorId = CAN_E_NO_ERROR;
  rxFullPara.mailboxHandle = rxMailboxHandle;
  rxFullPara.hwObjHandle = hwObjHandle;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if !defined(C_ENABLE_RX_FULLCAN_POLLING) /* COV_CAN_RX_FULLCAN_POLLING */
#   if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit (already checked in polling task - do it only for interrupt) */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#   endif
#  endif
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #25 receive handling begin CanLL_RxFullMsgReceivedBegin() \trace SPEC-1682, SPEC-1694 */
    if (CanLL_RxFullMsgReceivedBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxFullPara) == kCanOk) /* SBSW_CAN_HL27 */ /* COV_CAN_RxFullMsgReceivedBegin */
    {
  /* -------------------------- RAM check failed --- */
# if defined(C_ENABLE_CAN_RAM_CHECK)
      if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* COV_CAN_HARDWARE_FAILURE */
# endif
      { /* #30 RAM CHECK pass so continue reception */
        /* -------------------------- Overrun --- */
        {
          /* -------------------------- Get DLC and Data Pointer --- */
          /* #60 get ID, DLC and data from HW \trace SPEC-1691, SPEC-1693 */
          rxFullPara.rxStruct.localDlc = CanRxActualDLC((&(rxFullPara.rxStruct)));
          /* -------------------------- Get ID  &  reject unwanted ID type --- */
# if defined(C_ENABLE_EXTENDED_ID)
#  if defined(C_ENABLE_MIXED_ID)
          if ( CanRxActualIdType((&(rxFullPara.rxStruct))) == kCanIdTypeStd) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
          { /* mixed - standard ID */
            rxFullPara.rxStruct.localId = (Can_IdType)CanRxActualStdId((&(rxFullPara.rxStruct)));
          }
          else
#  endif 
          { /* mixed or pure - extended ID */
            rxFullPara.rxStruct.localId = (Can_IdType)(CanRxActualExtId((&(rxFullPara.rxStruct))) | CAN_ID_IDE_MASK);
          }
# else 
          rxFullPara.rxStruct.localId = CanRxActualStdId((&(rxFullPara.rxStruct)));
# endif
          { /* ID has valid IdType */
# if defined(C_ENABLE_CAN_FD_USED)
            if ( CanRxActualFdType((&(rxFullPara.rxStruct))) == kCanFdTypeFd )
            { /* \trace SPEC-60428 */
              rxFullPara.rxStruct.localId |= (Can_IdType)CAN_ID_FD_MASK;
            }
            /* DLC is not bigger than expected length (8) for CLASSIC CAN msg (additional to HashTag 145) */
            if ((CanRxActualFdType((&(rxFullPara.rxStruct))) != kCanFdTypeFd) && (rxFullPara.rxStruct.localDlc > 8u)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_E_PARAM_DLC;
            }
            else
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if (!defined(C_ENABLE_RX_FULLCAN_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING)) /* COV_CAN_RX_FULLCAN_POLLING */
            /* #140 Check HRH is FullCAN (already checked in polling task - do it only for interrupt) */
            if ( (rxFullPara.mailboxHandle < Can_GetRxFullHandleStart(canHwChannel)) ||
                 (rxFullPara.mailboxHandle >= Can_GetRxFullHandleStop(canHwChannel)) )  /* PRQA S 2991,2992,2995,2996 */ /* MD_Can_ConstValue */ /* CM_CAN_HL18 */ /* COV_CAN_GENDATA_FAILURE */
            {
              errorId = CAN_E_PARAM_HANDLE;
            }
            else
#  endif
# endif
            /* #145 DLC is not bigger than expected length from mailbox */
            if (rxFullPara.rxStruct.localDlc > CAN_MAX_DATALEN_OBJ(rxFullPara.mailboxHandle)) /* ESCAN00084263 */ /* COV_CAN_HARDWARE_FAILURE */
            {
              errorId = CAN_E_PARAM_DLC;
            }
            else
            {
              /* -------------------------- Notification --- */
              /* #150 RX queue and notification handling CanHL_RxMsgReceivedNotification() */
              rxFullPara.rxStruct.localMailboxHandle = rxFullPara.mailboxHandle;
              errorId = CanHL_RxMsgReceivedNotification(CAN_CHANNEL_CANPARA_FIRST &(rxFullPara.rxStruct)); /* SBSW_CAN_HL27 */
            }
          }
        }
      }
    }
    /* #160 receive handling end CanHL_RxFullMsgReceivedEnd() */
    CanLL_RxFullReleaseObj(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxFullPara); /* SBSW_CAN_HL27 */
    CanLL_RxFullMsgReceivedEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &rxFullPara); /* SBSW_CAN_HL27 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_RXINDI_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanHookEnd_CanHL_FullCanMsgReceived();
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* C_ENABLE_RX_FULLCAN_OBJECTS */

/****************************************************************************
| NAME:             CanHL_ErrorHandling
****************************************************************************/
/*
|<DataModelStart>| CanHL_ErrorHandling
Relation_Context:
# from Can_Mainfunction_BusOff() #
StatusPolling
# from BusOff Interrupt #
StatusPolling
Relation:
DevErrorDetect, StatusPolling, OneChOpt
BusOffRecovery
Overrun
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* explicite not inline (big code + multiple calls) */
V_DEF_FUNC(CAN_STATIC, void, STATIC_CODE) CanHL_ErrorHandling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined(C_ENABLE_ERROR_POLLING) /* COV_CAN_ERROR_POLLING */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Pre Error handling (LL) */
    CanLL_ErrorHandlingBegin(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
    if ( (CanLL_BusOffOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue) && (!Can_IsIsBusOff(channel) /* avoid repeated call */)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
    {
      /* #90 EXCLUSIVE_AREA_6 secure mode changes */
      SchM_Enter_Can_CAN_EXCLUSIVE_AREA_6();
      /* #100 BUSOFF occur -> ECU Manager restart Controller (no ResetBusOffStart/End needed) */
      Can_SetBusOffCounter(channel, 3); /* SBSW_CAN_HL33 */
      Can_SetIsBusOff(channel, TRUE); /* SBSW_CAN_HL08 */
      /* #110 CanResetBusOffStart need when BUSOFF handled by Application */
      (void)CanHL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST kCanModeResetBusOffStart, kCanContinueBusOffRecovery, kCanSuppressRamCheck);
      /* #115 Controller is in STOP mode after CanResetBusOffStart \trace SPEC-1578, SPEC-1664, SPEC-1663 */
      /* #120 Status changed to STOP - no more call of STOP from CAN Interface */
      Can_SetLogStatus(channel, (uint8)((Can_GetLogStatus(channel) & CAN_STATUS_MASK_NOMODE) | CAN_STATUS_STOP)); /* SBSW_CAN_HL02 */
      SchM_Exit_Can_CAN_EXCLUSIVE_AREA_6();
      /* #130 notify higher layer by call CanIf_ControllerBusOff() \trace SPEC-1726, SPEC-1578 */
      CanIf_ControllerBusOff((uint8)Can_GetCanToCanIfChannelMapping(channel));
    }
#if defined(C_HL_ENABLE_OVERRUN_IN_STATUS) /* COV_CAN_OVERRUN_IN_STATUS */
    /* #135 check for status register (overrun occur) */
# if defined(C_ENABLE_OVERRUN) && defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
    /* #140 notify BasicCAN overrun DET or Appl_CanOverrun() */
    if (CanLL_RxBasicCanOverrun(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue)
    {
#  if (CAN_OVERRUN_NOTIFICATION == CAN_DET)
      errorId = CAN_E_DATALOST; /* \trace SPEC-1686 */
#  else /* CAN_OVERRUN_NOTIFICATION == CAN_APPL */
      Appl_CanOverrun( (uint8)channel );
#  endif
    }
# endif
#endif
    /* #200 Post Error handling (LL) */
    CanLL_ErrorHandlingEnd(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_FAILURE */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CTRBUSOFF_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

# if defined(C_ENABLE_SLEEP_WAKEUP)

/****************************************************************************
| NAME:             CanHL_WakeUpHandling
****************************************************************************/
/*
|<DataModelStart>| CanHL_WakeUpHandling
Relation_Context:
# from CanLL_WakeUpHandling #
Wakeup
Relation:
DevErrorDetect, WakeupPolling, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(CAN_LOCAL_INLINE, void, STATIC_CODE) CanHL_WakeUpHandling( CAN_CHANNEL_CANTYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
#   if !defined(C_ENABLE_WAKEUP_POLLING) /* COV_CAN_WAKEUP_POLLING */
#    if !defined( C_SINGLE_RECEIVE_CHANNEL )
  /* #10 Check if parameter controller is in expected limit, only for interrupt systems where the channel parameter may fail */
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_HARDWARE_FAILURE */
  {
#     if (CAN_DEV_ERROR_REPORT == STD_ON)
    /* ----- Development Error Report --------------------------------------- */
    Can_CallDetReportError(CAN_CTRWAKEUP_ID, CAN_E_PARAM_CONTROLLER);
#     endif
  }
  else
#    endif
#   endif
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 WAKEUP already done in "CanLL_WakeUpHandling" via macro "CanWakeUp" -> (void)Can_SetControllerMode(controller, CAN_T_WAKEUP); */
    /* #30 ESCAN00032401: don't change to STOP mode here this will be done later from inside CANIf after Transceiver is switched to normal mode to avoid blocking while Transceiver produce dominant disturbance */
    Can_SetIsWakeup(channel, TRUE); /* SBSW_CAN_HL09 */
    /* #40 call EcuM_CheckWakeup()  - old API: CanIf_SetWakeupEvent();  \trace SPEC-1725, SPEC-1659, SPEC-1697 */
    EcuM_CheckWakeup(Can_GetWakeupSourceRef(channel));
  }
}
# endif

#define CAN_STOP_SEC_STATIC_CODE  /*---------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*-------------------------------------------------------------------------*/

#define CAN_START_SEC_CODE  /*---------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (CAN_VERSION_INFO_API == STD_ON) /* \trace SPEC-1716 */
/****************************************************************************
| NAME:             Can_GetVersionInfo
****************************************************************************/
/*
|<DataModelStart>| Can_GetVersionInfo
Relation_Context:
VersionInfoApi
Relation:
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_GetVersionInfo( Can_VersionInfoPtrType VersionInfo )
{ /* \trace SPEC-1723 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter versionInfo is an illegal null pointer \trace SPEC-1721 */
  if (VersionInfo == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  { /* #100 copy version info to given pointer parameter \trace SPEC-1717 */
    /* ----- Implementation ----------------------------------------------- */
    VersionInfo->vendorID   = CAN_VENDOR_ID; /* SBSW_CAN_HL10 */
    VersionInfo->moduleID   = CAN_MODULE_ID; /* SBSW_CAN_HL10 */
    VersionInfo->sw_major_version = (uint8)CAN_SW_MAJOR_VERSION; /* SBSW_CAN_HL10 */
    VersionInfo->sw_minor_version = (uint8)CAN_SW_MINOR_VERSION; /* SBSW_CAN_HL10 */
    VersionInfo->sw_patch_version = (uint8)CAN_SW_PATCH_VERSION; /* SBSW_CAN_HL10 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_VERSION_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

/****************************************************************************
| NAME:             Can_InitMemory
****************************************************************************/
/*
|<DataModelStart>| Can_InitMemory
Relation_Context:
Relation:
Variant
DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_InitMemory( void )
{ /* BR:011 */
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  /* #10 mark driver as uninitialized \trace SPEC-1650 */
  canConfigInitFlag = CAN_STATUS_UNINIT;
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER)
  /* #20 reset global configuration pointer */
  Can_ConfigDataPtr = NULL_PTR;
#endif /* otherwise constant pointer is used */
  /* #30 HW reset memory */
  CanLL_InitMemoryPowerOn(); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
#if(CAN_DEV_ERROR_DETECT == STD_OFF)
  CAN_DUMMY_STATEMENT(canConfigInitFlag); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
}


#if ((CAN_CHANGE_BAUDRATE_API == STD_ON) || (CAN_SET_BAUDRATE_API == STD_OFF))
/****************************************************************************
| NAME:             Can_ChangeBaudrate
****************************************************************************/
/*
|<DataModelStart>| Can_ChangeBaudrate
Relation_Context:
Relation:
ChangeBaudrate, DevErrorDetect, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_ChangeBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, APPL_CONST) Baudrate )
{ /* \trace SPEC-20314 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 errorId;
  retval = E_NOT_OK;
  errorId = CAN_E_PARAM_BAUDRATE; /* explicit default as Issue - remove when baud rate fit */ /* \trace SPEC-20321 */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT and STOP \trace SPEC-20338 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels ) /* CM_CAN_HL01 */
  { /* \trace SPEC-20331 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if ( (Can_GetLogStatus(channel) & CAN_STATUS_STOP) != CAN_STATUS_STOP )
  { /* \trace SPEC-1655, SPEC-20312 */
    errorId = CAN_E_TRANSITION;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least baudrateIndex;
    for (baudrateIndex = Can_GetInitObjectStartIndex(channel); baudrateIndex < Can_GetInitObjectStartIndex(channel + 1u); baudrateIndex++)
    { /* #30 search for baud rate configuration */
      if (Can_GetInitObjectBaudrate(baudrateIndex) == Baudrate)
      { /* #40 set baud rate and reinitialize controller to activate baud rate \trace SPEC-1669 */
        uint8 transitionState;
        Can_SetLastInitObject(channel, (uint8)baudrateIndex); /* SBSW_CAN_HL11 */
        transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST kCanModeStopReinit, kCanFinishBusOffRecovery, kCanSuppressRamCheck);
        if (transitionState == kCanOk) /* COV_CAN_TRANSITION_REQUEST */
        { /* #50 check transition STOP (Reinit) is successful */
          Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
        }
        retval = E_OK;
        errorId = CAN_E_NO_ERROR;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CHANGE_BR_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if (CAN_CHANGE_BAUDRATE_API == STD_ON)
/****************************************************************************
| NAME:             Can_CheckBaudrate
****************************************************************************/
/*
|<DataModelStart>| Can_CheckBaudrate
Relation_Context:
ChangeBaudrate
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, APPL_CONST) Baudrate )
{ /* \trace SPEC-20311 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 errorId;
  retval = E_NOT_OK;
  errorId = CAN_E_PARAM_BAUDRATE; /* \trace SPEC-20317 */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT \trace SPEC-20328, SPEC-20318 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels )
  { /* \trace SPEC-20335 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    uint8_least baudrateIndex;
    for (baudrateIndex = Can_GetInitObjectStartIndex(channel); baudrateIndex < Can_GetInitObjectStartIndex(channel + 1u); baudrateIndex++)
    { /* #30 search for baud rate configuration */
      if (Can_GetInitObjectBaudrate(baudrateIndex) == Baudrate)
      { /* #40 requested baud rate is set - return OK */
        retval = E_OK;
        errorId = CAN_E_NO_ERROR;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_CHECK_BR_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
}
#endif /* CAN_CHANGE_BAUDRATE_API == STD_ON */

#if (CAN_SET_BAUDRATE_API == STD_ON)
/****************************************************************************
| NAME:             Can_SetBaudrate
****************************************************************************/
/*
|<DataModelStart>| Can_SetBaudrate
Relation_Context:
Relation:
ChangeBaudrate, DevErrorDetect, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID )
{ /* \trace SPEC-50605 */
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  uint8 errorId;
  /* #5 return E_NOT_OK in case no fitting baudrate is found \trace-2622524 */
  retval = E_NOT_OK;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT and STOP \trace SPEC-50595 */
  if ( canConfigInitFlag == CAN_STATUS_UNINIT )
  {
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if ( channel >= kCanNumberOfChannels ) /* CM_CAN_HL01 */
  { /* \trace SPEC-50587 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if ( (Can_GetLogStatus(channel) & CAN_STATUS_STOP) != CAN_STATUS_STOP )
  { /* \trace SPEC-50584 */
    errorId = CAN_E_TRANSITION;
  }
  else
  if ( BaudRateConfigID >= (uint16)(Can_GetInitObjectStartIndex(channel + 1u) - Can_GetInitObjectStartIndex(channel)) ) /* PRQA S 4391 */ /* MD_Can_IntegerCast */
  { /* \trace SPEC-50625, SPEC-50563 */
    errorId = CAN_E_PARAM_BAUDRATE;
  }
  else
# endif
  { /* #50 set baud rate and reinitialize controller to activate baud rate */
    uint8 transitionState;
    /* ----- Implementation ----------------------------------------------- */
    Can_SetLastInitObject(channel, (uint8)(Can_GetInitObjectStartIndex(channel) + BaudRateConfigID)); /* SBSW_CAN_HL11 */
    transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST kCanModeStopReinit, kCanFinishBusOffRecovery, kCanSuppressRamCheck);
    /* #60 check if hardware cancellation appear while mode change, so for the baud rate set is not successful \trace SPEC-60434 */
    if (transitionState == kCanOk) /* COV_CAN_TRANSITION_REQUEST */
    {
      retval = E_OK;
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_SET_BR_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* CAN_SET_BAUDRATE_API == STD_ON */

/****************************************************************************
| NAME:             Can_Init
****************************************************************************/
/*
|<DataModelStart>| Can_Init
Relation_Context:
Relation:
Variant, DevErrorDetect, PrecompileAndLinktimeCRCCheck
RxQueue
OneChOpt
Variant
Wakeup
MirrorMode
SilentMode
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_Init( Can_ConfigPtrType ConfigPtr ) /* PRQA S 3206 */ /* MD_MSR_DummyStmt */
{ /* \trace SPEC-1587, SPEC-1708 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CAN_CHANNEL_CANTYPE_LOCAL
  CanHookBegin_Can_Init();
  errorId = CAN_E_NO_ERROR;
#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER) /* PostBuild (load+sel) */
  Can_ConfigDataPtr = ConfigPtr; /* \trace SPEC-1394, SPEC-1575 */
# if defined(CAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK) /* PostBuildLoadable */
  if (ConfigPtr == NULL_PTR)
  { /* #10 EcuM null pointer configuration check and notification */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
  }
  else
#  if (CAN_FINALMAGICNUMBER == STD_ON) /* COV_CAN_FINALMAGICNUMBER */
  if (Can_GetFinalMagicNumber() != 20510u) /* COV_CAN_GENDATA_FAILURE */
  { /* #20 EcuM wrong magic number check and notification */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
  else
#  endif
# else
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #30 Check if all parameters are valid \trace SPEC-1724 */
  if (ConfigPtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
#  endif
# endif
#else
  CAN_DUMMY_STATEMENT(ConfigPtr);  /* PRQA S 1338, 2982, 2983, 3112 */ /* MD_MSR_DummyStmt */
# if defined(V_ENABLE_USE_DUMMY_STATEMENT) /* COV_CAN_COMPATIBILITY */
  ConfigPtr = Can_ConfigDataPtr;  /* PRQA S 2983,1338 */ /* MD_MSR_DummyStmt */
# endif
#endif /* CAN_ENABLE_USE_INIT_ROOT_POINTER */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag != CAN_STATUS_UNINIT)
  {
    /* #60 Check already initialized -> 2nd call is not allowed \trace SPEC-1712, SPEC-1722 */
    errorId = CAN_E_TRANSITION;
  }
  else
#endif
  if (  ( Can_GetBaseDll_GeneratorVersion()     != (uint16)CAN_GEN_BASE_CFG5_VERSION ) ||  /* PRQA S 2742 */ /* MD_Can_ConstValue */
        ( Can_GetPlatformDll_GeneratorVersion() != (uint16)CAN_GEN_SH2RSCANASR_VERSION ) ) /* COV_CAN_GENDATA_FAILURE */
  {
    /* #70 EcuM generator and compatibility version check and notification */
#if defined(CAN_ENABLE_USE_ECUM_BSW_ERROR_HOOK) /* not for PostBuildSelectable */
    EcuM_BswErrorHook((uint16) CAN_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#else
    errorId = CAN_E_UNINIT; /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
#endif
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    {
      canIsRxTaskLocked = kCanFalse;
#if defined(C_ENABLE_RX_QUEUE)
      /* #110 delete RxQueue (all channels) */
      Can_GetRxQueueInfo().WriteIndex = 0u;  /* CM_CAN_HL24 */ /* SBSW_CAN_HL55 */
      Can_GetRxQueueInfo().ReadIndex = 0u; /* SBSW_CAN_HL55 */
      Can_GetRxQueueInfo().Count = 0u; /* SBSW_CAN_HL55 */
      canRxQueueMaxDataSize = (uint16) (sizeof(Can_GetRxQueueBuffer(0).data) / sizeof(Can_GetRxQueueBuffer(0).data[0]));
#endif
      /* #120 Set active Identity */
      /* #130 HW specific power on (LL) */
      if (CanLL_InitPowerOn() == kCanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
      {
        canConfigInitFlag = CAN_STATUS_INIT; /* \trace SPEC-1648 */ /* before Controller initialization begin */
#if !defined( C_SINGLE_RECEIVE_CHANNEL )
        for (channel = 0u; channel < kCanNumberOfChannels; channel++) /* CM_CAN_HL01 */
#endif
        { /* #132 for each controller */
#if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
          if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_FAILURE */
          { /* #134 not for inactive controller */
            continue;
          }
#endif
          /* #140 initialize start up values for each controllers */
          Can_SetLogStatus(channel, CAN_STATUS_UNINIT); /* PowerOn mark */ /* SBSW_CAN_HL02 */
          Can_SetModeTransitionRequest(channel, kCanModeNone); /* SBSW_CAN_HL01 */
          Can_SetBusOffTransitionRequest(channel, kCanFinishBusOffRecovery); /* SBSW_CAN_HL01 */
          Can_SetRamCheckTransitionRequest(channel, kCanSuppressRamCheck); /* SBSW_CAN_HL01 */
          Can_SetBusOffCounter(channel, 0u); /* SBSW_CAN_HL33 */
          Can_SetIsBusOff(channel, FALSE);  /* start up: no BUSOFF */ /* SBSW_CAN_HL08 */
#if defined(C_ENABLE_SLEEP_WAKEUP)
          Can_SetIsWakeup(channel, FALSE); /* SBSW_CAN_HL09 */
#endif
          Can_SetCanInterruptCounter(channel, 0u); /* SBSW_CAN_HL12 */
#if defined(C_ENABLE_MIRROR_MODE)
          Can_SetMirrorModeState(channel, CDDMIRROR_INACTIVE); /* SBSW_CAN_HL20 */
#endif
#if defined(C_ENABLE_SILENT_MODE)
          Can_SetSilentModeState(channel, CAN_SILENT_INACTIVE); /* SBSW_CAN_HL20 */
#endif
          /* #155 HW channel specific power on */
          if (CanLL_InitPowerOnChannelSpecific(CAN_CHANNEL_CANPARA_ONLY) == kCanOk) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_HARDWARE_FAILURE */
          {
            uint8 transitionState;
            /* #160 set baud rate and initialize all CAN controllers \trace SPEC-1587, SPEC-1656 */
            Can_SetLastInitObject(channel, (uint8)(Can_GetInitObjectStartIndex(channel) + Can_GetCanControllerDefaultBaudrateIdx(CAN_HL_HW_CHANNEL_STARTINDEX(channel)))); /* SBSW_CAN_HL11 */
            transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST kCanModeStopReinit, kCanFinishBusOffRecovery, kCanExecuteRamCheck);
            if (transitionState == kCanOk) /* COV_CAN_TRANSITION_REQUEST */
            { /* #170 check transition STOP (Reinit) is successful */
              Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* STOP mode reached or issue */ /* SBSW_CAN_HL02 */
            }
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            else
            {              
              errorId = CAN_E_TRANSITION;
            }
#endif
          }
        }
      } /* CanLL_InitPowerOn */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_INIT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_Init();
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_SetControllerMode
****************************************************************************/
/*
|<DataModelStart>| Can_SetControllerMode
Relation_Context:
Relation:
DevErrorDetect, OneChOpt, ChannelAmount
DevErrorDetect, Variant, ChannelAmount
DevErrorDetect, TransitionCheck
RamCheck, ChannelAmount
SilentMode, ChannelAmount
ReInitStart
BusOffRecovery
Wakeup
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition )
{ /* \trace SPEC-1715 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Can_ReturnType retval;
  uint8 transitionRequest;
  uint8 busOffRecovery;
  uint8 doRamCheck;
  uint8 transitionState;
  CanHookBegin_Can_SetControllerMode();
  retval = CAN_NOT_OK;  /* \trace SPEC-1407 */ /* For successful transition it is set explicit to CAN_OK */
  transitionState = kCanFailed;
  errorId = CAN_E_NO_ERROR;
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller and Transition is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1731 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1732 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  { 
    errorId = CAN_E_PARAM_CONTROLLER; /* \trace SPEC3874 */
  }
  else
# endif
#endif
  { /* #50 second level check (modes and transitions) only valid when controller is in active ECU and valid */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (!CanHL_IsControllerInit(channel))
    { /* #60 Check controller is initialized */
      errorId = CAN_E_UNINIT;
    }
    else
    if ((!CanHL_IsStop(channel)) && (Transition == CAN_T_START))
    { /* #70 Check No-STOP -> START-Req is invalid \trace SPEC-1637 */ /* ESCAN00073272 */
      errorId = CAN_E_TRANSITION;
    }
    else
# if (CAN_TRANSITION_CHECK == STD_ON)  /* SREQ00000291 */
    if ( ((!CanHL_IsStop(channel)) && (!CanHL_IsSleep(channel)) && ((Transition == CAN_T_WAKEUP) || (Transition == CAN_T_SLEEP))) ||
         ((CanHL_IsSleep(channel)) && (Transition == CAN_T_STOP)) )
    { /* #80 Check  No STOP Nor SLEEP -> SLEEP-Req   or   No SLEEP Nor STOP --> WAKEUP-Req   is invalid \trace SPEC-1654, SPEC-1649 */
      /* #90 Check  No START Nor STOP -> STOP-Req is invalid \trace SPEC-1652 */
      errorId = CAN_E_TRANSITION;
    }
    else
# endif
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
    /* #95 controller is active (no RAM check issue): */
    if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* PRQA S 2004 */ /* MD_Can_NoElseAfterIf */ /* COV_CAN_RAM_CHECK_NO_STIMULATION */
#endif
    {
      /* ----- Implementation ----------------------------------------------- */
      /* #100 EXCLUSIVE_AREA_6 avoid nesting mode changes (e.g. same API, initialization or BUSOFF) */
      SchM_Enter_Can_CAN_EXCLUSIVE_AREA_6();
      /* #125 HW begin mode transition */
      switch(Transition)
      {
      case CAN_T_START:
        /* #200 Handle --- START --- transition */
        if (Can_IsIsBusOff(channel)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
        { /* #210 BUSOFF occur so finish BUSOFF handling and do START transition inside */
          transitionRequest = kCanModeResetBusOffEnd;
        } 
        else
        {
#if defined(C_ENABLE_SILENT_MODE)
          if (Can_GetSilentModeState(channel) == CAN_SILENT_ACTIVE)
          {
            transitionRequest = kCanModeSilent;
          }
          else
#endif
          {
#if (CAN_REINIT_START == STD_ON)
            transitionRequest = kCanModeStartReinit;
#else
            transitionRequest = kCanModeStart;
#endif
          }
        }
        busOffRecovery = kCanContinueBusOffRecovery;
        doRamCheck = kCanSuppressRamCheck;
        transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
        if ( transitionState == kCanOk ) /* COV_CAN_TRANSITION_REQUEST */
        {
          Can_SetIsBusOff(channel, FALSE); /* SBSW_CAN_HL08 */
        }
        CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_START, CANIF_CS_STARTED, transitionState);
        break;

      case CAN_T_STOP:
        /* #300 Handle --- STOP --- transition */
        transitionRequest = kCanModeStopReinitFast;
        if (Can_GetBusOffCounter(channel) == 0u)  /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
        {
          busOffRecovery = kCanFinishBusOffRecovery;
        }
        else
        {
          Can_DecBusOffCounter(channel); /* SBSW_CAN_HL33 */
          busOffRecovery = kCanContinueBusOffRecovery;
        }
        doRamCheck = kCanSuppressRamCheck;
        transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
        CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_STOP, CANIF_CS_STOPPED, transitionState);
        break;

      case CAN_T_WAKEUP:
        /* #400 Handle --- WAKEUP --- transition */
#if defined(C_ENABLE_SLEEP_WAKEUP)
        if ( (Can_GetModeTransitionRequest(channel) & kCanModeSleep) == kCanModeSleep )
        { /* #410 ASR4: Check WAKEUP not allowed while transition to SLEEP \trace SPEC-1573, SPEC-1402, SPEC-1403, SPEC-1660 */
          errorId = CAN_E_TRANSITION;
          break;
        }
#endif
#if defined(C_ENABLE_CAN_RAM_CHECK) && !defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
        if (!CanHL_IsStop(channel)) { /* do not call RAM_CHECK again in case CanIf call wakeup a second time (buswakeup + stop transition afterwards) */
          /* #415 do standard RAM check CanHL_DoRamCheck() if controller is not in STOP mode */
          transitionRequest = kCanModeStopReinit;
          doRamCheck = kCanExecuteRamCheck;
        }
        else
#endif
        {
          transitionRequest = kCanModeStopReinitFast;
          doRamCheck = kCanSuppressRamCheck;
        }
#if defined(C_ENABLE_SLEEP_WAKEUP)
        if (Can_GetWakeupSourceRef(channel) != 0u) /* COV_CAN_WAKEUP_CHANNEL_NOT_IN_ALL_CONFIG */
        { /* #420 hardware is only in SLEEP if WAKEUP over bus is active and supported and wakeup on this controller is activated -> otherwise emulated SLEEP */
          transitionRequest = kCanModeWakeupStopReinit;
          busOffRecovery = kCanFinishBusOffRecovery;
        }
        else
#endif
        {
          busOffRecovery = kCanFinishBusOffRecovery;
        }
        transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
        CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_STOP, CANIF_CS_STOPPED, transitionState);
        break;

      case CAN_T_SLEEP: /* \trace SPEC-1639 */
        /* #500 Handle --- SLEEP --- transition */
#if defined(C_ENABLE_SLEEP_WAKEUP)
        /* #510 Transition only when WAKEUP by bus is configured, otherwise use emulated SLEEP \trace SPEC-1633 */
        if (Can_GetWakeupSourceRef(channel) != 0u) /* COV_CAN_WAKEUP_CHANNEL_NOT_IN_ALL_CONFIG */
        {
          transitionRequest = kCanModeSleep;
          busOffRecovery = kCanFinishBusOffRecovery;
          doRamCheck = kCanSuppressRamCheck;
          transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
        }
        else
#endif
        { /* #520 no WAKEUP-source-ref: do emulated SLEEP mode \trace SPEC-1629, SPEC-1641, SPEC-1645 */
          transitionState = kCanOk;
        }
        CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_SLEEP, CANIF_CS_SLEEP, transitionState);
        break;

      default:
        /* #600 check unknown transition, return NOT_OK \trace SPEC-1573, SPEC-1402, SPEC-1403 */
        errorId = CAN_E_TRANSITION; /* \trace SPEC-1733, SPEC-1407 */
        break;
      } /* switch */
      SchM_Exit_Can_CAN_EXCLUSIVE_AREA_6();
    }
  }
  if ( transitionState != kCanFailed ) /* COV_CAN_TRANSITION_REQUEST */
  {
    retval = CAN_OK;
  }
  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_SETCTR_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_SetControllerMode();
  return retval;
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_DisableControllerInterrupts
****************************************************************************/
/*
|<DataModelStart>| Can_DisableControllerInterrupts
Relation_Context:
# from Can_Mainfunction_BusOff #
StatusPolling, ChannelAmount
# from CanHL_TxTaskCancelationHandling #
HwCancelTx, IndividualPolling
# from CanHL_TxConfirmationPolling #
TxPolling
# from Rx BasicCan FullCan #
RxPolling
RxBasicCANSupport
RxFullCANSupport
# from Error handling #
StatusPolling
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
IntLock
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(V_NONE, void, CODE) Can_DisableControllerInterrupts( uint8 Controller )
{ /* \trace SPEC-1746 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1750 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1742 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
  if (!CanHL_IsControllerInit(channel))
  { /* #40 Check controller is initialized \trace SPEC-1750 */
    errorId = CAN_E_UNINIT;
  }
  else
#endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #100 EXCLUSIVE_AREA_1 secure interrupt lock handling */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_1();
    if (Can_GetCanInterruptCounter(channel) == 0u)
    { /* #110 Disable only when not disabled before (count nesting) \trace SPEC-1735, SPEC-1745 */
#if (CAN_INTLOCK == CAN_DRIVER) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
      { /* #120 Disable CAN interrupt for each HW channel */
        CanLL_CanInterruptDisable(CAN_CHANNEL_CANPARA_FIRST  &Can_GetCanInterruptOldStatus(canHwChannel)); /* SBSW_CAN_HL16 */
      }
#endif
#if (CAN_INTLOCK == CAN_APPL) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
      /* #130 Let application Disable CAN interrupt ApplCanInterruptDisable() */
      ApplCanInterruptDisable((uint8)channel);
#endif
    }
    Can_SetCanInterruptCounter(channel, Can_GetCanInterruptCounter(channel) + 1u); /* \trace SPEC-1748 */ /* SBSW_CAN_HL12 */
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_1();
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_DIINT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_EnableControllerInterrupts
****************************************************************************/
/*
|<DataModelStart>| Can_EnableControllerInterrupts
Relation_Context:
# from Can_Mainfunction_BusOff #
StatusPolling, ChannelAmount
# from CanHL_TxTaskCancelationHandling #
HwCancelTx, IndividualPolling
# from CanHL_TxConfirmationPolling #
TxPolling
# from Rx BasicCan FullCan #
RxPolling
RxBasicCANSupport
RxFullCANSupport
# from Error handling #
StatusPolling
Relation:
DevErrorDetect, OneChOpt 
DevErrorDetect, Variant
IntLock
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(V_NONE, void, CODE) Can_EnableControllerInterrupts( uint8 Controller )
{ /* \trace SPEC-1741 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1739 */
    errorId = CAN_E_UNINIT;
  }
  else
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* \trace SPEC-1752 */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
# endif
  if (!CanHL_IsControllerInit(channel))
  { /* #40 Check controller is initialized \trace SPEC-1739 */
    errorId = CAN_E_UNINIT;
  }
  else
#endif
  { /* ----- Implementation ----------------------------------------------- */
    /* #100 EXCLUSIVE_AREA_1 secure interrupt lock handling */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_1();
    if (Can_GetCanInterruptCounter(channel) != 0u)
    { /* #110 Enable only when disabled before (count nesting) \trace SPEC-1749, SPEC-1748 */
      Can_SetCanInterruptCounter(channel, Can_GetCanInterruptCounter(channel)-1u); /* SBSW_CAN_HL12 */
      if (Can_GetCanInterruptCounter(channel) == 0u) /* \trace SPEC-1736, SPEC-1756 */
      {
#if (CAN_INTLOCK == CAN_DRIVER) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
        { /* #120 Disable CAN interrupt for each HW channel */
          CanLL_CanInterruptRestore(CAN_CHANNEL_CANPARA_FIRST Can_GetCanInterruptOldStatus(canHwChannel));
        }
#endif
#if (CAN_INTLOCK == CAN_APPL) || (CAN_INTLOCK == CAN_BOTH) /* COV_CAN_LOCK_ISR_BY_APPL */
        /* #130 Let application Enable CAN interrupt ApplCanInterruptRestore() */
        ApplCanInterruptRestore((uint8)channel);
#endif
      }
    }
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_1();
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_ENINT_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_Write
****************************************************************************/
/*
|<DataModelStart>| Can_Write
Relation_Context:
Relation:
DevErrorDetect
OneChOpt
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
DevErrorDetect, TxFullCANSupport
DevErrorDetect, CanFdSupport
DevErrorDetect, MixedId
RamCheck
UseVectorCanIf
CanFdSupport
ChannelAmount
TxBasicAmount
TxFullAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_Write( Can_HwHandleType Hth, Can_PduInfoPtrType PduInfo )
{ /* \trace SPEC-1751, SPEC-1760, SPEC-1406 */
  /* ----- Local Variables ---------------------------------------------- */
  Can_ReturnType retval;
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  CanHookBegin_Can_Write();
  errorId = CAN_E_NO_ERROR;
  retval = CAN_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  uint8 mbId;
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* \trace SPEC-1759 */
    errorId = CAN_E_UNINIT;
  }
  else
  if (Hth >= Can_GetSizeOfMailbox()) {
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
#endif
  {
#if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Hth);
#endif
#if (CAN_DEV_ERROR_DETECT == STD_ON)
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
# endif
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_FAILURE */
    {
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
# endif
    if (!CanHL_IsControllerInit(channel))
    { /* #40 Check controller is initialized \trace SPEC-1407 */
      errorId = CAN_E_UNINIT;
    }
    else
# if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
    if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_FIFO_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# else
    if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_FIFO_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
# endif
    { /* \trace SPEC-1763 */
      errorId = CAN_E_PARAM_HANDLE;
    }
    else
    if ((PduInfo == NULL_PTR) || ((PduInfo->sdu == NULL_PTR) && (PduInfo->length != 0u)))
    { /* \trace SPEC-1761 */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# if !defined(C_ENABLE_CAN_FD_USED)
    if ( CanHL_IsFdMessage(PduInfo->id) )
    { /* no CAN_FD: Check parameter PduInfo->id should not have FD bit in ID */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# endif
# if defined(C_ENABLE_CAN_FD_FULL)
    if ( ((PduInfo->length > 8u) && (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_NONE)) ||
         (PduInfo->length > CAN_MAX_DATALEN_OBJ(Hth)) ) /* COV_CAN_GENDATA_FAILURE */
         { /* \trace SPEC-1758 */
      /* \trace SPEC-60433 */ /* CAN_FD: Check parameter PduInfo->length is smaller than 9 for none FD configuration
         If development error detection for the CAN module is enabled and the CAN Controller is not in CAN FD mode (no CanControllerFdBaudrateConfig):
         The function Can_Write shall raise the error CAN_E_PARAM_DLC and shall return CAN_NOT_OK if the length is more than 8 byte.() */
      /* CAN_FD: Check parameter PduInfo->length against PDU maximum size */
      errorId = CAN_E_PARAM_DLC;
    }
    else
# else
    if ( PduInfo->length > CAN_MAX_DATALEN_OBJ(Hth) ) /* CM_CAN_HL20 */
    { /* \trace SPEC-1758 */ /* Check parameter PduInfo->length against maximum buffer size */
      errorId = CAN_E_PARAM_DLC;
    }
    else
# endif
# if defined(C_ENABLE_MIXED_ID)
    if ( ((PduInfo->id & (Can_IdType)CAN_ID_IDE_MASK) != (Can_IdType)CAN_ID_IDE_MASK ) && ( (PduInfo->id & (Can_IdType)CAN_ID_MASK) > (Can_IdType)CAN_ID_MASK_STD ) ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    { /* Check parameter PduInfo->id for STD ID is in STD range (EXT is always in range) */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
# endif
    if ( (PduInfo->id & (Can_IdType)CAN_ID_UNUSED_MASK) != (Can_IdType)0UL )
    { /* Check parameter PduInfo->id contains illegal bits (e.g. bigger ID value than MAX for given type) */
      errorId = CAN_E_PARAM_POINTER;
    }
    else
#endif
    /* ----- Implementation ----------------------------------------------- */
#if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #150 reject deactivated mailbox (by RamCheck) */
    if (Can_GetMailboxState(Hth) == kCanFailed) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      retval = CAN_NOT_OK;
    }
    else
#endif
    /* #180 check Hardware is in BUSOFF recovery state and is not able to handle a request: return BUSY \trace SPEC-1764 */
    if (Can_IsIsBusOff(channel)) /* COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG */
    {
      retval = CAN_NOT_OK; /* ESCAN00096369 */
    }
    else
#if defined(C_ENABLE_CAN_RAM_CHECK)
    /* #200 controller is active (no RAM check issue): */
    if ((Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) != CAN_DEACTIVATE_CONTROLLER) /* PRQA S 2004 */ /* MD_Can_NoElseAfterIf */ /* COV_CAN_HARDWARE_FAILURE */
#endif
    {
      /* #205 temporary pdu buffer to avoid data modification on constant data (modification in generic pretransmit) */
      tCanTxTransmissionParaStruct txPara;
      /* #210 EXCLUSIVE_AREA_2: Interrupts may not be locked and re-entrant call may occur. */
      /*                        Time in between ID search and lock of mailbox is critical 
                                (only when no Vector Interface used otherwise CanIf EXCLUSIVE_AREA is used instead) 
                                Can_Write() could be called re-entrant, there for also for polling systems the interrupts have to be locked  
                                this is essential while check for mailbox is free (in between if (free) and set to not free) and save PDU handle */
#if !defined(CAN_USE_VECTOR_IF)
      SchM_Enter_Can_CAN_EXCLUSIVE_AREA_2();
#endif
      txPara.mailboxHandle = Hth;
      txPara.hwObjHandle = Can_GetMailboxHwHandle(Hth); 
      txPara.pdu.id = PduInfo->id;
      txPara.pdu.length = PduInfo->length;
      txPara.pdu.sdu = PduInfo->sdu;
      txPara.pdu.swPduHandle = PduInfo->swPduHandle;
#if defined(C_ENABLE_CAN_FD_USED)
      if (txPara.pdu.length <= 8u) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      {
        if (Can_GetInitObjectFdBrsConfig(Can_GetLastInitObject(channel)) == CAN_NONE)
        { /* #220 remove FD flag when no FD support is activated in this initialization structure and DLC not greater than 8 */
          /* CAN FD also support an extended payload which allows the transmission of up to 64 bytes.
          This feature also depends on the CAN FD configuration (see CanControllerFdBaudrateConfig).
          Therefore, if the CAN FD feature is enabled and the CAN FD flag is set in CanId passed to
           Can_Write(), CanDrv supports the transmission of PDUs with a length up to 64 bytes.
          If there is a request to transmit a CAN FD frame without the CAN FD feature enabled the
          frame is sent as conventional CAN frame as long as the PDU length <= 8 bytes. */
          txPara.pdu.id = txPara.pdu.id & ((Can_IdType)(CAN_ID_IDE_MASK | CAN_ID_MASK)); /* CAN_FD_   mask out the FD bit */
        }
      }
      txPara.fdBrsType = kCanFdBrsTypeFalse;
      if (CanHL_IsFdMessage(txPara.pdu.id))
      {
        txPara.fdType = kCanFdTypeFd;
        if (CanHL_IsFdTxBrs(channel))
        {
          txPara.fdBrsType = kCanFdBrsTypeTrue;
        }
      } else {
        txPara.fdType = kCanFdTypeClassic;
      }
      txPara.messageLen = txPara.pdu.length;
      txPara.frameLen = CAN_DLC2LEN(CAN_LEN2DLC(txPara.messageLen));
# if defined(C_ENABLE_CAN_FD_FULL)
      txPara.paddingVal = Can_GetMailboxFdPadding(txPara.mailboxHandle);
# endif
#endif
      /* #230 search for BasicCAN object handle to transmit (Multiplexed TX) and backup data for cancel TX object if necessary */
      CanHL_WritePrepare(CAN_CHANNEL_CANPARA_FIRST &txPara); /* SBSW_CAN_HL49 */
      /* #240 start transmission for given handle (if free) and return state */
      retval = CanHL_WriteStart(CAN_CHANNEL_CANPARA_FIRST &txPara); /* SBSW_CAN_HL49 */
/*
 *
 */


#if !defined(CAN_USE_VECTOR_IF) /* No Vector Interface used, Interrupts may not be locked */
      /* avoid change of PDU information due to TX interrupt while changing */
      SchM_Exit_Can_CAN_EXCLUSIVE_AREA_2();
#endif
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_WRITE_ID, errorId);
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_Write();
  return retval;
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             ASR4.x - Can_CheckWakeup
****************************************************************************/
/*
|<DataModelStart>| Can_CheckWakeup
Relation_Context:
Relation:
Wakeup, DevErrorDetect, OneChOpt
Wakeup, DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
#if defined(C_ENABLE_CHECK_WAKEUP_CAN_RET_TYPE) /* COV_CAN_COMPATIBILITY */
# define CAN_CHECKWAKEUP_RETTYPE Can_ReturnType
# define CAN_CHECKWAKEUP_RETVAL_OK     CAN_OK
# define CAN_CHECKWAKEUP_RETVAL_NOT_OK CAN_NOT_OK
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_CheckWakeup( uint8 Controller )
#else
# define CAN_CHECKWAKEUP_RETTYPE Std_ReturnType
# define CAN_CHECKWAKEUP_RETVAL_OK     E_OK
# define CAN_CHECKWAKEUP_RETVAL_NOT_OK E_NOT_OK
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckWakeup( uint8 Controller )
#endif
{ /* \trace SPEC-1740 */
  /* ----- Local Variables ---------------------------------------------- */
  CAN_CHECKWAKEUP_RETTYPE retval;
  retval = CAN_CHECKWAKEUP_RETVAL_NOT_OK; /* \trace SPEC-1407 */
#if defined(C_ENABLE_SLEEP_WAKEUP)
  {
    uint8 errorId;
    errorId = CAN_E_NO_ERROR;
  
    /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* #10 Check if parameter controller is valid and state is INIT */
    if (canConfigInitFlag == CAN_STATUS_UNINIT)
    { /* #20 Check Driver is initialized */
      errorId = CAN_E_UNINIT;
    }
    else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
    { /* \trace SPEC-1738 */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
    {
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
    if (!CanHL_IsControllerInit(channel))
    { /* #40 Check controller is initialized \trace SPEC-1743 */ /* ESCAN00045884 */
      errorId = CAN_E_UNINIT;
    }
    else
# endif
    {
     /* ----- Implementation ----------------------------------------------- */
     /* #100 if WAKEUP occur: */
     if (Can_IsIsWakeup(channel))
      {
        Can_SetIsWakeup(channel, FALSE); /* SBSW_CAN_HL09 */
        /* #110 Driver call EcuM_SetWakeupEvent() to prevent missing WAKEUP notification (multiple call is OK) */
        EcuM_SetWakeupEvent(Can_GetWakeupSourceRef(channel)); /* \trace SPEC-50550 */
        retval = CAN_CHECKWAKEUP_RETVAL_OK; /* \trace SPEC-1755 */
      }
    }

    /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
    if (errorId != CAN_E_NO_ERROR)
    { /* Throw DET if an error detected before */
      Can_CallDetReportError(CAN_CKWAKEUP_ID, errorId);
    }
#  else
    CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
    CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  }
#else
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  return retval;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_MainFunction_Write
****************************************************************************/
/*
|<DataModelStart>| Can_MainFunction_Write
Relation_Context:
Relation:
TxPolling, HwCancelTx, DevErrorDetect
TxPolling, HwCancelTx, OneChOpt
TxPolling, HwCancelTx, Variant
TxPolling, HwCancelTx, Wakeup
TxPolling, IndividualPolling
TxPolling, TxFullCANSupport, IndividualPolling
TxFullCANSupport, HwCancelTx
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Write( void )
{ /* \trace SPEC-1766 */
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_TX_POLLING) 
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  CanHookBegin_Can_MainFunction_Write();
  /* canSendSemaphor no more needed because of ControllerInterrupts disabled while Can_Write() */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-1767 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {  
    /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #20 over all active controller */
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON) /* \trace SPEC-1573, SPEC-1402, SPEC-1403 */
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
        if ( !CanHL_IsSleep(channel) )
        { /* #60 do not access CAN hardware in SLEEP */
          tCanTaskParaStruct taskPara;
# if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */ /* always true when no hw-cancel is supported */
          /* #100 do confirmation handling for pending mailboxes */
          if ( CanLL_TxIsGlobalConfPending(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue ) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
          { /* #110 is at least one mailbox pending */
            for ( taskPara.mailboxHandle = Can_GetTxBasicHandleStart(canHwChannel); taskPara.mailboxHandle < Can_GetTxBasicHandleStop(canHwChannel); taskPara.mailboxHandle++ ) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
            { /* #120 iterate over all TxBasicCAN */
              taskPara.hwObjHandle = Can_GetMailboxHwHandle(taskPara.mailboxHandle);
#  if defined(C_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
              if ( Can_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif
              { /* #130 is mailbox handled by polling (individual) */
                /* #140 call LL confirmation handling */
                CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
              }
            }
          }
# endif
# if defined(C_ENABLE_CANCEL_TX_IN_HW) 
# endif
# if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
#  if defined(C_ENABLE_TX_POLLING) /* COV_CAN_TX_POLLING TX */ /* always true when no hw-cancel is supported */
          /* #200 do confirmation handling for pending mailboxes */
          if ( CanLL_TxIsGlobalConfPending(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue ) /* PRQA S 2991,2995 */ /* MD_Can_ConstValue */ /* COV_CAN_LL_HARDWARE_BEHAVIOUR */
          { /* #210 is at least one mailbox pending */
            for ( taskPara.mailboxHandle = Can_GetTxFullHandleStart(canHwChannel); taskPara.mailboxHandle < Can_GetTxFullHandleStop(canHwChannel); taskPara.mailboxHandle++ ) /* PRQA S 2994,2996 */ /* MD_Can_ConstValue */
            { /* #220 iterate over all TxFullCAN */
              taskPara.hwObjHandle = Can_GetMailboxHwHandle(taskPara.mailboxHandle);
#   if defined(C_ENABLE_INDIVIDUAL_POLLING) /* COV_CAN_HWOBJINDIVPOLLING */
              if ( Can_IsMailboxIndivPolling(taskPara.mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#   endif
              { /* #230 is mailbox handled by polling (individual) */
                /* #240 call LL confirmation handling */
                CanLL_TxProcessPendings(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &taskPara); /* SBSW_CAN_HL44 */
              }
            }
          }
#  endif
#  if defined(C_ENABLE_CANCEL_TX_IN_HW) 
#  endif
# endif
        } /* !IsSleep */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_WRITE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

#else
  CanHookBegin_Can_MainFunction_Write();
#endif /* C_ENABLE_TX_POLLING */
  CanHookEnd_Can_MainFunction_Write();
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_MainFunction_Read
****************************************************************************/
/*
|<DataModelStart>| Can_MainFunction_Read
Relation_Context:
Relation:
DevErrorDetect
RxPolling, OneChOpt
RxPolling, Variant
RxPolling, DevErrorDetect
RxPolling, Wakeup
RxPolling, RxFullCANSupport
RxPolling, RxBasicCANSupport
RxQueue
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Read( void )
{ /* \trace SPEC-1776 */
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  CanHookBegin_Can_MainFunction_Read();
  errorId = CAN_E_NO_ERROR; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check Driver is initialized \trace SPEC-1784 */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  {
    errorId = CAN_E_UNINIT;
  }
  else
#endif
  /* ----- Implementation ----------------------------------------------- */
  /* #20 semaphore to secure parallel access to RX buffers interrupt or polling \trace SPEC-1569 */
  if ( canIsRxTaskLocked == kCanFalse )  /* PRQA S 2004 */ /* MD_Can_NoElseAfterIf */
  {
#if defined(C_ENABLE_RX_POLLING) /* COV_CAN_RX_POLLING */
    CAN_CHANNEL_CANTYPE_LOCAL
#endif
    canIsRxTaskLocked = kCanTrue; /* PRQA S 2982 */ /* MD_MSR_RetVal */
#if defined(C_ENABLE_RX_POLLING) /* \trace SPEC-1782 */ /* COV_CAN_RX_POLLING */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #30 iterate over all active controller */
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #60 Check controller is initialized */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
        if ( !CanHL_IsSleep(channel) )
        { /* #70 do not access CAN hardware in SLEEP */
          /* #80 over all HW channel \trace SPEC-1774 */
# if defined(C_ENABLE_RX_FULLCAN_OBJECTS)
          /* #90 search for all pending FullCAN mailbox objects and call notification */
          CanHL_RxFullCanPolling(CAN_HW_CHANNEL_CANPARA_ONLY);
# endif
# if defined(C_ENABLE_RX_BASICCAN_OBJECTS) /* COV_CAN_MULTIPLE_BASICCAN */
          /* #100 search for all pending BasicCAN mailbox objects and call notification */
          CanHL_RxBasicCanPolling(CAN_HW_CHANNEL_CANPARA_ONLY);
# endif
        }
      }
    }
#endif /* C_ENABLE_RX_POLLING */
#if defined(C_ENABLE_RX_QUEUE)
    /* #200 execute RxQueue CanHL_RxQueueExecution() */
    CanHL_RxQueueExecution(); 
#endif
    canIsRxTaskLocked = kCanFalse;
  }

  /* ----- Development Error Report --------------------------------------- */
#if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR) /* PRQA S 2992,2996 */ /* MD_Can_ConstValue */
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_READ_ID, errorId); /* PRQA S 2880 */ /*  MD_MSR_Unreachable */
  }
#else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanHookEnd_Can_MainFunction_Read();
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_MainFunction_BusOff
****************************************************************************/
/*
|<DataModelStart>| Can_MainFunction_BusOff
Relation_Context:
Relation:
StatusPolling, DevErrorDetect, ChannelAmount
StatusPolling, OneChOpt
StatusPolling, Variant, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_BusOff( void )
{ /* \trace SPEC-1783 */
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_ERROR_POLLING) /* \trace SPEC-1778 */ /* COV_CAN_ERROR_POLLING */
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-1780 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {  
    /* ----- Implementation ----------------------------------------------- */
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCanNumberOfChannels; channel++)
# endif
    { /* #20 over all active controller */
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
        if ( !CanHL_IsSleep(channel) )
        { /* #60 do not access CAN hardware in SLEEP */
          /* #80 disable CAN interrupts */
          Can_DisableControllerInterrupts((uint8)channel);
          /* #90 call CanHL_ErrorHandling */
          CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY );
          Can_EnableControllerInterrupts((uint8)channel);
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_BO_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
#endif /* C_ENABLE_ERROR_POLLING */
}


/****************************************************************************
| NAME:             Can_MainFunction_Wakeup
****************************************************************************/
/*
|<DataModelStart>| Can_MainFunction_Wakeup
Relation_Context:
Relation:
WakeupPolling, Wakeup, DevErrorDetect
WakeupPolling, Wakeup, OneChOpt
WakeupPolling, Wakeup, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Wakeup( void )
{ /* \trace SPEC-1770 */
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_WAKEUP_POLLING) /* COV_CAN_WAKEUP_POLLING */
# if defined(C_ENABLE_SLEEP_WAKEUP) /* \trace SPEC-1777 */
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-1781 */
    errorId = CAN_E_UNINIT;
  }
  else
#  endif
  {  
    /* ----- Implementation ----------------------------------------------- */
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCanNumberOfChannels; channel++)
#  endif
    { /* #20 over all active controller */
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
#  endif
#  if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */
        errorId = CAN_E_UNINIT;
      }
      else
#  endif
      {
        /* #65 HW WAKEUP occur */
   //     if (CanLL_WakeUpOccured(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_ONLY) == kCanTrue)
        {
          /* #70 EXCLUSIVE_AREA_5 secure WAKEUP handling - refer to ESCAN00021223 - same problem like for CBD */
          SchM_Enter_Can_CAN_EXCLUSIVE_AREA_5();
          /* #80 call CanLL_WakeUpHandling() if any WAKEUP occur for the logical controller \trace SPEC-1773 */
          CanLL_WakeUpHandling(CAN_CHANNEL_CANPARA_ONLY);
          SchM_Exit_Can_CAN_EXCLUSIVE_AREA_5();
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_WU_ID, errorId);
  }
#  else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
# endif
#endif
}

/****************************************************************************
| NAME:             Can_MainFunction_Mode
****************************************************************************/
/*
|<DataModelStart>| Can_MainFunction_Mode
Relation_Context:
Relation:
DevErrorDetect
OneChOpt, ChannelAmount
Variant, ChannelAmount
DevErrorDetect, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Mode( void )
{ /* \trace SPEC-1775 */
  /* ----- Local Variables ---------------------------------------------- */
  CAN_CHANNEL_CANTYPE_LOCAL
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized \trace SPEC-1779 */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  { /* #15 EXCLUSIVE_AREA_6 avoid nesting mode changes (e.g. same API, initialization or BUSOFF) */
    /* ----- Implementation ----------------------------------------------- */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_6();
# if !defined( C_SINGLE_RECEIVE_CHANNEL )
    for (channel = 0u; channel < kCanNumberOfChannels; channel++) /* CM_CAN_HL01 */
# endif
    { /* #20 over all active controller */
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON) /* one controller optimization is always off */
      if ( Can_GetCanIfChannelId(channel) == kCanChannelNotUsed ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
      { /* not for inactive controller */
        continue;
      }
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
      if (!CanHL_IsControllerInit(channel))
      { /* #50 Check controller is initialized */ /* \trace SPEC-1779 */
        errorId = CAN_E_UNINIT;
      }
      else
# endif
      {
        uint8 transitionRequest;
        uint8 busOffRecovery;
        uint8 doRamCheck;
        uint8 transitionState;
        transitionRequest = Can_GetModeTransitionRequest(channel);
        busOffRecovery = Can_GetBusOffTransitionRequest(channel);
        doRamCheck = Can_GetRamCheckTransitionRequest(channel);
        /* #55 only one transition request at one time is possible - execute it \trace SPEC-1771 */
        if(transitionRequest != kCanModeNone)
        {
          transitionState = CanLL_ModeTransition(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST transitionRequest, busOffRecovery, doRamCheck);
          switch(transitionRequest)
          {
# if defined(C_ENABLE_SLEEP_WAKEUP)
            case kCanModeSleep: /* COV_CAN_TRANSITION_REQUEST */
              CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_SLEEP, CANIF_CS_SLEEP, transitionState);
              break;
# endif
            case kCanModeStopReinitFast: /* COV_CAN_TRANSITION_REQUEST */
            case kCanModeStopReinit: /* COV_CAN_TRANSITION_REQUEST */
# if defined(C_ENABLE_SLEEP_WAKEUP)
            case kCanModeWakeupStopReinit: /* COV_CAN_TRANSITION_REQUEST */
# endif
              CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_STOP, CANIF_CS_STOPPED, transitionState);
              break;
            case kCanModeStart: /* COV_CAN_TRANSITION_REQUEST */
            case kCanModeStartReinit: /* COV_CAN_TRANSITION_REQUEST */
            case kCanModeResetBusOffEnd: /* COV_CAN_TRANSITION_REQUEST */
# if defined(C_ENABLE_SILENT_MODE)
            case kCanModeSilent: /* COV_CAN_TRANSITION_REQUEST */
# endif
              CanHL_NotifyTransition(CAN_CHANNEL_CANPARA_FIRST CAN_STATUS_START, CANIF_CS_STARTED, transitionState);
              if ( transitionState == kCanOk ) /* COV_CAN_TRANSITION_REQUEST */
              {
                Can_SetIsBusOff(channel, FALSE); /* SBSW_CAN_HL08 */
              }
              break;
            case kCanModeResetBusOffStart: /* COV_CAN_TRANSITION_REQUEST */ /* not expected, no repetition request */
            default: /* COV_CAN_TRANSITION_REQUEST */
              break;
          }
        }
      }
    } /* over all channels */
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_6();
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_MAINFCT_MODE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */


/****************************************************************************
| NAME:             Can_CancelTx
****************************************************************************/
/*
|<DataModelStart>| Can_CancelTx
Relation_Context:
TransmitCancellationAPI
Relation:
DevErrorDetect, TxFullCANSupport
OneChOpt
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
TxFullCANSupport, HwCancelTx
ChannelAmount
TxFullAmount
TxBasicAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_CancelTx( Can_HwHandleType Hth, PduIdType PduId )
{
  /* ----- Local Variables ---------------------------------------------- */
#if defined(C_ENABLE_CANCEL_SUPPORT_API)
  CAN_CHANNEL_CANTYPE_LOCAL
  tCanTxCancellationParaStruct txCancellationPara;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
  if (Hth >= Can_GetSizeOfMailbox())
  { /* #20 Check Hth is in range */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
#  if defined(C_ENABLE_TX_FULLCAN_OBJECTS)
  if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_FIFO_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
#  else
  if ((Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_MUX_TYPE) && (Can_GetMailboxType(Hth) != CAN_TX_BASICCAN_FIFO_TYPE)) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
#  endif
  { /* #30 Check Hth is FullCAN or BasicCAN */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
  {
# if !defined( C_SINGLE_RECEIVE_CHANNEL ) /* otherwise 'channel' is a define */
    channel = Can_GetMailboxController(Hth);
# endif
# if (CAN_DEV_ERROR_DETECT == STD_ON)
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
    if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */ /* COV_CAN_GENDATA_FAILURE */
    { /* #40 Check parameter controller is in range */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
    if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_FAILURE */
    { /* #60 Check parameter controller is valid */
      errorId = CAN_E_PARAM_CONTROLLER;
    }
    else
#  endif
    if (!CanHL_IsControllerInit(channel))
    { /* #70 Check controller is initialized */
      errorId = CAN_E_UNINIT;
    }
    else
# endif
    {
      /* ----- Implementation ----------------------------------------------- */
      txCancellationPara.mailboxHandle = Hth;
# if defined(C_ENABLE_CANCEL_TX_IN_HW)
      txCancellationPara.hwObjHandle = Can_GetMailboxHwHandle(Hth);
# endif
      txCancellationPara.mailboxElement = 0u;
      txCancellationPara.activeSendObject = CanHL_GetActiveSendObject(txCancellationPara.mailboxHandle, txCancellationPara.mailboxElement);

# if defined (C_ENABLE_TX_FULLCAN_OBJECTS)
      if ( Can_GetMailboxType(Hth) != CAN_TX_FULLCAN_TYPE ) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
# endif
      { /* #100 is BasicCAN */
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_ENABLE_TX_HW_FIFO) /* \trace SPEC-1677 */
        for (; txCancellationPara.mailboxElement < Can_GetMailboxSize(Hth); txCancellationPara.mailboxElement++, txCancellationPara.activeSendObject++) /* PRQA S 3418 */ /* MD_Can_IncompleteForLoop */
# endif
        { /* #110 over all Multiplexed TX objects - search for handle */
          if (Can_GetActiveSendPdu(txCancellationPara.activeSendObject) == PduId)
          {
            if ((Can_GetActiveSendState(txCancellationPara.activeSendObject) == kCanBufferSend)
# if defined(C_ENABLE_CANCEL_TX_IN_HW)
                || (Can_GetActiveSendState(txCancellationPara.activeSendObject) == kCanBufferCancel)
# endif
                )  /* COV_CAN_CANCEL_SW_STIMULATION */
            { /* #120 PDU found in active send list - handle found */
              /* #130 CANCEL_IN_HW is active - just suppress TX confirmation */
# if defined(C_ENABLE_CANCEL_IN_HW)
              { /* #140 LL TX cancel in HW */ /* \trace SPEC-1690 */
                /* #150 mark as to be cancelled by hardware */
                txCancellationPara.canHandleCurTxObj = kCanBufferCancelSw;
                CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txCancellationPara); /* SBSW_CAN_HL47 */
                Can_SetActiveSendState(txCancellationPara.activeSendObject, kCanBufferCancelSw); /* SBSW_CAN_HL04 */
              }
# else
              Can_SetActiveSendState(txCancellationPara.activeSendObject, kCanBufferCancelSw); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
# endif
# if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION) || defined(C_ENABLE_TX_HW_FIFO)
              break;
# endif
            }
          }
        }
      }
# if defined (C_ENABLE_TX_FULLCAN_OBJECTS)
      else
      { /* #200 is FullCAN */
        if (Can_GetActiveSendPdu(txCancellationPara.activeSendObject) == PduId)
        {
          if ((Can_GetActiveSendState(txCancellationPara.activeSendObject) == kCanBufferSend)
#  if defined(C_ENABLE_CANCEL_TX_IN_HW)
              || (Can_GetActiveSendState(txCancellationPara.activeSendObject) == kCanBufferCancel)
#  endif
             )  /* COV_CAN_CANCEL_SW_STIMULATION */
          { /* #210 mailbox to cancel is valid (PDU, handle, send state OK) */
            /* #220 CANCEL_FULLCAN_IN_HW is active - just suppress TX confirmation */
#  if defined(C_ENABLE_CANCEL_TX_IN_HW)
            { /* #230 LL TX cancel in HW */ /* \trace SPEC-1690 */
              /* #150 mark as to be cancelled by hardware */
              txCancellationPara.canHandleCurTxObj = kCanBufferCancelSw;
              CanLL_TxCancelInHw(CAN_CHANNEL_AND_HW_CHANNEL_CANPARA_FIRST &txCancellationPara); /* SBSW_CAN_HL47 */
              Can_SetActiveSendState(txCancellationPara.activeSendObject, kCanBufferCancelSw); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
            }
#  endif
            Can_SetActiveSendState(txCancellationPara.activeSendObject, kCanBufferCancelSw); /* mark as cancelled by SW */ /* SBSW_CAN_HL04 */
          }
        }
      }
# endif
    }
    CAN_CHANNEL_DUMMY_STATEMENT; /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_WRITE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
#else /* CAN_ENABLE_CANCEL_SUPPORT_API */
  CAN_DUMMY_STATEMENT(Hth); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CAN_DUMMY_STATEMENT(PduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* CAN_ENABLE_CANCEL_SUPPORT_API */
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

#if (CAN_GET_STATUS == STD_ON)
/****************************************************************************
| NAME:             Can_GetStatus    //////没有被调用
****************************************************************************/
/*
|<DataModelStart>| Can_GetStatus
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
V_DEF_FUNC(V_NONE, uint8, CODE) Can_GetStatus( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 canReturnCode;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  canReturnCode = CAN_STATUS_INCONSISTENT; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* #50 Check controller is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    CanLL_GetStatusBegin(CAN_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
    /* #100 set logical state as return value */
    canReturnCode = (uint8)Can_GetLogStatus(channel);
    if ( CanLL_HwIsBusOff(channel) ) /* COV_CAN_HARDWARE_FAILURE */
    { /* #150 set BUSOFF - BUSOFF can only happen on first HW channel (with TX objects) */
      canReturnCode |= CAN_STATUS_BUSOFF;
    }
# if defined(C_ENABLE_EXTENDED_STATUS) /* COV_CAN_EXTENDED_STATUS */
    {    
      if ( CanLL_HwIsPassive(channel) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #160 set Error Passive */
        canReturnCode |= CAN_STATUS_PASSIVE;
      }    
      if ( CanLL_HwIsWarning(channel) ) /* COV_CAN_HARDWARE_FAILURE */
      { /* #170 set Error Warning */
        canReturnCode |= CAN_STATUS_WARNING;
      }
    }
# endif /* C_ENABLE_EXTENDED_STATUS */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return (uint8)canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_GetControllerMode
****************************************************************************/
/*
|<DataModelStart>| Can_GetControllerMode
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_GetControllerMode( uint8 Controller, Can_ControllerStatePtrType ControllerModePtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameters are valid */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #20 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (ControllerModePtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 get logical controller mode from state machine variable */
    if (!CanHL_IsControllerInit(channel))
    {
      *ControllerModePtr = CAN_CS_UNINIT; /* SBSW_CAN_HL51 */
    }
    else if (CanHL_IsStart(channel))
    {
      *ControllerModePtr = CAN_CS_STARTED; /* SBSW_CAN_HL51 */
    } 
    else if (CanHL_IsSleep(channel))
    {
      *ControllerModePtr = CAN_CS_SLEEP; /* SBSW_CAN_HL51 */
    }
    else /* default is:   if (CanHL_IsStop(channel)) */
    {
      *ControllerModePtr = CAN_CS_STOPPED; /* SBSW_CAN_HL51 */
    }
    canReturnCode = E_OK;
  }
  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_GETCTR_MODE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_GetControllerErrorState
****************************************************************************/
/*
|<DataModelStart>| Can_GetControllerErrorState
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_GetControllerErrorState( uint8 Controller, Can_ErrorStatePtrType ErrorStatePtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* Check controller is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
  if (ErrorStatePtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    CanLL_GetStatusBegin(CAN_CHANNEL_CANPARA_ONLY); /* PRQA S 2987 */ /* MD_Can_EmptyFunction */
    if ( CanLL_HwIsBusOff(channel) ) /* COV_CAN_HARDWARE_FAILURE */
    { /* #40 set BUSOFF */
      *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF; /* SBSW_CAN_HL52 */
    } 
# if defined(C_ENABLE_EXTENDED_STATUS) /* COV_CAN_EXTENDED_STATUS */
    else if ( CanLL_HwIsPassive(channel) ) /* COV_CAN_HARDWARE_FAILURE */
    { /* #50 set Error Passive */
      *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE; /* SBSW_CAN_HL52 */
    }
# endif /* C_ENABLE_EXTENDED_STATUS */
    else
    { /* #60 default return is ACTIVE */
      *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE; /* SBSW_CAN_HL52 */
    }
    canReturnCode = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_GETCTR_STATE_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_GetControllerTxErrorCounter
****************************************************************************/
/*
|<DataModelStart>| Can_GetControllerTxErrorCounter
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_GetControllerTxErrorCounter( uint8 Controller, Can_ErrorCounterPtrType TxErrorCounterPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* Check controller is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
  if (TxErrorCounterPtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 get error counter from hardware */
# if defined( C_SINGLE_RECEIVE_CHANNEL )
    *TxErrorCounterPtr = CanTxActualErrorCounter(); /* SBSW_CAN_HL53 */
# else
    *TxErrorCounterPtr = CanTxActualErrorCounter(channel); /* SBSW_CAN_HL53 */
# endif
    canReturnCode = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_GETCTR_TXCNT_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/****************************************************************************
| NAME:             Can_GetControllerRxErrorCounter
****************************************************************************/
/*
|<DataModelStart>| Can_GetControllerRxErrorCounter
Relation_Context:
CanGetStatus
Relation:
DevErrorDetect, OneChOpt
DevErrorDetect, Variant
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_GetControllerRxErrorCounter( uint8 Controller, Can_ErrorCounterPtrType RxErrorCounterPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType canReturnCode;
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  canReturnCode = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter controller is valid and state is INIT */
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
#  if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
  if (Can_GetCanIfChannelId(channel) == kCanChannelNotUsed) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
  {
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
  if (!CanHL_IsControllerInit(channel))
  { /* Check controller is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
  if (RxErrorCounterPtr == NULL_PTR)
  {
    errorId = CAN_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #40 get error counter from hardware */
# if defined( C_SINGLE_RECEIVE_CHANNEL )
    *RxErrorCounterPtr = CanRxActualErrorCounter(); /* SBSW_CAN_HL54 */
# else
    *RxErrorCounterPtr = CanRxActualErrorCounter(channel); /* SBSW_CAN_HL54 */
# endif
    canReturnCode = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_GETCTR_RXCNT_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return canReturnCode;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#endif

#if defined(C_ENABLE_MIRROR_MODE)
/****************************************************************************
| NAME:             Can_SetMirrorMode
****************************************************************************/
/*
|<DataModelStart>| Can_SetMirrorMode
Relation_Context:
MirrorMode
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_SetMirrorMode( uint8 Controller, CddMirror_MirrorModeType mirrorMode )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 set mirror mode for given controller */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetMirrorModeState(channel, mirrorMode); /* SBSW_CAN_HL20 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

#if defined(C_ENABLE_SILENT_MODE)
/****************************************************************************
| NAME:             Can_SetSilentMode
****************************************************************************/
/*
|<DataModelStart>| Can_SetSilentMode
Relation_Context:
SilentMode
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_SetSilentMode( uint8 Controller, Can_SilentModeType silentMode )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  Std_ReturnType retval;
  errorId = CAN_E_NO_ERROR;
  retval = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 set silent mode for given controller */
    /* ----- Implementation ----------------------------------------------- */
    Can_SetSilentModeState(channel, silentMode); /* SBSW_CAN_HL20 */
    retval = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  return retval;
}
#endif

#if defined(C_ENABLE_CAN_RAM_CHECK_EXTENDED)
/****************************************************************************
| NAME:             Can_RamCheckExecute
****************************************************************************/
/*
|<DataModelStart>| Can_RamCheckExecute
Relation_Context:
Relation:
RamCheck, DevErrorDetect, OneChOpt, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckExecute( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  { /* #30 Do RamCheck by execute reinitialization with activated check */
    uint8 transitionState;
    /* ----- Implementation ----------------------------------------------- */
    transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST kCanModeStopReinit, kCanFinishBusOffRecovery, kCanExecuteRamCheck);
    if (transitionState == kCanOk) /* COV_CAN_TRANSITION_REQUEST */
    { /* #40 check transition STOP (Reinit) is successful */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}

/****************************************************************************
| NAME:             Can_RamCheckEnableMailbox
****************************************************************************/
/*
|<DataModelStart>| Can_RamCheckEnableMailbox
Relation_Context:
Relation:
RamCheck, DevErrorDetect
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckEnableMailbox( Can_HwHandleType htrh )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
  if (htrh >= Can_GetSizeOfMailbox()) { /* CM_CAN_HL28 */
    errorId = CAN_E_PARAM_HANDLE;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #15 disable controller to force reinitialization afterwards in Can_RamCheckEnableController() */
    Can_SetLogStatus(Can_GetMailboxController(htrh), CAN_DEACTIVATE_CONTROLLER); /* SBSW_CAN_HL40 */
    /* #20 reactivate mailbox */
    Can_SetMailboxState(htrh, kCanOk); /* SBSW_CAN_HL34 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}




/****************************************************************************
| NAME:             Can_RamCheckEnableController
****************************************************************************/
/*
|<DataModelStart>| Can_RamCheckEnableController
Relation_Context:
RamCheck
Relation:
DevErrorDetect, OneChOpt
ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
V_DEF_FUNC(V_NONE, void, CODE) Can_RamCheckEnableController( uint8 Controller )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  errorId = CAN_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CAN_DEV_ERROR_DETECT == STD_ON)
  if (canConfigInitFlag == CAN_STATUS_UNINIT)
  { /* #10 Check Driver is initialized */
    errorId = CAN_E_UNINIT;
  }
  else
#  if !defined( C_SINGLE_RECEIVE_CHANNEL )
  if (channel >= kCanNumberOfChannels) /* CM_CAN_HL01 */
  { /* #20 Check parameter controller is in range */
    errorId = CAN_E_PARAM_CONTROLLER;
  }
  else
#  endif
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 activate controller only when currently disabled */
    if ( (Can_GetLogStatus(channel) & CAN_DEACTIVATE_CONTROLLER) == CAN_DEACTIVATE_CONTROLLER ) /* COV_CAN_RAM_CHECK_NO_STIMULATION */
    {
      uint8 transitionState;
      /* #40 re-initialize to activate mailboxes and controller after RAM check issue */
      Can_SetLogStatus(channel, Can_GetLogStatus(channel) & (uint8)(~(CAN_DEACTIVATE_CONTROLLER))); /* SBSW_CAN_HL02 */
      transitionState = CanHL_ModeTransition(CAN_CHANNEL_CANPARA_FIRST kCanModeStopReinit, kCanFinishBusOffRecovery, kCanSuppressRamCheck);
      if (transitionState == kCanOk) /* COV_CAN_TRANSITION_REQUEST */
      { /* #40 check transition STOP (Reinit) is successful */
        Can_SetLogStatus(channel, Can_GetLogStatus(channel) | CAN_STATUS_STOP); /* STOP mode reached */ /* SBSW_CAN_HL02 */
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (CAN_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CAN_E_NO_ERROR)
  { /* Throw DET if an error detected before */
    Can_CallDetReportError(CAN_HW_ACCESS_ID, errorId);
  }
# else
  CAN_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
# if defined( C_SINGLE_RECEIVE_CHANNEL )
  CAN_DUMMY_STATEMENT(Controller); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif



#if defined (C_ENABLE_ECC_TX_ERROR)
/****************************************************************************
| NAME:             CanEccTxError()
****************************************************************************/
/*
|<DataModelStart>| CanEccTxError
Relation_Context:
EccTxError
Relation:
ChannelAmount
LLDerivative #Implicit in the usage of kCanEfMaskEccError#
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC_API(V_NONE, vuint8, CODE) CanEccTxError(CanChannelHandle Controller)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint8 retVal = kCanFalse;
  vuint32 bitmask;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 determine bitmask */
  if (Controller == kCanChannelNotUsed)
  {
    bitmask = kCanEfMaskEccError;
  }
  else
  {
    bitmask = CanLL_SL32(mCanLogToPhys(Controller) + 16u);
  }

  /* #20 return kCanTrue if relevant bits are set */
  if ((Can->CGEF & bitmask) != kCanZero) /* COV_CAN_HARDWARE_FAILURE XF */
  {
    retVal = kCanTrue;
  }

  return (retVal);
}
/* CODE CATEGORY 4 END */

/****************************************************************************
| NAME:             CanEccTxErrorClear()
****************************************************************************/
/*
|<DataModelStart>| CanEccTxErrorClear
Relation_Context:
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanEccTxErrorClear(CanChannelHandle Controller)
{
  /* ----- Local Variables ---------------------------------------------- */
  vuint32 bitmask;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 determine bitmask */
  if (Controller == kCanChannelNotUsed)
  {
    bitmask = kCanEfMaskEccErrorClear;
  }
  else
  {
    bitmask = ((vuint32) ~CanLL_SL32(mCanLogToPhys(Controller) + 16u));
  }

  /* #20 clear relevant bits in register */
  Can->CGEF = bitmask; /* SBSW_CAN_LL01 */
}
/* CODE CATEGORY 4 END */
#endif

#if defined(C_ENABLE_GLOBAL_INIT_POST_PROCESS)
/****************************************************************************
| NAME:             CanGetFilterRulesStartPage()
****************************************************************************/
/*
|<DataModelStart>| CanGetFilterRulesStartPage
Relation_Context:
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC_API(V_NONE, vuint8, CODE) CanGetFilterRulesStartPage(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 return the start page for adding additional filter rules */
  return (CanAddFilterRulesStartPage);
}
/* CODE CATEGORY 4 END */

/****************************************************************************
| NAME:             CanGetFilterRulesStartIndex()
****************************************************************************/
/*
|<DataModelStart>| CanGetFilterRulesStartIndex
Relation_Context:
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 4 START */
V_DEF_FUNC_API(V_NONE, vuint8, CODE) CanGetFilterRulesStartIndex(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 return the first register index for adding additional filter rules */
  return (CanAddFilterRulesStartIndex);
}
/* CODE CATEGORY 4 END */
#endif

# if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
#  if defined(C_ENABLE_RX_BASICCAN_POLLING ) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
#  else
/****************************************************************************
| NAME:             CanInterruptRxFifo()
****************************************************************************/
/*
|<DataModelStart>| CanInterruptRxFifo
Relation_Context:
RxBasicCANSupport, RxPolling, IndividualPolling
Relation:
HardwareLoopCheck, OneChOpt
OneChOpt, ChannelAmount, Variant, MultipleBasicCanObjects, IndividualPolling
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 1 START */
V_DEF_FUNC(V_NONE, void, CODE) CanInterruptRxFifo(Can_PduType pdu) /* COV_CAN_HWOBJINDIVPOLLING */
{
  /* ----- Local Variables ---------------------------------------------- */
  CAN_HW_CHANNEL_CANTYPE_LOCAL
  CanObjectHandle mailboxHandle;
  CanObjectHandle hwObjHandle;
  vuint8 canCount;

  /* ----- Implementation ----------------------------------------------- */
  CanLL_RtmStart(CanInterruptRxFifo);
  CanLL_EI(); /* PRQA S 1006 */ /* MD_Can_Assembler_LL */

#     if defined(C_MULTIPLE_RECEIVE_CHANNEL)
    /* #10 iterate channels */
//    for (canHwChannel=0; canHwChannel<kCanNumberOfChannels; canHwChannel++)
#     endif
    {
      /* #20 if channel is active in current identity */
#     if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
      if (Can_GetCanIfChannelId(channel) != CAN_NO_CANIFCHANNELID) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#     endif
      {
        /* #30 iterate FIFOs that are used on current channel */
        mailboxHandle = CAN_HL_MB_RX_BASIC_STARTINDEX(canHwChannel);
#     if defined(C_ENABLE_MULTIPLE_BASICCAN)
        for (; mailboxHandle < CAN_HL_MB_RX_BASIC_STOPINDEX(canHwChannel); mailboxHandle++)
#     endif
        {
#     if defined(C_ENABLE_INDIVIDUAL_POLLING)
          /* #40 if the object is configured for interrupt handling */
 //         if (!Can_IsMailboxIndivPolling(mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#     endif
          {
            /* #50 if current FIFO has pending messages */
            hwObjHandle = Can_GetMailboxHwHandle(mailboxHandle);
        //    if ((Can->CRFSR[hwObjHandle] & kCanSrFifoEmpty) == 0u) /* COV_CAN_LL_NOT_IN_ALL_CONFIG TX */
            {
        //      canCount = Can_GetFifoProcCountOfChannelData(canHwChannel);
              /* #60 process pending messages until FIFO is empty or configured limit is reached */
          //    do
          //    {
          //      canCount--;
                /* interrupt flag is cleared within CanHL_BasicCanMsgReceived() */
                CanHL_BasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, hwObjHandle,pdu);

            //	CanHL_BasicCanMsgReceived(1, hwObjHandle,pdu);
         //     } while (((Can->CRFSR[hwObjHandle] & kCanSrFifoEmpty) == 0u) && (canCount > 0u)); /* COV_CAN_LL_MANUAL TF tf tx */
            }
          }
        }
      }
    }

  CanLL_DI(); /* PRQA S 1006 */ /* MD_Can_Assembler_LL */
  CanLL_RtmStop(CanInterruptRxFifo);
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
/* CODE CATEGORY 1 END */
#  endif /* C_ENABLE_RX_BASICCAN_POLLING */
# endif /* C_ENABLE_RX_BASICCAN_OBJECTS */

# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
/****************************************************************************
| NAME:             CanInterruptTx()
****************************************************************************/
/*
|<DataModelStart>| CanInterruptTx
Relation_Context:
TxPolling, IndividualPolling
Relation:
OneChOpt, ChannelAmount
HwCancelTx, IndividualPolling, ChannelAmount
MultiplexedTx
TxHwFifo, TxBasicAmount, ChannelAmount
TxHwFifo, TxBasicAmount, IndividualPolling
IndividualPolling, HwCancelTx, ChannelAmount
IndividualPolling, TxHwFifo, ChannelAmount
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
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
/* CODE CATEGORY 1 START */
V_DEF_FUNC(V_NONE, void, CODE) CanInterruptTx(CAN_HW_CHANNEL_CANTYPE_ONLY) /* COV_CAN_HWOBJINDIVPOLLING */
{
  /* ----- Local Variables ---------------------------------------------- */
  kCanTxSize localReg;
  CanObjectHandle mailboxHandle;
  CanObjectHandle hwObjHandle;
  CanObjectHandle mailboxElement = kCanZero; /* PRQA S 2981 */ /* MD_Can_RedundantInit */
#  if defined(C_ENABLE_TX_HW_FIFO)
  vuint8 canCount;
  vuint8 requestCount;
  vuint8 pendingCount;
#  endif
#  if defined(C_MULTIPLE_PHYS_CHANNEL)
  CanChannelHandle canPhysChannel = mCanLogToPhys(canHwChannel);
#  endif

  /* ----- Implementation ----------------------------------------------- */
  CanLL_RtmStart(CanInterruptTx);
  CanLL_EI(); /* PRQA S 1006 */ /* MD_Can_Assembler_LL */
 // localReg=0;
//  hwObjHandle=0;
    /* #10 get transmit complete flags for transmit buffers configured for interrupt handling */
    /* work with local copy - any flags set during processing will be handled by interrupt immediately afterwards */
//    localReg = CanLL_TxSharedRegToWord(canPhysChannel, Can->CTBTCSR[CanLL_TxWordIndex(canPhysChannel)]) & Can_GetTxIntMaskOfChannelData(canHwChannel);
#   if defined(C_ENABLE_CANCEL_IN_HW)
    /* #20 get transmit abort flags for transmit buffers configured for interrupt handling */
#    if defined(C_ENABLE_INDIVIDUAL_POLLING)
 //   localReg |= CanLL_TxSharedRegToWord(canPhysChannel, Can->CTBASR[CanLL_TxWordIndex(canPhysChannel)]);
#    else
//    localReg |= CanLL_TxSharedRegToWord(canPhysChannel, Can->CTBASR[CanLL_TxWordIndex(canPhysChannel)]) & Can_GetTxIntMaskOfChannelData(canHwChannel);
#    endif
#   endif

    /* #30 if any flag is set in local copy */
//    if (localReg != 0u) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
    {
      /* determine start handle for iteration below */
#  if defined(C_ENABLE_IF_RSCAN_FD_V3) /* COV_CAN_LL_CONSTANT_DEFINITION_DERIVATIVE_IF_RSCAN_FD_V3 */
      if      ((localReg & 0x000000FFu) != 0u) { hwObjHandle = 0u; } /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
      else if ((localReg & 0x0000FF00u) != 0u) { hwObjHandle = 8u; } /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
      else if ((localReg & 0x00FF0000u) != 0u) { hwObjHandle = 16u; } /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
      else                                     { hwObjHandle = 24u; }
#  else
      if      ((localReg & 0x000Fu) != 0u) { hwObjHandle = 0u; } /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
      else if ((localReg & 0x00F0u) != 0u) { hwObjHandle = 4u; } /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
      else if ((localReg & 0x0F00u) != 0u) { hwObjHandle = 8u; } /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
      else                                 { hwObjHandle = 12u; }
#  endif

      /* #40 iterate transmit buffers */
      do
      {
        //if ((localReg & CanLL_SLTS(hwObjHandle)) != 0u) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
        {
          /* #50 call the confirmation handling */
          mailboxHandle = Can_GetTxHwToMbHandle(canHwChannel, hwObjHandle); /* PRQA S 2985 */ /* MD_Can_ConstValue */
#  if defined(C_ENABLE_MULTIPLEXED_TRANSMISSION)
          mailboxElement = hwObjHandle - Can_GetMailboxHwHandle(mailboxHandle);
#  endif
          CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, mailboxElement, hwObjHandle);
         // localReg &= (localReg-1u); /* clear bit */
        }
       // hwObjHandle++;
      }  while (0u); /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
    }

#  if defined(C_ENABLE_TX_HW_FIFO)
  /* #60 iterate transmit FIFO objects */
  for (hwObjHandle = kCanZero; hwObjHandle < Can_GetTxFifoCountOfChannelData(channel); hwObjHandle++) /* CM_CAN_LL07 */
  {
    mailboxHandle = Can_GetTxFifoHwToMbHandle(canHwChannel, hwObjHandle);
#   if defined(C_ENABLE_INDIVIDUAL_POLLING)
    if (!Can_IsMailboxIndivPolling(mailboxHandle)) /* COV_CAN_HWOBJINDIVPOLLING */
#   endif
    {
      if ((Can->ChFS[canPhysChannel].TRFSR[hwObjHandle] & kCanSrTxFifoIntFlag) != 0u) /* COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG */
      {
        /* #70 clear the transmit interrupt flag */
        Can->ChFS[canPhysChannel].TRFSR[hwObjHandle] &= ((kCanRegSize) ~kCanSrTxFifoIntFlag); /* SBSW_CAN_LL05 */ /* PRQA S 4399 */ /* MD_Can_IntegerCast */

        /* #80 call the confirmation handling for each transmitted message or the configured limit is reached */
        canCount = Can_GetFifoProcCountOfChannelData(canHwChannel);
        requestCount = (vuint8)Can_GetTxHwFifoFillCount(Can_GetMailboxTxHwFifo(mailboxHandle));
        pendingCount = (vuint8)((Can->ChFS[canPhysChannel].TRFSR[hwObjHandle] & kCanSrFifoMsgCount) >> 8);
        while (((requestCount - pendingCount) > 0u) && (canCount > 0u)) /* COV_CAN_LL_MANUAL TF tf tx */
        {
          canCount--;
          CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST mailboxHandle, kCanZero, hwObjHandle);
          requestCount = (vuint8)Can_GetTxHwFifoFillCount(Can_GetMailboxTxHwFifo(mailboxHandle));
          pendingCount = (vuint8)((Can->ChFS[canPhysChannel].TRFSR[hwObjHandle] & kCanSrFifoMsgCount) >> 8);
        }
      }
    }
  }
#  endif /* C_ENABLE_TX_HW_FIFO */

  CanLL_DI(); /* PRQA S 1006 */ /* MD_Can_Assembler_LL */
  CanLL_RtmStop(CanInterruptTx);
} /* PRQA S 6030 */ /* MD_MSR_STCYC */
/* CODE CATEGORY 1 END */
# endif /* C_ENABLE_TX_POLLING */


# if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
#  if defined(C_ENABLE_WAKEUP_POLLING)
#  else
/****************************************************************************
| NAME:             CanInterruptWakeup()
****************************************************************************/
/*
|<DataModelStart>| CanInterruptWakeup
Relation_Context:
Wakeup, WakeupPolling
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(V_NONE, void, CODE) CanInterruptWakeup(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Implementation ----------------------------------------------- */
  CanLL_RtmStart(CanInterruptWakeup);
  CanLL_EI(); /* PRQA S 1006 */ /* MD_Can_Assembler_LL */

  /* #10 call wakeup handling */
  CanLL_WakeUpHandling(CAN_HW_CHANNEL_CANPARA_ONLY);

  CanLL_DI(); /* PRQA S 1006 */ /* MD_Can_Assembler_LL */
  CanLL_RtmStop(CanInterruptWakeup);
}
/* CODE CATEGORY 1 END */
#  endif /* C_ENABLE_WAKEUP_POLLING */
# endif

# if defined(C_ENABLE_ERROR_POLLING)
# else
/****************************************************************************
| NAME:             CanInterruptStatus()
****************************************************************************/
/*
|<DataModelStart>| CanInterruptWakeup
Relation_Context:
StatusPolling
Relation:
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(V_NONE, void, CODE) CanInterruptStatus(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  /* ----- Implementation ----------------------------------------------- */
  CanLL_RtmStart(CanInterruptStatus);
  CanLL_EI(); /* PRQA S 1006 */ /* MD_Can_Assembler_LL */

  /* #10 call error handling */
  CanHL_ErrorHandling(CAN_HW_CHANNEL_CANPARA_ONLY);

  CanLL_DI(); /* PRQA S 1006 */ /* MD_Can_Assembler_LL */
  CanLL_RtmStop(CanInterruptStatus);
}
/* CODE CATEGORY 1 END */

#  if (defined(C_ENABLE_RX_BASICCAN_OBJECTS) && defined(C_ENABLE_OVERRUN)) 
/****************************************************************************
| NAME:             CanInterruptGlobalStatus()
****************************************************************************/
/*
|<DataModelStart>| CanInterruptWakeup
Relation_Context:
RxBasicCANSupport, Overrun
Relation:
HardwareLoopCheck, OneChOpt
OneChOpt, ChannelAmount
OneChOpt, Variant
Parameter_PreCompile:
Parameter_Data:
Constrain:
|<DataModelEnd>|
*/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/* CODE CATEGORY 1 START */
V_DEF_FUNC(V_NONE, void, CODE) CanInterruptGlobalStatus(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  CAN_HW_CHANNEL_CANTYPE_LOCAL

  /* ----- Implementation ----------------------------------------------- */
  CanLL_RtmStart(CanInterruptGlobalStatus);
  CanLL_EI(); /* PRQA S 1006 */ /* MD_Can_Assembler_LL */

#   if defined(C_MULTIPLE_RECEIVE_CHANNEL)
    /* #10 iterate channels */
    for (canHwChannel=0; canHwChannel<kCanNumberOfChannels; canHwChannel++)
#   endif
    {
      /* #20 if channel is active in current identity */
#   if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
      if (Can_GetCanIfChannelId(canHwChannel) != CAN_NO_CANIFCHANNELID) /* COV_CAN_GENDATA_NOT_IN_ALL_CONFIG */
#   endif
      {
        /* #30 call error handling */
        CanHL_ErrorHandling(CAN_HW_CHANNEL_CANPARA_ONLY);
      }
    }

  CanLL_DI(); /* PRQA S 1006 */ /* MD_Can_Assembler_LL */
  CanLL_RtmStop(CanInterruptGlobalStatus);
}
/* CODE CATEGORY 1 END */
#  endif /* C_ENABLE_RX_BASICCAN_OBJECTS && C_ENABLE_OVERRUN */
# endif /* C_ENABLE_ERROR_POLLING */

#define CAN_STOP_SEC_CODE  /*----------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/****************************************************************************/

/****************************************************************************/
/*  excluded Requirements                                                   */
/****************************************************************************/
/* part of other component: SPEC-1597 */
/* Currently no use-case / not supported: SPEC-1601, SPEC-1592, SPEC-1582 */

/****************************************************************************/
/*  MISRA deviations                                                        */
/****************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_Can_Goto:
PRQA message 2001
  Reason: 'goto' statements are used to reduce code complexity.
  Risk: Incorrect jump.
  Prevention: Code inspection and runtime tests.

MD_Can_MultipleReturn:
PRQA message 2889
  Reason: Multiple return paths are used to reduce code complexity.
  Risk: Return a function too soon.
  Prevention: Code inspection and runtime tests.

MD_Can_ParameterName:
PRQA message 0784
  Reason: API parameter that is also used as a macro name is accepted for compatibility reasons.
  Risk: The macro can change the declaration unintentionally.
  Prevention: Relevant inconsistencies in function declarations, definitions and calls are detected by the compiler.

MD_Can_ConstValue:
PRQA message 2741, 2742, 2880, 2985, 2986, 2990, 2991, 2992, 2993, 2994, 2995, 2996
  Reason: Value is constant depending on configuration aspects or platform specific implementation. This leads to constant control expressions, unreachable code or redundant operations.
  Risk: Wrong or missing functionality.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_EmptyFunction:
PRQA message 2987
  Reason: Function is empty depending on configuration aspects and platform specific implementation.
  Risk: Function implementation missing.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_NoneConstParameterPointer:
PRQA message 3673
  Reason: Non-const pointer parameter is required by the internal interface or compatibility reasons but depending on the configuration or specific platform implementation the target may not always be modified.
  Risk: Read only data could be modified without intention.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_ModuleDefine:
PRQA message 0602, 0603
  Reason: Usage of reserved identifiers with leading underscores is accepted for compatibility reasons.
  Risk: Name conflicts.
  Prevention: Compile and link of the different variants in the component and integration test.

MD_Can_RedundantInit:
PRQA message 2981
  Reason: Reduce code complexity by using an explicit variable initializer that may be always modified before being used in some configurations.
  Risk: Unintended change of value.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_GlobalScope:
PRQA message 3218
  Reason: The usage of variables depends on configuration aspects and they may be used only once or defined globally to improve overview.
  Risk: None.
  Prevention: None.

MD_Can_ExternalScope:
PRQA message 1514, 3408, 3447, 3451, 3210
  Reason: The variable is used by other modules and can't be declared static.
  Risk: Name conflicts.
  Prevention: Compile and link of the different variants in the component and integration test.

MD_Can_GenData:
PRQA message 1533
  Reason: These constants are defined in a generated file and cannot be moved to the static source file.
  Risk: None.
  Prevention: None.

MD_Can_Union:
PRQA message 0750, 0759
  Reason: Using union type to handle different data accesses.
  Risk: Misinterpreted data.
  Prevention: Code inspection and test of the different variants in the component test.

MD_Can_Assertion:
PRQA message 2842
  Reason: Assertion leads to apparent out of bounds indexing.
  Risk: Undefined behaviour.
  Prevention: Code inspection. Assertion itself detects out of bounds indexing.

MD_Can_PointerVoidCast:
PRQA message 0314, 0316
  Reason: API is defined with pointer to void parameter, so pointer has to be casted to or from void.
  Risk: Wrong data access or undefiend behavior for platforms where the byte alignment is not arbitrary.
  Prevention: Code inspection and test with the target compiler/platform in the component test.

MD_Can_PointerCast:
PRQA message 0310
  Reason: Different pointer type is used to access data.
  Risk: Wrong memory is accessed or alignment is incorrect.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_NoneVolatilePointerCast:
PRQA message 0312
  Reason: Cast to none volatile pointer.
  Risk: Incorrect multiple context access.
  Prevention: Code inspection checks that the value is not multiple accessed.

MD_Can_HwAccess:
PRQA message 0303
  Reason: Hardware access needs cast between a pointer to volatile object and an integral type.
  Risk: Access of unknown memory.
  Prevention: Runtime tests.

MD_Can_MixedSigns:
PRQA message 4393, 4394
  Reason: Casting from signed to unsigned types and vice versa is needed as different types are intentionally used.
  Risk: Value is changed during cast.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_IntegerCast:
PRQA message 4391, 4398, 4399, 4491
  Reason: Explicit cast to a different integer type.
  Risk: Value is changed during cast.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_CompilerAbstraction:
PRQA message 0342
  Reason: Glue operator used for compiler abstraction.
  Risk: Only K&R compiler support glue operator.
  Prevention: Compile test show whether compiler accept glue operator.

MD_Can_NoElseAfterIf:
PRQA message 2004
  Reason: No default handling needed for if-else-if here.
  Risk: Missing default handling.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_IncompleteForLoop:
PRQA message 3418
  Reason: Comma operator in for-loop header is used to get a compact code.
  Risk: Uninitialized variable.
  Prevention: Code inspection and test of different variants in the component test.



MD_Can_Pragma_LL:
PRQA message 3116
  Reason: Compiler specific pragmas are used for interrupt service function implementations.
  Risk: Portability problems when using another compiler.
  Prevention: Code inspection and usage of target compilers in the component test.

MD_Can_Assembler_LL:
PRQA message 1006
  Reason: Compiler specific in-line assembler has to be used for interrupt control or CPU pipeline synchronisation.
  Risk: Portability problems when using another compiler.
  Prevention: Code inspection and usage of target compilers in the component test.

MD_Can_RuntimeOptimization_LL:
PRQA message 3415
  Reason: Runtime optimization by explicitly assigning a function call to the right hand of the && or || operator.
  Risk: Side effects of function may always be expected.
  Prevention: Code inspection and test of different variants in the component test.

MD_Can_DummyRead_LL:
PRQA message 2981, 2982
  Reason: Explicit read accesses to hardware registers are necessary that always modify the same dummy variable which is never used.
  Risk: None.
  Prevention: None.

MD_Can_Concatenation_LL:
PRQA message 0342
  Reason: Concatenation is used to create symbolic name for runtime measurement points.
  Risk: Only K&R compilers support concatenation.
  Prevention: Usage of target compilers in the component and integration test.

MD_Can_TestCode_LL:
PRQA message 2981, 2982
  Reason: Test code to stimulate corrupt register RAM always modifies a previously set variable in some configurations, this is not active in productive code.
  Risk: None.
  Prevention: None.

MD_Can_SafeCheck_LL:
PRQA message 2742, 2880, 2991, 2992, 2995, 2996
  Reason: Generic verification of generated data leads to constant control expressions and unreachable code in some configurations.
  Risk:  None.
  Prevention: None.

*/

/****************************************************************************/
/*  Silent deviations                                                       */
/****************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_CAN_HL01
 \DESCRIPTION Write access to CanModeTransitionRequest with controller as index. Controller index is checked against sizeof CanModeTransitionRequest in Can_SetControllerMode(), Can_RamCheckExecute(), Can_MainFunction_Mode(), Can_Init() and Can_InitController().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL02
 \DESCRIPTION Write access to CanLogStatus with controller as index. Controller index is checked against sizeof CanLogStatus in Can_SetControllerMode(), CanHL_ErrorHandling(), Can_RamCheckEnableController(), Can_MainFunction_Mode(), Can_Init() and Can_InitController().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL04
 \DESCRIPTION Write access to CanActiveSendState with activeSendObject as index. activeSendObject is checked against size of ActiveSendObject in Can_CleanUpSendState(), CanHL_WritePrepare(), CanHL_InitTxFullCAN(), CanHL_InitTxBasicCAN(), CanHL_TxTaskCancelationHandling(), CanHL_TxConfirmation() and Can_CancelTx().
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL05
 \DESCRIPTION Write access to CanActiveSendPdu with activeSendObject as index. activeSendObject is checked against size of ActiveSendObject.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL06
 \DESCRIPTION Call Can_GenericPrecopy() and CanIf_RxIndication() with parameter RX Queue data pointer. The data pointer is only used for read access and it is always a valid pointer (module local defined).
 \COUNTERMEASURE \R [CM_CAN_HL25]

\ID SBSW_CAN_HL07
 \DESCRIPTION Call Can_GenericPrecopy() and CanIf_RxIndication() with parameter Rx Struct data pointer. The data pointer is only used for read access. Parameter is of type P2CONST in API.
 \COUNTERMEASURE \N [CM_CAN_HL31]

\ID SBSW_CAN_HL08
 \DESCRIPTION Write access to CanIsBusOff with controller as index. Controller index is checked against sizeof CanIsBusOff in Can_SetControllerMode(), CanHL_ErrorHandling() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL09
 \DESCRIPTION Write access to CanIsWakeup with controller as index. Controller index is checked against sizeof CanIsWakeup in CanHL_WakeUpHandling(), Can_CheckWakeup(), reinitialization and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL10
 \DESCRIPTION Write access to VersionInfo pointer within function Can_GetVersionInfo()
 \COUNTERMEASURE \N caller of Can_GetVersionInfo() has to ensure that VersionInfo pointer is valid. (global description available)

\ID SBSW_CAN_HL11
 \DESCRIPTION Write access to CanLastInitObject with controller as index. Controller index is checked against sizeof CanLastInitObject in Can_InitStruct(), Can_ChangeBaudrate(), Can_SetBaudrate() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL12
 \DESCRIPTION Write access to CanInterruptCounter with controller as index. Controller index is checked against sizeof CanInterruptCounter in Can_Init(), Can_EnableControllerInterrupts() and Can_DisableControllerInterrupts()
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL16
 \DESCRIPTION Call CanLL_CanInterruptDisable() with parameter CanInterruptOldStatus as pointer (compiler secures used type in function declaration fitting to given pointer parameter type).
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL18
 \DESCRIPTION Write access to CanRxQueueBuffer with queue write index. Write index is checked against size of CanRxQueueBuffer.
 \COUNTERMEASURE \R [CM_CAN_HL24]

\ID SBSW_CAN_HL19
 \DESCRIPTION Write access to CanRxQueueBuffer.data with queue write index and data index. Write index is checked against size of CanRxQueueBuffer. (see also generator CM_CAN_HL04 qualified use case CSL02)
 \COUNTERMEASURE \R [CM_CAN_HL24]
                 \R [CM_CAN_HL17]

\ID SBSW_CAN_HL20
 \DESCRIPTION Write access to CanMirrorModeState with controller as index. Controller is checked against size of CanMirrorModeState.
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL22
 \DESCRIPTION Write access to ActiveSendData with activeSendData + length as index. Index is checked against size of table.
 \COUNTERMEASURE \R [CM_CAN_HL20]

\ID SBSW_CAN_HL23
 \DESCRIPTION Write access to ActiveSendObject stuct with activeSendObject as index. activeSendObject is checked against size of CanActiveSendObject.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL24
 \DESCRIPTION Call Appl_GenericPreTransmit() with parameter PduInfoPtr_var pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL25
 \DESCRIPTION Call CanIf_CancelTxConfirmation() with parameter CanActiveSendObject.PduInfo[activeSendObject] as pointer with activeSendObject as index. activeSendObject is checked against size of CanActiveSendObject.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL26
 \DESCRIPTION Call CanHL_RxBasicMsgReceivedBegin(), CanHL_RxMsgReceivedNotification() and CanHL_RxBasicMsgReceivedEnd() with parameter rxBasicPara pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL27
 \DESCRIPTION Call CanHL_RxFullMsgReceivedBegin(), CanHL_RxFullReceivedNotification() and CanHL_RxFullMsgReceivedEnd() with parameter rxFullPara pointer (module local defined).
 \COUNTERMEASURE \N The pointer is static and always valid.

\ID SBSW_CAN_HL29
 \DESCRIPTION Write access to rxBasicPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL30
 \DESCRIPTION Write access to rxFullPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL31
 \DESCRIPTION Call Initialization subroutines with initPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL32
 \DESCRIPTION Call Appl_GenericConfirmation with canPdu pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL33
 \DESCRIPTION Write access to CanBusOffCounter with controller as index. Controller index is checked against sizeof CanBusOffCounter in Can_SetControllerMode(), CanHL_ErrorHandling() and Can_Init().
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_HL34
 \DESCRIPTION Write access to CanMailboxState with mailbox handle as index. Index secured by ComStackLib [CM_CAN_HL29] and [CM_CAN_HL30] and checked against size of CanMailboxState.
 \COUNTERMEASURE \R [CM_CAN_HL28]

\ID SBSW_CAN_HL35
 \DESCRIPTION Call with pointer to CAN cell register for write and read access.
 \COUNTERMEASURE \N Caller ensures validity of pointer parameter.

\ID SBSW_CAN_HL36
 \DESCRIPTION Write access to initPara structure as pointer (local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL37
 \DESCRIPTION Call GetElapsedValue with timer value pointers as parameter (module local defined).
 \COUNTERMEASURE \N The timer values are static and always valid.

\ID SBSW_CAN_HL38
 \DESCRIPTION Call GetCounterValue with timer value (LoopTimeout) pointers as parameter. Controller index is checked against size of ControllerData, kCanLoopXXX as index in LoopTimeout table is always smaller than the dimension of the table given as static user type in ComStackLib and checked against this value.
 \COUNTERMEASURE \R [CM_CAN_HL01]
                 \R [CM_CAN_HL22]

\ID SBSW_CAN_HL39
 \DESCRIPTION Undefine preprocessor switch to stimulate user defined feature (only test purpose).
 \COUNTERMEASURE \N Redefinement activates a none documented feature.

\ID SBSW_CAN_HL40
 \DESCRIPTION Write access to CanLogStatus with controller as index. Controller is secured by qualified use-case CSL03 of ComStackLib.
 \COUNTERMEASURE \N [CM_CAN_HL02]

\ID SBSW_CAN_HL41
 \DESCRIPTION Write access to CanActiveSendState with activeSendObject as index. activeSendObject is temporary stored in a list of [1,3] elements where each element is initialized to a valid value and always written with size check before.
 \COUNTERMEASURE \R [CM_CAN_HL03]

\ID SBSW_CAN_HL42
 \DESCRIPTION Write access to txPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL43
 \DESCRIPTION Write access to taskPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL44
 \DESCRIPTION Call task subroutines with taskPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL45
 \DESCRIPTION Call confirmation subroutines with txConfPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL46
 \DESCRIPTION Write access to txConfPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL47
 \DESCRIPTION Call cancellation subroutines with txCancellationPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL48
 \DESCRIPTION Write access to txCancellationPara (module local defined).
 \COUNTERMEASURE \N The structure is static and always valid.

\ID SBSW_CAN_HL49
 \DESCRIPTION Call transmit subroutines with txPara pointer as parameter (local defined).
 \COUNTERMEASURE \N The structure is static and always valid (pointer to a local stack variable)

\ID SBSW_CAN_HL50
 \DESCRIPTION Write access to TxHwFifo member FillCount, WriteIndex and ReadIndex with Mailbox member TxHwFifo as Index. Index is checked against size of TxHwFifo array.
 \COUNTERMEASURE \R [CM_CAN_HL32]

\ID SBSW_CAN_HL51
 \DESCRIPTION Write access to ControllerModePtr pointer within function Can_GetControllerMode()
 \COUNTERMEASURE \N caller of Can_GetControllerMode() has to ensure that ControllerModePtr pointer is valid. (global description available)

\ID SBSW_CAN_HL52
 \DESCRIPTION Write access to ErrorStatePtr pointer within function Can_GetControllerErrorState()
 \COUNTERMEASURE \N caller of Can_GetControllerErrorState() has to ensure that ErrorStatePtr pointer is valid. (global description available)

\ID SBSW_CAN_HL53
 \DESCRIPTION Write access to TxErrorCounterPtr pointer within function Can_GetControllerTxErrorCounter()
 \COUNTERMEASURE \N caller of Can_GetControllerTxErrorCounter() has to ensure that TxErrorCounterPtr pointer is valid. (global description available)

\ID SBSW_CAN_HL54
 \DESCRIPTION Write access to RxErrorCounterPtr pointer within function Can_GetControllerRxErrorCounter()
 \COUNTERMEASURE \N caller of Can_GetControllerRxErrorCounter() has to ensure that RxErrorCounterPtr pointer is valid. (global description available)

\ID SBSW_CAN_HL55
 \DESCRIPTION A ComStackLib generated variable is accessed.
 \COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables address without pointer arithmetic.

\ID SBSW_CAN_LL01
 \DESCRIPTION Write access or call to CanLL_WriteRegGlobal*() for a global CAN cell register. The register structure is static and verified by review.
 \COUNTERMEASURE \S [CM_CAN_LL01]
                 \S [CM_CAN_LL02]

\ID SBSW_CAN_LL02
 \DESCRIPTION Write access or call to CanLL_WriteReg*() for a channel or a shared channel related CAN cell register. The register structure is static and verified by review. The channel or shared register index is verified by a runtime check or by review if static.
 \COUNTERMEASURE \S [CM_CAN_LL01]
                 \S [CM_CAN_LL02]
                 \S [CM_CAN_LL03]
                 \R [CM_CAN_HL01]
                 \R [CM_CAN_LL04]

\ID SBSW_CAN_LL03
 \DESCRIPTION Write access or call to CanLL_WriteRegGlobal*() for a receive FIFO buffer related CAN cell register. The register structure is static and verified by review. The receive FIFO buffer index is verified by a runtime check.
 \COUNTERMEASURE \S [CM_CAN_LL01]
                 \S [CM_CAN_LL02]
                 \R [CM_CAN_LL05]

\ID SBSW_CAN_LL04
 \DESCRIPTION Write access to a transmit buffer related CAN cell register. The register structure is static and verified by review. The channel and buffer indices are verified by a runtime check.
 \COUNTERMEASURE \S [CM_CAN_LL01]
                 \S [CM_CAN_LL02]
                 \S [CM_CAN_LL03]
                 \R [CM_CAN_HL01]
                 \R [CM_CAN_LL04]
                 \R [CM_CAN_LL06]

\ID SBSW_CAN_LL05
 \DESCRIPTION Write access or call to CanLL_WriteRegGlobal*() for a transmit FIFO buffer related CAN cell register. The register structure is static and verified by review. The channel and FIFO buffer indices are verified by a runtime check.
 \COUNTERMEASURE \S [CM_CAN_LL01]
                 \S [CM_CAN_LL02]
                 \S [CM_CAN_LL03]
                 \R [CM_CAN_HL01]
                 \R [CM_CAN_LL04]
                 \R [CM_CAN_LL07]

\ID SBSW_CAN_LL06
 \DESCRIPTION Write access to a shared receive buffer related CAN cell register. The register structure is static and verified by review. The register index is verified by a runtime check or by review if static.
 \COUNTERMEASURE \S [CM_CAN_LL01]
                 \S [CM_CAN_LL02]
                 \R [CM_CAN_LL08]

\ID SBSW_CAN_LL07
 \DESCRIPTION Write access or call to CanLL_WriteRegGlobal*() for a receive rule related CAN cell register. The register structure is static and verified by review. The rule index is verified by a runtime check.
 \COUNTERMEASURE \S [CM_CAN_LL01]
                 \S [CM_CAN_LL02]
                 \R [CM_CAN_LL09]

\ID SBSW_CAN_LL08
 \DESCRIPTION Write access to mailbox related CAN cell register. The register structure is static and verified by review. The pointer is verified by a runtime check. The register structure is static and verified by review. The data index is verified by a runtime check or by review if static. The pointer of the HighLevel-LowLevel-interface (if applicable) has a static type and always references a local variable of the caller.
 \COUNTERMEASURE \S [CM_CAN_LL01]
                 \S [CM_CAN_LL02]
                 \S [CM_CAN_LL03]
                 \R [CM_CAN_HL01]
                 \R [CM_CAN_LL04]
                 \R [CM_CAN_LL05]
                 \R [CM_CAN_LL06]
                 \R [CM_CAN_LL07]
                 \R [CM_CAN_LL10]

\ID SBSW_CAN_LL09
 \DESCRIPTION Write access to local variable CanLL_TxTmpBuf. The data index is verified by a runtime check or by review if static.
 \COUNTERMEASURE \R [CM_CAN_LL10]

\ID SBSW_CAN_LL10
 \DESCRIPTION Write access to variable CanLL_RxTmpBuf. The controller index is checked against the size of ControllerData, the data index is verified by a runtime check (against max value determined by saturated access to local const) or by review if static.
 \COUNTERMEASURE \R [CM_CAN_HL01]
                 \R [CM_CAN_LL10]
                 \R [CM_CAN_LL11]

\ID SBSW_CAN_LL11
 \DESCRIPTION Write access via pointer parameter of an internal interface.
 \COUNTERMEASURE \N The pointer has a static type and always references a local variable of the caller.

\ID SBSW_CAN_LL12
 \DESCRIPTION Call GetCounterValue() with pointer to timer value. The controller index is checked against the size of ControllerData or static zero, the loop index is always smaller than the dimension of the table given as static user type in ComStackLib.
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_LL13
 \DESCRIPTION Write access via pointer to interrupt controller register.
 \COUNTERMEASURE \N In case of SafeBSW 'OS interrupt control' has to be enabled and this code is never active. This is ensured by a MSSV check and compiler error directive.

\ID SBSW_CAN_LL14
 \DESCRIPTION Write access via pointer to CanInterruptOldStatus (compiler secures used type in function declaration fitting to given pointer parameter type).
 \COUNTERMEASURE \N This local function is only called with valid pointers.

\ID SBSW_CAN_LL15
 \DESCRIPTION Call function with pointer to CanInterruptOldStatus (compiler secures used type in function declaration fitting to given pointer parameter type). The controller index is checked against the size of ControllerData.
 \COUNTERMEASURE \R [CM_CAN_HL01]

\ID SBSW_CAN_LL16
 \DESCRIPTION Call a function with pointer to a local variable.
 \COUNTERMEASURE \N The pointer has a static type and always references a local variable.

\ID SBSW_CAN_LL17
 \DESCRIPTION Write access via pointer to CAN cell register.
 \COUNTERMEASURE \N This local function is only called with valid pointers.

\ID SBSW_CAN_LL18
 \DESCRIPTION Assembler instruction is inserted.
 \COUNTERMEASURE \N Always valid because there is no memory access.

SBSW_JUSTIFICATION_END */

/* Counter measurement description

\CM_CAN_HL01 A runtime check ensures controller index is always smaller than number of elements in arrays with controller amount as dimension (Qualified use-case CSL01 of ComStackLib size of ControllerData).
\CM_CAN_HL02 Qualified use-case CSL03 of ComStackLib (CanMailbox.ControllerConfigIdx is always in range of controller ControllerData)
\CM_CAN_HL03 A runtime check ensures activeSendObject index is in valid range for Can_ActiveSendObject table (Qualified use-case CSL01 of ComStackLib - Can_ActiveSendObject size is extended by CAN_MULTIPLEXED_TX_MAX within generator to allow an access to logObjHandle+CAN_MULTIPLEXED_TX_MAX).
\CM_CAN_HL17 A runtime check ensures DLC index is always smaller than the dimension of CanRxQueueBuffer.data.
\CM_CAN_HL18 A runtime check ensures HRH values is always in range of start stop index of the given mailbox type. (Qualified use-case CSL03 of ComStackLib - start-stop index fit to mailbox entrys)
\CM_CAN_HL20 A runtime check ensures size of ActiveSendData (dataByte). For CAN-FD it is checked against the size of the table. For none CAN-FD size is checked against 8 as defined.
\CM_CAN_HL22 A runtime check ensures source index for LoopTimeout array is always smaller than the dimension of LoopTimeout.
\CM_CAN_HL24 A runtime check ensures RxQueue write index is always smaller than the dimension of RxQueue (Qualified use-case CSL01 of ComStackLib).
\CM_CAN_HL25 A runtime check ensures RxQueue read index is always smaller than the dimension of RxQueue (Qualified use-case CSL01 of ComStackLib).
\CM_CAN_HL28 A runtime check ensures htrh index is always smaller than the dimension of CanMailboxState (Qualified use-case CSL01 of ComStackLib).
\CM_CAN_HL29 Qualified use-case CSL02 of ComStackLib (size of CanMailboxState == size of CanMailbox) 
\CM_CAN_HL30 Qualified use-case CSL03 of ComStackLib (CanMailbox - CanController Start/Stop HtrhIndex).
\CM_CAN_HL31 valid mailbox data area is assigned to rxStruct.pChipData pointer (Has to be given by LL implementation part).
\CM_CAN_HL32 A runtime check ensures TxHwFifo index is always smaller than the dimension of TxHwFifo (Qualified use-case CSL01 of ComStackLib).

\CM_CAN_LL01 The definition of C_ENABLE_IF_RSCAN* is verified by user review [SMI-68706].
\CM_CAN_LL02 The value of kCanBaseAdr is verified by user review [SMI-68706].
\CM_CAN_LL03 The value of kCanMaxPhysChannels is verified by user review [SMI-68706].
\CM_CAN_LL04 A runtime check ensures that the used index is always smaller than kCanMaxPhysChannels.
\CM_CAN_LL05 A runtime check ensures that the used index is always smaller than kCanMaxRxFifos.
\CM_CAN_LL06 A runtime check ensures that the used index is always smaller than kCanMaxTxBuf.
\CM_CAN_LL07 A runtime check ensures that the used index is always smaller than kCanMaxTxFifos.
\CM_CAN_LL08 A runtime check ensures that the used index is always smaller than kCanNumberOfSharedReg16.
\CM_CAN_LL09 A runtime check ensures that the used index is always smaller than kCanMaxRuleAccessCell.
\CM_CAN_LL10 A runtime check ensures that the used index is always smaller than the data size.
\CM_CAN_LL11 A runtime check ensures that the data field of the CanLL_RxTmpBuf has sufficient size.

*/

/****************************************************************************/
/*  Coverage Justification                                                  */
/****************************************************************************/
/* START_COVERAGE_JUSTIFICATION

\ID COV_CAN_COMPATIBILITY
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX xf xf
  \ACCEPT XF tf tf
  \REASON The condition checks whether a switch is defined and conditionally assigns a default value. This is used to ensure compatibility to older AUTOSAR/Component versions. 

\ID COV_CAN_INTERNAL
  \ACCEPT XF
  \ACCEPT TX
  \REASON This switch is always active within CAN driver context. Secure visibility of internal interface and cannot be stimulated to off while test. The code is verified by code inspection.

\ID COV_CAN_CANCEL_SW_STIMULATION
  \ACCEPT TF
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT XX
  \ACCEPT TF tf xf
  \REASON It is not possible to stimulate a sw cancellation while the message is already start to send when hw cancellation is active. The code is verified by code inspection.

\ID COV_CAN_AMD_RUNTIME_MEASUREMENT
  \ACCEPT XF
  \REASON The feature AMD Runtime Measurement is not supported for SafeBSW. A MSSV plugin enforces this configuration for SafeBSW.

\ID COV_CAN_FINALMAGICNUMBER
  \ACCEPT TX
  \REASON Switch is always true is OK here no side effect will occur when switch is false verified by review.

\ID COV_CAN_SAFE_BSW_EXCLUSION
  \ACCEPT XF xf xf
  \REASON SafeBsw restricted feature will not be enforced to be deactivated or activated.

\ID COV_CAN_BUSOFF_NOT_IN_ALL_CONFIG
  \ACCEPT X
  \ACCEPT XF
  \ACCEPT TX
  \ACCEPT TF tf tx
  \ACCEPT TX tx tx
  \REASON BUSOFF not stimulated in each configruation. The behavior does not depend on each configuration variant but TCASE-274 takes long runtime and will not be executed for each configuration.   

\ID COV_CAN_WAKEUP_CHANNEL_NOT_IN_ALL_CONFIG
  \ACCEPT XF
  \ACCEPT TX
  \REASON Wakeup may be always activated or deactivated depend on configuration. Not all configurations contain activated or deactivated wakeup for at least one controller, but is sufficiantly tested in some configuations with both settings.

\ID COV_IMPLICITE_TXCANCEL
  \ACCEPT TX
  \REASON In some configurations there will be no recancellation but for this case there is no active code (empty else), so this is not really a test case.

---------------- LL ------------------

\ID COV_CAN_MULTIPLE_BASICCAN_TX
  \REASON This condition is fully covered for this component.

\ID COV_CAN_SLEEP_SUPPORT
  \ACCEPT TX
  \REASON This condition is constant for SafeBSW projects. A MSSV check and compiler error directives enforce this configuration.

\ID COV_CAN_WAKEUP_SUPPORT
  \REASON This condition is fully covered for this component.

\ID COV_CAN_TX_POLLING
  \REASON This condition is fully covered for this component.

\ID COV_CAN_RX_POLLING
  \REASON This condition is fully covered for this component.

\ID COV_CAN_RX_BASICCAN_POLLING
  \REASON This condition is fully covered for this component.

\ID COV_CAN_RX_FULLCAN_POLLING
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TF tx tf
  \REASON This condition is constant for SafeBSW projects. A MSSV check and compiler error directives enforce this configuration.

\ID COV_CAN_ERROR_POLLING
  \REASON This condition is fully covered for this component.

\ID COV_CAN_WAKEUP_POLLING
  \REASON This condition is fully covered for this component.

\ID COV_CAN_INDIVIDUAL_POLLING
  \REASON This condition is fully covered for this component.

\ID COV_CAN_GENERIC_CONFIRMATION_API2
  \REASON This condition is fully covered for this component.

\ID COV_CAN_FD_SUPPORT
  \REASON This condition is fully covered for this component.

\ID COV_CAN_MULTIPLE_BASICCAN
  \REASON This condition is fully covered for this component.

\ID COV_CAN_TX_FULLCAN_OBJECTS
  \REASON This condition is fully covered for this component.

\ID COV_CAN_RX_FULLCAN_OBJECTS
  \REASON This condition is fully covered for this component.

\ID COV_CAN_HW_TRANSMIT_CANCELLATION
  \REASON This condition is fully covered for this component.

\ID COV_CAN_CANCEL_IN_HW
  \REASON This condition is fully covered for this component.

\ID COV_CAN_HARDWARE_CANCELLATION
  \REASON This condition is fully covered for this component.

\ID COV_CAN_EXTENDED_ID
  \REASON This condition is fully covered for this component.

\ID COV_CAN_MIXED_ID
  \REASON This condition is fully covered for this component.

\ID COV_CAN_OVERRUN_NOTIFICATION
  \REASON This condition is fully covered for this component.

\ID COV_CAN_MULTIPLEXED_TRANSMISSION
  \REASON This condition is fully covered for this component.

\ID COV_CAN_RX_QUEUE
  \REASON This condition is fully covered for this component.

\ID COV_CAN_TX_HW_FIFO
  \REASON This condition is fully covered for this component.

\ID COV_CAN_HW_LAYOUT_TXBASIC_FIRST
  \ACCEPT TX
  \REASON This condition is constant for SafeBSW projects. A MSSV check and compiler error directives enforce this configuration.

\ID COV_CAN_EXTENDED_STATUS
  \ACCEPT TX
  \REASON This condition is constant for SafeBSW projects. A MSSV check and compiler error directives enforce this configuration.

\ID COV_CAN_OVERRUN_IN_STATUS
  \ACCEPT TX
  \REASON This condition is constant for SafeBSW projects. A MSSV check and compiler error directives enforce this configuration.

\ID COV_CAN_OS_USAGE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TX xf tx
  \ACCEPT TF tx tf
  \ACCEPT TF tf xf
  \REASON Not all OS types are used in component test. The code is verified by code inspection.

\ID COV_CAN_LOCK_ISR_BY_APPL
  \REASON This condition is fully covered for this component.

\ID COV_CAN_RAM_CHECK
  \REASON This condition is fully covered for this component.

\ID COV_CAN_RAM_CHECK_EXTENDED
  \REASON This condition is fully covered for this component.

\ID COV_CAN_SAFE_BSW
  \REASON This condition is fully covered for this component.

\ID COV_CAN_RxBasicMsgReceivedBegin
  \ACCEPT TX
  \REASON Depending on the enabled features the function CanLL_RxBasicMsgReceivedBegin() only returns kCanOk and this condition is always true.

\ID COV_CAN_RxFullMsgReceivedBegin
  \ACCEPT TX
  \REASON Depending on the enabled features the function CanLL_RxFullMsgReceivedBegin() only returns kCanOk and this condition is always true.

\ID COV_CAN_HARDWARE_FAILURE
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TF tf xf
  \ACCEPT TF tf xf tf tf
  \ACCEPT TF tf tx tf tf
  \ACCEPT TF xf xx tf tf
  \ACCEPT XF xf xx xf xx
  \REASON The condition checks for hardware failures that cannot be stimulated. The code is verified by code inspection.

\ID COV_CAN_GENDATA_FAILURE
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF xf xf
  \ACCEPT TF xf tf
  \ACCEPT XF xf tf xf xf
  \ACCEPT TF xf tf xf tf
  \REASON The condition checks for generated data failures that cannot be simulated. The code is verified by code inspection.

\ID COV_CAN_GENDATA_NOT_IN_ALL_CONFIG
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF tf xf
  \ACCEPT XF xf xx
  \REASON Generated data does not contain all data sets that are checked in code. Not encapsulated with preprocessor switch because of post build configurations or to reduce complexity, verified by code inspection.

\ID COV_CAN_GENDATA_TX_NOT_IN_ALL_CONFIG
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT TF tf tf tx
  \ACCEPT TF tf tx tx
  \ACCEPT TF tx tf tx
  \ACCEPT TF tx tx tf
  \ACCEPT TF tf tf tx tf
  \ACCEPT TF tf tx tx tf
  \ACCEPT TF tf tx tx tx
  \ACCEPT TF tx tf tx tf
  \ACCEPT TF tx tx tf tf
  \ACCEPT TF tx tx tx tf
  \REASON Generated data does not contain all data sets that are checked in code. Not encapsulated with preprocessor switch because of post build configurations or to reduce complexity, verified by code inspection.

\ID COV_CAN_HWOBJINDIVPOLLING
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT XF
  \REASON Generated data does not contain all data sets that are checked in code. Receive FullCAN mailboxes can only be processed by polling, so this condition is always true in this context.

\ID COV_CAN_RAM_CHECK_NO_STIMULATION
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT XF
  \ACCEPT XF xf xf
  \REASON Some configurations do not stimulate RAM check by test suite to check the standard CAN driver behaviour.

\ID COV_CAN_TRANSITION_REQUEST
  \ACCEPT X
  \ACCEPT TX
  \ACCEPT XF
  \REASON Not all mode transitions require an asynchronous handling that cannot be removed due to HighLevel-LowLevel-interface. The code is verified by code inspection.

\ID COV_CAN_LL_HARDWARE_BEHAVIOUR
  \ACCEPT TX
  \REASON This condition is always true but cannot be removed due to HighLevel-LowLevel-interface. The code is verified by code inspection.

\ID COV_CAN_LL_OSCAT_CONFIG_CHECK
  \REASON The define 'osdIsr' is only available with OSEK OS. It is only used to verify the configuration and does not influence the runtime code.

\ID COV_CAN_LL_ISR_USAGE
  \ACCEPT TX
  \ACCEPT XF
  \REASON Component tests are not executed for all possible channels, therefore some interrupt routines are never or always provided.
          The implementation for different channels is identical and verified with code inspection.

\ID COV_CAN_LL_HARDWARE_FAILURE_RAM_CHECK
  \ACCEPT XF
  \ACCEPT XF xf xf xf
  \ACCEPT XF xf xf xf xf
  \ACCEPT XF xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf xf xf
  \ACCEPT XF xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf xf
  \REASON The condition checks for hardware failures that cannot be stimulated. The code is verified by code inspection.

\ID COV_CAN_LL_MODE_CHECK
  \ACCEPT TX
  \ACCEPT XF
  \REASON The condition checks for hardware failures that cannot be stimulated or is always true or false depending on the pulsing of the controller. The code is verified by code inspection.

\ID COV_CAN_LL_NOT_IN_ALL_CONFIG
  \ACCEPT TF tf xf
  \ACCEPT TF tf tf xf
  \ACCEPT TF tf xf xf
  \ACCEPT TF tf xf xf xf
  \REASON This condition cannot be fully covered in all configurations. The code is verified by code inspection.

\ID COV_CAN_LL_MANUAL
  \REASON This condition is not fully covered by the testsuite. The code is verfied by manual tests and code inspection.

END_COVERAGE_JUSTIFICATION */ 


/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

