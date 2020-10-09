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
 */
/*! \addtogroup Dem_Esm
 *  \{
 *  \file       Dem_Esm_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    
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

#if !defined (DEM_ESM_TYPES_H)
#define DEM_ESM_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/*!
 * \defgroup  Dem_Esm_PermanentDtcStatus  Macros encoding status values for permanent DTCs
 * Macros encoding status values for permanent DTCs. Low byte is used for the state and the high byte is used for the visibility and the clear conditions
 * \{
 */
# define DEM_ESM_PERMANENT_STATES                (0x03U)  /*!< range of valid permanent states */
# define DEM_ESM_PERMANENT_STATEMASK             (0xfcU)  /*!< inverted DEM_ESM_PERMANENT_STATES */

# define DEM_ESM_PERMANENT_NONE                  (0x00U)  /*!< Permanent entry not used */
# define DEM_ESM_PERMANENT_ACTIVE                (0x01U)  /*!< Permanent entry active */
# define DEM_ESM_PERMANENT_PASSIVE               (0x02U)  /*!< Permanent entry not active */

# define DEM_ESM_PERMANENT_VISIBLE               (0x80U)  /*!< Permanent entry visible in mode 0xa */
# define DEM_ESM_PERMANENT_VISIBLEMASK           (0x7fU)  /*!< Mask to reset DEM_ESM_PERMANENT_VISIBLE */
# define DEM_ESM_PERMANENT_CONDITION_TESTED      (0x40U)  /*!< Permanent entry DTC tested this DCY */
# define DEM_ESM_PERMANENT_CONDITION_TESTEDMASK  (0xbfU)  /*!< Mask to reset DEM_ESM_PERMANENT_CONDITION_TESTED */
# define DEM_ESM_PERMANENT_CONDITION_PFC         (0x20U)  /*!< Permanent entry PFC condition fulfilled */
# define DEM_ESM_PERMANENT_CONDITION_PFCMASK     (0xdfU)  /*!< Mask to reset DEM_ESM_PERMANENT_CONDITION_PFC */
# define DEM_ESM_PERMANENT_CONDITION_DCY         (0x10U)  /*!< Permanent entry DCY qualified */
# define DEM_ESM_PERMANENT_CONDITION_DCYMASK     (0xefU)  /*!< Mask to reset DEM_ESM_PERMANENT_CONDITION_DCY */
/*!
 * \}
 */
#endif /* (DEM_CFG_SUPPORT_OBDII == STD_ON) */

#if (DEM_CFG_SUPPORT_WWHOBD == STD_ON)
/*!
 * \defgroup  Dem_Esm_WwhObdClass  Macros encoding WWHOBD DTC Classes
 * Macros encoding WWHOBD DTC Classes
 * \{
 */
# define DEM_ESM_WWHOBD_NUMBER_DTCCLASS          5U  /*!< Number of WWH-OBD DTC classes */

# define DEM_ESM_WWHOBD_DTCCLASS_NO              0U  /*!< No WWH-OBD DTC class */
# define DEM_ESM_WWHOBD_DTCCLASS_C               1U  /*!< WWH-OBD DTC class C */
# define DEM_ESM_WWHOBD_DTCCLASS_B2              2U  /*!< WWH-OBD DTC class B2 */
# define DEM_ESM_WWHOBD_DTCCLASS_B1              3U  /*!< WWH-OBD DTC class B1 */
# define DEM_ESM_WWHOBD_DTCCLASS_A               4U  /*!< WWH-OBD DTC class A */
/*!
 * \}
 */

/*! Aging timer 200 hour threshold value */
#define DEM_ESM_AGINGTIME_200h                   (0x00002ee0UL)
#endif

#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/*!
 * \defgroup  Dem_Esm_IumprGeneralDenominatorState  Macros encoding General Denominator states
 * Macros encoding General Denominator states
 * \{
 */
# define DEM_ESM_IUMPR_GENDEN_INCREMENTED                    ((uint8)(0x01U))  /*!< General denominator incremented this DCY */
# define DEM_ESM_IUMPR_GENDEN_INCREMENTED_MASK               ((uint8)(0xfeU))  /*!< Mask to reset 'General denominator incremented' */
# define DEM_ESM_IUMPR_GENDEN_CONDITIONS_REACHED             ((uint8)(0x02U))  /*!< General denominator conditions reached */
# define DEM_ESM_IUMPR_GENDEN_CONDITIONS_REACHED_MASK        ((uint8)(0xfdU))  /*!< Mask to reset 'General denominator conditions reached' */
# define DEM_ESM_IUMPR_GENDEN_CONDITIONS_FAILED              ((uint8)(0x04U))  /*!< General denominator is failed/blocked this DCY */
# define DEM_ESM_IUMPR_GENDEN_CONDITIONS_FAILED_MASK         ((uint8)(0xfbU))  /*!< Mask to reset 'General denominator failed/blocked this DCY' */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Esm_IumprHybridIgnitionCounterState  Macros encoding hybrid ignition cycle counter states
 * Macros encoding hybrid ignition counter states
 * \{
 */
# define DEM_ESM_IUMPR_IGN_CYC_HYBRID_INCREMENTED            ((uint8)(0x01U))  /*!< Hybrid ignition cycle counter incremented this DCY */
# define DEM_ESM_IUMPR_IGN_CYC_HYBRID_INCREMENTED_MASK       ((uint8)(0xfeU))  /*!< Reset mask hybrid ignition cycle counter incremented this DCY */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Esm_IumprGlobalNumeratorsState  Macros encoding Iumpr numerator states
 * Macros encoding Iumpr numerator locked states
 * \{
 */
# define DEM_ESM_IUMPR_NUMERATORS_LOCKED                     ((uint8)(0x01U))  /*!< Ratio numerators locked globally */
# define DEM_ESM_IUMPR_NUMERATORS_LOCKED_MASK                ((uint8)(0xfeU))  /*!< Reset mask for Ratio numerators locked globally */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Esm_IumprDenominatorStatus  Macros encoding ratio specific denominator states
 * Macros encoding ratio specific denominator states
 * \{
 */
# define DEM_ESM_IUMPR_DEN_INCREMENTED                       ((uint8)(0x01u))  /*!< Denominator incremented this DCY */
# define DEM_ESM_IUMPR_DEN_INCREMENTED_MASK                  ((uint8)(0xfeU))  /*!< Reset mask for denominator incremented this DCY */
# define DEM_ESM_IUMPR_DEN_LOCKED                            ((uint8)(0x02U))  /*!< Denominator status 'locked this DCY' */
# define DEM_ESM_IUMPR_DEN_LOCKED_MASK                       ((uint8)(0xfdU))  /*!< Reset mask for denominator status 'locked this DCY' */
# define DEM_ESM_IUMPR_DEN_CONDITIONS_REACHED                ((uint8)(0x04U))  /*!< Ratio specific denominator conditions reached this DCY */
# define DEM_ESM_IUMPR_DEN_CONDITIONS_REACHED_MASK           ((uint8)(0xfbU))  /*!< Reset mask for ratio specific denominator conditions reached this DCY */
# define DEM_ESM_IUMPR_FID_PENDING                           ((uint8)(0x08U))  /*!< Ratio blocked by pending FID */
# define DEM_ESM_IUMPR_FID_PENDING_MASK                      ((uint8)(0xf7U))  /*!< Reset mask for ratio blocked by pending FID */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Esm_IumprNumeratorStatus  Macros encoding ratio specific numerator states
 * Macros encoding ratio specific numerator states
 * \{
 */
# define DEM_ESM_IUMPR_NUM_INCREMENTED                       ((uint8)(0x10U))  /*!< Numerator incremented this DCY */
# define DEM_ESM_IUMPR_NUM_INCREMENTED_MASK                  ((uint8)(0xefU))  /*!< Reset mask for numerator incremented this DCY */
# define DEM_ESM_IUMPR_NUM_FAULTDETECT                       ((uint8)(0x20U))  /*!< Fault detection completed this DCY */
# define DEM_ESM_IUMPR_NUM_FAULTDETECT_MASK                  ((uint8)(0xdfU))  /*!< Reset mask for fault detection completed this DCY */
# define DEM_ESM_IUMPR_DISCONNECTED                          ((uint8)(0x40U))  /*!< Ratio disconnected (suppressed) */
# define DEM_ESM_IUMPR_DISCONNECTED_MASK                     ((uint8)(0xbfU))  /*!< Reset mask for ratio disconnected (suppressed) */
/*!
 * \}
 */

/*! Maximum counter value for numerator / denominator */
# define DEM_ESM_IUMPR_MAX_VALUE                             ((uint16)0xffffU)
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */

#if (DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON)                                                                                     /* PRQA S 0883 */ /* MD_DEM_19.15 */
/*! Trigger mask for creation of an event memory entry */
# define DEM_ESM_EVENT_STORAGE_TRIGGER           DEM_CFG_TRIGGER_CONFIRMED
#elif (DEM_CFG_STORAGE_AT_FAILED == STD_ON) || (DEM_CFG_STORAGE_AT_PENDING == STD_ON)
/*! Trigger mask for creation of an event memory entry */
# define DEM_ESM_EVENT_STORAGE_TRIGGER           (DEM_CFG_TRIGGER_TESTFAILED|DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE)
#elif (DEM_CFG_STORAGE_AT_FDC == STD_ON)                                                                                         /* COV_MSR_CONFIG TX */
/*! Trigger mask for creation of an event memory entry */
# define DEM_ESM_EVENT_STORAGE_TRIGGER           (DEM_CFG_TRIGGER_FDC|DEM_CFG_TRIGGER_TESTFAILED)
#else
# error "No event storage trigger defined"
#endif

#if ( (DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON)   \
   || (DEM_CFG_PROCESS_PDTC_STOREDONLY == STD_ON)   \
   || (DEM_CFG_PROCESS_TFSLC_STOREDONLY == STD_ON) )
/*! Option setting if status bits depend on creation of an event memory entry */
# define DEM_FEATURE_NEED_STOREDONLY_BITS        STD_ON
#else
/*! Option setting if status bits depend on creation of an event memory entry */
# define DEM_FEATURE_NEED_STOREDONLY_BITS        STD_OFF
#endif

#if (DEM_CFG_PROCESS_PDTC_STOREDONLY == STD_ON)
/*! Mask for stored only Pending DTC trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_PENDING        DEM_CFG_TRIGGER_PENDING
#else
/*! Mask for stored only Pending DTC trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_PENDING        0x00U
#endif
#if (DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON)
/*! Mask for stored only Confirmed DTC trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_CONFIRMED      DEM_CFG_TRIGGER_CONFIRMED
#else
/*! Mask for stored only Confirmed DTC trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_CONFIRMED      0x00U
#endif
#if (DEM_CFG_PROCESS_WIR_STOREDONLY == STD_ON)
/*! Mask for stored only Warning Indicator Requested trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_INDICATOR      DEM_CFG_TRIGGER_INDICATOR
#else
/*! Mask for stored only Warning Indicator Requested trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_INDICATOR      0x00U
#endif


#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/*! Trigger Mask for event updates */
#define DEM_ESM_EVENT_UPDATE_TRIGGER             (DEM_CFG_TRIGGER_TESTFAILED|DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE)
#else
/*! Trigger Mask for event updates */
#define DEM_ESM_EVENT_UPDATE_TRIGGER             DEM_CFG_TRIGGER_TESTFAILED
#endif

/*! Reset Mask for stored only triggers */
#define DEM_ESM_EVENT_RESET_TRIGGER_MASK         ((uint8)(0xffU ^ (DEM_ESM_EVENT_NO_TRIGGER_PENDING   \
                                                                 | DEM_ESM_EVENT_NO_TRIGGER_CONFIRMED \
                                                                 | DEM_ESM_EVENT_NO_TRIGGER_INDICATOR)))

                                                    /* PID01 PID41 Readiness */
/* ------------------------------------------------------------------------- */

/*!
* \defgroup  Dem_Readiness_Initialize  Macros encoding initial values
* Macros encoding initial values depending on engine type
* \{
*/
/*!< Readiness initialization for spark engines */
#define DEM_READINESS_INITIALIZE_UPDATE_SPARK         ((uint16)  (1 << DEM_CFG_READINESS_CAT ) \
                                                               | (1 << DEM_CFG_READINESS_HTCAT) \
                                                               | (1 << DEM_CFG_READINESS_EVAP)  \
                                                               | (1 << DEM_CFG_READINESS_SECAIR) \
                                                               | (1 << DEM_CFG_READINESS_O2SENS) \
                                                               | (1 << DEM_CFG_READINESS_O2SENSHT) \
                                                               | (1 << DEM_CFG_READINESS_CMPRCMPT) \
                                                               | (1 << DEM_CFG_READINESS_EGR) \
                                                               | (1 << DEM_CFG_READINESS_FLSYS_NONCONT) \
                                                               | (1 << DEM_CFG_READINESS_MISF) )  

/*!< Readiness initialization for compression engines */
#define DEM_READINESS_INITIALIZE_UPDATE_COMPRESSION   ((uint16)  (1 << DEM_CFG_READINESS_HCCAT ) \
                                                               | (1 << DEM_CFG_READINESS_NOXCAT) \
                                                               | (1 << DEM_CFG_READINESS_BOOSTPR) \
                                                               | (1 << DEM_CFG_READINESS_PMFLT) \
                                                               | (1 << DEM_CFG_READINESS_EGSENS) \
                                                               | (1 << DEM_CFG_READINESS_CMPRCMPT) \
                                                               | (1 << DEM_CFG_READINESS_EGR) \
                                                               | (1 << DEM_CFG_READINESS_FLSYS_NONCONT) \
                                                               | (1 << DEM_CFG_READINESS_MISF) ) 

#define DEM_READINESS_INITIALIZE_PID01COMPLETED_SPARK          (0xFFFFFFEFUL)  /*!< Readiness initialization for PID spark engines */
#define DEM_READINESS_INITIALIZE_PID01COMPLETED_COMPRESSION    (0xFFFFFFEBUL)  /*!< Readiness initialization for spark engines */
/*!
* \}
*/

/*!
* \defgroup  Dem_Readiness_Support_State  Macros encoding assignment of readiness group supported state
* Macros encoding assignment of readiness group supported state to 32-bit mask
* \{
*/
#define DEM_READINESS_SUPPORT_NONE_MASK               (0x00000000UL)             /*!< Used to initialze local variables */
#define DEM_READINESS_SUPPORT_MISF_MASK               (0x00010000UL)             /*!< Bit encoding for DEM_OBD_RDY_MISF supported state */
#define DEM_READINESS_SUPPORT_FLSYS_MASK              (0x00020000UL)             /*!< Bit encoding for DEM_OBD_RDY_FLSYS and DEM_OBD_RDY_FLSYS_NONCONT supported state */
#define DEM_READINESS_SUPPORT_CMPRCMPT                (0x00040000UL)             /*!< Bit encoding for DEM_OBD_RDY_CMPRCMPT supported state */
#define DEM_READINESS_SUPPORT_CAT_MASK                (0x00000100UL)             /*!< Bit encoding for DEM_OBD_RDY_CAT supported state */
#define DEM_READINESS_SUPPORT_HCCAT_MASK              (0x00000100UL)             /*!< Bit encoding for DEM_OBD_RDY_HCCAT supported state */
#define DEM_READINESS_SUPPORT_HTCAT_MASK              (0x00000200UL)             /*!< Bit encoding for DEM_OBD_RDY_HTCAT supported state */
#define DEM_READINESS_SUPPORT_NOXCAT_MASK             (0x00000200UL)             /*!< Bit encoding for DEM_OBD_RDY_NOXCAT supported state */
#define DEM_READINESS_SUPPORT_EVAP_MASK               (0x00000400UL)             /*!< Bit encoding for DEM_OBD_RDY_EVAP supported state */
#define DEM_READINESS_SUPPORT_SECAIR_MASK             (0x00000800UL)             /*!< Bit encoding for DEM_OBD_RDY_SECAIR supported state */
#define DEM_READINESS_SUPPORT_BOOSTPR_MASK            (0x00000800UL)             /*!< Bit encoding for DEM_OBD_RDY_BOOSTPR supported state */
#define DEM_READINESS_SUPPORT_O2SENS_MASK             (0x00002000UL)             /*!< Bit encoding for DEM_OBD_RDY_O2SENS supported state */
#define DEM_READINESS_SUPPORT_EGSENS_MASK             (0x00002000UL)             /*!< Bit encoding for DEM_OBD_RDY_EGSENS supported state */
#define DEM_READINESS_SUPPORT_O2SENSHT_MASK           (0x00004000UL)             /*!< Bit encoding for DEM_OBD_RDY_O2SENSHT supported state */
#define DEM_READINESS_SUPPORT_PMFLT_MASK              (0x00004000UL)             /*!< Bit encoding for DEM_OBD_RDY_PMFLT supported state */
#define DEM_READINESS_SUPPORT_EGR_MASK                (0x00008000UL)             /*!< Bit encoding for DEM_OBD_RDY_ERG supported state */
#define DEM_READINESS_SUPPORT_COMPRESSION             (0x00080000UL)             /*!< Bit encoding for engine type compression ignition supported state */
/*!
* \}
*/

/*!
* \defgroup  Dem_Readiness_Completed_State  Macros encoding assignment of readiness group completed state
* Macros encoding assignment of readiness group completed state to 32-bit mask
* \{
*/
#define DEM_READINESS_COMPLETE_MISF_MASK              (0x00100000UL)             /*!< Bit encoding for DEM_OBD_RDY_MISF completed state */
#define DEM_READINESS_COMPLETE_FLSYS_MASK             (0x00200000UL)             /*!< Bit encoding for DEM_OBD_RDY_FLSYS and DEM_OBD_RDY_FLSYS_NONCONT completed state */
#define DEM_READINESS_COMPLETE_CMPRCMPT               (0x00400000UL)             /*!< Bit encoding for DEM_OBD_RDY_CMPRCMPT completed state */
#define DEM_READINESS_COMPLETE_CAT_MASK               (0x00000001UL)             /*!< Bit encoding for DEM_OBD_RDY_CAT completed state */
#define DEM_READINESS_COMPLETE_HCCAT_MASK             (0x00000001UL)             /*!< Bit encoding for DEM_OBD_RDY_HCCAT completed state */
#define DEM_READINESS_COMPLETE_HTCAT_MASK             (0x00000002UL)             /*!< Bit encoding for DEM_OBD_RDY_HTCAT completed state */
#define DEM_READINESS_COMPLETE_NOXCAT_MASK            (0x00000002UL)             /*!< Bit encoding for DEM_OBD_RDY_NOXCAT completed state */
#define DEM_READINESS_COMPLETE_EVAP_MASK              (0x00000004UL)             /*!< Bit encoding for DEM_OBD_RDY_EVAP completed state */
#define DEM_READINESS_COMPLETE_SECAIR_MASK            (0x00000008UL)             /*!< Bit encoding for DEM_OBD_RDY_SECAIR completed state */
#define DEM_READINESS_COMPLETE_BOOSTPR_MASK           (0x00000008UL)             /*!< Bit encoding for DEM_OBD_RDY_BOOSTPR completed state */
#define DEM_READINESS_COMPLETE_O2SENS_MASK            (0x00000020UL)             /*!< Bit encoding for DEM_OBD_RDY_O2SENS completed state */
#define DEM_READINESS_COMPLETE_EGSENS_MASK            (0x00000020UL)             /*!< Bit encoding for DEM_OBD_RDY_EGSENS completed state */
#define DEM_READINESS_COMPLETE_O2SENSHT_MASK          (0x00000040UL)             /*!< Bit encoding for DEM_OBD_RDY_O2SENSHT completed state */
#define DEM_READINESS_COMPLETE_PMFLT_MASK             (0x00000040UL)             /*!< Bit encoding for DEM_OBD_RDY_PMFLT completed state */
#define DEM_READINESS_COMPLETE_EGR_MASK               (0x00000080UL)             /*!< Bit encoding for DEM_OBD_RDY_ERG completed state */
/*!
* \}
*/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

#if (DEM_CFG_SUPPORT_OBDII == STD_ON)
/* Permanent status bit 'event visible in permanent memory' ---------------- */
/*! Test permanent entry visible in permanent entry state */
# define DEM_ESM_TEST_PERMANENT_VISIBLE(Var)        (((Var) & DEM_ESM_PERMANENT_VISIBLE) != 0)                                   /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set permanent entry visible in permanent entry state */
# define DEM_ESM_SET_PERMANENT_VISIBLE(Status)      ((uint8)((Status) | DEM_ESM_PERMANENT_VISIBLE))                              /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset permanent entry visible in permanent entry state */
# define DEM_ESM_RESET_PERMANENT_VISIBLE(Status)    ((uint8)((Status) & DEM_ESM_PERMANENT_VISIBLEMASK))                          /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Permanent status bit 'tested condition' ---------------- */
/*! Test permanent condition tested in permanent entry state */
# define DEM_ESM_TEST_PERMANENT_CONDITION_TESTED(Var)        (((Var) & DEM_ESM_PERMANENT_CONDITION_TESTED) != 0)                 /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set permanent condition tested in permanent entry state */
# define DEM_ESM_SET_PERMANENT_CONDITION_TESTED(Status)      ((uint8)((Status) | DEM_ESM_PERMANENT_CONDITION_TESTED))            /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset permanent condition tested in permanent entry state */
# define DEM_ESM_RESET_PERMANENT_CONDITION_TESTED(Status)    ((uint8)((Status) & DEM_ESM_PERMANENT_CONDITION_TESTEDMASK))        /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Permanent status bit 'PFC condition' ---------------- */
/*! Test permanent condition PFC in permanent entry state */
# define DEM_ESM_TEST_PERMANENT_CONDITION_PFC(Var)           (((Var) & DEM_ESM_PERMANENT_CONDITION_PFC) != 0)                    /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set permanent condition PFC in permanent entry state */
# define DEM_ESM_SET_PERMANENT_CONDITION_PFC(Status)         ((uint8)((Status) | DEM_ESM_PERMANENT_CONDITION_PFC))               /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset permanent condition PFC in permanent entry state */
# define DEM_ESM_RESET_PERMANENT_CONDITION_PFC(Status)       ((uint8)((Status) & DEM_ESM_PERMANENT_CONDITION_PFCMASK))           /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Permanent status bit 'DCY condition' ---------------- */
/*! Test permanent condition DCY in permanent entry state */
# define DEM_ESM_TEST_PERMANENT_CONDITION_DCY(Var)           (((Var) & DEM_ESM_PERMANENT_CONDITION_DCY) != 0)                    /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set permanent condition DCY in permanent entry state */
# define DEM_ESM_SET_PERMANENT_CONDITION_DCY(Status)         ((uint8)((Status) | DEM_ESM_PERMANENT_CONDITION_DCY))               /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset permanent condition DCY in permanent entry state */
# define DEM_ESM_RESET_PERMANENT_CONDITION_DCY(Status)       ((uint8)((Status) & DEM_ESM_PERMANENT_CONDITION_DCYMASK))           /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Permanent entry current FSM status -------------------------------------- */
/*! Get permanent state part of permanent entry condition byte */
# define DEM_ESM_GET_PERMANENT_STATE(Status)        ((uint8)((Status) & DEM_ESM_PERMANENT_STATES))                               /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set permanent state part of permanent entry condition byte */
# define DEM_ESM_SET_PERMANENT_STATE(Var, Status)   ((uint8)(((uint8)((Var) & DEM_ESM_PERMANENT_STATEMASK)) | ((uint8)((Status) & DEM_ESM_PERMANENT_STATES)))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#endif
#if (DEM_FEATURE_NEED_IUMPR == STD_ON)
/* general IUMPR status bits ----------------------------------------------- */
/*! Test general denominator conditions reached state in global denominator state */
# define DEM_ESM_TEST_IUMPR_GENDEN_CONDITIONS_REACHED(Status)   (((Status) & DEM_ESM_IUMPR_GENDEN_CONDITIONS_REACHED) != 0)      /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set general denominator conditions reached state in global denominator state */
# define DEM_ESM_SET_IUMPR_GENDEN_CONDITIONS_REACHED(Status)    ((uint8)((Status) | DEM_ESM_IUMPR_GENDEN_CONDITIONS_REACHED))    /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset general denominator conditions reached state in global denominator state */
# define DEM_ESM_RESET_IUMPR_GENDEN_CONDITIONS_REACHED(Status)  ((uint8)((Status) & DEM_ESM_IUMPR_GENDEN_CONDITIONS_REACHED_MASK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test general denominator conditions failed state in global denominator state */
# define DEM_ESM_TEST_IUMPR_GENDEN_CONDITIONS_FAILED(Status)    (((Status) & DEM_ESM_IUMPR_GENDEN_CONDITIONS_FAILED) != 0)       /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set general denominator conditions failed state in global denominator state */
# define DEM_ESM_SET_IUMPR_GENDEN_CONDITIONS_FAILED(Status)     ((uint8)((Status) | DEM_ESM_IUMPR_GENDEN_CONDITIONS_FAILED))     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset general denominator conditions failed state in global denominator state */
# define DEM_ESM_RESET_IUMPR_GENDEN_CONDITIONS_FAILED(Status)   ((uint8)((Status) & DEM_ESM_IUMPR_GENDEN_CONDITIONS_FAILED_MASK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test general denominator incremented state in global denominator state */
# define DEM_ESM_TEST_IUMPR_GENDEN_INCREMENTED(Status)          (((Status) & DEM_ESM_IUMPR_GENDEN_INCREMENTED) != 0)             /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set general denominator incremented state in global denominator state */
# define DEM_ESM_SET_IUMPR_GENDEN_INCREMENTED(Status)           ((uint8)((Status) | DEM_ESM_IUMPR_GENDEN_INCREMENTED))           /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset general denominator incremented state in global denominator state */
# define DEM_ESM_RESET_IUMPR_GENDEN_INCREMENTED(Status)         ((uint8)((Status) & DEM_ESM_IUMPR_GENDEN_INCREMENTED_MASK))      /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Hybrid status ----------------------------------------------- */
/*! Test hybrid ignition cycle counter incremented state in global hybrid ignition cycle state */
# define DEM_ESM_TEST_IUMPR_IGN_CYC_HYBRID_INCREMENTED(Status)  (((Status) & DEM_ESM_IUMPR_IGN_CYC_HYBRID_INCREMENTED) != 0)     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set hybrid ignition cycle counter incremented state in global hybrid ignition cycle state */
# define DEM_ESM_SET_IUMPR_IGN_CYC_HYBRID_INCREMENTED(Status)   ((uint8)((Status) | DEM_ESM_IUMPR_IGN_CYC_HYBRID_INCREMENTED))   /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset hybrid ignition cycle counter incremented state in global hybrid ignition cycle state */
# define DEM_ESM_RESET_IUMPR_IGN_CYC_HYBRID_INCREMENTED(Status) ((uint8)((Status) & DEM_ESM_IUMPR_IGN_CYC_HYBRID_INCREMENTED_MASK)) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Numerators Locked ----------------------------------------------- */
/*! Test numerators locked state in global iumpr state */
# define DEM_ESM_TEST_IUMPR_NUMERATORS_LOCKED(Status)           (((Status) & DEM_ESM_IUMPR_NUMERATORS_LOCKED) != 0)              /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set numerators locked state in global iumpr state */
# define DEM_ESM_SET_IUMPR_NUMERATORS_LOCKED(Status)            ((uint8)((Status) | DEM_ESM_IUMPR_NUMERATORS_LOCKED))            /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset numerators locked state in global iumpr state */
# define DEM_ESM_RESET_IUMPR_NUMERATORS_LOCKED(Status)          ((uint8)((Status) & DEM_ESM_IUMPR_NUMERATORS_LOCKED_MASK))       /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* ratio specific status bits ---------------------------------------------- */
/*! Test denominator incremented state of ratio status */
# define DEM_ESM_TEST_IUMPR_DEN_INCREMENTED(Status)             (((Status) & DEM_ESM_IUMPR_DEN_INCREMENTED) != 0)                /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set denominator incremented state of ratio status */
# define DEM_ESM_SET_IUMPR_DEN_INCREMENTED(Status)              ((uint8)((Status) | DEM_ESM_IUMPR_DEN_INCREMENTED))              /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset denominator incremented state of ratio status */
# define DEM_ESM_RESET_IUMPR_DEN_INCREMENTED(Status)            ((uint8)((Status) & DEM_ESM_IUMPR_DEN_INCREMENTED_MASK))         /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test denominator locked state of ratio status */
# define DEM_ESM_TEST_IUMPR_DEN_LOCKED(Status)                  (((Status) & DEM_ESM_IUMPR_DEN_LOCKED) != 0)                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set denominator locked state of ratio status */
# define DEM_ESM_SET_IUMPR_DEN_LOCKED(Status)                   ((uint8)((Status) | DEM_ESM_IUMPR_DEN_LOCKED))                   /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset denominator locked state of ratio status */
# define DEM_ESM_RESET_IUMPR_DEN_LOCKED(Status)                 ((uint8)((Status) & DEM_ESM_IUMPR_DEN_LOCKED_MASK))              /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test denominator conditions reached state of ratio status */
# define DEM_ESM_TEST_IUMPR_DEN_CONDITIONS_REACHED(Status)      (((Status) & DEM_ESM_IUMPR_DEN_CONDITIONS_REACHED) != 0)         /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set denominator conditions reached state of ratio status */
# define DEM_ESM_SET_IUMPR_DEN_CONDITIONS_REACHED(Status)       ((uint8)((Status) | DEM_ESM_IUMPR_DEN_CONDITIONS_REACHED))       /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset denominator conditions reached state of ratio status */
# define DEM_ESM_RESET_IUMPR_DEN_CONDITIONS_REACHED(Status)     ((uint8)((Status) & DEM_ESM_IUMPR_DEN_CONDITIONS_REACHED_MASK))  /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test numerator incremented state of ratio status */
# define DEM_ESM_TEST_IUMPR_NUM_INCREMENTED(Status)             (((Status) & DEM_ESM_IUMPR_NUM_INCREMENTED) != 0)                /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set numerator incremented state of ratio status */
# define DEM_ESM_SET_IUMPR_NUM_INCREMENTED(Status)              ((uint8)((Status) | DEM_ESM_IUMPR_NUM_INCREMENTED))              /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset numerator incremented state of ratio status */
# define DEM_ESM_RESET_IUMPR_NUM_INCREMENTED(Status)            ((uint8)((Status) & DEM_ESM_IUMPR_NUM_INCREMENTED_MASK))         /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test fault detection completed state of ratio status */
# define DEM_ESM_TEST_IUMPR_NUM_FAULTDETECT(Status)             (((Status) & DEM_ESM_IUMPR_NUM_FAULTDETECT) != 0)                /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set fault detection completed state of ratio status */
# define DEM_ESM_SET_IUMPR_NUM_FAULTDETECT(Status)              ((uint8)((Status) | DEM_ESM_IUMPR_NUM_FAULTDETECT))              /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset fault detection completed state of ratio status */
# define DEM_ESM_RESET_IUMPR_NUM_FAULTDETECT(Status)            ((uint8)((Status) & DEM_ESM_IUMPR_NUM_FAULTDETECT_MASK))         /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test ratio blocked by pending FiD state of ratio status */
# define DEM_ESM_TEST_IUMPR_FID_PENDING(Status)                 (((Status) & DEM_ESM_IUMPR_FID_PENDING) != 0)                    /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set ratio blocked by pending FiD state of ratio status */
# define DEM_ESM_SET_IUMPR_FID_PENDING(Status)                  ((uint8)((Status) | DEM_ESM_IUMPR_FID_PENDING))                  /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset ratio blocked by pending FiD state of ratio status */
# define DEM_ESM_RESET_IUMPR_FID_PENDING(Status)                ((uint8)((Status) & DEM_ESM_IUMPR_FID_PENDING_MASK))             /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Test ratio disconnected state of ratio status */
# define DEM_ESM_TEST_IUMPR_DISCONNECTED(Status)                (((Status) & DEM_ESM_IUMPR_DISCONNECTED) != 0)                   /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set ratio disconnected state of ratio status */
# define DEM_ESM_SET_IUMPR_DISCONNECTED(Status)                 ((uint8)((Status) | DEM_ESM_IUMPR_DISCONNECTED))                 /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset ratio disconnected state of ratio status */
# define DEM_ESM_RESET_IUMPR_DISCONNECTED(Status)               ((uint8)((Status) & DEM_ESM_IUMPR_DISCONNECTED_MASK))            /* PRQA S 3453 */ /* MD_MSR_19.7 */
#endif /* (DEM_FEATURE_NEED_IUMPR == STD_ON) */


/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#endif /* DEM_ESM_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Esm_Types.h
 *********************************************************************************************************************/
