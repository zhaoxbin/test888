/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  NvM.h
 *    Component:  MemService_AsrNvM
 *       Module:  NvM
 *    Generator:  -
 *
 *  Description:  The NVRAM Manager ensure the data storage and maintenance of NV data.
 *                The NVRAM Manager shall be able to administrate the NV data of an EEPROM
 *                and/or a FLASH EEPROM emulation device.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Christian Kaiser              Ck            Vector Informatik GmbH
 *  Manfred Duschinger            Du            Vector Informatik GmbH
 *  Tomas Ondrovic                Oto           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  03.00.00  -           Ck      -             initial AUTOSAR 2.0.0 revision
 *  03.00.01  -           Ck      -             fixed behaviour for NVRAM blocks without permanent RAM block
 *                                              fixed behaviour for NVRAM blocks without permanent RAM block
 *                                              improved usage of Memory Mapping / Compiler Abstracion
 *                                              maximized link-time configurability (NVRAM blocks)
 *  03.00.02  -           Ck      -             implemented dummy callbacks for EA, to guarantee that the objects
 *                                              can be linked
 *  03.00.03  -           Ck      -             fixed include of OS services in NvM_Cfg.c
 *                                              corrected setting of CHANGED flag after successful reads
 *  03.01.00  -           Ck      -             initial AUTOSAR 2.1 revision
 *  03.01.01  -           Ck      -             internal release -  started fixing issues listed for next release.
 *  03.01.02  -           Ck     ESCAN00021797  Optimized CRC queuing algorithm (runtime)
 *                               ESCAN00021562  Added "wait for MemHwA" before completing NvM_WriteAll
 *                               ESCAN00022622  Fixed usage of CRC library functions
 *                               ESCAN00022889  Completely reworked job queuing, reduced critical section lengths
 *                               ESCAN00022986  Fixed usage of critical sections, paired enter/exit
 *  03.01.03  -           Ck     ESCAN00025422  Fixed inconsistencies between function declarations and definitions
 *  03.02.00  -           Du      -             initial AUTOSAR 3.0 revision
 *                                -             added NvM_SetBlockLockStatus API and handling of locked blocks
 *                               ESCAN00025490  Internal buffers for CRC handling added (Crc is not saved
 *                                              after RamBlockData)
 *                               ESCAN00026660  Library version check added
 *  03.02.01  -           Ck                    Preparation for ASR3.0 Release.
 *                                              Updated all source according to VI's templates
 *                                              No Changes in code, just comments!
 *  03.02.02  -           Ck     ESCAN00026660  NvM.h does not declare API when included from NvM_Cfg.c.
 *                                              This avoids multiple, incompatible function declarations when
 *                                              using the RTE.
 *                               ESCAN00027283  Fixed definition of NvM_ServiceIdType and its values:
 *                                              It depends on usage of callbacks via RTE.
 *                                              If used, the RTE will define them, otherwise NvM_Types.h does.
 *  03.03.00  -           Du     ESCAN00029722  At requesting a high prio job, when NvM is currently idle, NvM
 *                                              calls MemIf_Cancel before processing the high prio job.
 *                                              NvM resets the internal job processing state machine only, if
 *                                              there is a currently pending job.
 *                               ESCAN00031568  Incorrect null pointer constant NULL is replaced by NULL_PTR.
 *                               ESCAN00028104  Fixed, that Development error NVM_E_LIST_OVERFLOW occurs together
 *                                              with NVM_E_BLOCK_PENDING
 *                               ESCAN00028575  Repair of redundant blocks: If NVM detects a defect NV Block, it is
 *                                              written in preference to a valid NV Block. If both NV blocks are in
 *                                              same state, the write order matches the read order.
 *                               ESCAN00028591  DCM got a possibility to access NV data concurrently with NVM's
 *                                              applications. Therefore NVRAM Blocks that are aliases of other
 *                                              NVRAM Blocks are implemented. The aliases are neither read at
 *                                              start-up nor written at shut-down. These blocks have their own,
 *                                              common, Management Area.
 * 03.03.01  -            Ck     ESCAN00032565  Eliminated compiler Warnings.
 * 03.03.02  -            Du     ESCAN00028104  Development error NVM_E_LIST_OVERFLOW occured together with NVM_E_BLOCK_PENDING
 *                               ESCAN00029722  NvM calls MemIf_Cancel whenever it starts processing an immediate write job.
 *                                              It only cancels the "Device" the pending immediate Block will be written to.
 *                        Du     ESCAN00033499  Unused variables deleted
 * 03.03.03  -            Du     ESCAN00032992  Compiler Abstraction to parameter NvState of internal function
 *                                              NvM_IntCreateNvState was added.
 *                               ESCAN00033098  When Crc-Calculation of a DCM Block is queued, only one bit, the bit
 *                                              of the DCM block is set in queue.
 *                               ESCAN00032738  NVM calls underlying Cancel service with valid DeviceId parameter now.
 * 03.04.00  -            Du     ESCAN00033075  DataIndex Check in NvM_ReadBlock added.
 *                               -              Implementation of a design issue: State check (NvState) is only
 *                                              for Blocks of MngmtType Redundant.
 *                               ESCAN00033100  Handling of DataIndex and DCM-Blocks: Job processing generally ignores
 *                                              the DataIndex if the Block Type is NATIVE or REDUNDANT.
 *                               ESCAN00033900  Improve priority handling of DCM Blocks: For DCM-Blocks original
 *                                              priority shall be kept, but the job of a DCM-Block shall always
 *                                              be put into "normal prio queue"
 *                               ESCAN00035089  Implemented Callbacks: NvM_JobEndNotification, NvM_JobErrorNotification
 *                               ESCAN00034073  Crc Handling is configurable: Either an internal buffer is used or Crc is
 *                                              stored at the end of RAM Block.
 * 03.04.01  -             Ck    ESCAN00039625  Fixed casts at invocations of Blocks' callbacks
 *                               ESCAN00038509  Conditions to report an error to DEM also depend on Block's Type
 *                               ESCAN00040014  Corrected definition of NvM_QryMemHwaBusy() -> compiler abstraction
 *                               Review Input   No functional/behavioral changes, improved MISRA compliance, readability
 * 3.05.00   -             Ck    ESCAN00031315  Added Invocation of Check Routine in Development Mode from NvM_Init.
 *                               ESCAN00039749  guaranteed that result of CRC32 is always the same
 *                                              (independent of NvmNoOfCrcBytes).
 *                               ESCAN00035134  Added inclusion of generated NvM_PrivateCfg.h
 *                               ESCAN00041407  WriteBlock processing: Ensure that NvM_MainFunction is left when copying
 *                                              RAM Data to internal Buffer (Blocks with CRC)
 *                               ESCAN00041717,
 *                               ESCAN00041933  Avoid compiler warnings
 *                               ESCAN00034154  Added cancellation of interrupted job's device
 *                               ESCAN00042136  Corrected initialization of job queue.
 *                               Review         - Added header file version cross checks in NvM.c
 *                                              - Insignificant improvements, basically related to style.
 * 3.05.01                 Ck    ESCAN00044218  NvM_Init - corrected function call to execute ROM Block size checks.
 *                               ESCAN00044082  NvM_QueueRequeueLastJob - declaration encapsulated in pre-processor condition
 * 3.07.00                 Ck    ESCAN00047171  Added Service NvM_KillWriteAll
 *                               ESCAN00038030  Changed access to NvM_BlockDescriptor members
 *                               ESCAN00028600  Changed CRC handling - Object based approach,
 *                                              Generic and pre-compile parts contained in static code; parts specific
 *                                              to a CRC type is part of NvM_Cfg.c -> we are link-time configurable
 *                                              Changed handling of internal buffer (CRC calculation/check)
 *                                              Changed ReadBlock state machine -> read into internal buffer (if CRC)
 * 3.07.01                 Ck    ESCAN00049088  fixed declaration of internal function NvM_CrcGetQueuedBlockId
 *                               ESCAN00049095  avoid compiler warnings, improve MISRA compliance
 *                               Review         unimportant changes (comments)
 * 3.08.00                 Du           -        Update of version information because of minor update in GenTool_Ead
 * 3.08.01                 Ck    ESCAN00054304  modified NvM_QryNvBusy()
 *                               ESCAN00052156  modified NvM_QryWriteBlockOnce()
 *                               ESCAN00051883  corrected declaration/definition of NvM_KillWriteAll (compiler abstraction)
 *                               ESCAN00051123  compiler warnings (narrowing) due to negation operator
 *                               ESCAN00050976  corrected declaration of NvM_CrcJob_Process (compiler abstraction)
 *
 * 3.09.00                 Ck           -       Update of version information because of minor update in GenTool_Ead
 *                               ESCAN00053323  MISRA compliance / added justifications to source code
 * 5.00.00                 Du    ESCAN00058816  Compilant AUTOSAR 4 NvM: Features NvM_CancelJobs;
 *                                              DEM Error for Redundancyloss and Write-Protect;
 *                                              Writting block during NvM_WriteAll only if configured;
 *                                              NvM_CancelJobs API
 *                               ESCAN00058831  AUTOSAR 4: Explicit Synchronization mechanism between application and NVM
 *                                      -       instanceID deleted from VersionInfoType;
 *                                      -       AUTOSAR version defines updated to ASR 4
 *                                      -       MemMap Sections updated to ASR 4
 *                               ESCAN00060418  Removed include of Crc.h in NvM.c
 *                               ESCAN00060474  NvM_GenericRomDefaultsPtrType is checked against 0, because it's uint32
 *                          Ck   ESCAN00061156  API has been changed! Return Types
 * 5.00.01                  Ck   ESCAN00062069  Changed internal Buffer handling (copy data around) and CRC handling
 *                                              during read and write job execution (Actions, Queries).
 *                               ESCAN00062724  NvM_QueueJob: removed unused constant declaration,
 * 5.01.00                  Ck   ESCAN00062284  AR4-98 Interaction with BswM  
 *                               ESCAN00061946  replaced STATIC by static
 * 5.01.01                  Ck   ESCAN00049094  Removed Dummy Statements from NvM_Crc_NoCrc_* functions (NvM_Crc.c)
 *                               ESCAN00066947  initialization of DataIndexPtr in NvM_GetDataIndex (NvM.c)
 *                               ESCAN00068565  Corrected functional behavior of NvM_UnQueueJob
 *                               ESCAN00068995  Changed NvM_QueueFindBlock(), NvM_UnqueueJob()
 *                               ESCAN00068406  Added action function NvM_SetBlockPendingWriteAll()
 *                               ESCAN00068996  Added calls to NvM_BlockNotification in NvM_SetBlockPendingWriteAll,
 *                                              NvM_ActInitReadAll, NvM_ActFinishBlock
 *                               ESCAN00063532  Reversed block processing order during WriteAll; 
 *                                              - added NvM_QryLastBlockDone_WriteAll, NvM_ActInitNextBlockWriteAll
 *                                              - updated NvM_ActInitBlock, NvM_ActInitNextBlockReadAll
 *                                              - renamed NvM_QryLastBlockDone to NvM_QryLastBlockDone_ReadAll
 *                               ESCAN00069686  Minor re-design of data copy, added internal functions, modified actions
 *                                              queries, state descriptions. Restoring ROM Defaults now uses the same
 *                                              approach as copying data after read (from internal buffer to RAM block
 *                                              either via NvM_ReadRamFromNvMCbk - incl. retries - or via internal copy).
 *                                              Loading Defaults via internal copy became async. just like normal copy.
 *                               ESCAN00067153  - NvM_ActUpdateConfigId changed 
 *                                       -      Annotations (comments) to support ECO (coverage analysis)
 *                                       -      QAC (added justifications)
 * 5.01.02                  Ck   ESCAN00070883  NvM_Act.c: corrected conditions to change a Block's permanent
 *                                                   RAM block's VALID/CHANGED states during job proecessing
 * 5.01.03                  Ck   ESCAN00072502  Made sure NvM_KillWriteAll allways leaves its critical section.
 *                               ESCAN00072372  NvM_WriteBlock always allows passing a temp. RAM Block.
 *                               ESCAN00070403  Factored out DET checks in API 
 *                                              Refactored NvM_CrcGetQueuedBlockId (added NvM_CrcQueueCountTrailingZeros())
 * 5.01.04                  Ck   ESCAN00073678  Corrected NvM_QryBlockWriteAll, check for protection conditions.
 *                                           -  TAB to <spaces>
 *                                           -  MISRA Compliance - NvM_Act.c, NvM_ActKillWriteAll - added casts.
 *                               ESCAN00074892  Call NvM_ActInitRestoreBlockDefaults in transition from 
 *                                              NVM_STATE_READ_IMPL_RECOV to NVM_STATE_READ_LOAD_ROM.
 *                                              NvM_ActInitRestoreBlockDefaults only initializes byteCount.
 *                               ESCAN00074894  NvM_ActProcessCrcRead - RAM Copy will be skipped if INTERNAL_CRC_BUFFER
 *                                              is disabled.
 * 5.01.05                  Ck   ESCAN00076103  completeley removed "Privmary NV Block Defect Flag"
 *                               ESCAN00074862  NvM_DetCommonChecks() - extended RAM pointer check,
 *                                              extracted NvM_DetHasPermanentRamBlock()
 *                               ESCAN00074941  NvM_ActFinishCfgIdCheck() - set result to NVM_REQ_INTEGRITY_FAILED, if
 *                                              an error (including CRC mismatch) was detected.
 * 5.01.06                  Oto  ESCAN00075178  NvM_ReadBlock, NvM_WriteBlock and NvM_RestoreBlockDefaults update
 *                                              the changed and valid flags only if requested with NULL_PTR
 *                               ESCAN00078968  updated MISRA justifications to newest format
 *                               ESCAN00072877  after the ROM pointer InitCallback pointer were splitted into two different
 *                                              configuration parameter, the NvM code was adjusted and the 
 *                                              NvM_ActRestoreRomDefaults reworked
 * 5.01.07                  Oto  ESCAN00080526  NvM_ActRestoreRomDefaults - cast the Init Callback return value to
 *                                              void, because it will be ignored
 * 5.02.00                  Oto  ESCAN00075181  NvM_SetRamBlockStatus now checks the block to have permanent RAM only
 *                                              in DET-mode; SafeBSW API pattern was implemented within the NvM.c
 *                               ESCAN00077949  replaced runtime RAM- and ROM-Length DET checks with compile time
 *                                              within generated files
 *                               ESCAN00077968  added Multiblock pending DET check, NVM_E_BLOCK_PENDING DET check was
 *                                              moved from queue module to public API
 *                               ESCAN00077978  automatic Crc queue disabling in case no block is configured with
 *                                              CalcRamBlockCrc TRUE
 *                               ESCAN00080059  Block Id Check: use NvM Block Id and Dataindex to calculate Crc,
 *                                              if this feature is enabled
 *                               ESCAN00079077  skip blocks without defaults during Extended Runtime Preparation (ReadAll,
 *                                              Dynamic Configuration enabled and Configuration Id mismatch)
 *                               FEAT-1325      added NvM_RepairRedundantBlocks functionality
 *                               ESCAN00084228  use NvM_BlockIdType instead of uint16_least within NvM_ActInitReadAll
 * 5.02.01                  Oto  ESCAN00084457  removed multi block pending check and extend single block pending check,
 *                                              improved WriteAll FSM (moved skip check to another state, removed skip state)
 * 5.02.02                  Oto  -              no functionality changes, only internal improvements
 * 5.03.00                  Oto  ESCAN00081163  removed C++ comment
 *                               ESCAN00085159  removed separate Development Error switches
 *                               ESCAN00086550  blocks with permanent RAM and restored defaults via initialization callback
 *                                              shall be marked as valid and changed
 *                               ESCAN00072355  changed version numbering to BCD
 *                               ESCAN00087421  corrected different declaration and definition for private function (NVM_LOCAL vs. NVM_LOCAL_INLINE)
 * 5.04.00                  Oto  ESCAN00088233  removed non-AUTOSAR container NvMDevErrorChecks and parameter NvMCfgIncludeDem and NvMSeterror
 * 5.05.00                  Oto  ESCAN00088791  adjusted function declarations to AUTOSAR 4
 *                               ESCAN00089323  reworked NvM_QueueJob to ensure critical section exiting
 *                               FEAT-1888      reworked single and init block callback invoking during ReadAll
 *                               ESCAN00090438  added preprocessor directive to NvM_CheckAddress and NvM_ActProcessCrc declaration
 * 5.05.01                  Oto  ESCAN00089556  moved static code from generated files to static files
 *                               ESCAN00073639  updated DCM block handling
 * 5.06.00                  Oto  ESCAN00094128  DEM error reporting shall be configurable
 *                               ESCAN00094503  Update source identification define symbols to component template
 * 5.06.01                  Oto  ESCAN00095517  NvM block identifier out of range does not lead to a DET error report
 * 5.07.00                  Oto  FEAT-2914      Support CRC Compare Mechanism in NvM
 * 5.07.01                  Oto  ESCAN00098248  Immediate priority block requests during WriteAll may lead to unsuccessful WriteAll
 * 5.07.02                  Oto  ESCAN00099765  NvM writes redundant block even Crc CompareMechanism is enabled and Crc matches
 * 5.08.00                  Oto  STORY-6224/STORYC-5670 Provide an interface to protect and validate NV data.
 **********************************************************************************************************************/

/* Do not modify this file! */


/**********************************************************************************************************************
 * PROTECTION AGAINST MULTIPLE INCLUSION
 *********************************************************************************************************************/
#if (!defined NVM_H_)
#define NVM_H_

/**********************************************************************************************************************
 * VERSION IDENTIFICATION
 *********************************************************************************************************************/
#define NVM_VENDOR_ID              (30u)
#define NVM_MODULE_ID              (20u)

#define NVM_AR_RELEASE_MAJOR_VERSION       (4u)
#define NVM_AR_RELEASE_MINOR_VERSION       (0u)
#define NVM_AR_RELEASE_REVISION_VERSION    (3u)

#define NVM_SW_MAJOR_VERSION       (5u)
#define NVM_SW_MINOR_VERSION       (8u)
#define NVM_SW_PATCH_VERSION       (0u)

/**********************************************************************************************************************
 * API RELEVANT (PUBLIC) SECTION OF CONFIGURATION
 *********************************************************************************************************************/
#include "NvM_Cfg.h"

/**********************************************************************************************************************
 * API DEFINES
 *********************************************************************************************************************/
/* development errors */
#define NVM_E_NO_ERROR                  (0x00u)
#define NVM_E_PARAM_BLOCK_ID            (0x0Au)
#define NVM_E_PARAM_BLOCK_TYPE          (0x0Bu)
#define NVM_E_PARAM_BLOCK_DATA_IDX      (0x0Cu)
#define NVM_E_PARAM_ADDRESS             (0x0Du)

#define NVM_E_PARAM_DATA                (0x0Eu)

#define NVM_E_NOT_INITIALIZED           (0x14u)
#define NVM_E_BLOCK_PENDING             (0x15u)
#define NVM_E_BLOCK_CONFIG              (0x18u)

/**********************************************************************************************************************
 * API FUNCTIONS
 *********************************************************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 * NvM_Init
 *********************************************************************************************************************/
/*! \brief Initializes component.
 *  \details Service for basic NVRAM manager initialization: initializes internal structures and the state machines.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 *  \trace CREQ-723
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_Init(void);

/**********************************************************************************************************************
 *  NvM_SetDataIndex
 **********************************************************************************************************************/
/*! \brief Set the NvM block specific dataindex
 *  \details The request shall set the index to associate a dataset NV/ROM block with its corresponding RAM block.
 *  \param[in] BlockId
 *  \param[in] DataIndex
 *  \return dataindex was set: E_OK, otherwise: E_NOT_OK
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous TRUE
 *  \config At least one NvM block has datasets
 *  \pre -
 *  \trace CREQ-734
 */
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetDataIndex
    (
        NvM_BlockIdType BlockId,
        uint8 DataIndex
    );

/**********************************************************************************************************************
 *  NvM_GetDataIndex
 **********************************************************************************************************************/
/*! \brief Saves current NvM block
 *  \details The request shall get the current index (association) of a dataset NV/ROM block with its corresponding RAM block.
 *  \param[in] BlockId
 *  \param[in,out] DataIndexPtr
 *  \return E_OK dataindex was saved in DataIndexPtr
 *  \return E_NOT_OK otherwise
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous TRUE
 *  \config At least one NvM block has datasets
 *  \pre -
 *  \trace CREQ-735
 */
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_GetDataIndex
    (
        NvM_BlockIdType BlockId,
        P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DataIndexPtr
    );

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
/**********************************************************************************************************************
 *  NvM_SetBlockProtection
 **********************************************************************************************************************/
/*! \brief Set NvM block specific protection
 *  \details The request shall set/reset the write protection for the NV block. This shall be done by setting the write
 *           lock attribute in the administrative part of the corresponding RAM block. Any further write/erase requests
 *           to the NVRAM block shall be rejected synchronously if the NV block write protection is set. The data area
 *           of the RAM block shall remain writeable in case of write protection.
 *  \param[in] BlockId
 *  \param[in] ProtectionEnabled
 *  \return E_OK protection was set
 *  \return E_NOT_OK otherwise
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous TRUE
 *  \config NvM configuration class is 3
 *  \pre -
 *  \trace CREQ-736
 */
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetBlockProtection
    (
        NvM_BlockIdType BlockId,
        boolean ProtectionEnabled
    );
#endif /* (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

/**********************************************************************************************************************
 *  NvM_GetErrorStatus
 **********************************************************************************************************************/
/*! \brief Saves NvM block specific result in given pointer
 *  \details The request shall read the block dependent error/status information in the administrative part of a RAM block.
 *           The status/error information shall be set by a former or current asynchronous request.
 *  \param[in] BlockId
 *  \param[in,out] RequestResultPtr
 *  \return E_OK result was saved in RequestResultPtr
 *  \return E_NOT_OK otherwise
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous TRUE
 *  \pre -
 *  \trace CREQ-765
 */
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_GetErrorStatus
    (
        NvM_BlockIdType BlockId,
        P2VAR(NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr
    );

#if (NVM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  NvM_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief saved NvM version information in given pointer
 *  \details The request shall read the version info of the module: Module Id, Vendor Id, Vendor specific version numbers
 *  \param[in,out] Versioninfo
 *  \return E_OK current version information were saved in versionInfo
 *  \return E_NOT_OK otherwise
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous TRUE
 *  \config NvMVersionInfoApi is enabled
 *  \pre -
 *  \trace CREQ-739
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_GetVersionInfo
    (
        P2VAR(Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA) Versioninfo
    );
#endif /* (NVM_VERSION_INFO_API == STD_ON) */

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
/**********************************************************************************************************************
 *  NvM_SetRamBlockStatus
 **********************************************************************************************************************/
/*! \brief Sets the NvM block specific RAM status
 *  \details The request shall set a permanent RAM block to the valid or the invalid state.
 *  \param[in] BlockId
 *  \param[in] BlockChanged
 *  \return E_OK RAM status set
 *  \return E_NOT_OK RAM status not set
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous TRUE
 *  \config NvMSetRamBlockStatusApi is enabled
 *  \pre -
 *  \trace CREQ-738
 */
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_SetRamBlockStatus
    (
        NvM_BlockIdType BlockId,
        boolean BlockChanged
    );
#endif /* (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) */

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)
/**********************************************************************************************************************
 *  NvM_ReadBlock
 **********************************************************************************************************************/
/*! \brief Setups a read job for given NvM block
 *  \details Request to copy the data of the NV block to its corresponding RAM block. If the block to be written is
 *           permanent a NULL_PTR shall be given as parameter, otherwise a pointer to the ram block shall be given.
 *  \param[in] BlockId
 *  \param[in] NvM_DstPtr
 *  \return E_OK job was setup
 *  \return E_NOT_OK otherwise
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous FALSE
 *  \config NvM configuration class is 2 or 3
 *  \pre -
 *  \trace CREQ-724
 */
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_ReadBlock
    (
        NvM_BlockIdType BlockId,
        P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
    );

/**********************************************************************************************************************
 *  NvM_WriteBlock
 **********************************************************************************************************************/
/*! \brief Setups a write job for given NvM block
 *  \details Request to copy the data of the RAM block to its corresponding NV block. If the block to be written is
 *           permanent a NULL_PTR shall be given as parameter, otherwise a pointer to the ram block shall be given.
 *  \param[in] BlockId
 *  \param[in] NvM_SrcPtr
 *  \return E_OK job was setup
 *  \return E_NOT_OK otherwise
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous FALSE
 *  \config NvM configuration class is 2 or 3
 *  \pre -
 *  \trace CREQ-725
 */
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_WriteBlock
    (
        NvM_BlockIdType BlockId,
        P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
    );

/**********************************************************************************************************************
 *  NvM_RestoreBlockDefaults
 **********************************************************************************************************************/
/*! \brief Setups a restore block defaults job for given NvM block
 *  \details Request to restore the ROM block default data to its corresponding RAM block. If the ram block is not
 *           permanent NvM_DstPtr shall be used as output pointer, otherwise a NULL_PTR shall be handed.
 *  \param[in] BlockId
 *  \param[in] NvM_DstPtr
 *  \return E_OK job was setup
 *  \return E_NOT_OK otherwise
 *  \context ANY
 *  \reentrant FALSE
 *  \synchronous FALSE
 *  \config NvM configuration class is 2 or 3
 *  \pre -
 *  \trace CREQ-728
 */
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_RestoreBlockDefaults
    (
        NvM_BlockIdType BlockId,
        P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
    );
#endif /* (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) */

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
/**********************************************************************************************************************
 *  NvM_EraseNvBlock
 **********************************************************************************************************************/
/*! \brief Setups an erase job for given NvM block
 *  \details Request to erase a NV block. The content of the RAM block shall remain unmodified.
 *  \param[in] BlockId
 *  \return E_OK job was setup
 *  \return E_NOT_OK otherwise
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous FALSE
 *  \config NvM configuration class is 3
 *  \pre -
 *  \trace CREQ-726
 */
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_EraseNvBlock
    (
        NvM_BlockIdType BlockId
    );

/**********************************************************************************************************************
 *  NvM_InvalidateNvBlock
 **********************************************************************************************************************/
/*! \brief Setups an invalidate job for given NvM block
 *  \details Request to invalidate a NV block. The RAM block shall remain unmodified.
 *  \param[in] BlockId
 *  \return E_OK job was setup
 *  \return E_NOT_OK otherwise
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous FALSE
 *  \config NvM configuration class is 3
 *  \pre -
 *  \trace CREQ-727
 */
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_InvalidateNvBlock
    (
        NvM_BlockIdType BlockId
    );
#endif /* (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

#if (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1)
/**********************************************************************************************************************
 *  NvM_CancelJobs
 **********************************************************************************************************************/
/*! \brief Cancels currently pending job for given NvM block
 *  \details Request to cancel all jobs pending in the queue for the specified NV Block.
 *  \param[in] BlockId
 *  \return E_OK job was canceled
 *  \return E_NOT_OK otherwise
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous FALSE
 *  \config NvM configuration class is 2 or 3
 *  \pre -
 *  \trace CREQ-729
 */
extern FUNC(Std_ReturnType, NVM_PUBLIC_CODE) NvM_CancelJobs
    (
        NvM_BlockIdType BlockId
    );
#endif /* (NVM_API_CONFIG_CLASS > NVM_API_CONFIG_CLASS_1) */

/**********************************************************************************************************************
 *  NvM_ReadAll
 **********************************************************************************************************************/
/*! \brief Setups a read all job
 *  \details Request to read the data of all configured RAM blocks from their corresponding NV blocks.
 *           Only the data of valid NV blocks is read.
 *  \context ANY
 *  \reentrant FALSE
 *  \synchronous FALSE
 *  \pre -
 *  \trace CREQ-730
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_ReadAll(void);

/**********************************************************************************************************************
 *  NvM_WriteAll
 **********************************************************************************************************************/
/*! \brief Setups a write all job
 *  \details Request to copy the data of all configured RAM blocks to their corresponding NV blocks.
 *           Only the data of valid RAM blocks shall be written.
 *  \context ANY
 *  \reentrant FALSE
 *  \synchronous FALSE
 *  \pre -
 *  \trace CREQ-731
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_WriteAll(void);

/**********************************************************************************************************************
 *  NvM_CancelWriteAll
 **********************************************************************************************************************/
/*! \brief Cancel pending write all job
 *  \details Request to cancel a pending WriteAll request.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous FALSE
 *  \pre -
 *  \trace CREQ-732
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_CancelWriteAll(void);

#if (NVM_KILL_WRITEALL_API == STD_ON)
/**********************************************************************************************************************
 *  NvM_KillWriteAll
 **********************************************************************************************************************/
/*! \brief Kills pending write all job.
 *  \details Request to kill a pending WriteAll request, i.e. To cancel it destructively (in contrast to NvM_Cancelwriteall)
 *           It shall only called by EcuM (or comparable SW)
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous FALSE
 *  \config NvMKillWriteAllApi is enabled
 *  \pre -
 *  \trace CREQ-733
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_KillWriteAll(void);
#endif /* (NVM_KILL_WRITEALL_API == STD_ON) */

#if (NVM_REPAIR_REDUNDANT_BLOCKS_API == STD_ON)
/**********************************************************************************************************************
 *  NvM_RepairRedundantBlocks
 **********************************************************************************************************************/
/*! \brief Checks all configured redundant blocks redundancy within NV RAM and tries to restore the redundancy, in case it's lost.
 *  \details Repairing works as background job, which is non-destructively interruptible via any single or multi block
 *           jobs. The job will be resumed after the interrupting job is done and there is no other job setup.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous FALSE
 *  \config RepairRedundantBlocksApi is enabled
 *  \pre -
 *  \trace CREQ-909
 */
FUNC(void, NVM_PUBLIC_CODE) NvM_RepairRedundantBlocks(void);
#endif

/**********************************************************************************************************************
 *  NvM_MainFunction
 **********************************************************************************************************************/
/*! \brief Processed jobs
 *  \details This  function shall perform the processing of the NVRAM Manager jobs. Therefore it has to be called cyclically.
 *  \context TASK
 *  \reentrant FALSE
 *  \synchronous TRUE
 *  \pre -
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_MainFunction(void);

/**********************************************************************************************************************
 *  NvM_SetBlockLockStatus
 **********************************************************************************************************************/
/*! \brief Set the NvM block specific lock status
 *  \details The request shall set/reset the lock status for the NV block. This shall be done by setting the lock status
 *           attribute in the administrative part of the corresponding RAM block. The NV contents associated to the NVRAM
 *           block identified by BlockId, will not be modified by any request. The Block shall be skipped during NvM_WriteAll.
 *           Other write/erase requests shall be rejected. At processing NvM_ReadAll a locked block shall be loaded from
 *           NV memory.write protection.
 *  \param[in] BlockId
 *  \param[in] BlockLocked
 *  \context ANY
 *  \reentrant TRUE
 *  \synchronous TRUE
 *  \pre -
 *  \trace CREQ-737
 */
extern FUNC(void, NVM_PUBLIC_CODE) NvM_SetBlockLockStatus
    (
        NvM_BlockIdType BlockId,
        boolean BlockLocked
    );

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*!
 * \exclusivearea NvM_NVM_EXCLUSIVE_AREA_0
 * Ensures consistency while modifying internal variables.
 * \protects Internal variables
 * \usedin NvM_EnterCriticalSection, NvM_ExitCriticalSection
 * \exclude -
 * \length SHORT Only a few statements.
 * \endexclusivearea
 */

#endif

/* ---- End of File --------------------------------------------------------- */
