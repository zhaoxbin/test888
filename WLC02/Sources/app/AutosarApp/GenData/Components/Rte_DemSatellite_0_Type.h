/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Rte_DemSatellite_0_Type.h
 *           Config:  WLC.dpa
 *      ECU-Project:  WLC
 *
 *        Generator:  MICROSAR RTE Generator Version 4.20.0
 *                    RTE Core Version 1.20.0
 *          License:  CBD1900162
 *
 *      Description:  Application types header file for SW-C <DemSatellite_0>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_DEMSATELLITE_0_TYPE_H
# define _RTE_DEMSATELLITE_0_TYPE_H

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

# include "Rte_Type.h"

# ifndef RTE_CORE

/**********************************************************************************************************************
 * Range, Invalidation, Enumeration and Bit Field Definitions
 *********************************************************************************************************************/

#  ifndef DEM_DTC_FORMAT_OBD
#   define DEM_DTC_FORMAT_OBD (0U)
#  endif

#  ifndef DEM_DTC_FORMAT_UDS
#   define DEM_DTC_FORMAT_UDS (1U)
#  endif

#  ifndef DEM_DTC_FORMAT_J1939
#   define DEM_DTC_FORMAT_J1939 (2U)
#  endif

#  ifndef DEM_DTC_KIND_ALL_DTCS
#   define DEM_DTC_KIND_ALL_DTCS (1U)
#  endif

#  ifndef DEM_DTC_KIND_EMISSION_REL_DTCS
#   define DEM_DTC_KIND_EMISSION_REL_DTCS (2U)
#  endif

#  ifndef DEM_SEVERITY_NO_SEVERITY
#   define DEM_SEVERITY_NO_SEVERITY (0U)
#  endif

#  ifndef DTC_NO_SEVERITY_BflMask
#   define DTC_NO_SEVERITY_BflMask 255U
#  endif

#  ifndef DTC_NO_SEVERITY_BflPn
#   define DTC_NO_SEVERITY_BflPn 0U
#  endif

#  ifndef DTC_NO_SEVERITY_BflLn
#   define DTC_NO_SEVERITY_BflLn 8U
#  endif

#  ifndef DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS
#   define DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS (1U)
#  endif

#  ifndef DTC_CLASS_BflMask
#   define DTC_CLASS_BflMask 31U
#  endif

#  ifndef DTC_CLASS_BflPn
#   define DTC_CLASS_BflPn 0U
#  endif

#  ifndef DTC_CLASS_BflLn
#   define DTC_CLASS_BflLn 5U
#  endif

#  ifndef DEM_SEVERITY_WWHOBD_CLASS_A
#   define DEM_SEVERITY_WWHOBD_CLASS_A (2U)
#  endif

#  ifndef DTC_CLASS_BflMask
#   define DTC_CLASS_BflMask 31U
#  endif

#  ifndef DTC_CLASS_BflPn
#   define DTC_CLASS_BflPn 0U
#  endif

#  ifndef DTC_CLASS_BflLn
#   define DTC_CLASS_BflLn 5U
#  endif

#  ifndef DEM_SEVERITY_WWHOBD_CLASS_B1
#   define DEM_SEVERITY_WWHOBD_CLASS_B1 (4U)
#  endif

#  ifndef DTC_CLASS_BflMask
#   define DTC_CLASS_BflMask 31U
#  endif

#  ifndef DTC_CLASS_BflPn
#   define DTC_CLASS_BflPn 0U
#  endif

#  ifndef DTC_CLASS_BflLn
#   define DTC_CLASS_BflLn 5U
#  endif

#  ifndef DEM_SEVERITY_WWHOBD_CLASS_B2
#   define DEM_SEVERITY_WWHOBD_CLASS_B2 (8U)
#  endif

#  ifndef DTC_CLASS_BflMask
#   define DTC_CLASS_BflMask 31U
#  endif

#  ifndef DTC_CLASS_BflPn
#   define DTC_CLASS_BflPn 0U
#  endif

#  ifndef DTC_CLASS_BflLn
#   define DTC_CLASS_BflLn 5U
#  endif

#  ifndef DEM_SEVERITY_WWHOBD_CLASS_C
#   define DEM_SEVERITY_WWHOBD_CLASS_C (16U)
#  endif

#  ifndef DTC_CLASS_BflMask
#   define DTC_CLASS_BflMask 31U
#  endif

#  ifndef DTC_CLASS_BflPn
#   define DTC_CLASS_BflPn 0U
#  endif

#  ifndef DTC_CLASS_BflLn
#   define DTC_CLASS_BflLn 5U
#  endif

#  ifndef DEM_SEVERITY_MAINTENANCE_ONLY
#   define DEM_SEVERITY_MAINTENANCE_ONLY (32U)
#  endif

#  ifndef DTC_SEVERITY_BflMask
#   define DTC_SEVERITY_BflMask 224U
#  endif

#  ifndef DTC_SEVERITY_BflPn
#   define DTC_SEVERITY_BflPn 5U
#  endif

#  ifndef DTC_SEVERITY_BflLn
#   define DTC_SEVERITY_BflLn 3U
#  endif

#  ifndef DEM_SEVERITY_CHECK_AT_NEXT_HALT
#   define DEM_SEVERITY_CHECK_AT_NEXT_HALT (64U)
#  endif

#  ifndef DTC_SEVERITY_BflMask
#   define DTC_SEVERITY_BflMask 224U
#  endif

#  ifndef DTC_SEVERITY_BflPn
#   define DTC_SEVERITY_BflPn 5U
#  endif

#  ifndef DTC_SEVERITY_BflLn
#   define DTC_SEVERITY_BflLn 3U
#  endif

#  ifndef DEM_SEVERITY_CHECK_IMMEDIATELY
#   define DEM_SEVERITY_CHECK_IMMEDIATELY (128U)
#  endif

#  ifndef DTC_SEVERITY_BflMask
#   define DTC_SEVERITY_BflMask 224U
#  endif

#  ifndef DTC_SEVERITY_BflPn
#   define DTC_SEVERITY_BflPn 5U
#  endif

#  ifndef DTC_SEVERITY_BflLn
#   define DTC_SEVERITY_BflLn 3U
#  endif

#  ifndef DEM_DTR_CTL_NORMAL
#   define DEM_DTR_CTL_NORMAL (0U)
#  endif

#  ifndef DEM_DTR_CTL_NO_MAX
#   define DEM_DTR_CTL_NO_MAX (1U)
#  endif

#  ifndef DEM_DTR_CTL_NO_MIN
#   define DEM_DTR_CTL_NO_MIN (2U)
#  endif

#  ifndef DEM_DTR_CTL_RESET
#   define DEM_DTR_CTL_RESET (3U)
#  endif

#  ifndef DEM_DTR_CTL_INVISIBLE
#   define DEM_DTR_CTL_INVISIBLE (4U)
#  endif

#  ifndef DEM_DEBOUNCE_STATUS_FREEZE
#   define DEM_DEBOUNCE_STATUS_FREEZE (0U)
#  endif

#  ifndef DEM_DEBOUNCE_STATUS_RESET
#   define DEM_DEBOUNCE_STATUS_RESET (1U)
#  endif

#  ifndef DEM_TEMPORARILY_DEFECTIVE
#   define DEM_TEMPORARILY_DEFECTIVE (1U)
#  endif

#  ifndef DEM_TEMPORARILY_DEFECTIVE_BflMask
#   define DEM_TEMPORARILY_DEFECTIVE_BflMask 1U
#  endif

#  ifndef DEM_TEMPORARILY_DEFECTIVE_BflPn
#   define DEM_TEMPORARILY_DEFECTIVE_BflPn 0U
#  endif

#  ifndef DEM_TEMPORARILY_DEFECTIVE_BflLn
#   define DEM_TEMPORARILY_DEFECTIVE_BflLn 1U
#  endif

#  ifndef DEM_FINALLY_DEFECTIVE
#   define DEM_FINALLY_DEFECTIVE (2U)
#  endif

#  ifndef DEM_FINALLY_DEFECTIVE_BflMask
#   define DEM_FINALLY_DEFECTIVE_BflMask 2U
#  endif

#  ifndef DEM_FINALLY_DEFECTIVE_BflPn
#   define DEM_FINALLY_DEFECTIVE_BflPn 1U
#  endif

#  ifndef DEM_FINALLY_DEFECTIVE_BflLn
#   define DEM_FINALLY_DEFECTIVE_BflLn 1U
#  endif

#  ifndef DEM_TEMPORARILY_HEALED
#   define DEM_TEMPORARILY_HEALED (4U)
#  endif

#  ifndef DEM_TEMPORARILY_HEALED_BflMask
#   define DEM_TEMPORARILY_HEALED_BflMask 4U
#  endif

#  ifndef DEM_TEMPORARILY_HEALED_BflPn
#   define DEM_TEMPORARILY_HEALED_BflPn 2U
#  endif

#  ifndef DEM_TEMPORARILY_HEALED_BflLn
#   define DEM_TEMPORARILY_HEALED_BflLn 1U
#  endif

#  ifndef DEM_TEST_COMPLETE
#   define DEM_TEST_COMPLETE (8U)
#  endif

#  ifndef DEM_TEST_COMPLETE_BflMask
#   define DEM_TEST_COMPLETE_BflMask 8U
#  endif

#  ifndef DEM_TEST_COMPLETE_BflPn
#   define DEM_TEST_COMPLETE_BflPn 3U
#  endif

#  ifndef DEM_TEST_COMPLETE_BflLn
#   define DEM_TEST_COMPLETE_BflLn 1U
#  endif

#  ifndef DEM_DTR_UPDATE
#   define DEM_DTR_UPDATE (16U)
#  endif

#  ifndef DEM_DTR_UPDATE_BflMask
#   define DEM_DTR_UPDATE_BflMask 16U
#  endif

#  ifndef DEM_DTR_UPDATE_BflPn
#   define DEM_DTR_UPDATE_BflPn 4U
#  endif

#  ifndef DEM_DTR_UPDATE_BflLn
#   define DEM_DTR_UPDATE_BflLn 1U
#  endif

#  ifndef DEM_EVENT_STATUS_PASSED
#   define DEM_EVENT_STATUS_PASSED (0U)
#  endif

#  ifndef DEM_EVENT_STATUS_FAILED
#   define DEM_EVENT_STATUS_FAILED (1U)
#  endif

#  ifndef DEM_EVENT_STATUS_PREPASSED
#   define DEM_EVENT_STATUS_PREPASSED (2U)
#  endif

#  ifndef DEM_EVENT_STATUS_PREFAILED
#   define DEM_EVENT_STATUS_PREFAILED (3U)
#  endif

#  ifndef DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED
#   define DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED (4U)
#  endif

#  ifndef DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED
#   define DEM_EVENT_STATUS_PASSED_CONDITIONS_NOT_FULFILLED (5U)
#  endif

#  ifndef DEM_EVENT_STATUS_FAILED_CONDITIONS_NOT_FULFILLED
#   define DEM_EVENT_STATUS_FAILED_CONDITIONS_NOT_FULFILLED (6U)
#  endif

#  ifndef DEM_EVENT_STATUS_PREPASSED_CONDITIONS_NOT_FULFILLED
#   define DEM_EVENT_STATUS_PREPASSED_CONDITIONS_NOT_FULFILLED (7U)
#  endif

#  ifndef DEM_EVENT_STATUS_PREFAILED_CONDITIONS_NOT_FULFILLED
#   define DEM_EVENT_STATUS_PREFAILED_CONDITIONS_NOT_FULFILLED (8U)
#  endif

#  ifndef DEM_INDICATOR_OFF
#   define DEM_INDICATOR_OFF (0U)
#  endif

#  ifndef DEM_INDICATOR_CONTINUOUS
#   define DEM_INDICATOR_CONTINUOUS (1U)
#  endif

#  ifndef DEM_INDICATOR_BLINKING
#   define DEM_INDICATOR_BLINKING (2U)
#  endif

#  ifndef DEM_INDICATOR_BLINK_CONT
#   define DEM_INDICATOR_BLINK_CONT (3U)
#  endif

#  ifndef DEM_INDICATOR_SLOW_FLASH
#   define DEM_INDICATOR_SLOW_FLASH (4U)
#  endif

#  ifndef DEM_INDICATOR_FAST_FLASH
#   define DEM_INDICATOR_FAST_FLASH (5U)
#  endif

#  ifndef DEM_INDICATOR_ON_DEMAND
#   define DEM_INDICATOR_ON_DEMAND (6U)
#  endif

#  ifndef DEM_INDICATOR_SHORT
#   define DEM_INDICATOR_SHORT (7U)
#  endif

#  ifndef DEM_INIT_MONITOR_CLEAR
#   define DEM_INIT_MONITOR_CLEAR (1U)
#  endif

#  ifndef DEM_INIT_MONITOR_RESTART
#   define DEM_INIT_MONITOR_RESTART (2U)
#  endif

#  ifndef DEM_INIT_MONITOR_REENABLED
#   define DEM_INIT_MONITOR_REENABLED (3U)
#  endif

#  ifndef DEM_INIT_MONITOR_STORAGE_REENABLED
#   define DEM_INIT_MONITOR_STORAGE_REENABLED (4U)
#  endif

#  ifndef DEM_IUMPR_GENERAL_DENOMINATOR
#   define DEM_IUMPR_GENERAL_DENOMINATOR (1U)
#  endif

#  ifndef DEM_IUMPR_DEN_COND_COLDSTART
#   define DEM_IUMPR_DEN_COND_COLDSTART (2U)
#  endif

#  ifndef DEM_IUMPR_DEN_COND_EVAP
#   define DEM_IUMPR_DEN_COND_EVAP (3U)
#  endif

#  ifndef DEM_IUMPR_DEN_COND_500MI
#   define DEM_IUMPR_DEN_COND_500MI (4U)
#  endif

#  ifndef DEM_IUMPR_DEN_STATUS_NOT_REACHED
#   define DEM_IUMPR_DEN_STATUS_NOT_REACHED (0U)
#  endif

#  ifndef DEM_IUMPR_DEN_STATUS_REACHED
#   define DEM_IUMPR_DEN_STATUS_REACHED (1U)
#  endif

#  ifndef DEM_IUMPR_DEN_STATUS_INHIBITED
#   define DEM_IUMPR_DEN_STATUS_INHIBITED (2U)
#  endif

#  ifndef DEM_IUMPR_BOOSTPRS
#   define DEM_IUMPR_BOOSTPRS (0U)
#  endif

#  ifndef DEM_IUMPR_CAT1
#   define DEM_IUMPR_CAT1 (1U)
#  endif

#  ifndef DEM_IUMPR_CAT2
#   define DEM_IUMPR_CAT2 (2U)
#  endif

#  ifndef DEM_IUMPR_EGR
#   define DEM_IUMPR_EGR (3U)
#  endif

#  ifndef DEM_IUMPR_EGSENSOR
#   define DEM_IUMPR_EGSENSOR (4U)
#  endif

#  ifndef DEM_IUMPR_EVAP
#   define DEM_IUMPR_EVAP (5U)
#  endif

#  ifndef DEM_IUMPR_NMHCCAT
#   define DEM_IUMPR_NMHCCAT (6U)
#  endif

#  ifndef DEM_IUMPR_NOXADSORB
#   define DEM_IUMPR_NOXADSORB (7U)
#  endif

#  ifndef DEM_IUMPR_NOXCAT
#   define DEM_IUMPR_NOXCAT (8U)
#  endif

#  ifndef DEM_IUMPR_OXS1
#   define DEM_IUMPR_OXS1 (9U)
#  endif

#  ifndef DEM_IUMPR_OXS2
#   define DEM_IUMPR_OXS2 (10U)
#  endif

#  ifndef DEM_IUMPR_PMFILTER
#   define DEM_IUMPR_PMFILTER (11U)
#  endif

#  ifndef DEM_IUMPR_PRIVATE
#   define DEM_IUMPR_PRIVATE (12U)
#  endif

#  ifndef DEM_IUMPR_SAIR
#   define DEM_IUMPR_SAIR (13U)
#  endif

#  ifndef DEM_IUMPR_SECOXS1
#   define DEM_IUMPR_SECOXS1 (14U)
#  endif

#  ifndef DEM_IUMPR_SECOXS2
#   define DEM_IUMPR_SECOXS2 (15U)
#  endif

#  ifndef DEM_IUMPR_FLSYS
#   define DEM_IUMPR_FLSYS (16U)
#  endif

#  ifndef DEM_IUMPR_AFRI1
#   define DEM_IUMPR_AFRI1 (17U)
#  endif

#  ifndef DEM_IUMPR_AFRI2
#   define DEM_IUMPR_AFRI2 (18U)
#  endif

#  ifndef DEM_IUMPR_PF1
#   define DEM_IUMPR_PF1 (19U)
#  endif

#  ifndef DEM_IUMPR_PF2
#   define DEM_IUMPR_PF2 (20U)
#  endif

#  ifndef DEM_IUMPR_ALLGROUPS
#   define DEM_IUMPR_ALLGROUPS (255U)
#  endif

#  ifndef DEM_MONITOR_STATUS_TF
#   define DEM_MONITOR_STATUS_TF (1U)
#  endif

#  ifndef DEM_MONITOR_STATUS_TF_BflMask
#   define DEM_MONITOR_STATUS_TF_BflMask 1U
#  endif

#  ifndef DEM_MONITOR_STATUS_TF_BflPn
#   define DEM_MONITOR_STATUS_TF_BflPn 0U
#  endif

#  ifndef DEM_MONITOR_STATUS_TF_BflLn
#   define DEM_MONITOR_STATUS_TF_BflLn 1U
#  endif

#  ifndef DEM_MONITOR_STATUS_TNCTOC
#   define DEM_MONITOR_STATUS_TNCTOC (2U)
#  endif

#  ifndef DEM_MONITOR_STATUS_TNCTOC_BflMask
#   define DEM_MONITOR_STATUS_TNCTOC_BflMask 2U
#  endif

#  ifndef DEM_MONITOR_STATUS_TNCTOC_BflPn
#   define DEM_MONITOR_STATUS_TNCTOC_BflPn 1U
#  endif

#  ifndef DEM_MONITOR_STATUS_TNCTOC_BflLn
#   define DEM_MONITOR_STATUS_TNCTOC_BflLn 1U
#  endif

#  ifndef DEM_CYCLE_STATE_START
#   define DEM_CYCLE_STATE_START (0U)
#  endif

#  ifndef DEM_CYCLE_STATE_END
#   define DEM_CYCLE_STATE_END (1U)
#  endif

#  ifndef DEM_UDS_STATUS_TF
#   define DEM_UDS_STATUS_TF (1U)
#  endif

#  ifndef DEM_UDS_STATUS_TF_BflMask
#   define DEM_UDS_STATUS_TF_BflMask 1U
#  endif

#  ifndef DEM_UDS_STATUS_TF_BflPn
#   define DEM_UDS_STATUS_TF_BflPn 0U
#  endif

#  ifndef DEM_UDS_STATUS_TF_BflLn
#   define DEM_UDS_STATUS_TF_BflLn 1U
#  endif

#  ifndef DEM_UDS_STATUS_TFTOC
#   define DEM_UDS_STATUS_TFTOC (2U)
#  endif

#  ifndef DEM_UDS_STATUS_TFTOC_BflMask
#   define DEM_UDS_STATUS_TFTOC_BflMask 2U
#  endif

#  ifndef DEM_UDS_STATUS_TFTOC_BflPn
#   define DEM_UDS_STATUS_TFTOC_BflPn 1U
#  endif

#  ifndef DEM_UDS_STATUS_TFTOC_BflLn
#   define DEM_UDS_STATUS_TFTOC_BflLn 1U
#  endif

#  ifndef DEM_UDS_STATUS_PDTC
#   define DEM_UDS_STATUS_PDTC (4U)
#  endif

#  ifndef DEM_UDS_STATUS_PDTC_BflMask
#   define DEM_UDS_STATUS_PDTC_BflMask 4U
#  endif

#  ifndef DEM_UDS_STATUS_PDTC_BflPn
#   define DEM_UDS_STATUS_PDTC_BflPn 2U
#  endif

#  ifndef DEM_UDS_STATUS_PDTC_BflLn
#   define DEM_UDS_STATUS_PDTC_BflLn 1U
#  endif

#  ifndef DEM_UDS_STATUS_CDTC
#   define DEM_UDS_STATUS_CDTC (8U)
#  endif

#  ifndef DEM_UDS_STATUS_CDTC_BflMask
#   define DEM_UDS_STATUS_CDTC_BflMask 8U
#  endif

#  ifndef DEM_UDS_STATUS_CDTC_BflPn
#   define DEM_UDS_STATUS_CDTC_BflPn 3U
#  endif

#  ifndef DEM_UDS_STATUS_CDTC_BflLn
#   define DEM_UDS_STATUS_CDTC_BflLn 1U
#  endif

#  ifndef DEM_UDS_STATUS_TNCSLC
#   define DEM_UDS_STATUS_TNCSLC (16U)
#  endif

#  ifndef DEM_UDS_STATUS_TNCSLC_BflMask
#   define DEM_UDS_STATUS_TNCSLC_BflMask 16U
#  endif

#  ifndef DEM_UDS_STATUS_TNCSLC_BflPn
#   define DEM_UDS_STATUS_TNCSLC_BflPn 4U
#  endif

#  ifndef DEM_UDS_STATUS_TNCSLC_BflLn
#   define DEM_UDS_STATUS_TNCSLC_BflLn 1U
#  endif

#  ifndef DEM_UDS_STATUS_TFSLC
#   define DEM_UDS_STATUS_TFSLC (32U)
#  endif

#  ifndef DEM_UDS_STATUS_TFSLC_BflMask
#   define DEM_UDS_STATUS_TFSLC_BflMask 32U
#  endif

#  ifndef DEM_UDS_STATUS_TFSLC_BflPn
#   define DEM_UDS_STATUS_TFSLC_BflPn 5U
#  endif

#  ifndef DEM_UDS_STATUS_TFSLC_BflLn
#   define DEM_UDS_STATUS_TFSLC_BflLn 1U
#  endif

#  ifndef DEM_UDS_STATUS_TNCTOC
#   define DEM_UDS_STATUS_TNCTOC (64U)
#  endif

#  ifndef DEM_UDS_STATUS_TNCTOC_BflMask
#   define DEM_UDS_STATUS_TNCTOC_BflMask 64U
#  endif

#  ifndef DEM_UDS_STATUS_TNCTOC_BflPn
#   define DEM_UDS_STATUS_TNCTOC_BflPn 6U
#  endif

#  ifndef DEM_UDS_STATUS_TNCTOC_BflLn
#   define DEM_UDS_STATUS_TNCTOC_BflLn 1U
#  endif

#  ifndef DEM_UDS_STATUS_WIR
#   define DEM_UDS_STATUS_WIR (128U)
#  endif

#  ifndef DEM_UDS_STATUS_WIR_BflMask
#   define DEM_UDS_STATUS_WIR_BflMask 128U
#  endif

#  ifndef DEM_UDS_STATUS_WIR_BflPn
#   define DEM_UDS_STATUS_WIR_BflPn 7U
#  endif

#  ifndef DEM_UDS_STATUS_WIR_BflLn
#   define DEM_UDS_STATUS_WIR_BflLn 1U
#  endif

# endif /* RTE_CORE */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* _RTE_DEMSATELLITE_0_TYPE_H */
