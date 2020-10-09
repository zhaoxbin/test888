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
/*! \addtogroup Dem_DTC
 *  \{
 *  \file       Dem_DTC_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of DTC subcomponent
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

#if !defined (DEM_DTC_TYPES_H)
#define DEM_DTC_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
/*! Maximum value internal data element 'aged counter' can reach before it is latched' */
#define DEM_DTC_AGED_COUNTER_MAX_VALUE           (0xFFU)
/*! Initial value of internal data element 'aged counter' */
#define DEM_DTC_AGED_COUNTER_INIT_VALUE          (0x00U)
/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* Status 'ActiveDTC' ------------------------------------------------------ */
/*! Test active DTC state of UDS status */
#define DEM_DTC_TEST_J1939_STATUS_ADTC(Status)   (((Status) & (DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_TF)) == (DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_TF)) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Status 'PreviouslyActiveDTC' -------------------------------------------- */
/*! Test previously active DTC state of UDS status */
#define DEM_DTC_TEST_J1939_STATUS_PADTC(Status)  (((Status) & (DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_TF)) == (DEM_UDS_STATUS_CDTC)) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Pre-confirmed status bit 'unconfirmedDTC' ------------------------------- */
/*! Test pre-confirmed DTC state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_UDTC(Status)      (((Status) & 0x01U) != 0)                                                       /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set pre-confirmed DTC state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_UDTC(Status)       ((uint8)((Status) | 0x01U))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset pre-confirmed DTC state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_UDTC(Status)     ((uint8)((Status) & 0xfeU))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Pre-confirmed status bit 'unconfirmedDTCThisOperationCycle' ------------- */
/*! Test pre-confirmed DTC this operating cycle state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_UDTCTOC(Status)   (((Status) & 0x02U) != 0)                                                       /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set pre-confirmed DTC this operating cycle state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_UDTCTOC(Status)    ((uint8)((Status) | 0x02U))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset pre-confirmed DTC this operating cycle state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_UDTCTOC(Status)  ((uint8)((Status) & 0xfdU))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Pre-confirmed status bit 'unconfirmedDTCSinceLastClear' ----------------- */
/*! Test pre-confirmed DTC since last clear state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_UDTCSLC(Status)   (((Status) & 0x04U) != 0)                                                       /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set pre-confirmed DTC since last clear state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_UDTCSLC(Status)    ((uint8)((Status) | 0x04U))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset pre-confirmed DTC since last clear state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_UDTCSLC(Status)  ((uint8)((Status) & 0xfbU))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Pre-confirmed status bit 'agedDTC' -------------------------------------- */
/*! Test aged DTC state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_ADTC(Status)      (((Status) & 0x08U) != 0)                                                       /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set aged DTC state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_ADTC(Status)       ((uint8)((Status) | 0x08U))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset aged DTC state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_ADTC(Status)     ((uint8)((Status) & 0xf7U))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Pre-confirmed status bit 'symptomSinceLastClear' ------------------------ */
/*! Test symptom since last clear state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_SSLC(Status)      (((Status) & 0x10U) != 0)                                                       /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set symptom since last clear state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_SSLC(Status)       ((uint8)((Status) | 0x10U))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset symptom since last clear state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_SSLC(Status)     ((uint8)((Status) & 0xefU))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Pre-confirmed status bit 'warningIndicatorRequestedSinceLastClear' ------ */
/*! Test warning indicator requested since last clear state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_WIRSLC(Status)    (((Status) & 0x20U) != 0)                                                       /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set warning indicator requested since last clear state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_WIRSLC(Status)     ((uint8)((Status) | 0x20U))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset warning indicator requested since last clear state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_WIRSLC(Status)   ((uint8)((Status) & 0xdfU))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Pre-confirmed status bit 'emissionRelatedDTC' --------------------------- */
/*! Test emission related DTC state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_ODBDTC(Status)    (((Status) & 0x40U) != 0)                                                       /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set emission related DTC state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_ODBDTC(Status)     ((uint8)((Status) | 0x40U))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset emission related DTC state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_ODBDTC(Status)   ((uint8)((Status) & 0xbfU))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Pre-confirmed status bit 'testFailedSinceLastClear' --------------------- */
/*! Test test failed since last clear state of SI.30 status */
#define DEM_DTC_TEST_PC_STATUS_TFSLC(Status)     (((Status) & 0x80U) != 0)                                                       /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Set test failed since last clear state of SI.30 status */
#define DEM_DTC_SET_PC_STATUS_TFSLC(Status)      ((uint8)((Status) | 0x80U))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Reset test failed since last clear state of SI.30 status */
#define DEM_DTC_RESET_PC_STATUS_TFSLC(Status)    ((uint8)((Status) & 0x7fU))                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Type to store the UDS status of an DTC */
typedef uint8 Dem_DTC_UDSStatusType;

  /*! DTC status processing data */
struct Dem_DTC_Context_s
{
  Dem_EventIdType EventId;  /*!< Handle of processed DTC */
  Dem_Cfg_CombinedGroupIndexType GroupId;  /*!< [in] combination group of the DTC */
  Dem_DTC_UDSStatusType OldDtcStatus;  /*!< [in] DTC status before processing */
  Dem_DTC_UDSStatusType OldExternalDtcStatus;  /*!< [in] external DTC status before processing */
  Dem_DTC_UDSStatusType NewDtcStatus;  /*!< [in,out] DTC status after processing */
  uint8 DtcEffects;  /*!< [in,out] status change triggers resulting from DTC status changes */
};

/*! DTC status processing data type */
typedef struct Dem_DTC_Context_s Dem_DTC_ContextType;

/*! Structure used as argument type for Dem_DTC_ForEachCombinedEvent functions */
struct Dem_DTC_ForEachCombinedArgType_s
{
  /*! Function arguments common to all functions */
  struct
  {
    uint8 OldDtcStatus;  /*!< [in] DtcStatus before the call */
    uint8 NewDtcStatus;  /*!< [out] DtcStatus after the call */
  } Common;
  /*! Function arguments specific to the called function */
  union
  {                                                                                                                              /* PRQA S 0750 */ /* MD_MSR_18.4 */
    /*! Function arguments specific to Dem_Event_Cleared */
    struct
    {
      uint8 unused;  /*!< no specific arguments, dummy only */
    } EventClearState;
#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
    /*! Function arguments specific to Dem_Event_Displaced_Vcc */
    struct
    {
      uint8 SI30;  /*!< [in,out] In: SI30 value before the call, Out: SI30 value after the call */
    } EventDisplaced_Vcc_Internal;
#else
    /*! Function arguments specific to Dem_Event_Displaced */
    struct
    {
      uint8 unused;  /*!< no specific arguments, dummy only */
    } EventDisplaced_Internal;
#endif
    /*! Function arguments specific to Dem_Event_OpCycle */
    struct
    {
      uint8 CycleStatus;  /*!< [in] CycleStatus to set */
    } EventOpCycle_Internal;
    /*! Function arguments specific to Dem_Event_AgingCycle_Internal */
    struct
    {
      uint8 unused;  /*!< no specific arguments, dummy only */
    } EventAgingCycle_Internal;
    /*!function arguments specific to Dem_Event_CycleQualifyDcy */
    struct
    {
      uint8 unused;  /*!< no specific arguments, dummy only */
    } CycleQualifyDcy_Internal;
  } Specific;
};

/*! Argument type used for Dem_DTC_ForEachCombinedEvent functions */
typedef struct Dem_DTC_ForEachCombinedArgType_s Dem_DTC_ForEachCombinedArgType;

/*! Reference to argument struct used for Dem_DTC_ForEachCombinedEvent functions */
typedef P2VAR(Dem_DTC_ForEachCombinedArgType, TYPEDEF, DEM_VAR_NOINIT) Dem_DTC_ForEachCombinedArgPtrType;

/*! Function pointer type for Dem_DTC_ForEachCombinedEvent functions */
typedef P2FUNC(void, DEM_CODE, Dem_Util_ForEachCombinedFuncType)(
  CONST(Dem_EventIdType, AUTOMATIC)  EventId,
  CONST(Dem_DTC_ForEachCombinedArgPtrType, AUTOMATIC)  ArgPtr
  );

/*! Enum encapsulated current aging status of DTCs, only used when DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON */
typedef enum
{
  Dem_DTC_AgingStatusNone,       /*!< Aging is not currently in progress */
  Dem_DTC_AgingStatusInProgress, /*!< Aging is currently in progress */
  Dem_DTC_AgingStatusAged        /*!< Aging is finished, event is currently aged */
} Dem_DTC_AgingStatusType;

#endif /* DEM_DTC_TYPES_H */
/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_DTC_Types.h
 *********************************************************************************************************************/
