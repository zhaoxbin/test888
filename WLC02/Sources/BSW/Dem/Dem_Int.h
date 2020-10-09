/* ********************************************************************************************************************
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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Dem_Int.h
 *      Project:  MICROSAR Diagnostic Event Manager (Dem)
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Implementation file for the MICROSAR Dem
 *
 *********************************************************************************************************************/
/*!
 *  \addtogroup   Dem_Ungrouped
 *  \{
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Savas Ates                    vissat        Vector Informatik GmbH
 *  Anna Bosch                    visanh        Vector Informatik GmbH
 *  Stefan Huebner                vishrs        Vector Informatik GmbH
 *  Thomas Dedler                 visdth        Vector Informatik GmbH
 *  Alexander Ditte               visade        Vector Informatik GmbH
 *  Matthias Heil                 vismhe        Vector Informatik GmbH
 *  Erik Jeglorz                  visejz        Vector Informatik GmbH
 *  Friederike Hitzler            visfrs        Vector Informatik GmbH
 *  Aswin Vijayamohanan Nair      visavi        Vector Informatik GmbH
 *  Fabian Wild                   viszfa        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_INT_H)
#define DEM_INT_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Types.h"
#include "SchM_Dem.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*!
 * \defgroup  Dem_Bitmask_Macros  Macros to define bitmask values by preprocessor
 * Macros to define bitmask values by preprocessor
 * \{
 */


/*! bitfield length of one byte width (8bit) */
#define DEM_1BYTE                                1
/*! bitfield length of two byte width (16bit) */
#define DEM_2BYTE                                2
/*! bitfield length of four byte width (32bit) */
#define DEM_4BYTE                                4

/*! bitmask of one byte width (8bit) */
#define DEM_MASK_1                               0xffU
/*! bitmask of two byte width (16bit) */
#define DEM_MASK_2                               0xffffU
/*! bitmask of four byte width (32bit) */
#define DEM_MASK_4                               0xffffffffUL
/*! bitmask builder for mask of 'size' byte width */
#define DEM_MASK(size)                           DEM_MASK_##size                                                                 /* PRQA S 0342, 3453 */ /* MD_DEM_19.13, MD_MSR_18.4 */

/*! bitmask with bit 'pos' set */
#define DEM_BIT(pos)                             (0x01UL << (pos))                                                               /* PRQA S 3453 */ /* MD_MSR_18.4 */
/*! bitmask of 'size' byte width, with all bits but 'pos' set */
#define DEM_BIT_MASK(pos, size)                  (DEM_MASK(size) ^ DEM_BIT(pos))                                                 /* PRQA S 3453 */ /* MD_MSR_18.4 */

/*! bitmask with n bits set, starting at 'pos' */
#define DEM_NBIT(n, pos)                         ((DEM_MASK(1) >> (8U-(n))) << (pos))                                            /* PRQA S 3453 */ /* MD_MSR_18.4 */
/*! bitmask of 'size' byte width, with all bits set, but n bits starting at 'pos' */
#define DEM_NBIT_MASK(n, pos, size)              (DEM_MASK(size) ^ DEM_NBIT(n, pos))                                             /* PRQA S 3453 */ /* MD_MSR_18.4 */

/*! Test if bit 'pos' in a bitmask is set */
#define DEM_TEST_BIT(mask, pos)                  ((((mask) & DEM_BIT(pos))) != 0)                                                /* PRQA S 3453 */ /* MD_MSR_18.4 */
/*! bitmask with bit 'pos' set without changing existing bits */
#define DEM_SET_BIT(mask, pos)                   ((mask) | DEM_BIT(pos))                                                         /* PRQA S 3453 */ /* MD_MSR_18.4 */
/*! bitmask with bit 'pos' reset without changing existing bits */
#define DEM_RESET_BIT(mask, pos, size)           ((mask) & DEM_BIT_MASK(pos, size))                                              /* PRQA S 3453 */ /* MD_MSR_18.4 */

#define DEM_DIVIDE_ROUND_UP(value, divisor)      (((value) + ((divisor) - 1)) / (divisor))                                       /* PRQA S 3453 */ /* MD_MSR_18.4 */

/*!
 * \}
 */


/* Utilities */
/* ------------------------------------------------------------------------- */
/*! Prevent compiler warning for an unused constant function argument */
#define DEM_IGNORE_UNUSED_CONST_ARGUMENT(argument)  DEM_DUMMY_STATEMENT_CONST(argument);                                         /* PRQA S 3412, 3453 */ /* MD_MSR_19.4, MD_MSR_19.7 */
/*! Prevent compiler warning for an unused variable function argument */
#define DEM_IGNORE_UNUSED_ARGUMENT(argument)     DEM_DUMMY_STATEMENT(argument);                                                  /* PRQA S 3412, 3453 */ /* MD_MSR_19.4, MD_MSR_19.7 */
/*! Prevent compiler warning for an unused local variable */
#define DEM_IGNORE_UNUSED_VARIABLE(argument)     DEM_DUMMY_STATEMENT(argument);                                                  /* PRQA S 3412, 3453 */ /* MD_MSR_19.4, MD_MSR_19.7 */

/*! Rotate 'b' left one bit. b may only contain one set bit */
#define Dem_LROT1_Byte(b)                        { (b) = (uint8)(((b) == 0x80U)?(0x01U):((b) << 1)); }                           /* PRQA S 3412, 3453, 3458 */ /* MD_MSR_19.4, MD_MSR_19.7, MD_MSR_19.7 */
/*! Rotate 'b' left one bit. b may only contain one set bit. Increment 'acc' on each full turn */
#define Dem_LROT1_ADD_Byte(acc, b)               { if ((b) == 0x80U) { ++(acc); (b) = 0x01; } else { (b) = (uint8)((b) << 1); }} /* PRQA S 3412, 3453, 3458 */ /* MD_MSR_19.4, MD_MSR_19.7, MD_MSR_19.7 */
/*! Rotate 'b' left one bit. b may only contain one set bit. Increment 'acc' and do 'act' on each full turn */
#define Dem_LROT1_ADD_ACTION_Byte(acc, act, b)   { if ((b) == 0x80U) { ++(acc); (act); (b) = 0x01; } else { (b) = (uint8)((b) << 1); }} /* PRQA S 3412, 3453, 3458 */ /* MD_MSR_19.4, MD_MSR_19.7, MD_MSR_19.7 */
/*! Increment 'value', wrap around when reaching 'Max' */
#define Dem_WrappingIncrement(Value, Max)        { ++(Value); if ((Value) >= (Max)) { (Value) = 0U; } }                          /* PRQA S 3412, 3453, 3458 */ /* MD_MSR_19.4, MD_MSR_19.7, MD_MSR_19.7 */

/*! Get the high byte of a 16 bit value. Used to serialize data */
#define Dem_GetHiByte(value)                     ((uint8)((uint16)(value)>>8))                                                   /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Get the low byte of a 16 bit value. Used to serialize data */
#define Dem_GetLoByte(value)                     ((uint8)((value)))                                                              /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Get the high word, high byte of a 32 bit value. Used to serialize data */
#define Dem_GetHiHiByte(value)                   ((uint8)((uint32)(value)>>24))                                                  /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Get the high word, low byte of a 32 bit value. Used to serialize data */
#define Dem_GetHiLoByte(value)                   ((uint8)((uint32)(value)>>16))                                                  /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Get the low word, high byte of a 32 bit value. Used to serialize data */
#define Dem_GetLoHiByte(value)                   ((uint8)((uint32)(value)>>8))                                                   /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Get the low word, low byte of a 32 bit value. Used to serialize data */
#define Dem_GetLoLoByte(value)                   ((uint8)(value))                                                                /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Build a 16 bit value from high byte and low byte. Used to de-serialize data */
#define Dem_Make16Bit(hiByte,loByte)             ((uint16)((((uint16)(hiByte))<<8)| \
                                                 ((uint16)(loByte))))                                                            /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Build a 32 bit value from high word high byte, high word low byte, low word high byte and low word low byte. Used to de-serialize data */
#define Dem_Make32Bit(hiHiByte, hiLoByte, loHiByte, loLoByte)   ((uint32)(((uint32)(hiHiByte)<<24)| \
                                                                ((uint32)(hiLoByte)<<16)| \
                                                                ((uint32)(loHiByte)<<8) | \
                                                                ((uint32)(loLoByte))))                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */


/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

                                                        /* Critical Sections */
/* ------------------------------------------------------------------------- */

/*! Enter critical section 'DiagMonitor' */
#define Dem_EnterCritical_DiagMonitor()          SchM_Enter_Dem_DEM_EXCLUSIVE_AREA_0()                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Leave critical section 'DiagMonitor' */
#define Dem_LeaveCritical_DiagMonitor()          SchM_Exit_Dem_DEM_EXCLUSIVE_AREA_0()                                            /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Enter critical section 'StateManager' */
#define Dem_EnterCritical_StateManager()         SchM_Enter_Dem_DEM_EXCLUSIVE_AREA_1()                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Leave critical section 'StateManager' */
#define Dem_LeaveCritical_StateManager()         SchM_Exit_Dem_DEM_EXCLUSIVE_AREA_1()                                            /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Enter critical section 'DcmAPI' */
#define Dem_EnterCritical_DcmApi()               SchM_Enter_Dem_DEM_EXCLUSIVE_AREA_2()                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Leave critical section 'DcmAPI' */
#define Dem_LeaveCritical_DcmApi()               SchM_Exit_Dem_DEM_EXCLUSIVE_AREA_2()                                            /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Enter critical section 'CrossCoreCommunication' */
#define Dem_EnterCritical_CrossCoreComm()        SchM_Enter_Dem_DEM_EXCLUSIVE_AREA_3()                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Leave critical section 'CrossCoreCommunication' */
#define Dem_LeaveCritical_CrossCoreComm()        SchM_Exit_Dem_DEM_EXCLUSIVE_AREA_3()                                            /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Critical section is required, if platform does not support atomic 32 bit access */
#if DEM_ATOMIC_VARIABLE_ACCESS < 32U
/*! Enter critical section 'NonAtomic32bit' */
# define Dem_EnterCritical_NonAtomic32bit()      SchM_Enter_Dem_DEM_EXCLUSIVE_AREA_4()                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Leave critical section 'NonAtomic32bit' */
# define Dem_LeaveCritical_NonAtomic32bit()      SchM_Exit_Dem_DEM_EXCLUSIVE_AREA_4()                                            /* PRQA S 3453 */ /* MD_MSR_19.7 */
#else
/*! Enter critical section 'NonAtomic32bit' */
# define Dem_EnterCritical_NonAtomic32bit()      /* Atomic access */                                                             /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Leave critical section 'NonAtomic32bit' */
# define Dem_LeaveCritical_NonAtomic32bit()      /* Atomic access */                                                             /* PRQA S 3453 */ /* MD_MSR_19.7 */
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Type used for all handles */
typedef uint16 Dem_HandleType;

/*! Iterator type for iteration over global data */
typedef uint16_least Dem_SimpleIterType;

/*! Iterator type for iteration over data subsets */
struct Dem_ComplexIterType_s
{
  uint16_least mIdx;    /*!< Current iterator position */
  uint16_least mEndIdx; /*!< Iterator end position */
};

typedef struct Dem_ComplexIterType_s Dem_ComplexIterType;

#endif /* DEM_INT_H */
/*!
 *  \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Int.h
 *********************************************************************************************************************/
