 /**********************************************************************************************************************
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
 *  -----------------------------------------------------------------------------------------------------------------*/
 /**        \file  CanNm.c
 *         \brief  AUTOSAR CAN Network Management
 *
 *       \details  Source of AUTOSAR CAN Network Management
 *                 AUTOSAR Release 4.0
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2_0779 */

#define CANNM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "CanNm.h"                                                          /* Include CAN Network Management header */
#include "CanNm_Cbk.h"                                                             /* Include CAN NM callback header */
#include "Nm_Cbk.h"                                                          /* Include NM Interface callback header */
#include "CanIf.h"                                                                   /* Include CAN Interface header */
#if ( CANNM_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"                                                                /* Include Development Error Tracer */
#endif
#include "SchM_CanNm.h"                                            /* Include Scheduler Module for Critical Sections */
#if ( CANNM_COM_USER_DATA_SUPPORT == STD_ON ) || defined ( CANNM_PN_CALC_FEATURE_ENABLED )
# include "PduR_CanNm.h"                                       /* ESCAN00064052 */ /* PduR Callback Header for CanNm */
#endif

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON ) && ( CANNM_PN_TX_TIMEOUT_EXCEPTION_FEATURE_ENABLED == STD_ON )
# include "CanSM_TxTimeoutException.h"                                  /* CanSM TxTimeoutException Header for CanNm */
#endif

#if ( CANNM_CONFIGURATION_VARIANT == CANNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE ) || \
    ( CANNM_POSTBUILD_VARIANT_SUPPORT == STD_ON )
# include "EcuM_Error.h"                                            /* ESCAN00064309 */ /* Include EcuM Error header */
#endif

#if ( CANNM_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
# include "Rtm.h"                                                /* ESCAN00067700 */ /* Include Run Time Measurement */
#endif

#if( CANNM_ERRORWAITBUSSLEEPTIMEOFCHANNELCONFIG == STD_ON )
# include "NmOsek.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information check */
#if (  (CANNM_SW_MAJOR_VERSION != (0x09u)) \
    || (CANNM_SW_MINOR_VERSION != (0x00u)) \
    || (CANNM_SW_PATCH_VERSION != (0x01u)) )
# error "Vendor specific version numbers of CanNm.c and CanNm.h are inconsistent"
#endif

/* vendor specific version information check */
#if (  (CANNM_CBK_MAJOR_VERSION != (0x09u)) \
    || (CANNM_CBK_MINOR_VERSION != (0x00u)) \
    || (CANNM_CBK_PATCH_VERSION != (0x01u)) )
# error "Vendor specific version numbers of CanNm.c and CanNm_Cbk.h are inconsistent"
#endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
/*! Definition of channel parameter for local functions. */
/* Local functions do not use a channel parameter in single channel configurations. */
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# define CANNM_CHANNEL_TYPE_ONLY                    void
# define CANNM_CHANNEL_TYPE_FIRST
# define CANNM_CHANNEL_PARA_ONLY
# define CANNM_CHANNEL_PARA_FIRST
#else
# define CANNM_CHANNEL_TYPE_ONLY                    CONST( NetworkHandleType, AUTOMATIC ) channel
# define CANNM_CHANNEL_TYPE_FIRST                   CONST( NetworkHandleType, AUTOMATIC ) channel,
# define CANNM_CHANNEL_PARA_ONLY                    CANNM_CHANNEL_IDX
# define CANNM_CHANNEL_PARA_FIRST                   CANNM_CHANNEL_IDX,
#endif

#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# define CANNM_CHANNEL_IDX                          ((NetworkHandleType)0u)
#else
# define CANNM_CHANNEL_IDX                          (channel)
#endif
#define CANNM_NMTOSYSTEM_CHANNEL_IND                (CanNm_GetChannelIdOfChannelConfig(CANNM_CHANNEL_IDX))


/* Enumeration type for Communication Control (optimized) */
/*! The application has no communication need and is ready to sleep. */
#define COMM_READY_SLEEP                            ((uint8)0x00u)
/*! The application has communication need. */
#define COMM_NORMAL_OPERATION                       ((uint8)0x01u)

/* Enumeration type for Message Transmission Control (optimized) */
/*! Message Transmission Ability is disabled/enabled */
#define MSG_TX_DISABLED                             ((uint8)0x00u)
#define MSG_TX_ENABLED                              ((uint8)0x01u)

/*! Mask to check if the Repeat Message Bit is set or reset */
#define CANNM_REPEAT_MSG_BIT_MASK                   ((uint8)0x01u)
#define CANNM_REPEAT_MSG_BIT_INV_MASK               ((uint8)0xFEu)

/*! Mask to check if the Active Wakeup Bit is set or reset */
#define CANNM_ACT_WU_BIT_MASK                       ((uint8)0x10u)
#define CANNM_ACT_WU_BIT_INV_MASK                   ((uint8)0xEFu)

/*! Mask to check if the Cluster Request Bit is set */
#define CANNM_CRI_BIT_MASK                          ((uint8)0x40u)

/*! CanNm Instance ID */
#define CANNM_INSTANCE_ID                           ((uint8)0x00u)

/*! Mask to check if asynchronous transmission is requested */
#define CANNM_NO_TRANSMIT_REQUEST                   ((uint8)0x00u)
#define CANNM_TRANSMIT_REQUEST                      ((uint8)0x02u)

/*! Number of system channels */
#if ( CANNM_SYSTONMCHIND == STD_ON )
# define CANNM_CFG_NUMBER_OF_SYS_CHANNELS           (CanNm_GetSizeOfSysToNmChInd())
#else
# define CANNM_CFG_NUMBER_OF_SYS_CHANNELS           (CanNm_GetSizeOfChannelConfig())
#endif

/*! Macros for communication requests */
#define CANNM_NO_RESTART                            ((uint8)0u)
#define CANNM_PASSIVE_RESTART                       ((uint8)1u)
#define CANNM_ACTIVE_RESTART                        ((uint8)2u)

/*! Macro for Coordinator Sleep Handling */
#define CANNM_COORD_ASLEEP_OR_NOT_READY_TO_SLEEP    ((uint8)0x00u)

/*! Macro for NmOsek LimpHome state */
#define CANNM_NMOSEK_LIMP_HOME_FLAG_MASK            ((uint8)0x08u)

#if !defined ( CANNM_LOCAL ) /* COV_MSR_COMPATIBILITY */
# define CANNM_LOCAL static
#endif

#if !defined ( CANNM_LOCAL_INLINE ) /* COV_MSR_COMPATIBILITY */
# define CANNM_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/* ESCAN00067700 */
/* Macros for Runtime Measurement Support */
#if ( CANNM_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
/* PRQA S 0342 3 */ /* MD_MSR_Rule20.10_0342 */
# define CanNm_Rtm_Start(measurement) { \
                                        Rtm_Start(RtmConf_##measurement); \
                                      }
/* PRQA S 0342 3 */ /* MD_MSR_Rule20.10_0342 */
# define CanNm_Rtm_Stop(measurement)  { \
                                        Rtm_Stop(RtmConf_##measurement); \
                                      }
#else
# define CanNm_Rtm_Start(measurement) 
# define CanNm_Rtm_Stop(measurement)
#endif


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

#if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
/* ----------- Local 8 Bit Data definitions without initialization need ----------- */
#  define CANNM_START_SEC_VAR_NOINIT_8BIT
#  include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! local variable which stores the first channel where Partial Networking is enabled. This is calculated during CanNm_LocalInit() */
CANNM_LOCAL VAR( uint8, CANNM_VAR_NOINIT ) nmMaxPnChannel;

#  define CANNM_STOP_SEC_VAR_NOINIT_8BIT
#  include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */
# endif
#endif

/* ----------- Local Data definitions with unspecified size and frequent access ----------- */
#define CANNM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ESCAN00064047 */ /* ESCAN00071960 */
#if ( CANNM_USE_INIT_POINTER == STD_ON )
/*! Pointer to the current configuration */
CANNM_LOCAL P2CONST( CanNm_ConfigType, CANNM_VAR_ZERO_INIT, CANNM_INIT_DATA ) CanNm_ConfigDataPtr = NULL_PTR;
#endif

#define CANNM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define CANNM_START_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* CAN NM version (BCD coded). */
CONST(uint8, CANNM_CONST) CanNm_MainVersion     = (uint8)CANNM_SW_MAJOR_VERSION;
CONST(uint8, CANNM_CONST) CanNm_SubVersion      = (uint8)CANNM_SW_MINOR_VERSION;
CONST(uint8, CANNM_CONST) CanNm_ReleaseVersion  = (uint8)CANNM_SW_PATCH_VERSION;

#define CANNM_STOP_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define CANNM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_DetermineDynamicPnInfoLength
**********************************************************************************************************************/
/*! \brief       Determine maximum number of PnInfo Bytes depending on received PDU Length.
 *  \details     -
 *  \pre         -
 *  \param[in]   PduInfoPtr       - Pointer to CAN PDU related data containing DLC and pointer to CAN SDU buffer.
 *  \note        Called by CanNm_RxIndication
 *  \return      Adjusted (shortened) PnInfoLength
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( uint8, CANNM_CODE ) CanNm_DetermineDynamicPnInfoLength( P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR )PduInfoPtr );
#endif

#if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_PnEiraCalculation
**********************************************************************************************************************/
/*! \brief       Process received Partial Networking EIRA information
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21718, SPEC-21836, SPEC-21835, SPEC-21762, SPEC-21703, SPEC-21833, SPEC-21814, SPEC-21694, SPEC-2225427
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_PnEiraCalculation( CANNM_CHANNEL_TYPE_ONLY );
#endif

#if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_PnEraCalculation
**********************************************************************************************************************/
/*! \brief       Process received Partial Networking ERA information
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction 
 *  \trace       SPEC-21718, SPEC-22001, SPEC-21880, SPEC-21972, SPEC-21916, SPEC-21978, SPEC-21981, SPEC-2225427
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_PnEraCalculation( CANNM_CHANNEL_TYPE_ONLY );
#endif

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_PnFilterHandling
**********************************************************************************************************************/
/*! \brief       Process Partial Networking information
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \param[in]   PduInfoPtr       - Pointer to CAN PDU related data containing DLC and pointer to CAN SDU buffer.
 *  \context     TASK|ISR1|ISR2
 *  \note        Called by CanNm_RxIndication
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( boolean, CANNM_CODE ) CanNm_PnFilterHandling( CANNM_CHANNEL_TYPE_FIRST P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr );
#endif

#if ( ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) \
        || ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON ) )
/**********************************************************************************************************************
  CanNm_CopyRxMessageData
**********************************************************************************************************************/
/*! \brief       Process Data received in last NM message
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \param[in]   PduInfoPtr       - Pointer to CAN PDU related data containing DLC and pointer to CAN SDU buffer.
 *  \context     TASK|ISR1|ISR2
 *  \note        Called by CanNm_RxIndication
 *  \trace       SPEC-21994
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_CopyRxMessageData( CANNM_CHANNEL_TYPE_FIRST P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr );
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
/**********************************************************************************************************************
  CanNm_CommunicationControlHandling
**********************************************************************************************************************/
/*! \brief       Process Communication Control requests
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21805, SPEC-21943, SPEC-21784, SPEC-22035, SPEC-21899, SPEC-21818, SPEC-21742
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_CommunicationControlHandling( CANNM_CHANNEL_TYPE_ONLY );
#endif

/**********************************************************************************************************************
  CanNm_MainRxTxConfHandling
**********************************************************************************************************************/
/*! \brief       Process Tx Confirmations and Rx Indications
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21879, SPEC-21818, SPEC-21766, SPEC-21735, SPEC-21912, SPEC-22015, SPEC-21686, 
 *  \trace       SPEC-21967,  SPEC-21935, SPEC-21924, SPEC-21699, SPEC-21725
 *  \trace       DSGN-CanNm22932
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_MainRxTxConfHandling( CANNM_CHANNEL_TYPE_ONLY );


#if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
/**********************************************************************************************************************
  CanNm_RepeatMessageIndHandling
**********************************************************************************************************************/
/*! \brief       Process Repeat Message Indications from CanNm_RepeatMessageRequest
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21685, SPEC-21999, SPEC-21935, SPEC-22014, SPEC-21738, SPEC-21956, SPEC-21882
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_RepeatMessageIndHandling( CANNM_CHANNEL_TYPE_ONLY );
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
/**********************************************************************************************************************
  CanNm_BusCommunicationHandling
**********************************************************************************************************************/
/*! \brief       Process Request / Release of Communication
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \param[in]   commState        - Current communication request state
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21842, SPEC-22023
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_BusCommunicationHandling( CANNM_CHANNEL_TYPE_FIRST CONST( uint8, AUTOMATIC ) commState );
#endif

/**********************************************************************************************************************
  CanNm_TimeoutTimerHandling
**********************************************************************************************************************/
/*! \brief       Process Timeout Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21818, SPEC-21819, SPEC-21949, SPEC-21906, SPEC-21892, SPEC-21961, SPEC-50198, SPEC-21861
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_TimeoutTimerHandling( CANNM_CHANNEL_TYPE_ONLY );

/**********************************************************************************************************************
  CanNm_RepeatMessageTimerHandling
**********************************************************************************************************************/
/*! \brief       Process Repeat Message Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21740, SPEC-21934, SPEC-21856
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_RepeatMessageTimerHandling( CANNM_CHANNEL_TYPE_ONLY );

/**********************************************************************************************************************
  CanNm_WaitBusSleepTimerHandling
**********************************************************************************************************************/
/*! \brief       Process Wait Bus Sleep Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21681, SPEC-21885
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_WaitBusSleepTimerHandling( CANNM_CHANNEL_TYPE_ONLY );

#if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_RemoteSleepTimerHandling
**********************************************************************************************************************/
/*! \brief       Process Remote Sleep Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21889
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_RemoteSleepTimerHandling( CANNM_CHANNEL_TYPE_ONLY );
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
/**********************************************************************************************************************
  CanNm_MessageTimerHandling
**********************************************************************************************************************/
/*! \brief       Process Message Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21954, SPEC-21757, SPEC-21979, SPEC-21864, SPEC-21864, SPEC-21687
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_MessageTimerHandling( CANNM_CHANNEL_TYPE_ONLY );


# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
/**********************************************************************************************************************
  CanNm_MessageTimeoutTimerHandling
**********************************************************************************************************************/
/*! \brief       Process Message Timeout Timer
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21710, SPEC-21690, SPEC-21860
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_MessageTimeoutTimerHandling( CANNM_CHANNEL_TYPE_ONLY );
# endif
#endif

#if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_CarWakeupIndication
**********************************************************************************************************************/
/*! \brief       Process Car Wakeup Indication
 *  \details     Evaluates the Car Wakeup Bit in the last received Nm message.
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_RxIndication
 *  \trace       SPEC-21721, SPEC-21811
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_CarWakeupIndication( CANNM_CHANNEL_TYPE_FIRST  P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr );
#endif

#if ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
/**********************************************************************************************************************
  CanNm_CoordReadyToSleepHandling
**********************************************************************************************************************/
/*! \brief       Process CoordinatorReadyToSleep Indication
 *  \details     Evaluates the Sleep Ready Bit in the last received Nm message.
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_RxIndication
 *  \trace       SPEC-21965, SPEC-50205
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_CoordReadyToSleepHandling( CANNM_CHANNEL_TYPE_FIRST  CONST( uint8, AUTOMATIC ) rxMsgByte );
#endif

/**********************************************************************************************************************
  CanNm_TransitionToRepeatMessage
**********************************************************************************************************************/
/*! \brief       Process transition to Repeat Message state
 *  \details     Process transition from any other state to Repeat Message state
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_StateTransition
 *  \trace       SPEC-21897, SPEC-21771, SPEC-22002, SPEC-50180, SPEC-21687
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_TransitionToRepeatMessage( CANNM_CHANNEL_TYPE_ONLY );

/**********************************************************************************************************************
  CanNm_TransitionToNetworkMode
**********************************************************************************************************************/
/*! \brief       Process transition to Network mode
 *  \details     Process transition from BusSleep / PrepareBusSleep to Network Mode
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_StateTransition
 *  \trace       SPEC-22026, SPEC-21944, SPEC-21987, SPEC-21803, SPEC-21818
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_TransitionToNetworkMode( CANNM_CHANNEL_TYPE_FIRST  CONST(uint8, AUTOMATIC) lastNmState );

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_PnLocal_Init
**********************************************************************************************************************/
/*! \brief       Initialization of Partial Networking relevant variables
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_StateTransition
 *  \trace       SPEC-21693
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_PnLocal_Init( CANNM_CHANNEL_TYPE_ONLY );
#endif

# if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_DisablePnFilter
**********************************************************************************************************************/
/*! \brief      Disable the PN message filter.
 *  \details    The PN message filtering is deactivated in case it was indicated during transition to sleep and
 *              CanNm_ConfirmPnAvailability() was not call yet.
 *  \param[in]  channel          - Local channel handle
 *  \pre        -
 *  \context    TASK
 *  \note       Called by CanNm_PassiveStartUp() and CanNm_NetworkRequest()
 */
CANNM_LOCAL FUNC( void, CANNM_CODE ) CanNm_DisablePnFilter( CANNM_CHANNEL_TYPE_ONLY );
#endif

/**********************************************************************************************************************
  CanNm_LocalInit
**********************************************************************************************************************/
/*! \brief       Initialization of the Generic Network Management
 *               and its internal state machine for one channel.
 *  \details     By default the CanNm starts in the Bus-Sleep Mode.
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_Init
 *  \trace       SPEC-21901, SPEC-21790, SPEC-21784, SPEC-21824, SPEC-21693, SPEC-21769, SPEC-21821, SPEC-21850, 
 *  \trace       SPEC-21831, SPEC-21769, SPEC-21815, SPEC-21843
 *  \trace       DSGN-CanNm22953
 *********************************************************************************************************************/
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_LocalInit( CANNM_CHANNEL_TYPE_ONLY );

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/**********************************************************************************************************************
  CanNm_TriggerTransmission
**********************************************************************************************************************/
/*! \brief       Triggers NM message transmission
 *  \details     -
 *  \pre         -
 *  \param[in]   channel          - Local channel handle
 *  \context     TASK
 *  \note        Called by CanNm_RequestBusSynchronization, CanNm_MainFunction
 *  \return      E_OK             - Successful transmission of Nm Message
 *               E_NOT_OK         - Transmit request is not accepted by CanIf (i.e. CanIf_Transmit returned E_NOT_OK )
 *  \trace       SPEC-21902, SPEC-50201, SPEC-21682
 *********************************************************************************************************************/
CANNM_LOCAL FUNC( Std_ReturnType, CANNM_CODE ) CanNm_TriggerTransmission( CANNM_CHANNEL_TYPE_ONLY );
#endif

/**********************************************************************************************************************
  CanNm_StateTransition
**********************************************************************************************************************/
/*! \brief       Perform a transition to another state of the state machine
 *  \details     CBV is only access on Task level -> no interrupt locks required
 *               Access to RepeatMsgBitIndFlag does not require interrupt locks
 *  \pre         -
 *  \param[in]   nextNmState      - Next state in the state machine
 *  \context     TASK
 *  \note        Called by CanNm_MainFunction
 *  \trace       SPEC-21784, SPEC-21885, SPEC-21803, SPEC-21764, SPEC-21711, SPEC-21693, SPEC-21706, SPEC-21807, 
 *  \trace       SPEC-21948, SPEC-21897, SPEC-21998, SPEC-22011, SPEC-21776, SPEC-21739, SPEC-21717, SPEC-50200, SPEC-50200
 *********************************************************************************************************************/
CANNM_LOCAL FUNC( void, CANNM_CODE ) CanNm_StateTransition( CANNM_CHANNEL_TYPE_FIRST
                                                     CONST( Nm_StateType, AUTOMATIC ) nextNmState );


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_DetermineDynamicPnInfoLength
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( uint8, CANNM_CODE ) CanNm_DetermineDynamicPnInfoLength( P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR )PduInfoPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  adjustedInfoLength;
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
  /* No need to check RX PDU Length, fixed length assumed */
  adjustedInfoLength = (uint8)CanNm_GetSizeOfPnFilterMask();
  CANNM_DUMMY_STATEMENT(PduInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  /* #10 If PduInfoPointer DLC is less than the configured PN Info length
   *      Cut off all overlapping PnInfoBytes
   *     otherwise all PN Bytes shall be processed
   *     return the adjusted PnInfoLength value
   */
  if( (uint8)(PduInfoPtr->SduLength ) < (uint8)(CanNm_GetPnInfoOffset() + CanNm_GetSizeOfPnFilterMask()) ) /* COV_CANNM_PN_INFO_LENGTH */
  {
    adjustedInfoLength = (uint8)(PduInfoPtr->SduLength - CanNm_GetPnInfoOffset());
  }
  else
  {
    adjustedInfoLength = (uint8)CanNm_GetSizeOfPnFilterMask();
  }
# endif
  return adjustedInfoLength;
}

#endif

#if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_PnEiraCalculation
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_PnEiraCalculation( CANNM_CHANNEL_TYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanNm_SizeOfPnFilterMaskType  pnClusterRequestByte;
  uint8_least  pnClusterRequestBit;
  uint8        pnClusterRequestNew;
  boolean      pnClusterRequestChanged;
  PduInfoType  nmPnInfo;

  /* #10 If Partial Networking is enabled on the local channel and PnEiraCalc is enabled */
  if(
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
      (CanNm_IsPnEnabledOfPbChannelConfig(CANNM_CHANNEL_IDX))
# else
      (CANNM_CHANNEL_IDX == nmMaxPnChannel)
# endif
# if ( CANNM_ISDEF_PNEIRACALCENABLED == STD_OFF )
      && ( CanNm_IsPnEiraCalcEnabled() )
# endif
  ) /* COV_CANNM_PN_ENABLED */
  {
    /* #100 Iterate all Partial Networking Cluster Bytes
     *       If received Nm message contains new or repeated requests
     *        Copy PNC requests to local buffer to avoid long interrupt locks
     *        Clear request buffer to detect changes in next received NM message
     *        If received PNC Byte contains new EIRA requests.
     *         Update local EIRA requests
     *        Iterate all PNC Bits in the current PNC Byte
     *         If PNC Bit is set
     *          Restart PnClusterResetTimer of the requested PNC with PnResetTime
     */
    pnClusterRequestChanged = FALSE;
    for( pnClusterRequestByte = 0u; pnClusterRequestByte < CanNm_GetSizeOfPnFilterMask(); pnClusterRequestByte++ )
    {
      if( CanNm_GetPnClusterReqNew(pnClusterRequestByte) != 0u )
      {
        SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_0();
        pnClusterRequestNew = CanNm_GetPnClusterReqNew(pnClusterRequestByte);
        CanNm_SetPnClusterReqNew(pnClusterRequestByte, 0u); /* SBSW_CANNM_CSL02 */
        SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_0();

        /* pnClusterRequestBit contains now the sum of current and new PN EIRA requests. variable is reused as iterator below */
        pnClusterRequestBit = (uint8)(CanNm_GetPnClusterReq(pnClusterRequestByte) | pnClusterRequestNew);

        if( pnClusterRequestBit != CanNm_GetPnClusterReq(pnClusterRequestByte) )
        {
          pnClusterRequestChanged = TRUE;
          CanNm_SetPnClusterReq(pnClusterRequestByte, (CanNm_PnClusterReqType)pnClusterRequestBit); /* SBSW_CANNM_CSL02 */
        }

        /* Reuse of variable pnClusterRequestBit to iterate all Bits in current Cluster Request Byte */
        for( pnClusterRequestBit = 0u; pnClusterRequestBit < CANNM_PN_CLUSTERS_PER_BYTE; pnClusterRequestBit++ )
        {
          if( (pnClusterRequestNew & (1u << pnClusterRequestBit)) != 0u )
          {
            CanNm_GetPnClusterResetTimer(pnClusterRequestByte)[pnClusterRequestBit] = (uint16)CanNm_GetPnResetTime(); /* SBSW_CANNM_CSL_FILTERMASK_INDEX_PNCLUSTERS_PER_BYTE_INDEX_ACCESS */
          }
        }
      }
      /* #200 If at least one PNC is requested.
       *       Iterate all PNC Bits in the current PNC Byte
       *       If PnClusterResetTimer of PNC Bit in PNC Byte has not elapsed
       *        Decrement PnClusterResetTimer by one
       *        If PnClusterResetTimer has elapsed
       *         Reset the local PNC request
       */
      if( CanNm_GetPnClusterReq(pnClusterRequestByte) != 0u )
      {
        for( pnClusterRequestBit = 0u; pnClusterRequestBit < CANNM_PN_CLUSTERS_PER_BYTE; pnClusterRequestBit++ )
        {
          if( CanNm_GetPnClusterResetTimer(pnClusterRequestByte)[pnClusterRequestBit] != 0u )
          {
            CanNm_GetPnClusterResetTimer(pnClusterRequestByte)[pnClusterRequestBit]--; /* SBSW_CANNM_CSL_FILTERMASK_INDEX_PNCLUSTERS_PER_BYTE_INDEX_ACCESS */

            if( CanNm_GetPnClusterResetTimer(pnClusterRequestByte)[pnClusterRequestBit] == 0u )
            {
              pnClusterRequestChanged = TRUE;
              CanNm_SetPnClusterReq(pnClusterRequestByte, (CanNm_PnClusterReqType)(CanNm_GetPnClusterReq(pnClusterRequestByte) & (uint8)(~(1u << pnClusterRequestBit)))); /* SBSW_CANNM_CSL02 */
            }
          }
        }
      }
    }

    /* #300 If an PNC EIRA request has changed, indicate this to the ComM (via PduR -> Com <- ComM)
     *       Pass the changed PnClusterRequest buffer to the Com by calling PduR_CanNmRxIndication
     */
    if( pnClusterRequestChanged == TRUE )
    {
      nmPnInfo.SduDataPtr = CanNm_GetAddrPnClusterReq(0); /* Assign nmPnInfo.SduDataPtr pointer to address of PnClusterReq array */
      nmPnInfo.SduLength = CanNm_GetPnInfoLength(); /* Set nmPnInfo.SduLength to length of PnInfo container */
      PduR_CanNmRxIndication( CanNm_GetPnEiraRxPduId(), &nmPnInfo ); /* SBSW_CANNM_POINTER_PARAM */
    }
  }
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON */


#if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_PnEraCalculation
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_PnEraCalculation( CANNM_CHANNEL_TYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  CanNm_PnClusterResetTimerExtEndIdxOfPbChannelConfigType  pnClusterRequestByte;
  uint8        pnClusterRequestBit;
  uint8        pnClusterRequestNew;
  boolean      pnClusterRequestChanged;
  PduInfoType  nmPnInfo;

  /* #10 If Partial Networking is enabled on the local channel and PnEraCalc is enabled */

  if( (CanNm_IsPnEnabledOfPbChannelConfig(CANNM_CHANNEL_IDX) )
    && (CanNm_IsPnEraCalcEnabledOfChannelConfig(CANNM_CHANNEL_IDX)) ) /* COV_CANNM_PN_ENABLED */
  {
  /*   #100 Iterate all Partial Networking Cluster Bytes
   *         If received Nm message contains new or repeated cluster requests
   *          Copy PNC requests to local buffer to avoid long interrupt locks
   *          Clear request buffer to detect changes in next received NM message
   *          If received PNC Byte contains new ERA requests.
   *           Update local ERA requests
   *          Iterate all PNC Bits in the current PNC Byte
   *           If Pn Cluster Bit is set
   *            Restart PnClusterResetTimer of the requested PNC ERA with PnResetTime
   */

    pnClusterRequestChanged = FALSE;
    for( pnClusterRequestByte = CanNm_GetPnClusterReqExtStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX);
         pnClusterRequestByte < CanNm_GetPnClusterReqExtEndIdxOfPbChannelConfig(CANNM_CHANNEL_IDX);
         pnClusterRequestByte++ )
    {
#  if (CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
      /* Runtime Check that CanNm_SetPnClusterReqExtNew array is always written within its defined bounds.
         A Development Error is issued in CanNm_PnLocal_Init(). */
      if( pnClusterRequestByte < CanNm_GetSizeOfPnClusterReqExtNew() ) /* COV_CANNM_CHECK_PNCLUSTERREQEXTNEW */
#  endif
      {
        if( CanNm_GetPnClusterReqExtNew(pnClusterRequestByte) != 0u )
        {
          SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_0();
          pnClusterRequestNew = CanNm_GetPnClusterReqExtNew(pnClusterRequestByte);
          CanNm_SetPnClusterReqExtNew(pnClusterRequestByte, 0u); /* SBSW_CANNM_PNCLUSTERREQEXTNEW */
          SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_0();

          pnClusterRequestBit = (uint8)(CanNm_GetPnClusterReqExt(pnClusterRequestByte) | pnClusterRequestNew);
          if( pnClusterRequestBit != CanNm_GetPnClusterReqExt(pnClusterRequestByte) )
          {
            pnClusterRequestChanged = TRUE;
            CanNm_SetPnClusterReqExt(pnClusterRequestByte, (CanNm_PnClusterReqExtType)pnClusterRequestBit); /* SBSW_CANNM_CSL03 */
          }

          for( pnClusterRequestBit = 0u; pnClusterRequestBit < CANNM_PN_CLUSTERS_PER_BYTE; pnClusterRequestBit++ )
          {
            if( (pnClusterRequestNew & (1u << pnClusterRequestBit)) != 0u )
            {
              CanNm_GetPnClusterResetTimerExt(pnClusterRequestByte)[pnClusterRequestBit] = (uint16)CanNm_GetPnResetTime(); /* SBSW_CANNM_CSL_FILTERMASK_INDEX_PNCLUSTERS_PER_BYTE_INDEX_ACCESS */
            }
          }
        }

        /* #200 If at least one PNC is requested.
         *       Iterate all PNC Bits in the current PNC Byte
         *       If PnClusterResetTimer of PNC Bit in PNC Byte has not elapsed
         *        Decrement PnClusterResetTimer by one
         *        If PnClusterResetTimer has elapsed
         *         Reset the local PNC request
         */
        if( CanNm_GetPnClusterReqExt(pnClusterRequestByte) != 0u )
        {
          for( pnClusterRequestBit = 0u; pnClusterRequestBit < CANNM_PN_CLUSTERS_PER_BYTE; pnClusterRequestBit++ )
          {
            if( CanNm_GetPnClusterResetTimerExt(pnClusterRequestByte)[pnClusterRequestBit] != 0u )
            {
              CanNm_GetPnClusterResetTimerExt(pnClusterRequestByte)[pnClusterRequestBit]--; /* SBSW_CANNM_CSL_FILTERMASK_INDEX_PNCLUSTERS_PER_BYTE_INDEX_ACCESS */
              
              if( CanNm_GetPnClusterResetTimerExt(pnClusterRequestByte)[pnClusterRequestBit] == 0u )
              {
                pnClusterRequestChanged = TRUE;
                CanNm_SetPnClusterReqExt(pnClusterRequestByte, (CanNm_PnClusterReqExtType)(CanNm_GetPnClusterReqExt(pnClusterRequestByte) & (uint8)(~(1u << pnClusterRequestBit))) ); /* SBSW_CANNM_CSL03 */
              }
            }
          }
        }
      }
    }

    /* #300 If an PNC ERA request has changed, indicate this to the ComM (via PduR -> Com <- ComM)
     *       Pass the changed PnClusterRequest buffer to the Com by calling PduR_CanNmRxIndication
     */
    if( pnClusterRequestChanged == TRUE )
    {
      /* ESCAN00064309 */
      nmPnInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, CANNM_VAR_NOINIT)) (CanNm_GetAddrPnClusterReqExt(CanNm_GetPnClusterReqExtStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX))); /* Assign nmPnInfo.SduDataPtr pointer to address of PnClusterReqExt array (with channel offset) */
      nmPnInfo.SduLength = CanNm_GetPnInfoLength(); /* Set nmPnInfo.SduLength to length of PnInfo container */
      PduR_CanNmRxIndication( CanNm_GetPnEraRxPduIdOfChannelConfig(CANNM_CHANNEL_IDX), &nmPnInfo ); /* SBSW_CANNM_POINTER_PARAM */
    }
  }
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */
#endif /* CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON */


#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_PnFilterHandling
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( boolean, CANNM_CODE ) CanNm_PnFilterHandling( CANNM_CHANNEL_TYPE_FIRST P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr )
{
  boolean      msgRelevant = FALSE;
  uint8_least  rxMsgBytePos;
  uint8        reqCluster;
#  if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
  uint8        pnClusterRequestIndex;
#  endif

  /* #10 If Partial Networking is enabled */
  /* #20 If configuration parameter <Pdu Cbv Position> is set to Byte 0 or Byte 1
   *     AND CBV Byte fits into RX PDU buffer length in case <CanIf Range Config DLC Check> is configured
   */
  if( CanNm_IsPnEnabledOfPbChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_PN_ENABLED */
  {
    if( (CanNm_GetPduCbvPositionOfChannelConfig(CANNM_CHANNEL_IDX) != CANNM_PDU_OFF)
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
      /* No need to check RX PDU Length, fixed length assumed */
# else
        && (PduInfoPtr->SduLength > CanNm_GetPduCbvPositionOfChannelConfig(CANNM_CHANNEL_IDX))
# endif
      ) /* COV_CANNM_CHECK_CBVPOSITION */
    {
      /* #200 If CRI bit is set in received CBV
       *      AND Pn Info data can be found in RX PDU buffer in case <CanIf Range Config DLC Check> is configured
       *       Calculate an adjusted / truncated Pn Info Length value in case <CanIf Range Config DLC Check> is configured and the received DLC does not match the expected DLC
       *       Iterate all received Pn Info Bytes
       *        Store the received Pn Requests filtered by the configured Pn Filter Mask
       *        If at least one request matches the filter
       *         If <Pn Eira Calc Enabled> is configured
       *          Store the filtered EIRA request for further processing in CanNm_MainFunction
       *         If <Pn Era Calc Enabled> is configured
       *          Store the filtered ERA request for further processing in CanNm_MainFunction
       */
      if( (((uint8)(PduInfoPtr->SduDataPtr[CanNm_GetPduCbvPositionOfChannelConfig(CANNM_CHANNEL_IDX)]) &
                    CANNM_CRI_BIT_MASK) != 0u )
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
          /* No need to check RX PDU Length, fixed length assumed */
# else
          && (PduInfoPtr->SduLength > CanNm_GetPnInfoOffset())
# endif
        )
      {
        /* PN is enabled, PN bit is true => apply filter algorithm: */
        /* copy the requests and apply the PN filter mask: */
        SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_0();

        for( rxMsgBytePos = 0u; rxMsgBytePos < CanNm_DetermineDynamicPnInfoLength( PduInfoPtr ); rxMsgBytePos++ ) /* SBSW_CANNM_LOCALFUNCTION_CALL */
        {
          reqCluster =
            (uint8)(PduInfoPtr->SduDataPtr[rxMsgBytePos + CanNm_GetPnInfoOffset()] & CanNm_GetPnFilterMask(rxMsgBytePos));
          if( reqCluster != 0u )
          {
            msgRelevant = TRUE;
# if defined ( CANNM_PN_CALC_FEATURE_ENABLED )
#  if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
#   if ( CANNM_ISDEF_PNEIRACALCENABLED == STD_OFF )
            if( CanNm_IsPnEiraCalcEnabled() )
#   endif
            {
#   if( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
              /* Runtime Check that CanNm_SetPnClusterReqNew array is always written within its defined bounds. */
              if( rxMsgBytePos < CanNm_GetSizeOfPnClusterReqNew() ) /* COV_CANNM_CHECK_PNCLUSTERREQEXTNEW */
#   endif
              {
                CanNm_SetPnClusterReqNew(rxMsgBytePos, (CanNm_PnClusterReqNewType)(CanNm_GetPnClusterReqNew(rxMsgBytePos) | reqCluster)); /* SBSW_CANNM_CSL01_DYN_PNINFOLENGTH */
              }
            }
#  endif
#  if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )

            if( CanNm_IsPnEraCalcEnabledOfChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_PN_ERA_CALC_ENABLED */
            { /* ESCAN00064309 */
              pnClusterRequestIndex = (uint8)(CanNm_GetPnClusterReqExtStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX) + rxMsgBytePos);
#   if( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
              /* Runtime Check that CanNm_SetPnClusterReqExtNew array is always written within its defined bounds. */
              if( pnClusterRequestIndex < CanNm_GetSizeOfPnClusterReqExtNew() ) /* COV_CANNM_CHECK_PNCLUSTERREQEXTNEW */
#   endif
              {
                CanNm_SetPnClusterReqExtNew(pnClusterRequestIndex, (CanNm_PnClusterReqExtNewType)((CanNm_GetPnClusterReqExtNew(pnClusterRequestIndex)) | reqCluster)); /* SBSW_CANNM_PNCLUSTERREQEXTNEW */
              }
            }
#  endif
# else
            break;
# endif
          }
        }
        SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_0();
      }
    } /* if ( (CanNm_GetPduCbvPositionOfChannelConfig(CANNM_CHANNEL_IDX) != CANNM_PDU_OFF) && ... ) */
  } /* if ( CanNm_IsPnEnabledOfPbChannelConfig ) */
  else
  {
    msgRelevant = TRUE;
  }

  return msgRelevant;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif

#if ( ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) \
        || ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON ) )
/**********************************************************************************************************************
  CanNm_CopyRxMessageData
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_CopyRxMessageData( CANNM_CHANNEL_TYPE_FIRST P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr )
{
  uint8  rxMsgByte;

  /* #10 Copy received NM message data to the Rx Message Data buffer */
  SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_4();
  for( rxMsgByte = 0u; rxMsgByte < CanNm_GetRxMessageDataLengthOfPbChannelConfig(CANNM_CHANNEL_IDX); rxMsgByte++ ) /* ESCAN00064309 */
  {
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
    /* No need to check RX PDU Length, fixed length assumed */
# else
    if( rxMsgByte >= (PduInfoPtr->SduLength) )
    {
      CanNm_SetRxMessageData(CanNm_GetRxMessageDataStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX) + rxMsgByte, 0u); /* SBSW_CANNM_CSL03 */
    }
    else
# endif
    {
      CanNm_SetRxMessageData(CanNm_GetRxMessageDataStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX) + rxMsgByte, (CanNm_RxMessageDataType)(PduInfoPtr->SduDataPtr[rxMsgByte]) ); /* SBSW_CANNM_CSL03 */
    }
  }
  SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_4();
}
#endif


#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  CanNm_CommunicationControlHandling
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_CommunicationControlHandling( CANNM_CHANNEL_TYPE_ONLY )
{

  uint8 txControlStateReq;
  /* #10 If communication allowed request has changed
   *      Update TxControlState
   */
  txControlStateReq = CanNm_GetTxControlStateRequest(CANNM_CHANNEL_IDX);
  if( CanNm_GetTxControlState(CANNM_CHANNEL_IDX) != txControlStateReq )
  {
    CanNm_SetTxControlState(CANNM_CHANNEL_IDX, (CanNm_TxControlStateType)txControlStateReq); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    /* #100 If communication is not allowed
     *       Stop Nm Timeout Timer.
     *       Reset Remote Sleep Timer and state.
     *       Stop Nm Message Timer
     */
    if( txControlStateReq == MSG_TX_DISABLED )
    {
      CanNm_SetTimeoutTimer(CANNM_CHANNEL_IDX, 0u); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
      CanNm_SetRemoteSleepTimer(CANNM_CHANNEL_IDX, 0u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      CanNm_SetRemoteSleepIndState(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# endif
      CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, 0u); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    }
    /* #110 otherwise start Nm Timeout Timer
     *       In state NormalOperation: Start RemoteSleepIndicationTimer.
     *       In state NormalOperation or RepeatMessage: Start MessageTimer
     */
    else
    {
      CanNm_SetTimeoutTimer(CANNM_CHANNEL_IDX, (CanNm_TimeoutTimerType)((CanNm_TimeoutTimerType)CanNm_GetTimeoutTimeOfChannelConfig(CANNM_CHANNEL_IDX) + 1u)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
      if( CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION )
      {
        CanNm_SetRemoteSleepTimer(CANNM_CHANNEL_IDX, (CanNm_RemoteSleepTimerType)((CanNm_RemoteSleepTimerType)CanNm_GetRemoteSleepIndTimeOfChannelConfig(CANNM_CHANNEL_IDX) + 1u)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      }
# endif
      if( ( CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION ) ||
          ( CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_REPEAT_MESSAGE ) )
      {
        CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, (CanNm_MsgTimerType)((CanNm_MsgTimerType)CanNm_GetMsgCycleOffsetOfPbChannelConfig(CANNM_CHANNEL_IDX) + 1u)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      }
    }
  }
}
#endif /* #if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON ) */

/***********************************************************************************************************************
 *  CanNm_MainRxTxConfHandling
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_MainRxTxConfHandling( CANNM_CHANNEL_TYPE_ONLY )
{

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
  /* #10 Processing of event: Tx Confirmation (#1)
   *     If message transmission has been confirmed by CanIf
   *      If message transmission is allowed
   *       Restart Timeout Timer
   *      Stop Message Timeout Timer if Immediate Tx conf is enabled
   */
  /*
   * No interrupt locks required due to an update of the flag in the receive interrupt
   * does not influence the algorithm, even if it occurs somewhere near the check.
   */

  if( CanNm_IsMsgConfirmationFlag(CANNM_CHANNEL_IDX) )
  {
    CanNm_SetMsgConfirmationFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
    if ( CanNm_GetTxControlState(CANNM_CHANNEL_IDX) == MSG_TX_ENABLED )
# endif
    {
      CanNm_SetTimeoutTimer(CANNM_CHANNEL_IDX, (CanNm_TimeoutTimerType)((CanNm_TimeoutTimerType)CanNm_GetTimeoutTimeOfChannelConfig(CANNM_CHANNEL_IDX) + 1u)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    }
# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
    CanNm_SetMsgTimeoutTimer(CANNM_CHANNEL_IDX, 0u); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# endif
  }
#endif

  /* #20 Processing of event: Rx Indication. (#2)
   *     If NM message has been received
   */
  if( CanNm_IsMsgIndicationFlag(CANNM_CHANNEL_IDX) )
  {
    CanNm_SetMsgIndicationFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    switch (CanNm_GetNmState(CANNM_CHANNEL_IDX))
    {
      /* -------------------- Bus Sleep -------------------- */
      case NM_STATE_BUS_SLEEP:
        /* #200 in BusSleep
         *       Request to restart the network if a NM message has been received in Bus-Sleep Mode.
         */
        Nm_NetworkStartIndication ( CANNM_NMTOSYSTEM_CHANNEL_IND );
        break;

        /* -------------------- Prepare Bus Sleep -------------------- */
      case NM_STATE_PREPARE_BUS_SLEEP:
        /* #210 in PrepareBusSleep
         *       Perform state transition to RepeatMessage state (refer to CanNm_StateTransition)
         */
        CanNm_StateTransition ( CANNM_CHANNEL_PARA_FIRST NM_STATE_REPEAT_MESSAGE );
        break;

#if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) || ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON )
        /* -------------------- Normal Operation -------------------- */
        case NM_STATE_NORMAL_OPERATION:
          /* #220 in NormalOperation
           *       If message transmission is allowed
           *        Restart Remote Sleep Indication Timer
           *        If BusLoadReduction is enabled
           *         Reload NM message transmission timer with reduced cycle time.
           */
# if ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
          if ( CanNm_GetTxControlState(CANNM_CHANNEL_IDX) == MSG_TX_ENABLED )
# endif
          {
# if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
            CanNm_SetRemoteSleepTimer(CANNM_CHANNEL_IDX, (CanNm_RemoteSleepTimerType)((CanNm_RemoteSleepTimerType)CanNm_GetRemoteSleepIndTimeOfChannelConfig(CANNM_CHANNEL_IDX) + 1u)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# endif

# if ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON )
            /* Busload Reduction can only be active in normal operation and nowhere else */
            if( CanNm_IsBusLoadReductionActiveOfChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_BUS_LOAD_REDUCTION */
            {
              CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, (CanNm_MsgTimerType)((CanNm_MsgTimerType)CanNm_GetMsgReducedTimeOfPbChannelConfig(CANNM_CHANNEL_IDX) + 1u)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
            }
# endif /* ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON ) */
          }

        /* -------------------- Ready Sleep -------------------- */
        /* FALLTHROUGH */
        case NM_STATE_READY_SLEEP: /* PRQA S 2003 */ /* MD_CANNM_Rule16.3 */
          /* #230 in ReadySleep or NormalOperation
           *       Reset RemoteSleepIndication state
           *       Indicate RemoteSleepCancellation to the NmIf
           */
# if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
          if( CanNm_IsRemoteSleepIndState(CANNM_CHANNEL_IDX) )
          {
            CanNm_SetRemoteSleepIndState(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
            Nm_RemoteSleepCancellation( CANNM_NMTOSYSTEM_CHANNEL_IND );
          }
# endif /* ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) */
#endif /* ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) || ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON ) */

        /* -------------------- Repeat Message -------------------- */
        /* FALLTHROUGH */
      default: /* PRQA S 2003 */ /* MD_CANNM_Rule16.3 */
        /* #240 in RepeatMessage, ReadySleep or NormalOperation
         *       If message transmission is allowed
         *        Restart TimeoutTimer in order to stay awake
         */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
        if ( CanNm_GetTxControlState(CANNM_CHANNEL_IDX) == MSG_TX_ENABLED )
#endif
        {
          CanNm_SetTimeoutTimer(CANNM_CHANNEL_IDX, (CanNm_TimeoutTimerType)((CanNm_TimeoutTimerType)CanNm_GetTimeoutTimeOfChannelConfig(CANNM_CHANNEL_IDX) + 1u)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
        }
        break;
    }
  }
} /* PRQA S 6030 */ /* MD_MSR_STCYC */

#if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  CanNm_RepeatMessageIndHandling
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_RepeatMessageIndHandling( CANNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If RepeatMessage state was requested internally (Discovery of Network Nodes)
   *      Request RepeatMessage Indication to NmIf
   *      Set Repeat Message Bit in CBV
   */
  if (CanNm_IsRepeatMsgReqFlag(CANNM_CHANNEL_IDX))
  {
    CanNm_SetRepeatMsgBitIndFlag(CANNM_CHANNEL_IDX, TRUE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    /* Check for valid PDU Position */
    if ( CanNm_IsTxMessageData_CBVUsedOfPbChannelConfig(CANNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_CANNM_CHECK_CBVPOSITION */
    {
      /* Control Bit Vector is only accessed on task level. Therefore no interrupt locks are necessary. */
      /* Set Repeat Message Bit. */ /* ESCAN00064309 */
      CanNm_SetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX), /* SBSW_CANNM_CSL03 */
        (CanNm_TxMessageDataType)(CanNm_GetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)) | CANNM_REPEAT_MSG_BIT_MASK));
    }
  }
  /* #20 If RepeatMessageIndication is requested by Network or internally
   *      Indicate the NmIf that CanNm is no longer ready to sleep
   *      Execute state transition to RepeatMessage state
   *      Reset RepeatMessage request
   */
  if( CanNm_IsRepeatMsgBitIndFlag(CANNM_CHANNEL_IDX) )
  {
#  if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
    if( CanNm_IsRemoteSleepIndState(CANNM_CHANNEL_IDX) )
    {
      /* Notification that some nodes in the network are not ready to sleep. */
      Nm_RemoteSleepCancellation( CANNM_NMTOSYSTEM_CHANNEL_IND );
    }
#  endif
    /* Perform a State Transition to Repeat Message State. */
    CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST NM_STATE_REPEAT_MESSAGE );
    CanNm_SetRepeatMsgReqFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
  }
}
#endif /* ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) */

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
/***********************************************************************************************************************
 *  CanNm_BusCommunicationHandling
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_BusCommunicationHandling( CANNM_CHANNEL_TYPE_FIRST CONST( uint8, AUTOMATIC ) commState )
{
  /* #10 If Network is requested AND NmState is ReadySleep
   *      Do state transition to NormalOperation state
   *     If Network is released AND NmState is NormalOperation
   *      Do state transition to ReadySleep state
   */
  if( commState == COMM_NORMAL_OPERATION )
  {
    if( CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_READY_SLEEP )
    {
      /* Perform a state transition because bus-communication has been requested. */
      CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_NORMAL_OPERATION);
    }
  }
  else
  {
    if( CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION )
    {
      /* Perform a state transition because bus-communication has been released. */
      CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_READY_SLEEP );
    }
  }
}
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

/***********************************************************************************************************************
 *  CanNm_TimeoutTimerHandling
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_TimeoutTimerHandling( CANNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If Timeout Timer is running
   *      Decrement Timeout Timer
   *      If Timeout Timer has elapsed
   *       If NmState is not ReadySleep
   *        Report Development Error
   *        Restart Timeout Timer
   *       otherwise do state transition to PrepareBusSleep state
   */
  if( CanNm_GetTimeoutTimer(CANNM_CHANNEL_IDX) != 0u )
  {
    CanNm_DecTimeoutTimer(CANNM_CHANNEL_IDX); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    if( CanNm_GetTimeoutTimer(CANNM_CHANNEL_IDX) == 0u )
    {
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
      if( CanNm_GetNmState(CANNM_CHANNEL_IDX) != NM_STATE_READY_SLEEP )
      {
        /* Handling of the Timeout Timer (Repeat Message State and Normal Operation State) */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON ) && ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF )
        /* Report error if the timeout timer times out in Repeat Message State
         * or Normal Operation State.
         */
        (void)Det_ReportError( CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_MAINFUNCTION, CANNM_E_NETWORK_TIMEOUT );
# endif

        /* Restart the NM Timeout Timer. */
        CanNm_SetTimeoutTimer(CANNM_CHANNEL_IDX, (CanNm_TimeoutTimerType)CanNm_GetTimeoutTimeOfChannelConfig(CANNM_CHANNEL_IDX)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      }
      else
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */
      {
        /* Leave Ready Sleep State, when the Timeout Timer has expired. */
        CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_PREPARE_BUS_SLEEP );
      }
    }
  } /* Timeout Timer Handling */
}

/***********************************************************************************************************************
 *  CanNm_RepeatMessageTimerHandling
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_RepeatMessageTimerHandling( CANNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If Repeat Message Timer is running
   *      Decrement Repeat Message Timer
   *      If Repeat Message Timer has elapsed
   *       Do state transition to either NormalOperation (non-passive) or ReadySleep state, depending on internal request state.
   */
  if( CanNm_GetRepeatMsgTimer(CANNM_CHANNEL_IDX) != 0u )
  {
    CanNm_DecRepeatMsgTimer(CANNM_CHANNEL_IDX); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    if( CanNm_GetRepeatMsgTimer(CANNM_CHANNEL_IDX) == 0u ) /* COV_CANNM_CHECK_REPEATMSGTIMER */
    {
      /* Repeat Message State is left upon Repeat Message Timer timeout. */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
      CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST
                             (Nm_StateType)((CanNm_GetCommState(CANNM_CHANNEL_IDX) == COMM_NORMAL_OPERATION) ?
                                             NM_STATE_NORMAL_OPERATION : NM_STATE_READY_SLEEP) );
#else
      CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_READY_SLEEP );
#endif
    }
  } /* Repeat Message Timer Handling */
}


/**********************************************************************************************************************
  CanNm_WaitBusSleepTimerHandling
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_WaitBusSleepTimerHandling( CANNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If Wait Bus Sleep Timer is running
   *      Decrement Wait Bus Sleep Timer
   *      If Wait Bus Sleep Timer has elapsed
   *       Do state transition to BusSleep state
   */
  if( CanNm_GetWaitBusSleepTimer(CANNM_CHANNEL_IDX) != 0u )
  {
    CanNm_DecWaitBusSleepTimer(CANNM_CHANNEL_IDX); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    if( CanNm_GetWaitBusSleepTimer(CANNM_CHANNEL_IDX) == 0u )
    {
      /* Prepare Bus-Sleep Mode is left upon Wait Bus-Sleep Timer timeout. */
      CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_BUS_SLEEP );
    }
  } /* Wait Bus Sleep Timer Handling */
}

#if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_RemoteSleepTimerHandling
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_RemoteSleepTimerHandling( CANNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If Remote Sleep Indication Timer is running
   *      Decrement Remote Sleep Indication Timer
   *      If Remote Sleep Indication Timer has elapsed
   *       Indicate that channel is ready to go to sleep
   */
  if( CanNm_GetRemoteSleepTimer(CANNM_CHANNEL_IDX) != 0u )
  {
    CanNm_DecRemoteSleepTimer(CANNM_CHANNEL_IDX); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    if( CanNm_GetRemoteSleepTimer(CANNM_CHANNEL_IDX) == 0u )
    {
      /* Remote Sleep Indication (Normal Operation State only). */
      CanNm_SetRemoteSleepIndState(CANNM_CHANNEL_IDX, TRUE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */

      /* Notification that all other nodes are ready to sleep. */
      Nm_RemoteSleepIndication( CANNM_NMTOSYSTEM_CHANNEL_IND );
    }
  }
}
#endif /* ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) */

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
/**********************************************************************************************************************
  CanNm_MessageTimerHandling
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_MessageTimerHandling( CANNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If Tx Message Timer is running
   *      Decrement Tx Message Timer
   *      If Tx Message Timer has elapsed OR message shall be sent asynchronously (PN feature)
   *       Transmit one NM message
   *       If Immediate NM message shall be sent
   *        Clear the RetryFirstMessageRequestFlag
   *        If transmit request was successful
   *         Reduce number of Immediate NM transmissions by one
   *         Restart Tx Message Timer with ImmediateNmCycleTime
   *        If transmit request failed
   *         Restart Tx Message Timer with MainFunctionCycleTime
   */
  if( CanNm_GetMsgTimer(CANNM_CHANNEL_IDX) != 0u )
  {
    CanNm_DecMsgTimer(CANNM_CHANNEL_IDX); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    if( (CanNm_GetMsgTimer(CANNM_CHANNEL_IDX) == 0u )
# if ( CANNM_COM_USER_DATA_SUPPORT == STD_ON ) || ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
        || (CanNm_GetMsgRequest(CANNM_CHANNEL_IDX) != 0u)
# endif
      ) /* COV_CANNM_NO_REPMSG */
    {
      /* Transmit a NM message. */
      Std_ReturnType success = CanNm_TriggerTransmission( CANNM_CHANNEL_PARA_ONLY );

# if ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
      /* Reset timer with immediate cycle time when transmissions greater zero  */
      if( CanNm_GetImmediateNmMsgCount(CANNM_CHANNEL_IDX) != 0u )
      {
#if ( CANNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
        CanNm_SetRetryFirstMessageRequestFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
        if( success == E_OK )
        {
          CanNm_DecImmediateNmMsgCount(CANNM_CHANNEL_IDX); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */

          if ( CanNm_GetImmediateNmMsgCount(CANNM_CHANNEL_IDX) == 0u )
          {
            /* Reset Timer to MsgCycle Time */
            CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, (CanNm_MsgTimerType)(CanNm_GetMsgCycleTimeOfChannelConfig(CANNM_CHANNEL_IDX))); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
          }
          else
          {
            CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, (CanNm_MsgTimerType)CanNm_GetImmediateNmCycleTimeOfChannelConfig(CANNM_CHANNEL_IDX)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
          }
        }
        else
        {
          /* Try transmission in next main function cycle */
          CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, 1u); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
        }
      }
      else
# endif
       /*  #20  If no immediate Nm message shall be sent 
        *        If the RetryFirstMessageRequestFlag is set
        *         If transmit request was successful
        *          Clear the RetryFirstMessageRequestFlag
        *          If ImmediateRestart was enabled and failed
        *           Set MsgTimer to MsgCycleOffset
        *          If ImmediateRestart was not enabled or didn't fail
        *           Restart Tx Message Timer with MsgCycleTime
        *         If transmit request failed
        *          Restart Tx Message Timer with MainFunctionCycleTime
        *        If the RetryFirstMessgeRequestFlag is cleared
        *         Restart Tx Message Timer with MsgCycleTime
        */
      {
#if ( CANNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
        if ( CanNm_IsRetryFirstMessageRequestFlag(CANNM_CHANNEL_IDX) )
        {
          if( success == E_OK )
          {
            /* If one message was successfully transmitted, the RetryFirstMessageRequest feature is turned off */
            CanNm_SetRetryFirstMessageRequestFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
            
# if ( CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
            /* If the ImmediateRestart message failed, the MsgTimer will be reloaded with the offset that would have been transmitted if the ImmediateRestart didn't fail */
            if ( CanNm_IsImmediateRestartFailed(CANNM_CHANNEL_IDX) )
            {
              CanNm_SetImmediateRestartFailed( CANNM_CHANNEL_IDX, FALSE ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
              /* Reset Timer to MsgCycleOffset */
              CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, (CanNm_MsgTimerType)(CanNm_GetMsgCycleOffsetOfPbChannelConfig(CANNM_CHANNEL_IDX))); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
            }
            else
# endif
            {
              /* Reset Timer to MsgCycle Time */
              CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, (CanNm_MsgTimerType)(CanNm_GetMsgCycleTimeOfChannelConfig(CANNM_CHANNEL_IDX))); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
            }
          }
          else
          {
            /* Try transmission in next main function cycle */
            CanNm_SetMsgTimer( CANNM_CHANNEL_IDX, 1u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
          }
        }
        else
#endif
        {
          /* Reset Timer to MsgCycle Time */
          CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, (CanNm_MsgTimerType)(CanNm_GetMsgCycleTimeOfChannelConfig(CANNM_CHANNEL_IDX))); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
        }

        CANNM_DUMMY_STATEMENT( success ); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
      }
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
/**********************************************************************************************************************
  CanNm_MessageTimeoutTimerHandling
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_MessageTimeoutTimerHandling( CANNM_CHANNEL_TYPE_ONLY )
{
  /* #10 If Tx Message Timeout Timer is running
   *      Decrement Tx Message Timeout Timer
   *      If Tx Message Timer Timeout has elapsed
   *       Inform NmIf of the timeout
   *       Inform CanSM of the timeout ( PN feature only )
   */
  
  if( CanNm_GetMsgTimeoutTimer(CANNM_CHANNEL_IDX) != 0u )
  {
    SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_6();
    CanNm_DecMsgTimeoutTimer(CANNM_CHANNEL_IDX); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */

    if( CanNm_GetMsgTimeoutTimer(CANNM_CHANNEL_IDX) == 0u )
    {
      /* The ExArea must be closed in any case. The else path is created to keep the <>_TxTimeoutException call out of the ExArea. */
      SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_6();
      /* Call timeout exception only once  */
      Nm_TxTimeoutException( CANNM_NMTOSYSTEM_CHANNEL_IND );
#  if ( CANNM_PN_FEATURE_ENABLED == STD_ON ) && ( CANNM_PN_TX_TIMEOUT_EXCEPTION_FEATURE_ENABLED == STD_ON )
      if( (CanNm_IsPnEnabledOfPbChannelConfig(CANNM_CHANNEL_IDX)) &&
           (CanNm_IsPnCallTxTimeoutExceptionOfChannelConfig(CANNM_CHANNEL_IDX)) ) /* COV_CANNM_PN_ENABLED */
      {
        /* PN Feature enabled: call CanSM_TxTimeoutException */
        CanSM_TxTimeoutException( CANNM_NMTOSYSTEM_CHANNEL_IND );
      }
#  endif
    }
    else
    {
      SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_6();
    }
  }
}
# endif
#endif


#if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_CarWakeupIndication
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_CarWakeupIndication( CANNM_CHANNEL_TYPE_FIRST  P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr )
{
  /* #10 If all of the following conditions are met:
   *     1. "Car Wake Up Rx Enabled" is configured
   *     2. "Car Wake Up Byte Position is within received PDU length in case "CanIf Range Config DLC Check" is configured
   *     3. ( "Car Wake Up Filter Enabled" is not configured OR Node Identifier Byte is within received PDU length in case "CanIf Range Config DLC Check" is configured )
   *     4. Car Wake Up Bit is set in Car WakeUp Byte
   *     5. ( "Car Wake Up Filter Enabled" is not configured OR the received Node ID is equal to "Car Wake Up Filter Node Id" )
   *        Notify Car Wakeup to the Nm Interface
   */
  if( (CanNm_IsCarWakeUpRxEnabledOfChannelConfig(CANNM_CHANNEL_IDX)) 
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
     /* No need to check RX PDU Length, fixed length assumed */
# else
     /* Check whether Car Wake Up Byte can be found inside RX PDU buffer */
     && (PduInfoPtr->SduLength > CanNm_GetCarWakeUpBytePositionOfChannelConfig(CANNM_CHANNEL_IDX))
# endif
    ) /* COV_CANNM_CAR_WAKEUP_RX */
  { /* ESCAN00064309, ESCAN00078984 */
    if( (CanNm_GetRxMessageData(CanNm_GetRxMessageData_CarWakeUpByteIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)) & (CanNm_GetCarWakeUpBitMaskOfChannelConfig(CANNM_CHANNEL_IDX))) != 0u )
    {
# if ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED == STD_ON )
      if( (!CanNm_IsCarWakeUpFilterEnabledOfChannelConfig(CANNM_CHANNEL_IDX)) ||
          ((CanNm_GetPduNidPositionOfChannelConfig(CANNM_CHANNEL_IDX) != CANNM_PDU_OFF) &&
          (CanNm_GetRxMessageData(CanNm_GetRxMessageData_NIDIdxOfPbChannelConfig(CANNM_CHANNEL_IDX))
          == CanNm_GetCarWakeUpFilterNodeIdOfChannelConfig(CANNM_CHANNEL_IDX))) ) /* COV_CANNM_CAR_WAKEUP_FILTER */
# endif
      {
        /* CanNm_GetPduData shall return PDU Data for this call is
            fulfilled because message is already copied to local buffer  */
        Nm_CarWakeUpIndication( CANNM_NMTOSYSTEM_CHANNEL_IND );
      }
    }
  }
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
  CANNM_DUMMY_STATEMENT(PduInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
}
#endif

#if ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
/**********************************************************************************************************************
  CanNm_CoordReadyToSleepHandling
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_CoordReadyToSleepHandling( CANNM_CHANNEL_TYPE_FIRST  CONST( uint8, AUTOMATIC ) rxMsgByte )
{
  /* #10 If Sleep Ready Bit has changed and NmIf has not been notified yet
   *      If Sleep Ready Bit is set
   *       Call Nm_CoordReadyToSleepIndication()
   *      otherwise Call Nm_CoordReadyToSleepCancellation()
   *       Update the changed Sleep Ready Bit
   */
  uint8 sleepReadyBit;

  sleepReadyBit = (uint8)(rxMsgByte & NM_COORD_BIT_SLEEP);
  if( CanNm_GetCoordReadyToSleepState(CANNM_CHANNEL_IDX) != sleepReadyBit )
  {
    if( sleepReadyBit != 0u )
    {
      Nm_CoordReadyToSleepIndication( CANNM_NMTOSYSTEM_CHANNEL_IND );
    }
    else
    {
      Nm_CoordReadyToSleepCancellation( CANNM_NMTOSYSTEM_CHANNEL_IND );
    }
    CanNm_SetCoordReadyToSleepState(CANNM_CHANNEL_IDX, (CanNm_CoordReadyToSleepStateType)sleepReadyBit); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
  }
}
#endif

/**********************************************************************************************************************
  CanNm_TransitionToRepeatMessage
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_TransitionToRepeatMessage( CANNM_CHANNEL_TYPE_ONLY )
{
/* #10 If new state is Repeat Message
 *      Start the Repeat Message Timer
 *      Stop Remote Sleep Timer and clear Remote Sleep Indication flag
 *      If NodeDetection is enabled for this channel
 *       If Repeat Message Indication flag is set
 *        If Repeat Message Indication is enabled for this channel
 *         Clear Repeat Message Indication flag (No interrupt locks required)
 *         Notify NM Interface about Repeat Message Indication.
 */
  CanNm_SetRepeatMsgTimer(CANNM_CHANNEL_IDX, (CanNm_RepeatMsgTimerType)((CanNm_RepeatMsgTimerType)CanNm_GetRepeatMessageTimeOfChannelConfig(CANNM_CHANNEL_IDX) + 1u)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
  CanNm_SetRemoteSleepTimer(CANNM_CHANNEL_IDX, 0u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
  CanNm_SetRemoteSleepIndState(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
#if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
  if( CanNm_IsRepeatMsgBitIndFlag(CANNM_CHANNEL_IDX) )
  {
    CanNm_SetRepeatMsgBitIndFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( CANNM_REPEATMSGINDENABLEDOFCHANNELCONFIG == STD_ON ) /* depends on CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON */
    if( CanNm_IsRepeatMsgIndEnabledOfChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_REPEAT_MSG_IND_ENABLED */
    {
      Nm_RepeatMessageIndication( CANNM_NMTOSYSTEM_CHANNEL_IND );
    }
# endif
  }
#endif

  /* #20 If message transmission is allowed and enabled for this channel
   *      If Immediate Nm transmission feature is enabled
   *      AND Network is actively requested by this node
   *       Trigger an asynchronous transmission of the NM message
   *       Ensure that (ImmediateNmTransmissions - 1) NM messages are sent with faster cycle time
   *      otherwise start message transmission with regular cycle time
   */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
# if ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
  if ( CanNm_GetTxControlState(CANNM_CHANNEL_IDX) == MSG_TX_ENABLED ) /* COV_CANNM_COM_CONTROL_ENABLED */
# endif
  {
# if ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
 //   if( (CanNm_GetImmediateNmTransmissionsOfChannelConfig(CANNM_CHANNEL_IDX) > 0u)
  //    && (CanNm_GetNetworkRestartFlag(CANNM_CHANNEL_IDX) == CANNM_ACTIVE_RESTART) ) /* COV_CANNM_CHECK_IMMEDIATE_TRANSMISSIONS */
	  if( (CanNm_GetImmediateNmTransmissionsOfChannelConfig(CANNM_CHANNEL_IDX) > 0u))//修改这里，不论主动还是被动都要求快发
    {
      CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, 1u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      CanNm_SetImmediateNmMsgCount(CANNM_CHANNEL_IDX, (CanNm_ImmediateNmMsgCountType)CanNm_GetImmediateNmTransmissionsOfChannelConfig(CANNM_CHANNEL_IDX)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    }
    else
# endif
    {
      CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, (CanNm_MsgTimerType)((CanNm_MsgTimerType)CanNm_GetMsgCycleOffsetOfPbChannelConfig(CANNM_CHANNEL_IDX) + 1u)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    }
  }
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) */
}

/**********************************************************************************************************************
  CanNm_TransitionToNetworkMode
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_TransitionToNetworkMode( CANNM_CHANNEL_TYPE_FIRST  CONST(uint8, AUTOMATIC) lastNmState )
{
  /* #10 If RepeatMessage state was entered from BusSleep or PrepareBusSleep state
   *      Reset the RetryFirstMessageRequestFlag to the configured value
   *      Clear Wait Bus Sleep Timer
   *      Restart the Timeout Timer whenever Network Mode is entered.
   *      Notify Nm Interface that the network mode is entered.
   *      If "Active Wakeup Bit Enabled" is configured AND network is actively requested by this node
   *      AND CBV is available
   *       Set Active Wake-up Bit in CBV of Tx Nm message.
   */
  if( lastNmState < NM_STATE_READY_SLEEP ) /* COV_CANNM_CHECK_TRANSITION_TO_NETWORKMODE */
  {
#if ( CANNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
    CanNm_SetRetryFirstMessageRequestFlag(CANNM_CHANNEL_IDX, CanNm_IsRetryFirstMessageRequestOfChannelConfig(CANNM_CHANNEL_IDX)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */ /* PRQA S 4404 */ /* MD_MSR_AutosarBoolean */
#endif

    CanNm_SetWaitBusSleepTimer(CANNM_CHANNEL_IDX, 0u); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    CanNm_SetTimeoutTimer(CANNM_CHANNEL_IDX, (CanNm_TimeoutTimerType)((CanNm_TimeoutTimerType)CanNm_GetTimeoutTimeOfChannelConfig(CANNM_CHANNEL_IDX) + 1u)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    Nm_NetworkMode( CANNM_NMTOSYSTEM_CHANNEL_IND );

#if ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON )
    if( (CanNm_IsActiveWakeUpBitEnabledOfChannelConfig(CANNM_CHANNEL_IDX) )
      && (CanNm_GetNetworkRestartFlag(CANNM_CHANNEL_IDX) == CANNM_ACTIVE_RESTART) ) /* COV_CANNM_ACTIVE_WAKEUP_BIT */
    {
      if( CanNm_IsTxMessageData_CBVUsedOfPbChannelConfig(CANNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_CANNM_CHECK_CBVPOSITION */
      {
         /* ESCAN00064309 */
        CanNm_SetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX), /* SBSW_CANNM_CSL03 */
          (CanNm_TxMessageDataType)(CanNm_GetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)) | CANNM_ACT_WU_BIT_MASK));
      }
    }
#endif
  }
}

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_PnLocal_Init
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_PnLocal_Init( CANNM_CHANNEL_TYPE_ONLY )
{
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  CanNm_SizeOfPnFilterMaskType pnClusterRequestByteEira;
# endif
# if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
  CanNm_PnClusterResetTimerExtEndIdxOfPbChannelConfigType pnClusterRequestByteEra;
# endif
# if defined ( CANNM_PN_CALC_FEATURE_ENABLED )
  uint8_least pnClusterRequestBit;
# endif
  /* #10 Disable Pn Message Filter mechanism (Refer to API CanNm_ConfirmPnAvaiability ) */
  /* The CanNm module's initialization shall cause the PN message filtering to be disabled. */
  CanNm_SetPnMessageFilterEnabled(CANNM_CHANNEL_IDX, FALSE);  /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */ /* PRQA S 2842 */ /* MD_CANNM_Dir4.1 */
  CanNm_SetPnMessageFilterDeactivationIndicated(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */ /* PRQA S 2842 */ /* MD_CANNM_Dir4.1 */

  /* #20 If Partial Networking is enabled on this channel */
  /*  #200 If PnEraCalcEnabled is enabled
   *        Initialize ERA request buffer
   *        Stop all ERA PnClusterResetTimer
   */
  if( CanNm_IsPnEnabledOfPbChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_PN_ENABLED */
  {
# if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
    for( pnClusterRequestByteEra = CanNm_GetPnClusterReqExtStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX);
         pnClusterRequestByteEra < CanNm_GetPnClusterReqExtEndIdxOfPbChannelConfig(CANNM_CHANNEL_IDX);
         pnClusterRequestByteEra++ )
    { /* ESCAN00064309 */

#  if (CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
      /* Runtime Check that CanNm_SetPnClusterReqExtNew array is always written within its defined bounds. */
      if( pnClusterRequestByteEra < CanNm_GetSizeOfPnClusterReqExtNew() ) /* COV_CANNM_CHECK_PNCLUSTERREQEXTNEW */
#  endif
      {
        CanNm_SetPnClusterReqExt(pnClusterRequestByteEra, 0x00u); /* SBSW_CANNM_CSL03 */
        CanNm_SetPnClusterReqExtNew(pnClusterRequestByteEra, 0x00u); /* SBSW_CANNM_PNCLUSTERREQEXTNEW */

        for( pnClusterRequestBit = 0u; pnClusterRequestBit < CANNM_PN_CLUSTERS_PER_BYTE; pnClusterRequestBit++ )
        {
          CanNm_GetPnClusterResetTimerExt(pnClusterRequestByteEra)[pnClusterRequestBit] = 0u; /* SBSW_CANNM_CSL_FILTERMASK_INDEX_PNCLUSTERS_PER_BYTE_INDEX_ACCESS */
        }
      }
#  if (CANNM_DEV_ERROR_REPORT == STD_ON )
      else
      {
        (void)Det_ReportError( CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_INIT, CANNM_E_INVALID_GENDATA );
      }
#  endif
    }
# endif

    /* #210 If PnEiraCalcEnabled is enabled AND if EIRA buffer has not already been initialized.
     *       Initialize EIRA request buffer
     *       Stop all EIRA PnClusterResetTimer
     */
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#  else
    if( ( nmMaxPnChannel == 0xFFu ) || ( nmMaxPnChannel < CANNM_CHANNEL_IDX ) ) /* COV_CANNM_CHECK_MAX_PN_CHANNEL */
#  endif
    {
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#  else
    /* Note:
     * The EIRA buffer is not channel dependent, whereas the PnEnabled configuration switch is.
     * Therefore EIRA buffer needs only to be initialized once if at least one channel has PnEnabled switch ON (checked above).
     */
      nmMaxPnChannel = CANNM_CHANNEL_IDX;
#  endif
      for( pnClusterRequestByteEira = 0u; pnClusterRequestByteEira < CanNm_GetSizeOfPnFilterMask(); pnClusterRequestByteEira++ )
      {
        CanNm_SetPnClusterReq(pnClusterRequestByteEira, 0x00u); /* SBSW_CANNM_CSL02 */
        CanNm_SetPnClusterReqNew(pnClusterRequestByteEira, 0x00u); /* SBSW_CANNM_CSL02 */

        for( pnClusterRequestBit = 0u; pnClusterRequestBit < CANNM_PN_CLUSTERS_PER_BYTE; pnClusterRequestBit++ )
        {
          CanNm_GetPnClusterResetTimer(pnClusterRequestByteEira)[pnClusterRequestBit] = 0u; /* SBSW_CANNM_CSL_FILTERMASK_INDEX_PNCLUSTERS_PER_BYTE_INDEX_ACCESS */
        }
      }
    }
# endif
  }
}
#endif

# if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/**********************************************************************************************************************
  CanNm_DisablePnFilter
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
CANNM_LOCAL FUNC( void, CANNM_CODE ) CanNm_DisablePnFilter( CANNM_CHANNEL_TYPE_ONLY )
{
  if( (CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_BUS_SLEEP) &&
      (CanNm_IsPnMessageFilterDeactivationIndicated(CANNM_CHANNEL_IDX)) )
  {
    CanNm_SetPnMessageFilterEnabled(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    CanNm_SetPnMessageFilterDeactivationIndicated(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
  }
}
# endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
/**********************************************************************************************************************
  CanNm_TriggerTransmission
**********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL FUNC( Std_ReturnType, CANNM_CODE ) CanNm_TriggerTransmission( CANNM_CHANNEL_TYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  PduInfoType    nmPduInfo;
  Std_ReturnType retVal;
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  uint8_least    pnClusterRequestByte;
# endif

  /* #10 Set Pointer variable nmPduInfo to the correct CanNm Tx Message buffer address
   *     Call PduR_CanNmTriggerTransmit to read User Data from the Com IPDU and store it in Tx Message buffer
   *     If PDU Length written by PduR does not match the CanNm's UserData Length
   *      Report Development Error
   */
# if ( CANNM_COM_USER_DATA_SUPPORT == STD_ON )

  nmPduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, CANNM_VAR_NOINIT))
    (CanNm_GetAddrTxMessageData(CanNm_GetTxMessageData_UserDataStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)));
  /* ESCAN00087842 Set SduLength to expected Pdu Length. */
  nmPduInfo.SduLength = (PduLengthType)CanNm_GetTxMessageData_UserDataLengthOfPbChannelConfig(CANNM_CHANNEL_IDX);
  /* SDU Length is set by the upper layer to the number of copied bytes */ /* ESCAN00064309 */
  (void)PduR_CanNmTriggerTransmit( CanNm_GetTxUserDataPduIdOfPbChannelConfig(CANNM_CHANNEL_IDX), &nmPduInfo ); /* SBSW_CANNM_POINTER_PARAM */
#  if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  if( nmPduInfo.SduLength != (PduLengthType)CanNm_GetTxMessageData_UserDataLengthOfPbChannelConfig(CANNM_CHANNEL_IDX) )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_CHANNEL_IDX, CANNM_SID_MAINFUNCTION , CANNM_E_PDUR_TRIGGERTX_ERROR);
  }
#  endif
# endif

  /* #20 If Partial Networking is enabled and PnEiraCalcEnabled is enabled on this channel
   *      Iterate all Pn Cluster Request Bytes
   *       Copy EIRA requests and apply the PN filter mask
   */
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
  if( (CanNm_IsPnEnabledOfPbChannelConfig(CANNM_CHANNEL_IDX))
#  if ( CANNM_ISDEF_PNEIRACALCENABLED == STD_OFF )
     && ( CanNm_IsPnEiraCalcEnabled() )
#  endif
    ) /* COV_CANNM_PN_ENABLED */
  {
    SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_0();
    for( pnClusterRequestByte = 0u; pnClusterRequestByte < CanNm_GetSizeOfPnClusterReqNew(); pnClusterRequestByte++ )
    {
      /* ESCAN00064309 */
      CanNm_SetPnClusterReqNew(pnClusterRequestByte, /* SBSW_CANNM_CSL01 */
        (CanNm_PnClusterReqNewType)(CanNm_GetPnClusterReqNew(pnClusterRequestByte) |
            ((CanNm_GetTxMessageData((CanNm_GetTxMessageDataStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)) + (pnClusterRequestByte + CanNm_GetPnInfoOffset()))) & CanNm_GetPnFilterMask(pnClusterRequestByte))) );
    }
    SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_0();
  }
# endif

  /* #30 Prepare user data for transmission */
  /* #40 Clear local transmission request shortly before actual transmission */
  /* ESCAN00064309 */
  SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_1();
  nmPduInfo.SduDataPtr = (CanNm_GetAddrTxMessageData(CanNm_GetTxMessageDataStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)));
  nmPduInfo.SduLength = (PduLengthType)CanNm_GetTxMessageDataLengthOfPbChannelConfig(CANNM_CHANNEL_IDX);

# if ( CANNM_COM_USER_DATA_SUPPORT == STD_ON ) || ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
  CanNm_SetMsgRequest(CANNM_CHANNEL_IDX, CANNM_NO_TRANSMIT_REQUEST); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# endif

  /* #80 Transmit the NM message. */
  /* #90 If CanIf_Transmit returns E_OK
   *      Set message confirmation flag in order to process it in CanNm_MainFunction
   *      Start Message Timeout Timer (CanNm_TxConfirmation has to be called within this time by the CanIf)
   */
  retVal = CanIf_Transmit( CanNm_GetTxPduIdOfPbChannelConfig(CANNM_CHANNEL_IDX), &nmPduInfo ); /* SBSW_CANNM_POINTER_PARAM */
  SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_1();

  if( retVal == E_OK )
  {
# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_ON )
    /* A flag is used in order to ensure data consistency of the timeout timer. */
    CanNm_SetMsgConfirmationFlag(CANNM_CHANNEL_IDX, TRUE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# else
    /* ESCAN00075773 */
    CanNm_SetMsgTimeoutTimer(CANNM_CHANNEL_IDX, (CanNm_MsgTimeoutTimerType)((CanNm_MsgTimeoutTimerType)CanNm_GetMsgTimeoutTimeOfChannelConfig(CANNM_CHANNEL_IDX) + 1u )); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# endif
  }

  return retVal;
}
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

/**********************************************************************************************************************
  CanNm_LocalInit
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL_INLINE FUNC( void, CANNM_CODE ) CanNm_LocalInit( CANNM_CHANNEL_TYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( CANNM_TXMESSAGEDATA == STD_ON  )
  CanNm_TxMessageDataIterType txUserDataByte;
#endif
#if ( CANNM_RXMESSAGEDATA == STD_ON  )
  CanNm_RxMessageDataIterType rxUserDataByte;
#endif
# if ( CANNM_TXMESSAGEDATA == STD_ON )
#  if ( CANNM_PDUNIDPOSITIONOFCHANNELCONFIG == STD_ON )
  uint8       nidPosition;
#  endif
#  if ( CANNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_ON )
  uint8       cbvPosition;
#  endif
# endif

  /* #10 Initialize all global and local variables */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  /* The bus-communication is initially released. */
  CanNm_SetCommState(CANNM_CHANNEL_IDX, COMM_READY_SLEEP); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

  /* #20 Reset flags */
  CanNm_SetNetworkRestartFlag(CANNM_CHANNEL_IDX, CANNM_NO_RESTART); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
  CanNm_SetMsgIndicationFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#if ( CANNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
  CanNm_SetRetryFirstMessageRequestFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
  CanNm_SetImmediateRestartFailed(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# endif
#endif

#if ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
  CanNm_SetImmediateNmMsgCount(CANNM_CHANNEL_IDX, 0u); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  CanNm_SetMsgConfirmationFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
  CanNm_SetRepeatMsgBitIndFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
  CanNm_SetRepeatMsgReqFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif


  /* #30 Reset Timers. */
  /* All timers have to be initialized since they are processed in every state. */
  CanNm_SetTimeoutTimer(CANNM_CHANNEL_IDX, 0u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
  CanNm_SetWaitBusSleepTimer(CANNM_CHANNEL_IDX, 0u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
  CanNm_SetRepeatMsgTimer(CANNM_CHANNEL_IDX, 0u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */

#if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
  /* Reset Remote Sleep Timer and state. */
  CanNm_SetRemoteSleepTimer(CANNM_CHANNEL_IDX, 0u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
  CanNm_SetRemoteSleepIndState(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
  /* The transmission of NM messages is initially stopped. */
  CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, 0u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */

# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
  /* Timeout Timer is initially stopped */
  CanNm_SetMsgTimeoutTimer(CANNM_CHANNEL_IDX, 0u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# endif
#endif

#if ( CANNM_COM_USER_DATA_SUPPORT == STD_ON ) || ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
  CanNm_SetMsgRequest(CANNM_CHANNEL_IDX, CANNM_NO_TRANSMIT_REQUEST); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
  /* Per default the transmission control status is enabled. */
  CanNm_SetTxControlState(CANNM_CHANNEL_IDX, MSG_TX_ENABLED); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
  CanNm_SetTxControlStateRequest(CANNM_CHANNEL_IDX, MSG_TX_ENABLED); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
  CanNm_SetCoordReadyToSleepState(CANNM_CHANNEL_IDX, CANNM_COORD_ASLEEP_OR_NOT_READY_TO_SLEEP); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
  /* #40 Initialize PN relevant variables */
  CanNm_PnLocal_Init( CANNM_CHANNEL_PARA_ONLY );
#endif

  /* Initialize NM message data. */
  /* ESCAN00064309 */
  /* #50 Initialize User Data with 0xFF */
#if ( CANNM_TXMESSAGEDATA == STD_ON )
  for( txUserDataByte = CanNm_GetTxMessageDataStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX);
       txUserDataByte < CanNm_GetTxMessageDataEndIdxOfPbChannelConfig(CANNM_CHANNEL_IDX);
       txUserDataByte++ )
  {

    CanNm_SetTxMessageData(txUserDataByte, 0xFFu); /* SBSW_CANNM_CSL03 */
  }
#endif

#if ( CANNM_RXMESSAGEDATA == STD_ON )
  for( rxUserDataByte = CanNm_GetRxMessageDataStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX);
       rxUserDataByte < CanNm_GetRxMessageDataEndIdxOfPbChannelConfig(CANNM_CHANNEL_IDX);
       rxUserDataByte++ )
  {
    CanNm_SetRxMessageData(rxUserDataByte, 0xFFu); /* SBSW_CANNM_CSL03 */
  }
#endif

#if ( CANNM_TXMESSAGEDATA == STD_ON ) || ( CANNM_RXMESSAGEDATA == STD_ON )
  /* The reserved bits are set to 0 */
  /* #60 If Node Id Enabled is configured and 'Pdu Nid Position' is configured to Byte0 or Byte1
   *      Initialize Source Node Identifier Byte to the configured Node Id
   *     otherwise initialize the reserved Byte to zero
   */
# if ( CANNM_TXMESSAGEDATA == STD_ON )
#  if ( CANNM_PDUNIDPOSITIONOFCHANNELCONFIG == STD_ON )
  if( CanNm_GetPduNidPositionOfChannelConfig(CANNM_CHANNEL_IDX) != CANNM_PDU_OFF ) /* CANNM_CHECK_NIDPOSITION */ /* COV_CANNM_CHECK_NIDPOSITION */
  {
    nidPosition = (uint8)(CanNm_GetTxMessageData_NIDIdxOfPbChannelConfig(CANNM_CHANNEL_IDX));
      /* Source Node Identifier */
#   if ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON )
    if (CanNm_IsNodeIdEnabledOfChannelConfig(CANNM_CHANNEL_IDX)) /* COV_CANNM_NODE_ID_ENABLED */
    {
      CanNm_SetTxMessageData(nidPosition, (CanNm_TxMessageDataType)CanNm_GetNodeIdOfPbChannelConfig(CANNM_CHANNEL_IDX)); /* SBSW_CANNM_CSL03 */
    }
    else
#   endif
    {
      CanNm_SetTxMessageData(nidPosition, 0x00u); /* SBSW_CANNM_CSL03 */
    }
  }
#  endif

  /* #70 If 'Pn Enabled' is configured and 'Pdu Cbv Position' is configured to Byte0 or Byte1
   *      Initialize CBV Byte with CRI bit set
   *     otherwise initialize CBV to zero
   */
#  if ( CANNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_ON )
  if( CanNm_IsTxMessageData_CBVUsedOfPbChannelConfig(CANNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_CANNM_CHECK_CBVPOSITION */
  {
    cbvPosition = (uint8)(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX));
#   if ( CANNM_PNENABLEDOFPBCHANNELCONFIG == STD_ON )
    if( CanNm_IsPnEnabledOfPbChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_PN_ENABLED */
    {
      CanNm_SetTxMessageData(cbvPosition, CANNM_CRI_BIT_MASK); /* SBSW_CANNM_CSL03 */
    }
    else
#   endif
    {
      /* ControlBitVector = 0x00, RepeatMessageBit = FALSE */
      CanNm_SetTxMessageData(cbvPosition, 0x00u); /* SBSW_CANNM_CSL03 */
    }
  }
#  endif
# endif
#endif

  /* #90 Set NmState to default state Bus Sleep without notification of upper layer */
  /* State machine initialization without notification. */
  CanNm_SetNmState(CANNM_CHANNEL_IDX, NM_STATE_BUS_SLEEP); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */

}  /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */


/**********************************************************************************************************************
  CanNm_StateTransition
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
CANNM_LOCAL FUNC( void, CANNM_CODE ) CanNm_StateTransition( CANNM_CHANNEL_TYPE_FIRST
                                                            CONST( Nm_StateType, AUTOMATIC ) nextNmState )
{
  /* ----- Local Variables ---------------------------------------------- */
#if( CANNM_ERRORWAITBUSSLEEPTIMEOFCHANNELCONFIG == STD_ON )
  uint8 nmStatusPtr = 0u;
#endif
  Nm_StateType  lastNmState;   /* Last state of the state machine. */
#if ( CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
  boolean additionalTransmissionRequired = FALSE; /* ESCAN00065303 */
#endif

  /* #10 Update Nm state */
  lastNmState = CanNm_GetNmState(CANNM_CHANNEL_IDX);
  CanNm_SetNmState(CANNM_CHANNEL_IDX, nextNmState);  /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */

  switch (nextNmState)
  {
    /* -------------------- transition to Bus Sleep -------------------- */
    /* #100 If new state is Bus Sleep
     *       Notify Nm Interface that BusSleep mode has been entered.
     *       Disable the PN message filtering.
     */
  case NM_STATE_BUS_SLEEP:
    Nm_BusSleepMode( CANNM_NMTOSYSTEM_CHANNEL_IND );
#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
    CanNm_SetPnMessageFilterDeactivationIndicated(CANNM_CHANNEL_IDX, TRUE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
    break;

    /* -------------------- transition to Prepare Bus Sleep -------------------- */
    /* #200 If new state is Prepare Bus Sleep
     *       Notify Nm Interface that PrepareBusSleep mode has been entered.
     *       If NmOsek is in Limp Home and ErrorWaitBusSleep Time is greater zero
     *        Start WaitBusSleepTimer with ErrorWaitBusSleep time
     *       otherwise
     *        Start the WaitBusSleepTimer with WaitBusSleep time
     *       If ActiveWakeupBitEnabled is set and CBV is available
     *        Reset Active Wake-up Bit in CBV.
     *       Clear CoordReadyToSleepState. Notification handling is done in CanNm_RxIndication
     */
  case NM_STATE_PREPARE_BUS_SLEEP:
    Nm_PrepareBusSleepMode( CANNM_NMTOSYSTEM_CHANNEL_IND );
#if( CANNM_ERRORWAITBUSSLEEPTIMEOFCHANNELCONFIG == STD_ON )
    if( CanNm_GetErrorWaitBusSleepTimeOfChannelConfig(CANNM_CHANNEL_IDX) > 0u )
    {
      (void)NmOsek_GetStatus(CANNM_NMTOSYSTEM_CHANNEL_IND, &nmStatusPtr ); /* SBSW_CANNM_POINTER_PARAM */
      if( (nmStatusPtr & CANNM_NMOSEK_LIMP_HOME_FLAG_MASK) == CANNM_NMOSEK_LIMP_HOME_FLAG_MASK )
      {
        CanNm_SetWaitBusSleepTimer(CANNM_CHANNEL_IDX, (CanNm_WaitBusSleepTimerType)CanNm_GetErrorWaitBusSleepTimeOfChannelConfig(CANNM_CHANNEL_IDX) ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      }
      else
      {
        CanNm_SetWaitBusSleepTimer(CANNM_CHANNEL_IDX, (CanNm_WaitBusSleepTimerType)CanNm_GetWaitBusSleepTimeOfChannelConfig(CANNM_CHANNEL_IDX) ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      }
    }
    else
#endif
    {
      CanNm_SetWaitBusSleepTimer(CANNM_CHANNEL_IDX, (CanNm_WaitBusSleepTimerType)CanNm_GetWaitBusSleepTimeOfChannelConfig(CANNM_CHANNEL_IDX) ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    }

#if ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON )
    /* ESCAN00064309 */
    if( CanNm_IsActiveWakeUpBitEnabledOfChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_ACTIVE_WAKEUP_BIT */
    {CanNm_TransitionToRepeatMessage
      if( CanNm_IsTxMessageData_CBVUsedOfPbChannelConfig(CANNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_CANNM_CHECK_CBVPOSITION */
      {
        CanNm_SetTxMessageData((CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)), /* SBSW_CANNM_CSL03 */
          (CanNm_TxMessageDataType)(CanNm_GetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)) & CANNM_ACT_WU_BIT_INV_MASK));
      }
    }
#endif

#if ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
    /* No need to notify Nm about Ready To Sleep Cancellation, would be done by Nm_NetworkMode */
    CanNm_SetCoordReadyToSleepState(CANNM_CHANNEL_IDX, CANNM_COORD_ASLEEP_OR_NOT_READY_TO_SLEEP); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
    break;

    /* -------------------- transition to Ready Sleep -------------------- */
    /* #300 If new state is Ready Sleep
     *       Stop NM message timer.
     *       Reset Remote Sleep Timer (Normal to Ready Only)
     *       If NodeDetection is enabled for this channel
     *        If CBV is available:
     *         Clear the repeat message bit in CBV (no interrupt locks required, access on Task level only)
     *       Stop transmission of Nm Messages with faster cycle time (Immediate Nm transmission)
     *       Set RetryFirstMessageRequestFlag to False
     */
  case NM_STATE_READY_SLEEP:
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
    CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, 0u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
#if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
    CanNm_SetRemoteSleepTimer(CANNM_CHANNEL_IDX, 0u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
#if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
    if (CanNm_IsNodeDetectionEnabledOfChannelConfig(CANNM_CHANNEL_IDX)) /* COV_CANNM_NODE_DETECTION_ENABLED */
    {
      if( CanNm_IsTxMessageData_CBVUsedOfPbChannelConfig(CANNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_CANNM_CHECK_CBVPOSITION */
      {
        /* ESCAN00064309 */
        CanNm_SetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX), /* SBSW_CANNM_CSL03 */
          (CanNm_TxMessageDataType)(CanNm_GetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)) & CANNM_REPEAT_MSG_BIT_INV_MASK));
      }
    }
#endif
#if ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
    CanNm_SetImmediateNmMsgCount(CANNM_CHANNEL_IDX, 0u); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
#if ( CANNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
    CanNm_SetRetryFirstMessageRequestFlag(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
#endif
    break;

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
    /* -------------------- transition to Normal Operation -------------------- */
    /* #400 If new state is Normal Operation
     *       If message transmission is allowed for this channel
     *        Restart Remote Sleep Timer and clear Remote Sleep Indication flag
     *       If lastState was ReadySleep AND message transmission is allowed for this channel
     *        Trigger asynchronous transmission of the NM message.
     *       In any other state AND if NodeDetection is enabled for this channel AND if CBV is available
     *        Clear the repeat message bit in TxMessageData buffer
     */
  case NM_STATE_NORMAL_OPERATION:
# if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#  if ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
    if ( CanNm_GetTxControlState(CANNM_CHANNEL_IDX) == MSG_TX_ENABLED )
#  endif
    {
      CanNm_SetRemoteSleepTimer(CANNM_CHANNEL_IDX, (CanNm_RemoteSleepTimerType)((CanNm_RemoteSleepTimerType)CanNm_GetRemoteSleepIndTimeOfChannelConfig(CANNM_CHANNEL_IDX) + 1u )); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      CanNm_SetRemoteSleepIndState(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    }
# endif
    if( lastNmState == NM_STATE_READY_SLEEP )
    {
# if ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
      if ( CanNm_GetTxControlState(CANNM_CHANNEL_IDX) == MSG_TX_ENABLED )
# endif
      {
        CanNm_SetMsgTimer(CANNM_CHANNEL_IDX, 1u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      }
    }
    else
    {
# if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) && ( CANNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_ON )
      if ( CanNm_IsNodeDetectionEnabledOfChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_NODE_DETECTION_ENABLED */
      {
        if ( CanNm_IsTxMessageData_CBVUsedOfPbChannelConfig(CANNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_CANNM_CHECK_CBVPOSITION */
        {
          /* ESCAN00064309 */
          CanNm_SetTxMessageData((CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)), /* SBSW_CANNM_CSL03 */
            (CanNm_TxMessageDataType)(CanNm_GetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)) & CANNM_REPEAT_MSG_BIT_INV_MASK));
        }
      }
# endif
    }
    break;
#endif
    /* -------------------- transition to Repeat Message -------------------- */
  default:
    /* #500 Transition to Repeat Message */
    CanNm_TransitionToRepeatMessage( CANNM_CHANNEL_PARA_ONLY );

    /* #510 Additional actions when entering Network Mode */
    CanNm_TransitionToNetworkMode( CANNM_CHANNEL_PARA_FIRST  lastNmState );

    /* #520 If ImmediateRestartEnabled feature is active for this channel
     *      AND Repeat Message state is entered from PrepareBusSleep state due to an internal communication request and
     *       Trigger transmission of an asynchronous Nm message right after notification of new state has been done below.
     *       Clear NetworkRestartFlag
     */
#if ( CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
    /* If Network Mode has been entered from Prepare Bus-Sleep Mode due to a network request,
       an asynchronous NM message transmission is requested as soon as Network Mode has been entered */
    if (CanNm_IsImmediateRestartEnabledOfChannelConfig(CANNM_CHANNEL_IDX)) /* COV_CANNM_IMMEDIATE_RESTART_ENABLED */
    {
      if( (lastNmState == NM_STATE_PREPARE_BUS_SLEEP) &&
          (CanNm_GetMsgTimer(CANNM_CHANNEL_IDX) > 1u) &&
          (CanNm_GetNetworkRestartFlag(CANNM_CHANNEL_IDX) == CANNM_ACTIVE_RESTART) ) /* COV_CANNM_MSG_TIMER_GT_ZERO */ /* ESCAN00065303 */
      {
        additionalTransmissionRequired = TRUE;
      }
    }
    
#endif /* ( CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON ) */

    CanNm_SetNetworkRestartFlag(CANNM_CHANNEL_IDX, CANNM_NO_RESTART); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */

    break;
  }

#if ( CANNM_STATE_CHANGE_IND_ENABLED == STD_ON )
  /* #20 Notify Nm Interface that state has changed. */
  if ( lastNmState != nextNmState ) /* COV_CANNM_NO_PN_HANDLE_MULTIPLE_NETWORK_REQUESTS */
  {
    Nm_StateChangeNotification( CANNM_NMTOSYSTEM_CHANNEL_IND, lastNmState, nextNmState );
  }
#endif

#if ( CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
  /* #30 If Immediate Restart is enabled for this channel
   *      If transmission of asynchronous Nm message is required
   *       Call local function CanNm_TriggerTransmission in order to transmit an Nm message immediately
   *       If message transmission failed AND Retry First Message Request is enabled for this channel
   *        Reset the Message Timer to 2
   *        Set ImmediateRestartFailed TRUE
   *       If message transmission succeeded
   *        Clear RetryFirstMessageRequest Flag
   */

  if( additionalTransmissionRequired == TRUE )
  {
    Std_ReturnType retVal;
    /* Request the transmission of the asynchronous NM message in Network Mode. */
    /* Call CanNm_TriggerTransmission after Nm_StateChangeNotification because the user data might have been
      * changed inside the Nm_StateChangeNotification call */ /* ESCAN00065302 */
    retVal = CanNm_TriggerTransmission( CANNM_CHANNEL_PARA_ONLY );

# if ( CANNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON )
    if (CanNm_IsRetryFirstMessageRequestFlag(CANNM_CHANNEL_IDX)) /* COV_CANNM_RETRY_FIRST_MESSAGE_REQUEST_ENABLED */
    {
      if ( retVal == E_NOT_OK )
      {
        /* MsgTimer = 2 since the MsgTimer Handling is done later in the main function and a transmit request was already
         * processed during the current main function cycle.
         */
        CanNm_SetMsgTimer( CANNM_CHANNEL_IDX, 2u ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
        CanNm_SetImmediateRestartFailed( CANNM_CHANNEL_IDX, TRUE ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      }
      else
      {
        CanNm_SetRetryFirstMessageRequestFlag( CANNM_CHANNEL_IDX, FALSE ); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      }
    }
# endif

    CANNM_DUMMY_STATEMENT( retVal ); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  }

#endif /* ( CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON ) */
}  /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * CanNm_Init
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
/* ESCAN00071960 */
FUNC( void, CANNM_CODE ) CanNm_Init( CONSTP2CONST( CanNm_ConfigType, AUTOMATIC, CANNM_INIT_DATA ) cannmConfigPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8             errorId = CANNM_E_NO_ERROR;
  uint8             ecumErrorId = CANNM_E_ECUM_NO_ERROR;
#if ( CANNM_DEV_ERROR_DETECT == STD_ON ) && ( CANNM_PBCHANNELCONFIG == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  uint8             sizeOfChannelConfig;
#endif
  NetworkHandleType channel;


  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_INIT )

#if ( CANNM_USE_INIT_POINTER == STD_ON )
  /* Use selected configuration */
  /* #10 Store selected configuration from 'cannmConfigPtr' */
  CanNm_ConfigDataPtr = cannmConfigPtr;
#else
  CANNM_DUMMY_STATEMENT_CONST(cannmConfigPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
#if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #20 Check that module is not initialized */
  if( CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_ALREADY_INITIALIZED;
  }
  else
#endif /* ( CANNM_DEV_ERROR_DETECT == STD_ON ) */
#if ( CANNM_USE_INIT_POINTER == STD_ON )
  /* #30 Check that configuration parameter 'cannmConfigPtr' is not NULL */
  if( cannmConfigPtr == NULL_PTR )
  {
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
    errorId = CANNM_E_INIT_FAILED;
# endif
# if ( CANNM_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
    ecumErrorId = ECUM_BSWERROR_NULLPTR;
# endif
  }
  else
#endif
#if ( CANNM_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
  /* #40 Check Generator Compatibility Version */
  if( CanNm_GetGeneratorCompatibilityVersion() != (uint16)CANNM_EXPECTED_GENERATOR_COMPATIBILITY_VERSION )
  {
    ecumErrorId = ECUM_BSWERROR_COMPATIBILITYVERSION;
  }
  else
#endif
#if ( CANNM_FINALMAGICNUMBER == STD_ON )
  /* #50 Check Magic Number */
  if( CanNm_GetFinalMagicNumber() != CANNM_FINAL_MAGIC_NUMBER )
  {
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
    errorId = CANNM_E_INIT_FAILED;
# endif
  }
  else
#endif
  /* ESCAN00089823 */
  {
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) && ( CANNM_PBCHANNELCONFIG == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
    sizeOfChannelConfig = CanNm_GetSizeOfChannelConfig();

    if( sizeOfChannelConfig != CanNm_GetSizeOfPbChannelConfig() ) /* PRQA S 2992, 2996 */ /* MD_CANNM_Rule14.3, MD_CANNM_Rule2.2 */ /* COV_CANNM_INVALID_GENDATA */
    {
      errorId = CANNM_E_INVALID_GENDATA; /* PRQA S 2880 */ /* MD_CANNM_Rule2.1 */
    }
    else
# endif
    {
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#else
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
      nmMaxPnChannel = 0xFFu;
# endif
#endif
      for( channel = 0u; channel < CanNm_GetSizeOfChannelConfig(); channel++ )
      {
        /* #500 Call CanNm_LocalInit to initialize all global and local variables */
        CanNm_LocalInit( CANNM_CHANNEL_PARA_ONLY );
      }
#if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
      /* #510 Set global state to initialized */
      CanNm_SetModuleInitialized(TRUE); /* SBSW_CANNM_CSL_VAR_ACCESS */
#endif
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( CANNM_DEV_ERROR_REPORT == STD_ON ) /* ESCAN00064309 */
  /* #60 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_INIT , errorId);
  }
#else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  /* ESCAN00064309 */
#if ( CANNM_USE_ECUM_BSW_ERROR_HOOK == STD_ON )
  if( ecumErrorId != CANNM_E_ECUM_NO_ERROR )
  {
    (void)EcuM_BswErrorHook(CANNM_MODULE_ID, ecumErrorId);
  }
#else
  CANNM_DUMMY_STATEMENT(ecumErrorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_INIT )
} /* PRQA S 6010,6030,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STMIF */

/***********************************************************************************************************************
 *  CanNm_PassiveStartUp
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_PassiveStartUp( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = CANNM_E_NO_ERROR;

#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#else
  NetworkHandleType channel;
#endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_PASSIVESTARTUP )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
#if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
# else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
# endif
  else
#endif
  /* #20 If module is initialized and parameter checks are passed */
  {
#if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
#endif
    /* #200 If NmState is BusSleep or PrepareBusSleep
     *       Deactivate Pn Message Filtering (Bus Sleep only)
     *       If network was not actively requested
     *        Set NetworkRestartFlag to passive restart for further handling in main function
     */
    if( (CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_BUS_SLEEP) ||
        (CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_PREPARE_BUS_SLEEP) )
    {
# if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
      CanNm_DisablePnFilter(CANNM_CHANNEL_PARA_ONLY); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# endif

      if( CanNm_GetNetworkRestartFlag(CANNM_CHANNEL_IDX) == CANNM_NO_RESTART )
      {
        CanNm_SetNetworkRestartFlag(CANNM_CHANNEL_IDX, CANNM_PASSIVE_RESTART); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
      }
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_PASSIVESTARTUP , errorId);
  }
#else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_PASSIVESTARTUP )
  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
/***********************************************************************************************************************
 *  CanNm_NetworkRequest
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_NetworkRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8          errorId = CANNM_E_NO_ERROR;

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_NETWORKREQUEST )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* Request network */
    /* #200 Set internal communication flag to NormalOperation
    *       Deactivate Pn Message Filtering
     *      If no internal request is set AND ( CanNm is in state BusSleep or PrepareBusSleep OR ( <Pn Enabled> AND <Pn Handle Multiple Network Requests> is configured ) )
     *       Set NetworkRestartFlag to active restart for further handling in main function
     */
    CanNm_SetCommState(CANNM_CHANNEL_IDX, COMM_NORMAL_OPERATION); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */

# if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
    CanNm_DisablePnFilter(CANNM_CHANNEL_PARA_ONLY); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# endif

    /* Ensure Start-Up */
    if( (CanNm_GetNetworkRestartFlag(CANNM_CHANNEL_IDX) == CANNM_NO_RESTART) &&
        ( (CanNm_GetNmState(CANNM_CHANNEL_IDX) < NM_STATE_READY_SLEEP)
    /* Check is not done if PnHandleMultipleRequests = 0 on all channels ( A && 0 = 0 ) */
# if ( CANNM_PN_FEATURE_ENABLED == STD_ON ) && ( CANNM_PNHANDLEMULTIPLENETWORKREQUESTOFCHANNELCONFIG == STD_ON )
      /* Change to Network Mode if Multiple Network Request is set to true */
      || ( (CanNm_IsPnEnabledOfPbChannelConfig(CANNM_CHANNEL_IDX)) &&
           (CanNm_IsPnHandleMultipleNetworkRequestOfChannelConfig(CANNM_CHANNEL_IDX))
         )
# endif
         ) ) /* COV_CANNM_PN_ENABLED */
    {
      CanNm_SetNetworkRestartFlag(CANNM_CHANNEL_IDX, CANNM_ACTIVE_RESTART); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    }
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_NETWORKREQUEST , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_NETWORKREQUEST )
  return retVal;
}


/***********************************************************************************************************************
 *  CanNm_NetworkRelease
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_NetworkRelease( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8           errorId = CANNM_E_NO_ERROR;

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_NETWORKRELEASE )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* #200 Set internal communication flag to ReadySleep */
    CanNm_SetCommState(CANNM_CHANNEL_IDX, COMM_READY_SLEEP); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_NETWORKRELEASE , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_NETWORKRELEASE )
  return retVal;
}
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

/***********************************************************************************************************************
 *  CanNm_GetState
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_GetState( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                   CONSTP2VAR( Nm_StateType, AUTOMATIC, CANNM_APPL_VAR ) nmStatePtr,
                                                   CONSTP2VAR( Nm_ModeType, AUTOMATIC, CANNM_APPL_VAR ) nmModePtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8          errorId = CANNM_E_NO_ERROR;

#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#else
  NetworkHandleType channel;
#endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_GETSTATE )

  /* ----- Development Error Checks ------------------------------------- */
#if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmStatePtr' */
  else if( nmStatePtr == NULL_PTR )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  /* Check parameter 'nmModePtr' */
  else if( nmModePtr == NULL_PTR )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  else
#endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* #200 Return current CanNm state in passed <nmStatePtr> parameter */
    *nmStatePtr = CanNm_GetNmState(CANNM_CHANNEL_IDX); /* SBSW_CANNM_GETSTATE */
    /* Set mode according to the current state */
    /* #210 If CanNm state is BusSleep
     *       Return 'Bus Sleep Mode' in passed <nmModePtr> parameter
     */
    if( CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_BUS_SLEEP )                     /* Bus Sleep */
    {
      *nmModePtr = NM_MODE_BUS_SLEEP; /* SBSW_CANNM_GETSTATE */
    }
    /* #220 If CanNm state is PrepareBusSleep
     *       Return 'Prepare Bus Sleep Mode' in passed <nmModePtr> parameter
     */
    else if( CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_PREPARE_BUS_SLEEP )    /* Prepare Sleep */
    {
      *nmModePtr = NM_MODE_PREPARE_BUS_SLEEP; /* SBSW_CANNM_GETSTATE */
    }
    /* #230 in all other cases
     *       Return 'Network Mode' to passed <nmModePtr> parameter
     */
    else                                          /* Ready Sleep, Normal Operation, Repeat Message */
    {
      *nmModePtr = NM_MODE_NETWORK; /* SBSW_CANNM_GETSTATE */
    }
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_GETSTATE , errorId);
  }
#else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_GETSTATE )
  return retVal;
}  /* PRQA S 6080,6030 */ /* MD_MSR_STMIF,MD_MSR_STCYC */

#if ( CANNM_USER_DATA_ENABLED == STD_ON )
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_COM_USER_DATA_SUPPORT == STD_OFF )
/***********************************************************************************************************************
 *  CanNm_SetUserData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_SetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                      CONSTP2CONST( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmUserDataPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8  errorId = CANNM_E_NO_ERROR;
  CanNm_TxMessageDataIterType  txMesssageDataByte;
  CanNm_TxMessageDataIterType  userDataByte;

#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  else
  NetworkHandleType channel;
#  endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_SETUSERDATA )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
#  if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#   if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#   else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#   endif
  /* Check parameter 'nmUserDataPtr' */
  else if( nmUserDataPtr == NULL_PTR )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  else
#  endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_2();
    /* #200 Iterate all user data bytes
     *       Write user data into Tx Message Data buffer. Content is transmitted in the next Nm message.
     */
    /*
     * nmUserDataPtr is a zero based list. Iteration is done from 0u
     * TxMessageData is a indirected list.
     */
    /* PRQA S 2463, 3418 3 */ /* MD_CANNM_Rule14.2, MD_CANNM_Rule12.3 */
    for( txMesssageDataByte = CanNm_GetTxMessageData_UserDataStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX), userDataByte = 0u;
         txMesssageDataByte < CanNm_GetTxMessageData_UserDataEndIdxOfPbChannelConfig(CANNM_CHANNEL_IDX);
         txMesssageDataByte++, userDataByte++ )
    {
      /* ESCAN00064309 */
      CanNm_SetTxMessageData(txMesssageDataByte, (CanNm_TxMessageDataType)nmUserDataPtr[userDataByte]); /* SBSW_CANNM_CSL03 */
    }
    SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_2();
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
#  if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_SETUSERDATA , errorId);
  }
#  else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_SETUSERDATA )
  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_COM_USER_DATA_SUPPORT == STD_OFF ) */

/***********************************************************************************************************************
 *  CanNm_GetUserData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_GetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                      CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmUserDataPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8                         errorId = CANNM_E_NO_ERROR;
  CanNm_RxMessageDataIterType   userDataByte;

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_GETUSERDATA )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmUserDataPtr' */
  else if( nmUserDataPtr == NULL_PTR )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_5();
    /* #200 Iterate all user data bytes
     *       Return user data from last received Nm message.
     */
    for( userDataByte = 0u; userDataByte < CanNm_GetRxMessageData_UserDataLengthOfPbChannelConfig(CANNM_CHANNEL_IDX); userDataByte++ )
    {
      nmUserDataPtr[userDataByte] = CanNm_GetRxMessageData(CanNm_GetRxMessageData_UserDataStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX) + userDataByte); /* SBSW_CANNM_GETUSERDATA */ /* ESCAN00064309 */
    }
    SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_5();
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_GETUSERDATA , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_GETUSERDATA )
  return retVal;
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif  /* ( CANNM_USER_DATA_ENABLED == STD_ON ) */


#if ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  CanNm_GetNodeIdentifier
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_GetNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                            CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmNodeIdPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = CANNM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_GETNODEIDENTIFIER )

# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmNodeIdPtr' */
  else if( (nmNodeIdPtr) == NULL_PTR )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ----- Implementation ----------------------------------------------- */
    /* #200 If NodeIdentifier position is configured to Byte0 or Byte1
     *       If Node Identifier is enabled for this channel
     *        Return the current Node Identifier from the last received NM message
     */
    if( CanNm_GetPduNidPositionOfChannelConfig(CANNM_CHANNEL_IDX) != CANNM_PDU_OFF ) /* COV_CANNM_CHECK_NIDPOSITION */
    {
      /* ESCAN00064309 */
      if (CanNm_IsNodeIdEnabledOfChannelConfig(CANNM_CHANNEL_IDX)) /* COV_CANNM_NODE_ID_ENABLED */
      {
        *nmNodeIdPtr = CanNm_GetRxMessageData(CanNm_GetRxMessageData_NIDIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)); /* SBSW_CANNM_GETLOCALNODEIDENTIFIER */
        retVal = E_OK;
      }
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_GETNODEIDENTIFIER , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_GETNODEIDENTIFIER )

  return retVal;
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
 *  CanNm_GetLocalNodeIdentifier
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_GetLocalNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                                 CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR )
                                                                 nmNodeIdPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = CANNM_E_NO_ERROR;

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_GETLOCALNODEIDENTIFIER )

  /* ----- Development Error Checks ------------------------------------- */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmNodeIdPtr' */
  else if( nmNodeIdPtr == NULL_PTR )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ----- Implementation ----------------------------------------------- */
    /* #200 If Node Identifier is enabled for this channel
     *       Return Node ID from configuration. */
    if ( CanNm_IsNodeIdEnabledOfChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_NODE_ID_ENABLED */
    {
      *nmNodeIdPtr = CanNm_GetNodeIdOfPbChannelConfig(CANNM_CHANNEL_IDX); /* SBSW_CANNM_GETLOCALNODEIDENTIFIER */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_GETLOCALNODEIDENTIFIER , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_GETLOCALNODEIDENTIFIER )

  return retVal;
}
#endif /* ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) */

#if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  CanNm_RepeatMessageRequest
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_RepeatMessageRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = CANNM_E_NO_ERROR;

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_REPEATMESSAGEREQUEST )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ----- Implementation ----------------------------------------------- */
    /* #200 If Node Detection is enabled for this channel
     *       If current state is ReadySleep or NormalOperation.
     *        Request Transition to Repeat Message State.
     */
    if ( CanNm_IsNodeDetectionEnabledOfChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_NODE_DETECTION_ENABLED */
    {
      if( ( CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_READY_SLEEP ) ||
        ( CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION ) )
      {
        CanNm_SetRepeatMsgReqFlag(CANNM_CHANNEL_IDX, TRUE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
        retVal =  E_OK;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_REPEATMESSAGEREQUEST , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_REPEATMESSAGEREQUEST )

  return retVal;
}
#endif /* ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) */

#if ( ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) || \
      ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ))
/***********************************************************************************************************************
 *  CanNm_GetPduData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_GetPduData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                     CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmPduDataPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8                         errorId = CANNM_E_NO_ERROR;
  CanNm_RxMessageDataIterType   msgDataByte;

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_GETPDUDATA )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmPduDataPtr' */
  else if( (nmPduDataPtr) == NULL_PTR )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif

    /* ----- Implementation ----------------------------------------------- */
    
    /* #200 If Node Id is enabled for this channel
     *       Iterate all data bytes of last received Nm message
     *        Return current PDU data
     */

# if ( CANNM_USER_DATA_ENABLED == STD_OFF )
    if ( CanNm_IsNodeIdEnabledOfChannelConfig(CANNM_CHANNEL_IDX) )
# endif
    {
      SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_5();
      
      for( msgDataByte = 0u; msgDataByte < CanNm_GetRxMessageDataLengthOfPbChannelConfig(CANNM_CHANNEL_IDX); msgDataByte++ )
      {
        /* ESCAN00064309 */
        nmPduDataPtr[msgDataByte] = CanNm_GetRxMessageData((CanNm_GetRxMessageDataStartIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)) + (msgDataByte)); /* SBSW_CANNM_GETPDUDATA */
      }
      SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_5();
      retVal = E_OK;
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_GETPDUDATA , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_GETPDUDATA )

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) || ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) ||
          ( CANNM_USER_DATA_ENABLED == STD_ON ) */

#if ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  CanNm_RequestBusSynchronization
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_RequestBusSynchronization( CONST( NetworkHandleType, AUTOMATIC )
                                                                    nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = CANNM_E_NO_ERROR;

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_REQUESTBUSSYNCHRONIZATION )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ----- Implementation ----------------------------------------------- */
    /* Trigger Transmission */
    /* #200 If NmState is not BusSleep AND not PrepareBusSleep AND if message transmission is allowed on this channel.
     *       Call CanNm_TriggerTransmission to request an asynchronous NM message transmission
     */
    if( ( CanNm_GetNmState(CANNM_CHANNEL_IDX) != NM_STATE_BUS_SLEEP ) &&
        ( CanNm_GetNmState(CANNM_CHANNEL_IDX) != NM_STATE_PREPARE_BUS_SLEEP )
# if ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
          && ( CanNm_GetTxControlState(CANNM_CHANNEL_IDX) == MSG_TX_ENABLED )
# endif
       )
    {
      retVal = CanNm_TriggerTransmission( CANNM_CHANNEL_PARA_ONLY );
    }
  }
  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_REQUESTBUSSYNCHRONIZATION , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_REQUESTBUSSYNCHRONIZATION )

  return retVal;
}
#endif /* ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON ) */

#if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  CanNm_CheckRemoteSleepIndication
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_CheckRemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC )
                                                                     nmChannelHandle,
                                                                     CONSTP2VAR( boolean, AUTOMATIC, CANNM_APPL_VAR )
                                                                     nmRemoteSleepIndPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = CANNM_E_NO_ERROR;

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_CHECKREMOTESLEEPIND )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmRemoteSleepIndPtr' */
  else if( nmRemoteSleepIndPtr == NULL_PTR )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ----- Implementation ----------------------------------------------- */
    /* Check Remote Sleep Indication may only be requested in Ready Sleep State and during Normal Operation. */
    /* #200 If state is Ready Sleep or Normal Operation
     *       Return current Remote Sleep Indication state
     */
    if( (CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_READY_SLEEP) ||
        (CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION) )
    {
      /* Provide information about current status of remote sleep indication */
      *nmRemoteSleepIndPtr = (boolean)CanNm_IsRemoteSleepIndState(CANNM_CHANNEL_IDX); /* SBSW_CANNM_CHECKREMOTESLEEPINDICATION */ /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_CHECKREMOTESLEEPIND , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_CHECKREMOTESLEEPIND )

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) */


#if ( CANNM_VERSION_INFO_API == STD_ON )
/***********************************************************************************************************************
 *  CanNm_GetVersionInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( void, CANNM_CODE ) CanNm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CANNM_APPL_VAR ) versioninfo)
{

  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANNM_E_NO_ERROR;

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_GETVERSIONINFO )

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that module is initialized */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* Check parameter 'versioninfo' */
  if( versioninfo == NULL_PTR )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If parameter checks are successful */
  {
    /* Provide version information */
    /* #200 Return vendor ID, module ID and version data */
    versioninfo->vendorID = (uint16)CANNM_VENDOR_ID; /* SBSW_CANNM_GETVERSIONINFO */
    versioninfo->moduleID = (uint8)CANNM_MODULE_ID; /* SBSW_CANNM_GETVERSIONINFO */

    versioninfo->sw_major_version = (uint8)CANNM_SW_MAJOR_VERSION; /* SBSW_CANNM_GETVERSIONINFO */
    versioninfo->sw_minor_version = (uint8)CANNM_SW_MINOR_VERSION; /* SBSW_CANNM_GETVERSIONINFO */
    versioninfo->sw_patch_version = (uint8)CANNM_SW_PATCH_VERSION; /* SBSW_CANNM_GETVERSIONINFO */
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_GETVERSIONINFO , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_GETVERSIONINFO )
}
#endif /* ( CANNM_VERSION_INFO_API == STD_ON ) */

#if ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  CanNm_EnableCommunication
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_EnableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  uint8          errorId = CANNM_E_NO_ERROR;

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED ) || ( CANNM_PASSIVE_MODE_ENABLED == STD_ON )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_ENABLECOMMUNICATION )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_ON )
    retVal = E_NOT_OK;
# else
#  if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
#  endif

    /* #200 If Com Control is enabled for this channel
     *       If message transmission ability is disabled and Nm state is not BusSleep or PrepareBusSleep
     *        Request to enable the message transmission ability. Further handling is done in CanNm_MainFunction.
     */

    if ( CanNm_IsComControlEnabledOfChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_COM_CONTROL_ENABLED */
    {
      if( CanNm_GetNmState(CANNM_CHANNEL_IDX) > NM_STATE_PREPARE_BUS_SLEEP )
      {
        if( CanNm_GetTxControlState(CANNM_CHANNEL_IDX) == MSG_TX_DISABLED )
        {
          CanNm_SetTxControlStateRequest(CANNM_CHANNEL_IDX, MSG_TX_ENABLED); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
          retVal = E_OK;
        }
      }
    }
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_ENABLECOMMUNICATION , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_ENABLECOMMUNICATION )

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************
 *  CanNm_DisableCommunication
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_DisableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = CANNM_E_NO_ERROR;

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_DISABLECOMMUNICATION )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
#  endif

    /* Disable Nm PDU transmission ability in Network Mode */
    /* #200 If Com Control is enabled for this channel
     *       If Nm state is not BusSleep and not PrepareBusSleep
     *        Request to disable Tx Message transmission ability. Further handling is done in CanNm_MainFunction.
     */

    if ( CanNm_IsComControlEnabledOfChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_COM_CONTROL_ENABLED */
    {
      if( CanNm_GetNmState(CANNM_CHANNEL_IDX) > NM_STATE_PREPARE_BUS_SLEEP )
      {
        CanNm_SetTxControlStateRequest(CANNM_CHANNEL_IDX, MSG_TX_DISABLED); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
        retVal = E_OK;
      }
    }
# endif
  }
  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_DISABLECOMMUNICATION , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_DISABLECOMMUNICATION )

  return retVal;
}
#endif /* ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON ) */


/***********************************************************************************************************************
 *  CanNm_InitMemory
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC( void, CANNM_CODE ) CanNm_InitMemory( void )
{
  /* Note: Do not perform init check. */
#if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Set global state to not initialized */
  CanNm_SetModuleInitialized(FALSE); /* SBSW_CANNM_CSL_VAR_ACCESS */
#endif
#if ( CANNM_USE_INIT_POINTER == STD_ON )
  /* #20 Set config pointer to NULL_PTR */
  CanNm_ConfigDataPtr = NULL_PTR;
#endif
}

#if ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
/***********************************************************************************************************************
 *  CanNm_SetSleepReadyBit
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_SetSleepReadyBit( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                           CONST( boolean, AUTOMATIC ) nmSleepReadyBit )
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8          errorId = CANNM_E_NO_ERROR;

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_SETSLEEPREADYBIT )

  /* ----- Development Error Checks ------------------------------------- */
  /* Check whether the NM is initialized. */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  /* Check parameter 'nmSleepReadyBit' */
  else if( nmSleepReadyBit > 1u )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* Set Coordination Bit */
    /* #200 If configuration parameter <Pdu Cbv Position> is set to Byte 0 or Byte 1
     *       If passed parameter <nmSleepReadyBit> is set
     *        Set Nm Coordinator Sleep Ready Bit
     *       otherwise Clear Nm Coordinator Sleep Ready Bit
     */
    if( CanNm_IsTxMessageData_CBVUsedOfPbChannelConfig(CANNM_CHANNEL_IDX) ) /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */ /* COV_CANNM_CHECK_CBVPOSITION */
    {
      SchM_Enter_CanNm_CANNM_EXCLUSIVE_AREA_3();
      if( nmSleepReadyBit == TRUE ) /* ESCAN00064309 */
      {
        CanNm_SetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX), /* SBSW_CANNM_CSL03 */
          (CanNm_TxMessageDataType)(CanNm_GetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)) | NM_COORD_BIT_SLEEP));
      }
      else
      {
        CanNm_SetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX), /* SBSW_CANNM_CSL03 */
          (CanNm_TxMessageDataType)(CanNm_GetTxMessageData(CanNm_GetTxMessageData_CBVIdxOfPbChannelConfig(CANNM_CHANNEL_IDX)) & NM_COORD_BIT_INV_SLEEP));
      }
      SchM_Exit_CanNm_CANNM_EXCLUSIVE_AREA_3();
    /* #300 If state is Repeat Message OR Normal Operation AND message transmission is allowed on this channel.
     *        Trigger an asynchronous transmission of the NM message
     */
      if( ((CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION) ||
           (CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_REPEAT_MESSAGE))
# if ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
            && ( CanNm_GetTxControlState(CANNM_CHANNEL_IDX) == MSG_TX_ENABLED )
# endif
        ) /* COV_CANNM_NO_REPMSG */
      {
        CanNm_SetMsgRequest(CANNM_CHANNEL_IDX, CANNM_TRANSMIT_REQUEST); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */ /* FEATC-58 */
      }
      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_SETSLEEPREADYBIT , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_SETSLEEPREADYBIT )

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON ) */

/***********************************************************************************************************************
 *  CanNm_RxIndication
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( void, CANNM_CODE ) CanNm_RxIndication( VAR( PduIdType, AUTOMATIC ) RxPduId,
                                             P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8  errorId = CANNM_E_NO_ERROR;
#if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  NetworkHandleType channel;
#endif

#if ( ( CANNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_ON ) && ( ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON ) \
        || (( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) && ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )) ) )
  /* local variables */
  uint8             controlBitVector;
#endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_RXINDICATION )

  /* ----- Development Error Checks ------------------------------------- */
#if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'RxPduId' */
  else if
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
          ( RxPduId != CANNM_CHANNEL_IDX )
# else
#  if ( CANNM_PDUIDTOCHINDEX == STD_ON )
          ( RxPduId >= (NetworkHandleType)CanNm_GetSizeOfPduIdToChIndex() )
#  else
          ( RxPduId >= (NetworkHandleType)CanNm_GetSizeOfChannelConfig() )
#  endif
# endif
  {
    errorId = CANNM_E_INVALID_PDUID;
  }
  else
#endif
  {
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#else
# if ( CANNM_PDUIDTOCHINDEX == STD_ON )
    channel = (NetworkHandleType)CanNm_GetPduIdToChIndex(RxPduId);
# else
    channel = (NetworkHandleType)RxPduId;
# endif
#endif
#if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
    /* Check parameter 'PduInfoPtr' */
    if( (PduInfoPtr) == NULL_PTR )
    {
      errorId = CANNM_E_PARAM_POINTER;
    }
    /* Check parameter 'SduDataPtr' */
    else if( (PduInfoPtr->SduDataPtr) == NULL_PTR )
    {
      errorId = CANNM_E_PARAM_POINTER;
    }
    else
    /* Check parameter 'SduLength' */
    /* RangeConfig DLC Check has been adjusted by CanNm */
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK ) && ( CANNM_RXMESSAGEDATA == STD_ON )
    if( (PduInfoPtr->SduLength) != CanNm_GetRxMessageDataLengthOfPbChannelConfig(CANNM_CHANNEL_IDX) )
    {
      errorId = CANNM_E_RXINDICATION_DLC_ERROR;
    }
    else
# endif
#endif
    /* #20 If module is initialized and parameter checks are passed */
    {
#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
      /* #30 If PN Filtering needs to be applied OR <All Messages Keep Awake> is configured OR <Pn Message Filter Enabled> is not configured 
       *      If Node Id is enabled for this channel
       */
      if( (CanNm_PnFilterHandling( CANNM_CHANNEL_PARA_FIRST PduInfoPtr ) == TRUE) || /* SBSW_CANNM_LOCALFUNCTION_CALL */
# if ( CANNM_ALLMESSAGESKEEPAWAKEOFCHANNELCONFIG == STD_ON )
          (CanNm_IsAllMessagesKeepAwakeOfChannelConfig(CANNM_CHANNEL_IDX)) ||
# endif
          (!CanNm_IsPnMessageFilterEnabled(CANNM_CHANNEL_IDX)) ) /* COV_CANNM_ALL_MESSAGES_KEEP_AWAKE */
#endif /* ( CANNM_PN_FEATURE_ENABLED == STD_ON ) */
      {

#if ( ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) \
        || ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON ) )
# if ( ( CANNM_USER_DATA_ENABLED == STD_OFF ) && ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_OFF ) )
        if (CanNm_IsNodeIdEnabledOfChannelConfig(CANNM_CHANNEL_IDX))
# endif
        {
          /* #300 Copy received NM message data to the Rx Message Data buffer */
          CanNm_CopyRxMessageData( CANNM_CHANNEL_PARA_FIRST PduInfoPtr ); /* SBSW_CANNM_LOCALFUNCTION_CALL */
        }
#endif


#if ( ( CANNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_ON ) && ( ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON ) \
        || (( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) && ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )) ) )
        /* #310 If configuration parameter <Pdu Cbv Position> is set to Byte 0 or Byte 1
         *      AND CBV Byte fits into RX PDU buffer length in case <CanIf Range Config DLC Check> is configured
         *       If Node Detection is enabled for this channel
         *        If Nm state is not RepeatMessage state and Repeat Message Indication flag has not been set yet
         *         Set the Repeat Message Indication flag in order to notify it to the Nm Interface in next main function
         */
        if( (CanNm_GetPduCbvPositionOfChannelConfig(CANNM_CHANNEL_IDX) != CANNM_PDU_OFF) /* COV_CANNM_CHECK_CBVPOSITION */
# if defined ( CANNM_CANIF_RANGE_CONFIG_DLC_CHECK )
            /* No need to check RX PDU Length, fixed length assumed */
# else
            && (PduInfoPtr->SduLength > CanNm_GetPduCbvPositionOfChannelConfig(CANNM_CHANNEL_IDX))
# endif
          ) /* COV_CANNM_CHECK_CBVPOSITION */
        {
          /* Store the CBV Byte */
          controlBitVector = (uint8)(PduInfoPtr->SduDataPtr[CanNm_GetPduCbvPositionOfChannelConfig(CANNM_CHANNEL_IDX)]);
# if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
          if (CanNm_IsNodeDetectionEnabledOfChannelConfig(CANNM_CHANNEL_IDX)) /* COV_CANNM_NODE_DETECTION_ENABLED */
          {
            if ( ( ( CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION ) ||
                   ( CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_READY_SLEEP ) ) &&
                 ( !CanNm_IsRepeatMsgBitIndFlag(CANNM_CHANNEL_IDX) ) )
            {
              CanNm_SetRepeatMsgBitIndFlag(CANNM_CHANNEL_IDX, (CanNm_RepeatMsgBitIndFlagType)(controlBitVector & CANNM_REPEAT_MSG_BIT_MASK)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
            }
          }
# endif

# if ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
          /* #3100 Call CoordReadyToSleepHandling */
          CanNm_CoordReadyToSleepHandling( CANNM_CHANNEL_PARA_FIRST  controlBitVector);
# endif
        }
#endif

#if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
        /* #320 Car Wakeup Indication Handing */
        CanNm_CarWakeupIndication( CANNM_CHANNEL_PARA_FIRST  PduInfoPtr ); /* SBSW_CANNM_LOCALFUNCTION_CALL */
#endif

        /* #330 Further Message Reception is processed in CanNm_MainFunction */
        CanNm_SetMsgIndicationFlag(CANNM_CHANNEL_IDX, TRUE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */

        /* #340 Notify NM Interface that a Nm message has been received. */
#if ( CANNM_BUSNM_SPECIFIC_PDU_RX_INDICATION_ENABLED == STD_ON )
        /* If more than one BusNm is used an the same channel Nm_CanNm_PduRxIndication shall be used. ESCAN00082750 */
        Nm_CanNm_PduRxIndication( CANNM_NMTOSYSTEM_CHANNEL_IND, PduInfoPtr ); /* SBSW_CANNM_PDURXINDICATION */
#else
# if ( CANNM_PDU_RX_INDICATION_ENABLED == STD_ON )
        Nm_PduRxIndication( CANNM_NMTOSYSTEM_CHANNEL_IND );
# endif
#endif
      }
    }  /* Error checks */
  }

  /* ----- Development Error Report --------------------------------------- */
  /* Use channel number as InstanceID */
  /* #40 Report errors if applicable */
#if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_RXINDICATION, errorId);
  }
#else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

#if ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
#else
  CANNM_DUMMY_STATEMENT_CONST(PduInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT(RxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_RXINDICATION )
} /* PRQA S 6030,6050,6080 */ /* MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

#if ( ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF ) )
/***********************************************************************************************************************
 *  CanNm_TxConfirmation
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( void, CANNM_CODE ) CanNm_TxConfirmation( VAR( PduIdType, AUTOMATIC ) TxPduId )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8             errorId = CANNM_E_NO_ERROR;
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_TXCONFIRMATION )

  /* ----- Development Error Checks ------------------------------------- */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'TxPduId' */
  else if
#  if ( CANNM_PDUIDTOCHINDEX == STD_ON )
          ( TxPduId >= (NetworkHandleType)CanNm_GetSizeOfPduIdToChIndex() )
#  else
          ( TxPduId >= (NetworkHandleType)CanNm_GetSizeOfChannelConfig() )
#  endif
  {
    errorId = CANNM_E_INVALID_PDUID;
  }
  else
# endif
  {
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
# else
#  if ( CANNM_PDUIDTOCHINDEX == STD_ON )
    channel = (NetworkHandleType)CanNm_GetPduIdToChIndex(TxPduId);
#  else
    channel = (NetworkHandleType)TxPduId;
#  endif
# endif
    /* #20 If module is initialized and parameter checks are passed */

    /* A flag is used in order to ensure data consistency of the timeout timer. */
    /* #200 Set Message Confirmation Flag for further handling in CanNm_MainFunction
     *      Confirm User Data Transmission.
     */
    CanNm_SetMsgConfirmationFlag(CANNM_CHANNEL_IDX, TRUE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
# if ( CANNM_COM_USER_DATA_SUPPORT == STD_ON ) && ( CANNM_PDUR_CANNM_TXCONFIRMATION == STD_ON )
    /* ESCAN00064309 */ /* ESCAN00070925 */
    PduR_CanNmTxConfirmation( CanNm_GetTxUserDataPduIdOfPbChannelConfig(CANNM_CHANNEL_IDX) );
# endif
  }
  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    /* Development error detection */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_TXCONFIRMATION , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT(TxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_TXCONFIRMATION )
}
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF ) */

#if ( CANNM_COM_USER_DATA_SUPPORT == STD_ON ) || defined ( CANNM_PN_CALC_FEATURE_ENABLED )
/***********************************************************************************************************************
 *  CanNm_Transmit
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_Transmit( VAR( PduIdType, AUTOMATIC ) CanNmTxPduId,
                                                   P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType    retVal;
  uint8             errorId = CANNM_E_NO_ERROR;

# if ( CANNM_ALLOW_TRIGGERED_MSG_TRANSMISSION == STD_ON )
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  CANNM_DUMMY_STATEMENT(CanNmTxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#  else
  /* Create Channel Handle */
  NetworkHandleType channel;
#  endif
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_TRANSMIT )

# if ( CANNM_ALLOW_TRIGGERED_MSG_TRANSMISSION == STD_ON )
  retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check that module is initialized */
#  if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'PduInfoPtr' */
  else if( PduInfoPtr == NULL_PTR )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  /* Check parameter 'SduDataPtr' */
  else if( (PduInfoPtr->SduDataPtr) == NULL_PTR )
  {
    errorId = CANNM_E_PARAM_POINTER;
  }
  /* Check parameter 'CanNmTxPduId' */
  else if
#   if ( CANNM_PDUIDTOCHINDEX == STD_ON )
          ( CanNmTxPduId >= (NetworkHandleType)CanNm_GetSizeOfPduIdToChIndex() )
#   else
          ( CanNmTxPduId >= (NetworkHandleType)CanNm_GetSizeOfChannelConfig() )
#   endif
  {
    errorId = CANNM_E_INVALID_PDUID;
  }
  else
#  endif
  {
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
#  else
#   if ( CANNM_PDUIDTOCHINDEX == STD_ON )
    channel = (NetworkHandleType)CanNm_GetPduIdToChIndex(CanNmTxPduId);
#   else
    channel = (NetworkHandleType)CanNmTxPduId;
#   endif
#  endif
    /* #20 If module is initialized and parameter checks are passed */
    CANNM_DUMMY_STATEMENT_CONST(PduInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    /* Spontaneous transmission is required if
     * - The PN Feature is enabled and the handling of multiple calls of CanNm_NetworkRequest() is disabled
     * - The Car Wake-Up Rx feature is enabled
     * - The Allow Triggered Msg Transmission is enabled (ESCAN00083310)
     */
    /* #200 If Partial Networking is enabled AND Pn Handle Multiple Network Requests is disabled
     *      OR Car Wake Up Rx Enabled is enabled
     *      OR Allow Triggered Msg Transmission is enabled
     *       If Nm is in state NormalOperation OR RepeatMessage AND message transmission is allowed on this channel.
     *        Trigger transmission in next main function call
     */
    if(
#  if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
         ((CanNm_IsPnEnabledOfPbChannelConfig(CANNM_CHANNEL_IDX))
#   if ( CANNM_PNHANDLEMULTIPLENETWORKREQUESTOFCHANNELCONFIG == STD_ON )
          && (!CanNm_IsPnHandleMultipleNetworkRequestOfChannelConfig(CANNM_CHANNEL_IDX))
#   endif
         )
#   if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON ) || ( CANNM_ALLOWTRIGGEREDMSGTRANSMISSIONOFPBCHANNELCONFIG == STD_ON )
         ||
#   endif
#  endif
#  if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON )
         (CanNm_IsCarWakeUpRxEnabledOfChannelConfig(CANNM_CHANNEL_IDX))
#   if( CANNM_ALLOWTRIGGEREDMSGTRANSMISSIONOFPBCHANNELCONFIG == STD_ON )
         ||
#   endif
#  endif
#  if( CANNM_ALLOWTRIGGEREDMSGTRANSMISSIONOFPBCHANNELCONFIG == STD_ON )
         (CanNm_IsAllowTriggeredMsgTransmissionOfPbChannelConfig(CANNM_CHANNEL_IDX)) /* ESCAN00083310 */
#  endif
       ) /* COV_CANNM_PN_ENABLED */
    {
      if( ((CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_NORMAL_OPERATION) ||
           (CanNm_GetNmState(CANNM_CHANNEL_IDX) == NM_STATE_REPEAT_MESSAGE))
#  if ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
                && ( CanNm_GetTxControlState(CANNM_CHANNEL_IDX) == MSG_TX_ENABLED ) /* ESCAN00063983 */
#  endif
        ) /* COV_CANNM_NO_REPMSG_COM_CONTROL_ENABLED */
      {
        CanNm_SetMsgRequest(CANNM_CHANNEL_IDX, CANNM_TRANSMIT_REQUEST); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
        retVal = E_OK;
      }
    }
    else
    {
      retVal = E_OK;
    }
  }
# else /* if ( CANNM_ALLOW_TRIGGERED_MSG_TRANSMISSION == STD_ON ) */
  /* Passive Mode Enabled is ON or PN Feature and Car Wake-Up Rx Enabled are disabled:
   * no spontaneous NM message transmission required
   */
  CANNM_DUMMY_STATEMENT(CanNmTxPduId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  CANNM_DUMMY_STATEMENT_CONST(PduInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
  retVal = E_OK;
# endif

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON ) && ( CANNM_ALLOW_TRIGGERED_MSG_TRANSMISSION == STD_ON )
  if( errorId != CANNM_E_NO_ERROR ) /* COV_CANNM_TRANSMIT_NO_DET */
  {
  /* #90 Report errors if applicable */
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_TRANSMIT , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_TRANSMIT )

  return retVal;
} /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */
#endif

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  CanNm_ConfirmPnAvailability
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( void, CANNM_CODE ) CanNm_ConfirmPnAvailability( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8             errorId = CANNM_E_NO_ERROR;
# if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  /* ESCAN00063454 */
  CANNM_DUMMY_STATEMENT_CONST(nmChannelHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# else
  /* Create channel handle of Nm instance. */
  NetworkHandleType channel;
# endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_CONFIRMPNAVAILABILITY )

  /* ----- Development Error Checks ------------------------------------- */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  /* Check parameter 'Channel' */
#  if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
  else if( ( CanNm_GetSizeOfChannelConfig() == 0u )
        || ( nmChannelHandle != CanNm_GetChannelIdOfChannelConfig(0u) ) ) /* COV_CANNM_ONE_ACTIVE_CHANNEL */ /*lint !e506 */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  else
  else if( ( nmChannelHandle >= CANNM_CFG_NUMBER_OF_SYS_CHANNELS )
        || ( CanNm_GetSysToNmChInd(nmChannelHandle) >= CanNm_GetSizeOfChannelConfig() ) ) /* COV_CANNM_SINGLE_CHANNEL */
  {
    errorId = CANNM_E_INVALID_CHANNEL;
  }
#  endif
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
# if !defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED )
    channel = CanNm_GetSysToNmChInd(nmChannelHandle);
# endif
    /* ESCAN00078589 */
    /* #200 Enable PN message filter. */
    CanNm_SetPnMessageFilterEnabled(CANNM_CHANNEL_IDX, (CanNm_PnMessageFilterEnabledType)CanNm_IsPnEnabledOfPbChannelConfig(CANNM_CHANNEL_IDX)); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */ /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
    CanNm_SetPnMessageFilterDeactivationIndicated(CANNM_CHANNEL_IDX, FALSE); /* SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS */
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_CONFIRMPNAVAILABILITY , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif
  CanNm_Rtm_Stop( RtmMeasurementPoint_CANNM_SID_CONFIRMPNAVAILABILITY )

}
#endif

/***********************************************************************************************************************
 *  CanNm_CancelTransmit
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, CANNM_CODE ) CanNm_CancelTransmit( VAR( PduIdType, AUTOMATIC ) CanNmTxSduId )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8             errorId = CANNM_E_NO_ERROR;
  Std_ReturnType    retVal = E_NOT_OK; /* PRQA S 2981 */ /* MD_MSR_RetVal */

  /* ----- Development Error Checks ------------------------------------- */
# if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  else
# endif
  /* #20 If module is initialized and parameter checks are passed */
  {
    /* #200 Function is only provided for compatibility reasons and has no functionality. */
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_CANCELTRANSMIT , errorId);
  }
# else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif

  CANNM_DUMMY_STATEMENT( CanNmTxSduId ); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */

  return retVal;
}

/***********************************************************************************************************************
 *  CanNm_MainFunction
 **********************************************************************************************************************/
/*! \brief      Main function of the CanNm which processes the NM algorithm. This function is responsible to handle all
 *              CanNm instances.
 *  \details    -
 *  \pre        NM is initialized
 *  \context    TASK
 *  \note       Called by SchM
 *  \trace      SPEC-21803, SPEC-21885, SPEC-21698, SPEC-21988, SPEC-21732, SPEC-21887, SPEC-21788, SPEC-21680, 
 *  \trace      SPEC-21923, SPEC-21929
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( void, CANNM_CODE ) CanNm_MainFunction( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8             errorId = CANNM_E_NO_ERROR;
  NetworkHandleType channel;
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
  uint8             commState;                /* local copy of the global communication state. */
#endif

  CanNm_Rtm_Start( RtmMeasurementPoint_CANNM_SID_MAINFUNCTION )

  /* ----- Development Error Checks ------------------------------------- */
#if ( CANNM_DEV_ERROR_DETECT == STD_ON ) /* COV_CANNM_DEV_ERROR_DETECT_ON */
  /* #10 Check that module is initialized. */
  if( !CanNm_IsModuleInitialized() )
  {
    errorId = CANNM_E_NO_INIT;
  }
  else
#endif
  {
    /* #20 Iterate all Nm channels */
    for( channel = 0u; channel < (NetworkHandleType)CanNm_GetSizeOfChannelConfig(); channel++ )
    {
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
      /* #200 Process Communication Control (if ComControlEnabled enabled for this channel) */
      if ( CanNm_IsComControlEnabledOfChannelConfig(CANNM_CHANNEL_IDX) ) /* COV_CANNM_COM_CONTROL_ENABLED */
      {
        CanNm_CommunicationControlHandling( CANNM_CHANNEL_PARA_ONLY );
      }
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
      /* #210 Copy the global communication state. (no interrupt locks required) */
      commState = CanNm_GetCommState(CANNM_CHANNEL_IDX);
#endif

      /* #220 Process Rx Indication and Tx Confirmation events */
      CanNm_MainRxTxConfHandling( CANNM_CHANNEL_PARA_ONLY );

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
      /* #230 Process Repeat Message Ind. (if NodeDetectionEnabled enabled for this channel) */
      if (CanNm_IsNodeDetectionEnabledOfChannelConfig(CANNM_CHANNEL_IDX)) /* COV_CANNM_NODE_DETECTION_ENABLED */
      {
        CanNm_RepeatMessageIndHandling( CANNM_CHANNEL_PARA_ONLY );
      }
#endif
      /* #240 Process Network Restart */
      /* #2400 If passive or active start-up is requested
       *        Perform a state transition to RepeatMessage (Network Mode).
       */
      if( CanNm_GetNetworkRestartFlag(CANNM_CHANNEL_IDX) != CANNM_NO_RESTART )
      {
        CanNm_StateTransition( CANNM_CHANNEL_PARA_FIRST  NM_STATE_REPEAT_MESSAGE );
      }

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
      /* #250 Process Request or Release bus communication (if PassiveModeEnabled disabled) */
      CanNm_BusCommunicationHandling( CANNM_CHANNEL_PARA_FIRST  commState );
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */

      /* #260 Process NM Timeout Timer */
      CanNm_TimeoutTimerHandling( CANNM_CHANNEL_PARA_ONLY );

      /* #270 Process Repeat Message Timer */
      CanNm_RepeatMessageTimerHandling( CANNM_CHANNEL_PARA_ONLY );

      /* #280 Process Wait Bus Sleep Timer */
      CanNm_WaitBusSleepTimerHandling( CANNM_CHANNEL_PARA_ONLY );

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
      /* #290 Process Remote Sleep Indication Timer (if RemoteSleepIndEnabled enabled) */
      CanNm_RemoteSleepTimerHandling( CANNM_CHANNEL_PARA_ONLY );
#endif

#if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
      /* #300 Process Tx Message Timer */
      CanNm_MessageTimerHandling( CANNM_CHANNEL_PARA_ONLY );


# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF )
      /* #310 Process Tx Message Timeout Timer (if ImmediateTxConfEnabled disabled) */
      CanNm_MessageTimeoutTimerHandling( CANNM_CHANNEL_PARA_ONLY );
# endif /* ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF ) */
#endif /* ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) */

#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
# if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
      /* #330 Calculate Pn Era (if PnEraCalcEnabled enabled) */
      CanNm_PnEraCalculation( CANNM_CHANNEL_PARA_ONLY );
# endif

# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
      /* #320 Calculate Pn Eira (if PnEiraCalcEnabled enabled) */
      CanNm_PnEiraCalculation( CANNM_CHANNEL_PARA_ONLY );
# endif
#endif /* CANNM_PN_FEATURE_ENABLED == STD_ON */
    } /* Channel Iteration */
  } /* Error Checks */

  /* ----- Development Error Report --------------------------------------- */
#if ( CANNM_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report errors if applicable */
  if( errorId != CANNM_E_NO_ERROR )
  {
    (void)Det_ReportError(CANNM_MODULE_ID, CANNM_INSTANCE_ID, CANNM_SID_MAINFUNCTION , errorId);
  }
#else
  CANNM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif

  CanNm_Rtm_Stop(RtmMeasurementPoint_CANNM_SID_MAINFUNCTION)
} /* CanNm_MainFunction */ /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#define CANNM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*******************************************************************************
  Verify the configuration of the CAN Network Management
*******************************************************************************/

/* Check Error Detection / Diagnostic switches  SPEC-21802 */
#if !( defined ( CANNM_DEV_ERROR_DETECT ) && ( ( CANNM_DEV_ERROR_DETECT == STD_OFF ) || ( CANNM_DEV_ERROR_DETECT == STD_ON ) ) )
# error: "CAN NM configuration issue: Development Error Detection Enabled has to be defined STD_OFF or STD_ON"
#endif

#if !( defined ( CANNM_DEV_ERROR_REPORT ) && \
      ( ( CANNM_DEV_ERROR_REPORT == STD_OFF ) || ( CANNM_DEV_ERROR_REPORT == STD_ON ) ) )
# error: "CAN NM configuration issue: Development Error Reporting Enabled has to be defined STD_OFF or STD_ON"
#endif

/* Check CAN Nm Configuration switches */
#if !( defined CANNM_CONFIGURATION_VARIANT_PRECOMPILE )
# error: "CAN NM configuration issue: Config Variant Pre-Compile has to be defined"
#endif
#if !( defined CANNM_CONFIGURATION_VARIANT_LINKTIME )
# error: "CAN NM configuration issue: Config Variant Link-Time has to be defined"
#endif
#if !( defined CANNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
# error: "CAN NM configuration issue: Config Variant Post-Build-Loadable has to be defined"
#endif

#if ( CANNM_CONFIGURATION_VARIANT_PRECOMPILE == CANNM_CONFIGURATION_VARIANT_LINKTIME )
# error: "CAN NM configuration issue: Config Variant Defines of Pre-Compile and Link-Time must have different values"
#endif
#if ( CANNM_CONFIGURATION_VARIANT_PRECOMPILE == CANNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
# error: "CAN NM configuration issue: Config Variant Defines of Pre-Compile and Post-Build-Loadable must have different values"
#endif
#if ( CANNM_CONFIGURATION_VARIANT_LINKTIME == CANNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
# error: "CAN NM configuration issue: Config Variant Defines of Link-Time and Post-Build-Loadable must have different values"
#endif

#if !( defined ( CANNM_CONFIGURATION_VARIANT ) && \
      ( ( CANNM_CONFIGURATION_VARIANT == CANNM_CONFIGURATION_VARIANT_PRECOMPILE ) || \
        ( CANNM_CONFIGURATION_VARIANT == CANNM_CONFIGURATION_VARIANT_LINKTIME ) || \
        ( CANNM_CONFIGURATION_VARIANT == CANNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE ) ) )
# error: "CAN NM configuration issue: Configuration Variant has to be defined to Pre-Compile, Link-Time or Post-Build-Loadable"
#endif
#if !( defined ( CANNM_POSTBUILD_VARIANT_SUPPORT ) && \
      ( ( CANNM_POSTBUILD_VARIANT_SUPPORT == STD_OFF ) || ( CANNM_POSTBUILD_VARIANT_SUPPORT == STD_ON ) ) )
# error: "CAN NM configuration issue: PostBuild Variant Support has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_VERSION_INFO_API ) && \
      ( ( CANNM_VERSION_INFO_API == STD_OFF ) || ( CANNM_VERSION_INFO_API == STD_ON ) ) )
# error: "CAN NM configuration issue: Version Info Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG ) && \
      ( ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_OFF ) || ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "CAN NM configuration issue: Node Detection Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_REMOTE_SLEEP_IND_ENABLED ) && \
      ( ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_OFF ) || ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: Remote Sleep Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_USER_DATA_ENABLED ) && \
      ( ( CANNM_USER_DATA_ENABLED == STD_OFF ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: User Data Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_BUS_SYNCHRONIZATION_ENABLED ) && \
      ( ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_OFF ) || ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: Bus Synchronization Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_PASSIVE_MODE_ENABLED ) && \
      ( ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) || ( CANNM_PASSIVE_MODE_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: Passive Mode Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_NODEIDENABLEDOFCHANNELCONFIG ) && \
      ( ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_OFF ) || ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "CAN NM configuration issue: Node Identifier Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_PDU_RX_INDICATION_ENABLED ) && \
      ( ( CANNM_PDU_RX_INDICATION_ENABLED == STD_OFF ) || ( CANNM_PDU_RX_INDICATION_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: Pdu Rx Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_STATE_CHANGE_IND_ENABLED ) && \
      ( ( CANNM_STATE_CHANGE_IND_ENABLED == STD_OFF ) || ( CANNM_STATE_CHANGE_IND_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: State Change Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG ) && \
      ( ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_OFF ) || ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "CAN NM configuration issue: Communication Control Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_BUS_LOAD_REDUCTION_ENABLED ) && \
      ( ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_OFF ) || ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: Bus Load Reduction Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG ) && \
      ( ( CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_OFF ) || ( CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "CAN NM configuration issue: Immediate Restart Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_REPEATMSGINDENABLEDOFCHANNELCONFIG ) && \
      ( ( CANNM_REPEATMSGINDENABLEDOFCHANNELCONFIG == STD_OFF ) || ( CANNM_REPEATMSGINDENABLEDOFCHANNELCONFIG == STD_ON ) ) )
# error: "CAN NM configuration issue: Repeat Message Indication Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_IMMEDIATE_TXCONF_ENABLED ) && \
      ( ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF ) || ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: Immediate Tx Confirmation Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_DISABLE_TX_ERR_REPORT ) && \
      ( ( CANNM_DISABLE_TX_ERR_REPORT == STD_OFF ) || ( CANNM_DISABLE_TX_ERR_REPORT == STD_ON ) ) )
# error: "CAN NM configuration issue: Disable Transmission Error Reporting has to be defined STD_OFF or STD_ON"
#endif

#if !( defined ( CANNM_COM_USER_DATA_SUPPORT ) && \
      ( ( CANNM_COM_USER_DATA_SUPPORT == STD_OFF ) || ( CANNM_COM_USER_DATA_SUPPORT == STD_ON ) ) )
# error: "CAN NM configuration issue: User Data Support via Com has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_RUNTIME_MEASUREMENT_SUPPORT ) && \
      ( ( CANNM_RUNTIME_MEASUREMENT_SUPPORT == STD_OFF ) || ( CANNM_RUNTIME_MEASUREMENT_SUPPORT == STD_ON ) ) )
# error: "CAN NM configuration issue: Runtime Measurement Support has to be defined STD_OFF or STD_ON"
#endif
/* ESCAN00070925 */
#if !( defined ( CANNM_PDUR_CANNM_TXCONFIRMATION ) && \
      ( ( CANNM_PDUR_CANNM_TXCONFIRMATION == STD_OFF ) || ( CANNM_PDUR_CANNM_TXCONFIRMATION == STD_ON ) ) )
# error: "CAN NM configuration issue: PduR CanNm TxConfirmation has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED ) && \
      ( ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_OFF ) || ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: Immediate Nm Transmission Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED ) && \
      ( ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_OFF ) || ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: Active Wup Bit Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_CAR_WUP_RX_FEATURE_ENABLED ) && \
      ( ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_OFF ) || ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: Car Wup Rx Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED ) && \
      ( ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED == STD_OFF ) || ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: Car Wup Filter Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_PN_FEATURE_ENABLED ) && \
      ( ( CANNM_PN_FEATURE_ENABLED == STD_OFF ) || ( CANNM_PN_FEATURE_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: PN Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_PN_ERA_CALC_FEATURE_ENABLED ) && \
      ( ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_OFF ) || ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: PN ERA Calc Feature Enabled has to be defined STD_OFF or STD_ON"
#endif
#if !( defined ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED ) && \
      ( ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_OFF ) || ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: PN EIRA Calc Feature Enabled has to be defined STD_OFF or STD_ON"
#endif

#if !( defined ( CANNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG ) && \
      ( ( CANNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_OFF ) || ( CANNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG == STD_ON ) ) )
# error: "CAN NM configuration issue: Retry First Message Request has to be defined STD_OFF or STD_ON"
#endif

/* ESCAN00072375 */
#if !( defined ( CANNM_PN_TX_TIMEOUT_EXCEPTION_FEATURE_ENABLED ) && \
      ( ( CANNM_PN_TX_TIMEOUT_EXCEPTION_FEATURE_ENABLED == STD_OFF ) || ( CANNM_PN_TX_TIMEOUT_EXCEPTION_FEATURE_ENABLED == STD_ON ) ) )
# error: "CAN NM configuration issue: PN Tx Timeout Exception Feature Enabled has to be defined STD_OFF or STD_ON"
#endif

/* Check configuration of Passive Mode */
#if ( CANNM_PASSIVE_MODE_ENABLED == STD_ON )
# if ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
#  error "CAN NM configuration issue: CANNM_COORDINATOR_SYNC_SUPPORT cannot be activated if CANNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
#  error "CAN NM configuration issue: CANNM_BUS_SYNCHRONIZATION_ENABLED cannot be activated if CANNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( CANNM_BUS_LOAD_REDUCTION_ENABLED == STD_ON )
#  error "CAN NM configuration issue: CANNM_BUS_LOAD_REDUCTION_ENABLED cannot be activated if CANNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#  error "CAN NM configuration issue: CANNM_REMOTE_SLEEP_IND_ENABLED cannot be activated if CANNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
#  error "CAN NM configuration issue: CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG cannot be activated if CANNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON )
#  error "CAN NM configuration issue: CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED cannot be activated if CANNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED == STD_ON )
#  error "CAN NM configuration issue: CANNM_IMMEDIATE_NM_TX_FEATURE_ENABLED cannot be activated if CANNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( CANNM_IMMEDIATE_TXCONF_ENABLED == STD_ON )
#  error "CAN NM configuration issue: CANNM_IMMEDIATE_TXCONF_ENABLED cannot be activated if CANNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
# if ( CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG == STD_ON )
#  error "CAN NM configuration issue: CANNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG cannot be activated if CANNM_PASSIVE_MODE_ENABLED is STD_ON."
# endif
#endif

/* Check Car Wakeup */
#if ( CANNM_CAR_WUP_RX_FEATURE_ENABLED == STD_OFF ) && ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED == STD_ON )
# error "CAN NM configuration issue: CANNM_CAR_WUP_FILTER_FEATURE_ENABLED cannot be activated if CANNM_CAR_WUP_RX_FEATURE_ENABLED is STD_OFF."
#endif

/* Check PN Feature */
#if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON ) && ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if ( CANNM_COM_USER_DATA_SUPPORT == STD_OFF )
#   error "CAN NM configuration issue: CANNM_PN_EIRA_CALC_FEATURE_ENABLED activated requires CANNM_COM_USER_DATA_SUPPORT to be enabled."
#  endif
# endif
#else
# if ( CANNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
#  error "CAN NM configuration issue: CANNM_PN_ERA_CALC_FEATURE_ENABLED cannot be activated if CANNM_PN_FEATURE_ENABLED is STD_OFF."
# endif
# if ( CANNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON )
#  error "CAN NM configuration issue: CANNM_PN_EIRA_CALC_FEATURE_ENABLED cannot be activated if CANNM_PN_FEATURE_ENABLED is STD_OFF."
# endif
#endif

/* Check configuration of Single Channel optimization */
#if defined ( CANNM_OPTIMIZE_CHANNEL_ENABLED ) && ( CANNM_NUMBER_OF_CANNM_CHANNELS > 1u )
# error "CAN NM configuration issue: Single Channel optimization is only in single channel configurations possible."
#endif

/* Check configuration of Node Detection */
#if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) && ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_OFF )
# error: "CAN NM configuration issue: CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG cannot be activated if CANNM_NODEIDENABLEDOFCHANNELCONFIG is STD_OFF."
#endif

#if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_OFF ) && ( CANNM_REPEATMSGINDENABLEDOFCHANNELCONFIG == STD_ON )
# error "CAN NM configuration issue: CANNM_REPEATMSGINDENABLEDOFCHANNELCONFIG cannot be activated if CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG is STD_OFF."
#endif

/* Check configuration of CBV */
#if( CANNM_PDUCBVPOSITIONOFCHANNELCONFIG == STD_OFF )
# if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) || ( CANNM_ACTIVE_WUP_BIT_FEATURE_ENABLED == STD_ON ) || ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
#  error "CAN NM configuration issue: 'Pdu Cbv Position' has to be configured to CANNM_PDU_BYTE0 or CANNM_PDU_BYTE1."
# endif
#endif

#if ( CANNM_PDUNIDPOSITIONOFCHANNELCONFIG == STD_OFF )
# if ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ) || ( CANNM_CAR_WUP_FILTER_FEATURE_ENABLED == STD_ON )
#  error "CAN NM configuration issue: 'Pdu Cbv Position' has to be configured to CANNM_PDU_BYTE0 or CANNM_PDU_BYTE1."
# endif
#endif

/* module specific MISRA deviations:

  MD_CANNM_Dir4.1
    Reason:       The local API is only called with a valid parameter, so the bound of the array will not be exceeded.
    Risk:         No Risk.
    Prevention:   Covered by code review.

  MD_CANNM_Rule2.1
    Reason:     Previous if statement checks the generated configuration. In a valid configuration the error message will never be reached.
    Risk:       No Risk.
    Prevention: Covered by code review.

  MD_CANNM_Rule2.2
    Reason:     If statement checks the generated configuration. It ensures no Out-Of-Bounds access can occur.
    Risk:       No Risk.
    Prevention: Covered by code review.

  MD_CANNM_Rule12.3:
    Reason:     Used to have a compact and common pattern.
    Risk:       Creation of two statements.
    Prevention: Covered by code review and deep state machine tests with code coverage analysis.

  MD_CANNM_Rule14.2:
    Reason:     Used to have a compact and common pattern.
    Risk:       Creation of two statements.
    Prevention: Covered by code review and deep state machine tests with code coverage analysis.
 
  MD_CANNM_Rule14.3:
    Reason:     In certain configurations the if statement will always result in a TRUE/FALSE expression due to the generated code.
    Risk:       No Risk.
    Prevention: Covered by code review.

  MD_CANNM_Rule16.3:
    Reason:     Fall through used for code optimizations.
    Risk:       There is a risk that a fall through is overseen by a code review and lead to unexpected results.
    Prevention: Fall through is marked with explicit comments to draw attention to it when code review is performed.
*/

/* SBSW_JUSTIFICATION_BEGIN
\ID                SBSW_CANNM_POINTER_PARAM
\DESCRIPTION       The pointer 'nmPduInfo' is passed to the CanIf or PduR
                   The pointer 'nmStatusPtr' is passed to the NmOsek
\COUNTERMEASURE \N The parameters are not used in address calculations for memory manipulating
                   operations. Such calculations include but are not limited to: Array indexing,
                   pointer offset calculation and related forms of pointer arithmetic. Furthermore
                   these parameters are not forwarded to other software modules which could use
                   them for such operations unless they implement appropriate countermeasures.
                   And the addresses in the pointer variables are not saved in global variables
                   so that they could be used outside the function call. In that case, they are no
                   longer valid.

\ID                SBSW_CANNM_GETSTATE
\DESCRIPTION       The function CanNm_GetState writes to the object referenced by parameters 'nmStatePtr' and 'nmModePtr'
\COUNTERMEASURE \N The caller ensures that the pointers passed to the parameters 'nmStatePtr' and 'nmModePtr' is valid.

\ID                SBSW_CANNM_GETLOCALNODEIDENTIFIER
\DESCRIPTION       The function CanNm_GetLocalNodeIdentifier writes to the object referenced by parameters 'nmNodeIdPtr'
\COUNTERMEASURE \N The caller ensures that the pointers passed to the parameter 'nmNodeIdPtr' is valid.

\ID                SBSW_CANNM_GETVERSIONINFO
\DESCRIPTION       The function CanNm_GetVersionInfo writes to the object referenced by parameter 'versioninfo'
\COUNTERMEASURE \N The caller ensures that the pointers passed to the parameter 'versioninfo' is valid.

\ID                SBSW_CANNM_PDURXINDICATION
\DESCRIPTION       The pointer 'PduInfoPtr' is passed to the NmIf
\COUNTERMEASURE \N Pointer parameter is directly passed through.

\ID                SBSW_CANNM_CHECKREMOTESLEEPINDICATION
\DESCRIPTION       The function CanNm_CheckRemoteSleepIndication writes to the object referenced by parameter 'nmRemoteSleepIndPtr'
\COUNTERMEASURE \N The caller ensures that the pointers passed to the parameter 'nmRemoteSleepIndPtr' is valid.

\ID                SBSW_CANNM_GETUSERDATA
\DESCRIPTION       The function CanNm_GetUserData writes to the object referenced by parameter 'nmUserDataPtr'
\COUNTERMEASURE \S The caller of function CanNm_GetUserData must ensure that the pointer passed to the parameter 'nmUserDataPtr'
                   references a valid memory location and that the size of the array referenced by parameter 'nmUserDataPtr'
                   is greater or equal to CanNm_GetRxMessageData_UserDataLengthOfPbChannelConfig(channel). [SMI-326]

\ID                SBSW_CANNM_GETPDUDATA
\DESCRIPTION       The function CanNm_GetUserData writes to the object referenced by parameter 'nmUserDataPtr'
\COUNTERMEASURE \S The caller of function CanNm_GetUserData must ensure that the pointer passed to the parameter 'nmUserDataPtr'
                   references a valid memory location and that the size of the array referenced by parameter 'nmUserDataPtr'
                   is greater or equal to CanNm_GetRxMessageDataLengthOfPbChannelConfig(channel). [SMI-327]

\ID                SBSW_CANNM_LOCALFUNCTION_CALL
\DESCRIPTION       The pointer 'PduInfoPtr' is passed to the local functions CanNm_CopyRxMessageData, CanNm_PnFilterHandling, CanNm_DetermineDynamicPnInfoLength and CanNm_CarWakeupIndication.
\COUNTERMEASURE \N Pointer parameter is directly passed through.

\ID                SBSW_CANNM_NMSTATE_INDEX_ACCESS
\DESCRIPTION       Definition, Declaration of CanNm_NmState and iteration is done within the same bounds defined by CANNM_NUMBER_OF_CANNM_CHANNELS.
\COUNTERMEASURE \N The bounds of this access is checked during compile time.

\ID                SBSW_CANNM_CSL01_DYN_PNINFOLENGTH
\DESCRIPTION       The write access index of arrays CanNm_PnClusterReqNew and CanNm_PnClusterReqExtNew is calculated at runtime by local function CanNm_DetermineDynamicPnInfoLength()
                   The function CanNm_DetermineDynamicPnInfoLength() guarantees that only index values smaller or equal the size of CanNm_PnFilterMask are used.
                   CanNm_PnClusterReqNew and CanNm_PnClusterReqExtNew have a size relation to CanNm_PnFilterMask.
\COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID                SBSW_CANNM_PNCLUSTERREQEXTNEW
\DESCRIPTION       Access of CanNm_PnClusterReqExtNew using ComStackLib
\COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID                SBSW_CANNM_CSL01
\DESCRIPTION       Access of CanNm_PnClusterReqNew, CanNm_PnClusterReq using ComStackLib
\COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID                SBSW_CANNM_CSL02
\DESCRIPTION       Access of CanNm_PnClusterReq, CanNm_PnClusterReqNew, CanNm_PnClusterReqExt, CanNm_PnClusterReqExtNew via indirection to CanNm_PnFilterMask structure
                   with same index using ComStackLib.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID                SBSW_CANNM_CSL03
\DESCRIPTION       Access of CanNm_PnClusterReqExt, CanNm_PnClusterReqExtNew via indirection to CanNm_PnFilterMask structure
                   with same index using ComStackLib.
                   Access of CanNm_TxMesssageData and CanNm_RxMesssageData via indirection over CanNm_ChannelConfig structure
                   with same index using ComStackLib.
\COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID                SBSW_CANNM_CSL_FILTERMASK_INDEX_PNCLUSTERS_PER_BYTE_INDEX_ACCESS
\DESCRIPTION       First dimension access of CanNm_GetPnClusterResetTimer and CanNm_GetPnClusterResetTimerExt via indirection over CanNm_PnFilterMask structure
                   with same index using ComStackLib.
                   Second dimension access uses constant define CANNM_PN_CLUSTERS_PER_BYTE in declaration and iteration.
                   PnClusterResetTimer[SizeOfPnInfoLength][CANNM_PN_CLUSTERS_PER_BYTE]
\COUNTERMEASURE \N First dimension access is qualified use-case CSL02 of ComStackLib. Second dimension access is ensured by using constant define CANNM_PN_CLUSTERS_PER_BYTE.

\ID                SBSW_CANNM_CSL_CHANNEL_INDEX_ACCESS
\DESCRIPTION       Access of CanNm_TxControlState, CanNm_TxControlStateReq, CanNm_TimeoutTimer, CanNm_RemoteSleepTimer, CanNm_MsgTimer, CanNm_MsgConfirmationFlag,
                             CanNm_MsgIndicationFlag, CanNm_RepeatMsgBitIndFlag, CanNm_RepeatMsgTimer, CanNm_RemoteSleepIndState, CanNm_ImmediateNmMsgCount,
                             CanNm_CoordReadyToSleepState, CanNm_WaitBusSleepTimer, CanNm_PnMessageFilterEnabled, CanNm_MsgRequest, CanNm_MsgTimeoutTimer,
                             CanNm_CommState, CanNm_NetworkRestartFlag, CanNm_RepeatMsgReqFlag
                   via indirection over CanNm_ChannelConfig structure with same index using ComStackLib.
                   The 'channel' variable which is used as index is always checked.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID                SBSW_CANNM_CSL_VAR_ACCESS
\DESCRIPTION       A ComStackLib generated variable is accessed.
\COUNTERMEASURE \N The variable is written using a generated macro of the CSL. It immediately dereferences the variables
                   address without pointer arithmetic.

SBSW_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN
\ID COV_CANNM_CHECK_CBVPOSITION
   \ACCEPT TX
   \ACCEPT TF tx tf
   \ACCEPT TX tx tx
   \REASON Parameter is always configured equally on all channels through generator validation. Check improves robustness.

\ID COV_CANNM_CHECK_IMMEDIATE_TRANSMISSIONS
   \ACCEPT TX
   \ACCEPT TF tx tf
   \REASON In Configurations with 'Immediate Nm Transmission' > 0 on all channels, the condition can only evaluate to true.

\ID COV_CANNM_CHECK_MAX_PN_CHANNEL
   \ACCEPT TX tx xx
   \ACCEPT TX tf tx
   \REASON The variable 'maxPnChannel' is set to 0xFF in CanNm_Init() and set to highest Pn channel. If the last channel is the only Pn channel, it evaluates to TX tx xx.

\ID COV_CANNM_CHECK_NIDPOSITION
   \ALWAYS TX
   \REASON Parameter is always configured equally on all channels through generator validation. Check improves robustness.

\ID COV_CANNM_CHECK_PNCLUSTERREQEXTNEW
   \ALWAYS TX
   \REASON This condition checks if the generated values are correct. It shall always evaluate to TX.

\ID COV_CANNM_CHECK_REPEATMSGTIMER
   \ACCEPT TX
   \REASON In Configurations with 'Repeat Message Time' = 0, the condition can only evaluate to true.

\ID COV_CANNM_CHECK_TRANSITION_TO_NETWORKMODE
   \ACCEPT TX
   \REASON In Configurations with 'Node Detection Enabled' = OFF, no transition to NetworkMode from states > NM_STATE_READY_SLEEP is possible.

\ID COV_CANNM_CHECK_USERDATAPOSITION
   \ALWAYS XF
   \REASON This condition checks if the generated values are correct. It shall always evaluate to XF.



\ID COV_CANNM_ACTIVE_WAKEUP_BIT
   \ACCEPT TX
   \ACCEPT TF tx tf
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_ALL_MESSAGES_KEEP_AWAKE
   \ACCEPT TX tf tx xx
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_BUS_LOAD_REDUCTION
   \ACCEPT TX
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_CAR_WAKEUP_FILTER
   \ACCEPT TF tf tx tf
   \ACCEPT TF xf tx tf
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_CAR_WAKEUP_RX
   \ACCEPT TX
   \ACCEPT TF tx tf
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_COM_CONTROL_ENABLED
   \ACCEPT TX
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_DEV_ERROR_DETECT_ON
   \ACCEPT TX
   \ACCEPT TX tx
   \ACCEPT TX tx tx
   \REASON In the non-QM configurations it is only possible to test CANNM_DEV_ERROR_DETECT with value STD_ON

\ID COV_CANNM_IMMEDIATE_RESTART_ENABLED
   \ACCEPT TX
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_INVALID_GENDATA
   \ACCEPT XF
   \ACCEPT TF tf tx
   \REASON This statements checks if the static configuration is correctly generated so that all accesses to CanNm_PbChannelConfig are within its bounds.

\ID COV_CANNM_MSG_TIMER_GT_ZERO
   \ALWAYS TF tf tx tf
   \REASON Robustness of code.

\ID COV_CANNM_NO_NODE_DETECTION_ENABLED
   \ACCEPT TX tf tx
   \REASON Decision coverage is not fulfilled in case no node detection is enabled when retry first message request is enabled.

\ID COV_CANNM_NO_PN_HANDLE_MULTIPLE_NETWORK_REQUESTS
   \ACCEPT TX
   \REASON Only if Pn Handle Multiple Network Requests is activated, this decision can be tested false.

\ID COV_CANNM_NO_REPMSG
   \ACCEPT TF tf xf
   \REASON Decision coverage is not fulfilled in case Repeat Message Time is configured to zero.

\ID COV_CANNM_NO_REPMSG_COM_CONTROL_ENABLED
   \ACCEPT TF tf tf tx tf xf
   \ACCEPT TF tf xf
   \REASON Decision coverage is not fulfilled in case Repeat Message Time is configured to zero.

\ID COV_CANNM_NODE_DETECTION_ENABLED
   \ACCEPT TX
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_NODE_ID_ENABLED
   \ACCEPT TX
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_ONE_ACTIVE_CHANNEL
   \ACCEPT TF xf tf
   \REASON If a channel is configured the first argument can never be true.

\ID COV_CANNM_PN_ENABLED
   \ACCEPT TX
   \ACCEPT TX tx tx
   \ACCEPT TX tf tx
   \ACCEPT TX tx xx
   \ACCEPT TX tf tf tf tx
   \ACCEPT TX tx tf tf tx
   \ACCEPT TX tf tf tx
   \ACCEPT TF tf tx
   \ACCEPT TF tx tf
   \ACCEPT TF tf xf xf
   \ACCEPT TF tf tf tx tf
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_PN_ERA_CALC_ENABLED
   \ACCEPT TX
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_PN_INFO_LENGTH
   \ACCEPT XF
   \REASON Decision coverage is not fulfilled in case PnInfoOffset is configured to 2 and PnInfoLength is configured to 1.

\ID COV_CANNM_REPEAT_MSG_IND_ENABLED
   \ACCEPT TX
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_RETRY_FIRST_MESSAGE_REQUEST_ENABLED
   \ACCEPT TX
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_SINGLE_CHANNEL
   \ACCEPT TF tf xf
   \REASON Decision coverage is not fulfilled in case parameter is equally configured on all channels or in single channel configurations.

\ID COV_CANNM_TRANSMIT_NO_DET
   \ACCEPT XF
   \REASON Decision coverage is not fulfilled in case CANNM_ALLOW_TRIGGERED_MSG_TRANSMISSION is STD_OFF and CANNM_DEV_ERROR_REPORT is STD_ON.

\ID COV_CANNM_TX_CONTROL_STATE
   \ACCEPT TX
   \REASON Decision coverage is not fulfilled in case CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG is OFF and CANNM_COMCONTROLENABLEDOFCHANNELCONFIG is ON.

COV_JUSTIFICATION_END */
/**********************************************************************************************************************
 *  END OF FILE: CanNm.c
 *********************************************************************************************************************/

