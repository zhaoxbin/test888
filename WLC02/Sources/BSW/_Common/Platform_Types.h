/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2014 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Platform_Types.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  This file provides the platform types for Rh850
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Torsten Kercher               vistkr        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2012-09-17  vistkr                Initial for Rh850 platform
 *  01.00.01  2013-11-05  vistkr                Update to template 1.03.01
 *  01.00.02  2013-12-05  vistkr                Use unsigned suffix for defines
 *  01.01.00  2014-06-18  vistkr                Omit floating point typedefs if GHS compiler with option -fnone is used
 *  01.02.00  2014-10-20  vistkr                AR4-667: Support sint64 and uint64 (update to template 01.04.00)
 *********************************************************************************************************************/

#ifndef PLATFORM_TYPES_H
# define PLATFORM_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : CommonAsr_Rh850 CQComponent : Impl_PlatformTypes */
# define COMMONASR_RH850_IMPL_PLATFORMTYPES_VERSION 0x0102
# define COMMONASR_RH850_IMPL_PLATFORMTYPES_RELEASE_VERSION 0x00

# define PLATFORM_VENDOR_ID    30u    /* SREQ00015439, SREQ00015413 */
# define PLATFORM_MODULE_ID    199u   /* SREQ00015439, SREQ00015413 */

/* AUTOSAR Software Specification Document Version Information */
#   define PLATFORM_AR_RELEASE_MAJOR_VERSION      (4u)
#   define PLATFORM_AR_RELEASE_MINOR_VERSION      (0u)
#   define PLATFORM_AR_RELEASE_REVISION_VERSION   (3u)

/* Component Version Information */
# define PLATFORM_SW_MAJOR_VERSION       (1u)
# define PLATFORM_SW_MINOR_VERSION       (2u)
# define PLATFORM_SW_PATCH_VERSION       (0u) 

# define CPU_TYPE_8       8u
# define CPU_TYPE_16      16u
# define CPU_TYPE_32      32u

# define MSB_FIRST        0u    /* big endian bit ordering */
# define LSB_FIRST        1u    /* little endian bit ordering */

# define HIGH_BYTE_FIRST  0u    /* big endian byte ordering */
# define LOW_BYTE_FIRST   1u    /* little endian byte ordering */

# ifndef TRUE
#  define TRUE            1u
# endif

# ifndef FALSE
#  define FALSE           0u
# endif

# define CPU_TYPE         CPU_TYPE_32

# define CPU_BIT_ORDER    LSB_FIRST        /* little endian bit ordering */

# define CPU_BYTE_ORDER   LOW_BYTE_FIRST   /* little endian byte ordering */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

 typedef unsigned char         boolean;       /*        TRUE .. FALSE           */

 typedef signed char           sint8;         /*        -128 .. +127            */
 typedef unsigned char         uint8;         /*           0 .. 255             */
 typedef signed short          sint16;        /*      -32768 .. +32767          */
 typedef unsigned short        uint16;        /*           0 .. 65535           */
 typedef signed long           sint32;        /* -2147483648 .. +2147483647     */
 typedef unsigned long         uint32;        /*           0 .. 4294967295      */

 typedef signed int            sint8_least;   /* At least 7 bit + 1 bit sign    */
 typedef unsigned int          uint8_least;   /* At least 8 bit                 */
 typedef signed int            sint16_least;  /* At least 15 bit + 1 bit sign   */
 typedef unsigned int          uint16_least;  /* At least 16 bit                */
 typedef signed int            sint32_least;  /* At least 31 bit + 1 bit sign   */
 typedef unsigned int          uint32_least;  /* At least 32 bit                */

# if defined(__ghs__) && !defined(__LLONG_BIT)
 /* 
   The option --no_long_long for GHS compiler disables the support for the long long data type and generates compile
   errors if this type is used. So as an AUTOSAR extension the following typedefs are omitted if --no_long_long is
   given (__LLONG_BIT is not defined in this case).
 */ 
# else
#  define PLATFORM_SUPPORT_SINT64_UINT64
 typedef signed long long      sint64;        /* -9223372036854775808 .. 9223372036854775807      */
 typedef unsigned long long    uint64;        /*                    0 .. 18446744073709551615     */
# endif

# if defined(__ghs__) && defined(__NoFloat__) 
 /* 
   The option -fnone for GHS compiler disallows all floating-point operations and generates compile errors if such
   operations are used by the software. This also applies to any corresponding type definition. So as an AUTOSAR
   extension the following typedefs are omitted if -fnone is given (__NoFloat__ is defined in this case).
 */ 
# else
 typedef float                 float32;
 typedef double                float64;
# endif

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif  /* PLATFORM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Platform_Types.h
 *********************************************************************************************************************/

