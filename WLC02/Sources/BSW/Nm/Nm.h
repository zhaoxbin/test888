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
/*!        \file  Nm.h
 *        \brief  AUTOSAR NM Interface header file
 *
 *      \details  Header of AUTOSAR Generic Network Management Interface
 *                AUTOSAR Release 4
 *        \trace  SPEC-19592
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Leticia Garcia                visgle        Vector Informatik GmbH
 *  Markus Drescher               vismdr        Vector Informatik GmbH
 *  Oliver Hornung                visoh         Vector Informatik GmbH
 *  Philipp Ritter                visrpp        Vector Informatik GmbH
 *  Markus Schuster               vissrk        Vector Informatik GmbH
 *  Patrick Kleemann              vispkn        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2011-02-21  visoh   ESCAN00048893 Creation for AUTOSAR 4
 *  02.00.00  2012-07-20  visrpp  ESCAN00058346 Creation for AUTOSAR 4.0.3
 *  02.00.01  2012-11-08  vismdr  ESCAN00062843 Removed Nm_MainFunction prototype
 *  02.01.00  2013-04-10  vismdr  ESCAN00059538 No changes in this file
 *                                ESCAN00062968 Added NM_E_FUNCTION_PTR_IS_NULL error
 *                                ESCAN00066829 Using general define names for determining the configuration variant
 *  03.00.00  2013-07-02  vismdr  ESCAN00066637 Added dummy statements for functions with unused function arguments
 *                                ESCAN00068794 Added NM_STATE_OFFLINE, NM_BUSNM_J1939NM
 *                                ESCAN00068989 Conditional provision of Nm_PrepareBusSleepMode
 *                                ESCAN00069098 Added optimization for Nm_RestartCoordinator
 *                                ESCAN00070593 Added Run-Time Measurement Support
 *  03.01.00  2013-11-18  vismdr  ESCAN00071769 Added support for multiple BusNms on a channel
 *                                ESCAN00072754 Added NM_STATE_CHECK_WAKEUP, NM_STATE_WAIT_STARTUP
 *                                ESCAN00073347 Adapted argument of ComM_Nm_RestartIndication call
 *                                ESCAN00073359 Adapted condition for accepting Nm_SynchronizationPoint() notification
 *  04.00.00  2013-11-27  vissrk  ESCAN00070562 Added support for PostBuild-Selectable
 *                        vismdr  ESCAN00074996 Added reference to AUTOSAR Requirement and Comment to Code
 *                                ESCAN00074997 Added comment to Nm_PassiveStartUp implementation
 *                                ESCAN00075012 No coordinated shutdown cancellation on Nm_NetworkStartIndication
 *                                ESCAN00075013 Synchronous wake-up on all coordinated channels on a cluster
 *                                ESCAN00075311 Renamed 'shut down' coordinator state
 *                                ESCAN00075453 Added MISRA Deviation for Rule 1.1
 *                                ESCAN00075667 Added call of Det_ReportError to Nm_MainFunction()
 *  05.00.00  2014-08-06  vismdr  ESCAN00076815 No changes in this file
 *                                ESCAN00077044 Adapted implementation for usage of ComStackLib, Changed FAST to
 *                                              regular type; replaced NM_VAR_ZERO_INIT by NM_VAR_INIT
 *                                ESCAN00078185 Fixed compiler warning
 *                                ESCAN00078910 Adapted Nm_GetVersionInfo concerning NM_DEV_ERROR_DETECT == STD_ON
 *                                ESCAN00079029 Added NM_CHECK_CHANNEL_PARAM_VOID_RET checks for callback functions
 *  06.00.00  2014-12-12  vismdr  ESCAN00081182 Retry Network Request on coordinated channel on Nm_BusSleepMode
 *                                ESCAN00081234 Added dummy statements
 *                                ESCAN00081207 Added new states
 *  07.00.00  2014-11-21  visgle  ESCAN00079041 Implemented Nm_CarWakeUpIndication() in static source code
 *                                ESCAN00079121 Adapt the condition for the availability of Nm_MainFunction
 *                                ESCAN00080291 FEAT-427: SafeBSW Step I
 *                                ESCAN00081779 FEAT-1275: SafeBSW Step 2
 *                                ESCAN00082456 FEAT-109: Support Ford SDLC: NM-User Data allow changing gateway
 *                                              routing mode [AR4-1004]
 *                                ESCAN00082682 Added application-specific PDU RX indication callbacks
 *                                ESCAN00084289 Abort Shutdown immediately if network could not be released
 *  08.00.00  2014-09-24  visgle  ESCAN00084666 MISRA deviation: MISRA-C:2004 Rule MD_MSR_STMIF and 
 *                                              incorrect unused markers corrected
 *                                ESCAN00084675 Improved SafeBsw justifications
 *                                ESCAN00084859 FEAT-1507: Support Fiat Class C and ClassB NM with coordinator use case
 *                                ESCAN00085473 FEAT-1492: Support Ford SDLC: NM Gateway and Coordination
 *                                ESCAN00086148 Retry Network Request on coordinated channel on Nm_BusSleepMode only
 *                                              for FrNm
 *                                ESCAN00087190 Added typecast within the NM_COORDINATOR_PARA_ONLY definition
 *                        vismdr  ESCAN00087331 Adapted order of checking Network Handle / Passive Mode Enabled
 *                                ESCAN00087390 Renamed ChannelRemoteSleepState / ChannelPreviousBusNmState variables
 *  08.00.01  2016-02-01  vismdr  ESCAN00087967 Adapted Nm_NetworkStartIndication() / Nm_NetworkMode()
 *  09.00.00  2016-03-03  vismdr  ESCAN00087797 FEAT-1688: Introduced new optimizations
 *                                ESCAN00088827 Stop other Channel Active timers when Wait For Sync is entered
 *                                ESCAN00089163 Adapted dummy statement for errorId in Nm_BusSleepModeAuxFunc()
 *                                ESCAN00089293 Added MISRA deviation justifications for SchM_Enter_* / SchM_Exit_*
 *                                ESCAN00089486 Set global coordinator state to NM_COORDINATOR_START_TIMERS when this
 *                                              state is entered
 *  10.00.00  2016-04-28  visgle  ESCAN00089481 Added support for Wait Bus Sleep Extensions feature of NmOsek
 *            2016-06-03  vismdr  ESCAN00090155 Call ComM_Nm_RestartIndication() if Passive Start-up Forwarding is ON
 *  11.00.00  2018-02-01  visgle  STORYC-3896   Implementation of Nm GW Calibratable
 *  11.00.01  2018-03-13  visgle  STORYC-3896   Review changes: Mask correction in Nm_BusNmSpecificPduRxIndication().
 *                                              Unnecessary encapsulation for PartEcuToActToNodeId functions removed.
 *  12.00.00  2018-09-10  vispkn  STORYC-6129   Update to MISRA2012
 *********************************************************************************************************************/

#if !defined (NM_H)
# define NM_H
/* \trace SPEC-19592 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* \trace SPEC-4204 */
# include "Nm_Cfg.h"                                                           /* Include NM Interface Configuration */


/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Module internal check */
# if ( (NM_STACKTYPES_MAJOR_VERSION != (12u)) \
    || (NM_STACKTYPES_MINOR_VERSION != (0u)) \
    || (NM_STACKTYPES_PATCH_VERSION != (0u)))
#  error "Vendor specific version numbers of NmStackTypes.h and Nm.h are inconsistent!"
# endif


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : Nm_Asr4NmIf CQComponent : Implementation */

/* Vendor and module identification */ /* \trace SPEC-5704 */
# define NM_VENDOR_ID                        (30u)
# define NM_MODULE_ID                        (29u)

/* AUTOSAR Software specification version information */
# define NM_AR_RELEASE_MAJOR_VERSION         (0x04u)
# define NM_AR_RELEASE_MINOR_VERSION         (0x00u)
# define NM_AR_RELEASE_REVISION_VERSION      (0x03u)


/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define NM_SW_MAJOR_VERSION                 (12u)
# define NM_SW_MINOR_VERSION                 (0u)
# define NM_SW_PATCH_VERSION                 (0u)


# define NM_INSTANCE_ID                      (0x00u)

/* ----- API service IDs ----- */
# define NM_SID_INIT                         (0x00u)
# define NM_SID_PASSIVESTARTUP               (0x01u)
# define NM_SID_NETWORKREQUEST               (0x02u)
# define NM_SID_NETWORKRELEASE               (0x03u)
# define NM_SID_DISABLECOMMUNICATION         (0x04u)
# define NM_SID_ENABLECOMMUNICATION          (0x05u)
# define NM_SID_SETUSERDATA                  (0x06u)
# define NM_SID_GETUSERDATA                  (0x07u)
# define NM_SID_GETPDUDATA                   (0x08u)
# define NM_SID_REPEATMESSAGEREQUEST         (0x09u)
# define NM_SID_GETNODEIDENTIFIER            (0x0Au)
# define NM_SID_GETLOCALNODEIDENTIFIER       (0x0Bu)
# define NM_SID_CHECKREMOTESLEEPINDICATION   (0x0Du)
# define NM_SID_GETSTATE                     (0x0Eu)
# define NM_SID_GETVERSIONINFO               (0x0Fu)
# define NM_SID_MAINFUNCTION                 (0x10u)
# define NM_SID_INITMEMORY                   (0x20u)
/*-----------------------------------------------*/


/* Error Codes that are reported to the Development Error Tracer
 *  NM_E_NO_ERROR                 No error
 *  NM_E_UNINIT                   API service used without module initialization
 *  NM_E_HANDLE_UNDEF             API service used with wrong channel handle
 *  NM_E_PARAM_POINTER            API service called with a NULL pointer 
 *  NM_E_SYNCHRONIZATION_TIMEOUT  Nm_SynchronizationPoint was not called in predetermined time */

/* The plausibility checks of the APIs are always executed in order to assure correct behavior of the module.
 * As the variable errorId always exists in every function, the error values are assign after a check failed,
 * but only reported when the Development Error Report is on switch is on
 */

/* ----- Error codes ----- */
/* \trace SPEC-4180, SPEC-19567 */
/*! API service used without module initialization */
# define NM_E_UNINIT                        (0x00u)
/*! API service used with wrong channel handle */
# define NM_E_HANDLE_UNDEF                  (0x01u)
/*! API service called with a NULL pointer */
# define NM_E_PARAM_POINTER                 (0x02u)

/* ----- Vector Extension ----- */
/* \trace DSGN-Nm22896 */
/*! Nm_SynchronizationPoint was not called in predetermined time */
# define NM_E_SYNCHRONIZATION_TIMEOUT       (0x20u)
/*! Pointer to a function to be called is equals NULL */
# define NM_E_FUNCTION_PTR_IS_NULL          (0x21u)
/*! API State Change notification with invalid/unexpected state */
# define NM_E_INVALID_STATE                 (0x22u)
/*! API State Change notification with same current and previous state */
# define NM_E_SAME_STATES                   (0x23u)
/*! Nm Passive Mode is not enabled for this channel */
# define NM_E_NOT_AVAILABLE_IN_PASSIVE_MODE (0x24u)
/*! No error */
# define NM_E_NO_ERROR                      (0xFFu)

/* In case the Macro Layer is active, the initialization functions and initialization variables are not available */
# if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) || (((NM_POSTBUILD_VARIANT_SUPPORT == STD_ON) || (NM_DEV_ERROR_DETECT == STD_ON )) && ( NM_MACRO_LAYER_ENABLED == STD_OFF)) /* COV_NM_COORDINATOR_SUPPORT_ENABLED_ON_NM_POSTBUILD_VARIANT_SUPPORT_ON_NM_DEV_ERROR_DETECT_ON_NM_MACRO_LAYER_ENABLED_OFF */
#  define NM_INITIALIZATION_AVAILABLE STD_ON
# else
#  define NM_INITIALIZATION_AVAILABLE STD_OFF
# endif


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/* The Nm_Init() function availability is restricted to certain configuration cases */
# if ( NM_INITIALIZATION_AVAILABLE != STD_ON )
#  define Nm_Init()
#  define Nm_InitMemory()
# endif

# if ( NM_MACRO_LAYER_ENABLED == STD_ON )

/* Concatenation of BusNm prefix and function name */
#  define NM_CONCAT_FUNC_MACRO_EXPANSION( prefix, function )    prefix ## function /* PRQA S 0342 */ /* MD_MSR_Rule20.10_0342 */
#  define NM_CONCAT_FUNC( prefix, function )                    NM_CONCAT_FUNC_MACRO_EXPANSION( prefix, function ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#  define NM_MAP_CALL_2_BUSNM( function )                       NM_CONCAT_FUNC( NM_BUSNM_TYPE_PREFIX, function ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/* map functions to BusNm */
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#  define Nm_PassiveStartUp( nmNetworkHandle ) \
          (NM_MAP_CALL_2_BUSNM( _PassiveStartUp)( nmNetworkHandle ))
#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#   define Nm_NetworkRequest( nmNetworkHandle ) \
          (NM_MAP_CALL_2_BUSNM( _NetworkRequest)( nmNetworkHandle ))
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#   define Nm_NetworkRelease( nmNetworkHandle ) \
          (NM_MAP_CALL_2_BUSNM( _NetworkRelease)( nmNetworkHandle ))
#  endif
#  if ( NM_COM_CONTROL_ENABLED == STD_ON )
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#   define Nm_EnableCommunication( nmNetworkHandle ) \
          (NM_MAP_CALL_2_BUSNM( _EnableCommunication)( nmNetworkHandle ))
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#   define Nm_DisableCommunication( nmNetworkHandle ) \
          (NM_MAP_CALL_2_BUSNM( _DisableCommunication)( nmNetworkHandle ))
#  endif
#  if ( NM_USER_DATA_ENABLED == STD_ON )
#   if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_COM_USER_DATA_SUPPORT == STD_OFF )
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#    define Nm_SetUserData( nmNetworkHandle, nmUserDataPtr ) \
          (NM_MAP_CALL_2_BUSNM( _SetUserData)( (nmNetworkHandle), (nmUserDataPtr) ))
#   endif
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#   define Nm_GetUserData( nmNetworkHandle, nmUserDataPtr ) \
          (NM_MAP_CALL_2_BUSNM( _GetUserData)( (nmNetworkHandle), (nmUserDataPtr) ))
#  endif
#  if ( ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) )
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#   define Nm_GetPduData( nmNetworkHandle, nmPduData ) \
          (NM_MAP_CALL_2_BUSNM( _GetPduData)( (nmNetworkHandle), (nmPduData) ))
#  endif
#  if ( NM_NODE_ID_ENABLED == STD_ON )
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#   define Nm_GetNodeIdentifier( nmNetworkHandle, nmNodeIdPtr ) \
          (NM_MAP_CALL_2_BUSNM( _GetNodeIdentifier)( (nmNetworkHandle), (nmNodeIdPtr) ))
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#   define Nm_GetLocalNodeIdentifier( nmNetworkHandle, nmNodeIdPtr ) \
          (NM_MAP_CALL_2_BUSNM( _GetLocalNodeIdentifier)( (nmNetworkHandle), (nmNodeIdPtr) ))
#  endif
#  if ( NM_NODE_DETECTION_ENABLED == STD_ON )
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#   define Nm_RepeatMessageRequest( nmNetworkHandle ) \
          (NM_MAP_CALL_2_BUSNM( _RepeatMessageRequest)( nmNetworkHandle ))
#  endif
#  if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#   define Nm_CheckRemoteSleepIndication( nmNetworkHandle, nmRemoteSleepIndPtr ) \
          (NM_MAP_CALL_2_BUSNM( _CheckRemoteSleepIndication)( (nmNetworkHandle), (nmRemoteSleepIndPtr) ))
#  endif
/* PRQA S 3453 2 */ /* MD_MSR_FctLikeMacro */
#  define Nm_GetState( nmNetworkHandle, nmStatePtr, nmModePtr ) \
          (NM_MAP_CALL_2_BUSNM( _GetState)( (nmNetworkHandle), (nmStatePtr), (nmModePtr) ))

# endif /* ( NM_MACRO_LAYER_ENABLED == STD_ON ) */


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define NM_START_SEC_CONST_8
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* NM Interface version (decimal coded). */
extern CONST(uint8, NM_CONST) Nm_MainVersion;
extern CONST(uint8, NM_CONST) Nm_SubVersion;
extern CONST(uint8, NM_CONST) Nm_ReleaseVersion;

# define NM_STOP_SEC_CONST_8
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define NM_START_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Nm_Init()
 *********************************************************************************************************************/
/*! \brief       Initializes the NM Interface.
 *  \details     Initializes all component variables and sets the component state to 
 *               initialized. Called by application (BswM)
 *  \param[in]   nmConfigPtr      Configuration pointer for initializing the module
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      NM_INITIALIZATION_AVAILABLE == STD_ON
 *  \trace       CREQ-609
 *  \trace       SPEC-4130, SPEC-4191
 *  \trace       DSGN-Nm22876
 *********************************************************************************************************************/
# if ( NM_INITIALIZATION_AVAILABLE == STD_ON )
#  if ( NM_POSTBUILD_VARIANT_SUPPORT == STD_ON )
extern FUNC( void, NM_CODE ) Nm_Init( CONSTP2CONST( Nm_ConfigType, AUTOMATIC, NM_CONST ) nmConfigPtr );
#  else
extern FUNC( void, NM_CODE ) Nm_Init( void );
#  endif

/**********************************************************************************************************************
 *  Nm_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Power-up memory initialization 
 *  \details     Initializes component variables in *_INIT_* sections at power up. Vector Extension [BR:011]
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      NM_INITIALIZATION_AVAILABLE == STD_ON
 *  \note        Use this function in case these variables are not initialized by the startup code. 
 *  \trace       DSGN-Nm22893
 *********************************************************************************************************************/
/* Vector Extension */
extern FUNC( void, NM_CODE ) Nm_InitMemory( void );
# endif


# if ( NM_MACRO_LAYER_ENABLED == STD_ON )
# else

/**********************************************************************************************************************
 *  Nm_PassiveStartUp()
 *********************************************************************************************************************/
/*! \brief       Calls the <BusNm>_PassiveStartUp function. 
 *  \details     Called by application (ComM)
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \return      E_OK       Passive start of network management successful 
 *  \return      E_NOT_OK   Passive start of network management has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for the different network handles
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF)
 *  \trace       CREQ-613, CREQ-105653
 *  \trace       SPEC-4143, SPEC-4168, SPEC-4144, SPEC-31383, SPEC-19576, SPEC-4217
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_PassiveStartUp( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );

#  if ( NM_PASSIVE_MODE_ENABLED == STD_OFF )

/**********************************************************************************************************************
 *  Nm_NetworkRequest()
 *********************************************************************************************************************/
/*! \brief       Calls the <BusNm>_NetworkRequest.
 *  \details     Called by application (ComM)
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \return      E_OK       Requesting of bus communication successful 
 *  \return      E_NOT_OK   Requesting of bus communication has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for the different network handles
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF)
 *  \trace       CREQ-616
 *  \trace       SPEC-4185, SPEC-4189, SPEC-4141, SPEC-4144, SPEC-31388, SPEC-19573
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_NetworkRequest( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
/**********************************************************************************************************************
 *  Nm_NetworkRelease()
 *********************************************************************************************************************/
/*! \brief       Calls the <BusNm>_NetworkRelease bus specific function
 *  \details     Called by application (ComM)
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \return      E_OK       Releasing of bus communication successful
 *  \return      E_NOT_OK   Releasing of bus communication has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for the different network handles
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF)
 *  \trace       CREQ-617
 *  \trace       SPEC-4144, SPEC-4161, SPEC-4188, SPEC-19582
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_NetworkRelease( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
#  endif

#  if ( NM_COM_CONTROL_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_EnableCommunication()
 *********************************************************************************************************************/
/*! \brief       Enables the NM PDU transmission ability. 
 *  \details     Called by application
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \return      E_OK       Enabling of NM PDU transmission ability successful
 *  \return      E_NOT_OK   Enabling of NM PDU transmission ability has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for the different network handles
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_COM_CONTROL_ENABLED == STD_ON )
 *  \trace       CREQ-628
 *  \trace       SPEC-4142, SPEC-4165, SPEC-4183, SPEC-19577
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_EnableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
/**********************************************************************************************************************
 *  Nm_DisableCommunication()
 *********************************************************************************************************************/
/*! \brief       Disables the NM PDU transmission ability. 
 *  \details     Called by application
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \return      E_OK       Disabling of NM PDU transmission ability successful
 *  \return      E_NOT_OK   Disabling of NM PDU transmission ability has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \note        Called by application
 *  \reentrant   TRUE for the different network handles
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_COM_CONTROL_ENABLED == STD_ON )
 *  \trace       CREQ-627
 *  \trace       SPEC-4192, SPEC-4156, SPEC-19570, SPEC-40715
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_DisableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
#  endif

#  if ( NM_USER_DATA_ENABLED == STD_ON )
#   if ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_COM_USER_DATA_SUPPORT == STD_OFF )
/**********************************************************************************************************************
 *  Nm_SetUserData()
 *********************************************************************************************************************/
/*! \brief       Sets user data for NM messages transmitted next on the bus.
 *  \details     Called by application
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[in]   nmUserDataPtr         Pointer to User data for the next transmitted NM message
 *  \return      E_OK       Setting of user data successful
 *  \return      E_NOT_OK   Setting of user data has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for the different network handles
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_USER_DATA_ENABLED == STD_ON )  &&
 *               ( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_COM_USER_DATA_SUPPORT == STD_OFF )
 *  \trace       CREQ-629
 *  \trace       SPEC-4124, SPEC-4166, SPEC-4167, SPEC-4250, SPEC-19603
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_SetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                      CONSTP2CONST( uint8, AUTOMATIC, NM_APPL_VAR ) nmUserDataPtr );
#   endif

/**********************************************************************************************************************
 *  Nm_GetUserData()
 *********************************************************************************************************************/
/*! \brief       Gets user data out of the last successfully received NM message.
 *  \details     Called by application
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[in]   nmUserDataPtr         Pointer where user data out of the last successfully received NM message
 *                                     shall be copied to
 *  \return      E_OK       Getting of user data successful
 *  \return      E_NOT_OK   Getting of user data has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_USER_DATA_ENABLED == STD_ON )
 *  \trace       CREQ-630
 *  \trace       SPEC-4154, SPEC-4174, SPEC-19607
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_GetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                      CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmUserDataPtr );
#  endif

#  if ( ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) )
/**********************************************************************************************************************
 *  Nm_GetPduData()
 *********************************************************************************************************************/
/*! \brief       Gets the whole PDU data out of the most recently received NM message.
 *  \details     Called by application
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[out]  nmPduDataPtr          Pointer where PDU Data out of the most recently received NM message
 *                                     shall be copied to
 *  \return      E_OK       Getting of NM PDU data successful
 *  \return      E_NOT_OK   Getting of NM PDU data has failed
 *  \context     TASK|ISR1|ISR2
 *  \pre         -
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) &&
 *               ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON )
 *  \trace       CREQ-631
 *  \trace       SPEC-4164, SPEC-4202, SPEC-19584
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_GetPduData( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                     CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmPduDataPtr );
#  endif

#  if ( NM_NODE_DETECTION_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_RepeatMessageRequest()
 *********************************************************************************************************************/
/*! \brief       Sets Repeat Message Request Bit for NM messages transmitted next on the bus.
 *               This will force all nodes on the bus to transmit NM messages so that they can be identified.
 *  \details     Called by application
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \return      E_OK       Setting of Repeat Message Request Bit successful
 *  \return      E_NOT_OK   Setting of Repeat Message Request Bit has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for the different network handles
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_NODE_DETECTION_ENABLED == STD_ON )
 *  \trace       CREQ-632
 *  \trace       SPEC-4150, SPEC-4171, SPEC-19581
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_RepeatMessageRequest( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle );
#  endif

#  if ( NM_NODE_ID_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_GetNodeIdentifier()
 *********************************************************************************************************************/
/*! \brief       Gets node identifier out of the last successfully received NM message
 *  \details     Called by application
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[out]  nmNodeIdPtr           Pointer where node identifier out of the last successfully received NM message 
 *                                     shall be copied to
 *  \return      E_OK       Getting of node identifier successful
 *  \return      E_NOT_OK   Getting of node identifier has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_NODE_ID_ENABLED == STD_ON )
 *  \trace       CREQ-635
 *  \trace       SPEC-4190, SPEC-4193, SPEC-19613
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_GetNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                            CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmNodeIdPtr );

/**********************************************************************************************************************
 *  Nm_GetLocalNodeIdentifier()
 *********************************************************************************************************************/
/*! \brief       Gets node identifier configured for the local node
 *  \details     Called by application
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[out]  nmNodeIdPtr           Pointer where node identifier of the local node shall be copied to
 *  \return      E_OK       Getting of local node identifier successful
 *  \return      E_NOT_OK   Getting of local node identifier has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_NODE_ID_ENABLED == STD_ON )
 *  \trace       CREQ-636
 *  \trace       SPEC-4197, SPEC-4149, SPEC-4126, SPEC-19575
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_GetLocalNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                                 CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmNodeIdPtr );
#  endif

#  if ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/**********************************************************************************************************************
 *  Nm_CheckRemoteSleepIndication()
 *********************************************************************************************************************/
/*! \brief       Checks if remote sleep indication takes place or not.
 *  \details     Called by application
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[out]  nmRemoteSleepIndPtr   Pointer where remote sleep status shall be copied to
 *  \return      E_OK       Checking of remote sleep indication bits successful
 *  \return      E_NOT_OK   Checking of remote sleep indication bits has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for the different network handles
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
 *  \trace       CREQ-637
 *  \trace       SPEC-4139, SPEC-4181, SPEC-4186, SPEC-19597
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_CheckRemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                                     CONSTP2VAR( boolean, AUTOMATIC, NM_APPL_VAR ) nmRemoteSleepIndPtr );
#  endif

/**********************************************************************************************************************
 *  Nm_GetState()
 *********************************************************************************************************************/
/*! \brief       Copies the NM state and the NM mode to the location provided by the pointers.
 *  \details     Called by application
 *  \param[in]   nmNetworkHandle       Identification of the NM-channel
 *  \param[out]  nmStatePtr            Pointer where the current network management state shall be copied to 
 *  \param[out]  nmModePtr             Pointer where the current network management mode shall be copied to 
 *  \return      E_OK       Checking of remote sleep indication bits successful
 *  \return      E_NOT_OK   Checking of remote sleep indication bits has failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      (NM_MACRO_LAYER_ENABLED == STD_OFF)
 *  \trace       CREQ-611
 *  \trace       SPEC-4187, SPEC-19602
 *********************************************************************************************************************/
extern FUNC( Std_ReturnType, NM_CODE ) Nm_GetState( CONST( NetworkHandleType, AUTOMATIC ) nmNetworkHandle, 
                                                   CONSTP2VAR( Nm_StateType, AUTOMATIC, NM_APPL_VAR ) nmStatePtr, 
                                                   CONSTP2VAR( Nm_ModeType, AUTOMATIC, NM_APPL_VAR ) nmModePtr );





# endif /* else ( NM_MACRO_LAYER_ENABLED == STD_ON ) */

# if ( NM_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  Nm_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Returns the version information.
 *  \details     Returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  nmVerInfoPtr          Pointer where the version information shall be copied to
 *                                     Parameter must not be NULL.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      ( NM_VERSION_INFO_API == STD_ON )
 *  \trace       CREQ-612
 *  \trace       SPEC-4115, SPEC-4148, SPEC-19589, SPEC-34661
 *********************************************************************************************************************/
extern FUNC( void, NM_CODE ) Nm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, NM_APPL_VAR ) nmVerInfoPtr );
# endif

/* ESCAN00062843 */


/**********************************************************************************************************************
 *  Nm_MainFunction()
 *********************************************************************************************************************/
/*! \fn          Nm_MainFunction
 *  \brief       Implements the processes of the NM Interface, which need a fix cyclic scheduling.
 *  \details     Implements the handling of coordinated networks of the NM Interface.
 *  \pre         Coordinator Support is enabled.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
 *  \trace       CREQ-610, CREQ-790
 *  \trace       SPEC-4107, SPEC-4110, SPEC-4133, SPEC-4147
 *********************************************************************************************************************/
/* The Nm_MainFunction definition is localized in Nm.c. The declaration is realized by SchM */

# define NM_STOP_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */




/*!
 * \exclusivearea NM_EXCLUSIVE_AREA_0
 * Protects Nm Interface coordinator related variables from being modified by any interrupt.
 * Ensures data consistency between BusNm and coordination algorithm. 
 * \protects Nm_CoordinatorState, Nm_ChannelState, Nm_ChannelRequested, NmActiveCoordinatorOfChannelConfig,
 *           passiveChannelsAreReadyToSleep and activeChannelsAreReadyToSleep.
 * \usedin Nm_SynchronizationPoint(), Nm_MainFunction() and its auxiliary functions.
 * \exclude -
 * \length LONG may contain multiple function calls to the BusNms
 * \endexclusivearea
 *
 * \exclusivearea NM_EXCLUSIVE_AREA_1
 * Protects Nm Interface coordinator and multiple channel related variables from being modified by any interrupt.
 * Ensures data consistency between BusNm and coordination algorithm. 
 * \protects Nm_ChannelMode, Nm_ChannelState, Nm_ChRemSleepState and Nm_CoordinatorState.
 * \usedin Nm_NetworkRequest(), Nm_NetworkRelease(), Nm_NetworkMode(), Nm_BusSleepMode(), Nm_PrepareBusSleepMode(),
 *         Nm_RemoteSleepIndication(),  Nm_RemoteSleepCancellation(), Nm_CoordReadyToSleepIndication(),
 *         Nm_CoordReadyToSleepCancellation()
 * \exclude -
 * \length LONG may contain multiple function calls to the BusNms and ComM
 * \endexclusivearea
 */




#endif  /* NM_H */

/**********************************************************************************************************************
 *  END OF FILE: Nm.h
 *********************************************************************************************************************/
