/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  MemIf_Types.h
 *    Component:  If_AsrIfMem
 *       Module:  MemIf
 *    Generator:  -
 *
 *  Description:  The Memory Abstraction Interface provides uniform access to services of underlying
 *                Memory Hardware abstraction (MemHwA) modules, i.e. EEPROM Abstraction (EA) and
 *                Flash EEPROM Emulation (FEE). The appropriate MemHwA module is selected by a device index.
 *
 *********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/
#if !defined MEMIF_TYPES_H
#define MEMIF_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define MEMIF_TYPES_AR_RELEASE_MAJOR_VERSION     (4u)
#define MEMIF_TYPES_AR_RELEASE_MINOR_VERSION     (0u)
#define MEMIF_TYPES_AR_RELEASE_REVISION_VERSION  (3u)

#define MEMIF_TYPES_SW_MAJOR_VERSION             (3u)
#define MEMIF_TYPES_SW_MINOR_VERSION             (3u)
#define MEMIF_TYPES_SW_PATCH_VERSION             (1u)

/**** Error Codes in Development-Mode ******************************************************************************/
 /* \trace SPEC-23063 */

#define MEMIF_E_NO_ERROR               (0x00u)
#define MEMIF_E_PARAM_DEVICE           (0x01u)
#define MEMIF_E_PARAM_POINTER          (0x02u)


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* A memory hardware abstraction module's state is denoted in
 * this type. Mainly used in MemIf_GetStatus and related
 * APIs of memory hardware abstraction modules.
 */
typedef enum
{
  MEMIF_UNINIT = 0,
  MEMIF_IDLE,
  MEMIF_BUSY,
  MEMIF_BUSY_INTERNAL
} MemIf_StatusType; /*!< \trace CREQ-793 */


/* A requested job can have one these values after it has been
 * processed. Use in MemIf_GetJobResult and related memory
 * hardware abstraction module APIs.
 */
typedef enum
{
  MEMIF_JOB_OK = 0,
  MEMIF_JOB_FAILED,
  MEMIF_JOB_PENDING,
  MEMIF_JOB_CANCELED,
  MEMIF_BLOCK_INCONSISTENT,
  MEMIF_BLOCK_INVALID
} MemIf_JobResultType; /*!< \trace CREQ-793 */


/* Specifies the processing speed of requested jobs. The exact
 * processing duration in the different modes depends on
 * configuration of the underlying memory hardware abstraction
 * modules.
 */
typedef enum
{
    MEMIF_MODE_SLOW = 0,
    MEMIF_MODE_FAST
} MemIf_ModeType; /*!< \trace CREQ-793 */


/* data pointer for API */
typedef P2VAR(uint8, AUTOMATIC, MEMIF_APPL_DATA) MemIf_DataPtr_pu8;
typedef P2CONST(uint8, AUTOMATIC, MEMIF_APPL_DATA) MemIf_ConstDataPtr_pu8;

/* Workaround for AUTOSAR Release 2.0 Flash Drivers:
 *
 * Fls assumes, that MemIf provides MemIf_AddressType and MemIf_LenghthType.
 * Eep assumes, that it should define its address types on its own.
 * MemIf assumes, that Eep is right and hence does NOT provide these
 * types. However, there are some implementations, that did not recognize
 * this inconsistency, so we have to provide these types in order to
 * get Flash drivers and Flash Eeprom Emulation integrated with the
 * other BSW Modules. In order to minimize the risk of limiting the
 * address range of underlying flash drivers, both types are based
 * on 32bit-address range (allowing 4GB of data, which should be
 * considerably adequate). This might not be the optimum data type
 * on all platforms, but it's the safest.
 */
typedef uint32 MemIf_AddressType;
typedef uint32 MemIf_LengthType;

/*
 * Because of different spelling in AUTOSAR specifications both MEMIF_JOB_CANCELLED
 * and MEMIF_JOB_CANCELED are supported for reasons of compatibility.
 */
#define MEMIF_JOB_CANCELLED     MEMIF_JOB_CANCELED


#endif /* MEMIF_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: MemIf_Types.h
 *********************************************************************************************************************/
