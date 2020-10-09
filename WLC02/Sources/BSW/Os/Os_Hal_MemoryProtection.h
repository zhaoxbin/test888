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
 *  \addtogroup Os_Hal_MemoryProtection
 *  \{
 *
 *  \file       Os_Hal_MemoryProtection.h
 *  \brief
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_MEMORYPROTECTION_H
# define OS_HAL_MEMORYPROTECTION_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_MemoryProtectionInt.h"
# include "Os_Hal_MemoryProtection_Lcfg.h"

/* Os kernel module dependencies */
# include "Os_Kernel.h"
# include "Os_Common.h"

/* Os HAL dependencies */
# include "Os_Hal_Compiler.h"
# include "Os_Hal_Core.h"
# include "Os_Hal_Derivative.h"

/* Select type of core MPU */
# if (OS_HAL_MPU_G3X == STD_ON)
#  include "Os_Hal_MemoryProtection_G3X.h"
# elif (OS_HAL_MPU_G4X == STD_ON)                                                                                       /* COV_OS_DERIVATIVEBETAMODULE */
#  include "Os_Hal_MemoryProtection_G4X.h"
# endif

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/
#if 0
/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Os_Hal_MpAppSwitch()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_MpAppSwitch,
(
  P2CONST(Os_Hal_MpAppConfigType, TYPEDEF, OS_CONST) AppConfig
))
{
  Os_Hal_MpuConfigSwitch(AppConfig);                                                                                    /* SBSW_OS_HAL_FC_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_MpThreadSwitch()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_MpThreadSwitch,
(
  P2CONST(Os_Hal_MpThreadConfigType, TYPEDEF, OS_CONST) ThreadConfig
))
{
  Os_Hal_MpuConfigSwitch(ThreadConfig);                                                                                 /* SBSW_OS_HAL_FC_CALLER */
}


/***********************************************************************************************************************
 *  Os_Hal_MpuConfigSwitch()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,
Os_Hal_MpuConfigSwitch,
(
  P2CONST(Os_Hal_MpCoreConfigType, TYPEDEF, OS_CONST) MpuConfig
))
{
  /* #10 Reconfigure the MPU regions depending on the number of configured regions. */
  switch(MpuConfig->MpuRegionCount)
  {
     case 31: Os_Hal_SetMPU31(MpuConfig);                                                                               /* COV_OS_HALPLATFORMSETMPU */

     case 30: Os_Hal_SetMPU30(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 29: Os_Hal_SetMPU29(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 28: Os_Hal_SetMPU28(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 27: Os_Hal_SetMPU27(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 26: Os_Hal_SetMPU26(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 25: Os_Hal_SetMPU25(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 24: Os_Hal_SetMPU24(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 23: Os_Hal_SetMPU23(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 22: Os_Hal_SetMPU22(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 21: Os_Hal_SetMPU21(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 20: Os_Hal_SetMPU20(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 19: Os_Hal_SetMPU19(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 18: Os_Hal_SetMPU18(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 17: Os_Hal_SetMPU17(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 16: Os_Hal_SetMPU16(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 15: Os_Hal_SetMPU15(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 14: Os_Hal_SetMPU14(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 13: Os_Hal_SetMPU13(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 12: Os_Hal_SetMPU12(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 11: Os_Hal_SetMPU11(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case 10: Os_Hal_SetMPU10(MpuConfig);                                                                               /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case  9: Os_Hal_SetMPU9(MpuConfig);                                                                                /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case  8: Os_Hal_SetMPU8(MpuConfig);                                                                                /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case  7: Os_Hal_SetMPU7(MpuConfig);                                                                                /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case  6: Os_Hal_SetMPU6(MpuConfig);                                                                                /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case  5: Os_Hal_SetMPU5(MpuConfig);                                                                                /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case  4: Os_Hal_SetMPU4(MpuConfig);                                                                                /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case  3: Os_Hal_SetMPU3(MpuConfig);                                                                                /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */ /* COV_OS_HALPLATFORMSETMPU */

     case  2: Os_Hal_SetMPU2(MpuConfig);                                                                                /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */

     case  1: Os_Hal_SetMPU1(MpuConfig);                                                                                /* PRQA S 2003 */ /* MD_Os_Hal_Rule16.3_2003 */

     default: break;                                                                                                    /* PRQA S 2003, 2016 */ /* MD_Os_Hal_Rule16.3_2003, MD_MSR_EmptyClause */
   }
}                                                                                                                       /* PRQA S 6030, 6050 */ /* MD_Os_STCYC, MD_Os_Hal_STCAL */

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* OS_MEMORYPROTECTION_H */


#endif
/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_MemoryProtection.h
 **********************************************************************************************************************/
