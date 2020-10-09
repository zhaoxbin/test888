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
 *            Module: CanTrcv
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CanTrcv_30_Tja1040_Cfg.h
 *   Generation Time: 2019-11-29 11:59:10
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


#if !defined(CANTRCV_30_TJA1040_CFG_H)
#define CANTRCV_30_TJA1040_CFG_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
/* SREQ00010148 */
# include "ComStack_Types.h" 
# include "Can_GeneralTypes.h"


//#include "Dio.h"
#include "CanIf.h"
#include "EcuM_Cbk.h"



/**********************************************************************************************************************
  VERSION DEFINES (Adapted with: ESCAN00086365)
**********************************************************************************************************************/
#define DRVTRANS_CAN_30_TJA1040_GENTOOL_CFG5_MAJOR_VERSION 0x03u
#define DRVTRANS_CAN_30_TJA1040_GENTOOL_CFG5_MINOR_VERSION 0x02u
#define DRVTRANS_CAN_30_TJA1040_GENTOOL_CFG5_PATCH_VERSION 0x00u

#define CANTRCV_30_TJA1040_GENTOOL_CFG5_BASE_COMP_VERSION 0x0105u
#define CANTRCV_30_TJA1040_GENTOOL_CFG5_HW_COMP_VERSION   0x0103u


/**********************************************************************************************************************
  SWITCHES (BASE)
**********************************************************************************************************************/
#define CANTRCV_30_TJA1040_MAX_CHANNEL                       1u
#define CANTRCV_30_TJA1040_GENERAL_WAKE_UP_SUPPORT           CANTRCV_30_TJA1040_WAKEUP_BY_POLLING
#define CANTRCV_30_TJA1040_WAKEUP_BY_BUS_USED                STD_ON
#define CANTRCV_30_TJA1040_GET_VERSION_INFO                  STD_ON
#define CANTRCV_30_TJA1040_DEV_ERROR_DETECT                  STD_OFF
#define CANTRCV_30_TJA1040_DEV_ERROR_REPORT                  STD_OFF
#define CANTRCV_30_TJA1040_ECUC_SAFE_BSW_CHECKS              STD_OFF
#define CANTRCV_30_TJA1040_PROD_ERROR_DETECT                 STD_OFF 
#define CANTRCV_30_TJA1040_INSTANCE_ID                       0
#define CANTRCV_30_TJA1040_HW_PN_SUPPORT                     STD_OFF
#define CANTRCV_30_TJA1040_BUS_ERR_FLAG                      STD_OFF
#define CANTRCV_30_TJA1040_VERIFY_DATA                       STD_ON  
#define CANTRCV_30_TJA1040_SPI_ACCESS_SYNCHRONOUS            STD_OFF
#define CANTRCV_30_TJA1040_USE_ICU                           STD_OFF
#define CANTRCV_30_TJA1040_USE_EXTENDED_WU_SRC               STD_OFF
#define CANTRCV_30_TJA1040_SET_OP_MODE_WAIT_TIME_SUPPORT     STD_OFF


#define CanTrcv_30_Tja1040_CanTrcvChannel 0u 


#ifndef CANTRCV_30_TJA1040_USE_DUMMY_STATEMENT
#define CANTRCV_30_TJA1040_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/EcuC/EcucGeneral/DummyStatement */
#endif
#ifndef CANTRCV_30_TJA1040_DUMMY_STATEMENT
#define CANTRCV_30_TJA1040_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CANTRCV_30_TJA1040_DUMMY_STATEMENT_CONST
#define CANTRCV_30_TJA1040_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CANTRCV_30_TJA1040_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define CANTRCV_30_TJA1040_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef CANTRCV_30_TJA1040_ATOMIC_VARIABLE_ACCESS
#define CANTRCV_30_TJA1040_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef CANTRCV_30_TJA1040_PROCESSOR_RH850_1649
#define CANTRCV_30_TJA1040_PROCESSOR_RH850_1649
#endif
#ifndef CANTRCV_30_TJA1040_COMP_GREENHILLS
#define CANTRCV_30_TJA1040_COMP_GREENHILLS
#endif
#ifndef CANTRCV_30_TJA1040_GEN_GENERATOR_MSR
#define CANTRCV_30_TJA1040_GEN_GENERATOR_MSR
#endif
#ifndef CANTRCV_30_TJA1040_CPUTYPE_BITORDER_LSB2MSB
#define CANTRCV_30_TJA1040_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef CANTRCV_30_TJA1040_CONFIGURATION_VARIANT_PRECOMPILE
#define CANTRCV_30_TJA1040_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef CANTRCV_30_TJA1040_CONFIGURATION_VARIANT_LINKTIME
#define CANTRCV_30_TJA1040_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef CANTRCV_30_TJA1040_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define CANTRCV_30_TJA1040_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef CANTRCV_30_TJA1040_CONFIGURATION_VARIANT
#define CANTRCV_30_TJA1040_CONFIGURATION_VARIANT CANTRCV_30_TJA1040_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef CANTRCV_30_TJA1040_POSTBUILD_VARIANT_SUPPORT
#define CANTRCV_30_TJA1040_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/**********************************************************************************************************************
  SWITCHES (HW SPECIFIC)
**********************************************************************************************************************/
 

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanTrcv_30_Tja1040PCDataSwitches  CanTrcv_30_Tja1040 Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CANTRCV_30_TJA1040_CHANNEL                                    STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_Channel' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define CANTRCV_30_TJA1040_ICUCHANNELOFCHANNEL                        STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_Channel.IcuChannel' Reason: 'No "ICU" is configured.' */
#define CANTRCV_30_TJA1040_ICUCHANNELSETOFCHANNEL                     STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_Channel.IcuChannelSet' Reason: 'No "ICU" is configured.' */
#define CANTRCV_30_TJA1040_CHANNELUSED                                STD_ON
#define CANTRCV_30_TJA1040_DIOCONFIGURATION                           STD_ON
#define CANTRCV_30_TJA1040_PINRXDOFDIOCONFIGURATION                   STD_ON
#define CANTRCV_30_TJA1040_PINSTBOFDIOCONFIGURATION                   STD_ON
#define CANTRCV_30_TJA1040_FINALMAGICNUMBER                           STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define CANTRCV_30_TJA1040_GENERATORCOMPATIBILITYVERSION              STD_ON
#define CANTRCV_30_TJA1040_INITDATAHASHCODE                           STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define CANTRCV_30_TJA1040_SIZEOFCHANNELUSED                          STD_ON
#define CANTRCV_30_TJA1040_SIZEOFDIOCONFIGURATION                     STD_ON
#define CANTRCV_30_TJA1040_SIZEOFWAKEUPBYBUSUSED                      STD_ON
#define CANTRCV_30_TJA1040_SIZEOFWAKEUPSOURCE                         STD_ON
#define CANTRCV_30_TJA1040_WAKEUPBYBUSUSED                            STD_ON
#define CANTRCV_30_TJA1040_WAKEUPSOURCE                               STD_ON
#define CANTRCV_30_TJA1040_WUSRCPOR                                   STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_WuSrcPor' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define CANTRCV_30_TJA1040_WUSRCSYSERR                                STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_WuSrcSyserr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define CANTRCV_30_TJA1040_PCCONFIG                                   STD_ON
#define CANTRCV_30_TJA1040_CHANNELUSEDOFPCCONFIG                      STD_ON
#define CANTRCV_30_TJA1040_DIOCONFIGURATIONOFPCCONFIG                 STD_ON
#define CANTRCV_30_TJA1040_FINALMAGICNUMBEROFPCCONFIG                 STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define CANTRCV_30_TJA1040_GENERATORCOMPATIBILITYVERSIONOFPCCONFIG    STD_ON
#define CANTRCV_30_TJA1040_INITDATAHASHCODEOFPCCONFIG                 STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define CANTRCV_30_TJA1040_SIZEOFCHANNELUSEDOFPCCONFIG                STD_ON
#define CANTRCV_30_TJA1040_SIZEOFDIOCONFIGURATIONOFPCCONFIG           STD_ON
#define CANTRCV_30_TJA1040_SIZEOFWAKEUPBYBUSUSEDOFPCCONFIG            STD_ON
#define CANTRCV_30_TJA1040_SIZEOFWAKEUPSOURCEOFPCCONFIG               STD_ON
#define CANTRCV_30_TJA1040_WAKEUPBYBUSUSEDOFPCCONFIG                  STD_ON
#define CANTRCV_30_TJA1040_WAKEUPSOURCEOFPCCONFIG                     STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  CanTrcv_30_Tja1040PCIsReducedToDefineDefines  CanTrcv_30_Tja1040 Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define CANTRCV_30_TJA1040_ISDEF_CHANNELUSED                          STD_OFF
#define CANTRCV_30_TJA1040_ISDEF_PINRXDOFDIOCONFIGURATION             STD_OFF
#define CANTRCV_30_TJA1040_ISDEF_PINSTBOFDIOCONFIGURATION             STD_OFF
#define CANTRCV_30_TJA1040_ISDEF_WAKEUPBYBUSUSED                      STD_OFF
#define CANTRCV_30_TJA1040_ISDEF_WAKEUPSOURCE                         STD_OFF
#define CANTRCV_30_TJA1040_ISDEF_CHANNELUSEDOFPCCONFIG                STD_ON
#define CANTRCV_30_TJA1040_ISDEF_DIOCONFIGURATIONOFPCCONFIG           STD_ON
#define CANTRCV_30_TJA1040_ISDEF_WAKEUPBYBUSUSEDOFPCCONFIG            STD_ON
#define CANTRCV_30_TJA1040_ISDEF_WAKEUPSOURCEOFPCCONFIG               STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  CanTrcv_30_Tja1040PCEqualsAlwaysToDefines  CanTrcv_30_Tja1040 Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define CANTRCV_30_TJA1040_EQ2_CHANNELUSED                            
#define CANTRCV_30_TJA1040_EQ2_PINRXDOFDIOCONFIGURATION               
#define CANTRCV_30_TJA1040_EQ2_PINSTBOFDIOCONFIGURATION               
#define CANTRCV_30_TJA1040_EQ2_WAKEUPBYBUSUSED                        
#define CANTRCV_30_TJA1040_EQ2_WAKEUPSOURCE                           
#define CANTRCV_30_TJA1040_EQ2_CHANNELUSEDOFPCCONFIG                  CanTrcv_30_Tja1040_ChannelUsed
#define CANTRCV_30_TJA1040_EQ2_DIOCONFIGURATIONOFPCCONFIG             CanTrcv_30_Tja1040_DioConfiguration
#define CANTRCV_30_TJA1040_EQ2_WAKEUPBYBUSUSEDOFPCCONFIG              CanTrcv_30_Tja1040_WakeupByBusUsed
#define CANTRCV_30_TJA1040_EQ2_WAKEUPSOURCEOFPCCONFIG                 CanTrcv_30_Tja1040_WakeupSource
/** 
  \}
*/ 

/** 
  \defgroup  CanTrcv_30_Tja1040PCSymbolicInitializationPointers  CanTrcv_30_Tja1040 Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define CanTrcv_30_Tja1040_Config_Ptr                                 NULL_PTR  /**< symbolic identifier which shall be used to initialize 'CanTrcv_30_Tja1040' */
/** 
  \}
*/ 

/** 
  \defgroup  CanTrcv_30_Tja1040PCInitializationSymbols  CanTrcv_30_Tja1040 Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define CanTrcv_30_Tja1040_Config                                     NULL_PTR  /**< symbolic identifier which could be used to initialize 'CanTrcv_30_Tja1040 */
/** 
  \}
*/ 

/** 
  \defgroup  CanTrcv_30_Tja1040PCGeneral  CanTrcv_30_Tja1040 General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define CANTRCV_30_TJA1040_CHECK_INIT_POINTER                         STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define CANTRCV_30_TJA1040_FINAL_MAGIC_NUMBER                         0x461Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of CanTrcv_30_Tja1040 */
#define CANTRCV_30_TJA1040_INDIVIDUAL_POSTBUILD                       STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'CanTrcv_30_Tja1040' is not configured to be postbuild capable. */
#define CANTRCV_30_TJA1040_INIT_DATA                                  CANTRCV_30_TJA1040_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define CANTRCV_30_TJA1040_INIT_DATA_HASH_CODE                        -886254778  /**< the precompile constant to validate the initialization structure at initialization time of CanTrcv_30_Tja1040 with a hashcode. The seed value is '0x461Eu' */
#define CANTRCV_30_TJA1040_USE_ECUM_BSW_ERROR_HOOK                    STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define CANTRCV_30_TJA1040_USE_INIT_POINTER                           STD_OFF  /**< STD_ON if the init pointer CanTrcv_30_Tja1040 shall be used. */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanTrcv_30_Tja1040LTDataSwitches  CanTrcv_30_Tja1040 Data Switches  (LINK)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CANTRCV_30_TJA1040_LTCONFIG                                   STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_LTConfig' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanTrcv_30_Tja1040PBDataSwitches  CanTrcv_30_Tja1040 Data Switches  (POST_BUILD)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define CANTRCV_30_TJA1040_PBCONFIG                                   STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_PBConfig' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define CANTRCV_30_TJA1040_LTCONFIGIDXOFPBCONFIG                      STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_PBConfig.LTConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define CANTRCV_30_TJA1040_PCCONFIGIDXOFPBCONFIG                      STD_OFF  /**< Deactivateable: 'CanTrcv_30_Tja1040_PBConfig.PCConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
/** 
  \}
*/ 



/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  CanTrcv_30_Tja1040PCGetConstantDuplicatedRootDataMacros  CanTrcv_30_Tja1040 Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define CanTrcv_30_Tja1040_GetChannelUsedOfPCConfig()                 CanTrcv_30_Tja1040_ChannelUsed  /**< the pointer to CanTrcv_30_Tja1040_ChannelUsed */
#define CanTrcv_30_Tja1040_GetDioConfigurationOfPCConfig()            CanTrcv_30_Tja1040_DioConfiguration  /**< the pointer to CanTrcv_30_Tja1040_DioConfiguration */
#define CanTrcv_30_Tja1040_GetGeneratorCompatibilityVersionOfPCConfig() 0x01050103u
#define CanTrcv_30_Tja1040_GetSizeOfChannelUsedOfPCConfig()           1u  /**< the number of accomplishable value elements in CanTrcv_30_Tja1040_ChannelUsed */
#define CanTrcv_30_Tja1040_GetSizeOfDioConfigurationOfPCConfig()      1u  /**< the number of accomplishable value elements in CanTrcv_30_Tja1040_DioConfiguration */
#define CanTrcv_30_Tja1040_GetSizeOfWakeupByBusUsedOfPCConfig()       1u  /**< the number of accomplishable value elements in CanTrcv_30_Tja1040_WakeupByBusUsed */
#define CanTrcv_30_Tja1040_GetSizeOfWakeupSourceOfPCConfig()          1u  /**< the number of accomplishable value elements in CanTrcv_30_Tja1040_WakeupSource */
#define CanTrcv_30_Tja1040_GetWakeupByBusUsedOfPCConfig()             CanTrcv_30_Tja1040_WakeupByBusUsed  /**< the pointer to CanTrcv_30_Tja1040_WakeupByBusUsed */
#define CanTrcv_30_Tja1040_GetWakeupSourceOfPCConfig()                CanTrcv_30_Tja1040_WakeupSource  /**< the pointer to CanTrcv_30_Tja1040_WakeupSource */
/** 
  \}
*/ 

/** 
  \defgroup  CanTrcv_30_Tja1040PCGetDataMacros  CanTrcv_30_Tja1040 Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define CanTrcv_30_Tja1040_IsChannelUsed(Index)                       ((CanTrcv_30_Tja1040_GetChannelUsedOfPCConfig()[(Index)]) != FALSE)
#define CanTrcv_30_Tja1040_GetPinRXDOfDioConfiguration(Index)         (CanTrcv_30_Tja1040_GetDioConfigurationOfPCConfig()[(Index)].PinRXDOfDioConfiguration)
#define CanTrcv_30_Tja1040_GetPinSTBOfDioConfiguration(Index)         (CanTrcv_30_Tja1040_GetDioConfigurationOfPCConfig()[(Index)].PinSTBOfDioConfiguration)
#define CanTrcv_30_Tja1040_IsWakeupByBusUsed(Index)                   ((CanTrcv_30_Tja1040_GetWakeupByBusUsedOfPCConfig()[(Index)]) != FALSE)
#define CanTrcv_30_Tja1040_GetWakeupSource(Index)                     ((EcuM_WakeupSourceType)CanTrcv_30_Tja1040_GetWakeupSourceOfPCConfig()[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  CanTrcv_30_Tja1040PCGetDeduplicatedDataMacros  CanTrcv_30_Tja1040 Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define CanTrcv_30_Tja1040_GetGeneratorCompatibilityVersion()         CanTrcv_30_Tja1040_GetGeneratorCompatibilityVersionOfPCConfig()
#define CanTrcv_30_Tja1040_GetSizeOfChannelUsed()                     CanTrcv_30_Tja1040_GetSizeOfChannelUsedOfPCConfig()
#define CanTrcv_30_Tja1040_GetSizeOfDioConfiguration()                CanTrcv_30_Tja1040_GetSizeOfDioConfigurationOfPCConfig()
#define CanTrcv_30_Tja1040_GetSizeOfWakeupByBusUsed()                 CanTrcv_30_Tja1040_GetSizeOfWakeupByBusUsedOfPCConfig()
#define CanTrcv_30_Tja1040_GetSizeOfWakeupSource()                    CanTrcv_30_Tja1040_GetSizeOfWakeupSourceOfPCConfig()
/** 
  \}
*/ 

/** 
  \defgroup  CanTrcv_30_Tja1040PCHasMacros  CanTrcv_30_Tja1040 Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define CanTrcv_30_Tja1040_HasChannelUsed()                           (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasDioConfiguration()                      (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasPinRXDOfDioConfiguration()              (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasPinSTBOfDioConfiguration()              (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasGeneratorCompatibilityVersion()         (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasSizeOfChannelUsed()                     (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasSizeOfDioConfiguration()                (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasSizeOfWakeupByBusUsed()                 (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasSizeOfWakeupSource()                    (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasWakeupByBusUsed()                       (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasWakeupSource()                          (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasPCConfig()                              (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasChannelUsedOfPCConfig()                 (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasDioConfigurationOfPCConfig()            (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasGeneratorCompatibilityVersionOfPCConfig() (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasSizeOfChannelUsedOfPCConfig()           (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasSizeOfDioConfigurationOfPCConfig()      (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasSizeOfWakeupByBusUsedOfPCConfig()       (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasSizeOfWakeupSourceOfPCConfig()          (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasWakeupByBusUsedOfPCConfig()             (TRUE != FALSE)
#define CanTrcv_30_Tja1040_HasWakeupSourceOfPCConfig()                (TRUE != FALSE)
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  CanTrcv_30_Tja1040PCIterableTypes  CanTrcv_30_Tja1040 Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate CanTrcv_30_Tja1040_ChannelUsed */
typedef uint8_least CanTrcv_30_Tja1040_ChannelUsedIterType;

/**   \brief  type used to iterate CanTrcv_30_Tja1040_DioConfiguration */
typedef uint8_least CanTrcv_30_Tja1040_DioConfigurationIterType;

/**   \brief  type used to iterate CanTrcv_30_Tja1040_WakeupByBusUsed */
typedef uint8_least CanTrcv_30_Tja1040_WakeupByBusUsedIterType;

/**   \brief  type used to iterate CanTrcv_30_Tja1040_WakeupSource */
typedef uint8_least CanTrcv_30_Tja1040_WakeupSourceIterType;

/** 
  \}
*/ 

/** 
  \defgroup  CanTrcv_30_Tja1040PCValueTypes  CanTrcv_30_Tja1040 Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for CanTrcv_30_Tja1040_ChannelUsed */
typedef boolean CanTrcv_30_Tja1040_ChannelUsedType;

/**   \brief  value based type definition for CanTrcv_30_Tja1040_GeneratorCompatibilityVersion */
typedef uint32 CanTrcv_30_Tja1040_GeneratorCompatibilityVersionType;

/**   \brief  value based type definition for CanTrcv_30_Tja1040_SizeOfChannelUsed */
typedef uint8 CanTrcv_30_Tja1040_SizeOfChannelUsedType;

/**   \brief  value based type definition for CanTrcv_30_Tja1040_SizeOfDioConfiguration */
typedef uint8 CanTrcv_30_Tja1040_SizeOfDioConfigurationType;

/**   \brief  value based type definition for CanTrcv_30_Tja1040_SizeOfWakeupByBusUsed */
typedef uint8 CanTrcv_30_Tja1040_SizeOfWakeupByBusUsedType;

/**   \brief  value based type definition for CanTrcv_30_Tja1040_SizeOfWakeupSource */
typedef uint8 CanTrcv_30_Tja1040_SizeOfWakeupSourceType;

/**   \brief  value based type definition for CanTrcv_30_Tja1040_WakeupByBusUsed */
typedef boolean CanTrcv_30_Tja1040_WakeupByBusUsedType;

/**   \brief  value based type definition for CanTrcv_30_Tja1040_WakeupSource */
typedef uint8 CanTrcv_30_Tja1040_WakeupSourceType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  CanTrcv_30_Tja1040PCStructTypes  CanTrcv_30_Tja1040 Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in CanTrcv_30_Tja1040_DioConfiguration */
typedef uint8_least Dio_LevelType;
typedef uint8_least Dio_ChannelType;
typedef struct sCanTrcv_30_Tja1040_DioConfigurationType
{
  Dio_ChannelType PinRXDOfDioConfiguration;
  Dio_ChannelType PinSTBOfDioConfiguration;
} CanTrcv_30_Tja1040_DioConfigurationType;

/** 
  \}
*/ 

/** 
  \defgroup  CanTrcv_30_Tja1040PCRootPointerTypes  CanTrcv_30_Tja1040 Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to CanTrcv_30_Tja1040_ChannelUsed */
typedef P2CONST(CanTrcv_30_Tja1040_ChannelUsedType, TYPEDEF, CANTRCV_30_TJA1040_CONST) CanTrcv_30_Tja1040_ChannelUsedPtrType;

/**   \brief  type used to point to CanTrcv_30_Tja1040_DioConfiguration */
typedef P2CONST(CanTrcv_30_Tja1040_DioConfigurationType, TYPEDEF, CANTRCV_30_TJA1040_CONST) CanTrcv_30_Tja1040_DioConfigurationPtrType;

/**   \brief  type used to point to CanTrcv_30_Tja1040_WakeupByBusUsed */
typedef P2CONST(CanTrcv_30_Tja1040_WakeupByBusUsedType, TYPEDEF, CANTRCV_30_TJA1040_CONST) CanTrcv_30_Tja1040_WakeupByBusUsedPtrType;

/**   \brief  type used to point to CanTrcv_30_Tja1040_WakeupSource */
typedef P2CONST(CanTrcv_30_Tja1040_WakeupSourceType, TYPEDEF, CANTRCV_30_TJA1040_CONST) CanTrcv_30_Tja1040_WakeupSourcePtrType;

/** 
  \}
*/ 

/** 
  \defgroup  CanTrcv_30_Tja1040PCRootValueTypes  CanTrcv_30_Tja1040 Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in CanTrcv_30_Tja1040_PCConfig */
typedef struct sCanTrcv_30_Tja1040_PCConfigType
{
  uint8 CanTrcv_30_Tja1040_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} CanTrcv_30_Tja1040_PCConfigType;

typedef CanTrcv_30_Tja1040_PCConfigType CanTrcv_30_Tja1040_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CanTrcv_30_Tja1040_ChannelUsed
**********************************************************************************************************************/
#define CANTRCV_30_TJA1040_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(CanTrcv_30_Tja1040_ChannelUsedType, CANTRCV_30_TJA1040_CONST) CanTrcv_30_Tja1040_ChannelUsed[1];
#define CANTRCV_30_TJA1040_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTrcv_30_Tja1040_DioConfiguration
**********************************************************************************************************************/
/** 
  \var    CanTrcv_30_Tja1040_DioConfiguration
  \details
  Element    Description
  PinRXD 
  PinSTB 
*/ 
#define CANTRCV_30_TJA1040_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(CanTrcv_30_Tja1040_DioConfigurationType, CANTRCV_30_TJA1040_CONST) CanTrcv_30_Tja1040_DioConfiguration[1];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define CANTRCV_30_TJA1040_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTrcv_30_Tja1040_WakeupByBusUsed
**********************************************************************************************************************/
#define CANTRCV_30_TJA1040_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(CanTrcv_30_Tja1040_WakeupByBusUsedType, CANTRCV_30_TJA1040_CONST) CanTrcv_30_Tja1040_WakeupByBusUsed[1];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define CANTRCV_30_TJA1040_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  CanTrcv_30_Tja1040_WakeupSource
**********************************************************************************************************************/
#define CANTRCV_30_TJA1040_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(CanTrcv_30_Tja1040_WakeupSourceType, CANTRCV_30_TJA1040_CONST) CanTrcv_30_Tja1040_WakeupSource[1];
#define CANTRCV_30_TJA1040_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/





#endif /* CANTRCV_30_TJA1040_CFG_H */

