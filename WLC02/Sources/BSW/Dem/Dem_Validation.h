
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
 *         File:  Dem_Validation.h
 *      Project:  MICROSAR Diagnostic Event Manager (Dem)
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Configuration sanity checks. Please note, the validation performed in this file is intentionally
 *                incomplete and restricted to basic verifications.  Not all combinations of options are supported
 *                even if the compilation of this file is successful. This is intended behavior.
 *                Exhaustive verifications are performed by the generation tool before configuration files are
 *                created.
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

#if !defined (DEM_VALIDATION_H)                                                                                                  /* COV_MSR_HEADERGUARD TX */
#define DEM_VALIDATION_H

/* ********************************************************************************************************************
 *  VERIFY BASIC MACROS EXIST
 *********************************************************************************************************************/
#if !defined (STD_ON) || (STD_ON != 1)
# error "STD_ON is not correctly defined"
#endif

#if !defined (STD_OFF) || (STD_OFF != 0)
# error "STD_OFF is not correctly defined"
#endif

/**********************************************************************************************************************
 *  VERIFY SENSIBLE COMBINATION OF CONFIGURATION SWITCHES
 *********************************************************************************************************************/
#if !defined DEM_DUMMY_STATEMENT
# error "DEM_DUMMY_STATEMENT not defined"
#endif

/* Unsupported Features */
#if !defined PRQA_SIZE_T && !defined _lint && !defined _REVIEW_HELPER && !defined _PB_GENERATOR /* COV_DEM_UNSUPPORTED_TESTED_FEATURE TF xf xf xf xf tf */

#if (DEM_CFG_SUPPORT_J1939 == STD_ON) && (DEM_CFG_SUPPORT_MIL == STD_ON)
# error "DEM_CFG_SUPPORT_J1939 == STD_ON && DEM_CFG_SUPPORT_MIL == STD_ON is not supported"
#endif

#if (DEM_CFG_SUPPORT_J1939 == STD_ON) && (DEM_CFG_STORAGE_AT_CONFIRMED != STD_ON)
# error "DEM_CFG_SUPPORT_J1939 == STD_ON && DEM_CFG_STORAGE_AT_CONFIRMED != STD_ON is not supported"
#endif

#if (DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_STORAGE_AT_FAILED != STD_ON)
# error "OBDII requires Storage Trigger Failed"
#endif

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_STORAGE_AT_FAILED != STD_ON)
# error "WWH-OBD requires Storage Trigger Failed"
#endif
#endif

#if (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON) && (DEM_CFG_STORAGE_AT_FAILED == STD_OFF)
# error "Global snapshot records can only be used with event memory storage trigger 'Failed'"
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON) && (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
#error "Simultaneous aging for all DTCs can only be used in Non-WWHOBD configurations"
#endif

#if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON) && (DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON)
#error "Simultaneous aging for all DTCs can only be used configurations with CDTC processing set as DEM_CFG_PROCESS_CDTC_ALL_DTC"
#endif

#if !( /* Aging Type 1 */ \
      ( (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_ON) && (DEM_CFG_AGING_START_TESTS_TFTOC != STD_ON) && (DEM_CFG_AGING_NEXT_TESTS_TNCTOC != STD_ON) \
         && (DEM_CFG_AGING_NEXT_TESTS_TFTOC != STD_ON) && (DEM_CFG_AGING_00_START_TRIGGER_PASSED == STD_ON) && (DEM_CFG_AGING_00_START_TESTS_TFTOC != STD_ON) ) \
        /* Aging Type 2 */  \
    ||( (DEM_CFG_AGING_START_TRIGGER_PASSED != STD_ON) && (DEM_CFG_AGING_START_TESTS_TFTOC == STD_ON) && (DEM_CFG_AGING_NEXT_TESTS_TNCTOC != STD_ON) \
         && (DEM_CFG_AGING_NEXT_TESTS_TFTOC != STD_ON) && (DEM_CFG_AGING_00_START_TRIGGER_PASSED != STD_ON) && (DEM_CFG_AGING_00_START_TESTS_TFTOC == STD_ON) ) \
        /* Aging Type 3 */  \
    ||( (DEM_CFG_AGING_START_TRIGGER_PASSED != STD_ON) && (DEM_CFG_AGING_START_TESTS_TFTOC == STD_ON) && (DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON) \
         && (DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON) && (DEM_CFG_AGING_00_START_TRIGGER_PASSED != STD_ON) && (DEM_CFG_AGING_00_START_TESTS_TFTOC == STD_ON) ) \
        /* Aging Type 4 */  \
    ||( (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_ON) && (DEM_CFG_AGING_START_TESTS_TFTOC != STD_ON) && (DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON) \
        && (DEM_CFG_AGING_NEXT_TESTS_TFTOC != STD_ON) && (DEM_CFG_AGING_00_START_TRIGGER_PASSED == STD_ON) && (DEM_CFG_AGING_00_START_TESTS_TFTOC != STD_ON) ) \
        /* Aging Type 5 */  \
    ||( (DEM_CFG_AGING_START_TRIGGER_PASSED != STD_ON) && (DEM_CFG_AGING_START_TESTS_TFTOC == STD_ON) && (DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON) \
         && (DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON) && (DEM_CFG_AGING_00_START_TRIGGER_PASSED == STD_ON) && (DEM_CFG_AGING_00_START_TESTS_TFTOC == STD_ON) ) \
        /* Aging Type 6 */  \
    ||( (DEM_CFG_AGING_START_TRIGGER_PASSED == STD_ON) && (DEM_CFG_AGING_START_TESTS_TFTOC == STD_ON) && (DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_ON) \
         && (DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON) && (DEM_CFG_AGING_00_START_TRIGGER_PASSED == STD_ON) && (DEM_CFG_AGING_00_START_TESTS_TFTOC != STD_ON) ) \
    )
# error "Invalid combination of switches determining the Aging Type"
#endif

#if ((DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL != STD_ON) && (DEM_CFG_SUPPORT_DEBOUNCE_COUNTER != STD_ON) \
     && (DEM_CFG_SUPPORT_DEBOUNCE_TIME != STD_ON))
# error "Minimum of one debouncing algorithm must be enabled"
#endif

#if ((DEM_CFG_VARIANT_POSTBUILD_SELECTABLE != STD_ON) && (DEM_CFG_ISCONST_AVAILABLEINVARIANT != STD_ON))
#error "For Non Postbuild Selectable Configuration, DEM_CFG_ISCONST_AVAILABLEINVARIANT must be enabled"
#endif

#if ((DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON) && (DEM_CFG_SUPPORT_MULTITRIP != STD_ON))
#error "For Postbuild Loadable Configuration, Multitrip must be enabled"
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_MULTITRIP != STD_ON))
#error "For OBD-II ECUs, Multitrip must be enabled"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_TESTFAILED_STORAGE != STD_ON))
#error "For WWHOBD ECUs, event storage on test failed report must be enabled"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_MULTITRIP != STD_ON))
#error "For OBD ECUs, Multitrip must always be enabled"
#endif

#if ((DEM_CFG_DISPLACEMENT_FALLBACK_OLDEST == STD_ON) && (DEM_CFG_SUPPORT_DISPLACEMENT != STD_ON))
# error "DEM_CFG_SUPPORT_DISPLACEMENT cannot be disabled when DEM_CFG_DISPLACEMENT_FALLBACK_OLDEST is enabled"
#endif

#if ((DEM_CFG_SUPPORT_DEBOUNCE_COUNTER != STD_ON) && (DEM_CFG_SUPPORT_DEBOUNCE_NV == STD_ON))
# error "DEM_CFG_SUPPORT_DEBOUNCE_NV cannot be enabled when DEM_CFG_SUPPORT_DEBOUNCE_COUNTER is disabled"
#endif

#if (DEM_CFG_AGING_AFTER_HEALING == STD_ON) && (DEM_CFG_AGING_AFTER_HEALING_ALL_DTC == STD_ON)
# error "DEM_CFG_AGING_AFTER_HEALING == STD_ON and DEM_CFG_AGING_AFTER_HEALING_ALL_DTC == STD_ON is not supported"
#endif

#if (DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON) && (DEM_CFG_PROCESS_OCCTR_CONFIRMED != STD_ON)
# error "DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON and DEM_CFG_PROCESS_OCCTR_CONFIRMED != STD_ON is not supported"
#endif

#if (DEM_CFG_SUPPORT_NVM_IMMEDIATE != STD_ON) && (DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON)
# error "DEM_CFG_SUPPORT_NVM_IMMEDIATE != STD_ON and DEM_CFG_SUPPORT_NVM_WRITELIMIT == STD_ON is not supported"
#endif

#if (DEM_CFG_SUPPORT_OVFLIND_API != STD_ON) && (DEM_CFG_DATA_OVFLIND == STD_ON)
# error "DEM_CFG_SUPPORT_OVFLIND_API != STD_ON and DEM_CFG_DATA_OVFLIND == STD_ON is not supported"
#endif

#if (DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL != STD_ON) && (DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL_GETFDC == STD_ON)
# error "DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL != STD_ON and DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL_GETFDC == STD_ON is not supported"
#endif

#if (DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL == STD_ON) && (DEM_CFG_DATA_CURRENT_FDC == STD_ON) && (DEM_CFG_SUPPORT_DEBOUNCE_MONITORINTERNAL_GETFDC == STD_OFF)
# error "A GetFdc callback has to be available, if monitor internal debouncing and data element 'Current FDC' are used"
#endif

#if (DEM_CFG_SUPPORT_EVENTAVAILABLE != STD_ON) && (DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON)
# error "DEM_CFG_SUPPORT_EVENTAVAILABLE != STD_ON and DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON is not supported"
#endif

#if (DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON)
# error "DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME and DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME cannot be STD_ON at the same time"
#endif

#if (((DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON) || (DEM_CFG_SUPPORT_PENDING_UPDATE_FREEZE_FRAME == STD_ON)) \
     && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON))
# error "DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME or DEM_CFG_SUPPORT_PENDING_UPDATE_FREEZE_FRAME cannot be STD_ON \
         when DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME is STD_ON"
#endif

#if (DEM_CFG_SUPPORT_SRECS_CONFIGURED != STD_ON) && (DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON)
# error "DEM_CFG_SUPPORT_SRECS_CONFIGURED != STD_ON and DEM_CFG_SUPPORT_TRIGGER_FDC_FIRST_IN_CYCLE == STD_ON is not supported"
#endif

#if (DEM_CFG_CLEAR_NV_START_RESPONSE == STD_ON)
# error " DEM_CFG_CLEAR_NV_START_RESPONSE == STD_ON is not supported"
#endif

#if ( ((DEM_CFG_SUPPORT_AWL == STD_ON) || (DEM_CFG_SUPPORT_MIL == STD_ON) || (DEM_CFG_SUPPORT_PL == STD_ON) || (DEM_CFG_SUPPORT_RSL == STD_ON) \
      || (DEM_CFG_SUPPORT_USER_INDICATORS == STD_ON)) && (DEM_CFG_SUPPORT_INDICATORS != STD_ON) )
# error "DEM_CFG_SUPPORT_INDICATORS cannot be disabled when indicators are configured"
#endif

#if ( ((DEM_CFG_CLEAR_IMMEDIATE_RESPONSE + DEM_CFG_CLEAR_NV_END_RESPONSE) > STD_ON) \
      || (DEM_CFG_CLEAR_IMMEDIATE_RESPONSE + DEM_CFG_CLEAR_NV_END_RESPONSE) == STD_OFF)
# error "Exactly one of the settings DEM_CFG_CLEAR_IMMEDIATE_RESPONSE, DEM_CFG_CLEAR_NV_END_RESPONSE must be enabled"
#endif

#if ( ((DEM_CFG_PROCESS_OCCTR_CONFIRMED + DEM_CFG_PROCESS_OCCTR_TESTFAILED) > STD_ON) \
      || (DEM_CFG_PROCESS_OCCTR_CONFIRMED + DEM_CFG_PROCESS_OCCTR_TESTFAILED) == STD_OFF)
# error "Exactly one of the settings DEM_CFG_PROCESS_OCCTR_CONFIRMED, DEM_CFG_PROCESS_OCCTR_TESTFAILED must be enabled"
#endif

#if ( ((DEM_CFG_RESET_DEBOUNCE_ON_DISABLE_ENABLE_CONDITIONS + DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS) > STD_ON) \
      || (DEM_CFG_RESET_DEBOUNCE_ON_DISABLE_ENABLE_CONDITIONS + DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS) == STD_OFF)
# error "Exactly one of the settings DEM_CFG_RESET_DEBOUNCE_ON_DISABLE_ENABLE_CONDITIONS, DEM_CFG_RESET_DEBOUNCE_ON_ENABLE_ENABLE_CONDITIONS must be enabled"
#endif

#if ((DEM_CFG_SUPPORT_DISPLACEMENT != STD_ON) && ((DEM_CFG_DISPLACEMENT_PREFER_PASSIVE == STD_ON) || (DEM_CFG_DISPLACEMENT_TNCTOC_IS_PASSIVE == STD_ON)))
# error "DEM_CFG_DISPLACEMENT_PREFER_PASSIVE and DEM_CFG_DISPLACEMENT_TNCTOC_IS_PASSIVE cannot be enabled, when DEM_CFG_SUPPORT_DISPLACEMENT is disabled"
#endif

#if ((DEM_CFG_SUPPORT_DISPLACEMENT == STD_ON) && (DEM_CFG_DISPLACEMENT_PREFER_PASSIVE != STD_ON) && (DEM_CFG_DISPLACEMENT_TNCTOC_IS_PASSIVE == STD_ON))
# error "DEM_CFG_DISPLACEMENT_PREFER_PASSIVE cannot be disabled, when DEM_CFG_SUPPORT_DISPLACEMENT and DEM_CFG_DISPLACEMENT_TNCTOC_IS_PASSIVE are enabled"
#endif

#if (((DEM_CFG_SUPPORT_SRECS_CALCULATED + DEM_CFG_SUPPORT_SRECS_CONFIGURED) > STD_ON) \
    || (DEM_CFG_SUPPORT_SRECS_CALCULATED + DEM_CFG_SUPPORT_SRECS_CONFIGURED) == STD_OFF)
# error "Exactly one of the settings DEM_CFG_SUPPORT_SRECS_CONFIGURED, DEM_CFG_SUPPORT_SRECS_CALCULATED must be enabled"
#endif

#if ((DEM_CFG_SUPPORT_OPCYCLE_STORAGE != STD_ON) && (DEM_CFG_SUPPORT_OPCYCLE_AUTOMATIC_END == STD_ON))
# error "(DEM_CFG_SUPPORT_OPCYCLE_STORAGE != STD_ON) && (DEM_CFG_SUPPORT_OPCYCLE_AUTOMATIC_END == STD_ON) is not\
  a valid combination: without nonvolatile storage of cycle state there is no way NOT to end a cycle."
#endif

#if (DEM_CFG_PROCESS_PDTC_ALL_DTC == DEM_CFG_PROCESS_PDTC_STOREDONLY)
# error "Exactly one of the settings DEM_CFG_PROCESS_PDTC_ALL_DTC, DEM_CFG_PROCESS_PDTC_STOREDONLY must be enabled"
#endif

#if (DEM_CFG_PROCESS_CDTC_ALL_DTC == DEM_CFG_PROCESS_CDTC_STOREDONLY)
# error "Exactly one of the settings DEM_CFG_PROCESS_CDTC_ALL_DTC, DEM_CFG_PROCESS_CDTC_STOREDONLY must be enabled"
#endif

#if (((DEM_CFG_PROCESS_TFSLC_ALL_DTC + DEM_CFG_PROCESS_TFSLC_STOREDONLY + DEM_CFG_PROCESS_TFSLC_CLEARONLY) > STD_ON) \
    || ((DEM_CFG_PROCESS_TFSLC_ALL_DTC + DEM_CFG_PROCESS_TFSLC_STOREDONLY + DEM_CFG_PROCESS_TFSLC_CLEARONLY) == STD_OFF))
# error "Exactly one of the settings DEM_CFG_PROCESS_TFSLC_ALL_DTC, DEM_CFG_PROCESS_TFSLC_STOREDONLY must be enabled"
#endif

#if (DEM_CFG_PROCESS_WIR_ALL_DTC == DEM_CFG_PROCESS_WIR_STOREDONLY)
# error "Exactly one of the settings DEM_CFG_PROCESS_WIR_ALL_DTC, DEM_CFG_PROCESS_WIR_STOREDONLY must be enabled"
#endif

#if ((DEM_CFG_SUPPORT_EVENTAVAILABLE_NV == STD_ON) && (DEM_CFG_SUPPORT_EVENTAVAILABLE_DEFAULT == STD_ON))
# error "Event availability must use exactly one of initialization with default value, or initialization from NV"
#endif

#if ((DEM_CFG_SUPPORT_J1939 == STD_ON) && (DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON))
# error "DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON is not valid for non-OBD ECUs"
#endif

#if ((DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_NOTIFY_J1939DTC_STATUS == STD_ON))
# error "DEM_CFG_NOTIFY_J1939DTC_STATUS cannot be supported without J1939 support"
#endif

#if ((DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_HAS_J1939_NODE == STD_ON))
# error "J1939 nodes cannot be supported without J1939 support"
#endif

#if ((DEM_CFG_SUPPORT_J1939 == STD_ON) && (DEM_CFG_HAS_J1939_NODE != STD_ON))
# error "DEM_CFG_SUPPORT_J1939 cannot be on without J1939 node"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_PID91 == STD_ON))
# error "DEM_CFG_SUPPORT_WWHOBD == STD_OFF && DEM_CFG_SUPPORT_PID91 == STD_ON is not a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON))
# error "DEM_CFG_SUPPORT_OBDII == STD_OFF && DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON is not a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON))
# error "DEM_CFG_SUPPORT_WWHOBD == STD_ON && DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_ON is not a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON))
# error "DEM_CFG_SUPPORT_OBDII == STD_OFF && DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON is not a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON))
# error "DEM_CFG_SUPPORT_WWHOBD == STD_ON && DEM_CFG_SUPPORT_PENDING_DISPLACE_FREEZE_FRAME == STD_ON is not a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_OBDII != STD_ON) && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON))
# error "(DEM_CFG_SUPPORT_OBDII != STD_ON) && (DEM_CFG_SUPPORT_OBDII_FREEZEFRAME_IN_SVC19 == STD_ON) is not\
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_OBDII != STD_ON) && (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON))
# error "(DEM_CFG_SUPPORT_OBDII != STD_ON) && (DEM_CFG_SUPPORT_OBD_HIDE_OCCURRENCES == STD_ON) is not\
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_OBDII != STD_ON) && (DEM_CFG_SUPPORT_PERMANENT_CONDITION_DCY == STD_ON))
# error "(DEM_CFG_SUPPORT_OBDII != STD_ON) && (DEM_CFG_SUPPORT_PERMANENT_CONDITION_DCY == STD_ON) is not\
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_OBDII != STD_ON) && (DEM_CFG_SUPPORT_PERMANENT_MANDATORY_PFC == STD_ON))
# error "(DEM_CFG_SUPPORT_OBDII != STD_ON) && (DEM_CFG_SUPPORT_PERMANENT_MANDATORY_PFC == STD_ON) is not\
  a valid combination"
#endif

#if (DEM_CFG_SUPPORT_OBDII != DEM_CFG_SUPPORT_FREEZEFRAME)
# error " DEM_CFG_SUPPORT_OBDII and DEM_CFG_SUPPORT_FREEZEFRAME cannot be independently present"
#endif

#if ((DEM_CFG_SUPPORT_OBDII != STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON))
# error "DEM_CFG_SUPPORT_OBDII != STD_ON and DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON is not valid for OBDII ECUs"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON))
# error " (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) is not valid for WWH-OBD ECUs"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_OFF))
# error "DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_OFF is not valid for WWH-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_IUMPR == STD_ON))
# error "DEM_CFG_SUPPORT_IUMPR == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_MIL == STD_ON))
# error "DEM_CFG_SUPPORT_MIL == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON))
# error "DEM_CFG_SUPPORT_SIMILAR_CONDITIONS == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_DTR == STD_ON))
# error "DEM_CFG_SUPPORT_DTR == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_ON))
# error "DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_PENDING_UPDATE_FREEZE_FRAME == STD_ON))
# error "DEM_CFG_SUPPORT_PENDING_UPDATE_FREEZE_FRAME == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON))
# error "DEM_CFG_SUPPORT_MAJOR_MONITORS == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_CLEAR_PDTC_NO_PFC == STD_ON))
# error "DEM_CFG_SUPPORT_CLEAR_PDTC_NO_PFC == STD_ON is not valid for non-OBDII ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_RESTART_DCY_ON_CLEAR_DTC == STD_ON))
# error "DEM_CFG_SUPPORT_RESTART_DCY_ON_CLEAR_DTC == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON))
# error "DEM_CFG_SUPPORT_DELAY_WUC_TO_DCY == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_PID01 == STD_ON))
# error "DEM_CFG_SUPPORT_PID01 == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_PID1C == STD_ON))
# error "DEM_CFG_SUPPORT_PID1C == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_PID21 == STD_ON))
# error "DEM_CFG_SUPPORT_PID21 == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_PID30 == STD_ON))
# error "DEM_CFG_SUPPORT_PID30 == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_PID31 == STD_ON))
# error "DEM_CFG_SUPPORT_PID31 == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_PID41 == STD_ON))
# error "DEM_CFG_SUPPORT_PID41 == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_PID4D == STD_ON))
# error "DEM_CFG_SUPPORT_PID4D == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_SUPPORT_PID4E == STD_ON))
# error "DEM_CFG_SUPPORT_PID4E == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_PROCESS_PID41_COMPREHENSIVE_COMPLETE == STD_ON))
# error "DEM_CFG_PROCESS_PID41_COMPREHENSIVE_COMPLETE == STD_ON is not valid for non-OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_WWHOBD == STD_OFF) && (DEM_CFG_SUPPORT_OBDII == STD_OFF)) && (DEM_CFG_REPORT_BLINKING_MIL_AS_ACTIVE == STD_OFF))
# error "DEM_CFG_REPORT_BLINKING_MIL_AS_ACTIVE == STD_OFF is not valid for non-OBD ECUs"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON))
# error "DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON is not valid for WWH-OBD ECUs"
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_NVM_IMMEDIATE != STD_ON))
# error "(DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_NVM_IMMEDIATE != STD_ON) is not\
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_NVM_IMMEDIATE != STD_ON))
# error "(DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_NVM_IMMEDIATE != STD_ON) is not\
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_MIL != STD_ON))
# error "(DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_MIL != STD_ON) is not\
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_MIL != STD_ON))
# error "(DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_MIL != STD_ON) is not\
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC != STD_ON))
# error "(DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_PROCESS_CDTC_ALL_DTC != STD_ON) is not\
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PERMANENT == STD_ON))
# error "(DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_PERMANENT == STD_ON) is not\
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_CLEAR_TESTFAILED_ON_OPCYCLE == STD_ON))
# error "(DEM_CFG_SUPPORT_WWHOBD == STD_ON) && (DEM_CFG_SUPPORT_CLEAR_TESTFAILED_ON_OPCYCLE == STD_ON) is not\
  a valid combination"
#endif

#if (((DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)) && (DEM_CFG_SUPPORT_INDICATORS != STD_ON))
# error "((DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)) && (DEM_CFG_SUPPORT_INDICATORS != STD_ON) is not\
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_OFF))
# error "(DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME == STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_VISIBLE_FREEZE_FRAME == STD_OFF) is not \
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENT != STD_ON))
# error "(DEM_CFG_SUPPORT_OBDII == STD_ON) && (DEM_CFG_SUPPORT_PERMANENT != STD_ON) is not\
  a valid combination"
#endif

#if ((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_PERMANENT == STD_ON))
# error "DEM_CFG_SUPPORT_PERMANENT == STD_ON is not supported for non-OBD use cases"
#endif

#if ((DEM_CFG_SUPPORT_OBDII != STD_ON) && (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON))
# error "(DEM_CFG_SUPPORT_OBDII != STD_ON) && (DEM_CFG_SUPPORT_PERMANENTDTC_ACTIVATION_DISTANCE == STD_ON) is not\
  a valid combination"
#endif

#if (((DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)) && (DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME != STD_ON) && (DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME != STD_ON))
# error "DEM_CFG_SUPPORT_PENDING_STORAGE_FREEZE_FRAME != STD_ON && DEM_CFG_SUPPORT_CONFIRMED_STORAGE_FREEZE_FRAME != STD_ON is not valid for OBD ECUs"
#endif

#if (((DEM_CFG_SUPPORT_OBDII == STD_ON) || (DEM_CFG_SUPPORT_WWHOBD == STD_ON)) && (DEM_FEATURE_NEED_MULTIHEAL != STD_ON))
# error "OBD relevant events need healing cycle counter threshold 3"
#endif

#if (((DEM_CFG_SUPPORT_OBDII == STD_OFF) && (DEM_CFG_SUPPORT_WWHOBD == STD_OFF)) && (DEM_CFG_SUPPORT_MIL_GROUP == STD_ON))
# error "MIL Groups cannot be configured for non OBD ECUs"
#endif

#if (DEM_CFG_SUPPORT_DEBOUNCE_TIME != STD_ON) && ((DEM_CFG_SUPPORT_DEBOUNCE_TIME_HR == STD_ON) || (DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR == STD_ON))
# error "DEM_CFG_SUPPORT_DEBOUNCE_TIME != STD_ON && DEM_CFG_SUPPORT_DEBOUNCE_TIME_HR == STD_ON || DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR == STD_ON\
  is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_DEBOUNCE_TIME == STD_ON) && ((DEM_CFG_SUPPORT_DEBOUNCE_TIME_HR != STD_ON) && (DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR != STD_ON))
# error "DEM_CFG_SUPPORT_DEBOUNCE_TIME == STD_ON && DEM_CFG_SUPPORT_DEBOUNCE_TIME_HR != STD_ON && DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR != STD_ON\
  is not a valid combination"
#endif

#if (((DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON) || (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON) \
     || (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON) || (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)) \
     && (DEM_CFG_SUPPORT_SRECS != STD_ON))
# error "DEM_CFG_SUPPORT_SRECS != STD_ON and time series snapshots is not a valid combination"
#endif

#if (((DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON) || (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON) \
     || (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON) || (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON)) \
     && (DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON))
# error "DEM_CFG_SUPPORT_GLOBAL_SRECS == STD_ON and time series snapshots supported is not a valid combination"
#endif

#if (((DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON) || (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON)) \
     && ((DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL != STD_ON) && (DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL != STD_ON)))
# error "At least one Normal Time Series Snapshot Record must be configured"
#endif

#if (DEM_CFG_STORAGE_AT_CONFIRMED != STD_ON) && (DEM_CFG_STORAGE_AT_FAILED != STD_ON) && (DEM_CFG_STORAGE_AT_FDC != STD_ON) && (DEM_CFG_STORAGE_AT_PENDING != STD_ON)
# error "At least one DEM_CFG_STORAGE_AT_X must be defined to STD_ON"
#endif

#if ((DEM_CFG_STORAGE_AT_CONFIRMED + DEM_CFG_STORAGE_AT_FAILED + DEM_CFG_STORAGE_AT_FDC + DEM_CFG_STORAGE_AT_PENDING) > STD_ON)
# error "At most one DEM_CFG_STORAGE_AT_X must be defined to STD_ON"
#endif

#if (DEM_CFG_STORAGE_AT_FAILED == STD_ON) && (DEM_CFG_STORAGE_AT_FDC == STD_ON)
# error "At most one DEM_CFG_STORAGE_AT_X must be defined to STD_ON"
#endif

#if (DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_SUPPORT_AWL == STD_ON)
# error "DEM_CFG_SUPPORT_J1939 != STD_ON && DEM_CFG_SUPPORT_AWL == STD_ON is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_SUPPORT_PL == STD_ON)
# error "DEM_CFG_SUPPORT_J1939 != STD_ON && DEM_CFG_SUPPORT_PL == STD_ON is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_SUPPORT_RSL == STD_ON)
# error "DEM_CFG_SUPPORT_J1939 != STD_ON && DEM_CFG_SUPPORT_RSL == STD_ON is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON)
# error "DEM_CFG_SUPPORT_J1939 != STD_ON && DEM_CFG_SUPPORT_J1939_CLEAR_DTC == STD_ON is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON)
# error "DEM_CFG_SUPPORT_J1939 != STD_ON && DEM_CFG_SUPPORT_J1939_DM31 == STD_ON is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON)
# error "DEM_CFG_SUPPORT_J1939 != STD_ON && DEM_CFG_SUPPORT_J1939_EXPANDED_FREEZEFRAME == STD_ON is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON)
# error "DEM_CFG_SUPPORT_J1939 != STD_ON && DEM_CFG_SUPPORT_J1939_FREEZEFRAME == STD_ON is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON)
# error "DEM_CFG_SUPPORT_J1939 != STD_ON && DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
# error "DEM_CFG_SUPPORT_J1939 != STD_ON && DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_J1939 != STD_ON) && (DEM_CFG_NOTIFY_J1939DCM == STD_ON)
# error "DEM_CFG_SUPPORT_J1939 != STD_ON && DEM_CFG_NOTIFY_J1939DCM == STD_ON is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_OBDII + DEM_CFG_SUPPORT_WWHOBD + DEM_CFG_SUPPORT_J1939 > STD_ON)
# error "Exactly one of the settings DEM_CFG_SUPPORT_OBDII, DEM_CFG_SUPPORT_WWHOBD and DEM_CFG_SUPPORT_J1939 must be enabled"
#endif

#if (DEM_CFG_STORAGE_AT_FDC == STD_ON) && (DEM_CFG_SUPPORT_RETRY_STORAGE == STD_ON)
# error "The combination of DemStorageTrigger=DEM_STORAGE_ON_FDC_THRESHOLD and DemRetryStorageSupport==True is not supported."
#endif

#if ((DEM_CFG_SUPPORT_ERECS != STD_ON) && (DEM_CFG_SUPPORT_USER_ERECS == STD_ON))
# error "DEM_CFG_SUPPORT_ERECS != STD_ON && DEM_CFG_SUPPORT_USER_ERECS == STD_ON is not a valid combination"
#endif

#if ((DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON) && (DEM_CFG_PROCESS_PDTC_STOREDONLY == STD_ON))
# error "DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON && DEM_CFG_PROCESS_PDTC_STOREDONLY == STD_ON is not a valid combination"
#endif

#if ((DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON) && (DEM_CFG_PROCESS_TFSLC_STOREDONLY == STD_ON))
# error "DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON && DEM_CFG_PROCESS_TFSLC_STOREDONLY == STD_ON is not a valid combination"
#endif

#if (DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON)
# if (DEM_CFG_GLOBAL_COMBINED_GROUP_COUNT == 0)
#  error "DEM_CFG_SUPPORT_TYPE1_COMBINATION == STD_ON without combined events is not supported"
# endif
#endif

#if ((DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON) && (DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_OFF))
# error "(DEM_CFG_AGING_NEXT_TESTS_TFTOC == STD_ON) && (DEM_CFG_AGING_NEXT_TESTS_TNCTOC == STD_OFF) is not a valid combination"
#endif

#if ((DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON) && (DEM_CFG_PROCESS_PDTC_STOREDONLY == STD_ON))
# error "DEM_CFG_PROCESS_CDTC_ALL_DTC == STD_ON && DEM_CFG_PROCESS_PDTC_STOREDONLY == STD_ON is not a valid combination"
#endif

#if ((DEM_CFG_PROCESS_WIR_ALL_DTC == STD_ON) && (DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON))
# error "DEM_CFG_PROCESS_WIR_ALL_DTC == STD_ON && DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON is not a valid combination"
#endif

# if ( (DEM_CFG_CLEAR_SINGLE_DTCS != STD_ON) && (DEM_CFG_CLEAR_GROUP_DTCS != STD_ON) && (DEM_CFG_CLEAR_OBDII_GROUP_DTCS != STD_ON) \
       && (DEM_CFG_CLEAR_ALL_DTCS != STD_ON) && (DEM_CFG_CLEAR_WWHOBD_GROUP_DTCS != STD_ON) )
# error "The scope of Dem_ClearDTC API must be configured"
# endif

# if (((DEM_CFG_CLEAR_SINGLE_DTCS == STD_ON) || (DEM_CFG_CLEAR_GROUP_DTCS == STD_ON) || (DEM_CFG_CLEAR_OBDII_GROUP_DTCS == STD_ON) \
      || (DEM_CFG_CLEAR_WWHOBD_GROUP_DTCS == STD_ON)) && (DEM_CFG_CLEAR_ALL_DTCS != STD_ON))
# error "Clearing of ALL DTCs cannot be disabled when clearing of Single/ Group DTCs are supported"
# endif


#  if ( (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_FAST == STD_ON) || (DEM_CFG_SUPPORT_TIME_SERIES_FUTURE_NORMAL == STD_ON) \
         || (DEM_CFG_SUPPORT_TIME_SERIES_PAST_FAST == STD_ON) ||(DEM_CFG_SUPPORT_TIME_SERIES_PAST_NORMAL == STD_ON))
#  error "Time series snapshots are not supported for a non TMC configuration"
#  endif

# if (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON)
# error "DAG Standard Environmental Data is not licensed"
# endif
# if (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
# error "DAG Extended Environmental Data is not licensed"
# endif
# if (DEM_CFG_USE_OHDS == STD_ON)
# error "OHDS support is not licensed"
# endif

#if ((DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) && (DEM_CFG_SUPPORT_ERECS != STD_ON))
# error "DAG Standard Environmental Data cannot be used without extended data records"
#endif

#if ((DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON) && (DEM_CFG_SUPPORT_ERECS != STD_ON))
# error "DAG Standard Environmental Data cannot be used without extended data records"
#endif


#if ((DEM_CFG_USE_INIT_POINTER == STD_OFF) && (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON))
# error "In postbuild loadable configurations an init pointer has to be used"
#endif

#if ((DEM_CFG_USE_INIT_POINTER == STD_ON) && (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_OFF) && (DEM_CFG_VARIANT_POSTBUILD_SELECTABLE == STD_OFF))
# error "An init pointer may only be used in postbuild loadable or postbuild selectable configurations"
#endif

#if ((DEM_CFG_SUPPORT_DEBOUNCE_TIME == STD_ON) && (DEM_CFG_VARIANT_POSTBUILD_LOADABLE == STD_ON) \
&& ((DEM_CFG_SUPPORT_DEBOUNCE_TIME_LR == STD_OFF) || (DEM_CFG_SUPPORT_DEBOUNCE_TIME_HR == STD_OFF)))
# error "In postbuild loadable configurations both high and low resolution time based debouncing have to activated"
#endif

/* ********************************************************************************************************************
 *  UNSUPPORTED ASR FEATURES
 *********************************************************************************************************************/
#if (DEM_CFG_SUPPORT_MIRROR == STD_ON)
# error "DEM_CFG_SUPPORT_MIRROR == STD_ON is not yet supported"
#endif

#if (DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON)
# error "DEM_CFG_SUPPORT_TYPE2_COMBINATION == STD_ON is not yet supported"
#endif

#if (DEM_CFG_CAPTURE_EXTDATA_TESTFAILED == STD_ON)
# error "DEM_CFG_CAPTURE_EXTDATA_TESTFAILED == STD_ON is not yet supported"
#endif

#if (DEM_CFG_CAPTURE_FREEZEF_TESTFAILED == STD_ON)
# error "DEM_CFG_CAPTURE_FREEZEF_TESTFAILED == STD_ON is not yet supported"
#endif

#if (DEM_CFG_CLEAR_REINIT_BEFORE_RESPONSE != STD_ON)
# error "DEM_CFG_CLEAR_REINIT_BEFORE_RESPONSE == STD_OFF is not supported"
#endif

#if ( (DEM_CFG_CLEARDTCINDEXOFCLIENTTABLE != STD_ON) \
   || (DEM_CFG_CLIENTTABLE != STD_ON) \
   || (DEM_CFG_DTCSELECTORTABLE != STD_ON) \
   || (DEM_CFG_FILTERINFOTABLE != STD_ON) \
   || (DEM_CFG_READOUTBUFFERINDEXOFCLIENTTABLE != STD_ON) \
   || (DEM_CFG_FREEZEFRAMEITERATORTABLE != STD_ON) )
# error "If at least one client exist this tables are present. Configurations without a client are not supported"
#endif
#endif  /* DEM_VALIDATION_H */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Validation.h
 *********************************************************************************************************************/
