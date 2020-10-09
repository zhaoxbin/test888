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
/*!  Project    MICROSAR Diagnostic Event Manager (Dem)
 *
 *  \defgroup   Dem_Master    Dem Master Functionality
 *  \{
 *  \}
 *  \defgroup   Dem_Shared    Dem Shared Functionality
 *  \{
 *  \}
 *
 *  \ingroup    Dem_Shared
 *  \defgroup   Dem_Main Dem API
 *  \{
 *  \file       Dem.h
 *  \brief      Implementation header file for the MICROSAR Dem
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
 *  04.00.00  2012-06-29  vismhe  ESCAN00057159 AR4-82: DEM 4.x
 *                        visade  ESCAN00057159 AR4-82: DEM 4.x
 *  04.01.00  2012-09-07  vismhe  ESCAN00061254 VersionInfo API returns wrong version number
 *            2012-09-14  vismhe  ESCAN00061429 Autostart cycle has no effect
 *            2012-09-20  vismhe  ESCAN00061565 Wrong snapshot record number reported for 19 03
 *            2012-10-26  vismhe  ESCAN00062489 Compiler warning: Condition is always true
 *            2012-10-26  vismhe  ESCAN00062490 Compiler warning: Condition is always true
 *            2012-10-26  vismhe  ESCAN00062483 Unexpected ClearAllowed callback
 *  04.02.00  2012-11-05  vismhe  ESCAN00062646 Compiler warning: Function "Dem_Queue_CancelOperation" was declared but never referenced
 *            2012-11-05  vismhe  ESCAN00062647 Compiler warning: Variable "Dem_Mem_PrimaryInfo" was declared but never referenced
 *            2012-11-05  vismhe  ESCAN00062644 Compiler warning: Variable "lResult" was set but never used
 *            2012-11-06  vismhe  ESCAN00062645 Compiler warning: Variable "lOldEventStatus" was set but never used
 *            2012-11-06  visade  ESCAN00062771 Memory corruption after call of Dem_SetDTCFilter()
 *            2012-12-07  vismhe  ESCAN00061769 AR4-207: Support VCC Diagnostic specification and required Diagnostic RFCs
 *  04.03.00  2013-02-04  visdth  ESCAN00061747 OBDII Support: IUMPR handling added
 *            2013-03-05  vismhe  ESCAN00065600 DET error DEM_E_UNINIT in Dem_Mainfunction
 *            2013-03-08  visade  ESCAN00061747 AR4-55: DEM - OBDII Support
 *            2013-03-13  visdth  ESCAN00063590 OBD IUMPR Counting Misbehavior
 *            2013-03-13  visdth  ESCAN00065851 Support User Controlled Warning Indicator Request
 *            2013-03-13  visdth  ESCAN00065853 Support suppression of permanent DTC storage
 *            2013-03-13  visdth  ESCAN00065854 Support MIL Groups
 *            2013-03-13  vismhe  ESCAN00065867 Allow PendingDTC independent from event storage
 *            2013-03-13  vismhe  ESCAN00065868 Support different DTC aging protocols
 *  04.04.00  2013-04-02  visade  ESCAN00066314 Compiler warning: multiple dead assignments within Dem.c
 *            2013-04-03  vismhe  ESCAN00065209 AR4-375: Add Support of "Suppress DTC" in Dem
 *            2013-04-10  visdth  ESCAN00066201 Extension of Interface to read IUMPR data
 *            2013-04-26  vismhe  ESCAN00067007 Secondary Memory DTCs do not report Severity and FunctionalUnit information
 *  04.04.01  2013-05-15  visade  ESCAN00067368 Compiler error: OdometerAtClear is not a member of Dem_Cfg_AdminDataType_s
 *            2013-05-15  visade  ESCAN00067372 Compiler error: Dem_Cfg_ObdGetGlobalDenominator() not a modifiable lvalue
 *            2013-05-15  visade  ESCAN00067155 Missing type definitions if Dem is used without Rte
 *            2013-05-15  visade  ESCAN00067025 Include FiM.h only if IUMPR or FiM notification is enabled
 *            2013-05-22  vismhe  ESCAN00067180 Compiler warning: uninitialized local variable 'lDtcStatusNew' used
 *            2013-05-22  vismhe  ESCAN00067354 Compilation error: Undefined symbol
 *            2013-05-22  vismhe  ESCAN00067345 Compilation error: Undefined symbol
 *            2013-05-22  vismhe  ESCAN00067459 Compiler warning: dead assignment to "lReturnValue" eliminated
 *  04.05.00  2013-06-03  visade  ESCAN00067673 Change Permanent Activation Distance from absolute to relative distance calculation
 *            2013-06-10  visade  ESCAN00067618 Out-parameter not initialized in Dem_GetIUMPRGeneralData
 *            2013-06-19  visdth  ESCAN00068159 MIL Group trip counter not reset on ClearDTC
 *            2013-06-19  vismhe  ESCAN00067715 AR4-418: Support Event Combination Type 1
 *            2013-06-19  vismhe  ESCAN00068164 Immediately persist event status on ClearDTC
 *            2013-06-19  vismhe  ESCAN00068389 Extended use of Dem_GetSeverityOfDTC and Dem_GetFunctionalUnitOfDTC
 *            2013-06-27  vismhe  ESCAN00068390 OperationCycles not stopped during Shutdown
 *            2013-09-18  vismhe  ESCAN00070478 Unexpected value for EventStatusChanged and DTCStatusChanged callbacks
 *  04.05.01  2013-07-03  vismhe  ESCAN00068511 Compiler error: Dem.c: 'Dem_Cbk_InitMonitor' undefined
 *  04.05.02  2013-07-03  vismhe  ESCAN00068562 Mode 0x02 does not return data
 *            2013-07-04  vismhe  ESCAN00068508 IUMPR: Numerator is incremented without qualified test result
 *            2013-07-04  vismhe  ESCAN00068569 Suppression or UserControlled WIR has no effect
 *  04.05.03  2013-07-10  visade  ESCAN00068885 Provide OBD FreezeFrame in 0x1904 although Snapshots Records are disabled
 *            2013-07-18  visade  ESCAN00069154 Missing cast truncates OBD DTC number
 *            2013-07-22  vismhe  ESCAN00069132 Mixed internal and external data records are stored misaligned
 *            2013-07-22  vismhe  ESCAN00069237 Allow to override static / inline specific to Dem module
 *            2013-07-23  vismhe  ESCAN00069270 Too many increments of occurrence counter
 *            2013-07-23  vismhe  ESCAN00069271 DTC starts aging although it is still pending
 *            2013-07-23  visdth  ESCAN00068577 IUMPR Counters may be incremented more than once per DCY
 *  04.06.00  2013-07-24  visade  ESCAN00069311 Missing DID/PID validation check in Dem_GetEventFreezeFrameData()
 *            2013-07-24  visade  ESCAN00068636 AR4-419: Support Multiple OBD Freeze Frames
 *            2013-08-02  visade  ESCAN00069587 The code shall compile if NVM support is disabled and OBD support is enabled
 *            2013-08-06  visade  ESCAN00069626 OBD DTC Status does not qualify
 *            2013-08-07  visade  ESCAN00069423 OBD relevant data is not reset on configuration change
 *            2013-08-08  visade  ESCAN00069683 Erroneous indicator decrement during Mode 0x04
 *            2013-08-14  vismhe  ESCAN00069801 BSW error reporting after PreInit and before Init not possible
 *  05.00.00  2013-09-03  vismhe  ESCAN00068165 Compiler warning: Condition is always constant
 *            2013-09-03  vismhe  ESCAN00068395 AR4-292: Reporting of DET and DEM errors via DLT
 *            2013-09-03  vismhe  ESCAN00068416 AR4-420: Postbuild Loadable Support
 *            2013-09-03  vismhe  ESCAN00068465 AR4-371: Support signal interface
 *            2013-09-03  vismhe  ESCAN00068526 AR4-409: Support of OEM Volvo AB
 *            2013-09-03  vismhe  ESCAN00068530 AR4-542: Support of OEM Ford
 *            2013-09-03  vismhe  ESCAN00069882 Internal event is not cleared
 *            2013-09-03  vismhe  ESCAN00069989 Compiler warning: variable "lEntry" was set but never used
 *            2013-09-03  vismhe  ESCAN00069805 Add verification of EventKind to ReportErrorStatus and SetEventStatus
 *            2013-09-04  visdth  ESCAN00070048 OBD IUMPR: reading the same ratio several times is not possible
 *            2013-09-11  vismhe  ESCAN00070346 AgingCounter is reported with incorrect value
 *            2013-09-16  vismhe  ESCAN00069943 Delay WarmUpCycle until restart of Driving Cycle
 *            2013-09-16  vismhe  ESCAN00070219 Reset PID 0x21 if no OBD DTC requests the MIL for 40 warm-up cycles
 *            2013-09-19  vismhe  ESCAN00070500 Remove DET for consecutive qualified DCY reports
 *            2013-09-26  vismhe  ESCAN00070686 ConfirmedDTC is reset on initialization
 *            2013-10-02  vismhe  ESCAN00070834 Incorrect event displaced on overflow
 *            2013-11-27  vismhe  ESCAN00072203 Memory overwritten during initialization
 *  05.00.01  2013-11-13  vismhe  ESCAN00071873 DTCs do not age
 *            2013-11-14  vismhe  ESCAN00071948 Compiler warning: Definition different from declaration
 *  05.01.00  2013-10-17  visade  ESCAN00071182 Incorrect MIL group behavior after ClearAllDTCs
 *            2013-10-22  visade  ESCAN00071161 Change initialization of PID 0x31
 *            2013-10-22  visade  ESCAN00071162 Support ClearSingleDtc for OBD ECUs
 *            2013-10-25  visade  ESCAN00071244 Provide Dem internal EventId in Environmental Data
 *            2013-10-25  visade  ESCAN00071425 Provide OBD DTC in Environmental Data
 *            2013-10-30  visade  ESCAN00071346 Support application interface providing the permanent DTC activation state
 *            2013-11-20  vismhe  ESCAN00072084 Incorrect value for maximum FDC in current cycle
 *            2013-11-20  vismhe  ESCAN00071550 Incorrect status report handling for BSW errors
 *            2013-11-21  visade  ESCAN00072122 Stored UDS DTC does not have Confirmed and WarningIndicator bit set
 *            2013-11-28  vismhe  ESCAN00072310 Incorrect PID21 handling
 *  06.00.00  2014-02-04  visade  ESCAN00072994 Admin data is not persisted during shutdown if no Operation Cycle was started
 *            2014-02-04  vismhe  ESCAN00073575 Compile/Validation error: Incompatible prototypes
 *            2014-02-04  vismhe  ESCAN00073578 Rework NV MemoryAbstraction
 *            2014-02-04  vismhe  ESCAN00070873 AR4-402: Support of OEM Ford
 *            2014-02-04  visade  ESCAN00071380 AR4-465: Support for J1939 Diagnostics - API to DCM according AR 4.1.2
 *            2014-02-04  visade  ESCAN00071379 AR4-465: Support for J1939 Diagnostics
 *            2014-02-14  visade  ESCAN00073721 Driving cycle remains qualified after automatic end
 *            2014-02-18  vismhe  ESCAN00073792 Diagnostics locked when clearing DTCs
 *            2014-02-18  vismhe  ESCAN00079177 Compiler warning: Name Dem_DTCGroupType has already been declared
 *  06.01.00  2014-03-10  visdth  ESCAN00073613 Numerator is only incremented with fulfilled General Denominator conditions
 *            2014-03-12  vismhe  ESCAN00074193 NRC "conditions not correct" for services 19 04, 19 06
 *            2014-03-12  vismhe  ESCAN00074203 AR4-673: Diag_Asr4J1939Dcm + Diag_Asr4Dem shall work without Diag_Asr4Dcm
 *            2014-03-13  vismhe  ESCAN00074248 Compiler error: Missing type definition Dem_J1939DcmDiagnosticReadinessNType
 *            2014-03-12  visade  ESCAN00073876 Lock Numerator increment during active tester communication
 *            2014-03-13  visade  ESCAN00074253 Compile error if Aging is configured to start at passed
 *            2014-03-21  vismhe  ESCAN00074493 DTC does not re-enable after suppression
 *            2014-03-21  vismhe  ESCAN00074494 DTCs do not respect multiple trips
 *            2014-03-25  vismhe  ESCAN00074541 Hide Dependent OBD DTCs in UDS diagnostic services
 *            2014-03-25  vismhe  ESCAN00074410 Incorrect old DTC status in DtcStatusChangeCbk
 *            2014-03-26  vismhe  ESCAN00074566 Event does not debounce correctly
 *            2014-03-27  vismhe  ESCAN00074598 Significance value reported incorrectly in extended records
 *            2014-03-28  vismhe  ESCAN00074644 Time debounced events report wrong maximum debounce value
 *            2014-03-28  vismhe  ESCAN00074647 Occurrence Counter reported incorrectly
 *            2014-03-28  vismhe  ESCAN00073289 Add Operating Hours to Standardized Environmental Data
 *            2014-04-02  visade  ESCAN00074740 Possible out of bound access for variable Dem_Cfg_ObdIumprData.Status
 *            2014-04-02  vismhe  ESCAN00074743 Wrong result when reporting invalid event status
 *  06.02.00  2014-04-23  vismhe  ESCAN00074202 AR4-670: Support DTC Pre-storage
 *            2014-04-23  vismhe  ESCAN00075221 Support 16 Operation Cycles
 *            2014-04-23  vismhe  ESCAN00075100 Usage of OSEK OS symbol can cause errors during preprocessing
 *            2014-04-24  vismhe  ESCAN00075205 Provide API Dem_SetEventAvailable
 *            2014-04-24  vismhe  ESCAN00075207 Suppressed Events do not confirm
 *            2014-04-28  visade  ESCAN00073569 Do not track the ratio for suppressed DTCs/Events
 *            2014-05-05  vismhe  ESCAN00075368 Incorrect new DTC status reported in DTC status changed callback
 *            2014-05-07  visade  ESCAN00075400 PID 0x21 is not cleared if MIL is not triggered
 *            2014-05-08  visade  ESCAN00074965 Loop underrun in function Dem_EnablePermanentStorage()
 *            2014-06-04  vismhe  ESCAN00075786 Dem does not compile if PID 0x21 is not enabled
 *            2014-05-21  vismhe  ESCAN00075810 OBD Freeze Frame is not cleared correctly
 *            2014-06-04  vismhe  ESCAN00076016 Compile Error: Multiple errors for OBD DEM with feature OBD disabled
 *            2014-06-04  vismhe  ESCAN00076021 Compiler error: Undefined preprocessor identifier in Dem_Dcm.h
 *  07.00.00  2014-06-25  vismhe  ESCAN00076615 AR4-732: Application Trigger for NV Synchronization
 *            2014-06-25  vismhe  ESCAN00076615 AR4-732: Extend aging behavior to not require TFTOC==false
 *            2014-06-30  vismhe  ESCAN00076615 AR4-732: Added support for Clear DTC Limitation
 *            2014-07-02  vismhe  ESCAN00076615 AR4-732: Added support FDC trip / once per cycle
 *            2014-06-25  vismhe  ESCAN00076450 Compiler error: inline function's body is not declared previously
 *            2014-06-30  vismhe  ESCAN00077724 AR4-698: Move InitPointer to Dem_Init
 *            2014-07-02  visade  ESCAN00076529 AR4-607: Option to store the Fault Detection Counter in NVRAM
 *            2014-07-02  vismhe  ESCAN00076664 Improve DTC status recovery after power loss
 *            2014-07-02  visade  ESCAN00076667 Remove support of DEM_DTC_FORMAT_OBD from DTC suppression
 *            2014-07-10  vismhe  ESCAN00076878 Improve robustness against Shutdown
 *            2014-07-11  vismhe  ESCAN00076920 Wrong result when extended record is not stored
 *            2014-07-11  vismhe  ESCAN00076982 Implausible value for extended data records mapped to aging counter
 *            2014-07-23  visade  ESCAN00076612 AR4-741: Support multiple J1939 nodes in DEM and J1939DCM
 *            2014-08-07  vismhe  ESCAN00077685 Improve robustness of disable DTC record update
 *            2014-08-07  visade  ESCAN00077680 Do not report previously OBD relevant DTCs in Mode 0x0A
 *            2014-08-08  vismhe  ESCAN00077722 Compiler warning: 'EventId' : unreferenced formal parameter
 *            2014-08-12  vismhe  ESCAN00074759 Feature J1939 and EventCombination does not work together
 *            2014-08-25  vismhe  ESCAN00074190 Restore ConfirmedBit when StorageTrigger == Confirmed
 *            2014-08-25  vismhe  ESCAN00077999 Service 19 02 does not report all DTCs
 *            2014-09-12  vismhe  ESCAN00078381 Dem_GetIUMPRGeneralData returns an incorrect value for 'NumberOfRatios'
 *            2014-09-30  vismhe  ESCAN00078498 Recover external visible OBD Freeze Frame if event in memory is not OBD relevant by configuration (anymore)
 *            2014-10-01  visade  ESCAN00078639 Add NVRAM Recovery for Permanent Memesry
 *            2014-10-10  vismhe  ESCAN00078806 Wrong event displaced from event memory
 *            2014-10-13  vismhe  ESCAN00078902 Event availability not working with combined events
 *            2014-10-13  vismhe  ESCAN00068635 Compiler warning: expression always constant
 *            2014-10-13  vismhe  ESCAN00070124 Compiler warning: conditional expression is constant
 *            2014-10-13  vismhe  ESCAN00076527 AR4-572: Ford/Mazda Feature Complete - Ford in AR environment
 *            2014-10-13  vismhe  ESCAN00076605 AR4-669: Support for J1939 Diagnostics
 *            2014-10-13  vismhe  ESCAN00080571 Memory corruption when aging DTCs
 *            2015-01-14  vismhe  ESCAN00081016 Out of bound memory read access for Dem_Cfg_ObdIumprData.Status
 *  08.00.00  2014-11-24  vismhe  ESCAN00079766 Remove API Dem_GetNextIUMPRRatioData
 *            2014-11-24  vismhe  ESCAN00079776 Combined events not correctly unavailable in postbuild configuration
 *            2014-11-24  vismhe  ESCAN00079653 Change return value for API Dem_SetOperationCycleState()
 *            2014-11-24  visade  ESCAN00079787 Compiler warning: Dead assignment in function Dem_Data_PermanentEntryFind()
 *            2014-12-04  visade  ESCAN00079994 1-Trip DTC without the need for a qualified driving cycle
 *            2014-12-04  vismhe  ESCAN00079778 A Monitor Report is lost
 *            2014-12-05  vismhe  ESCAN00080187 FEAT-412 Support latching TestFailed of confirmed DTCs
 *            2014-12-11  vismhe  ESCAN00080187 FEAT-412 Support Freezing/Resetting the debouncing state by API
 *            2014-12-11  vismhe  ESCAN00080187 FEAT-412 Support init monitor notification when debouncing is reenabled
 *            2014-12-11  vismhe  ESCAN00080187 FEAT-412 Transport NvM error result to ClearDTC Api
 *            2014-12-17  visade  ESCAN00080224 Support of 3 Byte OBD DTC for DEM internal data element
 *            2015-01-12  vismhe  ESCAN00079539 FEAT-1200: Support of length information in Snapshot
 *            2015-01-12  vismhe  ESCAN00079539 FEAT-1200: Option to rest TF bit on operation cycle start
 *            2015-01-14  vismhe  ESCAN00080283 FEAT-427: Refactoring of large functions, rework function headers
 *            2015-01-21  visade  ESCAN00080705 Permanent DTC without permanent memory activation
 *            2015-01-21  visade  ESCAN00080718 Remove DCY wait state for permanent DTCs after CodeClear
 *            2015-01-21  visade  ESCAN00080178 Add DCY qualification as permanent DTC erase condition
 *            2015-01-28  vismhe  ESCAN00080898 Out of bounds memory read access
 *            2015-02-06  visade  ESCAN00081089 Improve NVRAM recovery for combined events in permanent memory
 *            2015-02-06  visade  ESCAN00081024 IUMPR - erroneous numerator increment
 *            2015-02-12  vismhe  ESCAN00081038 Event reports are not processed correctly before Dem_Init()
 *            2015-02-12  vismhe  ESCAN00081188 Keep auto-start cycles active after shutdown
 *            2015-02-15  vismhe  ESCAN00080245 FEAT-473: Support default initialization for event available state
 *            2015-02-18  vismhe  ESCAN00081328 Critical section is kept in lock state
 *            2015-02-20  vismhe  ESCAN00080555 Compiler warning: 'FreezeFrameIndex' : unreferenced formal parameter
 *            2015-02-23  visade  ESCAN00081400 Make active DTC immediately visible after permanent memory activation
 *            2015-02-25  visade  ESCAN00079859 FEAT-643: Support WWH OBD (Beta)
 *            2015-02-27  vismhe  ESCAN00081529 Blocking of ClearDTC while processing ClearSingleDTC
 *            2015-03-10  vismhe  ESCAN00081708 DTC aging starts too early
 *            2015-03-19  vismhe  ESCAN00079199 Compiler warning: 'FreezeFrameIndex' : unreferenced formal parameter
 *            2015-03-19  vismhe  ESCAN00079200 Compiler warning: 'SRecIndex' : unreferenced formal parameter
 *  09.00.00  2015-03-24  visade  ESCAN00082399 FEAT-1446: Make OBD II Freeze Frame optional in Service 0x1904
 *            2015-03-31  visade  ESCAN00082399 FEAT-1446: Optionally restart DCY on ClearAllDTCs
 *            2015-04-01  vismhe  ESCAN00082199 Compiler warning: Unitialized variable lReturnValue
 *            2015-04-08  visade  ESCAN00082399 FEAT-1446: Add option to displace Pending OBD Freeze Frame
 *            2015-04-09  vismhe  ESCAN00082289 Displacement of wrong DTC
 *            2015-04-09  vismhe  ESCAN00082319 Compiler error: Missing 'else' block
 *            2015-04-20  vismhe  ESCAN00082534 Compiler error or warning:  initializer type incompatible with object type
 *            2015-04-20  vismhe  ESCAN00082346 FEAT-56: Support data callbacks with EventId parameter
 *            2015-04-23  vismhe  ESCAN00082348 FEAT-285: Support healing for events without indicator
 *            2015-04-23  vismhe  ESCAN00082348 FEAT-285: Support debouncing while enable conditions are locked
 *            2015-05-05  visade  ESCAN00082811 Environmental data is missing for confirmed DTC
 *            2015-05-22  vismhe  ESCAN00082348 FEAT-285: Support entry retry
 *            2015-06-03  vismhe  ESCAN00082346 FEAT-56: Support data callbacks without NV storage
 *            2015-06-03  vismhe  ESCAN00082346 FEAT-56: Support JLR specific snapshot trigger
 *            2015-06-09  vismhe  ESCAN00082346 FEAT-56: Support aging at passed trigger for aging target == 0
 *            2015-06-26  vismhe  ESCAN00079889 Status change callback called without change of status
 *            2015-06-29  visade  ESCAN00083654 1-Trip DTC not available in Mode 0x0A
 *            2015-07-02  vismhe  ESCAN00083400 Compiler warning:  narrowing or signed-to-unsigned type conversion found
 *            2015-07-06  vismhe  ESCAN00083803 Combined events age without completed test
 *            2015-07-08  vismhe  ESCAN00082762 Compiler error: E0516: Zero sized structure 'DebounceInfo', E0823: Too long macro expansion 'VStdMemSet'
 *            2015-07-21  vismhe  ESCAN00084110 DID length is not included in snapshot record
 *            2015-07-21  visade  ESCAN00082355 FEAT-397: Support of WWH-OBD in Dcm and Dem [AR4-749] incl. Variant Handling for WWH-OBD use case
 *  10.00.00  2015-08-28  vismhe  ESCAN00084816 Compiler error: struct has no member SnapshotData
 *            2015-08-28  vismhe  ESCAN00084822 Compiler error: struct has no member MaxDebounceValue, missing symbols DEM_ESM_TEST/SET_FDC_MAX
 *            2015-08-28  vismhe  ESCAN00084823 Compiler error: undefined symbol Dem_Mem_SetOdometerMilOn
 *            2015-08-28  vismhe  ESCAN00084837 Compiler error: undefined symbol Dem_Cfg_GlobalIndicatorStates
 *            2015-08-28  vismhe  ESCAN00084839 Compiler error: undefined symbol Dem_Data_CollectDid
 *            2015-08-31  vismhe  ESCAN00084885 Compiler error: undefined symbol lEventId
 *            2015-09-02  vismhe  ESCAN00084948 Compiler error: syntax error in Dem_J1939Dcm_GetNextDTCwithLampStatus
 *            2015-09-03  vismhe  ESCAN00084954 Compiler error: undefined symbol 'Dem_Esm_TestEventHealed'
 *            2015-09-03  vismhe  ESCAN00084615 ClearDTC for secondary memory deletes wrong DTCs
 *            2015-09-10  vismhe  ESCAN00085138 DTCs not stored on FaultDetectionCounter Threshold
 *            2015-09-11  vismhe  ESCAN00085160 Compiler error: undefined symbol 'lNewEventStatus'
 *            2015-09-11  vismhe  ESCAN00085162 Compiler error: undefined symbol 'Dem_Queue_CalculatePid4E'
 *            2015-09-14  vismhe  ESCAN00084044 Indicator is reported active without requesting DTC
 *            2015-09-14  vismhe  ESCAN00085009 Support non-volatile availability setting
 *            2015-11-10  vismhe  ESCAN00085612 Out of bounds memory write access
 *            2015-11-10  vismhe  ESCAN00085604 Statistic values 'Failed Cycles counter', 'Consecutive Failed Cycles Counter' do not update correctly
 *            2015-11-10  vismhe  ESCAN00085552 Missing Data after DTC re-occurrence
 *            2015-11-20  vismhe  ESCAN00086554 Remove initailaziation check from API Dem_NvM_InitObdPermanentData
 *            2015-11-26  vismhe  ESCAN00086756 Code depends on undefined behavior
 *            2015-11-26  vismhe  ESCAN00086757 Dem calls FiM_DemTriggerOnEventStatus before initialization
 *            2015-11-26  vismhe  ESCAN00086808 Cycles since last failed not updated correctly
 *            2015-11-26  vismhe  ESCAN00086603 Compiler warning: variable "lOldStatus/lNewStatus" was set but never used
 *            2015-11-26  vismhe  ESCAN00086539 Compiler warning: variable 'lSRecId'/'lCfgSRecIndex' was set but never used
 *            2015-11-26  vismhe  ESCAN00086537 Compiler warning: variable 'lSRecId' was set but never used
 *            2015-11-26  visanh  ESCAN00085828 FEAT-1334: Support Time-series Snapshot Data Records
 *            2015-11-26  visanh  ESCAN00085143 FEAT-1527: SafeBSW Step 3
 *            2015-11-26  vismhe  ESCAN00085143 FEAT-1527: SafeBSW Step 3
 *            2015-11-30  vismhe  ESCAN00086885 Dcm cannot lock DTCs (unexpected NRC22)
 *            2015-12-14  vismhe  ESCAN00086336 Aging behavior for AgingTarget==0 is incorrect
 *            2015-12-14  vismhe  ESCAN00086887 Allow Dem_SetWIRStatus during ControlDTCSetting
 *  11.00.00  2016-01-14  vismhe  ESCAN00087477 Cannot report event status
 *            2016-01-14  vismhe  ESCAN00087481 Compiler error: Undefined symbol Dem_Esm_TestEventHealed
 *            2016-01-20  visanh  ESCAN00087429 Memory overwritten when using internal data elements in time series snapshot records
 *            2016-01-20  visanh  ESCAN00087534 Time Series Snapshot Records cannot be used without time based debouncing
 *            2016-02-03  vismhe  ESCAN00087637 FEAT-1472: Implement RoE for VAG
 *            2016-02-29  vismhe  ESCAN00088591 Permanent memory initialization pattern is overwritten
 *            2016-02-29  visanh  ESCAN00087794 FEAT-1688: SafeBSW Step 4
 *            2016-02-29  vismhe  ESCAN00087794 FEAT-1688: SafeBSW Step 4
 *            2016-03-07  vismhe  ESCAN00087325 Incorrect behavior for disablement of numerators and denominators after Clear DTC
 *            2016-03-11  vismhe  ESCAN00087868 FEAT-1605: Support DM5/27/53/54/55 in J1939Dcm
 *            2016-03-15  vismhe  ESCAN00088915 Fault data updated too often
 *            2016-03-23  vismhe  ESCAN00089043 Combined DTC incorrectly sets Pending and Confirmed bit
 *            2016-03-23  vismhe  ESCAN00089057 WarmUp cycle not restarted automatically
 *  12.00.00  2016-03-29  visanh  ESCAN00088997 FEAT-1770: Support up to 255 Enable and Storage Conditions
 *            2016-04-07  visanh  ESCAN00089288 Incorrect Maximum FDC Since Last Clear
 *            2016-04-08  visade  ESCAN00089273 FEAT-1723: Support clear PDTC without PFC if event has a ratio attached
 *            2016-04-11  visade  ESCAN00089273 FEAT-1723: Support IUMPR in environmental data
 *            2016-04-11  visade  ESCAN00089273 FEAT-1723: Support OBD DTCs that do not trigger the MIL (Black MIL)
 *            2016-04-11  visanh  ESCAN00089273 FEAT-1723: Change API name Dem_SetPfcCycle
 *            2016-04-11  visanh  ESCAN00089273 FEAT-1723: Provide API Dem_GetDebouncingOfEvent
 *            2016-04-13  visade  ESCAN00089273 FEAT-1723: Support Readiness Group based IUMPR data retrieval
 *            2016-04-20  visanh  ESCAN00089353 FEAT-1724: OBD: Support for DTR (Diag Test Results)
 *            2016-04-29  visade  ESCAN00089767 Reset ratio status before call of init monitor function
 *            2016-05-02  visanh  ESCAN00089273 FEAT-1723: Support similar conditions
 *            2016-05-23  vissat  ESCAN00089273 FEAT-1723: Support Readiness PID01/PID41
 *            2016-06-03  visade  ESCAN00090281 Mode 0x0A DTC which do not trigger the MIL yet after permanent memory activation
 *            2016-06-07  visanh  ESCAN00089775 SI30.5 is not set as expected
 *            2016-06-07  visanh  ESCAN00089619 Compiler warning: last line of file ends without a newline
 *            2016-06-07  visanh  ESCAN00089453 Compiler error: l-value specifies const object
 *            2016-06-07  visanh  ESCAN00089446 Monitor results are not processed
 *            2016-06-07  visanh  ESCAN00087975 OCC7 incorrect after reoccurrence of an aged DTC
 *            2016-06-08  visanh  ESCAN00090369 Add support for DM35
 *            2016-06-13  vismhe  ESCAN00090431 DTC is not stored during memory overflow
 *            2016-06-14  vismhe  ESCAN00090430 Module initialization fails
 *            2016-06-23  vismhe  ESCAN00090622 Aging counter incremented without test result
 *            2016-06-23  vismhe  ESCAN00090629 FEAT-1810: Adapt DCM and DEM to FCA Requirements
 *            2016-07-07  visanh  ESCAN00090874 Compiler warning: DEM_CFG_SUPPORT_NVM_POLLING undefined
 *  13.00.00  2016-10-25  viszfa  ESCAN00091941 OBD DTCs can't be displaced
 *            2017-01-11  viszfa  ESCAN00093510 Memory write access out of range
 *            2017-02-24  vismhe  ESCAN00091967 WIR status bit is reset for aged, but not healed DTC on ECU restart
 *            2017-02-24  visanh  FEAT-2212     SafeBSW for DEM
 *            2017-02-24  visejz  FEAT-2212     SafeBSW for DEM
 *            2017-02-24  vishrs  FEAT-2212     SafeBSW for DEM
 *            2017-02-24  vismhe  FEAT-2212     SafeBSW for DEM
 *            2017-02-24  viszfa  FEAT-2212     SafeBSW for DEM
 *            2017-02-24  visanh  FEAT-2212     Extend API to multiple satellites
 *            2017-02-24  visejz  FEAT-2212     Extend API to multiple satellites
 *            2017-02-24  vishrs  FEAT-2212     Extend API to multiple satellites
 *            2017-02-24  vismhe  FEAT-2212     Extend API to multiple satellites
 *            2017-02-24  viszfa  FEAT-2212     Extend API to multiple satellites
 *            2017-02-24  visanh  FEAT-2160     Rework Dcm interface to support parallel requests
 *            2017-02-24  visejz  FEAT-2160     Rework Dcm interface to support parallel requests
 *            2017-02-24  vishrs  FEAT-2160     Rework Dcm interface to support parallel requests
 *            2017-02-24  vismhe  FEAT-2160     Rework Dcm interface to support parallel requests
 *            2017-02-24  viszfa  FEAT-2160     Rework Dcm interface to support parallel requests
 *            2017-02-24  visavi  ESCAN00102117 Degradation in runtime performance including delayed processing of event reports
 *  13.01.00  2017-03-30  visavi  STORYC-446    Rework Dcm interface to support parallel requests 5 Verification
 *            2017-03-30  visfrs  STORYC-447    Rework Dcm interface to support parallel requests 9 Verification
 *            2017-03-30  visavi  STORYC-456    Rework Dcm interface to support parallel requests 6 Functional
 *            2017-03-30  vishrs  STORYC-459    Rework Dcm interface to support parallel requests 13 Functional
 *            2017-03-30  visavi  STORYC-468    Rework Dcm interface to support parallel requests 11 Verification
 *            2017-03-30  visfrs  STORYC-469    Rework Dcm interface to support parallel requests 12 Functional
 *            2017-03-30  visavi  STORYC-472    Rework Dcm interface to support parallel requests 5 Verification
 *            2017-03-30  visejz  STORYC-473    Rework Dcm interface to support parallel requests 9 Functional
 *            2017-03-30  vishrs  STORYC-474    Rework Dcm interface to support parallel requests 10 Functional
 *            2017-03-30  visanh  STORYC-475    Rework Dcm interface to support parallel requests 11 TechRef
 *            2017-03-30  visavi  STORYC-550    Rework Dcm interface to support parallel requests 6 Verification
 *            2017-04-05  visejz  ESCAN00094637 Suppressed DTCs reported by GetDTCbyOccurrenceTime
 *            2017-04-10  visejz  STORYC-448    Rework Dcm interface to support parallel requests 10 Verification
 *            2017-04-10  visfrs  STORYC-458    Rework Dcm interface to support parallel requests 8 Verification
 *            2017-04-11  visanh  STORYC-507    Extract time based de-bouncing Functional
 *            2017-04-11  vismhe  STORYC-232    Connect Protocol Handler to DEM
 *            2017-04-11  visejz  STORYC-510    Extract subcomponent Debounce Functional
 *            2017-04-11  vishrs  STORYC-512    Extract Subcomponent DTR Functional
 *            2017-04-10  visfrs  STORYC-555    Rework Dcm interface to support parallel requests 9 Verification
 *            2017-04-11  visejz  STORYC-513    Rework Dem_GetWIRStatus Functional
 *            2017-04-11  vishrs  ESCAN00099725 DTR Data might not be reported for some OBD MIDs
 *  13.02.00  2017-04-18  visanh  ESCAN00094549 FIM_E_WRONG_TRIGGER_ON_EVENT DET during initialization
 *            2017-04-20  visanh  ESCAN00094812 Compile error: Definition different from declaration
 *            2017-04-21  vishrs  STORYC-511    Extract subcomponent MonitorStatus Functional
 *            2017-04-24  vismhe  STORYC-514    Extract subcomponent event queue Functional
 *            2017-05-05  vishrs  STORYC-515    Extract subcomponent init state management Functional
 *  13.03.00  2017-05-22  vishrs  STORYC-994    Provide Dem_GetDTCSuppression API
 *            2017-05-22  vishrs  STORYC-752    Rework include of RTE files
 *            2017-06-06  visejz  STORYC-738    Extract subcomponent EventUds Functional
 *  13.04.00  2017-06-13  visanh  STORYC-222    Adapt DEM to FCA Requirements
 *            2017-06-14  visejz  STORYC-360    Add new API Dem_GetOperationCycleState
 *            2017-14-06  vissat  ESCAN00093466 Unexpected DET in Dem_DcmDisableDTCRecordUpdate
 *            2017-06-19  visanh  STORYC-361    Support indicator state CONT_BLINKING for OBD MIL
 *            2017-06-20  vissat  STORYC-721    Change SelectDTC to prohibit event selection during ongoing request Functional
 *            2017-06-28  vishrs  STORYC-1457   Extract subcomponent for SWC APIs for environmental data Functional
 *            2017-07-03  visanh  STORYC-1191   Extract subcomponent MemoryEntry Functional
 *  13.05.00  2017-07-10  vishrs  STORYC-1756   Support a component-specific SafeBSW configuration switch
 *            2017-07-15  vissat  STORYC-654    Extract subcomponent OperationCycle Functional
 *            2017-07-17  visejz  STORYC-651    Extract subcomponent UdsDtcStatus Functional
 *            2017-07-17  vishrs  STORYC-1519   Extract subcomponent Memory (part 1) Functional
 *            2017-07-19  visanh  STORYC-1538   Extract subcomponent NvM management Functional
 *  13.06.00  2017-08-04  vishrs  STORYC-1469   FCA CDDT Import for DEM
 *            2017-08-18  visejz  ESCAN00096295 Debounce data not persisted after manual NV synchronization
 *            2017-08-21  vissat  ESCAN00092216 PID 0x01: Incorrect calculation of bit B.4 and B.5
 *            2017-09-03  visavi  ESCAN00096492 Aging counter is incremented incorrectly
 *  14.00.00  2017-09-05  visanh  STORYC-1989   Upgrade J1939Dcm Interfaces in DEM
 *            2017-09-07  visavi  STORYC-2339   Reworked the Snapshot retrieval function in EnvDataSwcApi subcomponent
 *            2017-09-12  visanh  ESCAN00096549 DET check for DTCOrigin missing in API Dem_J1939DcmClearDTC
 *            2017-09-21  visanh  ESCAN00096826 Incorrect J1939 lamp status in DM31
 *  14.01.00  2017-10-05  visanh  STORYC-2640   Change DTR processing to fulfill SWS_Dem_01105
 *            2017-10-09  visanh  ESCAN00096945 Debounce data not persisted after manual NV synchronization
 *            2017-10-10  visanh  ESCAN00096960 CycleState is not stored in NvRam
 *            2017-10-10  visejz  STORYC-1318   Rework Similar Condition handlingfor multiple partitions
 *            2017-10-16  vismhe  ESCAN00097026 No response for service 19 06
 *            2017-10-16  visanh  ESCAN00097045 Dem_SetEventAvailable returns E_OK for events unavailable in variant
 *  14.02.00  2017-11-02  visanh  ESCAN00097267 PID 0x41: Incorrect calculation of comprehensive component monitoring, if major monitors are not supported
 *            2017-11-02  visanh  ESCAN00097254 Linker error: Fim_DemInit instead of FiM_DemInit is called
 *            2017-11-17  vissat  ESCAN00097201 DTC storing a Freeze Frame is not reported via OBDII Mode 02
 *            2017-11-20  visejz  STORYC-2340   Extract subcomponent Indicator Functional
 *            2017-11-20  visanh  ESCAN00097458 Compiler error: undefined symbol Dem_Event_GetTripCount
 *            2017-11-20  visanh  ESCAN00097474 Incorrect calculation of 'Cycles Tested Since Last Failed' and 'Healing Counter Inverted'
 *  14.03.00  2017-11-28  visanh  ESCAN00097584 Incorrect values for 'Cycles Tested Since Last Failed' and 'Healing Counter Inverted' returned
 *            2017-11-28  visanh  ESCAN00099810 Event heals to early after displacement (implicitly fixed with ESCAN00097584)
 *            2017-11-29  visanh  ESCAN00097595 Feature J1939 and Postbuild Loadable don't work together
 *            2017-11-30  vismhe  ESCAN00097339 Compiler warning: possible truncation at implicit conversion
 *            2017-11-30  vismhe  ESCAN00097564 Compiler error: Non defined function referenced in DEM Code
 *            2017-11-30  vismhe  ESCAN00097662 Configured ClearDTC finished notification does not occur
 *            2017-12-05  visejz  STORYC-1726   Add multi-partition support for freeze frame pre-storage
 *            2017-12-05  vismhe  ESCAN00097577 FreezeFrame is reported while no DTC is visible in modes 0x03 and 0x07
 *            2017-12-11  vismhe  ESCAN00097707 Unexpected DET during wakeup
 *            2017-12-11  vismhe  ESCAN00097712 Permanent DTC is not persisted into NV Ram
 *  14.04.00  2018-01-02  visanh  ESCAN00097699 Dem_SetWIRStatus is processed and returns E_OK for unavailable events
 *            2018-01-02  visanh  ESCAN00097848 Dem_GetWIRStatus returns E_OK for unavailable events
 *            2018-01-02  visanh  ESCAN00097849 Dem_GetEventEnableCondition returns E_OK for unavailable events
 *            2018-01-02  visanh  ESCAN00097850 Dem_GetEventAvailable returns AvailableStatus 'True' for events unavailable in variant
 *            2018-01-02  visanh  ESCAN00097852 Dem_GetCurrentIUMPRRatioDataAndDTC returns E_OK for unavailable/suppressed events
 *            2018-01-08  visanh  ESCAN00097884 DET check for pre-initialized satellite missing in Dem_SetEventStatus and Dem_ResetEventDebounceStatus
 *            2018-01-11  visanh  ESCAN00097932 Remove unused user defined switch DEM_CFG_AGING_START_CLEARS_OBD_FF
 *            2018-01-25  visanh  ESCAN00098143 WIR status bit of Black MIL DTC is reported, although driving cycle is not qualified
 *            2018-01-25  visanh  ESCAN00098142 Non OBD relevant DTC is not reported as confirmed
 *  14.05.00  2018-02-13  visanh  ESCAN00098374 Memory corruption during module initialization
 *            2018-02-13  visanh  ESCAN00099243 Compiler warning: 'Dem_Data_CopyStandardEnvData_Dag' declared, but never defined
 *            2018-02-14  vissat  ESCAN00098391 Compiler warning: Linker error/warning caused by usage of pointers to inline functions
 *            2018-02-15  visanh  ESCAN00098319 Compiler error: Non defined function(s) referenced in DEM Code
 *            2018-02-15  visanh  ESCAN00098311 Compiler error: Non defined function referenced in DEM Code
 *  14.06.00  2018-03-01  visanh  STORYC-4316   Fix several compile errors in new configurations
 *            2018-03-02  vishrs  ESCAN00098370 Dem calls monitor status change callbacks before Dem_Init
 *            2018-03-08  visanh  ESCAN00098637 Compiler error in configurations using DTRs without any event references
 *            2018-03-12  vissat  STORY-3042    Complete Silent Analysis
 *  15.00.00  2018-03-22  visanh  STORYC-4757   Fix several compile warnings in exotic configurations
 *  15.01.00  2018-04-16  visanh  ESCAN00098748 Similar conditions reported with pre-qualified monitor result not considered for events with time-based de-bouncing
 *            2018-04-17  visanh  ESCAN00098659 Permanent entry of combined event is cleared at initialization of Dem
 *            2018-04-18  visfrs  ESCAN00098660 Cycles since first failed is not latched at 255
 *            2018-04-25  visfrs  ESCAN00098186 Compiler error in configurations with certain aging behavior types
 *            2018-04-30  visanh  ESCAN00098183 DTCStatusOld in DTCStatusChanged callbacks wrong for OBD relevant DTCs
 *            2018-05-03  visanh  ESCAN00099302 Driving cycle qualification is not considered in EventStatusChanged callbacks
 *            2018-05-04  vishrs  ESCAN00099171 Value of 'Cycles Since First Failed' is 0
 *  15.02.00  2018-05-15  visanh  ESCAN00098626 Incorrect calculation of 'Cycles Tested Since Last Failed' for healing target 0
 *            2018-05-16  vishrs  ESCAN00098596 Combined event is not stored, during Storage Retry after Storage Conditions are fulfilled
 *            2018-05-17  vishrs  ESCAN00099241 Compiler warning: 'Dem_Cfg_FindGroupMaskFromUdsDtc' declared but never defined
 *            2018-06-05  visanh  ESCAN00099298 Missing safety manual item for ClearDTC notification function pointers
 *            2018-06-05  visanh  ESCAN00099490 Missing safety manual item for J1939 DTC Status Changed notification function pointers
 *  15.03.00  2018-06-13  visavi  ESCAN00099487 Supported OBD MIDs in response message of Service 06 are reported in the wrong order
 *            2018-06-22  visejz  ESCAN00099227 Healing of event continues despite pre-confirmation 
 *            2018-06-27  visavi  ESCAN00099383 Failure to collect data via Client/Server or Sender/Receiver R-Port results in random data
 *            2018-07-02  visfrs  ESCAN00099748 Completeness of PID01 Comprehensive Component Monitoring is reported incomplete.
 *  15.04.00  2018-07-17  visanh  STORYC-5589   Provide OBD Dem Autosar 4.3 IUMPR Groups
 *            2018-07-24  visavi  STORYC-5370   Extract subcomponent Memory Functional
 *            2018-07-30  visejz  STORYC-5849   Adapt DEM Interface for Initialization
 *  15.05.00  2018-08-10  visfrs  ESCAN00099789 Undefined behaviour: Satellite Status not initialized during RAM initialization 
 *            2018-08-10  visfrs  ESCAN00100047 Consecutive failed cycle counter not persisted to NvRAM
 *            2018-08-07  visavi  STORYC-5368   Extract subcomponent MemState Functional
 *            2018-08-16  visavi  STORYC-5364   Extract subcomponent MemStorageManager Functional
 *            2018-08-21  visfrs  STORYC-2206   Extract subcomponent Notifications Functional
 *            2018-08-21  visfrs  ESCAN00100432 First clear request after NvM error is responded with CLEAR_MEMORY_ERROR 
 *  15.06.00  2018-08-27  visejz  STORYC-5366   Extract subcomponent MemAccess Functional
 *  16.00.00  2018-09-12  visfrs  STORYC-4763   DEM: Support suppressed DTCs in response of service 19x0A
 *            2018-09-20  visejz  ESCAN00100732 Dem_DisableDTCRecordUpdate is not processed
 *            2018-09-21  visejz  ESCAN00100778 Suppressed DTCs are reported in UDS service 0x19 subfunction 0x15
 *            2018-09-24  visejz  STORYC-5932:  Extract subcomponent Memory Functional 2
 *            2018-09-25  visejz  ESCAN00100584 Dem doesn't return DEM_CLEAR_FAILED although all ClearEventAllowed callbacks return FALSE
 *            2018-09-26  visfrs  ESCAN00100537 Not qualified OBD Driving Cycle is restarted
 *  16.01.00  2018-09-26  visavi  STORYC-1548   Extract subcomponent Statistics Functional
 *            2018-10-01  visanh  ESCAN00100903 Compiler warning: last line of Dem_EnableCondition_Interface.h ends without a newline
 *            2018-10-01  visanh  ESCAN00100904 Compiler warning: last line of Dem_Cfg_Definitions.h ends without a newline
 *            2018-10-01  visanh  ESCAN00100905 Compiler warning: last line of Dem_MemState_Implementation.h ends without a newline
 *            2018-10-04  visejz  STORYC-4794   DEM: Support "Fault Pending Counter"
 *            2018-10-11  visejz  STORYC-6249   Improve recovery for stored EventIds in NvRAM blocks
 *            2018-10-16  vissat  ESCAN00101027 Stack Usage of Dem functions too high
 *  16.02.00  2018-10-25  visavi  STORYC-4762   Support Storage of Global Snapshot Record
 *            2018-11-14  visejz  STORYC-6782   [OBD] Use oldest Confirmed DTC, after PDTC memory gets freed
 *            2018-11-19  visavi  STORYC-6793   Make aging in Dem compliant to 1968.2, Support aging independent of memory entry
 *  16.03.00  2018-12-04  visejz  ESCAN00101111 Dem returns invalid OBD Freeze Frame data when read out through Application API
 *            2018-12-19  visavi  ESCAN00101179 Dem returns invalid OBD Freeze Frame data during UDS Service 19 05 and OBD Mode 02
 *  16.04.00  2019-01-08  visejz  STORYC-4761   DEM: Support "Aged Counter"
 *  16.05.00  2019-01-08  visavi  STORYC-7342   Included improvements in aging performance
 *            2019-01-22  visejz  STORYC-4797   DEM: Support Reading of Global Snapshot Record
 *            2019-01-31  visfrs  ESCAN00101934 OBD Freeze Frame of an event without memory entry is not cleared on aging
 *            2019-02-05  visfrs  ESCAN00101407 OBD freeze frame of major monitor events (misfire & fuel system monitors) do not displace existing OBD freeze frames. 
 *            2019-02-12  visfrs  STORY-10500   Adapt behavior of service 19 05 to be consistent with Obd mode 02
 *  16.06.00  2019-02-27  visejz  STORYC-7660   DEM: Support Reading of Global Snapshot Record (2)
 *            2019-03-04  vissat  ESCAN00101665 Dem returns invalid OBD Freeze Frame data during UDS Service 19 04
 *            2019-03-05  visavi  ESCAN00101894 Fuel System Monitoring Ready (bit B.5) in PID 0x01 is incorrectly reported as complete.
 *            2019-03-06  visejz  ESCAN00101907 Undefined behaviour due to memory access violation
 *            2019-03-12  visavi  ESCAN00102295 Incorrect configuration of DEM Aging Behavior
 *********************************************************************************************************************/

#if !defined (DEM_H)                                                                                                             /* COV_MSR_HEADERGUARD TX */
#define DEM_H


/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                     /* Dem public types, defined statically */
/* ------------------------------------------------------------------------- */
#include "Dem_Types.h"
/* ------------------------------------------------------------------------- */

                                                       /* Configuration data */
/* ------------------------------------------------------------------------- */
#include "Dem_Lcfg.h"
#include "Dem_PBcfg.h"
/* ------------------------------------------------------------------------- */

                                                       /* Subcomponent types */
/* ------------------------------------------------------------------------- */
#include "Dem_Cfg_Types.h"
#include "Dem_Cfg_Macros.h"
/* ------------------------------------------------------------------------- */


                                          /* Static configuration validation */
/* ------------------------------------------------------------------------- */
#include "Dem_Validation.h"
/* ------------------------------------------------------------------------- */

                                          /* Subcomponent interfaces */
/* ------------------------------------------------------------------------- */
#include "Dem_API_Interface.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

                                                      /* Version information */
/* ------------------------------------------------------------------------- */

/* vendor and module identification - decimal encoding */
#define DEM_VENDOR_ID                            (30U)
#define DEM_MODULE_ID                            (54U)
#define DEM_INSTANCE_ID                          (0U)

/* AUTOSAR Software Specification Version Information - decimal encoding */
#define DEM_AR_RELEASE_MAJOR_VERSION             (4U)
#define DEM_AR_RELEASE_MINOR_VERSION             (3U)
#define DEM_AR_RELEASE_REVISION_VERSION          (0U)

/* Component Version Information - decimal encoding */
#define DEM_SW_MAJOR_VERSION                     (16U)
#define DEM_SW_MINOR_VERSION                     (6U)
#define DEM_SW_PATCH_VERSION                     (0U)


                                                                  /* API Ids */
/* ------------------------------------------------------------------------- */
#define DEM_GETVERSIONINFO_APIID                          (0x00U)              /*< Service ID: Dem_GetVersionInfo() */
#define DEM_PREINIT_APIID                                 (0x01U)              /*< Service ID: Dem_PreInit() */
#define DEM_INIT_APIID                                    (0x02U)              /*< Service ID: Dem_Init() */
#define DEM_SHUTDOWN_APIID                                (0x03U)              /*< Service ID: Dem_Shutdown() */
#define DEM_SETEVENTSTATUS_APIID                          (0x04U)              /*< Service ID: Dem_SetEventStatus() */
#define DEM_RESETEVENTSTATUS_APIID                        (0x05U)              /*< Service ID: Dem_ResetEventStatus() */
#define DEM_PRESTOREFREEZEFRAME_APIID                     (0x06U)              /*< Service ID: Dem_PrestoreFreezeFrame() */
#define DEM_CLEARPRESTOREDFREEZEFRAME_APIID               (0x07U)              /*< Service ID: Dem_ClearPrestoredFreezeFrame() */
#define DEM_SETOPERATIONCYCLESTATE_APIID                  (0x08U)              /*< Service ID: Dem_SetOperationCycleState() */
#define DEM_RESETEVENTDEBOUNCESTATUS_APIID                (0x09U)              /*< Service ID: Dem_ResetEventDebounceStatus() */
#define DEM_GETEVENTUDSSTATUS_APIID                       (0x0aU)              /*< Service ID: Dem_GetEventUdsStatus() */
#define DEM_GETEVENTFAILED_APIID                          (0x0bU)              /*< Service ID: Dem_GetEventFailed() */
#define DEM_GETEVENTTESTED_APIID                          (0x0cU)              /*< Service ID: Dem_GetEventTested() */
#define DEM_GETDTCOFEVENT_APIID                           (0x0dU)              /*< Service ID: Dem_GetDTCOfEvent() */
#define DEM_GETSEVERITYOFDTC_APIID                        (0x0eU)              /*< Service ID: Dem_GetSeverityOfDTC() */
#define DEM_REPORTERRORSTATUS_APIID                       (0x0fU)              /*< Service ID: Dem_ReportErrorStatus() */
#define DEM_SETAGINGCYCLESTATE_APIID                      (0x11U)              /*< Service ID: Dem_SetAgingCycleState() */
#define DEM_SETAGINGCYCLECOUNTERVALUE_APIID               (0x12U)              /*< Service ID: Dem_SetAgingCounterValue() */
#define DEM_SETDTCFILTER_APIID                            (0x13U)              /*< Service ID: Dem_SetDTCFilter() */
#define DEM_GETSTATUSOFDTC_APIID                          (0x15U)              /*< Service ID: Dem_GetStatusOfDTC() */
#define DEM_GETDTCSTATUSAVAILABILITYMASK_APIID            (0x16U)              /*< Service ID: Dem_GetDTCStatusAvailabilityMask() */
#define DEM_GETNUMBEROFFILTEREDDTC_APIID                  (0x17U)              /*< Service ID: Dem_DcmGetNumberOfFilteredDTC() */
#define DEM_GETNEXTFILTEREDDTC_APIID                      (0x18U)              /*< Service ID: Dem_DcmGetNextFilteredDTC() */
#define DEM_GETDTCBYOCCURRENCETIME_APIID                  (0x19U)              /*< Service ID: Dem_GetDTCByOccurrenceTime() */
#define DEM_DISABLEDTCRECORDUPDATE_APIID                  (0x1aU)              /*< Service ID: Dem_DisableDTCRecordUpdate() */
#define DEM_ENABLEDTCRECORDUPDATE_APIID                   (0x1bU)              /*< Service ID: Dem_EnableDTCRecordUpdate() */
#define DEM_DCMGETOBDFREEZEFRAMEDATA_APIID                (0x1cU)              /*< Service ID: Dem_DcmGetOBDFreezeFrameData() */
#define DEM_GETNEXTFREEZEFRAMEDATA_APIID                  (0x1dU)              /*< Service ID: Dem_GetNextFreezeFrameData() */
#define DEM_GETSIZEOFFREEZEFRAMESELECTION_APIID           (0x1fU)              /*< Service ID: Dem_GetSizeOfFreezeFrameSelection() */
#define DEM_GETNEXTEXTENDEDDATARECORD_APIID               (0x20U)              /*< Service ID: Dem_GetNextExtendedDataRecord() */
#define DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_APIID    (0x21U)              /*< Service ID: Dem_GetSizeOfExtendedDataRecordSelection() */
#define DEM_CLEARDTC_APIID                                (0x23U)              /*< Service ID: Dem_ClearDTC() */
#define DEM_DISABLEDTCSETTING_APIID                       (0x24U)              /*< Service ID: Dem_DisableDTCSetting() */
#define DEM_ENABLEDTCSETTING_APIID                        (0x25U)              /*< Service ID: Dem_EnableDTCSetting() */
#define DEM_GETINDICATORSTATUS_APIID                      (0x29U)              /*< Service ID: Dem_GetIndicatorStatus() */
#define DEM_GETEVENTMEMORYOVERFLOW_APIID                  (0x32U)              /*< Service ID: Dem_GetEventMemoryOverflow() */
#define DEM_SETDTCSUPPRESSION_APIID                       (0x33U)              /*< Service ID: Dem_SetDTCSuppression() */
#define DEM_GETFUNCTIONALUNITOFDTC_APIID                  (0x34U)              /*< Service ID: Dem_GetFunctionalUnitOfDTC() */
#define DEM_GETNUMBEROFEVENTMEMORYENTRIES_APIID           (0x35U)              /*< Service ID: Dem_GetNumberOfEventMemoryEntries() */
#define DEM_SETEVENTAVAILABLE_APIID                       (0x37U)              /*< Service ID: Dem_SetEventAvailable() */
#define DEM_SETSTORAGECONDITION_APIID                     (0x38U)              /*< Service ID: Dem_SetStorageCondition() */
#define DEM_SETENABLECONDITION_APIID                      (0x39U)              /*< Service ID: Dem_SetEnableCondition() */
#define DEM_GETNEXTFILTEREDRECORD_APIID                   (0x3aU)              /*< Service ID: Dem_GetNextFilteredRecord() */
#define DEM_GETNEXTFILTEREDDTCANDFDC_APIID                (0x3bU)              /*< Service ID: Dem_DcmGetNextFilteredDTCAndFDC() */
#define DEM_GETTRANSLATIONTYPE_APIID                      (0x3cU)              /*< Service ID: Dem_GetTranslationType() */
#define DEM_GETNEXTFILTEREDDTCANDSEVERITY_APIID           (0x3dU)              /*< Service ID: Dem_DcmGetNextFilteredDTCAndSeverity() */
#define DEM_GETFAULTDETECTIONCOUNTER_APIID                (0x3eU)              /*< Service ID: Dem_GetFaultDetectionCounter() */
#define DEM_SETFREEZEFRAMERECORDFILTER_APIID              (0x3fU)              /*< Service ID: Dem_SetFreezeFrameRecordFilter() */
#define DEM_SETEVENTDISABLED_APIID                        (0x51U)              /*< Service ID: Dem_SetEventDisabled() */
#define DEM_DCMREADDATAOFOBDFREEZEFRAME_APIID             (0x52U)              /*< Service ID: Dem_DcmReadDataOfOBDFreezeFrame() */
#define DEM_DCMGETDTCOFOBDFREEZEFRAME_APIID               (0x53U)              /*< Service ID: Dem_DcmGetDTCOfOBDFreezeFrame() */
#define DEM_MAINFUNCTION_APIID                            (0x55U)              /*< Service ID: Dem_MainFunction() */
#define DEM_DCMREADDATAOFPID01_APIID                      (0x61U)              /*< Service ID: Dem_DcmReadDataOfPID01() */
#define DEM_DCMREADDATAOFPID1C_APIID                      (0x63U)              /*< Service ID: Dem_DcmReadDataOfPID1C() */
#define DEM_DCMREADDATAOFPID21_APIID                      (0x64U)              /*< Service ID: Dem_DcmReadDataOfPID21() */
#define DEM_DCMREADDATAOFPID30_APIID                      (0x65U)              /*< Service ID: Dem_DcmReadDataOfPID30() */
#define DEM_DCMREADDATAOFPID31_APIID                      (0x66U)              /*< Service ID: Dem_DcmReadDataOfPID31() */
#define DEM_DCMREADDATAOFPID41_APIID                      (0x67U)              /*< Service ID: Dem_DcmReadDataOfPID41() */
#define DEM_DCMREADDATAOFPID4D_APIID                      (0x68U)              /*< Service ID: Dem_DcmReadDataOfPID4D() */
#define DEM_DCMREADDATAOFPID4E_APIID                      (0x69U)              /*< Service ID: Dem_DcmReadDataOfPID4E() */
#define DEM_DCMREADDATAOFPID91_APIID                      (0x6aU)              /*< Service ID: Dem_DcmReadDataOfPID91() */
#define DEM_GETEVENTEXTENDEDDATARECORDEX_APIID            (0x6dU)              /*< Service ID: Dem_GetEventExtendedDataRecordEx() */
#define DEM_GETEVENTFREEZEFRAMEDATAEX_APIID               (0x6eU)              /*< Service ID: Dem_GetEventFreezeFrameDataEx() */
#define DEM_REPIUMPRDENLOCK_APIID                         (0x71U)              /*< Service ID: Dem_RepIUMPRDenLock() */
#define DEM_REPIUMPRDENRELEASE_APIID                      (0x72U)              /*< Service ID: Dem_RepIUMPRDenRelease() */
#define DEM_REPIUMPRFAULTDETECT_APIID                     (0x73U)              /*< Service ID: Dem_RepIUMPRFaultDetect() */
#define DEM_SETWIRSTATUS_APIID                            (0x7aU)              /*< Service ID: Dem_SetWIRStatus() */
#define DEM_J1939DCMSETDTCFILTER_APIID                    (0x90U)              /*< Service ID: Dem_J1939DcmSetDTCFilter() */
#define DEM_J1939DCMGETNUMBEROFFILTEREDDTC_APIID          (0x91U)              /*< Service ID: Dem_J1939DcmGetNumberOfFilteredDTC() */
#define DEM_J1939DCMGETNEXTFILTEREDDTC_APIID              (0x92U)              /*< Service ID: Dem_J1939DcmGetNextFilteredDTC() */
#define DEM_J1939DCMFIRSTDTCWITHLAMPSTATUS_APIID          (0x93U)              /*< Service ID: Dem_J1939DcmFirstDTCWithLampStatus() */
#define DEM_J1939DCMGETNEXTDTCWITHLAMPSTATUS_APIID        (0x94U)              /*< Service ID: Dem_J1939DcmGetNextDTCWithLampStatus() */
#define DEM_J1939DCMCLEARDTC_APIID                        (0x95U)              /*< Service ID: Dem_J1939DcmClearDTC() */
#define DEM_J1939DCMSETFREEZEFRAMEFILTER_APIID            (0x96U)              /*< Service ID: Dem_J1939DcmSetFreezeFrameFilter() */
#define DEM_J1939DCMGETNEXTFREEZEFRAME_APIID              (0x97U)              /*< Service ID: Dem_J1939DcmGetNextFreezeFrame() */
#define DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_APIID         (0x98U)              /*< Service ID: Dem_J1939DcmGetNextSPNInFreezeFrame() */
#define DEM_J1939DCMREADDIAGNOSTICREADINESS1_APIID        (0x9bU)              /*< Service ID: Dem_J1939DcmReadDiagnosticReadiness1() */
#define DEM_GETOPERATIONCYCLESTATE_APIID                  (0x9eU)              /*< Service ID: Dem_GetOperationCycleState() */
#define DEM_GETDEBOUNCINGOFEVENT_APIID                    (0x9fU)              /*< Service ID: Dem_GetDebouncingOfEvent() */
#define DEM_SETDTR_APIID                                  (0xa2U)              /*< Service ID: Dem_SetDTR() */
#define DEM_DCMGETAVAILABLEOBDMIDS                        (0xa3U)              /*< Service ID: Dem_DcmGetAvailableOBDMIDs() */
#define DEM_DCMGETNUMTIDSOFOBDMID                         (0xa4U)              /*< Service ID: Dem_DcmGetNumTIDsOfOBDMID() */
#define DEM_DCMGETDTRDATA                                 (0xa5U)              /*< Service ID: Dem_DcmGetDTRData() */
#define DEM_SETPFCCYCLEQUALIFIED_APIID                    (0xaaU)              /*< Service ID: Dem_SetPfcCycleQualified() */
#define DEM_GETPFCCYCLE_APIID                             (0xabU)              /*< Service ID: Dem_GetPfcCycle() */
#define DEM_SETIUMPRDENCONDITION_APIID                    (0xaeU)              /*< Service ID: Dem_SetIUMPRDenCondition() */
#define DEM_GETDTCSEVERITYAVAILABILITYMASK_APIID          (0xb2U)              /*< Service ID: Dem_GetDTCSeverityAvailabilityMask() */
#define DEM_READDATAOFPID01_APIID                         (0xb3U)              /*< Service ID: Dem_ReadDataOfPID01() */
#define DEM_GETB1COUNTER_APIID                            (0xb4U)              /*< Service ID: Dem_GetB1Counter() */
#define DEM_GETMONITORSTATUS_APIID                        (0xb5U)              /*< Service ID: Dem_GetMonitorStatus() */
#define DEM_SELECTDTC_APIID                               (0xb7U)              /*< Service ID: Dem_SelectDTC() */
#define DEM_SELECTFREEZEFRAMEDATA_APIID                   (0xb9U)              /*< Service ID: Dem_SelectFreezeFrameData() */
#define DEM_SELECTEXTENDEDDATARECORD_APIID                (0xbaU)              /*< Service ID: Dem_SelectExtendedDataRecord() */
#define DEM_GETDTCSELCETIONRESULT_APIID                   (0xb8U)              /*< Service ID: Dem_GetDTCSelectionResult() */

#define DEM_INITMEMORY_APIID                              (0xd0U)              /*< Service ID: Dem_InitMemory() */
#define DEM_POSTRUNREQUESTED_APIID                        (0xd1U)              /*< Service ID: Dem_PostRunRequested() */
#define DEM_GETENABLECONDITION_APIID                      (0xd2U)              /*< Service ID: Dem_GetEventEnableCondition() */
#define DEM_GETWIRSTATUS_APIID                            (0xd3U)              /*< Service ID: Dem_GetWIRStatus() */
#define DEM_ENABLEPERMANENTSTORAGE_APIID                  (0xd4U)              /*< Service ID: Dem_EnablePermanentStorage() */
#define DEM_GETIUMPRGENERALDATA_APIID                     (0xd5U)              /*< Service ID: Dem_GetIUMPRGeneralData() */
#define DEM_GETNEXTIUMPRRATIODATAANDDTC_APIID             (0xd7U)              /*< Service ID: Dem_GetNextIUMPRRatioDataAndDTC() */
#define DEM_GETCURRENTIUMPRRATIODATAANDDTC_APIID          (0xd8U)              /*< Service ID: Dem_GetCurrentIUMPRRatioDataAndDTC() */
#define DEM_GETPERMANENTSTORAGESTATE_APIID                (0xd9U)              /*< Service ID: Dem_GetPermanentStorageState() */
#define DEM_IUMPRLOCKNUMERATORS_APIID                     (0xdaU)              /*< Service ID: Dem_IUMPRLockNumerators() */
#define DEM_REQUESTNVSYNCHRONIZATION_APIID                (0xdbU)              /*< Service ID: Dem_RequestNVSynchronization() */
#define DEM_GETEVENTAVAILABLE_APIID                       (0xdcU)              /*< Service ID: Dem_GetEventAvailable() */
#define DEM_SETIUMPRFILTER_APIID                          (0xddU)              /*< Service ID: Dem_SetIUMPRFilter() */
#define DEM_GETNUMBEROFFILTEREDIUMPR_APIID                (0xdeU)              /*< Service ID: Dem_GetNumberOfFilteredIUMPR() */
#define DEM_UPDATEAVAILABLEOBDMIDS_APIID                  (0xdfU)              /*< Service ID: Dem_UpdateAvailableOBDMIDs() */
#define DEM_NVMINIT_APIID                                 (0xf1U)              /*< Service ID: Dem_NvM_InitAdminData(), Dem_NvM_InitStatusData(), Dem_NvM_InitDebounceData(), Dem_NvM_InitEventAvailableData(), Dem_NvM_InitObdFreezeFrameData, Dem_NvM_InitObdIumprData(), Dem_NvM_InitDtrData() */
#define DEM_NVMJOBFINISHED_APIID                          (0xf2U)              /*< Service ID: Dem_NvM_JobFinished() */
#define DEM_SETHIDEOBDOCCURRENCES_APIID                   (0xf3U)              /*< Service ID: Dem_SetHideOBDOccurrences() */
#define DEM_GETHIDEOBDOCCURRENCES_APIID                   (0xf4U)              /*< Service ID: Dem_GetHideOBDOccurrences() */
#define DEM_SATELLITEPREINIT_APIID                        (0xf5U)              /*< Service ID: Dem_SatellitePreInit() */
#define DEM_SATELLITEINIT_APIID                           (0xf6U)              /*< Service ID: Dem_SatelliteInit() */
#define DEM_SATELLITEMAINFUNCTION_APIID                   (0xf7U)              /*< Service ID: Dem_SatelliteMainFunction() */
#define DEM_GETEVENTIDOFDTC_APIID                         (0xf8U)              /*< Service ID: Dem_GetEventIdOfDTC() */
#define DEM_GETDTCSUPPRESSION_APIID                       (0xf9U)              /*< Service ID: Dem_GetDTCSuppression() */
#define DEM_INTERNAL_APIID                                (0xffU)              /*< Service ID: Internal Functions */


                                  /* Error Codes for Det and port interfaces */
/* ------------------------------------------------------------------------- */
#define DEM_E_NO_ERROR                           (0x00U)                       /*< This value is never returned as error code */
#define DEM_E_PARAM_CONFIG                       (0x10U)                       /*< API called with a parameter value which is not allowed in this configuration */
#define DEM_E_PARAM_POINTER                      (0x11U)                       /*< API called with a NULL pointer where NULL pointer is not allowed */
#define DEM_E_PARAM_DATA                         (0x12U)                       /*< API called with an invalid parameter value, e.g. outside the valid range */
#define DEM_E_PARAM_LENGTH                       (0x13U)                       /*< API called with an invalid length or size parameter */
#define DEM_E_UNINIT                             (0x20U)                       /*< API called before the Dem module has been initialized */
#define DEM_E_NODATAAVAILABLE                    (0x30U)                       /*< Data collection failed while storing a DTC */
#define DEM_E_WRONG_CONDITION                    (0x40U)                       /*< API called with unsatisfied precondition (other than initialization) */
#define DEM_E_INCONSISTENT_STATE                 (0xf0U)                       /*< Internal state inconsistency - indicates a serious error */


                                                                /* Constants */
/* ------------------------------------------------------------------------- */
#define DEM_EVENT_INVALID                        ((Dem_EventIdType)0x0000U)    /*< EventId which is not used */
#define DEM_EVENT_FIRST                          ((Dem_EventIdType)0x0001U)    /*< First valid EventId */

#define DEM_DTC_GROUP_ALL_DTCS                   ((Dem_DTCGroupType)(0x00ffffffUL))  /*< predefined DTC group encoding 'All DTCs' */
#define DEM_DTC_GROUP_EMISSION_REL_DTCS          ((Dem_DTCGroupType)(0x00000000UL))  /*< predefined DTC group encoding 'Emmission related DTCs' for OBD-II */
#define DEM_DTC_GROUP_WWHOBD_DTCS                ((Dem_DTCGroupType)(0x00ffff33UL))  /*< predefined DTC group encoding 'Emmission related DTCs' for WWH-OBD */


/* ********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define DEM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DEM_CFG_USE_INIT_POINTER == STD_ON)
/*! Stores the pointer to the active module configuration */
extern P2CONST(Dem_ConfigType, DEM_VAR_NOINIT, DEM_INIT_DATA)  Dem_GlobalConfigPtr;
#endif

#define DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* ********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


/***********************************************************************************************************************
 *  EXCLUSIVE AREA DEFINITION
 **********************************************************************************************************************/
/*! \page allEA Exclusive Areas
 * \exclusivearea DEM_EXCLUSIVE_AREA_0 (DiagMonitor)
 * Ensures consistency and atomicity of event reports.
 * \protects
 * Dem_Cfg_CombinedGroupInternalStatus
 * Dem_Cfg_EventInternalStatus
 * Dem_Cfg_ObdIumprData.Status
 * Dem_Cfg_StatusData.ExtendedEventStatus
 * Dem_Cfg_Prestorage<X>.EventId
 * Dem_Cfg_Prestorage<X>.State
 * Dem_Prestore_FreeListHeadIndex
 * Dem_Queue_Pid01UpdateFlag
 * Dem_Cfg_DtrData.TestValue
 * Dem_Cfg_DtrData.LowLimValue
 * Dem_Cfg_DtrData.UppLimValue
 * \usedin
 * Dem_ClearPrestoredFreezeFrame
 * Dem_DcmGetDTRData
 * Dem_Init
 * Dem_MainFunction
 * Dem_MasterInit
 * Dem_MasterMainFunction
 * Dem_PrestoreFreezeFrame
 * Dem_RepIUMPRDenLock
 * Dem_RepIUMPRDenRelease
 * Dem_RepIUMPRFaultDetect
 * Dem_ReportErrorStatus
 * Dem_SetDTCSuppression
 * Dem_SetDTR
 * Dem_SetEventAvailable
 * Dem_SetEventStatus
 * Dem_SetIUMPRDenCondition
 * Dem_SetWIRStatus
 * Dem_Shutdown
 *
 * \exclude N/A
 * \length MEDIUM Resetting ratios blocked by FIDs must iterate all ratios, but
 *                releases the critical sections regularly.
 *         SHORT  In all other cases.
 * \endexclusivearea
 *
 ******************************************************************************
 *
 * \exclusivearea DEM_EXCLUSIVE_AREA_1 (StateManager)
 * Ensures consistent status updates when receiving ECU states managed outside
 * the Dem.
 *
 * \protects
 * Dem_Cfg_AdminData.ObdCycleState
 * Dem_Cfg_EnableConditionGroupCounter
 * Dem_Cfg_StorageConditionGroupCounter
 * Dem_Cfg_EnableConditionGroupState
 * Dem_OperationCycle_CycleFlag
 * Dem_OperationCycle_PendingCycleState
 *
 * \usedin
 * Dem_DisableDTCSetting
 * Dem_EnableDTCSetting
 * Dem_Init
 * Dem_MainFunction
 * Dem_MasterInit
 * Dem_MasterMainFunction
 * Dem_SetEnableCondition
 * Dem_SetOperationCycleState
 * Dem_SetPfcCycleQualified
 * Dem_SetStorageCondition
 * Dem_Shutdown
 *
 * \exclude N/A
 * \length LONG   Setting enable/storage conditions will update all
 *                enable/storage condition groups.
 * \length MEDIUM Updating the operation cycle queue state will use a couple of
 *                IF statements.
 + \length SHORT  Setting the PFC cycle.
 * \endexclusivearea
 *
 ******************************************************************************
 *
 * \exclusivearea DEM_EXCLUSIVE_AREA_2 (DcmAPI)
 * Ensures consistent status updates when receiving ECU states managed outside
 * the Dem.
 *
 * \protects
 * Dem_Cfg_AdminData.PermanentActivationState (transition off->on)
 * Dem_ClearTask_ClearRequest
 * Dem_Cfg_ReadoutBuffer.State (transition from QUEUED)
 *
 * \usedin
 * Dem_ClearDTC
 * Dem_EnableDTCRecordUpdate
 * Dem_EnablePermanentStorage
 * Dem_J1939DcmClearDTC
 * Dem_MainFunction
 * Dem_MasterMainFunction
 * Dem_SelectDTC
 *
 * \exclude N/A
 * \length MEDIUM Clear request polling requires atomic comparison of multiple
 *                values.
 * \endexclusivearea
 *
 ******************************************************************************
 *
 * \exclusivearea DEM_EXCLUSIVE_AREA_3 (CrossCoreComm)
 * Ensures consistent prestorage when called from multiple clients.
 * Ensures data consistency between satellites and master, if the platform does
 * not provide a specific CompareAndSwap instruction.
 *
 * \protects
 * Dem_Cfg_SatelliteInfo<X>.SatelliteData
 * Dem_Cfg_SatelliteInfo<X>.SatelliteExtendedData
 * Dem_Cfg_SatelliteInfo<X>.SatelliteStatus
 * Dem_Scheduler_ScheduledSingleInvocationTasks
 * Dem_Scheduler_ScheduledMultipleInvocationTasks
 *
 * \usedin
 * Dem_ClearDTC
 * Dem_ClearPrestoredFreezeFrame
 * Dem_DisableDTCRecordUpdate
 * Dem_DisableDTCSetting
 * Dem_EnableDTCSetting
 * Dem_Init
 * Dem_J1939DcmClearDTC
 * Dem_MainFunction
 * Dem_MasterInit
 * Dem_MasterMainFunction
 * Dem_PrestoreFreezeFrame
 * Dem_RepIUMPRDenRelease
 * Dem_RepIUMPRFaultDetect
 * Dem_ReportErrorStatus
 * Dem_ResetEventDebounceStatus
 * Dem_ResetEventStatus
 * Dem_SatelliteInit
 * Dem_SatelliteMainFunction
 * Dem_SetDTR
 * Dem_SetEnableCondition
 * Dem_SetEventAvailable
 * Dem_SetEventStatus
 * Dem_SetIUMPRDenCondition
 * Dem_SetOperationCycleState
 *
 * \exclude N/A
 * \length SHORT Single read and write access to RAM.
 * \endexclusivearea
 *
  ******************************************************************************
 *
 * \exclusivearea DEM_EXCLUSIVE_AREA_4 (NonAtomic32bit)
 * Ensures consistency if the platform doesn't provide an atomic 32 bit access.
 *
 * \protects
 * Dem_Cfg_AdminData.OdometerAtClear
 * Dem_Cfg_AdminData.OdometerMilOn
 *
 * \usedin
 * Dem_DcmReadDataOfPID21
 * Dem_DcmReadDataOfPID31
 * Dem_Init
 * Dem_MainFunction
 * Dem_MasterInit
 * Dem_MasterMainFunction
 * Dem_Shutdown
 *
 * \exclude N/A
 * \length SHORT Single read and write access to RAM.
 * \endexclusivearea
 */

/*!
 * \}
 */

#endif  /* DEM_H */

/* ********************************************************************************************************************
 *  END OF FILE: Dem.h
 *********************************************************************************************************************/
