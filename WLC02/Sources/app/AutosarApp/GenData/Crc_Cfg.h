/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Crc
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Crc_Cfg.h
 *   Generation Time: 2020-02-08 12:42:12
 *           Project: WLC - Version 1.0
 *          Delivery: CBD1900162_D00
 *      Tool Version: DaVinci Configurator (beta) 5.19.29
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 ! BETA VERSION                                                                                                       !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 ! This version of DaVinci Configurator Pro and/or the related Basic Software Package is BETA software.               !
 ! BETA Software is basically operable, but not sufficiently tested, verified and/or qualified for use in series      !
 ! production and/or in vehicles operating on public or non-public roads.                                             !
 ! In particular, without limitation, BETA Software may cause unpredictable ECU behavior, may not provide all         !
 ! functions necessary for use in series production and/or may not comply with quality requirements which are         !
 ! necessary according to the state of the art. BETA Software must not be used in series production.                  !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**********************************************************************************************************************/

/**** Protection against multiple inclusion **************************************************************************/
#if !defined (CRC_CFG_H)
# define CRC_CFG_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* This is not the sub-package version but a compatibility version, which will only be updated if a change in the 
   generator (i.e. generated files) affects the implementation sub-package */
# define CRC_CFG_MAJOR_VERSION	(3u) 
# define CRC_CFG_MINOR_VERSION	(1u) 

/***** Supported CRC Calculation modes *******************************************************************************/

/* CRC 8 */
# define CRC_8_RUNTIME           (0u)
# define CRC_8_TABLE             (1u)
# define CRC_8_HARDWARE          (2u)

/* CRC 8H2F */
# define CRC_8H2F_RUNTIME        (0u)
# define CRC_8H2F_TABLE          (1u)
# define CRC_8H2F_HARDWARE       (2u)

/* CRC 16 */
# define CRC_16_RUNTIME          (0u)
# define CRC_16_TABLE            (1u)
# define CRC_16_HARDWARE         (2u)

/* CRC 32 */
# define CRC_32_RUNTIME          (0u)
# define CRC_32_TABLE            (1u)
# define CRC_32_HARDWARE         (2u)

/* CRC 32P4 */
# define CRC_32P4_RUNTIME        (0u)
# define CRC_32P4_TABLE          (1u)
# define CRC_32P4_HARDWARE       (2u)

/* CRC 64 */
# define CRC_64_RUNTIME          (0u)
# define CRC_64_TABLE            (1u)
# define CRC_64_HARDWARE         (2u)
        
/***** CRC Calculation configuration *********************************************************************************/

# define CRC_8_MODE              (CRC_8_TABLE)
# define CRC_8H2F_MODE           (CRC_8H2F_TABLE)
# define CRC_16_MODE             (CRC_16_RUNTIME)
# define CRC_32_MODE             (CRC_32_RUNTIME)
# define CRC_32P4_MODE           (CRC_32P4_RUNTIME)
# define CRC_64_MODE             (CRC_64_RUNTIME)


/***** Optional API function *****************************************************************************************/

# define CRC_VERSION_INFO_API    (STD_ON)



#endif  /* CRC_CFG_H */

/**********************************************************************************************************************
  END OF FILE: Crc_Cfg.h
**********************************************************************************************************************/
