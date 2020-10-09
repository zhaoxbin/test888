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
/**        \file  CanNm.h
 *        \brief  AUTOSAR CAN Network Management
 *
 *      \details  Header of AUTOSAR CAN Network Management
 *                AUTOSAR Release 4.0
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Markus Drescher               vismdr        Vector Informatik GmbH
 *  Markus Schuster               vissrk        Vector Informatik GmbH
 *  Patrick Kleemann              vispkn        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.00.00   2012-07-20  vismdr  ESCAN00058396 Creation of component for AUTOSAR Release 4.0
 *  1.01.00   2012-11-30  vismdr  ESCAN00063428 Adapted conditions for enabling the PN Filter Algorithm
 *                                ESCAN00063454 Added dummy statement to CanNm_ConfirmPnAvailability
 *                                ESCAN00064047 Adapted definition and initialization of CanNm_PbChConfigPtr
 *                                ESCAN00064052 Adapted inclusion conditions of PduR_CanNm.h
 *  1.02.00   2013-04-05  vismdr  ESCAN00059534 No changes in this file
 *                                ESCAN00063983 CanNm_DisableCommunication prevents TX NM PDU after CanNm_Transmit call
 *                                ESCAN00064220 Adapted condition for Nm_CarWakeUpIndication
 *                                ESCAN00064309 Implemented Variant Post-Build Loadable
 *                                ESCAN00065302 NM Msg Tx due to Immediate Restart after State Change Notification
 *                                ESCAN00065303 Adapted condition for sending NM message due to Immediate Restart
 *                                ESCAN00066830 Using general define names for determining the configuration variant
 *  2.00.00   2013-09-18  vismdr  ESCAN00067700 Added Run-Time Measurement Support
 *                                ESCAN00070925 Support optional call of PduR_CanNmTxConfirmation
 *  2.01.00   2013-12-10  vismdr  ESCAN00071960 Adapted definitions of pointer variables
 *                                ESCAN00072375 Adapted call of CanSM_TxTimeoutException
 *                                ESCAN00072626 Fixed compile/linker error for missing CANNM_MESSAGE_DATA_BYTE_INDEX
 *  3.00.00   2013-11-13  vissrk  ESCAN00070560 Implemented Variant Post-Build Selectable
 *                                ESCAN00075727 MISRA deviation: MISRA-C:2004 Rule 11.4
 *                                ESCAN00075773 Incorrect TX Deadline Monitoring of NM message
 *                                              after asynchronous NM message transmission
 *  4.00.00   2014-08-04  vissrk  ESCAN00076479 Replace FAST memory sections by standard sections
 *                                ESCAN00076217 Compiler error: 'CanNm_Transmit' : undeclared identifier
 *                                ESCAN00075919 Compiler error: 'CANNM_PDU_OFF' : undeclared identifier
 *                                ESCAN00077590 Adapt generator to use ComStackLib for all generated data
 *                                ESCAN00078589 Always enable the PN filter in CanNm_ConfirmPnAvailability
 *  4.00.01   2014-11-17  vissrk  ESCAN00079641 Corrected cast to CanNm_PnClusterResetTimerType
 *  4.00.02   2015-01-08  vissrk  ESCAN00080448 Compiler error: 'void' function returning a value
 *  5.00.00   2014-12-08  vissrk  ESCAN00080294 Implement SafeBSW I
 *            2015-07-01  vissrk  ESCAN00081782 Implement SafeBSW II
 *                                ESCAN00078984 The Car Wake Up Bit is generated as mask
 *                                ESCAN00082750 Added BusNm specific Rx Indication
 *                                ESCAN00083310 Allow Immediate Message Transmission due to Com User Data Changes
 *  6.00.00   2016-02-10  vissrk  ESCAN00087842 FEAT-1631: Trigger Transmit API with SduLength In/Out according to ASR4.2.2
 *                                ESCAN00087402 Correct Formal findings regarding SafeBSW
 *  6.01.00   2016-05-02  vissrk  ESCAN00089483 FEAT-1865: Add support for TMC NmDirOsek coordination use cases
 *                                ESCAN00089161 Add missing "\endexclusivearea" in CanNm.h
 *                                ESCAN00089823 PbChannelConfig struct is accessed with a index value that is
 *                                              not check against the bounds of PbChannelConfig struct
 *                                ESCAN00089944 [PartialNetworking] NM messages are transmitted even though channel should already be in sleep
 *                                ESCAN00089586 Compiler error: C1189 Due to wrong encapsulation an error directive leads to a compile error
 *  6.02.00   2016-08-08  vissrk  FEATC-58      Transmission of NM Coordinator Sleep Ready Bit
 *                                ESCAN00092026 Compiler warning: cannm.c: warning: conversion from 'uint8_least' to 'CanNm_PnClusterReqType', possible loss of data
 *  6.03.00   2017-02-06  vissrk  ESCAN00093001 CanNm calls Det_ReportError cyclically when not active in a predefined variant (PB-S)
 *                                FEATC-526     AUTOSAR 4.2.2 SWS Traceability Goals 2&3 for CanNm
 *  7.00.00   2018-01-08  vispkn  STORYC-3565   AUTOSAR 4.2.x SWS Retry first message request
 *                                ESCAN00098006 Transmit Immediate Nm Messages in next main function, if CanIf_Transmit returns E_NOT_OK
 *                                ESCAN00097257 Added function body of CanNm_CancelTransmit()
 *  7.01.00   2018-02-06  vispkn  STORYC-3912   Added channel based and post build selectable parameters
 *                                STORYC-4227   Retry First Message Request feature is extended for transition PrepareBusSleep to RepeatMessage state
 *  7.02.00   2018-03-12  vispkn  STORYC-4228   Updated Justifications
 *  7.02.01   2018-04-04  vispkn  ESCAN00098922 NmStateChangeCallback is not called if same states are passed in Nm_StateChangeNotification
 *                                ESCAN00099003 Missing storage class identifier extern in function declaration and missing compiler abstraction of input parameter
 *  8.00.00   2018-07-26  vispkn  STORYC-6139   Update to MISRA2012
 *                                ESCAN00099865 The NmState variable is generated via CSL in order to use CSL indexes
 *                                ESCAN00099951 Compiler error: 'CanNm_SetMsgRequest' undefined
 *                                ESCAN00100179 Minor fixes
 *  9.00.00   2018-09-27  vispkn  STORYC-6795   Support CanNM messages with length greater 8 Bytes
 *                                STORYC-7159   Synchronize Eira/Era execution to UdpNm
 *                                ESCAN00100425 Channel starts when receiving RepeatMessageBit in BusSleep
 *                                ESCAN00100378 An immediate NM message is not transmitted
 *                                ESCAN00100376 TxTimeoutException is called earlier than configured
 *  9.00.01   2019-01-24  vispkn  ESCAN00101831 Compiler warning: conversion leads to possible loss of data
 *********************************************************************************************************************/

#if !defined (CANNM_H)
# define CANNM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "CanNm_Cfg.h"                                                              /* Include CAN NM Configuration */
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : Nm_Asr4NmCan CQComponent : Implementation */
/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
# define NM_ASR4NMCAN_VERSION                          (0x0900u)
# define NM_ASR4NMCAN_RELEASE_VERSION                  (0x01u)

/* Vendor and module identification */
# define CANNM_VENDOR_ID                               (30u)
# define CANNM_MODULE_ID                               (31u)

/* AUTOSAR Software specification version information */
/* Document Version   3.3.0
   Part of Release    4.0
   Revision           0003, dated 2011-11-17 */
# define CANNM_AR_RELEASE_MAJOR_VERSION                (0x04u)
# define CANNM_AR_RELEASE_MINOR_VERSION                (0x00u)
# define CANNM_AR_RELEASE_REVISION_VERSION             (0x03u)

/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define CANNM_SW_MAJOR_VERSION                        (NM_ASR4NMCAN_VERSION >> 8)
# define CANNM_SW_MINOR_VERSION                        (NM_ASR4NMCAN_VERSION & 0x00FFu)
# define CANNM_SW_PATCH_VERSION                        (NM_ASR4NMCAN_RELEASE_VERSION)

/* ----- API service IDs ----- */
# define CANNM_SID_INIT                                (0x00u) /*!< Service ID: CanNm_Init() */
# define CANNM_SID_PASSIVESTARTUP                      (0x01u) /*!< Service ID: CanNm_PassiveStartup() */
# define CANNM_SID_NETWORKREQUEST                      (0x02u) /*!< Service ID: CanNm_NetworkRequest() */
# define CANNM_SID_NETWORKRELEASE                      (0x03u) /*!< Service ID: CanNm_NetworkRelease() */
# define CANNM_SID_SETUSERDATA                         (0x04u) /*!< Service ID: CanNm_SetUserData() */
# define CANNM_SID_GETUSERDATA                         (0x05u) /*!< Service ID: CanNm_GetUserData() */
# define CANNM_SID_GETNODEIDENTIFIER                   (0x06u) /*!< Service ID: CanNm_GetNodeIdentifier() */
# define CANNM_SID_GETLOCALNODEIDENTIFIER              (0x07u) /*!< Service ID: CanNm_GetLocalNodeIdentifier() */
# define CANNM_SID_REPEATMESSAGEREQUEST                (0x08u) /*!< Service ID: CanNm_RepeatMessageRequest() */
# define CANNM_SID_GETPDUDATA                          (0x0Au) /*!< Service ID: CanNm_GetPduData() */
# define CANNM_SID_GETSTATE                            (0x0Bu) /*!< Service ID: CanNm_GetState() */
# define CANNM_SID_DISABLECOMMUNICATION                (0x0Cu) /*!< Service ID: CanNm_DisableCommunication() */
# define CANNM_SID_ENABLECOMMUNICATION                 (0x0Du) /*!< Service ID: CanNm_EnableCommunication() */
# define CANNM_SID_MAINFUNCTION                        (0x13u) /*!< Service ID: CanNm_MainFunction() */
# define CANNM_SID_TRANSMIT                            (0x14u) /*!< Service ID: CanNm_Transmit() */
# define CANNM_SID_CONFIRMPNAVAILABILITY               (0x16u) /*!< Service ID: CanNm_ConfirmPnAvailibility() */
# define CANNM_SID_SETSLEEPREADYBIT                    (0x17u) /*!< Service ID: CanNm_SetSleepReadyBit() */
# define CANNM_SID_REQUESTBUSSYNCHRONIZATION           (0xC0u) /*!< Service ID: CanNm_RequestBusSynchronization() */
# define CANNM_SID_CHECKREMOTESLEEPIND                 (0xD0u) /*!< Service ID: CanNm_CheckRemoteSleepIndication() */
# define CANNM_SID_GETVERSIONINFO                      (0xF1u) /*!< Service ID: CanNm_GetVersionInfo() */
# define CANNM_SID_CANCELTRANSMIT                      (0xF2u) /*!< Service ID: CanNm_CancelTransmit() */

/* ----- Error codes ----- */
/* \trace SPEC-63526, SPEC-21927, SPEC-21705, SPEC-21953, SPEC-63524, SPEC-63524, SPEC-21826 */
# define CANNM_E_NO_ERROR                              (0x00u) /*!< used to check if no error occurred - use a value unequal to any error code */
# define CANNM_E_NO_INIT                               (0x01u) /*!< Error code: API service used without module initialization */
# define CANNM_E_INVALID_CHANNEL                       (0x02u) /*!< Error code: API service used with an invalid channel identifier or channel was not configured for the functionality of the calling API */
# define CANNM_E_INVALID_PDUID                         (0x03u) /*!< Error code: API service called with wrong PDU-ID */
# define CANNM_E_NET_START_IND                         (0x04u) /*!< Error code: Reception of NM messages in Bus-Sleep Mode */
# define CANNM_E_INIT_FAILED                           (0x05u) /*!< Error code: API service CanNm_Init() called with wrong parameter */
# define CANNM_E_NETWORK_TIMEOUT                       (0x11u) /*!< Error code: NM-Timeout Timer has abnormally expired outside of the Ready Sleep State */
# define CANNM_E_PARAM_POINTER                         (0x12u) /*!< Error code: API service used with invalid pointer parameter (NULL) */
# define CANNM_E_RXINDICATION_DLC_ERROR                (0x20u) /*!< Error code: DLC of received NM message does not match with configured PDU Length */
# define CANNM_E_PDUR_TRIGGERTX_ERROR                  (0x21u) /*!< Error code: Call of PduR_TriggerTransmit failed */
# define CANNM_E_ALREADY_INITIALIZED                   (0x22u) /*!< Error code: The service CanNm_Init() is called while the module is already initialized  */
# define CANNM_E_INVALID_GENDATA                       (0x33u) /*!< Error code: The value of a variable used for write accesses is out of bounds */

# define CANNM_E_ECUM_NO_ERROR                         (0xFFu)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define CANNM_START_SEC_CONST_8BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* CAN NM version (BCD coded). */
extern CONST(uint8, CANNM_CONST) CanNm_MainVersion;
extern CONST(uint8, CANNM_CONST) CanNm_SubVersion;
extern CONST(uint8, CANNM_CONST) CanNm_ReleaseVersion;

# define CANNM_STOP_SEC_CONST_8BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define CANNM_START_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 * CanNm_Init
 **********************************************************************************************************************/
/*! \brief       Initializes component
 *  \details     Initializes all component variables and sets the component state to
 *               initialized.
 *               By default the NM starts in the Bus-Sleep Mode.
 *  \param[in]   cannmConfigPtr              Component configuration structure
 *  \pre         Interrupts are disabled.
 *               Module is uninitialized.
 *               CanNm_InitMemory has been called unless CanNm_ModuleInitialized is initialized
 *               Initialization after CanIf and before call of any NM service.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       SPEC-21986, SPEC-21719, SPEC-21874, SPEC-21793, SPEC-22036, SPEC-21773
 *  \trace       DSGN-CanNm22475
 **********************************************************************************************************************/
/* ESCAN00071960 */
extern FUNC( void, CANNM_CODE ) CanNm_Init( CONSTP2CONST( CanNm_ConfigType, AUTOMATIC, CANNM_INIT_DATA ) cannmConfigPtr );

/*------------------ CAN NM services called by Nm Interface. -----------------*/
/***********************************************************************************************************************
 *  CanNm_PassiveStartUp
 **********************************************************************************************************************/
/*! \brief       Requests the given network passively
 *  \details     Starts the CanNm from the Bus Sleep Mode and triggers
 *               a transition to the Network Mode (Repeat Message State)
 *               This service has no effect if the current state is not equal to
 *               Bus Sleep Mode or Prepare Bus Sleep Mode. In that case E_NOT_OK is returned
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Start of network management failed
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \note        Called from NM Interface
 *  \trace       SPEC-21822, SPEC-21788, SPEC-21772, SPEC-21695, SPEC-21683, SPEC-21874, SPEC-21793, SPEC-50161, 
 *  \trace       SPEC-21797, SPEC-63523
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_PassiveStartUp( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

# if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF )
/***********************************************************************************************************************
 *  CanNm_NetworkRequest
 **********************************************************************************************************************/
/*! \brief       Requests the given network actively
 *  \details     A call of CanNm_NetworkRequest overrides a previous call of CanNm_PassiveStartUp
 *               ECU has a need to communicate on the bus
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Requesting bus-communication was not accepted
 *  \pre         -
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \note        Called from NM Interface
 *  \config      CANNM_PASSIVE_MODE_ENABLED == STD_OFF
 *  \trace       SPEC-21849, SPEC-21841, SPEC-22032, SPEC-21713, SPEC-21691, SPEC-21874, SPEC-21822, SPEC-21793, 
 *  \trace       SPEC-21893, SPEC-21797, SPEC-50207
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_NetworkRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

/***********************************************************************************************************************
 *  CanNm_NetworkRelease
 **********************************************************************************************************************/
/*! \brief       Releases the given network
 *  \details     ECU has no need to communicate on the bus
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Releasing bus-communication was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_PASSIVE_MODE_ENABLED == STD_OFF
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       SPEC-22007, SPEC-21990, SPEC-21903, SPEC-21696, SPEC-21874, SPEC-21793, SPEC-21950, SPEC-21797
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_NetworkRelease( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

/***********************************************************************************************************************
 *  CanNm_GetState
 **********************************************************************************************************************/
/*! \brief       Returns current state and mode of the network management
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[out]  nmStatePtr                  Pointer where the state of the Network Management shall be copied to
 *  \param[out]  nmModePtr                   Pointer where the mode of the Network Management shall be copied to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Getting the NM state was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-21808, SPEC-21874, SPEC-21793, SPEC-21712
 *  \trace       CREQ-239
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_GetState( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                          CONSTP2VAR( Nm_StateType, AUTOMATIC, CANNM_APPL_VAR ) nmStatePtr,
                                                          CONSTP2VAR( Nm_ModeType, AUTOMATIC, CANNM_APPL_VAR ) nmModePtr );

# if ( CANNM_USER_DATA_ENABLED == STD_ON )
#  if ( CANNM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( CANNM_COM_USER_DATA_SUPPORT == STD_OFF )
/***********************************************************************************************************************
 *  CanNm_SetUserData
 **********************************************************************************************************************/
/*! \brief       Sets user data for NM messages transmitted next on the bus
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[in]   nmUserDataPtr               Pointer to User data for the next transmitted NM message shall be copied
 *                                           from
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Setting of user data was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_USER_DATA_ENABLED = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       SPEC-21792, SPEC-21838, SPEC-21909, SPEC-21891, SPEC-22016, SPEC-21874, SPEC-21793, SPEC-21797, SPEC-22006
 *  \trace       CREQ-258
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_SetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                             CONSTP2CONST( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmUserDataPtr );
#  endif

/***********************************************************************************************************************
 *  CanNm_GetUserData
 **********************************************************************************************************************/
/*! \brief       Gets user data from last received NM message
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[in]   nmUserDataPtr               Pointer where user data out of the last received NM message shall be copied
 *                                           to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Getting of user data was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_USER_DATA_ENABLED = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-21792, SPEC-22033, SPEC-22037, SPEC-21852, SPEC-21939, SPEC-21874, SPEC-21793, SPEC-21797
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_GetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                             CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmUserDataPtr );
# endif

# if ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  CanNm_GetNodeIdentifier
 **********************************************************************************************************************/
/*! \brief       Gets node identifier of the last received NM message
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[out]  nmNodeIdPtr                 Pointer where node identifier from the last received NM message shall be
 *                                           copied to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Getting of node identifier was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_NODEIDENABLEDOFCHANNELCONFIG = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-21865, SPEC-21933, SPEC-21874, SPEC-21793, SPEC-21797, SPEC-21823, SPEC-21747
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_GetNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                                   CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmNodeIdPtr );

/***********************************************************************************************************************
 *  CanNm_GetLocalNodeIdentifier
 **********************************************************************************************************************/
/*! \brief       Gets node identifier configured for the local node
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[out]  nmNodeIdPtr                 Pointer where node identifier of the local node shall be copied to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Getting of local node identifier was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_NODEIDENABLEDOFCHANNELCONFIG = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-21900, SPEC-21866, SPEC-21874, SPEC-21793, SPEC-21797, SPEC-21781
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_GetLocalNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                                        CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmNodeIdPtr );
# endif

# if ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  CanNm_RepeatMessageRequest
 **********************************************************************************************************************/
/*! \brief       Requests state change to Repeat Message State
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Repeat Message Request was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       SPEC-50147, SPEC-21734, SPEC-21737, SPEC-21799, SPEC-21738, SPEC-21882, SPEC-21853, SPEC-21874, 
 *  \trace       SPEC-21793, SPEC-21797
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_RepeatMessageRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

# if ( ( CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG == STD_ON ) || ( CANNM_USER_DATA_ENABLED == STD_ON ) || \
      ( CANNM_NODEIDENABLEDOFCHANNELCONFIG == STD_ON ))
/***********************************************************************************************************************
 *  CanNm_GetPduData
 **********************************************************************************************************************/
/*! \brief       Gets the whole PDU data out of the last NM message received from the bus
 *  \details     This includes also the CBV and NID Byte, if configured
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[out]  nmPduDataPtr                Pointer where PDU Data out of the most recently received NM message shall be
 *                                           copied to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Getting the PDU data was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_NODEDETECTIONENABLEDOFCHANNELCONFIG = STD_ON or CANNM_USER_DATA_ENABLED = STD_ON or CANNM_NODEIDENABLEDOFCHANNELCONFIG = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       SPEC-21777, SPEC-21855, SPEC-22005, SPEC-21874, SPEC-21793, SPEC-21797, SPEC-21759
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_GetPduData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                            CONSTP2VAR( uint8, AUTOMATIC, CANNM_APPL_VAR ) nmPduDataPtr );
# endif


# if ( CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  CanNm_RequestBusSynchronization
 **********************************************************************************************************************/
/*! \brief       Requests bus synchronization
 *  \details     Transmission of an asynchronous NM message to support coordination of coupled networks
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Requesting bus synchronization was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_BUS_SYNCHRONIZATION_ENABLED = STD_ON
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       SPEC-21708, SPEC-21791, SPEC-21873, SPEC-21830, SPEC-21692, SPEC-21874, SPEC-21793, SPEC-21797
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_RequestBusSynchronization( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

# if ( CANNM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  CanNm_CheckRemoteSleepIndication
 **********************************************************************************************************************/
/*! \brief       Checks if remote sleep was indicated or not
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[out]  nmRemoteSleepIndPtr         Pointer where PDU Data out of the most recently received NM message
 *                                           shall be copied to
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Checking remote sleep indication was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_REMOTE_SLEEP_IND_ENABLED = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-21907, SPEC-21798, SPEC-21768, SPEC-21942, SPEC-21874, SPEC-21793, SPEC-21870, SPEC-21830, SPEC-21797
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_CheckRemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                                            CONSTP2VAR( boolean, AUTOMATIC, CANNM_APPL_VAR ) nmRemoteSleepIndPtr );
# endif

# if ( CANNM_VERSION_INFO_API == STD_ON )
/***********************************************************************************************************************
 *  CanNm_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief       Returns version information of this module
 *  \details     -
 *  \param[out]  versioninfo                Pointer to where to store the version information of this module
 *  \pre         -
 *  \note        Called from Application
 *  \config      CANNM_VERSION_INFO_API = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-21877, SPEC-21724, SPEC-21689, SPEC-21874, SPEC-21793
 *  \trace       CREQ-240
 **********************************************************************************************************************/
extern FUNC( void, CANNM_CODE ) CanNm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CANNM_APPL_VAR ) versioninfo);
# endif

# if ( CANNM_COMCONTROLENABLEDOFCHANNELCONFIG == STD_ON )
/***********************************************************************************************************************
 *  CanNm_EnableCommunication
 **********************************************************************************************************************/
/*! \brief       Enables NM message transmission control status
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Enabling of NM PDU transmission ability was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_COMCONTROLENABLEDOFCHANNELCONFIG = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       SPEC-21925, SPEC-21955, SPEC-21779, SPEC-21862, SPEC-21775, SPEC-21874, SPEC-21793, SPEC-21797, 
 *  \trace       SPEC-21829, SPEC-21984
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_EnableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

/***********************************************************************************************************************
 *  CanNm_DisableCommunication
 **********************************************************************************************************************/
/*! \brief       Disables NM message transmission control status
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Disabling NM PDU transmission ability was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_COMCONTROLENABLEDOFCHANNELCONFIG = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous FALSE
 *  \trace       SPEC-21810, SPEC-22024, SPEC-21884, SPEC-21767, SPEC-21874, SPEC-21793, SPEC-21723, SPEC-21797, SPEC-21940
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_DisableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

/***********************************************************************************************************************
 *  CanNm_InitMemory
 **********************************************************************************************************************/
/*! \brief       Power-up memory initialization
 *  \details     Initializes component variables in *_INIT_* sections at power up.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Use this function in case these variables are not initialized by the startup code.
 *  \trace       DSGN-CanNm22475
 **********************************************************************************************************************/
extern FUNC( void, CANNM_CODE ) CanNm_InitMemory( void );

# if ( CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON )
/***********************************************************************************************************************
 *  CanNm_SetSleepReadyBit
 **********************************************************************************************************************/
/*! \brief       Sets the NM Coordinator Sleep Ready Bit in the Control Bit Vector
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \param[in]   nmSleepReadyBit             Value written to ReadySleep Bit in CBV (Range: 0,1)
 *  \return      E_OK                        Function successful
 *               E_NOT_OK                    Writing of Sleep Ready Bit was not accepted
 *  \pre         -
 *  \note        Called from NM Interface
 *  \config      CANNM_COORDINATOR_SYNC_SUPPORT = STD_ON
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       SPEC-21997, SPEC-21809, SPEC-21963, SPEC-21874, SPEC-21793, SPEC-21797, SPEC-21858
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_SetSleepReadyBit( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle,
                                                                  CONST( boolean, AUTOMATIC ) nmSleepReadyBit );
# endif

# if ( CANNM_COM_USER_DATA_SUPPORT == STD_ON ) || defined ( CANNM_PN_CALC_FEATURE_ENABLED )
/***********************************************************************************************************************
 *  CanNm_Transmit
 **********************************************************************************************************************/
/*! \brief       Triggers a spontaneous transmission of an NM message
 *  \details     -
 *  \param[in]   CanNmTxPduId  L-PDU handle of CAN L-PDU to be transmitted. This handle specifies the corresponding CAN
 *                             LPDU ID and implicitly the CAN Driver instance as well as the corresponding CAN
 *                             controller device.
 *  \param[in]   PduInfoPtr    Parameter is ignored.
 *  \pre         -
 *  \return      E_OK                        Transmit request was accepted
 *               E_NOT_OK                    Transmit request was not accepted
 *  \note        Called from PduR
 *  \config      CANNM_COM_USER_DATA_SUPPORT = STD_ON or CANNM_PN_CALC_FEATURE_ENABLED = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-21947, SPEC-21910, SPEC-21846, SPEC-21910, SPEC-21848, SPEC-21874, SPEC-21793, SPEC-21797, 
 *  \trace       SPEC-2225434, SPEC-2225435
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_Transmit( VAR( PduIdType, AUTOMATIC ) CanNmTxPduId,
                                                          P2CONST( PduInfoType, AUTOMATIC, CANNM_APPL_VAR ) PduInfoPtr);
# endif

# if ( CANNM_PN_FEATURE_ENABLED == STD_ON )
/***********************************************************************************************************************
 *  CanNm_ConfirmPnAvailability
 **********************************************************************************************************************/
/*! \brief       Enables the PN filter on the given channel
 *  \details     -
 *  \param[in]   nmChannelHandle             System channel handle
 *  \pre         -
 *  \note        Called by CanSM
 *  \config      CANNM_PN_CALC_FEATURE_ENABLED = STD_ON
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       SPEC-21733, SPEC-21714, SPEC-21931, SPEC-21874, SPEC-21793, SPEC-21797, SPEC-21727
 **********************************************************************************************************************/
extern FUNC( void, CANNM_CODE ) CanNm_ConfirmPnAvailability( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
# endif

/***********************************************************************************************************************
 *  CanNm_CancelTransmit()
 **********************************************************************************************************************/
/*! \brief         No functionality provided
 *  \details       This function is only provided to avoid compiler errors.
 *  \param[in]     CanNmTxSduId           Parameter not used
 *  \return        E_OK                   Function call was successful
 *  \return        E_NOT_OK               Module was not initialized
 *  \context       TASK|ISR2
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           -
 *  \trace         CREQ-148062
 **********************************************************************************************************************/
extern FUNC( Std_ReturnType, CANNM_CODE ) CanNm_CancelTransmit( VAR( PduIdType, AUTOMATIC ) CanNmTxSduId );

# define CANNM_STOP_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif  /* CANNM_H */

/*
 * \exclusivearea CANNM_EXCLUSIVE_AREA_0
 * Protects the global Pn Cluster requests from being modified from RxIndication while copying to temporary buffer.
 * \length SHORT At max 7 bytes are copied within this exclusive area.
 * \usedin CanNm_MainFunction, CanNm_RxIndication
 * \exclude CanNm_MainFunction, CanNm_RxIndication
 * \protects CanNm_PnClusterReqExtNew, CanNm_PnClusterReqNew (read)
 * \endexclusivearea
 *
 * \exclusivearea CANNM_EXCLUSIVE_AREA_1
 * Protects the global TX message data from being modified while copying to the Sdu.
 * \length SHORT At max 8 bytes are copied within this exclusive area.
 * \usedin CanNm_MainFunction, CanNm_RequestBusSynchronization
 * \exclude CanNm_SetUserData, CanNm_SetSleepReadyBit
 * \protects CanNm_TxMessageData (read)
 * \endexclusivearea
 *
 * \exclusivearea CANNM_EXCLUSIVE_AREA_2
 * Ensures that the global TX message buffer is not read while user data is written to it.
 * \length SHORT At max 8 bytes are copied within this exclusive area.
 * \usedin CanNm_SetUserData
 * \exclude CanNm_MainFunction, CanNm_RequestBusSynchronization, CanNm_SetSleepReadyBit
 * \protects CanNm_TxMessageData (write)
 * \endexclusivearea
 *
 * \exclusivearea CANNM_EXCLUSIVE_AREA_3
 * Ensures that the global TX message buffer is not read while user data is written to it.
 * \length SHORT At max 8 bytes are copied within this exclusive area.
 * \usedin CanNm_SetSleepReadyBit
 * \exclude CanNm_MainFunction, CanNm_RequestBusSynchronization, CanNm_SetUserData
 * \protects CanNm_TxMessageData (write)
 * \endexclusivearea
 *
 * \exclusivearea CANNM_EXCLUSIVE_AREA_4
 * Ensures that the global RX message buffer is not read while data is written to it.
 * \length SHORT At max 8 bytes are copied within this exclusive area.
 * \usedin CanNm_RxIndication
 * \exclude CanNm_MainFunction, CanNm_GetUserData, CanNm_GetNodeIdentifier, CanNm_GetPduData
 * \protects CanNm_RxMessageData (write)
 * \endexclusivearea
 *
 * \exclusivearea CANNM_EXCLUSIVE_AREA_5
 * Ensures that the global RX message buffer is not written while user data is read from it.
 * \length SHORT At max 8 bytes are copied within this exclusive area.
 * \usedin CanNm_GetUserData, CanNm_GetPduData
 * \exclude CanNm_RxIndication
 * \protects CanNm_RxMessageData (read)
 * \endexclusivearea
 *
 * \exclusivearea CANNM_EXCLUSIVE_AREA_6
 * Ensures that the MsgTimeoutTimer is not written while data is modified.
 * Note: This critical section can be left empty when CanNm_MainFunction and Nm_MainFunction have the same task.
 * \length SHORT Usually one rmw of the variable CanNm_MsgTimeoutTimer is done.
 * \usedin CanNm_MainFunction
 * \exclude CanNm_RequestBusSynchronization
 * \protects CanNm_MsgTimeoutTimer
 * \endexclusivearea
 */
/**********************************************************************************************************************
 *  END OF FILE: CanNm.h
 *********************************************************************************************************************/
