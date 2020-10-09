
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
 *         File:  Dem_Types.h
 *      Project:  MICROSAR Diagnostic Event Manager (Dem)
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  Static public API declarations of the MICROSAR Dem.
 *                Dynamically available APIs are declared in the generated file Rte_Dem.h
 *
 *********************************************************************************************************************/
/*!
 *  \addtogroup Dem_Main
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

#if !defined (DEM_TYPES_H)                                                                                                       /* COV_MSR_HEADERGUARD TX */
#define DEM_TYPES_H

/* ********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

                                                   /* AUTOSAR standard types */
/* ------------------------------------------------------------------------- */
#include "Std_Types.h"
/* ------------------------------------------------------------------------- */

                                             /* Global configuration options */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg.h"
/* ------------------------------------------------------------------------- */

                                                  /* RTE generated Dem types */
/* ------------------------------------------------------------------------- */
#include "Dem_Swc_Types.h"
/* ------------------------------------------------------------------------- */

/* ********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (DEM_GLOBAL)                                                                                                        /* COV_MSR_COMPATIBILITY TX */
/*! Dem global linkage */
# define DEM_GLOBAL
#endif

#if !defined (DEM_LOCAL)                                                                                                         /* COV_MSR_COMPATIBILITY TX */
/*! Dem private linkage */
# define DEM_LOCAL                               static
#endif

#if !defined (DEM_LOCAL_INLINE)                                                                                                  /* COV_MSR_COMPATIBILITY TX */
/*! Dem private inline linkage */
# define DEM_LOCAL_INLINE                        LOCAL_INLINE
#endif

/* ********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/*! This type is used to identify a specific DemSatellite */
typedef uint8 Dem_SatelliteInfoType;

/*! Compatibility define for Uds status byte */
typedef Dem_UdsStatusByteType Dem_EventStatusExtendedType;

 /*!
  * \defgroup  ServiceInterfaceErrorCode AUTOSAR 4.3.0 Possible Error codes for Service Interfaces (APIs)
  * \{
  */
#define DEM_PENDING                               ((Std_ReturnType)(4U))        /*!< Operation is asynchronous processed (typically needs to be requested again) */
#define DEM_CLEAR_BUSY                            ((Std_ReturnType)(5U))        /*!< Operation ClearDTC reports "Busy" */
#define DEM_CLEAR_MEMORY_ERROR                    ((Std_ReturnType)(6U))        /*!< Operation ClearDTC has "Memory Error" */
#define DEM_CLEAR_FAILED                          ((Std_ReturnType)(7U))        /*!< DTC clearing failed */
#define DEM_WRONG_DTC                             ((Std_ReturnType)(8U))        /*!< Selected DTC value in selected format does not exist or operation is restricted by configuration */
#define DEM_WRONG_DTCORIGIN                       ((Std_ReturnType)(9U))        /*!< Selected DTCOrigin does not exist */
#define DEM_E_NO_DTC_AVAILABLE                    ((Std_ReturnType)(10U))       /*!< There is no DTC configured in the requested format */
#define DEM_E_NO_FDC_AVAILABLE                    ((Std_ReturnType)(14U))       /*!< There is no fault detection counter available for the requested event */
#define DEM_BUFFER_TOO_SMALL                      ((Std_ReturnType)(21U))       /*!< The provided buffer size is too small */
#define DEM_NO_SUCH_ELEMENT                       ((Std_ReturnType)(48U))       /*!< The requested event data is not currently stored (but the request was valid) OR The requested record number is not supported by the event OR The requested DID is not supported by the freeze frame (GetEventFreezeFrameDataEx) */
/*!
  * \}
  */


/*!
 * \defgroup  Dem_DTCTranslationFormatType DTCTranslationFormatType
 * \{
 */
/*! DTC translation format as defined in ISO14229-1 Service 0x19 returned by Dem_GetTranslationType(). */
typedef uint8                                    Dem_DTCTranslationFormatType;
#define DEM_DTC_TRANSLATION_ISO15031_6           ((Dem_DTCTranslationFormatType)(0x00U))  /*!< DTC format ISO 15031-6 / SAE J2012-DA_DTCFormat_00 */
#define DEM_DTC_TRANSLATION_ISO14229_1           ((Dem_DTCTranslationFormatType)(0x01U))  /*!< DTC format ISO 14229-1 */
#define DEM_DTC_TRANSLATION_SAEJ1939_73          ((Dem_DTCTranslationFormatType)(0x02U))  /*!< DTC format SAE J1939-73 */
#define DEM_DTC_TRANSLATION_ISO11992_4           ((Dem_DTCTranslationFormatType)(0x03U))  /*!< DTC format ISO 11992-4 */
#define DEM_DTC_TRANSLATION_J2012DA_FORMAT_04    ((Dem_DTCTranslationFormatType)(0x04U))  /*!< DTC format SAE_J2012-DA_DTCFormat_04 */
/*!
 * \}
 */


/*!
* \defgroup  Dem_DTCRequestType DTCRequestType
* \{
*/
/*! This type is used to request a DTC with specific attributes. */
typedef uint8                                    Dem_DTCRequestType;
#define DEM_FIRST_FAILED_DTC                     ((Dem_DTCRequestType)(0x01U))  /*!< first failed DTC requested */
#define DEM_MOST_RECENT_FAILED_DTC               ((Dem_DTCRequestType)(0x02U))  /*!< most recent failed DTC requested */
#define DEM_FIRST_DET_CONFIRMED_DTC              ((Dem_DTCRequestType)(0x03U))  /*!< first detected confirmed DTC requested */
#define DEM_MOST_REC_DET_CONFIRMED_DTC           ((Dem_DTCRequestType)(0x04U))  /*!< most recently detected confirmed DTC requested */
/*!
* \}
*/



/*!
 * \defgroup  Dem_J1939DcmSetClearFilterType J1939DcmSetClearFilterType
 * \{
 */
/*! The type to distinguish which DTCs gets cleared. */
typedef uint8                                            Dem_J1939DcmSetClearFilterType;
#define DEM_J1939DTC_CLEAR_ACTIVE                        ((Dem_J1939DcmSetClearFilterType)(0x00U))  /*!< Clear active DTCs */
#define DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE             ((Dem_J1939DcmSetClearFilterType)(0x01U))  /*!< Clear previously active DTCs */
#define DEM_J1939DTC_CLEAR_ACTIVE_AND_PREVIOUSLY_ACTIVE  ((Dem_J1939DcmSetClearFilterType)(0x02U))  /*!< Clear active and previously active DTCs */
/*!
 * \}
 */


/*! J1939 indicator lamp status
 *  LampStatus, bits 6- 7 : Malfunction Indicator Lamp Status
 *  LampStatus, bits 4- 5 : Red Stop Lamp Status
 *  LampStatus, bits 2- 3 : Amber Warning Lamp Status
 *  LampStatus, bits 0- 1 : Protect Lamp Status
 *  FlashLampStatus, bits 6- 7 : Malfunction Indicator Lamp Flash Status
 *  FlashLampStatus,bits  4- 5 : Red Stop Lamp Flash Status
 *  FlashLampStatus,bits  2- 3 : Amber Warning Lamp Flash Status
 *  FlashLampStatus,bits  0- 1 : Protect Lamp Flash Status
 */
typedef struct Dem_J1939DcmLampStatusType_s
{
  uint8 LampStatus;            /*!< Lamp status */
  uint8 FlashLampStatus;       /*!< Flash lamp status */
} Dem_J1939DcmLampStatusType;


/*!
 * \defgroup  Dem_J1939DcmSetFreezeFrameFilterType J1939DcmSetFreezeFrameFilterType
 * \{
 */
/*! The type to select the freeze frame filter. */
typedef uint8                                    Dem_J1939DcmSetFreezeFrameFilterType;
#define DEM_J1939DCM_FREEZEFRAME                  ((Dem_J1939DcmSetFreezeFrameFilterType)(0x00U))  /*!< Freeze Frame (DM04) */
#define DEM_J1939DCM_EXPANDED_FREEZEFRAME         ((Dem_J1939DcmSetFreezeFrameFilterType)(0x01U))  /*!< Expanded Freeze Frame (DM25) */
#define DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME ((Dem_J1939DcmSetFreezeFrameFilterType)(0x02U))  /*!< SPNs in Expanded Freeze Frame (DM24) */
/*!
 * \}
 */


/*!
 * \defgroup  Dem_J1939DcmDTCStatusFilterType J1939DcmDTCStatusFilterType
 * \{
 */
/*! The type to distinguish which DTCs should be filtered. */
typedef uint8                                    Dem_J1939DcmDTCStatusFilterType;
#define DEM_J1939DTC_ACTIVE                      ((Dem_J1939DcmDTCStatusFilterType)(0x00U))  /*!< active DTCs */
#define DEM_J1939DTC_PREVIOUSLY_ACTIVE           ((Dem_J1939DcmDTCStatusFilterType)(0x01U))  /*!< previously active DTCs */
#define DEM_J1939DTC_PENDING                     ((Dem_J1939DcmDTCStatusFilterType)(0x02U))  /*!< pending DTCs */
#define DEM_J1939DTC_PERMANENT                   ((Dem_J1939DcmDTCStatusFilterType)(0x03U))  /*!< permanent DTCs */
#define DEM_J1939DTC_CURRENTLY_ACTIVE            ((Dem_J1939DcmDTCStatusFilterType)(0x04U))  /*!< currently failed DTCs */
/*!
 * \}
 */

/*! This structure represents all data elements of the DM05 message. The encoding is according to SAE J1939-73 */
typedef struct Dem_J1939DcmDiagnosticReadiness1Type_s
{
  uint8 ActiveTroubleCodes;                          /*!< Number of active DTCs */
  uint8 PreviouslyActiveDiagnosticTroubleCodes;      /*!< Number of previously active DTCs */
  uint8 OBDCompliance;                               /*!< OBD Compliance */
  uint8 ContinuouslyMonitoredSystemsSupport_Status;  /*!< Identifies the continuously monitored system support and status */
  uint16 NonContinuouslyMonitoredSystemsSupport;     /*!< Identifies the non-continuously monitored systems support */
  uint16 NonContinuouslyMonitoredSystemsStatus;      /*!< Identifies the non-continuously monitored systems status */
} Dem_J1939DcmDiagnosticReadiness1Type;                                                                                          /* PRQA S 0779 */ /* MD_MSR_5.1_779_API */

/*! This structure represents all data elements of the DM21 message. The encoding is according to SAE J1939-73 */
typedef struct Dem_J1939DcmDiagnosticReadiness2Type_s
{
  uint16 DistanceTraveledWhileMILisActivated;        /*!< The kilometers accumulated while the MIL is activated */
  uint16 DistanceSinceDTCsCleared;                   /*!< Distance accumulated since emission related DTCs were cleared */
  uint16 MinutesRunbyEngineWhileMILisActivated;      /*!< Accumulated count (in minutes) while the MIL is activated (not off) */
  uint16 TimeSinceDiagnosticTroubleCodesCleared;     /*!< Engine run-time accumulated since emission related DTCs were cleared */
} Dem_J1939DcmDiagnosticReadiness2Type;                                                                                          /* PRQA S 0779 */ /* MD_MSR_5.1_779_API */

/*! This structure represents all data elements of the DM26 message. The encoding is according to SAE J1939-73 */
typedef struct Dem_J1939DcmDiagnosticReadiness3Type_s
{
  uint16 TimeSinceEngineStart;                       /*!< Time since key-on that the engine has been running. */
  uint8 NumberofWarmupsSinceDTCsCleared;             /*!< Number of OBD warm-up cycles since all DTCs were cleared */
  uint8 ContinuouslyMonitoredSystemsEnableCompletedStatus; /*!<  Identifies the continuously monitored system enable/completed support and status. */
  uint16 NonContinuouslyMonitoredSystemsEnableStatus;  /*!< Enable status of non-continuous monitors this monitoring cycle */
  uint16 NonContinuouslyMonitoredSystems;            /*!< Completion status of non-continuous monitors this monitoring cycle */
} Dem_J1939DcmDiagnosticReadiness3Type;                                                                                          /* PRQA S 0779 */ /* MD_MSR_5.1_779_API */

/*! Function pointer type for clear event allowed callbacks */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_ClearEventAllowedFPtrType)(
                                                   P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) /* [out] isAllowed */
                                                 );

/*! Function pointer type for clear event allowed callbacks */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_ClearDtcNotificationFPtrType)(
                                                   uint32 /* [in] DTC*/,
                                                   Dem_DTCFormatType /* [in] DTCFormat*/,
                                                   Dem_DTCOriginType /* [in] DTCOrigin*/
                                                 );

/*! Function pointer type for get fault detection counter callbacks */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_GetFDCFPtrType)(
                                                   P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) /* [out] FDC */
                                                 );

/*! Function pointer type for global monitor status changed notifications */
typedef P2FUNC(void, DEM_APPL_CODE,              Dem_GlobalTriggerOnMonitorStatusFPtrType)(
                                                   Dem_EventIdType /* [in] EventId*/
                                                 );

/*! Function pointer type for event status changed notifications */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_EventStatusChangedFPtrType)(
                                                   Dem_UdsStatusByteType /* [in] oldStatus */,
                                                   Dem_UdsStatusByteType /* [in] newStatus */
                                                 );

/*! Function pointer type for DTC status changed notifications */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_DtcStatusChangedFPtrType)(
                                                   uint32 /* [in] DTC */,
                                                   Dem_DTCStatusMaskType /* [in] oldStatus */,
                                                   Dem_DTCStatusMaskType /* [in] newStatus */
                                                 );

/*! Function pointer type for event data changed notifications */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_EventDataChangedFPtrType)(
                                                   void
                                                 );

/*! Function pointer type for global event status changed notifications */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_GlobalStatusChangedFPtrType)(
                                                   Dem_EventIdType /* [in] EventId*/,
                                                   Dem_UdsStatusByteType /* [in] oldStatus */,
                                                   Dem_UdsStatusByteType /* [in] newStatus */
                                                 );

/*! Function pointer type for global event data changed notifications */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_GlobalDataChangedFPtrType)(
                                                   Dem_EventIdType /* [in] EventId*/
                                                 );

/*! Function pointer type for init monitor for event notifications */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_InitMonitorForEventFPtrType)(
                                                   Dem_InitMonitorReasonType /* [in] initReason */
                                                 );

/*! Function pointer type for init monitor for function notifications */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_InitMonitorForFuncFPtrType)(
                                                   void
                                                 );

/*! Function pointer type for control DTC setting changed notifications */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_ControlDtcSettingChangedFPtrType)(
                                                   boolean
                                                 );

/*! Function pointer type for C/S read data callbacks */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_ReadDataStandardFPtrType)(
                                                   P2VAR(uint8, DEM_NVM_DATA, AUTOMATIC) /* [out] data */
                                                 );

/*! Function pointer type for C/S read data callbacks with additional event argument */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_ReadDataExtendedFPtrType)(
                                                   Dem_EventIdType /* [in] EventId*/,
                                                   P2VAR(uint8, DEM_NVM_DATA, AUTOMATIC) /* [out] data */
                                                   );

/*! Function pointer type for S/R read data callbacks for data type boolean */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_ReadDataSRBooleanFPtrType)(
                                                P2VAR(boolean, DEM_NVM_DATA, AUTOMATIC) /* [out] data */
                                                );

/*! Function pointer type for S/R read data callbacks for data type sint8 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_ReadDataSRSint8FPtrType)(
                                                P2VAR(sint8, DEM_NVM_DATA, AUTOMATIC) /* [out] data */
                                                );

/*! Function pointer type for S/R read data callbacks for data type sint16 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_ReadDataSRSint16FPtrType)(
                                                P2VAR(sint16, DEM_NVM_DATA, AUTOMATIC) /* [out] data */
  );

/*! Function pointer type for S/R read data callbacks for data type uint16 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_ReadDataSRUint16FPtrType)(
                                                P2VAR(uint16, DEM_NVM_DATA, AUTOMATIC) /* [out] data */
                                                );

/*! Function pointer type for S/R read data callbacks for data type sint32 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_ReadDataSRSint32FPtrType)(
                                                P2VAR(sint32, DEM_NVM_DATA, AUTOMATIC) /* [out] data */
                                                );

/*! Function pointer type for S/R read data callbacks for data type uint32 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_ReadDataSRUint32FPtrType)(
                                                P2VAR(uint32, DEM_NVM_DATA, AUTOMATIC) /* [out] data */
                                                );

/*! Common function pointer type for read data callbacks. Must be casted to the correct type before it can be called */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE,    Dem_ReadDataFPtrType)(void);

/*! Data pointer into Dem defined RAM */
typedef P2VAR(uint8, TYPEDEF, DEM_VAR_NOINIT)    Dem_DataPtrType;
/*! Data pointer into Nv backed RAM */
typedef P2VAR(uint8, TYPEDEF, DEM_NVM_DATA)      Dem_NvDataPtrType;
/*! Data pointer into Nv backed RAM */
typedef P2VAR(sint8, TYPEDEF, DEM_NVM_DATA)      Dem_SignedNvDataPtrType;
/*! Data pointer into RAM provided by Dcm */
typedef P2VAR(uint8, TYPEDEF, DEM_DCM_DATA)      Dem_DcmDataPtrType;
/*! Common data pointer into RAM - must be able to point to all used RAM locations */
typedef P2VAR(uint8, TYPEDEF, DEM_SHARED_DATA)   Dem_SharedDataPtrType;

/*! Common read-only data pointer Dem defined RAM */
typedef P2CONST(uint8, TYPEDEF, DEM_CONST)       Dem_ConstDataPtrType;
/*! Common read-only data pointer into RAM - must be able to point to all used RAM locations */
typedef P2CONST(uint8, TYPEDEF, DEM_SHARED_DATA) Dem_ConstSharedDataPtrType;


/* ********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/* ********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif  /* DEM_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Types.h
 *********************************************************************************************************************/
