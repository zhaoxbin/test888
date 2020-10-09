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
 *         \file  Crc.h
 *        \brief  Cyclic redundancy check header file
 *
 *      \details  Crc module is used to calculate cyclic codes, which encode messages by adding a fixed-length check
 *                value, for the purpose of error detection. Data blocks get a short CRC value attached, which is
 *                based on the remainder of a polynomial division of their contents. Upon retrieval of block data,
 *                the calculation is repeated and the calculated value is compared to the attached CRC value in order
 *                to ensure data integrity.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Tobias Schmid                 Tsd           Vector Informatik GmbH
 *  Claudia Mausz                 Mz            Vector Informatik GmbH
 *  Martin Froschhammer           Mfr           Vector Informatik GmbH
 *  Michael Goss                  Gmi           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id      Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  03.00.00  2007-11-29  Tsd     -              Updated component to AUTOSAR Release 2.1
 *  04.00.00  2008-05-07  Mz      -              Add Crc8 calculation AUTOSAR Release 3.0
 *                                ESCAN00026229  Add Extension for MSR3.0 LinkTime checks
 *  04.00.01  2009-02-13  Mz      ESCAN00031923  Resolved the inconsistency between Compiler Abstraction keywords
 *  05.00.00  2012-07-12  Mfr     -              API changes due to AUTOSAR Release 4.0
 *  05.00.01  2014-06-11  Gmi     ESCAN00076182  Multiple-call CRC calculation is handled correctly
 *                                ESCAN00075763  Inclusion of "v_ver.h" was removed
 *  05.01.00  2014-11-14  Gmi     ESCAN00079575  Calculation method Crc_CalculateCRC8H2F was added
 *  05.02.00  2015-04-30  Gmi     ESCAN00082814  FEAT-1275: SafeBSW
 *  05.03.00  2015-09-18  Gmi     ESCAN00085028  FEAT-1372: Updated Cfg Version Check
 *                                -              Formatted some elements due to Vector Coding Rules
 *                                -              NULL_PTR check was added to Crc_GetVersionInfo
 *            2015-11-09  Gmi     ESCAN00083396  Compiler warnings due to type conversion were fixed
 *  05.04.00  2016-11-22  Gmi     FEAT-2252      Support 64-bit ECMA CRC
 *  05.04.01  2017-06-08  Gmi     ESCAN00095459  Compiler warning: Crc.c: constant out of range
 *                                -              Inclusion of Std_Types.h was moved to Crc.h
 **********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/
#if !defined CRC_H
# define CRC_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

# include "Std_Types.h"
# include "Crc_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# define CRC_VENDOR_ID                     (30u)
# define CRC_MODULE_ID                     (201u)
# define CRC_INSTANCE_ID                   (0u)

# define CRC_AR_RELEASE_MAJOR_VERSION      (4u)
# define CRC_AR_RELEASE_MINOR_VERSION      (0u)
# define CRC_AR_RELEASE_REVISON_VERSION    (3u)

# define CRC_SW_MAJOR_VERSION              (5u)
# define CRC_SW_MINOR_VERSION              (4u)
# define CRC_SW_PATCH_VERSION              (1u)


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
# define CRC_START_SEC_CONST_8
# include "MemMap.h"          /* PRQA S 5087 */ /* MD_MSR_19.1 */

typedef P2CONST(uint8, AUTOMATIC, CRC_APPL_DATA) Crc_DataRefType;

# define CRC_STOP_SEC_CONST_8
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define CRC_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 *  Crc_CalculateCRC8()
 *********************************************************************************************************************/
/*!
 * \brief      Calculates 8-bit CRC value of passed data
 * \details    Calculates 8-bit CRC value of data pointed to by Crc_DataPtr over a number of data bytes (Crc_Length)
 *             based on the SAE-J1850 CRC8 Standard.
 * \param[in]  Crc_DataPtr - Pointer to start address of data block to be calculated.
 * \param[in]  Crc_Length - Length of data block to be calculated in bytes
 * \param[in]  Crc_StartValue8 - Start value when the algorithm starts.
 * \param[in]  Crc_IsFirstCall - TRUE: First call in a sequence; start from initial value; ignore Crc_StartValue8
 *                               FALSE: Subsequent call in a call sequence; Crc_StartValue8 has to be return value of previous call
 * \return     Calculated CRC8 value
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-858
 * \trace SPEC-50218, SPEC-50213, SPEC-24712
 * \trace DSGN-Crc22763
 */
FUNC(uint8, CRC_CODE) Crc_CalculateCRC8 (Crc_DataRefType Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8, boolean Crc_IsFirstCall);


/**********************************************************************************************************************
 *  Crc_CalculateCRC8H2F()
 *********************************************************************************************************************/
/*!
 * \brief      Calculates 8-bit CRC value of passed data
 * \details    Calculates 8-bit CRC value of data pointed to by Crc_DataPtr over a number of data bytes (Crc_Length)
 *             based on the polynomial 0x2F.
 * \param[in]  Crc_DataPtr - Pointer to start address of data block to be calculated.
 * \param[in]  Crc_Length - Length of data block to be calculated in bytes
 * \param[in]  Crc_StartValue8H2F - Start value when the algorithm starts.
 * \param[in]  Crc_IsFirstCall - TRUE: First call in a sequence; start from initial value; ignore Crc_StartValue8H2F
 *                               FALSE: Subsequent call in a call sequence; Crc_StartValue8H2F has to be return value of previous call
 * \return     Calculated CRC8H2F value
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-859
 * \trace SPEC-24705, SPEC-50217, SPEC-24706
 * \trace DSGN-Crc22764
 */
FUNC(uint8, CRC_CODE) Crc_CalculateCRC8H2F (Crc_DataRefType Crc_DataPtr, uint32 Crc_Length, uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall);


/**********************************************************************************************************************
 *  Crc_CalculateCRC16()
 *********************************************************************************************************************/
/*!
 * \brief      Calculates 16-bit CRC value of passed data
 * \details    Calculates 16-bit CRC value of data pointed to by Crc_DataPtr over a number of data bytes (Crc_Length)
 *             based on the CCITT CRC16 Standard.
 * \param[in]  Crc_DataPtr - Pointer to start address of data block to be calculated.
 * \param[in]  Crc_Length - Length of data block to be calculated in bytes
 * \param[in]  Crc_StartValue16 - Start value when the algorithm starts.
 * \param[in]  Crc_IsFirstCall - TRUE: First call in a sequence; start from initial value; ignore Crc_StartValue16
 *                               FALSE: Subsequent call in a call sequence; Crc_StartValue16 has to be return value of previous call
 * \return     Calculated CRC16 value
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-860
 * \trace SPEC-24717, SPEC-50220, SPEC-24714
 * \trace DSGN-Crc22767
 */
FUNC(uint16, CRC_CODE) Crc_CalculateCRC16 (Crc_DataRefType Crc_DataPtr, uint32 Crc_Length, uint16 Crc_StartValue16, boolean Crc_IsFirstCall);


/**********************************************************************************************************************
 *  Crc_CalculateCRC32()
 *********************************************************************************************************************/
/*!
 * \brief      Calculates 32-bit CRC value of passed data
 * \details    Calculates 32-bit CRC value of data pointed to by Crc_DataPtr over a number of data bytes (Crc_Length)
 *             based on the IEEE-802.3 CRC32 Standard.
 * \param[in]  Crc_DataPtr - Pointer to start address of data block to be calculated.
 * \param[in]  Crc_Length - Length of data block to be calculated in bytes
 * \param[in]  Crc_StartValue32 - Start value when the algorithm starts.
 * \param[in]  Crc_IsFirstCall - TRUE: First call in a sequence; start from initial value; ignore Crc_StartValue32
 *                               FALSE: Subsequent call in a call sequence; Crc_StartValue32 has to be return value of previous call
 * \return     Calculated CRC32 value
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-861
 * \trace SPEC-24704, SPEC-50224, SPEC-24699
 * \trace DSGN-Crc22766
 */
FUNC(uint32, CRC_CODE) Crc_CalculateCRC32 (Crc_DataRefType Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall);


/**********************************************************************************************************************
 *  Crc_CalculateCRC32P4()
 *********************************************************************************************************************/
/*!
 * \brief      Calculates 32-bit CRC P4 value of passed data
 * \details    Calculates 32-bit CRC value of data pointed to by Crc_DataPtr over a number of data bytes (Crc_Length)
 *             based on E2E Profile 4.
 * \param[in]  Crc_DataPtr - Pointer to start address of data block to be calculated.
 * \param[in]  Crc_Length - Length of data block to be calculated in bytes
 * \param[in]  Crc_StartValue32 - Start value when the algorithm starts.
 * \param[in]  Crc_IsFirstCall - TRUE: First call in a sequence; start from initial value; ignore Crc_StartValue32P4
 *                               FALSE: Subsequent call in a call sequence; Crc_StartValue32P4 has to be return value of previous call
 * \return     Calculated CRC32 P4 value
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-862
 * \trace DSGN-Crc22765
 */
FUNC(uint32, CRC_CODE) Crc_CalculateCRC32P4 (Crc_DataRefType Crc_DataPtr, uint32 Crc_Length, uint32 Crc_StartValue32, boolean Crc_IsFirstCall);


/**********************************************************************************************************************
 *  Crc_CalculateCRC64()
 *********************************************************************************************************************/
/*!
 * \brief      Calculates 64-bit CRC value of passed data
 * \details    Calculates 64-bit CRC value of data pointed to by Crc_DataPtr over a number of data bytes (Crc_Length)
 *             based on ECMA Standard.
 * \param[in]  Crc_DataPtr - Pointer to start address of data block to be calculated.
 * \param[in]  Crc_Length - Length of data block to be calculated in bytes
 * \param[in]  Crc_StartValue64 - Start value when the algorithm starts.
 * \param[in]  Crc_IsFirstCall - TRUE: First call in a sequence; start from initial value; ignore Crc_StartValue64
 *                               FALSE: Subsequent call in a call sequence; Crc_StartValue64 has to be return value of previous call
 * \return     Calculated CRC64 value
 * \pre        -
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-117997
 * \trace DSGN-Crc22770
 */
FUNC(uint64, CRC_CODE) Crc_CalculateCRC64 (Crc_DataRefType Crc_DataPtr, uint32 Crc_Length, uint64 Crc_StartValue64, boolean Crc_IsFirstCall);


# if (CRC_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Crc_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * \brief      Retrieves the version information of the Crc module.
 * \details    Stores version information, i.e. Module Id, Vendor Id, Vendor specific version numbers to structure pointed by Versioninfo
 * \param[in]  Versioninfo
 * \pre        GetVersionInfo API is enabled via pre-compile configuration
 * \context    TASK
 * \reentrant  TRUE
 * \synchronous TRUE
 * \trace CREQ-863
 * \trace SPEC-50219, SPEC-24718
 * \trace DSGN-Crc22768
 */
FUNC(void, CRC_CODE) Crc_GetVersionInfo (P2VAR(Std_VersionInfoType, AUTOMATIC, CRC_APPL_DATA) Versioninfo);
# endif


# define CRC_STOP_SEC_CODE
# include "MemMap.h"

#endif  /* CRC_H */

/**********************************************************************************************************************
 *  END OF FILE: Crc.h
 *********************************************************************************************************************/
