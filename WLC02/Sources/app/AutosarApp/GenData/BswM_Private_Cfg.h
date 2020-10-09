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
 *            Module: BswM
 *           Program: VAG AR4 (MSR_Vag_SLP5)
 *          Customer: SAIC Volkswagen Automotive Co., Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: R7F7016393AFP-C
 *    License Scope : The usage is restricted to CBD1900162_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: BswM_Private_Cfg.h
 *   Generation Time: 2020-09-02 09:28:37
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


#if !defined(BSWM_PRIVATE_CFG_H)
#define BSWM_PRIVATE_CFG_H


/* -----------------------------------------------------------------------------
    &&&~ INCLUDE
 ----------------------------------------------------------------------------- */
#include "BswM_Cfg.h"
#include "Com.h" 
#include "Rte_BswM.h" 
#include "Can.h" 
#include "CanIf.h" 
#include "PduR.h" 
#include "CanSM_EcuM.h" 
#include "CanNm.h" 
#include "Nm.h" 
#include "CanTp.h" 
#include "ComM.h" 
#include "Dcm.h" 
#include "Dem.h" 
#include "Rte_Main.h" 

#include "SchM_BswM.h" 
#include "EcuM.h" 
#include "Fls.h" 
#include "Fee_30_SmallSector.h" 
#include "NvM.h" 



/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/


# define BSWM_FUNCTION_BASED STD_ON

#if (defined (BSWM_ACTIONLISTSTRUEIDXOFRULES))
# if ((BSWM_ACTIONLISTSTRUEIDXOFRULES == STD_ON) && defined (BSWM_NO_ACTIONLISTSTRUEIDXOFRULES))
#  define BSWM_NO_ACTIONLIST(partition) BSWM_NO_ACTIONLISTSTRUEIDXOFRULES
# endif
#endif
#if (defined(BSWM_NO_ACTIONLIST))
#else
# if(defined(BSWM_ACTIONLISTSFALSEIDXOFRULES))
#  if ((BSWM_ACTIONLISTSFALSEIDXOFRULES == STD_ON) && defined (BSWM_NO_ACTIONLISTSFALSEIDXOFRULES))
#   define BSWM_NO_ACTIONLIST(partition) BSWM_NO_ACTIONLISTSFALSEIDXOFRULES
#  endif
# endif
#endif
#if (defined(BSWM_NO_ACTIONLIST))
#else
# if(defined(BSWM_SIZEOFACTIONLISTS))
#  if (BSWM_SIZEOFACTIONLISTS == STD_ON)
#   define BSWM_NO_ACTIONLIST(partition) BswM_GetSizeOfActionLists(partition) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif
# endif
#endif
#if (defined(BSWM_NO_ACTIONLIST))
#else
# define BSWM_NO_ACTIONLIST(partition) 255
#endif

#define BSWM_GROUPCONTROL_IDLE   (uint8)0x00u
#define BSWM_GROUPCONTROL_NORMAL (uint8)0x01u
#define BSWM_GROUPCONTROL_REINIT (uint8)0x02u
#define BSWM_GROUPCONTROL_DM     (uint8)0x04u

#if BSWM_NVMJOBSTATE == STD_ON
#define NVM_SERVICE_ID_READALL   (uint8)0x0Cu
#define NVM_SERVICE_ID_WRITEALL  (uint8)0x0Du
#endif



#define BSWM_ID_RULE_CC_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_RX               0u 
#define BSWM_ID_RULE_CC_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_RX_DM            1u 
#define BSWM_ID_RULE_ESH_RunToPostRun                                       2u 
#define BSWM_ID_RULE_ESH_RunToPostRunNested                                 3u 
#define BSWM_ID_RULE_ESH_WaitToShutdown                                     4u 
#define BSWM_ID_RULE_ESH_WakeupToPrep                                       5u 
#define BSWM_ID_RULE_ESH_WaitToWakeup                                       6u 
#define BSWM_ID_RULE_ESH_WakeupToRun                                        7u 
#define BSWM_ID_RULE_ESH_DemInit                                            8u 
#define BSWM_ID_RULE_ESH_InitToWakeup                                       9u 
#define BSWM_ID_RULE_ESH_PostRunToPrepNested                                10u 
#define BSWM_ID_RULE_ESH_PostRunNested                                      11u 
#define BSWM_ID_RULE_ESH_PostRun                                            12u 
#define BSWM_ID_RULE_ESH_PrepToWait                                         13u 
#define BSWM_ID_RULE_CC_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_NO_COM           14u 
#define BSWM_ID_RULE_CC_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_TX_ENABLE        15u 
#define BSWM_ID_RULE_CC_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_BUSOFF_SILENT    16u 
#define BSWM_ID_RULE_CC_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_TX_DISABLE       17u 
#define BSWM_ID_RULE_CC_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_TX_ENABLE_BUSOFF 18u 

#define BSWM_ID_AL_INIT_AL_Initialize                                       0u 
#define BSWM_ID_AL_CC_AL_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_RX_Disable      1u 
#define BSWM_ID_AL_CC_AL_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_Disable_DM      2u 
#define BSWM_ID_AL_CC_AL_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_Enable_DM       3u 
#define BSWM_ID_AL_CC_AL_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_TX_Disable      4u 
#define BSWM_ID_AL_CC_AL_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_TX_EnableNoinit 5u 
#define BSWM_ID_AL_ESH_AL_ExitRun                                           6u 
#define BSWM_ID_AL_ESH_AL_RunToPostRun                                      7u 
#define BSWM_ID_AL_ESH_AL_WaitForNvMToShutdown                              8u 
#define BSWM_ID_AL_ESH_AL_WakeupToPrep                                      9u 
#define BSWM_ID_AL_ESH_AL_WaitForNvMWakeup                                  10u 
#define BSWM_ID_AL_ESH_AL_WakeupToRun                                       11u 
#define BSWM_ID_AL_ESH_AL_DemInit                                           12u 
#define BSWM_ID_AL_ESH_AL_InitToWakeup                                      13u 
#define BSWM_ID_AL_ESH_AL_PostRunToPrepShutdown                             14u 
#define BSWM_ID_AL_ESH_AL_ESH_PostRunToPrepCheck                            15u 
#define BSWM_ID_AL_ESH_AL_PostRunToRun                                      16u 
#define BSWM_ID_AL_ESH_AL_ExitPostRun                                       17u 
#define BSWM_ID_AL_ESH_AL_PrepShutdownToWaitForNvM                          18u 
#define BSWM_ID_AL_CC_AL_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_RX_EnableReinit 19u 
#define BSWM_ID_AL_CC_AL_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_NO_COM          20u 
#define BSWM_ID_AL_CC_AL_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_TX_EnableReinit 21u 
#define BSWM_ID_AL_CC_AL_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f_BUSOFF_SILENT   22u 


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
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
  \defgroup  BswMPCGetConstantDuplicatedRootDataMacros  BswM Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define BswM_GetPartitionIdentifiersOfPCConfig()                                                    BswM_PartitionIdentifiers  /**< the pointer to BswM_PartitionIdentifiers */
#define BswM_GetSizeOfPartitionIdentifiersOfPCConfig()                                              1u  /**< the number of accomplishable value elements in BswM_PartitionIdentifiers */
#define BswM_GetActionListQueueOfPCPartitionConfig(partitionIndex)                                  BswM_ActionListQueue.raw  /**< the pointer to BswM_ActionListQueue */
#define BswM_GetActionListsOfPCPartitionConfig(partitionIndex)                                      BswM_ActionLists  /**< the pointer to BswM_ActionLists */
#define BswM_GetCanSMChannelMappingOfPCPartitionConfig(partitionIndex)                              BswM_CanSMChannelMapping  /**< the pointer to BswM_CanSMChannelMapping */
#define BswM_GetCanSMChannelStateOfPCPartitionConfig(partitionIndex)                                BswM_CanSMChannelState  /**< the pointer to BswM_CanSMChannelState */
#define BswM_GetComMChannelMappingOfPCPartitionConfig(partitionIndex)                               BswM_ComMChannelMapping  /**< the pointer to BswM_ComMChannelMapping */
#define BswM_GetComMChannelStateOfPCPartitionConfig(partitionIndex)                                 BswM_ComMChannelState  /**< the pointer to BswM_ComMChannelState */
#define BswM_GetDcmComMappingOfPCPartitionConfig(partitionIndex)                                    BswM_DcmComMapping  /**< the pointer to BswM_DcmComMapping */
#define BswM_GetDcmComStateOfPCPartitionConfig(partitionIndex)                                      BswM_DcmComState  /**< the pointer to BswM_DcmComState */
#define BswM_GetDeferredRulesOfPCPartitionConfig(partitionIndex)                                    BswM_DeferredRules  /**< the pointer to BswM_DeferredRules */
#define BswM_GetForcedActionListPriorityOfPCPartitionConfig(partitionIndex)                         (&(BswM_ForcedActionListPriority))  /**< the pointer to BswM_ForcedActionListPriority */
#define BswM_GetGenericMappingOfPCPartitionConfig(partitionIndex)                                   BswM_GenericMapping  /**< the pointer to BswM_GenericMapping */
#define BswM_GetGenericStateOfPCPartitionConfig(partitionIndex)                                     BswM_GenericState  /**< the pointer to BswM_GenericState */
#define BswM_GetImmediateUserOfPCPartitionConfig(partitionIndex)                                    BswM_ImmediateUser  /**< the pointer to BswM_ImmediateUser */
#define BswM_GetInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)                              BswM_InitGenVarAndInitAL  /**< the pointer to BswM_InitGenVarAndInitAL */
#define BswM_GetInitializedOfPCPartitionConfig(partitionIndex)                                      (&(BswM_Initialized))  /**< the pointer to BswM_Initialized */
#define BswM_GetModeNotificationFctOfPCPartitionConfig(partitionIndex)                              BswM_ModeNotificationFct  /**< the pointer to BswM_ModeNotificationFct */
#define BswM_GetModeRequestQueueOfPCPartitionConfig(partitionIndex)                                 BswM_ModeRequestQueue  /**< the pointer to BswM_ModeRequestQueue */
#define BswM_GetQueueSemaphoreOfPCPartitionConfig(partitionIndex)                                   (&(BswM_QueueSemaphore))  /**< the pointer to BswM_QueueSemaphore */
#define BswM_GetQueueWrittenOfPCPartitionConfig(partitionIndex)                                     (&(BswM_QueueWritten))  /**< the pointer to BswM_QueueWritten */
#define BswM_GetRuleStatesOfPCPartitionConfig(partitionIndex)                                       BswM_RuleStates  /**< the pointer to BswM_RuleStates */
#define BswM_GetRulesIndOfPCPartitionConfig(partitionIndex)                                         BswM_RulesInd  /**< the pointer to BswM_RulesInd */
#define BswM_GetRulesOfPCPartitionConfig(partitionIndex)                                            BswM_Rules  /**< the pointer to BswM_Rules */
#define BswM_GetSizeOfActionListsOfPCPartitionConfig(partitionIndex)                                23u  /**< the number of accomplishable value elements in BswM_ActionLists */
#define BswM_GetSizeOfCanSMChannelMappingOfPCPartitionConfig(partitionIndex)                        1u  /**< the number of accomplishable value elements in BswM_CanSMChannelMapping */
#define BswM_GetSizeOfCanSMChannelStateOfPCPartitionConfig(partitionIndex)                          1u  /**< the number of accomplishable value elements in BswM_CanSMChannelState */
#define BswM_GetSizeOfComMChannelMappingOfPCPartitionConfig(partitionIndex)                         1u  /**< the number of accomplishable value elements in BswM_ComMChannelMapping */
#define BswM_GetSizeOfComMChannelStateOfPCPartitionConfig(partitionIndex)                           1u  /**< the number of accomplishable value elements in BswM_ComMChannelState */
#define BswM_GetSizeOfDcmComMappingOfPCPartitionConfig(partitionIndex)                              1u  /**< the number of accomplishable value elements in BswM_DcmComMapping */
#define BswM_GetSizeOfDcmComStateOfPCPartitionConfig(partitionIndex)                                1u  /**< the number of accomplishable value elements in BswM_DcmComState */
#define BswM_GetSizeOfDeferredRulesOfPCPartitionConfig(partitionIndex)                              7u  /**< the number of accomplishable value elements in BswM_DeferredRules */
#define BswM_GetSizeOfGenericMappingOfPCPartitionConfig(partitionIndex)                             4u  /**< the number of accomplishable value elements in BswM_GenericMapping */
#define BswM_GetSizeOfGenericStateOfPCPartitionConfig(partitionIndex)                               4u  /**< the number of accomplishable value elements in BswM_GenericState */
#define BswM_GetSizeOfImmediateUserOfPCPartitionConfig(partitionIndex)                              5u  /**< the number of accomplishable value elements in BswM_ImmediateUser */
#define BswM_GetSizeOfInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)                        1u  /**< the number of accomplishable value elements in BswM_InitGenVarAndInitAL */
#define BswM_GetSizeOfModeNotificationFctOfPCPartitionConfig(partitionIndex)                        1u  /**< the number of accomplishable value elements in BswM_ModeNotificationFct */
#define BswM_GetSizeOfRulesIndOfPCPartitionConfig(partitionIndex)                                   22u  /**< the number of accomplishable value elements in BswM_RulesInd */
#define BswM_GetSizeOfRulesOfPCPartitionConfig(partitionIndex)                                      19u  /**< the number of accomplishable value elements in BswM_Rules */
#define BswM_GetSizeOfSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)                    1u  /**< the number of accomplishable value elements in BswM_SwcModeRequestUpdateFct */
#define BswM_GetSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)                          BswM_SwcModeRequestUpdateFct  /**< the pointer to BswM_SwcModeRequestUpdateFct */
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCGetDuplicatedRootDataMacros  BswM Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define BswM_GetSizeOfActionListQueueOfPCPartitionConfig(partitionIndex)                            BswM_GetSizeOfActionListsOfPCPartitionConfig(partitionIndex)  /**< the number of accomplishable value elements in BswM_ActionListQueue */
#define BswM_GetSizeOfModeRequestQueueOfPCPartitionConfig(partitionIndex)                           BswM_GetSizeOfImmediateUserOfPCPartitionConfig(partitionIndex)  /**< the number of accomplishable value elements in BswM_ModeRequestQueue */
#define BswM_GetSizeOfRuleStatesOfPCPartitionConfig(partitionIndex)                                 BswM_GetSizeOfRulesOfPCPartitionConfig(partitionIndex)  /**< the number of accomplishable value elements in BswM_RuleStates */
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCGetDataMacros  BswM Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define BswM_GetActionListQueue(Index, partitionIndex)                                              (BswM_GetActionListQueueOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetFctPtrOfActionLists(Index, partitionIndex)                                          (BswM_GetActionListsOfPCPartitionConfig(partitionIndex)[(Index)].FctPtrOfActionLists)
#define BswM_GetCanSMChannelState(Index, partitionIndex)                                            (BswM_GetCanSMChannelStateOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetComMChannelState(Index, partitionIndex)                                             (BswM_GetComMChannelStateOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetDcmComState(Index, partitionIndex)                                                  (BswM_GetDcmComStateOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetRulesIdxOfDeferredRules(Index, partitionIndex)                                      (BswM_GetDeferredRulesOfPCPartitionConfig(partitionIndex)[(Index)].RulesIdxOfDeferredRules)
#define BswM_GetForcedActionListPriority(partitionIndex)                                            ((*(BswM_GetForcedActionListPriorityOfPCPartitionConfig(partitionIndex))))
#define BswM_GetExternalIdOfGenericMapping(Index, partitionIndex)                                   (BswM_GetGenericMappingOfPCPartitionConfig(partitionIndex)[(Index)].ExternalIdOfGenericMapping)
#define BswM_GetImmediateUserEndIdxOfGenericMapping(Index, partitionIndex)                          (BswM_GetGenericMappingOfPCPartitionConfig(partitionIndex)[(Index)].ImmediateUserEndIdxOfGenericMapping)
#define BswM_GetImmediateUserStartIdxOfGenericMapping(Index, partitionIndex)                        (BswM_GetGenericMappingOfPCPartitionConfig(partitionIndex)[(Index)].ImmediateUserStartIdxOfGenericMapping)
#define BswM_GetInitValueOfGenericMapping(Index, partitionIndex)                                    (BswM_GetGenericMappingOfPCPartitionConfig(partitionIndex)[(Index)].InitValueOfGenericMapping)
#define BswM_GetGenericState(Index, partitionIndex)                                                 (BswM_GetGenericStateOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetMaskedBitsOfImmediateUser(Index, partitionIndex)                                    (BswM_GetImmediateUserOfPCPartitionConfig(partitionIndex)[(Index)].MaskedBitsOfImmediateUser)
#define BswM_GetRulesIndEndIdxOfImmediateUser(Index, partitionIndex)                                (BswM_GetImmediateUserOfPCPartitionConfig(partitionIndex)[(Index)].RulesIndEndIdxOfImmediateUser)
#define BswM_GetRulesIndStartIdxOfImmediateUser(Index, partitionIndex)                              (BswM_GetImmediateUserOfPCPartitionConfig(partitionIndex)[(Index)].RulesIndStartIdxOfImmediateUser)
#define BswM_GetInitGenVarAndInitAL(Index, partitionIndex)                                          (BswM_GetInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_IsInitialized(partitionIndex)                                                          (((*(BswM_GetInitializedOfPCPartitionConfig(partitionIndex)))) != FALSE)
#define BswM_GetModeNotificationFct(Index, partitionIndex)                                          (BswM_GetModeNotificationFctOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetModeRequestQueue(Index, partitionIndex)                                             (BswM_GetModeRequestQueueOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetPCPartitionConfigIdxOfPartitionIdentifiers(Index)                                   (BswM_GetPartitionIdentifiersOfPCConfig()[(Index)].PCPartitionConfigIdxOfPartitionIdentifiers)
#define BswM_GetPartitionSNVOfPartitionIdentifiers(Index)                                           (BswM_GetPartitionIdentifiersOfPCConfig()[(Index)].PartitionSNVOfPartitionIdentifiers)
#define BswM_GetQueueSemaphore(partitionIndex)                                                      ((*(BswM_GetQueueSemaphoreOfPCPartitionConfig(partitionIndex))))
#define BswM_IsQueueWritten(partitionIndex)                                                         (((*(BswM_GetQueueWrittenOfPCPartitionConfig(partitionIndex)))) != FALSE)
#define BswM_GetRuleStates(Index, partitionIndex)                                                   (BswM_GetRuleStatesOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetFctPtrOfRules(Index, partitionIndex)                                                (BswM_GetRulesOfPCPartitionConfig(partitionIndex)[(Index)].FctPtrOfRules)
#define BswM_GetIdOfRules(Index, partitionIndex)                                                    (BswM_GetRulesOfPCPartitionConfig(partitionIndex)[(Index)].IdOfRules)
#define BswM_GetInitOfRules(Index, partitionIndex)                                                  (BswM_GetRulesOfPCPartitionConfig(partitionIndex)[(Index)].InitOfRules)
#define BswM_GetRulesInd(Index, partitionIndex)                                                     (BswM_GetRulesIndOfPCPartitionConfig(partitionIndex)[(Index)])
#define BswM_GetSwcModeRequestUpdateFct(Index, partitionIndex)                                      (BswM_GetSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCGetBitDataMacros  BswM Get Bit Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read bitcoded data elements.
  \{
*/ 
#define BswM_IsOnInitOfImmediateUser(Index, partitionIndex)                                         (BSWM_ONINITOFIMMEDIATEUSER_MASK == (BswM_GetMaskedBitsOfImmediateUser(((Index)), (partitionIndex)) & BSWM_ONINITOFIMMEDIATEUSER_MASK))  /**< Arbitrate depending rules on initialization. */
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCGetDeduplicatedDataMacros  BswM Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define BswM_GetExternalIdOfCanSMChannelMapping(Index, partitionIndex)                              ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f  /**< External id of BswMCanSMIndication. */
#define BswM_GetImmediateUserEndIdxOfCanSMChannelMapping(Index, partitionIndex)                     1u  /**< the end index of the 0:n relation pointing to BswM_ImmediateUser */
#define BswM_GetImmediateUserStartIdxOfCanSMChannelMapping(Index, partitionIndex)                   0u  /**< the start index of the 0:n relation pointing to BswM_ImmediateUser */
#define BswM_IsImmediateUserUsedOfCanSMChannelMapping(Index, partitionIndex)                        (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to BswM_ImmediateUser */
#define BswM_GetInitValueOfCanSMChannelMapping(Index, partitionIndex)                               CANSM_BSWM_NO_COMMUNICATION  /**< Initialization value of port. */
#define BswM_GetExternalIdOfComMChannelMapping(Index, partitionIndex)                               ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f  /**< External id of BswMComMIndication. */
#define BswM_GetInitValueOfComMChannelMapping(Index, partitionIndex)                                COMM_NO_COMMUNICATION  /**< Initialization value of port. */
#define BswM_GetExternalIdOfDcmComMapping(Index, partitionIndex)                                    ComMConf_ComMChannel_CN_NIO_ES6_RF_CAN_SR_V3_0_d2612a1f  /**< External id of BswMDcmComModeRequest. */
#define BswM_GetImmediateUserEndIdxOfDcmComMapping(Index, partitionIndex)                           2u  /**< the end index of the 0:n relation pointing to BswM_ImmediateUser */
#define BswM_GetImmediateUserStartIdxOfDcmComMapping(Index, partitionIndex)                         1u  /**< the start index of the 0:n relation pointing to BswM_ImmediateUser */
#define BswM_IsImmediateUserUsedOfDcmComMapping(Index, partitionIndex)                              (((TRUE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to BswM_ImmediateUser */
#define BswM_GetInitValueOfDcmComMapping(Index, partitionIndex)                                     DCM_ENABLE_RX_TX_NORM  /**< Initialization value of port. */
#define BswM_IsImmediateUserUsedOfGenericMapping(Index, partitionIndex)                             (((boolean)(BswM_GetImmediateUserStartIdxOfGenericMapping(((Index)), (partitionIndex)) != BSWM_NO_IMMEDIATEUSERSTARTIDXOFGENERICMAPPING)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to BswM_ImmediateUser */
#define BswM_IsRulesIndUsedOfImmediateUser(Index, partitionIndex)                                   (((boolean)(BswM_GetRulesIndStartIdxOfImmediateUser(((Index)), (partitionIndex)) != BSWM_NO_RULESINDSTARTIDXOFIMMEDIATEUSER)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to BswM_RulesInd */
#define BswM_GetSizeOfActionListQueue(partitionIndex)                                               BswM_GetSizeOfActionListQueueOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfActionLists(partitionIndex)                                                   BswM_GetSizeOfActionListsOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfCanSMChannelMapping(partitionIndex)                                           BswM_GetSizeOfCanSMChannelMappingOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfCanSMChannelState(partitionIndex)                                             BswM_GetSizeOfCanSMChannelStateOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfComMChannelMapping(partitionIndex)                                            BswM_GetSizeOfComMChannelMappingOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfComMChannelState(partitionIndex)                                              BswM_GetSizeOfComMChannelStateOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfDcmComMapping(partitionIndex)                                                 BswM_GetSizeOfDcmComMappingOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfDcmComState(partitionIndex)                                                   BswM_GetSizeOfDcmComStateOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfDeferredRules(partitionIndex)                                                 BswM_GetSizeOfDeferredRulesOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfGenericMapping(partitionIndex)                                                BswM_GetSizeOfGenericMappingOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfGenericState(partitionIndex)                                                  BswM_GetSizeOfGenericStateOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfImmediateUser(partitionIndex)                                                 BswM_GetSizeOfImmediateUserOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfInitGenVarAndInitAL(partitionIndex)                                           BswM_GetSizeOfInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfModeNotificationFct(partitionIndex)                                           BswM_GetSizeOfModeNotificationFctOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfModeRequestQueue(partitionIndex)                                              BswM_GetSizeOfModeRequestQueueOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfPartitionIdentifiers()                                                        BswM_GetSizeOfPartitionIdentifiersOfPCConfig()
#define BswM_GetSizeOfRuleStates(partitionIndex)                                                    BswM_GetSizeOfRuleStatesOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfRules(partitionIndex)                                                         BswM_GetSizeOfRulesOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfRulesInd(partitionIndex)                                                      BswM_GetSizeOfRulesIndOfPCPartitionConfig(partitionIndex)
#define BswM_GetSizeOfSwcModeRequestUpdateFct(partitionIndex)                                       BswM_GetSizeOfSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCSetDataMacros  BswM Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define BswM_SetActionListQueue(Index, Value, partitionIndex)                                       BswM_GetActionListQueueOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define BswM_SetCanSMChannelState(Index, Value, partitionIndex)                                     BswM_GetCanSMChannelStateOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define BswM_SetComMChannelState(Index, Value, partitionIndex)                                      BswM_GetComMChannelStateOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define BswM_SetDcmComState(Index, Value, partitionIndex)                                           BswM_GetDcmComStateOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define BswM_SetForcedActionListPriority(Value, partitionIndex)                                     (*(BswM_GetForcedActionListPriorityOfPCPartitionConfig(partitionIndex))) = (Value)
#define BswM_SetGenericState(Index, Value, partitionIndex)                                          BswM_GetGenericStateOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define BswM_SetInitialized(Value, partitionIndex)                                                  (*(BswM_GetInitializedOfPCPartitionConfig(partitionIndex))) = (Value)
#define BswM_SetModeRequestQueue(Index, Value, partitionIndex)                                      BswM_GetModeRequestQueueOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define BswM_SetQueueSemaphore(Value, partitionIndex)                                               (*(BswM_GetQueueSemaphoreOfPCPartitionConfig(partitionIndex))) = (Value)
#define BswM_SetQueueWritten(Value, partitionIndex)                                                 (*(BswM_GetQueueWrittenOfPCPartitionConfig(partitionIndex))) = (Value)
#define BswM_SetRuleStates(Index, Value, partitionIndex)                                            BswM_GetRuleStatesOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCHasMacros  BswM Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define BswM_HasActionListQueue(partitionIndex)                                                     (TRUE != FALSE)
#define BswM_HasActionLists(partitionIndex)                                                         (TRUE != FALSE)
#define BswM_HasFctPtrOfActionLists(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasCanSMChannelMapping(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasExternalIdOfCanSMChannelMapping(partitionIndex)                                     (TRUE != FALSE)
#define BswM_HasImmediateUserEndIdxOfCanSMChannelMapping(partitionIndex)                            (TRUE != FALSE)
#define BswM_HasImmediateUserStartIdxOfCanSMChannelMapping(partitionIndex)                          (TRUE != FALSE)
#define BswM_HasImmediateUserUsedOfCanSMChannelMapping(partitionIndex)                              (TRUE != FALSE)
#define BswM_HasInitValueOfCanSMChannelMapping(partitionIndex)                                      (TRUE != FALSE)
#define BswM_HasCanSMChannelState(partitionIndex)                                                   (TRUE != FALSE)
#define BswM_HasComMChannelMapping(partitionIndex)                                                  (TRUE != FALSE)
#define BswM_HasExternalIdOfComMChannelMapping(partitionIndex)                                      (TRUE != FALSE)
#define BswM_HasInitValueOfComMChannelMapping(partitionIndex)                                       (TRUE != FALSE)
#define BswM_HasComMChannelState(partitionIndex)                                                    (TRUE != FALSE)
#define BswM_HasDcmComMapping(partitionIndex)                                                       (TRUE != FALSE)
#define BswM_HasExternalIdOfDcmComMapping(partitionIndex)                                           (TRUE != FALSE)
#define BswM_HasImmediateUserEndIdxOfDcmComMapping(partitionIndex)                                  (TRUE != FALSE)
#define BswM_HasImmediateUserStartIdxOfDcmComMapping(partitionIndex)                                (TRUE != FALSE)
#define BswM_HasImmediateUserUsedOfDcmComMapping(partitionIndex)                                    (TRUE != FALSE)
#define BswM_HasInitValueOfDcmComMapping(partitionIndex)                                            (TRUE != FALSE)
#define BswM_HasDcmComState(partitionIndex)                                                         (TRUE != FALSE)
#define BswM_HasDeferredRules(partitionIndex)                                                       (TRUE != FALSE)
#define BswM_HasRulesIdxOfDeferredRules(partitionIndex)                                             (TRUE != FALSE)
#define BswM_HasForcedActionListPriority(partitionIndex)                                            (TRUE != FALSE)
#define BswM_HasGenericMapping(partitionIndex)                                                      (TRUE != FALSE)
#define BswM_HasExternalIdOfGenericMapping(partitionIndex)                                          (TRUE != FALSE)
#define BswM_HasImmediateUserEndIdxOfGenericMapping(partitionIndex)                                 (TRUE != FALSE)
#define BswM_HasImmediateUserStartIdxOfGenericMapping(partitionIndex)                               (TRUE != FALSE)
#define BswM_HasImmediateUserUsedOfGenericMapping(partitionIndex)                                   (TRUE != FALSE)
#define BswM_HasInitValueOfGenericMapping(partitionIndex)                                           (TRUE != FALSE)
#define BswM_HasGenericState(partitionIndex)                                                        (TRUE != FALSE)
#define BswM_HasImmediateUser(partitionIndex)                                                       (TRUE != FALSE)
#define BswM_HasMaskedBitsOfImmediateUser(partitionIndex)                                           (TRUE != FALSE)
#define BswM_HasOnInitOfImmediateUser(partitionIndex)                                               (TRUE != FALSE)
#define BswM_HasRulesIndEndIdxOfImmediateUser(partitionIndex)                                       (TRUE != FALSE)
#define BswM_HasRulesIndStartIdxOfImmediateUser(partitionIndex)                                     (TRUE != FALSE)
#define BswM_HasRulesIndUsedOfImmediateUser(partitionIndex)                                         (TRUE != FALSE)
#define BswM_HasInitGenVarAndInitAL(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasInitialized(partitionIndex)                                                         (TRUE != FALSE)
#define BswM_HasModeNotificationFct(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasModeRequestQueue(partitionIndex)                                                    (TRUE != FALSE)
#define BswM_HasPartitionIdentifiers()                                                              (TRUE != FALSE)
#define BswM_HasPCPartitionConfigIdxOfPartitionIdentifiers()                                        (TRUE != FALSE)
#define BswM_HasPartitionSNVOfPartitionIdentifiers()                                                (TRUE != FALSE)
#define BswM_HasQueueSemaphore(partitionIndex)                                                      (TRUE != FALSE)
#define BswM_HasQueueWritten(partitionIndex)                                                        (TRUE != FALSE)
#define BswM_HasRuleStates(partitionIndex)                                                          (TRUE != FALSE)
#define BswM_HasRules(partitionIndex)                                                               (TRUE != FALSE)
#define BswM_HasFctPtrOfRules(partitionIndex)                                                       (TRUE != FALSE)
#define BswM_HasIdOfRules(partitionIndex)                                                           (TRUE != FALSE)
#define BswM_HasInitOfRules(partitionIndex)                                                         (TRUE != FALSE)
#define BswM_HasRulesInd(partitionIndex)                                                            (TRUE != FALSE)
#define BswM_HasSizeOfActionListQueue(partitionIndex)                                               (TRUE != FALSE)
#define BswM_HasSizeOfActionLists(partitionIndex)                                                   (TRUE != FALSE)
#define BswM_HasSizeOfCanSMChannelMapping(partitionIndex)                                           (TRUE != FALSE)
#define BswM_HasSizeOfCanSMChannelState(partitionIndex)                                             (TRUE != FALSE)
#define BswM_HasSizeOfComMChannelMapping(partitionIndex)                                            (TRUE != FALSE)
#define BswM_HasSizeOfComMChannelState(partitionIndex)                                              (TRUE != FALSE)
#define BswM_HasSizeOfDcmComMapping(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasSizeOfDcmComState(partitionIndex)                                                   (TRUE != FALSE)
#define BswM_HasSizeOfDeferredRules(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasSizeOfGenericMapping(partitionIndex)                                                (TRUE != FALSE)
#define BswM_HasSizeOfGenericState(partitionIndex)                                                  (TRUE != FALSE)
#define BswM_HasSizeOfImmediateUser(partitionIndex)                                                 (TRUE != FALSE)
#define BswM_HasSizeOfInitGenVarAndInitAL(partitionIndex)                                           (TRUE != FALSE)
#define BswM_HasSizeOfModeNotificationFct(partitionIndex)                                           (TRUE != FALSE)
#define BswM_HasSizeOfModeRequestQueue(partitionIndex)                                              (TRUE != FALSE)
#define BswM_HasSizeOfPartitionIdentifiers()                                                        (TRUE != FALSE)
#define BswM_HasSizeOfRuleStates(partitionIndex)                                                    (TRUE != FALSE)
#define BswM_HasSizeOfRules(partitionIndex)                                                         (TRUE != FALSE)
#define BswM_HasSizeOfRulesInd(partitionIndex)                                                      (TRUE != FALSE)
#define BswM_HasSizeOfSwcModeRequestUpdateFct(partitionIndex)                                       (TRUE != FALSE)
#define BswM_HasSwcModeRequestUpdateFct(partitionIndex)                                             (TRUE != FALSE)
#define BswM_HasPCConfig()                                                                          (TRUE != FALSE)
#define BswM_HasPCPartitionConfigOfPCConfig()                                                       (TRUE != FALSE)
#define BswM_HasPartitionIdentifiersOfPCConfig()                                                    (TRUE != FALSE)
#define BswM_HasSizeOfPartitionIdentifiersOfPCConfig()                                              (TRUE != FALSE)
#define BswM_HasPCPartitionConfig()                                                                 (TRUE != FALSE)
#define BswM_HasActionListQueueOfPCPartitionConfig(partitionIndex)                                  (TRUE != FALSE)
#define BswM_HasActionListsOfPCPartitionConfig(partitionIndex)                                      (TRUE != FALSE)
#define BswM_HasCanSMChannelMappingOfPCPartitionConfig(partitionIndex)                              (TRUE != FALSE)
#define BswM_HasCanSMChannelStateOfPCPartitionConfig(partitionIndex)                                (TRUE != FALSE)
#define BswM_HasComMChannelMappingOfPCPartitionConfig(partitionIndex)                               (TRUE != FALSE)
#define BswM_HasComMChannelStateOfPCPartitionConfig(partitionIndex)                                 (TRUE != FALSE)
#define BswM_HasDcmComMappingOfPCPartitionConfig(partitionIndex)                                    (TRUE != FALSE)
#define BswM_HasDcmComStateOfPCPartitionConfig(partitionIndex)                                      (TRUE != FALSE)
#define BswM_HasDeferredRulesOfPCPartitionConfig(partitionIndex)                                    (TRUE != FALSE)
#define BswM_HasForcedActionListPriorityOfPCPartitionConfig(partitionIndex)                         (TRUE != FALSE)
#define BswM_HasGenericMappingOfPCPartitionConfig(partitionIndex)                                   (TRUE != FALSE)
#define BswM_HasGenericStateOfPCPartitionConfig(partitionIndex)                                     (TRUE != FALSE)
#define BswM_HasImmediateUserOfPCPartitionConfig(partitionIndex)                                    (TRUE != FALSE)
#define BswM_HasInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)                              (TRUE != FALSE)
#define BswM_HasInitializedOfPCPartitionConfig(partitionIndex)                                      (TRUE != FALSE)
#define BswM_HasModeNotificationFctOfPCPartitionConfig(partitionIndex)                              (TRUE != FALSE)
#define BswM_HasModeRequestQueueOfPCPartitionConfig(partitionIndex)                                 (TRUE != FALSE)
#define BswM_HasQueueSemaphoreOfPCPartitionConfig(partitionIndex)                                   (TRUE != FALSE)
#define BswM_HasQueueWrittenOfPCPartitionConfig(partitionIndex)                                     (TRUE != FALSE)
#define BswM_HasRuleStatesOfPCPartitionConfig(partitionIndex)                                       (TRUE != FALSE)
#define BswM_HasRulesIndOfPCPartitionConfig(partitionIndex)                                         (TRUE != FALSE)
#define BswM_HasRulesOfPCPartitionConfig(partitionIndex)                                            (TRUE != FALSE)
#define BswM_HasSizeOfActionListQueueOfPCPartitionConfig(partitionIndex)                            (TRUE != FALSE)
#define BswM_HasSizeOfActionListsOfPCPartitionConfig(partitionIndex)                                (TRUE != FALSE)
#define BswM_HasSizeOfCanSMChannelMappingOfPCPartitionConfig(partitionIndex)                        (TRUE != FALSE)
#define BswM_HasSizeOfCanSMChannelStateOfPCPartitionConfig(partitionIndex)                          (TRUE != FALSE)
#define BswM_HasSizeOfComMChannelMappingOfPCPartitionConfig(partitionIndex)                         (TRUE != FALSE)
#define BswM_HasSizeOfComMChannelStateOfPCPartitionConfig(partitionIndex)                           (TRUE != FALSE)
#define BswM_HasSizeOfDcmComMappingOfPCPartitionConfig(partitionIndex)                              (TRUE != FALSE)
#define BswM_HasSizeOfDcmComStateOfPCPartitionConfig(partitionIndex)                                (TRUE != FALSE)
#define BswM_HasSizeOfDeferredRulesOfPCPartitionConfig(partitionIndex)                              (TRUE != FALSE)
#define BswM_HasSizeOfGenericMappingOfPCPartitionConfig(partitionIndex)                             (TRUE != FALSE)
#define BswM_HasSizeOfGenericStateOfPCPartitionConfig(partitionIndex)                               (TRUE != FALSE)
#define BswM_HasSizeOfImmediateUserOfPCPartitionConfig(partitionIndex)                              (TRUE != FALSE)
#define BswM_HasSizeOfInitGenVarAndInitALOfPCPartitionConfig(partitionIndex)                        (TRUE != FALSE)
#define BswM_HasSizeOfModeNotificationFctOfPCPartitionConfig(partitionIndex)                        (TRUE != FALSE)
#define BswM_HasSizeOfModeRequestQueueOfPCPartitionConfig(partitionIndex)                           (TRUE != FALSE)
#define BswM_HasSizeOfRuleStatesOfPCPartitionConfig(partitionIndex)                                 (TRUE != FALSE)
#define BswM_HasSizeOfRulesIndOfPCPartitionConfig(partitionIndex)                                   (TRUE != FALSE)
#define BswM_HasSizeOfRulesOfPCPartitionConfig(partitionIndex)                                      (TRUE != FALSE)
#define BswM_HasSizeOfSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)                    (TRUE != FALSE)
#define BswM_HasSwcModeRequestUpdateFctOfPCPartitionConfig(partitionIndex)                          (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCIncrementDataMacros  BswM Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define BswM_IncActionListQueue(Index, partitionIndex)                                              BswM_GetActionListQueue(((Index)), (partitionIndex))++
#define BswM_IncCanSMChannelState(Index, partitionIndex)                                            BswM_GetCanSMChannelState(((Index)), (partitionIndex))++
#define BswM_IncComMChannelState(Index, partitionIndex)                                             BswM_GetComMChannelState(((Index)), (partitionIndex))++
#define BswM_IncDcmComState(Index, partitionIndex)                                                  BswM_GetDcmComState(((Index)), (partitionIndex))++
#define BswM_IncForcedActionListPriority(partitionIndex)                                            BswM_GetForcedActionListPriority(partitionIndex)++
#define BswM_IncGenericState(Index, partitionIndex)                                                 BswM_GetGenericState(((Index)), (partitionIndex))++
#define BswM_IncModeRequestQueue(Index, partitionIndex)                                             BswM_GetModeRequestQueue(((Index)), (partitionIndex))++
#define BswM_IncQueueSemaphore(partitionIndex)                                                      BswM_GetQueueSemaphore(partitionIndex)++
#define BswM_IncRuleStates(Index, partitionIndex)                                                   BswM_GetRuleStates(((Index)), (partitionIndex))++
/** 
  \}
*/ 

/** 
  \defgroup  BswMPCDecrementDataMacros  BswM Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define BswM_DecActionListQueue(Index, partitionIndex)                                              BswM_GetActionListQueue(((Index)), (partitionIndex))--
#define BswM_DecCanSMChannelState(Index, partitionIndex)                                            BswM_GetCanSMChannelState(((Index)), (partitionIndex))--
#define BswM_DecComMChannelState(Index, partitionIndex)                                             BswM_GetComMChannelState(((Index)), (partitionIndex))--
#define BswM_DecDcmComState(Index, partitionIndex)                                                  BswM_GetDcmComState(((Index)), (partitionIndex))--
#define BswM_DecForcedActionListPriority(partitionIndex)                                            BswM_GetForcedActionListPriority(partitionIndex)--
#define BswM_DecGenericState(Index, partitionIndex)                                                 BswM_GetGenericState(((Index)), (partitionIndex))--
#define BswM_DecModeRequestQueue(Index, partitionIndex)                                             BswM_GetModeRequestQueue(((Index)), (partitionIndex))--
#define BswM_DecQueueSemaphore(partitionIndex)                                                      BswM_GetQueueSemaphore(partitionIndex)--
#define BswM_DecRuleStates(Index, partitionIndex)                                                   BswM_GetRuleStates(((Index)), (partitionIndex))--
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


#define BswM_GetPartitionContext() 0u

/* PRQA S 3453 1 */ /* MD_BswM_3453 */
#define BswM_SetIpduGroup(pduId, bitVal) Com_SetIpduGroup(BswM_ComIPduGroupState, (pduId), (bitVal))
/* PRQA S 3453 1 */ /* MD_BswM_3453 */
#define BswM_SetIpduReinitGroup(pduId, bitVal) Com_SetIpduGroup(BswM_ComIPduGroupReinitState, (pduId), (bitVal))
/* PRQA S 3453 1 */ /* MD_BswM_3453 */
#define BswM_SetIpduDMGroup(pduId, bitVal) Com_SetIpduGroup(BswM_ComRxIPduGroupDMState, (pduId), (bitVal))

/* PRQA S 3453 1 */ /* MD_BswM_3453 */
#define BswM_MarkPduGroupControlInvocation(control) BswM_PduGroupControlInvocation |= (control)
#define BswM_MarkDmControlInvocation() BswM_PduGroupControlInvocation |= BSWM_GROUPCONTROL_DM


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/* PRQA S 3449, 3451 EXTERNDECLARATIONS */ /* MD_BSWM_3449, MD_BSWM_3451 */ 
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  BswM_ActionLists
**********************************************************************************************************************/
/** 
  \var    BswM_ActionLists
  \details
  Element    Description
  FctPtr     Pointer to the array list function.
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(BswM_ActionListsType, BSWM_CONST) BswM_ActionLists[23];
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_DeferredRules
**********************************************************************************************************************/
/** 
  \var    BswM_DeferredRules
  \details
  Element     Description
  RulesIdx    the index of the 1:1 relation pointing to BswM_Rules
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(BswM_DeferredRulesType, BSWM_CONST) BswM_DeferredRules[7];
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_GenericMapping
**********************************************************************************************************************/
/** 
  \var    BswM_GenericMapping
  \brief  Maps the external id of BswMGenericRequest to an internal id and references immediate request ports.
  \details
  Element                  Description
  ExternalId               External id of BswMGenericRequest.
  ImmediateUserEndIdx      the end index of the 0:n relation pointing to BswM_ImmediateUser
  ImmediateUserStartIdx    the start index of the 0:n relation pointing to BswM_ImmediateUser
  InitValue                Initialization value of port.
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(BswM_GenericMappingType, BSWM_CONST) BswM_GenericMapping[4];
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_ImmediateUser
**********************************************************************************************************************/
/** 
  \var    BswM_ImmediateUser
  \brief  Contains all immediate request ports.
  \details
  Element             Description
  MaskedBits          contains bitcoded the boolean data of BswM_OnInitOfImmediateUser, BswM_RulesIndUsedOfImmediateUser
  RulesIndEndIdx      the end index of the 0:n relation pointing to BswM_RulesInd
  RulesIndStartIdx    the start index of the 0:n relation pointing to BswM_RulesInd
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(BswM_ImmediateUserType, BSWM_CONST) BswM_ImmediateUser[5];
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_InitGenVarAndInitAL
**********************************************************************************************************************/
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(BswM_InitGenVarAndInitALType, BSWM_CONST) BswM_InitGenVarAndInitAL[1];
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_ModeNotificationFct
**********************************************************************************************************************/
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(BswM_PartitionFunctionType, BSWM_CONST) BswM_ModeNotificationFct[1];
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_PartitionIdentifiers
**********************************************************************************************************************/
/** 
  \var    BswM_PartitionIdentifiers
  \brief  the partition contex in Config
  \details
  Element                 Description
  PartitionSNV        
  PCPartitionConfigIdx    the index of the 1:1 relation pointing to BswM_PCPartitionConfig
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(BswM_PartitionIdentifiersType, BSWM_CONST) BswM_PartitionIdentifiers[1];
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_Rules
**********************************************************************************************************************/
/** 
  \var    BswM_Rules
  \details
  Element    Description
  Id         External id of rule.
  Init       Initialization value of rule state (TRUE, FALSE, UNDEFINED or DEACTIVATED).
  FctPtr     Pointer to the rule function which does the arbitration.
*/ 
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(BswM_RulesType, BSWM_CONST) BswM_Rules[19];
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_RulesInd
**********************************************************************************************************************/
/** 
  \var    BswM_RulesInd
  \brief  the indexes of the 1:1 sorted relation pointing to BswM_Rules
*/ 
#define BSWM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(BswM_RulesIndType, BSWM_CONST) BswM_RulesInd[22];
#define BSWM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_SwcModeRequestUpdateFct
**********************************************************************************************************************/
#define BSWM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(BswM_PartitionFunctionType, BSWM_CONST) BswM_SwcModeRequestUpdateFct[1];
#define BSWM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_ActionListQueue
**********************************************************************************************************************/
/** 
  \var    BswM_ActionListQueue
  \brief  Variable to store action lists which shall be executed.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(BswM_ActionListQueueUType, BSWM_VAR_NOINIT) BswM_ActionListQueue;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_CanSMChannelState
**********************************************************************************************************************/
/** 
  \var    BswM_CanSMChannelState
  \brief  Variable to store current mode of BswMCanSMIndication mode request ports.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(CanSM_BswMCurrentStateType, BSWM_VAR_NOINIT) BswM_CanSMChannelState[1];
#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_ComMChannelState
**********************************************************************************************************************/
/** 
  \var    BswM_ComMChannelState
  \brief  Variable to store current mode of BswMComMIndication mode request ports.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(ComM_ModeType, BSWM_VAR_NOINIT) BswM_ComMChannelState[1];
#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_DcmComState
**********************************************************************************************************************/
/** 
  \var    BswM_DcmComState
  \brief  Variable to store current mode of BswMDcmComModeRequest mode request ports.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Dcm_CommunicationModeType, BSWM_VAR_NOINIT) BswM_DcmComState[1];
#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_ForcedActionListPriority
**********************************************************************************************************************/
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(BswM_ForcedActionListPriorityType, BSWM_VAR_NOINIT) BswM_ForcedActionListPriority;
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_GenericState
**********************************************************************************************************************/
/** 
  \var    BswM_GenericState
  \brief  Variable to store current mode of BswMGenericRequest mode request ports.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(BswM_ModeType, BSWM_VAR_NOINIT) BswM_GenericState[4];
#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_Initialized
**********************************************************************************************************************/
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(BswM_InitializedType, BSWM_VAR_NOINIT) BswM_Initialized;
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_ModeRequestQueue
**********************************************************************************************************************/
/** 
  \var    BswM_ModeRequestQueue
  \brief  Variable to store an immediate mode request which must be queued because of a current active arbitration.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(BswM_ModeRequestQueueType, BSWM_VAR_NOINIT) BswM_ModeRequestQueue[5];
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_QueueSemaphore
**********************************************************************************************************************/
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(BswM_QueueSemaphoreType, BSWM_VAR_NOINIT) BswM_QueueSemaphore;
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_QueueWritten
**********************************************************************************************************************/
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(BswM_QueueWrittenType, BSWM_VAR_NOINIT) BswM_QueueWritten;
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  BswM_RuleStates
**********************************************************************************************************************/
/** 
  \var    BswM_RuleStates
  \brief  Stores the last execution state of the rule.
*/ 
#define BSWM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(BswM_RuleStatesType, BSWM_VAR_NOINIT) BswM_RuleStates[19];
#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "BswM_vMemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/

/* PRQA L:EXTERNDECLARATIONS */


#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (BSWM_USE_INIT_POINTER == STD_ON)
extern  P2CONST(BswM_ConfigType, AUTOMATIC, BSWM_PBCFG) BswM_ConfigPtr;
#endif

#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define BSWM_START_SEC_VAR_NOINIT_8BIT
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern VAR(uint8, BSWM_VAR_NOINIT) BswM_PduGroupControlInvocation;

#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* PRQA S 3218 3 */ /* MD_BswM_3218 */
extern VAR(Com_IpduGroupVector, BSWM_VAR_NOINIT) BswM_ComIPduGroupState;
extern VAR(Com_IpduGroupVector, BSWM_VAR_NOINIT) BswM_ComIPduGroupReinitState;
extern VAR(Com_IpduGroupVector, BSWM_VAR_NOINIT) BswM_ComRxIPduGroupDMState;

#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define BswM_IsPreInitialized()                     (BswM_PreInitialized) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#define BswM_SetPreInitialized(Value)               (BswM_IsPreInitialized()) = (Value) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/* -----------------------------------------------------------------------------
    &&&~ EXTERNAL DECLARATIONS
 ----------------------------------------------------------------------------- */

#define BSWM_START_SEC_CODE
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */






#if (BSWM_FUNCTION_BASED == STD_OFF)
/**********************************************************************************************************************
 *  BswM_Action_ActionListHandler()
 **********************************************************************************************************************/
/*!
 * \brief       Executes an action list.
 * \details     Executes all actions of an action list.
 * \param[in]   handleId  Id of the action list to execute.
 * \param[in]   partitionIdx Index of current partition Context
 * \return      E_OK      Action list was completely executed.
 * \return      E_NOT_OK  Action list was aborted because an action failed.
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
extern FUNC(Std_ReturnType, BSWM_CODE) BswM_Action_ActionListHandler(BswM_HandleType handleId, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
#endif

#if ((BSWM_RULES == STD_ON)  && (BSWM_FUNCTION_BASED == STD_OFF))
/**********************************************************************************************************************
 *  BswM_ArbitrateRule()
 **********************************************************************************************************************/
/*!
 * \brief       Arbitrates a rule.
 * \details     Evaluates the logical expression of the rule and determines the action list to execute.
 * \param[in]   ruleId  Id of the rule to arbitrate
 * \param[in]   partitionIdx  Index of current partition Context
 * \return      ID of action list to execute (BSWM_NO_ACTIONLIST if no action list shall be executed)
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
extern FUNC(BswM_SizeOfActionListsType, BSWM_CODE) BswM_ArbitrateRule(BswM_HandleType ruleId, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
#endif

/**********************************************************************************************************************
 *  BswM_ExecuteIpduGroupControl()
 **********************************************************************************************************************/
/*!
 * \brief       Enabes and disables PDU Groups and DeadlineMonitoring in Com.
 * \details     Forwards the changes to the local Com_IpduGroupVector caused by executed actions to the corresponding 
 *              Com APIS.
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
extern FUNC(void, BSWM_CODE) BswM_ExecuteIpduGroupControl(void);

#if(BSWM_IMMEDIATEUSER == STD_ON)
# if (BSWM_DEV_ERROR_REPORT == STD_ON)
/**********************************************************************************************************************
 *  BswM_ImmediateModeRequest()
 **********************************************************************************************************************/
/*!
 * \brief       Processes an immediate mode request.
 * \details     Queues mode request and starts arbitration of depending rules if no other request is currently active.
 * \param[in]   start   Handle of first mode request.
 * \param[in]   end     Handle of last mode request.
 * \param[in]   sid     Service Id of calling API. Only available if BSWM_DEV_ERROR_REPORT is STD_ON.
 * \param[in]   partitionIdx Index of current partition Context
 * \pre         -
 * \context     ANY
 * \reentrant   TRUE
 * \synchronous TRUE
 */
extern FUNC(void, BSWM_CODE) BswM_ImmediateModeRequest(BswM_SizeOfImmediateUserType start, BswM_SizeOfImmediateUserType end, uint8 sid, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
# else
extern FUNC(void, BSWM_CODE) BswM_ImmediateModeRequest(BswM_SizeOfImmediateUserType start, BswM_SizeOfImmediateUserType end, BswM_PCPartitionConfigIdxOfPartitionIdentifiersType partitionIdx);
# endif
#endif

#define BSWM_STOP_SEC_CODE
#include "BswM_vMemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* BSWM_PRIVATE_CFG_H */


