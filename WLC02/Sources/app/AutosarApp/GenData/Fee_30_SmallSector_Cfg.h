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
 *            Module: Fee
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Fee_30_SmallSector_Cfg.h
 *   Generation Time: 2020-09-21 13:39:15
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
#ifndef FEE_30_SMALLSECTOR_CFG_H_PUBLIC
# define FEE_30_SMALLSECTOR_CFG_H_PUBLIC
 
/**********************************************************************************************************************
 *  GENERAL DEFINE BLOCK
 *********************************************************************************************************************/
 
#ifndef FEE_USE_DUMMY_STATEMENT
#define FEE_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/EcuC/EcucGeneral/DummyStatement */
#endif
#ifndef FEE_DUMMY_STATEMENT
#define FEE_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef FEE_DUMMY_STATEMENT_CONST
#define FEE_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef FEE_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define FEE_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef FEE_ATOMIC_VARIABLE_ACCESS
#define FEE_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef FEE_PROCESSOR_RH850_1649
#define FEE_PROCESSOR_RH850_1649
#endif
#ifndef FEE_COMP_GREENHILLS
#define FEE_COMP_GREENHILLS
#endif
#ifndef FEE_GEN_GENERATOR_MSR
#define FEE_GEN_GENERATOR_MSR
#endif
#ifndef FEE_CPUTYPE_BITORDER_LSB2MSB
#define FEE_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef FEE_CONFIGURATION_VARIANT_PRECOMPILE
#define FEE_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef FEE_CONFIGURATION_VARIANT_LINKTIME
#define FEE_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef FEE_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define FEE_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef FEE_CONFIGURATION_VARIANT
#define FEE_CONFIGURATION_VARIANT FEE_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef FEE_POSTBUILD_VARIANT_SUPPORT
#define FEE_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* This is not the sub-package version but a compatibility version, which will only be updated if a change in the 
   generator (i.e. generated files) affects the implementation sub-package */
#define FEE_30_SMALLSECTOR_CFG_MAJOR_VERSION    (2u) 
#define FEE_30_SMALLSECTOR_CFG_MINOR_VERSION    (0u) 

/**** Pre-compile switches for FEE development error checks ***********************************************************/

#define FEE_30_SMALLSECTOR_DEV_ERROR_DETECT	(STD_ON)
#define FEE_30_SMALLSECTOR_DEV_ERROR_REPORT	(STD_ON)
#include "Det.h"

/***** Optional API functions **************************************************************************************/

#define FEE_30_SMALLSECTOR_VERSION_INFO_API STD_OFF

/**** Symbolic block names **************************************************************************/
  
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration     16u 
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_001 32u 
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_002 48u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor        64u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_001    80u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_002    96u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_003    112u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_004    128u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_005    144u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_006    160u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_007    176u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_008    192u 
#define FeeConf_FeeBlockConfiguration_FeeDemStatusDataBlock     208u 
#define FeeConf_FeeBlockConfiguration_FeeDemAdminDataBlock      224u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_009    240u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_010    256u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_011    272u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_012    288u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_013    304u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_014    320u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_015    336u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_016    352u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_017    368u 
#define FeeConf_FeeBlockConfiguration_FeeBlockDescriptor_018    384u 


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
typedef uint32 Fee_30_SmallSector_AddressType;

/**********************************************************************************************************************
 *  MODULE RELEVANT CONFIGURATION
 *********************************************************************************************************************/
 
#ifdef FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "Fls.h" 

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_LAYER_ONE_INDEX             (0x00U)
#define FEE_30_SMALLSECTOR_LAYER_TWO_INDEX             (0x01U)
#define FEE_30_SMALLSECTOR_LAYER_THREE_INDEX           (0x02U)

/****  FLS Configuration *********************************************************************************************/

#define FEE_30_SMALLSECTOR_NUMBER_OF_FLS_DEVICES       (1u)

/****  FEE Configuration *********************************************************************************************/

#define FEE_30_SMALLSECTOR_FLS_POLLING_MODE            (STD_ON)
#define FEE_30_SMALLSECTOR_CORRECT_SINGLE_BIT_FLIPS    (STD_OFF)
#define FEE_30_SMALLSECTOR_MANAGEMENT_SIZE             (1u)
#define FEE_30_SMALLSECTOR_MAX_BLOCKS_PER_PARTITION    (24u)
#define FEE_30_SMALLSECTOR_NUMBER_OF_PARTITIONS        (1u)
#define FEE_30_SMALLSECTOR_NUMBER_OF_BLOCKS            (24u)
#define FEE_30_SMALLSECTOR_MAX_WRITE_ALIGNMENT         (4u)
#define FEE_30_SMALLSECTOR_MAX_READ_SIZE               (9u)

#define FEE_30_SMALLSECTOR_STATIC_PATTERN              (0xAAu)

/****  NVM Configuration *********************************************************************************************/

#define FEE_30_SMALLSECTOR_NVM_POLLING_MODE            (STD_ON)

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Function pointer prototypes for FLS API services */
typedef P2VAR(uint8, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_DataPtr;
typedef P2CONST(uint8, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_ConstDataPtr;

typedef P2FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_ReadPtrType)(Fls_AddressType FlsAddress, Fee_30_SmallSector_DataPtr TargetAddressPtr, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_WritePtrType)(Fls_AddressType FlsAddress, Fee_30_SmallSector_ConstDataPtr SourceAddressPtr, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_ComparePtrType)(Fls_AddressType FlsAddress, Fee_30_SmallSector_ConstDataPtr DataBufferPtr, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_ErasePtrType)(Fls_AddressType FlsAddress, Fls_LengthType Length);
typedef P2FUNC(Std_ReturnType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_BlankCheckPtrType)(Fls_AddressType FlsAddress, Fls_LengthType Length);
typedef P2FUNC(MemIf_StatusType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_GetStatusPtrType)(void);
typedef P2FUNC(MemIf_JobResultType, FEE_30_SMALLSECTOR_PRIVATE_CODE, Fee_30_SmallSector_GetJobResultPtrType)(void);

typedef struct
{
	Fee_30_SmallSector_ReadPtrType Read;
	Fee_30_SmallSector_WritePtrType Write;
	Fee_30_SmallSector_ComparePtrType Compare;
	Fee_30_SmallSector_ErasePtrType Erase;
	Fee_30_SmallSector_BlankCheckPtrType BlankCheck;
	Fee_30_SmallSector_GetStatusPtrType GetStatus;
	Fee_30_SmallSector_GetJobResultPtrType GetJobResult;
} Fee_30_SmallSector_FlsApiType;

typedef P2CONST(Fee_30_SmallSector_FlsApiType, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_FlsApiPtrType;
  
typedef struct
{
    Fee_30_SmallSector_AddressType PartitionStartAddress;
    uint16 PartitionAddressAlignment;
    uint16 PartitionWriteAlignment;
    uint16 PartitionReadAlignment;
    uint16 FlsDeviceIndex;
    Fee_30_SmallSector_FlsApiPtrType FlsApiPtr;
    uint8 FlsEraseValue;
    boolean BlankCheckApiEnabled;
    uint16 BlockNumberList[FEE_30_SMALLSECTOR_MAX_BLOCKS_PER_PARTITION];
} Fee_30_SmallSector_PartitionConfigType;

typedef struct
{
    Fee_30_SmallSector_AddressType BlockStartAddress;
    uint16 DataLength;
    uint8 NumberOfInstances;
    uint8 NumberOfDatasets;
    boolean IsImmediateData;
    boolean HasVerificationEnabled;
} Fee_30_SmallSector_BlockConfigType;


/* Function pointer prototypes NvM callback routines */

typedef P2FUNC(void, FEE_30_SMALLSECTOR_NVM_CODE, Fee_30_SmallSector_CbkJobEndNotificationType)(void);
typedef P2FUNC(void, FEE_30_SMALLSECTOR_NVM_CODE, Fee_30_SmallSector_CbkJobErrorNotificationType)(void);

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_START_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */

extern CONST(uint8, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_DatasetSelectionBits;

#define FEE_30_SMALLSECTOR_STOP_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */


#define FEE_30_SMALLSECTOR_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	/* PRQA S 5087 */  /* MD_MSR_MemMap */
  
extern CONST(Fee_30_SmallSector_PartitionConfigType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_PartitionConfigList[FEE_30_SMALLSECTOR_NUMBER_OF_PARTITIONS];
extern CONST(Fee_30_SmallSector_BlockConfigType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_BlockConfigList[FEE_30_SMALLSECTOR_NUMBER_OF_BLOCKS];
extern CONST(Fee_30_SmallSector_FlsApiType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_FlsApi0; 


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/* Function pointers to the callback routines of the NvM. */
extern CONST(Fee_30_SmallSector_CbkJobEndNotificationType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_CbkJobEndNotification;
extern CONST(Fee_30_SmallSector_CbkJobErrorNotificationType, FEE_30_SMALLSECTOR_PRIVATE_CONST) Fee_30_SmallSector_CbkJobErrorNotification;

#define FEE_30_SMALLSECTOR_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	/* PRQA S 5087 */  /* MD_MSR_MemMap */


#endif /* FEE_30_SMALLSECTOR_IMPLEMENTATION_SOURCE */

#endif /* FEE_30_SMALLSECTOR_CFG_H_PUBLIC */

/**********************************************************************************************************************
 *  END OF FILE: Fee_30_SmallSector_Cfg.h
 *********************************************************************************************************************/

