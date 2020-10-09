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
 *  \addtogroup  Os_Hal_Timer
 *  \{
 *
 *  \file         Os_Hal_Timer_Types.h
 *  \brief        HAL interface to work with timer hardware.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#ifndef OS_HAL_TIMER_TYPES_H
# define OS_HAL_TIMER_TYPES_H
                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */

/* Os HAL dependencies */


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

struct Os_Hal_TimerConfigType_Tag;
typedef struct Os_Hal_TimerConfigType_Tag Os_Hal_TimerPitConfigType;
typedef struct Os_Hal_TimerConfigType_Tag Os_Hal_TimerFrtConfigType;


/*! Extended high resolution timer's counter data type. */
typedef uint32 Os_Hal_TimerFrtTickType;

/*! Forward declaration of platform specific OSTM timer type. */
struct Os_Hal_OSTMType_Tag;
typedef struct Os_Hal_OSTMType_Tag Os_Hal_OSTMType;
/*! Pointer to a platform specific OSTM timer type. */
typedef P2VAR(volatile Os_Hal_OSTMType, AUTOMATIC, OS_CONST) Os_Hal_OSTMRefType;

/*! Forward declaration of platform specific TAUJ timer type. */
struct Os_Hal_TAUJType_Tag;
typedef struct Os_Hal_TAUJType_Tag Os_Hal_TAUJType;
/*! Pointer to a platform specific TAUJ timer type. */
typedef P2VAR(volatile Os_Hal_TAUJType, AUTOMATIC, OS_CONST) Os_Hal_TAUJRefType;

/*! Forward declaration of platform specific STM timer type. */
struct Os_Hal_STMType_Tag;
typedef struct Os_Hal_STMType_Tag Os_Hal_STMType;
/*! Forward declaration of platform specific STM timer type. */
typedef P2VAR(volatile Os_Hal_STMType, AUTOMATIC, OS_CONST) Os_Hal_STMRefType;

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/


#endif /* OS_HAL_TIMER_TYPES_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Timer_Types.h
 **********************************************************************************************************************/

