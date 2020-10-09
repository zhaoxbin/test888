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

/***************************************************************************/
/* Include files                                                           */
/***************************************************************************/
/* ECO_IGNORE_BLOCK_BEGIN */
#define C_DRV_INTERNAL
#define CAN_IRQ_SOURCE     /* testability */

#include "Can.h"
#if defined(V_OSTYPE_OSEK) /* COV_CAN_OS_USAGE */
# include "osek.h"
#endif
/* \trace SPEC-1408 */
#if defined(V_OSTYPE_AUTOSAR) /* COV_CAN_OS_USAGE */
# include "Os.h"
#endif


/* ECO_IGNORE_BLOCK_END */

/***************************************************************************/
/* Version Check                                                           */
/***************************************************************************/
/* \trace SPEC-20329 */
/* not the SW version but all file versions that represent the SW version are checked */
#if (CAN_COREVERSION           != 0x0800u) /* \trace SPEC-1699, SPEC-3837 */
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

#if defined(CAN_ENABLE_USE_INIT_ROOT_POINTER)
# define CAN_START_SEC_VAR_INIT_UNSPECIFIED  /*-----------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
V_DEF_P2CONST (extern, Can_ConfigType, VAR_INIT, CONST_PBCFG) Can_ConfigDataPtr; /* PRQA S 3447,3451,3210 */ /* MD_Can_ExternalScope */
# define CAN_STOP_SEC_VAR_INIT_UNSPECIFIED  /*------------------------------*/
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

/***************************************************************************/
/* Interrupt Service Routine                                               */
/***************************************************************************/
#define CAN_START_SEC_CODE  /*-----------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* \trace SPEC-1579, SPEC-1395, SPEC-1567 */
# if (CAN_POSTBUILD_VARIANT_SUPPORT == STD_ON)
#  define CAN_USE_PHYSTOLOG_MAPPING
# endif


/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_0 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrTx_0Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrTx_0Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_0 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrTx_0Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrTx_0Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrTx_0()
****************************************************************************/
/*
|<DataModelStart>| CanIsrTx_0
Relation_Context:
TxPolling, IndividualPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_0( void ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptTx(Can_GetPhysToLogChannel(0));
#    else
  CanInterruptTx(kCanPhysToLogChannelIndex_0);
#    endif
#  else
  CanInterruptTx();
#  endif
}
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_0) */
/* CODE CATEGORY 1 END */


#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_0 ) /* COV_CAN_LL_ISR_USAGE */
# if !defined(C_ENABLE_WAKEUP_POLLING) || defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrWakeup_0Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrWakeup_0Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_0 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrWakeup_0Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrWakeup_0Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrWakeup_0()
****************************************************************************/
/*
|<DataModelStart>| CanIsrWakeup_0
Relation_Context:
Wakeup, WakeupPolling, CanInterruptControl, UseNestedCANInterrupts
Relation:
WakeupPolling, OneChOpt, Variant, ChannelAmount
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
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_0( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
#  if !defined(C_ENABLE_WAKEUP_POLLING)
  /* #10 call interrupt handler */
#   if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#     if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptWakeup(Can_GetPhysToLogChannel(0));
#     else
  CanInterruptWakeup(kCanPhysToLogChannelIndex_0);
#     endif
#   else
  CanInterruptWakeup();
#   endif
#  endif
}
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_0) */
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_0 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrStatus_0Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrStatus_0Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_0 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrStatus_0Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrStatus_0Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrStatus_0()
****************************************************************************/
/*
|<DataModelStart>| CanIsrStatus_0
Relation_Context:
TxPolling, IndividualPolling, StatusPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_0( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptStatus(Can_GetPhysToLogChannel(0));
#    else
  CanInterruptStatus(kCanPhysToLogChannelIndex_0);
#    endif
#  else
  CanInterruptStatus();
#  endif
}
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_0) */
/* CODE CATEGORY 1 END */


/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_1 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrTx_1Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrTx_1Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_1 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrTx_1Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrTx_1Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrTx_1()
****************************************************************************/
/*
|<DataModelStart>| CanIsrTx_1
Relation_Context:
TxPolling, IndividualPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_1( void ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptTx(Can_GetPhysToLogChannel(1));
#    else
  CanInterruptTx(kCanPhysToLogChannelIndex_1);
#    endif
#  else
  CanInterruptTx();
#  endif
}
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_1) */
/* CODE CATEGORY 1 END */


#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_1 ) /* COV_CAN_LL_ISR_USAGE */
# if !defined(C_ENABLE_WAKEUP_POLLING) || defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrWakeup_1Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrWakeup_1Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_1 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrWakeup_1Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrWakeup_1Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrWakeup_1()
****************************************************************************/
/*
|<DataModelStart>| CanIsrWakeup_1
Relation_Context:
Wakeup, WakeupPolling, CanInterruptControl, UseNestedCANInterrupts
Relation:
WakeupPolling, OneChOpt, Variant, ChannelAmount
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
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_1( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
#  if !defined(C_ENABLE_WAKEUP_POLLING)
  /* #10 call interrupt handler */
#   if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#     if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptWakeup(Can_GetPhysToLogChannel(1));
#     else
  CanInterruptWakeup(kCanPhysToLogChannelIndex_1);
#     endif
#   else
  CanInterruptWakeup();
#   endif
#  endif
}
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_1) */
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_1 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrStatus_1Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrStatus_1Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_1 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrStatus_1Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrStatus_1Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrStatus_1()
****************************************************************************/
/*
|<DataModelStart>| CanIsrStatus_1
Relation_Context:
TxPolling, IndividualPolling, StatusPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_1( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptStatus(Can_GetPhysToLogChannel(1));
#    else
  CanInterruptStatus(kCanPhysToLogChannelIndex_1);
#    endif
#  else
  CanInterruptStatus();
#  endif
}
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_1) */
/* CODE CATEGORY 1 END */


/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_2 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrTx_2Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrTx_2Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_2 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrTx_2Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrTx_2Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrTx_2()
****************************************************************************/
/*
|<DataModelStart>| CanIsrTx_2
Relation_Context:
TxPolling, IndividualPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_2( void ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptTx(Can_GetPhysToLogChannel(2));
#    else
  CanInterruptTx(kCanPhysToLogChannelIndex_2);
#    endif
#  else
  CanInterruptTx();
#  endif
}
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_2) */
/* CODE CATEGORY 1 END */


#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_2 ) /* COV_CAN_LL_ISR_USAGE */
# if !defined(C_ENABLE_WAKEUP_POLLING) || defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrWakeup_2Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrWakeup_2Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_2 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrWakeup_2Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrWakeup_2Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrWakeup_2()
****************************************************************************/
/*
|<DataModelStart>| CanIsrWakeup_2
Relation_Context:
Wakeup, WakeupPolling, CanInterruptControl, UseNestedCANInterrupts
Relation:
WakeupPolling, OneChOpt, Variant, ChannelAmount
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
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_2( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
#  if !defined(C_ENABLE_WAKEUP_POLLING)
  /* #10 call interrupt handler */
#   if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#     if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptWakeup(Can_GetPhysToLogChannel(2));
#     else
  CanInterruptWakeup(kCanPhysToLogChannelIndex_2);
#     endif
#   else
  CanInterruptWakeup();
#   endif
#  endif
}
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_2) */
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_2 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrStatus_2Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrStatus_2Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_2 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrStatus_2Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrStatus_2Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrStatus_2()
****************************************************************************/
/*
|<DataModelStart>| CanIsrStatus_2
Relation_Context:
TxPolling, IndividualPolling, StatusPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_2( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptStatus(Can_GetPhysToLogChannel(2));
#    else
  CanInterruptStatus(kCanPhysToLogChannelIndex_2);
#    endif
#  else
  CanInterruptStatus();
#  endif
}
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_2) */
/* CODE CATEGORY 1 END */


/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_3 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrTx_3Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrTx_3Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_3 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrTx_3Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrTx_3Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrTx_3()
****************************************************************************/
/*
|<DataModelStart>| CanIsrTx_3
Relation_Context:
TxPolling, IndividualPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_3( void ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptTx(Can_GetPhysToLogChannel(3));
#    else
  CanInterruptTx(kCanPhysToLogChannelIndex_3);
#    endif
#  else
  CanInterruptTx();
#  endif
}
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_3) */
/* CODE CATEGORY 1 END */


#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_3 ) /* COV_CAN_LL_ISR_USAGE */
# if !defined(C_ENABLE_WAKEUP_POLLING) || defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrWakeup_3Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrWakeup_3Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_3 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrWakeup_3Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrWakeup_3Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrWakeup_3()
****************************************************************************/
/*
|<DataModelStart>| CanIsrWakeup_3
Relation_Context:
Wakeup, WakeupPolling, CanInterruptControl, UseNestedCANInterrupts
Relation:
WakeupPolling, OneChOpt, Variant, ChannelAmount
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
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_3( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
#  if !defined(C_ENABLE_WAKEUP_POLLING)
  /* #10 call interrupt handler */
#   if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#     if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptWakeup(Can_GetPhysToLogChannel(3));
#     else
  CanInterruptWakeup(kCanPhysToLogChannelIndex_3);
#     endif
#   else
  CanInterruptWakeup();
#   endif
#  endif
}
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_3) */
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_3 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrStatus_3Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrStatus_3Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_3 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrStatus_3Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrStatus_3Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrStatus_3()
****************************************************************************/
/*
|<DataModelStart>| CanIsrStatus_3
Relation_Context:
TxPolling, IndividualPolling, StatusPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_3( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptStatus(Can_GetPhysToLogChannel(3));
#    else
  CanInterruptStatus(kCanPhysToLogChannelIndex_3);
#    endif
#  else
  CanInterruptStatus();
#  endif
}
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_3) */
/* CODE CATEGORY 1 END */


/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_4 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrTx_4Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrTx_4Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_4 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrTx_4Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrTx_4Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrTx_4()
****************************************************************************/
/*
|<DataModelStart>| CanIsrTx_4
Relation_Context:
TxPolling, IndividualPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_4( void ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptTx(Can_GetPhysToLogChannel(4));
#    else
  CanInterruptTx(kCanPhysToLogChannelIndex_4);
#    endif
#  else
  CanInterruptTx();
#  endif
}
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_4) */
/* CODE CATEGORY 1 END */


#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_4 ) /* COV_CAN_LL_ISR_USAGE */
# if !defined(C_ENABLE_WAKEUP_POLLING) || defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrWakeup_4Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrWakeup_4Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_4 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrWakeup_4Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrWakeup_4Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrWakeup_4()
****************************************************************************/
/*
|<DataModelStart>| CanIsrWakeup_4
Relation_Context:
Wakeup, WakeupPolling, CanInterruptControl, UseNestedCANInterrupts
Relation:
WakeupPolling, OneChOpt, Variant, ChannelAmount
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
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_4( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
#  if !defined(C_ENABLE_WAKEUP_POLLING)
  /* #10 call interrupt handler */
#   if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#     if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptWakeup(Can_GetPhysToLogChannel(4));
#     else
  CanInterruptWakeup(kCanPhysToLogChannelIndex_4);
#     endif
#   else
  CanInterruptWakeup();
#   endif
#  endif
}
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_4) */
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_4 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrStatus_4Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrStatus_4Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_4 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrStatus_4Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrStatus_4Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrStatus_4()
****************************************************************************/
/*
|<DataModelStart>| CanIsrStatus_4
Relation_Context:
TxPolling, IndividualPolling, StatusPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_4( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptStatus(Can_GetPhysToLogChannel(4));
#    else
  CanInterruptStatus(kCanPhysToLogChannelIndex_4);
#    endif
#  else
  CanInterruptStatus();
#  endif
}
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_4) */
/* CODE CATEGORY 1 END */


/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_5 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrTx_5Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrTx_5Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_5 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrTx_5Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrTx_5Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrTx_5()
****************************************************************************/
/*
|<DataModelStart>| CanIsrTx_5
Relation_Context:
TxPolling, IndividualPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_5( void ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptTx(Can_GetPhysToLogChannel(5));
#    else
  CanInterruptTx(kCanPhysToLogChannelIndex_5);
#    endif
#  else
  CanInterruptTx();
#  endif
}
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_5) */
/* CODE CATEGORY 1 END */


#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_5 ) /* COV_CAN_LL_ISR_USAGE */
# if !defined(C_ENABLE_WAKEUP_POLLING) || defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrWakeup_5Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrWakeup_5Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_5 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrWakeup_5Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrWakeup_5Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrWakeup_5()
****************************************************************************/
/*
|<DataModelStart>| CanIsrWakeup_5
Relation_Context:
Wakeup, WakeupPolling, CanInterruptControl, UseNestedCANInterrupts
Relation:
WakeupPolling, OneChOpt, Variant, ChannelAmount
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
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_5( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
#  if !defined(C_ENABLE_WAKEUP_POLLING)
  /* #10 call interrupt handler */
#   if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#     if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptWakeup(Can_GetPhysToLogChannel(5));
#     else
  CanInterruptWakeup(kCanPhysToLogChannelIndex_5);
#     endif
#   else
  CanInterruptWakeup();
#   endif
#  endif
}
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_5) */
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_5 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrStatus_5Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrStatus_5Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_5 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrStatus_5Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrStatus_5Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrStatus_5()
****************************************************************************/
/*
|<DataModelStart>| CanIsrStatus_5
Relation_Context:
TxPolling, IndividualPolling, StatusPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_5( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptStatus(Can_GetPhysToLogChannel(5));
#    else
  CanInterruptStatus(kCanPhysToLogChannelIndex_5);
#    endif
#  else
  CanInterruptStatus();
#  endif
}
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_5) */
/* CODE CATEGORY 1 END */


/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_6 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrTx_6Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrTx_6Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_6 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrTx_6Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrTx_6Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrTx_6()
****************************************************************************/
/*
|<DataModelStart>| CanIsrTx_6
Relation_Context:
TxPolling, IndividualPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_6( void ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptTx(Can_GetPhysToLogChannel(6));
#    else
  CanInterruptTx(kCanPhysToLogChannelIndex_6);
#    endif
#  else
  CanInterruptTx();
#  endif
}
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_6) */
/* CODE CATEGORY 1 END */


#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_6 ) /* COV_CAN_LL_ISR_USAGE */
# if !defined(C_ENABLE_WAKEUP_POLLING) || defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrWakeup_6Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrWakeup_6Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_6 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrWakeup_6Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrWakeup_6Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrWakeup_6()
****************************************************************************/
/*
|<DataModelStart>| CanIsrWakeup_6
Relation_Context:
Wakeup, WakeupPolling, CanInterruptControl, UseNestedCANInterrupts
Relation:
WakeupPolling, OneChOpt, Variant, ChannelAmount
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
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_6( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
#  if !defined(C_ENABLE_WAKEUP_POLLING)
  /* #10 call interrupt handler */
#   if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#     if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptWakeup(Can_GetPhysToLogChannel(6));
#     else
  CanInterruptWakeup(kCanPhysToLogChannelIndex_6);
#     endif
#   else
  CanInterruptWakeup();
#   endif
#  endif
}
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_6) */
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_6 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrStatus_6Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrStatus_6Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_6 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrStatus_6Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrStatus_6Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrStatus_6()
****************************************************************************/
/*
|<DataModelStart>| CanIsrStatus_6
Relation_Context:
TxPolling, IndividualPolling, StatusPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_6( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptStatus(Can_GetPhysToLogChannel(6));
#    else
  CanInterruptStatus(kCanPhysToLogChannelIndex_6);
#    endif
#  else
  CanInterruptStatus();
#  endif
}
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_6) */
/* CODE CATEGORY 1 END */


/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_7 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_TX_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrTx_7Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrTx_7Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrTx_7 ) /* COV_CAN_HWOBJINDIVPOLLING */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrTx_7Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrTx_7Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrTx_7()
****************************************************************************/
/*
|<DataModelStart>| CanIsrTx_7
Relation_Context:
TxPolling, IndividualPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrTx_7( void ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptTx(Can_GetPhysToLogChannel(7));
#    else
  CanInterruptTx(kCanPhysToLogChannelIndex_7);
#    endif
#  else
  CanInterruptTx();
#  endif
}
# endif /* C_ENABLE_TX_POLLING */
#endif /* (kCanPhysToLogChannelIndex_7) */
/* CODE CATEGORY 1 END */


#if defined(C_ENABLE_LL_WAKEUP_SUPPORT)
/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_7 ) /* COV_CAN_LL_ISR_USAGE */
# if !defined(C_ENABLE_WAKEUP_POLLING) || defined(C_ENABLE_USE_OS_INTERRUPT_CONTROL)
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrWakeup_7Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrWakeup_7Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrWakeup_7 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrWakeup_7Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrWakeup_7Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrWakeup_7()
****************************************************************************/
/*
|<DataModelStart>| CanIsrWakeup_7
Relation_Context:
Wakeup, WakeupPolling, CanInterruptControl, UseNestedCANInterrupts
Relation:
WakeupPolling, OneChOpt, Variant, ChannelAmount
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
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrWakeup_7( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
#  if !defined(C_ENABLE_WAKEUP_POLLING)
  /* #10 call interrupt handler */
#   if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#     if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptWakeup(Can_GetPhysToLogChannel(7));
#     else
  CanInterruptWakeup(kCanPhysToLogChannelIndex_7);
#     endif
#   else
  CanInterruptWakeup();
#   endif
#  endif
}
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* (kCanPhysToLogChannelIndex_7) */
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 1 START */
#if defined( kCanPhysToLogChannelIndex_7 ) /* COV_CAN_LL_ISR_USAGE */
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrStatus_7Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrStatus_7Cat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrStatus_7 ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrStatus_7Cat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrStatus_7Cat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrStatus_7()
****************************************************************************/
/*
|<DataModelStart>| CanIsrStatus_7
Relation_Context:
TxPolling, IndividualPolling, StatusPolling, UseNestedCANInterrupts
Relation:
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
 */
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrStatus_7( void ) /* COV_CAN_LL_NOT_IN_ALL_CONFIG X */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
#  if defined(C_MULTIPLE_RECEIVE_CHANNEL) /* COV_CAN_LL_ISR_USAGE */
#    if defined(CAN_USE_PHYSTOLOG_MAPPING)
  CanInterruptStatus(Can_GetPhysToLogChannel(7));
#    else
  CanInterruptStatus(kCanPhysToLogChannelIndex_7);
#    endif
#  else
  CanInterruptStatus();
#  endif
}
# endif /* C_ENABLE_ERROR_POLLING */
#endif /* (kCanPhysToLogChannelIndex_7) */
/* CODE CATEGORY 1 END */


#if (defined(C_ENABLE_RX_BASICCAN_OBJECTS) && defined(C_ENABLE_OVERRUN)) 
/* CODE CATEGORY 1 START */
# if defined(C_ENABLE_ERROR_POLLING)
# else
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrGlobalStatusCat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrGlobalStatusCat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrGlobalStatus )
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrGlobalStatusCat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrGlobalStatusCat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrGlobalStatus()
****************************************************************************/
/*
|<DataModelStart>| CanIsrGlobalStatus
Relation_Context:
TxPolling, IndividualPolling, StatusPolling, RxBasicCANSupport, Overrun, UseNestedCANInterrupts
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
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrGlobalStatus( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
  CanInterruptGlobalStatus();
}
# endif /* C_ENABLE_ERROR_POLLING */
/* CODE CATEGORY 1 END */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS && C_ENABLE_OVERRUN */

#if defined(C_ENABLE_RX_BASICCAN_OBJECTS)
# if defined(C_ENABLE_RX_BASICCAN_POLLING) && !defined(C_ENABLE_INDIVIDUAL_POLLING)
# else

/* CODE CATEGORY 1 START */
#  if defined(C_ENABLE_OSEK_OS) && defined(C_ENABLE_OSEK_OS_INTCAT2) /* COV_CAN_OS_USAGE */
#   if defined(osdIsrCanIsrRxFifoCat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#    if (osdIsrCanIsrRxFifoCat != 2u)
#     error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsrRxFifo ) /* COV_CAN_HWOBJINDIVPOLLING */
#  else
#   if defined(C_ENABLE_OSEK_OS) /* COV_CAN_OS_USAGE */
#    if defined(osdIsrCanIsrRxFifoCat) /* COV_CAN_LL_OSCAT_CONFIG_CHECK XF */
#     if (osdIsrCanIsrRxFifoCat != 1u)
#      error "inconsistent configuration of Osek-OS interrupt category between CANgen/GENy and OIL-configurator (CanIsr)"
#     endif
#    endif
#   endif
#   if !defined(C_ENABLE_ISRVOID)
#    if defined(C_COMP_GHS_RH850_RSCAN) /* COV_CAN_LL_CONSTANT_DEFINITION_COMPILER */
#     if defined(C_ENABLE_NESTED_INTERRUPTS)
#pragma ghs interrupt(enabled) /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     else
#pragma ghs interrupt /* PRQA S 3116 */ /* MD_Can_Pragma_LL */
#     endif
#    endif
#   endif
/****************************************************************************
| NAME:             CanIsrRxFifo()
****************************************************************************/
/*
|<DataModelStart>| CanIsrRxFifo
Relation_Context:
TxPolling, IndividualPolling, RxBasicCANSupport, IndividualPolling, ChannelAmount, RxPolling, UseNestedCANInterrupts
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
V_DEF_FUNC(C_ISR_KEYWORD, void, CODE) CanIsrRxFifo( void ) /* COV_CAN_HWOBJINDIVPOLLING */
#  endif /* C_ENABLE_OSEK_OS */
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 call interrupt handler */
  //CanInterruptRxFifo();
}
/* CODE CATEGORY 1 END */

# endif /* C_ENABLE_RX_BASICCAN_POLLING */
#endif /* C_ENABLE_RX_BASICCAN_OBJECTS */


#define CAN_STOP_SEC_CODE  /*------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 1 */

