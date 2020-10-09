/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 *  \addtogroup  Os_Hal_Core
 *  \{
 *
 *  \file        Os_Hal_Core.c
 *  \brief       Core related primitives which don't have to be inlined.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

                                                                                                                        /* PRQA S 0777 EOF */ /* MD_MSR_Rule5.1 */

#define OS_HAL_CORE_SOURCE

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Core.h"

/* Os kernel module dependencies */

/* Os HAL dependencies */
#include "Os_Core.h"
#include "Os_Hal_Entry.h"
#include "Os_Hal_Core_Cfg.h"
#include "Os_Hal_Os.h"


/***********************************************************************************************************************
 *  VERSION CHECK
 **********************************************************************************************************************/

/* Check the version of OS header file */
#if (  (OS_HAL_SW_MAJOR_VERSION != (2u)) \
    || (OS_HAL_SW_MINOR_VERSION != (27u)) \
    || (OS_HAL_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of Os_Hal_Core.c and Os_Hal_Os.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (OS_CFG_HAL_MAJOR_VERSION != (2u)) \
    || (OS_CFG_HAL_MINOR_VERSION != (20u)) )
# error "Version numbers of Os_Hal_Core.c and Os_Hal_Cfg.h are inconsistent!"
#endif

/***********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#if  0

/***********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define OS_START_SEC_CODE
#include "Os_MemMap_OsCode.h"                                                                                           /* PRQA S 5087 */ /* MD_MSR_MemMap */


/***********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Os_Hal_CoreInit()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, OS_CODE) Os_Hal_CoreInit(P2CONST(Os_Hal_CoreAsrConfigType, AUTOMATIC, OS_CONST) Config)
{
  Os_Hal_IntGlobalStateType oldInterruptState;

  /* #10 Disable all interrupts (EI) and store old state. */
  oldInterruptState = Os_Hal_IntDisableAndReturnGlobalState();

  /* #20 Initialize interrupt controller. */
  Os_Hal_SetEBVFlag();
  Os_Hal_SetINTCFG(0/*OS_HAL_INTCFG_MODE*/);
  Os_Hal_SetEBASE((uint32)(Config->ExceptionVectorTableAddr));                                                          /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  Os_Hal_SetINTBP((uint32)(Config->EIINTVectorTableAddr));                                                              /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
  /* #30 Initialize syscall table and ASID if memory protection is enabled. */
  if (Os_MpIsEnabled() != 0u)
  {
    Os_Hal_Set_MemRegionID(OS_HAL_MEM_REGION_ID_INIT_VAL);
    Os_Hal_SetSCCFG(0);
    Os_Hal_SetSCBP((uint32)OS_SYSCALL_TABLE);                                                                           /* PRQA S 0306 */ /* MD_Os_Hal_Rule11.4_0306 */
    Os_Hal_SyncPipeline();
  }

  /* #40 Restore old interrupt (EI) state. */
  Os_Hal_IntSetGlobalState(&oldInterruptState);                                                                         /* SBSW_OS_HAL_FC_POINTER2LOCAL */
}                                                                                                                       /* PRQA S 6050 */ /* MD_Os_Hal_STCAL */


/***********************************************************************************************************************
 *  Os_Hal_CoreInitHardware()
 **********************************************************************************************************************/
FUNC(void, OS_CODE) Os_Hal_CoreInitHardware(P2CONST(Os_Hal_SystemConfigType, AUTOMATIC, OS_CONST) Config)
{
  OS_IGNORE_UNREF_PARAM(Config);                                                                                        /* PRQA S 3112 */ /* MD_MSR_DummyStmt */
}


/***********************************************************************************************************************
 *  Os_Hal_CoreFreeze()
 **********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
OS_FUNC_ATTRIBUTE_DEFINITION(void, OS_CODE, OS_NORETURN, Os_Hal_CoreFreeze, (void))                                     /* COV_OS_HALCOREFREEZE */
{
  /* #10 Loop endlessly. */
  while(1u == 1u)                                                                                                       /* COV_OS_HALCOREFREEZE */
  {
    Os_Hal_CoreNop();
  }
}


#define OS_STOP_SEC_CODE
#include "Os_MemMap_OsCode.h"                                                                                           /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif
/* START_COVERAGE_JUSTIFICATION

\ID COV_OS_HALCOREFREEZE
   \ACCEPT XX
   \REASON This function is called from Os_ErrKernelPanic() right after the panic hook has returned. As the panic hook
           is the last possible exit point for the tests, Os_Hal_CoreFreeze cannot be covered in tests. Because of the
           simplicity of the code, the performed code inspection results in sufficient quality.

Justifications for core:

\ID COV_OS_HALPLATFORMCLZAVAILABILITY
   \ACCEPT TX
   \REASON The condition is hardware dependent always true. The unnecessary code parts should be
           removed by compiler optimization. As the tests run on each platform, the OS is to be released for, we
           always just test the code for the respective platform. No risk as the remaining code shall be optimized
           away. (Other platforms may set ACCEPT XF with a similar justification)

\ID COV_OS_HALPLATFORMTHREADPOINTERUSERREADABILITY_TX_XF
   \ACCEPT XF
   \REASON The condition is hardware dependent always false. The unnecessary code parts should be
           removed by compiler optimization. As the tests run on each platform, the OS is to be released for, we
           always just test the code for the respective platform. No risk as the remaining code shall be optimized
           away. (Other platforms may set ACCEPT TX with a similar justification)

\ID COV_OS_HALCOREISCOREIDUSERREADABLE
   \ACCEPT XX
   \REASON Since the function Os_Hal_CoreIsThreadPointerUserReadable always returns FALSE within RH850 the
           function Os_Hal_CoreIsCoreIdUserReadable will never be called by core code. No risk as the function
           not needed for any functionallity of the OS and it is extremly simple.

\ID COV_OS_HALPLATFORMCOREIDUSERREADABILITY_TX_XF
   \ACCEPT XF
   \REASON The condition is hardware dependent always false. The unnecessary code parts should be
           removed by compiler optimization. As the tests run on each platform, the OS is to be released for, we
           always just test the code for the respective platform. No risk as the remaining code shall be optimized
           away. (Other platforms may set ACCEPT XF with a similar justification)

\ID COV_OS_HALPLATFORMPRIVILEGEMODEUSERREADABILITY
  \ACCEPT TX
  \REASON The condition is hardware dependent always true. The unnecessary code parts should be
          removed by compiler optimization. As the tests run on each platform, the OS is to be released for, we
          always just test the code for the respective platform. No risk as the remaining code shall be optimized
          away.

\ID COV_OS_HALPLATFORMTHREADPOINTERUSERREADABILITY_XX
  \ACCEPT XX
  \REASON Due to the hardware ability to read the current privileges directly, this function is never called. The
          unnecessary code parts should be removed by compiler optimization. As the tests run on each platform, the OS
          is to be released for, we always just test the code for the respective platform. No risk as the remaining code
          shall be optimized away.

\ID COV_OS_HALPLATFORMCLEARPENDINGAVAILABILITY
   \ACCEPT TX
   \REASON The condition is hardware dependent always true. The unnecessary code parts should be
           removed by compiler optimization. As the tests run on each platform, the OS is to be released for, we
           always just test the code for the respective platform. No risk as the remaining code shall be optimized
           away. (Other platforms may set ACCEPT XF with a similar justification)

\ID COV_OS_HALPLATFORMBITLIBCLZ
   \ACCEPT XX
   \REASON This code is meant as library code for the software implementation of Os_Bit_CountLeadingZeros(). As this
           processor provides a hardware solution, this code is unused. However, the function is extremely simple,
           code inspected and unit tested. It is typically optimized away by the linker. Therefore, the risk of
           keeping this code is expected to be low.

\ID COV_OS_HALPLATFORMUNSUPPORTED8082
   \ACCEPT XX
   \ACCEPT TX
   \ACCEPT XF
   \REASON Unit test and code inspection have not found any risk in keeping this code. On PPC platform this code is
           covered in any case. Exhaustive testing is planned in WORKITEM8082.

\ID COV_OS_HALPLATFORMUNHANDLEDSYSCALL
   \ACCEPT TF
   \REASON This justification is not valid for RH850 and thus it must be covered.

\ID COV_OS_HALPLATFORMNEEDMORETHAN2CORES
   \ACCEPT XF
   \REASON This code can only be reached by using a derivative with more than 2 cores. Currently there is no RH850
           derivatives with more than 2 cores.

\ID COV_OS_HALPLATFORMMASTERSTARTALLOWED
   \ACCEPT XF
   \REASON This code can only be reached when at least one core is configured to be allowed to start the master core.
           In RH850 all cores are auto-started and thus there is no need to configure a core to start the master core.

\ID COV_OS_HALPLATFORMNONAUTOSTARTCORE
   \ACCEPT XX
   \ACCEPT TX
   \REASON This code can only be reached when at least one core is configured to be non-auto start core. In RH850
           all cores are auto-started.

\ID COV_OS_HALPLATFORMGETSPINLOCK
   \ACCEPT XF
   \REASON Though this code may be reached, it is impossible to have a reliable test with only 2 cores to cover this
           branch. Thus this is not covered on RH850, since the reference derivative has only 2 cores. However, the
           correctness can be proved by code review and unit test.

\ID COV_OS_HALPLATFORMAPPISPRIVILEGED
   \ACCEPT XX
   \REASON This function is only called within Os_TrapIsCallerPrivileged and the function Os_TrapIsCallerPrivileged
           will never be called on RH850, since the thread pointer is not readable in user mode.

\ID COV_OS_HALPLATFORMEXCEPTIONCONTEXTUNSUPPORTED
   \ACCEPT XF
   \ACCEPT XX
   \REASON The feature "exception context" is not supported on this platform.

\ID COV_OS_HALPLATFORMEXCEPTIONCONTEXTAVAILABILITY
   \ACCEPT TX
   \REASON The feature "exception context" is not available on this platform.

\ID COV_OS_HALPLATFORMGLOBAL2LEVELSUPPORTED
   \ACCEPT TX
   \REASON Global to level switch is supported on this platform.

\ID COV_OS_HALPLATFORMSETMPU
   \ACCEPT XX
   \REASON Most of the macros Os_Hal_SetMPUx have not been covered by tests. However, all these macros are very similar
           and some of them have been covered by the tests. The only differences between the different macros are the
           addressed registers. These have been reviewed carefully. Therefore, the risk is considered to be low.

\ID COV_OS_HALPLATFORMFRT64BITAVAILABILITY
   \ACCEPT XF
   \ACCEPT XX
   \REASON The feature "64-bit FRT timer" is not available on this platform.

END_COVERAGE_JUSTIFICATION */

/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_OS_HAL_PWA_CALLER
 \DESCRIPTION    A write access is performed on a pointer, which is coming directly from the caller.
 \COUNTERMEASURE \N No measure is required, because the caller has to check the validity.

\ID SBSW_OS_HAL_FC_CALLER
 \DESCRIPTION    A function is called with one or more pointer parameters, which are coming directly from the caller.
 \COUNTERMEASURE \N No measure is required, because the caller has to check the validity.

\ID SBSW_OS_HAL_PWA_XSIGNAL_ENABLE
 \DESCRIPTION    A write access is performed on the interrupt control register INTIPIRn via OS_HAL_XSIG_INTCTRL(addr) in order to
                 clear the interrupt disable flag. The validity of macro OS_HAL_XSIG_INTCTRL(addr) is checked by review.
 \COUNTERMEASURE \S Safety manual should state that the functionality of each configured ISR has to be checked for its correctness.
                 The user of MICROSAR Safe shall verify the functionality of each configured ISR.
                 This includes the correct call of the ISR handler with the correct priority (level) as well as enabling, disabling,
                 reading the enable state, reading the pending state and clearing of the pending information of the corresponding
                 ISR sources.
                 SMI-491

\ID SBSW_OS_HAL_PWA_XSIGNAL_TRIGGER
 \DESCRIPTION    A write access is performed on the interrupt control register IPIR_CHn via OS_HAL_XSIG_TRIGGER(addr) in order to
                 trigger the XSignal interrupt. The validity of macro OS_HAL_XSIG_TRIGGER(addr) is checked by review.
 \COUNTERMEASURE \S Safety manual should state that the functionality of each configured ISR has to be checked for its correctness.
                 The user of MICROSAR Safe shall verify the functionality of each configured ISR.
                 This includes the correct call of the ISR handler with the correct priority (level) as well as enabling, disabling,
                 reading the enable state, reading the pending state and clearing of the pending information of the corresponding
                 ISR sources.
                 SMI-491

\ID SBSW_OS_HAL_PWA_PA_ISRCONFIG
 \DESCRIPTION    A write access is performed on a pointer, which is obtained by dereferencing a pointer to a struct,
                 of type Os_Hal_IntIsrConfigType, coming directly from the caller.
 \COUNTERMEASURE \S Safety manual should state that the functionality of each configured ISR has to be checked for its correctness.
                 The user of MICROSAR Safe shall verify the functionality of each configured ISR.
                 This includes the correct call of the ISR handler with the correct priority (level) as well as enabling, disabling,
                 reading the enable state, reading the pending state and clearing of the pending information of the corresponding
                 ISR sources.
                 SMI-491

\ID SBSW_OS_HAL_PWA_PITCONFIG
 \DESCRIPTION    A write access is performed starting from the Timer Base Address, which is generated from the timer configuration
                 for OSTM or TAUJ of type Os_Hal_TimerPitConfigType.
                 In addition, the validity of OS_HAL_TIMER_OSTM<X>_BASE, OS_HAL_TIMER_TAUJ<X>_BASE and OS_HAL_TIMER_CH<Y> is checked by review.
 \COUNTERMEASURE \S Safety manual should state that the PIT timer configuration of type Os_Hal_TimerPitConfigType in Os_Hal_Timer_Lcfg.c
                 has to be checked for its correctness.
                 If the OSTM module <X> (0,1,2,5) is configured, the following attributes must be generated as follows:
                 Timer Base Address  = OS_HAL_TIMER_OSTM<X>_BASE
                 Timer Hardware Type = OS_HAL_TIMER_OSTM
                 Timer Channel Index = OS_HAL_TIMER_CH0
                 Timer Unit Index    = OS_HAL_TIMER_OSTM<X>
                 If the TAUJ module <X> (0,1,2) channel <Y> (0,1,2,3) is configured, the following attributes must be generated as follows:
                 Timer Base Address  = OS_HAL_TIMER_TAUJ<X>_BASE
                 Timer Hardware Type = OS_HAL_TIMER_TAUJ
                 Timer Channel Index = OS_HAL_TIMER_CH<Y>
                 Timer Unit Index    = OS_HAL_TIMER_TAUJ<X>
                 SMI-3310

\ID SBSW_OS_HAL_PWA_FRTCONFIG
 \DESCRIPTION    A write access is performed starting from the Timer Base Address, which is generated from the timer configuration
                 for OSTM or STM of type Os_Hal_TimerFrtConfigType in Os_Hal_Timer_Lcfg.c.
                 In addition, the validity of OS_HAL_TIMER_OSTM<X>_BASE, OS_HAL_TIMER_STM<X>_BASE and OS_HAL_TIMER_CH<Y> is checked by review.
 \COUNTERMEASURE \S Safety manual should state that the FRT timer configuration of type Os_Hal_TimerFrtConfigType in Os_Hal_Timer_Lcfg.c
                 has to be checked for its correctness.
                 If the STM module <X> (0,1) channel <Y> (1,2,3) is configured, the following attributes must be generated as follows:
                 Timer Base Address  = OS_HAL_TIMER_STM<X>_BASE
                 Timer Hardware Type = OS_HAL_TIMER_STM
                 Timer Channel Index = OS_HAL_TIMER_CH<Y>
                 Timer Unit Index    = OS_HAL_TIMER_STM<X>
                 SMI-3311

\ID SBSW_OS_HAL_PWA_FEINTFMSKCONFIG
 \DESCRIPTION    A write access is performed into register FEINFMSKn. The base address is taken from table osFEINTFMSKnBase[] which is
                 checked by review. Pointer TimerConfig is valid because it is checked by caller. The Array index is taken from generated
                 timer configuration and the validity of TimerConfig->TimerIndex (OS_HAL_TIMER_STM<X>) is checked by review.
 \COUNTERMEASURE \S Safety manual should state that the STM timer configuration of type Os_Hal_TimerFrtConfigType in Os_Hal_Timer_Lcfg.c
                 has to be checked for its correctness.
                 If the STM module <X> (0,1) channel <Y> (1,2,3) is configured, the following attributes must be generated as follows:
                 Timer Base Address  = OS_HAL_TIMER_STM<X>_BASE
                 Timer Hardware Type = OS_HAL_TIMER_STM
                 Timer Channel Index = OS_HAL_TIMER_CH<Y>
                 Timer Unit Index    = OS_HAL_TIMER_STM<X>
                 SMI-3311

\ID SBSW_OS_HAL_FC_POINTER2LOCAL
 \DESCRIPTION    Pass a reference to a local variable.
 \COUNTERMEASURE \N No measure required, as the passed pointer refers to a local variable and the called function
                    allows that the existence of the local variable ends on return.

SBSW_JUSTIFICATION_END */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Core.c
 **********************************************************************************************************************/

