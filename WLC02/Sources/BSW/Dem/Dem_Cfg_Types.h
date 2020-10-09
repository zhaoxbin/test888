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
 *         File:  Dem_Cfg_Types.h
 *      Project:  MICROSAR Diagnostic Event Manager (Dem)
 *       Module:  Configuration
 *    Generator:  -
 *
 *  Description:  Type definitions of configuration subcomponent
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

#if !defined (DEM_CFG_TYPES_H)
#define DEM_CFG_TYPES_H
#include "Dem_Int.h"
#include "Dem_Prestore_Types.h"

/* ********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \defgroup  Dem_ConfigurationLimits  No-such-element identifiers
 * Enumeration labels defining invalid values for number based data elements
 * \{
 */

#define DEM_CFG_DTC_J1939_INVALID                (0x00FFFFFFUL)                              /*!< No J1939 DTC */
#define DEM_CFG_DTC_OBD_INVALID                  (0x0000U)                                   /*!< No OBD DTC */
#define DEM_CFG_DTC_UDS_INVALID                  (0x00FFFFFFUL)                              /*!< No UDS DTC */
#define DEM_CFG_COMBINED_GROUP_INVALID           (DEM_CFG_NO_COMBINEDGROUPSIDXOFEVENTTABLE)  /*!< No event combination */
#define DEM_CFG_MIL_GROUP_INVALID                (0U)                                        /*!< No MIL group */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_DataElementTypes  Data element type
 * Enumeration labels defining the type of a data element
 * \{
 */
#define DEM_CFG_DATA_FROM_AGINGCTR                                             (0U)   /*!< Data element maps to the up-counting aging counter (1 byte) */
#define DEM_CFG_DATA_FROM_OCCCTR                                               (2U)   /*!< Data element maps to the occurrence counter (1 byte) */
#define DEM_CFG_DATA_FROM_OCCCTR_2BYTE                                         (3U)   /*!< Data element maps to the occurrence counter (2 byte) */
#define DEM_CFG_DATA_FROM_OVFLIND                                              (4U)   /*!< Data element maps to the memory overflow state (1 byte) */
#define DEM_CFG_DATA_FROM_SIGNIFICANCE                                         (5U)   /*!< Data element maps to the event significance (1 byte) */
#define DEM_CFG_DATA_FROM_DAG_STANDARD_ENV_DATA                                (6U)   /*!< Data element maps to the standard data record (7 byte) */
#define DEM_CFG_DATA_FROM_DAG_EXTENDED_ENV_DATA                                (7U)   /*!< Data element maps to the extended data record (11 byte) */
#define DEM_CFG_DATA_FROM_PRIORITY                                             (8U)   /*!< Data element maps to the event priority (1 byte) */
#define DEM_CFG_DATA_FROM_AGINGCTR_INVERTED                                    (9U)   /*!< Data element maps to the down-counting aging counter (1 byte) */
#define DEM_CFG_DATA_FROM_MAX_FDC_SINCE_LAST_CLEAR                             (11U)  /*!< Data element maps to the maximum FDC since last clear (1 byte) */
#define DEM_CFG_DATA_FROM_MAX_FDC_DURING_CURRENT_CYCLE                         (12U)  /*!< Data element maps to the maximum FDC in the current cycle (1 byte) */
#define DEM_CFG_DATA_FROM_CYCLES_SINCE_LAST_FAILED                             (13U)  /*!< Data element maps to the number of cycle since last failed (1 byte) */
#define DEM_CFG_DATA_FROM_CYCLES_SINCE_FIRST_FAILED                            (14U)  /*!< Data element maps to the number of cycles since first failed (1 byte) */
#define DEM_CFG_DATA_FROM_FAILED_CYCLES                                        (15U)  /*!< Data element maps to the number of cycles with a failed result (1 byte) */
#define DEM_CFG_DATA_FROM_CYCLES_SINCE_LAST_UNCONFIRMED                        (16U)  /*!< Data element maps to the number of cycles since last FDC trip (1 byte)*/
#define DEM_CFG_DATA_FROM_CYCLES_PASSED_SINCE_LAST_UNCONFIRMED                 (17U)  /*!< Data element maps to the number of cycles with a passed result since last FDC trip (1 byte) */
#define DEM_CFG_DATA_FROM_CYCLES_SINCE_FIRST_UNCONFIRMED                       (18U)  /*!< Data element maps to the number of cycles since the first cycle with an FDC trip (1 byte) */
#define DEM_CFG_DATA_FROM_UNCONFIRMED_CYCLES                                   (19U)  /*!< Data element maps to the number of cycles with an FDC trip (1 byte) */
#define DEM_CFG_DATA_FROM_CONSECUTIVE_FAILED_CYCLES                            (20U)  /*!< Data element maps to the number of cycles with a failed result since the last passed cycle (1 byte) */
#define DEM_CFG_DATA_FROM_CYCLES_PASSED_OR_UNCONFIRMED_SINCE_FIRST_UNCONFIRMED (21U)  /*!< Data element maps to the number of cycles with a passed result of FDC trip since the first cycle with an FDC trip (1 byte) */
#define DEM_CFG_DATA_FROM_CURRENT_FDC                                          (22U)  /*!< Data element maps to the current FDC (1 byte) */
#define DEM_CFG_DATA_FROM_DTC_STATUS_INDICATOR                                 (23U)  /*!< Data element maps to the DTC status indicator byte (1 byte) */
#define DEM_CFG_DATA_FROM_ROOTCAUSE_EVENTID                                    (24U)  /*!< Data element maps to the root-cause event id (2 byte) */
#define DEM_CFG_DATA_FROM_OBDDTC                                               (25U)  /*!< Data element maps to the OBD DTC number (2 byte) */
#define DEM_CFG_DATA_FROM_OBDDTC_3BYTE                                         (26U)  /*!< Data element maps to the OBD DTC number (3 byte) */
#define DEM_CFG_DATA_FROM_CYCLES_TESTED_SINCE_FIRST_FAILED                     (27U)  /*!< Data element maps to the number of cycles with a test result since first failed cycle (1 byte) */
#define DEM_CFG_DATA_FROM_CYCLES_TESTED_SINCE_LAST_FAILED                      (28U)  /*!< Data element maps to the number of cycles with a test result since last failed cycle (1 byte) */
#define DEM_CFG_DATA_FROM_HEALINGCTR_DOWNCNT                                   (29U)  /*!< Data element maps to the down-counting healing counter (1 byte) */
#define DEM_CFG_DATA_FROM_OBD_RATIO                                            (30U)  /*!< Data element maps to the ratio (Numerator and Denominator) */
#define DEM_CFG_DATA_FROM_FAULT_PENDING_COUNTER                                (31U)  /*!< Data element maps to the fault pending counter (1 byte) */
#define DEM_CFG_DATA_FROM_AGED_COUNTER                                         (32U)  /*!< Data element maps to the aged counter (1 byte) */
#define DEM_CFG_DATA_FROM_CBK                                                  (33U)  /*!< Data element maps to an application callback (configured size) */
#define DEM_CFG_DATA_FROM_CBK_WITH_EVENTID                                     (34U)  /*!< Data element maps to an application callback with EventId argument (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_BOOLEAN                                      (35U)  /*!< Data element maps to a Sender Receiver callback with data type boolean (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_SINT8                                        (36U)  /*!< Data element maps to a Sender Receiver callback with data type sint32 Motorola (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_SINT16                                       (37U)  /*!< Data element maps to a Sender Receiver callback with data type sint16 Intel (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_SINT32                                       (38U)  /*!< Data element maps to a Sender Receiver callback with data type sint32 Intel (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_SINT16_INTEL                                 (39U)  /*!< Data element maps to a Sender Receiver callback with data type sint8 Array (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_SINT32_INTEL                                 (40U)  /*!< Data element maps to a Sender Receiver callback with data type uint8 (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_SINT8_N                                      (41U)  /*!< Data element maps to a Sender Receiver callback with data type uint16 Motorola (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_UINT8                                        (42U)  /*!< Data element maps to a Sender Receiver callback with data type uint32 Motorola (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_UINT16                                       (43U)  /*!< Data element maps to a Sender Receiver callback with data type uint16 Intel (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_UINT32                                       (44U)  /*!< Data element maps to a Sender Receiver callback with data type uint32 Intel (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_UINT16_INTEL                                 (45U)  /*!< Data element maps to a Sender Receiver callback with data type uint8 Array (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_UINT32_INTEL                                 (46U)  /*!< Data element maps to a Sender Receiver callback with data type sint16 Motorola (configured size) */
#define DEM_CFG_DATA_FROM_SR_PORT_UINT8_N                                      (47U)  /*!< Data element maps to a Sender Receiver callback with data type sint8 (configured size) */
#define DEM_CFG_DATAELEMENT_INVALID                                            (65U)  /*!< Data element does not map to data */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_DebounceType  debounce algorithm type
 * Enumeration labels defining the debounce algorithm of an event
 * \{
 */
#define DEM_CFG_DEBOUNCETYPE_COUNTER             (0U)  /*!< Event uses counter based debouncing */
#define DEM_CFG_DEBOUNCETYPE_TIMER               (1U)  /*!< Event uses time based debouncing */
#define DEM_CFG_DEBOUNCETYPE_MONITORINTERNAL     (2U)  /*!< Event monitor implements debouncing (no debouncing in Dem) */
#define DEM_CFG_DEBOUNCETYPE_INVALID             (3U)  /*!< No debouncing set (invalid) */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_ERecStorageTypes  Extended data record storage type
 * Enumeration labels defining the storage type of an extended data record
 * \{
 */
#define DEM_CFG_EREC_TYPE_GLOBAL                 (0U)  /*!< Data record does not require storage */
#define DEM_CFG_EREC_TYPE_INTERNAL               (1U)  /*!< Data record requires a memory entry */
#define DEM_CFG_EREC_TYPE_USER                   (2U)  /*!< Data record requires room in the user record buffer within a memory entry */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_SignificanceTypes  Event Significance type
 * Enumeration labels defining the event significance
 * \{
 */
#define DEM_CFG_EVENT_SIGNIFICANCE_OCCURRENCE    (0U)  /*!< Event is a Occurrence */
#define DEM_CFG_EVENT_SIGNIFICANCE_FAULT         (1U)  /*!< Event is a Fault */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_ReportingType  Event reporting types
 * Enumeration labels defining the reporting types for an event
 * \{
 */
#define DEM_CFG_EVENT_KIND_BSW                   (0U)  /*!< Event is reported by Dem_ReportErrorStatus */
#define DEM_CFG_EVENT_KIND_SWC                   (1U)  /*!< Event is reported by Dem_SetEventStatus */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_DTCGroupMask  DTC Group Mask identifier
 * Enumeration labels defining the DTC group masks
 * \{
 */
#define DEM_CFG_GROUPMASK_ALLDTCS                (0xFFU)  /*!< Mask for 'ALL DTCs' */
#define DEM_CFG_GROUPMASK_NETWORK                (0x10U)  /*!< Mask for DTC group network */
#define DEM_CFG_GROUPMASK_BODY                   (0x08U)  /*!< Mask for DTC group body */
#define DEM_CFG_GROUPMASK_CHASSIS                (0x04U)  /*!< Mask for DTC group chassis */
#define DEM_CFG_GROUPMASK_POWERTRAIN             (0x02U)  /*!< Mask for DTC group powertrain */
#define DEM_CFG_GROUPMASK_NONE                   (0x00U)  /*!< Mask for 'no group' */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_MemoryId  Memory locations
 * Enumeration labels defining the event memory locations used by the Dem
 * \{
 */
#define DEM_CFG_MEMORYID_PRIMARY                 (0U)  /*!< primary event memory */
#define DEM_CFG_MEMORYID_SECONDARY               (1U)  /*!< secondary event memory */
#define DEM_CFG_MEMORYID_MIRROR                  (2U)  /*!< mirror event memory - unsupported */
#define DEM_CFG_MEMORYID_PERMANENT               (3U)  /*!< permanent DTC memory */
#define DEM_CFG_MEMORYID_TIMESERIES              (4U)  /*!< time series memory */
#define DEM_CFG_MEMORYID_INVALID                 (5U)  /*!< not a memory location */

/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_OpCycleKind  Operation cycle kind
 * Enumeration labels defining the operation cycle kind
 * \{
 */
#define DEM_CFG_OPCYC_IGNITION                   (0U)  /*!< Ignition Cycle */
#define DEM_CFG_OPCYC_OBD_DCY                    (1U)  /*!< OBD Driving Cycle */
#define DEM_CFG_OPCYC_OTHER                      (2U)  /*!< Generic Cycle */
#define DEM_CFG_OPCYC_POWER                      (3U)  /*!< Power Cycle */
#define DEM_CFG_OPCYC_TIME                       (4U)  /*!< Timeout Cycle */
#define DEM_CFG_OPCYC_WARMUP                     (5U)  /*!< WarmUp Cycle */
#define DEM_CFG_OPCYC_IGNITION_HYBRID            (6U)  /*!< Hybrid Ignition Cycle */
#define DEM_CFG_OPCYC_AGING                      (7U)  /*!< Aging Cycle */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_StorageTriggerType  Storage trigger
 * Enumeration labels defining storage triggers
 * \{
 */
#define DEM_CFG_TRIGGER_NONE                       (0U)    /*!< No trigger */
#define DEM_CFG_TRIGGER_FDC                        (1U)    /*!< Fault detection counter threshold */
#define DEM_CFG_TRIGGER_TESTFAILED                 (2U)    /*!< TestFailed 0->1 transition */
#define DEM_CFG_TRIGGER_TESTPASSED                 (2U)    /*!< TestFailed 1->0 transition */
#define DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE        (4U)    /*!< TestFailedthisOperatingCycle 0->1 transition */
#define DEM_CFG_TRIGGER_PENDING                    (8U)    /*!< PendingDTC 0->1 transition */
#define DEM_CFG_TRIGGER_CONFIRMED                  (16U)   /*!< ConfirmedDTC 0->1 transition */
#define DEM_CFG_TRIGGER_INDICATOR                  (32U)   /*!< WarningIndicatorRequested 0->1 transition */
#define DEM_CFG_TRIGGER_FIRSTTHISCYCLE             (64U)   /*!< Modifier flag: First trigger in the cycle - does not occur by itself */
#define DEM_CFG_TRIGGER_FDC_FIRST_IN_CYCLE         (65U)   /*!< First fault detection counter threshold in the cycle */
#define DEM_CFG_TRIGGER_TESTFAILED_FIRST_IN_CYCLE  (66U)   /*!< First TestFailed 1->0 transition in the cycle */
#define DEM_CFG_TRIGGER_OEM                        (128U)  /*!< OEM defined trigger calculation */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_RatioReportingType  Ratio reporting types
 * Enumeration labels defining ratio reporting types
 * \{
 */
#define DEM_RATIO_API                            (0U)  /*!< Numerator increment by event report */
#define DEM_RATIO_OBSERVER                       (1U)  /*!< Numerator increment by dedicated API */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_DenominatorGroupType  Ratio denominator groups
 * Enumeration labels defining ratio denominator groups
 * \{
 */
#define DEM_IUMPR_DEN_NONE                       (0U)  /*!< no additional denominator conditions */
#define DEM_IUMPR_DEN_PHYS_API                   (1U)  /*!< additional denominator condition reported by API*/
#define DEM_IUMPR_DEN_COLDSTART                  (2U)  /*!< additional cold start denominator condition */
#define DEM_IUMPR_DEN_EVAP                       (3U)  /*!< additional evaporator denominator condition */
#define DEM_IUMPR_DEN_500MI                      (4U)  /*!< additional 500 miles denominator condition */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Cfg_ReadinessGroupType  Event OBD Readiness groups
 * Enumeration labels defining event OBD readiness groups
 * \{
 */
#define DEM_CFG_READINESS_MISF                   (0U)  /*!< OBD readiness group DEM_OBD_RDY_MISF */
#define DEM_CFG_READINESS_CMPRCMPT               (1U)  /*!< OBD readiness group DEM_OBD_RDY_CMPRCMPT */
#define DEM_CFG_READINESS_CAT                    (2U)  /*!< OBD readiness group DEM_OBD_RDY_CAT */
#define DEM_CFG_READINESS_HCCAT                  (3U)  /*!< OBD readiness group DEM_OBD_RDY_HCCAT */
#define DEM_CFG_READINESS_HTCAT                  (4U)  /*!< OBD readiness group DEM_OBD_RDY_HTCAT */
#define DEM_CFG_READINESS_NOXCAT                 (5U)  /*!< OBD readiness group DEM_OBD_RDY_NOXCAT */
#define DEM_CFG_READINESS_EVAP                   (6U)  /*!< OBD readiness group DEM_OBD_RDY_EVAP */
#define DEM_CFG_READINESS_SECAIR                 (7U)  /*!< OBD readiness group DEM_OBD_RDY_SECAIR */
#define DEM_CFG_READINESS_BOOSTPR                (8U)  /*!< OBD readiness group DEM_OBD_RDY_BOOSTPR */
#define DEM_CFG_READINESS_O2SENS                 (9U)  /*!< OBD readiness group DEM_OBD_RDY_O2SENS */
#define DEM_CFG_READINESS_EGSENS                 (10U)  /*!< OBD readiness group DEM_OBD_RDY_EGSENS */
#define DEM_CFG_READINESS_O2SENSHT               (11U)  /*!< OBD readiness group DEM_OBD_RDY_O2SENSHT */
#define DEM_CFG_READINESS_PMFLT                  (12U)  /*!< OBD readiness group DEM_OBD_RDY_PMFLT */
#define DEM_CFG_READINESS_EGR                    (13U)  /*!< OBD readiness group DEM_OBD_RDY_ERG */
#define DEM_CFG_READINESS_ERG                    (13U)  /*!< Compatibility define for typo in Autosar */
#define DEM_CFG_READINESS_FLSYS_NONCONT          (14U)  /*!< OBD readiness group DEM_OBD_RDY_FLSYS_NONCONT */
#define DEM_CFG_READINESS_FLSYS                  (15U)  /*!< OBD readiness group DEM_OBD_RDY_FLSYS */
#define DEM_CFG_READINESS_NONE                   (16U)  /*!< Event is not assigned to a readiness group */
#define DEM_CFG_READINESS_GROUP_COUNT            (16U)  /*!< Number of readiness groups assigned to different numbers - without DEM_CFG_READINESS_NONE */
/*!
* \}
*/

#define DEM_CFG_UDSSEVERITYBITMASK               (0x1fU)


/*!
 * \defgroup  Dem_Cfg_DtrUpdateTypes  Dtr Update type
 * Enumeration labels defining the Dtr Update Kind
 * \{
 */
#define DEM_DTR_UPDATE_ALWAYS    (0U)
#define DEM_DTR_UPDATE_STEADY    (1U)
/*!
* \}
*/

/* ********************************************************************************************************************
 * GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! Index type for accessing combined group configuration tables */
typedef uint16 Dem_Cfg_CombinedGroupIndexType;
/*! Index type for accessing data element configuration tables */
typedef uint16 Dem_Cfg_DataIndexType;
/*! Index type for accessing extended data record configuration tables */
typedef uint16 Dem_Cfg_ERecIndexType;
/*! Index type for accessing data identifier configuration tables */
typedef uint16 Dem_Cfg_DidIndexType;
/*! Index type for accessing snapshot record configuration tables */
typedef uint16 Dem_Cfg_SRecIndexType;
/*! Index type for accessing J1939 node configuration tables */
typedef uint16 Dem_Cfg_J1939NodeIndexType;

/*! Iterator type for iteration over global data */
typedef uint16_least Dem_Cfg_SimpleIterType;
/*! Iterator type for iteration over data subsets */
struct Dem_Cfg_ComplexIterType_s
{
  uint16_least mIdx;    /*!< Current iterator position */
  uint16_least mEndIdx; /*!< Iterator end position */
};

/*! Base type for iterations */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_ComplexIterType;
/*! Iterator type for iteration over data elements of data identifiers */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_DidDataIterType;
/*! Iterator type for iteration over status change notification of an event */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventCbkStatusIterType;
/*! Iterator type for iteration over data identifiers stored for an event */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventDidIterType;
/*! Iterator type for iteration over data identifiers stored for a global snapshot record*/
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_GlobalSnapshotDidIterType;
/*! Iterator type for iteration over extended data records relevant for an event */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventERecIterType;
/*! Iterator type for iteration over indicator infos relevant for an event */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventIndicatorIterType;
/*! Iterator type for iteration over J1939 nodes relevant for an event */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventJ1939NodeIterType;
/*! Iterator type for iteration over data identifier in an event's WWH-OBD freeze frame */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventObdDidIterType;
/*! Iterator type for iteration over snapshot records relevant for an event */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventSRecIterType;
/*! Iterator type for iteration over suspect parameter numbers stored for an event's j1939 freezeframe */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventSPNIterType;
/*! Iterator type for iteration over events belonging to a event combination */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_CombinedGroupIterType;
/*! Iterator type for iteration over function inhibitions relevant for an event's ratio */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_ObdFimFidIterType;
/*! Iterator type for iteration over init function notifications relevant for an event */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventCbkInitFuncIterType;
/*! Iterator type for iteration over DTRs mapped to an event */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_EventDtrIterType;
/*! Iterator type for iteration over all high resolution debounce timers */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_DebounceHiResIterType;
/*! Iterator type for iteration over all low resolution debounce timers */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_DebounceLoResIterType;
/*! Iterator type for iteration over J1939 DTC status change notifictions */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Cfg_GlobalCbkJ1939DtcIterType;

/*! Iterator type for iteration over UDS DTC status change notifictions */
typedef Dem_Cfg_SimpleIterType Dem_Cfg_GlobalCbkDtcIterType;
/*! Iterator type for iteration over all ratios */
typedef Dem_Cfg_SimpleIterType Dem_Cfg_ObdRatioIdIterType;
/*! Iterator type for iteration over PIDs stored in the OBD-II freeze frame */
typedef Dem_Cfg_SimpleIterType Dem_Cfg_GlobalPidIterType;
/*! Iterator type for iteration over DIDs stored in fast rate time series snapshots */
typedef Dem_Cfg_SimpleIterType Dem_Cfg_TimeSeriesDidFastIterType;
/*! Iterator type for iteration over DIDs stored in normal rate time series snapshots */
typedef Dem_Cfg_SimpleIterType Dem_Cfg_TimeSeriesDidNormalIterType;


/*! Function pointer for 'GetCurrentOdometer' callback */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_OemCbkGetCurrentOdometerFptrType)(
                                                   P2VAR(uint32, DEM_APPL_DATA, AUTOMATIC) /* [out] data */
                                                 );
/*! Function pointer for 'GetExternalTester' callback */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_OemCbkGetExternalTesterStatusFptrType)(
                                                   P2VAR(boolean, DEM_APPL_DATA, AUTOMATIC) /* [out] data */
                                                 );

#endif  /* DEM_CFG_TYPES_H */
/*!
 * \}
 */
