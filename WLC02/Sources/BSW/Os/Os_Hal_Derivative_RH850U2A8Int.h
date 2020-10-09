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
/**
 * \addtogroup  Os_Hal_Derivative
 * \{
 *
 * \file
 * \brief  This file contains derivative specific information.
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 *********************************************************************************************************************/

#ifndef OS_HAL_DERIVATIVE_RH850U2A8INT_H
# define OS_HAL_DERIVATIVE_RH850U2A8INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  RH850U2A8
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  Core Type
 *********************************************************************************************************************/
/* Defines whether G3X core is supported (STD_ON) or not (STD_OFF) */
# define OS_HAL_CORE_G3X    STD_OFF
/* Defines whether G4X core is supported (STD_ON) or not (STD_OFF) */
# define OS_HAL_CORE_G4X    STD_ON


/**********************************************************************************************************************
 *  Interrupt Controller
 *********************************************************************************************************************/
/* Defines whether G3X interrupt controller is supported (STD_ON) or not (STD_OFF). */
# define OS_HAL_INTC_G3X    STD_OFF
/* Defines whether G4X interrupt controller is supported (STD_ON) or not (STD_OFF). */
# define OS_HAL_INTC_G4X    STD_ON

/*! INTC1 register base address */
# define OS_HAL_INTC1_BASE   (0xFFFC0200uL)
/*! INTC2 register base address */
# define OS_HAL_INTC2_BASE   (0xFFF84000uL)
/*! EIBD1 register base address */
# define OS_HAL_EIBD1_BASE   (0xFFFC0100uL)
/*! EIBD2 register base address */
# define OS_HAL_EIBD2_BASE   (0xFFF82000uL)
/*! IPIR register base address */
# define OS_HAL_IPIR_BASE   (0xFFFB9000uL)


/**********************************************************************************************************************
 *  Timer
 *********************************************************************************************************************/
/*! Support of STM timer units. */
# define OS_HAL_CFG_TIMER_STM    (STD_OFF)
/*! Support of OSTM timer units. */
# define OS_HAL_CFG_TIMER_OSTM   (STD_ON)
/*! Support of TAUJ timer units. */
# define OS_HAL_CFG_TIMER_TAUJ   (STD_ON)

/*! OSTM0 timer unit base address */
# define OS_HAL_TIMER_OSTM0_BASE   (0xFFBF0000uL)
/*! TAUJ0 timer unit base address */
# define OS_HAL_TIMER_TAUJ0_BASE   (0xFFBF7000uL)
/*! TAUJ1 timer unit base address */
# define OS_HAL_TIMER_TAUJ1_BASE   (0xFFBF7200uL)
/*! OSTM1 timer unit base address */
# define OS_HAL_TIMER_OSTM1_BASE   (0xFFBF0100uL)
/*! OSTM2 timer unit base address */
# define OS_HAL_TIMER_OSTM2_BASE   (0xFFBF0200uL)
/*! OSTM3 timer unit base address */
# define OS_HAL_TIMER_OSTM3_BASE   (0xFFBF0300uL)
/*! TAUJ2 timer unit base address */
# define OS_HAL_TIMER_TAUJ2_BASE   (0xFFE80000uL)
/*! TAUJ3 timer unit base address */
# define OS_HAL_TIMER_TAUJ3_BASE   (0xFFE81000uL)
/*! OSTM4 timer unit base address */
# define OS_HAL_TIMER_OSTM4_BASE   (0xFFBF0400uL)
/*! OSTM5 timer unit base address */
# define OS_HAL_TIMER_OSTM5_BASE   (0xFFBF0500uL)
/*! OSTM8 timer unit base address */
# define OS_HAL_TIMER_OSTM8_BASE   (0xFFBF0800uL)
/*! OSTM9 timer unit base address */
# define OS_HAL_TIMER_OSTM9_BASE   (0xFFBF0900uL)

/*! Bit mask to enable OSTM interrupt. */
# define OS_HAL_TIMER_OSTM_INT_ENABLE_MASK    (0x80u)

/**********************************************************************************************************************
 *  Memory Protection
 *********************************************************************************************************************/
/* Defines whether G3X interrupt controller is supported (STD_ON) or not (STD_OFF). */
# define OS_HAL_MPU_G3X    STD_OFF
/* Defines whether G4X interrupt controller is supported (STD_ON) or not (STD_OFF). */
# define OS_HAL_MPU_G4X    STD_ON 

/*! Number of supported MPU regions (Core0). */
# define OS_HAL_MPU_REGION_COUNT_CORE0    (32uL)
/*! Number of supported MPU regions (Core1). */
# define OS_HAL_MPU_REGION_COUNT_CORE1    (32uL)
   
/* Defines initial value to be set to memory region ID */
# define OS_HAL_MEM_REGION_ID_INIT_VAL    (0x1uL)

/**********************************************************************************************************************
 *  Interrupt Priority Mask
 *********************************************************************************************************************/
/*! Mask to disable all EI interrupt levels. */
# define OS_HAL_PMR_MASK     (0x0000001FuL)

/*! Defines the value for register MPM which is used to enable the MPU. */
# define OS_HAL_MPU_ENABLE   (0x00000003uL)

/*! Defines the value for register MPAT0 which is used to setup access rights of MPU region 0 . */
# define OS_HAL_MPU_MPAT0    (0x0000C09BuL)




#endif /* OS_HAL_DERIVATIVE_RH850U2A8INT_H */

/*!
 * \}
 */
/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Derivative_RH850U2A8Int.h
 *********************************************************************************************************************/
