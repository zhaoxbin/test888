/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!       \file  Nm.c
 *       \brief  AUTOSAR NM Interface
 *
 *      \details  Implementation of AUTOSAR Generic Network Management Interface
 *                AUTOSAR Release 4
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

#define NM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Nm.h"                                                              /* Include Network Management Interface */
#include "Nm_Cbk.h"                                                          /* Include NM Interface Callback Header */
#if ( NM_MACRO_LAYER_ENABLED == STD_ON )
#else
# include "ComM_Nm.h"                                                                /* Include ComM callback header */
# include "SchM_Nm.h"                                              /* Include Scheduler Module for Critical Sections */
#endif

#if ( NM_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"                                                                /* Include Development Error Tracer */
#endif

#if ( NM_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
# include "Rtm.h"                                                /* ESCAN00070593 */ /* Include Run Time Measurement */
#endif

#if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
# include "NmFiatC.h"
#endif

#if ( NM_BUSNM_FRNM_ENABLED == STD_ON )
# include "FrNm.h"
#endif

#if ( NM_WAIT_BUS_SLEEP_EXTENSIONS == STD_ON )
# include "NmOsek.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Vendor specific version information is decimal coded */
#if ( (NM_SW_MAJOR_VERSION != (12u)) \
   || (NM_SW_MINOR_VERSION != (0u)) \
   || (NM_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of Nm.c and Nm.h are inconsistent"
#endif

/* Vendor specific version information check */
#if ( (NM_CBK_MAJOR_VERSION != (12u)) \
   || (NM_CBK_MINOR_VERSION != (0u)) \
   || (NM_CBK_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of Nm.c and Nm_Cbk.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

#if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF )
# define NM_COORDINATOR_TYPE_ONLY                CONST( uint8, AUTOMATIC ) coordinator
# define NM_COORDINATOR_TYPE_FIRST               CONST( uint8, AUTOMATIC ) coordinator,
# define NM_COORDINATOR_PARA_ONLY                (uint8)(coordinator)
# define NM_COORDINATOR_PARA_FIRST               (uint8)(coordinator),
# define NM_COORDINATOR_IDX                      (coordinator)
#else
# define NM_COORDINATOR_TYPE_ONLY                void
# define NM_COORDINATOR_TYPE_FIRST
# define NM_COORDINATOR_PARA_ONLY
# define NM_COORDINATOR_PARA_FIRST
# define NM_COORDINATOR_IDX                      0u
#endif

#ifndef NM_PDURXINDICATIONOFCHANNELCONFIG
# define NM_PDURXINDICATIONOFCHANNELCONFIG STD_OFF
#endif

#ifndef NM_PDURXINDICATIONOFNMBUSNMASSOCIATION
# define NM_PDURXINDICATIONOFNMBUSNMASSOCIATION STD_OFF
#endif

#if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
# define NM_FIRST_BUSNM_INDEX_FOR_NETWORK_HANDLE         NM_CHANNEL_IDX
#else
# define NM_FIRST_BUSNM_INDEX_FOR_NETWORK_HANDLE         Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX)
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/
/* Run Time Measurements: ESCAN00070593 */
/* \trace DSGN-Nm22873 */
#if ( NM_RUNTIME_MEASUREMENT_SUPPORT == STD_ON )
/* PRQA S 0342 6 */ /* MD_MSR_Rule20.10_0342 */
# define Nm_Rtm_Start(measurement)                { \
                                                    Rtm_Start(RtmConf_##measurement); \
                                                  }
# define Nm_Rtm_Stop(measurement)                 { \
                                                    Rtm_Stop(RtmConf_##measurement); \
                                                  }
#else
# define Nm_Rtm_Start(measurement)
# define Nm_Rtm_Stop(measurement)
#endif

/* Initialization APIs */
#if ( NM_INITIALIZATION_AVAILABLE == STD_ON )
# define Nm_GetInitialized()       Nm_Initialized
# define Nm_SetInitialized(value)  Nm_Initialized = (value) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif


#if ( NM_MACRO_LAYER_ENABLED == STD_ON )
#else
/* (NM_SYSTONMCHIND == STD_ON) If the number of system channels is not equal to the number of NM channels,
 * channel indirection is needed. Otherwise, the channel index is equal to the network handle. */
# if ( NM_SYSTONMCHIND == STD_ON )
#  define NM_CHANNEL_IDX                          Nm_GetSysToNmChInd(nmNetworkHandle)
# else
#  define NM_CHANNEL_IDX                          nmNetworkHandle
# endif

/* When NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON, there is one BusNm per channel, and the index used in 
 * the BusNm functions is equal to the channel. Otherwise, a busNm Index is needed to call the BusNm functions. */
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
#  define NM_CHANNEL_OR_BUSNM_IDX                 channel
#  define NM_NETWORK_HANDLE_OR_BUSNM_IDX          NM_CHANNEL_IDX
#  define NM_NETWORK_HANDLE_OR_FIRST_BUSNM_IDX    NM_CHANNEL_IDX
#  define NM_FIRST_BUSNM_INDEX_OF_CHANNEL         channel

#  if ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
#   define NM_PREVIOUS_STATE                      nmPreviousState
#   define NM_CURRENT_STATE                       nmCurrentState
#  endif
# else
#  define NM_CHANNEL_OR_BUSNM_IDX                 busNmIndex
#  define NM_NETWORK_HANDLE_OR_BUSNM_IDX          busNmIndex
#  define NM_NETWORK_HANDLE_OR_FIRST_BUSNM_IDX    Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX)
#  define NM_FIRST_BUSNM_INDEX_OF_CHANNEL         Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(channel)

#  if ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
#   define NM_PREVIOUS_STATE                      Nm_GetChPrevBusNmState(NM_CHANNEL_IDX)
#   define NM_CURRENT_STATE                       newBusNmMaxState
#  endif
# endif


/* If the NM channel coordination is active, the channel and the bus states can take the possible values: */
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#  define NM_BUS_STATE_UNINIT                     (0x00u)
#  define NM_BUS_STATE_READY_TO_SLEEP             (0x01u)
#  define NM_BUS_STATE_BUS_SLEEP                  (0x02u)
#  define NM_BUS_STATE_PREPARE_BUS_SLEEP          (0x04u)
#  define NM_BUS_STATE_BUS_AWAKE                  (0x08u)

#  define NM_CHANNEL_REQUESTED                    (0x00u)
#  define NM_CHANNEL_READY_TO_RELEASE             (0x01u)
#  define NM_CHANNEL_RELEASED                     (0x02u)
#  if (NM_PASSIVE_STARTUP_FORWARDING_ENABLED == STD_ON)
#   define NM_CHANNEL_WAIT_FOR_PASSIVE_STARTUP    (0x03u)
#  endif
# endif

/* Values notified to the Com module in order to update the signal object during state change notification */
# if ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
#  define NM_RM_BSM                               (0x01u)
#  define NM_RM_PBSM                              (0x02u)
#  define NM_NO_RM                                (0x04u)
#  define NM_NO_RS                                (0x08u)
#  define NM_RM_RS                                (0x10u)
#  define NM_RM_NO                                (0x20u)
# endif

/* If the Nm Channel coordination is active, the coordinator can take the possible states: */
# if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
/* Renaming of coordination states: ESCAN00075311 */ /* \trace SPEC-4208 */
#  define NM_COORDINATOR_SHUT_DOWN                (0x00u)
#  define NM_COORDINATOR_ABORT_SHUTDOWN           (0x01u)
#  define NM_COORDINATOR_NETWORK_REQUESTED        (0x02u)
#  define NM_COORDINATOR_NETWORK_PASSIVE_RELEASED (0x03u)
#  define NM_COORDINATOR_START_TIMERS             (0x04u)
#  define NM_COORDINATOR_WAIT_FOR_TIMERS          (0x05u)
#  define NM_COORDINATOR_TIMER_EXPIRED            (0x06u)
#  define NM_COORDINATOR_WAIT_FOR_SYNC            (0x07u)
#  define NM_COORDINATOR_NO_STATE_CHANGE          (0xFFu)
# endif

/* If the optimization of one BusNm per channel is not available, the different BusNms per channel 
 * can take the following values: */
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
#  define NM_CHANNEL_MODE_INDEX_BUS_SLEEP          (0x00u)
#  define NM_CHANNEL_MODE_INDEX_PREPARE_BUS_SLEEP  (0x01u)
#  define NM_CHANNEL_MODE_INDEX_NETWORK            (0x02u)
# endif

/* Depending on the number of coordinators, the masks are 2 or 4 bytes long */


/* Access to the tables containing the BusNm functions to be called */
/* Access to the shut down delay timer used to set the timer of the active channel */
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
#  define NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(channel) Nm_GetNmFunctionTableIdxOfChannelConfig(channel) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  if ( NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE == STD_ON )
#   define NM_BUSNM_GET_SHUTDOWN_DELAY_TIMER(channel) (1u) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  else
#   define NM_BUSNM_GET_SHUTDOWN_DELAY_TIMER(channel) Nm_GetNmShutdownDelayTimerOfChannelConfig(channel) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif

#  if (NM_PDURXINDICATIONOFCHANNELCONFIG == STD_ON) /* COV_NM_COMSTACKLIB_GEN_NULL */
#   define NM_BUSNM_GET_PDU_RX_INDICATION(channel)    Nm_GetPduRxIndicationOfChannelConfig(channel) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif

#  if (NM_WAIT_BUS_SLEEP_EXTENSIONS == STD_ON)
#   if (NM_NMSHUTDOWNNORMALDELAYTIMEROFCHANNELCONFIG == STD_ON)
#    define NM_BUSNM_GET_SHUTDOWN_NORMAL_DELAY_TIMER(channel) Nm_GetNmShutdownNormalDelayTimerOfChannelConfig(channel) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   else
#    define NM_BUSNM_GET_SHUTDOWN_NORMAL_DELAY_TIMER(channel) (1u) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   endif
#  endif

# else
#  define NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(calculatedBusNmIndex) Nm_GetNmFunctionTableIdxOfNmBusNmAssociation(calculatedBusNmIndex) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  if ( NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE == STD_ON )
#   define NM_BUSNM_GET_SHUTDOWN_DELAY_TIMER(calculatedBusNmIndex) (1u) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  else
#   define NM_BUSNM_GET_SHUTDOWN_DELAY_TIMER(calculatedBusNmIndex) Nm_GetNmShutdownDelayTimerOfNmBusNmAssociation(calculatedBusNmIndex) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif
#  if (NM_PDURXINDICATIONOFNMBUSNMASSOCIATION == STD_ON) /* COV_NM_COMSTACKLIB_GEN_NULL */
#   define NM_BUSNM_GET_PDU_RX_INDICATION(calculatedBusNmIndex)    Nm_GetPduRxIndicationOfNmBusNmAssociation(calculatedBusNmIndex) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif

#  if (NM_WAIT_BUS_SLEEP_EXTENSIONS == STD_ON)
#   if (NM_NMSHUTDOWNNORMALDELAYTIMEROFNMBUSNMASSOCIATION == STD_ON)
#    define NM_BUSNM_GET_SHUTDOWN_NORMAL_DELAY_TIMER(calculatedBusNmIndex) Nm_GetNmShutdownNormalDelayTimerOfNmBusNmAssociation(calculatedBusNmIndex) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   else
#    define NM_BUSNM_GET_SHUTDOWN_NORMAL_DELAY_TIMER(calculatedBusNmIndex) (1u) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#   endif
#  endif

# endif


# if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
#  define  Nm_GetNetworkRequested()             Nm_NetworkRequested
#  define  Nm_SetNetworkRequested(value)        Nm_NetworkRequested = (value) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
# endif

/* \trace SPEC-4239 */
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#  if ( NM_OPTIMIZE_ALL_SLEEP_MASTER == STD_ON )
#   define Nm_InitialRemoteSleepStateAfterNetworkMode(channel)  Nm_GetNmBusNmAssociationLengthOfChannelConfig(channel) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  else
#   define Nm_InitialRemoteSleepStateAfterNetworkMode(channel)  Nm_GetNmNumberOfChannelSleepMastersOfChannelConfig(channel) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  endif
# endif

#endif /* else ( NM_MACRO_LAYER_ENABLED == STD_ON ) */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (NM_LOCAL)
# define NM_LOCAL static
#endif

#if !defined (NM_LOCAL_INLINE)
# define NM_LOCAL_INLINE LOCAL_INLINE
#endif

/* Type for storing network requests */
#if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
typedef uint32 Nm_NetworkRequestedType;
#endif


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
#if (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
# define NM_START_SEC_CONST_8
# include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */

NM_LOCAL CONST(uint8, NM_CONST) Nm_ModeIndirection[4] = /* PRQA S 3218 */ /* MD_NM_Rule8.9 */
{
  0u /*!< Bus Sleep Mode */,
  1u /*!< Prepare Bus Sleep Mode */,
  0u /*!< Synchronize Mode */,
  2u /*!< Network Mode */
};

# define NM_STOP_SEC_CONST_8
# include "MemMap.h"   /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

#define NM_START_SEC_VAR_INIT_8
#include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( NM_INITIALIZATION_AVAILABLE == STD_ON )
NM_LOCAL VAR(boolean, NM_VAR_INIT) Nm_Initialized = FALSE;
#endif

#define NM_STOP_SEC_VAR_INIT_8
#include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define NM_START_SEC_VAR_NO_INIT_32
#include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
NM_LOCAL VAR( Nm_NetworkRequestedType, NM_VAR_NO_INIT ) Nm_NetworkRequested;
#endif

#define NM_STOP_SEC_VAR_NO_INIT_32
#include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define NM_START_SEC_CONST_8
#include "MemMap.h"    /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* NM Interface version is decimal coded. */
CONST(uint8, NM_CONST) Nm_MainVersion      = NM_SW_MAJOR_VERSION;
CONST(uint8, NM_CONST) Nm_SubVersion       = NM_SW_MINOR_VERSION;
CONST(uint8, NM_CONST) Nm_ReleaseVersion   = NM_SW_PATCH_VERSION;

#define NM_STOP_SEC_CONST_8
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define NM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if ( NM_MACRO_LAYER_ENABLED == STD_ON )
#else
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_RestartCoordinator()
 *********************************************************************************************************************/
/*! \brief       Restarts the channels of the given coordinator.
 *  \details     This function is called when the coordinated shut down should be aborted.
 *               Indication of ready sleep is withdrawn.
 *  \param[in]   coordinator     Identification of the NM-coordinator cluster index
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE for the different coordinators
 *  \synchronous TRUE
 *  \note        Called by Nm_MainFunction() and by Nm_MainAux_NmCoordWaitForTm_CheckTimers with blocked Interrupts
 *  \trace       SPEC-4138, SPEC-4147
 *********************************************************************************************************************/
NM_LOCAL FUNC( void, NM_CODE ) Nm_RestartCoordinator(NM_COORDINATOR_TYPE_ONLY);

/**********************************************************************************************************************
 * Nm_AbortShutdown()
 *********************************************************************************************************************/
/*! \brief       Aborts the shutdown process of the coordinator belonging to given network
 *  \details     Sets the coordination state as abort shutdown
 *  \param[in]   nmNetworkHandle     Identification of the NM-channel
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for the different network handles
 *  \synchronous FALSE
 *  \note        Called by Nm
 *  \trace       SPEC-4147, SPEC-4176
 *********************************************************************************************************************/
NM_LOCAL FUNC( void, NM_CODE ) Nm_AbortShutdown(CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle);
# endif



# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
/**********************************************************************************************************************
 *  Nm_RecalculateChannelMode()
 *********************************************************************************************************************/
/*! \brief       Determine the channel mode via BusNm_GetState for all BusNms on the given channel
 *  \details     Calculates the aggregated mode of the channel that is to be forwarded.
 *  \param[in]   nmNetworkHandle     Identification of the NM-channel
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for the different network handles
 *  \synchronous TRUE
 *  \note        Called by Nm_NetworkMode, Nm_PrepareBusSleepMode, Nm_BusSleepMode
 *********************************************************************************************************************/
NM_LOCAL FUNC( void, NM_CODE ) Nm_RecalculateChannelMode(CONST(NetworkHandleType, AUTOMATIC) nmNetworkHandle);
# endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#  if ( NM_OPTIMIZE_NO_SYNC_CHANNEL == STD_OFF )
/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordWaitForSync()
 *********************************************************************************************************************/
/*! \brief       If the current coordinator state is NM_COORDINATOR_WAIT_FOR_SYNC: Manages the channel active timer.
 *               Identifies if there is a time out and calculate the next state.
 *  \details     Handling of the actions realized in the corresponding state "Wait for Sync"
 *               of the "State Machine of Coordinator".
 *  \param[in]   coordinator     coordinator to be processed in the main function
 *  \param[in]   nextState       the calculated next state during main processing passed to the function
 *  \return      Next state for the state machine in the main function.
 *  \pre         coordinator state is NM_COORDINATOR_WAIT_FOR_SYNC
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Called by Nm_MainFunction()
 *  \trace       SPEC-4162
 *********************************************************************************************************************/
#   if (NM_SYNCHRONIZATION_TIMEOUT_TIME == 0u)
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordWaitForSync(uint8 nextState);
#   else 
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordWaitForSync(NM_COORDINATOR_TYPE_FIRST uint8 nextState);
#   endif
#  endif

/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordTimerExpired()
 *********************************************************************************************************************/
/*! \brief       If the current coordinator state is NM_COORDINATOR_TIMER_EXPIRED: Calculates the next 
 *               state of the coordinator 
 *  \details     Handling of the actions realized in the corresponding state "Timer Expired"
 *               of the "State Machine of Coordinator".
 *  \param[in]   coordinator     coordinator to be processed in the main function
 *  \param[in]   nextState       the calculated next state during main processing passed to the function
 *  \return      Next state for the state machine in the main function.
 *  \pre         coordinator state is NM_COORDINATOR_TIMER_EXPIRED
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Called by Nm_MainFunction()
 *  \trace       SPEC-4194
 *********************************************************************************************************************/
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordTimerExpired(NM_COORDINATOR_TYPE_FIRST uint8 nextState);

/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordWaitForTimers()
 *********************************************************************************************************************/
/*! \brief       In case the current coordinator state is NM_COORDINATOR_WAIT_FOR_TIMERS:
 *               Processes the synchronization timers and releases the network if necessary.
 *  \details     Handling of the actions realized in the corresponding state "Wait for Timers"
 *               of the "State Machine of Coordinator".
 *  \param[in]   coordinator     coordinator to be processed in the main function
 *  \param[in]   nextState       the calculated next state during main processing passed to the function
 *  \param[out]  errorId         Error code, in case a function pointer is equals NULL
 *  \return      Next state for the state machine in the main function.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Called by Nm_MainFunction()
 *********************************************************************************************************************/
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordWaitForTimers(NM_COORDINATOR_TYPE_FIRST uint8 nextState, P2VAR( uint8, AUTOMATIC, AUTOMATIC ) errorId);



/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordStartTimers()
 *********************************************************************************************************************/
/*! \brief       If the current coordinator state is NM_COORDINATOR_START_TIMERS: calls <BusNm>_NetworkRelease and
 *               resets the active timer to shutdown delay time if the channel has not been released.
 *               Otherwise deactivate the timer.
 *  \details     Handling of the actions realized in the corresponding state "Start Timers"
 *               of the "State Machine of Coordinator"
 *  \param[in]   coordinator     coordinator to be processed in the main function
 *  \param[out]  errorId         Error code, in case a function pointer is equals NULL
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
NM_LOCAL_INLINE FUNC( void, NM_CODE ) Nm_MainAux_NmCoordStartTimers(NM_COORDINATOR_TYPE_FIRST P2VAR( uint8, AUTOMATIC, AUTOMATIC ) errorId);

/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordNetworkPassiveReleased()
 *********************************************************************************************************************/
/*! \brief       If the current coordinator state is NM_COORDINATOR_NETWORK_PASSIVE_RELEASED 
 *               or NM_COORDINATOR_NETWORK_REQUESTED: calculates if the
 *               channel is ready to sleep, determines if the synchronization timer is needed.
 *               Sets the active timer of every channel. Calculates the next coordinator state.
 *  \details     Handling of the actions realized in the corresponding state "Network Passive Released"
 *               of the "State Machine of Coordinator"
 *  \param[in]   coordinator     coordinator to be processed in the main function
 *  \param[out]  errorId         Error code, in case a function pointer is equals NULL
 *  \param[in]   nextState       the calculated next state during main processing passed to the function
 *  \return      TRUE - break statement shall be executed
 *               FALSE - break statement shall not be executed
 *  \pre         Coordinator state is NM_COORDINATOR_NETWORK_REQUESTED or NM_COORDINATOR_NETWORK_PASSIVE_RELEASED
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Called by Nm_MainFunction() 
 *********************************************************************************************************************/
NM_LOCAL_INLINE FUNC( boolean, NM_CODE ) Nm_MainAux_NmCoordNetworkPassiveReleased(NM_COORDINATOR_TYPE_FIRST P2VAR( uint8, AUTOMATIC, AUTOMATIC ) errorId, P2VAR( uint8, AUTOMATIC, AUTOMATIC ) nextState);

/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordShutDown()
 *********************************************************************************************************************/
/*! \brief       If the coordinator state is NM_COORDINATOR_SHUT_DOWN: Checks the state of the coordinator, 
 *               in case the channel is not asleep, change the coordinator state to "network requested"
 *  \details     Handling of the actions realized in the corresponding state "Shut Down"
 *               of the "State Machine of Coordinator"
 *  \param[in]   coordinator     coordinator to be processed in the main function
 *  \return      Next state for the state machine in the main function.
 *  \pre         Coordinator state is NM_COORDINATOR_SHUT_DOWN
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Called by Nm_MainFunction() 
 *********************************************************************************************************************/
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordShutDown( NM_COORDINATOR_TYPE_ONLY );

/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordWaitForTm_CheckTimers()
 *********************************************************************************************************************/
/*! \brief       Processes the timers of the channel. Calls the corresponding Nm_GetRequestBusSynchronization
 *               function when the timers expire
 *  \details     Sub-handling of the actions realized in the corresponding state "Wait for Timers"
 *               of the "State Machine of Coordinator"
 *  \param[in]   coordinator     coordinator to be processed in the main function
 *  \param[in]   channel         network handle identifier, needed for the calculation of the timers
 *  \param[in]   nextStateFromAuxFunc: the calculated next state during main processing passed to the function
 *  \param[out]  allBusNmTimersHaveExpired:  indicate if all timers have expired already
 *  \param[out]  continueWithNextState:  indicate that the next state should be entered
 *  \param[out]  errorId: Error code, in case a function pointer is equals NULL
 *  \return      Next state for the state machine in the main function.
 *  \pre         Coordinator state is NM_COORDINATOR_WAIT_FOR_TIMERS
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Called by Nm_MainAux_NmCoordWaitForTimers()
 *********************************************************************************************************************/
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordWaitForTm_CheckTimers(NM_COORDINATOR_TYPE_FIRST NetworkHandleType channel, uint8 nextStateFromAuxFunc, P2VAR( boolean, AUTOMATIC, AUTOMATIC ) allBusNmTimersHaveExpired, P2VAR( boolean, AUTOMATIC, AUTOMATIC ) continueWithNextState, P2VAR( uint8, AUTOMATIC, AUTOMATIC ) errorId);
#  else
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordWaitForTm_CheckTimers(NM_COORDINATOR_TYPE_FIRST NetworkHandleType channel, uint8 nextStateFromAuxFunc, P2VAR( boolean, AUTOMATIC, AUTOMATIC ) continueWithNextState, P2VAR( uint8, AUTOMATIC, AUTOMATIC ) errorId);
#  endif

#  if ( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_OFF )
/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordNetworkPassRelCheckAbort()
 *********************************************************************************************************************/
/*! \brief       Called when all active coordinated channels are ready to sleep but at least one passive is awake.
 *               As long as AbortShutdown has not been called during execution of the main function, this function
 *               sets the channel as released.
 *  \details     Sub-handling of the actions realized in the corresponding state "Network Passive Released"
 *               of the "State Machine of Coordinator"
 *  \param[in]   coordinator       coordinator to be processed in the main function
 *  \param[out]  errorId           Error code, in case a function pointer is equals NULL
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Called by Nm_MainAux_NmCoordNetworkPassiveReleased()
 *********************************************************************************************************************/
NM_LOCAL_INLINE FUNC( void, NM_CODE ) Nm_MainAux_NmCoordNetworkPassRelCheckAbort(NM_COORDINATOR_TYPE_FIRST P2VAR( uint8, AUTOMATIC, AUTOMATIC ) errorId);
#  endif

# endif

/**********************************************************************************************************************
 *  Nm_BusSleepModeAuxFunc()
 *********************************************************************************************************************/
/*! \brief       Iterates over all busNm and sets the channels to sleep
 *  \details     Set the channel state to bus sleep and clear the "Sleep Ready Bit"
 *  \param[in]   nmNetworkHandle      Identification of the NM-channel
 *  \param[out]  errorId              Error code, in case a function pointer is equals NULL
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Called by the Nm_BusSleepMode() function
 *********************************************************************************************************************/
NM_LOCAL_INLINE FUNC( void, NM_CODE ) Nm_BusSleepModeAuxFunc( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, P2VAR( uint8, AUTOMATIC, AUTOMATIC ) errorId );

# if ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  Nm_SetSleepReadyBitToFalse()
 *********************************************************************************************************************/
/*! \brief       Sets the Sleep Ready Bit to FALSE for all BusNms on the channel
 *  \details     Iterates over all BusNms on the channel and sets the Sleep Ready Bit to FALSE
 *  \param[in]   channel       Local NM-channel index
 *  \param[in]   api           API Identifier
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Called by the Nm_BusSleepModeAuxFunc() and by Nm_RestartCoordinator()
 *  \trace       SPEC-19578
 *********************************************************************************************************************/
#  if (NM_DEV_ERROR_REPORT == STD_ON)
NM_LOCAL_INLINE FUNC( void, NM_CODE ) Nm_SetSleepReadyBitToFalse( CONST( NetworkHandleType, AUTOMATIC ) channel, CONST( uint8, AUTOMATIC) api );
#  else
NM_LOCAL_INLINE FUNC( void, NM_CODE ) Nm_SetSleepReadyBitToFalse( CONST( NetworkHandleType, AUTOMATIC ) channel );
#  endif
# endif

# if ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
/**********************************************************************************************************************
 *  Nm_StateChangeNotAux_OverallState()
 *********************************************************************************************************************/
/*! \brief       Calculation of the overall current state when there is no optimization for one BusNm on a channel.
 *  \details     Auxiliary function for the Nm_StateNotification function
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[in]   nmPreviousState       Previous state of the NM-channel 
 *  \param[in]   nmCurrentState        Current (new) state of the NM-channel
 *  \return      new overall current state
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE:                               if NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL is STD_ON
 *               Only for different channel handles: if NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL is STD_OFF
 *  \synchronous TRUE
 *  \note        Called by Nm_StateChangeNotification()
 *********************************************************************************************************************/
NM_LOCAL_INLINE FUNC(Nm_StateType, NM_CODE) Nm_StateChangeNotAux_OverallState( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle,
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmPreviousState, 
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmCurrentState );
#  endif


#  if ( NM_STATE_CHANGE_REPORT_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_StateChangeNotAux_ReportState()
 *********************************************************************************************************************/
/*! \brief       Report with the Com_SendSignal() API of the state change.
 *  \details     Auxiliary function for the Nm_StateNotification function
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[in]   newBusNmMaxState      The calculated maximum BusNm state
 *  \param[in]   nmPreviousState       Previous state of the NM-channel 
 *  \param[in]   nmCurrentState        Current (new) state of the NM-channel 
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE:                               if NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL is STD_ON
 *               Only for different channel handles: if NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL is STD_OFF
 *  \synchronous TRUE
 *  \note        Called by Nm_StateChangeNotification()
 *********************************************************************************************************************/
NM_LOCAL_INLINE FUNC(void, NM_CODE)  Nm_StateChangeNotAux_ReportState( 
                                                  CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle,  
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
                                                  CONST( Nm_StateType,      AUTOMATIC ) newBusNmMaxState
#   else
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmPreviousState,
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmCurrentState
#   endif
                                                  );

#  endif

/**********************************************************************************************************************
 *  Nm_StateChangeNotAux_NmFiatCAbortShutdown()
 *********************************************************************************************************************/
/*! \brief       Special behavior for NmFiatC, in which Abort shutdown is realized when the 
 *               BusNm is the first BusNm that has entered Normal Operation or Ready Sleep
 *  \details     Auxiliary function for the Nm_StateNotification function
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[in]   nmPreviousState       Previous state of the NM-channel 
 *  \param[in]   nmCurrentState        Current (new) state of the NM-channel 
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE:                               if NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL is STD_ON
 *               Only for different channel handles: if NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL is STD_OFF
 *  \synchronous TRUE
 *  \note        Called by Nm_StateChangeNotification()
 *********************************************************************************************************************/
#  if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
NM_LOCAL_INLINE FUNC(void, NM_CODE)  Nm_StateChangeNotAux_NmFiatCAbortShutdown(
                                                  CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle,
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmPreviousState,
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmCurrentState );

#  endif
# endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordShutDown()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordShutDown( NM_COORDINATOR_TYPE_ONLY )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( NetworkHandleType, AUTOMATIC ) channel;
  VAR( uint8, AUTOMATIC ) nextState = NM_COORDINATOR_NO_STATE_CHANGE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all channels */
  for (channel = 0u; channel < Nm_GetSizeOfChannelConfig(); channel++)
  {
    /* #20 If the coordinator is part of the channel coordination cluster:
           In case the channel is not asleep, change the coordinator state to network requested. */
#  if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF )
    if (Nm_GetCoordinatorStateClusterIdxOfChannelConfig(channel) == coordinator )
#  endif
    {
      if (Nm_GetChannelState(channel) != NM_BUS_STATE_BUS_SLEEP)
      {
        nextState = NM_COORDINATOR_NETWORK_REQUESTED;
        break;
      }
    }
  }
  return nextState;
}

/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordNetworkPassRelCheckAbort()
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
 */
#  if ( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_OFF )
/* PRQA S 3673 1 */ /* MD_MSR_Rule8.13 */
NM_LOCAL_INLINE FUNC( void, NM_CODE ) Nm_MainAux_NmCoordNetworkPassRelCheckAbort(NM_COORDINATOR_TYPE_FIRST P2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) errorId)
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( NetworkHandleType, AUTOMATIC ) channel;
  VAR( Std_ReturnType, AUTOMATIC )  retVal;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC ) busNmIndex;
#   endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all channels */
  for (channel = 0u; channel < Nm_GetSizeOfChannelConfig(); channel++)
  {
    /* #20 In case the channel is coordinated, and the Nm is not an active coordinator,
           and the channel is ready to be released, then execute the following block: */
    if(
#   if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF )
       (Nm_GetCoordinatorStateClusterIdxOfChannelConfig(channel) == coordinator) && 
#   endif
        (!Nm_IsNmActiveCoordinatorOfChannelConfig(channel)) &&
        (Nm_GetChannelRequested(channel) == NM_CHANNEL_READY_TO_RELEASE)
       )
    {
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      retVal = E_OK;
      /* #30 If optimization for exactly one BusNm on a channel is off, iterate over all BusNms of the channel:
       *              In case there is no optimization for exactly one BusNm on a channel,
       *              calculate the BusNm index that corresponds to the given channel.
       *              If the function is available: Release the network by
       *              forwarding a call of <BusNm>_NetworkRelease to the lower layer.
       */

      /* ESCAN00075453 */
      for (busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(channel); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(channel); busNmIndex++)
#   endif
      {
        /* \trace SPEC-19593 */
#   if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
        if( (Nm_GetNetworkReleaseOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
        {
          *errorId = NM_E_FUNCTION_PTR_IS_NULL; /* SBSW_NM_AUXILIARY_PTRWRITE */
          retVal = E_NOT_OK;
#    if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
          /* This break belongs to the for loop of the busNms */
          break;
#    endif
        }
        else
#   endif
        {
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
          retVal = (Nm_GetNetworkReleaseOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))(Nm_GetNmChannelIdOfChannelConfig(channel))); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#   else
          retVal |= (Nm_GetNetworkReleaseOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))(Nm_GetNmChannelIdOfChannelConfig(channel))); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#   endif
        }
      }

      if( retVal == E_OK ) /* \trace SPEC-19612 */
      {
        /* #80 Set the channel as released */
        Nm_SetChannelRequested(channel, NM_CHANNEL_RELEASED); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
      }
      /* #90 Set coordinator to an abortable state, nextState remains on NM_COORDINATOR_NO_STATE_CHANGE */
      Nm_SetCoordinatorState(NM_COORDINATOR_IDX, NM_COORDINATOR_NETWORK_PASSIVE_RELEASED); /* SBSW_NM_CSL_COORDINATOR_INDEX_ACCESS */
    }
  }
#   if (( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON ) || (NM_DEV_ERROR_DETECT == STD_OFF)) /* COV_NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL_ON_NM_DEV_ERROR_DETECT_OFF */
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#   endif
} 
#  endif /*( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_OFF )*/


/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordNetworkPassiveReleased()
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
 */
/* PRQA S 3673 1 */ /* MD_MSR_Rule8.13 */
NM_LOCAL_INLINE FUNC( boolean, NM_CODE ) Nm_MainAux_NmCoordNetworkPassiveReleased(NM_COORDINATOR_TYPE_FIRST P2VAR( uint8, AUTOMATIC, AUTOMATIC ) errorId, P2VAR( uint8, AUTOMATIC, AUTOMATIC ) nextState )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( NetworkHandleType, AUTOMATIC ) channel;
  VAR( boolean, AUTOMATIC ) doBreak = FALSE;
  VAR( boolean, AUTOMATIC ) activeChannelsAreReadyToSleep = TRUE;
#  if ( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_OFF )
  VAR( boolean, AUTOMATIC ) passiveChannelsAreReadyToSleep = TRUE;
#  endif
#  if ( NM_OPTIMIZE_NO_SYNC_CHANNEL == STD_OFF )
  VAR( boolean, AUTOMATIC ) synchronize = FALSE;
#  endif
  *nextState = NM_COORDINATOR_NO_STATE_CHANGE; /* SBSW_NM_AUXILIARY_PTRWRITE */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Determine common channel states of coordinator */
  SchM_Enter_Nm_NM_EXCLUSIVE_AREA_0();
  /* #20 Iterate over all channels: */
  for (channel = 0u; channel < Nm_GetSizeOfChannelConfig(); channel++)
  {
#  if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF )
    if (Nm_GetCoordinatorStateClusterIdxOfChannelConfig(channel) == coordinator)
#  endif
    {
#  if ( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_OFF )
      /* #30 If the channel is passive, calculate if it is ready to sleep */
      if (!Nm_IsNmActiveCoordinatorOfChannelConfig(channel))
      {
        /* \trace SPEC-4129 */
        if ( (Nm_GetChannelRequested(channel) == NM_CHANNEL_REQUESTED)
                   || (Nm_GetChannelState(channel) == NM_BUS_STATE_BUS_AWAKE) )
        {
          passiveChannelsAreReadyToSleep = FALSE;
        }
        /* Note: a passive channel cannot be a 'Channel Sleep Master' */
      }
      else
#  endif
      {
        /* #40 If the channel is an active coordinator, calculate if it is ready to sleep */
        /* \trace SPEC-4129, SPEC-4239 */

        if ( ( Nm_GetChannelRequested(channel) == NM_CHANNEL_REQUESTED )
#  if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) && ( NM_OPTIMIZE_ALL_SLEEP_MASTER == STD_OFF )
             || ( (Nm_GetChannelState(channel) == NM_BUS_STATE_BUS_AWAKE)          
#   if ( NM_OPTIMIZE_NO_SLEEP_MASTER == STD_OFF )
#    if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
             && (!Nm_IsNmChannelSleepMasterOfChannelConfig(channel))
#    else
             && (Nm_GetNmNumberOfChannelSleepMastersOfChannelConfig(channel) != Nm_GetNmBusNmAssociationLengthOfChannelConfig(channel))
#    endif
#   endif
                )
#  endif          
          )
        {
          activeChannelsAreReadyToSleep = FALSE;
        }

#  if ( NM_OPTIMIZE_NO_SYNC_CHANNEL == STD_OFF )
        /* #50 Determine if the synchronization of the timers is needed */
        if ( ( Nm_GetChannelState(channel) != NM_BUS_STATE_BUS_SLEEP )
#   if ( NM_OPTIMIZE_ALL_SYNC_CHANNEL == STD_OFF )
             && ( Nm_IsNmSynchronizingNetworkOfChannelConfig(channel) )
#   endif
           )
        {
          synchronize = TRUE;
        }
#  endif
      }
    }
  }

  /* \trace SPEC-4176 */
  if(activeChannelsAreReadyToSleep != FALSE)
  {
#  if ( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_OFF )
    if (passiveChannelsAreReadyToSleep == FALSE)
    {
      /* #60 All active coordinated channels are ready to sleep but at least one passive is awake */
      /* #70 Check if AbortShutdown was called during execution of main function */
      if (Nm_GetCoordinatorState(NM_COORDINATOR_IDX) != NM_COORDINATOR_ABORT_SHUTDOWN)
      {
        Nm_MainAux_NmCoordNetworkPassRelCheckAbort(NM_COORDINATOR_PARA_FIRST errorId); /* SBSW_NM_CSL_COORDINATOR_INDEX_ACCESS */
      }
      /* #80 Wait for passive networks */
      doBreak = TRUE; 
    }
    else
#  endif
    {

#  if ( NM_OPTIMIZE_NO_SYNC_CHANNEL == STD_OFF )
      /* Note: coordinator clusters with passively coordinated networks cannot contain a synchronized network */
      if ( synchronize == TRUE )
      {
        /* #90 In case it was calculated that it is not necessary to go immediately to the next state
               and synchronization is needed, then:
               Reset the active timer of every synchronized channel with the value of the synchronization time out
               for the synchronization point.
               Stop the active timer for every non-synchronized channel.
         */
#   if (NM_SYNCHRONIZATION_TIMEOUT_TIME != 0u)
        for (channel = 0u; channel < Nm_GetSizeOfChannelConfig(); channel++)
        {
#    if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF )
          if (Nm_GetCoordinatorStateClusterIdxOfChannelConfig(channel) == coordinator)
#    endif
          {
            /* #100 There is no need to iterate over all BusNms, only one timer per channel required. */
#    if ( NM_OPTIMIZE_ALL_SYNC_CHANNEL == STD_OFF )
            if (!Nm_IsNmSynchronizingNetworkOfChannelConfig(channel)) 
            {
              /* Timer might still be running since last aborted shutdown, so stop it. */ /* ESCAN00088827 */
              Nm_SetChannelActiveTimer(NM_FIRST_BUSNM_INDEX_OF_CHANNEL, 0u); /* SBSW_NM_CSL_TIMER_INDEX_ACCESS */
            }
            else
#    endif
            {
              Nm_SetChannelActiveTimer(NM_FIRST_BUSNM_INDEX_OF_CHANNEL, NM_SYNCHRONIZATION_TIMEOUT_TIME); /* SBSW_NM_CSL_TIMER_INDEX_ACCESS */
            }
          }
        }
#   endif
        /* #110 Go to the next state in order to wait for synchronization */
        *nextState = NM_COORDINATOR_WAIT_FOR_SYNC; /* SBSW_NM_AUXILIARY_PTRWRITE */
        doBreak = TRUE; 
      }
      else
#  endif
      {
        /* #120 If it was previously determined that the next state is needed,
                there is no need to set nextState because NM_COORDINATOR_START_TIMERS
                always falls through the state NM_COORDINATOR_WAIT_FOR_TIMERS
                Nevertheless, set coordinator state to Start Timers because we are in an exclusive area and after
                leaving this exclusive area, the context of the Nm_MainFunction may be interrupted by a Nm function
                that calls Nm_AbortShutdown (e.g. Nm_RemoteSleepCancellation(), Nm_NetworkRequest()).
                Otherwise, the effects of the interrupting functions would be overwritten if there is a coordinator 
                cluster with a shutdown delay timer start value of 1.
         */
        /* \trace SPEC-4199 */
        /* ESCAN00089486 */
        Nm_SetCoordinatorState(NM_COORDINATOR_IDX, NM_COORDINATOR_START_TIMERS); /* SBSW_NM_CSL_COORDINATOR_INDEX_ACCESS */
      }
    }
  }
  else 
  {
    /* #130 Network is requested - nothing to do */
    doBreak = TRUE;
  }

  SchM_Exit_Nm_NM_EXCLUSIVE_AREA_0();

#  if !((NM_DEV_ERROR_DETECT == STD_ON) && ( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_OFF )) /* COV_NOT_NM_DEV_ERROR_DETECT_ON_NM_OPTIMIZE_NO_PASSIVE_COORD_OFF */
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  return doBreak;
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */



/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordStartTimers()
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
 */
/* PRQA S 3673 1 */ /* MD_MSR_Rule8.13 */
NM_LOCAL_INLINE FUNC( void, NM_CODE ) Nm_MainAux_NmCoordStartTimers(NM_COORDINATOR_TYPE_FIRST P2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) errorId )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( NetworkHandleType, AUTOMATIC ) channel;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC ) busNmIndex;
#  endif
#  if (NM_WAIT_BUS_SLEEP_EXTENSIONS == STD_ON)
  VAR( boolean, AUTOMATIC ) allNmOsekInNormal = TRUE;
#  endif

  /* ----- Implementation ----------------------------------------------- */
#  if (NM_WAIT_BUS_SLEEP_EXTENSIONS == STD_ON)
  SchM_Enter_Nm_NM_EXCLUSIVE_AREA_0();
  /* #10 Iterate over all channels: */
  for (channel = 0u; channel < Nm_GetSizeOfChannelConfig(); channel++)
  {
#   if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF )
    if (Nm_GetCoordinatorStateClusterIdxOfChannelConfig(channel) == coordinator)
#   endif
    {
#   if ( NM_NMCONTAINSNMOSEKOFCHANNELCONFIG == STD_ON )
      /* #15 If the channel contains NmOsek: */
      if(Nm_IsNmContainsNmOsekOfChannelConfig(channel))
#   endif
      {
        /* #16 Determine whether NmOsek is in NMNormal */
        (void)NmOsek_GetStatus(Nm_GetNmChannelIdOfChannelConfig(channel), Nm_GetAddrOsekNormal(channel)); /* SBSW_NM_CSL_NMOSEK_GET_STATUS_CALL */

        /* NmOsek is in NMLimpHome if bit 3 is set, otherwise in NMNormal. Therefore mask only bit 3 and right shift
         * it by 3, so that the value of 0x08 will be 0x01, the value of 0x00 remains 0x00.
         * Then 0x01 means that NmOsek is in NMLimpHome, 0x00 means that NmOsek is in NMNormal. Therefore invert the
         * value by subtracting this value from 1.
         */
        Nm_SetOsekNormal(channel, (Nm_OsekNormalType)( 1u - (Nm_OsekNormalType)(((Nm_OsekNormalType)Nm_GetOsekNormal(channel) & 0x08u) >> 3))); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */

        /* #17 Update NMNormal status for all channels with NmOsek in this coordinator cluster */
        allNmOsekInNormal &= (boolean)Nm_GetOsekNormal(channel);
      }
    }
  }
  SchM_Exit_Nm_NM_EXCLUSIVE_AREA_0();
#  endif

  /* #20 Iterate over all channels: */
  for (channel = 0u; channel < Nm_GetSizeOfChannelConfig(); channel++)
  {
#  if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF )
    if (Nm_GetCoordinatorStateClusterIdxOfChannelConfig(channel) == coordinator)
#  endif
    {
      /* #25 If the channel has not been released: */
      if (Nm_GetChannelRequested(channel) < NM_CHANNEL_RELEASED)
      {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* #30 If optimization for exactly one BusNm on a channel is off, iterate over all BusNms of the channel: */
        for (busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(channel); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(channel); busNmIndex++)
#  endif
        {
#  if ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON )
#   if ( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_OFF )
          if (Nm_IsNmActiveCoordinatorOfChannelConfig(channel))
#   endif
          {
#   if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
            if( (Nm_GetSetSleepReadyBitOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
            {
              *errorId = NM_E_FUNCTION_PTR_IS_NULL; /* SBSW_NM_AUXILIARY_PTRWRITE */
#    if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
              /* There is no need to iterate over all BusNms */
              break;
#    endif
            }
            else
#   endif
            {
              /* #50 If the function is available: set the sleep ready bit by forwarding a call of
                     <BusNm>_SetSleepReadyBit to the lower layer. */
              /* \trace SPEC-19599 */
              (void)Nm_GetSetSleepReadyBitOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))(Nm_GetNmChannelIdOfChannelConfig(channel), TRUE); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
            }
          }
#  endif

#  if (NM_WAIT_BUS_SLEEP_EXTENSIONS == STD_ON)
          if (allNmOsekInNormal == TRUE)
          {
            Nm_SetChannelActiveTimer(NM_CHANNEL_OR_BUSNM_IDX, NM_BUSNM_GET_SHUTDOWN_NORMAL_DELAY_TIMER(NM_CHANNEL_OR_BUSNM_IDX)); /* SBSW_NM_CSL_TIMER_INDEX_ACCESS */
          }
          else
          {
#   if (NM_NMSHUTDOWNLIMPHOMETIMEROFCHANNELCONFIG == STD_ON)
            Nm_SetChannelActiveTimer(NM_CHANNEL_OR_BUSNM_IDX, (Nm_ChannelActiveTimerType)(NM_BUSNM_GET_SHUTDOWN_DELAY_TIMER(NM_CHANNEL_OR_BUSNM_IDX) + (((Nm_ChannelActiveTimerType)Nm_GetOsekNormal(channel)) * (Nm_ChannelActiveTimerType)Nm_GetNmShutdownLimpHomeTimerOfChannelConfig(channel)))); /* SBSW_NM_CSL_TIMER_INDEX_ACCESS */
#   else
            Nm_SetChannelActiveTimer(NM_CHANNEL_OR_BUSNM_IDX, NM_BUSNM_GET_SHUTDOWN_DELAY_TIMER(NM_CHANNEL_OR_BUSNM_IDX)); /* SBSW_NM_CSL_TIMER_INDEX_ACCESS */
#   endif
          }
#  else
          /* #60 Set the timer of the active channel with the value of the shutdown delay timer */
          Nm_SetChannelActiveTimer(NM_CHANNEL_OR_BUSNM_IDX, NM_BUSNM_GET_SHUTDOWN_DELAY_TIMER(NM_CHANNEL_OR_BUSNM_IDX)); /* SBSW_NM_CSL_TIMER_INDEX_ACCESS */
#  endif
        }
      }
      else
      {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        for (busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(channel); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(channel); busNmIndex++)
#  endif
        {
          /* #70 Deactivate Timer */
          Nm_SetChannelActiveTimer(NM_CHANNEL_OR_BUSNM_IDX, 0u); /* SBSW_NM_CSL_TIMER_INDEX_ACCESS */
        }
      }
    }
  }
#  if(( NM_DEV_ERROR_DETECT == STD_OFF ) || ( NM_COORDINATOR_SYNC_SUPPORT == STD_OFF )) /* COV_NM_DEV_ERROR_DETECT_OFF_NM_COORDINATOR_SYNC_SUPPORT_OFF */
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordWaitForTm_CheckTimers()
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
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
/* PRQA S 3673 1 */ /* MD_MSR_Rule8.13 */
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordWaitForTm_CheckTimers(NM_COORDINATOR_TYPE_FIRST NetworkHandleType channel, uint8 nextStateFromAuxFunc, P2VAR( boolean, AUTOMATIC, AUTOMATIC ) allBusNmTimersHaveExpired, P2VAR( boolean, AUTOMATIC, AUTOMATIC ) continueWithNextState, P2VAR( uint8, AUTOMATIC, AUTOMATIC ) errorId)
#  else
/* PRQA S 3673 1 */ /* MD_MSR_Rule8.13 */
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordWaitForTm_CheckTimers(NM_COORDINATOR_TYPE_FIRST NetworkHandleType channel, uint8 nextStateFromAuxFunc, P2VAR( boolean, AUTOMATIC, AUTOMATIC ) continueWithNextState, P2VAR( uint8, AUTOMATIC, AUTOMATIC ) errorId)
#  endif
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC ) localNextStateFromAuxFunc = nextStateFromAuxFunc;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC ) busNmIndex;
  /* ----- Implementation ----------------------------------------------- */
  *allBusNmTimersHaveExpired = TRUE; /* SBSW_NM_AUXILIARY_PTRWRITE */

  for (busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(channel); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(channel); busNmIndex++)
#  endif
  {
    /* #10 If the active timer has not expired: */
    if (Nm_GetChannelActiveTimer(NM_CHANNEL_OR_BUSNM_IDX) > 0u)
    {
      /* #20 Decrease timer */
      Nm_DecChannelActiveTimer(NM_CHANNEL_OR_BUSNM_IDX); /* SBSW_NM_CSL_INCREMENT_DECREMENT_INDEX_ACCESS */
      
#  if ( NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE == STD_OFF )
      if (Nm_GetChannelActiveTimer(NM_CHANNEL_OR_BUSNM_IDX) == 0u)
#  endif
      {
        SchM_Enter_Nm_NM_EXCLUSIVE_AREA_0();
        /* #30 Check if AbortShutdown was called during execution of main function */
        if (Nm_GetCoordinatorState(NM_COORDINATOR_IDX) != NM_COORDINATOR_ABORT_SHUTDOWN)
        {
          /* #40 Timer is expired - Release Network by calling BusNm_RequestBusSynchronization()
                 and BusNm_NetworkRelease() functions. */

          /* #50 Forward a call of <BusNm>_RequestBusSynchronization to the lower layer. */
          /* \trace SPEC-4177 */
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
          if( (Nm_GetRequestBusSynchronizationOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
          {
            *errorId = NM_E_FUNCTION_PTR_IS_NULL; /* SBSW_NM_AUXILIARY_PTRWRITE */
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
            /* There is no need to iterate over all BusNms */
            break;
#   endif
          }
          else
#  endif
          {
            (void)Nm_GetRequestBusSynchronizationOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))(Nm_GetNmChannelIdOfChannelConfig(channel)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
          }
          /* #60 Release the network by forwarding a call of <BusNm>_NetworkRelease to the lower layer. */
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
          if( (Nm_GetNetworkReleaseOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
          {
            *errorId = NM_E_FUNCTION_PTR_IS_NULL; /* SBSW_NM_AUXILIARY_PTRWRITE */
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
            /* There is no need to iterate over all BusNms */
            break; /* PRQA S 0771 */ /* MD_NM_Rule15.4 */
#   endif
          }
          else
#  endif
          {
            if (E_OK != Nm_GetNetworkReleaseOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))(Nm_GetNmChannelIdOfChannelConfig(channel))) /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
            {
              /* ESCAN00074996 */
              /*
               * \trace SPEC-19612: abort shutdown immediately
               * (time-critical: BusNms may have transited directly to Bus Sleep after NetworkRelease)
               */
              /* #70 In case the Network could not be released, abort the shutdown immediately and restart the coordinator */
              Nm_RestartCoordinator(NM_COORDINATOR_PARA_ONLY);
              localNextStateFromAuxFunc = NM_COORDINATOR_NETWORK_REQUESTED;
              /* To avoid overwriting in the calling function Nm_MainAux_NmCoordWaitForTimers */
              *continueWithNextState = FALSE; /* SBSW_NM_AUXILIARY_PTRWRITE */

#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
              break; /* PRQA S 0771 */ /* MD_NM_Rule15.4 */
              /* #80 Breaks only iteration - No need to request release of other channels */
#  endif
            }
            else
            {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
              /* #90 Successful channel release */
              Nm_SetChannelRequested(channel, NM_CHANNEL_RELEASED); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#  endif
            }
          }
        }
        SchM_Exit_Nm_NM_EXCLUSIVE_AREA_0();
      }
#  if ( NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE == STD_OFF )
      else
      {
        /* #100 If the active timer has not expired after decreasing the timer:
         *                 Indicate that it should not be continued with the next state
         *                 Indicate that not all busNm have expired, thus the channel can not be released.
         *                 This indications are useful for the calling function,
         *                 in order to release the channel or change of state.
         */

        *continueWithNextState = FALSE; /* SBSW_NM_AUXILIARY_PTRWRITE */
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        *allBusNmTimersHaveExpired = FALSE;  /* SBSW_NM_AUXILIARY_PTRWRITE */
#   endif
      }
#  endif
    }
  }
#  if (NM_DEV_ERROR_DETECT == STD_OFF) /* COV_NM_DEV_ERROR_DETECT_OFF */
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif
  return localNextStateFromAuxFunc;
} /* PRQA S 6060, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */



/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordWaitForTimers()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordWaitForTimers(NM_COORDINATOR_TYPE_FIRST uint8 nextState, P2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) errorId)
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( boolean, AUTOMATIC ) continueWithNextState;
  VAR( NetworkHandleType, AUTOMATIC ) channel; 
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( boolean, AUTOMATIC ) allBusNmTimersHaveExpired;
#  endif 
  VAR( uint8, AUTOMATIC ) localNextState = nextState; /* PRQA S 2981 */ /* MD_MSR_RetVal */
  /* ----- Implementation ----------------------------------------------- */
  continueWithNextState = TRUE;
  /* #10 Iterate over all channels
         Process the synchronization timers and release of the network if necessary */
  for (channel = 0u; channel < Nm_GetSizeOfChannelConfig(); channel++)
  {
#  if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF )
    if (Nm_GetCoordinatorStateClusterIdxOfChannelConfig(channel) == coordinator)
#  endif
    {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      localNextState = Nm_MainAux_NmCoordWaitForTm_CheckTimers(NM_COORDINATOR_PARA_FIRST channel, localNextState, &allBusNmTimersHaveExpired, &continueWithNextState, errorId); /* SBSW_NM_MAINAUX_NMCOORWAITFORTM_TMRS_CALL */
#  else
      localNextState = Nm_MainAux_NmCoordWaitForTm_CheckTimers(NM_COORDINATOR_PARA_FIRST channel, localNextState, &continueWithNextState, errorId); /* SBSW_NM_MAINAUX_NMCOORWAITFORTM_CALL */
#  endif

#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      if (localNextState == NM_COORDINATOR_NETWORK_REQUESTED)
      {
        break; /* breaks only iteration - No need to request release of other channels */
      }
      else
#   if ( NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE == STD_OFF )
      if (allBusNmTimersHaveExpired == TRUE)
#   endif
      {
        /* #30 If all BusNm have already expired, release the channel */
        Nm_SetChannelRequested(channel, NM_CHANNEL_RELEASED); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
      }
#   if ( NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE == STD_OFF )
      else
      {
        /* Intentionally left empty */
      }
#   endif
#  endif
    }
  }
  if (continueWithNextState == TRUE)
  {
    localNextState = NM_COORDINATOR_TIMER_EXPIRED;
    /* no break intended */
  }
#  if( NM_DEV_ERROR_DETECT == STD_OFF ) /* COV_NM_DEV_ERROR_DETECT_OFF */
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif
    
  return localNextState;
} 




/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordTimerExpired()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordTimerExpired(NM_COORDINATOR_TYPE_FIRST uint8 nextState )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC ) continueWithState = NM_BUS_STATE_BUS_SLEEP;
  VAR( NetworkHandleType, AUTOMATIC ) channel;
  VAR( uint8, AUTOMATIC ) localNextState = nextState;
  
  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Iterate over all channels and calculate the next state */
  for (channel = 0u; channel < Nm_GetSizeOfChannelConfig(); channel++)
  {
#  if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF )
    if (Nm_GetCoordinatorStateClusterIdxOfChannelConfig(channel) == coordinator )
#  endif
    {
      continueWithState &= Nm_GetChannelState(channel);
    }
  }
  if( continueWithState == NM_BUS_STATE_BUS_SLEEP )
  {
    localNextState = NM_COORDINATOR_SHUT_DOWN; /* ESCAN00075311 */
  }
          
  return localNextState;
}

/**********************************************************************************************************************
 *  Nm_MainAux_NmCoordWaitForSync()
**********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
#  if ( NM_OPTIMIZE_NO_SYNC_CHANNEL == STD_OFF )
#   if (NM_SYNCHRONIZATION_TIMEOUT_TIME == 0u)
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordWaitForSync(uint8 nextState)
#   else 
NM_LOCAL_INLINE FUNC( uint8, NM_CODE ) Nm_MainAux_NmCoordWaitForSync(NM_COORDINATOR_TYPE_FIRST uint8 nextState)
#   endif
{
  /* ----- Local Variables ---------------------------------------------- */
#   if ( NM_SYNCHRONIZATION_TIMEOUT_TIME != 0u )
  VAR( NetworkHandleType, AUTOMATIC ) channel; 
#   endif
  VAR( uint8, AUTOMATIC ) localNextState = nextState;
  /* ----- Development Error Checks ------------------------------------- */
#   if ( NM_SYNCHRONIZATION_TIMEOUT_TIME != 0u )
  /* #10 Iterate over all channels to find one timer per channel */
  for (channel = 0u; channel < Nm_GetSizeOfChannelConfig(); channel++) /* COV_NM_CONFIG_SYNCHRONIZATION_TIMEOUT */
  {
    /* #30 If the active timer has not expired yet: */
#    if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF ) || ( NM_OPTIMIZE_ALL_SYNC_CHANNEL == STD_OFF )
    if (
#     if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF )
        (Nm_GetCoordinatorStateClusterIdxOfChannelConfig(channel) == coordinator)
#      if ( NM_OPTIMIZE_ALL_SYNC_CHANNEL == STD_OFF )
        &&
#      endif
#     endif
#     if ( NM_OPTIMIZE_ALL_SYNC_CHANNEL == STD_OFF )
        (Nm_GetChannelActiveTimer(NM_FIRST_BUSNM_INDEX_OF_CHANNEL) > 0u)
#     endif
     )
#    endif
    {
      /* #40 Decrease timer */
      Nm_DecChannelActiveTimer(NM_FIRST_BUSNM_INDEX_OF_CHANNEL); /* SBSW_NM_CSL_INCREMENT_DECREMENT_INDEX_ACCESS */

#    if ( NM_SYNCHRONIZATION_TIMEOUT_TIME != 1u )
      if (Nm_GetChannelActiveTimer(NM_FIRST_BUSNM_INDEX_OF_CHANNEL) == 0u)
#    endif
      {
        /* #50 If there is a timeout for Nm_SynchronizationPoint expired - Report error and go to next state */
        /* \trace SPEC-4123, SPEC-31350 */
#    if ( NM_DEV_ERROR_REPORT == STD_ON )
        (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID,
                               NM_SID_MAINFUNCTION, NM_E_SYNCHRONIZATION_TIMEOUT);
#    endif
        localNextState = NM_COORDINATOR_START_TIMERS;
        break; /* break for - no need to check further channels */
      }
    }
  }
#   endif
  return localNextState;
} 
#  endif /* ( NM_OPTIMIZE_NO_SYNC_CHANNEL == STD_OFF ) */
# endif /* ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) */

/**********************************************************************************************************************
 *  Nm_AbortShutdown()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
NM_LOCAL FUNC( void, NM_CODE ) Nm_AbortShutdown(CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* #10 Get the index of the coordination cluster, given a network handle. */
  VAR( uint8, AUTOMATIC ) coordinator = Nm_GetCoordinatorStateClusterIdxOfChannelConfig(NM_CHANNEL_IDX);
  /* #20 If the given network is coordinated,
        and if there is no network requested and the coordinator is not already in shut down state:
        Abort Shutdown of the coordinator */

  /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF )
  if( coordinator != NM_NO_COORDINATORSTATECLUSTERIDXOFCHANNELCONFIG )
#  endif
  {
    if( (Nm_GetCoordinatorState(coordinator) != NM_COORDINATOR_NETWORK_REQUESTED) 
#  if (NM_COORDINATOR_REQUEST_CHANNELS_IN_BUS_SLEEP == STD_OFF)
        /* ESCAN00075013 */ /* \trace SPEC-4160 */
        && (Nm_GetCoordinatorState(coordinator) != NM_COORDINATOR_SHUT_DOWN) /* ESCAN00075311 */
#  endif
      )
    {
      /* \trace SPEC-4129 */
      Nm_SetCoordinatorState(coordinator, NM_COORDINATOR_ABORT_SHUTDOWN); /* SBSW_NM_CSL_COORDINATOR_INDEX_ACCESS */
    }
  }
}

/**********************************************************************************************************************
 *  Nm_RestartCoordinator()
 *********************************************************************************************************************/
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
 */

NM_LOCAL FUNC( void, NM_CODE ) Nm_RestartCoordinator(NM_COORDINATOR_TYPE_ONLY)
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
  VAR ( NetworkHandleType, AUTOMATIC ) channel;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR ( uint8_least, AUTOMATIC ) busNmIndex;
#  endif

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all channels: */
  for (channel = 0u; channel < Nm_GetSizeOfChannelConfig(); channel++)
  {
#  if ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF )
    /*  #20 If the current channel belongs to the provided coordinator cluster: */
    if (Nm_GetCoordinatorStateClusterIdxOfChannelConfig(channel) == coordinator)
#  endif
    {
#  if ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON )
      /*  #30 Set the Sleep Ready Bit to FALSE */
      Nm_SetSleepReadyBitToFalse(channel
#   if ( NM_DEV_ERROR_REPORT == STD_ON )
                                 , NM_SID_MAINFUNCTION
#   endif
        );
#  endif
      if ( Nm_GetChannelRequested(channel) != NM_CHANNEL_REQUESTED )
      {
        /*  #70 Call ComM restart indication for all networks that already indicated bus sleep. */
        if (Nm_GetChannelState(channel) == NM_BUS_STATE_BUS_SLEEP)
        {
#  if (NM_PASSIVE_STARTUP_FORWARDING_ENABLED == STD_ON)
          Nm_SetChannelRequested(channel, NM_CHANNEL_WAIT_FOR_PASSIVE_STARTUP); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#  endif
          /* \trace SPEC-4145 */
          ComM_Nm_RestartIndication(Nm_GetNmChannelIdOfChannelConfig(channel)); /* ESCAN00073347 */
        }
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
        else if ( Nm_GetChannelRequested(channel) >= NM_CHANNEL_RELEASED )
#  else
        else
#  endif
        {
          /* #80 If the channel has not indicated bus sleep, request network for all BusNms of the channel. */
          Nm_SetChannelRequested(channel, NM_CHANNEL_READY_TO_RELEASE); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
          /* \trace SPEC-4175, SPEC-4247 */
          /* SPEC-4247 - Indication of the bus mode comes through Nm_NetworkMode by BusNm */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
          /* #90 Iterate over all BusNms of the channel:
                 Only request the network for the BusNms where the channel has been released.
                 Request the network by forwarding a call of <BusNm>_NetworkRequest to the lower layer. */
          for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(channel); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(channel); busNmIndex++ )
#  endif
          {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
            if (Nm_GetChannelActiveTimer(NM_CHANNEL_OR_BUSNM_IDX) == 0u)
#  endif
            {
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
              if( (Nm_GetNetworkRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
              {
                errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
                /* There is no need to iterate over all BusNms */
                break;
#   endif
              }
              else
#  endif
              {
                (void)Nm_GetNetworkRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))(Nm_GetNmChannelIdOfChannelConfig(channel)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
              }
            }
          }
        }
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
        else
        {
          /* Intentionally left empty */
        }
#  endif
      }

    }
  }
  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR) /* COV_NM_NULLFUNCTION */
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_MAINFUNCTION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
# endif /* ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) */


/**********************************************************************************************************************
 *  Nm_RecalculateChannelMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
NM_LOCAL FUNC(void, NM_CODE) Nm_RecalculateChannelMode(CONST(NetworkHandleType, AUTOMATIC) nmNetworkHandle)
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(Nm_StateType, AUTOMATIC)  state = NM_STATE_BUS_SLEEP;
  VAR(Nm_ModeType, AUTOMATIC)   mode = NM_MODE_BUS_SLEEP;
  VAR(uint8_least, AUTOMATIC)   busNmIndex;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset counters. */
  Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_BUS_SLEEP] = 0u; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */
  Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_PREPARE_BUS_SLEEP] = 0u; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */
  Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_NETWORK] = 0u; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */


  for (busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++)
  {
    /* #20 Iterate over all BusNms and calculate the overall channel mode. */
    (void)Nm_GetGetStateOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle, /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
      (P2VAR( Nm_StateType, AUTOMATIC, AUTOMATIC ))&state,
      (P2VAR( Nm_ModeType, AUTOMATIC, AUTOMATIC ))&mode); 
    /* #22 Count the number of modes found */
    /* #23 Assure valid access to the array by using the AND operation of the index with 0x03 (size of the array) */
    Nm_GetChannelMode(NM_CHANNEL_IDX)[Nm_ModeIndirection[mode & NM_NUMBER_OF_CHANNEL_MODES]]++; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */
  }
}
# endif


/**********************************************************************************************************************
 *  Nm_BusSleepModeAuxFunc()
 *********************************************************************************************************************/
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
 */
/* PRQA S 3673 1 */ /* MD_MSR_Rule8.13 */
NM_LOCAL_INLINE FUNC(void, NM_CODE) Nm_BusSleepModeAuxFunc( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, P2VAR( uint8, AUTOMATIC, AUTOMATIC ) errorId )
{
  /* ----- Local Variables ---------------------------------------------- */
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF ) && ( NM_BUSNM_FRNM_ENABLED == STD_ON )
  VAR( uint8_least, AUTOMATIC ) busNmIndex;
# endif

  /* ----- Implementation ----------------------------------------------- */
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  /* #80 Set the channel state to bus sleep */
  Nm_SetChannelState(NM_CHANNEL_IDX, NM_BUS_STATE_BUS_SLEEP); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#  if ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON )
#   if ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF )
  /* #90 In case the coordinator synchronization is active and
         the optimization for all channels coordinated is not active and
         If the network is part of a cluster of coordinated networks: */
  if ( Nm_GetCoordinatorStateClusterIdxOfChannelConfig(NM_CHANNEL_IDX) != NM_NO_COORDINATORSTATECLUSTERIDXOFCHANNELCONFIG )
#   endif
  {
    Nm_SetSleepReadyBitToFalse(NM_CHANNEL_IDX
#   if ( NM_DEV_ERROR_REPORT == STD_ON )
                               , NM_SID_BUSSLEEPMODE
#   endif
                              );
  }
#  endif
# endif
  /* #120 Notify that the network management has entered Bus-Sleep Mode to the ComM module. */
  ComM_Nm_BusSleepMode( nmNetworkHandle );
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_BUSNM_FRNM_ENABLED == STD_ON )
  /* Request this channel again because it has entered Bus Sleep Mode although it was already requested */
  /* ESCAN00081182, ESCAN00086148 */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX);
#  endif
  if ((Nm_GetNetworkRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX)) == FrNm_NetworkRequest) &&
      (Nm_GetChannelRequested(NM_CHANNEL_IDX) != NM_CHANNEL_RELEASED)) /* COV_NM_CONFIG_FRNM */
  {
    ComM_Nm_RestartIndication(nmNetworkHandle);
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX);
          busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#  endif
    {
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetNetworkRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        *errorId = NM_E_FUNCTION_PTR_IS_NULL; /* SBSW_NM_AUXILIARY_PTRWRITE */
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        break;
#   endif
      }
      else
#  endif
      {
        (void)Nm_GetNetworkRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
      }
    }
  }
# endif
  
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_OFF ) || ( NM_BUSNM_FRNM_ENABLED == STD_OFF ) || ( NM_DEV_ERROR_DETECT == STD_OFF ) /* COV_NM_COORDINATOR_SUPPORT_ENABLED_OFF_NM_BUSNM_FRNM_ENABLED_OFF_NM_DEV_ERROR_DETECT_STD_OFF */
  /* ESCAN00089163 */
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif
}


# if ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  Nm_SetSleepReadyBitToFalse()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
NM_LOCAL_INLINE FUNC( void, NM_CODE ) Nm_SetSleepReadyBitToFalse( CONST( NetworkHandleType, AUTOMATIC ) channel, CONST( uint8, AUTOMATIC) api )
#  else
NM_LOCAL_INLINE FUNC( void, NM_CODE ) Nm_SetSleepReadyBitToFalse( CONST( NetworkHandleType, AUTOMATIC ) channel )
#  endif
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR ( uint8_least, AUTOMATIC ) busNmIndex;
#  endif

  /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_OFF )
  /* #10 If the channel is actively coordinated: */
  if (Nm_IsNmActiveCoordinatorOfChannelConfig(channel))
#  endif
  {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    /* #20 Iterate over all BusNms of the channel: Clear the bit that indicates ready sleep for all buses. */
    for (busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(channel); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(channel); busNmIndex++)
#  endif
    {
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetSetSleepReadyBitOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        break;
#   endif
      }
      else
#  endif
      {
        (void)Nm_GetSetSleepReadyBitOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_OR_BUSNM_IDX))(Nm_GetNmChannelIdOfChannelConfig(channel), FALSE); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
      }
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR) /* COV_NM_NULLFUNCTION */
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, api, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif
}
# endif

# if ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
/**********************************************************************************************************************
 *  Nm_StateChangeNotAux_OverallState()
 *********************************************************************************************************************/
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
 */
NM_LOCAL_INLINE FUNC(Nm_StateType, NM_CODE) Nm_StateChangeNotAux_OverallState( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle,
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmPreviousState, 
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmCurrentState )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(Nm_StateType, AUTOMATIC) newBusNmMaxState;
  
  /* ----- Implementation ----------------------------------------------- */
  /* #20 Indicate that the current state is entered and the previous state was left */
  Nm_GetChannelBusNmState(NM_CHANNEL_IDX)[nmCurrentState]++; /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
  Nm_GetChannelBusNmState(NM_CHANNEL_IDX)[nmPreviousState]--; /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */

  /* #30 Calculate the new overall state */
  newBusNmMaxState = NM_STATE_NUMBER_OF_STATES;

  if (nmCurrentState > Nm_GetChPrevBusNmState(NM_CHANNEL_IDX))
  {
    /* #40 In case the current state is bigger than the previous state, take is as the new overall state */
    newBusNmMaxState = nmCurrentState;
  }
  else if ((nmCurrentState < Nm_GetChPrevBusNmState(NM_CHANNEL_IDX)) &&
            (Nm_GetChannelBusNmState(NM_CHANNEL_IDX)[Nm_GetChPrevBusNmState(NM_CHANNEL_IDX)] == 0u))
  {
    /* #50 In case the last BusNm has already left the currently highest state,
            locate the next highest state of the BusNm */
    for (newBusNmMaxState = (Nm_StateType)(Nm_GetChPrevBusNmState(NM_CHANNEL_IDX) - 1u);
          newBusNmMaxState > NM_STATE_UNINIT;
          newBusNmMaxState--)
    {
      if (Nm_GetChannelBusNmState(NM_CHANNEL_IDX)[newBusNmMaxState] > 0u)
      {
        /* #60 New overall state is less than previous overall state */
        break;
      }
    }
  }
  else
  {
    /* Intentionally left empty */
  }  
    
  return newBusNmMaxState;
   
}
#  endif

#  if ( NM_STATE_CHANGE_REPORT_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_StateChangeNotAux_ReportState()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
NM_LOCAL_INLINE FUNC(void, NM_CODE)  Nm_StateChangeNotAux_ReportState( 
                                                   
                                                  CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle,  
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
                                                  CONST( Nm_StateType,      AUTOMATIC ) newBusNmMaxState
#   else
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmPreviousState,
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmCurrentState
#   endif
                                                  )
{     
  /* ----- Local Variables ---------------------------------------------- */
  VAR(uint8, AUTOMATIC) nmStateSignal = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the Nm state signal in case the current state is repeat message or normal operation */
#   if ( NM_NMSTATEREPORTENABLEDOFCHANNELCONFIG == STD_ON )
  if( Nm_IsNmStateReportEnabledOfChannelConfig(NM_CHANNEL_IDX) )
#   else
  /* #20 State Report Enabled is turned ON for every channel */
#   endif
  {
    if( NM_CURRENT_STATE == NM_STATE_REPEAT_MESSAGE )
    {
      switch(NM_PREVIOUS_STATE)
      {
        case NM_STATE_BUS_SLEEP:
          nmStateSignal = NM_RM_BSM;
          break;
        case NM_STATE_PREPARE_BUS_SLEEP:
          nmStateSignal = NM_RM_PBSM;
          break;
        case NM_STATE_READY_SLEEP:
          nmStateSignal = NM_RM_RS; 
          break;
        case NM_STATE_NORMAL_OPERATION:
          nmStateSignal = NM_RM_NO;
          break;
        default: /* PRQA S 2016 */ /* MD_MSR_EmptyClause */
          break;
      }
    }
    else if (NM_CURRENT_STATE == NM_STATE_NORMAL_OPERATION)
    {
      if(NM_PREVIOUS_STATE == NM_STATE_REPEAT_MESSAGE)
      {
        nmStateSignal = NM_NO_RM;
      }
      else if(NM_PREVIOUS_STATE == NM_STATE_READY_SLEEP)
      {
        nmStateSignal = NM_NO_RS;
      }
      else
      {
        /* Empty */
      }
    }
    else
    {
      /* Empty */
    }
    /* #30 Call Com API in order to update the signal object. */
    (void)Com_SendSignal(Nm_GetNmStateReportSignalRefOfChannelConfig(NM_CHANNEL_IDX), &nmStateSignal); /* PRQA S 0315 */ /* MD_NM_Dir1.1 */ /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
  }      
     
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
     
#  endif /* (NM_STATE_CHANGE_REPORT_ENABLED == STD_ON ) */

#  if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
/**********************************************************************************************************************
 *  Nm_StateChangeNotAux_NmFiatCAbortShutdown()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
NM_LOCAL_INLINE FUNC(void, NM_CODE)  Nm_StateChangeNotAux_NmFiatCAbortShutdown( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmPreviousState, 
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmCurrentState )
{
  if(Nm_GetPassiveStartUpOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_FIRST_BUSNM_IDX)) == NmFiatC_PassiveStartUp)
  {
    if ( (nmCurrentState == NM_STATE_READY_SLEEP) || (nmCurrentState == NM_STATE_NORMAL_OPERATION) )
    {
      if ( (nmPreviousState != NM_STATE_READY_SLEEP ) && (nmPreviousState != NM_STATE_NORMAL_OPERATION ) )
      {
        /* #10 If this BusNm is the first BusNm that has entered Network Mode:
         *      Reset the Remote Sleep State to the initial value:
         *      number of BusNms that are Channel Sleep Masters.
         *      Wake the channels and abort shutdown
         */
      
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        Nm_SetChRemSleepState(NM_CHANNEL_IDX, Nm_InitialRemoteSleepStateAfterNetworkMode(NM_CHANNEL_IDX)); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#   endif

        Nm_SetChannelState(NM_CHANNEL_IDX, NM_BUS_STATE_BUS_AWAKE); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
        Nm_AbortShutdown(nmNetworkHandle);
      }
    }
  }                                                                                             
}                                                  
#  endif  
# endif /* (NM_STATE_CHANGE_IND_ENABLED == STD_ON ) */


#endif /* ELSE NM_MACRO_LAYER_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
#if ( NM_INITIALIZATION_AVAILABLE == STD_ON )
/**********************************************************************************************************************
 *  Nm_Init()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
# if ( NM_POSTBUILD_VARIANT_SUPPORT == STD_ON )
FUNC( void, NM_CODE ) Nm_Init( CONSTP2CONST( Nm_ConfigType, AUTOMATIC, NM_CONST ) nmConfigPtr )
# else
FUNC( void, NM_CODE ) Nm_Init( void )
# endif
{
  /* ----- Local Variables ---------------------------------------------- */
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  /* ESCAN00078185 */
  VAR( uint8_least, AUTOMATIC ) coordinator;
  VAR( uint8_least, AUTOMATIC ) channel;
# endif

# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC ) busNmIndex;
# endif

# if (NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF)
#  if (NM_STATE_CHANGE_IND_ENABLED == STD_ON)
  VAR( Nm_StateType, AUTOMATIC ) state;
#  endif
# endif

  /* ----- Implementation ----------------------------------------------- */
  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_INIT)

# if ( NM_USE_INIT_POINTER == STD_ON )

  /* #10 In the post-build variant: Save the pointer to configuration. */
  Nm_ConfigPtr = nmConfigPtr;

  if( nmConfigPtr != NULL_PTR )
# else
#  if ( NM_POSTBUILD_VARIANT_SUPPORT == STD_ON )
  NM_DUMMY_STATEMENT_CONST(nmConfigPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif
# endif
  {
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
    /* #20 Iterate over all coordinators and initialize them in the NM_COORDINATOR_SHUT_DOWN state. */
    for (coordinator = 0u; coordinator < Nm_GetSizeOfCoordinatorState(); coordinator++)
    {
      Nm_SetCoordinatorState(coordinator, NM_COORDINATOR_SHUT_DOWN); /* SBSW_NM_CSL_COORDINATOR_INDEX_ACCESS */ /* ESCAN00075311 */


    }
    /* #30 Iterate over all channels, initialize their channel state to NM_BUS_STATE_BUS_SLEEP and their requested state to NM_CHANNEL_RELEASED. */
    for (channel = 0u; channel < Nm_GetSizeOfChannelConfig(); channel++)
    {
      Nm_SetChannelState(channel, NM_BUS_STATE_BUS_SLEEP); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
      Nm_SetChannelRequested(channel, NM_CHANNEL_RELEASED); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      for (busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(channel); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(channel); busNmIndex++)
#  endif
      {
        /* #35 Initialize Timers to zero */
        Nm_SetChannelActiveTimer(NM_CHANNEL_OR_BUSNM_IDX, 0u); /* SBSW_NM_CSL_TIMER_INDEX_ACCESS */
      }

#  if (NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF)
      Nm_GetChannelMode(channel)[NM_CHANNEL_MODE_INDEX_BUS_SLEEP]         = Nm_GetNmBusNmAssociationLengthOfChannelConfig(channel); /* SBSW_NM_CHANNELMODE_ARRAYWRITE */
      Nm_GetChannelMode(channel)[NM_CHANNEL_MODE_INDEX_PREPARE_BUS_SLEEP] = 0u; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */
      Nm_GetChannelMode(channel)[NM_CHANNEL_MODE_INDEX_NETWORK]           = 0u; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */

#   if (NM_STATE_CHANGE_IND_ENABLED == STD_ON)
      Nm_SetChPrevBusNmState(channel, NM_STATE_BUS_SLEEP); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
      Nm_GetChannelBusNmState(channel)[NM_STATE_UNINIT]    = 0u; /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
      Nm_GetChannelBusNmState(channel)[NM_STATE_BUS_SLEEP] = Nm_GetNmBusNmAssociationLengthOfChannelConfig(channel); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
      for (state = NM_STATE_PREPARE_BUS_SLEEP; state < NM_STATE_NUMBER_OF_STATES; state++)
      {
        Nm_GetChannelBusNmState(channel)[state] = 0u; /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
      }
#   endif
#   if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
      Nm_SetChRemSleepState(channel, Nm_GetNmBusNmAssociationLengthOfChannelConfig(channel)); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#   endif
#   if ( NM_OSEKNORMAL == STD_ON )
      Nm_SetOsekNormal(channel, 0u); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#   endif
#  endif
    }
#  if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
    Nm_SetNetworkRequested(0);
#  endif

# endif


  }

  /* #40 Set NM as initialized. */
  Nm_SetInitialized(TRUE);

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_INIT)
}
#endif

/**********************************************************************************************************************
 *  Nm_InitMemory()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
#if ( NM_INITIALIZATION_AVAILABLE == STD_ON )
FUNC( void, NM_CODE ) Nm_InitMemory( void )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set Nm as uninitialized. */
  Nm_SetInitialized(FALSE);

# if ( NM_USE_INIT_POINTER == STD_ON )
  /* #20 In the post-build variant: set config pointer to NULL (Nm not currently active in this variant). */
  Nm_ConfigPtr = NULL_PTR;
# endif

}
#endif

#if ( NM_MACRO_LAYER_ENABLED == STD_OFF ) 
/**********************************************************************************************************************
 *  Nm_PassiveStartUp()
 *********************************************************************************************************************/
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
 */
 FUNC( Std_ReturnType, NM_CODE ) Nm_PassiveStartUp( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
# endif
# if ( NM_PASSIVE_STARTUP_FORWARDING_ENABLED == STD_ON )
  VAR( boolean, AUTOMATIC )         callNetworkRequest;
# endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_PASSIVESTARTUP)
  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters. */
# if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
# endif
# if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
# endif
  if(
# if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
# else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
# endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
    /* \trace SPEC-4147 */
#  if ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF )
    /* #20 If the network is part of a cluster of coordinated networks: */
    if ( Nm_GetCoordinatorStateClusterIdxOfChannelConfig(NM_CHANNEL_IDX) != NM_NO_COORDINATORSTATECLUSTERIDXOFCHANNELCONFIG )
#  endif
    {

#  if ( NM_PASSIVE_STARTUP_FORWARDING_ENABLED == STD_OFF )
      /* #30 Abort shutdown and release the channel. */
      Nm_AbortShutdown(nmNetworkHandle);
#  endif


#  if ( NM_PASSIVE_STARTUP_FORWARDING_ENABLED == STD_ON )
      SchM_Enter_Nm_NM_EXCLUSIVE_AREA_1();
      callNetworkRequest = (boolean)(Nm_GetChannelRequested(NM_CHANNEL_IDX) == NM_CHANNEL_WAIT_FOR_PASSIVE_STARTUP); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */

      if (callNetworkRequest != FALSE)
#  endif
      {
        Nm_SetChannelRequested(NM_CHANNEL_IDX, NM_CHANNEL_READY_TO_RELEASE); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
      }
#  if ( NM_PASSIVE_STARTUP_FORWARDING_ENABLED == STD_ON )
      SchM_Exit_Nm_NM_EXCLUSIVE_AREA_1();
#  endif

#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      retVal = E_OK;
      /* #40 Iterate over all BusNms of the channel: 
             In case passive start-up forwarding enabled is turned off :
             Request the network by forwarding a call of <BusNm>_NetworkRequest to the lower layer. 
             In case passive start-up forwarding enabled is turned on  :
             Forward the request by calling the function <BusNm>_PassiveStartUp of the lower layer.              
       */
      for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#  endif
      {

#  if ( NM_PASSIVE_STARTUP_FORWARDING_ENABLED == STD_ON )
        if (callNetworkRequest == FALSE)
        {
#   if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
          if( (Nm_GetPassiveStartUpOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
          {
            errorId = NM_E_FUNCTION_PTR_IS_NULL;
#    if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
            /* There is no need to iterate over all BusNms */
            retVal = E_NOT_OK;
            break;
#    endif
          }
          else
#   endif
          {
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
            retVal = (Nm_GetPassiveStartUpOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#   else
            retVal |= (Nm_GetPassiveStartUpOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#   endif
          }
        }
        else
#  endif
        {
          /* ESCAN00074997: The next macro contains a return statement if NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON.
           * => BusNm_PassiveStartUp will not be called.
           */
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
          if( (Nm_GetNetworkRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
          {
            errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
            /* There is no need to iterate over all BusNms */
            retVal = E_NOT_OK;
            break; /* PRQA S 0771 */ /* MD_NM_Rule15.4 */
#   endif
          }
          else
#  endif
          {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
            retVal = (Nm_GetNetworkRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  else
            retVal |= (Nm_GetNetworkRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  endif
          }
        }
      }
    }
#  if ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF )
    /* #70 If the network is not part of a cluster of coordinated networks: */
    else
#  endif
# endif /* ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) */
# if ((NM_COORDINATOR_SUPPORT_ENABLED == STD_OFF) || ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF))
    {  
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      /* #80 In case there is no optimization for exactly one BusNm on a channel active, calculate the BusNm index
             that corresponds to the given channel.
             Trigger the transition from Bus-Sleep Mode to the Network Mode without
             requesting the network by forwarding a call of <BusNm>_PassiveStartUp to the lower layer. */
#   if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetPassiveStartUpOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX)))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
      }
      else
#   endif
      {
        retVal = (Nm_GetPassiveStartUpOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX)))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
      }
#  else
      /* #90 In case there is optimization for exactly one BusNm on a channel active,
             the parameter of the given function is the network number.
             Trigger the transition from Bus-Sleep Mode to the Network Mode.
             by calling <BusNm>_PassiveStartUp. */
#   if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetPassiveStartUpOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
      }
      else
#   endif
      {
        retVal = (Nm_GetPassiveStartUpOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_CHANNEL_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
      }
#  endif
    }
# endif

  }
  /* ----- Development Error Report --------------------------------------- */
# if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_PASSIVESTARTUP, errorId);
  }
# else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_PASSIVESTARTUP)

  return retVal;
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */


# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
/**********************************************************************************************************************
 *  Nm_NetworkRequest()
 *********************************************************************************************************************/
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
FUNC( Std_ReturnType, NM_CODE ) Nm_NetworkRequest( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{ 
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
#  endif
  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_NETWORKREQUEST)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters */
#  if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  /* #20 Check if NmPassiveMode is enabled on the channel. */
  /* ESCAN00087331 */
#  if (NM_NMPASSIVEMODEENABLEDOFCHANNELCONFIG == STD_ON )
  if( Nm_IsNmPassiveModeEnabledOfChannelConfig(NM_CHANNEL_IDX) )
  {
    errorId = NM_E_NOT_AVAILABLE_IN_PASSIVE_MODE;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 If the network handle is part of a cluster of coordinated networks: */
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
    /* \trace SPEC-4147 */
#   if ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF )
    if( Nm_GetCoordinatorStateClusterIdxOfChannelConfig(NM_CHANNEL_IDX) != NM_NO_COORDINATORSTATECLUSTERIDXOFCHANNELCONFIG )
#   endif
    {
    
#   if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
      SchM_Enter_Nm_NM_EXCLUSIVE_AREA_1();
#    if ( NM_NMCOORDINATORWITHNMFIATC == STD_ON )
      /* #40 If the network handle belongs to the coordinator cluster that has NmFiatC: */
      if(Nm_GetNmCoordinatorWithNmFiatC() == Nm_GetCoordinatorStateClusterIdxOfChannelConfig(NM_CHANNEL_IDX))
#    endif
      {
        /* #41 Inform NmFiatC if this is the first channel request by calling the internal network request */
        if (Nm_GetNetworkRequested() == 0u)
        {
          NmFiatC_InternalNetworkRequest();
        }
        /* #42 Store application request */
        Nm_SetNetworkRequested( (Nm_NetworkRequestedType)(Nm_GetNetworkRequested() | (Nm_NetworkRequestedType)((Nm_NetworkRequestedType)1u << (Nm_NetworkRequestedType)NM_CHANNEL_IDX))); 
      }
      SchM_Exit_Nm_NM_EXCLUSIVE_AREA_1();
#   endif
      /* #50 Abort Shutdown and request channel. */
      Nm_AbortShutdown(nmNetworkHandle);
      Nm_SetChannelRequested(NM_CHANNEL_IDX, NM_CHANNEL_REQUESTED); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
    }
#  endif /* ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) */
    
    
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    retVal = E_OK;
    /* #60 Iterate over all BusNms of the channel:
           Request the network by forwarding a call of <BusNm>_NetworkRequest to the lower layer. */
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#  endif
    {
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetNetworkRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        retVal = E_NOT_OK;
        break;
#   endif
      }
      else
#  endif
      {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
        retVal = (Nm_GetNetworkRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  else
        retVal |= (Nm_GetNetworkRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  endif
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_NETWORKREQUEST, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_NETWORKREQUEST)
  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  Nm_NetworkRelease()
 *********************************************************************************************************************/
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
 */
 FUNC( Std_ReturnType, NM_CODE ) Nm_NetworkRelease( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_NETWORKRELEASE)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters. */
#  if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  /* #20 Check if NmPassiveMode is enabled in the channel. */
  /* ESCAN00087331 */
#  if (NM_NMPASSIVEMODEENABLEDOFCHANNELCONFIG == STD_ON )
  if( Nm_IsNmPassiveModeEnabledOfChannelConfig(NM_CHANNEL_IDX) )
  {
    errorId = NM_E_NOT_AVAILABLE_IN_PASSIVE_MODE;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* \trace SPEC-4147 */
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF )
    /* #30 If the network is not part of a cluster of coordinated networks: */
    if( Nm_GetCoordinatorStateClusterIdxOfChannelConfig(NM_CHANNEL_IDX) == NM_NO_COORDINATORSTATECLUSTERIDXOFCHANNELCONFIG )
#  endif
    {
      /* #40 In case there is no optimization for exactly one BusNm on a channel active, calculate
       *              the BusNm index that corresponds to the given channel.
       *              Release the network by forwarding a call of <BusNm>_NetworkRelease to the lower layer.
       */
      /* #50 In case there is optimization for exactly one BusNm on a channel active, the parameter
             of the given function is the network number.
             Release the network by forwarding a call of <BusNm>_NetworkRelease to the lower layer.
       */

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_OFF) || ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF )

#   if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetNetworkReleaseOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_FIRST_BUSNM_INDEX_FOR_NETWORK_HANDLE))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
      }
      else
#   endif
      {
        retVal = (Nm_GetNetworkReleaseOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_FIRST_BUSNM_INDEX_FOR_NETWORK_HANDLE))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
      }

#  endif
    }
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF )
    else
#  endif
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
    {
      /* #60 Release the channel if it was requested before */
      if (Nm_GetChannelRequested(NM_CHANNEL_IDX) == NM_CHANNEL_REQUESTED)
      {

#   if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
#    if ( NM_NMCOORDINATORWITHNMFIATC == STD_ON )
        /* #70 If the network handle belongs to the coordinator cluster that has NmFiatC: */
        if(Nm_GetNmCoordinatorWithNmFiatC() == Nm_GetCoordinatorStateClusterIdxOfChannelConfig(NM_CHANNEL_IDX))
#    endif
        {
          SchM_Enter_Nm_NM_EXCLUSIVE_AREA_1();
          /* #71 Inform NmFiatC if this is the last channel request to be released by calling the internal network
           *     release
           */
          if (Nm_GetNetworkRequested() == (Nm_NetworkRequestedType)((Nm_NetworkRequestedType)1u << (Nm_NetworkRequestedType)NM_CHANNEL_IDX))
          {
            NmFiatC_InternalNetworkRelease();
          }
          /* #72 Store application release */
          Nm_SetNetworkRequested( (Nm_NetworkRequestedType)(Nm_GetNetworkRequested() & (Nm_NetworkRequestedType)(~((uint32_least)((Nm_NetworkRequestedType)1u << (Nm_NetworkRequestedType)NM_CHANNEL_IDX)))));
        
          SchM_Exit_Nm_NM_EXCLUSIVE_AREA_1();
        }
#   endif

        Nm_SetChannelRequested(NM_CHANNEL_IDX, NM_CHANNEL_READY_TO_RELEASE); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
      }
      retVal = E_OK;
    }
#  endif
  }
  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_NETWORKRELEASE, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_NETWORKRELEASE)
  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* NM_PASSIVE_MODE_ENABLED == STD_OFF */


# if ( NM_COM_CONTROL_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_DisableCommunication()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 */
 FUNC( Std_ReturnType, NM_CODE ) Nm_DisableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
#  endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_DISABLECOMMUNICATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters. */
#  if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    retVal = E_OK;
    /* #20 Iterate over all BusNms of the channel: Disable the Nm PDU transmission ability by forwarding
           a call of <BusNm>_DisableCommunication to the lower layer. */
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#  endif
    {
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetDisableCommunicationOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        retVal = E_NOT_OK;
        break;
#   endif
      }
      else
#  endif
      {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
        retVal = (Nm_GetDisableCommunicationOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  else
        retVal |= (Nm_GetDisableCommunicationOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  endif
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_DISABLECOMMUNICATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_DISABLECOMMUNICATION)

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  Nm_EnableCommunication()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
 FUNC( Std_ReturnType, NM_CODE ) Nm_EnableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
#  endif
  /* ----- Development Error Checks ------------------------------------- */
  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_ENABLECOMMUNICATION)
  /* #10 Check if Nm is initialized and the validity of the input parameters. */
#  if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    retVal = E_OK;
    /* #20 Iterate over all BusNms of the channel:
           Enable the Nm PDU transmission ability by forwarding
           a call of <BusNm>_EnableCommunication to the lower layer. */
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#  endif
    {
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetEnableCommunicationOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        retVal = E_NOT_OK;
        break;
#   endif
      }
      else
#  endif
      {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
        retVal = (Nm_GetEnableCommunicationOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  else
        retVal |= (Nm_GetEnableCommunicationOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  endif
      }
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_ENABLECOMMUNICATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_ENABLECOMMUNICATION)

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* NM_COM_CONTROL_ENABLED == STD_ON */


# if ( NM_USER_DATA_ENABLED == STD_ON )
#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_COM_USER_DATA_SUPPORT == STD_OFF )
/**********************************************************************************************************************
 *  Nm_SetUserData()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, NM_CODE ) Nm_SetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                               CONSTP2CONST( uint8, AUTOMATIC, NM_APPL_VAR ) nmUserDataPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
#   endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_SETUSERDATA)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters. */
#   if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#   endif
#   if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#   endif
  if(
#   if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#   else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#   endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  /* #20 Check if NmPassiveMode is enabled in the channel. */
  /* ESCAN00087331 */
#   if (NM_NMPASSIVEMODEENABLEDOFCHANNELCONFIG == STD_ON )
  if( Nm_IsNmPassiveModeEnabledOfChannelConfig(NM_CHANNEL_IDX) )
  {
    errorId = NM_E_NOT_AVAILABLE_IN_PASSIVE_MODE;
  }
  else
#   endif
  if( (nmUserDataPtr) == NULL_PTR )
  {
    /* \trace SPEC-19569 */
    errorId = NM_E_PARAM_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    retVal = E_OK;
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#   endif
    {
      /* #30 Iterate over all BusNms of the channel.
             Forward a call of <BusNm>_SetUserData to the lower layer
             and propagate the provided user data to all BusNms. */
#   if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetSetUserDataOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#    if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        retVal = E_NOT_OK;
        break;
#    endif
      }
      else
#   endif
      {
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
        retVal = (Nm_GetSetUserDataOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmUserDataPtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#   else
        retVal |= (Nm_GetSetUserDataOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmUserDataPtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#   endif
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#   if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_SETUSERDATA, errorId);
  }
#   else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#   endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_SETUSERDATA)

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

#  endif /* ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_COM_USER_DATA_SUPPORT == STD_OFF ) */


/**********************************************************************************************************************
 *  Nm_GetUserData()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
 FUNC( Std_ReturnType, NM_CODE ) Nm_GetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                               CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmUserDataPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
#  endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_GETUSERDATA)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters. */
#  if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  if( (nmUserDataPtr) == NULL_PTR )
  {
    /* \trace SPEC-19569 */
    errorId = NM_E_PARAM_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    retVal = E_OK;
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#  endif
    {
      /* #20 Iterate over all BusNms of the channel.
             Retrieve the user data of the last received NM message by calling the get user data
             function of the respective BusNm on the network.*/
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetGetUserDataOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        retVal = E_NOT_OK;
        break;
#   endif
      }
      else
#  endif
      {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
        retVal = (Nm_GetGetUserDataOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmUserDataPtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  else
        retVal |= (Nm_GetGetUserDataOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmUserDataPtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  endif
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_GETUSERDATA, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_GETUSERDATA)

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* NM_USER_DATA_ENABLED == STD_ON */


# if ( ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) )
/**********************************************************************************************************************
 *  Nm_GetPduData()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
 FUNC( Std_ReturnType, NM_CODE ) Nm_GetPduData( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                              CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmPduDataPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
#  endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_GETPDUDATA)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters. */
#  if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  if( (nmPduDataPtr) == NULL_PTR )
  {
    /* \trace SPEC-19569 */
    errorId = NM_E_PARAM_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    retVal = E_OK;
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#  endif
    {
      /* #20 Iterate over all BusNms of the channel.
             Retrieve the PDU data of the last received NM message by calling
             the get PDU data function of the respective BusNm on the network. */
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetGetPduDataOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        retVal = E_NOT_OK;
        break;
#   endif
      }
      else
#  endif
      {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
        retVal = (Nm_GetGetPduDataOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmPduDataPtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  else
        retVal |= (Nm_GetGetPduDataOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmPduDataPtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  endif
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_GETPDUDATA, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_GETPDUDATA)

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* ( ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) ) */


# if ( NM_NODE_DETECTION_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_RepeatMessageRequest()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Std_ReturnType, NM_CODE ) Nm_RepeatMessageRequest( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
#  endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_REPEATMESSAGEREQUEST)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters */
#  if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  /* #15 Check if NmPassiveMode is enabled on the channel. */
  /* ESCAN00087331 */
#  if (NM_NMPASSIVEMODEENABLEDOFCHANNELCONFIG == STD_ON )
  if( Nm_IsNmPassiveModeEnabledOfChannelConfig(NM_CHANNEL_IDX) )
  {
    errorId = NM_E_NOT_AVAILABLE_IN_PASSIVE_MODE;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    retVal = E_OK;
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#  endif
    {
      /* #20 Iterate over all BusNms of the channel.
             Forward the repeat message request by calling
             the repeat message request function of the respective BusNm on the network. */
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetRepeatMessageRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        retVal = E_NOT_OK;
        break;
#   endif
      }
      else
#  endif
      {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
        retVal = (Nm_GetRepeatMessageRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  else
        retVal |= (Nm_GetRepeatMessageRequestOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  endif
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_REPEATMESSAGEREQUEST, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif
  
  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_REPEATMESSAGEREQUEST)

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* ( NM_NODE_DETECTION_ENABLED == STD_ON ) */

# if ( NM_NODE_ID_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_GetNodeIdentifier()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
 FUNC( Std_ReturnType, NM_CODE ) Nm_GetNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                     CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmNodeIdPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
#  endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_GETNODEIDENTIFIER)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters */
#  if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  if( (nmNodeIdPtr) == NULL_PTR )
  {
    /* \trace SPEC-19569 */
    errorId = NM_E_PARAM_POINTER;
  }
  else
  {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    retVal = E_OK;
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#  endif
    {
      /* ----- Implementation ----------------------------------------------- */
      /* #20 Iterate over all BusNms of the channel.
             Determine the node identifier of the last received NM message by calling
             the get node identifier function of the respective BusNm on the network. */
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetGetNodeIdentifierOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        retVal = E_NOT_OK;
        break;
#   endif
      }
      else
#  endif
      {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
        retVal = (Nm_GetGetNodeIdentifierOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmNodeIdPtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  else
        retVal |= (Nm_GetGetNodeIdentifierOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmNodeIdPtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  endif
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_GETNODEIDENTIFIER, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_GETNODEIDENTIFIER)

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 *  Nm_GetLocalNodeIdentifier()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
 FUNC( Std_ReturnType, NM_CODE ) Nm_GetLocalNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                          CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmNodeIdPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
#  endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_GETLOCALNODEIDENTIFIER)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters */
#  if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  if( (nmNodeIdPtr) == NULL_PTR )
  {
    /* \trace SPEC-19569 */
    errorId = NM_E_PARAM_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    retVal = E_OK;
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#  endif
    {
      /* #20 Iterate over all BusNms of the channel.
             Determine the local node identifier by calling
             the get local node identifier function of the respective BusNm on the network. */
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetGetLocalNodeIdentifierOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        retVal = E_NOT_OK;
        break;
#   endif
      }
      else
#  endif
      {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
        retVal = (Nm_GetGetLocalNodeIdentifierOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmNodeIdPtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  else
        retVal |= (Nm_GetGetLocalNodeIdentifierOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmNodeIdPtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  endif
      }
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_GETLOCALNODEIDENTIFIER, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_GETLOCALNODEIDENTIFIER)

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */
# endif /* ( NM_NODE_ID_ENABLED == STD_ON ) */


# if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_CheckRemoteSleepIndication()
 *********************************************************************************************************************/
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
 */
FUNC( Std_ReturnType, NM_CODE ) Nm_CheckRemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                               CONSTP2VAR( boolean, AUTOMATIC, NM_APPL_VAR ) nmRemoteSleepIndPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
  VAR( boolean, AUTOMATIC )         remoteSleepInd = TRUE;
  VAR( boolean, AUTOMATIC )         overallRemoteSleepInd = TRUE;
#  endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_CHECKREMOTESLEEPINDICATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters */
#  if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  /* #15 Check if NmPassiveMode is enabled on the channel. */
  /* ESCAN00087331 */
#  if (NM_NMPASSIVEMODEENABLEDOFCHANNELCONFIG == STD_ON )
  if( Nm_IsNmPassiveModeEnabledOfChannelConfig(NM_CHANNEL_IDX) )
  {
    errorId = NM_E_NOT_AVAILABLE_IN_PASSIVE_MODE;
  }
  else
#  endif
  if( (nmRemoteSleepIndPtr) == NULL_PTR )
  {
    /* \trace SPEC-19569 */
    errorId = NM_E_PARAM_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    retVal = E_OK;
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#  endif
    {
      /* #20 Iterate over all BusNms of the channel.
             Determine the remote sleep status by calling
             the check remote sleep indication function of the respective BusNm on the network. */
#  if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetCheckRemoteSleepIndicationOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        retVal = E_NOT_OK;
        break;
#   endif
      }
      else
#  endif
      {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        retVal |= (Nm_GetCheckRemoteSleepIndicationOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,(P2VAR(boolean,AUTOMATIC,AUTOMATIC))&remoteSleepInd)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
        overallRemoteSleepInd &= remoteSleepInd;
#  else
        retVal = (Nm_GetCheckRemoteSleepIndicationOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmRemoteSleepIndPtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
#  endif
      }
    }

    /* #30 Copy the overall remote sleep status to the output parameter.
     *            The value was calculated by using the AND operation over the remote sleep status of all channels
     */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    if (retVal == E_OK)
    {
      *nmRemoteSleepIndPtr = overallRemoteSleepInd; /* SBSW_NM_CHECKREMOTESLEEP */
    }
#  endif
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_CHECKREMOTESLEEPINDICATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_CHECKREMOTESLEEPINDICATION)

  return retVal;
}  /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */
# endif /* ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) */


/**********************************************************************************************************************
 *  Nm_GetState()
 *********************************************************************************************************************/
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
 */


FUNC( Std_ReturnType, NM_CODE ) Nm_GetState( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                             CONSTP2VAR( Nm_StateType, AUTOMATIC, NM_APPL_VAR ) nmStatePtr, 
                                             CONSTP2VAR( Nm_ModeType, AUTOMATIC, NM_APPL_VAR ) nmModePtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( Std_ReturnType, AUTOMATIC )  retVal = E_NOT_OK;
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
  VAR( Nm_StateType, AUTOMATIC )    state = NM_STATE_UNINIT;
  VAR( Nm_StateType, AUTOMATIC )    busNmMaxState = NM_STATE_UNINIT;
  VAR( Nm_ModeType, AUTOMATIC )     mode = NM_MODE_BUS_SLEEP;
  VAR( Nm_ModeType, AUTOMATIC )     busNmMaxMode = NM_MODE_BUS_SLEEP;
# endif


  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_GETSTATE)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters */
# if (NM_INITIALIZATION_AVAILABLE == STD_ON) /* COV_NM_INITIALIZATION_AVAILABLE */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
# endif
# if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
# endif
  if(
# if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
# else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
# endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  if(( (nmStatePtr) == NULL_PTR ) || ( (nmModePtr) == NULL_PTR ))
  {
    /* \trace SPEC-19569 */
    errorId = NM_E_PARAM_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    retVal = E_OK;
    /* #20 Iterate over all BusNms of the channel: */
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
# endif
    {
      /* #30 If optimization for exactly one BusNm on a channel is off:    Determine the NM state and 
       *               the NM mode by calling the get state function of the respective BusNm on
       *               the network in order to calculate the maximum state and mode.
       *               If optimization for exactly one BusNm on a channel is on:     Determine the NM state and
       *               the NM mode by calling the get state function of
       *               the respective BusNm on the network.
       */
# if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
      if( (Nm_GetGetStateOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))) == NULL_PTR ) /* COV_NM_NULLFUNCTION */
      {
        errorId = NM_E_FUNCTION_PTR_IS_NULL;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        /* There is no need to iterate over all BusNms */
        retVal = E_NOT_OK;
        break;
#  endif
      }
      else
# endif
      {
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )

        retVal |= (Nm_GetGetStateOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,(P2VAR(Nm_StateType,AUTOMATIC,AUTOMATIC))&state,(P2VAR(Nm_ModeType,AUTOMATIC,AUTOMATIC))&mode)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */

        if (state > busNmMaxState)
        {
          busNmMaxState = state;
        }

        if (mode > busNmMaxMode)
        {
          busNmMaxMode = mode;
        }
# else
        retVal = (Nm_GetGetStateOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_BUSNM_IDX))(nmNetworkHandle,nmStatePtr,nmModePtr)); /* SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL */
# endif
      }
    }

# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    if (retVal == E_OK)
    {
      /* #40 If BusNm optimization for exactly one BusNm on a channel is off, pass the calculated values to the pointers. */
      *nmStatePtr = busNmMaxState; /* SBSW_NM_GETSTATE */
      *nmModePtr = busNmMaxMode; /* SBSW_NM_GETSTATE */
    }
# endif
  }
  /* ----- Development Error Report --------------------------------------- */
# if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_GETSTATE, errorId);
  }
# else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_GETSTATE)

  return retVal;
} /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */

#endif /* else ( NM_MACRO_LAYER_ENABLED == STD_OFF ) */


#if ( NM_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  Nm_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, NM_APPL_VAR ) nmVerInfoPtr )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_GETVERSIONINFO)

  /* ----- Development Error Checks ------------------------------------- */
# if (NM_DEV_ERROR_DETECT == STD_ON) /* COV_NM_DEV_ERROR_DETECT_ON */
  /* ESCAN00078910 */
  /* #20 Check versioninfo for NULL pointer. Note: no uninit check is performed. */
  if( (nmVerInfoPtr) == NULL_PTR )
  {
    /* \trace SPEC-19569 */
    errorId = NM_E_PARAM_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Set versioninfo with corresponding macros from component header. */
    nmVerInfoPtr->vendorID = NM_VENDOR_ID; /* SBSW_NM_VERSIONINFO_PTRWRITE */
    nmVerInfoPtr->moduleID = NM_MODULE_ID; /* SBSW_NM_VERSIONINFO_PTRWRITE */
    nmVerInfoPtr->sw_major_version = NM_SW_MAJOR_VERSION; /* SBSW_NM_VERSIONINFO_PTRWRITE */
    nmVerInfoPtr->sw_minor_version = NM_SW_MINOR_VERSION; /* SBSW_NM_VERSIONINFO_PTRWRITE */
    nmVerInfoPtr->sw_patch_version = NM_SW_PATCH_VERSION; /* SBSW_NM_VERSIONINFO_PTRWRITE */
  }

 /* ----- Development Error Report --------------------------------------- */
# if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_GETVERSIONINFO, errorId);
  }
# else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_GETVERSIONINFO)
}
#endif /* ( NM_VERSION_INFO_API == STD_ON ) */


/**********************************************************************************************************************
 *  Call-back notifications - Standard Call-back notifications
 *********************************************************************************************************************/
#if ( NM_MACRO_LAYER_ENABLED == STD_ON )
/* Callback Functions directly redefined to ComM in Nm_Cbk.h */
/* \trace DSGN-Nm22880 */
#else


/*********************************************************************************************************************
 *  Nm_NetworkStartIndication()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_NetworkStartIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_NETWORKSTARTINDICATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters */
# if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
# endif
  if(
# if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
# else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
# endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* ESCAN00075012 */
    /* #20 Notify a network start to the ComM Module */
    ComM_Nm_NetworkStartIndication( nmNetworkHandle );
  }

  /* ----- Development Error Report --------------------------------------- */
# if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_NETWORKSTARTINDICATION, errorId);
  }
# else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_NETWORKSTARTINDICATION)

}


/**********************************************************************************************************************
 *  Nm_NetworkMode()
 *********************************************************************************************************************/
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
 */
FUNC( void, NM_CODE ) Nm_NetworkMode( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
  
  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_NETWORKMODE)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters */
# if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
# endif
  if(
# if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
# else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
# endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {

    /* ----- Implementation ----------------------------------------------- */
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Enter_Nm_NM_EXCLUSIVE_AREA_1();

    /* #20 If not all BusNms have entered Network Mode previously:
           Indicate that Network Mode has been entered
           If there is one or more channels in sleep mode and in prepare sleep mode:
             Resolve ambiguity: one of the BusNms has either left Prepare Bus Sleep Mode or Bus Sleep Mode
           If there is no channel in Bus Sleep Mode:
             Indicate that Prepare Bus Sleep Mode has been left
           If there is one or more channels in Sleep Mode, but no channel in Prepare Bus Sleep Mode:
             Indicate that Prepare Bus Sleep Mode has been left */
    if (Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_NETWORK] < Nm_GetNmBusNmAssociationLengthOfChannelConfig(NM_CHANNEL_IDX))
# endif
    {
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_NETWORK]++; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */

      if (Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_BUS_SLEEP] > 0u)
      {
        if (Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_PREPARE_BUS_SLEEP] > 0u)
        {
          Nm_RecalculateChannelMode(nmNetworkHandle);
        }
        else
        {
          Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_BUS_SLEEP]--; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */
        }
      }
      else
      {
        Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_PREPARE_BUS_SLEEP]--; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */
      }
# endif
# if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
      
      /* Is this channel NmFiatC ? */
      if(Nm_GetPassiveStartUpOfNmFunctionTable(NM_BUSNM_CALL_FUNCTION_TABLE_INDEX(NM_NETWORK_HANDLE_OR_FIRST_BUSNM_IDX)) == NmFiatC_PassiveStartUp)
      {
        /* Only notify network mode to the ComM module */
        ComM_Nm_NetworkMode( nmNetworkHandle );
      }
      else
# endif
      {
        /* #30 If this BusNm is the first BusNm that has entered Network Mode:
               Reset the Remote Sleep State to the initial value:
               number of BusNms that are Channel Sleep Masters.
               Wake the channels and abort shut down
               Notify network mode to the ComM module */
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        if (Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_NETWORK] == 1u)
# endif
        {
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
          Nm_SetChRemSleepState(NM_CHANNEL_IDX, Nm_InitialRemoteSleepStateAfterNetworkMode(NM_CHANNEL_IDX)); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
# endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
          /* \trace SPEC-4147 */
#  if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
          Nm_SetChannelState(NM_CHANNEL_IDX, NM_BUS_STATE_BUS_AWAKE); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#  else
          Nm_SetChannelState(NM_CHANNEL_IDX, NM_BUS_STATE_READY_TO_SLEEP); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#  endif
          Nm_AbortShutdown(nmNetworkHandle);
# endif
          ComM_Nm_NetworkMode( nmNetworkHandle );
        }
      }
    }
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Exit_Nm_NM_EXCLUSIVE_AREA_1();
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_NETWORKMODE, errorId);
  }
# else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_NETWORKMODE)
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/**********************************************************************************************************************
 *  Nm_BusSleepMode()
 *********************************************************************************************************************/
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
 */
FUNC( void, NM_CODE ) Nm_BusSleepMode( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8, AUTOMATIC ) previousNetworkMode;
# endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_BUSSLEEPMODE)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters */
# if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
# endif
  if(
# if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
# else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
# endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Enter_Nm_NM_EXCLUSIVE_AREA_1();

    /* #20 If not all BusNms have entered Bus Sleep Mode previously:
           Indicate that Bus Sleep Mode has been entered
           If there is one or more channels in Network Mode and in Prepare Sleep mode:
             Resolve ambiguity: one of the BusNms has either left Network Mode or Prepare Sleep Mode
           If there is no channel in Network Mode:
             Indicate that Prepare Bus Sleep Mode has been left
           If there is one or more channels in Network Mode, but no channel in Prepare Bus Sleep Mode:
             Indicate that Network Mode has been left */
    if (Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_BUS_SLEEP] < Nm_GetNmBusNmAssociationLengthOfChannelConfig(NM_CHANNEL_IDX))
# endif
    {
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_BUS_SLEEP]++; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */
      previousNetworkMode = Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_NETWORK];

      if (previousNetworkMode > 0u)
      {
        if (Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_PREPARE_BUS_SLEEP] > 0u)
        {
          Nm_RecalculateChannelMode(nmNetworkHandle);
        }
        else
        {
          Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_NETWORK]--; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */
        }
      }
      else
      {
        Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_PREPARE_BUS_SLEEP]--; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */
      }

      /* If all BusNms have entered Bus Sleep Mode: Set the channel state to bus sleep */
      if (Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_BUS_SLEEP] == Nm_GetNmBusNmAssociationLengthOfChannelConfig(NM_CHANNEL_IDX))
# endif
      {

        Nm_BusSleepModeAuxFunc(nmNetworkHandle, &errorId); /* SBSW_NM_ERRORID_AS_PARAMETER_CALL */

      }
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      /* #130 If this BusNm is the last one that has left Network Mode
              but there is still one BusNm in Prepare Bus Sleep Mode: */
      else if ((Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_NETWORK] == 0u) && (previousNetworkMode > 0u))
      {
        /* #140 Notify that the network management has entered Prepared Bus-Sleep Mode to the ComM module */
        Nm_SetChannelState(NM_CHANNEL_IDX, NM_BUS_STATE_PREPARE_BUS_SLEEP); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
        ComM_Nm_PrepareBusSleepMode(nmNetworkHandle);
      }
      else
      {
        /* Intentionally left empty */
      }
# endif
    }
  
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Exit_Nm_NM_EXCLUSIVE_AREA_1();
# endif
  }

  /* ----- Development Error Report --------------------------------------- */
# if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_BUSSLEEPMODE, errorId);
  }
# else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_BUSSLEEPMODE)
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */


# if ( NM_OPTIMIZE_NO_PREPARE_BUS_SLEEP_MODE == STD_OFF )
/*********************************************************************************************************************
 *  Nm_PrepareBusSleepMode()
 *********************************************************************************************************************/
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
 */
FUNC( void, NM_CODE ) Nm_PrepareBusSleepMode( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_PREPAREBUSSLEEPMODE)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Enter_Nm_NM_EXCLUSIVE_AREA_1();

    /* #20 If not all BusNms have entered Prepare Bus Sleep Mode previously and at least one BusNm is in Network Mode: */
    if ((Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_PREPARE_BUS_SLEEP] <  
         Nm_GetNmBusNmAssociationLengthOfChannelConfig(NM_CHANNEL_IDX)) && 
        (Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_NETWORK] > 0u)) 
#  endif
    {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      /* #30 Indicate that prepare bus sleep has been entered */
      Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_PREPARE_BUS_SLEEP]++; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */
      Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_NETWORK]--; /* SBSW_NM_CHANNELMODE_ARRAYWRITE */

      /* #40 If this is the last BusNm that has left Network Mode:
             Set the channel state as prepare bus sleep.
             Notify that the network management has entered Prepare Bus-Sleep Mode to the ComM module */
      if (Nm_GetChannelMode(NM_CHANNEL_IDX)[NM_CHANNEL_MODE_INDEX_NETWORK] == 0u)
#  endif
      {
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
        /* \trace SPEC-4147 */
        Nm_SetChannelState(NM_CHANNEL_IDX, NM_BUS_STATE_PREPARE_BUS_SLEEP); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#  endif

        ComM_Nm_PrepareBusSleepMode( nmNetworkHandle );
      }
    }

#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Exit_Nm_NM_EXCLUSIVE_AREA_1();
#  endif
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_PREPAREBUSSLEEPMODE, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_PREPAREBUSSLEEPMODE)
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
# endif

# if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_RemoteSleepIndication()
 *********************************************************************************************************************/
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
 */
FUNC( void, NM_CODE ) Nm_RemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_REMOTESLEEPINDICATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Enter_Nm_NM_EXCLUSIVE_AREA_1();
    /* #20 If not all BusNms have entered Remote Sleep State previously: */
    if (Nm_GetChRemSleepState(NM_CHANNEL_IDX) < Nm_GetNmBusNmAssociationLengthOfChannelConfig(NM_CHANNEL_IDX))
#  endif
    {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      /* #30 Increment the variable that counts the number of remote sleep states for the given channel */
      Nm_IncChRemSleepState(NM_CHANNEL_IDX); /* SBSW_NM_CSL_INCREMENT_DECREMENT_INDEX_ACCESS */
      /* #40 If this BusNm is the last BusNm that has entered Remote Sleep State:
               Set channel state as ready to sleep
               Forward call to upper layer */
      if (Nm_GetChRemSleepState(NM_CHANNEL_IDX) == Nm_GetNmBusNmAssociationLengthOfChannelConfig(NM_CHANNEL_IDX))
#  endif
      {
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
        /* \trace SPEC-4147, SPEC-4176 */
        Nm_SetChannelState(NM_CHANNEL_IDX, NM_BUS_STATE_READY_TO_SLEEP); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#  endif

#  if defined ( UL_Nm_RemoteSleepIndication )
        UL_Nm_RemoteSleepIndication(nmNetworkHandle);
#  else
#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_OFF )
        NM_DUMMY_STATEMENT_CONST(nmNetworkHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#   endif
#  endif
      }
    }

#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Exit_Nm_NM_EXCLUSIVE_AREA_1();
#  endif
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_REMOTESLEEPINDICATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_REMOTESLEEPINDICATION)
} 


/**********************************************************************************************************************
 *  Nm_RemoteSleepCancellation()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_RemoteSleepCancellation( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_REMOTESLEEPCANCELLATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters. */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Enter_Nm_NM_EXCLUSIVE_AREA_1();

    if (Nm_GetChRemSleepState(NM_CHANNEL_IDX) > 0u)
#  endif
    {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      /* #20 Indicate that one remote sleep indication has been left for the corresponding channel */
      Nm_DecChRemSleepState(NM_CHANNEL_IDX); /* SBSW_NM_CSL_INCREMENT_DECREMENT_INDEX_ACCESS */
      /* #30 If this BusNm is the first BusNm that has left the Remote Sleep State:
               Set channel state as awake and abort shut down
               Forward call to upper layer */
      if (Nm_GetChRemSleepState(NM_CHANNEL_IDX) ==
         (uint8)(Nm_GetNmBusNmAssociationLengthOfChannelConfig(NM_CHANNEL_IDX) - 1u))
#  endif
      {
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
        /* \trace SPEC-4147 */
        Nm_SetChannelState(NM_CHANNEL_IDX, NM_BUS_STATE_BUS_AWAKE); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
        Nm_AbortShutdown(nmNetworkHandle);
#  endif

#  if defined ( UL_Nm_RemoteSleepCancellation )
        UL_Nm_RemoteSleepCancellation(nmNetworkHandle);
#  else
#   if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_OFF )
        NM_DUMMY_STATEMENT_CONST(nmNetworkHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#   endif
#  endif
      }
    }

#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Exit_Nm_NM_EXCLUSIVE_AREA_1();
#  endif
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_REMOTESLEEPCANCELLATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_REMOTESLEEPCANCELLATION)
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

# endif /* ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) */


# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_SynchronizationPoint()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_SynchronizationPoint( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_SYNCHRONIZATIONPOINT)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_NO_SYNC_CHANNEL == STD_OFF )
#   if ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF ) || ( NM_OPTIMIZE_ALL_SYNC_CHANNEL == STD_OFF )
    if(
#    if ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF )
        /* #20 If the network is part of a cluster of coordinated networks: */
        ( Nm_GetCoordinatorStateClusterIdxOfChannelConfig(NM_CHANNEL_IDX) != NM_NO_COORDINATORSTATECLUSTERIDXOFCHANNELCONFIG )
#     if ( NM_OPTIMIZE_ALL_SYNC_CHANNEL == STD_OFF )
        &&
#     endif
#    endif
#    if ( NM_OPTIMIZE_ALL_SYNC_CHANNEL == STD_OFF )
        ( Nm_IsNmSynchronizingNetworkOfChannelConfig(NM_CHANNEL_IDX) ) /* ESCAN00073359 */
#    endif
      )
#   endif
    {
      SchM_Enter_Nm_NM_EXCLUSIVE_AREA_0();
      /* \trace SPEC-4153 */
      if (Nm_GetCoordinatorState(Nm_GetCoordinatorStateClusterIdxOfChannelConfig(NM_CHANNEL_IDX)) == NM_COORDINATOR_WAIT_FOR_SYNC)
      {
        /* #30 Set the state of the coordinator as "start timers"
               in case the previous state was waiting for synchronization */
        Nm_SetCoordinatorState(Nm_GetCoordinatorStateClusterIdxOfChannelConfig(NM_CHANNEL_IDX), NM_COORDINATOR_START_TIMERS); /* SBSW_NM_CSL_COORDINATOR_INDEX_ACCESS */
      }
      SchM_Exit_Nm_NM_EXCLUSIVE_AREA_0();
    }
#  else
    NM_DUMMY_STATEMENT_CONST(nmNetworkHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_SYNCHRONIZATIONPOINT, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_SYNCHRONIZATIONPOINT)
} 
# endif /* NM_COORDINATOR_SUPPORT_ENABLED == STD_ON */

/**********************************************************************************************************************
 *  Call-back notifications - Extra Call-back notifications
 *********************************************************************************************************************/

# if ( NM_CAR_WAKE_UP_RX_ENABLED == STD_ON )
/**********************************************************************************************************************
 * Nm_CarWakeUpIndication()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_CarWakeUpIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_CARWAKEUPINDICATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters. */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Forward call to upper layer. */
#  if (NM_CARWAKEUPCALLBACKFCTPTR == STD_ON) /* COV_NM_UL_NULLFUNCTION */
    if(Nm_GetCarWakeUpCallbackFctPtr() != NULL_PTR) /* COV_NM_CONFIG_FUNC_CALL */
    {
      Nm_GetCarWakeUpCallbackFctPtr()(nmNetworkHandle); /* SBSW_NM_CONFIG_FUNC_CALL */
    }
#  endif
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_CARWAKEUPINDICATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif
  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_CARWAKEUPINDICATION)
} 
# endif

# if ( NM_PDU_RX_INDICATION_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_PduRxIndication()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_PduRxIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR( uint8_least, AUTOMATIC )     busNmIndex;
#  endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_PDURXINDICATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters. */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_PDURXINDICATIONOFCHANNELCONFIG == STD_ON ) || ( NM_PDURXINDICATIONOFNMBUSNMASSOCIATION == STD_ON ) /* COV_NM_COMSTACKLIB_GEN */

#   if (NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF && NM_PDURXINDICATIONOFNMBUSNMASSOCIATION == STD_ON)
    for ( busNmIndex = Nm_GetNmBusNmAssociationStartIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex < Nm_GetNmBusNmAssociationEndIdxOfChannelConfig(NM_CHANNEL_IDX); busNmIndex++ )
#   endif
    {
      CONST(Nm_CallbackFunctionWithPduInfoType, AUTOMATIC) callbackFunction = NM_BUSNM_GET_PDU_RX_INDICATION(NM_NETWORK_HANDLE_OR_BUSNM_IDX);
      if (callbackFunction != NULL_PTR) /* COV_NM_CONFIG_FUNC_CALL */ 
      {
        callbackFunction(nmNetworkHandle, NULL_PTR); /* SBSW_NM_CONFIG_FUNC_CALL */
      }
    }
#  endif

#  if defined ( UL_Nm_PduRxIndication )
    /* #20 Forward call to upper layer */
    UL_Nm_PduRxIndication( nmNetworkHandle );
#  else
    NM_DUMMY_STATEMENT_CONST(nmNetworkHandle); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_PDURXINDICATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_PDURXINDICATION)
} 
# endif

# if (NM_BUSNM_SPECIFIC_PDU_RX_INDICATION_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Nm_BusNmSpecificPduRxIndication()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_BusNmSpecificPduRxIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle,
#  if (NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF)
                                                       CONST( uint8, AUTOMATIC ) busNmIndex,
#  endif
                                                       CONSTP2CONST( PduInfoType, AUTOMATIC, AUTOMATIC) pduInfo )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;


  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_BUSNMSPECIFICPDURXINDICATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters. */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
#  if (NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF)
  if (busNmIndex >= Nm_GetSizeOfNmBusNmAssociation())
  {
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
#  endif
  if( (pduInfo) == NULL_PTR )
  {
    /* \trace SPEC-19569 */
    errorId = NM_E_PARAM_POINTER;
  }
  else
  if( (pduInfo->SduDataPtr) == NULL_PTR )
  {
    /* \trace SPEC-19569 */
    errorId = NM_E_PARAM_POINTER;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if (NM_PDURXINDICATIONOFCHANNELCONFIG == STD_ON) || (NM_PDURXINDICATIONOFNMBUSNMASSOCIATION == STD_ON) /* COV_NM_COMSTACKLIB_GEN */
    CONST(Nm_CallbackFunctionWithPduInfoType, AUTOMATIC) callbackFunction = NM_BUSNM_GET_PDU_RX_INDICATION(NM_NETWORK_HANDLE_OR_BUSNM_IDX);
    if (callbackFunction != NULL_PTR) /* COV_NM_CONFIG_FUNC_CALL */
    {
      /* #20 Forward call to upper layer */
      callbackFunction(nmNetworkHandle, pduInfo); /* SBSW_NM_CONFIG_FUNC_CALL */
    }
#  endif

  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_BUSNMSPECIFICPDURXINDICATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_BUSNMSPECIFICPDURXINDICATION)
} /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
# endif


# if ( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_StateChangeNotification()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_StateChangeNotification( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmPreviousState, 
                                                  CONST( Nm_StateType,      AUTOMATIC ) nmCurrentState )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  VAR(Nm_StateType, AUTOMATIC) newBusNmMaxState;
#  endif

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_STATECHANGENOTIFICATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters. */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  if (nmCurrentState == nmPreviousState)
  {
    errorId = NM_E_SAME_STATES;
  }
  else
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
  if ((nmPreviousState >= NM_STATE_NUMBER_OF_STATES) ||
      (nmCurrentState >= NM_STATE_NUMBER_OF_STATES) ||
      (Nm_GetChannelBusNmState(NM_CHANNEL_IDX)[nmCurrentState] >= Nm_GetNmBusNmAssociationLengthOfChannelConfig(NM_CHANNEL_IDX)) ||
      (Nm_GetChannelBusNmState(NM_CHANNEL_IDX)[nmPreviousState] <= 0u))
  {
    errorId = NM_E_INVALID_STATE;
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    /* #20 Calculate the new overall state */ 
    newBusNmMaxState = Nm_StateChangeNotAux_OverallState(nmNetworkHandle, nmPreviousState, nmCurrentState);
    
    /* #30 If there has been an overall state change: */
    if (newBusNmMaxState < NM_STATE_NUMBER_OF_STATES)
#  endif
    {
#  if ( NM_STATE_CHANGE_REPORT_ENABLED == STD_ON )
      Nm_StateChangeNotAux_ReportState( nmNetworkHandle, 
#   if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
        newBusNmMaxState
#   else
        nmPreviousState, nmCurrentState
#   endif
      );
#  endif /* (NM_STATE_CHANGE_REPORT_ENABLED == STD_ON ) */

      
#  if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
      /* #40 FiatC check previous and current mode, special NetworkMode handling */
      Nm_StateChangeNotAux_NmFiatCAbortShutdown( nmNetworkHandle, nmPreviousState, nmCurrentState );
#  endif


#  if defined ( UL_Nm_StateChangeNotification )
      /* #50 Call the upper layer state change notification */
      UL_Nm_StateChangeNotification( nmNetworkHandle, NM_PREVIOUS_STATE, NM_CURRENT_STATE );
#  endif

#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      Nm_SetChPrevBusNmState(NM_CHANNEL_IDX, newBusNmMaxState); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
#  endif
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_STATECHANGENOTIFICATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_STATECHANGENOTIFICATION)
}  /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCAL, MD_MSR_STCYC, MD_MSR_STMIF */
# endif


# if ( NM_REPEAT_MSG_IND_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_RepeatMessageIndication()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_RepeatMessageIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_REPEATMESSAGEINDICATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters. */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if defined ( UL_Nm_RepeatMessageIndication )
    /* #20 Forward call to upper layer */
    UL_Nm_RepeatMessageIndication( nmNetworkHandle );
#  endif
  
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_REPEATMESSAGEINDICATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_REPEATMESSAGEINDICATION)
} 
# endif


# if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
/**********************************************************************************************************************
 *  Nm_TxTimeoutException()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_TxTimeoutException( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_TXTIMEOUTEXCEPTION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters. */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
     /* ----- Implementation ----------------------------------------------- */
#  if defined ( UL_Nm_TxTimeoutException )
    /* #20 Forward call to upper layer */
    UL_Nm_TxTimeoutException( nmNetworkHandle );
#  endif
  }
  
  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_TXTIMEOUTEXCEPTION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_TXTIMEOUTEXCEPTION)
}
# endif



# if ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  Nm_CoordReadyToSleepIndication()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_CoordReadyToSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_COORDREADYTOSLEEPINDICATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters. */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Enter_Nm_NM_EXCLUSIVE_AREA_1();
    /* #20 If not all BusNms have entered Remote Sleep State previously: */
    if (Nm_GetChRemSleepState(NM_CHANNEL_IDX) < Nm_GetNmBusNmAssociationLengthOfChannelConfig(NM_CHANNEL_IDX))
#  endif
    {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      /* #30 Increment the variable that counts the number of remote sleep states for the given channel */
      Nm_IncChRemSleepState(NM_CHANNEL_IDX); /* SBSW_NM_CSL_INCREMENT_DECREMENT_INDEX_ACCESS */
      /* #40 If this BusNm is the last BusNm that has entered Remote Sleep State: */
      if (Nm_GetChRemSleepState(NM_CHANNEL_IDX) == Nm_GetNmBusNmAssociationLengthOfChannelConfig(NM_CHANNEL_IDX))
#  endif
      {
        /* #50 Set channel state as ready to sleep */
        /* \trace SPEC-4176 */
        Nm_SetChannelState(NM_CHANNEL_IDX, NM_BUS_STATE_READY_TO_SLEEP); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
      }
    }

#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Exit_Nm_NM_EXCLUSIVE_AREA_1();
#  endif
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_COORDREADYTOSLEEPINDICATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_COORDREADYTOSLEEPINDICATION)
} 


/**********************************************************************************************************************
 *  Nm_CoordReadyToSleepCancellation()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_CoordReadyToSleepCancellation( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;

  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_COORDREADYTOSLEEPCANCELLATION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check the validity of the input parameters. */
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  endif
  if(
#  if ( NM_SYSTONMCHIND == STD_ON )
      (nmNetworkHandle >= Nm_GetSizeOfSysToNmChInd()) || (NM_CHANNEL_IDX >= Nm_GetSizeOfChannelConfig())
#  else
      (nmNetworkHandle >= Nm_GetSizeOfChannelConfig())
#  endif
    )
  {
    /* \trace SPEC-4237 */
    errorId = NM_E_HANDLE_UNDEF;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Enter_Nm_NM_EXCLUSIVE_AREA_1();

    if (Nm_GetChRemSleepState(NM_CHANNEL_IDX) > 0u)
#  endif
    {
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
      /* #20 One remote sleep indication has been left for the corresponding channel, thus
             decrement the variable that counts the number channel remote sleep states */
      Nm_DecChRemSleepState(NM_CHANNEL_IDX); /* SBSW_NM_CSL_INCREMENT_DECREMENT_INDEX_ACCESS */
      /* #30 If this BusNm is the first BusNm that has left the Remote Sleep State:
             Set channel state as awake and abort shut down */
      if (Nm_GetChRemSleepState(NM_CHANNEL_IDX) ==
         (uint8)(Nm_GetNmBusNmAssociationLengthOfChannelConfig(NM_CHANNEL_IDX) - 1u))
#  endif
      {
        Nm_SetChannelState(NM_CHANNEL_IDX, NM_BUS_STATE_BUS_AWAKE); /* SBSW_NM_CSL_CHANNEL_INDEX_ACCESS */
        Nm_AbortShutdown(nmNetworkHandle);
      }
    }
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
    SchM_Exit_Nm_NM_EXCLUSIVE_AREA_1();
#  endif
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_COORDREADYTOSLEEPCANCELLATION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_COORDREADYTOSLEEPCANCELLATION)
}/* PRQA S 6050 */ /* MD_MSR_STCAL */
# endif /* ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON ) */


# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_MainFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, NM_CODE ) Nm_MainFunction( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR( uint8, AUTOMATIC )           errorId = NM_E_NO_ERROR;
  VAR( uint8_least, AUTOMATIC ) coordinator;
  VAR( uint8, AUTOMATIC ) nextState;


  Nm_Rtm_Start(RtmMeasurementPoint_NM_SID_MAINFUNCTION)

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if Nm is initialized and the validity of the input parameters */
  /* If coordination is on, the initialization is always available */
  if (Nm_GetInitialized() == FALSE)
  {
    errorId = NM_E_UNINIT;
  }
  else
#  if ( NM_USE_INIT_POINTER == STD_ON )
  if (Nm_ConfigPtr == NULL_PTR)
  {
    /* Do nothing, the Nm is not active for this variant */
  }
  else
#  endif
  {
    /* ----- Implementation ----------------------------------------------- */

    for (coordinator = 0u; coordinator < Nm_GetSizeOfCoordinatorState(); coordinator++)
    {
      nextState = NM_COORDINATOR_NO_STATE_CHANGE;


      /* #30 Management of the Nm Coordinator state machine */
      switch(Nm_GetCoordinatorState(coordinator))
      {
        case NM_COORDINATOR_SHUT_DOWN: /* ESCAN00075311 */
          nextState = Nm_MainAux_NmCoordShutDown(NM_COORDINATOR_PARA_ONLY);
          break;

        case NM_COORDINATOR_ABORT_SHUTDOWN:
          SchM_Enter_Nm_NM_EXCLUSIVE_AREA_0();
          Nm_RestartCoordinator(NM_COORDINATOR_PARA_ONLY);
          /* Set Coordinator state to next state immediately - leave nextState on NM_COORDINATOR_NO_STATE_CHANGE */
          Nm_SetCoordinatorState(coordinator, NM_COORDINATOR_NETWORK_REQUESTED); /* SBSW_NM_CSL_COORDINATOR_INDEX_ACCESS */
          SchM_Exit_Nm_NM_EXCLUSIVE_AREA_0();
          /* \trace SPEC-4195 */
          /* fall through */

        case NM_COORDINATOR_NETWORK_REQUESTED: /* PRQA S 2003 */ /* MD_NM_Rule16.3 */
          /* fall through */

        case NM_COORDINATOR_NETWORK_PASSIVE_RELEASED: /* COV_NM_PASSIVE_CONDITION */

          /* The following function determines internally the next state, it can be
           * - NM_COORDINATOR_START_TIMERS (fall through case),
           * - NM_COORDINATOR_WAIT_FOR_SYNC (break needed)
           * - Stay in the current state because: network has been requested or a 
           *   passive network is still awake */
          if (Nm_MainAux_NmCoordNetworkPassiveReleased(NM_COORDINATOR_PARA_FIRST &errorId, &nextState) == FALSE ) /* SBSW_NM_ERRORID_AND_NEXTSTATE_AS_PARAMETER_CALL */
          {
            /* fall through */
          }
          else
          {
            break;
          }
          /* fall through if condition fulfilled */

        case NM_COORDINATOR_START_TIMERS: /* PRQA S 2003 */ /* MD_NM_Rule16.3 */ /* COV_NM_TRANSIENT_START_TIMERS_CASE */
          Nm_MainAux_NmCoordStartTimers(NM_COORDINATOR_PARA_FIRST &errorId ); /* SBSW_NM_ERRORID_AS_PARAMETER_CALL */
          nextState = NM_COORDINATOR_WAIT_FOR_TIMERS;
          /* fall through */

        case NM_COORDINATOR_WAIT_FOR_TIMERS: /* PRQA S 2003 */ /* MD_NM_Rule16.3 */ /* COV_NM_TRANSIENT_WAIT_FOR_TIMERS_CASE */
          nextState = Nm_MainAux_NmCoordWaitForTimers(NM_COORDINATOR_PARA_FIRST nextState, &errorId); /* SBSW_NM_ERRORID_AS_PARAMETER_CALL */
          if (nextState == NM_COORDINATOR_TIMER_EXPIRED )
          {
            /* fall through */
          }
          else
          {
            break;
          }
          /* fall through if condition fulfilled */

        case NM_COORDINATOR_TIMER_EXPIRED: /* PRQA S 2003 */ /* MD_NM_Rule16.3 */
          nextState = Nm_MainAux_NmCoordTimerExpired(NM_COORDINATOR_PARA_FIRST nextState);
          break;

#  if ( NM_OPTIMIZE_NO_SYNC_CHANNEL == STD_OFF )
        case NM_COORDINATOR_WAIT_FOR_SYNC:
#   if ( NM_SYNCHRONIZATION_TIMEOUT_TIME == 0u)
          nextState = Nm_MainAux_NmCoordWaitForSync(nextState);
#   else
          nextState = Nm_MainAux_NmCoordWaitForSync(NM_COORDINATOR_PARA_FIRST nextState);
#   endif
          break;
#  endif
        default: /* COV_NM_MISRA_DEFAULTCASE */
          break;
      }

      /* #40 Save next state to coordinator */
      SchM_Enter_Nm_NM_EXCLUSIVE_AREA_0();
      if ( (nextState != NM_COORDINATOR_NO_STATE_CHANGE) && 
           (Nm_GetCoordinatorState(coordinator) != NM_COORDINATOR_ABORT_SHUTDOWN) )
      {
        Nm_SetCoordinatorState(coordinator, nextState); /* SBSW_NM_CSL_COORDINATOR_INDEX_ACCESS */
      }
      SchM_Exit_Nm_NM_EXCLUSIVE_AREA_0();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (NM_DEV_ERROR_REPORT == STD_ON)
  if (errorId != NM_E_NO_ERROR)
  {
    /* \trace SPEC-4123, SPEC-31350 */
    (void)Det_ReportError( NM_MODULE_ID, NM_INSTANCE_ID, NM_SID_MAINFUNCTION, errorId);
  }
#  else
  NM_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#  endif

  Nm_Rtm_Stop(RtmMeasurementPoint_NM_SID_MAINFUNCTION)
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */




# endif /* ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) */
#endif /* else ( NM_MACRO_LAYER_ENABLED == STD_ON ) */

#define NM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GENERATED FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Nm_<Prefix>_PduRxIndication()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 */


/**********************************************************************************************************************
 *  Verify the configuration of the Network Management Interface
 *********************************************************************************************************************/

/* Check standard define switches */
#if !defined ( STD_OFF ) || !defined ( STD_ON ) || ( STD_ON == STD_OFF )
# error: "Configuration issue: STD_ON and STD_OFF have to be defined to a different value!"
#endif

/* Check Nm Interface Configuration switches */
#if !defined( NM_CONFIGURATION_VARIANT_PRECOMPILE )
# error: "Nm configuration issue: Configuration Variant Pre-Compile has to be defined."
#endif

#if !defined( NM_CONFIGURATION_VARIANT_LINKTIME )
# error: "Nm configuration issue: Configuration Variant Link-Time has to be defined."
#endif

#if ( NM_CONFIGURATION_VARIANT_PRECOMPILE == NM_CONFIGURATION_VARIANT_LINKTIME )
# error: "Nm configuration issue: Config Variant Defines of Pre-Compile and Link-Time must have different values."
#endif

#if !( ( defined ( NM_CONFIGURATION_VARIANT ) ) \
    && ( ( NM_CONFIGURATION_VARIANT == NM_CONFIGURATION_VARIANT_PRECOMPILE ) || \
    ( NM_CONFIGURATION_VARIANT == NM_CONFIGURATION_VARIANT_LINKTIME ) ) )
# error: "Nm configuration issue: Configuration Variant has to be defined to Pre-Compile or Link-Time."
#endif

#if !( ( defined NM_COM_CONTROL_ENABLED ) \
    && ( ( NM_COM_CONTROL_ENABLED == STD_OFF ) || ( NM_COM_CONTROL_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: Com Control Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_VERSION_INFO_API ) \
    && ( ( NM_VERSION_INFO_API == STD_OFF ) || ( NM_VERSION_INFO_API == STD_ON ) ))
# error: "Nm configuration issue: Version Info Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_MACRO_LAYER_ENABLED ) \
    && ( ( NM_MACRO_LAYER_ENABLED == STD_OFF ) || ( NM_MACRO_LAYER_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: Macro Layer Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_RUNTIME_MEASUREMENT_SUPPORT ) \
    && ( ( NM_RUNTIME_MEASUREMENT_SUPPORT == STD_OFF ) || ( NM_RUNTIME_MEASUREMENT_SUPPORT == STD_ON ) ) )
# error: "Nm configuration issue: Runtime Measurement has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_USER_DATA_ENABLED ) \
    && ( ( NM_USER_DATA_ENABLED == STD_OFF ) || ( NM_USER_DATA_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: User Data Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_NODE_DETECTION_ENABLED ) \
    && ( ( NM_NODE_DETECTION_ENABLED == STD_OFF ) || ( NM_NODE_DETECTION_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: Node Detection Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_NODE_ID_ENABLED ) \
    && ( ( NM_NODE_ID_ENABLED == STD_OFF ) || ( NM_NODE_ID_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: Node Identifier Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_PASSIVE_MODE_ENABLED ) \
    && ( ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) || ( NM_PASSIVE_MODE_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: Passive Mode Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_STATE_CHANGE_REPORT_ENABLED ) \
    && ( ( NM_STATE_CHANGE_REPORT_ENABLED == STD_OFF ) || ( NM_STATE_CHANGE_REPORT_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: State Change Report Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_PDU_RX_INDICATION_ENABLED ) \
    && ( ( NM_PDU_RX_INDICATION_ENABLED == STD_OFF ) || ( NM_PDU_RX_INDICATION_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: Pdu Rx Indication Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_STATE_CHANGE_IND_ENABLED ) \
    && ( ( NM_STATE_CHANGE_IND_ENABLED == STD_OFF ) || ( NM_STATE_CHANGE_IND_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: State Change Indication Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_REMOTE_SLEEP_IND_ENABLED ) \
    && ( ( NM_REMOTE_SLEEP_IND_ENABLED == STD_OFF ) || ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: Remote Sleep Ind Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_REPEAT_MSG_IND_ENABLED ) \
    && ( ( NM_REPEAT_MSG_IND_ENABLED == STD_OFF ) || ( NM_REPEAT_MSG_IND_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: Repeat Msg Ind Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_CAR_WAKE_UP_RX_ENABLED ) \
    && ( ( NM_CAR_WAKE_UP_RX_ENABLED == STD_OFF ) || ( NM_CAR_WAKE_UP_RX_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: Car Wake Up Rx Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_BUS_SYNCHRONIZATION_ENABLED ) \
    && ( ( NM_BUS_SYNCHRONIZATION_ENABLED == STD_OFF ) || ( NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: Bus Synchronization Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_COORDINATOR_SYNC_SUPPORT ) \
    && ( ( NM_COORDINATOR_SYNC_SUPPORT == STD_OFF ) || ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON ) ) )
# error: "Nm configuration issue: Coordinator Sync Support has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_DEV_ERROR_DETECT ) \
    && ( ( NM_DEV_ERROR_DETECT == STD_OFF ) || ( NM_DEV_ERROR_DETECT == STD_ON ) ) )
# error: "Nm configuration issue: Dev Error Detect has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_DEV_ERROR_REPORT ) \
    && ( ( NM_DEV_ERROR_REPORT == STD_OFF ) || ( NM_DEV_ERROR_REPORT == STD_ON ) ) )
# error: "Nm configuration issue: Dev Error Report has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_COM_USER_DATA_SUPPORT ) \
    && ( ( NM_COM_USER_DATA_SUPPORT == STD_OFF ) || ( NM_COM_USER_DATA_SUPPORT == STD_ON ) ) )
# error: "Nm configuration issue: Com User Data Support has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_COORDINATOR_SUPPORT_ENABLED ) \
    && ( ( NM_COORDINATOR_SUPPORT_ENABLED == STD_OFF ) || ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) ) )
# error: "Nm configuration issue: Coordinator Support Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_SYNCHRONIZATION_TIMEOUT_TIME ) && ( NM_SYNCHRONIZATION_TIMEOUT_TIME >= 0u  ) )
# error: "Nm configuration issue: Nm Synchronization Timeout Time has to be defined equal or greater zero."
#endif

/* ESCAN00075013 */
#if !( ( defined NM_COORDINATOR_REQUEST_CHANNELS_IN_BUS_SLEEP ) \
    && ( ( NM_COORDINATOR_REQUEST_CHANNELS_IN_BUS_SLEEP == STD_OFF ) || ( NM_COORDINATOR_REQUEST_CHANNELS_IN_BUS_SLEEP == STD_ON ) ) )
# error: "Nm configuration issue: Coordinator Request Channels in Bus Sleep has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_USE_DUMMY_STATEMENT ) \
    && ( ( NM_USE_DUMMY_STATEMENT == STD_OFF ) || ( NM_USE_DUMMY_STATEMENT == STD_ON ) ) )
# error: "Nm configuration issue: Use Dummy Statement has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_OPTIMIZE_ONLY_ONE_COORD ) \
    && ( ( NM_OPTIMIZE_ONLY_ONE_COORD == STD_OFF ) || ( NM_OPTIMIZE_ONLY_ONE_COORD == STD_ON ) ))
# error: "Nm configuration issue: Optimization for one Coordiantor has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_OPTIMIZE_ALL_CHANNEL_COORD ) \
    && ( ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_OFF ) || ( NM_OPTIMIZE_ALL_CHANNEL_COORD == STD_ON ) ) )
# error: "Nm configuration issue: Optimization for all Channels coordinated has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_OPTIMIZE_NO_PASSIVE_COORD ) \
    && ( ( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_OFF ) || ( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_ON ) ) )
# error: "Nm configuration issue: Optimization for no passive coordinated channel has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_OPTIMIZE_NO_SYNC_CHANNEL ) \
    && ( ( NM_OPTIMIZE_NO_SYNC_CHANNEL == STD_OFF ) || ( NM_OPTIMIZE_NO_SYNC_CHANNEL == STD_ON ) ) )
# error: "Nm configuration issue: Optimization for no synchronizing channel has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_OPTIMIZE_ALL_SYNC_CHANNEL ) \
    && ( ( NM_OPTIMIZE_ALL_SYNC_CHANNEL == STD_OFF ) || ( NM_OPTIMIZE_ALL_SYNC_CHANNEL == STD_ON ) ) )
# error: "Nm configuration issue: Optimization for all synchronizing channels has to be defined STD_OFF or STD_ON."
#endif

#if !( ( defined NM_OPTIMIZE_NO_PASSIVE_CHANNEL ) \
    && ( ( NM_OPTIMIZE_NO_PASSIVE_CHANNEL == STD_OFF ) || ( NM_OPTIMIZE_NO_PASSIVE_CHANNEL == STD_ON ) ) )
# error: "Nm configuration issue: Optimization for no passive channel has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_OPTIMIZE_NO_SLEEP_MASTER ) \
    && ( ( NM_OPTIMIZE_NO_SLEEP_MASTER == STD_OFF ) || ( NM_OPTIMIZE_NO_SLEEP_MASTER == STD_ON ) ))
# error: "Nm configuration issue: Optimization for no sleep master channel has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_OPTIMIZE_ALL_SLEEP_MASTER ) \
    && ( ( NM_OPTIMIZE_ALL_SLEEP_MASTER == STD_OFF ) || ( NM_OPTIMIZE_ALL_SLEEP_MASTER == STD_ON ) ))
# error: "Nm configuration issue: Optimization for all sleep master channels has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_OPTIMIZE_NO_PREPARE_BUS_SLEEP_MODE ) \
    && ( ( NM_OPTIMIZE_NO_PREPARE_BUS_SLEEP_MODE == STD_OFF ) || ( NM_OPTIMIZE_NO_PREPARE_BUS_SLEEP_MODE == STD_ON ) ))
# error: "Nm configuration issue: Optimization for no Prepare Bus Sleep Mode has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL ) \
    && ( ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF ) || ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON ) ))
# error: "Nm configuration issue: Optimization for One BusNm on a Channel has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT ) \
    && ( ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_OFF ) || ( NM_OPTIMIZE_ALL_OR_NONE_COORD_IN_VARIANT == STD_ON ) ))
# error: "Nm configuration issue: Optimization for All or none coordinated channels in each variant has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE ) \
    && ( ( NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE == STD_OFF ) || ( NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE == STD_ON ) ))
# error: "Nm configuration issue: Optimization for All Shutdown Delay Timers being one has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_POSTBUILD_VARIANT_SUPPORT ) \
    && ( ( NM_POSTBUILD_VARIANT_SUPPORT == STD_OFF ) || ( NM_POSTBUILD_VARIANT_SUPPORT == STD_ON ) ))
# error: "Nm configuration issue: Postbuild Variant Support has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_USE_INIT_POINTER ) \
    && ( ( NM_USE_INIT_POINTER == STD_OFF ) || ( NM_USE_INIT_POINTER == STD_ON ) ))
# error: "Nm configuration issue: Use Init Pointer has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_BUSNM_SPECIFIC_PDU_RX_INDICATION_ENABLED ) \
    && ( ( NM_BUSNM_SPECIFIC_PDU_RX_INDICATION_ENABLED == STD_OFF ) || ( NM_BUSNM_SPECIFIC_PDU_RX_INDICATION_ENABLED == STD_ON ) ))
# error: "Nm configuration issue: BusNm Specific Pdu Rx Indication has to be defined STD_OFF or STD_ON."
#endif

/* ESCAN00086148 */
#if !(( defined NM_BUSNM_FRNM_ENABLED ) \
    && ( ( NM_BUSNM_FRNM_ENABLED == STD_OFF ) || ( NM_BUSNM_FRNM_ENABLED == STD_ON ) ))
# error: "Nm configuration issue: BusNm FrNm Enabled has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC ) \
    && ( ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_OFF ) || ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) ))
# error: "Nm configuration issue: Channel type coordinated NmFiatC has to be defined STD_OFF or STD_ON."
#endif

/* ESCAN00089481 */
#if !(( defined NM_WAIT_BUS_SLEEP_EXTENSIONS ) \
    && ( ( NM_WAIT_BUS_SLEEP_EXTENSIONS == STD_OFF ) || ( NM_WAIT_BUS_SLEEP_EXTENSIONS == STD_ON ) ))
# error: "Nm configuration issue: Wait Bus Sleep Extensions has to be defined STD_OFF or STD_ON."
#endif

#if !(( defined NM_OSEKNORMAL ) \
    && ( ( NM_OSEKNORMAL == STD_OFF ) || ( NM_OSEKNORMAL == STD_ON ) ))
# error: "Nm configuration issue: Osek Normal has to be defined STD_OFF or STD_ON."
#endif

/* Check number of channels */
#if ( NM_MACRO_LAYER_ENABLED == STD_ON )
#else
# if ( NM_CONFIGURATION_VARIANT == NM_CONFIGURATION_VARIANT_PRECOMPILE ) /* COV_NM_CONFIG */
#  if !(defined ( NM_NM_CHANNELS_PC ) && ( NM_NM_CHANNELS_PC > 0u ))
#   error: "Nm configuration issue: Number of NM channels has to be defined greater than 0!"
#  endif

#  if !(defined ( NM_SYS_CHANNELS_PC ) && ( NM_SYS_CHANNELS_PC >= NM_NM_CHANNELS_PC ))
#   error: "Nm configuration issue: Number of system channels has to be equal to or greater than the number of NM channels!"
#  endif
# endif /* ( NM_CONFIGURATION_VARIANT == NM_CONFIGURATION_VARIANT_PRECOMPILE ) */

# if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON ) /* COV_MSR_UNSUPPORTED */
#  if ( NM_NM_CHANNELS_PC > 32 )
#   error: "NM Interface configuration error: NM Interface with Coordinator Support ON does not support more than 32 channels!"
#  endif
# endif

#endif /* else  NM_MACRO_LAYER_ENABLED == STD_ON */

/* Check configuration of Passive Mode */
#if ( NM_PASSIVE_MODE_ENABLED == STD_ON )
# if ( NM_BUS_SYNCHRONIZATION_ENABLED == STD_ON ) 
#  error: "Nm configuration issue: NM_BUS_SYNCHRONIZATION_ENABLED should not be used with NM_PASSIVE_MODE_ENABLED."
# endif
# if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON ) 
#  error: "Nm configuration issue: NM_REMOTE_SLEEP_IND_ENABLED should not be used with NM_PASSIVE_MODE_ENABLED."
# endif
# if ( NM_NODE_DETECTION_ENABLED == STD_ON ) 
#  error: "Nm configuration issue: NM_NODE_DETECTION_ENABLED should not be used with NM_PASSIVE_MODE_ENABLED."
# endif
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#  error: "Nm configuration issue: NM_COORDINATOR_SUPPORT_ENABLED should not be used with NM_PASSIVE_MODE_ENABLED."
# endif
#endif

#if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
# if ( NM_BUS_SYNCHRONIZATION_ENABLED == STD_OFF ) 
#  error: "Nm configuration issue: NM_BUS_SYNCHRONIZATION_ENABLED must be STD_ON if NM_COORDINATOR_SUPPORT_ENABLED is STD_ON."
# endif
#  if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_OFF ) 
#   error: "Nm configuration issue: NM_REMOTE_SLEEP_IND_ENABLED should be STD_ON if NM_COORDINATOR_SUPPORT_ENABLED is STD_ON."
#  endif
# if ( NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE == STD_ON )
#  if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_ON )
#   if ( NM_NMSHUTDOWNDELAYTIMEROFCHANNELCONFIG == STD_ON )
#    error: "Nm configuration issue: NM_NMSHUTDOWNDELAYTIMEROFCHANNELCONFIG must be defined to STD_OFF if NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE is STD_ON."
#   endif
#  else
#   if ( NM_NMSHUTDOWNDELAYTIMEROFNMBUSNMASSOCIATION == STD_ON )
#    error: "Nm configuration issue: NM_NMSHUTDOWNDELAYTIMEROFNMBUSNMASSOCIATION must be defined to STD_OFF if NM_OPTIMIZE_ALL_SHUTDOWN_DELAY_TIMER_ARE_ONE is STD_ON."
#   endif
#  endif
# endif
#else
# if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )
#  error: "Nm configuration issue: NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL should be STD_ON if NM_COORDINATOR_SUPPORT_ENABLED is STD_OFF."
# endif
# if ( NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC == STD_ON )
#  error: "Nm configuration issue: NM_ENABLE_CHANNELTYPE_COORDINATED_NMFIATC should be STD_OFF if NM_COORDINATOR_SUPPORT_ENABLED is STD_OFF."
# endif
#endif

#if ( ( NM_COORDINATOR_SYNC_SUPPORT == STD_ON ) && ( NM_COORDINATOR_SUPPORT_ENABLED == STD_OFF ))
# error: "Nm configuration issue: NM_COORDINATOR_SUPPORT_ENABLED must be on if NM_COORDINATOR_SYNC_SUPPORT is on."
#endif

/* Check configuration of Node Detection */
#if ( NM_NODE_DETECTION_ENABLED == STD_ON ) && ( NM_NODE_ID_ENABLED == STD_OFF )
# error: "Nm configuration issue: NM_NODE_DETECTION_ENABLED cannot be STD_ON if NM_NODE_ID_ENABLED is STD_OFF."
#endif

/* Check required settings */
#if !(( defined NM_MACRO_LAYER_ENABLED ) \
    && ( ( NM_MACRO_LAYER_ENABLED == STD_OFF ) || ( NM_MACRO_LAYER_ENABLED == STD_ON ) ))
# error: "Nm configuration issue: Macro Layer Optimization has to be defined STD_OFF or STD_ON."
#endif

#if ( NM_MACRO_LAYER_ENABLED == STD_ON)
# if ( NM_POSTBUILD_VARIANT_SUPPORT == STD_ON )
#  error "Nm configuration issue: Macro Layer Optimization has to be STD_OFF in configuration variant PostBuild-Selectable"
# endif
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#  error: "Nm configuration issue: Current NM implementation requires coordinator support switch to be disabled."
# endif 
# if ( !defined ( NM_BUSNM_TYPE_PREFIX ))
#  error: "Nm configuration issue: Prefix for BusNm must be set"
# endif
#endif

#if ( NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL == STD_OFF )

# if defined(E_OK) /* COV_NM_CONFIG */
#  if (E_OK != 0u)
#   error: "Nm configuration issue: E_OK needs to be defined to 0 if Optimize One BusNm On A Channel is STD_OFF."
#  endif
# endif

# if !defined(NM_NUMBER_OF_CHANNEL_MODES) 
#  error: "Nm configuration issue: Number of channel modes has to be defined to 3u."
# endif

# if defined(NM_NUMBER_OF_CHANNEL_MODES) /* COV_NM_CONFIG */
#  if !((NM_CHANNEL_MODE_INDEX_BUS_SLEEP == 0x00) && (NM_CHANNEL_MODE_INDEX_PREPARE_BUS_SLEEP == 0x01) &&\
        (NM_CHANNEL_MODE_INDEX_NETWORK == 0x02) && (NM_NUMBER_OF_CHANNEL_MODES > NM_CHANNEL_MODE_INDEX_NETWORK) &&\
        (NM_NUMBER_OF_CHANNEL_MODES == 0x03))
#   error: "Nm configuration issue: NM_NUMBER_OF_CHANNEL_MODES needs to be defined to 3 (number of possible channel modes) if Optimize One BusNm On A Channel is STD_OFF."
#  endif
# endif

#endif

#if ( NM_OPTIMIZE_NO_PASSIVE_COORD == STD_OFF )
# if ( NM_OPTIMIZE_ALL_SLEEP_MASTER == STD_ON )
#  error: "Nm configuration issue: NM_OPTIMIZE_ALL_SLEEP_MASTER must be defined to STD_OFF if NM_OPTIMIZE_NO_PASSIVE_COORD is STD_OFF."
# endif
#endif

/**********************************************************************************************************************
 *  Module specific MISRA deviations
 *********************************************************************************************************************/
/* Module specific MISRA deviations
  MD_NM_Dir1.1:
    Reason:     The return value is not needed, therefore it is casted to a void type.
    Risk:       No risk.
    Prevention: No prevention.

  MD_NM_Rule2.2:
    Reason:     The bit mask is never needed due to the generated code.
    Risk:       No risk.
    Prevention: Covered by code review 

  MD_NM_Rule8.2:
    Reason:     In order to keep a generic function pointer prototype for all BusNms, the parameter name is not defined.
    Risk:       No risk.
    Prevention: Covered by code review.

  MD_NM_Rule8.9:
    Reason:     Not all compilers can cope with static const at function scope
    Risk:       Developer is tempted to use static const variables in other functions although it is not designated.
    Prevention: Assert that the variables are used in one function only during review.

  MD_NM_Rule15.4:
    Reason:     Break statement used to exit from a switch case block in case the transition has to be interrupted and
                proceeded in the next main function call.
    Risk:       None
    Prevention: Covered by code review 

  MD_NM_Rule16.3:
    Reason:     Fall through used for code optimizations.
    Risk:       There is a risk that a fall through is overseen by a code review and leads to unexpected results.
    Prevention: Fall through is marked with explicit comments to draw attention to it when code review is performed.

 */

/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_NM_CSL_CHANNEL_INDEX_ACCESS
\DESCRIPTION Access of ChannelState, ChannelRequested, ChPrevBusNmState, ChRemSleepState via
             indirection over ChannelConfig structure.
             The 'channel' variable which is used as index is always checked.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_NM_CSL_CHANNEL_INDEX_ACCESS_GW
\DESCRIPTION Access of WakeupDetected, RemoteSleepFilter, RemoteWakeupFilter, PartEcuActiveChannels, PartEcuReqChannels, ExternalWakeupProcessed via:
             indirection over CoordCluster structure. The 'coordinator' variable which is used as index is always checked.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_NM_CSL_NODEID_INDEX_ACCESS_GW
\DESCRIPTION Access of PartEcuToActToNodeId via:
             indirection over MapPartEcuToActChOfNmPartEcuMapping array  with same index using ComStackLib .
             The 'nodeId' variable which is used as index is always checked.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_NM_CSL_PARTECUTOACTNODEID_INDEX_ACCESS_GW
\DESCRIPTION Access of PartEcuToActToNodeId using ComStackLib
\COUNTERMEASURE \N Qualified use-case CSL01 of ComStackLib

\ID SBSW_NM_CSL_COORDINATOR_INDEX_ACCESS
\DESCRIPTION Access of CoordinatorState via index determined by 
             CoordinatorStateClusterIdxOfChannelConfig / for loop index from 0..GetSizeOfCoordinatorState()-1.
             The 'coordinator' variable which is used as index is always checked.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_NM_CSL_TIMER_INDEX_ACCESS
\DESCRIPTION Access of ChannelActiveTimer via indirection over ChannelConfig structure if optimization for one
             BusNm on a Channel is active. Otherwise the indirection is done via the Nm_NmBusNmAssociation table.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_NM_CSL_FUNCTION_TABLE_PTRCALL
\DESCRIPTION Function pointer call from the table Nm_Get<name_of_the_function>OfNmFunctionTable with
             NM_CHANNEL_OR_BUSNM_IDX used as index, which is the generated number of Nms and corresponds to the
             size of the arrays containing the functions.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_NM_CSL_NMOSEK_GET_STATUS_CALL
\DESCRIPTION Function call of NmOsek_GetStatus() with a pointer to a buffer as a global variable.
             The address of the first byte of the buffer is generated by ComStackLib.
\COUNTERMEASURE \N Qualified use-case CSL03 of ComStackLib

\ID SBSW_NM_CSL_INCREMENT_DECREMENT_INDEX_ACCESS
\DESCRIPTION Access to the ChRemSleepState and ActiveTimer through the functions:
             Nm_DecChRemSleepState, Nm_IncChRemSleepState
             and Nm_DecChannelActiveTimer respectively
             always uses NM_CHANNEL_IDX as index, which is the generated number of Nms and corresponds to the size
             of the array ChRemSleepState and ActiveTimer.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib

\ID SBSW_NM_VERSIONINFO_PTRWRITE
\DESCRIPTION The function Nm_GetVersionInfo() writes to the object referenced by parameter nmVerInfoPtr.
\COUNTERMEASURE \N The caller ensures that the pointer passed to the parameter nmVerInfoPtr is valid.

\ID SBSW_NM_ERRORID_AS_PARAMETER_CALL
\DESCRIPTION Call to the function with pointer to local stack variable errorId as parameter.
\COUNTERMEASURE \N [CM_NMIF_GENERAL_FUNCTIONCALL]

\ID SBSW_NM_ERRORID_AND_NEXTSTATE_AS_PARAMETER_CALL
\DESCRIPTION Call to the function with pointer to local stack variables errorId and nextState as parameter.
\COUNTERMEASURE \N [CM_NMIF_GENERAL_FUNCTIONCALL]

\ID SBSW_NM_MAINAUX_NMCOORWAITFORTM_TMRS_CALL
\DESCRIPTION Call to Nm_MainAux_NmCoordWaitForTm_CheckTimers with a pointer to local stack variables
             allBusNmTimersHaveExpired, continueWithNextState and errorId as parameter.
\COUNTERMEASURE \N [CM_NMIF_GENERAL_FUNCTIONCALL]

\ID SBSW_NM_MAINAUX_NMCOORWAITFORTM_CALL
\DESCRIPTION Call to Nm_MainAux_NmCoordWaitForTm_CheckTimers with a pointer to local stack variable
             continueWithNextState and errorId as parameter.
\COUNTERMEASURE \N [CM_NMIF_GENERAL_FUNCTIONCALL]

\ID SBSW_NM_AUXILIARY_PTRWRITE
\DESCRIPTION The auxiliary function writes to the object referenced by parameter pointer to local stack variables.
\COUNTERMEASURE \N [CM_NMIF_GENERAL_FUNCTIONCALL]

\ID SBSW_NM_CHANNELMODE_ARRAYWRITE
\DESCRIPTION Access of the first dimension of ChannelMode via indirection over ChannelConfig structure.
             The 'channel' variable which is used as index is always checked.
             For the second dimension of the array, a preprocessor check is realized
             in order to check the validity of the size of such array 
             (NM_NUMBER_OF_CHANNEL_MODES) and the possible values that are used as index in the code.
\COUNTERMEASURE \N Qualified use-case CSL02 of ComStackLib
                   The preprocessor check validates the possible index and the size of the array used,
                   therefore it is always valid.

\ID SBSW_NM_CHECKREMOTESLEEP
\DESCRIPTION The function Nm_CheckRemoteSleepIndication writes to the object referenced by parameter nmRemoteSleepIndPtr.
\COUNTERMEASURE \N The caller ensures that the pointers passed to the parameters nmRemoteSleepIndPtr is valid.

\ID SBSW_NM_GETSTATE
\DESCRIPTION The function Nm_GetState writes to the object referenced by parameters nmStatePtr and nmModePtr.
\COUNTERMEASURE \N The caller ensures that the pointers passed to the parameters nmStatePtr and nmModePtr are valid.

\ID SBSW_NM_CONFIG_FUNC_CALL
\DESCRIPTION There is a call to the function that is being pointed.
\COUNTERMEASURE \N The user ensures that the configured parameters passed as function pointers are valid.

\ID SBSW_NM_CSL_GENERATED_FUNC
\DESCRIPTION Access to Nm_GetNmBusNmAssociation<BusNm>BusNmChannelIndexToBusNmIndexIndirections table to get the number of BusNm 
             used by Nm_BusNmSpecificPduRxIndication, created by the ComStackLib. 
             The index Nm_GetSysToNmChInd(nmNetworkHandle) or nmNetworkHandle validity is proven in Nm_BusNmSpecificPduRxIndication. 
\COUNTERMEASURE \N The called function ensures that the passed calculated BusNm index is valid. 


 SBSW_JUSTIFICATION_END */

/*
\CM CM_NMIF_GENERAL_FUNCTIONCALL The parameters are not used in address calculations for memory manipulating
                                 operations. Such calculations include but are not limited to: Array indexing,
                                 pointer offset calculation and related forms of pointer arithmetic. Furthermore
                                 these parameters are not forwarded to other software modules which could use
                                 them for such operations unless they implement appropriate countermeasures.
                                 And the addresses in the pointer variables are not saved in global variables
                                 so that they could be used outside the function call. In that case, they are no
                                 longer valid.
*/


/* COV_JUSTIFICATION_BEGIN


\ID COV_NM_COMSTACKLIB_GEN
  \ACCEPT TX tf tf
  \REASON In the configurations it is not possible to test NM_PDURXINDICATIONOFNMBUSNMASSOCIATION with value != STD_ON
          because either the variable ( NM_PDURXINDICATIONOFCHANNELCONFIG == STD_ON ) 
          or the variable ( NM_PDURXINDICATIONOFNMBUSNMASSOCIATION == STD_ON )
          the condition checks for generation failures.

\ID COV_NM_COMSTACKLIB_GEN_NULL
  \ACCEPT TX
  \REASON In the configurations it is not possible to test NM_PDURXINDICATIONOFNMBUSNMASSOCIATION with value != STD_ON
          because either the variable ( NM_PDURXINDICATIONOFCHANNELCONFIG == STD_ON ) 
          or the variable ( NM_PDURXINDICATIONOFNMBUSNMASSOCIATION == STD_ON ).
          The PduRxIndication always exists, the ComStackLib does not optimize it when its value is equals NULL.

\ID COV_NM_DEV_ERROR_DETECT_ON
  \ACCEPT TX
  \REASON In the non-QM configurations it is only possible to test NM_DEV_ERROR_DETECT with value STD_ON

\ID COV_NM_DEV_ERROR_DETECT_OFF
  \ACCEPT XF
  \REASON In the non-QM configurations it is only possible to test NM_DEV_ERROR_DETECT with value STD_ON

\ID COV_NM_OPTIMIZE_ONE_BUSNM_ON_A_CHANNEL_ON_NM_DEV_ERROR_DETECT_OFF
  \ACCEPT TF tf xf
  \REASON In the non-QM configurations it is only possible to test NM_DEV_ERROR_DETECT with value STD_ON

\ID COV_NOT_NM_DEV_ERROR_DETECT_ON_NM_OPTIMIZE_NO_PASSIVE_COORD_OFF
  \ACCEPT TF tx tf
  \REASON In the non-QM configurations it is only possible to test NM_DEV_ERROR_DETECT with value STD_ON

\ID COV_NM_DEV_ERROR_DETECT_OFF_NM_COORDINATOR_SYNC_SUPPORT_OFF
  \ACCEPT TF xf tf
  \REASON In the non-QM configurations it is only possible to test NM_DEV_ERROR_DETECT with value STD_ON

\ID COV_NM_COORDINATOR_SUPPORT_ENABLED_OFF_NM_BUSNM_FRNM_ENABLED_OFF_NM_DEV_ERROR_DETECT_STD_OFF
  \ACCEPT TF tf tf xf
  \REASON In the non-QM configurations it is only possible to test NM_DEV_ERROR_DETECT with value STD_ON

\ID COV_NM_COORDINATOR_SUPPORT_ENABLED_ON_NM_POSTBUILD_VARIANT_SUPPORT_ON_NM_DEV_ERROR_DETECT_ON_NM_MACRO_LAYER_ENABLED_OFF
  \ACCEPT TF tf tf tx tf
  \REASON In the non-QM configurations it is only possible to test NM_DEV_ERROR_DETECT with value STD_ON

\ID COV_NM_INITIALIZATION_AVAILABLE
  \ACCEPT TX
  \REASON In the non-QM configurations it is only possible to test NM_DEV_ERROR_DETECT with value STD_ON

\ID COV_NM_TRANSIENT_START_TIMERS_CASE
  \ACCEPT X
  \REASON The NM_COORDINATOR_START_TIMERS state is only a transient state if there is no 'Synchronizing Network' being
          coordinated. However, the case label is not enclosed by a preprocessor #if / #endif block to minimize risks
          due to changes.

\ID COV_NM_TRANSIENT_WAIT_FOR_TIMERS_CASE
  \ACCEPT X
  \REASON The NM_COORDINATOR_WAIT_FOR_TIMERS state is only a transient state if there is no BusNm on a channel with
          a shutdown delay timer greater than 1. However, the case label is not enclosed by a preprocessor #if / #endif
          block to minimize risks due to changes.

\ID COV_NM_MISRA_DEFAULTCASE
  \ACCEPT XX
  \REASON The final clause of a switch statement shall be the default clause, to fulfill MISRA Rule 15.3 
  
\ID COV_NM_CONFIG
   \ACCEPT TX
   \REASON [COV_MSR_CONFIG]

\ID COV_NM_NULLFUNCTION
  \ACCEPT XF
  \ACCEPT XX
  \REASON The condition checks for generation failures that cannot be simulated. (NULL pointer to a required function)

\ID COV_NM_UL_NULLFUNCTION
  \ACCEPT TX
  \REASON The condition checks for generation failures that cannot be simulated.
          (Existence of a pointer to an upper layer function)

\ID COV_NM_CONFIG_FUNC_CALL
  \ACCEPT XF
  \ACCEPT TX
  \REASON The callback function has not been configured for certain configurations,
          thus condition always true for an specific configuration.

\ID COV_NM_CONFIG_FRNM
  \ACCEPT TF tx tf
  \REASON There might be configurations where FrNm is the only BusNm configured and thus the comparison is always
          true.

\ID COV_NM_CONFIG_SYNCHRONIZATION_TIMEOUT
  \ACCEPT TX
  \REASON There might be configurations where NM_SYNCHRONIZATION_TIMEOUT_TIME is defined to 1 and therefore the for
          loop is always left through the break statement.

\ID COV_NM_PASSIVE_CONDITION
\ACCEPT X
\REASON The coordinator state NM_COORDINATOR_NETWORK_PASSIVE_RELEASED
        can only be set in configurations with (NM_OPTIMIZE_NO_PASSIVE_COORD = STD_OFF). Thus the 
        switch label is not directly evaluated.

COV_JUSTIFICATION_END */ 

/**********************************************************************************************************************
 *  END OF FILE: Nm.c
 *********************************************************************************************************************/
